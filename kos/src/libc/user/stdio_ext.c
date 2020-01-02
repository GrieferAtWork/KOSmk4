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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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





/*[[[start:implementation]]]*/

/*[[[head:__fbufsize,hash:CRC-32=0xa3d8dc26]]]*/
/* Return the size of the buffer of FP in bytes currently in use by the given stream */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fbufsize") size_t
NOTHROW_NCX(LIBCCALL libc___fbufsize)(FILE *fp)
/*[[[body:__fbufsize]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (size_t)fp->if_bufsiz;
}
/*[[[end:__fbufsize]]]*/

/*[[[head:__freading,hash:CRC-32=0x5e015f07]]]*/
/* Return non-zero value iff the stream FP is opened readonly,
 * or if the last operation on the stream was a read operation */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__freading") int
NOTHROW_NCX(LIBCCALL libc___freading)(FILE *fp)
/*[[[body:__freading]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_flag & __IO_FILE_IORW) ||
	       (fp->if_exdata->io_chsz == 0);
}
/*[[[end:__freading]]]*/

/*[[[head:__fwriting,hash:CRC-32=0x47725344]]]*/
/* Return non-zero value iff the stream FP is opened write-only or
 * append-only, or if the last operation on the stream was a write
 * operation */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fwriting") int
NOTHROW_NCX(LIBCCALL libc___fwriting)(FILE *fp)
/*[[[body:__fwriting]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_exdata->io_chsz != 0);
}
/*[[[end:__fwriting]]]*/

/*[[[head:__freadable,hash:CRC-32=0xc0c5e22b]]]*/
/* Return non-zero value iff stream FP is not opened write-only or append-only */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__freadable") int
NOTHROW_NCX(LIBCCALL libc___freadable)(FILE *fp)
/*[[[body:__freadable]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	(void)fp;
	/* KOS's stdio itself always allows reads.
	 * It's up to the kernel to stop us from doing so. */
	return 1;
}
/*[[[end:__freadable]]]*/

/*[[[head:__fwritable,hash:CRC-32=0x6dc544cf]]]*/
/* Return non-zero value iff stream FP is not opened read-only */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fwritable") int
NOTHROW_NCX(LIBCCALL libc___fwritable)(FILE *fp)
/*[[[body:__fwritable]]]*/
{
	assert(fp);
	assert(fp->if_exdata);
	return (fp->if_flag & __IO_FILE_IORW) != 0;
}
/*[[[end:__fwritable]]]*/

/*[[[head:__flbf,hash:CRC-32=0xccc38147]]]*/
/* Return non-zero value iff the stream FP is line-buffered */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__flbf") int
NOTHROW_NCX(LIBCCALL libc___flbf)(FILE *fp)
/*[[[body:__flbf]]]*/
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
/*[[[end:__flbf]]]*/

/*[[[head:__fpurge,hash:CRC-32=0xcd8afb5a]]]*/
/* Discard all pending buffered I/O on the stream FP */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fpurge") void
NOTHROW_NCX(LIBCCALL libc___fpurge)(FILE *fp)
/*[[[body:__fpurge]]]*/
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
/*[[[end:__fpurge]]]*/

/*[[[head:__fpending,hash:CRC-32=0xf6879ec4]]]*/
/* Return amount of output in bytes pending on a stream FP */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fpending") size_t
NOTHROW_NCX(LIBCCALL libc___fpending)(FILE *fp)
/*[[[body:__fpending]]]*/
{
	size_t result;
	struct iofile_data *ex;
	assert(fp);
	ex = fp->if_exdata;
	assert(ex);
	result = ATOMIC_READ(ex->io_chsz);
	return result;
}
/*[[[end:__fpending]]]*/

/*[[[head:_flushlbf,hash:CRC-32=0x28836784]]]*/
/* Flush all line-buffered files */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext._flushlbf") void
NOTHROW_NCX(LIBCCALL libc__flushlbf)(void)
/*[[[body:_flushlbf]]]*/
{
	file_sync_lnfiles();
}
/*[[[end:_flushlbf]]]*/

/*[[[head:__fsetlocking,hash:CRC-32=0x9436fb87]]]*/
/* Set locking status of stream FP to TYPE */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.FILE.utility.ext.__fsetlocking") int
NOTHROW_NCX(LIBCCALL libc___fsetlocking)(FILE *fp,
                                         int type)
/*[[[body:__fsetlocking]]]*/
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
			ATOMIC_FETCHOR(fp->if_flag, IO_NOLOCK);
		} else {
			ATOMIC_FETCHAND(fp->if_flag, ~IO_NOLOCK);
		}
	}
#endif /* IO_NOLOCK */
	return result;
}
/*[[[end:__fsetlocking]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xfd5529ca]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(__fbufsize, libc___fbufsize);
DEFINE_PUBLIC_WEAK_ALIAS(__freading, libc___freading);
DEFINE_PUBLIC_WEAK_ALIAS(__fwriting, libc___fwriting);
DEFINE_PUBLIC_WEAK_ALIAS(__freadable, libc___freadable);
DEFINE_PUBLIC_WEAK_ALIAS(__fwritable, libc___fwritable);
DEFINE_PUBLIC_WEAK_ALIAS(__flbf, libc___flbf);
DEFINE_PUBLIC_WEAK_ALIAS(__fpurge, libc___fpurge);
DEFINE_PUBLIC_WEAK_ALIAS(__fpending, libc___fpending);
DEFINE_PUBLIC_WEAK_ALIAS(_flushlbf, libc__flushlbf);
DEFINE_PUBLIC_WEAK_ALIAS(_IO_flush_all_linebuffere, libc__flushlbf);
DEFINE_PUBLIC_WEAK_ALIAS(__fsetlocking, libc___fsetlocking);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_EXT_C */
