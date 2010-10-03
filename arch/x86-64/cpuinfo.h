
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

#ifndef ARCH_X86_64_CPUINFO_H_INCLUDED
#define ARCH_X86_64_CPUINFO_H_INCLUDED 1

#include <config.h>

/** @file cpuinfo
 *  Information about the CPU
 */

#ifndef CPUINFO_H_INCLUDED
#error "do not include arch/x86-64/cpuinfo.h direct. Include cpuinfo.h instead!"
#endif

#ifndef ON_X86_64
#error "only for x86-64 architectures!"
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
{
	/** Maximal supported extended standard function */
	uint32_t max_supported_ext_fn;
	/** Vendor string */
	char     vendor[CPUINFO_VENDOR_STRING_LENGTH+1];
	/** Processor family */
	int32_t	 family;
	/** Processor model */
	int32_t	 model;
	/** Processor name */
	char	 name[CPUINFO_PROC_NAME_STRING_LENGTH+1];
	/** L1 cache size in kilobytes (per core) */
	int32_t	 l1_data_cache_size;
	/* L1 cache associativity */
	int32_t	 l1_data_cache_assoc;
	/* L1 cache line size */
	int32_t	 l1_data_cache_line_size;
	/** L2 cache size in kilobytes */
	int32_t  l2_data_cache_size;
	/* L2 cache associativity */
	int32_t	 l2_data_cache_assoc;
	/* L2 cache line size */
	int32_t	 l2_data_cache_line_size;
	/** L3 cache size in kilobytes */
	int32_t  l3_data_cache_size;
	/** L3 cache associativity */
	int32_t	 l3_data_cache_assoc;
	/** L3 cache line size */
	int32_t	 l3_data_cache_line_size;
	/** Estimated cpu frequency in MHz. This one is hard to get because it 
 	 *  might change over time
	 */
	double   est_cpu_freq;
	
} cpu_info_t;

/** CPU database
 */
extern cpu_info_t cpu_database[];

/** Map from the associativity field to a string and to the number of cache lines
 *  per map
 */
static struct { uint8_t d; int k; const char s[19]; } cpuinfo_assoc_field_map[] =
	{
		{ 0x0,   0,            "disabled" },
		{ 0x1,   0,       "direct mapped" },
		{ 0x2,   2,   "2-way associative" },
		{ 0x4,   4,   "4-way associative" },
		{ 0x5,   6,   "6-way associative" }, // My definition ...
		{ 0x6,   8,   "8-way associative" },
		{ 0x7,  12,  "12-way associative" }, // My definition ...
		{ 0x8,  16,  "16-way associative" },
		{ 0x9,  24,  "24-way associative" }, // My definition ...
		{ 0xa,  32,  "32-way associative" },
		{ 0xb,  48,  "48-way associative" },
		{ 0xc,  64,  "64-way associative" },
		{ 0xd,  96,  "96-way associative" },
		{ 0xe, 128, "128-way associative" },
		{ 0xf,   0,   "fully associative" }
	};

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

