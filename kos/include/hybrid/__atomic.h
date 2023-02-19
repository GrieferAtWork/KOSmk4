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
#ifndef __GUARD_HYBRID___ATOMIC_H
#define __GUARD_HYBRID___ATOMIC_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifndef __cplusplus
#ifdef __COMPILER_HAVE_TYPEOF
#define __ATOMIC_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __ATOMIC_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __ATOMIC_RECAST(p, y) (y)
#endif /* !... */
#endif /* !__cplusplus */

#if defined(_MSC_VER) && !defined(__cplusplus)
#define __ATOMIC_DOWNCAST(T) (T)(__UINTPTR_TYPE__)
#else /* _MSC_VER && !__cplusplus */
#define __ATOMIC_DOWNCAST(T) (T)
#endif /* !_MSC_VER || __cplusplus */

/* Define atomic memory order constants. */
#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#endif /* !__ATOMIC_RELAXED */
#ifndef __ATOMIC_CONSUME
#define __ATOMIC_CONSUME 1
#endif /* !__ATOMIC_CONSUME */
#ifndef __ATOMIC_ACQUIRE
#define __ATOMIC_ACQUIRE 2
#endif /* !__ATOMIC_ACQUIRE */
#ifndef __ATOMIC_RELEASE
#define __ATOMIC_RELEASE 3
#endif /* !__ATOMIC_RELEASE */
#ifndef __ATOMIC_ACQ_REL
#define __ATOMIC_ACQ_REL 4
#endif /* !__ATOMIC_ACQ_REL */
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST 5
#endif /* !__ATOMIC_SEQ_CST */

/* Figure out how to implement atomic operations.
 *
 * >> uintN_t __hybrid_atomic_loadN(uintN_t const *p, int order);
 * >> uintN_t __hybrid_atomic_storeN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_xchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchincN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_fetchdecN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_fetchaddN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchsubN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchandN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchxorN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchorN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchnandN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_incfetchN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_decfetchN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_addfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_subfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_andfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_xorfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_orfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_nandfetchN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_incN(uintN_t *p, int order);
 * >> void    __hybrid_atomic_decN(uintN_t *p, int order);
 * >> void    __hybrid_atomic_addN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_subN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_andN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_xorN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_orN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_nandN(uintN_t *p, uintN_t val, int order);
 * >> bool    __hybrid_atomic_cmpxchN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 * >> bool    __hybrid_atomic_cmpxch_weakN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 * >> uintN_t __hybrid_atomic_cmpxch_valN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 *
 * >> T    __hybrid_atomic_load(T const *p, int order);
 * >> T    __hybrid_atomic_store(T *p, T val, int order);
 * >> T    __hybrid_atomic_xch(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchinc(T *p, int order);
 * >> T    __hybrid_atomic_fetchdec(T *p, int order);
 * >> T    __hybrid_atomic_fetchadd(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchsub(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchand(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchxor(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchor(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchnand(T *p, T val, int order);
 * >> T    __hybrid_atomic_incfetch(T *p, int order);
 * >> T    __hybrid_atomic_decfetch(T *p, int order);
 * >> T    __hybrid_atomic_addfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_subfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_andfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_xorfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_orfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_nandfetch(T *p, T val, int order);
 * >> void __hybrid_atomic_inc(T *p, int order);
 * >> void __hybrid_atomic_dec(T *p, int order);
 * >> void __hybrid_atomic_add(T *p, T val, int order);
 * >> void __hybrid_atomic_sub(T *p, T val, int order);
 * >> void __hybrid_atomic_and(T *p, T val, int order);
 * >> void __hybrid_atomic_xor(T *p, T val, int order);
 * >> void __hybrid_atomic_or(T *p, T val, int order);
 * >> void __hybrid_atomic_nand(T *p, T val, int order);
 * >> bool __hybrid_atomic_cmpxch(T *p, T oldval, T newval, int succ, int fail);
 * >> bool __hybrid_atomic_cmpxch_weak(T *p, T oldval, T newval, int succ, int fail);
 * >> T    __hybrid_atomic_cmpxch_val(T *p, T oldval, T newval, int succ, int fail);
 * >> void __hybrid_atomic_thread_fence(int order);
 * >> void __hybrid_atomic_signal_fence(int order);
 */


/* HINT: In order to have full atomic support, we need at least an cmpxch/cmpxch_weak function */
#ifdef __CC__
#ifdef __INTELLISENSE__
__DECL_BEGIN

#define __hybrid_atomic_load8        __hybrid_atomic_load8
#define __hybrid_atomic_store8       __hybrid_atomic_store8
#define __hybrid_atomic_xch8         __hybrid_atomic_xch8
#define __hybrid_atomic_cmpxch8      __hybrid_atomic_cmpxch8
#define __hybrid_atomic_cmpxch_weak8 __hybrid_atomic_cmpxch_weak8
#define __hybrid_atomic_cmpxch_val8  __hybrid_atomic_cmpxch_val8
#define __hybrid_atomic_incfetch8    __hybrid_atomic_incfetch8
#define __hybrid_atomic_decfetch8    __hybrid_atomic_decfetch8
#define __hybrid_atomic_addfetch8    __hybrid_atomic_addfetch8
#define __hybrid_atomic_subfetch8    __hybrid_atomic_subfetch8
#define __hybrid_atomic_andfetch8    __hybrid_atomic_andfetch8
#define __hybrid_atomic_orfetch8     __hybrid_atomic_orfetch8
#define __hybrid_atomic_xorfetch8    __hybrid_atomic_xorfetch8
#define __hybrid_atomic_nandfetch8   __hybrid_atomic_nandfetch8
#define __hybrid_atomic_fetchinc8    __hybrid_atomic_fetchinc8
#define __hybrid_atomic_fetchdec8    __hybrid_atomic_fetchdec8
#define __hybrid_atomic_fetchadd8    __hybrid_atomic_fetchadd8
#define __hybrid_atomic_fetchsub8    __hybrid_atomic_fetchsub8
#define __hybrid_atomic_fetchand8    __hybrid_atomic_fetchand8
#define __hybrid_atomic_fetchor8     __hybrid_atomic_fetchor8
#define __hybrid_atomic_fetchxor8    __hybrid_atomic_fetchxor8
#define __hybrid_atomic_fetchnand8   __hybrid_atomic_fetchnand8
#define __hybrid_atomic_inc8         __hybrid_atomic_inc8
#define __hybrid_atomic_dec8         __hybrid_atomic_dec8
#define __hybrid_atomic_add8         __hybrid_atomic_add8
#define __hybrid_atomic_sub8         __hybrid_atomic_sub8
#define __hybrid_atomic_and8         __hybrid_atomic_and8
#define __hybrid_atomic_or8          __hybrid_atomic_or8
#define __hybrid_atomic_xor8         __hybrid_atomic_xor8
#define __hybrid_atomic_nand8        __hybrid_atomic_nand8
extern __UINT8_TYPE__ __hybrid_atomic_load8(__UINT8_TYPE__ const volatile *__ptr, int __order);
extern void __hybrid_atomic_store8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_xch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern bool __hybrid_atomic_cmpxch8(__UINT8_TYPE__ volatile *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail);
extern bool __hybrid_atomic_cmpxch_weak8(__UINT8_TYPE__ volatile *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail);
extern __UINT8_TYPE__ __hybrid_atomic_cmpxch_val8(__UINT8_TYPE__ volatile *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail);
extern __UINT8_TYPE__ __hybrid_atomic_incfetch8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_decfetch8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_addfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_subfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_andfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_orfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_xorfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_nandfetch8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchinc8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchdec8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchadd8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchsub8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchand8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchor8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchxor8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ __hybrid_atomic_fetchnand8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_inc8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_dec8(__UINT8_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_add8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_sub8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_and8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_or8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_xor8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);
extern void __hybrid_atomic_nand8(__UINT8_TYPE__ volatile *__ptr, __UINT8_TYPE__ __val, int __order);

#define __hybrid_atomic_load16        __hybrid_atomic_load16
#define __hybrid_atomic_store16       __hybrid_atomic_store16
#define __hybrid_atomic_xch16         __hybrid_atomic_xch16
#define __hybrid_atomic_cmpxch16      __hybrid_atomic_cmpxch16
#define __hybrid_atomic_cmpxch_weak16 __hybrid_atomic_cmpxch_weak16
#define __hybrid_atomic_cmpxch_val16  __hybrid_atomic_cmpxch_val16
#define __hybrid_atomic_incfetch16    __hybrid_atomic_incfetch16
#define __hybrid_atomic_decfetch16    __hybrid_atomic_decfetch16
#define __hybrid_atomic_addfetch16    __hybrid_atomic_addfetch16
#define __hybrid_atomic_subfetch16    __hybrid_atomic_subfetch16
#define __hybrid_atomic_andfetch16    __hybrid_atomic_andfetch16
#define __hybrid_atomic_orfetch16     __hybrid_atomic_orfetch16
#define __hybrid_atomic_xorfetch16    __hybrid_atomic_xorfetch16
#define __hybrid_atomic_nandfetch16   __hybrid_atomic_nandfetch16
#define __hybrid_atomic_fetchinc16    __hybrid_atomic_fetchinc16
#define __hybrid_atomic_fetchdec16    __hybrid_atomic_fetchdec16
#define __hybrid_atomic_fetchadd16    __hybrid_atomic_fetchadd16
#define __hybrid_atomic_fetchsub16    __hybrid_atomic_fetchsub16
#define __hybrid_atomic_fetchand16    __hybrid_atomic_fetchand16
#define __hybrid_atomic_fetchor16     __hybrid_atomic_fetchor16
#define __hybrid_atomic_fetchxor16    __hybrid_atomic_fetchxor16
#define __hybrid_atomic_fetchnand16   __hybrid_atomic_fetchnand16
#define __hybrid_atomic_inc16         __hybrid_atomic_inc16
#define __hybrid_atomic_dec16         __hybrid_atomic_dec16
#define __hybrid_atomic_add16         __hybrid_atomic_add16
#define __hybrid_atomic_sub16         __hybrid_atomic_sub16
#define __hybrid_atomic_and16         __hybrid_atomic_and16
#define __hybrid_atomic_or16          __hybrid_atomic_or16
#define __hybrid_atomic_xor16         __hybrid_atomic_xor16
#define __hybrid_atomic_nand16        __hybrid_atomic_nand16
extern __UINT16_TYPE__ __hybrid_atomic_load16(__UINT16_TYPE__ const volatile *__ptr, int __order);
extern void __hybrid_atomic_store16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_xch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern bool __hybrid_atomic_cmpxch16(__UINT16_TYPE__ volatile *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail);
extern bool __hybrid_atomic_cmpxch_weak16(__UINT16_TYPE__ volatile *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail);
extern __UINT16_TYPE__ __hybrid_atomic_cmpxch_val16(__UINT16_TYPE__ volatile *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail);
extern __UINT16_TYPE__ __hybrid_atomic_incfetch16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_decfetch16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_addfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_subfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_andfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_orfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_xorfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_nandfetch16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchinc16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchdec16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchadd16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchsub16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchand16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchor16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchxor16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ __hybrid_atomic_fetchnand16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_inc16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_dec16(__UINT16_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_add16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_sub16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_and16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_or16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_xor16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);
extern void __hybrid_atomic_nand16(__UINT16_TYPE__ volatile *__ptr, __UINT16_TYPE__ __val, int __order);

#define __hybrid_atomic_load32        __hybrid_atomic_load32
#define __hybrid_atomic_store32       __hybrid_atomic_store32
#define __hybrid_atomic_xch32         __hybrid_atomic_xch32
#define __hybrid_atomic_cmpxch32      __hybrid_atomic_cmpxch32
#define __hybrid_atomic_cmpxch_weak32 __hybrid_atomic_cmpxch_weak32
#define __hybrid_atomic_cmpxch_val32  __hybrid_atomic_cmpxch_val32
#define __hybrid_atomic_incfetch32    __hybrid_atomic_incfetch32
#define __hybrid_atomic_decfetch32    __hybrid_atomic_decfetch32
#define __hybrid_atomic_addfetch32    __hybrid_atomic_addfetch32
#define __hybrid_atomic_subfetch32    __hybrid_atomic_subfetch32
#define __hybrid_atomic_andfetch32    __hybrid_atomic_andfetch32
#define __hybrid_atomic_orfetch32     __hybrid_atomic_orfetch32
#define __hybrid_atomic_xorfetch32    __hybrid_atomic_xorfetch32
#define __hybrid_atomic_nandfetch32   __hybrid_atomic_nandfetch32
#define __hybrid_atomic_fetchinc32    __hybrid_atomic_fetchinc32
#define __hybrid_atomic_fetchdec32    __hybrid_atomic_fetchdec32
#define __hybrid_atomic_fetchadd32    __hybrid_atomic_fetchadd32
#define __hybrid_atomic_fetchsub32    __hybrid_atomic_fetchsub32
#define __hybrid_atomic_fetchand32    __hybrid_atomic_fetchand32
#define __hybrid_atomic_fetchor32     __hybrid_atomic_fetchor32
#define __hybrid_atomic_fetchxor32    __hybrid_atomic_fetchxor32
#define __hybrid_atomic_fetchnand32   __hybrid_atomic_fetchnand32
#define __hybrid_atomic_inc32         __hybrid_atomic_inc32
#define __hybrid_atomic_dec32         __hybrid_atomic_dec32
#define __hybrid_atomic_add32         __hybrid_atomic_add32
#define __hybrid_atomic_sub32         __hybrid_atomic_sub32
#define __hybrid_atomic_and32         __hybrid_atomic_and32
#define __hybrid_atomic_or32          __hybrid_atomic_or32
#define __hybrid_atomic_xor32         __hybrid_atomic_xor32
#define __hybrid_atomic_nand32        __hybrid_atomic_nand32
extern __UINT32_TYPE__ __hybrid_atomic_load32(__UINT32_TYPE__ const volatile *__ptr, int __order);
extern void __hybrid_atomic_store32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_xch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern bool __hybrid_atomic_cmpxch32(__UINT32_TYPE__ volatile *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail);
extern bool __hybrid_atomic_cmpxch_weak32(__UINT32_TYPE__ volatile *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail);
extern __UINT32_TYPE__ __hybrid_atomic_cmpxch_val32(__UINT32_TYPE__ volatile *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail);
extern __UINT32_TYPE__ __hybrid_atomic_incfetch32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_decfetch32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_addfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_subfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_andfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_orfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_xorfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_nandfetch32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchinc32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchdec32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchadd32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchsub32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchand32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchor32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchxor32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ __hybrid_atomic_fetchnand32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_inc32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_dec32(__UINT32_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_add32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_sub32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_and32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_or32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_xor32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);
extern void __hybrid_atomic_nand32(__UINT32_TYPE__ volatile *__ptr, __UINT32_TYPE__ __val, int __order);

#ifdef __UINT64_TYPE__
#define __hybrid_atomic_load64        __hybrid_atomic_load64
#define __hybrid_atomic_store64       __hybrid_atomic_store64
#define __hybrid_atomic_xch64         __hybrid_atomic_xch64
#define __hybrid_atomic_cmpxch64      __hybrid_atomic_cmpxch64
#define __hybrid_atomic_cmpxch_weak64 __hybrid_atomic_cmpxch_weak64
#define __hybrid_atomic_cmpxch_val64  __hybrid_atomic_cmpxch_val64
#define __hybrid_atomic_incfetch64    __hybrid_atomic_incfetch64
#define __hybrid_atomic_decfetch64    __hybrid_atomic_decfetch64
#define __hybrid_atomic_addfetch64    __hybrid_atomic_addfetch64
#define __hybrid_atomic_subfetch64    __hybrid_atomic_subfetch64
#define __hybrid_atomic_andfetch64    __hybrid_atomic_andfetch64
#define __hybrid_atomic_orfetch64     __hybrid_atomic_orfetch64
#define __hybrid_atomic_xorfetch64    __hybrid_atomic_xorfetch64
#define __hybrid_atomic_nandfetch64   __hybrid_atomic_nandfetch64
#define __hybrid_atomic_fetchinc64    __hybrid_atomic_fetchinc64
#define __hybrid_atomic_fetchdec64    __hybrid_atomic_fetchdec64
#define __hybrid_atomic_fetchadd64    __hybrid_atomic_fetchadd64
#define __hybrid_atomic_fetchsub64    __hybrid_atomic_fetchsub64
#define __hybrid_atomic_fetchand64    __hybrid_atomic_fetchand64
#define __hybrid_atomic_fetchor64     __hybrid_atomic_fetchor64
#define __hybrid_atomic_fetchxor64    __hybrid_atomic_fetchxor64
#define __hybrid_atomic_fetchnand64   __hybrid_atomic_fetchnand64
#define __hybrid_atomic_inc64         __hybrid_atomic_inc64
#define __hybrid_atomic_dec64         __hybrid_atomic_dec64
#define __hybrid_atomic_add64         __hybrid_atomic_add64
#define __hybrid_atomic_sub64         __hybrid_atomic_sub64
#define __hybrid_atomic_and64         __hybrid_atomic_and64
#define __hybrid_atomic_or64          __hybrid_atomic_or64
#define __hybrid_atomic_xor64         __hybrid_atomic_xor64
#define __hybrid_atomic_nand64        __hybrid_atomic_nand64
extern __UINT64_TYPE__ __hybrid_atomic_load64(__UINT64_TYPE__ const volatile *__ptr, int __order);
extern void __hybrid_atomic_store64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_xch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern bool __hybrid_atomic_cmpxch64(__UINT64_TYPE__ volatile *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail);
extern bool __hybrid_atomic_cmpxch_weak64(__UINT64_TYPE__ volatile *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail);
extern __UINT64_TYPE__ __hybrid_atomic_cmpxch_val64(__UINT64_TYPE__ volatile *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail);
extern __UINT64_TYPE__ __hybrid_atomic_incfetch64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_decfetch64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_addfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_subfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_andfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_orfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_xorfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_nandfetch64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchinc64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchdec64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchadd64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchsub64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchand64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchor64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchxor64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ __hybrid_atomic_fetchnand64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_inc64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_dec64(__UINT64_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_add64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_sub64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_and64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_or64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_xor64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
extern void __hybrid_atomic_nand64(__UINT64_TYPE__ volatile *__ptr, __UINT64_TYPE__ __val, int __order);
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
#define __hybrid_atomic_load128        __hybrid_atomic_load128
#define __hybrid_atomic_store128       __hybrid_atomic_store128
#define __hybrid_atomic_xch128         __hybrid_atomic_xch128
#define __hybrid_atomic_cmpxch128      __hybrid_atomic_cmpxch128
#define __hybrid_atomic_cmpxch_weak128 __hybrid_atomic_cmpxch_weak128
#define __hybrid_atomic_cmpxch_val128  __hybrid_atomic_cmpxch_val128
#define __hybrid_atomic_incfetch128    __hybrid_atomic_incfetch128
#define __hybrid_atomic_decfetch128    __hybrid_atomic_decfetch128
#define __hybrid_atomic_addfetch128    __hybrid_atomic_addfetch128
#define __hybrid_atomic_subfetch128    __hybrid_atomic_subfetch128
#define __hybrid_atomic_andfetch128    __hybrid_atomic_andfetch128
#define __hybrid_atomic_orfetch128     __hybrid_atomic_orfetch128
#define __hybrid_atomic_xorfetch128    __hybrid_atomic_xorfetch128
#define __hybrid_atomic_nandfetch128   __hybrid_atomic_nandfetch128
#define __hybrid_atomic_fetchinc128    __hybrid_atomic_fetchinc128
#define __hybrid_atomic_fetchdec128    __hybrid_atomic_fetchdec128
#define __hybrid_atomic_fetchadd128    __hybrid_atomic_fetchadd128
#define __hybrid_atomic_fetchsub128    __hybrid_atomic_fetchsub128
#define __hybrid_atomic_fetchand128    __hybrid_atomic_fetchand128
#define __hybrid_atomic_fetchor128     __hybrid_atomic_fetchor128
#define __hybrid_atomic_fetchxor128    __hybrid_atomic_fetchxor128
#define __hybrid_atomic_fetchnand128   __hybrid_atomic_fetchnand128
#define __hybrid_atomic_inc128         __hybrid_atomic_inc128
#define __hybrid_atomic_dec128         __hybrid_atomic_dec128
#define __hybrid_atomic_add128         __hybrid_atomic_add128
#define __hybrid_atomic_sub128         __hybrid_atomic_sub128
#define __hybrid_atomic_and128         __hybrid_atomic_and128
#define __hybrid_atomic_or128          __hybrid_atomic_or128
#define __hybrid_atomic_xor128         __hybrid_atomic_xor128
#define __hybrid_atomic_nand128        __hybrid_atomic_nand128
extern __UINT128_TYPE__ __hybrid_atomic_load128(__UINT128_TYPE__ const volatile *__ptr, int __order);
extern void __hybrid_atomic_store128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_xch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern bool __hybrid_atomic_cmpxch128(__UINT128_TYPE__ volatile *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail);
extern bool __hybrid_atomic_cmpxch_weak128(__UINT128_TYPE__ volatile *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail);
extern __UINT128_TYPE__ __hybrid_atomic_cmpxch_val128(__UINT128_TYPE__ volatile *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail);
extern __UINT128_TYPE__ __hybrid_atomic_incfetch128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_decfetch128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_addfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_subfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_andfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_orfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_xorfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_nandfetch128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchinc128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchdec128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchadd128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchsub128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchand128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchor128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchxor128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ __hybrid_atomic_fetchnand128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_inc128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_dec128(__UINT128_TYPE__ volatile *__ptr, int __order);
extern void __hybrid_atomic_add128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_sub128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_and128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_or128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_xor128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
extern void __hybrid_atomic_nand128(__UINT128_TYPE__ volatile *__ptr, __UINT128_TYPE__ __val, int __order);
#endif /* __UINT128_TYPE__ */

#define __hybrid_atomic_thread_fence __hybrid_atomic_thread_fence
#define __hybrid_atomic_signal_fence __hybrid_atomic_signal_fence
void __hybrid_atomic_thread_fence(int __order);
void __hybrid_atomic_signal_fence(int __order);
__DECL_END

#ifdef __cplusplus
#define __hybrid_atomic_load        __hybrid_atomic_load
#define __hybrid_atomic_store       __hybrid_atomic_store
#define __hybrid_atomic_xch         __hybrid_atomic_xch
#define __hybrid_atomic_cmpxch      __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch_weak __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_val  __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_incfetch    __hybrid_atomic_incfetch
#define __hybrid_atomic_decfetch    __hybrid_atomic_decfetch
#define __hybrid_atomic_addfetch    __hybrid_atomic_addfetch
#define __hybrid_atomic_subfetch    __hybrid_atomic_subfetch
#define __hybrid_atomic_andfetch    __hybrid_atomic_andfetch
#define __hybrid_atomic_orfetch     __hybrid_atomic_orfetch
#define __hybrid_atomic_xorfetch    __hybrid_atomic_xorfetch
#define __hybrid_atomic_nandfetch   __hybrid_atomic_nandfetch
#define __hybrid_atomic_fetchinc    __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchdec    __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchadd    __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchsub    __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchand    __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchor     __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchxor    __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchnand   __hybrid_atomic_fetchnand
#define __hybrid_atomic_inc         __hybrid_atomic_inc
#define __hybrid_atomic_dec         __hybrid_atomic_dec
#define __hybrid_atomic_add         __hybrid_atomic_add
#define __hybrid_atomic_sub         __hybrid_atomic_sub
#define __hybrid_atomic_and         __hybrid_atomic_and
#define __hybrid_atomic_or          __hybrid_atomic_or
#define __hybrid_atomic_xor         __hybrid_atomic_xor
#define __hybrid_atomic_nand        __hybrid_atomic_nand
#define __hybrid_atomic_lockfree    __hybrid_atomic_lockfree
extern "C++" {
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, T>::__type __hybrid_atomic_load(T const volatile *__ptr, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_store(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_xch(T volatile *__ptr, S __val, int __order);
template<class T, class S, class U> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value && ::__intern::____INTELLISENSE_isarith<U>::__value, bool>::__type __hybrid_atomic_cmpxch(T volatile *__p, S __oldval, U __newval, int __succ, int __fail);
template<class T, class S, class U> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value && ::__intern::____INTELLISENSE_isarith<U>::__value, bool>::__type __hybrid_atomic_cmpxch_weak(T volatile *__p, S __oldval, U __newval, int __succ, int __fail);
template<class T, class S, class U> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value && ::__intern::____INTELLISENSE_isarith<U>::__value, T>::__type __hybrid_atomic_cmpxch_val(T volatile *__p, S __oldval, U __newval, int __succ, int __fail);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, T>::__type __hybrid_atomic_incfetch(T volatile *__ptr, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, T>::__type __hybrid_atomic_decfetch(T volatile *__ptr, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_addfetch(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_subfetch(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_andfetch(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_orfetch(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_xorfetch(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_nandfetch(T volatile *__ptr, S __val, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, T>::__type __hybrid_atomic_fetchinc(T volatile *__ptr, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, T>::__type __hybrid_atomic_fetchdec(T volatile *__ptr, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchadd(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchsub(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchand(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchor(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchxor(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, T>::__type __hybrid_atomic_fetchnand(T volatile *__ptr, S __val, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, void>::__type __hybrid_atomic_inc(T volatile *__ptr, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, void>::__type __hybrid_atomic_dec(T volatile *__ptr, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_add(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_sub(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_and(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_or(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_xor(T volatile *__ptr, S __val, int __order);
template<class T, class S> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value && ::__intern::____INTELLISENSE_isarith<S>::__value, void>::__type __hybrid_atomic_nand(T volatile *__ptr, S __val, int __order);
template<class T> typename ::__intern::____INTELLISENSE_enableif< ::__intern::____INTELLISENSE_isarith<T>::__value, bool>::__type __hybrid_atomic_lockfree(T volatile *__ptr);
} /* extern "C++" */
#else /* __cplusplus */
#include "__atomic-complete.h"
#endif /* !__cplusplus */
#elif defined(__HYBRID_ATOMIC_USE_LIBATOMIC)
#include "__atomic-libatomic.h" /* libatomic */
/**/
#include "__atomic-complete.h"
#elif ((defined(__GNUC__) && __GCC_VERSION_NUM >= 40700) || \
       defined(____INTELLISENSE_STDINC_COMMON_H) || defined(__clang__))
/* __atomic_xxx() */
#define __hybrid_atomic_load(p, order)                             __atomic_load_n(p, order)
#define __hybrid_atomic_store(p, val, order)                       __atomic_store_n(p, val, order)
#define __hybrid_atomic_xch(p, val, order)                         __atomic_exchange_n(p, val, order)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)      __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __atomic_compare_exchange_n(p, &__oldv, newval, 0, succ, fail); })
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __atomic_compare_exchange_n(p, &__oldv, newval, 1, succ, fail); })
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail)  __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __atomic_compare_exchange_n(p, &__oldv, newval, 0, succ, fail); __XRETURN __oldv; })
#define __hybrid_atomic_incfetch(p, order)                         __atomic_add_fetch(p, 1, order)
#define __hybrid_atomic_decfetch(p, order)                         __atomic_sub_fetch(p, 1, order)
#define __hybrid_atomic_addfetch(p, val, order)                    __atomic_add_fetch(p, val, order)
#define __hybrid_atomic_subfetch(p, val, order)                    __atomic_sub_fetch(p, val, order)
#define __hybrid_atomic_andfetch(p, val, order)                    __atomic_and_fetch(p, val, order)
#define __hybrid_atomic_orfetch(p, val, order)                     __atomic_or_fetch(p, val, order)
#define __hybrid_atomic_xorfetch(p, val, order)                    __atomic_xor_fetch(p, val, order)
#define __hybrid_atomic_nandfetch(p, val, order)                   __atomic_nand_fetch(p, val, order)
#define __hybrid_atomic_fetchinc(p, order)                         __atomic_fetch_add(p, 1, order)
#define __hybrid_atomic_fetchdec(p, order)                         __atomic_fetch_sub(p, 1, order)
#define __hybrid_atomic_fetchadd(p, val, order)                    __atomic_fetch_add(p, val, order)
#define __hybrid_atomic_fetchsub(p, val, order)                    __atomic_fetch_sub(p, val, order)
#define __hybrid_atomic_fetchand(p, val, order)                    __atomic_fetch_and(p, val, order)
#define __hybrid_atomic_fetchor(p, val, order)                     __atomic_fetch_or(p, val, order)
#define __hybrid_atomic_fetchxor(p, val, order)                    __atomic_fetch_xor(p, val, order)
#define __hybrid_atomic_fetchnand(p, val, order)                   __atomic_fetch_nand(p, val, order)
#define __hybrid_atomic_thread_fence(order)                        __atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __atomic_signal_fence(order)
#define __hybrid_atomic_inc(p, order)                              (void)__hybrid_atomic_fetchinc(p, order)
#define __hybrid_atomic_dec(p, order)                              (void)__hybrid_atomic_fetchdec(p, order)
#define __hybrid_atomic_add(p, val, order)                         (void)__hybrid_atomic_fetchadd(p, val, order)
#define __hybrid_atomic_sub(p, val, order)                         (void)__hybrid_atomic_fetchsub(p, val, order)
#define __hybrid_atomic_and(p, val, order)                         (void)__hybrid_atomic_fetchand(p, val, order)
#define __hybrid_atomic_or(p, val, order)                          (void)__hybrid_atomic_fetchor(p, val, order)
#define __hybrid_atomic_xor(p, val, order)                         (void)__hybrid_atomic_fetchxor(p, val, order)
#define __hybrid_atomic_nand(p, val, order)                        (void)__hybrid_atomic_fetchnand(p, val, order)
#define __hybrid_atomic_lockfree(p)                                __atomic_is_lock_free(sizeof(*(p)), p)

#define __hybrid_atomic_load8(p, order)                             __hybrid_atomic_load((__UINT8_TYPE__ const *)(p), order)
#define __hybrid_atomic_store8(p, val, order)                       __hybrid_atomic_store((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch8(p, val, order)                         __hybrid_atomic_xch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch8(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak8(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch8(p, order)                         __hybrid_atomic_incfetch((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch8(p, order)                         __hybrid_atomic_decfetch((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch8(p, val, order)                    __hybrid_atomic_addfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch8(p, val, order)                    __hybrid_atomic_subfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch8(p, val, order)                    __hybrid_atomic_andfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch8(p, val, order)                     __hybrid_atomic_orfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch8(p, val, order)                    __hybrid_atomic_xorfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch8(p, val, order)                   __hybrid_atomic_nandfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc8(p, order)                         __hybrid_atomic_fetchinc((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec8(p, order)                         __hybrid_atomic_fetchdec((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd8(p, val, order)                    __hybrid_atomic_fetchadd((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub8(p, val, order)                    __hybrid_atomic_fetchsub((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand8(p, val, order)                    __hybrid_atomic_fetchand((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor8(p, val, order)                     __hybrid_atomic_fetchor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor8(p, val, order)                    __hybrid_atomic_fetchxor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand8(p, val, order)                   __hybrid_atomic_fetchnand((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc8(p, order)                              __hybrid_atomic_inc((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_dec8(p, order)                              __hybrid_atomic_dec((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_add8(p, val, order)                         __hybrid_atomic_add((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub8(p, val, order)                         __hybrid_atomic_sub((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and8(p, val, order)                         __hybrid_atomic_and((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or8(p, val, order)                          __hybrid_atomic_or((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor8(p, val, order)                         __hybrid_atomic_xor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand8(p, val, order)                        __hybrid_atomic_nand((__UINT8_TYPE__ *)(p), val, order)

#define __hybrid_atomic_load16(p, order)                             __hybrid_atomic_load((__UINT16_TYPE__ const *)(p), order)
#define __hybrid_atomic_store16(p, val, order)                       __hybrid_atomic_store((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch16(p, val, order)                         __hybrid_atomic_xch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch16(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak16(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch16(p, order)                         __hybrid_atomic_incfetch((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch16(p, order)                         __hybrid_atomic_decfetch((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch16(p, val, order)                    __hybrid_atomic_addfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch16(p, val, order)                    __hybrid_atomic_subfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch16(p, val, order)                    __hybrid_atomic_andfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch16(p, val, order)                     __hybrid_atomic_orfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch16(p, val, order)                    __hybrid_atomic_xorfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch16(p, val, order)                   __hybrid_atomic_nandfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc16(p, order)                         __hybrid_atomic_fetchinc((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec16(p, order)                         __hybrid_atomic_fetchdec((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd16(p, val, order)                    __hybrid_atomic_fetchadd((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub16(p, val, order)                    __hybrid_atomic_fetchsub((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand16(p, val, order)                    __hybrid_atomic_fetchand((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor16(p, val, order)                     __hybrid_atomic_fetchor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor16(p, val, order)                    __hybrid_atomic_fetchxor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand16(p, val, order)                   __hybrid_atomic_fetchnand((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc16(p, order)                              __hybrid_atomic_inc((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_dec16(p, order)                              __hybrid_atomic_dec((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_add16(p, val, order)                         __hybrid_atomic_add((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub16(p, val, order)                         __hybrid_atomic_sub((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and16(p, val, order)                         __hybrid_atomic_and((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or16(p, val, order)                          __hybrid_atomic_or((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor16(p, val, order)                         __hybrid_atomic_xor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand16(p, val, order)                        __hybrid_atomic_nand((__UINT16_TYPE__ *)(p), val, order)

#define __hybrid_atomic_load32(p, order)                             __hybrid_atomic_load((__UINT32_TYPE__ const *)(p), order)
#define __hybrid_atomic_store32(p, val, order)                       __hybrid_atomic_store((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch32(p, val, order)                         __hybrid_atomic_xch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch32(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak32(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch32(p, order)                         __hybrid_atomic_incfetch((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch32(p, order)                         __hybrid_atomic_decfetch((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch32(p, val, order)                    __hybrid_atomic_addfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch32(p, val, order)                    __hybrid_atomic_subfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch32(p, val, order)                    __hybrid_atomic_andfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch32(p, val, order)                     __hybrid_atomic_orfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch32(p, val, order)                    __hybrid_atomic_xorfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch32(p, val, order)                   __hybrid_atomic_nandfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc32(p, order)                         __hybrid_atomic_fetchinc((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec32(p, order)                         __hybrid_atomic_fetchdec((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd32(p, val, order)                    __hybrid_atomic_fetchadd((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub32(p, val, order)                    __hybrid_atomic_fetchsub((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand32(p, val, order)                    __hybrid_atomic_fetchand((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor32(p, val, order)                     __hybrid_atomic_fetchor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor32(p, val, order)                    __hybrid_atomic_fetchxor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand32(p, val, order)                   __hybrid_atomic_fetchnand((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc32(p, order)                              __hybrid_atomic_inc((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_dec32(p, order)                              __hybrid_atomic_dec((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_add32(p, val, order)                         __hybrid_atomic_add((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub32(p, val, order)                         __hybrid_atomic_sub((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and32(p, val, order)                         __hybrid_atomic_and((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or32(p, val, order)                          __hybrid_atomic_or((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor32(p, val, order)                         __hybrid_atomic_xor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand32(p, val, order)                        __hybrid_atomic_nand((__UINT32_TYPE__ *)(p), val, order)

#ifdef __UINT64_TYPE__
#define __hybrid_atomic_load64(p, order)                             __hybrid_atomic_load((__UINT64_TYPE__ const *)(p), order)
#define __hybrid_atomic_store64(p, val, order)                       __hybrid_atomic_store((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch64(p, val, order)                         __hybrid_atomic_xch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch64(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak64(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch64(p, order)                         __hybrid_atomic_incfetch((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch64(p, order)                         __hybrid_atomic_decfetch((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch64(p, val, order)                    __hybrid_atomic_addfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch64(p, val, order)                    __hybrid_atomic_subfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch64(p, val, order)                    __hybrid_atomic_andfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch64(p, val, order)                     __hybrid_atomic_orfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch64(p, val, order)                    __hybrid_atomic_xorfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch64(p, val, order)                   __hybrid_atomic_nandfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc64(p, order)                         __hybrid_atomic_fetchinc((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec64(p, order)                         __hybrid_atomic_fetchdec((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd64(p, val, order)                    __hybrid_atomic_fetchadd((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub64(p, val, order)                    __hybrid_atomic_fetchsub((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand64(p, val, order)                    __hybrid_atomic_fetchand((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor64(p, val, order)                     __hybrid_atomic_fetchor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor64(p, val, order)                    __hybrid_atomic_fetchxor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand64(p, val, order)                   __hybrid_atomic_fetchnand((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc64(p, order)                              __hybrid_atomic_inc((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_dec64(p, order)                              __hybrid_atomic_dec((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_add64(p, val, order)                         __hybrid_atomic_add((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub64(p, val, order)                         __hybrid_atomic_sub((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and64(p, val, order)                         __hybrid_atomic_and((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or64(p, val, order)                          __hybrid_atomic_or((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor64(p, val, order)                         __hybrid_atomic_xor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand64(p, val, order)                        __hybrid_atomic_nand((__UINT64_TYPE__ *)(p), val, order)
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
#define __hybrid_atomic_load128(p, order)                             __hybrid_atomic_load((__UINT128_TYPE__ const *)(p), order)
#define __hybrid_atomic_store128(p, val, order)                       __hybrid_atomic_store((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch128(p, val, order)                         __hybrid_atomic_xch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch128(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak128(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val128(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch128(p, order)                         __hybrid_atomic_incfetch((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch128(p, order)                         __hybrid_atomic_decfetch((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch128(p, val, order)                    __hybrid_atomic_addfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch128(p, val, order)                    __hybrid_atomic_subfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch128(p, val, order)                    __hybrid_atomic_andfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch128(p, val, order)                     __hybrid_atomic_orfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch128(p, val, order)                    __hybrid_atomic_xorfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch128(p, val, order)                   __hybrid_atomic_nandfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc128(p, order)                         __hybrid_atomic_fetchinc((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec128(p, order)                         __hybrid_atomic_fetchdec((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd128(p, val, order)                    __hybrid_atomic_fetchadd((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub128(p, val, order)                    __hybrid_atomic_fetchsub((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand128(p, val, order)                    __hybrid_atomic_fetchand((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor128(p, val, order)                     __hybrid_atomic_fetchor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor128(p, val, order)                    __hybrid_atomic_fetchxor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand128(p, val, order)                   __hybrid_atomic_fetchnand((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc128(p, order)                              __hybrid_atomic_inc((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_dec128(p, order)                              __hybrid_atomic_dec((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_add128(p, val, order)                         __hybrid_atomic_add((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub128(p, val, order)                         __hybrid_atomic_sub((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and128(p, val, order)                         __hybrid_atomic_and((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or128(p, val, order)                          __hybrid_atomic_or((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor128(p, val, order)                         __hybrid_atomic_xor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand128(p, val, order)                        __hybrid_atomic_nand((__UINT128_TYPE__ *)(p), val, order)
#endif /* __UINT128_TYPE__ */
#elif __has_extension(c_atomic) || __has_extension(cxx_atomic) /* clang */
/* __c11_atomic_xxx() */
#define __hybrid_atomic_load(p, order)                             __c11_atomic_load(p, order)
#define __hybrid_atomic_store(p, val, order)                       __c11_atomic_store(p, val, order)
#define __hybrid_atomic_xch(p, val, order)                         __c11_atomic_exchange(p, val, order)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)      __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __c11_atomic_compare_exchange_strong(p, &__oldv, newval, succ, fail); })
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __c11_atomic_compare_exchange_weak(p, &__oldv, newval, succ, fail); })
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail)  __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __c11_atomic_compare_exchange_strong(p, &__oldv, newval, succ, fail); __XRETURN __oldv; })
#define __hybrid_atomic_fetchinc(p, order)                         __c11_atomic_fetch_add(p, 1, order)
#define __hybrid_atomic_fetchdec(p, order)                         __c11_atomic_fetch_sub(p, 1, order)
#define __hybrid_atomic_fetchadd(p, val, order)                    __c11_atomic_fetch_add(p, val, order)
#define __hybrid_atomic_fetchsub(p, val, order)                    __c11_atomic_fetch_sub(p, val, order)
#define __hybrid_atomic_fetchand(p, val, order)                    __c11_atomic_fetch_and(p, val, order)
#define __hybrid_atomic_fetchor(p, val, order)                     __c11_atomic_fetch_or(p, val, order)
#define __hybrid_atomic_fetchxor(p, val, order)                    __c11_atomic_fetch_xor(p, val, order)
#define __hybrid_atomic_incfetch(p, order)                         (__hybrid_atomic_fetchinc(p, order) + 1)
#define __hybrid_atomic_decfetch(p, order)                         (__hybrid_atomic_fetchdec(p, order) - 1)
#define __hybrid_atomic_addfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchadd(p, __val, order) + __val; })
#define __hybrid_atomic_subfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchsub(p, __val, order) - __val; })
#define __hybrid_atomic_andfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchand(p, __val, order) & __val; })
#define __hybrid_atomic_orfetch(p, val, order)                     __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchor(p, __val, order) | __val; })
#define __hybrid_atomic_xorfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchxor(p, __val, order) ^ __val; })
#define __hybrid_atomic_inc(p, order)                              (void)__hybrid_atomic_fetchinc(p, order)
#define __hybrid_atomic_dec(p, order)                              (void)__hybrid_atomic_fetchdec(p, order)
#define __hybrid_atomic_add(p, val, order)                         (void)__hybrid_atomic_fetchadd(p, val, order)
#define __hybrid_atomic_sub(p, val, order)                         (void)__hybrid_atomic_fetchsub(p, val, order)
#define __hybrid_atomic_and(p, val, order)                         (void)__hybrid_atomic_fetchand(p, val, order)
#define __hybrid_atomic_or(p, val, order)                          (void)__hybrid_atomic_fetchor(p, val, order)
#define __hybrid_atomic_xor(p, val, order)                         (void)__hybrid_atomic_fetchxor(p, val, order)
#define __hybrid_atomic_thread_fence(order)                        __c11_atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __c11_atomic_signal_fence(order)
#define __hybrid_atomic_lockfree(p)                                __atomic_is_lock_free(sizeof(*(p)), p)

#define __hybrid_atomic_load8(p, order)                             __hybrid_atomic_load((__UINT8_TYPE__ const *)(p), order)
#define __hybrid_atomic_store8(p, val, order)                       __hybrid_atomic_store((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch8(p, val, order)                         __hybrid_atomic_xch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch8(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak8(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT8_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch8(p, order)                         __hybrid_atomic_incfetch((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch8(p, order)                         __hybrid_atomic_decfetch((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch8(p, val, order)                    __hybrid_atomic_addfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch8(p, val, order)                    __hybrid_atomic_subfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch8(p, val, order)                    __hybrid_atomic_andfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch8(p, val, order)                     __hybrid_atomic_orfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch8(p, val, order)                    __hybrid_atomic_xorfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch8(p, val, order)                   __hybrid_atomic_nandfetch((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc8(p, order)                         __hybrid_atomic_fetchinc((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec8(p, order)                         __hybrid_atomic_fetchdec((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd8(p, val, order)                    __hybrid_atomic_fetchadd((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub8(p, val, order)                    __hybrid_atomic_fetchsub((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand8(p, val, order)                    __hybrid_atomic_fetchand((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor8(p, val, order)                     __hybrid_atomic_fetchor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor8(p, val, order)                    __hybrid_atomic_fetchxor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand8(p, val, order)                   __hybrid_atomic_fetchnand((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc8(p, order)                              __hybrid_atomic_inc((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_dec8(p, order)                              __hybrid_atomic_dec((__UINT8_TYPE__ *)(p), order)
#define __hybrid_atomic_add8(p, val, order)                         __hybrid_atomic_add((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub8(p, val, order)                         __hybrid_atomic_sub((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and8(p, val, order)                         __hybrid_atomic_and((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or8(p, val, order)                          __hybrid_atomic_or((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor8(p, val, order)                         __hybrid_atomic_xor((__UINT8_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand8(p, val, order)                        __hybrid_atomic_nand((__UINT8_TYPE__ *)(p), val, order)

#define __hybrid_atomic_load16(p, order)                             __hybrid_atomic_load((__UINT16_TYPE__ const *)(p), order)
#define __hybrid_atomic_store16(p, val, order)                       __hybrid_atomic_store((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch16(p, val, order)                         __hybrid_atomic_xch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch16(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak16(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT16_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch16(p, order)                         __hybrid_atomic_incfetch((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch16(p, order)                         __hybrid_atomic_decfetch((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch16(p, val, order)                    __hybrid_atomic_addfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch16(p, val, order)                    __hybrid_atomic_subfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch16(p, val, order)                    __hybrid_atomic_andfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch16(p, val, order)                     __hybrid_atomic_orfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch16(p, val, order)                    __hybrid_atomic_xorfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch16(p, val, order)                   __hybrid_atomic_nandfetch((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc16(p, order)                         __hybrid_atomic_fetchinc((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec16(p, order)                         __hybrid_atomic_fetchdec((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd16(p, val, order)                    __hybrid_atomic_fetchadd((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub16(p, val, order)                    __hybrid_atomic_fetchsub((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand16(p, val, order)                    __hybrid_atomic_fetchand((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor16(p, val, order)                     __hybrid_atomic_fetchor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor16(p, val, order)                    __hybrid_atomic_fetchxor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand16(p, val, order)                   __hybrid_atomic_fetchnand((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc16(p, order)                              __hybrid_atomic_inc((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_dec16(p, order)                              __hybrid_atomic_dec((__UINT16_TYPE__ *)(p), order)
#define __hybrid_atomic_add16(p, val, order)                         __hybrid_atomic_add((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub16(p, val, order)                         __hybrid_atomic_sub((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and16(p, val, order)                         __hybrid_atomic_and((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or16(p, val, order)                          __hybrid_atomic_or((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor16(p, val, order)                         __hybrid_atomic_xor((__UINT16_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand16(p, val, order)                        __hybrid_atomic_nand((__UINT16_TYPE__ *)(p), val, order)

#define __hybrid_atomic_load32(p, order)                             __hybrid_atomic_load((__UINT32_TYPE__ const *)(p), order)
#define __hybrid_atomic_store32(p, val, order)                       __hybrid_atomic_store((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch32(p, val, order)                         __hybrid_atomic_xch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch32(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak32(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT32_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch32(p, order)                         __hybrid_atomic_incfetch((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch32(p, order)                         __hybrid_atomic_decfetch((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch32(p, val, order)                    __hybrid_atomic_addfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch32(p, val, order)                    __hybrid_atomic_subfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch32(p, val, order)                    __hybrid_atomic_andfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch32(p, val, order)                     __hybrid_atomic_orfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch32(p, val, order)                    __hybrid_atomic_xorfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch32(p, val, order)                   __hybrid_atomic_nandfetch((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc32(p, order)                         __hybrid_atomic_fetchinc((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec32(p, order)                         __hybrid_atomic_fetchdec((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd32(p, val, order)                    __hybrid_atomic_fetchadd((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub32(p, val, order)                    __hybrid_atomic_fetchsub((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand32(p, val, order)                    __hybrid_atomic_fetchand((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor32(p, val, order)                     __hybrid_atomic_fetchor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor32(p, val, order)                    __hybrid_atomic_fetchxor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand32(p, val, order)                   __hybrid_atomic_fetchnand((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc32(p, order)                              __hybrid_atomic_inc((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_dec32(p, order)                              __hybrid_atomic_dec((__UINT32_TYPE__ *)(p), order)
#define __hybrid_atomic_add32(p, val, order)                         __hybrid_atomic_add((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub32(p, val, order)                         __hybrid_atomic_sub((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and32(p, val, order)                         __hybrid_atomic_and((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or32(p, val, order)                          __hybrid_atomic_or((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor32(p, val, order)                         __hybrid_atomic_xor((__UINT32_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand32(p, val, order)                        __hybrid_atomic_nand((__UINT32_TYPE__ *)(p), val, order)

#ifdef __UINT64_TYPE__
#define __hybrid_atomic_load64(p, order)                             __hybrid_atomic_load((__UINT64_TYPE__ const *)(p), order)
#define __hybrid_atomic_store64(p, val, order)                       __hybrid_atomic_store((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch64(p, val, order)                         __hybrid_atomic_xch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch64(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak64(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT64_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch64(p, order)                         __hybrid_atomic_incfetch((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch64(p, order)                         __hybrid_atomic_decfetch((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch64(p, val, order)                    __hybrid_atomic_addfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch64(p, val, order)                    __hybrid_atomic_subfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch64(p, val, order)                    __hybrid_atomic_andfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch64(p, val, order)                     __hybrid_atomic_orfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch64(p, val, order)                    __hybrid_atomic_xorfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch64(p, val, order)                   __hybrid_atomic_nandfetch((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc64(p, order)                         __hybrid_atomic_fetchinc((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec64(p, order)                         __hybrid_atomic_fetchdec((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd64(p, val, order)                    __hybrid_atomic_fetchadd((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub64(p, val, order)                    __hybrid_atomic_fetchsub((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand64(p, val, order)                    __hybrid_atomic_fetchand((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor64(p, val, order)                     __hybrid_atomic_fetchor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor64(p, val, order)                    __hybrid_atomic_fetchxor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand64(p, val, order)                   __hybrid_atomic_fetchnand((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc64(p, order)                              __hybrid_atomic_inc((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_dec64(p, order)                              __hybrid_atomic_dec((__UINT64_TYPE__ *)(p), order)
#define __hybrid_atomic_add64(p, val, order)                         __hybrid_atomic_add((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub64(p, val, order)                         __hybrid_atomic_sub((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and64(p, val, order)                         __hybrid_atomic_and((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or64(p, val, order)                          __hybrid_atomic_or((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor64(p, val, order)                         __hybrid_atomic_xor((__UINT64_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand64(p, val, order)                        __hybrid_atomic_nand((__UINT64_TYPE__ *)(p), val, order)
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
#define __hybrid_atomic_load128(p, order)                             __hybrid_atomic_load((__UINT128_TYPE__ const *)(p), order)
#define __hybrid_atomic_store128(p, val, order)                       __hybrid_atomic_store((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xch128(p, val, order)                         __hybrid_atomic_xch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_cmpxch128(p, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_weak128(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_cmpxch_val128(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val((__UINT128_TYPE__ *)(p), oldval, newval, succ, fail)
#define __hybrid_atomic_incfetch128(p, order)                         __hybrid_atomic_incfetch((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_decfetch128(p, order)                         __hybrid_atomic_decfetch((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_addfetch128(p, val, order)                    __hybrid_atomic_addfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_subfetch128(p, val, order)                    __hybrid_atomic_subfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_andfetch128(p, val, order)                    __hybrid_atomic_andfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_orfetch128(p, val, order)                     __hybrid_atomic_orfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xorfetch128(p, val, order)                    __hybrid_atomic_xorfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nandfetch128(p, val, order)                   __hybrid_atomic_nandfetch((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchinc128(p, order)                         __hybrid_atomic_fetchinc((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchdec128(p, order)                         __hybrid_atomic_fetchdec((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_fetchadd128(p, val, order)                    __hybrid_atomic_fetchadd((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchsub128(p, val, order)                    __hybrid_atomic_fetchsub((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchand128(p, val, order)                    __hybrid_atomic_fetchand((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchor128(p, val, order)                     __hybrid_atomic_fetchor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchxor128(p, val, order)                    __hybrid_atomic_fetchxor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_fetchnand128(p, val, order)                   __hybrid_atomic_fetchnand((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_inc128(p, order)                              __hybrid_atomic_inc((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_dec128(p, order)                              __hybrid_atomic_dec((__UINT128_TYPE__ *)(p), order)
#define __hybrid_atomic_add128(p, val, order)                         __hybrid_atomic_add((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_sub128(p, val, order)                         __hybrid_atomic_sub((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_and128(p, val, order)                         __hybrid_atomic_and((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_or128(p, val, order)                          __hybrid_atomic_or((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_xor128(p, val, order)                         __hybrid_atomic_xor((__UINT128_TYPE__ *)(p), val, order)
#define __hybrid_atomic_nand128(p, val, order)                        __hybrid_atomic_nand((__UINT128_TYPE__ *)(p), val, order)
#endif /* __UINT128_TYPE__ */
#elif defined(__GNUC__) || defined(__DCC_VERSION__)
/* __sync_xxx() */
#define __hybrid_atomic_addfetch_seq_cst(p, val)                  __sync_add_and_fetch(p, val)
#define __hybrid_atomic_subfetch_seq_cst(p, val)                  __sync_sub_and_fetch(p, val)
#define __hybrid_atomic_orfetch_seq_cst(p, val)                   __sync_or_and_fetch(p, val)
#define __hybrid_atomic_andfetch_seq_cst(p, val)                  __sync_and_and_fetch(p, val)
#define __hybrid_atomic_xorfetch_seq_cst(p, val)                  __sync_xor_and_fetch(p, val)
#define __hybrid_atomic_fetchadd_seq_cst(p, val)                  __sync_fetch_and_add(p, val)
#define __hybrid_atomic_fetchsub_seq_cst(p, val)                  __sync_fetch_and_sub(p, val)
#define __hybrid_atomic_fetchor_seq_cst(p, val)                   __sync_fetch_and_or(p, val)
#define __hybrid_atomic_fetchand_seq_cst(p, val)                  __sync_fetch_and_and(p, val)
#define __hybrid_atomic_fetchxor_seq_cst(p, val)                  __sync_fetch_and_xor(p, val)
#define __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)         __sync_bool_compare_and_swap(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)     __sync_val_compare_and_swap(p, oldval, newval)
#define __hybrid_atomic_thread_fence_seq_cst()                    __sync_synchronize()
#define __hybrid_atomic_addfetch(p, val, order)                   __hybrid_atomic_addfetch_seq_cst(p, val)
#define __hybrid_atomic_subfetch(p, val, order)                   __hybrid_atomic_subfetch_seq_cst(p, val)
#define __hybrid_atomic_orfetch(p, val, order)                    __hybrid_atomic_orfetch_seq_cst(p, val)
#define __hybrid_atomic_andfetch(p, val, order)                   __hybrid_atomic_andfetch_seq_cst(p, val)
#define __hybrid_atomic_xorfetch(p, val, order)                   __hybrid_atomic_xorfetch_seq_cst(p, val)
#define __hybrid_atomic_fetchadd(p, val, order)                   __hybrid_atomic_fetchadd_seq_cst(p, val)
#define __hybrid_atomic_fetchsub(p, val, order)                   __hybrid_atomic_fetchsub_seq_cst(p, val)
#define __hybrid_atomic_fetchor(p, val, order)                    __hybrid_atomic_fetchor_seq_cst(p, val)
#define __hybrid_atomic_fetchand(p, val, order)                   __hybrid_atomic_fetchand_seq_cst(p, val)
#define __hybrid_atomic_fetchxor(p, val, order)                   __hybrid_atomic_fetchxor_seq_cst(p, val)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)     __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)
#define __hybrid_atomic_thread_fence(order)                       __hybrid_atomic_thread_fence_seq_cst()
#if !defined(__GNUC__) || __GCC_VERSION_NUM >= 40400
#define __hybrid_atomic_fetchnand_seq_cst(p, val) __sync_fetch_and_nand(p, val)
#define __hybrid_atomic_nandfetch_seq_cst(p, val) __sync_nand_and_fetch(p, val)
#define __hybrid_atomic_fetchnand(p, val, order)  __hybrid_atomic_fetchnand_seq_cst(p, val)
#define __hybrid_atomic_nandfetch(p, val, order)  __hybrid_atomic_nandfetch_seq_cst(p, val)
#endif /* GCC 4.4 */
/**/
#include "__atomic-complete.h"
#elif __has_builtin(__sync_bool_compare_and_swap) || __has_builtin(__sync_val_compare_and_swap)
/* __sync_xxx()  (compiler-detected)
 * Note that  for full  support, the  compiler must  at least  provide
 * `__sync_bool_compare_and_swap()' or `__sync_val_compare_and_swap()' */
#if __has_builtin(__sync_bool_compare_and_swap)
#define __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval) \
	__sync_bool_compare_and_swap(p, oldval, newval)
#endif /* __has_builtin(__sync_bool_compare_and_swap) */
#if __has_builtin(__sync_val_compare_and_swap)
#define __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval) \
	__sync_val_compare_and_swap(p, oldval, newval)
#endif /* __has_builtin(__sync_val_compare_and_swap) */

#if __has_builtin(__sync_swap)
#define __hybrid_atomic_xch_seq_cst(p, val) __sync_swap(p, val)
#endif /* __has_builtin(__sync_swap) */
#if __has_builtin(__sync_add_and_fetch)
#define __hybrid_atomic_addfetch_seq_cst(p, val) __sync_add_and_fetch(p, val)
#endif /* __has_builtin(__sync_add_and_fetch) */
#if __has_builtin(__sync_sub_and_fetch)
#define __hybrid_atomic_subfetch_seq_cst(p, val) __sync_sub_and_fetch(p, val)
#endif /* __has_builtin(__sync_sub_and_fetch) */
#if __has_builtin(__sync_or_and_fetch)
#define __hybrid_atomic_orfetch_seq_cst(p, val) __sync_or_and_fetch(p, val)
#endif /* __has_builtin(__sync_or_and_fetch) */
#if __has_builtin(__sync_and_and_fetch)
#define __hybrid_atomic_andfetch_seq_cst(p, val) __sync_and_and_fetch(p, val)
#endif /* __has_builtin(__sync_and_and_fetch) */
#if __has_builtin(__sync_xor_and_fetch)
#define __hybrid_atomic_xorfetch_seq_cst(p, val) __sync_xor_and_fetch(p, val)
#endif /* __has_builtin(__sync_xor_and_fetch) */
#if __has_builtin(__sync_fetch_and_add)
#define __hybrid_atomic_fetchadd_seq_cst(p, val) __sync_fetch_and_add(p, val)
#endif /* __has_builtin(__sync_fetch_and_add) */
#if __has_builtin(__sync_fetch_and_sub)
#define __hybrid_atomic_fetchsub_seq_cst(p, val) __sync_fetch_and_sub(p, val)
#endif /* __has_builtin(__sync_fetch_and_sub) */
#if __has_builtin(__sync_fetch_and_or)
#define __hybrid_atomic_fetchor_seq_cst(p, val) __sync_fetch_and_or(p, val)
#endif /* __has_builtin(__sync_fetch_and_or) */
#if __has_builtin(__sync_fetch_and_and)
#define __hybrid_atomic_fetchand_seq_cst(p, val) __sync_fetch_and_and(p, val)
#endif /* __has_builtin(__sync_fetch_and_and) */
#if __has_builtin(__sync_fetch_and_xor)
#define __hybrid_atomic_fetchxor_seq_cst(p, val) __sync_fetch_and_xor(p, val)
#endif /* __has_builtin(__sync_fetch_and_xor) */
#if __has_builtin(__sync_fetch_and_nand)
#define __hybrid_atomic_fetchnand_seq_cst(p, val) __sync_fetch_and_nand(p, val)
#endif /* __has_builtin(__sync_fetch_and_nand) */
#if __has_builtin(__sync_nand_and_fetch)
#define __hybrid_atomic_nandfetch_seq_cst(p, val) __sync_nand_and_fetch(p, val)
#endif /* __has_builtin(__sync_nand_and_fetch) */
#if __has_builtin(__sync_synchronize)
#define __hybrid_atomic_thread_fence(order) __sync_synchronize()
#endif /* __has_builtin(__sync_synchronize) */

#ifdef __hybrid_atomic_cmpxch_seq_cst
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)
#endif /* __hybrid_atomic_cmpxch_seq_cst */
#ifdef __hybrid_atomic_cmpxch_val_seq_cst
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)
#endif /* __hybrid_atomic_cmpxch_val_seq_cst */
#ifdef __hybrid_atomic_addfetch_seq_cst
#define __hybrid_atomic_addfetch(p, val, order) __hybrid_atomic_addfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_addfetch_seq_cst */
#ifdef __hybrid_atomic_subfetch_seq_cst
#define __hybrid_atomic_subfetch(p, val, order) __hybrid_atomic_subfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_subfetch_seq_cst */
#ifdef __hybrid_atomic_orfetch_seq_cst
#define __hybrid_atomic_orfetch(p, val, order) __hybrid_atomic_orfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_orfetch_seq_cst */
#ifdef __hybrid_atomic_andfetch_seq_cst
#define __hybrid_atomic_andfetch(p, val, order) __hybrid_atomic_andfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_andfetch_seq_cst */
#ifdef __hybrid_atomic_xorfetch_seq_cst
#define __hybrid_atomic_xorfetch(p, val, order) __hybrid_atomic_xorfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_xorfetch_seq_cst */
#ifdef __hybrid_atomic_fetchadd_seq_cst
#define __hybrid_atomic_fetchadd(p, val, order) __hybrid_atomic_fetchadd_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchadd_seq_cst */
#ifdef __hybrid_atomic_fetchsub_seq_cst
#define __hybrid_atomic_fetchsub(p, val, order) __hybrid_atomic_fetchsub_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchsub_seq_cst */
#ifdef __hybrid_atomic_fetchor_seq_cst
#define __hybrid_atomic_fetchor(p, val, order) __hybrid_atomic_fetchor_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchor_seq_cst */
#ifdef __hybrid_atomic_fetchand_seq_cst
#define __hybrid_atomic_fetchand(p, val, order) __hybrid_atomic_fetchand_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchand_seq_cst */
#ifdef __hybrid_atomic_fetchxor_seq_cst
#define __hybrid_atomic_fetchxor(p, val, order) __hybrid_atomic_fetchxor_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchxor_seq_cst */
#ifdef __hybrid_atomic_fetchnand_seq_cst
#define __hybrid_atomic_fetchnand(p, val, order) __hybrid_atomic_fetchnand_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchnand_seq_cst */
#ifdef __hybrid_atomic_nandfetch_seq_cst
#define __hybrid_atomic_nandfetch(p, val, order) __hybrid_atomic_nandfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_nandfetch_seq_cst */
/**/
#include "__atomic-complete.h"
#elif defined(_MSC_VER)
/* _InterlockedXXX() */
#ifdef __cplusplus
#pragma warning(push) /* Keep `4197' disabled in C because of its use in macros. */
#endif /* __cplusplus */
#pragma warning(disable: 4197) /* Casting away `volatile' */
#pragma warning(disable: 4047) /* Differing number of dereferences. */
#pragma warning(disable: 4310) /* Cast truncates constant value */
#include "__atomic-msvc.h"
/**/
#include "__atomic-complete.h"
#ifdef __cplusplus
#pragma warning(pop)
#endif /* __cplusplus */
#else /* ... */
#ifdef __COMPILER_HAVE_GCC_ASM
#include "host.h"
#if defined(__x86_64__) || defined(__i386__)
/* __asm__("lock; cmpxchg") */
#include "__atomic-gasm-x86.h"
/**/
#include "__atomic-complete.h"
#endif /* __x86_64__ || __i386__ */
#endif /* __COMPILER_HAVE_GCC_ASM */

/* Fallback: just use libatomic. - If it's not there, we'll
 * get  link errors, but  for now it's the  best we can do. */
#ifndef __hybrid_atomic_cmpxch
#include "__atomic-libatomic.h"
/**/
#include "__atomic-complete.h"
#endif /* !__hybrid_atomic_cmpxch */
#endif /* !... */

#ifndef __hybrid_atomic_signal_fence
/* Fallback: Emit compiler barriers to implement atomic signal fencing.
 * HINT: If available, compiler barriers are implemented using intrinsic
 *       signal fences, meaning that they are literally the same  thing.
 * e.g.: When hosted by msvc, stuff like `_ReadWriteBarrier()' will appear below. */
#ifdef __COMPILER_BARRIERS_ALL_IDENTICAL
#define __hybrid_atomic_signal_fence(order) __COMPILER_BARRIER()
#else /* __COMPILER_BARRIERS_ALL_IDENTICAL */
#define __hybrid_atomic_signal_fence(order)                     \
	((order) >= __ATOMIC_ACQ_REL ? __COMPILER_BARRIER() :       \
	 (order) >= __ATOMIC_RELEASE ? __COMPILER_WRITE_BARRIER() : \
	 (order) >= __ATOMIC_ACQUIRE ? __COMPILER_READ_BARRIER() : (void)0)
#endif /* !__COMPILER_BARRIERS_ALL_IDENTICAL */
#endif /* !__hybrid_atomic_signal_fence */

#ifndef __hybrid_atomic_thread_fence
#define __hybrid_atomic_thread_fence __hybrid_atomic_signal_fence
#endif /* !__hybrid_atomic_thread_fence */

#ifndef __hybrid_atomic_lockfree
#define __hybrid_atomic_lockfree(p) (__HYBRID_ATOMIC_LOCKFREE(sizeof(*(p))) == 2)
#endif /* !__hybrid_atomic_lockfree */
#endif /* __CC__ */

/* Determine the lock-free-ness of a type with size `x'
 * @return: 0: Never lock-free
 * @return: 1: Sometimes lock-free
 * @return: 2: Always lock-free */
#ifndef __HYBRID_ATOMIC_LOCKFREE
#ifndef __HYBRID_ATOMIC_LOCKFREE_MAX
#define __HYBRID_ATOMIC_LOCKFREE_MAX __SIZEOF_POINTER__
#if defined(__GCC_ATOMIC_LLONG_LOCK_FREE) && defined(__SIZEOF_LONG_LONG__)
#if __HYBRID_ATOMIC_LOCKFREE_MAX < __SIZEOF_LONG_LONG__
#undef __HYBRID_ATOMIC_LOCKFREE_MAX
#define __HYBRID_ATOMIC_LOCKFREE_MAX __SIZEOF_LONG_LONG__
#endif /* __HYBRID_ATOMIC_LOCKFREE_MAX < __SIZEOF_LONG_LONG__ */
#endif /* __GCC_ATOMIC_LLONG_LOCK_FREE && __SIZEOF_LONG_LONG__ */
#endif /* !__HYBRID_ATOMIC_LOCKFREE_MAX */
#define __HYBRID_ATOMIC_LOCKFREE(x) ((x) <= __HYBRID_ATOMIC_LOCKFREE_MAX ? 2 : 0)
#endif /* !__HYBRID_ATOMIC_LOCKFREE */

#ifndef __GCC_ATOMIC_BOOL_LOCK_FREE
#ifndef __SIZEOF_BOOL__
#define __SIZEOF_BOOL__ __SIZEOF_CHAR__
#endif /* !__SIZEOF_BOOL__ */
#define __GCC_ATOMIC_BOOL_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_BOOL__)
#endif /* !__GCC_ATOMIC_BOOL_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR_LOCK_FREE
#define __GCC_ATOMIC_CHAR_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_CHAR__)
#endif /* !__GCC_ATOMIC_CHAR_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR8_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(1)
#endif /* !__GCC_ATOMIC_CHAR8_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(2)
#endif /* !__GCC_ATOMIC_CHAR16_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(4)
#endif /* !__GCC_ATOMIC_CHAR32_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_WCHAR_T__)
#endif /* !__GCC_ATOMIC_WCHAR_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_SHORT_LOCK_FREE
#define __GCC_ATOMIC_SHORT_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_SHORT__)
#endif /* !__GCC_ATOMIC_SHORT_LOCK_FREE */

#ifndef __GCC_ATOMIC_INT_LOCK_FREE
#define __GCC_ATOMIC_INT_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_INT__)
#endif /* !__GCC_ATOMIC_INT_LOCK_FREE */

#ifndef __GCC_ATOMIC_LONG_LOCK_FREE
#define __GCC_ATOMIC_LONG_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_LONG__)
#endif /* !__GCC_ATOMIC_LONG_LOCK_FREE */

#ifndef __GCC_ATOMIC_LLONG_LOCK_FREE
#ifdef __SIZEOF_LONG_LONG__
#define __GCC_ATOMIC_LLONG_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_LONG_LONG__)
#endif /* __SIZEOF_LONG_LONG__ */
#endif /* !__GCC_ATOMIC_LLONG_LOCK_FREE */

#ifndef __GCC_ATOMIC_POINTER_LOCK_FREE
#define __GCC_ATOMIC_POINTER_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_POINTER__)
#endif /* !__GCC_ATOMIC_POINTER_LOCK_FREE */

#endif /* !__GUARD_HYBRID___ATOMIC_H */
