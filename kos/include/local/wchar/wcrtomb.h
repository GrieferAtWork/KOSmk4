/* HASH CRC-32:0x8d96df7d */
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
#ifndef __local_wcrtomb_defined
#define __local_wcrtomb_defined 1
__NAMESPACE_LOCAL_BEGIN
#ifndef ____local_wcrtomb_ps_defined
#define ____local_wcrtomb_ps_defined 1
__LOCAL_LIBC_DATA(__wcrtomb_ps) __mbstate_t __wcrtomb_ps = __MBSTATE_INIT;
#endif /* !____local_wcrtomb_ps_defined */
__LOCAL_LIBC(wcrtomb) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcrtomb))(char *__restrict __str,
                                                     __WCHAR_TYPE__ __wc,
                                                     __mbstate_t *__ps) {
#line 251 "kos/src/libc/magic/wchar.c"
	if (!__ps)
		__ps = &__wcrtomb_ps;
	if (!__str) {
		__ps->__word = 0;
		return 0;
	}
	*__str = (char)__wc;
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcrtomb_defined */
