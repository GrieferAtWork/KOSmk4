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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C
#define GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C 1

#include "../api.h"
/**/

#include <malloc.h>
#include <uchar.h>

#include "../libc/uchar.h"
#include "parts.wchar.utime.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_wutime,hash:CRC-32=0xeecda22f]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wutime)(char32_t const *filename,
                                  struct utimbuf const *file_times)
/*[[[body:libc_wutime]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c32tombs(filename);
	if likely(used_filename) {
		result = utime(used_filename, file_times);
		free(used_filename);
	}
	return result;
}
/*[[[end:libc_wutime]]]*/

/*[[[head:libd__wutime32,hash:CRC-32=0x8b4f2f05]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd__wutime32)(char16_t const *filename,
                                     struct utimbuf const *file_times)
/*[[[body:libd__wutime32]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = utime(used_filename, file_times);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wutime32]]]*/

/*[[[head:libc_wutime64,hash:CRC-32=0x8e1bd0a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_wutime64, libc_wutime);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wutime64)(char32_t const *filename,
                                    struct utimbuf64 const *file_times)
/*[[[body:libc_wutime64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c32tombs(filename);
	if likely(used_filename) {
		result = utime64(used_filename, file_times);
		free(used_filename);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_wutime64]]]*/

/*[[[head:libd__wutime64,hash:CRC-32=0xc461d51]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd__wutime64)(char16_t const *filename,
                                     struct utimbuf64 const *file_times)
/*[[[body:libd__wutime64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = utime64(used_filename, file_times);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wutime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc116b8c9]]]*/
DEFINE_PUBLIC_ALIAS(DOS$_wutime32, libd__wutime32);
DEFINE_PUBLIC_ALIAS(wutime, libc_wutime);
DEFINE_PUBLIC_ALIAS(DOS$_wutime64, libd__wutime64);
DEFINE_PUBLIC_ALIAS(wutime64, libc_wutime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C */
