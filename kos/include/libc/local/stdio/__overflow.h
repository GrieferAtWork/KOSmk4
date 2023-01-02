/* HASH CRC-32:0x8cc20389 */
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
#ifndef __local___overflow_defined
#define __local___overflow_defined
#include <__crt.h>
#if defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__flsbuf_defined
#define __local___localdep__flsbuf_defined
#ifdef __CRT_HAVE__flsbuf
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep__flsbuf,(int __ch, __FILE *__restrict __stream),_flsbuf,(__ch,__stream))
#elif defined(__CRT_HAVE___swbuf)
__CREDIRECT(__ATTR_INOUT(2),int,__THROWING,__localdep__flsbuf,(int __ch, __FILE *__restrict __stream),__swbuf,(__ch,__stream))
#else /* ... */
#undef __local___localdep__flsbuf_defined
#endif /* !... */
#endif /* !__local___localdep__flsbuf_defined */
__LOCAL_LIBC(__overflow) __ATTR_INOUT(1) int
(__LIBCCALL __LIBC_LOCAL_NAME(__overflow))(__FILE *__stream, int __ch) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep__flsbuf)(__ch, __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___overflow_defined
#define __local___localdep___overflow_defined
#define __localdep___overflow __LIBC_LOCAL_NAME(__overflow)
#endif /* !__local___localdep___overflow_defined */
#else /* __CRT_HAVE__flsbuf || __CRT_HAVE___swbuf */
#undef __local___overflow_defined
#endif /* !__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf */
#endif /* !__local___overflow_defined */
