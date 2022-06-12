/* HASH CRC-32:0x372c948f */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_qsort_r_defined
#define __local_qsort_r_defined
#include <__crt.h>
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qsort_r) __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)) void
(__LIBCCALL __LIBC_LOCAL_NAME(qsort_r))(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) {
	/* A public domain qsort() drop-in implementation. I couldn't find the original
	 * source referenced (see the comment below), but this code is the first  thing
	 * that comes up when you search for `libc qsort public domain'.
	 * https://git.busybox.net/uClibc/tree/libc/stdlib/stdlib.c#n770
	 *
	 * Note that I made some modifications, and you should see the linked source for
	 * the original code.
	 *
	 * WARNING: This function's logic will break in situations where `item_count' is
	 *          greater than or equal to:
	 *  - sizeof(size_t) == 4: item_count >= 0x67ea0dc9         (> 2.5 GiB of data at least)
	 *  - sizeof(size_t) == 8: item_count >= 0xfd150e7b3dafdc31 (an insane amount of memory...)
	 *
	 * But I would argue that this isn't something that could ever feasibly happen, and
	 * even speaking architecturally, this isn't something that _can_ happen on x86_64.
	 * It ~could~ happen on i386, but I very much doubt that there is any justification
	 * as to why it should.
	 *
	 * ================= Documented origin =================
	 *  ssort()  --  Fast, small, qsort()-compatible Shell sort
	 *
	 *  by Ray Gardner,  public domain   5/90
	 */
	__SIZE_TYPE__ __total_bytes, __gap;
	__total_bytes = __item_size * __item_count;
	for (__gap = 0; ++__gap < __item_count;)
		__gap *= 3;
	while ((__gap /= 3) != 0) {
		__SIZE_TYPE__ __i, __gap_bytes;
		__gap_bytes = __item_size * __gap;
		for (__i = __gap_bytes; __i < __total_bytes; __i += __item_size) {
			__SIZE_TYPE__ __j;
			for (__j = __i - __gap_bytes;; __j -= __gap_bytes) {
				__SIZE_TYPE__ __swap_index;
				__BYTE_TYPE__ __tmp, *__a, *__b;
				__a = (__BYTE_TYPE__ *)__pbase + __j;
				__b = __a + __gap_bytes;
				if ((*__compar)(__a, __b, __arg) <= 0)
					break;
				__swap_index = __item_size;
				do {
					__tmp  = *__a;
					*__a++ = *__b;
					*__b++ = __tmp;
				} while (--__swap_index);
				if (__j < __gap_bytes)
					break;
			}
		}
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qsort_r_defined
#define __local___localdep_qsort_r_defined
#define __localdep_qsort_r __LIBC_LOCAL_NAME(qsort_r)
#endif /* !__local___localdep_qsort_r_defined */
#endif /* !__local_qsort_r_defined */
