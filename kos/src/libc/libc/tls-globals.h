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
#include <hybrid/typecore.h>

#include <bits/crt/tm.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */

struct re_code;

/* clang-format off */
struct libc_tlsglobals {
	struct re_code *ltg_re_comp_buffer; /* [0..1] The static buffer used by `re_comp(3)' and `re_exec(3)' */
/*[[[begin:libc_tlsglobals]]]*/
	char     *ltg_getpass_buf;
	char     *ltg_strtok_save_ptr;
	void     *ltg_cuserid_buf;
	void     *ltg_devname_buf;
	void     *ltg_ptsname_buf;
	void     *ltg_ttyname_buf;
	struct tm ltg_tmbuf;
	char      ltg_l64a_buf[(((sizeof(long) * __CHAR_BIT__) + 5) / 6) + 1];
	char      ltg_ctime_buf[26];
	char      ltg_qcvt_buf[32];
	char      ltg_ctermid_buf[9];
/*[[[end:libc_tlsglobals]]]*/
};
/* clang-format on */

/* Return a pointer to the calling thread's tls-globals controller. */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct libc_tlsglobals *
NOTHROW(LIBCCALL libc_get_tlsglobals)(void);

/* Finalize `self' (called when a pthread is destroyed, but not called for the main thread) */
INTDEF NONNULL((1)) void
NOTHROW(LIBCCALL libc_fini_tlsglobals)(struct libc_tlsglobals *__restrict self);

DECL_END
#endif /* __CC__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_LIBC_TLS_GLOBALS_H */
