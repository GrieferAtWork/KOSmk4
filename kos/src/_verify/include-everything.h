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


#include <kos/exec/library.h> /* FIXME: This header cannot be included after <dlfcn.h> */

/* In order to ensure that all of our system headers work nice with each other,
 * try to include every single one at the same time in the following configurations:
 *   - <nothing>
 *   - _ALL_SOURCE
 *   - __cplusplus
 *   - __cplusplus, _ALL_SOURCE
 *   - __CRT_FREESTANDING
 *   - __CRT_FREESTANDING, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __cplusplus
 *   - __CRT_FREESTANDING, __cplusplus, _ALL_SOURCE
 *   - _ISOC_PURE_SOURCE
 *   - _ISOC_PURE_SOURCE, _ALL_SOURCE
 *   - _ISOC_PURE_SOURCE, __cplusplus
 *   - _ISOC_PURE_SOURCE, __cplusplus, _ALL_SOURCE
 *   - __KERNEL__
 *   - __KERNEL__, _ALL_SOURCE
 *   - __KERNEL__, __cplusplus
 *   - __KERNEL__, __cplusplus, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__
 *   - __CRT_FREESTANDING, __KERNEL__, _ALL_SOURCE
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus
 *   - __CRT_FREESTANDING, __KERNEL__, __cplusplus, _ALL_SOURCE
 *   - _ISOC_PURE_SOURCE, __KERNEL__
 *   - _ISOC_PURE_SOURCE, __KERNEL__, _ALL_SOURCE
 *   - _ISOC_PURE_SOURCE, __KERNEL__, __cplusplus
 *   - _ISOC_PURE_SOURCE, __KERNEL__, __cplusplus, _ALL_SOURCE
 * NOTE: The __KERNEL__ variants are achieved by include all *.c files
 *       twice, once as part of the kernel core, and once again as part
 *       of /bin/system-test
 */

/*[[[deemon
local chk_include = {
	"eti.h",
	"form.h",
	"menu.h",
	"panel.h",
	"curses.h",
	"ncurses_cfg.h",
	"ncurses_def.h",
	"nc_tparm.h",
	"ncurses.h",
	"ncurses_dll.h",
	"term.h",
	"term_entry.h",
	"termcap.h",
	"tic.h",
	"unctrl.h",
	"zconf.h",
	"zlib.h",
};

import fs;
function incdir(prefix, path) {
	for (local x: fs.dir(path).sorted()) {
		local total = fs.joinpath(path, x);
		if (fs.stat.isdir(total)) {
			if (x in ["i386-kos", "c++", "local", "compiler", "crt-features", "__ice__", "system-test"])
				continue;
			incdir(prefix + x + "/", total);
			continue;
		}
		if ("." !in x || x in ["__stdcxx.h"]) {
			// c++ header
		} else if (x !in [
			"atree-abi.h", "__atomic-gasm.h", "__atomic-msvc.h",
			"__atomic-libatomic.h", "service-lock.h"
		]) {
			if (x.endswith(".h") && !x.endswith("-impl.h")) {
				local full;
				if (".." in prefix) {
					full = "\"" + prefix + x + "\"";
				} else {
					full = "<" + prefix + x + ">";
				}
				if (x in chk_include) {
					print "#if __has_include(" + full + ")";
					print "#include",full;
					print "#endif /" "* __has_include(" + full + ") *" "/";
				} else {
					print "#include",full;
				}
			}
		}
	}
}
//print "#if 0";
//incdir("../../include/", "../../include");
//print "#else";
incdir("", "../../include");
//print "#endif";

]]]*/
#include <ConcurrencySal.h>
#include <__crt.h>
#include <__stdinc.h>
#include <_ansi.h>
#include <_newlib_version.h>
#include <aio.h>
#include <aliases.h>
#include <alloc.h>
#include <alloca.h>
#include <ar.h>
#include <argz.h>
#include <arpa/inet.h>
#include <asm/bitsperlong.h>
#include <asm/byteswap.h>
#include <asm/cacheline.h>
#include <asm/int-l64.h>
#include <asm/int-ll64.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#include <asm/ioctl.h>
#include <asm/ioctls.h>
#include <asm/ls-syscalls.h>
#include <asm/pageid.h>
#include <asm/pagesize.h>
#include <asm/param.h>
#include <asm/posix_types.h>
#include <asm/socket.h>
#include <asm/sockios.h>
#include <asm/syscalls-proto.h>
#include <asm/syscalls-trace.h>
#include <asm/syscalls.h>
#include <asm/termbits.h>
#include <asm/termios.h>
#include <asm/types.h>
#include <asm/unistd.h>
#include <assert.h>
#include <attr/xattr.h>
#include <bits/auxv.h>
#include <bits/byteswap.h>
#include <bits/compat.h>
#include <bits/confname.h>
#include <bits/dirent.h>
#include <bits/dlfcn.h>
#include <bits/elf-types.h>
#include <bits/endian.h>
#include <bits/environments.h>
#include <bits/epoll.h>
#include <bits/eventfd.h>
#include <bits/fcntl.h>
#include <bits/fenv-inline.h>
#include <bits/fenv.h>
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
#include <bits/iovec-struct.h>
#include <bits/ipc.h>
#include <bits/itimerspec.h>
#include <bits/itimerval.h>
#include <bits/local_lim.h>
#include <bits/locale.h>
#include <bits/math-vector.h>
#include <bits/mathdef.h>
#include <bits/mbstate.h>
#include <bits/mman.h>
#include <bits/msq.h>
#include <bits/nan.h>
#include <bits/netdb.h>
#include <bits/oflags.h>
#include <bits/os_defines.h>
#include <bits/param.h>
#include <bits/poll.h>
#include <bits/posix1_lim.h>
#include <bits/posix2_lim.h>
#include <bits/posix_opt.h>
#include <bits/pthreadinit.h>
#include <bits/pthreadtypes.h>
#include <bits/pthreadvalues.h>
#include <bits/resource.h>
#include <bits/sched.h>
#include <bits/select.h>
#include <bits/sem.h>
#include <bits/semaphore.h>
#include <bits/shm.h>
#include <bits/sigaction-struct.h>
#include <bits/sigaction.h>
#include <bits/sigcontext.h>
#include <bits/sigevent.h>
#include <bits/siginfo-struct.h>
#include <bits/siginfo-values.h>
#include <bits/siginfo.h>
#include <bits/signalfd.h>
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
#include <bits/syscalls.h>
#include <bits/syslog-path.h>
#include <bits/termios.h>
#include <bits/threads.h>
#include <bits/time.h>
#include <bits/timerfd.h>
#include <bits/timespec-cxx-support.h>
#include <bits/timespec.h>
#include <bits/timeval-cxx-support.h>
#include <bits/timeval.h>
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
#include <compat/bits/iovec-struct.h>
#include <compat/bits/types.h>
#include <compat/bits/typesizes.h>
#include <compat/config.h>
#include <compat/kos/types.h>
#include <cpio.h>
#include <crtdbg.h>
#include <crtdefs.h>
#include <crypt.h>
#include <ctype.h>
#if __has_include(<curses.h>)
#include <curses.h>
#endif /* __has_include(<curses.h>) */
#include <dir.h>
#include <direct.h>
#include <dirent.h>
#include <dlfcn.h>
#include <dos.h>
#include <elf.h>
#include <endian.h>
#include <envz.h>
#include <err.h>
#include <errno.h>
#include <error.h>
#if __has_include(<eti.h>)
#include <eti.h>
#endif /* __has_include(<eti.h>) */
#include <execinfo.h>
#include <fcntl.h>
#include <features.h>
#include <fenv.h>
#include <file.h>
#include <float.h>
#include <fnmatch.h>
#if __has_include(<form.h>)
#include <form.h>
#endif /* __has_include(<form.h>) */
#include <format-printer.h>
#include <format-reader.h>
#include <getopt.h>
#include <getpagesize.h>
#include <glob.h>
#include <gnu/stubs.h>
#include <gnu/lib-names.h>
#include <grp.h>
#include <hybrid/__alloca.h>
#include <hybrid/__altint.h>
#include <hybrid/__asm.h>
#include <hybrid/__assembly.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__bit.h>
#include <hybrid/__byteorder.h>
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
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/vector.h>
#include <hybrid/struct.h>
#include <hybrid/sync/atomic-once.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>
#include <ieee754.h>
#include <ifaddrs.h>
#include <int128.h>
#include <inttypes.h>
#include <io.h>
#include <iso646.h>
#include <kos/anno.h>
#include <kos/asm/except.h>
#include <kos/asm/syscall.h>
#include <kos/bits/debugtrap.h>
#include <kos/bits/except-handler.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/futex-expr.h>
#include <kos/bits/futex.h>
#include <kos/bits/thread.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern.h>
#include <kos/debugtrap.h>
#include <kos/dev.h>
#include <kos/except-fs.h>
#include <kos/except-handler.h>
#include <kos/except-inval.h>
#include <kos/except-io.h>
#include <kos/except-noexec.h>
#include <kos/except.h>
#include <kos/exec/asm/rtld.h>
#include <kos/exec/asm/elf.h>
#include <kos/exec/bits/library-listdef.h>
#include <kos/exec/bits/library.h>
#include <kos/exec/bits/peb.h>
#include <kos/exec/elf-rel.h>
#include <kos/exec/elf.h>
#include <kos/exec/lazybind.h>
#include <kos/exec/library-listdef.h>
#include <kos/exec/library.h>
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h>
#include <kos/fcntl.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/futexlock.h>
#include <kos/guid.h>
#include <kos/hop.h>
#include <kos/hybrid/sched-signal.h>
#include <kos/hybrid/heap.h>
#include <kos/io/ohci.h>
#include <kos/io/pci.h>
#include <kos/io/ps2.h>
#include <kos/io/scsi.h>
#include <kos/io/serial.h>
#include <kos/io/uhci.h>
#include <kos/io/usb-class.h>
#include <kos/io/usb-hid.h>
#include <kos/io/usb-hub.h>
#include <kos/io/usb.h>
#include <kos/io/vga.h>
#include <kos/io.h>
#include <kos/ioctl/clock.h>
#include <kos/ioctl/keyboard.h>
#include <kos/ioctl/mouse.h>
#include <kos/jiffies.h>
#include <kos/kernel/handle.h>
#include <kos/kernel/syscalls.h>
#include <kos/kernel/types.h>
#include <kos/keyboard.h>
#include <kos/ksysctl.h>
#include <kos/malloc.h>
#include <kos/personality.h>
#include <kos/sys/stat.h>
#include <kos/sys/ioctl.h>
#include <kos/syscalls.h>
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
#include <libc/error.h>
#include <libc/malloc.h>
#include <libc/parts.uchar.string.h>
#include <libc/slow/ctype.h>
#include <libc/slow/error.h>
#include <libc/slow/malloc.h>
#include <libc/slow/parts.uchar.string.h>
#include <libc/slow/stdlib.h>
#include <libc/slow/string.h>
#include <libc/slow/unicode.h>
#include <libc/stdlib.h>
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
#include <libinstrlen/instrlen.h>
#include <libinstrlen/api.h>
#include <libio.h>
#include <libjson/api.h>
#include <libjson/generator.h>
#include <libjson/parser.h>
#include <libjson/writer.h>
#include <libkeymap/keymap.h>
#include <libkeymap/api.h>
#include <libregdump/printer.h>
#include <libregdump/api.h>
#include <libregex/regex.h>
#include <libregex/api.h>
#include <librpc/api.h>
#include <librpc/bits/syscall-info.h>
#include <librpc/bits/rpc.h>
#include <librpc/rpc.h>
#include <librt/_api.h>
#include <librt/aio.h>
#include <librt/api.h>
#include <librt/asm/aio.h>
#include <librt/bits/aiocb.h>
#include <librt/bits/aioinit.h>
#include <librt/bits/mqueue.h>
#include <librt/mqueue.h>
#include <libterm/termio.h>
#include <libterm/api.h>
#include <libunwind/api.h>
#include <libunwind/arch-register.h>
#include <libunwind/cfi/x86_64.h>
#include <libunwind/cfi/i386.h>
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
#include <libvideo/window/window.h>
#include <libvideo/window/api.h>
#include <libvm86/api.h>
#include <libvm86/emulator.h>
#include <libvm86/intrin86.h>
#include <libzlib/api.h>
#include <libzlib/error.h>
#include <libzlib/inflate.h>
#include <limits.h>
#include <linux/fd.h>
#include <linux/fs.h>
#include <linux/futex.h>
#include <linux/hdreg.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_fddi.h>
#include <linux/ioctl.h>
#include <linux/kd.h>
#include <linux/kernel.h>
#include <linux/limits.h>
#include <linux/magic.h>
#include <linux/msdos_fs.h>
#include <linux/param.h>
#include <linux/pci.h>
#include <linux/posix_types.h>
#include <linux/stddef.h>
#include <linux/sysinfo.h>
#include <linux/termios.h>
#include <linux/types.h>
#include <linux/vt.h>
#include <locale.h>
#include <machine/_default_types.h>
#include <machine/_endian.h>
#include <machine/_time.h>
#include <machine/_types.h>
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
#include <malloc.h>
#include <malloca.h>
#include <math.h>
#include <mem.h>
#include <memory.h>
#if __has_include(<menu.h>)
#include <menu.h>
#endif /* __has_include(<menu.h>) */
#include <minmax.h>
#include <mntent.h>
#include <monetary.h>
#include <mqueue.h>
#if __has_include(<nc_tparm.h>)
#include <nc_tparm.h>
#endif /* __has_include(<nc_tparm.h>) */
#if __has_include(<ncurses.h>)
#include <ncurses.h>
#endif /* __has_include(<ncurses.h>) */
#if __has_include(<ncurses_cfg.h>)
#include <ncurses_cfg.h>
#endif /* __has_include(<ncurses_cfg.h>) */
#if __has_include(<ncurses_def.h>)
#include <ncurses_def.h>
#endif /* __has_include(<ncurses_def.h>) */
#if __has_include(<ncurses_dll.h>)
#include <ncurses_dll.h>
#endif /* __has_include(<ncurses_dll.h>) */
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
#include <netpacket/packet.h>
#include <newlib.h>
#include <optimized/error.h>
#include <optimized/fenv.h>
#include <optimized/string.h>
#include <osfcn.h>
#if __has_include(<panel.h>)
#include <panel.h>
#endif /* __has_include(<panel.h>) */
#include <parts/assert-failed.h>
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
#include <parts/uchar/sys/stat.h>
#include <parts/uchar/sys/mman.h>
#include <parts/uchar/time.h>
#include <parts/uchar/unistd.h>
#include <parts/uchar/utime.h>
#include <parts/wchar/format-printer.h>
#include <parts/wchar/process.h>
#include <parts/wchar/stdio.h>
#include <parts/wchar/sys/stat.h>
#include <parts/wchar/unistd.h>
#include <parts/wchar/utime.h>
#include <paths.h>
#include <poll.h>
#include <process.h>
#include <pthread.h>
#include <pty.h>
#include <pwd.h>
#include <random.h>
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
#include <std.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <strings.h>
#include <stropts.h>
#include <sys/_types.h>
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
#include <sys/kd.h>
#include <sys/klog.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/msg.h>
#include <sys/param.h>
#include <sys/pci.h>
#include <sys/perm.h>
#include <sys/poll.h>
#include <sys/procfs.h>
#include <sys/ptrace.h>
#include <sys/reboot.h>
#include <sys/resource.h>
#include <sys/select.h>
#include <sys/sem.h>
#include <sys/sendfile.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/signalfd.h>
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
#include <sys/vfs.h>
#include <sys/vt.h>
#include <sys/wait.h>
#include <sys/xattr.h>
#include <syscall.h>
#include <syslog.h>
#if __has_include(<term.h>)
#include <term.h>
#endif /* __has_include(<term.h>) */
#if __has_include(<term_entry.h>)
#include <term_entry.h>
#endif /* __has_include(<term_entry.h>) */
#if __has_include(<termcap.h>)
#include <termcap.h>
#endif /* __has_include(<termcap.h>) */
#include <termio.h>
#include <termios.h>
#include <threads.h>
#if __has_include(<tic.h>)
#include <tic.h>
#endif /* __has_include(<tic.h>) */
#include <time.h>
#include <ttyent.h>
#include <uchar.h>
#include <ucontext.h>
#include <ulimit.h>
#if __has_include(<unctrl.h>)
#include <unctrl.h>
#endif /* __has_include(<unctrl.h>) */
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
#if __has_include(<zconf.h>)
#include <zconf.h>
#endif /* __has_include(<zconf.h>) */
#if __has_include(<zlib.h>)
#include <zlib.h>
#endif /* __has_include(<zlib.h>) */
//[[[end]]]


#ifdef __cplusplus
/* libstdc++ doesn't work in freestanding mode. */
#ifndef __CRT_FREESTANDING
/* libstdc++ headers don't work without GNU extensions... */
#ifdef _GNU_SOURCE
/* libstdc++ doesn't work in kernel-space:
 *  - missing functions that libstdc++ assumes to be there (locale, etc...)
 *  - The fact that most libc functions are defined as STDCALL,
 *    which breaks assigning them to to prototype pointers. */
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

