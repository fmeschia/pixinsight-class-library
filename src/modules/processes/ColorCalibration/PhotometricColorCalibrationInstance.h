//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard ColorCalibration Process Module Version 1.5.1
// ----------------------------------------------------------------------------
// PhotometricColorCalibrationInstance.h - Released 2021-04-09T19:41:48Z
// ----------------------------------------------------------------------------
// This file is part of the standard ColorCalibration PixInsight module.
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

#ifndef __PhotometricColorCalibrationInstance_h
#define __PhotometricColorCalibrationInstance_h

#include <pcl/MetaParameter.h>
#include <pcl/ProcessImplementation.h>

namespace pcl
{

// ----------------------------------------------------------------------------

class PhotometricColorCalibrationInstance : public ProcessImplementation
{
public:

   PhotometricColorCalibrationInstance( const MetaProcess* );
   PhotometricColorCalibrationInstance( const PhotometricColorCalibrationInstance& );

   void Assign( const ProcessImplementation& ) override;
   UndoFlags UndoMode( const View& ) const override;
   bool CanExecuteOn( const View&, pcl::String& whyNot ) const override;
   bool ExecuteOn( View& ) override;
   void* LockParameter( const MetaParameter*, size_type tableRow ) override;
   bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow ) override;
   size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const override;

private:

   /*
    * Working modes.
    */
   pcl_enum p_workingMode; // RGB / narrowband
   pcl_bool p_applyCalibration;

   /*
    * Filter parameters (narrowband mode).
    */
   float    p_redFilterWavelength;
   float    p_redFilterBandwidth;
   float    p_greenFilterWavelength;
   float    p_greenFilterBandwidth;
   float    p_blueFilterWavelength;
   float    p_blueFilterBandwidth;

   /*
    * White reference parameters (broadband mode).
    */
   String   p_whiteReferenceId;
   String   p_whiteReferenceName; // informative
   float    p_whiteReferenceSr_JV;
   float    p_whiteReferenceJB_JV;
   float    p_zeroPointSr_JV;
   float    p_zeroPointJB_JV;

   /*
    * Plate solving parameters.
    */
   float    p_focalLength; // mm
   float    p_pixelSize;   // um
   double   p_centerRA;    // deg
   double   p_centerDec;   // deg
   double   p_epochJD;
   pcl_bool p_forcePlateSolve;
   pcl_bool p_ignorePositionAndScale;
   String   p_serverURL;
   String   p_solverCatalogName;
   pcl_bool p_solverAutoCatalog;
   int32    p_solverLimitMagnitude;
   pcl_bool p_solverAutoLimitMagnitude;
   float    p_solverAutoLimitMagnitudeFactor;
   float    p_solverStarSensitivity;
   int32    p_solverNoiseLayers;
   pcl_enum p_solverAlignmentDevice;
   pcl_bool p_solverDistortionCorrection;
   float    p_solverSplineSmoothing;
   pcl_enum p_solverProjection;

   /*
    * Photometry parameters.
    */
   String   p_photCatalogName;
   pcl_bool p_photAutoCatalog;
   int32    p_photLimitMagnitude;
   pcl_bool p_photAutoLimitMagnitude;
   float    p_photAutoLimitMagnitudeFactor;
   pcl_bool p_photAutoAperture;
   int32    p_photAperture;
   pcl_bool p_photUsePSF;
   float    p_photSaturationThreshold;
   pcl_bool p_photShowDetectedStars;
   pcl_bool p_photShowBackgroundModels;
   pcl_bool p_photGenerateGraphs;

   /*
    * Background neutralization parameters.
    */
   pcl_bool p_neutralizeBackground;
   String   p_backgroundReferenceViewId; // if empty, use $T
   float    p_backgroundLow;
   float    p_backgroundHigh;
   pcl_bool p_backgroundUseROI; // use a region of interest; entire image otherwise
   Rect     p_backgroundROI = 0;

   friend class PhotometricColorCalibrationInterface;
   friend class PhotometricColorCalibrationProcess;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __PhotometricColorCalibrationInstance_h

// ----------------------------------------------------------------------------
// EOF PhotometricColorCalibrationInstance.h - Released 2021-04-09T19:41:48Z
