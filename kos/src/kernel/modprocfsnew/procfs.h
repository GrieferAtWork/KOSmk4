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
#ifndef GUARD_MODPROCFS_PROCFS_H
#define GUARD_MODPROCFS_PROCFS_H 1

#include <kernel/compiler.h>

/*
 * Procfs API design:
 *
 * - Inode  numbers don't matter; file lookup is entirely
 *   facilitated via custom fdirent opennode() operators,
 *   and fn_ino is set to `0', and mso_stat is defined to
 *   fill in stat INO fields with `skew_kernel_pointer()'
 *   For per-process nodes, INO is filled with the skewed
 *   pointer `self->mf_ops ^ self->TASKPID'.
 * - All singleton procfs objects are statically allocated
 * - Per-process  nodes use the fsdata pointer to directly
 *   store a pointer to the taskpid of the thread, or have
 *   it point to later in the struct where said taskpid is
 *   then stored instead.
 *   As such, there are no  race conditions in regards  to
 *   paths going away and being replaced by some new same-
 *   pid process.
 * - Per-process nodes all have `MFILE_FM_FLEETING' set
 * - Per-process nodes all have `MFILE_FM_ATTRREADONLY' set
 *
 * TODO: Custom access checks  for per-process nodes  (since
 *       we fill in the uid/gid field with `0', access tests
 *       must be altered to compare against the active  cred
 *       of the target thread instead)
 */

DECL_BEGIN

INTDEF struct fsuper_ops const procfs_super_ops;
INTDEF struct fsuper procfs_super;
INTDEF struct ffilesys procfs_filesys;
INTDEF struct fdirnode_ops const procfs_constdir_ops; /* Operators used for `struct constdir' under /proc */

DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_H */
