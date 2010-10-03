
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
#include <cycle.h>
#include <sleep.h>

/** List of known cpus 
 */
cpu_info_t cpu_database[] = 
{
	{
		3192.0000
	}
};

/** Estimate the cpu frequency
 */
void estimate_cpu_frequency(cpu_info_t *info)
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

	estimate_cpu_frequency	 (info);
}

void print_cpu_info(cpu_info_t *info, FILE *fh)
{
	fprintf(fh, " estimated cpu frequency                 : %.4f\n",
			info->est_cpu_freq);
}

int find_cpu_in_database()
{
	/* Only Cell supported */
	return 0;
}

