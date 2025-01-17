/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_ASM_REDIRECT_H
#define _ARM_KOS_ASM_REDIRECT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* T2 encoding */
#define __arm_redirect_t2_delta(from_pc, to_pc) ((__BYTE_TYPE__ *)(to_pc) - (__BYTE_TYPE__ *)((from_pc) + 4))
#define __arm_redirect_t2_possible(from_pc, to_pc)       \
	(__arm_redirect_t2_delta(from_pc, to_pc) >= -2048 && \
	 __arm_redirect_t2_delta(from_pc, to_pc) <= 2046)
#define __arm_redirect_t2(from_pc, to_pc)                                                    \
	(void)(*(__UINT16_TYPE__ *)(from_pc) = __UINT16_C(0xe000) |                              \
	                                       ((__arm_redirect_t2_delta(from_pc, to_pc) >> 1) & \
	                                        __UINT16_C(0x07ff)))

/* T4 encoding */
#define __arm_redirect_t4_delta(from_pc, to_pc) ((__BYTE_TYPE__ *)(to_pc) - (__BYTE_TYPE__ *)((from_pc) + 4))
#define __arm_redirect_t4_possible(from_pc, to_pc)           \
	(__arm_redirect_t4_delta(from_pc, to_pc) >= -16777216 && \
	 __arm_redirect_t4_delta(from_pc, to_pc) <= 16777214)
#define __arm_redirect_t4(from_pc, to_pc)                                                                               \
	(void)(((__UINT16_TYPE__ *)(from_pc))[0] = __UINT16_C(0xf000) |                                                     \
	                                           ((__arm_redirect_t4_delta(from_pc, to_pc) >> 12) & __UINT16_C(0x03ff)) | \
	                                           (((__arm_redirect_t4_delta(from_pc, to_pc) >> 24) & 1) << 10),           \
	       ((__UINT16_TYPE__ *)(from_pc))[1] = __UINT16_C(0x9000) |                                                     \
	                                           ((__arm_redirect_t4_delta(from_pc, to_pc) >> 1) & __UINT16_C(0x07ff)) |  \
	                                           (((__arm_redirect_t4_delta(from_pc, to_pc) >> 23) & 1) << 13) |          \
	                                           (((__arm_redirect_t4_delta(from_pc, to_pc) >> 22) & 1) << 11))

/* A1 encoding */
#define __arm_redirect_a1_delta(from_pc, to_pc) ((__BYTE_TYPE__ *)(to_pc) - (__BYTE_TYPE__ *)((from_pc) + 8))
#define __arm_redirect_a1_possible(from_pc, to_pc)           \
	(__arm_redirect_a1_delta(from_pc, to_pc) >= -33554432 && \
	 __arm_redirect_a1_delta(from_pc, to_pc) <= 33554428)
#define __arm_redirect_a1(from_pc, to_pc)                           \
	(void)(*(__UINT32_TYPE__ *)(from_pc) = __UINT32_C(0xea000000) | \
	                                       ((__arm_redirect_a1_delta(from_pc, to_pc) >> 2) & __UINT32_C(0x00ffffff)))

/* Auto-select encoding for thumb */
#define __arm_redirect_thumb(from_pc, to_pc)    \
	(__arm_redirect_t2_possible(from_pc, to_pc) \
	 ? __arm_redirect_t2(from_pc, to_pc)        \
	 : __arm_redirect_t4(from_pc, to_pc))
#define __arm_redirect_thumb_size(from_pc, to_pc) \
	(__arm_redirect_t2_possible(from_pc, to_pc) ? 2 : 4)
#define __arm_redirect_thumb_possible(from_pc, to_pc) \
	__arm_redirect_t4_possible(from_pc, to_pc)

/* Define portable redirect macros.
 * WARNING: Because of the thumb vs. arm problem, we expose the macros for  whatever
 *          the user's current code is being compiled for. If this is incorrect, you
 *          will have to use the arm-specific macros defined above. */
#ifdef __thumb__
#define __arch_redirect          __arm_redirect_thumb
#define __arch_redirect_possible __arm_redirect_thumb_possible
#define __arch_redirect_size     __arm_redirect_thumb_size
#else /* __thumb__ */
#define __arch_redirect                      __arm_redirect_a1
#define __arch_redirect_possible             __arm_redirect_a1_possible
#define __arch_redirect_size(from_pc, to_pc) 4
#endif /* !__thumb__ */

/* Both ARM and THUMB encodings need up to 4 bytes */
#define __ARCH_REDIRECT_MAXBYTES 4

#endif /* !_ARM_KOS_ASM_REDIRECT_H */
