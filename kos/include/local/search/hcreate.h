/* HASH CRC-32:0x6cce4aa6 */
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
#ifndef __local_hcreate_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_hcreate_r)
#define __local_hcreate_defined 1
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int     size;
	unsigned int     filled;
};
#endif /* !__hsearch_data_defined */
/* Dependency: "hcreate_r" from "search" */
#ifndef ____localdep_hcreate_r_defined
#define ____localdep_hcreate_r_defined 1
#ifdef __CRT_HAVE_hcreate_r
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_hcreate_r,(__SIZE_TYPE__ __nel, struct hsearch_data *__htab),hcreate_r,(__nel,__htab))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/search/hcreate_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
#define __localdep_hcreate_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hcreate_r))
#else /* CUSTOM: hcreate_r */
#undef ____localdep_hcreate_r_defined
#endif /* hcreate_r... */
#endif /* !____localdep_hcreate_r_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __local_htab_defined
#define __local_htab_defined 1
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = {__NULLPTR, 0, 0};
#endif /* !__local_htab_defined */
/* Create a new hashing table which will at most contain NEL elements */
__LOCAL_LIBC(hcreate) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hcreate))(__SIZE_TYPE__ __nel) {
#line 212 "kos/src/libc/magic/search.c"
	return __localdep_hcreate_r(__nel, &__htab);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc || __CRT_HAVE_hcreate_r */
#endif /* !__local_hcreate_defined */
