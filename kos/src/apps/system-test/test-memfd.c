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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_MEMFD_C
#define GUARD_APPS_SYSTEM_TEST_TEST_MEMFD_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _FILE_OFFSET_BITS 64
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(memfd) {
	fd_t mfd;
	size_t i, ps = getpagesize();
	byte_t *base;
	struct stat st;
	char buf[16];

	ISpos((mfd = memfd_create("mymemfd", MFD_CLOEXEC)));
	EQ(0, fstat(mfd, &st));
	EQ(0, st.st_size);

	/* Attempts to write beyond the physically possible file size limit must be clamped.
	 * Note: yes, this system call is able to succeed, and no: it doesn't cause unconditional
	 *       out-of-memory,  simply because KOS  doesn't actually allocate  memory for all of
	 *       the file locations that aren't actually used! */
	errno = 0;

	/* This would extend the file size beyond the maximum representable. */
	EQ(-1, pwrite(mfd, "!abcdef", 7, (uint64_t)-1));
	EQerrno(EFBIG);

	/* This is just barely possible, but only the first byte can be written. */
	EQ(1, pwrite(mfd, "!abcdef", 7, (uint64_t)-2));

	/* Assert that the file size is now 2^64-1 */
	EQ(0, fstat(mfd, &st));
	EQ((uint64_t)-1, st.st_size);

	/* Map the last page of the memfd into memory. */
	NE((byte_t *)MAP_FAILED,
	   (base = (byte_t *)mmap(NULL, ps, PROT_READ | PROT_WRITE,
	                          MAP_SHARED | MAP_FILE,
	                          mfd, (uint64_t)0 - ps)));

	/* The second-to-last byte of the page should be a '!' character; all others must be 0-bytes */
	for (i = 0; i < ps - 2; ++i)
		EQf(0, base[i], "i = %" PRIuSIZ, i);
	EQ('!', base[ps - 2]);
	EQ('\0', base[ps - 1]); /* This byte can't be accessed via pread/pwrite, but can via mmap()! */

	/* Make changes to the mapping. */
	strcpy((char *)base, "Ping");

	/* The changes should be immediately visible to read/write */
	EQ((ssize_t)sizeof(buf), pread(mfd, buf, sizeof(buf), (uint64_t)0 - ps));
	EQmem("Ping\0\0\0\0\0\0\0\0\0\0\0\0", buf, 16);

	/* I/O works in both ways. */
	EQ(4, pwrite(mfd, "Pong", 4, (uint64_t)0 - ps));
	EQmem("Pong", base, 5);

	/* If we truncate the file, then the connection to the mapping will be lost. */
	EQ(0, ftruncate(mfd, 0));
	EQ(6, pwrite(mfd, "Hello?", 6, (uint64_t)0 - ps));
	EQ(0, fstat(mfd, &st));
	EQ(((uint64_t)0 - ps) + 6, st.st_size);
	EQmem("Pong", base, 5); /* This still contains what was written earlier. */
	EQ(0, munmap(base, ps));

	/* Also make sure that the procfs fd-text is correct. */
	sprintf(buf, "/proc/self/fd/%d", mfd);
	EQ(13, readlink(buf, buf, sizeof(buf)));
	EQmem("memfd:mymemfd", buf, 13);

	EQ(0, close(mfd));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_MEMFD_C */
