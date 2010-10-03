
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

#ifndef ARCH_X86_64_CYCLE_H_INCLUDED
#define ARCH_X86_64_CYCLE_H_INCLUDED 1

#include <config.h>
#include <cpuinfo.h>

/** @file cycle.h
 *  Implements timing routines used for code evaluation
 *
 *  I'm using ideas here from the cycle.h header in fftw by Matteo Frigo.
 *  @see http://www.fftw.org/cycle.h
 */

#ifndef ON_X86_64
#error "only for x86-64 architectures!"
#endif 

#ifdef __cplusplus
extern "C" {
#endif

/** A cycle counter
 */
typedef uint64_t tick;

/** Read the cycle counter value
 */
static inline tick getticks()
{
	uint32_t x, y;

	__asm__ __volatile__ ("rdtsc" : "=a" (x), "=d" (y));

	return ((tick )x) | (((tick )y) << 32);
}

/** Get the elapsed time between to measured cycles
 *  @param[in]	t1	the cycle counter value measured at a later time
 *  @param[in]	t0	the cycle counter value before the measured instructions
 */
static inline double elapsed(tick t1, tick t0)
{
	return (double )t1 - (double )t0;
}

/** Convert from ticks to microseconds
 *  @param[in]	t	the elapsed time span
 */
static inline double usecs(double t)
{
	return t/get_cpu_info()->est_cpu_freq;
}

#ifdef __cplusplus
}
#endif

#endif

