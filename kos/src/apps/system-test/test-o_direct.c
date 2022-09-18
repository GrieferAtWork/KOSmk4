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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_O_DIRECT_C
#define GUARD_APPS_SYSTEM_TEST_TEST_O_DIRECT_C 1
#define _BSD_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/ioctl/file.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE void
do_o_direct_test(char const *filename) {
	fd_t fd;
	struct file_blkshift align;
	void *buf;
	size_t blocksize;
	size_t blockalign;
	size_t bufsize;
	struct stat st;

	unlink(filename);
	fd = open(filename, O_CREAT | O_EXCL | O_DIRECT | O_RDWR, 0644); /* NOLINT */
	if (fd < 0) {
		if (bcmp(filename, "/var/", 5 * sizeof(char)) == 0)
			mkdir("/var/", 755);
		LEd(0, (fd = open(filename, O_CREAT | O_EXCL | O_DIRECT | O_RDWR, 0644))); /* NOLINT */
	}

	/* Query alignment requirements. */
	EQd(0, ioctl(fd, FILE_IOC_BLKSHIFT, &align));

	/* Buffer alignment requirements must be at most as restrictive as block-alignment. */
	blocksize  = (size_t)1 << align.fbs_blck;
	blockalign = (size_t)1 << align.fbs_ioba;
	GEd(blocksize, blockalign);

	/* Allocate a properly aligned (and sized) buffer for I/O on at least 64 byts. */
	bufsize = CEIL_ALIGN(64, blocksize);
	buf     = memalign(blockalign, bufsize);
	assertf(buf, "memalign(%" PRIuSIZ ", %" PRIuSIZ ") failed", blockalign, bufsize);
	bzero(buf, bufsize);
	strcpy((char *)buf, "Test Data!");

	/* Unaligned I/O must produce errors. */
	if (blocksize > 1) {
		errno = 0;
		EQss(-1, pwrite(fd, buf, bufsize - 1, 0));
		EQd(errno, EINVAL);
		errno = 0;
		EQss(-1, pwrite(fd, buf, bufsize, 1));
		EQd(errno, EINVAL);
	}
	if (blockalign > 1) {
		errno = 0;
		EQss(-1, pwrite(fd, (byte_t *)buf + 1, bufsize, 0));
		EQd(errno, EINVAL);
	}

	/* Now to actually do I/O */
	EQss(bufsize, pwrite(fd, buf, bufsize, 0));
	EQd(0, fstat(fd, &st));
	EQu64((uint64_t)bufsize, (uint64_t)st.st_size);

	/* Also make sure that we can read back data. */
	memset(buf, 0xcc, bufsize);
	EQss(bufsize, pread(fd, buf, bufsize, 0));
	assertf(strcmp((char *)buf, "Test Data!") == 0,
	        "%$[hex]\n", bufsize, buf);

	/* Cleanup... */
	EQd(0, unlink(filename));
	EQd(0, close(fd));
}

DEFINE_TEST(o_direct) {
	/* Test for direct I/O */
	do_o_direct_test("/var/o_direct.txt");

	/* Also test O_DIRECT on ramfs files */
	do_o_direct_test("/tmp/o_direct.txt");
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_O_DIRECT_C */
