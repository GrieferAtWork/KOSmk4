/* HASH CRC-32:0x996cd9ee */
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
#ifndef __local_re_set_syntax_defined
#define __local_re_set_syntax_defined
#include <__crt.h>
#include <libc/template/re_syntax_options.h>
#ifdef __LOCAL_re_syntax_options
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(re_set_syntax) __reg_syntax_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(re_set_syntax))(__reg_syntax_t __syntax) {
	__reg_syntax_t __result = __LOCAL_re_syntax_options;
	__LOCAL_re_syntax_options   = __syntax;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_re_set_syntax_defined
#define __local___localdep_re_set_syntax_defined
#define __localdep_re_set_syntax __LIBC_LOCAL_NAME(re_set_syntax)
#endif /* !__local___localdep_re_set_syntax_defined */
#else /* __LOCAL_re_syntax_options */
#undef __local_re_set_syntax_defined
#endif /* !__LOCAL_re_syntax_options */
#endif /* !__local_re_set_syntax_defined */
