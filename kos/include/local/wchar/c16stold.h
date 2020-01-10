/* HASH CRC-32:0x884821c7 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef __local_c16stold_defined
#define __local_c16stold_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stold) __ATTR_PURE __ATTR_NONNULL((1)) long double
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stold))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                      __CHAR16_TYPE__ **__endptr) {
#line 929 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	__COMPILER_IMPURE();
	if (__endptr)
		*__endptr = (__CHAR16_TYPE__ *)__nptr;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16stold_defined */
