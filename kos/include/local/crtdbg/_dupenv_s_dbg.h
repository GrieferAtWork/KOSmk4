/* HASH CRC-32:0x3cbe2dcf */
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
#ifndef __local__dupenv_s_dbg_defined
#ifdef __CRT_HAVE__dupenv_s
#define __local__dupenv_s_dbg_defined 1
/* Dependency: "_dupenv_s" */
#ifndef ____localdep__dupenv_s_defined
#define ____localdep__dupenv_s_defined 1
#ifdef __CRT_HAVE__dupenv_s
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep__dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),_dupenv_s,(__pbuf,__pbuflen,__varname))
#else /* LIBC: _dupenv_s */
#undef ____localdep__dupenv_s_defined
#endif /* _dupenv_s... */
#endif /* !____localdep__dupenv_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_dupenv_s_dbg) _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_dupenv_s_dbg))(char **__pbuf,
                                                           __SIZE_TYPE__ *__pbufsize,
                                                           char const *__varname,
                                                           int __block_type,
                                                           char const *__filename,
                                                           int __line) {
#line 526 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__dupenv_s(__pbuf, __pbufsize, __varname);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__dupenv_s */
#endif /* !__local__dupenv_s_dbg_defined */
