/* HASH CRC-32:0xe33ade7f */
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
#ifndef __local_vsscanf_defined
#define __local_vsscanf_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vscanf_defined
#define __local___localdep_format_vscanf_defined
#ifdef __CRT_HAVE_format_vscanf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__localdep_format_vscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vscanf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vscanf __LIBC_LOCAL_NAME(format_vscanf)
#endif /* !__CRT_HAVE_format_vscanf */
#endif /* !__local___localdep_format_vscanf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) __format_word_t
(__FORMATPRINTER_CC __vsscanf_getc)(void *__arg) {
	unsigned char const *__reader = *(unsigned char const **)__arg;
	unsigned char __result        = *__reader++;
	if (!__result)
		return __EOF;
	*(unsigned char const **)__arg = __reader;
	return (__format_word_t)__result;
}
__LOCAL_LIBC(vsscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsscanf_ungetc)(void *__arg, __format_word_t __UNUSED(__word)) {
	--(*(unsigned char const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf) __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsscanf))(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vscanf)(&__NAMESPACE_LOCAL_SYM __vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __vsscanf_ungetc,
	                     (void *)&__input, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsscanf_defined
#define __local___localdep_vsscanf_defined
#define __localdep_vsscanf __LIBC_LOCAL_NAME(vsscanf)
#endif /* !__local___localdep_vsscanf_defined */
#endif /* !__local_vsscanf_defined */
