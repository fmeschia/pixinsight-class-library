//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.6.11
// ----------------------------------------------------------------------------
// Standard Debayer Process Module Version 1.12.0
// ----------------------------------------------------------------------------
// DebayerModule.cpp - Released 2024-05-07T15:28:01Z
// ----------------------------------------------------------------------------
// This file is part of the standard Debayer PixInsight module.
//
// Copyright (c) 2003-2024 Pleiades Astrophoto S.L. All Rights Reserved.
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

#define MODULE_VERSION_MAJOR     1
#define MODULE_VERSION_MINOR     12
#define MODULE_VERSION_REVISION  0
#define MODULE_VERSION_BUILD     0
#define MODULE_VERSION_LANGUAGE  eng

#define MODULE_RELEASE_YEAR      2024
#define MODULE_RELEASE_MONTH     5
#define MODULE_RELEASE_DAY       7

#include "DebayerModule.h"
#include "DebayerProcess.h"
#include "DebayerInterface.h"

namespace pcl
{

// ----------------------------------------------------------------------------

DebayerModule::DebayerModule()
{
}

// ----------------------------------------------------------------------------

const char* DebayerModule::Version() const
{
   return PCL_MODULE_VERSION( MODULE_VERSION_MAJOR,
                              MODULE_VERSION_MINOR,
                              MODULE_VERSION_REVISION,
                              MODULE_VERSION_BUILD,
                              MODULE_VERSION_LANGUAGE );
}

// ----------------------------------------------------------------------------

IsoString DebayerModule::Name() const
{
   return "Debayer";
}

// ----------------------------------------------------------------------------

String DebayerModule::Description() const
{
   return "PixInsight Debayer Module. In memory of Sander Pool.";
}

// ----------------------------------------------------------------------------

String DebayerModule::Company() const
{
   return "Tungsten Technologies / Pleiades Astrophoto";
}

// ----------------------------------------------------------------------------

String DebayerModule::Author() const
{
   return "Sander Pool / Zbynek Vrastil / Juan Conejero";
}

// ----------------------------------------------------------------------------

String DebayerModule::Copyright() const
{
   return "Copyright (c) Sander Pool, 2009 / (c) Zbynek Vrastil, 2011 / (c) Pleiades Astrophoto, 2009-2024";
}

// ----------------------------------------------------------------------------

String DebayerModule::TradeMarks() const
{
   return "PixInsight";
}

// ----------------------------------------------------------------------------

String DebayerModule::OriginalFileName() const
{
#ifdef __PCL_FREEBSD
   return "Debayer-pxm.so";
#endif
#ifdef __PCL_LINUX
   return "Debayer-pxm.so";
#endif
#ifdef __PCL_MACOSX
   return "Debayer-pxm.dylib";
#endif
#ifdef __PCL_WINDOWS
   return "Debayer-pxm.dll";
#endif
}

// ----------------------------------------------------------------------------

void DebayerModule::GetReleaseDate( int& year, int& month, int& day ) const
{
   year  = MODULE_RELEASE_YEAR;
   month = MODULE_RELEASE_MONTH;
   day   = MODULE_RELEASE_DAY;
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------

PCL_MODULE_EXPORT int InstallPixInsightModule( int mode )
{
   new pcl::DebayerModule;

   if ( mode == pcl::InstallMode::FullInstall )
   {
      new pcl::DebayerProcess;
      new pcl::DebayerInterface;
   }

   return 0;
}

// ----------------------------------------------------------------------------
// EOF DebayerModule.cpp - Released 2024-05-07T15:28:01Z
