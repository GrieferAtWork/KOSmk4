/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C
#define GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C 1

#include "../api.h"
/**/

#include "../libc/uchar.h"
#include "parts.wchar.utime.h"
#include <uchar.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:wutime,hash:0x41e6445e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.modify_time.wutime") int
NOTHROW_RPC(LIBCCALL libc_wutime)(char32_t const *filename,
                                  struct utimbuf const *file_times)
/*[[[body:wutime]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c32tombs(filename);
	if likely(used_filename) {
		result = utime(used_filename, file_times);
		libc_uchar_free(used_filename);
	}
	return result;
}
/*[[[end:wutime]]]*/

/*[[[head:DOS$wutime,hash:0x8045efba]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time.wutime") int
NOTHROW_RPC(LIBDCALL libd_wutime)(char16_t const *filename,
                                  struct utimbuf const *file_times)
/*[[[body:DOS$wutime]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = utime(used_filename, file_times);
		libc_uchar_free(used_filename);
	}
	return result;
}
/*[[[end:DOS$wutime]]]*/

/*[[[head:wutime64,hash:0x1a9c416f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_wutime64, libc_wutime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.modify_time.wutime64") int
NOTHROW_RPC(LIBCCALL libc_wutime64)(char32_t const *filename,
                                    struct utimbuf64 const *file_times)
/*[[[body:wutime64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c32tombs(filename);
	if likely(used_filename) {
		result = utime64(used_filename, file_times);
		libc_uchar_free(used_filename);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:wutime64]]]*/

/*[[[head:DOS$wutime64,hash:0x4ba88aee]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd_wutime64, libd_wutime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time.wutime64") int
NOTHROW_RPC(LIBDCALL libd_wutime64)(char16_t const *filename,
                                    struct utimbuf64 const *file_times)
/*[[[body:DOS$wutime64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = utime64(used_filename, file_times);
		libc_uchar_free(used_filename);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:DOS$wutime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x2cfaa8b5]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(wutime, libc_wutime);
DEFINE_PUBLIC_WEAK_ALIAS(_wutime32, libc_wutime);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wutime, libd_wutime);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wutime32, libd_wutime);
DEFINE_PUBLIC_WEAK_ALIAS(wutime64, libc_wutime64);
DEFINE_PUBLIC_WEAK_ALIAS(_wutime64, libc_wutime64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wutime64, libd_wutime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UTIME_C */
