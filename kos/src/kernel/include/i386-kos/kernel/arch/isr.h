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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#define ISR_VECTOR_INVALID   0xef /* APIC spurious */
#ifdef __CC__
typedef u8 isr_vector_t;
#endif /* __CC__ */

/* On X86, we have a _lot_ of general purpose ISR vectors available.
 * But to prevent confusion, the  following are the ranges that  are
 * reserved for special purposes:
 *     0x00 ... 0x1f  -  CPU Exceptions
 *     0x20 ... 0x2f  -  Special interrupts reserved for windows compatibility
 *     0x80           -  System call
 *     0xee           -  APIC IPI
 *     0xef           -  APIC spurious
 *     0xf0           -  Preemptive interrupt
 *     0xf1 ... 0xff  -  PIC #1/#2 interrupts
 * With that in mind, we declare vectors as follows:
 *   - Generic vectors are  0x81 ... 0xed
 *   - Specific vectors are 0xf1 ... 0xff
 *   - Vectors below 0x80, but above exceptions are unused / used for windows compatibility
 * Which leaves the following ranges as undefined:
 *   - 0x30 ... 0x7f
 */
#define ISR_GENERIC_VECTOR_COUNT  0x6d
#define ISR_SPECIFIC_VECTOR_COUNT 0x0f
#define ISR_VECTOR_IS_VALID(vec)  (((vec) >= 0xf1 && (vec) <= 0xff) || ((vec) >= 0x81 && (vec) <= 0xed))
#define ISR_VECTOR_TO_INDEX(vec)  ((vec) >= 0xf1 ? (ISR_GENERIC_VECTOR_COUNT+((vec)-0xf1)) : (vec)-0x81)
#define ISR_INDEX_TO_VECTOR(idx)  ((idx) >= ISR_GENERIC_VECTOR_COUNT ? 0xf1+((idx)-ISR_GENERIC_VECTOR_COUNT) : 0x81+(idx))

#define ISR_GENERIC_VECTOR_ENUM(func)   \
	func(00) func(01) func(02) func(03) \
	func(04) func(05) func(06) func(07) \
	func(08) func(09) func(0a) func(0b) \
	func(0c) func(0d) func(0e) func(0f) \
	func(10) func(11) func(12) func(13) \
	func(14) func(15) func(16) func(17) \
	func(18) func(19) func(1a) func(1b) \
	func(1c) func(1d) func(1e) func(1f) \
	func(20) func(21) func(22) func(23) \
	func(24) func(25) func(26) func(27) \
	func(28) func(29) func(2a) func(2b) \
	func(2c) func(2d) func(2e) func(2f) \
	func(30) func(31) func(32) func(33) \
	func(34) func(35) func(36) func(37) \
	func(38) func(39) func(3a) func(3b) \
	func(3c) func(3d) func(3e) func(3f) \
	func(40) func(41) func(42) func(43) \
	func(44) func(45) func(46) func(47) \
	func(48) func(49) func(4a) func(4b) \
	func(4c) func(4d) func(4e) func(4f) \
	func(50) func(51) func(52) func(53) \
	func(54) func(55) func(56) func(57) \
	func(58) func(59) func(5a) func(5b) \
	func(5c) func(5d) func(5e) func(5f) \
	func(60) func(61) func(62) func(63) \
	func(64) func(65) func(66) func(67) \
	func(68) func(69) func(6a) func(6b) \
	func(6c)
#define ISR_SPECIFIC_VECTOR_ENUM(func)  \
	/*    */ func(00) func(01) func(02) \
	func(03) func(04) func(05) func(06) \
	func(07) func(08) func(09) func(0a) \
	func(0b) func(0c) func(0d) func(0e)

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_H */
