/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[declare_user_export(environ, _environ, __environ)]
%[declare_user_export(__peb, __argc, __argv, _pgmptr)]
%[declare_user_export(program_invocation_name, __progname_full)]
%[declare_user_export(program_invocation_short_name, __progname)]
%[default:nodos]


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <kos/anno.h>
)]%{

}%[insert:prefix(
#include <unistd.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pos_t_defined
#define __pos_t_defined
typedef __pos_t pos_t; /* File/device position */
#endif /* !__pos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __pos64_t_defined
#define __pos64_t_defined
typedef __pos64_t pos64_t; /* File/device position */
#endif /* !__pos64_t_defined */
#endif /* __USE_LARGEFILE64 */

}

[[cp, throws, noreturn, doc_alias("execv"), argument_names(path, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execv([[in]] char const *__restrict path, [[in]] __TARGV);

[[cp, throws, noreturn, doc_alias("execve"), argument_names(path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execve([[in]] char const *__restrict path, [[in]] __TARGV, [[in]] __TENVP);

[[cp, throws, noreturn, doc_alias("execvp"), argument_names(file, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execvp([[in]] char const *__restrict file, [[in]] __TARGV);

[[cp, throws, impl_include("<parts/redirect-exec.h>"), doc_alias("execl")]]
[[requires_dependent_function(Execv), ATTR_SENTINEL, noreturn]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execl([[in]] char const *__restrict path, [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_XEXECL(char, Execv, path, args)
}

[[cp, throws, impl_include("<parts/redirect-exec.h>"), doc_alias("execle")]]
[[requires_dependent_function(Execve), ATTR_SENTINEL_O(1), noreturn]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execle([[in]] char const *__restrict path, [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] (char **)environ*/) {
	__REDIRECT_XEXECLE(char, Execve, path, args)
}

[[cp, throws, impl_include("<parts/redirect-exec.h>"), doc_alias("execlp")]]
[[requires_dependent_function(Execvp), ATTR_SENTINEL, noreturn]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execpl([[in]] char const *__restrict file, [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_XEXECL(char, Execvp, file, args)
}

[[cp, throws, impl_include("<parts/redirect-exec.h>"), doc_alias("execle")]]
[[requires_dependent_function(Execvpe), ATTR_SENTINEL_O(1), noreturn]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execlpe([[in]] char const *__restrict file, [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] (char **)environ*/) {
	__REDIRECT_XEXECLE(char, Execvpe, file, args)
}


[[throws, doc_alias("pipe"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.access")]]
void Pipe([[out]] $fd_t pipedes[2]);


[[cp, throws, doc_alias("fsync")]]
[[decl_include("<bits/types.h>")]]
[[userimpl, alias("FDataSync")]]
[[section(".text.crt{|.dos}.except.io.sync")]]
void FSync([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-Op */
}


[[throws, doc_alias("setpgid"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
void SetPGid($pid_t pid, $pid_t pgid);

[[throws, doc_alias("setsid"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
$pid_t SetSid();

[[throws, doc_alias("setuid"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
void SetUid($uid_t uid);

[[throws, doc_alias("setgid"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
void SetGid($gid_t gid);

[[throws, wunused, decl_include("<bits/types.h>"), doc_alias("fork")]]
[[section(".text.crt{|.dos}.except.sched.access")]]
$pid_t Fork();

[[cp, throws, wunused, doc_alias("fpathconf")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
$longptr_t FPathConf([[fdarg]] $fd_t fd, __STDC_INT_AS_UINT_T name);

[[throws, wunused, doc_alias("tcgetpgrp")]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(Ioctl) && defined(__TIOCGPGRP))]]
[[section(".text.crt{|.dos}.except.io.tty")]]
$pid_t TCGetPGrp([[fdarg]] $fd_t fd) {
	pid_t result;
	Ioctl(fd, __TIOCGPGRP, &result);
	return result;
}

[[throws, doc_alias("tcsetpgrp")]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(Ioctl) && defined(__TIOCSPGRP))]]
[[section(".text.crt{|.dos}.except.io.tty")]]
void TCSetPGrp([[fdarg]] $fd_t fd, $pid_t pgrp_id) {
	Ioctl(fd, __TIOCSPGRP, &pgrp_id);
}


[[cp, throws, doc_alias("pathconf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[userimpl, requires_include("<asm/os/oflags.h>")]]
[[requires($has_function(FPathConf) && $has_function(Open) && defined(__O_RDONLY))]]
[[impl_include("<kos/bits/except-compiler.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
$longptr_t PathConf([[in]] char const *path, __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = Open(path, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_if defined(__RAII_FINALLY) && $has_function(close)@@
	__RAII_FINALLY { (void)close(fd); }
@@pp_endif@@
	result = FPathConf(fd, name);
	return result;
}


[[cp, throws, decl_include("<bits/types.h>"), doc_alias("chown")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(FChOwnAt))]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void ChOwn([[in]] char const *file, $uid_t owner, $gid_t group) {
	FChOwnAt(__AT_FDCWD, file, owner, group, 0);
}

[[cp, throws, doc_alias("link")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(LinkAt))]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void Link([[in]] char const *from, [[in]] char const *to) {
	LinkAt(__AT_FDCWD, from, __AT_FDCWD, to, 0);
}

[[cp, throws, doc_alias("read")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.read")]]
size_t Read([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize);

[[cp, throws, doc_alias("write")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.write")]]
size_t Write([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize);

%#ifdef __USE_KOS
[[cp, throws, doc_alias("readall")]]
[[decl_include("<bits/types.h>")]]
[[requires_function(Read, lseek)]]
[[impl_include("<libc/errno.h>", "<kos/except.h>")]]
[[section(".text.crt{|.dos}.except.io.read")]]
size_t ReadAll([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf, size_t bufsize) {
	size_t result, temp;
	result = Read(fd, buf, bufsize);
	if (result != 0 && result < bufsize) {
		/* Keep on reading */
		for (;;) {
@@pp_if defined(@TRY@)@@
			@TRY@
@@pp_endif@@
			{
				temp = Read(fd,
				           (byte_t *)buf + (size_t)result,
				            bufsize - (size_t)result);
			}
@@pp_if defined(@TRY@)@@
			@EXCEPT@ {
@@pp_ifdef libc_geterrno@@
				int old_error = libc_geterrno();
@@pp_endif@@
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
@@pp_ifdef libc_geterrno@@
				(void)libc_seterrno(old_error);
@@pp_endif@@
				@RETHROW@();
			}
@@pp_endif@@
			if (!temp) {
@@pp_ifdef libc_geterrno@@
				int old_error = libc_geterrno();
@@pp_endif@@
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
@@pp_ifdef libc_geterrno@@
				(void)libc_seterrno(old_error);
@@pp_endif@@
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}

[[cp, throws, doc_alias("writeall")]]
[[decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), export_alias("WritePrinter")]]
[[requires_function(Write)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.except.io.write")]]
size_t WriteAll([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf, size_t bufsize) {
	size_t result, temp;
	result = Write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = Write(fd,
			             (byte_t *)buf + (size_t)result,
			             bufsize - (size_t)result);
			if (temp == 0) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}

[[cp, throws, doc_alias("write_printer")]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")!defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__))]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), preferred_alias("WriteAll")]]
[[requires_function(WriteAll)]]
[[impl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.write")]]
ssize_t WritePrinter(/*[[fdwrite]] fd_t*/ void *fd,
                     [[in(bufsize)]] char const *__restrict buf,
                     size_t bufsize) {
	return (ssize_t)WriteAll((fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(uintptr_t)fd, buf, bufsize);
}

%(auto_header){
#if !defined(__KERNEL__) && (defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__)
/* Define the libc internal header variant as an alias for WriteAll() when it would otherwise not be defined. */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_WritePrinter)(void *fd, char const *__restrict buf, size_t bufsize) THROWS(...) ASMNAME("libc_WriteAll");
#endif /* !__KERNEL__ && (__LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) */
}

%{

#ifndef WRITE_PRINTER_ARG
/* >> void *WRITE_PRINTER_ARG([[fdwrite]] fd_t fd);
 * Encode a given `fd' as an argument to `write_printer(3)' */
#define WRITE_PRINTER_ARG(fd) ((void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(fd))
#endif /* !WRITE_PRINTER_ARG */
}

%#endif /* __USE_KOS */


[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("crt_lseek32"), ignore, nocrt, alias("LSeek")]]
$pos32_t crt_LSeek32([[fdarg]] $fd_t fd, $off32_t offset, int whence);

[[throws, decl_include("<bits/types.h>"), doc_alias("lseek"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("LSeek")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("LSeek64")]]
[[userimpl, requires($has_function(crt_LSeek32) || $has_function(LSeek64))]]
[[section(".text.crt{|.dos}.except.io.seek")]]
$pos_t LSeek([[fdarg]] $fd_t fd, $off_t offset, int whence) {
@@pp_if $has_function(crt_LSeek32)@@
	return crt_LSeek32(fd, ($off32_t)offset, whence);
@@pp_else@@
	return LSeek64(fd, ($off64_t)offset, whence);
@@pp_endif@@
}

[[throws, doc_alias("dup2")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup2([[fdarg]] $fd_t oldfd, [[no_fdarg]] $fd_t newfd);

[[throws, wunused, doc_alias("dup")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup([[fdarg]] $fd_t fd);

[[cp, throws, doc_alias("chdir")]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
void ChDir([[in]] char const *path);

[[cp, throws, doc_alias("getcwd")]]
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
char *GetCwd([[out(? <= bufsize)]] char *buf, size_t bufsize);

[[cp, throws, doc_alias("unlink")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(UnlinkAt))]]
[[section(".text.crt{|.dos}.fs.modify")]]
void Unlink([[in]] char const *file) {
	UnlinkAt(__AT_FDCWD, file, 0);
}

[[cp, throws, doc_alias("rmdir")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(UnlinkAt))]]
[[section(".text.crt{|.dos}.fs.modify")]]
void RmDir([[in]] char const *path) {
	UnlinkAt(__AT_FDCWD, path, 0x0200); /* AT_REMOVEDIR */
}

%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("fchownat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void FChOwnAt([[dirfd]] $fd_t dfd, [[in]] char const *file,
              $uid_t owner, $gid_t group, $atflag_t flags);

[[cp, throws, doc_alias("linkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void LinkAt([[dirfd]] $fd_t fromfd, [[in]] char const *from,
            [[dirfd]] $fd_t tofd, [[in]] char const *to,
            $atflag_t flags);

[[cp, throws, doc_alias("symlinkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void SymlinkAt([[in]] char const *link_text, [[dirfd]] $fd_t tofd,
               [[in]] char const *target_path);

[[cp, throws, doc_alias("readlinkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
size_t ReadLinkAt([[dirfd]] $fd_t dfd, [[in]] char const *__restrict path,
                  [[out(return <= buflen)]] char *__restrict buf,
                  size_t buflen);

[[cp, throws, doc_alias("unlinkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void UnlinkAt([[dirfd]] $fd_t dfd, [[in]] char const *name, $atflag_t flags);

%#ifdef __USE_KOS

[[cp, throws, doc_alias("fchdirat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
void FChDirAt([[dirfd]] $fd_t dfd, [[in]] char const *path, $atflag_t flags);

[[cp, throws, doc_alias("fsymlinkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
void FSymlinkAt([[in]] char const *link_text, [[dirfd]] $fd_t tofd,
                [[in]] char const *target_path, $atflag_t flags);

[[cp, throws, doc_alias("freadlinkat")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.property")]]
size_t FReadLinkAt([[dirfd]] $fd_t dfd, [[in]] char const *__restrict path,
                   [[out(return<= buflen)]] char *__restrict buf,
                   size_t buflen, $atflag_t flags);

%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */


%
%
%#ifdef __USE_LARGEFILE64
[[throws, doc_alias("lseek64")]]
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(LSeek)]]
[[userimpl, requires_function(crt_LSeek32)]]
[[section(".text.crt{|.dos}.except.io.large.seek")]]
$pos64_t LSeek64([[fdarg]] $fd_t fd, $off64_t offset, int whence) {
	return crt_LSeek32(fd, (__off32_t)offset, whence);
}
%#endif /* __USE_LARGEFILE64 */


%
%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)

[[cp, throws, decl_include("<bits/types.h>"), doc_alias("pread"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PRead")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PRead64")]]
[[userimpl, requires($has_function(PRead32) || $has_function(PRead64))]]
[[section(".text.crt{|.dos}.except.io.read")]]
size_t PRead([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize, pos_t offset) {
@@pp_if $has_function(PRead32)@@
	return PRead32(fd, buf, bufsize, (pos32_t)offset);
@@pp_else@@
	return PRead64(fd, buf, bufsize, (pos64_t)offset);
@@pp_endif@@
}

[[cp, throws, decl_include("<bits/types.h>"), doc_alias("pwrite"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PWrite")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PWrite64")]]
[[userimpl, requires($has_function(PWrite32) || $has_function(PWrite64))]]
[[section(".text.crt{|.dos}.except.io.write")]]
size_t PWrite([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize, pos_t offset) {
@@pp_if $has_function(PWrite32)@@
	return PWrite32(fd, buf, bufsize, (pos32_t)offset);
@@pp_else@@
	return PWrite64(fd, buf, bufsize, (pos64_t)offset);
@@pp_endif@@
}


%#ifdef __USE_KOS
[[cp, throws, decl_include("<bits/types.h>"), doc_alias("preadall"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PReadAll")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PReadAll64")]]
[[requires_function(PRead)]]
[[section(".text.crt{|.dos}.except.io.read")]]
size_t PReadAll([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf, size_t bufsize, pos_t offset) {
	size_t result, temp;
	result = PRead(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = PRead(fd,
			             (byte_t *)buf + result,
			             bufsize - result,
			             offset + result);
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}

[[cp, throws, decl_include("<bits/types.h>"), doc_alias("pwriteall"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PWriteAll")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("PWriteAll64")]]
[[requires_function(PWrite)]]
[[section(".text.crt{|.dos}.except.io.write")]]
size_t PWriteAll([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf, size_t bufsize, pos_t offset) {
	size_t result, temp;
	result = PWrite(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = PWrite(fd,
			              (byte_t const *)buf + result,
			              bufsize - result,
			              offset + result);
			if (!temp)
				break;
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */

%#ifdef __USE_LARGEFILE64

[[cp, throws, ignore, nocrt, alias("PRead"), decl_include("<bits/types.h>")]]
size_t PRead32([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, ignore, nocrt, alias("PWrite"), decl_include("<bits/types.h>")]]
size_t PWrite32([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(PRead), doc_alias("pread64")]]
[[userimpl, requires_function(PRead32)]]
[[section(".text.crt{|.dos}.except.io.large.read")]]
size_t PRead64([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize, pos64_t offset) {
	return PRead32(fd, buf, bufsize, (pos32_t)offset);
}

[[cp, throws, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(PWrite), doc_alias("pwrite64")]]
[[userimpl, requires_function(PWrite32)]]
[[section(".text.crt{|.dos}.except.io.large.write")]]
size_t PWrite64([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize, pos64_t offset) {
	return PWrite32(fd, buf, bufsize, (pos32_t)offset);
}

%#ifdef __USE_KOS
[[cp, throws, decl_include("<bits/types.h>"), ignore, nocrt, alias("PReadAll")]]
size_t PReadAll32([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize, $pos32_t offset);
[[cp, throws, decl_include("<bits/types.h>"), ignore, nocrt, alias("PWriteAll")]]
size_t PWriteAll32([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(PReadAll), doc_alias("preadall64")]]
[[requires_function(PRead64)]]
[[section(".text.crt{|.dos}.except.io.large.read")]]
size_t PReadAll64([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf, size_t bufsize, pos64_t offset) {
	size_t result, temp;
	result = PRead64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = PRead64(fd,
			               (byte_t *)buf + result,
			               bufsize - result,
			               offset + result);
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}

[[cp, throws, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(PWriteAll), doc_alias("pwriteall64")]]
[[requires_function(PWrite64)]]
[[section(".text.crt{|.dos}.except.io.large.write")]]
size_t PWriteAll64([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf, size_t bufsize, pos64_t offset) {
	size_t result, temp;
	result = PWrite64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = PWrite64(fd,
			                (byte_t const *)buf + result,
			                bufsize - result,
			                offset + result);
			if (!temp)
				break;
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%
%#ifdef __USE_GNU

[[throws, doc_alias("pipe2")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.access")]]
void Pipe2([[out]] $fd_t pipedes[2], $oflag_t flags);

[[throws, doc_alias("dup3")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup3([[fdarg]] $fd_t oldfd, [[no_fdarg]] $fd_t newfd, $oflag_t flags);

@@>> GetCurrentDirName(3)
@@Alias for `GetCwd(NULL, 0)'
[[cp, throws]]
[[decl_include("<bits/types.h>")]]
[[requires_function(GetCwd)]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
GetCurrentDirName() -> [[nonnull, malloc]] char * {
	return GetCwd(NULL, 0);
}

[[cp, throws, doc_alias("syncfs")]]
[[decl_include("<bits/types.h>")]]
[[userimpl]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void SyncFS([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* NO-OP */
}

[[throws, doc_alias("getresuid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void GetRESUid([[out_opt]] $uid_t *ruid,
               [[out_opt]] $uid_t *euid,
               [[out_opt]] $uid_t *suid);

[[throws, doc_alias("getresgid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void GetRESGid([[out_opt]] $gid_t *rgid,
               [[out_opt]] $gid_t *egid,
               [[out_opt]] $gid_t *sgid);

[[throws, doc_alias("setresuid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetRESUid($uid_t ruid, $uid_t euid, $uid_t suid);

[[throws, doc_alias("setresgid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetRESGid($gid_t rgid, $gid_t egid, $gid_t sgid);
%#endif /* __USE_GNU */

%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || defined(__USE_MISC)
//TODO:[[cp, doc_alias("usleep")]]
//TODO:[[decl_include("<bits/types.h>")]]
//TODO:[[requires($has_function(NanoSleep) || $has_function(__crtSleep))]]
//TODO:[[impl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
//TODO:[[section(".text.crt{|.dos}.except.system.utility")]]
//TODO:void USleep($useconds_t useconds) {
//TODO:@@pp_if $has_function(NanoSleep)@@
//TODO:	struct timespec ts;
//TODO:	ts.@tv_sec@  = (time_t)(useconds / USEC_PER_SEC);
//TODO:	ts.@tv_nsec@ = (syscall_ulong_t)(useconds % USEC_PER_SEC) * NSEC_PER_USEC;
//TODO:	NanoSleep(&ts, NULL);
//TODO:@@pp_else@@
//TODO:	__crtSleep(useconds / 1000l); /*USEC_PER_MSEC*/
//TODO:@@pp_endif@@
//TODO:}
//TODO:
//TODO:[[throws, doc_alias("ualarm")]]
//TODO:[[decl_include("<bits/types.h>")]]
//TODO:[[requires_include("<asm/os/itimer.h>")]]
//TODO:[[requires(defined(__ITIMER_REAL) && $has_function(SetITimer))]]
//TODO:[[impl_include("<asm/os/itimer.h>", "<bits/os/itimerval.h>")]]
//TODO:[[section(".text.crt{|.dos}.except.system.utility")]]
//TODO:$useconds_t UAlarm($useconds_t value, $useconds_t interval) {
//TODO:	struct itimerval timer, otimer;
//TODO:	timer.@it_value@.@tv_sec@     = value / 1000000;
//TODO:	timer.@it_value@.@tv_usec@    = value % 1000000;
//TODO:	timer.@it_interval@.@tv_sec@  = interval / 1000000;
//TODO:	timer.@it_interval@.@tv_usec@ = interval % 1000000;
//TODO:	SetITimer((__itimer_which_t)__ITIMER_REAL, &timer, &otimer);
//TODO:	return (otimer.@it_value@.@tv_sec@ * 1000000) +
//TODO:	       (otimer.@it_value@.@tv_usec@);
//TODO:}

[[throws, returns_twice, wunused, doc_alias("vfork")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.access")]]
$pid_t VFork();
%#endif


[[cp, throws, doc_alias("fchown")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void FChOwn([[fdarg]] $fd_t fd, $uid_t owner, $gid_t group);

[[cp, throws, doc_alias("fchdir")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
void FChDir([[fdarg]] $fd_t fd);

[[throws, wunused, doc_alias("getpgid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
$pid_t GetPGid($pid_t pid);

[[throws, wunused, doc_alias("getsid")]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
$pid_t GetSid($pid_t pid);

[[cp, throws, doc_alias("lchown")]]
[[decl_include("<bits/types.h>")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(FChOwnAt))]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void LChOwn([[in]] char const *file, $uid_t owner, $gid_t group) {
	FChOwnAt(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);
}


%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

[[throws, doc_alias("truncate")]]
[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("Truncate")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("Truncate64")]]
[[userimpl, requires($has_function(Truncate32) || $has_function(Truncate64))]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void Truncate([[in]] char const *file, pos_t length) {
@@pp_if $has_function(Truncate32)@@
	Truncate64(file, (__pos64_t)length);
@@pp_else@@
	Truncate32(file, (__pos32_t)length);
@@pp_endif@@
}

[[throws, doc_alias("Truncate")]]
[[decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("Truncate")]]
void Truncate32([[in]] char const *file, $pos32_t length);

%#ifdef __USE_LARGEFILE64
[[throws, doc_alias("truncate64")]]
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(Truncate)]]
[[userimpl, requires_function(Truncate32)]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void Truncate64([[in]] char const *file, pos64_t length) {
	Truncate32(file, (__pos32_t)length);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */


%
%#ifdef __USE_XOPEN2K8

[[cp, throws, noreturn, doc_alias("fexecve")]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_prefix(DEFINE_TARGV)]]
[[argument_names(fd, ___argv, ___envp)]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void FExecve([[fdread]] $fd_t fd, [[in]] __TARGV, [[in]] __TENVP);

%#endif /* __USE_XOPEN2K8 */


%
%#ifdef __USE_GNU

[[cp, throws, noreturn, doc_alias("execvpe")]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[argument_names(file, ___argv, ___envp)]]
[[section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execvpe([[in]] char const *__restrict file, [[in]] __TARGV, [[in]] __TENVP);

%#endif /* __USE_GNU */


%
%#ifdef __USE_POSIX2

[[throws, doc_alias("confstr")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
size_t ConfStr(__STDC_INT_AS_UINT_T name, [[out(? <= buflen)]] char *buf, size_t buflen);

%#endif /* __USE_POSIX2 */


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)

[[throws, userimpl]]
[[section(".text.crt{|.dos}.except.sched.param")]]
int Nice(int inc) {
	COMPILER_IMPURE();
	(void)inc;
	/* It should be sufficient to emulate this is a no-op. */
	return 0;
}

%#endif /* __USE_MISC || __USE_XOPEN */


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

[[throws, doc_alias("setpgrp")]]
[[section(".text.crt{|.dos}.except.sched.process")]]
void SetPGrp();

[[throws, decl_include("<bits/types.h>"), doc_alias("setreuid")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetREUid($uid_t ruid, $uid_t euid);

[[throws, decl_include("<bits/types.h>"), doc_alias("setregid")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetREGid($gid_t rgid, $gid_t egid);

%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */


%
%#ifdef __USE_XOPEN2K

[[throws, decl_include("<bits/types.h>"), doc_alias("seteuid")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetEUid($uid_t euid);

[[throws, decl_include("<bits/types.h>"), doc_alias("setegid")]]
[[section(".text.crt{|.dos}.except.sched.user")]]
void SetEGid($gid_t egid);

%#endif /* __USE_XOPEN2K */


%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

[[cp, throws, doc_alias("symlink")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(SymlinkAt))]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
void Symlink([[in]] char const *link_text,
             [[in]] char const *target_path) {
	SymlinkAt(link_text, __AT_FDCWD, target_path);
}

[[cp, throws, decl_include("<hybrid/typecore.h>"), doc_alias("readlink")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(ReadLinkAt))]]
[[section(".text.crt{|.dos}.except.fs.property")]]
size_t ReadLink([[in]] char const *__restrict path,
                [[out(return <= buflen)]] char *__restrict buf,
                size_t buflen) {
	ReadLinkAt(__AT_FDCWD, path, buf, buflen);
}

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */


%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

[[throws, decl_include("<hybrid/typecore.h>"), doc_alias("gethostname")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
void GetHostName([[out(? <= buflen)]] char *name, size_t buflen);

%#endif /* __USE_UNIX98 || __USE_XOPEN2K */


%
%#ifdef __USE_MISC

[[throws, decl_include("<hybrid/typecore.h>"), doc_alias("sethostname")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
void SetHostName([[in(? <= len)]] char const *name, size_t len);

[[throws, decl_include("<hybrid/typecore.h>"), doc_alias("getdomainname")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
void GetDomainName([[out(? <= buflen)]] char *name, size_t buflen);

[[throws, decl_include("<hybrid/typecore.h>"), doc_alias("setdomainname")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
void SetDomainName([[in(? <= len)]] char const *name, size_t len);

[[cp, throws, section(".text.crt{|.dos}.except.system.utility")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
[[decl_include("<bits/types.h>")]]
__syscall_slong_t Syscall($syscall_ulong_t sysno, ...);

%#ifdef __USE_KOS

[[cp, throws, decl_include("<bits/types.h>"), preferred_alias("Syscall")]]
[[section(".text.crt{|.dos}.except.system.utility")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
__LONG64_TYPE__ Syscall64($syscall_ulong_t sysno, ...);

%#endif /* __USE_KOS */
%#endif /* __USE_MISC */


%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))

[[cp, throws, doc_alias("chroot"), section(".text.crt{|.dos}.except.fs.utility")]]
void ChRoot([[in]] char const *__restrict path);

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */


%
%#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("crt_ftruncate32"), ignore, nocrt, alias("FTruncate")]]
int crt_FTruncate32([[fdwrite]] $fd_t fd, __pos32_t length);

[[throws, decl_include("<bits/types.h>"), doc_alias("ftruncate"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("FTruncate")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("FTruncate64")]]
[[userimpl, requires($has_function(crt_FTruncate32) || $has_function(FTruncate64))]]
[[section(".text.crt{|.dos}.except.io.write")]]
void FTruncate([[fdwrite]] $fd_t fd, pos_t length) {
@@pp_if $has_function(crt_FTruncate32)@@
	crt_FTruncate32(fd, (__pos32_t)length);
@@pp_else@@
	FTruncate64(fd, (__pos64_t)length);
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64

[[throws, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(FTruncate), doc_alias("ftruncate64")]]
[[userimpl, requires_function(crt_FTruncate32)]]
[[section(".text.crt{|.dos}.except.io.large.write")]]
void FTruncate64([[fdwrite]] $fd_t fd, pos64_t length) {
	crt_FTruncate32(fd, (pos32_t)length);
}

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
[[cp, throws, decl_include("<bits/types.h>"), doc_alias("fdatasync"), alias("FSync")]]
[[userimpl, section(".text.crt{|.dos}.except.io.sync")]]
void FDataSync([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-Op */
}
%#endif /* __USE_POSIX199309 || __USE_UNIX98 */


%
%#ifdef __USE_NETBSD
[[cp, throws, doc_alias("lpathconf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<asm/os/oflags.h>")]]
[[requires($has_function(FPathConf) && $has_function(Open) && defined(__O_RDONLY) &&
           defined(__O_PATH) && defined(__O_NOFOLLOW))]]
[[impl_include("<kos/bits/except-compiler.h>")]]
[[userimpl, section(".text.crt{|.dos}.except.fs.property")]]
$longptr_t LPathConf([[in]] char const *path, __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = Open(path, O_RDONLY | O_PATH | O_NOFOLLOW | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_if defined(__RAII_FINALLY) && $has_function(close)@@
	__RAII_FINALLY { (void)close(fd); }
@@pp_endif@@
	result = FPathConf(fd, name);
	return result;
}

[[throws, doc_alias("setruid")]]
[[decl_include("<bits/types.h>")]]
[[requires_function(SetREUid)]]
[[section(".text.crt{|.dos}.except.bsd.user")]]
void SetRUid(uid_t ruid) {
	SetREUid(ruid, (uid_t)-1);
}

[[throws, doc_alias("setrgid")]]
[[decl_include("<bits/types.h>")]]
[[requires_function(SetREGid)]]
[[section(".text.crt{|.dos}.except.bsd.user")]]
void SetRGid(gid_t rgid) {
	SetREGid(rgid, (gid_t)-1);
}
%#endif /* __USE_NETBSD */


[[cp, throws, wunused, doc_alias("sysconf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
$longptr_t SysConf(__STDC_INT_AS_UINT_T name);


%
%#ifdef __USE_BSD

[[throws, doc_alias("close_range")]]
[[section(".text.crt{|.dos}.bsd.io.access")]]
void CloseRange(unsigned int minfd, unsigned int maxfd, unsigned int flags);

%#endif /* __USE_BSD */


%
%#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)

[[throws, doc_alias("fchroot")]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(Dup2) && defined(__AT_FDROOT))]]
[[impl_include("<asm/os/fcntl.h>")]]
[[section(".text.crt{|.dos}.except.bsd")]]
void FChRoot([[fdarg]] $fd_t fd) {
	(void)Dup2(fd, __AT_FDROOT);
}

%#endif /* __USE_SOLARIS || __USE_NETBSD */


%
%#ifdef __USE_SOLARIS

[[throws, wunused, doc_alias("tell")]]
[[decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("Tell")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("Tell64")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(LSeek) && defined(__SEEK_CUR))]]
[[impl_include("<asm/os/stdio.h>")]]
[[section(".text.crt{|.dos}.except.solaris")]]
$pos_t Tell([[fdarg]] $fd_t fd) {
	return LSeek(fd, 0, SEEK_CUR);
}

%#ifdef __USE_LARGEFILE64
[[throws, wunused, doc_alias("tell64")]]
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(Tell)]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(LSeek64) && defined(__SEEK_CUR))]]
[[impl_include("<asm/os/stdio.h>")]]
[[section(".text.crt{|.dos}.except.solaris")]]
$pos64_t Tell64([[fdarg]] $fd_t fd) {
	return LSeek64(fd, 0, __SEEK_CUR);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_SOLARIS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
