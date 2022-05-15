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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFOHANDLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFOHANDLE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN


struct ffifonode;
struct path;
struct fdirent;
struct fifohandle {
	/* HANDLE:HANDLE_TYPE_FIFOHANDLE */
	WEAK refcnt_t         fu_refcnt;  /* Reference counter */
	REF struct ffifonode *fu_fifo;    /* [1..1][const] The associated fifo. */
	REF struct path      *fu_path;    /* [0..1][const] The path from which `fr_fifo' was opened. */
	REF struct fdirent   *fu_dirent;  /* [0..1][const] The directory entry associated with `fr_fifo' that was used to open the fifo. */
	iomode_t              fu_accmode; /* [const] Original I/O mode with which this fifo user was opened (masked by IO_ACCMODE). */
};

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL fifohandle_destroy)(struct fifohandle *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct fifohandle, fu_refcnt, fifohandle_destroy)

/* Create a reader/writer for the given fifo `self'
 * NOTE: If  applicable,  the  caller  should  fill  in `fu_path'
 *       and/or `fu_dirent' directly after calling this function.
 * @param: iomode: Set of `IO_ACCMODE | IO_NONBLOCK' (other bits are silently ignored)
 * @throw: E_ILLEGAL_IO_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS: [...] */
FUNDEF BLOCKING ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifohandle *FCALL
fifohandle_new(struct ffifonode *__restrict self, iomode_t iomode,
               struct path *access_path, struct fdirent *access_dent)
		THROWS(E_BADALLOC, E_ILLEGAL_IO_OPERATION, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFOHANDLE_H */
