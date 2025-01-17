/* HASH CRC-32:0xffe052b1 */
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
#ifndef __local_step_defined
#define __local_step_defined
#include <__crt.h>
#include <asm/crt/regex.h>
#include <libc/template/locN.h>
#if defined(__LOCAL_loc1) && defined(__LOCAL_loc2) && defined(__REG_NOTEOL) && defined(__CRT_HAVE_regexec)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_regexec_defined
#define __local___localdep_regexec_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_regexec,(struct re_pattern_buffer const *__restrict __self, char const *__restrict __string, __SIZE_TYPE__ __nmatch, struct __regmatch __pmatch[__restrict_arr], int __eflags),regexec,(__self,__string,__nmatch,__pmatch,__eflags))
#endif /* !__local___localdep_regexec_defined */
__LOCAL_LIBC(step) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(step))(char const *__string, char const *__expbuf) {
	struct __regmatch __match;
	__expbuf = (char *)((__UINTPTR_TYPE__)(__expbuf + __COMPILER_ALIGNOF(struct re_pattern_buffer) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                  ~(__COMPILER_ALIGNOF(struct re_pattern_buffer) - 1));
	if ((__NAMESPACE_LOCAL_SYM __localdep_regexec)((struct re_pattern_buffer const *)__expbuf, __string, 1, &__match, __REG_NOTEOL) != 0)
		return 0;
	__LOCAL_loc1 = (char *)__string + __match.rm_so;
	__LOCAL_loc2 = (char *)__string + __match.rm_eo;
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_step_defined
#define __local___localdep_step_defined
#define __localdep_step __LIBC_LOCAL_NAME(step)
#endif /* !__local___localdep_step_defined */
#else /* __LOCAL_loc1 && __LOCAL_loc2 && __REG_NOTEOL && __CRT_HAVE_regexec */
#undef __local_step_defined
#endif /* !__LOCAL_loc1 || !__LOCAL_loc2 || !__REG_NOTEOL || !__CRT_HAVE_regexec */
#endif /* !__local_step_defined */
