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
#ifndef _ASM_CRT_AIO_H
#define _ASM_CRT_AIO_H 1

/* Return values of cancellation function. */
#define __AIO_CANCELED    0 /* ??? */
#define __AIO_NOTCANCELED 1 /* ??? */
#define __AIO_ALLDONE     2 /* ??? */

/* Operation codes for `aio_lio_opcode'. */
#define __LIO_READ  0 /* Perform an async `read(2)' or `pread(2)' */
#define __LIO_WRITE 1 /* Perform an async `write(2)' or `pwrite(2)' */
#define __LIO_NOP   2 /* No-op */

/* Synchronization options for `lio_listio' function. */
#define __LIO_WAIT   0 /* ??? */
#define __LIO_NOWAIT 1 /* ??? */

#endif /* !_ASM_CRT_AIO_H */
