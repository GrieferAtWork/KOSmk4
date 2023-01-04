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
#ifndef _LIBC_TEMPLATE_GETOPT_H
#define _LIBC_TEMPLATE_GETOPT_H

#include <__crt.h>

__DECL_BEGIN
#ifndef __LOCAL_optarg
#ifdef optarg
#define __LOCAL_optarg optarg
#elif defined(__CRT_HAVE_optarg)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_optarg,optarg)
#define __LOCAL_optarg __LOCAL_optarg
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,optarg)
#define optarg         optarg
#define __LOCAL_optarg optarg
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_optarg */

#ifndef __LOCAL_optind
#ifdef optind
#define __LOCAL_optind optind
#elif defined(__CRT_HAVE_optind)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,__LOCAL_optind,optind)
#define __LOCAL_optind __LOCAL_optind
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,optind)
#define optind         optind
#define __LOCAL_optind optind
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_optind */

#ifndef __LOCAL_opterr
#ifdef opterr
#define __LOCAL_opterr opterr
#elif defined(__CRT_HAVE_opterr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,__LOCAL_opterr,opterr)
#define __LOCAL_opterr __LOCAL_opterr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,opterr)
#define opterr         opterr
#define __LOCAL_opterr opterr
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_opterr */

#ifndef __LOCAL_optopt
#ifdef optopt
#define __LOCAL_optopt optopt
#elif defined(__CRT_HAVE_optopt)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,__LOCAL_optopt,optopt)
#define __LOCAL_optopt __LOCAL_optopt
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,optopt)
#define optopt         optopt
#define __LOCAL_optopt optopt
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_optopt */

__DECL_END
#endif /* !_LIBC_TEMPLATE_GETOPT_H */
