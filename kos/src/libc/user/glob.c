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
#ifndef GUARD_LIBC_USER_GLOB_C
#define GUARD_LIBC_USER_GLOB_C 1

#include "../api.h"
#include "glob.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_glob,hash:CRC-32=0xaa9e134f]]]*/
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
INTERN ATTR_SECTION(".text.crt.utility.glob") NONNULL((1, 4)) int
NOTHROW_NCX(LIBCCALL libc_glob)(char const *__restrict pattern,
                                int flags,
                                __glob_errfunc_t errfunc,
                                glob_t *__restrict pglob)
/*[[[body:libc_glob]]]*/
{
	(void)pattern;
	(void)flags;
	(void)errfunc;
	(void)pglob;
	COMPILER_IMPURE();
	/* TODO */
	return GLOB_NOSYS;
}
/*[[[end:libc_glob]]]*/

/*[[[head:libc_globfree,hash:CRC-32=0xe8b659c9]]]*/
/* Free storage allocated in PGLOB by a previous `glob' call */
INTERN ATTR_SECTION(".text.crt.utility.glob") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_globfree)(glob_t *pglob)
/*[[[body:libc_globfree]]]*/
{
	(void)pglob;
	CRT_UNIMPLEMENTED("globfree"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_globfree]]]*/

/*[[[head:libc_glob64,hash:CRC-32=0x3dac10fb]]]*/
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
INTERN ATTR_SECTION(".text.crt.utility.glob") NONNULL((1, 4)) int
NOTHROW_NCX(LIBCCALL libc_glob64)(const char *__restrict pattern,
                                  int flags,
                                  __glob_errfunc_t errfunc,
                                  struct __glob64_struct *__restrict pglob)
/*[[[body:libc_glob64]]]*/
{
	(void)pattern;
	(void)flags;
	(void)errfunc;
	(void)pglob;
	COMPILER_IMPURE();
	/* TODO */
	return GLOB_NOSYS;
}
/*[[[end:libc_glob64]]]*/

/*[[[head:libc_globfree64,hash:CRC-32=0x25fe68c5]]]*/
/* Free storage allocated in PGLOB by a previous `glob' call */
INTERN ATTR_SECTION(".text.crt.utility.glob") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_globfree64)(struct __glob64_struct *pglob)
/*[[[body:libc_globfree64]]]*/
{
	(void)pglob;
	CRT_UNIMPLEMENTED("globfree64"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_globfree64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x3798dee4]]]*/
DEFINE_PUBLIC_ALIAS(glob, libc_glob);
DEFINE_PUBLIC_ALIAS(globfree, libc_globfree);
DEFINE_PUBLIC_ALIAS(glob64, libc_glob64);
DEFINE_PUBLIC_ALIAS(globfree64, libc_globfree64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_GLOB_C */
