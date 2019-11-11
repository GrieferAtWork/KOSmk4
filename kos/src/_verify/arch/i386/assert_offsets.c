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
#ifndef GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C
#define GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>
#include <stddef.h>
#include <stdalign.h>


#include <ieee754.h>
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
	"../../../../include/i386-kos/bits/sigevent32.h",
	"../../../../include/i386-kos/bits/sigevent64.h",
	"../../../../include/i386-kos/bits/siginfo-struct32.h",
	"../../../../include/i386-kos/bits/siginfo-struct64.h",
	"../../../../include/i386-kos/bits/sigaction-struct-cygwin.h",
	"../../../../include/i386-kos/bits/sigaction-struct32.h",
	"../../../../include/i386-kos/bits/sigaction-struct64.h",
	"../../../../include/i386-kos/bits/sigstack32.h",
	"../../../../include/i386-kos/bits/sigstack64.h",
	"../../../../include/i386-kos/bits/sigval32.h",
	"../../../../include/i386-kos/bits/sigval64.h",
	"../../../../include/i386-kos/bits/timespec32.h",
	"../../../../include/i386-kos/bits/timespec64.h",
	"../../../../include/i386-kos/bits/timeval32.h",
	"../../../../include/i386-kos/bits/timeval64.h",
	"../../../../include/i386-kos/bits/va_list-struct32.h",
	"../../../../include/i386-kos/bits/va_list-struct64.h",
	"../../../../include/i386-kos/kos/bits/debugtrap32.h",
	"../../../../include/i386-kos/kos/bits/debugtrap64.h",
	"../../../../include/i386-kos/kos/bits/exception_data32.h",
	"../../../../include/i386-kos/kos/bits/exception_data64.h",
	"../../../../include/i386-kos/kos/bits/peb32.h",
	"../../../../include/i386-kos/kos/bits/peb64.h",
	"../../../../include/i386-kos/kos/bits/process32.h",
	"../../../../include/i386-kos/kos/bits/process64.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct32.h",
	"../../../../include/i386-kos/kos/bits/ukern-struct64.h",
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
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[{i}]) == OFFSET_XFPUSTATE32_ST({i}));".format({ .i = i });
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[{i}]) == OFFSET_XFPUSTATE32_MM({i}));".format({ .i = i });
}
for (local i: [:8])
	print "STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[{i}]) == OFFSET_XFPUSTATE32_XMM({i}));".format({ .i = i });
for (local i: [:8]) {
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[{i}]) == OFFSET_XFPUSTATE64_ST({i}));".format({ .i = i });
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[{i}]) == OFFSET_XFPUSTATE64_MM({i}));".format({ .i = i });
}
for (local i: [:16])
	print "STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[{i}]) == OFFSET_XFPUSTATE64_XMM({i}));".format({ .i = i });
for (local i: [1:8])
	print "STATIC_ASSERT(OFFSET_TSS64_IST{i} == OFFSET_TSS64_IST({i}));".format({ .i = i });
for (local i: [:16]) {
	print "#if X86_64_VA_LIST_XMM_COUNT >=",i;
	print "STATIC_ASSERT(offsetof(struct x86_64_va_list_reg_save_area, rsa_xmm[{i}]) == OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM({i}));".format({ .i = i });
	print "#endif";
}

]]]*/
#include <bits/sigevent32.h>

/* struct sigevent32 */
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_data) == __OFFSET_SIGEVENT32_DATA);
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_un._data) == __OFFSET_SIGEVENT32_DATA);
STATIC_ASSERT(offsetof(struct sigevent32, sigev_notify) == __OFFSET_SIGEVENT32_NOTIFY);
STATIC_ASSERT(offsetof(struct sigevent32, sigev_notify_attributes) == __OFFSET_SIGEVENT32_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENT32_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct sigevent32, sigev_notify_function) == __OFFSET_SIGEVENT32_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENT32_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct sigevent32, sigev_signo) == __OFFSET_SIGEVENT32_SIGNO);
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_tid) == __OFFSET_SIGEVENT32_TID);
STATIC_ASSERT(offsetof(struct sigevent32, _sigev_un._tid) == __OFFSET_SIGEVENT32_TID);
STATIC_ASSERT(offsetof(struct sigevent32, sigev_value) == __OFFSET_SIGEVENT32_VALUE);
STATIC_ASSERT(sizeof(struct sigevent32) == __SIZEOF_SIGEVENT32);





#include <bits/sigevent64.h>

/* struct sigevent64 */
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_data) == __OFFSET_SIGEVENT64_DATA);
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_un._data) == __OFFSET_SIGEVENT64_DATA);
STATIC_ASSERT(offsetof(struct sigevent64, sigev_notify) == __OFFSET_SIGEVENT64_NOTIFY);
STATIC_ASSERT(offsetof(struct sigevent64, sigev_notify_attributes) == __OFFSET_SIGEVENT64_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_un._sigev_thread._attribute) == __OFFSET_SIGEVENT64_NOTIFY_ATTRIBUTES);
STATIC_ASSERT(offsetof(struct sigevent64, sigev_notify_function) == __OFFSET_SIGEVENT64_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_un._sigev_thread._function) == __OFFSET_SIGEVENT64_NOTIFY_FUNCTION);
STATIC_ASSERT(offsetof(struct sigevent64, sigev_signo) == __OFFSET_SIGEVENT64_SIGNO);
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_tid) == __OFFSET_SIGEVENT64_TID);
STATIC_ASSERT(offsetof(struct sigevent64, _sigev_un._tid) == __OFFSET_SIGEVENT64_TID);
STATIC_ASSERT(offsetof(struct sigevent64, sigev_value) == __OFFSET_SIGEVENT64_VALUE);
STATIC_ASSERT(sizeof(struct sigevent64) == __SIZEOF_SIGEVENT64);





#include <bits/siginfo-struct32.h>

/* struct __siginfo32_struct */
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_addr) == __OFFSET_SIGINFO32_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFO32_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_addr_lsb) == __OFFSET_SIGINFO32_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFO32_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_arch) == __OFFSET_SIGINFO32_ARCH);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFO32_ARCH);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_band) == __OFFSET_SIGINFO32_BAND);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFO32_BAND);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_call_addr) == __OFFSET_SIGINFO32_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFO32_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_code) == __OFFSET_SIGINFO32_CODE);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _si_data) == __OFFSET_SIGINFO32_DATA);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._data) == __OFFSET_SIGINFO32_DATA);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_errno) == __OFFSET_SIGINFO32_ERRNO);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_fd) == __OFFSET_SIGINFO32_FD);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFO32_FD);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_int) == __OFFSET_SIGINFO32_INT);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFO32_INT);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_lower) == __OFFSET_SIGINFO32_LOWER);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFO32_LOWER);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_overrun) == __OFFSET_SIGINFO32_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFO32_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, __sig_si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, __cld_si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFO32_PID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_ptr) == __OFFSET_SIGINFO32_PTR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFO32_PTR);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_signo) == __OFFSET_SIGINFO32_SIGNO);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_status) == __OFFSET_SIGINFO32_STATUS);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFO32_STATUS);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_stime) == __OFFSET_SIGINFO32_STIME);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFO32_STIME);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_syscall) == __OFFSET_SIGINFO32_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFO32_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_timerid) == __OFFSET_SIGINFO32_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFO32_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, __sig_si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, __cld_si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFO32_UID);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_upper) == __OFFSET_SIGINFO32_UPPER);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFO32_UPPER);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_utime) == __OFFSET_SIGINFO32_UTIME);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFO32_UTIME);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, si_value) == __OFFSET_SIGINFO32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, __sig_si_sigval) == __OFFSET_SIGINFO32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFO32_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo32_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFO32_VALUE);





#include <bits/siginfo-struct64.h>

/* struct __siginfo64_struct */
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_addr) == __OFFSET_SIGINFO64_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigfault._si_addr) == __OFFSET_SIGINFO64_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_addr_lsb) == __OFFSET_SIGINFO64_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigfault._si_addr_lsb) == __OFFSET_SIGINFO64_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_arch) == __OFFSET_SIGINFO64_ARCH);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigsys._arch) == __OFFSET_SIGINFO64_ARCH);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_band) == __OFFSET_SIGINFO64_BAND);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigpoll._si_band) == __OFFSET_SIGINFO64_BAND);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_call_addr) == __OFFSET_SIGINFO64_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigsys._call_addr) == __OFFSET_SIGINFO64_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_code) == __OFFSET_SIGINFO64_CODE);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _si_data) == __OFFSET_SIGINFO64_DATA);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._data) == __OFFSET_SIGINFO64_DATA);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_errno) == __OFFSET_SIGINFO64_ERRNO);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_fd) == __OFFSET_SIGINFO64_FD);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigpoll._si_fd) == __OFFSET_SIGINFO64_FD);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_int) == __OFFSET_SIGINFO64_INT);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._timer.si_sigval.sival_int) == __OFFSET_SIGINFO64_INT);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_lower) == __OFFSET_SIGINFO64_LOWER);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigfault.si_addr_bnd._lower) == __OFFSET_SIGINFO64_LOWER);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_overrun) == __OFFSET_SIGINFO64_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._timer._si_overrun) == __OFFSET_SIGINFO64_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, __sig_si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, __cld_si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._kill._si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._rt._si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigchld._si_pid) == __OFFSET_SIGINFO64_PID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_ptr) == __OFFSET_SIGINFO64_PTR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._timer.si_sigval.sival_ptr) == __OFFSET_SIGINFO64_PTR);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_signo) == __OFFSET_SIGINFO64_SIGNO);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_status) == __OFFSET_SIGINFO64_STATUS);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigchld._si_status) == __OFFSET_SIGINFO64_STATUS);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_stime) == __OFFSET_SIGINFO64_STIME);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigchld._si_stime) == __OFFSET_SIGINFO64_STIME);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_syscall) == __OFFSET_SIGINFO64_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigsys._syscall) == __OFFSET_SIGINFO64_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_timerid) == __OFFSET_SIGINFO64_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._timer._si_tid) == __OFFSET_SIGINFO64_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, __sig_si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, __cld_si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._kill._si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._rt._si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigchld._si_uid) == __OFFSET_SIGINFO64_UID);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_upper) == __OFFSET_SIGINFO64_UPPER);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigfault.si_addr_bnd._upper) == __OFFSET_SIGINFO64_UPPER);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_utime) == __OFFSET_SIGINFO64_UTIME);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._sigchld._si_utime) == __OFFSET_SIGINFO64_UTIME);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, si_value) == __OFFSET_SIGINFO64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, __sig_si_sigval) == __OFFSET_SIGINFO64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._rt.si_sigval) == __OFFSET_SIGINFO64_VALUE);
STATIC_ASSERT(offsetof(struct __siginfo64_struct, _sifields._timer.si_sigval) == __OFFSET_SIGINFO64_VALUE);





#include <bits/sigaction-struct-cygwin.h>

/* struct __sigaction_cygwin */
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_flags) == __OFFSET_SIGACTION_CYGWIN_FLAGS);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_handler) == __OFFSET_SIGACTION_CYGWIN_HANDLER);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_mask) == __OFFSET_SIGACTION_CYGWIN_MASK);
STATIC_ASSERT(offsetof(struct __sigaction_cygwin, sa_sigaction) == __OFFSET_SIGACTION_CYGWIN_SIGACTION);





#include <bits/sigaction-struct32.h>

/* struct __sigset_struct32 */
/* ... */

/* struct sigaction32 */
STATIC_ASSERT(offsetof(struct sigaction32, sa_flags) == __OFFSET_SIGACTION32_FLAGS);
STATIC_ASSERT(offsetof(struct sigaction32, sa_handler) == __OFFSET_SIGACTION32_HANDLER);
STATIC_ASSERT(offsetof(struct sigaction32, sa_mask) == __OFFSET_SIGACTION32_MASK);
STATIC_ASSERT(offsetof(struct sigaction32, sa_restorer) == __OFFSET_SIGACTION32_RESTORER);
STATIC_ASSERT(offsetof(struct sigaction32, sa_sigaction) == __OFFSET_SIGACTION32_SIGACTION);
STATIC_ASSERT(sizeof(struct sigaction32) == __SIZEOF_SIGACTION32);
STATIC_ASSERT(alignof(struct sigaction32) == __ALIGNOF_SIGACTION32);





#include <bits/sigaction-struct64.h>

/* struct sigaction64 */
STATIC_ASSERT(offsetof(struct sigaction64, sa_flags) == __OFFSET_SIGACTION64_FLAGS);
STATIC_ASSERT(offsetof(struct sigaction64, sa_handler) == __OFFSET_SIGACTION64_HANDLER);
STATIC_ASSERT(offsetof(struct sigaction64, sa_mask) == __OFFSET_SIGACTION64_MASK);
STATIC_ASSERT(offsetof(struct sigaction64, sa_restorer) == __OFFSET_SIGACTION64_RESTORER);
STATIC_ASSERT(offsetof(struct sigaction64, sa_sigaction) == __OFFSET_SIGACTION64_SIGACTION);
STATIC_ASSERT(sizeof(struct sigaction64) == __SIZEOF_SIGACTION64);
STATIC_ASSERT(alignof(struct sigaction64) == __ALIGNOF_SIGACTION64);





#include <bits/sigstack32.h>

/* struct sigstack32 */
STATIC_ASSERT(offsetof(struct sigstack32, ss_sp) == __OFFSET_SIGSTACK32_SP);
STATIC_ASSERT(offsetof(struct sigstack32, ss_onstack) == __OFFSET_SIGSTACK32_ONSTACK);
STATIC_ASSERT(sizeof(struct sigstack32) == __SIZEOF_SIGSTACK32);

/* struct sigaltstack32 */
STATIC_ASSERT(offsetof(struct sigaltstack32, ss_flags) == __OFFSET_SIGALTSTACK32_FLAGS);
STATIC_ASSERT(offsetof(struct sigaltstack32, ss_size) == __OFFSET_SIGALTSTACK32_SIZE);
STATIC_ASSERT(offsetof(struct sigaltstack32, ss_sp) == __OFFSET_SIGALTSTACK32_SP);
STATIC_ASSERT(sizeof(struct sigaltstack32) == __SIZEOF_SIGALTSTACK32);





#include <bits/sigstack64.h>

/* struct sigstack64 */
STATIC_ASSERT(offsetof(struct sigstack64, ss_sp) == __OFFSET_SIGSTACK64_SP);
STATIC_ASSERT(offsetof(struct sigstack64, ss_onstack) == __OFFSET_SIGSTACK64_ONSTACK);

/* struct sigaltstack64 */
STATIC_ASSERT(offsetof(struct sigaltstack64, ss_flags) == __OFFSET_SIGALTSTACK64_FLAGS);
STATIC_ASSERT(offsetof(struct sigaltstack64, ss_size) == __OFFSET_SIGALTSTACK64_SIZE);
STATIC_ASSERT(offsetof(struct sigaltstack64, ss_sp) == __OFFSET_SIGALTSTACK64_SP);





#include <bits/sigval32.h>





#include <bits/sigval64.h>





#include <bits/timespec32.h>

/* struct timespec32 */
STATIC_ASSERT(offsetof(struct timespec32, tv_nsec) == __OFFSET_TIMESPEC32_NSEC);
STATIC_ASSERT(offsetof(struct timespec32, tv_sec) == __OFFSET_TIMESPEC32_SEC);
STATIC_ASSERT(sizeof(struct timespec32) == __SIZEOF_TIMESPEC32);

/* struct timespec32_64 */
STATIC_ASSERT(offsetof(struct timespec32_64, tv_sec) == __OFFSET_TIMESPEC32_64_SEC);
STATIC_ASSERT(offsetof(struct timespec32_64, tv_nsec) == __OFFSET_TIMESPEC32_64_NSEC);
STATIC_ASSERT(sizeof(struct timespec32_64) == __SIZEOF_TIMESPEC32_64);





#include <bits/timespec64.h>

/* struct timespecx64 */
STATIC_ASSERT(offsetof(struct timespecx64, tv_sec) == __OFFSET_TIMESPECX64_SEC);
STATIC_ASSERT(offsetof(struct timespecx64, tv_nsec) == __OFFSET_TIMESPECX64_NSEC);
STATIC_ASSERT(sizeof(struct timespecx64) == __SIZEOF_TIMESPECX64);





#include <bits/timeval32.h>

/* struct timeval32 */
STATIC_ASSERT(offsetof(struct timeval32, tv_sec) == __OFFSET_TIMEVAL32_SEC);
STATIC_ASSERT(offsetof(struct timeval32, tv_usec) == __OFFSET_TIMEVAL32_USEC);
STATIC_ASSERT(sizeof(struct timeval32) == __SIZEOF_TIMEVAL32);

/* struct timeval32_64 */
STATIC_ASSERT(offsetof(struct timeval32_64, tv_usec) == __OFFSET_TIMEVAL32_64_USEC);
STATIC_ASSERT(offsetof(struct timeval32_64, tv_sec) == __OFFSET_TIMEVAL32_64_SEC);
STATIC_ASSERT(sizeof(struct timeval32_64) == __SIZEOF_TIMEVAL32_64);





#include <bits/timeval64.h>

/* struct timevalx64 */
STATIC_ASSERT(offsetof(struct timevalx64, tv_usec) == __OFFSET_TIMEVALX64_USEC);
STATIC_ASSERT(offsetof(struct timevalx64, tv_sec) == __OFFSET_TIMEVALX64_SEC);
STATIC_ASSERT(sizeof(struct timevalx64) == __SIZEOF_TIMEVALX64);





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





#include <kos/bits/peb32.h>

/* struct process_peb32 */
STATIC_ASSERT(offsetof(struct process_peb32, pp_argc) == OFFSET_PROCESS_PEB32_ARGC);
STATIC_ASSERT(offsetof(struct process_peb32, pp_argv) == OFFSET_PROCESS_PEB32_ARGV);
STATIC_ASSERT(offsetof(struct process_peb32, pp_envc) == OFFSET_PROCESS_PEB32_ENVC);
STATIC_ASSERT(offsetof(struct process_peb32, pp_envp) == OFFSET_PROCESS_PEB32_ENVP);





#include <kos/bits/peb64.h>

/* struct process_peb64 */
STATIC_ASSERT(offsetof(struct process_peb64, pp_argc) == OFFSET_PROCESS_PEB64_ARGC);
STATIC_ASSERT(offsetof(struct process_peb64, pp_argv) == OFFSET_PROCESS_PEB64_ARGV);
STATIC_ASSERT(offsetof(struct process_peb64, pp_envc) == OFFSET_PROCESS_PEB64_ENVC);
STATIC_ASSERT(offsetof(struct process_peb64, pp_envp) == OFFSET_PROCESS_PEB64_ENVP);





#include <kos/bits/process32.h>

/* struct process_rtld_elf32 */
STATIC_ASSERT(offsetof(struct process_rtld_elf32, pr_phdr) == __OFFSET_PROCESS_RTLD_ELF32_PHDR);
STATIC_ASSERT(offsetof(struct process_rtld_elf32, pr_pnum) == __OFFSET_PROCESS_RTLD_ELF32_PNUM);
STATIC_ASSERT(offsetof(struct process_rtld_elf32, pr_rtldaddr) == __OFFSET_PROCESS_RTLD_ELF32_RTLDADDR);





#include <kos/bits/process64.h>

/* struct process_rtld_elf64 */
STATIC_ASSERT(offsetof(struct process_rtld_elf64, pr_phdr) == __OFFSET_PROCESS_RTLD_ELF64_PHDR);
STATIC_ASSERT(offsetof(struct process_rtld_elf64, pr_pnum) == __OFFSET_PROCESS_RTLD_ELF64_PNUM);
STATIC_ASSERT(offsetof(struct process_rtld_elf64, pr_rtldaddr) == __OFFSET_PROCESS_RTLD_ELF64_RTLDADDR);





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
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fcw) == OFFSET_SFPUENV_FCW);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fop) == OFFSET_SFPUENV_FOP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fpucs) == OFFSET_SFPUENV_FPUCS);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fpudp) == OFFSET_SFPUENV_FPUDP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fpuds) == OFFSET_SFPUENV_FPUDS);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fpuip) == OFFSET_SFPUENV_FPUIP);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_fsw) == OFFSET_SFPUENV_FSW);
STATIC_ASSERT(offsetof(struct sfpuenv, fe_ftw) == OFFSET_SFPUENV_FTW);
STATIC_ASSERT(sizeof(struct sfpuenv) == SIZEOF_SFPUENV);
STATIC_ASSERT(alignof(struct sfpuenv) == ALIGNOF_SFPUENV);

/* struct sfpustate */
STATIC_ASSERT(offsetof(struct sfpustate, fs_fcw) == OFFSET_SFPUSTATE_FCW);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fop) == OFFSET_SFPUSTATE_FOP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fpucs) == OFFSET_SFPUSTATE_FPUCS);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fpudp) == OFFSET_SFPUSTATE_FPUDP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fpuds) == OFFSET_SFPUSTATE_FPUDS);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fpuip) == OFFSET_SFPUSTATE_FPUIP);
STATIC_ASSERT(offsetof(struct sfpustate, fs_fsw) == OFFSET_SFPUSTATE_FSW);
STATIC_ASSERT(offsetof(struct sfpustate, fs_ftw) == OFFSET_SFPUSTATE_FTW);
STATIC_ASSERT(sizeof(struct sfpustate) == SIZEOF_SFPUSTATE);
STATIC_ASSERT(alignof(struct sfpustate) == ALIGNOF_SFPUSTATE);





#include <kos/kernel/fpu-state32.h>

/* struct xfpustate32 */
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fcw) == OFFSET_XFPUSTATE32_FCW);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fop) == OFFSET_XFPUSTATE32_FOP);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fpucs) == OFFSET_XFPUSTATE32_FPUCS);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fpudp) == OFFSET_XFPUSTATE32_FPUDP);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fpuds) == OFFSET_XFPUSTATE32_FPUDS);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fpuip) == OFFSET_XFPUSTATE32_FPUIP);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_fsw) == OFFSET_XFPUSTATE32_FSW);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_ftw) == OFFSET_XFPUSTATE32_FTW);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_mxcsr) == OFFSET_XFPUSTATE32_MXCSR);
STATIC_ASSERT(offsetof(struct xfpustate32, fs_mxcsr_mask) == OFFSET_XFPUSTATE32_MXCSR_MASK);
STATIC_ASSERT(sizeof(struct xfpustate32) == SIZEOF_XFPUSTATE32);
STATIC_ASSERT(alignof(struct xfpustate32) == ALIGNOF_XFPUSTATE32);

/* struct fpustate32 */
STATIC_ASSERT(sizeof(struct fpustate32) == SIZEOF_FPUSTATE32);
STATIC_ASSERT(alignof(struct fpustate32) == ALIGNOF_FPUSTATE32);





#include <kos/kernel/fpu-state64.h>

/* struct xfpustate64 */
STATIC_ASSERT(offsetof(struct xfpustate64, fs_fcw) == OFFSET_XFPUSTATE64_FCW);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_fop) == OFFSET_XFPUSTATE64_FOP);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_fpudp) == OFFSET_XFPUSTATE64_FPUDP);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_fpuip) == OFFSET_XFPUSTATE64_FPUIP);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_fsw) == OFFSET_XFPUSTATE64_FSW);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_ftw) == OFFSET_XFPUSTATE64_FTW);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_mxcsr) == OFFSET_XFPUSTATE64_MXCSR);
STATIC_ASSERT(offsetof(struct xfpustate64, fs_mxcsr_mask) == OFFSET_XFPUSTATE64_MXCSR_MASK);
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

/* struct __sigset_struct32 */
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
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[0]) == OFFSET_XFPUSTATE32_ST(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[0]) == OFFSET_XFPUSTATE32_MM(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[1]) == OFFSET_XFPUSTATE32_ST(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[1]) == OFFSET_XFPUSTATE32_MM(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[2]) == OFFSET_XFPUSTATE32_ST(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[2]) == OFFSET_XFPUSTATE32_MM(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[3]) == OFFSET_XFPUSTATE32_ST(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[3]) == OFFSET_XFPUSTATE32_MM(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[4]) == OFFSET_XFPUSTATE32_ST(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[4]) == OFFSET_XFPUSTATE32_MM(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[5]) == OFFSET_XFPUSTATE32_ST(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[5]) == OFFSET_XFPUSTATE32_MM(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[6]) == OFFSET_XFPUSTATE32_ST(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[6]) == OFFSET_XFPUSTATE32_MM(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[7]) == OFFSET_XFPUSTATE32_ST(7));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_regs[7]) == OFFSET_XFPUSTATE32_MM(7));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[0]) == OFFSET_XFPUSTATE32_XMM(0));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[1]) == OFFSET_XFPUSTATE32_XMM(1));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[2]) == OFFSET_XFPUSTATE32_XMM(2));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[3]) == OFFSET_XFPUSTATE32_XMM(3));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[4]) == OFFSET_XFPUSTATE32_XMM(4));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[5]) == OFFSET_XFPUSTATE32_XMM(5));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[6]) == OFFSET_XFPUSTATE32_XMM(6));
STATIC_ASSERT(offsetof(struct xfpustate32, fs_xmm[7]) == OFFSET_XFPUSTATE32_XMM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[0]) == OFFSET_XFPUSTATE64_ST(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[0]) == OFFSET_XFPUSTATE64_MM(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[1]) == OFFSET_XFPUSTATE64_ST(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[1]) == OFFSET_XFPUSTATE64_MM(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[2]) == OFFSET_XFPUSTATE64_ST(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[2]) == OFFSET_XFPUSTATE64_MM(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[3]) == OFFSET_XFPUSTATE64_ST(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[3]) == OFFSET_XFPUSTATE64_MM(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[4]) == OFFSET_XFPUSTATE64_ST(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[4]) == OFFSET_XFPUSTATE64_MM(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[5]) == OFFSET_XFPUSTATE64_ST(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[5]) == OFFSET_XFPUSTATE64_MM(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[6]) == OFFSET_XFPUSTATE64_ST(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[6]) == OFFSET_XFPUSTATE64_MM(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[7]) == OFFSET_XFPUSTATE64_ST(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_regs[7]) == OFFSET_XFPUSTATE64_MM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[0]) == OFFSET_XFPUSTATE64_XMM(0));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[1]) == OFFSET_XFPUSTATE64_XMM(1));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[2]) == OFFSET_XFPUSTATE64_XMM(2));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[3]) == OFFSET_XFPUSTATE64_XMM(3));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[4]) == OFFSET_XFPUSTATE64_XMM(4));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[5]) == OFFSET_XFPUSTATE64_XMM(5));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[6]) == OFFSET_XFPUSTATE64_XMM(6));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[7]) == OFFSET_XFPUSTATE64_XMM(7));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[8]) == OFFSET_XFPUSTATE64_XMM(8));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[9]) == OFFSET_XFPUSTATE64_XMM(9));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[10]) == OFFSET_XFPUSTATE64_XMM(10));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[11]) == OFFSET_XFPUSTATE64_XMM(11));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[12]) == OFFSET_XFPUSTATE64_XMM(12));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[13]) == OFFSET_XFPUSTATE64_XMM(13));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[14]) == OFFSET_XFPUSTATE64_XMM(14));
STATIC_ASSERT(offsetof(struct xfpustate64, fs_xmm[15]) == OFFSET_XFPUSTATE64_XMM(15));
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

#endif /* !GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C */
