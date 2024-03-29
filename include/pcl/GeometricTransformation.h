//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// pcl/GeometricTransformation.h - Released 2021-04-09T19:40:59Z
// ----------------------------------------------------------------------------
// This file is part of the PixInsight Class Library (PCL).
// PCL is a multiplatform C++ framework for development of PixInsight modules.
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

#ifndef __PCL_GeometricTransformation_h
#define __PCL_GeometricTransformation_h

/// \file pcl/GeometricTransformation.h

#include <pcl/Defs.h>
#include <pcl/Diagnostics.h>

#include <pcl/ImageTransformation.h>
#include <pcl/PixelInterpolation.h>

namespace pcl
{

// ----------------------------------------------------------------------------

/*!
 * \class GeometricTransformation
 * \brief Abstract base class of all PCL geometric image transformations.
 *
 * %GeometricTransformation represents a geometrical transformation that can be
 * applied to any image type defined in PCL.
 *
 * \sa InterpolatingGeometricTransformation, ImageTransformation
 */
class PCL_CLASS GeometricTransformation : public virtual ImageTransformation
{
public:

   /*!
    * Constructs a %GeometricTransformation object.
    */
   GeometricTransformation() = default;

   /*!
    * Copy constructor.
    */
   GeometricTransformation( const GeometricTransformation& ) = default;

   /*!
    * Destroys a %GeometricTransformation object.
    */
   virtual ~GeometricTransformation()
   {
   }

   /*!
    * Predicts transformed image dimensions.
    *
    * \param[in,out] width  Reference to a variable whose value is a horizontal
    *             dimension in pixels (width). On output, it will receive the
    *             predicted horizontal dimension after the transformation.
    *
    * \param[in,out] height Reference to a variable whose value is a vertical
    *             dimension in pixels (height). On output, it will receive the
    *             predicted vertical dimension after the transformation.
    *
    * \note This is a pure virtual member function that must be reimplemented
    * in every derived class.
    */
   virtual void GetNewSizes( int& width, int& height ) const = 0;
};

// ----------------------------------------------------------------------------

/*!
 * \class InterpolatingGeometricTransformation
 * \brief Abstract base class of all PCL interpolating geometric image
 *        transformations.
 *
 * %InterpolatingGeometricTransformation represents a geometrical
 * transformation that uses a pixel interpolating algorithm to yield
 * transformed pixel sample values. Transformations implemented as derived
 * classes of %InterpolatingGeometricTransformation can be applied to all
 * standard image types defined in PCL.
 *
 * \sa GeometricTransformation, PixelInterpolation, ImageTransformation
 */
class PCL_CLASS InterpolatingGeometricTransformation : public GeometricTransformation
{
public:

   /*!
    * Constructs a %InterpolatingGeometricTransformation object that will use
    * the specified pixel interpolation \a p.
    *
    * The specified PixelInterpolation object must remain valid and accessible
    * as long as this object exists, or until this object is associated with a
    * different pixel interpolation.
    */
   InterpolatingGeometricTransformation( PixelInterpolation& p )
      : m_interpolation( &p )
   {
      PCL_CHECK( m_interpolation != nullptr )
   }

   /*!
    * Copy constructor. The constructed object will use the same pixel
    * interpolation as the specified source object.
    *
    * The PixelInterpolation object used by both this object and the source
    * object must remain valid and accessible as long as at least one of both
    * objects is associated with it.
    */
   InterpolatingGeometricTransformation( const InterpolatingGeometricTransformation& ) = default;

   /*!
    * Move constructor.
    */
   InterpolatingGeometricTransformation( InterpolatingGeometricTransformation&& x )
      : GeometricTransformation( x )
      , m_interpolation( x.m_interpolation )
      , m_unclipped( x.m_unclipped )
   {
      x.m_interpolation = nullptr;
   }

   /*!
    * Copy assignment operator. Returns a reference to this object.
    *
    * After assignment, this object will use the same pixel interpolation as
    * the specified source object. The previously used pixel interpolation is
    * simply forgotten by this object, which will no longer depend on it.
    *
    * The PixelInterpolation object used by both this object and the source
    * object must remain valid and accessible as long as at least one of both
    * objects is associated with it.
    */
   InterpolatingGeometricTransformation& operator =( const InterpolatingGeometricTransformation& ) = default;

   /*!
    * Move assignment operator. Returns a reference to this object.
    */
   InterpolatingGeometricTransformation& operator =( InterpolatingGeometricTransformation&& x )
   {
      m_interpolation = x.m_interpolation;
      x.m_interpolation = nullptr;
      m_unclipped = x.m_unclipped;
      return *this;
   }

   /*!
    * Returns a reference to the unmodifiable PixelInterpolation object that
    * this transformation is currently using.
    */
   const PixelInterpolation& Interpolation() const
   {
      PCL_CHECK( m_interpolation != nullptr )
      return *m_interpolation;
   }

   /*!
    * Returns a reference to the PixelInterpolation object that this
    * transformation is currently using.
    */
   PixelInterpolation& Interpolation()
   {
      PCL_CHECK( m_interpolation != nullptr )
      return *m_interpolation;
   }

   /*!
    * Causes this transformation to use the specified pixel interpolation \a p.
    *
    * The new pixel interpolation will be used to generate transformed pixel
    * values after calling this function. The previously used pixel
    * interpolation is simply forgotten by this object, which will no longer
    * depend on it.
    *
    * The specified PixelInterpolation object must remain valid and accessible
    * as long as this object exists, or until this object is associated with a
    * different pixel interpolation.
    */
   void SetInterpolation( PixelInterpolation& p )
   {
      m_interpolation = &p;
      PCL_CHECK( m_interpolation != nullptr )
   }

   /*!
    * Returns true if this image transformation applies unclipped pixel
    * interpolations. Unclipped interpolations don't constrain interpolated
    * pixel sample values to the native range of the pixel data type of the
    * transformed image. This allows to apply interpolating transformations to
    * images that exceed their representable ranges; for example, when images
    * are used to store and manipulate arbitrary matrices for convenience.
    *
    * Unclipped transformations are always disabled by default.
    */
   bool UsingUnclippedInterpolation() const
   {
      return m_unclipped;
   }

   /*!
    * Enables the use of unclipped pixel interpolations. See
    * UsingUnclippedInterpolation() for more information.
    */
   void EnableUnclippedInterpolation( bool enable = true )
   {
      m_unclipped = enable;
   }

   /*!
    * Disables the use of unclipped pixel interpolations. See
    * UsingUnclippedInterpolation() for more information.
    */
   void DisableUnclippedInterpolation( bool disable = true )
   {
      EnableUnclippedInterpolation( !disable );
   }

protected:

   PixelInterpolation* m_interpolation = nullptr;
   bool                m_unclipped = false;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __PCL_GeometricTransformation_h

// ----------------------------------------------------------------------------
// EOF pcl/GeometricTransformation.h - Released 2021-04-09T19:40:59Z
