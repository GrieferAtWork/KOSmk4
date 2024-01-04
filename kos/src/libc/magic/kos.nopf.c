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
%[default:section(".text.crt.string.nopf")]

%[insert:prefix(
#include <kos/bits/nopf.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

/* Define nopf functions */

}

[[ignore, nocrt, alias("readb_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_readb_nopf)]]
bool crt_readb_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint8_t *presult);

[[ignore, nocrt, alias("readw_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readw_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_readw_nopf)]]
bool crt_readw_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint16_t *presult);

[[ignore, nocrt, alias("readl_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readl_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_readl_nopf)]]
bool crt_readl_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint32_t *presult);

[[ignore, nocrt, alias("readq_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readq_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_readq_nopf)]]
bool crt_readq_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint64_t *presult);

[[ignore, nocrt, alias("writeb_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_writeb_nopf)]]
bool crt_writeb_nopf([[user, checked, out_opt]] void *addr, $uint8_t val);

[[ignore, nocrt, alias("writew_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writew_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_writew_nopf)]]
bool crt_writew_nopf([[user, checked, out_opt]] void *addr, $uint16_t val);

[[ignore, nocrt, alias("writel_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writel_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_writel_nopf)]]
bool crt_writel_nopf([[user, checked, out_opt]] void *addr, $uint32_t val);

[[ignore, nocrt, alias("writeq_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeq_nopf")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_writeq_nopf)]]
bool crt_writeq_nopf([[user, checked, out_opt]] void *addr, $uint64_t val);

[[ignore, nocrt, alias("memcpy_nopf")]]
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro("<kos/bits/nopf.h>", __arch_memcpy_nopf)]]
$size_t crt_memcpy_nopf([[user, checked, out_opt(num_bytes)]] void *dst,
                        [[user, checked, in_opt(num_bytes)]] void const *src,
                        $size_t num_bytes);

%(auto_source){
#define crt_readb_nopf  libc_readb_nopf
#define crt_readw_nopf  libc_readw_nopf
#define crt_readl_nopf  libc_readl_nopf
#define crt_readq_nopf  libc_readq_nopf
#define crt_memcpy_nopf libc_memcpy_nopf
}


@@>> read[bwlq]_nopf(3)
@@Try to read from a possibly faulty `addr' into `*presult'
@@Return `true' on success, `false' on fault
[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_readb_nopf)]]
[[requires($has_function(crt_memcpy_nopf) ||
           $has_function(crt_readw_nopf) ||
           $has_function(crt_readl_nopf) ||
           $has_function(crt_readq_nopf))]]
[[impl_include("<hybrid/typecore.h>")]]
bool readb_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint8_t *presult) {
@@pp_if $has_function(crt_memcpy_nopf)@@
	return likely(crt_memcpy_nopf(presult, addr, 1) == 0);
@@pp_elif $has_function(crt_readw_nopf)@@
	bool ok;
	union { uint16_t w; uint8_t b[2]; } result;
	ok = crt_readw_nopf((void const *)((uintptr_t)addr & ~1), &result.w);
	*presult = result.b[(uintptr_t)addr & 1];
	return ok;
@@pp_elif $has_function(crt_readl_nopf)@@
	bool ok;
	union { uint32_t l; uint8_t b[4]; } result;
	ok = crt_readl_nopf((void const *)((uintptr_t)addr & ~3), &result.l);
	*presult = result.b[(uintptr_t)addr & 3];
	return ok;
@@pp_else@@
	bool ok;
	union { uint64_t q; uint8_t b[2]; } result;
	ok = crt_readw_nopf((void const *)((uintptr_t)addr & ~7), &result.q);
	*presult = result.b[(uintptr_t)addr & 7];
	return ok;
@@pp_endif@@
}

[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_readw_nopf)]]
[[requires($has_function(readb_nopf) ||
           $has_function(crt_memcpy_nopf))]]
[[impl_include("<hybrid/typecore.h>")]]
bool readw_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint16_t *presult) {
@@pp_if $has_function(crt_readb_nopf) || !$has_function(crt_memcpy_nopf)@@
	bool ok;
	union { uint16_t w; uint8_t b[2]; } result;
	ok = likely(readb_nopf((void const *)((uintptr_t)addr + 0), &result.b[0])) &&
	     likely(readb_nopf((void const *)((uintptr_t)addr + 1), &result.b[1]));
	*presult = result.w;
	return ok;
@@pp_else@@
	return likely(crt_memcpy_nopf(presult, addr, 2) == 0);
@@pp_endif@@
}


[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_readl_nopf)]]
[[requires($has_function(readw_nopf) ||
           $has_function(crt_memcpy_nopf))]]
[[impl_include("<hybrid/typecore.h>")]]
bool readl_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint32_t *presult) {
@@pp_if $has_function(crt_readw_nopf) || !$has_function(crt_memcpy_nopf)@@
	bool ok;
	union { uint32_t l; uint16_t w[2]; } result;
	ok = likely(readw_nopf((void const *)((uintptr_t)addr + 0), &result.w[0])) &&
	     likely(readw_nopf((void const *)((uintptr_t)addr + 2), &result.w[1]));
	*presult = result.l;
	return ok;
@@pp_else@@
	return likely(crt_memcpy_nopf(presult, addr, 4) == 0);
@@pp_endif@@
}

[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_readq_nopf)]]
[[requires($has_function(readl_nopf) ||
           $has_function(crt_memcpy_nopf))]]
[[impl_include("<hybrid/typecore.h>")]]
bool readq_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint64_t *presult) {
@@pp_if $has_function(crt_readl_nopf) || !$has_function(crt_memcpy_nopf)@@
	bool ok;
	union { uint64_t q; uint32_t l[2]; } result;
	ok = likely(readl_nopf((void const *)((uintptr_t)addr + 0), &result.l[0])) &&
	     likely(readl_nopf((void const *)((uintptr_t)addr + 4), &result.l[1]));
	*presult = result.q;
	return ok;
@@pp_else@@
	return likely(crt_memcpy_nopf(presult, addr, 8) == 0);
@@pp_endif@@
}


@@>> write[bwlq]_nopf(3)
@@Try to write `val' into a possibly faulty `addr'
@@Return  `true'  on  success,  `false'  on  error
[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_writeb_nopf)]]
[[requires_function(crt_memcpy_nopf)]]
bool writeb_nopf([[user, checked, out_opt]] void *addr, $uint8_t val) {
	return likely(crt_memcpy_nopf(addr, &val, 1) == 0);
}

[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_writew_nopf)]]
[[requires_function(readb_nopf, writeb_nopf)]]
bool writew_nopf([[user, checked, out_opt]] void *addr, $uint16_t val) {
	union { uint16_t w; uint8_t b[2]; } uval;
	uint8_t old_addr0;
	uval.w = val;
	if unlikely(!readb_nopf(addr, &old_addr0))
		return false;
	if unlikely(!writeb_nopf(addr, uval.b[0]))
		return false;
	if unlikely(!writeb_nopf((uint8_t *)addr + 1, uval.b[1])) {
		COMPILER_UNUSED(writeb_nopf(addr, old_addr0));
		return false;
	}
	return true;
}

[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_writel_nopf)]]
[[requires_function(readw_nopf, writew_nopf)]]
bool writel_nopf([[user, checked, out_opt]] void *addr, $uint32_t val) {
	union { uint32_t l; uint16_t w[2]; } uval;
	uint16_t old_addr0;
	uval.l = val;
	if unlikely(!readw_nopf(addr, &old_addr0))
		return false;
	if unlikely(!writew_nopf(addr, uval.w[0]))
		return false;
	if unlikely(!writew_nopf((uint16_t *)addr + 1, uval.w[1])) {
		COMPILER_UNUSED(writew_nopf(addr, old_addr0));
		return false;
	}
	return true;
}

[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_writeq_nopf)]]
[[requires_function(readl_nopf, writel_nopf)]]
bool writeq_nopf([[user, checked, out_opt]] void *addr, $uint64_t val) {
	union { uint64_t q; uint32_t l[2]; } uval;
	uint32_t old_addr0;
	uval.q = val;
	if unlikely(!readl_nopf(addr, &old_addr0))
		return false;
	if unlikely(!writel_nopf(addr, uval.l[0]))
		return false;
	if unlikely(!writel_nopf((uint32_t *)addr + 1, uval.l[1])) {
		COMPILER_UNUSED(writel_nopf(addr, old_addr0));
		return false;
	}
	return true;
}



@@>> memcpy_nopf(3)
@@Copy memory from `src' to `dst', but  stop if any sort of #PF  happens,
@@regardless of that #PF being handleable or not (aka: load-on-access, or
@@copy-on-write  will never be  triggered by this  function, and the same
@@also goes for VIO)
@@This function can be used to copy user-space memory whilst holding  an
@@atomic lock, allowing the caller to handle the PF by handling the next
@@data byte/word/etc. individually after releasing the atomic lock, thus
@@allowing a necessary #PF to run its course without the caller  holding
@@an atomic lock.
@@@return: 0 : The copy operation completed without any problems.
@@@return: * : The number of bytes that could not be transferred.
@@             The affected memory ranges are:
@@              - `dst + num_bytes - return ... dst + num_bytes - 1'
@@              - `src + num_bytes - return ... src + num_bytes - 1'
[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_memcpy_nopf)]]
[[requires_function(readb_nopf, writeb_nopf)]]
$size_t memcpy_nopf([[user, checked, out_opt(num_bytes)]] void *dst,
                    [[user, checked, in_opt(num_bytes)]] void const *src,
                    $size_t num_bytes) {
	while (num_bytes) {
		byte_t b;
		if unlikely(!readb_nopf(src, &b))
			break;
		if unlikely(!writeb_nopf(dst, b))
			break;
		--num_bytes;
		dst = (byte_t *)dst + 1;
		src = (byte_t const *)src + 1;
	}
	return num_bytes;
}

@@>> memset_nopf(3)
@@@return: * : The # of bytes that could not be accessed
[[kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_memset_nopf)]]
[[requires_function(writeb_nopf)]]
$size_t memset_nopf([[user, checked, out_opt(num_bytes)]] void *dst,
                    int byte, $size_t num_bytes) {
	while (num_bytes) {
		if unlikely(!writeb_nopf(dst, (byte_t)(unsigned int)byte))
			break;
		--num_bytes;
		dst = (byte_t *)dst + 1;
	}
	return num_bytes;
}

@@>> memeq_nopf(3)
@@Compare the data pointed to by 2 potentially faulty memory buffers.
@@@return: >0: The contents of the 2 buffers differ from each other.
@@@return:  0: The contents of the 2 buffers are identical.
@@@return: <0: At least one of the 2 buffers is faulty.
[[kernel, noblock, wunused, nothrow, decl_include("<bits/types.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_nopf_memeq)]]
[[requires_function(readb_nopf)]]
[[impl_include("<hybrid/typecore.h>")]]
$ssize_t memeq_nopf([[user, checked, in_opt(num_bytes)]] void const *lhs,
                    [[user, checked, in_opt(num_bytes)]] void const *rhs,
                    $size_t num_bytes) {
	while (num_bytes) {
		uint8_t lhs_byte, rhs_byte;
		if unlikely(!readb_nopf(lhs, &lhs_byte))
			return -1; /* #PF error */
		if unlikely(!readb_nopf(rhs, &rhs_byte))
			return -1; /* #PF error */

		if (lhs_byte != rhs_byte)
			return 1; /* Blobs differ */

		--num_bytes;
		lhs = (byte_t const *)lhs + 1;
		rhs = (byte_t const *)rhs + 1;
	}
	return 0;
}


/* All of the remaining functions are optional */
%[default:no_crt_impl]


@@>> atomic_xch[bwlq]_nopf(3)
@@Try  to atomic_xch  at a  possibly faulty  `addr', storing the
@@old value in `*poldval', and loading a new value from `newval'
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xchb_nopf)]]
[[requires_function(readb_nopf, atomic_cmpxchb_nopf)]]
bool atomic_xchb_nopf([[user, checked, inout_opt]] void *addr,
                      $uint8_t newval, [[out]] $uint8_t *poldval) {
	bool nopf;
	uint8_t expected_oldval;
	do {
		nopf = likely(readb_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchb_nopf(addr, expected_oldval, newval, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xchw_nopf)]]
[[requires_function(readw_nopf, atomic_cmpxchw_nopf)]]
bool atomic_xchw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t newval, [[out]] $uint16_t *poldval) {
	bool nopf;
	uint16_t  expected_oldval;
	do {
		nopf = likely(readw_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchw_nopf(addr, expected_oldval, newval, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xchl_nopf)]]
[[requires_function(readl_nopf, atomic_cmpxchl_nopf)]]
bool atomic_xchl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t newval, [[out]] $uint32_t *poldval) {
	bool nopf;
	uint32_t  expected_oldval;
	do {
		nopf = likely(readl_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchl_nopf(addr, expected_oldval, newval, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xchq_nopf)]]
[[requires_function(readq_nopf, atomic_cmpxchq_nopf)]]
bool atomic_xchq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t newval, [[out]] $uint64_t *poldval) {
	bool nopf;
	uint64_t  expected_oldval;
	do {
		nopf = likely(readq_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchq_nopf(addr, expected_oldval, newval, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}


@@>> atomic_fetchadd[bwlq]_nopf(3)
@@Try to atomic_fetchadd at a possibly faulty `addr', storing  the
@@old value in `*poldval', and adding `newval' onto the stored val
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_fetchaddb_nopf)]]
[[requires_function(readb_nopf, atomic_cmpxchb_nopf)]]
bool atomic_fetchaddb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t addend, [[out]] $uint8_t *poldval) {
	bool nopf;
	uint8_t  expected_oldval;
	do {
		nopf = likely(readb_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchb_nopf(addr, expected_oldval, expected_oldval + addend, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_fetchaddw_nopf)]]
[[requires_function(readw_nopf, atomic_cmpxchw_nopf)]]
bool atomic_fetchaddw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t addend, [[out]] $uint16_t *poldval) {
	bool nopf;
	uint16_t  expected_oldval;
	do {
		nopf = likely(readw_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchw_nopf(addr, expected_oldval, expected_oldval + addend, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_fetchaddl_nopf)]]
[[requires_function(readl_nopf, atomic_cmpxchl_nopf)]]
bool atomic_fetchaddl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t addend, [[out]] $uint32_t *poldval) {
	bool nopf;
	uint32_t  expected_oldval;
	do {
		nopf = likely(readl_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchl_nopf(addr, expected_oldval, expected_oldval + addend, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_fetchaddq_nopf)]]
[[requires_function(readq_nopf, atomic_cmpxchq_nopf)]]
bool atomic_fetchaddq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t addend, [[out]] $uint64_t *poldval) {
	bool nopf;
	uint64_t  expected_oldval;
	do {
		nopf = likely(readq_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchq_nopf(addr, expected_oldval, expected_oldval + addend, poldval));
	} while (likely(nopf) && unlikely(*poldval != expected_oldval));
	return nopf;
}


@@>> atomic_or[bwlq]_nopf(3)
@@Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_orb_nopf)]]
[[requires_function(readb_nopf, atomic_cmpxchb_nopf)]]
bool atomic_orb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask) {
	bool nopf;
	uint8_t expected_oldval, real_oldval;
	do {
		nopf = likely(readb_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchb_nopf(addr, expected_oldval, expected_oldval | mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_orw_nopf)]]
[[requires_function(readw_nopf, atomic_cmpxchw_nopf)]]
bool atomic_orw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask) {
	bool nopf;
	uint16_t expected_oldval, real_oldval;
	do {
		nopf = likely(readw_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchw_nopf(addr, expected_oldval, expected_oldval | mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_orl_nopf)]]
[[requires_function(readl_nopf, atomic_cmpxchl_nopf)]]
bool atomic_orl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask) {
	bool nopf;
	uint32_t expected_oldval, real_oldval;
	do {
		nopf = likely(readl_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchl_nopf(addr, expected_oldval, expected_oldval | mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_orq_nopf)]]
[[requires_function(readq_nopf, atomic_cmpxchq_nopf)]]
bool atomic_orq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask) {
	bool nopf;
	uint64_t expected_oldval, real_oldval;
	do {
		nopf = likely(readq_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchq_nopf(addr, expected_oldval, expected_oldval | mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}


@@>> atomic_and[bwlq]_nopf(3)
@@Try to atomically mask all bits with `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_andb_nopf)]]
[[requires_function(readb_nopf, atomic_cmpxchb_nopf)]]
bool atomic_andb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask) {
	bool nopf;
	uint8_t expected_oldval, real_oldval;
	do {
		nopf = likely(readb_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchb_nopf(addr, expected_oldval, expected_oldval & mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_andw_nopf)]]
[[requires_function(readw_nopf, atomic_cmpxchw_nopf)]]
bool atomic_andw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask) {
	bool nopf;
	uint16_t expected_oldval, real_oldval;
	do {
		nopf = likely(readw_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchw_nopf(addr, expected_oldval, expected_oldval & mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_andl_nopf)]]
[[requires_function(readl_nopf, atomic_cmpxchl_nopf)]]
bool atomic_andl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask) {
	bool nopf;
	uint32_t expected_oldval, real_oldval;
	do {
		nopf = likely(readl_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchl_nopf(addr, expected_oldval, expected_oldval & mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_andq_nopf)]]
[[requires_function(readq_nopf, atomic_cmpxchq_nopf)]]
bool atomic_andq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask) {
	bool nopf;
	uint64_t expected_oldval, real_oldval;
	do {
		nopf = likely(readq_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchq_nopf(addr, expected_oldval, expected_oldval & mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}


@@>> atomic_xor[bwlq]_nopf(3)
@@Try to atomically flip all bits from `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xorb_nopf)]]
[[requires_function(readb_nopf, atomic_cmpxchb_nopf)]]
bool atomic_xorb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask) {
	bool nopf;
	uint8_t expected_oldval, real_oldval;
	do {
		nopf = likely(readb_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchb_nopf(addr, expected_oldval, expected_oldval ^ mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xorw_nopf)]]
[[requires_function(readw_nopf, atomic_cmpxchw_nopf)]]
bool atomic_xorw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask) {
	bool nopf;
	uint16_t expected_oldval, real_oldval;
	do {
		nopf = likely(readw_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchw_nopf(addr, expected_oldval, expected_oldval ^ mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xorl_nopf)]]
[[requires_function(readl_nopf, atomic_cmpxchl_nopf)]]
bool atomic_xorl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask) {
	bool nopf;
	uint32_t expected_oldval, real_oldval;
	do {
		nopf = likely(readl_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchl_nopf(addr, expected_oldval, expected_oldval ^ mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_xorq_nopf)]]
[[requires_function(readq_nopf, atomic_cmpxchq_nopf)]]
bool atomic_xorq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask) {
	bool nopf;
	uint64_t expected_oldval, real_oldval;
	do {
		nopf = likely(readq_nopf(addr, &expected_oldval)) &&
		       likely(atomic_cmpxchq_nopf(addr, expected_oldval, expected_oldval ^ mask, &real_oldval));
	} while (likely(nopf) && unlikely(real_oldval != expected_oldval));
	return nopf;
}


@@>> atomic_cmpxch[bwlq]_nopf(3)
@@Try to do an atomic-compare-exchange at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_cmpxchb_nopf)]]
bool atomic_cmpxchb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t oldval, $uint8_t newval,
                         [[out]] $uint8_t *preal_oldval);

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_cmpxchw_nopf)]]
bool atomic_cmpxchw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t oldval, $uint16_t newval,
                         [[out]] $uint16_t *preal_oldval);

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_cmpxchl_nopf)]]
bool atomic_cmpxchl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t oldval, $uint32_t newval,
                         [[out]] $uint32_t *preal_oldval);

[[guard, kernel, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]]
[[preferred_bind_arch_macro_replacement("<kos/bits/nopf.h>", __arch_atomic_cmpxchq_nopf)]]
bool atomic_cmpxchq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t oldval, $uint64_t newval,
                         [[out]] $uint64_t *preal_oldval);



%{
#ifdef __arch_insb_nopf
#define insb_nopf __arch_insb_nopf
#endif /* __arch_insb_nopf */
#ifdef __arch_insw_nopf
#define insw_nopf __arch_insw_nopf
#endif /* __arch_insw_nopf */
#ifdef __arch_insl_nopf
#define insl_nopf __arch_insl_nopf
#endif /* __arch_insl_nopf */
#ifdef __arch_outsb_nopf
#define outsb_nopf __arch_outsb_nopf
#endif /* __arch_outsb_nopf */
#ifdef __arch_outsw_nopf
#define outsw_nopf __arch_outsw_nopf
#endif /* __arch_outsw_nopf */
#ifdef __arch_outsl_nopf
#define outsl_nopf __arch_outsl_nopf
#endif /* __arch_outsl_nopf */

/* Type-generic helper macros. */
#define read_nopf(addr, presult)                          \
	(sizeof(*(addr)) == 1                                 \
	 ? readb_nopf(addr, (__UINT8_TYPE__ *)(presult))      \
	 : sizeof(*(addr)) == 2                               \
	   ? readw_nopf(addr, (__UINT16_TYPE__ *)(presult))   \
	   : sizeof(*(addr)) == 4                             \
	     ? readl_nopf(addr, (__UINT32_TYPE__ *)(presult)) \
	     : readq_nopf(addr, (__UINT64_TYPE__ *)(presult)))
#define write_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                              \
	 ? writeb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                            \
	   ? writew_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                          \
	     ? writel_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : writeq_nopf(addr, (__UINT64_TYPE__)(value)))

#if (defined(__atomic_cmpxchb_nopf_defined) && defined(__atomic_cmpxchw_nopf_defined) && \
     defined(__atomic_cmpxchl_nopf_defined) && defined(__atomic_cmpxchq_nopf_defined))
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                                \
	(sizeof(*(addr)) == 1                                                                                                     \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))        \
	 : sizeof(*(addr)) == 2                                                                                                   \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval))   \
	   : sizeof(*(addr)) == 4                                                                                                 \
	     ? atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)) \
	     : atomic_cmpxchq_nopf(addr, (__UINT64_TYPE__)(oldval), (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(preal_oldval)))
#elif (defined(__atomic_cmpxchb_nopf_defined) && defined(__atomic_cmpxchw_nopf_defined) && defined(__atomic_cmpxchl_nopf_defined))
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                              \
	(sizeof(*(addr)) == 1                                                                                                   \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))      \
	 : sizeof(*(addr)) == 2                                                                                                 \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval)) \
	   : atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)))
#endif /* ... */

#if (defined(__atomic_xchb_nopf_defined) && defined(__atomic_xchw_nopf_defined) && \
     defined(__atomic_xchl_nopf_defined) && defined(__atomic_xchq_nopf_defined))
#define atomic_xch_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                  \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                              \
	     ? atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_xchq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif (defined(__atomic_xchb_nopf_defined) && defined(__atomic_xchw_nopf_defined) && defined(__atomic_xchl_nopf_defined))
#define atomic_xch_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                              \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#if (defined(__atomic_fetchaddb_nopf_defined) && defined(__atomic_fetchaddw_nopf_defined) && \
     defined(__atomic_fetchaddl_nopf_defined) && defined(__atomic_fetchaddq_nopf_defined))
#define atomic_fetchadd_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                       \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                     \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                                   \
	     ? atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_fetchaddq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif (defined(__atomic_fetchaddb_nopf_defined) && defined(__atomic_fetchaddw_nopf_defined) && defined(__atomic_fetchaddl_nopf_defined))
#define atomic_fetchadd_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                     \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                                   \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#if (defined(__atomic_orb_nopf_defined) && defined(__atomic_orw_nopf_defined) && \
     defined(__atomic_orl_nopf_defined) && defined(__atomic_orq_nopf_defined))
#define atomic_or_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                  \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                              \
	     ? atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_orq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_orb_nopf_defined) && defined(__atomic_orw_nopf_defined) && defined(__atomic_orl_nopf_defined))
#define atomic_or_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                              \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#if (defined(__atomic_andb_nopf_defined) && defined(__atomic_andw_nopf_defined) && \
     defined(__atomic_andl_nopf_defined) && defined(__atomic_andq_nopf_defined))
#define atomic_and_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_andq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_andb_nopf_defined) && defined(__atomic_andw_nopf_defined) && defined(__atomic_andl_nopf_defined))
#define atomic_and_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#if (defined(__atomic_xorb_nopf_defined) && defined(__atomic_xorw_nopf_defined) && \
     defined(__atomic_xorl_nopf_defined) && defined(__atomic_xorq_nopf_defined))
#define atomic_xor_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_xorq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_xorb_nopf_defined) && defined(__atomic_xorw_nopf_defined) && defined(__atomic_xorl_nopf_defined))
#define atomic_xor_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

}
