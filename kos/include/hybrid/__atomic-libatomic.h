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
#ifndef __GUARD_HYBRID___ATOMIC_LIBATOMIC_H
#define __GUARD_HYBRID___ATOMIC_LIBATOMIC_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __HYBRID_LIBATOMIC_CC
#define __HYBRID_LIBATOMIC_CC /* nothing */
#endif /* !__HYBRID_LIBATOMIC_CC */

__NAMESPACE_INT_BEGIN
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_load_1)(__UINT8_TYPE__ const *__mptr, int __order);
extern void (__HYBRID_LIBATOMIC_CC __atomic_store_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_exchange_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_compare_exchange_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ *__p_expected, __UINT8_TYPE__ __newval, int __succ, int __fail);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_test_and_set_1)(__UINT8_TYPE__ *__mptr, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_add_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_sub_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_and_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_xor_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_or_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_nand_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_add_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_sub_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_and_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_xor_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_or_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);
extern __UINT8_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_nand_fetch_1)(__UINT8_TYPE__ *__mptr, __UINT8_TYPE__ __val, int __order);

extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_load_2)(__UINT16_TYPE__ const *__mptr, int __order);
extern void (__HYBRID_LIBATOMIC_CC __atomic_store_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_exchange_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_compare_exchange_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ *__p_expected, __UINT16_TYPE__ __newval, int __succ, int __fail);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_test_and_set_2)(__UINT16_TYPE__ *__mptr, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_add_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_sub_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_and_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_xor_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_or_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_nand_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_add_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_sub_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_and_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_xor_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_or_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);
extern __UINT16_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_nand_fetch_2)(__UINT16_TYPE__ *__mptr, __UINT16_TYPE__ __val, int __order);

extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_load_4)(__UINT32_TYPE__ const *__mptr, int __order);
extern void (__HYBRID_LIBATOMIC_CC __atomic_store_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_exchange_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_compare_exchange_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ *__p_expected, __UINT32_TYPE__ __newval, int __succ, int __fail);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_test_and_set_4)(__UINT32_TYPE__ *__mptr, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_add_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_sub_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_and_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_xor_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_or_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_nand_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_add_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_sub_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_and_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_xor_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_or_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);
extern __UINT32_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_nand_fetch_4)(__UINT32_TYPE__ *__mptr, __UINT32_TYPE__ __val, int __order);

#ifdef __UINT64_TYPE__
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_load_8)(__UINT64_TYPE__ const *__mptr, int __order);
extern void (__HYBRID_LIBATOMIC_CC __atomic_store_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_exchange_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_compare_exchange_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ *__p_expected, __UINT64_TYPE__ __newval, int __succ, int __fail);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_test_and_set_8)(__UINT64_TYPE__ *__mptr, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_add_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_sub_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_and_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_xor_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_or_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_nand_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_add_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_sub_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_and_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_xor_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_or_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
extern __UINT64_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_nand_fetch_8)(__UINT64_TYPE__ *__mptr, __UINT64_TYPE__ __val, int __order);
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_load_16)(__UINT128_TYPE__ const *__mptr, int __order);
extern void (__HYBRID_LIBATOMIC_CC __atomic_store_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_exchange_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_compare_exchange_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ *__p_expected, __UINT128_TYPE__ __newval, int __succ, int __fail);
extern __BOOL (__HYBRID_LIBATOMIC_CC __atomic_test_and_set_16)(__UINT128_TYPE__ *__mptr, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_add_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_sub_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_and_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_xor_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_or_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_fetch_nand_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_add_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_sub_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_and_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_xor_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_or_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
extern __UINT128_TYPE__ (__HYBRID_LIBATOMIC_CC __atomic_nand_fetch_16)(__UINT128_TYPE__ *__mptr, __UINT128_TYPE__ __val, int __order);
#endif /* __UINT128_TYPE__ */
__NAMESPACE_INT_END

#define __hybrid_atomic_load8(p, order)           (__NAMESPACE_INT_SYM __atomic_load_1)(p, order)
#define __hybrid_atomic_store8(p, val, order)     (__NAMESPACE_INT_SYM __atomic_store_1)(p, val, order)
#define __hybrid_atomic_xch8(p, val, order)       (__NAMESPACE_INT_SYM __atomic_exchange_1)(p, val, order)
#define __hybrid_atomic_fetchadd8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_add_1)(p, val, order)
#define __hybrid_atomic_fetchsub8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_sub_1)(p, val, order)
#define __hybrid_atomic_fetchand8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_and_1)(p, val, order)
#define __hybrid_atomic_fetchxor8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_xor_1)(p, val, order)
#define __hybrid_atomic_fetchor8(p, val, order)   (__NAMESPACE_INT_SYM __atomic_fetch_or_1)(p, val, order)
#define __hybrid_atomic_fetchnand8(p, val, order) (__NAMESPACE_INT_SYM __atomic_fetch_nand_1)(p, val, order)
#define __hybrid_atomic_addfetch8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_add_fetch_1)(p, val, order)
#define __hybrid_atomic_subfetch8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_sub_fetch_1)(p, val, order)
#define __hybrid_atomic_andfetch8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_and_fetch_1)(p, val, order)
#define __hybrid_atomic_xorfetch8(p, val, order)  (__NAMESPACE_INT_SYM __atomic_xor_fetch_1)(p, val, order)
#define __hybrid_atomic_orfetch8(p, val, order)   (__NAMESPACE_INT_SYM __atomic_or_fetch_1)(p, val, order)
#define __hybrid_atomic_nandfetch8(p, val, order) (__NAMESPACE_INT_SYM __atomic_nand_fetch_1)(p, val, order)

#define __hybrid_atomic_load16(p, order)           (__NAMESPACE_INT_SYM __atomic_load_2)(p, order)
#define __hybrid_atomic_store16(p, val, order)     (__NAMESPACE_INT_SYM __atomic_store_2)(p, val, order)
#define __hybrid_atomic_xch16(p, val, order)       (__NAMESPACE_INT_SYM __atomic_exchange_2)(p, val, order)
#define __hybrid_atomic_fetchadd16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_add_2)(p, val, order)
#define __hybrid_atomic_fetchsub16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_sub_2)(p, val, order)
#define __hybrid_atomic_fetchand16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_and_2)(p, val, order)
#define __hybrid_atomic_fetchxor16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_xor_2)(p, val, order)
#define __hybrid_atomic_fetchor16(p, val, order)   (__NAMESPACE_INT_SYM __atomic_fetch_or_2)(p, val, order)
#define __hybrid_atomic_fetchnand16(p, val, order) (__NAMESPACE_INT_SYM __atomic_fetch_nand_2)(p, val, order)
#define __hybrid_atomic_addfetch16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_add_fetch_2)(p, val, order)
#define __hybrid_atomic_subfetch16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_sub_fetch_2)(p, val, order)
#define __hybrid_atomic_andfetch16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_and_fetch_2)(p, val, order)
#define __hybrid_atomic_xorfetch16(p, val, order)  (__NAMESPACE_INT_SYM __atomic_xor_fetch_2)(p, val, order)
#define __hybrid_atomic_orfetch16(p, val, order)   (__NAMESPACE_INT_SYM __atomic_or_fetch_2)(p, val, order)
#define __hybrid_atomic_nandfetch16(p, val, order) (__NAMESPACE_INT_SYM __atomic_nand_fetch_2)(p, val, order)

#define __hybrid_atomic_load32(p, order)           (__NAMESPACE_INT_SYM __atomic_load_4)(p, order)
#define __hybrid_atomic_store32(p, val, order)     (__NAMESPACE_INT_SYM __atomic_store_4)(p, val, order)
#define __hybrid_atomic_xch32(p, val, order)       (__NAMESPACE_INT_SYM __atomic_exchange_4)(p, val, order)
#define __hybrid_atomic_fetchadd32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_add_4)(p, val, order)
#define __hybrid_atomic_fetchsub32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_sub_4)(p, val, order)
#define __hybrid_atomic_fetchand32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_and_4)(p, val, order)
#define __hybrid_atomic_fetchxor32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_xor_4)(p, val, order)
#define __hybrid_atomic_fetchor32(p, val, order)   (__NAMESPACE_INT_SYM __atomic_fetch_or_4)(p, val, order)
#define __hybrid_atomic_fetchnand32(p, val, order) (__NAMESPACE_INT_SYM __atomic_fetch_nand_4)(p, val, order)
#define __hybrid_atomic_addfetch32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_add_fetch_4)(p, val, order)
#define __hybrid_atomic_subfetch32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_sub_fetch_4)(p, val, order)
#define __hybrid_atomic_andfetch32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_and_fetch_4)(p, val, order)
#define __hybrid_atomic_xorfetch32(p, val, order)  (__NAMESPACE_INT_SYM __atomic_xor_fetch_4)(p, val, order)
#define __hybrid_atomic_orfetch32(p, val, order)   (__NAMESPACE_INT_SYM __atomic_or_fetch_4)(p, val, order)
#define __hybrid_atomic_nandfetch32(p, val, order) (__NAMESPACE_INT_SYM __atomic_nand_fetch_4)(p, val, order)

#ifdef __UINT64_TYPE__
#define __hybrid_atomic_load64(p, order)           (__NAMESPACE_INT_SYM __atomic_load_8)(p, order)
#define __hybrid_atomic_store64(p, val, order)     (__NAMESPACE_INT_SYM __atomic_store_8)(p, val, order)
#define __hybrid_atomic_xch64(p, val, order)       (__NAMESPACE_INT_SYM __atomic_exchange_8)(p, val, order)
#define __hybrid_atomic_fetchadd64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_add_8)(p, val, order)
#define __hybrid_atomic_fetchsub64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_sub_8)(p, val, order)
#define __hybrid_atomic_fetchand64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_and_8)(p, val, order)
#define __hybrid_atomic_fetchxor64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_xor_8)(p, val, order)
#define __hybrid_atomic_fetchor64(p, val, order)   (__NAMESPACE_INT_SYM __atomic_fetch_or_8)(p, val, order)
#define __hybrid_atomic_fetchnand64(p, val, order) (__NAMESPACE_INT_SYM __atomic_fetch_nand_8)(p, val, order)
#define __hybrid_atomic_addfetch64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_add_fetch_8)(p, val, order)
#define __hybrid_atomic_subfetch64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_sub_fetch_8)(p, val, order)
#define __hybrid_atomic_andfetch64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_and_fetch_8)(p, val, order)
#define __hybrid_atomic_xorfetch64(p, val, order)  (__NAMESPACE_INT_SYM __atomic_xor_fetch_8)(p, val, order)
#define __hybrid_atomic_orfetch64(p, val, order)   (__NAMESPACE_INT_SYM __atomic_or_fetch_8)(p, val, order)
#define __hybrid_atomic_nandfetch64(p, val, order) (__NAMESPACE_INT_SYM __atomic_nand_fetch_8)(p, val, order)
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
#define __hybrid_atomic_load128(p, order)           (__NAMESPACE_INT_SYM __atomic_load_16)(p, order)
#define __hybrid_atomic_store128(p, val, order)     (__NAMESPACE_INT_SYM __atomic_store_16)(p, val, order)
#define __hybrid_atomic_xch128(p, val, order)       (__NAMESPACE_INT_SYM __atomic_exchange_16)(p, val, order)
#define __hybrid_atomic_fetchadd128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_add_16)(p, val, order)
#define __hybrid_atomic_fetchsub128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_sub_16)(p, val, order)
#define __hybrid_atomic_fetchand128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_and_16)(p, val, order)
#define __hybrid_atomic_fetchxor128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_fetch_xor_16)(p, val, order)
#define __hybrid_atomic_fetchor128(p, val, order)   (__NAMESPACE_INT_SYM __atomic_fetch_or_16)(p, val, order)
#define __hybrid_atomic_fetchnand128(p, val, order) (__NAMESPACE_INT_SYM __atomic_fetch_nand_16)(p, val, order)
#define __hybrid_atomic_addfetch128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_add_fetch_16)(p, val, order)
#define __hybrid_atomic_subfetch128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_sub_fetch_16)(p, val, order)
#define __hybrid_atomic_andfetch128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_and_fetch_16)(p, val, order)
#define __hybrid_atomic_xorfetch128(p, val, order)  (__NAMESPACE_INT_SYM __atomic_xor_fetch_16)(p, val, order)
#define __hybrid_atomic_orfetch128(p, val, order)   (__NAMESPACE_INT_SYM __atomic_or_fetch_16)(p, val, order)
#define __hybrid_atomic_nandfetch128(p, val, order) (__NAMESPACE_INT_SYM __atomic_nand_fetch_16)(p, val, order)
#endif /* __UINT128_TYPE__ */

#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch8(p, oldval, newval, succ, fail)                                              \
	__XBLOCK({                                                                                              \
		__UINT8_TYPE__ _hacx8_oldval = (oldval);                                                            \
		__XRETURN (__NAMESPACE_INT_SYM __atomic_compare_exchange_1)(p, &_hacx8_oldval, newval, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail)                                \
	__XBLOCK({                                                                                    \
		__UINT8_TYPE__ _hacx8_oldval = (oldval);                                                  \
		(__NAMESPACE_INT_SYM __atomic_compare_exchange_1)(p, &_hacx8_oldval, newval, succ, fail); \
		__XRETURN _hacx8_oldval;                                                                  \
	})
#define __hybrid_atomic_cmpxch16(p, oldval, newval, succ, fail)                                              \
	__XBLOCK({                                                                                               \
		__UINT16_TYPE__ _hacx16_oldval = (oldval);                                                           \
		__XRETURN (__NAMESPACE_INT_SYM __atomic_compare_exchange_2)(p, &_hacx16_oldval, newval, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail)                                \
	__XBLOCK({                                                                                     \
		__UINT16_TYPE__ _hacx16_oldval = (oldval);                                                 \
		(__NAMESPACE_INT_SYM __atomic_compare_exchange_2)(p, &_hacx16_oldval, newval, succ, fail); \
		__XRETURN _hacx16_oldval;                                                                  \
	})
#define __hybrid_atomic_cmpxch32(p, oldval, newval, succ, fail)                                              \
	__XBLOCK({                                                                                               \
		__UINT32_TYPE__ _hacx32_oldval = (oldval);                                                           \
		__XRETURN (__NAMESPACE_INT_SYM __atomic_compare_exchange_4)(p, &_hacx32_oldval, newval, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail)                                \
	__XBLOCK({                                                                                     \
		__UINT32_TYPE__ _hacx32_oldval = (oldval);                                                 \
		(__NAMESPACE_INT_SYM __atomic_compare_exchange_4)(p, &_hacx32_oldval, newval, succ, fail); \
		__XRETURN _hacx32_oldval;                                                                  \
	})
#ifdef __UINT64_TYPE__
#define __hybrid_atomic_cmpxch64(p, oldval, newval, succ, fail)                                              \
	__XBLOCK({                                                                                               \
		__UINT64_TYPE__ _hacx64_oldval = (oldval);                                                           \
		__XRETURN (__NAMESPACE_INT_SYM __atomic_compare_exchange_8)(p, &_hacx64_oldval, newval, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail)                                \
	__XBLOCK({                                                                                     \
		__UINT64_TYPE__ _hacx64_oldval = (oldval);                                                 \
		(__NAMESPACE_INT_SYM __atomic_compare_exchange_8)(p, &_hacx64_oldval, newval, succ, fail); \
		__XRETURN _hacx64_oldval;                                                                  \
	})
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#define __hybrid_atomic_cmpxch128(p, oldval, newval, succ, fail)                                               \
	__XBLOCK({                                                                                                 \
		__UINT128_TYPE__ _hacx128_oldval = (oldval);                                                           \
		__XRETURN (__NAMESPACE_INT_SYM __atomic_compare_exchange_16)(p, &_hacx128_oldval, newval, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val128(p, oldval, newval, succ, fail)                                 \
	__XBLOCK({                                                                                       \
		__UINT128_TYPE__ _hacx128_oldval = (oldval);                                                 \
		(__NAMESPACE_INT_SYM __atomic_compare_exchange_16)(p, &_hacx128_oldval, newval, succ, fail); \
		__XRETURN _hacx128_oldval;                                                                   \
	})
#endif /* __UINT128_TYPE__ */
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_cmpxch8 __hybrid_atomic_cmpxch8
__LOCAL __BOOL (__hybrid_atomic_cmpxch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __oldval,
                                         __UINT8_TYPE__ __newval, int __succ, int __fail) {
	return (__NAMESPACE_INT_SYM __atomic_compare_exchange_1)(__p, &__oldval, __newval, __succ, __fail);
}
#define __hybrid_atomic_cmpxch_val8 __hybrid_atomic_cmpxch_val8
__LOCAL __UINT8_TYPE__ (__hybrid_atomic_cmpxch_val8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __oldval,
                                                     __UINT8_TYPE__ __newval, int __succ, int __fail) {
	(__NAMESPACE_INT_SYM __atomic_compare_exchange_1)(__p, &__oldval, __newval, __succ, __fail);
	return __oldval;
}
#define __hybrid_atomic_cmpxch16 __hybrid_atomic_cmpxch16
__LOCAL __BOOL (__hybrid_atomic_cmpxch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __oldval,
                                          __UINT16_TYPE__ __newval, int __succ, int __fail) {
	return (__NAMESPACE_INT_SYM __atomic_compare_exchange_2)(__p, &__oldval, __newval, __succ, __fail);
}
#define __hybrid_atomic_cmpxch_val16 __hybrid_atomic_cmpxch_val16
__LOCAL __UINT16_TYPE__ (__hybrid_atomic_cmpxch_val16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __oldval,
                                                       __UINT16_TYPE__ __newval, int __succ, int __fail) {
	(__NAMESPACE_INT_SYM __atomic_compare_exchange_2)(__p, &__oldval, __newval, __succ, __fail);
	return __oldval;
}
#define __hybrid_atomic_cmpxch32 __hybrid_atomic_cmpxch32
__LOCAL __BOOL (__hybrid_atomic_cmpxch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __oldval,
                                          __UINT32_TYPE__ __newval, int __succ, int __fail) {
	return (__NAMESPACE_INT_SYM __atomic_compare_exchange_4)(__p, &__oldval, __newval, __succ, __fail);
}
#define __hybrid_atomic_cmpxch_val32 __hybrid_atomic_cmpxch_val32
__LOCAL __UINT32_TYPE__ (__hybrid_atomic_cmpxch_val32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __oldval,
                                                       __UINT32_TYPE__ __newval, int __succ, int __fail) {
	(__NAMESPACE_INT_SYM __atomic_compare_exchange_4)(__p, &__oldval, __newval, __succ, __fail);
	return __oldval;
}
#ifdef __UINT64_TYPE__
#define __hybrid_atomic_cmpxch64 __hybrid_atomic_cmpxch64
__LOCAL __BOOL (__hybrid_atomic_cmpxch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __oldval,
                                          __UINT64_TYPE__ __newval, int __succ, int __fail) {
	return (__NAMESPACE_INT_SYM __atomic_compare_exchange_8)(__p, &__oldval, __newval, __succ, __fail);
}
#define __hybrid_atomic_cmpxch_val64 __hybrid_atomic_cmpxch_val64
__LOCAL __UINT64_TYPE__ (__hybrid_atomic_cmpxch_val64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __oldval,
                                                       __UINT64_TYPE__ __newval, int __succ, int __fail) {
	(__NAMESPACE_INT_SYM __atomic_compare_exchange_8)(__p, &__oldval, __newval, __succ, __fail);
	return __oldval;
}
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#define __hybrid_atomic_cmpxch128 __hybrid_atomic_cmpxch128
__LOCAL __BOOL (__hybrid_atomic_cmpxch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __oldval,
                                           __UINT128_TYPE__ __newval, int __succ, int __fail) {
	return (__NAMESPACE_INT_SYM __atomic_compare_exchange_16)(__p, &__oldval, __newval, __succ, __fail);
}
#define __hybrid_atomic_cmpxch_val128 __hybrid_atomic_cmpxch_val128
__LOCAL __UINT128_TYPE__ (__hybrid_atomic_cmpxch_val128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __oldval,
                                                         __UINT128_TYPE__ __newval, int __succ, int __fail) {
	(__NAMESPACE_INT_SYM __atomic_compare_exchange_16)(__p, &__oldval, __newval, __succ, __fail);
	return __oldval;
}
#endif /* __UINT128_TYPE__ */
#endif /* __NO_XBLOCK */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___ATOMIC_LIBATOMIC_H */
