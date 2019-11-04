/* HASH CRC-32:0x4b0d35bd */
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
#ifndef __local__tempnam_dbg_defined
#if defined(__CRT_HAVE_tempnam) || defined(__CRT_HAVE__tempnam)
#define __local__tempnam_dbg_defined 1
/* Dependency: "tempnam" */
#ifndef ____localdep_tempnam_defined
#define ____localdep_tempnam_defined 1
#ifdef __CRT_HAVE_tempnam
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_tempnam,(char const *__dir, char const *__pfx),tempnam,(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_tempnam,(char const *__dir, char const *__pfx),_tempnam,(__dir,__pfx))
#else /* LIBC: tempnam */
#undef ____localdep_tempnam_defined
#endif /* tempnam... */
#endif /* !____localdep_tempnam_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_tempnam_dbg) __ATTR_MALLOC __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_tempnam_dbg))(char const *__dir_name,
                                                          char const *__file_prefix,
                                                          int __block_type,
                                                          char const *__filename,
                                                          int __line) {
#line 430 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep_tempnam(__dir_name, __file_prefix);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_tempnam) || defined(__CRT_HAVE__tempnam) */
#endif /* !__local__tempnam_dbg_defined */
