//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard ImageIntegration Process Module Version 1.2.33
// ----------------------------------------------------------------------------
// HDRCompositionProcess.cpp - Released 2021-04-09T19:41:48Z
// ----------------------------------------------------------------------------
// This file is part of the standard ImageIntegration PixInsight module.
//
// Copyright (c) 2003-2021 Pleiades Astrophoto S.L. All Rights Reserved.
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

#include "HDRCompositionInstance.h"
#include "HDRCompositionInterface.h"
#include "HDRCompositionParameters.h"
#include "HDRCompositionProcess.h"

namespace pcl
{

// ----------------------------------------------------------------------------

HDRCompositionProcess* TheHDRCompositionProcess = nullptr;

// ----------------------------------------------------------------------------

HDRCompositionProcess::HDRCompositionProcess()
{
   TheHDRCompositionProcess = this;

   new HCImages( this );
   new HCImageEnabled( TheHCImagesParameter );
   new HCImagePath( TheHCImagesParameter );
   new HCInputHints( this );
   new HCMaskBinarizingThreshold( this );
   new HCMaskSmoothness( this );
   new HCMaskGrowth( this );
   new HCReplaceLargeScales( this );
   new HCAutoExposures( this );
   new HCRejectBlack( this );
   new HCUseFittingRegion( this );
   new HCFittingRectX0( this );
   new HCFittingRectY0( this );
   new HCFittingRectX1( this );
   new HCFittingRectY1( this );
   new HCGenerate64BitResult( this );
   new HCOutputMasks( this );
   new HCClosePreviousImages( this );
}

// ----------------------------------------------------------------------------

IsoString HDRCompositionProcess::Id() const
{
   return "HDRComposition";
}

// ----------------------------------------------------------------------------

IsoString HDRCompositionProcess::Category() const
{
   return "ImageIntegration";
}

// ----------------------------------------------------------------------------

uint32 HDRCompositionProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String HDRCompositionProcess::Description() const
{
   return "";
}

// ----------------------------------------------------------------------------

String HDRCompositionProcess::IconImageSVGFile() const
{
   return "@module_icons_dir/HDRComposition.svg";
}

// ----------------------------------------------------------------------------

ProcessInterface* HDRCompositionProcess::DefaultInterface() const
{
   return TheHDRCompositionInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* HDRCompositionProcess::Create() const
{
   return new HDRCompositionInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* HDRCompositionProcess::Clone( const ProcessImplementation& p ) const
{
   const HDRCompositionInstance* instPtr = dynamic_cast<const HDRCompositionInstance*>( &p );
   return (instPtr != nullptr) ? new HDRCompositionInstance( *instPtr ) : nullptr;
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF HDRCompositionProcess.cpp - Released 2021-04-09T19:41:48Z
