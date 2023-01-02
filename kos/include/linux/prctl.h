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
/* (#) Portability: Linux     (/usr/include/linux/prctl.h) */
/* (#) Portability: diet libc (/include/linux/prctl.h) */
#ifndef _LINUX_PRCTL_H
#define _LINUX_PRCTL_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include <bits/types.h>

#if defined(__KOS__) || defined(__linux__)
#define __TASK_COMM_LEN 16 /* The max length of the task command name (including the trailing NUL) */
#endif /* __KOS__ || __linux__ */

/* IMPORTANT:
 *  - Macros "#define PR_foo" will appear in libsctrace
 *  - Macros "#   define PR_bar" will NOT appear in libsctrace
 * For this purpose, turn off clang-format for this file! */

/* clang-format off */

/************************************************************************/
/* Command codes for `prctl(2)'                                         */
/************************************************************************/

/* Signal send to parent on exit */
#define PR_SET_PDEATHSIG       1  /* [signo_t signo] Set death signal (SIGCHLD) */
#define PR_GET_PDEATHSIG       2  /* [signo_t *p_signo] Get death signal (SIGCHLD) */

/* Can create coredump */
#define PR_GET_DUMPABLE        3  /* [bool return] Get process-is-dumpable */
#define PR_SET_DUMPABLE        4  /* [bool dumpable] Set process-is-dumpable */

/* Unaligned memory emulation */
#if (!defined(__USE_KOS_PURE) || defined(__ia64__) || \
     defined(__parisc__) || defined(__powerpc__) ||   \
     defined(__alpha__) || defined(__sh__) || defined(__tile__))
#define PR_GET_UNALIGN         5  /* [unsigned int *arg] Get unaligned memory access mode (set of `PR_UNALIGN_*') */
#define PR_SET_UNALIGN         6  /* [unsigned int arg] Set unaligned memory access mode (set of `PR_UNALIGN_*') */
#   define PR_UNALIGN_NOPRINT  0x00000001 /* Silently fix (emulate) unaligned memory access */
#   define PR_UNALIGN_SIGBUS   0x00000002 /* Raise SIGBUS on unaligned memory access (only on certain architectures) */
#endif /* ... */

/* Don't clear permitted capabilities when all of (r|e|s)uid become non-0 */
#define PR_GET_KEEPCAPS        7  /* [bool result] Get `THIS_CRED->c_securebits & SECBIT_KEEP_CAPS' */
#define PR_SET_KEEPCAPS        8  /* [bool arg] Set `THIS_CRED->c_securebits & SECBIT_KEEP_CAPS' */

/* FPU emulation mode */
#if !defined(__USE_KOS_PURE) || defined(__ia64__)
#define PR_GET_FPEMU           9  /* [unsigned int *arg] Get FPU emulation mode (set of `PR_FPEMU_*') */
#define PR_SET_FPEMU           10 /* [unsigned int arg] Set FPU emulation mode (set of `PR_FPEMU_*') */
#   define PR_FPEMU_NOPRINT    0x00000001 /* Silently emulate FPU operations */
#   define PR_FPEMU_SIGFPE     0x00000002 /* Raise SIGBUS on FPU operation (only on certain architectures) */
#endif /* !__USE_KOS_PURE || __ia64__ */

/* FPU exception mode */
#if !defined(__USE_KOS_PURE) || defined(__powerpc__)
#define PR_GET_FPEXC           11 /* [int *arg] Get FPU exception mode (PPC only; set of `PR_FP_EXC_*') */
#define PR_SET_FPEXC           12 /* [int arg] Set FPU exception mode (PPC only; set of `PR_FP_EXC_*') */
#   define PR_FP_EXC_DISABLED  0x00000000 /* FPU exceptions disabled */
#   define PR_FP_EXC_NONRECOV  0x00000001 /* ??? */
#   define PR_FP_EXC_ASYNC     0x00000002 /* ??? */
#   define PR_FP_EXC_PRECISE   0x00000003 /* ??? */
#   define PR_FP_EXC_SW_ENABLE 0x00000080 /* ??? */
#   define PR_FP_EXC_DIV       0x00010000 /* Divide by zero */
#   define PR_FP_EXC_OVF       0x00020000 /* Overflow */
#   define PR_FP_EXC_UND       0x00040000 /* Underflow */
#   define PR_FP_EXC_RES       0x00080000 /* Inexact result */
#   define PR_FP_EXC_INV       0x00100000 /* Invalid operation */
#endif /* !__USE_KOS_PURE || __powerpc__ */

/* ??? */
#define PR_GET_TIMING          13 /* Returns `PR_TIMING_STATISTICAL' */
#define PR_SET_TIMING          14 /* [int arg] Requires that `arg' be `PR_TIMING_STATISTICAL' */
#   define PR_TIMING_STATISTICAL 0x00000000 /* ??? */
#   define PR_TIMING_TIMESTAMP   0x00000001 /* ??? */

/* Process name */
#define PR_SET_NAME            15 /* [char const *arg] `write(open("/proc/thread-self/comm"))' */
#define PR_GET_NAME            16 /* [char arg[TASK_COMM_LEN]] `read(open("/proc/thread-self/comm"))' */
#ifdef __USE_KOS
#if !defined(TASK_COMM_LEN) && defined(__TASK_COMM_LEN)
#define TASK_COMM_LEN __TASK_COMM_LEN /* The max length of the task command name (including the trailing NUL) */
#endif /* !TASK_COMM_LEN && __TASK_COMM_LEN */
#endif /* __USE_KOS */

/* Process endian */
#define PR_GET_ENDIAN          19 /* [int *arg] Return one of `PR_ENDIAN_*' */
#define PR_SET_ENDIAN          20 /* [int arg] Set endian (one of `PR_ENDIAN_*') */
#   define PR_ENDIAN_BIG       0x00000000 /* Big endian */
#   define PR_ENDIAN_LITTLE    0x00000001 /* Little endian */
#if !defined(__USE_KOS_PURE) || defined(__powerpc__)
#   define PR_ENDIAN_PPC_LITTLE 0x00000002 /* Pseudo little endian (powerpc-only) */
#endif /* !__USE_KOS_PURE || __powerpc__ */

/* ??? */
#define PR_GET_SECCOMP         21 /* [int return] ??? */
#define PR_SET_SECCOMP         22 /* [int arg] ??? */

/* Access process capability bounding set */
#define PR_CAPBSET_READ        23 /* [int cred] Do `return credcap_capable(&THIS_CRED->c_cap_bounding, cred)' */
#define PR_CAPBSET_DROP        24 /* [int cred] Do `credcap_turnoff(&THIS_CRED->c_cap_bounding, cred)' (requires `CAP_SETPCAP') */

/* Control access to `__rdtsc()' (from <asm/intrin.h>) */
#if !defined(__USE_KOS_PURE) || defined(__i386__) || defined(__x86_64__)
#define PR_GET_TSC             25 /* [int *arg] Get TSC-allowed status */
#define PR_SET_TSC             26 /* [int arg] Set TSC-allowed status */
#   define PR_TSC_ENABLE       0x00000001 /* Allow use */
#   define PR_TSC_SIGSEGV      0x00000002 /* Raise SIGSEGV on use */
#endif /* !__USE_KOS_PURE || __i386__ || __x86_64__ */

/* Access credentials "securebits" */
#define PR_GET_SECUREBITS      27 /* [int return] Return `THIS_CRED->c_securebits' */
#define PR_SET_SECUREBITS      28 /* [int arg] Set `THIS_CRED->c_securebits' (EPERM if not allowed) */

/* ??? */
#define PR_SET_TIMERSLACK      29 /* [syscall_ulong_t arg] ??? */
#define PR_GET_TIMERSLACK      30 /* [syscall_ulong_t return] ??? */

/* ??? */
#define PR_TASK_PERF_EVENTS_DISABLE 31 /* [void] ??? */
#define PR_TASK_PERF_EVENTS_ENABLE  32 /* [void] ??? */

/* ??? */
#define PR_MCE_KILL            33 /* [int arg] Arg is one of `PR_MCE_KILL_CLEAR', `PR_MCE_KILL_SET' */
#   define PR_MCE_KILL_CLEAR   0x00000000 /* [0, 0, 0]  ??? */
#   define PR_MCE_KILL_SET     0x00000001 /* [int mode, 0, 0] Mode is one of `PR_MCE_KILL_LATE', `PR_MCE_KILL_EARLY', `PR_MCE_KILL_DEFAULT' */
#      define PR_MCE_KILL_LATE    0x00000000 /* ??? */
#      define PR_MCE_KILL_EARLY   0x00000001 /* ??? */
#      define PR_MCE_KILL_DEFAULT 0x00000002 /* ??? */
#define PR_MCE_KILL_GET        34 /* [int return, 0, 0, 0, 0] ??? */

/* Set user-space memory address ranges */
#define PR_SET_MM              35    /* [int arg] Arg is one of `PR_SET_MM_*' */
#    define PR_SET_MM_START_CODE  1  /* [void *addr, 0, 0] Set .tect start address */
#    define PR_SET_MM_END_CODE    2  /* [void *addr, 0, 0] Set .text end address */
#    define PR_SET_MM_START_DATA  3  /* [void *addr, 0, 0] Set .data start address */
#    define PR_SET_MM_END_DATA    4  /* [void *addr, 0, 0] Set .data end address */
#    define PR_SET_MM_START_STACK 5  /* [void *addr, 0, 0] Set stack start address */
#    define PR_SET_MM_START_BRK   6  /* [void *addr, 0, 0] Set program break start address (and stack end address) */
#    define PR_SET_MM_BRK         7  /* [void *addr, 0, 0] Set program break end address */
#    define PR_SET_MM_ARG_START   8  /* [void *addr, 0, 0] Set start address of argv */
#    define PR_SET_MM_ARG_END     9  /* [void *addr, 0, 0] Set end address of argv */
#    define PR_SET_MM_ENV_START   10 /* [void *addr, 0, 0] Set start address of environ */
#    define PR_SET_MM_ENV_END     11 /* [void *addr, 0, 0] Set end address of environ */
#    define PR_SET_MM_AUXV        12 /* [ElfW(auxv_t) const *vec, size_t vecsize, 0] Set auxv vector */
#    define PR_SET_MM_EXE_FILE    13 /* [fd_t fd, 0, 0] Set main executable file */
#    define PR_SET_MM_MAP         14 /* [struct prctl_mm_map const *map, size_t mapsize, 0] Set all ranges (WARNING: NO EMULATION IN COMPATIBILITY MODE!) */
#    define PR_SET_MM_MAP_SIZE    15 /* [unsigned int *arg, 0, 0] Stores `sizeof(struct prctl_mm_map)' */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("start_code")
#pragma push_macro("end_code")
#pragma push_macro("start_data")
#pragma push_macro("end_data")
#pragma push_macro("start_brk")
#pragma push_macro("brk")
#pragma push_macro("start_stack")
#pragma push_macro("arg_start")
#pragma push_macro("arg_end")
#pragma push_macro("env_start")
#pragma push_macro("env_end")
#pragma push_macro("auxv")
#pragma push_macro("auxv_size")
#pragma push_macro("exe_fd")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef start_code
#undef end_code
#undef start_data
#undef end_data
#undef start_brk
#undef brk
#undef start_stack
#undef arg_start
#undef arg_end
#undef env_start
#undef env_end
#undef auxv
#undef auxv_size
#undef exe_fd
struct prctl_mm_map {
	__u64 start_code;  /* .text start */
	__u64 end_code;    /* .text end */
	__u64 start_data;  /* .data start */
	__u64 end_data;    /* .data end */
	__u64 start_brk;   /* Program break start / stack end */
	__u64 brk;         /* Program break end */
	__u64 start_stack; /* Stack start */
	__u64 arg_start;   /* argv start */
	__u64 arg_end;     /* argv end */
	__u64 env_start;   /* environ start */
	__u64 env_end;     /* environ end */
	__u64 *auxv;       /* Auxv address */
	__u32 auxv_size;   /* Auxv length (in bytes) */
	__u32 exe_fd;      /* Program exe file descriptor */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("exe_fd")
#pragma pop_macro("auxv_size")
#pragma pop_macro("auxv")
#pragma pop_macro("env_end")
#pragma pop_macro("env_start")
#pragma pop_macro("arg_end")
#pragma pop_macro("arg_start")
#pragma pop_macro("start_stack")
#pragma pop_macro("brk")
#pragma pop_macro("start_brk")
#pragma pop_macro("end_data")
#pragma pop_macro("start_data")
#pragma pop_macro("end_code")
#pragma pop_macro("start_code")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

/* Child sub-reaper */
#define PR_SET_CHILD_SUBREAPER 36 /* [bool enable] Mark/unmark the calling process as a child sub-reaper */
#define PR_GET_CHILD_SUBREAPER 37 /* [int *arg] Return caller's child sub-reaper attribute */

/* Get/Set process no-new-privs attribute -- When non-zero, exec() calls do not add new permissions. */
#define PR_SET_NO_NEW_PRIVS    38 /* [int arg, 0, 0, 0] Set `THIS_CRED->c_no_new_privs = arg' (cannot be set to 0 if already non-zero) */
#define PR_GET_NO_NEW_PRIVS    39 /* [int return, 0, 0, 0, 0] Return `THIS_CRED->c_no_new_privs' */

/* Thread TID address. */
#define PR_GET_TID_ADDRESS     40 /* [pid_t **arg] Return thread TID address (s.a. `set_tid_address(2)', `CLONE_CHILD_CLEARTID') */

/* ??? */
#define PR_SET_THP_DISABLE     41 /* [bool arg] ??? */
#define PR_GET_THP_DISABLE     42 /* [bool return] ??? */

/* User-managed bounds tables control (x86-only; removed in linux 5.4) */
#ifndef __USE_KOS_PURE
#define PR_MPX_ENABLE_MANAGEMENT  43 /* [0, 0, 0, 0] Enable */
#define PR_MPX_DISABLE_MANAGEMENT 44 /* [0, 0, 0, 0] Disable */
#endif /* !__USE_KOS_PURE */

/* FPU mode control (mips only) */
#if !defined(__USE_KOS_PURE) || defined(__mips__)
#define PR_SET_FP_MODE         45 /* [unsigned int arg] Arg is a set of `PR_FP_MODE_*' */
#define PR_GET_FP_MODE         46 /* [unsigned int return] Returns a set of `PR_FP_MODE_*' */
#   define PR_FP_MODE_FR  0x00000001 /* 64-bit FPU registers */
#   define PR_FP_MODE_FRE 0x00000002 /* 32-bit compatibility */
#endif /* !__USE_KOS_PURE || __mips__ */

/* Access control for `THIS_CRED->c_cap_ambient' */
#define PR_CAP_AMBIENT         47 /* [int arg] Arg is one of `PR_CAP_AMBIENT_*' */
#    define PR_CAP_AMBIENT_IS_SET    0x00000001 /* [int cap, 0, 0] Do `return credcap_capable(&THIS_CRED->c_cap_ambient, cred);' */
#    define PR_CAP_AMBIENT_RAISE     0x00000002 /* [int cap, 0, 0] Add `cap' to `c_cap_ambient' (must already appear in `c_cap_permitted' and `c_cap_inheritable'; requires `!SECBIT_NO_CAP_AMBIENT_RAISE') */
#    define PR_CAP_AMBIENT_LOWER     0x00000003 /* [int cap, 0, 0] Do `credcap_turnoff(&THIS_CRED->c_cap_ambient, cred);' */
#    define PR_CAP_AMBIENT_CLEAR_ALL 0x00000004 /* [0, 0, 0] Do `bzero(&THIS_CRED->c_cap_ambient, sizeof(struct credcap));' */

/* Speculative execution control */
#define PR_GET_SPECULATION_CTRL 52 /* [int return, int what, 0, 0, 0] What must be `PR_SPEC_STORE_BYPASS'; Return is set of `PR_SPEC_*' */
#define PR_SET_SPECULATION_CTRL 53 /* [int what, int how, 0, 0] What is one of `PR_SPEC_STORE_BYPASS', `PR_SPEC_INDIRECT_BRANCH'; How is set of `PR_SPEC_*' */
#   define PR_SPEC_STORE_BYPASS    0x00000000 /* ??? */
#   define PR_SPEC_INDIRECT_BRANCH 0x00000001 /* ??? */
/* Bits for `PR_GET_SPECULATION_CTRL' and `PR_SET_SPECULATION_CTRL' */
#   define PR_SPEC_NOT_AFFECTED  0x00000000 /* ??? */
#   define PR_SPEC_PRCTL         0x00000001 /* ??? */
#   define PR_SPEC_ENABLE        0x00000002 /* ??? */
#   define PR_SPEC_DISABLE       0x00000004 /* ??? */
#   define PR_SPEC_FORCE_DISABLE 0x00000008 /* ??? */

/* ??? */
#if !defined(__USE_KOS_PURE) || defined(__arm64__)
#define PR_PAC_RESET_KEYS       54 /* [int what, 0, 0, 0] What is a set of `PR_PAC_AP' */
#   define PR_PAC_APIAKEY       0x00000001 /* ... */
#   define PR_PAC_APIBKEY       0x00000002 /* ... */
#   define PR_PAC_APDAKEY       0x00000004 /* ... */
#   define PR_PAC_APDBKEY       0x00000008 /* ... */
#   define PR_PAC_APGAKEY       0x00000010 /* ... */
#endif /* !__USE_KOS_PURE || __arm64__ */

/* ??? */
#if !defined(__USE_KOS_PURE) || defined(__arm64__)
#define PR_SET_TAGGED_ADDR_CTRL 55 /* [int arg, 0, 0, 0] Arg is one of `0', `PR_TAGGED_ADDR_ENABLE' */
#define PR_GET_TAGGED_ADDR_CTRL 56 /* [int return, 0, 0, 0, 0] Returns a set of ??? */
#   define PR_TAGGED_ADDR_ENABLE   0x00000001 /* ??? */
#   define PR_MTE_TCF_SHIFT        1          /* TagCheckFault */
#   define PR_MTE_TCF_NONE         0x00000000 /* == 0 << PR_MTE_TCF_SHIFT */
#   define PR_MTE_TCF_SYNC         0x00000002 /* == 1 << PR_MTE_TCF_SHIFT */
#   define PR_MTE_TCF_ASYNC        0x00000004 /* == 2 << PR_MTE_TCF_SHIFT */
#   define PR_MTE_TCF_MASK         0x00000006 /* == 3 << PR_MTE_TCF_SHIFT */
#   define PR_MTE_TAG_SHIFT        3          /* Tag including mask */
#   define PR_MTE_TAG_MASK         0x0007fff8 /* == 0xffff << PR_MTE_TAG_SHIFT */
#endif /* !__USE_KOS_PURE || __arm64__ */

/* ??? */
#define PR_SET_IO_FLUSHER 57 /* [int arg, 0, 0, 0] ??? */
#define PR_GET_IO_FLUSHER 58 /* [int return, 0, 0, 0, 0] ??? */


/* ??? */
#define PR_SET_PTRACER         0x59616d61 /* Set PID of who can trace this process (0: no-one; PR_SET_PTRACER_ANY: everyone) */
#   define PR_SET_PTRACER_ANY  (__CCAST(__syscall_ulong_t)(-1)) /* Anyone can trace this process */

/* KOS-specific prctl codes */
#ifdef __KOS__
#define PR_KOS_GET_AT_SECURE 0x8050fff1 /* [int return] Returns 0/1 indicative of `getauxval(AT_SECURE)' */
#endif /* __KOS__ */

/* clang-format on */


#endif /* !_LINUX_PRCTL_H */
