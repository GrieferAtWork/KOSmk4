/* HASH CRC-32:0x3352e139 */
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
#ifndef __local_obstack_printf_defined
#ifdef __CRT_HAVE_obstack_vprintf
#define __local_obstack_printf_defined 1
/* Dependency: "obstack_vprintf" */
#ifndef ____localdep_obstack_vprintf_defined
#define ____localdep_obstack_vprintf_defined 1
#ifdef __CRT_HAVE_obstack_vprintf
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),int,__NOTHROW_NCX,__localdep_obstack_vprintf,(struct obstack *__restrict __obstack_, char const *__restrict __format, __builtin_va_list __args),obstack_vprintf,(__obstack_,__format,__args))
#else /* LIBC: obstack_vprintf */
#undef ____localdep_obstack_vprintf_defined
#endif /* obstack_vprintf... */
#endif /* !____localdep_obstack_vprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(obstack_printf) __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) int
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(obstack_printf))(struct obstack *__restrict __obstack_,
                                                             char const *__restrict __format,
                                                             ...) {
#line 1513 "kos/src/libc/magic/stdio.c"
	int __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_obstack_vprintf(__obstack_, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_obstack_vprintf */
#endif /* !__local_obstack_printf_defined */
