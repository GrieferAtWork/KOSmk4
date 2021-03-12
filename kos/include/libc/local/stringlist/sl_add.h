/* HASH CRC-32:0xc2e5ed1 */
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
#ifndef __local_sl_add_defined
#define __local_sl_add_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_realloc
#include <hybrid/typecore.h>
#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str;
	__SIZE_TYPE__   sl_max;
	__SIZE_TYPE__   sl_cur;
} StringList;
#endif /* !___stringlist_defined */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#else /* __has_builtin(__builtin_realloc) && __LIBC_BIND_CRTBUILTINS */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#endif /* !__has_builtin(__builtin_realloc) || !__LIBC_BIND_CRTBUILTINS */
#endif /* !__local___localdep_realloc_defined */
/* >> sl_add(3)
 * Append a given `name' to `sl'. `name' is considered
 * inherited if the StringList is destroyed with `freeit=1' */
__LOCAL_LIBC(sl_add) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sl_add))(struct _stringlist *__sl, char *__name) {
	if __unlikely(__sl->sl_cur >= __sl->sl_max) {
		char **__new_vector;
		__SIZE_TYPE__ __new_alloc;
		__new_alloc = __sl->sl_max + 20;
		__new_vector = (char **)__localdep_realloc(__sl->sl_str, __new_alloc * sizeof(char *));
		if __unlikely(__new_vector == __NULLPTR)
			return -1;
		__sl->sl_str = __new_vector;
		__sl->sl_max = __new_alloc;
	}
	__sl->sl_str[__sl->sl_cur] = __name; /* Inherit (maybe) */
	++__sl->sl_cur;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sl_add_defined
#define __local___localdep_sl_add_defined 1
#define __localdep_sl_add __LIBC_LOCAL_NAME(sl_add)
#endif /* !__local___localdep_sl_add_defined */
#else /* __CRT_HAVE_realloc */
#undef __local_sl_add_defined
#endif /* !__CRT_HAVE_realloc */
#endif /* !__local_sl_add_defined */
