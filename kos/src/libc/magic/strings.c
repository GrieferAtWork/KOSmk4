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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/strings.h) */
/* (#) Portability: DJGPP         (/include/strings.h) */
/* (#) Portability: DragonFly BSD (/include/strings.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/strings.h) */
/* (#) Portability: FreeBSD       (/include/strings.h) */
/* (#) Portability: GNU C Library (/string/strings.h) */
/* (#) Portability: GNU Hurd      (/usr/include/strings.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/strings.h) */
/* (#) Portability: NetBSD        (/include/strings.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/strings.h) */
/* (#) Portability: OpenBSD       (/include/strings.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/strings.h) */
/* (#) Portability: diet libc     (/include/strings.h) */
/* (#) Portability: libc4/5       (/include/strings.h) */
/* (#) Portability: libc6         (/include/strings.h) */
/* (#) Portability: mintlib       (/include/strings.h) */
/* (#) Portability: musl libc     (/include/strings.h) */
/* (#) Portability: uClibc        (/include/strings.h) */
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */
}%[insert:prefix(
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
)]%{

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_NETBSD
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#endif /* __USE_NETBSD */

}
%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)

%[insert:extern(bcopy)]
%[insert:guarded_function(index = strchr)]
%[insert:guarded_function(rindex = strrchr)]

%
%#ifndef __bcmp_defined
%#define __bcmp_defined
%[insert:function(bcmp)]
%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(bcmp = bcmpc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */
%#endif /* !__bcmp_defined */

%
%#ifndef __bzero_defined
%#define __bzero_defined
%[insert:function(bzero)]
%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(bzero = bzeroc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */
%#endif /* !__bzero_defined */

%
%#ifdef __USE_STRING_BWLQ
%[insert:extern(bcmpb)]
%[insert:extern(bcmpw)]
%[insert:extern(bcmpl)]
%[insert:extern(bzerob)]
%[insert:extern(bzerow)]
%[insert:extern(bzerol)]
%#ifdef __UINT64_TYPE__
%[insert:extern(bcmpq)]
%[insert:extern(bzeroq)]
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */
%
%#ifdef __USE_KOS
%[insert:extern(bcmpc)]
%[insert:extern(bzeroc)]
%#endif /* __USE_KOS */
%#endif /* __USE_MISC || !__USE_XOPEN2K8 */
%
%[insert:extern(strcasecmp)]
%[insert:extern(strncasecmp)]
%
%#ifdef __USE_XOPEN2K8
%[insert:extern(strcasecmp_l)]
%[insert:extern(strncasecmp_l)]
%#endif /* __USE_XOPEN2K8 */
%


%
%#if defined(__USE_KOS) || defined(__USE_GNU) || defined(__USE_BSD)
@@>> explicit_bzero(3)
@@Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
@@away uses of this function when they (think) that clearing the  memory
@@wouldn't  have  any  visible side-effects  (though  those side-effects
@@may be a security-conscious application trying to wipe sensitive data)
[[decl_include("<hybrid/typecore.h>")]]
[[libc, nocrt, no_crt_self_import, guard]]
[[alias("bzero", "explicit_bzero", "__bzero")]]
void explicit_bzero([[out(n_bytes)]] void *dst, size_t n_bytes) {
	void *volatile vdst = dst;
	bzero(vdst, n_bytes);
}
%#endif /* __USE_KOS || __USE_GNU || __USE_BSD */


%{
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS) && defined(__HYBRID_PP_VA_OVERLOAD)
/* In C, we can use argument-count overload macros to implement these overloads! */
#ifdef __USE_MISC
#undef __PRIVATE_bcmp_3
#undef __PRIVATE_bcmp_4
#undef __PRIVATE_bzero_2
#undef __PRIVATE_bzero_3
#ifdef __USE_KOS
#define __PRIVATE_bcmp_4  bcmpc
#define __PRIVATE_bzero_3 bzeroc
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_bcmp_4  __libc_bcmpc
#define __PRIVATE_bzero_3 __libc_bzeroc
#endif /* !__USE_KOS */
#define __PRIVATE_bcmp_3  (bcmp)
#define __PRIVATE_bzero_2 (bzero)
#undef bcmp
#undef bzero
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define bcmp(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (__VA_ARGS__))(__VA_ARGS__)
#define bzero(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define bcmp(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (args))(args)
#define bzero(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (args))(args)
#endif /* ... */
#endif /* __USE_MISC */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS && __HYBRID_PP_VA_OVERLOAD */
}

%
%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8) || defined(__USE_XOPEN2K8XSI)
%[insert:extern(ffs)]
%{
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* shift_t FFS(INTEGER i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define ffs(i) __hybrid_ffs(i)
#endif /* !__USE_KOS */
}
%#endif /* __USE_MISC || !__USE_XOPEN2K8 || __USE_XOPEN2K8XSI */

%
%#if defined(__USE_NETBSD)
%[default:section(".text.crt{|.dos}.string.memory")]

@@>> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
@@POPulationCOUNT. Return the number of 1-bits in `i'
[[const, wunused, nothrow, crtbuiltin]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 4),                                        alias("popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),                                        alias("popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)), crt_intern_kos_alias("libc_popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)), crt_intern_kos_alias("libc_popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),                          alias("popcountl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__),                     alias("popcountll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 4),                                        bind_local_function(popcount32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),                                        bind_local_function(popcount64)]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_POPCOUNT))]]
unsigned int popcount(unsigned int i) {
	return __hybrid_popcount(i);
}

[[const, wunused, nothrow, crtbuiltin, doc_alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),                                        alias("popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                                        alias("popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)), crt_intern_kos_alias("libc_popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)), crt_intern_kos_alias("libc_popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),                           alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__),                     alias("popcountll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),                                        bind_local_function(popcount32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                                        bind_local_function(popcount64)]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_POPCOUNTL))]]
unsigned int popcountl(unsigned long i) {
	return __hybrid_popcount(i);
}

%#ifdef __LONGLONG
[[const, wunused, nothrow, crtbuiltin, doc_alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4),                                        alias("popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                                        alias("popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)), crt_intern_kos_alias("libc_popcount32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)), crt_intern_kos_alias("libc_popcount64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),                           alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),                          alias("popcountl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4),                                        bind_local_function(popcount32)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                                        bind_local_function(popcount64)]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_POPCOUNTLL))]]
unsigned int popcountll(__ULONGLONG i) {
	return __hybrid_popcount(i);
}
%#endif /* __LONGLONG */

[[decl_include("<hybrid/typecore.h>")]]
[[const, wunused, nothrow, crtbuiltin, doc_alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 4),       alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      alias("popcountl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("popcountll")]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_POPCOUNT32))]]
unsigned int popcount32($uint32_t i) {
	return __hybrid_popcount(i);
}

%#ifdef __UINT64_TYPE__
[[decl_include("<hybrid/typecore.h>")]]
[[const, wunused, nothrow, crtbuiltin, doc_alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       alias("popcount")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias("popcountl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("popcountll")]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_POPCOUNT64))]]
unsigned int popcount64($uint64_t i) {
	return __hybrid_popcount(i);
}
%#endif /* __UINT64_TYPE__ */


%{
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* shift_t POPCOUNT(unsigned Integer i):
 *     POPulationCOUNT
 *     Return the number of 1-bits in `i' */
#define popcount(i) __hybrid_popcount(i)
#endif /* !__USE_KOS */
}
%#endif /* __USE_NETBSD */


%{
#endif /* __CC__ */

__SYSDECL_END

}
