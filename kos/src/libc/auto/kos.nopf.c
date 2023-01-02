/* HASH CRC-32:0x19de2a47 */
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
#ifndef GUARD_LIBC_AUTO_KOS_NOPF_C
#define GUARD_LIBC_AUTO_KOS_NOPF_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.nopf.h"
#include <kos/bits/nopf.h>

DECL_BEGIN

#define crt_readb_nopf  libc_readb_nopf
#define crt_readw_nopf  libc_readw_nopf
#define crt_readl_nopf  libc_readl_nopf
#define crt_readq_nopf  libc_readq_nopf
#define crt_memcpy_nopf libc_memcpy_nopf
#ifndef __arch_readb_nopf
#include <hybrid/typecore.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool
NOTHROW(LIBCCALL libc_readb_nopf)(void const *addr,
                                  uint8_t *presult) {
#if defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
	return likely(crt_memcpy_nopf(presult, addr, 1) == 0);
#elif defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf)
	bool ok;
	union { uint16_t w; uint8_t b[2]; } result;
	ok = crt_readw_nopf((void const *)((uintptr_t)addr & ~1), &result.w);
	*presult = result.b[(uintptr_t)addr & 1];
	return ok;
#elif defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf)
	bool ok;
	union { uint32_t l; uint8_t b[4]; } result;
	ok = crt_readl_nopf((void const *)((uintptr_t)addr & ~3), &result.l);
	*presult = result.b[(uintptr_t)addr & 3];
	return ok;
#else /* ... */
	bool ok;
	union { uint64_t q; uint8_t b[2]; } result;
	ok = crt_readw_nopf((void const *)((uintptr_t)addr & ~7), &result.q);
	*presult = result.b[(uintptr_t)addr & 7];
	return ok;
#endif /* !... */
}
#endif /* !__arch_readb_nopf */
#ifndef __arch_readw_nopf
#include <hybrid/typecore.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool
NOTHROW(LIBCCALL libc_readw_nopf)(void const *addr,
                                  uint16_t *presult) {
#if defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || (!defined(__arch_memcpy_nopf) && !defined(__CRT_HAVE_memcpy_nopf))
	bool ok;
	union { uint16_t w; uint8_t b[2]; } result;
	ok = likely(libc_readb_nopf((void const *)((uintptr_t)addr + 0), &result.b[0])) &&
	     likely(libc_readb_nopf((void const *)((uintptr_t)addr + 1), &result.b[1]));
	*presult = result.w;
	return ok;
#else /* __arch_readb_nopf || __CRT_HAVE_readb_nopf || (!__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) */
	return likely(crt_memcpy_nopf(presult, addr, 2) == 0);
#endif /* !__arch_readb_nopf && !__CRT_HAVE_readb_nopf && (__arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) */
}
#endif /* !__arch_readw_nopf */
#ifndef __arch_readl_nopf
#include <hybrid/typecore.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool
NOTHROW(LIBCCALL libc_readl_nopf)(void const *addr,
                                  uint32_t *presult) {
#if defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || (!defined(__arch_memcpy_nopf) && !defined(__CRT_HAVE_memcpy_nopf))
	bool ok;
	union { uint32_t l; uint16_t w[2]; } result;
	ok = likely(libc_readw_nopf((void const *)((uintptr_t)addr + 0), &result.w[0])) &&
	     likely(libc_readw_nopf((void const *)((uintptr_t)addr + 2), &result.w[1]));
	*presult = result.l;
	return ok;
#else /* __arch_readw_nopf || __CRT_HAVE_readw_nopf || (!__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) */
	return likely(crt_memcpy_nopf(presult, addr, 4) == 0);
#endif /* !__arch_readw_nopf && !__CRT_HAVE_readw_nopf && (__arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) */
}
#endif /* !__arch_readl_nopf */
#ifndef __arch_readq_nopf
#include <hybrid/typecore.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool
NOTHROW(LIBCCALL libc_readq_nopf)(void const *addr,
                                  uint64_t *presult) {
#if defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || (!defined(__arch_memcpy_nopf) && !defined(__CRT_HAVE_memcpy_nopf))
	bool ok;
	union { uint64_t q; uint32_t l[2]; } result;
	ok = likely(libc_readl_nopf((void const *)((uintptr_t)addr + 0), &result.l[0])) &&
	     likely(libc_readl_nopf((void const *)((uintptr_t)addr + 4), &result.l[1]));
	*presult = result.q;
	return ok;
#else /* __arch_readl_nopf || __CRT_HAVE_readl_nopf || (!__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) */
	return likely(crt_memcpy_nopf(presult, addr, 8) == 0);
#endif /* !__arch_readl_nopf && !__CRT_HAVE_readl_nopf && (__arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) */
}
#endif /* !__arch_readq_nopf */
#ifndef __arch_writeb_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool
NOTHROW(LIBCCALL libc_writeb_nopf)(void *addr,
                                   uint8_t val) {
	return likely(crt_memcpy_nopf(addr, &val, 1) == 0);
}
#endif /* !__arch_writeb_nopf */
#ifndef __arch_writew_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool
NOTHROW(LIBCCALL libc_writew_nopf)(void *addr,
                                   uint16_t val) {
	union { uint16_t w; uint8_t b[2]; } uval;
	uint8_t old_addr0;
	uval.w = val;
	if unlikely(!libc_readb_nopf(addr, &old_addr0))
		return false;
	if unlikely(!libc_writeb_nopf(addr, uval.b[0]))
		return false;
	if unlikely(!libc_writeb_nopf((uint8_t *)addr + 1, uval.b[1])) {
		COMPILER_UNUSED(libc_writeb_nopf(addr, old_addr0));
		return false;
	}
	return true;
}
#endif /* !__arch_writew_nopf */
#ifndef __arch_writel_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool
NOTHROW(LIBCCALL libc_writel_nopf)(void *addr,
                                   uint32_t val) {
	union { uint32_t l; uint16_t w[2]; } uval;
	uint16_t old_addr0;
	uval.l = val;
	if unlikely(!libc_readw_nopf(addr, &old_addr0))
		return false;
	if unlikely(!libc_writew_nopf(addr, uval.w[0]))
		return false;
	if unlikely(!libc_writew_nopf((uint16_t *)addr + 1, uval.w[1])) {
		COMPILER_UNUSED(libc_writew_nopf(addr, old_addr0));
		return false;
	}
	return true;
}
#endif /* !__arch_writel_nopf */
#ifndef __arch_writeq_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool
NOTHROW(LIBCCALL libc_writeq_nopf)(void *addr,
                                   uint64_t val) {
	union { uint64_t q; uint32_t l[2]; } uval;
	uint32_t old_addr0;
	uval.q = val;
	if unlikely(!libc_readl_nopf(addr, &old_addr0))
		return false;
	if unlikely(!libc_writel_nopf(addr, uval.l[0]))
		return false;
	if unlikely(!libc_writel_nopf((uint32_t *)addr + 1, uval.l[1])) {
		COMPILER_UNUSED(libc_writel_nopf(addr, old_addr0));
		return false;
	}
	return true;
}
#endif /* !__arch_writeq_nopf */
#ifndef __arch_memcpy_nopf
/* >> memcpy_nopf(3)
 * Copy memory from `src' to `dst', but  stop if any sort of #PF  happens,
 * regardless of that #PF being handleable or not (aka: load-on-access, or
 * copy-on-write  will never be  triggered by this  function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding  an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller  holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW(LIBCCALL libc_memcpy_nopf)(void *dst,
                                   void const *src,
                                   size_t num_bytes) {
	while (num_bytes) {
		byte_t b;
		if unlikely(!libc_readb_nopf(src, &b))
			break;
		if unlikely(!libc_writeb_nopf(dst, b))
			break;
		--num_bytes;
		dst = (byte_t *)dst + 1;
		src = (byte_t const *)src + 1;
	}
	return num_bytes;
}
#endif /* !__arch_memcpy_nopf */
#ifndef __arch_memset_nopf
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_OUTS(1, 3) size_t
NOTHROW(LIBCCALL libc_memset_nopf)(void *dst,
                                   int byte,
                                   size_t num_bytes) {
	while (num_bytes) {
		if unlikely(!libc_writeb_nopf(dst, (byte_t)(unsigned int)byte))
			break;
		--num_bytes;
		dst = (byte_t *)dst + 1;
	}
	return num_bytes;
}
#endif /* !__arch_memset_nopf */
#ifndef __arch_nopf_memeq
#include <hybrid/typecore.h>
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
INTERN ATTR_SECTION(".text.crt.string.nopf") WUNUSED __NOBLOCK ATTR_INS(1, 3) ATTR_INS(2, 3) ssize_t
NOTHROW(LIBCCALL libc_memeq_nopf)(void const *lhs,
                                  void const *rhs,
                                  size_t num_bytes) {
	while (num_bytes) {
		uint8_t lhs_byte, rhs_byte;
		if unlikely(!libc_readb_nopf(lhs, &lhs_byte))
			return -1; /* #PF error */
		if unlikely(!libc_readb_nopf(rhs, &rhs_byte))
			return -1; /* #PF error */

		if (lhs_byte != rhs_byte)
			return 1; /* Blobs differ */

		--num_bytes;
		lhs = (byte_t const *)lhs + 1;
		rhs = (byte_t const *)rhs + 1;
	}
	return 0;
}
#endif /* !__arch_nopf_memeq */

DECL_END

#ifndef __arch_readb_nopf
DEFINE_PUBLIC_ALIAS(readb_nopf, libc_readb_nopf);
#endif /* !__arch_readb_nopf */
#ifndef __arch_readw_nopf
DEFINE_PUBLIC_ALIAS(readw_nopf, libc_readw_nopf);
#endif /* !__arch_readw_nopf */
#ifndef __arch_readl_nopf
DEFINE_PUBLIC_ALIAS(readl_nopf, libc_readl_nopf);
#endif /* !__arch_readl_nopf */
#ifndef __arch_readq_nopf
DEFINE_PUBLIC_ALIAS(readq_nopf, libc_readq_nopf);
#endif /* !__arch_readq_nopf */
#ifndef __arch_writeb_nopf
DEFINE_PUBLIC_ALIAS(writeb_nopf, libc_writeb_nopf);
#endif /* !__arch_writeb_nopf */
#ifndef __arch_writew_nopf
DEFINE_PUBLIC_ALIAS(writew_nopf, libc_writew_nopf);
#endif /* !__arch_writew_nopf */
#ifndef __arch_writel_nopf
DEFINE_PUBLIC_ALIAS(writel_nopf, libc_writel_nopf);
#endif /* !__arch_writel_nopf */
#ifndef __arch_writeq_nopf
DEFINE_PUBLIC_ALIAS(writeq_nopf, libc_writeq_nopf);
#endif /* !__arch_writeq_nopf */
#ifndef __arch_memcpy_nopf
DEFINE_PUBLIC_ALIAS(memcpy_nopf, libc_memcpy_nopf);
#endif /* !__arch_memcpy_nopf */
#ifndef __arch_memset_nopf
DEFINE_PUBLIC_ALIAS(memset_nopf, libc_memset_nopf);
#endif /* !__arch_memset_nopf */
#ifndef __arch_nopf_memeq
DEFINE_PUBLIC_ALIAS(memeq_nopf, libc_memeq_nopf);
#endif /* !__arch_nopf_memeq */

#endif /* !GUARD_LIBC_AUTO_KOS_NOPF_C */
