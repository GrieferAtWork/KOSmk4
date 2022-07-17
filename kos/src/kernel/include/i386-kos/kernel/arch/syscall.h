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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/unistd.h>
#include <bits/types.h>

#ifdef __ASSEMBLER__
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#endif /* __ASSEMBLER__ */

#ifdef BUILDING_KERNEL_CORE
#ifdef __x86_64__
#if !defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT) || \
    !defined(__NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES) || \
    !defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES)
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_RETURN_TYPES
#undef __WANT_SYSCALL_ARGUMENT_TYPES
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_RETURN_TYPES   1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#include <asm/syscalls-proto32_d.h>
#endif /* !... */

#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */

#include <asm/syscall3264-compat.h>

#define ATTR_SECTION_SYSCALL32(name_str) ATTR_SECTION(".text.x86.syscall32." name_str)
#endif /* __x86_64__ */

#define ATTR_SECTION_SYSCALL(name_str)   ATTR_SECTION(".text.x86.syscall." name_str)
#endif /* BUILDING_KERNEL_CORE */


#ifdef __CC__
DECL_BEGIN

struct icpustate;
struct rpc_syscall_info;

/* Emulate a system call invocation, given a user-space register state. */
#ifdef __x86_64__
/* emulation with automatic target detection (either x32 or x64) */
FUNDEF struct icpustate *FCALL x86_syscall_emulate_int80h(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate_int80h_r)(struct icpustate *__restrict state);
/* x32-specific emulation */
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_int80h(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate32_int80h_r)(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_sysenter(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate32_sysenter_r)(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_cdecl(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate32_cdecl_r)(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
/* x64-specific emulation */
FUNDEF struct icpustate *FCALL x86_syscall_emulate_sysvabi(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate_sysvabi_r)(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
FUNDEF struct icpustate *FCALL x86_syscall_emulate64_int80h(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate64_int80h_r)(struct icpustate *__restrict state);
#define x86_syscall_emulate64_sysvabi   x86_syscall_emulate_sysvabi
#define x86_syscall_emulate64_sysvabi_r x86_syscall_emulate_sysvabi_r
#else /* __x86_64__ */
FUNDEF struct icpustate *FCALL x86_syscall_emulate_int80h(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate_int80h_r)(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate_sysenter(struct icpustate *__restrict state) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate_sysenter_r)(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate_cdecl(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except) THROWS(...);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void NOTHROW(FCALL x86_syscall_emulate_cdecl_r)(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
#define x86_syscall_emulate32_int80h     x86_syscall_emulate_int80h
#define x86_syscall_emulate32_int80h_r   x86_syscall_emulate_int80h_r
#define x86_syscall_emulate32_sysenter   x86_syscall_emulate_sysenter
#define x86_syscall_emulate32_sysenter_r x86_syscall_emulate_sysenter_r
#define x86_syscall_emulate32_cdecl      x86_syscall_emulate_cdecl
#define x86_syscall_emulate32_cdecl_r    x86_syscall_emulate_cdecl_r
#endif /* !__x86_64__ */

/* Emulate a system call using a standard function call */
#ifdef __x86_64__
#define syscall_emulate_callback(state, sysno, enable_except)                            \
	(icpustate_is64bit(state) ? x86_syscall_emulate_sysvabi(state, sysno, enable_except) \
	                          : x86_syscall_emulate32_cdecl(state, sysno, enable_except))
#define syscall_emulate_callback_r(state, sysno, enable_except)                            \
	(icpustate_is64bit(state) ? x86_syscall_emulate_sysvabi_r(state, sysno, enable_except) \
	                          : x86_syscall_emulate32_cdecl_r(state, sysno, enable_except))
#define syscall_emulate32_callback   x86_syscall_emulate32_cdecl
#define syscall_emulate32_callback_r x86_syscall_emulate32_cdecl_r
#define syscall_emulate64_callback   x86_syscall_emulate_sysvabi
#define syscall_emulate64_callback_r x86_syscall_emulate_sysvabi_r
#define syscall_emulate_callback_compat   x86_syscall_emulate32_cdecl
#define syscall_emulate_callback_compat_r x86_syscall_emulate32_cdecl_r
#else /* __x86_64__ */
#define syscall_emulate_callback     x86_syscall_emulate_cdecl
#define syscall_emulate_callback_r   x86_syscall_emulate_cdecl_r
#define syscall_emulate32_callback   x86_syscall_emulate_cdecl
#define syscall_emulate32_callback_r x86_syscall_emulate_cdecl_r
#endif /* !__x86_64__ */


#ifdef __x86_64__
FUNDEF WUNUSED struct icpustate *FCALL
syscall_emulate32(struct icpustate *__restrict state,
                  struct rpc_syscall_info const *__restrict sc_info)
		 THROWS(...);
FUNDEF WUNUSED struct icpustate *FCALL
syscall_emulate64(struct icpustate *__restrict state,
                  struct rpc_syscall_info const *__restrict sc_info)
		 THROWS(...);
#define syscall_emulate32_r syscall_emulate_r
#define syscall_emulate64_r syscall_emulate_r
#else /* __x86_64__ */
#define syscall_emulate32   syscall_emulate
#define syscall_emulate32_r syscall_emulate_r
#endif /* !__x86_64__ */

DECL_END


/* Define compatibility-mode system calls. */
#ifdef BUILDING_KERNEL_CORE
#ifdef __x86_64__
/* When defining a 64-bit system call, alias compatible 32-bit variant(s) onto it,
 * thus implementing system  calls without  dedicated compatibility-mode  variants
 * by calling forward to their 64-bit (regular) variants (if possible).
 *
 * A  listing of compatible system calls can be found in: `<asm/syscall3264-compat.h>':
 * `#define __NR3264COMPAT_<NAME> <COMPAT_COUNT>(<FIRST_COMPAT>,<SECOND_COMPAT>,<...>)'
 *
 * Comments found further  below detail exactly  how this meta-data  is used to  define
 * system call aliases (don't even try to read the preprocessor magic used to implement
 * the logic. - It works and is standard-compliant, but it is extremely convoluted) */
#undef __ARCH_DEFINE_SYSCALL_COMMON
#undef __ARCH_DEFINE_SYSCALL32_COMMON

#define __X86_NR3264COMPAT_ARG_PLACEHOLDER_1(...) ,
#define __X86_NR3264COMPAT_ARG_PLACEHOLDER_2(...) ,
#define __X86_NR3264COMPAT_ARG_PLACEHOLDER_3(...) ,
#define __X86_NR3264COMPAT_ARG_PLACEHOLDER_4(...) ,
#define __X86_NR3264COMPAT_ARG_PLACEHOLDER_5(...) ,
#define __X86_NR3264COMPAT_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __X86_NR3264COMPAT_TAKE_SECOND_ARG(x) __X86_NR3264COMPAT_TAKE_SECOND_ARG_IMPL x
#define __X86_NR3264COMPAT_IS_DEFINED3(...) __X86_NR3264COMPAT_TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define __X86_NR3264COMPAT_IS_DEFINED2(x) __X86_NR3264COMPAT_IS_DEFINED3(__X86_NR3264COMPAT_ARG_PLACEHOLDER_##x)
#define __X86_NR3264COMPAT_IS_DEFINED(x) __X86_NR3264COMPAT_IS_DEFINED2(x)

/* ... and the following behavior when defining a 32-bit system call:
 * >> __asm__(".ifdef sys32" #_compat_name "\n");
 * >> __asm__(".error \"" __FILE__ ":" __LINE_STR__ ":error: Duplicate definition of sys32" #_compat_name "\"\n");
 * >> __asm__(".endif\n");
 * >> if (__NR32RC##_compat_name == 0) {
 * >>     DEFINE_INTERN_ALIAS(__x86_asm32_sysrun32##_compat_name, sys_name);
 * >> }
 */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_0(sys_name, _compat_name) DEFINE_INTERN_ALIAS(__x86_asm32_sysrun32##_compat_name, sys_name);
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_1(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_2(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_3(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_4(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_5(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_6(sys_name, _compat_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2(sys_name, _compat_name, regc) \
	__X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2_##regc(sys_name, _compat_name)
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC(sys_name, _compat_name, regc) \
	__X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC2(sys_name, _compat_name, regc)
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR3(x) #x
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR2(x) __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR3(x)
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR2(__LINE__)
#define __X86_NR3264COMPAT_SYSCALL32_COMPAT64(sys_name, _compat_name, more)                     \
	__asm__(".ifdef sys32" #_compat_name "\n"                                                  \
	        ".error \"" __FILE__ ":" __X86_NR3264COMPAT_SYSCALL32_COMPAT64_LINE_STR ":error: " \
	        "Duplicate definition of 'sys32" #_compat_name "'\"\n" more                        \
	        ".endif");                                                                         \
	__X86_NR3264COMPAT_SYSCALL32_COMPAT64_REGC(sys_name, _compat_name, __NR32RC##_compat_name)


/* Using macros, implement the following behavior when defining a 64-bit system call:
 * >> if (defined(__NR3264COMPAT##_name)) {
 * >>     for (compat_name: __NR3264COMPAT##_name) {
 * >>         __asm__(".ifdef sys32_" #compat_name "\n");
 * >>         __asm__(".error \"" __FILE__ ":" __LINE_STR__ ":error: Duplicate definition of sys32_" #compat_name "\"\n");
 * >>         DEFINE_PUBLIC_ALIAS(sys32_##compat_name, sys##_name);
 * >>         __asm__(".endif\n");
 * >>         if (__NR32RC_##compat_name == 0) {
 * >>             DEFINE_INTERN_ALIAS(__x86_asm32_sysrun32_##compat_name, sys##_name);
 * >>         }
 * >>     }
 * >> } */
#define __X86_NR3264COMPAT_SYSCALL_TEXTALIAS32(compat_name, _name) \
	/* DEFINE_PUBLIC_ALIAS(sys32_##compat_name, sys##_name); */    \
	".global sys32_" #compat_name "\n"                             \
	".set sys32_" #compat_name ",sys" #_name "\n"
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, a) \
	__X86_NR3264COMPAT_SYSCALL32_COMPAT64(sys##_name, _##a, ".else\n" __X86_NR3264COMPAT_SYSCALL_TEXTALIAS32(a, _name))
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_2(_name, a, b) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, a)        \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, b)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_3(_name, a, b, c) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, a)           \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, b)           \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, c)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_4(_name, a, b, c, d) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, a)              \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, b)              \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, c)              \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, d)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_5(_name, a, b, c, d, e) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, a)                 \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, b)                 \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, c)                 \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, d)                 \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_1(_name, e)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_1(...) __VA_ARGS__
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_2(...) __VA_ARGS__
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_3(...) __VA_ARGS__
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_4(...) __VA_ARGS__
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_5(...) __VA_ARGS__
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_1(...) 1
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_2(...) 2
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_3(...) 3
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_4(...) 4
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_5(...) 5
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X1(_name, compatc, ...) __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_##compatc(_name, __VA_ARGS__)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_3(_name, argc, ...) __X86_NR3264COMPAT_SYSCALL_COMMON3_1_X_##argc(_name, __VA_ARGS__)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_2(_name, argc, ...) __X86_NR3264COMPAT_SYSCALL_COMMON3_1_3(_name, argc, __VA_ARGS__)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_1(_name, def) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_1_2(_name, __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Z_##def, __X86_NR3264COMPAT_SYSCALL_COMMON3_1_Y_##def)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1_0(_name, def) __X86_NR3264COMPAT_SYSCALL_COMMON3_1_1(_name, def)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_1(_name) __X86_NR3264COMPAT_SYSCALL_COMMON3_1_0(_name, __NR3264COMPAT##_name)
#define __X86_NR3264COMPAT_SYSCALL_COMMON3_0(_name) /* nothing */
#define __X86_NR3264COMPAT_SYSCALL_COMMON3(is_defined, _name) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3_##is_defined(_name)
#define __X86_NR3264COMPAT_SYSCALL_COMMON2(is_defined, _name) \
	__X86_NR3264COMPAT_SYSCALL_COMMON3(is_defined, _name)
#define __ARCH_DEFINE_SYSCALL_COMMON(_name) \
	__X86_NR3264COMPAT_SYSCALL_COMMON2(__X86_NR3264COMPAT_IS_DEFINED(__NR3264COMPAT##_name), _name)
/* ... and the following behavior when defining a 32-bit system call:
 * >> .ifdef sys32##_name
 * >> .error "Duplicate definition of sys32##_name"
 * >> .endif
 * >> if (__NR32RC##_name == 0) {
 * >>     DEFINE_INTERN_ALIAS(__x86_asm32_sysrun32##_name, sys32##_name);
 * >> }
 */
#define __ARCH_DEFINE_SYSCALL32_COMMON(_name) \
	__X86_NR3264COMPAT_SYSCALL32_COMPAT64(sys32##_name, _name,)

#ifndef __PRIVATE_SYSCALL_GET_ESCAPED_TYPE
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2(a, b) b
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(t) __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2 t
#endif /* !__PRIVATE_SYSCALL_GET_ESCAPED_TYPE */
#define DEFINE_SYSCALL32_0(return_type, name)                                                                      \
	STATIC_ASSERT(__NR32AC_##name == 0);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(void) ASMNAME("sys32_" #name);                           \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                       \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(void)
#define DEFINE_SYSCALL32_1(return_type, name, T0, N0)                                                              \
	STATIC_ASSERT(__NR32AC_##name == 1);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0) ASMNAME("sys32_" #name);                          \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                       \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0)
#define DEFINE_SYSCALL32_2(return_type, name, T0, N0, T1, N1)                                                      \
	STATIC_ASSERT(__NR32AC_##name == 2);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1) ASMNAME("sys32_" #name);                   \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                       \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1)
#define DEFINE_SYSCALL32_3(return_type, name, T0, N0, T1, N1, T2, N2)                                              \
	STATIC_ASSERT(__NR32AC_##name == 3);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2) ASMNAME("sys32_" #name);            \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                       \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2)
#define DEFINE_SYSCALL32_4(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3)                                      \
	STATIC_ASSERT(__NR32AC_##name == 4);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3) ASMNAME("sys32_" #name);     \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                       \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3)
#define DEFINE_SYSCALL32_5(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4)                                 \
	STATIC_ASSERT(__NR32AC_##name == 5);                                                                              \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type));    \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name), T4));            \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4) ASMNAME("sys32_" #name); \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                          \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4)
#define DEFINE_SYSCALL32_6(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4, T5, N5)                                \
	STATIC_ASSERT(__NR32AC_##name == 6);                                                                                     \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type));           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name), T4));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT5_##name), T5));                   \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5) ASMNAME("sys32_" #name); \
	__ARCH_DEFINE_SYSCALL32_COMMON(_##name);                                                                                 \
	PUBLIC ATTR_SECTION_SYSCALL32(#name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5)
#define DEFINE_SYSCALL64_0 DEFINE_SYSCALL0
#define DEFINE_SYSCALL64_1 DEFINE_SYSCALL1
#define DEFINE_SYSCALL64_2 DEFINE_SYSCALL2
#define DEFINE_SYSCALL64_3 DEFINE_SYSCALL3
#define DEFINE_SYSCALL64_4 DEFINE_SYSCALL4
#define DEFINE_SYSCALL64_5 DEFINE_SYSCALL5
#define DEFINE_SYSCALL64_6 DEFINE_SYSCALL6
#define DEFINE_COMPAT_SYSCALL0 DEFINE_SYSCALL32_0
#define DEFINE_COMPAT_SYSCALL1 DEFINE_SYSCALL32_1
#define DEFINE_COMPAT_SYSCALL2 DEFINE_SYSCALL32_2
#define DEFINE_COMPAT_SYSCALL3 DEFINE_SYSCALL32_3
#define DEFINE_COMPAT_SYSCALL4 DEFINE_SYSCALL32_4
#define DEFINE_COMPAT_SYSCALL5 DEFINE_SYSCALL32_5
#define DEFINE_COMPAT_SYSCALL6 DEFINE_SYSCALL32_6
#else /* __x86_64__ */
#define DEFINE_SYSCALL32_0 DEFINE_SYSCALL0
#define DEFINE_SYSCALL32_1 DEFINE_SYSCALL1
#define DEFINE_SYSCALL32_2 DEFINE_SYSCALL2
#define DEFINE_SYSCALL32_3 DEFINE_SYSCALL3
#define DEFINE_SYSCALL32_4 DEFINE_SYSCALL4
#define DEFINE_SYSCALL32_5 DEFINE_SYSCALL5
#define DEFINE_SYSCALL32_6 DEFINE_SYSCALL6
#endif /* !__x86_64__ */
#endif /* BUILDING_KERNEL_CORE */


#endif /* __CC__ */




#ifdef __ASSEMBLER__
#ifdef __x86_64__
#include <asm/instr/interrupt.h>

/* Do the equivalent of `intr_exit', but try to make use of `sysretl' if the register
 * state described by the iret  tail stored at `0(%rsp)' allow  for this to be  done.
 * Note  that  if sysexit  ends  up being  used,  the following  user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %rcx      (Set to OFFSET_IRREGS_RIP(%rsp))
 *  - %r8-%r15  (Undefined, but since these are invisible to 32-bit programs, this shouldn't matter) */
#define X86_IRET_BUT_PREFER_SYSRET32 \
	jmp __x86_32_syscall_iret

/* Do the equivalent of `intr_exit', but try to make use of `sysretq' if the register
 * state described by the iret  tail stored at `0(%rsp)' allow  for this to be  done.
 * Note  that  if sysexit  ends  up being  used,  the following  user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %rcx      (Set to OFFSET_IRREGS_RIP(%rsp))
 *  - %r11      (Set to OFFSET_IRREGS_RFLAGS(%rsp)) */
#define X86_IRET_BUT_PREFER_SYSRET64 \
	jmp __x86_64_syscall_iret

#else /* __x86_64__ */

/* Do  the equivalent of `iret', but try to  make use of `sysexit' if the register
 * state described by the iret tail stored at `0(%esp)' allow for this to be done.
 * Note  that if  sysexit ends up  being used, the  following user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %ecx   (Set to OFFSET_IRREGS_ESP(%esp))
 *  - %edx   (Set to OFFSET_IRREGS_EIP(%esp)) */
#define X86_IRET_BUT_PREFER_SYSEXIT \
	jmp __i386_syscall_iret

#endif /* !__x86_64__ */
#endif /* __ASSEMBLER__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H */
