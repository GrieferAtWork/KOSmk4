/*[[[magic
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-g"); // Disable debug informations for this file!
gcc_opt.remove("-fno-rtti");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MISC_SYSCALL_PROPERTIES_C
#define GUARD_KERNEL_SRC_MISC_SYSCALL_PROPERTIES_C 1
#define __WANT_SYSCALL_REGISTER_COUNT 1
#define __WANT_SYSCALL_RESTART_MODES 1
#define __WANT_SYSCALL_CANCELLATION_POINTS 1
#define __WANT_SYSCALL_DOUBLE_WIDE_RETURN 1

#include <kernel/compiler.h>

#include <kernel/syscall-properties.h>
#include <kernel/types.h>

#define ARG_PLACEHOLDER_   ,
#define ARG_PLACEHOLDER_1  ,
#define ARG_PLACEHOLDER_2  ,
#define ARG_PLACEHOLDER_3  ,
#define ARG_PLACEHOLDER_4  ,
#define ARG_PLACEHOLDER_5  ,
#define ARG_PLACEHOLDER_6  ,
#define ARG_PLACEHOLDER_7  ,
#define ARG_PLACEHOLDER_8  ,
#define ARG_PLACEHOLDER_9  ,
#define ARG_PLACEHOLDER_10 ,
#define ARG_PLACEHOLDER_11 ,
#define ARG_PLACEHOLDER_12 ,
#define ARG_PLACEHOLDER_13 ,
#define ARG_PLACEHOLDER_14 ,
#define ARG_PLACEHOLDER_15 ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(...) TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)


DECL_BEGIN

/* Directly include the arch-specific header, so it we get recompiled
 * if that header changes. (normally, changes in system headers won't
 * trigger a re-compile of consumer source files) */
#if defined(__i386__) || defined(__x86_64__)
#define INC_LS_SYSCALLS "../../../../include/i386-kos/asm/ls-syscalls.h"
#include "../../../../include/i386-kos/asm/syscalls.h"
#else /* Arch... */
/* Fallback for when we can't use relative includes... */
#undef asm
#undef ls
#undef syscalls
#undef h
#define INC_LS_SYSCALLS <asm/ls-syscalls.h>
#include <asm/unistd.h>
#endif /* !Arch... */


/************************************************************************/
/* Define kernel_syscallN_iscp                                          */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct struct_kernel_syscall##table_id##_iscp {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int iscp_##name : 1;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int iscp_break##sysno : 1;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct struct_kernel_syscall##table_id##_iscp \
	kernel_syscall##table_id##_iscp_s ASMNAME("kernel_syscall" #table_id "_iscp") = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .iscp_##name       = */ IS_DEFINED(__NRCP_##name),
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .iscp_break##sysno = */ 0,
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS





/************************************************************************/
/* Define kernel_syscallN_restartmode                                   */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct struct_kernel_syscall##table_id##_restartmode {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int rm_##name : 2;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int rm_break##sysno : 2;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct struct_kernel_syscall##table_id##_restartmode \
	kernel_syscall##table_id##_restartmode_s ASMNAME("kernel_syscall" #table_id "_restartmode") = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .rm_##name       = */ __NRRM_##name,
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .rm_break##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS





/************************************************************************/
/* Define kernel_syscallN_regcnt                                        */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct struct_kernel_syscall##table_id##_regcnt {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int rc_##name : 4;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int rc_break##sysno : 4;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct struct_kernel_syscall##table_id##_regcnt \
	kernel_syscall##table_id##_regcnt_s ASMNAME("kernel_syscall" #table_id "_regcnt") = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .rc_##name       = */ __NRRC_##name | (IS_DEFINED(__NRDW_##name) ? 8 : 0),
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .rc_break##sysno = */ __NRFEAT_SYSCALL_REGISTER_MAX_COUNT,
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INC_LS_SYSCALLS




/* Define system call properties for compatibility mode (should such a mode exists on the target arch)
 * -> Use     `KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS'     the     same      way
 *    `platformSuffix' is  used in  `generate_syscall.dee'  in order  to  define
 *    `kernel_syscall##id##_restartmode##KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS' */
#ifdef KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS
#define CN3(x, y)   x##y
#define CN2(x, y)   CN3(x, y)
#define CN(x)       CN2(x, KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS)
#define NRCN3(x, y) __NR##x##y
#define NRCN2(x, y) NRCN3(x, y)
#define NRCN(x)     NRCN2(KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS, x)
#define CNS         PP_STR(KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS)
#define INCLUDE_ASM_LS_SYSCALLS_COMPAT_H() <asm/ls-CN(syscalls).h>

/************************************************************************/
/* Define kernel_syscallN_iscpCN                                        */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct CN(struct_kernel_syscall##table_id##_iscp) {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int iscp_##name : 1;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int iscp_break##sysno : 1;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct CN(struct_kernel_syscall##table_id##_iscp) \
	CN(kernel_syscall##table_id##_iscp_s) ASMNAME("kernel_syscall" #table_id "_iscp" CNS) = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .iscp_##name       = */ IS_DEFINED(NRCN(CP_##name)),
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .iscp_break##sysno = */ 0,
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()





/************************************************************************/
/* Define kernel_syscallN_restartmodeCN                                 */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct CN(struct_kernel_syscall##table_id##_restartmode) {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int rm_##name : 2;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int rm_break##sysno : 2;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct CN(struct_kernel_syscall##table_id##_restartmode) \
	CN(kernel_syscall##table_id##_restartmode_s) ASMNAME("kernel_syscall" #table_id "_restartmode" CNS) = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .rm_##name       = */ NRCN(RM_##name),
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .rm_break##sysno = */ SYSCALL_RESTART_MODE_AUTO,
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()





/************************************************************************/
/* Define kernel_syscallN_regcnt                                        */
/************************************************************************/
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct CN(struct_kernel_syscall##table_id##_regcnt) {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) unsigned int rc_##name : 4;
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     unsigned int rc_break##sysno : 4;
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC struct CN(struct_kernel_syscall##table_id##_regcnt) \
	CN(kernel_syscall##table_id##_regcnt_s) ASMNAME("kernel_syscall" #table_id "_regcnt" CNS) = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) /* .rc_##name       = */ NRCN(RC_##name) | (IS_DEFINED(NRCN(DW_##name)) ? 8 : 0),
#define __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)                     /* .rc_break##sysno = */ NRCN(FEAT_SYSCALL_REGISTER_MAX_COUNT),
#define __TSYSCALL_UNUSED(table_id, sysno, table_index, table_index_without_unused_leading) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_UNUSED_TRAILING(table_id, sysno, table_index, table_index_without_unused_leading, index_in_unused_trailing) __TSYSCALL_UNUSED_LEADING(table_id, sysno, table_index)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include INCLUDE_ASM_LS_SYSCALLS_COMPAT_H()

#undef INCLUDE_ASM_LS_SYSCALLS_COMPAT_H
#undef CNS
#undef NRCN
#undef NRCN2
#undef NRCN3
#undef CN
#undef CN2
#undef CN3
#endif /* KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_SYSCALL_PROPERTIES_C */
