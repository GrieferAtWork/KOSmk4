/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C
#define GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/ioctl/fd.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <system-test/ctest.h>

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

DECL_BEGIN

/* Procfs has to have special  handling for open(2)ing files  from
 * the /proc/[pid]/fd/ folder, as  doing so mustn't follow  normal
 * open rules, where the associated symlink is followed.  Instead,
 * an open invocation for one of these files must behave more like
 * a dup(2), followed by `fcntl(F_SETFL)' to apply the new  oflags
 * that were passed to open(2).
 *
 * While the regular follow-symlink approach works for ~regular~,
 * named files, anonymous  files would still  appear as  symlinks
 * within /proc/[pid]/fd/, though they can't be opened the normal
 * way because they don't actually have a name.
 *
 * Expected behavior:
 *    `open("/proc/self/fd/0")' acts as `dup(0)'
 *
 * Behavior without special handling:
 *    `open("/proc/self/fd/0")' acts as `open(readlink("/proc/self/fd/0"))'
 *                              acts as `open(frealpath(fd: 0))'
 *
 */
DEFINE_TEST(open_anon_inode) {
	fd_t rw[2], dupres;
	char pathbuf[64];

	/* Check  if  procfs  is  actually   mounted.
	 * If it isn't, then don't perform this test. */
	if (access("/proc/self/exe", F_OK) != 0)
		return;

	/* Pipes exist as anonymous objects in kernel-space.
	 * -> Reading their symlink will yield something
	 *    along  the  lines  of   `anon_inode:[...]' */
	EQ(0, pipe(rw)); /* NOLINT */
	EQ(0, close(rw[1]));

	/* First  test: When using one of the  fd/xxx files as part of a
	 * path expression, the symlink must still be followed normally,
	 * and the expression would have to behave more like a call to
	 * openat():
	 * >> open("/proc/self/fd/{dfd}/{path}", oflags);
	 * Same as:
	 * >> openat(dfd, path, oflags);
	 * As  such, by  having the fd's  number be followed  by a slash,
	 * we're explicitly dereferencing the symlink (which in this case
	 * will expand to something like  `anon_inode:[reader:pipe:...]`)
	 * as  a path,  which must  obviously result  in a file-not-found
	 * exception. */
	ISpos(sprintf(pathbuf, "/proc/self/fd/%d/", rw[0]));
	EQ(-1, open(pathbuf, O_RDONLY)); /* NOLINT */
	EQerrno(ENOENT); /* ENOENT is the result of `E_FSERROR_NOT_A_DIRECTORY' */

	/* By passing O_NOFOLLOW, we can explicitly suppress the custom
	 * follow-last-path-component behavior of  procfs fd files,  at
	 * which point  we'd once  again be  trying to  open a  symlink
	 * directly. */
	ISpos(sprintf(pathbuf, "/proc/self/fd/%d", rw[0]));
	EQ(-1, open(pathbuf, O_RDONLY | O_NOFOLLOW)); /* NOLINT */
	EQerrno(ELOOP); /* ELOOP is the result of `E_FSERROR_IS_A_SYMBOLIC_LINK' */

	/* Last  case, as well as the actual special case in which
	 * open() must invoke the custom open-callback that exists
	 * for procfs fd files.
	 * This is the case where open() must behave as dup() */
	ISpos(sprintf(pathbuf, "/proc/self/fd/%d", rw[0]));
	ISpos((dupres = open(pathbuf, O_RDONLY))); /* NOLINT */

	/* Compare kernel object pointers to ensure that `dupres'
	 * is the same object as rw[0] */
	{
		uint64_t addr1, addr2;
		EQ(0, ioctl(rw[0], FD_IOC_GETADDR, &addr1));
		EQ(0, ioctl(dupres, FD_IOC_GETADDR, &addr2));
		EQf(addr1, addr2, "Not the same kernel object");
	}
	EQ(0, close(dupres));
	EQ(0, close(rw[0]));

	{
		fd_t dfd;
		char *with_follow;
		char const *expected_with_follow;
		char *without_follow;

		/* Test what had already been mentioned above:
		 * Use files from `/proc/self/fd/[...]/' to implement the
		 * equivalent  of an `openat()' system call, whilst still
		 * using the regular `open(2)'. */
		ISpos((dfd = open("/proc/self", O_RDONLY | O_DIRECTORY))); /* NOLINT */

		ISpos(sprintf(pathbuf, "/proc/self/fd/%d/exe", dfd));
		ISnonnull((with_follow = frealpathat(AT_FDCWD, pathbuf, NULL, 0, 0)));
		ISnonnull((without_follow = frealpathat(AT_FDCWD, pathbuf, NULL, 0, AT_SYMLINK_NOFOLLOW)));
		EQ(0, close(dfd));

		/* `with_follow'  should be the equivalent of `readlink("/proc/self/exe")'
		 * we can check this by comparing it against `expected_with_follow', which
		 * should be an identical string. */
		ISnonnullf((expected_with_follow = dlmodulename(dlopen(NULL, 0))), "%s", dlerror());
		EQstr(expected_with_follow, with_follow);

		/* `without_follow' should simply be a string `/proc/[getpid()]/exe', since
		 * in  this  case  the  final  symbolic  link  `exe'  wasn't  dereferenced. */
		ISpos(sprintf(pathbuf, "/proc/%d/exe", getpid()));
		EQstr(pathbuf, without_follow);

		free(without_follow);
		free(with_follow);
	}

}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C */
