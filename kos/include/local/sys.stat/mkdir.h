/* HASH CRC-32:0x8f50a229 */
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
#ifndef __local_mkdir_defined
#if defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
#define __local_mkdir_defined 1
/* Dependency: "dos_mkdir" from "sys.stat" */
#ifndef ____localdep_dos_mkdir_defined
#define ____localdep_dos_mkdir_defined 1
#ifdef __CRT_HAVE__mkdir
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_dos_mkdir,(char const *__pathname),_mkdir,(__pathname))
#else /* LIBC: _mkdir */
#undef ____localdep_dos_mkdir_defined
#endif /* dos_mkdir... */
#endif /* !____localdep_dos_mkdir_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mkdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkdir))(char const *__pathname,
                                                   __mode_t __mode) {
#line 466 "kos/src/libc/magic/sys.stat.c"
	(void)__mode;
	return __localdep_dos_mkdir(__pathname);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_DOS_PRIMARY && __CRT_HAVE__mkdir */
#endif /* !__local_mkdir_defined */
