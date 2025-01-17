/* HASH CRC-32:0x2b01f04e */
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
/* (#) Portability: GNU C Library (/resource/sys/vlimit.h) */
#ifndef _SYS_VLIMIT_H
#define _SYS_VLIMIT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/vlimit.h>


/* Accepted codes for `resource' argument of `vlimit(3)' */
#if !defined(LIM_NORAISE) && defined(__LIM_NORAISE)
#define LIM_NORAISE __LIM_NORAISE /* Unsupported */
#endif /* !LIM_NORAISE && __LIM_NORAISE */
#if !defined(LIM_CPU) && defined(__LIM_CPU)
#define LIM_CPU     __LIM_CPU     /* s.a. `RLIMIT_CPU' */
#endif /* !LIM_CPU && __LIM_CPU */
#if !defined(LIM_FSIZE) && defined(__LIM_FSIZE)
#define LIM_FSIZE   __LIM_FSIZE   /* s.a. `RLIMIT_FSIZE' */
#endif /* !LIM_FSIZE && __LIM_FSIZE */
#if !defined(LIM_DATA) && defined(__LIM_DATA)
#define LIM_DATA    __LIM_DATA    /* s.a. `RLIMIT_DATA' */
#endif /* !LIM_DATA && __LIM_DATA */
#if !defined(LIM_STACK) && defined(__LIM_STACK)
#define LIM_STACK   __LIM_STACK   /* s.a. `RLIMIT_STACK' */
#endif /* !LIM_STACK && __LIM_STACK */
#if !defined(LIM_CORE) && defined(__LIM_CORE)
#define LIM_CORE    __LIM_CORE    /* s.a. `RLIMIT_CORE' */
#endif /* !LIM_CORE && __LIM_CORE */
#if !defined(LIM_MAXRSS) && defined(__LIM_MAXRSS)
#define LIM_MAXRSS  __LIM_MAXRSS  /* s.a. `RLIMIT_RSS' */
#endif /* !LIM_MAXRSS && __LIM_MAXRSS */


/* No limit.
 * WARNING: <math.h> also defines a macro `INFINITY'. - Both are guarded by #ifndef,
 *          but if you include both headers, you'll only get the first one's #define
 *          for this macro! */
#if !defined(INFINITY) && defined(__VLIMIT_INFINITY)
#define INFINITY __VLIMIT_INFINITY
#endif /* !INFINITY && __VLIMIT_INFINITY */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_vlimit
/* >> vlimit(3)
 * Ancient wrapper for `setrlimit(2)' (s.a. `struct rlimit::rlim_cur')
 * @param: resource: One of `LIM_*' (see above)
 * @param: value:    Value to assign to `resource'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,vlimit,(int __resource, int ___value),(__resource,___value))
#else /* __CRT_HAVE_vlimit */
#include <asm/os/resource.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((defined(__CRT_HAVE_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_setrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)))
#include <libc/local/sys.vlimit/vlimit.h>
/* >> vlimit(3)
 * Ancient wrapper for `setrlimit(2)' (s.a. `struct rlimit::rlim_cur')
 * @param: resource: One of `LIM_*' (see above)
 * @param: value:    Value to assign to `resource'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(vlimit, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL vlimit)(int __resource, int ___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vlimit))(__resource, ___value); })
#endif /* ((__CRT_HAVE_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_getrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((__CRT_HAVE_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_setrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) */
#endif /* !__CRT_HAVE_vlimit */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_VLIMIT_H */
