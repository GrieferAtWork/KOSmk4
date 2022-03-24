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
%(c_prefix){
/* (#) Portability: Cygwin (/newlib/libc/include/ssp/string.h) */
/* (#) Portability: NetBSD (/include/ssp/string.h) */
/* (#) Portability: Newlib (/newlib/libc/include/ssp/string.h) */
}

%[default:section(".text.crt{|.dos}.ssp.string.memory")]

%{
#include <features.h>

#include <hybrid/typecore.h>

#include <ssp/ssp.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/ssp.string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__

}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memcpy_chk([[nonnull]] void *__restrict dst,
             [[nonnull]] void const *__restrict src,
             $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmove_chk([[nonnull]] void *dst,
              [[nonnull]] void const *src,
              $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memset_chk([[nonnull]] void *__restrict dst, int byte,
             $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__strcat_chk([[nonnull]] char *__restrict dst,
             [[nonnull]] char const *__restrict src,
             $size_t dst_objsize)
		-> [[== dst]] char *
	%{chk("strcat", "(void)dst_objsize; /* TODO */")}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__strcpy_chk([[nonnull]] char *__restrict dst,
             [[nonnull]] char const *__restrict src,
             $size_t dst_objsize)
		-> [[== dst]] char *
	%{chk("strcpy", "(void)dst_objsize; /* TODO */")}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__strncat_chk([[nonnull]] char *__restrict dst,
              [[nonnull]] char const *__restrict src,
              $size_t buflen, $size_t dst_objsize)
		-> [[== dst]] char *
	%{chk("strncat", "(void)dst_objsize; /* TODO */")}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__strncpy_chk([[nonnull]] char *__restrict dst,
              [[nonnull]] char const *__restrict src,
              $size_t buflen, $size_t dst_objsize)
		-> [[== dst]] char *
	%{chk("strncpy", "(void)dst_objsize; /* TODO */")}

%
%#ifdef __USE_GNU
[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempcpy_chk([[nonnull]] void *__restrict dst,
              [[nonnull]] void const *__restrict src,
              $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst + n_bytes]] void *
	%{chk}
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K8
[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__stpcpy_chk:([[nonnull]] char *__restrict dst,
              [[nonnull]] char const *__restrict src,
              $size_t dst_objsize)
		-> [== dst + strlen(src)] char *
	%{chk("stpcpy", "(void)dst_objsize; /* TODO */")}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__stpncpy_chk:([[nonnull]] char *__restrict dst,
               [[nonnull]] char const *__restrict src,
               $size_t buflen, $size_t dst_objsize)
		-> [== dst + strlen(src)] char *
	%{chk("stpncpy", "(void)dst_objsize; /* TODO */")}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_KOS
[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmove_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
               $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst + n_bytes]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempset_chk([[nonnull]] void *__restrict dst, int byte,
              $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst + n_bytes]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmoveup_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmovedown_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                  $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmoveup_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                 $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst + n_bytes]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmovedown_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                   $size_t n_bytes, $size_t dst_objsize)
		-> [[== dst + n_bytes]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memcpyc_chk([[nonnull]] void *__restrict dst,
              [[nonnull]] void const *__restrict src,
              $size_t elem_count, $size_t elem_size,
              $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmovec_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
               $size_t elem_count, $size_t elem_size, $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempcpyc_chk([[nonnull]] void *__restrict dst,
               [[nonnull]] void const *__restrict src,
               $size_t elem_count, $size_t elem_size,
               $size_t dst_objsize)
		-> [[== dst + (elem_count * elem_size)]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmovec_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                $size_t elem_count, $size_t elem_size,
                $size_t dst_objsize)
		-> [[== dst + (elem_count * elem_size)]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmoveupc_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                 $size_t elem_count, $size_t elem_size,
                 $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__memmovedownc_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                   $size_t elem_count, $size_t elem_size,
                   $size_t dst_objsize)
		-> [[== dst]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmoveupc_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                  $size_t elem_count, $size_t elem_size,
                  $size_t dst_objsize)
		-> [[== dst + (elem_count * elem_size)]] void *
	%{chk}

[[libc, fast, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmovedownc_chk([[nonnull]] void *dst, [[nonnull]] void const *src,
                    $size_t elem_count, $size_t elem_size,
                    $size_t dst_objsize)
		-> [[== dst + (elem_count * elem_size)]] void *
	%{chk}

%#endif /* __USE_KOS */


%#ifdef __USE_STRING_BWLQ

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("__wmemcpy_chk")]]
__memcpyw_chk([[nonnull]] /*aligned(2)*/ void *__restrict dst,
              [[nonnull]] /*aligned(2)*/ void const *__restrict src,
              $size_t n_words, $size_t dst_objsize)
		-> [[== dst]] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("__wmempcpy_chk")]]
__mempcpyw_chk([[nonnull]] /*aligned(2)*/ void *__restrict dst,
               [[nonnull]] /*aligned(2)*/ void const *__restrict src,
               $size_t n_words, $size_t dst_objsize)
		-> [== dst + n_words * 2] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("__wmemmove_chk")]]
__memmovew_chk([[nonnull]] /*aligned(2)*/ void *dst,
               [[nonnull]] /*aligned(2)*/ void const *src,
               $size_t n_words, $size_t dst_objsize)
		-> [[== dst]] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("__wmemcpy_chk")]]
__memcpyl_chk([[nonnull]] /*aligned(4)*/ void *__restrict dst,
              [[nonnull]] /*aligned(4)*/ void const *__restrict src,
              $size_t n_dwords, $size_t dst_objsize)
		-> [[== dst]] $uint32_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("__wmempcpy_chk")]]
__mempcpyl_chk([[nonnull]] /*aligned(4)*/ void *__restrict dst,
               [[nonnull]] /*aligned(4)*/ void const *__restrict src,
               $size_t n_dwords, $size_t dst_objsize)
		-> [== dst + n_dwords * 4] $uint32_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("__wmemmove_chk")]]
__memmovel_chk([[nonnull]] /*aligned(4)*/ void *dst,
               [[nonnull]] /*aligned(4)*/ void const *src,
               $size_t n_dwords, $size_t dst_objsize)
		-> [[== dst]] $uint32_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmovew_chk([[nonnull]] /*aligned(2)*/ void *dst,
                [[nonnull]] /*aligned(2)*/ void const *src,
                $size_t n_words, $size_t dst_objsize)
		-> [== dst + n_words * 2] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmovel_chk([[nonnull]] /*aligned(4)*/ void *dst,
                [[nonnull]] /*aligned(4)*/ void const *src,
                $size_t n_dwords, $size_t dst_objsize)
		-> [== dst + n_dwords * 4] $uint32_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__memsetw_chk([[nonnull]] /*aligned(2)*/ void *__restrict dst,
              $uint16_t word, $size_t n_words, $size_t dst_objsize)
		-> [[== dst]] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempsetw_chk([[nonnull]] /*aligned(2)*/ void *__restrict dst,
               $uint16_t word, $size_t n_words, $size_t dst_objsize)
		-> [== dst + n_words * 2] $uint16_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__memsetl_chk([[nonnull]] /*aligned(4)*/ void *__restrict dst,
              $uint32_t dword, $size_t n_dwords, $size_t dst_objsize)
		-> [[== dst]] $uint32_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempsetl_chk([[nonnull]] /*aligned(4)*/ void *__restrict dst,
               $uint32_t dword, $size_t n_dwords, $size_t dst_objsize)
		-> [== dst + n_dwords * 4] $uint32_t * %{chk}


%#ifdef __USE_KOS
[[fast, libc, leaf, alias("__memmovew_chk"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("__wmemmove_chk")]]
__memmoveupw_chk([[nonnull]] /*aligned(2)*/ void *dst,
                 [[nonnull]] /*aligned(2)*/ void const *src,
                 $size_t n_words, $size_t dst_objsize)
		-> [[== dst]] $uint16_t * %{chk}

[[fast, libc, leaf, alias("__memmovew_chk"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("__wmemmove_chk")]]
__memmovedownw_chk([[nonnull]] /*aligned(2)*/ void *dst,
                   [[nonnull]] /*aligned(2)*/ void const *src,
                   $size_t n_words, $size_t dst_objsize)
		-> [[== dst]] $uint16_t * %{chk}

[[fast, libc, leaf, alias("__memmovel_chk"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("__wmemmove_chk")]]
__memmoveupl_chk([[nonnull]] /*aligned(4)*/ void *dst,
                 [[nonnull]] /*aligned(4)*/ void const *src,
                 $size_t n_dwords, $size_t dst_objsize)
		-> [[== dst]] $uint32_t * %{chk}

[[fast, libc, leaf, alias("__memmovel_chk"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("__wmemmove_chk")]]
__memmovedownl_chk([[nonnull]] /*aligned(4)*/ void *dst,
                   [[nonnull]] /*aligned(4)*/ void const *src,
                   $size_t n_dwords, $size_t dst_objsize)
		-> [[== dst]] $uint32_t * %{chk}

[[fast, libc, leaf, alias("__mempmovew_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmoveupw_chk([[nonnull]] /*aligned(2)*/ void *dst,
                  [[nonnull]] /*aligned(2)*/ void const *src,
                  $size_t n_words, $size_t dst_objsize)
		-> [== dst + n_words * 2] $uint16_t * %{chk}

[[fast, libc, leaf, alias("__mempmovew_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmovedownw_chk([[nonnull]] /*aligned(2)*/ void *dst,
                    [[nonnull]] /*aligned(2)*/ void const *src,
                    $size_t n_words, $size_t dst_objsize)
		-> [== dst + n_words * 2] $uint16_t * %{chk}

[[fast, libc, leaf, alias("__mempmovel_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmoveupl_chk([[nonnull]] /*aligned(4)*/ void *dst,
                  [[nonnull]] /*aligned(4)*/ void const *src,
                  $size_t n_dwords, $size_t dst_objsize)
		-> [== dst + n_dwords * 4] $uint32_t * %{chk}

[[fast, libc, leaf, alias("__mempmovel_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmovedownl_chk([[nonnull]] /*aligned(4)*/ void *dst,
                    [[nonnull]] /*aligned(4)*/ void const *src,
                    $size_t n_dwords, $size_t dst_objsize)
		-> [== dst + n_dwords * 4] $uint32_t * %{chk}

%#endif /* __USE_KOS */
%#ifdef __UINT64_TYPE__
[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__memcpyq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
              [[nonnull]] /*aligned(8)*/ void const *__restrict src,
              $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst]] $uint64_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempcpyq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
               [[nonnull]] /*aligned(8)*/ void const *__restrict src,
               $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst + n_qwords * 8]] $uint64_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__memmoveq_chk([[nonnull]] /*aligned(8)*/ void *dst,
               [[nonnull]] /*aligned(8)*/ void const *src,
               $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst]] $uint64_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempmoveq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
                [[nonnull]] /*aligned(8)*/ void const *__restrict src,
                $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst + n_qwords * 8]] $uint64_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__memsetq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
              $uint64_t qword, $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst]] $uint64_t * %{chk}

[[fast, libc, leaf, decl_include("<hybrid/typecore.h>")]]
__mempsetq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
               $uint64_t qword, $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst + n_qwords * 8]] $uint64_t * %{chk}

%#ifdef __USE_KOS
[[fast, libc, leaf, alias("__memmoveq_chk"), decl_include("<hybrid/typecore.h>")]]
__memmoveupq_chk([[nonnull]] /*aligned(8)*/ void *dst,
                 [[nonnull]] /*aligned(8)*/ void const *src,
                 $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst]] $uint64_t * %{chk}

[[fast, libc, leaf, alias("__memmoveq_chk"), decl_include("<hybrid/typecore.h>")]]
__memmovedownq_chk([[nonnull]] /*aligned(8)*/ void *dst,
                   [[nonnull]] /*aligned(8)*/ void const *src,
                   $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst]] $uint64_t * %{chk}

[[fast, libc, leaf, alias("__mempmoveq_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmoveupq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
                  [[nonnull]] /*aligned(8)*/ void const *__restrict src,
                  $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst + n_qwords * 8]] $uint64_t * %{chk}

[[fast, libc, leaf, alias("__mempmoveq_chk"), decl_include("<hybrid/typecore.h>")]]
__mempmovedownq_chk([[nonnull]] /*aligned(8)*/ void *__restrict dst,
                    [[nonnull]] /*aligned(8)*/ void const *__restrict src,
                    $size_t n_qwords, $size_t dst_objsize)
		-> [[== dst + n_qwords * 8]] $uint64_t * %{chk}

%#endif /* __USE_KOS */
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */



%
%
%
%/* Bind SSP function variants if necessary */
%#ifdef __SSP_FORTIFY_LEVEL
%[define_ssp_builtin_undef("__PRIVATE_memset_3(dst, byte, n_bytes)" = "__memset_chk(dst, byte, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_builtin_undef("__PRIVATE_memcpy_3(dst, src, n_bytes)" = "__memcpy_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_builtin_undef("__PRIVATE_memmove_3(dst, src, n_bytes)" = "__memmove_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%
%#ifdef __USE_STRING_OVERLOADS
%[define_ssp_undef("__PRIVATE_memcpy_4(dst, src, elem_count, elem_size)" = "__memcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_memmove_4(dst, src, elem_count, elem_size)" = "__memmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%#endif /* __USE_STRING_OVERLOADS */
%
%#ifdef __USE_GNU
%[define_ssp_builtin_undef("__PRIVATE_mempcpy_3(dst, src, n_bytes)" = "__mempcpy_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%#ifdef __USE_STRING_OVERLOADS
%[define_ssp_undef("__PRIVATE_mempcpy_4(dst, src, elem_count, elem_size)" = "__mempcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%#endif /* __USE_STRING_OVERLOADS */
%#endif /* __USE_GNU */
%
%#ifdef __USE_KOS
%[define_ssp_undef("memcpyc(dst, src, elem_count, elem_size)"       = "__memcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovec(dst, src, elem_count, elem_size)"      = "__memmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("mempcpyc(dst, src, elem_count, elem_size)"      = "__mempcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovec(dst, src, elem_count, elem_size)"     = "__mempmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("memmoveupc(dst, src, elem_count, elem_size)"    = "__memmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmoveupc(dst, src, elem_count, elem_size)"   = "__mempmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovedownc(dst, src, elem_count, elem_size)"  = "__memmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovedownc(dst, src, elem_count, elem_size)" = "__mempmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempset_3(dst, byte, n_bytes)"        = "__mempset_chk(dst, byte, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempmove_3(dst, src, n_bytes)"        = "__mempmove_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_memmoveup_3(dst, src, n_bytes)"       = "__memmoveup_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempmoveup_3(dst, src, n_bytes)"      = "__mempmoveup_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_memmovedown_3(dst, src, n_bytes)"     = "__memmovedown_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempmovedown_3(dst, src, n_bytes)"    = "__mempmovedown_chk(dst, src, n_bytes, __ssp_bos0(dst))")]
%#ifdef __USE_STRING_OVERLOADS
%[define_ssp_undef("__PRIVATE_mempmove_4(dst, src, elem_count, elem_size)"     = "__mempmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_memmoveup_4(dst, src, elem_count, elem_size)"    = "__memmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempmoveup_4(dst, src, elem_count, elem_size)"   = "__mempmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_memmovedown_4(dst, src, elem_count, elem_size)"  = "__memmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%[define_ssp_undef("__PRIVATE_mempmovedown_4(dst, src, elem_count, elem_size)" = "__mempmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))")]
%#endif /* __USE_STRING_OVERLOADS */
%#endif /* __USE_KOS */


%#ifdef __USE_STRING_BWLQ
%[define_ssp_undef("memcpyw(dst, src, n_words)"     = "__memcpyw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("mempcpyw(dst, src, n_words)"    = "__mempcpyw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovew(dst, src, n_words)"    = "__memmovew_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("memcpyl(dst, src, n_dwords)"    = "__memcpyl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempcpyl(dst, src, n_dwords)"   = "__mempcpyl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovel(dst, src, n_dwords)"   = "__memmovel_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovew(dst, src, n_words)"   = "__mempmovew_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovel(dst, src, n_dwords)"  = "__mempmovel_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memsetw(dst, word, n_words)"    = "__memsetw_chk(dst, word, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("mempsetw(dst, word, n_words)"   = "__mempsetw_chk(dst, word, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("memsetl(dst, dword, n_dwords)"  = "__memsetl_chk(dst, dword, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempsetl(dst, dword, n_dwords)" = "__mempsetl_chk(dst, dword, n_dwords, __ssp_bos0(dst))")]
%#ifdef __USE_KOS
%[define_ssp_undef("memmoveupw(dst, src, n_words)"     = "__memmoveupw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovedownw(dst, src, n_words)"   = "__memmovedownw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("memmoveupl(dst, src, n_dwords)"    = "__memmoveupl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovedownl(dst, src, n_dwords)"  = "__memmovedownl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmoveupw(dst, src, n_words)"    = "__mempmoveupw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovedownw(dst, src, n_words)"  = "__mempmovedownw_chk(dst, src, n_words, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmoveupl(dst, src, n_dwords)"   = "__mempmoveupl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovedownl(dst, src, n_dwords)" = "__mempmovedownl_chk(dst, src, n_dwords, __ssp_bos0(dst))")]
%#endif /* __USE_KOS */
%#ifdef __UINT64_TYPE__
%[define_ssp_undef("memcpyq(dst, src, n_qwords)"    = "__memcpyq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempcpyq(dst, src, n_qwords)"   = "__mempcpyq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memmoveq(dst, src, n_qwords)"   = "__memmoveq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmoveq(dst, src, n_qwords)"  = "__mempmoveq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memsetq(dst, qword, n_qwords)"  = "__memsetq_chk(dst, qword, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempsetq(dst, qword, n_qwords)" = "__mempsetq_chk(dst, qword, n_qwords, __ssp_bos0(dst))")]
%#ifdef __USE_KOS
%[define_ssp_undef("memmoveupq(dst, src, n_qwords)"    = "__memmoveupq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("memmovedownq(dst, src, n_qwords)"  = "__memmovedownq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmoveupq(dst, src, n_qwords)"   = "__mempmoveupq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%[define_ssp_undef("mempmovedownq(dst, src, n_qwords)" = "__mempmovedownq_chk(dst, src, n_qwords, __ssp_bos0(dst))")]
%#endif /* __USE_KOS */
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */




%
%{
#if defined(__cplusplus) || !defined(__USE_STRING_OVERLOADS)
#ifdef __cplusplus
__NAMESPACE_STD_BEGIN
typedef void *__forward_voidp;
__NAMESPACE_STD_END
__NAMESPACE_STD_USING(__forward_voidp)
#endif /* __cplusplus */
#undef memset
#undef memcpy
#undef memmove
#ifdef __USE_STRING_OVERLOADS
#ifdef __cplusplus
#define memset(...)  __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__))
#define memcpy(...)  __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__))
#define memmove(...) __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__))
#else /* __cplusplus */
#define memset(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__)
#define memcpy(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__)
#define memmove(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */
#ifdef __USE_GNU
#undef mempcpy
#define mempcpy(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_GNU */
#ifdef __USE_KOS
#undef mempset
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#define mempset(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmove(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmoveup(...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmovedown(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#define memmoveup(...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define memmovedown(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_KOS */
#else /* __USE_STRING_OVERLOADS */
#define memset(dst, src, n_bytes)  __forward_voidp(__PRIVATE_memset_3(dst, src, n_bytes))
#define memcpy(dst, src, n_bytes)  __forward_voidp(__PRIVATE_memcpy_3(dst, src, n_bytes))
#define memmove(dst, src, n_bytes) __forward_voidp(__PRIVATE_memmove_3(dst, src, n_bytes))
#ifdef __USE_GNU
#undef mempcpy
#define mempcpy(dst, src, n_bytes) __PRIVATE_mempcpy_3(dst, src, n_bytes)
#endif /* __USE_GNU */
#ifdef __USE_KOS
#undef mempset
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#define mempset(dst, src, n_bytes)      __PRIVATE_mempset_3(dst, src, n_bytes)
#define mempmove(dst, src, n_bytes)     __PRIVATE_mempmove_3(dst, src, n_bytes)
#define mempmoveup(dst, src, n_bytes)   __PRIVATE_mempmoveup_3(dst, src, n_bytes)
#define mempmovedown(dst, src, n_bytes) __PRIVATE_mempmovedown_3(dst, src, n_bytes)
#define memmoveup(dst, src, n_bytes)    __PRIVATE_memmoveup_3(dst, src, n_bytes)
#define memmovedown(dst, src, n_bytes)  __PRIVATE_memmovedown_3(dst, src, n_bytes)
#endif /* __USE_KOS */
#endif /* !__USE_STRING_OVERLOADS */
#endif /* __cplusplus || !__USE_STRING_OVERLOADS */
}
%
%
%[define_ssp_builtin_undef(strcpy(buf, src) = __strcpy_chk(buf, src, __ssp_bos0(buf)))]
%[define_ssp_builtin_undef(strcat(buf, src) = __strcat_chk(buf, src, __ssp_bos0(buf)))]
%[define_ssp_builtin_undef(strncpy(buf, src, buflen) = __strncpy_chk(buf, src, buflen, __ssp_bos0(buf)))]
%[define_ssp_builtin_undef(strncat(buf, src, buflen) = __strncat_chk(buf, src, buflen, __ssp_bos0(buf)))]
%#ifdef __USE_XOPEN2K8
%[define_ssp_builtin_undef(stpcpy(buf, src) = __stpcpy_chk(buf, src, __ssp_bos0(buf)))]
%[define_ssp_builtin_undef(stpncpy(buf, src, buflen) = __stpncpy_chk(buf, src, buflen, __ssp_bos0(buf)))]
%#endif /* __USE_XOPEN2K8 */


%
%#endif /* __SSP_FORTIFY_LEVEL */

%{


#endif /* __CC__ */

__SYSDECL_END

}
