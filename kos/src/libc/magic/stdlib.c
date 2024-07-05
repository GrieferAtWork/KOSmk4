/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: DJGPP         (/include/stdlib.h) */
/* (#) Portability: DragonFly BSD (/include/stdlib.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdlib.h) */
/* (#) Portability: FreeBSD       (/include/stdlib.h) */
/* (#) Portability: GNU C Library (/stdlib/stdlib.h) */
/* (#) Portability: GNU Hurd      (/usr/include/stdlib.h) */
/* (#) Portability: MSVC          (/include/stdlib.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdlib.h) */
/* (#) Portability: NetBSD        (/include/stdlib.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: OpenBSD       (/include/stdlib.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdlib.h) */
/* (#) Portability: PDCLib        (/include/stdlib.h) */
/* (#) Portability: Windows Kits  (/ucrt/stdlib.h) */
/* (#) Portability: avr-libc      (/include/stdlib.h) */
/* (#) Portability: diet libc     (/include/stdlib.h) */
/* (#) Portability: libbsd        (/include/bsd/stdlib.h) */
/* (#) Portability: libc4/5       (/include/stdlib.h) */
/* (#) Portability: libc6         (/include/stdlib.h) */
/* (#) Portability: libcmini      (/include/stdlib.h) */
/* (#) Portability: mintlib       (/include/stdlib.h) */
/* (#) Portability: musl libc     (/include/stdlib.h) */
/* (#) Portability: uClibc        (/include/stdlib.h) */
}

%[define_decl_include("<bits/crt/random-data.h>": [
	"struct random_data",
])]

%[define_ccompat_header("cstdlib")]

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
%[define_replacement(shift_t = __SHIFT_TYPE__)]

/* itoa */
%[define_replacement(itoa_digit         = __LOCAL_itoa_digit)]
%[define_replacement(itoa_decimal       = __LOCAL_itoa_decimal)]
%[define_replacement(_itoa_digits       = __LOCAL_itoa_digits)]
%[define_replacement(_itoa_lower_digits = __LOCAL_itoa_lower_digits)]
%[define_replacement(_itoa_upper_digits = __LOCAL_itoa_upper_digits)]

%[define_replacement(__WAIT_STATUS = __WAIT_STATUS)]
%[define_replacement(__WAIT_STATUS_DEFN = __WAIT_STATUS_DEFN)]
%[define_type_class(__WAIT_STATUS      = "TP")]
%[define_type_class(__WAIT_STATUS_DEFN = "TP")]
%[define_type_class(__on_exit_func_t   = "TP")]
%[define_type_class(comparison_fn_t    = "TP")]
%[define_type_class(__compar_fn_t      = "TP")]
%[define_type_class(__compar_d_fn_t    = "TP")]

%[assume_defined_in_kos(NAME_MAX = "65535")]
%[assume_defined_in_kos(__NAME_MAX = "65535")]
%[assume_defined_in_kos(PATH_MAX = "-1")]
%[assume_defined_in_kos(__PATH_MAX = "-1")]


%[define_decl_include("<bits/crt/div.h>": [
	"struct __div_struct",
	"struct __ldiv_struct",
	"struct __lldiv_struct",
])]

%[define_replacement(div_t = "struct __div_struct")]
%[define_replacement(ldiv_t = "struct __ldiv_struct")]
%[define_replacement(lldiv_t = "struct __lldiv_struct")]
%[define_type_class(div_t = "TS(__SIZEOF_DIV_STRUCT)")]
%[define_type_class(ldiv_t = "TS(__SIZEOF_LDIV_STRUCT)")]
%[define_type_class(lldiv_t = "TS(__SIZEOF_LLDIV_STRUCT)")]


%(auto_source){
#include "../libc/globals.h"
#include <strings.h>
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
#include <bits/crt/div.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_MISC
#include <alloca.h>
#include <bits/crt/random-data.h>
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

#ifdef __USE_NETBSD
#include <asm/crt/humanize_number.h>
#endif /* __USE_NETBSD */

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
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

__NAMESPACE_STD_BEGIN
#ifndef __std_div_t_defined
#define __std_div_t_defined
typedef struct __div_struct div_t;
#endif /* !__std_div_t_defined */
#ifndef __std_ldiv_t_defined
#define __std_ldiv_t_defined
typedef struct __ldiv_struct ldiv_t;
#endif /* !__std_ldiv_t_defined */
#if defined(__USE_ISOC99) && defined(__LONGLONG)
#ifndef __std_lldiv_t_defined
#define __std_lldiv_t_defined
typedef struct __lldiv_struct lldiv_t;
#endif /* !__std_lldiv_t_defined */
#endif /* __USE_ISOC99 && __LONGLONG */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __div_t_defined
#define __div_t_defined
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

}

%[define_crt_name_list(CNL_llabs       = ["llabs", "qabs"])]
%[define_crt_name_list(CNL_lldiv       = ["lldiv", "qdiv"])]
%[define_crt_name_list(CNL_strtol      = ["strtol"])]
%[define_crt_name_list(CNL_strtoul     = ["strtoul"])]
%[define_crt_name_list(CNL_strtoll     = ["strtoll", "strtoq", "__strtoq"])]
%[define_crt_name_list(CNL_strtoull    = ["strtoull", "strtouq", "__strtouq"])]
%[define_crt_name_list(CNL_strtoimax   = ["strtoimax"])]
%[define_crt_name_list(CNL_strtoumax   = ["strtoumax"])]
%[define_crt_name_list(CNL_strtol_l    = ["strtol_l", "_strtol_l", "__strtol_l"])]
%[define_crt_name_list(CNL_strtoul_l   = ["strtoul_l", "_strtoul_l", "__strtoul_l"])]
%[define_crt_name_list(CNL_strtoll_l   = ["strtoll_l", "_strtoll_l", "__strtoll_l", "strtoq_l"])]
%[define_crt_name_list(CNL_strtoull_l  = ["strtoull_l", "_strtoull_l", "__strtoull_l", "strtouq_l"])]
%[define_crt_name_list(CNL_strtoimax_l = ["strtoimax_l", "_strtoimax_l", "__strtoimax_l"])]
%[define_crt_name_list(CNL_strtoumax_l = ["strtoumax_l", "_strtoumax_l", "__strtoumax_l"])]



%
%#ifdef __USE_KOS

%{
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}

[[nothrow_cb_ncx, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.utility.stdlib")]]
[[crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(a, b, c->arg); },
	impl: bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void *bsearch_r([[in]] void const *pkey, [[in(item_count * item_size)]] void const *pbase, $size_t item_count, $size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg)
	[([[in]] void const *pkey, [[in(item_count * item_size)]] void *pbase, $size_t item_count, $size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg): void *]
	[([[in]] void const *pkey, [[in(item_count * item_size)]] void const *pbase, $size_t item_count, $size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg): void const *]
{
	/* Optimize this function with the (allowed) assumption that `pbase' is sorted according to:
	 * >> qsort_r(pbase, item_count, item_size, compar, arg); */
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
		difference = (*compar)(pkey, item_addr, arg);
		if (difference < 0) {
			/* KEY < ITEM --> Narrow the search-area to everything below */
			hi = test_index;
		} else if (difference > 0) {
			/* KEY > ITEM --> Narrow the search-area to everything above */
			lo = test_index + 1;
		} else {
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



%[define(DEFINE_INVOKE_COMPARE_HELPER =
@@pp_ifndef         __LIBCCALL_CALLER_CLEANUP@@
@@pp_ifndef ____invoke_compare_helper_defined@@
@@push_namespace(local)@@
#define ____invoke_compare_helper_defined
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(int (__LIBCCALL *)(void const *, void const *))__arg)(__a, __b);
}
@@pop_namespace@@
@@pp_endif@@
@@pp_endif@@
)]

[[nothrow_cb_ncx, std, kernel, guard]]
[[decl_include("<hybrid/typecore.h>")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_qsort_r")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_qsort_r")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER)]]
[[section(".text.crt{|.dos}.utility.stdlib")]]
[[crt_dos_variant(callback(
	cook: auto = compar,
	wrap: (void const *a, void const *b, $cook c): int { return (*c)(a, b); },
	impl: qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, (void *)$cook),
))]]
void qsort([[inout(item_count * item_size)]] void *pbase, size_t item_count, size_t item_size,
           [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	qsort_r(pbase, item_count, item_size,
	        (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar,
	        NULL);
@@pp_else@@
	qsort_r(pbase, item_count, item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)compar);
@@pp_endif@@
}

[[wunused, std, nothrow_cb_ncx, guard]]
[[decl_include("<hybrid/typecore.h>")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_bsearch_r")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_bsearch_r")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER)]]
[[section(".text.crt{|.dos}.utility.stdlib")]]
[[crt_dos_variant(callback(
	cook: auto = compar,
	wrap: (void const *a, void const *b, $cook c): int { return (*c)(a, b); },
	impl: bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, (void *)$cook),
))]]
void *bsearch([[in]] void const *pkey, [[in(item_count * item_size)]] void const *pbase, size_t item_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b))
	[([[in]] void const *pkey, [[in(item_count * item_size)]] void *pbase, size_t item_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)): void *]
	[([[in]] void const *pkey, [[in(item_count * item_size)]] void const *pbase, size_t item_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)): void const *]
{
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	return (void *)bsearch_r(pkey, pbase, item_count, item_size,
	                         (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar,
	                         NULL);
@@pp_else@@
	return (void *)bsearch_r(pkey, pbase, item_count, item_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	                         (void *)compar);
@@pp_endif@@
}


[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ == __SIZEOF_INT__), export_as("imaxabs")]]
[[std, const, wunused, nothrow, crtbuiltin, extern_inline]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_abs64")]]
[[section(".text.crt{|.dos}.math.utility")]]
int abs(int x) {
	return x < 0 ? -x : x;
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("imaxabs")]]
[[std, const, wunused, nothrow, crtbuiltin, extern_inline]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, abs)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_abs64")]]
[[section(".text.crt{|.dos}.math.utility")]]
long labs(long x) {
	return x < 0 ? -x : x;
}



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

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ == __SIZEOF_INT__), export_as("imaxdiv")]]
[[std, attribute("__ATTR_CONST"), wunused, decl_include("<bits/crt/div.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("ldiv")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias(CNL_lldiv...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
[[section(".text.crt{|.dos}.math.utility")]]
struct __div_struct div(int numer, int denom) {
	div_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("imaxdiv")]]
[[std, attribute("__ATTR_CONST"), wunused, decl_include("<bits/crt/div.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, div)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_lldiv...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
[[section(".text.crt{|.dos}.math.utility")]]
$ldiv_t ldiv(long numer, long denom) {
	ldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),
  export_as("imaxabs")]]
[[std, const, wunused, nothrow, crtbuiltin, extern_inline]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_llabs...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, "abs")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, "labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_abs64")]]
[[section(".text.crt{|.dos}.math.utility")]]
__LONGLONG llabs(__LONGLONG x) {
	return x < 0 ? -x : x;
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),
  export_as("imaxdiv")]]
[[std, attribute("__ATTR_CONST"), wunused, decl_include("<bits/crt/div.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_lldiv...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, div)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, ldiv)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("imaxdiv")]]
[[section(".text.crt{|.dos}.math.utility")]]
$lldiv_t lldiv(__LONGLONG numer, __LONGLONG denom) {
	lldiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}
%(std, c, ccompat)#endif /* __USE_ISOC99 */

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

[[std, wunused, crt_dos_variant, userimpl]]
[[requires_include("<libc/template/environ.h>")]]
[[requires(defined(__LOCAL_environ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(
@@pp_ifndef __OPTIMIZE_SIZE__@@
#include <hybrid/__unaligned.h>
@@pp_endif@@
)]]
[[section(".text.crt{|.dos}.fs.environ")]]
char *getenv([[in]] char const *varname) {
	char *result, **envp;
	if unlikely(!varname)
		return NULL;
	envp = __LOCAL_environ;
	if unlikely(!envp) {
		result = NULL;
	} else {
		size_t namelen = strlen(varname);
@@pp_ifdef __OPTIMIZE_SIZE__@@
		for (; (result = *envp) != NULL; ++envp) {
			if (bcmpc(result, varname, namelen, sizeof(char)) != 0)
				continue;
			if (result[namelen] != '=')
				continue;
			result += namelen + 1;
			break;
		}
@@pp_else@@
		union {
			uint16_t      word;
			unsigned char chr[2];
		} pattern;

		/* Following the assumption that no environment variable string
		 * (should)  ever consist of an empty string, we can infer that
		 * all  variable strings  should consist  of at  least 2 bytes,
		 * namely the first character of the name, followed by at least
		 * the terminating NUL character.
		 *
		 * As such, when walking the  table of strings, we can  speed
		 * up operation via an initial dismissal check that  compares
		 * the first 2 characters from the environ-string against the
		 * expected pattern based on the caller's `varname'.
		 *
		 * As far as portability goes, Glibc makes the same assumption. */
		if unlikely(!namelen) {
			result = NULL;
		} else {
			pattern.word = __hybrid_unaligned_get16(varname);
			if unlikely(namelen == 1) {
				/* Single-character variable name -> Only need to search for
				 * that specific character,  as well as  the follow-up  '='! */
				pattern.chr[1] = '=';
				for (; (result = *envp) != NULL; ++envp) {
					if (__hybrid_unaligned_get16(result) != pattern.word)
						continue;
					result += 2;
					break;
				}
			} else {
				size_t tail_namelen;
				varname += 2;
				tail_namelen = namelen - 2;
				for (; (result = *envp) != NULL; ++envp) {
					if (__hybrid_unaligned_get16(result) != pattern.word)
						continue; /* First 2 characters don't match. */
					if (bcmpc(result + 2, varname, tail_namelen, sizeof(char)) != 0)
						continue; /* Rest of string didn't match */
					if (result[namelen] != '=')
						continue; /* It's not the complete string. */
					result += namelen + 1;
					break;
				}
			}
		}
@@pp_endif@@
	}
	return result;
}

[[std, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int mblen([[in_opt/*(maxlen)*/]] char const *str, size_t maxlen) {
	return mbrlen(str, maxlen, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int mbtowc([[out_opt]] wchar_t *__restrict pwc,
           [[in_opt/*(maxlen)*/]] char const *__restrict str,
           size_t maxlen) {
	return mbrtowc(pwc, str, maxlen, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int wctomb([[out_opt]] char *str, wchar_t wc) {
	return wcrtomb(str, wc, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
size_t mbstowcs([[out(return <= dstlen)]] wchar_t *__restrict dst,
                [[in]] char const *__restrict src, size_t dstlen) {
	return mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}

[[std, wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
size_t wcstombs([[out(return <= dstlen)]] char *__restrict dst,
                [[in]] wchar_t const *__restrict src, size_t dstlen) {
	return wcsrtombs(dst, (wchar_t const **)&src, dstlen, NULL);
}

@@>> system(3)
@@Execute a given `command' on the system interpreter (as in `sh -c $command')
@@The return value is the `union wait' status after running `command', and may
@@be inspected using the `W*' macros (e.g. `WIFEXITED()') from `<sys/wait.h>'.
@@
@@When `command' is `NULL' only check if a system interpreter is available, and
@@return 0(false)/1(true) indicative of its present. When no system interpreter
@@is available and `command != NIL', `W_EXITCODE(127, 0)' is returned.
@@
@@@return: -1: Error (s.a. `errno')
@@@return: 0 : [command == NULL] No system interpreter is available
@@@return: 1 : [command == NULL] A system interpreter is available
@@@return: * : The `union wait'-style exit status of running `command'
[[cp, std, guard]]
[[export_alias("__libc_system")]]
[[requires($has_function(shexec, _Exit, waitpid) &&
           ($has_function(vfork) || $has_function(fork)))]]
[[section(".text.crt{|.dos}.fs.exec.system")]]
int system([[in_opt]] char const *command) {
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
	return status;
}


[[std, guard, noreturn, no_nothrow, crtbuiltin]]
[[export_alias("_ZSt9terminatev", "terminate", "__chk_fail")]]
[[dos_only_export_alias("?terminate@@YAXXZ")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_ABORT))]]
[[requires_function(_Exit), impl_include("<asm/os/stdlib.h>")]]
[[section(".text.crt{|.dos}.application.exit")]]
void abort() {
	_Exit(@__EXIT_FAILURE@);
}

[[std, guard, noreturn, no_nothrow, crtbuiltin]]
[[alias("quick_exit", "_exit", "_Exit"), export_alias("xexit")]]
[[section(".text.crt{|.dos}.application.exit")]]
void exit(int status);

[[dos_only_export_alias("_crt_atexit")]]
[[std, alias("at_quick_exit", "_crt_at_quick_exit")]]
[[export_alias("xatexit")]]
[[section(".text.crt{|.dos}.sched.process")]]
int atexit([[nonnull]] void (LIBCCALL *func)(void));


%(std, c, ccompat)#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
[[std, noreturn, no_nothrow, alias("exit", "_exit", "_Exit")]]
[[section(".text.crt{|.dos}.sched.process")]]
void quick_exit(int status);

[[dos_only_export_alias("_crt_at_quick_exit")]]
[[std, alias("atexit", "_crt_atexit")]]
[[section(".text.crt{|.dos}.sched.process")]]
int at_quick_exit([[nonnull]] void (LIBCCALL *func)(void));
%(std, c, ccompat)#endif /* __USE_ISOC11 || __USE_ISOCXX11 */

%(std, c, ccompat)#ifdef __USE_ISOC99
[[std, noreturn, no_nothrow]]
[[crtbuiltin, export_alias("_exit"), alias("quick_exit", "exit")]]
[[if(__has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("_exit", { __builtin__exit(status); })]]
[[section(".text.crt{|.dos}.application.exit")]]
void _Exit(int status);
%(std, c, ccompat)#endif /* __USE_ISOC99 */

[[ignore, decl_include("<hybrid/typecore.h>")]]
[[nocrt, alias("calloc", "__libc_calloc")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
void *crt_calloc(size_t count, size_t num_bytes);

[[std, guard, libc, decl_include("<hybrid/typecore.h>")]]
[[ATTR_ALLOC_SIZE((1)), wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[crtbuiltin, export_alias("__libc_malloc")]]
[[userimpl, requires($has_function(crt_calloc) || $has_function(realloc) || $has_function(memalign))]]
[[section(".text.crt{|.dos}.heap.malloc")]]
[[export_as("__malloc")]] /* From Glibc 2.0.4 */
void *malloc(size_t num_bytes) {
@@pp_if $has_function(crt_calloc)@@
	return crt_calloc(1, num_bytes);
@@pp_elif $has_function(realloc)@@
	return realloc(NULL, num_bytes);
@@pp_else@@
	return memalign(__LIBC_MALLOC_ALIGNMENT, num_bytes);
@@pp_endif@@
}

[[guard, std, libc, decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
[[crtbuiltin, export_alias("__libc_calloc")]]
[[userimpl, requires_function(malloc)]]
[[impl_include("<hybrid/__overflow.h>")]]
[[section(".text.crt{|.dos}.heap.malloc")]]
[[export_as("__calloc")]] /* From Glibc 2.0.4 */
void *calloc(size_t count, size_t num_bytes) {
	void *result;
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(count, num_bytes, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = malloc(total_bytes);
	if likely(result)
		bzero(result, total_bytes);
	return result;
}

[[guard, std, libc, decl_include("<hybrid/typecore.h>")]]
[[crtbuiltin, export_alias("__libc_realloc")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
[[section(".text.crt{|.dos}.heap.malloc")]]
[[export_as("__realloc")]] /* From Glibc 2.0.4 */
void *realloc(void *mallptr, size_t num_bytes);

[[guard, std, libc]]
[[crtbuiltin, export_alias("cfree", "__libc_free" /*, "__builtin_delete"*/ )]]
[[section(".text.crt{|.dos}.heap.malloc")]]
[[export_as("__cfree", "__free")]] /* From Glibc 2.0.4 */
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
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("random")]]
[[section(".text.crt{|.dos}.random")]]
int rand() {
	COMPILER_IMPURE();
	/* https://xkcd.com/221/ */
	return 4;
}


/* Convert a string to an integer.  */
[[std, pure, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("atol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("atoll")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
int atoi([[in]] char const *__restrict nptr) {
@@pp_if __SIZEOF_INT__ <= 4@@
	return (int)strto32(nptr, NULL, 10);
@@pp_else@@
	return (int)strto64(nptr, NULL, 10);
@@pp_endif@@
}

[[std, pure, wunused]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, "atoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("atoll")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
long atol([[in]] char const *__restrict nptr) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (long)strto32(nptr, NULL, 10);
@@pp_else@@
	return (long)strto64(nptr, NULL, 10);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("strtoimax")]]
[[std, leaf, guard]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtol...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4, strto32)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_strtoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
long strtol([[in]] char const *__restrict nptr,
            [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (long)strto32(nptr, endptr, base);
@@pp_else@@
	return (long)strto64(nptr, endptr, base);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("strtoumax")]]
[[std, leaf, guard]]
[[decl_include("<features.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoul...)]]
[[alt_variant_of(__SIZEOF_LONG__ == 4, strtou32)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_strtoumax...)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
unsigned long strtoul([[in]] char const *__restrict nptr,
                      [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG__ <= 4@@
	return (unsigned long)strtou32(nptr, endptr, base);
@@pp_else@@
	return (unsigned long)strtou64(nptr, endptr, base);
@@pp_endif@@
}


%(std, c, ccompat)#if defined(__LONGLONG) && defined(__USE_ISOC99)
[[std, pure, wunused]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, atoi)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, atol)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
__LONGLONG atoll([[in]] char const *__restrict nptr) {
@@pp_if __SIZEOF_LONG_LONG__ <= 4@@
	return (__LONGLONG)strto32(nptr, NULL, 10);
@@pp_else@@
	return (__LONGLONG)strto64(nptr, NULL, 10);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), export_as("strtoimax")]]
[[std, leaf, guard]]
[[decl_include("<features.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoll...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, strto64)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4, strto32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias("_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strto32)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
__LONGLONG strtoll([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG_LONG__ <= 4@@
	return (__LONGLONG)strto32(nptr, endptr, base);
@@pp_else@@
	return (__LONGLONG)strto64(nptr, endptr, base);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), export_as("strtoumax")]]
[[std, leaf, guard]]
[[decl_include("<features.h>")]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_strtoull...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, strtou64)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4, strtou32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias("_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strtou32)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
__ULONGLONG strtoull([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_LONG_LONG__ <= 4@@
	return (__ULONGLONG)strtou32(nptr, endptr, base);
@@pp_else@@
	return (__ULONGLONG)strtou64(nptr, endptr, base);
@@pp_endif@@
}
%(std, c, ccompat)#endif /* __USE_ISOC99 && __LONGLONG */


%(std, c, ccompat)#ifndef __NO_FPU
[[std, leaf, wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
double atof([[in]] char const *__restrict nptr) {
	return strtod(nptr, NULL);
}

[[std, leaf]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("strtold", "__strtold")]]
[[impl_include("<ieee754.h>", "<libm/inf.h>", "<libm/nan.h>")]]
[[impl_include("<libc/unicode.h>", "<hybrid/typecore.h>")]]
double strtod([[in]] char const *__restrict nptr,
              [[out_opt]] char **endptr) {
	char sign, ch = *nptr;
	double float_extension_mult;
	double fltval = 0.0;
	uint8_t numsys, digit;
	while (isspace((unsigned char)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!isdigit((unsigned char)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)@@
		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0(@inf@)
			                   : +__LIBM_MATHFUN0(@inf@);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1I(@nan@, NULL)
			                   : +__LIBM_MATHFUN1I(@nan@, NULL);
		}
@@pp_endif@@
		numsys = 10;
	}

	float_extension_mult = 0.0;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0)
			goto done;
		float_extension_mult = (double)numsys;
		ch = *++nptr;
		goto next;

	default: {
@@pp_if __SIZEOF_CHAR__ == 1@@
		char const *new_nptr;
		char32_t uni;
@@pp_ifndef __OPTIMIZE_SIZE__@@
		if ((unsigned char)ch < 0x80)
			goto done;
@@pp_endif@@
		new_nptr = nptr;
		uni = @__libc_unicode_readutf8@(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else
@@pp_elif __SIZEOF_CHAR__ == 2@@
		char16_t const *new_nptr;
		char32_t uni;
		new_nptr = (char16_t const *)nptr;
		uni = @__libc_unicode_readutf16@(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else
@@pp_else@@
		if (__libc_unicode_asdigit(ch, numsys, &digit)) {
			++nptr;
		} else
@@pp_endif@@
		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0) {
		fltval += (double)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}

%(std, c, ccompat)#ifdef __USE_ISOC99
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[std, export_alias("__strtof")]] strtof(*) %{generate(double2float("strtod"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("strtod", ...)]]
[[std, export_alias("__strtold")]] strtold(*) %{generate(double2ldouble("strtod"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */
%(std, c, ccompat)#endif /* !__NO_FPU */




%
%#if !defined(__NO_FPU) && (defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__))
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT32_AS_SIZE_T strfromd([[out(return <= buflen)]] char *__restrict buf, $size_t buflen,
                                [[in]] char const *__restrict format, double fp);
/* TODO: Implement as inline */

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT32_AS_SIZE_T strfromf([[out(return <= buflen)]] char *__restrict buf, $size_t buflen,
                                [[in]] char const *__restrict format, float fp);
/* TODO: Implement as inline */

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ldouble_variant_of("strfromd", [])]]
__STDC_INT32_AS_SIZE_T strfroml([[out(return <= buflen)]] char *__restrict buf, $size_t buflen,
                                [[in]] char const *__restrict format, __LONGDOUBLE fp);
/* TODO: Implement as inline */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU  && (__USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__)*/


%
%#ifdef __USE_KOS

@@>> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
@@Safely parse & return an integer from `nptr', and store any potential
@@errors in `*error' (if non-NULL).  The following errors are  defined:
@@ - 0:         Success
@@ - ECANCELED: Nothing was parsed.
@@              In this case, `*endptr' is set to the original `nptr'
@@              (iow: leading spaces are _not_ skipped in `*endptr'),
@@              and the returned integer is `0'
@@ - ERANGE:    Integer over- or under-flow while parsing.
@@              In this case, `*endptr' is still updated correctly,  and
@@              the  returned integer is the closest representable value
@@              to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
@@              This error supersedes `EINVAL' if both conditions apply.
@@ - EINVAL:    Only when `endptr == NULL': The parsed number is followed
@@              by   at  least  1  additional  non-whitespace  character.
@@              The returned integer value is not affected by this error.
[[kernel, leaf]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint32_t strtou32_r([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[out_opt]] $errno_t *error)
	%{template(tpl_strtoi_r<uint32_t, nptr, endptr, base, error>)}

[[kernel, leaf, doc_alias("strtou32_r")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int32_t strto32_r([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                   [[out_opt]] $errno_t *error)
	%{template(tpl_strtoi_r<int32_t, nptr, endptr, base, error>)}

%#ifdef __UINT64_TYPE__
[[kernel, leaf, doc_alias("strtou32_r")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint64_t strtou64_r([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[out_opt]] $errno_t *error)
	%{template(tpl_strtoi_r<uint64_t, nptr, endptr, base, error>)}

[[kernel, leaf, doc_alias("strtou32_r")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int64_t strto64_r([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                   [[out_opt]] $errno_t *error)
	%{template(tpl_strtoi_r<int64_t, nptr, endptr, base, error>)}
%#endif /* __UINT64_TYPE__ */

%[define_template(tpl_strtoi_r<T, nptr, endptr, base, error> =
	[[impl_include("<asm/os/errno.h>", "<hybrid/__overflow.h>")]]
	[[impl_include("<libc/template/hex.h>", "<hybrid/limitcore.h>")]]
	[[impl_include("<libc/unicode.h>", "<hybrid/typecore.h>")]]
{
@@exec /*   */ global SIGNED = !"${T}".@startswith@("u");@@
@@exec /*   */ global BITS = "${T}".@strip@("uint_t");@@
@@exec /*   */ global su = SIGNED ? "s" : "u";@@
@@exec /*   */ global TU = "__UINT" + BITS + "_TYPE__";@@
@@if SIGNED@@
	char sign;
@@endif@@
	${T} result;
	char const *num_start = ${nptr};
	char const *num_iter;
	num_start = strlstrip(num_start);
@@if SIGNED@@
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
@@endif@@
	if (${base} == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				${base} = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				${base} = 2;
				++num_start;
			} else {
				${base} = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			${base} = 10;
		}
	}
	num_iter = num_start;
	result   = 0;

	for (;;) {
		uint8_t digit;
		char ch;
		ch = *num_iter;
		if (!__libc_hex2int(ch, &digit)) {
@@pp_if $has_function(__unicode_descriptor)@@
			/* Unicode decimal support */
@@pp_if __SIZEOF_CHAR__ == 1@@
			char const *new_num_iter;
			char32_t uni;
@@pp_ifndef __OPTIMIZE_SIZE__@@
			if ((unsigned char)ch < 0x80)
				break;
@@pp_endif@@
			new_num_iter = num_iter;
			uni = @__libc_unicode_readutf8@(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
				num_iter = new_num_iter;
			} else
@@pp_elif __SIZEOF_CHAR__ == 2@@
			char16_t const *new_num_iter;
			char32_t uni;
			new_num_iter = (char16_t const *)num_iter;
			uni = @__libc_unicode_readutf16@(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
				num_iter = new_num_iter;
			} else
@@pp_else@@
			if (__libc_unicode_asdigit(ch, (uint8_t)${base}, &digit)) {
				++num_iter;
			} else
@@pp_endif@@
@@pp_endif@@
			{
				break;
			}
		} else {
			if (digit >= ${base})
				break;
			++num_iter;
		}
		if unlikely(@@yield("__hybrid_overflow_" + su + "mul")@@(result, (unsigned int)${base}, &result) ||
		/*       */ @@yield("__hybrid_overflow_" + su + "add")@@(result, digit, &result)) {
@@if SIGNED@@
			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((@@yield(TU)@@)result == ((@@yield(TU)@@)0 - (@@yield(TU)@@)@@yield("__INT" + BITS + "_MIN__")@@) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {
@@pp_if $has_function(__unicode_descriptor)@@
					/* Unicode decimal support */
@@pp_if __SIZEOF_CHAR__ == 1@@
					char const *new_num_iter;
					char32_t uni;
@@pp_ifndef __OPTIMIZE_SIZE__@@
					if ((unsigned char)ch < 0x80) {
						/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
						goto handle_not_an_overflow;
					}
@@pp_endif@@
					new_num_iter = num_iter;
					uni = @__libc_unicode_readutf8@(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
						goto handle_overflow;
					} else
@@pp_elif __SIZEOF_CHAR__ == 2@@
					char16_t const *new_num_iter;
					char32_t uni;
					new_num_iter = (char16_t const *)num_iter;
					uni = @__libc_unicode_readutf16@(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
						goto handle_overflow;
					} else
@@pp_else@@
					if (__libc_unicode_asdigit(ch, (uint8_t)${base}, &digit)) {
						goto handle_overflow;
					} else
@@pp_endif@@
@@pp_endif@@
					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < ${base})
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
@@pp_if $has_function(__unicode_descriptor) && __SIZEOF_CHAR__ == 1 && !defined(__OPTIMIZE_SIZE__)@@
handle_not_an_overflow:
@@pp_endif@@
				result = @@yield("__INT" + BITS + "_MIN__")@@;
				goto return_not_an_overflow;
			}
handle_overflow:
@@endif@@
			/* Integer overflow. */
			if (${error}) {
@@pp_ifdef ERANGE@@
				*${error} = ERANGE;
@@pp_else@@
				*${error} = 1;
@@pp_endif@@
			}
			if (${endptr}) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {
@@pp_if $has_function(__unicode_descriptor)@@
						/* Unicode decimal support */
@@pp_if __SIZEOF_CHAR__ == 1@@
						char const *new_num_iter;
						char32_t uni;
@@pp_ifndef __OPTIMIZE_SIZE__@@
						if ((unsigned char)ch < 0x80)
							break;
@@pp_endif@@
						new_num_iter = num_iter;
						uni = @__libc_unicode_readutf8@(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
							num_iter = new_num_iter;
						} else
@@pp_elif __SIZEOF_CHAR__ == 2@@
						char16_t const *new_num_iter;
						char32_t uni;
						new_num_iter = (char16_t const *)num_iter;
						uni = @__libc_unicode_readutf16@(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)${base}, &digit)) {
							num_iter = new_num_iter;
						} else
@@pp_else@@
						if (__libc_unicode_asdigit(ch, (uint8_t)${base}, &digit)) {
							++num_iter;
						} else
@@pp_endif@@
@@pp_endif@@
						{
							break;
						}
					} else {
						if (digit >= ${base})
							break;
						++num_iter;
					}
				}
				*${endptr} = (char *)num_iter;
			}
@@if SIGNED@@
			if (sign == '-')
				return @@yield("__INT" + BITS + "_MIN__")@@;
			return @@yield("__INT" + BITS + "_MAX__")@@;
@@else@@
			return @@yield("__UINT" + BITS + "_MAX__")@@;
@@endif@@
		}
	}
@@if SIGNED@@
	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}
@@endif@@

	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((${base} == 16 || ${base} == 2) && num_start > ${nptr}) {
			char const *nptr_ps = ${nptr};
			nptr_ps = strlstrip(nptr_ps);
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (${endptr})
					*${endptr} = (char *)nptr_ps + 1;
				if (${error})
					*${error} = 0;
				return 0;
			}
		}
		/* Empty number... */
		if (${error}) {
@@pp_ifdef ECANCELED@@
			*${error} = ECANCELED;
@@pp_else@@
			*${error} = 1;
@@pp_endif@@
		}
		/* Set endptr to the original `${nptr}' (_before_ leading spaces were skipped) */
		if (${endptr})
			*${endptr} = (char *)${nptr};
	} else {
@@if SIGNED@@
return_not_an_overflow:
@@endif@@
		if (${endptr}) {
			*${endptr} = (char *)num_iter;
			if (${error})
				*${error} = 0;
		} else if (${error}) {
			*${error} = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = strlstrip(num_iter);
				if (*num_iter) {
@@pp_ifdef EINVAL@@
					*${error} = EINVAL;
@@pp_else@@
					*${error} = 1;
@@pp_endif@@
				}
			}
		}
	}
	return result;
})]



/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
long strtol_r([[in]] char const *__restrict nptr,
              [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
              [[out_opt]] $errno_t *error) {
@@pp_if __SIZEOF_LONG__ >= 8@@
	return (long)strto64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG__ >= 4@@
	return (long)strto32_r(nptr, endptr, base, error);
@@pp_else@@
	s32 result = strto32_r(nptr, endptr, base, error);
	if (result > __LONG_MAX__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_MAX__;
	} else if (result < __LONG_MIN__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_MIN__;
	}
	return (long)result;
@@pp_endif@@
}

[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strtou32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strtou64_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
unsigned long strtoul_r([[in]] char const *__restrict nptr,
                        [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                        [[out_opt]] $errno_t *error) {
@@pp_if __SIZEOF_LONG__ >= 8@@
	return (unsigned long)strtou64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG__ >= 4@@
	return (unsigned long)strtou32_r(nptr, endptr, base, error);
@@pp_else@@
	u32 result = strtou32_r(nptr, endptr, base, error);
	if (result > __ULONG_MAX__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
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
[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strto32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
__LONGLONG strtoll_r([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                     [[out_opt]] $errno_t *error) {
@@pp_if __SIZEOF_LONG_LONG__ >= 8@@
	return (__LONGLONG)strto64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG_LONG__ >= 4@@
	return (__LONGLONG)strto32_r(nptr, endptr, base, error);
@@pp_else@@
	s32 result = strto32_r(nptr, endptr, base, error);
	if (result > __LONG_LONG_MAX__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_LONG_MAX__;
	} else if (result < __LONG_LONG_MIN__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __LONG_LONG_MIN__;
	}
	return (__LONGLONG)result;
@@pp_endif@@
}

[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strtou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strtou32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
__ULONGLONG strtoull_r([[in]] char const *__restrict nptr,
                       [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                       [[out_opt]] $errno_t *error) {
@@pp_if __SIZEOF_LONG_LONG__ >= 8@@
	return (__ULONGLONG)strtou64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_LONG_LONG__ >= 4@@
	return (__ULONGLONG)strtou32_r(nptr, endptr, base, error);
@@pp_else@@
	u32 result = strtou32_r(nptr, endptr, base, error);
	if (result > __ULONG_LONG_MAX__) {
		if (error) {
@@pp_ifdef ERANGE@@
			*error = ERANGE;
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
@@and store a pointer to the  end of the number in  `*endptr'.
@@
@@If `errno(3)' support is available, integer overflow is handled
@@by setting `errno=ERANGE', and returning the greatest or lowest
@@valid  integer (`U?INTn_(MIN|MAX))'. (though note that `endptr'
@@(if non-NULL) is still updated in this case!)
@@
@@Upon success, `errno' is left unchanged, and the integer repr
@@of the parsed number is returned. When no integer was parsed,
@@then `0' is returned, `*endptr' is set to `nptr', but `errno'
@@will not have been modified.
@@
@@@return: * :         Success: The parsed integer
@@@return: 0 :         [*endptr=nptr] error: Nothing was parsed
@@@return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
@@@return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent
[[if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 4), export_as("strtoumax")]]
[[kernel, leaf]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoumax...)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint32_t strtou32([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	uint32_t result;
	errno_t error;
	result = strtou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strtou32_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 4), export_as("strtoimax")]]
[[kernel, leaf, doc_alias("strtou32")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoimax...)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int32_t strto32([[in]] char const *__restrict nptr,
                 [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	int32_t result;
	errno_t error;
	result = strto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strto32_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

%#ifdef __UINT64_TYPE__
[[if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 8), export_as("strtoumax")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[kernel, leaf, doc_alias("strtou32"), alias("_strtoui64")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoumax...)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint64_t strtou64([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	uint64_t result;
	errno_t error;
	result = strtou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strtou64_r(nptr, endptr, base, NULL);
@@pp_endif@@
}

[[if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 8), export_as("strtoimax")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[kernel, leaf, doc_alias("strtou32"), alias("_strtoi64")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoimax...)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int64_t strto64([[in]] char const *__restrict nptr,
                 [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if defined(__libc_geterrno) && defined(ERANGE)@@
	int64_t result;
	errno_t error;
	result = strto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
@@pp_else@@
	return strto64_r(nptr, endptr, base, NULL);
@@pp_endif@@
}
%#endif /* __UINT64_TYPE__ */

%
%#ifdef __USE_XOPEN2K8
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), export_as("strtoumax_l"), dos_only_export_as("_strtoumax_l")]]
[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoumax_l...)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint32_t strtou32_l([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strtou32(nptr, endptr, base);
}

[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), export_as("strtoimax_l"), dos_only_export_as("_strtoimax_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias(CNL_strtol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias(CNL_strtoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_strtoimax_l...)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int32_t strto32_l([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strto32(nptr, endptr, base);
}

%#ifdef __UINT64_TYPE__
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), export_as("strtoumax_l"), dos_only_export_as("_strtoumax_l")]]
[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strtoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoumax_l...)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uint64_t strtou64_l([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strtou64(nptr, endptr, base);
}

[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), export_as("strtoimax_l"), dos_only_export_as("_strtoimax_l")]]
[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strtoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias(CNL_strtol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_strtoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_strtoimax_l...)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$int64_t strto64_l([[in]] char const *__restrict nptr,
                   [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base, $locale_t locale) {
	(void)locale;
	return strto64(nptr, endptr, base);
}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */


%[declare_kernel_export("_itoa_digits")]
%[declare_user_export("_itoa_lower_digits")]
%[declare_user_export("_itoa_upper_digits")]

%(auto_source){
#undef _itoa_digits
#undef libc__itoa_digits
DEFINE_PUBLIC_ALIAS(_itoa_digits, libc__itoa_digits);
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") char const libc__itoa_digits[101] =
"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define _itoa_digits libc__itoa_digits

/* For ABI compat, also export the lower/upper tables as dedicated symbols. (but only in user-space) */
#ifndef __KERNEL__
#undef libc__itoa_lower_digits
#undef libc__itoa_upper_digits
__asm__(".hidden libc__itoa_lower_digits\n"
        ".hidden libc__itoa_upper_digits\n"
        ".global libc__itoa_lower_digits\n"
        ".global libc__itoa_upper_digits\n"
        ".type   libc__itoa_lower_digits, \"object\"\n"
        ".type   libc__itoa_upper_digits, \"object\"\n"
        ".set    .Ldisp_itoa_lower_digits, libc__itoa_digits - 1\n"       /* Prevent size aliasing */
        ".set    libc__itoa_lower_digits, .Ldisp_itoa_lower_digits + 1\n" /* *ditto* */
        ".set    libc__itoa_upper_digits, libc__itoa_digits + 64\n"
        ".size   libc__itoa_lower_digits, 37\n"
        ".size   libc__itoa_upper_digits, 37\n");
#undef _itoa_lower_digits
#undef _itoa_upper_digits
DEFINE_PUBLIC_ALIAS(_itoa_lower_digits, libc__itoa_lower_digits);
DEFINE_PUBLIC_ALIAS(_itoa_upper_digits, libc__itoa_upper_digits);
#define _itoa_lower_digits (libc__itoa_digits + 0)
#define _itoa_upper_digits (libc__itoa_digits + 64)
#endif /* !__KERNEL__ */
}

%{

/* >> char itoa_digit(bool upper, uint8_t digit); */
#define itoa_digit(upper, digit) \
	_itoa_digits[(digit) + (!!(upper) << 6)]

/* >> char itoa_decimal(uint8_t digit);
 * Same as `itoa_digit()', but weak undefined behavior when `digit >= 10' */
#define itoa_decimal(digit) \
	(char)('0' + (digit))

/* >> char const _itoa_digits[101] =
 * >> "0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
 * >> "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // << offset from base: 64 */
#ifndef _itoa_digits
#ifdef __LOCAL_itoa_digits
#define _itoa_digits __LOCAL_itoa_digits
#elif defined(__CRT_HAVE__itoa_digits)
__CSDECLARE2(,char const _itoa_digits[101],_itoa_digits)
#define _itoa_digits _itoa_digits
#elif defined(__cplusplus)
#define _itoa_digits __LOCAL_itoa_digits_fp()
__ATTR_FORCEINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
char const *(__LOCAL_itoa_digits_fp)(void) {
	__ATTR_VISIBILITY("hidden")
	static __LOCAL_LIBC_CONST_DATA_SECTION(_itoa_digits) char const ___itoa_digits_p[101] =
	"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return ___itoa_digits_p;
}
#else /* ... */
__LOCAL_LIBC_CONST_DATA(_itoa_digits) char const _itoa_digits[101] =
"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define _itoa_digits _itoa_digits
#endif /* !... */
#endif /* !_itoa_digits */

/* >> char const _itoa_lower_digits[37] = "0123456789abcdefghijklmnopqrstuvwxyz"; */
#ifndef _itoa_lower_digits
#ifdef __LOCAL_itoa_lower_digits
#define _itoa_lower_digits __LOCAL_itoa_lower_digits
#elif defined(__CRT_HAVE__itoa_lower_digits)
__CSDECLARE2(,char const _itoa_lower_digits[37],_itoa_lower_digits)
#define _itoa_lower_digits _itoa_lower_digits
#else /* ... */
#define _itoa_lower_digits (_itoa_digits + 0)
#endif /* !... */
#endif /* !_itoa_lower_digits */

/* >> char const _itoa_upper_digits[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; */
#ifndef _itoa_upper_digits
#ifdef __LOCAL_itoa_upper_digits
#define _itoa_upper_digits __LOCAL_itoa_upper_digits
#elif defined(__CRT_HAVE__itoa_upper_digits)
__CSDECLARE2(,char const _itoa_upper_digits[37],_itoa_upper_digits)
#define _itoa_upper_digits _itoa_upper_digits
#else /* ... */
#define _itoa_upper_digits (_itoa_digits + 64)
#endif /* !... */
#endif /* !_itoa_upper_digits */

}

%#endif /* __USE_KOS */

%
%#if (defined(__USE_MISC) || defined(__USE_DOS) || \
%     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))


%#ifndef __NO_FPU
[[wunused, dos_only_export_alias("_gcvt")]]
[[impl_include("<hybrid/floatcore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *gcvt(double val, int ndigit, [[out]] char *buf) {
@@pp_ifndef     DBL_NDIGIT_MAX@@
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
int rand_r([[inout]] unsigned int *__restrict pseed) {
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
errno_t dos_ecvt_s([[out(? <= buflen)]] char *buf,
                   $size_t buflen, double val, int ndigit,
                   [[out]] int *__restrict decptr,
                   [[out]] int *__restrict sign);

[[decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("_fcvt_s")]]
errno_t dos_fcvt_s([[out(? <= buflen)]] char *buf,
                   $size_t buflen, double val, int ndigit,
                   [[out]] int *__restrict decptr,
                   [[out]] int *__restrict sign);

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
int ecvt_r(double val, int ndigit,
           [[out]] int *__restrict decptr,
           [[out]] int *__restrict sign,
           [[out(? <= len)]] char *__restrict buf, $size_t len) {
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

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
int fcvt_r(double val, int ndigit,
           [[out]] int *__restrict decptr,
           [[out]] int *__restrict sign,
           [[out(? <= len)]] char *__restrict buf, $size_t len) {
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
[[ldouble_variant_of("gcvt", ["_gcvt"])]]
char *qgcvt(__LONGDOUBLE val, int ndigit, [[out]] char *buf) {
@@pp_ifndef     LDBG_NDIGIT_MAX@@
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

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("ecvt_r", [])]]
int qecvt_r(__LONGDOUBLE val, int ndigit,
            [[out]] int *__restrict decptr,
            [[out]] int *__restrict sign,
            [[out(? <= len)]] char *__restrict buf, $size_t len) {
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

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("fcvt_r", [])]]
int qfcvt_r(__LONGDOUBLE val, int ndigit,
            [[out]] int *__restrict decptr,
            [[out]] int *__restrict sign,
            [[out(? <= len)]] char *__restrict buf, $size_t len) {
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


[[wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("ecvt", ["_ecvt"])]]
char *qecvt(__LONGDOUBLE val, int ndigit,
            [[out]] int *__restrict decptr,
            [[out]] int *__restrict sign) {
	@@static char qcvt_buf[32] = {0}@@
	if (qecvt_r(val, ndigit, decptr, sign,  qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}

[[wunused]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("fcvt", ["_fcvt"])]]
char *qfcvt(__LONGDOUBLE val, int ndigit,
            [[out]] int *__restrict decptr,
            [[out]] int *__restrict sign) {
	@@static char qcvt_buf[32] = {0}@@
	if (qfcvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

[[cp, guard, decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int getloadavg(double loadavg[], __STDC_INT_AS_SIZE_T nelem);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int drand48_r([[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] double *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int erand48_r([[nonnull]] unsigned short xsubi[3],
              [[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] double *__restrict result);
%#endif /* !__NO_FPU */

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int lrand48_r([[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] long *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int nrand48_r([[nonnull]] unsigned short xsubi[3],
              [[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] long *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int mrand48_r([[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] long *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int jrand48_r([[nonnull]] unsigned short xsubi[3],
              [[nonnull]] struct drand48_data *__restrict buffer,
              [[nonnull]] long *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int srand48_r(long seedval,
              [[nonnull]] struct drand48_data *buffer);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int seed48_r([[nonnull]] unsigned short seed16v[3],
             [[nonnull]] struct drand48_data *buffer);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
int lcong48_r([[nonnull]] unsigned short param[7],
              [[nonnull]] struct drand48_data *buffer);

[[decl_include("<hybrid/typecore.h>", "<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
[[export_as("__random_r")]] /* From Glibc 2.0.4 */
int random_r([[nonnull]] struct random_data *__restrict buf, [[nonnull]] $int32_t *__restrict result);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
[[export_as("__srandom_r")]] /* From Glibc 2.0.4 */
int srandom_r(unsigned int seed, [[nonnull]] struct random_data *buf);

[[decl_include("<bits/crt/random-data.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.random")]]
[[export_as("__initstate_r")]] /* From Glibc 2.0.4 */
int initstate_r(unsigned int seed,
                [[nonnull]] char *__restrict statebuf, $size_t statelen,
                [[nonnull]] struct random_data *__restrict buf);

[[decl_include("<bits/crt/random-data.h>")]]
[[section(".text.crt{|.dos}.random")]]
[[export_as("__setstate_r")]] /* From Glibc 2.0.4 */
int setstate_r([[nonnull]] char *__restrict statebuf,
               [[nonnull]] struct random_data *__restrict buf);


[[crt_dos_variant]]
[[crt_dos_impl_if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL))]]
[[export_alias("__on_exit")]]
[[section(".text.crt{|.dos}.sched.process")]]
int on_exit([[nonnull]] void (LIBCCALL *func)(int status, void *arg), void *arg);

[[requires_include("<libc/template/environ.h>")]]
[[userimpl, requires(defined(__LOCAL_environ))]]
[[section(".text.crt{|.dos}.fs.environ")]]
[[export_as("__clearenv")]] /* From Glibc 2.0.4 */
int clearenv(void) {
	__LOCAL_environ = NULL;
	return 0;
}


@@>> mkstemps(3), mkstemps64(3)
@@Replace the last 6 characters of `template_' (which are followed by exactly
@@`suffixlen' more characters that are left alone), which must be filled with
@@all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
@@random  characters such that the filename described by `template_' will not
@@already  exists. Then, create a new file  with `O_RDWR' and return the file
@@descriptor of that file.
@@@param: suffixlen: The #  of trailing  characters to-be  ignored
@@                   after the required 6 trailing 'X'-characters.
[[cp, guard, wunused]]
[[decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("mkstemps")]]
[[                                                                                                                                                     alias("mkstemps64")]]
[[requires_function(mkostemps)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkstemps([[inout]] char *template_, __STDC_INT_AS_SIZE_T suffixlen) {
	return mkostemps(template_, suffixlen, 0);
}

[[pure, wunused]]
[[section(".text.crt{|.dos}.utility.locale")]]
int rpmatch([[in]] char const *response) {
	char c = response[0];
	if (c == 'n' || c == 'N')
		return 0;
	if (c == 'y' || c == 'Y')
		return 1;
	return -1;
}

%[insert:extern(cfree)]

%#ifdef __USE_LARGEFILE64
[[cp, wunused, doc_alias("mkstemps")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[preferred_largefile64_variant_of(mkstemps)]]
[[requires_function(mkostemps64)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkstemps64([[inout]] char *template_, __STDC_INT_AS_SIZE_T suffixlen) {
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
int dos_putenv_s([[in]] char const *varname,
                 [[in]] char const *val);

[[crt_dos_variant, userimpl]]
[[requires_function(getenv, dos_putenv_s)]]
[[section(".text.crt{|.dos}.fs.environ")]]
int setenv([[in]] char const *varname,
           [[in]] char const *val, int replace) {
	if (!replace && getenv(varname))
		return 0;
	return dos_putenv_s(varname, val);
}

[[crt_dos_variant, userimpl]]
[[requires_function(putenv)]]
[[impl_include("<parts/malloca.h>")]]
[[section(".text.crt{|.dos}.fs.environ")]]
int unsetenv([[in]] char const *varname) {
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
#ifdef __LOCAL_MB_CUR_MAX
#define MB_CUR_MAX __LOCAL_MB_CUR_MAX
#elif defined(__mb_cur_max)
#define MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#elif defined(__ctype_get_mb_cur_max) || defined(____ctype_get_mb_cur_max_defined)
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(___mb_cur_max_func) || defined(_____mb_cur_max_func_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__p___mb_cur_max) || defined(____p___mb_cur_max_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___ctype_get_mb_cur_max)
#define ____ctype_get_mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(__CRT_HAVE____mb_cur_max_func)
#define _____mb_cur_max_func_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,___mb_cur_max_func,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__CRT_HAVE___p___mb_cur_max)
#define ____p___mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__p___mb_cur_max,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___mb_cur_max)
__CSDECLARE(,int,__mb_cur_max)
#define __mb_cur_max __mb_cur_max
#define MB_CUR_MAX   ((__SIZE_TYPE__)__mb_cur_max)
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
[[crt_dos_variant, dos_export_alias("_putenv")]]
[[section(".text.crt{|.dos}.fs.environ")]]
int putenv([[/*async*/inout]] char *string);
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

[[export_alias("__random")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("rand")]]
[[userimpl]]
[[section(".text.crt{|.dos}.random")]]
long random() {
	return (long)rand();
}

[[export_alias("__srandom")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("srand")]]
[[userimpl]]
[[section(".text.crt{|.dos}.random")]]
void srandom(unsigned int seed) {
	srand((long)seed);
}

[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__initstate")]]
[[section(".text.crt{|.dos}.random")]]
char *initstate(unsigned int seed, [[out(statelen)]] char *statebuf, $size_t statelen);

[[section(".text.crt{|.dos}.random")]]
[[export_alias("__setstate")]]
char *setstate([[nonnull]] char *statebuf);


@@>> l64a(3), a64l(3)
@@Convert between `long' and base-64 encoded integer strings.
[[nonnull, wunused]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
char *l64a(long n) {
	/* l64a_r() encodes 6 bytes from `n' into 1 character, followed
	 * by 1 trailing NUL-character. So we can can calculate the max
	 * required buffer size here, based on `sizeof(long)'! */
	@@static char l64a_buf[(((sizeof(long) * __CHAR_BIT__) + 5) / 6) + 1] = {0}@@
	l64a_r(n, l64a_buf, sizeof(l64a_buf));
	return l64a_buf;
}

[[pure, wunused, doc_alias("l64a")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
long a64l([[in]] char const *s) {
	unsigned long digit, result = 0;
	shift_t shift = 0;
	for (;; ++s) {
		char ch = *s;
		if ((unsigned char)ch <= '\0') {
			break;
		} else if ((unsigned char)ch <= '/') {
			digit = (unsigned long)(unsigned int)(ch - '.' + 0);
		} else if ((unsigned char)ch <= '9') {
			digit = (unsigned long)(unsigned int)(ch - '0' + 2);
		} else if ((unsigned char)ch <= 'Z') {
			digit = (unsigned long)(unsigned int)(ch - 'A' + 12);
		} else {
			digit = (unsigned long)(unsigned int)(ch - 'a' + 38);
		}
		digit <<= shift;
		result |= digit;
		shift += 6;
	}
	return result;
}

%[define(_POSIX_PATH_MAX = 256)] /* s.a. <limits.h> */

@@>> realpath(3)
@@Load the filesystem location of a given file handle.
@@This  function behaves similar to `readlink()', but will also function for
@@non-symlink paths, as well as always return an absolute (unambiguous) path
@@@param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
@@                  path, or NULL  to automatically `malloc()'ate  and return  a
@@                  buffer of sufficient size.
[[crt_dos_variant, cp, wunused]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(frealpathat))]]
[[impl_include("<asm/os/fcntl.h>", "<asm/os/limits.h>")]]
[[section(".text.crt{|.dos}.fs.property")]]
char *realpath([[in]] char const *filename, char *resolved) {
@@pp_if defined(__PATH_MAX) && __PATH_MAX != -1@@
	return frealpathat(__AT_FDCWD, filename, resolved, resolved ? __PATH_MAX : 0, 0);
@@pp_else@@
	return frealpathat(__AT_FDCWD, filename, resolved, resolved ? _POSIX_PATH_MAX : 0, 0);
@@pp_endif@@
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
%/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
% *       but it seems to be something that Glibc isn't implementing for some reason...
% *       Because of that, I didn't really know where to put this, so I put it in the
% *       same _SOURCE-block as its `realpath()' companion. */
@@>> frealpath(3)
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
@@      bytes  automatically allocated  in the heap,  ontop of which  you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
[[cp, wunused, crt_dos_variant]]
[[decl_include("<bits/types.h>")]]
[[requires_function(frealpath4)]]
[[section(".text.crt{|.dos}.fs.property")]]
char *frealpath([[fdarg]] $fd_t fd, [[out_opt]] char *resolved, $size_t buflen) {
	return frealpath4(fd, resolved, buflen, 0);
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

%
%#ifdef __USE_KOS
@@>> frealpath4(2)
@@Load the filesystem location of a given file handle.
@@This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
@@@param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
@@NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
@@      representation  mode. This means  that if the  path would have normally
@@      been printed as a unix path, it would instead be printed as a DOS path.
@@      Similarly, the reverse also applies.
@@NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
@@      bytes  automatically allocated  in the heap,  ontop of which  you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
[[cp, wunused, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
char *frealpath4([[fdarg]] $fd_t fd, [[out_opt/*(buflen)*/]] char *resolved, $size_t buflen, $atflag_t flags);

@@>> frealpathat(2)
@@Returns the absolute filesystem path for the specified file
@@When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
@@causing the path to  the symlink itself to  be printed. - Otherwise,  the
@@file pointed to by the symbolic link is printed.
@@NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
@@      representation  mode. This means  that if the  path would have normally
@@      been printed as a unix path, it would instead be printed as a DOS path.
@@      Similarly, the reverse also applies.
@@NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
@@      bytes  automatically allocated  in the heap,  ontop of which  you may also
@@      pass `0' for `buflen' to automatically determine the required buffer size.
@@@param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
@@@return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path
[[cp, wunused, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
char *frealpathat([[dirfd]] $fd_t dirfd, [[in]] char const *filename,
                  [[out_opt/*(buflen)*/]] char *resolved,
                  $size_t buflen, $atflag_t flags);
%#endif /* __USE_KOS */

%
%
%#if (defined(__USE_MISC) || \
%     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))

@@>> mktemp(3)
@@Badly designed version of  `mkstemp' that won't actually  create
@@the temporary file, meaning that by the time the caller tries to
@@create the  file themselves,  another process  may have  already
@@created it.
@@Also: when no  temporary filename  can be  created, rather  than
@@      returning something  sensible like  `NULL', this  function
@@      will instead set `template_' to an empty string, and still
@@      re-return it like it would if everything had worked!
[[nonnull, guard, dos_only_export_alias("_mktemp"), export_alias("__mktemp")]]
[[requires(($has_function(open) || $has_function(stat)) && $has_function(system_mktemp))]]
[[section(".text.crt{|.dos}.fs.utility")]]
char *mktemp([[inout]] char *template_) {
	if (system_mktemp(2, template_, 0, 0))
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
           [[out]] int *__restrict decptr,
           [[out]] int *__restrict sign) {
	@@static char qcvt_buf[32] = {0}@@
	if (ecvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}

[[wunused, dos_only_export_alias("_fcvt")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *fcvt(double val, int ndigit,
           [[out]] int *__restrict decptr,
           [[out]] int *__restrict sign) {
	@@static char qcvt_buf[32] = {0}@@
	if (fcvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
%#endif /* !__NO_FPU */

%#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */


%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%(auto_source){
#ifndef __KERNEL__
#undef suboptarg
INTDEF char *libc_suboptarg;
INTERN ATTR_SECTION(".bss.crt.application.getopt") char *libc_suboptarg = NULL;
DEFINE_PUBLIC_ALIAS(suboptarg, libc_suboptarg);
#define suboptarg GET_NOREL_GLOBAL(suboptarg)
#endif /* !__KERNEL__ */
}

@@>> getsubopt(3)
@@Parse a sequence of sub-options from `*optionp'.
@@
@@Sub-options look like this "rw,user=root drive=/dev/sda1"
@@Options may be separated by ',', ' ', or '\t' characters.
@@Both leading and trailing such characters are skipped.
@@
@@Note  that although KOS's implementation of this function only ever writes
@@to `suboptarg(3)' (meaning that it is technically thread-safe, so-long  as
@@no other piece of code ever reads from `suboptarg'), other implementations
@@_will_ in fact  perform reads  from `suboptarg', meaning  that a  portable
@@application must treat this function as thread-unsafe.
@@
@@Note that `suboptarg(3)' gets declared by <unistd.h> under `_NETBSD_SOURCE'
@@
@@@param: optionp: Pointer to sub-options that  have yet to be  parsed.
@@                 Note that the pointed-to string is modified in-place
@@                 in order to produce NUL-terminated strings.
@@@param: tokens:  A NULL-terminated  array of  recognized option  names.
@@                 The function searches this array for options specified
@@                 in `*optionp' (in the example above: "rw", "user"  and
@@                 "drive"), and returns the index of matched string,  or
@@                 `-1' with `*valuep'  set to the  whole sub-opt  option
@@                 string (e.g. "user=root") when  the option key is  not
@@                 part of this array.
@@@param: valuep:  Pointer to the value-portion of the matched sub-option.
@@                 When the sub-option name is not found in `tokens', this
@@                 pointer is set to  the entire sub-option string.  Else,
@@                 it is set to NULL when the end of `optionp' is reached,
@@                 or when the matched token doesn't have a value-portion.
@@@return: * : The return'th string from `tokens'  was matched. `*valuep' is  set
@@             to `NULL' when no `=' appeared in the sub-option, or to the string
@@             following `='  if it  was present  (e.g. "root"  in  "user=root").
@@             Additionally, the global variable `suboptarg'  is set to the  name
@@             of matched option (e.g. "user" in "root=user")
@@@return: -1: [*valuep == NULL] End of `optionp' has been reached (`suboptarg' is set to `NULL')
@@@return: -1: [*valuep != NULL] Unknown sub-option encountered (`*valuep' and
@@                               `suboptarg' are the whole sub-option  string)
[[guard, wunused]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/template/suboptarg.h>")]]
[[section(".text.crt{|.dos}.application.getopt")]]
int getsubopt([[inout_opt]] char **__restrict optionp,
              [[in]] char *const *__restrict tokens,
              [[out]] char **__restrict valuep) {
	unsigned int i;
	char *option, *nextopt, *eq;
	*valuep = NULL;
	if unlikely(!optionp)
		goto err_noopt;
	option = *optionp;
	if unlikely(!option)
		goto err_noopt;

	/* Skip leading whitespace and commas */
#define GETSUBOPT_ISSPACE(ch) (strchr(", \t", ch) != NULL)
	while (GETSUBOPT_ISSPACE(*option))
		++option;
	if unlikely(!*option)
		goto err_noopt;

	/* Save the starting pointer to the sub-option. */
@@pp_ifdef __LOCAL_suboptarg@@
	__LOCAL_suboptarg = option;
@@pp_endif@@

	/* Find the next option */
	nextopt = option;
	while (*nextopt != '\0' && !GETSUBOPT_ISSPACE(*nextopt))
		++nextopt;
	if (*nextopt != '\0')
		*nextopt++ = '\0';
	while (GETSUBOPT_ISSPACE(*nextopt))
		++nextopt;
	*optionp = nextopt;
#undef GETSUBOPT_ISSPACE

	/* Check if this option has a value-part */
	eq = strchr(option, '=');
	if (eq != NULL) {
		*eq++   = '\0';
		*valuep = eq;
	}

	/* Find the referenced token. */
	for (i = 0; tokens[i]; ++i) {
		if (strcmp(tokens[i], option) == 0)
			return (int)i;
	}

	/* Not found (return the whole `name[=value]' string) */
	*valuep = option;
	/* Restore the '=' since we want to return the whole string */
	if (eq != NULL)
		eq[-1] = '=';
	return -1;
err_noopt:
@@pp_ifdef __LOCAL_suboptarg@@
	__LOCAL_suboptarg = NULL;
@@pp_endif@@
	return -1;
}


@@>> mkstemp(3), mkstemp64(3)
@@Replace the last 6 characters of  `template_', which must be filled  with
@@all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
@@with random characters  such that the  filename described by  `template_'
@@will not already exists. Then, create a new file with `O_RDWR' and return
@@the file descriptor of that file.
[[cp, wunused, decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("mkstemp")]]
[[                                                                                                                                                     alias("mkstemp64")]]
[[requires_function(mkstemps)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkstemp([[inout]] char *template_) {
	return mkstemps(template_, 0);
}

%#ifdef __USE_LARGEFILE64
[[cp, wunused, doc_alias("mkstemp")]]
[[decl_include("<bits/types.h>")]]
[[preferred_largefile64_variant_of(mkstemp)]]
[[requires_function(mkstemps64)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkstemp64([[inout]] char *template_) {
	return mkstemps64(template_, 0);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN2K8
@@>> mkdtemp(3)
@@Replace the last 6 characters of `template_', which must be filled with
@@all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
@@with random characters such that the pathname described by  `template_'
@@will not already exists. Then, create a new directory with `mode=0700',
@@and re-return `template_' to indicate success.
@@On error, `NULL' will be returned, and the contents of `template_' are undefined.
[[cp, wunused]]
[[requires_function(mkdir, system_mktemp)]]
[[section(".text.crt{|.dos}.fs.utility")]]
char *mkdtemp([[inout]] char *template_) {
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
int grantpt([[fdarg]] $fd_t fd);

[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCSPTLCK))]]
[[section(".text.crt{|.dos}.io.tty")]]
int unlockpt([[fdarg]] $fd_t fd) {
	int action = 0;
	if (ioctl(fd, __TIOCSPTLCK, &action))
		return -1;
	return 0;
}

@@>> ptsname(3)
@@Returns the name of the PTY slave (Pseudo TTY slave)
@@associated   with   the   master   descriptor   `fd'
[[wunused, decl_include("<bits/types.h>")]]
[[crt_dos_variant, requires_function(ptsname_r)]]
[[section(".text.crt{|.dos}.io.tty")]]
char *ptsname([[fdarg]] $fd_t fd) {
@@pp_if $has_function(realloc)@@
	/* Buffer is typed as `void *' so it can be re-used for `wptsname(3)' */
	@@static void *ptsname_buf; [fini: free(ptsname_buf)]@@
	errno_t error;
@@pp_if $has_function(malloc_usable_size)@@
	size_t bufsize = malloc_usable_size(ptsname_buf) / sizeof(char);
@@pp_else@@
	size_t bufsize = ptsname_buf ? 64 : 0;
@@pp_endif@@
	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
	}
@@pp_ifdef ERANGE@@
again:
@@pp_endif@@
	error = ptsname_r(fd, (char *)ptsname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = strlen((char *)ptsname_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = realloc(ptsname_buf, retlen * sizeof(char));
			if likely(retbuf)
				ptsname_buf = retbuf;
		}
		return (char *)ptsname_buf;
	}
@@pp_ifdef ERANGE@@
	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
		goto again;
	}
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(ptsname_buf);
	ptsname_buf = NULL;
@@pp_endif@@
err:
	return NULL;
@@pp_else@@
	static char buf[64];
	if likely(ptsname_r(fd, buf, sizeof(buf)) == 0)
		return buf;
	return NULL;
@@pp_endif@@
}
%#endif /* __USE_XOPEN */

%
%#ifdef __USE_XOPEN2KXSI
[[cp, wunused, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
$fd_t posix_openpt($oflag_t oflags);
%#endif /* __USE_XOPEN2KXSI */


%#if defined(__USE_GNU) || defined(__USE_NETBSD)
@@Returns the name of the PTY slave (Pseudo TTY slave)
@@associated   with   the   master   descriptor   `fd'
[[crt_dos_variant, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
int ptsname_r([[fdarg]] $fd_t fd, [[out(? <= buflen)]] char *buf, $size_t buflen);
%#endif /* __USE_GNU || __USE_NETBSD */

%#ifdef __USE_GNU
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___),
  export_as("strtoimax_l"), dos_only_export_as("_strtoimax_l")]]
[[decl_include("<features.h>")]]
[[dos_only_export_alias("_strtol_l"), export_alias("__strtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoll_l...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4, strto32_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strto32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strto64_l)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
long strtol_l([[in]] char const *__restrict nptr,
              [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
              $locale_t locale) {
	(void)locale;
	return strtol(nptr, endptr, base);
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___),
  export_as("strtoumax_l"), dos_only_export_as("_strtoumax_l")]]
[[decl_include("<features.h>")]]
[[dos_only_export_alias("_strtoul_l"), export_alias("__strtoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_strtoull_l...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4, strtou32_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(strtou32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(strtou64_l)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
unsigned long strtoul_l([[in]] char const *__restrict nptr,
                        [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                        $locale_t locale) {
	(void)locale;
	return strtoul(nptr, endptr, base);
}

%#ifdef __LONGLONG
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___),
  export_as("strtoimax_l"), dos_only_export_as("_strtoimax_l")]]
[[decl_include("<features.h>")]]
[[dos_only_export_alias("_strtoll_l"), export_alias("__strtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(CNL_strtol_l...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, strto64_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4, strto32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strto32_l)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
__LONGLONG strtoll_l([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                     $locale_t locale) {
	(void)locale;
	return strtoll(nptr, endptr, base);
}

[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___),
  export_as("strtoumax_l"), dos_only_export_as("_strtoumax_l")]]
[[decl_include("<features.h>")]]
[[dos_only_export_alias("_strtoull_l"), export_alias("__strtoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(CNL_strtoul_l...)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, strtou64_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4, strtou32_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_strtoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(strtou32_l)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
__ULONGLONG strtoull_l([[in]] char const *__restrict nptr,
                       [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale) {
	(void)locale;
	return strtoull(nptr, endptr, base);
}
%#endif /* __LONGLONG */

%#ifndef __NO_FPU
[[dos_only_export_alias("_strtod_l"), export_alias("__strtod_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("strtold_l", "_strtold_l", "__strtold_l")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
double strtod_l([[in]] char const *__restrict nptr,
                [[out_opt]] char **endptr, $locale_t locale) {
	(void)locale;
	return strtod(nptr, endptr);
}

[[dos_only_export_alias("_strtof_l"), export_alias("__strtof_l")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
float strtof_l([[in]] char const *__restrict nptr,
               [[out_opt]] char **endptr, $locale_t locale) {
	(void)locale;
	return strtof(nptr, endptr);
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[dos_only_export_alias("_strtold_l"), export_alias("__strtold_l")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("strtod_l", ["_strtod_l", "__strtod_l"])]]
__LONGDOUBLE strtold_l([[in]] char const *__restrict nptr,
                       [[out_opt]] char **endptr, $locale_t locale) {
	(void)locale;
	return strtold(nptr, endptr);
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

@@>> secure_getenv(3)
@@Same as `getenv(3)', but always  return `NULL' if the  caller
@@is running in set-ugid mode (s.a. `__libc_enable_secure(3)').
[[crt_dos_variant, wunused]]
[[export_alias("__secure_getenv", "__libc_secure_getenv")]]
[[if($extended_include_prefix("<libc/template/__libc_enable_secure.h>")
     !defined(__LOCAL___libc_enable_secure)), alias("getenv")]]
[[if($extended_include_prefix("<libc/template/environ.h>", "<libc/template/__libc_enable_secure.h>")
     defined(__LOCAL_environ) && !defined(__LOCAL___libc_enable_secure)), bind_local_function(getenv)]]
[[requires_function(getenv)]]
[[impl_include("<libc/template/__libc_enable_secure.h>")]]
[[section(".text.crt{|.dos}.fs.environ")]]
char *secure_getenv([[in]] char const *varname) {
@@pp_ifdef __LOCAL___libc_enable_secure@@
	if (__LOCAL___libc_enable_secure)
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
@@pp_endif@@
	return getenv(varname);
}

[[cp, section(".text.crt{|.dos}.io.tty")]]
int getpt();

@@>> canonicalize_file_name(3)
@@Return the result of `realpath(filename)' as a `malloc()'-
@@allocated  buffer. Upon error, `NULL' is returned instead.
[[crt_dos_variant, cp, ATTR_MALLOC, wunused]]
[[section(".text.crt{|.dos}.fs.property")]]
char *canonicalize_file_name([[in]] char const *filename);

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
[[cp, static, wunused]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_include("<asm/os/oflags.h>")]]
[[impl_include("<asm/crt/stdio.h>")]] /* __TMP_MAX */
[[impl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timeval.h>")]]
[[impl_include("<bits/os/stat.h>")]]
[[impl_include("<hybrid/__overflow.h>")]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t system_mktemp(unsigned int what, [[inout]] char *template_,
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
	if unlikely(xloc < template_ || bcmpc(xloc, "XXXXXX", 6, sizeof(char)) != 0) {
@@pp_ifdef EINVAL@@
		return libc_seterrno(EINVAL);
@@pp_else@@
		return libc_seterrno(1);
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
			seed = (uint32_t)(tv.tv_sec) ^
			       (uint32_t)(tv.tv_sec >> 32) ^
			       (uint32_t)(tv.@tv_usec@ << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
@@pp_elif $has_function(gettimeofday)@@
		struct timeval tv;
		if (gettimeofday(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.tv_sec) ^
@@pp_if __SIZEOF_TIME_T__ > 4@@
			       (uint32_t)(tv.tv_sec >> 32) ^
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
@@pp_ifdef    O_RDWR@@
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
			result = libc_seterrno(EEXIST);
@@pp_else@@
			result = libc_seterrno(1);
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
%#endif /* __USE_GNU */

%
%#if defined(__USE_KOS) || defined(__USE_MISC) || defined(__USE_BSD)
%[insert:extern(reallocarray)]
%#endif /* __USE_KOS || __USE_MISC || __USE_BSD */

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
@@This  function is used  to implement `system(3)' and  `popen(3)', and may be
@@used to invoke the system interpreter.
@@This function only returns on failure (similar to exec(2)), and will never
@@return on success (since in that case, the calling program will have  been
@@replaced by the system shell)
@@The shell paths attempted by this function are system-dependent, but before any
@@of them are tested, this function will try to use `secure_getenv("SHELL")',  if
@@and only if that variable is defined and starts with a '/'-character.
[[cp, guard]]
[[requires_function(execl)]]
[[section(".text.crt{|.dos}.fs.exec.system")]]
int shexec([[in_opt]] char const *command) {
	static char const arg_sh[] = "sh";
	static char const arg__c[] = "-c";

@@pp_if $has_function(secure_getenv)@@
	/* Try to make use of $SHELL, if defined and an absolute path. */
	char const *environ_shell = secure_getenv("SHELL");
	if (environ_shell && *environ_shell == '/') {
		char const *environ_shell_sh;
		environ_shell_sh = strrchrnul(environ_shell, '/') + 1;
		execl(environ_shell, environ_shell_sh,
		      arg__c, command, (char *)NULL);
	}
@@pp_endif@@
	execl("/bin/sh", arg_sh, arg__c, command, (char *)NULL);
	execl("/bin/csh", "csh", arg__c, command, (char *)NULL);
	execl("/bin/bash", "bash", arg__c, command, (char *)NULL);
	return execl("/bin/busybox", arg_sh, arg__c, command, (char *)NULL);
}


@@>> abortf(3)
@@Same  as  `abort(3)',  but prior  to  doing what  `abort(3)'  does, this
@@function will print the specified message `format' to `syslog(LOG_ERR)',
@@as well as `STDERR_FILENO' (if  that file is opened  and a tty). In  the
@@message version that is printed  to `STDERR_FILENO', every line that  is
@@printed  is prefixed by  "{program_invocation_short_name}: ", and in the
@@syslog, every  line  is  prefixed  "[{program_invocation_short_name}] ".
@@
@@Additionally, in the stderr-version, `[foo]'  prefixes at the start  of
@@lines are replaced with `foo: ' (but are kept as-is in syslog messages)
[[noreturn, no_nothrow]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_ABORTF))]]
[[requires_include("<asm/os/stdio.h>", "<asm/os/syslog.h>", "<libc/template/program_invocation_name.h>")]]
[[requires(defined(__STDERR_FILENO) && defined(__LOG_ERR) && defined(__LOCAL_program_invocation_name) &&
           $has_function(isatty, writeall, syslog_printer, abort, format_vprintf))]]
[[dependency(isatty, writeall, syslog_printer, abort, format_vprintf, strchr)]]
[[section(".text.crt{|.dos}.assert")]]
[[impl_prefix(
@@push_namespace(local)@@
struct __vabortmsgf_data {
	char const *vamfd_ptag_str; /* [1..vamfd_ptag_len] Program tag. */
	size_t      vamfd_ptag_len; /* Length of the program tag. */
	bool        vamfd_isatty;   /* True if STDERR_FILENO is a tty. */
	bool        vamfd_at_sol;   /* True if at the start of a line. */
	bool        vamfd_rp_brk;   /* True if a closing ']' must be replaced with ": " on stderr */
};
__LOCAL_LIBC(@vabortmsgf_printer@) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC abortf_printer)(void *arg, char const *__restrict data, size_t datalen) {
	ssize_t result = (ssize_t)datalen;
	struct __vabortmsgf_data *cookie = (struct __vabortmsgf_data *)arg;
	while (datalen) {
		char tailchar;
		size_t block_len;
		if (cookie->vamfd_at_sol) {
			cookie->vamfd_at_sol = false;
			cookie->vamfd_rp_brk = false;
			(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
			(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
			(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, "] ", data[0] == '[' ? 1 : 2);
			if (cookie->vamfd_isatty) {
				(void)writeall(__STDERR_FILENO, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
				(void)writeall(__STDERR_FILENO, ": ", 2);
				if (data[0] == '[') {
					cookie->vamfd_rp_brk = true;
					(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
					++data;
					--datalen;
				}
			}
		}
		for (block_len = 0;;) {
			for (; block_len < datalen; ++block_len) {
				if (strchr("\r\n]", data[block_len]))
					break;
			}
			if (block_len >= datalen)
				break;
			if (data[block_len] != ']')
				break;
			if (cookie->vamfd_rp_brk)
				break;
		}
		tailchar = '\0';
		if (block_len < datalen)
			tailchar = data[block_len];
		if (tailchar == '\n') {
			cookie->vamfd_at_sol = true;
			++block_len;
		}
		(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, data, block_len);
		if (cookie->vamfd_isatty)
			(void)writeall(__STDERR_FILENO, data, block_len);
		data += block_len;
		datalen -= block_len;
		if (tailchar == ']') {
			(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, "]", 1);
			if (cookie->vamfd_isatty)
				(void)writeall(__STDERR_FILENO, ":", 1);
			++data;
			--datalen;
			cookie->vamfd_rp_brk = false;
		} else if (tailchar == '\r') {
			++data;
			--datalen;
			if (datalen && *data == '\n') {
				++data;
				--datalen;
			}
			(void)syslog_printer((void *)(uintptr_t)__LOG_ERR, "\n", 1);
			if (cookie->vamfd_isatty)
				(void)writeall(__STDERR_FILENO, "\n", 1);
			cookie->vamfd_at_sol = true;
		}
	}
	return result;
}
@@pop_namespace@@
)]]
void abortf([[in, format("printf")]] char const *format, ...) {
	struct __NAMESPACE_LOCAL_SYM __vabortmsgf_data data;
	va_list args;
	data.vamfd_ptag_str = program_invocation_name;
	if (data.vamfd_ptag_str == NULL)
		data.vamfd_ptag_str = "?";
	data.vamfd_ptag_len = strlen(data.vamfd_ptag_str);
	data.vamfd_isatty   = isatty(STDERR_FILENO) != 0;
	data.vamfd_at_sol   = true;
	data.vamfd_rp_brk   = false;
	va_start(args, format);
	(void)format_vprintf(&__NAMESPACE_LOCAL_SYM abortf_printer, &data, format, args);
	if (!data.vamfd_at_sol)
		(void)__NAMESPACE_LOCAL_SYM abortf_printer(&data, "\n", 1);
	va_end(args);
	abort();
}

%#endif /* __USE_KOS */

%
%#ifdef __USE_SOLARIS
%[default:section(".text.crt{|.dos}.solaris")]

%#ifndef __uid_t_defined
%#define __uid_t_defined
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

@@>> getexecname(3)
@@Returns the absolute filename of the main executable (s.a. `program_invocation_name')
[[crt_dos_variant, const, wunused, nothrow]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name))]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
char const *getexecname() {
	return __LOCAL_program_invocation_name;
}

@@>> fdwalk(3)
@@Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
@@If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
@@and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
@@invocations return 0, `fdwalk()' will also return 0.
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/features.h>")]]
[[requires(($has_function(fcntl) && defined(__F_NEXT)) ||
           (defined(__OS_HAVE_PROCFS_SELF_FD) && $has_function(opendir, readdir)))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>", "<hybrid/__overflow.h>")]]
[[impl_include("<bits/os/dirent.h>")]]
[[nothrow_cb_ncx, crt_dos_variant(callback(
	cook: struct { auto walk = walk; auto arg = arg; },
	wrap: ($cook *c, [[fdarg]] $fd_t fd): int { return (*c->walk)(c->arg, fd); },
	impl: fdwalk((int (LIBCCALL *)(void *, $fd_t))&$wrap, &$cook),
))]]
int fdwalk([[nonnull]] int (LIBCCALL *walk)(void *arg, $fd_t fd), void *arg) {
	int result = 0;
@@pp_ifdef __libc_geterrno@@
	errno_t saved_err;
@@pp_endif@@
@@pp_if $has_function(fcntl) && defined(__F_NEXT)@@
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
			(void)libc_seterrno(saved_err);
@@pp_endif@@
			break;
		}
		result = (*walk)(arg, fd);
		if (result != 0)
			break;
		if (__hybrid_overflow_sadd(fd, 1, &fd))
			break;
	}
@@pp_else@@
	/* Implementation alternative using `opendir("/proc/self/fd")' */
	DIR *dir = opendir("/proc/self/fd");
	if likely(dir) {
		struct dirent *ent;
@@pp_ifdef __libc_geterrno@@
		saved_err = __libc_geterrno();
@@pp_endif@@
		ent = readdir(dir);
		if (!ent) {
@@pp_ifdef __libc_geterrno@@
			(void)libc_seterrno(saved_err);
@@pp_endif@@
			break;
		}
		result = (*walk)(arg, atoi(ent->@d_name@));
	}
@@pp_if $has_function(closedir)@@
	closedir(dir);
@@pp_endif@@
@@pp_endif@@
	return result;
}

%[insert:function(getpassphrase = getpass)]

%#ifdef __LONGLONG
[[nonnull, wunused]]
char *lltostr(__LONGLONG value, [[out]] char *buf) {
	char *result;
	if (value < 0) {
		result    = ulltostr((__ULONGLONG)0 - value, buf);
		*--result = '-';
	} else {
		result = ulltostr((__ULONGLONG)value, buf);
	}
	return result;
}

[[nonnull, wunused]]
[[impl_include("<libc/template/itoa_digits.h>")]]
char *ulltostr(__ULONGLONG value, [[out]] char *buf) {
	do {
		*--buf = itoa_decimal(value % 10);
	} while ((value /= 10) != 0);
	return buf;
}
%#endif /* __LONGLONG */
%#endif /* __USE_SOLARIS */


%
%#ifdef __USE_BSD
@@>> reallocf(3)
@@Same as `realloc(3)',  but `mallptr'  is always freed  when `NULL'  is
@@returned (both error and the implementation-specific `realloc(ptr, 0)'
@@case; s.a. __REALLOC_ZERO_IS_NONNULL)
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
[[guard, decl_include("<hybrid/typecore.h>")]]
[[requires_function(realloc)]]
[[impl_include("<asm/crt/malloc.h>")]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
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
	 * was guessed incorrectly, so we know that the realloc
	 * can only fail when  returning `NULL' for a  non-zero
	 * size argument! */
	if unlikely(!result && num_bytes != 0)
@@pp_endif@@
	{
		free(mallptr);
	}
@@pp_endif@@
	return result;
}

@@>> recallocarray(3)
@@Same  as  `recallocv(mallptr, new_elem_count, elem_size)', but  also ensure  that when
@@`mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
@@is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory
@@block
[[guard, decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((3, 4))]]
[[requires_function(recallocv, calloc, malloc_usable_size)]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
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

@@>> freezero(3)
@@Same as  `free(mallptr)', but  also ensure  that the  memory  region
@@described by `mallptr...+=num_bytes' is explicitly freed to zero, or
@@immediately returned  to the  OS, rather  than being  left in  cache
@@while still containing its previous contents.
[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(free), guard]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
void freezero(void *mallptr, $size_t num_bytes) {
	if likely(mallptr) {
		explicit_bzero(mallptr, num_bytes);
		free(mallptr);
	}
}

%[default:section(".text.crt{|.dos}.bsd")]

//TODO:uint32_t arc4random(void);
//TODO:void arc4random_stir(void);
//TODO:void arc4random_buf(void *, size_t);
//TODO:uint32_t arc4random_uniform(uint32_t);
//TODO:void arc4random_addrandom(unsigned char *, int);


[[guard, wunused, decl_include("<hybrid/typecore.h>")]]
char *getbsize([[out]] int *headerlenp,
               [[out]] __LONGPTR_TYPE__ *blocksizep);
/* TODO: `getbsize()' can be implemented via magic! */

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


%[insert:extern(daemon)]

[[cp, guard, doc_alias("daemon")]]
[[decl_include("<bits/types.h>")]]
[[requires_function(daemon_setup, fchdir, dup2)]]
[[section(".text.crt{|.dos}.system.utility")]]
int daemonfd([[fdarg_opt]] $fd_t chdirfd, [[fdarg_opt]] $fd_t nullfd) {
	int error = daemon_setup();
	if likely(error == 0) {
		if (chdirfd != -1)
			(void)fchdir(chdirfd);
		if (nullfd != -1) {
			fd_t i;
			for (i = 0; i < 3; ++i) {
				if (nullfd != i)
					(void)dup2(nullfd, i);
			}
		}
	}
	return error;
}

//TODO:char *devname($dev_t dev, $mode_t mode);
//TODO:char *devname_r($dev_t dev, $mode_t mode, char *buf, __STDC_INT_AS_SIZE_T buflen);
//TODO:char *fdevname([[fdarg]] $fd_t fd);
//TODO:char *fdevname_r([[fdarg]] $fd_t fd, char *buf, __STDC_INT_AS_SIZE_T buflenint);
//TODO:$fd_t mkostempsat([[dirfd]] $fd_t dirfd, char *template_, __STDC_INT_AS_SIZE_T suffixlen, $oflag_t flags);
//TODO:void srandomdev(void);

%{

/* >> suboptarg(3)
 * Global variable that gets assigned by `getsubopt(3)' */
#ifndef suboptarg
#ifdef __LOCAL_suboptarg
#define suboptarg __LOCAL_suboptarg
#elif defined(__CRT_HAVE_suboptarg)
__CSDECLARE(,char *,suboptarg)
#define suboptarg suboptarg
#endif /* ... */
#endif /* !suboptarg */

}

@@>> l64a_r(3)
@@Reentrant variant of `l64a(3)'. Note that the max required buffer size
@@@param: buf:     Target buffer (with a size of `bufsize' bytes)
@@@param: bufsize: Buffer size (including a trailing NUL-character)
@@@return: 0 : Success
@@@return: -1: Buffer too small (`errno' was not modified)
[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
int l64a_r(long n, char *buf, __STDC_INT_AS_SIZE_T bufsize) {
	unsigned long un;
	/* Mapping from digit values --> base-64 characters. */
	static char const chrs[64] = {
		'.', '/', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', 'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};
	un = (unsigned long )n;
	while (bufsize) {
		--bufsize;
		if (!un) {
			/* Done! */
			*buf = '\0';
			return 0;
		}
		/* Encode 1 character. */
		*buf++ = chrs[un & 0x3f];
		un >>= 6;
	}
	return -1;

}


/* These are defined in <libc/template/program_invocation_name.h> */
%[define_replacement(program_invocation_name       = __LOCAL_program_invocation_name)]
%[define_replacement(program_invocation_short_name = __LOCAL_program_invocation_short_name)]


@@>> getprogname(3), setprogname(3)
[[guard, const, wunused, nothrow]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_short_name))]]
char const *getprogname(void) {
	return program_invocation_short_name;
}

[[guard, doc_alias("getprogname")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_short_name_p))]]
void setprogname(char const *name) {
	__LOCAL_program_invocation_short_name_p = (char *)name;
}


[[/*TODO:crt_dos_variant,*/ guard, nothrow_cb_ncx]]
[[decl_include("<hybrid/typecore.h>")]]
int heapsort([[inout(item_count * item_size)]] void *pbase, $size_t item_count, $size_t item_size,
             [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
	/* TODO: Actually do heap-sort! */
	qsort(pbase, item_count, item_size, compar);
	return 0;
}

[[/*TODO:crt_dos_variant,*/ guard, nothrow_cb_ncx]]
[[decl_include("<hybrid/typecore.h>")]]
int mergesort([[inout(item_count * item_size)]] void *pbase, $size_t item_count, $size_t item_size,
              [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
	/* TODO: Actually do merge-sort! */
	qsort(pbase, item_count, item_size, compar);
	return 0;
}


[[guard]]
int radixsort([[inout(item_count)]] unsigned char const **base, int item_count,
              [[in_opt]] unsigned char const table[256], unsigned endbyte);
/* TODO: `radixsort()' can be implemented via magic! */

[[guard]]
int sradixsort([[inout(item_count)]] unsigned char const **base, int item_count,
               [[in_opt]] unsigned char const table[256], unsigned endbyte);
/* TODO: `sradixsort()' can be implemented via magic! */




%
%#ifdef __LONGLONG

@@>> strtonum(3)
@@Similar to `strtoi()'  with `base=10',  but return  human-
@@readable error messages in `*p_errstr' on error (alongside
@@`return==0') (or `NULL' on success).
@@The following messages are defined:
@@  - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
@@  - "too small": Numeric value is too small (`ERANGE' && less than `lo')
@@  - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
@@@return: 0 : [*p_errstr != NULL] Error
@@@return: 0 : [*p_errstr == NULL] Success
@@@return: * : [*p_errstr == NULL] Success
[[guard, wunused]]
[[impl_include("<bits/types.h>", "<asm/os/errno.h>")]]
__LONGLONG strtonum([[in]] char const *nptr,
                    __LONGLONG lo, __LONGLONG hi,
                    [[out]] char const **p_errstr) {
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
%#endif /* __LONGLONG */
%#endif /* __USE_BSD */


%
%#if defined(__USE_GNU) || defined(__USE_BSD)
%{
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
}



@@>> qsort_r(3)
[[kernel, decl_include("<hybrid/typecore.h>")]]
[[alias("_quicksort")]]
[[if(!defined(__KERNEL__)), export_as("_quicksort")]] /* NOTE: `_quicksort' is the old libc4/5 name of this function. */
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.utility.stdlib")]]
[[nothrow_cb_ncx, crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(a, b, c->arg); },
	impl: qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void qsort_r([[inout(item_count * item_size)]] void *pbase, $size_t item_count, $size_t item_size,
             [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
             void *arg) {
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
				if ((*compar)(a, b, arg) <= 0)
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


@@>> mkostemp(3), mkostemp64(3)
@@Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
@@`suffixlen'  more  characters that  are left  alone), which  must be  filled with
@@all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
@@random  characters  such  that the  filename  described by  `template_'  will not
@@already exists. Then, create a new file with `O_RDWR | flags' and return the file
@@descriptor of that file.
@@@param: flags: Additional  flags  to pass  to `open(2)',
@@               but `O_ACCMODE' is always set to `O_RDWR'
[[wunused, no_crt_self_import]]
[[decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("mkostemp")]]
[[                                                                                                                                                     alias("mkostemp64")]]
[[requires_function(mkostemps)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkostemp([[inout]] char *template_, $oflag_t flags) {
	return mkostemps(template_, 0, flags);
}

[[wunused, no_crt_self_import]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("mkostemps")]]
[[                                                                                                                                                     alias("mkostemps64")]]
[[requires_function(open, system_mktemp)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkostemps([[inout]] char *template_,
                __STDC_INT_AS_SIZE_T suffixlen,
                $oflag_t flags) {
	return system_mktemp(0, template_, suffixlen, flags);
}

%#ifdef __USE_LARGEFILE64
[[wunused, doc_alias("mkostemp")]]
[[decl_include("<bits/types.h>")]]
[[preferred_largefile64_variant_of(mkostemp)]]
[[requires_function(mkostemps64)]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkostemp64([[inout]] char *template_, $oflag_t flags) {
	return mkostemps64(template_, 0, flags);
}

[[wunused, doc_alias("mkostemps")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[preferred_largefile64_variant_of(mkostemps)]]
[[requires_function(open, system_mktemp)]]
[[impl_include("<asm/os/oflags.h>")]]
[[section(".text.crt{|.dos}.fs.utility")]]
$fd_t mkostemps64([[inout]] char *template_,
                  __STDC_INT_AS_SIZE_T suffixlen,
                  $oflag_t flags) {
@@pp_ifdef O_LARGEFILE@@
	return system_mktemp(0, template_, suffixlen, flags | O_LARGEFILE);
@@pp_else@@
	return system_mktemp(0, template_, suffixlen, flags);
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU || __USE_BSD */



%
%#ifdef __USE_NETBSD
%{
#ifndef __dev_t_defined
#define __dev_t_defined
typedef __dev_t dev_t;
#endif /* !__dev_t_defined */
#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */
}

%[default:section(".text.crt{|.dos}.bsd")]

//TODO:void csetexpandtc(int);

@@>> devname(3), devname_r(3)
[[decl_include("<bits/types.h>")]]
[[alias("__devname50")]]
[[requires_function(devname_r)]]
char *devname(dev_t dev, mode_t type) {
@@pp_if $has_function(realloc)@@
	/* Buffer is typed as `void *' so it can be re-used for `wdevname(3)' */
	@@static void *devname_buf; [fini: free(devname_buf)]@@
	errno_t error;
@@pp_if $has_function(malloc_usable_size)@@
	size_t bufsize = malloc_usable_size(devname_buf) / sizeof(char);
@@pp_else@@
	size_t bufsize = devname_buf ? 64 : 0;
@@pp_endif@@
	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = realloc(devname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		devname_buf = newbuf;
	}
@@pp_ifdef ERANGE@@
again:
@@pp_endif@@
	error = devname_r(dev, type, (char *)devname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = strlen((char *)devname_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = realloc(devname_buf, retlen * sizeof(char));
			if likely(retbuf)
				devname_buf = retbuf;
		}
		return (char *)devname_buf;
	}
@@pp_ifdef ERANGE@@
	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = realloc(devname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		devname_buf = newbuf;
		goto again;
	}
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(devname_buf);
	devname_buf = NULL;
@@pp_endif@@
err:
	return NULL;
@@pp_else@@
	static char devname_buf[64];
	if likely(devname_r(dev, type, devname_buf, COMPILER_LENOF(devname_buf)) == 0)
		return devname_buf;
	return NULL;
@@pp_endif@@
}

[[doc_alias("devname")]]
[[decl_include("<bits/types.h>")]]
int devname_r(dev_t dev, mode_t type, [[out(? <= len)]] char *buf, $size_t len);


%{

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

}

@@>> humanize_number(3), dehumanize_number(3)
@@@param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
@@@param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES'
[[guard, decl_include("<hybrid/typecore.h>")]]
int humanize_number(char *buf, $size_t len, $int64_t bytes,
                    char const *suffix, int scale, int flags); /* TODO: Implement here */

[[guard, decl_include("<hybrid/typecore.h>"), doc_alias("humanize_number")]]
int dehumanize_number(char const *str, $int64_t *size); /* TODO: Implement here */


[[static]]
[[requires_include("<linux/prctl.h>")]]
[[requires((($has_function(prctl) && defined(@PR_SET_NAME@)) ||
            ($has_function(pthread_self, pthread_setname_np))) &&
            (defined(__TASK_COMM_LEN) || $has_function(vstrdupf)))]]
[[impl_include("<linux/prctl.h>")]]
void vsetproctitle([[in, format("printf")]] char const *format,
                   va_list args) {
	/* Load+fill a buffer for the fully qualified program name. */
@@pp_ifdef __TASK_COMM_LEN@@
	char namebuf[__TASK_COMM_LEN];
	vsnprintf(namebuf, __TASK_COMM_LEN - 1, format, args);
	namebuf[__TASK_COMM_LEN - 1] = '\0';
@@pp_else@@
	char *namebuf = vstrdupf(format, args);
	if unlikely(!namebuf)
		return;
@@pp_endif@@

	/* Tell the kernel about our new program name. */
@@pp_if $has_function(prctl) && defined(@PR_SET_NAME@)@@
	prctl(@PR_SET_NAME@, namebuf);
@@pp_else@@
	pthread_setname_np(pthread_self(), namebuf);
@@pp_endif@@

	/* Free the name buffer if it was allocated dynamically. */
@@pp_if !defined(__TASK_COMM_LEN) && $has_function(free)@@
	free(namebuf);
@@pp_endif@@
}

@@>> setproctitle(3)
@@Set the program comm name. S.a.:
@@ - pthread_setname_np(3)
@@ - prctl(PR_SET_NAME)
@@ - "/proc/self/comm"
[[guard]]
void setproctitle([[in, format("printf")]] char const *format, ...)
	%{printf("vsetproctitle")}


@@>> reallocarr(3)
@@Badly designed  alternative to  `reallocarray(3)'. Note  that
@@the given `ptr_p' argument is really typed as `void **ptr_p',
@@but for API compatibility  is defined as `void *ptr_p'.  This
@@function simply does:
@@>> *(void **)ptr_p = reallocarray(*(void **)ptr_p, elem_count, elem_size);
@@Though `*(void **)ptr_p' is only updated on success.
@@@return: 0 : Success (`*(void **)ptr_p' was updated)
@@@return: -1: Error (s.a. `errno'; `*(void **)ptr_p' is unchanged)
[[wunused, requires_function(reallocarray)]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
int reallocarr(void *ptr_p, $size_t elem_count, $size_t elem_size) {
	void **p_ptr = (void **)ptr_p;
	void *result;
	result = reallocarray(*p_ptr, elem_count, elem_size);
	if unlikely(!result)
		return -1;
	*p_ptr = result;
	return 0;
}

//TODO:ssize_t hmac(char const *, void const *, $size_t, void const *, $size_t, void *, $size_t);
//TODO:devmajor_t getdevmajor(char const *, mode_t);
//TODO:int getenv_r(char const *, char *, $size_t);
//TODO:void mi_vector_hash(void const *__restrict, $size_t, uint32_t, uint32_t[3]);

//TODO:$size_t shquote(char const *arg, char *buf, $size_t buflen);
//TODO:$size_t shquotev(int argc, char *const *argv, char *buf, $size_t buflen);


%#ifdef __LONGLONG
@@>> strsuftoll(3)
@@Same as `strsuftollx(3)', but if an error happens, make
@@use of `errx(3)' to terminate the program, rather  than
@@return to the caller.
[[wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsuftollx, errx)]]
[[impl_include("<asm/os/stdlib.h>")]]
__LONGLONG strsuftoll([[in]] char const *desc,
                      [[in]] char const *val,
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
[[decl_include("<hybrid/typecore.h>")]]
__LONGLONG strsuftollx([[in]] char const *desc,
                       [[in]] char const *val,
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
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBDCALL *_onexit_t)(void);
#endif /* !_ONEXIT_T_DEFINED */
#ifndef onexit_t
#define onexit_t _onexit_t
#endif /* !onexit_t */
}

%
%#ifndef _CRT_ERRNO_DEFINED
%#define _CRT_ERRNO_DEFINED 1
/* NOTE: Cygwin calls it `__errno()', and DOS calls it `_errno()' */
%#ifndef errno
%[insert:extern(__errno_location)]
%#ifdef ____errno_location_defined
%#define errno (*__errno_location())
%#endif /* ____errno_location_defined */
%#endif /* !errno */

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt.dos.errno_access")]]
errno_t _get_errno(errno_t *perr);

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt.dos.errno_access")]]
errno_t _set_errno(errno_t err);
%#endif /* !_CRT_ERRNO_DEFINED */



[[guard, const, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.errno")]]
$u32 *__doserrno();

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt.dos.errno")]]
errno_t _get_doserrno($u32 *perr);

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.errno")]]
errno_t _set_doserrno($u32 err);

%{
#ifdef ____doserrno_defined
#define _doserrno (*__doserrno())
#endif /* ____doserrno_defined */
}


%
%{
#ifndef _environ
#if defined(environ)
#define _environ environ
#elif defined(__environ)
#define _environ __environ
#elif defined(__LOCAL_environ)
#define _environ __LOCAL_environ
#elif defined(__CRT_HAVE_environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,environ)
#define environ  environ
#define _environ environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,_environ,environ)
#define _environ _environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__environ)
__CSDECLARE(,char **,_environ)
#define _environ _environ
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,__environ)
#define __environ __environ
#define _environ  __environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,_environ,__environ)
#define _environ _environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__environ_defined)
#define _environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define _environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW_NCX,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define _environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !_environ */

}


%{
#ifndef __argc
#ifdef __CRT_HAVE___argc
__CSDECLARE(,int,__argc)
#define __argc __argc
#else /* __CRT_HAVE___argc */
}
[[nonnull, guard, const, wunused, nothrow]]
[[section(".text.crt.dos.application.init")]]
int *__p___argc();
%{
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !__CRT_HAVE___argc */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__CSDECLARE(,char **,__argv)
#else /* __CRT_HAVE___argv */
}
[[nonnull, guard, const, wunused, nothrow]]
[[section(".text.crt.dos.application.init")]]
char ***__p___argv();
%{
#ifdef ____p___argv_defined
#define __argv (*__p___argv())
#endif /* ____p___argv_defined */
#endif /* !__CRT_HAVE___argv */
#endif /* !__argv */

#ifndef __wargv
#ifdef __CRT_HAVE___wargv
__CSDECLARE(,wchar_t **,__wargv)
#define __wargv __wargv
#else /* __CRT_HAVE___wargv */
}
[[nonnull, guard, const, wunused, nothrow, wchar]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.application.init")]]
wchar_t ***__p___wargv();
%{
#ifdef ____p___wargv_defined
#define __wargv (*__p___wargv())
#endif /* ____p___wargv_defined */
#endif /* !__CRT_HAVE___wargv */
#endif /* !__wargv */

#ifndef _wenviron
#ifdef __CRT_HAVE__wenviron
__CSDECLARE(,wchar_t **,_wenviron)
#define _wenviron _wenviron
#else /* __CRT_HAVE__wenviron */
}
[[nonnull, guard, const, wunused, nothrow, wchar]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
wchar_t ***__p__wenviron();
%{
#ifdef ____p__wenviron_defined
#define _wenviron (*__p__wenviron())
#endif /* ____p__wenviron_defined */
#endif /* !__CRT_HAVE__wenviron */
#endif /* !_wenviron */

#ifndef _wpgmptr
#ifdef __CRT_HAVE__wpgmptr
__CSDECLARE(,wchar_t *,_wpgmptr)
#define _wpgmptr _wpgmptr
#else /* __CRT_HAVE__wpgmptr */
}
[[nonnull, guard, const, wunused, nothrow, wchar]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.application.init")]]
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
#define _pgmptr program_invocation_name
#elif defined(__progname_full)
#define _pgmptr __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,_pgmptr,program_invocation_name)
#define _pgmptr _pgmptr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,program_invocation_name)
#define program_invocation_name program_invocation_name
#define _pgmptr                 program_invocation_name
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__pgmptr)
__CSDECLARE(,char *,_pgmptr)
#define _pgmptr _pgmptr
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,_pgmptr,__progname_full)
#define _pgmptr _pgmptr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,__progname_full)
#define __progname_full __progname_full
#define _pgmptr         __progname_full
#endif /* __NO_COMPILER_SREDIRECT */
#else /* ... */
}

@@Alias for argv[0], as passed to main()
[[nonnull, guard, const, wunused, nothrow]]
[[export_alias("__p_program_invocation_name")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name_p))]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[section(".text.crt.dos.application.init")]]
char **__p__pgmptr() {
	return &__LOCAL_program_invocation_name_p;
}

%{
#ifdef ____p__pgmptr_defined
#define _pgmptr (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !_pgmptr */
}

%
%#ifdef __USE_KOS
%{
#ifndef __initenv
#ifdef __CRT_HAVE___initenv
__CSDECLARE(,char **,__initenv)
#define __initenv __initenv
#else /* __CRT_HAVE___initenv */
}
@@Access to the initial environment block
[[nonnull, crt_dos_variant, guard, const, wunused, nothrow]]
[[section(".text.crt.dos.fs.environ")]]
char ***__p___initenv();
%{
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !__CRT_HAVE___initenv */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__CSDECLARE(,wchar_t **,__winitenv)
#define __winitenv __winitenv
#else /* __CRT_HAVE___winitenv */
}
@@Access to the initial environment block
[[nonnull, guard, const, wunused, nothrow, wchar]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
wchar_t ***__p___winitenv();
%{
#ifdef ____p___winitenv_defined
#define __winitenv (*__p___winitenv())
#endif /* ____p___winitenv_defined */
#endif /* !__CRT_HAVE___winitenv */
#endif /* !__winitenv */
}
%#endif /* __USE_KOS */

[[hidden]] __p___c16initenv(*) %{uchar16("__p___winitenv")}
[[hidden]] __p___c32initenv(*) %{uchar32("__p___winitenv")}

%
%#ifndef _countof
%#define _countof(a) __COMPILER_LENOF(a)
%#endif /* !_countof */


%[define(DEFINE_PURECALL_HANDLER =
#ifndef ___purecall_handler_defined
#define ___purecall_handler_defined
typedef void (__LIBDCALL *_purecall_handler)(void);
#endif /* !___purecall_handler_defined */
)]
%[define_replacement(_purecall_handler = _purecall_handler)]
%[define_type_class(_purecall_handler = "TP")]


%
%[insert:prefix(DEFINE_PURECALL_HANDLER)]

[[decl_prefix(DEFINE_PURECALL_HANDLER)]]
[[section(".text.crt.dos.errno")]]
_purecall_handler _set_purecall_handler(_purecall_handler handler);

[[decl_prefix(DEFINE_PURECALL_HANDLER)]]
[[section(".text.crt.dos.errno")]]
_purecall_handler _get_purecall_handler();

%[define(DEFINE_INVALID_PARAMETER_HANDLER =
@@pp_ifndef ___invalid_parameter_handler_defined@@
#define ___invalid_parameter_handler_defined
typedef void (__LIBDCALL *_invalid_parameter_handler)(__WCHAR16_TYPE__ const *__expr,
                                                      __WCHAR16_TYPE__ const *__func,
                                                      __WCHAR16_TYPE__ const *__file,
                                                      unsigned int __line,
                                                      __UINTPTR_TYPE__ __zero);
@@pp_endif@@
)]
%[define_replacement(_invalid_parameter_handler = _invalid_parameter_handler)]
%[define_type_class(_invalid_parameter_handler = "TP")]

%
%[insert:prefix(DEFINE_INVALID_PARAMETER_HANDLER)]

[[decl_prefix(DEFINE_INVALID_PARAMETER_HANDLER)]]
[[section(".text.crt.dos.errno")]]
_invalid_parameter_handler _set_invalid_parameter_handler(_invalid_parameter_handler handler);

[[decl_prefix(DEFINE_INVALID_PARAMETER_HANDLER)]]
[[section(".text.crt.dos.errno")]]
_invalid_parameter_handler _get_invalid_parameter_handler();


[[decl_include("<bits/types.h>")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_program_invocation_name))]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[section(".text.crt.dos.application.init")]]
errno_t _get_pgmptr([[out]] char **pvalue) {
	*pvalue = __LOCAL_program_invocation_name;
	return EOK;
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(__p__wpgmptr)]]
[[section(".text.crt.dos.wchar.application.init")]]
errno_t _get_wpgmptr([[out]] wchar_t **pvalue) {
	*pvalue = *__p__wpgmptr();
	return EOK;
}

%#ifdef __CRT_HAVE__fmode
%__CSDECLARE(,int,_fmode)
%#else /* ... */
[[guard, const, wunused, nothrow]]
[[section(".text.crt.dos.FILE.utility")]]
[[nonnull]] int *__p__fmode();
%#ifdef ____p__fmode_defined
%#define _fmode (*__p__fmode())
%#endif /* ____p__fmode_defined */
%#endif /* !... */

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.FILE.utility")]]
errno_t _set_fmode(int mode);

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.FILE.utility")]]
errno_t _get_fmode([[out]] int *pmode);

[[section(".text.crt.dos.errno")]]
unsigned int _set_abort_behavior(unsigned int flags, unsigned int mask);

%#ifdef __INT64_TYPE__
%#if defined(_MSC_VER) && defined(__LIBCCALL_IS_LIBDCALL)
%{
#ifndef _abs64
#define _abs64 _abs64
extern __ATTR_CONST __INT64_TYPE__ (__LIBDCALL _abs64)(__INT64_TYPE__ __x);
#pragma intrinsic(_abs64)
#endif /* !_abs64 */
}
%#else /* _MSC_VER && __LIBCCALL_IS_LIBDCALL */
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ == 8),
  export_as("imaxabs")]]
[[const, wunused, nothrow, decl_include("<hybrid/typecore.h>"), extern_inline]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       crt_intern_kos_alias("libc_abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), crt_intern_kos_alias("libc_llabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       alias("abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias(CNL_llabs...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias("imaxabs")]]
/* -- local functions don't exist for `abs(3)' & friends because of extern_inline -- */
/*[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       bind_local_function(abs)]]*/
/*[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(llabs)]]*/
/* -- */
[[section(".text.crt.dos.math.utility")]]
__INT64_TYPE__ _abs64(__INT64_TYPE__ x) {
	return x < 0 ? -x : x;
}
%#endif /* !_MSC_VER || !__LIBCCALL_IS_LIBDCALL */
%#endif /* __INT64_TYPE__ */


%#ifndef __NO_FPU
[[pure, wunused]]
[[section(".text.crt.dos.unicode.locale.convert")]]
double _atof_l([[in]] char const *__restrict nptr, $locale_t locale) {
	return strtod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

[[pure, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("_atol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("_atoll_l")]]
[[section(".text.crt.dos.unicode.locale.convert")]]
int _atoi_l([[in]] char const *__restrict nptr, $locale_t locale) {
	return (int)strtol_l(nptr, NULL, 10, locale);
}
[[pure, wunused]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, _atoi_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("_atoll_l")]]
[[section(".text.crt.dos.unicode.locale.convert")]]
long int _atol_l([[in]] char const *__restrict nptr, $locale_t locale) {
	return strtol_l(nptr, NULL, 10, locale);
}
%#ifdef __LONGLONG
[[pure, wunused]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _atol_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _atoi_l)]]
[[section(".text.crt.dos.unicode.locale.convert")]]
__LONGLONG _atoll_l([[in]] char const *__restrict nptr, $locale_t locale) {
	return strtoll_l(nptr, NULL, 10, locale);
}
%#endif /* __LONGLONG */

%
%{
#ifdef _MSC_VER
#ifndef _byteswap_ushort
extern unsigned short (_byteswap_ushort)(unsigned short __x);
#pragma intrinsic(_byteswap_ushort)
#define _byteswap_ushort _byteswap_ushort
#endif /* !_byteswap_ushort */
#ifndef _byteswap_ulong
extern unsigned long (_byteswap_ulong)(unsigned long __x);
#pragma intrinsic(_byteswap_ulong)
#define _byteswap_ulong _byteswap_ulong
#endif /* !_byteswap_ulong */
#ifndef _byteswap_uint64
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 __x);
#pragma intrinsic(_byteswap_uint64)
#define _byteswap_uint64 _byteswap_uint64
#endif /* !_byteswap_uint64 */
#else /* _MSC_VER */
}

[[const, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__byteswap.h>")]]
[[section(".text.crt.dos.math.utility")]]
$u16 _byteswap_ushort($u16 val) {
	return __hybrid_bswap16(val);
}

[[const, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__byteswap.h>")]]
[[section(".text.crt.dos.math.utility")]]
$u32 _byteswap_ulong($u32 val) {
	return __hybrid_bswap32(val);
}

%#ifdef __UINT64_TYPE__
[[const, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__byteswap.h>")]]
[[section(".text.crt.dos.math.utility")]]
$u64 _byteswap_uint64($u64 val) {
	return __hybrid_bswap64(val);
}
%#endif /* __UINT64_TYPE__ */

%{
#ifndef _byteswap_ushort
#define _byteswap_ushort(x) __hybrid_bswap16(x)
#endif /* !_byteswap_ushort */
#ifndef _byteswap_ulong
#define _byteswap_ulong(x)  __hybrid_bswap32(x)
#endif /* !_byteswap_ulong */
#ifdef __UINT64_TYPE__
#ifndef _byteswap_uint64
#define _byteswap_uint64(x) __hybrid_bswap64(x)
#endif /* !_byteswap_uint64 */
#endif /* __UINT64_TYPE__ */
}
%#endif /* !_MSC_VER */

%#ifdef __USE_DOS_SLIB
%{
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */
}

%
%#ifndef _CRT_ALGO_DEFINED
%#define _CRT_ALGO_DEFINED 1

%[define(DEFINE_INVOKE_COMPARE_HELPER_S =
@@pp_ifndef ____invoke_compare_helper_s_defined@@
#define ____invoke_compare_helper_s_defined
@@push_namespace(local)@@
struct __invoke_compare_helper_s_data {
	int (__LIBCCALL *__fun)(void *__arg, void const *__a, void const *__b);
	void            *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
@@pop_namespace@@
@@pp_endif@@
)]

[[guard, nothrow_cb_ncx, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER_S)]]
[[section(".text.crt.dos.utility")]]
[[crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(c->arg, a, b); },
	impl: bsearch_r(key, base, elem_count, elem_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void *bsearch_s([[in]] void const *key,
                [[in(elem_count * elem_size)]] void const *base, $size_t elem_count, $size_t elem_size,
                [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                void *arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return (void *)bsearch_r(key, base, elem_count, elem_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	                         &data);
}

[[guard, nothrow_cb_ncx]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER_S)]]
[[section(".text.crt.dos.utility")]]
[[crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(c->arg, a, b); },
	impl: qsort_r(base, elem_count, elem_size, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void qsort_s([[inout(elem_count * elem_size)]] void *base, $size_t elem_count, $size_t elem_size,
             [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
             void *arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	qsort_r(base, elem_count, elem_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	        &data);
}
%#endif  /* _CRT_ALGO_DEFINED */
%

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[requires_function(getenv)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.utility")]]
errno_t getenv_s([[out]] $size_t *preqsize,
                 [[out(? <= bufsize)]] char *buf, rsize_t bufsize,
                 [[in]] char const *varname) {
	size_t reqsize;
	char *name = getenv(varname);
	if (!name) {
		if (preqsize)
			*preqsize = 0;
		return EOK;
	}
	reqsize = (strlen(name) + 1) * sizeof(char);
	if (preqsize)
		*preqsize = reqsize;
	if (reqsize > bufsize) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	memcpy(buf, name, reqsize);
	return EOK;
}

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[requires_function(getenv, strdup)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.utility")]]
errno_t _dupenv_s([[out]] char **__restrict pbuf,
                  [[out]] $size_t *pbuflen,
                  [[in]] char const *varname) {
	char *name = getenv(varname);
	if (!name) {
		*pbuf    = NULL;
		*pbuflen = 0;
		return $EOK;
	}
	name = strdup(name);
	if (!name) {
@@pp_ifdef ENOMEM@@
		return $ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*pbuf    = name;
	*pbuflen = (strlen(name) + 1) * sizeof(char);
	return $EOK;
}
%#endif /* __USE_DOS_SLIB */

%[insert:function(_itoa = itoa)]
%[insert:function(_ltoa = ltoa)]
%[insert:function(_ultoa = ultoa)]


%[define_template(tpl_itoa<T, UT, val, buf, buflen, radix> =
	[[impl_include("<hybrid/typecore.h>")]]
	[[impl_include("<libc/errno.h>")]]
	[[impl_include("<libc/template/itoa_digits.h>")]]
{
@@exec global SIGNED = "${T}" != "${UT}";@@
	char *p;
	${UT} temp;
	if unlikely(${radix} < 2)
		${radix} = 2;
	if unlikely(${radix} > 36)
		${radix} = 36;
	p = ${buf};
@@if SIGNED@@
	if (${val} < 0) {
		if (!${buflen}--) {
@@pp_ifdef ERANGE@@
			return $ERANGE;
@@pp_else@@
			return 1;
@@pp_endif@@
		}
		*p++ = '-';
		${val} = -${val};
	}
@@endif@@
	temp = (${UT})${val};
	do {
		++p;
	} while ((temp /= (${UT})${radix}) != 0);
	if (${buflen} <= ($size_t)(p - ${buf})) {
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	temp = (${UT})${val};
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (${UT})${radix}];
	} while ((temp /= (${UT})${radix}) != 0);
	return 0;
})]


[[decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_ltoa_s")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_i64toa_s")]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _itoa_s(int val, [[out(? <= buflen)]] char *buf, $size_t buflen, int radix)
	%{template(tpl_itoa<int, unsigned int, val, buf, buflen, radix>)}

[[decl_include("<bits/types.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, "_itoa_s")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_i64toa_s")]]
[[crt_intern_dos_alias(libd__itoa_s)]]
[[section(".text.crt.dos.unicode.static.convert")]]
//[[crt_dos_variant({ impl: libd_errno_kos2dosinvoke_libclibc]); })]]
errno_t _ltoa_s(long val, [[out(? <= buflen)]] char *buf, $size_t buflen, int radix)
	%{template(tpl_itoa<long, unsigned long, val, buf, buflen, radix>)}

[[decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ui64toa_s")]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _ultoa_s(unsigned long val, [[out(? <= buflen)]] char *buf, $size_t buflen, int radix)
	%{template(tpl_itoa<unsigned long, unsigned long, val, buf, buflen, radix>)}


%
%#ifdef __UINT64_TYPE__
[[decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8, itoa)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_itoa")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, ltoa)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ltoa")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.unicode.static.convert")]]
char *_i64toa($s64 val, [[out]] char *buf, int radix) {
	_i64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, "ultoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ultoa")]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[impl_include("<hybrid/typecore.h>")]]
char *_ui64toa($u64 val, [[out]] char *buf, int radix) {
	_ui64toa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[decl_include("<bits/types.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, _ltoa_s)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8, _itoa_s)]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _i64toa_s($s64 val, [[out(? <= buflen)]] char *buf, $size_t buflen, int radix)
	%{template(tpl_itoa<__INT64_TYPE__, __UINT64_TYPE__, val, buf, buflen, radix>)}

[[decl_include("<bits/types.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, _ultoa_s)]]
[[section(".text.crt.dos.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _ui64toa_s($u64 val, [[out(? <= buflen)]] char *buf, $size_t buflen, int radix)
	%{template(tpl_itoa<__UINT64_TYPE__, __UINT64_TYPE__, val, buf, buflen, radix>)}


%[insert:function(_strtoi64 = strto64)]
%[insert:function(_strtoui64 = strtou64)]
%[insert:function(_strtoi64_l = strto64_l)]
%[insert:function(_strtoui64_l = strtou64_l)]


[[pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8, "atoi")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, "atol")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, "atoll")]]
[[section(".text.crt.dos.unicode.static.convert")]]
$s64 _atoi64([[in]] char const *__restrict nptr) {
	return strto64(nptr, NULL, 10);
}

[[pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8, _atoi_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8, _atol_l)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8, _atoll_l)]]
[[section(".text.crt.dos.unicode.static.convert")]]
$s64 _atoi64_l([[in]] char const *__restrict nptr, $locale_t locale) {
	return strto64_l(nptr, NULL, 10, locale);
}
%#endif /* __UINT64_TYPE__ */


[[pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrlen([[in]] char const *str) {
	size_t result = 0;
	while (unicode_readutf8((char const **)&str))
		++result;
	return result;
}

[[pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrnlen([[in(? <= maxlen)]] char const *str, $size_t maxlen) {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrlen_l([[in]] char const *str, $locale_t locale) {
	(void)locale;
	return _mbstrlen(str);
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstrnlen_l([[in(? <= maxlen)]] char const *str, $size_t maxlen, $locale_t locale) {
	(void)locale;
	return _mbstrnlen(str, maxlen);
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _mblen_l([[in(? <= maxlen)]] char const *str, $size_t maxlen, $locale_t locale) {
	(void)locale;
	return mblen(str, maxlen);
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _mbtowc_l(wchar_t *dst, char const *src,
              $size_t srclen, $locale_t locale) {
	(void)locale;
	return mbtowc(dst, src, srclen);
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _mbstowcs_l(wchar_t *dst, char const *src,
                    $size_t dstlen, $locale_t locale) {
	(void)locale;
	return mbstowcs(dst, src, dstlen);
}


[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<bits/types.h>", "<libc/errno.h>")]]
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
		return $EILSEQ;
@@pp_endif@@
	return $EOK;
}

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<bits/types.h>")]]
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
		return $EILSEQ;
@@pp_endif@@
	return $EOK;
}


[[decl_include("<bits/types.h>")]]
[[requires_function(rand)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.random")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t rand_s([[out]] unsigned int *__restrict randval) {
	if (!randval) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*randval = rand();
	return $EOK;
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
[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int _wctomb_l(char *buf, wchar_t wc, $locale_t locale) {
	(void)locale;
	return wctomb(buf, wc);
}

%
%#ifdef __USE_DOS_SLIB
[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(wctomb)]]
[[impl_include("<libc/errno.h>", "<libc/template/MB_CUR_MAX.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t wctomb_s([[out_opt]] int *presult,
                 [[out(? <= buflen)]] char *buf,
                 rsize_t buflen, wchar_t wc) {
	if (!presult || !buf) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
@@pp_ifdef __LOCAL_MB_CUR_MAX@@
	if (buflen < __LOCAL_MB_CUR_MAX)
@@pp_else@@
	if (buflen < 7)
@@pp_endif@@
	{
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*presult = wctomb(buf, wc);
	return $EOK;
}
%#endif /* __USE_DOS_SLIB */

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _wctomb_s_l([[out_opt]] int *presult,
                    [[out(? <= buflen)]] char *buf,
                    $size_t buflen, wchar_t wc,
                    $locale_t locale) {
	(void)locale;
	return wctomb_s(presult, buf, buflen, wc);
}

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t _wcstombs_s_l([[out_opt]] $size_t *presult,
                      [[out(? <= buflen)]] char *buf, $size_t buflen,
                      [[in(? <= maxlen)]] wchar_t const *src,
                      $size_t maxlen, $locale_t locale) {
	(void)locale;
	return wcstombs_s(presult, buf, buflen, src, maxlen);
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
$size_t _wcstombs_l([[out(? <= dstlen)]] char *dst,
                    [[in]] wchar_t const *src,
                    $size_t dstlen, $locale_t locale) {
	(void)locale;
	return wcstombs(dst, src, dstlen);
}

[[wchar, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
errno_t wcstombs_s([[out_opt]] $size_t *presult,
                   [[out(? <= buflen)]] char *buf, $size_t buflen,
                   [[in(? <= maxlen)]] wchar_t const *src, $size_t maxlen) {
	if (!presult || !buf || !src) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = wcstombs(buf, src, buflen);
	/* TODO: if (buflen < *presult) return ERANGE; */
	return $EOK;
}


%
%#define _CVTBUFSIZE   349
@@>> _fullpath(3)
@@s.a. `realpath(3)', `frealpathat(3)'
[[cp, wunused, crt_dos_variant]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(frealpathat))]]
[[impl_include("<asm/os/fcntl.h>")]]
[[section(".text.crt.dos.fs.utility")]]
char *_fullpath([[out(? <= buflen)]] char *buf, [[in]] char const *path, $size_t buflen) {
	return frealpathat(__AT_FDCWD, path, buf, buflen, 0);
}

%#ifndef __NO_FPU
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _ecvt_s([[out(? <= buflen)]] char *buf, $size_t buflen,
                double val, int ndigit,
                [[out]] int *__restrict decptr,
                [[out]] int *__restrict sign) {
	if (!buf || !decptr || !sign) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return $EOK;
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _fcvt_s([[out(? <= buflen)]] char *buf, $size_t buflen,
                double val, int ndigit,
                [[out]] int *__restrict decptr,
                [[out]] int *__restrict sign) {
	if (!buf || !decptr || !sign) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return $EOK;
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _gcvt_s([[out(? <= buflen)]] char *buf, $size_t buflen,
                double val, int ndigit) {
	int a, b;
	if (!buf) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return $EOK;
}


%[insert:function(_ecvt = ecvt)]
%[insert:function(_fcvt = fcvt)]
%[insert:function(_gcvt = gcvt)]

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atoflt([[out]] float *__restrict result,
            [[in]] char const *__restrict nptr) {
	*result = strtof(nptr, NULL);
	return 0;
}

[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atoflt_l([[out]] float *__restrict result,
              [[in]] char const *__restrict nptr, $locale_t locale) {
	*result = strtof_l(nptr, NULL, locale);
	return 0;
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atodbl([[out]] double *__restrict result,
            [[in]] char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtod(nptr, NULL);
	return 0;
}

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
int _atodbl_l([[out]] double *__restrict result,
              [[in]] char __KOS_FIXED_CONST *__restrict nptr, $locale_t locale) {
	*result = strtod_l(nptr, NULL, locale);
	return 0;
}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("_atodbl", [])]]
int _atoldbl([[out]] __LONGDOUBLE *__restrict result,
             [[in]] char __KOS_FIXED_CONST *__restrict nptr) {
	*result = strtold(nptr, NULL);
	return 0;
}

[[decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
[[ldouble_variant_of("_atodbl_l", [])]]
int _atoldbl_l([[out]] __LONGDOUBLE *__restrict result,
               [[in]] char __KOS_FIXED_CONST *__restrict nptr,
               $locale_t locale) {
	*result = strtold_l(nptr, NULL, locale);
	return 0;
}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */


%#if !__has_builtin(_rotl)
[[const, nothrow]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_lrotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotl64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), crt_intern_alias("_rotl64")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
unsigned int _rotl(unsigned int val, int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_rotl) */

%#if !__has_builtin(_rotr)
[[const, nothrow]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_lrotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotr64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), crt_intern_alias("_rotr64")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
unsigned int _rotr(unsigned int val, int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_rotr) */

%#if !__has_builtin(_lrotl)
[[const, nothrow]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_rotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_rotl64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), crt_intern_alias("_rotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), crt_intern_alias("_rotl64")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
unsigned long _lrotl(unsigned long val, int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_lrotl) */

%#if !__has_builtin(_lrotr)
[[const, nothrow]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_rotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_rotr64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), crt_intern_alias("_rotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), crt_intern_alias("_rotr64")]]
[[impl_include("<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
unsigned long _lrotr(unsigned long val, int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_lrotr) */

%#ifdef __UINT64_TYPE__
%#if !__has_builtin(_rotl64)
[[const, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_lrotl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotl")]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
$u64 _rotl64($u64 val, int shift) {
	return __hybrid_rol64(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_rotl64) */

%#if !__has_builtin(_rotr64)
[[const, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_lrotr")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_rotr")]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__rotate.h>")]]
[[section(".text.crt.dos.math.utility")]]
$u64 _rotr64($u64 val, int shift) {
	return __hybrid_ror64(val, (shift_t)(unsigned int)shift);
}
%#endif /* !__has_builtin(_rotr64) */
%#endif /* __UINT64_TYPE__ */

%
%#ifndef _CRT_PERROR_DEFINED
%#define _CRT_PERROR_DEFINED 1
%[insert:extern(perror)]
%#endif  /* _CRT_PERROR_DEFINED */

%
%[insert:function(_putenv = putenv)]
%[insert:function(_swab = swab)]

[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[requires_function(setenv)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.fs.environ")]]
errno_t _putenv_s(char const *varname, char const *val) {
	return setenv(varname, val, 1)
@@pp_ifdef EINVAL@@
	       ? __libc_geterrno_or($EINVAL)
@@pp_else@@
	       ? __libc_geterrno_or(1)
@@pp_endif@@
	       : 0;
}


[[cp]]
[[requires_function(_searchenv_s)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.fs.utility")]]
void _searchenv([[in]] char const *file,
                [[in]] char const *envvar,
                [[out]] char *__restrict resultpath) {
	_searchenv_s(file, envvar, resultpath, ($size_t)-1);
}

[[cp, decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.fs.utility")]]
errno_t _searchenv_s([[in]] char const *file,
                     [[in]] char const *envvar,
                     [[out(? <= resultpath_len)]] char *__restrict resultpath,
                     $size_t resultpath_len);

[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.fs.utility")]]
void _makepath([[out]] char *__restrict buf,
               [[in_opt]] char const *drive,
               [[in_opt]] char const *dir,
               [[in_opt]] char const *file,
               [[in_opt]] char const *ext) {
	_makepath_s(buf, ($size_t)-1, drive, dir, file, ext);
}

[[section(".text.crt.dos.fs.utility")]]
void _splitpath([[in]] char const *__restrict abspath,
                [[out_opt]] char *drive,
                [[out_opt]] char *dir,
                [[out_opt]] char *file,
                [[out_opt]] char *ext) {
	_splitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
[[section(".text.crt.dos.fs.utility")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _makepath_s([[out(? <= buflen)]] char *buf, $size_t buflen,
                    [[in_opt]] char const *drive,
                    [[in_opt]] char const *dir,
                    [[in_opt]] char const *file,
                    [[in_opt]] char const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char *)mempcpyc(buf, p, n, sizeof(char)); \
	}	__WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	}	__WHILE0
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
@@pp_ifdef EINVAL@@
	return $EINVAL;
@@pp_else@@
	return 1;
@@pp_endif@@
#undef path_putn
#undef path_putc
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
[[section(".text.crt.dos.fs.utility")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _splitpath_s([[in]] char const *__restrict abspath,
                     [[out(drivelen)]] char *drive, $size_t drivelen,
                     [[out(dirlen)]] char *dir, $size_t dirlen,
                     [[out(filelen)]] char *file, $size_t filelen,
                     [[out(extlen)]] char *ext, $size_t extlen) {
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
	return $EINVAL;
@@pp_else@@
	return 1;
@@pp_endif@@
err_range:
@@pp_ifdef ERANGE@@
	(void)libc_seterrno(ERANGE);
	return $ERANGE;
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

@@>> _sleep(3)
@@Sleep for `milli' milliseconds (1/1.000 seconds)
[[cp, decl_include("<hybrid/typecore.h>")]]
[[export_alias("__crtSleep")]]
[[requires_function(nanosleep)]]
[[impl_include("<bits/os/timespec.h>", "<libc/errno.h>")]]
void _sleep($uint32_t milli) {
	struct timespec ts;
	ts.@tv_sec@  = milli / 1000;
	ts.@tv_nsec@ = (milli % 1000) * 1000;
@@pp_if defined(__libc_geterrno) && defined(EINTR)@@
	{
		struct timespec rem;
		for (;;) {
			rem.@tv_sec@  = 0;
			rem.@tv_nsec@ = 0;
			if (nanosleep(&ts, &rem) == 0)
				break;
			if (__libc_geterrno() == EINTR)
				break;
			ts.@tv_sec@  = rem.@tv_sec@;
			ts.@tv_nsec@ = rem.@tv_nsec@;
		}
	}
@@pp_else@@
	nanosleep(&ts, NULL);
@@pp_endif@@
}

%
%{
#ifndef environ
#ifdef __CRT_HAVE_environ
__CSDECLARE(,char **,environ)
#define environ environ
#elif defined(_environ)
#define environ _environ
#elif defined(__environ)
#define environ __environ
#elif defined(__LOCAL_environ)
#define environ __LOCAL_environ
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ _environ
#define environ  _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,_environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,__environ)
#define __environ _environ
#define environ   __environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,__environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__environ_defined)
#define environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW_NCX,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char const **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !environ */
}

%
%[insert:extern(swab)]


%
%
%

[[dos_only_export_alias("_itoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("_ltoa", "ltoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_i64toa")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *itoa(int val, [[out]] char *buf, int radix) {
	_itoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[dos_only_export_alias("_ltoa")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__, "itoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_itoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_i64toa")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *ltoa(long val, [[out]] char *buf, int radix) {
	_ltoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

[[dos_only_export_alias("_ultoa")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_ui64toa")]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
char *ultoa(unsigned long val, [[out]] char *buf, int radix) {
	_ultoa_s(val, buf, ($size_t)-1, radix);
	return buf;
}

%[insert:function(_onexit = onexit)]

%[define_replacement(onexit_t = _onexit_t)]
%[define_replacement(_onexit_t = _onexit_t)]
%[define(DEFINE_ONEXIT_T =
@@pp_ifndef _ONEXIT_T_DEFINED@@
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBDCALL *_onexit_t)(void);
@@pp_endif@@
)]
%[define_type_class(onexit_t  = "TP")]
%[define_type_class(_onexit_t = "TP")]

[[decl_prefix(DEFINE_ONEXIT_T)]]
[[dos_only_export_alias("_onexit")]]
[[section(".text.crt.dos.sched.process")]]
onexit_t onexit(onexit_t func);




/************************************************************************/
/* The following functions are exposed in <corecrt_wstdlib.h>, but for  */
/* the sake of making their impl in user/stdlib.c easier, we define     */
/* them here, such that they can be defined alongside the other environ */
/* functions.                                                           */
/************************************************************************/
%[push_default]
%[default:ignore]

%[define_str2wcs_replacement(getenv       = _wgetenv)]
%[define_str2wcs_replacement(_putenv      = _wputenv)]
%[define_str2wcs_replacement(_putenv_s    = _wputenv_s)]
%[define_str2wcs_replacement(_searchenv_s = _wsearchenv_s)]

[[wchar, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
wchar_t *_wgetenv([[in]] wchar_t const *varname);

//[[wchar]]
//[[section(".text.crt.dos.wchar.fs.environ")]]
//_wgetenv(*) %{generate(str2wcs("getenv"))}

[[wchar]]
[[section(".text.crt.dos.wchar.fs.environ")]]
_wgetenv_s(*) %{generate(str2wcs("getenv_s"))}

[[wchar]]
[[section(".text.crt.dos.wchar.fs.environ")]]
_wdupenv_s(*) %{generate(str2wcs("_dupenv_s"))}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
int _wputenv([[inout]] wchar_t *string);

[[wchar, decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
errno_t _wputenv_s(wchar_t const *varname, wchar_t const *val);

[[cp, wchar, decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.wchar.fs.environ")]]
errno_t _wsearchenv_s([[in]] wchar_t const *file,
                      [[in]] wchar_t const *envvar,
                      [[out(resultpath_len)]] wchar_t *__restrict resultpath,
                      $size_t resultpath_len);


[[decl_include("<bits/types.h>")]]
[[requires_include("<libc/template/environ.h>")]]
[[requires(defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>")]]
[[section(".text.crt.dos.fs.environ")]]
errno_t _get_environ([[out]] char ***p_environ) {
	*p_environ = __LOCAL_environ;
	return 0;
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(__p__wenviron)]]
[[section(".text.crt.dos.wchar.fs.environ")]]
errno_t _get_wenviron([[out]] wchar_t ***p_wenviron) {
	*p_wenviron = *__p__wenviron();
	return 0;
}


%[pop_default]
/************************************************************************/
/************************************************************************/

%(user){
#ifdef __clang_tidy__
#define libc_malloc(num_bytes)           __builtin_malloc(num_bytes)
#define libc_calloc(count, num_bytes)    __builtin_calloc(count, num_bytes)
#define libc_realloc(mallptr, num_bytes) __builtin_realloc(mallptr, num_bytes)
#define libc_free(mallptr)               __builtin_free(mallptr)
#endif /* __clang_tidy__ */
}


%{

#endif /* __CC__ */
#endif /* __USE_DOS */

__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_malloc.h>  /* Include <malloc.h> instead */
#include <corecrt_search.h>  /* Include <search.h> instead */
#include <corecrt_wstdlib.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

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
