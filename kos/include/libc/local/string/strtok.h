/* HASH CRC-32:0x43e97318 */
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
#ifndef __local_strtok_defined
#define __local_strtok_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtok_r_defined
#define __local___localdep_strtok_r_defined
#ifdef __CRT_HAVE_strtok_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__localdep_strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_r,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__localdep_strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_s,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__localdep_strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),__strtok_r,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strtok_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtok_r __LIBC_LOCAL_NAME(strtok_r)
#endif /* !... */
#endif /* !__local___localdep_strtok_r_defined */
__LOCAL_LIBC(strtok) __ATTR_IN(2) __ATTR_INOUT_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtok))(char *__str, char const *__delim) {
	static char *__strtok_save_ptr = __NULLPTR;
	return (__NAMESPACE_LOCAL_SYM __localdep_strtok_r)(__str, __delim, &__strtok_save_ptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtok_defined
#define __local___localdep_strtok_defined
#define __localdep_strtok __LIBC_LOCAL_NAME(strtok)
#endif /* !__local___localdep_strtok_defined */
#endif /* !__local_strtok_defined */
