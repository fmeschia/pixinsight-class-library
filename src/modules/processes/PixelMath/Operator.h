//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 2.4.0
// ----------------------------------------------------------------------------
// Standard PixelMath Process Module Version 1.5.0
// ----------------------------------------------------------------------------
// Operator.h - Released 2020-07-31T19:33:39Z
// ----------------------------------------------------------------------------
// This file is part of the standard PixelMath PixInsight module.
//
// Copyright (c) 2003-2020 Pleiades Astrophoto S.L. All Rights Reserved.
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

#ifndef __Operator_h
#define __Operator_h

#include "Functional.h"

namespace pcl
{

// ----------------------------------------------------------------------------

/*
 * Representation of an operator in a PixelMath expression.
 */
class Operator : public Functional
{
public:

   typedef IndirectArray<Operator>  operator_set;

   struct IndexNode
   {
            String    token;
      const Operator* op;

      IndexNode( const String& t, const Operator* o = nullptr )
         : token( t )
         , op( o )
      {
      }

      IndexNode( const IndexNode& ) = default;

      bool operator ==( const IndexNode& x ) const
      {
         return token == x.token;
      }

      bool operator <( const IndexNode& x ) const
      {
         return token < x.token;
      }
   };

   typedef SortedArray<IndexNode>   operator_index;

   Operator( int p )
      : Functional( XPR_OPERATOR, p )
   {
   }

   Operator( const Operator& ) = default;

   int NumberOfArguments() const override
   {
      return (IsLeftAssociative() && IsRightAssociative()) ? 2 : 1;
   }

   virtual Expression* Clone() const = 0;
   virtual Expression* Generate( int ) const = 0;

   virtual String Meta() const = 0;
   virtual String Id() const = 0;
   virtual String Token() const = 0;

   virtual void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const = 0;

   virtual int Precedence() const = 0;

   virtual bool IsLeftAssociative() const
   {
      return true;
   }

   virtual bool IsRightAssociative() const
   {
      return true;
   }

   virtual bool IsCommutative() const
   {
      return true;
   }

   virtual bool IsArithmetic() const
   {
      return false;
   }

   virtual bool IsBitwise() const
   {
      return false;
   }

   virtual bool IsLogical() const
   {
      return false;
   }

   virtual bool IsRelational() const
   {
      return false;
   }

   virtual bool IsAssignment() const
   {
      return false;
   }

   virtual bool IsAdditive() const
   {
      return false;
   }

   virtual bool IsMultiplicative() const
   {
      return false;
   }

   String ToString() const override;

   static void InitializeList( operator_set&, operator_index& );
};

// ----------------------------------------------------------------------------

/*
 * Operator Precedence.
 *
 * Currently we have 14 operator precedence levels, as described in the table
 * below. Lower precedence levels correspond to higher evaluation precedences.
 *
 * =====  ================================  ===================================
 * Prec.  Operators                         Description
 * =====  ================================  ===================================
 *   0    () [] -> . :: ++ --               Grouping
 *   1    ! ~ ++ -- - + * &                 Logical negation / sign change
 *   2    ^                                 Exponentiation
 *   3    * / %                             Multiplication, division, modulus
 *   4    + -                               Addition and subtraction
 *   5    << >>                             Bitwise shift left and right
 *   6    < <= > >=                         Comparisons: less-than, ...
 *   7    ==  !=                            Comparisons: equal and not equal
 *   8    &                                 Bitwise AND
 *   9    ^                                 Bitwise exclusive OR
 *  10    |                                 Bitwise inclusive (normal) OR
 *  11    &&                                Logical AND
 *  12    ||                                Logical OR
 *  13    = += -= *= /= %= &= ^= <<= >>=    Assignment operators
 * =====  ================================  ===================================
 */
#define PRECEDENCE_GROUPING       0
#define PRECEDENCE_INV            1
#define PRECEDENCE_POW            2
#define PRECEDENCE_MUL            3
#define PRECEDENCE_ADD            4
#define PRECEDENCE_SHIFT          5
#define PRECEDENCE_INEQUALITY     6
#define PRECEDENCE_EQUALITY       7
#define PRECEDENCE_AND            8
#define PRECEDENCE_XOR            9
#define PRECEDENCE_OR            10
#define PRECEDENCE_LOGICAL_AND   11
#define PRECEDENCE_LOGICAL_OR    12
#define PRECEDENCE_ASSIGNMENT    13

#define MAX_PRECEDENCE           PRECEDENCE_ASSIGNMENT

// ----------------------------------------------------------------------------

class InvOperator : public Operator
{
public:

   InvOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new InvOperator( *this ); }
   Expression* Generate( int p ) const override { return new InvOperator( p ); }

   String Meta() const override               { return "~x"; }
   String Id() const override                 { return "Pixel inversion.\n"
                                                       "Evaluates to 1 &minus; <i>x</i>, where <i>x</i> is "
                                                       "in the normalized [0,1] range (0=black, 1=white)."; }
   String Token() const override              { return "~"; }
   int    Precedence() const override         { return PRECEDENCE_INV; }
   bool   IsLeftAssociative() const override  { return false; }
   bool   IsArithmetic() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class ChsOperator : public Operator
{
public:

   ChsOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new ChsOperator( *this ); }
   Expression* Generate( int p ) const override { return new ChsOperator( p ); }

   String Meta() const override               { return "-x"; }
   String Id() const override                 { return "Unary minus (sign change).\n"
                                                       "Evaluates to <i>x</i> negative if <i>x</i> &gt; 0; "
                                                       "to <i>x</i> positive if <i>x</i> &le; 0."; }
   String Token() const override              { return "-"; }
   int    Precedence() const override         { return PRECEDENCE_INV; }
   bool   IsLeftAssociative() const override  { return false; }
   bool   IsArithmetic() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class PlusOperator : public Operator
{
public:

   PlusOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new PlusOperator( *this ); }
   Expression* Generate( int p ) const override { return new PlusOperator( p ); }

   String Meta() const override               { return "+x"; }
   String Id() const override                 { return "Unary plus (no change).\n"
                                                       "Evaluates to <i>x</i>."; }
   String Token() const override              { return "+"; }
   int    Precedence() const override         { return PRECEDENCE_INV; }
   bool   IsLeftAssociative() const override  { return false; }
   bool   IsArithmetic() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class LogicalNotOperator : public Operator
{
public:

   LogicalNotOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new LogicalNotOperator( *this ); }
   Expression* Generate( int p ) const override { return new LogicalNotOperator( p ); }

   String Meta() const override               { return "!x"; }
   String Id() const override                 { return "Logical NOT.\n"
                                                       "Evaluates to 0 if <i>x</i> &ne; 0; to 1 if <i>x</i> = 0."; }
   String Token() const override              { return "!"; }
   int    Precedence() const override         { return PRECEDENCE_INV; }
   bool   IsLeftAssociative() const override  { return false; }
   bool   IsLogical() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class PowOperator : public Operator
{
public:

   PowOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new PowOperator( *this ); }
   Expression* Generate( int p ) const override { return new PowOperator( p ); }

   String Meta() const override               { return "x ^ y"; }
   String Id() const override                 { return "Exponentiation.\n"
                                                       "Evaluates to <i>x</i> raised to <i>y</i>."; }
   String Token() const override              { return "^"; }
   int    Precedence() const override         { return PRECEDENCE_POW; }
   bool   IsCommutative() const override      { return false; }
   bool   IsArithmetic() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class MulOperator : public Operator
{
public:

   MulOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new MulOperator( *this ); }
   Expression* Generate( int p ) const override { return new MulOperator( p ); }

   String Meta() const override               { return "x * y"; }
   String Id() const override                 { return "Multiplication.\n"
                                                       "Evaluates to <i>x</i> multiplied by <i>y</i>."; }
   String Token() const override              { return "*"; }
   int    Precedence() const override         { return PRECEDENCE_MUL; }
   bool   IsArithmetic() const override       { return true; }
   bool   IsMultiplicative() const override   { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class DivOperator : public Operator
{
public:

   DivOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new DivOperator( *this ); }
   Expression* Generate( int p ) const override { return new DivOperator( p ); }

   String Meta() const override               { return "x / y"; }
   String Id() const override                 { return "Division.\n"
                                                       "Evaluates to <i>x</i> divided by <i>y</i>. If "
                                                       "<i>y</i> is zero or insignificant, then the result is the "
                                                       "maximum representable finite 64-bit floating-point value, "
                                                       "with the same sign as the numerator."; }
   String Token() const override              { return "/"; }
   int    Precedence() const override         { return PRECEDENCE_MUL; }
   bool   IsCommutative() const override      { return false; }
   bool   IsArithmetic() const override       { return true; }
   bool   IsMultiplicative() const override   { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class ModOperator : public Operator
{
public:

   ModOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new ModOperator( *this ); }
   Expression* Generate( int p ) const override { return new ModOperator( p ); }

   String Meta() const override               { return "x % y"; }
   String Id() const override                 { return "Modulus.\n"
                                                       "Evaluates to the floating-point remainder of the "
                                                       "<i>x</i>/<i>y</i> division, such that "
                                                       "<i>x</i> = <i>i</i>&times;<i>y</i> + <i>f</i>, "
                                                       "where <i>i</i> is an integer, <i>f</i> has the same "
                                                       "sign as <i>x</i>, and the absolute value of <i>f</i> "
                                                       "is less than the absolute value of <i>y</i>.\n"
                                                       "If <i>y</i> evaluates to zero or to an insignificant value, "
                                                       "the result is zero conventionally."; }
   String Token() const override              { return "%"; }
   int    Precedence() const override         { return PRECEDENCE_MUL; }
   bool   IsCommutative() const override      { return false; }
   bool   IsArithmetic() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AddOperator : public Operator
{
public:

   AddOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AddOperator( *this ); }
   Expression* Generate( int p ) const override { return new AddOperator( p ); }

   String Meta() const override               { return "x + y"; }
   String Id() const override                 { return "Addition.\n"
                                                       "Evaluates to <i>x</i> added to <i>y</i>."; }
   String Token() const override              { return "+"; }
   int    Precedence() const override         { return PRECEDENCE_ADD; }
   bool   IsArithmetic() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class SubOperator : public Operator
{
public:

   SubOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new SubOperator( *this ); }
   Expression* Generate( int p ) const override { return new SubOperator( p ); }

   String Meta() const override               { return "x - y"; }
   String Id() const override                 { return "Subtraction.\n"
                                                       "Evaluates to <i>y</i> subtracted from <i>x</i>."; }
   String Token() const override              { return "-"; }
   int    Precedence() const override         { return PRECEDENCE_ADD; }
   bool   IsCommutative() const override      { return false; }
   bool   IsArithmetic() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class DifOperator : public Operator
{
public:

   DifOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new DifOperator( *this ); }
   Expression* Generate( int p ) const override { return new DifOperator( p ); }

   String Meta() const override               { return "x -- y"; }
   String Id() const override                 { return "Absolute Difference.\n"
                                                       "Evaluates to the absolute value of <i>x</i>&minus;<i>y</i>."; }
   String Token() const override              { return "--"; }
   int    Precedence() const override         { return PRECEDENCE_ADD; }
   bool   IsCommutative() const override      { return false; }
   bool   IsArithmetic() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class LessThanOperator : public Operator
{
public:

   LessThanOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new LessThanOperator( *this ); }
   Expression* Generate( int p ) const override { return new LessThanOperator( p ); }

   String Meta() const override               { return "x < y"; }
   String Id() const override                 { return "Less Than relational operator\n"
                                                       "Evaluates to 1 if <i>x</i> &lt; <i>y</i>; "
                                                       "to 0 if <i>x</i> &ge; <i>y</i>."; }
   String Token() const override              { return "<"; }
   int    Precedence() const override         { return PRECEDENCE_INEQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class LessThanOrEqualOperator : public Operator
{
public:

   LessThanOrEqualOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new LessThanOrEqualOperator( *this ); }
   Expression* Generate( int p ) const override { return new LessThanOrEqualOperator( p ); }

   String Meta() const override               { return "x <= y"; }
   String Id() const override                 { return "Less Than Or Equal relational operator.\n"
                                                       "Evaluates to 1 if <i>x</i> &le; <i>y</i>; "
                                                       "to 0 if <i>x</i> &gt; <i>y</i>."; }
   String Token() const override              { return "<="; }
   int    Precedence() const override         { return PRECEDENCE_INEQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class GreaterThanOperator : public Operator
{
public:

   GreaterThanOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new GreaterThanOperator( *this ); }
   Expression* Generate( int p ) const override { return new GreaterThanOperator( p ); }

   String Meta() const override               { return "x > y"; }
   String Id() const override                 { return "Greater Than relational operator.\n"
                                                       "Evaluates to 1 if <i>x</i> &gt; <i>y</i>; "
                                                       "to 0 if <i>x</i> &le; <i>y</i>."; }
   String Token() const override              { return ">"; }
   int    Precedence() const override         { return PRECEDENCE_INEQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class GreaterThanOrEqualOperator : public Operator
{
public:

   GreaterThanOrEqualOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new GreaterThanOrEqualOperator( *this ); }
   Expression* Generate( int p ) const override { return new GreaterThanOrEqualOperator( p ); }

   String Meta() const override               { return "x >= y"; }
   String Id() const override                 { return "Greater Than Or Equal relational operator.\n"
                                                       "Evaluates to 1 if <i>x</i> &ge; <i>y</i>; "
                                                       "to 0 if <i>x</i> &lt; <i>y</i>."; }
   String Token() const override              { return ">="; }
   int    Precedence() const override         { return PRECEDENCE_INEQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class EqualToOperator : public Operator
{
public:

   EqualToOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new EqualToOperator( *this ); }
   Expression* Generate( int p ) const override { return new EqualToOperator( p ); }

   String Meta() const override               { return "x == y"; }
   String Id() const override                 { return "Equal To relational operator.\n"
                                                       "Evaluates to 1 if <i>x</i> = <i>y</i>; "
                                                       "to 0 if <i>x</i> &ne; <i>y</i>."; }
   String Token() const override              { return "=="; }
   int    Precedence() const override         { return PRECEDENCE_EQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class NotEqualToOperator : public Operator
{
public:

   NotEqualToOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new NotEqualToOperator( *this ); }
   Expression* Generate( int p ) const override { return new NotEqualToOperator( p ); }

   String Meta() const override               { return "x != y"; }
   String Id() const override                 { return "Not Equal To relational operator.\n"
                                                       "Evaluates to 1 if <i>x</i> &ne; <i>y</i>; "
                                                       "to 0 if <i>x</i> = <i>y</i>."; }
   String Token() const override              { return "!="; }
   int    Precedence() const override         { return PRECEDENCE_EQUALITY; }
   bool   IsRelational() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AndOperator : public Operator
{
public:

   AndOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AndOperator( *this ); }
   Expression* Generate( int p ) const override { return new AndOperator( p ); }

   String Meta() const override               { return "x & y"; }
   String Id() const override                 { return "Bitwise AND.\n"
                                                       "Evaluates to the bitwise AND operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 1 if "
                                                       "both bits are 1; 0 otherwise."; }
   String Token() const override              { return "&"; }
   int    Precedence() const override         { return PRECEDENCE_AND; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class NandOperator : public Operator
{
public:

   NandOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new NandOperator( *this ); }
   Expression* Generate( int p ) const override { return new NandOperator( p ); }

   String Meta() const override               { return "x !& y"; }
   String Id() const override                 { return "Bitwise NAND.\n"
                                                       "Evaluates to the bitwise NAND operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 0 if "
                                                       "both bits are 1; 1 otherwise."; }
   String Token() const override              { return "!&"; }
   int    Precedence() const override         { return PRECEDENCE_AND; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class XorOperator : public Operator
{
public:

   XorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new XorOperator( *this ); }
   Expression* Generate( int p ) const override { return new XorOperator( p ); }

   String Meta() const override               { return "x &| y"; }
   String Id() const override                 { return "Bitwise XOR.\n"
                                                       "Evaluates to the bitwise XOR operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 0 if "
                                                       "both bits are equal; 1 otherwise."; }
   String Token() const override              { return "&|"; }
   int    Precedence() const override         { return PRECEDENCE_XOR; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class XnorOperator : public Operator
{
public:

   XnorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new XnorOperator( *this ); }
   Expression* Generate( int p ) const override { return new XnorOperator( p ); }

   String Meta() const override               { return "x !&| y"; }
   String Id() const override                 { return "Bitwise XNOR.\n"
                                                       "Evaluates to the bitwise XNOR operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 1 if "
                                                       "both bits are equal; 0 otherwise."; }
   String Token() const override              { return "!&|"; }
   int    Precedence() const override         { return PRECEDENCE_XOR; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class OrOperator : public Operator
{
public:

   OrOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new OrOperator( *this ); }
   Expression* Generate( int p ) const override { return new OrOperator( p ); }

   String Meta() const override               { return "x | y"; }
   String Id() const override                 { return "Bitwise OR.\n"
                                                       "Evaluates to the bitwise OR operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 0 if "
                                                       "both bits are 0; 1 otherwise."; }
   String Token() const override              { return "|"; }
   int    Precedence() const override         { return PRECEDENCE_OR; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class NorOperator : public Operator
{
public:

   NorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new NorOperator( *this ); }
   Expression* Generate( int p ) const override { return new NorOperator( p ); }

   String Meta() const override               { return "x !| y"; }
   String Id() const override                 { return "Bitwise NOR.\n"
                                                       "Evaluates to the bitwise NOR operation applied to both "
                                                       "operands truncated to integer values. For each pair of "
                                                       "corresponding bits in both operands, the result is 1 if "
                                                       "both bits are 0; 0 otherwise."; }
   String Token() const override              { return "!|"; }
   int    Precedence() const override         { return PRECEDENCE_OR; }
   bool   IsBitwise() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class LogicalAndOperator : public Operator
{
public:

   LogicalAndOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new LogicalAndOperator( *this ); }
   Expression* Generate( int p ) const override { return new LogicalAndOperator( p ); }

   String Meta() const override               { return "x && y"; }
   String Id() const override                 { return "Logical AND.\n"
                                                       "Evaluates to 1 if both operands are nonzero; "
                                                       "to 0 if any of the operands is zero."; }
   String Token() const override              { return "&&"; }
   int    Precedence() const override         { return PRECEDENCE_LOGICAL_AND; }
   bool   IsLogical() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;

   bool CanOptimize() const override          { return true; }
   component_list Optimized() const override;
};

// ----------------------------------------------------------------------------

class LogicalOrOperator : public Operator
{
public:

   LogicalOrOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new LogicalOrOperator( *this ); }
   Expression* Generate( int p ) const override { return new LogicalOrOperator( p ); }

   String Meta() const override               { return "x || y"; }
   String Id() const override                 { return "Logical OR.\n"
                                                       "Evaluates to 0 if both operands are zero; "
                                                       "to 1 if any of the operands is nonzero."; }
   String Token() const override              { return "||"; }
   int    Precedence() const override         { return PRECEDENCE_LOGICAL_OR; }
   bool   IsLogical() const override          { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;

   bool IsInvariant( component_list::const_iterator, component_list::const_iterator ) const override;
   void operator()( Pixel&, component_list::const_iterator, component_list::const_iterator ) const override;

   bool CanOptimize() const override          { return true; }
   component_list Optimized() const override;
};

// ----------------------------------------------------------------------------

class AssignmentOperator : public Operator
{
public:

   AssignmentOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentOperator( p ); }

   String Meta() const override               { return "var = expr"; }
   String Id() const override                 { return "Assignment.\n"
                                                       "The expression <i>expr</i> is evaluated, and its "
                                                       "resulting value is assigned to the variable <i>var</i>."; }
   String Token() const override              { return "="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentAddOperator : public Operator
{
public:

   AssignmentAddOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentAddOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentAddOperator( p ); }

   String Meta() const override               { return "var += expr"; }
   String Id() const override                 { return "Assignment / Addition.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then added to the current value of the variable "
                                                       "<i>var</i>, and the result of the addition is assigned to "
                                                       "<i>var</i>."; }
   String Token() const override              { return "+="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentSubOperator : public Operator
{
public:

   AssignmentSubOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentSubOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentSubOperator( p ); }

   String Meta() const override               { return "var -= expr"; }
   String Id() const override                 { return "Assignment / Subtraction.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then subtracted from the current value of the variable "
                                                       "<i>var</i>, and the result of the subtraction is assigned to "
                                                       "<i>var</i>."; }
   String Token() const override              { return "-="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentMulOperator : public Operator
{
public:

   AssignmentMulOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentMulOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentMulOperator( p ); }

   String Meta() const override               { return "var *= expr"; }
   String Id() const override                 { return "Assignment / Multiplication.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then multiplied by the current value of the variable "
                                                       "<i>var</i>, and the result of the multiplication is assigned to "
                                                       "<i>var</i>."; }
   String Token() const override              { return "*="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }
   bool   IsMultiplicative() const override   { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentDivOperator : public Operator
{
public:

   AssignmentDivOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentDivOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentDivOperator( p ); }

   String Meta() const override               { return "var /= expr"; }
   String Id() const override                 { return "Assignment / Division.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then divided by the current value of the variable "
                                                       "<i>var</i>, and the result of the division is assigned to "
                                                       "<i>var</i>. If <i>expr</i> evaluates to zero or to an "
                                                       "insignificant value, <i>var</i> is assigned with the maximum "
                                                       "representable finite 64-bit floating-point value, with the same "
                                                       "sign as <i>var</i>."; }
   String Token() const override              { return "/="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }
   bool   IsMultiplicative() const override   { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentPowOperator : public Operator
{
public:

   AssignmentPowOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentPowOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentPowOperator( p ); }

   String Meta() const override               { return "var ^= expr"; }
   String Id() const override                 { return "Assignment / Exponentiation.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then raised to the current value of the variable "
                                                       "<i>var</i>, and the result of the exponentiation is assigned to "
                                                       "<i>var</i>."; }
   String Token() const override              { return "^="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentModOperator : public Operator
{
public:

   AssignmentModOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentModOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentModOperator( p ); }

   String Meta() const override               { return "var %= expr"; }
   String Id() const override                 { return "Assignment / Modulus.\n"
                                                       "The expression <i>expr</i> is evaluated, the remainder of its "
                                                       "resulting value divided by the current value of the variable "
                                                       "<i>var</i> is then calculated and assigned to <i>var</i>. "
                                                       "If <i>expr</i> evaluates to zero or to an insignificant value, "
                                                       "<i>var</i> is assigned with zero conventionally.\n"
                                                       "See also the modulus arithmetic operator."; }
   String Token() const override              { return "%="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentDifOperator : public Operator
{
public:

   AssignmentDifOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentDifOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentDifOperator( p ); }

   String Meta() const override               { return "var --= expr"; }
   String Id() const override                 { return "Assignment / Absolute Difference.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then subtracted from the current value of the variable "
                                                       "<i>var</i>, and the absolute value of the difference is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "--="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }
   bool   IsAdditive() const override         { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentAndOperator : public Operator
{
public:

   AssignmentAndOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentAndOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentAndOperator( p ); }

   String Meta() const override               { return "var &= expr"; }
   String Id() const override                 { return "Assignment / Bitwise AND.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-ANDed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise AND is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "&="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentNandOperator : public Operator
{
public:

   AssignmentNandOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentNandOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentNandOperator( p ); }

   String Meta() const override               { return "var !&= expr"; }
   String Id() const override                 { return "Assignment / Bitwise NAND.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-NANDed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise NAND is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "!&="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentOrOperator : public Operator
{
public:

   AssignmentOrOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentOrOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentOrOperator( p ); }

   String Meta() const override               { return "var |= expr"; }
   String Id() const override                 { return "Assignment / Bitwise OR.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-ORed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise OR is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "|="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentNorOperator : public Operator
{
public:

   AssignmentNorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentNorOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentNorOperator( p ); }

   String Meta() const override               { return "var !|= expr"; }
   String Id() const override                 { return "Assignment / Bitwise NOR.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-NORed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise NOR is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "!|="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentXorOperator : public Operator
{
public:

   AssignmentXorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentXorOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentXorOperator( p ); }

   String Meta() const override               { return "var &|= expr"; }
   String Id() const override                 { return "Assignment / Bitwise XOR.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-XORed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise XOR is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "&|="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentXnorOperator : public Operator
{
public:

   AssignmentXnorOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentXnorOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentXnorOperator( p ); }

   String Meta() const override               { return "var !&|= expr"; }
   String Id() const override                 { return "Assignment / Bitwise XNOR.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then bitwise-XNORed with the current value of the "
                                                       "variable <i>var</i>, and the result of the bitwise XNOR is "
                                                       "assigned to <i>var</i>."; }
   String Token() const override              { return "!&|="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentLogicalAndOperator : public Operator
{
public:

   AssignmentLogicalAndOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentLogicalAndOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentLogicalAndOperator( p ); }

   String Meta() const override               { return "var &&= expr"; }
   String Id() const override                 { return "Assignment / Logical AND.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then logically-ANDed with the current value of the "
                                                       "variable <i>var</i>, and the result of the logical AND "
                                                       "(either 1 or 0) is assigned to <i>var</i>."; }
   String Token() const override              { return "&&="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

class AssignmentLogicalOrOperator : public Operator
{
public:

   AssignmentLogicalOrOperator( int p = 0 ) : Operator( p ) {}

   Expression* Clone() const override { return new AssignmentLogicalOrOperator( *this ); }
   Expression* Generate( int p ) const override { return new AssignmentLogicalOrOperator( p ); }

   String Meta() const override               { return "var ||= expr"; }
   String Id() const override                 { return "Assignment / Logical OR.\n"
                                                       "The expression <i>expr</i> is evaluated, its resulting "
                                                       "value is then logically-ORed with the current value of the "
                                                       "variable <i>var</i>, and the result of the logical OR "
                                                       "(either 1 or 0) is assigned to <i>var</i>."; }
   String Token() const override              { return "||="; }
   int    Precedence() const override         { return PRECEDENCE_ASSIGNMENT; }
   bool   IsCommutative() const override      { return false; }
   bool   IsAssignment() const override       { return true; }

   void operator()( Pixel&, pixel_set::const_iterator, pixel_set::const_iterator ) const override;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __Operator_h

// ----------------------------------------------------------------------------
// EOF Operator.h - Released 2020-07-31T19:33:39Z