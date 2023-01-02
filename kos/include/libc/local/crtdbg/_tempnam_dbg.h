/* HASH CRC-32:0x84a597e */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__tempnam_dbg_defined
#define __local__tempnam_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE_tempnam) || defined(__CRT_HAVE__tempnam)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tempnam_defined
#define __local___localdep_tempnam_defined
#ifdef __CRT_HAVE_tempnam
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_tempnam,(char const *__dir, char const *__pfx),tempnam,(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_tempnam,(char const *__dir, char const *__pfx),_tempnam,(__dir,__pfx))
#else /* ... */
#undef __local___localdep_tempnam_defined
#endif /* !... */
#endif /* !__local___localdep_tempnam_defined */
__LOCAL_LIBC(_tempnam_dbg) __ATTR_MALLOC __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_tempnam_dbg))(char const *__dir_name, char const *__file_prefix, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep_tempnam)(__dir_name, __file_prefix);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__tempnam_dbg_defined
#define __local___localdep__tempnam_dbg_defined
#define __localdep__tempnam_dbg __LIBC_LOCAL_NAME(_tempnam_dbg)
#endif /* !__local___localdep__tempnam_dbg_defined */
#else /* __CRT_HAVE_tempnam || __CRT_HAVE__tempnam */
#undef __local__tempnam_dbg_defined
#endif /* !__CRT_HAVE_tempnam && !__CRT_HAVE__tempnam */
#endif /* !__local__tempnam_dbg_defined */
