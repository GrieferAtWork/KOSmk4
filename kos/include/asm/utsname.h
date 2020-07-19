/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_UTSNAME_H
#define _ASM_UTSNAME_H 1

#include <__stdinc.h>
#include <asm/limits.h> /* __HOST_NAME_MAX */

#ifndef _UTSNAME_LENGTH
#if defined(__HOST_NAME_MAX) && (__HOST_NAME_MAX + 0) != -1
#define _UTSNAME_LENGTH (__HOST_NAME_MAX + 1)
#else /* __HOST_NAME_MAX != -1 */
#define _UTSNAME_LENGTH 65
#endif /* __HOST_NAME_MAX == -1 */
#endif /* !_UTSNAME_LENGTH */

#ifndef _UTSNAME_DOMAIN_LENGTH
#define _UTSNAME_DOMAIN_LENGTH _UTSNAME_LENGTH
#endif /* !_UTSNAME_DOMAIN_LENGTH */

#endif /* !_ASM_UTSNAME_H */
