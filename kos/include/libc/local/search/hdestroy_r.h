/* HASH CRC-32:0x8b63c042 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_hdestroy_r_defined
#define __local_hdestroy_r_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
struct hsearch_data;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
__NAMESPACE_LOCAL_END
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Reentrant versions which can handle multiple hashing tables at the same time */
__LOCAL_LIBC(hdestroy_r) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hdestroy_r))(struct hsearch_data *__htab) {
	if (__htab == __NULLPTR) {
#ifdef __EINVAL
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return;
	}
	__localdep_free(__htab->table);
	__htab->table = __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hdestroy_r_defined
#define __local___localdep_hdestroy_r_defined 1
#define __localdep_hdestroy_r __LIBC_LOCAL_NAME(hdestroy_r)
#endif /* !__local___localdep_hdestroy_r_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree */
#undef __local_hdestroy_r_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree */
#endif /* !__local_hdestroy_r_defined */
