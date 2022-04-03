/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_NOTIFY_C
#define GUARD_KERNEL_CORE_FILESYS_NOTIFY_C 1
#define __WANT_DNOTIFY_LINK__dnl_rbword

#include <kernel/compiler.h>

#ifdef CONFIG_HAVE_FS_NOTIFY
#include <kernel/fs/notify.h>
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <linux/inotify.h>

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE(name)           dnotify_link_tree_##name
#define RBTREE_T               struct dnotify_link
#define RBTREE_Tkey            struct fdirent const *
#define RBTREE_GETNODE(self)   (self)->dnl_dirnode
#define RBTREE_GETKEY(self)    (self)->dnl_ent
#define RBTREE_REDFIELD        _dnl_rbword
#define RBTREE_REDBIT          1
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* SMP-lock  for filesystem event notify. -- We use a global lock for this because
 * the alternative would be to set-up many smaller locks, each of which would also
 * need to have a  list of lock-ops, which  probably wouldn't actually make  stuff
 * faster since filesystem event notification is usually a brief process. */
#ifndef CONFIG_NO_SMP
PUBLIC struct atomic_lock notify_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */


/* TODO: Everything else */



DECL_END
#endif /* CONFIG_HAVE_FS_NOTIFY */

#endif /* !GUARD_KERNEL_CORE_FILESYS_NOTIFY_C */
