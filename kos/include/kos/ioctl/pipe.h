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
#ifndef _KOS_IOCTL_PIPE_H
#define _KOS_IOCTL_PIPE_H 1

/* KOS-specific ioctl codes for pipes. These can be used with:
 *  - HANDLE_TYPE_MFILE        (subclass: HANDLE_TYPEKIND_MFILE_FFIFONODE)
 *  - HANDLE_TYPE_FIFOHANDLE
 *  - HANDLE_TYPE_PIPE_WRITER
 *  - HANDLE_TYPE_PIPE_READER
 *  - HANDLE_TYPE_PIPE
 */

#include <__stdinc.h>

#include <asm/ioctl.h>

/* Ioctl codes.
 * NOTE: [r] codes  require `IO_CANREAD', [w] codes require `IO_CANWRITE'.
 *       If not possible -> `E_INVALID_HANDLE_OPERATION_(GET|SET)PROPERTY' */
#define PIPE_IOC_CLOSED   _IOR_KOS('P', 0x00, int)              /*     Check if the pipe has been closed (reading yield remaining data before returning `0'; writing is no longer possible) */
#define PIPE_IOC_READABLE _IOR_KOS('P', 0x01, __size_t)         /* [r] Return the # of bytes available for reading (or peeking; `== OUT(pipe_peek::pp_bufsz)'). */
#define PIPE_IOC_PEEK    _IOWR_KOS('P', 0x08, struct pipe_peek) /* [r] Peek pending data (read w/o consume). */
#define PIPE_IOC_DISCARD _IOWR_KOS('P', 0x09, __size_t)         /* [r] Discard up to IN:ARG bytes of data, and set OUT:ARG to the actual amount discarded */

#ifdef __CC__
__DECL_BEGIN

struct pipe_peek {
	__uint64_t      pp_bufof; /* [in]  # of leading bytes to skip during the peek */
	__uint64_t      pp_bufsz; /* [in]  Max bytes to copy into `pp_buf'.
	                           * [out] Total bytes available. (== PIPE_IOC_READABLE)
	                           * NOTE: The # of bytes written to `pp_buf'
	                           *       is `min(IN:pp_bufsz, OUT:pp_bufsz - IN:pp_bufof)' */
	union {
		void       *pp_buf;   /* Output buffer base */
		__uint64_t _pp_albuf; /* Alignment... */
	};
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_IOCTL_PIPE_H */
