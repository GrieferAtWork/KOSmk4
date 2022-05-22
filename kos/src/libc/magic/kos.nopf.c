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
%[default:section(".text.crt.none_of_these_are_defined_in_libc")]

/* Disable CRT implementations for all functions (only defined by arch-specific for now) */
%[default:no_crt_impl]

/* Enable guard macros for all functions */
%[default:guard]

%[insert:prefix(
#include <kos/bits/nopf.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

/* Define nopf functions not already defined in `<kos/bits/nopf.h>' */

}


@@>> memeq_nopf(3)
@@Compare the data pointed to by 2 potentially faulty memory buffers.
@@@return: >0: The contents of the 2 buffers differ from each other.
@@@return:  0: The contents of the 2 buffers are identical.
@@@return: <0: At least one of the 2 buffers is faulty.
[[noblock, wunused, nothrow, decl_include("<bits/types.h>")]]
$ssize_t memeq_nopf([[user, checked, in_opt(num_bytes)]] void const *lhs,
                    [[user, checked, in_opt(num_bytes)]] void const *rhs,
                    $size_t num_bytes);

@@>> read[bwlq]_nopf(3)
@@Try to read from a possibly faulty `addr' into `*presult'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool readb_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint8_t *presult);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]] bool readw_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint16_t *presult);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]] bool readl_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint32_t *presult);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("readb_nopf")]] bool readq_nopf([[user, checked, in_opt]] void const *addr, [[out]] $uint64_t *presult);

@@>> write[bwlq]_nopf(3)
@@Try to write `val' into a possibly faulty `addr'
@@Return  `true'  on  success,  `false'  on  error
[[no_crt_impl, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool writeb_nopf([[user, checked, out_opt]] void *addr, $uint8_t val);
[[no_crt_impl, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]] bool writew_nopf([[user, checked, out_opt]] void *addr, $uint16_t val);
[[no_crt_impl, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]] bool writel_nopf([[user, checked, out_opt]] void *addr, $uint32_t val);
[[no_crt_impl, noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("writeb_nopf")]] bool writeq_nopf([[user, checked, out_opt]] void *addr, $uint64_t val);


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
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
$size_t memcpy_nopf([[user, checked, out_opt(num_bytes)]] void *dst,
                    [[user, checked, in_opt(num_bytes)]] void const *src,
                    $size_t num_bytes);

@@>> memset_nopf(3)
@@@return: * : The # of bytes that could not be accessed
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]]
$size_t memset_nopf([[user, checked, out_opt(num_bytes)]] void *dst,
                    int byte, $size_t num_bytes);


@@>> atomic_xch[bwlq]_nopf(3)
@@Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
@@old value in `*poldval', and loading a new value from `newval'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_xchb_nopf([[user, checked, inout_opt]] void const *addr, $uint8_t newval, [[out]] $uint8_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]] bool atomic_xchw_nopf([[user, checked, inout_opt]] void const *addr, $uint16_t newval, [[out]] $uint16_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]] bool atomic_xchl_nopf([[user, checked, inout_opt]] void const *addr, $uint32_t newval, [[out]] $uint32_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xchb_nopf")]] bool atomic_xchq_nopf([[user, checked, inout_opt]] void const *addr, $uint64_t newval, [[out]] $uint64_t *poldval);

@@>> atomic_fetchadd[bwlq]_nopf(3)
@@Try to ATOMIC_FETCHADD at a possibly faulty `addr', storing  the
@@old value in `*poldval', and adding `newval' onto the stored val
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_fetchaddb_nopf([[user, checked, inout_opt]] void const *addr, $uint8_t addend, [[out]] $uint8_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]] bool atomic_fetchaddw_nopf([[user, checked, inout_opt]] void const *addr, $uint16_t addend, [[out]] $uint16_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]] bool atomic_fetchaddl_nopf([[user, checked, inout_opt]] void const *addr, $uint32_t addend, [[out]] $uint32_t *poldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_fetchaddb_nopf")]] bool atomic_fetchaddq_nopf([[user, checked, inout_opt]] void const *addr, $uint64_t addend, [[out]] $uint64_t *poldval);

@@>> atomic_or[bwlq]_nopf(3)
@@Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_orb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]] bool atomic_orw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]] bool atomic_orl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_orb_nopf")]] bool atomic_orq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask);

@@>> atomic_and[bwlq]_nopf(3)
@@Try to atomically mask all bits with `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_andb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]] bool atomic_andw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]] bool atomic_andl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_andb_nopf")]] bool atomic_andq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask);

@@>> atomic_xor[bwlq]_nopf(3)
@@Try to atomically flip all bits from `mask' at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_xorb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]] bool atomic_xorw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]] bool atomic_xorl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t mask);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_xorb_nopf")]] bool atomic_xorq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t mask);

@@>> atomic_cmpxch[bwlq]_nopf(3)
@@Try to do an atomic-compare-exchange at the possibly faulty `addr'
@@Return `true' on success, `false' on fault
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>")]] bool atomic_cmpxchb_nopf([[user, checked, inout_opt]] void *addr, $uint8_t oldval, $uint8_t newval, [[out]] $uint8_t *preal_oldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]] bool atomic_cmpxchw_nopf([[user, checked, inout_opt]] void *addr, $uint16_t oldval, $uint16_t newval, [[out]] $uint16_t *preal_oldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]] bool atomic_cmpxchl_nopf([[user, checked, inout_opt]] void *addr, $uint32_t oldval, $uint32_t newval, [[out]] $uint32_t *preal_oldval);
[[noblock, wunused, nothrow, decl_include("<hybrid/typecore.h>"), doc_alias("atomic_cmpxchb_nopf")]] bool atomic_cmpxchq_nopf([[user, checked, inout_opt]] void *addr, $uint64_t oldval, $uint64_t newval, [[out]] $uint64_t *preal_oldval);


%{

#ifdef __memcpy_nopf_defined
#ifndef __readb_nopf_defined
#define __readb_nopf_defined 1
#define readb_nopf(addr, presult) (memcpy_nopf(presult, addr, 1) == 0)
#endif /* !__readb_nopf_defined */
#ifndef __readw_nopf_defined
#define __readw_nopf_defined 1
#define readw_nopf(addr, presult) (memcpy_nopf(presult, addr, 2) == 0)
#endif /* !__readw_nopf_defined */
#ifndef __readl_nopf_defined
#define __readl_nopf_defined 1
#define readl_nopf(addr, presult) (memcpy_nopf(presult, addr, 4) == 0)
#endif /* !__readl_nopf_defined */
#ifndef __readq_nopf_defined
#define __readq_nopf_defined 1
#define readq_nopf(addr, presult) (memcpy_nopf(presult, addr, 8) == 0)
#endif /* !__readq_nopf_defined */
#ifdef __NO_XBLOCK
#ifndef __writeb_nopf_defined
#define __writeb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writeb_nopf)(__USER __CHECKED void *__addr, __uint8_t __val) {
	return memcpy_nopf(__addr, &__val, 1) == 0;
}
#endif /* !__writeb_nopf_defined */
#ifndef __writew_nopf_defined
#define __writew_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writew_nopf)(__USER __CHECKED void *__addr, __uint16_t __val) {
	return memcpy_nopf(__addr, &__val, 2) == 0;
}
#endif /* !__writew_nopf_defined */
#ifndef __writel_nopf_defined
#define __writel_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writel_nopf)(__USER __CHECKED void *__addr, __uint32_t __val) {
	return memcpy_nopf(__addr, &__val, 4) == 0;
}
#endif /* !__writel_nopf_defined */
#ifndef __writeq_nopf_defined
#define __writeq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writeq_nopf)(__USER __CHECKED void *__addr, __uint64_t __val) {
	return memcpy_nopf(__addr, &__val, 8) == 0;
}
#endif /* !__writeq_nopf_defined */
#else /* __NO_XBLOCK */
#ifndef __writeb_nopf_defined
#define __writeb_nopf_defined 1
#define writeb_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint8_t __wnpf_val = (val);                     \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 1) == 0; \
	})
#endif /* !__writeb_nopf_defined */
#ifndef __writew_nopf_defined
#define __writew_nopf_defined 1
#define writew_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint16_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 2) == 0; \
	})
#endif /* !__writew_nopf_defined */
#ifndef __writel_nopf_defined
#define __writel_nopf_defined 1
#define writel_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint32_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 4) == 0; \
	})
#endif /* !__writel_nopf_defined */
#ifndef __writeq_nopf_defined
#define __writeq_nopf_defined 1
#define writeq_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint64_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 8) == 0; \
	})
#endif /* !__writeq_nopf_defined */
#endif /* !__NO_XBLOCK */
#endif /* __memcpy_nopf_defined */


/* Type-generic helper macros. */
#if (defined(__readb_nopf_defined) && defined(__readw_nopf_defined) && \
     defined(__readl_nopf_defined) && defined(__readq_nopf_defined))
#define read_nopf(addr, presult)                          \
	(sizeof(*(addr)) == 1                                 \
	 ? readb_nopf(addr, (__UINT8_TYPE__ *)(presult))      \
	 : sizeof(*(addr)) == 2                               \
	   ? readw_nopf(addr, (__UINT16_TYPE__ *)(presult))   \
	   : sizeof(*(addr)) == 4                             \
	     ? readl_nopf(addr, (__UINT32_TYPE__ *)(presult)) \
	     : readq_nopf(addr, (__UINT64_TYPE__ *)(presult)))
#endif /* __read[bwlq]_nopf_defined */
#if (defined(__writeb_nopf_defined) && defined(__writew_nopf_defined) && \
     defined(__writel_nopf_defined) && defined(__writeq_nopf_defined))
#define write_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                              \
	 ? writeb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                            \
	   ? writew_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                          \
	     ? writel_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : writeq_nopf(addr, (__UINT64_TYPE__)(value)))
#endif /* __write[bwlq]_nopf_defined */

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
