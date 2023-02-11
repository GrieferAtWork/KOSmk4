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
#ifndef __GUARD_HYBRID_ATOMIC_H
#define __GUARD_HYBRID_ATOMIC_H 1

#include "../__stdinc.h"
#include "__atomic.h"
#include "host.h"

#ifdef __CC__

#define OATOMIC_LOAD(var, order)                             __hybrid_atomic_load(&(var), order)
#define OATOMIC_STORE(var, value, order)                     __hybrid_atomic_store(&(var), value, order)
#define OATOMIC_XCH(var, value, order)                       __hybrid_atomic_xch(&(var), value, order)
#define OATOMIC_CMPXCH(var, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch(&(var), oldval, newval, succ, fail)
#define OATOMIC_CMPXCH_WEAK(var, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak(&(var), oldval, newval, succ, fail)
#define OATOMIC_CMPXCH_VAL(var, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val(&(var), oldval, newval, succ, fail)
#define OATOMIC_ADDFETCH(var, value, order)                  __hybrid_atomic_addfetch(&(var), value, order)
#define OATOMIC_SUBFETCH(var, value, order)                  __hybrid_atomic_subfetch(&(var), value, order)
#define OATOMIC_ANDFETCH(var, value, order)                  __hybrid_atomic_andfetch(&(var), value, order)
#define OATOMIC_ORFETCH(var, value, order)                   __hybrid_atomic_orfetch(&(var), value, order)
#define OATOMIC_XORFETCH(var, value, order)                  __hybrid_atomic_xorfetch(&(var), value, order)
#define OATOMIC_NANDFETCH(var, value, order)                 __hybrid_atomic_nandfetch(&(var), value, order)
#define OATOMIC_INCFETCH(var, order)                         __hybrid_atomic_incfetch(&(var), order)
#define OATOMIC_DECFETCH(var, order)                         __hybrid_atomic_decfetch(&(var), order)
#define OATOMIC_FETCHADD(var, value, order)                  __hybrid_atomic_fetchadd(&(var), value, order)
#define OATOMIC_FETCHSUB(var, value, order)                  __hybrid_atomic_fetchsub(&(var), value, order)
#define OATOMIC_FETCHAND(var, value, order)                  __hybrid_atomic_fetchand(&(var), value, order)
#define OATOMIC_FETCHOR(var, value, order)                   __hybrid_atomic_fetchor(&(var), value, order)
#define OATOMIC_FETCHXOR(var, value, order)                  __hybrid_atomic_fetchxor(&(var), value, order)
#define OATOMIC_FETCHNAND(var, value, order)                 __hybrid_atomic_fetchnand(&(var), value, order)
#define OATOMIC_FETCHINC(var, order)                         __hybrid_atomic_fetchinc(&(var), order)
#define OATOMIC_FETCHDEC(var, order)                         __hybrid_atomic_fetchdec(&(var), order)
#define OATOMIC_ADD(var, value, order)                       __hybrid_atomic_add(&(var), value, order)
#define OATOMIC_SUB(var, value, order)                       __hybrid_atomic_sub(&(var), value, order)
#define OATOMIC_AND(var, value, order)                       __hybrid_atomic_and(&(var), value, order)
#define OATOMIC_OR(var, value, order)                        __hybrid_atomic_or(&(var), value, order)
#define OATOMIC_XOR(var, value, order)                       __hybrid_atomic_xor(&(var), value, order)
#define OATOMIC_NAND(var, value, order)                      __hybrid_atomic_nand(&(var), value, order)
#define OATOMIC_INC(var, order)                              __hybrid_atomic_inc(&(var), order)
#define OATOMIC_DEC(var, order)                              __hybrid_atomic_dec(&(var), order)

#define ATOMIC_LOAD(var)                    OATOMIC_LOAD(var, __ATOMIC_SEQ_CST)
#define ATOMIC_STORE(var, value)            OATOMIC_STORE(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XCH(var, value)              OATOMIC_XCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH(var, oldv, newv)      OATOMIC_CMPXCH(var, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_WEAK(var, oldv, newv) OATOMIC_CMPXCH_WEAK(var, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_CMPXCH_VAL(var, oldv, newv)  OATOMIC_CMPXCH_VAL(var, oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_ADDFETCH(var, value)         OATOMIC_ADDFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_SUBFETCH(var, value)         OATOMIC_SUBFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_ANDFETCH(var, value)         OATOMIC_ANDFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_ORFETCH(var, value)          OATOMIC_ORFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XORFETCH(var, value)         OATOMIC_XORFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_NANDFETCH(var, value)        OATOMIC_NANDFETCH(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_INCFETCH(var)                OATOMIC_INCFETCH(var, __ATOMIC_SEQ_CST)
#define ATOMIC_DECFETCH(var)                OATOMIC_DECFETCH(var, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHADD(var, value)         OATOMIC_FETCHADD(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHSUB(var, value)         OATOMIC_FETCHSUB(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHAND(var, value)         OATOMIC_FETCHAND(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHOR(var, value)          OATOMIC_FETCHOR(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHXOR(var, value)         OATOMIC_FETCHXOR(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHNAND(var, value)        OATOMIC_FETCHNAND(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHINC(var)                OATOMIC_FETCHINC(var, __ATOMIC_SEQ_CST)
#define ATOMIC_FETCHDEC(var)                OATOMIC_FETCHDEC(var, __ATOMIC_SEQ_CST)
#define ATOMIC_ADD(var, value)              OATOMIC_ADD(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_SUB(var, value)              OATOMIC_SUB(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_AND(var, value)              OATOMIC_AND(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_OR(var, value)               OATOMIC_OR(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_XOR(var, value)              OATOMIC_XOR(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_NAND(var, value)             OATOMIC_NAND(var, value, __ATOMIC_SEQ_CST)
#define ATOMIC_INC(var)                     OATOMIC_INC(var, __ATOMIC_SEQ_CST)
#define ATOMIC_DEC(var)                     OATOMIC_DEC(var, __ATOMIC_SEQ_CST)

/* Simplified atomic read/write  functions that only  guaranty correct  ordering
 * of  reads/writes respectively,  as well as  that reads and  writes are always
 * completed  as a whole (i.e. reading a 64-bit value is always done in a single
 * instruction, preventing  the possibility  of some  part of  a value  changing
 * after it had already been read, but before all other parts were read as well) */
#define ATOMIC_READ(var)         OATOMIC_LOAD(var, __ATOMIC_ACQUIRE)
#define ATOMIC_WRITE(var, value) OATOMIC_STORE(var, value, __ATOMIC_RELEASE)

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_ATOMIC_H */
