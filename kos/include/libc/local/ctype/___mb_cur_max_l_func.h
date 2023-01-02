/* HASH CRC-32:0x68cfbb2b */
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
#ifndef __local____mb_cur_max_l_func_defined
#define __local____mb_cur_max_l_func_defined
#include <__crt.h>
#include <libc/template/MB_CUR_MAX.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(___mb_cur_max_l_func) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(___mb_cur_max_l_func))(__locale_t __locale) {
	(void)__locale;
	return __LOCAL_MB_CUR_MAX;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep____mb_cur_max_l_func_defined
#define __local___localdep____mb_cur_max_l_func_defined
#define __localdep____mb_cur_max_l_func __LIBC_LOCAL_NAME(___mb_cur_max_l_func)
#endif /* !__local___localdep____mb_cur_max_l_func_defined */
#endif /* !__local____mb_cur_max_l_func_defined */
