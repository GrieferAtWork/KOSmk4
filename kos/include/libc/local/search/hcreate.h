/* HASH CRC-32:0xd4b307d6 */
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
#ifndef __local_hcreate_defined
#define __local_hcreate_defined
#include <__crt.h>
#if defined(__CRT_HAVE_hcreate_r) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_hcreate_r_defined
#define __local___localdep_hcreate_r_defined
#ifdef __CRT_HAVE_hcreate_r
__NAMESPACE_LOCAL_END
struct hsearch_data;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_hcreate_r,(__SIZE_TYPE__ __nel, struct hsearch_data *__htab),hcreate_r,(__nel,__htab))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/search/hcreate_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hcreate_r __LIBC_LOCAL_NAME(hcreate_r)
#else /* ... */
#undef __local___localdep_hcreate_r_defined
#endif /* !... */
#endif /* !__local___localdep_hcreate_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __hsearch_data_defined
#define __hsearch_data_defined
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = { __NULLPTR, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(hcreate) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hcreate))(__SIZE_TYPE__ __nel) {
	return (__NAMESPACE_LOCAL_SYM __localdep_hcreate_r)(__nel, &__NAMESPACE_LOCAL_SYM __htab);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hcreate_defined
#define __local___localdep_hcreate_defined
#define __localdep_hcreate __LIBC_LOCAL_NAME(hcreate)
#endif /* !__local___localdep_hcreate_defined */
#else /* __CRT_HAVE_hcreate_r || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_hcreate_defined
#endif /* !__CRT_HAVE_hcreate_r && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_hcreate_defined */
