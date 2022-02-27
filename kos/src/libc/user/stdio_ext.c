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

/*[[[head:libc___fbufsize,hash:CRC-32=0xbbcaae72]]]*/
/* >> __fbufsize(3)
 * Return the size of the buffer of `stream' in
 * bytes  currently in use  by the given stream */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc___fbufsize)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fbufsize]]]*/
{
	stream = file_fromuser(stream);
	return (size_t)stream->if_bufsiz;
}
/*[[[end:libc___fbufsize]]]*/

/*[[[head:libc___freading,hash:CRC-32=0xb337dbfa]]]*/
/* >> __freading(3)
 * Return  non-zero value when  `stream' is opened readonly,
 * or if the last operation on `stream' was a read operation */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___freading)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___freading]]]*/
{
	stream = file_fromuser(stream);
	return (stream->if_flag & __IO_FILE_IORW) ||
	       (stream->if_exdata->io_chsz == 0);
}
/*[[[end:libc___freading]]]*/

/*[[[head:libc___fwriting,hash:CRC-32=0x79deca70]]]*/
/* >> __fwriting(3)
 * Return non-zero value when  `stream' is opened write-only  or
 * append-only, or if the last operation on `stream' was a write
 * operation */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___fwriting)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fwriting]]]*/
{
	stream = file_fromuser(stream);
	return (stream->if_exdata->io_chsz != 0);
}
/*[[[end:libc___fwriting]]]*/

/*[[[head:libc___freadable,hash:CRC-32=0x6443ce78]]]*/
/* >> __freadable(3)
 * Return non-zero value when `stream' is not opened write-only or append-only */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
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

/*[[[head:libc___fwritable,hash:CRC-32=0xd7cccf6a]]]*/
/* >> __fwritable(3)
 * Return non-zero value when `stream' is not opened read-only */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___fwritable)(FILE __KOS_FIXED_CONST *stream)
/*[[[body:libc___fwritable]]]*/
{
	stream = file_fromuser(stream);
	return (stream->if_flag & __IO_FILE_IORW) != 0;
}
/*[[[end:libc___fwritable]]]*/

/*[[[head:libc___flbf,hash:CRC-32=0x6ee65875]]]*/
/* >> __flbf(3)
 * Return non-zero value when `stream' is line-buffered */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
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


/*[[[head:libc___fpurge,hash:CRC-32=0xfa2958a0]]]*/
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) void
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

/*[[[head:libc___fpending,hash:CRC-32=0xf5470da]]]*/
/* >> __fpending(3)
 * Return amount of output in bytes pending on a `stream' */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) size_t
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

/*[[[head:libc__flushlbf,hash:CRC-32=0x44e31e48]]]*/
/* >> _flushlbf(3)
 * Flush all line-buffered files */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") void
(LIBCCALL libc__flushlbf)(void) THROWS(...)
/*[[[body:libc__flushlbf]]]*/
{
	file_sync_lnfiles();
}
/*[[[end:libc__flushlbf]]]*/

/*[[[head:libc___fsetlocking,hash:CRC-32=0xf9179fdf]]]*/
/* >> __fsetlocking(3)
 * Set locking status of `stream' to `type'
 * @param: type: One of `FSETLOCKING_*' */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) int
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

/*[[[head:libc___fseterr,hash:CRC-32=0xbf21e9db]]]*/
/* >> __fseterr(3)
 * Set the error indicator for the given `stream' (s.a. `ferror()') */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) void
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
