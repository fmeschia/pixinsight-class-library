// ****************************************************************************
// PixInsight Class Library - PCL 02.00.13.0689
// Standard Geometry Process Module Version 01.01.00.0245
// ****************************************************************************
// ResampleParameters.cpp - Released 2014/10/29 07:34:55 UTC
// ****************************************************************************
// This file is part of the standard Geometry PixInsight module.
//
// Copyright (c) 2003-2014, Pleiades Astrophoto S.L. All Rights Reserved.
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
// ****************************************************************************

#include "ResampleParameters.h"

namespace pcl
{

XSize*                  TheXSizeParameter = 0;
YSize*                  TheYSizeParameter = 0;
ResampleMode*           TheResampleModeParameter = 0;
AbsoluteResampleMode*   TheAbsoluteResampleModeParameter = 0;
XResolution*            TheXResolutionResampleParameter = 0;
YResolution*            TheYResolutionResampleParameter = 0;
MetricResolution*       TheMetricResolutionResampleParameter = 0;
ForceResolution*        TheForceResolutionResampleParameter = 0;
InterpolationAlgorithm* TheInterpolationAlgorithmResampleParameter = 0;
ClampingThreshold*      TheClampingThresholdResampleParameter = 0;
Smoothness*             TheSmoothnessResampleParameter = 0;

// ----------------------------------------------------------------------------

XSize::XSize( MetaProcess* P ) : MetaDouble( P )
{
   TheXSizeParameter = this;
}

IsoString XSize::Id() const
{
   return "xSize";
}

int XSize::Precision() const
{
   return 4;
}

double XSize::DefaultValue() const
{
   return 1;
}

// ----------------------------------------------------------------------------

YSize::YSize( MetaProcess* P ) : MetaDouble( P )
{
   TheYSizeParameter = this;
}

IsoString YSize::Id() const
{
   return "ySize";
}

int YSize::Precision() const
{
   return 4;
}

double YSize::DefaultValue() const
{
   return 1;
}

// ----------------------------------------------------------------------------

ResampleMode::ResampleMode( MetaProcess* P ) : MetaEnumeration( P )
{
   TheResampleModeParameter = this;
}

IsoString ResampleMode::Id() const
{
   return "mode";
}

size_type ResampleMode::NumberOfElements() const
{
   return NumberOfResampleModes;
}

IsoString ResampleMode::ElementId( size_type i ) const
{
   switch ( i )
   {
   default:
   case RelativeDimensions:   return "RelativeDimensions";
   case AbsolutePixels:       return "AbsolutePixels";
   case AbsoluteCentimeters:  return "AbsoluteCentimeters";
   case AbsoluteInches:       return "AbsoluteInches";
   case ForceArea:            return "ForceArea";
   }
}

int ResampleMode::ElementValue( size_type i ) const
{
   return int( i );
}

size_type ResampleMode::DefaultValueIndex() const
{
   return Default;
}

// ----------------------------------------------------------------------------

AbsoluteResampleMode::AbsoluteResampleMode( MetaProcess* P ) : MetaEnumeration( P )
{
   TheAbsoluteResampleModeParameter = this;
}

IsoString AbsoluteResampleMode::Id() const
{
   return "absoluteMode";
}

size_type AbsoluteResampleMode::NumberOfElements() const
{
   return NumberOfAbsoluteResampleModes;
}

IsoString AbsoluteResampleMode::ElementId( size_type i ) const
{
   switch ( i )
   {
   default:
   case ForceWidthAndHeight:  return "ForceWidthAndHeight";
   case ForceWidth:           return "ForceWidth";
   case ForceHeight:          return "ForceHeight";
   }
}

int AbsoluteResampleMode::ElementValue( size_type i ) const
{
   return int( i );
}

size_type AbsoluteResampleMode::DefaultValueIndex() const
{
   return Default;
}

// ----------------------------------------------------------------------------

} // pcl

// ****************************************************************************
// EOF ResampleParameters.cpp - Released 2014/10/29 07:34:55 UTC