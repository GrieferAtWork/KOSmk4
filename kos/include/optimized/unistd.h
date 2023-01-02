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
#ifndef _OPTIMIZED_UNISTD_H
#define _OPTIMIZED_UNISTD_H 1

#include <__stdinc.h>

#include <asm/pagesize.h>

#if defined(__CC__) && defined(__ARCH_PAGESIZE) && !defined(__fast_getpagesize_defined)
#include <__crt.h>
#include <features.h>

#define __fast_getpagesize_defined
__DECL_BEGIN __NAMESPACE_FAST_BEGIN

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED
__STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBC_FAST_NAME(getpagesize))(void) {
	return __ARCH_PAGESIZE;
}

__NAMESPACE_FAST_END __DECL_END
#endif /* __CC__ && __ARCH_PAGESIZE && !__fast_getpagesize_defined */

#endif /* !_OPTIMIZED_UNISTD_H */
