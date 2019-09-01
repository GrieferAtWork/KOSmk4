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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C
#define GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C 1

#include "../api.h"
#include "parts.wchar.process.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:wexecv,hash:0x561e0620]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecv") int
NOTHROW_RPC(LIBCCALL libc_wexecv)(char32_t const *__restrict path,
                                  __TWARGV)
/*[[[body:wexecv]]]*/
{
	CRT_UNIMPLEMENTED("wexecv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecv]]]*/

/*[[[head:DOS$wexecv,hash:0x9238373c]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecv") int
NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path,
                                  __TWARGV)
/*[[[body:DOS$wexecv]]]*/
{
	CRT_UNIMPLEMENTED("wexecv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecv]]]*/

/*[[[head:wexecve,hash:0x6ea16938]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecve") int
NOTHROW_RPC(LIBCCALL libc_wexecve)(char32_t const *__restrict path,
                                   __TWARGV,
                                   __TWENVP)
/*[[[body:wexecve]]]*/
{
	CRT_UNIMPLEMENTED("wexecve"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecve]]]*/

/*[[[head:DOS$wexecve,hash:0x9fd51d7d]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecve") int
NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path,
                                   __TWARGV,
                                   __TWENVP)
/*[[[body:DOS$wexecve]]]*/
{
	CRT_UNIMPLEMENTED("wexecve"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecve]]]*/

/*[[[head:wexecvp,hash:0x34cd8e05]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecvp") int
NOTHROW_RPC(LIBCCALL libc_wexecvp)(char32_t const *__restrict file,
                                   __TWARGV)
/*[[[body:wexecvp]]]*/
{
	CRT_UNIMPLEMENTED("wexecvp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecvp]]]*/

/*[[[head:DOS$wexecvp,hash:0xc47ae4d2]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecvp") int
NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file,
                                   __TWARGV)
/*[[[body:DOS$wexecvp]]]*/
{
	CRT_UNIMPLEMENTED("wexecvp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecvp]]]*/

/*[[[head:wexecvpe,hash:0x3fd7902b]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecvpe") int
NOTHROW_RPC(LIBCCALL libc_wexecvpe)(char32_t const *__restrict file,
                                    __TWARGV,
                                    __TWENVP)
/*[[[body:wexecvpe]]]*/
{
	CRT_UNIMPLEMENTED("wexecvpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecvpe]]]*/

/*[[[head:DOS$wexecvpe,hash:0x54e7a5b9]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecvpe") int
NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file,
                                    __TWARGV,
                                    __TWENVP)
/*[[[body:DOS$wexecvpe]]]*/
{
	CRT_UNIMPLEMENTED("wexecvpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecvpe]]]*/

/*[[[head:wexecl,hash:0xebbf1aa5]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecl") int
NOTHROW_RPC(VLIBCCALL libc_wexecl)(char32_t const *__restrict path,
                                   char32_t const *args,
                                   ... /*, (wchar_t *)NULL*/)
/*[[[body:wexecl]]]*/
{
	CRT_UNIMPLEMENTED("wexecl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecl]]]*/

/*[[[head:DOS$wexecl,hash:0xb49ec86]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecl") int
NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path,
                                   char16_t const *args,
                                   ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wexecl]]]*/
{
	CRT_UNIMPLEMENTED("wexecl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecl]]]*/

/*[[[head:wexecle,hash:0xf18d5dc3]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecle") int
NOTHROW_RPC(VLIBCCALL libc_wexecle)(char32_t const *__restrict path,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wexecle]]]*/
{
	CRT_UNIMPLEMENTED("wexecle"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexecle]]]*/

/*[[[head:DOS$wexecle,hash:0x25907509]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecle") int
NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wexecle]]]*/
{
	CRT_UNIMPLEMENTED("wexecle"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexecle]]]*/

/*[[[head:wexeclp,hash:0x6d37c823]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexeclp") int
NOTHROW_RPC(VLIBCCALL libc_wexeclp)(char32_t const *__restrict file,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:wexeclp]]]*/
{
	CRT_UNIMPLEMENTED("wexeclp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexeclp]]]*/

/*[[[head:DOS$wexeclp,hash:0xe4432dba]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexeclp") int
NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wexeclp]]]*/
{
	CRT_UNIMPLEMENTED("wexeclp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexeclp]]]*/

/*[[[head:wexeclpe,hash:0xb954b42b]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexeclpe") int
NOTHROW_RPC(VLIBCCALL libc_wexeclpe)(char32_t const *__restrict file,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wexeclpe]]]*/
{
	CRT_UNIMPLEMENTED("wexeclpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wexeclpe]]]*/

/*[[[head:DOS$wexeclpe,hash:0xac905d0b]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexeclpe") int
NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wexeclpe]]]*/
{
	CRT_UNIMPLEMENTED("wexeclpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wexeclpe]]]*/

/*[[[head:wspawnv,hash:0x8a0aa1de]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnv") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnv)(int mode,
                                   char32_t const *__restrict path,
                                   __TWARGV)
/*[[[body:wspawnv]]]*/
{
	CRT_UNIMPLEMENTED("wspawnv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnv]]]*/

/*[[[head:DOS$wspawnv,hash:0xba8e46bf]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnv") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnv)(int mode,
                                   char16_t const *__restrict path,
                                   __TWARGV)
/*[[[body:DOS$wspawnv]]]*/
{
	CRT_UNIMPLEMENTED("wspawnv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnv]]]*/

/*[[[head:wspawnve,hash:0xc2a927b5]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnve") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnve)(int mode,
                                    char32_t const *__restrict path,
                                    __TWARGV,
                                    __TWENVP)
/*[[[body:wspawnve]]]*/
{
	CRT_UNIMPLEMENTED("wspawnve"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnve]]]*/

/*[[[head:DOS$wspawnve,hash:0x11373b81]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnve") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnve)(int mode,
                                    char16_t const *__restrict path,
                                    __TWARGV,
                                    __TWENVP)
/*[[[body:DOS$wspawnve]]]*/
{
	CRT_UNIMPLEMENTED("wspawnve"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnve]]]*/

/*[[[head:wspawnvp,hash:0x9f848bf6]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnvp") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnvp)(int mode,
                                    char32_t const *__restrict file,
                                    __TWARGV)
/*[[[body:wspawnvp]]]*/
{
	CRT_UNIMPLEMENTED("wspawnvp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnvp]]]*/

/*[[[head:DOS$wspawnvp,hash:0x33c039b4]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnvp") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvp)(int mode,
                                    char16_t const *__restrict file,
                                    __TWARGV)
/*[[[body:DOS$wspawnvp]]]*/
{
	CRT_UNIMPLEMENTED("wspawnvp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnvp]]]*/

/*[[[head:wspawnvpe,hash:0x44da1f78]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnvpe") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnvpe)(int mode,
                                     char32_t const *__restrict file,
                                     __TWARGV,
                                     __TWENVP)
/*[[[body:wspawnvpe]]]*/
{
	CRT_UNIMPLEMENTED("wspawnvpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnvpe]]]*/

/*[[[head:DOS$wspawnvpe,hash:0x874c4f93]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnvpe") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(int mode,
                                     char16_t const *__restrict file,
                                     __TWARGV,
                                     __TWENVP)
/*[[[body:DOS$wspawnvpe]]]*/
{
	CRT_UNIMPLEMENTED("wspawnvpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnvpe]]]*/

/*[[[head:wspawnl,hash:0xf9918168]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnl") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnl)(int mode,
                                    char32_t const *__restrict path,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:wspawnl]]]*/
{
	CRT_UNIMPLEMENTED("wspawnl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnl]]]*/

/*[[[head:DOS$wspawnl,hash:0xcc481072]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnl") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnl)(int mode,
                                    char16_t const *__restrict path,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wspawnl]]]*/
{
	CRT_UNIMPLEMENTED("wspawnl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnl]]]*/

/*[[[head:wspawnle,hash:0x667f3516]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnle") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnle)(int mode,
                                     char32_t const *__restrict path,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wspawnle]]]*/
{
	CRT_UNIMPLEMENTED("wspawnle"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnle]]]*/

/*[[[head:DOS$wspawnle,hash:0x124847a7]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnle") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnle)(int mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wspawnle]]]*/
{
	CRT_UNIMPLEMENTED("wspawnle"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnle]]]*/

/*[[[head:wspawnlp,hash:0xb20d3fb7]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnlp") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnlp)(int mode,
                                     char32_t const *__restrict file,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL*/)
/*[[[body:wspawnlp]]]*/
{
	CRT_UNIMPLEMENTED("wspawnlp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnlp]]]*/

/*[[[head:DOS$wspawnlp,hash:0x4955fb23]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnlp") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(int mode,
                                     char16_t const *__restrict file,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wspawnlp]]]*/
{
	CRT_UNIMPLEMENTED("wspawnlp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnlp]]]*/

/*[[[head:wspawnlpe,hash:0x8350dccb]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnlpe") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnlpe)(int mode,
                                      char32_t const *__restrict file,
                                      char32_t const *args,
                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wspawnlpe]]]*/
{
	CRT_UNIMPLEMENTED("wspawnlpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wspawnlpe]]]*/

/*[[[head:DOS$wspawnlpe,hash:0x4826df73]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnlpe") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(int mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wspawnlpe]]]*/
{
	CRT_UNIMPLEMENTED("wspawnlpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wspawnlpe]]]*/

/*[[[head:wsystem,hash:0x2c775b19]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.system.wsystem") int
NOTHROW_RPC(LIBCCALL libc_wsystem)(char32_t const *cmd)
/*[[[body:wsystem]]]*/
{
	CRT_UNIMPLEMENTED("wsystem"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wsystem]]]*/

/*[[[head:DOS$wsystem,hash:0x5cd8b1f3]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.system.wsystem") int
NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd)
/*[[[body:DOS$wsystem]]]*/
{
	CRT_UNIMPLEMENTED("wsystem"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wsystem]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x821a6564]]]*/
#undef wexecl
#undef _wexecl
#undef wexecle
#undef _wexecle
#undef wexeclp
#undef _wexeclp
#undef wexeclpe
#undef _wexeclpe
#undef wspawnl
#undef _wspawnl
#undef wspawnle
#undef _wspawnle
#undef wspawnlp
#undef _wspawnlp
#undef wspawnlpe
#undef _wspawnlpe
DEFINE_PUBLIC_WEAK_ALIAS(wexecv, libc_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecv, libc_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecv, libd_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(wexecve, libc_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecve, libc_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecve, libd_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(wexecvp, libc_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecvp, libc_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecvp, libd_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecvpe, libd_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(wexecl, libc_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecl, libc_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecl, libd_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(wexecle, libc_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecle, libc_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecle, libd_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(wexeclp, libc_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(_wexeclp, libc_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexeclp, libd_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecle, libd_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnv, libc_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnv, libc_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnv, libd_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnve, libc_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnve, libc_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnve, libd_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnvp, libd_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnvpe, libd_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnl, libc_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnl, libc_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnl, libd_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnle, libc_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnle, libc_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnle, libd_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnle, libd_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(wsystem, libc_wsystem);
DEFINE_PUBLIC_WEAK_ALIAS(_wsystem, libc_wsystem);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wsystem, libd_wsystem);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C */
