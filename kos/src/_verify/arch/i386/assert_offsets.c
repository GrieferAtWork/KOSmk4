/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

#include <ieee754.h>
#include <stdalign.h>
#include <stddef.h>
STATIC_ASSERT(sizeof(union ieee754_float) == 4);
STATIC_ASSERT(alignof(union ieee754_float) == 4);
STATIC_ASSERT(sizeof(union ieee754_double) == 8);
STATIC_ASSERT(alignof(union ieee754_double) == 8);
STATIC_ASSERT(sizeof(union ieee854_long_double) == 16);
STATIC_ASSERT(alignof(union ieee854_long_double) == 16);
STATIC_ASSERT(sizeof(union ieee854_float80) == 10);

/*[[[deemon
import * from .....misc.libgen.assert_offsetof;
local files = {
	"../../../../include/i386-kos/bits/cmsghdr-struct32.h",
	"../../../../include/i386-kos/bits/cmsghdr-struct64.h",
	"../../../../include/i386-kos/bits/flock-struct32.h",
	"../../../../include/i386-kos/bits/flock-struct64.h",
	"../../../../include/i386-kos/bits/itimerspec32.h",
	"../../../../include/i386-kos/bits/itimerspec64.h",
	"../../../../include/i386-kos/bits/itimerval32.h",
	"../../../../include/i386-kos/bits/itimerval64.h",
	"../../../../include/i386-kos/bits/mmsghdr-struct32.h",
	"../../../../include/i386-kos/bits/mmsghdr-struct64.h",
	"../../../../include/i386-kos/bits/msghdr-struct32.h",
	"../../../../include/i386-kos/bits/msghdr-struct64.h",
	"../../../../include/i386-kos/bits/rusage-struct32.h",
	"../../../../include/i386-kos/bits/rusage-struct64.h",
	"../../../../include/i386-kos/bits/sigaction-struct-cygwin.h",
	"../../../../include/i386-kos/bits/sigaction-struct32.h",
	"../../../../include/i386-kos/bits/sigaction-struct64.h",
	"../../../../include/i386-kos/bits/sigevent32.h",
	"../../../../include/i386-kos/bits/sigevent64.h",
	"../../../../include/i386-kos/bits/siginfo-struct32.h",
	"../../../../include/i386-kos/bits/siginfo-struct64.h",
	"../../../../include/i386-kos/bits/sigstack32.h",
	"../../../../include/i386-kos/bits/sigstack64.h",
	"../../../../include/i386-kos/bits/sigval32.h",
	"../../../../include/i386-kos/bits/sigval64.h",
	"../../../../include/i386-kos/bits/stat-kos32.h",
	"../../../../include/i386-kos/bits/stat-kos64.h",
	"../../../../include/i386-kos/bits/statfs32.h",
	"../../../../include/i386-kos/bits/statfs64.h",
	"../../../../include/i386-kos/bits/timeb32.h",
	"../../../../include/i386-kos/bits/timeb64.h",
	"../../../../include/i386-kos/bits/timespec32.h",
	"../../../../include/i386-kos/bits/timespec64.h",
	"../../../../include/i386-kos/bits/timeval32.h",
	"../../../../include/i386-kos/bits/timeval64.h",
	"../../../../include/i386-kos/bits/utimbuf32.h",
	"../../../../include/i386-kos/bits/utimbuf64.h",
	"../../../../include/i386-kos/bits/va_list-struct32.h",
	"../../../../include/i386-kos/bits/va_list-struct64.h",
	"../../../../include/i386-kos/kos/bits/debugtrap32.h",
	"../../../../include/i386-kos/kos/bits/debugtrap64.h",
	"../../../../include/i386-kos/kos/bits/exception_data32.h",
	"../../../../include/i386-kos/kos/bits/exception_data64.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct32.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct64.h",
	"../../../../include/i386-kos/kos/bits/spawn-action32.h",
	"../../../../include/i386-kos/kos/bits/spawn-action64.h",
	"../../../../include/i386-kos/kos/exec/asm/elf32.h",
	"../../../../include/i386-kos/kos/exec/asm/elf64.h",
	"../../../../include/i386-kos/kos/exec/bits/library-listdef32.h",
	"../../../../include/i386-kos/kos/exec/bits/library-listdef64.h",
	"../../../../include/i386-kos/kos/exec/bits/peb32.h",
	"../../../../include/i386-kos/kos/exec/bits/peb64.h",
	"../../../../include/i386-kos/kos/kernel/cpu-state32.h",
	"../../../../include/i386-kos/kos/kernel/cpu-state64.h",
	"../../../../include/i386-kos/kos/kernel/fpu-sstate.h",
	"../../../../include/i386-kos/kos/kernel/fpu-state32.h",
	"../../../../include/i386-kos/kos/kernel/fpu-state64.h",
	"../../../../include/i386-kos/kos/kernel/mcontext32.h",
	"../../../../include/i386-kos/kos/kernel/mcontext64.h",
	"../../../../include/i386-kos/kos/kernel/tss16.h",
	"../../../../include/i386-kos/kos/kernel/tss32.h",
	"../../../../include/i386-kos/kos/kernel/tss64.h",
	"../../../../include/i386-kos/kos/kernel/ucontext32.h",
	"../../../../include/i386-kos/kos/kernel/ucontext64.h",
	"../../../../include/i386-kos/librpc/bits/rpc32.h",
	"../../../../include/i386-kos/librpc/bits/rpc64.h",
	"../../../../include/i386-kos/librpc/bits/syscall-info32.h",
	"../../../../include/i386-kos/librpc/bits/syscall-info64.h",
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

print "#undef sigev_value";
print "#undef sigev_signo";
print "#undef sigev_notify";
print "#undef sigev_notify_function";
print "#undef sigev_notify_attributes";
genAsserts("../../../../include/i386-kos/bits/sigevent-cygwin.h");

print "#undef si_signo";
print "#undef si_code";
print "#undef si_pid";
print "#undef si_uid";
print "#undef si_errno";
print "#undef _si_data";
print "#undef _si_commune";
print "#undef si_sigval";
print "#undef si_value";
print "#undef si_tid";
print "#undef si_overrun";
print "#undef si_status";
print "#undef si_utime";
print "#undef si_stime";
print "#undef si_addr";
genAsserts("../../../../include/i386-kos/bits/siginfo-struct-cygwin.h");

for (local i: [:8]) {
	print "STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[{i}]) == OFFSET_SFPUSTATE_ST({i}));".format({ .i = i });
	print "STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[{i}]) == OFFSET_SFPUSTATE_MM({i}));".format({ .i = i });
}
for (local i: [:8]) {
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[{i}]) == OFFSET_XFPUSTATE32_ST({i}));".format({ .i = i });
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[{i}]) == OFFSET_XFPUSTATE32_MM({i}));".format({ .i = i });
}
for (local i: [:8])
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[{i}]) == OFFSET_XFPUSTATE32_XMM({i}));".format({ .i = i });
for (local i: [:8]) {
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[{i}]) == OFFSET_XFPUSTATE64_ST({i}));".format({ .i = i });
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[{i}]) == OFFSET_XFPUSTATE64_MM({i}));".format({ .i = i });
}
for (local i: [:16])
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[{i}]) == OFFSET_XFPUSTATE64_XMM({i}));".format({ .i = i });
for (local i: [1:8])
	print "STATIC_ASSERT(OFFSET_TSS64_IST{i} == OFFSET_TSS64_IST({i}));".format({ .i = i });
for (local i: [:16]) {
	print "#if X86_64_VA_LIST_XMM_COUNT >=",i;
	print "STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[{i}]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM({i}));".format({ .i = i });
	print "#endif";
}

]]]*/
#include <bits/cmsghdr-struct32.h>

/* struct __cmsghdrx32 */
STATIC_ASSERT(offsetof(struct __cmsghdrx32, cmsg_data) == __OFFSET_CMSGHDRX32_DATA);
STATIC_ASSERT(offsetof(struct __cmsghdrx32, cmsg_len) == __OFFSET_CMSGHDRX32_LEN);
STATIC_ASSERT(offsetof(struct __cmsghdrx32, cmsg_level) == __OFFSET_CMSGHDRX32_LEVEL);
STATIC_ASSERT(offsetof(struct __cmsghdrx32, cmsg_type) == __OFFSET_CMSGHDRX32_TYPE);





#include <bits/cmsghdr-struct64.h>

/* struct __cmsghdrx64 */
STATIC_ASSERT(offsetof(struct __cmsghdrx64, cmsg_data) == __OFFSET_CMSGHDRX64_DATA);
STATIC_ASSERT(offsetof(struct __cmsghdrx64, cmsg_len) == __OFFSET_CMSGHDRX64_LEN);
STATIC_ASSERT(offsetof(struct __cmsghdrx64, cmsg_level) == __OFFSET_CMSGHDRX64_LEVEL);
STATIC_ASSERT(offsetof(struct __cmsghdrx64, cmsg_type) == __OFFSET_CMSGHDRX64_TYPE);





#include <bits/flock-struct32.h>

/* struct flockx32 */
STATIC_ASSERT(offsetof(struct flockx32, l_len) == __OFFSET_FLOCKX32_LEN);
STATIC_ASSERT(offsetof(struct flockx32, l_pid) == __OFFSET_FLOCKX32_PID);
STATIC_ASSERT(offsetof(struct flockx32, l_start) == __OFFSET_FLOCKX32_START);
STATIC_ASSERT(offsetof(struct flockx32, l_type) == __OFFSET_FLOCKX32_TYPE);
STATIC_ASSERT(offsetof(struct flockx32, l_whence) == __OFFSET_FLOCKX32_WHENCE);
STATIC_ASSERT(sizeof(struct flockx32) == __SIZEOF_FLOCKX32);

/* struct flockx32_64 */
STATIC_ASSERT(offsetof(struct flockx32_64, l_len) == __OFFSET_FLOCKX32_64_LEN);
STATIC_ASSERT(offsetof(struct flockx32_64, l_pid) == __OFFSET_FLOCKX32_64_PID);
STATIC_ASSERT(offsetof(struct flockx32_64, l_start) == __OFFSET_FLOCKX32_64_START);
STATIC_ASSERT(offsetof(struct flockx32_64, l_type) == __OFFSET_FLOCKX32_64_TYPE);
STATIC_ASSERT(offsetof(struct flockx32_64, l_whence) == __OFFSET_FLOCKX32_64_WHENCE);
STATIC_ASSERT(sizeof(struct flockx32_64) == __SIZEOF_FLOCKX32_64);

/* struct __flockx32_64_alt */
/* ... */





#include <bits/flock-struct64.h>

/* struct flockx64 */
STATIC_ASSERT(offsetof(struct flockx64, l_len) == __OFFSET_FLOCKX64_LEN);
STATIC_ASSERT(offsetof(struct flockx64, l_pid) == __OFFSET_FLOCKX64_PID);
STATIC_ASSERT(offsetof(struct flockx64, l_start) == __OFFSET_FLOCKX64_START);
STATIC_ASSERT(offsetof(struct flockx64, l_type) == __OFFSET_FLOCKX64_TYPE);
STATIC_ASSERT(offsetof(struct flockx64, l_whence) == __OFFSET_FLOCKX64_WHENCE);
STATIC_ASSERT(sizeof(struct flockx64) == __SIZEOF_FLOCKX64);

/* struct __flockx64_alt */
/* ... */





#include <bits/itimerspec32.h>

/* struct itimerspecx32 */
STATIC_ASSERT(offsetof(struct itimerspecx32, it_value) == __OFFSET_ITIMERSPECX32_VALUE);
STATIC_ASSERT(offsetof(struct itimerspecx32, it_interval) == __OFFSET_ITIMERSPECX32_INTERVAL);
STATIC_ASSERT(sizeof(struct itimerspecx32) == __SIZEOF_ITIMERSPECX32);
STATIC_ASSERT(alignof(struct itimerspecx32) == __ALIGNOF_ITIMERSPECX32);

/* struct itimerspecx32_64 */
STATIC_ASSERT(offsetof(struct itimerspecx32_64, it_value) == __OFFSET_ITIMERSPECX32_64_VALUE);
STATIC_ASSERT(offsetof(struct itimerspecx32_64, it_interval) == __OFFSET_ITIMERSPECX32_64_INTERVAL);
STATIC_ASSERT(sizeof(struct itimerspecx32_64) == __SIZEOF_ITIMERSPECX32_64);
STATIC_ASSERT(alignof(struct itimerspecx32_64) == __ALIGNOF_ITIMERSPECX32_64);

/* struct __itimerspecx32_64_alt */
/* ... */





#include <bits/itimerspec64.h>

/* struct itimerspecx64 */
STATIC_ASSERT(offsetof(struct itimerspecx64, it_value) == __OFFSET_ITIMERSPECX64_VALUE);
STATIC_ASSERT(offsetof(struct itimerspecx64, it_interval) == __OFFSET_ITIMERSPECX64_INTERVAL);
STATIC_ASSERT(sizeof(struct itimerspecx64) == __SIZEOF_ITIMERSPECX64);
STATIC_ASSERT(alignof(struct itimerspecx64) == __ALIGNOF_ITIMERSPECX64);

/* struct __itimerspecx64_alt */
/* ... */





#include <bits/itimerval32.h>

/* struct itimervalx32 */
STATIC_ASSERT(offsetof(struct itimervalx32, it_value) == __OFFSET_ITIMERVALX32_VALUE);
STATIC_ASSERT(offsetof(struct itimervalx32, it_interval) == __OFFSET_ITIMERVALX32_INTERVAL);
STATIC_ASSERT(sizeof(struct itimervalx32) == __SIZEOF_ITIMERVALX32);
STATIC_ASSERT(alignof(struct itimervalx32) == __ALIGNOF_ITIMERVALX32);

/* struct itimervalx32_64 */
STATIC_ASSERT(offsetof(struct itimervalx32_64, it_value) == __OFFSET_ITIMERVALX32_64_VALUE);
STATIC_ASSERT(offsetof(struct itimervalx32_64, it_interval) == __OFFSET_ITIMERVALX32_64_INTERVAL);
STATIC_ASSERT(sizeof(struct itimervalx32_64) == __SIZEOF_ITIMERVALX32_64);
STATIC_ASSERT(alignof(struct itimervalx32_64) == __ALIGNOF_ITIMERVALX32_64);

/* struct __itimervalx32_64_alt */
/* ... */





#include <bits/itimerval64.h>

/* struct itimervalx64 */
STATIC_ASSERT(offsetof(struct itimervalx64, it_value) == __OFFSET_ITIMERVALX64_VALUE);
STATIC_ASSERT(offsetof(struct itimervalx64, it_interval) == __OFFSET_ITIMERVALX64_INTERVAL);
STATIC_ASSERT(sizeof(struct itimervalx64) == __SIZEOF_ITIMERVALX64);
STATIC_ASSERT(alignof(struct itimervalx64) == __ALIGNOF_ITIMERVALX64);

/* struct __itimervalx64_alt */
/* ... */





#include <bits/mmsghdr-struct32.h>

/* struct __mmsghdrx32 */
STATIC_ASSERT(offsetof(struct __mmsghdrx32, msg_len) == __OFFSET_MMSGHDRX32_LEN);
STATIC_ASSERT(offsetof(struct __mmsghdrx32, msg_hdr) == __OFFSET_MMSGHDRX32_HDR);
STATIC_ASSERT(sizeof(struct __mmsghdrx32) == __SIZEOF_MMSGHDRX32);
STATIC_ASSERT(alignof(struct __mmsghdrx32) == __ALIGNOF_MMSGHDRX32);





#include <bits/mmsghdr-struct64.h>

/* struct __mmsghdrx64 */
STATIC_ASSERT(offsetof(struct __mmsghdrx64, msg_len) == __OFFSET_MMSGHDRX64_LEN);
STATIC_ASSERT(offsetof(struct __mmsghdrx64, msg_hdr) == __OFFSET_MMSGHDRX64_HDR);
STATIC_ASSERT(sizeof(struct __mmsghdrx64) == __SIZEOF_MMSGHDRX64);
STATIC_ASSERT(alignof(struct __mmsghdrx64) == __ALIGNOF_MMSGHDRX64);





#include <bits/msghdr-struct32.h>

/* struct __msghdrx32 */
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_control) == __OFFSET_MSGHDRX32_CONTROL);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_controllen) == __OFFSET_MSGHDRX32_CONTROLLEN);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_flags) == __OFFSET_MSGHDRX32_FLAGS);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_iov) == __OFFSET_MSGHDRX32_IOV);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_iovlen) == __OFFSET_MSGHDRX32_IOVLEN);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_name) == __OFFSET_MSGHDRX32_NAME);
STATIC_ASSERT(offsetof(struct __msghdrx32, msg_namelen) == __OFFSET_MSGHDRX32_NAMELEN);
STATIC_ASSERT(sizeof(struct __msghdrx32) == __SIZEOF_MSGHDRX32);
STATIC_ASSERT(alignof(struct __msghdrx32) == __ALIGNOF_MSGHDRX32);





#include <bits/msghdr-struct64.h>

/* struct __msghdrx64 */
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_control) == __OFFSET_MSGHDRX64_CONTROL);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_controllen) == __OFFSET_MSGHDRX64_CONTROLLEN);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_flags) == __OFFSET_MSGHDRX64_FLAGS);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_iov) == __OFFSET_MSGHDRX64_IOV);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_iovlen) == __OFFSET_MSGHDRX64_IOVLEN);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_name) == __OFFSET_MSGHDRX64_NAME);
STATIC_ASSERT(offsetof(struct __msghdrx64, msg_namelen) == __OFFSET_MSGHDRX64_NAMELEN);
STATIC_ASSERT(sizeof(struct __msghdrx64) == __SIZEOF_MSGHDRX64);
STATIC_ASSERT(alignof(struct __msghdrx64) == __ALIGNOF_MSGHDRX64);





#include <bits/rusage-struct32.h>

/* struct rusagex32 */
STATIC_ASSERT(offsetof(struct rusagex32, ru_idrss) == __OFFSET_RUSAGEX32_IDRSS);
STATIC_ASSERT(offsetof(struct rusagex32, ru_inblock) == __OFFSET_RUSAGEX32_INBLOCK);
STATIC_ASSERT(offsetof(struct rusagex32, ru_isrss) == __OFFSET_RUSAGEX32_ISRSS);
STATIC_ASSERT(offsetof(struct rusagex32, ru_ixrss) == __OFFSET_RUSAGEX32_IXRSS);
STATIC_ASSERT(offsetof(struct rusagex32, ru_majflt) == __OFFSET_RUSAGEX32_MAJFLT);
STATIC_ASSERT(offsetof(struct rusagex32, ru_maxrss) == __OFFSET_RUSAGEX32_MAXRSS);
STATIC_ASSERT(offsetof(struct rusagex32, ru_minflt) == __OFFSET_RUSAGEX32_MINFLT);
STATIC_ASSERT(offsetof(struct rusagex32, ru_msgrcv) == __OFFSET_RUSAGEX32_MSGRCV);
STATIC_ASSERT(offsetof(struct rusagex32, ru_msgsnd) == __OFFSET_RUSAGEX32_MSGSND);
STATIC_ASSERT(offsetof(struct rusagex32, ru_nivcsw) == __OFFSET_RUSAGEX32_NIVCSW);
STATIC_ASSERT(offsetof(struct rusagex32, ru_nsignals) == __OFFSET_RUSAGEX32_NSIGNALS);
STATIC_ASSERT(offsetof(struct rusagex32, ru_nswap) == __OFFSET_RUSAGEX32_NSWAP);
STATIC_ASSERT(offsetof(struct rusagex32, ru_nvcsw) == __OFFSET_RUSAGEX32_NVCSW);
STATIC_ASSERT(offsetof(struct rusagex32, ru_oublock) == __OFFSET_RUSAGEX32_OUBLOCK);
STATIC_ASSERT(offsetof(struct rusagex32, ru_stime) == __OFFSET_RUSAGEX32_STIME);
STATIC_ASSERT(offsetof(struct rusagex32, ru_utime) == __OFFSET_RUSAGEX32_UTIME);
STATIC_ASSERT(sizeof(struct rusagex32) == __SIZEOF_RUSAGEX32);
STATIC_ASSERT(alignof(struct rusagex32) == __ALIGNOF_RUSAGEX32);

/* struct rusagex32_64 */
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_idrss) == __OFFSET_RUSAGEX32_64_IDRSS);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_inblock) == __OFFSET_RUSAGEX32_64_INBLOCK);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_isrss) == __OFFSET_RUSAGEX32_64_ISRSS);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_ixrss) == __OFFSET_RUSAGEX32_64_IXRSS);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_majflt) == __OFFSET_RUSAGEX32_64_MAJFLT);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_maxrss) == __OFFSET_RUSAGEX32_64_MAXRSS);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_minflt) == __OFFSET_RUSAGEX32_64_MINFLT);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_msgrcv) == __OFFSET_RUSAGEX32_64_MSGRCV);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_msgsnd) == __OFFSET_RUSAGEX32_64_MSGSND);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_nivcsw) == __OFFSET_RUSAGEX32_64_NIVCSW);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_nsignals) == __OFFSET_RUSAGEX32_64_NSIGNALS);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_nswap) == __OFFSET_RUSAGEX32_64_NSWAP);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_nvcsw) == __OFFSET_RUSAGEX32_64_NVCSW);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_oublock) == __OFFSET_RUSAGEX32_64_OUBLOCK);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_stime) == __OFFSET_RUSAGEX32_64_STIME);
STATIC_ASSERT(offsetof(struct rusagex32_64, ru_utime) == __OFFSET_RUSAGEX32_64_UTIME);
STATIC_ASSERT(sizeof(struct rusagex32_64) == __SIZEOF_RUSAGEX32_64);
STATIC_ASSERT(alignof(struct rusagex32_64) == __ALIGNOF_RUSAGEX32_64);

/* struct __rusagex32_64_alt */
/* ... */





#include <bits/rusage-struct64.h>

/* struct rusagex64 */
STATIC_ASSERT(offsetof(struct rusagex64, ru_idrss) == __OFFSET_RUSAGEX64_IDRSS);
STATIC_ASSERT(offsetof(struct rusagex64, ru_inblock) == __OFFSET_RUSAGEX64_INBLOCK);
STATIC_ASSERT(offsetof(struct rusagex64, ru_isrss) == __OFFSET_RUSAGEX64_ISRSS);
STATIC_ASSERT(offsetof(struct rusagex64, ru_ixrss) == __OFFSET_RUSAGEX64_IXRSS);
STATIC_ASSERT(offsetof(struct rusagex64, ru_majflt) == __OFFSET_RUSAGEX64_MAJFLT);
STATIC_ASSERT(offsetof(struct rusagex64, ru_maxrss) == __OFFSET_RUSAGEX64_MAXRSS);
STATIC_ASSERT(offsetof(struct rusagex64, ru_minflt) == __OFFSET_RUSAGEX64_MINFLT);
STATIC_ASSERT(offsetof(struct rusagex64, ru_msgrcv) == __OFFSET_RUSAGEX64_MSGRCV);
STATIC_ASSERT(offsetof(struct rusagex64, ru_msgsnd) == __OFFSET_RUSAGEX64_MSGSND);
STATIC_ASSERT(offsetof(struct rusagex64, ru_nivcsw) == __OFFSET_RUSAGEX64_NIVCSW);
STATIC_ASSERT(offsetof(struct rusagex64, ru_nsignals) == __OFFSET_RUSAGEX64_NSIGNALS);
STATIC_ASSERT(offsetof(struct rusagex64, ru_nswap) == __OFFSET_RUSAGEX64_NSWAP);
STATIC_ASSERT(offsetof(struct rusagex64, ru_nvcsw) == __OFFSET_RUSAGEX64_NVCSW);
STATIC_ASSERT(offsetof(struct rusagex64, ru_oublock) == __OFFSET_RUSAGEX64_OUBLOCK);
STATIC_ASSERT(offsetof(struct rusagex64, ru_stime) == __OFFSET_RUSAGEX64_STIME);
STATIC_ASSERT(offsetof(struct rusagex64, ru_utime) == __OFFSET_RUSAGEX64_UTIME);
STATIC_ASSERT(sizeof(struct rusagex64) == __SIZEOF_RUSAGEX64);
STATIC_ASSERT(alignof(struct rusagex64) == __ALIGNOF_RUSAGEX64);

/* struct __rusagex64_alt */
/* ... */





#include <bits/sigaction-struct-cygwin.h>

/* struct __sigaction_cygwin */
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_flags) == __OFFSET_SIGACTION_CYGWIN_FLAGS);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_handler) == __OFFSET_SIGACTION_CYGWIN_HANDLER);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_mask) == __OFFSET_SIGACTION_CYGWIN_MASK);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_sigaction) == __OFFSET_SIGACTION_CYGWIN_SIGACTION);
STATIC_ASSERT(sizeof(struct __sigaction_cygwin) == __SIZEOF_SIGACTION_CYGWIN);
STATIC_ASSERT(alignof(struct __sigaction_cygwin) == __ALIGNOF_SIGACTION_CYGWIN);





#include <bits/sigaction-struct32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct __sigactionx32 */
STATIC_ASSERT(offsetof(struct __sigactionx32, sa_flags) == __OFFSET_SIGACTIONX32_FLAGS);
STATIC_ASSERT(offsetof(struct __sigactionx32, sa_handler) == __OFFSET_SIGACTIONX32_HANDLER);
STATIC_ASSERT(offsetof(struct __sigactionx32, sa_mask) == __OFFSET_SIGACTIONX32_MASK);
STATIC_ASSERT(offsetof(struct __sigactionx32, sa_restorer) == __OFFSET_SIGACTIONX32_RESTORER);
STATIC_ASSERT(offsetof(struct __sigactionx32, sa_sigaction) == __OFFSET_SIGACTIONX32_SIGACTION);
STATIC_ASSERT(sizeof(struct __sigactionx32) == __SIZEOF_SIGACTIONX32);
STATIC_ASSERT(alignof(struct __sigactionx32) == __ALIGNOF_SIGACTIONX32);





#include <bits/sigaction-struct64.h>

/* struct __sigactionx64 */
STATIC_ASSERT(offsetof(struct __sigactionx64, sa_flags) == __OFFSET_SIGACTIONX64_FLAGS);
STATIC_ASSERT(offsetof(struct __sigactionx64, sa_handler) == __OFFSET_SIGACTIONX64_HANDLER);
STATIC_ASSERT(offsetof(struct __sigactionx64, sa_mask) == __OFFSET_SIGACTIONX64_MASK);
STATIC_ASSERT(offsetof(struct __sigactionx64, sa_restorer) == __OFFSET_SIGACTIONX64_RESTORER);
STATIC_ASSERT(offsetof(struct __sigactionx64, sa_sigaction) == __OFFSET_SIGACTIONX64_SIGACTION);
STATIC_ASSERT(sizeof(struct __sigactionx64) == __SIZEOF_SIGACTIONX64);
STATIC_ASSERT(alignof(struct __sigactionx64) == __ALIGNOF_SIGACTIONX64);





#include <bits/sigevent32.h>

/* struct __sigeventx32 */
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_data) == __OFFSET_SIGEVENTX32_DATA);
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_un._data) == __OFFSET_SIGEVENTX32_DATA);
STATIC_ASSERT(offsetof(struct __sigeventx32, sigev_notify) == __OFFSET_SIGEVENTX32_NOTIFY);
STATIC_ASSERT(offsetof(struct __sigeventx32, sigev_notify_attributes) == __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct __sigeventx32, sigev_notify_function) == __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct __sigeventx32, sigev_signo) == __OFFSET_SIGEVENTX32_SIGNO);
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_tid) == __OFFSET_SIGEVENTX32_TID);
STATIC_ASSERT(offsetof(struct __sigeventx32, _sigev_un._tid) == __OFFSET_SIGEVENTX32_TID);
STATIC_ASSERT(offsetof(struct __sigeventx32, sigev_value) == __OFFSET_SIGEVENTX32_VALUE);
STATIC_ASSERT(sizeof(struct __sigeventx32) == __SIZEOF_SIGEVENTX32);





#include <bits/sigevent64.h>

/* struct __sigeventx64 */
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_data) == __OFFSET_SIGEVENTX64_DATA);
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_un._data) == __OFFSET_SIGEVENTX64_DATA);
STATIC_ASSERT(offsetof(struct __sigeventx64, sigev_notify) == __OFFSET_SIGEVENTX64_NOTIFY);
STATIC_ASSERT(offsetof(struct __sigeventx64, sigev_notify_attributes) == __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct __sigeventx64, sigev_notify_function) == __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct __sigeventx64, sigev_signo) == __OFFSET_SIGEVENTX64_SIGNO);
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_tid) == __OFFSET_SIGEVENTX64_TID);
STATIC_ASSERT(offsetof(struct __sigeventx64, _sigev_un._tid) == __OFFSET_SIGEVENTX64_TID);
STATIC_ASSERT(offsetof(struct __sigeventx64, sigev_value) == __OFFSET_SIGEVENTX64_VALUE);
STATIC_ASSERT(sizeof(struct __sigeventx64) == __SIZEOF_SIGEVENTX64);





#include <bits/siginfo-struct32.h>

/* struct __siginfox32_struct */
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_addr) == __OFFSET_SIGINFOX32_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFOX32_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_addr_lsb) == __OFFSET_SIGINFOX32_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFOX32_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_arch) == __OFFSET_SIGINFOX32_ARCH);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFOX32_ARCH);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_band) == __OFFSET_SIGINFOX32_BAND);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFOX32_BAND);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_call_addr) == __OFFSET_SIGINFOX32_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFOX32_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_code) == __OFFSET_SIGINFOX32_CODE);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _si_data) == __OFFSET_SIGINFOX32_DATA);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._data) == __OFFSET_SIGINFOX32_DATA);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_errno) == __OFFSET_SIGINFOX32_ERRNO);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_fd) == __OFFSET_SIGINFOX32_FD);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFOX32_FD);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_int) == __OFFSET_SIGINFOX32_INT);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFOX32_INT);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_lower) == __OFFSET_SIGINFOX32_LOWER);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFOX32_LOWER);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_overrun) == __OFFSET_SIGINFOX32_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFOX32_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, __sig_si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, __cld_si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFOX32_PID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_ptr) == __OFFSET_SIGINFOX32_PTR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFOX32_PTR);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_signo) == __OFFSET_SIGINFOX32_SIGNO);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_status) == __OFFSET_SIGINFOX32_STATUS);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFOX32_STATUS);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_stime) == __OFFSET_SIGINFOX32_STIME);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFOX32_STIME);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_syscall) == __OFFSET_SIGINFOX32_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFOX32_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_timerid) == __OFFSET_SIGINFOX32_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFOX32_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, __sig_si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, __cld_si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFOX32_UID);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_upper) == __OFFSET_SIGINFOX32_UPPER);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFOX32_UPPER);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_utime) == __OFFSET_SIGINFOX32_UTIME);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFOX32_UTIME);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, si_value) == __OFFSET_SIGINFOX32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, __sig_si_sigval) == __OFFSET_SIGINFOX32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFOX32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox32_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFOX32_VALUE);
STATIC_ASSERT(sizeof(struct __siginfox32_struct) == __SIZEOF_SIGINFOX32);





#include <bits/siginfo-struct64.h>

/* struct __siginfox64_struct */
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_addr) == __OFFSET_SIGINFOX64_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFOX64_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_addr_lsb) == __OFFSET_SIGINFOX64_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFOX64_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_arch) == __OFFSET_SIGINFOX64_ARCH);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFOX64_ARCH);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_band) == __OFFSET_SIGINFOX64_BAND);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFOX64_BAND);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_call_addr) == __OFFSET_SIGINFOX64_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFOX64_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_code) == __OFFSET_SIGINFOX64_CODE);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _si_data) == __OFFSET_SIGINFOX64_DATA);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._data) == __OFFSET_SIGINFOX64_DATA);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_errno) == __OFFSET_SIGINFOX64_ERRNO);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_fd) == __OFFSET_SIGINFOX64_FD);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFOX64_FD);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_int) == __OFFSET_SIGINFOX64_INT);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFOX64_INT);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_lower) == __OFFSET_SIGINFOX64_LOWER);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFOX64_LOWER);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_overrun) == __OFFSET_SIGINFOX64_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFOX64_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, __sig_si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, __cld_si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFOX64_PID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_ptr) == __OFFSET_SIGINFOX64_PTR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFOX64_PTR);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_signo) == __OFFSET_SIGINFOX64_SIGNO);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_status) == __OFFSET_SIGINFOX64_STATUS);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFOX64_STATUS);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_stime) == __OFFSET_SIGINFOX64_STIME);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFOX64_STIME);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_syscall) == __OFFSET_SIGINFOX64_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFOX64_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_timerid) == __OFFSET_SIGINFOX64_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFOX64_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, __sig_si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, __cld_si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFOX64_UID);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_upper) == __OFFSET_SIGINFOX64_UPPER);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFOX64_UPPER);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_utime) == __OFFSET_SIGINFOX64_UTIME);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFOX64_UTIME);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, si_value) == __OFFSET_SIGINFOX64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, __sig_si_sigval) == __OFFSET_SIGINFOX64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFOX64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfox64_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFOX64_VALUE);
STATIC_ASSERT(sizeof(struct __siginfox64_struct) == __SIZEOF_SIGINFOX64);





#include <bits/sigstack32.h>

/* struct __sigstackx32 */
STATIC_ASSERT(offsetof(struct __sigstackx32, ss_sp) == __OFFSET_SIGSTACKX32_SP);
STATIC_ASSERT(offsetof(struct __sigstackx32, ss_onstack) == __OFFSET_SIGSTACKX32_ONSTACK);
STATIC_ASSERT(sizeof(struct __sigstackx32) == __SIZEOF_SIGSTACKX32);

/* struct __sigaltstackx32 */
STATIC_ASSERT(offsetof(struct __sigaltstackx32, ss_flags) == __OFFSET_SIGALTSTACKX32_FLAGS);
STATIC_ASSERT(offsetof(struct __sigaltstackx32, ss_size) == __OFFSET_SIGALTSTACKX32_SIZE);
STATIC_ASSERT(offsetof(struct __sigaltstackx32, ss_sp) == __OFFSET_SIGALTSTACKX32_SP);
STATIC_ASSERT(sizeof(struct __sigaltstackx32) == __SIZEOF_SIGALTSTACKX32);





#include <bits/sigstack64.h>

/* struct __sigstackx64 */
STATIC_ASSERT(offsetof(struct __sigstackx64, ss_sp) == __OFFSET_SIGSTACKX64_SP);
STATIC_ASSERT(offsetof(struct __sigstackx64, ss_onstack) == __OFFSET_SIGSTACKX64_ONSTACK);

/* struct __sigaltstackx64 */
STATIC_ASSERT(offsetof(struct __sigaltstackx64, ss_flags) == __OFFSET_SIGALTSTACKX64_FLAGS);
STATIC_ASSERT(offsetof(struct __sigaltstackx64, ss_size) == __OFFSET_SIGALTSTACKX64_SIZE);
STATIC_ASSERT(offsetof(struct __sigaltstackx64, ss_sp) == __OFFSET_SIGALTSTACKX64_SP);





#include <bits/sigval32.h>

/* union __sigvalx32 */
STATIC_ASSERT(sizeof(union __sigvalx32) == __SIZEOF_SIGVALX32);
STATIC_ASSERT(alignof(union __sigvalx32) == __ALIGNOF_SIGVALX32);





#include <bits/sigval64.h>

/* union __sigvalx64 */
STATIC_ASSERT(sizeof(union __sigvalx64) == __SIZEOF_SIGVALX64);
STATIC_ASSERT(alignof(union __sigvalx64) == __ALIGNOF_SIGVALX64);





#include <bits/stat-kos32.h>

/* struct __kos_statx32 */
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atime) == __OFFSET_KOS_STATX32_ATIME);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atime32) == __OFFSET_KOS_STATX32_ATIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atime64) == __OFFSET_KOS_STATX32_ATIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimensec) == __OFFSET_KOS_STATX32_ATIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimensec32) == __OFFSET_KOS_STATX32_ATIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimensec64) == __OFFSET_KOS_STATX32_ATIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimespec) == __OFFSET_KOS_STATX32_ATIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimespec32) == __OFFSET_KOS_STATX32_ATIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_atimespec64) == __OFFSET_KOS_STATX32_ATIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_blksize) == __OFFSET_KOS_STATX32_BLKSIZE);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_blocks) == __OFFSET_KOS_STATX32_BLOCKS);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctime) == __OFFSET_KOS_STATX32_CTIME);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctime32) == __OFFSET_KOS_STATX32_CTIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctime64) == __OFFSET_KOS_STATX32_CTIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimensec) == __OFFSET_KOS_STATX32_CTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimensec32) == __OFFSET_KOS_STATX32_CTIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimensec64) == __OFFSET_KOS_STATX32_CTIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimespec) == __OFFSET_KOS_STATX32_CTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimespec32) == __OFFSET_KOS_STATX32_CTIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ctimespec64) == __OFFSET_KOS_STATX32_CTIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_dev) == __OFFSET_KOS_STATX32_DEV);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_gid) == __OFFSET_KOS_STATX32_GID);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_ino) == __OFFSET_KOS_STATX32_INO);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mode) == __OFFSET_KOS_STATX32_MODE);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtime) == __OFFSET_KOS_STATX32_MTIME);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtime32) == __OFFSET_KOS_STATX32_MTIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtime64) == __OFFSET_KOS_STATX32_MTIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimensec) == __OFFSET_KOS_STATX32_MTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimensec32) == __OFFSET_KOS_STATX32_MTIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimensec64) == __OFFSET_KOS_STATX32_MTIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimespec) == __OFFSET_KOS_STATX32_MTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimespec32) == __OFFSET_KOS_STATX32_MTIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_mtimespec64) == __OFFSET_KOS_STATX32_MTIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_nlink) == __OFFSET_KOS_STATX32_NLINK);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_rdev) == __OFFSET_KOS_STATX32_RDEV);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_size) == __OFFSET_KOS_STATX32_SIZE);
STATIC_ASSERT(offsetof(struct __kos_statx32, st_uid) == __OFFSET_KOS_STATX32_UID);
STATIC_ASSERT(sizeof(struct __kos_statx32) == __SIZEOF_KOS_STATX32);

/* struct __kos_statx32_alias64 */
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atime) == __OFFSET_KOS_STATX32_ATIME);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atime32) == __OFFSET_KOS_STATX32_ATIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atime64) == __OFFSET_KOS_STATX32_ATIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimensec) == __OFFSET_KOS_STATX32_ATIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimensec32) == __OFFSET_KOS_STATX32_ATIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimensec64) == __OFFSET_KOS_STATX32_ATIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimespec) == __OFFSET_KOS_STATX32_ATIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimespec32) == __OFFSET_KOS_STATX32_ATIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_atimespec64) == __OFFSET_KOS_STATX32_ATIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_blksize) == __OFFSET_KOS_STATX32_BLKSIZE);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_blocks) == __OFFSET_KOS_STATX32_BLOCKS);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctime) == __OFFSET_KOS_STATX32_CTIME);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctime32) == __OFFSET_KOS_STATX32_CTIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctime64) == __OFFSET_KOS_STATX32_CTIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimensec) == __OFFSET_KOS_STATX32_CTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimensec32) == __OFFSET_KOS_STATX32_CTIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimensec64) == __OFFSET_KOS_STATX32_CTIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimespec) == __OFFSET_KOS_STATX32_CTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimespec32) == __OFFSET_KOS_STATX32_CTIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ctimespec64) == __OFFSET_KOS_STATX32_CTIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_dev) == __OFFSET_KOS_STATX32_DEV);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_gid) == __OFFSET_KOS_STATX32_GID);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_ino) == __OFFSET_KOS_STATX32_INO);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mode) == __OFFSET_KOS_STATX32_MODE);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtime) == __OFFSET_KOS_STATX32_MTIME);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtime32) == __OFFSET_KOS_STATX32_MTIME32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtime64) == __OFFSET_KOS_STATX32_MTIME64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimensec) == __OFFSET_KOS_STATX32_MTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimensec32) == __OFFSET_KOS_STATX32_MTIMENSEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimensec64) == __OFFSET_KOS_STATX32_MTIMENSEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimespec) == __OFFSET_KOS_STATX32_MTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimespec32) == __OFFSET_KOS_STATX32_MTIMESPEC32);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_mtimespec64) == __OFFSET_KOS_STATX32_MTIMESPEC64);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_nlink) == __OFFSET_KOS_STATX32_NLINK);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_rdev) == __OFFSET_KOS_STATX32_RDEV);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_size) == __OFFSET_KOS_STATX32_SIZE);
STATIC_ASSERT(offsetof(struct __kos_statx32_alias64, st_uid) == __OFFSET_KOS_STATX32_UID);
STATIC_ASSERT(sizeof(struct __kos_statx32_alias64) == __SIZEOF_KOS_STATX32);





#include <bits/stat-kos64.h>

/* struct __kos_statx64 */
STATIC_ASSERT(offsetof(struct __kos_statx64, st_atime) == __OFFSET_KOS_STATX64_ATIME);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_atimensec) == __OFFSET_KOS_STATX64_ATIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_atimespec) == __OFFSET_KOS_STATX64_ATIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_blksize) == __OFFSET_KOS_STATX64_BLKSIZE);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_blocks) == __OFFSET_KOS_STATX64_BLOCKS);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_ctime) == __OFFSET_KOS_STATX64_CTIME);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_ctimensec) == __OFFSET_KOS_STATX64_CTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_ctimespec) == __OFFSET_KOS_STATX64_CTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_dev) == __OFFSET_KOS_STATX64_DEV);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_gid) == __OFFSET_KOS_STATX64_GID);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_ino) == __OFFSET_KOS_STATX64_INO);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_mode) == __OFFSET_KOS_STATX64_MODE);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_mtime) == __OFFSET_KOS_STATX64_MTIME);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_mtimensec) == __OFFSET_KOS_STATX64_MTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_mtimespec) == __OFFSET_KOS_STATX64_MTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_nlink) == __OFFSET_KOS_STATX64_NLINK);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_rdev) == __OFFSET_KOS_STATX64_RDEV);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_size) == __OFFSET_KOS_STATX64_SIZE);
STATIC_ASSERT(offsetof(struct __kos_statx64, st_uid) == __OFFSET_KOS_STATX64_UID);
STATIC_ASSERT(sizeof(struct __kos_statx64) == __SIZEOF_KOS_STATX64);

/* struct __kos_statx64_alias64 */
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_atime) == __OFFSET_KOS_STATX64_ATIME);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_atimensec) == __OFFSET_KOS_STATX64_ATIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_atimespec) == __OFFSET_KOS_STATX64_ATIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_blksize) == __OFFSET_KOS_STATX64_BLKSIZE);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_blocks) == __OFFSET_KOS_STATX64_BLOCKS);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_ctime) == __OFFSET_KOS_STATX64_CTIME);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_ctimensec) == __OFFSET_KOS_STATX64_CTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_ctimespec) == __OFFSET_KOS_STATX64_CTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_dev) == __OFFSET_KOS_STATX64_DEV);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_gid) == __OFFSET_KOS_STATX64_GID);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_ino) == __OFFSET_KOS_STATX64_INO);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_mode) == __OFFSET_KOS_STATX64_MODE);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_mtime) == __OFFSET_KOS_STATX64_MTIME);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_mtimensec) == __OFFSET_KOS_STATX64_MTIMENSEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_mtimespec) == __OFFSET_KOS_STATX64_MTIMESPEC);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_nlink) == __OFFSET_KOS_STATX64_NLINK);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_rdev) == __OFFSET_KOS_STATX64_RDEV);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_size) == __OFFSET_KOS_STATX64_SIZE);
STATIC_ASSERT(offsetof(struct __kos_statx64_alias64, st_uid) == __OFFSET_KOS_STATX64_UID);
STATIC_ASSERT(sizeof(struct __kos_statx64_alias64) == __SIZEOF_KOS_STATX64);





#include <bits/statfs32.h>

/* struct statfsx32 */
STATIC_ASSERT(offsetof(struct statfsx32, f_bavail) == __OFFSET_STATFSX32_BAVAIL);
STATIC_ASSERT(offsetof(struct statfsx32, f_bfree) == __OFFSET_STATFSX32_BFREE);
STATIC_ASSERT(offsetof(struct statfsx32, f_blocks) == __OFFSET_STATFSX32_BLOCKS);
STATIC_ASSERT(offsetof(struct statfsx32, f_bsize) == __OFFSET_STATFSX32_BSIZE);
STATIC_ASSERT(offsetof(struct statfsx32, f_ffree) == __OFFSET_STATFSX32_FFREE);
STATIC_ASSERT(offsetof(struct statfsx32, f_files) == __OFFSET_STATFSX32_FILES);
STATIC_ASSERT(offsetof(struct statfsx32, f_flags) == __OFFSET_STATFSX32_FLAGS);
STATIC_ASSERT(offsetof(struct statfsx32, f_frsize) == __OFFSET_STATFSX32_FRSIZE);
STATIC_ASSERT(offsetof(struct statfsx32, f_fsid) == __OFFSET_STATFSX32_FSID);
STATIC_ASSERT(offsetof(struct statfsx32, f_namelen) == __OFFSET_STATFSX32_NAMELEN);
STATIC_ASSERT(offsetof(struct statfsx32, f_spare) == __OFFSET_STATFSX32_SPARE);
STATIC_ASSERT(offsetof(struct statfsx32, f_type) == __OFFSET_STATFSX32_TYPE);
STATIC_ASSERT(sizeof(struct statfsx32) == __SIZEOF_STATFSX32);
STATIC_ASSERT(alignof(struct statfsx32) == __ALIGNOF_STATFSX32);

/* struct statfsx32_64 */
STATIC_ASSERT(offsetof(struct statfsx32_64, f_bavail) == __OFFSET_STATFSX32_64_BAVAIL);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_bfree) == __OFFSET_STATFSX32_64_BFREE);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_blocks) == __OFFSET_STATFSX32_64_BLOCKS);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_bsize) == __OFFSET_STATFSX32_64_BSIZE);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_ffree) == __OFFSET_STATFSX32_64_FFREE);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_files) == __OFFSET_STATFSX32_64_FILES);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_flags) == __OFFSET_STATFSX32_64_FLAGS);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_frsize) == __OFFSET_STATFSX32_64_FRSIZE);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_fsid) == __OFFSET_STATFSX32_64_FSID);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_namelen) == __OFFSET_STATFSX32_64_NAMELEN);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_spare) == __OFFSET_STATFSX32_64_SPARE);
STATIC_ASSERT(offsetof(struct statfsx32_64, f_type) == __OFFSET_STATFSX32_64_TYPE);
STATIC_ASSERT(sizeof(struct statfsx32_64) == __SIZEOF_STATFSX32_64);
STATIC_ASSERT(alignof(struct statfsx32_64) == __ALIGNOF_STATFSX32_64);

/* struct __statfsx32_64_alt */
/* ... */





#include <bits/statfs64.h>

/* struct statfsx64 */
STATIC_ASSERT(offsetof(struct statfsx64, f_bavail) == __OFFSET_STATFSX64_BAVAIL);
STATIC_ASSERT(offsetof(struct statfsx64, f_bfree) == __OFFSET_STATFSX64_BFREE);
STATIC_ASSERT(offsetof(struct statfsx64, f_blocks) == __OFFSET_STATFSX64_BLOCKS);
STATIC_ASSERT(offsetof(struct statfsx64, f_bsize) == __OFFSET_STATFSX64_BSIZE);
STATIC_ASSERT(offsetof(struct statfsx64, f_ffree) == __OFFSET_STATFSX64_FFREE);
STATIC_ASSERT(offsetof(struct statfsx64, f_files) == __OFFSET_STATFSX64_FILES);
STATIC_ASSERT(offsetof(struct statfsx64, f_flags) == __OFFSET_STATFSX64_FLAGS);
STATIC_ASSERT(offsetof(struct statfsx64, f_frsize) == __OFFSET_STATFSX64_FRSIZE);
STATIC_ASSERT(offsetof(struct statfsx64, f_fsid) == __OFFSET_STATFSX64_FSID);
STATIC_ASSERT(offsetof(struct statfsx64, f_namelen) == __OFFSET_STATFSX64_NAMELEN);
STATIC_ASSERT(offsetof(struct statfsx64, f_spare) == __OFFSET_STATFSX64_SPARE);
STATIC_ASSERT(offsetof(struct statfsx64, f_type) == __OFFSET_STATFSX64_TYPE);
STATIC_ASSERT(sizeof(struct statfsx64) == __SIZEOF_STATFSX64);
STATIC_ASSERT(alignof(struct statfsx64) == __ALIGNOF_STATFSX64);

/* struct __statfsx64_alt */
/* ... */





#include <bits/timeb32.h>

/* struct timebx32 */
STATIC_ASSERT(offsetof(struct timebx32, dstflag) == __OFFSET_TIMEBX32_DSTFLAG);
STATIC_ASSERT(offsetof(struct timebx32, millitm) == __OFFSET_TIMEBX32_MILLITM);
STATIC_ASSERT(offsetof(struct timebx32, time) == __OFFSET_TIMEBX32_TIME);
STATIC_ASSERT(offsetof(struct timebx32, timezone) == __OFFSET_TIMEBX32_TIMEZONE);
STATIC_ASSERT(sizeof(struct timebx32) == __SIZEOF_TIMEBX32);
STATIC_ASSERT(alignof(struct timebx32) == __ALIGNOF_TIMEBX32);

/* struct timebx32_64 */
STATIC_ASSERT(offsetof(struct timebx32_64, dstflag) == __OFFSET_TIMEBX32_64_DSTFLAG);
STATIC_ASSERT(offsetof(struct timebx32_64, millitm) == __OFFSET_TIMEBX32_64_MILLITM);
STATIC_ASSERT(offsetof(struct timebx32_64, time) == __OFFSET_TIMEBX32_64_TIME);
STATIC_ASSERT(offsetof(struct timebx32_64, timezone) == __OFFSET_TIMEBX32_64_TIMEZONE);
STATIC_ASSERT(sizeof(struct timebx32_64) == __SIZEOF_TIMEBX32_64);
STATIC_ASSERT(alignof(struct timebx32_64) == __ALIGNOF_TIMEBX32_64);

/* struct __timebx32_64_alt */
/* ... */





#include <bits/timeb64.h>

/* struct timebx64 */
STATIC_ASSERT(offsetof(struct timebx64, dstflag) == __OFFSET_TIMEBX64_DSTFLAG);
STATIC_ASSERT(offsetof(struct timebx64, millitm) == __OFFSET_TIMEBX64_MILLITM);
STATIC_ASSERT(offsetof(struct timebx64, time) == __OFFSET_TIMEBX64_TIME);
STATIC_ASSERT(offsetof(struct timebx64, timezone) == __OFFSET_TIMEBX64_TIMEZONE);
STATIC_ASSERT(sizeof(struct timebx64) == __SIZEOF_TIMEBX64);
STATIC_ASSERT(alignof(struct timebx64) == __ALIGNOF_TIMEBX64);

/* struct __timebx64_alt */
/* ... */





#include <bits/timespec32.h>

/* struct timespecx32 */
STATIC_ASSERT(offsetof(struct timespecx32, tv_sec) == __OFFSET_TIMESPECX32_SEC);
STATIC_ASSERT(offsetof(struct timespecx32, tv_nsec) == __OFFSET_TIMESPECX32_NSEC);
STATIC_ASSERT(sizeof(struct timespecx32) == __SIZEOF_TIMESPECX32);
STATIC_ASSERT(alignof(struct timespecx32) == __ALIGNOF_TIMESPECX32);

/* struct timespecx32_64 */
STATIC_ASSERT(offsetof(struct timespecx32_64, tv_sec) == __OFFSET_TIMESPECX32_64_SEC);
STATIC_ASSERT(offsetof(struct timespecx32_64, tv_nsec) == __OFFSET_TIMESPECX32_64_NSEC);
STATIC_ASSERT(sizeof(struct timespecx32_64) == __SIZEOF_TIMESPECX32_64);
STATIC_ASSERT(alignof(struct timespecx32_64) == __ALIGNOF_TIMESPECX32_64);

/* struct __timespecx32_64_alt */
/* ... */





#include <bits/timespec64.h>

/* struct timespecx64 */
STATIC_ASSERT(offsetof(struct timespecx64, tv_sec) == __OFFSET_TIMESPECX64_SEC);
STATIC_ASSERT(offsetof(struct timespecx64, tv_nsec) == __OFFSET_TIMESPECX64_NSEC);
STATIC_ASSERT(sizeof(struct timespecx64) == __SIZEOF_TIMESPECX64);
STATIC_ASSERT(alignof(struct timespecx64) == __ALIGNOF_TIMESPECX64);

/* struct __timespecx64_alt */
/* ... */





#include <bits/timeval32.h>

/* struct timevalx32 */
STATIC_ASSERT(offsetof(struct timevalx32, tv_usec) == __OFFSET_TIMEVALX32_USEC);
STATIC_ASSERT(offsetof(struct timevalx32, tv_sec) == __OFFSET_TIMEVALX32_SEC);
STATIC_ASSERT(sizeof(struct timevalx32) == __SIZEOF_TIMEVALX32);
STATIC_ASSERT(alignof(struct timevalx32) == __ALIGNOF_TIMEVALX32);

/* struct timevalx32_64 */
STATIC_ASSERT(offsetof(struct timevalx32_64, tv_usec) == __OFFSET_TIMEVALX32_64_USEC);
STATIC_ASSERT(offsetof(struct timevalx32_64, tv_sec) == __OFFSET_TIMEVALX32_64_SEC);
STATIC_ASSERT(sizeof(struct timevalx32_64) == __SIZEOF_TIMEVALX32_64);
STATIC_ASSERT(alignof(struct timevalx32_64) == __ALIGNOF_TIMEVALX32_64);

/* struct __timevalx32_64_alt */
/* ... */





#include <bits/timeval64.h>

/* struct timevalx64 */
STATIC_ASSERT(offsetof(struct timevalx64, tv_usec) == __OFFSET_TIMEVALX64_USEC);
STATIC_ASSERT(offsetof(struct timevalx64, tv_sec) == __OFFSET_TIMEVALX64_SEC);
STATIC_ASSERT(sizeof(struct timevalx64) == __SIZEOF_TIMEVALX64);
STATIC_ASSERT(alignof(struct timevalx64) == __ALIGNOF_TIMEVALX64);

/* struct __timevalx64_alt */
/* ... */





#include <bits/utimbuf32.h>

/* struct utimbufx32 */
STATIC_ASSERT(offsetof(struct utimbufx32, modtime) == __OFFSET_UTIMBUFX32_MODTIME);
STATIC_ASSERT(offsetof(struct utimbufx32, actime) == __OFFSET_UTIMBUFX32_ACTIME);
STATIC_ASSERT(sizeof(struct utimbufx32) == __SIZEOF_UTIMBUFX32);
STATIC_ASSERT(alignof(struct utimbufx32) == __ALIGNOF_UTIMBUFX32);

/* struct utimbufx32_64 */
STATIC_ASSERT(offsetof(struct utimbufx32_64, modtime) == __OFFSET_UTIMBUFX32_64_MODTIME);
STATIC_ASSERT(offsetof(struct utimbufx32_64, actime) == __OFFSET_UTIMBUFX32_64_ACTIME);
STATIC_ASSERT(sizeof(struct utimbufx32_64) == __SIZEOF_UTIMBUFX32_64);
STATIC_ASSERT(alignof(struct utimbufx32_64) == __ALIGNOF_UTIMBUFX32_64);

/* struct __utimbufx32_64_alt */
/* ... */





#include <bits/utimbuf64.h>

/* struct utimbufx64 */
STATIC_ASSERT(offsetof(struct utimbufx64, modtime) == __OFFSET_UTIMBUFX64_MODTIME);
STATIC_ASSERT(offsetof(struct utimbufx64, actime) == __OFFSET_UTIMBUFX64_ACTIME);
STATIC_ASSERT(sizeof(struct utimbufx64) == __SIZEOF_UTIMBUFX64);
STATIC_ASSERT(alignof(struct utimbufx64) == __ALIGNOF_UTIMBUFX64);

/* struct __utimbufx64_alt */
/* ... */





#include <bits/va_list-struct32.h>

/* struct i386_va_list_struct */
/* ... */





#include <bits/va_list-struct64.h>

/* struct x86_64_va_list_reg_save_area */
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_r8) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R8);
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_r9) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9);
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_rcx) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RCX);
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_rdi) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDI);
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_rdx) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX);
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_rsi) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RSI);
STATIC_ASSERT(sizeof(struct x86_64_va_list_reg_save_area) == SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA);

/* struct x86_64_va_list_struct */
STATIC_ASSERT(offsetof(struct x86_64_va_list_struct, vl_fp_offset) == OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET);
STATIC_ASSERT(offsetof(struct x86_64_va_list_struct, vl_gp_offset) == OFFSET_X86_64_VA_LIST_STRUCT_GP_OFFSET);
STATIC_ASSERT(offsetof(struct x86_64_va_list_struct, vl_overflow_arg_area) == OFFSET_X86_64_VA_LIST_STRUCT_OVERFLOW_ARG_AREA);
STATIC_ASSERT(offsetof(struct x86_64_va_list_struct, vl_reg_save_area) == OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA);
STATIC_ASSERT(sizeof(struct x86_64_va_list_struct) == SIZEOF_X86_64_VA_LIST_STRUCT);





#include <kos/bits/debugtrap32.h>

/* struct debugtrap_reason32 */
STATIC_ASSERT(offsetof(struct debugtrap_reason32, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON32_INTARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason32, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON32_PTRARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason32, dtr_reason) == __OFFSET_DEBUGTRAP_REASON32_REASON);
STATIC_ASSERT(offsetof(struct debugtrap_reason32, dtr_signo) == __OFFSET_DEBUGTRAP_REASON32_SIGNO);
STATIC_ASSERT(offsetof(struct debugtrap_reason32, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON32_STRARG);
STATIC_ASSERT(sizeof(struct debugtrap_reason32) == __SIZEOF_DEBUGTRAP_REASON32);





#include <kos/bits/debugtrap64.h>

/* struct debugtrap_reason64 */
STATIC_ASSERT(offsetof(struct debugtrap_reason64, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON64_INTARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason64, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON64_PTRARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason64, dtr_reason) == __OFFSET_DEBUGTRAP_REASON64_REASON);
STATIC_ASSERT(offsetof(struct debugtrap_reason64, dtr_signo) == __OFFSET_DEBUGTRAP_REASON64_SIGNO);
STATIC_ASSERT(offsetof(struct debugtrap_reason64, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON64_STRARG);
STATIC_ASSERT(sizeof(struct debugtrap_reason64) == __SIZEOF_DEBUGTRAP_REASON64);





#include <kos/bits/exception_data32.h>

/* struct exception_data32 */
STATIC_ASSERT(offsetof(struct exception_data32, e_class) == __OFFSET_EXCEPTION_DATA32_CLASS);
STATIC_ASSERT(offsetof(struct exception_data32, e_code) == __OFFSET_EXCEPTION_DATA32_CODE);
STATIC_ASSERT(offsetof(struct exception_data32, e_faultaddr) == __OFFSET_EXCEPTION_DATA32_FAULTADDR);
STATIC_ASSERT(offsetof(struct exception_data32, e_pointers) == __OFFSET_EXCEPTION_DATA32_POINTERS);
STATIC_ASSERT(offsetof(struct exception_data32, e_subclass) == __OFFSET_EXCEPTION_DATA32_SUBCLASS);
STATIC_ASSERT(sizeof(struct exception_data32) == __SIZEOF_EXCEPTION_DATA32);





#include <kos/bits/exception_data64.h>

/* struct exception_data64 */
STATIC_ASSERT(offsetof(struct exception_data64, e_class) == __OFFSET_EXCEPTION_DATA64_CLASS);
STATIC_ASSERT(offsetof(struct exception_data64, e_code) == __OFFSET_EXCEPTION_DATA64_CODE);
STATIC_ASSERT(offsetof(struct exception_data64, e_faultaddr) == __OFFSET_EXCEPTION_DATA64_FAULTADDR);
STATIC_ASSERT(offsetof(struct exception_data64, e_pointers) == __OFFSET_EXCEPTION_DATA64_POINTERS);
STATIC_ASSERT(offsetof(struct exception_data64, e_subclass) == __OFFSET_EXCEPTION_DATA64_SUBCLASS);
STATIC_ASSERT(sizeof(struct exception_data64) == __SIZEOF_EXCEPTION_DATA64);





#include <kos/bits/ukern-struct32.h>

/* struct userkern32 */
STATIC_ASSERT(offsetof(struct userkern32, uk_base) == OFFSET_USERKERN32_BASE);
STATIC_ASSERT(offsetof(struct userkern32, uk_egid) == OFFSET_USERKERN32_EGID);
STATIC_ASSERT(offsetof(struct userkern32, uk_euid) == OFFSET_USERKERN32_EUID);
STATIC_ASSERT(offsetof(struct userkern32, uk_gid) == OFFSET_USERKERN32_GID);
STATIC_ASSERT(offsetof(struct userkern32, uk_pgid) == OFFSET_USERKERN32_PGID);
STATIC_ASSERT(offsetof(struct userkern32, uk_pid) == OFFSET_USERKERN32_PID);
STATIC_ASSERT(offsetof(struct userkern32, uk_ppid) == OFFSET_USERKERN32_PPID);
STATIC_ASSERT(offsetof(struct userkern32, uk_regs) == OFFSET_USERKERN32_REGS);
STATIC_ASSERT(offsetof(struct userkern32, uk_sfpu) == OFFSET_USERKERN32_SFPU);
STATIC_ASSERT(offsetof(struct userkern32, uk_sgid) == OFFSET_USERKERN32_SGID);
STATIC_ASSERT(offsetof(struct userkern32, uk_sid) == OFFSET_USERKERN32_SID);
STATIC_ASSERT(offsetof(struct userkern32, uk_suid) == OFFSET_USERKERN32_SUID);
STATIC_ASSERT(offsetof(struct userkern32, uk_tid) == OFFSET_USERKERN32_TID);
STATIC_ASSERT(offsetof(struct userkern32, uk_uid) == OFFSET_USERKERN32_UID);
STATIC_ASSERT(offsetof(struct userkern32, uk_xfpu) == OFFSET_USERKERN32_XFPU);
STATIC_ASSERT(sizeof(struct userkern32) == SIZEOF_USERKERN32);





#include <kos/bits/ukern-struct64.h>

/* struct userkern64 */
STATIC_ASSERT(offsetof(struct userkern64, uk_base) == OFFSET_USERKERN64_BASE);
STATIC_ASSERT(offsetof(struct userkern64, uk_egid) == OFFSET_USERKERN64_EGID);
STATIC_ASSERT(offsetof(struct userkern64, uk_euid) == OFFSET_USERKERN64_EUID);
STATIC_ASSERT(offsetof(struct userkern64, uk_gid) == OFFSET_USERKERN64_GID);
STATIC_ASSERT(offsetof(struct userkern64, uk_pgid) == OFFSET_USERKERN64_PGID);
STATIC_ASSERT(offsetof(struct userkern64, uk_pid) == OFFSET_USERKERN64_PID);
STATIC_ASSERT(offsetof(struct userkern64, uk_ppid) == OFFSET_USERKERN64_PPID);
STATIC_ASSERT(offsetof(struct userkern64, uk_regs) == OFFSET_USERKERN64_REGS);
STATIC_ASSERT(offsetof(struct userkern64, uk_sfpu) == OFFSET_USERKERN64_SFPU);
STATIC_ASSERT(offsetof(struct userkern64, uk_sgid) == OFFSET_USERKERN64_SGID);
STATIC_ASSERT(offsetof(struct userkern64, uk_sid) == OFFSET_USERKERN64_SID);
STATIC_ASSERT(offsetof(struct userkern64, uk_suid) == OFFSET_USERKERN64_SUID);
STATIC_ASSERT(offsetof(struct userkern64, uk_tid) == OFFSET_USERKERN64_TID);
STATIC_ASSERT(offsetof(struct userkern64, uk_uid) == OFFSET_USERKERN64_UID);
STATIC_ASSERT(offsetof(struct userkern64, uk_xfpu) == OFFSET_USERKERN64_XFPU);
STATIC_ASSERT(sizeof(struct userkern64) == SIZEOF_USERKERN64);





#include <kos/bits/spawn-action32.h>

/* struct spawn_actionx32 */
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_closerange.sa_hifd) == __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_HIFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_closerange.sa_lofd) == __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_LOFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_close.sa_fd) == __OFFSET_SPAWN_ACTIONX32_CLOSE_FD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_dup2.sa_newfd) == __OFFSET_SPAWN_ACTIONX32_DUP2_NEWFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_dup2.sa_oldfd) == __OFFSET_SPAWN_ACTIONX32_DUP2_OLDFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_fsmode.sa_flag) == __OFFSET_SPAWN_ACTIONX32_FSMODE_FLAG);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_fsmode.sa_mask) == __OFFSET_SPAWN_ACTIONX32_FSMODE_MASK);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_openat.sa_dfd) == __OFFSET_SPAWN_ACTIONX32_OPENAT_DFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_openat.sa_fd) == __OFFSET_SPAWN_ACTIONX32_OPENAT_FD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_openat.sa_filename) == __OFFSET_SPAWN_ACTIONX32_OPENAT_FILENAME);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_openat.sa_mode) == __OFFSET_SPAWN_ACTIONX32_OPENAT_MODE);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_openat.sa_oflags) == __OFFSET_SPAWN_ACTIONX32_OPENAT_OFLAGS);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sched_setparam.sa_param) == __OFFSET_SPAWN_ACTIONX32_SCHED_SETPARAM_PARAM);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sched_setscheduler.sa_param) == __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_PARAM);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sched_setscheduler.sa_policy) == __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_POLICY);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setfsgid.sa_fsgid) == __OFFSET_SPAWN_ACTIONX32_SETFSGID_FSGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setfsuid.sa_fsuid) == __OFFSET_SPAWN_ACTIONX32_SETFSUID_FSUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setgid.sa_gid) == __OFFSET_SPAWN_ACTIONX32_SETGID_GID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setgroups.sa_gcnt) == __OFFSET_SPAWN_ACTIONX32_SETGROUPS_GCNT);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setgroups.sa_gvec) == __OFFSET_SPAWN_ACTIONX32_SETGROUPS_GVEC);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setpgid.sa_pid) == __OFFSET_SPAWN_ACTIONX32_SETPGID_PID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setregid.sa_egid) == __OFFSET_SPAWN_ACTIONX32_SETREGID_EGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setregid.sa_rgid) == __OFFSET_SPAWN_ACTIONX32_SETREGID_RGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresgid.sa_egid) == __OFFSET_SPAWN_ACTIONX32_SETRESGID_EGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresgid.sa_rgid) == __OFFSET_SPAWN_ACTIONX32_SETRESGID_RGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresgid.sa_sgid) == __OFFSET_SPAWN_ACTIONX32_SETRESGID_SGID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresuid.sa_euid) == __OFFSET_SPAWN_ACTIONX32_SETRESUID_EUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresuid.sa_ruid) == __OFFSET_SPAWN_ACTIONX32_SETRESUID_RUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setresuid.sa_suid) == __OFFSET_SPAWN_ACTIONX32_SETRESUID_SUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setreuid.sa_euid) == __OFFSET_SPAWN_ACTIONX32_SETREUID_EUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setreuid.sa_ruid) == __OFFSET_SPAWN_ACTIONX32_SETREUID_RUID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_setuid.sa_uid) == __OFFSET_SPAWN_ACTIONX32_SETUID_UID);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sigdfl.sa_sigset) == __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSET);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sigdfl.sa_sigsetsz) == __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSETSZ);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sigprocmask.sa_sigset) == __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSET);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_sigprocmask.sa_sigsetsz) == __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSETSZ);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_tcsetpgrp.sa_ttyfd) == __OFFSET_SPAWN_ACTIONX32_TCSETPGRP_TTYFD);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_type) == __OFFSET_SPAWN_ACTIONX32_TYPE);
STATIC_ASSERT(offsetof(struct spawn_actionx32, sa_umask.sa_mask) == __OFFSET_SPAWN_ACTIONX32_UMASK_MASK);

/* struct spawn_action_listx32 */
/* ... */

/* struct spawn_actionsx32 */
/* ... */





#include <kos/bits/spawn-action64.h>

/* struct spawn_actionx64 */
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_closerange.sa_hifd) == __OFFSET_SPAWN_ACTIONX64_CLOSERANGE_HIFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_closerange.sa_lofd) == __OFFSET_SPAWN_ACTIONX64_CLOSERANGE_LOFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_close.sa_fd) == __OFFSET_SPAWN_ACTIONX64_CLOSE_FD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_dup2.sa_newfd) == __OFFSET_SPAWN_ACTIONX64_DUP2_NEWFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_dup2.sa_oldfd) == __OFFSET_SPAWN_ACTIONX64_DUP2_OLDFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_fsmode.sa_flag) == __OFFSET_SPAWN_ACTIONX64_FSMODE_FLAG);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_fsmode.sa_mask) == __OFFSET_SPAWN_ACTIONX64_FSMODE_MASK);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_openat.sa_dfd) == __OFFSET_SPAWN_ACTIONX64_OPENAT_DFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_openat.sa_fd) == __OFFSET_SPAWN_ACTIONX64_OPENAT_FD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_openat.sa_filename) == __OFFSET_SPAWN_ACTIONX64_OPENAT_FILENAME);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_openat.sa_mode) == __OFFSET_SPAWN_ACTIONX64_OPENAT_MODE);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_openat.sa_oflags) == __OFFSET_SPAWN_ACTIONX64_OPENAT_OFLAGS);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sched_setparam.sa_param) == __OFFSET_SPAWN_ACTIONX64_SCHED_SETPARAM_PARAM);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sched_setscheduler.sa_param) == __OFFSET_SPAWN_ACTIONX64_SCHED_SETSCHEDULER_PARAM);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sched_setscheduler.sa_policy) == __OFFSET_SPAWN_ACTIONX64_SCHED_SETSCHEDULER_POLICY);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setfsgid.sa_fsgid) == __OFFSET_SPAWN_ACTIONX64_SETFSGID_FSGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setfsuid.sa_fsuid) == __OFFSET_SPAWN_ACTIONX64_SETFSUID_FSUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setgid.sa_gid) == __OFFSET_SPAWN_ACTIONX64_SETGID_GID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setgroups.sa_gcnt) == __OFFSET_SPAWN_ACTIONX64_SETGROUPS_GCNT);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setgroups.sa_gvec) == __OFFSET_SPAWN_ACTIONX64_SETGROUPS_GVEC);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setpgid.sa_pid) == __OFFSET_SPAWN_ACTIONX64_SETPGID_PID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setregid.sa_egid) == __OFFSET_SPAWN_ACTIONX64_SETREGID_EGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setregid.sa_rgid) == __OFFSET_SPAWN_ACTIONX64_SETREGID_RGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresgid.sa_egid) == __OFFSET_SPAWN_ACTIONX64_SETRESGID_EGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresgid.sa_rgid) == __OFFSET_SPAWN_ACTIONX64_SETRESGID_RGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresgid.sa_sgid) == __OFFSET_SPAWN_ACTIONX64_SETRESGID_SGID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresuid.sa_euid) == __OFFSET_SPAWN_ACTIONX64_SETRESUID_EUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresuid.sa_ruid) == __OFFSET_SPAWN_ACTIONX64_SETRESUID_RUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setresuid.sa_suid) == __OFFSET_SPAWN_ACTIONX64_SETRESUID_SUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setreuid.sa_euid) == __OFFSET_SPAWN_ACTIONX64_SETREUID_EUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setreuid.sa_ruid) == __OFFSET_SPAWN_ACTIONX64_SETREUID_RUID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_setuid.sa_uid) == __OFFSET_SPAWN_ACTIONX64_SETUID_UID);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sigdfl.sa_sigset) == __OFFSET_SPAWN_ACTIONX64_SIGDFL_SIGSET);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sigdfl.sa_sigsetsz) == __OFFSET_SPAWN_ACTIONX64_SIGDFL_SIGSETSZ);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sigprocmask.sa_sigset) == __OFFSET_SPAWN_ACTIONX64_SIGPROCMASK_SIGSET);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_sigprocmask.sa_sigsetsz) == __OFFSET_SPAWN_ACTIONX64_SIGPROCMASK_SIGSETSZ);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_tcsetpgrp.sa_ttyfd) == __OFFSET_SPAWN_ACTIONX64_TCSETPGRP_TTYFD);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_type) == __OFFSET_SPAWN_ACTIONX64_TYPE);
STATIC_ASSERT(offsetof(struct spawn_actionx64, sa_umask.sa_mask) == __OFFSET_SPAWN_ACTIONX64_UMASK_MASK);

/* struct spawn_action_listx64 */
/* ... */

/* struct spawn_actionsx64 */
/* ... */





#include <kos/exec/asm/elf32.h>





#include <kos/exec/asm/elf64.h>





#include <kos/exec/bits/library-listdef32.h>

/* struct library_listdef32 */
STATIC_ASSERT(offsetof(struct library_listdef32, lld_count) == __OFFSET_LIBRARY_LISTDEF32_COUNT);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_entry_offsetof_module) == __OFFSET_LIBRARY_LISTDEF32_ENTRY_OFFSETOF_MODULE);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_entry_offsetof_next) == __OFFSET_LIBRARY_LISTDEF32_ENTRY_OFFSETOF_NEXT);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_first) == __OFFSET_LIBRARY_LISTDEF32_FIRST);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_flags) == __OFFSET_LIBRARY_LISTDEF32_FLAGS);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_module_offsetof_filename) == __OFFSET_LIBRARY_LISTDEF32_MODULE_OFFSETOF_FILENAME);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_module_offsetof_loadaddr) == __OFFSET_LIBRARY_LISTDEF32_MODULE_OFFSETOF_LOADADDR);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_module_offsetof_loadstart) == __OFFSET_LIBRARY_LISTDEF32_MODULE_OFFSETOF_LOADSTART);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_size) == __OFFSET_LIBRARY_LISTDEF32_SIZE);
STATIC_ASSERT(offsetof(struct library_listdef32, lld_sizeof_pointer) == __OFFSET_LIBRARY_LISTDEF32_SIZEOF_POINTER);
STATIC_ASSERT(sizeof(struct library_listdef32) == __SIZEOF_LIBRARY_LISTDEF32);





#include <kos/exec/bits/library-listdef64.h>

/* struct library_listdef64 */
STATIC_ASSERT(offsetof(struct library_listdef64, lld_count) == __OFFSET_LIBRARY_LISTDEF64_COUNT);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_entry_offsetof_module) == __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_MODULE);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_entry_offsetof_next) == __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_NEXT);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_first) == __OFFSET_LIBRARY_LISTDEF64_FIRST);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_flags) == __OFFSET_LIBRARY_LISTDEF64_FLAGS);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_module_offsetof_filename) == __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_FILENAME);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_module_offsetof_loadaddr) == __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADADDR);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_module_offsetof_loadstart) == __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADSTART);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_size) == __OFFSET_LIBRARY_LISTDEF64_SIZE);
STATIC_ASSERT(offsetof(struct library_listdef64, lld_sizeof_pointer) == __OFFSET_LIBRARY_LISTDEF64_SIZEOF_POINTER);
STATIC_ASSERT(sizeof(struct library_listdef64) == __SIZEOF_LIBRARY_LISTDEF64);





#include <kos/exec/bits/peb32.h>

/* struct process_peb32 */
STATIC_ASSERT(offsetof(struct process_peb32, pp_argc) == OFFSET_PROCESS_PEB32_ARGC);
STATIC_ASSERT(offsetof(struct process_peb32, pp_argv) == OFFSET_PROCESS_PEB32_ARGV);
STATIC_ASSERT(offsetof(struct process_peb32, pp_envc) == OFFSET_PROCESS_PEB32_ENVC);
STATIC_ASSERT(offsetof(struct process_peb32, pp_envp) == OFFSET_PROCESS_PEB32_ENVP);





#include <kos/exec/bits/peb64.h>

/* struct process_peb64 */
STATIC_ASSERT(offsetof(struct process_peb64, pp_argc) == OFFSET_PROCESS_PEB64_ARGC);
STATIC_ASSERT(offsetof(struct process_peb64, pp_argv) == OFFSET_PROCESS_PEB64_ARGV);
STATIC_ASSERT(offsetof(struct process_peb64, pp_envc) == OFFSET_PROCESS_PEB64_ENVC);
STATIC_ASSERT(offsetof(struct process_peb64, pp_envp) == OFFSET_PROCESS_PEB64_ENVP);





#include <kos/kernel/cpu-state32.h>

/* struct gpregs32 */
STATIC_ASSERT(offsetof(struct gpregs32, gp_eax) == OFFSET_GPREGS32_EAX);
STATIC_ASSERT(offsetof(struct gpregs32, gp_ebp) == OFFSET_GPREGS32_EBP);
STATIC_ASSERT(offsetof(struct gpregs32, gp_ebx) == OFFSET_GPREGS32_EBX);
STATIC_ASSERT(offsetof(struct gpregs32, gp_ecx) == OFFSET_GPREGS32_ECX);
STATIC_ASSERT(offsetof(struct gpregs32, gp_edi) == OFFSET_GPREGS32_EDI);
STATIC_ASSERT(offsetof(struct gpregs32, gp_edx) == OFFSET_GPREGS32_EDX);
STATIC_ASSERT(offsetof(struct gpregs32, gp_esi) == OFFSET_GPREGS32_ESI);
STATIC_ASSERT(offsetof(struct gpregs32, gp_esp) == OFFSET_GPREGS32_ESP);
STATIC_ASSERT(sizeof(struct gpregs32) == SIZEOF_GPREGS32);

/* struct sgregs32 */
STATIC_ASSERT(offsetof(struct sgregs32, sg_ds) == OFFSET_SGREGS32_DS);
STATIC_ASSERT(offsetof(struct sgregs32, sg_es) == OFFSET_SGREGS32_ES);
STATIC_ASSERT(offsetof(struct sgregs32, sg_fs) == OFFSET_SGREGS32_FS);
STATIC_ASSERT(offsetof(struct sgregs32, sg_gs) == OFFSET_SGREGS32_GS);
STATIC_ASSERT(sizeof(struct sgregs32) == SIZEOF_SGREGS32);

/* struct coregs32 */
STATIC_ASSERT(offsetof(struct coregs32, co_cr0) == OFFSET_COREGS32_CR0);
STATIC_ASSERT(offsetof(struct coregs32, co_cr2) == OFFSET_COREGS32_CR2);
STATIC_ASSERT(offsetof(struct coregs32, co_cr3) == OFFSET_COREGS32_CR3);
STATIC_ASSERT(offsetof(struct coregs32, co_cr4) == OFFSET_COREGS32_CR4);
STATIC_ASSERT(sizeof(struct coregs32) == SIZEOF_COREGS32);

/* struct drregs32 */
STATIC_ASSERT(offsetof(struct drregs32, dr_dr0) == OFFSET_DRREGS32_DR0);
STATIC_ASSERT(offsetof(struct drregs32, dr_dr1) == OFFSET_DRREGS32_DR1);
STATIC_ASSERT(offsetof(struct drregs32, dr_dr2) == OFFSET_DRREGS32_DR2);
STATIC_ASSERT(offsetof(struct drregs32, dr_dr3) == OFFSET_DRREGS32_DR3);
STATIC_ASSERT(offsetof(struct drregs32, dr_dr6) == OFFSET_DRREGS32_DR6);
STATIC_ASSERT(offsetof(struct drregs32, dr_dr7) == OFFSET_DRREGS32_DR7);
STATIC_ASSERT(sizeof(struct drregs32) == SIZEOF_DRREGS32);

/* struct irregs32_kernel */
STATIC_ASSERT(offsetof(struct irregs32_kernel, ir_cs) == OFFSET_IRREGS32_KERNEL_CS);
STATIC_ASSERT(offsetof(struct irregs32_kernel, ir_eflags) == OFFSET_IRREGS32_KERNEL_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs32_kernel, ir_eip) == OFFSET_IRREGS32_KERNEL_EIP);
STATIC_ASSERT(sizeof(struct irregs32_kernel) == SIZEOF_IRREGS32_KERNEL);

/* struct irregs32_user */
STATIC_ASSERT(offsetof(struct irregs32_user, ir_cs) == OFFSET_IRREGS32_USER_CS);
STATIC_ASSERT(offsetof(struct irregs32_user, ir_eflags) == OFFSET_IRREGS32_USER_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs32_user, ir_eip) == OFFSET_IRREGS32_USER_EIP);
STATIC_ASSERT(offsetof(struct irregs32_user, ir_esp) == OFFSET_IRREGS32_USER_ESP);
STATIC_ASSERT(offsetof(struct irregs32_user, ir_ss) == OFFSET_IRREGS32_USER_SS);
STATIC_ASSERT(sizeof(struct irregs32_user) == SIZEOF_IRREGS32_USER);

/* struct irregs32_vm86 */
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_cs) == OFFSET_IRREGS32_VM86_CS);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_ds) == OFFSET_IRREGS32_VM86_DS);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_eflags) == OFFSET_IRREGS32_VM86_EFLAGS);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_eip) == OFFSET_IRREGS32_VM86_EIP);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_es) == OFFSET_IRREGS32_VM86_ES);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_esp) == OFFSET_IRREGS32_VM86_ESP);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_fs) == OFFSET_IRREGS32_VM86_FS);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_gs) == OFFSET_IRREGS32_VM86_GS);
STATIC_ASSERT(offsetof(struct irregs32_vm86, ir_ss) == OFFSET_IRREGS32_VM86_SS);
STATIC_ASSERT(sizeof(struct irregs32_vm86) == SIZEOF_IRREGS32_VM86);

/* struct ucpustate32 */
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_cs) == OFFSET_UCPUSTATE32_CS);
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_eflags) == OFFSET_UCPUSTATE32_EFLAGS);
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_eip) == OFFSET_UCPUSTATE32_EIP);
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_gpregs) == OFFSET_UCPUSTATE32_GPREGS);
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_sgregs) == OFFSET_UCPUSTATE32_SGREGS);
STATIC_ASSERT(offsetof(struct ucpustate32, ucs_ss) == OFFSET_UCPUSTATE32_SS);
STATIC_ASSERT(sizeof(struct ucpustate32) == SIZEOF_UCPUSTATE32);

/* struct lcpustate32 */
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_ebp) == OFFSET_LCPUSTATE32_EBP);
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_ebx) == OFFSET_LCPUSTATE32_EBX);
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_edi) == OFFSET_LCPUSTATE32_EDI);
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_eip) == OFFSET_LCPUSTATE32_EIP);
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_esi) == OFFSET_LCPUSTATE32_ESI);
STATIC_ASSERT(offsetof(struct lcpustate32, lcs_esp) == OFFSET_LCPUSTATE32_ESP);
STATIC_ASSERT(sizeof(struct lcpustate32) == SIZEOF_LCPUSTATE32);

/* struct kcpustate32 */
STATIC_ASSERT(offsetof(struct kcpustate32, kcs_eflags) == OFFSET_KCPUSTATE32_EFLAGS);
STATIC_ASSERT(offsetof(struct kcpustate32, kcs_eip) == OFFSET_KCPUSTATE32_EIP);
STATIC_ASSERT(offsetof(struct kcpustate32, kcs_gpregs) == OFFSET_KCPUSTATE32_GPREGS);
STATIC_ASSERT(sizeof(struct kcpustate32) == SIZEOF_KCPUSTATE32);

/* struct icpustate32 */
STATIC_ASSERT(offsetof(struct icpustate32, ics_ds) == OFFSET_ICPUSTATE32_DS);
STATIC_ASSERT(offsetof(struct icpustate32, ics_es) == OFFSET_ICPUSTATE32_ES);
STATIC_ASSERT(offsetof(struct icpustate32, ics_fs) == OFFSET_ICPUSTATE32_FS);
STATIC_ASSERT(offsetof(struct icpustate32, ics_gpregs) == OFFSET_ICPUSTATE32_GPREGS);
STATIC_ASSERT(offsetof(struct icpustate32, ics_irregs) == OFFSET_ICPUSTATE32_IRREGS);

/* struct scpustate32 */
STATIC_ASSERT(offsetof(struct scpustate32, scs_gpregs) == OFFSET_SCPUSTATE32_GPREGS);
STATIC_ASSERT(offsetof(struct scpustate32, scs_irregs) == OFFSET_SCPUSTATE32_IRREGS);
STATIC_ASSERT(offsetof(struct scpustate32, scs_sgregs) == OFFSET_SCPUSTATE32_SGREGS);

/* struct desctab32 */
STATIC_ASSERT(offsetof(struct desctab32, dt_limit) == OFFSET_DESCTAB32_LIMIT);
STATIC_ASSERT(offsetof(struct desctab32, dt_base) == OFFSET_DESCTAB32_BASE);
STATIC_ASSERT(sizeof(struct desctab32) == SIZEOF_DESCTAB32);

/* struct fcpustate32 */
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_coregs) == OFFSET_FCPUSTATE32_COREGS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_cs) == OFFSET_FCPUSTATE32_CS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_drregs) == OFFSET_FCPUSTATE32_DRREGS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_ds) == OFFSET_FCPUSTATE32_DS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_eflags) == OFFSET_FCPUSTATE32_EFLAGS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_eip) == OFFSET_FCPUSTATE32_EIP);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_es) == OFFSET_FCPUSTATE32_ES);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_fs) == OFFSET_FCPUSTATE32_FS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_gdt) == OFFSET_FCPUSTATE32_GDT);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_gpregs) == OFFSET_FCPUSTATE32_GPREGS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_gs) == OFFSET_FCPUSTATE32_GS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_idt) == OFFSET_FCPUSTATE32_IDT);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_ldt) == OFFSET_FCPUSTATE32_LDT);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_ss) == OFFSET_FCPUSTATE32_SS);
STATIC_ASSERT(offsetof(struct fcpustate32, fcs_sgregs.sg_tr) == OFFSET_FCPUSTATE32_TR);
STATIC_ASSERT(sizeof(struct fcpustate32) == SIZEOF_FCPUSTATE32);





#include <kos/kernel/cpu-state64.h>

/* struct gpregs64 */
STATIC_ASSERT(offsetof(struct gpregs64, gp_r10) == OFFSET_GPREGS64_R10);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r11) == OFFSET_GPREGS64_R11);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r12) == OFFSET_GPREGS64_R12);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r13) == OFFSET_GPREGS64_R13);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r14) == OFFSET_GPREGS64_R14);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r15) == OFFSET_GPREGS64_R15);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r8) == OFFSET_GPREGS64_R8);
STATIC_ASSERT(offsetof(struct gpregs64, gp_r9) == OFFSET_GPREGS64_R9);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rax) == OFFSET_GPREGS64_RAX);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rbp) == OFFSET_GPREGS64_RBP);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rbx) == OFFSET_GPREGS64_RBX);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rcx) == OFFSET_GPREGS64_RCX);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rdi) == OFFSET_GPREGS64_RDI);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rdx) == OFFSET_GPREGS64_RDX);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rsi) == OFFSET_GPREGS64_RSI);
STATIC_ASSERT(offsetof(struct gpregs64, gp_rsp) == OFFSET_GPREGS64_RSP);
STATIC_ASSERT(sizeof(struct gpregs64) == SIZEOF_GPREGS64);

/* struct gpregsnsp64 */
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r10) == OFFSET_GPREGSNSP64_R10);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r11) == OFFSET_GPREGSNSP64_R11);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r12) == OFFSET_GPREGSNSP64_R12);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r13) == OFFSET_GPREGSNSP64_R13);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r14) == OFFSET_GPREGSNSP64_R14);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r15) == OFFSET_GPREGSNSP64_R15);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r8) == OFFSET_GPREGSNSP64_R8);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_r9) == OFFSET_GPREGSNSP64_R9);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rax) == OFFSET_GPREGSNSP64_RAX);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rbp) == OFFSET_GPREGSNSP64_RBP);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rbx) == OFFSET_GPREGSNSP64_RBX);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rcx) == OFFSET_GPREGSNSP64_RCX);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rdi) == OFFSET_GPREGSNSP64_RDI);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rdx) == OFFSET_GPREGSNSP64_RDX);
STATIC_ASSERT(offsetof(struct gpregsnsp64, gp_rsi) == OFFSET_GPREGSNSP64_RSI);
STATIC_ASSERT(sizeof(struct gpregsnsp64) == SIZEOF_GPREGSNSP64);

/* struct sgregs64 */
STATIC_ASSERT(offsetof(struct sgregs64, sg_ds) == OFFSET_SGREGS64_DS);
STATIC_ASSERT(offsetof(struct sgregs64, sg_es) == OFFSET_SGREGS64_ES);
STATIC_ASSERT(offsetof(struct sgregs64, sg_fs) == OFFSET_SGREGS64_FS);
STATIC_ASSERT(offsetof(struct sgregs64, sg_gs) == OFFSET_SGREGS64_GS);
STATIC_ASSERT(sizeof(struct sgregs64) == SIZEOF_SGREGS64);

/* struct sgbase64 */
STATIC_ASSERT(offsetof(struct sgbase64, sg_gsbase) == OFFSET_SGBASE64_GSBASE);
STATIC_ASSERT(offsetof(struct sgbase64, sg_fsbase) == OFFSET_SGBASE64_FSBASE);
STATIC_ASSERT(sizeof(struct sgbase64) == SIZEOF_SGBASE64);

/* struct coregs64 */
STATIC_ASSERT(offsetof(struct coregs64, co_cr0) == OFFSET_COREGS64_CR0);
STATIC_ASSERT(offsetof(struct coregs64, co_cr2) == OFFSET_COREGS64_CR2);
STATIC_ASSERT(offsetof(struct coregs64, co_cr3) == OFFSET_COREGS64_CR3);
STATIC_ASSERT(offsetof(struct coregs64, co_cr4) == OFFSET_COREGS64_CR4);
STATIC_ASSERT(sizeof(struct coregs64) == SIZEOF_COREGS64);

/* struct drregs64 */
STATIC_ASSERT(offsetof(struct drregs64, dr_dr0) == OFFSET_DRREGS64_DR0);
STATIC_ASSERT(offsetof(struct drregs64, dr_dr1) == OFFSET_DRREGS64_DR1);
STATIC_ASSERT(offsetof(struct drregs64, dr_dr2) == OFFSET_DRREGS64_DR2);
STATIC_ASSERT(offsetof(struct drregs64, dr_dr3) == OFFSET_DRREGS64_DR3);
STATIC_ASSERT(offsetof(struct drregs64, dr_dr6) == OFFSET_DRREGS64_DR6);
STATIC_ASSERT(offsetof(struct drregs64, dr_dr7) == OFFSET_DRREGS64_DR7);
STATIC_ASSERT(sizeof(struct drregs64) == SIZEOF_DRREGS64);

/* struct irregs64 */
STATIC_ASSERT(offsetof(struct irregs64, ir_cs) == OFFSET_IRREGS64_CS);
STATIC_ASSERT(offsetof(struct irregs64, ir_rflags) == OFFSET_IRREGS64_RFLAGS);
STATIC_ASSERT(offsetof(struct irregs64, ir_rip) == OFFSET_IRREGS64_RIP);
STATIC_ASSERT(offsetof(struct irregs64, ir_rsp) == OFFSET_IRREGS64_RSP);
STATIC_ASSERT(offsetof(struct irregs64, ir_ss) == OFFSET_IRREGS64_SS);
STATIC_ASSERT(sizeof(struct irregs64) == SIZEOF_IRREGS64);

/* struct ucpustate64 */
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_cs) == OFFSET_UCPUSTATE64_CS);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_gpregs) == OFFSET_UCPUSTATE64_GPREGS);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_rflags) == OFFSET_UCPUSTATE64_RFLAGS);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_rip) == OFFSET_UCPUSTATE64_RIP);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_sgbase) == OFFSET_UCPUSTATE64_SGBASE);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_sgregs) == OFFSET_UCPUSTATE64_SGREGS);
STATIC_ASSERT(offsetof(struct ucpustate64, ucs_ss) == OFFSET_UCPUSTATE64_SS);
STATIC_ASSERT(sizeof(struct ucpustate64) == SIZEOF_UCPUSTATE64);

/* struct lcpustate64 */
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_r12) == OFFSET_LCPUSTATE64_R12);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_r13) == OFFSET_LCPUSTATE64_R13);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_r14) == OFFSET_LCPUSTATE64_R14);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_r15) == OFFSET_LCPUSTATE64_R15);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_rbp) == OFFSET_LCPUSTATE64_RBP);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_rbx) == OFFSET_LCPUSTATE64_RBX);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_rip) == OFFSET_LCPUSTATE64_RIP);
STATIC_ASSERT(offsetof(struct lcpustate64, lcs_rsp) == OFFSET_LCPUSTATE64_RSP);
STATIC_ASSERT(sizeof(struct lcpustate64) == SIZEOF_LCPUSTATE64);

/* struct kcpustate64 */
STATIC_ASSERT(offsetof(struct kcpustate64, kcs_gpregs) == OFFSET_KCPUSTATE64_GPREGS);
STATIC_ASSERT(offsetof(struct kcpustate64, kcs_rflags) == OFFSET_KCPUSTATE64_RFLAGS);
STATIC_ASSERT(offsetof(struct kcpustate64, kcs_rip) == OFFSET_KCPUSTATE64_RIP);
STATIC_ASSERT(sizeof(struct kcpustate64) == SIZEOF_KCPUSTATE64);

/* struct icpustate64 */
STATIC_ASSERT(offsetof(struct icpustate64, ics_irregs) == OFFSET_ICPUSTATE64_IRREGS);
STATIC_ASSERT(offsetof(struct icpustate64, ics_gpregs) == OFFSET_ICPUSTATE64_GPREGSNSP);
STATIC_ASSERT(sizeof(struct icpustate64) == SIZEOF_ICPUSTATE64);

/* struct scpustate64 */
STATIC_ASSERT(offsetof(struct scpustate64, scs_gpregs) == OFFSET_SCPUSTATE64_GPREGSNSP);
STATIC_ASSERT(offsetof(struct scpustate64, scs_irregs) == OFFSET_SCPUSTATE64_IRREGS);
STATIC_ASSERT(offsetof(struct scpustate64, scs_sgbase) == OFFSET_SCPUSTATE64_SGBASE);
STATIC_ASSERT(offsetof(struct scpustate64, scs_sgregs) == OFFSET_SCPUSTATE64_SGREGS);
STATIC_ASSERT(sizeof(struct scpustate64) == SIZEOF_SCPUSTATE64);

/* struct desctab64 */
STATIC_ASSERT(offsetof(struct desctab64, dt_limit) == OFFSET_DESCTAB64_LIMIT);
STATIC_ASSERT(offsetof(struct desctab64, dt_base) == OFFSET_DESCTAB64_BASE);
STATIC_ASSERT(sizeof(struct desctab64) == SIZEOF_DESCTAB64);

/* struct fcpustate64 */
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_coregs) == OFFSET_FCPUSTATE64_COREGS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_cs) == OFFSET_FCPUSTATE64_CS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_drregs) == OFFSET_FCPUSTATE64_DRREGS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_ds) == OFFSET_FCPUSTATE64_DS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_es) == OFFSET_FCPUSTATE64_ES);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_fs) == OFFSET_FCPUSTATE64_FS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_gdt) == OFFSET_FCPUSTATE64_GDT);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_gpregs) == OFFSET_FCPUSTATE64_GPREGS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_gs) == OFFSET_FCPUSTATE64_GS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_idt) == OFFSET_FCPUSTATE64_IDT);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_ldt) == OFFSET_FCPUSTATE64_LDT);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_rflags) == OFFSET_FCPUSTATE64_RFLAGS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_rip) == OFFSET_FCPUSTATE64_RIP);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgbase) == OFFSET_FCPUSTATE64_SGBASE);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_ss) == OFFSET_FCPUSTATE64_SS);
STATIC_ASSERT(offsetof(struct fcpustate64, fcs_sgregs.sg_tr) == OFFSET_FCPUSTATE64_TR);
STATIC_ASSERT(sizeof(struct fcpustate64) == SIZEOF_FCPUSTATE64);





#include <kos/kernel/fpu-sstate.h>

/* struct sfpuenv */
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fcs) == OFFSET_SFPUENV_FCS);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fcw) == OFFSET_SFPUENV_FCW);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fdp) == OFFSET_SFPUENV_FDP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fds) == OFFSET_SFPUENV_FDS);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fip) == OFFSET_SFPUENV_FIP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fop) == OFFSET_SFPUENV_FOP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fsw) == OFFSET_SFPUENV_FSW);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_ftw) == OFFSET_SFPUENV_FTW);
STATIC_ASSERT(sizeof(struct sfpuenv) == SIZEOF_SFPUENV);
STATIC_ASSERT(alignof(struct sfpuenv) == ALIGNOF_SFPUENV);

/* struct sfpustate */
STATIC_ASSERT(offsetof(struct sfpustate, fs_fcs) == OFFSET_SFPUSTATE_FCS);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fcw) == OFFSET_SFPUSTATE_FCW);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fdp) == OFFSET_SFPUSTATE_FDP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fds) == OFFSET_SFPUSTATE_FDS);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fip) == OFFSET_SFPUSTATE_FIP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fop) == OFFSET_SFPUSTATE_FOP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fsw) == OFFSET_SFPUSTATE_FSW);
STATIC_ASSERT(offsetof(struct sfpustate, fs_ftw) == OFFSET_SFPUSTATE_FTW);
STATIC_ASSERT(sizeof(struct sfpustate) == SIZEOF_SFPUSTATE);
STATIC_ASSERT(alignof(struct sfpustate) == ALIGNOF_SFPUSTATE);





#include <kos/kernel/fpu-state32.h>

/* struct xfpustate32 */
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fcs) == OFFSET_XFPUSTATE32_FCS);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fcw) == OFFSET_XFPUSTATE32_FCW);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fdp) == OFFSET_XFPUSTATE32_FDP);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fds) == OFFSET_XFPUSTATE32_FDS);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fip) == OFFSET_XFPUSTATE32_FIP);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fop) == OFFSET_XFPUSTATE32_FOP);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_fsw) == OFFSET_XFPUSTATE32_FSW);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_ftw) == OFFSET_XFPUSTATE32_FTW);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_mxcsr) == OFFSET_XFPUSTATE32_MXCSR);
STATIC_ASSERT(offsetof(struct xfpustate32, fx_mxcsr_mask) == OFFSET_XFPUSTATE32_MXCSR_MASK);
STATIC_ASSERT(sizeof(struct xfpustate32) == SIZEOF_XFPUSTATE32);
STATIC_ASSERT(alignof(struct xfpustate32) == ALIGNOF_XFPUSTATE32);

/* struct fpustate32 */
STATIC_ASSERT(sizeof(struct fpustate32) == SIZEOF_FPUSTATE32);
STATIC_ASSERT(alignof(struct fpustate32) == ALIGNOF_FPUSTATE32);





#include <kos/kernel/fpu-state64.h>

/* struct xfpustate64 */
STATIC_ASSERT(offsetof(struct xfpustate64, fx_fcw) == OFFSET_XFPUSTATE64_FCW);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_fdp) == OFFSET_XFPUSTATE64_FDP);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_fip) == OFFSET_XFPUSTATE64_FIP);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_fop) == OFFSET_XFPUSTATE64_FOP);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_fsw) == OFFSET_XFPUSTATE64_FSW);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_ftw) == OFFSET_XFPUSTATE64_FTW);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_mxcsr) == OFFSET_XFPUSTATE64_MXCSR);
STATIC_ASSERT(offsetof(struct xfpustate64, fx_mxcsr_mask) == OFFSET_XFPUSTATE64_MXCSR_MASK);
STATIC_ASSERT(sizeof(struct xfpustate64) == SIZEOF_XFPUSTATE64);
STATIC_ASSERT(alignof(struct xfpustate64) == ALIGNOF_XFPUSTATE64);

/* struct fpustate64 */
STATIC_ASSERT(sizeof(struct fpustate64) == SIZEOF_FPUSTATE64);
STATIC_ASSERT(alignof(struct fpustate64) == ALIGNOF_FPUSTATE64);





#include <kos/kernel/mcontext32.h>

/* struct mcontext32 */
STATIC_ASSERT(offsetof(struct mcontext32, gregs) == __OFFSET_MCONTEXT32_CPU);
STATIC_ASSERT(offsetof(struct mcontext32, mc_gregs) == __OFFSET_MCONTEXT32_CPU);
STATIC_ASSERT(offsetof(struct mcontext32, mc_context) == __OFFSET_MCONTEXT32_CPU);
STATIC_ASSERT(offsetof(struct mcontext32, cr2) == __OFFSET_MCONTEXT32_CR2);
STATIC_ASSERT(offsetof(struct mcontext32, mc_cr2) == __OFFSET_MCONTEXT32_CR2);
STATIC_ASSERT(offsetof(struct mcontext32, mc_flags) == __OFFSET_MCONTEXT32_FLAGS);
STATIC_ASSERT(offsetof(struct mcontext32, fpregs) == __OFFSET_MCONTEXT32_FPU);
STATIC_ASSERT(offsetof(struct mcontext32, mc_fpu) == __OFFSET_MCONTEXT32_FPU);
STATIC_ASSERT(sizeof(struct mcontext32) == __SIZEOF_MCONTEXT32);
STATIC_ASSERT(alignof(struct mcontext32) == __ALIGNOF_MCONTEXT32);





#include <kos/kernel/mcontext64.h>

/* struct mcontext64 */
STATIC_ASSERT(offsetof(struct mcontext64, gregs) == __OFFSET_MCONTEXT64_CPU);
STATIC_ASSERT(offsetof(struct mcontext64, mc_gregs) == __OFFSET_MCONTEXT64_CPU);
STATIC_ASSERT(offsetof(struct mcontext64, mc_context) == __OFFSET_MCONTEXT64_CPU);
STATIC_ASSERT(offsetof(struct mcontext64, cr2) == __OFFSET_MCONTEXT64_CR2);
STATIC_ASSERT(offsetof(struct mcontext64, mc_cr2) == __OFFSET_MCONTEXT64_CR2);
STATIC_ASSERT(offsetof(struct mcontext64, mc_flags) == __OFFSET_MCONTEXT64_FLAGS);
STATIC_ASSERT(offsetof(struct mcontext64, fpregs) == __OFFSET_MCONTEXT64_FPU);
STATIC_ASSERT(offsetof(struct mcontext64, mc_fpu) == __OFFSET_MCONTEXT64_FPU);
STATIC_ASSERT(sizeof(struct mcontext64) == __SIZEOF_MCONTEXT64);
STATIC_ASSERT(alignof(struct mcontext64) == __ALIGNOF_MCONTEXT64);





#include <kos/kernel/tss16.h>

/* struct tss16 */
STATIC_ASSERT(offsetof(struct tss16, t_ax) == OFFSET_TSS16_AX);
STATIC_ASSERT(offsetof(struct tss16, t_bp) == OFFSET_TSS16_BP);
STATIC_ASSERT(offsetof(struct tss16, t_bx) == OFFSET_TSS16_BX);
STATIC_ASSERT(offsetof(struct tss16, t_cs) == OFFSET_TSS16_CS);
STATIC_ASSERT(offsetof(struct tss16, t_cx) == OFFSET_TSS16_CX);
STATIC_ASSERT(offsetof(struct tss16, t_di) == OFFSET_TSS16_DI);
STATIC_ASSERT(offsetof(struct tss16, t_ds) == OFFSET_TSS16_DS);
STATIC_ASSERT(offsetof(struct tss16, t_dx) == OFFSET_TSS16_DX);
STATIC_ASSERT(offsetof(struct tss16, t_es) == OFFSET_TSS16_ES);
STATIC_ASSERT(offsetof(struct tss16, t_flags) == OFFSET_TSS16_FLAGS);
STATIC_ASSERT(offsetof(struct tss16, t_ip) == OFFSET_TSS16_IP);
STATIC_ASSERT(offsetof(struct tss16, t_ldtr) == OFFSET_TSS16_LDTR);
STATIC_ASSERT(offsetof(struct tss16, t_link) == OFFSET_TSS16_LINK);
STATIC_ASSERT(offsetof(struct tss16, t_si) == OFFSET_TSS16_SI);
STATIC_ASSERT(offsetof(struct tss16, t_sp) == OFFSET_TSS16_SP);
STATIC_ASSERT(offsetof(struct tss16, t_sp0) == OFFSET_TSS16_SP0);
STATIC_ASSERT(offsetof(struct tss16, t_sp1) == OFFSET_TSS16_SP1);
STATIC_ASSERT(offsetof(struct tss16, t_sp2) == OFFSET_TSS16_SP2);
STATIC_ASSERT(offsetof(struct tss16, t_ss) == OFFSET_TSS16_SS);
STATIC_ASSERT(offsetof(struct tss16, t_ss0) == OFFSET_TSS16_SS0);
STATIC_ASSERT(offsetof(struct tss16, t_ss1) == OFFSET_TSS16_SS1);
STATIC_ASSERT(offsetof(struct tss16, t_ss2) == OFFSET_TSS16_SS2);
STATIC_ASSERT(sizeof(struct tss16) == SIZEOF_TSS16);
STATIC_ASSERT(alignof(struct tss16) == ALIGNOF_TSS16);





#include <kos/kernel/tss32.h>

/* struct tss32 */
STATIC_ASSERT(offsetof(struct tss32, t_cr3) == OFFSET_TSS32_CR3);
STATIC_ASSERT(offsetof(struct tss32, t_cs) == OFFSET_TSS32_CS);
STATIC_ASSERT(offsetof(struct tss32, t_ds) == OFFSET_TSS32_DS);
STATIC_ASSERT(offsetof(struct tss32, t_eax) == OFFSET_TSS32_EAX);
STATIC_ASSERT(offsetof(struct tss32, t_ebp) == OFFSET_TSS32_EBP);
STATIC_ASSERT(offsetof(struct tss32, t_ebx) == OFFSET_TSS32_EBX);
STATIC_ASSERT(offsetof(struct tss32, t_ecx) == OFFSET_TSS32_ECX);
STATIC_ASSERT(offsetof(struct tss32, t_edi) == OFFSET_TSS32_EDI);
STATIC_ASSERT(offsetof(struct tss32, t_edx) == OFFSET_TSS32_EDX);
STATIC_ASSERT(offsetof(struct tss32, t_eflags) == OFFSET_TSS32_EFLAGS);
STATIC_ASSERT(offsetof(struct tss32, t_eip) == OFFSET_TSS32_EIP);
STATIC_ASSERT(offsetof(struct tss32, t_es) == OFFSET_TSS32_ES);
STATIC_ASSERT(offsetof(struct tss32, t_esi) == OFFSET_TSS32_ESI);
STATIC_ASSERT(offsetof(struct tss32, t_esp) == OFFSET_TSS32_ESP);
STATIC_ASSERT(offsetof(struct tss32, t_esp0) == OFFSET_TSS32_ESP0);
STATIC_ASSERT(offsetof(struct tss32, t_esp1) == OFFSET_TSS32_ESP1);
STATIC_ASSERT(offsetof(struct tss32, t_esp2) == OFFSET_TSS32_ESP2);
STATIC_ASSERT(offsetof(struct tss32, t_flags) == OFFSET_TSS32_FLAGS);
STATIC_ASSERT(offsetof(struct tss32, t_fs) == OFFSET_TSS32_FS);
STATIC_ASSERT(offsetof(struct tss32, t_gs) == OFFSET_TSS32_GS);
STATIC_ASSERT(offsetof(struct tss32, t_iomap) == OFFSET_TSS32_IOMAP);
STATIC_ASSERT(offsetof(struct tss32, t_ldtr) == OFFSET_TSS32_LDTR);
STATIC_ASSERT(offsetof(struct tss32, t_link) == OFFSET_TSS32_LINK);
STATIC_ASSERT(offsetof(struct tss32, t_ss) == OFFSET_TSS32_SS);
STATIC_ASSERT(offsetof(struct tss32, t_ss0) == OFFSET_TSS32_SS0);
STATIC_ASSERT(offsetof(struct tss32, t_ss1) == OFFSET_TSS32_SS1);
STATIC_ASSERT(offsetof(struct tss32, t_ss2) == OFFSET_TSS32_SS2);
STATIC_ASSERT(sizeof(struct tss32) == SIZEOF_TSS32);
STATIC_ASSERT(alignof(struct tss32) == ALIGNOF_TSS32);





#include <kos/kernel/tss64.h>

/* struct tss64 */
STATIC_ASSERT(offsetof(struct tss64, t_iomap) == OFFSET_TSS64_IOMAP);
STATIC_ASSERT(offsetof(struct tss64, t_ist1) == OFFSET_TSS64_IST1);
STATIC_ASSERT(offsetof(struct tss64, t_ist2) == OFFSET_TSS64_IST2);
STATIC_ASSERT(offsetof(struct tss64, t_ist3) == OFFSET_TSS64_IST3);
STATIC_ASSERT(offsetof(struct tss64, t_ist4) == OFFSET_TSS64_IST4);
STATIC_ASSERT(offsetof(struct tss64, t_ist5) == OFFSET_TSS64_IST5);
STATIC_ASSERT(offsetof(struct tss64, t_ist6) == OFFSET_TSS64_IST6);
STATIC_ASSERT(offsetof(struct tss64, t_ist7) == OFFSET_TSS64_IST7);
STATIC_ASSERT(offsetof(struct tss64, t_rsp0) == OFFSET_TSS64_RSP0);
STATIC_ASSERT(offsetof(struct tss64, t_rsp1) == OFFSET_TSS64_RSP1);
STATIC_ASSERT(offsetof(struct tss64, t_rsp2) == OFFSET_TSS64_RSP2);
STATIC_ASSERT(sizeof(struct tss64) == SIZEOF_TSS64);
STATIC_ASSERT(alignof(struct tss64) == ALIGNOF_TSS64);





#include <kos/kernel/ucontext32.h>

/* struct __sigset_structx32 */
/* ... */

/* struct ucontext32 */
STATIC_ASSERT(offsetof(struct ucontext32, uc_link) == __OFFSET_UCONTEXT32_LINK);
STATIC_ASSERT(offsetof(struct ucontext32, uc_mcontext) == __OFFSET_UCONTEXT32_MCONTEXT);
STATIC_ASSERT(offsetof(struct ucontext32, uc_sigmask) == __OFFSET_UCONTEXT32_SIGMASK);
STATIC_ASSERT(offsetof(struct ucontext32, uc_stack) == __OFFSET_UCONTEXT32_STACK);
STATIC_ASSERT(sizeof(struct ucontext32) == __SIZEOF_UCONTEXT32);





#include <kos/kernel/ucontext64.h>

/* struct ucontext64 */
STATIC_ASSERT(offsetof(struct ucontext64, uc_link) == __OFFSET_UCONTEXT64_LINK);
STATIC_ASSERT(offsetof(struct ucontext64, uc_mcontext) == __OFFSET_UCONTEXT64_MCONTEXT);
STATIC_ASSERT(offsetof(struct ucontext64, uc_sigmask) == __OFFSET_UCONTEXT64_SIGMASK);
STATIC_ASSERT(offsetof(struct ucontext64, uc_stack) == __OFFSET_UCONTEXT64_STACK);
STATIC_ASSERT(sizeof(struct ucontext64) == __SIZEOF_UCONTEXT64);





#include <librpc/bits/rpc32.h>

/* struct rpc_register_state32 */
/* ... */





#include <librpc/bits/rpc64.h>

/* struct rpc_register_state64 */
/* ... */





#include <librpc/bits/syscall-info32.h>

/* struct rpc_syscall_info32 */
STATIC_ASSERT(offsetof(struct rpc_syscall_info32, rsi_sysno) == OFFSET_RPC_SYSCALL_INFO32_SYSNO);
STATIC_ASSERT(offsetof(struct rpc_syscall_info32, rsi_flags) == OFFSET_RPC_SYSCALL_INFO32_FLAGS);
STATIC_ASSERT(sizeof(struct rpc_syscall_info32) == SIZEOF_RPC_SYSCALL_INFO32);





#include <librpc/bits/syscall-info64.h>

/* struct rpc_syscall_info64 */
STATIC_ASSERT(offsetof(struct rpc_syscall_info64, rsi_sysno) == OFFSET_RPC_SYSCALL_INFO64_SYSNO);
STATIC_ASSERT(offsetof(struct rpc_syscall_info64, rsi_flags) == OFFSET_RPC_SYSCALL_INFO64_FLAGS);
STATIC_ASSERT(sizeof(struct rpc_syscall_info64) == SIZEOF_RPC_SYSCALL_INFO64);





#undef sigev_value
#undef sigev_signo
#undef sigev_notify
#undef sigev_notify_function
#undef sigev_notify_attributes
#include <bits/sigevent-cygwin.h>

/* struct sigevent_cygwin */
STATIC_ASSERT(offsetof(struct sigevent_cygwin, sigev_notify) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY);
STATIC_ASSERT(offsetof(struct sigevent_cygwin, sigev_notify_attributes) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct sigevent_cygwin, sigev_notify_function) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct sigevent_cygwin, sigev_signo) == __OFFSET_SIGEVENT_CYGWIN_SIGNO);
STATIC_ASSERT(offsetof(struct sigevent_cygwin, sigev_value) == __OFFSET_SIGEVENT_CYGWIN_VALUE);
STATIC_ASSERT(sizeof(struct sigevent_cygwin) == __SIZEOF_SIGEVENT_CYGWIN);





#undef si_signo
#undef si_code
#undef si_pid
#undef si_uid
#undef si_errno
#undef _si_data
#undef _si_commune
#undef si_sigval
#undef si_value
#undef si_tid
#undef si_overrun
#undef si_status
#undef si_utime
#undef si_stime
#undef si_addr
#include <bits/siginfo-struct-cygwin.h>

/* struct _sigcommune */
/* ... */

/* struct __siginfo_cygwin_struct */
/* ... */





STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_ST(0));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[0]) == OFFSET_SFPUSTATE_MM(0));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_ST(1));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[1]) == OFFSET_SFPUSTATE_MM(1));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_ST(2));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[2]) == OFFSET_SFPUSTATE_MM(2));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_ST(3));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[3]) == OFFSET_SFPUSTATE_MM(3));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_ST(4));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[4]) == OFFSET_SFPUSTATE_MM(4));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_ST(5));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[5]) == OFFSET_SFPUSTATE_MM(5));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_ST(6));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[6]) == OFFSET_SFPUSTATE_MM(6));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_ST(7));
STATIC_ASSERT(offsetof(struct sfpustate, fs_regs[7]) == OFFSET_SFPUSTATE_MM(7));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_ST(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[0]) == OFFSET_XFPUSTATE32_MM(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_ST(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[1]) == OFFSET_XFPUSTATE32_MM(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_ST(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[2]) == OFFSET_XFPUSTATE32_MM(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_ST(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[3]) == OFFSET_XFPUSTATE32_MM(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_ST(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[4]) == OFFSET_XFPUSTATE32_MM(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_ST(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[5]) == OFFSET_XFPUSTATE32_MM(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_ST(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[6]) == OFFSET_XFPUSTATE32_MM(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_ST(7));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_regs[7]) == OFFSET_XFPUSTATE32_MM(7));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[0]) == OFFSET_XFPUSTATE32_XMM(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[1]) == OFFSET_XFPUSTATE32_XMM(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[2]) == OFFSET_XFPUSTATE32_XMM(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[3]) == OFFSET_XFPUSTATE32_XMM(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[4]) == OFFSET_XFPUSTATE32_XMM(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[5]) == OFFSET_XFPUSTATE32_XMM(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[6]) == OFFSET_XFPUSTATE32_XMM(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fx_xmm[7]) == OFFSET_XFPUSTATE32_XMM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_ST(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[0]) == OFFSET_XFPUSTATE64_MM(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_ST(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[1]) == OFFSET_XFPUSTATE64_MM(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_ST(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[2]) == OFFSET_XFPUSTATE64_MM(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_ST(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[3]) == OFFSET_XFPUSTATE64_MM(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_ST(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[4]) == OFFSET_XFPUSTATE64_MM(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_ST(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[5]) == OFFSET_XFPUSTATE64_MM(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_ST(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[6]) == OFFSET_XFPUSTATE64_MM(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_ST(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_regs[7]) == OFFSET_XFPUSTATE64_MM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[0]) == OFFSET_XFPUSTATE64_XMM(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[1]) == OFFSET_XFPUSTATE64_XMM(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[2]) == OFFSET_XFPUSTATE64_XMM(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[3]) == OFFSET_XFPUSTATE64_XMM(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[4]) == OFFSET_XFPUSTATE64_XMM(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[5]) == OFFSET_XFPUSTATE64_XMM(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[6]) == OFFSET_XFPUSTATE64_XMM(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[7]) == OFFSET_XFPUSTATE64_XMM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[8]) == OFFSET_XFPUSTATE64_XMM(8));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[9]) == OFFSET_XFPUSTATE64_XMM(9));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[10]) == OFFSET_XFPUSTATE64_XMM(10));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[11]) == OFFSET_XFPUSTATE64_XMM(11));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[12]) == OFFSET_XFPUSTATE64_XMM(12));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[13]) == OFFSET_XFPUSTATE64_XMM(13));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[14]) == OFFSET_XFPUSTATE64_XMM(14));
STATIC_ASSERT(offsetof(struct xfpustate64, fx_xmm[15]) == OFFSET_XFPUSTATE64_XMM(15));
STATIC_ASSERT(OFFSET_TSS64_IST1 == OFFSET_TSS64_IST(1));
STATIC_ASSERT(OFFSET_TSS64_IST2 == OFFSET_TSS64_IST(2));
STATIC_ASSERT(OFFSET_TSS64_IST3 == OFFSET_TSS64_IST(3));
STATIC_ASSERT(OFFSET_TSS64_IST4 == OFFSET_TSS64_IST(4));
STATIC_ASSERT(OFFSET_TSS64_IST5 == OFFSET_TSS64_IST(5));
STATIC_ASSERT(OFFSET_TSS64_IST6 == OFFSET_TSS64_IST(6));
STATIC_ASSERT(OFFSET_TSS64_IST7 == OFFSET_TSS64_IST(7));
#if X86_64_VA_LIST_XMM_COUNT >= 0
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[0]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(0));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 1
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[1]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(1));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 2
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[2]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(2));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 3
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[3]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(3));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 4
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[4]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(4));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 5
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[5]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(5));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 6
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[6]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(6));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 7
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[7]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(7));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 8
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[8]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(8));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 9
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[9]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(9));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 10
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[10]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(10));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 11
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[11]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(11));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 12
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[12]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(12));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 13
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[13]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(13));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 14
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[14]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(14));
#endif
#if X86_64_VA_LIST_XMM_COUNT >= 15
STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[15]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(15));
#endif
//[[[end]]]


#include <bits/sigset.h>
STATIC_ASSERT(sizeof(__sigset_t) == __SIZEOF_SIGSET_T__);
STATIC_ASSERT(COMPILER_LENOF(((__sigset_t *)0)->__val) == _SIGSET_NWORDS);

#include <bits/semaphore.h>
STATIC_ASSERT(sizeof(sem_t) == __SIZEOF_SEM_T);
STATIC_ASSERT(alignof(sem_t) >= alignof(void *));


#include <kos/kernel/segment.h>
STATIC_ASSERT(sizeof(struct segment) == SIZEOF_SEGMENT_DESCRIPTOR);
STATIC_ASSERT(SIZEOF_SEGMENT_DESCRIPTOR == 8);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_limit0) == OFFSET_SEGMENT_DESCRIPTOR_LIMIT0);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_base0) == OFFSET_SEGMENT_DESCRIPTOR_BASE0);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_base1) == OFFSET_SEGMENT_DESCRIPTOR_BASE1);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_type_s_dpl_p) == OFFSET_SEGMENT_DESCRIPTOR_TYPE_S_DPL_P);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_limit1_avl_l_db_g) == OFFSET_SEGMENT_DESCRIPTOR_LIMIT1_AVL_L_DB_G);
STATIC_ASSERT(offsetof(struct segment, s_descriptor.d_base2) == OFFSET_SEGMENT_DESCRIPTOR_BASE2);
STATIC_ASSERT(sizeof(struct idt_segment) == SIZEOF_IDT_SEGMENT);


#include <kos/kernel/gdt.h>

STATIC_ASSERT(SEGMENT_IS_VALID_KERNCODE(SEGMENT_KERNEL_CODE));
STATIC_ASSERT(!SEGMENT_IS_VALID_KERNCODE(SEGMENT_USER_CODE));
STATIC_ASSERT(!SEGMENT_IS_VALID_KERNCODE(SEGMENT_USER_CODE_RPL));
STATIC_ASSERT(SEGMENT_IS_VALID_KERNDATA(SEGMENT_KERNEL_DATA));
STATIC_ASSERT(!SEGMENT_IS_VALID_KERNDATA(SEGMENT_USER_DATA));
STATIC_ASSERT(!SEGMENT_IS_VALID_KERNDATA(SEGMENT_USER_DATA_RPL));

STATIC_ASSERT(SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE));
STATIC_ASSERT(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA));

#ifndef __x86_64__
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_FSBASE_RPL));
STATIC_ASSERT(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_FSBASE_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_GSBASE_RPL));
STATIC_ASSERT(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_GSBASE_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_FSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_FSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_GSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_GSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS_DF));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS_DF));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS_DF | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS_DF | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_FSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_FSBASE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_FSBASE | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_FSBASE | 3));
#endif /* !__x86_64__ */

STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_CODE));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_DATA));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_KERNEL_CODE | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_KERNEL_DATA | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_TSS | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_TSS | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_LDT));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_LDT));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_CPU_LDT | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_CPU_LDT | 3));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(LDT_SEGMENT_SYSCALL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(LDT_SEGMENT_SYSCALL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(LDT_SEGMENT_SYSCALL_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(LDT_SEGMENT_SYSCALL_RPL));

#ifdef __x86_64__
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE32));
STATIC_ASSERT(SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_CODE32_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE32));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_CODE32_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA32));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERCODE(SEGMENT_USER_DATA32_RPL));
STATIC_ASSERT(!SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA32));
STATIC_ASSERT(SEGMENT_IS_VALID_USERDATA(SEGMENT_USER_DATA32_RPL));
#endif /* __x86_64__ */

#include <kos/bits/exception_data32.h>
#include <kos/bits/exception_data64.h>
STATIC_ASSERT(__SIZEOF_ERROR_CODE32_T__ == sizeof(error_code32_t));
STATIC_ASSERT(__SIZEOF_ERROR_CLASS32_T__ == sizeof(error_class32_t));
STATIC_ASSERT(__SIZEOF_ERROR_SUBCLASS32_T__ == sizeof(error_subclass32_t));
STATIC_ASSERT(__SIZEOF_ERROR_CODE64_T__ == sizeof(error_code64_t));
STATIC_ASSERT(__SIZEOF_ERROR_CLASS64_T__ == sizeof(error_class64_t));
STATIC_ASSERT(__SIZEOF_ERROR_SUBCLASS64_T__ == sizeof(error_subclass64_t));
STATIC_ASSERT(__SIZEOF_ERROR_CODE_T__ == sizeof(error_code_t));
STATIC_ASSERT(__SIZEOF_ERROR_CLASS_T__ == sizeof(error_class_t));
STATIC_ASSERT(__SIZEOF_ERROR_SUBCLASS_T__ == sizeof(error_subclass_t));

#endif /* !GUARD__VERIFY_ARCH_I386_ASSERT_TYPES_C */
