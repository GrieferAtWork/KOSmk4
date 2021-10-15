/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* Disable warnings emit by some headers under certain circumstances. */
#define __NO_WARNINGS 1


/* In order to  ensure that all  of our system  headers work nice  with each  other,
 * try to include every single one at the same time in the following configurations:
 *   - <nothing>
 *   - _EVERY_SOURCE
 *   - __cplusplus
 *   - __cplusplus, _EVERY_SOURCE
 *   - __CRT_FREESTANDING
 *   - __CRT_FREESTANDING, _EVERY_SOURCE
 *   - __CRT_FREESTANDING, __cplusplus
 *   - __CRT_FREESTANDING, __cplusplus, _EVERY_SOURCE
 *   - _ISOC_PURE_SOURCE
 *   - _ISOC_PURE_SOURCE, _EVERY_SOURCE
 *   - _ISOC_PURE_SOURCE, __cplusplus
 *   - _ISOC_PURE_SOURCE, __cplusplus, _EVERY_SOURCE
 *   - __KERNEL__
 *   - __KERNEL__, _EVERY_SOURCE
 *   - __KERNEL__, __cplusplus
 *   - __KERNEL__, __cplusplus, _EVERY_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__
 *   - __CRT_FREESTANDING, __KERNEL__, _EVERY_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus, _EVERY_SOURCE
 *   - _ISOC_PURE_SOURCE, __KERNEL__
 *   - _ISOC_PURE_SOURCE, __KERNEL__, _EVERY_SOURCE
 *   - _ISOC_PURE_SOURCE, __KERNEL__, __cplusplus
 *   - _ISOC_PURE_SOURCE, __KERNEL__, __cplusplus, _EVERY_SOURCE
 * NOTE: The __KERNEL__ variants are achieved by include all *.c  files
 *       twice, once as part of the kernel core, and once again as part
 *       of /bin/system-test
 */

/*[[[deemon
import fs;
import * from deemon;

local badFiles = List({
	"__stdcxx.h",
	"hybrid/__atomic-gasm.h",
	"hybrid/__atomic-libatomic.h",
	"hybrid/__atomic-msvc.h",
	"hybrid/sequence/atree-abi.h",
	"hybrid/sequence/rbtree-abi.h",
	"hybrid/__pointer-cxx-impl.h",
	"hybrid/sync/service-lock.h",
	"asm/os/",
	"bits/os/",
	"compat/asm/os/",
	"compat/bits/os/",
	"i386-kos",
	"libc/local",
	"libc/template",
	"c++",
	"compiler",
	"crt-features",
	"libdl/module.h",
	"system-test/ctest.h",
});

// Include everything from the .gitignore
for (local l: File.open("../../../.gitignore", "r")) {
	l = l.strip();
	if (!l || l.startswith("#"))
		continue;
	l = l.strip("/");
	if (!l.startswith("kos/"))
		continue;
	l = l[4:].lstrip("/");
	if (!l.startswith("include/"))
		continue;
	l = l[8:].lstrip("/");
	badFiles.append(l);
}


final global INCLUDE_PATH = "../../include/";
function incdir(path) {
	for (local x: fs.dir(INCLUDE_PATH + path).sorted()) {
		if (x in ["__ice__"])
			continue;
		x = fs.joinpath(path, x).replace("\\", "/");
		if (x in badFiles)
			continue;
		if (fs.stat.isdir(INCLUDE_PATH + x)) {
			if ((path + "/") in badFiles)
				continue;
			incdir(x);
			continue;
		}
		if (!x.endswith(".h"))
			continue;
		print("#include <", x, ">");
	}
}
incdir("");

]]]*/
#include <ConcurrencySal.h>
#include <__crt.h>
#include <__stdinc.h>
#include <_ansi.h>
#include <_lfs_64.h>
#include <aio.h>
#include <aliases.h>
#include <alloc.h>
#include <alloca.h>
#include <ansidecl.h>
#include <ar.h>
#include <argz.h>
#include <arpa/inet.h>
#include <asm/__stdinc.h>
#include <asm/asmword.h>
#include <asm/cacheline.h>
#include <asm/crt/aio.h>
#include <asm/crt/confname.h>
#include <asm/crt/getpassfd.h>
#include <asm/crt/glob.h>
#include <asm/crt/humanize_number.h>
#include <asm/crt/limits.h>
#include <asm/crt/locale.h>
#include <asm/crt/malloc.h>
#include <asm/crt/math-exception.h>
#include <asm/crt/math-libc_version.h>
#include <asm/crt/posix_spawn.h>
#include <asm/crt/process.h>
#include <asm/crt/pthreadvalues.h>
#include <asm/crt/readpassphrase.h>
#include <asm/crt/semaphore.h>
#include <asm/crt/stdio.h>
#include <asm/crt/stdio_ext.h>
#include <asm/crt/stdlib.h>
#include <asm/crt/threads.h>
#include <asm/crt/time.h>
#include <asm/crt/ttyent.h>
#include <asm/crt/ucontext.h>
#include <asm/crt/util.h>
#include <asm/fp_type.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#include <asm/ioctl.h>
#include <asm/ls-syscalls.h>
#include <asm/os/block.h>
#include <asm/os/clock.h>
#include <asm/os/dirent.h>
#include <asm/os/epoll.h>
#include <asm/os/errno.h>
#include <asm/os/eventfd.h>
#include <asm/os/fcntl.h>
#include <asm/os/fd_set.h>
#include <asm/os/ipc.h>
#include <asm/os/itimer.h>
#include <asm/os/limits.h>
#include <asm/os/mman.h>
#include <asm/os/mount.h>
#include <asm/os/msq.h>
#include <asm/os/oflags.h>
#include <asm/os/paths.h>
#include <asm/os/poll.h>
#include <asm/os/ptrace.h>
#include <asm/os/random.h>
#include <asm/os/reboot.h>
#include <asm/os/resource.h>
#include <asm/os/sched.h>
#include <asm/os/sem.h>
#include <asm/os/shm.h>
#include <asm/os/sigevent.h>
#include <asm/os/siginfo.h>
#include <asm/os/signal.h>
#include <asm/os/signalfd.h>
#include <asm/os/sigset.h>
#include <asm/os/sigstack.h>
#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#include <asm/os/stat.h>
#include <asm/os/statvfs.h>
#include <asm/os/stdio.h>
#include <asm/os/stdlib.h>
#include <asm/os/stropts.h>
#include <asm/os/swap.h>
#include <asm/os/syslog.h>
#include <asm/os/termios.h>
#include <asm/os/timerfd.h>
#include <asm/os/timex.h>
#include <asm/os/tty.h>
#include <asm/os/ulimit.h>
#include <asm/os/utsname.h>
#include <asm/os/vfork.h>
#include <asm/os/wait.h>
#include <asm/os/xattr.h>
#include <asm/page.h>
#include <asm/pageid.h>
#include <asm/pagesize.h>
#include <asm/pkey.h>
#include <asm/signed-shift.h>
#include <asm/syscalls-proto.h>
#include <asm/syscalls-trace.h>
#include <asm/syscalls-types.h>
#include <asm/syscalls.h>
#include <asm/unistd.h>
#include <assert.h>
#include <attr/xattr.h>
#include <bits/crt/_diskfree_t.h>
#include <bits/crt/aiocb.h>
#include <bits/crt/aioinit.h>
#include <bits/crt/crypt_data.h>
#include <bits/crt/ctype.h>
#include <bits/crt/db/aliases.h>
#include <bits/crt/db/group.h>
#include <bits/crt/db/mntent.h>
#include <bits/crt/db/netdb.h>
#include <bits/crt/db/passwd.h>
#include <bits/crt/db/rpcent.h>
#include <bits/crt/db/spwd.h>
#include <bits/crt/db/ttyent.h>
#include <bits/crt/db/utmp.h>
#include <bits/crt/db/utmpx.h>
#include <bits/crt/environments.h>
#include <bits/crt/fenv-inline.h>
#include <bits/crt/fenv.h>
#include <bits/crt/format-printer.h>
#include <bits/crt/fts.h>
#include <bits/crt/ftw.h>
#include <bits/crt/glob.h>
#include <bits/crt/ifaddrs.h>
#include <bits/crt/inttypes.h>
#include <bits/crt/io-file.h>
#include <bits/crt/lconv.h>
#include <bits/crt/locale.h>
#include <bits/crt/math-vector.h>
#include <bits/crt/mathdef.h>
#include <bits/crt/mbstate.h>
#include <bits/crt/ntptimeval.h>
#include <bits/crt/posix_spawn.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/crt/pthreadtypesizes.h>
#include <bits/crt/semaphore.h>
#include <bits/crt/setjmp.h>
#include <bits/crt/stdio.h>
#include <bits/crt/sys_errlist.h>
#include <bits/crt/threads.h>
#include <bits/crt/tm.h>
#include <bits/crt/uformat-printer.h>
#include <bits/crt/unicode.h>
#include <bits/crt/wctype.h>
#include <bits/crt/wformat-printer.h>
#include <bits/elf-types.h>
#include <bits/elf.h>
#include <bits/math-constants.h>
#include <bits/os/acct.h>
#include <bits/os/cmsghdr.h>
#include <bits/os/cpu_set.h>
#include <bits/os/dirent.h>
#include <bits/os/epoll.h>
#include <bits/os/f_owner_ex.h>
#include <bits/os/fd_set.h>
#include <bits/os/file_handle.h>
#include <bits/os/flock.h>
#include <bits/os/iovec.h>
#include <bits/os/ipc.h>
#include <bits/os/itimerspec.h>
#include <bits/os/itimerval.h>
#include <bits/os/linger.h>
#include <bits/os/mcontext.h>
#include <bits/os/mmsghdr.h>
#include <bits/os/mqueue.h>
#include <bits/os/msgbuf.h>
#include <bits/os/msghdr.h>
#include <bits/os/msq.h>
#include <bits/os/pollfd.h>
#include <bits/os/ptrace.h>
#include <bits/os/rlimit.h>
#include <bits/os/rusage-convert.h>
#include <bits/os/rusage.h>
#include <bits/os/sched.h>
#include <bits/os/sem.h>
#include <bits/os/sembuf.h>
#include <bits/os/shm.h>
#include <bits/os/sigaction.h>
#include <bits/os/sigcontext.h>
#include <bits/os/sigevent.h>
#include <bits/os/siginfo.h>
#include <bits/os/signalfd_siginfo.h>
#include <bits/os/sigset.h>
#include <bits/os/sigstack.h>
#include <bits/os/sigval.h>
#include <bits/os/sockaddr-common.h>
#include <bits/os/sockaddr.h>
#include <bits/os/sockaddr_storage.h>
#include <bits/os/stat.h>
#include <bits/os/statfs-convert.h>
#include <bits/os/statfs.h>
#include <bits/os/statvfs.h>
#include <bits/os/stropts.h>
#include <bits/os/termio.h>
#include <bits/os/termios.h>
#include <bits/os/termiox.h>
#include <bits/os/timeb.h>
#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <bits/os/timex.h>
#include <bits/os/tms.h>
#include <bits/os/ucontext.h>
#include <bits/os/ucred.h>
#include <bits/os/ustat.h>
#include <bits/os/utimbuf.h>
#include <bits/os/utsname.h>
#include <bits/os/wait.h>
#include <bits/os_defines.h>
#include <bits/posix_lim1.h>
#include <bits/posix_lim2.h>
#include <bits/posix_opt.h>
#include <bits/pthreadtypes.h>
#include <bits/sigset.h>
#include <bits/sockaddr.h>
#include <bits/syscalls.h>
#include <bits/timex.h>
#include <bits/types/FILE.h>
#include <bits/types/__FILE.h>
#include <bits/types/__fpos64_t.h>
#include <bits/types/__fpos_t.h>
#include <bits/types/__locale_t.h>
#include <bits/types/__mbstate_t.h>
#include <bits/types/__sigset_t.h>
#include <bits/types/__sigval_t.h>
#include <bits/types/clock_t.h>
#include <bits/types/clockid_t.h>
#include <bits/types/cookie_io_functions_t.h>
#include <bits/types/locale_t.h>
#include <bits/types/mbstate_t.h>
#include <bits/types/sig_atomic_t.h>
#include <bits/types/sigevent_t.h>
#include <bits/types/siginfo_t.h>
#include <bits/types/sigset_t.h>
#include <bits/types/sigval_t.h>
#include <bits/types/stack_t.h>
#include <bits/types/struct_iovec.h>
#include <bits/types/struct_itimerspec.h>
#include <bits/types/struct_osockaddr.h>
#include <bits/types/struct_rusage.h>
#include <bits/types/struct_sigstack.h>
#include <bits/types/struct_timespec.h>
#include <bits/types/struct_timeval.h>
#include <bits/types/struct_tm.h>
#include <bits/types/time_t.h>
#include <bits/types/timer_t.h>
#include <bits/types/wint_t.h>
#include <bits/types.h>
#include <bits/typesizes.h>
#include <bits/wchar.h>
#include <bits/wordsize.h>
#include <bits/xopen_lim.h>
#include <bitstring.h>
#include <bsd/bitstring.h>
#include <bsd/bsd.h>
#include <bsd/err.h>
#include <bsd/errno.h>
#include <bsd/getopt.h>
#include <bsd/grp.h>
#include <bsd/inttypes.h>
#include <bsd/libutil.h>
#include <bsd/pwd.h>
#include <bsd/readpassphrase.h>
#include <bsd/sgtty.h>
#include <bsd/signal.h>
#include <bsd/stdio.h>
#include <bsd/stdlib.h>
#include <bsd/string.h>
#include <bsd/stringlist.h>
#include <bsd/sys/bitstring.h>
#include <bsd/sys/cdefs.h>
#include <bsd/sys/endian.h>
#include <bsd/sys/param.h>
#include <bsd/sys/poll.h>
#include <bsd/sys/queue.h>
#include <bsd/sys/time.h>
#include <bsd/sys/ttychars.h>
#include <bsd/tzfile.h>
#include <bsd/unistd.h>
#include <bsd/wchar.h>
#include <bstring.h>
#include <bytesex.h>
#include <byteswap.h>
#include <compat/bits/os/cmsghdr.h>
#include <compat/bits/os/flock.h>
#include <compat/bits/os/iovec.h>
#include <compat/bits/os/itimerspec.h>
#include <compat/bits/os/itimerval.h>
#include <compat/bits/os/mcontext.h>
#include <compat/bits/os/mmsghdr.h>
#include <compat/bits/os/msghdr.h>
#include <compat/bits/os/rusage-convert.h>
#include <compat/bits/os/rusage.h>
#include <compat/bits/os/sigaction.h>
#include <compat/bits/os/sigevent.h>
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/bits/os/sigset.h>
#include <compat/bits/os/sigstack.h>
#include <compat/bits/os/sigval.h>
#include <compat/bits/os/stat-convert.h>
#include <compat/bits/os/stat.h>
#include <compat/bits/os/statfs-convert.h>
#include <compat/bits/os/statfs.h>
#include <compat/bits/os/timeb.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/bits/os/tms.h>
#include <compat/bits/os/ucontext.h>
#include <compat/bits/os/utimbuf.h>
#include <compat/bits/types.h>
#include <compat/bits/typesizes.h>
#include <compat/bits/va_list-struct.h>
#include <compat/config.h>
#include <compat/kos/bits/coredump.h>
#include <compat/kos/bits/except-handler.h>
#include <compat/kos/bits/futex-expr.h>
#include <compat/kos/bits/futex.h>
#include <compat/kos/bits/syscall-info.h>
#include <compat/kos/compat/linux-dirent.h>
#include <compat/kos/compat/linux-olddirent.h>
#include <compat/kos/compat/linux-oldselect.h>
#include <compat/kos/compat/linux-stat.h>
#include <compat/kos/except-handler.h>
#include <compat/kos/exec/asm/elf.h>
#include <compat/kos/exec/asm/rtld.h>
#include <compat/kos/exec/bits/elf.h>
#include <compat/kos/exec/bits/peb.h>
#include <compat/kos/exec/elf.h>
#include <compat/kos/exec/peb.h>
#include <compat/kos/exec/rtld.h>
#include <compat/kos/futex.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#include <compat/sys/ucontext.h>
#include <complex.h>
#include <confname.h>
#include <confstr.h>
#include <corecrt.h>
#include <cpio.h>
#include <crtdbg.h>
#include <crtdefs.h>
#include <crypt.h>
#include <ctype.h>
#include <daemon.h>
#include <dir.h>
#include <direct.h>
#include <dirent.h>
#include <dlfcn.h>
#include <dos.h>
#include <elf.h>
#include <elf_abi.h>
#include <endian.h>
#include <envz.h>
#include <err.h>
#include <errno.h>
#include <error.h>
#include <execinfo.h>
#include <fastmath.h>
#include <fcntl.h>
#include <features.h>
#include <fenv.h>
#include <file.h>
#include <float.h>
#include <fnmatch.h>
#include <format-printer.h>
#include <fts.h>
#include <ftw.h>
#include <getopt.h>
#include <getpagesize.h>
#include <glob.h>
#include <gnu/lib-names.h>
#include <gnu/stubs.h>
#include <grp.h>
#include <huge_val.h>
#include <hw/bus/pci.h>
#include <hw/bus/serial.h>
#include <hw/disk/ata.h>
#include <hw/disk/scsi.h>
#include <hw/hid/ps2.h>
#include <hw/hid/usb-hid.h>
#include <hw/hid/usbkbd.h>
#include <hw/ic/apic.h>
#include <hw/ic/pic.h>
#include <hw/net/ne2k.h>
#include <hw/rtc/cmos.h>
#include <hw/timer/pit.h>
#include <hw/usb/class.h>
#include <hw/usb/hub.h>
#include <hw/usb/ohci.h>
#include <hw/usb/uhci.h>
#include <hw/usb/usb.h>
#include <hw/video/vga.h>
#include <hybrid/__alloca.h>
#include <hybrid/__altint.h>
#include <hybrid/__asm.h>
#include <hybrid/__assembly.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__bit.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__debug-alignment.h>
#include <hybrid/__minmax.h>
#include <hybrid/__overflow.h>
#include <hybrid/__pointer.h>
#include <hybrid/__rotate.h>
#include <hybrid/__unaligned.h>
#include <hybrid/__va_size.h>
#include <hybrid/__wordbits.h>
#include <hybrid/align.h>
#include <hybrid/alloca.h>
#include <hybrid/altint.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/compiler.h>
#include <hybrid/debug-alignment.h>
#include <hybrid/floatcore.h>
#include <hybrid/host.h>
#include <hybrid/int128.h>
#include <hybrid/limitcore.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/pointer.h>
#include <hybrid/pp/__bubble.h>
#include <hybrid/pp/__va_nargs.h>
#include <hybrid/pp/bubble.h>
#include <hybrid/sched/__gettid.h>
#include <hybrid/sched/__yield.h>
#include <hybrid/sched/yield.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/bitset.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sequence/vector.h>
#include <hybrid/struct.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-once.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>
#include <iconv.h>
#include <ieee754.h>
#include <ieee854.h>
#include <ieeefp.h>
#include <ifaddrs.h>
#include <int128.h>
#include <inttypes.h>
#include <io.h>
#include <iso646.h>
#include <jmp_buf.h>
#include <kos/anno.h>
#include <kos/aref.h>
#include <kos/asm/rpc.h>
#include <kos/asm/rtm.h>
#include <kos/asm/syscall.h>
#include <kos/bits/coredump.h>
#include <kos/bits/debugtrap.h>
#include <kos/bits/except-handler.h>
#include <kos/bits/except.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_info.h>
#include <kos/bits/exception_nest.h>
#include <kos/bits/fastexcept.h>
#include <kos/bits/futex-expr.h>
#include <kos/bits/futex.h>
#include <kos/bits/lockop.h>
#include <kos/bits/rtm.h>
#include <kos/bits/syscall-info.h>
#include <kos/bits/thread.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern.h>
#include <kos/bits/userprocmask.h>
#include <kos/capability.h>
#include <kos/compat/linux-dirent.h>
#include <kos/compat/linux-dirent64.h>
#include <kos/compat/linux-olddirent.h>
#include <kos/compat/linux-oldselect.h>
#include <kos/compat/linux-stat.h>
#include <kos/coredump.h>
#include <kos/debugtrap.h>
#include <kos/dev.h>
#include <kos/except/asm/codes.h>
#include <kos/except/codes.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/except/reason/net.h>
#include <kos/except/reason/noexec.h>
#include <kos/except-handler.h>
#include <kos/except.h>
#include <kos/exec/asm/elf.h>
#include <kos/exec/asm/rtld.h>
#include <kos/exec/bits/peb.h>
#include <kos/exec/elf-rel.h>
#include <kos/exec/elf.h>
#include <kos/exec/idata.h>
#include <kos/exec/lazybind.h>
#include <kos/exec/module.h>
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h>
#include <kos/fcntl.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/futexlock.h>
#include <kos/guid.h>
#include <kos/hop/api.h>
#include <kos/hop/blkdev.h>
#include <kos/hop/filehandle.h>
#include <kos/hop/futex.h>
#include <kos/hop/handle.h>
#include <kos/hop/mfile.h>
#include <kos/hop/module.h>
#include <kos/hop/mpart.h>
#include <kos/hop/openfd.h>
#include <kos/hop/path.h>
#include <kos/hop/pidns.h>
#include <kos/hop/pipe.h>
#include <kos/hop/task.h>
#include <kos/hybrid/heap.h>
#include <kos/hybrid/sched-signal.h>
#include <kos/io.h>
#include <kos/ioctl/clock.h>
#include <kos/ioctl/keyboard.h>
#include <kos/ioctl/mouse.h>
#include <kos/ioctl/tty.h>
#include <kos/ioctl/video.h>
#include <kos/kernel/handle.h>
#include <kos/kernel/memory.h>
#include <kos/kernel/syscalls.h>
#include <kos/kernel/types.h>
#include <kos/keyboard.h>
#include <kos/ksysctl.h>
#include <kos/lockop.h>
#include <kos/malloc.h>
#include <kos/malloca.h>
#include <kos/net/printf.h>
#include <kos/parts/malloca.h>
#include <kos/personality.h>
#include <kos/refcnt-nonatomic.h>
#include <kos/refcnt.h>
#include <kos/refptr.h>
#include <kos/rpc.h>
#include <kos/rtm.h>
#include <kos/sys/epoll.h>
#include <kos/sys/ioctl.h>
#include <kos/sys/mman.h>
#include <kos/sys/socket.h>
#include <kos/sys/stat.h>
#include <kos/syscalls.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <kos/ukern.h>
#include <kos/unistd.h>
#include <lastlog.h>
#include <libansitty/ansitty.h>
#include <libansitty/api.h>
#include <libansitty/ctl.h>
#include <libbuffer/api.h>
#include <libbuffer/linebuffer.h>
#include <libbuffer/packetbuffer.h>
#include <libbuffer/ringbuffer.h>
#include <libc/core/ctype.h>
#include <libc/core/errno.h>
#include <libc/core/error.h>
#include <libc/core/fenv.h>
#include <libc/core/kos.malloc.h>
#include <libc/core/malloc.h>
#include <libc/core/parts.uchar.string.h>
#include <libc/core/signal.h>
#include <libc/core/ssp.string.h>
#include <libc/core/stdlib.h>
#include <libc/core/string.h>
#include <libc/core/strings.h>
#include <libc/core/unicode.h>
#include <libc/core/unistd.h>
#include <libc/ctype.h>
#include <libc/errno.h>
#include <libc/error.h>
#include <libc/fenv.h>
#include <libc/kos.malloc.h>
#include <libc/malloc.h>
#include <libc/parts.uchar.string.h>
#include <libc/signal.h>
#include <libc/ssp.string.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <libc/strings.h>
#include <libc/unicode.h>
#include <libc/unistd.h>
#include <libcmdline/api.h>
#include <libcmdline/decode.h>
#include <libcmdline/encode.h>
#include <libcpustate/api.h>
#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/api.h>
#include <libdebuginfo/cfi_entry.h>
#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_frame.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>
#include <libdebuginfo/symtab.h>
#include <libdebuginfo/unwind.h>
#include <libdemangle/api.h>
#include <libdemangle/demangle.h>
#include <libdemangle/gcc.h>
#include <libdisasm/api.h>
#include <libdisasm/disassembler.h>
#include <libdisasm/format.h>
#include <libdl/api.h>
#include <libdl/asm/dlfcn.h>
#include <libdl/bits/dlfcn.h>
#include <libdl/extension.h>
#include <libemu86/api.h>
#include <libemu86/eflags.h>
#include <libemu86/emu/push-pop-util.h>
#include <libemu86/emu/string-util.h>
#include <libemu86/emu86.h>
#include <libemu86/helpers.h>
#include <libgen.h>
#include <libgen86/api.h>
#include <libgen86/gen.h>
#include <libgen86/register.h>
#include <libiconv/api.h>
#include <libiconv/codec.h>
#include <libiconv/iconv.h>
#include <libiconv/stdiconv.h>
#include <libiconv/transliterate.h>
#include <libinstrlen/api.h>
#include <libinstrlen/bits/isa.h>
#include <libinstrlen/instrlen.h>
#include <libintl.h>
#include <libio.h>
#include <libjson/api.h>
#include <libjson/generator.h>
#include <libjson/parser.h>
#include <libjson/writer.h>
#include <libkeymap/api.h>
#include <libkeymap/keymap.h>
#include <libm/api.h>
#include <libm/asm/_builtin.h>
#include <libm/asm/atan.h>
#include <libm/asm/atan2.h>
#include <libm/asm/builtin.h>
#include <libm/asm/ceil.h>
#include <libm/asm/exp.h>
#include <libm/asm/expm1.h>
#include <libm/asm/fabs.h>
#include <libm/asm/fcomp.h>
#include <libm/asm/floor.h>
#include <libm/asm/inf.h>
#include <libm/asm/lrint.h>
#include <libm/asm/lround.h>
#include <libm/asm/nan.h>
#include <libm/asm/rint.h>
#include <libm/asm/round.h>
#include <libm/asm/significand.h>
#include <libm/asm/sqrt.h>
#include <libm/asm/trunc.h>
#include <libm/atan.h>
#include <libm/atan2.h>
#include <libm/cbrt.h>
#include <libm/ceil.h>
#include <libm/copysign.h>
#include <libm/exp.h>
#include <libm/expm1.h>
#include <libm/fabs.h>
#include <libm/fcomp.h>
#include <libm/fdlibm.h>
#include <libm/finite.h>
#include <libm/floor.h>
#include <libm/fmod.h>
#include <libm/fpclassify.h>
#include <libm/frexp.h>
#include <libm/ilogb.h>
#include <libm/inf.h>
#include <libm/isinf.h>
#include <libm/isnan.h>
#include <libm/issignaling.h>
#include <libm/ldexp.h>
#include <libm/lrint.h>
#include <libm/lround.h>
#include <libm/matherr.h>
#include <libm/modf.h>
#include <libm/nan.h>
#include <libm/nextafter.h>
#include <libm/nexttoward.h>
#include <libm/pow.h>
#include <libm/remainder.h>
#include <libm/rint.h>
#include <libm/round.h>
#include <libm/scalb.h>
#include <libm/scalbn.h>
#include <libm/signbit.h>
#include <libm/significand.h>
#include <libm/sqrt.h>
#include <libm/trunc.h>
#include <libpciaccess/api.h>
#include <libpciaccess/config.h>
#include <libpciaccess/paths.h>
#include <libpciaccess/pciaccess.h>
#include <libphys/api.h>
#include <libphys/phys.h>
#include <libregdump/api.h>
#include <libregdump/printer.h>
#include <libregdump/register.h>
#include <libregex/api.h>
#include <libregex/regex.h>
#include <libsctrace/api.h>
#include <libsctrace/repr-types.h>
#include <libsctrace/sctrace.h>
#include <libservice/api.h>
#include <libservice/client.h>
#include <libservice/server.h>
#include <libservice/types.h>
#include <libterm/api.h>
#include <libterm/termio.h>
#include <libunwind/api.h>
#include <libunwind/arch-register.h>
#include <libunwind/cfi/i386.h>
#include <libunwind/cfi/x86_64.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/except.h>
#include <libunwind/unwind.h>
#include <libutil.h>
#include <libvgastate/api.h>
#include <libvgastate/vga.h>
#include <libvideo/codec/api.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/fonts/tlft.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/window/api.h>
#include <libvideo/window/window.h>
#include <libvio/access.h>
#include <libvio/api.h>
#include <libvio/userviofd.h>
#include <libvio/vio.h>
#include <libviocore/api.h>
#include <libviocore/bits/viocore.h>
#include <libviocore/viocore.h>
#include <libvm86/api.h>
#include <libvm86/emulator.h>
#include <libzlib/api.h>
#include <libzlib/error.h>
#include <libzlib/inflate.h>
#include <limits.h>
#include <link.h>
#include <linux/agpgart.h>
#include <linux/bits/posix_types.h>
#include <linux/fd.h>
#include <linux/fs.h>
#include <linux/futex.h>
#include <linux/hdreg.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_fddi.h>
#include <linux/ioctl.h>
#include <linux/kcmp.h>
#include <linux/kd.h>
#include <linux/kernel.h>
#include <linux/limits.h>
#include <linux/magic.h>
#include <linux/msdos_fs.h>
#include <linux/net.h>
#include <linux/param.h>
#include <linux/pci.h>
#include <linux/posix_types.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/stddef.h>
#include <linux/sysinfo.h>
#include <linux/termios.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/vt.h>
#include <locale.h>
#include <machine/_default_types.h>
#include <machine/_endian.h>
#include <machine/_time.h>
#include <machine/_types.h>
#include <machine/ansi.h>
#include <machine/endian.h>
#include <machine/ieeefp.h>
#include <machine/malloc.h>
#include <machine/param.h>
#include <machine/setjmp-dj.h>
#include <machine/setjmp.h>
#include <machine/stdlib.h>
#include <machine/termios.h>
#include <machine/time.h>
#include <machine/types.h>
#include <malloc.h>
#include <malloca.h>
#include <math.h>
#include <mem.h>
#include <memory.h>
#include <minmax.h>
#include <mntent.h>
#include <monetary.h>
#include <mqueue.h>
#include <nan.h>
#include <ndir.h>
#include <net/bits/types.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/if_packet.h>
#include <netdb.h>
#include <netinet/bits/in.h>
#include <netinet/ether.h>
#include <netinet/icmp6.h>
#include <netinet/if_ether.h>
#include <netinet/if_fddi.h>
#include <netinet/if_tr.h>
#include <netinet/igmp.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/ipport.h>
#include <netinet/ipproto.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netpacket/packet.h>
#include <newlib.h>
#include <optimized/error.h>
#include <optimized/fenv.h>
#include <optimized/ssp.string.h>
#include <optimized/string.h>
#include <optimized/unistd.h>
#include <osfcn.h>
#include <parts/assert-failed.h>
#include <parts/assert.h>
#include <parts/malloca.h>
#include <parts/printf-config.h>
#include <parts/redirect-exec.h>
#include <parts/timespec-cxx-support.h>
#include <parts/timeval-cxx-support.h>
#include <parts/uchar/fcntl.h>
#include <parts/uchar/format-printer.h>
#include <parts/uchar/inttypes.h>
#include <parts/uchar/io.h>
#include <parts/uchar/process.h>
#include <parts/uchar/stdio.h>
#include <parts/uchar/stdlib.h>
#include <parts/uchar/string.h>
#include <parts/uchar/sys/mman.h>
#include <parts/uchar/sys/stat.h>
#include <parts/uchar/time.h>
#include <parts/uchar/unistd.h>
#include <parts/uchar/utime.h>
#include <parts/uchar/wchar.h>
#include <parts/uchar/wctype.h>
#include <parts/waitmacros.h>
#include <parts/wchar/format-printer.h>
#include <parts/wchar/process.h>
#include <parts/wchar/stdio.h>
#include <parts/wchar/stdlib.h>
#include <parts/wchar/sys/stat.h>
#include <parts/wchar/unistd.h>
#include <parts/wchar/utime.h>
#include <paths.h>
#include <pciaccess.h>
#include <poll.h>
#include <process.h>
#include <pthread.h>
#include <pthread_np.h>
#include <pty.h>
#include <pwd.h>
#include <random.h>
#include <re_comp.h>
#include <readpassphrase.h>
#include <regex.h>
#include <rpc/netdb.h>
#include <sal.h>
#include <sched.h>
#include <search.h>
#include <semaphore.h>
#include <setjmp.h>
#include <sgtty.h>
#include <shadow.h>
#include <share.h>
#include <signal.h>
#include <spawn.h>
#include <ssp/chk.h>
#include <ssp/ssp.h>
#include <ssp/string.h>
#include <stack_unwind.h>
#include <std.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdc-predef.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <stringlist.h>
#include <strings.h>
#include <stropts.h>
#include <struct.h>
#include <sys/_default_fcntl.h>
#include <sys/_intsup.h>
#include <sys/_iovec.h>
#include <sys/_null.h>
#include <sys/_pthreadtypes.h>
#include <sys/_sigset.h>
#include <sys/_sockaddr_storage.h>
#include <sys/_stdarg.h>
#include <sys/_stdint.h>
#include <sys/_timespec.h>
#include <sys/_timeval.h>
#include <sys/_types.h>
#include <sys/acct.h>
#include <sys/ansi.h>
#include <sys/auxv.h>
#include <sys/bitstring.h>
#include <sys/bitypes.h>
#include <sys/bsdtypes.h>
#include <sys/bswap.h>
#include <sys/byteorder.h>
#include <sys/cdefs.h>
#include <sys/common_ansi.h>
#include <sys/common_int_const.h>
#include <sys/common_int_fmtio.h>
#include <sys/common_int_limits.h>
#include <sys/common_int_mwgwtypes.h>
#include <sys/common_int_types.h>
#include <sys/common_limits.h>
#include <sys/common_wchar_limits.h>
#include <sys/config.h>
#include <sys/dir.h>
#include <sys/elf.h>
#include <sys/elf_386.h>
#include <sys/elf_SPARC.h>
#include <sys/elf_amd64.h>
#include <sys/elf_notes.h>
#include <sys/elftypes.h>
#include <sys/endian.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/eventfd.h>
#include <sys/exec_elf.h>
#include <sys/fcntl.h>
#include <sys/fcntlcom.h>
#include <sys/feature_tests.h>
#include <sys/features.h>
#include <sys/featuretest.h>
#include <sys/file.h>
#include <sys/filio.h>
#include <sys/fsuid.h>
#include <sys/int_const.h>
#include <sys/int_fmtio.h>
#include <sys/int_limits.h>
#include <sys/int_types.h>
#include <sys/inttypes.h>
#include <sys/io.h>
#include <sys/ioccom.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/isa_defs.h>
#include <sys/kd.h>
#include <sys/klog.h>
#include <sys/loadavg.h>
#include <sys/mman.h>
#include <sys/mmio.h>
#include <sys/mount.h>
#include <sys/msg.h>
#include <sys/ndir.h>
#include <sys/null.h>
#include <sys/param.h>
#include <sys/pci.h>
#include <sys/perm.h>
#include <sys/poll.h>
#include <sys/procfs.h>
#include <sys/ptrace.h>
#include <sys/queue.h>
#include <sys/random.h>
#include <sys/reboot.h>
#include <sys/resource.h>
#include <sys/sched.h>
#include <sys/select.h>
#include <sys/sem.h>
#include <sys/sendfile.h>
#include <sys/setjmp.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/sockio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>
#include <sys/stdarg.h>
#include <sys/stdbool.h>
#include <sys/stdint.h>
#include <sys/stdtypes.h>
#include <sys/stropts.h>
#include <sys/swap.h>
#include <sys/syscall-proto.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <sys/syslimits.h>
#include <sys/syslog.h>
#include <sys/sysmacros.h>
#include <sys/systeminfo.h>
#include <sys/termio.h>
#include <sys/termios.h>
#include <sys/termiox.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/timerfd.h>
#include <sys/times.h>
#include <sys/timespec.h>
#include <sys/timex.h>
#include <sys/ttychars.h>
#include <sys/ttycom.h>
#include <sys/ttydefaults.h>
#include <sys/ttydev.h>
#include <sys/types.h>
#include <sys/ucontext.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/unistd.h>
#include <sys/user.h>
#include <sys/ustat.h>
#include <sys/utime.h>
#include <sys/utsname.h>
#include <sys/vfs.h>
#include <sys/vt.h>
#include <sys/wait.h>
#include <sys/xattr.h>
#include <syscall.h>
#include <sysexits.h>
#include <syslimits.h>
#include <syslog.h>
#include <system-test/api.h>
#include <tar.h>
#include <termio.h>
#include <termios.h>
#include <tgmath.h>
#include <threads.h>
#include <time.h>
#include <ttyent.h>
#include <uchar.h>
#include <ucontext.h>
#include <ulimit.h>
#include <unicode.h>
#include <unistd.h>
#include <unwind.h>
#include <ustat.h>
#include <util.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#include <vadefs.h>
#include <values.h>
#include <vfork.h>
#include <wait.h>
#include <waitflags.h>
#include <waitstatus.h>
#include <wchar.h>
#include <wctype.h>
#include <xlocale.h>
//[[[end]]]


#ifdef __cplusplus
/* libstdc++ doesn't work in freestanding mode. */
#ifndef __CRT_FREESTANDING
/* libstdc++ headers don't work without GNU extensions... */
#ifdef _GNU_SOURCE
/* libstdc++ doesn't work in kernel-space:
 *  - missing functions that libstdc++ assumes to be there (locale, etc...)
 *  - The fact that most libc functions are defined as STDCALL,
 *    which   breaks  assigning  them  to  prototype  pointers. */
#ifndef __KERNEL__
#undef min
#undef max
/* Some of the SAL bs also breaks libstdc++. */
#undef __valid
/* libstdc++ also doesn't like KOS's `error_code()' macro. */
#undef error_code
#include <__stdcxx.h>
#include <atomic>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdalign>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <mutex>
#include <new>
#include <type_traits>
#include <typeinfo>
#include <utility>
#endif /* !__KERNEL__ */
#endif /* _GNU_SOURCE */
#endif /* !__CRT_FREESTANDING */
#endif /* __cplusplus */
