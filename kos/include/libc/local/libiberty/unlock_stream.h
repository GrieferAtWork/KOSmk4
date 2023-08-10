/* HASH CRC-32:0xfa50743e */
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
#ifndef __local_unlock_stream_defined
#define __local_unlock_stream_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep___fsetlocking_defined) && defined(__CRT_HAVE___fsetlocking)
#define __local___localdep___fsetlocking_defined
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep___fsetlocking,(__FILE *__stream, int __type),__fsetlocking,(__stream,__type))
#endif /* !__local___localdep___fsetlocking_defined && __CRT_HAVE___fsetlocking */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio_ext.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unlock_stream) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unlock_stream))(__FILE *__fp) {
	__COMPILER_IMPURE();
	(void)__fp;
#if defined(__FSETLOCKING_BYCALLER) && defined(__CRT_HAVE___fsetlocking)
	(__NAMESPACE_LOCAL_SYM __localdep___fsetlocking)(__fp, __FSETLOCKING_BYCALLER);
#endif /* __FSETLOCKING_BYCALLER && __CRT_HAVE___fsetlocking */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unlock_stream_defined
#define __local___localdep_unlock_stream_defined
#define __localdep_unlock_stream __LIBC_LOCAL_NAME(unlock_stream)
#endif /* !__local___localdep_unlock_stream_defined */
#endif /* !__local_unlock_stream_defined */
