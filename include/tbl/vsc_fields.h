/*-
 * Copyright (c) 2006 Verdens Gang AS
 * Copyright (c) 2006-2011 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Definition of all shared memory statistics below.
 *
 * Fields (n, t, l, f, e, d):
 *    n - Name:		Field name, in C-source and stats programs
 *    t - Type:		C-type, uint64_t, unless marked in 'f'
 *    l - Local:	Local counter in worker thread.
 *    f - Format:	Semantics of the value in this field
 *				'a' - Accumulator (deprecated, use 'c')
 *				'b' - Bitmap
 *				'c' - Counter, never decreases.
 *				'g' - Gauge, goes up and down
 *				'i' - Integer (deprecated, use 'g')
 *    e - Explantion:	Short explanation of field (for screen use)
 *    d - Description:	Long explanation of field (for doc use)
 *
 * Please describe Gauge variables as "Number of..." to indicate that
 * this is a snapshot, and Counter variables as "Count of" to indicate
 * accumulative count.
 *
 * -----------------------
 * NB: Cleanup in progress
 * -----------------------
 *
 * Insufficient attention has caused this to become a swamp of conflicting
 * conventions, shorthands and general mumbo-jumbo.  I'm trying to clean
 * it up as I go over the code in other business.
 *
 * Please see the sessmem section for how it should look.
 *
 */

/**********************************************************************/

#ifdef VSC_DO_LCK

VSC_F(creat,			uint64_t, 0, 'a',
    "Created locks",
	""
)
VSC_F(destroy,			uint64_t, 0, 'a',
    "Destroyed locks",
	""
)
VSC_F(locks,			uint64_t, 0, 'a',
    "Lock Operations",
	""
)
VSC_F(colls,			uint64_t, 0, 'a',
    "Collisions",
	""
)

#endif

/**********************************************************************
 * All Stevedores support these counters
 */

#if defined(VSC_DO_SMA) || defined (VSC_DO_SMF)
VSC_F(c_req,			uint64_t, 0, 'a',
    "Allocator requests",
	""
)
VSC_F(c_fail,			uint64_t, 0, 'a',
    "Allocator failures",
	""
)
VSC_F(c_bytes,			uint64_t, 0, 'a',
    "Bytes allocated",
	""
)
VSC_F(c_freed,			uint64_t, 0, 'a',
    "Bytes freed",
	""
)
VSC_F(g_alloc,			uint64_t, 0, 'i',
    "Allocations outstanding",
	""
)
VSC_F(g_bytes,			uint64_t, 0, 'i',
    "Bytes outstanding",
	""
)
VSC_F(g_space,			uint64_t, 0, 'i',
    "Bytes available",
	""
)
#endif


/**********************************************************************/

#ifdef VSC_DO_SMA
/* No SMA specific counters */
#endif

/**********************************************************************/

#ifdef VSC_DO_SMF
VSC_F(g_smf,			uint64_t, 0, 'i',
    "N struct smf",
	""
)
VSC_F(g_smf_frag,		uint64_t, 0, 'i',
    "N small free smf",
	""
)
VSC_F(g_smf_large,		uint64_t, 0, 'i',
    "N large free smf",
	""
)
#endif

/**********************************************************************/

#ifdef VSC_DO_SMP
#define VAMPIRE_NOTE "  Note: Does not include vampire objects"
VSC_F(c_req,			uint64_t, 0, 'c',
    "Allocater requests",
        "Number of chunks allocated from this silo."
        VAMPIRE_NOTE
)
VSC_F(c_fail,			uint64_t, 0, 'c',
    "Allocater failures",
        "Number of failed allocation attempts from this silo."
        VAMPIRE_NOTE
)
VSC_F(c_bytes,			uint64_t, 0, 'c',
    "Bytes allocated",
        "Bytes allocated from this silo."
        VAMPIRE_NOTE
)
VSC_F(c_freed,			uint64_t, 0, 'c',
    "Bytes freed",
        "Bytes freed from this silo."
        VAMPIRE_NOTE
)
VSC_F(g_alloc,			uint64_t, 0, 'g',
    "Allocations outstanding",
        "Outstanding allocations from this silo."
        VAMPIRE_NOTE
)
VSC_F(g_bytes,			uint64_t, 0, 'g',
    "Bytes outstanding",
        "Outstanding bytes from this silo."
        VAMPIRE_NOTE
)
VSC_F(g_free,			uint64_t, 0, 'g',
    "Free space",
        "Free space in silo"
)
VSC_F(g_free_pending,		uint64_t, 0, 'g',
    "Free space pending",
        "Free space from nuked segments, pending release"
)
VSC_F(g_segments,		uint64_t, 0, 'g',
    "In use segments",
        "Number of segments currently in use in the silo."
)
VSC_F(c_segments_nuked,		uint64_t, 0, 'c',
    "Number of nuked segments",
	"Total number of segments nuked to make room"
)
VSC_F(g_vampireobjects,		uint64_t, 0, 'g',
    "Vampire objects",
        "Number of vampire objects in cache with storage in this silo."
)
VSC_F(c_resurrection_fail,	uint64_t, 0, 'c',
    "Failed resurrections",
        "Number of failed resurrections attempts of vampire objects"
)
#undef VAMPIRE_NOTE
#endif

/**********************************************************************/

#ifdef VSC_DO_VBE

VSC_F(vcls,			uint64_t, 0, 'i',
    "VCL references",
	""
)
VSC_F(happy,			uint64_t, 0, 'b',
    "Happy health probes",
	""
)

#endif

/**********************************************************************/
#ifdef VSC_DO_MEMPOOL

VSC_F(live,			uint64_t, 0, 'g',
    "In use",
	""
)
VSC_F(pool,			uint64_t, 0, 'g',
    "In Pool",
	""
)
VSC_F(sz_wanted,		uint64_t, 0, 'g',
    "Size requested",
	""
)
VSC_F(sz_needed,		uint64_t, 0, 'g',
    "Size allocated",
	""
)
VSC_F(allocs,			uint64_t, 0, 'c',
    "Allocations",
	""
)
VSC_F(frees,			uint64_t, 0, 'c',
    "Frees",
	""
)
VSC_F(recycle,			uint64_t, 0, 'c',
    "Recycled from pool",
	""
)
VSC_F(timeout,			uint64_t, 0, 'c',
    "Timed out from pool",
	""
)
VSC_F(toosmall,			uint64_t, 0, 'c',
    "Too small to recycle",
	""
)
VSC_F(surplus,			uint64_t, 0, 'c',
    "Too many for pool",
	""
)
VSC_F(randry,			uint64_t, 0, 'c',
    "Pool ran dry",
	""
)

#endif
