/* HASH CRC-32:0x9827663b */
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
#ifndef GUARD_LIBC_AUTO_KOS_NOPF_H
#define GUARD_LIBC_AUTO_KOS_NOPF_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/nopf.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <kos/bits/nopf.h>
#ifdef __arch_readb_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libd_readb_nopf(addr, presult) __arch_readb_nopf(addr, presult)
#else /* __arch_readb_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBDCALL libd_readb_nopf)(void const *addr, uint8_t *presult);
#endif /* !__arch_readb_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#include <kos/bits/nopf.h>
#ifdef __arch_readb_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libc_readb_nopf(addr, presult) __arch_readb_nopf(addr, presult)
#else /* __arch_readb_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBCCALL libc_readb_nopf)(void const *addr, uint8_t *presult);
#endif /* !__arch_readb_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_readw_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libd_readw_nopf(addr, presult) __arch_readw_nopf(addr, presult)
#else /* __arch_readw_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBDCALL libd_readw_nopf)(void const *addr, uint16_t *presult);
#endif /* !__arch_readw_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_readw_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libc_readw_nopf(addr, presult) __arch_readw_nopf(addr, presult)
#else /* __arch_readw_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBCCALL libc_readw_nopf)(void const *addr, uint16_t *presult);
#endif /* !__arch_readw_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_readl_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libd_readl_nopf(addr, presult) __arch_readl_nopf(addr, presult)
#else /* __arch_readl_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBDCALL libd_readl_nopf)(void const *addr, uint32_t *presult);
#endif /* !__arch_readl_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_readl_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libc_readl_nopf(addr, presult) __arch_readl_nopf(addr, presult)
#else /* __arch_readl_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBCCALL libc_readl_nopf)(void const *addr, uint32_t *presult);
#endif /* !__arch_readl_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_readq_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libd_readq_nopf(addr, presult) __arch_readq_nopf(addr, presult)
#else /* __arch_readq_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBDCALL libd_readq_nopf)(void const *addr, uint64_t *presult);
#endif /* !__arch_readq_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_readq_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define libc_readq_nopf(addr, presult) __arch_readq_nopf(addr, presult)
#else /* __arch_readq_nopf */
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
INTDEF WUNUSED __NOBLOCK ATTR_IN_OPT(1) ATTR_OUT(2) bool NOTHROW(LIBCCALL libc_readq_nopf)(void const *addr, uint64_t *presult);
#endif /* !__arch_readq_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_writeb_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libd_writeb_nopf(addr, val) __arch_writeb_nopf(addr, val)
#else /* __arch_writeb_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBDCALL libd_writeb_nopf)(void *addr, uint8_t val);
#endif /* !__arch_writeb_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_writeb_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libc_writeb_nopf(addr, val) __arch_writeb_nopf(addr, val)
#else /* __arch_writeb_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBCCALL libc_writeb_nopf)(void *addr, uint8_t val);
#endif /* !__arch_writeb_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_writew_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libd_writew_nopf(addr, val) __arch_writew_nopf(addr, val)
#else /* __arch_writew_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBDCALL libd_writew_nopf)(void *addr, uint16_t val);
#endif /* !__arch_writew_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_writew_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libc_writew_nopf(addr, val) __arch_writew_nopf(addr, val)
#else /* __arch_writew_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBCCALL libc_writew_nopf)(void *addr, uint16_t val);
#endif /* !__arch_writew_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_writel_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libd_writel_nopf(addr, val) __arch_writel_nopf(addr, val)
#else /* __arch_writel_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBDCALL libd_writel_nopf)(void *addr, uint32_t val);
#endif /* !__arch_writel_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_writel_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libc_writel_nopf(addr, val) __arch_writel_nopf(addr, val)
#else /* __arch_writel_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBCCALL libc_writel_nopf)(void *addr, uint32_t val);
#endif /* !__arch_writel_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_writeq_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libd_writeq_nopf(addr, val) __arch_writeq_nopf(addr, val)
#else /* __arch_writeq_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBDCALL libd_writeq_nopf)(void *addr, uint64_t val);
#endif /* !__arch_writeq_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_writeq_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define libc_writeq_nopf(addr, val) __arch_writeq_nopf(addr, val)
#else /* __arch_writeq_nopf */
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
INTDEF WUNUSED __NOBLOCK ATTR_OUT_OPT(1) bool NOTHROW(LIBCCALL libc_writeq_nopf)(void *addr, uint64_t val);
#endif /* !__arch_writeq_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_memcpy_nopf
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
#define libd_memcpy_nopf(dst, src, num_bytes) __arch_memcpy_nopf(dst, src, num_bytes)
#else /* __arch_memcpy_nopf */
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
INTDEF WUNUSED __NOBLOCK ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW(LIBDCALL libd_memcpy_nopf)(void *dst, void const *src, size_t num_bytes);
#endif /* !__arch_memcpy_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_memcpy_nopf
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
#define libc_memcpy_nopf(dst, src, num_bytes) __arch_memcpy_nopf(dst, src, num_bytes)
#else /* __arch_memcpy_nopf */
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
INTDEF WUNUSED __NOBLOCK ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t NOTHROW(LIBCCALL libc_memcpy_nopf)(void *dst, void const *src, size_t num_bytes);
#endif /* !__arch_memcpy_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_memset_nopf
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
#define libd_memset_nopf(dst, byte, num_bytes) __arch_memset_nopf(dst, byte, num_bytes)
#else /* __arch_memset_nopf */
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
INTDEF WUNUSED __NOBLOCK ATTR_OUTS(1, 3) size_t NOTHROW(LIBDCALL libd_memset_nopf)(void *dst, int byte, size_t num_bytes);
#endif /* !__arch_memset_nopf */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_memset_nopf
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
#define libc_memset_nopf(dst, byte, num_bytes) __arch_memset_nopf(dst, byte, num_bytes)
#else /* __arch_memset_nopf */
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
INTDEF WUNUSED __NOBLOCK ATTR_OUTS(1, 3) size_t NOTHROW(LIBCCALL libc_memset_nopf)(void *dst, int byte, size_t num_bytes);
#endif /* !__arch_memset_nopf */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __arch_nopf_memeq
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
#define libd_memeq_nopf(lhs, rhs, num_bytes) __arch_nopf_memeq(lhs, rhs, num_bytes)
#else /* __arch_nopf_memeq */
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
INTDEF WUNUSED __NOBLOCK ATTR_INS(1, 3) ATTR_INS(2, 3) ssize_t NOTHROW(LIBDCALL libd_memeq_nopf)(void const *lhs, void const *rhs, size_t num_bytes);
#endif /* !__arch_nopf_memeq */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __arch_nopf_memeq
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
#define libc_memeq_nopf(lhs, rhs, num_bytes) __arch_nopf_memeq(lhs, rhs, num_bytes)
#else /* __arch_nopf_memeq */
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
INTDEF WUNUSED __NOBLOCK ATTR_INS(1, 3) ATTR_INS(2, 3) ssize_t NOTHROW(LIBCCALL libc_memeq_nopf)(void const *lhs, void const *rhs, size_t num_bytes);
#endif /* !__arch_nopf_memeq */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_NOPF_H */
