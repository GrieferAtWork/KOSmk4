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
#ifndef __GUARD_HYBRID_ATOMIC_H
#define __GUARD_HYBRID_ATOMIC_H 1

#include "../__stdinc.h"
#include "__atomic.h"
#include "host.h"

#ifdef __CC__

#define OATOMIC_LOAD        __hybrid_atomic_load
#define OATOMIC_STORE       __hybrid_atomic_store
#define OATOMIC_XCH         __hybrid_atomic_xch
#define OATOMIC_CMPXCH      __hybrid_atomic_cmpxch
#define OATOMIC_CMPXCH_WEAK __hybrid_atomic_cmpxch_weak
#define OATOMIC_CMPXCH_VAL  __hybrid_atomic_cmpxch_val
#define OATOMIC_ADDFETCH    __hybrid_atomic_addfetch
#define OATOMIC_SUBFETCH    __hybrid_atomic_subfetch
#define OATOMIC_ANDFETCH    __hybrid_atomic_andfetch
#define OATOMIC_ORFETCH     __hybrid_atomic_orfetch
#define OATOMIC_XORFETCH    __hybrid_atomic_xorfetch
#define OATOMIC_NANDFETCH   __hybrid_atomic_nandfetch
#define OATOMIC_INCFETCH    __hybrid_atomic_incfetch
#define OATOMIC_DECFETCH    __hybrid_atomic_decfetch
#define OATOMIC_FETCHADD    __hybrid_atomic_fetchadd
#define OATOMIC_FETCHSUB    __hybrid_atomic_fetchsub
#define OATOMIC_FETCHAND    __hybrid_atomic_fetchand
#define OATOMIC_FETCHOR     __hybrid_atomic_fetchor
#define OATOMIC_FETCHXOR    __hybrid_atomic_fetchxor
#define OATOMIC_FETCHNAND   __hybrid_atomic_fetchnand
#define OATOMIC_FETCHINC    __hybrid_atomic_fetchinc
#define OATOMIC_FETCHDEC    __hybrid_atomic_fetchdec
#define OATOMIC_ADD         __hybrid_atomic_add
#define OATOMIC_SUB         __hybrid_atomic_sub
#define OATOMIC_AND         __hybrid_atomic_and
#define OATOMIC_OR          __hybrid_atomic_or
#define OATOMIC_XOR         __hybrid_atomic_xor
#define OATOMIC_NAND        __hybrid_atomic_nand
#define OATOMIC_INC         __hybrid_atomic_inc
#define OATOMIC_DEC         __hybrid_atomic_dec

#define ATOMIC_LOAD(x)                    OATOMIC_LOAD(x, __ATOMIC_SEQ_CST)
#define ATOMIC_STORE(x, v)                OATOMIC_STORE(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_XCH(x, v)                  OATOMIC_XCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH(x, oldv, newv)      OATOMIC_CMPXCH(x, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_WEAK(x, oldv, newv) OATOMIC_CMPXCH_WEAK(x, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_VAL(x, oldv, newv)  OATOMIC_CMPXCH_VAL(x, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_ADDFETCH(x, v)             OATOMIC_ADDFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_SUBFETCH(x, v)             OATOMIC_SUBFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_ANDFETCH(x, v)             OATOMIC_ANDFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_ORFETCH(x, v)              OATOMIC_ORFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_XORFETCH(x, v)             OATOMIC_XORFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_NANDFETCH(x, v)            OATOMIC_NANDFETCH(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_INCFETCH(x)                OATOMIC_INCFETCH(x, __ATOMIC_SEQ_CST)
#define ATOMIC_DECFETCH(x)                OATOMIC_DECFETCH(x, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHADD(x, v)             OATOMIC_FETCHADD(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHSUB(x, v)             OATOMIC_FETCHSUB(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHAND(x, v)             OATOMIC_FETCHAND(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHOR(x, v)              OATOMIC_FETCHOR(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHXOR(x, v)             OATOMIC_FETCHXOR(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHNAND(x, v)            OATOMIC_FETCHNAND(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHINC(x)                OATOMIC_FETCHINC(x, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHDEC(x)                OATOMIC_FETCHDEC(x, __ATOMIC_SEQ_CST)
#define ATOMIC_ADD(x, v)                  OATOMIC_ADD(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_SUB(x, v)                  OATOMIC_SUB(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_AND(x, v)                  OATOMIC_AND(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_OR(x, v)                   OATOMIC_OR(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_XOR(x, v)                  OATOMIC_XOR(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_NAND(x, v)                 OATOMIC_NAND(x, v, __ATOMIC_SEQ_CST)
#define ATOMIC_INC(x)                     OATOMIC_INC(x, __ATOMIC_SEQ_CST)
#define ATOMIC_DEC(x)                     OATOMIC_DEC(x, __ATOMIC_SEQ_CST)

/* Simplified atomic read/write  functions that only  guaranty correct  ordering
 * of  reads/writes respectively,  as well as  that reads and  writes are always
 * completed  as a whole (i.e. reading a 64-bit value is always done in a single
 * instruction, preventing  the possibility  of some  part of  a value  changing
 * after it had already been read, but before all other parts were read as well) */
#define ATOMIC_READ(x)     OATOMIC_LOAD(x, __ATOMIC_ACQUIRE)
#define ATOMIC_WRITE(x, v) OATOMIC_STORE(x, v, __ATOMIC_RELEASE)

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_ATOMIC_H */
