/* HASH CRC-32:0x456e6676 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__searchenv_defined
#ifdef __CRT_HAVE__searchenv_s
#define __local__searchenv_defined 1
/* Dependency: "_searchenv_s" */
#ifndef ____localdep__searchenv_s_defined
#define ____localdep__searchenv_s_defined 1
#ifdef __CRT_HAVE__searchenv_s
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep__searchenv_s,(char const *__file, char const *__envvar, char *__restrict __resultpath, __SIZE_TYPE__ __buflen),_searchenv_s,(__file,__envvar,__resultpath,__buflen))
#else /* LIBC: _searchenv_s */
#undef ____localdep__searchenv_s_defined
#endif /* _searchenv_s... */
#endif /* !____localdep__searchenv_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_searchenv) __ATTR_NONNULL((1, 2, 3)) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_searchenv))(char const *__file,
                                                        char const *__envvar,
                                                        char *__restrict __resultpath) {
#line 2880 "kos/src/libc/magic/stdlib.c"
	__localdep__searchenv_s(__file, __envvar, __resultpath, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__searchenv_s */
#endif /* !__local__searchenv_defined */
