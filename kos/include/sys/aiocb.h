/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/aiocb.h) */
#ifndef _SYS_AIOCB_H
#define _SYS_AIOCB_H 1

#include <__stdinc.h>
#include <asm/crt/aio.h>
#include <bits/crt/aiocb.h>

/* Return values of cancellation function. */
#if !defined(AIO_CANCELED) && defined(__AIO_CANCELED)
#define AIO_CANCELED    __AIO_CANCELED    /* ??? */
#endif /* !AIO_CANCELED && __AIO_CANCELED */
#if !defined(AIO_NOTCANCELED) && defined(__AIO_NOTCANCELED)
#define AIO_NOTCANCELED __AIO_NOTCANCELED /* ??? */
#endif /* !AIO_NOTCANCELED && __AIO_NOTCANCELED */
#if !defined(AIO_ALLDONE) && defined(__AIO_ALLDONE)
#define AIO_ALLDONE     __AIO_ALLDONE     /* ??? */
#endif /* !AIO_ALLDONE && __AIO_ALLDONE */

/* Operation codes for `aio_lio_opcode'. */
#if !defined(LIO_READ) && defined(__LIO_READ)
#define LIO_READ  __LIO_READ  /* Perform an async `read(2)' or `pread(2)' */
#endif /* !LIO_READ && __LIO_READ */
#if !defined(LIO_WRITE) && defined(__LIO_WRITE)
#define LIO_WRITE __LIO_WRITE /* Perform an async `write(2)' or `pwrite(2)' */
#endif /* !LIO_WRITE && __LIO_WRITE */
#if !defined(LIO_NOP) && defined(__LIO_NOP)
#define LIO_NOP   __LIO_NOP   /* No-op */
#endif /* !LIO_NOP && __LIO_NOP */

/* Synchronization options for `lio_listio' function. */
#if !defined(LIO_WAIT) && defined(__LIO_WAIT)
#define LIO_WAIT   __LIO_WAIT   /* ??? */
#endif /* !LIO_WAIT && __LIO_WAIT */
#if !defined(LIO_NOWAIT) && defined(__LIO_NOWAIT)
#define LIO_NOWAIT __LIO_NOWAIT /* ??? */
#endif /* !LIO_NOWAIT && __LIO_NOWAIT */

#endif /* !_SYS_AIOCB_H */
