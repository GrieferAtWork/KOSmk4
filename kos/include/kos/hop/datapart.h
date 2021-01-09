/* Copyright (c) 2019-2021 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_DATAPART_H
#define _KOS_HOP_DATAPART_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "datablock.h"
#include "openfd.h"

__DECL_BEGIN

#define HOP_DATAPART_STAT_FEATURE_NONE         0x00000000 /* No special features. */
#define HOP_DATAPART_STAT_FEATURE_ISLOCKED     0x00000001 /* s.a. VM_DATAPART_FLAG_LOCKED. */
#define HOP_DATAPART_STAT_FEATURE_HASCHANGED   0x00000004 /* s.a. VM_DATAPART_FLAG_CHANGED. */
#define HOP_DATAPART_STAT_FEATURE_KEEPRAM      0x00000800 /* s.a. `VM_DATAPART_FLAG_KEEPRAM'. */
#define HOP_DATAPART_STAT_FEATURE_TRKCHNG      0x00001000 /* s.a. `VM_DATAPART_FLAG_TRKCHNG'. */
#define HOP_DATAPART_STAT_FEATURE_COREPRT      0x00004000 /* s.a. `VM_DATAPART_FLAG_COREPRT'. */
#define HOP_DATAPART_STAT_FEATURE_KERNPRT      0x00008000 /* s.a. `VM_DATAPART_FLAG_KERNPRT'. */
#define HOP_DATAPART_STAT_FEATURE_ISANON       0x00010000 /* The datapart is anonymous. */
#define HOP_DATAPART_STAT_FEATURE_HASFUTEXCTRL 0x00020000 /* The datapart has a futex controller. */
#define HOP_DATAPART_STAT_FEATURE_HASFUTEXLIVE 0x00040000 /* The datapart has live futex objects (implies `HOP_DATAPART_STAT_FEATURE_HASFUTEXCTRL'). */
#define HOP_DATAPART_STAT_FEATURE_HASCMAP      0x00100000 /* The datapart has copy-on-write memory mappings. */
#define HOP_DATAPART_STAT_FEATURE_HASSMAP      0x00200000 /* The datapart has shared memory mappings. */
#define HOP_DATAPART_STAT_STATE_ABSENT 0x0000 /* s.a. `VM_DATAPART_STATE_ABSENT' */
#define HOP_DATAPART_STAT_STATE_INCORE 0x0001 /* s.a. `VM_DATAPART_STATE_INCORE' */
#define HOP_DATAPART_STAT_STATE_LOCKED 0x0002 /* s.a. `VM_DATAPART_STATE_LOCKED' */
#define HOP_DATAPART_STAT_STATE_INSWAP 0x0003 /* s.a. `VM_DATAPART_STATE_INSWAP' */
#define HOP_DATAPART_STAT_STATE_VIOPRT 0x0004 /* s.a. `VM_DATAPART_STATE_VIOPRT' */
#define __OFFSET_HOP_DATAPART_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_DATAPART_STAT_FEATURES    4
#define __OFFSET_HOP_DATAPART_STAT_STATE       8
#define __OFFSET_HOP_DATAPART_STAT_MINADDR     16
#define __OFFSET_HOP_DATAPART_STAT_MAXADDR     24
#define __OFFSET_HOP_DATAPART_STAT_MINVPAGE    32
#define __OFFSET_HOP_DATAPART_STAT_MAXVPAGE    40
#define __OFFSET_HOP_DATAPART_STAT_MINDPAGE    48
#define __OFFSET_HOP_DATAPART_STAT_MAXDPAGE    56
#define __SIZEOF_HOP_DATAPART_STAT             64
#ifdef __CC__
struct hop_datapart_stat /*[PREFIX(ds_)]*/ {
	__uint32_t   ds_struct_size;          /* [== sizeof(struct hop_datablock_stat)]
	                                       * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                       * this value is too small or doesn't match any recognized
	                                       * structure version. */
	__uint32_t   ds_features;             /* [OUT] Set of `HOP_DATAPART_STAT_FEATURE_*' */
	__uint32_t   ds_state;                /* [OUT] One of `HOP_DATAPART_STAT_STATE_*' */
	__uint32_t __ds_pad;                  /* ... */
	__uint64_t   ds_minaddr;              /* [OUT] Lowest address within the associated datablock mapped by this part. */
	__uint64_t   ds_maxaddr;              /* [OUT] Greatest address within the associated datablock mapped by this part.
	                                       *       Note that this value may decrease over time, as the data part gets split. */
	__uint64_t   ds_minvpage;             /* [OUT] Lowest virt-page number mapped by this part. */
	__uint64_t   ds_maxvpage;             /* [OUT] Greatest virt-page number mapped by this part (may decrease over time). */
	__uint64_t   ds_mindpage;             /* [OUT] Lowest data-page number mapped by this part. */
	__uint64_t   ds_maxdpage;             /* [OUT] Greatest data-page number mapped by this part (may decrease over time). */
};
#endif /* __CC__ */


/* HANDLE_TYPE_DATAPART */
#define HOP_DATAPART_OPEN_DATABLOCK      0x00150001 /* [struct hop_openfd *result] Open the datablock associated with the given datapart.
                                                     * @return: == result->of_hint */
#define HOP_DATAPART_OPEN_FUTEX          0x00150002 /* [struct hop_datablock_open_futex *result] Return, or create a futex for the given address.
                                                     * @return: == result->dof_openfd.of_hint */
#define HOP_DATAPART_OPEN_FUTEX_EXISTING 0x00150003 /* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address.
                                                     * @return: -ENOENT: No futex exists for the given address
                                                     * @return: -ERANGE: The given address lies outside of the bounds of this datapart
                                                     *                   Note that this can happen arbitrarily since it is possible that
                                                     *                   the datapart is truncated between the time of you accessing it,
                                                     *                   and invoking this command!
                                                     * @return: == result->dof_openfd.of_hint */
#define HOP_DATAPART_STAT                0x00150004 /* [struct hop_datapart_stat *result] Read information about the datapart */
#define HOP_DATAPART_HASCHANGED          0x00150005 /* [struct hop_datablock_haschanged *result] Check for changes within the data part (s.a. `vm_datapart_haschanged()') */
//TODO:#define HOP_DATAPART_SYNC         -- vm_datapart_sync() */
//TODO:#define HOP_DATAPART_SPLIT        -- vm_datapart_split() */

__DECL_END

#endif /* !_KOS_HOP_DATAPART_H */
