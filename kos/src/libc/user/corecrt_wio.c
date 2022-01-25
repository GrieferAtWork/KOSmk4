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
#ifndef GUARD_LIBC_USER_CORECRT_WIO_C
#define GUARD_LIBC_USER_CORECRT_WIO_C 1

#include "../api.h"
/**/

#include "corecrt_wio.h"

DECL_BEGIN

/*[[[head:libd__wmktemp_s,hash:CRC-32=0x651c7a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__wmktemp_s)(char16_t *template_,
                                      size_t bufsize)
/*[[[body:libd__wmktemp_s]]]*/
/*AUTO*/{
	(void)template_;
	(void)bufsize;
	CRT_UNIMPLEMENTEDF("DOS$_wmktemp_s(%p, %Ix)", template_, bufsize); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wmktemp_s]]]*/

/*[[[head:libc__wmktemp_s,hash:CRC-32=0x19ad0c21]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc__wmktemp_s)(char32_t *template_,
                                      size_t bufsize)
/*[[[body:libc__wmktemp_s]]]*/
/*AUTO*/{
	(void)template_;
	(void)bufsize;
	CRT_UNIMPLEMENTEDF("_wmktemp_s(%p, %Ix)", template_, bufsize); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wmktemp_s]]]*/

/*[[[head:libd__wmktemp,hash:CRC-32=0x48a0582d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd__wmktemp)(char16_t *template_)
/*[[[body:libd__wmktemp]]]*/
/*AUTO*/{
	(void)template_;
	CRT_UNIMPLEMENTEDF("DOS$_wmktemp(%p)", template_); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wmktemp]]]*/

/*[[[head:libc__wmktemp,hash:CRC-32=0x4c022051]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc__wmktemp)(char32_t *template_)
/*[[[body:libc__wmktemp]]]*/
/*AUTO*/{
	(void)template_;
	CRT_UNIMPLEMENTEDF("_wmktemp(%p)", template_); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wmktemp]]]*/

/*[[[head:libd__wfindfirst32,hash:CRC-32=0xbe38039b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst32)(char16_t const *__restrict filename,
                                         struct _wfinddata32_t *__restrict finddata)
/*[[[body:libd__wfindfirst32]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindfirst32(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindfirst32]]]*/

/*[[[head:libc__wfindfirst32,hash:CRC-32=0xb29a3674]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst32)(char32_t const *__restrict filename,
                                         struct _wfinddata32_t *__restrict finddata)
/*[[[body:libc__wfindfirst32]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindfirst32(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindfirst32]]]*/

/*[[[head:libd__wfindfirst32i64,hash:CRC-32=0x566f5379]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst32i64)(char16_t const *__restrict filename,
                                            struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libd__wfindfirst32i64]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindfirst32i64(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindfirst32i64]]]*/

/*[[[head:libc__wfindfirst32i64,hash:CRC-32=0x3cac6a35]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst32i64)(char32_t const *__restrict filename,
                                            struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libc__wfindfirst32i64]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindfirst32i64(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindfirst32i64]]]*/

/*[[[head:libd__wfindfirst64,hash:CRC-32=0xf7f9b67c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__wfindfirst64)(char16_t const *__restrict filename,
                                         struct _wfinddata64_t *__restrict finddata)
/*[[[body:libd__wfindfirst64]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindfirst64(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindfirst64]]]*/

/*[[[head:libc__wfindfirst64,hash:CRC-32=0xfb5b8393]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBKCALL libc__wfindfirst64)(char32_t const *__restrict filename,
                                         struct _wfinddata64_t *__restrict finddata)
/*[[[body:libc__wfindfirst64]]]*/
/*AUTO*/{
	(void)filename;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindfirst64(%p, %p)", filename, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindfirst64]]]*/

/*[[[head:libd__wfindnext32,hash:CRC-32=0x7095abfd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__wfindnext32)(intptr_t findfd,
                                        struct _wfinddata32_t *__restrict finddata)
/*[[[body:libd__wfindnext32]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindnext32(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindnext32]]]*/

/*[[[head:libc__wfindnext32,hash:CRC-32=0x4cd8960]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc__wfindnext32)(intptr_t findfd,
                                        struct _wfinddata32_t *__restrict finddata)
/*[[[body:libc__wfindnext32]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindnext32(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindnext32]]]*/

/*[[[head:libd__wfindnext32i64,hash:CRC-32=0xac54bc09]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__wfindnext32i64)(intptr_t findfd,
                                           struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libd__wfindnext32i64]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindnext32i64(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindnext32i64]]]*/

/*[[[head:libc__wfindnext32i64,hash:CRC-32=0xac54944c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc__wfindnext32i64)(intptr_t findfd,
                                           struct _wfinddata32i64_t *__restrict finddata)
/*[[[body:libc__wfindnext32i64]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindnext32i64(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindnext32i64]]]*/

/*[[[head:libd__wfindnext64,hash:CRC-32=0x798928b5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__wfindnext64)(intptr_t findfd,
                                        struct _wfinddata64_t *__restrict finddata)
/*[[[body:libd__wfindnext64]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("DOS$_wfindnext64(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wfindnext64]]]*/

/*[[[head:libc__wfindnext64,hash:CRC-32=0xdd10a28]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc__wfindnext64)(intptr_t findfd,
                                        struct _wfinddata64_t *__restrict finddata)
/*[[[body:libc__wfindnext64]]]*/
/*AUTO*/{
	(void)findfd;
	(void)finddata;
	CRT_UNIMPLEMENTEDF("_wfindnext64(%p, %p)", findfd, finddata); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wfindnext64]]]*/

/*[[[start:exports,hash:CRC-32=0x448ef099]]]*/
DEFINE_PUBLIC_ALIAS(DOS$_wmktemp_s, libd__wmktemp_s);
DEFINE_PUBLIC_ALIAS(_wmktemp_s, libc__wmktemp_s);
DEFINE_PUBLIC_ALIAS(DOS$_wmktemp, libd__wmktemp);
DEFINE_PUBLIC_ALIAS(_wmktemp, libc__wmktemp);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirst, libd__wfindfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirst32, libd__wfindfirst32);
DEFINE_PUBLIC_ALIAS(_wfindfirst, libc__wfindfirst32);
DEFINE_PUBLIC_ALIAS(_wfindfirst32, libc__wfindfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirsti64, libd__wfindfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirst32i64, libd__wfindfirst32i64);
DEFINE_PUBLIC_ALIAS(_wfindfirsti64, libc__wfindfirst32i64);
DEFINE_PUBLIC_ALIAS(_wfindfirst32i64, libc__wfindfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirst64i32, libd__wfindfirst64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindfirst64, libd__wfindfirst64);
DEFINE_PUBLIC_ALIAS(_wfindfirst64i32, libc__wfindfirst64);
DEFINE_PUBLIC_ALIAS(_wfindfirst64, libc__wfindfirst64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnext, libd__wfindnext32);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnext32, libd__wfindnext32);
DEFINE_PUBLIC_ALIAS(_wfindnext, libc__wfindnext32);
DEFINE_PUBLIC_ALIAS(_wfindnext32, libc__wfindnext32);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnexti64, libd__wfindnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnext32i64, libd__wfindnext32i64);
DEFINE_PUBLIC_ALIAS(_wfindnexti64, libc__wfindnext32i64);
DEFINE_PUBLIC_ALIAS(_wfindnext32i64, libc__wfindnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnext64i32, libd__wfindnext64);
DEFINE_PUBLIC_ALIAS(DOS$_wfindnext64, libd__wfindnext64);
DEFINE_PUBLIC_ALIAS(_wfindnext64i32, libc__wfindnext64);
DEFINE_PUBLIC_ALIAS(_wfindnext64, libc__wfindnext64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WIO_C */
