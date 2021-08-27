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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C
#define GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <kos/hop/handle.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

DECL_BEGIN

#define ASSERT_ERROR_OK(expr) \
	assertf(expr, "errno = %d (%m)", errno)
#define ASSERT_ERROR_NOT_OK(expr, expected_errno) \
	assertf(!(expr) && (errno) == expected_errno, \
	        "errno = %d (%m)", errno)


/* Procfs has to have special  handling for open(2)ing files  from
 * the /proc/[pid]/fd/ folder, as  doing so mustn't follow  normal
 * open rules, where the associated symlink is followed.  Instead,
 * an open invocation for one of these files must behave more like
 * a dup(), followed by `fcntl(F_SETFL)'  to apply the new  oflags
 * that were passed to open().
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
	int error;
	struct stat st;

	/* Check  if  procfs  is  actually   mounted.
	 * If it isn't, then don't perform this test. */
	if (lstat("/proc/self/exe", &st) != 0)
		return;

	/* Pipes exist as anonymous objects in kernel-space.
	 * -> Reading their symlink will yield something
	 *    along  the  lines  of   `anon_inode:[...]' */
	error = pipe(rw);
	ASSERT_ERROR_OK(error == 0);
	error = close(rw[1]);
	ASSERT_ERROR_OK(error == 0);

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
	sprintf(pathbuf, "/proc/self/fd/%d/", rw[0]);
	dupres = open(pathbuf, O_RDONLY);
	/* ENOENT is the result of `E_FSERROR_NOT_A_DIRECTORY' */
	ASSERT_ERROR_NOT_OK(dupres != -1, ENOENT);

	/* By passing O_NOFOLLOW, we can explicitly suppress the custom
	 * follow-last-path-component behavior of  procfs fd files,  at
	 * which point  we'd once  again be  trying to  open a  symlink
	 * directly. (Note  that this  call would  succeed if  we  were
	 * to also  pass O_SYMLINK,  however at  that point  this  call
	 * would  return  a  handle to  a  procfs `struct symlink_node'
	 * object of type  `ProcFS_PerProc_Fd_Entry_Type', rather  than
	 * the pointed-to object) */
	sprintf(pathbuf, "/proc/self/fd/%d", rw[0]);
	dupres = open(pathbuf, O_RDONLY | O_NOFOLLOW);
	/* ELOOP is the result of `E_FSERROR_IS_A_SYMBOLIC_LINK' */
	ASSERT_ERROR_NOT_OK(dupres != -1, ELOOP);

	/* Last  case, as well as the actual special case in which
	 * open() must invoke the custom open-callback that exists
	 * for procfs fd files.
	 * This is the case where open() must behave as dup() */
	sprintf(pathbuf, "/proc/self/fd/%d", rw[0]);
	dupres = open(pathbuf, O_RDONLY);
	ASSERT_ERROR_OK(dupres != -1);

	/* Compare kernel object pointers to ensure that `dupres'
	 * is the same object as rw[0] */
	{
		uint64_t addr1, addr2;
		error = hop(rw[0], HOP_HANDLE_GET_ADDRESS, &addr1);
		ASSERT_ERROR_OK(error == 0);
		error = hop(dupres, HOP_HANDLE_GET_ADDRESS, &addr2);
		ASSERT_ERROR_OK(error == 0);
		assertf(addr1 == addr2,
		        "Not the same kernel object: %I64p != %I64p",
		        addr1, addr2);
	}
	error = close(dupres);
	ASSERT_ERROR_OK(error == 0);
	error = close(rw[0]);
	ASSERT_ERROR_OK(error == 0);

	{
		fd_t dfd;
		char *with_follow;
		char const *expected_with_follow;
		char *without_follow;

		/* Test what had already been mentioned above:
		 * Use files from `/proc/self/fd/[...]/' to implement the
		 * equivalent  of an `openat()' system call, whilst still
		 * using the regular `open()'. */
		dfd = open("/proc/self", O_RDONLY | O_DIRECTORY);
		ASSERT_ERROR_OK(dfd != -1);

		sprintf(pathbuf, "/proc/self/fd/%d/exe", dfd);
		with_follow = frealpathat(AT_FDCWD, pathbuf, NULL, 0, 0);
		ASSERT_ERROR_OK(with_follow != NULL);
		without_follow = frealpathat(AT_FDCWD, pathbuf, NULL, 0, AT_SYMLINK_NOFOLLOW);
		ASSERT_ERROR_OK(without_follow != NULL);
		error = close(dfd);
		ASSERT_ERROR_OK(error == 0);

		/* `with_follow'  should be the equivalent of `readlink("/proc/self/exe")'
		 * we can check this by comparing it against `expected_with_follow', which
		 * should be an identical string. */
		expected_with_follow = dlmodulename(dlopen(NULL, 0));
		assertf(expected_with_follow != NULL, "%s", dlerror());
		assertf(strcmp(with_follow, expected_with_follow) == 0,
		        "%q != %q", with_follow, expected_with_follow);

		/* `without_follow' should simply be a string `/proc/[getpid()]/exe', since
		 * in  this  case  the  final  symbolic  link  `exe'  wasn't  dereferenced. */
		sprintf(pathbuf, "/proc/%d/exe", getpid());
		assertf(strcmp(without_follow, pathbuf) == 0,
		        "%q != %q", without_follow, pathbuf);


		free(without_follow);
		free(with_follow);
	}

}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_OPEN_ANON_INODE_C */
