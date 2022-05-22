/* HASH CRC-32:0x234f77eb */
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
#ifndef __local_format_vc32scanf_defined
#define __local_format_vc32scanf_defined
#include <__crt.h>
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
#include <libc/string.h>
#include <libc/unicode.h>
#include <parts/printf-config.h>
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_vc32scanf) __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
(__LIBKCALL __LIBC_LOCAL_NAME(format_vc32scanf))(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
#ifndef __INTELLISENSE__
#define __CHAR_TYPE      __CHAR32_TYPE__
#define __CHAR_SIZE      4
#define __FORMAT_PGETC   __pgetc
#define __FORMAT_PUNGETC __pungetc
#define __FORMAT_ARG     __arg
#define __FORMAT_FORMAT  __format
#define __FORMAT_ARGS    __args
#include <libc/template/format-scanf.h>
#endif /* !__INTELLISENSE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_vc32scanf_defined
#define __local___localdep_format_vc32scanf_defined
#define __localdep_format_vc32scanf __LIBC_LOCAL_NAME(format_vc32scanf)
#endif /* !__local___localdep_format_vc32scanf_defined */
#endif /* !__local_format_vc32scanf_defined */
