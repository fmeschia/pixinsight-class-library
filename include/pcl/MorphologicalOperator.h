//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.9
// ----------------------------------------------------------------------------
// pcl/MorphologicalOperator.h - Released 2021-04-09T19:40:59Z
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

#ifndef __PCL_MorphologicalOperator_h
#define __PCL_MorphologicalOperator_h

/// \file pcl/MorphologicalOperator.h

#include <pcl/Defs.h>
#include <pcl/Diagnostics.h>

#include <pcl/Exception.h>
#include <pcl/Math.h>
#include <pcl/PixelTraits.h>
#include <pcl/Selection.h>
#include <pcl/Sort.h>
#include <pcl/String.h>
#include <pcl/Utility.h>

namespace pcl
{

// ----------------------------------------------------------------------------

/*!
 * \class MorphologicalOperator
 * \brief Abstract base class of all PCL morphological operators.
 *
 * \sa ErosionFilter, DilationFilter, MedianFilter, SelectionFilter,
 * MidpointFilter, AlphaTrimmedMeanFilter
 */
class PCL_CLASS MorphologicalOperator
{
public:

   /*!
    * Constructs a %MorphologicalOperator object.
    */
   MorphologicalOperator() = default;

   /*!
    * Copy constructor.
    */
   MorphologicalOperator( const MorphologicalOperator& ) = default;

   /*!
    * Destroys a %MorphologicalOperator object.
    */
   virtual ~MorphologicalOperator()
   {
   }

   /*!
    * Returns a pointer to a dynamically allocated duplicate of this
    * morphological operator.
    */
   virtual MorphologicalOperator* Clone() const = 0;

   /*!
    * Returns a human-readable description of this morphological operator.
    */
   virtual String Description() const
   {
      return String();
   }

   /*!
    * \internal
    * Returns true iff this object performs a dilation morphological operation.
    * This member function is used internally to decide whether to reflect the
    * structuring element during morphological transformations.
    */
   virtual bool IsDilation() const
   {
      return false;
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   virtual FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 32-bit floating-point images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   virtual DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 64-bit floating-point images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point complex pixel samples.
    */
   virtual ComplexPixelTraits::sample operator ()( ComplexPixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 32-bit complex images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point complex pixel samples.
    */
   virtual DComplexPixelTraits::sample operator ()( DComplexPixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 64-bit complex images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   virtual UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 8-bit integer images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   virtual UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 16-bit integer images" );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   virtual UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const
   {
      throw NotImplemented( *this, "Apply to 32-bit integer images" );
   }
};

// ----------------------------------------------------------------------------

/*!
 * \class ErosionFilter
 * \brief Erosion morphological operator.
 *
 * The \e erosion morphological operator computes the minimum value in a pixel
 * neighborhood.
 */
class PCL_CLASS ErosionFilter : public MorphologicalOperator
{
public:

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new ErosionFilter( *this );
   }

   /*!
    */
   String Description() const override
   {
      return "Erosion";
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

private:

   template <typename T>
   static T Operate( T* __restrict__ f, size_type n )
   {
      T x = *f++;
      for ( ; --n > 0; ++f )
         if ( *f < x )
            x = *f;
      return x;
   }
};

// ----------------------------------------------------------------------------

/*!
 * \class DilationFilter
 * \brief Dilation morphological operator.
 *
 * The \e dilation morphological operator computes the maximum value in a pixel
 * neighborhood.
 */
class PCL_CLASS DilationFilter : public MorphologicalOperator
{
public:

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new DilationFilter( *this );
   }

   /*!
    */
   String Description() const override
   {
      return "Dilation";
   }

   /*!
    */
   bool IsDilation() const override
   {
      return true;
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

private:

   template <typename T>
   static T Operate( T* __restrict__ f, size_type n )
   {
      T x = *f++;
      for ( ; --n > 0; ++f )
         if ( x < *f )
            x = *f;
      return x;
   }
};

// ----------------------------------------------------------------------------

/*!
 * \class MedianFilter
 * \brief Morphological median operator.
 *
 * The \e median morphological operator (or median order-statistic filter)
 * computes the median of the values in a pixel neighborhood.
 */
class PCL_CLASS MedianFilter : public MorphologicalOperator
{
public:

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new MedianFilter( *this );
   }

   /*!
    */
   String Description() const override
   {
      return "Median";
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (FloatPixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (DoublePixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt8PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt16PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt32PixelTraits*)0 );
   }

private:

#define CMPXCHG( a, b )  \
   if ( f[b] < f[a] ) pcl::Swap( f[a], f[b] )

#define MEAN( a, b ) \
   P::FloatToSample( (double( a ) + double( b ))/2 )

   template <typename T, class P>
   static T Operate( T* __restrict__ f, size_type n, P* )
   {
      /*
       * Use fast, hard-coded selection networks for n <= 24:
       *
       * Knuth, D. E., The Art of Computer Programming, volume 3: Sorting and
       * Searching, Addison Wesley, 1973.
       *
       * Hillis, W. D., Co-evolving parasites improve simulated evolution as an
       * optimization procedure.</em> Langton, C. et al. (Eds.), Artificial
       * Life II. Addison Wesley, 1992.
       *
       * Hugues Juille, Evolution of Non-Deterministic Incremental Algorithms
       * as a New Approach for Search in State Spaces, 1995.
       *
       * Use a quick selection algorithm for n > 24:
       *
       * William H. Press et al., Numerical Recipes 3rd Edition: The Art of
       * Scientific Computing, Cambridge University Press, 2007, Section 8.5.
       *
       * Robert Sedgewick, Kevin Wayne, Algorithms, 4th Edition, Addison-Wesley
       * Professional, 2011, pp 345-347.
       */
      switch ( n )
      {
      case  0: // ?!
         return 0;
      case  1: // !?
         return f[0];
      case  2:
         return MEAN( f[0], f[1] );
      case  3:
         CMPXCHG( 0, 1 ); CMPXCHG( 1, 2 );
         return pcl::Max( f[0], f[1] );
      case  4:
         CMPXCHG( 0, 1 ); CMPXCHG( 2, 3 ); CMPXCHG( 0, 2 );
         CMPXCHG( 1, 3 );
         return MEAN( f[1], f[2] );
      case  5:
         CMPXCHG( 0, 1 ); CMPXCHG( 3, 4 ); CMPXCHG( 0, 3 );
         CMPXCHG( 1, 4 ); CMPXCHG( 1, 2 ); CMPXCHG( 2, 3 );
         return pcl::Max( f[1], f[2] );
      case  6:
         CMPXCHG( 0, 1 ); CMPXCHG( 2, 3 ); CMPXCHG( 0, 2 );
         CMPXCHG( 1, 3 ); CMPXCHG( 1, 2 ); CMPXCHG( 4, 5 );
         CMPXCHG( 0, 4 ); CMPXCHG( 1, 5 ); CMPXCHG( 1, 4 );
         CMPXCHG( 2, 4 ); CMPXCHG( 3, 5 ); CMPXCHG( 3, 4 );
         return MEAN( f[2], f[3] );
      case  7:
         CMPXCHG( 0, 5 ); CMPXCHG( 0, 3 ); CMPXCHG( 1, 6 );
         CMPXCHG( 2, 4 ); CMPXCHG( 0, 1 ); CMPXCHG( 3, 5 );
         CMPXCHG( 2, 6 ); CMPXCHG( 2, 3 ); CMPXCHG( 3, 6 );
         CMPXCHG( 4, 5 ); CMPXCHG( 1, 4 ); CMPXCHG( 1, 3 );
         return pcl::Min( f[3], f[4] );
      case  8:
         CMPXCHG( 0, 4 ); CMPXCHG( 1, 5 ); CMPXCHG( 2, 6 );
         CMPXCHG( 3, 7 ); CMPXCHG( 0, 2 ); CMPXCHG( 1, 3 );
         CMPXCHG( 4, 6 ); CMPXCHG( 5, 7 ); CMPXCHG( 2, 4 );
         CMPXCHG( 3, 5 ); CMPXCHG( 0, 1 ); CMPXCHG( 2, 3 );
         CMPXCHG( 4, 5 ); CMPXCHG( 6, 7 ); CMPXCHG( 1, 4 );
         CMPXCHG( 3, 6 );
         return MEAN( f[3], f[4] );
      case  9:
         CMPXCHG( 1, 2 ); CMPXCHG( 4, 5 ); CMPXCHG( 7, 8 );
         CMPXCHG( 0, 1 ); CMPXCHG( 3, 4 ); CMPXCHG( 6, 7 );
         CMPXCHG( 1, 2 ); CMPXCHG( 4, 5 ); CMPXCHG( 7, 8 );
         CMPXCHG( 0, 3 ); CMPXCHG( 5, 8 ); CMPXCHG( 4, 7 );
         CMPXCHG( 3, 6 ); CMPXCHG( 1, 4 ); CMPXCHG( 2, 5 );
         CMPXCHG( 4, 7 ); CMPXCHG( 4, 2 ); CMPXCHG( 6, 4 );
         return pcl::Min( f[2], f[4] );
      case 10:
         CMPXCHG( 4, 9 ); CMPXCHG( 3, 8 ); CMPXCHG( 2, 7 );
         CMPXCHG( 1, 6 ); CMPXCHG( 0, 5 ); CMPXCHG( 1, 4 );
         CMPXCHG( 6, 9 ); CMPXCHG( 0, 3 ); CMPXCHG( 5, 8 );
         CMPXCHG( 0, 2 ); CMPXCHG( 3, 6 ); CMPXCHG( 7, 9 );
         CMPXCHG( 0, 1 ); CMPXCHG( 2, 4 ); CMPXCHG( 5, 7 );
         CMPXCHG( 8, 9 ); CMPXCHG( 1, 2 ); CMPXCHG( 4, 6 );
         CMPXCHG( 7, 8 ); CMPXCHG( 3, 5 ); CMPXCHG( 2, 5 );
         CMPXCHG( 6, 8 ); CMPXCHG( 1, 3 ); CMPXCHG( 4, 7 );
         CMPXCHG( 2, 3 ); CMPXCHG( 6, 7 ); CMPXCHG( 3, 4 );
         CMPXCHG( 5, 6 );
         return MEAN( f[4], f[5] );
      case 11:
         CMPXCHG( 0,  1 ); CMPXCHG( 2,  3 ); CMPXCHG( 4,  5 );
         CMPXCHG( 6,  7 ); CMPXCHG( 8,  9 ); CMPXCHG( 1,  3 );
         CMPXCHG( 5,  7 ); CMPXCHG( 0,  2 ); CMPXCHG( 4,  6 );
         CMPXCHG( 8, 10 ); CMPXCHG( 1,  2 ); CMPXCHG( 5,  6 );
         CMPXCHG( 9, 10 ); CMPXCHG( 1,  5 ); CMPXCHG( 6, 10 );
         CMPXCHG( 5,  9 ); CMPXCHG( 2,  6 ); CMPXCHG( 1,  5 );
         CMPXCHG( 6, 10 ); CMPXCHG( 0,  4 ); CMPXCHG( 3,  7 );
         CMPXCHG( 4,  8 ); CMPXCHG( 0,  4 ); CMPXCHG( 1,  4 );
         CMPXCHG( 7, 10 ); CMPXCHG( 3,  8 ); CMPXCHG( 2,  3 );
         CMPXCHG( 8,  9 ); CMPXCHG( 3,  5 ); CMPXCHG( 6,  8 );
         return pcl::Min( f[5], f[6] );
      case 12:
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG(  1,  3 ); CMPXCHG(  5,  7 ); CMPXCHG(  9, 11 );
         CMPXCHG(  0,  2 ); CMPXCHG(  4,  6 ); CMPXCHG(  8, 10 );
         CMPXCHG(  1,  2 ); CMPXCHG(  5,  6 ); CMPXCHG(  9, 10 );
         CMPXCHG(  1,  5 ); CMPXCHG(  6, 10 ); CMPXCHG(  5,  9 );
         CMPXCHG(  2,  6 ); CMPXCHG(  1,  5 ); CMPXCHG(  6, 10 );
         CMPXCHG(  0,  4 ); CMPXCHG(  7, 11 ); CMPXCHG(  3,  7 );
         CMPXCHG(  4,  8 ); CMPXCHG(  0,  4 ); CMPXCHG(  7, 11 );
         CMPXCHG(  1,  4 ); CMPXCHG(  7, 10 ); CMPXCHG(  3,  8 );
         CMPXCHG(  2,  3 ); CMPXCHG(  8,  9 ); CMPXCHG(  3,  5 );
         CMPXCHG(  6,  8 );
         return MEAN( f[5], f[6] );
      case 13:
         CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 );
         CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 ); CMPXCHG(  0,  4 );
         CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 );
         CMPXCHG(  8, 12 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG(  0,  2 );
         CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 ); CMPXCHG(  5,  7 );
         CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 ); CMPXCHG(  2,  8 );
         CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 ); CMPXCHG(  2,  4 );
         CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 );
         CMPXCHG( 10, 12 ); CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 );
         CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 );
         CMPXCHG( 10, 11 ); CMPXCHG(  1,  8 ); CMPXCHG(  3, 10 );
         CMPXCHG(  5, 12 ); CMPXCHG(  3,  6 ); CMPXCHG(  5,  8 );
         return pcl::Max( f[5], f[6] );
      case 14:
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG(  0,  2 ); CMPXCHG(  4,  6 );
         CMPXCHG(  8, 10 ); CMPXCHG(  1,  3 ); CMPXCHG(  5,  7 );
         CMPXCHG(  9, 11 ); CMPXCHG(  0,  4 ); CMPXCHG(  8, 12 );
         CMPXCHG(  1,  5 ); CMPXCHG(  9, 13 ); CMPXCHG(  2,  6 );
         CMPXCHG(  3,  7 ); CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 );
         CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 );
         CMPXCHG(  5, 13 ); CMPXCHG(  5, 10 ); CMPXCHG(  6,  9 );
         CMPXCHG(  3, 12 ); CMPXCHG(  7, 11 ); CMPXCHG(  1,  2 );
         CMPXCHG(  4,  8 ); CMPXCHG(  7, 13 ); CMPXCHG(  2,  8 );
         CMPXCHG(  5,  6 ); CMPXCHG(  9, 10 ); CMPXCHG(  3,  8 );
         CMPXCHG(  7, 12 ); CMPXCHG(  6,  8 ); CMPXCHG(  3,  5 );
         CMPXCHG(  7,  9 ); CMPXCHG(  5,  6 ); CMPXCHG(  7,  8 );
         return MEAN( f[6], f[7] );
      case 15:
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG(  0,  2 ); CMPXCHG(  4,  6 );
         CMPXCHG(  8, 10 ); CMPXCHG( 12, 14 ); CMPXCHG(  1,  3 );
         CMPXCHG(  5,  7 ); CMPXCHG(  9, 11 ); CMPXCHG(  0,  4 );
         CMPXCHG(  8, 12 ); CMPXCHG(  1,  5 ); CMPXCHG(  9, 13 );
         CMPXCHG(  2,  6 ); CMPXCHG( 10, 14 ); CMPXCHG(  3,  7 );
         CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 );
         CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 );
         CMPXCHG(  6, 14 ); CMPXCHG(  5, 10 ); CMPXCHG(  6,  9 );
         CMPXCHG(  3, 12 ); CMPXCHG( 13, 14 ); CMPXCHG(  7, 11 );
         CMPXCHG(  1,  2 ); CMPXCHG(  4,  8 ); CMPXCHG(  7, 13 );
         CMPXCHG(  2,  8 ); CMPXCHG(  5,  6 ); CMPXCHG(  9, 10 );
         CMPXCHG(  3,  8 ); CMPXCHG(  7, 12 ); CMPXCHG(  6,  8 );
         CMPXCHG(  3,  5 ); CMPXCHG(  7,  9 ); CMPXCHG(  5,  6 );
         CMPXCHG(  7,  8 );
         return pcl::Max( f[6], f[7] );
      case 16:
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 ); CMPXCHG(  0,  2 );
         CMPXCHG(  4,  6 ); CMPXCHG(  8, 10 ); CMPXCHG( 12, 14 );
         CMPXCHG(  1,  3 ); CMPXCHG(  5,  7 ); CMPXCHG(  9, 11 );
         CMPXCHG( 13, 15 ); CMPXCHG(  0,  4 ); CMPXCHG(  8, 12 );
         CMPXCHG(  1,  5 ); CMPXCHG(  9, 13 ); CMPXCHG(  2,  6 );
         CMPXCHG( 10, 14 ); CMPXCHG(  3,  7 ); CMPXCHG( 11, 15 );
         CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 );
         CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 );
         CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 ); CMPXCHG(  5, 10 );
         CMPXCHG(  6,  9 ); CMPXCHG(  3, 12 ); CMPXCHG( 13, 14 );
         CMPXCHG(  7, 11 ); CMPXCHG(  1,  2 ); CMPXCHG(  4,  8 );
         CMPXCHG(  7, 13 ); CMPXCHG(  2,  8 ); CMPXCHG(  5,  6 );
         CMPXCHG(  9, 10 ); CMPXCHG(  3,  8 ); CMPXCHG(  7, 12 );
         CMPXCHG(  6,  8 ); CMPXCHG( 10, 12 ); CMPXCHG(  3,  5 );
         CMPXCHG(  7,  9 ); CMPXCHG(  5,  6 ); CMPXCHG(  7,  8 );
         CMPXCHG(  9, 10 ); CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 );
         return MEAN( f[7], f[8] );
      case 17:
         CMPXCHG(  0, 16 ); CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 );
         CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 );
         CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 );
         CMPXCHG(  8, 16 ); CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 );
         CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 );
         CMPXCHG(  9, 13 ); CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 );
         CMPXCHG(  4, 16 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG(  2, 16 );
         CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 );
         CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 ); CMPXCHG(  2,  4 );
         CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 );
         CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 );
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 ); CMPXCHG(  1, 16 );
         CMPXCHG(  1,  8 ); CMPXCHG(  3, 10 ); CMPXCHG(  5, 12 );
         CMPXCHG(  7, 14 ); CMPXCHG(  5,  8 ); CMPXCHG(  7, 10 );
         return pcl::Max( f[7], f[8] );
      case 18:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  0,  8 );
         CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 );
         CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 );
         CMPXCHG(  7, 15 ); CMPXCHG(  8, 16 ); CMPXCHG(  9, 17 );
         CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 );
         CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 ); CMPXCHG(  9, 13 );
         CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 ); CMPXCHG(  4, 16 );
         CMPXCHG(  5, 17 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 );
         CMPXCHG(  4,  6 ); CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 );
         CMPXCHG(  9, 11 ); CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 );
         CMPXCHG(  2, 16 ); CMPXCHG(  3, 17 ); CMPXCHG(  2,  8 );
         CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 ); CMPXCHG(  7, 13 );
         CMPXCHG( 10, 16 ); CMPXCHG( 11, 17 ); CMPXCHG(  2,  4 );
         CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 );
         CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 );
         CMPXCHG( 15, 17 ); CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 );
         CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 );
         CMPXCHG( 10, 11 ); CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 );
         CMPXCHG( 16, 17 ); CMPXCHG(  1, 16 ); CMPXCHG(  1,  8 );
         CMPXCHG(  3, 10 ); CMPXCHG(  5, 12 ); CMPXCHG(  7, 14 );
         CMPXCHG(  9, 16 ); CMPXCHG(  5,  8 ); CMPXCHG(  7, 10 );
         CMPXCHG(  9, 12 ); CMPXCHG(  7,  8 ); CMPXCHG(  9, 10 );
         return MEAN( f[8], f[9] );
      case 19:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 );
         CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 );
         CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 ); CMPXCHG(  8, 16 );
         CMPXCHG(  9, 17 ); CMPXCHG( 10, 18 ); CMPXCHG(  0,  4 );
         CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 );
         CMPXCHG(  8, 12 ); CMPXCHG(  9, 13 ); CMPXCHG( 10, 14 );
         CMPXCHG( 11, 15 ); CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 );
         CMPXCHG(  6, 18 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG(  0,  2 );
         CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 ); CMPXCHG(  5,  7 );
         CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 ); CMPXCHG( 12, 14 );
         CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 ); CMPXCHG(  2, 16 );
         CMPXCHG(  3, 17 ); CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 );
         CMPXCHG(  6, 12 ); CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 );
         CMPXCHG( 11, 17 ); CMPXCHG(  2,  4 ); CMPXCHG(  3,  5 );
         CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 ); CMPXCHG( 10, 12 );
         CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 ); CMPXCHG( 15, 17 );
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 ); CMPXCHG( 16, 17 );
         CMPXCHG(  1, 16 ); CMPXCHG(  3, 18 ); CMPXCHG(  3, 10 );
         CMPXCHG(  5, 12 ); CMPXCHG(  7, 14 ); CMPXCHG(  9, 16 );
         CMPXCHG(  7, 10 ); CMPXCHG(  9, 12 );
         return pcl::Min( f[9], f[10] );
      case 20:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  3, 19 ); CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 );
         CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 );
         CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 );
         CMPXCHG(  8, 16 ); CMPXCHG(  9, 17 ); CMPXCHG( 10, 18 );
         CMPXCHG( 11, 19 ); CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 );
         CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 );
         CMPXCHG(  9, 13 ); CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 );
         CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 ); CMPXCHG(  6, 18 );
         CMPXCHG(  7, 19 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG( 15, 19 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 );
         CMPXCHG( 17, 19 ); CMPXCHG(  2, 16 ); CMPXCHG(  3, 17 );
         CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 );
         CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 ); CMPXCHG( 11, 17 );
         CMPXCHG(  2,  4 ); CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 );
         CMPXCHG(  7,  9 ); CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 );
         CMPXCHG( 14, 16 ); CMPXCHG( 15, 17 ); CMPXCHG(  0,  1 );
         CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 );
         CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 ); CMPXCHG( 12, 13 );
         CMPXCHG( 14, 15 ); CMPXCHG( 16, 17 ); CMPXCHG( 18, 19 );
         CMPXCHG(  1, 16 ); CMPXCHG(  3, 18 ); CMPXCHG(  3, 10 );
         CMPXCHG(  5, 12 ); CMPXCHG(  7, 14 ); CMPXCHG(  9, 16 );
         CMPXCHG(  7, 10 ); CMPXCHG(  9, 12 );
         return MEAN( f[9], f[10] );
      case 21:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  3, 19 ); CMPXCHG(  4, 20 ); CMPXCHG(  0,  8 );
         CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 );
         CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 );
         CMPXCHG(  7, 15 ); CMPXCHG(  8, 16 ); CMPXCHG(  9, 17 );
         CMPXCHG( 10, 18 ); CMPXCHG( 11, 19 ); CMPXCHG( 12, 20 );
         CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 );
         CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 ); CMPXCHG(  9, 13 );
         CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 ); CMPXCHG( 16, 20 );
         CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 ); CMPXCHG(  6, 18 );
         CMPXCHG(  7, 19 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG( 15, 19 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 );
         CMPXCHG( 17, 19 ); CMPXCHG(  2, 16 ); CMPXCHG(  3, 17 );
         CMPXCHG(  6, 20 ); CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 );
         CMPXCHG(  6, 12 ); CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 );
         CMPXCHG( 11, 17 ); CMPXCHG( 14, 20 ); CMPXCHG(  2,  4 );
         CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 );
         CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 );
         CMPXCHG( 15, 17 ); CMPXCHG( 18, 20 ); CMPXCHG(  0,  1 );
         CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 );
         CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 ); CMPXCHG( 12, 13 );
         CMPXCHG( 14, 15 ); CMPXCHG( 16, 17 ); CMPXCHG( 18, 19 );
         CMPXCHG(  1, 16 ); CMPXCHG(  3, 18 ); CMPXCHG(  5, 20 );
         CMPXCHG(  3, 10 ); CMPXCHG(  5, 12 ); CMPXCHG(  7, 14 );
         CMPXCHG(  9, 16 ); CMPXCHG(  7, 10 ); CMPXCHG(  9, 12 );
         return pcl::Max( f[9], f[10] );
      case 22:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  3, 19 ); CMPXCHG(  4, 20 ); CMPXCHG(  5, 21 );
         CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 );
         CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 );
         CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 ); CMPXCHG(  8, 16 );
         CMPXCHG(  9, 17 ); CMPXCHG( 10, 18 ); CMPXCHG( 11, 19 );
         CMPXCHG( 12, 20 ); CMPXCHG( 13, 21 ); CMPXCHG(  0,  4 );
         CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 );
         CMPXCHG(  8, 12 ); CMPXCHG(  9, 13 ); CMPXCHG( 10, 14 );
         CMPXCHG( 11, 15 ); CMPXCHG( 16, 20 ); CMPXCHG( 17, 21 );
         CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 ); CMPXCHG(  6, 18 );
         CMPXCHG(  7, 19 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG( 15, 19 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 );
         CMPXCHG( 17, 19 ); CMPXCHG(  2, 16 ); CMPXCHG(  3, 17 );
         CMPXCHG(  6, 20 ); CMPXCHG(  7, 21 ); CMPXCHG(  2,  8 );
         CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 ); CMPXCHG(  7, 13 );
         CMPXCHG( 10, 16 ); CMPXCHG( 11, 17 ); CMPXCHG( 14, 20 );
         CMPXCHG( 15, 21 ); CMPXCHG(  2,  4 ); CMPXCHG(  3,  5 );
         CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 ); CMPXCHG( 10, 12 );
         CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 ); CMPXCHG( 15, 17 );
         CMPXCHG( 18, 20 ); CMPXCHG( 19, 21 ); CMPXCHG(  0,  1 );
         CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 );
         CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 ); CMPXCHG( 12, 13 );
         CMPXCHG( 14, 15 ); CMPXCHG( 16, 17 ); CMPXCHG( 18, 19 );
         CMPXCHG( 20, 21 ); CMPXCHG(  1, 16 ); CMPXCHG(  3, 18 );
         CMPXCHG(  5, 20 ); CMPXCHG(  3, 10 ); CMPXCHG(  5, 12 );
         CMPXCHG(  7, 14 ); CMPXCHG(  9, 16 ); CMPXCHG( 11, 18 );
         CMPXCHG(  7, 10 ); CMPXCHG(  9, 12 ); CMPXCHG( 11, 14 );
         CMPXCHG(  9, 10 ); CMPXCHG( 11, 12 );
         return MEAN( f[10], f[11] );
      case 23:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  3, 19 ); CMPXCHG(  4, 20 ); CMPXCHG(  5, 21 );
         CMPXCHG(  6, 22 ); CMPXCHG(  0,  8 ); CMPXCHG(  1,  9 );
         CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 ); CMPXCHG(  4, 12 );
         CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 ); CMPXCHG(  7, 15 );
         CMPXCHG(  8, 16 ); CMPXCHG(  9, 17 ); CMPXCHG( 10, 18 );
         CMPXCHG( 11, 19 ); CMPXCHG( 12, 20 ); CMPXCHG( 13, 21 );
         CMPXCHG( 14, 22 ); CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 );
         CMPXCHG(  2,  6 ); CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 );
         CMPXCHG(  9, 13 ); CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 );
         CMPXCHG( 16, 20 ); CMPXCHG( 17, 21 ); CMPXCHG( 18, 22 );
         CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 ); CMPXCHG(  6, 18 );
         CMPXCHG(  7, 19 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG( 15, 19 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 );
         CMPXCHG( 17, 19 ); CMPXCHG( 20, 22 ); CMPXCHG(  2, 16 );
         CMPXCHG(  3, 17 ); CMPXCHG(  6, 20 ); CMPXCHG(  7, 21 );
         CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 ); CMPXCHG(  6, 12 );
         CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 ); CMPXCHG( 11, 17 );
         CMPXCHG( 14, 20 ); CMPXCHG( 15, 21 ); CMPXCHG(  2,  4 );
         CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 ); CMPXCHG(  7,  9 );
         CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 ); CMPXCHG( 14, 16 );
         CMPXCHG( 15, 17 ); CMPXCHG( 18, 20 ); CMPXCHG( 19, 21 );
         CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 ); CMPXCHG(  4,  5 );
         CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 ); CMPXCHG( 10, 11 );
         CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 ); CMPXCHG( 16, 17 );
         CMPXCHG( 18, 19 ); CMPXCHG( 20, 21 ); CMPXCHG(  1, 16 );
         CMPXCHG(  3, 18 ); CMPXCHG(  5, 20 ); CMPXCHG(  7, 22 );
         CMPXCHG(  5, 12 ); CMPXCHG(  7, 14 ); CMPXCHG(  9, 16 );
         CMPXCHG( 11, 18 ); CMPXCHG(  9, 12 ); CMPXCHG( 11, 14 );
         return pcl::Min( f[11], f[12] );
      case 24:
         CMPXCHG(  0, 16 ); CMPXCHG(  1, 17 ); CMPXCHG(  2, 18 );
         CMPXCHG(  3, 19 ); CMPXCHG(  4, 20 ); CMPXCHG(  5, 21 );
         CMPXCHG(  6, 22 ); CMPXCHG(  7, 23 ); CMPXCHG(  0,  8 );
         CMPXCHG(  1,  9 ); CMPXCHG(  2, 10 ); CMPXCHG(  3, 11 );
         CMPXCHG(  4, 12 ); CMPXCHG(  5, 13 ); CMPXCHG(  6, 14 );
         CMPXCHG(  7, 15 ); CMPXCHG(  8, 16 ); CMPXCHG(  9, 17 );
         CMPXCHG( 10, 18 ); CMPXCHG( 11, 19 ); CMPXCHG( 12, 20 );
         CMPXCHG( 13, 21 ); CMPXCHG( 14, 22 ); CMPXCHG( 15, 23 );
         CMPXCHG(  0,  4 ); CMPXCHG(  1,  5 ); CMPXCHG(  2,  6 );
         CMPXCHG(  3,  7 ); CMPXCHG(  8, 12 ); CMPXCHG(  9, 13 );
         CMPXCHG( 10, 14 ); CMPXCHG( 11, 15 ); CMPXCHG( 16, 20 );
         CMPXCHG( 17, 21 ); CMPXCHG( 18, 22 ); CMPXCHG( 19, 23 );
         CMPXCHG(  4, 16 ); CMPXCHG(  5, 17 ); CMPXCHG(  6, 18 );
         CMPXCHG(  7, 19 ); CMPXCHG(  4,  8 ); CMPXCHG(  5,  9 );
         CMPXCHG(  6, 10 ); CMPXCHG(  7, 11 ); CMPXCHG( 12, 16 );
         CMPXCHG( 13, 17 ); CMPXCHG( 14, 18 ); CMPXCHG( 15, 19 );
         CMPXCHG(  0,  2 ); CMPXCHG(  1,  3 ); CMPXCHG(  4,  6 );
         CMPXCHG(  5,  7 ); CMPXCHG(  8, 10 ); CMPXCHG(  9, 11 );
         CMPXCHG( 12, 14 ); CMPXCHG( 13, 15 ); CMPXCHG( 16, 18 );
         CMPXCHG( 17, 19 ); CMPXCHG( 20, 22 ); CMPXCHG( 21, 23 );
         CMPXCHG(  2, 16 ); CMPXCHG(  3, 17 ); CMPXCHG(  6, 20 );
         CMPXCHG(  7, 21 ); CMPXCHG(  2,  8 ); CMPXCHG(  3,  9 );
         CMPXCHG(  6, 12 ); CMPXCHG(  7, 13 ); CMPXCHG( 10, 16 );
         CMPXCHG( 11, 17 ); CMPXCHG( 14, 20 ); CMPXCHG( 15, 21 );
         CMPXCHG(  2,  4 ); CMPXCHG(  3,  5 ); CMPXCHG(  6,  8 );
         CMPXCHG(  7,  9 ); CMPXCHG( 10, 12 ); CMPXCHG( 11, 13 );
         CMPXCHG( 14, 16 ); CMPXCHG( 15, 17 ); CMPXCHG( 18, 20 );
         CMPXCHG( 19, 21 ); CMPXCHG(  0,  1 ); CMPXCHG(  2,  3 );
         CMPXCHG(  4,  5 ); CMPXCHG(  6,  7 ); CMPXCHG(  8,  9 );
         CMPXCHG( 10, 11 ); CMPXCHG( 12, 13 ); CMPXCHG( 14, 15 );
         CMPXCHG( 16, 17 ); CMPXCHG( 18, 19 ); CMPXCHG( 20, 21 );
         CMPXCHG( 22, 23 ); CMPXCHG(  1, 16 ); CMPXCHG(  3, 18 );
         CMPXCHG(  5, 20 ); CMPXCHG(  7, 22 ); CMPXCHG(  5, 12 );
         CMPXCHG(  7, 14 ); CMPXCHG(  9, 16 ); CMPXCHG( 11, 18 );
         CMPXCHG(  9, 12 ); CMPXCHG( 11, 14 );
         return MEAN( f[11], f[12] );
      default:
         {
            distance_type n2 = distance_type( n >> 1 );
            if ( n & 1 )
               return *pcl::Select( f, f+n, n2 );
            return P::FloatToSample( (double( *pcl::Select( f, f+n, n2   ) )
                                    + double( *pcl::Select( f, f+n, n2-1 ) ))/2 );
         }
      }
   }

#undef CMPXCHG
#undef MEAN
};

// ----------------------------------------------------------------------------

/*!
 * \class SelectionFilter
 * \brief Morphological selection operator.
 *
 * The \e selection morphological operator (or selection order-statistic
 * filter) computes the value corresponding to a prescribed percentile in the
 * ranked set of values from a pixel neighborhood.
 *
 * The <em>selection point</em> \a k of the selection operator defines the
 * working percentile: for k=0, we have an erosion (or minimum) operator; for
 * k=1 we have a dilation (or maximum) operator; k=0.5 defines the median
 * operator. Other values work as a balance between erosion and dilation.
 */
class PCL_CLASS SelectionFilter : public MorphologicalOperator
{
public:

   /*!
    * Default constructor. The default selection point is 0.5, equivalent to a
    * median operator.
    */
   SelectionFilter() = default;

   /*!
    * Constructs a %SelectionFilter with selection point \a p.
    */
   SelectionFilter( float p )
      : k( pcl::Range( p, float( 0 ), float( 1 ) ) )
   {
      PCL_PRECONDITION( 0 <= p && p <= 1 )
      PCL_CHECK( 0 <= k && k <= 1 )
   }

   /*!
    * Copy constructor.
    */
   SelectionFilter( const SelectionFilter& ) = default;

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new SelectionFilter( *this );
   }

   /*!
    * Returns the selection point of this morphological selection operator.
    */
   float SelectionPoint() const
   {
      return k;
   }

   /*!
    * Sets the selection point of this morphological selection operator.
    */
   void SetSelectionPoint( float _k )
   {
      PCL_PRECONDITION( 0 <= _k && _k <= 1 )
      k = pcl::Range( _k, float( 0 ), float( 1 ) );
   }

   /*!
    */
   String Description() const override
   {
      return String().Format( "Selection, k=%.5f", k );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n );
   }

private:

   float k = 0.5F;

   template <typename T>
   T Operate( T* f, size_type n ) const
   {
      return *pcl::Select( f, f+n, distance_type( pcl::RoundInt( k*(n-1) ) ) );
   }
};

// ----------------------------------------------------------------------------

/*!
 * \class MidpointFilter
 * \brief Midpoint operator.
 *
 * The \e midpoint operator computes the midpoint value in a pixel
 * neighborhood, namely: (minimum + maximum)/2.
 */
class PCL_CLASS MidpointFilter : public MorphologicalOperator
{
public:

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new MidpointFilter( *this );
   }

   /*!
    */
   String Description() const override
   {
      return "Midpoint";
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (FloatPixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (DoublePixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt8PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt16PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt32PixelTraits*)0 );
   }

private:

   template <typename T, class P>
   static T Operate( T* f, size_type n, P* )
   {
      T* min, * max;
      pcl::FindExtremeItems( min, max, f, f+n );
      return P::FloatToSample( (double( *min ) + double( *max ))/2 );
   }
};

// ----------------------------------------------------------------------------

/*!
 * \class AlphaTrimmedMeanFilter
 * \brief Alpha-trimmed mean operator
 *
 * The <em>alpha-trimmed mean</em> operator computes the mean of the remaining
 * values in a pixel neighborhood, after suppressing the d/2 lowest and the d/2
 * highest values. The point \a d defines the <em>trimming factor</em> of the
 * operator. When d=0, we have an arithmetic mean filter. If d=1, the filter is
 * the median operator.
 *
 * The alpha-trimmed operator is not a morphological operator in the strict
 * sense, although it allows for the implementation of robust filters that
 * share some important properties with morphological filters in practical
 * applications.
 */
class PCL_CLASS AlphaTrimmedMeanFilter : public MorphologicalOperator
{
public:

   /*!
    * Default constructor. The default trimming factor is 0.2, which leads to
    * the suppression of a 10% of the lowest and highest neighbor pixels. The
    * resulting object is a robust mean filter resilient to outliers in most
    * practical cases.
    */
   AlphaTrimmedMeanFilter() = default;

   /*!
    * Constructs a %AlphaTrimmedMeanFilter object with the specified trimming
    * factor \a t in the [0,1] range.
    */
   AlphaTrimmedMeanFilter( float t )
      : d( pcl::Range( t, float( 0 ), float( 1 ) ) )
   {
      PCL_PRECONDITION( 0 <= t && t <= 1 )
      PCL_CHECK( 0 <= d && d <= 1 )
   }

   /*!
    * Copy constructor.
    */
   AlphaTrimmedMeanFilter( const AlphaTrimmedMeanFilter& ) = default;

   /*!
    */
   MorphologicalOperator* Clone() const override
   {
      return new AlphaTrimmedMeanFilter( *this );
   }

   /*!
    * Returns the trimming factor of this alpha-trimmed mean operator.
    */
   float TrimmingFactor() const
   {
      return d;
   }

   /*!
    * Sets the trimming factor \a t of this alpha-trimmed mean operator.
    */
   void SetTrimmingFactor( float t )
   {
      PCL_PRECONDITION( 0 <= t && t <= 1 )
      d = pcl::Range( t, float( 0 ), float( 1 ) );
   }

   /*!
    */
   String Description() const override
   {
      return String().Format( "Alpha-trimmed mean, d=%.5f", d );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * floating point pixel samples.
    */
   FloatPixelTraits::sample operator ()( FloatPixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (FloatPixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 64-bit
    * floating point pixel samples.
    */
   DoublePixelTraits::sample operator ()( DoublePixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (DoublePixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 8-bit
    * unsigned integer pixel samples.
    */
   UInt8PixelTraits::sample operator ()( UInt8PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt8PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 16-bit
    * unsigned integer pixel samples.
    */
   UInt16PixelTraits::sample operator ()( UInt16PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt16PixelTraits*)0 );
   }

   /*!
    * Applies this morphological operator to a vector \a f of \a n 32-bit
    * unsigned integer pixel samples.
    */
   UInt32PixelTraits::sample operator ()( UInt32PixelTraits::sample* f, size_type n ) const override
   {
      return Operate( f, n, (UInt32PixelTraits*)0 );
   }

private:

   float d = 0.2F;

   template <typename T, class P>
   T Operate( T* f, size_type n, P* ) const
   {
      pcl::Sort( f, f+n );
      double s = 0;
      size_type i1 = RoundInt( d*((n - 1) >> 1) );
      size_type i2 = n-i1;
      for ( size_type i = i1; i < i2; ++i )
         s += f[i];
      return P::FloatToSample( s/(i2 - i1) );
   }
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __PCL_MorphologicalOperator_h

// ----------------------------------------------------------------------------
// EOF pcl/MorphologicalOperator.h - Released 2021-04-09T19:40:59Z
