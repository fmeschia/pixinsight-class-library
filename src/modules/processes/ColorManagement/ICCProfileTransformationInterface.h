//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.5.7
// ----------------------------------------------------------------------------
// Standard ColorManagement Process Module Version 1.0.1
// ----------------------------------------------------------------------------
// ICCProfileTransformationInterface.h - Released 2023-08-10T11:44:14Z
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

#ifndef __ICCProfileTransformationInterface_h
#define __ICCProfileTransformationInterface_h

#include <pcl/CheckBox.h>
#include <pcl/ComboBox.h>
#include <pcl/Edit.h>
#include <pcl/GroupBox.h>
#include <pcl/ICCProfile.h>
#include <pcl/Label.h>
#include <pcl/ProcessInterface.h>
#include <pcl/PushButton.h>
#include <pcl/RadioButton.h>
#include <pcl/Sizer.h>
#include <pcl/ToolButton.h>
#include <pcl/ViewList.h>

#include "ICCProfileTransformationInstance.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class ICCProfileTransformationInterface : public ProcessInterface
{
public:

   ICCProfileTransformationInterface();
   virtual ~ICCProfileTransformationInterface();

   IsoString Id() const override;
   MetaProcess* Process() const override;
   String IconImageSVGFile() const override;
   InterfaceFeatures Features() const override;
   void ApplyInstance() const override;
   void TrackViewUpdated( bool active ) override;
   void ResetInstance() override;
   bool Launch( const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ ) override;
   ProcessImplementation* NewProcess() const override;
   bool ValidateProcess( const ProcessImplementation&, pcl::String& whyNot ) const override;
   bool RequiresInstanceValidation() const override;
   bool ImportProcess( const ProcessImplementation& ) override;
   bool WantsImageNotifications() const override;
   void ImageUpdated( const View& ) override;
   void ImageFocused( const View& ) override;
   void ImageCMUpdated( const View& ) override;
   bool WantsGlobalNotifications() const override;
   void GlobalCMUpdated() override;

private:

   ICCProfileTransformationInstance m_instance;
   ICCProfile::profile_list         m_profiles;
   String                           m_defaultRGBProfile;
   String                           m_defaultGrayscaleProfile;

   struct GUIData
   {
      GUIData( ICCProfileTransformationInterface& );

      VerticalSizer     Global_Sizer;

      GroupBox          SourceProfile_GroupBox;
      VerticalSizer     SourceProfile_Sizer;
         ViewList          AllImages_ViewList;
         Edit              SourceProfile_Edit;

      GroupBox          TargetProfile_GroupBox;
      VerticalSizer     TargetProfile_Sizer;
         RadioButton       ToProfile_RadioButton;
         Edit              TargetProfile_Edit;
         HorizontalSizer   AllProfiles_Sizer;
            ComboBox          AllProfiles_ComboBox;
            ToolButton        RefreshProfiles_ToolButton;
         RadioButton       ToDefaultProfile_RadioButton;
         HorizontalSizer   DefaultRGBProfile_Sizer;
            Label             DefaultRGBProfile_Label;
            Edit              DefaultRGBProfile_Edit;
         HorizontalSizer   DefaultGrayscaleProfile_Sizer;
            Label             DefaultGrayscaleProfile_Label;
            Edit              DefaultGrayscaleProfile_Edit;

      GroupBox          RenderingIntent_GroupBox;
      VerticalSizer     RenderingIntent_Sizer;
         ComboBox          RenderingIntent_ComboBox;

      GroupBox          Options_GroupBox;
      HorizontalSizer   Options_Sizer;
         CheckBox          UseBlackPointCompensation_CheckBox;
         CheckBox          UseFloatingPointTransformation_CheckBox;
   };

   GUIData* GUI = nullptr;

   void UpdateControls();

   void RefreshProfiles();
   void RefreshDefaultProfiles();

   void __ViewList_ViewSelected( ViewList& sender, View& view );
   void __TargetProfile_EditCompleted( Edit& );
   void __Profile_ItemSelected( ComboBox& sender, int itemIndex );
   void __RefreshProfiles_ButtonClick( Button& sender, bool checked );
   void __ToProfile_ButtonClick( Button& sender, bool checked );
   void __RenderingIntent_ItemSelected( ComboBox& sender, int itemIndex );
   void __Option_ButtonClick( Button& sender, bool checked );
   void __ViewDrag( Control& sender, const Point& pos, const View& view, unsigned modifiers, bool& wantsView );
   void __ViewDrop( Control& sender, const Point& pos, const View& view, unsigned modifiers );

   friend struct GUIData;
};

// ----------------------------------------------------------------------------

PCL_BEGIN_LOCAL
extern ICCProfileTransformationInterface* TheICCProfileTransformationInterface;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ICCProfileTransformationInterface_h

// ----------------------------------------------------------------------------
// EOF ICCProfileTransformationInterface.h - Released 2023-08-10T11:44:14Z
