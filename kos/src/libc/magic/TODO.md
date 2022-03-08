
### Missing functions (ABI)

- GLibc:
	- Misc:
		- `__register_atfork()`
		- `gnu_get_libc_version()`
		- `gnu_get_libc_release()`
		- `inotify_add_watch()`
		- `inotify_init()`
		- `inotify_rm_watch()`
		- `pmap_getport()`
		- `pmap_set()`
		- `pmap_unset()`
		- `svc_register()`
		- `svc_run()`
		- `svc_sendreply()`
		- `svctcp_create()`
		- `svcudp_create()`
		- `xdr_u_int()`
		- `xdrstdio_create()`
	- `<ssp/unistd.h>`:
		- `__getcwd_chk()`
		- `__getgroups_chk()`
		- `__gethostname_chk()`
		- `__getlogin_r_chk()`
		- `__pread64_chk()`
		- `__pread_chk()`
		- `__read_chk()`
		- `__readlink_chk()`
		- `__realpath_chk()`
		- `__ttyname_r_chk()`
	- `<ssp/stdio.h>`:
		- `__fgets_chk()`
		- `__fgets_unlocked_chk()`
		- `__fprintf_chk()`
		- `__printf_chk()`
		- `__snprintf_chk()`
		- `__sprintf_chk()`
		- `__vfprintf_chk()`
		- `__vprintf_chk()`
		- `__vsnprintf_chk()`
		- `__vsprintf_chk()`
	- `<ssp/wchar.h>`:
		- `__fgetws_chk()`
		- `__fgetws_unlocked_chk()`
		- `__fwprintf_chk()`
		- `__mbsnrtowcs_chk()`
		- `__mbsrtowcs_chk()`
		- `__mbstowcs_chk()`
		- `__swprintf_chk()`
		- `__vfwprintf_chk()`
		- `__vswprintf_chk()`
		- `__vwprintf_chk()`
		- `__wcpcpy_chk()`
		- `__wcpncpy_chk()`
		- `__wcrtomb_chk()`
		- `__wcscat_chk()`
		- `__wcscpy_chk()`
		- `__wcsncat_chk()`
		- `__wcsncpy_chk()`
		- `__wcsnrtombs_chk()`
		- `__wcsrtombs_chk()`
		- `__wcstod_internal()`
		- `__wcstof_internal()`
		- `__wcstol_internal()`
		- `__wcstold_internal()`
		- `__wcstombs_chk()`
		- `__wcstoul_internal()`
		- `__wctomb_chk()`
		- `__wmemcpy_chk()`
		- `__wmemmove_chk()`
		- `__wmempcpy_chk()`
		- `__wmemset_chk()`
		- `__wprintf_chk()`
	- `<ssp/sys/socket.h>`:
		- `__recv_chk()`
		- `__recvfrom_chk()`
	- `<stdlib.h>`:
		- `__strtod_internal()`
		- `__strtof_internal()`
		- `__strtol_internal()`
		- `__strtold_internal()`
		- `__strtoll_internal()`
		- `__strtoul_internal()`
		- `__strtoull_internal()`
	- `<ssp/sys/syslog.h>`:
		- `__syslog_chk()`
		- `__vsyslog_chk()`
- Misc
	- `walkcontext()`
	- `int ungetchar(int ch)`     (same as `ungetc(ch, stdin)`)
	- `int optreset`
	- `bsd_getopt()`





### Missing headers

- `<a.out.h>`               (GLibc!)
- `<argp.h>`                (GLibc!)
- `<bsd/netinet/ip_icmp.h>` (libbsd)
- `<bsd/md5.h>`             (libbsd)
- `<bsd/sys/tree.h>`        (libbsd)
- `<bsd/timeconv.h>`        (libbsd)
- `<bsd/vis.h>`             (libbsd)
- `<conio.h>`               (dos)
- `<fmtmsg.h>`              (GLibc!)
- `<fstab.h>`               (GLibc!)
- `<gnu-versions.h>`        (GLibc!)
- `<gnu/libc-version.h>`    (GLibc!)
- `<gshadow.h>`             (GLibc!)
- `<mbctype.h>`             (msvcrt)
- `<mbstring.h>`            (msvcrt)
- `<mcheck.h>`              (GLibc!)
- `<obstack.h>`             (GLibc!)
- `<regexp.h>`              (GLibc!)
- `<resolv.h>`              (GLibc!)
- `<stab.h>`                (GLibc!)
- `<sys/capability.h>`      (linux: found in `/usr/include/sys/capability.h`; aka not in arch-headers!)
- `<sys/fanotify.h>`        (linux)
- `<sys/gmon.h>`            (linux)
- `<sys/gmon_out.h>`        (linux: Only some macros, and structs)
- `<sys/inotify.h>`         (linux)
- `<sys/kdaemon.h>`         (uClibc)
- `<sys/machine.h>`         (AIX???)
- `<sys/mtio.h>`            (linux: Only some macros, and structs. - Mainly interesting for ioctl() & the kernel)
- `<sys/personality.h>`     (linux)
- `<sys/prctl.h>`           (linux)
- `<sys/profil.h>`          (linux)
- `<sys/quota.h>`           (linux)
- `<sys/raw.h>`             (linux: Only some macros, and structs. - Mainly interesting for ioctl() & the kernel)
- `<sys/reg.h>`             (linux)
- `<sys/sdt.h>`             (NetBSD, OpenSolaris)
- `<sys/soundcard.h>`       (linux)
- `<sys/sysctl.h>`          (linux)
- `<sys/va_impl.h>`         (OpenSolaris)
- `<sys/va_list.h>`         (OpenSolaris)
- `<sys/varargs.h>`         (OpenSolaris)
- `<sys/vlimit.h>`          (GLibc!)
- `<sys/vtimes.h>`          (linux)
- `<timeconv.h>`            (libbsd)
- `<thread_db.h>`           (GLibc!)
- `<wordexp.h>`             (GLibc!)


### Referenced, but origin unknown

- `<cthreads.h>`           (Python ./configure)
- `<fp.h>`                 (libstdc++ ./configure)


### Unlikely to ever be added

- `<nlist.h>`              (libbsd)
- `<bsd/nlist.h>`          (libbsd)
- `<_G_config.h>`          (GLibc!)
- `<gconv.h>`              (GLibc!)
- `<nss.h>`                (GLibc!)
- `<printf.h>`             (GLibc!)
- `<rpc/auth.h>`
- `<rpc/auth_des.h>`
- `<rpc/auth_unix.h>`
- `<rpc/clnt.h>`
- `<rpc/des_crypt.h>`
- `<rpc/pmap_clnt.h>`
- `<rpc/pmap_prot.h>`
- `<rpc/pmap_rmt.h>`
- `<rpc/rpc.h>`
- `<rpc/rpc_des.h>`
- `<rpc/rpc_msg.h>`
- `<rpc/svc.h>`
- `<rpc/svc_auth.h>`
- `<rpc/types.h>`
- `<rpc/xdr.h>`

### Misc TODOs

- TODO: `__CORRECT_ISO_CPP_MATH_H_PROTO` interferes with libstdc++'s autoconf detection...
- TODO: libstdc++ doesn't detect `_GLIBCXX_HAVE_LINUX_FUTEX` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_HAVE_MACHINE_ENDIAN_H` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_HAVE_STRERROR_L` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_HAVE_STRXFRM_L` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_SCHED_YIELD` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_NANOSLEEP` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_SENDFILE` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_CLOCK_GETTIME_SYSCALL` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_CLOCK_MONOTONIC` properly
- TODO: libstdc++ doesn't detect `_GLIBCXX_USE_CLOCK_REALTIME` properly
- TODO: Add support for `_GLIBCXX_HAVE___CXA_THREAD_ATEXIT`
- TODO: Add support for `_GLIBCXX_HAVE___CXA_THREAD_ATEXIT_IMPL`

- TODO: Add support for (more) `*_chk` variants (using `__builtin_object_size()`)
