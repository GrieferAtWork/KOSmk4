/* HASH 0x13c29750 */
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
#ifndef __local_strtok_defined
#define __local_strtok_defined 1
/* Dependency: "strtok_r" from "string" */
#ifndef ____localdep_strtok_r_defined
#define ____localdep_strtok_r_defined 1
#if defined(__CRT_HAVE_strtok_r)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__localdep_strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_r,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__localdep_strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_s,(__string,__delim,__save_ptr))
#else /* LIBC: strtok_r */
#include <local/string/strtok_r.h>
#define __localdep_strtok_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))
#endif /* strtok_r... */
#endif /* !____localdep_strtok_r_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__save_ptr) char *__save_ptr = __NULLPTR;
__LOCAL_LIBC(strtok) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtok))(char *__string,
                                                    char const *__delim) {
#line 348 "kos/src/libc/magic/string.c"
	return __localdep_strtok_r(__string, __delim, &__save_ptr);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strtok_defined */
