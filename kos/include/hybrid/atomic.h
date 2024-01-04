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
#ifndef __GUARD_HYBRID_ATOMIC_H
#define __GUARD_HYBRID_ATOMIC_H 1

#include "../__stdinc.h"
#include "__atomic.h"
#include "host.h"

#ifdef __CC__

#define ATOMIC_LOAD_EXPLICIT(ptr, order)                             __hybrid_atomic_load(ptr, order)
#define ATOMIC_STORE_EXPLICIT(ptr, value, order)                     __hybrid_atomic_store(ptr, value, order)
#define ATOMIC_XCH_EXPLICIT(ptr, value, order)                       __hybrid_atomic_xch(ptr, value, order)
#define ATOMIC_CMPXCH_EXPLICIT(ptr, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch(ptr, oldval, newval, succ, fail)
#define ATOMIC_CMPXCH_WEAK_EXPLICIT(ptr, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak(ptr, oldval, newval, succ, fail)
#define ATOMIC_CMPXCH_VAL_EXPLICIT(ptr, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val(ptr, oldval, newval, succ, fail)
#define ATOMIC_ADDFETCH_EXPLICIT(ptr, value, order)                  __hybrid_atomic_addfetch(ptr, value, order)
#define ATOMIC_SUBFETCH_EXPLICIT(ptr, value, order)                  __hybrid_atomic_subfetch(ptr, value, order)
#define ATOMIC_ANDFETCH_EXPLICIT(ptr, value, order)                  __hybrid_atomic_andfetch(ptr, value, order)
#define ATOMIC_ORFETCH_EXPLICIT(ptr, value, order)                   __hybrid_atomic_orfetch(ptr, value, order)
#define ATOMIC_XORFETCH_EXPLICIT(ptr, value, order)                  __hybrid_atomic_xorfetch(ptr, value, order)
#define ATOMIC_NANDFETCH_EXPLICIT(ptr, value, order)                 __hybrid_atomic_nandfetch(ptr, value, order)
#define ATOMIC_INCFETCH_EXPLICIT(ptr, order)                         __hybrid_atomic_incfetch(ptr, order)
#define ATOMIC_DECFETCH_EXPLICIT(ptr, order)                         __hybrid_atomic_decfetch(ptr, order)
#define ATOMIC_FETCHADD_EXPLICIT(ptr, value, order)                  __hybrid_atomic_fetchadd(ptr, value, order)
#define ATOMIC_FETCHSUB_EXPLICIT(ptr, value, order)                  __hybrid_atomic_fetchsub(ptr, value, order)
#define ATOMIC_FETCHAND_EXPLICIT(ptr, value, order)                  __hybrid_atomic_fetchand(ptr, value, order)
#define ATOMIC_FETCHOR_EXPLICIT(ptr, value, order)                   __hybrid_atomic_fetchor(ptr, value, order)
#define ATOMIC_FETCHXOR_EXPLICIT(ptr, value, order)                  __hybrid_atomic_fetchxor(ptr, value, order)
#define ATOMIC_FETCHNAND_EXPLICIT(ptr, value, order)                 __hybrid_atomic_fetchnand(ptr, value, order)
#define ATOMIC_FETCHINC_EXPLICIT(ptr, order)                         __hybrid_atomic_fetchinc(ptr, order)
#define ATOMIC_FETCHDEC_EXPLICIT(ptr, order)                         __hybrid_atomic_fetchdec(ptr, order)
#define ATOMIC_ADD_EXPLICIT(ptr, value, order)                       __hybrid_atomic_add(ptr, value, order)
#define ATOMIC_SUB_EXPLICIT(ptr, value, order)                       __hybrid_atomic_sub(ptr, value, order)
#define ATOMIC_AND_EXPLICIT(ptr, value, order)                       __hybrid_atomic_and(ptr, value, order)
#define ATOMIC_OR_EXPLICIT(ptr, value, order)                        __hybrid_atomic_or(ptr, value, order)
#define ATOMIC_XOR_EXPLICIT(ptr, value, order)                       __hybrid_atomic_xor(ptr, value, order)
#define ATOMIC_NAND_EXPLICIT(ptr, value, order)                      __hybrid_atomic_nand(ptr, value, order)
#define ATOMIC_INC_EXPLICIT(ptr, order)                              __hybrid_atomic_inc(ptr, order)
#define ATOMIC_DEC_EXPLICIT(ptr, order)                              __hybrid_atomic_dec(ptr, order)

#define ATOMIC_LOAD(ptr)                    ATOMIC_LOAD_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_STORE(ptr, value)            ATOMIC_STORE_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XCH(ptr, value)              ATOMIC_XCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH(ptr, oldv, newv)      ATOMIC_CMPXCH_EXPLICIT(ptr, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_WEAK(ptr, oldv, newv) ATOMIC_CMPXCH_WEAK_EXPLICIT(ptr, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_VAL(ptr, oldv, newv)  ATOMIC_CMPXCH_VAL_EXPLICIT(ptr, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_ADDFETCH(ptr, value)         ATOMIC_ADDFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_SUBFETCH(ptr, value)         ATOMIC_SUBFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_ANDFETCH(ptr, value)         ATOMIC_ANDFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_ORFETCH(ptr, value)          ATOMIC_ORFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XORFETCH(ptr, value)         ATOMIC_XORFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_NANDFETCH(ptr, value)        ATOMIC_NANDFETCH_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_INCFETCH(ptr)                ATOMIC_INCFETCH_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_DECFETCH(ptr)                ATOMIC_DECFETCH_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHADD(ptr, value)         ATOMIC_FETCHADD_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHSUB(ptr, value)         ATOMIC_FETCHSUB_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHAND(ptr, value)         ATOMIC_FETCHAND_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHOR(ptr, value)          ATOMIC_FETCHOR_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHXOR(ptr, value)         ATOMIC_FETCHXOR_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHNAND(ptr, value)        ATOMIC_FETCHNAND_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHINC(ptr)                ATOMIC_FETCHINC_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHDEC(ptr)                ATOMIC_FETCHDEC_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_ADD(ptr, value)              ATOMIC_ADD_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_SUB(ptr, value)              ATOMIC_SUB_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_AND(ptr, value)              ATOMIC_AND_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_OR(ptr, value)               ATOMIC_OR_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XOR(ptr, value)              ATOMIC_XOR_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_NAND(ptr, value)             ATOMIC_NAND_EXPLICIT(ptr, value, __ATOMIC_SEQ_CST)
#define ATOMIC_INC(ptr)                     ATOMIC_INC_EXPLICIT(ptr, __ATOMIC_SEQ_CST)
#define ATOMIC_DEC(ptr)                     ATOMIC_DEC_EXPLICIT(ptr, __ATOMIC_SEQ_CST)

/* Simplified atomic read/write  functions that only  guaranty correct  ordering
 * of  reads/writes respectively,  as well as  that reads and  writes are always
 * completed  as a whole (i.e. reading a 64-bit value is always done in a single
 * instruction, preventing  the possibility  of some  part of  a value  changing
 * after it had already been read, but before all other parts were read as well) */
#define ATOMIC_READ(ptr)         ATOMIC_LOAD_EXPLICIT(ptr, __ATOMIC_ACQUIRE)
#define ATOMIC_WRITE(ptr, value) ATOMIC_STORE_EXPLICIT(ptr, value, __ATOMIC_RELEASE)

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_ATOMIC_H */
