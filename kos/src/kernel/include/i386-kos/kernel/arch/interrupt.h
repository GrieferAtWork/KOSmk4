/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_INTERRUPT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_INTERRUPT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#define ISR_VECTOR_INVALID   0xef /* APIC spurious */
#ifdef __CC__
typedef u8 isr_vector_t;
#endif /* __CC__ */

/* On X86, we have a _lot_ of general purpose ISR vectors available.
 * But to prevent confusion, the following are the ranges that are
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
 */
#define ISR_GENERIC_VECTOR_COUNT   0x6d
#define ISR_SPECIFIC_VECTOR_COUNT  0x0f
#define ISR_VECTOR_IS_VALID(vec)  (((vec) >= 0xf1 && (vec) <= 0xff) || ((vec) >= 0x81 && (vec) <= 0xed))
#define ISR_VECTOR_TO_INDEX(vec)  ((vec) >= 0xf1 ? (ISR_GENERIC_VECTOR_COUNT+((vec)-0xf1)) : (vec)-0x81)
#define ISR_INDEX_TO_VECTOR(idx)  ((idx) >= ISR_GENERIC_VECTOR_COUNT ? 0xf1+((idx)-ISR_GENERIC_VECTOR_COUNT) : 0x81+(idx))

#define ISR_GENERIC_VECTOR_ENUM(func) \
	func(0x00, 81) func(0x01, 82) func(0x02, 83) func(0x03, 84) \
	func(0x04, 85) func(0x05, 86) func(0x06, 87) func(0x07, 88) \
	func(0x08, 89) func(0x09, 8a) func(0x0a, 8b) func(0x0b, 8c) \
	func(0x0c, 8d) func(0x0d, 8e) func(0x0e, 8f) func(0x0f, 90) \
	func(0x10, 91) func(0x11, 92) func(0x12, 93) func(0x13, 94) \
	func(0x14, 95) func(0x15, 96) func(0x16, 97) func(0x17, 98) \
	func(0x18, 99) func(0x19, 9a) func(0x1a, 9b) func(0x1b, 9c) \
	func(0x1c, 9d) func(0x1d, 9e) func(0x1e, 9f) func(0x1f, a0) \
	func(0x20, a1) func(0x21, a2) func(0x22, a3) func(0x23, a4) \
	func(0x24, a5) func(0x25, a6) func(0x26, a7) func(0x27, a8) \
	func(0x28, a9) func(0x29, aa) func(0x2a, ab) func(0x2b, ac) \
	func(0x2c, ad) func(0x2d, ae) func(0x2e, af) func(0x2f, b0) \
	func(0x30, b1) func(0x31, b2) func(0x32, b3) func(0x33, b4) \
	func(0x34, b5) func(0x35, b6) func(0x36, b7) func(0x37, b8) \
	func(0x38, b9) func(0x39, ba) func(0x3a, bb) func(0x3b, bc) \
	func(0x3c, bd) func(0x3d, be) func(0x3e, bf) func(0x3f, c0) \
	func(0x40, c1) func(0x41, c2) func(0x42, c3) func(0x43, c4) \
	func(0x44, c5) func(0x45, c6) func(0x46, c7) func(0x47, c8) \
	func(0x48, c9) func(0x49, ca) func(0x4a, cb) func(0x4b, cc) \
	func(0x4c, cd) func(0x4d, ce) func(0x4e, cf) func(0x4f, d0) \
	func(0x50, d1) func(0x51, d2) func(0x52, d3) func(0x53, d4) \
	func(0x54, d5) func(0x55, d6) func(0x56, d7) func(0x57, d8) \
	func(0x58, d9) func(0x59, da) func(0x5a, db) func(0x5b, dc) \
	func(0x5c, dd) func(0x5d, de) func(0x5e, df) func(0x5f, e0) \
	func(0x60, e1) func(0x61, e2) func(0x62, e3) func(0x63, e4) \
	func(0x64, e5) func(0x65, e6) func(0x66, e7) func(0x67, e8) \
	func(0x68, e9) func(0x69, ea) func(0x6a, eb) func(0x6b, ec) \
	func(0x6c, ed) \
/**/
#define ISR_SPECIFIC_VECTOR_ENUM(func) \
	/*          */ func(0x00, f1) func(0x01, f2) func(0x02, f3) \
	func(0x03, f4) func(0x04, f5) func(0x05, f6) func(0x06, f7) \
	func(0x07, f8) func(0x08, f9) func(0x09, fa) func(0x0a, fb) \
	func(0x0b, fc) func(0x0c, fd) func(0x0d, fe) func(0x0e, ff) \
/**/

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_INTERRUPT_H */
