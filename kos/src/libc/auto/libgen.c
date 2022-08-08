/* HASH CRC-32:0x6510a1ca */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_LIBGEN_C
#define GUARD_LIBC_AUTO_LIBGEN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "libgen.h"
#include "../user/ctype.h"
#include "../user/fcntl.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Return the directory, that is everything leading up to, but not
 * including the last slash of `path'. If no such path exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> dirname("/usr/include///"); // Returns "/usr"
 * >> dirname("/usr/include/");   // Returns "/usr"
 * >> dirname("/usr/include");    // Returns "/usr"
 * >> dirname("/usr/");           // Returns "/"
 * >> dirname("/usr");            // Returns "/"
 * >> dirname("/");               // Returns "/"
 * >> dirname("///");             // Returns "/"
 * >> dirname("foo/bar/");        // Returns "foo"
 * >> dirname("foo/bar");         // Returns "foo"
 * >> dirname("foo/");            // Returns "."
 * >> dirname("foo");             // Returns "."
 * >> dirname(".");               // Returns "."
 * >> dirname("..");              // Returns "."
 * >> dirname("");                // Returns "."
 * >> dirname(NULL);              // Returns "."
 * Note  that for this purpose, `path' may be modified in-place, meaning
 * that you should really always pass an strdup()'d, or writable string. */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_RETNONNULL ATTR_IN_OPT(1) char *
NOTHROW_NCX(LIBCCALL libc_dirname)(char *path) {
	char *iter;
	/* Handle the empty-path case. */
	if (!path || !*path)
		goto fallback;
	iter = libc_strend(path);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= path) {
			/* String consists only of '/'-characters */
			return path;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < path)
			goto fallback;
		if (*iter == '/')
			break;
		--iter;
	}
	if (iter == path) {
		/* First character is the slash (e.g. "/foo/")
		 * Return "/" in this case! */
		++iter;
	}
	/* Delete the  slash character  (or  the one  after  the
	 * slash, if the only character left is a leading slash) */
	iter[0] = '\0';
	return path;
fallback:
	return (char *)".";
}
/* Return the filename-part, that is everything following
 * the last slash of `filename'. If no such part exists, "."
 * is returned instead. Trailing slashes are ignored
 * >> basename("/usr/include///"); // Returns "include"
 * >> basename("/usr/include/");   // Returns "include"
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns "usr"
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns "/"
 * >> basename("///");             // Returns "/"
 * >> basename("foo/bar/");        // Returns "bar"
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns "foo"
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns "."
 * >> basename(NULL);              // Returns "."
 * Note that for this purpose, `filename' may be modified in-place, meaning
 * that  you should really  always pass an  strdup()'d, or writable string.
 *
 * Also note that a different version of this function exists in <string.h>,
 * where if you  include both  <libgen.h> and  <string.h>, you  can use  the
 * alternate function from <string.h>  by `#undef basename', or calling  the
 * function as `(basename)(...)' (as opposed to `basename(...)') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_RETNONNULL ATTR_INOUT_OPT(1) char *
NOTHROW_NCX(LIBCCALL libc___xpg_basename)(char *filename) {
	char *iter;
	/* Handle the empty-path case. */
	if (!filename || !*filename)
		goto fallback;
	iter = libc_strend(filename);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= filename) {
			/* String consists only of '/'-characters */
			return filename;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < filename)
			break;
		if (*iter == '/')
			break;
		--iter;
	}
	return iter + 1;
fallback:
	return (char *)".";
}
#include <asm/crt/stdio.h>
/* >> bgets(3)
 * Read at most `buflen_minus_one' characters from `fp' and into `buf'
 * Afterwards, a trailing  NUL-character is appended  to `buf'  (hence
 * the `minus_one' in  `buflen_minus_one'). Stop  reading (and  append
 * the trailing NUL) once `fgetc(fp) == EOF', or `fgetc(fp)' returns a
 * character from `stop_chars'. In this last case, the read  character
 * is NOT ungetc'd, meaning it will be lost.
 * @param: buf:   Output buffer. (Assuming success), this function always
 *                writes at least  `1' (trailing NUL)  character to  this
 *                buffer.
 * @return: NULL: `buflen_minus_one != 0', and the  first character  read
 *                from `fp' was `EOF'. The case where the first character
 *                read is in `stop_chars' doesn't cause a NULL-return.
 * @return: * :   Returns a pointer to the trailing NUL written to `buf'
 *                There is no true error  case; read errors are  treated
 *                the same way as end-of-file. */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_INOUT(3) ATTR_IN_OPT(4) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_bgets)(char *buf,
                                 size_t buflen_minus_one,
                                 FILE *fp,
                                 char __KOS_FIXED_CONST *stop_chars) {
	char *iter = buf;
	if (stop_chars == NULL)
		stop_chars = (char __KOS_FIXED_CONST *)"";
	for (; buflen_minus_one; --buflen_minus_one) {
		int ch = libc_fgetc(fp);
		if (ch == EOF) {
			if (iter == buf)
				return NULL;
			break;
		}
		if (libc_strchr(stop_chars, ch))
			break;
		*iter++ = ch;
	}
	*iter = '\0';
	return iter;
}
#include <hybrid/host.h>
/* >> bufsplit(3)
 * Split `string' on field-separator characters (by default "\t" or  "\n"),
 * replacing  those characters with  '\0'. The produced  list of strings is
 * then stored in up to `result_c' pointers of `result_v', with the  actual
 * number  of produced  strings returned  (any unused  trailing pointers of
 * `result_v' are  filled  with  the  empty  string  at  `strend(string)').
 * In  case `string' contains  more than `result_c'  fields, only the first
 * `result_c' fields are actually split and `result_v[result_c-1]' contains
 * the remaining of `string', including any unsplit trailing fields.
 *
 * The set of characters used as field-separators can also be changed  for
 * this function in a  call `bufsplit(NEW_FIELDS, 0, NULL)'. Note that  in
 * this case, `string' must remain  allocated and usable until fields  are
 * changed yet again. There is no way to reset the default ("\t\n") set of
 * field separator characters.
 *
 * @return: * : The number of  field strings extracted  from `string'  and
 *              stored in `result_v'. All remaining pointers in `result_v'
 *              beyond `return' (and  before `result_c')  are filled  with
 *              the empty string found at `strend(IN:string)'. */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_INOUT_OPT(1) ATTR_OUT_OPT(3) size_t
NOTHROW_NCX(LIBCCALL libc_bufsplit)(char *string,
                                    size_t result_c,
                                    char **result_v) {
	size_t count;
	char const *splitchar;
	static char const default_splitchar[] = "\t\n";
#ifdef __pic__
	static char const *saved_splitchar = NULL;
	if (saved_splitchar == NULL)
		saved_splitchar = default_splitchar;
#else /* __pic__ */
	static char const *saved_splitchar = default_splitchar;
#endif /* !__pic__ */
	if unlikely(!string)
		return 0;
	if (result_c == 0 && result_v == NULL) {
		saved_splitchar = (char const *)string;
		return 1;
	} else {
		if unlikely((result_c != 0 && result_v == NULL) ||
		            (result_c == 0 && result_v != NULL))
			return 0;
	}
	splitchar = saved_splitchar;
	for (count = 0; count < result_c; ) {
		result_v[count++] = string;
		/* Find end of field. */
		string = libc_strpbrk(string, splitchar);
		if (!string)
			break;
		/* Split field. */
		*string++ = '\0';
		if (*string == '\0') {
			/* Special case: end-of-string after field separator
			 * --> no more fields. */
			break;
		}
	}
	/* All remaining fields become the empty string that exists at
	 * the end of the last  (preceding) field. There is always  at
	 * least one field at the start of the string. */
	if (count < result_c) {
		size_t i;
		string = libc_strend(result_v[count - 1]);
		for (i = count; i < result_c; i++)
			result_v[i] = string;
	}
	return count;
}
#include <asm/crt/malloc.h>
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_fcopylist_sz)(fd_t fd,
                                        size_t *p_filesize) {
	size_t reslen  = 0;
	size_t buflen  = 1024;
	byte_t *result = (byte_t *)libc_malloc(buflen);
	if unlikely(!result) {
		buflen = 1;
		result = (byte_t *)libc_malloc(1);
		if unlikely(!result)
			goto err;
	}
	for (;;) {
		/* Ensure that buffer space is available. */
		size_t i, insize;
		size_t freelen = buflen - reslen;
		byte_t *bufptr;
		if unlikely(!freelen) {
			byte_t *new_result;
			size_t newlen = buflen * 2;
			if unlikely(newlen < buflen)
				newlen = buflen + 1;
			new_result = (byte_t *)libc_realloc(result, newlen);
			if unlikely(!new_result) {
				newlen = buflen + 1;
				new_result = (byte_t *)libc_realloc(result, newlen);
				if unlikely(!new_result)
					goto err_r;
			}
			result  = new_result;
			buflen  = newlen;
			freelen = buflen - reslen;
		}
		bufptr = result + reslen;
		insize = (size_t)libc_read(fd, bufptr, freelen);
		if ((ssize_t)insize <= 0) {
			if unlikely((ssize_t)insize < 0)
				goto err_r;
			break; /* End-of-file */
		}
		/* Replace all line-feeds within read text with '\0' */

		for (i = 0; i < insize;) {
			char ch = bufptr[i];
			if (ch == '\r') {
				/* Universal linefeed support */
				bufptr[i] = '\0';
				++i;
				if (i >= insize)
					break;
				if (bufptr[i] == '\n') {
					/* Collapse 2-byte linefeed into a single '\0' */
					--insize;
					libc_memmovedown(&bufptr[i],
					            &bufptr[i + 1],
					            insize - i);
				}
			} else {
				if (ch == '\n')
					bufptr[i] = '\0';
				++i;
			}
		}






		reslen += insize;
	}

	/* Free unused memory */
	{
		byte_t *new_result;
#ifdef __REALLOC_ZERO_IS_NONNULL
		new_result = (byte_t *)libc_realloc(result, reslen);
#else /* __REALLOC_ZERO_IS_NONNULL */
		new_result = (byte_t *)libc_realloc(result, reslen ? reslen : 1);
#endif /* !__REALLOC_ZERO_IS_NONNULL */
		if likely(new_result)
			result = new_result;
	}
	*p_filesize = reslen;
	return (char *)result;
err_r:

	libc_free(result);

err:
	return NULL;
}
#include <asm/os/oflags.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBDCALL libd_copylist_sz)(char const *filename,
                                       size_t *p_filesize) {
	char *result;

	fd_t fd = libd_open(filename, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);



	if unlikely(fd < 0)
		return NULL;
	result = libc_fcopylist_sz(fd, p_filesize);

	libc_close(fd);

	return result;
}
#include <asm/os/oflags.h>
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_copylist_sz)(char const *filename,
                                       size_t *p_filesize) {
	char *result;

	fd_t fd = libc_open(filename, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);



	if unlikely(fd < 0)
		return NULL;
	result = libc_fcopylist_sz(fd, p_filesize);

	libc_close(fd);

	return result;
}
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#include <bits/types.h>
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_RPC(LIBDCALL libd_copylist)(char const *filename,
                                    __PIO_OFFSET *p_filesize) {
#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
	__PIO_OFFSET64 filesize64;
	char *result = libd_copylist64(filename, &filesize64);
	*p_filesize = (__PIO_OFFSET)filesize64;
	return result;
#elif __SIZEOF_OFF_T__ == __SIZEOF_SIZE_T__
	return libd_copylist_sz(filename, (size_t *)p_filesize);
#else /* ... */
	char *result;
	size_t size;
	result = libd_copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET)size;
	return result;
#endif /* !... */
}
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS(libc_copylist, libc_copylist_sz);
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_SIZE_T__ */
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_RPC(LIBCCALL libc_copylist)(char const *filename,
                                    __PIO_OFFSET *p_filesize) {
#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
	__PIO_OFFSET64 filesize64;
	char *result = libc_copylist64(filename, &filesize64);
	*p_filesize = (__PIO_OFFSET)filesize64;
	return result;
#elif __SIZEOF_OFF_T__ == __SIZEOF_SIZE_T__
	return libc_copylist_sz(filename, (size_t *)p_filesize);
#else /* ... */
	char *result;
	size_t size;
	result = libc_copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET)size;
	return result;
#endif /* !... */
}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_SIZE_T__ */
#include <bits/types.h>
#if __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
DEFINE_INTERN_ALIAS(libd_copylist64, libd_copylist);
#else /* __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__ */
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_RPC(LIBDCALL libd_copylist64)(char const *filename,
                                      __PIO_OFFSET64 *p_filesize) {
#if __SIZEOF_OFF64_T__ == __SIZEOF_SIZE_T__
	return libd_copylist_sz(filename, (size_t *)p_filesize);
#else /* __SIZEOF_OFF64_T__ == __SIZEOF_SIZE_T__ */
	char *result;
	size_t size;
	result = libd_copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET64)size;
	return result;
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_SIZE_T__ */
}
#endif /* __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__ */
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_copylist64, libc_copylist);
#elif __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
DEFINE_INTERN_ALIAS(libc_copylist64, libc_copylist);
#elif __SIZEOF_OFF64_T__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS(libc_copylist64, libc_copylist_sz);
#else /* ... */
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
/* >> copylist(3), copylist64(3)
 * Load a given file `filename' into memory (via `malloc(3)'), and return
 * a  pointer to this newly malloc'd data-blob (the caller is responsible
 * to eventually free(3) it). The size of this loaded data blob is stored
 * in the given `p_filesize'. The file  is processed such that all  line-
 * feeds are replaced with '\0' characters.
 * This function is stupid and should not be used for the following reasons:
 *  - Loading  an entire file  into an malloc buffer  is highly inefficient. If
 *    you want to load a file into memory, use mmap(2), which allows the kernel
 *    to only load file  parts as you  actually make use  of them, rather  than
 *    being forced to load all  of them at once. Even  if you want to load  all
 *    of them at  once, mmap(2) is  still more efficient  since the kernel  can
 *    simply map its actual  I/O buffer into you  process, rather than the  way
 *    that `read(2)' would be required to first load the I/O buffer, then  copy
 *    from that I/O buffer into your malloc'd buffer.
 *  - The `p_filesize' argument, and the fact  that this function has a  64-bit
 *    offset variant doesn't make any flipping sense. - Because the entire file
 *    gets  loaded into memory  at once, it's literally  impossible to use this
 *    function with files that are  larger than `SIZE_MAX' bytes, meaning  that
 *    any file size for which this function could possibly succeed _has_ to  be
 *    small enough to fit into a `size_t'. As such, using off_t/pos_t where the
 *    actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
 *    make any sense. For example:
 *     i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
 *      -> copylist()  is non-portable to other architectures because there
 *         is no guaranty on the  relation between size_t and pos_t.  There
 *         might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
 *         have to be ready to use `copylist64()' instead.
 *      -> copylist64() doesn't make any sense because the function literally
 *         cannot succeed for  files larger than  32-bit, as it's  physically
 *         impossible to malloc() a buffer for such a file.
 *     x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
 *      -> copylist() is non-portable for the same reasons as on i386
 *      -> copylist64() is identical to copylist() because pos_t is  always
 *         64-bit, meaning that its existence isn't explicitly warranted on
 *         this architecture. */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_RPC(LIBCCALL libc_copylist64)(char const *filename,
                                      __PIO_OFFSET64 *p_filesize) {



	char *result;
	size_t size;
	result = libc_copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET64)size;
	return result;

}
#endif /* !... */
#include <hybrid/typecore.h>
/* >> strcadd(3)
 * Decode C-style escape sequences from `string' and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
 * bytes long (the +1 because this function appends a trailing '\0')
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strcadd)(char *dstbuf,
                                   char const *string) {
	for (;;) {
		char ch = *string++;
		if (ch == '\0')
			break;
		if (ch == '\\') {
			ch = *string++;
			switch (ch) {

			case '\0': goto done;

			case 'a': ch = 7; break;  /* BEL */
			case 'b': ch = 8; break;  /* BS */
			case 't': ch = 9; break;  /* TAB */
			case 'n': ch = 10; break; /* LF */
			case 'v': ch = 11; break; /* VT */
			case 'f': ch = 12; break; /* FF */
			case 'r': ch = 13; break; /* CR */
//			case '\\': break; /* Unnecessary; already done by default case */

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7': {
				/* Octal character */
				byte_t outb = (byte_t)(ch - '0');
				unsigned int count = 1;
				for (; count < 3; ++string, ++count) {
					ch = *string;
					if (!(ch >= '0' && ch <= '7'))
						break;
					outb <<= 3;
					outb |= (byte_t)(ch - '0');
				}
				ch = (char )outb;
			}	break;

			/* XXX: '\xAB' */
			/* XXX: '\u0014' */
			/* XXX: '\U00000014' */

			default:
				break;
			}
		}
		*dstbuf++ = ch;
	}
done:
	*dstbuf = '\0'; /* NUL-terminate */
	return dstbuf;
}
/* >> strccpy(3)
 * Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strccpy)(char *dstbuf,
                                   char const *string) {
	libc_strcadd(dstbuf, string);
	return dstbuf;
}
/* >> strcadd(3)
 * Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
 * To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
 * long (the +1 because this function appends a trailing '\0')
 * When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
 * @return: * : A pointer to the trailing '\0' appended to `dstbuf' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_streadd)(char *dstbuf,
                                   char const *string,
                                   char const *dont_encode) {
	if (dont_encode == NULL)
		dont_encode = "";
	for (;;) {
		char ch = *string++;
		if (ch == '\0')
			break;
		if ((!libc_isprint(ch) || ch == '\\') && !libc_strchr(dont_encode, ch)) {
			/* Escape this character. */
			*dstbuf++ = '\\';
			switch (ch) {

			case 7: ch = 'a'; break;  /* BEL */
			case 8: ch = 'b'; break;  /* BS */
			case 9: ch = 't'; break;  /* TAB */
			case 10: ch = 'n'; break; /* LF */
			case 11: ch = 'v'; break; /* VT */
			case 12: ch = 'f'; break; /* FF */
			case 13: ch = 'r'; break; /* CR */
			case '\\': break;
			/* NOTE: Yes, apparently " and ' don't get encoded... */

			default:

				dstbuf += libc_sprintf(dstbuf, "%.3o", (unsigned int)(unsigned char)ch);





				continue;
			}
		}
		*dstbuf++ = ch;
	}
/*done:*/
	*dstbuf = '\0'; /* NUL-terminate */
	return dstbuf;
}
/* >> strecpy(3)
 * Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
 * @return: dstbuf: Always re-returns `dstbuf' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL ATTR_IN(2) ATTR_IN_OPT(3) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strecpy)(char *dstbuf,
                                   char const *string,
                                   char const *dont_encode) {
	libc_streadd(dstbuf, string, dont_encode);
	return dstbuf;
}
#include <features.h>
/* >> strfind(3)
 * Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
 * @return: * : `needle' found at `haystack + return'
 * @return: -1: `needle' not found in `haystack' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_strfind)(char const *haystack,
                                   char const *needle) {
	char const *ptr = libc_strstr(haystack, needle);
	return ptr ? (__STDC_INT_AS_SSIZE_T)(ptr - haystack) : -1;
}
/* >> strrspn(3)
 * Scanning from the right, return a pointer to last character in  `haystack'
 * for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
 * characters from `accept', re-returns `haystack'. */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strrspn)(char const *haystack,
                                   char const *accept) {
	char const *iter = libc_strend(haystack);
	while (iter > haystack && libc_strchr(accept, iter[-1]))
		--iter;
	return (char *)iter;
}
#include <bits/types.h>
/* >> strtrns(3)
 * Copy `string' to `result'  (including its trailing NUL),  but
 * replace any characters that appear at `find_map[i]' with  the
 * character from `repl_map[i]'. For this purpose, this function
 * assumes that at least the first `strlen(find_map)' characters
 * of `repl_map' can be accessed,  and that the `result'  buffer
 * has space for at least `strlen(string) + 1' characters.
 * @return: result: Always re-returns `result' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) ATTR_OUT(4) char *
NOTHROW_NCX(LIBCCALL libc_strtrns)(char const *string,
                                   char const *find_map,
                                   char const *repl_map,
                                   char *result) {
	char *dst = result;
	for (;;) {
		char ch = *string++;
		char const *pos;
		if (!ch)
			break;
		pos = libc_strchr(find_map, ch);
		if (pos != NULL)
			ch = repl_map[(size_t)(pos - find_map)];
		*dst++ = ch;
	}
	*dst++ = '\0';
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(dirname, libc_dirname);
DEFINE_PUBLIC_ALIAS(__gnu_basename, libc___xpg_basename);
DEFINE_PUBLIC_ALIAS(__xpg_basename, libc___xpg_basename);
DEFINE_PUBLIC_ALIAS(bgets, libc_bgets);
DEFINE_PUBLIC_ALIAS(bufsplit, libc_bufsplit);
DEFINE_PUBLIC_ALIAS(DOS$copylist, libd_copylist);
DEFINE_PUBLIC_ALIAS(copylist, libc_copylist);
DEFINE_PUBLIC_ALIAS(DOS$copylist64, libd_copylist64);
DEFINE_PUBLIC_ALIAS(copylist64, libc_copylist64);
DEFINE_PUBLIC_ALIAS(strcadd, libc_strcadd);
DEFINE_PUBLIC_ALIAS(strccpy, libc_strccpy);
DEFINE_PUBLIC_ALIAS(streadd, libc_streadd);
DEFINE_PUBLIC_ALIAS(strecpy, libc_strecpy);
DEFINE_PUBLIC_ALIAS(strfind, libc_strfind);
DEFINE_PUBLIC_ALIAS(strrspn, libc_strrspn);
DEFINE_PUBLIC_ALIAS(strtrns, libc_strtrns);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBGEN_C */
