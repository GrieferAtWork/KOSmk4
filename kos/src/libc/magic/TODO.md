
### Missing functions (ABI)

- Glibc:
	- Misc:
		- `__register_atfork()`
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
	- `<glob.h>`:
		- `glob_pattern_p()`
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
		- `__confstr_chk()`
		- `__getdomainname_chk()`
		- `__getwd_chk()`
		- `__readlinkat_chk()`
	- `<ssp/setjmp.h>`:
		- `__longjmp_chk()`
	- `<ssp/stdio.h>`:
		- `__fgets_chk()`
		- `__fgets_unlocked_chk()`
		- `__fprintf_chk()`
		- `__vfprintf_chk()`
		- `__printf_chk()`
		- `__vprintf_chk()`
		- `__snprintf_chk()`
		- `__vsnprintf_chk()`
		- `__sprintf_chk()`
		- `__vsprintf_chk()`
		- `__asprintf_chk()`
		- `__vasprintf_chk()`
		- `__dprintf_chk()`
		- `__vdprintf_chk()`
		- `__fread_chk()`
		- `__fread_unlocked_chk()`
		- `__gets_chk()`
		- `__obstack_printf_chk()`
		- `__obstack_vprintf_chk()`
	- `<ssp/stdlib.h>`:
		- `__ptsname_r_chk()`
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
	- `<ssp/sys/poll.h>`:
		- `__poll_chk()`
		- `__ppoll_chk()`
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
	- <dl.h>  (http://3kranger.com/HP3000/mpeix/en-hpux/B2355-90683/shl_load.3X.html)
		- `shl_t shl_load(const char *path, int flags, long address);`
		- `int shl_findsym(shl_t *handle, const char *sym, short type, void *value);`
		- `int shl_definesym(const char *sym, short type, long value, int flags);`
		- `int shl_getsymbols(shl_t handle, short type, int flags, void *(*memory) (), struct shl_symbol **symbols);`
		- `int shl_unload(shl_t handle);`
		- `int shl_get(int index, struct shl_descriptor **desc);`
		- `int shl_gethandle(shl_t handle, struct shl_descriptor **desc);`
		- `int shl_get_r(int index, struct shl_descriptor *desc);`
		- `int shl_gethandle_r(shl_t handle, struct shl_descriptor *desc);`
	- <dlfcn.h>  (http://3kranger.com/HP3000/mpeix/en-hpux/B2355-90683/dlgetname.3C.html)
		- `char *dlgetname(struct load_module_desc *desc, size_t desc_size, void *(*read_tgt_mem)(void* buffer, unsigned long long ptr, size_t bufsiz, int ident), int ident_parm, unsigned long long load_map_parm);`
		- `unsigned long dlmodinfo(unsigned long ip_value, struct load_module_desc *desc, size_t desc_size, void *(*read_tgt_mem)(void* buffer, unsigned long ptr, size_t bufsiz, int ident), int ident_parm, uint64_t load_map_parm);`
		- `void *dlget(unsigned int index, struct load_module_desc *desc, size_t desc_size);`
	- <ucontext.h>
		- `int signalcontext(ucontext_t *ucp, int sig, __sighandler_t *func);`
	- <unistd.h>
		- #ifdef __USE_BSD: `int execvP(char const *file, char const *search_path, char *const argv[]);`
		- #ifdef __USE_BSD: `int execvPe(char const *file, char const *search_path, char *const argv[], char *const envp[]);`
	- <stdlib.h>
		- #ifdef __USE_BSD: `char *fdevname($fd_t fd);` (partner to "devname")
		- #ifdef __USE_BSD: `char *fdevname_r($fd_t fd, char *buf, __STDC_INT_AS_SIZE_T bufsize);` (partner to "devname_r")






### Missing linux headers referenced by busybox's networking code

- `<linux/ethtool.h>`           (linux)
- `<linux/filter.h>`            (linux)
- `<linux/if.h>`                (linux)
- `<linux/if_addr.h>`           (linux)
- `<linux/if_bonding.h>`        (linux)
- `<linux/if_link.h>`           (linux)
- `<linux/if_packet.h>`         (linux)
- `<linux/if_slip.h>`           (linux)
- `<linux/if_tun.h>`            (linux)
- `<linux/if_vlan.h>`           (linux)
- `<linux/mii.h>`               (linux)
- `<linux/neighbour.h>`         (linux)
- `<linux/netlink.h>`           (linux)
- `<linux/pkt_sched.h>`         (linux)
- `<linux/rtnetlink.h>`         (linux)
- `<linux/version.h>`           (linux)
- `<linux/wireless.h>`          (linux)



### Missing headers

- `<stdbit.h>`                  (STDC)
- `<stdckdint.h>`               (STDC)
- `<a.out.h>`                   (Glibc)
- `<asm-generic/perf_regs.h>`   (linux)
- `<asm-generic/ptrace.h>`      (linux)
- `<asm-generic/sembuf.h>`      (linux)
- `<asm-generic/shmbuf.h>`      (linux)
- `<asm-generic/sigcontext.h>`  (linux)
- `<asm/perf_regs.h>`           (linux)
- `<asm/ptrace.h>`              (linux)
- `<asm/sembuf.h>`              (linux)
- `<asm/shmbuf.h>`              (linux)
- `<asm/sigcontext.h>`          (linux)
- `<bits/types/res_state.h>`    (Glibc)
- `<bits/types/struct_statx.h>` (Glibc)
- `<bits/types/struct_statx_timestamp.h>` (Glibc)
- `<bm.h>`                      (NetBSD)
- `<bsd/netinet/ip_icmp.h>`     (libbsd)
- `<bsd/md5.h>`                 (libbsd)
- `<bsd/sys/tree.h>`            (libbsd)
- `<bsd/timeconv.h>`            (libbsd)
- `<corecrt_share.h>`           (DOS)
- `<corecrt_terminate.h>`       (DOS)
- `<gshadow.h>`                 (Glibc)
- `<mcheck.h>`                  (Glibc)
- `<share.h>`                   (DOS)
- `<stab.h>`                    (Glibc)
- `<sys/fanotify.h>`            (linux)
- `<sys/gmon.h>`                (linux)
- `<sys/gmon_out.h>`            (linux: Only some macros, and structs)
- `<sys/kdaemon.h>`             (uClibc)
- `<sys/locking.h>`             (DOS)
- `<sys/machine.h>`             (AIX???)
- `<sys/mtio.h>`                (linux: Only some macros, and structs. - Mainly interesting for ioctl() & the kernel)
- `<sys/personality.h>`         (linux)
- `<sys/quota.h>`               (linux)
- `<sys/raw.h>`                 (linux: Only some macros, and structs. - Mainly interesting for ioctl() & the kernel)
- `<sys/reg.h>`                 (linux)
- `<sys/sdt.h>`                 (NetBSD, OpenSolaris)
- `<sys/soundcard.h>`           (linux)
- `<sys/sysctl.h>`              (linux)
- `<sys/va_impl.h>`             (OpenSolaris)
- `<sys/va_list.h>`             (OpenSolaris)
- `<sys/varargs.h>`             (OpenSolaris)
- `<timeconv.h>`                (libbsd)
- `<thread_db.h>`               (Glibc)
- libiberty:
	- `<libiberty/fibheap.h>`
	- `<libiberty/floatformat.h>`
	- `<libiberty/hashtab.h>`
	- `<libiberty/safe-ctype.h>`
	- `<libiberty/splay-tree.h>`



### Referenced, but origin unknown

- `<fp.h>`                  (libstdc++ ./configure)


### Unlikely to ever be added

- `<libiberty/demangle.h>`
- `<nlist.h>`               (libbsd)
- `<bsd/nlist.h>`           (libbsd)
- `<_G_config.h>`           (Glibc)
- `<gconv.h>`               (Glibc)
- `<nss.h>`                 (Glibc)
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
