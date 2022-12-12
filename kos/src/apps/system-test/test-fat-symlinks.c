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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FAT_SYMLINKS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FAT_SYMLINKS_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/* Ensure that symlinks in FAT folders work */
DEFINE_TEST(fat_symlinks) {
	char buf[64];
	if (access("/var", R_OK | W_OK) != 0)
		return;
	unlink("/var/test-symlink");
	sync();                              /* sync */
	ksysctl(KSYSCTL_SYSTEM_CLEARCACHES); /* cc */

	EQ(0, symlink("link1-text", "/var/test-symlink"));
	EQ(10, readlink("/var/test-symlink", buf, sizeof(buf)));
	buf[10] = 0;
	EQstr("link1-text", buf);
	EQ(0, unlink("/var/test-symlink"));

	EQ(0, symlink("link2-text", "/var/test-symlink"));
	EQ(10, readlink("/var/test-symlink", buf, sizeof(buf)));
	buf[10] = 0;
	EQstr("link2-text", buf);
	EQ(0, unlink("/var/test-symlink"));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FAT_SYMLINKS_C */
