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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PROPERTIES_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PROPERTIES_C 1
#define _KOS_SOURCE 1
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_COUNT_386 1
#define __WANT_SYSCALL_RESTART_MODES 1
#define __WANT_SYSCALL_CANCELLATION_POINTS 1
#define __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386 1

#include <kernel/compiler.h>

#include <kernel/syscall.h>

#include <asm/unistd.h>

DECL_BEGIN


/* System call register count information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_argc_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_argc_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int argc_##name : 4;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int argc_unused_##sysno : 4;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

#define ARG_PLACEHOLDER_1  ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(...) TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)


DATDEF struct syscalls_argc_info const x86_syscall_register_count_s ASMNAME("x86_syscall_register_count");
DATDEF struct extended_syscalls_argc_info const x86_exsyscall_register_count_s ASMNAME("x86_exsyscall_register_count");

#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_argc_info const x86_syscall_register_count_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_argc_info const x86_exsyscall_register_count_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#ifdef __x86_64__
#define __SYSCALL(name)                                              /* .argc_##name  = */ __NRAC_##name,
#else /* __x86_64__ */
#define IS_DOUBLE_WIDE(name)   IS_DEFINED(__NRDW386_##name)
#define __SYSCALL(name)                                              /* .argc_##name  = */ __NRAC386_##name | (IS_DOUBLE_WIDE(name) ? 8 : 0),
#endif /* !__x86_64__ */
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .argc_##sysno = */ 0,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .argc_##sysno = */ 0,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .argc_##sysno = */ 0,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


/* System call restart mode / cancellation point information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_restart_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_restart_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int rm_##name : 2;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int rm_unused_##sysno : 2;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls_restart_info const x86_syscall_restart_mode_s ASMNAME("x86_syscall_restart_mode");
DATDEF struct extended_syscalls_restart_info const x86_exsyscall_restart_mode_s ASMNAME("x86_exsyscall_restart_mode");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_restart_info const x86_syscall_restart_mode_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_restart_info const x86_exsyscall_restart_mode_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .rm_##name  = */ __NRRM_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_is_cancellation_point_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_is_cancellation_point_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int icp_##name : 1;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int icp_unused_##sysno : 1;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls_is_cancellation_point_info const x86_syscall_is_cancellation_point_s ASMNAME("x86_syscall_is_cancellation_point");
DATDEF struct extended_syscalls_is_cancellation_point_info const x86_exsyscall_is_cancellation_point_s ASMNAME("x86_exsyscall_is_cancellation_point");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_is_cancellation_point_info const x86_syscall_is_cancellation_point_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_is_cancellation_point_info const x86_exsyscall_is_cancellation_point_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .icp_##name  = */ __NRCP_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .icp_unused_##sysno = */ 1,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .icp_unused_##sysno = */ 1,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .icp_unused_##sysno = */ 1,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS






#ifdef __x86_64__
#include <asm/syscalls32.inl>

#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_argc_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_argc_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int argc_##name : 4;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int argc_unused_##sysno : 4;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_argc_info const x86_syscall32_register_count_s ASMNAME("x86_syscall32_register_count");
DATDEF struct extended_syscalls32_argc_info const x86_exsyscall32_register_count_s ASMNAME("x86_exsyscall32_register_count");

#define __BEGIN_SYSCALLS(min,max,cnt)          PUBLIC_CONST struct syscalls32_argc_info const x86_syscall32_register_count_s = {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) PUBLIC_CONST struct extended_syscalls32_argc_info const x86_exsyscall32_register_count_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define IS_DOUBLE_WIDE_386(name)   IS_DEFINED(__NR32AC386_##name)
#define __SYSCALL(name)                                              /* .argc_##name  = */ __NR32AC386_##name | (IS_DOUBLE_WIDE_386(name) ? 8 : 0),
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .argc_##sysno = */ 0,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .argc_##sysno = */ 0,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .argc_##sysno = */ 0,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS



/* System call restart mode / cancellation point information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_restart_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_restart_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int rm_##name : 2;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int rm_unused_##sysno : 2;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_restart_info const x86_syscall32_restart_mode_s ASMNAME("x86_syscall32_restart_mode");
DATDEF struct extended_syscalls32_restart_info const x86_exsyscall32_restart_mode_s ASMNAME("x86_exsyscall32_restart_mode");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls32_restart_info const x86_syscall32_restart_mode_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls32_restart_info const x86_exsyscall32_restart_mode_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .rm_##name  = */ __NR32RM_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .rm_unused_##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_is_cancellation_point_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_is_cancellation_point_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int icp_##name : 1;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int icp_unused_##sysno : 1;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_is_cancellation_point_info const x86_syscall32_is_cancellation_point_s ASMNAME("x86_syscall32_is_cancellation_point");
DATDEF struct extended_syscalls32_is_cancellation_point_info const x86_exsyscall32_is_cancellation_point_s ASMNAME("x86_exsyscall32_is_cancellation_point");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls32_is_cancellation_point_info const x86_syscall32_is_cancellation_point_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls32_is_cancellation_point_info const x86_exsyscall32_is_cancellation_point_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .icp_##name  = */ __NR32CP_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .icp_unused_##sysno = */ 1,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .icp_unused_##sysno = */ 1,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .icp_unused_##sysno = */ 1,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS
#endif /* __x86_64__ */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PROPERTIES_C */
