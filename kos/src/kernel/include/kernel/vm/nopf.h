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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_NOPF_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_NOPF_H 1

#include <kernel/compiler.h>

#include <kernel/arch/vm/nopf.h>

#include <hybrid/typecore.h>

#ifdef __CC__
DECL_BEGIN

#ifndef CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF
/* Copy memory from `src' to `dst', but stop if any sort of #PF happens,
 * regardless of that #PF being handable or not (aka: load-on-access, or
 * copy-on-write will never be triggered by this function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
FUNDEF NOBLOCK WUNUSED size_t
NOTHROW(KCALL memcpy_nopf)(USER CHECKED void *dst,
                           USER CHECKED void const *src,
                           size_t num_bytes);
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF
/* Same as memcpy_nopf(), but implements memset() functionality */
FUNDEF NOBLOCK WUNUSED size_t
NOTHROW(KCALL memset_nopf)(USER CHECKED void *dst,
                           int byte,
                           size_t num_bytes);
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF
/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
FUNDEF NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_nopf)(USER CHECKED void const *lhs,
                          USER CHECKED void const *rhs,
                          size_t num_bytes);
/* Same as `memeq_nopf()', but the function may assume that only `user_buffer' can be faulty. */
FUNDEF NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_ku_nopf)(KERNEL void const *kernel_buffer,
                             USER CHECKED void const *user_buffer,
                             size_t num_bytes);
#else /* !CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF */
#ifndef memeq_ku_nopf
#define memeq_ku_nopf  memeq_nopf
#endif /* !memeq_ku_nopf */
#endif /* CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
#define readb_nopf(addr, presult) (memcpy_nopf(presult, addr, 1) == 0)
#define readw_nopf(addr, presult) (memcpy_nopf(presult, addr, 2) == 0)
#define readl_nopf(addr, presult) (memcpy_nopf(presult, addr, 4) == 0)
#define readq_nopf(addr, presult) (memcpy_nopf(presult, addr, 8) == 0)
#endif /* !CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF
/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writeb_nopf)(USER CHECKED void *addr, u8 value) {
	return memcpy_nopf(addr, &value, 1) == 0;
}
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writew_nopf)(USER CHECKED void *addr, u16 value) {
	return memcpy_nopf(addr, &value, 2) == 0;
}
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writel_nopf)(USER CHECKED void *addr, u32 value) {
	return memcpy_nopf(addr, &value, 4) == 0;
}
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writeq_nopf)(USER CHECKED void *addr, u64 value) {
	return memcpy_nopf(addr, &value, 8) == 0;
}
#endif /* !CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF */


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
	 : sizeof(va * (addr)lue) == 2                     \
	   ? writew_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                          \
	     ? writel_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : writeq_nopf(addr, (__UINT64_TYPE__)(value)))

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_XCHBWLQ_NOPF
#define atomic_xch_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                  \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                              \
	     ? atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_xchq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_XCHBWL_NOPF)
#define atomic_xch_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                              \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_FETCHADDBWLQ_NOPF
#define atomic_fetchadd_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                       \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                     \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                                   \
	     ? atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_fetchaddq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_FETCHADDBWL_NOPF)
#define atomic_fetchadd_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                     \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                                   \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_ORBWLQ_NOPF
#define atomic_or_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                  \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                              \
	     ? atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_orq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_ORBWL_NOPF)
#define atomic_or_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                              \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_ANDBWLQ_NOPF
#define atomic_and_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_andq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_ANDBWL_NOPF)
#define atomic_and_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_XORBWLQ_NOPF
#define atomic_xor_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_xorq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_XORBWL_NOPF)
#define atomic_xor_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#ifdef CONFIG_VM_ARCH_DEFINES_ATOMIC_CMPXCHBWLQ_NOPF
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                                \
	(sizeof(*(addr)) == 1                                                                                                     \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))        \
	 : sizeof(*(addr)) == 2                                                                                                   \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval))   \
	   : sizeof(*(addr)) == 4                                                                                                 \
	     ? atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)) \
	     : atomic_cmpxchq_nopf(addr, (__UINT64_TYPE__)(oldval), (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(preal_oldval)))
#elif defined(CONFIG_VM_ARCH_DEFINES_ATOMIC_CMPXCHBWL_NOPF)
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                              \
	(sizeof(*(addr)) == 1                                                                                                   \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))      \
	 : sizeof(*(addr)) == 2                                                                                                 \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval)) \
	   : atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)))
#endif /* ... */


/* TODO: When `CONFIG_VM_ARCH_DEFINES_ATOMIC_CMPXCHBWL_NOPF'
 *         or `CONFIG_VM_ARCH_DEFINES_ATOMIC_CMPXCHBWLQ_NOPF'
 *       is defined, then we should try to substitute other,
 *       missing operations using these ones. */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_NOPF_H */
