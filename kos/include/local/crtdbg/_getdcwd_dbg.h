/* HASH CRC-32:0xd75cb7ce */
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
#ifndef __local__getdcwd_dbg_defined
#ifdef __CRT_HAVE__getdcwd
#define __local__getdcwd_dbg_defined 1
/* Dependency: "_getdcwd" */
#ifndef ____localdep__getdcwd_defined
#define ____localdep__getdcwd_defined 1
#ifdef __CRT_HAVE__getdcwd
__CREDIRECT(,char *,__NOTHROW_RPC,__localdep__getdcwd,(int __drive, char *__buf, __SIZE_TYPE__ __size),_getdcwd,(__drive,__buf,__size))
#else /* LIBC: _getdcwd */
#undef ____localdep__getdcwd_defined
#endif /* _getdcwd... */
#endif /* !____localdep__getdcwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getdcwd_dbg) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_getdcwd_dbg))(int __driveno,
                                                          char *__buf,
                                                          __STDC_INT_AS_SIZE_T __bufsize,
                                                          int __block_type,
                                                          char const *__filename,
                                                          int __line) {
#line 497 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__getdcwd(__driveno, __buf, __bufsize);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__getdcwd */
#endif /* !__local__getdcwd_dbg_defined */
