/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/string.h) */
/* (#) Portability: DJGPP         (/include/string.h) */
/* (#) Portability: DragonFly BSD (/include/string.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/string.h) */
/* (#) Portability: FreeBSD       (/include/string.h) */
/* (#) Portability: GNU C Library (/string/string.h) */
/* (#) Portability: GNU Hurd      (/usr/include/string.h) */
/* (#) Portability: MSVC          (/include/string.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/string.h) */
/* (#) Portability: NetBSD        (/include/string.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/string.h) */
/* (#) Portability: OpenBSD       (/include/string.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/string.h) */
/* (#) Portability: PDCLib        (/include/string.h) */
/* (#) Portability: Windows Kits  (/ucrt/string.h) */
/* (#) Portability: avr-libc      (/include/string.h) */
/* (#) Portability: diet libc     (/include/string.h) */
/* (#) Portability: libbsd        (/include/bsd/string.h) */
/* (#) Portability: libc4/5       (/include/string.h) */
/* (#) Portability: libc6         (/include/string.h) */
/* (#) Portability: libcmini      (/include/string.h) */
/* (#) Portability: mintlib       (/include/string.h) */
/* (#) Portability: musl libc     (/include/string.h) */
/* (#) Portability: uClibc        (/include/string.h) */
}

%[define_ccompat_header("cstring")]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]
%[default:section(".text.crt{|.dos}.string.memory")]


%(auto_source){
#include "../user/stdio.h"
#ifndef __KERNEL__
#include "../libc/errno.h"


/* Variants for `__USE_MEMMEM_EMPTY_NEEDLE_NULL' */
DEFINE_PUBLIC_ALIAS(memcasemem0_l, libc_memcasemem0_l);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.locale.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0_l)(void const *haystack, size_t haystacklen,
                                         void const *needle, size_t needlelen,
                                         locale_t locale) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memcasemem0, libc_memcasemem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.static.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0)(void const *haystack, size_t haystacklen,
                                       void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memmem0, libc_memmem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memmem0)(void const *haystack, size_t haystacklen,
                                   void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (bcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memrmem0, libc_memrmem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memrmem0)(void const *haystack, size_t haystacklen,
                                    void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= needlelen - 1;
	marker = *(uint8_t const *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (bcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}

#endif /* !__KERNEL__ */
}


%(auto_header){
/* Bind optimized variants  of various string  functions,
 * so those get used when building the automatic portions
 * of libc. */
#include <optimized/string.h>
/*[[[deemon
local funcs = {
	"mempmovedownc(dst, src, elem_count, elem_size)",
	"mempmovedownc(dst, src, elem_count, elem_size)",
	"memmovedownc(dst, src, elem_count, elem_size)",
	"mempmoveupc(dst, src, elem_count, elem_size)",
	"memmoveupc(dst, src, elem_count, elem_size)",
	"mempmovec(dst, src, elem_count, elem_size)",
	"memmovec(dst, src, elem_count, elem_size)",
	"mempcpyc(dst, src, elem_count, elem_size)",
	"memcpyc(dst, src, elem_count, elem_size)",
	"bcmpc(s1, s2, elem_count, elem_size)",
	"memcmpc(s1, s2, elem_count, elem_size)",
	"mempatq(dst, pattern, n_bytes)",
	"mempatl(dst, pattern, n_bytes)",
	"mempatw(dst, pattern, n_bytes)",
	"mempmove(dst, src, n_bytes)",
	"mempmovew(dst, src, n_words)",
	"mempmovel(dst, src, n_dwords)",
	"mempmoveq(dst, src, n_qwords)",
	"memmove(dst, src, n_bytes)",
	"memmovew(dst, src, n_words)",
	"memmovel(dst, src, n_dwords)",
	"memmoveq(dst, src, n_qwords)",
	"mempmoveup(dst, src, n_bytes)",
	"mempmoveupw(dst, src, n_words)",
	"mempmoveupl(dst, src, n_dwords)",
	"mempmoveupq(dst, src, n_qwords)",
	"memmoveup(dst, src, n_bytes)",
	"memmoveupw(dst, src, n_words)",
	"memmoveupl(dst, src, n_dwords)",
	"memmoveupq(dst, src, n_qwords)",
	"mempmovedown(dst, src, n_bytes)",
	"mempmovedownw(dst, src, n_words)",
	"mempmovedownl(dst, src, n_dwords)",
	"mempmovedownq(dst, src, n_qwords)",
	"memmovedown(dst, src, n_bytes)",
	"memmovedownw(dst, src, n_words)",
	"memmovedownl(dst, src, n_dwords)",
	"memmovedownq(dst, src, n_qwords)",
	"memcmp(s1, s2, n_bytes)",
	"memcmpw(s1, s2, n_words)",
	"memcmpl(s1, s2, n_dwords)",
	"memcmpq(s1, s2, n_qwords)",
	"memchr(haystack, needle, n_bytes)",
	"memchrw(haystack, needle, n_words)",
	"memchrl(haystack, needle, n_dwords)",
	"memchrq(haystack, needle, n_qwords)",
	"memrchr(haystack, needle, n_bytes)",
	"memrchrw(haystack, needle, n_words)",
	"memrchrl(haystack, needle, n_dwords)",
	"memrchrq(haystack, needle, n_qwords)",
	"memset(dst, byte, n_bytes)",
	"memsetw(dst, word, n_words)",
	"memsetl(dst, dword, n_dwords)",
	"memsetq(dst, qword, n_qwords)",
	"mempset(dst, byte, n_bytes)",
	"mempsetw(dst, word, n_words)",
	"mempsetl(dst, dword, n_dwords)",
	"mempsetq(dst, qword, n_qwords)",
	"bcmp(s1, s2, n_bytes)",
	"bcmpw(s1, s2, n_words)",
	"bcmpl(s1, s2, n_dwords)",
	"bcmpq(s1, s2, n_qwords)",
	"bzero(dst, n_bytes)",
	"bzerow(dst, n_words)",
	"bzerol(dst, n_dwords)",
	"bzeroq(dst, n_qwords)",
	"mempcpy(dst, src, n_bytes)",
	"mempcpyw(dst, src, n_words)",
	"mempcpyl(dst, src, n_dwords)",
	"mempcpyq(dst, src, n_qwords)",
	"memcpy(dst, src, n_bytes)",
	"memcpyw(dst, src, n_words)",
	"memcpyl(dst, src, n_dwords)",
	"memcpyq(dst, src, n_qwords)",
};
for (local f: funcs) {
	local i = f.index("(");
	local name = f[:i];
	local args = f[i:];
	print("#ifdef __fast_", name, "_defined");
	print("#define libc_", name, args, " (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(", name, "))", args);
	print("#endif /" "* __fast_", name, "_defined *" "/");
}
]]]*/
#ifdef __fast_mempmovedownc_defined
#define libc_mempmovedownc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(dst, src, elem_count, elem_size)
#endif /* __fast_mempmovedownc_defined */
#ifdef __fast_mempmovedownc_defined
#define libc_mempmovedownc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(dst, src, elem_count, elem_size)
#endif /* __fast_mempmovedownc_defined */
#ifdef __fast_memmovedownc_defined
#define libc_memmovedownc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(dst, src, elem_count, elem_size)
#endif /* __fast_memmovedownc_defined */
#ifdef __fast_mempmoveupc_defined
#define libc_mempmoveupc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(dst, src, elem_count, elem_size)
#endif /* __fast_mempmoveupc_defined */
#ifdef __fast_memmoveupc_defined
#define libc_memmoveupc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(dst, src, elem_count, elem_size)
#endif /* __fast_memmoveupc_defined */
#ifdef __fast_mempmovec_defined
#define libc_mempmovec(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(dst, src, elem_count, elem_size)
#endif /* __fast_mempmovec_defined */
#ifdef __fast_memmovec_defined
#define libc_memmovec(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(dst, src, elem_count, elem_size)
#endif /* __fast_memmovec_defined */
#ifdef __fast_mempcpyc_defined
#define libc_mempcpyc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(dst, src, elem_count, elem_size)
#endif /* __fast_mempcpyc_defined */
#ifdef __fast_memcpyc_defined
#define libc_memcpyc(dst, src, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(dst, src, elem_count, elem_size)
#endif /* __fast_memcpyc_defined */
#ifdef __fast_bcmpc_defined
#define libc_bcmpc(s1, s2, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(s1, s2, elem_count, elem_size)
#endif /* __fast_bcmpc_defined */
#ifdef __fast_memcmpc_defined
#define libc_memcmpc(s1, s2, elem_count, elem_size) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(s1, s2, elem_count, elem_size)
#endif /* __fast_memcmpc_defined */
#ifdef __fast_mempatq_defined
#define libc_mempatq(dst, pattern, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))(dst, pattern, n_bytes)
#endif /* __fast_mempatq_defined */
#ifdef __fast_mempatl_defined
#define libc_mempatl(dst, pattern, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))(dst, pattern, n_bytes)
#endif /* __fast_mempatl_defined */
#ifdef __fast_mempatw_defined
#define libc_mempatw(dst, pattern, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))(dst, pattern, n_bytes)
#endif /* __fast_mempatw_defined */
#ifdef __fast_mempmove_defined
#define libc_mempmove(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(dst, src, n_bytes)
#endif /* __fast_mempmove_defined */
#ifdef __fast_mempmovew_defined
#define libc_mempmovew(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(dst, src, n_words)
#endif /* __fast_mempmovew_defined */
#ifdef __fast_mempmovel_defined
#define libc_mempmovel(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(dst, src, n_dwords)
#endif /* __fast_mempmovel_defined */
#ifdef __fast_mempmoveq_defined
#define libc_mempmoveq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))(dst, src, n_qwords)
#endif /* __fast_mempmoveq_defined */
#ifdef __fast_memmove_defined
#define libc_memmove(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(dst, src, n_bytes)
#endif /* __fast_memmove_defined */
#ifdef __fast_memmovew_defined
#define libc_memmovew(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(dst, src, n_words)
#endif /* __fast_memmovew_defined */
#ifdef __fast_memmovel_defined
#define libc_memmovel(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(dst, src, n_dwords)
#endif /* __fast_memmovel_defined */
#ifdef __fast_memmoveq_defined
#define libc_memmoveq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))(dst, src, n_qwords)
#endif /* __fast_memmoveq_defined */
#ifdef __fast_mempmoveup_defined
#define libc_mempmoveup(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(dst, src, n_bytes)
#endif /* __fast_mempmoveup_defined */
#ifdef __fast_mempmoveupw_defined
#define libc_mempmoveupw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(dst, src, n_words)
#endif /* __fast_mempmoveupw_defined */
#ifdef __fast_mempmoveupl_defined
#define libc_mempmoveupl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(dst, src, n_dwords)
#endif /* __fast_mempmoveupl_defined */
#ifdef __fast_mempmoveupq_defined
#define libc_mempmoveupq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))(dst, src, n_qwords)
#endif /* __fast_mempmoveupq_defined */
#ifdef __fast_memmoveup_defined
#define libc_memmoveup(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(dst, src, n_bytes)
#endif /* __fast_memmoveup_defined */
#ifdef __fast_memmoveupw_defined
#define libc_memmoveupw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(dst, src, n_words)
#endif /* __fast_memmoveupw_defined */
#ifdef __fast_memmoveupl_defined
#define libc_memmoveupl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(dst, src, n_dwords)
#endif /* __fast_memmoveupl_defined */
#ifdef __fast_memmoveupq_defined
#define libc_memmoveupq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))(dst, src, n_qwords)
#endif /* __fast_memmoveupq_defined */
#ifdef __fast_mempmovedown_defined
#define libc_mempmovedown(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(dst, src, n_bytes)
#endif /* __fast_mempmovedown_defined */
#ifdef __fast_mempmovedownw_defined
#define libc_mempmovedownw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(dst, src, n_words)
#endif /* __fast_mempmovedownw_defined */
#ifdef __fast_mempmovedownl_defined
#define libc_mempmovedownl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(dst, src, n_dwords)
#endif /* __fast_mempmovedownl_defined */
#ifdef __fast_mempmovedownq_defined
#define libc_mempmovedownq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))(dst, src, n_qwords)
#endif /* __fast_mempmovedownq_defined */
#ifdef __fast_memmovedown_defined
#define libc_memmovedown(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(dst, src, n_bytes)
#endif /* __fast_memmovedown_defined */
#ifdef __fast_memmovedownw_defined
#define libc_memmovedownw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(dst, src, n_words)
#endif /* __fast_memmovedownw_defined */
#ifdef __fast_memmovedownl_defined
#define libc_memmovedownl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(dst, src, n_dwords)
#endif /* __fast_memmovedownl_defined */
#ifdef __fast_memmovedownq_defined
#define libc_memmovedownq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))(dst, src, n_qwords)
#endif /* __fast_memmovedownq_defined */
#ifdef __fast_memcmp_defined
#define libc_memcmp(s1, s2, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(s1, s2, n_bytes)
#endif /* __fast_memcmp_defined */
#ifdef __fast_memcmpw_defined
#define libc_memcmpw(s1, s2, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(s1, s2, n_words)
#endif /* __fast_memcmpw_defined */
#ifdef __fast_memcmpl_defined
#define libc_memcmpl(s1, s2, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(s1, s2, n_dwords)
#endif /* __fast_memcmpl_defined */
#ifdef __fast_memcmpq_defined
#define libc_memcmpq(s1, s2, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(s1, s2, n_qwords)
#endif /* __fast_memcmpq_defined */
#ifdef __fast_memchr_defined
#define libc_memchr(haystack, needle, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(haystack, needle, n_bytes)
#endif /* __fast_memchr_defined */
#ifdef __fast_memchrw_defined
#define libc_memchrw(haystack, needle, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(haystack, needle, n_words)
#endif /* __fast_memchrw_defined */
#ifdef __fast_memchrl_defined
#define libc_memchrl(haystack, needle, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(haystack, needle, n_dwords)
#endif /* __fast_memchrl_defined */
#ifdef __fast_memchrq_defined
#define libc_memchrq(haystack, needle, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(haystack, needle, n_qwords)
#endif /* __fast_memchrq_defined */
#ifdef __fast_memrchr_defined
#define libc_memrchr(haystack, needle, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(haystack, needle, n_bytes)
#endif /* __fast_memrchr_defined */
#ifdef __fast_memrchrw_defined
#define libc_memrchrw(haystack, needle, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(haystack, needle, n_words)
#endif /* __fast_memrchrw_defined */
#ifdef __fast_memrchrl_defined
#define libc_memrchrl(haystack, needle, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(haystack, needle, n_dwords)
#endif /* __fast_memrchrl_defined */
#ifdef __fast_memrchrq_defined
#define libc_memrchrq(haystack, needle, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(haystack, needle, n_qwords)
#endif /* __fast_memrchrq_defined */
#ifdef __fast_memset_defined
#define libc_memset(dst, byte, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(dst, byte, n_bytes)
#endif /* __fast_memset_defined */
#ifdef __fast_memsetw_defined
#define libc_memsetw(dst, word, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(dst, word, n_words)
#endif /* __fast_memsetw_defined */
#ifdef __fast_memsetl_defined
#define libc_memsetl(dst, dword, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(dst, dword, n_dwords)
#endif /* __fast_memsetl_defined */
#ifdef __fast_memsetq_defined
#define libc_memsetq(dst, qword, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(dst, qword, n_qwords)
#endif /* __fast_memsetq_defined */
#ifdef __fast_mempset_defined
#define libc_mempset(dst, byte, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(dst, byte, n_bytes)
#endif /* __fast_mempset_defined */
#ifdef __fast_mempsetw_defined
#define libc_mempsetw(dst, word, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(dst, word, n_words)
#endif /* __fast_mempsetw_defined */
#ifdef __fast_mempsetl_defined
#define libc_mempsetl(dst, dword, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(dst, dword, n_dwords)
#endif /* __fast_mempsetl_defined */
#ifdef __fast_mempsetq_defined
#define libc_mempsetq(dst, qword, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))(dst, qword, n_qwords)
#endif /* __fast_mempsetq_defined */
#ifdef __fast_bcmp_defined
#define libc_bcmp(s1, s2, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(s1, s2, n_bytes)
#endif /* __fast_bcmp_defined */
#ifdef __fast_bcmpw_defined
#define libc_bcmpw(s1, s2, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(s1, s2, n_words)
#endif /* __fast_bcmpw_defined */
#ifdef __fast_bcmpl_defined
#define libc_bcmpl(s1, s2, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(s1, s2, n_dwords)
#endif /* __fast_bcmpl_defined */
#ifdef __fast_bcmpq_defined
#define libc_bcmpq(s1, s2, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(s1, s2, n_qwords)
#endif /* __fast_bcmpq_defined */
#ifdef __fast_bzero_defined
#define libc_bzero(dst, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(dst, n_bytes)
#endif /* __fast_bzero_defined */
#ifdef __fast_bzerow_defined
#define libc_bzerow(dst, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(dst, n_words)
#endif /* __fast_bzerow_defined */
#ifdef __fast_bzerol_defined
#define libc_bzerol(dst, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(dst, n_dwords)
#endif /* __fast_bzerol_defined */
#ifdef __fast_bzeroq_defined
#define libc_bzeroq(dst, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(dst, n_qwords)
#endif /* __fast_bzeroq_defined */
#ifdef __fast_mempcpy_defined
#define libc_mempcpy(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(dst, src, n_bytes)
#endif /* __fast_mempcpy_defined */
#ifdef __fast_mempcpyw_defined
#define libc_mempcpyw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(dst, src, n_words)
#endif /* __fast_mempcpyw_defined */
#ifdef __fast_mempcpyl_defined
#define libc_mempcpyl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(dst, src, n_dwords)
#endif /* __fast_mempcpyl_defined */
#ifdef __fast_mempcpyq_defined
#define libc_mempcpyq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))(dst, src, n_qwords)
#endif /* __fast_mempcpyq_defined */
#ifdef __fast_memcpy_defined
#define libc_memcpy(dst, src, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(dst, src, n_bytes)
#endif /* __fast_memcpy_defined */
#ifdef __fast_memcpyw_defined
#define libc_memcpyw(dst, src, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(dst, src, n_words)
#endif /* __fast_memcpyw_defined */
#ifdef __fast_memcpyl_defined
#define libc_memcpyl(dst, src, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(dst, src, n_dwords)
#endif /* __fast_memcpyl_defined */
#ifdef __fast_memcpyq_defined
#define libc_memcpyq(dst, src, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))(dst, src, n_qwords)
#endif /* __fast_memcpyq_defined */
/*[[[end]]]*/


#ifdef __KERNEL__
/* The kernel isn't exporting  these functions, but they're  still
 * used by a couple of function that _are_ exported by the kernel! */
#ifndef libc_mempmovedownc
#define libc_mempmovedownc(dst, src, elem_count, elem_size) libc_mempmovedown(dst, src, (elem_count) * (elem_size))
#endif /* !libc_mempmovedownc */
#ifndef libc_memmovedownc
#define libc_memmovedownc(dst, src, elem_count, elem_size) libc_memmovedown(dst, src, (elem_count) * (elem_size))
#endif /* !libc_memmovedownc */
#ifndef libc_mempmoveupc
#define libc_mempmoveupc(dst, src, elem_count, elem_size) libc_mempmoveup(dst, src, (elem_count) * (elem_size))
#endif /* !libc_mempmoveupc */
#ifndef libc_memmoveupc
#define libc_memmoveupc(dst, src, elem_count, elem_size) libc_memmoveup(dst, src, (elem_count) * (elem_size))
#endif /* !libc_memmoveupc */
#ifndef libc_mempmovec
#define libc_mempmovec(dst, src, elem_count, elem_size) libc_mempmove(dst, src, (elem_count) * (elem_size))
#endif /* !libc_mempmovec */
#ifndef libc_memmovec
#define libc_memmovec(dst, src, elem_count, elem_size) libc_memmove(dst, src, (elem_count) * (elem_size))
#endif /* !libc_memmovec */
#ifndef libc_mempcpyc
#define libc_mempcpyc(dst, src, elem_count, elem_size) libc_mempcpy(dst, src, (elem_count) * (elem_size))
#endif /* !libc_mempcpyc */
#ifndef libc_memcpyc
#define libc_memcpyc(dst, src, elem_count, elem_size) libc_memcpy(dst, src, (elem_count) * (elem_size))
#endif /* !libc_memcpyc */
#endif /* __KERNEL__ */

}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#if defined(__USE_KOS) || defined(__USE_GNU)
#include <hybrid/__alloca.h>
#endif /* __USE_KOS || __USE_GNU */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_DOS
#include <libc/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */
#ifdef __USE_STRING_OVERLOADS
#include <hybrid/pp/__va_nargs.h>
#endif /* __USE_STRING_OVERLOADS */
}%[insert:prefix(
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
)]%{

__SYSDECL_BEGIN

#ifdef __CC__
__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __size_t size_t;
#endif /* !__std_size_t_defined */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Memory functions (An optional `[b|w|l|q]' suffix is a kos extension):
 *   [std] memcmp[b|w|l|q]      - Compare memory buffers and return the difference of the first non-matching byte/word/dword/qword
 *   [std] memset[b|w|l|q]      - Fill memory with a given byte/word/dword/qword
 *   [kos] mempset[b|w|l|q]     - Same as `memset[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [std] memcpy[b|w|l|q]      - Copy memory between non-overlapping memory blocks.
 *   [glc] mempcpy[b|w|l|q]     - Same as `memcpy[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [std] memmove[b|w|l|q]     - Move memory between potentially overlapping memory blocks.
 *   [kos] mempmove[b|w|l|q]    - Same as `memmove[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [kos] memmoveup[b|w|l|q]   - Same as `memmove[b|w|l|q]', but assume that `dst >= src'
 *   [kos] memmovedown[b|w|l|q] - Same as `memmove[b|w|l|q]', but assume that `dst <= src'
 *   [kos] mempmoveup[b|w|l|q]  - Same as `mempmove[b|w|l|q]', but assume that `dst >= src'
 *   [kos] mempmovedown[b|w|l|q]- Same as `mempmove[b|w|l|q]', but assume that `dst <= src'
 *   [std] memchr[b|w|l|q]      - Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
 *   [glc] memrchr[b|w|l|q]     - Descendingly search for `needle', starting at `haystack+n_(bytes|words|dwords|qwords)-1'. - Return `NULL' if `needle' wasn't found.
 *   [glc] rawmemchr[b|w|l|q]   - Same as `memchr[b|w|l|q]' with a search limit of `(size_t)-1/sizeof(T)'
 *   [kos] rawmemrchr[b|w|l|q]  - Same as `memrchr[b|w|l|q]' without a search limit, starting at `haystack-sizeof(T)'
 *   [kos] memend[b|w|l|q]      - Same as `memchr[b|w|l|q]', but return `haystack+n_(bytes|words|dwords|qwords)', rather than `NULL' if `needle' wasn't found.
 *   [kos] memrend[b|w|l|q]     - Same as `memrchr[b|w|l|q]', but return `haystack - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] memlen[b|w|l|q]      - Same as `memend[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] memrlen[b|w|l|q]     - Same as `memrend[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] rawmemlen[b|w|l|q]   - Same as `rawmemchr[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] rawmemrlen[b|w|l|q]  - Same as `rawmemrchr[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] memxchr[b|w|l|q]     - Same as `memchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxchr[b|w|l|q]    - Same as `memrchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemxchr[b|w|l|q]  - Same as `rawmemchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemrxchr[b|w|l|q] - Same as `rawmemrchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] memxend[b|w|l|q]     - Same as `memend[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxend[b|w|l|q]    - Same as `memrend[b|w|l|q]', but search for non-matching locations.
 *   [kos] memxlen[b|w|l|q]     - Same as `memlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxlen[b|w|l|q]    - Same as `memrlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemxlen[b|w|l|q]  - Same as `rawmemlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemrxlen[b|w|l|q] - Same as `rawmemrlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] mempat[b|w|l|q]      - Same as `memset', but repeat a multi-byte pattern on aligned addresses.
 *
 * NOTE: Alignment requirements of b/w/l/q-suffixed functions:
 *   - For maximum portability, pointer arguments should have the same alignment as
 *     would be expected for Byte=1,Word=2,Long=4,Quad=8. The required alignment is
 *     also annotated for arguments.
 *   - On architecture that allow unaligned memory accesses (e.g. x86), the alignment
 *     isn't mandatory, but is still recommended. To determine if the current  target
 *     architecture allows for unaligned memory  access, and thereby doesn't  enforce
 *     the alignment requirements of b/w/l/q string  functions, you may test for  the
 *     `__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS' macro from `<hybrid/host.h>'
 *
 * String functions:
 *   [std] strlen               - Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')´)
 *   [std] strnlen              - Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´)
 *   [kos] strend               - Same as `str + strlen(str)'
 *   [kos] strnend              - Same as `str + strnlen(str, max_chars)'
 *   [std] strchr               - Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found.
 *   [std] strrchr              - Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found.
 *   [kos] strnchr              - Same as `strchr', but don't exceed `max_chars' characters.
 *   [kos] strnrchr             - Same as `strrchr', but don't exceed `max_chars' characters.
 *   [glc] strchrnul            - Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found.
 *   [kos] strrchrnul           - Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] strnchrnul           - Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found.
 *   [kos] strnrchrnul          - Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] stroff               - Same as `strchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strroff              - Same as `strrchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strnoff              - Same as `strnchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strnroff             - Same as `strnrchrnul', but return the offset from `str', rather than the actual address.
 *   [std] strcpy               - Same as `(char *)memcpy(dst, src, (strlen(src) + 1) * sizeof(char))'
 *   [std] strcat               - Same as `memcpy(strend(dst), src, (strlen(src) + 1) * sizeof(char))', but re-return `dst'
 *   [std] strncpy              - Similar to `strcpy', but always write `dstsize' characters, copying from `src' and filling the rest with padding ZEROes.
 *   [std] strncat              - Copy `strnlen(src, max_chars)' characters to `strend(dst)', then (try to) append a NUL-character thereafter. - Return `dst'.
 *   [glc] stpcpy               - Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´
 *   [glc] stpncpy              - Copy `strnlen(src, max_chars)' characters to `dst', then (try to) append a NUL-character thereafter. - Return `dst'.
 *
 * Annotations:
 *   [std]: The function is defined by the C standard
 *           - `memcpy()'
 *   [glc]: The function is also provided by Glibc, and is likely
 *          apart of some posix/unix standard
 *           - `rawmemchr()'
 *   [kos]: The function is kos-specific, or apart of a standard other than
 *          the C standard, or one  of the standards implemented by  Glibc.
 *           - `strend()' - Not apart of any standard (that I know of) -> KOS-specific
 *           - `strlwr()' - Can also be found in DOS -> DOS-specific, but also provided by KOS
 */
}
%[insert:std]
%


%(auto_header){
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __size_t rsize_t;
#endif /* !__rsize_t_defined */

}


@@>> memcpy(3)
@@Copy memory between non-overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[guard, decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, libc, std, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPY))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__memcpy_c", "__memcpy_g", "__memcpy_by4", "__memcpy_by2")]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memcpy([[out(n_bytes)]] void *__restrict dst,
                         [[in (n_bytes)]] void const *__restrict src,
                         size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}


@@>> memmove(3)
@@Move memory between potentially overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, libc, std, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVE))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memmove([[out(n_bytes)]] void *dst,
                          [[in (n_bytes)]] void const *src,
                          size_t n_bytes) {
	byte_t *pdst;
	byte_t const *psrc;
	if (dst <= src) {
		pdst = (byte_t *)dst;
		psrc = (byte_t const *)src;
		while (n_bytes--)
			*pdst++ = *psrc++;
	} else {
		pdst = (byte_t *)dst + n_bytes;
		psrc = (byte_t const *)src + n_bytes;
		while (n_bytes--)
			*--pdst = *--psrc;
	}
	return dst;
}

@@>> memset(3)
@@Fill memory with a given byte
@@@return: * : Always re-returns `dst'
[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, libc, std, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSET))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__memset_cc",
            "__memset_cg", "__memset_ccn_by4", "__memset_ccn_by2",
            "__memset_gg", "__memset_gcn_by4", "__memset_gcn_by2")]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memset([[out(n_bytes)]] void *__restrict dst,
                         int byte, size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	while (n_bytes--)
		*pdst++ = (byte_t)byte;
	return dst;
}

@@>> memcmp(3)
@@Compare memory buffers and return the difference of the first non-matching byte
@@@return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
@@@return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
@@@return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes'
[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, std, libc, kernel, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMP))]]
[[alias("__gcc_bcmp")]]
[[if(!defined(__KERNEL__)), export_as("__gcc_bcmp")]]
[[impl_include("<hybrid/typecore.h>")]]
int memcmp([[in(n_bytes)]] void const *s1,
           [[in(n_bytes)]] void const *s2, $size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
@@pp_if __SIZEOF_INT__ >= 2@@
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)))
		;
	return (int)v1 - (int)v2;
@@pp_else@@
	while (n_bytes--) {
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
@@pp_endif@@
}

@@>> memchr(3)
@@Ascendingly search for `needle', starting at `haystack'.
@@Return `NULL' if `needle' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, libc, std, kernel, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
void *memchr([[in(n_bytes)]] void const *__restrict haystack, int needle, size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, size_t n_bytes): void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, size_t n_bytes): void const *]
{
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter == (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}


%(libc_fast)#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p) && (__has_builtin(__builtin_strlen) && defined(__CRT_HAVE_strlen))
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
%(libc_fast)#define __libc_strlen(str) (__builtin_constant_p(str) ? __builtin_strlen(str) : __libc_core_strlen(str))
%(libc_fast)#else /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p && __builtin_strlen && __CRT_HAVE_strlen */

@@>> strlen(3)
@@Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')')
[[decl_include("<hybrid/typecore.h>")]]
[[libc, std, kernel, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRLEN))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strlen_g")]]
[[impl_include("<hybrid/typecore.h>")]]
size_t strlen([[in]] char const *__restrict str) {
	return (size_t)(strend(str) - str);
}
%(libc_fast)#endif /* !__LIBC_BIND_OPTIMIZATIONS || __NO_builtin_constant_p || !__builtin_strlen || !__CRT_HAVE_strlen */

@@>> strchr(3)
@@Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found.
[[libc, std, kernel, wunused, crtbuiltin, pure, alias("index")]]
[[if(!defined(__KERNEL__)), export_as("index")]]
[[if(__has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(index, { return __builtin_index(haystack, needle); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCHR))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strchr_g", "__strchr_c")]]
char *strchr([[in]] char const *__restrict haystack, int needle)
	[([[in]] char *__restrict haystack, int needle): char *]
	[([[in]] char const *__restrict haystack, int needle): char const *]
{
	for (;; ++haystack) {
		char ch = *haystack;
		if unlikely((unsigned char)ch == (unsigned char)needle)
			return (char *)haystack;
		if (!ch)
			break;
	}
	return NULL;
}

@@>> strrchr(3)
@@Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found.
[[std, kernel, wunused, crtbuiltin, pure, alias("rindex")]]
[[if(!defined(__KERNEL__)), export_as("rindex")]]
[[if(__has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(rindex, { return __builtin_rindex(haystack, needle); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRRCHR))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strrchr_g", "__strrchr_c")]]
char *strrchr([[in]] char const *__restrict haystack, int needle)
	[([[in]] char *__restrict haystack, int needle): char *]
	[([[in]] char const *__restrict haystack, int needle): char const *]
{
	char const *result = NULL;
	for (;; ++haystack) {
		char ch = *haystack;
		if unlikely((unsigned char)ch == (unsigned char)needle)
			result = haystack;
		if (!ch)
			break;
	}
	return (char *)result;
}

@@>> strcmp(3)
@@Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical
[[libc, std, kernel, wunused, crtbuiltin, pure]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCMP))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strcmp_gg")]]
int strcmp([[in]] char const *s1, [[in]] char const *s2) {
	char c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@>> strncmp(3)
@@Same as `strcmp', but compare at most `maxlen' characters from either string
[[decl_include("<hybrid/typecore.h>")]]
[[std, kernel, wunused, crtbuiltin, pure]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCMP))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strncmp_g")]]
int strncmp([[in(strnlen(., maxlen))]] char const *s1,
            [[in(strnlen(., maxlen))]] char const *s2, size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@>> strstr(3)
@@Search for a given `needle' appearing as a sub-string within `haystack'
@@If no such needle exists, return `NULL'
[[std, kernel, wunused, crtbuiltin, pure]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRSTR))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strstr_g", "__strstr_cg")]]
char *strstr([[in]] char const *haystack, [[in]] char const *needle)
	[([[in]] char *haystack, [[in]] char const *needle): char *]
	[([[in]] char const *haystack, [[in]] char const *needle): char const *]
{
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}


@@>> strcpy(3)
@@Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
@@The exact # of characters copied is `strlen(src) + 1' (+1 because
@@the trailing NUL-character is also copied)
[[std, kernel, crtbuiltin, leaf, dos_only_export_alias("_mbscpy"), libc]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCPY))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strcpy_g")]]
[[nonnull]] char *strcpy([[out]] char *__restrict dst,
                         [[in]] char const *__restrict src) {
	return (char *)memcpy(dst, src, (strlen(src) + 1) * sizeof(char));
}

@@>> strncpy(3)
@@Always write exactly `buflen' characters to `buf'. As far as
@@space  for doing so is available, up to the `strlen(src)' of
@@the first characters  are copied from  `src'. All  remaining
@@characters are always set  to '\0'. Always re-returns  `buf'
[[std, crtbuiltin, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCPY))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strncpy_byn", "__strncpy_by4", "__strncpy_by2", "__strncpy_gg")]]
[[nonnull]] char *strncpy([[out(buflen)]] char *__restrict buf,
                          [[in(strnlen(src, buflen))]] char const *__restrict src,
                          size_t buflen) {
	stpncpy(buf, src, buflen);
	return buf;
}

@@>> strcat(3)
@@Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
@@append it at the end of `dst', or more precisely copy to `strend(dst)'
@@Always re-returns `dst'
[[std, kernel, crtbuiltin, leaf, dos_only_export_alias("_mbscat")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCAT))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strcat_g", "__strcat_c")]]
[[nonnull]] char *strcat([[inout]] char *__restrict dst,
                         [[in]] char const *__restrict src) {
	memcpy(strend(dst), src, (strlen(src) + 1) * sizeof(char));
	return dst;
}

@@>> strncat(3)
@@Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
@@characters   to    `strend(buf)',   and    always   re-return    `buf'.
[[std, crtbuiltin, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCAT))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strncat_g")]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] char *strncat([[inout]] char *__restrict buf,
                          [[in(strnlen(., max_srclen))]] char const *__restrict src,
                          size_t max_srclen) {
	size_t srclen = strnlen(src, max_srclen);
	char *dst = strend(buf);
	*(char *)mempcpy(dst, src, srclen * sizeof(char)) = '\0';
	return buf;
}

@@>> strcspn(3)
@@Return the  offset from  `haystack' to  the first  character
@@for which `strchr(reject, ch) == NULL'. If no such character
@@exists, return `strlen(haystack)'
[[std, wunused, crtbuiltin, pure]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCSPN))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strcspn_g", "__strcspn_cg")]]
size_t strcspn([[in]] char const *haystack,
               [[in]] char const *reject) {
	char const *iter = haystack;
	while (*iter && !strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

@@>> strspn(3)
@@Return the  offset from  `haystack' to  the first  character
@@for which `strchr(accept, ch) != NULL'. If no such character
@@exists, return `strlen(haystack)'
[[std, wunused, crtbuiltin, pure]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRSPN))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strspn_g", "__strspn_cg")]]
size_t strspn([[in]] char const *haystack,
              [[in]] char const *accept) {
	char const *iter = haystack;
	while (*iter && strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

@@>> strpbrk(3)
@@Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
@@If no such character exists, return `NULL' instead.
[[std, wunused, crtbuiltin, pure]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRPBRK))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strpbrk_g", "__strpbrk_cg")]]
char *strpbrk([[in]] char const *haystack, [[in]] char const *accept)
	[([[in]] char *haystack, [[in]] char const *accept): char *]
	[([[in]] char const *haystack, [[in]] char const *accept): char const *]
{
	char haych, ch;
	while ((haych = *haystack++) != '\0') {
		char const *ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char *)haystack - 1;
		}
	}
	return NULL;
}


[[std]]
char *strtok([[inout_opt]] char *str, [[in]] char const *delim) {
	@@static char *strtok_save_ptr = NULL@@
	return strtok_r(str, delim, &strtok_save_ptr);
}

[[std, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCOLL))]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
int strcoll([[in]] char const *s1,
            [[in]] char const *s2) {
	/* XXX: Implement properly? */
	return strcmp(s1, s2);
}

[[std, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRXFRM))]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[impl_include("<hybrid/typecore.h>")]]
size_t strxfrm([[out(buflen)]] char *dst,
               [[in(strnlen(., buflen))]] char const *__restrict src,
               size_t buflen) {
	/* XXX: Implement properly? */
	size_t n = strnlen(src, buflen);
	memcpy(dst, src, n * sizeof(char));
	return n;
}

[[std, wunused, cold]]
[[decl_include("<bits/types.h>")]]
[[export_alias("xstrerror")]]
[[crt_dos_variant({ impl:{ return libc_strerror(libd_errno_dos2kos(errnum)); }})]]
[[section(".text.crt{|.dos}.errno")]]
[[impl_include("<bits/types.h>", "<libc/template/itoa_digits.h>")]]
[[nonnull]] char *strerror($errno_t errnum) {
	@@static char strerror_buf[64] = {0}@@
	char *result;
	char const *string;
	result = strerror_buf;
	string = strerrordesc_np(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strerror_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(strerror_buf) - 1);
	} else {
@@pp_ifdef __BUILDING_LIBC@@
		@libc_sprintf@(result, "Unknown error %d", errnum);
@@pp_else@@
		/* Can't use sprintf() because that would form a  dependency
		 * loop with format_vprintf() which uses strerror() in order
		 * to implement %m! */
		$errno_t iter = errnum;
		if (iter < 0)
			iter = -iter;
		result = COMPILER_ENDOF(strerror_buf);
		*--result = '\0';
		do {
			*--result = itoa_decimal(iter % 10);
		} while ((iter /= 10) != 0);
		if (errnum < 0)
			*--result = '-';
		result -= 14;
		memcpy(result, "Unknown error ", 14 * sizeof(char));
@@pp_endif@@
	}
	return result;
}

%(std)#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:std_function_nousing(memcmp = memcmpc, externLinkageOverride: "C++")]
%[insert:std_function_nousing(memcpy = memcpyc, externLinkageOverride: "C++")]
%[insert:std_function_nousing(memmove = memmovec, externLinkageOverride: "C++")]
%(std)#endif /* __cplusplus && __USE_STRING_OVERLOADS */



%{

#ifdef _MSC_VER
__NAMESPACE_STD_BEGIN
#pragma intrinsic(strcpy)
#pragma intrinsic(strcat)
__NAMESPACE_STD_END
#endif /* _MSC_VER */

}

%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
@@>> strnlen(3)
@@Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´)
[[decl_include("<hybrid/typecore.h>"), guard]]
[[libc, kernel, wunused, crtbuiltin, pure, alias("__strncnt")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("__strncnt")]] /* DOS-specific name */
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNLEN))]]
$size_t strnlen([[in(strnlen(., maxlen))]] char const *__restrict str, $size_t maxlen) {
	return (size_t)(strnend(str, maxlen) - str);
}
%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%#ifdef __USE_XOPEN2K8

@@>> stpcpy(3)
@@Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´
[[crtbuiltin, kernel, leaf, alias("__stpcpy")]]
[[if(!defined(__KERNEL__)), export_as("__stpcpy")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STPCPY))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)), export_as("__stpcpy_g")]]
stpcpy:([[out]] char *__restrict buf,
        [[in]] char const *__restrict src)
	-> [[== buf + strlen(src)]] char *
{
	return (char *)mempcpy(buf, src, (strlen(src) + 1) * sizeof(char)) - 1;
}

@@>> stpncpy(3)
[[decl_include("<hybrid/typecore.h>")]]
[[crtbuiltin, leaf, export_alias("__stpncpy")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STPNCPY))]]
[[impl_include("<hybrid/typecore.h>")]]
stpncpy:([[out(buflen)]] char *__restrict buf,
         [[in(strnlen(., buflen))]] char const *__restrict src,
         $size_t buflen)
	-> [[== buf + strnlen(src, buflen)]] char *
{
	size_t srclen = strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	bzero(buf + srclen, (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}

%[insert:function(__stpcpy = stpcpy)]
%[insert:function(__stpncpy = stpncpy)]

[[pure, wunused, section(".text.crt{|.dos}.unicode.locale.memory")]]
[[dos_only_export_alias("_strcoll_l"), export_alias("__strcoll_l")]]
int strcoll_l([[in]] char const *s1,
              [[in]] char const *s2,
              $locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return strcoll(s1, s2);
}

[[decl_include("<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strxfrm_l"), export_alias("__strxfrm_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
$size_t strxfrm_l([[out(buflen)]] char *dst,
                  [[in(strnlen(., buflen))]] char const *__restrict src,
                  $size_t buflen, $locale_t locale) {
	(void)locale;
	return strxfrm(dst, src, buflen);
}

[[cold, wunused, decl_include("<bits/types.h>")]]
[[crt_dos_variant, section(".text.crt{|.dos}.errno")]]
char *strerror_l($errno_t errnum, $locale_t locale) {
	(void)locale;
	return strerror(errnum);
}

[[wunused, cold, guard, decl_include("<bits/types.h>")]]
[[decl_include("<bits/types.h>")]]
[[crt_dos_variant({ impl:{ return libc_strerror(libd_signo_dos2kos(signo)); }})]]
[[section(".text.crt{|.dos}.string.memory.strsignal")]]
[[nonnull]] char *strsignal($signo_t signo) {
	@@static char strsignal_buf[64] = {0}@@
	char *result = strsignal_buf;
	char const *string;
	string = sigdescr_np(signo);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strsignal_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(strsignal_buf) - 1);
	} else {
		sprintf(result, "Unknown signal %d", signo);
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[crtbuiltin, export_alias("__strndup")]]
[[requires_function(malloc), section(".text.crt{|.dos}.heap.strdup")]]
[[impl_include("<hybrid/typecore.h>")]]
strndup([[in(strnlen(., max_chars))]] char const *__restrict str, $size_t max_chars)
	-> [[malloc/*((strnlen(str, max_chars) + 1) * sizeof(char))*/]] char *
{
	size_t resultsize = strnlen(str, max_chars) * sizeof(char);
	char *result = (char *)malloc(resultsize + sizeof(char));
	if likely(result) {
		*(char *)mempcpy(result, str, resultsize) = '\0';
	}
	return result;
}


%#endif /* __USE_XOPEN2K8 */
%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)

[[crtbuiltin]]
[[dos_only_export_alias("_strdup", "_mbsdup"), export_alias("__strdup")]]
[[requires_function(malloc)]]
[[section(".text.crt{|.dos}.heap.strdup")]]
[[impl_include("<hybrid/typecore.h>")]]
strdup([[in(strlen(string))]] char const *__restrict string)
	-> [[malloc/*((strlen(string) + 1) * sizeof(char))*/]] char *
{
	size_t resultsize = (strlen(string) + 1) * sizeof(char);
	char *result = (char *)malloc(resultsize);
	if likely(result)
		memcpy(result, string, resultsize);
	return result;
}

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */
%
%#ifdef __USE_POSIX

[[leaf, export_alias("strtok_s", "__strtok_r")]]
char *strtok_r([[inout_opt]] char *str,
               [[in]] char const *delim,
               [[inout]] char **__restrict save_ptr) {
	char *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += strspn(str, delim);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + strcspn(str, delim);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}

%#endif /* __USE_POSIX */


%
%#if defined(__USE_GNU) || defined(__USE_BSD)
@@>> memrchr(3)
@@Descendingly search for `needle', starting at `haystack + n_bytes'.
@@Return `NULL' if `needle' wasn't found.
[[libc, kernel, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
void *memrchr([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if (*--iter == (byte_t)needle)
			return iter;
	}
	return NULL;
}

@@>> memmem(3)
@@Return the first address of a sub-string `needle...+=needlelen'
@@stored within `haystack...+=haystacklen'
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[libc, pure, wunused, decl_include("<hybrid/typecore.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>") defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memmem0")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memmem")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMEM))]]
[[impl_include("<features.h>", "<hybrid/typecore.h>")]]
[[nullable]] void *memmem([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen)
	[([[in(haystacklen)]] void *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): [[nullable]] void *]
	[([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): [[nullable]] void const *]
{
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (void *)haystack;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (bcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

@@>> strcasestr(3), strcasestr_l(3)
@@Same as `strstr', but ignore casing
[[kernel, pure, wunused, alias("__strcasestr")]]
[[if(!defined(__KERNEL__)), export_as("__strcasestr")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[impl_include("<hybrid/typecore.h>")]]
[[nullable]] char *strcasestr([[in]] char const *haystack, [[in]] char const *needle)
	[([[in]] char *haystack, [[in]] char const *needle): [[nullable]] char *]
	[([[in]] char const *haystack, [[in]] char const *needle): [[nullable]] char const *]
{
	size_t needle_len = strlen(needle);
	for (; *haystack; ++haystack) {
		if (memcasecmp(haystack, needle, needle_len * sizeof(char)) == 0)
			return (char *)haystack;
	}
	return NULL;
}
%#endif /* __USE_GNU || __USE_BSD */


%
%#if defined(__USE_GNU) || defined(__USE_NETBSD)
@@>> strchrnul(3)
@@Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found.
[[kernel, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRCHRNUL))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__strchrnul_g", "__strchrnul_c")]]
[[nonnull]] char *strchrnul([[in]] char const *__restrict haystack, int needle)
	[([[in]] char *__restrict haystack, int needle): [[nonnull]] char *]
	[([[in]] char const *__restrict haystack, int needle): [[nonnull]] char const *]
{
	for (; *haystack; ++haystack) {
		if ((unsigned char)*haystack == (unsigned char)needle)
			break;
	}
	return (char *)haystack;
}
%#endif /* __USE_GNU || __USE_NETBSD */



%
%#ifdef __USE_GNU

@@>> rawmemchr(3)
@@Same as `memchr' with a search limit of `(size_t)-1'
[[kernel, pure, wunused, alias("__rawmemchr")]]
[[if(!defined(__KERNEL__)), kos_export_as("__rawmemchr")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *rawmemchr([[in]] void const *__restrict haystack, int needle)
	[([[in]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[in]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if (*iter == (byte_t)needle)
			break;
	}
	return iter;
}

@@>> basename(3)
@@Alternate `basename(3)' function that doesn't modify its `filename' argument
@@For a version that is allowed to modify its argument, but is also allowed to
@@strip trailing slashes, include <libgen.h> instead, which will override this
@@GNU-specific  basename() function (you  can explicitly make  use of this GNU
@@version by doing  `#undef basename', or  writing `(basename)(filename)',  as
@@opposed to  `basename(filename)',  when  both  version  have  been  defined)
@@>> basename("/usr/include///"); // Returns ""
@@>> basename("/usr/include/");   // Returns ""
@@>> basename("/usr/include");    // Returns "include"
@@>> basename("/usr/");           // Returns ""
@@>> basename("/usr");            // Returns "usr"
@@>> basename("/");               // Returns ""
@@>> basename("///");             // Returns ""
@@>> basename("foo/bar/");        // Returns ""
@@>> basename("foo/bar");         // Returns "bar"
@@>> basename("foo/");            // Returns ""
@@>> basename("foo");             // Returns "foo"
@@>> basename(".");               // Returns "."
@@>> basename("..");              // Returns ".."
@@>> basename("");                // Returns ""
@@>> basename(NULL);              // <Undefined behavior>
[[guard, pure, wunused, export_alias("__basename", "lbasename"), nonnull]]
[[if(defined(_WIN32)), export_as("dos_lbasename")]]
[[if(!defined(_WIN32)), export_as("unix_lbasename")]]
char *basename([[in]] char const *filename)
	[([[in]] char *filename): char *]
	[([[in]] char const *filename): char const *]
{
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;
@@pp_ifdef _WIN32@@
	/* Skip drive letter. */
	if (isalpha(iter[0]) && iter[1] == ':')
		iter += 2;
@@pp_endif@@
	result = iter;
	for (;;) {
		char ch = *iter++;
@@pp_ifdef _WIN32@@
		if (ch == '/' || ch == '\\')
@@pp_else@@
		if (ch == '/')
@@pp_endif@@
		{
			result = iter;
		}
		if (!ch)
			break;
	}
	return result;
}


@@>> strverscmp(3)
[[pure, wunused, export_alias("__strverscmp"), guard]]
int strverscmp([[in]] char const *s1,
               [[in]] char const *s2) {
	char const *s1_start = s1;
	char c1, c2;
	do {
		if ((c1 = *s1) != (c2 = *s2)) {
			unsigned int vala, valb;

			/* Unwind common digits. */
			while (s1 != s1_start) {
				if (s1[-1] < '0' || s1[-1] > '9')
					break;
				c2 = c1 = *--s1, --s2;
			}

			/* Check if both strings have digit sequences in the same places. */
			if ((c1 < '0' || c1 > '9') &&
			    (c2 < '0' || c2 > '9'))
				return (int)((unsigned char)c1 - (unsigned char)c2);

			/* Deal with leading zeros. */
			if (c1 == '0')
				return -1;
			if (c2 == '0')
				return 1;

			/* Compare digits. */
			vala = c1 - '0';
			valb = c2 - '0';
			for (;;) {
				c1 = *s1++;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1 - '0';
			}
			for (;;) {
				c2 = *s2++;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2 - '0';
			}

			/* Return difference between digits. */
			return (int)vala - (int)valb;
		}
		++s1;
		++s2;
	} while (c1 != '\0');
	return 0;
}


%[insert:function(__mempcpy = mempcpy)]

@@>> mempcpy(3)
@@Same as `memcpy', but return `dst + n_bytes', rather than `dst'
[[decl_include("<hybrid/typecore.h>")]]
[[guard, libc, kernel, leaf, alias("__mempcpy")]]
[[if(!defined(__KERNEL__)), kos_export_as("__mempcpy")]]
[[preferred_fastbind(mempcpy, ["mempcpy", "__mempcpy"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPY))]]
/* Alias for old pre-Glibc 2.26 functions (only existed on i386 32-bit) */
[[if(defined(__i386__) && !defined(__x86_64__) && !defined(__KERNEL__)),
  export_as("__mempcpy_byn", "__mempcpy_by4", "__mempcpy_by2")]]
[[impl_include("<hybrid/typecore.h>")]]
mempcpy:([[out(n_bytes)]] void *__restrict dst,
         [[in (n_bytes)]] void const *__restrict src,
         $size_t n_bytes) -> [[== dst + n_bytes]] void * {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}

%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(mempcpy = mempcpyc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */


@@>> strfry(3)
[[leaf]]
[[impl_include("<hybrid/typecore.h>")]]
strfry:([[inout]] char *__restrict str) -> [[== str]] char * {
	size_t i, count = strlen(str);
	for (i = 0; i < count; ++i) {
		char temp;
		size_t j = rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}

@@>> memfrob(3)
@@Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
@@Always re-return the given `buf'
[[leaf, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memfrob:([[inout(num_bytes)]] void *buf, $size_t num_bytes) -> [[== buf]] void * {
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}

[[guard, pure, wunused, section(".text.crt{|.dos}.unicode.locale.memory")]]
[[dos_only_export_alias("_stricmp_l"), export_alias("__strcasecmp_l")]]
int strcasecmp_l([[in]] char const *s1,
                 [[in]] char const *s2,
                 $locale_t locale) {
	(void)locale;
	return strcasecmp(s1, s2);
}

[[guard, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strnicmp_l", "_strncmpi_l")]]
[[export_alias("__strncasecmp_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
int strncasecmp_l([[in]] char const *s1,
                  [[in]] char const *s2,
                  $size_t maxlen, $locale_t locale) {
	(void)locale;
	return strncasecmp(s1, s2, maxlen);
}

[[const, wunused, nothrow, kernel, libc]]
[[decl_include("<bits/types.h>"), impl_prefix(
@@pp_ifndef __BUILDING_LIBC@@
@@pp_ifndef ___local_sys_errlist_defined@@
#define ___local_sys_errlist_defined
@@pp_if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)@@
@@pp_if !defined(@_sys_errlist@)@@
__CSDECLARE2(,char const *const @_sys_errlist@[],@_sys_errlist@)
#define @_sys_errlist@ @_sys_errlist@
@@pp_endif@@
@@pp_if !defined(@_sys_nerr@)@@
__CSDECLARE(,int,@_sys_nerr@)
#define @_sys_nerr@ @_sys_nerr@
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)@@
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *const *,__NOTHROW,@__sys_errlist@,(void),())
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,int *,__NOTHROW,@__sys_nerr@,(void),())
@@pp_else@@
#undef ___local_sys_errlist_defined
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
), section(".text.crt{|.dos}.errno"), impl_include("<asm/os/errno.h>")]]
[[crt_dos_variant({
impl: {
	char const *result;
	result = libd_strerrorname_np(errnum);
	if (result)
		result = strend(result) + 1;
	return result;
}
})]]
char const *strerrordesc_np($errno_t errnum) {
@@pp_if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)@@
	return (unsigned int)errnum < (unsigned int)@_sys_nerr@ ? @_sys_errlist@[errnum] : NULL;
@@pp_elif !defined(__BUILDING_LIBC) && defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)@@
	return (unsigned int)errnum < (unsigned int)*@__sys_nerr@() ? @__sys_errlist@()[errnum] : NULL;
@@pp_elif defined(__BUILDING_LIBC) || !defined(__CRT_HAVE_strerrorname_np) || defined(__CRT_KOS)@@
	char const *result;
	result = strerrorname_np(errnum);
	if (result)
		result = strend(result) + 1;
	return result;
@@pp_else@@
	char const *result;
	switch (errnum) {

@@pp_ifdef EPERM@@
	case EPERM:           result = "Operation not permitted"; break;
@@pp_endif@@
@@pp_ifdef ENOENT@@
	case ENOENT:          result = "No such file or directory"; break;
@@pp_endif@@
@@pp_ifdef ESRCH@@
	case ESRCH:           result = "No such process"; break;
@@pp_endif@@
@@pp_ifdef EINTR@@
	case EINTR:           result = "Interrupted system call"; break;
@@pp_endif@@
@@pp_ifdef EIO@@
	case EIO:             result = "I/O error"; break;
@@pp_endif@@
@@pp_ifdef ENXIO@@
	case ENXIO:           result = "No such device or address"; break;
@@pp_endif@@
@@pp_ifdef E2BIG@@
	case E2BIG:           result = "Argument list too long"; break;
@@pp_endif@@
@@pp_ifdef ENOEXEC@@
	case ENOEXEC:         result = "Exec format error"; break;
@@pp_endif@@
@@pp_ifdef EBADF@@
	case EBADF:           result = "Bad file number"; break;
@@pp_endif@@
@@pp_ifdef ECHILD@@
	case ECHILD:          result = "No child processes"; break;
@@pp_endif@@
@@pp_ifdef EAGAIN@@
	case EAGAIN:          result = "Try again"; break;
@@pp_endif@@
@@pp_ifdef ENOMEM@@
	case ENOMEM:          result = "Out of memory"; break;
@@pp_endif@@
@@pp_ifdef EACCES@@
	case EACCES:          result = "Permission denied"; break;
@@pp_endif@@
@@pp_ifdef EFAULT@@
	case EFAULT:          result = "Bad address"; break;
@@pp_endif@@
@@pp_ifdef EBUSY@@
	case EBUSY:           result = "Device or resource busy"; break;
@@pp_endif@@
@@pp_ifdef EEXIST@@
	case EEXIST:          result = "File exists"; break;
@@pp_endif@@
@@pp_ifdef EXDEV@@
	case EXDEV:           result = "Cross-device link"; break;
@@pp_endif@@
@@pp_ifdef ENODEV@@
	case ENODEV:          result = "No such device"; break;
@@pp_endif@@
@@pp_ifdef ENOTDIR@@
	case ENOTDIR:         result = "Not a directory"; break;
@@pp_endif@@
@@pp_ifdef EISDIR@@
	case EISDIR:          result = "Is a directory"; break;
@@pp_endif@@
@@pp_ifdef ENFILE@@
	case ENFILE:          result = "File table overflow"; break;
@@pp_endif@@
@@pp_ifdef EMFILE@@
	case EMFILE:          result = "Too many open files"; break;
@@pp_endif@@
@@pp_ifdef ENOTTY@@
	case ENOTTY:          result = "Not a typewriter"; break;
@@pp_endif@@
@@pp_ifdef EFBIG@@
	case EFBIG:           result = "File too large"; break;
@@pp_endif@@
@@pp_ifdef ENOSPC@@
	case ENOSPC:          result = "No space left on device"; break;
@@pp_endif@@
@@pp_ifdef ESPIPE@@
	case ESPIPE:          result = "Illegal seek"; break;
@@pp_endif@@
@@pp_ifdef EROFS@@
	case EROFS:           result = "Read-only file system"; break;
@@pp_endif@@
@@pp_ifdef EMLINK@@
	case EMLINK:          result = "Too many links"; break;
@@pp_endif@@
@@pp_ifdef EPIPE@@
	case EPIPE:           result = "Broken pipe"; break;
@@pp_endif@@
@@pp_ifdef EDOM@@
	case EDOM:            result = "Math argument out of domain of func"; break;
@@pp_endif@@
@@pp_ifdef ENAMETOOLONG@@
	case ENAMETOOLONG:    result = "File name too long"; break;
@@pp_endif@@
@@pp_ifdef ENOLCK@@
	case ENOLCK:          result = "No record locks available"; break;
@@pp_endif@@
@@pp_ifdef ENOSYS@@
	case ENOSYS:          result = "Function not implemented"; break;
@@pp_endif@@
@@pp_ifdef ENOTEMPTY@@
	case ENOTEMPTY:       result = "Directory not empty"; break;
@@pp_endif@@
@@pp_ifdef EINVAL@@
	case EINVAL:          result = "Invalid argument"; break;
@@pp_endif@@
@@pp_ifdef ERANGE@@
	case ERANGE:          result = "Math result not representable"; break;
@@pp_endif@@
@@pp_ifdef EILSEQ@@
	case EILSEQ:          result = "Illegal byte sequence"; break;
@@pp_endif@@
@@pp_ifdef EDEADLOCK@@
	case EDEADLOCK:       result = "Resource deadlock would occur"; break;
@@pp_endif@@
@@pp_ifdef EADDRINUSE@@
	case EADDRINUSE:      result = "Address already in use"; break;
@@pp_endif@@
@@pp_ifdef EADDRNOTAVAIL@@
	case EADDRNOTAVAIL:   result = "Cannot assign requested address"; break;
@@pp_endif@@
@@pp_ifdef EAFNOSUPPORT@@
	case EAFNOSUPPORT:    result = "Address family not supported by protocol"; break;
@@pp_endif@@
@@pp_ifdef EALREADY@@
	case EALREADY:        result = "Operation already in progress"; break;
@@pp_endif@@
@@pp_ifdef EBADMSG@@
	case EBADMSG:         result = "Not a data message"; break;
@@pp_endif@@
@@pp_ifdef ECANCELED@@
	case ECANCELED:       result = "Operation Canceled"; break;
@@pp_endif@@
@@pp_ifdef ECONNABORTED@@
	case ECONNABORTED:    result = "Software caused connection abort"; break;
@@pp_endif@@
@@pp_ifdef ECONNREFUSED@@
	case ECONNREFUSED:    result = "Connection refused"; break;
@@pp_endif@@
@@pp_ifdef ECONNRESET@@
	case ECONNRESET:      result = "Connection reset by peer"; break;
@@pp_endif@@
@@pp_ifdef EDESTADDRREQ@@
	case EDESTADDRREQ:    result = "Destination address required"; break;
@@pp_endif@@
@@pp_ifdef EHOSTUNREACH@@
	case EHOSTUNREACH:    result = "No route to host"; break;
@@pp_endif@@
@@pp_ifdef EIDRM@@
	case EIDRM:           result = "Identifier removed"; break;
@@pp_endif@@
@@pp_ifdef EINPROGRESS@@
	case EINPROGRESS:     result = "Operation now in progress"; break;
@@pp_endif@@
@@pp_ifdef EISCONN@@
	case EISCONN:         result = "Transport endpoint is already connected"; break;
@@pp_endif@@
@@pp_ifdef ELOOP@@
	case ELOOP:           result = "Too many symbolic links encountered"; break;
@@pp_endif@@
@@pp_ifdef EMSGSIZE@@
	case EMSGSIZE:        result = "Message too long"; break;
@@pp_endif@@
@@pp_ifdef ENETDOWN@@
	case ENETDOWN:        result = "Network is down"; break;
@@pp_endif@@
@@pp_ifdef ENETRESET@@
	case ENETRESET:       result = "Network dropped connection because of reset"; break;
@@pp_endif@@
@@pp_ifdef ENETUNREACH@@
	case ENETUNREACH:     result = "Network is unreachable"; break;
@@pp_endif@@
@@pp_ifdef ENOBUFS@@
	case ENOBUFS:         result = "No buffer space available"; break;
@@pp_endif@@
@@pp_ifdef ENODATA@@
	case ENODATA:         result = "No data available"; break;
@@pp_endif@@
@@pp_ifdef ENOLINK@@
	case ENOLINK:         result = "Link has been severed"; break;
@@pp_endif@@
@@pp_ifdef ENOMSG@@
	case ENOMSG:          result = "No message of desired type"; break;
@@pp_endif@@
@@pp_ifdef ENOPROTOOPT@@
	case ENOPROTOOPT:     result = "Protocol not available"; break;
@@pp_endif@@
@@pp_ifdef ENOSR@@
	case ENOSR:           result = "Out of streams resources"; break;
@@pp_endif@@
@@pp_ifdef ENOSTR@@
	case ENOSTR:          result = "Device not a stream"; break;
@@pp_endif@@
@@pp_ifdef ENOTCONN@@
	case ENOTCONN:        result = "Transport endpoint is not connected"; break;
@@pp_endif@@
@@pp_ifdef ENOTRECOVERABLE@@
	case ENOTRECOVERABLE: result = "State not recoverable"; break;
@@pp_endif@@
@@pp_ifdef ENOTSOCK@@
	case ENOTSOCK:        result = "Socket operation on non-socket"; break;
@@pp_endif@@
@@pp_ifdef ENOTSUP@@
	case ENOTSUP:         result = "Not supported"; break;
@@pp_endif@@
@@pp_ifdef EOPNOTSUPP@@
	case EOPNOTSUPP:      result = "Operation not supported on transport endpoint"; break;
@@pp_endif@@
@@pp_ifdef EOTHER@@
	case EOTHER:          result = "Other"; break;
@@pp_endif@@
@@pp_ifdef EOVERFLOW@@
	case EOVERFLOW:       result = "Value too large for defined data type"; break;
@@pp_endif@@
@@pp_ifdef EOWNERDEAD@@
	case EOWNERDEAD:      result = "Owner died"; break;
@@pp_endif@@
@@pp_ifdef EPROTO@@
	case EPROTO:          result = "Protocol error"; break;
@@pp_endif@@
@@pp_ifdef EPROTONOSUPPORT@@
	case EPROTONOSUPPORT: result = "Protocol not supported"; break;
@@pp_endif@@
@@pp_ifdef EPROTOTYPE@@
	case EPROTOTYPE:      result = "Protocol wrong type for socket"; break;
@@pp_endif@@
@@pp_ifdef ETIME@@
	case ETIME:           result = "Timer expired"; break;
@@pp_endif@@
@@pp_ifdef ETIMEDOUT@@
	case ETIMEDOUT:       result = "Connection timed out"; break;
@@pp_endif@@
@@pp_ifdef ETXTBSY@@
	case ETXTBSY:         result = "Text file busy"; break;
@@pp_endif@@
@@pp_ifdef EFTYPE@@
	case EFTYPE:          result = "Inappropriate file type or format"; break;
@@pp_endif@@
@@pp_ifdef ENMFILE@@
	case ENMFILE:         result = "No more files"; break;
@@pp_endif@@
@@pp_ifdef EPFNOSUPPORT@@
	case EPFNOSUPPORT:    result = "Protocol family not supported"; break;
@@pp_endif@@
@@pp_ifdef EHOSTDOWN@@
	case EHOSTDOWN:       result = "Host is down"; break;
@@pp_endif@@
@@pp_ifdef ETOOMANYREFS@@
	case ETOOMANYREFS:    result = "Too many references: cannot splice"; break;
@@pp_endif@@
@@pp_ifdef EDQUOT@@
	case EDQUOT:          result = "Quota exceeded"; break;
@@pp_endif@@
@@pp_ifdef ESTALE@@
	case ESTALE:          result = "Stale file handle"; break;
@@pp_endif@@
@@pp_ifdef ENOSHARE@@
	case ENOSHARE:        result = "No such host or network path"; break;
@@pp_endif@@
@@pp_ifdef ECASECLASH@@
	case ECASECLASH:      result = "Filename exists with different case"; break;
@@pp_endif@@
@@pp_ifdef ENOTBLK@@
	case ENOTBLK:         result = "Block device required"; break;
@@pp_endif@@
@@pp_ifdef ECHRNG@@
	case ECHRNG:          result = "Channel number out of range"; break;
@@pp_endif@@
@@pp_ifdef EL2NSYNC@@
	case EL2NSYNC:        result = "Level 2 not synchronized"; break;
@@pp_endif@@
@@pp_ifdef EL3HLT@@
	case EL3HLT:          result = "Level 3 halted"; break;
@@pp_endif@@
@@pp_ifdef EL3RST@@
	case EL3RST:          result = "Level 3 reset"; break;
@@pp_endif@@
@@pp_ifdef ELNRNG@@
	case ELNRNG:          result = "Link number out of range"; break;
@@pp_endif@@
@@pp_ifdef EUNATCH@@
	case EUNATCH:         result = "Protocol driver not attached"; break;
@@pp_endif@@
@@pp_ifdef ENOCSI@@
	case ENOCSI:          result = "No CSI structure available"; break;
@@pp_endif@@
@@pp_ifdef EL2HLT@@
	case EL2HLT:          result = "Level 2 halted"; break;
@@pp_endif@@
@@pp_ifdef EBADE@@
	case EBADE:           result = "Invalid exchange"; break;
@@pp_endif@@
@@pp_ifdef EBADR@@
	case EBADR:           result = "Invalid request descriptor"; break;
@@pp_endif@@
@@pp_ifdef EXFULL@@
	case EXFULL:          result = "Exchange full"; break;
@@pp_endif@@
@@pp_ifdef ENOANO@@
	case ENOANO:          result = "No anode"; break;
@@pp_endif@@
@@pp_ifdef EBADRQC@@
	case EBADRQC:         result = "Invalid request code"; break;
@@pp_endif@@
@@pp_ifdef EBADSLT@@
	case EBADSLT:         result = "Invalid slot"; break;
@@pp_endif@@
@@pp_ifdef EBFONT@@
	case EBFONT:          result = "Bad font file fmt"; break;
@@pp_endif@@
@@pp_ifdef ENONET@@
	case ENONET:          result = "Machine is not on the network"; break;
@@pp_endif@@
@@pp_ifdef ENOPKG@@
	case ENOPKG:          result = "Package not installed"; break;
@@pp_endif@@
@@pp_ifdef EREMOTE@@
	case EREMOTE:         result = "The object is remote"; break;
@@pp_endif@@
@@pp_ifdef EADV@@
	case EADV:            result = "Advertise error"; break;
@@pp_endif@@
@@pp_ifdef ESRMNT@@
	case ESRMNT:          result = "Srmount error"; break;
@@pp_endif@@
@@pp_ifdef ECOMM@@
	case ECOMM:           result = "Communication error on send"; break;
@@pp_endif@@
@@pp_ifdef ELBIN@@
	case ELBIN:           result = "Inode is remote (not really error)"; break;
@@pp_endif@@
@@pp_ifdef EDOTDOT@@
	case EDOTDOT:         result = "Cross mount point (not really error)"; break;
@@pp_endif@@
@@pp_ifdef ENOTUNIQ@@
	case ENOTUNIQ:        result = "Given log. name not unique"; break;
@@pp_endif@@
@@pp_ifdef EBADFD@@
	case EBADFD:          result = "f.d. invalid for this operation"; break;
@@pp_endif@@
@@pp_ifdef EREMCHG@@
	case EREMCHG:         result = "Remote address changed"; break;
@@pp_endif@@
@@pp_ifdef ELIBACC@@
	case ELIBACC:         result = "Can't access a needed shared lib"; break;
@@pp_endif@@
@@pp_ifdef ELIBBAD@@
	case ELIBBAD:         result = "Accessing a corrupted shared lib"; break;
@@pp_endif@@
@@pp_ifdef ELIBSCN@@
	case ELIBSCN:         result = ".lib section in a.out corrupted"; break;
@@pp_endif@@
@@pp_ifdef ELIBMAX@@
	case ELIBMAX:         result = "Attempting to link in too many libs"; break;
@@pp_endif@@
@@pp_ifdef ELIBEXEC@@
	case ELIBEXEC:        result = "Attempting to exec a shared library"; break;
@@pp_endif@@
@@pp_ifdef ESHUTDOWN@@
	case ESHUTDOWN:       result = "Can't send after socket shutdown"; break;
@@pp_endif@@
@@pp_ifdef ESOCKTNOSUPPORT@@
	case ESOCKTNOSUPPORT: result = "Socket type not supported"; break;
@@pp_endif@@
@@pp_ifdef EPROCLIM@@
	case EPROCLIM:        result = "Process limit reached"; break;
@@pp_endif@@
@@pp_ifdef EUSERS@@
	case EUSERS:          result = "Too many users"; break;
@@pp_endif@@
@@pp_ifdef ENOMEDIUM@@
	case ENOMEDIUM:       result = "No medium (in tape drive)"; break;
@@pp_endif@@
@@pp_ifdef ESTRPIPE@@
	case ESTRPIPE:        result = "Streams pipe error"; break;
@@pp_endif@@
@@pp_ifdef EMULTIHOP@@
	case EMULTIHOP:       result = "Multihop attempted"; break;
@@pp_endif@@
@@pp_ifdef ERESTART@@
	case ERESTART:        result = "Interrupted system call should be restarted"; break;
@@pp_endif@@
@@pp_ifdef EUCLEAN@@
	case EUCLEAN:         result = "Structure needs cleaning"; break;
@@pp_endif@@
@@pp_ifdef ENOTNAM@@
	case ENOTNAM:         result = "Not a XENIX named type file"; break;
@@pp_endif@@
@@pp_ifdef ENAVAIL@@
	case ENAVAIL:         result = "No XENIX semaphores available"; break;
@@pp_endif@@
@@pp_ifdef EISNAM@@
	case EISNAM:          result = "Is a named type file"; break;
@@pp_endif@@
@@pp_ifdef EREMOTEIO@@
	case EREMOTEIO:       result = "Remote I/O error"; break;
@@pp_endif@@
@@pp_ifdef EMEDIUMTYPE@@
	case EMEDIUMTYPE:     result = "Wrong medium type"; break;
@@pp_endif@@
@@pp_ifdef ENOKEY@@
	case ENOKEY:          result = "Required key not available"; break;
@@pp_endif@@
@@pp_ifdef EKEYEXPIRED@@
	case EKEYEXPIRED:     result = "Key has expired"; break;
@@pp_endif@@
@@pp_ifdef EKEYREVOKED@@
	case EKEYREVOKED:     result = "Key has been revoked"; break;
@@pp_endif@@
@@pp_ifdef EKEYREJECTED@@
	case EKEYREJECTED:    result = "Key was rejected by service"; break;
@@pp_endif@@
@@pp_ifdef ERFKILL@@
	case ERFKILL:         result = "Operation not possible due to RF-kill"; break;
@@pp_endif@@
@@pp_ifdef EHWPOISON@@
	case EHWPOISON:       result = "Memory page has hardware error"; break;
@@pp_endif@@
@@pp_if defined(STRUNCATE) && (!defined(ERANGE) || STRUNCATE != ERANGE)@@
	case STRUNCATE:       result = "Truncated"; break;
@@pp_endif@@
@@pp_if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)@@
	case EWOULDBLOCK:     result = "Operation would block"; break;
@@pp_endif@@
@@pp_if defined(EDEADLK) && (!defined(EDEADLOCK) || EDEADLOCK != EDEADLK)@@
	case EDEADLK:         result = "Resource deadlock would occur"; break;
@@pp_endif@@

	default:
		result = NULL;
		break;
	}
	return result;
@@pp_endif@@
}

[[const, wunused, nothrow, kernel, libc]]
[[decl_include("<bits/types.h>"), alias("strerrno")]]
[[if(!defined(__KERNEL__)), export_as("strerrno")]]
[[crt_dos_variant({
impl: {
	/* Special handling for a hand full of errno
	 * values that don't  have KOS  equivalents. */
	switch (errnum) {
	case DOS_STRUNCATE:
		return "STRUNCATE\0" "Truncated";
	case DOS_EOTHER:
		return "EOTHER\0" "Other";
	default:
		break;
	}
	errnum = libd_errno_dos2kos(errnum);
	return libc_strerrorname_np(errnum);
}
})]]
[[section(".text.crt{|.dos}.errno")]]
[[impl_include("<hybrid/typecore.h>", "<asm/os/errno.h>")]]
char const *strerrorname_np($errno_t errnum) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosErrnoMappings: {int: (string, string)} = Dict();
local inside = false;
with (local fp = File.open("../../../include/asm/os/kos/errno.h")) {
	for (local l: fp) {
		l = l.strip();
		if (l == "/" "*[[[begin]]]*" "/")
			inside = true;
		if (l == "/" "*[[[end]]]*" "/")
			inside = false;
		if (!inside)
			continue;
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __%[^ ] %[^/ ] /" "* %[^]")...;
		} catch (...) {
			continue;
		}
		comment = comment.partition("*" "/")[0].strip();
		while (comment.startswith("["))
			comment = comment.partition("]")[2].lstrip();
		value = int(value.strip());
		if (value in kosErrnoMappings)
			continue;
		kosErrnoMappings[value] = (name, comment);
	}
}
local emax = kosErrnoMappings.keys > ...;
print("#define HAVE_KOS_ERRNO_VALUES");
for (local ids: kosErrnoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined({0}) || {0} != {1}".format({ kosErrnoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_ERRNO_VALUES");
	print("@@pp_endif@@");
}
kosErrnoMappings[0] = ("EOK", "Success");
print("@@pp_ifdef HAVE_KOS_ERRNO_VALUES@@");
print("	static char const errno_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:emax + 1]) {
	local name, comment = kosErrnoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != emax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:emax + 1]) {
	if (kosErrnoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const errno_offsets[", (emax + 1), "] = {");
for (local i: [:emax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define HAVE_KOS_ERRNO_VALUES
@@pp_if !defined(EPERM) || EPERM != 1 || !defined(ENOENT) || ENOENT != 2 || !defined(ESRCH) || ESRCH != 3 || !defined(EINTR) || EINTR != 4@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EIO) || EIO != 5 || !defined(ENXIO) || ENXIO != 6 || !defined(E2BIG) || E2BIG != 7 || !defined(ENOEXEC) || ENOEXEC != 8@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EBADF) || EBADF != 9 || !defined(ECHILD) || ECHILD != 10 || !defined(EAGAIN) || EAGAIN != 11 || !defined(ENOMEM) || ENOMEM != 12@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EACCES) || EACCES != 13 || !defined(EFAULT) || EFAULT != 14 || !defined(ENOTBLK) || ENOTBLK != 15 || !defined(EBUSY) || EBUSY != 16@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EEXIST) || EEXIST != 17 || !defined(EXDEV) || EXDEV != 18 || !defined(ENODEV) || ENODEV != 19 || !defined(ENOTDIR) || ENOTDIR != 20@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EISDIR) || EISDIR != 21 || !defined(EINVAL) || EINVAL != 22 || !defined(ENFILE) || ENFILE != 23 || !defined(EMFILE) || EMFILE != 24@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOTTY) || ENOTTY != 25 || !defined(ETXTBSY) || ETXTBSY != 26 || !defined(EFBIG) || EFBIG != 27 || !defined(ENOSPC) || ENOSPC != 28@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ESPIPE) || ESPIPE != 29 || !defined(EROFS) || EROFS != 30 || !defined(EMLINK) || EMLINK != 31 || !defined(EPIPE) || EPIPE != 32@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EDOM) || EDOM != 33 || !defined(ERANGE) || ERANGE != 34 || !defined(EDEADLK) || EDEADLK != 35 || !defined(ENAMETOOLONG) || ENAMETOOLONG != 36@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOLCK) || ENOLCK != 37 || !defined(ENOSYS) || ENOSYS != 38 || !defined(ENOTEMPTY) || ENOTEMPTY != 39 || !defined(ELOOP) || ELOOP != 40@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOMSG) || ENOMSG != 42 || !defined(EIDRM) || EIDRM != 43 || !defined(ECHRNG) || ECHRNG != 44 || !defined(EL2NSYNC) || EL2NSYNC != 45@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EL3HLT) || EL3HLT != 46 || !defined(EL3RST) || EL3RST != 47 || !defined(ELNRNG) || ELNRNG != 48 || !defined(EUNATCH) || EUNATCH != 49@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOCSI) || ENOCSI != 50 || !defined(EL2HLT) || EL2HLT != 51 || !defined(EBADE) || EBADE != 52 || !defined(EBADR) || EBADR != 53@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EXFULL) || EXFULL != 54 || !defined(ENOANO) || ENOANO != 55 || !defined(EBADRQC) || EBADRQC != 56 || !defined(EBADSLT) || EBADSLT != 57@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EBFONT) || EBFONT != 59 || !defined(ENOSTR) || ENOSTR != 60 || !defined(ENODATA) || ENODATA != 61 || !defined(ETIME) || ETIME != 62@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOSR) || ENOSR != 63 || !defined(ENONET) || ENONET != 64 || !defined(ENOPKG) || ENOPKG != 65 || !defined(EREMOTE) || EREMOTE != 66@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOLINK) || ENOLINK != 67 || !defined(EADV) || EADV != 68 || !defined(ESRMNT) || ESRMNT != 69 || !defined(ECOMM) || ECOMM != 70@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EPROTO) || EPROTO != 71 || !defined(EMULTIHOP) || EMULTIHOP != 72 || !defined(EDOTDOT) || EDOTDOT != 73 || !defined(EBADMSG) || EBADMSG != 74@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EOVERFLOW) || EOVERFLOW != 75 || !defined(ENOTUNIQ) || ENOTUNIQ != 76 || !defined(EBADFD) || EBADFD != 77 || !defined(EREMCHG) || EREMCHG != 78@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ELIBACC) || ELIBACC != 79 || !defined(ELIBBAD) || ELIBBAD != 80 || !defined(ELIBSCN) || ELIBSCN != 81 || !defined(ELIBMAX) || ELIBMAX != 82@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ELIBEXEC) || ELIBEXEC != 83 || !defined(EILSEQ) || EILSEQ != 84 || !defined(ERESTART) || ERESTART != 85 || !defined(ESTRPIPE) || ESTRPIPE != 86@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EUSERS) || EUSERS != 87 || !defined(ENOTSOCK) || ENOTSOCK != 88 || !defined(EDESTADDRREQ) || EDESTADDRREQ != 89 || !defined(EMSGSIZE) || EMSGSIZE != 90@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EPROTOTYPE) || EPROTOTYPE != 91 || !defined(ENOPROTOOPT) || ENOPROTOOPT != 92 || !defined(EPROTONOSUPPORT) || EPROTONOSUPPORT != 93 || !defined(ESOCKTNOSUPPORT) || ESOCKTNOSUPPORT != 94@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EOPNOTSUPP) || EOPNOTSUPP != 95 || !defined(EPFNOSUPPORT) || EPFNOSUPPORT != 96 || !defined(EAFNOSUPPORT) || EAFNOSUPPORT != 97 || !defined(EADDRINUSE) || EADDRINUSE != 98@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EADDRNOTAVAIL) || EADDRNOTAVAIL != 99 || !defined(ENETDOWN) || ENETDOWN != 100 || !defined(ENETUNREACH) || ENETUNREACH != 101 || !defined(ENETRESET) || ENETRESET != 102@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ECONNABORTED) || ECONNABORTED != 103 || !defined(ECONNRESET) || ECONNRESET != 104 || !defined(ENOBUFS) || ENOBUFS != 105 || !defined(EISCONN) || EISCONN != 106@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOTCONN) || ENOTCONN != 107 || !defined(ESHUTDOWN) || ESHUTDOWN != 108 || !defined(ETOOMANYREFS) || ETOOMANYREFS != 109 || !defined(ETIMEDOUT) || ETIMEDOUT != 110@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ECONNREFUSED) || ECONNREFUSED != 111 || !defined(EHOSTDOWN) || EHOSTDOWN != 112 || !defined(EHOSTUNREACH) || EHOSTUNREACH != 113 || !defined(EALREADY) || EALREADY != 114@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EINPROGRESS) || EINPROGRESS != 115 || !defined(ESTALE) || ESTALE != 116 || !defined(EUCLEAN) || EUCLEAN != 117 || !defined(ENOTNAM) || ENOTNAM != 118@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENAVAIL) || ENAVAIL != 119 || !defined(EISNAM) || EISNAM != 120 || !defined(EREMOTEIO) || EREMOTEIO != 121 || !defined(EDQUOT) || EDQUOT != 122@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOMEDIUM) || ENOMEDIUM != 123 || !defined(EMEDIUMTYPE) || EMEDIUMTYPE != 124 || !defined(ECANCELED) || ECANCELED != 125 || !defined(ENOKEY) || ENOKEY != 126@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(EKEYEXPIRED) || EKEYEXPIRED != 127 || !defined(EKEYREVOKED) || EKEYREVOKED != 128 || !defined(EKEYREJECTED) || EKEYREJECTED != 129 || !defined(EOWNERDEAD) || EOWNERDEAD != 130@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_if !defined(ENOTRECOVERABLE) || ENOTRECOVERABLE != 131 || !defined(ERFKILL) || ERFKILL != 132 || !defined(EHWPOISON) || EHWPOISON != 133@@
#undef HAVE_KOS_ERRNO_VALUES
@@pp_endif@@
@@pp_ifdef HAVE_KOS_ERRNO_VALUES@@
	static char const errno_strtab[] =
	"EOK\0Success\0"
	"EPERM\0Operation not permitted\0"
	"ENOENT\0No such file or directory\0"
	"ESRCH\0No such process\0"
	"EINTR\0Interrupted system call\0"
	"EIO\0I/O error\0"
	"ENXIO\0No such device or address\0"
	"E2BIG\0Argument list too long\0"
	"ENOEXEC\0Exec format error\0"
	"EBADF\0Bad file number\0"
	"ECHILD\0No child processes\0"
	"EAGAIN\0Try again\0"
	"ENOMEM\0Out of memory\0"
	"EACCES\0Permission denied\0"
	"EFAULT\0Bad address\0"
	"ENOTBLK\0Block device required\0"
	"EBUSY\0Device or resource busy\0"
	"EEXIST\0File exists\0"
	"EXDEV\0Cross-device link\0"
	"ENODEV\0No such device\0"
	"ENOTDIR\0Not a directory\0"
	"EISDIR\0Is a directory\0"
	"EINVAL\0Invalid argument\0"
	"ENFILE\0File table overflow\0"
	"EMFILE\0Too many open files\0"
	"ENOTTY\0Not a typewriter\0"
	"ETXTBSY\0Text file busy\0"
	"EFBIG\0File too large\0"
	"ENOSPC\0No space left on device\0"
	"ESPIPE\0Illegal seek\0"
	"EROFS\0Read-only file system\0"
	"EMLINK\0Too many links\0"
	"EPIPE\0Broken pipe\0"
	"EDOM\0Math argument out of domain of func\0"
	"ERANGE\0Math result not representable\0"
	"EDEADLK\0Resource deadlock would occur\0"
	"ENAMETOOLONG\0File name too long\0"
	"ENOLCK\0No record locks available\0"
	"ENOSYS\0Function not implemented\0"
	"ENOTEMPTY\0Directory not empty\0"
	"ELOOP\0Too many symbolic links encountered\0"
	"ENOMSG\0No message of desired type\0"
	"EIDRM\0Identifier removed\0"
	"ECHRNG\0Channel number out of range\0"
	"EL2NSYNC\0Level 2 not synchronized\0"
	"EL3HLT\0Level 3 halted\0"
	"EL3RST\0Level 3 reset\0"
	"ELNRNG\0Link number out of range\0"
	"EUNATCH\0Protocol driver not attached\0"
	"ENOCSI\0No CSI structure available\0"
	"EL2HLT\0Level 2 halted\0"
	"EBADE\0Invalid exchange\0"
	"EBADR\0Invalid request descriptor\0"
	"EXFULL\0Exchange full\0"
	"ENOANO\0No anode\0"
	"EBADRQC\0Invalid request code\0"
	"EBADSLT\0Invalid slot\0"
	"EBFONT\0Bad font file format\0"
	"ENOSTR\0Device not a stream\0"
	"ENODATA\0No data available\0"
	"ETIME\0Timer expired\0"
	"ENOSR\0Out of streams resources\0"
	"ENONET\0Machine is not on the network\0"
	"ENOPKG\0Package not installed\0"
	"EREMOTE\0Object is remote\0"
	"ENOLINK\0Link has been severed\0"
	"EADV\0Advertise error\0"
	"ESRMNT\0Srmount error\0"
	"ECOMM\0Communication error on send\0"
	"EPROTO\0Protocol error\0"
	"EMULTIHOP\0Multihop attempted\0"
	"EDOTDOT\0RFS specific error\0"
	"EBADMSG\0Not a data message\0"
	"EOVERFLOW\0Value too large for defined data type\0"
	"ENOTUNIQ\0Name not unique on network\0"
	"EBADFD\0File descriptor in bad state\0"
	"EREMCHG\0Remote address changed\0"
	"ELIBACC\0Can not access a needed shared library\0"
	"ELIBBAD\0Accessing a corrupted shared library\0"
	"ELIBSCN\0.lib section in a.out corrupted\0"
	"ELIBMAX\0Attempting to link in too many shared libraries\0"
	"ELIBEXEC\0Cannot exec a shared library directly\0"
	"EILSEQ\0Illegal byte sequence\0"
	"ERESTART\0Interrupted system call should be restarted\0"
	"ESTRPIPE\0Streams pipe error\0"
	"EUSERS\0Too many users\0"
	"ENOTSOCK\0Socket operation on non-socket\0"
	"EDESTADDRREQ\0Destination address required\0"
	"EMSGSIZE\0Message too long\0"
	"EPROTOTYPE\0Protocol wrong type for socket\0"
	"ENOPROTOOPT\0Protocol not available\0"
	"EPROTONOSUPPORT\0Protocol not supported\0"
	"ESOCKTNOSUPPORT\0Socket type not supported\0"
	"EOPNOTSUPP\0Operation not supported on transport endpoint\0"
	"EPFNOSUPPORT\0Protocol family not supported\0"
	"EAFNOSUPPORT\0Address family not supported by protocol\0"
	"EADDRINUSE\0Address already in use\0"
	"EADDRNOTAVAIL\0Cannot assign requested address\0"
	"ENETDOWN\0Network is down\0"
	"ENETUNREACH\0Network is unreachable\0"
	"ENETRESET\0Network dropped connection because of reset\0"
	"ECONNABORTED\0Software caused connection abort\0"
	"ECONNRESET\0Connection reset by peer\0"
	"ENOBUFS\0No buffer space available\0"
	"EISCONN\0Transport endpoint is already connected\0"
	"ENOTCONN\0Transport endpoint is not connected\0"
	"ESHUTDOWN\0Cannot send after transport endpoint shutdown\0"
	"ETOOMANYREFS\0Too many references: cannot splice\0"
	"ETIMEDOUT\0Connection timed out\0"
	"ECONNREFUSED\0Connection refused\0"
	"EHOSTDOWN\0Host is down\0"
	"EHOSTUNREACH\0No route to host\0"
	"EALREADY\0Operation already in progress\0"
	"EINPROGRESS\0Operation now in progress\0"
	"ESTALE\0Stale file handle\0"
	"EUCLEAN\0Structure needs cleaning\0"
	"ENOTNAM\0Not a XENIX named type file\0"
	"ENAVAIL\0No XENIX semaphores available\0"
	"EISNAM\0Is a named type file\0"
	"EREMOTEIO\0Remote I/O error\0"
	"EDQUOT\0Quota exceeded\0"
	"ENOMEDIUM\0No medium found\0"
	"EMEDIUMTYPE\0Wrong medium type\0"
	"ECANCELED\0Operation canceled\0"
	"ENOKEY\0Required key not available\0"
	"EKEYEXPIRED\0Key has expired\0"
	"EKEYREVOKED\0Key has been revoked\0"
	"EKEYREJECTED\0Key was rejected by service\0"
	"EOWNERDEAD\0Owner died\0"
	"ENOTRECOVERABLE\0State not recoverable\0"
	"ERFKILL\0Operation not possible due to RF-kill\0"
	"EHWPOISON\0Memory page has hardware error"
	"";
	static uint16_t const errno_offsets[134] = {
		0, 12, 42, 75, 97, 127, 141, 173, 202, 228, 250, 276, 293, 314, 339, 358,
		388, 418, 437, 461, 483, 507, 529, 553, 580, 607, 631, 654, 675, 706, 726, 754,
		776, 794, 835, 872, 910, 942, 975, 1007, 1037, 4166, 1079, 1113, 1138, 1173, 1207, 1229,
		1250, 1282, 1319, 1353, 1375, 1398, 1431, 1452, 1468, 1497, 4166, 1518, 1546, 1573, 1599, 1619,
		1650, 1687, 1716, 1741, 1771, 1792, 1813, 1847, 1869, 1898, 1925, 1952, 2000, 2036, 2072, 2103,
		2150, 2195, 2235, 2291, 2338, 2367, 2420, 2448, 2470, 2510, 2552, 2578, 2620, 2655, 2694, 2736,
		2793, 2836, 2890, 2924, 2970, 2995, 3030, 3084, 3130, 3166, 3200, 3248, 3293, 3349, 3397, 3428,
		3460, 3483, 3513, 3552, 3590, 3615, 3648, 3684, 3722, 3750, 3777, 3799, 3825, 3855, 3884, 3918,
		3946, 3979, 4020, 4042, 4080, 4126,
	};
/*[[[end]]]*/
	char const *result;
	if ((unsigned int)errnum >= COMPILER_LENOF(errno_offsets))
		return NULL;
	result = &errno_strtab[errno_offsets[errnum]];
	if (!*result)
		result = NULL;
	return result;
@@pp_else@@
	char const *result;
	switch (errnum) {

@@pp_ifdef EPERM@@
	case EPERM:           result = "EPERM\0Operation not permitted"; break;
@@pp_endif@@
@@pp_ifdef ENOENT@@
	case ENOENT:          result = "ENOENT\0No such file or directory"; break;
@@pp_endif@@
@@pp_ifdef ESRCH@@
	case ESRCH:           result = "ESRCH\0No such process"; break;
@@pp_endif@@
@@pp_ifdef EINTR@@
	case EINTR:           result = "EINTR\0Interrupted system call"; break;
@@pp_endif@@
@@pp_ifdef EIO@@
	case EIO:             result = "EIO\0I/O error"; break;
@@pp_endif@@
@@pp_ifdef ENXIO@@
	case ENXIO:           result = "ENXIO\0No such device or address"; break;
@@pp_endif@@
@@pp_ifdef E2BIG@@
	case E2BIG:           result = "E2BIG\0Argument list too long"; break;
@@pp_endif@@
@@pp_ifdef ENOEXEC@@
	case ENOEXEC:         result = "ENOEXEC\0Exec format error"; break;
@@pp_endif@@
@@pp_ifdef EBADF@@
	case EBADF:           result = "EBADF\0Bad file number"; break;
@@pp_endif@@
@@pp_ifdef ECHILD@@
	case ECHILD:          result = "ECHILD\0No child processes"; break;
@@pp_endif@@
@@pp_ifdef EAGAIN@@
	case EAGAIN:          result = "EAGAIN\0Try again"; break;
@@pp_endif@@
@@pp_ifdef ENOMEM@@
	case ENOMEM:          result = "ENOMEM\0Out of memory"; break;
@@pp_endif@@
@@pp_ifdef EACCES@@
	case EACCES:          result = "EACCES\0Permission denied"; break;
@@pp_endif@@
@@pp_ifdef EFAULT@@
	case EFAULT:          result = "EFAULT\0Bad address"; break;
@@pp_endif@@
@@pp_ifdef EBUSY@@
	case EBUSY:           result = "EBUSY\0Device or resource busy"; break;
@@pp_endif@@
@@pp_ifdef EEXIST@@
	case EEXIST:          result = "EEXIST\0File exists"; break;
@@pp_endif@@
@@pp_ifdef EXDEV@@
	case EXDEV:           result = "EXDEV\0Cross-device link"; break;
@@pp_endif@@
@@pp_ifdef ENODEV@@
	case ENODEV:          result = "ENODEV\0No such device"; break;
@@pp_endif@@
@@pp_ifdef ENOTDIR@@
	case ENOTDIR:         result = "ENOTDIR\0Not a directory"; break;
@@pp_endif@@
@@pp_ifdef EISDIR@@
	case EISDIR:          result = "EISDIR\0Is a directory"; break;
@@pp_endif@@
@@pp_ifdef ENFILE@@
	case ENFILE:          result = "ENFILE\0File table overflow"; break;
@@pp_endif@@
@@pp_ifdef EMFILE@@
	case EMFILE:          result = "EMFILE\0Too many open files"; break;
@@pp_endif@@
@@pp_ifdef ENOTTY@@
	case ENOTTY:          result = "ENOTTY\0Not a typewriter"; break;
@@pp_endif@@
@@pp_ifdef EFBIG@@
	case EFBIG:           result = "EFBIG\0File too large"; break;
@@pp_endif@@
@@pp_ifdef ENOSPC@@
	case ENOSPC:          result = "ENOSPC\0No space left on device"; break;
@@pp_endif@@
@@pp_ifdef ESPIPE@@
	case ESPIPE:          result = "ESPIPE\0Illegal seek"; break;
@@pp_endif@@
@@pp_ifdef EROFS@@
	case EROFS:           result = "EROFS\0Read-only file system"; break;
@@pp_endif@@
@@pp_ifdef EMLINK@@
	case EMLINK:          result = "EMLINK\0Too many links"; break;
@@pp_endif@@
@@pp_ifdef EPIPE@@
	case EPIPE:           result = "EPIPE\0Broken pipe"; break;
@@pp_endif@@
@@pp_ifdef EDOM@@
	case EDOM:            result = "EDOM\0Math argument out of domain of func"; break;
@@pp_endif@@
@@pp_ifdef ENAMETOOLONG@@
	case ENAMETOOLONG:    result = "ENAMETOOLONG\0File name too long"; break;
@@pp_endif@@
@@pp_ifdef ENOLCK@@
	case ENOLCK:          result = "ENOLCK\0No record locks available"; break;
@@pp_endif@@
@@pp_ifdef ENOSYS@@
	case ENOSYS:          result = "ENOSYS\0Function not implemented"; break;
@@pp_endif@@
@@pp_ifdef ENOTEMPTY@@
	case ENOTEMPTY:       result = "ENOTEMPTY\0Directory not empty"; break;
@@pp_endif@@
@@pp_ifdef EINVAL@@
	case EINVAL:          result = "EINVAL\0Invalid argument"; break;
@@pp_endif@@
@@pp_ifdef ERANGE@@
	case ERANGE:          result = "ERANGE\0Math result not representable"; break;
@@pp_endif@@
@@pp_ifdef EILSEQ@@
	case EILSEQ:          result = "EILSEQ\0Illegal byte sequence"; break;
@@pp_endif@@
@@pp_ifdef EDEADLOCK@@
	case EDEADLOCK:       result = "EDEADLOCK\0Resource deadlock would occur"; break;
@@pp_endif@@
@@pp_ifdef EADDRINUSE@@
	case EADDRINUSE:      result = "EADDRINUSE\0Address already in use"; break;
@@pp_endif@@
@@pp_ifdef EADDRNOTAVAIL@@
	case EADDRNOTAVAIL:   result = "EADDRNOTAVAIL\0Cannot assign requested address"; break;
@@pp_endif@@
@@pp_ifdef EAFNOSUPPORT@@
	case EAFNOSUPPORT:    result = "EAFNOSUPPORT\0Address family not supported by protocol"; break;
@@pp_endif@@
@@pp_ifdef EALREADY@@
	case EALREADY:        result = "EALREADY\0Operation already in progress"; break;
@@pp_endif@@
@@pp_ifdef EBADMSG@@
	case EBADMSG:         result = "EBADMSG\0Not a data message"; break;
@@pp_endif@@
@@pp_ifdef ECANCELED@@
	case ECANCELED:       result = "ECANCELED\0Operation Canceled"; break;
@@pp_endif@@
@@pp_ifdef ECONNABORTED@@
	case ECONNABORTED:    result = "ECONNABORTED\0Software caused connection abort"; break;
@@pp_endif@@
@@pp_ifdef ECONNREFUSED@@
	case ECONNREFUSED:    result = "ECONNREFUSED\0Connection refused"; break;
@@pp_endif@@
@@pp_ifdef ECONNRESET@@
	case ECONNRESET:      result = "ECONNRESET\0Connection reset by peer"; break;
@@pp_endif@@
@@pp_ifdef EDESTADDRREQ@@
	case EDESTADDRREQ:    result = "EDESTADDRREQ\0Destination address required"; break;
@@pp_endif@@
@@pp_ifdef EHOSTUNREACH@@
	case EHOSTUNREACH:    result = "EHOSTUNREACH\0No route to host"; break;
@@pp_endif@@
@@pp_ifdef EIDRM@@
	case EIDRM:           result = "EIDRM\0Identifier removed"; break;
@@pp_endif@@
@@pp_ifdef EINPROGRESS@@
	case EINPROGRESS:     result = "EINPROGRESS\0Operation now in progress"; break;
@@pp_endif@@
@@pp_ifdef EISCONN@@
	case EISCONN:         result = "EISCONN\0Transport endpoint is already connected"; break;
@@pp_endif@@
@@pp_ifdef ELOOP@@
	case ELOOP:           result = "ELOOP\0Too many symbolic links encountered"; break;
@@pp_endif@@
@@pp_ifdef EMSGSIZE@@
	case EMSGSIZE:        result = "EMSGSIZE\0Message too long"; break;
@@pp_endif@@
@@pp_ifdef ENETDOWN@@
	case ENETDOWN:        result = "ENETDOWN\0Network is down"; break;
@@pp_endif@@
@@pp_ifdef ENETRESET@@
	case ENETRESET:       result = "ENETRESET\0Network dropped connection because of reset"; break;
@@pp_endif@@
@@pp_ifdef ENETUNREACH@@
	case ENETUNREACH:     result = "ENETUNREACH\0Network is unreachable"; break;
@@pp_endif@@
@@pp_ifdef ENOBUFS@@
	case ENOBUFS:         result = "ENOBUFS\0No buffer space available"; break;
@@pp_endif@@
@@pp_ifdef ENODATA@@
	case ENODATA:         result = "ENODATA\0No data available"; break;
@@pp_endif@@
@@pp_ifdef ENOLINK@@
	case ENOLINK:         result = "ENOLINK\0Link has been severed"; break;
@@pp_endif@@
@@pp_ifdef ENOMSG@@
	case ENOMSG:          result = "ENOMSG\0No message of desired type"; break;
@@pp_endif@@
@@pp_ifdef ENOPROTOOPT@@
	case ENOPROTOOPT:     result = "ENOPROTOOPT\0Protocol not available"; break;
@@pp_endif@@
@@pp_ifdef ENOSR@@
	case ENOSR:           result = "ENOSR\0Out of streams resources"; break;
@@pp_endif@@
@@pp_ifdef ENOSTR@@
	case ENOSTR:          result = "ENOSTR\0Device not a stream"; break;
@@pp_endif@@
@@pp_ifdef ENOTCONN@@
	case ENOTCONN:        result = "ENOTCONN\0Transport endpoint is not connected"; break;
@@pp_endif@@
@@pp_ifdef ENOTRECOVERABLE@@
	case ENOTRECOVERABLE: result = "ENOTRECOVERABLE\0State not recoverable"; break;
@@pp_endif@@
@@pp_ifdef ENOTSOCK@@
	case ENOTSOCK:        result = "ENOTSOCK\0Socket operation on non-socket"; break;
@@pp_endif@@
@@pp_ifdef ENOTSUP@@
	case ENOTSUP:         result = "ENOTSUP\0Not supported"; break;
@@pp_endif@@
@@pp_ifdef EOPNOTSUPP@@
	case EOPNOTSUPP:      result = "EOPNOTSUPP\0Operation not supported on transport endpoint"; break;
@@pp_endif@@
@@pp_ifdef EOTHER@@
	case EOTHER:          result = "EOTHER\0Other"; break;
@@pp_endif@@
@@pp_ifdef EOVERFLOW@@
	case EOVERFLOW:       result = "EOVERFLOW\0Value too large for defined data type"; break;
@@pp_endif@@
@@pp_ifdef EOWNERDEAD@@
	case EOWNERDEAD:      result = "EOWNERDEAD\0Owner died"; break;
@@pp_endif@@
@@pp_ifdef EPROTO@@
	case EPROTO:          result = "EPROTO\0Protocol error"; break;
@@pp_endif@@
@@pp_ifdef EPROTONOSUPPORT@@
	case EPROTONOSUPPORT: result = "EPROTONOSUPPORT\0Protocol not supported"; break;
@@pp_endif@@
@@pp_ifdef EPROTOTYPE@@
	case EPROTOTYPE:      result = "EPROTOTYPE\0Protocol wrong type for socket"; break;
@@pp_endif@@
@@pp_ifdef ETIME@@
	case ETIME:           result = "ETIME\0Timer expired"; break;
@@pp_endif@@
@@pp_ifdef ETIMEDOUT@@
	case ETIMEDOUT:       result = "ETIMEDOUT\0Connection timed out"; break;
@@pp_endif@@
@@pp_ifdef ETXTBSY@@
	case ETXTBSY:         result = "ETXTBSY\0Text file busy"; break;
@@pp_endif@@
@@pp_ifdef EFTYPE@@
	case EFTYPE:          result = "EFTYPE\0Inappropriate file type or format"; break;
@@pp_endif@@
@@pp_ifdef ENMFILE@@
	case ENMFILE:         result = "ENMFILE\0No more files"; break;
@@pp_endif@@
@@pp_ifdef EPFNOSUPPORT@@
	case EPFNOSUPPORT:    result = "EPFNOSUPPORT\0Protocol family not supported"; break;
@@pp_endif@@
@@pp_ifdef EHOSTDOWN@@
	case EHOSTDOWN:       result = "EHOSTDOWN\0Host is down"; break;
@@pp_endif@@
@@pp_ifdef ETOOMANYREFS@@
	case ETOOMANYREFS:    result = "ETOOMANYREFS\0Too many references: cannot splice"; break;
@@pp_endif@@
@@pp_ifdef EDQUOT@@
	case EDQUOT:          result = "EDQUOT\0Quota exceeded"; break;
@@pp_endif@@
@@pp_ifdef ESTALE@@
	case ESTALE:          result = "ESTALE\0Stale file handle"; break;
@@pp_endif@@
@@pp_ifdef ENOSHARE@@
	case ENOSHARE:        result = "ENOSHARE\0No such host or network path"; break;
@@pp_endif@@
@@pp_ifdef ECASECLASH@@
	case ECASECLASH:      result = "ECASECLASH\0Filename exists with different case"; break;
@@pp_endif@@
@@pp_ifdef ENOTBLK@@
	case ENOTBLK:         result = "ENOTBLK\0Block device required"; break;
@@pp_endif@@
@@pp_ifdef ECHRNG@@
	case ECHRNG:          result = "ECHRNG\0Channel number out of range"; break;
@@pp_endif@@
@@pp_ifdef EL2NSYNC@@
	case EL2NSYNC:        result = "EL2NSYNC\0Level 2 not synchronized"; break;
@@pp_endif@@
@@pp_ifdef EL3HLT@@
	case EL3HLT:          result = "EL3HLT\0Level 3 halted"; break;
@@pp_endif@@
@@pp_ifdef EL3RST@@
	case EL3RST:          result = "EL3RST\0Level 3 reset"; break;
@@pp_endif@@
@@pp_ifdef ELNRNG@@
	case ELNRNG:          result = "ELNRNG\0Link number out of range"; break;
@@pp_endif@@
@@pp_ifdef EUNATCH@@
	case EUNATCH:         result = "EUNATCH\0Protocol driver not attached"; break;
@@pp_endif@@
@@pp_ifdef ENOCSI@@
	case ENOCSI:          result = "ENOCSI\0No CSI structure available"; break;
@@pp_endif@@
@@pp_ifdef EL2HLT@@
	case EL2HLT:          result = "EL2HLT\0Level 2 halted"; break;
@@pp_endif@@
@@pp_ifdef EBADE@@
	case EBADE:           result = "EBADE\0Invalid exchange"; break;
@@pp_endif@@
@@pp_ifdef EBADR@@
	case EBADR:           result = "EBADR\0Invalid request descriptor"; break;
@@pp_endif@@
@@pp_ifdef EXFULL@@
	case EXFULL:          result = "EXFULL\0Exchange full"; break;
@@pp_endif@@
@@pp_ifdef ENOANO@@
	case ENOANO:          result = "ENOANO\0No anode"; break;
@@pp_endif@@
@@pp_ifdef EBADRQC@@
	case EBADRQC:         result = "EBADRQC\0Invalid request code"; break;
@@pp_endif@@
@@pp_ifdef EBADSLT@@
	case EBADSLT:         result = "EBADSLT\0Invalid slot"; break;
@@pp_endif@@
@@pp_ifdef EBFONT@@
	case EBFONT:          result = "EBFONT\0Bad font file fmt"; break;
@@pp_endif@@
@@pp_ifdef ENONET@@
	case ENONET:          result = "ENONET\0Machine is not on the network"; break;
@@pp_endif@@
@@pp_ifdef ENOPKG@@
	case ENOPKG:          result = "ENOPKG\0Package not installed"; break;
@@pp_endif@@
@@pp_ifdef EREMOTE@@
	case EREMOTE:         result = "EREMOTE\0The object is remote"; break;
@@pp_endif@@
@@pp_ifdef EADV@@
	case EADV:            result = "EADV\0Advertise error"; break;
@@pp_endif@@
@@pp_ifdef ESRMNT@@
	case ESRMNT:          result = "ESRMNT\0Srmount error"; break;
@@pp_endif@@
@@pp_ifdef ECOMM@@
	case ECOMM:           result = "ECOMM\0Communication error on send"; break;
@@pp_endif@@
@@pp_ifdef ELBIN@@
	case ELBIN:           result = "ELBIN\0Inode is remote (not really error)"; break;
@@pp_endif@@
@@pp_ifdef EDOTDOT@@
	case EDOTDOT:         result = "EDOTDOT\0Cross mount point (not really error)"; break;
@@pp_endif@@
@@pp_ifdef ENOTUNIQ@@
	case ENOTUNIQ:        result = "ENOTUNIQ\0Given log. name not unique"; break;
@@pp_endif@@
@@pp_ifdef EBADFD@@
	case EBADFD:          result = "EBADFD\0f.d. invalid for this operation"; break;
@@pp_endif@@
@@pp_ifdef EREMCHG@@
	case EREMCHG:         result = "EREMCHG\0Remote address changed"; break;
@@pp_endif@@
@@pp_ifdef ELIBACC@@
	case ELIBACC:         result = "ELIBACC\0Can't access a needed shared lib"; break;
@@pp_endif@@
@@pp_ifdef ELIBBAD@@
	case ELIBBAD:         result = "ELIBBAD\0Accessing a corrupted shared lib"; break;
@@pp_endif@@
@@pp_ifdef ELIBSCN@@
	case ELIBSCN:         result = "ELIBSCN\0.lib section in a.out corrupted"; break;
@@pp_endif@@
@@pp_ifdef ELIBMAX@@
	case ELIBMAX:         result = "ELIBMAX\0Attempting to link in too many libs"; break;
@@pp_endif@@
@@pp_ifdef ELIBEXEC@@
	case ELIBEXEC:        result = "ELIBEXEC\0Attempting to exec a shared library"; break;
@@pp_endif@@
@@pp_ifdef ESHUTDOWN@@
	case ESHUTDOWN:       result = "ESHUTDOWN\0Can't send after socket shutdown"; break;
@@pp_endif@@
@@pp_ifdef ESOCKTNOSUPPORT@@
	case ESOCKTNOSUPPORT: result = "ESOCKTNOSUPPORT\0Socket type not supported"; break;
@@pp_endif@@
@@pp_ifdef EPROCLIM@@
	case EPROCLIM:        result = "EPROCLIM\0Process limit reached"; break;
@@pp_endif@@
@@pp_ifdef EUSERS@@
	case EUSERS:          result = "EUSERS\0Too many users"; break;
@@pp_endif@@
@@pp_ifdef ENOMEDIUM@@
	case ENOMEDIUM:       result = "ENOMEDIUM\0No medium (in tape drive)"; break;
@@pp_endif@@
@@pp_ifdef ESTRPIPE@@
	case ESTRPIPE:        result = "ESTRPIPE\0Streams pipe error"; break;
@@pp_endif@@
@@pp_ifdef EMULTIHOP@@
	case EMULTIHOP:       result = "EMULTIHOP\0Multihop attempted"; break;
@@pp_endif@@
@@pp_ifdef ERESTART@@
	case ERESTART:        result = "ERESTART\0Interrupted system call should be restarted"; break;
@@pp_endif@@
@@pp_ifdef EUCLEAN@@
	case EUCLEAN:         result = "EUCLEAN\0Structure needs cleaning"; break;
@@pp_endif@@
@@pp_ifdef ENOTNAM@@
	case ENOTNAM:         result = "ENOTNAM\0Not a XENIX named type file"; break;
@@pp_endif@@
@@pp_ifdef ENAVAIL@@
	case ENAVAIL:         result = "ENAVAIL\0No XENIX semaphores available"; break;
@@pp_endif@@
@@pp_ifdef EISNAM@@
	case EISNAM:          result = "EISNAM\0Is a named type file"; break;
@@pp_endif@@
@@pp_ifdef EREMOTEIO@@
	case EREMOTEIO:       result = "EREMOTEIO\0Remote I/O error"; break;
@@pp_endif@@
@@pp_ifdef EMEDIUMTYPE@@
	case EMEDIUMTYPE:     result = "EMEDIUMTYPE\0Wrong medium type"; break;
@@pp_endif@@
@@pp_ifdef ENOKEY@@
	case ENOKEY:          result = "ENOKEY\0Required key not available"; break;
@@pp_endif@@
@@pp_ifdef EKEYEXPIRED@@
	case EKEYEXPIRED:     result = "EKEYEXPIRED\0Key has expired"; break;
@@pp_endif@@
@@pp_ifdef EKEYREVOKED@@
	case EKEYREVOKED:     result = "EKEYREVOKED\0Key has been revoked"; break;
@@pp_endif@@
@@pp_ifdef EKEYREJECTED@@
	case EKEYREJECTED:    result = "EKEYREJECTED\0Key was rejected by service"; break;
@@pp_endif@@
@@pp_ifdef ERFKILL@@
	case ERFKILL:         result = "ERFKILL\0Operation not possible due to RF-kill"; break;
@@pp_endif@@
@@pp_ifdef EHWPOISON@@
	case EHWPOISON:       result = "EHWPOISON\0Memory page has hardware error"; break;
@@pp_endif@@
@@pp_if defined(STRUNCATE) && (!defined(ERANGE) || STRUNCATE != ERANGE)@@
	case STRUNCATE:       result = "STRUNCATE\0Truncated"; break;
@@pp_endif@@
@@pp_if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)@@
	case EWOULDBLOCK:     result = "EWOULDBLOCK\0Operation would block"; break;
@@pp_endif@@
@@pp_if defined(EDEADLK) && (!defined(EDEADLOCK) || EDEADLOCK != EDEADLK)@@
	case EDEADLK:         result = "EDEADLK\0Resource deadlock would occur"; break;
@@pp_endif@@

	default:
		result = NULL;
		break;
	}
	return result;
@@pp_endif@@
}

@@>> sigabbrev_np(3)
@@Return the name of a given signal, _without_ the leading `SIG*' prefix.
@@When the given  `signo' isn't recognized,  `NULL' is returned  instead.
[[const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[kernel, alias("signalname", "strsigno")]]
[[if(!defined(__KERNEL__)), export_as("signalname", "strsigno")]]
[[crt_dos_variant({ impl:{ return libc_sigabbrev_np(libd_signo_dos2kos(signo)); }})]]
[[section(".text.crt{|.dos}.errno")]]
[[impl_include("<hybrid/typecore.h>", "<asm/os/signal.h>")]]
char const *sigabbrev_np($signo_t signo) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosSignoMappings: {int: (string, string)} = Dict();
local rtmin = none;
local rtmax = none;
with (local fp = File.open("../../../include/asm/os/kos/signal.h")) {
	for (local l: fp) {
		l = l.strip();
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __SIG%[^ ] %[^/ ] /" "*%[^]")...;
		} catch (...) {
			try {
				name, value = l.scanf(" # define __SIG%[^ ] %[^]")...;
			} catch (...) {
				continue;
			}
			comment = "";
		}
		if (name.startswith("_"))
			continue;
		value = value.strip();
		if (name == "RTMIN") {
			rtmin = int(value);
		} else if (name == "RTMAX") {
			rtmax = int(value);
		} else {
			comment = comment.partition("*" "/")[0].strip();
			while (comment.startswith("["))
				comment = comment.partition("]")[2].lstrip();
			comment = comment.rstrip(".").strip();
			if ("--" in comment) {
				comment = comment.partition("--")[0].strip();
			} else {
				while (comment.endswith(")"))
					comment = comment[:comment.rindex("(")].strip();
			}
			value = try int(value) catch (...) none;
			if (value is none)
				continue;
			if (value in kosSignoMappings)
				continue;
			kosSignoMappings[value] = (name, comment);
		}
	}
}
assert rtmin !is none;
assert rtmax !is none;
assert rtmin <= rtmax;

local sigmax = kosSignoMappings.keys > ...;
if (sigmax < rtmax)
	sigmax = rtmax;

print("#define HAVE_KOS_SIGNO_VALUES");
for (local ids: kosSignoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined(__SIG{0}) || __SIG{0} != {1}".format({ kosSignoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_SIGNO_VALUES");
	print("@@pp_endif@@");
}
print("@@pp_if __SIGRTMIN != ", rtmin, " || __SIGRTMAX != ", rtmax, "@@");
print("#undef HAVE_KOS_SIGNO_VALUES");
print("@@pp_endif@@");

// Generate names+descriptors for real-time signals.
for (local id: [rtmin:rtmax]) {
	local desc = f"RTMIN+{id - rtmin}";
	kosSignoMappings[id] = (desc, desc.lower());
}
kosSignoMappings[rtmin] = ("RTMIN", "rtmin");
kosSignoMappings[rtmax] = ("RTMAX", "rtmax");


print("@@pp_ifdef HAVE_KOS_SIGNO_VALUES@@");
print("	static char const signo_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:sigmax + 1]) {
	local name, comment = kosSignoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != sigmax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:sigmax + 1]) {
	if (kosSignoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const signo_offsets[", (sigmax + 1), "] = {");
for (local i: [:sigmax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define HAVE_KOS_SIGNO_VALUES
@@pp_if !defined(__SIGHUP) || __SIGHUP != 1 || !defined(__SIGINT) || __SIGINT != 2 || !defined(__SIGQUIT) || __SIGQUIT != 3 || !defined(__SIGILL) || __SIGILL != 4@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGTRAP) || __SIGTRAP != 5 || !defined(__SIGABRT) || __SIGABRT != 6 || !defined(__SIGBUS) || __SIGBUS != 7 || !defined(__SIGFPE) || __SIGFPE != 8@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGKILL) || __SIGKILL != 9 || !defined(__SIGUSR1) || __SIGUSR1 != 10 || !defined(__SIGSEGV) || __SIGSEGV != 11 || !defined(__SIGUSR2) || __SIGUSR2 != 12@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGPIPE) || __SIGPIPE != 13 || !defined(__SIGALRM) || __SIGALRM != 14 || !defined(__SIGTERM) || __SIGTERM != 15 || !defined(__SIGSTKFLT) || __SIGSTKFLT != 16@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGCHLD) || __SIGCHLD != 17 || !defined(__SIGCONT) || __SIGCONT != 18 || !defined(__SIGSTOP) || __SIGSTOP != 19 || !defined(__SIGTSTP) || __SIGTSTP != 20@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGTTIN) || __SIGTTIN != 21 || !defined(__SIGTTOU) || __SIGTTOU != 22 || !defined(__SIGURG) || __SIGURG != 23 || !defined(__SIGXCPU) || __SIGXCPU != 24@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGXFSZ) || __SIGXFSZ != 25 || !defined(__SIGVTALRM) || __SIGVTALRM != 26 || !defined(__SIGPROF) || __SIGPROF != 27 || !defined(__SIGWINCH) || __SIGWINCH != 28@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if !defined(__SIGIO) || __SIGIO != 29 || !defined(__SIGPWR) || __SIGPWR != 30 || !defined(__SIGSYS) || __SIGSYS != 31@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_if __SIGRTMIN != 32 || __SIGRTMAX != 64@@
#undef HAVE_KOS_SIGNO_VALUES
@@pp_endif@@
@@pp_ifdef HAVE_KOS_SIGNO_VALUES@@
	static char const signo_strtab[] =
	"HUP\0Hangup\0"
	"INT\0Interrupt\0"
	"QUIT\0Quit\0"
	"ILL\0Illegal instruction\0"
	"TRAP\0Trace/breakpoint trap\0"
	"ABRT\0Aborted\0"
	"BUS\0Bus error\0"
	"FPE\0Floating point exception\0"
	"KILL\0Killed\0"
	"USR1\0User defined signal 1\0"
	"SEGV\0Segmentation violation\0"
	"USR2\0User defined signal 2\0"
	"PIPE\0Broken pipe\0"
	"ALRM\0Alarm clock\0"
	"TERM\0Terminated\0"
	"STKFLT\0Stack fault\0"
	"CHLD\0Child exited\0"
	"CONT\0Continued\0"
	"STOP\0Stopped (signal)\0"
	"TSTP\0Stopped\0"
	"TTIN\0Stopped (tty input)\0"
	"TTOU\0Stopped (tty output)\0"
	"URG\0Urgent I/O condition\0"
	"XCPU\0CPU time limit exceeded\0"
	"XFSZ\0File size limit exceeded\0"
	"VTALRM\0Virtual timer expired\0"
	"PROF\0Profiling timer expired\0"
	"WINCH\0Window changed\0"
	"IO\0I/O possible\0"
	"PWR\0Power failure\0"
	"SYS\0Bad system call\0"
	"RTMIN\0rtmin\0"
	"RTMIN+1\0rtmin+1\0"
	"RTMIN+2\0rtmin+2\0"
	"RTMIN+3\0rtmin+3\0"
	"RTMIN+4\0rtmin+4\0"
	"RTMIN+5\0rtmin+5\0"
	"RTMIN+6\0rtmin+6\0"
	"RTMIN+7\0rtmin+7\0"
	"RTMIN+8\0rtmin+8\0"
	"RTMIN+9\0rtmin+9\0"
	"RTMIN+10\0rtmin+10\0"
	"RTMIN+11\0rtmin+11\0"
	"RTMIN+12\0rtmin+12\0"
	"RTMIN+13\0rtmin+13\0"
	"RTMIN+14\0rtmin+14\0"
	"RTMIN+15\0rtmin+15\0"
	"RTMIN+16\0rtmin+16\0"
	"RTMIN+17\0rtmin+17\0"
	"RTMIN+18\0rtmin+18\0"
	"RTMIN+19\0rtmin+19\0"
	"RTMIN+20\0rtmin+20\0"
	"RTMIN+21\0rtmin+21\0"
	"RTMIN+22\0rtmin+22\0"
	"RTMIN+23\0rtmin+23\0"
	"RTMIN+24\0rtmin+24\0"
	"RTMIN+25\0rtmin+25\0"
	"RTMIN+26\0rtmin+26\0"
	"RTMIN+27\0rtmin+27\0"
	"RTMIN+28\0rtmin+28\0"
	"RTMIN+29\0rtmin+29\0"
	"RTMIN+30\0rtmin+30\0"
	"RTMIN+31\0rtmin+31\0"
	"RTMAX\0rtmax"
	"";
	static uint16_t const signo_offsets[65] = {
		1204, 0, 11, 25, 35, 59, 86, 99, 113, 142, 154, 181, 209, 236, 253, 270,
		286, 305, 323, 338, 360, 373, 398, 424, 449, 478, 508, 537, 566, 587, 603, 621,
		641, 653, 669, 685, 701, 717, 733, 749, 765, 781, 797, 815, 833, 851, 869, 887,
		905, 923, 941, 959, 977, 995, 1013, 1031, 1049, 1067, 1085, 1103, 1121, 1139, 1157, 1175,
		1193,
	};
/*[[[end]]]*/
	char const *result;
	if ((unsigned int)signo >= COMPILER_LENOF(signo_offsets))
		return NULL;
	result = &signo_strtab[signo_offsets[signo]];
	if (!*result)
		result = NULL;
	return result;
@@pp_else@@
	char const *result;
	switch (signo) {

@@pp_ifdef SIGABRT_COMPAT@@
	case SIGABRT_COMPAT: result = "ABRT_COMPAT\0Aborted"; break;
@@pp_endif@@
@@pp_ifdef SIGBREAK@@
	case SIGBREAK:       result = "BREAK\0Stopped (tty input)"; break;
@@pp_endif@@
@@pp_ifdef SIGHUP@@
	case SIGHUP:         result = "HUP\0Hangup"; break;
@@pp_endif@@
@@pp_ifdef SIGINT@@
	case SIGINT:         result = "INT\0Interrupt"; break;
@@pp_endif@@
@@pp_ifdef SIGQUIT@@
	case SIGQUIT:        result = "QUIT\0Quit"; break;
@@pp_endif@@
@@pp_ifdef SIGILL@@
	case SIGILL:         result = "ILL\0Illegal instruction"; break;
@@pp_endif@@
@@pp_ifdef SIGTRAP@@
	case SIGTRAP:        result = "TRAP\0Trace/breakpoint trap"; break;
@@pp_endif@@
@@pp_ifdef SIGABRT@@
	case SIGABRT:        result = "ABRT\0Aborted"; break;
@@pp_endif@@
@@pp_ifdef SIGBUS@@
	case SIGBUS:         result = "BUS\0Bus error"; break;
@@pp_endif@@
@@pp_ifdef SIGFPE@@
	case SIGFPE:         result = "FPE\0Floating point exception"; break;
@@pp_endif@@
@@pp_ifdef SIGKILL@@
	case SIGKILL:        result = "KILL\0Killed"; break;
@@pp_endif@@
@@pp_ifdef SIGUSR1@@
	case SIGUSR1:        result = "USR1\0User defined signal 1"; break;
@@pp_endif@@
@@pp_ifdef SIGSEGV@@
	case SIGSEGV:        result = "SEGV\0Segmentation violation"; break;
@@pp_endif@@
@@pp_ifdef SIGUSR2@@
	case SIGUSR2:        result = "USR2\0User defined signal 2"; break;
@@pp_endif@@
@@pp_ifdef SIGPIPE@@
	case SIGPIPE:        result = "PIPE\0Broken pipe"; break;
@@pp_endif@@
@@pp_ifdef SIGALRM@@
	case SIGALRM:        result = "ALRM\0Alarm clock"; break;
@@pp_endif@@
@@pp_ifdef SIGTERM@@
	case SIGTERM:        result = "TERM\0Terminated"; break;
@@pp_endif@@
@@pp_ifdef SIGSTKFLT@@
	case SIGSTKFLT:      result = "STKFLT\0Stack fault"; break;
@@pp_endif@@
@@pp_ifdef SIGCHLD@@
	case SIGCHLD:        result = "CHLD\0Child exited"; break;
@@pp_endif@@
@@pp_ifdef SIGCONT@@
	case SIGCONT:        result = "CONT\0Continued"; break;
@@pp_endif@@
@@pp_ifdef SIGSTOP@@
	case SIGSTOP:        result = "STOP\0Stopped (signal)"; break;
@@pp_endif@@
@@pp_ifdef SIGTSTP@@
	case SIGTSTP:        result = "TSTP\0Stopped"; break;
@@pp_endif@@
@@pp_ifdef SIGTTOU@@
	case SIGTTOU:        result = "TTOU\0Stopped (tty output)"; break;
@@pp_endif@@
@@pp_ifdef SIGURG@@
	case SIGURG:         result = "URG\0Urgent I/O condition"; break;
@@pp_endif@@
@@pp_ifdef SIGXCPU@@
	case SIGXCPU:        result = "XCPU\0CPU time limit exceeded"; break;
@@pp_endif@@
@@pp_ifdef SIGXFSZ@@
	case SIGXFSZ:        result = "XFSZ\0File size limit exceeded"; break;
@@pp_endif@@
@@pp_ifdef SIGVTALRM@@
	case SIGVTALRM:      result = "VTALRM\0Virtual timer expired"; break;
@@pp_endif@@
@@pp_ifdef SIGPROF@@
	case SIGPROF:        result = "PROF\0Profiling timer expired"; break;
@@pp_endif@@
@@pp_ifdef SIGWINCH@@
	case SIGWINCH:       result = "WINCH\0Window changed"; break;
@@pp_endif@@
@@pp_ifdef SIGIO@@
	case SIGIO:          result = "IO\0I/O possible"; break;
@@pp_endif@@
@@pp_ifdef SIGSYS@@
	case SIGSYS:         result = "SYS\0Bad system call"; break;
@@pp_endif@@
@@pp_ifdef SIGEMT@@
	case SIGEMT:         result = "EMT\0EMT instruction"; break;
@@pp_endif@@
@@pp_ifdef SIGLOST@@
	case SIGLOST:        result = "LOST\0Resource lost"; break;
@@pp_endif@@
@@pp_if defined(SIGTTIN) && (!defined(SIGBREAK) || SIGBREAK != SIGTTIN)@@
	case SIGTTIN:        result = "TTIN\0Stopped (tty input)"; break;
@@pp_endif@@
@@pp_if defined(SIGCLD) && (!defined(SIGCHLD) || SIGCLD != SIGCHLD)@@
	case SIGCLD:         result = "CLD\0Child exited"; break;
@@pp_endif@@
@@pp_if defined(SIGIOT) && (!defined(SIGABRT) || SIGIOT != SIGABRT)@@
	case SIGIOT:         result = "IOT\0IOT trap"; break;
@@pp_endif@@
@@pp_if defined(SIGPOLL) && (!defined(SIGIO) || SIGPOLL != SIGIO)@@
	case SIGPOLL:        result = "POLL\0Pollable event occurred"; break;
@@pp_endif@@
@@pp_if defined(SIGPWR) && (!defined(SIGLOST) || SIGPWR != SIGLOST)@@
	case SIGPWR:         result = "PWR\0Power failure"; break;
@@pp_endif@@

	default:
		result = NULL;
		break;
	}
	return result;
@@pp_endif@@
}

@@>> sigdescr_np(3)
@@Return a description for the given signal.
@@If the given `signo' isn't recognized, return `NULL' instead.
[[const, wunused, nothrow]]
[[kernel, decl_include("<bits/types.h>")]]
[[impl_include("<asm/os/signal.h>"), impl_prefix(
@@pp_ifndef __BUILDING_LIBC@@
@@pp_if defined(__CRT_HAVE__sys_siglist)@@
@@pp_if         !defined(@_sys_siglist@)@@
@@pp_ifdef __NSIG@@
__CSDECLARE2(,char const *const @_sys_siglist@[__NSIG],@_sys_siglist@)
@@pp_else@@
__CSDECLARE2(,char const *const @_sys_siglist@[],@_sys_siglist@)
@@pp_endif@@
#define @_sys_siglist@ @_sys_siglist@
@@pp_endif@@
@@pp_if !defined(@_sys_nsig@) && defined(__CRT_HAVE__sys_nsig)@@
__CSDECLARE(,int,@_sys_nsig@)
#define @_sys_nsig@ @_sys_nsig@
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
), section(".text.crt{|.dos}.errno")]]
[[crt_dos_variant({ impl:{ return libc_sigdescr_np(libd_signo_dos2kos(signo)); }})]]
char const *sigdescr_np($signo_t signo) {
@@pp_if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE__sys_siglist) && (defined(@_sys_nsig@) || defined(__NSIG))@@
@@pp_if defined(@_sys_nsig@)@@
	return (unsigned int)signo < (unsigned int)@_sys_nsig@ ? @_sys_siglist@[signo] : NULL;
@@pp_else@@
	return (unsigned int)signo < (unsigned int)__NSIG ? @_sys_siglist@[signo] : NULL;
@@pp_endif@@
@@pp_elif defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_sigabbrev_np) &&
                                       !defined(__CRT_HAVE_signalname) &&
                                       !defined(__CRT_HAVE_strsigno)) ||
          defined(__CRT_KOS)@@
	char const *result;
	result = sigabbrev_np(signo);
	if (result)
		result = strend(result) + 1;
	return result;
@@pp_else@@
	char const *result;
	switch (signo) {

@@pp_ifdef SIGABRT_COMPAT@@
	case SIGABRT_COMPAT: result = "Aborted"; break;
@@pp_endif@@
@@pp_ifdef SIGBREAK@@
	case SIGBREAK:       result = "Stopped (tty input)"; break;
@@pp_endif@@
@@pp_ifdef SIGHUP@@
	case SIGHUP:         result = "Hangup"; break;
@@pp_endif@@
@@pp_ifdef SIGINT@@
	case SIGINT:         result = "Interrupt"; break;
@@pp_endif@@
@@pp_ifdef SIGQUIT@@
	case SIGQUIT:        result = "Quit"; break;
@@pp_endif@@
@@pp_ifdef SIGILL@@
	case SIGILL:         result = "Illegal instruction"; break;
@@pp_endif@@
@@pp_ifdef SIGTRAP@@
	case SIGTRAP:        result = "Trace/breakpoint trap"; break;
@@pp_endif@@
@@pp_ifdef SIGABRT@@
	case SIGABRT:        result = "Aborted"; break;
@@pp_endif@@
@@pp_ifdef SIGBUS@@
	case SIGBUS:         result = "Bus error"; break;
@@pp_endif@@
@@pp_ifdef SIGFPE@@
	case SIGFPE:         result = "Floating point exception"; break;
@@pp_endif@@
@@pp_ifdef SIGKILL@@
	case SIGKILL:        result = "Killed"; break;
@@pp_endif@@
@@pp_ifdef SIGUSR1@@
	case SIGUSR1:        result = "User defined signal 1"; break;
@@pp_endif@@
@@pp_ifdef SIGSEGV@@
	case SIGSEGV:        result = "Segmentation violation"; break;
@@pp_endif@@
@@pp_ifdef SIGUSR2@@
	case SIGUSR2:        result = "User defined signal 2"; break;
@@pp_endif@@
@@pp_ifdef SIGPIPE@@
	case SIGPIPE:        result = "Broken pipe"; break;
@@pp_endif@@
@@pp_ifdef SIGALRM@@
	case SIGALRM:        result = "Alarm clock"; break;
@@pp_endif@@
@@pp_ifdef SIGTERM@@
	case SIGTERM:        result = "Terminated"; break;
@@pp_endif@@
@@pp_ifdef SIGSTKFLT@@
	case SIGSTKFLT:      result = "Stack fault"; break;
@@pp_endif@@
@@pp_ifdef SIGCHLD@@
	case SIGCHLD:        result = "Child exited"; break;
@@pp_endif@@
@@pp_ifdef SIGCONT@@
	case SIGCONT:        result = "Continued"; break;
@@pp_endif@@
@@pp_ifdef SIGSTOP@@
	case SIGSTOP:        result = "Stopped (signal)"; break;
@@pp_endif@@
@@pp_ifdef SIGTSTP@@
	case SIGTSTP:        result = "Stopped"; break;
@@pp_endif@@
@@pp_ifdef SIGTTOU@@
	case SIGTTOU:        result = "Stopped (tty output)"; break;
@@pp_endif@@
@@pp_ifdef SIGURG@@
	case SIGURG:         result = "Urgent I/O condition"; break;
@@pp_endif@@
@@pp_ifdef SIGXCPU@@
	case SIGXCPU:        result = "CPU time limit exceeded"; break;
@@pp_endif@@
@@pp_ifdef SIGXFSZ@@
	case SIGXFSZ:        result = "File size limit exceeded"; break;
@@pp_endif@@
@@pp_ifdef SIGVTALRM@@
	case SIGVTALRM:      result = "Virtual timer expired"; break;
@@pp_endif@@
@@pp_ifdef SIGPROF@@
	case SIGPROF:        result = "Profiling timer expired"; break;
@@pp_endif@@
@@pp_ifdef SIGWINCH@@
	case SIGWINCH:       result = "Window changed"; break;
@@pp_endif@@
@@pp_ifdef SIGIO@@
	case SIGIO:          result = "I/O possible"; break;
@@pp_endif@@
@@pp_ifdef SIGSYS@@
	case SIGSYS:         result = "Bad system call"; break;
@@pp_endif@@
@@pp_ifdef SIGEMT@@
	case SIGEMT:         result = "EMT instruction"; break;
@@pp_endif@@
@@pp_ifdef SIGLOST@@
	case SIGLOST:        result = "Resource lost"; break;
@@pp_endif@@
@@pp_if defined(SIGTTIN) && (!defined(SIGBREAK) || SIGBREAK != SIGTTIN)@@
	case SIGTTIN:        result = "Stopped (tty input)"; break;
@@pp_endif@@
@@pp_if defined(SIGCLD) && (!defined(SIGCHLD) || SIGCLD != SIGCHLD)@@
	case SIGCLD:         result = "Child exited"; break;
@@pp_endif@@
@@pp_if defined(SIGIOT) && (!defined(SIGABRT) || SIGIOT != SIGABRT)@@
	case SIGIOT:         result = "IOT trap"; break;
@@pp_endif@@
@@pp_if defined(SIGPOLL) && (!defined(SIGIO) || SIGPOLL != SIGIO)@@
	case SIGPOLL:        result = "Pollable event occurred"; break;
@@pp_endif@@
@@pp_if defined(SIGPWR) && (!defined(SIGLOST) || SIGPWR != SIGLOST)@@
	case SIGPWR:         result = "Power failure"; break;
@@pp_endif@@

	default:
		result = NULL;
		break;
	}
	return result;
@@pp_endif@@
}

%#endif /* __USE_GNU */


%
%#ifdef __USE_XOPEN2K
%#ifdef __USE_GNU
[[cold, decl_include("<bits/types.h>")]]
[[export_alias("__strerror_r")]]
[[crt_dos_variant({ impl:{ return libc_strerror_r(libd_errno_dos2kos(errnum), buf, buflen); }})]]
[[section(".text.crt{|.dos}.errno")]]
[[impl_include("<hybrid/__assert.h>")]]
[[nonnull]] char *strerror_r($errno_t errnum, [[nonnull]] char *buf, $size_t buflen) {
	char const *string;
	if (!buf)
		goto fallback;
	if (!buflen)
		goto fallback;
	string = strerrordesc_np(errnum);
	if (string) {
		/* Copy the descriptor text. */
		size_t msg_len = strlen(string) + 1;
		if (msg_len > buflen)
			goto fallback;
		memcpyc(buf, string, msg_len, sizeof(char));
	} else {
		if ((size_t)snprintf(buf, buflen, "Unknown error %d", errnum) >= buflen)
			goto fallback;
	}
	return buf;
fallback:
	return strerror(errnum);
}

%#else /* __USE_GNU */

[[cold, exposed_name("strerror_r"), decl_include("<bits/types.h>")]]
[[crt_dos_variant({ impl:{ return libc___xpg_strerror_r(libd_errno_dos2kos(errnum), buf, buflen); }})]]
[[section(".text.crt{|.dos}.errno")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
$errno_t __xpg_strerror_r($errno_t errnum, [[out(buflen)]] char *buf, $size_t buflen) {
	size_t msg_len;
	char const *string;
	string = strerrordesc_np(errnum);
	if (!buf)
		buflen = 0;
	if (!string) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	/* Copy the descriptor text. */
	msg_len = strlen(string) + 1;
	if (msg_len > buflen) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	memcpyc(buf, string, msg_len, sizeof(char));
	return EOK;
}
%#endif /* !__USE_GNU */
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_MISC

[[leaf, export_as("__strsep_g")]]
char *strsep([[inout]] char **__restrict stringp,
             [[in]] char const *__restrict delim) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !strchr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

@@Same as `memmove(dst, src, num_bytes)'
@@Note that bcopy is called with `dst' and `src' reversed
[[guard, crtbuiltin]]
[[decl_include("<hybrid/typecore.h>")]]
void bcopy([[in(num_bytes)]] void const *src,
           [[out(num_bytes)]] void *dst, $size_t num_bytes) {
	memmove(dst, src, num_bytes);
}

%(auto_source){
/* Prevent bzero()'s call to memset() from being routed back to bzero itself! */
#ifndef LIBC_ARCH_HAVE_BZERO
#undef libc_memset
#endif /* !LIBC_ARCH_HAVE_BZERO */
#ifndef LIBC_ARCH_HAVE_BZEROW
#undef libc_memsetw
#endif /* !LIBC_ARCH_HAVE_BZEROW */
#ifndef LIBC_ARCH_HAVE_BZEROL
#undef libc_memsetl
#endif /* !LIBC_ARCH_HAVE_BZEROL */
#ifndef LIBC_ARCH_HAVE_BZEROQ
#undef libc_memsetq
#endif /* !LIBC_ARCH_HAVE_BZEROQ */
}


%#ifndef __bzero_defined
%#define __bzero_defined
/* Disable [[crtbuiltin]] because gcc translates `__builtin_bzero()' into a call to `memset()'
 * s.a.: https://gcc.gnu.org/legacy-ml/gcc-bugs/2002-01/msg00511.html
 * While I do understand what  is causing GCC to  do this, I still cannot  let it do this  under
 * KOS due to  the fact  that we're  using __CRT_HAVE_*  feature test  macros that  rely on  the
 * compiler not randomly deciding to emit calls to libc function that haven't been white-listed.
 * And  while this could  be fixed by only  calling `__builtin_bzero()' when `__CRT_HAVE_memset'
 * is defined,  doing this  would still  produce  sub-optimal code  because `memset()'  takes  3
 * arguments, while bzero()  only takes 2  (and also doesn't  have to fill  the return  register
 * with any meaningful value)
 * So rather than dealing with that headache, just don't link bzero() against its builtin
 * counterpart! */
[[libc, kernel, /*crtbuiltin,*/ alias("__bzero", "explicit_bzero")]]
[[if(!defined(__KERNEL__)), export_as("__bzero", "explicit_bzero")]]
[[preferred_fastbind(bzero, ["bzero", "__bzero", "explicit_bzero"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_BZERO))]]
[[decl_include("<hybrid/typecore.h>")]]
void bzero([[out(num_bytes)]] void *__restrict dst, $size_t num_bytes) {
	memset(dst, 0, num_bytes);
}
%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(bzero = bzeroc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */
%#endif /* !__bzero_defined */


%
%#ifdef __USE_STRING_BWLQ

[[guard, decl_include("<hybrid/typecore.h>")]]
[[nocrt, leaf, alias("bzero", "__bzero", "explicit_bzero")]]
[[preferred_fastbind(bzero, ["bzero", "__bzero", "explicit_bzero"])]]
[[bind_local_function("bzero")]]
void bzerob([[out(num_bytes)]] void *__restrict dst, $size_t num_bytes);


[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, guard, libc, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_BZEROW))]]
void bzerow([[out(num_words * 2)]] void *__restrict dst, $size_t num_words) {
	memsetw(dst, 0, num_words);
}

[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, guard, libc, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_BZEROL))]]
void bzerol([[out(num_dwords * 4)]] void *__restrict dst, $size_t num_dwords) {
	memsetl(dst, 0, num_dwords);
}

[[guard, pure, wunused, decl_include("<hybrid/typecore.h>")]]
int bcmpb([[in(n_bytes * 1), aligned(1)]] void const *s1,
          [[in(n_bytes * 1), aligned(1)]] void const *s2,
          $size_t n_bytes) = bcmp;

[[guard, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if_fast_defined(bcmpw), preferred_fast_extern_inline("bcmpw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), preferred_fast_extern_inline("bcmpw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(bcmpw), preferred_fast_extern_inline("memcmpw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), preferred_fast_extern_inline("memcmpw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(bcmpw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_BCMPW))]]
[[if(!defined(LIBC_ARCH_HAVE_BCMPW)), crt_intern_alias(memcmpw)]]
[[alias("memcmpw"), bind_local_function("memcmpw")]]
int bcmpw([[in(n_words * 2), aligned(2)]] void const *s1,
          [[in(n_words * 2), aligned(2)]] void const *s2, $size_t n_words) {
	return memcmpw(s1, s2, n_words);
}

[[guard, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if_fast_defined(bcmpl), preferred_fast_extern_inline("bcmpl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), preferred_fast_extern_inline("bcmpl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(bcmpl), preferred_fast_extern_inline("memcmpl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), preferred_fast_extern_inline("memcmpl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(bcmpl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_BCMPL))]]
[[if(!defined(LIBC_ARCH_HAVE_BCMPL)), crt_intern_alias(memcmpl)]]
[[alias("memcmpl"), bind_local_function("memcmpl")]]
int bcmpl([[in(n_dwords * 4), aligned(4)]] void const *s1,
          [[in(n_dwords * 4), aligned(4)]] void const *s2,
          $size_t n_dwords) {
	return memcmpl(s1, s2, n_dwords);
}

%#ifdef __UINT64_TYPE__

[[decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind, guard, libc, kernel, leaf]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_BZEROQ))]]
void bzeroq([[out(num_qwords * 8)]] void *__restrict dst, $size_t num_qwords) {
@@pp_if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8@@
	memsetq(dst, 0, num_qwords);
@@pp_else@@
	bzerol(dst, num_qwords * 2);
@@pp_endif@@
}

[[guard, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if_fast_defined(bcmpq), preferred_fast_extern_inline("bcmpq", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpq@))(s1, s2, n_qwords); })]]
[[if_fast_defined(memcmpq), preferred_fast_extern_inline("bcmpq", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpq@))(s1, s2, n_qwords); })]]
[[if_fast_defined(bcmpq), preferred_fast_extern_inline("memcmpq", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpq@))(s1, s2, n_qwords); })]]
[[if_fast_defined(memcmpq), preferred_fast_extern_inline("memcmpq", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpq@))(s1, s2, n_qwords); })]]
[[if_fast_defined(bcmpq), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@bcmpq@))(s1, s2, n_qwords); })]]
[[if_fast_defined(memcmpq), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpq@))(s1, s2, n_qwords); })]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_BCMPQ))]]
[[if(!defined(LIBC_ARCH_HAVE_BCMPQ)), crt_intern_alias(memcmpq)]]
[[alias("memcmpq"), bind_local_function("memcmpq")]]
int bcmpq([[in(n_qwords * 8), aligned(8)]] void const *s1,
          [[in(n_qwords * 8), aligned(8)]] void const *s2,
          $size_t n_qwords) {
	return memcmpq(s1, s2, n_qwords);
}

%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */


%(auto_source){
/* Restore optimized libc string functions */
#if !defined(LIBC_ARCH_HAVE_BZERO) && defined(__fast_memset_defined)
#define libc_memset(dst, byte, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(dst, byte, n_bytes)
#endif /* !LIBC_ARCH_HAVE_BZERO && __fast_memset_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROW) && defined(__fast_memsetw_defined)
#define libc_memsetw(dst, word, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(dst, word, n_words)
#endif /* !LIBC_ARCH_HAVE_BZEROW && __fast_memsetw_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROL) && defined(__fast_memsetl_defined)
#define libc_memsetl(dst, dword, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(dst, dword, n_dwords)
#endif /* !LIBC_ARCH_HAVE_BZEROL && __fast_memsetl_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROQ) && defined(__fast_memsetq_defined)
#define libc_memsetq(dst, qword, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(dst, qword, n_qwords)
#endif /* !LIBC_ARCH_HAVE_BZEROQ && __fast_memsetq_defined */
}



%
%#ifdef __USE_KOS
[[preferred_fastbind, guard, kernel, libc, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/host.h>")]]
void bzeroc([[out(elem_count * elem_size)]] void *__restrict dst,
            $size_t elem_count, $size_t elem_size) {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		bzero(dst, elem_count);
		break;

	case 2:
		bzerow(dst, elem_count);
		break;

	case 4:
		bzerol(dst, elem_count);
		break;

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		bzeroq(dst, elem_count);
		break;
@@pp_endif@@

	default:
		bzero(dst, elem_count * elem_size);
		break;
	}
@@pp_else@@
	bzero(dst, elem_count * elem_size);
@@pp_endif@@
}

[[guard, decl_include("<hybrid/typecore.h>")]]
[[libc, kernel, pure, wunused]]
[[preferred_fastbind(bcmpc(s1, s2, elem_count, elem_size), ["bcmpc"])]]
[[preferred_fastbind(memcmpc(s1, s2, elem_count, elem_size), ["bcmpc"])]]
[[preferred_fastbind(bcmpc(s1, s2, elem_count, elem_size), ["memcmpc"])]]
[[preferred_fastbind(memcmpc(s1, s2, elem_count, elem_size), ["memcmpc"])]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_BCMPC))]]
[[alias("memcmpc"), bind_local_function("memcmpc")]]
[[impl_include("<hybrid/host.h>")]]
int bcmpc([[in(elem_count * elem_size)]] void const *s1,
          [[in(elem_count * elem_size)]] void const *s2,
          $size_t elem_count, $size_t elem_size) {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return bcmp(s1, s2, elem_count);

	case 2:
		return bcmpw(s1, s2, elem_count);

	case 4:
		return bcmpl(s1, s2, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return bcmpq(s1, s2, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return bcmp(s1, s2, elem_count * elem_size);
}
%#endif /* __USE_KOS */


@@>> bcmp(3)
@@Similar to `memcmp(3)', except that no ordering is done,
@@such  that compare is  only correct for equal/non-equal.
@@@return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
@@@return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes'
[[guard, decl_include("<hybrid/typecore.h>")]]
[[libc, kernel, pure, wunused]]
[[preferred_fastbind(bcmp(s1, s2, n_bytes), ["bcmp"])]]
[[preferred_fastbind(memcmp(s1, s2, n_bytes), ["bcmp"])]]
[[preferred_fastbind(bcmp(s1, s2, n_bytes), ["memcmp"])]]
[[preferred_fastbind(memcmp(s1, s2, n_bytes), ["memcmp"])]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_BCMP))]]
[[if(!defined(LIBC_ARCH_HAVE_BCMP)), crt_intern_alias(memcmp)]]
[[alias("memcmp"), bind_local_function("memcmp")]]
int bcmp([[in(n_bytes)]] void const *s1,
         [[in(n_bytes)]] void const *s2, $size_t n_bytes) {
	return memcmp(s1, s2, n_bytes);
}

%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(bcmp = bcmpc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */


%[insert:guarded_function(index = strchr)]
%[insert:guarded_function(rindex = strrchr)]

[[guard, dos_only_export_alias("_stricmp", "_strcmpi")]]
[[kernel, alias("stricmp", "strcmpi", "__strcasecmp")]]
[[if(!defined(__KERNEL__)), export_as("stricmp", "strcmpi", "__strcasecmp")]]
[[pure, wunused, section(".text.crt{|.dos}.unicode.static.memory"), crtbuiltin]]
int strcasecmp([[in]] char const *s1, [[in]] char const *s2) {
	char c1, c2;
	do {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char)tolower((unsigned char)c1);
			c2 = (char)tolower((unsigned char)c2);
			if (c1 != c2)
				return (int)((unsigned char)c1 - (unsigned char)c2);
		}
	} while (c1 != '\0');
	return 0;
}

[[guard, kernel, decl_include("<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strnicmp", "_strncmpi"), alias("strnicmp", "strncmpi")]]
[[if(!defined(__KERNEL__)), export_as("strnicmp", "strncmpi")]]
[[pure, wunused, section(".text.crt{|.dos}.unicode.static.memory"), crtbuiltin]]
int strncasecmp([[in(strnlen(., maxlen))]] char const *s1,
                [[in(strnlen(., maxlen))]] char const *s2,
                $size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char)tolower((unsigned char)c1);
			c2 = (char)tolower((unsigned char)c2);
			if (c1 != c2)
				return (int)((unsigned char)c1 - (unsigned char)c2);
		}
	} while (c1 != '\0');
	return 0;
}


[[decl_include("<features.h>")]]
[[guard, const, wunused, nothrow, crtbuiltin]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && !defined(LIBC_ARCH_HAVE_FFSL)),       crt_intern_kos_alias("libc_ffsl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)), crt_intern_kos_alias("libc_ffsll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),                                        alias("ffsl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__),                                   alias("ffsll")]]
[[export_alias("__ffs")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_FFS))]]
[[impl_include("<features.h>", "<hybrid/__bit.h>")]]
__STDC_INT_AS_UINT_T ffs(int i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)i);
}

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

%#ifdef __USE_GNU
[[decl_include("<features.h>")]]
[[const, wunused, nothrow, crtbuiltin]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)), crt_intern_kos_alias("libc_ffsll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),                                         alias("ffs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__),                                   alias("ffsll")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_FFSL))]]
[[impl_include("<features.h>", "<hybrid/__bit.h>")]]
__STDC_INT_AS_UINT_T ffsl(long i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)i);
}

[[decl_include("<features.h>")]]
[[const, wunused, nothrow, crtbuiltin]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("ffs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("ffsl")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_FFSLL))]]
[[impl_include("<features.h>", "<hybrid/__bit.h>")]]
__STDC_INT_AS_UINT_T ffsll(__LONGLONG i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)i);
}
%#endif /* __USE_GNU */

[[leaf, kernel, guard, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRLCAT))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t strlcat([[inout(bufsize)]] char *__restrict dst,
                [[in]] char const *__restrict src,
                $size_t bufsize) {
	size_t result = strlen(src);
	char *new_dst = dst + strnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(new_dst, src, copy_size*sizeof(char));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}

[[leaf, kernel, guard, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRLCPY))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t strlcpy([[out(bufsize)]] char *__restrict dst,
                [[in]] char const *__restrict src,
                $size_t bufsize) {
	size_t result = strlen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(dst, src, copy_size * sizeof(char));
	dst[copy_size] = '\0';
	return result;
}

%#endif /* __USE_MISC */
%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)

[[guard, leaf, decl_include("<hybrid/typecore.h>")]]
[[dos_only_export_alias("_memccpy"), export_alias("__memccpy")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCCPY))]]
[[impl_include("<hybrid/typecore.h>")]]
void *memccpy([[out(num_bytes)]] void *__restrict dst,
              [[in(num_bytes)]] void const *__restrict src,
              int needle, $size_t num_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (num_bytes--) {
		if ((*pdst++ = *psrc++) == (byte_t)needle)
			return pdst; /* Yes, this returns +1 past the needle. */
	}
	return NULL;
}
%{
#endif /* __USE_MISC || __USE_XOPEN */


}

%[insert:function(__bzero = bzero)]
%[insert:function(__strtok_r = strtok_r)]

%
%#ifdef __USE_STRING_BWLQ

@@Copy memory between non-overlapping memory blocks.
[[decl_include("<hybrid/typecore.h>")]]
[[nocrt, leaf, alias("memcpy")]]
[[preferred_fastbind(($uint8_t *)memcpy(dst, src, n_bytes))]]
[[bind_local_function("memcpy")]]
memcpyb:([[out(n_bytes * 1), aligned(1)]] void *__restrict dst,
         [[in (n_bytes * 1), aligned(1)]] void const *__restrict src,
         $size_t n_bytes) -> [[== dst]] $uint8_t *;

@@Same as `memcpyb', but return `dst + n_bytes', rather than `dst'
[[decl_include("<hybrid/typecore.h>")]]
[[nocrt, leaf, alias("mempcpy", "__mempcpy")]]
[[preferred_fastbind(($uint8_t *)mempcpy(dst, src, n_bytes), ["mempcpy", "__mempcpy"])]]
[[bind_local_function("mempcpy")]]
mempcpyb:([[out(n_bytes * 1), aligned(1)]] void *__restrict dst,
          [[in (n_bytes * 1), aligned(1)]] void const *__restrict src,
          $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t *;

@@Copy memory between non-overlapping memory blocks.
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemcpy")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemcpy")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmemcpy")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmemcpy")]]
[[if_fast_defined(memcpyw), preferred_fast_extern_inline("memcpyw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(memcpyw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(memcpyw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(memcpyw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYW))]]
[[impl_include("<hybrid/typecore.h>")]]
memcpyw:([[out(n_words * 2), aligned(2)]] void *__restrict dst,
         [[in (n_words * 2), aligned(2)]] void const *__restrict src,
         $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	u16 const *psrc = (u16 const *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}


@@Same as `memcpyw', but return `dst + N_WORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmempcpy")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmempcpy")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmempcpy")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmempcpy")]]
[[if_fast_defined(mempcpyw), preferred_fast_extern_inline("mempcpyw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(mempcpyw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmempcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(mempcpyw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmempcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyw@))(dst, src, n_words); })]]
[[if_fast_defined(mempcpyw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYW))]]
[[impl_include("<hybrid/typecore.h>")]]
mempcpyw:([[out(n_words * 2), aligned(2)]] void *__restrict dst,
          [[in (n_words * 2), aligned(2)]] void const *__restrict src,
          $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memcpyw(dst, src, n_words) + n_words;
}

@@Copy memory between non-overlapping memory blocks.
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemcpy")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemcpy")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmemcpy")]]
[[if_fast_defined(memcpyl), preferred_fast_extern_inline("memcpyl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memcpyl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memcpyl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memcpyl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcpyl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYL))]]
[[impl_include("<hybrid/typecore.h>")]]
memcpyl:([[out(n_dwords * 4), aligned(4)]] void *__restrict dst,
         [[in (n_dwords * 4), aligned(4)]] void const *__restrict src,
         $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	u32 const *psrc = (u32 const *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

@@Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmempcpy")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmempcpy")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmempcpy")]]
[[if_fast_defined(mempcpyl), preferred_fast_extern_inline("mempcpyl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempcpyl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmempcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempcpyl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmempcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempcpyl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempcpyl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYL))]]
[[impl_include("<hybrid/typecore.h>")]]
mempcpyl:([[out(n_dwords * 4), aligned(4)]] void *__restrict dst,
          [[in (n_dwords * 4), aligned(4)]] void const *__restrict src,
          $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memcpyl(dst, src, n_dwords) + n_dwords;
}


@@Move memory between potentially overlapping memory blocks.
[[nocrt, leaf, alias("memmove"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memmove(dst, src, n_bytes))]]
[[bind_local_function("memmove")]]
memmoveb:([[out(n_bytes * 1), aligned(1)]] void *dst,
          [[in (n_bytes * 1), aligned(1)]] void const *src,
          $size_t n_bytes) -> [[== dst]] $uint8_t *;

@@Same as `memmoveb', but return `dst + n_bytes', rather than `dst'
[[nocrt, leaf, alias("mempmove"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)mempmove(dst, src, n_bytes))]]
[[bind_local_function("mempmove")]]
mempmoveb:([[out(n_bytes * 1), aligned(1)]] void *dst,
           [[in (n_bytes * 1), aligned(1)]] void const *src,
           $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t *;

@@Move memory between potentially overlapping memory blocks.
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemmove")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmemmove")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmemmove")]]
[[if_fast_defined(memmovew), preferred_fast_extern_inline("memmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovew@))(dst, src, n_words); })]]
[[if_fast_defined(memmovew), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovew@))(dst, src, n_words); })]]
[[if_fast_defined(memmovew), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovew@))(dst, src, n_words); })]]
[[if_fast_defined(memmovew), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovew@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEW))]]
[[impl_include("<hybrid/typecore.h>")]]
memmovew:([[out(n_words * 2), aligned(2)]] void *dst,
          [[in (n_words * 2), aligned(2)]] void const *src,
          $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst;
	u16 const *psrc;
	if (dst <= src) {
		pdst = (u16 *)dst;
		psrc = (u16 const *)src;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u16 *)dst + n_words;
		psrc = (u16 const *)src + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}

@@Same as `memmovew', but return `dst + N_WORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmempmove")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmempmove")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmempmove")]]
[[if_fast_defined(mempmovew), preferred_fast_extern_inline("mempmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovew@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovew), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovew@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovew), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovew@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovew), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovew@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEW))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmovew:([[out(n_words * 2), aligned(2)]] void *dst,
           [[in (n_words * 2), aligned(2)]] void const *src,
           $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmovew(dst, src, n_words) + n_words;
}

@@Move memory between potentially overlapping memory blocks.
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemmove")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmemmove")]]
[[if_fast_defined(memmovel), preferred_fast_extern_inline("memmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovel), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovel), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovel), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovel@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEL))]]
[[impl_include("<hybrid/typecore.h>")]]
memmovel:([[out(n_dwords * 4), aligned(4)]] void *dst,
          [[in (n_dwords * 4), aligned(4)]] void const *src,
          $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst;
	u32 const *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 const *)src;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u32 *)dst + n_dwords;
		psrc = (u32 const *)src + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}

@@Same as `memmovew', but return `dst + N_DWORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmempmove")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmempmove")]]
[[if_fast_defined(mempmovel), preferred_fast_extern_inline("mempmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovel), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovel), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovel@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovel), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovel@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEL))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmovel:([[out(n_dwords * 4), aligned(4)]] void *dst,
           [[in (n_dwords * 4), aligned(4)]] void const *src,
           $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmovel(dst, src, n_dwords) + n_dwords;
}

%#ifdef __USE_KOS
@@Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_bytes')
[[nocrt, leaf, alias("memmoveup"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memmoveup(dst, src, n_bytes))]]
[[bind_local_function("memmoveup")]]
memmoveupb:([[out(n_bytes * 1), aligned(1)]] void *dst,
            [[in (n_bytes * 1), aligned(1)]] void const *src,
            $size_t n_bytes) -> [[== dst]] $uint8_t *;

@@Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_bytes')
[[nocrt, leaf, alias("memmovedown"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memmovedown(dst, src, n_bytes))]]
[[bind_local_function("memmovedown")]]
memmovedownb:([[out(n_bytes * 1), aligned(1)]] void *dst,
              [[in (n_bytes * 1), aligned(1)]] void const *src,
              $size_t n_bytes) -> [[== dst]] $uint8_t *;

@@Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes')
[[nocrt, leaf, alias("mempmoveup"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)mempmoveup(dst, src, n_bytes))]]
[[bind_local_function("mempmoveup")]]
mempmoveupb:([[out(n_bytes * 1), aligned(1)]] void *dst,
             [[in (n_bytes * 1), aligned(1)]] void const *src,
             $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t *;

@@Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes')
[[nocrt, leaf, alias("mempmovedown"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)mempmovedown(dst, src, n_bytes))]]
[[bind_local_function("mempmovedown")]]
mempmovedownb:([[out(n_bytes * 1), aligned(1)]] void *dst,
               [[in (n_bytes * 1), aligned(1)]] void const *src,
               $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t *;

@@Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS')
[[libc, kernel, leaf, alias("memmovew"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemmove")]]
[[if_fast_defined(memmoveupw), preferred_fast_extern_inline("memmoveupw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(memmoveupw), preferred_fast_extern_inline("memmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(memmoveupw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(memmoveupw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(memmoveupw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPW))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmoveupw:([[out(n_words * 2), aligned(2)]] void *dst,
            [[in (n_words * 2), aligned(2)]] void const *src,
            $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst;
	u16 const *psrc;
	pdst = (u16 *)dst + n_words;
	psrc = (u16 const *)src + n_words;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst >= psrc || !n_words, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_words);
@@pp_else@@
	@__hybrid_assertf@(pdst >= psrc || !n_words, "%p < %p (count:%zu)", dst, src, n_words);
@@pp_endif@@
	while (n_words--)
		*--pdst = *--psrc;
	return (u16 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS')
[[libc, kernel, leaf, alias("memmovew"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemmove")]]
[[if_fast_defined(memmovedownw), preferred_fast_extern_inline("memmovedownw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(memmovedownw), preferred_fast_extern_inline("memmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(memmovedownw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(memmovedownw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(memmovedownw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNW))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmovedownw:([[out(n_words * 2), aligned(2)]] void *dst,
              [[in (n_words * 2), aligned(2)]] void const *src,
              $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst;
	u16 const *psrc;
	pdst = (u16 *)dst;
	psrc = (u16 const *)src;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst <= psrc || !n_words, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_words);
@@pp_else@@
	@__hybrid_assertf@(pdst <= psrc || !n_words, "%p > %p (count:%zu)", dst, src, n_words);
@@pp_endif@@
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}

@@Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS')
[[libc, kernel, leaf, alias("mempmovew"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmempmove")]]
[[if_fast_defined(mempmoveupw), preferred_fast_extern_inline("mempmoveupw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmoveupw), preferred_fast_extern_inline("mempmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmoveupw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmoveupw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmoveupw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPW))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmoveupw:([[out(n_words * 2), aligned(2)]] void *dst,
             [[in (n_words * 2), aligned(2)]] void const *src,
             $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmoveupw(dst, src, n_words) + n_words;
}

@@Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS')
[[libc, kernel, leaf, alias("mempmovew"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmempmove")]]
[[if_fast_defined(mempmovedownw), preferred_fast_extern_inline("mempmovedownw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovedownw), preferred_fast_extern_inline("mempmovew", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovedownw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovedownw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownw@))(dst, src, n_words); })]]
[[if_fast_defined(mempmovedownw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownw@))(dst, src, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNW))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmovedownw:([[out(n_words * 2), aligned(2)]] void *dst,
               [[in (n_words * 2), aligned(2)]] void const *src,
               $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmovedownw(dst, src, n_words) + n_words;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS')
[[libc, kernel, leaf, alias("memmovel"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemmove")]]
[[if_fast_defined(memmoveupl), preferred_fast_extern_inline("memmoveupl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmoveupl), preferred_fast_extern_inline("memmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmoveupl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmoveupl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmoveupl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmoveupl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPL))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmoveupl:([[out(n_dwords * 4), aligned(4)]] void *dst,
            [[in (n_dwords * 4), aligned(4)]] void const *src,
            $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst;
	u32 const  *psrc;
	pdst = (u32 *)dst + n_dwords;
	psrc = (u32 const *)src + n_dwords;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst >= psrc || !n_dwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_dwords);
@@pp_else@@
	@__hybrid_assertf@(pdst >= psrc || !n_dwords, "%p < %p (count:%zu)", dst, src, n_dwords);
@@pp_endif@@
	while (n_dwords--)
		*--pdst = *--psrc;
	return (u32 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS')
[[libc, kernel, leaf, alias("memmovel"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemmove")]]
[[if_fast_defined(memmovedownl), preferred_fast_extern_inline("memmovedownl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovedownl), preferred_fast_extern_inline("memmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovedownl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovedownl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(memmovedownl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memmovedownl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNL))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmovedownl:([[out(n_dwords * 4), aligned(4)]] void *dst,
              [[in (n_dwords * 4), aligned(4)]] void const *src,
              $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 const *)src;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst <= psrc || !n_dwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_dwords);
@@pp_else@@
	@__hybrid_assertf@(pdst <= psrc || !n_dwords, "%p > %p (count:%zu)", dst, src, n_dwords);
@@pp_endif@@
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

@@Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS')
[[libc, kernel, leaf, alias("mempmovel"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmempmove")]]
[[if_fast_defined(mempmoveupl), preferred_fast_extern_inline("mempmoveupl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmoveupl), preferred_fast_extern_inline("mempmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmoveupl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmoveupl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmoveupl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmoveupl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPL))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmoveupl:([[out(n_dwords * 4), aligned(4)]] void *dst,
             [[in (n_dwords * 4), aligned(4)]] void const *src,
             $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmoveupl(dst, src, n_dwords) + n_dwords;
}

@@Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS')
[[libc, kernel, leaf, alias("mempmovel"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmempmove")]]
[[if_fast_defined(mempmovedownl), preferred_fast_extern_inline("mempmovedownl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovedownl), preferred_fast_extern_inline("mempmovel", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovedownl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovedownl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmempmove", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownl@))(dst, src, n_dwords); })]]
[[if_fast_defined(mempmovedownl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempmovedownl@))(dst, src, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNL))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmovedownl:([[out(n_dwords * 4), aligned(4)]] void *dst,
               [[in (n_dwords * 4), aligned(4)]] void const *src,
               $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmovedownl(dst, src, n_dwords) + n_dwords;
}

%#endif /* __USE_KOS */


@@Fill memory with a given byte
[[nocrt, leaf, alias("memset"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memset(dst, byte, n_bytes))]]
[[bind_local_function("memset")]]
memsetb:([[out(n_bytes * 1), aligned(1)]] void *__restrict dst,
         int byte, $size_t n_bytes) -> [[== dst]] $uint8_t *;

@@Same as `memsetb', but return `dst + n_bytes', rather than `dst'
[[nocrt, leaf, alias("mempset"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)mempset(dst, byte, n_bytes))]]
[[bind_local_function("mempset")]]
mempsetb:([[out(n_bytes * 1), aligned(1)]] void *__restrict dst,
          int byte, $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t *;

@@Fill memory with a given word
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemset")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemset")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmemset")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmemset")]]
[[if_fast_defined(memsetw), preferred_fast_extern_inline("memsetw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetw@))(dst, word, n_words); })]]
[[if_fast_defined(memsetw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetw@))(dst, word, n_words); })]]
[[if_fast_defined(memsetw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetw@))(dst, word, n_words); })]]
[[if_fast_defined(memsetw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetw@))(dst, word, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETW))]]
[[impl_include("<hybrid/typecore.h>")]]
memsetw:([[out(n_words * 2), aligned(2)]] void *__restrict dst,
         $uint16_t word, $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	while (n_words--)
		*pdst++ = word;
	return (u16 *)dst;
}


@@Same as `memsetw', but return `dst + N_WORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmempset")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmempset")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmempset")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmempset")]]
[[if_fast_defined(mempsetw), preferred_fast_extern_inline("mempsetw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetw@))(dst, word, n_words); })]]
[[if_fast_defined(mempsetw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmempset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetw@))(dst, word, n_words); })]]
[[if_fast_defined(mempsetw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmempset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetw@))(dst, word, n_words); })]]
[[if_fast_defined(mempsetw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetw@))(dst, word, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETW))]]
[[impl_include("<hybrid/typecore.h>")]]
mempsetw:([[out(n_words * 2), aligned(2)]] void *__restrict dst,
          $uint16_t word, $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memsetw(dst, word, n_words) + n_words;
}

@@Fill memory with a given dword
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemset")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemset")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmemset")]]
[[if_fast_defined(memsetl), preferred_fast_extern_inline("memsetl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(memsetl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(memsetl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(memsetl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memsetl@))(dst, dword, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETL))]]
[[impl_include("<hybrid/typecore.h>")]]
memsetl:([[out(n_dwords * 4), aligned(4)]] void *__restrict dst,
         $uint32_t dword, $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	while (n_dwords--)
		*pdst++ = dword;
	return (u32 *)dst;
}

@@Same as `memsetl', but return `dst + N_DWORDS', rather than `dst'
[[libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmempset")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmempset")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmempset")]]
[[if_fast_defined(mempsetl), preferred_fast_extern_inline("mempsetl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(mempsetl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmempset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(mempsetl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmempset", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetl@))(dst, dword, n_dwords); })]]
[[if_fast_defined(mempsetl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@mempsetl@))(dst, dword, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETL))]]
[[impl_include("<hybrid/typecore.h>")]]
mempsetl:([[out(n_dwords * 4), aligned(4)]] void *__restrict dst,
          $uint32_t dword, $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memsetl(dst, dword, n_dwords) + n_dwords;
}


@@Compare memory buffers and return the difference of the first non-matching byte
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
int memcmpb([[in(n_bytes * 1), aligned(1)]] void const *s1,
            [[in(n_bytes * 1), aligned(1)]] void const *s2,
            $size_t n_bytes) = memcmp;

@@Compare memory buffers and return the difference of the first non-matching word
[[libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemcmp")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemcmp")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmemcmp")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmemcmp")]]
[[if_fast_defined(memcmpw), preferred_fast_extern_inline("memcmpw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemcmp", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemcmp", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[if_fast_defined(memcmpw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpw@))(s1, s2, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPW))]]
[[impl_include("<hybrid/typecore.h>")]]
int memcmpw([[in(n_words * 2), aligned(2)]] void const *s1,
            [[in(n_words * 2), aligned(2)]] void const *s2, $size_t n_words) {
	u16 const *p1 = (u16 const *)s1;
	u16 const *p2 = (u16 const *)s2;
	while (n_words--) {
		u16 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}

@@Compare memory buffers and return the difference of the first non-matching dword
[[libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemcmp")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemcmp")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmemcmp")]]
[[if_fast_defined(memcmpl), preferred_fast_extern_inline("memcmpl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemcmp", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemcmp", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[if_fast_defined(memcmpl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memcmpl@))(s1, s2, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPL))]]
[[impl_include("<hybrid/typecore.h>")]]
int memcmpl([[in(n_dwords * 4), aligned(4)]] void const *s1,
            [[in(n_dwords * 4), aligned(4)]] void const *s2,
            $size_t n_dwords) {
	u32 const *p1 = (u32 const *)s1;
	u32 const *p2 = (u32 const *)s2;
	while (n_dwords--) {
		u32 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}


@@Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
[[pure, wunused, nocrt, alias("memchr"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memchr(haystack, needle, n_bytes))]]
[[bind_local_function("memchr")]]
$uint8_t *memchrb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): $uint8_t const *];

@@Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
[[libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wmemchr")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wmemchr")]]
[[if(!defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$wmemchr")]]
[[if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$wmemchr")]]
[[if_fast_defined(memchrw), preferred_fast_extern_inline("memchrw", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrw@))(haystack, needle, n_words); })]]
[[if_fast_defined(memchrw), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), preferred_fast_extern_inline("wmemchr", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrw@))(haystack, needle, n_words); })]]
[[if_fast_defined(memchrw), if(defined(__LIBCCALL_IS_LIBDCALL)), preferred_fast_extern_inline("DOS$wmemchr", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrw@))(haystack, needle, n_words); })]]
[[if_fast_defined(memchrw), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrw@))(haystack, needle, n_words); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint16_t *memchrw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}

@@Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
[[libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wmemchr")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wmemchr")]]
[[if(!defined(__KERNEL__)), kos_export_as("wmemchr")]]
[[if_fast_defined(memchrl), preferred_fast_extern_inline("memchrl", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrl@))(haystack, needle, n_dwords); })]]
[[if_fast_defined(memchrl), if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_fast_extern_inline("wmemchr", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrl@))(haystack, needle, n_dwords); })]]
[[if_fast_defined(memchrl), if(defined(__LIBCCALL_IS_LIBKCALL)), preferred_fast_extern_inline("KOS$wmemchr", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrl@))(haystack, needle, n_dwords); })]]
[[if_fast_defined(memchrl), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@memchrl@))(haystack, needle, n_dwords); })]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint32_t *memchrl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found.
[[pure, wunused, nocrt, alias("memrchr"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memrchr(haystack, needle, n_bytes))]]
[[bind_local_function("memrchr")]]
$uint8_t *memrchrb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): $uint8_t const *];

@@Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint16_t *memrchrw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}

@@Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint32_t *memrchrl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}

@@Same as `memchrb' with a search limit of `(size_t)-1'
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *rawmemchrb([[in, aligned(1)]] void const *__restrict haystack, int needle)
	[([[in, aligned(1)]] void *__restrict haystack, int needle): [[nonnull]] $uint8_t *]
	[([[in, aligned(1)]] void const *__restrict haystack, int needle): [[nonnull]] $uint8_t const *]
	= rawmemchr;

@@Same as `memchrw' with a search limit of `(size_t)-1 / 2'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *rawmemchrw([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle)
	[([[in, aligned(2)]] void *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t *]
	[([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}

@@Same as `memchrl' with a search limit of `(size_t)-1 / 4'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *rawmemchrl([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle)
	[([[in, aligned(4)]] void *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t *]
	[([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}


@@Same as `memrchrb' without a search limit, starting at `haystack - 1'
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *rawmemrchrb([[nonnull, aligned(1)]] void const *__restrict haystack, int needle)
	[([[nonnull, aligned(1)]] void *__restrict haystack, int needle): [[nonnull]] $uint8_t *]
	[([[nonnull, aligned(1)]] void const *__restrict haystack, int needle): [[nonnull]] $uint8_t const *]
	= rawmemrchr;

@@Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *rawmemrchrw([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle)
	[([[nonnull, aligned(2)]] void *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t *]
	[([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}

@@Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *rawmemrchrl([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle)
	[([[nonnull, aligned(4)]] void *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t *]
	[([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}


@@Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found.
[[pure, wunused, nocrt, alias("memend"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memend(haystack, byte, n_bytes))]]
[[bind_local_function("memend")]]
[[nonnull]] $uint8_t *memendb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t const *];

@@Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *memendw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_bytes)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_bytes): [[nonnull]] $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_bytes): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}

@@Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *memendl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_dwords--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}

@@Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found.
[[pure, wunused, nocrt, alias("memrend"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(($uint8_t *)memrend(haystack, needle, n_bytes))]]
[[bind_local_function("memrend")]]
[[nonnull]] $uint8_t *memrendb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t const *];

@@Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *memrendw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result == needle)
			break;
		--n_words;
	}
	return result;
}

@@Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *memrendl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result == needle)
			break;
		--n_dwords;
	}
	return result;
}



@@Same as `memendb', but return the offset from `haystack', rather than the actual address.
@@Returns `haystack + N_DWORDS' if the given `needle' wasn't found
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t memlenb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack,
                int needle, $size_t n_bytes) = memlen;

@@Same as `memendw', but return the offset from `haystack', rather than the actual address.
@@Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memlenw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack,
                $uint16_t needle, $size_t n_words) {
	return (size_t)(memendw(haystack, needle, n_words) - (u16 *)haystack);
}

@@Same as `memendl', but return the offset from `haystack', rather than the actual address.
@@Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memlenl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack,
                $uint32_t needle, $size_t n_dwords) {
	return (size_t)(memendl(haystack, needle, n_dwords) - (u32 *)haystack);
}

@@Same as `memrendb', but return the offset from `haystack', rather than the actual address.
@@Returns `(size_t)-1' if the given `needle' wasn't found
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t memrlenb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack,
                 int needle, $size_t n_bytes) = memrlen;

@@Same as `memrendw', but return the offset from `haystack', rather than the actual address.
@@Returns `(size_t)-1 / 2' if the given `needle' wasn't found
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrlenw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack,
                 $uint16_t needle, $size_t n_words) {
	return (size_t)(memrendw(haystack, needle, n_words) - (u16 *)haystack);
}

@@Same as `memrendl', but return the offset from `haystack', rather than the actual address.
@@Returns `(size_t)-1 / 4' if the given `needle' wasn't found
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrlenl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack,
                 $uint32_t needle, $size_t n_dwords) {
	return (size_t)(memrendl(haystack, needle, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemchrb', but return the offset from `haystack', rather than the actual address.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t rawmemlenb([[in, aligned(1)]] void const *__restrict haystack, int needle) = rawmemlen;

@@Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemlenw([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle) {
	return (size_t)(rawmemchrw(haystack, needle) - (u16 *)haystack);
}

@@Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemlenl([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle) {
	return (size_t)(rawmemchrl(haystack, needle) - (u32 *)haystack);
}


@@Same as `rawmemrchrb', but return the offset from `haystack', rather than the actual address.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t rawmemrlenb([[nonnull, aligned(1)]] void const *__restrict haystack, int needle) = rawmemrlen;

@@Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrlenw([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle) {
	return (size_t)(rawmemrchrw(haystack, needle) - (u16 *)haystack);
}

@@Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrlenl([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle) {
	return (size_t)(rawmemrchrl(haystack, needle) - (u32 *)haystack);
}


%
%#ifdef __UINT64_TYPE__
@@Copy memory between non-overlapping memory blocks.
[[preferred_fastbind, libc, kernel, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYQ))]]
[[impl_include("<hybrid/typecore.h>")]]
memcpyq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
         [[in (n_qwords * 8), aligned(8)]] void const *__restrict src,
         $size_t n_qwords) -> [[== dst]] $uint64_t * {
@@pp_if __SIZEOF_BUSINT__ >= 8@@
	u64 *pdst = (u64 *)dst;
	u64 const *psrc = (u64 const *)src;
	while (n_qwords--)
		*pdst++ = *psrc++;
@@pp_else@@
	u32 *pdst = (u32 *)dst;
	u32 const *psrc = (u32 const *)src;
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
@@pp_endif@@
	return (u64 *)dst;
}

@@Same as `memcpyq', but return `dst + n_qwords', rather than `dst'
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYQ))]]
[[impl_include("<hybrid/typecore.h>")]]
mempcpyq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
          [[in (n_qwords * 8), aligned(8)]] void const *__restrict src,
          $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memcpyq(dst, src, n_qwords) + n_qwords;
}

@@Move memory between potentially overlapping memory blocks.
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEQ))]]
[[impl_include("<hybrid/typecore.h>")]]
memmoveq:([[out(n_qwords * 8), aligned(8)]] void *dst,
          [[in (n_qwords * 8), aligned(8)]] void const *src,
          $size_t n_qwords) -> [[== dst]] $uint64_t * {
@@pp_if __SIZEOF_BUSINT__ >= 8@@
	u64 *pdst;
	u64 const *psrc;
	if (dst <= src) {
		pdst = (u64 *)dst;
		psrc = (u64 const *)src;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u64 *)dst + n_qwords;
		psrc = (u64 const *)src + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
@@pp_else@@
	u32 *pdst;
	u32 const *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 const *)src;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		pdst = (u32 *)dst + (n_qwords * 2);
		psrc = (u32 const *)src + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
@@pp_endif@@
	return (u64 *)dst;
}

@@Same as `memmovew', but return `dst + n_qwords', rather than `dst'
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEQ))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmoveq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
           [[in (n_qwords * 8), aligned(8)]] void const *__restrict src,
           $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmoveq(dst, src, n_qwords) + n_qwords;
}

%#ifdef __USE_KOS

@@Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords')
[[libc, kernel, leaf, alias("memmoveq"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(memmoveupq, ["memmoveupq", "memmoveq"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPQ))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmoveupq:([[out(n_qwords * 8), aligned(8)]] void *dst,
            [[in (n_qwords * 8), aligned(8)]] void const *src,
            $size_t n_qwords) -> [[== dst]] $uint64_t * {
@@pp_if __SIZEOF_BUSINT__ >= 8@@
	u64 *pdst;
	u64 const *psrc;
	pdst = (u64 *)dst + n_qwords;
	psrc = (u64 const *)src + n_qwords;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
@@pp_else@@
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%zu)", dst, src, n_qwords);
@@pp_endif@@
	while (n_qwords--)
		*--pdst = *--psrc;
@@pp_else@@
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst + (n_qwords * 2);
	psrc = (u32 const *)src + (n_qwords * 2);
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
@@pp_else@@
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%zu)", dst, src, n_qwords);
@@pp_endif@@
	while (n_qwords--) {
		*--pdst = *--psrc;
		*--pdst = *--psrc;
	}
@@pp_endif@@
	return (u64 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords')
[[libc, kernel, leaf, alias("memmoveq"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(memmovedownq, ["memmovedownq", "memmoveq"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNQ))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
memmovedownq:([[out(n_qwords * 8), aligned(8)]] void *dst,
              [[in (n_qwords * 8), aligned(8)]] void const *src,
              $size_t n_qwords) -> [[== dst]] $uint64_t * {
@@pp_if __SIZEOF_BUSINT__ >= 8@@
	u64 *pdst;
	u64 const *psrc;
	pdst = (u64 *)dst;
	psrc = (u64 const *)src;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
@@pp_else@@
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%zu)", dst, src, n_qwords);
@@pp_endif@@
	while (n_qwords--)
		*pdst++ = *psrc++;
@@pp_else@@
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 const *)src;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
@@pp_else@@
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%zu)", dst, src, n_qwords);
@@pp_endif@@
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
@@pp_endif@@
	return (u64 *)dst;
}

@@Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords')
[[libc, kernel, leaf, alias("mempmoveq"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(mempmoveupq, ["mempmoveupq", "mempmoveq"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPQ))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmoveupq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
             [[in (n_qwords * 8), aligned(8)]] void const *__restrict src,
             $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmoveupq(dst, src, n_qwords) + n_qwords;
}

@@Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords')
[[libc, kernel, leaf, alias("mempmoveq"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(mempmovedownq, ["mempmovedownq", "mempmoveq"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNQ))]]
[[impl_include("<hybrid/typecore.h>")]]
mempmovedownq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
               [[in (n_qwords * 8), aligned(8)]] void const *__restrict src,
               $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmovedownq(dst, src, n_qwords) + n_qwords;
}

%#endif /* __USE_KOS */


@@Fill memory with a given qword
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETQ))]]
[[impl_include("<hybrid/typecore.h>")]]
memsetq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
         $uint64_t qword, $size_t n_qwords) -> [[== dst]] $uint64_t * {
	u64 *pdst = (u64 *)dst;
	while (n_qwords--)
		*pdst++ = qword;
	return (u64 *)dst;
}

@@Same as `memsetq', but return `dst + n_qwords', rather than `dst'
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETQ))]]
[[impl_include("<hybrid/typecore.h>")]]
mempsetq:([[out(n_qwords * 8), aligned(8)]] void *__restrict dst,
          $uint64_t qword, $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memsetq(dst, qword, n_qwords) + n_qwords;
}

@@Compare memory buffers and return the difference of the first non-matching qword
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPQ))]]
[[impl_include("<hybrid/typecore.h>")]]
int memcmpq([[in(n_qwords * 8), aligned(8)]] void const *s1,
            [[in(n_qwords * 8), aligned(8)]] void const *s2, $size_t n_dwords) {
	u64 const *p1 = (u64 const *)s1;
	u64 const *p2 = (u64 const *)s2;
	while (n_dwords--) {
		u64 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}

@@Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint64_t *memchrq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint64_t *memrchrq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}

@@Same as `memchrq' with a search limit of `(size_t)-1 / 8'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *rawmemchrq([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle)
	[([[in, aligned(8)]] void *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t *]
	[([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}

@@Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8'
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *rawmemrchrq([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle)
	[([[nonnull, aligned(8)]] void *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t *]
	[([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}

@@Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *memendq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_bytes)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_bytes): [[nonnull]] $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_bytes): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}

@@Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *memrendq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): [[nonnull]] $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result == needle)
			break;
		--n_qwords;
	}
	return result;
}

@@Same as `memendq', but return the offset from `haystack', rather than the actual address.
@@Returns `n_qwords' if the given `needle' wasn't found
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memlenq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack,
                $uint64_t needle, $size_t n_qwords) {
	return (size_t)(memendq(haystack, needle, n_qwords) - (u64 *)haystack);
}

@@Same as `memrendq', but return the offset from `haystack', rather than the actual address.
@@Returns `(size_t)-1 / 8' if the given `needle' wasn't found
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrlenq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack,
                 $uint64_t needle, $size_t n_qwords) {
	return (size_t)(memrendq(haystack, needle, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemlenq([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle) {
	return (size_t)(rawmemchrq(haystack, needle) - (u64 *)haystack);
}

@@Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrlenq([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle) {
	return (size_t)(rawmemrchrq(haystack, needle) - (u64 *)haystack);
}


%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */
%
%
%#ifdef __USE_STRING_XCHR


@@Same as `memchr', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
void *memxchr([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter != (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchr', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
void *memrxchr([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--iter != (byte_t)needle)
			return iter;
	}
	return NULL;
}


@@Same as `rawmemchr', but search for non-matching locations.
[[pure, wunused, impl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *rawmemxchr([[in]] void const *__restrict haystack, int needle)
	[([[in]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[in]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `rawmemrchr', but search for non-matching locations.
[[pure, wunused, impl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *rawmemrxchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `memend', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXEND))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memxend([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memrend', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXEND))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memrxend([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	for (;;) {
		--result;
		if unlikely(!n_bytes)
			break;
		if unlikely(*result != (byte_t)needle)
			break;
		--n_bytes;
	}
	return result;
}

@@Same as `memlen', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memxlen([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `memrlen', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrxlen([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `rawmemlen', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemxlen([[in]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemxchr(haystack, needle) - (byte_t *)haystack);
}

@@Same as `rawmemrlen', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrxlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemrxchr(haystack, needle) - (byte_t *)haystack);
}



%#ifdef __USE_STRING_BWLQ

@@Same as `memchrb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$uint8_t *memxchrb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): $uint8_t const *]
	= memxchr;

@@Same as `memchrw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint16_t *memxchrw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memchrl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint32_t *memxchrl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$uint8_t *memrxchrb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): $uint8_t const *]
	= memrxchr;

@@Same as `memrchrw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint16_t *memrxchrw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}

@@Same as `memrchrl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint32_t *memrxchrl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *rawmemxchrb([[in, aligned(1)]] void const *__restrict haystack, int needle)
	[([[in, aligned(1)]] void *__restrict haystack, int needle): [[nonnull]] $uint8_t *]
	[([[in, aligned(1)]] void const *__restrict haystack, int needle): [[nonnull]] $uint8_t const *]
	= rawmemxchr;

@@Same as `rawmemchrw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *rawmemxchrw([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle)
	[([[in, aligned(2)]] void *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t *]
	[([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}

@@Same as `rawmemchrl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *rawmemxchrl([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle)
	[([[in, aligned(4)]] void *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t *]
	[([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}


@@Same as `rawmemrchrb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *rawmemrxchrb([[nonnull, aligned(1)]] void const *__restrict haystack, int needle)
	[([[nonnull, aligned(1)]] void *__restrict haystack, int needle): [[nonnull]] $uint8_t *]
	[([[nonnull, aligned(1)]] void const *__restrict haystack, int needle): [[nonnull]] $uint8_t const *]
	= rawmemrxchr;

@@Same as `rawmemrchrw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *rawmemrxchrw([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle)
	[([[nonnull, aligned(2)]] void *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t *]
	[([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *rawmemrxchrl([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle)
	[([[nonnull, aligned(4)]] void *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t *]
	[([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}


@@Same as `memendb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *memxendb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memxend;

@@Same as `memendw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *memxendw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_words--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}

@@Same as `memendl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *memxendl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_dwords--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}


@@Same as `memrendb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint8_t *memrxendb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes * 1), aligned(1)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memrxend;

@@Same as `memrendw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDW))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint16_t *memrxendw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words)
	[([[in(n_words * 2), aligned(2)]] void *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t *]
	[([[in(n_words * 2), aligned(2)]] void const *__restrict haystack, $uint16_t needle, $size_t n_words): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result != needle)
			break;
		--n_words;
	}
	return result;
}

@@Same as `memrendl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDL))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint32_t *memrxendl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords)
	[([[in(n_dwords * 4), aligned(4)]] void *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack, $uint32_t needle, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result != needle)
			break;
		--n_dwords;
	}
	return result;
}



@@Same as `memlenb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t memxlenb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack,
                 int needle, $size_t n_bytes) = memxlen;

@@Same as `memlenw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memxlenw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack,
                 $uint16_t needle, $size_t n_words) {
	return (size_t)(memxendw(haystack, needle, n_words) - (u16 *)haystack);
}

@@Same as `memlenl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memxlenl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack,
                 $uint32_t needle, $size_t n_dwords) {
	return (size_t)(memxendl(haystack, needle, n_dwords) - (u32 *)haystack);
}

@@Same as `memrlenb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t memrxlenb([[in(n_bytes * 1), aligned(1)]] void const *__restrict haystack,
                  int needle, $size_t n_bytes) = memrxlen;

@@Same as `memrlenw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrxlenw([[in(n_words * 2), aligned(2)]] void const *__restrict haystack,
                  $uint16_t needle, $size_t n_words) {
	return (size_t)(memrxendw(haystack, needle, n_words) - (u16 *)haystack);
}

@@Same as `memrlenl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrxlenl([[in(n_dwords * 4), aligned(4)]] void const *__restrict haystack,
                  $uint32_t needle, $size_t n_dwords) {
	return (size_t)(memrxendl(haystack, needle, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemlenb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t rawmemxlenb([[in, aligned(1)]] void const *__restrict haystack,
                    int needle) = rawmemxlen;

@@Same as `rawmemlenw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemxlenw([[in, aligned(2)]] void const *__restrict haystack, $uint16_t needle) {
	return (size_t)(rawmemxchrw(haystack, needle) - (u16 *)haystack);
}

@@Same as `rawmemlenl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemxlenl([[in, aligned(4)]] void const *__restrict haystack, $uint32_t needle) {
	return (size_t)(rawmemxchrl(haystack, needle) - (u32 *)haystack);
}


@@Same as `rawmemrlenb', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t rawmemrxlenb([[nonnull, aligned(1)]] void const *__restrict haystack, int needle) = rawmemrxlen;

@@Same as `rawmemrlenw', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENW))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrxlenw([[nonnull, aligned(2)]] void const *__restrict haystack, $uint16_t needle) {
	return (size_t)(rawmemrxchrw(haystack, needle) - (u16 *)haystack);
}

@@Same as `rawmemrlenl', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENL))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrxlenl([[nonnull, aligned(4)]] void const *__restrict haystack, $uint32_t needle) {
	return (size_t)(rawmemrxchrl(haystack, needle) - (u32 *)haystack);
}



%#ifdef __UINT64_TYPE__

@@Same as `memchrq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint64_t *memxchrq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$uint64_t *memrxchrq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *rawmemxchrq([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle)
	[([[in, aligned(8)]] void *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t *]
	[([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *rawmemrxchrq([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle)
	[([[nonnull, aligned(8)]] void *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t *]
	[([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}

@@Same as `memendq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *memxendq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_bytes)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_bytes): [[nonnull]] $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_bytes): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}

@@Same as `memrendq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDQ))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] $uint64_t *memrxendq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords)
	[([[in(n_qwords * 8), aligned(8)]] void *__restrict haystack, $uint64_t needle, $size_t n_qwords): [[nonnull]] $uint64_t *]
	[([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result != needle)
			break;
		--n_qwords;
	}
	return result;
}

@@Same as `memlenq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memxlenq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords) {
	return (size_t)(memxendq(haystack, needle, n_qwords) - (u64 *)haystack);
}

@@Same as `memrlenq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrxlenq([[in(n_qwords * 8), aligned(8)]] void const *__restrict haystack, $uint64_t needle, $size_t n_qwords) {
	return (size_t)(memrxendq(haystack, needle, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemlenq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemxlenq([[in, aligned(8)]] void const *__restrict haystack, $uint64_t needle) {
	return (size_t)(rawmemxchrq(haystack, needle) - (u64 *)haystack);
}

@@Same as `rawmemrlenq', but search for non-matching locations.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENQ))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrxlenq([[nonnull, aligned(8)]] void const *__restrict haystack, $uint64_t needle) {
	return (size_t)(rawmemrxchrq(haystack, needle) - (u64 *)haystack);
}

%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */
%#endif /* __USE_STRING_XCHR */
%
%
%
%
%
%#ifdef __USE_KOS

@@>> memmoveup(3)
@@Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
@@@return: * : Always re-returns `dst'
[[libc, kernel, leaf, alias("memmove")]]
[[preferred_fastbind(memmoveup, ["memmoveup", "memmove"])]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUP))]]
[[impl_include("<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memmoveup:([[out(n_bytes)]] void *dst,
           [[in (n_bytes)]] void const *src,
           $size_t n_bytes) -> [[== dst]] void * {
	byte_t *pdst;
	byte_t const *psrc;
	pdst = (byte_t *)dst + n_bytes;
	psrc = (byte_t const *)src + n_bytes;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst >= psrc || !n_bytes, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_bytes);
@@pp_else@@
	@__hybrid_assertf@(pdst >= psrc || !n_bytes, "%p < %p (count:%zu)", dst, src, n_bytes);
@@pp_endif@@
	while (n_bytes--)
		*--pdst = *--psrc;
	return dst;
}

@@>> memmovedown(3)
@@Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
@@@return: * : Always re-returns `dst'
[[libc, kernel, leaf, alias("memmove")]]
[[preferred_fastbind(memmovedown, ["memmovedown", "memmove"])]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWN))]]
[[impl_include("<hybrid/__assert.h>", "<bits/crt/inttypes.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memmovedown:([[out(n_bytes)]] void *dst,
             [[in (n_bytes)]] void const *src,
             $size_t n_bytes) -> [[== dst]] void * {
	byte_t *pdst;
	byte_t const *psrc;
	pdst = (byte_t *)dst;
	psrc = (byte_t const *)src;
@@pp_ifdef __PRIP_PREFIX@@
	@__hybrid_assertf@(pdst <= psrc || !n_bytes, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_bytes);
@@pp_else@@
	@__hybrid_assertf@(pdst <= psrc || !n_bytes, "%p > %p (count:%zu)", dst, src, n_bytes);
@@pp_endif@@
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}


@@>> memcmpc(3)
@@Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
@@from  the 2 given  buffers. If all are  identical, return `0'. Else:
@@ - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
@@ - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
[[preferred_fastbind, libc, kernel, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPC))]]
[[impl_include("<hybrid/byteorder.h>", "<hybrid/host.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
int memcmpc([[in(elem_count * elem_size)]] void const *s1,
            [[in(elem_count * elem_size)]] void const *s2,
            $size_t elem_count, $size_t elem_size) {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return memcmp(s1, s2, elem_count);

	case 2:
		return memcmpw(s1, s2, elem_count);

	case 4:
		return memcmpl(s1, s2, elem_count);

	case 8:
		return memcmpq(s1, s2, elem_count);

	default:
		break;
	}
@@pp_endif@@
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return memcmp(s1, s2, elem_count * elem_size);
@@pp_else@@
	/* Complicated case: we must compare elem_size-large unsigned integers,
	 * but because host endian is LITTLE, we can't just compare bytes  from
	 * lowest address -> highest address (because the most significant byte
	 * comes last in a LITTLE-ENDIAN data-word) */
	while (elem_count--) {
		size_t i;
		byte_t const *s1_iter, *s2_iter;
		s1      = (byte_t const *)s1 + elem_size;
		s2      = (byte_t const *)s2 + elem_size;
		s1_iter = (byte_t const *)s1;
		s2_iter = (byte_t const *)s2;
		i = elem_size;
		while (i--) {
			byte_t v1, v2;
			v1 = *--s1_iter;
			v2 = *--s2_iter;
			if (v1 != v2) {
@@pp_if __SIZEOF_INT__ >= 2@@
				return (int)(unsigned int)v1 -
				       (int)(unsigned int)v2;
@@pp_else@@
				return v1 < v2 ? -1 : 1;
@@pp_endif@@
			}
		}
	}
	return 0;
@@pp_endif@@
}



@@>> memcpyc(3)
@@Copy memory between non-overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
memcpyc:([[out(elem_count * elem_size)]] void *__restrict dst,
         [[in (elem_count * elem_size)]] void const *__restrict src,
         $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return memcpy(dst, src, elem_count);

	case 2:
		return memcpyw(dst, src, elem_count);

	case 4:
		return memcpyl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return memcpyq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return memcpy(dst, src, elem_count * elem_size);
}

@@>> mempcpyc(3)
@@Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
mempcpyc:([[out(elem_count * elem_size)]] void *__restrict dst,
          [[in (elem_count * elem_size)]] void const *__restrict src,
          $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return mempcpy(dst, src, elem_count);

	case 2:
		return mempcpyw(dst, src, elem_count);

	case 4:
		return mempcpyl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return mempcpyq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return mempcpy(dst, src, elem_count * elem_size);
}

@@>> memmovec(3)
@@Move memory between potentially overlapping memory blocks
@@@return: * : Always re-returns `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
memmovec:([[out(elem_count * elem_size)]] void *dst,
          [[in (elem_count * elem_size)]] void const *src,
          $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return memmove(dst, src, elem_count);

	case 2:
		return memmovew(dst, src, elem_count);

	case 4:
		return memmovel(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return memmoveq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return memmove(dst, src, elem_count * elem_size);
}

@@>> mempmovec(3)
@@Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
mempmovec:([[out(elem_count * elem_size)]] void *dst,
           [[in (elem_count * elem_size)]] void const *src,
           $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return mempmove(dst, src, elem_count);

	case 2:
		return mempmovew(dst, src, elem_count);

	case 4:
		return mempmovel(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return mempmoveq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return mempmove(dst, src, elem_count * elem_size);
}

@@>> memmoveupc(3)
@@Move memory between potentially overlapping memory
@@blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
@@@return: * : Always re-returns `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
memmoveupc:([[out(elem_count * elem_size)]] void *dst,
            [[in (elem_count * elem_size)]] void const *src,
            $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return memmoveup(dst, src, elem_count);

	case 2:
		return memmoveupw(dst, src, elem_count);

	case 4:
		return memmoveupl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return memmoveupq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return memmoveup(dst, src, elem_count * elem_size);
}

@@>> mempmoveupc(3)
@@Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
@@rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
mempmoveupc:([[out(elem_count * elem_size)]] void *dst,
             [[in (elem_count * elem_size)]] void const *src,
             $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return mempmoveup(dst, src, elem_count);

	case 2:
		return mempmoveupw(dst, src, elem_count);

	case 4:
		return mempmoveupl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return mempmoveupq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return mempmoveup(dst, src, elem_count * elem_size);
}

@@>> memmovedownc(3)
@@Move memory between potentially overlapping memory
@@blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
@@@return: * : Always re-returns `dst'
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
memmovedownc:([[out(elem_count * elem_size)]] void *dst,
              [[in (elem_count * elem_size)]] void const *src,
              $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return memmovedown(dst, src, elem_count);

	case 2:
		return memmovedownw(dst, src, elem_count);

	case 4:
		return memmovedownl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return memmovedownq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return memmovedown(dst, src, elem_count * elem_size);
}

@@>> mempmovedownc(3)
@@Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
@@rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
[[preferred_fastbind, libc, leaf]]
[[impl_include("<hybrid/host.h>"), decl_include("<hybrid/typecore.h>")]]
mempmovedownc:([[out(elem_count * elem_size)]] void *dst,
               [[in (elem_count * elem_size)]] void const *src,
               $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
@@pp_ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS@@
	switch (elem_size) {

	case 1:
		return mempmovedown(dst, src, elem_count);

	case 2:
		return mempmovedownw(dst, src, elem_count);

	case 4:
		return mempmovedownl(dst, src, elem_count);

@@pp_ifdef __UINT64_TYPE__@@
	case 8:
		return mempmovedownq(dst, src, elem_count);
@@pp_endif@@

	default:
		break;
	}
@@pp_endif@@
	return mempmovedown(dst, src, elem_count * elem_size);
}




/* KOS String extension functions. */
@@>> strend(3)
@@Same as `str + strlen(str)'
[[libc, kernel, pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STREND))]]
[[nonnull]] char *strend([[in]] char const *__restrict str)
	[([[in]] char *__restrict str): [[nonnull]] char *]
	[([[in]] char const *__restrict str): [[nonnull]] char const *]
{
	while (*str)
		++str;
	return (char *)str;
}

@@>> strnend(3)
@@Same as `str + strnlen(str, max_chars)'
[[libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNEND))]]
[[nonnull]] char *strnend([[in(strnlen(., maxlen))]] char const *__restrict str, $size_t maxlen)
	[([[in(strnlen(., maxlen))]] char *__restrict str, $size_t maxlen): [[nonnull]] char *]
	[([[in(strnlen(., maxlen))]] char const *__restrict str, $size_t maxlen): [[nonnull]] char const *]
{
	for (; maxlen && *str; ++str, --maxlen)
		;
	return (char *)str;
}

@@>> strnchr(3)
@@Same as `strchr', but don't exceed `max_chars' characters.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCHR))]]
char *strnchr([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[in(strnlen(., maxlen))]] char *__restrict haystack, int needle, $size_t maxlen): char *]
	[([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen): char const *]
{
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			return (char *)haystack;
	}
	return NULL;
}

@@>> strnrchr(3)
@@Same as `strrchr', but don't exceed `max_chars' characters.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNRCHR))]]
char *strnrchr([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[in(strnlen(., maxlen))]] char *__restrict haystack, int needle, $size_t maxlen): char *]
	[([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen): char const *]
{
	char const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@>> strrchrnul(3)
@@Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
[[pure, wunused]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRRCHRNUL))]]
[[nonnull]] char *strrchrnul([[in]] char const *__restrict haystack, int needle)
	[([[in]] char *__restrict haystack, int needle): [[nonnull]] char *]
	[([[in]] char const *__restrict haystack, int needle): [[nonnull]] char const *]
{
	char const *result = haystack - 1;
	do {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	} while (*haystack++);
	return (char *)result;
}

@@>> strnchrnul(3)
@@Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCHRNUL))]]
[[nonnull]] char *strnchrnul([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[in(strnlen(., maxlen))]] char *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char *]
	[([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char const *]
{
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack)
		;
	return (char *)haystack;
}

@@>> strnrchrnul(3)
@@Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNRCHRNUL))]]
[[nonnull]] char *strnrchrnul([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[in(strnlen(., maxlen))]] char *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char *]
	[([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char const *]
{
	char const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@>> stroff(3)
@@Same as `strchrnul', but return the offset from `str', rather than the actual address
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STROFF))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t stroff([[in]] char const *__restrict haystack, int needle) {
	return (size_t)(strchrnul(haystack, needle) - haystack);
}

@@>> strroff(3)
@@Same as `strrchrnul', but return the offset from `str', rather than the actual address
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRROFF))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t strroff([[in]] char const *__restrict haystack, int needle) {
	return (size_t)(strrchrnul(haystack, needle) - haystack);
}

@@>> strnoff(3)
@@Same as `strnchrnul', but return the offset from `str', rather than the actual address
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNOFF))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t strnoff([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen) {
	return (size_t)(strnchrnul(haystack, needle, maxlen) - haystack);
}

@@>> strnroff(3)
@@Same as `strnrchrnul', but return the offset from `str', rather than the actual address
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRNROFF))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t strnroff([[in(strnlen(., maxlen))]] char const *__restrict haystack, int needle, $size_t maxlen) {
	return (size_t)(strnrchrnul(haystack, needle, maxlen) - haystack);
}


@@>> mempset(3)
@@Same as `memset', but return `dst + n_bytes', rather than `dst'
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSET))]]
[[impl_include("<hybrid/typecore.h>")]]
mempset:([[out(n_bytes)]] void *__restrict dst, int byte, $size_t n_bytes) -> [[== dst + n_bytes]] void * {
	return (void *)((byte_t *)memset(dst, byte, n_bytes) + n_bytes);
}

@@>> mempmove(3)
@@Same as `memmove', but return `dst + n_bytes', rather than `dst'
[[preferred_fastbind, libc, kernel, leaf, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVE))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *mempmove:([[out(n_bytes)]] void *dst,
                            [[in (n_bytes)]] void const *src,
                            $size_t n_bytes) {
	return (void *)((byte_t *)memmove(dst, src, n_bytes) + n_bytes);
}

@@>> mempmoveup(3)
@@Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes')
[[libc, kernel, leaf, alias("mempmove"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(mempmoveup, ["mempmoveup", "mempmove"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUP))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *mempmoveup:([[out(n_bytes)]] void *dst,
                              [[in (n_bytes)]] void const *src,
                              $size_t n_bytes) {
	return (void *)((byte_t *)memmoveup(dst, src, n_bytes) + n_bytes);
}

@@>> mempmovedown(3)
@@Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes')
[[libc, kernel, leaf, alias("mempmove"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(mempmovedown, ["mempmovedown", "mempmove"])]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWN))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *mempmovedown:([[out(n_bytes)]] void *dst,
                                [[in (n_bytes)]] void const *src,
                                $size_t n_bytes) {
	return (void *)((byte_t *)memmovedown(dst, src, n_bytes) + n_bytes);
}

%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(mempmove = mempmovec, externLinkageOverride: "C++")]
%[insert:function(mempmoveup = mempmoveupc, externLinkageOverride: "C++")]
%[insert:function(mempmovedown = mempmovedownc, externLinkageOverride: "C++")]
%[insert:function(memmoveup = memmoveupc, externLinkageOverride: "C++")]
%[insert:function(memmovedown = memmovedownc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */


@@>> rawmemrchr(3)
@@Same as `memrchr' without a search limit, starting at `haystack - 1'
[[kernel, pure, wunused, impl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHR))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *rawmemrchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter == (byte_t)needle)
			break;
	}
	return iter;
}


/* This could be an idea. - But it may also turn out like memxch(), and never be used... */
//[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
//void *memdiff([[in(n_bytes)]] void const *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes)
//	[([[in(n_bytes)]] void *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes): void *]
//	[([[in(n_bytes)]] void const *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes): void const *]
//{
//	byte_t  *diter   =  (byte_t   *)data;
//	byte_t *biter  = (byte_t  *)baseline;
//	for (; n_bytes--; ++diter, ++biter) {
//		if unlikely(*diter != *biter)
//			return diter;
//	}
//	return NULL;
//}
//[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
//void *memrdiff([[in(n_bytes)]] void const *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes)
//	[([[in(n_bytes)]] void *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes): void *]
//	[([[in(n_bytes)]] void const *__restrict data, [[in(n_bytes)]] void const *__restrict baseline, $size_t n_bytes): void const *]
//{
//	byte_t  *diter  = (byte_t  *)data  + n_bytes;
//	byte_t *biter = (byte_t *)baseline + n_bytes;
//	while (n_bytes--) {
//		if unlikely(*--diter != *--biter)
//			return diter;
//	}
//	return NULL;
//}

@@>> memend(3)
@@Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMEND))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memend([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == (byte_t)needle)
			break;
	}
	return result;
}

@@>> memrend(3)
@@Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found.
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMREND))]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] void *memrend([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[in(n_bytes)]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	for (;;) {
		--result;
		if unlikely(!n_bytes)
			break;
		if unlikely(*result == (byte_t)needle)
			break;
		--n_bytes;
	}
	return result;
}

@@>> memlen(3)
@@Same as `memend', but return the offset from `haystack', rather than the actual address.
@@Returns `n_bytes' if the given `needle' wasn't found
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memlen([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@>> memrlen(3)
@@Same as `memrend', but return the offset from `haystack', rather than the actual address.
@@Returns `(size_t)-1' if the given `needle' wasn't found
[[preferred_fastbind, libc, kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t memrlen([[in(n_bytes)]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@>> rawmemlen(3)
@@Same as `rawmemchr', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemlen([[in]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemchr(haystack, needle) - (byte_t *)haystack);
}

@@>> rawmemrlen(3)
@@Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLEN))]]
[[impl_include("<hybrid/typecore.h>")]]
$size_t rawmemrlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemrchr(haystack, needle) - (byte_t *)haystack);
}


@@>> memrmem(3)
@@Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[libc, pure, wunused, decl_include("<hybrid/typecore.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>") defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memrmem0")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memrmem")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRMEM))]]
[[impl_include("<hybrid/typecore.h>", "<features.h>")]]
void *memrmem([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen)
	[([[in(haystacklen)]] void *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): void *]
	[([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): void const *]
{
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= needlelen - 1;
	marker = *(uint8_t const *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (bcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}


@@>> mempatb(3)
@@Same as `memsetb', but repeat a 1-byte pattern on aligned addresses.
[[nocrt, leaf, alias("memset"), decl_include("<hybrid/typecore.h>")]]
[[preferred_fastbind(memset(dst, pattern, n_bytes))]]
[[bind_local_function("memset")]]
mempatb:([[out(n_bytes)]] void *__restrict dst,
         int pattern, $size_t n_bytes) -> [[== dst]] void *;

@@>> mempatw(3)
@@Same as `memsetw', but repeat a 2-byte pattern on aligned addresses.
[[preferred_fastbind, libc, kernel, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATW))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__wordbits.h>")]]
mempatw([[out(n_bytes)]] void *__restrict dst,
        $uint16_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	if (n_bytes && (uintptr_t)iter & 1) {
		*iter = __INT16_BYTE(pattern, 1);
		++iter;
		--n_bytes;
	}
	iter = (byte_t *)mempsetw(iter, pattern, n_bytes / 2);
	if (n_bytes & 1)
		*iter = __INT16_BYTE(pattern, 0);
	return dst;
}

@@>> mempatl(3)
@@Same as `memsetl', but repeat a 4-byte pattern on aligned addresses.
[[preferred_fastbind, libc, kernel, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATL))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__wordbits.h>")]]
mempatl([[out(n_bytes)]] void *__restrict dst,
        $uint32_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 3; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	iter = (byte_t *)mempsetl(iter, pattern, n_bytes / 4);
	for (n_bytes &= 3; n_bytes; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	return dst;
}

%#ifdef __UINT64_TYPE__
@@>> mempatq(3)
@@Same as `memsetq', but repeat an 8-byte pattern on aligned addresses.
[[preferred_fastbind, libc, kernel, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATQ))]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__wordbits.h>")]]
mempatq([[out(n_bytes)]] void *__restrict dst,
        $uint64_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 7; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	iter = (byte_t *)mempsetq(iter, pattern, n_bytes / 8);
	for (n_bytes &= 7; n_bytes; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	return dst;
}
%#endif /* __UINT64_TYPE__ */

%{

/* memsetc() and mempsetc() */
#if defined(__cplusplus) && defined(__INTELLISENSE__)
extern "C++" {
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(memsetc)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(mempsetc)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
} /* extern "C++" */
#elif defined(__UINT64_TYPE__)
#ifndef __NO_builtin_choose_expr
#define memsetc(dst, word, word_count, word_size)                                                             \
	__builtin_choose_expr((word_size) == 1,                                                                   \
	                      (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                                   \
	                      (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count),                          \
	__builtin_choose_expr((word_size) == 4,                                                                   \
	                      (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count),                          \
	                      (void *)memsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#define mempsetc(dst, word, word_count, word_size)                                         \
	__builtin_choose_expr((word_size) == 1,                                                \
	                      (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                \
	                      (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count),      \
	__builtin_choose_expr((word_size) == 4,                                                \
	                      (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count),      \
	                      (void *)mempsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#else /* !__NO_builtin_choose_expr */
#define memsetc(dst, word, word_count, word_size)                                         \
	((word_size) == 1                                                                     \
	 ? (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                                   \
	   ? (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count)                        \
	   : (word_size) == 4                                                                 \
	     ? (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count)                      \
	     : (void *)memsetq(dst, (__UINT64_TYPE__)(word), word_count))
#define mempsetc(dst, word, word_count, word_size)                     \
	((word_size) == 1                                                  \
	 ? (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                \
	   ? (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count)    \
	   : (word_size) == 4                                              \
	     ? (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count)  \
	     : (void *)mempsetq(dst, (__UINT64_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifndef __NO_builtin_choose_expr
#define memsetc(dst, word, word_count, word_size)                                                             \
	__builtin_choose_expr((word_size) == 1,                                                                   \
	                      (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                                   \
	                      (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count),                          \
	                      (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#define mempsetc(dst, word, word_count, word_size)                                         \
	__builtin_choose_expr((word_size) == 1,                                                \
	                      (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                \
	                      (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count),      \
	                      (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#else /* !__NO_builtin_choose_expr */
#define memsetc(dst, word, word_count, word_size)                                         \
	((word_size) == 1                                                                     \
	 ? (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                                   \
	   ? (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count)                        \
	   : (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count))
#define mempsetc(dst, word, word_count, word_size)                     \
	((word_size) == 1                                                  \
	 ? (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                \
	   ? (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count)    \
	   : (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */

}



@@>> memcasecmp(3), memcasecmp_l(3)
[[decl_include("<hybrid/typecore.h>")]]
[[kernel, pure, wunused, alias("memicmp", "_memicmp")]]
[[if(!defined(__KERNEL__)), export_as("memicmp")]]
[[if(!defined(__KERNEL__)), dos_only_export_as("_memicmp")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[impl_include("<hybrid/typecore.h>")]]
int memcasecmp([[in(num_chars)]] void const *s1,
               [[in(num_chars)]] void const *s2, $size_t num_chars) {
	unsigned char const *p1 = (unsigned char const *)s1;
	unsigned char const *p2 = (unsigned char const *)s2;
	unsigned char v1, v2;
	v1 = 0;
	v2 = 0;
	while (num_chars--) {
		v1 = *p1++;
		v2 = *p2++;
		if (v1 != v2) {
			v1 = (unsigned char)tolower(v1);
			v2 = (unsigned char)tolower(v2);
			if (v1 != v2)
				break;
		}
	}
@@pp_if __SIZEOF_CHAR__ < __SIZEOF_INT__@@
	return (int)v1 - (int)v2;
@@pp_else@@
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
@@pp_endif@@
}


@@>> memcasemem(3), memcasemem_l(3)
@@Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@During comparisons, casing of character is ignored (s.a. `memmem()')
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[pure, wunused, decl_include("<hybrid/typecore.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>") defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memcasemem0")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memcasemem")]]
[[impl_include("<features.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
void *memcasemem([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen)
	[([[in(haystacklen)]] void *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): void *]
	[([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen): void const *]
{
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

%#ifdef __USE_XOPEN2K8
[[decl_include("<hybrid/typecore.h>"), doc_alias("memcasecmp")]]
[[pure, wunused, dos_only_export_alias("_memicmp_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
int memcasecmp_l([[in(num_chars)]] void const *s1,
                 [[in(num_chars)]] void const *s2,
                 $size_t num_chars, $locale_t locale) {
	(void)locale;
	return memcasecmp(s1, s2, num_chars);
}


[[pure, wunused, decl_include("<hybrid/typecore.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>") defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memcasemem0_l")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), alias("memcasemem_l")]]
[[impl_include("<features.h>"), doc_alias("memcasemem")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
[[impl_include("<hybrid/typecore.h>")]]
void *memcasemem_l([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen, $locale_t locale)
	[([[in(haystacklen)]] void *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen, $locale_t locale): void *]
	[([[in(haystacklen)]] void const *haystack, $size_t haystacklen, [[in(needlelen)]] void const *needle, $size_t needlelen, $locale_t locale): void const *]
{
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

[[pure, wunused, doc_alias("strcasestr")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
[[impl_include("<hybrid/typecore.h>")]]
char *strcasestr_l([[in]] char const *haystack, [[in]] char const *needle, $locale_t locale)
	[([[in]] char *haystack, [[in]] char const *needle, $locale_t locale): char *]
	[([[in]] char const *haystack, [[in]] char const *needle, $locale_t locale): char const *]
{
	size_t needle_len = strlen(needle);
	for (; *haystack; ++haystack) {
		if (memcasecmp_l(haystack, needle, needle_len * sizeof(char), locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}

%#endif /* __USE_XOPEN2K8 */
%
%
%


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[doc_alias("strdupf"), section(".text.crt{|.dos}.heap.strdup")]]
[[requires_function(vasprintf)]]
char *vstrdupf([[in, format("printf")]] char const *__restrict format, $va_list args) {
	char *result;
	return vasprintf(&result, format, args) >= 0 ? result : NULL;
}

@@>> strdupf(3), vstrdupf(3)
@@Print the given `format' into a newly allocated, heap-allocated string
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[section(".text.crt{|.dos}.heap.strdup")]]
char *strdupf([[in, format("printf")]] char const *__restrict format, ...)
	%{printf(vstrdupf)}

%{
/* mstrdupa() & friends. */
#ifdef __INTELLISENSE__
#define mstrdupa  mstrdupa
#define mstrndupa mstrndupa
#ifdef __malloca_mayfail
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrdupa)(char const *__restrict __string);
#else /* __malloca_mayfail */
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrdupa)(char const *__restrict __string);
#endif /* !__malloca_mayfail */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifdef __malloca_mayfail
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrndupa)(char const *__restrict __string, __size_t __maxlen);
#else /* __malloca_mayfail */
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrndupa)(char const *__restrict __string, __size_t __maxlen);
#endif /* !__malloca_mayfail */
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#elif defined(__NO_XBLOCK)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__mstrdupa_init)(void *__buf, char const *__restrict __string) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__buf = __NAMESPACE_STD_SYM strcpy((char *)__buf, __string);
	}
	return (char *)__buf;
}
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__mstrndupa_init)(void *__buf, char const *__restrict __string, __size_t __maxlen) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__size_t __buflen = strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
		*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
		((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	}
	return (char *)__buf;
}
#endif /* __USE_XOPEN2K8 || __USE_DOS */
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `str' argument... */
#define mstrdupa(str) \
	__mstrdupa_init(__malloca((__NAMESPACE_STD_SYM strlen(str) + 1) * sizeof(char)), str)
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen) \
	__mstrndupa_init(__malloca((strnlen(str, maxlen) + 1) * sizeof(char)), str, maxlen)
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __NO_XBLOCK */
#ifdef __malloca_mayfail
#define mstrdupa(str)                                                                     \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN __likely(__copy_s)                                                      \
		          ? (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len)    \
		          : __copy_s;                                                             \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen)                                               \
	__XBLOCK({                                                               \
		char const *__orig_s = (str);                                        \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);     \
		char *__copy_s       = (char *)__malloca(__orig_len + sizeof(char)); \
		if __likely(__copy_s) {                                              \
			__copy_s[__orig_len / sizeof(char)] = 0;                         \
			__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);      \
		}                                                                    \
		__XRETURN __copy_s;                                                  \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __malloca_mayfail */
#define mstrdupa(str)                                                                     \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);     \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen)                                                        \
	__XBLOCK({                                                                        \
		char const *__orig_s = (str);                                                 \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);              \
		char *__copy_s = (char *)__malloca(__orig_len + sizeof(char));                \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#endif /* !__malloca_mayfail */
#endif /* !__NO_XBLOCK */
}


/* TODO: strdupaf() */
/* TODO: vstrdupaf() */
/* TODO: mstrdupaf() */
/* TODO: vmstrdupaf() */


@@>> wildstrcmp(3)
[[pure, wunused]]
int wildstrcmp([[in]] char const *pattern,
               [[in]] char const *string) {
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(unsigned char)*pattern;
		}
		if (!*pattern)
			return (int)(unsigned char)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			char card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!wildstrcmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*pattern == *string || *pattern == '?') {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)*string - (unsigned char)*pattern);
}

@@>> wildstrcasecmp(3)
[[pure, wunused, section(".text.crt{|.dos}.unicode.static.memory")]]
int wildstrcasecmp([[in]] char const *pattern,
                   [[in]] char const *string) {
	char pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			char card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char)tolower((unsigned char)card_post);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == (char)tolower((unsigned char)ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!wildstrcasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch  = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		    (pattern_ch = (char)tolower((unsigned char)pattern_ch),
		     string_ch  = (char)tolower((unsigned char)string_ch),
		     pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

@@>> fuzzy_strcmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, requires_function(fuzzy_memcmp)]]
$size_t fuzzy_strcmp([[in]] char const *s1, [[in]] char const *s2) {
	return fuzzy_memcmp(s1, strlen(s1), s2, strlen(s2));
}

@@>> fuzzy_strncmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, requires_function(fuzzy_memcmp)]]
$size_t fuzzy_strncmp([[in(strnlen(., s1_maxlen))]] char const *s1, $size_t s1_maxlen,
                      [[in(strnlen(., s2_maxlen))]] char const *s2, $size_t s2_maxlen) {
	return fuzzy_memcmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

@@>> fuzzy_strcasecmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[pure, wunused, requires_function(fuzzy_memcasecmp)]]
$size_t fuzzy_strcasecmp([[in]] char const *s1, [[in]] char const *s2) {
	return fuzzy_memcasecmp(s1, strlen(s1), s2, strlen(s2));
}

@@>> fuzzy_strncasecmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[pure, wunused, requires_function(fuzzy_memcasecmp)]]
$size_t fuzzy_strncasecmp([[in(strnlen(., s1_maxlen))]] char const *s1, $size_t s1_maxlen,
                          [[in(strnlen(., s2_maxlen))]] char const *s2, $size_t s2_maxlen) {
	return fuzzy_memcasecmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

@@>> fuzzy_memcmp(3)
[[pure, wunused, requires_include("<parts/malloca.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires(!defined(__NO_MALLOCA))]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcmp([[in(s1_bytes)]] void const *s1, $size_t s1_bytes,
                     [[in(s2_bytes)]] void const *s2, $size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			cost  = ((byte_t *)s1)[i] != ((byte_t *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

@@>> fuzzy_memcasecmp(3)
[[pure, wunused, requires_include("<parts/malloca.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires(!defined(__NO_MALLOCA))]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcasecmp([[in(s1_bytes)]] void const *s1, $size_t s1_bytes,
                         [[in(s2_bytes)]] void const *s2, $size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (tolower((unsigned char)c1) !=
			                     tolower((unsigned char)c2));
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __USE_XOPEN2K8
[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, requires_function(fuzzy_memcasecmp_l)]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
$size_t fuzzy_strcasecmp_l([[in]] char const *s1,
                           [[in]] char const *s2,
                           $locale_t locale) {
	return fuzzy_memcasecmp_l(s1, strlen(s1), s2, strlen(s2), locale);
}

[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, requires_function(fuzzy_memcasecmp_l)]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
$size_t fuzzy_strncasecmp_l([[in(strnlen(., s1_maxlen))]] char const *s1, $size_t s1_maxlen,
                            [[in(strnlen(., s2_maxlen))]] char const *s2, $size_t s2_maxlen,
                            $locale_t locale) {
	return fuzzy_memcasecmp_l(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen), locale);
}

[[pure, wunused, section(".text.crt{|.dos}.unicode.locale.memory")]]
int wildstrcasecmp_l([[in]] char const *pattern,
                     [[in]] char const *string, $locale_t locale) {
	char pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			char card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char)tolower_l(card_post, locale);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == (char)tolower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!strcasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch  = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		    (pattern_ch = (char)tolower_l((unsigned char)pattern_ch, locale),
		     string_ch  = (char)tolower_l((unsigned char)string_ch, locale),
		     pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

[[pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA))]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcasecmp_l([[in(s1_bytes)]] void const *s1, $size_t s1_bytes,
                           [[in(s2_bytes)]] void const *s2, $size_t s2_bytes,
                           $locale_t locale) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (tolower_l((unsigned char)c1, locale) !=
			                     tolower_l((unsigned char)c2, locale));
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
%#endif /* __USE_XOPEN2K8 */

%{

#ifdef __USE_STRING_BWLQ
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t fuzzy_memcmpb([[in(s1_bytes)]] void const *s1, $size_t s1_bytes,
                      [[in(s2_bytes)]] void const *s2, $size_t s2_bytes) = fuzzy_memcmp;

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("fuzzy_wmemcmp")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$fuzzy_wmemcmp")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as("DOS$fuzzy_wmemcmp")]]
[[if(!defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$fuzzy_wmemcmp")]]
[[requires_include("<parts/malloca.h>"), requires(!defined(__NO_MALLOCA))]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcmpw([[in(s1_words * 2)]] void const *s1, $size_t s1_words,
                      [[in(s2_words * 2)]] void const *s2, $size_t s2_words) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_words)
		return s2_words;
	if unlikely(!s2_words)
		return s1_words;
	if (s2_words > s1_words) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_words;
			s1_words = s2_words;
			s2_words = temp;
		}
	}
	__malloca_tryhard(v0, (s2_words+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_words+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_words; ++i)
		v0[i] = i;
	for (i = 0; i < s1_words; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_words; j++) {
			cost  = ((u16 *)s1)[i] != ((u16 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_words, sizeof(size_t));
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}


[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, requires_include("<parts/malloca.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("fuzzy_wmemcmp")]]
[[if(defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$fuzzy_wmemcmp")]]
[[export_as("fuzzy_wmemcmp"), requires(!defined(__NO_MALLOCA))]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcmpl([[in(s1_dwords * 4)]] void const *s1, $size_t s1_dwords,
                      [[in(s2_dwords * 4)]] void const *s2, $size_t s2_dwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_dwords)
		return s2_dwords;
	if unlikely(!s2_dwords)
		return s1_dwords;
	if (s2_dwords > s1_dwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_dwords;
			s1_dwords = s2_dwords;
			s2_dwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_dwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_dwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_dwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_dwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_dwords; j++) {
			cost  = ((u32 *)s1)[i] != ((u32 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_dwords, sizeof(size_t));
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __UINT64_TYPE__
[[pure, wunused, requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA)), decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
$size_t fuzzy_memcmpq([[in(s1_qwords * 8)]] void const *s1, $size_t s1_qwords,
                      [[in(s2_qwords * 8)]] void const *s2, $size_t s2_qwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_qwords)
		return s2_qwords;
	if unlikely(!s2_qwords)
		return s1_qwords;
	if (s2_qwords > s1_qwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_qwords;
			s1_qwords = s2_qwords;
			s2_qwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_qwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_qwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_qwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_qwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_qwords; j++) {
			cost  = ((u64 *)s1)[i] != ((u64 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc(v0, v1, s2_qwords, sizeof(size_t));
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */


[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, dos_only_export_alias("_strncoll")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
int strncoll([[in(strnlen(., maxlen))]] char const *s1,
             [[in(strnlen(., maxlen))]] char const *s2,
             $size_t maxlen) {
	/* XXX: Implement properly? */
	return strncmp(s1, s2, maxlen);
}

[[dos_only_export_alias("_stricoll")]]
[[alias("strcasecmp", "_stricmp", "stricmp", "_strcmpi", "strcmpi")]]
[[pure, wunused, section(".text.crt{|.dos}.unicode.static.memory")]]
int strcasecoll([[in]] char const *s1,
                [[in]] char const *s2) {
	/* XXX: Implement properly? */
	return strcasecmp(s1, s2);
}

[[decl_include("<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strnicoll"), alias("strncasecmp")]]
[[pure, wunused, section(".text.crt{|.dos}.unicode.static.memory")]]
int strncasecoll([[in(strnlen(., maxlen))]] char const *s1,
                 [[in(strnlen(., maxlen))]] char const *s2,
                 $size_t maxlen) {
	/* XXX: Implement properly? */
	return strncasecmp(s1, s2, maxlen);
}

[[leaf, decl_include("<hybrid/typecore.h>")]]
strnrev:([[inout(strnlen(., maxlen))]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	return (char *)memrev(str, strnlen(str, maxlen));
}

[[leaf, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
strnlwr:([[inout(strnlen(., maxlen))]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower((unsigned char)ch);
	return str;
}

[[leaf, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
strnupr:([[inout(strnlen(., maxlen))]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper((unsigned char)ch);
	return str;
}

[[leaf, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memrev:([[inout(n_bytes)]] void *__restrict base,
        $size_t n_bytes) -> [[== base]] void * {
	byte_t *iter, *end;
	end = (iter = (byte_t *)base) + n_bytes;
	while (iter < end) {
		byte_t temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return base;
}


%#ifdef __USE_XOPEN2K8
[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, dos_only_export_alias("_strncoll_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
int strncoll_l([[in(strnlen(., maxlen))]] char const *s1,
               [[in(strnlen(., maxlen))]] char const *s2,
               $size_t maxlen, $locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return strncoll(s1, s2, maxlen);
}

[[pure, wunused, dos_only_export_alias("_stricoll_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
int strcasecoll_l([[in]] char const *s1,
                  [[in]] char const *s2,
                  $locale_t locale) {
	/* XXX: Implement properly? */
	return strcasecmp_l(s1, s2, locale);
}

[[decl_include("<hybrid/typecore.h>")]]
[[pure, wunused, dos_only_export_alias("_strnicoll_l")]]
[[alias("strncasecmp_l", "_strnicmp_l", "_strncmpi_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
int strncasecoll_l([[in(strnlen(., maxlen))]] char const *s1,
                   [[in(strnlen(., maxlen))]] char const *s2,
                   $size_t maxlen, $locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return strncasecoll(s1, s2, maxlen);
}

[[leaf, dos_only_export_alias("_strlwr_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
strlwr_l:([[inout]] char *__restrict str, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower_l((unsigned char)ch, locale);
	return str;
}

[[leaf, dos_only_export_alias("_strupr_l")]]
[[section(".text.crt{|.dos}.unicode.locale.memory")]]
strupr_l:([[inout]] char *__restrict str, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper_l((unsigned char)ch, locale);
	return str;
}

[[decl_include("<hybrid/typecore.h>")]]
[[leaf, section(".text.crt{|.dos}.unicode.locale.memory")]]
strnlwr_l:([[inout(strnlen(., maxlen))]] char *__restrict str,
           $size_t maxlen, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower_l((unsigned char)ch, locale);
	return str;
}

[[decl_include("<hybrid/typecore.h>")]]
[[leaf, section(".text.crt{|.dos}.unicode.locale.memory")]]
strnupr_l:([[inout(strnlen(., maxlen))]] char *__restrict str,
           $size_t maxlen, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper_l((unsigned char)ch, locale);
	return str;
}
%#endif /* __USE_XOPEN2K8 */

%#ifdef __USE_STRING_BWLQ
[[leaf, decl_include("<hybrid/typecore.h>")]]
memrevb:([[inout(n_bytes)]] void *__restrict base, $size_t n_bytes) -> [[== base]] $uint8_t * = memrev;

[[leaf, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memrevw:([[inout(n_words * 2)]] void *__restrict base, $size_t n_words) -> [[== base]] $uint16_t * {
	u16 *iter, *end;
	end = (iter = (u16 *)base) + n_words;
	while (iter < end) {
		u16 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u16 *)base;
}

[[leaf, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memrevl:([[inout(n_dwords * 4)]] void *__restrict base, $size_t n_dwords) -> [[== base]] $uint32_t * {
	u32 *iter, *end;
	end = (iter = (u32 *)base) + n_dwords;
	while (iter < end) {
		u32 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u32 *)base;
}

%#ifdef __UINT64_TYPE__
[[leaf, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
memrevq:([[inout(n_qwords * 8)]] void *__restrict base, $size_t n_qwords) -> [[== base]] $uint64_t * {
	u64 *iter, *end;
	end = (iter = (u64 *)base) + n_qwords;
	while (iter < end) {
		u64 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u64 *)base;
}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */

@@>> strcmpz(3)
@@Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
@@Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
@@> char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
@@> *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
@@> return strcmp(lhs, dup);
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
int strcmpz([[in(strnlen(., rhs_len))]] char const *lhs,
            [[in(rhs_len)]] char const *rhs, size_t rhs_len) {
	char c1, c2;
	do {
		c1 = *lhs++;
		if (!rhs_len--) {
			/* Once  RHS  reaches  the end  of  the string,
			 * compare the last character of LHS with `NUL' */
			return (int)((unsigned char)c1 - '\0');
		}
		c2 = *rhs++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@>> strstartcmp(3)
@@Compare the first `strnlen(str, strlen(startswith_str))' characters
@@of `str' with  `startswith_str', returning the  usual >0, <0,  ==0.
[[kernel, pure, wunused]]
int strstartcmp([[in]] char const *str,
                [[in]] char const *startswith) {
	char c1, c2;
	do {
		c2 = *startswith++;
		if (!c2) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		c1 = *str++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);

	/* The given `str' has a  length less than `strlen(startswith)',  meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}

@@>> strstartcmpz(3)
@@Compare the first `strnlen(str, startswith_len)' characters of
@@`str' with  `startswith', returning  the  usual >0,  <0,  ==0.
[[kernel, pure, wunused, decl_include("<hybrid/typecore.h>")]]
int strstartcmpz([[in(strnlen(., startswith_len))]] char const *str,
                 [[in(startswith_len)]] char const *startswith,
                 size_t startswith_len) {
	char c1, c2;
	do {
		if (!startswith_len--) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		c1 = *str++;
		c2 = *startswith++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);

	/* The  given  `str' has  a  length less  than  `startswith_len', meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}


@@>> bitcpy(3)
@@Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
@@doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
@@bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
@@significant bit is at `NBBY-1':
@@>> byte_t src[] = { 0b00001001 };
@@>> byte_t dst[] = { 0b00000000 };
@@>> bitcpy(dst, 4, src, 0, 4);
@@>> assert(dst == 0b10010000);
[[kernel]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
void bitcpy([[out]] void *__restrict dst_base, size_t dst_bit_offset,
            [[in]] void const *__restrict src_base, size_t src_bit_offset,
            size_t num_bits) {
	while (num_bits) {
		byte_t remaining, src_value, remaining_temp;
		src_base = (byte_t const *)src_base + (src_bit_offset / __CHAR_BIT__);
		src_bit_offset %= __CHAR_BIT__;
		remaining = (byte_t)(__CHAR_BIT__ - src_bit_offset);
		if ((size_t)remaining > num_bits)
			remaining = (byte_t)num_bits;
		src_value      = *(byte_t const *)src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			byte_t avail, dst_value;
			dst_base = (byte_t *)dst_base + (dst_bit_offset / __CHAR_BIT__);
			dst_bit_offset %= __CHAR_BIT__;
			avail = (byte_t)(__CHAR_BIT__ - dst_bit_offset);
			if (avail > remaining_temp)
				avail = remaining_temp;
			dst_value = *(byte_t *)dst_base;
			dst_value &= ~(((1 << avail) - 1) << dst_bit_offset);
			dst_value |= (src_value & ((1 << avail) - 1)) << dst_bit_offset;
			*(byte_t *)dst_base = dst_value;
			dst_bit_offset += avail;
			remaining_temp -= avail;
			src_value >>= avail;
		}
		src_bit_offset += remaining;
		num_bits -= remaining;
	}
}


@@>> strrstr(3)
@@Find the last instance of `needle' appearing as a sub-string within `haystack'
@@If no such needle exists, return `NULL'
[[wunused, pure]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_STRRSTR))]]
char *strrstr([[in]] char const *haystack, [[in]] char const *needle)
	[([[in]] char *haystack, [[in]] char const *needle): char *]
	[([[in]] char const *haystack, [[in]] char const *needle): char const *]
{
	char *result = NULL;
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			result = (char *)haystack - 1;
		}
miss:
		;
	}
	return result;
}

@@>> strlstrip(3)
@@Skip all leading `isspace(3)'-characters of `str' to return a pointer
@@to  the first  non-space character (or  the trailing NUL  if `str' is
@@empty or contains only spaces).
@@NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
@@@return: * : Pointer to the first non-space character in `str'
[[kernel, nonnull, wunused, pure, requires_function(isspace)]]
[[impl_include("<libc/unicode.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
char *strlstrip([[in]] char const *str)
	[([[in]] char *str): [[nonnull]] char *]
	[([[in]] char const *str): [[nonnull]] char const *]
{
	/* NOTE: assert(!isspace('\0'));
	 * -> So we don't need special handling to stop on NUL! */
@@pp_if $has_function(__unicode_descriptor) && __SIZEOF_CHAR__ == 1@@
	/* Unicode support */
	for (;;) {
		unsigned char ch = (unsigned char)*str;
		if (isspace(ch)) {
			/* Fast-pass: ASCII space characters. */
			++str;
		} else if (ch >= 0x80) {
			char const *new_str = str;
			char32_t uni = @__libc_unicode_readutf8@(&new_str);
			if (!__libc_unicode_isspace(uni))
				break;
			str = new_str;
		} else {
			break;
		}
	}
@@pp_else@@
@@pp_if __SIZEOF_CHAR__ == 2@@
	/* NOTE: No  need for special  handling for UTF-16 surrogates:
	 *       there are no unicode whitespace characters that would
	 *       need to be  encoded using surrogates  (so any  UTF-16
	 *       character that  might be  a space  is always  encoded
	 *       using a single word) */
@@pp_endif@@
	while (isspace((unsigned char)*str))
		++str;
@@pp_endif@@
	return (char *)str;
}

@@>> strrstrip(3)
@@Find the last trailing `isspace(3)'-character (i.e. the one closest
@@to the start and not followed by a non-`isspace(3)'-character), and
@@replace it with '\0', effectively deleting trailing space.
@@NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
@@@return: * : Always re-returns `str'
[[kernel, nonnull, wunused, requires_function(isspace)]]
[[impl_include("<libc/unicode.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
char *strrstrip([[in]] char *str) {
	char *endp = strend(str);
@@pp_if $has_function(__unicode_descriptor) && __SIZEOF_CHAR__ == 1@@
	/* Unicode support */
	for (;;) {
		unsigned char ch = (unsigned char)endp[-1];
		if (isspace(ch)) {
			/* Fast-pass: ASCII space characters. */
			--endp;
		} else if (ch >= 0x80) {
			char const *new_endp = endp;
			char32_t uni;
			uni = @__libc_unicode_readutf8_rev_n@(&new_endp, str);
			if (!__libc_unicode_isspace(uni))
				break;
			endp = (char *)new_endp;
		} else {
			break;
		}
	}
@@pp_else@@
@@pp_if __SIZEOF_CHAR__ == 2@@
	/* NOTE: No  need for special  handling for UTF-16 surrogates:
	 *       there are no unicode whitespace characters that would
	 *       need to be  encoded using surrogates  (so any  UTF-16
	 *       character that  might be  a space  is always  encoded
	 *       using a single word) */
@@pp_endif@@
	while (endp > str && isspace((unsigned char)endp[-1]))
		--endp;
@@pp_endif@@
	*endp = '\0'; /* Delete trailing space. */
	return str;
}

@@>> strstrip(3)
@@The combination of `strlstrip(3)' and `strrstrip(3)'
@@@return: * : Same as `strrstrip(strlstrip(str))'
[[kernel, nonnull, wunused, requires_function(strlstrip, strrstrip)]]
char *strstrip([[in]] char *str) {
	str = strlstrip(str);
	str = strrstrip(str);
	return str;
}

%#endif /* __USE_KOS */

%
%
%#if defined(__USE_KOS) || defined(__USE_DOS)

[[dos_only_export_alias("_strlwr")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
strlwr:([[inout]] char *__restrict str) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower((unsigned char)ch);
	return str;
}

[[dos_only_export_alias("_strupr")]]
[[section(".text.crt{|.dos}.unicode.static.memory")]]
strupr:([[inout]] char *__restrict str) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper((unsigned char)ch);
	return str;
}

[[leaf, dos_only_export_alias("_strset")]]
strset:([[inout]] char *__restrict str, int ch) -> [[== str]] char * {
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[[dos_only_export_alias("_strnset")]]
[[leaf, decl_include("<hybrid/typecore.h>")]]
strnset:([[inout(strnlen(., maxlen))]] char *__restrict str, int ch, $size_t maxlen) -> [[== str]] char * {
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[[leaf, dos_only_export_alias("_strrev")]]
strrev:([[inout]] char *__restrict str) -> [[== str]] char * {
	return (char *)memrev(str, strlen(str));
}
%{
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
}

%[insert:guarded_function(_memccpy = memccpy)]
%[insert:guarded_function(_memicmp = memcasecmp)]
%[insert:guarded_function(_memicmp_l = memcasecmp_l)]
%[insert:guarded_function(memicmp = memcasecmp)]

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t _strset_s([[inout_opt(? <= dstsize)]] char *dst,
                           $size_t dstsize, int ch) {
	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return DOS_EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return DOS_EINVAL;
	}
	__libc_memsetc(p, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%
%#ifdef __USE_DOS_SLIB
[[guard]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t memcpy_s([[out_opt(dstlength)]] void *dst, rsize_t dstlength,
                          [[in_opt (srclength)]] void const *src, rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return DOS_EINVAL;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, __SIZEOF_CHAR__);
		if (!src)
			return DOS_EINVAL;
		if (dstlength < srclength)
			return DOS_ERANGE;
		return DOS_EINVAL;
	}
	__libc_memcpyc(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}

[[guard]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t memmove_s([[out_opt(dstlength)]] void *dst, rsize_t dstlength,
                           [[in_opt(srclength)]] void const *src, rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return DOS_EINVAL;
	if (dstlength < srclength)
		return DOS_ERANGE;
	__libc_memmovec(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}


[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t strcpy_s([[out_opt(dstsize)]] char *dst, $size_t dstsize,
                          [[in_opt]] char const *src) {
	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return DOS_EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return DOS_ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<libc/errno.h>")]]
/*dos*/ $errno_t strcat_s([[inout_opt]] char *dst, $size_t dstsize,
                          [[in_opt]] char const *src) {
	if (!dst || !src)
		return DOS_EINVAL;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return DOS_EINVAL;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return DOS_ERANGE;
	return 0;
}

[[guard, inline, nocrt, pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t strnlen_s([[in_opt(strnlen(., maxlen))]] char const *str, $size_t maxlen) {
	return str ? strnlen(str, maxlen) : 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t strncat_s([[inout_opt]] char *dst, rsize_t dstsize,
                           [[in_opt]] const char *src, rsize_t maxlen) {
	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return DOS_EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return DOS_EINVAL;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return DOS_ERANGE;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return DOS_STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return DOS_ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t strncpy_s([[out_opt(dstsize)]] char *dst, $size_t dstsize,
                           [[in_opt]] char const *src, $size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return DOS_EINVAL;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return DOS_ERANGE;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return DOS_STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return DOS_ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%[insert:function(strtok_s = strtok_r)]
%#endif /* __USE_DOS_SLIB */

%[insert:function(_strdup = strdup)]
%[insert:function(_stricmp = strcasecmp)]
%[insert:function(_strcmpi = strcasecmp)]
%[insert:function(_stricmp_l = strcasecmp_l)]
%[insert:function(_strcoll_l = strcoll_l)]
%[insert:function(_stricoll = strcasecoll)]
%[insert:function(_stricoll_l = strcasecoll_l)]
%[insert:function(_strncoll = strncoll)]
%[insert:function(_strncoll_l = strncoll_l)]
%[insert:function(_strnicoll = strncasecoll)]
%[insert:function(_strnicoll_l = strncasecoll_l)]

[[cp, wunused, section(".text.crt.dos.errno")]]
[[requires_function(_strerror_s)]]
char *_strerror([[in_opt]] char const *message) {
@@pp_if $has_function(realloc)@@
	/* Buffer is typed as `void *' so it can be re-used for `_wcserror(3)' */
	@@static void *_strerror_buf = NULL; [fini: free(_strerror_buf)]@@
	errno_t error;
@@pp_if $has_function(malloc_usable_size)@@
	size_t bufsize = malloc_usable_size(_strerror_buf) / sizeof(char);
@@pp_else@@
	size_t bufsize = _strerror_buf ? 64 : 0;
@@pp_endif@@
	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = realloc(_strerror_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		_strerror_buf = newbuf;
	}
@@pp_ifdef ERANGE@@
again:
@@pp_endif@@
	error = _strerror_s((char *)_strerror_buf, bufsize, message);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = strlen((char *)_strerror_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = realloc(_strerror_buf, retlen * sizeof(char));
			if likely(retbuf)
				_strerror_buf = retbuf;
		}
		return (char *)_strerror_buf;
	}
@@pp_ifdef ERANGE@@
	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = realloc(_strerror_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		_strerror_buf = newbuf;
		goto again;
	}
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(_strerror_buf);
	_strerror_buf = NULL;
@@pp_endif@@
err:
	return NULL;
@@pp_else@@
	static char _strerror_buf[64];
	if likely(_strerror_s(_strerror_buf, COMPILER_LENOF(_strerror_buf), message) == 0)
		return _strerror_buf;
	return NULL;
@@pp_endif@@
}

[[cp]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<libc/errno.h>")]]
[[requires(defined(__libc_geterrno))]]
[[section(".text.crt.dos.errno")]]
[[impl_include("<bits/types.h>", "<libc/errno.h>")]]
/*dos*/ $errno_t _strerror_s([[out(buflen)]] char *__restrict buf, $size_t buflen,
                             [[in_opt]] char const *message) {
	char const *string;
	size_t reqlen;
	errno_t eno = __libc_geterrno();
	string = strerrordesc_np(eno);
	if (string) {
		if (message) {
			reqlen = snprintf(buf, buflen, "%s: %s\n", message, string);
		} else {
			reqlen = snprintf(buf, buflen, "%s\n", string);
		}
	} else if (message) {
		reqlen = snprintf(buf, buflen, "%s: Unknown error %d\n", message, eno);
	} else {
		reqlen = snprintf(buf, buflen, "Unknown error %d\n", eno);
	}
	if (reqlen > buflen)
		return DOS_ERANGE;
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.unicode.static.memory")]]
[[impl_include("<libc/errno.h>")]]
/*dos*/ $errno_t _strlwr_s([[inout_opt]] char *buf, $size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return DOS_EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return DOS_EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower((unsigned char)ch);
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.unicode.static.memory")]]
/*dos*/ $errno_t _strupr_s([[inout_opt]] char *buf, $size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return DOS_EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return DOS_EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper((unsigned char)ch);
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.unicode.locale.memory")]]
/*dos*/ $errno_t _strlwr_s_l([[inout_opt]] char *buf, $size_t buflen, $locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return DOS_EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return DOS_EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)tolower_l((unsigned char)ch, locale);
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.unicode.locale.memory")]]
/*dos*/ $errno_t _strupr_s_l([[inout_opt]] char *buf, $size_t buflen, $locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return DOS_EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return DOS_EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)toupper_l((unsigned char)ch, locale);
	return 0;
}

%[insert:function(_strnicmp = strncasecmp)]
%[insert:function(_strnicmp_l = strncasecmp_l)]

[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.string.memory")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<libc/string.h>")]]
/*dos*/ $errno_t _strnset_s([[inout_opt(? <= maxlen)]] char *__restrict buf,
                            $size_t buflen, int ch, $size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return DOS_EINVAL;
	if (maxlen >= buflen)
		return DOS_ERANGE;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (wchar_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, __SIZEOF_CHAR__);
		return DOS_EINVAL;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%[insert:function(_strrev = strrev)]
%[insert:function(_strxfrm_l = strxfrm_l)]
%[insert:function(stricmp = strcasecmp)]
%[insert:function(strcmpi = strcasecmp)]
%[insert:function(strnicmp = strncasecmp)]

/* The following aren't actually defined by DOS, but one might assume that they were */
%[insert:function(_strncmpi = strncasecmp)]
%[insert:function(_strncmpi_l = strncasecmp_l)]
%[insert:function(strncmpi = strncasecmp)]

%{
#endif /* __USE_DOS */

#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p)
#ifndef __INTELLISENSE__
#if __has_builtin(__builtin_strlen)
#ifdef __cplusplus
/* Special handling, so this macro also works as `std::strlen(...)' */
#define strlen(x) size_t(__builtin_constant_p(x) ? __builtin_strlen(x) : (__NAMESPACE_STD_SYM strlen)(x))
#else /* __cplusplus */
#define strlen(x) (__builtin_constant_p(x) ? __builtin_strlen(x) : (strlen)(x))
#endif /* !__cplusplus */
#endif /* __has_builtin(__builtin_strlen) */
#endif /* !__INTELLISENSE__ */
#endif /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p */

/* strdupa() & friends. */
#if defined(__USE_GNU) && defined(__hybrid_alloca)
#ifdef __INTELLISENSE__
#define strdupa  strdupa
#define strndupa strndupa
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strdupa)(char const *__restrict __string);
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strndupa)(char const *__restrict __string, __size_t __maxlen);
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#elif defined(__NO_XBLOCK)
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__strndupa_init)(void *__restrict __buf, char const *__restrict __string, __size_t __maxlen) {
	__size_t __buflen = strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
	*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
	((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	return (char *)__buf;
}
#endif /* __USE_XOPEN2K8 || __USE_DOS */
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `str' argument... */
#define strdupa(str) \
	(__NAMESPACE_STD_SYM strcpy((char *)__hybrid_alloca((__NAMESPACE_STD_SYM strlen(str) + 1) * sizeof(char)), str))
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define strndupa(str, maxlen) \
	__strndupa_init(__hybrid_alloca((strnlen(str, maxlen) + 1) * sizeof(char)), str, maxlen)
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __NO_XBLOCK */
#define strdupa(str)                                                                      \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__hybrid_alloca(__orig_len),         \
		                                             __orig_s, __orig_len);               \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define strndupa(str, maxlen)                                                         \
	__XBLOCK({                                                                        \
		char const *__orig_s = (str);                                                 \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);              \
		char *__copy_s = (char *)__hybrid_alloca(__orig_len + sizeof(char));          \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#endif /* !__NO_XBLOCK */
#endif /* __USE_GNU && __hybrid_alloca */


/* >> void *memset(void *dst, int byte, size_t num_bytes);
 * >> void *memset(void *dst, T word, size_t word_count, size_t word_size);
 * >> void *mempset(void *dst, int byte, size_t num_bytes);
 * >> void *mempset(void *dst, T word, size_t word_count, size_t word_size); */
#ifdef __USE_STRING_OVERLOADS
#if defined(__cplusplus) && defined(__INTELLISENSE__)
extern "C++" {
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(memset)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
#ifdef __USE_KOS
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(mempset)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
#endif /* __USE_KOS */
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_memset_3 (memset)
#ifdef __USE_KOS
#define __PRIVATE_memset_4  memsetc
#define __PRIVATE_mempset_3 (mempset)
#define __PRIVATE_mempset_4 mempsetc
#undef mempset
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempset(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempset(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (args))(args)
#endif /* ... */
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#ifdef __UINT64_TYPE__
#ifndef __NO_builtin_choose_expr
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                                   \
	__builtin_choose_expr((word_size) == 1,                                                    \
	                      (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                    \
	                      (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count),    \
	__builtin_choose_expr((word_size) == 4,                                                    \
	                      (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count),    \
	                      (void *)__libc_memsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#else /* !__NO_builtin_choose_expr */
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                \
	((word_size) == 1                                                       \
	 ? (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count)  \
	 : (word_size) == 2                                                     \
	   ? (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count)   \
	   : (word_size) == 4                                                   \
	     ? (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count) \
	     : (void *)__libc_memsetq(dst, (__UINT64_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifndef __NO_builtin_choose_expr
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                                   \
	__builtin_choose_expr((word_size) == 1,                                                    \
	                      (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                    \
	                      (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count),    \
	                      (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#else /* !__NO_builtin_choose_expr */
#define __PRIVATE_memset_4(dst, word, word_count, word_size)               \
	((word_size) == 1                                                      \
	 ? (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                    \
	   ? (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count)  \
	   : (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */
#endif /* !__USE_KOS */
#undef memset
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define memset(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define memset(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (args))(args)
#endif /* ... */
#endif /* __HYBRID_PP_VA_OVERLOAD */
#endif /* __USE_STRING_OVERLOADS */

#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS) && defined(__HYBRID_PP_VA_OVERLOAD)
/* In C, we can use argument-count overload macros to implement these overloads:
 * >> int memcmp(void const *s1, void const *s2, size_t num_bytes);
 * >> int memcmp(void const *s1, void const *s2, size_t elem_count, size_t elem_size);
 * >> void *memcpy(void *dst, void const *src, size_t num_bytes);
 * >> void *memcpy(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmove(void *dst, void const *src, size_t num_bytes);
 * >> void *memmove(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmoveup(void *dst, void const *src, size_t num_bytes);
 * >> void *memmoveup(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmovedown(void *dst, void const *src, size_t num_bytes);
 * >> void *memmovedown(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempcpy(void *dst, void const *src, size_t num_bytes);
 * >> void *mempcpy(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmove(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmove(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmoveup(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmoveup(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmovedown(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmovedown(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> int bcmp(void const *s1, void const *s2, size_t num_bytes);
 * >> int bcmp(void const *s1, void const *s2, size_t elem_count, size_t elem_size);
 * >> void bzero(void *dst, size_t num_bytes);
 * >> void bzero(void *dst, size_t elem_count, size_t elem_size); */
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
#ifdef __USE_KOS
#define __PRIVATE_memcmp_4  memcmpc
#define __PRIVATE_memcpy_4  memcpyc
#define __PRIVATE_memmove_4 memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 mempcpyc
#endif /* __USE_GNU */
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_memcmp_4  __libc_memcmpc
#define __PRIVATE_memcpy_4  __libc_memcpyc
#define __PRIVATE_memmove_4 __libc_memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 __libc_mempcpyc
#endif /* __USE_GNU */
#endif /* !__USE_KOS */
#define __PRIVATE_memcmp_3  (memcmp)
#define __PRIVATE_memcpy_3  (memcpy)
#define __PRIVATE_memmove_3 (memmove)
#undef memcmp
#undef memcpy
#undef memmove
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define memcmp(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcmp_, (__VA_ARGS__))(__VA_ARGS__)
#define memcpy(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__)
#define memmove(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define memcmp(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcmp_, (args))(args)
#define memcpy(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (args))(args)
#define memmove(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (args))(args)
#endif /* ... */
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_3 (mempcpy)
#undef mempcpy
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempcpy(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempcpy(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (args))(args)
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_KOS
#define __PRIVATE_mempmove_4     mempmovec
#define __PRIVATE_mempmoveup_4   mempmoveupc
#define __PRIVATE_mempmovedown_4 mempmovedownc
#define __PRIVATE_memmoveup_4    memmoveupc
#define __PRIVATE_memmovedown_4  memmovedownc
#define __PRIVATE_mempmove_3     (mempmove)
#define __PRIVATE_mempmoveup_3   (mempmoveup)
#define __PRIVATE_mempmovedown_3 (mempmovedown)
#define __PRIVATE_memmoveup_3    (memmoveup)
#define __PRIVATE_memmovedown_3  (memmovedown)
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempmove(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmoveup(...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmovedown(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#define memmoveup(...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define memmovedown(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempmove(args...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (args))(args)
#define mempmoveup(args...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (args))(args)
#define mempmovedown(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (args))(args)
#define memmoveup(args...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (args))(args)
#define memmovedown(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (args))(args)
#endif /* ... */
#endif /* __USE_KOS */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS && __HYBRID_PP_VA_OVERLOAD */


}
%#if defined(__USE_BSD) || defined(__USE_KOS)

@@>> strnstr(3)
@@Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
@@If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
@@This function originates from BSD, but is also provided as a KOS extension
[[pure, guard, wunused, decl_include("<hybrid/typecore.h>")]]
char *strnstr([[in(strnlen(., haystack_maxlen))]] char const *haystack, [[in]] char const *needle, $size_t haystack_maxlen)
	[([[in(strnlen(., haystack_maxlen))]] char *haystack, [[in]] char const *needle, $size_t haystack_maxlen): char *]
	[([[in(strnlen(., haystack_maxlen))]] char const *haystack, [[in]] char const *needle, $size_t haystack_maxlen): char const *]
{
	char ch, needle_start = *needle++;
	while (haystack_maxlen-- && (ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			size_t maxlen2;
			hay2     = haystack;
			ned_iter = needle;
			maxlen2  = haystack_maxlen;
			while ((ch = *ned_iter++) != '\0') {
				if (!maxlen2-- || *hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}

%#endif /* __USE_BSD || __USE_KOS */

%
%
%#ifdef __USE_BSD
%(auto_source)#include <sys/stat.h>

@@Generate  a file mode representation similar to what's printed by `ls -l'
@@The representation is written to `p', and `mode' is the value as returned
@@by `stat(2)' in `struct stat::st_mode'
@@The format written is:
@@   p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
@@                              S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
@@                              S_IFIFO: 'p' }, else: '?';
@@   p[1]  = mode & S_IRUSR ? 'r' : '-';
@@   p[2]  = mode & S_IWUSR ? 'w' : '-';
@@   p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
@@                                         S_IXUSR | S_ISUID: 's' };
@@   p[4] = mode & S_IRGRP ? 'r' : '-';
@@   p[5] = mode & S_IWGRP ? 'w' : '-';
@@   p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
@@                                         S_IXGRP | S_ISGID: 's' };
@@   p[7] = mode & S_IROTH ? 'r' : '-';
@@   p[8] = mode & S_IWOTH ? 'w' : '-';
@@   p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
@@                                         S_IXOTH | S_ISVTX: 't' };
@@   p[10] = ' '; // '+', if "alternate or additional access control
@@                //          methods associated with the inode"
@@   p[11] = '\0';
[[guard]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.bsd.strstat")]]
[[impl_include("<asm/os/stat.h>")]]
void strmode($mode_t mode, [[out]] char p[12]) {
	char ch;

@@pp_ifndef S_IRUSR@@
#define S_IRUSR 0400 /* Read by owner. */
@@pp_endif@@
@@pp_ifndef S_IWUSR@@
#define S_IWUSR 0200 /* Write by owner. */
@@pp_endif@@
@@pp_ifndef S_IXUSR@@
#define S_IXUSR 0100 /* Execute by owner. */
@@pp_endif@@
@@pp_ifndef S_IRWXU@@
#define S_IRWXU 0700
@@pp_endif@@
@@pp_ifndef S_IRGRP@@
#define S_IRGRP 0040 /* Read by group. */
@@pp_endif@@
@@pp_ifndef S_IWGRP@@
#define S_IWGRP 0020 /* Write by group. */
@@pp_endif@@
@@pp_ifndef S_IXGRP@@
#define S_IXGRP 0010 /* Execute by group. */
@@pp_endif@@
@@pp_ifndef S_IRWXG@@
#define S_IRWXG 0070
@@pp_endif@@
@@pp_ifndef S_IROTH@@
#define S_IROTH 0004 /* Read by others. */
@@pp_endif@@
@@pp_ifndef S_IWOTH@@
#define S_IWOTH 0002 /* Write by others. */
@@pp_endif@@
@@pp_ifndef S_IXOTH@@
#define S_IXOTH 0001 /* Execute by others. */
@@pp_endif@@
@@pp_ifndef S_IRWXO@@
#define S_IRWXO 0007
@@pp_endif@@

	/* First character: File type */
	ch = '?';
@@pp_ifdef S_IFMT@@
	switch (mode & S_IFMT) {
@@pp_ifdef S_IFDIR@@
	case S_IFDIR:  ch = 'd'; break;
@@pp_endif@@
@@pp_ifdef S_IFCHR@@
	case S_IFCHR:  ch = 'c'; break;
@@pp_endif@@
@@pp_ifdef S_IFBLK@@
	case S_IFBLK:  ch = 'b'; break;
@@pp_endif@@
@@pp_ifdef S_IFREG@@
	case S_IFREG:  ch = '-'; break;
@@pp_endif@@
@@pp_ifdef S_IFLNK@@
	case S_IFLNK:  ch = 'l'; break;
@@pp_endif@@
@@pp_ifdef S_IFSOCK@@
	case S_IFSOCK: ch = 's'; break;
@@pp_endif@@
@@pp_ifdef S_IFIFO@@
	case S_IFIFO:  ch = 'p'; break; /* p=pipe */
@@pp_endif@@
	default: break;
	}
@@pp_endif@@
	*p++ = ch;

	*p++ = mode & S_IRUSR ? 'r' : '-';
	*p++ = mode & S_IWUSR ? 'w' : '-';

@@pp_ifdef S_ISUID@@
	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:                 ch = '-'; break;
	case S_IXUSR:           ch = 'x'; break;
	case S_ISUID:           ch = 'S'; break;
	case S_IXUSR | S_ISUID: ch = 's'; break;
	default: __builtin_unreachable();
	}
@@pp_else@@
	ch = mode & S_IXUSR ? 'x' : '-';
@@pp_endif@@
	*p++ = ch;

	*p++ = mode & S_IRGRP ? 'r' : '-';
	*p++ = mode & S_IWGRP ? 'w' : '-';

@@pp_ifdef S_ISGID@@
	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:                 ch = '-'; break;
	case S_IXGRP:           ch = 'x'; break;
	case S_ISGID:           ch = 'S'; break;
	case S_IXGRP | S_ISGID: ch = 's'; break;
	default: __builtin_unreachable();
	}
@@pp_else@@
	ch = mode & S_IXGRP ? 'x' : '-';
@@pp_endif@@
	*p++ = ch;

	*p++ = mode & S_IROTH ? 'r' : '-';
	*p++ = mode & S_IWOTH ? 'w' : '-';

@@pp_ifdef S_ISVTX@@
	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:                 ch = '-'; break;
	case S_IXOTH:           ch = 'x'; break;
	case S_ISVTX:           ch = 'T'; break;
	case S_IXOTH | S_ISVTX: ch = 't'; break;
	default: __builtin_unreachable();
	}
@@pp_else@@
	ch = mode & S_IXOTH ? 'x' : '-';
@@pp_endif@@
	*p++ = ch;

	/* Always space in this implementation */
	*p++ = ' ';

	/* NUL-terminate */
	*p = '\0';
}

@@>> timingsafe_bcmp(3)
@@Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
@@@return: == 0: Memory blocks are equal.
@@@return: != 0: Memory blocks are non-equal.
[[nocrt, no_crt_self_import, wunused/*, pure*/]]
[[decl_include("<hybrid/typecore.h>")]]
[[alias("timingsafe_bcmp", "timingsafe_memcmp")]]
[[bind_local_function(timingsafe_memcmp)]]
int timingsafe_bcmp([[in(n_bytes)]] void const *s1,
                    [[in(n_bytes)]] void const *s2, size_t n_bytes);

@@>> timingsafe_memcmp(3)
@@Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
@@@return: <  0: Block `s1' should be considered less than `s2'
@@@return: == 0: Memory blocks are equal.
@@@return: >  0: Block `s1' should be considered greater than `s2'
[[wunused/*, pure*/]]
[[decl_include("<hybrid/typecore.h>")]]
[[export_as("timingsafe_bcmp")]]
[[section(".text.crt{|.dos}.bsd")]]
[[impl_include("<hybrid/typecore.h>", "<asm/signed-shift.h>")]]
int timingsafe_memcmp([[in(n_bytes)]] void const *s1,
                      [[in(n_bytes)]] void const *s2, size_t n_bytes) {
	int result = 0, finished = 0;
	/* Suppress warnings about ATTR_PURE. Even though they're correct,
	 * don't mark  this function  as `pure'  to prevent  any  compiler
	 * optimizations which  may result  in  the `timingsafe'  part  of
	 * this function's purpose no longer being correct. */
	COMPILER_IMPURE();
	while (n_bytes) {
		int a_le_b, a_gr_b, diff;
		__SBYTE_TYPE__ a, b;
		a = *(__SBYTE_TYPE__ const *)s1;
		b = *(__SBYTE_TYPE__ const *)s2;

		/* a_le_b:
		 *    0  <=> a <= b <=> 0b0???????
		 *   -1  <=> a >  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_le_b = a <= b ? 0 : -1; */
@@pp_ifdef __ARCH_SIGNED_SHIFT_IS_SDIV@@
		a_le_b = (int)((b - a) >> (__CHAR_BIT__ - 1));
@@pp_else@@
		a_le_b = (int)((b - a) / (1 << (__CHAR_BIT__ - 1)));
@@pp_endif@@

		/* a_gr_b:
		 *    0  <=> a >= b <=> 0b0???????
		 *   -1  <=> a <  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_gr_b = a >= b ? 0 : -1; */
@@pp_ifdef __ARCH_SIGNED_SHIFT_IS_SDIV@@
		a_gr_b = (int)((a - b) >> (__CHAR_BIT__ - 1));
@@pp_else@@
		a_gr_b = (int)((a - b) / (1 << (__CHAR_BIT__ - 1)));
@@pp_endif@@

		/* a <  b  <=>  [a_le_b= 0,a_gr_b=-1]   -> diff=-1
		 * a == b  <=>  [a_le_b= 0,a_gr_b= 0]   -> diff= 0
		 * a >  b  <=>  [a_le_b=-1,a_gr_b= 0]   -> diff=+1 */
		diff = a_gr_b - a_le_b;

		/* (finished == 0) <=> (~finished != 0)
		 * (finished == 0) <=> {All preceding bytes were equal}
		 *
		 * >> if ({All preceding bytes were equal})
		 * >>     result = diff; */
		result |= diff & ~finished;

		/* ((a_gr_b | a_le_b) == -1)  <=>  {a != b}
		 *
		 * >> if (a != b)
		 * >>     finished = -1; */
		finished |= a_gr_b | a_le_b;

		s1 = (__SBYTE_TYPE__ const *)s1 + 1;
		s2 = (__SBYTE_TYPE__ const *)s2 + 1;
		--n_bytes;
	}
	return result;
}

%#endif /* __USE_BSD */


%
%#ifdef __USE_CYGWIN
@@>> strtosigno(3)
@@Return the signal number for a given name.
@@e.g.: `strtosigno("SIGINT") == SIGINT'
@@When `name' isn't recognized, return `0' instead.
[[guard, pure, wunused]]
[[decl_include("<bits/types.h>")]]
[[requires_function(signalnumber, isupper)]]
[[impl_include("<hybrid/typecore.h>", "<asm/os/signal.h>")]]
$signo_t strtosigno([[in]] const char *name) {
	size_t i;
	if (name[0] != 'S' || name[1] != 'I' || name[2] != 'G')
		return 0;
	name += 3;
	for (i = 0; name[i]; ++i) {
		if (!isupper(name[i]))
			return 0;
	}
	return signalnumber(name);
}
%#endif /* __USE_CYGWIN */


%
%#ifdef __USE_NETBSD

[[nocrt, no_crt_self_import, guard, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
[[alias("memset", "explicit_memset")]]
[[nonnull]] void *explicit_memset([[out(n_bytes)]] void *__restrict dst,
                                  int byte, size_t n_bytes) {
	void *volatile vdst = dst;
	return memset(vdst, byte, n_bytes);
}

@@>> stresep(3)
@@Same as `strsep(3)', but allow the specification of an additional `escape'
@@character  that will cause  the following character  from `*stringp' to be
@@escaped, and not  be considered  as a separator,  even if  it is  included
@@within `delim'. Note that `escape'-characters (if present) are not removed
@@from  the input  string, meaning that  they will still  appear in returned
@@strings, should they have been present in the original input string.
[[leaf]]
char *stresep([[inout]] char **__restrict stringp,
              [[in]] char const *__restrict delim,
              int escape) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result;; ++iter) {
		char ch = *iter;
		if (!ch)
			break;
		if ((int)(unsigned int)(unsigned char)ch == escape) {
			/* Escape the next character. */
			ch = *++iter;
			if (!ch)
				break;
		}
		if (strchr(delim, ch))
			break;
	}
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

@@>> consttime_memequal(3)
@@Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
@@@return: == 0: Memory blocks are non-equal.
@@@return: != 0: Memory blocks are equal.
[[wunused/*, pure*/]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
int consttime_memequal([[in(n_bytes)]] void const *s1,
                       [[in(n_bytes)]] void const *s2, size_t n_bytes) {
	return timingsafe_memcmp(s1, s2, n_bytes) == 0;
}

%#endif /* __USE_NETBSD */

%
%#ifdef __USE_SOLARIS
@@>> uucopy(2)
@@Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
@@faulty memory access is handled by returning `-1' with `errno=EFAULT'
@@@return: 0 : Success
@@@return: -1: [errno=EFAULT] Faulty memory access
[[decl_include("<hybrid/typecore.h>")]]
[[requires(defined(__KOS__) && defined(__cplusplus) &&
           $has_function(except_nesting_begin, except_nesting_end))]]
[[section(".text.crt{|.dos}.solaris")]]
[[impl_include("<kos/except.h>", "<libc/errno.h>")]]
int uucopy([[in_opt(num_bytes)]] void const *__restrict src,
           [[out_opt(num_bytes)]] void *__restrict dst,
           size_t num_bytes) {
	@NESTED_TRY@ {
		memcpy(dst, src, num_bytes);
	} @EXCEPT@ {
@@pp_if $has_function(except_as_errno, except_data)@@
		return __libc_seterrno(except_as_errno(except_data()));
@@pp_elif defined(EFAULT)@@
		return __libc_seterrno(EFAULT);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
	return 0;
}

@@>> uucopystr(2)
@@Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
@@The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
@@@return: * : The number of copied characters (including trialing NUL; )
@@@return: -1: [errno=EFAULT]       Faulty memory access
@@@return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen'
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires(defined(__KOS__) && defined(__cplusplus) &&
           $has_function(except_nesting_begin, except_nesting_end))]]
[[section(".text.crt{|.dos}.solaris")]]
[[impl_include("<hybrid/typecore.h>", "<kos/except.h>", "<libc/errno.h>")]]
__STDC_INT_AS_SSIZE_T uucopystr([[in_opt]] /*char*/ void const *__restrict src,
                                [[out_opt]] /*char*/ void *__restrict dst, size_t maxlen) {
	size_t result = 0;
	@NESTED_TRY@ {
		byte_t const *s_ptr = (byte_t const *)src;
		byte_t *d_ptr = (byte_t *)dst;
		for (;;) {
			char ch;
			if unlikely(maxlen == 0) {
@@pp_if defined(ENAMETOOLONG)@@
				return __libc_seterrno(ENAMETOOLONG);
@@pp_else@@
				return __libc_seterrno(1);
@@pp_endif@@
			}
			--maxlen;
			COMPILER_BARRIER();
			ch = *s_ptr++;
			*d_ptr++ = ch;
			COMPILER_BARRIER();
			++result;
			if (ch == '\0')
				break;
		}
	} @EXCEPT@ {
@@pp_if $has_function(except_as_errno, except_data)@@
		return __libc_seterrno(except_as_errno(except_data()));
@@pp_elif defined(EFAULT)@@
		return __libc_seterrno(EFAULT);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
	return (__STDC_INT_AS_SSIZE_T)result;
}

%#endif /* __USE_SOLARIS */

%(libc_fast){
#define __libc_PRIVATE_memset1 __libc_memset
#define __libc_PRIVATE_memset2 __libc_memsetw
#define __libc_PRIVATE_memset4 __libc_memsetl
#define __libc_PRIVATE_memset8 __libc_memsetq
#define __libc_PRIVATE_memset(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset##elem_size(dst, word, elem_count)
#define __libc_memsetc(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset(dst, word, elem_count, elem_size)
}


%{

#endif /* __CC__ */

__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wstring.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

#ifdef __SSP_FORTIFY_LEVEL
#include <ssp/string.h>
#endif /* __SSP_FORTIFY_LEVEL */

}


%[default:section(".text.crt{|.dos}.compat.glibc")]

/* Not-declared "fast" string functions from old pre-Glibc 2.25 */
[[hidden, leaf]]
char *__strtok_r_1c([[inout_opt]] char *str, char delim,
                    [[inout]] char **__restrict save_ptr) {
	char *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += __strspn_c1(str, delim);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + __strcspn_c1(str, delim);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}

[[hidden, leaf]]
char *__strsep_1c([[inout]] char **__restrict stringp, char delim) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !(delim == *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

[[hidden, leaf]]
char *__strsep_2c([[inout]] char **__restrict stringp,
                  char delim1, char delim2) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !(delim1 == *iter || delim2 == *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

[[hidden, leaf]]
char *__strsep_3c([[inout]] char **__restrict stringp,
                  char delim1, char delim2, char delim3) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !(delim1 == *iter || delim2 == *iter || delim3 == *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}



/* Not-declared "fast" string functions from old pre-Glibc 2.24 */
[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strcspn_c1([[in]] char const *haystack, int reject) {
	char const *iter = haystack;
	while (*iter && !(reject == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strcspn_c2([[in]] char const *haystack, int reject1, int reject2) {
	char const *iter = haystack;
	while (*iter && !(reject1 == *iter || reject2 == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strcspn_c3([[in]] char const *haystack, int reject1, int reject2, int reject3) {
	char const *iter = haystack;
	while (*iter && !(reject1 == *iter || reject2 == *iter || reject3 == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strspn_c1([[in]] char const *haystack, int accept) {
	char const *iter = haystack;
	while (*iter && (accept == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strspn_c2([[in]] char const *haystack, int accept1, int accept2) {
	char const *iter = haystack;
	while (*iter && (accept1 == *iter || accept2 == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
[[decl_include("<hybrid/typecore.h>")]]
size_t __strspn_c3([[in]] char const *haystack, int accept1, int accept2, int accept3) {
	char const *iter = haystack;
	while (*iter && (accept1 == *iter || accept2 == *iter || accept3 == *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[hidden, leaf]]
char *__strpbrk_c2([[in]] char const *haystack, int accept1, int accept2) {
	char haych;
	while ((haych = *haystack++) != '\0') {
		if (haych == accept1 || haych == accept2)
			return (char *)haystack - 1;
	}
	return NULL;
}

[[hidden, leaf]]
char *__strpbrk_c3([[in]] char const *haystack, int accept1, int accept2, int accept3) {
	char haych;
	while ((haych = *haystack++) != '\0') {
		if (haych == accept1 || haych == accept2 || haych == accept3)
			return (char *)haystack - 1;
	}
	return NULL;
}
