/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FLOCK_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FLOCK_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <bsd/libutil.h>
#include <kos/types.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

DECL_BEGIN

#define FLOCK_NAME "/tmp/my-flock"

DEFINE_TEST(flock) {
	fd_t fd;
	(void)unlink(FLOCK_NAME);

	/* The first flock-open must work */
	ISpos((fd = flopen(FLOCK_NAME, O_RDWR | O_CREAT | O_NONBLOCK, 0644)));

	/* At this point, trying to open the file again must fail with E_WOULDBLOCK */
	EQ(-1, flopen(FLOCK_NAME, O_RDWR | O_CREAT | O_NONBLOCK, 0644));
	EQerrno(EWOULDBLOCK);

	/* After closing the file, opening it must once again work. */
	EQ(0, close(fd));
	ISpos((fd = flopen(FLOCK_NAME, O_RDWR | O_CREAT | O_NONBLOCK, 0644)));
	EQ(-1, flopen(FLOCK_NAME, O_RDWR | O_CREAT | O_NONBLOCK, 0644));
	EQerrno(EWOULDBLOCK);
	EQ(0, close(fd));

	/* Cleanup... */
	EQ(0, unlink(FLOCK_NAME));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FLOCK_C */
