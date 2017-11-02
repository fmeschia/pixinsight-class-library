//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.07.0873
// ----------------------------------------------------------------------------
// Standard SubframeSelector Process Module Version 01.00.02.0261
// ----------------------------------------------------------------------------
// SubframeSelectorMeasureData.h - Released 2017-08-01T14:26:58Z
// ----------------------------------------------------------------------------
// This file is part of the standard SubframeSelector PixInsight module.
//
// Copyright (c) 2003-2017 Pleiades Astrophoto S.L. All Rights Reserved.
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

#ifndef __SubframeSelectorMeasureData_h
#define __SubframeSelectorMeasureData_h

#include <pcl/MetaParameter.h>
#include "SubframeSelectorParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

struct MeasureData
{
   String   path;
   double   fwhm;
   double   eccentricity;

   MeasureData( const String& p = String( "" ) ) :
           path( p ),
           fwhm( TheSSMeasurementFWHMParameter->DefaultValue() ),
           eccentricity( TheSSMeasurementEccentricityParameter->DefaultValue() )
   {
   }

   MeasureData( const MeasureData& x ) = default;
};

// ----------------------------------------------------------------------------

struct MeasureItem
{
   uint16   index;
   pcl_bool enabled;
   pcl_bool locked;
   String   path;
   float    weight;
   float    fwhm;
   float    eccentricity;

   MeasureItem( uint16 i, const String& p = String( "" ) ) :
           index( i ),
           enabled( TheSSMeasurementEnabledParameter->DefaultValue() ),
           locked( TheSSMeasurementLockedParameter->DefaultValue() ),
           path( p ),
           weight( TheSSMeasurementWeightParameter->DefaultValue() ),
           fwhm( TheSSMeasurementFWHMParameter->DefaultValue() ),
           eccentricity( TheSSMeasurementEccentricityParameter->DefaultValue() )
   {
   }

   MeasureItem( const MeasureItem& x ) = default;

   void Input( const MeasureData& measureData )
   {
      path = measureData.path;
      fwhm = measureData.fwhm;
      eccentricity = measureData.eccentricity;
   }

   float FWHM( const float& subframeScale, const int& scaleUnit ) const
   {
      if ( scaleUnit == SSScaleUnit::ArcSeconds )
         return fwhm * subframeScale;
      if ( scaleUnit == SSScaleUnit::Pixel )
         return fwhm;
      return fwhm;
   }

   String JavaScriptParameters( const float& subframeScale, const int& scaleUnit ) const
   {
      return String().Format( "let Index = %i;\n", index ) +
              String().Format( "let Weight = %.4f;\n", weight ) +
              String().Format( "let FWHM = %.4f;\n", FWHM( subframeScale, scaleUnit ) ) +
              String().Format( "let Eccentricity = %.4f;\n", eccentricity );
   }

   double SortingValue( pcl_enum sortBy ) const
   {
      switch ( sortBy )
      {
      case SSSortingProperty::Index: return index;
      case SSSortingProperty::Weight: return weight;
      case SSSortingProperty::FWHM: return fwhm;
      case SSSortingProperty::Eccentricity: return eccentricity;
      default: return 0; // ?
      }
   }
};

// ----------------------------------------------------------------------------

struct MeasureUtils
{
   // Rudimentary first-line check for a JS Expression
   static bool IsValidExpression( const String& expression )
   {
      if ( expression.IsEmpty() )
         return true;

      int pOpen = 0;
      int pClose = 0;
      int a = 0;
      int o = 0;
      for ( String::const_iterator i = expression.Begin(); i < expression.End(); ++i )
      {
         if ( !isalnum( *i ) && *i != '(' && *i != ')' && *i != '&' && *i != '|' && *i != ' '
              && *i != '*' && *i != '+' && *i != '-' && *i != '/' && *i != '.'
              && *i != '<' && *i != '>' && *i != '=' && *i != '!' )
            return false;

         if ( *i == '(' )
            ++pOpen;
         if ( *i == ')' )
            ++pClose;

         if ( *i == '&' )
            ++a;
         if ( *i == '|' )
            ++o;
      }

      return pOpen == pClose && a % 2 == 0 && o % 2 == 0;
   }
};

// ----------------------------------------------------------------------------


} // pcl

#endif   // __SubframeSelectorMeasureData_h

// ----------------------------------------------------------------------------
// EOF SubframeSelectorMeasureData.h - Released 2017-08-01T14:26:58Z
