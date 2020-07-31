//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.0
// ----------------------------------------------------------------------------
// Standard ImageIntegration Process Module Version 1.25.0
// ----------------------------------------------------------------------------
// MapIntegrationEngine.cpp - Released 2020-07-31T19:33:39Z
// ----------------------------------------------------------------------------
// This file is part of the standard ImageIntegration PixInsight module.
//
// Copyright (c) 2003-2020 Pleiades Astrophoto S.L. All Rights Reserved.
//
// Redistribution and use in both source and binary forms, with or without
// modification, is permitted provided that the following conditions are met:
//
// 1. All redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. All redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the names "PixInsight" and "Pleiades Astrophoto", nor the names
//    of their contributors, may be used to endorse or promote products derived
//    from this software without specific prior written permission. For written
//    permission, please contact info@pixinsight.com.
//
// 4. All products derived from this software, in any form whatsoever, must
//    reproduce the following acknowledgment in the end-user documentation
//    and/or other materials provided with the product:
//
//    "This product is based on software from the PixInsight project, developed
//    by Pleiades Astrophoto and its contributors (http://pixinsight.com/)."
//
//    Alternatively, if that is where third-party acknowledgments normally
//    appear, this acknowledgment must be reproduced in the product itself.
//
// THIS SOFTWARE IS PROVIDED BY PLEIADES ASTROPHOTO AND ITS CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PLEIADES ASTROPHOTO OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, BUSINESS
// INTERRUPTION; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; AND LOSS OF USE,
// DATA OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

#include "IntegrationFile.h"
#include "MapIntegrationEngine.h"

namespace pcl
{

// ----------------------------------------------------------------------------

MapIntegrationEngine::MapIntegrationEngine( const ImageIntegrationInstance& instance, StatusMonitor& monitor,
                                            const DVector& zeroOffset, DVector& location, const scale_estimates& scale,
                                            int channel, int y0, int numberOfRows,
                                            float* result32, double* result64 )
   : IntegrationEngineBase( instance, monitor )
   , m_d( zeroOffset ), m_m( location ), m_s( scale )
   , m_channel( channel ), m_y0( y0 ), m_numberOfRows( numberOfRows )
   , m_result32( result32 ), m_result64( result64 )
{
   Array<size_type> L = Thread::OptimalThreadLoads( m_numberOfRows );
   for ( int i = 0, n = 0; i < int( L.Length() ); n += int( L[i++] ) )
      m_threads << new IntegrationThread( *this, n, n + int( L[i] ) );
}

// ----------------------------------------------------------------------------

MapIntegrationEngine::~MapIntegrationEngine()
{
   m_threads.Destroy();
}

// ----------------------------------------------------------------------------

void MapIntegrationEngine::Integrate()
{
   if ( !m_threads.IsEmpty() )
   {
      m_threadData.total = size_type( m_numberOfRows );
      m_threadData.count = 0;
      AbstractImage::RunThreads( m_threads, m_threadData );
      m_monitor = m_threadData.status;
   }
}

// ----------------------------------------------------------------------------

#define E   m_engine
#define I   m_engine.m_instance

// ----------------------------------------------------------------------------

void MapIntegrationEngine::IntegrationThread::Run()
{
   INIT_THREAD_MONITOR()

   float* result32 = nullptr;
   double* result64 = nullptr;
   if ( I.p_generate64BitResult )
      result64 = E.m_result64 + size_type( m_firstStack )*size_type( IntegrationFile::Width() );
   else
      result32 = E.m_result32 + size_type( m_firstStack )*size_type( IntegrationFile::Width() );

   for ( int k = m_firstStack, y = E.m_y0+k; k < m_endStack; ++k, ++y )
   {
      for ( int x = 0; x < IntegrationFile::Width(); ++x )
      {
         int n = 0;
         DVector stack( IntegrationFile::NumberOfFiles() );
         IVector index( IntegrationFile::NumberOfFiles() );
         for ( int i = 0; i < IntegrationFile::NumberOfFiles(); ++i )
            if ( IntegrationFile::FileByIndex( i ).RejectionMap()( x, y, E.m_channel ) == 0 )
            {
               stack[n] = IntegrationFile::FileByIndex( i )[k][x];
               index[n] = i;
               ++n;
            }

         pcl_enum thisCombination = I.p_combination;
         if ( n == 0 )
         {
            /*
             * If all pixels have been rejected, take the median as the final
             * pixel value for this stack.
             */
            for ( int i = 0; i < IntegrationFile::NumberOfFiles(); ++i )
            {
               stack[i] = IntegrationFile::FileByIndex( i )[k][x];
               index[i] = i;
            }
            thisCombination = IICombination::Median;
            n = IntegrationFile::NumberOfFiles();
         }

         const DVector& d = E.m_d;
         const DVector& m = E.m_m;
         const scale_estimates& s = E.m_s;

         /*
          * Normalize/scale output
          */
         switch ( I.p_normalization )
         {
         case IINormalization::NoNormalization:
            break;
         default:
         case IINormalization::Additive:
            for ( int i = 0; i < n; ++i )
               stack[i] += d[index[i]];
            break;
         case IINormalization::Multiplicative:
            for ( int i = 0; i < n; ++i )
               stack[i] *= d[index[i]];
            break;
         case IINormalization::AdditiveWithScaling:
            for ( int i = 0; i < n; ++i )
               stack[i] = (stack[i] - m[index[i]])*double( s[index[i]] ) + m[0];
            break;
         case IINormalization::MultiplicativeWithScaling:
            for ( int i = 0; i < n; ++i )
               stack[i] = (stack[i] / m[index[i]])*double( s[index[i]] ) * m[0];
            break;
         case IINormalization::LocalNormalization:
            for ( int i = 0; i < n; ++i )
               stack[i] = IntegrationFile::FileByIndex( index[i] ).Normalize( stack[i], x, y, E.m_channel );
            break;
         case IINormalization::AdaptiveNormalization:
            {
               const AdaptiveNormalizationData& a0 = IntegrationFile::FileByIndex( 0 ).AdaptiveNormalization();
               double m0 = a0.Location( x, y, E.m_channel );
               double s00 = a0.ScaleLow( x, y, E.m_channel );
               double s10 = a0.ScaleHigh( x, y, E.m_channel );
               for ( int i = 0; i < n; ++i )
               {
                  const AdaptiveNormalizationData& a = IntegrationFile::FileByIndex( index[i] ).AdaptiveNormalization();
                  double m = a.Location( x, y, E.m_channel );
                  stack[i] = (stack[i] - m)
                        * ((stack[i] <= m) ? s00/a.ScaleLow( x, y, E.m_channel ) : s10/a.ScaleHigh( x, y, E.m_channel ))
                        + m0;
               }
            }
            break;
         }

         /*
          * Integrate
          */
         double f;
         switch ( thisCombination )
         {
         default:
         case IICombination::Average:
            {
               f = 0;
               if ( I.p_weightMode == IIWeightMode::DontCare )
               {
                  for ( int i = 0; i < n; ++i )
                     f += stack[i];
                  f /= n;
               }
               else
               {
                  double ws = 0;
                  for ( int i = 0; i < n; ++i )
                  {
                     double w = IntegrationFile::FileByIndex( index[i] ).Weight( E.m_channel );
                     f += w*stack[i];
                     ws += w;
                  }
                  f /= ws;
               }
            }
            break;

         case IICombination::Median:
         case IICombination::Minimum:
         case IICombination::Maximum:
            Sort( stack.Begin(), stack.At( n ) );
            switch ( thisCombination )
            {
            default:
            case IICombination::Median:
               {
                  int n2 = n >> 1;
                  if ( n & 1 )
                     f = stack[n2];
                  else
                     f = 0.5*(stack[n2] + stack[n2-1]);
               }
               break;
            case IICombination::Minimum:
               f = stack[0];
               break;
            case IICombination::Maximum:
               f = stack[n-1];
               break;
            }
            break;
         }

         if ( result32 != nullptr )
            *result32++ = float( f );
         else
            *result64++ = f;
      }

      UPDATE_THREAD_MONITOR( 10 )
   }
}

// ----------------------------------------------------------------------------

#undef E
#undef I

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF MapIntegrationEngine.cpp - Released 2020-07-31T19:33:39Z