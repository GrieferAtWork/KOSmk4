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
#ifndef GUARD_LIBC_USER_STDIO_EXT_C
#define GUARD_LIBC_USER_STDIO_EXT_C 1

#include "../api.h"
/**/

#include <unicode.h> /* mbstate_init */

#include "stdio-api.h"
#include "stdio_ext.h"

DECL_BEGIN

/*[[[head:libc___fbufsize,hash:CRC-32=0xe08b5118]]]*/
/* >> __fbufsize(3)
 * Returns the used buffer size of the given `stream' (s.a. `setvbuf(3)')
 * @return: * : Used buffer size of `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc___fbufsize)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fbufsize]]]*/
{
	stream = file_fromuser(stream);
	return (size_t)stream->if_bufsiz;
}
/*[[[end:libc___fbufsize]]]*/

/*[[[head:libc___freading,hash:CRC-32=0x713eaae1]]]*/
/* >> __freading(3)
 * Returns  non-zero if the `stream' is read-only, or "the last operation
 * performed on `stream' was a read-operation". On KOS, this last part is
 * implemented such that we check for unsaved changes to `stream'. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc___freading)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___freading]]]*/
{
	stream = file_fromuser(stream);
	return !(stream->if_flag & __IO_FILE_IORW) ||
	       (stream->if_exdata->io_chsz == 0);
}
/*[[[end:libc___freading]]]*/

/*[[[head:libc___fwriting,hash:CRC-32=0xb77b24c3]]]*/
/* >> __fwriting(3)
 * Returns non-zero if the `stream'  is "write-only", or "the last  operation
 * performed on `stream' was a write-operation". On KOS, our stdio impl  does
 * not support write-only files (if reading isn't allowed, this will only  be
 * enforced on an fd-level by the kernel). Instead, we implement `__fwriting'
 * to return indicative of `stream' containing any unwritten changes. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc___fwriting)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fwriting]]]*/
{
	stream = file_fromuser(stream);
	return (stream->if_exdata->io_chsz != 0);
}
/*[[[end:libc___fwriting]]]*/

/*[[[head:libc___freadable,hash:CRC-32=0xd135d593]]]*/
/* >> __freadable(3)
 * Returns non-zero if `stream'  allows for reading (s.a.  `fread(3)')
 * On  KOS, all stdio files can be  read from (except those opened for
 * file descriptors opened as `O_WRONLY', though in this case write(2)
 * is still attempted). As such, KOS  considers all stdio files to  be
 * readable, meaning that on KOS this function always returns `1'. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc___freadable)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___freadable]]]*/
{
	/* KOS's   stdio   itself  always   allows  reads.
	 * It's up to the kernel to stop us from doing so. */
	(void)stream;
	COMPILER_IMPURE();
	return 1;
}
/*[[[end:libc___freadable]]]*/

/*[[[head:libc___fwritable,hash:CRC-32=0x66bd8f09]]]*/
/* >> __fwritable(3)
 * Returns non-zero if `stream' is writable, that is: has been opened
 * with "w",  "r+", or  some similar  flag that  allows for  writing. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc___fwritable)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fwritable]]]*/
{
	stream = file_fromuser(stream);
	return (stream->if_flag & __IO_FILE_IORW) != 0;
}
/*[[[end:libc___fwritable]]]*/

/*[[[head:libc___flbf,hash:CRC-32=0x15dfaa]]]*/
/* >> __flbf(3)
 * Return  non-zero  if `stream'  is line-buffered.  (s.a. `_IOLBF')
 * Note  that on KOS, the line-buffered attribute of stdio files may
 * be determined  lazily, based  on  an underlying  file  descriptor
 * referring to a TTY. If this is the case, this function will  make
 * the appropriate call to `isatty(3)' and set the internal is-line-
 * buffered flag accordingly, before returning its state. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc___flbf)(FILE *stream)
/*[[[body:libc___flbf]]]*/
{
	stream = file_fromuser(stream);
	if (stream->if_flag & IO_LNIFTYY) {
		if (FMUSTLOCK(stream)) {
			file_lock_write(stream);
			file_determine_isatty(stream);
			file_lock_endwrite(stream);
		} else {
			file_determine_isatty(stream);
		}
	}
	return (stream->if_flag & IO_LNBUF) != 0;
}
/*[[[end:libc___flbf]]]*/


PRIVATE ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL stdio_purge_file)(FILE *__restrict stream) {
	struct iofile_data *ex;
	stream = file_fromuser(stream);
	ex     = stream->if_exdata;
	stream->if_ptr += stream->if_cnt;
	stream->if_cnt = 0;
	ex->io_chng    = stream->if_base;
	ex->io_chsz    = 0;
	mbstate_init(&ex->io_mbs);
}


/*[[[head:libc___fpurge,hash:CRC-32=0xddf5a955]]]*/
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") void
NOTHROW_NCX(LIBCCALL libc___fpurge)(FILE *stream)
/*[[[body:libc___fpurge]]]*/
{
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		stdio_purge_file(stream);
		file_lock_endwrite(stream);
	} else {
		stdio_purge_file(stream);
	}
}
/*[[[end:libc___fpurge]]]*/

/*[[[head:libc___fpending,hash:CRC-32=0x9efce4f2]]]*/
/* >> __fpending(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc___fpending)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fpending]]]*/
{
	size_t result;
	struct iofile_data *ex;
	stream = file_fromuser(stream);
	ex     = stream->if_exdata;
	result = ATOMIC_READ(ex->io_chsz);
	return result;
}
/*[[[end:libc___fpending]]]*/

/*[[[head:libc__flushlbf,hash:CRC-32=0x3d029d6f]]]*/
/* >> _flushlbf(3)
 * Perform  a call  `fflush(stream)' for  every open  line-buffered stdio file.
 * Note that usually call this function isn't necessary, since the same already
 * happens automatically when  writing a line-feed  to any line-buffered  stdio
 * file (where line-buffered files are usually those opened on TTYs) */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") void
(LIBCCALL libc__flushlbf)(void) THROWS(...)
/*[[[body:libc__flushlbf]]]*/
{
	file_sync_lnfiles();
}
/*[[[end:libc__flushlbf]]]*/

/*[[[head:libc___fsetlocking,hash:CRC-32=0xddb6863f]]]*/
/* >> __fsetlocking(3)
 * Set the locking type for `stream' to `type'. This affects all stdio functions
 * that aren't already lock-less by nature (iow: everything but `*_unlocked(3)')
 * @param: type: One of `FSETLOCKING_*', as defined in `<stdio_ext.h>'
 * @return: * : The locking type prior to this call (one of `FSETLOCKING_INTERNAL' or `FSETLOCKING_BYCALLER') */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") int
NOTHROW_NCX(LIBCCALL libc___fsetlocking)(FILE *stream,
                                         int type)
/*[[[body:libc___fsetlocking]]]*/
{
	int result;
	(void)type;
	stream = file_fromuser(stream);
	result = FMUSTLOCK(stream)
	         ? FSETLOCKING_INTERNAL
	         : FSETLOCKING_BYCALLER;
#ifdef IO_NOLOCK
	if (type != FSETLOCKING_QUERY) {
		if (type == FSETLOCKING_BYCALLER) {
			ATOMIC_OR(stream->if_flag, IO_NOLOCK);
		} else {
			ATOMIC_AND(stream->if_flag, ~IO_NOLOCK);
		}
	}
#endif /* IO_NOLOCK */
	return result;
}
/*[[[end:libc___fsetlocking]]]*/

/*[[[head:libc___fseterr,hash:CRC-32=0x27095700]]]*/
/* >> __fseterr(3)
 * Set the error indicator of `stream', the same an error file error would, such
 * that `ferror(stream) != 0', and `clearerr(stream)' must be used if one wishes
 * to clear the error once again. */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") void
NOTHROW_NCX(LIBCCALL libc___fseterr)(FILE *stream)
/*[[[body:libc___fseterr]]]*/
{
	stream = file_fromuser(stream);
	FSETERROR(stream);
}
/*[[[end:libc___fseterr]]]*/





/*[[[start:exports,hash:CRC-32=0xe6a2f628]]]*/
DEFINE_PUBLIC_ALIAS(__fbufsize, libc___fbufsize);
DEFINE_PUBLIC_ALIAS(__freading, libc___freading);
DEFINE_PUBLIC_ALIAS(__fwriting, libc___fwriting);
DEFINE_PUBLIC_ALIAS(__freadable, libc___freadable);
DEFINE_PUBLIC_ALIAS(__fwritable, libc___fwritable);
DEFINE_PUBLIC_ALIAS(__flbf, libc___flbf);
DEFINE_PUBLIC_ALIAS(fpurge, libc___fpurge);
DEFINE_PUBLIC_ALIAS(__fpurge, libc___fpurge);
DEFINE_PUBLIC_ALIAS(__fpending, libc___fpending);
DEFINE_PUBLIC_ALIAS(_IO_flush_all_linebuffered, libc__flushlbf);
DEFINE_PUBLIC_ALIAS(_flushlbf, libc__flushlbf);
DEFINE_PUBLIC_ALIAS(__fsetlocking, libc___fsetlocking);
DEFINE_PUBLIC_ALIAS(__fseterr, libc___fseterr);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_EXT_C */
