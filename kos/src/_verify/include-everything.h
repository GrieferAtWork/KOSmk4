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
/* Disable warnings emit by some headers under certain circumstances. */
#define __NO_WARNINGS 1


/* In order to ensure that all of our system headers work nice with each other,
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
 * NOTE: The __KERNEL__ variants are achieved by include all *.c files
 *       twice, once as part of the kernel core, and once again as part
 *       of /bin/system-test
 */

/*[[[deemon
#define IS_CHK_INCLUDE(x)         \
	(x in chk_include ||          \
	 x.startswith("ncursesw/") || \
	 x.startswith("drm/") ||      \
	 x.startswith("libpng") ||    \
	 x.startswith("openssl/") ||  \
	 x.startswith("pixman-1/"))

local chk_include = {
	"eti.h",
	"etip.h",
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
	"cursesapp.h",
	"cursesf.h",
	"cursesm.h",
	"cursesp.h",
	"cursesw.h",
	"cursslk.h",

	"pciaccess.h",
	"drm.h",
	"xf86drm.h",
	"xf86drmMode.h",

	"png.h",
	"pngconf.h",
	"pnglibconf.h",

	"expat.h",
	"expat_external.h",

	"bzlib.h",

	"ft2build.h",

	"uuid.h",
	"uuid/uuid.h",

	"pixman.h",
	"pixman-version.h",

	"zconf.h",
	"zlib.h",
};

local cxx_include = {
	"__stdcxx.h",

	"cursesapp.h",
	"cursesf.h",
	"cursesm.h",
	"cursesp.h",
	"cursesw.h",
	"cursslk.h",
	"etip.h",

	"ncursesw/cursesapp.h",
	"ncursesw/cursesf.h",
	"ncursesw/cursesm.h",
	"ncursesw/cursesp.h",
	"ncursesw/cursesw.h",
	"ncursesw/cursslk.h",
	"ncursesw/etip.h",
};

import fs;
function incdir(prefix, path) {
	for (local x: fs.dir(path).sorted()) {
		local total = fs.joinpath(path, x);
		if (fs.stat.isdir(total)) {
			if (x in [
					"i386-kos", "c++", "local", "compiler",
					"crt-features", "__ice__", "system-test",
					"libdl", "X11", "xcb", "freetype", "GL",
					"xorg", "python2.7"])
				continue;
			if (prefix.rstrip("\\/").endswith("/os"))
				continue;
			incdir(prefix + x + "/", total);
			continue;
		}
		if ("." !in x) {
			// c++ header
		} else if (x in cxx_include) {
			local full;
			x = prefix + x;
			if (".." in prefix) {
				full = "\"" + x + "\"";
			} else {
				full = "<" + x + ">";
			}
			if (IS_CHK_INCLUDE(x)) {
				print("#if defined(__cpluslus) && __has_include(", full, ")");
				print("#include ", full);
				print("#endif /" "* __cpluslus && __has_include(", full, ") *" "/");
			} else {
				print("#ifdef __cpluslus");
				print("#include ", full);
				print("#endif /" "* __cpluslus *" "/");
			}
		} else if (x !in [
			"atree-abi.h", "__atomic-gasm.h", "__atomic-msvc.h",
			"__atomic-libatomic.h", "service-lock.h",
			"pixman-version.h"
		]) {
			if (x.endswith(".h") && !x.endswith("-impl.h")) {
				local full;
				x = prefix + x;
				if (".." in prefix) {
					full = "\"" + x + "\"";
				} else {
					full = "<" + x + ">";
				}
				if (IS_CHK_INCLUDE(x)) {
					print("#if __has_include(", full, ")");
					print("#include ", full);
					print("#endif /" "* __has_include(", full, ") *" "/");
				} else {
					print("#include ", full);
				}
			}
		}
	}
}
incdir("", "../../include");

]]]*/
#include <ConcurrencySal.h>
#include <__crt.h>
#ifdef __cpluslus
#include <__stdcxx.h>
#endif /* __cpluslus */
#include <__stdinc.h>
#include <_ansi.h>
#include <_lfs_64.h>
#include <aio.h>
#include <aliases.h>
#include <alloc.h>
#include <alloca.h>
#include <ar.h>
#include <argz.h>
#include <arpa/inet.h>
#include <asm/__stdinc.h>
#include <asm/asmword.h>
#include <asm/cacheline.h>
#include <asm/crt/confname.h>
#include <asm/crt/limits.h>
#include <asm/crt/malloc.h>
#include <asm/crt/math-exception.h>
#include <asm/crt/math-libc_version.h>
#include <asm/crt/posix_spawn.h>
#include <asm/crt/process.h>
#include <asm/crt/pthreadvalues.h>
#include <asm/crt/stdio.h>
#include <asm/crt/stdio_ext.h>
#include <asm/crt/stdlib.h>
#include <asm/crt/threads.h>
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
#include <asm/syscalls-proto.h>
#include <asm/syscalls-trace.h>
#include <asm/syscalls-types.h>
#include <asm/syscalls.h>
#include <asm/unistd.h>
#include <assert.h>
#include <attr/xattr.h>
#include <bits/crt/_diskfree_t.h>
#include <bits/crt/crypt_data.h>
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
#include <bits/crt/sys_errlist.h>
#include <bits/crt/threads.h>
#include <bits/crt/tm.h>
#include <bits/crt/uformat-printer.h>
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
#include <bits/os/mcontext.h>
#include <bits/os/mmsghdr.h>
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
#include <bsd/err.h>
#include <bsd/libutil.h>
#include <bsd/stringlist.h>
#include <bsd/sys/bitstring.h>
#include <bsd/sys/cdefs.h>
#include <bsd/sys/endian.h>
#include <bsd/sys/param.h>
#include <bsd/sys/poll.h>
#include <byteswap.h>
#if __has_include(<bzlib.h>)
#include <bzlib.h>
#endif /* __has_include(<bzlib.h>) */
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
#include <compat/kos/bits/except-handler.h>
#include <compat/kos/bits/futex-expr.h>
#include <compat/kos/bits/futex.h>
#include <compat/kos/compat/linux-dirent.h>
#include <compat/kos/compat/linux-olddirent.h>
#include <compat/kos/compat/linux-oldselect.h>
#include <compat/kos/compat/linux-stat.h>
#include <compat/kos/except-handler.h>
#include <compat/kos/exec/asm/elf.h>
#include <compat/kos/exec/bits/elf.h>
#include <compat/kos/exec/elf.h>
#include <compat/kos/futex.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#include <compat/sys/ucontext.h>
#include <corecrt.h>
#include <cpio.h>
#include <crtdbg.h>
#include <crtdefs.h>
#include <crypt.h>
#include <ctype.h>
#if __has_include(<curses.h>)
#include <curses.h>
#endif /* __has_include(<curses.h>) */
#if defined(__cpluslus) && __has_include(<cursesapp.h>)
#include <cursesapp.h>
#endif /* __cpluslus && __has_include(<cursesapp.h>) */
#if defined(__cpluslus) && __has_include(<cursesf.h>)
#include <cursesf.h>
#endif /* __cpluslus && __has_include(<cursesf.h>) */
#if defined(__cpluslus) && __has_include(<cursesm.h>)
#include <cursesm.h>
#endif /* __cpluslus && __has_include(<cursesm.h>) */
#if defined(__cpluslus) && __has_include(<cursesp.h>)
#include <cursesp.h>
#endif /* __cpluslus && __has_include(<cursesp.h>) */
#if defined(__cpluslus) && __has_include(<cursesw.h>)
#include <cursesw.h>
#endif /* __cpluslus && __has_include(<cursesw.h>) */
#if defined(__cpluslus) && __has_include(<cursslk.h>)
#include <cursslk.h>
#endif /* __cpluslus && __has_include(<cursslk.h>) */
#include <dir.h>
#include <direct.h>
#include <dirent.h>
#include <dlfcn.h>
#include <dos.h>
#if __has_include(<drm/amdgpu_drm.h>)
#include <drm/amdgpu_drm.h>
#endif /* __has_include(<drm/amdgpu_drm.h>) */
#if __has_include(<drm/drm.h>)
#include <drm/drm.h>
#endif /* __has_include(<drm/drm.h>) */
#if __has_include(<drm/drm_fourcc.h>)
#include <drm/drm_fourcc.h>
#endif /* __has_include(<drm/drm_fourcc.h>) */
#if __has_include(<drm/drm_mode.h>)
#include <drm/drm_mode.h>
#endif /* __has_include(<drm/drm_mode.h>) */
#if __has_include(<drm/drm_sarea.h>)
#include <drm/drm_sarea.h>
#endif /* __has_include(<drm/drm_sarea.h>) */
#if __has_include(<drm/i915_drm.h>)
#include <drm/i915_drm.h>
#endif /* __has_include(<drm/i915_drm.h>) */
#if __has_include(<drm/mach64_drm.h>)
#include <drm/mach64_drm.h>
#endif /* __has_include(<drm/mach64_drm.h>) */
#if __has_include(<drm/mga_drm.h>)
#include <drm/mga_drm.h>
#endif /* __has_include(<drm/mga_drm.h>) */
#if __has_include(<drm/nouveau_drm.h>)
#include <drm/nouveau_drm.h>
#endif /* __has_include(<drm/nouveau_drm.h>) */
#if __has_include(<drm/qxl_drm.h>)
#include <drm/qxl_drm.h>
#endif /* __has_include(<drm/qxl_drm.h>) */
#if __has_include(<drm/r128_drm.h>)
#include <drm/r128_drm.h>
#endif /* __has_include(<drm/r128_drm.h>) */
#if __has_include(<drm/radeon_drm.h>)
#include <drm/radeon_drm.h>
#endif /* __has_include(<drm/radeon_drm.h>) */
#if __has_include(<drm/savage_drm.h>)
#include <drm/savage_drm.h>
#endif /* __has_include(<drm/savage_drm.h>) */
#if __has_include(<drm/sis_drm.h>)
#include <drm/sis_drm.h>
#endif /* __has_include(<drm/sis_drm.h>) */
#if __has_include(<drm/tegra_drm.h>)
#include <drm/tegra_drm.h>
#endif /* __has_include(<drm/tegra_drm.h>) */
#if __has_include(<drm/vc4_drm.h>)
#include <drm/vc4_drm.h>
#endif /* __has_include(<drm/vc4_drm.h>) */
#if __has_include(<drm/via_drm.h>)
#include <drm/via_drm.h>
#endif /* __has_include(<drm/via_drm.h>) */
#if __has_include(<drm/virtgpu_drm.h>)
#include <drm/virtgpu_drm.h>
#endif /* __has_include(<drm/virtgpu_drm.h>) */
#if __has_include(<drm/vmwgfx_drm.h>)
#include <drm/vmwgfx_drm.h>
#endif /* __has_include(<drm/vmwgfx_drm.h>) */
#if __has_include(<drm.h>)
#include <drm.h>
#endif /* __has_include(<drm.h>) */
#include <elf.h>
#include <endian.h>
#include <envz.h>
#include <err.h>
#include <errno.h>
#include <error.h>
#if __has_include(<eti.h>)
#include <eti.h>
#endif /* __has_include(<eti.h>) */
#if defined(__cpluslus) && __has_include(<etip.h>)
#include <etip.h>
#endif /* __cpluslus && __has_include(<etip.h>) */
#include <execinfo.h>
#if __has_include(<expat.h>)
#include <expat.h>
#endif /* __has_include(<expat.h>) */
#if __has_include(<expat_external.h>)
#include <expat_external.h>
#endif /* __has_include(<expat_external.h>) */
#include <fastmath.h>
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
#if __has_include(<ft2build.h>)
#include <ft2build.h>
#endif /* __has_include(<ft2build.h>) */
#include <getopt.h>
#include <getpagesize.h>
#include <glob.h>
#include <gnu/lib-names.h>
#include <gnu/stubs.h>
#include <grp.h>
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
#include <hybrid/sequence/bitset.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/vector.h>
#include <hybrid/struct.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-once.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>
#include <ieee754.h>
#include <ieeefp.h>
#include <ifaddrs.h>
#include <int128.h>
#include <inttypes.h>
#include <io.h>
#include <iso646.h>
#include <kos/anno.h>
#include <kos/asm/rtm.h>
#include <kos/asm/syscall.h>
#include <kos/asm/uaio.h>
#include <kos/bits/debugtrap.h>
#include <kos/bits/except-handler.h>
#include <kos/bits/except.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_info.h>
#include <kos/bits/fastexcept.h>
#include <kos/bits/futex-expr.h>
#include <kos/bits/futex.h>
#include <kos/bits/rtm.h>
#include <kos/bits/thread.h>
#include <kos/bits/uaio.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern.h>
#include <kos/bits/userprocmask.h>
#include <kos/capability.h>
#include <kos/compat/linux-dirent.h>
#include <kos/compat/linux-dirent64.h>
#include <kos/compat/linux-olddirent.h>
#include <kos/compat/linux-oldselect.h>
#include <kos/compat/linux-stat.h>
#include <kos/debugtrap.h>
#include <kos/dev.h>
#include <kos/except/asm/codes.h>
#include <kos/except/codes.h>
#include <kos/except/reason/fs.h>
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
#include <kos/hop/blockdevice.h>
#include <kos/hop/datablock.h>
#include <kos/hop/datapart.h>
#include <kos/hop/driver.h>
#include <kos/hop/file.h>
#include <kos/hop/futex.h>
#include <kos/hop/handle.h>
#include <kos/hop/openfd.h>
#include <kos/hop/path.h>
#include <kos/hop/pidns.h>
#include <kos/hop/pipe.h>
#include <kos/hop/task.h>
#include <kos/hop/uaio.h>
#include <kos/hop/vm.h>
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
#include <kos/malloc.h>
#include <kos/net/printf.h>
#include <kos/personality.h>
#include <kos/refcnt.h>
#include <kos/refptr.h>
#include <kos/rtm.h>
#include <kos/sys/ioctl.h>
#include <kos/sys/stat.h>
#include <kos/syscalls.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <kos/uaio.h>
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
#include <libc/core/malloc.h>
#include <libc/core/parts.uchar.string.h>
#include <libc/core/ssp.string.h>
#include <libc/core/stdlib.h>
#include <libc/core/string.h>
#include <libc/core/unicode.h>
#include <libc/core/unistd.h>
#include <libc/ctype.h>
#include <libc/errno.h>
#include <libc/error.h>
#include <libc/fenv.h>
#include <libc/malloc.h>
#include <libc/parts.uchar.string.h>
#include <libc/ssp.string.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <libc/unicode.h>
#include <libc/unistd.h>
#include <libcmdline/api.h>
#include <libcmdline/decode.h>
#include <libcmdline/encode.h>
#include <libcpustate/api.h>
#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/api.h>
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
#include <libemu86/api.h>
#include <libemu86/eflags.h>
#include <libemu86/emu/push-pop-util.h>
#include <libemu86/emu/string-util.h>
#include <libemu86/emu86.h>
#include <libemu86/helpers.h>
#include <libgen.h>
#include <libinstrlen/api.h>
#include <libinstrlen/bits/isa.h>
#include <libinstrlen/instrlen.h>
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
#if __has_include(<libpng/png.h>)
#include <libpng/png.h>
#endif /* __has_include(<libpng/png.h>) */
#if __has_include(<libpng/pngconf.h>)
#include <libpng/pngconf.h>
#endif /* __has_include(<libpng/pngconf.h>) */
#if __has_include(<libpng/pnglibconf.h>)
#include <libpng/pnglibconf.h>
#endif /* __has_include(<libpng/pnglibconf.h>) */
#if __has_include(<libpng16/png.h>)
#include <libpng16/png.h>
#endif /* __has_include(<libpng16/png.h>) */
#if __has_include(<libpng16/pngconf.h>)
#include <libpng16/pngconf.h>
#endif /* __has_include(<libpng16/pngconf.h>) */
#if __has_include(<libpng16/pnglibconf.h>)
#include <libpng16/pnglibconf.h>
#endif /* __has_include(<libpng16/pnglibconf.h>) */
#include <libregdump/api.h>
#include <libregdump/printer.h>
#include <libregex/api.h>
#include <libregex/regex.h>
#include <librpc/api.h>
#include <librpc/bits/rpc.h>
#include <librpc/bits/syscall-info.h>
#include <librpc/rpc.h>
#include <librt/_api.h>
#include <librt/aio.h>
#include <librt/api.h>
#include <librt/asm/aio.h>
#include <librt/bits/aiocb.h>
#include <librt/bits/aioinit.h>
#include <librt/bits/mqueue.h>
#include <librt/mqueue.h>
#include <libsctrace/api.h>
#include <libsctrace/repr-types.h>
#include <libsctrace/sctrace.h>
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
#include <linux/param.h>
#include <linux/pci.h>
#include <linux/posix_types.h>
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
#if __has_include(<ncursesw/curses.h>)
#include <ncursesw/curses.h>
#endif /* __has_include(<ncursesw/curses.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursesapp.h>)
#include <ncursesw/cursesapp.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursesapp.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursesf.h>)
#include <ncursesw/cursesf.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursesf.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursesm.h>)
#include <ncursesw/cursesm.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursesm.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursesp.h>)
#include <ncursesw/cursesp.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursesp.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursesw.h>)
#include <ncursesw/cursesw.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursesw.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/cursslk.h>)
#include <ncursesw/cursslk.h>
#endif /* __cpluslus && __has_include(<ncursesw/cursslk.h>) */
#if __has_include(<ncursesw/eti.h>)
#include <ncursesw/eti.h>
#endif /* __has_include(<ncursesw/eti.h>) */
#if defined(__cpluslus) && __has_include(<ncursesw/etip.h>)
#include <ncursesw/etip.h>
#endif /* __cpluslus && __has_include(<ncursesw/etip.h>) */
#if __has_include(<ncursesw/form.h>)
#include <ncursesw/form.h>
#endif /* __has_include(<ncursesw/form.h>) */
#if __has_include(<ncursesw/menu.h>)
#include <ncursesw/menu.h>
#endif /* __has_include(<ncursesw/menu.h>) */
#if __has_include(<ncursesw/nc_tparm.h>)
#include <ncursesw/nc_tparm.h>
#endif /* __has_include(<ncursesw/nc_tparm.h>) */
#if __has_include(<ncursesw/ncurses.h>)
#include <ncursesw/ncurses.h>
#endif /* __has_include(<ncursesw/ncurses.h>) */
#if __has_include(<ncursesw/ncurses_cfg.h>)
#include <ncursesw/ncurses_cfg.h>
#endif /* __has_include(<ncursesw/ncurses_cfg.h>) */
#if __has_include(<ncursesw/ncurses_def.h>)
#include <ncursesw/ncurses_def.h>
#endif /* __has_include(<ncursesw/ncurses_def.h>) */
#if __has_include(<ncursesw/ncurses_dll.h>)
#include <ncursesw/ncurses_dll.h>
#endif /* __has_include(<ncursesw/ncurses_dll.h>) */
#if __has_include(<ncursesw/panel.h>)
#include <ncursesw/panel.h>
#endif /* __has_include(<ncursesw/panel.h>) */
#if __has_include(<ncursesw/term.h>)
#include <ncursesw/term.h>
#endif /* __has_include(<ncursesw/term.h>) */
#if __has_include(<ncursesw/term_entry.h>)
#include <ncursesw/term_entry.h>
#endif /* __has_include(<ncursesw/term_entry.h>) */
#if __has_include(<ncursesw/termcap.h>)
#include <ncursesw/termcap.h>
#endif /* __has_include(<ncursesw/termcap.h>) */
#if __has_include(<ncursesw/tic.h>)
#include <ncursesw/tic.h>
#endif /* __has_include(<ncursesw/tic.h>) */
#if __has_include(<ncursesw/unctrl.h>)
#include <ncursesw/unctrl.h>
#endif /* __has_include(<ncursesw/unctrl.h>) */
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
#if __has_include(<openssl/aes.h>)
#include <openssl/aes.h>
#endif /* __has_include(<openssl/aes.h>) */
#if __has_include(<openssl/asn1.h>)
#include <openssl/asn1.h>
#endif /* __has_include(<openssl/asn1.h>) */
#if __has_include(<openssl/asn1err.h>)
#include <openssl/asn1err.h>
#endif /* __has_include(<openssl/asn1err.h>) */
#if __has_include(<openssl/asn1t.h>)
#include <openssl/asn1t.h>
#endif /* __has_include(<openssl/asn1t.h>) */
#if __has_include(<openssl/async.h>)
#include <openssl/async.h>
#endif /* __has_include(<openssl/async.h>) */
#if __has_include(<openssl/asyncerr.h>)
#include <openssl/asyncerr.h>
#endif /* __has_include(<openssl/asyncerr.h>) */
#if __has_include(<openssl/bio.h>)
#include <openssl/bio.h>
#endif /* __has_include(<openssl/bio.h>) */
#if __has_include(<openssl/bioerr.h>)
#include <openssl/bioerr.h>
#endif /* __has_include(<openssl/bioerr.h>) */
#if __has_include(<openssl/blowfish.h>)
#include <openssl/blowfish.h>
#endif /* __has_include(<openssl/blowfish.h>) */
#if __has_include(<openssl/bn.h>)
#include <openssl/bn.h>
#endif /* __has_include(<openssl/bn.h>) */
#if __has_include(<openssl/bnerr.h>)
#include <openssl/bnerr.h>
#endif /* __has_include(<openssl/bnerr.h>) */
#if __has_include(<openssl/buffer.h>)
#include <openssl/buffer.h>
#endif /* __has_include(<openssl/buffer.h>) */
#if __has_include(<openssl/buffererr.h>)
#include <openssl/buffererr.h>
#endif /* __has_include(<openssl/buffererr.h>) */
#if __has_include(<openssl/camellia.h>)
#include <openssl/camellia.h>
#endif /* __has_include(<openssl/camellia.h>) */
#if __has_include(<openssl/cast.h>)
#include <openssl/cast.h>
#endif /* __has_include(<openssl/cast.h>) */
#if __has_include(<openssl/cmac.h>)
#include <openssl/cmac.h>
#endif /* __has_include(<openssl/cmac.h>) */
#if __has_include(<openssl/cms.h>)
#include <openssl/cms.h>
#endif /* __has_include(<openssl/cms.h>) */
#if __has_include(<openssl/cmserr.h>)
#include <openssl/cmserr.h>
#endif /* __has_include(<openssl/cmserr.h>) */
#if __has_include(<openssl/comp.h>)
#include <openssl/comp.h>
#endif /* __has_include(<openssl/comp.h>) */
#if __has_include(<openssl/comperr.h>)
#include <openssl/comperr.h>
#endif /* __has_include(<openssl/comperr.h>) */
#if __has_include(<openssl/conf.h>)
#include <openssl/conf.h>
#endif /* __has_include(<openssl/conf.h>) */
#if __has_include(<openssl/conf_api.h>)
#include <openssl/conf_api.h>
#endif /* __has_include(<openssl/conf_api.h>) */
#if __has_include(<openssl/conferr.h>)
#include <openssl/conferr.h>
#endif /* __has_include(<openssl/conferr.h>) */
#if __has_include(<openssl/crypto.h>)
#include <openssl/crypto.h>
#endif /* __has_include(<openssl/crypto.h>) */
#if __has_include(<openssl/cryptoerr.h>)
#include <openssl/cryptoerr.h>
#endif /* __has_include(<openssl/cryptoerr.h>) */
#if __has_include(<openssl/ct.h>)
#include <openssl/ct.h>
#endif /* __has_include(<openssl/ct.h>) */
#if __has_include(<openssl/cterr.h>)
#include <openssl/cterr.h>
#endif /* __has_include(<openssl/cterr.h>) */
#if __has_include(<openssl/des.h>)
#include <openssl/des.h>
#endif /* __has_include(<openssl/des.h>) */
#if __has_include(<openssl/dh.h>)
#include <openssl/dh.h>
#endif /* __has_include(<openssl/dh.h>) */
#if __has_include(<openssl/dherr.h>)
#include <openssl/dherr.h>
#endif /* __has_include(<openssl/dherr.h>) */
#if __has_include(<openssl/dsa.h>)
#include <openssl/dsa.h>
#endif /* __has_include(<openssl/dsa.h>) */
#if __has_include(<openssl/dsaerr.h>)
#include <openssl/dsaerr.h>
#endif /* __has_include(<openssl/dsaerr.h>) */
#if __has_include(<openssl/dtls1.h>)
#include <openssl/dtls1.h>
#endif /* __has_include(<openssl/dtls1.h>) */
#if __has_include(<openssl/e_os2.h>)
#include <openssl/e_os2.h>
#endif /* __has_include(<openssl/e_os2.h>) */
#if __has_include(<openssl/ebcdic.h>)
#include <openssl/ebcdic.h>
#endif /* __has_include(<openssl/ebcdic.h>) */
#if __has_include(<openssl/ec.h>)
#include <openssl/ec.h>
#endif /* __has_include(<openssl/ec.h>) */
#if __has_include(<openssl/ecdh.h>)
#include <openssl/ecdh.h>
#endif /* __has_include(<openssl/ecdh.h>) */
#if __has_include(<openssl/ecdsa.h>)
#include <openssl/ecdsa.h>
#endif /* __has_include(<openssl/ecdsa.h>) */
#if __has_include(<openssl/ecerr.h>)
#include <openssl/ecerr.h>
#endif /* __has_include(<openssl/ecerr.h>) */
#if __has_include(<openssl/engine.h>)
#include <openssl/engine.h>
#endif /* __has_include(<openssl/engine.h>) */
#if __has_include(<openssl/engineerr.h>)
#include <openssl/engineerr.h>
#endif /* __has_include(<openssl/engineerr.h>) */
#if __has_include(<openssl/err.h>)
#include <openssl/err.h>
#endif /* __has_include(<openssl/err.h>) */
#if __has_include(<openssl/evp.h>)
#include <openssl/evp.h>
#endif /* __has_include(<openssl/evp.h>) */
#if __has_include(<openssl/evperr.h>)
#include <openssl/evperr.h>
#endif /* __has_include(<openssl/evperr.h>) */
#if __has_include(<openssl/hmac.h>)
#include <openssl/hmac.h>
#endif /* __has_include(<openssl/hmac.h>) */
#if __has_include(<openssl/idea.h>)
#include <openssl/idea.h>
#endif /* __has_include(<openssl/idea.h>) */
#if __has_include(<openssl/kdf.h>)
#include <openssl/kdf.h>
#endif /* __has_include(<openssl/kdf.h>) */
#if __has_include(<openssl/kdferr.h>)
#include <openssl/kdferr.h>
#endif /* __has_include(<openssl/kdferr.h>) */
#if __has_include(<openssl/lhash.h>)
#include <openssl/lhash.h>
#endif /* __has_include(<openssl/lhash.h>) */
#if __has_include(<openssl/md2.h>)
#include <openssl/md2.h>
#endif /* __has_include(<openssl/md2.h>) */
#if __has_include(<openssl/md4.h>)
#include <openssl/md4.h>
#endif /* __has_include(<openssl/md4.h>) */
#if __has_include(<openssl/md5.h>)
#include <openssl/md5.h>
#endif /* __has_include(<openssl/md5.h>) */
#if __has_include(<openssl/mdc2.h>)
#include <openssl/mdc2.h>
#endif /* __has_include(<openssl/mdc2.h>) */
#if __has_include(<openssl/modes.h>)
#include <openssl/modes.h>
#endif /* __has_include(<openssl/modes.h>) */
#if __has_include(<openssl/obj_mac.h>)
#include <openssl/obj_mac.h>
#endif /* __has_include(<openssl/obj_mac.h>) */
#if __has_include(<openssl/objects.h>)
#include <openssl/objects.h>
#endif /* __has_include(<openssl/objects.h>) */
#if __has_include(<openssl/objectserr.h>)
#include <openssl/objectserr.h>
#endif /* __has_include(<openssl/objectserr.h>) */
#if __has_include(<openssl/ocsp.h>)
#include <openssl/ocsp.h>
#endif /* __has_include(<openssl/ocsp.h>) */
#if __has_include(<openssl/ocsperr.h>)
#include <openssl/ocsperr.h>
#endif /* __has_include(<openssl/ocsperr.h>) */
#if __has_include(<openssl/opensslv.h>)
#include <openssl/opensslv.h>
#endif /* __has_include(<openssl/opensslv.h>) */
#if __has_include(<openssl/ossl_typ.h>)
#include <openssl/ossl_typ.h>
#endif /* __has_include(<openssl/ossl_typ.h>) */
#if __has_include(<openssl/pem.h>)
#include <openssl/pem.h>
#endif /* __has_include(<openssl/pem.h>) */
#if __has_include(<openssl/pem2.h>)
#include <openssl/pem2.h>
#endif /* __has_include(<openssl/pem2.h>) */
#if __has_include(<openssl/pemerr.h>)
#include <openssl/pemerr.h>
#endif /* __has_include(<openssl/pemerr.h>) */
#if __has_include(<openssl/pkcs12.h>)
#include <openssl/pkcs12.h>
#endif /* __has_include(<openssl/pkcs12.h>) */
#if __has_include(<openssl/pkcs12err.h>)
#include <openssl/pkcs12err.h>
#endif /* __has_include(<openssl/pkcs12err.h>) */
#if __has_include(<openssl/pkcs7.h>)
#include <openssl/pkcs7.h>
#endif /* __has_include(<openssl/pkcs7.h>) */
#if __has_include(<openssl/pkcs7err.h>)
#include <openssl/pkcs7err.h>
#endif /* __has_include(<openssl/pkcs7err.h>) */
#if __has_include(<openssl/rand.h>)
#include <openssl/rand.h>
#endif /* __has_include(<openssl/rand.h>) */
#if __has_include(<openssl/rand_drbg.h>)
#include <openssl/rand_drbg.h>
#endif /* __has_include(<openssl/rand_drbg.h>) */
#if __has_include(<openssl/randerr.h>)
#include <openssl/randerr.h>
#endif /* __has_include(<openssl/randerr.h>) */
#if __has_include(<openssl/rc2.h>)
#include <openssl/rc2.h>
#endif /* __has_include(<openssl/rc2.h>) */
#if __has_include(<openssl/rc4.h>)
#include <openssl/rc4.h>
#endif /* __has_include(<openssl/rc4.h>) */
#if __has_include(<openssl/rc5.h>)
#include <openssl/rc5.h>
#endif /* __has_include(<openssl/rc5.h>) */
#if __has_include(<openssl/ripemd.h>)
#include <openssl/ripemd.h>
#endif /* __has_include(<openssl/ripemd.h>) */
#if __has_include(<openssl/rsa.h>)
#include <openssl/rsa.h>
#endif /* __has_include(<openssl/rsa.h>) */
#if __has_include(<openssl/rsaerr.h>)
#include <openssl/rsaerr.h>
#endif /* __has_include(<openssl/rsaerr.h>) */
#if __has_include(<openssl/safestack.h>)
#include <openssl/safestack.h>
#endif /* __has_include(<openssl/safestack.h>) */
#if __has_include(<openssl/seed.h>)
#include <openssl/seed.h>
#endif /* __has_include(<openssl/seed.h>) */
#if __has_include(<openssl/sha.h>)
#include <openssl/sha.h>
#endif /* __has_include(<openssl/sha.h>) */
#if __has_include(<openssl/srp.h>)
#include <openssl/srp.h>
#endif /* __has_include(<openssl/srp.h>) */
#if __has_include(<openssl/srtp.h>)
#include <openssl/srtp.h>
#endif /* __has_include(<openssl/srtp.h>) */
#if __has_include(<openssl/ssl.h>)
#include <openssl/ssl.h>
#endif /* __has_include(<openssl/ssl.h>) */
#if __has_include(<openssl/ssl2.h>)
#include <openssl/ssl2.h>
#endif /* __has_include(<openssl/ssl2.h>) */
#if __has_include(<openssl/ssl3.h>)
#include <openssl/ssl3.h>
#endif /* __has_include(<openssl/ssl3.h>) */
#if __has_include(<openssl/sslerr.h>)
#include <openssl/sslerr.h>
#endif /* __has_include(<openssl/sslerr.h>) */
#if __has_include(<openssl/stack.h>)
#include <openssl/stack.h>
#endif /* __has_include(<openssl/stack.h>) */
#if __has_include(<openssl/store.h>)
#include <openssl/store.h>
#endif /* __has_include(<openssl/store.h>) */
#if __has_include(<openssl/storeerr.h>)
#include <openssl/storeerr.h>
#endif /* __has_include(<openssl/storeerr.h>) */
#if __has_include(<openssl/symhacks.h>)
#include <openssl/symhacks.h>
#endif /* __has_include(<openssl/symhacks.h>) */
#if __has_include(<openssl/tls1.h>)
#include <openssl/tls1.h>
#endif /* __has_include(<openssl/tls1.h>) */
#if __has_include(<openssl/ts.h>)
#include <openssl/ts.h>
#endif /* __has_include(<openssl/ts.h>) */
#if __has_include(<openssl/tserr.h>)
#include <openssl/tserr.h>
#endif /* __has_include(<openssl/tserr.h>) */
#if __has_include(<openssl/txt_db.h>)
#include <openssl/txt_db.h>
#endif /* __has_include(<openssl/txt_db.h>) */
#if __has_include(<openssl/ui.h>)
#include <openssl/ui.h>
#endif /* __has_include(<openssl/ui.h>) */
#if __has_include(<openssl/uierr.h>)
#include <openssl/uierr.h>
#endif /* __has_include(<openssl/uierr.h>) */
#if __has_include(<openssl/whrlpool.h>)
#include <openssl/whrlpool.h>
#endif /* __has_include(<openssl/whrlpool.h>) */
#if __has_include(<openssl/x509.h>)
#include <openssl/x509.h>
#endif /* __has_include(<openssl/x509.h>) */
#if __has_include(<openssl/x509_vfy.h>)
#include <openssl/x509_vfy.h>
#endif /* __has_include(<openssl/x509_vfy.h>) */
#if __has_include(<openssl/x509err.h>)
#include <openssl/x509err.h>
#endif /* __has_include(<openssl/x509err.h>) */
#if __has_include(<openssl/x509v3.h>)
#include <openssl/x509v3.h>
#endif /* __has_include(<openssl/x509v3.h>) */
#if __has_include(<openssl/x509v3err.h>)
#include <openssl/x509v3err.h>
#endif /* __has_include(<openssl/x509v3err.h>) */
#include <optimized/error.h>
#include <optimized/fenv.h>
#include <optimized/ssp.string.h>
#include <optimized/string.h>
#include <optimized/unistd.h>
#include <osfcn.h>
#if __has_include(<panel.h>)
#include <panel.h>
#endif /* __has_include(<panel.h>) */
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
#include <parts/waitmacros.h>
#include <parts/wchar/format-printer.h>
#include <parts/wchar/process.h>
#include <parts/wchar/stdio.h>
#include <parts/wchar/stdlib.h>
#include <parts/wchar/sys/stat.h>
#include <parts/wchar/unistd.h>
#include <parts/wchar/utime.h>
#include <paths.h>
#if __has_include(<pciaccess.h>)
#include <pciaccess.h>
#endif /* __has_include(<pciaccess.h>) */
#if __has_include(<pixman-1/pixman.h>)
#include <pixman-1/pixman.h>
#endif /* __has_include(<pixman-1/pixman.h>) */
#if __has_include(<pixman.h>)
#include <pixman.h>
#endif /* __has_include(<pixman.h>) */
#if __has_include(<png.h>)
#include <png.h>
#endif /* __has_include(<png.h>) */
#if __has_include(<pngconf.h>)
#include <pngconf.h>
#endif /* __has_include(<pngconf.h>) */
#if __has_include(<pnglibconf.h>)
#include <pnglibconf.h>
#endif /* __has_include(<pnglibconf.h>) */
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
#include <sys/_pthreadtypes.h>
#include <sys/_sigset.h>
#include <sys/_stdint.h>
#include <sys/_timespec.h>
#include <sys/_timeval.h>
#include <sys/_types.h>
#include <sys/acct.h>
#include <sys/auxv.h>
#include <sys/bitstring.h>
#include <sys/bitypes.h>
#include <sys/cdefs.h>
#include <sys/config.h>
#include <sys/dir.h>
#include <sys/elf.h>
#include <sys/endian.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/eventfd.h>
#include <sys/fcntl.h>
#include <sys/features.h>
#include <sys/file.h>
#include <sys/filio.h>
#include <sys/fsuid.h>
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
#include <sys/random.h>
#include <sys/reboot.h>
#include <sys/resource.h>
#include <sys/sched.h>
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
#include <sys/stdarg.h>
#include <sys/stdbool.h>
#include <sys/stdint.h>
#include <sys/stropts.h>
#include <sys/swap.h>
#include <sys/syscall-proto.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <sys/syslimits.h>
#include <sys/syslog.h>
#include <sys/sysmacros.h>
#include <sys/termio.h>
#include <sys/termios.h>
#include <sys/termiox.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/timerfd.h>
#include <sys/times.h>
#include <sys/timex.h>
#include <sys/ttychars.h>
#include <sys/ttydefaults.h>
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
#include <tar.h>
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
#include <util.h>
#include <utime.h>
#include <utmp.h>
#include <utmpx.h>
#if __has_include(<uuid/uuid.h>)
#include <uuid/uuid.h>
#endif /* __has_include(<uuid/uuid.h>) */
#if __has_include(<uuid.h>)
#include <uuid.h>
#endif /* __has_include(<uuid.h>) */
#include <vadefs.h>
#include <values.h>
#include <vfork.h>
#include <wait.h>
#include <wchar.h>
#include <wctype.h>
#if __has_include(<xf86drm.h>)
#include <xf86drm.h>
#endif /* __has_include(<xf86drm.h>) */
#if __has_include(<xf86drmMode.h>)
#include <xf86drmMode.h>
#endif /* __has_include(<xf86drmMode.h>) */
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
 *    which breaks assigning them to prototype pointers. */
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

