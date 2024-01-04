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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PIPE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PIPE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <libbuffer/ringbuffer.h>

#ifdef __CC__
DECL_BEGIN

struct pipe {
	/* HANDLE:HANDLE_TYPE_PIPE */
	WEAK refcnt_t     p_refcnt; /* Reference counter */
	struct ringbuffer p_buffer; /* The pipe's buffer. */
	WEAK refcnt_t     p_rdcnt;  /* Number of reader objects (when this hits 0, the ringbuffer is closed) */
	WEAK refcnt_t     p_wrcnt;  /* Number of writer objects (when this hits 0, the ringbuffer is closed) */
};
FUNDEF NOBLOCK void NOTHROW(KCALL pipe_destroy)(struct pipe *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct pipe, p_refcnt, pipe_destroy)

/* The  max pipe buffer size which may  be set by an unprivileged process.
 * NOTE: This value can be read/written using `/proc/sys/fs/pipe-max-size' */
DATDEF size_t pipe_max_bufsize_unprivileged;


struct pipe_reader {
	/* HANDLE:HANDLE_TYPE_PIPE_READER */
	WEAK refcnt_t     pr_refcnt; /* Reference counter */
	REF struct pipe  *pr_pipe;   /* [1..1][const] The associated pipe. */
};
struct pipe_writer {
	/* HANDLE:HANDLE_TYPE_PIPE_WRITER */
	WEAK refcnt_t     pw_refcnt; /* Reference counter */
	REF struct pipe  *pw_pipe;   /* [1..1][const] The associated pipe. */
};

FUNDEF NOBLOCK void NOTHROW(KCALL pipe_reader_destroy)(struct pipe_reader *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL pipe_writer_destroy)(struct pipe_writer *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct pipe_reader, pr_refcnt, pipe_reader_destroy)
DEFINE_REFCNT_FUNCTIONS(struct pipe_writer, pw_refcnt, pipe_writer_destroy)

/* Create a new pipe object. */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe *KCALL
pipe_create(size_t limit DFL(RINGBUFFER_DEFAULT_LIMIT)) THROWS(E_BADALLOC);

/* Create a reader/writer for the given `pipe' */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe_reader *KCALL
pipe_reader_create(struct pipe *__restrict self) THROWS(E_BADALLOC);
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe_writer *KCALL
pipe_writer_create(struct pipe *__restrict self) THROWS(E_BADALLOC);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PIPE_H */
