/* HASH CRC-32:0xc060942d */
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
#ifndef GUARD_LIBC_AUTO_MNTENT_C
#define GUARD_LIBC_AUTO_MNTENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "mntent.h"
#include "../user/ctype.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> endmntent(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_INOUT(1) int
NOTHROW_RPC_NOKOS(LIBCCALL libc_endmntent)(FILE *stream) {
	libc_fclose(stream);
	return 1;
}
#include <bits/crt/db/mntent.h>
#include "../libc/tls-globals.h"
/* >> getmntent(3), getmntent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_INOUT(1) struct mntent *
NOTHROW_CB_NCX(LIBCCALL libc_getmntent)(FILE *stream) {

	void **const _p_getmntent_buf = &libc_get_tlsglobals()->ltg_getmntent_buf;
#define getmntent_buf (*_p_getmntent_buf)
	if (!getmntent_buf &&
	    (getmntent_buf = libc_malloc(sizeof(struct mntent) +
	                            512 * sizeof(char))) == NULL)
		return NULL;
	return libc_getmntent_r(stream, (struct mntent *)getmntent_buf,
	                   (char *)((struct mntent *)getmntent_buf + 1), 512);





}
#undef getmntent_buf
/* >> getmntent(3), getmntent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUTS(3, 4) struct mntent *
NOTHROW_CB_NCX(LIBCCALL libc_getmntent_r)(FILE *__restrict stream,
                                          struct mntent *__restrict result,
                                          char *__restrict buffer,
                                          __STDC_INT_AS_SIZE_T bufsize) {
	char *line;
	do {
		line = libc_fgets(buffer, bufsize, stream);
		if (!line)
			goto err;
		while (*line && libc_isspace(*line))
			++line;
	} while (*line == '#');

	result->mnt_fsname = line;
	while (*line && !libc_isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && libc_isspace(*line))
		++line;

	result->mnt_dir = line;
	while (*line && !libc_isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && libc_isspace(*line))
		++line;

	result->mnt_type = line;
	while (*line && !libc_isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && libc_isspace(*line))
		++line;

	result->mnt_opts = line;
	while (*line && !libc_isspace(*line))
		++line;
	if (!*line)
		goto err;
	*line++ = '\0';
	while (*line && libc_isspace(*line))
		++line;

	result->mnt_freq = 0;
	while (*line && libc_isdigit(*line)) {
		result->mnt_freq *= 10;
		result->mnt_freq += *line - '0';
		++line;
	}
	if (!*line)
		goto err;
	while (*line && libc_isspace(*line))
		++line;

	result->mnt_passno = 0;
	while (*line && libc_isdigit(*line)) {
		result->mnt_passno *= 10;
		result->mnt_passno += *line - '0';
		++line;
	}
	return result;
err:
	return NULL;
}
/* >> addmntent(3)
 * Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_CB_NCX(LIBCCALL libc_addmntent)(FILE *__restrict stream,
                                        struct mntent const *__restrict mnt) {
	if unlikely(!mnt ||
	            !mnt->mnt_fsname || !mnt->mnt_dir ||
	            !mnt->mnt_type || !mnt->mnt_opts)
		return 1;
	if (libc_fseek(stream, 0, __SEEK_END) < 0)
		return 1;
	libc_fprintf(stream, "%s %s %s %s %d %d\n",
	        mnt->mnt_fsname,
	        mnt->mnt_dir,
	        mnt->mnt_type,
	        mnt->mnt_opts,
	        mnt->mnt_freq,
	        mnt->mnt_passno);
	return 0;
}
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char *
NOTHROW_NCX(LIBCCALL libc_hasmntopt)(struct mntent const *mnt,
                                     char const *opt) {
	char *str;
	if likely(mnt && opt && (str = mnt->mnt_opts) != NULL) {
		size_t optlen = libc_strlen(opt);
		while (*str) {
			if (libc_bcmpc(str, opt, optlen, sizeof(char)) == 0 &&
			    (str[optlen] == ',' || str[optlen] == '\0'))
				return str;
			str = libc_strchrnul(str, ',');
		}
	}
	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__endmntent,libc_endmntent,ATTR_INOUT(1),int,NOTHROW_RPC_NOKOS,LIBCCALL,(FILE *stream),(stream));
DEFINE_PUBLIC_ALIAS_P(endmntent,libc_endmntent,ATTR_INOUT(1),int,NOTHROW_RPC_NOKOS,LIBCCALL,(FILE *stream),(stream));
DEFINE_PUBLIC_ALIAS_P(getmntent,libc_getmntent,ATTR_INOUT(1),struct mntent *,NOTHROW_CB_NCX,LIBCCALL,(FILE *stream),(stream));
DEFINE_PUBLIC_ALIAS_P(__getmntent_r,libc_getmntent_r,ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUTS(3, 4),struct mntent *,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize),(stream,result,buffer,bufsize));
DEFINE_PUBLIC_ALIAS_P(getmntent_r,libc_getmntent_r,ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUTS(3, 4),struct mntent *,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize),(stream,result,buffer,bufsize));
DEFINE_PUBLIC_ALIAS_P(__addmntent,libc_addmntent,ATTR_IN(2) ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, struct mntent const *__restrict mnt),(stream,mnt));
DEFINE_PUBLIC_ALIAS_P(addmntent,libc_addmntent,ATTR_IN(2) ATTR_INOUT(1),int,NOTHROW_CB_NCX,LIBCCALL,(FILE *__restrict stream, struct mntent const *__restrict mnt),(stream,mnt));
DEFINE_PUBLIC_ALIAS_P(__hasmntopt,libc_hasmntopt,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2),char *,NOTHROW_NCX,LIBCCALL,(struct mntent const *mnt, char const *opt),(mnt,opt));
DEFINE_PUBLIC_ALIAS_P(hasmntopt,libc_hasmntopt,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2),char *,NOTHROW_NCX,LIBCCALL,(struct mntent const *mnt, char const *opt),(mnt,opt));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MNTENT_C */
