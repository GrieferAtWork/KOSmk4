/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mntent.h) */
/* (#) Portability: DJGPP         (/include/mntent.h) */
/* (#) Portability: GNU C Library (/misc/mntent.h) */
/* (#) Portability: GNU Hurd      (/usr/include/mntent.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/mntent.h) */
/* (#) Portability: diet libc     (/include/mntent.h) */
/* (#) Portability: libc4/5       (/include/mntent.h) */
/* (#) Portability: libc6         (/include/mntent.h) */
/* (#) Portability: mintlib       (/include/mntent.h) */
/* (#) Portability: musl libc     (/include/mntent.h) */
/* (#) Portability: uClibc        (/include/mntent.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.mntent")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <paths.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <bits/crt/db/mntent.h>
)]%{


/* Filename for the mounting-point table (/etc/fstab) */
#define MNTTAB _PATH_MNTTAB /* Deprecated alias. */

/* Filename for currently mounted filesystems (/proc/self/mounts) */
#define MOUNTED _PATH_MOUNTED /* Deprecated alias. */

/* Some filesystem type names. */
#define MNTTYPE_IGNORE "ignore" /* Ignore this entry. */
#define MNTTYPE_NFS    "nfs"    /* Network file system. */
#define MNTTYPE_SWAP   "swap"   /* Swap device. */

/* Some filesystem mount options. */
#define MNTOPT_DEFAULTS "defaults" /* Default options */
#define MNTOPT_RO       "ro"       /* Read-only file access.            (s.a. `ST_RDONLY') */
#define MNTOPT_RW       "rw"       /* Read/write file access.           (s.a. `ST_RDONLY') */
#define MNTOPT_SUID     "suid"     /* Allow `S_ISUID' and `S_ISGID'.    (s.a. `ST_NOSUID') */
#define MNTOPT_NOSUID   "nosuid"   /* Disallow `S_ISUID' and `S_ISGID'. (s.a. `ST_NOSUID') */
#define MNTOPT_NOAUTO   "noauto"   /* Don't auto-mount.                 (s.a. `mount -a') */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

}


@@>> setmntent(3)
[[cp, nocrt, wunused]]
[[alias("setmntent", "__setmntent", "fopen", "_IO_fopen", "fopen64")]]
$FILE *setmntent([[in]] char const *file,
                 [[in]] char const *mode);

@@>> endmntent(3)
[[cp_nokos, requires_function(fclose)]]
[[export_alias("__endmntent")]]
int endmntent([[inout]] $FILE *stream) {
	fclose(stream);
	return 1;
}

@@>> getmntent(3), getmntent_r(3)
[[cp_stdio, decl_include("<bits/crt/db/mntent.h>")]]
[[impl_include("<bits/crt/db/mntent.h>")]]
[[requires_function(getmntent_r)]]
struct mntent *getmntent([[inout]] $FILE *stream) {
@@pp_if $has_function(malloc)@@
	@@static void *getmntent_buf = NULL; [fini: free(getmntent_buf)]@@
	if (!getmntent_buf &&
	    (getmntent_buf = malloc(sizeof(struct mntent) +
	                            512 * sizeof(char))) == NULL)
		return NULL;
	return getmntent_r(stream, (struct mntent *)getmntent_buf,
	                   (char *)((struct mntent *)getmntent_buf + 1), 512);
@@pp_else@@
	static struct mntent ent[1];
	static char buf[512];
	return getmntent_r(stream, ent, buf, 512);
@@pp_endif@@
}

%
%#ifdef __USE_MISC
[[decl_include("<features.h>", "<bits/crt/db/mntent.h>")]]
[[cp_stdio, doc_alias("getmntent"), export_alias("__getmntent_r")]]
[[requires_function(fgets)]]
struct mntent *getmntent_r([[inout]] $FILE *__restrict stream,
                           [[out]] struct mntent *__restrict result,
                           [[out(? <= bufsize)]] char *__restrict buffer,
                           __STDC_INT_AS_SIZE_T bufsize) {
	char *line;
	do {
		line = fgets(buffer, bufsize, stream);
		if (!line)
			goto err;
		while (*line && isspace(*line))
			++line;
	} while (*line == '#');

	result->@mnt_fsname@ = line;
	while (*line && !isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && isspace(*line))
		++line;

	result->@mnt_dir@ = line;
	while (*line && !isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && isspace(*line))
		++line;

	result->@mnt_type@ = line;
	while (*line && !isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && isspace(*line))
		++line;

	result->@mnt_opts@ = line;
	while (*line && !isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && isspace(*line))
		++line;

	result->@mnt_freq@ = 0;
	while (*line && isdigit(*line)) {
		result->@mnt_freq@ *= 10;
		result->@mnt_freq@ += *line - '0';
		++line;
	}
	if (!*line)
		goto err;
	while (*line && isspace(*line))
		++line;

	result->@mnt_passno@ = 0;
	while (*line && isdigit(*line)) {
		result->@mnt_passno@ *= 10;
		result->@mnt_passno@ += *line - '0';
		++line;
	}
	return result;
err:
	return NULL;
}
%#endif /* __USE_MISC */
%


@@>> addmntent(3)
@@Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
@@mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
@@@return: 0: Success
@@@return: 1: Error (WARNING: `errno' is left undefined)
[[cp_stdio, decl_include("<bits/crt/db/mntent.h>")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires(defined(__SEEK_END) && $has_function(fseek) && $has_function(fprintf))]]
[[export_as("__addmntent")]] /* From Glibc 2.0.4 */
int addmntent([[inout]] $FILE *__restrict stream,
              [[in]] struct mntent const *__restrict mnt) {
	if unlikely(!mnt ||
	            !mnt->@mnt_fsname@ || !mnt->@mnt_dir@ ||
	            !mnt->@mnt_type@ || !mnt->@mnt_opts@)
		return 1;
	if (fseek(stream, 0, @__SEEK_END@) < 0)
		return 1;
	fprintf(stream, "%s %s %s %s %d %d\n",
	        mnt->@mnt_fsname@,
	        mnt->@mnt_dir@,
	        mnt->@mnt_type@,
	        mnt->@mnt_opts@,
	        mnt->@mnt_freq@,
	        mnt->@mnt_passno@);
	return 0;
}

@@>> hasmntopt(3)
@@Check if `mnt->mnt_opts' contains an option matching `opt'.
@@@return: * :   Address of the `opt'-string in `mnt->mnt_opts'
@@@return: NULL: No option `opt' found in `mnt->mnt_opts'
[[pure, wunused, decl_include("<bits/crt/db/mntent.h>")]]
[[export_as("__hasmntopt")]] /* From Glibc 2.0.4 */
char *hasmntopt([[in_opt]] struct mntent const *mnt,
                [[in_opt]] char const *opt) {
	char *str;
	if likely(mnt && opt && (str = mnt->@mnt_opts@) != NULL) {
		size_t optlen = strlen(opt);
		while (*str) {
			if (bcmpc(str, opt, optlen, sizeof(char)) == 0 &&
			    (str[optlen] == ',' || str[optlen] == '\0'))
				return str;
			str = strchrnul(str, ',');
		}
	}
	return NULL;
}



%{

__SYSDECL_END
#endif /* __CC__ */

}
