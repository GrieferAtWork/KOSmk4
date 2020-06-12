/* HASH CRC-32:0x37f57200 */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_C
#define GUARD_LIBC_AUTO_STDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/stdlib.h"
#include <parts/uchar/stdlib.h>
#include <parts/uchar/wchar.h>
#include <stdio.h>
#include <string.h>
#include <uchar.h>
#include <unicode.h>
#include <wchar.h>

DECL_BEGIN

#include "stdio.h"
#ifndef __KERNEL__
#include <hybrid/__minmax.h>
INTERN ATTR_SECTION(".text.crt.utility.stdlib") NONNULL((1, 4)) void
(LIBCCALL libc_qsort_r)(void *pbase,
                        size_t item_count,
                        size_t item_size,
                        __compar_d_fn_t cmp,
                        void *arg) THROWS(...) {
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
#define SWAP(a, b, size)               \
	do {                               \
		size_t __size = (size);        \
		byte_t *__a = (a), *__b = (b); \
		do{ byte_t __tmp = *__a;       \
			*__a++ = *__b;             \
			*__b++ = __tmp;            \
		} while (--__size > 0);        \
	} __WHILE0
#define MAX_THRESH 4
	typedef struct { byte_t *lo, *hi; } stack_node;
#define STACK_SIZE      (8*sizeof(size_t))
#define PUSH(low, high)  ((void)((top->lo = (low)), (top->hi = (high)), ++top))
#define POP(low, high)   ((void)(--top, (low = top->lo), (high = top->hi)))
#define STACK_NOT_EMPTY (stack < top)
	byte_t *base_ptr = (byte_t *)pbase;
	size_t const max_thresh = MAX_THRESH * item_size;
	if (item_count == 0)
		return;
	if (item_count > MAX_THRESH) {
		byte_t *lo = base_ptr;
		byte_t *hi = &lo[item_size * (item_count-1)];
		stack_node stack[STACK_SIZE];
		stack_node *top = stack;
		PUSH(NULL, NULL);
		while (STACK_NOT_EMPTY) {
			byte_t *left_ptr;
			byte_t *right_ptr;
			byte_t *mid = lo+item_size * ((hi-lo) / item_size >> 1);
			if ((*cmp)((void *)mid, (void *)lo, arg) < 0)
				SWAP(mid, lo, item_size);
			if ((*cmp)((void *)hi, (void *)mid, arg) < 0)
				SWAP(mid, hi, item_size);
			else
				goto jump_over;
			if ((*cmp) ((void *)mid, (void *)lo, arg) < 0)
				SWAP(mid, lo, item_size);
jump_over:
			left_ptr  = lo+item_size;
			right_ptr = hi-item_size;
			do {
				while ((*cmp)((void *)left_ptr, (void *)mid, arg) < 0)
					left_ptr += item_size;
				while ((*cmp)((void *)mid, (void *)right_ptr, arg) < 0)
					right_ptr -= item_size;
				if (left_ptr < right_ptr) {
					SWAP(left_ptr, right_ptr, item_size);
					if (mid == left_ptr)
						mid = right_ptr;
					else if (mid == right_ptr)
						mid = left_ptr;
					left_ptr += item_size;
					right_ptr -= item_size;
				} else if (left_ptr == right_ptr) {
					left_ptr += item_size;
					right_ptr -= item_size;
					break;
				}
			} while (left_ptr <= right_ptr);
			if ((size_t)(right_ptr-lo) <= max_thresh) {
				if ((size_t)(hi-left_ptr) <= max_thresh)
					POP(lo, hi);
				else
					lo = left_ptr;
			} else if ((size_t)(hi-left_ptr) <= max_thresh) {
				hi = right_ptr;
			} else if ((right_ptr-lo) > (hi - left_ptr)) {
				PUSH(lo, right_ptr);
				lo = left_ptr;
			} else {
				PUSH(left_ptr, hi);
				hi = right_ptr;
			}
		}
	}
	{
		byte_t *const end_ptr = &base_ptr[item_size * (item_count-1)];
		byte_t *run_ptr, *tmp_ptr = base_ptr;
		byte_t *thresh = __hybrid_min(end_ptr, base_ptr+max_thresh);
		for (run_ptr = tmp_ptr+item_size; run_ptr <= thresh; run_ptr += item_size) {
			if ((*cmp) ((void *)run_ptr, (void *)tmp_ptr, arg) < 0)
				tmp_ptr = run_ptr;
		}
		if (tmp_ptr != base_ptr)
			SWAP(tmp_ptr, base_ptr, item_size);
		run_ptr = base_ptr+item_size;
		while ((run_ptr += item_size) <= end_ptr) {
			tmp_ptr = run_ptr-item_size;
			while ((*cmp)((void *)run_ptr, (void *)tmp_ptr, arg) < 0)
				tmp_ptr -= item_size;
			tmp_ptr += item_size;
			if (tmp_ptr != run_ptr) {
				byte_t *trav = run_ptr+item_size;
				while (--trav >= run_ptr) {
					byte_t *hi, *lo, c = *trav;
					for (hi = lo = trav; (lo -= item_size) >= tmp_ptr; hi = lo)
						*hi = *lo;
					*hi = c;
				}
			}
		}
	}
#undef STACK_NOT_EMPTY
#undef POP
#undef PUSH
#undef STACK_SIZE
#undef MAX_THRESH
#undef SWAP
}
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch_r)(void const *pkey,
                          void const *pbase,
                          size_t item_count,
                          size_t item_size,
                          __compar_d_fn_t cmp,
                          void *arg) THROWS(...) {
	/* Optimize this function with the (allowed) assumption that `pbase' is sorted according to:
	 * >> qsort_r(pbase, item_count, item_size, cmp, arg); */
	size_t lo, hi;
	lo = 0;
	hi = item_count;
	while likely(lo < hi) {
		size_t test_index;
		int difference;
		void *item_addr;
		/* Select the item right-smack in the middle of
		 * the lower and upper bound for comparison
		 * Assuming an even distribution, the chance of it being the
		 * intended item should be the greatest there, and will increase
		 * with every iteration
		 * Also: This way, the entire algorithm has a worst-case of
		 *       O(INDEX_OF_MSB(item_count))
		 *       with on 32-bit is O(32) and on 64-bit is O(64)
		 */
		test_index = (lo + hi) / 2;
		item_addr  = (byte_t *)pbase + (test_index * item_size);
		/* Check if the requested item lies above, or below the selected one */
		difference = (*cmp)(pkey, item_addr, arg);
		if (difference < 0)
			/* KEY < ITEM --> Narrow the search-area to everything below */
			hi = test_index;
		else if (difference > 0)
			/* KEY > ITEM --> Narrow the search-area to everything above */
			lo = test_index + 1;
		else {
			/* Found it! */
			return item_addr;
		}
	}
	return NULL;
}
#endif /* !__KERNEL__ */
#ifdef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_USING(__invoke_compare_helper)
#endif /* ____invoke_compare_helper_defined */
#ifndef __KERNEL__
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined 1
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
INTERN ATTR_SECTION(".text.crt.utility.stdlib") NONNULL((1, 4)) void
(LIBCCALL libc_qsort)(void *pbase,
                      size_t item_count,
                      size_t item_size,
                      __compar_fn_t cmp) THROWS(...) {
	qsort_r(pbase, item_count, item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)cmp);
}
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined 1
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch)(void const *pkey,
                        void const *pbase,
                        size_t item_count,
                        size_t item_size,
                        __compar_fn_t cmp) THROWS(...) {
	return (void *)bsearch_r(pkey, pbase, item_count, item_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	                         (void *)cmp);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_labs, libc_abs);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED long
NOTHROW(LIBCCALL libc_labs)(long x) {
	return x < 0 ? -x : x;
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_llabs, libc_abs);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_llabs, libc_labs);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_ldiv, libc_div);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED ldiv_t
NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer,
                                long denom) {
	ldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_lldiv, libc_div);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_lldiv, libc_ldiv);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED lldiv_t
NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer,
                                 __LONGLONG denom) {
	lldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_abs)(int x) {
	return x < 0 ? -x : x;
}
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED struct __div_struct
NOTHROW_NCX(LIBCCALL libc_div)(int numer,
                               int denom) {
	div_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBCCALL libc_mblen)(char const *str,
                                 size_t maxlen) {
	return mbrlen(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return mbrtoc16(pwc, str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc_mbtowc)(char32_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return mbrtoc32(pwc, str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd_wctomb)(char *str,
                                  char16_t wc) {
	return c16rtomb(str, wc, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc_wctomb)(char *str,
                                  char32_t wc) {
	return c32rtomb(str, wc, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return mbsrtoc16(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbstowcs)(char32_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return mbsrtoc32(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict dst,
                                    char16_t const *__restrict src,
                                    size_t dstlen) {
	return c16rtombs(dst, (char16_t const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcstombs)(char *__restrict dst,
                                    char32_t const *__restrict src,
                                    size_t dstlen) {
	return c32rtombs(dst, (char32_t const **)&src, dstlen, NULL);
}
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORT)
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc_abort)(void) THROWS(...) {
	_Exit(/* EXIT_FAILURE */ 1);
}
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_ABORT */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)strto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)strto64(nptr, NULL, 10);
#endif /* !(__SIZEOF_INT__ <= 4) */
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_atol, libc_atoi);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr) {
#if __SIZEOF_LONG__ <= 4
	return (long)strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)strto64(nptr, NULL, 10);
#endif /* !(__SIZEOF_LONG__ <= 4) */
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_atoll, libc_atoi);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_atoll, libc_atol);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr) {
#if __SIZEOF_LONG_LONG__
	return (__LONGLONG)strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ */
	return (__LONGLONG)strto64(nptr, NULL, 10);
#endif /* !__SIZEOF_LONG_LONG__ */
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoul, libc_strtou32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoul, libc_strtou64);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)strtou64(nptr, endptr, base);
#endif /* !(__SIZEOF_LONG__ <= 4) */
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtol, libc_strto32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtol, libc_strto64);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr,
                                  char **endptr,
                                  int base) {
#if __SIZEOF_LONG__ <= 4
	return (long)strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)strto64(nptr, endptr, base);
#endif /* !(__SIZEOF_LONG__ <= 4) */
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoull, libc_strtou64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoull, libc_strtou32);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)strtou64(nptr, endptr, base);
#endif /* !(__SIZEOF_LONG_LONG__ <= 4) */
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoll, libc_strto64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoll, libc_strto32);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)strto64(nptr, endptr, base);
#endif /* !(__SIZEOF_LONG_LONG__ <= 4) */
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr) {
	return strtod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr,
                                  char **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr,
                                  char **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
DEFINE_INTERN_ALIAS(libc_strtold, libc_strtod);
#else /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr,
                                   char **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}
#endif /* !(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__) */
#endif /* !__KERNEL__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
	u32 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	u32 result;
	bool neg = false;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = strtou32(nptr, endptr, base);
	return neg ? -(s32)result : (s32)result;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
	u64 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	u64 result;
	bool neg = false;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = strtou64(nptr, endptr, base);
	return neg ? -(s64)result : (s64)result;
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	(void)locale;
	return strtou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	(void)locale;
	return strto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	(void)locale;
	return strtou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	(void)locale;
	return strto64(nptr, endptr, base);
}
#include <hybrid/floatcore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_gcvt)(double val,
                                int ndigit,
                                char *buf) {
#ifndef DBL_NDIGIT_MAX
#if __DBL_MANT_DIG__ == 53
#define DBL_NDIGIT_MAX 17
#elif __DBL_MANT_DIG__ == 24
#define DBL_NDIGIT_MAX 9
#elif __DBL_MANT_DIG__ == 56
#define DBL_NDIGIT_MAX 18
#else /* ... */
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define DBL_NDIGIT_MAX (__DBL_MANT_DIG__ / 4)
#endif /* !... */
#endif /* !DBL_NDIGIT_MAX */
	if (ndigit > DBL_NDIGIT_MAX)
		ndigit = DBL_NDIGIT_MAX;
	sprintf(buf, "%.*g", ndigit, val);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return dos_ecvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return dos_fcvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
#include <hybrid/floatcore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_qgcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 char *buf) {
#ifndef LDBG_NDIGIT_MAX
#if __LDBL_MANT_DIG__ == 53
#define LDBG_NDIGIT_MAX 17
#elif __LDBL_MANT_DIG__ == 24
#define LDBG_NDIGIT_MAX 9
#elif __LDBL_MANT_DIG__ == 56
#define LDBG_NDIGIT_MAX 18
#else /* ... */
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define LDBG_NDIGIT_MAX (__LDBL_MANT_DIG__ / 4)
#endif /* !... */
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > LDBG_NDIGIT_MAX)
		ndigit = LDBG_NDIGIT_MAX;
	sprintf(buf, "%.*Lg", ndigit, val);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_qecvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return dos_ecvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return dos_fcvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = { 0 };
__NAMESPACE_LOCAL_END
#endif
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_qecvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	if (qecvt_r(val, ndigit, decptr, sign,
	            __NAMESPACE_LOCAL_SYM __qcvt_buffer,
	            sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = { 0 };
__NAMESPACE_LOCAL_END
#endif
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_qfcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	if (qfcvt_r(val, ndigit, decptr, sign,
	            __NAMESPACE_LOCAL_SYM __qcvt_buffer,
	            sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = { 0 };
__NAMESPACE_LOCAL_END
#endif
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_ecvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	if (ecvt_r(val, ndigit, decptr, sign,
	           __NAMESPACE_LOCAL_SYM __qcvt_buffer,
	           sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = { 0 };
__NAMESPACE_LOCAL_END
#endif
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_fcvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	if (fcvt_r(val, ndigit, decptr, sign,
	           __NAMESPACE_LOCAL_SYM __qcvt_buffer,
	           sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}
INTERN ATTR_SECTION(".text.crt.application.options") WUNUSED NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp,
                                     char *const *__restrict tokens,
                                     char **__restrict valuep) {
	unsigned int i;
	char *option, *nextopt;
	size_t option_len;
	option  = *optionp;
	*valuep = NULL;
	/* Find the next option */
	nextopt = strchr(option, ',');
	if (nextopt) {
		option_len = (size_t)(nextopt - option);
		*nextopt++ = '\0';
	} else {
		option_len = strlen(option);
		nextopt = option + option_len;
	}
	*optionp = nextopt;
	for (i = 0; tokens[i]; ++i) {
		size_t toklen = strlen(tokens[i]);
		/* Check if this token is matches the found option */
		if (memcmp(tokens[i], option, toklen * sizeof(char)) != 0)
			continue;
		/* Deal with a potential option value. */
		if (option[toklen] == '=') {
			*valuep = option + toklen + 1;
		} else {
			/* Make sure that the option doesn't keep on going */
			if (option[toklen] != 0)
				continue;
		}
		return (int)i;
	}
	/* Not found (return the whole `name[=value]' string) */
	*valuep = option;
	return -1;
}
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtol_l, libc_strto32_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtol_l, libc_strto64_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr,
                                    char **endptr,
                                    int base,
                                    locale_t locale) {
	(void)locale;
	return strtol(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoul_l, libc_strtou32_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoul_l, libc_strtou64_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	(void)locale;
	return strtoul(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoll_l, libc_strto64_l);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoll_l, libc_strto32_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	(void)locale;
	return strtoll(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoull_l, libc_strtou64_l);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoull_l, libc_strtou32_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	(void)locale;
	return strtoull(nptr, endptr, base);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return strtod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) float
NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return strtof(nptr, endptr);
}
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
DEFINE_INTERN_ALIAS(libc_strtold_l, libc_strtod_l);
#else /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr,
                                     char **endptr,
                                     locale_t locale) {
	(void)locale;
	return strtold(nptr, endptr);
}
#endif /* !(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__) */
#include <local/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.dos.application.init") errno_t
NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue) {
	*pvalue = __LOCAL_program_invocation_name;
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue) {
	*pvalue = *__p__c16pgmptr();
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") errno_t
NOTHROW_NCX(LIBKCALL libc__get_wpgmptr)(char32_t **pvalue) {
	*pvalue = *__p__c32pgmptr();
	return EOK;
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__abs64, libc_abs);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__abs64, libc_llabs);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED __INT64_TYPE__
NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return strtod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return (int)strtol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__atol_l, libc__atoi_l);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return strtol_l(nptr, NULL, 10, locale);
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc__atoll_l, libc__atol_l);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__atoll_l, libc__atoi_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr,
                                    locale_t locale) {
	return strtoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u16
NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val) {
	return __hybrid_bswap16(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u32
NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val) {
	return __hybrid_bswap32(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u64
NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val) {
	return __hybrid_bswap64(val);
}
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch_s)(void const *key,
                          void const *base,
                          size_t nmemb,
                          size_t size,
                          __dos_compar_d_fn_t compar,
                          void *arg) THROWS(...) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return (void *)bsearch_r(key, base, nmemb, size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	                         &data);
}
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 4)) void
(LIBCCALL libc_qsort_s)(void *base,
                        size_t nmemb,
                        size_t size,
                        __dos_compar_d_fn_t compar,
                        void *arg) THROWS(...) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return qsort_r(base, nmemb, size,
	               &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	               &data);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	char *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__ltoa_s, libc__itoa_s);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	char *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val,
                                    char *buf,
                                    size_t buflen,
                                    int radix) {
	char *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa, libc_itoa);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa, libc_ltoa);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val,
                                   char *buf,
                                   int radix) {
	_i64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* !... */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__ui64toa, libc_ultoa);
#else /* __SIZEOF_LONG__ == 8 */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val,
                                    char *buf,
                                    int radix) {
	_ui64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* !(__SIZEOF_LONG__ == 8) */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa_s, libc__ltoa_s);
#elif __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa_s, libc__itoa_s);
#else /* ... */
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t buflen,
                                     int radix) {
	char *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* !... */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__ui64toa_s, libc__ultoa_s);
#else /* __SIZEOF_LONG__ == 8 */
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t buflen,
                                      int radix) {
	char *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* !(__SIZEOF_LONG__ == 8) */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atoi);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atol);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atoll);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr) {
	return strto64(nptr, NULL, 10);
}
#endif /* !... */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atoi_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atol_l);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atoll_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr,
                                     locale_t locale) {
	return strto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str) {
	size_t result = 0;
	while (unicode_readutf8((char const **)&str))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str,
                                      size_t maxlen) {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str,
                                       locale_t locale) {
	(void)locale;
	return _mbstrlen(str);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str,
                                        size_t maxlen,
                                        locale_t locale) {
	(void)locale;
	return _mbstrnlen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str,
                                    size_t maxlen,
                                    locale_t locale) {
	(void)locale;
	return mblen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
	(void)locale;
	return mbtoc16(dst, src, srclen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc__mbtowc_l)(char32_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
	(void)locale;
	return mbtoc32(dst, src, srclen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *dst,
                                       char const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return mbstoc16s(dst, src, dstlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_l)(char32_t *dst,
                                       char const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return mbstoc32s(dst, src, dstlen);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult,
                                       char16_t *dst,
                                       size_t dstsize,
                                       char const *src,
                                       size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = mbstoc16s(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_s)(size_t *presult,
                                       char32_t *dst,
                                       size_t dstsize,
                                       char const *src,
                                       size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = mbstoc32s(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult,
                                         char16_t *dst,
                                         size_t dstsize,
                                         char const *src,
                                         size_t dstlen,
                                         locale_t locale) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = _mbstoc16s_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_s_l)(size_t *presult,
                                         char32_t *dst,
                                         size_t dstsize,
                                         char const *src,
                                         size_t dstlen,
                                         locale_t locale) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = _mbstoc32s_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval) {
	if (!randval) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	*randval = rand();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd__wctomb_l)(char *buf,
                                     char16_t wc,
                                     locale_t locale) {
	(void)locale;
	return c16tomb(buf, wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc__wctomb_l)(char *buf,
                                     char32_t wc,
                                     locale_t locale) {
	(void)locale;
	return c32tomb(buf, wc);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    wchar_t wc) {
	if (!presult || !buf) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen < MB_CUR_MAX) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	*presult = wctomb(buf, wc);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       wchar_t wc,
                                       locale_t locale) {
	(void)locale;
	return wctomb_s(presult, buf, buflen, wc);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         wchar_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return wcstombs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__wcstombs_l)(char *dst,
                                       wchar_t const *src,
                                       size_t maxlen,
                                       locale_t locale) {
	(void)locale;
	return wcstombs(dst, src, maxlen);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      wchar_t const *src,
                                      size_t maxlen) {
	if (!presult || !buf || !src) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen < wcstombs(NULL, src, maxlen)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	*presult = wcstombs(buf, src, maxlen);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes,
                                           size_t min_alignment) {
	void *result = malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1);
	if (result) {
		void *base = (void *)(((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1));
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes,
                                                  size_t min_alignment,
                                                  size_t offset) {
	void *result;
	offset &= (min_alignment - 1);
	result = malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1 + (min_alignment - offset));
	if (result) {
		void *base = (void *)((((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1)) + offset);
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr,
                                            size_t newsize,
                                            size_t min_alignment) {
	void *result;
	result = _aligned_malloc(newsize, min_alignment);
	if (result && aligned_mallptr) {
		size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr,
                                             size_t count,
                                             size_t num_bytes,
                                             size_t min_alignment) {
	void *result;
	num_bytes *= count;
	result = _aligned_malloc(num_bytes, min_alignment);
	if (result) {
		size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		memset((byte_t *)result + temp, 0, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr,
                                                   size_t newsize,
                                                   size_t min_alignment,
                                                   size_t offset) {
	void *result;
	result = _aligned_offset_malloc(newsize, min_alignment, offset);
	if (result) {
		size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr,
                                                    size_t count,
                                                    size_t num_bytes,
                                                    size_t min_alignment,
                                                    size_t offset) {
	void *result;
	num_bytes *= count;
	result = _aligned_offset_malloc(num_bytes, min_alignment, offset);
	if (result) {
		size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		memset((byte_t *)result + temp, 0, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr,
                                          size_t min_alignment,
                                          size_t offset) {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return (size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}
INTERN ATTR_SECTION(".text.crt.dos.heap") void
NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr) {
	if (aligned_mallptr)
		free(((void **)aligned_mallptr)[-1]);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
	int a, b;
	if (!buf)
		return __EINVAL;
	ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result,
                                   char const *__restrict nptr) {
	*result = strtof(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result,
                                     char const *__restrict nptr,
                                     locale_t locale) {
	*result = strtof_l(nptr, NULL, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result,
                                   char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtod(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result,
                                     char __KOS_FIXED_CONST *__restrict nptr,
                                     locale_t locale) {
	*result = strtod_l(nptr, NULL, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoldbl)(__LONGDOUBLE *__restrict result,
                                    char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtold(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(__LONGDOUBLE *__restrict result,
                                      char __KOS_FIXED_CONST *__restrict nptr,
                                      locale_t locale) {
	*result = strtold_l(nptr, NULL, locale);
	return 0;
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotl)(unsigned int val,
                             int shift) {
	return __hybrid_rol(val, shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotr)(unsigned int val,
                             int shift) {
	return __hybrid_ror(val, shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBCCALL libc__rotl64)(u64 val,
                               int shift) {
	return __hybrid_rol64(val, shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBCCALL libc__rotr64)(u64 val,
                               int shift) {
	return __hybrid_ror64(val, shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotl)(unsigned long val,
                              int shift) {
	return __hybrid_rol(val, shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotr)(unsigned long val,
                              int shift) {
	return __hybrid_ror(val, shift);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") errno_t
NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname,
                                     char const *val) {
	return setenv(varname, val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1, 2, 3)) void
NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file,
                                      char const *envvar,
                                      char *__restrict resultpath) {
	_searchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf,
                                     char const *drive,
                                     char const *dir,
                                     char const *file,
                                     char const *ext) {
	_makepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath,
                                      char *drive,
                                      char *dir,
                                      char *file,
                                      char *ext) {
	_splitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf,
                                       size_t buflen,
                                       char const *drive,
                                       char const *dir,
                                       char const *file,
                                       char const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char *)mempcpyc(buf, p, n, sizeof(char)); \
	} __WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	} __WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = strlen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = strlen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = strlen(ext);
		if (*ext != ':')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
#undef path_putn
#undef path_putc
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath,
                                        char *drive,
                                        size_t drivelen,
                                        char *dir,
                                        size_t dirlen,
                                        char *file,
                                        size_t filelen,
                                        char *ext,
                                        size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				memcpyc(drive, abspath, len, sizeof(char));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			memcpyc(dir, abspath, last_slash, sizeof(char));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		memcpyc(file, abspath + last_slash, len, sizeof(char));
		file[len] = 0;
	}
	return 0;
err_inval:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
err_range:
#ifdef ERANGE
	__libc_seterrno(ERANGE);
	return ERANGE;
#else /* ERANGE */
	return 1;
#endif /* !ERANGE */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_itoa)(int val,
                                char *buf,
                                int radix) {
	_itoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_ltoa, libc_itoa);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_ltoa)(long val,
                                char *buf,
                                int radix) {
	_ltoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val,
                                 char *buf,
                                 int radix) {
	_ultoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd__wtof)(char16_t const *nptr) {
	return c16stod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc__wtof)(char32_t const *nptr) {
	return c32stod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd__wtof_l)(char16_t const *nptr,
                                   locale_t locale) {
	return c16stod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc__wtof_l)(char32_t const *nptr,
                                   locale_t locale) {
	return c32stod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__itow)(int val,
                                 char16_t *buf,
                                 int radix) {
	_itoc16_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__itow)(int val,
                                 char32_t *buf,
                                 int radix) {
	_itoc32_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ltow)(long val,
                                 char16_t *buf,
                                 int radix) {
	_ltoc16_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ltow)(long val,
                                 char32_t *buf,
                                 int radix) {
	_ltoc32_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ultow)(unsigned long val,
                                  char16_t *buf,
                                  int radix) {
	_ultoc16_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ultow)(unsigned long val,
                                  char32_t *buf,
                                  int radix) {
	_ultoc32_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__i64tow)(s64 val,
                                   char16_t *buf,
                                   int radix) {
	_i64toc16_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__i64tow)(s64 val,
                                   char32_t *buf,
                                   int radix) {
	_i64toc32_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ui64tow)(u64 val,
                                    char16_t *buf,
                                    int radix) {
	_ui64toc16_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ui64tow)(u64 val,
                                    char32_t *buf,
                                    int radix) {
	_ui64toc32_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__itow_s)(int val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {
	char16_t *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char16_t)('0' + digit) : (char16_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__itow_s)(int val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {
	char32_t *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char32_t)('0' + digit) : (char32_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ltow_s)(long val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {
	char16_t *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char16_t)('0' + digit) : (char16_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ltow_s)(long val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {
	char32_t *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char32_t)('0' + digit) : (char32_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ultow_s)(unsigned long val,
                                    char16_t *buf,
                                    size_t buflen,
                                    int radix) {
	char16_t *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char16_t)('0' + digit) : (char16_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ultow_s)(unsigned long val,
                                    char32_t *buf,
                                    size_t buflen,
                                    int radix) {
	char32_t *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char32_t)('0' + digit) : (char32_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__i64tow_s)(s64 val,
                                     char16_t *buf,
                                     size_t buflen,
                                     int radix) {
	char16_t *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char16_t)('0' + digit) : (char16_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__i64tow_s)(s64 val,
                                     char32_t *buf,
                                     size_t buflen,
                                     int radix) {
	char32_t *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char32_t)('0' + digit) : (char32_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ui64tow_s)(u64 val,
                                      char16_t *buf,
                                      size_t buflen,
                                      int radix) {
	char16_t *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char16_t)('0' + digit) : (char16_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ui64tow_s)(u64 val,
                                      char32_t *buf,
                                      size_t buflen,
                                      int radix) {
	char32_t *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char32_t)('0' + digit) : (char32_t)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64)(char16_t const *__restrict nptr) {
	return c16sto64(nptr, NULL, 10);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64)(char32_t const *__restrict nptr) {
	return c32sto64(nptr, NULL, 10);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__wtoi_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)c16stol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc__wtoi_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)c32stol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBDCALL libd__wtol_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return c16stol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__wtol_l, libc__wtoi_l);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBKCALL libc__wtol_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return c32stol_l(nptr, NULL, 10, locale);
}
#endif /* !(__SIZEOF_LONG__ == __SIZEOF_INT__) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64_l)(char16_t const *__restrict nptr,
                                     locale_t locale) {
	return c16sto64_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtoi_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtol_l);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtoll_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64_l)(char32_t const *__restrict nptr,
                                     locale_t locale) {
	return c32sto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd__wtoll_l)(char16_t const *__restrict nptr,
                                    locale_t locale) {
	return c16stoll_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__wtoll_l, libc__wtoi_l);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc__wtoll_l, libc__wtol_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc__wtoll_l)(char32_t const *__restrict nptr,
                                    locale_t locale) {
	return c32stoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(qsort_r, libc_qsort_r);
DEFINE_PUBLIC_ALIAS(bsearch_r, libc_bsearch_r);
DEFINE_PUBLIC_ALIAS(qsort, libc_qsort);
DEFINE_PUBLIC_ALIAS(bsearch, libc_bsearch);
DEFINE_PUBLIC_ALIAS(labs, libc_labs);
DEFINE_PUBLIC_ALIAS(llabs, libc_llabs);
DEFINE_PUBLIC_ALIAS(ldiv, libc_ldiv);
DEFINE_PUBLIC_ALIAS(lldiv, libc_lldiv);
DEFINE_PUBLIC_ALIAS(abs, libc_abs);
DEFINE_PUBLIC_ALIAS(div, libc_div);
DEFINE_PUBLIC_ALIAS(mblen, libc_mblen);
DEFINE_PUBLIC_ALIAS(DOS$mbtowc, libd_mbtowc);
DEFINE_PUBLIC_ALIAS(mbtowc, libc_mbtowc);
DEFINE_PUBLIC_ALIAS(DOS$wctomb, libd_wctomb);
DEFINE_PUBLIC_ALIAS(wctomb, libc_wctomb);
DEFINE_PUBLIC_ALIAS(DOS$mbstowcs, libd_mbstowcs);
DEFINE_PUBLIC_ALIAS(mbstowcs, libc_mbstowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcstombs, libd_wcstombs);
DEFINE_PUBLIC_ALIAS(wcstombs, libc_wcstombs);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORT)
DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort);
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort);
DEFINE_PUBLIC_ALIAS(abort, libc_abort);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_ABORT */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(atoi, libc_atoi);
DEFINE_PUBLIC_ALIAS(atol, libc_atol);
DEFINE_PUBLIC_ALIAS(atoll, libc_atoll);
DEFINE_PUBLIC_ALIAS(strtoul, libc_strtoul);
DEFINE_PUBLIC_ALIAS(strtol, libc_strtol);
DEFINE_PUBLIC_ALIAS(strtouq, libc_strtoull);
DEFINE_PUBLIC_ALIAS(strtoull, libc_strtoull);
DEFINE_PUBLIC_ALIAS(strtoq, libc_strtoll);
DEFINE_PUBLIC_ALIAS(strtoll, libc_strtoll);
DEFINE_PUBLIC_ALIAS(atof, libc_atof);
DEFINE_PUBLIC_ALIAS(strtod, libc_strtod);
DEFINE_PUBLIC_ALIAS(strtof, libc_strtof);
DEFINE_PUBLIC_ALIAS(strtold, libc_strtold);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strtou32, libc_strtou32);
DEFINE_PUBLIC_ALIAS(strto32, libc_strto32);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_strtoui64, libc_strtou64);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strtou64, libc_strtou64);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_strtoi64, libc_strto64);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strto64, libc_strto64);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strtou32_l, libc_strtou32_l);
DEFINE_PUBLIC_ALIAS(strto32_l, libc_strto32_l);
DEFINE_PUBLIC_ALIAS(_strtoui64_l, libc_strtou64_l);
DEFINE_PUBLIC_ALIAS(strtou64_l, libc_strtou64_l);
DEFINE_PUBLIC_ALIAS(_strtoi64_l, libc_strto64_l);
DEFINE_PUBLIC_ALIAS(strto64_l, libc_strto64_l);
DEFINE_PUBLIC_ALIAS(_gcvt, libc_gcvt);
DEFINE_PUBLIC_ALIAS(gcvt, libc_gcvt);
DEFINE_PUBLIC_ALIAS(ecvt_r, libc_ecvt_r);
DEFINE_PUBLIC_ALIAS(fcvt_r, libc_fcvt_r);
DEFINE_PUBLIC_ALIAS(qgcvt, libc_qgcvt);
DEFINE_PUBLIC_ALIAS(qecvt_r, libc_qecvt_r);
DEFINE_PUBLIC_ALIAS(qfcvt_r, libc_qfcvt_r);
DEFINE_PUBLIC_ALIAS(_ecvt, libc_qecvt);
DEFINE_PUBLIC_ALIAS(qecvt, libc_qecvt);
DEFINE_PUBLIC_ALIAS(_fcvt, libc_qfcvt);
DEFINE_PUBLIC_ALIAS(qfcvt, libc_qfcvt);
DEFINE_PUBLIC_ALIAS(_ecvt, libc_ecvt);
DEFINE_PUBLIC_ALIAS(ecvt, libc_ecvt);
DEFINE_PUBLIC_ALIAS(_ecvt, libc_fcvt);
DEFINE_PUBLIC_ALIAS(fcvt, libc_fcvt);
DEFINE_PUBLIC_ALIAS(getsubopt, libc_getsubopt);
DEFINE_PUBLIC_ALIAS(_strtol_l, libc_strtol_l);
DEFINE_PUBLIC_ALIAS(__strtol_l, libc_strtol_l);
DEFINE_PUBLIC_ALIAS(strtol_l, libc_strtol_l);
DEFINE_PUBLIC_ALIAS(_strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_ALIAS(__strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_ALIAS(strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_ALIAS(_strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_ALIAS(__strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_ALIAS(strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_ALIAS(_strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_ALIAS(__strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_ALIAS(strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_ALIAS(_strtod_l, libc_strtod_l);
DEFINE_PUBLIC_ALIAS(__strtod_l, libc_strtod_l);
DEFINE_PUBLIC_ALIAS(strtod_l, libc_strtod_l);
DEFINE_PUBLIC_ALIAS(_strtof_l, libc_strtof_l);
DEFINE_PUBLIC_ALIAS(__strtof_l, libc_strtof_l);
DEFINE_PUBLIC_ALIAS(strtof_l, libc_strtof_l);
DEFINE_PUBLIC_ALIAS(_strtold_l, libc_strtold_l);
DEFINE_PUBLIC_ALIAS(__strtold_l, libc_strtold_l);
DEFINE_PUBLIC_ALIAS(strtold_l, libc_strtold_l);
DEFINE_PUBLIC_ALIAS(_get_pgmptr, libc__get_pgmptr);
DEFINE_PUBLIC_ALIAS(DOS$_get_wpgmptr, libd__get_wpgmptr);
DEFINE_PUBLIC_ALIAS(_get_wpgmptr, libc__get_wpgmptr);
DEFINE_PUBLIC_ALIAS(_abs64, libc__abs64);
DEFINE_PUBLIC_ALIAS(_atof_l, libc__atof_l);
DEFINE_PUBLIC_ALIAS(_atoi_l, libc__atoi_l);
DEFINE_PUBLIC_ALIAS(_atol_l, libc__atol_l);
DEFINE_PUBLIC_ALIAS(_atoll_l, libc__atoll_l);
DEFINE_PUBLIC_ALIAS(_byteswap_ushort, libc__byteswap_ushort);
DEFINE_PUBLIC_ALIAS(_byteswap_ulong, libc__byteswap_ulong);
DEFINE_PUBLIC_ALIAS(_byteswap_uint64, libc__byteswap_uint64);
DEFINE_PUBLIC_ALIAS(bsearch_s, libc_bsearch_s);
DEFINE_PUBLIC_ALIAS(qsort_s, libc_qsort_s);
DEFINE_PUBLIC_ALIAS(_itoa_s, libc__itoa_s);
DEFINE_PUBLIC_ALIAS(_ltoa_s, libc__ltoa_s);
DEFINE_PUBLIC_ALIAS(_ultoa_s, libc__ultoa_s);
DEFINE_PUBLIC_ALIAS(_i64toa, libc__i64toa);
DEFINE_PUBLIC_ALIAS(_ui64toa, libc__ui64toa);
DEFINE_PUBLIC_ALIAS(_i64toa_s, libc__i64toa_s);
DEFINE_PUBLIC_ALIAS(_ui64toa_s, libc__ui64toa_s);
DEFINE_PUBLIC_ALIAS(_atoi64, libc__atoi64);
DEFINE_PUBLIC_ALIAS(_atoi64_l, libc__atoi64_l);
DEFINE_PUBLIC_ALIAS(_mbstrlen, libc__mbstrlen);
DEFINE_PUBLIC_ALIAS(_mbstrnlen, libc__mbstrnlen);
DEFINE_PUBLIC_ALIAS(_mbstrlen_l, libc__mbstrlen_l);
DEFINE_PUBLIC_ALIAS(_mbstrnlen_l, libc__mbstrnlen_l);
DEFINE_PUBLIC_ALIAS(_mblen_l, libc__mblen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbtowc_l, libd__mbtowc_l);
DEFINE_PUBLIC_ALIAS(_mbtowc_l, libc__mbtowc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_l, libd__mbstowcs_l);
DEFINE_PUBLIC_ALIAS(_mbstowcs_l, libc__mbstowcs_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_s, libd__mbstowcs_s);
DEFINE_PUBLIC_ALIAS(_mbstowcs_s, libc__mbstowcs_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_s_l, libd__mbstowcs_s_l);
DEFINE_PUBLIC_ALIAS(_mbstowcs_s_l, libc__mbstowcs_s_l);
DEFINE_PUBLIC_ALIAS(rand_s, libc_rand_s);
DEFINE_PUBLIC_ALIAS(DOS$_wctomb_l, libd__wctomb_l);
DEFINE_PUBLIC_ALIAS(_wctomb_l, libc__wctomb_l);
DEFINE_PUBLIC_ALIAS(wctomb_s, libc_wctomb_s);
DEFINE_PUBLIC_ALIAS(_wctomb_s_l, libc__wctomb_s_l);
DEFINE_PUBLIC_ALIAS(_wcstombs_s_l, libc__wcstombs_s_l);
DEFINE_PUBLIC_ALIAS(_wcstombs_l, libc__wcstombs_l);
DEFINE_PUBLIC_ALIAS(wcstombs_s, libc_wcstombs_s);
DEFINE_PUBLIC_ALIAS(_aligned_malloc, libc__aligned_malloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_malloc, libc__aligned_offset_malloc);
DEFINE_PUBLIC_ALIAS(_aligned_realloc, libc__aligned_realloc);
DEFINE_PUBLIC_ALIAS(_aligned_recalloc, libc__aligned_recalloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_realloc, libc__aligned_offset_realloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_recalloc, libc__aligned_offset_recalloc);
DEFINE_PUBLIC_ALIAS(_aligned_msize, libc__aligned_msize);
DEFINE_PUBLIC_ALIAS(_aligned_free, libc__aligned_free);
DEFINE_PUBLIC_ALIAS(_ecvt_s, libc__ecvt_s);
DEFINE_PUBLIC_ALIAS(_fcvt_s, libc__fcvt_s);
DEFINE_PUBLIC_ALIAS(_gcvt_s, libc__gcvt_s);
DEFINE_PUBLIC_ALIAS(_atoflt, libc__atoflt);
DEFINE_PUBLIC_ALIAS(_atoflt_l, libc__atoflt_l);
DEFINE_PUBLIC_ALIAS(_atodbl, libc__atodbl);
DEFINE_PUBLIC_ALIAS(_atodbl_l, libc__atodbl_l);
DEFINE_PUBLIC_ALIAS(_atoldbl, libc__atoldbl);
DEFINE_PUBLIC_ALIAS(_atoldbl_l, libc__atoldbl_l);
DEFINE_PUBLIC_ALIAS(_rotl, libc__rotl);
DEFINE_PUBLIC_ALIAS(_rotr, libc__rotr);
DEFINE_PUBLIC_ALIAS(_rotl64, libc__rotl64);
DEFINE_PUBLIC_ALIAS(_rotr64, libc__rotr64);
DEFINE_PUBLIC_ALIAS(_lrotl, libc__lrotl);
DEFINE_PUBLIC_ALIAS(_lrotr, libc__lrotr);
DEFINE_PUBLIC_ALIAS(_putenv_s, libc__putenv_s);
DEFINE_PUBLIC_ALIAS(_searchenv, libc__searchenv);
DEFINE_PUBLIC_ALIAS(_makepath, libc__makepath);
DEFINE_PUBLIC_ALIAS(_splitpath, libc__splitpath);
DEFINE_PUBLIC_ALIAS(_makepath_s, libc__makepath_s);
DEFINE_PUBLIC_ALIAS(_splitpath_s, libc__splitpath_s);
DEFINE_PUBLIC_ALIAS(_itoa, libc_itoa);
DEFINE_PUBLIC_ALIAS(itoa, libc_itoa);
DEFINE_PUBLIC_ALIAS(_ltoa, libc_ltoa);
DEFINE_PUBLIC_ALIAS(ltoa, libc_ltoa);
DEFINE_PUBLIC_ALIAS(_ultoa, libc_ultoa);
DEFINE_PUBLIC_ALIAS(ultoa, libc_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$_wtof, libd__wtof);
DEFINE_PUBLIC_ALIAS(_wtof, libc__wtof);
DEFINE_PUBLIC_ALIAS(DOS$_wtof_l, libd__wtof_l);
DEFINE_PUBLIC_ALIAS(_wtof_l, libc__wtof_l);
DEFINE_PUBLIC_ALIAS(DOS$_itow, libd__itow);
DEFINE_PUBLIC_ALIAS(_itow, libc__itow);
DEFINE_PUBLIC_ALIAS(DOS$_ltow, libd__ltow);
DEFINE_PUBLIC_ALIAS(_ltow, libc__ltow);
DEFINE_PUBLIC_ALIAS(DOS$_ultow, libd__ultow);
DEFINE_PUBLIC_ALIAS(_ultow, libc__ultow);
DEFINE_PUBLIC_ALIAS(DOS$_i64tow, libd__i64tow);
DEFINE_PUBLIC_ALIAS(_i64tow, libc__i64tow);
DEFINE_PUBLIC_ALIAS(DOS$_ui64tow, libd__ui64tow);
DEFINE_PUBLIC_ALIAS(_ui64tow, libc__ui64tow);
DEFINE_PUBLIC_ALIAS(DOS$_itow_s, libd__itow_s);
DEFINE_PUBLIC_ALIAS(_itow_s, libc__itow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ltow_s, libd__ltow_s);
DEFINE_PUBLIC_ALIAS(_ltow_s, libc__ltow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ultow_s, libd__ultow_s);
DEFINE_PUBLIC_ALIAS(_ultow_s, libc__ultow_s);
DEFINE_PUBLIC_ALIAS(DOS$_i64tow_s, libd__i64tow_s);
DEFINE_PUBLIC_ALIAS(_i64tow_s, libc__i64tow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ui64tow_s, libd__ui64tow_s);
DEFINE_PUBLIC_ALIAS(_ui64tow_s, libc__ui64tow_s);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi64, libd__wtoi64);
DEFINE_PUBLIC_ALIAS(_wtoi64, libc__wtoi64);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi_l, libd__wtoi_l);
DEFINE_PUBLIC_ALIAS(_wtoi_l, libc__wtoi_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtol_l, libd__wtol_l);
DEFINE_PUBLIC_ALIAS(_wtol_l, libc__wtol_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi64_l, libd__wtoi64_l);
DEFINE_PUBLIC_ALIAS(_wtoi64_l, libc__wtoi64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtoll_l, libd__wtoll_l);
DEFINE_PUBLIC_ALIAS(_wtoll_l, libc__wtoll_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDLIB_C */
