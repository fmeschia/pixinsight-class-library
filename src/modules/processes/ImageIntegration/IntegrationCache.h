//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// Standard ImageIntegration Process Module Version 1.2.33
// ----------------------------------------------------------------------------
// IntegrationCache.h - Released 2021-04-09T19:41:48Z
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

#ifndef __IntegrationCache_h
#define __IntegrationCache_h

#include <pcl/FileDataCache.h>

#include "IntegrationFile.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class IntegrationCacheItem : public FileDataCacheItem
{
public:

   typedef IntegrationFile::scale_estimates  scale_estimates;

   DVector         mean;        // mean pixel values
   DVector         median;      // location estimates
   scale_estimates avgDev;      // two-sided AvgDev scale estimates
   scale_estimates mad;         // two-sided MAD scale estimates
   scale_estimates bwmv;        // two-sided BWMV scale estimates
   DVector         noise;       // noise stdDev estimates
   DVector         ax;          // adaptive normalization: sample X-coordinates
   DVector         ay;          // adaptive normalization: sample Y-coordinates
   DMultiVector    am;          // adaptive normalization: location estimates
   DMultiVector    as0_avgDev;  // adaptive normalization: low scale estimates (AvgDev)
   DMultiVector    as1_avgDev;  // adaptive normalization: high scale estimates (AvgDev)
   DMultiVector    as0_mad;     // adaptive normalization: low scale estimates (MAD)
   DMultiVector    as1_mad;     // adaptive normalization: high scale estimates (MAD)
   DMultiVector    as0_bwmv;    // adaptive normalization: low scale estimates (BWMV)
   DMultiVector    as1_bwmv;    // adaptive normalization: high scale estimates (BWMV)
   String          metadata;    // image metadata

   IntegrationCacheItem( const String& path = String() )
      : FileDataCacheItem( path )
   {
   }

   virtual ~IntegrationCacheItem()
   {
   }

private:

   void AssignData( const FileDataCacheItem& item ) override;
   String DataToString() const override;
   bool GetDataFromTokens( const StringList& tokens ) override;
};

// ----------------------------------------------------------------------------

class IntegrationCache : public FileDataCache
{
public:

   IntegrationCache();
   virtual ~IntegrationCache();

   String CacheName() const override
   {
      return "ImageIntegration Cache";
   }

   int Version() const override
   {
      return 2;
   }

   int MinSupportedVersion() const override
   {
      return 2;
   }

private:

   FileDataCacheItem* NewItem() const override
   {
      return new IntegrationCacheItem;
   }
};

extern IntegrationCache* TheIntegrationCache;

// ----------------------------------------------------------------------------

} // pcl

#endif   // __IntegrationCache_h

// ----------------------------------------------------------------------------
// EOF IntegrationCache.h - Released 2021-04-09T19:41:48Z
