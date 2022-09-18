/* HASH CRC-32:0xa5f8d4c1 */
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
#ifndef GUARD_LIBC_AUTO_STRING_H
#define GUARD_LIBC_AUTO_STRING_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <string.h>

DECL_BEGIN

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

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __size_t rsize_t;
#endif /* !__rsize_t_defined */

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_memcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_memmove)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memset)(void *__restrict dst, int byte, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memset)(void *__restrict dst, int byte, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_memcmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1, void const *s2, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_strlen)(char const *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict str);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strchr)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strrchr)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcmp)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcmp)(char const *s1, char const *s2);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncmp)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncmp)(char const *s1, char const *s2, size_t maxlen);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strstr)(char const *haystack, char const *needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strstr)(char const *haystack, char const *needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_strcpy)(char *__restrict dst, char const *__restrict src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict dst, char const *__restrict src);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_strncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strcat)(char *__restrict dst, char const *__restrict src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict dst, char const *__restrict src);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUT(1) ATTR_INS(2, 3) NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_strncat)(char *__restrict buf, char const *__restrict src, size_t max_srclen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUT(1) ATTR_INS(2, 3) NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf, char const *__restrict src, size_t max_srclen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd_strcspn)(char const *haystack, char const *reject);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack, char const *reject);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd_strspn)(char const *haystack, char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack, char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strpbrk)(char const *haystack, char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strpbrk)(char const *haystack, char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_strtok)(char *str, char const *delim);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_strtok)(char *str, char const *delim);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcoll)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW_NCX(LIBDCALL libd_strxfrm)(char *dst, char const *__restrict src, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst, char const *__restrict src, size_t buflen);
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_strerror)(errno_t errnum);
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror)(errno_t errnum);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_strnlen)(char const *__restrict str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict str, size_t maxlen);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_stpcpy)(char *__restrict buf, char const *__restrict src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf, char const *__restrict src);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stpncpy(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_stpncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stpncpy(3) */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcoll_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW_NCX(LIBDCALL libd_strxfrm_l)(char *dst, char const *__restrict src, size_t buflen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst, char const *__restrict src, size_t buflen, locale_t locale);
INTDEF ATTR_COLD WUNUSED char *NOTHROW_NCX(LIBDCALL libd_strerror_l)(errno_t errnum, locale_t locale);
INTDEF ATTR_COLD WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror_l)(errno_t errnum, locale_t locale);
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_strsignal)(signo_t signo);
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strsignal)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2) char *NOTHROW_NCX(LIBDCALL libd_strndup)(char const *__restrict str, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2) char *NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict str, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strdup)(char const *__restrict string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_strtok_r)(char *str, char const *delim, char **__restrict save_ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *str, char const *delim, char **__restrict save_ptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memrchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBDCALL libd_memmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strcasestr)(char const *haystack, char const *needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack, char const *needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strchrnul)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *NOTHROW_NCX(LIBDCALL libd_rawmemchr)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *NOTHROW_NCX(LIBCCALL libc_rawmemchr)(void const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_basename)(char const *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strverscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strverscmp)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strverscmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strverscmp)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_mempcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strfry(3) */
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strfry)(char *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strfry(3) */
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memfrob)(void *buf, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strncasecmp_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_strerrordesc_np)(errno_t errnum);
#endif /* !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strerrordesc_np)(errno_t errnum);
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_strerrorname_np)(errno_t errnum);
#endif /* !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strerrorname_np)(errno_t errnum);
#ifndef __KERNEL__
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_sigabbrev_np)(signo_t signo);
#endif /* !__KERNEL__ */
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_sigabbrev_np)(signo_t signo);
#ifndef __KERNEL__
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_sigdescr_np)(signo_t signo);
#endif /* !__KERNEL__ */
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_sigdescr_np)(signo_t signo);
#ifndef __KERNEL__
INTDEF ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *NOTHROW_NCX(LIBDCALL libd_strerror_r)(errno_t errnum, char *buf, size_t buflen);
INTDEF ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strerror_r)(errno_t errnum, char *buf, size_t buflen);
INTDEF ATTR_COLD ATTR_OUTS(2, 3) errno_t NOTHROW_NCX(LIBDCALL libd___xpg_strerror_r)(errno_t errnum, char *buf, size_t buflen);
INTDEF ATTR_COLD ATTR_OUTS(2, 3) errno_t NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(errno_t errnum, char *buf, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strsep)(char **__restrict stringp, char const *__restrict delim);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp, char const *__restrict delim);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) void NOTHROW_NCX(LIBDCALL libd_bcopy)(void const *src, void *dst, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) void NOTHROW_NCX(LIBCCALL libc_bcopy)(void const *src, void *dst, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUTS(1, 2) void NOTHROW_NCX(LIBDCALL libd_bzero)(void *__restrict dst, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_OUTS(1, 2) void NOTHROW_NCX(LIBCCALL libc_bzero)(void *__restrict dst, size_t num_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_bzerow)(void *__restrict dst, size_t num_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_bzerow)(void *__restrict dst, size_t num_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_bzerol)(void *__restrict dst, size_t num_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_bzerol)(void *__restrict dst, size_t num_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_bzeroq)(void *__restrict dst, size_t num_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_bzeroq)(void *__restrict dst, size_t num_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_bzeroc)(void *__restrict dst, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_bzeroc)(void *__restrict dst, size_t elem_count, size_t elem_size);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_bcmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_bcmp)(void const *s1, void const *s2, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcasecmp)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1, char const *s2);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncasecmp)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1, char const *s2, size_t maxlen);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBDCALL libd_ffs)(int i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBCCALL libc_ffs)(int i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBDCALL libd_ffsl)(long i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBCCALL libc_ffsl)(long i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBDCALL libd_ffsll)(__LONGLONG i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_strlcat)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strlcat)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_strlcpy)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INS(2, 4) ATTR_OUTS(1, 4) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_memccpy)(void *__restrict dst, void const *__restrict src, int needle, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INS(2, 4) ATTR_OUTS(1, 4) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memccpy)(void *__restrict dst, void const *__restrict src, int needle, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_mempcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_mempcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memmovew)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovew)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_mempmovew)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovew)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memmovel)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovel)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_mempmovel)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovel)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memmoveupw)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmoveupw)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memmovedownw)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovedownw)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_mempmoveupw)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupw)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_mempmovedownw)(void *dst, void const *src, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownw)(void *dst, void const *src, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memmoveupl)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmoveupl)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memmovedownl)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovedownl)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_mempmoveupl)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupl)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_mempmovedownl)(void *dst, void const *src, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownl)(void *dst, void const *src, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Fill memory with a given word */
INTDEF ATTR_LEAF ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Fill memory with a given word */
INTDEF ATTR_LEAF ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_mempsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Fill memory with a given dword */
INTDEF ATTR_LEAF ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Fill memory with a given dword */
INTDEF ATTR_LEAF ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_mempsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Compare memory buffers and return the difference of the first non-matching word */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_memcmpw)(void const *s1, void const *s2, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Compare memory buffers and return the difference of the first non-matching word */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_memcmpw)(void const *s1, void const *s2, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Compare memory buffers and return the difference of the first non-matching dword */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_memcmpl)(void const *s1, void const *s2, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Compare memory buffers and return the difference of the first non-matching dword */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_memcmpl)(void const *s1, void const *s2, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memrchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memrchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_rawmemchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(void const *__restrict haystack, uint16_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_rawmemchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(void const *__restrict haystack, uint32_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBDCALL libd_rawmemrchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(void const *__restrict haystack, uint16_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBDCALL libd_rawmemrchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(void const *__restrict haystack, uint32_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memendw)(void const *__restrict haystack, uint16_t needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memendw)(void const *__restrict haystack, uint16_t needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memrendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memrendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendw', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memendw', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendl', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memendl', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendw', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrendw', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendl', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrendl', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(void const *__restrict haystack, uint16_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(void const *__restrict haystack, uint32_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(void const *__restrict haystack, uint16_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(void const *__restrict haystack, uint32_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_mempcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memmoveq)(void *dst, void const *src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveq)(void *dst, void const *src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_mempmoveq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memmoveupq)(void *dst, void const *src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveupq)(void *dst, void const *src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memmovedownq)(void *dst, void const *src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmovedownq)(void *dst, void const *src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_mempmoveupq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_mempmovedownq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Fill memory with a given qword */
INTDEF ATTR_LEAF ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Fill memory with a given qword */
INTDEF ATTR_LEAF ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_mempsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
INTDEF ATTR_LEAF ATTR_OUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Compare memory buffers and return the difference of the first non-matching qword */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_memcmpq)(void const *s1, void const *s2, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Compare memory buffers and return the difference of the first non-matching qword */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_memcmpq)(void const *s1, void const *s2, size_t n_dwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memrchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_rawmemchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(void const *__restrict haystack, uint64_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBDCALL libd_rawmemrchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(void const *__restrict haystack, uint64_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memendq)(void const *__restrict haystack, uint64_t needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memendq)(void const *__restrict haystack, uint64_t needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memrendq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrendq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(void const *__restrict haystack, uint64_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(void const *__restrict haystack, uint64_t needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memrxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *NOTHROW_NCX(LIBDCALL libd_rawmemxchr)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *NOTHROW_NCX(LIBCCALL libc_rawmemxchr)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_rawmemrxchr)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrxchr)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memrxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_memxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_memrxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemxlen)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlen)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrxlen)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlen)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memxchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memxchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memrxchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxchrw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memrxchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxchrl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_rawmemxchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_rawmemxchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBDCALL libd_rawmemrxchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBDCALL libd_rawmemrxchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memxendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memxendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memrxendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxendw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memrxendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxendl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memxlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memxlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memxlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memxlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrxlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenw)(void const *__restrict haystack, uint16_t needle, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrxlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenl)(void const *__restrict haystack, uint32_t needle, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemxlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemxlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrxlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(void const *__restrict haystack, uint16_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrxlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(void const *__restrict haystack, uint32_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memxchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memrxchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxchrq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_rawmemxchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBDCALL libd_rawmemrxchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memxendq)(void const *__restrict haystack, uint64_t needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxendq)(void const *__restrict haystack, uint64_t needle, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memrxendq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxendq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memxlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memxlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `memrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_memrxlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `memrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenq)(void const *__restrict haystack, uint64_t needle, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemxlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrxlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(void const *__restrict haystack, uint64_t needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_memmoveup)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmoveup)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_memmovedown)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmovedown)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_memcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_memcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_mempcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_mempcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_memmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_memmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_mempmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_mempmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_memmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_memmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_mempmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_mempmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_memmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_memmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBDCALL libd_mempmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *NOTHROW_NCX(LIBCCALL libc_mempmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strend(3)
 * Same as `str + strlen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strend)(char const *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strend(3)
 * Same as `str + strlen(str)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict str);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnend)(char const *__restrict str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict str, size_t maxlen);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnrchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strrchrnul)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strrchrnul)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnrchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stroff(3)
 * Same as `strchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_stroff)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stroff(3)
 * Same as `strchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strroff(3)
 * Same as `strrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_strroff)(char const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strroff(3)
 * Same as `strrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnoff(3)
 * Same as `strnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_strnoff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnoff(3)
 * Same as `strnchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnroff(3)
 * Same as `strnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_strnroff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnroff(3)
 * Same as `strnrchrnul', but return the offset from `str', rather than the actual address */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_mempset)(void *__restrict dst, int byte, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst, int byte, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_mempmove)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_mempmoveup)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmoveup)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_mempmovedown)(void *dst, void const *src, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmovedown)(void *dst, void const *src, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_rawmemrchr)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrchr)(void const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memend)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memrend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrend)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_memlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_memrlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> rawmemlen(3)
 * Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd_rawmemlen)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> rawmemlen(3)
 * Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> rawmemrlen(3)
 * Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_rawmemrlen)(void const *__restrict haystack, int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> rawmemrlen(3)
 * Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack, int needle);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBDCALL libd_memrmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memrmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_mempatw)(void *__restrict dst, uint16_t pattern, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatw)(void *__restrict dst, uint16_t pattern, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_mempatl)(void *__restrict dst, uint32_t pattern, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatl)(void *__restrict dst, uint32_t pattern, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_mempatq)(void *__restrict dst, uint64_t pattern, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatq)(void *__restrict dst, uint64_t pattern, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcasecmp(3), memcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_memcasecmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> memcasecmp(3), memcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcasecmp)(void const *s1, void const *s2, size_t n_bytes);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBDCALL libd_memcasemem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memcasemem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcasecmp(3), memcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_memcasecmp_l)(void const *s1, void const *s2, size_t n_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memcasecmp(3), memcasecmp_l(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcasecmp_l)(void const *s1, void const *s2, size_t n_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBDCALL libd_memcasemem_l)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memcasemem_l)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strcasestr_l)(char const *haystack, char const *needle, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack, char const *needle, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBDCALL libd_vstrdupf)(char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *NOTHROW_NCX(VLIBDCALL libd_strdupf)(char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> wildstrcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_wildstrcmp)(char const *pattern, char const *string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> wildstrcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_wildstrcmp)(char const *pattern, char const *string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> wildstrcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_wildstrcasecmp)(char const *pattern, char const *string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> wildstrcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp)(char const *pattern, char const *string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_strcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strcmp)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_strcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcmp)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_strncmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strncmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_strncmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_strcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strcasecmp)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_strcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_strncasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strncasecmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_strncasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_memcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_memcmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fuzzy_memcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcasecmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fuzzy_memcasecmp(3) */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_strncasecmp_l)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp_l)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_wildstrcasecmp_l)(char const *pattern, char const *string, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp_l)(char const *pattern, char const *string, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcasecmp_l)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp_l)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpw)(void const *s1, size_t s1_words, void const *s2, size_t s2_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpw)(void const *s1, size_t s1_words, void const *s2, size_t s2_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpl)(void const *s1, size_t s1_dwords, void const *s2, size_t s2_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpl)(void const *s1, size_t s1_dwords, void const *s2, size_t s2_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpq)(void const *s1, size_t s1_qwords, void const *s2, size_t s2_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpq)(void const *s1, size_t s1_qwords, void const *s2, size_t s2_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncoll)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncoll)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcasecoll)(char const *s1, char const *s2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcasecoll)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncasecoll)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecoll)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnrev)(char *__restrict str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrev)(char *__restrict str, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnlwr)(char *__restrict str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnlwr)(char *__restrict str, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnupr)(char *__restrict str, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnupr)(char *__restrict str, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_memrev)(void *__restrict base, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrev)(void *__restrict base, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strcasecoll_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strcasecoll_l)(char const *s1, char const *s2, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strncasecoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strlwr_l)(char *__restrict str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strlwr_l)(char *__restrict str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strupr_l)(char *__restrict str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strupr_l)(char *__restrict str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnlwr_l)(char *__restrict str, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnlwr_l)(char *__restrict str, size_t maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnupr_l)(char *__restrict str, size_t maxlen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnupr_l)(char *__restrict str, size_t maxlen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) uint16_t *NOTHROW_NCX(LIBDCALL libd_memrevw)(void *__restrict base, size_t n_words);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrevw)(void *__restrict base, size_t n_words);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) uint32_t *NOTHROW_NCX(LIBDCALL libd_memrevl)(void *__restrict base, size_t n_dwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrevl)(void *__restrict base, size_t n_dwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) uint64_t *NOTHROW_NCX(LIBDCALL libd_memrevq)(void *__restrict base, size_t n_qwords);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrevq)(void *__restrict base, size_t n_qwords);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strcmpz(3)
 * Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
 * Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
 * > char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
 * > *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
 * > return strcmp(lhs, dup); */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strcmpz)(char const *lhs, char const *rhs, size_t rhs_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strcmpz(3)
 * Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
 * Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
 * > char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
 * > *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
 * > return strcmp(lhs, dup); */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcmpz)(char const *lhs, char const *rhs, size_t rhs_len);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strstartcmp(3)
 * Compare the first `strnlen(str, strlen(startswith_str))' characters
 * of `str' with  `startswith_str', returning the  usual >0, <0,  ==0. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_strstartcmp)(char const *str, char const *startswith);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strstartcmp(3)
 * Compare the first `strnlen(str, strlen(startswith_str))' characters
 * of `str' with  `startswith_str', returning the  usual >0, <0,  ==0. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_strstartcmp)(char const *str, char const *startswith);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strstartcmpz(3)
 * Compare the first `strnlen(str, startswith_len)' characters of
 * `str' with  `startswith', returning  the  usual >0,  <0,  ==0. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_strstartcmpz)(char const *str, char const *startswith, size_t startswith_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strstartcmpz(3)
 * Compare the first `strnlen(str, startswith_len)' characters of
 * `str' with  `startswith', returning  the  usual >0,  <0,  ==0. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strstartcmpz)(char const *str, char const *startswith, size_t startswith_len);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> bitcpy(3)
 * Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
 * doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
 * bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
 * significant bit is at `NBBY-1':
 * >> byte_t src[] = { 0b00001001 };
 * >> byte_t dst[] = { 0b00000000 };
 * >> bitcpy(dst, 4, src, 0, 4);
 * >> assert(dst == 0b10010000); */
INTDEF ATTR_IN(3) ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_bitcpy)(void *__restrict dst_base, size_t dst_bit_offset, void const *__restrict src_base, size_t src_bit_offset, size_t num_bits);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> bitcpy(3)
 * Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
 * doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
 * bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
 * significant bit is at `NBBY-1':
 * >> byte_t src[] = { 0b00001001 };
 * >> byte_t dst[] = { 0b00000000 };
 * >> bitcpy(dst, 4, src, 0, 4);
 * >> assert(dst == 0b10010000); */
INTDEF ATTR_IN(3) ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_bitcpy)(void *__restrict dst_base, size_t dst_bit_offset, void const *__restrict src_base, size_t src_bit_offset, size_t num_bits);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_strrstr)(char const *haystack, char const *needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBCCALL libc_strrstr)(char const *haystack, char const *needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strlstrip)(char const *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strlstrip)(char const *str);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strrstrip(3)
 * Find the last trailing `isspace(3)'-character (i.e. the one closest
 * to the start and not followed by a non-`isspace(3)'-character), and
 * replace it with '\0', effectively deleting trailing space.
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Always re-returns `str' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strrstrip)(char *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strrstrip(3)
 * Find the last trailing `isspace(3)'-character (i.e. the one closest
 * to the start and not followed by a non-`isspace(3)'-character), and
 * replace it with '\0', effectively deleting trailing space.
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Always re-returns `str' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strrstrip)(char *str);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strstrip(3)
 * The combination of `strlstrip(3)' and `strrstrip(3)'
 * @return: * : Same as `strrstrip(strlstrip(str))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_strstrip)(char *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> strstrip(3)
 * The combination of `strlstrip(3)' and `strrstrip(3)'
 * @return: * : Same as `strrstrip(strlstrip(str))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_strstrip)(char *str);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strlwr)(char *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strlwr)(char *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strupr)(char *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strupr)(char *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strset)(char *__restrict str, int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strset)(char *__restrict str, int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnset)(char *__restrict str, int ch, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnset)(char *__restrict str, int ch, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_strrev)(char *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_strrev)(char *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__strset_s)(char *dst, size_t dstsize, int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst, size_t dstsize, int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_memcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_memmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_strcpy_s)(char *dst, size_t dstsize, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst, size_t dstsize, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_strcat_s)(char *dst, size_t dstsize, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst, size_t dstsize, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_strncat_s)(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_strncpy_s)(char *dst, size_t dstsize, char const *src, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst, size_t dstsize, char const *src, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN_OPT(1) char *NOTHROW_RPC(LIBDCALL libd__strerror)(char const *message);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN_OPT(1) char *NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_RPC(LIBDCALL libd__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__strlwr_s)(char *buf, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__strupr_s)(char *buf, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__strlwr_s_l)(char *buf, size_t buflen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf, size_t buflen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__strupr_s_l)(char *buf, size_t buflen, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf, size_t buflen, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBDCALL libd__strnset_s)(char *__restrict buf, size_t buflen, int ch, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf, size_t buflen, int ch, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTDEF ATTR_PURE WUNUSED ATTR_IN(2) ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_strnstr)(char const *haystack, char const *needle, size_t haystack_maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTDEF ATTR_PURE WUNUSED ATTR_IN(2) ATTR_INS(1, 3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnstr)(char const *haystack, char const *needle, size_t haystack_maxlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
INTDEF ATTR_OUT(2) void NOTHROW_NCX(LIBDCALL libd_strmode)(mode_t mode, char p[12]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
INTDEF ATTR_OUT(2) void NOTHROW_NCX(LIBCCALL libc_strmode)(mode_t mode, char p[12]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
INTDEF WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int NOTHROW_NCX(LIBDCALL libd_timingsafe_memcmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
INTDEF WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int NOTHROW_NCX(LIBCCALL libc_timingsafe_memcmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) signo_t NOTHROW_NCX(LIBDCALL libd_strtosigno)(const char *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) signo_t NOTHROW_NCX(LIBCCALL libc_strtosigno)(const char *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stresep(3)
 * Same as `strsep(3)', but allow the specification of an additional `escape'
 * character  that will cause  the following character  from `*stringp' to be
 * escaped, and not  be considered  as a separator,  even if  it is  included
 * within `delim'. Note that `escape'-characters (if present) are not removed
 * from  the input  string, meaning that  they will still  appear in returned
 * strings, should they have been present in the original input string. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_stresep)(char **__restrict stringp, char const *__restrict delim, int escape);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stresep(3)
 * Same as `strsep(3)', but allow the specification of an additional `escape'
 * character  that will cause  the following character  from `*stringp' to be
 * escaped, and not  be considered  as a separator,  even if  it is  included
 * within `delim'. Note that `escape'-characters (if present) are not removed
 * from  the input  string, meaning that  they will still  appear in returned
 * strings, should they have been present in the original input string. */
INTDEF ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_stresep)(char **__restrict stringp, char const *__restrict delim, int escape);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
INTDEF WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int NOTHROW_NCX(LIBDCALL libd_consttime_memequal)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
INTDEF WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int NOTHROW_NCX(LIBCCALL libc_consttime_memequal)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> uucopy(2)
 * Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
 * faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: 0 : Success
 * @return: -1: [errno=EFAULT] Faulty memory access */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBDCALL libd_uucopy)(void const *__restrict src, void *__restrict dst, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> uucopy(2)
 * Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
 * faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: 0 : Success
 * @return: -1: [errno=EFAULT] Faulty memory access */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBCCALL libc_uucopy)(void const *__restrict src, void *__restrict dst, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> uucopystr(2)
 * Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
 * The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: * : The number of copied characters (including trialing NUL; )
 * @return: -1: [errno=EFAULT]       Faulty memory access
 * @return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen' */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_uucopystr)(void const *__restrict src, void *__restrict dst, size_t maxlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> uucopystr(2)
 * Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
 * The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: * : The number of copied characters (including trialing NUL; )
 * @return: -1: [errno=EFAULT]       Faulty memory access
 * @return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen' */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_uucopystr)(void const *__restrict src, void *__restrict dst, size_t maxlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRING_H */
