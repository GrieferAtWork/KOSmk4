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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_DOSABI_C
#define GUARD_APPS_SYSTEM_TEST_TEST_DOSABI_C 1
#define _UTF_SOURCE 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef __LIBDCALL_IS_LIBKCALL
#if (defined(__CRT_HAVE_DOS$_makepath_s) && defined(__CRT_HAVE__makepath_s) && \
     defined(__CRT_HAVE_DOS$_splitpath_s) && defined(__CRT_HAVE__splitpath_s))

extern errno_t __LIBDCALL
DOS__makepath_s(char *buf, size_t buflen, char const *drive,
                char const *dir, char const *file, char const *ext)
	ASMNAME("DOS$_makepath_s");

extern errno_t __LIBKCALL
KOS__makepath_s(char *buf, size_t buflen, char const *drive,
                char const *dir, char const *file, char const *ext)
	ASMNAME("_makepath_s");

extern errno_t __LIBDCALL
DOS__splitpath_s(char const *__restrict abspath,
                 char *drive, size_t drivelen,
                 char *dir, size_t dirlen,
                 char *file, size_t filelen,
                 char *ext, size_t extlen)
	ASMNAME("DOS$_splitpath_s");

extern errno_t __LIBKCALL
KOS__splitpath_s(char const *__restrict abspath,
                 char *drive, size_t drivelen,
                 char *dir, size_t dirlen,
                 char *file, size_t filelen,
                 char *ext, size_t extlen)
	ASMNAME("_splitpath_s");


DEFINE_TEST(dosabi) {
	char dos_fullpath[128];
	char kos_fullpath[128];
	static char const drive[] = "C";
	static char const dir[]   = "\\path\\to\\some\\file\\";
	static char const file[]  = "some_file";
	static char const ext[]   = ".txt";
#define ASSERT_STRINGS_EQUAL(a, b) \
	assertf(strcmp(a, b) == 0, "%q != %q", a, b)
	EQd(0, KOS__makepath_s(kos_fullpath, sizeof(kos_fullpath), drive, dir, file, ext));
	EQd(0, DOS__makepath_s(dos_fullpath, sizeof(dos_fullpath), drive, dir, file, ext));
	ASSERT_STRINGS_EQUAL(kos_fullpath, dos_fullpath);
	ASSERT_STRINGS_EQUAL(kos_fullpath, "C:\\path\\to\\some\\file\\some_file.txt");
	{
		char buf_drive[64];
		char buf_dir[64];
		char buf_file[64];
		char buf_ext[64];
		EQd(0, KOS__splitpath_s(kos_fullpath,
		                        buf_drive, sizeof(buf_drive),
		                        buf_dir, sizeof(buf_dir),
		                        buf_file, sizeof(buf_file),
		                        buf_ext, sizeof(buf_ext)));
		ASSERT_STRINGS_EQUAL(buf_drive, drive);
		ASSERT_STRINGS_EQUAL(buf_dir, dir);
		ASSERT_STRINGS_EQUAL(buf_file, file);
		ASSERT_STRINGS_EQUAL(buf_ext, ext);
		EQd(0, DOS__splitpath_s(kos_fullpath,
		                        buf_drive, sizeof(buf_drive),
		                        buf_dir, sizeof(buf_dir),
		                        buf_file, sizeof(buf_file),
		                        buf_ext, sizeof(buf_ext)));
		ASSERT_STRINGS_EQUAL(buf_drive, drive);
		ASSERT_STRINGS_EQUAL(buf_dir, dir);
		ASSERT_STRINGS_EQUAL(buf_file, file);
		ASSERT_STRINGS_EQUAL(buf_ext, ext);
	}
}

#endif /* __CRT_HAVE_... */
#endif /* !__LIBDCALL_IS_LIBKCALL */


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_DOSABI_C */
