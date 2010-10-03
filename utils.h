
/// vim: tabstop=4:hlsearch

/* Copyright 2010 University of Lugano. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of the University of Lugano.
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED 1

/** @file utils.h
 *  Utility functions
 */

#ifdef __cplusplus
extern "C" {
#endif

/** min function which returns the minimum of the two input arguments
 */
#define DEFINE_MIN_FUNCTION(type)			\
	static inline type min_ ## type(type x, type y)	\
	{						\
		return (x > y) ? y : x;			\
	}

/** max function which returns the minimum of the two input arguments
 */
#define DEFINE_MAX_FUNCTION(type)			\
	static inline type max_ ## type(type x, type y)	\
	{						\
		return (x > y) ? x : y;			\
	}

/** fill function which fills the values between the x and y with the value val
 */
#define DEFINE_FILL_FUNCTION(type)						\
	static inline void fill_ ## type ## s(type *x, type *y, type val)	\
	{									\
		type *z;							\
		for(z = x; z != y; ++z) {					\
			*z = val;						\
		}								\
	}

/** Swap function which exchanges two values
 */
#define DEFINE_SWAP_FUNCTION(type)				\
	static inline void swap_ ## type(type *x, type *y)	\
	{							\
		type t;						\
		t  = *x;					\
		*x = *y;					\
		*y = t;						\
	}

/** Accumulate function to compute the sum of the elements of a range
 */
#define DEFINE_ACCUMULATE_FUNCTION(type)					\
	static inline type accumulate_ ## type(type *p, type *q, type i)	\
	{									\
		for(; p != q; ++p) {						\
			i += *p;						\
		}								\
		return i;							\
	}

/** Product function
 */
#define DEFINE_PRODUCT_FUNCTION(type)						\
	static inline type product_ ## type(type *p, type *q, type i)		\
	{									\
		for(; p != q; ++p) {						\
			i *= *p;						\
		}								\
		return i;							\
	}
	

DEFINE_MIN_FUNCTION(   int)
DEFINE_MIN_FUNCTION( float)
DEFINE_MIN_FUNCTION(double)

#undef DEFINE_MIN_FUNCTION

DEFINE_MAX_FUNCTION(   int)
DEFINE_MAX_FUNCTION( float)
DEFINE_MAX_FUNCTION(double)

#undef DEFINE_MAX_FUNCTION

DEFINE_FILL_FUNCTION(   int)
DEFINE_FILL_FUNCTION( float)
DEFINE_FILL_FUNCTION(double)

#undef DEFINE_FILL_FUNCTION

DEFINE_SWAP_FUNCTION(   int)
DEFINE_SWAP_FUNCTION( float)
DEFINE_SWAP_FUNCTION(double)
	
#undef DEFINE_SWAP_FUNCTION

DEFINE_ACCUMULATE_FUNCTION(   int)
DEFINE_ACCUMULATE_FUNCTION( float)
DEFINE_ACCUMULATE_FUNCTION(double)
	
#undef DEFINE_ACCUMULATE_FUNCTION

DEFINE_PRODUCT_FUNCTION(   int)
DEFINE_PRODUCT_FUNCTION( float)
DEFINE_PRODUCT_FUNCTION(double)
	
#undef DEFINE_PRODUCT_FUNCTION

/** Repeat a statement a constant number of times
 *  @warning Do not put multiple repeats in the same line
 */
#define repeat(n)       for(int CONCAT(i,__LINE__) = 0; CONCAT(i,__LINE__) < (n); ++CONCAT(i,__LINE__))

/** The famous lenghtof macro to get the length of a statically defined
 *  array
 */
#define lengthof(x)	(sizeof((x))/sizeof((x)[0]))

#ifdef __cplusplus
}
#endif

#endif

