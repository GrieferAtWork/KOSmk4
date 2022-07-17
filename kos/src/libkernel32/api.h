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
#ifndef GUARD_LIBKERNEL32_API_H
#define GUARD_LIBKERNEL32_API_H 1
#undef _TIME_T_BITS
#define _TIME_T_BITS 64

#include <__crt.h>
#include <__stdinc.h>
#include <hybrid/compiler.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#define CC  ATTR_STDCALL /* WINAPI */
#define VCC ATTR_CDECL

#ifndef REF
#define REF __REF
#endif /* !REF */

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

#ifndef LIBCCALL
#define LIBCCALL __LIBCCALL
#endif /* !LIBCCALL */

#ifndef LIBKCALL
#define LIBKCALL __LIBKCALL
#endif /* !LIBKCALL */

#ifndef LIBDCALL
#define LIBDCALL __LIBDCALL
#endif /* !LIBDCALL */

#ifdef __CC__
DECL_BEGIN

__LIBC __errno_t *NOTHROW(LIBCCALL __nterrno_location)(void);
#define _nterrno (*__nterrno_location())

DECL_END
#endif /* __CC__ */

#if 1
#include <syslog.h>
#define TRACE(format, ...) \
	syslog(LOG_DEBUG, "[k32] " format "\n", ##__VA_ARGS__)
#endif

#ifndef TRACE
#define TRACE(...) (void)0
#endif /* !TRACE */


#endif /* !GUARD_LIBKERNEL32_API_H */
