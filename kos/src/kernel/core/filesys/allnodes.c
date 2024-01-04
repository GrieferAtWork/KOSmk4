/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_ALLNODES_C
#define GUARD_KERNEL_CORE_FILESYS_ALLNODES_C 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/ramfs.h>

DECL_BEGIN

/************************************************************************/
/* List of all file-nodes (excluding superblock root nodes)             */
/************************************************************************/

/* [0..n][lock(fallnodes_list)] List of all file nodes */

REF_IF([*]._fnode_file_ mf_flags & MFILE_FN_GLOBAL_REF)
PUBLIC struct fnode_list fallnodes_list = LIST_HEAD_INITIALIZER(fallnodes_list);

/* Lock for `fallnodes_list' */
PUBLIC struct atomic_lock fallnodes_lock = ATOMIC_LOCK_INIT;

/* Lock operations for `fallnodes_list' */
PUBLIC struct lockop_slist fallnodes_lockops = SLIST_HEAD_INITIALIZER(fallnodes_lockops);




/************************************************************************/
/* List of all super blocks                                             */
/************************************************************************/

/* [0..n][lock(fallsuper_list)] List of all super blocks */
REF_IF([*].fs_root._fdirnode_node_ _fnode_file_ mf_flags & MFILE_FN_GLOBAL_REF)
PUBLIC struct fsuper_list fallsuper_list = { &devfs };

/* Lock for `fallsuper_list' */
PUBLIC struct atomic_lock fallsuper_lock = ATOMIC_LOCK_INIT;

/* Lock operations for `fallsuper_list' */
PUBLIC struct lockop_slist fallsuper_lockops = SLIST_HEAD_INITIALIZER(fallsuper_lockops);



/************************************************************************/
/* List of all super blocks with modified nodes (for `sync(2)')         */
/************************************************************************/

/* [0..n][lock(fchangedsuper_list)] List of all changed super blocks */
PUBLIC struct REF fsuper_list fchangedsuper_list = LIST_HEAD_INITIALIZER(fchangedsuper_list);

/* Lock for `fchangedsuper_list' */
PUBLIC struct atomic_lock fchangedsuper_lock = ATOMIC_LOCK_INIT;

/* Lock operations for `fchangedsuper_list' */
PUBLIC struct lockop_slist fchangedsuper_lockops = SLIST_HEAD_INITIALIZER(fchangedsuper_lockops);


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_ALLNODES_C */
