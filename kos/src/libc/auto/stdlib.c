/* HASH CRC-32:0x3f400de4 */
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
#ifndef GUARD_LIBC_AUTO_STDLIB_C
#define GUARD_LIBC_AUTO_STDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "stdlib.h"
#include "stdio.h"

DECL_BEGIN

#ifdef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_USING(__invoke_compare_helper)
#endif /* ____invoke_compare_helper_defined */
INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtou32") uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
#line 882 "kos/src/libc/magic/stdlib.c"
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
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
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

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strto32") int32_t
NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#line 927 "kos/src/libc/magic/stdlib.c"
	u32 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libc_strtou32(nptr, endptr, base);
	return neg ? -(s32)result : (s32)result;
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtou64") uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
#line 942 "kos/src/libc/magic/stdlib.c"
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
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
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

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strto64") int64_t
NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#line 986 "kos/src/libc/magic/stdlib.c"
	u64 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libc_strtou64(nptr, endptr, base);
	return neg ? -(s64)result : (s64)result;
}

#ifndef __KERNEL__
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#include <hybrid/__minmax.h>
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.stdlib.qsort_r") void
(LIBCCALL libc_qsort_r)(void *pbase,
                        size_t item_count,
                        size_t item_size,
                        __compar_d_fn_t cmp,
                        void *arg) __THROWS(...) {
#line 221 "kos/src/libc/magic/stdlib.c"
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
#define SWAP(a, b, size) \
do{	size_t __size = (size); \
	byte_t *__a = (a), *__b = (b); \
	do{ byte_t __tmp = *__a; \
		*__a++ = *__b; \
		*__b++ = __tmp; \
	} while (--__size > 0); \
}while(0)
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

#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
INTERN WUNUSED NONNULL((1, 2, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.stdlib.bsearch_r") void *
NOTHROW_NCX(LIBCCALL libc_bsearch_r)(void const *pkey,
                                     void const *pbase,
                                     size_t item_count,
                                     size_t item_size,
                                     __compar_d_fn_t cmp,
                                     void *arg) {
#line 372 "kos/src/libc/magic/stdlib.c"
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

#ifndef ____invoke_compare_helper_defined
#define ____invoke_compare_helper_defined 1
__PRIVATE int (__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
#endif /* !____invoke_compare_helper_defined */
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.stdlib.qsort") void
(LIBCCALL libc_qsort)(void *pbase,
                      size_t item_count,
                      size_t item_size,
                      __compar_fn_t cmp) __THROWS(...) {
#line 429 "kos/src/libc/magic/stdlib.c"
	libc_qsort_r(pbase, item_count, item_size, &__invoke_compare_helper, (void *)cmp);
}

#ifndef ____invoke_compare_helper_defined
#define ____invoke_compare_helper_defined 1
__PRIVATE int (__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
#endif /* !____invoke_compare_helper_defined */
INTERN WUNUSED NONNULL((1, 2, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.stdlib.bsearch") void *
NOTHROW_NCX(LIBCCALL libc_bsearch)(void const *pkey,
                                   void const *pbase,
                                   size_t item_count,
                                   size_t item_size,
                                   __compar_fn_t cmp) {
#line 445 "kos/src/libc/magic/stdlib.c"
	return libc_bsearch_r(pkey, pbase, item_count, item_size, &__invoke_compare_helper, (void *)cmp);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.labs") long
NOTHROW(LIBCCALL libc_labs)(long x) {
#line 456 "kos/src/libc/magic/stdlib.c"
	return x < 0 ? -x : x;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.llabs") __LONGLONG
NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x) {
#line 465 "kos/src/libc/magic/stdlib.c"
	return x < 0 ? -x : x;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.ldiv") ldiv_t
NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer,
                                long denom) {
#line 474 "kos/src/libc/magic/stdlib.c"
	ldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.lldiv") lldiv_t
NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer,
                                 __LONGLONG denom) {
#line 486 "kos/src/libc/magic/stdlib.c"
	lldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.abs") int
NOTHROW(LIBCCALL libc_abs)(int x) {
#line 574 "kos/src/libc/magic/stdlib.c"
	return x < 0 ? -x : x;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.div") div_t
NOTHROW_NCX(LIBCCALL libc_div)(int numer,
                               int denom) {
#line 581 "kos/src/libc/magic/stdlib.c"
	div_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mblen") int
NOTHROW_NCX(LIBCCALL libc_mblen)(char const *s,
                                 size_t n) {
#line 622 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbtowc") int
NOTHROW_NCX(LIBCCALL libc_mbtowc)(char32_t *__restrict pwc,
                                  char const *__restrict s,
                                  size_t n) {
#line 627 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbtowc") int
NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc,
                                  char const *__restrict s,
                                  size_t n) {
#line 627 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wctomb") int
NOTHROW_NCX(LIBCCALL libc_wctomb)(char *s,
                                  char32_t wchar) {
#line 632 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wctomb") int
NOTHROW_NCX(LIBDCALL libd_wctomb)(char *s,
                                  char16_t wchar) {
#line 632 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbstowcs") size_t
NOTHROW_NCX(LIBCCALL libc_mbstowcs)(char32_t *__restrict pwcs,
                                    char const *__restrict src,
                                    size_t maxlen) {
#line 637 "kos/src/libc/magic/stdlib.c"
	size_t result;
	if (libc__mbstowcs_s(&result, pwcs, (size_t)-1, src, maxlen))
		result = 0;
	return result;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbstowcs") size_t
NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict pwcs,
                                    char const *__restrict src,
                                    size_t maxlen) {
#line 637 "kos/src/libc/magic/stdlib.c"
	size_t result;
	if (libd__mbstowcs_s(&result, pwcs, (size_t)-1, src, maxlen))
		result = 0;
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcstombs") size_t
NOTHROW_NCX(LIBCCALL libc_wcstombs)(char *__restrict s,
                                    char32_t const *__restrict pwcs,
                                    size_t n) {
#line 644 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcstombs") size_t
NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict s,
                                    char16_t const *__restrict pwcs,
                                    size_t n) {
#line 644 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.srand") void
NOTHROW(LIBCCALL libc_srand)(long seed) {
#line 725 "kos/src/libc/magic/stdlib.c"
	/* ... */
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.rand") int
NOTHROW(LIBCCALL libc_rand)(void) {
#line 731 "kos/src/libc/magic/stdlib.c"
	/* https://xkcd.com/221/ */
	return 4;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.atoi") int
NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr) {
#line 742 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_INT__ <= 4
	return (int)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.atol") long
NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr) {
#line 752 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.atoll") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr) {
#line 763 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoul") unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#line 778 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libc_strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libc_strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtol") long
NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr,
                                  char **endptr,
                                  int base) {
#line 791 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libc_strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoull") __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
#line 805 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libc_strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libc_strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoll") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
#line 816 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}

INTERN ATTR_LEAF WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.atof") double
NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr) {
#line 828 "kos/src/libc/magic/stdlib.c"
	return libc_strtod(nptr, NULL);
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtod") double
NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr,
                                  char **endptr) {
#line 833 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtof") float
NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr,
                                  char **endptr) {
#line 839 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtold") long double
NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr,
                                   char **endptr) {
#line 846 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN WUNUSED NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.gcvt") char *
NOTHROW_NCX(LIBCCALL libc_gcvt)(double val,
                                int ndigit,
                                char *buf) {
#line 1005 "kos/src/libc/magic/stdlib.c"
#ifndef DBL_NDIGIT_MAX
#if __DBL_MANT_DIG__ == 53
#define DBL_NDIGIT_MAX 17
#elif __DBL_MANT_DIG__ == 24
#define DBL_NDIGIT_MAX 9
#elif __DBL_MANT_DIG__ == 56
#define DBL_NDIGIT_MAX 18
#else
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define DBL_NDIGIT_MAX (__DBL_MANT_DIG__ / 4)
#endif
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > DBL_NDIGIT_MAX)
		ndigit = DBL_NDIGIT_MAX;
	libc_sprintf(buf, "%.*g", ndigit, val);
	return buf;
}

INTERN NONNULL((3, 4, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.ecvt_r") int
NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#line 1035 "kos/src/libc/magic/stdlib.c"
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return libc_dos_ecvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	return 0;
#endif
}

INTERN NONNULL((3, 4, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.fcvt_r") int
NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#line 1047 "kos/src/libc/magic/stdlib.c"
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return libc_dos_fcvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	return 0;
#endif
}

#include <hybrid/floatcore.h>
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.qgcvt") char *
NOTHROW_NCX(LIBCCALL libc_qgcvt)(long double val,
                                 int ndigit,
                                 char *buf) {
#line 1059 "kos/src/libc/magic/stdlib.c"
#ifndef LDBG_NDIGIT_MAX
#if __LDBL_MANT_DIG__ == 53
#define LDBG_NDIGIT_MAX 17
#elif __LDBL_MANT_DIG__ == 24
#define LDBG_NDIGIT_MAX 9
#elif __LDBL_MANT_DIG__ == 56
#define LDBG_NDIGIT_MAX 18
#else
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define LDBG_NDIGIT_MAX (__LDBL_MANT_DIG__ / 4)
#endif
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > LDBG_NDIGIT_MAX)
		ndigit = LDBG_NDIGIT_MAX;
	libc_sprintf(buf, "%.*Lg", ndigit, val);
	return buf;
}

INTERN NONNULL((3, 4, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.qecvt_r") int
NOTHROW_NCX(LIBCCALL libc_qecvt_r)(long double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#line 1081 "kos/src/libc/magic/stdlib.c"
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return libc_dos_ecvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	return 0;
#endif
}

INTERN NONNULL((3, 4, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.qfcvt_r") int
NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(long double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#line 1093 "kos/src/libc/magic/stdlib.c"
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return libc_dos_fcvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	return 0;
#endif
}

#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
INTERN WUNUSED NONNULL((3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.qecvt") char *
NOTHROW_NCX(LIBCCALL libc_qecvt)(long double val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
#line 1112 "kos/src/libc/magic/stdlib.c"
	if (libc_qecvt_r(val, ndigit, decptr, sign, __NAMESPACE_LOCAL_SYM __qcvt_buffer, sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}

#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
INTERN WUNUSED NONNULL((3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.qfcvt") char *
NOTHROW_NCX(LIBCCALL libc_qfcvt)(long double val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
#line 1129 "kos/src/libc/magic/stdlib.c"
	if (libc_qfcvt_r(val, ndigit, decptr, sign, __NAMESPACE_LOCAL_SYM __qcvt_buffer, sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.rand_r") int
NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict seed) {
#line 1199 "kos/src/libc/magic/stdlib.c"
	/* https://xkcd.com/221/ */
	return 4;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.random") long
NOTHROW_NCX(LIBCCALL libc_random)(void) {
#line 1282 "kos/src/libc/magic/stdlib.c"
	return (long)libc_rand();
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.srandom") void
NOTHROW_NCX(LIBCCALL libc_srandom)(unsigned int seed) {
#line 1286 "kos/src/libc/magic/stdlib.c"
	libc_srand((long)seed);
}

#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
INTERN WUNUSED NONNULL((3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.ecvt") char *
NOTHROW_NCX(LIBCCALL libc_ecvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
#line 1406 "kos/src/libc/magic/stdlib.c"
	if (libc_ecvt_r(val, ndigit, decptr, sign, __NAMESPACE_LOCAL_SYM __qcvt_buffer, sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}

#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
INTERN WUNUSED NONNULL((3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.fcvt") char *
NOTHROW_NCX(LIBCCALL libc_fcvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
#line 1423 "kos/src/libc/magic/stdlib.c"
	if (libc_fcvt_r(val, ndigit, decptr, sign, __NAMESPACE_LOCAL_SYM __qcvt_buffer, sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return NULL;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}

INTERN WUNUSED NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.application.options.getsubopt") int
NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp,
                                     char *const *__restrict tokens,
                                     char **__restrict valuep) {
#line 1438 "kos/src/libc/magic/stdlib.c"
	/* TODO: Implement here */
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtol_l") long
NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr,
                                    char **endptr,
                                    int base,
                                    locale_t locale) {
#line 1484 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtol(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoul_l") unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
#line 1494 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtoul(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoll_l") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
#line 1505 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtoll(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoull_l") __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
#line 1515 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtoull(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtod_l") double
NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
#line 1525 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtod(nptr, endptr);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtof_l") float
NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
#line 1532 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtof(nptr, endptr);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtold_l") long double
NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr,
                                     char **endptr,
                                     locale_t locale) {
#line 1540 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtold(nptr, endptr);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._abs64") __INT64_TYPE__
NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x) {
#line 1792 "kos/src/libc/magic/stdlib.c"
	return x < 0 ? -x : x;
}

INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.convert._atof_l") double
NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr,
                                   locale_t locale) {
#line 1802 "kos/src/libc/magic/stdlib.c"
	return libc_strtod_l(nptr, NULL, locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.convert._atoi_l") int
NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr,
                                   locale_t locale) {
#line 1808 "kos/src/libc/magic/stdlib.c"
	return (int)libc_strtol_l(nptr, NULL, 10, locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.convert._atol_l") long int
NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr,
                                   locale_t locale) {
#line 1812 "kos/src/libc/magic/stdlib.c"
	return libc_strtol_l(nptr, NULL, 10, locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.convert._atoll_l") __LONGLONG
NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr,
                                    locale_t locale) {
#line 1817 "kos/src/libc/magic/stdlib.c"
	return libc_strtoll_l(nptr, NULL, 10, locale);
}

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._byteswap_ushort") u16
NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val) {
#line 1837 "kos/src/libc/magic/stdlib.c"
	return __hybrid_bswap16(val);
}

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._byteswap_ulong") u32
NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val) {
#line 1842 "kos/src/libc/magic/stdlib.c"
	return __hybrid_bswap32(val);
}

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._byteswap_uint64") u64
NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val) {
#line 1848 "kos/src/libc/magic/stdlib.c"
	return __hybrid_bswap64(val);
}

#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__PRIVATE int (__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(((struct __invoke_compare_helper_s_data *)__arg)->__arg, __a, __b);
}
#endif /* !____invoke_compare_helper_defined */
INTERN WUNUSED NONNULL((1, 2, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.utility.bsearch_s") void *
NOTHROW_NCX(LIBCCALL libc_bsearch_s)(void const *key,
                                     void const *base,
                                     size_t nmemb,
                                     size_t size,
                                     __dos_compar_d_fn_t compar,
                                     void *arg) {
#line 1893 "kos/src/libc/magic/stdlib.c"
	struct __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return libc_bsearch_r(key, base, nmemb, size, &__invoke_compare_helper_s, &data);
}

#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__PRIVATE int (__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(((struct __invoke_compare_helper_s_data *)__arg)->__arg, __a, __b);
}
#endif /* !____invoke_compare_helper_defined */
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.utility.qsort_s") void
NOTHROW_NCX(LIBCCALL libc_qsort_s)(void *base,
                                   size_t nmemb,
                                   size_t size,
                                   __dos_compar_d_fn_t compar,
                                   void *arg) {
#line 1918 "kos/src/libc/magic/stdlib.c"
	struct __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return libc_qsort_r(base, nmemb, size, &__invoke_compare_helper_s, &data);
}

#include <parts/errno.h>
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._itoa_s") errno_t
NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val,
                                   char *buf,
                                   size_t bufsize,
                                   int radix) {
#line 1953 "kos/src/libc/magic/stdlib.c"
	char *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!bufsize--)
			return __ERANGE;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (bufsize <= (size_t)(p - buf))
		return __ERANGE;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._ltoa_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val,
                                   char *buf,
                                   size_t bufsize,
                                   int radix) {
#line 1984 "kos/src/libc/magic/stdlib.c"
	char *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!bufsize--)
			return __ERANGE;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (bufsize <= (size_t)(p - buf))
		return __ERANGE;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._ultoa_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val,
                                    char *buf,
                                    size_t bufsize,
                                    int radix) {
#line 2014 "kos/src/libc/magic/stdlib.c"
	char *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (bufsize <= (size_t)(p - buf))
		return __ERANGE;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._i64toa") char *
NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val,
                                   char *buf,
                                   int radix) {
#line 2041 "kos/src/libc/magic/stdlib.c"
	libc__i64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._ui64toa") char *
NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val,
                                    char *buf,
                                    int radix) {
#line 2048 "kos/src/libc/magic/stdlib.c"
	libc__ui64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}

#include <parts/errno.h>
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._i64toa_s") errno_t
NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t bufsize,
                                     int radix) {
#line 2057 "kos/src/libc/magic/stdlib.c"
	char *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!bufsize--)
			return __ERANGE;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (bufsize <= (size_t)(p - buf))
		return __ERANGE;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._ui64toa_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t bufsize,
                                      int radix) {
#line 2087 "kos/src/libc/magic/stdlib.c"
	char *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (bufsize <= (size_t)(p - buf))
		return __ERANGE;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._atoi64") s64
NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr) {
#line 2135 "kos/src/libc/magic/stdlib.c"
	return libc_strto64(nptr, NULL, 10);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.convert._atoi64_l") s64
NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr,
                                     locale_t locale) {
#line 2139 "kos/src/libc/magic/stdlib.c"
	return libc_strto64_l(nptr, NULL, 10, locale);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstrlen") size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str) {
#line 2147 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstrnlen") size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str,
                                      size_t maxlen) {
#line 2153 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstrlen_l") size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str,
                                       locale_t locale) {
#line 2159 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc__mbstrlen(str);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstrnlen_l") size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str,
                                        size_t maxlen,
                                        locale_t locale) {
#line 2165 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc__mbstrnlen(str, maxlen);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mblen_l") int
NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str,
                                    size_t maxlen,
                                    locale_t locale) {
#line 2171 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_mblen(str, maxlen);
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbtowc_l") int
NOTHROW_NCX(LIBCCALL libc__mbtowc_l)(char32_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
#line 2178 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_mbtowc(dst, src, srclen);
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs._mbtowc_l") int
NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
#line 2178 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_mbtowc(dst, src, srclen);
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstowcs_l") size_t
NOTHROW_NCX(LIBCCALL libc__mbstowcs_l)(char32_t *buf,
                                       char const *src,
                                       size_t maxlen,
                                       locale_t locale) {
#line 2184 "kos/src/libc/magic/stdlib.c"
	size_t result;
	if (libc__mbstowcs_s_l(&result, buf, (size_t)-1, src, maxlen, locale))
		result = 0;
	return result;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs._mbstowcs_l") size_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *buf,
                                       char const *src,
                                       size_t maxlen,
                                       locale_t locale) {
#line 2184 "kos/src/libc/magic/stdlib.c"
	size_t result;
	if (libd__mbstowcs_s_l(&result, buf, (size_t)-1, src, maxlen, locale))
		result = 0;
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstowcs_s") errno_t
NOTHROW_NCX(LIBCCALL libc__mbstowcs_s)(size_t *presult,
                                       char32_t *buf,
                                       size_t buflen,
                                       char const *src,
                                       size_t maxlen) {
#line 2193 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs._mbstowcs_s") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult,
                                       char16_t *buf,
                                       size_t buflen,
                                       char const *src,
                                       size_t maxlen) {
#line 2193 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._mbstowcs_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__mbstowcs_s_l)(size_t *presult,
                                         char32_t *buf,
                                         size_t buflen,
                                         char const *src,
                                         size_t maxlen,
                                         locale_t locale) {
#line 2199 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc__mbstowcs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs._mbstowcs_s_l") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult,
                                         char16_t *buf,
                                         size_t buflen,
                                         char const *src,
                                         size_t maxlen,
                                         locale_t locale) {
#line 2199 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd__mbstowcs_s(presult, buf, buflen, src, maxlen);
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.random.rand_s") errno_t
NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval) {
#line 2207 "kos/src/libc/magic/stdlib.c"
	if (!randval)
		return __EINVAL;
	*randval = libc_rand();
	return 0;
}
#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.random.rand_s") errno_t
NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval) {
#line 2207 "kos/src/libc/magic/stdlib.c"
	if (!randval)
		return __EINVAL;
	*randval = libc_rand();
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._wctomb_l") int
NOTHROW_NCX(LIBCCALL libc__wctomb_l)(char *buf,
                                     char32_t wc,
                                     locale_t locale) {
#line 2260 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wctomb(buf, wc);
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs._wctomb_l") int
NOTHROW_NCX(LIBDCALL libd__wctomb_l)(char *buf,
                                     char16_t wc,
                                     locale_t locale) {
#line 2260 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wctomb(buf, wc);
}

#include <parts/errno.h>
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wctomb_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    char32_t wc) {
#line 2269 "kos/src/libc/magic/stdlib.c"
	if (!presult || !buf)
		return __EINVAL;
	if (buflen < MB_CUR_MAX)
		return __ERANGE;
	*presult = libc_wctomb(buf, wc);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._wctomb_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       char32_t wc,
                                       locale_t locale) {
#line 2281 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wctomb_s(presult, buf, buflen, wc);
}

#include <parts/errno.h>
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._wcstombs_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         char32_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
#line 2289 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstombs_s(presult, buf, buflen, src, maxlen);
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs._wcstombs_l") size_t
NOTHROW_NCX(LIBCCALL libc__wcstombs_l)(char *dst,
                                       char32_t const *src,
                                       size_t maxlen,
                                       locale_t locale) {
#line 2295 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstombs(dst, src, maxlen);
}

#include <parts/errno.h>
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcstombs_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      char32_t const *src,
                                      size_t maxlen) {
#line 2303 "kos/src/libc/magic/stdlib.c"
	if (!presult || !buf || !src)
		return __EINVAL;
	if (buflen < libc_wcstombs(NULL, src, maxlen))
		return __ERANGE;
	*presult = libc_wcstombs(buf, src, maxlen);
	return 0;
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_msize") size_t
NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *mptr,
                                          size_t min_alignment,
                                          size_t offset) {
#line 2419 "kos/src/libc/magic/stdlib.c"
	(void)min_alignment;
	(void)offset;
	if (!mptr)
		return 0;
	return (size_t)(uintptr_t)((void **)mptr)[-2];
}

#include <parts/errno.h>
INTERN NONNULL((1, 5, 6))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._ecvt_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
#line 2444 "kos/src/libc/magic/stdlib.c"
	if (!buf || !decptr || !sign)
		return __EINVAL;
	libc_ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 5, 6))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._fcvt_s") errno_t
NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
#line 2454 "kos/src/libc/magic/stdlib.c"
	if (!buf || !decptr || !sign)
		return __EINVAL;
	libc_fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._gcvt_s") errno_t
NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
#line 2462 "kos/src/libc/magic/stdlib.c"
	int a, b;
	if (!buf)
		return __EINVAL;
	libc_ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atoflt") int
NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result,
                                   char const *__restrict nptr) {
#line 2476 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtof(nptr, NULL);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atoflt_l") int
NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result,
                                     char const *__restrict nptr,
                                     locale_t locale) {
#line 2482 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtof_l(nptr, NULL, locale);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atodbl") int
NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result,
                                   char __KOS_FIXED_CONST *__restrict nptr) {
#line 2490 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtod(nptr, NULL);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atodbl_l") int
NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result,
                                     char __KOS_FIXED_CONST *__restrict nptr,
                                     locale_t locale) {
#line 2498 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtod_l(nptr, NULL, locale);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atoldbl") int
NOTHROW_NCX(LIBCCALL libc__atoldbl)(long double *__restrict result,
                                    char __KOS_FIXED_CONST *__restrict nptr) {
#line 2507 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtold(nptr, NULL);
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert._atoldbl_l") int
NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(long double *__restrict result,
                                      char __KOS_FIXED_CONST *__restrict nptr,
                                      locale_t locale) {
#line 2515 "kos/src/libc/magic/stdlib.c"
	*result = libc_strtold_l(nptr, NULL, locale);
	return 0;
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._rotl") unsigned int
NOTHROW(LIBCCALL libc__rotl)(unsigned int val,
                             int shift) {
#line 2529 "kos/src/libc/magic/stdlib.c"
	return __hybrid_rol(val, shift);
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._rotr") unsigned int
NOTHROW(LIBCCALL libc__rotr)(unsigned int val,
                             int shift) {
#line 2538 "kos/src/libc/magic/stdlib.c"
	return __hybrid_ror(val, shift);
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._rotl64") u64
NOTHROW(LIBCCALL libc__rotl64)(u64 val,
                               int shift) {
#line 2548 "kos/src/libc/magic/stdlib.c"
	return __hybrid_rol64(val, shift);
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._rotr64") u64
NOTHROW(LIBCCALL libc__rotr64)(u64 val,
                               int shift) {
#line 2557 "kos/src/libc/magic/stdlib.c"
	return __hybrid_ror64(val, shift);
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._lrotl") unsigned long
NOTHROW(LIBCCALL libc__lrotl)(unsigned long val,
                              int shift) {
#line 2567 "kos/src/libc/magic/stdlib.c"
	return __hybrid_rol(val, shift);
}

#include <hybrid/__rotate.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.math.utility._lrotr") unsigned long
NOTHROW(LIBCCALL libc__lrotr)(unsigned long val,
                              int shift) {
#line 2576 "kos/src/libc/magic/stdlib.c"
	return __hybrid_ror(val, shift);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._makepath") void
NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf,
                                     char const *drive,
                                     char const *dir,
                                     char const *file,
                                     char const *ext) {
#line 2614 "kos/src/libc/magic/stdlib.c"
	libc__makepath_s(buf, (size_t)-1, drive, dir, file, ext);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._splitpath") void
NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath,
                                      char *drive,
                                      char *dir,
                                      char *file,
                                      char *ext) {
#line 2619 "kos/src/libc/magic/stdlib.c"
	libc__splitpath_s(abspath, drive, (size_t)-1, dir, (size_t)-1, file, (size_t)-1, ext, (size_t)-1);
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._makepath_s") errno_t
NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf,
                                       size_t buflen,
                                       char const *drive,
                                       char const *dir,
                                       char const *file,
                                       char const *ext) {
#line 2626 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._splitpath_s") errno_t
NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath,
                                        char *drive,
                                        size_t drivelen,
                                        char *dir,
                                        size_t dirlen,
                                        char *file,
                                        size_t filelen,
                                        char *ext,
                                        size_t extlen) {
#line 2636 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.itoa") char *
NOTHROW_NCX(LIBCCALL libc_itoa)(int val,
                                char *dst,
                                int radix) {
#line 2717 "kos/src/libc/magic/stdlib.c"
	libc__itoa_s(val, dst, (size_t)-1, radix);
	return dst;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.ltoa") char *
NOTHROW_NCX(LIBCCALL libc_ltoa)(long val,
                                char *dst,
                                int radix) {
#line 2725 "kos/src/libc/magic/stdlib.c"
	libc__ltoa_s(val, dst, (size_t)-1, radix);
	return dst;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.ultoa") char *
NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val,
                                 char *dst,
                                 int radix) {
#line 2732 "kos/src/libc/magic/stdlib.c"
	libc__ultoa_s(val, dst, (size_t)-1, radix);
	return dst;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strto64_l") s64
NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
#line 2764 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strto64(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtou64_l") u64
NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
#line 2773 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_strtou64(nptr, endptr, base);
}

#endif /* !__KERNEL__ */
DEFINE_PUBLIC_WEAK_ALIAS(strtou32, libc_strtou32);
DEFINE_PUBLIC_WEAK_ALIAS(strto32, libc_strto32);
DEFINE_PUBLIC_WEAK_ALIAS(strtou64, libc_strtou64);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoui64, libc_strtou64);
DEFINE_PUBLIC_WEAK_ALIAS(strto64, libc_strto64);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoi64, libc_strto64);
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(qsort_r, libc_qsort_r);
DEFINE_PUBLIC_WEAK_ALIAS(bsearch_r, libc_bsearch_r);
DEFINE_PUBLIC_WEAK_ALIAS(qsort, libc_qsort);
DEFINE_PUBLIC_WEAK_ALIAS(bsearch, libc_bsearch);
DEFINE_PUBLIC_WEAK_ALIAS(labs, libc_labs);
DEFINE_PUBLIC_WEAK_ALIAS(llabs, libc_llabs);
DEFINE_PUBLIC_WEAK_ALIAS(ldiv, libc_ldiv);
DEFINE_PUBLIC_WEAK_ALIAS(lldiv, libc_lldiv);
DEFINE_PUBLIC_WEAK_ALIAS(abs, libc_abs);
DEFINE_PUBLIC_WEAK_ALIAS(div, libc_div);
DEFINE_PUBLIC_WEAK_ALIAS(mblen, libc_mblen);
DEFINE_PUBLIC_WEAK_ALIAS(mbtowc, libc_mbtowc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbtowc, libd_mbtowc);
DEFINE_PUBLIC_WEAK_ALIAS(wctomb, libc_wctomb);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wctomb, libd_wctomb);
DEFINE_PUBLIC_WEAK_ALIAS(mbstowcs, libc_mbstowcs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbstowcs, libd_mbstowcs);
DEFINE_PUBLIC_WEAK_ALIAS(wcstombs, libc_wcstombs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstombs, libd_wcstombs);
DEFINE_PUBLIC_WEAK_ALIAS(srand, libc_srand);
DEFINE_PUBLIC_WEAK_ALIAS(rand, libc_rand);
DEFINE_PUBLIC_WEAK_ALIAS(atoi, libc_atoi);
DEFINE_PUBLIC_WEAK_ALIAS(atol, libc_atol);
DEFINE_PUBLIC_WEAK_ALIAS(atoll, libc_atoll);
DEFINE_PUBLIC_WEAK_ALIAS(strtoul, libc_strtoul);
DEFINE_PUBLIC_WEAK_ALIAS(strtol, libc_strtol);
DEFINE_PUBLIC_WEAK_ALIAS(strtoull, libc_strtoull);
DEFINE_PUBLIC_WEAK_ALIAS(strtouq, libc_strtoull);
DEFINE_PUBLIC_WEAK_ALIAS(strtoll, libc_strtoll);
DEFINE_PUBLIC_WEAK_ALIAS(strtoq, libc_strtoll);
DEFINE_PUBLIC_WEAK_ALIAS(atof, libc_atof);
DEFINE_PUBLIC_WEAK_ALIAS(strtod, libc_strtod);
DEFINE_PUBLIC_WEAK_ALIAS(strtof, libc_strtof);
DEFINE_PUBLIC_WEAK_ALIAS(strtold, libc_strtold);
DEFINE_PUBLIC_WEAK_ALIAS(gcvt, libc_gcvt);
DEFINE_PUBLIC_WEAK_ALIAS(_gcvt, libc_gcvt);
DEFINE_PUBLIC_WEAK_ALIAS(ecvt_r, libc_ecvt_r);
DEFINE_PUBLIC_WEAK_ALIAS(fcvt_r, libc_fcvt_r);
DEFINE_PUBLIC_WEAK_ALIAS(qgcvt, libc_qgcvt);
DEFINE_PUBLIC_WEAK_ALIAS(qecvt_r, libc_qecvt_r);
DEFINE_PUBLIC_WEAK_ALIAS(qfcvt_r, libc_qfcvt_r);
DEFINE_PUBLIC_WEAK_ALIAS(qecvt, libc_qecvt);
DEFINE_PUBLIC_WEAK_ALIAS(qfcvt, libc_qfcvt);
DEFINE_PUBLIC_WEAK_ALIAS(rand_r, libc_rand_r);
DEFINE_PUBLIC_WEAK_ALIAS(random, libc_random);
DEFINE_PUBLIC_WEAK_ALIAS(srandom, libc_srandom);
DEFINE_PUBLIC_WEAK_ALIAS(ecvt, libc_ecvt);
DEFINE_PUBLIC_WEAK_ALIAS(_ecvt, libc_ecvt);
DEFINE_PUBLIC_WEAK_ALIAS(fcvt, libc_fcvt);
DEFINE_PUBLIC_WEAK_ALIAS(_fcvt, libc_fcvt);
DEFINE_PUBLIC_WEAK_ALIAS(getsubopt, libc_getsubopt);
DEFINE_PUBLIC_WEAK_ALIAS(strtol_l, libc_strtol_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtol_l, libc_strtol_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtol_l, libc_strtol_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtod_l, libc_strtod_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtod_l, libc_strtod_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtod_l, libc_strtod_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtof_l, libc_strtof_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtof_l, libc_strtof_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtof_l, libc_strtof_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtold_l, libc_strtold_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strtold_l, libc_strtold_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtold_l, libc_strtold_l);
DEFINE_PUBLIC_WEAK_ALIAS(_abs64, libc__abs64);
DEFINE_PUBLIC_WEAK_ALIAS(_atof_l, libc__atof_l);
DEFINE_PUBLIC_WEAK_ALIAS(_atoi_l, libc__atoi_l);
DEFINE_PUBLIC_WEAK_ALIAS(_atol_l, libc__atol_l);
DEFINE_PUBLIC_WEAK_ALIAS(_atoll_l, libc__atoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_byteswap_ushort, libc__byteswap_ushort);
DEFINE_PUBLIC_WEAK_ALIAS(_byteswap_ulong, libc__byteswap_ulong);
DEFINE_PUBLIC_WEAK_ALIAS(_byteswap_uint64, libc__byteswap_uint64);
DEFINE_PUBLIC_WEAK_ALIAS(bsearch_s, libc_bsearch_s);
DEFINE_PUBLIC_WEAK_ALIAS(qsort_s, libc_qsort_s);
DEFINE_PUBLIC_WEAK_ALIAS(_itoa_s, libc__itoa_s);
DEFINE_PUBLIC_WEAK_ALIAS(_ltoa_s, libc__ltoa_s);
DEFINE_PUBLIC_WEAK_ALIAS(_ultoa_s, libc__ultoa_s);
DEFINE_PUBLIC_WEAK_ALIAS(_i64toa, libc__i64toa);
DEFINE_PUBLIC_WEAK_ALIAS(_ui64toa, libc__ui64toa);
DEFINE_PUBLIC_WEAK_ALIAS(_i64toa_s, libc__i64toa_s);
DEFINE_PUBLIC_WEAK_ALIAS(_ui64toa_s, libc__ui64toa_s);
DEFINE_PUBLIC_WEAK_ALIAS(_atoi64, libc__atoi64);
DEFINE_PUBLIC_WEAK_ALIAS(_atoi64_l, libc__atoi64_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstrlen, libc__mbstrlen);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstrnlen, libc__mbstrnlen);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstrlen_l, libc__mbstrlen_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstrnlen_l, libc__mbstrnlen_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mblen_l, libc__mblen_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mbtowc_l, libc__mbtowc_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_mbtowc_l, libd__mbtowc_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstowcs_l, libc__mbstowcs_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_mbstowcs_l, libd__mbstowcs_l);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstowcs_s, libc__mbstowcs_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_mbstowcs_s, libd__mbstowcs_s);
DEFINE_PUBLIC_WEAK_ALIAS(_mbstowcs_s_l, libc__mbstowcs_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_mbstowcs_s_l, libd__mbstowcs_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(rand_s, libc_rand_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$rand_s, libd_rand_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wctomb_l, libc__wctomb_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wctomb_l, libd__wctomb_l);
DEFINE_PUBLIC_WEAK_ALIAS(wctomb_s, libc_wctomb_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wctomb_s_l, libc__wctomb_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcstombs_s_l, libc__wcstombs_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcstombs_l, libc__wcstombs_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstombs_s, libc_wcstombs_s);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_msize, libc__aligned_msize);
DEFINE_PUBLIC_WEAK_ALIAS(_ecvt_s, libc__ecvt_s);
DEFINE_PUBLIC_WEAK_ALIAS(_fcvt_s, libc__fcvt_s);
DEFINE_PUBLIC_WEAK_ALIAS(_gcvt_s, libc__gcvt_s);
DEFINE_PUBLIC_WEAK_ALIAS(_atoflt, libc__atoflt);
DEFINE_PUBLIC_WEAK_ALIAS(_atoflt_l, libc__atoflt_l);
DEFINE_PUBLIC_WEAK_ALIAS(_atodbl, libc__atodbl);
DEFINE_PUBLIC_WEAK_ALIAS(_atodbl_l, libc__atodbl_l);
DEFINE_PUBLIC_WEAK_ALIAS(_atoldbl, libc__atoldbl);
DEFINE_PUBLIC_WEAK_ALIAS(_atoldbl_l, libc__atoldbl_l);
DEFINE_PUBLIC_WEAK_ALIAS(_rotl, libc__rotl);
DEFINE_PUBLIC_WEAK_ALIAS(_rotr, libc__rotr);
DEFINE_PUBLIC_WEAK_ALIAS(_rotl64, libc__rotl64);
DEFINE_PUBLIC_WEAK_ALIAS(_rotr64, libc__rotr64);
DEFINE_PUBLIC_WEAK_ALIAS(_lrotl, libc__lrotl);
DEFINE_PUBLIC_WEAK_ALIAS(_lrotr, libc__lrotr);
DEFINE_PUBLIC_WEAK_ALIAS(_makepath, libc__makepath);
DEFINE_PUBLIC_WEAK_ALIAS(_splitpath, libc__splitpath);
DEFINE_PUBLIC_WEAK_ALIAS(_makepath_s, libc__makepath_s);
DEFINE_PUBLIC_WEAK_ALIAS(_splitpath_s, libc__splitpath_s);
DEFINE_PUBLIC_WEAK_ALIAS(itoa, libc_itoa);
DEFINE_PUBLIC_WEAK_ALIAS(_itoa, libc_itoa);
DEFINE_PUBLIC_WEAK_ALIAS(ltoa, libc_ltoa);
DEFINE_PUBLIC_WEAK_ALIAS(_ltoa, libc_ltoa);
DEFINE_PUBLIC_WEAK_ALIAS(ultoa, libc_ultoa);
DEFINE_PUBLIC_WEAK_ALIAS(_ultoa, libc_ultoa);
DEFINE_PUBLIC_WEAK_ALIAS(strto64_l, libc_strto64_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoi64_l, libc_strto64_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtou64_l, libc_strtou64_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoui64_l, libc_strtou64_l);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDLIB_C */
