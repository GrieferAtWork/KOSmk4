/* HASH CRC-32:0x2151dbf2 */
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
#ifndef GUARD_LIBC_AUTO_SORT_C
#define GUARD_LIBC_AUTO_SORT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "sort.h"
#include "../user/stdlib.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sort_pointers_compar) __ATTR_PURE int
__NOTHROW_NCX(__LIBCCALL sort_pointers_compar)(void const *a, void const *b) {
	byte_t *lhs = *(byte_t **)a;
	byte_t *rhs = *(byte_t **)b;
#if __SIZEOF_POINTER__ < __SIZEOF_INT__
	return (int)(uintptr_t)lhs - (int)(uintptr_t)rhs;
#else /* __SIZEOF_POINTER__ < __SIZEOF_INT__ */
	if (lhs < rhs)
		return -1;
	if (lhs > rhs)
		return 1;
	return 0;
#endif /* __SIZEOF_POINTER__ >= __SIZEOF_INT__ */
}
__NAMESPACE_LOCAL_END
/* >> sort_pointers(3)
 * Sort an array of `count' pointers `sortme' in ascending order
 * @param: work: An  additional array of `count' elements that may
 *               be used as temporary storage by the implemenation
 *               The  contents  of this  array are  undefined upon
 *               return of this function. */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUTS(2, 1) ATTR_OUTS(3, 1) void
NOTHROW_NCX(LIBCCALL libc_sort_pointers)(size_t count,
                                         void **sortme,
                                         void **work) {
	(void)work; /* unused by this implementation */
	libc_qsort(sortme, count, sizeof(void *), &__NAMESPACE_LOCAL_SYM sort_pointers_compar);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(sort_pointers,libc_sort_pointers,ATTR_INOUTS(2, 1) ATTR_OUTS(3, 1),NOTHROW_NCX,LIBCCALL,(size_t count, void **sortme, void **work),(count,sortme,work));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SORT_C */
