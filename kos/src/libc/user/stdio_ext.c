/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_STDIO_EXT_C
#define GUARD_LIBC_USER_STDIO_EXT_C 1

#include "../api.h"
/**/

#include "stdio-api.h"
#include "stdio_ext.h"

DECL_BEGIN







/*[[[head:libc___fbufsize,hash:CRC-32=0xa7687e05]]]*/
/* Return the size of the buffer of FP in bytes currently in use by the given stream */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc___fbufsize)(FILE *fp)
/*[[[body:libc___fbufsize]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (size_t)fp->if_bufsiz;
}
/*[[[end:libc___fbufsize]]]*/

/*[[[head:libc___freading,hash:CRC-32=0xb7673689]]]*/
/* Return non-zero value iff the stream FP is opened readonly,
 * or if the last operation on the stream was a read operation */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___freading)(FILE *fp)
/*[[[body:libc___freading]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_flag & __IO_FILE_IORW) ||
	       (fp->if_exdata->io_chsz == 0);
}
/*[[[end:libc___freading]]]*/

/*[[[head:libc___fwriting,hash:CRC-32=0x73604f24]]]*/
/* Return non-zero value iff the stream FP is opened write-only or
 * append-only, or if the last operation on the stream was a write
 * operation */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___fwriting)(FILE *fp)
/*[[[body:libc___fwriting]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_exdata->io_chsz != 0);
}
/*[[[end:libc___fwriting]]]*/

/*[[[head:libc___freadable,hash:CRC-32=0xe5c33448]]]*/
/* Return non-zero value iff stream FP is not opened write-only or append-only */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___freadable)(FILE *fp)
/*[[[body:libc___freadable]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	(void)fp;
	/* KOS's stdio itself always allows reads.
	 * It's up to the kernel to stop us from doing so. */
	return 1;
}
/*[[[end:libc___freadable]]]*/

/*[[[head:libc___fwritable,hash:CRC-32=0x568f4f55]]]*/
/* Return non-zero value iff stream FP is not opened read-only */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___fwritable)(FILE *fp)
/*[[[body:libc___fwritable]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_flag & __IO_FILE_IORW) != 0;
}
/*[[[end:libc___fwritable]]]*/

/*[[[head:libc___flbf,hash:CRC-32=0x425b258c]]]*/
/* Return non-zero value iff the stream FP is line-buffered */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___flbf)(FILE *fp)
/*[[[body:libc___flbf]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	if (fp->if_flag & IO_LNIFTYY) {
		if (FMUSTLOCK(fp)) {
			file_write(fp);
			file_determine_isatty(fp);
			file_endwrite(fp);
		} else {
			file_determine_isatty(fp);
		}
	}
	return (fp->if_flag & IO_LNBUF) != 0;
}
/*[[[end:libc___flbf]]]*/

/*[[[head:libc___fpurge,hash:CRC-32=0x4ef865fb]]]*/
/* Discard all pending buffered I/O on the stream FP */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___fpurge)(FILE *fp)
/*[[[body:libc___fpurge]]]*/
{
	struct iofile_data *ex;
	assert(fp);
	ex = fp->if_exdata;
	assert(ex);
	if (FMUSTLOCK(fp)) {
		file_write(fp);
		fp->if_ptr += fp->if_cnt;
		fp->if_cnt  = 0;
		ex->io_chng = fp->if_base;
		ex->io_chsz = 0;
		ex->io_mbs.__word = 0;
		file_endwrite(fp);
	} else {
		fp->if_ptr += fp->if_cnt;
		fp->if_cnt  = 0;
		ex->io_chng = fp->if_base;
		ex->io_chsz = 0;
		ex->io_mbs.__word = 0;
	}
}
/*[[[end:libc___fpurge]]]*/

/*[[[head:libc___fpending,hash:CRC-32=0xc5ccb8c3]]]*/
/* Return amount of output in bytes pending on a stream FP */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc___fpending)(FILE *fp)
/*[[[body:libc___fpending]]]*/
{
	size_t result;
	struct iofile_data *ex;
	assert(fp);
	ex = fp->if_exdata;
	assert(ex);
	result = ATOMIC_READ(ex->io_chsz);
	return result;
}
/*[[[end:libc___fpending]]]*/

/*[[[head:libc__flushlbf,hash:CRC-32=0x8baf5ba3]]]*/
/* Flush all line-buffered files */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") void
(LIBCCALL libc__flushlbf)(void) THROWS(...)
/*[[[body:libc__flushlbf]]]*/
{
	file_sync_lnfiles();
}
/*[[[end:libc__flushlbf]]]*/

/*[[[head:libc___fsetlocking,hash:CRC-32=0x75ded10a]]]*/
/* Set locking status of stream FP to TYPE */
INTERN ATTR_SECTION(".text.crt.FILE.utility.ext") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___fsetlocking)(FILE *fp,
                                         int type)
/*[[[body:libc___fsetlocking]]]*/
{
	int result;
	assert(fp);
	assert(fp->if_exdata);
	(void)type;
	result = FMUSTLOCK(fp)
	         ? FSETLOCKING_INTERNAL
	         : FSETLOCKING_BYCALLER;
#ifdef IO_NOLOCK
	if (type != FSETLOCKING_QUERY) {
		if (type == FSETLOCKING_BYCALLER) {
			ATOMIC_OR(fp->if_flag, IO_NOLOCK);
		} else {
			ATOMIC_AND(fp->if_flag, ~IO_NOLOCK);
		}
	}
#endif /* IO_NOLOCK */
	return result;
}
/*[[[end:libc___fsetlocking]]]*/





/*[[[start:exports,hash:CRC-32=0x38cda9ad]]]*/
DEFINE_PUBLIC_ALIAS(__fbufsize, libc___fbufsize);
DEFINE_PUBLIC_ALIAS(__freading, libc___freading);
DEFINE_PUBLIC_ALIAS(__fwriting, libc___fwriting);
DEFINE_PUBLIC_ALIAS(__freadable, libc___freadable);
DEFINE_PUBLIC_ALIAS(__fwritable, libc___fwritable);
DEFINE_PUBLIC_ALIAS(__flbf, libc___flbf);
DEFINE_PUBLIC_ALIAS(__fpurge, libc___fpurge);
DEFINE_PUBLIC_ALIAS(__fpending, libc___fpending);
DEFINE_PUBLIC_ALIAS(_IO_flush_all_linebuffere, libc__flushlbf);
DEFINE_PUBLIC_ALIAS(_flushlbf, libc__flushlbf);
DEFINE_PUBLIC_ALIAS(__fsetlocking, libc___fsetlocking);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_EXT_C */
