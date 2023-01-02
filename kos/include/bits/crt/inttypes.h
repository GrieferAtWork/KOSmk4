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
#ifndef _BITS_CRT_INTTYPES_H
#define _BITS_CRT_INTTYPES_H 1

#include <__stdinc.h>
#include <__crt.h>

#include <hybrid/typecore.h>
#include <hybrid/__va_size.h> /* __VA_SIZE */

/* Since   `__VA_SIZE >= sizeof(int)',   and   `sizeof(int) != 0',
 * we also  know that  `__VA_SIZE >= 1',  meaning that  any  8-bit
 * data word will _always_ be promoted to an int, meaning in order
 * to  print an 8-bit data word we  never need any sort of prefix! */
#ifndef __PRI1_PREFIX
#define __PRI1_PREFIX /* nothing */
#endif /* !__PRI1_PREFIX */

#ifndef __PRI2_PREFIX
#if __VA_SIZE >= 2
#define __PRI2_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 2
#define __PRI2_PREFIX "l"
#elif __SIZEOF_SHORT__ == 2
#define __PRI2_PREFIX "h"
#elif (__SIZEOF_POINTER__ == 2 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI2_PREFIX "I"
#elif __SIZEOF_CHAR__ == 2
#define __PRI2_PREFIX "hh"
#elif __SIZEOF_LONG_LONG__ == 2
#define __PRI2_PREFIX "ll"
#else /* ... == 2 */
#define __PRI2_PREFIX "I16" /* XXX: non-portable */
#endif /* ... != 2 */
#endif /* !__PRI2_PREFIX */

#ifndef __PRI4_PREFIX
#if __VA_SIZE >= 4
#define __PRI4_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 4
#define __PRI4_PREFIX "l"
#elif __SIZEOF_SHORT__ == 4
#define __PRI4_PREFIX "h"
#elif (__SIZEOF_POINTER__ == 4 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI4_PREFIX "I"
#elif __SIZEOF_CHAR__ == 4
#define __PRI4_PREFIX "hh"
#elif __SIZEOF_LONG_LONG__ == 4
#define __PRI4_PREFIX "ll"
#else /* ... == 4 */
#define __PRI4_PREFIX "I32" /* XXX: non-portable */
#endif /* ... != 4 */
#endif /* !__PRI4_PREFIX */

#ifndef __PRI8_PREFIX
#if __VA_SIZE >= 8
#define __PRI8_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 8
#define __PRI8_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == 8
#define __PRI8_PREFIX "j"
#elif (__SIZEOF_POINTER__ == 8 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI8_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 8
#define __PRI8_PREFIX "ll"
#else /* ... == 8 */
#define __PRI8_PREFIX "I64" /* XXX: non-portable */
#endif /* ... != 8 */
#endif /* !__PRI8_PREFIX */

#ifndef __PRIP_PREFIX
#if __VA_SIZE >= __SIZEOF_POINTER__
#define __PRIP_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == __SIZEOF_POINTER__
#define __PRIP_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_POINTER__
#define __PRIP_PREFIX "j"
#elif defined(__CRT_KOS) || defined(__CRT_DOS)
#define __PRIP_PREFIX "I"
#endif /* ... */
#endif /* !__PRIP_PREFIX */

#define __PRIN2_PREFIX(n) __PRI##n##_PREFIX
#define __PRIN_PREFIX(n)  __PRIN2_PREFIX(n)

#define __PRIL1_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST8_T__)
#define __PRIL2_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST16_T__)
#define __PRIL4_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST32_T__)
#define __PRIL8_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST64_T__)
#define __PRIF1_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST8_T__)
#define __PRIF2_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST16_T__)
#define __PRIF4_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST32_T__)
#define __PRIF8_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST64_T__)


#ifdef __CRT_KOS /* FEATURE: CRT's printf() supports fixed-length pointers */
#if __SIZEOF_POINTER__ == 1
#define __PRINP_1 "p"
#elif __SIZEOF_LONG__ == 1
#define __PRINP_1 "lp"
#elif __SIZEOF_SHORT__ == 1
#define __PRINP_1 "hp"
#elif __SIZEOF_INTMAX_T__ == 1
#define __PRINP_1 "jp"
#elif __SIZEOF_CHAR__ == 1
#define __PRINP_1 "hhp"
#elif __SIZEOF_LONG_LONG__ == 1
#define __PRINP_1 "llp"
#else /* ... == 1 */
#define __PRINP_1 "I8p"
#endif /* ... != 1 */

#if __SIZEOF_POINTER__ == 2
#define __PRINP_2 "p"
#elif __SIZEOF_LONG__ == 2
#define __PRINP_2 "lp"
#elif __SIZEOF_SHORT__ == 2
#define __PRINP_2 "hp"
#elif __SIZEOF_INTMAX_T__ == 2
#define __PRINP_2 "jp"
#elif __SIZEOF_CHAR__ == 2
#define __PRINP_2 "hhp"
#elif __SIZEOF_LONG_LONG__ == 2
#define __PRINP_2 "llp"
#else /* ... == 2 */
#define __PRINP_2 "I16p"
#endif /* ... != 2 */

#if __SIZEOF_POINTER__ == 4
#define __PRINP_4 "p"
#elif __SIZEOF_LONG__ == 4
#define __PRINP_4 "lp"
#elif __SIZEOF_SHORT__ == 4
#define __PRINP_4 "hp"
#elif __SIZEOF_INTMAX_T__ == 4
#define __PRINP_4 "jp"
#elif __SIZEOF_CHAR__ == 4
#define __PRINP_4 "hhp"
#elif __SIZEOF_LONG_LONG__ == 4
#define __PRINP_4 "llp"
#else /* ... == 4 */
#define __PRINP_4 "I32p"
#endif /* ... != 4 */

#if __SIZEOF_POINTER__ == 8
#define __PRINP_8 "p"
#elif __SIZEOF_LONG__ == 8
#define __PRINP_8 "lp"
#elif __SIZEOF_SHORT__ == 8
#define __PRINP_8 "hp"
#elif __SIZEOF_INTMAX_T__ == 8
#define __PRINP_8 "jp"
#elif __SIZEOF_CHAR__ == 8
#define __PRINP_8 "hhp"
#elif __SIZEOF_LONG_LONG__ == 8
#define __PRINP_8 "llp"
#else /* ... == 8 */
#define __PRINP_8 "I64p"
#endif /* ... != 8 */

#else /* __CRT_KOS */

#ifdef __PRI1_PREFIX
#define __PRINP_1 ".2" __PRI1_PREFIX "X"
#endif /* __PRI1_PREFIX */
#ifdef __PRI2_PREFIX
#define __PRINP_2 ".4" __PRI2_PREFIX "X"
#endif /* __PRI2_PREFIX */
#ifdef __PRI4_PREFIX
#define __PRINP_4 ".8" __PRI4_PREFIX "X"
#endif /* __PRI4_PREFIX */
#ifdef __PRI8_PREFIX
#define __PRINP_8 ".16" __PRI8_PREFIX "X"
#endif /* __PRI8_PREFIX */

#endif /* !__CRT_KOS */


#define __PRINP2(n) __PRINP_##n
#define __PRINP(n) __PRINP2(n)


#ifndef __SCA1_PREFIX
#if __SIZEOF_INT__ == 1
#define __SCA1_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 1
#define __SCA1_PREFIX "h"
#elif __SIZEOF_CHAR__ == 1
#define __SCA1_PREFIX "hh"
#else /* ... == 1 */
#define __SCA1_PREFIX "I8"
#endif /* ... != 1 */
#endif /* !__SCA1_PREFIX */

#ifndef __SCA2_PREFIX
#if __SIZEOF_INT__ == 2
#define __SCA2_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 2
#define __SCA2_PREFIX "h"
#elif __SIZEOF_LONG__ == 2
#define __SCA2_PREFIX "l"
#elif __SIZEOF_POINTER__ == 2
#define __SCA2_PREFIX "I"
#else /* ... == 2 */
#define __SCA2_PREFIX "I16"
#endif /* ... != 2 */
#endif /* !__SCA2_PREFIX */

#ifndef __SCA4_PREFIX
#if __SIZEOF_INT__ == 4
#define __SCA4_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 4
#define __SCA4_PREFIX "h"
#elif __SIZEOF_LONG__ == 4
#define __SCA4_PREFIX "l"
#elif __SIZEOF_POINTER__ == 4 && \
     (defined(__CRT_KOS) || defined(__CRT_DOS))
#define __SCA4_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 4
#define __SCA4_PREFIX "ll"
#else /* ... == 4 */
#define __SCA4_PREFIX "I32"
#endif /* ... != 4 */
#endif /* !__SCA4_PREFIX */

#ifndef __SCA8_PREFIX
#if __SIZEOF_INT__ == 8
#define __SCA8_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 8
#define __SCA8_PREFIX "h"
#elif __SIZEOF_LONG__ == 8
#define __SCA8_PREFIX "l"
#elif __SIZEOF_POINTER__ == 8 && \
     (defined(__CRT_KOS) || defined(__CRT_DOS))
#define __SCA8_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 8
#define __SCA8_PREFIX "ll"
#else /* ... == 8 */
#define __SCA8_PREFIX "I64"
#endif /* ... != 8 */
#endif /* !__SCA8_PREFIX */

#ifndef __SCAP_PREFIX
#if __SIZEOF_INT__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX "j"
#else /* ... == __SIZEOF_POINTER__ */
#define __SCAP_PREFIX "I"
#endif /* ... != __SIZEOF_POINTER__ */
#endif /* !__SCAP_PREFIX */

#define __SCAN2_PREFIX(n) __SCA##n##_PREFIX
#define __SCAN_PREFIX(n)  __SCAN2_PREFIX(n)
#ifdef __SIZEOF_INT_LEAST8_T__
#define __SCAL1_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST8_T__)
#endif /* __SIZEOF_INT_LEAST8_T__ */
#ifdef __SIZEOF_INT_LEAST16_T__
#define __SCAL2_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST16_T__)
#endif /* __SIZEOF_INT_LEAST16_T__ */
#ifdef __SIZEOF_INT_LEAST32_T__
#define __SCAL4_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST32_T__)
#endif /* __SIZEOF_INT_LEAST32_T__ */
#ifdef __SIZEOF_INT_LEAST64_T__
#define __SCAL8_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */
#ifdef __SIZEOF_INT_FAST8_T__
#define __SCAF1_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST8_T__)
#endif /* __SIZEOF_INT_FAST8_T__ */
#ifdef __SIZEOF_INT_FAST16_T__
#define __SCAF2_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST16_T__)
#endif /* __SIZEOF_INT_FAST16_T__ */
#ifdef __SIZEOF_INT_FAST32_T__
#define __SCAF4_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST32_T__)
#endif /* __SIZEOF_INT_FAST32_T__ */
#ifdef __SIZEOF_INT_FAST64_T__
#define __SCAF8_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */

#endif /* !_BITS_CRT_INTTYPES_H */
