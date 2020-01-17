/* HASH CRC-32:0xabb57f2 */
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
#ifndef __local_asctime_s_defined
#define __local_asctime_s_defined 1
#include <parts/errno.h>
/* Dependency: "asctime_r" from "time" */
#ifndef ____localdep_asctime_r_defined
#define ____localdep_asctime_r_defined 1
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_asctime_r,(__STRUCT_TM const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* LIBC: asctime_r */
#include <local/time/asctime_r.h>
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
#define __localdep_asctime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))
#endif /* asctime_r... */
#endif /* !____localdep_asctime_r_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(asctime_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(asctime_s))(char *__restrict __buf,
                                                       __SIZE_TYPE__ __buflen,
                                                       struct __NAMESPACE_STD_SYM tm const *__restrict __tp) {
#line 599 "kos/src/libc/magic/time.c"
	if (__buflen < 26)
		return __ERANGE;
	__localdep_asctime_r(__tp, __buf);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_asctime_s_defined */
