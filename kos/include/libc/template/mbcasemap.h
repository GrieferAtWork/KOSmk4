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
#ifndef __LOCAL__mbcasemap
#include <__crt.h>
#ifndef __LOCAL__mbcasemap
#ifdef _mbcasemap
#define __LOCAL__mbcasemap _mbcasemap
#elif defined(__CRT_HAVE__mbcasemap)
__DECL_BEGIN
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,unsigned char _mbcasemap[],_mbcasemap)
#define _mbcasemap         _mbcasemap
#define __LOCAL__mbcasemap _mbcasemap
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,unsigned char __LOCAL__mbcasemap[],__LOCAL__mbcasemap,_mbcasemap)
#define __LOCAL__mbcasemap __LOCAL__mbcasemap
#endif /* !__NO_COMPILER_SREDIRECT */
__DECL_END
#elif defined(____p__mbcasemap_defined)
#define __LOCAL__mbcasemap __p__mbcasemap()
#elif defined(__CRT_HAVE___p__mbcasemap)
#define ____p__mbcasemap_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,unsigned char *,__NOTHROW_NCX,__p__mbcasemap,(void),())
#define __LOCAL__mbcasemap __p__mbcasemap()
#endif /* ... */
#endif /* !__LOCAL__mbcasemap */
#endif /* !__LOCAL__mbcasemap */
