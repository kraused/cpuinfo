
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

#include <cpuinfo.h>
#include "arch/x86-64/cpuid.h"
#include <utils.h>
#include <memory.h>
#include <cycle.h>
#include <sleep.h>

/** List of known cpus 
 */
cpu_info_t cpu_database[] = 
{
	/*
	{
		0x80000008, 
		"GenuineIntel",
		6,
		26,
		"Intel(R) Xeon(R) CPU           E5520  @ 2.27GHz",
		32,
		0x6,
		64,
		256,
		0x6,
		64,
		8192,
		0x8,
		64,
		2260.360
	},
	{
		0x80000008, 
		"GenuineIntel",
		6,
		23,
		"Intel(R) Xeon(R) CPU           X5260  @ 3.33GHz",
		32,
		0x6,
		64,
		6144,
		0x8,
		64,
		0,
		0x8,
		64,
		3325.006
	},
	{
		0x8000001a,
		"AuthenticAMD",
		16,
		2,
		"Quad-Core AMD Opteron(tm) Processor 2344 HE",
		64,
		0x2,
		64,
		512,
		0x8,
		64,
		2048,
		0x8,
		64,
		1700.123
	},
	{
		0x8000001b,
		"AuthenticAMD",
		16,
		4,
		"Quad-Core AMD Opteron(tm) Processor 2384",
		64,
		0x2,
		64,
		512,
		0x8,
		64,
		6144,
		0x8,
		64,
		2700.098
	}
	*/
};

/** Read the maximal supported extended function number
 */
static void read_max_supported_ext_fn(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	
	cpuid(CPUID_EXTENDED_MAX, &eax, &ebx, &ecx, &edx);
	
	info->max_supported_ext_fn = eax;
}

/** Read the vendor string
 */
static void read_vendor_string(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	char* reg[] =  { ((char *)&ebx), 
			 ((char *)&edx), 
		         ((char *)&ecx) };
	int i;
	
	cpuid(CPUID_VENDOR, &eax, &ebx, &ecx, &edx);
	
	for(i = 0; i < CPUINFO_VENDOR_STRING_LENGTH; ++i) {
		info->vendor[i] = reg[i/4][i%4];
	}
	
	info->vendor[CPUINFO_VENDOR_STRING_LENGTH] = 0;	
}

/** Read the processor family
 */
static void read_cpu_family(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	
	cpuid(CPUID_FAMILY_MODEL, &eax, &ebx, &ecx, &edx);
	
	info->family = ((0xff00000 & eax) >> 20) + ((0xf00 & eax) >> 8);
}

/** Read the processor model
 */
static void read_cpu_model(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	
	cpuid(CPUID_FAMILY_MODEL, &eax, &ebx, &ecx, &edx);
	
	info->model  = ((0x00f0000 & eax) >> 12) | ((0x0f0 & eax) >> 4);
}

/** Read the processor name
 */
static void read_cpu_name(cpu_info_t *info)
{
	uint32_t eax1, eax2, eax3,
		 ebx1, ebx2, ebx3, 
		 ecx1, ecx2, ecx3,
		 edx1, edx2, edx3;
	char* reg[] =  { ((char *)&eax1), 
			 ((char *)&ebx1), 
		         ((char *)&ecx1), 
		         ((char *)&edx1),
			 ((char *)&eax2), 
			 ((char *)&ebx2), 
		         ((char *)&ecx2), 
		         ((char *)&edx2),
			 ((char *)&eax3), 
			 ((char *)&ebx3), 
		         ((char *)&ecx3), 
		         ((char *)&edx3) };
	int i;

	cpuid(CPUID_EXTENDED_PROC_NAME_1, &eax1, &ebx1, &ecx1, &edx1);
	cpuid(CPUID_EXTENDED_PROC_NAME_2, &eax2, &ebx2, &ecx2, &edx2);
	cpuid(CPUID_EXTENDED_PROC_NAME_3, &eax3, &ebx3, &ecx3, &edx3);

	for(i = 0; i < CPUINFO_PROC_NAME_STRING_LENGTH; ++i) {
		info->name[i] = reg[i/4][i%4];
	}	

	info->name[CPUINFO_PROC_NAME_STRING_LENGTH] = 0;		
}

/** Translate the cache associativity descriptor to a string
 */
static const char *translate_cache_assoc(int32_t descr)
{
	size_t i;

	for(i = 0; i < lengthof(cpuinfo_assoc_field_map); ++i) {
		if(cpuinfo_assoc_field_map[i].d == descr) {
			return cpuinfo_assoc_field_map[i].s;
		}
	}

	return "encoding reserved";
}

/** Read the L1 data cache info
 */
static void read_l1_data_cache_info(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	size_t   i, j;	

	cpuid(CPUID_EXTENDED_TLB_L1, &eax, &ebx, &ecx, &edx);

	info->l1_data_cache_size      = ((0xff000000) & ecx) >> 24;
	info->l1_data_cache_assoc     = ((0x00ff0000) & ecx) >> 16;
	info->l1_data_cache_line_size = ((0x000000ff) & ecx);

	/* Intel CPUs */
	cpuid(CPUID_PROC_CONFIG, &eax, &ebx, &ecx, &edx);

	uint8_t ds[] = { ((uint8_t *)&eax)[1],
		      	 ((uint8_t *)&eax)[2],
		     	 ((uint8_t *)&eax)[3],
		     	 ((uint8_t *)&ebx)[0],
		     	 ((uint8_t *)&ebx)[1],
		     	 ((uint8_t *)&ebx)[2],
		      	 ((uint8_t *)&ebx)[3],
		      	 ((uint8_t *)&ecx)[0],
		      	 ((uint8_t *)&ecx)[1],
		      	 ((uint8_t *)&ecx)[2],
		      	 ((uint8_t *)&ecx)[3],
		      	 ((uint8_t *)&edx)[0],
		      	 ((uint8_t *)&edx)[1],
		      	 ((uint8_t *)&edx)[2],
		      	 ((uint8_t *)&edx)[3] };

	/** @see http://www.intel.com/assets/pdf/appnote/241618.pdf */
	struct { uint8_t d; int32_t sz; uint8_t assoc; int32_t lsz; } map[] =
		{
			{ 0x0a,  8, 0x4, 32 },
			{ 0x0c, 16, 0x4, 32 },
			{ 0x0d, 16, 0x4, 64 },
			{ 0x2c, 32, 0x6, 64 },
			{ 0x60, 16, 0x6, 64 },
			{ 0x66,  8, 0x4, 64 },
			{ 0x67, 16, 0x4, 64 },
			{ 0x68, 32, 0x4, 64 } 
		};

	for(i = 0; i < lengthof(ds); ++i) {
		for(j = 0; j < lengthof(map); ++j) {
			if(ds[i] == map[j].d) {
				info->l1_data_cache_size      = map[j].sz;
				info->l1_data_cache_assoc     = map[j].assoc;
				info->l1_data_cache_line_size = map[j].lsz;
			}
		}
	}
}

/** Read the L2 data cache size
 */
static void read_l2_data_cache_info(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	
	cpuid(CPUID_EXTENDED_TLB_L2_L3, &eax, &ebx, &ecx, &edx);

	info->l2_data_cache_size      = ((0xffff0000) & ecx) >> 16;
	info->l2_data_cache_assoc     = ((0x0000f000) & ecx) >> 12;
	info->l2_data_cache_line_size = ((0x000000ff) & ecx);
}

/** Read the L3 data cache size
 */
static void read_l3_data_cache_info(cpu_info_t *info)
{
	uint32_t eax, ebx, ecx, edx;
	size_t   i, j;	

	cpuid(CPUID_EXTENDED_TLB_L2_L3, &eax, &ebx, &ecx, &edx);

	info->l3_data_cache_size      = (((0xfffc0000) & edx) >> 18 )*512;
	info->l3_data_cache_assoc     = ((0x0000f000) & ecx) >> 12;
	info->l3_data_cache_line_size = ((0x000000ff) & ecx);

	/* Intel CPUs */
	cpuid(CPUID_PROC_CONFIG, &eax, &ebx, &ecx, &edx);

	uint8_t ds[] = { ((uint8_t *)&eax)[1],
		      	 ((uint8_t *)&eax)[2],
		      	 ((uint8_t *)&eax)[3],
		     	 ((uint8_t *)&ebx)[0],
		      	 ((uint8_t *)&ebx)[1],
		      	 ((uint8_t *)&ebx)[2],
		      	 ((uint8_t *)&ebx)[3],
		      	 ((uint8_t *)&ecx)[0],
		      	 ((uint8_t *)&ecx)[1],
		      	 ((uint8_t *)&ecx)[2],
		      	 ((uint8_t *)&ecx)[3],
		      	 ((uint8_t *)&edx)[0],
		      	 ((uint8_t *)&edx)[1],
		      	 ((uint8_t *)&edx)[2],
		      	 ((uint8_t *)&edx)[3] };

	/** @see http://www.intel.com/assets/pdf/appnote/241618.pdf */
	struct { uint8_t d; uint32_t sz; uint8_t assoc; int32_t lsz; } map[] =
		{
			{ 0xd0,           512, 0x4, 64 },
			{ 0xd1,  1*1024      , 0x4, 64 },
			{ 0xd2,  2*1024      , 0x4, 64 },
			{ 0xd6,  1*1024      , 0x6, 64 },
			{ 0xd7,  2*1024      , 0x6, 64 },
			{ 0xd8,  2*1024      , 0x6, 64 },
			{ 0xdc,  1*1024 + 512, 0x7, 64 },
			{ 0xdd,  3*1024      , 0x7, 64 },
			{ 0xde,  6*1024      , 0x7, 64 },
			{ 0xe2,  2*1024      , 0x8, 64 },
			{ 0xe3,  4*1024      , 0x8, 64 },
			{ 0xe4,  8*1024      , 0x8, 64 },
			{ 0xea, 12*1024      , 0x9, 64 },
			{ 0xeb, 18*1024      , 0x9, 64 },
			{ 0xec, 24*1024      , 0x9, 64 },
			{ 0x22,           512, 0x4, 64 },
			{ 0x23,  1*1024      , 0x6, 64 },
			{ 0x25,  2*1024      , 0x6, 64 },
			{ 0x29,  4*1024      , 0x6, 64 },
			{ 0x46,  4*1024      , 0x4, 64 },
			{ 0x47,  8*1024      , 0x6, 64 },
			{ 0x49,  4*1024      , 0x8, 64 },
			{ 0x4a,  6*1024	     , 0x7, 64 },
			{ 0x4b,  8*1024	     , 0x8, 64 },
			{ 0x4c, 12*1024	     , 0x7, 64 },
			{ 0x4d, 16*1024	     , 0x8, 64 }
		};

	for(i = 0; i < lengthof(ds); ++i) {
		for(j = 0; j < lengthof(map); ++j) {
			if(ds[i] == map[j].d) {
				info->l3_data_cache_size      = map[j].sz;
				info->l3_data_cache_assoc     = map[j].assoc;
				info->l3_data_cache_line_size = map[j].lsz;
			}
		}
	}
}

/** Estimate the cpu frequency
 */
static void estimate_cpu_frequency(cpu_info_t *info)
{
/* TODO Parse /proc/cpuinfo */
/* #ifdef LINUX
#else */
	tick t1 = getticks();
	sleep(10);
	tick t2 = getticks();

	info->est_cpu_freq = elapsed(t2,t1)/(10*1e6);
/* #endif */
}

void read_cpu_info(cpu_info_t *info)
{
	memset(info, 0x0, sizeof(*info));

	read_max_supported_ext_fn(info);

	if(info->max_supported_ext_fn <= 0x80000006) {
		exit(1); // error
	}

	read_vendor_string	 (info);
	read_cpu_family          (info);
	read_cpu_model           (info);
	read_cpu_name		 (info);
	read_l1_data_cache_info  (info);
	read_l2_data_cache_info  (info);
	read_l3_data_cache_info  (info);
	estimate_cpu_frequency	 (info);
}

/** Faster version of read_cpu_info which ommits some entries
 */
static void read_cpu_info_fast(cpu_info_t *info)
{
	read_vendor_string	 (info);
	read_cpu_family          (info);
	read_cpu_model           (info);
}

void print_cpu_info(cpu_info_t *info, FILE *fh)
{
	fprintf(fh, " max supported extension function number : 0x%x\n",
			info->max_supported_ext_fn);
	fprintf(fh, " vendor Id                               : %s\n",
			info->vendor);
	fprintf(fh, " cpu family                              : %d\n",
			info->family);
	fprintf(fh, " cpu model                               : %d\n",
			info->model);
	fprintf(fh, " model name                              : %s\n",
			info->name);
	fprintf(fh, " L1 data cache size                      : %d KB\n",
			info->l1_data_cache_size);
	fprintf(fh, " L1 data cache associativity             : %s (0x%x)\n",
			translate_cache_assoc(info->l1_data_cache_assoc),
			info->l1_data_cache_assoc);
	fprintf(fh, " L1 data cache line size                 : %d B\n",
			info->l1_data_cache_line_size);
	fprintf(fh, " L2 data cache size                      : %d KB\n",
			info->l2_data_cache_size);
	fprintf(fh, " L2 data cache associativity             : %s (0x%x)\n",
			translate_cache_assoc(info->l2_data_cache_assoc),
			info->l2_data_cache_assoc);
	fprintf(fh, " L2 data cache line size                 : %d B\n",
			info->l2_data_cache_line_size);
	fprintf(fh, " L3 data cache size                      : %d KB\n",
			info->l3_data_cache_size);
	fprintf(fh, " L3 data cache associativity             : %s (0x%x)\n",
			translate_cache_assoc(info->l3_data_cache_assoc),
			info->l3_data_cache_assoc);
	fprintf(fh, " L3 data cache line size                 : %d B\n",
			info->l3_data_cache_line_size);
	fprintf(fh, " estimated cpu frequency                 : %.4f\n",
			info->est_cpu_freq);
}

int find_cpu_in_database()
{
	cpu_info_t info;
	size_t	   i;

	if(0 == lengthof(cpu_database))
		return (-1);

	read_cpu_info_fast(&info);	

	for(i = 0; i < lengthof(cpu_database)-1; ++i) {
		if(cpu_database[i].family == info.family and
		   cpu_database[i].model  == info.model) {
			return i;
		}
	}

	return (-1);
}

