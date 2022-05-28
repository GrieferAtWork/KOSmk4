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
#ifndef GUARD_LIBC_USER_FTS_C
#define GUARD_LIBC_USER_FTS_C 1

#include "../api.h"
/**/

#include "fts.h"

DECL_BEGIN

/*[[[head:libc_fts_children,hash:CRC-32=0x9e7c2a17]]]*/
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_INOUT(1) FTSENT *
NOTHROW_RPC(LIBCCALL libc_fts_children)(FTS *ftsp,
                                        __STDC_INT_AS_UINT_T instr)
/*[[[body:libc_fts_children]]]*/
/*AUTO*/{
	(void)ftsp;
	(void)instr;
	CRT_UNIMPLEMENTEDF("fts_children(%p, %x)", ftsp, instr); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fts_children]]]*/

/*[[[head:libc_fts_close,hash:CRC-32=0xed046568]]]*/
/* >> fts_close(3), fts_close64(3) */
INTERN ATTR_SECTION(".text.crt.fs.fts") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_fts_close)(FTS *ftsp)
/*[[[body:libc_fts_close]]]*/
/*AUTO*/{
	(void)ftsp;
	CRT_UNIMPLEMENTEDF("fts_close(%p)", ftsp); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fts_close]]]*/

/*[[[head:libc_fts_open,hash:CRC-32=0xf31150]]]*/
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_IN(1) FTS *
NOTHROW_RPC(LIBCCALL libc_fts_open)(char *const *path_argv,
                                    __STDC_INT_AS_UINT_T options,
                                    int (LIBKCALL *compar)(FTSENT const **lhs, FTSENT const **rhs))
/*[[[body:libc_fts_open]]]*/
/*AUTO*/{
	(void)path_argv;
	(void)options;
	(void)compar;
	CRT_UNIMPLEMENTEDF("fts_open(%p, %x, %p)", path_argv, options, compar); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fts_open]]]*/

/*[[[head:libc_fts_read,hash:CRC-32=0xe1d5d796]]]*/
/* >> fts_read(3), fts_read64(3) */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_INOUT(1) FTSENT *
NOTHROW_RPC(LIBCCALL libc_fts_read)(FTS *ftsp)
/*[[[body:libc_fts_read]]]*/
/*AUTO*/{
	(void)ftsp;
	CRT_UNIMPLEMENTEDF("fts_read(%p)", ftsp); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fts_read]]]*/

/*[[[head:libc_fts_set,hash:CRC-32=0x286ee668]]]*/
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") ATTR_INOUT(1) ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_fts_set)(FTS *ftsp,
                                   FTSENT *f,
                                   __STDC_INT_AS_UINT_T instr)
/*[[[body:libc_fts_set]]]*/
/*AUTO*/{
	(void)ftsp;
	(void)f;
	(void)instr;
	CRT_UNIMPLEMENTEDF("fts_set(%p, %p, %x)", ftsp, f, instr); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fts_set]]]*/

/*[[[head:libc_fts64_children,hash:CRC-32=0x578c7996]]]*/
#ifdef __FTS32_MATCHES_FTS64
DEFINE_INTERN_ALIAS(libc_fts64_children, libc_fts_children);
#else /* MAGIC:alias */
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_INOUT(1) FTSENT64 *
NOTHROW_RPC(LIBCCALL libc_fts64_children)(FTS64 *ftsp,
                                          __STDC_INT_AS_UINT_T instr)
/*[[[body:libc_fts64_children]]]*/
/*AUTO*/{
	(void)ftsp;
	(void)instr;
	CRT_UNIMPLEMENTEDF("fts64_children(%p, %x)", ftsp, instr); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fts64_children]]]*/

/*[[[head:libc_fts64_close,hash:CRC-32=0x9833099d]]]*/
#ifdef __FTS32_MATCHES_FTS64
DEFINE_INTERN_ALIAS(libc_fts64_close, libc_fts_close);
#else /* MAGIC:alias */
/* >> fts_close(3), fts_close64(3) */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_INOUT(1) int
NOTHROW_RPC(LIBCCALL libc_fts64_close)(FTS64 *ftsp)
/*[[[body:libc_fts64_close]]]*/
/*AUTO*/{
	(void)ftsp;
	CRT_UNIMPLEMENTEDF("fts64_close(%p)", ftsp); /* TODO */
	return libc_seterrno(ENOSYS);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fts64_close]]]*/

/*[[[head:libc_fts64_open,hash:CRC-32=0xc72e162b]]]*/
#ifdef __FTS32_MATCHES_FTS64
DEFINE_INTERN_ALIAS(libc_fts64_open, libc_fts_open);
#else /* MAGIC:alias */
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_IN(1) FTS64 *
NOTHROW_RPC(LIBCCALL libc_fts64_open)(char *const *path_argv,
                                      __STDC_INT_AS_UINT_T options,
                                      int (LIBKCALL *compar)(FTSENT64 const **lhs, FTSENT64 const **rhs))
/*[[[body:libc_fts64_open]]]*/
/*AUTO*/{
	(void)path_argv;
	(void)options;
	(void)compar;
	CRT_UNIMPLEMENTEDF("fts64_open(%p, %x, %p)", path_argv, options, compar); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fts64_open]]]*/

/*[[[head:libc_fts64_read,hash:CRC-32=0xff9cae9d]]]*/
#ifdef __FTS32_MATCHES_FTS64
DEFINE_INTERN_ALIAS(libc_fts64_read, libc_fts_read);
#else /* MAGIC:alias */
/* >> fts_read(3), fts_read64(3) */
INTERN ATTR_SECTION(".text.crt.fs.fts") WUNUSED ATTR_INOUT(1) FTSENT64 *
NOTHROW_RPC(LIBCCALL libc_fts64_read)(FTS64 *ftsp)
/*[[[body:libc_fts64_read]]]*/
/*AUTO*/{
	(void)ftsp;
	CRT_UNIMPLEMENTEDF("fts64_read(%p)", ftsp); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fts64_read]]]*/

/*[[[head:libc_fts64_set,hash:CRC-32=0x57d7047c]]]*/
#ifdef __FTS32_MATCHES_FTS64
DEFINE_INTERN_ALIAS(libc_fts64_set, libc_fts_set);
#else /* MAGIC:alias */
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTERN ATTR_SECTION(".text.crt.fs.fts") ATTR_INOUT(1) ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_fts64_set)(FTS64 *ftsp,
                                     FTSENT64 *f,
                                     __STDC_INT_AS_UINT_T instr)
/*[[[body:libc_fts64_set]]]*/
/*AUTO*/{
	(void)ftsp;
	(void)f;
	(void)instr;
	CRT_UNIMPLEMENTEDF("fts64_set(%p, %p, %x)", ftsp, f, instr); /* TODO */
	return libc_seterrno(ENOSYS);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fts64_set]]]*/

/*[[[start:exports,hash:CRC-32=0x255e42a]]]*/
DEFINE_PUBLIC_ALIAS(fts_children, libc_fts_children);
DEFINE_PUBLIC_ALIAS(fts_close, libc_fts_close);
DEFINE_PUBLIC_ALIAS(fts_open, libc_fts_open);
DEFINE_PUBLIC_ALIAS(fts_read, libc_fts_read);
DEFINE_PUBLIC_ALIAS(fts_set, libc_fts_set);
DEFINE_PUBLIC_ALIAS(fts64_children, libc_fts64_children);
DEFINE_PUBLIC_ALIAS(fts64_close, libc_fts64_close);
DEFINE_PUBLIC_ALIAS(fts64_open, libc_fts64_open);
DEFINE_PUBLIC_ALIAS(fts64_read, libc_fts64_read);
DEFINE_PUBLIC_ALIAS(fts64_set, libc_fts64_set);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FTS_C */
