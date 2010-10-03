
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

#ifndef ARCH_X86_64_CPUID_H_INCLUDED
#define ARCH_X86_64_CPUID_H_INCLUDED 1

#include "config.h"

/** @file cpuid
 *  Wrapper around the cpuid assembler command
 */

#ifndef ON_X86_64
#error "only for x86-64 architectures!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** cpuid extended level
 *  typedef uin64_t cpuid_ext_id
 */
#define CPUID_VENDOR	           (0x00000000)
#define CPUID_FAMILY_MODEL         (0x00000001)
#define CPUID_PROC_CONFIG	   (0x00000002)
#define CPUID_EXTENDED_MAX         (0x80000000)
#define CPUID_EXTENDED_ID	   (0x80000001)
#define CPUID_EXTENDED_PROC_NAME_1 (0x80000002)
#define CPUID_EXTENDED_PROC_NAME_2 (0x80000003)
#define CPUID_EXTENDED_PROC_NAME_3 (0x80000004)
#define CPUID_EXTENDED_TLB_L1      (0x80000005)
#define CPUID_EXTENDED_TLB_L2_L3   (0x80000006)
	
/** Get the CPU id info
 *  @param[in]	val	input value for eax
 *  @param[out]	eax	register value
 *  @param[out]	ebx	register value	
 *  @param[out]	ecx	register value
 *  @param[out]	edx	register value
 */
static inline void cpuid(uint64_t val, 
			 uint32_t *eax, 
			 uint32_t *ebx, 
			 uint32_t *ecx, 
			 uint32_t *edx)
{
	__asm__ __volatile__ ("cpuid" : "=a" (*eax), "=b" (*ebx), 
					"=c" (*ecx), "=d" (*edx) : "a" (val) );
}

#ifdef __cplusplus
}
#endif

#endif

