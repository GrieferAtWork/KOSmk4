/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBDL_TLS_H
#define _LIBDL_TLS_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/types.h>

#ifdef __CC__
DECL_BEGIN

struct dlmodule;
struct dltls_extension {
	/* Tree for mapping TLS extensions data tables to modules.
	 * NOTE: These extension tables are allocated lazily! */
	LLRBTREE_NODE(dltls_extension) te_tree;     /* [lock(:ts_exlock)] R/B-tree node. */
	union {
		struct dlmodule           *te_module;   /* [0..1][lock(:ts_exlock)] The module itself.
		                                         * The  least significant bit  of this is used
		                                         * to indicate if this leaf is red of black! */
		uintptr_t                  te_redblack; /* Red/black status bit at bit#0 */
	};
	byte_t                        *te_data;     /* [1..1][const] Pointer to the base of TLS data. */
	/* The actual extension data goes here. (with proper alignment, and pointed-to by `te_data') */
};
#define DTLS_EXTENSION_REDBIT          1
#define dtls_extension_getmodule(self) ((struct dlmodule *)((self)->te_redblack & ~DTLS_EXTENSION_REDBIT))
#define dtls_extension_isred(self)     ((self)->te_redblack & DTLS_EXTENSION_REDBIT)


/* This is the actual structure that the TLS register (e.g. `%fs.base' /
 * `%gs.base'  on i386 and  x86_64) points to. It  is also the structure
 * returned by `dltlsallocseg(3D)'! */
struct dltls_segment {
	/* Static TLS data goes here (aka. at negative offsets from `ts_self') */
	struct dltls_segment          *ts_self;    /* [1..1][const][== self] Self-pointer
	                                            * At offset 0; mandaged by ELF, and a good idea in general. */
	LIST_ENTRY(dltls_segment)      ts_threads; /* [lock(dlglobals::dg_tls_segment_lock)] Thread entry within `dlglobals::dg_tls_segment_list' */
	struct atomic_rwlock           ts_exlock;  /* Lock for `ts_extree' */
	LLRBTREE_ROOT(dltls_extension) ts_extree;  /* [0..1][lock(ts_exlock)] TLS extension table. */
};

/* Helper macros for `struct dltls_segment::ts_exlock' */
#define dltls_segment_ex_mustreap(self)   0
#define dltls_segment_ex_reap(self)       (void)0
#define _dltls_segment_ex_reap(self)      (void)0
#define dltls_segment_ex_write(self)      atomic_rwlock_write(&(self)->ts_exlock)
#define dltls_segment_ex_trywrite(self)   atomic_rwlock_trywrite(&(self)->ts_exlock)
#define dltls_segment_ex_endwrite(self)   (atomic_rwlock_endwrite(&(self)->ts_exlock), dltls_segment_ex_reap(self))
#define _dltls_segment_ex_endwrite(self)  atomic_rwlock_endwrite(&(self)->ts_exlock)
#define dltls_segment_ex_read(self)       atomic_rwlock_read(&(self)->ts_exlock)
#define dltls_segment_ex_tryread(self)    atomic_rwlock_tryread(&(self)->ts_exlock)
#define _dltls_segment_ex_endread(self)   atomic_rwlock_endread(&(self)->ts_exlock)
#define dltls_segment_ex_endread(self)    (void)(atomic_rwlock_endread(&(self)->ts_exlock) && (dltls_segment_ex_reap(self), 0))
#define _dltls_segment_ex_end(self)       atomic_rwlock_end(&(self)->ts_exlock)
#define dltls_segment_ex_end(self)        (void)(atomic_rwlock_end(&(self)->ts_exlock) && (dltls_segment_ex_reap(self), 0))
#define dltls_segment_ex_upgrade(self)    atomic_rwlock_upgrade(&(self)->ts_exlock)
#define dltls_segment_ex_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->ts_exlock)
#define dltls_segment_ex_downgrade(self)  atomic_rwlock_downgrade(&(self)->ts_exlock)
#define dltls_segment_ex_reading(self)    atomic_rwlock_reading(&(self)->ts_exlock)
#define dltls_segment_ex_writing(self)    atomic_rwlock_writing(&(self)->ts_exlock)
#define dltls_segment_ex_canread(self)    atomic_rwlock_canread(&(self)->ts_exlock)
#define dltls_segment_ex_canwrite(self)   atomic_rwlock_canwrite(&(self)->ts_exlock)
#define dltls_segment_ex_waitread(self)   atomic_rwlock_waitread(&(self)->ts_exlock)
#define dltls_segment_ex_waitwrite(self)  atomic_rwlock_waitwrite(&(self)->ts_exlock)

DECL_END
#endif /* __CC__ */

#endif /* !_LIBDL_TLS_H */
