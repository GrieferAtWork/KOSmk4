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
/* (#) Portability: NetBSD      (/sys/sys/atomic.h) */
/* (#) Portability: OpenBSD     (/sys/sys/atomic.h) */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/atomic.h) */
/* (#) Portability: diet libc   (/include/sys/atomic.h) */
#ifndef _SYS_ATOMIC_H
#define _SYS_ATOMIC_H 1

#include <__stdinc.h>

#include <hybrid/__atomic.h>

#include <sys/inttypes.h>
#include <sys/types.h>

/************************************************************************/
/* From BSD/Solaris (with a couple of extensions)                       */
#define atomic_inc_8(p)                      __hybrid_atomic_inc((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_16(p)                     __hybrid_atomic_inc((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_32(p)                     __hybrid_atomic_inc((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_uchar(p)                  __hybrid_atomic_inc((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_ushort(p)                 __hybrid_atomic_inc((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_uint(p)                   __hybrid_atomic_inc((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_ulong(p)                  __hybrid_atomic_inc((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_char(p)                   __hybrid_atomic_inc((unsigned char *)__COMPILER_REQTYPE(signed char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_short(p)                  __hybrid_atomic_inc((unsigned short *)__COMPILER_REQTYPE(short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_int(p)                    __hybrid_atomic_inc((unsigned int *)__COMPILER_REQTYPE(int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_long(p)                   __hybrid_atomic_inc((unsigned long *)__COMPILER_REQTYPE(long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_8(p)                      __hybrid_atomic_dec((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_16(p)                     __hybrid_atomic_dec((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_32(p)                     __hybrid_atomic_dec((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_uchar(p)                  __hybrid_atomic_dec((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_ushort(p)                 __hybrid_atomic_dec((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_uint(p)                   __hybrid_atomic_dec((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_ulong(p)                  __hybrid_atomic_dec((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_char(p)                   __hybrid_atomic_dec((unsigned char *)__COMPILER_REQTYPE(signed char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_short(p)                  __hybrid_atomic_dec((unsigned short *)__COMPILER_REQTYPE(short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_int(p)                    __hybrid_atomic_dec((unsigned int *)__COMPILER_REQTYPE(int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_long(p)                   __hybrid_atomic_dec((unsigned long *)__COMPILER_REQTYPE(long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_add_8(p, v)                   __hybrid_atomic_add((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(__INT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_16(p, v)                  __hybrid_atomic_add((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(__INT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_32(p, v)                  __hybrid_atomic_add((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(__INT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_char(p, v)                __hybrid_atomic_add((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(signed char)(v), __ATOMIC_SEQ_CST)
#define atomic_add_short(p, v)               __hybrid_atomic_add((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(short)(v), __ATOMIC_SEQ_CST)
#define atomic_add_int(p, v)                 __hybrid_atomic_add((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(int)(v), __ATOMIC_SEQ_CST)
#define atomic_add_long(p, v)                __hybrid_atomic_add((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(long)(v), __ATOMIC_SEQ_CST)
#define atomic_add_ptr(p, v)                 __hybrid_atomic_add((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(__INTPTR_TYPE__)(__SSIZE_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_8(p, v)                   __hybrid_atomic_sub((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(__INT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_16(p, v)                  __hybrid_atomic_sub((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(__INT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_32(p, v)                  __hybrid_atomic_sub((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(__INT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_char(p, v)                __hybrid_atomic_sub((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(signed char)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_short(p, v)               __hybrid_atomic_sub((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(short)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_int(p, v)                 __hybrid_atomic_sub((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(int)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_long(p, v)                __hybrid_atomic_sub((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(long)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_ptr(p, v)                 __hybrid_atomic_sub((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(__INTPTR_TYPE__)(__SSIZE_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_8(p, v)                    __hybrid_atomic_or((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_16(p, v)                   __hybrid_atomic_or((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_32(p, v)                   __hybrid_atomic_or((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_uchar(p, v)                __hybrid_atomic_or((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(v), __ATOMIC_SEQ_CST)
#define atomic_or_ushort(p, v)               __hybrid_atomic_or((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(v), __ATOMIC_SEQ_CST)
#define atomic_or_uint(p, v)                 __hybrid_atomic_or((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(v), __ATOMIC_SEQ_CST)
#define atomic_or_ulong(p, v)                __hybrid_atomic_or((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(v), __ATOMIC_SEQ_CST)
#define atomic_and_8(p, v)                   __hybrid_atomic_and((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_16(p, v)                  __hybrid_atomic_and((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_32(p, v)                  __hybrid_atomic_and((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_uchar(p, v)               __hybrid_atomic_and((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(v), __ATOMIC_SEQ_CST)
#define atomic_and_ushort(p, v)              __hybrid_atomic_and((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(v), __ATOMIC_SEQ_CST)
#define atomic_and_uint(p, v)                __hybrid_atomic_and((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(v), __ATOMIC_SEQ_CST)
#define atomic_and_ulong(p, v)               __hybrid_atomic_and((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(v), __ATOMIC_SEQ_CST)
#define atomic_inc_8_nv(p)                   __hybrid_atomic_incfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_16_nv(p)                  __hybrid_atomic_incfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_32_nv(p)                  __hybrid_atomic_incfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_uchar_nv(p)               __hybrid_atomic_incfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_ushort_nv(p)              __hybrid_atomic_incfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_uint_nv(p)                __hybrid_atomic_incfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_ulong_nv(p)               __hybrid_atomic_incfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_char_nv(p)                __hybrid_atomic_incfetch((unsigned char *)__COMPILER_REQTYPE(signed char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_short_nv(p)               __hybrid_atomic_incfetch((unsigned short *)__COMPILER_REQTYPE(short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_int_nv(p)                 __hybrid_atomic_incfetch((unsigned int *)__COMPILER_REQTYPE(int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_inc_long_nv(p)                __hybrid_atomic_incfetch((unsigned long *)__COMPILER_REQTYPE(long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_8_nv(p)                   __hybrid_atomic_decfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_16_nv(p)                  __hybrid_atomic_decfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_32_nv(p)                  __hybrid_atomic_decfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_uchar_nv(p)               __hybrid_atomic_decfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_ushort_nv(p)              __hybrid_atomic_decfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_uint_nv(p)                __hybrid_atomic_decfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_ulong_nv(p)               __hybrid_atomic_decfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_char_nv(p)                __hybrid_atomic_decfetch((unsigned char *)__COMPILER_REQTYPE(signed char volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_short_nv(p)               __hybrid_atomic_decfetch((unsigned short *)__COMPILER_REQTYPE(short volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_int_nv(p)                 __hybrid_atomic_decfetch((unsigned int *)__COMPILER_REQTYPE(int volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_long_nv(p)                __hybrid_atomic_decfetch((unsigned long *)__COMPILER_REQTYPE(long volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_add_8_nv(p, v)                __hybrid_atomic_addfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(__INT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_16_nv(p, v)               __hybrid_atomic_addfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(__INT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_32_nv(p, v)               __hybrid_atomic_addfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(__INT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_add_char_nv(p, v)             __hybrid_atomic_addfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(signed char)(v), __ATOMIC_SEQ_CST)
#define atomic_add_short_nv(p, v)            __hybrid_atomic_addfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(short)(v), __ATOMIC_SEQ_CST)
#define atomic_add_int_nv(p, v)              __hybrid_atomic_addfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(int)(v), __ATOMIC_SEQ_CST)
#define atomic_add_long_nv(p, v)             __hybrid_atomic_addfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(long)(v), __ATOMIC_SEQ_CST)
#define atomic_add_ptr_nv(p, v)              ((void *)__hybrid_atomic_addfetch((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(__INTPTR_TYPE__)(__SSIZE_TYPE__)(v)), __ATOMIC_SEQ_CST)
#define atomic_sub_8_nv(p, v)                __hybrid_atomic_subfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(__INT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_16_nv(p, v)               __hybrid_atomic_subfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(__INT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_32_nv(p, v)               __hybrid_atomic_subfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(__INT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_char_nv(p, v)             __hybrid_atomic_subfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(signed char)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_short_nv(p, v)            __hybrid_atomic_subfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(short)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_int_nv(p, v)              __hybrid_atomic_subfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(int)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_long_nv(p, v)             __hybrid_atomic_subfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(long)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_ptr_nv(p, v)              ((void *)__hybrid_atomic_subfetch((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(__INTPTR_TYPE__)(__SSIZE_TYPE__)(v)), __ATOMIC_SEQ_CST)
#define atomic_or_8_nv(p, v)                 __hybrid_atomic_orfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_16_nv(p, v)                __hybrid_atomic_orfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_32_nv(p, v)                __hybrid_atomic_orfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_uchar_nv(p, v)             __hybrid_atomic_orfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(v), __ATOMIC_SEQ_CST)
#define atomic_or_ushort_nv(p, v)            __hybrid_atomic_orfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(v), __ATOMIC_SEQ_CST)
#define atomic_or_uint_nv(p, v)              __hybrid_atomic_orfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(v), __ATOMIC_SEQ_CST)
#define atomic_or_ulong_nv(p, v)             __hybrid_atomic_orfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(v), __ATOMIC_SEQ_CST)
#define atomic_and_8_nv(p, v)                __hybrid_atomic_andfetch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_16_nv(p, v)               __hybrid_atomic_andfetch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_32_nv(p, v)               __hybrid_atomic_andfetch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_uchar_nv(p, v)            __hybrid_atomic_andfetch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(v), __ATOMIC_SEQ_CST)
#define atomic_and_ushort_nv(p, v)           __hybrid_atomic_andfetch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(v), __ATOMIC_SEQ_CST)
#define atomic_and_uint_nv(p, v)             __hybrid_atomic_andfetch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(v), __ATOMIC_SEQ_CST)
#define atomic_and_ulong_nv(p, v)            __hybrid_atomic_andfetch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(v), __ATOMIC_SEQ_CST)
#define atomic_cas_8(p, oldval, newval)      __hybrid_atomic_cmpxch_val((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_16(p, oldval, newval)     __hybrid_atomic_cmpxch_val((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_32(p, oldval, newval)     __hybrid_atomic_cmpxch_val((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_uchar(p, oldval, newval)  __hybrid_atomic_cmpxch_val((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(oldval), (unsigned char)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_ushort(p, oldval, newval) __hybrid_atomic_cmpxch_val((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(oldval), (unsigned short)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_uint(p, oldval, newval)   __hybrid_atomic_cmpxch_val((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(oldval), (unsigned int)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_ulong(p, oldval, newval)  __hybrid_atomic_cmpxch_val((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(oldval), (unsigned long)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cas_ptr(p, oldval, newval)    ((void *)__hybrid_atomic_cmpxch_val((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(void *)(oldval), (__UINTPTR_TYPE__)(void *)(newval)), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_swap_8(p, v)                  __hybrid_atomic_xch((__UINT8_TYPE__ *)__COMPILER_REQTYPE(__UINT8_TYPE__ volatile *, p), (__UINT8_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_16(p, v)                 __hybrid_atomic_xch((__UINT16_TYPE__ *)__COMPILER_REQTYPE(__UINT16_TYPE__ volatile *, p), (__UINT16_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_32(p, v)                 __hybrid_atomic_xch((__UINT32_TYPE__ *)__COMPILER_REQTYPE(__UINT32_TYPE__ volatile *, p), (__UINT32_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_uchar(p, v)              __hybrid_atomic_xch((unsigned char *)__COMPILER_REQTYPE(unsigned char volatile *, p), (unsigned char)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_ushort(p, v)             __hybrid_atomic_xch((unsigned short *)__COMPILER_REQTYPE(unsigned short volatile *, p), (unsigned short)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_uint(p, v)               __hybrid_atomic_xch((unsigned int *)__COMPILER_REQTYPE(unsigned int volatile *, p), (unsigned int)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_ulong(p, v)              __hybrid_atomic_xch((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), (unsigned long)(v), __ATOMIC_SEQ_CST)
#define atomic_swap_ptr(p, v)                ((void *)__hybrid_atomic_xch((__UINTPTR_TYPE__ *)__COMPILER_REQTYPE(void volatile *, p), (__UINTPTR_TYPE__)(void *)(v)), __ATOMIC_SEQ_CST)

#if defined(__UINT64_TYPE__) && __HYBRID_ATOMIC_LOCKFREE(8)
#define atomic_inc_64(p)                 __hybrid_atomic_inc((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_64(p)                 __hybrid_atomic_dec((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_add_64(p, v)              __hybrid_atomic_add((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(__INT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_64(p, v)              __hybrid_atomic_sub((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(__INT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_64(p, v)               __hybrid_atomic_or((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_64(p, v)              __hybrid_atomic_and((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_inc_64_nv(p)              __hybrid_atomic_incfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_dec_64_nv(p)              __hybrid_atomic_decfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), __ATOMIC_SEQ_CST)
#define atomic_add_64_nv(p, v)           __hybrid_atomic_addfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(__INT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_sub_64_nv(p, v)           __hybrid_atomic_subfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(__INT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_or_64_nv(p, v)            __hybrid_atomic_orfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_and_64_nv(p, v)           __hybrid_atomic_andfetch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#define atomic_cas_64(p, oldval, newval) __hybrid_atomic_cmpxch_val((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(oldval), (__UINT64_TYPE__)(newval), __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_swap_64(p, v)             __hybrid_atomic_xch((__UINT64_TYPE__ *)__COMPILER_REQTYPE(__UINT64_TYPE__ volatile *, p), (__UINT64_TYPE__)(v), __ATOMIC_SEQ_CST)
#endif /* __UINT64_TYPE__ && __HYBRID_ATOMIC_LOCKFREE(8) */

#define atomic_set_long_excl(p, bitno)   (((__hybrid_atomic_fetchor((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), 1ul << (bitno), __ATOMIC_SEQ_CST) >> (bitno)) & 1) ? -1 : 0)
#define atomic_clear_long_excl(p, bitno) (((__hybrid_atomic_fetchand((unsigned long *)__COMPILER_REQTYPE(unsigned long volatile *, p), 1ul << (bitno), __ATOMIC_SEQ_CST) >> (bitno)) & 1) ? 0 : -1)

#define membar_enter()              __hybrid_atomic_signal_fence(__ATOMIC_ACQUIRE)
#define membar_exit()               __hybrid_atomic_signal_fence(__ATOMIC_RELEASE)
#define membar_producer()           __hybrid_atomic_signal_fence(__ATOMIC_ACQ_REL)
#define membar_consumer()           __hybrid_atomic_signal_fence(__ATOMIC_CONSUME)
#define membar_sync()               __hybrid_atomic_signal_fence(__ATOMIC_SEQ_CST)
#define membar_enter_after_atomic() membar_enter()
#define membar_exit_before_atomic() membar_exit()


/************************************************************************/
/* From dietlibc                                                        */
#define __CAS(p, oldval, newval)                                                        \
	__hybrid_atomic_cmpxch_val((__SIZE_TYPE__ *)__COMPILER_REQTYPE(__SIZE_TYPE__ *)(p), \
	                           (__SIZE_TYPE__)(oldval), (__SIZE_TYPE__)(newval),        \
	                           __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#ifdef __CC__
__DECL_BEGIN

/* Can't use a macro for this one because libstdc++ has internal functions called `__atomic_add' */
__FORCELOCAL __SIZE_TYPE__ (__atomic_add)(__SIZE_TYPE__ *__p, __SIZE_TYPE__ __val) {
	return __hybrid_atomic_fetchadd(__p, __val, __ATOMIC_SEQ_CST);
}

__DECL_END
#endif /* !__CC__ */


#endif /* !_SYS_ATOMIC_H */
