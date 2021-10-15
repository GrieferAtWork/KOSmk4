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
#ifndef GUARD_KERNEL_INCLUDE_FS_FILE_H
#define GUARD_KERNEL_INCLUDE_FS_FILE_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/filehandle.h>
#else /* CONFIG_USE_NEW_FS */
#include <kernel/types.h>
#include <sched/atomic64.h>

#include <hybrid/sync/atomic-rwlock.h>

DECL_BEGIN

#ifdef __CC__

struct inode;
struct path;
struct directory_node;
struct fdirent;

struct filehandle {
	/* [HANDLE_TYPE(HANDLE_TYPE_FILEHANDLE)] */
	WEAK refcnt_t               f_refcnt; /* File reference counter. */
	REF struct inode           *f_node;   /* [1..1][const] The opened file INode. */
	REF struct path            *f_path;   /* [0..1][const] The path from which `f_node' was opened. */
	REF struct fdirent *f_dirent; /* [0..1][const] The directory entry associated with `f_node' that was used to open the file. */
	WEAK atomic64_t             f_offset; /* File I/O read/write position. */
	struct atomic_rwlock        f_curlck; /* Lock for accessing the current directory entry & its index. */
	pos_t                       f_curidx; /* [lock(f_curlck)][valid_if(INODE_ISDIR(f_node))]
	                                       * The index of the directory entry currently selected by `f_curent'. */
	REF struct fdirent *f_curent; /* [lock(f_curlck)][valid_if(INODE_ISDIR(f_node))][0..1]
	                                       * The  f_curidx-2'th  directory of  `f_node',  or NULL. */
};

/* Destroy the given file object. */
FUNDEF NOBLOCK void NOTHROW(KCALL filehandle_destroy)(struct filehandle *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct filehandle, f_refcnt, filehandle_destroy)


/* A special  kind  of  file  stream  that  is  intended  to  be  used
 * for  enumerating  directories   that  contain   data  which   could
 * randomly change at any time, independent of the filesystem. (/proc)
 * This type of file makes use of the  `it_directory.d_oneshot.o_enum'
 * facility exposed by the `struct inode_type' structure.
 *  - This type of directory stream is designed to collect _all_
 *    entries  that will  ever show  up _once_  during the first
 *   `readdir()' operation. */
struct oneshot_directory_buffer;
struct dirhandle {
	/* [HANDLE_TYPE(HANDLE_TYPE_DIRHANDLE)] */
	WEAK refcnt_t                    d_refcnt; /* File reference counter. */
	REF struct directory_node       *d_node;   /* [1..1] The opened directory INode. */
	REF struct path                 *d_path;   /* [0..1] The path from which `d_node' was opened. */
	REF struct fdirent              *d_dirent; /* [0..1] The directory entry associated with `d_node' that was used to open the file. */
	WEAK atomic64_t                  d_offset; /* [lock(d_node)] File I/O read/write position. */
	struct atomic_rwlock             d_curlck; /* Lock for accessing the current directory entry & its index. */
	pos_t                            d_curidx; /* [lock(d_curlck)] The index of the directory entry currently selected by `d_curent'. */
	struct dirent                   *d_curent; /* [0..1][lock(d_curlck)] The current directory entry. */
	struct oneshot_directory_buffer *d_curbuf; /* [0..1][lock(d_curlck)] The current buffer block. */
	struct oneshot_directory_buffer *d_buf;    /* [0..1][lock(WRITE_ONCE)][owned] Directory contents buffer. */
};

/* Destroy the given oneshot-directory-file object. */
FUNDEF NOBLOCK void NOTHROW(KCALL dirhandle_destroy)(struct dirhandle *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct dirhandle, d_refcnt, dirhandle_destroy)



#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_FS_FILE_H */
