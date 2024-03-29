//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard CometAlignment Process Module Version 1.2.6
// ----------------------------------------------------------------------------
// CometAlignmentParameters.cpp - Released 2021-04-09T19:41:49Z
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

#include "CometAlignmentParameters.h"

namespace pcl
{
// ----------------------------------------------------------------------------

CATargetFrames* TheTargetFrames = nullptr;

CATargetFramePath* TheTargetFramePath = nullptr;
CATargetFrameEnabled* TheTargetFrameEnabled = nullptr;

CATargetFrameDate* TheTargetFrameDate = nullptr;
CATargetFrameJDate* TheTargetFrameJDate = nullptr;
CATargetFrameX* TheTargetFrameX = nullptr;
CATargetFrameY* TheTargetFrameY = nullptr;
CADrizzlePath* TheDrizzlePath = nullptr;

CAInputHints* TheCAInputHintsParameter = nullptr;
CAOutputHints* TheCAOutputHintsParameter = nullptr;
CAOutputDir* TheOutputDir = nullptr;
CAOutputExtension* TheCAOutputExtensionParameter = nullptr;
CAPrefix* ThePrefix = nullptr;
CAPostfix* ThePostfix = nullptr;
CAOverwrite* TheOverwrite = nullptr;

CAReference* TheReference = nullptr;

CASubtractFile* TheSubtractFile = nullptr;
CASubtractMode* TheSubtractMode = nullptr;
CAOperandIsDI* TheOperandIsDI = nullptr;
CANormalize* TheNormalize = nullptr;
CAEnableLinearFit* TheEnableLinearFit = nullptr;
CARejectLow* TheRejectLow = nullptr;
CARejectHigh* TheRejectHigh = nullptr;
CADrzSaveSA* TheDrzSaveSA = nullptr;
CADrzSaveCA* TheDrzSaveCA = nullptr;

CAPixelInterpolation* ThePixelInterpolationParameter = nullptr;
CALinearClampingThreshold* TheLinearClampingThresholdParameter = nullptr;

// ----------------------------------------------------------------------------

CATargetFrames::CATargetFrames( MetaProcess* P )
   : MetaTable( P )
{
   TheTargetFrames = this;
}

IsoString CATargetFrames::Id() const
{
   return "targetFrames";
}

// ----------------------------------------------------------------------------

CATargetFrameEnabled::CATargetFrameEnabled( MetaTable* T )
   : MetaBoolean( T )
{
   TheTargetFrameEnabled = this;
}

IsoString CATargetFrameEnabled::Id() const
{
   return "enabled";
}

bool CATargetFrameEnabled::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CATargetFramePath::CATargetFramePath( MetaTable* T )
   : MetaString( T )
{
   TheTargetFramePath = this;
}

IsoString CATargetFramePath::Id() const
{
   return "path";
}

// ----------------------------------------------------------------------------

CATargetFrameDate::CATargetFrameDate( MetaTable* T )
   : MetaString( T )
{
   TheTargetFrameDate = this;
}

IsoString CATargetFrameDate::Id() const
{
   return "date";
}

// ----------------------------------------------------------------------------

CATargetFrameJDate::CATargetFrameJDate( MetaTable* T )
   : MetaDouble( T )
{
   TheTargetFrameJDate = this;
}

IsoString CATargetFrameJDate::Id() const
{
   return "jDate";
}

int CATargetFrameJDate::Precision() const
{
   return 15;
}

// ----------------------------------------------------------------------------

CATargetFrameX::CATargetFrameX( MetaTable* T )
   : MetaDouble( T )
{
   TheTargetFrameX = this;
}

IsoString CATargetFrameX::Id() const
{
   return "x";
}

int CATargetFrameX::Precision() const
{
   return 8;
}

double CATargetFrameX::MinimumValue() const
{
   return 0;
}

double CATargetFrameX::MaximumValue() const
{
   return 100000;
}

// ----------------------------------------------------------------------------

CATargetFrameY::CATargetFrameY( MetaTable* T )
   : MetaDouble( T )
{
   TheTargetFrameY = this;
}

IsoString CATargetFrameY::Id() const
{
   return "y";
}

int CATargetFrameY::Precision() const
{
   return 8;
}

double CATargetFrameY::MinimumValue() const
{
   return 0;
}

double CATargetFrameY::MaximumValue() const
{
   return 100000;
}

// ----------------------------------------------------------------------------

CADrizzlePath::CADrizzlePath( MetaTable* T )
   : MetaString( T )
{
   TheDrizzlePath = this;
}

IsoString CADrizzlePath::Id() const
{
   return "drizzlePath";
}

// ----------------------------------------------------------------------------

CAInputHints::CAInputHints( MetaProcess* P )
   : MetaString( P )
{
   TheCAInputHintsParameter = this;
}

IsoString CAInputHints::Id() const
{
   return "inputHints";
}

// ----------------------------------------------------------------------------

CAOutputHints::CAOutputHints( MetaProcess* P )
   : MetaString( P )
{
   TheCAOutputHintsParameter = this;
}

IsoString CAOutputHints::Id() const
{
   return "outputHints";
}

// ----------------------------------------------------------------------------

CAOutputDir::CAOutputDir( MetaProcess* P )
   : MetaString( P )
{
   TheOutputDir = this;
}

IsoString CAOutputDir::Id() const
{
   return "outputDir";
}

String CAOutputDir::DefaultValue() const
{
   return String();
}

// ----------------------------------------------------------------------------

CAOutputExtension::CAOutputExtension( MetaProcess* P )
   : MetaString( P )
{
   TheCAOutputExtensionParameter = this;
}

IsoString CAOutputExtension::Id() const
{
   return "outputExtension";
}

String CAOutputExtension::DefaultValue() const
{
   return ".xisf";
}

// ----------------------------------------------------------------------------

CAPrefix::CAPrefix( MetaProcess* P )
   : MetaString( P )
{
   ThePrefix = this;
}

IsoString CAPrefix::Id() const
{
   return "prefix";
}

String CAPrefix::DefaultValue() const
{
   return "";
}

// ----------------------------------------------------------------------------

CAPostfix::CAPostfix( MetaProcess* P )
   : MetaString( P )
{
   ThePostfix = this;
}

IsoString CAPostfix::Id() const
{
   return "postfix";
}

String CAPostfix::DefaultValue() const
{
   return "_ca";
}

// ----------------------------------------------------------------------------

CAOverwrite::CAOverwrite( MetaProcess* P )
   : MetaBoolean( P )
{
   TheOverwrite = this;
}

IsoString CAOverwrite::Id() const
{
   return "overwrite";
}

bool CAOverwrite::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CAReference::CAReference( MetaProcess* P )
   : MetaUInt16( P )
{
   TheReference = this;
}

IsoString CAReference::Id() const
{
   return "reference";
}

// ----------------------------------------------------------------------------

CASubtractFile::CASubtractFile( MetaProcess* P )
   : MetaString( P )
{
   TheSubtractFile = this;
}

IsoString CASubtractFile::Id() const
{
   return "subtractFile";
}

String CASubtractFile::DefaultValue() const
{
   return "";
}

// ----------------------------------------------------------------------------

CASubtractMode::CASubtractMode( MetaProcess* P )
   : MetaBoolean( P )
{
   TheSubtractMode = this;
}

IsoString CASubtractMode::Id() const
{
   return "subtractMode";
}

bool CASubtractMode::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CANormalize::CANormalize( MetaProcess* P )
   : MetaBoolean( P )
{
   TheNormalize = this;
}

IsoString CANormalize::Id() const
{
   return "normalize";
}

bool CANormalize::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CAEnableLinearFit::CAEnableLinearFit( MetaProcess* P )
   : MetaBoolean( P )
{
   TheEnableLinearFit = this;
}

IsoString CAEnableLinearFit::Id() const
{
   return "enableLinearFit";
}

bool CAEnableLinearFit::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CARejectLow::CARejectLow( MetaProcess* P )
   : MetaFloat( P )
{
   TheRejectLow = this;
}

IsoString CARejectLow::Id() const
{
   return "rejectLow";
}

int CARejectLow::Precision() const
{
   return 6;
}

double CARejectLow::MinimumValue() const
{
   return 0;
}

double CARejectLow::MaximumValue() const
{
   return 1;
}

double CARejectLow::DefaultValue() const
{
   return 0;
}

// ----------------------------------------------------------------------------

CARejectHigh::CARejectHigh( MetaProcess* P )
   : MetaFloat( P )
{
   TheRejectHigh = this;
}

IsoString CARejectHigh::Id() const
{
   return "rejectHigh";
}

int CARejectHigh::Precision() const
{
   return 6;
}

double CARejectHigh::MinimumValue() const
{
   return 0;
}

double CARejectHigh::MaximumValue() const
{
   return 1;
}

double CARejectHigh::DefaultValue() const
{
   return 0.92;
}

// ----------------------------------------------------------------------------

CADrzSaveSA::CADrzSaveSA( MetaProcess* P )
   : MetaBoolean( P )
{
   TheDrzSaveSA = this;
}

IsoString CADrzSaveSA::Id() const
{
   return "drzSaveStarsAligned";
}

bool CADrzSaveSA::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CADrzSaveCA::CADrzSaveCA( MetaProcess* P )
   : MetaBoolean( P )
{
   TheDrzSaveCA = this;
}

IsoString CADrzSaveCA::Id() const
{
   return "drzSaveCometAligned";
}

bool CADrzSaveCA::DefaultValue() const
{
   return true;
}
// ----------------------------------------------------------------------------

CAOperandIsDI::CAOperandIsDI( MetaProcess* P )
   : MetaBoolean( P )
{
   TheOperandIsDI = this;
}

IsoString CAOperandIsDI::Id() const
{
   return "operandIsDI";
}

bool CAOperandIsDI::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

CAPixelInterpolation::CAPixelInterpolation( MetaProcess* p )
   : MetaEnumeration( p )
{
   ThePixelInterpolationParameter = this;
}

IsoString CAPixelInterpolation::Id() const
{
   return "pixelInterpolation";
}

size_type CAPixelInterpolation::NumberOfElements() const
{
   return NumberOfInterpolationAlgorithms;
}

IsoString CAPixelInterpolation::ElementId( size_type i ) const
{
   switch ( i )
   {
   case NearestNeighbor:
      return "NearestNeighbor";
   case Bilinear:
      return "Bilinear";
   default:
   case BicubicSpline:
      return "BicubicSpline";
   case BicubicBSpline:
      return "BicubicBSpline";
   case Lanczos3:
      return "Lanczos3";
   case Lanczos4:
      return "Lanczos4";
   case Lanczos5:
      return "Lanczos5";
   case MitchellNetravaliFilter:
      return "MitchellNetravaliFilter";
   case CatmullRomSplineFilter:
      return "CatmullRomSplineFilter";
   case CubicBSplineFilter:
      return "CubicBSplineFilter";
   case Auto:
      return "Auto";
   }
}

int CAPixelInterpolation::ElementValue( size_type i ) const
{
   return int( i );
}

size_type CAPixelInterpolation::DefaultValueIndex() const
{
   return size_type( Default );
}

// ----------------------------------------------------------------------------

CALinearClampingThreshold::CALinearClampingThreshold( MetaProcess* p )
   : MetaFloat( p )
{
   TheLinearClampingThresholdParameter = this;
}

IsoString CALinearClampingThreshold::Id() const
{
   return "linearClampingThreshold";
}

int CALinearClampingThreshold::Precision() const
{
   return 2;
}

double CALinearClampingThreshold::DefaultValue() const
{
   return 0.3;
} // __PCL_BICUBIC_SPLINE_CLAMPING_THRESHOLD;

double CALinearClampingThreshold::MinimumValue() const
{
   return 0;
}

double CALinearClampingThreshold::MaximumValue() const
{
   return 1;
}

// ----------------------------------------------------------------------------
} // namespace pcl

// ----------------------------------------------------------------------------
// EOF CometAlignmentParameters.cpp - Released 2021-04-09T19:41:49Z
