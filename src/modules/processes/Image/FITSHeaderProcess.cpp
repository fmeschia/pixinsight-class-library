//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.35
// ----------------------------------------------------------------------------
// Standard Image Process Module Version 1.3.2
// ----------------------------------------------------------------------------
// FITSHeaderProcess.cpp - Released 2022-11-21T14:47:17Z
// ----------------------------------------------------------------------------
// This file is part of the standard Image PixInsight module.
//
// Copyright (c) 2003-2022 Pleiades Astrophoto S.L. All Rights Reserved.
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

#include "FITSHeaderProcess.h"
#include "FITSHeaderParameters.h"
#include "FITSHeaderInstance.h"
#include "FITSHeaderInterface.h"

#include <pcl/Arguments.h>
#include <pcl/ImageWindow.h>
#include <pcl/View.h>
#include <pcl/Console.h>

namespace pcl
{

// ----------------------------------------------------------------------------

FITSHeaderProcess* TheFITSHeaderProcess = nullptr;

// ----------------------------------------------------------------------------

FITSHeaderProcess::FITSHeaderProcess()
{
   TheFITSHeaderProcess = this;

   new FITSKeywordTable( this );
   new FITSKeywordName( TheFITSKeywordTableParameter );
   new FITSKeywordValue( TheFITSKeywordTableParameter );
   new FITSKeywordComment( TheFITSKeywordTableParameter );
}

// ----------------------------------------------------------------------------

IsoString FITSHeaderProcess::Id() const
{
   return "FITSHeader";
}

// ----------------------------------------------------------------------------

IsoString FITSHeaderProcess::Category() const
{
   return "Image";
}

// ----------------------------------------------------------------------------

uint32 FITSHeaderProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String FITSHeaderProcess::Description() const
{
   return

   "<html>"
   "<p>The FITSHeader process allows you to browse and edit FITS header keywords.</p>"
   "</html>";
}

// ----------------------------------------------------------------------------

String FITSHeaderProcess::IconImageSVGFile() const
{
   return "@module_icons_dir/FITSHeader.svg";
}

// ----------------------------------------------------------------------------

ProcessInterface* FITSHeaderProcess::DefaultInterface() const
{
   return TheFITSHeaderInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* FITSHeaderProcess::Create() const
{
   return new FITSHeaderInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* FITSHeaderProcess::Clone( const ProcessImplementation& p ) const
{
   const FITSHeaderInstance* instPtr = dynamic_cast<const FITSHeaderInstance*>( &p );
   return (instPtr != nullptr) ? new FITSHeaderInstance( *instPtr ) : nullptr;
}

// ----------------------------------------------------------------------------

bool FITSHeaderProcess::CanProcessCommandLines() const
{
   return true;
}

// ----------------------------------------------------------------------------

static void ShowHelp()
{
   Console().Write(
"<raw>"
"Usage: FITSHeader [<arg_list>] [<view_list>]"
"\n"
"\n--interface"
"\n"
"\n      Launches the interface of this process."
"\n"
"\n--help"
"\n"
"\n      Displays this help and exits."
"</raw>" );
}

int FITSHeaderProcess::ProcessCommandLine( const StringList& argv ) const
{
   ArgumentList arguments =
   ExtractArguments( argv, ArgumentItemMode::AsViews,
                     ArgumentOption::AllowWildcards|ArgumentOption::NoPreviews );

   FITSHeaderInstance instance( this );

   bool launchInterface = false;
   int count = 0;

   for ( ArgumentList::const_iterator i = arguments.Begin(); i != arguments.End(); ++i )
   {
      const Argument& arg = *i;

      if ( arg.IsNumeric() )
         throw Error( "Unknown numeric argument: " + arg.Token() );
      else if ( arg.IsString() )
         throw Error( "Unknown string argument: " + arg.Token() );
      else if ( arg.IsSwitch() )
         throw Error( "Unknown switch argument: " + arg.Token() );
      else if ( arg.IsLiteral() )
         throw Error( "Unknown argument: " + arg.Token() );
      else if ( arg.IsItemList() )
      {
         ++count;

         if ( arg.Items().IsEmpty() )
         {
            Console().WriteLn( "No view(s) found: " + arg.Token() );
            continue;
         }

         for ( StringList::const_iterator j = arg.Items().Begin(); j != arg.Items().End(); ++j )
         {
            View v = View::ViewById( *j );
            if ( v.IsNull() )
               throw Error( "No such view: " + *j );
            instance.LaunchOn( v );
         }
      }
   }

   if ( launchInterface )
      instance.LaunchInterface();
   else if ( count == 0 )
   {
      if ( ImageWindow::ActiveWindow().IsNull() )
         throw Error( "There is no active image window." );
      instance.LaunchOnCurrentWindow();
   }

   return 0;
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF FITSHeaderProcess.cpp - Released 2022-11-21T14:47:17Z
