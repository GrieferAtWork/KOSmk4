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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FS_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

DECL_BEGIN

#define assertFileText(dfd, name, text) \
	assertFileText_impl(dfd, name, text, __LINE__)

PRIVATE void
assertFileText_impl(fd_t dfd, char const *name,
                    char const *text, int line) {
	fd_t fd;
	int error;
	size_t len = strlen(text);
	fd = openat(dfd, name, O_RDONLY);
	assertf(fd != -1,
	        "%s\n"
	        "line:%d",
	        strerror(errno),
	        line);
	{
		char buf[16];
		ssize_t temp;
		temp = read(fd, buf, sizeof(buf));
		assertf(temp == (ssize_t)len,
		        "%Id (%s)\n"
		        "line:%d",
		        temp, strerror(errno), line);
		assertf(memcmp(buf, text, len) == 0,
		        "%$q != %q\n"
		        "line:%d",
		        len, buf, text, line);
	}
	error = close(fd);
	assertf(error == 0, "%s\n"
	                    "line:%d",
	        strerror(errno), line);
}

#define checkTestFiles(inherited_dfd, files_must_exist) \
	checkTestFiles_impl(inherited_dfd, files_must_exist, __LINE__)

PRIVATE void
checkTestFiles_impl(char const *path,
                    bool files_must_exist,
                    int line) {
	DIR *d;
	int error;
	bool found_test = false;
	bool found_test2 = false;
	char const *error_reason;
	d = opendir(path);
	assertf(d != NULL,
	        "%s\n"
	        "line:%d",
	        strerror(errno),
	        line);
	for (;;) {
		struct dirent *de;
		errno = 0;
		de = readdir(d);
		if (!de) {
			assertf(errno == 0,
			        "%s\n"
			        "line:%d",
			        strerror(errno),
			        line);
			break;
		}
		if (strcmp(de->d_name, "test") == 0) {
			found_test = true;
		} else if (strcmp(de->d_name, "test2") == 0) {
			found_test2 = true;
		}
	}
	error_reason = files_must_exist ? "Didn't find file"
	                                : "Found deleted file";
	assertf(found_test == files_must_exist,
	        "%s: `test'\n"
	        "line:%d",
	        error_reason,
	        line);
	assertf(found_test2 == files_must_exist,
	        "%s: `test2'\n"
	        "line:%d",
	        error_reason,
	        line);
	error = closedir(d);
	assertf(error == 0,
	        "%s\n"
	        "line:%d",
	        strerror(errno),
	        line);
}

PRIVATE void testPath(char const *path) {
	ssize_t temp;
	fd_t fd;
	fd_t dfd = open(path, O_PATH | O_CLOEXEC);
	int error;
	assertf(dfd != -1, "%s", strerror(errno));
	/* Cleanup artifacts from possibly failed prior tests... */
	unlinkat(dfd, "test", 0);
	unlinkat(dfd, "test2", 0);
	checkTestFiles(path, false);

	/* Create a previous non-existent file. */
	fd = openat(dfd, "test", O_WRONLY | O_CREAT | O_EXCL, 0644);
	assertf(fd != -1, "%s", strerror(errno));
	temp = write(fd, "F1\n", 3);
	assertf(temp == 3, "%s", strerror(errno));
	error = close(fd);
	assertf(error == 0, "%s", strerror(errno));

	/* At this point, the file should already exist */
	fd = openat(dfd, "test", O_WRONLY | O_CREAT | O_EXCL, 0644);
	assertf(fd == -1, "%d", fd);
	assertf(errno == EEXIST, "%s", strerror(errno));

	/* At this point, the file should already exist */
	assertFileText(dfd, "test", "F1\n");

	/* Now rename the file */
	assertf(renameat(dfd, "test", dfd, "test2") == 0, "%s", strerror(errno));

	/* The open should now fail. */
	fd = openat(dfd, "test", O_RDONLY);
	assertf(fd == -1, "%d", fd);
	assertf(errno == ENOENT, "%s", strerror(errno));

	/* But an open with the new filename shouldn't */
	assertFileText(dfd, "test2", "F1\n");

	/* Now try to create a second file. */
	fd = openat(dfd, "test", O_WRONLY | O_CREAT | O_EXCL, 0644);
	assertf(fd != -1, "%s", strerror(errno));
	temp = write(fd, "F2\n", 3);
	assertf(temp == 3, "%s", strerror(errno));
	error = close(fd);
	assertf(error == 0, "%s", strerror(errno));

	/* Ensure that both file are still intact */
	assertFileText(dfd, "test2", "F1\n");
	assertFileText(dfd, "test", "F2\n");

	/* At this point, a rename should fail with EEXIST */
	assert(renameat(dfd, "test", dfd, "test2") == -1);
	assertf(errno == EEXIST, "%s", strerror(errno));
	assert(renameat(dfd, "test2", dfd, "test") == -1);
	assertf(errno == EEXIST, "%s", strerror(errno));

	/* Try to delete `test2' and re-attempt the re-name */
	assertf(unlinkat(dfd, "test2", 0) == 0, "%s", strerror(errno));

	/* The "test" file should still be intact */
	assertFileText(dfd, "test", "F2\n");

	/* But the test2 file should no longer exist. */
	fd = openat(dfd, "test2", O_RDONLY);
	assertf(fd == -1, "%d", fd);
	assertf(errno == ENOENT, "%s", strerror(errno));

	/* Now try the rename once again */
	assertf(renameat(dfd, "test", dfd, "test2") == 0, "%s", strerror(errno));

	/* Verify the contents of the "test2" file */
	assertFileText(dfd, "test2", "F2\n");

	/* All right! That worked.
	 * Finally, try to create a new `test' file.
	 * The important part here is that a file of
	 * the same name already existed at one point! */
	fd = openat(dfd, "test", O_WRONLY | O_CREAT | O_EXCL, 0644);
	assertf(fd != -1, "%s", strerror(errno));
	temp = write(fd, "F3\n", 3);
	assertf(temp == 3, "%s", strerror(errno));
	error = close(fd);
	assertf(error == 0, "%s", strerror(errno));

	/* Verify file contents one last time. */
	assertFileText(dfd, "test2", "F2\n");
	assertFileText(dfd, "test", "F3\n");

	/* Also verify that both files can be enumerated with `readdir()' */
	checkTestFiles(path, true);

	/* Finally, delete the two remaining test files. */
	assertf(unlinkat(dfd, "test2", 0) == 0, "%s", strerror(errno));
	assertf(unlinkat(dfd, "test", 0) == 0, "%s", strerror(errno));

	/* And after that, ensure that neither still shows up in `readdir()' */
	checkTestFiles(path, false);

	/* Finally, close our directory handle */
	error = close(dfd);
	assertf(error == 0, "%s", strerror(errno));
}


DEFINE_TEST(fs) {

	ctest_substatf("path: /tmp\n");
	testPath("/tmp");

	if (mkdir("/var", 755) == -1)
		assertf(errno == EEXIST, "%s", strerror(errno));
	ctest_substatf("path: /var\n");
	testPath("/var");

	/* Make sure the kernel doesn't crash if we try to
	 * sync any potential modifications made above. */
	sync();
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FS_C */
