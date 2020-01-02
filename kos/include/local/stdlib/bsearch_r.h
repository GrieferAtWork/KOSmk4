/* HASH CRC-32:0x153e782 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_bsearch_r_defined
#define __local_bsearch_r_defined 1
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bsearch_r) __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bsearch_r))(void const *__pkey,
                                                       void const *__pbase,
                                                       __SIZE_TYPE__ __item_count,
                                                       __SIZE_TYPE__ __item_size,
                                                       __compar_d_fn_t __cmp,
                                                       void *__arg) {
#line 372 "kos/src/libc/magic/stdlib.c"
	/* Optimize this function with the (allowed) assumption that `pbase' is sorted according to:
	 * >> qsort_r(pbase, item_count, item_size, cmp, arg); */
	__SIZE_TYPE__ __lo, __hi;
	__lo = 0;
	__hi = __item_count;
	while __likely(__lo < __hi) {
		__SIZE_TYPE__ __test_index;
		int __difference;
		void *__item_addr;
		/* Select the item right-smack in the middle of
		 * the lower and upper bound for comparison
		 * Assuming an even distribution, the chance of it being the
		 * intended item should be the greatest there, and will increase
		 * with every iteration
		 * Also: This way, the entire algorithm has a worst-case of
		 *       O(INDEX_OF_MSB(item_count))
		 *       with on 32-bit is O(32) and on 64-bit is O(64)
		 */
		__test_index = (__lo + __hi) / 2;
		__item_addr  = (__BYTE_TYPE__ *)__pbase + (__test_index * __item_size);
		/* Check if the requested item lies above, or below the selected one */
		__difference = (*__cmp)(__pkey, __item_addr, __arg);
		if (__difference < 0)
			/* KEY < ITEM --> Narrow the search-area to everything below */
			__hi = __test_index;
		else if (__difference > 0)
			/* KEY > ITEM --> Narrow the search-area to everything above */
			__lo = __test_index + 1;
		else {
			/* Found it! */
			return __item_addr;
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_bsearch_r_defined */
