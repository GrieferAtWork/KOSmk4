/* HASH CRC-32:0xf5eb48f1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_Truncate_defined
#define __local_Truncate_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_Truncate64) || defined(__CRT_HAVE_Truncate)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_Truncate32_defined) && defined(__CRT_HAVE_Truncate)
#define __local___localdep_Truncate32_defined
__CREDIRECT_VOID(__ATTR_IN(1),__THROWING(...),__localdep_Truncate32,(char const *__file, __pos32_t __length),Truncate,(__file,__length))
#endif /* !__local___localdep_Truncate32_defined && __CRT_HAVE_Truncate */
#ifndef __local___localdep_Truncate64_defined
#define __local___localdep_Truncate64_defined
#if defined(__CRT_HAVE_Truncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT_VOID(__ATTR_IN(1),__THROWING(...),__localdep_Truncate64,(char const *__file, __pos64_t __length),Truncate,(__file,__length))
#elif defined(__CRT_HAVE_Truncate64)
__CREDIRECT_VOID(__ATTR_IN(1),__THROWING(...),__localdep_Truncate64,(char const *__file, __pos64_t __length),Truncate64,(__file,__length))
#elif defined(__CRT_HAVE_Truncate)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/Truncate64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_Truncate64 __LIBC_LOCAL_NAME(Truncate64)
#else /* ... */
#undef __local___localdep_Truncate64_defined
#endif /* !... */
#endif /* !__local___localdep_Truncate64_defined */
__LOCAL_LIBC(Truncate) __ATTR_IN(1) void
(__LIBCCALL __LIBC_LOCAL_NAME(Truncate))(char const *__file, __pos_t __length) __THROWS(...) {
#ifdef __CRT_HAVE_Truncate
	(__NAMESPACE_LOCAL_SYM __localdep_Truncate64)(__file, (__pos64_t)__length);
#else /* __CRT_HAVE_Truncate */
	(__NAMESPACE_LOCAL_SYM __localdep_Truncate32)(__file, (__pos32_t)__length);
#endif /* !__CRT_HAVE_Truncate */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Truncate_defined
#define __local___localdep_Truncate_defined
#define __localdep_Truncate __LIBC_LOCAL_NAME(Truncate)
#endif /* !__local___localdep_Truncate_defined */
#else /* __CRT_HAVE_Truncate64 || __CRT_HAVE_Truncate */
#undef __local_Truncate_defined
#endif /* !__CRT_HAVE_Truncate64 && !__CRT_HAVE_Truncate */
#endif /* !__local_Truncate_defined */
