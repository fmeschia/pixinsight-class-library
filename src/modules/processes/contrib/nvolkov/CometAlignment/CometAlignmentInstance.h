//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard CometAlignment Process Module Version 1.2.6
// ----------------------------------------------------------------------------
// CometAlignmentInstance.h - Released 2021-04-09T19:41:49Z
// ----------------------------------------------------------------------------
// This file is part of the standard CometAlignment PixInsight module.
//
// Copyright (c) 2012-2018 Nikolay Volkov
// Copyright (c) 2003-2018 Pleiades Astrophoto S.L.
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
//    by Pleiades Astrophoto and its contributors (https://pixinsight.com/)."
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

#ifndef __CometAlignmentInstance_h
#define __CometAlignmentInstance_h

#include <pcl/FileFormatInstance.h>
#include <pcl/PixelInterpolation.h>
#include <pcl/ProcessImplementation.h>

#include "CometAlignmentParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class CometAlignmentInterface;
class CAThread;
struct CAThreadData;

typedef IndirectArray<CAThread> thread_list;

class CometAlignmentInstance : public ProcessImplementation
{
public:

   CometAlignmentInstance( const MetaProcess* );
   CometAlignmentInstance( const CometAlignmentInstance& );

   void Assign( const ProcessImplementation& ) override;
   bool CanExecuteOn( const View&, String& whyNot ) const override;
   bool IsHistoryUpdater( const View& v ) const override;
   bool CanExecuteGlobal( String& whyNot ) const override;
   bool ExecuteGlobal() override;
   void* LockParameter( const MetaParameter*, size_type tableRow ) override;
   bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow ) override;
   size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const override;

private:

   struct ImageItem
   {
      String path;      // absolute file path
      pcl_bool enabled = true; // if disabled, skip (ignore) this image
      String date;      // DATE-OBS yyyy-mm-ddThh:mm:ss[.sss...]
      double Jdate;     // Julian Date
      double x = 0, y = 0;      // Comet coordinates
      String drzPath;   // drizzle data file

      ImageItem( const String& p = String(), const String& d = String() )
         : path( p )
         , date( d )
         , Jdate( GetJdate( d ) )
      {
      }

      ImageItem( const ImageItem& i )
         : path( i.path )
         , enabled( i.enabled )
         , date( i.date )
         , Jdate( i.Jdate )
         , x( i.x )
         , y( i.y )
         , drzPath( i.drzPath )
      {
      }

      double GetJdate( const String& d ) // Convert "yyyy-mm-ddThh:mm:ss[.sss...]" to Julian Date
      {
         if ( d.IsEmpty() )
            return 0;
         try
         {
            // 1234567890123456789
            // yyyy-mm-ddThh:mm:ss[.sss...]

            if ( d.Length() < 19 )
               throw 0;

            int year, month, day, h, m;
            double s;

            if ( !d.Substring( 0, 4 ).TryToInt( year, 10 ) )
               throw 0;
            if ( !d.Substring( 5, 2 ).TryToInt( month, 10 ) )
               throw 0;
            if ( !d.Substring( 8, 2 ).TryToInt( day, 10 ) )
               throw 0;
            if ( !d.Substring( 11, 2 ).TryToInt( h, 10 ) )
               throw 0;
            if ( !d.Substring( 14, 2 ).TryToInt( m, 10 ) )
               throw 0;
            if ( !d.Substring( 17 ).TryToDouble( s ) )
               throw 0;

            double dayf = ( 3600.0 * h + 60.0 * m + s ) / 86400;
            return CalendarTimeToJD( year, month, day, dayf );
         }
         catch ( ... )
         {
            throw Error( "Can't convert DATE-OBS keyword value \'" + d + "\' to a Julian day number." );
         }
      }
   };

   typedef Array<ImageItem> image_list;

   ImageVariant* m_OperandImage;
   Rect m_geometry;

   image_list p_targetFrames;
   String p_inputHints;
   String p_outputHints;
   String p_outputDir;
   String p_outputExtension;
   pcl_bool p_overwrite;
   String p_prefix;
   String p_postfix;
   size_t p_reference;
   String p_subtractFile;
   pcl_bool p_subtractMode; // true == move operand and subtract from target, false = subtract operand from target and move
   pcl_bool p_operandIsDI;  // true == Subtraction Operand have DrizzleIntegration origin
   pcl_bool p_normalize;
   pcl_bool p_enableLinearFit;
   float p_rejectLow;
   float p_rejectHigh;
   pcl_bool p_drzSaveSA;
   pcl_bool p_drzSaveCA;
   pcl_enum p_pixelInterpolation;   // bicubic spline | bilinear | nearest neighbor
   float p_linearClampingThreshold; // for bicubic spline

   // -------------------------------------------------------------------------

   thread_list LoadTargetFrame( size_t fileIndex );
   String OutputImgPath( const String&, const String& );
   void Save( const ImageVariant&, CAThread*, const int8 );
   void SaveImage( CAThread* );
   void InitPixelInterpolation();
   DImage GetCometImage( const String& );
   ImageVariant* LoadOperandImage( const String& filePath );

   friend class CAThread;
   friend class CometAlignmentInterface;
   friend class LinearFitEngine;
};

// ----------------------------------------------------------------------------

} // pcl

#endif // __CometAlignmentInstance_h

// ----------------------------------------------------------------------------
// EOF CometAlignmentInstance.h - Released 2021-04-09T19:41:49Z
