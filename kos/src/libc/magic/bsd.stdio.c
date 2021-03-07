/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: libbsd (/include/bsd/stdio.h) */
}

%[insert:prefix(
#include <stdio.h>
)]%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */

}

%[insert:extern(fmtcheck)]
%[insert:extern(fgetln)]
%[insert:guarded_function(fpurge = __fpurge)]

%[insert:extern(funopen)]

%{
#ifdef __funopen_defined
#define fropen(cookie, fn) funopen(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen(cookie, fn) funopen(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR)
#endif /* __funopen_defined */

__SYSDECL_END
#endif /* __CC__ */

}
