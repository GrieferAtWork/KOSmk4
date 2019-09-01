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
/* Disable warnings emit by some headers under certain circumstances. */
#define __NO_WARNINGS 1


#include <kos/hybrid/library.h> /* FIXME: This header cannot be included after <dlfcn.h> */

/* In order to ensure that all of our system headers work nice with each other,
 * try to include every single one at the same time in the following configurations:
 *   - <nothing>
 *   - _ALL_SOURCE
 *   - __cplusplus
 *   - __cplusplus, _ALL_SOURCE
 *   - __KERNEL__
 *   - __KERNEL__, _ALL_SOURCE
 *   - __KERNEL__, __cplusplus
 *   - __KERNEL__, __cplusplus, _ALL_SOURCE
 *   - __CRT_FREESTANDING
 *   - __CRT_FREESTANDING, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __cplusplus
 *   - __CRT_FREESTANDING, __cplusplus, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__
 *   - __CRT_FREESTANDING, __KERNEL__, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus, _ALL_SOURCE
 */

 /*[[[deemon
import fs;
function incdir(prefix, path) {
	for (local x: fs.dir(path)) {
		local total = fs.joinpath(path, x);
		if (fs.stat.isdir(total)) {
			if (x in ["i386-kos", "c++", "local", "compiler", "crt-features", "__ice__", "system-test"])
				continue;
			incdir(prefix + x + "/", total);
			continue;
		}
		if (x !in ["atree-abi.h", "__atomic-gasm.h", "__atomic-msvc.h", "__stdcxx.h"]) {
			if (x.endswith(".h") && !x.endswith("-impl.h")) {
				if (".." in prefix) {
					print "#include \"" + prefix + x + "\"";
				} else {
					print "#include <" + prefix + x + ">";
				}
			}
		}
	}
}
//print "#if 0";
//incdir("../../../include/", "../../../include");
//print "#else";
incdir("", "../../../include");
//print "#endif";
]]]*/
#include <aliases.h>
#include <alloc.h>
#include <alloca.h>
#include <ar.h>
#include <arpa/inet.h>
#include <asm/bitsperlong.h>
#include <asm/byteswap.h>
#include <asm/int-l64.h>
#include <asm/int-ll64.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#include <asm/ioctl.h>
#include <asm/ioctls.h>
#include <asm/param.h>
#include <asm/posix_types.h>
#include <asm/socket.h>
#include <asm/sockios.h>
#include <asm/types.h>
#include <asm/unistd.h>
#include <assert.h>
#include <attr/xattr.h>
#include <bits/auxv.h>
#include <bits/byteswap.h>
#include <bits/confname.h>
#include <bits/dirent.h>
#include <bits/dlfcn.h>
#include <bits/elf-types.h>
#include <bits/endian.h>
#include <bits/environments.h>
#include <bits/epoll.h>
#include <bits/eventfd.h>
#include <bits/fcntl.h>
#include <bits/format-printer.h>
#include <bits/huge_val.h>
#include <bits/huge_valf.h>
#include <bits/huge_vall.h>
#include <bits/hwcap.h>
#include <bits/in.h>
#include <bits/inf.h>
#include <bits/io-file.h>
#include <bits/ioctl-types.h>
#include <bits/ioctls.h>
#include <bits/ipc.h>
#include <bits/itimerval.h>
#include <bits/locale.h>
#include <bits/local_lim.h>
#include <bits/math-vector.h>
#include <bits/mathdef.h>
#include <bits/mbstate.h>
#include <bits/mman.h>
#include <bits/nan.h>
#include <bits/netdb.h>
#include <bits/oflags.h>
#include <bits/param.h>
#include <bits/poll.h>
#include <bits/posix1_lim.h>
#include <bits/posix2_lim.h>
#include <bits/posix_opt.h>
#include <bits/resource.h>
#include <bits/sched.h>
#include <bits/select.h>
#include <bits/semaphore.h>
#include <bits/shm.h>
#include <bits/sigaction-struct.h>
#include <bits/sigaction.h>
#include <bits/sigcontext.h>
#include <bits/sigevent.h>
#include <bits/siginfo-struct.h>
#include <bits/siginfo-values.h>
#include <bits/siginfo.h>
#include <bits/signum-values.h>
#include <bits/signum.h>
#include <bits/sigset.h>
#include <bits/sigstack.h>
#include <bits/sigthread.h>
#include <bits/sigval.h>
#include <bits/sockaddr.h>
#include <bits/socket.h>
#include <bits/socket_type.h>
#include <bits/stat.h>
#include <bits/statfs.h>
#include <bits/statvfs.h>
#include <bits/stdio_lim.h>
#include <bits/stropts.h>
#include <bits/syscall.h>
#include <bits/syslog-path.h>
#include <bits/termios.h>
#include <bits/time.h>
#include <bits/timerfd.h>
#include <bits/timespec-cxx-support.h>
#include <bits/timespec.h>
#include <bits/timeval-cxx-support.h>
#include <bits/timeval.h>
#include <bits/timex.h>
#include <bits/types/clockid_t.h>
#include <bits/types/clock_t.h>
#include <bits/types/FILE.h>
#include <bits/types/locale_t.h>
#include <bits/types/mbstate_t.h>
#include <bits/types/sigevent_t.h>
#include <bits/types/siginfo_t.h>
#include <bits/types/sigset_t.h>
#include <bits/types/sigval_t.h>
#include <bits/types/sig_atomic_t.h>
#include <bits/types/stack_t.h>
#include <bits/types/struct_iovec.h>
#include <bits/types/struct_itimerspec.h>
#include <bits/types/struct_osockaddr.h>
#include <bits/types/struct_rusage.h>
#include <bits/types/struct_sigstack.h>
#include <bits/types/struct_timespec.h>
#include <bits/types/struct_timeval.h>
#include <bits/types/struct_tm.h>
#include <bits/types/timer_t.h>
#include <bits/types/time_t.h>
#include <bits/types/wint_t.h>
#include <bits/types/__FILE.h>
#include <bits/types/__locale_t.h>
#include <bits/types/__mbstate_t.h>
#include <bits/types/__sigset_t.h>
#include <bits/types.h>
#include <bits/typesizes.h>
#include <bits/uformat-printer.h>
#include <bits/uio.h>
#include <bits/ustat.h>
#include <bits/utimebuf.h>
#include <bits/utmp.h>
#include <bits/utmpx.h>
#include <bits/utsname.h>
#include <bits/waitflags.h>
#include <bits/waitstatus.h>
#include <bits/wchar.h>
#include <bits/wformat-printer.h>
#include <bits/wordsize.h>
#include <bits/xopen_lim.h>
#include <bits/xtitypes.h>
#include <byteswap.h>
#include <ConcurrencySal.h>
#include <cpio.h>
#include <crtdefs.h>
#include <ctype.h>
#include <dir.h>
#include <direct.h>
#include <dirent.h>
#include <dlfcn.h>
#include <dos.h>
#include <elf.h>
#include <endian.h>
#include <errno.h>
#include <execinfo.h>
#include <fcntl.h>
#include <features.h>
#include <float.h>
#include <fnmatch.h>
#include <format-printer.h>
#include <getopt.h>
#include <gnu/lib-names.h>
#include <gnu/stubs.h>
#include <grp.h>
#include <hybrid/align.h>
#include <hybrid/alloca.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/compiler.h>
#include <hybrid/debug-alignment.h>
#include <hybrid/floatcore.h>
#include <hybrid/host.h>
#include <hybrid/limitcore.h>
#include <hybrid/limits.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/pointer.h>
#include <hybrid/pp/bubble.h>
#include <hybrid/pp/__bubble.h>
#include <hybrid/pp/__va_nargs.h>
#include <hybrid/sched/yield.h>
#include <hybrid/sched/__gettid.h>
#include <hybrid/sched/__yield.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/vector.h>
#include <hybrid/struct.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>
#include <hybrid/__alloca.h>
#include <hybrid/__asm.h>
#include <hybrid/__assembly.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__bit.h>
#include <hybrid/__byteorder.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__debug-alignment.h>
#include <hybrid/__limits.h>
#include <hybrid/__minmax.h>
#include <hybrid/__overflow.h>
#include <hybrid/__pointer.h>
#include <hybrid/__rotate.h>
#include <hybrid/__unaligned.h>
#include <hybrid/__wordbits.h>
#include <ieee754.h>
#include <inttypes.h>
#include <io.h>
#include <iso646.h>
#include <kos/anno.h>
#include <kos/asm/except.h>
#include <kos/asm/syscalls.h>
#include <kos/bits/debugtrap.h>
#include <kos/bits/elf-reloc.h>
#include <kos/bits/except-handler.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/futex-expr.h>
#include <kos/bits/futex.h>
#include <kos/bits/library.h>
#include <kos/bits/peb.h>
#include <kos/bits/process.h>
#include <kos/bits/thread.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern.h>
#include <kos/debugtrap.h>
#include <kos/dev/clock.h>
#include <kos/dev/keyboard.h>
#include <kos/dev/mouse.h>
#include <kos/dev.h>
#include <kos/except-handler.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/futexlock.h>
#include <kos/guid.h>
#include <kos/hop.h>
#include <kos/hybrid/heap.h>
#include <kos/hybrid/library.h>
#include <kos/hybrid/sched-signal.h>
#include <kos/io/serial.h>
#include <kos/io.h>
#include <kos/jiffies.h>
#include <kos/kernel/handle.h>
#include <kos/kernel/types.h>
#include <kos/keyboard.h>
#include <kos/lazybind.h>
#include <kos/library-listdef.h>
#include <kos/malloc.h>
#include <kos/process.h>
#include <kos/syscalls.h>
#include <kos/sysctl.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <kos/ukern.h>
#include <kos/unistd.h>
#include <lastlog.h>
#include <libansitty/ansitty.h>
#include <libansitty/api.h>
#include <libbuffer/api.h>
#include <libbuffer/linebuffer.h>
#include <libbuffer/ringbuffer.h>
#include <libc/ctype.h>
#include <libc/malloc.h>
#include <libc/parts.uchar.string.h>
#include <libc/slow/ctype.h>
#include <libc/slow/malloc.h>
#include <libc/slow/parts.uchar.string.h>
#include <libc/slow/string.h>
#include <libc/slow/unicode.h>
#include <libc/string.h>
#include <libc/unicode.h>
#include <libcmdline/api.h>
#include <libcmdline/decode.h>
#include <libcmdline/encode.h>
#include <libcpustate/api.h>
#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/api.h>
#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>
#include <libdebuginfo/symtab.h>
#include <libdemangle/api.h>
#include <libdemangle/demangle.h>
#include <libdemangle/gcc.h>
#include <libdisasm/api.h>
#include <libdisasm/disassembler.h>
#include <libdisasm/format.h>
#include <libgen.h>
#include <libinstrlen/api.h>
#include <libinstrlen/instrlen.h>
#include <libio.h>
#include <libjson/api.h>
#include <libjson/generator.h>
#include <libjson/parser.h>
#include <libjson/writer.h>
#include <libkeymap/api.h>
#include <libkeymap/keymap.h>
#include <libregdump/api.h>
#include <libregdump/printer.h>
#include <librpc/api.h>
#include <librpc/bits/rpc.h>
#include <librpc/bits/syscall-info.h>
#include <librpc/rpc.h>
#include <libterm/api.h>
#include <libterm/termio.h>
#include <libunwind/api.h>
#include <libunwind/arch-register.h>
#include <libunwind/cfi/i386.h>
#include <libunwind/cfi/x86_64.h>
#include <libunwind/cfi.h>
#include <libunwind/eh_frame.h>
#include <libunwind/except.h>
#include <libunwind/unwind.h>
#include <libvideo/codec/api.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/window/api.h>
#include <libvideo/window/window.h>
#include <libvm86/api.h>
#include <libvm86/emulator.h>
#include <libvm86/intrin86.h>
#include <limits.h>
#include <linux/fs.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_fddi.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/limits.h>
#include <linux/magic.h>
#include <linux/msdos_fs.h>
#include <linux/param.h>
#include <linux/pci.h>
#include <linux/posix_types.h>
#include <linux/stddef.h>
#include <linux/sysinfo.h>
#include <linux/types.h>
#include <locale.h>
#include <machine/ansi.h>
#include <machine/endian.h>
#include <machine/malloc.h>
#include <machine/param.h>
#include <machine/setjmp-dj.h>
#include <machine/setjmp.h>
#include <machine/stdlib.h>
#include <machine/termios.h>
#include <machine/time.h>
#include <machine/types.h>
#include <machine/_default_types.h>
#include <machine/_endian.h>
#include <machine/_time.h>
#include <machine/_types.h>
#include <malloc.h>
#include <malloca.h>
#include <math.h>
#include <memory.h>
#include <minmax.h>
#include <mntent.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/if_packet.h>
#include <netdb.h>
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
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <newlib.h>
#include <optimized/string.h>
#include <parts/assert.h>
#include <parts/cyg/errno.h>
#include <parts/dos/errno.h>
#include <parts/errno.h>
#include <parts/generic/errno.h>
#include <parts/glibc/errno.h>
#include <parts/malloca.h>
#include <parts/redirect-exec.h>
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
#include <parts/uchar/unistd.h>
#include <parts/uchar/utime.h>
#include <parts/wchar/format-printer.h>
#include <parts/wchar/process.h>
#include <parts/wchar/sys/stat.h>
#include <parts/wchar/unistd.h>
#include <parts/wchar/utime.h>
#include <paths.h>
#include <poll.h>
#include <process.h>
#include <pthread.h>
#include <pty.h>
#include <pwd.h>
#include <rpc/netdb.h>
#include <sal.h>
#include <sched.h>
#include <search.h>
#include <semaphore.h>
#include <setjmp.h>
#include <sgtty.h>
#include <shadow.h>
#include <signal.h>
#include <spawn.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <strings.h>
#include <stropts.h>
#include <sys/acct.h>
#include <sys/auxv.h>
#include <sys/bitypes.h>
#include <sys/cdefs.h>
#include <sys/config.h>
#include <sys/dir.h>
#include <sys/elf.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/eventfd.h>
#include <sys/fcntl.h>
#include <sys/features.h>
#include <sys/file.h>
#include <sys/filio.h>
#include <sys/fsuid.h>
#include <sys/ioccom.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/isa_defs.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/pci.h>
#include <sys/poll.h>
#include <sys/procfs.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>
#include <sys/stropts.h>
#include <sys/swap.h>
#include <sys/syscall-proto.h>
#include <sys/syscall-trace.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <sys/syslog.h>
#include <sys/sysmacros.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/timerfd.h>
#include <sys/times.h>
#include <sys/timex.h>
#include <sys/ttydefaults.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/unistd.h>
#include <sys/user.h>
#include <sys/ustat.h>
#include <sys/utime.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/xattr.h>
#include <sys/_types.h>
#include <syscall.h>
#include <syslog.h>
#include <termio.h>
#include <termios.h>
#include <time.h>
#include <ttyent.h>
#include <uchar.h>
#include <ucontext.h>
#include <ulimit.h>
#include <unicode.h>
#include <unistd.h>
#include <unwind.h>
#include <ustat.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#include <vadefs.h>
#include <values.h>
#include <wait.h>
#include <wchar.h>
#include <wctype.h>
#include <xlocale.h>
#include <_ansi.h>
#include <_newlib_version.h>
#include <__crt.h>
#include <__stdinc.h>
//[[[end]]]

