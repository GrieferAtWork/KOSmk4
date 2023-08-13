/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_TLS_GLOBALS_H
#define GUARD_LIBC_LIBC_TLS_GLOBALS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#ifndef __KERNEL__
#ifdef __CC__
DECL_BEGIN

/* clang-format off */
struct libc_tlsglobals {
/*[[[begin:libc_tlsglobals]]]*/
	char *ltg_strtok_save_ptr;
	void *ltg_ttyname_buf;
/*[[[end:libc_tlsglobals]]]*/
};
/* clang-format on */

/* Return a pointer to the calling thread's tls-globals controller. */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct libc_tlsglobals *
NOTHROW(LIBCCALL libc_get_tlsglobals)(void);

/* Finalize `self' (called when a pthread exits, but not called for the main thread) */
INTDEF NONNULL((1)) void
NOTHROW(LIBCCALL libc_fini_tlsglobals)(struct libc_tlsglobals *__restrict self);

/* TODO: change the following functions to use tls-globals:
 * - char[]: getpass
 * - char[]: ptsname
 * - char[]: l64a
 * - char[]: ctime, ctime64
 * - char[]: asctime
 * - char[]: ctermid
 * - char[]: cuserid
 * - char[]: qecvt
 * - char[]: qfcvt
 * - char[]: ecvt
 * - char[]: fcvt
 * - char[]: devname
 * - struct tm: gmtime, gmtime64
 * - struct tm: localtime, localtime64
 * - struct tm: getdate
 */

DECL_END
#endif /* __CC__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_LIBC_TLS_GLOBALS_H */
