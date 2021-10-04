//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.11
// ----------------------------------------------------------------------------
// Standard TIFF File Format Module Version 1.0.8
// ----------------------------------------------------------------------------
// TIFFRangeOptionsDialog.h - Released 2021-10-04T16:20:05Z
// ----------------------------------------------------------------------------
// This file is part of the standard TIFF PixInsight module.
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

#ifndef __TIFFRangeOptionsDialog_h
#define __TIFFRangeOptionsDialog_h

#include "TIFFOptionsDialog.h"
#include "TIFFFormat.h"

#include <pcl/Dialog.h>
#include <pcl/Sizer.h>
#include <pcl/GroupBox.h>
#include <pcl/PushButton.h>
#include <pcl/CheckBox.h>
#include <pcl/NumericControl.h>
#include <pcl/ComboBox.h>

namespace pcl
{

// ----------------------------------------------------------------------------

class TIFFRangeOptionsDialog : public Dialog
{
public:

   TIFFRangeOptionsDialog( const TIFFFormat::OutOfRangePolicyOptions&,
                           int bitsPerSample, double minSampleValue, double maxSampleValue );

   TIFFFormat::OutOfRangePolicyOptions outOfRange;

private:

   VerticalSizer           Global_Sizer;

   Label                   Info_Label;
   GroupBox                ReadRange_GroupBox;
   VerticalSizer           ReadRange_Sizer;
      NumericEdit             LowerRange_NumericEdit;
      NumericEdit             UpperRange_NumericEdit;
      HorizontalSizer         ReadRescaleMode_Sizer;
         Label                   ReadRescaleMode_Label;
         ComboBox                ReadRescaleMode_ComboBox;
   HorizontalSizer         BottomSection_Sizer;
      PushButton              OK_PushButton;
      PushButton              Cancel_PushButton;

   void Button_Click( Button& sender, bool checked );
   void Dialog_Return( Dialog& sender, int retVal );
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __TIFFRangeOptionsDialog_h

// ----------------------------------------------------------------------------
// EOF TIFFRangeOptionsDialog.h - Released 2021-10-04T16:20:05Z
