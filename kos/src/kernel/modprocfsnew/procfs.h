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

#include <kernel/fs/dirent.h>
#include <kernel/fs/printnode.h>
#include <kernel/types.h>

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
 * - Per-process nodes all have `MFILE_FN_FLEETING' set
 * - Per-process nodes all have `MFILE_FN_ATTRREADONLY' set
 *
 * TODO: Custom access checks  for per-process nodes  (since
 *       we fill in the uid/gid field with `0', access tests
 *       must be altered to compare against the active  cred
 *       of the target thread instead)
 */

DECL_BEGIN

#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
typedef __pformatgetc pformatgetc;
typedef __pformatungetc pformatungetc;
#endif /* !__pformatprinter_defined */


struct procfs_regfile
#ifndef __WANT_FS_INLINE_STRUCTURES
    : printnode                /* Underlying print file */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct printnode prf_node; /* Underlying print file */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	/* [1..1] Print callback. */
	void (KCALL *prf_print)(pformatprinter printer, void *arg, size_t offset_hint);
	/* [0..1] Write callback. (when NULL, file is read-only) */
	void (KCALL *prf_write)(USER CHECKED void const *buf, size_t bufsize);
};

struct procfs_txtfile
#ifndef __WANT_FS_INLINE_STRUCTURES
    : printnode                /* Underlying print file */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct printnode ptf_node; /* Underlying print file */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	char const *ptf_string; /* [1..1][const] The string that gets printed. */
};


/************************************************************************/
/* Root/static types                                                    */
/************************************************************************/
INTDEF struct fsuper procfs_super;
INTDEF struct ffilesys procfs_filesys;
INTDEF struct fsuper_ops const procfs_super_ops;      /* Operators for `procfs_super' */
INTDEF struct printnode_ops const procfs_regfile_ops; /* Operators for `struct procfs_regfile' */
INTDEF struct printnode_ops const procfs_txtfile_ops; /* Operators for `struct procfs_txtfile' */


/************************************************************************/
/* Per-process types                                                    */
/************************************************************************/
struct taskpid;
struct procfs_perproc_root_dirent {
	/* Directory entry for the PID number of a /proc/PID directory. */
	REF struct taskpid *pprd_pid; /* [1..1][const] PID of the thread */
	struct fdirent      pprd_ent; /* Underlying directory entry. */
};
#define fdirent_asperprocroot(self) COMPILER_CONTAINER_OF(self, struct procfs_perproc_root_dirent, pprd_ent)


/* Operators for `procfs_perproc_root_dirent' */
INTDEF struct fdirent_ops const procfs_perproc_root_dirent_ops;

/* Operators for `/proc/[pid]/'
 * NOTE: For this directory, `fn_fsdata' is a `REF struct taskpid *' [1..1] */
INTDEF struct fdirnode_ops const procfs_perproc_root_ops;

/* Permissions operators for per-process files. */
INTDEF struct fnode_perm_ops const procfs_perproc_v_perm_ops;

/* Calculate+return the INO of a given taskpid-pointer and INode operators table.
 * @param: context_object_ptr: Pointer an unique object  with a unique address  that
 *                             identifies the current context (for per-thread files,
 *                             this is  `struct taskpid';  for  fd-files,  it's  the
 *                             handle data pointer, etc...)
 */
#define procfs_perproc_ino(context_object_ptr, node_ops)         \
	(ino_t)((uintptr_t)skew_kernel_pointer(context_object_ptr) ^ \
	        (uintptr_t)skew_kernel_pointer(node_ops))
/************************************************************************/





/************************************************************************/
/* Helpers for printing/parsing user-space values.                      */
/************************************************************************/

/* Print a string "0\n" or "1\n" depending on `value' */
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintBool(pformatprinter printer, void *arg, bool value);
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintU32(pformatprinter printer, void *arg, u32 value);
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintU64(pformatprinter printer, void *arg, u64 value);

/* Parse  a given user-space buffer from being  a string `0' or `1', which
 * may optionally be surrounded by space characters that are automatically
 * stripped prior to being parsed.
 * If the buffer  contains anything other  than `[SPC]0|1[SPC]', then  a
 * `E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER'
 * exception is thrown.
 * If the buffer has an incorrect length, then a `E_BUFFER_TOO_SMALL'
 * exception is thrown instead. */
INTDEF NONNULL((1)) bool FCALL
ProcFS_ParseBool(USER CHECKED void const *buf, size_t bufsize)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);
INTDEF NONNULL((1)) u32 FCALL
ProcFS_ParseU32(USER CHECKED void const *buf, size_t bufsize, u32 minval DFL(0), u32 maxval DFL((u32)-1))
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);
INTDEF NONNULL((1)) u64 FCALL
ProcFS_ParseU64(USER CHECKED void const *buf, size_t bufsize, u64 minval DFL(0), u64 maxval DFL((u64)-1))
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);

#if __SIZEOF_SIZE_T__ >= 8
#define ProcFS_ParseSize ProcFS_ParseU64
#define ProcFS_PrintSize ProcFS_PrintU64
#else /* __SIZEOF_SIZE_T__ >= 8 */
#define ProcFS_ParseSize ProcFS_ParseU32
#define ProcFS_PrintSize ProcFS_PrintU32
#endif /* __SIZEOF_SIZE_T__ < 8 */

#if __SIZEOF_INT__ >= 8
#define ProcFS_ParseUInt ProcFS_ParseU64
#define ProcFS_PrintUInt ProcFS_PrintU64
#else /* __SIZEOF_INT__ >= 8 */
#define ProcFS_ParseUInt ProcFS_ParseU32
#define ProcFS_PrintUInt ProcFS_PrintU32
#endif /* __SIZEOF_INT__ < 8 */

#if __SIZEOF_PID_T__ >= 8
#define ProcFS_ParseUPid ProcFS_ParseU64
#define ProcFS_PrintUPid ProcFS_PrintU64
#else /* __SIZEOF_PID_T__ >= 8 */
#define ProcFS_ParseUPid ProcFS_ParseU32
#define ProcFS_PrintUPid ProcFS_PrintU32
#endif /* __SIZEOF_PID_T__ < 8 */


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_H */
