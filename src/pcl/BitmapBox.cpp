//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.12.0947
// ----------------------------------------------------------------------------
// pcl/BitmapBox.cpp - Released 2019-04-30T16:30:49Z
// ----------------------------------------------------------------------------
// This file is part of the PixInsight Class Library (PCL).
// PCL is a multiplatform C++ framework for development of PixInsight modules.
//
// Copyright (c) 2003-2019 Pleiades Astrophoto S.L. All Rights Reserved.
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

#include <pcl/BitmapBox.h>

#include <pcl/api/APIInterface.h>
#include <pcl/api/APIException.h>

namespace pcl
{

// ----------------------------------------------------------------------------

BitmapBox::BitmapBox( const Bitmap& bm, Control& parent ) :
   Frame( (*API->BitmapBox->CreateBitmapBox)( ModuleHandle(), this, bm.handle, parent.handle, 0/*flags*/ ) )
{
   if ( handle == 0 )
      throw APIFunctionError( "CreateBitmapBox" );
}

// ----------------------------------------------------------------------------

Bitmap BitmapBox::CurrentBitmap() const
{
   return Bitmap( (*API->BitmapBox->GetBitmapBoxBitmap)( handle ) );
}

// ----------------------------------------------------------------------------

void BitmapBox::SetBitmap( const Bitmap& pm )
{
   (*API->BitmapBox->SetBitmapBoxBitmap)( handle, pm.handle );
}

// ----------------------------------------------------------------------------

int BitmapBox::Margin() const
{
   return (*API->BitmapBox->GetBitmapBoxMargin)( handle );
}

// ----------------------------------------------------------------------------

void BitmapBox::SetMargin( int px )
{
   (*API->BitmapBox->SetBitmapBoxMargin)( handle, px );
}

// ----------------------------------------------------------------------------

bool BitmapBox::IsAutoFitEnabled() const
{
   return (*API->BitmapBox->GetBitmapBoxAutoFitEnabled)( handle ) != api_false;
}

// ----------------------------------------------------------------------------

void BitmapBox::EnableAutoFit( bool enable )
{
   (*API->BitmapBox->SetBitmapBoxAutoFitEnabled)( handle, enable );
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// EOF pcl/BitmapBox.cpp - Released 2019-04-30T16:30:49Z
