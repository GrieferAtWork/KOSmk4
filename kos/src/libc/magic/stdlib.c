/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: DJGPP         (/include/stdlib.h) */
/* (#) Portability: FreeBSD       (/include/stdlib.h) */
/* (#) Portability: GNU C Library (/stdlib/stdlib.h) */
/* (#) Portability: MSVC          (/include/stdlib.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdlib.h) */
/* (#) Portability: NetBSD        (/include/stdlib.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdlib.h) */
/* (#) Portability: diet libc     (/include/stdlib.h) */
/* (#) Portability: musl libc     (/include/stdlib.h) */
/* (#) Portability: uClibc        (/include/stdlib.h) */
}

%[define_ccompat_header("cstdlib")]
%[declare_known_section(".text.crt{|.dos}.application.init")]
%[declare_known_section(".text.crt{|.dos}.glibc")]

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

%[define_replacement(__WAIT_STATUS = __WAIT_STATUS)]
%[define_replacement(__WAIT_STATUS_DEFN = __WAIT_STATUS_DEFN)]
%[define_type_class(__WAIT_STATUS      = "TP")]
%[define_type_class(__WAIT_STATUS_DEFN = "TP")]
%[define_type_class(__atexit_func_t    = "TP")]
%[define_type_class(__on_exit_func_t   = "TP")]
%[define_type_class(comparison_fn_t    = "TP")]
%[define_type_class(__compar_fn_t      = "TP")]
%[define_type_class(__compar_d_fn_t    = "TP")]

%(auto_source){
#include "../libc/globals.h"
}


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <asm/crt/stdlib.h>
)]%[insert:prefix(
#include <asm/os/oflags.h> /* __O_LARGEFILE */
)]%[insert:prefix(
#include <asm/os/stdlib.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_MISC
#include <alloca.h>
#endif /* __USE_MISC */

#ifdef __USE_DOS
#include <hybrid/__byteswap.h>
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __USE_GNU
#include <xlocale.h>
#endif /* __USE_GNU */

#ifdef __USE_SOLARIS
#include <getopt.h>
#endif /* __USE_SOLARIS */

#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <parts/waitmacros.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

__SYSDECL_BEGIN

#ifdef __RAND_MAX
#define RAND_MAX __RAND_MAX
#endif /* __RAND_MAX */
#ifdef __EXIT_SUCCESS
#define EXIT_SUCCESS __EXIT_SUCCESS
#endif /* __EXIT_SUCCESS */
#ifdef __EXIT_FAILURE
#define EXIT_FAILURE __EXIT_FAILURE
#endif /* __EXIT_FAILURE */

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
%[define_replacement(div_t = "struct __div_struct")]
%[define_replacement(ldiv_t = "struct __ldiv_struct")]
%[define_replacement(lldiv_t = "struct __lldiv_struct")]
%[define_type_class(div_t = "TS(__SIZEOF_DIV_STRUCT)")]
%[define_type_class(ldiv_t = "TS(__SIZEOF_LDIV_STRUCT)")]
%[define_type_class(lldiv_t = "TS(__SIZEOF_LLDIV_STRUCT)")]
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
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (__LIBCCALL *__atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */

}

%[define_crt_name_list(CNL_llabs       = ["llabs", "qabs"])]
%[define_crt_name_list(CNL_lldiv       = ["lldiv", "qdiv"])]
%[define_crt_name_list(CNL_strtol      = ["strtol"])]
%[define_crt_name_list(CNL_strtoul     = ["strtoul"])]
%[define_crt_name_list(CNL_strtoll     = ["strtoll", "strtoq"])]
%[define_crt_name_list(CNL_strtoull    = ["strtoull", "strtouq"])]
%[define_crt_name_list(CNL_strtoimax   = ["strtoimax"])]
%[define_crt_name_list(CNL_strtoumax   = ["strtoumax"])]
%[define_crt_name_list(CNL_strtol_l    = ["strtol_l", "_strtol_l", "__strtol_l"])]
%[define_crt_name_list(CNL_strtoul_l   = ["strtoul_l", "_strtoul_l", "__strtoul_l"])]
%[define_crt_name_list(CNL_strtoll_l   = ["strtoll_l", "_strtoll_l", "__strtoll_l", "strtoq_l"])]
%[define_crt_name_list(CNL_strtoull_l  = ["strtoull_l", "_strtoull_l", "__strtoull_l", "strtouq_l"])]
%[define_crt_name_list(CNL_strtoimax_l = ["strtoimax_l", "_strtoimax_l", "__strtoimax_l"])]
%[define_crt_name_list(CNL_strtoumax_l = ["strtoumax_l", "_strtoumax_l", "__strtoumax_l"])]



%#ifdef __USE_GNU
%{
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}


%[define(DEFINE_COMPAR_D_FN_T =
@@pp_ifndef __compar_d_fn_t_defined@@
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
@@pp_endif@@
)]

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.utility.stdlib")]]
[[decl_prefix(DEFINE_COMPAR_D_FN_T), throws, kernel]]
void qsort_r([[nonnull]] void *pbase, $size_t item_count, $size_t item_size,
             [[nonnull]] __compar_d_fn_t cmp, void *arg) {
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
	 *  - sizeof(size_t) == 4: item_count >= 0x67ea0dc9         (> 2.5 GiB is data at least)
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
	size_t total_bytes, gap;
	total_bytes = item_size * item_count;
	for (gap = 0; ++gap < item_count;)
		gap *= 3;
	while ((gap /= 3) != 0) {
		size_t i, gap_bytes;
		gap_bytes = item_size * gap;
		for (i = gap_bytes; i < total_bytes; i += item_size) {
			size_t j;
			for (j = i - gap_bytes;; j -= gap_bytes) {
				size_t swap_index;
				byte_t tmp, *a, *b;
				a = (byte_t *)pbase + j;
				b = a + gap_bytes;
				if ((*cmp)(a, b, arg) <= 0)
					break;
				swap_index = item_size;
				do {
					tmp  = *a;
					*a++ = *b;
					*b++ = tmp;
				} while (--swap_index);
				if (j < gap_bytes)
					break;
			}
		}
	}
}

%#endif /* __USE_GNU */

%
%#ifdef __USE_KOS

%{
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}

[[section(".text.crt{|.dos}.utility.stdlib")]]
[[decl_prefix(DEFINE_COMPAR_D_FN_T), throws, wunused, decl_include("<hybrid/typecore.h>")]]
void *bsearch_r([[nonnull]] void const *pkey, [[nonnull]] void const *pbase, $size_t item_count, $size_t item_size, [[nonnull]] __compar_d_fn_t cmp, void *arg)
	[([[nonnull]] void const *pkey, [[nonnull]] void *pbase, $size_t item_count, $size_t item_size, [[nonnull]] __compar_d_fn_t cmp, void *arg): void *]
	[([[nonnull]] void const *pkey, [[nonnull]] void const *pbase, $size_t item_count, $size_t item_size, [[nonnull]] __compar_d_fn_t cmp, void *arg): void const *]
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
		 * the  lower  and upper  bound  for comparison
		 * Assuming  an even  distribution, the  chance of  it being the
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

%[define(DEFINE_COMPAR_FN_T =
@@pp_ifndef ____compar_fn_t_defined@@
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
@@pp_endif@@
)]



%[define(DEFINE_INVOKE_COMPARE_HELPER =
@@pp_ifndef __LIBCCALL_CALLER_CLEANUP@@
@@pp_ifndef ____invoke_compare_helper_defined@@
@@push_namespace(local)@@
#define ____invoke_compare_helper_defined 1
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
@@pop_namespace@@
@@pp_endif@@
@@pp_endif@@
)]

[[section(".text.crt{|.dos}.utility.stdlib")]]
[[decl_prefix(DEFINE_COMPAR_FN_T), no_crt_dos_wrapper]] /* The DOS wrapper is implemented manually */
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER), throws, std, kernel, decl_include("<hybrid/typecore.h>")]]
void qsort([[nonnull]] void *pbase, size_t item_count,
           size_t item_size, [[nonnull]] __compar_fn_t cmp) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	qsort_r(pbase, item_count, item_size,
	        (int(__LIBCCALL *)(void const *, void const *, void *))(void *)cmp,
	        NULL);
@@pp_else@@
	qsort_r(pbase, item_count, item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)cmp);
@@pp_endif@@
}

[[section(".text.crt{|.dos}.utility.stdlib")]]
[[decl_prefix(DEFINE_COMPAR_FN_T), no_crt_dos_wrapper]] /* The DOS wrapper is implemented manually */
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER), wunused, std, throws, decl_include("<hybrid/typecore.h>")]]
void *bsearch([[nonnull]] void const *pkey, [[nonnull]] void const *pbase, size_t item_count, size_t item_size, [[nonnull]] __compar_fn_t cmp)
	[([[nonnull]] void const *pkey, [[nonnull]] void *pbase, size_t item_count, size_t item_size, [[nonnull]] __compar_fn_t cmp): void *]
	[([[nonnull]] void const *pkey, [[nonnull]] void const *pbase, size_t item_count, size_t item_size, [[nonnull]] __compar_fn_t cmp): void const *]
{
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	return (void *)bsearch_r(pkey, pbase, item_count, item_size,
	                         (int(__LIBCCALL *)(void const *, void const *, void *))(void *)cmp,
	                         NULL);
@@pp_else@@
	return (void *)bsearch_r(pkey, pbase, item_count, item_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	                         (void *)cmp);
@@pp_endif@@
}


[[section(".text.crt{|.dos}.math.utility")]]
[[const, wunused, nothrow, std, crtbuiltin]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, abs)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_abs64")]]
long labs(long x) {
	return x < 0 ? -x : x;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[[section(".text.crt{|.dos}.math.utility")]]
[[const, wunused, nothrow, std, crtbuiltin]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_llabs...)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, "abs")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, "labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_abs64")]]
__LONGLONG llabs(__LONGLONG x) {
	return x < 0 ? -x : x;
}
%(std, c, ccompat)#endif /* __USE_ISOC99 */


/* NOTE: `div_t', `ldiv_t' and `lldiv_t' return types need to be escaped, even if
 *       the associated unescaped types are actually defined in the current scope
 *       in order to work around a g++ bug I've discovered:
 *  When running `g++ -std=c++1z' or `g++ -std=gnu++1z', and `__LIBCCALL' is defined
 *  as non-empty,  g++  will  see  something like  this  as  definition  for  `div':
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
 *  However,  changing  the declaration  to  not use  `div_t',  but `struct __div_struct'
 *  fixes the problem (NOTE: The problem also goes away if `__attribute__((__stdcall__))'
 *  were to be removed,  however we can't do  the later since that  would break the  ABI)
 *  >> static inline
 *  >>     __attribute__((__always_inline__))
 *  >>     __attribute__((__const__))
 *  >>     __attribute__((__warn_unused_result__))
 *  >> struct __div_struct (__attribute__((__stdcall__)) div)(int __numer, int __denom) {
 *  >>     ...
 *  >> }
 *
 *  g++  seems to think that the first version is trying to declare `div_t' as a
 *  variable with a  c++ initializer  (remember: you can  declare c++  variables
 *  as `int x(42);' instead of `int x = 42;'). A point that is proven even more,
 *  as re-writing the  declaration like  the following also  fixes the  problem:
 *  >> static inline
 *  >>     __attribute__((__always_inline__))
 *  >>     __attribute__((__const__))
 *  >>     __attribute__((__warn_unused_result__))
 *  >> div_t __attribute__((__stdcall__)) div(int __numer, int __denom) {
 *  >>     ...
 *  >> }
 *
 *  However, this last  version also wouldn't  work for us,  since that would  leave
 *  the declaration  of  `div'  vulnerable to  `#define div(a, b)'  macro  overrides
 *  being declared prior to the header being included (which we prevent by declaring
 *  functions  such that their  names cannot be  interpreted by function-like macros
 *  using the same name)
 *
 *  Honestly: I don't really understand why using the struct-prefixed name (`struct __div_struct')
 *  fixes the problem (Note that  when leaving out the  `struct' and only writing  `__div_struct',
 *  a different error ```error: expected primary-expression before '__attribute__'``` occurs  with
 *  is also incorrect in this scenario), however a work-around is a work-around, and I'm satisfied
 *
 *  For reference, I've created a bug report for this problem here:
 *  https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92438
 *
 */

[[const, wunused, std]]
[[section(".text.crt{|.dos}.math.utility")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, div)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_lldiv...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
$ldiv_t ldiv(long numer, long denom) {
	ldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[[const, wunused, std]]
[[section(".text.crt{|.dos}.math.utility")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_lldiv...)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, div)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, ldiv)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
$lldiv_t lldiv(__LONGLONG numer, __LONGLONG denom) {
	lldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}
%(std, c, ccompat)#endif /* __USE_ISOC99 */

[[const, wunused, nothrow, std, crtbuiltin]]
[[section(".text.crt{|.dos}.math.utility")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_abs64")]]
int abs(int x) {
	return x < 0 ? -x : x;
}

[[const, wunused, std]]
[[section(".text.crt{|.dos}.math.utility")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("ldiv")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(CNL_lldiv...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
struct __div_struct div(int numer, int denom) {
	div_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}


%(std)#ifdef __cplusplus
%(std)#ifdef __CORRECT_ISO_CPP_STDLIB_H_PROTO
%[insert:std_function_nousing(abs = labs, externLinkageOverride: "C++")]
%[insert:std_function_nousing(div = ldiv, externLinkageOverride: "C++")]
%(std)#if defined(__USE_ISOC99) && defined(__COMPILER_HAVE_LONGLONG)
%[insert:std_function_nousing(abs = llabs, externLinkageOverride: "C++")]
%[insert:std_function_nousing(div = lldiv, externLinkageOverride: "C++")]
%(std)#endif /* __USE_ISOC99 && __COMPILER_HAVE_LONGLONG */
%(std)#endif /* __CORRECT_ISO_CPP_STDLIB_H_PROTO */
%(std)#if defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
%[insert:std_function_nousing(abs = fabsf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(abs = fabs, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(abs = fabsl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
//TODO: %(std)#ifdef __COMPILER_HAVE_FLOAT128
//TODO: %(std)__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __float128 __NOTHROW(__LIBCCALL abs)(__float128 __x) { return __x < 0 ? -__x : __x; }
//TODO: %(std)#endif /* __COMPILER_HAVE_FLOAT128 */
%(std)#endif /* __CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */
%(std)#endif /* __cplusplus */

[[impl_include("<hybrid/typecore.h>")]]
[[std, wunused, section(".text.crt{|.dos}.fs.environ")]]
[[requires_include("<libc/local/environ.h>")]]
[[userimpl, requires(defined(__LOCAL_environ))]]
char *getenv([[nonnull]] char const *varname) {
	char *result, **envp;
	if unlikely(!varname)
		return NULL;
	envp = __LOCAL_environ;
	if unlikely(!envp)
		result = NULL;
	else {
		size_t namelen;
		namelen = strlen(varname);
		for (; (result = *envp) != NULL; ++envp) {
			if (memcmp(result, varname, namelen * sizeof(char)) != 0 ||
			    result[namelen] != '=')
				continue;
			result += namelen + 1;
			break;
		}
	}
	return result;
}

[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[std, decl_include("<hybrid/typecore.h>")]]
int mblen([[inp_opt(maxlen)]] char const *str, size_t maxlen) {
	return mbrlen(str, maxlen, NULL);
}

[[std, wchar]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int mbtowc(wchar_t *__restrict pwc,
           [[inp_opt(maxlen)]] char const *__restrict str,
           size_t maxlen) {
	return mbrtowc(pwc, str, maxlen, NULL);
}

[[std, wchar]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int wctomb(char *str, wchar_t wc) {
	return wcrtomb(str, wc, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
size_t mbstowcs([[nonnull]] wchar_t *__restrict dst,
                [[nonnull]] char const *__restrict src,
                size_t dstlen) {
	return mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
size_t wcstombs([[nonnull]] char *__restrict dst,
                [[nonnull]] wchar_t const *__restrict src,
                size_t dstlen) {
	return wcsrtombs(dst, (wchar_t const **)&src, dstlen, NULL);
}

@@>> system(3)
@@Execute a given `command' on the system interpreter (as in `sh -c $command')
@@The return value is the exit status after running `command'
@@When `command' is `NULL' only check if a system interpreter is available.
@@When no system interpreter is available, `127' is returned.
[[cp, std, guard, section(".text.crt{|.dos}.fs.exec.system")]]
[[impl_include("<asm/os/wait.h>")]]
[[requires($has_function(shexec) && $has_function(_Exit) &&
           $has_function(waitpid) &&
           ($has_function(vfork) || $has_function(fork)))]]
int system([[nullable]] char const *command) {
	int status;
	pid_t cpid, error;
@@pp_if $has_function(vfork)@@
	cpid = vfork();
@@pp_else@@
	cpid = fork();
@@pp_endif@@
	if (cpid == 0) {
		shexec(command);
		/* NOTE: system() must return ZERO(0) if no command processor is available. */
		_Exit(command ? 127 : 0);
	}
	if (cpid < 0)
		return -1;
	for (;;) {
		error = waitpid(cpid, &status, 0);
		if (error == cpid)
			break;
		if (error >= 0)
			continue;
@@pp_if defined(__libc_geterrno) && defined(__EINTR)@@
		if (__libc_geterrno() != __EINTR)
			return -1;
@@pp_else@@
		return -1;
@@pp_endif@@
	}
@@pp_ifdef __WIFEXITED@@
	if (!__WIFEXITED(status))
		return 1;
@@pp_endif@@
@@pp_ifdef __WEXITSTATUS@@
	return __WEXITSTATUS(status);
@@pp_else@@
	return status;
@@pp_endif@@
}


[[std, guard, crtbuiltin, ATTR_NORETURN, throws]]
[[section(".text.crt{|.dos}.application.exit")]]
[[export_alias("_ZSt9terminatev")]]
[[dos_only_export_alias("?terminate@@YAXXZ")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_ABORT))]]
[[requires_function(_Exit), impl_include("<asm/os/stdlib.h>")]]
void abort() {
	_Exit(@__EXIT_FAILURE@);
}

[[std, guard, crtbuiltin, ATTR_NORETURN, throws]]
[[section(".text.crt{|.dos}.application.exit")]]
[[alias("quick_exit", "_exit", "_Exit")]]
void exit(int status);

%[define(DEFINE_ATEXIT_FUNC_T =
#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (__LIBCCALL *__atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */
)]

[[no_crt_dos_wrapper]] /* The DOS wrapper is implemented manually */
[[section(".text.crt{|.dos}.sched.process")]]
[[std, alias("at_quick_exit"), decl_prefix(DEFINE_ATEXIT_FUNC_T)]]
int atexit([[nonnull]] __atexit_func_t func);


%(std, c, ccompat)#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
[[section(".text.crt{|.dos}.sched.process")]]
[[std, ATTR_NORETURN, throws, alias("exit", "_exit", "_Exit")]]
void quick_exit(int status);

[[no_crt_dos_wrapper]] /* The DOS wrapper is implemented manually */
[[section(".text.crt{|.dos}.sched.process")]]
[[std, alias("atexit"), decl_prefix(DEFINE_ATEXIT_FUNC_T)]]
int at_quick_exit([[nonnull]] __atexit_func_t func);
%(std, c, ccompat)#endif /* __USE_ISOC11 || __USE_ISOCXX11 */

%(std, c, ccompat)#ifdef __USE_ISOC99
[[section(".text.crt{|.dos}.sched.process")]]
[[std, crtbuiltin, export_alias("_exit"), alias("quick_exit", "exit")]]
[[if(__has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("_exit", { __builtin__exit(status); })]]
[[ATTR_NORETURN, throws, section(".text.crt{|.dos}.application.exit")]]
void _Exit(int status);
%(std, c, ccompat)#endif /* __USE_ISOC99 */

[[ignore, nocrt, alias("calloc"), decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
void *crt_calloc(size_t count, size_t num_bytes);

[[section(".text.crt{|.dos}.heap.malloc")]]
[[std, guard, crtbuiltin, libc, decl_include("<hybrid/typecore.h>")]]
[[ATTR_ALLOC_SIZE((1)), wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[userimpl, requires($has_function(crt_calloc) || $has_function(realloc) || $has_function(memalign))]]
void *malloc(size_t num_bytes) {
@@pp_if $has_function(crt_calloc)@@
	return crt_calloc(1, num_bytes);
@@pp_elif $has_function(realloc)@@
	return realloc(NULL, num_bytes);
@@pp_else@@
	return memalign(__LIBC_MALLOC_ALIGNMENT, num_bytes);
@@pp_endif@@
}

[[section(".text.crt{|.dos}.heap.malloc")]]
[[guard, std, libc, crtbuiltin, decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
[[userimpl, requires_function(malloc), impl_include("<hybrid/__overflow.h>")]]
void *calloc(size_t count, size_t num_bytes) {
	void *result;
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(count, num_bytes, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = malloc(total_bytes);
	if likely(result)
		memset(result, 0, total_bytes);
	return result;
}

[[section(".text.crt{|.dos}.heap.malloc")]]
[[guard, std, libc, crtbuiltin, decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
void *realloc(void *mallptr, size_t num_bytes);

[[section(".text.crt{|.dos}.heap.malloc")]]
[[guard, std, libc, crtbuiltin, export_alias("cfree")]]
void free(void *mallptr);


[[std, nothrow, userimpl]]
[[section(".text.crt{|.dos}.random")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("srandom")]]
void srand(long seed) {
	/* ... */
	(void)seed;
	COMPILER_IMPURE();
}

[[nothrow, std, userimpl]]
[[section(".text.crt{|.dos}.random")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("random")]]
int rand() {
	COMPILER_IMPURE();
	/* https://xkcd.com/221/ */
	return 4;
}


/* Convert a string to an integer.  */
[[std, wunused, pure]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("atol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("atoll")]]
int atoi([[nonnull]] char const *__restrict nptr) {
@@pp_if __SIZEOF_INT__ <= 4@@
	return (int)strto32(nptr, NULL, 10);
@@pp_else@@
	return (int)strto64(nptr, NULL, 10);
@@pp_endif@@
}

[[std, wunused, pure]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, "atoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("atoll")]]
long atol([[nonnull]] char const *__restrict nptr) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (long)strto32(nptr, NULL, 10);
@@pp_else@@
	return (long)strto64(nptr, NULL, 10);
@@pp_endif@@
}

%#if defined(__LONGLONG) && defined(__USE_ISOC99)
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[std, wunused, pure, decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, atoi)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, atol)]]
__LONGLONG atoll([[nonnull]] char const *__restrict nptr) {
@@pp_if __SIZEOF_LONG_LONG__@@
	return (__LONGLONG)strto32(nptr, NULL, 10);
@@pp_else@@
	return (__LONGLONG)strto64(nptr, NULL, 10);
@@pp_endif@@
}
%#endif /* __LONGLONG && __USE_ISOC99 */


[[std, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoul...)]]
[[alt_variant_of(__SIZEOF_LONG__ == 4, strtou32)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_strtoumax...)]]
unsigned long strtoul([[nonnull]] char const *__restrict nptr,
                      [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (unsigned long)strtou32(nptr, endptr, base);
@@pp_else@@
	return (unsigned long)strtou64(nptr, endptr, base);
@@pp_endif@@
}

[[std, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtol...)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == 4, strto32)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_strtoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64)]]
long strtol([[nonnull]] char const *__restrict nptr,
            [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (long)strto32(nptr, endptr, base);
@@pp_else@@
	return (long)strto64(nptr, endptr, base);
@@pp_endif@@
}

%(std)#ifdef __LONGLONG
%(std)#ifdef __USE_ISOC99
[[std, guard, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoull...)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strtou64)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strtou32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias("_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strtou32)]]
__ULONGLONG strtoull([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG_LONG__ <= 4@@
	return (__ULONGLONG)strtou32(nptr, endptr, base);
@@pp_else@@
	return (__ULONGLONG)strtou64(nptr, endptr, base);
@@pp_endif@@
}

[[std, guard, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoll...)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strto64)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strto32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias("_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32)]]
__LONGLONG strtoll([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG_LONG__ <= 4@@
	return (__LONGLONG)strto32(nptr, endptr, base);
@@pp_else@@
	return (__LONGLONG)strto64(nptr, endptr, base);
@@pp_endif@@
}
%(std)#endif /* __USE_ISOC99 */
%(std)#endif /* __LONGLONG */

%(std, c, ccompat)#ifndef __NO_FPU
[[std, ATTR_LEAF, wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
double atof([[nonnull]] char const *__restrict nptr) {
	return strtod(nptr, NULL);
}

[[std, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[impl_include("<asm/crt/stdio.h>")]]
[[impl_prefix(
@@pp_if __SIZEOF_CHAR__ == 1@@
DEFINE_VSSCANF_HELPERS_C8
@@pp_elif __SIZEOF_CHAR__ == 2@@
DEFINE_VSSCANF_HELPERS_C16
@@pp_else@@
DEFINE_VSSCANF_HELPERS_C32
@@pp_endif@@
)]]
[[dependency(unicode_readutf8, unicode_readutf8_rev)]]
[[alt_variant_of(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__, strtod)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("strtold")]]
double strtod([[nonnull]] char const *__restrict nptr,
              [[nullable]] char **endptr) {
	double result;
	char const *text_pointer = nptr;
@@pp_if __SIZEOF_CHAR__ == 1@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;
@@pp_elif __SIZEOF_CHAR__ == 2@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;
@@pp_else@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;
@@pp_endif@@
	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}

%(std)#ifdef __USE_ISOC99
[[guard, std, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[impl_include("<asm/crt/stdio.h>")]]
[[impl_prefix(
@@pp_if __SIZEOF_CHAR__ == 1@@
DEFINE_VSSCANF_HELPERS_C8
@@pp_elif __SIZEOF_CHAR__ == 2@@
DEFINE_VSSCANF_HELPERS_C16
@@pp_else@@
DEFINE_VSSCANF_HELPERS_C32
@@pp_endif@@
)]]
[[dependency(unicode_readutf8, unicode_readutf8_rev)]]
float strtof([[nonnull]] char const *__restrict nptr,
             [[nullable]] char **endptr) {
	float result;
	char const *text_pointer = nptr;
@@pp_if __SIZEOF_CHAR__ == 1@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;
@@pp_elif __SIZEOF_CHAR__ == 2@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;
@@pp_else@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;
@@pp_endif@@
	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[guard, std, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[impl_include("<asm/crt/stdio.h>")]]
[[impl_prefix(
@@pp_if __SIZEOF_CHAR__ == 1@@
DEFINE_VSSCANF_HELPERS_C8
@@pp_elif __SIZEOF_CHAR__ == 2@@
DEFINE_VSSCANF_HELPERS_C16
@@pp_else@@
DEFINE_VSSCANF_HELPERS_C32
@@pp_endif@@
)]]
[[dependency(unicode_readutf8, unicode_readutf8_rev)]]
[[alt_variant_of(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__, strtod)]]
__LONGDOUBLE strtold([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr) {
	__LONGDOUBLE result;
	char const *text_pointer = nptr;
@@pp_if __SIZEOF_CHAR__ == 1@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;
@@pp_elif __SIZEOF_CHAR__ == 2@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;
@@pp_else@@
	if (!format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;
@@pp_endif@@
	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_ISOC99 */
%(std, c, ccompat)#endif /* !__NO_FPU */




%
%#ifdef __USE_KOS

@@>> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
@@Safely parse & return an integer from `nptr', and store any potential
@@errors in `*error' (if non-NULL). The following errors are defined:
@@ - 0:         Success
@@ - ECANCELED: Nothing was parsed.
@@              In this case, `*endptr' is set to the original `nptr'
@@              (iow: leading spaces are _not_ skipped in `*endptr'),
@@              and the returned integer is `0'
@@ - ERANGE:    Integer over- or under-flow while parsing.
@@              In this case, `*endptr' is still updated correctly, and
@@              the returned integer is the closest representable value
@@              to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
@@              This error supercedes `EINVAL' if both conditions apply.
@@ - EINVAL:    Only when `endptr == NULL': The parsed number is followed
@@              by at least 1 additional non-whitespace character.
@@              The returned integer value is not affected by this error.
[[kernel, ATTR_LEAF]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/errno.h>", "<hybrid/__overflow.h>")]]
$uint32_t strtou32_r([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[nullable]] $errno_t *error) {
	uint32_t result;
	char const *num_start = nptr;
	char const *num_iter;
	while (isspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {
@@pp_ifdef __ERANGE@@
				*error = __ERANGE;
@@pp_else@@
				*error = 1;
@@pp_endif@@
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			return (uint32_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
@@pp_ifdef __ECANCELED@@
			*error = __ECANCELED;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
@@pp_ifdef __EINVAL@@
					*error = __EINVAL;
@@pp_else@@
					*error = 1;
@@pp_endif@@
				}
			}
		}
	}
	return result;
}

[[kernel, ATTR_LEAF, doc_alias("strtou32_r")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/errno.h>", "<hybrid/__overflow.h>")]]
[[impl_include("<hybrid/limitcore.h>")]]
$int32_t strto32_r([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                   [[nullable]] $errno_t *error) {
	int32_t result;
	char sign;
	char const *num_start = nptr;
	char const *num_iter;
	while (isspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {
@@pp_ifdef __ERANGE@@
				*error = __ERANGE;
@@pp_else@@
				*error = 1;
@@pp_endif@@
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
@@pp_ifdef __ECANCELED@@
			*error = __ECANCELED;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
@@pp_ifdef __EINVAL@@
					*error = __EINVAL;
@@pp_else@@
					*error = 1;
@@pp_endif@@
				}
			}
		}
	}
	return result;
}



%#ifdef __UINT64_TYPE__
[[kernel, ATTR_LEAF, doc_alias("strtou32_r")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/errno.h>", "<hybrid/__overflow.h>")]]
$uint64_t strtou64_r([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[nullable]] $errno_t *error) {
	uint64_t result;
	char const *num_start = nptr;
	char const *num_iter;
	while (isspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {
@@pp_ifdef __ERANGE@@
				*error = __ERANGE;
@@pp_else@@
				*error = 1;
@@pp_endif@@
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			return (uint64_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
@@pp_ifdef __ECANCELED@@
			*error = __ECANCELED;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
@@pp_ifdef __EINVAL@@
					*error = __EINVAL;
@@pp_else@@
					*error = 1;
@@pp_endif@@
				}
			}
		}
	}
	return result;
}

[[kernel, ATTR_LEAF, doc_alias("strtou32_r")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/errno.h>", "<hybrid/__overflow.h>")]]
[[impl_include("<hybrid/limitcore.h>")]]
$int64_t strto64_r([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                   [[nullable]] $errno_t *error) {
	int64_t result;
	char sign;
	char const *num_start = nptr;
	char const *num_iter;
	while (isspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {
@@pp_ifdef __ERANGE@@
				*error = __ERANGE;
@@pp_else@@
				*error = 1;
@@pp_endif@@
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
@@pp_ifdef __ECANCELED@@
			*error = __ECANCELED;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
@@pp_ifdef __EINVAL@@
					*error = __EINVAL;
@@pp_else@@
					*error = 1;
@@pp_endif@@
				}
			}
		}
	}
	return result;
}
%#endif /* __UINT64_TYPE__ */


/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
[[nocrt, ATTR_LEAF, decl_include("<features.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
long strtol_r([[nonnull]] char const *__restrict nptr,
              [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
              [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_LONG__ >= 8@@
	return (long)strto64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG__ >= 4@@
	return (long)strto32_r(nptr, endptr, base, error);
@@pp_else@@
	s32 result = strto32_r(nptr, endptr, base, error);
	if (result > __LONG_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_MAX__;
	} else if (result < __LONG_MIN__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_MIN__;
	}
	return (long)result;
@@pp_endif@@
}

[[nocrt, ATTR_LEAF, decl_include("<features.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strtou32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strtou64_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
unsigned long strtoul_r([[nonnull]] char const *__restrict nptr,
                        [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                        [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_LONG__ >= 8@@
	return (unsigned long)strtou64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG__ >= 4@@
	return (unsigned long)strtou32_r(nptr, endptr, base, error);
@@pp_else@@
	u32 result = strtou32_r(nptr, endptr, base, error);
	if (result > __ULONG_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __ULONG_MAX__;
	}
	return (unsigned long)result;
@@pp_endif@@
}

%#ifdef __LONGLONG
[[nocrt, ATTR_LEAF, decl_include("<features.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strto32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
__LONGLONG strtoll_r([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_LONG_LONG__ >= 8@@
	return (__LONGLONG)strto64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG_LONG__ >= 4@@
	return (__LONGLONG)strto32_r(nptr, endptr, base, error);
@@pp_else@@
	s32 result = strto32_r(nptr, endptr, base, error);
	if (result > __LONG_LONG_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_LONG_MAX__;
	} else if (result < __LONG_LONG_MIN__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_LONG_MIN__;
	}
	return (__LONGLONG)result;
@@pp_endif@@
}

[[nocrt, ATTR_LEAF, decl_include("<features.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strtou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strtou32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
__ULONGLONG strtoull_r([[nonnull]] char const *__restrict nptr,
                       [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                       [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_LONG_LONG__ >= 8@@
	return (__ULONGLONG)strtou64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG_LONG__ >= 4@@
	return (__ULONGLONG)strtou32_r(nptr, endptr, base, error);
@@pp_else@@
	u32 result = strtou32_r(nptr, endptr, base, error);
	if (result > __ULONG_LONG_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __ULONG_LONG_MAX__;
	}
	return (__ULONGLONG)result;
@@pp_endif@@
}
%#endif /* __LONGLONG */
/************************************************************************/




@@>> strto32(3), strto64(3), strtou32(3), strtou64(3)
@@Convert a string (radix=`base') from `nptr' into an integer,
@@and store a pointer to the end of the number in `*endptr'.
@@If `errno(3)' support is available, integer overflow is handled
@@by setting `errno=ERANGE', and returning the greatest or lowest
@@valid integer (`U?INTn_(MIN|MAX))'. (though note that
@@`endptr' (if non-NULL) is still updated in this case!)
@@Upon success, `errno' is left unchanged, and the integer repr
@@of the parsed number is returned. When no integer was parsed,
@@then `0' is returned, `*endptr' is set to `nptr', but `errno'
@@will not have been modified.
@@@return: * :         Success: The parsed integer
@@@return: 0 :         [*endptr=nptr] error: Nothing was parsed
@@@return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
@@@return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent
[[kernel, ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoumax...)]]
[[impl_include("<libc/errno.h>")]]
$uint32_t strtou32([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	uint32_t result;
	errno_t error;
	result = strtou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		__libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strtou32_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

[[kernel, ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoimax...)]]
[[doc_alias("strtou32"), impl_include("<libc/errno.h>")]]
$int32_t strto32([[nonnull]] char const *__restrict nptr,
                 [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	int32_t result;
	errno_t error;
	result = strto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		__libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strto32_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

%#ifdef __UINT64_TYPE__
[[kernel, ATTR_LEAF, alias("_strtoui64")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("_strtoui64")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoumax...)]]
[[doc_alias("strtou32"), impl_include("<libc/errno.h>")]]
$uint64_t strtou64([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	uint64_t result;
	errno_t error;
	result = strtou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		__libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strtou64_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

[[kernel, ATTR_LEAF, alias("_strtoi64")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("_strtoi64")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoimax...)]]
[[doc_alias("strtou32"), impl_include("<libc/errno.h>")]]
$int64_t strto64([[nonnull]] char const *__restrict nptr,
                 [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	int64_t result;
	errno_t error;
	result = strto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		__libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strto64_r(nptr, endptr, base, NULL);
@@pp_endif@@
}
%#endif /* __UINT64_TYPE__ */

%
%#ifdef __USE_XOPEN2K8
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoumax_l...)]]
$uint32_t strtou32_l([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strtou32(nptr, endptr, base);
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoimax_l...)]]
$int32_t strto32_l([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strto32(nptr, endptr, base);
}

%#ifdef __UINT64_TYPE__
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ATTR_LEAF, dos_only_export_alias("_strtoui64_l")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoumax_l...)]]
$uint64_t strtou64_l([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strtou64(nptr, endptr, base);
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ATTR_LEAF, dos_only_export_alias("_strtoi64_l")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoimax_l...)]]
$int64_t strto64_l([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strto64(nptr, endptr, base);
}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */
%#endif /* __USE_KOS */

%
%#if (defined(__USE_MISC) || defined(__USE_DOS) || \
%     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))


%#ifndef __NO_FPU
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[wunused, dos_only_export_alias("_gcvt")]]
[[impl_include("<hybrid/floatcore.h>")]]
char *gcvt(double val, int ndigit, [[nonnull]] char *buf) {
@@pp_ifndef DBL_NDIGIT_MAX@@
@@pp_if __DBL_MANT_DIG__ == 53@@
#define DBL_NDIGIT_MAX 17
@@pp_elif __DBL_MANT_DIG__ == 24@@
#define DBL_NDIGIT_MAX 9
@@pp_elif __DBL_MANT_DIG__ == 56@@
#define DBL_NDIGIT_MAX 18
@@pp_else@@
	/* ceil(M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define DBL_NDIGIT_MAX (__DBL_MANT_DIG__ / 4)
@@pp_endif@@
@@pp_endif@@
	if (ndigit > DBL_NDIGIT_MAX)
		ndigit = DBL_NDIGIT_MAX;
	sprintf(buf, "%.*g", ndigit, val);
	return buf;
}
%#endif /* !__NO_FPU */
%#endif /* ... */


%
%#ifdef __USE_POSIX
[[userimpl]]
[[section(".text.crt{|.dos}.random")]]
int rand_r([[nonnull]] unsigned int *__restrict pseed) {
	(void)pseed;
	COMPILER_IMPURE();
	/* https://xkcd.com/221/ */
	return 4;
}
%#endif /* __USE_POSIX */


%
%#ifdef __USE_MISC

%#ifdef __LONGLONG
%[insert:function(strtoq = strtoll)]
%[insert:function(strtouq = strtoull)]
%#endif /* __LONGLONG */

%#ifndef __NO_FPU

[[decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("_ecvt_s")]]
errno_t dos_ecvt_s([[nonnull]] char *buf,
                   $size_t buflen, double val, int ndigit,
                   [[nonnull]] int *__restrict decptr,
                   [[nonnull]] int *__restrict sign);

[[decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("_fcvt_s")]]
errno_t dos_fcvt_s([[nonnull]] char *buf,
                   $size_t buflen, double val, int ndigit,
                   [[nonnull]] int *__restrict decptr,
                   [[nonnull]] int *__restrict sign);

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int ecvt_r(double val, int ndigit,
           [[nonnull]] int *__restrict decptr,
           [[nonnull]] int *__restrict sign,
           [[nonnull]] char *__restrict buf, $size_t len) {
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

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int fcvt_r(double val, int ndigit,
           [[nonnull]] int *__restrict decptr,
           [[nonnull]] int *__restrict sign,
           [[nonnull]] char *__restrict buf, $size_t len) {
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
[[impl_include("<hybrid/floatcore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("gcvt", "_gcvt")]]
char *qgcvt(__LONGDOUBLE val, int ndigit, [[nonnull]] char *buf) {
@@pp_ifndef LDBG_NDIGIT_MAX@@
@@pp_if __LDBL_MANT_DIG__ == 53@@
#define LDBG_NDIGIT_MAX 17
@@pp_elif __LDBL_MANT_DIG__ == 24@@
#define LDBG_NDIGIT_MAX 9
@@pp_elif __LDBL_MANT_DIG__ == 56@@
#define LDBG_NDIGIT_MAX 18
@@pp_else@@
	/* ceil(M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define LDBG_NDIGIT_MAX (__LDBL_MANT_DIG__ / 4)
@@pp_endif@@
@@pp_endif@@
	if (ndigit > LDBG_NDIGIT_MAX)
		ndigit = LDBG_NDIGIT_MAX;
	sprintf(buf, "%.*Lg", ndigit, val);
	return buf;
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int qecvt_r(__LONGDOUBLE val, int ndigit,
            [[nonnull]] int *__restrict decptr,
            [[nonnull]] int *__restrict sign,
            [[nonnull]] char *__restrict buf, $size_t len) {
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

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int qfcvt_r(__LONGDOUBLE val, int ndigit,
            [[nonnull]] int *__restrict decptr,
            [[nonnull]] int *__restrict sign,
            [[nonnull]] char *__restrict buf, $size_t len) {
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

%(auto_source){
#ifndef __KERNEL__
static char qcvt_buffer[32];
#endif /* !__KERNEL__ */
}


[[wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("ecvt", "_ecvt")]]
char *qecvt(__LONGDOUBLE val, int ndigit,
            [[nonnull]] int *__restrict decptr,
            [[nonnull]] int *__restrict sign) {
@@pp_ifndef __BUILDING_LIBC@@
	static char qcvt_buffer[32];
@@pp_endif@@
	if (qecvt_r(val, ndigit, decptr, sign,  qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}

[[wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("fcvt", "_fcvt")]]
char *qfcvt(__LONGDOUBLE val, int ndigit,
            [[nonnull]] int *__restrict decptr,
            [[nonnull]] int *__restrict sign) {
@@pp_ifndef __BUILDING_LIBC@@
	static char qcvt_buffer[32];
@@pp_endif@@
	if (qfcvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

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
[[section(".text.crt{|.dos}.random")]]
int drand48_r([[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] double *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int erand48_r([[nonnull]] unsigned short xsubi[3], [[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] double *__restrict result);
%#endif /* !__NO_FPU */

[[section(".text.crt{|.dos}.random")]]
int lrand48_r([[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] long *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int nrand48_r([[nonnull]] unsigned short xsubi[3], [[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] long *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int mrand48_r([[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] long *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int jrand48_r([[nonnull]] unsigned short xsubi[3], [[nonnull]] struct drand48_data *__restrict buffer, [[nonnull]] long *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int srand48_r(long seedval, [[nonnull]] struct drand48_data *buffer);

[[section(".text.crt{|.dos}.random")]]
int seed48_r([[nonnull]] unsigned short seed16v[3], [[nonnull]] struct drand48_data *buffer);

[[section(".text.crt{|.dos}.random")]]
int lcong48_r([[nonnull]] unsigned short param[7], [[nonnull]] struct drand48_data *buffer);

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

[[section(".text.crt{|.dos}.random")]]
int random_r([[nonnull]] struct random_data *__restrict buf, [[nonnull]] $int32_t *__restrict result);

[[section(".text.crt{|.dos}.random")]]
int srandom_r(unsigned int seed, [[nonnull]] struct random_data *buf);

[[section(".text.crt{|.dos}.random")]]
int initstate_r(unsigned int seed, [[nonnull]] char *__restrict statebuf, $size_t statelen, [[nonnull]] struct random_data *__restrict buf);

[[section(".text.crt{|.dos}.random")]]
int setstate_r([[nonnull]] char *__restrict statebuf, [[nonnull]] struct random_data *__restrict buf);

%typedef void (__LIBKCALL *__on_exit_func_t)(int __status, void *__arg);
[[section(".text.crt{|.dos}.sched.process")]]
int on_exit([[nonnull]] __on_exit_func_t func, void *arg);

[[section(".text.crt{|.dos}.fs.environ")]]
int clearenv();


@@>> mkstemps(3), mkstemps64(3)
@@Replace the last 6 characters of `template_' (which are followed by exactly
@@`suffixlen' more characters that are left alone), which must be filled with
@@all 'X'-characters before the call (else errno=EINVAL + return -1), with
@@random characters such that the filename described by `template_' will not
@@already exists. Then, create a new file with `O_RDWR' and return the file
@@descriptor of that file.
@@@param: suffixlen: The # of trailing characters to-be ignored
@@                   after the required 6 trailing 'X'-characters.
[[section(".text.crt{|.dos}.fs.utility")]]
[[wunused, guard, decl_include("<features.h>", "<bits/types.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("mkstemps64")]]
[[export_alias("mkstemps64"), requires_function(mkostemps)]]
$fd_t mkstemps([[nonnull]] char *template_, __STDC_INT_AS_SIZE_T suffixlen) {
	return mkostemps(template_, suffixlen, 0);
}

[[wunused, pure]]
[[section(".text.crt{|.dos}.utility.locale")]]
int rpmatch([[nonnull]] char const *response) {
	char c = response[0];
	if (c == 'n' || c == 'N')
		return 0;
	if (c == 'y' || c == 'Y')
		return 1;
	return -1;
}

%[insert:extern(cfree)]

%#ifndef __NO_FPU
[[cp, guard, decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int getloadavg(double loadavg[], __STDC_INT_AS_SIZE_T nelem);
%#endif /* !__NO_FPU */

%#ifdef __USE_LARGEFILE64
[[alias("mkstemps64"), nocrt, largefile64_variant_of(mkstemps)]]
[[wunused, requires_function(mkostemps64), decl_include("<features.h>", "<bits/types.h>")]]
$fd_t mkstemps64([[nonnull]] char *template_, __STDC_INT_AS_SIZE_T suffixlen) {
	return mkostemps64(template_, suffixlen, 0);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K))
%[insert:extern(valloc)]
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) */

%
%#ifdef __USE_XOPEN2K
%[insert:extern(posix_memalign)]

[[ignore, nocrt, alias("_putenv_s")]]
int dos_putenv_s([[nonnull]] char const *varname,
                 [[nonnull]] char const *val);

[[section(".text.crt{|.dos}.fs.environ")]]
[[userimpl, requires_function(getenv, dos_putenv_s)]]
int setenv([[nonnull]] char const *varname,
           [[nonnull]] char const *val, int replace) {
	if (!replace && getenv(varname))
		return 0;
	return dos_putenv_s(varname, val);
}

[[section(".text.crt{|.dos}.fs.environ")]]
[[impl_include("<parts/malloca.h>")]]
[[userimpl, requires_function(putenv)]]
int unsetenv([[nonnull]] char const *varname) {
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
	copy[namelen]     = '=';
	copy[namelen + 1] = '\0';
	result = putenv(copy);
	@__freea@(copy);
	return result;
}
%#endif /* __USE_XOPEN2K */

%
%(c,std)#ifdef __USE_ISOCXX17
[[std, guard]]
aligned_alloc(*) = memalign;
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
#define MB_CUR_MAX (__ctype_get_mb_cur_max())
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define MB_CUR_MAX 7 /* == UNICODE_UTF8_CURLEN */
#endif /* !__CRT_HAVE___ctype_get_mb_cur_max */
#endif /* !MB_CUR_MAX */
}


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
%#ifndef __NO_FPU
[[section(".text.crt{|.dos}.random")]]
double drand48();
%#endif /* !__NO_FPU */

[[section(".text.crt{|.dos}.random")]]
long lrand48();

[[section(".text.crt{|.dos}.random")]]
long mrand48();

%#ifndef __NO_FPU
[[section(".text.crt{|.dos}.random")]]
double erand48([[nonnull]] unsigned short xsubi[3]);
%#endif /* !__NO_FPU */

[[section(".text.crt{|.dos}.random")]]
long nrand48([[nonnull]] unsigned short xsubi[3]);

[[section(".text.crt{|.dos}.random")]]
long jrand48([[nonnull]] unsigned short xsubi[3]);

[[section(".text.crt{|.dos}.random")]]
void srand48(long seedval);

[[section(".text.crt{|.dos}.random")]]
unsigned short *seed48([[nonnull]] unsigned short seed16v[3]);

[[section(".text.crt{|.dos}.random")]]
void lcong48([[nonnull]] unsigned short param[7]);
%#endif /* __USE_MISC || __USE_XOPEN */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
[[section(".text.crt{|.dos}.fs.environ")]]
[[dos_only_export_alias("_putenv")]]
int putenv([[nonnull]] char *string);
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

[[userimpl]]
[[section(".text.crt{|.dos}.random")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("rand")]]
long random() {
	return (long)rand();
}

[[userimpl]]
[[section(".text.crt{|.dos}.random")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("srand")]]
void srandom(unsigned int seed) {
	srand((long)seed);
}

[[section(".text.crt{|.dos}.random")]]
char *initstate(unsigned int seed, [[outp(statelen)]] char *statebuf, $size_t statelen);

[[section(".text.crt{|.dos}.random")]]
char *setstate([[nonnull]] char *statebuf);


[[wunused]]
[[section(".text.crt{|.dos}.string.encrypt")]]
char *l64a(long n); /* TODO: Implement here */

[[wunused, pure]]
[[section(".text.crt{|.dos}.string.encrypt")]]
long a64l([[nonnull]] char const *s); /* TODO: Implement here */

@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink()', but will also function for
@@non-symlink paths, as well as always return an absolute (unambiguous) path
@@@param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
@@                  path, or NULL to automatically `malloc()'ate and return a
@@                  buffer of sufficient size.
[[cp, wunused, section(".text.crt{|.dos}.fs.property")]]
char *realpath([[nonnull]] char const *filename, char *resolved);
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
%/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
% *       but it seems to be something that GLibc isn't implementing for some reason...
% *       Because of that, I didn't really know where to put this, so I put it in the
% *       same _SOURCE-block as its `realpath()' companion. */
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
[[cp, wunused, section(".text.crt{|.dos}.fs.property")]]
[[decl_include("<bits/types.h>")]]
char *frealpath($fd_t fd, char *resolved, $size_t buflen);
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

%
%#ifdef __USE_KOS
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@@param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
@@NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
@@      representation mode. This means that if the path would have normally
@@      been printed as a unix path, it would instead be printed as a DOS path.
@@      Similarly, the reverse also applies.
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
[[cp, wunused, section(".text.crt{|.dos}.fs.property")]]
[[decl_include("<bits/types.h>")]]
char *frealpath4($fd_t fd, char *resolved, $size_t buflen, $atflag_t flags);

@@Returns the absolute filesystem path for the specified file
@@When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
@@causing the path to the symlink itself to be printed. - Otherwise, the
@@filed pointed to by the symblic link is printed.
@@NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
@@      representation mode. This means that if the path would have normally
@@      been printed as a unix path, it would instead be printed as a DOS path.
@@      Similarly, the reverse also applies.
@@NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
@@      bytes automatically allocated in the heap, ontop of which you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
@@@param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
@@@return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path
[[cp, wunused, section(".text.crt{|.dos}.fs.property")]]
[[decl_include("<bits/types.h>")]]
char *frealpathat($fd_t dirfd, [[nonnull]] char const *filename,
                  char *resolved, $size_t buflen, $atflag_t flags);
%#endif /* __USE_KOS */

%
%
%#if (defined(__USE_MISC) || \
%     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))

@@>> mktemp(3)
@@Badly designed version of `mkstemp' that won't actually create
@@the temporary file, meaning that by the time the caller tries to
@@create the file themselves, another process may have already
@@created it.
@@Also: when no temporary filename can be created, rather than
@@      returning something sensible like `NULL', this function
@@      will instead set `template_' to an empty string, and still
@@      re-return it like it would if everything had worked!
[[section(".text.crt{|.dos}.fs.utility")]]
[[guard, dos_only_export_alias("_mktemp"), export_alias("__mktemp")]]
[[requires(($has_function(open) || $has_function(stat)) && $has_function(system_mktemp))]]
[[nonnull]] char *mktemp([[nonnull]] char *template_) {
	if (system_mktemp(2, template_, 0, 0) )
		*template_ = 0;
	return template_;
}
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */


%
%
%#if (defined(__USE_MISC) || defined(__USE_DOS) || \
%     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))

%#ifndef __NO_FPU
[[wunused, dos_only_export_alias("_ecvt")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *ecvt(double val, int ndigit,
           [[nonnull]] int *__restrict decptr,
           [[nonnull]] int *__restrict sign) {
@@pp_ifndef __BUILDING_LIBC@@
	static char qcvt_buffer[32];
@@pp_endif@@
	if (ecvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}

[[wunused, dos_only_export_alias("_fcvt")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *fcvt(double val, int ndigit,
           [[nonnull]] int *__restrict decptr,
           [[nonnull]] int *__restrict sign) {
@@pp_ifndef __BUILDING_LIBC@@
	static char qcvt_buffer[32];
@@pp_endif@@
	if (fcvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
%#endif /* !__NO_FPU */

%#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */


%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
[[guard, wunused]]
[[section(".text.crt{|.dos}.application.options")]]
int getsubopt([[nonnull]] char **__restrict optionp,
              [[nonnull]] char *const *__restrict tokens,
              [[nonnull]] char **__restrict valuep) {
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


@@>> mkstemp(3), mkstemp64(3)
@@Replace the last 6 characters of `template_', which must be filled with
@@all 'X'-characters before the call (else errno=EINVAL + return -1),
@@with random characters such that the filename described by `template_'
@@will not already exists. Then, create a new file with `O_RDWR' and return
@@the file descriptor of that file.
[[section(".text.crt{|.dos}.fs.utility")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("mkstemp64")]]
[[cp, wunused, export_alias("mkstemp64"), requires_function(mkstemps)]]
[[decl_include("<bits/types.h>")]]
$fd_t mkstemp([[nonnull]] char *template_) {
	return mkstemps(template_, 0);
}

%#ifdef __USE_LARGEFILE64
[[cp, alias("mkstemp64"), nocrt, alt_variant_of(mkstemp)]]
[[wunused, requires_function(mkstemps64)]]
[[decl_include("<bits/types.h>")]]
$fd_t mkstemp64([[nonnull]] char *template_) {
	return mkstemps64(template_, 0);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN2K8
@@>> mkdtemp(3)
@@Replace the last 6 characters of `template_', which must be filled with
@@all 'X'-characters before the call (else errno=EINVAL + return -1),
@@with random characters such that the pathname described by `template_'
@@will not already exists. Then, create a new directory with `mode=0700',
@@and re-return `template_' to indicate success.
@@On error, `NULL' will be returned, and the contents of `template_' are undefined.
[[section(".text.crt{|.dos}.fs.utility")]]
[[cp, wunused, requires_function(mkdir, system_mktemp)]]
char *mkdtemp([[nonnull]] char *template_) {
	if (system_mktemp(1, template_, 0, 0) )
		template_ = NULL;
	return template_;
}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN
%[insert:extern(setkey)]

[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
int grantpt($fd_t fd);

[[section(".text.crt{|.dos}.io.tty")]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCSPTLCK))]]
int unlockpt($fd_t fd) {
	int action = 0;
	if (ioctl(fd, __TIOCSPTLCK, &action))
		return -1;
	return 0;
}

@@Returns the name of the PTY slave (Pseudo TTY slave)
@@associated with the master descriptor `fd'
[[section(".text.crt{|.dos}.io.tty")]]
[[wunused, requires_function(ptsname_r)]]
[[decl_include("<bits/types.h>")]]
char *ptsname($fd_t fd) {
	static char buf[64];
	if unlikely(ptsname_r(fd, buf, sizeof(buf)))
		return NULL;
	return buf;
}
%#endif /* __USE_XOPEN */

%
%#ifdef __USE_XOPEN2KXSI
[[section(".text.crt{|.dos}.io.tty")]]
[[cp, wunused, decl_include("<bits/types.h>")]]
$fd_t posix_openpt($oflag_t oflags);
%#endif /* __USE_XOPEN2KXSI */


%#if defined(__USE_GNU) || defined(__USE_NETBSD)
@@Returns the name of the PTY slave (Pseudo TTY slave)
@@associated with the master descriptor `fd'
[[section(".text.crt{|.dos}.io.tty"), decl_include("<bits/types.h>")]]
int ptsname_r($fd_t fd, [[nonnull]] char *buf, $size_t buflen);
%#endif /* __USE_GNU || __USE_NETBSD */

%#ifdef __USE_GNU
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtol_l"), export_alias("__strtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoll_l...)]]
[[alt_variant_of(__SIZEOF_LONG__ == 4, strto32_l)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64_l)]]
[[decl_include("<features.h>")]]
long strtol_l([[nonnull]] char const *__restrict nptr,
              char **endptr, __STDC_INT_AS_UINT_T base,
              $locale_t locale) {
	(void)locale;
	return strtol(nptr, endptr, base);
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtoul_l"), export_alias("__strtoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoull_l...)]]
[[alt_variant_of(__SIZEOF_LONG__ == 4, strtou32_l)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strtou32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strtou64_l)]]
[[decl_include("<features.h>")]]
unsigned long strtoul_l([[nonnull]] char const *__restrict nptr,
                        char **endptr, __STDC_INT_AS_UINT_T base,
                        $locale_t locale) {
	(void)locale;
	return strtoul(nptr, endptr, base);
}

%#ifdef __LONGLONG
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtoll_l"), export_alias("__strtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(CNL_strtol_l...)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strto64_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strto32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strto32_l)]]
[[decl_include("<features.h>")]]
__LONGLONG strtoll_l([[nonnull]] char const *__restrict nptr,
                     char **endptr, __STDC_INT_AS_UINT_T base,
                     $locale_t locale) {
	(void)locale;
	return strtoll(nptr, endptr, base);
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtoull_l"), export_alias("__strtoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(CNL_strtoul_l...)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, strtou64_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 4, strtou32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strtou32_l)]]
[[decl_include("<features.h>")]]
__ULONGLONG strtoull_l([[nonnull]] char const *__restrict nptr,
                       char **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale) {
	(void)locale;
	return strtoull(nptr, endptr, base);
}
%#endif /* __LONGLONG */

%#ifndef __NO_FPU
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtod_l"), export_alias("__strtod_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("strtold_l", "_strtold_l", "__strtold_l")]]
double strtod_l([[nonnull]] char const *__restrict nptr,
                char **endptr, $locale_t locale) {
	(void)locale;
	return strtod(nptr, endptr);
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtof_l"), export_alias("__strtof_l")]]
float strtof_l([[nonnull]] char const *__restrict nptr,
               char **endptr, $locale_t locale) {
	(void)locale;
	return strtof(nptr, endptr);
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[dos_only_export_alias("_strtold_l"), export_alias("__strtold_l")]]
[[alt_variant_of(__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__, strtod_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__), alias("_strtod_l", "__strtod_l")]]
__LONGDOUBLE strtold_l([[nonnull]] char const *__restrict nptr,
                       char **endptr, $locale_t locale) {
	(void)locale;
	return strtold(nptr, endptr);
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

[[wunused, section(".text.crt{|.dos}.fs.environ")]]
[[export_alias("__secure_getenv"), alias("getenv")]]
[[if($extended_include_prefix("<libc/local/environ.h>")defined(__LOCAL_environ)), bind_local_function(getenv)]]
char *secure_getenv([[nonnull]] char const *varname);

[[cp, section(".text.crt{|.dos}.io.tty")]]
int getpt();

@@Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
@@Upon error, `NULL' is returned instead
[[cp, ATTR_MALLOC, wunused, section(".text.crt{|.dos}.fs.property")]]
char *canonicalize_file_name([[nonnull]] char const *filename);

@@>> mkostemp(3), mkostemp64(3)
@@Replace the last 6 characters of `template_' (which are followed by exactly
@@`suffixlen' more characters that are left alone), which must be filled with
@@all 'X'-characters before the call (else errno=EINVAL + return -1), with
@@random characters such that the filename described by `template_' will not
@@already exists. Then, create a new file with `O_RDWR | flags' and return the file
@@descriptor of that file.
@@@param: flags: Additional flags to pass to `open(2)',
@@               but `O_ACCMODE' is always set to `O_RDWR'
[[section(".text.crt{|.dos}.fs.utility")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("mkostemp64")]]
[[wunused, export_alias("mkostemp64"), requires_function(mkostemps)]]
[[decl_include("<bits/types.h>")]]
$fd_t mkostemp([[nonnull]] char *template_, $oflag_t flags) {
	return mkostemps(template_, 0, flags);
}

[[section(".text.crt{|.dos}.fs.utility")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("mkostemps64")]]
[[wunused, export_alias("mkostemps64")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[requires_function(open, system_mktemp)]]
$fd_t mkostemps([[nonnull]] char *template_,
                __STDC_INT_AS_SIZE_T suffixlen,
                $oflag_t flags) {
	return system_mktemp(0, template_, suffixlen, flags);
}

@@Internal implementation for creating temporary files.
@@@param: what: Select what kind of temporary object to create.
@@                 `0': Create a temporary file. (The handle of that file will be returned)
@@                      Creating mode used is 0600
@@                      This mode is only recognized when `$has_function(open)'
@@                 `1': Create a temporary directory. (0 is returned on success)
@@                      Creating mode used is 0700
@@                      This mode is only recognized when `$has_function(mkdir)'
@@                      NOTE: `flags' is ignored in this mode
@@                 `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
@@                      file. Instead, return `0' on success
@@                      This mode is only recognized when `$has_function(open) || $has_function(stat)'
@@                      NOTE: `flags' is ignored in this mode
[[section(".text.crt{|.dos}.fs.utility")]]
[[cp, static, wunused]]
[[impl_include("<libc/errno.h>")]]
[[impl_include("<asm/os/oflags.h>")]]
[[impl_include("<asm/crt/stdio.h>")]] /* __TMP_MAX */
[[impl_include("<bits/os/timeval.h>")]]
[[impl_include("<bits/os/stat.h>")]]
[[impl_include("<hybrid/__overflow.h>")]]
$fd_t system_mktemp(unsigned int what, [[nonnull]] char *template_,
                    __STDC_INT_AS_SIZE_T suffixlen, $oflag_t flags) {
	/* Selection of random letters which  may appear as replacements for  XXXXXX
	 * For this  purpose,  only  use  lower-case letters,  as  well  as  digits.
	 * We  could also  use upper-case letters,  but that may  not work correctly
	 * depending on the calling process running in DOS-mode, or flags containing
	 * O_DOSPATH... */
	static char const letters[] = "abcdefghijklmnopqrstuvwxyz0123456789";
#define NUM_LETTERS 36
	char *xloc = strend(template_) - (suffixlen + 6);
	uint32_t seed, overflow;
	size_t i, attempt;
	fd_t result;
	/* Verify the validity of the input template. */
	if unlikely(xloc < template_ || memcmp(xloc, "XXXXXX", 6 * sizeof(char)) != 0) {
@@pp_ifdef EINVAL@@
		return __libc_seterrno(EINVAL);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
	/* Calculate an  initial,  random  seed.
	 * For this purpose, try to make use of:
	 *   - gettimeofday()
	 *   - gettid() or getpid()
	 *   - rand() */
	attempt = 0;
again:
	{
@@pp_if $has_function(gettimeofday64) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__@@
		struct timeval64 tv;
		if (gettimeofday64(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.@tv_sec@) ^
			       (uint32_t)(tv.@tv_sec@ >> 32) ^
			       (uint32_t)(tv.@tv_usec@ << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
@@pp_elif $has_function(gettimeofday)@@
		struct timeval tv;
		if (gettimeofday(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.@tv_sec@) ^
@@pp_if __SIZEOF_TIME_T__ > 4@@
			       (uint32_t)(tv.@tv_sec@ >> 32) ^
@@pp_endif@@
			       (uint32_t)(tv.@tv_usec@ << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
@@pp_endif@@
		{
			uint32_t sum;
@@pp_ifdef __RAND_MAX@@
#define LIBC_RAND_MAX __RAND_MAX
@@pp_else@@
#define LIBC_RAND_MAX 0x7fff
@@pp_endif@@
			seed = sum = 0;
			/* Generate at least 32 bits of random data. */
			do {
				seed *= LIBC_RAND_MAX;
				seed += (uint32_t)rand();
			} while (!__hybrid_overflow_uadd(sum, LIBC_RAND_MAX, &sum));
#undef LIBC_RAND_MAX
		}
	}
@@pp_if $has_function(gettid)@@
	seed ^= gettid();
@@pp_elif $has_function(getpid)@@
	seed ^= getpid();
@@pp_endif@@

	/* Using the seed, generate some initial random data.
	 * We've generated 32 bits of entropy above, and with
	 * a total of 6 characters to generate from a pool of
	 * 36 letters each, this 5.333(rep) bits per digit. */
	overflow = seed >> 30;
	for (i = 0; i < 6; ++i) {
		unsigned int digit;
	    digit = seed & 0x1f;                      /* digit in 0-31 */
		digit += overflow & ((1 << (i & 3)) - 1); /* Add a random addend between 0-7 */
		/* Right now, digit in 0-38. But because we're using 2 addend, `0' is less
		 * likely than the other digits. As such, subtract a bit if we're not at 0
		 * already. */
		if (digit)
			--digit;
		if (digit)
			--digit;
		/* Now, digit in 0-36, but 36 itself would still be invalid. */
		if (digit > 35)
			digit = 35;
		/* All right! we've got the digit. */
		xloc[i] = letters[digit];
		seed >>= 5;
	}

	/* Try to create/test the file/directory. */
	(void)flags;
	switch (what) {

@@pp_if $has_function(open)@@
	case 0: {
@@pp_ifdef O_RDWR@@
@@pp_ifdef O_ACCMODE@@
		flags &= ~O_ACCMODE;
@@pp_endif@@
		flags |= O_RDWR;
@@pp_endif@@
@@pp_ifdef O_CREAT@@
		flags |= O_CREAT;
@@pp_endif@@
@@pp_ifdef O_EXCL@@
		flags |= O_EXCL;
@@pp_endif@@
		result = open(template_, flags, 0600);
	}	break;
@@pp_endif@@

@@pp_if $has_function(mkdir)@@
	case 1:
		result = mkdir(template_, 0700);
		break;
@@pp_endif@@

@@pp_if $has_function(open) || $has_function(stat)@@
	case 2: {
@@pp_if $has_function(stat)@@
		struct @stat@ st;
		result = stat(template_, &st);
@@pp_else@@
		result = open(template_,
@@pp_ifdef O_RDONLY@@
		              O_RDONLY
@@pp_elif defined(O_RDWR)@@
		              O_RDWR
@@pp_elif defined(O_WRONLY)@@
		              O_WRONLY
@@pp_else@@
		              0
@@pp_endif@@
		              ,
		              0600);
@@pp_endif@@
		if (result < 0) {
			/* File doesn't already exist. */
			result = 0;
		} else {
			/* File does already exist. */
@@pp_if !$has_function(stat) && $has_function(close)@@
			close(result);
@@pp_endif@@
@@pp_ifdef EEXIST@@
			result = __libc_seterrno(EEXIST);
@@pp_else@@
			result = __libc_seterrno(1);
@@pp_endif@@
#define NEED_do_try_again
			goto do_try_again;
		}
	}	break;
@@pp_endif@@

	default: __builtin_unreachable();
	}
	if (result == -1) {
		/* Only re-attempt if the error was that the file already existed. */
@@pp_if defined(__libc_geterrno) && defined(EEXIST)@@
		if (__libc_geterrno() == EEXIST)
@@pp_endif@@
		{
@@pp_ifdef NEED_do_try_again@@
#undef NEED_do_try_again
do_try_again:
@@pp_endif@@
			/* Limit the max # of attempts */
@@pp_ifdef __TMP_MAX@@
			if (attempt < __TMP_MAX)
@@pp_else@@
			if (attempt < 238328)
@@pp_endif@@
			{
				++attempt;
				goto again;
			}
		}
	}
	return result;
}


%#ifdef __USE_LARGEFILE64
[[alias("mkostemp64"), nocrt, largefile64_variant_of(mkostemp)]]
[[wunused, requires_function(mkostemps64), decl_include("<bits/types.h>")]]
$fd_t mkostemp64([[nonnull]] char *template_, $oflag_t flags) {
	return mkostemps64(template_, 0, flags);
}

[[wunused, alias("mkostemps64"), nocrt, largefile64_variant_of(mkostemps)]]
[[requires_function(mkostemps), decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/oflags.h>")]]
$fd_t mkostemps64([[nonnull]] char *template_,
                  __STDC_INT_AS_SIZE_T suffixlen,
                  $oflag_t flags) {
	return mkostemps(template_, suffixlen, flags | __O_LARGEFILE);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */

%
%#if defined(__USE_KOS) || defined(__USE_MISC) || defined(__USE_OPENBSD)
%[insert:extern(reallocarray)]
%#endif /* __USE_KOS || __USE_MISC || __USE_OPENBSD */

%
%#ifdef __USE_KOS
%[insert:extern(recalloc)]
%[insert:extern(reallocv)]
%[insert:extern(recallocv)]

%
%
%#ifdef __USE_STRING_OVERLOADS
%#ifndef __MALLOC_OVERLOADS_DEFINED
%#define __MALLOC_OVERLOADS_DEFINED 1
%{
#ifdef __malloc_defined
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mallocv))(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
	__SIZE_TYPE__ __total_size;
	if (__hybrid_overflow_umul(__elem_count, __elem_size, &__total_size))
		__total_size = (__SIZE_TYPE__)-1; /* Force down-stream failure */
	return (malloc)(__total_size);
}
__NAMESPACE_LOCAL_END
#endif /* __malloc_defined */
}
%#ifdef __cplusplus
%extern "C++" {
%{
#ifdef __malloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL malloc)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)(__elem_count, __elem_size); }
#endif /* __malloc_defined */
#ifdef __calloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__NOTHROW_NCX(__LIBCCALL calloc)(__SIZE_TYPE__ __num_bytes) { return (calloc)(1, __num_bytes); }
#endif /* __calloc_defined */
}
%} /* extern "C++" */
%[insert:function(realloc = reallocarray, externLinkageOverride: "C++")]
%[insert:function(recalloc = recallocv, externLinkageOverride: "C++")]
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
#ifdef __malloc_defined
#define __PRIVATE_malloc_1 (malloc)
#define __PRIVATE_malloc_2 __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)
#undef malloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define malloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define malloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (args))(args)
#endif /* ... */
#endif /* __malloc_defined */
#ifdef __calloc_defined
#define __PRIVATE_calloc_1(num_bytes) (calloc)(1, num_bytes)
#define __PRIVATE_calloc_2            (calloc)
#undef calloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define calloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define calloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (args))(args)
#endif /* ... */
#endif /* __calloc_defined */
#if defined(__realloc_defined) && defined(__reallocarray_defined)
#define __PRIVATE_realloc_2 (realloc)
#define __PRIVATE_realloc_3 (reallocarray)
#undef realloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define realloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define realloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (args))(args)
#endif /* ... */
#endif /* __realloc_defined && __reallocarray_defined */
#if defined(__recalloc_defined) && defined(__recallocv_defined)
#define __PRIVATE_recalloc_2 (recalloc)
#define __PRIVATE_recalloc_3 (recallocv)
#undef recalloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define recalloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define recalloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (args))(args)
#endif /* ... */
#endif /* __recalloc_defined && __recallocv_defined */
}
%#endif /* ... */
%#endif /* !__MALLOC_OVERLOADS_DEFINED */
%#endif /* __USE_STRING_OVERLOADS */

@@>> shexec(3)
@@Execute command with the system interpreter (such as: `/bin/sh -c $command')
@@This function is used to implement `system(3)' and `popen(3)', and may be
@@used to invoke the system interpreter.
@@This function only returns on failure (similar to exec(2)), and will never
@@return on success (since in that case, the calling program will have been
@@replaced by the system shell)
[[cp, guard, section(".text.crt{|.dos}.fs.exec.system")]]
[[requires_function(execl)]]
int shexec([[nullable]] char const *command) {
	static char const arg_sh[] = "sh";
	static char const arg__c[] = "-c";
@@pp_ifdef __KOS__@@
	/* By default, KOS uses busybox, so try to invoke that first. */
	execl("/bin/busybox", arg_sh, arg__c, command, (char *)NULL);
	execl("/bin/sh", arg_sh, arg__c, command, (char *)NULL);
	execl("/bin/bash", arg_sh, arg__c, command, (char *)NULL);
@@pp_else@@
	execl("/bin/sh", arg_sh, arg__c, command, (char *)NULL);
	execl("/bin/bash", arg_sh, arg__c, command, (char *)NULL);
	execl("/bin/busybox", arg_sh, arg__c, command, (char *)NULL);
@@pp_endif@@
	return -1;
}
%#endif /* __USE_KOS */

%
%#ifdef __USE_BSD
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
[[userimpl, requires_function(realloc)]]
[[impl_include("<asm/crt/malloc.h>"), guard]]
void *reallocf(void *mallptr, $size_t num_bytes) {
	void *result;
	result = realloc(mallptr, num_bytes);
@@pp_if $has_function(free)@@
@@pp_ifdef __REALLOC_ZERO_IS_NONNULL@@
	if unlikely(!result)
@@pp_else@@
	/* Must check that num_bytes != 0 because if it isn't
	 * (iow: num_bytes == 0), then realloc(mallptr, 0) may
	 * act  the same as  `free(mallptr)'. If that happens,
	 * then we mustn't double-free `mallptr'.
	 * Note that realloc(<non-NULL>, 0) can't possibly fail
	 * for  lack  of memory  if `__REALLOC_ZERO_IS_NONNULL'
	 * was guessed incorrectly, so this may of doing it  is
	 * entirely safe! */
	if unlikely(!result && num_bytes != 0)
@@pp_endif@@
	{
		free(mallptr);
	}
@@pp_endif@@
	return result;
}

@@>> recallocarray(3)
@@Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
@@when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
@@is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block
[[guard, section(".text.crt{|.dos}.heap.rare_helpers")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((3, 4))]]
[[userimpl, requires_function(recallocv, calloc, malloc_usable_size)]]
void *recallocarray(void *mallptr, $size_t old_elem_count,
                    $size_t new_elem_count, $size_t elem_size) {
	if (mallptr != NULL && old_elem_count != 0) {
		void *result;
		size_t oldusable, newneeded;
		oldusable = malloc_usable_size(mallptr);
		newneeded = new_elem_count * elem_size;
		if (oldusable >= newneeded) {
			if (old_elem_count > new_elem_count) {
				size_t zero_bytes;
				zero_bytes = (old_elem_count - new_elem_count) * elem_size;
				explicit_bzero((byte_t *)mallptr + newneeded, zero_bytes);
			}
			return mallptr;
		}
		/* Allocate a new block so we can ensure that  an
		 * existing block gets freezero()'ed in all cases */
		result = calloc(new_elem_count, elem_size);
		if (result) {
			if (oldusable > newneeded)
				oldusable = newneeded;
			memcpy(result, mallptr, oldusable);
			freezero(mallptr, old_elem_count * elem_size);
		}
		return result;
	}
	return recallocv(mallptr, new_elem_count, elem_size);
}

@@Same as `free(mallptr)', but also ensure that the memory region
@@described by `mallptr...+=num_bytes' is explicitly freed to zero, or
@@immediately returned to the OS, rather than being left in cache
@@while still containing its previous contents.
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
[[userimpl, requires_function(free), guard]]
void freezero(void *mallptr, $size_t num_bytes) {
	if likely(mallptr) {
		explicit_bzero(mallptr, num_bytes);
		free(mallptr);
	}
}

%#endif /* __USE_BSD */

%
%#ifdef __USE_SOLARIS
%[default:section(".text.crt{|.dos}.solaris")]

%#ifndef __uid_t_defined
%#define __uid_t_defined 1
%typedef __uid_t uid_t; /* User ID */
%#endif /* !__uid_t_defined */

%[insert:extern(closefrom)]
%[insert:extern(dup2)]
%[insert:extern(getcwd)]
%[insert:extern(getlogin)]
%[insert:extern(getpass)]
%[insert:extern(getpw)]
%[insert:extern(isatty)]
%[insert:extern(memalign)]
%[insert:extern(ttyname)]

@@Returns the absolute filename of the main executable (s.a. `program_invocation_name')
[[wunused, const]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name))]]
[[impl_include("<libc/local/program_invocation_name.h>")]]
char const *getexecname() {
	return __LOCAL_program_invocation_name;
}

%{
#ifndef ____fdwalk_func_t_defined
#define ____fdwalk_func_t_defined 1
typedef int (__LIBKCALL *__fdwalk_func_t)(void *__cookie, __fd_t __fd);
#endif /* !____fdwalk_func_t_defined */
}
%[define_replacement(__fdwalk_func_t = __fdwalk_func_t)]
%[define_type_class(__fdwalk_func_t = "TP")]

%[define(DEFINE_FDWALK_FUNC_T =
@@pp_ifndef ____fdwalk_func_t_defined@@
#define ____fdwalk_func_t_defined 1
typedef int (__LIBKCALL *__fdwalk_func_t)(void *__cookie, __fd_t __fd);
@@pp_endif@@
)]


@@Enumerate all open file descriptors by invoking `(*func)(cookie, <fd>)' for each of them
@@If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
@@and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
@@invocations return 0, `fdwalk()' will also return 0.
[[decl_prefix(DEFINE_FDWALK_FUNC_T)]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(fcntl) && defined(__F_NEXT))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>")]]
int fdwalk([[nonnull]] __fdwalk_func_t func, void *cookie) {
	/* TODO: Implementation alternative using `opendir("/proc/self/fd")' */
	int result = 0;
@@pp_ifdef __libc_geterrno@@
	errno_t saved_err;
@@pp_endif@@
	fd_t fd = 0;
	for (;;) {
@@pp_ifdef __libc_geterrno@@
		saved_err = __libc_geterrno();
@@pp_endif@@
		/* fcntl(F_NEXT) returns the next valid  (i.e.
		 * currently open) fd that is >= the given fd. */
		fd = fcntl(fd, __F_NEXT);
		if (fd < 0) {
@@pp_ifdef __libc_geterrno@@
			__libc_seterrno(saved_err);
@@pp_endif@@
			break;
		}
		result = (*func)(cookie, fd);
		if (result != 0)
			break;
		++fd;
	}
	return result;
}

%[insert:function(getpassphrase = getpass)]

//TODO: char *lltostr(long long, char *);
//TODO: char *ulltostr(unsigned long long, char *);
%#endif /* __USE_SOLARIS */


%
%#if defined(__USE_OPENBSD) && defined(__LONGLONG)
%[default:section(".text.crt{|.dos}.bsd")]

@@>> strtonum(3)
@@Similar to `strtoi()' with `base=10', but return human-
@@readable error messages in `*p_errstr' on error (alongside
@@`return==0') (or `NULL' on success).
@@The following messages are defined:
@@  - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
@@  - "too small": Numeric value is too small (`ERANGE' && less than `lo')
@@  - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
@@@return: 0 : [*p_errstr != NULL] Error
@@@return: 0 : [*p_errstr == NULL] Success
@@@return: * : [*p_errstr == NULL] Success
[[guard, wunused, impl_include("<bits/types.h>", "<asm/os/errno.h>")]]
__LONGLONG strtonum([[nonnull]] char const *nptr,
                    __LONGLONG lo, __LONGLONG hi,
                    [[nonnull]] char const **p_errstr) {
	errno_t error;
	__LONGLONG result;
	result = (__LONGLONG)strtoi(nptr, NULL, 10, lo, hi, &error);
	if (error == 0) {
		if (p_errstr)
			*p_errstr = NULL;
		return result;
	}
	if (p_errstr) {
		*p_errstr = "invalid";
@@pp_ifdef ERANGE@@
		if (error == ERANGE) {
			*p_errstr = "too large";
			if (result == lo)
				*p_errstr = "too small";
		}
@@pp_endif@@
	}
	return 0;
}
%#endif /* __USE_OPENBSD && __LONGLONG */


%
%#ifdef __USE_NETBSD
%[default:section(".text.crt{|.dos}.bsd")]

[[guard, throws, decl_prefix(DEFINE_COMPAR_FN_T), decl_include("<hybrid/typecore.h>")]]
int heapsort([[nonnull]] void *pbase,
             $size_t item_count, $size_t item_size,
             [[nonnull]] __compar_fn_t cmp) {
	/* TODO: Actually do heap-sort! */
	qsort(pbase, item_count, item_size, cmp);
	return 0;
}

[[guard, throws, decl_prefix(DEFINE_COMPAR_FN_T), decl_include("<hybrid/typecore.h>")]]
int mergesort([[nonnull]] void *pbase,
              $size_t item_count, $size_t item_size,
              [[nonnull]] __compar_fn_t cmp) {
	/* TODO: Actually do merge-sort! */
	qsort(pbase, item_count, item_size, cmp);
	return 0;
}


[[guard]]
int radixsort([[nonnull]] unsigned char const **base, int item_count,
              [[nullable]] unsigned char const *table, unsigned endbyte);
/* TODO: `radixsort()' can be implemented via magic! */

[[guard]]
int sradixsort([[nonnull]] unsigned char const **base, int item_count,
               [[nullable]] unsigned char const *table, unsigned endbyte);
/* TODO: `sradixsort()' can be implemented via magic! */

//TODO:uint32_t arc4random(void);
//TODO:void arc4random_stir(void);
//TODO:void arc4random_buf(void *, size_t);
//TODO:uint32_t arc4random_uniform(uint32_t);
//TODO:void arc4random_addrandom(unsigned char *, int);

//TODO:char *cgetcap(char *, char const *, int);
//TODO:int cgetclose(void);
//TODO:int cgetent(char **, char const *const *, char const *);
//TODO:int cgetfirst(char **, char const *const *);
//TODO:int cgetmatch(char const *, char const *);
//TODO:int cgetnext(char **, char const *const *);
//TODO:int cgetnum(char *, char const *, long *);
//TODO:int cgetset(char const *);
//TODO:int cgetstr(char *, char const *, char **);
//TODO:int cgetustr(char *, char const *, char **);
//TODO:void csetexpandtc(int);

[[guard, wunused, decl_include("<hybrid/typecore.h>")]]
char *getbsize([[nonnull]] int *headerlenp,
               [[nonnull]] __LONGPTR_TYPE__ *blocksizep);
/* TODO: `getbsize()' can be implemented via magic! */


@@>> devname(3), devname_r(3)
[[const, alias("__devname50"), requires_function(devname_r)]]
char *devname(dev_t dev, mode_t type) {
	static char buf[64];
	return devname_r(dev, type, buf, sizeof(buf)) ? NULL : buf;
}

[[doc_alias("devname")]]
int devname_r(dev_t dev, mode_t type, [[outp(len)]] char *buf, $size_t len);


//TODO:#define HN_DECIMAL      0x01
//TODO:#define HN_NOSPACE      0x02
//TODO:#define HN_B            0x04
//TODO:#define HN_DIVISOR_1000 0x08
//TODO:#define HN_GETSCALE     0x10
//TODO:#define HN_AUTOSCALE    0x20
//TODO:int humanize_number(char *, $size_t, int64_t, char const *, int, int);
//TODO:int dehumanize_number(char const *, int64_t *);

//TODO:ssize_t hmac(char const *, const void *, $size_t, const void *, $size_t, void *, $size_t);
//TODO:devmajor_t getdevmajor(char const *, mode_t);
//TODO:int getenv_r(char const *, char *, $size_t);
//TODO:void mi_vector_hash(const void *__restrict, $size_t, uint32_t, uint32_t[3]);

[[guard, ATTR_LIBC_PRINTF(1, 2)]]
void setproctitle(char const *format, ...);

@@>> getprogname(3), setprogname(3)
[[guard, wunused, const]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_short_name))]]
char const *getprogname(void) {
	return __LOCAL_program_invocation_short_name;
}

[[guard, doc_alias("getprogname")]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_short_name_p))]]
void setprogname(char const *name) {
	__LOCAL_program_invocation_short_name_p = (char *)name;
}

//TODO:int l64a_r(long, char *, int);
//TODO:$size_t shquote(char const *, char *, $size_t);
//TODO:$size_t shquotev(int, char *const *, char *, $size_t);

%[insert:extern(daemon)]
%[insert:function(reallocarr = reallocarray)]
%#ifdef __LONGLONG
@@>> strsuftoll(3)
@@Same as `strsuftollx(3)', but if an error happens, make
@@use of `errx(3)' to terminate the program, rather than
@@return to the caller.
[[wunused, requires_function(errx)]]
[[impl_include("<asm/os/stdlib.h>")]]
__LONGLONG strsuftoll([[nonnull]] char const *desc,
                      [[nonnull]] char const *val,
                      __LONGLONG lo, __LONGLONG hi) {
	__LONGLONG result;
	char error_message[128];
	result = strsuftollx(desc, val, lo, hi,
	                     error_message,
	                     sizeof(error_message));
	if (result == 0 && *error_message) {
@@pp_ifdef __EXIT_FAILURE@@
		errx(__EXIT_FAILURE, "%s", error_message);
@@pp_else@@
		errx(1, "%s", error_message);
@@pp_endif@@
	}
	return result;
}

@@>> strsuftollx(3)
[[wunused]]
__LONGLONG strsuftollx([[nonnull]] char const *desc,
                       [[nonnull]] char const *val,
                       __LONGLONG lo, __LONGLONG hi,
                       char *errbuf, $size_t errbuflen) {
	/* TODO */
	(void)desc;
	(void)lo;
	(void)hi;
	if (errbuflen)
		*errbuf = 0;
	return strtoll(val, NULL, 10);
}


%typedef struct __lldiv_struct qdiv_t;
%[insert:function(qabs = llabs)]
%[insert:function(qdiv = lldiv)]
%[insert:function(strtoq_l = strtoll_l)]
%[insert:function(strtouq_l = strtoull_l)]
%#endif /* __LONGLONG */
%#endif /* __USE_NETBSD */


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
#ifndef __cplusplus
#define min(a, b) __hybrid_min(a, b)
#define max(a, b) __hybrid_max(a, b)
#endif /* !__cplusplus */

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
typedef int (__LIBDCALL *_onexit_t)(void);
#endif  /* _ONEXIT_T_DEFINED */
#ifndef onexit_t
#define onexit_t _onexit_t
#endif /* !onexit_t */
}

%
%#ifndef _CRT_ERRNO_DEFINED
%#define _CRT_ERRNO_DEFINED 1
/* NOTE: Cygwin calls it `__errno()' and DOS calls it `_errno()' */
%#ifndef errno
%[insert:extern(__errno_location)]
%#ifdef ____errno_location_defined
%#define errno (*__errno_location())
%#endif /* ____errno_location_defined */
%#endif /* !errno */

[[section(".text.crt.dos.errno_access")]]
[[crt_dos_variant, decl_include("<bits/types.h>")]]
errno_t _get_errno(errno_t *perr);

[[section(".text.crt.dos.errno_access")]]
[[crt_dos_variant, decl_include("<bits/types.h>")]]
errno_t _set_errno(errno_t err);
%#endif /* !_CRT_ERRNO_DEFINED */



[[guard, const, section(".text.crt.dos.errno")]]
$u32 *__doserrno();

[[section(".text.crt.dos.errno")]]
[[crt_dos_variant, decl_include("<bits/types.h>")]]
errno_t _get_doserrno($u32 *perr);

[[section(".text.crt.dos.errno")]]
[[decl_include("<bits/types.h>")]]
errno_t _set_doserrno($u32 err);

%{
#ifdef ____doserrno_defined
#define _doserrno (*__doserrno())
#endif /* ____doserrno_defined */
}


%
%{
#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("environ");
#define _environ _environ
#elif defined(__CRT_HAVE_environ)
#ifndef __environ_defined
#define __environ_defined 1
#undef environ
__LIBC char **environ;
#endif /* !__environ_defined */
#define _environ environ
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#define _environ _environ
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("__environ");
#define _environ _environ
#elif defined(__CRT_HAVE___environ)
#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
__LIBC char **__environ;
#endif /* !____environ_defined */
#define _environ __environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define _environ (*__p__environ())
#else /* ... */
#undef ___environ_defined
#endif /* !... */
#endif /* !___environ_defined */

}


%{
#ifndef __argc
#ifdef __CRT_HAVE___argc
__LIBC int __argc;
#define __argc __argc
#else /* __CRT_HAVE___argc */
}
[[guard, wunused, const]]
[[nonnull, section(".text.crt.dos.application.init")]]
int *__p___argc();
%{
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !__CRT_HAVE___argc */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__LIBC char **__argv;
#else /* __CRT_HAVE___argv */
}
[[guard, wunused, const]]
[[nonnull, section(".text.crt.dos.application.init")]]
char ***__p___argv();
%{
#ifdef ____p___argv_defined
#define __argv (*__p___argv())
#endif /* ____p___argv_defined */
#endif /* !__CRT_HAVE___argv */
#endif /* !__argv */

#ifndef __wargv
#ifdef __CRT_HAVE___wargv
__LIBC wchar_t **__wargv;
#define __wargv __wargv
#else /* __CRT_HAVE___wargv */
}
[[guard, wunused, const, wchar]]
[[nonnull, section(".text.crt.dos.wchar.application.init")]]
wchar_t ***__p___wargv();
%{
#ifdef ____p___wargv_defined
#define __wargv (*__p___wargv())
#endif /* ____p___wargv_defined */
#endif /* !__CRT_HAVE___wargv */
#endif /* !__wargv */

#ifndef _wenviron
#ifdef __CRT_HAVE__wenviron
__LIBC wchar_t **_wenviron;
#define _wenviron _wenviron
#else /* __CRT_HAVE__wenviron */
}
[[guard, wunused, const, wchar]]
[[nonnull, section(".text.crt.dos.wchar.fs.environ")]]
wchar_t ***__p__wenviron();
%{
#ifdef ____p__wenviron_defined
#define _wenviron (*__p__wenviron())
#endif /* ____p__wenviron_defined */
#endif /* !__CRT_HAVE__wenviron */
#endif /* !_wenviron */

#ifndef _wpgmptr
#ifdef __CRT_HAVE__wpgmptr
__LIBC wchar_t *_wpgmptr;
#define _wpgmptr _wpgmptr
#else /* __CRT_HAVE__wpgmptr */
}
[[guard, wunused, const, wchar]]
[[nonnull, section(".text.crt.dos.wchar.application.init")]]
wchar_t **__p__wpgmptr();
%{
#ifdef ____p__wpgmptr_defined
#define _wpgmptr (*__p__wpgmptr())
#endif /* ____p__wpgmptr_defined */
#endif /* !__CRT_HAVE__wpgmptr */
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
[[guard, wunused, const]]
[[export_alias("__p_program_invocation_name")]]
[[impl_include("<libc/local/program_invocation_name.h>")]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name_p))]]
[[nonnull, section(".text.crt.dos.application.init")]]
char **__p__pgmptr() {
	return &__LOCAL_program_invocation_name_p;
}

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
#else /* __CRT_HAVE___initenv */
}
@@Access to the initial environment block
[[guard, wunused, const]]
[[section(".text.crt.dos.fs.environ")]]
__p___initenv() -> [[nonnull]] char ***;
%{
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !__CRT_HAVE___initenv */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__LIBC wchar_t **__winitenv;
#else /* __CRT_HAVE___winitenv */
}
@@Access to the initial environment block
[[guard, wunused, const, wchar]]
[[section(".text.crt.dos.wchar.fs.environ")]]
__p___winitenv() -> [[nonnull]] wchar_t ***;
%{
#ifdef ____p___winitenv_defined
#define __winitenv (*__p___winitenv())
#endif /* ____p___winitenv_defined */
#endif /* !__CRT_HAVE___winitenv */
#endif /* !__winitenv */
}
%#endif /* __USE_KOS */

%
%#ifndef _countof
%#define _countof(a) __COMPILER_LENOF(a)
%#endif /* !_countof */


%
%{
#ifndef ___purecall_handler_defined
#define ___purecall_handler_defined 1
typedef void (__LIBDCALL *_purecall_handler)(void);
#endif /* !___purecall_handler_defined */
}

%[define(DEFINE_PURECALL_HANDLER =
#ifndef ___purecall_handler_defined
#define ___purecall_handler_defined 1
typedef void (__LIBDCALL *_purecall_handler)(void);
#endif /* !___purecall_handler_defined */
)]
%[define_replacement(_purecall_handler = _purecall_handler)]
%[define_type_class(_purecall_handler = "TP")]


[[section(".text.crt.dos.errno")]]
[[decl_prefix(DEFINE_PURECALL_HANDLER)]]
_purecall_handler _set_purecall_handler(_purecall_handler __handler);

[[section(".text.crt.dos.errno")]]
[[decl_prefix(DEFINE_PURECALL_HANDLER)]]
_purecall_handler _get_purecall_handler();

%
%{
#ifndef ___invalid_parameter_handler_defined
#define ___invalid_parameter_handler_defined 1
typedef void (__LIBDCALL *_invalid_parameter_handler)(wchar_t const *, wchar_t const *, wchar_t const *, unsigned int, __UINTPTR_TYPE__);
#endif /* !___invalid_parameter_handler_defined */
}

%[define(DEFINE_INVALID_PARAMETER_HANDLER =
#ifndef ___invalid_parameter_handler_defined
#define ___invalid_parameter_handler_defined 1
typedef void (__LIBDCALL *_invalid_parameter_handler)(wchar_t const *, wchar_t const *, wchar_t const *, unsigned int, __UINTPTR_TYPE__);
#endif /* !___invalid_parameter_handler_defined */
)]
%[define_replacement(_invalid_parameter_handler = _invalid_parameter_handler)]
%[define_type_class(_invalid_parameter_handler = "TP")]

[[section(".text.crt.dos.errno")]]
[[decl_prefix(DEFINE_INVALID_PARAMETER_HANDLER)]]
_invalid_parameter_handler _set_invalid_parameter_handler(_invalid_parameter_handler __handler);

[[section(".text.crt.dos.errno")]]
[[decl_prefix(DEFINE_INVALID_PARAMETER_HANDLER)]]
_invalid_parameter_handler _get_invalid_parameter_handler();


[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.application.init")]]
[[impl_include("<libc/local/program_invocation_name.h>")]]
[[requires_include("<libc/local/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name))]]
errno_t _get_pgmptr(char **pvalue) {
	*pvalue = __LOCAL_program_invocation_name;
	return EOK;
}

[[decl_include("<bits/types.h>")]]
[[wchar, section(".text.crt.dos.wchar.application.init")]]
[[requires_function(__p__wpgmptr)]]
errno_t _get_wpgmptr(wchar_t **pvalue) {
	*pvalue = *__p__wpgmptr();
	return EOK;
}

%#ifdef __CRT_HAVE__fmode
%__LIBC int _fmode;
%#else /* ... */
[[guard, wunused, const]]
[[nonnull, section(".text.crt.dos.FILE.utility")]]
int *__p__fmode();
%#ifdef ____p__fmode_defined
%#define _fmode (*__p__fmode())
%#endif /* ____p__fmode_defined */
%#endif /* !... */

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.FILE.utility")]]
errno_t _set_fmode(int mode);

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.FILE.utility")]]
errno_t _get_fmode(int *pmode);

[[section(".text.crt.dos.errno")]]
unsigned int _set_abort_behavior(unsigned int flags, unsigned int mask);

%#ifdef __INT64_TYPE__
%#if defined(_MSC_VER) && defined(__LIBCCALL_IS_LIBDCALL)
%extern __ATTR_CONST __INT64_TYPE__ (__LIBDCALL _abs64)(__INT64_TYPE__ __x);
%#pragma intrinsic(_abs64)
%#else /* _MSC_VER && __LIBCCALL_IS_LIBDCALL */
[[const, wunused, nothrow, section(".text.crt.dos.math.utility")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       crt_intern_kos_alias("libc_abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), crt_intern_kos_alias("libc_llabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       alias("abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       bind_local_function(abs)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(llabs)]]
__INT64_TYPE__ _abs64(__INT64_TYPE__ x) {
	return x < 0 ? -x : x;
}
%#endif /* !_MSC_VER || !__LIBCCALL_IS_LIBDCALL */
%#endif /* __INT64_TYPE__ */


%#ifndef __NO_FPU
[[wunused, pure, section(".text.crt.dos.unicode.locale.convert")]]
double _atof_l([[nonnull]] char const *__restrict nptr, $locale_t locale) {
	return strtod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

[[wunused, pure, section(".text.crt.dos.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("_atol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("_atoll_l")]]
int _atoi_l([[nonnull]] char const *__restrict nptr, $locale_t locale) {
	return (int)strtol_l(nptr, NULL, 10, locale);
}
[[wunused, pure, section(".text.crt.dos.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _atoi_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("_atoll_l")]]
long int _atol_l([[nonnull]] char const *__restrict nptr, $locale_t locale) {
	return strtol_l(nptr, NULL, 10, locale);
}
%#ifdef __LONGLONG
[[wunused, pure, section(".text.crt.dos.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _atol_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _atoi_l)]]
__LONGLONG _atoll_l([[nonnull]] char const *__restrict nptr, $locale_t locale) {
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

[[section(".text.crt.dos.math.utility")]]
[[const, wunused, impl_include("<hybrid/__byteswap.h>")]]
$u16 _byteswap_ushort($u16 val) {
	return __hybrid_bswap16(val);
}

[[section(".text.crt.dos.math.utility")]]
[[const, wunused, impl_include("<hybrid/__byteswap.h>")]]
$u32 _byteswap_ulong($u32 val) {
	return __hybrid_bswap32(val);
}

%#ifdef __UINT64_TYPE__
[[section(".text.crt.dos.math.utility")]]
[[const, wunused, impl_include("<hybrid/__byteswap.h>")]]
$u64 _byteswap_uint64($u64 val) {
	return __hybrid_bswap64(val);
}
%#endif /* __UINT64_TYPE__ */

%{
#define _byteswap_ushort(x) __hybrid_bswap16(x)
#define _byteswap_ulong(x)  __hybrid_bswap32(x)
#ifdef __UINT64_TYPE__
#define _byteswap_uint64(x) __hybrid_bswap64(x)
#endif /* __UINT64_TYPE__ */
}
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
typedef int (__LIBDCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
}


%[define(DEFINE_DOS_COMPAR_D_FN_T =
@@pp_ifndef __dos_compar_d_fn_t_defined@@
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBDCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
@@pp_endif@@
)]
%[define_replacement(__dos_compar_d_fn_t = __dos_compar_d_fn_t)]
%[define_type_class(__dos_compar_d_fn_t = "TP")]

%[define(DEFINE_INVOKE_COMPARE_HELPER_S =
@@pp_ifndef ____invoke_compare_helper_s_defined@@
#define ____invoke_compare_helper_s_defined 1
@@push_namespace(local)@@
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBKCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
@@pop_namespace@@
@@pp_endif@@
)]

[[throws, wunused]]
[[section(".text.crt.dos.utility")]]
[[decl_prefix(DEFINE_DOS_COMPAR_D_FN_T)]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER_S)]]
void *bsearch_s([[nonnull]] void const *key,
                [[nonnull]] void const *base, $size_t elem_count, $size_t elem_size,
                [[nonnull]] __dos_compar_d_fn_t compar, void *arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return (void *)bsearch_r(key, base, elem_count, elem_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	                         &data);
}

[[throws]]
[[section(".text.crt.dos.utility")]]
[[decl_prefix(DEFINE_DOS_COMPAR_D_FN_T)]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER_S)]]
void qsort_s([[nonnull]] void *base, $size_t elem_count, $size_t elem_size,
             [[nonnull]] __dos_compar_d_fn_t compar, void *arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return qsort_r(base, elem_count, elem_size,
	               &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	               &data);
}
%#endif  /* _CRT_ALGO_DEFINED */
%

[[section(".text.crt.dos.utility")]]
[[decl_include("<bits/types.h>")]]
errno_t getenv_s([[nonnull]] $size_t *psize,
                 [[nonnull]] char *buf, rsize_t buflen,
                 [[nonnull]] char const *varname);

[[section(".text.crt.dos.utility")]]
[[decl_include("<bits/types.h>")]]
errno_t _dupenv_s([[nonnull]] char **__restrict pbuf,
                  [[nonnull]] $size_t *pbuflen,
                  [[nonnull]] char const *varname);
%#endif /* __USE_DOS_SLIB */

%[insert:function(_itoa = itoa)]
%[insert:function(_ltoa = ltoa)]
%[insert:function(_ultoa = ultoa)]


[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_ltoa_s")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_i64toa_s")]]
[[section(".text.crt.dos.unicode.static.convert")]]
errno_t _itoa_s(int val, [[nonnull]] char *buf, $size_t buflen, int radix) {
	char *p;
	int temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
@@pp_ifdef ERANGE@@
			return ERANGE;
@@pp_else@@
			return 1;
@@pp_endif@@
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf)) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
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

[[decl_include("<bits/types.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, "_itoa_s")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_i64toa_s")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.unicode.static.convert")]]
errno_t _ltoa_s(long val, [[nonnull]] char *buf, $size_t buflen, int radix) {
	char *p;
	long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
@@pp_ifdef ERANGE@@
			return ERANGE;
@@pp_else@@
			return 1;
@@pp_endif@@
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf)) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
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

[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ui64toa_s")]]
[[section(".text.crt.dos.unicode.static.convert")]]
errno_t _ultoa_s(unsigned long val, [[nonnull]] char *buf, $size_t buflen, int radix) {
	char *p;
	unsigned long temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf)) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
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


%
%#ifdef __UINT64_TYPE__
[[alt_variant_of(__SIZEOF_INT__ == 8, itoa)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_itoa")]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, ltoa)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ltoa")]]
[[section(".text.crt.dos.unicode.static.convert")]]
char *_i64toa($s64 val, [[nonnull]] char *buf, int radix) {
	_i64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[alt_variant_of(__SIZEOF_LONG__ == 8, "ultoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ultoa")]]
[[section(".text.crt.dos.unicode.static.convert")]]
char *_ui64toa($u64 val, [[nonnull]] char *buf, int radix) {
	_ui64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[decl_include("<bits/types.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, _ltoa_s)]]
[[alt_variant_of(__SIZEOF_INT__ == 8, _itoa_s)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.unicode.static.convert")]]
errno_t _i64toa_s($s64 val, [[nonnull]] char *buf, $size_t buflen, int radix) {
	char *p;
	s64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
@@pp_ifdef ERANGE@@
			return ERANGE;
@@pp_else@@
			return 1;
@@pp_endif@@
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf)) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
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

[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, _ultoa_s)]]
[[section(".text.crt.dos.unicode.static.convert")]]
errno_t _ui64toa_s($u64 val, [[nonnull]] char *buf, $size_t buflen, int radix) {
	char *p;
	u64 temp;
	if (radix < 2)
		radix = 10;
	p = buf;
	temp = val;
	do ++p;
	while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= ($size_t)(p - buf)) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
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


%[insert:function(_strtoi64 = strto64)]
%[insert:function(_strtoui64 = strtou64)]
%[insert:function(_strtoi64_l = strto64_l)]
%[insert:function(_strtoui64_l = strtou64_l)]


[[wunused, pure]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[alt_variant_of(__SIZEOF_INT__ == 8, "atoi")]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, "atol")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, "atoll")]]
$s64 _atoi64([[nonnull]] char const *__restrict nptr) {
	return strto64(nptr, NULL, 10);
}

[[wunused, pure]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[alt_variant_of(__SIZEOF_INT__ == 8, _atoi_l)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, _atol_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, _atoll_l)]]
$s64 _atoi64_l([[nonnull]] char const *__restrict nptr, $locale_t locale) {
	return strto64_l(nptr, NULL, 10, locale);
}
%#endif /* __UINT64_TYPE__ */


[[wunused, pure, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrlen([[nonnull]] char const *str) {
	size_t result = 0;
	while (unicode_readutf8((char const **)&str))
		++result;
	return result;
}

[[wunused, pure, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrnlen([[nonnull]] char const *str, $size_t maxlen) {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}

[[wunused, pure, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrlen_l([[nonnull]] char const *str, $locale_t locale) {
	(void)locale;
	return _mbstrlen(str);
}

[[wunused, pure, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrnlen_l([[nonnull]] char const *str, $size_t maxlen, $locale_t locale) {
	(void)locale;
	return _mbstrnlen(str, maxlen);
}

[[wunused, pure, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _mblen_l([[nonnull]] char const *str, $size_t maxlen, $locale_t locale) {
	(void)locale;
	return mblen(str, maxlen);
}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _mbtowc_l(wchar_t *dst, char const *src,
              $size_t srclen, $locale_t locale) {
	(void)locale;
	return mbtowc(dst, src, srclen);
}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstowcs_l(wchar_t *dst, char const *src,
                    $size_t dstlen, $locale_t locale) {
	(void)locale;
	return mbstowcs(dst, src, dstlen);
}


[[decl_include("<bits/types.h>")]]
[[wchar, impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _mbstowcs_s($size_t *presult,
                    wchar_t *dst, $size_t dstsize,
                    char const *src, $size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
@@pp_ifdef EILSEQ@@
	if (error == (size_t)-1)
		return EILSEQ;
@@pp_endif@@
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[wchar, impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t mbstowcs_s($size_t *presult,
                   wchar_t *dst, $size_t dstsize,
                   char const *src, $size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
@@pp_ifdef EILSEQ@@
	if (error == (size_t)-1)
		return EILSEQ;
@@pp_endif@@
	return 0;
}

[[wchar, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _mbstowcs_s_l($size_t *presult,
                      wchar_t *dst, $size_t dstsize,
                      char const *src, $size_t dstlen,
                      $locale_t locale) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = _mbstowcs_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
@@pp_ifdef EILSEQ@@
	if (error == (size_t)-1)
		return EILSEQ;
@@pp_endif@@
	return 0;
}


[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.random")]]
errno_t rand_s([[nonnull]] unsigned int *__restrict randval) {
	if (!randval) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*randval = rand();
	return 0;
}


%[insert:function(_strtol_l = strtol_l)]
%[insert:function(_strtoul_l = strtoul_l)]
%[insert:function(_strtoll_l = strtoll_l)]
%[insert:function(_strtoull_l = strtoull_l)]
%#ifndef __NO_FPU
%[insert:function(_strtod_l = strtod_l)]
%[insert:function(_strtof_l = strtof_l)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(_strtold_l = strtold_l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

%
%#ifndef _CRT_SYSTEM_DEFINED
%#define _CRT_SYSTEM_DEFINED 1
%#endif /* !_CRT_SYSTEM_DEFINED */

%
[[wchar]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _wctomb_l(char *buf, wchar_t wc, $locale_t locale) {
	(void)locale;
	return wctomb(buf, wc);
}

%
%#ifdef __USE_DOS_SLIB
[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t wctomb_s([[nonnull]] int *presult,
                 [[nonnull]] char *buf,
                 rsize_t buflen, wchar_t wc) {
	if (!presult || !buf) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	if (buflen < @MB_CUR_MAX@) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*presult = wctomb(buf, wc);
	return 0;
}
%#endif /* __USE_DOS_SLIB */

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _wctomb_s_l([[nonnull]] int *presult, [[nonnull]] char *buf,
                    $size_t buflen, wchar_t wc, $locale_t locale) {
	(void)locale;
	return wctomb_s(presult, buf, buflen, wc);
}

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _wcstombs_s_l([[nonnull]] $size_t *presult, [[nonnull]] char *buf,
                      $size_t buflen, [[nonnull]] wchar_t const *src,
                      $size_t maxlen, $locale_t locale) {
	(void)locale;
	return wcstombs_s(presult, buf, buflen, src, maxlen);
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _wcstombs_l([[nonnull]] char *dst,
                    [[nonnull]] wchar_t const *src,
                    $size_t maxlen, $locale_t locale) {
	(void)locale;
	return wcstombs(dst, src, maxlen);
}

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t wcstombs_s([[nonnull]] $size_t *presult,
                   [[nonnull]] char *buf, $size_t buflen,
                   [[nonnull]] wchar_t const *src, $size_t maxlen) {
	if (!presult || !buf || !src) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = wcstombs(buf, src, buflen);
	/* TODO: if (__buflen < *presult) return ERANGE; */
	return 0;
}


%
%/* DOS malloc extensions */

%[insert:function(_recalloc = recallocv)]

[[section(".text.crt.dos.heap")]]
[[requires_function(malloc)]]
_aligned_malloc:($size_t num_bytes, $size_t min_alignment)
	-> [[memalign(min_alignment, num_bytes)]] void *
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

[[section(".text.crt.dos.heap")]]
[[requires_function(malloc)]]
_aligned_offset_malloc:($size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [[malloc_unaligned(num_bytes)]] void *
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

[[section(".text.crt.dos.heap")]]
[[requires_function(_aligned_malloc, _aligned_free, _aligned_msize)]]
_aligned_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment)
	-> [[realign(aligned_mallptr, min_alignment, newsize)]] void *
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

[[section(".text.crt.dos.heap")]]
[[requires_function(_aligned_malloc, _aligned_free, _aligned_msize)]]
_aligned_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment)
	-> [[realign(aligned_mallptr, min_alignment, count * num_bytes)]] void *
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

[[section(".text.crt.dos.heap")]]
[[requires_function(_aligned_offset_malloc, _aligned_free, _aligned_msize)]]
_aligned_offset_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment, $size_t offset)
	-> [[realloc_unaligned(aligned_mallptr, newsize)]] void *
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

[[section(".text.crt.dos.heap")]]
[[requires_function(_aligned_offset_malloc, _aligned_free, _aligned_msize)]]
_aligned_offset_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [[realloc_unaligned(aligned_mallptr, count * num_bytes)]] void *
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

[[wunused, pure, section(".text.crt.dos.heap")]]
$size_t _aligned_msize(void *aligned_mallptr, $size_t min_alignment, $size_t offset) {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return ($size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}

[[section(".text.crt.dos.heap")]]
[[requires_function(free)]]
void _aligned_free(void *aligned_mallptr) {
	if (aligned_mallptr)
		free(((void **)aligned_mallptr)[-1]);
}

%
%#define _CVTBUFSIZE   349
[[cp, section(".text.crt.dos.fs.utility")]]
char *_fullpath(char *buf, char const *path, $size_t buflen);

%#ifndef __NO_FPU
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _ecvt_s([[nonnull]] char *buf, $size_t buflen,
                double val, int ndigit,
                [[nonnull]] int *__restrict decptr,
                [[nonnull]] int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _fcvt_s([[nonnull]] char *buf, $size_t buflen,
                double val, int ndigit,
                [[nonnull]] int *__restrict decptr,
                [[nonnull]] int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _gcvt_s([[nonnull]] char *buf, $size_t buflen,
                double val, int ndigit) {
	int a, b;
	if (!buf)
		return __EINVAL;
	ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return 0;
}


%[insert:function(_ecvt = ecvt)]
%[insert:function(_fcvt = fcvt)]
%[insert:function(_gcvt = gcvt)]

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atoflt([[nonnull]] float *__restrict result,
            [[nonnull]] char const *__restrict nptr) {
	*result = strtof(nptr, NULL);
	return 0;
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atoflt_l([[nonnull]] float *__restrict result,
              [[nonnull]] char const *__restrict nptr, $locale_t locale) {
	*result = strtof_l(nptr, NULL, locale);
	return 0;
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias("_atoldbl")]]
int _atodbl([[nonnull]] double *__restrict result,
            [[nonnull]] char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtod(nptr, NULL);
	return 0;
}

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias("_atoldbl_l")]]
int _atodbl_l([[nonnull]] double *__restrict result,
              [[nonnull]] char __KOS_FIXED_CONST *__restrict nptr, $locale_t locale) {
	*result = strtod_l(nptr, NULL, locale);
	return 0;
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias("_atodbl")]]
int _atoldbl([[nonnull]] __LONGDOUBLE *__restrict result,
             [[nonnull]] char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtold(nptr, NULL);
	return 0;
}

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__), alias("_atodbl_l")]]
int _atoldbl_l([[nonnull]] __LONGDOUBLE *__restrict result,
               [[nonnull]] char __KOS_FIXED_CONST *__restrict nptr,
               $locale_t locale) {
	*result = strtold_l(nptr, NULL, locale);
	return 0;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */


[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_lrotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotl64")]]
unsigned int _rotl(unsigned int val, int shift) {
	return __hybrid_rol(val, shift);
}

[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_lrotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotr64")]]
unsigned int _rotr(unsigned int val, int shift) {
	return __hybrid_ror(val, shift);
}

%#ifdef __UINT64_TYPE__
[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_lrotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotl")]]
$u64 _rotl64($u64 val, int shift) {
	return __hybrid_rol64(val, shift);
}

[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_lrotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotr")]]
$u64 _rotr64($u64 val, int shift) {
	return __hybrid_ror64(val, shift);
}
%#endif /* __UINT64_TYPE__ */

[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_rotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_rotl64")]]
unsigned long _lrotl(unsigned long val, int shift) {
	return __hybrid_rol(val, shift);
}

[[nothrow, const, section(".text.crt.dos.math.utility")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_rotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_rotr64")]]
unsigned long _lrotr(unsigned long val, int shift) {
	return __hybrid_ror(val, shift);
}

%
%#ifndef _CRT_PERROR_DEFINED
%#define _CRT_PERROR_DEFINED 1
%[insert:extern(perror)]
%#endif  /* _CRT_PERROR_DEFINED */

%
%[insert:function(_putenv = putenv)]
%[insert:function(_swab = swab)]

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.fs.environ")]]
[[requires_function(setenv), impl_include("<libc/errno.h>")]]
errno_t _putenv_s(char const *varname, char const *val) {
	return setenv(varname, val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}


[[section(".text.crt.dos.fs.utility")]]
[[cp, requires_function(_searchenv_s)]]
void _searchenv([[nonnull]] char const *file,
                [[nonnull]] char const *envvar,
                [[nonnull]] char *__restrict resultpath) {
	_searchenv_s(file, envvar, resultpath, ($size_t)-1);
}

[[section(".text.crt.dos.fs.utility")]]
[[cp, decl_include("<bits/types.h>")]]
errno_t _searchenv_s([[nonnull]] char const *file,
                     [[nonnull]] char const *envvar,
                     [[nonnull]] char *__restrict resultpath,
                     $size_t buflen);

[[section(".text.crt.dos.fs.utility")]]
void _makepath([[nonnull]] char *__restrict buf,
               char const *drive, char const *dir,
               char const *file, char const *ext) {
	_makepath_s(buf, ($size_t)-1, drive, dir, file, ext);
}

[[section(".text.crt.dos.fs.utility")]]
void _splitpath([[nonnull]] char const *__restrict abspath,
                char *drive, char *dir, char *file, char *ext) {
	_splitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}

[[section(".text.crt.dos.fs.utility")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _makepath_s([[nonnull]] char *buf, $size_t buflen,
                    char const *drive, char const *dir,
                    char const *file, char const *ext) {
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
		if (*ext != '.')
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

[[section(".text.crt.dos.fs.utility")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _splitpath_s([[nonnull]] char const *__restrict abspath,
                     [[outp_opt(drivelen)]] char *drive, $size_t drivelen,
                     [[outp_opt(dirlen)]] char *dir, $size_t dirlen,
                     [[outp_opt(filelen)]] char *file, $size_t filelen,
                     [[outp_opt(extlen)]] char *ext, $size_t extlen) {
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
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
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
@@pp_ifdef EINVAL@@
	return EINVAL;
@@pp_else@@
	return 1;
@@pp_endif@@
err_range:
@@pp_ifdef ERANGE@@
	__libc_seterrno(ERANGE);
	return ERANGE;
@@pp_else@@
	return 1;
@@pp_endif@@
}

[[section(".text.crt.dos.errno")]]
void _seterrormode(int mode);

[[section(".text.crt.dos.errno")]]
int _set_error_mode(int mode);

[[section(".text.crt.dos.system")]]
void _beep(unsigned int freq, unsigned int duration);

[[cp]] void _sleep($u32 duration) = sleep;

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
#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("__environ");
#define environ environ
#elif defined(__CRT_HAVE___environ)
#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
__LIBC char **__environ;
#endif /* !____environ_defined */
#define environ __environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ (*__p__environ())
#else /* ... */
#undef __environ_defined
#endif /* !... */
#endif /* !__environ_defined */
}

%
%[insert:extern(swab)]


%
%
%

[[dos_only_export_alias("_itoa")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_ltoa", "ltoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_i64toa")]]
char *itoa(int val, [[nonnull]] char *buf, int radix) {
	_itoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[dos_only_export_alias("_ltoa")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, "itoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_itoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_i64toa")]]
char *ltoa(long val, [[nonnull]] char *buf, int radix) {
	_ltoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[dos_only_export_alias("_ultoa")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ui64toa")]]
char *ultoa(unsigned long val, [[nonnull]] char *buf, int radix) {
	_ultoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

%[insert:function(_onexit = onexit)]

%[define_replacement(onexit_t = _onexit_t)]
%[define_replacement(_onexit_t = _onexit_t)]
%[define(DEFINE_ONEXIT_T =
#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBDCALL *_onexit_t)(void);
#endif  /* _ONEXIT_T_DEFINED */
)]
%[define_type_class(onexit_t  = "TP")]
%[define_type_class(_onexit_t = "TP")]

[[section(".text.crt.dos.sched.process")]]
[[dos_only_export_alias("_onexit"), decl_prefix(DEFINE_ONEXIT_T)]]
onexit_t onexit(onexit_t func);


%#ifndef _WSTDLIB_DEFINED
%#define _WSTDLIB_DEFINED

[[guard, wchar, wunused]]
[[section(".text.crt.dos.wchar.fs.environ")]]
wchar_t *_wgetenv([[nonnull]] wchar_t const *varname);

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
[[guard, wchar, decl_include("<bits/types.h>")]]
errno_t _wgetenv_s([[nonnull]] $size_t *return_size,
                   [[outp_opt(buflen)]] wchar_t *buf, $size_t buflen,
                   [[nonnull]] wchar_t const *varname);

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
[[guard, wchar, decl_include("<bits/types.h>")]]
errno_t _wdupenv_s([[nonnull]] wchar_t **pbuf,
                   [[nonnull]] $size_t *pbuflen,
                   [[nonnull]] wchar_t const *varname);

%[insert:function(_wsystem = wsystem, guardName: "_CRT_WSYSTEM_DEFINED")]

%[insert:extern(wcstol)]
%[insert:extern(wcstoll)]
%[insert:extern(wcstoul)]
%[insert:extern(wcstoull)]
%[insert:guarded_function(_wcstol_l = wcstol_l)]
%[insert:guarded_function(_wcstoul_l = wcstoul_l)]

%#ifndef __NO_FPU
%[insert:extern(wcstof)]
%[insert:extern(wcstod)]
%[insert:guarded_function(_wcstof_l = wcstof_l)]
%[insert:guarded_function(_wcstod_l = wcstod_l)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:extern(wcstold)]
%[insert:guarded_function(_wcstold_l = wcstold_l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

[[guard, wchar, wunused, pure]]
[[section(".text.crt.dos.wchar.unicode.static.convert")]]
double _wtof([[nonnull]] wchar_t const *nptr) {
	return wcstod(nptr, NULL);
}

[[guard, wchar, wunused, pure]]
[[section(".text.crt.dos.wchar.unicode.static.convert")]]
double _wtof_l([[nonnull]] wchar_t const *nptr,
               [[nullable]] $locale_t locale) {
	return wcstod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_itow(*) %{generate(str2wcs("itoa"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ltow(*) %{generate(str2wcs("ltoa"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ultow(*) %{generate(str2wcs("ultoa"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_i64tow(*) %{generate(str2wcs("_i64toa"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ui64tow(*) %{generate(str2wcs("_ui64toa"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_itow_s(*) %{generate(str2wcs("_itoa_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ltow_s(*) %{generate(str2wcs("_ltoa_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ultow_s(*) %{generate(str2wcs("_ultoa_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_i64tow_s(*) %{generate(str2wcs("_i64toa_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ui64tow_s(*) %{generate(str2wcs("_ui64toa_s"))}

%[insert:guarded_function(_wtoi = wtoi)]
%[insert:guarded_function(_wtol = wtol)]

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       alias("_wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias("_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoll")]]
_wtoi64(*) %{generate(str2wcs("_atoi64"))}

%[insert:guarded_function(_wcstoi64  = wcsto64)]
%[insert:guarded_function(_wcstoui64 = wcstou64)]

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("_wtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("_wtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),                    alias("_wtoi64_l")]]
_wtoi_l(*) %{generate(str2wcs("_atoi_l"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _wtoi_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("_wtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_wtoi64_l")]]
_wtol_l(*) %{generate(str2wcs("_atol_l"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_INT__ == 8, _wtoi_l)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, _wtol_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, _wtoll_l)]]
_wtoi64_l(*) %{generate(str2wcs("_atoi64_l"))}

%[insert:guarded_function(_wcstoi64_l  = wcsto64_l)]
%[insert:guarded_function(_wcstoui64_l = wcstou64_l)]


%#ifdef __LONGLONG
%[insert:guarded_function(_wcstoll_l  = wcstoll_l)]
%[insert:guarded_function(_wcstoull_l = wcstoull_l)]
%[insert:guarded_function(_wtoll      = wtoll)]

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _wtoi_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _wtol_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoi64_l")]]
_wtoll_l(*) %{generate(str2wcs("_atoll_l"))}
%#endif /* __LONGLONG */

%#endif /* !_WSTDLIB_DEFINED */


%#ifndef _WSTDLIBP_DEFINED
%#define _WSTDLIBP_DEFINED 1

[[guard, wchar, section(".text.crt.dos.wchar.fs.utility")]]
wchar_t *_wfullpath(wchar_t *buf, wchar_t const *path, $size_t buflen);

[[guard, wchar, section(".text.crt.dos.wchar.fs.utility")]]
_wmakepath_s(*) %{generate(str2wcs("_makepath_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.fs.utility")]]
_wmakepath(*) %{generate(str2wcs("_makepath"))}

%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]

%[define_str2wcs_replacement(_putenv      = _wputenv)]
%[define_str2wcs_replacement(_putenv_s    = _wputenv_s)]
%[define_str2wcs_replacement(_searchenv_s = _wsearchenv_s)]

[[guard, wchar, section(".text.crt.dos.wchar.fs.environ")]]
int _wputenv([[nonnull]] wchar_t *string);

[[guard, wchar, decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
errno_t _wputenv_s(wchar_t const *varname, wchar_t const *val);

[[cp, guard, wchar, decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
errno_t _wsearchenv_s([[nonnull]] wchar_t const *file,
                      [[nonnull]] wchar_t const *envvar,
                      [[nonnull]] wchar_t *__restrict resultpath,
                      $size_t buflen);

[[guard, wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsearchenv(*) %{generate(str2wcs("_searchenv"))}

[[guard, wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsplitpath(*) %{generate(str2wcs("_splitpath"))}

[[guard, wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsplitpath_s(*) %{generate(str2wcs("_splitpath_s"))}

%#endif /* !_WSTDLIBP_DEFINED */



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
