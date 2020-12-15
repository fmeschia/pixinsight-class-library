//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.7
// ----------------------------------------------------------------------------
// Standard Fourier Process Module Version 1.0.4
// ----------------------------------------------------------------------------
// FourierTransformProcess.cpp - Released 2020-12-15T18:51:35Z
// ----------------------------------------------------------------------------
// This file is part of the standard Fourier PixInsight module.
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

#include "FourierTransformProcess.h"
#include "FourierTransformParameters.h"
#include "FourierTransformInstance.h"
#include "FourierTransformInterface.h"

namespace pcl
{

// ----------------------------------------------------------------------------

FourierTransformProcess* TheFourierTransformProcess = nullptr;

// ----------------------------------------------------------------------------

FourierTransformProcess::FourierTransformProcess()
{
   TheFourierTransformProcess = this;

   new FTRadialCoordinates( this );
   new FTCentered( this );
}

// ----------------------------------------------------------------------------

IsoString FourierTransformProcess::Id() const
{
   return "FourierTransform";
}

// ----------------------------------------------------------------------------

IsoString FourierTransformProcess::Category() const
{
   return "Fourier";
}

// ----------------------------------------------------------------------------

uint32 FourierTransformProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String FourierTransformProcess::Description() const
{
   return

   "<html>"
   "<p>FourierTransform is a simple tool to compute the Fourier transform of an image. "
   "It can provide the components of the Fourier transform directly as complex "
   "numbers, or as the magnitude and phase components of the power spectrum.</p>"
   "</html>";
}

// ----------------------------------------------------------------------------

String FourierTransformProcess::IconImageSVGFile() const
{
   return "@module_icons_dir/FourierTransform.svg";
}

// ----------------------------------------------------------------------------

ProcessInterface* FourierTransformProcess::DefaultInterface() const
{
   return TheFourierTransformInterface;
}

// ----------------------------------------------------------------------------

ProcessImplementation* FourierTransformProcess::Create() const
{
   return new FourierTransformInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* FourierTransformProcess::Clone( const ProcessImplementation& p ) const
{
   const FourierTransformInstance* instPtr = dynamic_cast<const FourierTransformInstance*>( &p );
   return (instPtr != nullptr) ? new FourierTransformInstance( *instPtr ) : nullptr;
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF FourierTransformProcess.cpp - Released 2020-12-15T18:51:35Z
