/* HASH CRC-32:0x7de49606 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.unistd.h"
#include "../user/malloc.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.utsname.h"
#include "uchar.h"
#include "../user/unicode.h"
#include "../user/unistd.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/errno.h>
#include "../libc/tls-globals.h"
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.io.tty") WUNUSED ATTR_FDARG(1) char16_t *
NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd) {

	/* Buffer is typed as `void *' so it can be re-used for `wttyname(3)' */
	void **const _p_ttyname_buf = &libc_get_tlsglobals()->ltg_ttyname_buf;
#define ttyname_buf (*_p_ttyname_buf)
	errno_t error;

	size_t bufsize = libc_malloc_usable_size(ttyname_buf) / sizeof(char16_t);



	if (bufsize < 32) {
		void *newbuf;
		bufsize = 32;
		newbuf  = libc_realloc(ttyname_buf, bufsize * sizeof(char16_t));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
	}

again:

	error = libd_wttyname_r(fd, (char16_t *)ttyname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = libd_wcslen((char16_t *)ttyname_buf) + 1;
		if (retlen < 32)
			retlen = 32; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = libc_realloc(ttyname_buf, retlen * sizeof(char16_t));
			if likely(retbuf)
				ttyname_buf = retbuf;
		}
		return (char16_t *)ttyname_buf;
	}

	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = libc_realloc(ttyname_buf, bufsize * sizeof(char16_t));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
		goto again;
	}


	libc_free(ttyname_buf);
	ttyname_buf = NULL;

err:
	return NULL;






}
#undef ttyname_buf
#include <asm/os/errno.h>
#include "../libc/tls-globals.h"
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.wchar.io.tty") WUNUSED ATTR_FDARG(1) char32_t *
NOTHROW_RPC(LIBKCALL libc_wttyname)(fd_t fd) {

	/* Buffer is typed as `void *' so it can be re-used for `wttyname(3)' */
	void **const _p_ttyname_buf = &libc_get_tlsglobals()->ltg_ttyname_buf;
#define ttyname_buf (*_p_ttyname_buf)
	errno_t error;

	size_t bufsize = libc_malloc_usable_size(ttyname_buf) / sizeof(char32_t);



	if (bufsize < 32) {
		void *newbuf;
		bufsize = 32;
		newbuf  = libc_realloc(ttyname_buf, bufsize * sizeof(char32_t));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
	}

again:

	error = libc_wttyname_r(fd, (char32_t *)ttyname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = libc_wcslen((char32_t *)ttyname_buf) + 1;
		if (retlen < 32)
			retlen = 32; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = libc_realloc(ttyname_buf, retlen * sizeof(char32_t));
			if likely(retbuf)
				ttyname_buf = retbuf;
		}
		return (char32_t *)ttyname_buf;
	}

	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = libc_realloc(ttyname_buf, bufsize * sizeof(char32_t));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
		goto again;
	}


	libc_free(ttyname_buf);
	ttyname_buf = NULL;

err:
	return NULL;






}
#undef ttyname_buf
#include <libc/errno.h>
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.io.tty") ATTR_FDARG(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd,
                                      char16_t *buf,
                                      size_t buflen) {
	errno_t result;



	size_t utf8_buflen = buflen * 3; /* s.a. `UNICODE_16TO8_MAXBUF()' */

	char *utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
	if unlikely(!utf8_buf) {

		return 12;



	}
	result = libc_ttyname_r(fd, utf8_buf, utf8_buflen);
	if (result == 0) {
		size_t reqlen;
		utf8_buflen = libc_strlen(utf8_buf) + 1; /* +1 for trailing NUL */



		reqlen = libc_unicode_len8to16(utf8_buf, utf8_buflen);

		if (reqlen > buflen) {

			result = 34;



		} else {



			buf = (char16_t *)libc_unicode_8to16_n((char16_t *)buf, buflen, utf8_buf, reqlen);

			*buf = '\0'; /* NUL-terminate */
		}
	}

	libc_free(utf8_buf);

	return result;
}
#include <libc/errno.h>
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.wchar.io.tty") ATTR_FDARG(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd,
                                      char32_t *buf,
                                      size_t buflen) {
	errno_t result;

	size_t utf8_buflen = buflen * 7; /* s.a. `UNICODE_32TO8_MAXBUF()' */



	char *utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
	if unlikely(!utf8_buf) {

		return ENOMEM;



	}
	result = libc_ttyname_r(fd, utf8_buf, utf8_buflen);
	if (result == 0) {
		size_t reqlen;
		utf8_buflen = libc_strlen(utf8_buf) + 1; /* +1 for trailing NUL */

		reqlen = libc_unicode_len8to32(utf8_buf, utf8_buflen);



		if (reqlen > buflen) {

			result = ERANGE;



		} else {

			buf = (char32_t *)libc_unicode_8to32_n((char32_t *)buf, buflen, utf8_buf, reqlen);



			*buf = '\0'; /* NUL-terminate */
		}
	}

	libc_free(utf8_buf);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file,
                                  uid_t owner,
                                  gid_t group) {

	return libd_wfchownat(__AT_FDCWD, file, owner, group, 0);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wchown)(char32_t const *file,
                                  uid_t owner,
                                  gid_t group) {

	return libc_wfchownat(__AT_FDCWD, file, owner, group, 0);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path,
                                     __STDC_INT_AS_UINT_T name) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libd_pathconf(utf8_path, name);

	libc_free(utf8_path);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBKCALL libc_wpathconf)(char32_t const *path,
                                     __STDC_INT_AS_UINT_T name) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libc_pathconf(utf8_path, name);

	libc_free(utf8_path);

	return result;
}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from,
                                 char16_t const *to) {

	return libd_wlinkat(__AT_FDCWD, from, __AT_FDCWD, to, 0);




















}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wlink)(char32_t const *from,
                                 char32_t const *to) {

	return libc_wlinkat(__AT_FDCWD, from, __AT_FDCWD, to, 0);




















}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file,
                                   __STDC_INT_AS_UINT_T type) {

	return libd_wfaccessat(__AT_FDCWD, file, type, 0);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_waccess)(char32_t const *file,
                                   __STDC_INT_AS_UINT_T type) {

	return libc_wfaccessat(__AT_FDCWD, file, type, 0);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.basic_property") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libd_chdir(utf8_path);

	libc_free(utf8_path);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.basic_property") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wchdir)(char32_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libc_chdir(utf8_path);

	libc_free(utf8_path);

	return result;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.basic_property") ATTR_OUTS(1, 2) char16_t *
NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf,
                                   size_t bufsize) {
	char *utf8_result;
	char16_t *result;
	size_t result_len;
	utf8_result = libd_getcwd(NULL, 0);
	if unlikely(!utf8_result)
		return NULL;
	result = libd_convert_mbstowcs(utf8_result);
	libc_free(utf8_result);
	if unlikely(!result)
		return NULL;
	result_len = libd_wcslen(result) + 1;
	if (!buf) {
		char16_t *new_result;
		if (!bufsize)
			return result;
		if (bufsize < result_len) {

			(void)libc_seterrno(ERANGE);



			buf = NULL;
			goto done;
		}

		new_result = (char16_t *)libc_realloc(result, bufsize * 2);
		if unlikely(!new_result) {
			buf = NULL;
			goto done;
		}



		return new_result;
	}
	if (bufsize < result_len) {

		(void)libc_seterrno(ERANGE);



		buf = NULL;
		goto done;
	}
	buf = (char16_t *)libc_memcpyw(buf, result, result_len);
done:

	libc_free(result);

	return buf;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.basic_property") ATTR_OUTS(1, 2) char32_t *
NOTHROW_RPC(LIBKCALL libc_wgetcwd)(char32_t *buf,
                                   size_t bufsize) {
	char *utf8_result;
	char32_t *result;
	size_t result_len;
	utf8_result = libc_getcwd(NULL, 0);
	if unlikely(!utf8_result)
		return NULL;
	result = libc_convert_mbstowcs(utf8_result);
	libc_free(utf8_result);
	if unlikely(!result)
		return NULL;
	result_len = libc_wcslen(result) + 1;
	if (!buf) {
		char32_t *new_result;
		if (!bufsize)
			return result;
		if (bufsize < result_len) {

			(void)libc_seterrno(ERANGE);



			buf = NULL;
			goto done;
		}

		new_result = (char32_t *)libc_realloc(result, bufsize * 4);
		if unlikely(!new_result) {
			buf = NULL;
			goto done;
		}



		return new_result;
	}
	if (bufsize < result_len) {

		(void)libc_seterrno(ERANGE);



		buf = NULL;
		goto done;
	}
	buf = (char32_t *)libc_memcpyl(buf, result, result_len);
done:

	libc_free(result);

	return buf;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file) {

	return libd_wunlinkat(__AT_FDCWD, file, 0);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wunlink)(char32_t const *file) {

	return libc_wunlinkat(__AT_FDCWD, file, 0);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path) {

	return libd_wunlinkat(__AT_FDCWD, path, __AT_REMOVEDIR);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wrmdir)(char32_t const *path) {

	return libc_wunlinkat(__AT_FDCWD, path, __AT_REMOVEDIR);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file,
                                       __STDC_INT_AS_UINT_T type) {

	return libd_wfaccessat(__AT_FDCWD, file, type, __AT_EACCESS);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_weuidaccess)(char32_t const *file,
                                       __STDC_INT_AS_UINT_T type) {

	return libc_wfaccessat(__AT_FDCWD, file, type, __AT_EACCESS);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.basic_property") ATTR_MALLOC WUNUSED char16_t *
NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void) {
	char *utf8_path;
	char16_t *result;
	utf8_path = libd_get_current_dir_name();
	if unlikely(!utf8_path)
		return NULL;
	result = libd_convert_mbstowcs(utf8_path);

	libc_free(utf8_path);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.basic_property") ATTR_MALLOC WUNUSED char32_t *
NOTHROW_RPC(LIBKCALL libc_wget_current_dir_name)(void) {
	char *utf8_path;
	char32_t *result;
	utf8_path = libc_get_current_dir_name();
	if unlikely(!utf8_path)
		return NULL;
	result = libc_convert_mbstowcs(utf8_path);

	libc_free(utf8_path);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd,
                                      char16_t const *file,
                                      __STDC_INT_AS_UINT_T type,
                                      atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_faccessat(dfd, utf8_file, type, flags);

	libc_free(utf8_file);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wfaccessat)(fd_t dfd,
                                      char32_t const *file,
                                      __STDC_INT_AS_UINT_T type,
                                      atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_faccessat(dfd, utf8_file, type, flags);

	libc_free(utf8_file);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd,
                                     char16_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_fchownat(dfd, utf8_file, owner, group, flags);

	libc_free(utf8_file);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wfchownat)(fd_t dfd,
                                     char32_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_fchownat(dfd, utf8_file, owner, group, flags);

	libc_free(utf8_file);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd,
                                   char16_t const *from,
                                   fd_t tofd,
                                   char16_t const *to,
                                   atflag_t flags) {
	int result = -1;
	char *utf8_from, *utf8_to;
	utf8_from = libd_convert_wcstombs(from);
	if unlikely(!utf8_from)
		goto done;
	utf8_to = libd_convert_wcstombs(to);
	if unlikely(!utf8_to)
		goto done_from;
	result = libd_linkat(fromfd, utf8_from, tofd, utf8_to, flags);

	libc_free(utf8_to);

done_from:

	libc_free(utf8_from);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBKCALL libc_wlinkat)(fd_t fromfd,
                                   char32_t const *from,
                                   fd_t tofd,
                                   char32_t const *to,
                                   atflag_t flags) {
	int result = -1;
	char *utf8_from, *utf8_to;
	utf8_from = libc_convert_wcstombs(from);
	if unlikely(!utf8_from)
		goto done;
	utf8_to = libc_convert_wcstombs(to);
	if unlikely(!utf8_to)
		goto done_from;
	result = libc_linkat(fromfd, utf8_from, tofd, utf8_to, flags);

	libc_free(utf8_to);

done_from:

	libc_free(utf8_from);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *link_text,
                                      fd_t tofd,
                                      char16_t const *target_path) {

	return libd_wfsymlinkat(link_text, tofd, target_path, 0);




















}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBKCALL libc_wsymlinkat)(char32_t const *link_text,
                                      fd_t tofd,
                                      char32_t const *target_path) {

	return libc_wfsymlinkat(link_text, tofd, target_path, 0);




















}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd,
                                       char16_t const *path,
                                       char16_t *buf,
                                       size_t buflen) {

	return libd_wfreadlinkat(dfd, path, buf, buflen, 0);





































}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlinkat)(fd_t dfd,
                                       char32_t const *path,
                                       char32_t *buf,
                                       size_t buflen) {

	return libc_wfreadlinkat(dfd, path, buf, buflen, 0);





































}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBDCALL libd_wfsymlinkat)(char16_t const *link_text,
                                       fd_t tofd,
                                       char16_t const *target_path,
                                       atflag_t flags) {
	int result = -1;
	char *utf8_link_text, *utf8_target_path;
	utf8_link_text = libd_convert_wcstombs(link_text);
	if unlikely(!utf8_link_text)
		goto done;
	utf8_target_path = libd_convert_wcstombs(target_path);
	if unlikely(!utf8_target_path)
		goto done_from;
	result = libd_fsymlinkat(utf8_link_text, tofd, utf8_target_path, flags);

	libc_free(utf8_target_path);

done_from:

	libc_free(utf8_link_text);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBKCALL libc_wfsymlinkat)(char32_t const *link_text,
                                       fd_t tofd,
                                       char32_t const *target_path,
                                       atflag_t flags) {
	int result = -1;
	char *utf8_link_text, *utf8_target_path;
	utf8_link_text = libc_convert_wcstombs(link_text);
	if unlikely(!utf8_link_text)
		goto done;
	utf8_target_path = libc_convert_wcstombs(target_path);
	if unlikely(!utf8_target_path)
		goto done_from;
	result = libc_fsymlinkat(utf8_link_text, tofd, utf8_target_path, flags);

	libc_free(utf8_target_path);

done_from:

	libc_free(utf8_link_text);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd,
                                        char16_t const *path,
                                        char16_t *buf,
                                        size_t buflen,
                                        atflag_t flags) {
	char *utf8_path;
	ssize_t result;



	size_t utf8_buflen = buflen * 3; /* s.a. `UNICODE_16TO8_MAXBUF()' */

	char *utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
	if unlikely(!utf8_buf)
		goto err;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto err_utf8_buf;

again_freadlinkat:

	result = libd_freadlinkat(dfd, utf8_path, utf8_buf, utf8_buflen, flags);



	if likely(result >= 0) {
		char16_t *dst;

		if ((size_t)result > utf8_buflen) {
			/* Caller used the REQSIZE flag, and the buffer was too small.
			 * -> Allocate a larger utf-8 buffer so we can get the entire
			 *    utf-8 string from the kernel! */
			utf8_buflen = (size_t)result;

			libc_free(utf8_buf);

			utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
			if unlikely(!utf8_buf) {

				libc_free(utf8_path);

				goto err;
			}
			goto again_freadlinkat;
		}

		libc_free(utf8_path);





		dst = (char16_t *)libc_unicode_8to16_n((char16_t *)buf, buflen, utf8_buf, (size_t)result);


		if (flags & __AT_READLINK_REQSIZE) {



			result = libc_unicode_len8to16(utf8_buf, (size_t)result);

		} else

		{
			result = (size_t)(dst - buf);
		}
	} else {

		libc_free(utf8_path);

	}

	libc_free(utf8_buf);

	return result;
err_utf8_buf:

	libc_free(utf8_buf);

err:
	return -1;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBKCALL libc_wfreadlinkat)(fd_t dfd,
                                        char32_t const *path,
                                        char32_t *buf,
                                        size_t buflen,
                                        atflag_t flags) {
	char *utf8_path;
	ssize_t result;

	size_t utf8_buflen = buflen * 7; /* s.a. `UNICODE_32TO8_MAXBUF()' */



	char *utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
	if unlikely(!utf8_buf)
		goto err;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto err_utf8_buf;

again_freadlinkat:

	result = libc_freadlinkat(dfd, utf8_path, utf8_buf, utf8_buflen, flags);



	if likely(result >= 0) {
		char32_t *dst;

		if ((size_t)result > utf8_buflen) {
			/* Caller used the REQSIZE flag, and the buffer was too small.
			 * -> Allocate a larger utf-8 buffer so we can get the entire
			 *    utf-8 string from the kernel! */
			utf8_buflen = (size_t)result;

			libc_free(utf8_buf);

			utf8_buf = (char *)libc_malloc(utf8_buflen * sizeof(char));
			if unlikely(!utf8_buf) {

				libc_free(utf8_path);

				goto err;
			}
			goto again_freadlinkat;
		}

		libc_free(utf8_path);



		dst = (char32_t *)libc_unicode_8to32_n((char32_t *)buf, buflen, utf8_buf, (size_t)result);




		if (flags & __AT_READLINK_REQSIZE) {

			result = libc_unicode_len8to32(utf8_buf, (size_t)result);



		} else

		{
			result = (size_t)(dst - buf);
		}
	} else {

		libc_free(utf8_path);

	}

	libc_free(utf8_buf);

	return result;
err_utf8_buf:

	libc_free(utf8_buf);

err:
	return -1;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd,
                                     char16_t const *file,
                                     atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_unlinkat(dfd, utf8_file, flags);

	libc_free(utf8_file);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wunlinkat)(fd_t dfd,
                                     char32_t const *file,
                                     atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_unlinkat(dfd, utf8_file, flags);

	libc_free(utf8_file);

	return result;
}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file,
                                   uid_t owner,
                                   gid_t group) {

	return libd_wfchownat(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wlchown)(char32_t const *file,
                                   uid_t owner,
                                   gid_t group) {

	return libc_wfchownat(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file,
                                     __PIO_OFFSET length) {


#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
	return libd_wtruncate64(file, (__PIO_OFFSET64)length);
#else /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_truncate(utf8_file, length);

	libc_free(utf8_file);

	return result;
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBKCALL libc_wtruncate)(char32_t const *file,
                                     __PIO_OFFSET length) {


#if defined(__LIBCCALL_IS_LIBKCALL) && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
	return libc_wtruncate64(file, (__PIO_OFFSET64)length);
#else /* __LIBCCALL_IS_LIBKCALL && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_truncate(utf8_file, length);

	libc_free(utf8_file);

	return result;
#endif /* !__LIBCCALL_IS_LIBKCALL || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
}
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS_P(libd_wtruncate64,libd_wtruncate,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char16_t const *file, __PIO_OFFSET64 length),(file,length));
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file,
                                       __PIO_OFFSET64 length) {

	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_truncate64(utf8_file, length);

	libc_free(utf8_file);

	return result;



}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS_P(libc_wtruncate64,libc_wtruncate,ATTR_IN(1),int,NOTHROW_NCX,LIBKCALL,(char32_t const *file, __PIO_OFFSET64 length),(file,length));
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBKCALL libc_wtruncate64)(char32_t const *file,
                                       __PIO_OFFSET64 length) {

	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_truncate64(utf8_file, length);

	libc_free(utf8_file);

	return result;



}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *link_text,
                                    char16_t const *target_path) {

	return libd_wfsymlinkat(link_text, __AT_FDCWD, target_path, 0);






















}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wsymlink)(char32_t const *link_text,
                                    char32_t const *target_path) {

	return libc_wfsymlinkat(link_text, __AT_FDCWD, target_path, 0);






















}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *path,
                                     char16_t *buf,
                                     size_t buflen) {

	return libd_wreadlinkat(__AT_FDCWD, path, buf, buflen);






































}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlink)(char32_t const *path,
                                     char32_t *buf,
                                     size_t buflen) {

	return libc_wreadlinkat(__AT_FDCWD, path, buf, buflen);






































}
#include <bits/crt/uformat-printer.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.system.configuration") ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name,
                                        size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		char16_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = libc_uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = libc_strnlen(uts.nodename, COMPILER_LENOF(uts.nodename));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &libd_format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = libd_format_8tow(&convert_data, uts.nodename, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {

			return libc_seterrno(ERANGE);



		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
#include <bits/crt/uformat-printer.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.system.configuration") ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBKCALL libc_wgethostname)(char32_t *name,
                                        size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		char32_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = libc_uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = libc_strnlen(uts.nodename, COMPILER_LENOF(uts.nodename));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &libc_format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = libc_format_8tow(&convert_data, uts.nodename, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {

			return libc_seterrno(ERANGE);



		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.io.tty") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name) {
	int result;
	char *utf8_name;
	utf8_name = libd_convert_wcstombs(name);
	if unlikely(!utf8_name)
		return -1;
	result = libc_setlogin(utf8_name);

	libc_free(utf8_name);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.io.tty") ATTR_IN(1) int
NOTHROW_NCX(LIBKCALL libc_wsetlogin)(char32_t const *name) {
	int result;
	char *utf8_name;
	utf8_name = libc_convert_wcstombs(name);
	if unlikely(!utf8_name)
		return -1;
	result = libc_setlogin(utf8_name);

	libc_free(utf8_name);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name,
                                        size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = libd_convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = libc_sethostname(utf8_name, utf8_len);

	libc_free(utf8_name);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBKCALL libc_wsethostname)(char32_t const *name,
                                        size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = libc_convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = libc_sethostname(utf8_name, utf8_len);

	libc_free(utf8_name);

	return result;
}
#include <bits/crt/uformat-printer.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.system.configuration") ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name,
                                          size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		char16_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = libc_uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = libc_strnlen(uts.__PRIVATE_UTSNAME_DOMAINNAME, COMPILER_LENOF(uts.__PRIVATE_UTSNAME_DOMAINNAME));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &libd_format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = libd_format_8tow(&convert_data, uts.__PRIVATE_UTSNAME_DOMAINNAME, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {

			return libc_seterrno(ERANGE);



		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
#include <bits/crt/uformat-printer.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.system.configuration") ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBKCALL libc_wgetdomainname)(char32_t *name,
                                          size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		char32_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = libc_uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = libc_strnlen(uts.__PRIVATE_UTSNAME_DOMAINNAME, COMPILER_LENOF(uts.__PRIVATE_UTSNAME_DOMAINNAME));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &libc_format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = libc_format_8tow(&convert_data, uts.__PRIVATE_UTSNAME_DOMAINNAME, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {

			return libc_seterrno(ERANGE);



		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name,
                                          size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = libd_convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = libc_setdomainname(utf8_name, utf8_len);

	libc_free(utf8_name);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBKCALL libc_wsetdomainname)(char32_t const *name,
                                          size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = libc_convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = libc_setdomainname(utf8_name, utf8_len);

	libc_free(utf8_name);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libd_chroot(utf8_path);

	libc_free(utf8_path);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.utility") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wchroot)(char32_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = libc_chroot(utf8_path);

	libc_free(utf8_path);

	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$wttyname,libd_wttyname,WUNUSED ATTR_FDARG(1),char16_t *,NOTHROW_RPC,LIBDCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(wttyname,libc_wttyname,WUNUSED ATTR_FDARG(1),char32_t *,NOTHROW_RPC,LIBKCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(DOS$wttyname_r,libd_wttyname_r,ATTR_FDARG(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_RPC,LIBDCALL,(fd_t fd, char16_t *buf, size_t buflen),(fd,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(wttyname_r,libc_wttyname_r,ATTR_FDARG(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_RPC,LIBKCALL,(fd_t fd, char32_t *buf, size_t buflen),(fd,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wchown,libd_wchown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(wchown,libc_wchown,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$wpathconf,libd_wpathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBDCALL,(char16_t const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(wpathconf,libc_wpathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBKCALL,(char32_t const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(DOS$wlink,libd_wlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *from, char16_t const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(wlink,libc_wlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(char32_t const *from, char32_t const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(DOS$_waccess,libd_waccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$waccess,libd_waccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(waccess,libc_waccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$_wchdir,libd_wchdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$wchdir,libd_wchdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(wchdir,libc_wchdir,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$_wgetcwd,libd_wgetcwd,ATTR_OUTS(1, 2),char16_t *,NOTHROW_RPC,LIBDCALL,(char16_t *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$wgetcwd,libd_wgetcwd,ATTR_OUTS(1, 2),char16_t *,NOTHROW_RPC,LIBDCALL,(char16_t *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(wgetcwd,libc_wgetcwd,ATTR_OUTS(1, 2),char32_t *,NOTHROW_RPC,LIBKCALL,(char32_t *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$_wunlink,libd_wunlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$wunlink,libd_wunlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file),(file));
DEFINE_PUBLIC_ALIAS_P(wunlink,libc_wunlink,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$_wrmdir,libd_wrmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$wrmdir,libd_wrmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(wrmdir,libc_wrmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$weuidaccess,libd_weuidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(weuidaccess,libc_weuidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$wget_current_dir_name,libd_wget_current_dir_name,ATTR_MALLOC WUNUSED,char16_t *,NOTHROW_RPC,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(wget_current_dir_name,libc_wget_current_dir_name,ATTR_MALLOC WUNUSED,char32_t *,NOTHROW_RPC,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$wfaccessat,libd_wfaccessat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char16_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags),(dfd,file,type,flags));
DEFINE_PUBLIC_ALIAS_P(wfaccessat,libc_wfaccessat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dfd, char32_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags),(dfd,file,type,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wfchownat,libd_wfchownat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char16_t const *file, uid_t owner, gid_t group, atflag_t flags),(dfd,file,owner,group,flags));
DEFINE_PUBLIC_ALIAS_P(wfchownat,libc_wfchownat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dfd, char32_t const *file, uid_t owner, gid_t group, atflag_t flags),(dfd,file,owner,group,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wlinkat,libd_wlinkat,ATTR_IN(2) ATTR_IN(4),int,NOTHROW_RPC,LIBDCALL,(fd_t fromfd, char16_t const *from, fd_t tofd, char16_t const *to, atflag_t flags),(fromfd,from,tofd,to,flags));
DEFINE_PUBLIC_ALIAS_P(wlinkat,libc_wlinkat,ATTR_IN(2) ATTR_IN(4),int,NOTHROW_RPC,LIBKCALL,(fd_t fromfd, char32_t const *from, fd_t tofd, char32_t const *to, atflag_t flags),(fromfd,from,tofd,to,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wsymlinkat,libd_wsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *link_text, fd_t tofd, char16_t const *target_path),(link_text,tofd,target_path));
DEFINE_PUBLIC_ALIAS_P(wsymlinkat,libc_wsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBKCALL,(char32_t const *link_text, fd_t tofd, char32_t const *target_path),(link_text,tofd,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$wreadlinkat,libd_wreadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen),(dfd,path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(wreadlinkat,libc_wreadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBKCALL,(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen),(dfd,path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wfsymlinkat,libd_wfsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *link_text, fd_t tofd, char16_t const *target_path, atflag_t flags),(link_text,tofd,target_path,flags));
DEFINE_PUBLIC_ALIAS_P(wfsymlinkat,libc_wfsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBKCALL,(char32_t const *link_text, fd_t tofd, char32_t const *target_path, atflag_t flags),(link_text,tofd,target_path,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wfreadlinkat,libd_wfreadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen, atflag_t flags),(dfd,path,buf,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(wfreadlinkat,libc_wfreadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBKCALL,(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen, atflag_t flags),(dfd,path,buf,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wunlinkat,libd_wunlinkat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char16_t const *file, atflag_t flags),(dfd,file,flags));
DEFINE_PUBLIC_ALIAS_P(wunlinkat,libc_wunlinkat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dfd, char32_t const *file, atflag_t flags),(dfd,file,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wlchown,libd_wlchown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(wlchown,libc_wlchown,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$wtruncate,libd_wtruncate,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char16_t const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(wtruncate,libc_wtruncate,ATTR_IN(1),int,NOTHROW_NCX,LIBKCALL,(char32_t const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(DOS$wtruncate64,libd_wtruncate64,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char16_t const *file, __PIO_OFFSET64 length),(file,length));
DEFINE_PUBLIC_ALIAS_P(wtruncate64,libc_wtruncate64,ATTR_IN(1),int,NOTHROW_NCX,LIBKCALL,(char32_t const *file, __PIO_OFFSET64 length),(file,length));
DEFINE_PUBLIC_ALIAS_P(DOS$wsymlink,libd_wsymlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *link_text, char16_t const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(wsymlink,libc_wsymlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(char32_t const *link_text, char32_t const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$wreadlink,libd_wreadlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBDCALL,(char16_t const *path, char16_t *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(wreadlink,libc_wreadlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBKCALL,(char32_t const *path, char32_t *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wgethostname,libd_wgethostname,ATTR_OUTS(1, 2),int,NOTHROW_NCX,LIBDCALL,(char16_t *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P(wgethostname,libc_wgethostname,ATTR_OUTS(1, 2),int,NOTHROW_NCX,LIBKCALL,(char32_t *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wsetlogin,libd_wsetlogin,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char16_t const *name),(name));
DEFINE_PUBLIC_ALIAS_P(wsetlogin,libc_wsetlogin,ATTR_IN(1),int,NOTHROW_NCX,LIBKCALL,(char32_t const *name),(name));
DEFINE_PUBLIC_ALIAS_P(DOS$wsethostname,libd_wsethostname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(wsethostname,libc_wsethostname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(DOS$wgetdomainname,libd_wgetdomainname,ATTR_OUTS(1, 2),int,NOTHROW_NCX,LIBDCALL,(char16_t *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P(wgetdomainname,libc_wgetdomainname,ATTR_OUTS(1, 2),int,NOTHROW_NCX,LIBKCALL,(char32_t *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wsetdomainname,libd_wsetdomainname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(wsetdomainname,libc_wsetdomainname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(DOS$wchroot,libd_wchroot,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *path),(path));
DEFINE_PUBLIC_ALIAS_P(wchroot,libc_wchroot,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *path),(path));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_C */
