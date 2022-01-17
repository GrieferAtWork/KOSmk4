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

#include <__stdinc.h>
#include <hybrid/compiler.h>

#include <__crt.h>
#include <kos/anno.h>

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

#endif /* !GUARD_LIBKERNEL32_API_H */
