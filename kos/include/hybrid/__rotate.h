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
#ifndef __GUARD_HYBRID___ROTATE_H
#define __GUARD_HYBRID___ROTATE_H 1

#include "../__stdinc.h"
#include "typecore.h"

/* Compile-time constant implementations. */
#define __hybrid_rol8_c(x, shift)  (((x) >> (0x8 - ((shift) & 0x07))) | ((x) << ((shift) & 0x07)))
#define __hybrid_ror8_c(x, shift)  (((x) << (0x8 - ((shift) & 0x07))) | ((x) >> ((shift) & 0x07)))
#define __hybrid_rol16_c(x, shift) (((x) >> (0x10 - ((shift) & 0x0f))) | ((x) << ((shift) & 0x0f)))
#define __hybrid_ror16_c(x, shift) (((x) << (0x10 - ((shift) & 0x0f))) | ((x) >> ((shift) & 0x0f)))
#define __hybrid_rol32_c(x, shift) (((x) >> (0x20 - ((shift) & 0x1f))) | ((x) << ((shift) & 0x1f)))
#define __hybrid_ror32_c(x, shift) (((x) << (0x20 - ((shift) & 0x1f))) | ((x) >> ((shift) & 0x1f)))
#ifdef __UINT64_TYPE__
#define __hybrid_rol64_c(x, shift) (((x) >> (0x40 - ((shift) & 0x3f))) | ((x) << ((shift) & 0x3f)))
#define __hybrid_ror64_c(x, shift) (((x) << (0x40 - ((shift) & 0x3f))) | ((x) >> ((shift) & 0x3f)))
#ifdef __UINT128_TYPE__
#define __hybrid_rol128_c(x, shift) (((x) >> (0x80 - ((shift) & 0x7f))) | ((x) << ((shift) & 0x7f)))
#define __hybrid_ror128_c(x, shift) (((x) << (0x80 - ((shift) & 0x7f))) | ((x) >> ((shift) & 0x7f)))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

/* Arch/Compiler-specific runtime-optimized implementations. */
#if !defined(__hybrid_rol8_r) && __has_builtin(__builtin_rotateleft8)
#define __hybrid_rol8_r __builtin_rotateleft8
#endif /* !__hybrid_rol8_r && __has_builtin(__builtin_rotateleft8) */
#if !defined(__hybrid_rol16_r) && __has_builtin(__builtin_rotateleft16)
#define __hybrid_rol16_r __builtin_rotateleft16
#endif /* !__hybrid_rol16_r && __has_builtin(__builtin_rotateleft16) */
#if !defined(__hybrid_rol32_r) && __has_builtin(__builtin_rotateleft32)
#define __hybrid_rol32_r __builtin_rotateleft32
#endif /* !__hybrid_rol32_r && __has_builtin(__builtin_rotateleft32) */
#if !defined(__hybrid_rol64_r) && __has_builtin(__builtin_rotateleft64)
#define __hybrid_rol64_r __builtin_rotateleft64
#endif /* !__hybrid_rol64_r && __has_builtin(__builtin_rotateleft64) */
#if !defined(__hybrid_rol128_r) && __has_builtin(__builtin_rotateleft128)
#define __hybrid_rol128_r __builtin_rotateleft128
#endif /* !__hybrid_rol128_r && __has_builtin(__builtin_rotateleft128) */
#if !defined(__hybrid_ror8_r) && __has_builtin(__builtin_rotateright8)
#define __hybrid_ror8_r __builtin_rotateright8
#endif /* !__hybrid_ror8_r && __has_builtin(__builtin_rotateright8) */
#if !defined(__hybrid_ror16_r) && __has_builtin(__builtin_rotateright16)
#define __hybrid_ror16_r __builtin_rotateright16
#endif /* !__hybrid_ror16_r && __has_builtin(__builtin_rotateright16) */
#if !defined(__hybrid_ror32_r) && __has_builtin(__builtin_rotateright32)
#define __hybrid_ror32_r __builtin_rotateright32
#endif /* !__hybrid_ror32_r && __has_builtin(__builtin_rotateright32) */
#if !defined(__hybrid_ror64_r) && __has_builtin(__builtin_rotateright64)
#define __hybrid_ror64_r __builtin_rotateright64
#endif /* !__hybrid_ror64_r && __has_builtin(__builtin_rotateright64) */
#if !defined(__hybrid_ror128_r) && __has_builtin(__builtin_rotateright128)
#define __hybrid_ror128_r __builtin_rotateright128
#endif /* !__hybrid_ror128_r && __has_builtin(__builtin_rotateright128) */


#if defined(_MSC_VER) && defined(__CC__)
#include "host.h"
__DECL_BEGIN

#ifdef __x86_64__
#ifndef __hybrid_rol8_r
#define __hybrid_rol8_r _rotl8
#ifndef _rotl8
#define _rotl8 _rotl8
unsigned char __cdecl _rotl8(unsigned char __val, unsigned char __shift);
#pragma intrinsic(_rotl8)
#endif /* !_rotl8 */
#endif /* !__hybrid_rol8_r */

#ifndef __hybrid_ror8_r
#define __hybrid_ror8_r _rotr8
#ifndef _rotr8
#define _rotr8 _rotr8
unsigned char __cdecl _rotr8(unsigned char __val, unsigned char __shift);
#pragma intrinsic(_rotr8)
#endif /* !_rotr8 */
#endif /* !__hybrid_ror8_r */

#ifndef __hybrid_rol16_r
#define __hybrid_rol16_r _rotl16
#ifndef _rotl16
unsigned short __cdecl _rotl16(unsigned short __val, unsigned char __shift);
#pragma intrinsic(_rotl16)
#endif /* !_rotl16 */
#endif /* !__hybrid_rol16_r */

#ifndef __hybrid_ror16_r
#define __hybrid_ror16_r _rotr16
#ifndef _rotr16
#define _rotr16 _rotr16
unsigned short __cdecl _rotr16(unsigned short __val, unsigned char __shift);
#pragma intrinsic(_rotr16)
#endif /* !_rotr16 */
#endif /* __x86_64__ */
#endif /* !__hybrid_ror16_r */

#if _MSC_VER >= 1300
#ifndef __hybrid_rol32_r
#define __hybrid_rol32_r(val, shift) _rotl(val, (int)(__SHIFT_TYPE__)(shift))
#ifndef _rotl
#define _rotl _rotl
unsigned int __cdecl _rotl(unsigned int __val, int __shift);
#pragma intrinsic(_rotl)
#endif /* !_rotl */
#endif /* !__hybrid_rol32_r */

#ifndef __hybrid_ror32_r
#define __hybrid_ror32_r(val, shift) _rotr(val, (int)(__SHIFT_TYPE__)(shift))
#ifndef _rotr
#define _rotr _rotr
unsigned int __cdecl _rotr(unsigned int __val, int __shift);
#pragma intrinsic(_rotr)
#endif /* !_rotr */
#endif /* !__hybrid_ror32_r */

#ifndef __hybrid_rol64_r
#define __hybrid_rol64_r(val, shift) _rotl64(val, (int)(__SHIFT_TYPE__)(shift))
#ifndef _rotl64
#define _rotl64 _rotl64
unsigned __int64 __cdecl _rotl64(unsigned __int64 __val, int __shift);
#pragma intrinsic(_rotl64)
#endif /* !_rotl64 */
#endif /* !__hybrid_rol64_r */

#ifndef __hybrid_ror64_r
#define __hybrid_ror64_r(val, shift) _rotr64(val, (int)(__SHIFT_TYPE__)(shift))
#ifndef _rotr64
#define _rotr64 _rotr64
unsigned __int64 __cdecl _rotr64(unsigned __int64 __val, int __shift);
#pragma intrinsic(_rotr64)
#endif /* !_rotr64 */
#endif /* !__hybrid_ror64_r */
#endif  /* _MSC_VER >= 1300 */

__DECL_END
#endif /* _MSC_VER && __CC__ */

#if ((!defined(__hybrid_rol8_r) || !defined(__hybrid_rol16_r) ||  \
      !defined(__hybrid_rol32_r) || !defined(__hybrid_rol64_r) || \
      !defined(__hybrid_ror8_r) || !defined(__hybrid_ror16_r) ||  \
      !defined(__hybrid_ror32_r) || !defined(__hybrid_ror64_r)) && \
     defined(__COMPILER_HAVE_GCC_ASM) && defined(__CC__))
#include "host.h"

/* X86-specific inline-assembly implementation */
#if defined(__i386__) || defined(__x86_64__)
__DECL_BEGIN
__NAMESPACE_INT_BEGIN

/* `-fnon-call-exception' currently  requires  __asm__  to be  marked  as  volatile.
 * s.a. the following bug report: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94357 */
#ifndef __asm_ncx_memop__
#ifdef __NON_CALL_EXCEPTIONS
#define __asm_ncx_memop__ __asm__ __volatile__
#else /* __NON_CALL_EXCEPTIONS */
#define __asm_ncx_memop__ __asm__
#endif /* !__NON_CALL_EXCEPTIONS */
#endif /* !__asm_ncx_memop__ */

#ifndef __hybrid_rol8_r
#define __hybrid_rol8_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rolb(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW_NCX(__hybrid_x86_rolb)(__UINT8_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT8_TYPE__ __res;
	__asm_ncx_memop__("rolb %b1, %b0"
	                  : "=qm" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_rol8_r */

#ifndef __hybrid_ror8_r
#define __hybrid_ror8_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rorb(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW_NCX(__hybrid_x86_rorb)(__UINT8_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT8_TYPE__ __res;
	__asm_ncx_memop__("rorb %b1, %b0"
	                  : "=qm" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_ror8_r */

#ifndef __hybrid_rol16_r
#define __hybrid_rol16_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rolw(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT16_TYPE__
__NOTHROW_NCX(__hybrid_x86_rolw)(__UINT16_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT16_TYPE__ __res;
	__asm_ncx_memop__("rolw %b1, %w0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_rol16_r */

#ifndef __hybrid_ror16_r
#define __hybrid_ror16_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rorw(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT16_TYPE__
__NOTHROW_NCX(__hybrid_x86_rorw)(__UINT16_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT16_TYPE__ __res;
	__asm_ncx_memop__("rorw %b1, %w0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_ror16_r */

#ifndef __hybrid_rol32_r
#define __hybrid_rol32_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_roll(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__
__NOTHROW_NCX(__hybrid_x86_roll)(__UINT32_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT32_TYPE__ __res;
	__asm_ncx_memop__("roll %b1, %k0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_rol32_r */

#ifndef __hybrid_ror32_r
#define __hybrid_ror32_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rorl(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__
__NOTHROW_NCX(__hybrid_x86_rorl)(__UINT32_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT32_TYPE__ __res;
	__asm_ncx_memop__("rorl %b1, %k0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_ror32_r */

#if defined(__x86_64__) && defined(__UINT64_TYPE__)
#ifndef __hybrid_rol64_r
#define __hybrid_rol64_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rolq(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW_NCX(__hybrid_x86_rolq)(__UINT64_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT64_TYPE__ __res;
	__asm_ncx_memop__("rolq %b1, %q0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_rol64_r */

#ifndef __hybrid_ror64_r
#define __hybrid_ror64_r(x, shift) \
	__NAMESPACE_INT_SYM __hybrid_x86_rorq(x, (__SHIFT_TYPE__)(shift))
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW_NCX(__hybrid_x86_rorq)(__UINT64_TYPE__ __lhs, __SHIFT_TYPE__ __shift) {
	__UINT64_TYPE__ __res;
	__asm_ncx_memop__("rorq %b1, %q0"
	                  : "=g" (__res)
	                  : "Nc" (__shift)
	                  , "0" (__lhs)
	                  : "cc");
	return __res;
}
#endif /* !__hybrid_ror64_r */
#endif /* __x86_64__ && __UINT64_TYPE__ */

__NAMESPACE_INT_END
__DECL_END
#endif /* __i386__ || __x86_64__ */
#endif /* !__hybrid_ro[l|r][8|16|32|64]_r */



/*[[[deemon
function printRotateMacro(n, d) {
	local npad = { 1: "  ", 2: " ", 3: "" }[#n];
	print("#ifdef __hybrid_ro", d, n, "_r");
	print("#ifndef __NO_builtin_constant_p");
	print("#ifndef __NO_builtin_choose_expr");
	print("#define __hybrid_ro", d, n, "(x, shift)                                                 ", npad, "\\");
	print("	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \\");
	print("	                      __hybrid_ro", d, n, "_c(x, shift),                            ", npad, "\\");
	print("	                      __hybrid_ro", d, n, "_r(x, shift))");
	print("#else /" "* !__NO_builtin_choose_expr *" "/");
	print("#define __hybrid_ro", d, n, "(x, shift)                             ", npad, "\\");
	print("	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \\");
	print("	 ? __hybrid_ro", d, n, "_c(x, shift)                            ", npad, "\\");
	print("	 : __hybrid_ro", d, n, "_r(x, shift))");
	print("#endif /" "* __NO_builtin_choose_expr *" "/");
	print("#else /" "* !__NO_builtin_constant_p *" "/");
	print("#define __hybrid_ro", d, n, " __hybrid_ro", d, n, "_r");
	print("#endif /" "* __NO_builtin_constant_p *" "/");
	print("#else /" "* __hybrid_ro", d, n, "_r *" "/");
	print("#define __hybrid_ro", d, n, " __hybrid_ro", d, n, "_c");
	print("#endif /" "* !__hybrid_ro", d, n, "_r *" "/");
}

for (local n: ["8", "16", "32"]) {
	for (local d: ["l", "r"])
		printRotateMacro(n, d);
}
print("#ifdef __UINT64_TYPE__");
for (local d: ["l", "r"])
	printRotateMacro("64", d);
print("#ifdef __UINT128_TYPE__");
for (local d: ["l", "r"])
	printRotateMacro("128", d);
print("#endif /" "* __UINT128_TYPE__ *" "/");
print("#endif /" "* __UINT64_TYPE__ *" "/");
]]]*/
#ifdef __hybrid_rol8_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_rol8(x, shift)                                                   \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_rol8_c(x, shift),                              \
	                      __hybrid_rol8_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_rol8(x, shift)                               \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_rol8_c(x, shift)                              \
	 : __hybrid_rol8_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_rol8 __hybrid_rol8_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_rol8_r */
#define __hybrid_rol8 __hybrid_rol8_c
#endif /* !__hybrid_rol8_r */
#ifdef __hybrid_ror8_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_ror8(x, shift)                                                   \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_ror8_c(x, shift),                              \
	                      __hybrid_ror8_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ror8(x, shift)                               \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_ror8_c(x, shift)                              \
	 : __hybrid_ror8_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_ror8 __hybrid_ror8_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_ror8_r */
#define __hybrid_ror8 __hybrid_ror8_c
#endif /* !__hybrid_ror8_r */
#ifdef __hybrid_rol16_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_rol16(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_rol16_c(x, shift),                             \
	                      __hybrid_rol16_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_rol16(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_rol16_c(x, shift)                             \
	 : __hybrid_rol16_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_rol16 __hybrid_rol16_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_rol16_r */
#define __hybrid_rol16 __hybrid_rol16_c
#endif /* !__hybrid_rol16_r */
#ifdef __hybrid_ror16_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_ror16(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_ror16_c(x, shift),                             \
	                      __hybrid_ror16_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ror16(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_ror16_c(x, shift)                             \
	 : __hybrid_ror16_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_ror16 __hybrid_ror16_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_ror16_r */
#define __hybrid_ror16 __hybrid_ror16_c
#endif /* !__hybrid_ror16_r */
#ifdef __hybrid_rol32_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_rol32(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_rol32_c(x, shift),                             \
	                      __hybrid_rol32_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_rol32(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_rol32_c(x, shift)                             \
	 : __hybrid_rol32_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_rol32 __hybrid_rol32_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_rol32_r */
#define __hybrid_rol32 __hybrid_rol32_c
#endif /* !__hybrid_rol32_r */
#ifdef __hybrid_ror32_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_ror32(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_ror32_c(x, shift),                             \
	                      __hybrid_ror32_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ror32(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_ror32_c(x, shift)                             \
	 : __hybrid_ror32_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_ror32 __hybrid_ror32_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_ror32_r */
#define __hybrid_ror32 __hybrid_ror32_c
#endif /* !__hybrid_ror32_r */
#ifdef __UINT64_TYPE__
#ifdef __hybrid_rol64_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_rol64(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_rol64_c(x, shift),                             \
	                      __hybrid_rol64_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_rol64(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_rol64_c(x, shift)                             \
	 : __hybrid_rol64_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_rol64 __hybrid_rol64_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_rol64_r */
#define __hybrid_rol64 __hybrid_rol64_c
#endif /* !__hybrid_rol64_r */
#ifdef __hybrid_ror64_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_ror64(x, shift)                                                  \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_ror64_c(x, shift),                             \
	                      __hybrid_ror64_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ror64(x, shift)                              \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_ror64_c(x, shift)                             \
	 : __hybrid_ror64_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_ror64 __hybrid_ror64_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_ror64_r */
#define __hybrid_ror64 __hybrid_ror64_c
#endif /* !__hybrid_ror64_r */
#ifdef __UINT128_TYPE__
#ifdef __hybrid_rol128_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_rol128(x, shift)                                                 \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_rol128_c(x, shift),                            \
	                      __hybrid_rol128_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_rol128(x, shift)                             \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_rol128_c(x, shift)                            \
	 : __hybrid_rol128_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_rol128 __hybrid_rol128_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_rol128_r */
#define __hybrid_rol128 __hybrid_rol128_c
#endif /* !__hybrid_rol128_r */
#ifdef __hybrid_ror128_r
#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define __hybrid_ror128(x, shift)                                                 \
	__builtin_choose_expr(__builtin_constant_p(x) && __builtin_constant_p(shift), \
	                      __hybrid_ror128_c(x, shift),                            \
	                      __hybrid_ror128_r(x, shift))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ror128(x, shift)                             \
	((__builtin_constant_p(x) && __builtin_constant_p(shift)) \
	 ? __hybrid_ror128_c(x, shift)                            \
	 : __hybrid_ror128_r(x, shift))
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define __hybrid_ror128 __hybrid_ror128_r
#endif /* __NO_builtin_constant_p */
#else /* __hybrid_ror128_r */
#define __hybrid_ror128 __hybrid_ror128_c
#endif /* !__hybrid_ror128_r */
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
/*[[[end]]]*/

#ifndef __NO_builtin_choose_expr
#if !defined(__UINT64_TYPE__)
#define __hybrid_rol(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_rol8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_rol16((__UINT16_TYPE__)(x), shift), \
	                                      __hybrid_rol32((__UINT32_TYPE__)(x), shift)))
#define __hybrid_ror(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_ror8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_ror16((__UINT16_TYPE__)(x), shift), \
	                                      __hybrid_ror32((__UINT32_TYPE__)(x), shift)))
#elif !defined(__UINT128_TYPE__)
#define __hybrid_rol(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_rol8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_rol16((__UINT16_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 4, __hybrid_rol32((__UINT32_TYPE__)(x), shift), \
	                                      __hybrid_rol64((__UINT64_TYPE__)(x), shift))))
#define __hybrid_ror(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_ror8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_ror16((__UINT16_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 4, __hybrid_ror32((__UINT32_TYPE__)(x), shift), \
	                                      __hybrid_ror64((__UINT64_TYPE__)(x), shift))))
#else /* !... */
#define __hybrid_rol(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_rol8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_rol16((__UINT16_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 4, __hybrid_rol32((__UINT32_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 8, __hybrid_rol64((__UINT64_TYPE__)(x), shift), \
	                                      __hybrid_rol128((__UINT128_TYPE__)(x), shift)))))
#define __hybrid_ror(x, shift)                                                         \
	__builtin_choose_expr(sizeof(x) == 1, __hybrid_ror8((__UINT8_TYPE__)(x), shift),   \
	__builtin_choose_expr(sizeof(x) == 2, __hybrid_ror16((__UINT16_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 4, __hybrid_ror32((__UINT32_TYPE__)(x), shift), \
	__builtin_choose_expr(sizeof(x) == 8, __hybrid_ror64((__UINT64_TYPE__)(x), shift), \
	                                      __hybrid_ror128((__UINT128_TYPE__)(x), shift)))))
#endif /* ... */
#else /* !__NO_builtin_choose_expr */
#if !defined(__UINT64_TYPE__)
#define __hybrid_rol(x, shift)                       \
	(sizeof(x) == 1                                  \
	 ? __hybrid_rol8((__UINT8_TYPE__)(x), shift)     \
	 : sizeof(x) == 2                                \
	   ? __hybrid_rol16((__UINT16_TYPE__)(x), shift) \
	   : __hybrid_rol32((__UINT32_TYPE__)(x), shift))
#define __hybrid_ror(x, shift)                       \
	(sizeof(x) == 1                                  \
	 ? __hybrid_ror8((__UINT8_TYPE__)(x), shift)     \
	 : sizeof(x) == 2                                \
	   ? __hybrid_ror16((__UINT16_TYPE__)(x), shift) \
	   : __hybrid_ror32((__UINT32_TYPE__)(x), shift))
#elif !defined(__UINT128_TYPE__)
#define __hybrid_rol(x, shift)                         \
	(sizeof(x) == 1                                    \
	 ? __hybrid_rol8((__UINT8_TYPE__)(x), shift)       \
	 : sizeof(x) == 2                                  \
	   ? __hybrid_rol16((__UINT16_TYPE__)(x), shift)   \
	   : sizeof(x) == 4                                \
	     ? __hybrid_rol32((__UINT32_TYPE__)(x), shift) \
	     : __hybrid_rol64((__UINT64_TYPE__)(x), shift))
#define __hybrid_ror(x, shift)                         \
	(sizeof(x) == 1                                    \
	 ? __hybrid_ror8((__UINT8_TYPE__)(x), shift)       \
	 : sizeof(x) == 2                                  \
	   ? __hybrid_ror16((__UINT16_TYPE__)(x), shift)   \
	   : sizeof(x) == 4                                \
	     ? __hybrid_ror32((__UINT32_TYPE__)(x), shift) \
	     : __hybrid_ror64((__UINT64_TYPE__)(x), shift))
#else /* !... */
#ifdef __INTELLISENSE__
#define __hybrid_rol(x, shift)                                             \
	(sizeof(x) == 1                                                        \
	 ? (__UINT128_TYPE__)__hybrid_rol8((__UINT8_TYPE__)(x), shift)         \
	 : sizeof(x) == 2                                                      \
	   ? (__UINT128_TYPE__)__hybrid_rol16((__UINT16_TYPE__)(x), shift)     \
	   : sizeof(x) == 4                                                    \
	     ? (__UINT128_TYPE__)__hybrid_rol32((__UINT32_TYPE__)(x), shift)   \
	     : sizeof(x) == 8                                                  \
	       ? (__UINT128_TYPE__)__hybrid_rol64((__UINT64_TYPE__)(x), shift) \
	       : __hybrid_rol128((__UINT128_TYPE__)(x), shift))
#define __hybrid_ror(x, shift)                                             \
	(sizeof(x) == 1                                                        \
	 ? (__UINT128_TYPE__)__hybrid_ror8((__UINT8_TYPE__)(x), shift)         \
	 : sizeof(x) == 2                                                      \
	   ? (__UINT128_TYPE__)__hybrid_ror16((__UINT16_TYPE__)(x), shift)     \
	   : sizeof(x) == 4                                                    \
	     ? (__UINT128_TYPE__)__hybrid_ror32((__UINT32_TYPE__)(x), shift)   \
	     : sizeof(x) == 8                                                  \
	       ? (__UINT128_TYPE__)__hybrid_ror64((__UINT64_TYPE__)(x), shift) \
	       : __hybrid_ror128((__UINT128_TYPE__)(x), shift))
#else /* __INTELLISENSE__ */
#define __hybrid_rol(x, shift)                           \
	(sizeof(x) == 1                                      \
	 ? __hybrid_rol8((__UINT8_TYPE__)(x), shift)         \
	 : sizeof(x) == 2                                    \
	   ? __hybrid_rol16((__UINT16_TYPE__)(x), shift)     \
	   : sizeof(x) == 4                                  \
	     ? __hybrid_rol32((__UINT32_TYPE__)(x), shift)   \
	     : sizeof(x) == 8                                \
	       ? __hybrid_rol64((__UINT64_TYPE__)(x), shift) \
	       : __hybrid_rol128((__UINT128_TYPE__)(x), shift))
#define __hybrid_ror(x, shift)                           \
	(sizeof(x) == 1                                      \
	 ? __hybrid_ror8((__UINT8_TYPE__)(x), shift)         \
	 : sizeof(x) == 2                                    \
	   ? __hybrid_ror16((__UINT16_TYPE__)(x), shift)     \
	   : sizeof(x) == 4                                  \
	     ? __hybrid_ror32((__UINT32_TYPE__)(x), shift)   \
	     : sizeof(x) == 8                                \
	       ? __hybrid_ror64((__UINT64_TYPE__)(x), shift) \
	       : __hybrid_ror128((__UINT128_TYPE__)(x), shift))
#endif /* !__INTELLISENSE__ */
#endif /* ... */
#endif /* __NO_builtin_choose_expr */

#endif /* !__GUARD_HYBRID___ROTATE_H */
