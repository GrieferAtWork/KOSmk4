/* HASH CRC-32:0x55dc3a60 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_qsort_r_defined
#define __local_qsort_r_defined 1
#include <kos/anno.h>
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#include <hybrid/__minmax.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qsort_r) __ATTR_NONNULL((1, 4)) void
(__LIBCCALL __LIBC_LOCAL_NAME(qsort_r))(void *__pbase,
                                        __SIZE_TYPE__ __item_count,
                                        __SIZE_TYPE__ __item_size,
                                        __compar_d_fn_t __cmp,
                                        void *__arg) __THROWS(...) {
#line 217 "kos/src/libc/magic/stdlib.c"
	/* DISCALIMER: The qsort() implementation below has been taken directly
	 *             from glibc (`/stdlib/qsort.c'), before being retuned and
	 *             formatted to best work with KOS.
	 *          >> For better source documentation, consult the original function!
	 */
	/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
	   This file is part of the GNU C Library.
	   Written by Douglas C. Schmidt (schmidt@ics.uci.edu).

	   The GNU C Library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.

	   The GNU C Library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.

	   You should have received a copy of the GNU Lesser General Public
	   License along with the GNU C Library; if not, see
	   <http://www.gnu.org/licenses/>.  */
#define __SWAP(__a, __b, __size) \
do{	__SIZE_TYPE__ __size = (__size); \
	__BYTE_TYPE__ *__a = (__a), *__b = (__b); \
	do{ __BYTE_TYPE__ __tmp = *__a; \
		*__a++ = *__b; \
		*__b++ = __tmp; \
	} while (--__size > 0); \
}while(0)
#define __MAX_THRESH 4
	typedef struct { __BYTE_TYPE__ *__lo, *__hi; } __stack_node;
#define __STACK_SIZE      (8*sizeof(__SIZE_TYPE__))
#define __PUSH(__low, __high)  ((void)((__top->__lo = (__low)), (__top->__hi = (__high)), ++__top))
#define __POP(__low, __high)   ((void)(--__top, (__low = __top->__lo), (__high = __top->__hi)))
#define __STACK_NOT_EMPTY (__stack < __top)
	__BYTE_TYPE__ *__base_ptr = (__BYTE_TYPE__ *)__pbase;
	__SIZE_TYPE__ const __max_thresh = __MAX_THRESH * __item_size;
	if (__item_count == 0)
		return;
	if (__item_count > __MAX_THRESH) {
		__BYTE_TYPE__ *__lo = __base_ptr;
		__BYTE_TYPE__ *__hi = &__lo[__item_size * (__item_count-1)];
		__stack_node __stack[__STACK_SIZE];
		__stack_node *__top = __stack;
		__PUSH(__NULLPTR, __NULLPTR);
		while (__STACK_NOT_EMPTY) {
			__BYTE_TYPE__ *__left_ptr;
			__BYTE_TYPE__ *__right_ptr;
			__BYTE_TYPE__ *__mid = __lo+__item_size * ((__hi-__lo) / __item_size >> 1);
			if ((*__cmp)((void *)__mid, (void *)__lo, __arg) < 0)
				__SWAP(__mid, __lo, __item_size);
			if ((*__cmp)((void *)__hi, (void *)__mid, __arg) < 0)
				__SWAP(__mid, __hi, __item_size);
			else
				goto __jump_over;
			if ((*__cmp) ((void *)__mid, (void *)__lo, __arg) < 0)
				__SWAP(__mid, __lo, __item_size);
__jump_over:
			__left_ptr  = __lo+__item_size;
			__right_ptr = __hi-__item_size;
			do {
				while ((*__cmp)((void *)__left_ptr, (void *)__mid, __arg) < 0)
					__left_ptr += __item_size;
				while ((*__cmp)((void *)__mid, (void *)__right_ptr, __arg) < 0)
					__right_ptr -= __item_size;
				if (__left_ptr < __right_ptr) {
					__SWAP(__left_ptr, __right_ptr, __item_size);
					if (__mid == __left_ptr)
						__mid = __right_ptr;
					else if (__mid == __right_ptr)
						__mid = __left_ptr;
					__left_ptr += __item_size;
					__right_ptr -= __item_size;
				} else if (__left_ptr == __right_ptr) {
					__left_ptr += __item_size;
					__right_ptr -= __item_size;
					break;
				}
			} while (__left_ptr <= __right_ptr);
			if ((__SIZE_TYPE__)(__right_ptr-__lo) <= __max_thresh) {
				if ((__SIZE_TYPE__)(__hi-__left_ptr) <= __max_thresh)
					__POP(__lo, __hi);
				else
					__lo = __left_ptr;
			} else if ((__SIZE_TYPE__)(__hi-__left_ptr) <= __max_thresh) {
				__hi = __right_ptr;
			} else if ((__right_ptr-__lo) > (__hi - __left_ptr)) {
				__PUSH(__lo, __right_ptr);
				__lo = __left_ptr;
			} else {
				__PUSH(__left_ptr, __hi);
				__hi = __right_ptr;
			}
		}
	}
	{
		__BYTE_TYPE__ *const __end_ptr = &__base_ptr[__item_size * (__item_count-1)];
		__BYTE_TYPE__ *__run_ptr, *__tmp_ptr = __base_ptr;
		__BYTE_TYPE__ *__thresh = __hybrid_min(__end_ptr, __base_ptr+__max_thresh);
		for (__run_ptr = __tmp_ptr+__item_size; __run_ptr <= __thresh; __run_ptr += __item_size) {
			if ((*__cmp) ((void *)__run_ptr, (void *)__tmp_ptr, __arg) < 0)
				__tmp_ptr = __run_ptr;
		}
		if (__tmp_ptr != __base_ptr)
			__SWAP(__tmp_ptr, __base_ptr, __item_size);
		__run_ptr = __base_ptr+__item_size;
		while ((__run_ptr += __item_size) <= __end_ptr) {
			__tmp_ptr = __run_ptr-__item_size;
			while ((*__cmp)((void *)__run_ptr, (void *)__tmp_ptr, __arg) < 0)
				__tmp_ptr -= __item_size;
			__tmp_ptr += __item_size;
			if (__tmp_ptr != __run_ptr) {
				__BYTE_TYPE__ *__trav = __run_ptr+__item_size;
				while (--__trav >= __run_ptr) {
					__BYTE_TYPE__ *__hi, *__lo, __c = *__trav;
					for (__hi = __lo = __trav; (__lo -= __item_size) >= __tmp_ptr; __hi = __lo)
						*__hi = *__lo;
					*__hi = __c;
				}
			}
		}
	}
#undef __STACK_NOT_EMPTY
#undef __POP
#undef __PUSH
#undef __STACK_SIZE
#undef __MAX_THRESH
#undef __SWAP
}
__NAMESPACE_LOCAL_END
#endif /* !__local_qsort_r_defined */
