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
#ifndef __LOCAL_re_syntax_options
#include <__crt.h>
#ifndef __LOCAL_re_syntax_options
#include <bits/crt/regex.h>
#ifndef __LOCAL_re_syntax_options
__DECL_BEGIN
#ifdef re_syntax_options
#define __LOCAL_re_syntax_options re_syntax_options
#elif defined(__CRT_HAVE_re_syntax_options)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__reg_syntax_t,re_syntax_options)
#define re_syntax_options         re_syntax_options
#define __LOCAL_re_syntax_options re_syntax_options
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__reg_syntax_t,__LOCAL_re_syntax_options,re_syntax_options)
#define __LOCAL_re_syntax_options __LOCAL_re_syntax_options
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_re_syntax_options */
#endif /* !__LOCAL_re_syntax_options */
#endif /* !__LOCAL_re_syntax_options */
