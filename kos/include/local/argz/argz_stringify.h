/* HASH CRC-32:0xbb2e3add */
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
#ifndef __local_argz_stringify_defined
#define __local_argz_stringify_defined 1
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__LOCAL_LIBC(argz_stringify) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_stringify))(char *__argz,
                                                            __SIZE_TYPE__ __len,
                                                            int __sep) {
#line 225 "kos/src/libc/magic/argz.c"
	__SIZE_TYPE__ __i;
	/* replace(base: argz, count: len - 1, old: '\0', new: sep); */
	if __unlikely(!__len)
		return;
	for (__i = 0;;) {
		__SIZE_TYPE__ __temp;
		__temp = __localdep_strlen(__argz) + 1;
		if (__temp >= __len)
			break;
		__len  -= __temp;
		__argz += __temp;
		__argz[-1] = (char)(unsigned char)(unsigned int)__sep;
	}
}
__NAMESPACE_LOCAL_END
#endif /* !__local_argz_stringify_defined */
