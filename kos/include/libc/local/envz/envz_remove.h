/* HASH CRC-32:0x1f670151 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_envz_remove_defined
#define __local_envz_remove_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_argz_delete_defined
#define __local___localdep_argz_delete_defined
#ifdef __CRT_HAVE_argz_delete
__CREDIRECT_VOID(__ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_IN_OPT(3),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),argz_delete,(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_delete)
__CREDIRECT_VOID(__ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_IN_OPT(3),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),__argz_delete,(__pargz,__pargz_len,__entry))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/argz/argz_delete.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_argz_delete __LIBC_LOCAL_NAME(argz_delete)
#endif /* !... */
#endif /* !__local___localdep_argz_delete_defined */
#ifndef __local___localdep_envz_entry_defined
#define __local___localdep_envz_entry_defined
#ifdef __CRT_HAVE_envz_entry
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_envz_entry,(char const *__restrict __envz, __SIZE_TYPE__ __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
#else /* __CRT_HAVE_envz_entry */
__NAMESPACE_LOCAL_END
#include <libc/local/envz/envz_entry.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_envz_entry __LIBC_LOCAL_NAME(envz_entry)
#endif /* !__CRT_HAVE_envz_entry */
#endif /* !__local___localdep_envz_entry_defined */
__LOCAL_LIBC(envz_remove) __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_remove))(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __name) {
	char *__entry;
	__entry = (__NAMESPACE_LOCAL_SYM __localdep_envz_entry)(*__penvz, *__penvz_len, __name);
	if (__entry)
		(__NAMESPACE_LOCAL_SYM __localdep_argz_delete)(__penvz, __penvz_len, __entry);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_remove_defined
#define __local___localdep_envz_remove_defined
#define __localdep_envz_remove __LIBC_LOCAL_NAME(envz_remove)
#endif /* !__local___localdep_envz_remove_defined */
#endif /* !__local_envz_remove_defined */
