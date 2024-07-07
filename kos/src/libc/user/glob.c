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
#ifndef GUARD_LIBC_USER_GLOB_C
#define GUARD_LIBC_USER_GLOB_C 1

#include "../api.h"
#include "glob.h"

DECL_BEGIN

/*[[[head:libc_glob,hash:CRC-32=0x615d184b]]]*/
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
INTERN ATTR_SECTION(".text.crt.utility.glob") ATTR_IN(1) ATTR_OUT(4) int
NOTHROW_NCX(LIBCCALL libc_glob)(char const *__restrict pattern,
                                __STDC_INT_AS_UINT_T flags,
                                int (LIBKCALL *errfunc)(char const *path, int flags),
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

/*[[[head:libc_globfree,hash:CRC-32=0x4d4ba756]]]*/
/* >> globfree(3), globfree64(3) */
INTERN ATTR_SECTION(".text.crt.utility.glob") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_globfree)(glob_t *pglob)
/*[[[body:libc_globfree]]]*/
{
	(void)pglob;
	CRT_UNIMPLEMENTED("globfree"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_globfree]]]*/

/*[[[head:libc_glob64,hash:CRC-32=0x8bc0a868]]]*/
#ifdef __GLOB32_MATCHES_GLOB64
DEFINE_INTERN_ALIAS(libc_glob64, libc_glob);
#else /* MAGIC:alias */
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
INTERN ATTR_SECTION(".text.crt.utility.glob") ATTR_IN(1) ATTR_OUT(4) int
NOTHROW_NCX(LIBCCALL libc_glob64)(const char *__restrict pattern,
                                  __STDC_INT_AS_UINT_T flags,
                                  int (LIBKCALL *errfunc)(char const *path, int flags),
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
#endif /* MAGIC:alias */
/*[[[end:libc_glob64]]]*/

/*[[[head:libc_globfree64,hash:CRC-32=0x68408de3]]]*/
#ifdef __GLOB32_MATCHES_GLOB64
DEFINE_INTERN_ALIAS(libc_globfree64, libc_globfree);
#else /* MAGIC:alias */
/* >> globfree(3), globfree64(3) */
INTERN ATTR_SECTION(".text.crt.utility.glob") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_globfree64)(struct __glob64_struct *pglob)
/*[[[body:libc_globfree64]]]*/
{
	(void)pglob;
	CRT_UNIMPLEMENTED("globfree64"); /* TODO */
	libc_seterrno(ENOSYS);
}
#endif /* MAGIC:alias */
/*[[[end:libc_globfree64]]]*/





/*[[[start:exports,hash:CRC-32=0x97adf6a6]]]*/
DEFINE_PUBLIC_ALIAS_P(glob,libc_glob,ATTR_IN(1) ATTR_OUT(4),int,NOTHROW_NCX,LIBCCALL,(char const *__restrict pattern, __STDC_INT_AS_UINT_T flags, int (LIBKCALL *errfunc)(char const *path, int flags), glob_t *__restrict pglob),(pattern,flags,errfunc,pglob));
DEFINE_PUBLIC_ALIAS_P_VOID(globfree,libc_globfree,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(glob_t *pglob),(pglob));
DEFINE_PUBLIC_ALIAS_P(glob64,libc_glob64,ATTR_IN(1) ATTR_OUT(4),int,NOTHROW_NCX,LIBCCALL,(const char *__restrict pattern, __STDC_INT_AS_UINT_T flags, int (LIBKCALL *errfunc)(char const *path, int flags), struct __glob64_struct *__restrict pglob),(pattern,flags,errfunc,pglob));
DEFINE_PUBLIC_ALIAS_P_VOID(globfree64,libc_globfree64,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(struct __glob64_struct *pglob),(pglob));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_GLOB_C */
