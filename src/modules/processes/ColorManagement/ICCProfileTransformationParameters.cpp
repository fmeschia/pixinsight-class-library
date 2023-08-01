//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.5.7
// ----------------------------------------------------------------------------
// Standard ColorManagement Process Module Version 1.0.1
// ----------------------------------------------------------------------------
// ICCProfileTransformationParameters.cpp - Released 2023-08-01T16:30:17Z
// ----------------------------------------------------------------------------
// This file is part of the standard ColorManagement PixInsight module.
//
// Copyright (c) 2003-2023 Pleiades Astrophoto S.L. All Rights Reserved.
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

#include "ICCProfileTransformationParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

ICCTTargetProfile*                  TheICCTTargetProfileParameter = nullptr;
ICCTToDefaultProfile*               TheICCTToDefaultProfileParameter = nullptr;
ICCTRenderingIntent*                TheICCTRenderingIntentParameter = nullptr;
ICCTUseBlackPointCompensation*      TheICCTUseBlackPointCompensationParameter = nullptr;
ICCTUseFloatingPointTransformation* TheICCTUseFloatingPointTransformationParameter = nullptr;

// ----------------------------------------------------------------------------

ICCTTargetProfile::ICCTTargetProfile( MetaProcess* P ) : MetaString( P )
{
   TheICCTTargetProfileParameter = this;
}

IsoString ICCTTargetProfile::Id() const
{
   return "targetProfile";
}

// ----------------------------------------------------------------------------

ICCTToDefaultProfile::ICCTToDefaultProfile( MetaProcess* P ) : MetaBoolean( P )
{
   TheICCTToDefaultProfileParameter = this;
}

IsoString ICCTToDefaultProfile::Id() const
{
   return "toDefaultProfile";
}

bool ICCTToDefaultProfile::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

ICCTRenderingIntent::ICCTRenderingIntent( MetaProcess* P ) : MetaEnumeration( P )
{
   TheICCTRenderingIntentParameter = this;
}

IsoString ICCTRenderingIntent::Id() const
{
   return "renderingIntent";
}

size_type ICCTRenderingIntent::NumberOfElements() const
{
   return NumberOfRenderingIntents;
}

IsoString ICCTRenderingIntent::ElementId( size_type i ) const
{
   switch ( i )
   {
   default:
   case Perceptual:           return "Perceptual";
   case Saturation:           return "Saturation";
   case RelativeColorimetric: return "RelativeColorimetric";
   case AbsoluteColorimetric: return "AbsoluteColorimetric";
   }
}

int ICCTRenderingIntent::ElementValue( size_type i ) const
{
   return int( i );
}

size_type ICCTRenderingIntent::DefaultValueIndex() const
{
   return Default;
}

// ----------------------------------------------------------------------------

ICCTUseBlackPointCompensation::ICCTUseBlackPointCompensation( MetaProcess* P ) : MetaBoolean( P )
{
   TheICCTUseBlackPointCompensationParameter = this;
}

IsoString ICCTUseBlackPointCompensation::Id() const
{
   return "useBlackPointCompensation";
}

bool ICCTUseBlackPointCompensation::DefaultValue() const
{
   return false;
}

// ----------------------------------------------------------------------------

ICCTUseFloatingPointTransformation::ICCTUseFloatingPointTransformation( MetaProcess* P ) : MetaBoolean( P )
{
   TheICCTUseFloatingPointTransformationParameter = this;
}

IsoString ICCTUseFloatingPointTransformation::Id() const
{
   return "useFloatingPointTransformation";
}

bool ICCTUseFloatingPointTransformation::DefaultValue() const
{
   return true;
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF ICCProfileTransformationParameters.cpp - Released 2023-08-01T16:30:17Z
