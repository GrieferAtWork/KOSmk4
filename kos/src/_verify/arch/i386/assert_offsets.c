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
#ifndef GUARD__VERIFY_ARCH_I386_ASSERT_TYPES_C
#define GUARD__VERIFY_ARCH_I386_ASSERT_TYPES_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define __WANT_FULL_STRUCT_STAT 1
#ifndef __KERNEL__
#define _FILE_OFFSET_BITS 32
#define _TIME_T_BITS 32
#endif /* !__KERNEL__ */

#include <hybrid/host.h>

#ifdef __x86_64__
#define __kos_statx32_alias64 __kos_statx32_alias64
#define __kos_statx64_alias64 stat64
#else /* __x86_64__ */
#define __kos_statx32_alias64 stat64
#define __kos_statx64_alias64 __kos_statx64_alias64
#endif /* !__x86_64__ */

#include <hybrid/compiler.h>

#include <assert.h>
#include <ieee754.h>
#include <stdalign.h>
#include <stddef.h>

static_assert(sizeof(union ieee754_float) == 4);
static_assert(alignof(union ieee754_float) == 4);
static_assert(sizeof(union ieee754_double) == 8);
static_assert(alignof(union ieee754_double) == 8);
static_assert(sizeof(union ieee854_long_double) == 16);
static_assert(alignof(union ieee854_long_double) == 16);
static_assert(sizeof(union ieee854_float80) == 10);
static_assert(sizeof(((union ieee854_float80 *)0)->ieee) == 10);
static_assert(sizeof(((union ieee854_float80 *)0)->ieee_nan) == 10);

/*[[[deemon
import * from .....misc.libgen.assert_offsetof;
local files = {
	"../../../../include/i386-kos/bits/os/generic/iovec32.h",
	"../../../../include/i386-kos/bits/os/generic/iovec64.h",
	"../../../../include/i386-kos/bits/os/generic/itimerspec32.h",
	"../../../../include/i386-kos/bits/os/generic/itimerspec64.h",
	"../../../../include/i386-kos/bits/os/generic/itimerval32.h",
	"../../../../include/i386-kos/bits/os/generic/itimerval64.h",
	"../../../../include/i386-kos/bits/os/generic/timespec32.h",
	"../../../../include/i386-kos/bits/os/generic/timespec64.h",
	"../../../../include/i386-kos/bits/os/generic/timeval32.h",
	"../../../../include/i386-kos/bits/os/generic/timeval64.h",
	"../../../../include/i386-kos/bits/os/generic/sigset_with_size32.h",
	"../../../../include/i386-kos/bits/os/generic/sigset_with_size64.h",
	"../../../../include/i386-kos/bits/os/kos/cmsghdr32.h",
	"../../../../include/i386-kos/bits/os/kos/cmsghdr64.h",
	"../../../../include/i386-kos/bits/os/kos/flock32.h",
	"../../../../include/i386-kos/bits/os/kos/flock64.h",
	"../../../../include/i386-kos/bits/os/kos/mmsghdr32.h",
	"../../../../include/i386-kos/bits/os/kos/mmsghdr64.h",
	"../../../../include/i386-kos/bits/os/kos/msghdr32.h",
	"../../../../include/i386-kos/bits/os/kos/msghdr64.h",
	"../../../../include/i386-kos/bits/os/kos/rusage32.h",
	"../../../../include/i386-kos/bits/os/kos/rusage64.h",
	"../../../../include/i386-kos/bits/os/kos/sigaction32.h",
	"../../../../include/i386-kos/bits/os/kos/sigaction64.h",
	"../../../../include/i386-kos/bits/os/kos/sigevent32.h",
	"../../../../include/i386-kos/bits/os/kos/sigevent64.h",
	"../../../../include/i386-kos/bits/os/kos/siginfo32.h",
	"../../../../include/i386-kos/bits/os/kos/siginfo64.h",
	"../../../../include/i386-kos/bits/os/kos/sigstack32.h",
	"../../../../include/i386-kos/bits/os/kos/sigstack64.h",
	"../../../../include/i386-kos/bits/os/kos/sigval32.h",
	"../../../../include/i386-kos/bits/os/kos/sigval64.h",
	"../../../../include/i386-kos/bits/os/kos/statfs32.h",
	"../../../../include/i386-kos/bits/os/kos/statfs64.h",
	"../../../../include/i386-kos/bits/os/kos/timeb32.h",
	"../../../../include/i386-kos/bits/os/kos/timeb64.h",
	"../../../../include/i386-kos/bits/os/kos/tms32.h",
	"../../../../include/i386-kos/bits/os/kos/tms64.h",
	"../../../../include/i386-kos/bits/os/kos/utimbuf32.h",
	"../../../../include/i386-kos/bits/os/kos/utimbuf64.h",
	"../../../../include/i386-kos/bits/va_list-struct32.h",
	"../../../../include/i386-kos/bits/va_list-struct64.h",
	"../../../../include/i386-kos/bits/os/kos/mcontext32.h",
	"../../../../include/i386-kos/bits/os/kos/mcontext64.h",
	"../../../../include/i386-kos/bits/os/linux/mcontext32.h",
	"../../../../include/i386-kos/bits/os/linux/mcontext64.h",
	"../../../../include/i386-kos/bits/os/cygwin/mcontext32.h",
	"../../../../include/i386-kos/bits/os/cygwin/mcontext64.h",
	"../../../../include/i386-kos/bits/os/kos/ucontext32.h",
	"../../../../include/i386-kos/bits/os/kos/ucontext64.h",
	"../../../../include/i386-kos/bits/os/linux/ucontext32.h",
	"../../../../include/i386-kos/bits/os/linux/ucontext64.h",
	"../../../../include/i386-kos/bits/os/cygwin/ucontext32.h",
	"../../../../include/i386-kos/bits/os/cygwin/ucontext64.h",
	"../../../../include/i386-kos/kos/bits/debugtrap32.h",
	"../../../../include/i386-kos/kos/bits/debugtrap64.h",
	"../../../../include/i386-kos/kos/bits/exception_data32.h",
	"../../../../include/i386-kos/kos/bits/exception_data64.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct32.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct64.h",
	"../../../../include/i386-kos/kos/bits/syscall-info32.h",
	"../../../../include/i386-kos/kos/bits/syscall-info64.h",
	"../../../../include/i386-kos/kos/exec/asm/elf32.h",
	"../../../../include/i386-kos/kos/exec/asm/elf64.h",
	"../../../../include/i386-kos/kos/exec/bits/peb32.h",
	"../../../../include/i386-kos/kos/exec/bits/peb64.h",
	"../../../../include/i386-kos/kos/kernel/bits/cpu-state32.h",
	"../../../../include/i386-kos/kos/kernel/bits/cpu-state64.h",
	"../../../../include/i386-kos/kos/kernel/bits/fpu-sstate.h",
	"../../../../include/i386-kos/kos/kernel/bits/fpu-state32.h",
	"../../../../include/i386-kos/kos/kernel/bits/fpu-state64.h",
	"../../../../include/i386-kos/kos/kernel/x86/tss16.h",
	"../../../../include/i386-kos/kos/kernel/x86/tss32.h",
	"../../../../include/i386-kos/kos/kernel/x86/tss64.h",
};

local include_prefixes = {
	"../../../../include/i386-kos",
	"../../../../include",
};

function genAsserts(f) {
	for (local pfx: include_prefixes) {
		if (f.startswith(pfx)) {
			print "#include <" + f[#pfx:].lstrip("/") + ">";
			goto do_gen_asserts;
		}
	}
	print "#include", repr(f);
do_gen_asserts:
	generateAssertions(f);
	print;
	print;
	print;
	print;
	print;
}


for (local f: files)
	genAsserts(f);

for (local i: [:8]) {
	print f"static_assert(offsetof(struct sfpustate, fs_regs[{i}]) == OFFSET_SFPUSTATE_ST({i}));";
	print f"static_assert(offsetof(struct sfpustate, fs_regs[{i}]) == OFFSET_SFPUSTATE_MM({i}));";
}
for (local i: [:8]) {
	print f"static_assert(offsetof(struct xfpustate32, fx_regs[{i}]) == OFFSET_XFPUSTATE32_ST({i}));";
	print f"static_assert(offsetof(struct xfpustate32, fx_regs[{i}]) == OFFSET_XFPUSTATE32_MM({i}));";
}
for (local i: [:8])
	print f"static_assert(offsetof(struct xfpustate32, fx_xmm[{i}]) == OFFSET_XFPUSTATE32_XMM({i}));";
for (local i: [:8]) {
	print f"static_assert(offsetof(struct xfpustate64, fx_regs[{i}]) == OFFSET_XFPUSTATE64_ST({i}));";
	print f"static_assert(offsetof(struct xfpustate64, fx_regs[{i}]) == OFFSET_XFPUSTATE64_MM({i}));";
}
for (local i: [:16])
	print f"static_assert(offsetof(struct xfpustate64, fx_xmm[{i}]) == OFFSET_XFPUSTATE64_XMM({i}));";
for (local i: [1:8])
	print f"static_assert(OFFSET_TSS64_IST{i} == OFFSET_TSS64_IST({i}));";
for (local i: [:16]) {
	print "#if X86_64_VA_LIST_XMM_COUNT >=",i;
	print f"static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[{i}]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM({i}));";
	print "#endif";
}

]]]*/
#include <bits/os/generic/iovec32.h>

/* struct __iovecx32 */
static_assert(offsetof(struct __iovecx32, iov_base) == __OFFSET_IOVECX32_BASE);
static_assert(offsetof(struct __iovecx32, iov_len) == __OFFSET_IOVECX32_LEN);
static_assert(sizeof(struct __iovecx32) == __SIZEOF_IOVECX32);
static_assert(alignof(struct __iovecx32) == __ALIGNOF_IOVECX32);





#include <bits/os/generic/iovec64.h>

/* struct __iovecx64 */
static_assert(offsetof(struct __iovecx64, iov_base) == __OFFSET_IOVECX64_BASE);
static_assert(offsetof(struct __iovecx64, iov_len) == __OFFSET_IOVECX64_LEN);
static_assert(sizeof(struct __iovecx64) == __SIZEOF_IOVECX64);
static_assert(alignof(struct __iovecx64) == __ALIGNOF_IOVECX64);





#include <bits/os/generic/itimerspec32.h>

/* struct itimerspecx32 */
static_assert(offsetof(struct itimerspecx32, it_interval) == __OFFSET_ITIMERSPECX32_INTERVAL);
static_assert(offsetof(struct itimerspecx32, it_value) == __OFFSET_ITIMERSPECX32_VALUE);
static_assert(sizeof(struct itimerspecx32) == __SIZEOF_ITIMERSPECX32);
static_assert(alignof(struct itimerspecx32) == __ALIGNOF_ITIMERSPECX32);

/* struct itimerspecx32_64 */
static_assert(offsetof(struct itimerspecx32_64, it_interval) == __OFFSET_ITIMERSPECX32_64_INTERVAL);
static_assert(offsetof(struct itimerspecx32_64, it_value) == __OFFSET_ITIMERSPECX32_64_VALUE);
static_assert(sizeof(struct itimerspecx32_64) == __SIZEOF_ITIMERSPECX32_64);
static_assert(alignof(struct itimerspecx32_64) == __ALIGNOF_ITIMERSPECX32_64);

/* struct __itimerspecx32_64_alt */
/* ... */





#include <bits/os/generic/itimerspec64.h>

/* struct itimerspecx64 */
static_assert(offsetof(struct itimerspecx64, it_interval) == __OFFSET_ITIMERSPECX64_INTERVAL);
static_assert(offsetof(struct itimerspecx64, it_value) == __OFFSET_ITIMERSPECX64_VALUE);
static_assert(sizeof(struct itimerspecx64) == __SIZEOF_ITIMERSPECX64);
static_assert(alignof(struct itimerspecx64) == __ALIGNOF_ITIMERSPECX64);

/* struct __itimerspecx64_alt */
/* ... */





#include <bits/os/generic/itimerval32.h>

/* struct itimervalx32 */
static_assert(offsetof(struct itimervalx32, it_interval) == __OFFSET_ITIMERVALX32_INTERVAL);
static_assert(offsetof(struct itimervalx32, it_value) == __OFFSET_ITIMERVALX32_VALUE);
static_assert(sizeof(struct itimervalx32) == __SIZEOF_ITIMERVALX32);
static_assert(alignof(struct itimervalx32) == __ALIGNOF_ITIMERVALX32);

/* struct itimervalx32_64 */
static_assert(offsetof(struct itimervalx32_64, it_interval) == __OFFSET_ITIMERVALX32_64_INTERVAL);
static_assert(offsetof(struct itimervalx32_64, it_value) == __OFFSET_ITIMERVALX32_64_VALUE);
static_assert(sizeof(struct itimervalx32_64) == __SIZEOF_ITIMERVALX32_64);
static_assert(alignof(struct itimervalx32_64) == __ALIGNOF_ITIMERVALX32_64);

/* struct __itimervalx32_64_alt */
/* ... */





#include <bits/os/generic/itimerval64.h>

/* struct itimervalx64 */
static_assert(offsetof(struct itimervalx64, it_interval) == __OFFSET_ITIMERVALX64_INTERVAL);
static_assert(offsetof(struct itimervalx64, it_value) == __OFFSET_ITIMERVALX64_VALUE);
static_assert(sizeof(struct itimervalx64) == __SIZEOF_ITIMERVALX64);
static_assert(alignof(struct itimervalx64) == __ALIGNOF_ITIMERVALX64);

/* struct __itimervalx64_alt */
/* ... */





#include <bits/os/generic/timespec32.h>

/* struct timespecx32 */
static_assert(offsetof(struct timespecx32, tv_nsec) == __OFFSET_TIMESPECX32_NSEC);
static_assert(offsetof(struct timespecx32, tv_sec) == __OFFSET_TIMESPECX32_SEC);
static_assert(sizeof(struct timespecx32) == __SIZEOF_TIMESPECX32);
static_assert(alignof(struct timespecx32) == __ALIGNOF_TIMESPECX32);

/* struct timespecx32_64 */
static_assert(offsetof(struct timespecx32_64, tv_nsec) == __OFFSET_TIMESPECX32_64_NSEC);
static_assert(offsetof(struct timespecx32_64, tv_sec) == __OFFSET_TIMESPECX32_64_SEC);
static_assert(sizeof(struct timespecx32_64) == __SIZEOF_TIMESPECX32_64);
static_assert(alignof(struct timespecx32_64) == __ALIGNOF_TIMESPECX32_64);

/* struct __timespecx32_64_alt */
/* ... */





#include <bits/os/generic/timespec64.h>

/* struct timespecx64 */
static_assert(offsetof(struct timespecx64, tv_nsec) == __OFFSET_TIMESPECX64_NSEC);
static_assert(offsetof(struct timespecx64, tv_sec) == __OFFSET_TIMESPECX64_SEC);
static_assert(sizeof(struct timespecx64) == __SIZEOF_TIMESPECX64);
static_assert(alignof(struct timespecx64) == __ALIGNOF_TIMESPECX64);

/* struct __timespecx64_alt */
/* ... */





#include <bits/os/generic/timeval32.h>

/* struct timevalx32 */
static_assert(offsetof(struct timevalx32, tv_sec) == __OFFSET_TIMEVALX32_SEC);
static_assert(offsetof(struct timevalx32, tv_usec) == __OFFSET_TIMEVALX32_USEC);
static_assert(sizeof(struct timevalx32) == __SIZEOF_TIMEVALX32);
static_assert(alignof(struct timevalx32) == __ALIGNOF_TIMEVALX32);

/* struct timevalx32_64 */
static_assert(offsetof(struct timevalx32_64, tv_sec) == __OFFSET_TIMEVALX32_64_SEC);
static_assert(offsetof(struct timevalx32_64, tv_usec) == __OFFSET_TIMEVALX32_64_USEC);
static_assert(sizeof(struct timevalx32_64) == __SIZEOF_TIMEVALX32_64);
static_assert(alignof(struct timevalx32_64) == __ALIGNOF_TIMEVALX32_64);

/* struct __timevalx32_64_alt */
/* ... */





#include <bits/os/generic/timeval64.h>

/* struct timevalx64 */
static_assert(offsetof(struct timevalx64, tv_sec) == __OFFSET_TIMEVALX64_SEC);
static_assert(offsetof(struct timevalx64, tv_usec) == __OFFSET_TIMEVALX64_USEC);
static_assert(sizeof(struct timevalx64) == __SIZEOF_TIMEVALX64);
static_assert(alignof(struct timevalx64) == __ALIGNOF_TIMEVALX64);

/* struct __timevalx64_alt */
/* ... */





#include <bits/os/generic/sigset_with_size32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __sigset_with_sizex32 */
static_assert(offsetof(struct __sigset_with_sizex32, sws_sigset) == __OFFSET_SIGSET_WITH_SIZEX32_SIGSET);
static_assert(offsetof(struct __sigset_with_sizex32, sws_sigsiz) == __OFFSET_SIGSET_WITH_SIZEX32_SIGSIZ);
static_assert(sizeof(struct __sigset_with_sizex32) == __SIZEOF_SIGSET_WITH_SIZEX32);
static_assert(alignof(struct __sigset_with_sizex32) == __ALIGNOF_SIGSET_WITH_SIZEX32);





#include <bits/os/generic/sigset_with_size64.h>

/* struct __sigset_with_sizex64 */
static_assert(offsetof(struct __sigset_with_sizex64, sws_sigset) == __OFFSET_SIGSET_WITH_SIZEX64_SIGSET);
static_assert(offsetof(struct __sigset_with_sizex64, sws_sigsiz) == __OFFSET_SIGSET_WITH_SIZEX64_SIGSIZ);
static_assert(sizeof(struct __sigset_with_sizex64) == __SIZEOF_SIGSET_WITH_SIZEX64);
static_assert(alignof(struct __sigset_with_sizex64) == __ALIGNOF_SIGSET_WITH_SIZEX64);





#include <bits/os/kos/cmsghdr32.h>

/* struct __cmsghdrx32 */
static_assert(offsetof(struct __cmsghdrx32, cmsg_data) == __OFFSET_CMSGHDRX32_DATA);
static_assert(offsetof(struct __cmsghdrx32, cmsg_len) == __OFFSET_CMSGHDRX32_LEN);
static_assert(offsetof(struct __cmsghdrx32, cmsg_level) == __OFFSET_CMSGHDRX32_LEVEL);
static_assert(offsetof(struct __cmsghdrx32, cmsg_type) == __OFFSET_CMSGHDRX32_TYPE);
static_assert(alignof(struct __cmsghdrx32) == __ALIGNOF_CMSGHDRX32);





#include <bits/os/kos/cmsghdr64.h>

/* struct __cmsghdrx64 */
static_assert(offsetof(struct __cmsghdrx64, cmsg_data) == __OFFSET_CMSGHDRX64_DATA);
static_assert(offsetof(struct __cmsghdrx64, cmsg_len) == __OFFSET_CMSGHDRX64_LEN);
static_assert(offsetof(struct __cmsghdrx64, cmsg_level) == __OFFSET_CMSGHDRX64_LEVEL);
static_assert(offsetof(struct __cmsghdrx64, cmsg_type) == __OFFSET_CMSGHDRX64_TYPE);
static_assert(alignof(struct __cmsghdrx64) == __ALIGNOF_CMSGHDRX64);





#include <bits/os/kos/flock32.h>

/* struct flockx32 */
static_assert(offsetof(struct flockx32, l_len) == __OFFSET_FLOCKX32_LEN);
static_assert(offsetof(struct flockx32, l_pid) == __OFFSET_FLOCKX32_PID);
static_assert(offsetof(struct flockx32, l_start) == __OFFSET_FLOCKX32_START);
static_assert(offsetof(struct flockx32, l_type) == __OFFSET_FLOCKX32_TYPE);
static_assert(offsetof(struct flockx32, l_whence) == __OFFSET_FLOCKX32_WHENCE);
static_assert(sizeof(struct flockx32) == __SIZEOF_FLOCKX32);

/* struct flockx32_64 */
static_assert(offsetof(struct flockx32_64, l_len) == __OFFSET_FLOCKX32_64_LEN);
static_assert(offsetof(struct flockx32_64, l_pid) == __OFFSET_FLOCKX32_64_PID);
static_assert(offsetof(struct flockx32_64, l_start) == __OFFSET_FLOCKX32_64_START);
static_assert(offsetof(struct flockx32_64, l_type) == __OFFSET_FLOCKX32_64_TYPE);
static_assert(offsetof(struct flockx32_64, l_whence) == __OFFSET_FLOCKX32_64_WHENCE);
static_assert(sizeof(struct flockx32_64) == __SIZEOF_FLOCKX32_64);

/* struct __flockx32_64_alt */
/* ... */





#include <bits/os/kos/flock64.h>

/* struct flockx64 */
static_assert(offsetof(struct flockx64, l_len) == __OFFSET_FLOCKX64_LEN);
static_assert(offsetof(struct flockx64, l_pid) == __OFFSET_FLOCKX64_PID);
static_assert(offsetof(struct flockx64, l_start) == __OFFSET_FLOCKX64_START);
static_assert(offsetof(struct flockx64, l_type) == __OFFSET_FLOCKX64_TYPE);
static_assert(offsetof(struct flockx64, l_whence) == __OFFSET_FLOCKX64_WHENCE);
static_assert(sizeof(struct flockx64) == __SIZEOF_FLOCKX64);

/* struct __flockx64_alt */
/* ... */





#include <bits/os/kos/mmsghdr32.h>

/* struct __mmsghdrx32 */
static_assert(offsetof(struct __mmsghdrx32, msg_hdr) == __OFFSET_MMSGHDRX32_HDR);
static_assert(offsetof(struct __mmsghdrx32, msg_len) == __OFFSET_MMSGHDRX32_LEN);
static_assert(sizeof(struct __mmsghdrx32) == __SIZEOF_MMSGHDRX32);
static_assert(alignof(struct __mmsghdrx32) == __ALIGNOF_MMSGHDRX32);





#include <bits/os/kos/mmsghdr64.h>

/* struct __mmsghdrx64 */
static_assert(offsetof(struct __mmsghdrx64, msg_hdr) == __OFFSET_MMSGHDRX64_HDR);
static_assert(offsetof(struct __mmsghdrx64, msg_len) == __OFFSET_MMSGHDRX64_LEN);
static_assert(sizeof(struct __mmsghdrx64) == __SIZEOF_MMSGHDRX64);
static_assert(alignof(struct __mmsghdrx64) == __ALIGNOF_MMSGHDRX64);





#include <bits/os/kos/msghdr32.h>

/* struct __msghdrx32 */
static_assert(offsetof(struct __msghdrx32, msg_control) == __OFFSET_MSGHDRX32_CONTROL);
static_assert(offsetof(struct __msghdrx32, msg_controllen) == __OFFSET_MSGHDRX32_CONTROLLEN);
static_assert(offsetof(struct __msghdrx32, msg_flags) == __OFFSET_MSGHDRX32_FLAGS);
static_assert(offsetof(struct __msghdrx32, msg_iov) == __OFFSET_MSGHDRX32_IOV);
static_assert(offsetof(struct __msghdrx32, msg_iovlen) == __OFFSET_MSGHDRX32_IOVLEN);
static_assert(offsetof(struct __msghdrx32, msg_name) == __OFFSET_MSGHDRX32_NAME);
static_assert(offsetof(struct __msghdrx32, msg_namelen) == __OFFSET_MSGHDRX32_NAMELEN);
static_assert(sizeof(struct __msghdrx32) == __SIZEOF_MSGHDRX32);
static_assert(alignof(struct __msghdrx32) == __ALIGNOF_MSGHDRX32);





#include <bits/os/kos/msghdr64.h>

/* struct __msghdrx64 */
static_assert(offsetof(struct __msghdrx64, msg_control) == __OFFSET_MSGHDRX64_CONTROL);
static_assert(offsetof(struct __msghdrx64, msg_controllen) == __OFFSET_MSGHDRX64_CONTROLLEN);
static_assert(offsetof(struct __msghdrx64, msg_flags) == __OFFSET_MSGHDRX64_FLAGS);
static_assert(offsetof(struct __msghdrx64, msg_iov) == __OFFSET_MSGHDRX64_IOV);
static_assert(offsetof(struct __msghdrx64, msg_iovlen) == __OFFSET_MSGHDRX64_IOVLEN);
static_assert(offsetof(struct __msghdrx64, msg_name) == __OFFSET_MSGHDRX64_NAME);
static_assert(offsetof(struct __msghdrx64, msg_namelen) == __OFFSET_MSGHDRX64_NAMELEN);
static_assert(sizeof(struct __msghdrx64) == __SIZEOF_MSGHDRX64);
static_assert(alignof(struct __msghdrx64) == __ALIGNOF_MSGHDRX64);





#include <bits/os/kos/rusage32.h>

/* struct rusagex32 */
static_assert(offsetof(struct rusagex32, ru_idrss) == __OFFSET_RUSAGEX32_IDRSS);
static_assert(offsetof(struct rusagex32, ru_inblock) == __OFFSET_RUSAGEX32_INBLOCK);
static_assert(offsetof(struct rusagex32, ru_isrss) == __OFFSET_RUSAGEX32_ISRSS);
static_assert(offsetof(struct rusagex32, ru_ixrss) == __OFFSET_RUSAGEX32_IXRSS);
static_assert(offsetof(struct rusagex32, ru_majflt) == __OFFSET_RUSAGEX32_MAJFLT);
static_assert(offsetof(struct rusagex32, ru_maxrss) == __OFFSET_RUSAGEX32_MAXRSS);
static_assert(offsetof(struct rusagex32, ru_minflt) == __OFFSET_RUSAGEX32_MINFLT);
static_assert(offsetof(struct rusagex32, ru_msgrcv) == __OFFSET_RUSAGEX32_MSGRCV);
static_assert(offsetof(struct rusagex32, ru_msgsnd) == __OFFSET_RUSAGEX32_MSGSND);
static_assert(offsetof(struct rusagex32, ru_nivcsw) == __OFFSET_RUSAGEX32_NIVCSW);
static_assert(offsetof(struct rusagex32, ru_nsignals) == __OFFSET_RUSAGEX32_NSIGNALS);
static_assert(offsetof(struct rusagex32, ru_nswap) == __OFFSET_RUSAGEX32_NSWAP);
static_assert(offsetof(struct rusagex32, ru_nvcsw) == __OFFSET_RUSAGEX32_NVCSW);
static_assert(offsetof(struct rusagex32, ru_oublock) == __OFFSET_RUSAGEX32_OUBLOCK);
static_assert(offsetof(struct rusagex32, ru_stime) == __OFFSET_RUSAGEX32_STIME);
static_assert(offsetof(struct rusagex32, ru_utime) == __OFFSET_RUSAGEX32_UTIME);
static_assert(sizeof(struct rusagex32) == __SIZEOF_RUSAGEX32);
static_assert(alignof(struct rusagex32) == __ALIGNOF_RUSAGEX32);

/* struct rusagex32_64 */
static_assert(offsetof(struct rusagex32_64, ru_idrss) == __OFFSET_RUSAGEX32_64_IDRSS);
static_assert(offsetof(struct rusagex32_64, ru_inblock) == __OFFSET_RUSAGEX32_64_INBLOCK);
static_assert(offsetof(struct rusagex32_64, ru_isrss) == __OFFSET_RUSAGEX32_64_ISRSS);
static_assert(offsetof(struct rusagex32_64, ru_ixrss) == __OFFSET_RUSAGEX32_64_IXRSS);
static_assert(offsetof(struct rusagex32_64, ru_majflt) == __OFFSET_RUSAGEX32_64_MAJFLT);
static_assert(offsetof(struct rusagex32_64, ru_maxrss) == __OFFSET_RUSAGEX32_64_MAXRSS);
static_assert(offsetof(struct rusagex32_64, ru_minflt) == __OFFSET_RUSAGEX32_64_MINFLT);
static_assert(offsetof(struct rusagex32_64, ru_msgrcv) == __OFFSET_RUSAGEX32_64_MSGRCV);
static_assert(offsetof(struct rusagex32_64, ru_msgsnd) == __OFFSET_RUSAGEX32_64_MSGSND);
static_assert(offsetof(struct rusagex32_64, ru_nivcsw) == __OFFSET_RUSAGEX32_64_NIVCSW);
static_assert(offsetof(struct rusagex32_64, ru_nsignals) == __OFFSET_RUSAGEX32_64_NSIGNALS);
static_assert(offsetof(struct rusagex32_64, ru_nswap) == __OFFSET_RUSAGEX32_64_NSWAP);
static_assert(offsetof(struct rusagex32_64, ru_nvcsw) == __OFFSET_RUSAGEX32_64_NVCSW);
static_assert(offsetof(struct rusagex32_64, ru_oublock) == __OFFSET_RUSAGEX32_64_OUBLOCK);
static_assert(offsetof(struct rusagex32_64, ru_stime) == __OFFSET_RUSAGEX32_64_STIME);
static_assert(offsetof(struct rusagex32_64, ru_utime) == __OFFSET_RUSAGEX32_64_UTIME);
static_assert(sizeof(struct rusagex32_64) == __SIZEOF_RUSAGEX32_64);
static_assert(alignof(struct rusagex32_64) == __ALIGNOF_RUSAGEX32_64);

/* struct __rusagex32_64_alt */
/* ... */





#include <bits/os/kos/rusage64.h>

/* struct rusagex64 */
static_assert(offsetof(struct rusagex64, ru_idrss) == __OFFSET_RUSAGEX64_IDRSS);
static_assert(offsetof(struct rusagex64, ru_inblock) == __OFFSET_RUSAGEX64_INBLOCK);
static_assert(offsetof(struct rusagex64, ru_isrss) == __OFFSET_RUSAGEX64_ISRSS);
static_assert(offsetof(struct rusagex64, ru_ixrss) == __OFFSET_RUSAGEX64_IXRSS);
static_assert(offsetof(struct rusagex64, ru_majflt) == __OFFSET_RUSAGEX64_MAJFLT);
static_assert(offsetof(struct rusagex64, ru_maxrss) == __OFFSET_RUSAGEX64_MAXRSS);
static_assert(offsetof(struct rusagex64, ru_minflt) == __OFFSET_RUSAGEX64_MINFLT);
static_assert(offsetof(struct rusagex64, ru_msgrcv) == __OFFSET_RUSAGEX64_MSGRCV);
static_assert(offsetof(struct rusagex64, ru_msgsnd) == __OFFSET_RUSAGEX64_MSGSND);
static_assert(offsetof(struct rusagex64, ru_nivcsw) == __OFFSET_RUSAGEX64_NIVCSW);
static_assert(offsetof(struct rusagex64, ru_nsignals) == __OFFSET_RUSAGEX64_NSIGNALS);
static_assert(offsetof(struct rusagex64, ru_nswap) == __OFFSET_RUSAGEX64_NSWAP);
static_assert(offsetof(struct rusagex64, ru_nvcsw) == __OFFSET_RUSAGEX64_NVCSW);
static_assert(offsetof(struct rusagex64, ru_oublock) == __OFFSET_RUSAGEX64_OUBLOCK);
static_assert(offsetof(struct rusagex64, ru_stime) == __OFFSET_RUSAGEX64_STIME);
static_assert(offsetof(struct rusagex64, ru_utime) == __OFFSET_RUSAGEX64_UTIME);
static_assert(sizeof(struct rusagex64) == __SIZEOF_RUSAGEX64);
static_assert(alignof(struct rusagex64) == __ALIGNOF_RUSAGEX64);

/* struct __rusagex64_alt */
/* ... */





#include <bits/os/kos/sigaction32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __sigactionx32 */
static_assert(offsetof(struct __sigactionx32, sa_flags) == __OFFSET_SIGACTIONX32_FLAGS);
static_assert(offsetof(struct __sigactionx32, sa_handler) == __OFFSET_SIGACTIONX32_HANDLER);
static_assert(offsetof(struct __sigactionx32, sa_mask) == __OFFSET_SIGACTIONX32_MASK);
static_assert(offsetof(struct __sigactionx32, sa_restorer) == __OFFSET_SIGACTIONX32_RESTORER);
static_assert(offsetof(struct __sigactionx32, sa_sigaction) == __OFFSET_SIGACTIONX32_SIGACTION);
static_assert(sizeof(struct __sigactionx32) == __SIZEOF_SIGACTIONX32);
static_assert(alignof(struct __sigactionx32) == __ALIGNOF_SIGACTIONX32);

/* struct __kernel_sigactionx32 */
static_assert(offsetof(struct __kernel_sigactionx32, sa_flags) == __OFFSET_KERNEL_SIGACTIONX32_FLAGS);
static_assert(offsetof(struct __kernel_sigactionx32, sa_handler) == __OFFSET_KERNEL_SIGACTIONX32_HANDLER);
static_assert(offsetof(struct __kernel_sigactionx32, sa_mask) == __OFFSET_KERNEL_SIGACTIONX32_MASK);
static_assert(offsetof(struct __kernel_sigactionx32, sa_restorer) == __OFFSET_KERNEL_SIGACTIONX32_RESTORER);
static_assert(alignof(struct __kernel_sigactionx32) == __ALIGNOF_KERNEL_SIGACTIONX32);

/* struct __old_kernel_sigactionx32 */
static_assert(offsetof(struct __old_kernel_sigactionx32, sa_flags) == __OFFSET_OLD_KERNEL_SIGACTIONX32_FLAGS);
static_assert(offsetof(struct __old_kernel_sigactionx32, sa_handler) == __OFFSET_OLD_KERNEL_SIGACTIONX32_HANDLER);
static_assert(offsetof(struct __old_kernel_sigactionx32, sa_mask) == __OFFSET_OLD_KERNEL_SIGACTIONX32_MASK);
static_assert(offsetof(struct __old_kernel_sigactionx32, sa_restorer) == __OFFSET_OLD_KERNEL_SIGACTIONX32_RESTORER);
static_assert(sizeof(struct __old_kernel_sigactionx32) == __SIZEOF_OLD_KERNEL_SIGACTIONX32);
static_assert(alignof(struct __old_kernel_sigactionx32) == __ALIGNOF_OLD_KERNEL_SIGACTIONX32);





#include <bits/os/kos/sigaction64.h>

/* struct __sigactionx64 */
static_assert(offsetof(struct __sigactionx64, sa_flags) == __OFFSET_SIGACTIONX64_FLAGS);
static_assert(offsetof(struct __sigactionx64, sa_handler) == __OFFSET_SIGACTIONX64_HANDLER);
static_assert(offsetof(struct __sigactionx64, sa_mask) == __OFFSET_SIGACTIONX64_MASK);
static_assert(offsetof(struct __sigactionx64, sa_restorer) == __OFFSET_SIGACTIONX64_RESTORER);
static_assert(offsetof(struct __sigactionx64, sa_sigaction) == __OFFSET_SIGACTIONX64_SIGACTION);
static_assert(sizeof(struct __sigactionx64) == __SIZEOF_SIGACTIONX64);
static_assert(alignof(struct __sigactionx64) == __ALIGNOF_SIGACTIONX64);





#include <bits/os/kos/sigevent32.h>

/* struct __sigeventx32 */
static_assert(offsetof(struct __sigeventx32, _sigev_data) == __OFFSET_SIGEVENTX32_DATA);
static_assert(offsetof(struct __sigeventx32, _sigev_un._data) == __OFFSET_SIGEVENTX32_DATA);
static_assert(offsetof(struct __sigeventx32, sigev_notify) == __OFFSET_SIGEVENTX32_NOTIFY);
static_assert(offsetof(struct __sigeventx32, sigev_notify_attributes) == __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES);
static_assert(offsetof(struct __sigeventx32, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES);
static_assert(offsetof(struct __sigeventx32, sigev_notify_function) == __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION);
static_assert(offsetof(struct __sigeventx32, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION);
static_assert(offsetof(struct __sigeventx32, sigev_signo) == __OFFSET_SIGEVENTX32_SIGNO);
static_assert(offsetof(struct __sigeventx32, _sigev_tid) == __OFFSET_SIGEVENTX32_TID);
static_assert(offsetof(struct __sigeventx32, _sigev_un._tid) == __OFFSET_SIGEVENTX32_TID);
static_assert(offsetof(struct __sigeventx32, sigev_value) == __OFFSET_SIGEVENTX32_VALUE);
static_assert(sizeof(struct __sigeventx32) == __SIZEOF_SIGEVENTX32);





#include <bits/os/kos/sigevent64.h>

/* struct __sigeventx64 */
static_assert(offsetof(struct __sigeventx64, _sigev_data) == __OFFSET_SIGEVENTX64_DATA);
static_assert(offsetof(struct __sigeventx64, _sigev_un._data) == __OFFSET_SIGEVENTX64_DATA);
static_assert(offsetof(struct __sigeventx64, sigev_notify) == __OFFSET_SIGEVENTX64_NOTIFY);
static_assert(offsetof(struct __sigeventx64, sigev_notify_attributes) == __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES);
static_assert(offsetof(struct __sigeventx64, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES);
static_assert(offsetof(struct __sigeventx64, sigev_notify_function) == __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION);
static_assert(offsetof(struct __sigeventx64, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION);
static_assert(offsetof(struct __sigeventx64, sigev_signo) == __OFFSET_SIGEVENTX64_SIGNO);
static_assert(offsetof(struct __sigeventx64, _sigev_tid) == __OFFSET_SIGEVENTX64_TID);
static_assert(offsetof(struct __sigeventx64, _sigev_un._tid) == __OFFSET_SIGEVENTX64_TID);
static_assert(offsetof(struct __sigeventx64, sigev_value) == __OFFSET_SIGEVENTX64_VALUE);
static_assert(sizeof(struct __sigeventx64) == __SIZEOF_SIGEVENTX64);





#include <bits/os/kos/siginfo32.h>

/* struct __siginfox32_struct */
static_assert(offsetof(struct __siginfox32_struct, si_addr) == __OFFSET_SIGINFOX32_ADDR);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFOX32_ADDR);
static_assert(offsetof(struct __siginfox32_struct, si_addr_lsb) == __OFFSET_SIGINFOX32_ADDR_LSB);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFOX32_ADDR_LSB);
static_assert(offsetof(struct __siginfox32_struct, si_arch) == __OFFSET_SIGINFOX32_ARCH);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFOX32_ARCH);
static_assert(offsetof(struct __siginfox32_struct, si_band) == __OFFSET_SIGINFOX32_BAND);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFOX32_BAND);
static_assert(offsetof(struct __siginfox32_struct, si_call_addr) == __OFFSET_SIGINFOX32_CALL_ADDR);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFOX32_CALL_ADDR);
static_assert(offsetof(struct __siginfox32_struct, si_code) == __OFFSET_SIGINFOX32_CODE);
static_assert(offsetof(struct __siginfox32_struct, _si_data) == __OFFSET_SIGINFOX32_DATA);
static_assert(offsetof(struct __siginfox32_struct, _sifields._data) == __OFFSET_SIGINFOX32_DATA);
static_assert(offsetof(struct __siginfox32_struct, si_errno) == __OFFSET_SIGINFOX32_ERRNO);
static_assert(offsetof(struct __siginfox32_struct, si_fd) == __OFFSET_SIGINFOX32_FD);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFOX32_FD);
static_assert(offsetof(struct __siginfox32_struct, si_int) == __OFFSET_SIGINFOX32_INT);
static_assert(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFOX32_INT);
static_assert(offsetof(struct __siginfox32_struct, si_lower) == __OFFSET_SIGINFOX32_LOWER);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFOX32_LOWER);
static_assert(offsetof(struct __siginfox32_struct, si_overrun) == __OFFSET_SIGINFOX32_OVERRUN);
static_assert(offsetof(struct __siginfox32_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFOX32_OVERRUN);
static_assert(offsetof(struct __siginfox32_struct, si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, __sig_si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, __cld_si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFOX32_PID);
static_assert(offsetof(struct __siginfox32_struct, si_ptr) == __OFFSET_SIGINFOX32_PTR);
static_assert(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFOX32_PTR);
static_assert(offsetof(struct __siginfox32_struct, si_signo) == __OFFSET_SIGINFOX32_SIGNO);
static_assert(offsetof(struct __siginfox32_struct, si_status) == __OFFSET_SIGINFOX32_STATUS);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFOX32_STATUS);
static_assert(offsetof(struct __siginfox32_struct, si_stime) == __OFFSET_SIGINFOX32_STIME);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFOX32_STIME);
static_assert(offsetof(struct __siginfox32_struct, si_syscall) == __OFFSET_SIGINFOX32_SYSCALL);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFOX32_SYSCALL);
static_assert(offsetof(struct __siginfox32_struct, si_timerid) == __OFFSET_SIGINFOX32_TIMERID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFOX32_TIMERID);
static_assert(offsetof(struct __siginfox32_struct, si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, __sig_si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, __cld_si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFOX32_UID);
static_assert(offsetof(struct __siginfox32_struct, si_upper) == __OFFSET_SIGINFOX32_UPPER);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFOX32_UPPER);
static_assert(offsetof(struct __siginfox32_struct, si_utime) == __OFFSET_SIGINFOX32_UTIME);
static_assert(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFOX32_UTIME);
static_assert(offsetof(struct __siginfox32_struct, si_value) == __OFFSET_SIGINFOX32_VALUE);
static_assert(offsetof(struct __siginfox32_struct, __sig_si_sigval) == __OFFSET_SIGINFOX32_VALUE);
static_assert(offsetof(struct __siginfox32_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFOX32_VALUE);
static_assert(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFOX32_VALUE);
static_assert(sizeof(struct __siginfox32_struct) == __SIZEOF_SIGINFOX32);
static_assert(alignof(struct __siginfox32_struct) == __ALIGNOF_SIGINFOX32);





#include <bits/os/kos/siginfo64.h>

/* struct __siginfox64_struct */
static_assert(offsetof(struct __siginfox64_struct, si_addr) == __OFFSET_SIGINFOX64_ADDR);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFOX64_ADDR);
static_assert(offsetof(struct __siginfox64_struct, si_addr_lsb) == __OFFSET_SIGINFOX64_ADDR_LSB);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFOX64_ADDR_LSB);
static_assert(offsetof(struct __siginfox64_struct, si_arch) == __OFFSET_SIGINFOX64_ARCH);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFOX64_ARCH);
static_assert(offsetof(struct __siginfox64_struct, si_band) == __OFFSET_SIGINFOX64_BAND);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFOX64_BAND);
static_assert(offsetof(struct __siginfox64_struct, si_call_addr) == __OFFSET_SIGINFOX64_CALL_ADDR);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFOX64_CALL_ADDR);
static_assert(offsetof(struct __siginfox64_struct, si_code) == __OFFSET_SIGINFOX64_CODE);
static_assert(offsetof(struct __siginfox64_struct, _si_data) == __OFFSET_SIGINFOX64_DATA);
static_assert(offsetof(struct __siginfox64_struct, _sifields._data) == __OFFSET_SIGINFOX64_DATA);
static_assert(offsetof(struct __siginfox64_struct, si_errno) == __OFFSET_SIGINFOX64_ERRNO);
static_assert(offsetof(struct __siginfox64_struct, si_fd) == __OFFSET_SIGINFOX64_FD);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFOX64_FD);
static_assert(offsetof(struct __siginfox64_struct, si_int) == __OFFSET_SIGINFOX64_INT);
static_assert(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFOX64_INT);
static_assert(offsetof(struct __siginfox64_struct, si_lower) == __OFFSET_SIGINFOX64_LOWER);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFOX64_LOWER);
static_assert(offsetof(struct __siginfox64_struct, si_overrun) == __OFFSET_SIGINFOX64_OVERRUN);
static_assert(offsetof(struct __siginfox64_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFOX64_OVERRUN);
static_assert(offsetof(struct __siginfox64_struct, si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, __sig_si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, __cld_si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFOX64_PID);
static_assert(offsetof(struct __siginfox64_struct, si_ptr) == __OFFSET_SIGINFOX64_PTR);
static_assert(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFOX64_PTR);
static_assert(offsetof(struct __siginfox64_struct, si_signo) == __OFFSET_SIGINFOX64_SIGNO);
static_assert(offsetof(struct __siginfox64_struct, si_status) == __OFFSET_SIGINFOX64_STATUS);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFOX64_STATUS);
static_assert(offsetof(struct __siginfox64_struct, si_stime) == __OFFSET_SIGINFOX64_STIME);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFOX64_STIME);
static_assert(offsetof(struct __siginfox64_struct, si_syscall) == __OFFSET_SIGINFOX64_SYSCALL);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFOX64_SYSCALL);
static_assert(offsetof(struct __siginfox64_struct, si_timerid) == __OFFSET_SIGINFOX64_TIMERID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFOX64_TIMERID);
static_assert(offsetof(struct __siginfox64_struct, si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, __sig_si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, __cld_si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFOX64_UID);
static_assert(offsetof(struct __siginfox64_struct, si_upper) == __OFFSET_SIGINFOX64_UPPER);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFOX64_UPPER);
static_assert(offsetof(struct __siginfox64_struct, si_utime) == __OFFSET_SIGINFOX64_UTIME);
static_assert(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFOX64_UTIME);
static_assert(offsetof(struct __siginfox64_struct, si_value) == __OFFSET_SIGINFOX64_VALUE);
static_assert(offsetof(struct __siginfox64_struct, __sig_si_sigval) == __OFFSET_SIGINFOX64_VALUE);
static_assert(offsetof(struct __siginfox64_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFOX64_VALUE);
static_assert(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFOX64_VALUE);
static_assert(sizeof(struct __siginfox64_struct) == __SIZEOF_SIGINFOX64);
static_assert(alignof(struct __siginfox64_struct) == __ALIGNOF_SIGINFOX64);





#include <bits/os/kos/sigstack32.h>

/* struct __sigstackx32 */
static_assert(offsetof(struct __sigstackx32, ss_onstack) == __OFFSET_SIGSTACKX32_ONSTACK);
static_assert(offsetof(struct __sigstackx32, ss_sp) == __OFFSET_SIGSTACKX32_SP);
static_assert(sizeof(struct __sigstackx32) == __SIZEOF_SIGSTACKX32);

/* struct __sigaltstackx32 */
static_assert(offsetof(struct __sigaltstackx32, ss_flags) == __OFFSET_SIGALTSTACKX32_FLAGS);
static_assert(offsetof(struct __sigaltstackx32, ss_size) == __OFFSET_SIGALTSTACKX32_SIZE);
static_assert(offsetof(struct __sigaltstackx32, ss_sp) == __OFFSET_SIGALTSTACKX32_SP);
static_assert(sizeof(struct __sigaltstackx32) == __SIZEOF_SIGALTSTACKX32);





#include <bits/os/kos/sigstack64.h>

/* struct __sigstackx64 */
static_assert(offsetof(struct __sigstackx64, ss_onstack) == __OFFSET_SIGSTACKX64_ONSTACK);
static_assert(offsetof(struct __sigstackx64, ss_sp) == __OFFSET_SIGSTACKX64_SP);
static_assert(sizeof(struct __sigstackx64) == __SIZEOF_SIGSTACKX64);

/* struct __sigaltstackx64 */
static_assert(offsetof(struct __sigaltstackx64, ss_flags) == __OFFSET_SIGALTSTACKX64_FLAGS);
static_assert(offsetof(struct __sigaltstackx64, ss_size) == __OFFSET_SIGALTSTACKX64_SIZE);
static_assert(offsetof(struct __sigaltstackx64, ss_sp) == __OFFSET_SIGALTSTACKX64_SP);
static_assert(sizeof(struct __sigaltstackx64) == __SIZEOF_SIGALTSTACKX64);





#include <bits/os/kos/sigval32.h>

/* union __sigvalx32 */
static_assert(sizeof(union __sigvalx32) == __SIZEOF_SIGVALX32);
static_assert(alignof(union __sigvalx32) == __ALIGNOF_SIGVALX32);





#include <bits/os/kos/sigval64.h>

/* union __sigvalx64 */
static_assert(sizeof(union __sigvalx64) == __SIZEOF_SIGVALX64);
static_assert(alignof(union __sigvalx64) == __ALIGNOF_SIGVALX64);





#include <bits/os/kos/statfs32.h>

/* struct statfsx32 */
static_assert(offsetof(struct statfsx32, f_bavail) == __OFFSET_STATFSX32_BAVAIL);
static_assert(offsetof(struct statfsx32, f_bfree) == __OFFSET_STATFSX32_BFREE);
static_assert(offsetof(struct statfsx32, f_blocks) == __OFFSET_STATFSX32_BLOCKS);
static_assert(offsetof(struct statfsx32, f_bsize) == __OFFSET_STATFSX32_BSIZE);
static_assert(offsetof(struct statfsx32, f_ffree) == __OFFSET_STATFSX32_FFREE);
static_assert(offsetof(struct statfsx32, f_files) == __OFFSET_STATFSX32_FILES);
static_assert(offsetof(struct statfsx32, f_flags) == __OFFSET_STATFSX32_FLAGS);
static_assert(offsetof(struct statfsx32, f_frsize) == __OFFSET_STATFSX32_FRSIZE);
static_assert(offsetof(struct statfsx32, f_fsid) == __OFFSET_STATFSX32_FSID);
static_assert(offsetof(struct statfsx32, f_namelen) == __OFFSET_STATFSX32_NAMELEN);
static_assert(offsetof(struct statfsx32, f_spare) == __OFFSET_STATFSX32_SPARE);
static_assert(offsetof(struct statfsx32, f_type) == __OFFSET_STATFSX32_TYPE);
static_assert(sizeof(struct statfsx32) == __SIZEOF_STATFSX32);
static_assert(alignof(struct statfsx32) == __ALIGNOF_STATFSX32);

/* struct statfsx32_64 */
static_assert(offsetof(struct statfsx32_64, f_bavail) == __OFFSET_STATFSX32_64_BAVAIL);
static_assert(offsetof(struct statfsx32_64, f_bfree) == __OFFSET_STATFSX32_64_BFREE);
static_assert(offsetof(struct statfsx32_64, f_blocks) == __OFFSET_STATFSX32_64_BLOCKS);
static_assert(offsetof(struct statfsx32_64, f_bsize) == __OFFSET_STATFSX32_64_BSIZE);
static_assert(offsetof(struct statfsx32_64, f_ffree) == __OFFSET_STATFSX32_64_FFREE);
static_assert(offsetof(struct statfsx32_64, f_files) == __OFFSET_STATFSX32_64_FILES);
static_assert(offsetof(struct statfsx32_64, f_flags) == __OFFSET_STATFSX32_64_FLAGS);
static_assert(offsetof(struct statfsx32_64, f_frsize) == __OFFSET_STATFSX32_64_FRSIZE);
static_assert(offsetof(struct statfsx32_64, f_fsid) == __OFFSET_STATFSX32_64_FSID);
static_assert(offsetof(struct statfsx32_64, f_namelen) == __OFFSET_STATFSX32_64_NAMELEN);
static_assert(offsetof(struct statfsx32_64, f_spare) == __OFFSET_STATFSX32_64_SPARE);
static_assert(offsetof(struct statfsx32_64, f_type) == __OFFSET_STATFSX32_64_TYPE);
static_assert(sizeof(struct statfsx32_64) == __SIZEOF_STATFSX32_64);
static_assert(alignof(struct statfsx32_64) == __ALIGNOF_STATFSX32_64);

/* struct __statfsx32_64_alt */
/* ... */





#include <bits/os/kos/statfs64.h>

/* struct statfsx64 */
static_assert(offsetof(struct statfsx64, f_bavail) == __OFFSET_STATFSX64_BAVAIL);
static_assert(offsetof(struct statfsx64, f_bfree) == __OFFSET_STATFSX64_BFREE);
static_assert(offsetof(struct statfsx64, f_blocks) == __OFFSET_STATFSX64_BLOCKS);
static_assert(offsetof(struct statfsx64, f_bsize) == __OFFSET_STATFSX64_BSIZE);
static_assert(offsetof(struct statfsx64, f_ffree) == __OFFSET_STATFSX64_FFREE);
static_assert(offsetof(struct statfsx64, f_files) == __OFFSET_STATFSX64_FILES);
static_assert(offsetof(struct statfsx64, f_flags) == __OFFSET_STATFSX64_FLAGS);
static_assert(offsetof(struct statfsx64, f_frsize) == __OFFSET_STATFSX64_FRSIZE);
static_assert(offsetof(struct statfsx64, f_fsid) == __OFFSET_STATFSX64_FSID);
static_assert(offsetof(struct statfsx64, f_namelen) == __OFFSET_STATFSX64_NAMELEN);
static_assert(offsetof(struct statfsx64, f_spare) == __OFFSET_STATFSX64_SPARE);
static_assert(offsetof(struct statfsx64, f_type) == __OFFSET_STATFSX64_TYPE);
static_assert(sizeof(struct statfsx64) == __SIZEOF_STATFSX64);
static_assert(alignof(struct statfsx64) == __ALIGNOF_STATFSX64);

/* struct __statfsx64_alt */
/* ... */





#include <bits/os/kos/timeb32.h>

/* struct timebx32 */
static_assert(offsetof(struct timebx32, dstflag) == __OFFSET_TIMEBX32_DSTFLAG);
static_assert(offsetof(struct timebx32, millitm) == __OFFSET_TIMEBX32_MILLITM);
static_assert(offsetof(struct timebx32, time) == __OFFSET_TIMEBX32_TIME);
static_assert(offsetof(struct timebx32, timezone) == __OFFSET_TIMEBX32_TIMEZONE);
static_assert(sizeof(struct timebx32) == __SIZEOF_TIMEBX32);
static_assert(alignof(struct timebx32) == __ALIGNOF_TIMEBX32);

/* struct timebx32_64 */
static_assert(offsetof(struct timebx32_64, dstflag) == __OFFSET_TIMEBX32_64_DSTFLAG);
static_assert(offsetof(struct timebx32_64, millitm) == __OFFSET_TIMEBX32_64_MILLITM);
static_assert(offsetof(struct timebx32_64, time) == __OFFSET_TIMEBX32_64_TIME);
static_assert(offsetof(struct timebx32_64, timezone) == __OFFSET_TIMEBX32_64_TIMEZONE);
static_assert(sizeof(struct timebx32_64) == __SIZEOF_TIMEBX32_64);
static_assert(alignof(struct timebx32_64) == __ALIGNOF_TIMEBX32_64);

/* struct __timebx32_64_alt */
/* ... */





#include <bits/os/kos/timeb64.h>

/* struct timebx64 */
static_assert(offsetof(struct timebx64, dstflag) == __OFFSET_TIMEBX64_DSTFLAG);
static_assert(offsetof(struct timebx64, millitm) == __OFFSET_TIMEBX64_MILLITM);
static_assert(offsetof(struct timebx64, time) == __OFFSET_TIMEBX64_TIME);
static_assert(offsetof(struct timebx64, timezone) == __OFFSET_TIMEBX64_TIMEZONE);
static_assert(sizeof(struct timebx64) == __SIZEOF_TIMEBX64);
static_assert(alignof(struct timebx64) == __ALIGNOF_TIMEBX64);

/* struct __timebx64_alt */
/* ... */





#include <bits/os/kos/tms32.h>

/* struct __tmsx32 */
static_assert(offsetof(struct __tmsx32, tms_cstime) == __OFFSET_TMSX32_CSTIME);
static_assert(offsetof(struct __tmsx32, tms_cutime) == __OFFSET_TMSX32_CUTIME);
static_assert(offsetof(struct __tmsx32, tms_stime) == __OFFSET_TMSX32_STIME);
static_assert(offsetof(struct __tmsx32, tms_utime) == __OFFSET_TMSX32_UTIME);
static_assert(sizeof(struct __tmsx32) == __SIZEOF_TMSX32);
static_assert(alignof(struct __tmsx32) == __ALIGNOF_TMSX32);





#include <bits/os/kos/tms64.h>

/* struct __tmsx64 */
static_assert(offsetof(struct __tmsx64, tms_cstime) == __OFFSET_TMSX64_CSTIME);
static_assert(offsetof(struct __tmsx64, tms_cutime) == __OFFSET_TMSX64_CUTIME);
static_assert(offsetof(struct __tmsx64, tms_stime) == __OFFSET_TMSX64_STIME);
static_assert(offsetof(struct __tmsx64, tms_utime) == __OFFSET_TMSX64_UTIME);
static_assert(sizeof(struct __tmsx64) == __SIZEOF_TMSX64);
static_assert(alignof(struct __tmsx64) == __ALIGNOF_TMSX64);





#include <bits/os/kos/utimbuf32.h>

/* struct utimbufx32 */
static_assert(offsetof(struct utimbufx32, actime) == __OFFSET_UTIMBUFX32_ACTIME);
static_assert(offsetof(struct utimbufx32, modtime) == __OFFSET_UTIMBUFX32_MODTIME);
static_assert(sizeof(struct utimbufx32) == __SIZEOF_UTIMBUFX32);
static_assert(alignof(struct utimbufx32) == __ALIGNOF_UTIMBUFX32);

/* struct utimbufx32_64 */
static_assert(offsetof(struct utimbufx32_64, actime) == __OFFSET_UTIMBUFX32_64_ACTIME);
static_assert(offsetof(struct utimbufx32_64, modtime) == __OFFSET_UTIMBUFX32_64_MODTIME);
static_assert(sizeof(struct utimbufx32_64) == __SIZEOF_UTIMBUFX32_64);
static_assert(alignof(struct utimbufx32_64) == __ALIGNOF_UTIMBUFX32_64);

/* struct __utimbufx32_64_alt */
/* ... */





#include <bits/os/kos/utimbuf64.h>

/* struct utimbufx64 */
static_assert(offsetof(struct utimbufx64, actime) == __OFFSET_UTIMBUFX64_ACTIME);
static_assert(offsetof(struct utimbufx64, modtime) == __OFFSET_UTIMBUFX64_MODTIME);
static_assert(sizeof(struct utimbufx64) == __SIZEOF_UTIMBUFX64);
static_assert(alignof(struct utimbufx64) == __ALIGNOF_UTIMBUFX64);

/* struct __utimbufx64_alt */
/* ... */





#include <bits/va_list-struct32.h>

/* struct i386_va_list_struct */
/* ... */





#include <bits/va_list-struct64.h>

/* struct x86_64_va_list_reg_save_area */
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_r8) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R8);
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_r9) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9);
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_rcx) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RCX);
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_rdi) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDI);
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_rdx) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX);
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_rsi) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RSI);
static_assert(sizeof(struct x86_64_va_list_reg_save_area) == SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA);

/* struct x86_64_va_list_struct */
static_assert(offsetof(struct x86_64_va_list_struct, vl_fp_offset) == OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET);
static_assert(offsetof(struct x86_64_va_list_struct, vl_gp_offset) == OFFSET_X86_64_VA_LIST_STRUCT_GP_OFFSET);
static_assert(offsetof(struct x86_64_va_list_struct, vl_overflow_arg_area) == OFFSET_X86_64_VA_LIST_STRUCT_OVERFLOW_ARG_AREA);
static_assert(offsetof(struct x86_64_va_list_struct, vl_reg_save_area) == OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA);
static_assert(sizeof(struct x86_64_va_list_struct) == SIZEOF_X86_64_VA_LIST_STRUCT);





#include <bits/os/kos/mcontext32.h>

/* struct _libc_fpreg */
/* ... */

/* struct _libc_fpstate */
/* ... */

/* struct __mcontextx32 */
static_assert(offsetof(struct __mcontextx32, gregs) == __OFFSET_MCONTEXTX32_CPU);
static_assert(offsetof(struct __mcontextx32, mc_gregs) == __OFFSET_MCONTEXTX32_CPU);
static_assert(offsetof(struct __mcontextx32, mc_context) == __OFFSET_MCONTEXTX32_CPU);
static_assert(offsetof(struct __mcontextx32, cr2) == __OFFSET_MCONTEXTX32_CR2);
static_assert(offsetof(struct __mcontextx32, mc_cr2) == __OFFSET_MCONTEXTX32_CR2);
static_assert(offsetof(struct __mcontextx32, mc_flags) == __OFFSET_MCONTEXTX32_FLAGS);
static_assert(offsetof(struct __mcontextx32, fpregs) == __OFFSET_MCONTEXTX32_FPU);
static_assert(offsetof(struct __mcontextx32, mc_fpu) == __OFFSET_MCONTEXTX32_FPU);
static_assert(sizeof(struct __mcontextx32) == __SIZEOF_MCONTEXTX32);
static_assert(alignof(struct __mcontextx32) == __ALIGNOF_MCONTEXTX32);





#include <bits/os/kos/mcontext64.h>

/* struct __mcontextx64 */
static_assert(offsetof(struct __mcontextx64, gregs) == __OFFSET_MCONTEXTX64_CPU);
static_assert(offsetof(struct __mcontextx64, mc_gregs) == __OFFSET_MCONTEXTX64_CPU);
static_assert(offsetof(struct __mcontextx64, mc_context) == __OFFSET_MCONTEXTX64_CPU);
static_assert(offsetof(struct __mcontextx64, cr2) == __OFFSET_MCONTEXTX64_CR2);
static_assert(offsetof(struct __mcontextx64, mc_cr2) == __OFFSET_MCONTEXTX64_CR2);
static_assert(offsetof(struct __mcontextx64, mc_flags) == __OFFSET_MCONTEXTX64_FLAGS);
static_assert(offsetof(struct __mcontextx64, fpregs) == __OFFSET_MCONTEXTX64_FPU);
static_assert(offsetof(struct __mcontextx64, mc_fpu) == __OFFSET_MCONTEXTX64_FPU);
static_assert(sizeof(struct __mcontextx64) == __SIZEOF_MCONTEXTX64);
static_assert(alignof(struct __mcontextx64) == __ALIGNOF_MCONTEXTX64);





#include <bits/os/linux/mcontext32.h>

/* struct __libc_linux32_fpreg */
static_assert(offsetof(struct __libc_linux32_fpreg, exponent) == __OFFSET_LIBC_LINUX32_FPREG_EXPONENT);
static_assert(offsetof(struct __libc_linux32_fpreg, significand) == __OFFSET_LIBC_LINUX32_FPREG_SIGNIFICAND);
static_assert(sizeof(struct __libc_linux32_fpreg) == __SIZEOF_LIBC_LINUX32_FPREG);

/* struct __libc_linux32_fpstate */
static_assert(offsetof(struct __libc_linux32_fpstate, cssel) == __OFFSET_LIBC_LINUX32_FPSTATE_CSSEL);
static_assert(offsetof(struct __libc_linux32_fpstate, cw) == __OFFSET_LIBC_LINUX32_FPSTATE_CW);
static_assert(offsetof(struct __libc_linux32_fpstate, dataoff) == __OFFSET_LIBC_LINUX32_FPSTATE_DATAOFF);
static_assert(offsetof(struct __libc_linux32_fpstate, datasel) == __OFFSET_LIBC_LINUX32_FPSTATE_DATASEL);
static_assert(offsetof(struct __libc_linux32_fpstate, ipoff) == __OFFSET_LIBC_LINUX32_FPSTATE_IPOFF);
static_assert(offsetof(struct __libc_linux32_fpstate, _st) == __OFFSET_LIBC_LINUX32_FPSTATE_ST);
static_assert(offsetof(struct __libc_linux32_fpstate, status) == __OFFSET_LIBC_LINUX32_FPSTATE_STATUS);
static_assert(offsetof(struct __libc_linux32_fpstate, sw) == __OFFSET_LIBC_LINUX32_FPSTATE_SW);
static_assert(offsetof(struct __libc_linux32_fpstate, tag) == __OFFSET_LIBC_LINUX32_FPSTATE_TAG);
static_assert(sizeof(struct __libc_linux32_fpstate) == __SIZEOF_LIBC_LINUX32_FPSTATE);

/* struct __mcontext_linux32 */
static_assert(offsetof(struct __mcontext_linux32, cr2) == __OFFSET_MCONTEXT_LINUX32_CR2);
static_assert(offsetof(struct __mcontext_linux32, fpregs) == __OFFSET_MCONTEXT_LINUX32_FPREGS);
static_assert(offsetof(struct __mcontext_linux32, gregs) == __OFFSET_MCONTEXT_LINUX32_GREGS);
static_assert(offsetof(struct __mcontext_linux32, oldmask) == __OFFSET_MCONTEXT_LINUX32_OLDMASK);
static_assert(sizeof(struct __mcontext_linux32) == __SIZEOF_MCONTEXT_LINUX32);
static_assert(alignof(struct __mcontext_linux32) == __ALIGNOF_MCONTEXT_LINUX32);





#include <bits/os/linux/mcontext64.h>

/* struct __libc_linux64_fpxreg */
static_assert(offsetof(struct __libc_linux64_fpxreg, exponent) == __OFFSET_LIBC_LINUX64_FPXREG_EXPONENT);
static_assert(offsetof(struct __libc_linux64_fpxreg, padding) == __OFFSET_LIBC_LINUX64_FPXREG_PADDING);
static_assert(offsetof(struct __libc_linux64_fpxreg, significand) == __OFFSET_LIBC_LINUX64_FPXREG_SIGNIFICAND);
static_assert(sizeof(struct __libc_linux64_fpxreg) == __SIZEOF_LIBC_LINUX64_FPXREG);

/* struct __libc_linux64_xmmreg */
static_assert(offsetof(struct __libc_linux64_xmmreg, element) == __OFFSET_LIBC_LINUX64_XMMREG_ELEMENT);
static_assert(sizeof(struct __libc_linux64_xmmreg) == __SIZEOF_LIBC_LINUX64_XMMREG);

/* struct __libc_linux64_fpstate */
static_assert(offsetof(struct __libc_linux64_fpstate, cwd) == __OFFSET_LIBC_LINUX64_FPSTATE_CWD);
static_assert(offsetof(struct __libc_linux64_fpstate, fop) == __OFFSET_LIBC_LINUX64_FPSTATE_FOP);
static_assert(offsetof(struct __libc_linux64_fpstate, ftw) == __OFFSET_LIBC_LINUX64_FPSTATE_FTW);
static_assert(offsetof(struct __libc_linux64_fpstate, mxcr_mask) == __OFFSET_LIBC_LINUX64_FPSTATE_MXCR_MASK);
static_assert(offsetof(struct __libc_linux64_fpstate, mxcsr) == __OFFSET_LIBC_LINUX64_FPSTATE_MXCSR);
static_assert(offsetof(struct __libc_linux64_fpstate, padding) == __OFFSET_LIBC_LINUX64_FPSTATE_PADDING);
static_assert(offsetof(struct __libc_linux64_fpstate, rdp) == __OFFSET_LIBC_LINUX64_FPSTATE_RDP);
static_assert(offsetof(struct __libc_linux64_fpstate, rip) == __OFFSET_LIBC_LINUX64_FPSTATE_RIP);
static_assert(offsetof(struct __libc_linux64_fpstate, _st) == __OFFSET_LIBC_LINUX64_FPSTATE_ST);
static_assert(offsetof(struct __libc_linux64_fpstate, swd) == __OFFSET_LIBC_LINUX64_FPSTATE_SWD);
static_assert(offsetof(struct __libc_linux64_fpstate, _xmm) == __OFFSET_LIBC_LINUX64_FPSTATE_XMM);
static_assert(sizeof(struct __libc_linux64_fpstate) == __SIZEOF_LIBC_LINUX64_FPSTATE);

/* struct __mcontext_linux64 */
static_assert(offsetof(struct __mcontext_linux64, fpregs) == __OFFSET_MCONTEXT_LINUX64_FPREGS);
static_assert(offsetof(struct __mcontext_linux64, fs_base) == __OFFSET_MCONTEXT_LINUX64_FS_BASE);
static_assert(offsetof(struct __mcontext_linux64, gregs) == __OFFSET_MCONTEXT_LINUX64_GREGS);
static_assert(offsetof(struct __mcontext_linux64, gs_base) == __OFFSET_MCONTEXT_LINUX64_GS_BASE);
static_assert(sizeof(struct __mcontext_linux64) == __SIZEOF_MCONTEXT_LINUX64);
static_assert(alignof(struct __mcontext_linux64) == __ALIGNOF_MCONTEXT_LINUX64);





#include <bits/os/cygwin/mcontext32.h>

/* struct __cygwin32_uc_fpreg */
static_assert(offsetof(struct __cygwin32_uc_fpreg, exponent) == __OFFSET_CYGWIN32_UC_FPREG_EXPONENT);
static_assert(offsetof(struct __cygwin32_uc_fpreg, significand) == __OFFSET_CYGWIN32_UC_FPREG_SIGNIFICAND);
static_assert(sizeof(struct __cygwin32_uc_fpreg) == __SIZEOF_CYGWIN32_UC_FPREG);
static_assert(alignof(struct __cygwin32_uc_fpreg) == __ALIGNOF_CYGWIN32_UC_FPREG);

/* struct __cygwin32_fpstate */
static_assert(offsetof(struct __cygwin32_fpstate, cssel) == __OFFSET_CYGWIN32_FPSTATE_CSSEL);
static_assert(offsetof(struct __cygwin32_fpstate, cw) == __OFFSET_CYGWIN32_FPSTATE_CW);
static_assert(offsetof(struct __cygwin32_fpstate, dataoff) == __OFFSET_CYGWIN32_FPSTATE_DATAOFF);
static_assert(offsetof(struct __cygwin32_fpstate, datasel) == __OFFSET_CYGWIN32_FPSTATE_DATASEL);
static_assert(offsetof(struct __cygwin32_fpstate, ipoff) == __OFFSET_CYGWIN32_FPSTATE_IPOFF);
static_assert(offsetof(struct __cygwin32_fpstate, nxst) == __OFFSET_CYGWIN32_FPSTATE_NXST);
static_assert(offsetof(struct __cygwin32_fpstate, _st) == __OFFSET_CYGWIN32_FPSTATE_ST);
static_assert(offsetof(struct __cygwin32_fpstate, sw) == __OFFSET_CYGWIN32_FPSTATE_SW);
static_assert(offsetof(struct __cygwin32_fpstate, tag) == __OFFSET_CYGWIN32_FPSTATE_TAG);
static_assert(sizeof(struct __cygwin32_fpstate) == __SIZEOF_CYGWIN32_FPSTATE);
static_assert(alignof(struct __cygwin32_fpstate) == __ALIGNOF_CYGWIN32_FPSTATE);

/* struct __cygwin32_mcontext */
static_assert(offsetof(struct __cygwin32_mcontext, cr2) == __OFFSET_CYGWIN32_MCONTEXT_CR2);
static_assert(offsetof(struct __cygwin32_mcontext, cs) == __OFFSET_CYGWIN32_MCONTEXT_CS);
static_assert(offsetof(struct __cygwin32_mcontext, ctxflags) == __OFFSET_CYGWIN32_MCONTEXT_CTXFLAGS);
static_assert(offsetof(struct __cygwin32_mcontext, dr0) == __OFFSET_CYGWIN32_MCONTEXT_DR0);
static_assert(offsetof(struct __cygwin32_mcontext, dr1) == __OFFSET_CYGWIN32_MCONTEXT_DR1);
static_assert(offsetof(struct __cygwin32_mcontext, dr2) == __OFFSET_CYGWIN32_MCONTEXT_DR2);
static_assert(offsetof(struct __cygwin32_mcontext, dr3) == __OFFSET_CYGWIN32_MCONTEXT_DR3);
static_assert(offsetof(struct __cygwin32_mcontext, dr6) == __OFFSET_CYGWIN32_MCONTEXT_DR6);
static_assert(offsetof(struct __cygwin32_mcontext, dr7) == __OFFSET_CYGWIN32_MCONTEXT_DR7);
static_assert(offsetof(struct __cygwin32_mcontext, ds) == __OFFSET_CYGWIN32_MCONTEXT_DS);
static_assert(offsetof(struct __cygwin32_mcontext, eax) == __OFFSET_CYGWIN32_MCONTEXT_EAX);
static_assert(offsetof(struct __cygwin32_mcontext, ebp) == __OFFSET_CYGWIN32_MCONTEXT_EBP);
static_assert(offsetof(struct __cygwin32_mcontext, ebx) == __OFFSET_CYGWIN32_MCONTEXT_EBX);
static_assert(offsetof(struct __cygwin32_mcontext, ecx) == __OFFSET_CYGWIN32_MCONTEXT_ECX);
static_assert(offsetof(struct __cygwin32_mcontext, edi) == __OFFSET_CYGWIN32_MCONTEXT_EDI);
static_assert(offsetof(struct __cygwin32_mcontext, edx) == __OFFSET_CYGWIN32_MCONTEXT_EDX);
static_assert(offsetof(struct __cygwin32_mcontext, eflags) == __OFFSET_CYGWIN32_MCONTEXT_EFLAGS);
static_assert(offsetof(struct __cygwin32_mcontext, eip) == __OFFSET_CYGWIN32_MCONTEXT_EIP);
static_assert(offsetof(struct __cygwin32_mcontext, es) == __OFFSET_CYGWIN32_MCONTEXT_ES);
static_assert(offsetof(struct __cygwin32_mcontext, esi) == __OFFSET_CYGWIN32_MCONTEXT_ESI);
static_assert(offsetof(struct __cygwin32_mcontext, esp) == __OFFSET_CYGWIN32_MCONTEXT_ESP);
static_assert(offsetof(struct __cygwin32_mcontext, fpstate) == __OFFSET_CYGWIN32_MCONTEXT_FPSTATE);
static_assert(offsetof(struct __cygwin32_mcontext, fs) == __OFFSET_CYGWIN32_MCONTEXT_FS);
static_assert(offsetof(struct __cygwin32_mcontext, gs) == __OFFSET_CYGWIN32_MCONTEXT_GS);
static_assert(offsetof(struct __cygwin32_mcontext, oldmask) == __OFFSET_CYGWIN32_MCONTEXT_OLDMASK);
static_assert(offsetof(struct __cygwin32_mcontext, reserved) == __OFFSET_CYGWIN32_MCONTEXT_RESERVED);
static_assert(offsetof(struct __cygwin32_mcontext, ss) == __OFFSET_CYGWIN32_MCONTEXT_SS);
static_assert(sizeof(struct __cygwin32_mcontext) == __SIZEOF_CYGWIN32_MCONTEXT);
static_assert(alignof(struct __cygwin32_mcontext) == __ALIGNOF_CYGWIN32_MCONTEXT);





#include <bits/os/cygwin/mcontext64.h>

/* struct __cygwin64_uc_fpxreg */
static_assert(offsetof(struct __cygwin64_uc_fpxreg, exponent) == __OFFSET_CYGWIN64_UC_FPXREG_EXPONENT);
static_assert(offsetof(struct __cygwin64_uc_fpxreg, padding) == __OFFSET_CYGWIN64_UC_FPXREG_PADDING);
static_assert(offsetof(struct __cygwin64_uc_fpxreg, significand) == __OFFSET_CYGWIN64_UC_FPXREG_SIGNIFICAND);
static_assert(sizeof(struct __cygwin64_uc_fpxreg) == __SIZEOF_CYGWIN64_UC_FPXREG);
static_assert(alignof(struct __cygwin64_uc_fpxreg) == __ALIGNOF_CYGWIN64_UC_FPXREG);

/* struct __cygwin64_uc_xmmreg */
static_assert(offsetof(struct __cygwin64_uc_xmmreg, element) == __OFFSET_CYGWIN64_UC_XMMREG_ELEMENT);
static_assert(sizeof(struct __cygwin64_uc_xmmreg) == __SIZEOF_CYGWIN64_UC_XMMREG);
static_assert(alignof(struct __cygwin64_uc_xmmreg) == __ALIGNOF_CYGWIN64_UC_XMMREG);

/* struct __cygwin64_fpstate */
static_assert(offsetof(struct __cygwin64_fpstate, cwd) == __OFFSET_CYGWIN64_FPSTATE_CWD);
static_assert(offsetof(struct __cygwin64_fpstate, fop) == __OFFSET_CYGWIN64_FPSTATE_FOP);
static_assert(offsetof(struct __cygwin64_fpstate, ftw) == __OFFSET_CYGWIN64_FPSTATE_FTW);
static_assert(offsetof(struct __cygwin64_fpstate, mxcr_mask) == __OFFSET_CYGWIN64_FPSTATE_MXCR_MASK);
static_assert(offsetof(struct __cygwin64_fpstate, mxcsr) == __OFFSET_CYGWIN64_FPSTATE_MXCSR);
static_assert(offsetof(struct __cygwin64_fpstate, padding) == __OFFSET_CYGWIN64_FPSTATE_PADDING);
static_assert(offsetof(struct __cygwin64_fpstate, rdp) == __OFFSET_CYGWIN64_FPSTATE_RDP);
static_assert(offsetof(struct __cygwin64_fpstate, rip) == __OFFSET_CYGWIN64_FPSTATE_RIP);
static_assert(offsetof(struct __cygwin64_fpstate, st) == __OFFSET_CYGWIN64_FPSTATE_ST);
static_assert(offsetof(struct __cygwin64_fpstate, swd) == __OFFSET_CYGWIN64_FPSTATE_SWD);
static_assert(offsetof(struct __cygwin64_fpstate, xmm) == __OFFSET_CYGWIN64_FPSTATE_XMM);
static_assert(sizeof(struct __cygwin64_fpstate) == __SIZEOF_CYGWIN64_FPSTATE);
static_assert(alignof(struct __cygwin64_fpstate) == __ALIGNOF_CYGWIN64_FPSTATE);

/* struct __cygwin64_mcontext */
static_assert(offsetof(struct __cygwin64_mcontext, bfr) == __OFFSET_CYGWIN64_MCONTEXT_BFR);
static_assert(offsetof(struct __cygwin64_mcontext, btr) == __OFFSET_CYGWIN64_MCONTEXT_BTR);
static_assert(offsetof(struct __cygwin64_mcontext, cr2) == __OFFSET_CYGWIN64_MCONTEXT_CR2);
static_assert(offsetof(struct __cygwin64_mcontext, cs) == __OFFSET_CYGWIN64_MCONTEXT_CS);
static_assert(offsetof(struct __cygwin64_mcontext, ctxflags) == __OFFSET_CYGWIN64_MCONTEXT_CTXFLAGS);
static_assert(offsetof(struct __cygwin64_mcontext, dbc) == __OFFSET_CYGWIN64_MCONTEXT_DBC);
static_assert(offsetof(struct __cygwin64_mcontext, dr0) == __OFFSET_CYGWIN64_MCONTEXT_DR0);
static_assert(offsetof(struct __cygwin64_mcontext, dr1) == __OFFSET_CYGWIN64_MCONTEXT_DR1);
static_assert(offsetof(struct __cygwin64_mcontext, dr2) == __OFFSET_CYGWIN64_MCONTEXT_DR2);
static_assert(offsetof(struct __cygwin64_mcontext, dr3) == __OFFSET_CYGWIN64_MCONTEXT_DR3);
static_assert(offsetof(struct __cygwin64_mcontext, dr6) == __OFFSET_CYGWIN64_MCONTEXT_DR6);
static_assert(offsetof(struct __cygwin64_mcontext, dr7) == __OFFSET_CYGWIN64_MCONTEXT_DR7);
static_assert(offsetof(struct __cygwin64_mcontext, ds) == __OFFSET_CYGWIN64_MCONTEXT_DS);
static_assert(offsetof(struct __cygwin64_mcontext, eflags) == __OFFSET_CYGWIN64_MCONTEXT_EFLAGS);
static_assert(offsetof(struct __cygwin64_mcontext, efr) == __OFFSET_CYGWIN64_MCONTEXT_EFR);
static_assert(offsetof(struct __cygwin64_mcontext, es) == __OFFSET_CYGWIN64_MCONTEXT_ES);
static_assert(offsetof(struct __cygwin64_mcontext, etr) == __OFFSET_CYGWIN64_MCONTEXT_ETR);
static_assert(offsetof(struct __cygwin64_mcontext, fpregs) == __OFFSET_CYGWIN64_MCONTEXT_FPREGS);
static_assert(offsetof(struct __cygwin64_mcontext, fs) == __OFFSET_CYGWIN64_MCONTEXT_FS);
static_assert(offsetof(struct __cygwin64_mcontext, gs) == __OFFSET_CYGWIN64_MCONTEXT_GS);
static_assert(offsetof(struct __cygwin64_mcontext, mxcsr) == __OFFSET_CYGWIN64_MCONTEXT_MXCSR);
static_assert(offsetof(struct __cygwin64_mcontext, oldmask) == __OFFSET_CYGWIN64_MCONTEXT_OLDMASK);
static_assert(offsetof(struct __cygwin64_mcontext, p1home) == __OFFSET_CYGWIN64_MCONTEXT_P1HOME);
static_assert(offsetof(struct __cygwin64_mcontext, p2home) == __OFFSET_CYGWIN64_MCONTEXT_P2HOME);
static_assert(offsetof(struct __cygwin64_mcontext, p3home) == __OFFSET_CYGWIN64_MCONTEXT_P3HOME);
static_assert(offsetof(struct __cygwin64_mcontext, p4home) == __OFFSET_CYGWIN64_MCONTEXT_P4HOME);
static_assert(offsetof(struct __cygwin64_mcontext, p5home) == __OFFSET_CYGWIN64_MCONTEXT_P5HOME);
static_assert(offsetof(struct __cygwin64_mcontext, p6home) == __OFFSET_CYGWIN64_MCONTEXT_P6HOME);
static_assert(offsetof(struct __cygwin64_mcontext, r10) == __OFFSET_CYGWIN64_MCONTEXT_R10);
static_assert(offsetof(struct __cygwin64_mcontext, r11) == __OFFSET_CYGWIN64_MCONTEXT_R11);
static_assert(offsetof(struct __cygwin64_mcontext, r12) == __OFFSET_CYGWIN64_MCONTEXT_R12);
static_assert(offsetof(struct __cygwin64_mcontext, r13) == __OFFSET_CYGWIN64_MCONTEXT_R13);
static_assert(offsetof(struct __cygwin64_mcontext, r14) == __OFFSET_CYGWIN64_MCONTEXT_R14);
static_assert(offsetof(struct __cygwin64_mcontext, r15) == __OFFSET_CYGWIN64_MCONTEXT_R15);
static_assert(offsetof(struct __cygwin64_mcontext, r8) == __OFFSET_CYGWIN64_MCONTEXT_R8);
static_assert(offsetof(struct __cygwin64_mcontext, r9) == __OFFSET_CYGWIN64_MCONTEXT_R9);
static_assert(offsetof(struct __cygwin64_mcontext, rax) == __OFFSET_CYGWIN64_MCONTEXT_RAX);
static_assert(offsetof(struct __cygwin64_mcontext, rbp) == __OFFSET_CYGWIN64_MCONTEXT_RBP);
static_assert(offsetof(struct __cygwin64_mcontext, rbx) == __OFFSET_CYGWIN64_MCONTEXT_RBX);
static_assert(offsetof(struct __cygwin64_mcontext, rcx) == __OFFSET_CYGWIN64_MCONTEXT_RCX);
static_assert(offsetof(struct __cygwin64_mcontext, rdi) == __OFFSET_CYGWIN64_MCONTEXT_RDI);
static_assert(offsetof(struct __cygwin64_mcontext, rdx) == __OFFSET_CYGWIN64_MCONTEXT_RDX);
static_assert(offsetof(struct __cygwin64_mcontext, rip) == __OFFSET_CYGWIN64_MCONTEXT_RIP);
static_assert(offsetof(struct __cygwin64_mcontext, rsi) == __OFFSET_CYGWIN64_MCONTEXT_RSI);
static_assert(offsetof(struct __cygwin64_mcontext, rsp) == __OFFSET_CYGWIN64_MCONTEXT_RSP);
static_assert(offsetof(struct __cygwin64_mcontext, ss) == __OFFSET_CYGWIN64_MCONTEXT_SS);
static_assert(offsetof(struct __cygwin64_mcontext, vcx) == __OFFSET_CYGWIN64_MCONTEXT_VCX);
static_assert(offsetof(struct __cygwin64_mcontext, vregs) == __OFFSET_CYGWIN64_MCONTEXT_VREGS);
static_assert(sizeof(struct __cygwin64_mcontext) == __SIZEOF_CYGWIN64_MCONTEXT);
static_assert(alignof(struct __cygwin64_mcontext) == __ALIGNOF_CYGWIN64_MCONTEXT);





#include <bits/os/kos/ucontext32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __ucontextx32 */
static_assert(offsetof(struct __ucontextx32, uc_link) == __OFFSET_UCONTEXTX32_LINK);
static_assert(offsetof(struct __ucontextx32, uc_mcontext) == __OFFSET_UCONTEXTX32_MCONTEXT);
static_assert(offsetof(struct __ucontextx32, uc_sigmask) == __OFFSET_UCONTEXTX32_SIGMASK);
static_assert(offsetof(struct __ucontextx32, uc_stack) == __OFFSET_UCONTEXTX32_STACK);
static_assert(alignof(struct __ucontextx32) == __ALIGNOF_UCONTEXTX32);





#include <bits/os/kos/ucontext64.h>

/* struct __ucontextx64 */
static_assert(offsetof(struct __ucontextx64, uc_link) == __OFFSET_UCONTEXTX64_LINK);
static_assert(offsetof(struct __ucontextx64, uc_mcontext) == __OFFSET_UCONTEXTX64_MCONTEXT);
static_assert(offsetof(struct __ucontextx64, uc_sigmask) == __OFFSET_UCONTEXTX64_SIGMASK);
static_assert(offsetof(struct __ucontextx64, uc_stack) == __OFFSET_UCONTEXTX64_STACK);
static_assert(alignof(struct __ucontextx64) == __ALIGNOF_UCONTEXTX64);





#include <bits/os/linux/ucontext32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __ucontext_linux32 */
static_assert(offsetof(struct __ucontext_linux32, uc_flags) == __OFFSET_UCONTEXT_LINUX32_FLAGS);
static_assert(offsetof(struct __ucontext_linux32, __fpregs_mem) == __OFFSET_UCONTEXT_LINUX32_FPREGS);
static_assert(offsetof(struct __ucontext_linux32, uc_link) == __OFFSET_UCONTEXT_LINUX32_LINK);
static_assert(offsetof(struct __ucontext_linux32, uc_mcontext) == __OFFSET_UCONTEXT_LINUX32_MCONTEXT);
static_assert(offsetof(struct __ucontext_linux32, uc_sigmask) == __OFFSET_UCONTEXT_LINUX32_SIGMASK);
static_assert(offsetof(struct __ucontext_linux32, uc_stack) == __OFFSET_UCONTEXT_LINUX32_STACK);
static_assert(sizeof(struct __ucontext_linux32) == __SIZEOF_UCONTEXT_LINUX32);
static_assert(alignof(struct __ucontext_linux32) == __ALIGNOF_UCONTEXT_LINUX32);





#include <bits/os/linux/ucontext64.h>

/* struct __ucontext_linux64 */
/* ... */





#include <bits/os/cygwin/ucontext32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __cygwin32_ucontext */
static_assert(offsetof(struct __cygwin32_ucontext, uc_flags) == __OFFSET_CYGWIN32_UCONTEXT_FLAGS);
static_assert(offsetof(struct __cygwin32_ucontext, uc_link) == __OFFSET_CYGWIN32_UCONTEXT_LINK);
static_assert(offsetof(struct __cygwin32_ucontext, uc_mcontext) == __OFFSET_CYGWIN32_UCONTEXT_MCONTEXT);
static_assert(offsetof(struct __cygwin32_ucontext, uc_sigmask) == __OFFSET_CYGWIN32_UCONTEXT_SIGMASK);
static_assert(offsetof(struct __cygwin32_ucontext, uc_stack) == __OFFSET_CYGWIN32_UCONTEXT_STACK);
static_assert(sizeof(struct __cygwin32_ucontext) == __SIZEOF_CYGWIN32_UCONTEXT);
static_assert(alignof(struct __cygwin32_ucontext) == __ALIGNOF_CYGWIN32_UCONTEXT);





#include <bits/os/cygwin/ucontext64.h>

/* struct __cygwin64_ucontext */
static_assert(offsetof(struct __cygwin64_ucontext, uc_flags) == __OFFSET_CYGWIN64_UCONTEXT_FLAGS);
static_assert(offsetof(struct __cygwin64_ucontext, uc_link) == __OFFSET_CYGWIN64_UCONTEXT_LINK);
static_assert(offsetof(struct __cygwin64_ucontext, uc_mcontext) == __OFFSET_CYGWIN64_UCONTEXT_MCONTEXT);
static_assert(offsetof(struct __cygwin64_ucontext, uc_sigmask) == __OFFSET_CYGWIN64_UCONTEXT_SIGMASK);
static_assert(offsetof(struct __cygwin64_ucontext, uc_stack) == __OFFSET_CYGWIN64_UCONTEXT_STACK);
static_assert(sizeof(struct __cygwin64_ucontext) == __SIZEOF_CYGWIN64_UCONTEXT);
static_assert(alignof(struct __cygwin64_ucontext) == __ALIGNOF_CYGWIN64_UCONTEXT);





#include <kos/bits/debugtrap32.h>

/* struct debugtrap_reason32 */
static_assert(offsetof(struct debugtrap_reason32, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON32_INTARG);
static_assert(offsetof(struct debugtrap_reason32, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON32_PTRARG);
static_assert(offsetof(struct debugtrap_reason32, dtr_reason) == __OFFSET_DEBUGTRAP_REASON32_REASON);
static_assert(offsetof(struct debugtrap_reason32, dtr_signo) == __OFFSET_DEBUGTRAP_REASON32_SIGNO);
static_assert(offsetof(struct debugtrap_reason32, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON32_STRARG);
static_assert(sizeof(struct debugtrap_reason32) == __SIZEOF_DEBUGTRAP_REASON32);





#include <kos/bits/debugtrap64.h>

/* struct debugtrap_reason64 */
static_assert(offsetof(struct debugtrap_reason64, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON64_INTARG);
static_assert(offsetof(struct debugtrap_reason64, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON64_PTRARG);
static_assert(offsetof(struct debugtrap_reason64, dtr_reason) == __OFFSET_DEBUGTRAP_REASON64_REASON);
static_assert(offsetof(struct debugtrap_reason64, dtr_signo) == __OFFSET_DEBUGTRAP_REASON64_SIGNO);
static_assert(offsetof(struct debugtrap_reason64, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON64_STRARG);
static_assert(sizeof(struct debugtrap_reason64) == __SIZEOF_DEBUGTRAP_REASON64);





#include <kos/bits/exception_data32.h>

/* struct __exception_badalloc_data32 */
/* ... */

/* struct __exception_buffer_too_small_data32 */
/* ... */

/* struct __exception_exit_process_data32 */
/* ... */

/* struct __exception_exit_thread_data32 */
/* ... */

/* struct __exception_fserror_data32 */
/* ... */

/* struct __exception_illegal_instruction_data32 */
/* ... */

/* struct __exception_illegal_operation_data32 */
/* ... */

/* struct __exception_index_error_data32 */
/* ... */

/* struct __exception_insufficient_rights_data32 */
/* ... */

/* struct __exception_invalid_argument_data32 */
/* ... */

/* struct __exception_invalid_handle_data32 */
/* ... */

/* struct __exception_ioerror_data32 */
/* ... */

/* struct __exception_net_error_data32 */
/* ... */

/* struct __exception_not_executable_data32 */
/* ... */

/* struct __exception_no_device_data32 */
/* ... */

/* struct __exception_process_exited_data32 */
/* ... */

/* struct __exception_segfault_data32 */
/* ... */

/* struct __exception_unhandled_interrupt_data32 */
/* ... */

/* struct __exception_unknown_systemcall_data32 */
/* ... */

/* union __exception_data_pointers32 */
/* ... */

/* struct __exception_data32 */
static_assert(offsetof(struct __exception_data32, e_args) == __OFFSET_EXCEPTION_DATA32_ARGS);
static_assert(offsetof(struct __exception_data32, e_class) == __OFFSET_EXCEPTION_DATA32_CLASS);
static_assert(offsetof(struct __exception_data32, e_code) == __OFFSET_EXCEPTION_DATA32_CODE);
static_assert(offsetof(struct __exception_data32, e_faultaddr) == __OFFSET_EXCEPTION_DATA32_FAULTADDR);
static_assert(offsetof(struct __exception_data32, e_subclass) == __OFFSET_EXCEPTION_DATA32_SUBCLASS);
static_assert(sizeof(struct __exception_data32) == __SIZEOF_EXCEPTION_DATA32);





#include <kos/bits/exception_data64.h>

/* struct __exception_badalloc_data64 */
/* ... */

/* struct __exception_buffer_too_small_data64 */
/* ... */

/* struct __exception_exit_process_data64 */
/* ... */

/* struct __exception_exit_thread_data64 */
/* ... */

/* struct __exception_fserror_data64 */
/* ... */

/* struct __exception_illegal_instruction_data64 */
/* ... */

/* struct __exception_illegal_operation_data64 */
/* ... */

/* struct __exception_index_error_data64 */
/* ... */

/* struct __exception_insufficient_rights_data64 */
/* ... */

/* struct __exception_invalid_argument_data64 */
/* ... */

/* struct __exception_invalid_handle_data64 */
/* ... */

/* struct __exception_ioerror_data64 */
/* ... */

/* struct __exception_net_error_data64 */
/* ... */

/* struct __exception_not_executable_data64 */
/* ... */

/* struct __exception_no_device_data64 */
/* ... */

/* struct __exception_process_exited_data64 */
/* ... */

/* struct __exception_segfault_data64 */
/* ... */

/* struct __exception_unhandled_interrupt_data64 */
/* ... */

/* struct __exception_unknown_systemcall_data64 */
/* ... */

/* union __exception_data_pointers64 */
/* ... */

/* struct __exception_data64 */
static_assert(offsetof(struct __exception_data64, e_args) == __OFFSET_EXCEPTION_DATA64_ARGS);
static_assert(offsetof(struct __exception_data64, e_class) == __OFFSET_EXCEPTION_DATA64_CLASS);
static_assert(offsetof(struct __exception_data64, e_code) == __OFFSET_EXCEPTION_DATA64_CODE);
static_assert(offsetof(struct __exception_data64, e_faultaddr) == __OFFSET_EXCEPTION_DATA64_FAULTADDR);
static_assert(offsetof(struct __exception_data64, e_subclass) == __OFFSET_EXCEPTION_DATA64_SUBCLASS);
static_assert(sizeof(struct __exception_data64) == __SIZEOF_EXCEPTION_DATA64);





#include <kos/bits/ukern-struct32.h>

/* struct userkern32 */
static_assert(offsetof(struct userkern32, uk_base) == OFFSET_USERKERN32_BASE);
static_assert(offsetof(struct userkern32, uk_egid) == OFFSET_USERKERN32_EGID);
static_assert(offsetof(struct userkern32, uk_euid) == OFFSET_USERKERN32_EUID);
static_assert(offsetof(struct userkern32, uk_gid) == OFFSET_USERKERN32_GID);
static_assert(offsetof(struct userkern32, uk_pgid) == OFFSET_USERKERN32_PGID);
static_assert(offsetof(struct userkern32, uk_pid) == OFFSET_USERKERN32_PID);
static_assert(offsetof(struct userkern32, uk_ppid) == OFFSET_USERKERN32_PPID);
static_assert(offsetof(struct userkern32, uk_regs) == OFFSET_USERKERN32_REGS);
static_assert(offsetof(struct userkern32, uk_sfpu) == OFFSET_USERKERN32_SFPU);
static_assert(offsetof(struct userkern32, uk_sgid) == OFFSET_USERKERN32_SGID);
static_assert(offsetof(struct userkern32, uk_sid) == OFFSET_USERKERN32_SID);
static_assert(offsetof(struct userkern32, uk_suid) == OFFSET_USERKERN32_SUID);
static_assert(offsetof(struct userkern32, uk_tid) == OFFSET_USERKERN32_TID);
static_assert(offsetof(struct userkern32, uk_uid) == OFFSET_USERKERN32_UID);
static_assert(offsetof(struct userkern32, uk_xfpu) == OFFSET_USERKERN32_XFPU);
static_assert(sizeof(struct userkern32) == SIZEOF_USERKERN32);





#include <kos/bits/ukern-struct64.h>

/* struct userkern64 */
static_assert(offsetof(struct userkern64, uk_base) == OFFSET_USERKERN64_BASE);
static_assert(offsetof(struct userkern64, uk_egid) == OFFSET_USERKERN64_EGID);
static_assert(offsetof(struct userkern64, uk_euid) == OFFSET_USERKERN64_EUID);
static_assert(offsetof(struct userkern64, uk_gid) == OFFSET_USERKERN64_GID);
static_assert(offsetof(struct userkern64, uk_pgid) == OFFSET_USERKERN64_PGID);
static_assert(offsetof(struct userkern64, uk_pid) == OFFSET_USERKERN64_PID);
static_assert(offsetof(struct userkern64, uk_ppid) == OFFSET_USERKERN64_PPID);
static_assert(offsetof(struct userkern64, uk_regs) == OFFSET_USERKERN64_REGS);
static_assert(offsetof(struct userkern64, uk_sfpu) == OFFSET_USERKERN64_SFPU);
static_assert(offsetof(struct userkern64, uk_sgid) == OFFSET_USERKERN64_SGID);
static_assert(offsetof(struct userkern64, uk_sid) == OFFSET_USERKERN64_SID);
static_assert(offsetof(struct userkern64, uk_suid) == OFFSET_USERKERN64_SUID);
static_assert(offsetof(struct userkern64, uk_tid) == OFFSET_USERKERN64_TID);
static_assert(offsetof(struct userkern64, uk_uid) == OFFSET_USERKERN64_UID);
static_assert(offsetof(struct userkern64, uk_xfpu) == OFFSET_USERKERN64_XFPU);
static_assert(sizeof(struct userkern64) == SIZEOF_USERKERN64);





#include <kos/bits/syscall-info32.h>

/* struct rpc_syscall_info32 */
static_assert(offsetof(struct rpc_syscall_info32, rsi_flags) == OFFSET_RPC_SYSCALL_INFO32_FLAGS);
static_assert(offsetof(struct rpc_syscall_info32, rsi_sysno) == OFFSET_RPC_SYSCALL_INFO32_SYSNO);
static_assert(sizeof(struct rpc_syscall_info32) == SIZEOF_RPC_SYSCALL_INFO32);





#include <kos/bits/syscall-info64.h>

/* struct rpc_syscall_info64 */
static_assert(offsetof(struct rpc_syscall_info64, rsi_flags) == OFFSET_RPC_SYSCALL_INFO64_FLAGS);
static_assert(offsetof(struct rpc_syscall_info64, rsi_sysno) == OFFSET_RPC_SYSCALL_INFO64_SYSNO);
static_assert(sizeof(struct rpc_syscall_info64) == SIZEOF_RPC_SYSCALL_INFO64);





#include <kos/exec/asm/elf32.h>





#include <kos/exec/asm/elf64.h>





#include <kos/exec/bits/peb32.h>

/* struct process_peb32 */
static_assert(offsetof(struct process_peb32, pp_argc) == OFFSET_PROCESS_PEB32_ARGC);
static_assert(offsetof(struct process_peb32, pp_argv) == OFFSET_PROCESS_PEB32_ARGV);
static_assert(offsetof(struct process_peb32, pp_envc) == OFFSET_PROCESS_PEB32_ENVC);
static_assert(offsetof(struct process_peb32, pp_envp) == OFFSET_PROCESS_PEB32_ENVP);





#include <kos/exec/bits/peb64.h>

/* struct process_peb64 */
static_assert(offsetof(struct process_peb64, pp_argc) == OFFSET_PROCESS_PEB64_ARGC);
static_assert(offsetof(struct process_peb64, pp_argv) == OFFSET_PROCESS_PEB64_ARGV);
static_assert(offsetof(struct process_peb64, pp_envc) == OFFSET_PROCESS_PEB64_ENVC);
static_assert(offsetof(struct process_peb64, pp_envp) == OFFSET_PROCESS_PEB64_ENVP);





#include <kos/kernel/bits/cpu-state32.h>

/* struct gpregs32 */
static_assert(offsetof(struct gpregs32, gp_eax) == OFFSET_GPREGS32_EAX);
static_assert(offsetof(struct gpregs32, gp_ebp) == OFFSET_GPREGS32_EBP);
static_assert(offsetof(struct gpregs32, gp_ebx) == OFFSET_GPREGS32_EBX);
static_assert(offsetof(struct gpregs32, gp_ecx) == OFFSET_GPREGS32_ECX);
static_assert(offsetof(struct gpregs32, gp_edi) == OFFSET_GPREGS32_EDI);
static_assert(offsetof(struct gpregs32, gp_edx) == OFFSET_GPREGS32_EDX);
static_assert(offsetof(struct gpregs32, gp_esi) == OFFSET_GPREGS32_ESI);
static_assert(offsetof(struct gpregs32, gp_esp) == OFFSET_GPREGS32_ESP);
static_assert(sizeof(struct gpregs32) == SIZEOF_GPREGS32);

/* struct sgregs32 */
static_assert(offsetof(struct sgregs32, sg_ds) == OFFSET_SGREGS32_DS);
static_assert(offsetof(struct sgregs32, sg_es) == OFFSET_SGREGS32_ES);
static_assert(offsetof(struct sgregs32, sg_fs) == OFFSET_SGREGS32_FS);
static_assert(offsetof(struct sgregs32, sg_gs) == OFFSET_SGREGS32_GS);
static_assert(sizeof(struct sgregs32) == SIZEOF_SGREGS32);

/* struct coregs32 */
static_assert(offsetof(struct coregs32, co_cr0) == OFFSET_COREGS32_CR0);
static_assert(offsetof(struct coregs32, co_cr2) == OFFSET_COREGS32_CR2);
static_assert(offsetof(struct coregs32, co_cr3) == OFFSET_COREGS32_CR3);
static_assert(offsetof(struct coregs32, co_cr4) == OFFSET_COREGS32_CR4);
static_assert(sizeof(struct coregs32) == SIZEOF_COREGS32);

/* struct drregs32 */
static_assert(offsetof(struct drregs32, dr_dr0) == OFFSET_DRREGS32_DR0);
static_assert(offsetof(struct drregs32, dr_dr1) == OFFSET_DRREGS32_DR1);
static_assert(offsetof(struct drregs32, dr_dr2) == OFFSET_DRREGS32_DR2);
static_assert(offsetof(struct drregs32, dr_dr3) == OFFSET_DRREGS32_DR3);
static_assert(offsetof(struct drregs32, dr_dr6) == OFFSET_DRREGS32_DR6);
static_assert(offsetof(struct drregs32, dr_dr7) == OFFSET_DRREGS32_DR7);
static_assert(sizeof(struct drregs32) == SIZEOF_DRREGS32);

/* struct irregs32_kernel */
static_assert(offsetof(struct irregs32_kernel, ir_cs) == OFFSET_IRREGS32_KERNEL_CS);
static_assert(offsetof(struct irregs32_kernel, ir_eflags) == OFFSET_IRREGS32_KERNEL_EFLAGS);
static_assert(offsetof(struct irregs32_kernel, ir_eip) == OFFSET_IRREGS32_KERNEL_EIP);
static_assert(sizeof(struct irregs32_kernel) == SIZEOF_IRREGS32_KERNEL);

/* struct irregs32_user */
static_assert(offsetof(struct irregs32_user, ir_cs) == OFFSET_IRREGS32_USER_CS);
static_assert(offsetof(struct irregs32_user, ir_eflags) == OFFSET_IRREGS32_USER_EFLAGS);
static_assert(offsetof(struct irregs32_user, ir_eip) == OFFSET_IRREGS32_USER_EIP);
static_assert(offsetof(struct irregs32_user, ir_esp) == OFFSET_IRREGS32_USER_ESP);
static_assert(offsetof(struct irregs32_user, ir_ss) == OFFSET_IRREGS32_USER_SS);
static_assert(sizeof(struct irregs32_user) == SIZEOF_IRREGS32_USER);

/* struct irregs32_vm86 */
static_assert(offsetof(struct irregs32_vm86, ir_cs) == OFFSET_IRREGS32_VM86_CS);
static_assert(offsetof(struct irregs32_vm86, ir_ds) == OFFSET_IRREGS32_VM86_DS);
static_assert(offsetof(struct irregs32_vm86, ir_eflags) == OFFSET_IRREGS32_VM86_EFLAGS);
static_assert(offsetof(struct irregs32_vm86, ir_eip) == OFFSET_IRREGS32_VM86_EIP);
static_assert(offsetof(struct irregs32_vm86, ir_es) == OFFSET_IRREGS32_VM86_ES);
static_assert(offsetof(struct irregs32_vm86, ir_esp) == OFFSET_IRREGS32_VM86_ESP);
static_assert(offsetof(struct irregs32_vm86, ir_fs) == OFFSET_IRREGS32_VM86_FS);
static_assert(offsetof(struct irregs32_vm86, ir_gs) == OFFSET_IRREGS32_VM86_GS);
static_assert(offsetof(struct irregs32_vm86, ir_ss) == OFFSET_IRREGS32_VM86_SS);
static_assert(sizeof(struct irregs32_vm86) == SIZEOF_IRREGS32_VM86);

/* struct ucpustate32 */
static_assert(offsetof(struct ucpustate32, ucs_cs) == OFFSET_UCPUSTATE32_CS);
static_assert(offsetof(struct ucpustate32, ucs_eflags) == OFFSET_UCPUSTATE32_EFLAGS);
static_assert(offsetof(struct ucpustate32, ucs_eip) == OFFSET_UCPUSTATE32_EIP);
static_assert(offsetof(struct ucpustate32, ucs_gpregs) == OFFSET_UCPUSTATE32_GPREGS);
static_assert(offsetof(struct ucpustate32, ucs_sgregs) == OFFSET_UCPUSTATE32_SGREGS);
static_assert(offsetof(struct ucpustate32, ucs_ss) == OFFSET_UCPUSTATE32_SS);
static_assert(sizeof(struct ucpustate32) == SIZEOF_UCPUSTATE32);

/* struct lcpustate32 */
static_assert(offsetof(struct lcpustate32, lcs_ebp) == OFFSET_LCPUSTATE32_EBP);
static_assert(offsetof(struct lcpustate32, lcs_ebx) == OFFSET_LCPUSTATE32_EBX);
static_assert(offsetof(struct lcpustate32, lcs_edi) == OFFSET_LCPUSTATE32_EDI);
static_assert(offsetof(struct lcpustate32, lcs_eip) == OFFSET_LCPUSTATE32_EIP);
static_assert(offsetof(struct lcpustate32, lcs_esi) == OFFSET_LCPUSTATE32_ESI);
static_assert(offsetof(struct lcpustate32, lcs_esp) == OFFSET_LCPUSTATE32_ESP);
static_assert(sizeof(struct lcpustate32) == SIZEOF_LCPUSTATE32);

/* struct kcpustate32 */
static_assert(offsetof(struct kcpustate32, kcs_eflags) == OFFSET_KCPUSTATE32_EFLAGS);
static_assert(offsetof(struct kcpustate32, kcs_eip) == OFFSET_KCPUSTATE32_EIP);
static_assert(offsetof(struct kcpustate32, kcs_gpregs) == OFFSET_KCPUSTATE32_GPREGS);
static_assert(sizeof(struct kcpustate32) == SIZEOF_KCPUSTATE32);

/* struct icpustate32 */
static_assert(offsetof(struct icpustate32, ics_ds) == OFFSET_ICPUSTATE32_DS);
static_assert(offsetof(struct icpustate32, ics_es) == OFFSET_ICPUSTATE32_ES);
static_assert(offsetof(struct icpustate32, ics_fs) == OFFSET_ICPUSTATE32_FS);
static_assert(offsetof(struct icpustate32, ics_gpregs) == OFFSET_ICPUSTATE32_GPREGS);
static_assert(offsetof(struct icpustate32, ics_irregs) == OFFSET_ICPUSTATE32_IRREGS);

/* struct scpustate32 */
static_assert(offsetof(struct scpustate32, scs_gpregs) == OFFSET_SCPUSTATE32_GPREGS);
static_assert(offsetof(struct scpustate32, scs_irregs) == OFFSET_SCPUSTATE32_IRREGS);
static_assert(offsetof(struct scpustate32, scs_sgregs) == OFFSET_SCPUSTATE32_SGREGS);

/* struct desctab32 */
static_assert(offsetof(struct desctab32, dt_base) == OFFSET_DESCTAB32_BASE);
static_assert(offsetof(struct desctab32, dt_limit) == OFFSET_DESCTAB32_LIMIT);
static_assert(sizeof(struct desctab32) == SIZEOF_DESCTAB32);

/* struct fcpustate32 */
static_assert(offsetof(struct fcpustate32, fcs_coregs) == OFFSET_FCPUSTATE32_COREGS);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_cs) == OFFSET_FCPUSTATE32_CS);
static_assert(offsetof(struct fcpustate32, fcs_drregs) == OFFSET_FCPUSTATE32_DRREGS);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_ds) == OFFSET_FCPUSTATE32_DS);
static_assert(offsetof(struct fcpustate32, fcs_eflags) == OFFSET_FCPUSTATE32_EFLAGS);
static_assert(offsetof(struct fcpustate32, fcs_eip) == OFFSET_FCPUSTATE32_EIP);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_es) == OFFSET_FCPUSTATE32_ES);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_fs) == OFFSET_FCPUSTATE32_FS);
static_assert(offsetof(struct fcpustate32, fcs_gdt) == OFFSET_FCPUSTATE32_GDT);
static_assert(offsetof(struct fcpustate32, fcs_gpregs) == OFFSET_FCPUSTATE32_GPREGS);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_gs) == OFFSET_FCPUSTATE32_GS);
static_assert(offsetof(struct fcpustate32, fcs_idt) == OFFSET_FCPUSTATE32_IDT);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_ldt) == OFFSET_FCPUSTATE32_LDT);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_ss) == OFFSET_FCPUSTATE32_SS);
static_assert(offsetof(struct fcpustate32, fcs_sgregs.sg_tr) == OFFSET_FCPUSTATE32_TR);
static_assert(sizeof(struct fcpustate32) == SIZEOF_FCPUSTATE32);





#include <kos/kernel/bits/cpu-state64.h>

/* struct gpregs64 */
static_assert(offsetof(struct gpregs64, gp_r10) == OFFSET_GPREGS64_R10);
static_assert(offsetof(struct gpregs64, gp_r11) == OFFSET_GPREGS64_R11);
static_assert(offsetof(struct gpregs64, gp_r12) == OFFSET_GPREGS64_R12);
static_assert(offsetof(struct gpregs64, gp_r13) == OFFSET_GPREGS64_R13);
static_assert(offsetof(struct gpregs64, gp_r14) == OFFSET_GPREGS64_R14);
static_assert(offsetof(struct gpregs64, gp_r15) == OFFSET_GPREGS64_R15);
static_assert(offsetof(struct gpregs64, gp_r8) == OFFSET_GPREGS64_R8);
static_assert(offsetof(struct gpregs64, gp_r9) == OFFSET_GPREGS64_R9);
static_assert(offsetof(struct gpregs64, gp_rax) == OFFSET_GPREGS64_RAX);
static_assert(offsetof(struct gpregs64, gp_rbp) == OFFSET_GPREGS64_RBP);
static_assert(offsetof(struct gpregs64, gp_rbx) == OFFSET_GPREGS64_RBX);
static_assert(offsetof(struct gpregs64, gp_rcx) == OFFSET_GPREGS64_RCX);
static_assert(offsetof(struct gpregs64, gp_rdi) == OFFSET_GPREGS64_RDI);
static_assert(offsetof(struct gpregs64, gp_rdx) == OFFSET_GPREGS64_RDX);
static_assert(offsetof(struct gpregs64, gp_rsi) == OFFSET_GPREGS64_RSI);
static_assert(offsetof(struct gpregs64, gp_rsp) == OFFSET_GPREGS64_RSP);
static_assert(sizeof(struct gpregs64) == SIZEOF_GPREGS64);

/* struct gpregsnsp64 */
static_assert(offsetof(struct gpregsnsp64, gp_r10) == OFFSET_GPREGSNSP64_R10);
static_assert(offsetof(struct gpregsnsp64, gp_r11) == OFFSET_GPREGSNSP64_R11);
static_assert(offsetof(struct gpregsnsp64, gp_r12) == OFFSET_GPREGSNSP64_R12);
static_assert(offsetof(struct gpregsnsp64, gp_r13) == OFFSET_GPREGSNSP64_R13);
static_assert(offsetof(struct gpregsnsp64, gp_r14) == OFFSET_GPREGSNSP64_R14);
static_assert(offsetof(struct gpregsnsp64, gp_r15) == OFFSET_GPREGSNSP64_R15);
static_assert(offsetof(struct gpregsnsp64, gp_r8) == OFFSET_GPREGSNSP64_R8);
static_assert(offsetof(struct gpregsnsp64, gp_r9) == OFFSET_GPREGSNSP64_R9);
static_assert(offsetof(struct gpregsnsp64, gp_rax) == OFFSET_GPREGSNSP64_RAX);
static_assert(offsetof(struct gpregsnsp64, gp_rbp) == OFFSET_GPREGSNSP64_RBP);
static_assert(offsetof(struct gpregsnsp64, gp_rbx) == OFFSET_GPREGSNSP64_RBX);
static_assert(offsetof(struct gpregsnsp64, gp_rcx) == OFFSET_GPREGSNSP64_RCX);
static_assert(offsetof(struct gpregsnsp64, gp_rdi) == OFFSET_GPREGSNSP64_RDI);
static_assert(offsetof(struct gpregsnsp64, gp_rdx) == OFFSET_GPREGSNSP64_RDX);
static_assert(offsetof(struct gpregsnsp64, gp_rsi) == OFFSET_GPREGSNSP64_RSI);
static_assert(sizeof(struct gpregsnsp64) == SIZEOF_GPREGSNSP64);

/* struct sgregs64 */
static_assert(offsetof(struct sgregs64, sg_ds) == OFFSET_SGREGS64_DS);
static_assert(offsetof(struct sgregs64, sg_es) == OFFSET_SGREGS64_ES);
static_assert(offsetof(struct sgregs64, sg_fs) == OFFSET_SGREGS64_FS);
static_assert(offsetof(struct sgregs64, sg_gs) == OFFSET_SGREGS64_GS);
static_assert(sizeof(struct sgregs64) == SIZEOF_SGREGS64);

/* struct sgbase64 */
static_assert(offsetof(struct sgbase64, sg_fsbase) == OFFSET_SGBASE64_FSBASE);
static_assert(offsetof(struct sgbase64, sg_gsbase) == OFFSET_SGBASE64_GSBASE);
static_assert(sizeof(struct sgbase64) == SIZEOF_SGBASE64);

/* struct coregs64 */
static_assert(offsetof(struct coregs64, co_cr0) == OFFSET_COREGS64_CR0);
static_assert(offsetof(struct coregs64, co_cr2) == OFFSET_COREGS64_CR2);
static_assert(offsetof(struct coregs64, co_cr3) == OFFSET_COREGS64_CR3);
static_assert(offsetof(struct coregs64, co_cr4) == OFFSET_COREGS64_CR4);
static_assert(sizeof(struct coregs64) == SIZEOF_COREGS64);

/* struct drregs64 */
static_assert(offsetof(struct drregs64, dr_dr0) == OFFSET_DRREGS64_DR0);
static_assert(offsetof(struct drregs64, dr_dr1) == OFFSET_DRREGS64_DR1);
static_assert(offsetof(struct drregs64, dr_dr2) == OFFSET_DRREGS64_DR2);
static_assert(offsetof(struct drregs64, dr_dr3) == OFFSET_DRREGS64_DR3);
static_assert(offsetof(struct drregs64, dr_dr6) == OFFSET_DRREGS64_DR6);
static_assert(offsetof(struct drregs64, dr_dr7) == OFFSET_DRREGS64_DR7);
static_assert(sizeof(struct drregs64) == SIZEOF_DRREGS64);

/* struct irregs64 */
static_assert(offsetof(struct irregs64, ir_cs) == OFFSET_IRREGS64_CS);
static_assert(offsetof(struct irregs64, ir_rflags) == OFFSET_IRREGS64_RFLAGS);
static_assert(offsetof(struct irregs64, ir_rip) == OFFSET_IRREGS64_RIP);
static_assert(offsetof(struct irregs64, ir_rsp) == OFFSET_IRREGS64_RSP);
static_assert(offsetof(struct irregs64, ir_ss) == OFFSET_IRREGS64_SS);
static_assert(sizeof(struct irregs64) == SIZEOF_IRREGS64);

/* struct ucpustate64 */
static_assert(offsetof(struct ucpustate64, ucs_cs) == OFFSET_UCPUSTATE64_CS);
static_assert(offsetof(struct ucpustate64, ucs_gpregs) == OFFSET_UCPUSTATE64_GPREGS);
static_assert(offsetof(struct ucpustate64, ucs_rflags) == OFFSET_UCPUSTATE64_RFLAGS);
static_assert(offsetof(struct ucpustate64, ucs_rip) == OFFSET_UCPUSTATE64_RIP);
static_assert(offsetof(struct ucpustate64, ucs_sgbase) == OFFSET_UCPUSTATE64_SGBASE);
static_assert(offsetof(struct ucpustate64, ucs_sgregs) == OFFSET_UCPUSTATE64_SGREGS);
static_assert(offsetof(struct ucpustate64, ucs_ss) == OFFSET_UCPUSTATE64_SS);
static_assert(sizeof(struct ucpustate64) == SIZEOF_UCPUSTATE64);

/* struct lcpustate64 */
static_assert(offsetof(struct lcpustate64, lcs_r12) == OFFSET_LCPUSTATE64_R12);
static_assert(offsetof(struct lcpustate64, lcs_r13) == OFFSET_LCPUSTATE64_R13);
static_assert(offsetof(struct lcpustate64, lcs_r14) == OFFSET_LCPUSTATE64_R14);
static_assert(offsetof(struct lcpustate64, lcs_r15) == OFFSET_LCPUSTATE64_R15);
static_assert(offsetof(struct lcpustate64, lcs_rbp) == OFFSET_LCPUSTATE64_RBP);
static_assert(offsetof(struct lcpustate64, lcs_rbx) == OFFSET_LCPUSTATE64_RBX);
static_assert(offsetof(struct lcpustate64, lcs_rip) == OFFSET_LCPUSTATE64_RIP);
static_assert(offsetof(struct lcpustate64, lcs_rsp) == OFFSET_LCPUSTATE64_RSP);
static_assert(sizeof(struct lcpustate64) == SIZEOF_LCPUSTATE64);

/* struct kcpustate64 */
static_assert(offsetof(struct kcpustate64, kcs_gpregs) == OFFSET_KCPUSTATE64_GPREGS);
static_assert(offsetof(struct kcpustate64, kcs_rflags) == OFFSET_KCPUSTATE64_RFLAGS);
static_assert(offsetof(struct kcpustate64, kcs_rip) == OFFSET_KCPUSTATE64_RIP);
static_assert(sizeof(struct kcpustate64) == SIZEOF_KCPUSTATE64);

/* struct icpustate64 */
static_assert(offsetof(struct icpustate64, ics_gpregs) == OFFSET_ICPUSTATE64_GPREGSNSP);
static_assert(offsetof(struct icpustate64, ics_irregs) == OFFSET_ICPUSTATE64_IRREGS);
static_assert(sizeof(struct icpustate64) == SIZEOF_ICPUSTATE64);

/* struct scpustate64 */
static_assert(offsetof(struct scpustate64, scs_gpregs) == OFFSET_SCPUSTATE64_GPREGSNSP);
static_assert(offsetof(struct scpustate64, scs_irregs) == OFFSET_SCPUSTATE64_IRREGS);
static_assert(offsetof(struct scpustate64, scs_sgbase) == OFFSET_SCPUSTATE64_SGBASE);
static_assert(offsetof(struct scpustate64, scs_sgregs) == OFFSET_SCPUSTATE64_SGREGS);
static_assert(sizeof(struct scpustate64) == SIZEOF_SCPUSTATE64);

/* struct desctab64 */
static_assert(offsetof(struct desctab64, dt_base) == OFFSET_DESCTAB64_BASE);
static_assert(offsetof(struct desctab64, dt_limit) == OFFSET_DESCTAB64_LIMIT);
static_assert(sizeof(struct desctab64) == SIZEOF_DESCTAB64);

/* struct fcpustate64 */
static_assert(offsetof(struct fcpustate64, fcs_coregs) == OFFSET_FCPUSTATE64_COREGS);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_cs) == OFFSET_FCPUSTATE64_CS);
static_assert(offsetof(struct fcpustate64, fcs_drregs) == OFFSET_FCPUSTATE64_DRREGS);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_ds) == OFFSET_FCPUSTATE64_DS);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_es) == OFFSET_FCPUSTATE64_ES);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_fs) == OFFSET_FCPUSTATE64_FS);
static_assert(offsetof(struct fcpustate64, fcs_gdt) == OFFSET_FCPUSTATE64_GDT);
static_assert(offsetof(struct fcpustate64, fcs_gpregs) == OFFSET_FCPUSTATE64_GPREGS);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_gs) == OFFSET_FCPUSTATE64_GS);
static_assert(offsetof(struct fcpustate64, fcs_idt) == OFFSET_FCPUSTATE64_IDT);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_ldt) == OFFSET_FCPUSTATE64_LDT);
static_assert(offsetof(struct fcpustate64, fcs_rflags) == OFFSET_FCPUSTATE64_RFLAGS);
static_assert(offsetof(struct fcpustate64, fcs_rip) == OFFSET_FCPUSTATE64_RIP);
static_assert(offsetof(struct fcpustate64, fcs_sgbase) == OFFSET_FCPUSTATE64_SGBASE);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_ss) == OFFSET_FCPUSTATE64_SS);
static_assert(offsetof(struct fcpustate64, fcs_sgregs.sg_tr) == OFFSET_FCPUSTATE64_TR);
static_assert(sizeof(struct fcpustate64) == SIZEOF_FCPUSTATE64);





#include <kos/kernel/bits/fpu-sstate.h>

/* struct sfpuenv */
static_assert(offsetof(struct sfpuenv, fe_fcs) == OFFSET_SFPUENV_FCS);
static_assert(offsetof(struct sfpuenv, fe_fcw) == OFFSET_SFPUENV_FCW);
static_assert(offsetof(struct sfpuenv, fe_fdp) == OFFSET_SFPUENV_FDP);
static_assert(offsetof(struct sfpuenv, fe_fds) == OFFSET_SFPUENV_FDS);
static_assert(offsetof(struct sfpuenv, fe_fip) == OFFSET_SFPUENV_FIP);
static_assert(offsetof(struct sfpuenv, fe_fop) == OFFSET_SFPUENV_FOP);
static_assert(offsetof(struct sfpuenv, fe_fsw) == OFFSET_SFPUENV_FSW);
static_assert(offsetof(struct sfpuenv, fe_ftw) == OFFSET_SFPUENV_FTW);
static_assert(sizeof(struct sfpuenv) == SIZEOF_SFPUENV);
static_assert(alignof(struct sfpuenv) == ALIGNOF_SFPUENV);

/* struct sfpustate */
static_assert(offsetof(struct sfpustate, fs_fcs) == OFFSET_SFPUSTATE_FCS);
static_assert(offsetof(struct sfpustate, fs_fcw) == OFFSET_SFPUSTATE_FCW);
static_assert(offsetof(struct sfpustate, fs_fdp) == OFFSET_SFPUSTATE_FDP);
static_assert(offsetof(struct sfpustate, fs_fds) == OFFSET_SFPUSTATE_FDS);
static_assert(offsetof(struct sfpustate, fs_fip) == OFFSET_SFPUSTATE_FIP);
static_assert(offsetof(struct sfpustate, fs_fop) == OFFSET_SFPUSTATE_FOP);
static_assert(offsetof(struct sfpustate, fs_fsw) == OFFSET_SFPUSTATE_FSW);
static_assert(offsetof(struct sfpustate, fs_ftw) == OFFSET_SFPUSTATE_FTW);
static_assert(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_MM0);
static_assert(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_MM1);
static_assert(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_MM2);
static_assert(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_MM3);
static_assert(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_MM4);
static_assert(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_MM5);
static_assert(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_MM6);
static_assert(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_MM7);
static_assert(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_ST0);
static_assert(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_ST1);
static_assert(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_ST2);
static_assert(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_ST3);
static_assert(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_ST4);
static_assert(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_ST5);
static_assert(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_ST6);
static_assert(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_ST7);
static_assert(offsetof(struct sfpustate, __fs_pad2) == OFFSET_SFPUSTATE___PAD2);
static_assert(sizeof(struct sfpustate) == SIZEOF_SFPUSTATE);
static_assert(alignof(struct sfpustate) == ALIGNOF_SFPUSTATE);





#include <kos/kernel/bits/fpu-state32.h>

/* struct xfpustate32 */
static_assert(offsetof(struct xfpustate32, fx_fcs) == OFFSET_XFPUSTATE32_FCS);
static_assert(offsetof(struct xfpustate32, fx_fcw) == OFFSET_XFPUSTATE32_FCW);
static_assert(offsetof(struct xfpustate32, fx_fdp) == OFFSET_XFPUSTATE32_FDP);
static_assert(offsetof(struct xfpustate32, fx_fds) == OFFSET_XFPUSTATE32_FDS);
static_assert(offsetof(struct xfpustate32, fx_fip) == OFFSET_XFPUSTATE32_FIP);
static_assert(offsetof(struct xfpustate32, fx_fop) == OFFSET_XFPUSTATE32_FOP);
static_assert(offsetof(struct xfpustate32, fx_fsw) == OFFSET_XFPUSTATE32_FSW);
static_assert(offsetof(struct xfpustate32, fx_ftw) == OFFSET_XFPUSTATE32_FTW);
static_assert(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_MM0);
static_assert(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_MM1);
static_assert(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_MM2);
static_assert(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_MM3);
static_assert(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_MM4);
static_assert(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_MM5);
static_assert(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_MM6);
static_assert(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_MM7);
static_assert(offsetof(struct xfpustate32, fx_mxcsr) == OFFSET_XFPUSTATE32_MXCSR);
static_assert(offsetof(struct xfpustate32, fx_mxcsr_mask) == OFFSET_XFPUSTATE32_MXCSR_MASK);
static_assert(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_ST0);
static_assert(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_ST1);
static_assert(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_ST2);
static_assert(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_ST3);
static_assert(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_ST4);
static_assert(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_ST5);
static_assert(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_ST6);
static_assert(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_ST7);
static_assert(offsetof(struct xfpustate32, fx_xmm[0]) == OFFSET_XFPUSTATE32_XMM0);
static_assert(offsetof(struct xfpustate32, fx_xmm[1]) == OFFSET_XFPUSTATE32_XMM1);
static_assert(offsetof(struct xfpustate32, fx_xmm[2]) == OFFSET_XFPUSTATE32_XMM2);
static_assert(offsetof(struct xfpustate32, fx_xmm[3]) == OFFSET_XFPUSTATE32_XMM3);
static_assert(offsetof(struct xfpustate32, fx_xmm[4]) == OFFSET_XFPUSTATE32_XMM4);
static_assert(offsetof(struct xfpustate32, fx_xmm[5]) == OFFSET_XFPUSTATE32_XMM5);
static_assert(offsetof(struct xfpustate32, fx_xmm[6]) == OFFSET_XFPUSTATE32_XMM6);
static_assert(offsetof(struct xfpustate32, fx_xmm[7]) == OFFSET_XFPUSTATE32_XMM7);
static_assert(sizeof(struct xfpustate32) == SIZEOF_XFPUSTATE32);
static_assert(alignof(struct xfpustate32) == ALIGNOF_XFPUSTATE32);

/* struct fpustate32 */
static_assert(sizeof(struct fpustate32) == SIZEOF_FPUSTATE32);
static_assert(alignof(struct fpustate32) == ALIGNOF_FPUSTATE32);





#include <kos/kernel/bits/fpu-state64.h>

/* struct xfpustate64 */
static_assert(offsetof(struct xfpustate64, fx_fcw) == OFFSET_XFPUSTATE64_FCW);
static_assert(offsetof(struct xfpustate64, fx_fdp) == OFFSET_XFPUSTATE64_FDP);
static_assert(offsetof(struct xfpustate64, fx_fip) == OFFSET_XFPUSTATE64_FIP);
static_assert(offsetof(struct xfpustate64, fx_fop) == OFFSET_XFPUSTATE64_FOP);
static_assert(offsetof(struct xfpustate64, fx_fsw) == OFFSET_XFPUSTATE64_FSW);
static_assert(offsetof(struct xfpustate64, fx_ftw) == OFFSET_XFPUSTATE64_FTW);
static_assert(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_MM0);
static_assert(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_MM1);
static_assert(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_MM2);
static_assert(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_MM3);
static_assert(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_MM4);
static_assert(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_MM5);
static_assert(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_MM6);
static_assert(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_MM7);
static_assert(offsetof(struct xfpustate64, fx_mxcsr) == OFFSET_XFPUSTATE64_MXCSR);
static_assert(offsetof(struct xfpustate64, fx_mxcsr_mask) == OFFSET_XFPUSTATE64_MXCSR_MASK);
static_assert(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_ST0);
static_assert(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_ST1);
static_assert(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_ST2);
static_assert(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_ST3);
static_assert(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_ST4);
static_assert(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_ST5);
static_assert(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_ST6);
static_assert(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_ST7);
static_assert(offsetof(struct xfpustate64, fx_xmm[0]) == OFFSET_XFPUSTATE64_XMM0);
static_assert(offsetof(struct xfpustate64, fx_xmm[1]) == OFFSET_XFPUSTATE64_XMM1);
static_assert(offsetof(struct xfpustate64, fx_xmm[10]) == OFFSET_XFPUSTATE64_XMM10);
static_assert(offsetof(struct xfpustate64, fx_xmm[11]) == OFFSET_XFPUSTATE64_XMM11);
static_assert(offsetof(struct xfpustate64, fx_xmm[12]) == OFFSET_XFPUSTATE64_XMM12);
static_assert(offsetof(struct xfpustate64, fx_xmm[13]) == OFFSET_XFPUSTATE64_XMM13);
static_assert(offsetof(struct xfpustate64, fx_xmm[14]) == OFFSET_XFPUSTATE64_XMM14);
static_assert(offsetof(struct xfpustate64, fx_xmm[15]) == OFFSET_XFPUSTATE64_XMM15);
static_assert(offsetof(struct xfpustate64, fx_xmm[2]) == OFFSET_XFPUSTATE64_XMM2);
static_assert(offsetof(struct xfpustate64, fx_xmm[3]) == OFFSET_XFPUSTATE64_XMM3);
static_assert(offsetof(struct xfpustate64, fx_xmm[4]) == OFFSET_XFPUSTATE64_XMM4);
static_assert(offsetof(struct xfpustate64, fx_xmm[5]) == OFFSET_XFPUSTATE64_XMM5);
static_assert(offsetof(struct xfpustate64, fx_xmm[6]) == OFFSET_XFPUSTATE64_XMM6);
static_assert(offsetof(struct xfpustate64, fx_xmm[7]) == OFFSET_XFPUSTATE64_XMM7);
static_assert(offsetof(struct xfpustate64, fx_xmm[8]) == OFFSET_XFPUSTATE64_XMM8);
static_assert(offsetof(struct xfpustate64, fx_xmm[9]) == OFFSET_XFPUSTATE64_XMM9);
static_assert(sizeof(struct xfpustate64) == SIZEOF_XFPUSTATE64);
static_assert(alignof(struct xfpustate64) == ALIGNOF_XFPUSTATE64);

/* struct fpustate64 */
static_assert(sizeof(struct fpustate64) == SIZEOF_FPUSTATE64);
static_assert(alignof(struct fpustate64) == ALIGNOF_FPUSTATE64);





#include <kos/kernel/x86/tss16.h>

/* struct tss16 */
static_assert(offsetof(struct tss16, t_ax) == OFFSET_TSS16_AX);
static_assert(offsetof(struct tss16, t_bp) == OFFSET_TSS16_BP);
static_assert(offsetof(struct tss16, t_bx) == OFFSET_TSS16_BX);
static_assert(offsetof(struct tss16, t_cs) == OFFSET_TSS16_CS);
static_assert(offsetof(struct tss16, t_cx) == OFFSET_TSS16_CX);
static_assert(offsetof(struct tss16, t_di) == OFFSET_TSS16_DI);
static_assert(offsetof(struct tss16, t_ds) == OFFSET_TSS16_DS);
static_assert(offsetof(struct tss16, t_dx) == OFFSET_TSS16_DX);
static_assert(offsetof(struct tss16, t_es) == OFFSET_TSS16_ES);
static_assert(offsetof(struct tss16, t_flags) == OFFSET_TSS16_FLAGS);
static_assert(offsetof(struct tss16, t_ip) == OFFSET_TSS16_IP);
static_assert(offsetof(struct tss16, t_ldtr) == OFFSET_TSS16_LDTR);
static_assert(offsetof(struct tss16, t_link) == OFFSET_TSS16_LINK);
static_assert(offsetof(struct tss16, t_si) == OFFSET_TSS16_SI);
static_assert(offsetof(struct tss16, t_sp) == OFFSET_TSS16_SP);
static_assert(offsetof(struct tss16, t_sp0) == OFFSET_TSS16_SP0);
static_assert(offsetof(struct tss16, t_sp1) == OFFSET_TSS16_SP1);
static_assert(offsetof(struct tss16, t_sp2) == OFFSET_TSS16_SP2);
static_assert(offsetof(struct tss16, t_ss) == OFFSET_TSS16_SS);
static_assert(offsetof(struct tss16, t_ss0) == OFFSET_TSS16_SS0);
static_assert(offsetof(struct tss16, t_ss1) == OFFSET_TSS16_SS1);
static_assert(offsetof(struct tss16, t_ss2) == OFFSET_TSS16_SS2);
static_assert(sizeof(struct tss16) == SIZEOF_TSS16);
static_assert(alignof(struct tss16) == ALIGNOF_TSS16);





#include <kos/kernel/x86/tss32.h>

/* struct tss32 */
static_assert(offsetof(struct tss32, t_cr3) == OFFSET_TSS32_CR3);
static_assert(offsetof(struct tss32, t_cs) == OFFSET_TSS32_CS);
static_assert(offsetof(struct tss32, t_ds) == OFFSET_TSS32_DS);
static_assert(offsetof(struct tss32, t_eax) == OFFSET_TSS32_EAX);
static_assert(offsetof(struct tss32, t_ebp) == OFFSET_TSS32_EBP);
static_assert(offsetof(struct tss32, t_ebx) == OFFSET_TSS32_EBX);
static_assert(offsetof(struct tss32, t_ecx) == OFFSET_TSS32_ECX);
static_assert(offsetof(struct tss32, t_edi) == OFFSET_TSS32_EDI);
static_assert(offsetof(struct tss32, t_edx) == OFFSET_TSS32_EDX);
static_assert(offsetof(struct tss32, t_eflags) == OFFSET_TSS32_EFLAGS);
static_assert(offsetof(struct tss32, t_eip) == OFFSET_TSS32_EIP);
static_assert(offsetof(struct tss32, t_es) == OFFSET_TSS32_ES);
static_assert(offsetof(struct tss32, t_esi) == OFFSET_TSS32_ESI);
static_assert(offsetof(struct tss32, t_esp) == OFFSET_TSS32_ESP);
static_assert(offsetof(struct tss32, t_esp0) == OFFSET_TSS32_ESP0);
static_assert(offsetof(struct tss32, t_esp1) == OFFSET_TSS32_ESP1);
static_assert(offsetof(struct tss32, t_esp2) == OFFSET_TSS32_ESP2);
static_assert(offsetof(struct tss32, t_flags) == OFFSET_TSS32_FLAGS);
static_assert(offsetof(struct tss32, t_fs) == OFFSET_TSS32_FS);
static_assert(offsetof(struct tss32, t_gs) == OFFSET_TSS32_GS);
static_assert(offsetof(struct tss32, t_iomap) == OFFSET_TSS32_IOMAP);
static_assert(offsetof(struct tss32, t_ldtr) == OFFSET_TSS32_LDTR);
static_assert(offsetof(struct tss32, t_link) == OFFSET_TSS32_LINK);
static_assert(offsetof(struct tss32, t_ss) == OFFSET_TSS32_SS);
static_assert(offsetof(struct tss32, t_ss0) == OFFSET_TSS32_SS0);
static_assert(offsetof(struct tss32, t_ss1) == OFFSET_TSS32_SS1);
static_assert(offsetof(struct tss32, t_ss2) == OFFSET_TSS32_SS2);
static_assert(sizeof(struct tss32) == SIZEOF_TSS32);
static_assert(alignof(struct tss32) == ALIGNOF_TSS32);





#include <kos/kernel/x86/tss64.h>

/* struct tss64 */
static_assert(offsetof(struct tss64, t_iomap) == OFFSET_TSS64_IOMAP);
static_assert(offsetof(struct tss64, t_ist1) == OFFSET_TSS64_IST1);
static_assert(offsetof(struct tss64, t_ist2) == OFFSET_TSS64_IST2);
static_assert(offsetof(struct tss64, t_ist3) == OFFSET_TSS64_IST3);
static_assert(offsetof(struct tss64, t_ist4) == OFFSET_TSS64_IST4);
static_assert(offsetof(struct tss64, t_ist5) == OFFSET_TSS64_IST5);
static_assert(offsetof(struct tss64, t_ist6) == OFFSET_TSS64_IST6);
static_assert(offsetof(struct tss64, t_ist7) == OFFSET_TSS64_IST7);
static_assert(offsetof(struct tss64, t_rsp0) == OFFSET_TSS64_RSP0);
static_assert(offsetof(struct tss64, t_rsp1) == OFFSET_TSS64_RSP1);
static_assert(offsetof(struct tss64, t_rsp2) == OFFSET_TSS64_RSP2);
static_assert(sizeof(struct tss64) == SIZEOF_TSS64);
static_assert(alignof(struct tss64) == ALIGNOF_TSS64);





static_assert(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_ST(0));
static_assert(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_MM(0));
static_assert(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_ST(1));
static_assert(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_MM(1));
static_assert(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_ST(2));
static_assert(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_MM(2));
static_assert(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_ST(3));
static_assert(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_MM(3));
static_assert(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_ST(4));
static_assert(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_MM(4));
static_assert(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_ST(5));
static_assert(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_MM(5));
static_assert(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_ST(6));
static_assert(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_MM(6));
static_assert(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_ST(7));
static_assert(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_MM(7));
static_assert(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_ST(0));
static_assert(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_MM(0));
static_assert(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_ST(1));
static_assert(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_MM(1));
static_assert(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_ST(2));
static_assert(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_MM(2));
static_assert(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_ST(3));
static_assert(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_MM(3));
static_assert(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_ST(4));
static_assert(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_MM(4));
static_assert(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_ST(5));
static_assert(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_MM(5));
static_assert(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_ST(6));
static_assert(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_MM(6));
static_assert(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_ST(7));
static_assert(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_MM(7));
static_assert(offsetof(struct xfpustate32, fx_xmm[0]) == OFFSET_XFPUSTATE32_XMM(0));
static_assert(offsetof(struct xfpustate32, fx_xmm[1]) == OFFSET_XFPUSTATE32_XMM(1));
static_assert(offsetof(struct xfpustate32, fx_xmm[2]) == OFFSET_XFPUSTATE32_XMM(2));
static_assert(offsetof(struct xfpustate32, fx_xmm[3]) == OFFSET_XFPUSTATE32_XMM(3));
static_assert(offsetof(struct xfpustate32, fx_xmm[4]) == OFFSET_XFPUSTATE32_XMM(4));
static_assert(offsetof(struct xfpustate32, fx_xmm[5]) == OFFSET_XFPUSTATE32_XMM(5));
static_assert(offsetof(struct xfpustate32, fx_xmm[6]) == OFFSET_XFPUSTATE32_XMM(6));
static_assert(offsetof(struct xfpustate32, fx_xmm[7]) == OFFSET_XFPUSTATE32_XMM(7));
static_assert(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_ST(0));
static_assert(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_MM(0));
static_assert(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_ST(1));
static_assert(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_MM(1));
static_assert(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_ST(2));
static_assert(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_MM(2));
static_assert(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_ST(3));
static_assert(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_MM(3));
static_assert(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_ST(4));
static_assert(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_MM(4));
static_assert(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_ST(5));
static_assert(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_MM(5));
static_assert(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_ST(6));
static_assert(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_MM(6));
static_assert(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_ST(7));
static_assert(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_MM(7));
static_assert(offsetof(struct xfpustate64, fx_xmm[0]) == OFFSET_XFPUSTATE64_XMM(0));
static_assert(offsetof(struct xfpustate64, fx_xmm[1]) == OFFSET_XFPUSTATE64_XMM(1));
static_assert(offsetof(struct xfpustate64, fx_xmm[2]) == OFFSET_XFPUSTATE64_XMM(2));
static_assert(offsetof(struct xfpustate64, fx_xmm[3]) == OFFSET_XFPUSTATE64_XMM(3));
static_assert(offsetof(struct xfpustate64, fx_xmm[4]) == OFFSET_XFPUSTATE64_XMM(4));
static_assert(offsetof(struct xfpustate64, fx_xmm[5]) == OFFSET_XFPUSTATE64_XMM(5));
static_assert(offsetof(struct xfpustate64, fx_xmm[6]) == OFFSET_XFPUSTATE64_XMM(6));
static_assert(offsetof(struct xfpustate64, fx_xmm[7]) == OFFSET_XFPUSTATE64_XMM(7));
static_assert(offsetof(struct xfpustate64, fx_xmm[8]) == OFFSET_XFPUSTATE64_XMM(8));
static_assert(offsetof(struct xfpustate64, fx_xmm[9]) == OFFSET_XFPUSTATE64_XMM(9));
static_assert(offsetof(struct xfpustate64, fx_xmm[10]) == OFFSET_XFPUSTATE64_XMM(10));
static_assert(offsetof(struct xfpustate64, fx_xmm[11]) == OFFSET_XFPUSTATE64_XMM(11));
static_assert(offsetof(struct xfpustate64, fx_xmm[12]) == OFFSET_XFPUSTATE64_XMM(12));
static_assert(offsetof(struct xfpustate64, fx_xmm[13]) == OFFSET_XFPUSTATE64_XMM(13));
static_assert(offsetof(struct xfpustate64, fx_xmm[14]) == OFFSET_XFPUSTATE64_XMM(14));
static_assert(offsetof(struct xfpustate64, fx_xmm[15]) == OFFSET_XFPUSTATE64_XMM(15));
static_assert(OFFSET_TSS64_IST1 == OFFSET_TSS64_IST(1));
static_assert(OFFSET_TSS64_IST2 == OFFSET_TSS64_IST(2));
static_assert(OFFSET_TSS64_IST3 == OFFSET_TSS64_IST(3));
static_assert(OFFSET_TSS64_IST4 == OFFSET_TSS64_IST(4));
static_assert(OFFSET_TSS64_IST5 == OFFSET_TSS64_IST(5));
static_assert(OFFSET_TSS64_IST6 == OFFSET_TSS64_IST(6));
static_assert(OFFSET_TSS64_IST7 == OFFSET_TSS64_IST(7));
#if X86_64_VA_LIST_XMM_COUNT >= 0
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[0]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(0));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 1
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[1]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(1));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 2
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[2]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(2));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 3
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[3]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(3));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 4
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[4]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(4));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 5
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[5]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(5));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 6
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[6]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(6));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 7
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[7]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(7));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 8
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[8]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(8));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 9
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[9]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(9));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 10
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[10]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(10));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 11
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[11]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(11));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 12
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[12]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(12));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 13
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[13]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(13));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 14
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[14]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(14));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 15
static_assert(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[15]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(15));
#endif
//[[[end]]]


#include <bits/os/sigset.h>
static_assert(sizeof(struct __sigset_struct) == __SIZEOF_SIGSET_T__);
static_assert(COMPILER_LENOF(((struct __sigset_struct *)0)->__val) == __SIGSET_NWORDS);

#include <bits/crt/semaphore.h>
static_assert(sizeof(__sem_t) == __SIZEOF_SEM_T);
static_assert(alignof(__sem_t) >= alignof(void *));


#include <kos/kernel/x86/segment.h>
static_assert(sizeof(struct segment) == SIZEOF_SEGMENT_DESCRIPTOR);
static_assert(SIZEOF_SEGMENT_DESCRIPTOR == 8);
static_assert(offsetof(struct segment, s_descriptor.d_limit0) == OFFSET_SEGMENT_DESCRIPTOR_LIMIT0);
static_assert(offsetof(struct segment, s_descriptor.d_base0) == OFFSET_SEGMENT_DESCRIPTOR_BASE0);
static_assert(offsetof(struct segment, s_descriptor.d_base1) == OFFSET_SEGMENT_DESCRIPTOR_BASE1);
static_assert(offsetof(struct segment, s_descriptor.d_type_s_dpl_p) == OFFSET_SEGMENT_DESCRIPTOR_TYPE_S_DPL_P);
static_assert(offsetof(struct segment, s_descriptor.d_limit1_avl_l_db_g) == OFFSET_SEGMENT_DESCRIPTOR_LIMIT1_AVL_L_DB_G);
static_assert(offsetof(struct segment, s_descriptor.d_base2) == OFFSET_SEGMENT_DESCRIPTOR_BASE2);
static_assert(sizeof(struct idt_segment) == SIZEOF_IDT_SEGMENT);


#include <kos/kernel/x86/gdt.h>

static_assert(SEGMENT_IS_VALID_KERNCODE(SEGMENT_KERNEL_CODE));
static_assert(!SEGMENT_IS_VALID_KERNCODE(SEGMENT_USER_CODE));
static_assert(!SEGMENT_IS_VALID_KERNCODE(SEGMENT_USER_CODE_RPL));
static_assert(SEGMENT_IS_VALID_KERNDATA(SEGMENT_KERNEL_DATA));
static_assert(!SEGMENT_IS_VALID_KERNDATA(SEGMENT_USER_DATA));
static_assert(!SEGMENT_IS_VALID_KERNDATA(SEGMENT_USER_DATA_RPL));

static_assert(SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE_RPL));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE_RPL));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE));
static_assert(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA_RPL));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA_RPL));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA));

#ifndef __x86_64__
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_FSBASE_RPL));
static_assert(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_FSBASE_RPL));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_GSBASE_RPL));
static_assert(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_GSBASE_RPL));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_FSBASE));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_FSBASE));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_GSBASE));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_GSBASE));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS_DF));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS_DF));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS_DF | 3));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS_DF | 3));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_FSBASE));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_FSBASE));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_FSBASE | 3));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_FSBASE | 3));
#endif /* !__x86_64__ */

static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_CODE));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_DATA));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_CODE | 3));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_DATA | 3));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS | 3));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS | 3));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_LDT));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_LDT));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_LDT | 3));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_LDT | 3));
static_assert(!SEGMENT_IS_VALID_USERCODE(LDT_SEGMENT_SYSCALL));
static_assert(!SEGMENT_IS_VALID_USERDATA(LDT_SEGMENT_SYSCALL));
static_assert(!SEGMENT_IS_VALID_USERCODE(LDT_SEGMENT_SYSCALL_RPL));
static_assert(!SEGMENT_IS_VALID_USERDATA(LDT_SEGMENT_SYSCALL_RPL));

#ifdef __x86_64__
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE32));
static_assert(SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE32_RPL));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE32));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE32_RPL));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA32));
static_assert(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA32_RPL));
static_assert(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA32));
static_assert(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA32_RPL));
#endif /* __x86_64__ */

#include <kos/bits/exception_data32.h>
#include <kos/bits/exception_data64.h>
static_assert(__SIZEOF_EXCEPT_CODE32_T__ == sizeof(__except_code32_t));
static_assert(__SIZEOF_EXCEPT_CLASS32_T__ == sizeof(__except_class32_t));
static_assert(__SIZEOF_EXCEPT_SUBCLASS32_T__ == sizeof(__except_subclass32_t));
static_assert(__SIZEOF_EXCEPT_CODE64_T__ == sizeof(__except_code64_t));
static_assert(__SIZEOF_EXCEPT_CLASS64_T__ == sizeof(__except_class64_t));
static_assert(__SIZEOF_EXCEPT_SUBCLASS64_T__ == sizeof(__except_subclass64_t));
static_assert(__SIZEOF_EXCEPT_CODE_T__ == sizeof(__except_code_t));
static_assert(__SIZEOF_EXCEPT_CLASS_T__ == sizeof(__except_class_t));
static_assert(__SIZEOF_EXCEPT_SUBCLASS_T__ == sizeof(__except_subclass_t));

#include <bits/os/kos/mcontext32.h>
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EDI]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_edi));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_ESI]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_esi));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EBP]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_ebp));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_ESP]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_esp));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EBX]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_ebx));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EDX]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_edx));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_ECX]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_ecx));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EAX]) == offsetof(struct __mcontextx32, mc_context.ucs_gpregs.gp_eax));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_GS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_gs));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_GS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_gs16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_FS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_fs));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_FS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_fs16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_ES])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_es));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_ES])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_es16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_DS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_ds));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_DS])  == offsetof(struct __mcontextx32, mc_context.ucs_sgregs.sg_ds16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_CS])  == offsetof(struct __mcontextx32, mc_context.ucs_cs));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_CS])  == offsetof(struct __mcontextx32, mc_context.ucs_cs16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_SS])  == offsetof(struct __mcontextx32, mc_context.ucs_ss));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_SS])  == offsetof(struct __mcontextx32, mc_context.ucs_ss16));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EFL]) == offsetof(struct __mcontextx32, mc_context.ucs_eflags));
static_assert(offsetof(struct __mcontextx32, mc_gregs[__MCONTEXTX32_REGNO_EIP]) == offsetof(struct __mcontextx32, mc_context.ucs_eip));

#include <bits/os/kos/mcontext64.h>
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_GS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_gs));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_GS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_gs16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_FS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_fs));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_FS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_fs16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_ES])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_es));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_ES])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_es16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_DS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_ds));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_DS])     == offsetof(struct __mcontextx64, mc_context.ucs_sgregs.sg_ds16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_GSBASE]) == offsetof(struct __mcontextx64, mc_context.ucs_sgbase.sg_gsbase));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_FSBASE]) == offsetof(struct __mcontextx64, mc_context.ucs_sgbase.sg_fsbase));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_CS])     == offsetof(struct __mcontextx64, mc_context.ucs_cs));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_CS])     == offsetof(struct __mcontextx64, mc_context.ucs_cs16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_SS])     == offsetof(struct __mcontextx64, mc_context.ucs_ss));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_SS])     == offsetof(struct __mcontextx64, mc_context.ucs_ss16));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R15])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r15));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R14])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r14));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R13])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r13));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R12])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r12));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R11])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r11));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R10])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r10));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R9])     == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r9));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_R8])     == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_r8));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RDI])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rdi));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RSI])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rsi));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RBP])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rbp));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RSP])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rsp));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RBX])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rbx));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RDX])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rdx));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RCX])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rcx));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RAX])    == offsetof(struct __mcontextx64, mc_context.ucs_gpregs.gp_rax));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RFLAGS]) == offsetof(struct __mcontextx64, mc_context.ucs_rflags));
static_assert(offsetof(struct __mcontextx64, mc_gregs[__MCONTEXTX64_REGNO_RIP])    == offsetof(struct __mcontextx64, mc_context.ucs_rip));



#endif /* !GUARD__VERIFY_ARCH_I386_ASSERT_TYPES_C */
