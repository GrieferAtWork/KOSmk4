/* HASH CRC-32:0x97e520fd */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_LIBGEN_C
#define GUARD_LIBC_AUTO_LIBGEN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "libgen.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Return directory part of PATH or "." if none is available */
INTERN ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.dirname") char *
NOTHROW_NCX(LIBCCALL libc_dirname)(char *path) {
#line 33 "kos/src/libc/magic/libgen.c"
	/* NOTE: This implementation is taken form GLibc */
	/* dirname - return directory part of PATH.
	   Copyright (C) 1996-2017 Free Software Foundation, Inc.
	   This file is part of the GNU C Library.
	   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.
	
	   The GNU C Library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.
	
	   The GNU C Library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.
	
	   You should have received a copy of the GNU Lesser General Public
	   License along with the GNU C Library; if not, see
	   <http://www.gnu.org/licenses/>.  */
	char *last_slash;
	last_slash = path ? libc_strrchr(path, '/') : NULL;
	if (last_slash && last_slash != path && last_slash[1] == '\0') {
		char *runp;
		for (runp = last_slash; runp != path; --runp) {
			if (runp[-1] != '/')
				break;
		}
		if (runp != path)
			last_slash = (char *)libc_memrchr(path, '/', (size_t)(runp - path));
	}
	if (last_slash) {
		char *runp;
		for (runp = last_slash; runp != path; --runp) {
			if (runp[-1] != '/')
				break;
		}
		if (runp == path) {
			if (last_slash == path + 1)
				++last_slash;
			else {
				last_slash = path + 1;
			}
		} else {
			last_slash = runp;
		}
		last_slash[0] = '\0';
	} else {
		path = (char *)".";
	}
	return path;
}

/* Return final component of PATH.
 * This is the weird XPG version of this function. It sometimes will
 * modify its argument. Therefore we normally use the GNU version (in
 * <string.h>) and only if this header is included make the XPG
 * version available under the real name */
INTERN ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.__xpg_basename") char *
NOTHROW_NCX(LIBCCALL libc___xpg_basename)(char *filename) {
#line 91 "kos/src/libc/magic/libgen.c"
	/* NOTE: This implementation is taken form GLibc */
	/* Return basename of given pathname according to the weird XPG specification.
	   Copyright (C) 1997-2017 Free Software Foundation, Inc.
	   This file is part of the GNU C Library.
	   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.
	
	   The GNU C Library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.
	
	   The GNU C Library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.
	
	   You should have received a copy of the GNU Lesser General Public
	   License along with the GNU C Library; if not, see
	   <http://www.gnu.org/licenses/>.  */
	char *result;
	if (!filename || !filename[0])
		result = (char *)".";
	else {
		result = libc_strrchr(filename, '/');
		if (!result)
			result = filename;
		else if (!result[1]) {
			while (result > filename && result[-1] == '/')
				--result;
			if (result > filename) {
				*result-- = '\0';
				while (result > filename && result[-1] != '/')
					--result;
			} else {
				while (result[1] != '\0')
					++result;
			}
		} else {
			++result;
		}
	}
	return result;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(dirname, libc_dirname);
DEFINE_PUBLIC_WEAK_ALIAS(__xpg_basename, libc___xpg_basename);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBGEN_C */
