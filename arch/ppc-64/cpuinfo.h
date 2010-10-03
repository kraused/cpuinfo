
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

#ifndef ARCH_PPC_64_CPUINFO_H_INCLUDED
#define ARCH_PPC_64_CPUINFO_H_INCLUDED 1

#include <config.h>

/** @file cpuinfo
 *  Information about the CPU
 */

#ifndef CPUINFO_H_INCLUDED
#error "do not include arch/ppc-64/cpuinfo.h direct. Include cpuinfo.h instead!"
#endif

#ifndef ON_PPC_64
#error "only for ppc-64 architectures!"
#endif 

#ifdef __cplusplus
extern "C" {
#endif

/** Maximal vendor string length
 */
#define CPUINFO_VENDOR_STRING_LENGTH 12
	
/** Maximal processor name length
 */
#define CPUINFO_PROC_NAME_STRING_LENGTH 48

/** cpu_info: CPU type informations
 */
typedef struct cpu_info
{	/** Estimated cpu frequency in MHz
	 */
	double   est_cpu_freq;

} cpu_info_t;

/** CPU database
 */
extern cpu_info_t cpu_database[];

/** Read the CPU information
 *  @param[in]	info	the cpu info structure
 */
extern void read_cpu_info(cpu_info_t *info);

/** Print the CPU information
 *  @param[in]	info	the cpu info structure
 *  @param[in]	fh	file handler
 */
extern void print_cpu_info(cpu_info_t *info, FILE *fh);

/** Get the number of the cpu in the database
 *  @returns the index in the database and -1 if the cpu is not in the database
 */
extern int find_cpu_in_database();

#ifdef __cplusplus
}
#endif

#endif

