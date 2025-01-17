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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_H 1

#include <kernel/compiler.h>

#include <kernel/arch/syscall.h>
#include <kernel/types.h>

#include <asm/unistd.h>
#include <bits/crt/format-printer.h>
#include <kos/kernel/syscalls.h> /* __ARCH_WANT_SYSCALL_* */
#include <kos/syscalls.h>        /* System call prototypes */

#ifdef BUILDING_KERNEL_CORE
#if (!defined(__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT) || \
     !defined(__NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES) || \
     !defined(__NRFEAT_DEFINED_SYSCALL_RETURN_TYPES))
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_TYPES
#undef __WANT_SYSCALL_RETURN_TYPES
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#define __WANT_SYSCALL_RETURN_TYPES   1
#include <asm/syscalls-proto.h>
#endif /* !... */
#endif /* BUILDING_KERNEL_CORE */


/* Need to get `__NRFEAT_SYSCALL_REGISTER_MAX_COUNT' */
#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */

#ifndef ATTR_SECTION_SYSCALL
#define ATTR_SECTION_SYSCALL(name_str) /* nothing */
#endif /* !ATTR_SECTION_SYSCALL */

#ifndef __ARCH_SYSCALLCC
#define __ARCH_SYSCALLCC KCALL
#endif /* !__ARCH_SYSCALLCC */

#ifndef __ARCH_DEFINE_SYSCALL_COMMON
#define __ARCH_DEFINE_SYSCALL_COMMON(_name) /* nothing */
#endif /* !__ARCH_DEFINE_SYSCALL_COMMON */

#ifdef __CC__
DECL_BEGIN

#ifdef BUILDING_KERNEL_CORE
#ifndef __PRIVATE_SYSCALL_GET_ESCAPED_TYPE
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2(a, b) b
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(t) __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2 t
#endif /* !__PRIVATE_SYSCALL_GET_ESCAPED_TYPE */
#define __PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(T1, T2)      \
	STATIC_ASSERT_MSG(__builtin_types_compatible_p(T1, T2),   \
	                  "Types `" __PP_PRIVATE_STR(T1) "' and " \
	                  "`" __PP_PRIVATE_STR(T2) "' are not compatible")

#define DEFINE_SYSCALL0(return_type, name)                                                                    \
	STATIC_ASSERT(__NRAC_##name == 0);                                                                        \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type); \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                     \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(void) ASMNAME("sys_" #name);                          \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(void)
#define DEFINE_SYSCALL1(return_type, name, T0, N0)                                                            \
	STATIC_ASSERT(__NRAC_##name == 1);                                                                        \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type); \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);         \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                     \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0) ASMNAME("sys_" #name);                         \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0)
#define DEFINE_SYSCALL2(return_type, name, T0, N0, T1, N1)                                                    \
	STATIC_ASSERT(__NRAC_##name == 2);                                                                        \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type); \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_##name), T1);         \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                     \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1) ASMNAME("sys_" #name);                  \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1)
#define DEFINE_SYSCALL3(return_type, name, T0, N0, T1, N1, T2, N2)                                            \
	STATIC_ASSERT(__NRAC_##name == 3);                                                                        \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type); \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_##name), T1);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_##name), T2);         \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                     \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2) ASMNAME("sys_" #name);           \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2)
#define DEFINE_SYSCALL4(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3)                                    \
	STATIC_ASSERT(__NRAC_##name == 4);                                                                        \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type); \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_##name), T1);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_##name), T2);         \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_##name), T3);         \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                     \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3) ASMNAME("sys_" #name);    \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3)
#define DEFINE_SYSCALL5(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4)                                \
	STATIC_ASSERT(__NRAC_##name == 5);                                                                            \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type);     \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);             \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_##name), T1);             \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_##name), T2);             \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_##name), T3);             \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT4_##name), T4);             \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4) ASMNAME("sys_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4)
#define DEFINE_SYSCALL6(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4, T5, N5)                               \
	STATIC_ASSERT(__NRAC_##name == 6);                                                                                   \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRRT_##name), return_type);            \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT0_##name), T0);                    \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_##name), T1);                    \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_##name), T2);                    \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_##name), T3);                    \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT4_##name), T4);                    \
	__PRIVATE_STATIC_ASSERT_TYPES_COMPATIBLE(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT5_##name), T5);                    \
	__ARCH_DEFINE_SYSCALL_COMMON(_##name)                                                                                \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5) ASMNAME("sys_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL(#name) return_type __ARCH_SYSCALLCC impl_sys_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5)
#endif /* BUILDING_KERNEL_CORE */

/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however already
 *       includes all of the necessary exception handling ~ala userexcept_handler:
 * >> PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
 * >> NOTHROW(FCALL syscall_emulate_r)(struct icpustate *__restrict state,
 * >>                                  struct rpc_syscall_info const *__restrict sc_info) {
 * >> again:
 * >>     TRY {
 * >>         state = syscall_emulate(state, sc_info);
 * >>         cpu_apply_icpustate(state);
 * >>     } EXCEPT {
 * >>         state = userexcept_handler(state, sc_info);
 * >>         // PERTASK_SET(this_exception_code, 1); // Prevent internal assertion check
 * >>         goto again;
 * >>     }
 * >> } */
FUNDEF WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info const *__restrict sc_info)
		THROWS(...);

FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
NOTHROW(FCALL syscall_emulate_r)(struct icpustate *__restrict state,
                                 struct rpc_syscall_info const *__restrict sc_info);

DECL_END
#endif /* !__CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_H */
