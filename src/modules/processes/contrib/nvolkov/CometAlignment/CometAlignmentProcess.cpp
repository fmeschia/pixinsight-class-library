//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard CometAlignment Process Module Version 1.2.6
// ----------------------------------------------------------------------------
// CometAlignmentProcess.cpp - Released 2021-04-09T19:41:49Z
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

#include "CometAlignmentInstance.h"
#include "CometAlignmentInterface.h"
#include "CometAlignmentParameters.h"
#include "CometAlignmentProcess.h"

namespace pcl
{

// ----------------------------------------------------------------------------

CometAlignmentProcess* TheCometAlignmentProcess = nullptr;

// ----------------------------------------------------------------------------

CometAlignmentProcess::CometAlignmentProcess()
{
   TheCometAlignmentProcess = this;

   new CATargetFrames( this );
   new CATargetFrameEnabled( TheTargetFrames );
   new CATargetFramePath( TheTargetFrames );
   new CATargetFrameDate( TheTargetFrames );
   new CATargetFrameJDate( TheTargetFrames );
   new CATargetFrameX( TheTargetFrames );
   new CATargetFrameY( TheTargetFrames );
   new CADrizzlePath( TheTargetFrames );
   new CAInputHints( this );
   new CAOutputHints( this );
   new CAOutputDir( this );
   new CAOutputExtension( this );
   new CAPrefix( this );
   new CAPostfix( this );
   new CAOverwrite( this );
   new CAReference( this );
   new CASubtractFile( this );
   new CASubtractMode( this );
   new CAEnableLinearFit( this );
   new CARejectLow( this );
   new CARejectHigh( this );
   new CANormalize( this );
   new CADrzSaveSA( this );
   new CADrzSaveCA( this );
   new CAOperandIsDI( this );
   new CAPixelInterpolation( this );
   new CALinearClampingThreshold( this );
}

// ----------------------------------------------------------------------------

IsoString CometAlignmentProcess::Id() const
{
   return "CometAlignment";
}

// ----------------------------------------------------------------------------

IsoString CometAlignmentProcess::Category() const
{
   return "ImageRegistration";
}

// ----------------------------------------------------------------------------

uint32 CometAlignmentProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String CometAlignmentProcess::Description() const
{
   return "";
}

// ----------------------------------------------------------------------------

String CometAlignmentProcess::IconImageSVGFile() const
{
   return "@module_icons_dir/CometAlignment.svg";
}

// ----------------------------------------------------------------------------

ProcessInterface* CometAlignmentProcess::DefaultInterface() const
{
   return TheCometAlignmentInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* CometAlignmentProcess::Create() const
{
   return new CometAlignmentInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* CometAlignmentProcess::Clone( const ProcessImplementation& p ) const
{
   const CometAlignmentInstance* instPtr = dynamic_cast<const CometAlignmentInstance*>( &p );
   return (instPtr != nullptr) ? new CometAlignmentInstance( *instPtr ) : nullptr;
}

// ----------------------------------------------------------------------------

} // namespace pcl

// ----------------------------------------------------------------------------
// EOF CometAlignmentProcess.cpp - Released 2021-04-09T19:41:49Z
