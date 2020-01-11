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

%[define_ccompat_header(cstdlib)]
%[declare_known_section(.text.crt.application.init)]
%[declare_known_section(.text.crt.glibc)]

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[define_replacement(locale_t = __locale_t)]
%[define_replacement(u8 = __UINT8_TYPE__)]
%[define_replacement(u16 = __UINT16_TYPE__)]
%[define_replacement(u32 = __UINT32_TYPE__)]
%[define_replacement(u64 = __UINT64_TYPE__)]
%[define_replacement(s8 = __INT8_TYPE__)]
%[define_replacement(s16 = __INT16_TYPE__)]
%[define_replacement(s32 = __INT32_TYPE__)]
%[define_replacement(s64 = __INT64_TYPE__)]

%(libc_auto_source)#include "stdio.h"


%{
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#ifdef __USE_MISC
#include <alloca.h>
#endif /* __USE_MISC */
#ifdef __USE_DOS
#include <xlocale.h>
#include <bits/byteswap.h>
#endif /* __USE_DOS */
#ifdef __USE_GNU
#include <xlocale.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifdef __CRT_DOS_PRIMARY
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#elif defined(__CRT_KOS_PRIMARY)
#define RAND_MAX 0x7fffffff
#elif defined(__CRT_GLC_PRIMARY)
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#elif defined(__CRT_CYG_PRIMARY)
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#else
#define RAND_MAX 0x7fff
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#ifdef __CC__

#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __WAIT_MACROS_DEFINED
#define __WAIT_MACROS_DEFINED 1
#include <bits/waitflags.h>
#include <bits/waitstatus.h>

#ifdef __USE_MISC
#if defined(__GNUC__) && !defined(__cplusplus)
#   define __WAIT_INT(status) (__extension__(((union{ __typeof__(status) __inval; int __ival; }) { .__inval = (status) }).__ival))
#else /* __GNUC__ && !__cplusplus */
#   define __WAIT_INT(status) (*(int *)&(status))
#endif /* !__GNUC__ || __cplusplus */
#ifdef __NO_ATTR_TRANSPARENT_UNION
#   define __WAIT_STATUS      void *
#   define __WAIT_STATUS_DEFN void *
#else
typedef union {
	union wait *__uptr;
	int        *__iptr;
} __WAIT_STATUS __ATTR_TRANSPARENT_UNION;
#   define __WAIT_STATUS_DEFN int *
#endif
#else /* __USE_MISC */
#   define __WAIT_INT(status)  (status)
#   define __WAIT_STATUS        int *
#   define __WAIT_STATUS_DEFN   int *
#endif /* !__USE_MISC */
#   define WEXITSTATUS(status)  __WEXITSTATUS(__WAIT_INT(status))
#   define WTERMSIG(status)     __WTERMSIG(__WAIT_INT(status))
#   define WSTOPSIG(status)     __WSTOPSIG(__WAIT_INT(status))
#   define WIFEXITED(status)    __WIFEXITED(__WAIT_INT(status))
#   define WIFSIGNALED(status)  __WIFSIGNALED(__WAIT_INT(status))
#   define WIFSTOPPED(status)   __WIFSTOPPED(__WAIT_INT(status))
#ifdef __WIFCONTINUED
#   define WIFCONTINUED(status) __WIFCONTINUED(__WAIT_INT(status))
#endif
#endif /* !__WAIT_MACROS_DEFINED */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

}%[push_macro @undef { quot rem }]%{
struct __div_struct {
	int quot;
	int rem;
};
struct __ldiv_struct {
	long quot;
	long rem;
};
#ifdef __USE_ISOC99
struct __lldiv_struct {
	__LONGLONG quot;
	__LONGLONG rem;
};
#endif /* __USE_ISOC99 */
}%[pop_macro]
%[define_replacement(div_t = struct __div_struct)]
%[define_replacement(ldiv_t = struct __ldiv_struct)]
%[define_replacement(lldiv_t = struct __lldiv_struct)]
%{

__NAMESPACE_STD_BEGIN
#ifndef __std_div_t_defined
#define __std_div_t_defined 1
typedef struct __div_struct div_t;
#endif /* !__std_div_t_defined */
#ifndef __std_ldiv_t_defined
#define __std_ldiv_t_defined 1
typedef struct __ldiv_struct ldiv_t;
#endif /* !__std_ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __std_lldiv_t_defined
#define __std_lldiv_t_defined 1
typedef struct __lldiv_struct lldiv_t;
#endif /* !__std_lldiv_t_defined */
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __div_t_defined
#define __div_t_defined 1
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined 1
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined 1
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (*__LIBCCALL __atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */

#ifdef __USE_GNU
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}

[section(.text.crt.utility.stdlib)]
[dependency_include(<hybrid/__minmax.h>)]
[decl_prefix(
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
)][throws]
qsort_r:([nonnull] void *pbase, $size_t item_count, $size_t item_size, [nonnull] __compar_d_fn_t cmp, void *arg) {
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
%{
#endif /* __USE_GNU */

#ifdef __USE_KOS
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}

[section(.text.crt.utility.stdlib)]
[decl_prefix(
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
)][ATTR_WUNUSED]
bsearch_r:([nonnull] void const *pkey, [nonnull] void const *pbase, $size_t item_count, $size_t item_size, [nonnull] __compar_d_fn_t cmp, void *arg) -> void *
	[([nonnull] void const *pkey, [nonnull] void *pbase, $size_t item_count, $size_t item_size, [nonnull] __compar_d_fn_t cmp, void *arg) -> void *]
	[([nonnull] void const *pkey, [nonnull] void const *pbase, $size_t item_count, $size_t item_size, [nonnull] __compar_d_fn_t cmp, void *arg) -> void const *]
{
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

%{
#endif /* __USE_KOS */

}
%[insert:std]
%

%(auto_source)#ifdef ____invoke_compare_helper_defined
%(auto_source)__NAMESPACE_LOCAL_USING(__invoke_compare_helper)
%(auto_source)#endif /* ____invoke_compare_helper_defined */

[section(.text.crt.utility.stdlib)]
[impl_prefix(
#ifndef ____invoke_compare_helper_defined
#define ____invoke_compare_helper_defined 1
__PRIVATE int (__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
#endif /* !____invoke_compare_helper_defined */
)][throws][std]
qsort:([nonnull] void *pbase, size_t item_count, size_t item_size, [nonnull] __compar_fn_t cmp) {
	qsort_r(pbase, item_count, item_size, &@__invoke_compare_helper@, (void *)cmp);
}

[section(.text.crt.utility.stdlib)]
[impl_prefix(
#ifndef ____invoke_compare_helper_defined
#define ____invoke_compare_helper_defined 1
__PRIVATE int (__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
#endif /* !____invoke_compare_helper_defined */
)][ATTR_WUNUSED][std]
bsearch:([nonnull] void const *pkey, [nonnull] void const *pbase, size_t item_count, size_t item_size, [nonnull] __compar_fn_t cmp) -> void *
	[([nonnull] void const *pkey, [nonnull] void *pbase, size_t item_count, size_t item_size, [nonnull] __compar_fn_t cmp) -> void *]
	[([nonnull] void const *pkey, [nonnull] void const *pbase, size_t item_count, size_t item_size, [nonnull] __compar_fn_t cmp) -> void const *]
{
	return bsearch_r(pkey, pbase, item_count, item_size, &@__invoke_compare_helper@, (void *)cmp);
}


%[default_impl_section(.text.crt.math.utility)]

[ATTR_CONST][ATTR_WUNUSED][nothrow][std][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, abs)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(llabs)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(imaxabs)]
[if(__SIZEOF_LONG__ == 8), alias(_abs64)]
labs:(long x) -> long {
	return x < 0 ? -x : x;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[ATTR_CONST][ATTR_WUNUSED][nothrow][std][crtbuiltin]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, abs)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, labs)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(imaxabs)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_abs64)]
llabs:(__LONGLONG x) -> __LONGLONG {
	return x < 0 ? -x : x;
}
%(std, c, ccompat)#endif /* __USE_ISOC99 */


/* NOTE: `div_t', `ldiv_t' and `lldiv_t' return types need to be escaped, even if
 *       the associated unescaped types are actually defined in the current scope
 *       in order to work around a g++ bug I've discovered:
 *  When running `g++ -std=c++1z' or `g++ -std=gnu++1z', and `__LIBCCALL' is defined
 *  as non-empty, g++ will see something like this as definition for `div':
 *  >> static inline
 *  >>     __attribute__((__always_inline__))
 *  >>     __attribute__((__const__))
 *  >>     __attribute__((__warn_unused_result__))
 *  >> div_t (__attribute__((__stdcall__)) div)(int __numer, int __denom) {
 *  >>     ...
 *  >> }
 *
 *  There is nothing work with this declaration, however g++ will generate an error:
 *     ```error: 'int std::div_t' redeclared as different kind of entity```
 *  With the error indicating pointing to the `)' after `div)'
 *  However, changing the declaration to not use `div_t', but `struct __div_struct'
 *  fixes the problem (NOTE: The problem also goes away if `__attribute__((__stdcall__))'
 *  were to be removed, however we can't do the later since that would break the ABI)
 *  >> static inline
 *  >>     __attribute__((__always_inline__))
 *  >>     __attribute__((__const__))
 *  >>     __attribute__((__warn_unused_result__))
 *  >> struct __div_struct (__attribute__((__stdcall__)) div)(int __numer, int __denom) {
 *  >>     ...
 *  >> }
 *
 *  g++ seems to think that the first version is trying to declare `div_t' as a
 *  variable with a c++ initializer (remember: you can declare c++ variables
 *  as `int x(42);' instead of `int x = 42;'). A point that is proven even more,
 *  as re-writing the declaration like the following also fixes the problem:
 *  >> static inline
 *  >>     __attribute__((__always_inline__))
 *  >>     __attribute__((__const__))
 *  >>     __attribute__((__warn_unused_result__))
 *  >> div_t __attribute__((__stdcall__)) div(int __numer, int __denom) {
 *  >>     ...
 *  >> }
 *
 *  However, this last version also wouldn't work for us, since that would leave
 *  the declaration of `div' vulnerable to `#define div(a, b)' macro overrides
 *  being declared prior to the header being included (which we prevent by declaring
 *  functions such that their names cannot be interpreted by function-like macros
 *  using the same name)
 *
 *  Honestly: I don't really understand why using the struct-prefixed name (`struct __div_struct')
 *  fixes the problem (Note that when leaving out the `struct' and only writing `__div_struct',
 *  a different error ```error: expected primary-expression before '__attribute__'``` occurs with
 *  is also incorrect in this scenario), however a work-around is a work-around, and I'm happy
 *  enough 
 *
 *  For reference, I've created a bug report for this problem here:
 *  https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92438
 *
 */

[ATTR_CONST][ATTR_WUNUSED][std]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, div)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(lldiv)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(imaxdiv)]
ldiv:(long numer, long denom) -> $ldiv_t {
	ldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[ATTR_CONST][ATTR_WUNUSED][std]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, div)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, ldiv)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(imaxdiv)]
lldiv:(__LONGLONG numer, __LONGLONG denom) -> $lldiv_t {
	lldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
%(std){
extern "C++" {
#ifdef __CRT_HAVE_abs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),_abs64,(__x))
#elif __has_builtin(__builtin_abs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abs)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int (__LIBCCALL abs)(int __x) { return __builtin_abs(__x); }
#else /* abs... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int (__LIBCCALL abs)(int __x) { return __x < 0 ? -__x : __x; }
#endif /* !abs... */
#ifdef __CRT_HAVE_labs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),_abs64,(__x))
#else /* lbas... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED long (__LIBCCALL abs)(long __x) { return (labs)(__x); }
#endif /* !lbas... */
#ifdef __CRT_HAVE_div
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* div... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __div_struct (__LIBCCALL div)(int __numer, int __denom) { div_t __result; __result.quot = __numer / __denom; __result.rem = __numer % __denom; return __result; }
#endif /* !div... */
#ifdef __CRT_HAVE_ldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ldiv... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct (__LIBCCALL div)(long __numer, long __denom) { return ldiv(__numer, __denom); }
#endif /* !ldiv... */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE_llabs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),_abs64,(__x))
#else /* llabs... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG (__LIBCCALL abs)(__LONGLONG __x) { return (llabs)(__x); }
#endif /* !llabs... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* lldiv... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct (__LIBCCALL div)(__LONGLONG __numer, __LONGLONG __denom) { return lldiv(__numer, __denom); }
#endif /* !lldiv... */
#endif /* __USE_ISOC99 */
} /* extern "C++" */
}
%(std)#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
[ATTR_CONST][ATTR_WUNUSED][nothrow][std][crtbuiltin]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(labs)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(llabs)]
[if(__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias(imaxabs)]
[if(__SIZEOF_INT__ == 8), alias(_abs64)]
abs:(int x) -> int {
	return x < 0 ? -x : x;
}
[ATTR_CONST][ATTR_WUNUSED][std]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(ldiv)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(lldiv)]
[if(__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias(imaxdiv)]
div:(int numer, int denom) -> struct __div_struct {
	div_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}
%(std)#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */

%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
%(std){
extern "C++" {
/* Also provide abs() for floating point types. */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST float __NOTHROW(__LIBCCALL abs)(float __x) { return __builtin_fabsf(__x); }
#else /* __builtin_fabsf && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabsf */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST float __NOTHROW(__LIBCCALL abs)(float __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabsf || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabsf */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST double __NOTHROW(__LIBCCALL abs)(double __x) { return __builtin_fabs(__x); }
#else /* __builtin_fabs && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabs */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST double __NOTHROW(__LIBCCALL abs)(double __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabs || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabs */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long double __NOTHROW(__LIBCCALL abs)(long double __x) { return __builtin_fabsl(__x); }
#else /* __builtin_fabsl && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabsl */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long double __NOTHROW(__LIBCCALL abs)(long double __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabsl || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabsl */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __COMPILER_HAVE_FLOAT128
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __float128 __NOTHROW(__LIBCCALL abs)(__float128 __x) { return __x < 0 ? -__x : __x; }
#endif /* __COMPILER_HAVE_FLOAT128 */
} /* extern "C++" */
}
%(std)#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */

[section(.text.crt.fs.environ)][std][ATTR_WUNUSED]
getenv:([nonnull] char const *varname) -> char *;

%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
[std]
mblen:([inp_opt(maxlen)] char const *str, size_t maxlen) -> int {
	return mbrlen(str, maxlen, NULL);
}

[std][wchar]
mbtowc:(wchar_t *__restrict pwc,
        [inp_opt(maxlen)] char const *__restrict str, size_t maxlen) -> int {
	return mbrtowc(pwc, str, maxlen, NULL);
}

[std][wchar]
wctomb:(char *str, wchar_t wc) -> int {
	return wcrtomb(str, wc, NULL);
}

[std][wchar]
mbstowcs:(wchar_t *__restrict dst, char const *__restrict src, size_t dstlen) -> size_t {
	return mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}

[std][wchar]
wcstombs:(char *__restrict dst, wchar_t const *__restrict src, size_t dstlen) -> size_t {
	return wcsrtombs(dst, (wchar_t const **)&src, dstlen, NULL);
}

[section(.text.crt.fs.exec.system)][cp][std][std_guard]
system:([nullable] char const *__restrict command) -> int;


%[default_impl_section(.text.crt.application.exit)]
[crtbuiltin][std][std_guard][ATTR_NORETURN][export_alias(_ZSt9terminatev, ?terminate@@YAXXZ)][throws()] abort:();
[crtbuiltin][std][std_guard][alias(quick_exit)][alias(_exit)][alias(_Exit)][ATTR_NORETURN]
[throws] exit:(int status);

%[define(DEFINE_ATEXIT_FUNC_T =
#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (*__LIBCCALL __atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */
)]

%[default_impl_section(.text.crt.sched.process)]
[decl_prefix(DEFINE_ATEXIT_FUNC_T)]
[std][alias(at_quick_exit)] atexit:([nonnull] __atexit_func_t func) -> int;
%(std, c, ccompat)#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
[std][alias(exit)][alias(_exit)][alias(_Exit)][ATTR_NORETURN][throws] quick_exit:(int status);
[decl_prefix(DEFINE_ATEXIT_FUNC_T)]
[std][alias(atexit)] at_quick_exit:([nonnull] __atexit_func_t func) -> int;
%(std, c, ccompat)#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
%(std, c, ccompat)#ifdef __USE_ISOC99
[std][alias(_exit)][alias(quick_exit)][alias(exit)]
[section(.text.crt.application.exit)]
[crtbuiltin][ATTR_NORETURN][throws()] _Exit:(int status);
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%[default_impl_section(.text.crt.heap.malloc)]
[ignore][ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC][ATTR_ALLOC_SIZE((1, 2))]
crt_calloc:(size_t count, size_t num_bytes) -> void * = calloc?;

[std_guard][std][libc][ATTR_WUNUSED]
[ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC]
[ATTR_ALLOC_SIZE((1))][noexport][crtbuiltin]
[requires($has_function(crt_calloc) || $has_function(realloc) || $has_function(memalign))]
malloc:(size_t num_bytes) -> void * {
@@if_has_function(crt_calloc)@@
	return crt_calloc(1, num_bytes);
@@elif_has_function(realloc)@@
	return realloc(NULL, num_bytes);
@@else_has_function@@
	return memalign(__LIBC_MALLOC_ALIGNMENT, num_bytes);
@@endif_has_function@@
}

[std_guard][std][libc]
[requires($has_function(malloc))]
[dependency_include(<hybrid/__overflow.h>)]
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC]
[ATTR_ALLOC_SIZE((1, 2))][crtbuiltin]
calloc:(size_t count, size_t num_bytes) -> void * {
	void *result;
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(count, num_bytes, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = malloc(total_bytes);
	if likely(result)
		memset(result, 0, total_bytes);
	return result;
}

[std_guard][std][libc]
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED]
[ATTR_ALLOC_SIZE((2))][crtbuiltin]
realloc:(void *mallptr, size_t num_bytes) -> void *;

[std_guard][std][libc][alias(cfree)][crtbuiltin]
free:(void *mallptr);


%[default_impl_section(.text.crt.random)]
[nothrow][std][user][same_impl]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(srandom)]
srand:(long seed) -> void {
	/* ... */
	(void)seed;
	COMPILER_IMPURE();
}

[nothrow][std][user][same_impl]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(random)]
rand:() -> int {
	COMPILER_IMPURE();
	/* https://xkcd.com/221/ */
	return 4;
}


%[default_impl_section(.text.crt.unicode.static.convert)]
/* Convert a string to an integer.  */
[std][ATTR_PURE][ATTR_WUNUSED]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(atol)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(atoll)]
atoi:([nonnull] char const *__restrict nptr) -> int {
#if __SIZEOF_INT__ <= 4
	return (int)strto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)strto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
[std][ATTR_PURE][ATTR_WUNUSED]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, atoi)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(atoll)]
atol:([nonnull] char const *__restrict nptr) -> long {
#if __SIZEOF_LONG__ <= 4
	return (long)strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
%#if defined(__LONGLONG) && defined(__USE_ISOC99)
[std][ATTR_PURE][ATTR_WUNUSED]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, atoi)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, atol)]
atoll:([nonnull] char const *__restrict nptr) -> __LONGLONG {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
%#endif /* __LONGLONG && __USE_ISOC99 */


[std][ATTR_LEAF]
[alt_variant_of(__SIZEOF_LONG__ == 4, strtou32)]
[alt_variant_of(__SIZEOF_LONG__ == 8, strtou64)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(strtoull, strtouq)]
[if(__SIZEOF_LONG__ == 8), alias(_strtoui64)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoumax)]
strtoul:([nonnull] char const *__restrict nptr, char **endptr, int base) -> unsigned long {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}

[std][ATTR_LEAF]
[alt_variant_of(__SIZEOF_LONG__ == 4, strto32)]
[alt_variant_of(__SIZEOF_LONG__ == 8, strto64)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(strtoll, strtoq)]
[if(__SIZEOF_LONG__ == 8), alias(_strtoi64)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoimax)]
strtol:([nonnull] char const *__restrict nptr, char **endptr, int base) -> long {
#if __SIZEOF_LONG__ <= 4
	return (long)strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}

%(std)#ifdef __ULONGLONG
%(std)#ifdef __USE_ISOC99
[std][std_guard][ATTR_LEAF][alias(strtouq)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strtou64)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strtou32)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(strtoul)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_strtoui64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoumax)]
strtoull:([nonnull] char const *__restrict nptr, char **endptr, int base) -> __ULONGLONG {
#if @__SIZEOF_LONG_LONG__@ <= 4
	return (@__ULONGLONG@)strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (@__ULONGLONG@)strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
[std][std_guard][ATTR_LEAF][alias(strtoq)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strto64)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strto32)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(strtol)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_strtoi64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoimax)]
strtoll:([nonnull] char const *__restrict nptr, char **endptr, int base) -> __LONGLONG {
#if @__SIZEOF_LONG_LONG__@ <= 4
	return (@__LONGLONG@)strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (@__LONGLONG@)strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
%(std)#endif /* __USE_ISOC99 */
%(std)#endif /* __ULONGLONG */

%(std, c, ccompat)#ifndef __NO_FPU
[std][ATTR_LEAF][ATTR_WUNUSED]
atof:([nonnull] char const *__restrict nptr) -> double {
	return strtod(nptr, NULL);
}

[std][ATTR_LEAF]
[if(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias(strtold)]
strtod:([nonnull] char const *__restrict nptr, char **endptr) -> double {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}

%(std)#ifdef __USE_ISOC99
[std_guard][std][ATTR_LEAF]
strtof:([nonnull] char const *__restrict nptr, char **endptr) -> float {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std_guard][std][ATTR_LEAF]
[alt_variant_of(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__, strtod)]
strtold:([nonnull] char const *__restrict nptr, char **endptr) -> long double {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char *)nptr;
	return 0;
}
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_ISOC99 */
%(std, c, ccompat)#endif /* !__NO_FPU */



%
%#ifdef __USE_MISC
%#ifdef __ULONGLONG
[alias(*)][attribute(*)] strtoq:(*) = strtoll;
[alias(*)][attribute(*)] strtouq:(*) = strtoull;
%#endif /* __ULONGLONG */
%#endif /* __USE_MISC */





%#ifdef __USE_KOS
[kernel][ATTR_LEAF]
[if(__SIZEOF_LONG__ == 4), alias(strtoul)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(strtoull, strtouq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtoumax)]
strtou32:([nonnull] char const *__restrict nptr, char **endptr, int base) -> $uint32_t {
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

[kernel][ATTR_LEAF]
[if(__SIZEOF_LONG__ == 4), alias(strtol)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(strtoll, strtoq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtoimax)]
strto32:([nonnull] char const *__restrict nptr, char **endptr, int base) -> $int32_t {
	u32 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = strtou32(nptr, endptr, base);
	return neg ? -(s32)result : (s32)result;
}
%#ifdef __UINT64_TYPE__
[kernel][ATTR_LEAF][alias(_strtoui64)]
[if(__SIZEOF_LONG__ == 8), alias(strtoul)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(strtoull, strtouq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtoumax)]
strtou64:([nonnull] char const *__restrict nptr, char **endptr, int base) -> $uint64_t {
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
[kernel][ATTR_LEAF][alias(_strtoi64)]
[if(__SIZEOF_LONG__ == 8), alias(strtol)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(strtoll, strtoq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtoimax)]
strto64:([nonnull] char const *__restrict nptr, char **endptr, int base) -> $int64_t {
	u64 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = strtou64(nptr, endptr, base);
	return neg ? -(s64)result : (s64)result;
}
%#endif /* __UINT64_TYPE__ */
%
%#ifdef __USE_XOPEN2K8
[ATTR_LEAF]
[if(__SIZEOF_LONG__ == 4), alias(strtoul_l, _strtoul_l, __strtoul_l)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(strtoull_l, _strtoull_l, __strtoull_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtoumax_l, _strtoumax_l, __strtoumax_l)]
strtou32_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $uint32_t {
	(void)locale;
	return strtou32(nptr, endptr, base);
}

[ATTR_LEAF]
[if(__SIZEOF_LONG__ == 4), alias(strtol_l, _strtol_l, __strtol_l)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(strtoll_l, _strtoll_l, __strtoll_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtoimax_l, _strtoimax_l, __strtoimax_l)]
strto32_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $int32_t {
	(void)locale;
	return strto32(nptr, endptr, base);
}

%#ifdef __UINT64_TYPE__
[ATTR_LEAF][alias(_strtoui64_l)]
[if(__SIZEOF_LONG__ == 8), alias(strtoul_l, _strtoul_l, __strtoul_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(strtoull_l, _strtoull_l, __strtoull_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtoumax_l, _strtoumax_l, __strtoumax_l)]
strtou64_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $uint64_t {
	(void)locale;
	return strtou64(nptr, endptr, base);
}

[ATTR_LEAF][alias(_strtoi64_l)]
[if(__SIZEOF_LONG__ == 8), alias(strtol_l, _strtol_l, __strtol_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(strtoll_l, _strtoll_l, __strtoll_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtoimax_l, _strtoimax_l, __strtoimax_l)]
strto64_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $int64_t {
	(void)locale;
	return strto64(nptr, endptr, base);
}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */
%#endif /* __USE_KOS */

%
%
%#if defined(__USE_MISC) || defined(__USE_DOS) || \
%   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
%#ifndef __NO_FPU
[ATTR_WUNUSED][alias(_gcvt)]
gcvt:(double val, int ndigit, [nonnull] char *buf) -> char * {
#ifndef DBL_NDIGIT_MAX
#if @__DBL_MANT_DIG__@ == 53
#define DBL_NDIGIT_MAX 17
#elif @__DBL_MANT_DIG__@ == 24
#define DBL_NDIGIT_MAX 9
#elif @__DBL_MANT_DIG__@ == 56
#define DBL_NDIGIT_MAX 18
#else
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define DBL_NDIGIT_MAX (@__DBL_MANT_DIG__@ / 4)
#endif
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > DBL_NDIGIT_MAX)
		ndigit = DBL_NDIGIT_MAX;
	sprintf(buf, "%.*g", ndigit, val);
	return buf;
}
%#endif /* !__NO_FPU */
%#endif /* ... */
%
%#ifdef __USE_MISC
%#ifndef __NO_FPU

[ignore] dos_ecvt_s:([nonnull] char *buf, $size_t buflen, double val, int ndigit, [nonnull] int *__restrict decptr, [nonnull] int *__restrict sign) -> errno_t = _ecvt_s?;
[ignore] dos_fcvt_s:([nonnull] char *buf, $size_t buflen, double val, int ndigit, [nonnull] int *__restrict decptr, [nonnull] int *__restrict sign) -> errno_t = _fcvt_s?;

ecvt_r:(double val, int ndigit,
        [nonnull] int *__restrict decptr,
        [nonnull] int *__restrict sign,
        [nonnull] char *__restrict buf, $size_t len) -> int {
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

fcvt_r:(double val, int ndigit,
        [nonnull] int *__restrict decptr,
        [nonnull] int *__restrict sign,
        [nonnull] char *__restrict buf, $size_t len) -> int {
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

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[impl_include(<hybrid/floatcore.h>)]
[if(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias(_gcvt)]
qgcvt:(long double val, int ndigit, [nonnull] char *buf) -> char * {
#ifndef LDBG_NDIGIT_MAX
#if @__LDBL_MANT_DIG__@ == 53
#define LDBG_NDIGIT_MAX 17
#elif @__LDBL_MANT_DIG__@ == 24
#define LDBG_NDIGIT_MAX 9
#elif @__LDBL_MANT_DIG__@ == 56
#define LDBG_NDIGIT_MAX 18
#else
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define LDBG_NDIGIT_MAX (@__LDBL_MANT_DIG__@ / 4)
#endif
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > LDBG_NDIGIT_MAX)
		ndigit = LDBG_NDIGIT_MAX;
	sprintf(buf, "%.*Lg", ndigit, val);
	return buf;
}

qecvt_r:(long double val, int ndigit,
         [nonnull] int *__restrict decptr,
         [nonnull] int *__restrict sign,
         [nonnull] char *__restrict buf, $size_t len) -> int {
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

qfcvt_r:(long double val, int ndigit,
         [nonnull] int *__restrict decptr,
         [nonnull] int *__restrict sign,
         [nonnull] char *__restrict buf, $size_t len) -> int {
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

%[define(DEFINE_QCVT_BUFFER =
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
)]


[dependency_prefix(DEFINE_QCVT_BUFFER)]
[ATTR_WUNUSED][alias(_ecvt)]
qecvt:(long double val, int ndigit,
       [nonnull] int *__restrict decptr,
       [nonnull] int *__restrict sign) -> char * {
	if (qecvt_r(val, ndigit, decptr, sign, @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@, sizeof(@__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@)))
		return NULL;
	return @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@;
}

[dependency_prefix(DEFINE_QCVT_BUFFER)]
[ATTR_WUNUSED][alias(_fcvt)]
qfcvt:(long double val, int ndigit,
       [nonnull] int *__restrict decptr,
       [nonnull] int *__restrict sign) -> char * {
	if (qfcvt_r(val, ndigit, decptr, sign, @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@, sizeof(@__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@)))
		return NULL;
	return @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

%[default_impl_section(.text.crt.random)]
%{
struct drand48_data {
	unsigned short __x[3];
	unsigned short __old_x[3];
	unsigned short __c;
	unsigned short __init;
	__ULONGLONG    __a;
};
}
%#ifndef __NO_FPU
drand48_r:([nonnull] struct drand48_data *__restrict buffer, [nonnull] double *__restrict result) -> int;
erand48_r:([nonnull] unsigned short xsubi[3], [nonnull] struct drand48_data *__restrict buffer, [nonnull] double *__restrict result) -> int;
%#endif /* !__NO_FPU */
lrand48_r:([nonnull] struct drand48_data *__restrict buffer, [nonnull] long *__restrict result) -> int;
nrand48_r:([nonnull] unsigned short xsubi[3], [nonnull] struct drand48_data *__restrict buffer, [nonnull] long *__restrict result) -> int;
mrand48_r:([nonnull] struct drand48_data *__restrict buffer, [nonnull] long *__restrict result) -> int;
jrand48_r:([nonnull] unsigned short xsubi[3], [nonnull] struct drand48_data *__restrict buffer, [nonnull] long *__restrict result) -> int;
srand48_r:(long seedval, [nonnull] struct drand48_data *buffer) -> int;
seed48_r:([nonnull] unsigned short seed16v[3], [nonnull] struct drand48_data *buffer) -> int;
lcong48_r:([nonnull] unsigned short param[7], [nonnull] struct drand48_data *buffer) -> int;

%{
}%[push_macro @undef { fptr rptr state rand_type rand_deg rand_sep end_ptr }]%{
struct random_data {
	__INT32_TYPE__ *fptr;
	__INT32_TYPE__ *rptr;
	__INT32_TYPE__ *state;
	int             rand_type;
	int             rand_deg;
	int             rand_sep;
	__INT32_TYPE__ *end_ptr;
};
}%[pop_macro]%{
}

random_r:([nonnull] struct random_data *__restrict buf, [nonnull] $int32_t *__restrict result) -> int;
srandom_r:(unsigned int seed, [nonnull] struct random_data *buf) -> int;
initstate_r:(unsigned int seed, [nonnull] char *__restrict statebuf, $size_t statelen, [nonnull] struct random_data *__restrict buf) -> int;
setstate_r:([nonnull] char *__restrict statebuf, [nonnull] struct random_data *__restrict buf) -> int;

%[default_impl_section(.text.crt.sched.process)]
%typedef void (__LIBCCALL *__on_exit_func_t)(int __status, void *__arg);
on_exit:([nonnull] __on_exit_func_t func, void *arg) -> int;

%[default_impl_section(.text.crt.fs.environ)]
clearenv:() -> int;

%[default_impl_section(.text.crt.fs.utility)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(mkstemps64)]
[ATTR_WUNUSED] mkstemps:([nonnull] char *template_, int suffixlen) -> int;
[ATTR_WUNUSED] rpmatch:([nonnull] char const *response) -> int;
%#ifdef __USE_LARGEFILE64
[alias(mkstemps)][ATTR_WUNUSED][largefile64_variant_of(mkstemps)]
mkstemps64:([nonnull] char *template_, int suffixlen) -> int;
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC */

%[default_impl_section(.text.crt.random)]
%
%
%#ifdef __USE_POSIX
[user]
rand_r:([nonnull] unsigned int *__restrict pseed) -> int {
	(void)pseed;
	COMPILER_IMPURE();
	/* https://xkcd.com/221/ */
	return 4;
}
%#endif /* __USE_POSIX */

%[default_impl_section(.text.crt.system.utility)]
%
%
%#ifdef __USE_MISC
%[insert:extern(cfree)]
%#ifndef __NO_FPU
[cp] getloadavg:(double loadavg[], int nelem) -> int;
%#endif /* !__NO_FPU */
%#endif /* __USE_MISC */

%
%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K))
%[default_impl_section(.text.crt.heap)]
%[insert:extern(valloc)]
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) */

%
%
%#ifdef __USE_XOPEN2K
%[insert:extern(posix_memalign)]
%#endif /* __USE_XOPEN2K */

%
%
%(c,std)#ifdef __USE_ISOCXX17
[ATTR_WUNUSED][ATTR_ALLOC_ALIGN(1)][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][std][guard][std_guard][crtbuiltin]
aligned_alloc:($size_t alignment, $size_t num_bytes) -> void * = memalign;
%(c,std)#endif /* __USE_ISOCXX17 */

%
%/* aligned_alloc() is defined by both c11 and c++17 */
%#ifdef __USE_ISOC11
%[insert:extern(aligned_alloc)]
%#endif /* __USE_ISOC11 */


%
%{
#ifndef MB_CUR_MAX
#ifdef __CRT_HAVE___ctype_get_mb_cur_max
__CDECLARE(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX  (__ctype_get_mb_cur_max())
#else
#define MB_CUR_MAX   7 /* == UNICODE_UTF8_CURLEN */
#endif
#endif /* !MB_CUR_MAX */
}


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
%[default_impl_section(.text.crt.random)]
%#ifndef __NO_FPU
drand48:() -> double;
%#endif /* !__NO_FPU */
lrand48:() -> long;
mrand48:() -> long;
%#ifndef __NO_FPU
erand48:([nonnull] unsigned short xsubi[3]) -> double;
%#endif /* !__NO_FPU */
nrand48:([nonnull] unsigned short xsubi[3]) -> long;
jrand48:([nonnull] unsigned short xsubi[3]) -> long;
srand48:(long seedval);
seed48:([nonnull] unsigned short seed16v[3]) -> unsigned short *;
lcong48:([nonnull] unsigned short param[7]);
%#endif /* __USE_MISC || __USE_XOPEN */

%#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
%[default_impl_section(.text.crt.fs.environ)]
[alias(_putenv)] putenv:([nonnull] char *string) -> int;
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
%[default_impl_section(.text.crt.random)][user][same_impl]
[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias(rand)]
random:() -> long {
	return (long)rand();
}
[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias(srand)][user][same_impl]
srandom:(unsigned int seed) {
	srand((long)seed);
}

initstate:(unsigned int seed, [outp(statelen)] char *statebuf, $size_t statelen) -> char *;
setstate:([nonnull] char *statebuf) -> char *;

%[default_impl_section(.text.crt.string.encrypt)]
[ATTR_WUNUSED] l64a:(long n) -> char *; /* TODO: Implement here */
[ATTR_WUNUSED][ATTR_PURE] a64l:([nonnull] char const *s) -> long; /* TODO: Implement here */

@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink()', but will also function for
@@non-symlink paths, as well as always return an absolute (unambiguous) path
@@@param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
@@                  path, or NULL to automatically `malloc()'ate and return a
@@                  buffer of sufficient size.
[section(.text.crt.fs.property)][cp][ATTR_WUNUSED]
realpath:([nonnull] char const *__restrict filename, char *resolved) -> char *;
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
%/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
% *       but it seems to be something that GLibc isn't implementing for some reason...
% *       Because of that, I didn't really know where to put this, so I put it in the
% *       same _SOURCE-block as its `realpath()' companion. */
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `bufsize' to automatically determine the required buffer size.
[section(.text.crt.fs.property)][cp][ATTR_WUNUSED]
frealpath:($fd_t fd, char *resolved, $size_t bufsize) -> char *;
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

%
%#ifdef __USE_KOS
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@@param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `bufsize' to automatically determine the required buffer size.
[section(.text.crt.fs.property)][cp][ATTR_WUNUSED]
frealpath4:($fd_t fd, char *resolved, $size_t bufsize, $atflag_t flags) -> char *;

@@Returns the absolute filesystem path for the specified file
@@When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
@@causing the pointed-to file location to be retrieved. - Otherwise, the
@@location of the link is printed instead.
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `bufsize' to automatically determine the required buffer size.
@@@param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH'
[section(.text.crt.fs.property)][cp][ATTR_WUNUSED]
frealpathat:($fd_t dirfd, [nonnull] char const *filename,
             char *resolved, $size_t bufsize, $atflag_t flags) -> char *;
%#endif /* __USE_KOS */


%
%
%#ifdef __USE_XOPEN2K
%[default_impl_section(.text.crt.fs.environ)]
[ignore] dos_putenv_s:(char const *varname, char const *val) -> int = _putenv_s?;
[requires(defined(__CRT_HAVE__putenv_s))][noexport]
setenv:(char const *varname, [nonnull] char const *val, int replace) -> int {
	if (!replace && getenv(varname))
		return 0;
	return dos_putenv_s(varname, val);
}
[dependency_include(<parts/malloca.h>)][noexport]
[requires($has_function(putenv))]
unsetenv:([nonnull] char const *varname) -> int {
	int result;
	char *copy;
	$size_t namelen;
	if (!varname)
		return -1;
	namelen = strlen(varname);
	copy = (char *)@__malloca@((namelen + 2) * sizeof(char));
	if unlikely(!copy)
		return -1;
	memcpyc(copy, varname, namelen, sizeof(char));
	copy[namelen] = '=';
	copy[namelen + 1] = '\0';
	result = putenv(copy);
	@__freea@(copy);
	return result;
}
%#endif /* __USE_XOPEN2K */

%
%
%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
%[default_impl_section(.text.crt.fs.utility)]
[guard][alias(_mktemp)][export_alias(__mktemp)]
mktemp:([nonnull] char *template_) -> char *;
%#endif


%
%
%#if defined(__USE_MISC) || defined(__USE_DOS) || \
%   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
%[default_impl_section(.text.crt.unicode.static.convert)]
%#ifndef __NO_FPU
[dependency_prefix(DEFINE_QCVT_BUFFER)]
[ATTR_WUNUSED][alias(_ecvt)]
ecvt:(double val, int ndigit,
      [nonnull] int *__restrict decptr,
      [nonnull] int *__restrict sign) -> char * {
	if (ecvt_r(val, ndigit, decptr, sign, @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@,
	           sizeof(@__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@)))
		return NULL;
	return @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@;
}

[dependency_prefix(DEFINE_QCVT_BUFFER)]
[ATTR_WUNUSED][alias(_ecvt)]
fcvt:(double val, int ndigit,
      [nonnull] int *__restrict decptr,
      [nonnull] int *__restrict sign) -> char * {
	if (fcvt_r(val, ndigit, decptr, sign, @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@,
	           sizeof(@__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@)))
		return NULL;
	return @__NAMESPACE_LOCAL_SYM@ @__qcvt_buffer@;
}
%#endif /* !__NO_FPU */

%#endif /* ... */


%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%[default_impl_section(.text.crt.application.options)]
[ATTR_WUNUSED]
getsubopt:([nonnull] char **__restrict optionp,
           [nonnull] char *const *__restrict tokens,
           [nonnull] char **__restrict valuep) -> int {
	/* TODO: Implement here */
	(void)optionp;
	(void)tokens;
	(void)valuep;
	COMPILER_IMPURE();
	return 0;
}

%[default_impl_section(.text.crt.fs.utility)]
[ATTR_WUNUSED][noexport][requires($has_function(mktemp))]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(mkstemp64)]
mkstemp:([nonnull] char *template_) -> int {
	return mktemp(template_) ? 0 : -1;
}

%#ifdef __USE_LARGEFILE64
[ATTR_WUNUSED][noexport][largefile64_variant_of(mkstemp)]
mkstemp64:([nonnull] char *template_) -> int = mkstemp;
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN2K8
[alias(_mktemp)][ATTR_WUNUSED][guard]
mkdtemp:([nonnull] char *template_) -> char *;
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN
%[default_impl_section(.text.crt.io.tty)]
setkey:([nonnull] char const *key);
grantpt:($fd_t fd) -> int;
unlockpt:($fd_t fd) -> int;
[ATTR_WUNUSED] ptsname:($fd_t fd) -> char *; /* TODO: Implement using `ptsname_r()' */
%#endif /* __USE_XOPEN */

%
%#ifdef __USE_XOPEN2KXSI
[cp][ATTR_WUNUSED] posix_openpt:($oflag_t oflags) -> int;
%#endif /* __USE_XOPEN2KXSI */


%#ifdef __USE_GNU
%[default_impl_section(.text.crt.unicode.static.convert)]
[export_alias(_strtol_l, __strtol_l)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(strtoll_l, _strtoll_l, __strtoll_l)]
[alt_variant_of(__SIZEOF_LONG__ == 4, strto32_l)]
[alt_variant_of(__SIZEOF_LONG__ == 8, strto64_l)]
strtol_l:([nonnull] char const *__restrict nptr,
          char **endptr, int base, $locale_t locale) -> long {
	(void)locale;
	return strtol(nptr, endptr, base);
}

[export_alias(_strtoul_l, __strtoul_l)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(strtoull_l, _strtoll_l, __strtoll_l)]
[alt_variant_of(__SIZEOF_LONG__ == 4, strtou32_l)]
[alt_variant_of(__SIZEOF_LONG__ == 8, strtou64_l)]
strtoul_l:([nonnull] char const *__restrict nptr,
           char **endptr, int base, $locale_t locale) -> unsigned long {
	(void)locale;
	return strtoul(nptr, endptr, base);
}

%#ifdef __LONGLONG
[export_alias(_strtoll_l, __strtoll_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(strtol_l, _strtol_l, __strtol_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strto64_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strto32_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoimax_l, _strtoimax_l, __strtoimax_l)]
strtoll_l:([nonnull] char const *__restrict nptr,
           char **endptr, int base, $locale_t locale) -> __LONGLONG {
	(void)locale;
	return strtoll(nptr, endptr, base);
}

[export_alias(_strtoull_l, __strtoull_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(strtoul_l, _strtoul_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strtou64_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strtou32_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(strtoumax_l, _strtoumax_l, __strtoumax_l)]
strtoull_l:([nonnull] char const *__restrict nptr,
            char **endptr, int base, $locale_t locale) -> __ULONGLONG {
	(void)locale;
	return strtoull(nptr, endptr, base);
}
%#endif /* __LONGLONG */

%#ifndef __NO_FPU
[alias(_strtod_l)][export_alias(__strtod_l)]
[if(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias(strtold_l, _strtold_l)]
strtod_l:([nonnull] char const *__restrict nptr,
          char **endptr, $locale_t locale) -> double {
	(void)locale;
	return strtod(nptr, endptr);
}

[alias(_strtof_l)][export_alias(__strtof_l)]
strtof_l:([nonnull] char const *__restrict nptr,
          char **endptr, $locale_t locale) -> float {
	(void)locale;
	return strtof(nptr, endptr);
}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[alias(_strtold_l)][export_alias(__strtold_l)]
[alt_variant_of(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__, strtod_l)]
[if(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias(_strtod_l)]
strtold_l:([nonnull] char const *__restrict nptr,
           char **endptr, $locale_t locale) -> long double {
	(void)locale;
	return strtold(nptr, endptr);
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

%[default_impl_section(.text.crt.fs.environ)]
[alias(getenv)][ATTR_WUNUSED][export_alias(__secure_getenv)]
secure_getenv:([nonnull] char const *varname) -> char *;

%[default_impl_section(.text.crt.io.tty)]
ptsname_r:($fd_t fd, [nonnull] char *buf, $size_t buflen) -> int;

[cp] getpt:() -> int;

%[default_impl_section(.text.crt.fs.property)]
@@Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
@@Upon error, `NULL' is returned instead
[cp][ATTR_MALLOC][ATTR_WUNUSED]
canonicalize_file_name:([nonnull] char const *filename) -> char *;

%[default_impl_section(.text.crt.fs.utility)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(mkostemp64)]
[cp][ATTR_WUNUSED][alias(mkostemp64)]
mkostemp:([nonnull] char *template_, int flags) -> int;

[if(defined(__USE_FILE_OFFSET64)), preferred_alias(mkostemps64)]
[cp][ATTR_WUNUSED][alias(mkostemps64)]
mkostemps:([nonnull] char *template_, int suffixlen, int flags) -> int;

%#ifdef __USE_LARGEFILE64
[cp][ATTR_WUNUSED][largefile64_variant_of(mkostemp)]
mkostemp64:([nonnull] char *template_, int flags) -> int;

[cp][ATTR_WUNUSED][largefile64_variant_of(mkostemps)]
mkostemps64:([nonnull] char *template_, int suffixlen, int flags) -> int;
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */

%{

#endif /* __CC__ */

#define __DOS_MAX_PATH         260
#define __DOS_MAX_DRIVE        3
#define __DOS_MAX_DIR          256
#define __DOS_MAX_FNAME        256
#define __DOS_MAX_EXT          256
#define __DOS_OUT_TO_DEFAULT   0
#define __DOS_OUT_TO_STDERR    1
#define __DOS_OUT_TO_MSGBOX    2
#define __DOS_REPORT_ERRMODE   3
#define __DOS_WRITE_ABORT_MSG  0x1
#define __DOS_CALL_REPORTFAULT 0x2
#define __DOS_MAX_ENV          0x7fff

}
%#ifdef __USE_DOS
%{
__SYSDECL_END

#include <hybrid/__minmax.h>

__SYSDECL_BEGIN

#define __min(a, b) __hybrid_min(a, b)
#define __max(a, b) __hybrid_max(a, b)

#define _MAX_PATH         __DOS_MAX_PATH
#define _MAX_DRIVE        __DOS_MAX_DRIVE
#define _MAX_DIR          __DOS_MAX_DIR
#define _MAX_FNAME        __DOS_MAX_FNAME
#define _MAX_EXT          __DOS_MAX_EXT
#define _OUT_TO_DEFAULT   __DOS_OUT_TO_DEFAULT
#define _OUT_TO_STDERR    __DOS_OUT_TO_STDERR
#define _OUT_TO_MSGBOX    __DOS_OUT_TO_MSGBOX
#define _REPORT_ERRMODE   __DOS_REPORT_ERRMODE
#define _WRITE_ABORT_MSG  __DOS_WRITE_ABORT_MSG
#define _CALL_REPORTFAULT __DOS_CALL_REPORTFAULT
#define _MAX_ENV          __DOS_MAX_ENV

}
%#ifdef __CC__
%{

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */

#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBCCALL *_onexit_t)(void);
#define onexit_t         _onexit_t
#endif  /* _ONEXIT_T_DEFINED */
}

%
%#ifndef _CRT_ERRNO_DEFINED
%#define _CRT_ERRNO_DEFINED 1
/* NOTE: Cygwin calls it `__errno()' and DOS calls it `_errno()' */
%#ifndef errno
%[default_impl_section(.text.crt.errno_access)]
[guard][ATTR_WUNUSED][ATTR_CONST][alias(_errno, __errno)]
__errno_location:() -> errno_t *;
%#ifdef ____errno_location_defined
%#define errno     (*__errno_location())
%#endif /* ____errno_location_defined */
%#endif /* !errno */
_get_errno:(errno_t *perr) -> errno_t;
_set_errno:(errno_t err) -> errno_t;
%#endif /* !_CRT_ERRNO_DEFINED */


%
%#ifdef __CRT_HAVE___doserrno
%#define _doserrno     (*__doserrno())
%#endif /* __CRT_HAVE___doserrno */
%[default_impl_section(.text.crt.dos.errno)]
[ATTR_CONST] __doserrno:() -> $u32 *;
_get_doserrno:($u32 *perr) -> errno_t;
_set_doserrno:($u32 err) -> errno_t;

%
%{
#ifndef ___sys_errlist_defined
#define ___sys_errlist_defined 1
#if defined(__CRT_HAVE__sys_errlist)
__LIBC char const *const _sys_errlist[];
#elif defined(__CRT_HAVE___sys_errlist)
__CDECLARE(, char const *const *,__NOTHROW, __sys_errlist, (void), ())
#define _sys_errlist (__sys_errlist())
#endif

#if defined(__CRT_HAVE__sys_nerr)
__LIBC int _sys_nerr;
#elif defined(__CRT_HAVE___sys_nerr)
__CDECLARE(, int *,__NOTHROW, __sys_nerr, (void), ())
#define _sys_nerr    (*__sys_nerr())
#endif
#endif /* !___sys_errlist_defined */

#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("environ");
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("__environ");
#elif defined(__CRT_HAVE_environ)
#undef environ
#ifndef __environ_defined
#define __environ_defined 1
__LIBC char **environ;
#endif /* !__environ_defined */
#define _environ environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define _environ (*__p__environ())
#else
#undef ___environ_defined
#endif
#endif /* !___environ_defined */

}

%[default_impl_section(.text.crt.dos.application.init)]

%{
#ifndef __argc
#ifdef __CRT_HAVE___argc
__LIBC int __argc;
#define __argc __argc
#else /* .... */
}
[guard][ATTR_WUNUSED][ATTR_CONST][ATTR_RETNONNULL]
__p___argc:() -> [nonnull] int *;
%{
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !... */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__LIBC char **__argv;
#else /* .... */
}
[guard][ATTR_WUNUSED][ATTR_CONST][ATTR_RETNONNULL]
__p___argv:() -> [nonnull] char ***;
%{
#ifdef ____p___argv_defined
#define __argv (*__p___argv())
#endif /* ____p___argv_defined */
#endif /* !... */
#endif /* !__argv */

#ifndef __wargv
#ifdef __CRT_HAVE___wargv
__LIBC wchar_t **__wargv;
#define __wargv __wargv
#else /* .... */
}
[guard][ATTR_WUNUSED][ATTR_CONST][wchar][ATTR_RETNONNULL]
__p___wargv:() -> [nonnull] wchar_t ***;
%{
#ifdef ____p___wargv_defined
#define __wargv (*__p___wargv())
#endif /* ____p___wargv_defined */
#endif /* !... */
#endif /* !__wargv */

#ifndef _wenviron
#ifdef __CRT_HAVE__wenviron
__LIBC wchar_t **_wenviron;
#define _wenviron _wenviron
#else /* .... */
}
[guard][ATTR_WUNUSED][ATTR_CONST][wchar][ATTR_RETNONNULL]
__p__wenviron:() -> [nonnull] wchar_t ***;
%{
#ifdef ____p__wenviron_defined
#define _wenviron (*__p__wenviron())
#endif /* ____p__wenviron_defined */
#endif /* !... */
#endif /* !_wenviron */

#ifndef _wpgmptr
#ifdef __CRT_HAVE__wpgmptr
__LIBC wchar_t *_wpgmptr;
#define _wpgmptr _wpgmptr
#else /* .... */
}
[guard][ATTR_WUNUSED][ATTR_CONST][wchar][ATTR_RETNONNULL]
__p__wpgmptr:() -> [nonnull] wchar_t **;
%{
#ifdef ____p__wpgmptr_defined
#define _wpgmptr (*__p__wpgmptr())
#endif /* ____p__wpgmptr_defined */
#endif /* !... */
#endif /* !_wpgmptr */

/* Alias for argv[0], as passed to main()
 * HINT: The GNU equivalent of this is `program_invocation_name' */
#ifndef _pgmptr
#ifdef program_invocation_name
#define _pgmptr   program_invocation_name
#elif defined(__progname_full)
#define _pgmptr   __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
#ifndef __NO_ASMNAME
__LIBC char *_pgmptr __ASMNAME("program_invocation_name");
#define _pgmptr   _pgmptr
#else /* !__NO_ASMNAME */
__LIBC char *program_invocation_name;
#define program_invocation_name program_invocation_name
#define _pgmptr                 program_invocation_name
#endif /* __NO_ASMNAME */
#elif defined(__CRT_HAVE__pgmptr)
__LIBC char *_pgmptr;
#define _pgmptr   _pgmptr
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_ASMNAME
__LIBC char *_pgmptr __ASMNAME("__progname_full");
#define _pgmptr   _pgmptr
#else /* !__NO_ASMNAME */
__LIBC char *__progname_full;
#define __progname_full __progname_full
#define _pgmptr         __progname_full
#endif /* __NO_ASMNAME */
#else /* ... */
}
@@Alias for argv[0], as passed to main()
[guard][ATTR_WUNUSED][ATTR_CONST][ATTR_RETNONNULL]
[export_alias(__p_program_invocation_name)]
__p__pgmptr:() -> [nonnull] char **;
%{
#ifdef ____p__pgmptr_defined
#define _pgmptr   (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !_pgmptr */
}

%
%#ifdef __USE_KOS
%{
#ifndef __initenv
#ifdef __CRT_HAVE___initenv
__LIBC char **__initenv;
#else /* .... */
}
@@Access to the initial environment block
[guard][ATTR_WUNUSED][ATTR_CONST] __p___initenv:() -> [nonnull] char ***;
%{
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !... */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__LIBC wchar_t **__winitenv;
#else /* .... */
}
@@Access to the initial environment block
[guard][ATTR_WUNUSED][ATTR_CONST][wchar] __p___winitenv:() -> [nonnull] wchar_t ***;
%{
#ifdef ____p___winitenv_defined
#define __winitenv (*__p___winitenv())
#endif /* ____p___winitenv_defined */
#endif /* !... */
#endif /* !__winitenv */
}
%#endif /* __USE_KOS */

%
%#ifndef _countof
%#define _countof(a) __COMPILER_LENOF(a)
%#endif /* !_countof */


%
%[default_impl_section(.text.crt.dos.errno)]
%typedef void (__LIBCCALL *_purecall_handler)(void);
_set_purecall_handler:(_purecall_handler __handler) -> _purecall_handler;
_get_purecall_handler:() -> _purecall_handler;

%
%[default_impl_section(.text.crt.dos.errno)]
%typedef void (__LIBCCALL *_invalid_parameter_handler)(wchar_t const *, wchar_t const *, wchar_t const *, unsigned int, __UINTPTR_TYPE__);
_set_invalid_parameter_handler:(_invalid_parameter_handler __handler) -> _invalid_parameter_handler;
_get_invalid_parameter_handler:() -> _invalid_parameter_handler;

%
[section(.text.crt.dos.application.init)]
_get_pgmptr:(char **pvalue) -> errno_t; /* TODO: Implement using `_pgmptr' */
[section(.text.crt.dos.wchar.application.init)]
[wchar] _get_wpgmptr:(wchar_t **pvalue) -> errno_t; /* TODO: Implement using `_wpgmptr' */

%
%[default_impl_section(.text.crt.dos.FILE.utility)]
%#ifdef __CRT_HAVE__fmode
%__LIBC int _fmode;
%#else /* ... */
[guard][ATTR_WUNUSED][ATTR_CONST][ATTR_RETNONNULL] __p__fmode:() -> int *;
%#ifdef ____p__fmode_defined
%#define _fmode (*__p__fmode())
%#endif /* ____p__fmode_defined */
%#endif /* !... */
_set_fmode:(int mode) -> errno_t;
_get_fmode:(int *pmode) -> errno_t;

%
%[default_impl_section(.text.crt.dos.errno)]
_set_abort_behavior:(unsigned int flags, unsigned int mask) -> unsigned int;

%
%#ifdef __INT64_TYPE__
%#ifdef _MSC_VER
%extern __ATTR_CONST __INT64_TYPE__ (__LIBCCALL _abs64)(__INT64_TYPE__ __x);
%#pragma intrinsic(_abs64)
%#else /* _MSC_VER */
%[default_impl_section(.text.crt.dos.math.utility)]
[ATTR_CONST][ATTR_WUNUSED][nothrow]
[alt_variant_of(__SIZEOF_INT__ == 8, abs)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, llabs)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(imaxabs)]
_abs64:(__INT64_TYPE__ x) -> __INT64_TYPE__ {
	return x < 0 ? -x : x;
}
%#endif /* !_MSC_VER */
%#endif /* __INT64_TYPE__ */


%[default_impl_section(.text.crt.dos.unicode.locale.convert)]
%#ifndef __NO_FPU
[ATTR_WUNUSED][ATTR_PURE]
_atof_l:([nonnull] char const *__restrict nptr, $locale_t locale) -> double {
	return strtod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

[ATTR_WUNUSED][ATTR_PURE]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_atol_l)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(_atoll_l)]
_atoi_l:([nonnull] char const *__restrict nptr, $locale_t locale) -> int {
	return (int)strtol_l(nptr, NULL, 10, locale);
}
[ATTR_WUNUSED][ATTR_PURE]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _atoi_l)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(_atoll_l)]
_atol_l:([nonnull] char const *__restrict nptr, $locale_t locale) -> long int {
	return strtol_l(nptr, NULL, 10, locale);
}
%#ifdef __LONGLONG
[ATTR_WUNUSED][ATTR_PURE]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _atol_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _atoi_l)]
_atoll_l:([nonnull] char const *__restrict nptr, $locale_t locale) -> __LONGLONG {
	return strtoll_l(nptr, NULL, 10, locale);
}
%#endif /* __LONGLONG */

%
%{
#ifdef _MSC_VER
extern unsigned short (_byteswap_ushort)(unsigned short __x);
extern unsigned long (_byteswap_ulong)(unsigned long __x);
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 __x);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)
#else /* _MSC_VER */
}

%[default_impl_section(.text.crt.dos.math.utility)]
[dependency_include(<hybrid/__byteswap.h>)]
[ATTR_CONST][ATTR_WUNUSED]
_byteswap_ushort:($u16 val) -> $u16 {
	return __hybrid_bswap16(val);
}
[dependency_include(<hybrid/__byteswap.h>)]
[ATTR_CONST][ATTR_WUNUSED]
_byteswap_ulong:($u32 val) -> $u32 {
	return __hybrid_bswap32(val);
}
%#ifdef __UINT64_TYPE__
[dependency_include(<hybrid/__byteswap.h>)]
[ATTR_CONST][ATTR_WUNUSED]
_byteswap_uint64:($u64 val) -> $u64 {
	return __hybrid_bswap64(val);
}
%#endif /* __UINT64_TYPE__ */
%#endif /* !_MSC_VER */

%#ifdef __USE_DOS_SLIB
%{
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */
}

%
%#ifndef _CRT_ALGO_DEFINED
%#define _CRT_ALGO_DEFINED 1
%{
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
}

%[default_impl_section(.text.crt.dos.utility)]

[dependency_prefix(
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
)][impl_prefix(
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
)][ATTR_WUNUSED]
bsearch_s:([nonnull] void const *key, [nonnull] void const *base,
           $size_t nmemb, $size_t size,
           [nonnull] __dos_compar_d_fn_t compar, void *arg) -> void * {
	struct @__invoke_compare_helper_s_data@ data;
	data.@__fun@ = compar;
	data.@__arg@ = arg;
	return bsearch_r(key, base, nmemb, size, &@__invoke_compare_helper_s@, &data);
}

[dependency_prefix(
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
)][impl_prefix(
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
)]
qsort_s:([nonnull] void *base, $size_t nmemb, $size_t size,
         [nonnull] __dos_compar_d_fn_t compar, void *arg) {
	struct @__invoke_compare_helper_s_data@ data;
	data.@__fun@ = compar;
	data.@__arg@ = arg;
	return qsort_r(base, nmemb, size, &@__invoke_compare_helper_s@, &data);
}
%#endif  /* _CRT_ALGO_DEFINED */
%

getenv_s:([nonnull] $size_t *psize,
          [nonnull] char *buf, rsize_t bufsize,
          [nonnull] char const *varname) -> errno_t;
_dupenv_s:([nonnull] char **__restrict pbuf,
           [nonnull] $size_t *pbuflen,
           [nonnull] char const *varname) -> errno_t;
%#endif /* __USE_DOS_SLIB */

%
%[default_impl_section(.text.crt.dos.unicode.static.convert)]
[alias(*)][attribute(*)] _itoa:(*) = itoa;
[alias(*)][attribute(*)] _ltoa:(*) = ltoa;
[alias(*)][attribute(*)] _ultoa:(*) = ultoa;


[alias(itoa_s)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_ltoa_s)]
[if(__SIZEOF_INT__ == 8), alias(_i64toa_s)]
[dependency_include(<parts/errno.h>)]
_itoa_s:(int val, [nonnull] char *buf, $size_t buflen, int radix) -> errno_t {
	char *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--)
			return @__ERANGE@;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf))
		return @__ERANGE@;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

[alias(ltoa_s)]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _itoa_s)]
[if(__SIZEOF_LONG__ == 8), alias(_i64toa_s)]
[dependency_include(<parts/errno.h>)]
_ltoa_s:(long val, [nonnull] char *buf, $size_t buflen, int radix) -> errno_t {
	char *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--)
			return @__ERANGE@;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf))
		return @__ERANGE@;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

[alias(ultoa_s)]
[if(__SIZEOF_LONG__ == 8), alias(_ui64toa_s)]
[dependency_include(<parts/errno.h>)]
_ultoa_s:(unsigned long val, [nonnull] char *buf, $size_t buflen, int radix) -> errno_t {
	char *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf))
		return @__ERANGE@;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}


%
%#ifdef __UINT64_TYPE__
[alias(i64toa)]
[alt_variant_of(__SIZEOF_INT__ == 8, itoa)]
[if(__SIZEOF_INT__ == 8), alias(_itoa)]
[alt_variant_of(__SIZEOF_LONG__ == 8, ltoa)]
[if(__SIZEOF_LONG__ == 8), alias(_ltoa)]
_i64toa:($s64 val, [nonnull] char *buf, int radix) -> char * {
	_i64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[alt_variant_of(__SIZEOF_LONG__ == 8, ultoa)]
[if(__SIZEOF_LONG__ == 8), alias(_ultoa)]
_ui64toa:($u64 val, [nonnull] char *buf, int radix) -> char * {
	_ui64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[alt_variant_of(__SIZEOF_LONG__ == 8, _ltoa_s)]
[alt_variant_of(__SIZEOF_INT__ == 8, _itoa_s)]
[dependency_include(<parts/errno.h>)]
_i64toa_s:($s64 val, [nonnull] char *buf, $size_t buflen, int radix) -> errno_t {
	char *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--)
			return @__ERANGE@;
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf))
		return @__ERANGE@;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}

[alt_variant_of(__SIZEOF_LONG__ == 8, _ultoa_s)]
[dependency_include(<parts/errno.h>)]
_ui64toa_s:($u64 val, [nonnull] char *buf, $size_t buflen, int radix) -> errno_t {
	char *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf))
		return @__ERANGE@;
	temp = val;
	*p = '\0';
	do {
		unsigned char digit;
		digit = temp % (unsigned int)radix;
		*--p = digit < 10 ? (char)('0' + digit) : (char)('A' + (digit - 10));
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}


[attribute(*)][alias(*)] _strtoi64:(*) = strto64;
[attribute(*)][alias(*)] _strtoui64:(*) = strtou64;
[attribute(*)][alias(*)] _strtoi64_l:(*) = strto64_l;
[attribute(*)][alias(*)] _strtoui64_l:(*) = strtou64_l;


[ATTR_PURE][ATTR_WUNUSED]
[alt_variant_of(__SIZEOF_INT__ == 8, atoi)]
[alt_variant_of(__SIZEOF_LONG__ == 8, atol)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, atoll)]
_atoi64:([nonnull] char const *__restrict nptr) -> $s64 {
	return strto64(nptr, NULL, 10);
}

[ATTR_PURE][ATTR_WUNUSED]
[alt_variant_of(__SIZEOF_INT__ == 8, _atoi_l)]
[alt_variant_of(__SIZEOF_LONG__ == 8, _atol_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, _atoll_l)]
_atoi64_l:([nonnull] char const *__restrict nptr, $locale_t locale) -> $s64 {
	return strto64_l(nptr, NULL, 10, locale);
}
%#endif /* __UINT64_TYPE__ */

%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]

[ATTR_PURE][ATTR_WUNUSED]
_mbstrlen:([nonnull] char const *str) -> $size_t {
	size_t result = 0;
	while (unicode_readutf8((char const **)&str))
		++result;
	return result;
}

[ATTR_PURE][ATTR_WUNUSED]
_mbstrnlen:([nonnull] char const *str, $size_t maxlen) -> $size_t {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}

[ATTR_PURE][ATTR_WUNUSED]
_mbstrlen_l:([nonnull] char const *str, $locale_t locale) -> $size_t {
	(void)locale;
	return _mbstrlen(str);
}

[ATTR_PURE][ATTR_WUNUSED]
_mbstrnlen_l:([nonnull] char const *str, $size_t maxlen, $locale_t locale) -> $size_t {
	(void)locale;
	return _mbstrnlen(str, maxlen);
}

[ATTR_PURE][ATTR_WUNUSED]
_mblen_l:([nonnull] char const *str, $size_t maxlen, $locale_t locale) -> int {
	(void)locale;
	return mblen(str, maxlen);
}

[wchar]
_mbtowc_l:(wchar_t *dst, char const *src,
           $size_t srclen, $locale_t locale) -> int {
	(void)locale;
	return mbtowc(dst, src, srclen);
}

[wchar]
_mbstowcs_l:(wchar_t *dst, char const *src,
             $size_t dstlen, $locale_t locale) -> $size_t {
	(void)locale;
	return mbstowcs(dst, src, dstlen);
}


[wchar][dependency_include(<parts/errno.h>)]
_mbstowcs_s:($size_t *presult,
             wchar_t *dst, $size_t dstsize,
             char const *src, $size_t dstlen) -> errno_t {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef @__EILSEQ@
	if (error == (size_t)-1)
		return @__EILSEQ@;
#endif /* EILSEQ */
	return 0;
}

[wchar]
_mbstowcs_s_l:($size_t *presult,
               wchar_t *dst, $size_t dstsize,
               char const *src, $size_t dstlen,
               $locale_t locale) -> errno_t {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = _mbstowcs_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
#ifdef @__EILSEQ@
	if (error == (size_t)-1)
		return @__EILSEQ@;
#endif /* EILSEQ */
	return 0;
}

%[default_impl_section(.text.crt.dos.random)]
[dependency_include(<parts/errno.h>)]
[user][same_impl][dos_variant]
rand_s:([nonnull] unsigned int *__restrict randval) -> errno_t{
	if (!randval)
		return @__EINVAL@;
	*randval = rand();
	return 0;
}


%[default_impl_section(.text.crt.unicode.static.convert)]
[attribute(*)][alias(*)] _strtol_l:(*) = strtol_l;
[attribute(*)][alias(*)] _strtoul_l:(*) = strtoul_l;
[attribute(*)][alias(*)] _strtoll_l:(*) = strtoll_l;
[attribute(*)][alias(*)] _strtoull_l:(*) = strtoull_l;
%#ifndef __NO_FPU
[attribute(*)][alias(*)] _strtod_l:(*) = strtod_l;
[attribute(*)][alias(*)] _strtof_l:(*) = strtof_l;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[attribute(*)][alias(*)] _strtold_l:(*) = strtold_l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

%
%#ifndef _CRT_SYSTEM_DEFINED
%#define _CRT_SYSTEM_DEFINED 1
%#endif /* !_CRT_SYSTEM_DEFINED */

%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]

%
[wchar]
_wctomb_l:(char *buf, wchar_t wc, $locale_t locale) -> int {
	(void)locale;
	return wctomb(buf, wc);
}

%
%#ifdef __USE_DOS_SLIB
[dependency_include(<parts/errno.h>)]
wctomb_s:([nonnull] int *presult, [nonnull] char *buf,
          rsize_t buflen, wchar_t wc) -> errno_t {
	if (!presult || !buf)
		return __EINVAL;
	if (buflen < @MB_CUR_MAX@)
		return @__ERANGE@;
	*presult = wctomb(buf, wc);
	return 0;
}
%#endif /* __USE_DOS_SLIB */

[dependency_include(<parts/errno.h>)]
_wctomb_s_l:([nonnull] int *presult, [nonnull] char *buf,
             $size_t buflen, wchar_t wc, $locale_t locale) -> errno_t {
	(void)locale;
	return wctomb_s(presult, buf, buflen, wc);
}

[dependency_include(<parts/errno.h>)]
_wcstombs_s_l:([nonnull] $size_t *presult, [nonnull] char *buf,
               $size_t buflen, [nonnull] wchar_t const *src,
               $size_t maxlen, $locale_t locale) -> errno_t {
	(void)locale;
	return wcstombs_s(presult, buf, buflen, src, maxlen);
}

_wcstombs_l:([nonnull] char *dst, [nonnull] wchar_t const *src,
             $size_t maxlen, $locale_t locale) -> $size_t {
	(void)locale;
	return wcstombs(dst, src, maxlen);
}

[dependency_include(<parts/errno.h>)]
wcstombs_s:([nonnull] $size_t *presult,
            [nonnull] char *buf, $size_t buflen,
            [nonnull] wchar_t const *src, $size_t maxlen) -> errno_t {
	if (!presult || !buf || !src)
		return __EINVAL;
	if (buflen < wcstombs(NULL, src, maxlen))
		return @__ERANGE@;
	*presult = wcstombs(buf, src, maxlen);
	return 0;
}

%
%/* DOS malloc extensions */
%[default_impl_section(.text.crt.dos.heap)]

[requires($has_function(realloc) && $has_function(malloc_usable_size))]
[dependency_include(<hybrid/__overflow.h>)][same_impl]
_recalloc:(void *mallptr, $size_t count, $size_t num_bytes)
		-> [realloc(mallptr, count * num_bytes)] void * {
	void *result;
	size_t total_bytes, oldsize = malloc_usable_size(mallptr);
	if unlikely(__hybrid_overflow_umul(count, num_bytes, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = realloc(mallptr, total_bytes);
	if likely(result) {
		if (total_bytes > oldsize)
			memset((byte_t *)result + oldsize, 0, total_bytes - oldsize);
	}
	return result;

}

[requires($has_function(malloc))][same_impl]
_aligned_malloc:($size_t num_bytes, $size_t min_alignment)
	-> [memalign(min_alignment, num_bytes)] void *
{
	void *result = malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1);
	if (result) {
		void *base = (void *)(((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1));
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}

[requires($has_function(malloc))][same_impl]
_aligned_offset_malloc:($size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [malloc_unaligned(num_bytes)] void *
{
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

[same_impl]
[requires($has_function(_aligned_malloc) && $has_function(_aligned_free) && $has_function(_aligned_msize))]
_aligned_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment)
	-> [realign(aligned_mallptr, min_alignment, newsize)] void *
{
	void *result;
	result = _aligned_malloc(newsize, min_alignment);
	if (result && aligned_mallptr) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[same_impl]
[requires($has_function(_aligned_malloc) && $has_function(_aligned_free) && $has_function(_aligned_msize))]
_aligned_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment)
	-> [realign(aligned_mallptr, min_alignment, count * num_bytes)] void *
{
	void *result;
	num_bytes *= count;
	result = _aligned_malloc(num_bytes, min_alignment);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		memset((byte_t *)result + temp, 0, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[same_impl]
[requires($has_function(_aligned_offset_malloc) && $has_function(_aligned_free) && $has_function(_aligned_msize))]
_aligned_offset_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment, $size_t offset)
	-> [realloc_unaligned(aligned_mallptr, newsize)] void *
{
	void *result;
	result = _aligned_offset_malloc(newsize, min_alignment, offset);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[same_impl]
[requires($has_function(_aligned_offset_malloc) && $has_function(_aligned_free) && $has_function(_aligned_msize))]
_aligned_offset_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [realloc_unaligned(aligned_mallptr, count * num_bytes)] void *
{
	void *result;
	num_bytes *= count;
	result = _aligned_offset_malloc(num_bytes, min_alignment, offset);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		memset((byte_t *)result + temp, 0, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[ATTR_WUNUSED][ATTR_PURE][same_impl]
_aligned_msize:(void *aligned_mallptr, $size_t min_alignment, $size_t offset) -> $size_t {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return ($size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}

[requires($has_function(free))][same_impl]
_aligned_free:(void *aligned_mallptr) {
	if (aligned_mallptr)
		free(((void **)aligned_mallptr)[-1]);
}

%
%#define _CVTBUFSIZE   349
%[default_impl_section(.text.crt.dos.fs.utility)]
[cp] _fullpath:(char *buf, char const *path, $size_t buflen) -> char *;

%[default_impl_section(.text.crt.unicode.static.convert)]

%#ifndef __NO_FPU
[dependency_include(<parts/errno.h>)]
_ecvt_s:([nonnull] char *buf, $size_t buflen, double val, int ndigit,
         [nonnull] int *__restrict decptr,
         [nonnull] int *__restrict sign) -> errno_t {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

[dependency_include(<parts/errno.h>)]
_fcvt_s:([nonnull] char *buf, $size_t buflen, double val, int ndigit,
         [nonnull] int *__restrict decptr,
         [nonnull] int *__restrict sign) -> errno_t {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

[dependency_include(<parts/errno.h>)]
_gcvt_s:([nonnull] char *buf, $size_t buflen, double val, int ndigit) -> errno_t {
	int a, b;
	if (!buf)
		return __EINVAL;
	ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return 0;
}


[alias(*)][attribute(*)] _ecvt:(*) = ecvt;
[alias(*)][attribute(*)] _fcvt:(*) = fcvt;
[alias(*)][attribute(*)] _gcvt:(*) = gcvt;

_atoflt:([nonnull] float *__restrict result,
         [nonnull] char const *__restrict nptr) -> int {
	*result = strtof(nptr, NULL);
	return 0;
}

_atoflt_l:([nonnull] float *__restrict result,
           [nonnull] char const *__restrict nptr, $locale_t locale) -> int {
	*result = strtof_l(nptr, NULL, locale);
	return 0;
}

[requires_include(<hybrid/typecore.h>)]
[if(__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias(_atoldbl)]
_atodbl:([nonnull] double *__restrict result,
         [nonnull] char __KOS_FIXED_CONST *__restrict nptr) -> int {
	*result = strtod(nptr, NULL);
	return 0;
}

[requires_include(<hybrid/typecore.h>)]
[if(__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias(_atoldbl_l)]
_atodbl_l:([nonnull] double *__restrict result,
           [nonnull] char __KOS_FIXED_CONST *__restrict nptr, $locale_t locale) -> int {
	*result = strtod_l(nptr, NULL, locale);
	return 0;
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[requires_include(<hybrid/typecore.h>)]
[if(__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias(_atodbl)]
_atoldbl:([nonnull] long double *__restrict result,
          [nonnull] char __KOS_FIXED_CONST *__restrict nptr) -> int {
	*result = strtold(nptr, NULL);
	return 0;
}

[requires_include(<hybrid/typecore.h>)]
[if(__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias(_atodbl_l)]
_atoldbl_l:([nonnull] long double *__restrict result,
            [nonnull] char __KOS_FIXED_CONST *__restrict nptr, $locale_t locale) -> int {
	*result = strtold_l(nptr, NULL, locale);
	return 0;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */


%[default_impl_section(.text.crt.dos.math.utility)]
[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_lrotl)]
[if(__SIZEOF_INT__ == 8), alias(_rotl64)]
_rotl:(unsigned int val, int shift) -> unsigned int {
	return __hybrid_rol(val, shift);
}

[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_lrotr)]
[if(__SIZEOF_INT__ == 8), alias(_rotr64)]
_rotr:(unsigned int val, int shift) -> unsigned int {
	return __hybrid_ror(val, shift);
}

%#ifdef __UINT64_TYPE__
[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_LONG__ == 8), alias(_lrotl)]
[if(__SIZEOF_INT__ == 8), alias(_rotl)]
_rotl64:($u64 val, int shift) -> $u64 {
	return __hybrid_rol64(val, shift);
}

[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_LONG__ == 8), alias(_lrotr)]
[if(__SIZEOF_INT__ == 8), alias(_rotr)]
_rotr64:($u64 val, int shift) -> $u64 {
	return __hybrid_ror64(val, shift);
}
%#endif /* __UINT64_TYPE__ */

[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias(_rotl)]
[if(__SIZEOF_LONG__ == 8), alias(_rotl64)]
_lrotl:(unsigned long val, int shift) -> unsigned long {
	return __hybrid_rol(val, shift);
}

[ATTR_CONST][nothrow]
[requires_include(<hybrid/typecore.h>)]
[dependency_include(<hybrid/__rotate.h>)]
[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias(_rotr)]
[if(__SIZEOF_LONG__ == 8), alias(_rotr64)]
_lrotr:(unsigned long val, int shift) -> unsigned long {
	return __hybrid_ror(val, shift);
}

%
%#ifndef _CRT_PERROR_DEFINED
%#define _CRT_PERROR_DEFINED 1
%[insert:extern(perror)]
%#endif  /* _CRT_PERROR_DEFINED */

%
[attribute(*)][alias(*)] _putenv:(*) = putenv;
[attribute(*)][alias(*)] _swab:(*) = swab;

%[default_impl_section(.text.crt.dos.fs.environ)]
[requires(defined(__CRT_HAVE_setenv))][same_impl]
[dependency_include(<parts/errno.h>)]
_putenv_s:(char const *varname, char const *val) -> errno_t {
	return setenv(varname, val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}

%[default_impl_section(.text.crt.dos.fs.utility)]
[cp][requires($has_function(_searchenv_s))][same_impl]
_searchenv:([nonnull] char const *file,
            [nonnull] char const *envvar,
            [nonnull] char *__restrict resultpath) {
	_searchenv_s(file, envvar, resultpath, ($size_t)-1);
}

[cp]
_searchenv_s:([nonnull] char const *file,
              [nonnull] char const *envvar,
              [nonnull] char *__restrict resultpath,
              $size_t buflen) -> errno_t;

[same_impl]
_makepath:([nonnull] char *__restrict buf,
           char const *drive, char const *dir,
           char const *file, char const *ext) {
	_makepath_s(buf, ($size_t)-1, drive, dir, file, ext);
}

[same_impl]
_splitpath:([nonnull] char const *__restrict abspath,
            char *drive, char *dir, char *file, char *ext) {
	_splitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}

[dependency_include(<parts/errno.h>)][same_impl]
_makepath_s:([nonnull] char *buf, $size_t buflen,
             char const *drive, char const *dir,
             char const *file, char const *ext) -> errno_t {
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
#ifdef @__EINVAL@
	return @__EINVAL@;
#else /* __EINVAL */
	return -1;
#endif /* !__EINVAL */
#undef path_putn
#undef path_putc
}

[dependency_include(<parts/errno.h>)]
_splitpath_s:([nonnull] char const *__restrict abspath,
              [outp_opt(drivelen)] char *drive, $size_t drivelen,
              [outp_opt(dirlen)] char *dir, $size_t dirlen,
              [outp_opt(filelen)] char *file, $size_t filelen,
              [outp_opt(extlen)] char *ext, $size_t extlen) -> errno_t {
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
#ifdef @__EINVAL@
	return @__EINVAL@;
#else /* __EINVAL */
	return -1;
#endif /* !__EINVAL */
err_range:
#ifdef @__ERANGE@
	@__libc_seterrno@(@__ERANGE@);
	return @__ERANGE@;
#else /* __ERANGE */
	return -1;
#endif /* !__ERANGE */
}

%[default_impl_section(.text.crt.dos.errno)]
%
_seterrormode:(int mode);
_set_error_mode:(int mode) -> int;

%[default_impl_section(.text.crt.dos.system)]
%
_beep:(unsigned int freq, unsigned int duration);

%
%#ifndef _CRT_WPERROR_DEFINED
%#define _CRT_WPERROR_DEFINED 1
%[insert:extern(_wperror)]
%#endif /* !_CRT_WPERROR_DEFINED */

%[default_impl_section(.text.crt.dos.system)]
[cp] _sleep:($u32 duration) = sleep;

%
%{
#ifndef __cplusplus
#define min(a, b)   __min(a, b)
#define max(a, b)   __max(a, b)
#endif /* !__cplusplus */
}

%
%{
#define sys_errlist _sys_errlist
#define sys_nerr    _sys_nerr
}

%
%{
#ifndef __environ_defined
#define __environ_defined 1
#undef environ
#if defined(__CRT_HAVE_environ)
__LIBC char **environ;
#define environ environ
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("_environ");
#define environ environ
#elif defined(__CRT_HAVE__environ)
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ   (*__p__environ())
#else
#undef __environ_defined
#endif
#endif /* !__environ_defined */
}

%[default_impl_section(.text.crt.dos.string.utility)]
%
%[insert:extern(swab)]
%[default_impl_section(.text.crt.unicode.static.convert)]


%
%
%

[export_alias(_itoa)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_ltoa, ltoa)]
[if(__SIZEOF_INT__ == 8), alias(_i64toa)]
itoa:(int val, [nonnull] char *buf, int radix) -> char * {
	_itoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[export_alias(_ltoa)]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, itoa)]
[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias(_itoa)]
[if(__SIZEOF_LONG__ == 8), alias(_i64toa)]
ltoa:(long val, [nonnull] char *buf, int radix) -> char * {
	_ltoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[export_alias(_ultoa)]
[if(__SIZEOF_LONG__ == 8), alias(_ui64toa)]
ultoa:(unsigned long val, [nonnull] char *buf, int radix) -> char * {
	_ultoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

%[default_impl_section(.text.crt.dos.sched.process)]
[alias(*)][attribute(*)] _onexit:(*) = onexit;
[alias(_onexit)] onexit:(onexit_t func) -> onexit_t;


%#ifndef _WSTDLIB_DEFINED
%#define _WSTDLIB_DEFINED

%[default_impl_section(.text.crt.dos.wchar.fs.environ)]
[guard][wchar][ATTR_WUNUSED] _wgetenv:([nonnull] wchar_t const *varname) -> wchar_t *;
[guard][wchar] _wgetenv_s:([nonnull] $size_t *return_size, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, [nonnull] wchar_t const *varname) -> errno_t;
[guard][wchar] _wdupenv_s:([nonnull] wchar_t **pbuf, [nonnull] $size_t *pbuflen, [nonnull] wchar_t const *varname) -> errno_t;

%[insert:extern(_wsystem)]

%[default_impl_section(.text.crt.dos.wchar.unicode.static.convert)]
%[insert:extern(wcstol)]
%[insert:extern(wcstoll)]
%[insert:extern(wcstoul)]
%[insert:extern(wcstoull)]
[guard][wchar][attribute(*)][alias(*)] _wcstol_l:(*) = wcstol_l;
[guard][wchar][attribute(*)][alias(*)] _wcstoul_l:(*) = wcstoul_l;

%#ifndef __NO_FPU
%[insert:extern(wcstof)]
%[insert:extern(wcstod)]
[guard][wchar][attribute(*)][alias(*)] _wcstof_l:(*) = wcstof_l;
[guard][wchar][attribute(*)][alias(*)] _wcstod_l:(*) = wcstod_l;
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:extern(wcstold)]
[guard][wchar][attribute(*)][alias(*)] _wcstold_l:(*) = wcstold_l;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
_wtof:([nonnull] wchar_t const *nptr) -> double {
	return wcstod(nptr, NULL);
}

[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
_wtof_l:([nonnull] wchar_t const *nptr, [nullable] $locale_t locale) -> double {
	return wcstod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

%[default_impl_section(.text.crt.dos.wchar.unicode.static.convert)]
[guard][wchar] _itow:(int val, [nonnull] wchar_t *buf, int radix) -> wchar_t * %{copy(itoa, str2wcs)}
[guard][wchar] _ltow:(long val, [nonnull] wchar_t *buf, int radix) -> wchar_t * %{copy(ltoa, str2wcs)}
[guard][wchar] _ultow:(unsigned long val, [nonnull] wchar_t *buf, int radix) -> wchar_t * %{copy(ultoa, str2wcs)}
[guard][wchar] _i64tow:($int64_t val, [nonnull] wchar_t *buf, int radix) -> wchar_t * %{copy(_i64toa, str2wcs)}
[guard][wchar] _ui64tow:($uint64_t val, [nonnull] wchar_t *buf, int radix) -> wchar_t * %{copy(_ui64toa, str2wcs)}
[guard][wchar] _itow_s:(int val, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, int radix) -> errno_t %{copy(_itoa_s, str2wcs)}
[guard][wchar] _ltow_s:(long val, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, int radix) -> errno_t %{copy(_ltoa_s, str2wcs)}
[guard][wchar] _ultow_s:(unsigned long val, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, int radix) -> errno_t %{copy(_ultoa_s, str2wcs)}
[guard][wchar] _i64tow_s:($int64_t val, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, int radix) -> errno_t %{copy(_i64toa_s, str2wcs)}
[guard][wchar] _ui64tow_s:($uint64_t val, [outp_opt(buflen)] wchar_t *buf, $size_t buflen, int radix) -> errno_t %{copy(_ui64toa_s, str2wcs)}

%[default_impl_section(.text.crt.dos.wchar.unicode.static.convert)]
[guard][wchar][attribute(*)][alias(*)] _wtoi:(*) = wtoi;
[guard][wchar][attribute(*)][alias(*)] _wtol:(*) = wtol;

[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
[if(__SIZEOF_INT__ == 8), alias(_wtoi)]
[if(__SIZEOF_LONG__ == 8), alias(_wtol)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_wtoll)]
_wtoi64:([nonnull] wchar_t const *nptr) -> $int64_t %{copy(_atoi64, str2wcs)}

[guard][wchar][alias(*)][attribute(*)] _wcstoi64:(*) = wcsto64;
[guard][wchar][alias(*)][attribute(*)] _wcstoui64:(*) = wcstou64;

%[default_impl_section(.text.crt.dos.wchar.unicode.locale.convert)]
[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias(_wtol_l)]
[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(_wtoll_l)]
[if(__SIZEOF_INT__ == 8), alias(_wtoi64_l)]
_wtoi_l:([nonnull] wchar_t const *nptr, [nullable] $locale_t locale) -> int %{copy(_atoi_l, str2wcs)}

[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _wtoi_l)]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(_wtoll_l)]
[if(__SIZEOF_LONG__ == 8), alias(_wtoi64_l)]
_wtol_l:([nonnull] wchar_t const *nptr, [nullable] $locale_t locale) -> long %{copy(_atol_l, str2wcs)}

[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
[alt_variant_of(__SIZEOF_INT__ == 8, _wtoi_l)]
[alt_variant_of(__SIZEOF_LONG__ == 8, _wtol_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, _wtoll_l)]
_wtoi64_l:([nonnull] wchar_t const *nptr, [nullable] $locale_t locale) -> $int64_t %{copy(_atoi64_l, str2wcs)}

[guard][wchar][alias(*)][attribute(*)] _wcstoi64_l:(*) = wcsto64_l;
[guard][wchar][alias(*)][attribute(*)] _wcstoui64_l:(*) = wcstou64_l;


%#ifdef __LONGLONG
%[default_impl_section(.text.crt.dos.wchar.unicode.static.convert)]
[guard][wchar][attribute(*)][alias(*)] _wcstoll_l:(*) = wcstoll_l;
[guard][wchar][attribute(*)][alias(*)] _wcstoull_l:(*) = wcstoull_l;
[guard][wchar][attribute(*)][alias(*)] _wtoll:(*) = wtoll;

%[default_impl_section(.text.crt.dos.wchar.unicode.locale.convert)]
[guard][wchar][ATTR_WUNUSED][ATTR_PURE]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _wtoi_l)]
[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _wtol_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_wtoi64_l)]
_wtoll_l:([nonnull] wchar_t const *nptr, [nullable] $locale_t locale) -> __LONGLONG %{copy(_atoll_l, str2wcs)}
%#endif /* __LONGLONG */

%#endif /* !_WSTDLIB_DEFINED */

%{

#endif /* __CC__ */
#endif /* __USE_DOS */



__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDLIB_H */
#endif /* __USE_UTF */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_STDLIB_H)
#include <parts/wchar/stdlib.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_STDLIB_H */
#endif /* __USE_KOS */

}

