
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

#include "arch/x86-64/cache.h"
#include <utils.h>
#include <report.h>

int cache_lines_per_set(enum cache_level lv)
{
	int32_t d = -1;
	size_t  i;

	switch(lv) {
	case L1_CACHE:
		return d = get_cpu_info()->l1_data_cache_assoc;
		break;
	case L2_CACHE:
		return d = get_cpu_info()->l2_data_cache_assoc;
		break;
	case L3_CACHE:
		return d = get_cpu_info()->l3_data_cache_assoc;
		break;
	}	

	for(i = 0; i < lengthof(cpuinfo_assoc_field_map); ++i) {
		if(cpuinfo_assoc_field_map[i].d == d) {
			return cpuinfo_assoc_field_map[i].k;
		}
	}

	die("invalid input (lv = %d) in %s which is impossible.",
		lv, __FUNCTION__);
	return (-1);
}

