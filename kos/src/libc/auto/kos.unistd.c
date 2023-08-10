/* HASH CRC-32:0xef4c85e8 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_UNISTD_C
#define GUARD_LIBC_AUTO_KOS_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.unistd.h"
#include "../user/kos.sys.ioctl.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void
(VLIBCCALL libc_Execl)(char const *__restrict path,
                       char const *args,
                       ...) THROWS(...) {
	__REDIRECT_XEXECL(char, libc_Execv, path, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void
(VLIBCCALL libc_Execle)(char const *__restrict path,
                        char const *args,
                        ...) THROWS(...) {
	__REDIRECT_XEXECLE(char, libc_Execve, path, args)
}
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void
(VLIBCCALL libc_Execpl)(char const *__restrict file,
                        char const *args,
                        ...) THROWS(...) {
	__REDIRECT_XEXECL(char, libc_Execvp, file, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void
(VLIBCCALL libc_Execlpe)(char const *__restrict file,
                         char const *args,
                         ...) THROWS(...) {
	__REDIRECT_XEXECLE(char, libc_Execvpe, file, args)
}
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.except.io.tty") WUNUSED ATTR_FDARG(1) pid_t
(LIBCCALL libc_TCGetPGrp)(fd_t fd) THROWS(...) {
	pid_t result;
	libc_Ioctl(fd, __TIOCGPGRP, &result);
	return result;
}
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.except.io.tty") ATTR_FDARG(1) void
(LIBCCALL libc_TCSetPGrp)(fd_t fd,
                          pid_t pgrp_id) THROWS(...) {
	libc_Ioctl(fd, __TIOCSPGRP, &pgrp_id);
}
#include <libc/errno.h>
#include <kos/except.h>
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.except.io.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) size_t
(LIBCCALL libc_ReadAll)(fd_t fd,
                        void *buf,
                        size_t bufsize) THROWS(...) {
	size_t result, temp;
	result = libc_Read(fd, buf, bufsize);
	if (result != 0 && result < bufsize) {
		/* Keep on reading */
		for (;;) {
#ifdef TRY
			TRY
#endif /* TRY */
			{
				temp = libc_Read(fd,
				           (byte_t *)buf + (size_t)result,
				            bufsize - (size_t)result);
			}
#ifdef TRY
			EXCEPT {
#ifdef libc_geterrno
				int old_error = libc_geterrno();
#endif /* libc_geterrno */
				/* Try to un-read data that had already been loaded. */
				libc_lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
#ifdef libc_geterrno
				(void)libc_seterrno(old_error);
#endif /* libc_geterrno */
				RETHROW();
			}
#endif /* TRY */
			if (!temp) {
#ifdef libc_geterrno
				int old_error = libc_geterrno();
#endif /* libc_geterrno */
				/* Try to un-read data that had already been loaded. */
				libc_lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
#ifdef libc_geterrno
				(void)libc_seterrno(old_error);
#endif /* libc_geterrno */
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
#include <libc/errno.h>
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTERN ATTR_SECTION(".text.crt.except.io.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) size_t
(LIBCCALL libc_WriteAll)(fd_t fd,
                         void const *buf,
                         size_t bufsize) THROWS(...) {
	size_t result, temp;
	result = libc_Write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = libc_Write(fd,
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
#endif /* !__KERNEL__ */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
#include <bits/types.h>
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
INTERN ATTR_SECTION(".text.crt.except.io.write") ATTR_INS(2, 3) ssize_t
(__FORMATPRINTER_CC libc_WritePrinter)(void *fd,
                                       char const *__restrict buf,
                                       size_t bufsize) THROWS(...) {
	return (ssize_t)libc_WriteAll((fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(uintptr_t)fd, buf, bufsize);
}
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#ifndef __KERNEL__
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.except.io.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) size_t
(LIBCCALL libc_PReadAll)(fd_t fd,
                         void *buf,
                         size_t bufsize,
                         pos_t offset) THROWS(...) {
	size_t result, temp;
	result = libc_PRead(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = libc_PRead(fd,
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
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.except.io.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) size_t
(LIBCCALL libc_PWriteAll)(fd_t fd,
                          void const *buf,
                          size_t bufsize,
                          pos_t offset) THROWS(...) {
	size_t result, temp;
	result = libc_PWrite(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = libc_PWrite(fd,
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
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_PReadAll64, libc_PReadAll);
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.except.io.large.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) size_t
(LIBCCALL libc_PReadAll64)(fd_t fd,
                           void *buf,
                           size_t bufsize,
                           pos64_t offset) THROWS(...) {
	size_t result, temp;
	result = libc_PRead64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = libc_PRead64(fd,
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
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_PWriteAll64, libc_PWriteAll);
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.except.io.large.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) size_t
(LIBCCALL libc_PWriteAll64)(fd_t fd,
                            void const *buf,
                            size_t bufsize,
                            pos64_t offset) THROWS(...) {
	size_t result, temp;
	result = libc_PWrite64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = libc_PWrite64(fd,
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
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
/* >> GetCurrentDirName(3)
 * Alias for `GetCwd(NULL, 0)' */
INTERN ATTR_SECTION(".text.crt.except.fs.basic_property") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
(LIBCCALL libc_GetCurrentDirName)(void) THROWS(...) {
	return libc_GetCwd(NULL, 0);
}
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.except.bsd.user") void
(LIBCCALL libc_SetRUid)(uid_t ruid) THROWS(...) {
	libc_SetREUid(ruid, (uid_t)-1);
}
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.except.bsd.user") void
(LIBCCALL libc_SetRGid)(gid_t rgid) THROWS(...) {
	libc_SetREGid(rgid, (gid_t)-1);
}
#include <asm/os/fcntl.h>
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTERN ATTR_SECTION(".text.crt.except.bsd") ATTR_FDARG(1) void
(LIBCCALL libc_FChRoot)(fd_t fd) THROWS(...) {
	(void)libc_Dup2(fd, __AT_FDROOT);
}
#include <asm/os/stdio.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.except.solaris") WUNUSED ATTR_FDARG(1) pos_t
(LIBCCALL libc_Tell)(fd_t fd) THROWS(...) {
	return libc_LSeek(fd, 0, SEEK_CUR);
}
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_Tell64, libc_Tell);
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#include <asm/os/stdio.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.except.solaris") WUNUSED ATTR_FDARG(1) pos64_t
(LIBCCALL libc_Tell64)(fd_t fd) THROWS(...) {
	return libc_LSeek64(fd, 0, __SEEK_CUR);
}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(Execl, libc_Execl);
DEFINE_PUBLIC_ALIAS(Execle, libc_Execle);
DEFINE_PUBLIC_ALIAS(Execpl, libc_Execpl);
DEFINE_PUBLIC_ALIAS(Execlpe, libc_Execlpe);
DEFINE_PUBLIC_ALIAS(TCGetPGrp, libc_TCGetPGrp);
DEFINE_PUBLIC_ALIAS(TCSetPGrp, libc_TCSetPGrp);
DEFINE_PUBLIC_ALIAS(ReadAll, libc_ReadAll);
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
DEFINE_PUBLIC_ALIAS(WritePrinter, libc_WriteAll);
#endif /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__ */
DEFINE_PUBLIC_ALIAS(WriteAll, libc_WriteAll);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
DEFINE_PUBLIC_ALIAS(WritePrinter, libc_WritePrinter);
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(PReadAll, libc_PReadAll);
DEFINE_PUBLIC_ALIAS(PWriteAll, libc_PWriteAll);
DEFINE_PUBLIC_ALIAS(PReadAll64, libc_PReadAll64);
DEFINE_PUBLIC_ALIAS(PWriteAll64, libc_PWriteAll64);
DEFINE_PUBLIC_ALIAS(GetCurrentDirName, libc_GetCurrentDirName);
DEFINE_PUBLIC_ALIAS(SetRUid, libc_SetRUid);
DEFINE_PUBLIC_ALIAS(SetRGid, libc_SetRGid);
DEFINE_PUBLIC_ALIAS(FChRoot, libc_FChRoot);
DEFINE_PUBLIC_ALIAS(Tell, libc_Tell);
DEFINE_PUBLIC_ALIAS(Tell64, libc_Tell64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_UNISTD_C */
