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
%(c_prefix){
/* (#) Portability: EMX kLIBC (/libc/include/sort.h) */
/* (#) Portability: libiberty (/include/sort.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

@@>> sort_pointers(3)
@@Sort an array of `count' pointers `sortme' in ascending order
@@@param: work: An  additional array of `count' elements that may
@@              be used as temporary storage by the implemenation
@@              The  contents  of this  array are  undefined upon
@@              return of this function.
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(qsort), impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(@sort_pointers_compar@) __ATTR_PURE int
__NOTHROW_NCX(__LIBCCALL sort_pointers_compar)(void const *a, void const *b) {
	byte_t *lhs = *(byte_t **)a;
	byte_t *rhs = *(byte_t **)b;
@@pp_if __SIZEOF_POINTER__ < __SIZEOF_INT__@@
	return (int)(uintptr_t)lhs - (int)(uintptr_t)rhs;
@@pp_else@@
	if (lhs < rhs)
		return -1;
	if (lhs > rhs)
		return 1;
	return 0;
@@pp_endif@@
}
@@pop_namespace@@
)]]
void sort_pointers(size_t count,
                   [[inout(count)]] void **sortme,
                   [[out(count)]] void **work) {
	(void)work; /* unused by this implementation */
	qsort(sortme, count, sizeof(void *), &__NAMESPACE_LOCAL_SYM sort_pointers_compar);
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
