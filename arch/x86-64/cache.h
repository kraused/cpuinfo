
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

#ifndef ARCH_X86_64_CACHE_H_INCLUDED
#define ARCH_X86_64_CACHE_H_INCLUDED 1

#include <config.h>
#include <cpuinfo.h>

/** @file cache.h functions to control the cache system
 */

#ifdef __cplusplus
extern "C" {
#endif

/** cache levels
 */
enum cache_level
{
	L1_CACHE = 0,	/**< first  level cache */
	L2_CACHE = 1,	/**< second level cache */
	L3_CACHE = 2	/**< third  level cache */
};

/** Get cache size in bytes
 *  @param[in]	lv	the cache level
 */
static inline size_t cache_size(enum cache_level lv)
{
	switch(lv) {
	case L1_CACHE:
		return get_cpu_info()->l1_data_cache_size;
		break;
	case L2_CACHE:
		return get_cpu_info()->l2_data_cache_size;
		break;
	case L3_CACHE:
		return get_cpu_info()->l3_data_cache_size;
		break;
	}

	return 0;
}

/** Get cache line size
 *  @param[in]	lv	the cache level
 */
static inline size_t cache_line_size(enum cache_level lv)
{
	switch(lv) {
	case L1_CACHE:
		return get_cpu_info()->l1_data_cache_line_size;
		break;
	case L2_CACHE:
		return get_cpu_info()->l2_data_cache_line_size;
		break;
	case L3_CACHE:
		return get_cpu_info()->l3_data_cache_line_size;
		break;
	}

	return 0;
}

/** Number of lines k per set in a k-way set associatie cache
 *  @param[in]	lv	the cache level
 */
extern int cache_lines_per_set(enum cache_level lv);

#ifdef __cplusplus
}
#endif

#endif

