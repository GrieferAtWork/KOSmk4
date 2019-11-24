/* HASH CRC-32:0x1353fc06 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16set_defined
#define __local_c16set_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16set) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16set))(__CHAR16_TYPE__ *__restrict __str,
                                                    __CHAR16_TYPE__ __ch) {
#line 4795 "kos/src/libc/magic/string.c"
	__CHAR16_TYPE__ *__iter;
	for (__iter = __str; *__iter; ++__iter)
		*__iter = (__CHAR16_TYPE__)__ch;
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16set_defined */
