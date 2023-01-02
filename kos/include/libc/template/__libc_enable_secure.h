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
#ifndef __LOCAL___libc_enable_secure
#include <__crt.h>
#ifndef __LOCAL___libc_enable_secure
#ifdef __libc_enable_secure
#define __LOCAL___libc_enable_secure __libc_enable_secure
#elif defined(__CRT_HAVE___libc_enable_secure)
#ifndef __NO_COMPILER_SREDIRECT
#define __LOCAL___libc_enable_secure __LOCAL___libc_enable_secure
#ifdef __CC__
__DECL_BEGIN
__CSREDIRECT(,int,__LOCAL___libc_enable_secure,__libc_enable_secure)
__DECL_END
#endif /* __CC__ */
#else /* !__NO_COMPILER_SREDIRECT */
#define __LOCAL___libc_enable_secure __libc_enable_secure
#define __libc_enable_secure         __libc_enable_secure
#ifdef __CC__
__DECL_BEGIN
__CSDECLARE(,int,__libc_enable_secure)
__DECL_END
#endif /* __CC__ */
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_issetugid)
#ifndef __issetugid_defined
#define __issetugid_defined
#ifdef __CC__
__DECL_BEGIN
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issetugid,(void),())
__DECL_END
#endif /* __CC__ */
#endif /* !__issetugid_defined */
#define __LOCAL___libc_enable_secure issetugid()
#else /* ... */
#include <libc/sys.auxv.h>
#ifdef ____libc_getauxval_defined
#include <elf.h>
#ifdef AT_SECURE
#ifndef __LOCAL___libc_enable_secure
#define __LOCAL___libc_enable_secure __libc_getauxval(AT_SECURE)
#endif /* !__LOCAL___libc_enable_secure */
#endif /* AT_SECURE */
#endif /* ____libc_getauxval_defined */
#endif /* !... */
#endif /* !__LOCAL___libc_enable_secure */
#endif /* !__LOCAL___libc_enable_secure */
