/* HASH CRC-32:0x7386e1da */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___stpcpy_chk_defined
#define __local___stpcpy_chk_defined 1
/* Dependency: "stpcpy" from "string" */
#ifndef ____localdep_stpcpy_defined
#define ____localdep_stpcpy_defined 1
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__EXTERNINLINE __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __localdep_stpcpy)(char *__restrict __buf, char const *__restrict __src) { return __builtin_stpcpy(__buf, __src); }
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* LIBC: stpcpy */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
#define __localdep_stpcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))
#endif /* stpcpy... */
#endif /* !____localdep_stpcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__stpcpy_chk) __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__stpcpy_chk))(char *__restrict __dst,
                                                          char const *__restrict __src,
                                                          __SIZE_TYPE__ __dst_bufsize) {
#line 77 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_bufsize;
	return __localdep_stpcpy(__dst, __src);
}
__NAMESPACE_LOCAL_END
#endif /* !__local___stpcpy_chk_defined */
