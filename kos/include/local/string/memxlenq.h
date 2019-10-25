/* HASH CRC-32:0x455d22e1 */
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
#ifndef __local_memxlenq_defined
#define __local_memxlenq_defined 1
/* Dependency: "memxendq" from "string" */
#ifndef ____localdep_memxendq_defined
#define ____localdep_memxendq_defined 1
#if defined(__CRT_HAVE_memxendq)
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memxendq,(__haystack,__qword,__n_bytes))
#else /* LIBC: memxendq */
#include <local/string/memxendq.h>
/* Same as `memendq', but search for non-matching locations. */
#define __localdep_memxendq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))
#endif /* memxendq... */
#endif /* !____localdep_memxendq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memlenq', but search for non-matching locations. */
__LOCAL_LIBC(memxlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxlenq))(void const *__restrict __haystack,
                                                      __UINT64_TYPE__ __qword,
                                                      __SIZE_TYPE__ __n_qwords) {
#line 2053 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memxendq(__haystack, __qword, __n_qwords) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memxlenq_defined */
