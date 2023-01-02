/* HASH CRC-32:0x17ee0ff4 */
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
#ifndef __local_unicode_writeutf8_n_defined
#define __local_unicode_writeutf8_n_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
__LOCAL_LIBC(unicode_writeutf8_n) __ATTR_RETNONNULL __ATTR_OUTS(1, 3) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_writeutf8_n))(char *__restrict __dst, __CHAR32_TYPE__ __ch, __SIZE_TYPE__ __dst_maxbytes) {
	if __likely(__dst_maxbytes != 0) {
		if __likely(__ch <= ((__UINT32_TYPE__)1 << 7)-1) {
			*__dst++ = (char)(unsigned char)__ch;
		} else {
			char __tempbuf[7], *__tempdst = __tempbuf;
			__SIZE_TYPE__ __templen;
			if (__ch <= ((__UINT32_TYPE__)1 << 11)-1) {
				*__tempdst++ = (char)(unsigned char)(0xc0 | (__UINT8_TYPE__)((__ch >> 6)/* & 0x1f*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			} else if (__ch <= ((__UINT32_TYPE__)1 << 16)-1) {
				*__tempdst++ = (char)(unsigned char)(0xe0 | (__UINT8_TYPE__)((__ch >> 12)/* & 0x0f*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			} else if (__ch <= ((__UINT32_TYPE__)1 << 21)-1) {
				*__tempdst++ = (char)(unsigned char)(0xf0 | (__UINT8_TYPE__)((__ch >> 18)/* & 0x07*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 12) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			} else if (__ch <= ((__UINT32_TYPE__)1 << 26)-1) {
				*__tempdst++ = (char)(unsigned char)(0xf8 | (__UINT8_TYPE__)((__ch >> 24)/* & 0x03*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 18) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 12) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			} else if (__ch <= ((__UINT32_TYPE__)1 << 31)-1) {
				*__tempdst++ = (char)(unsigned char)(0xfc | (__UINT8_TYPE__)((__ch >> 30)/* & 0x01*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 24) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 18) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 12) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			} else {
				*__tempdst++ = (char)(unsigned char)(0xfe);
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 30) & 0x03/* & 0x3f*/));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 24) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 18) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 12) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
				*__tempdst++ = (char)(unsigned char)(0x80 | (__UINT8_TYPE__)((__ch)&0x3f));
			}
			__templen = (__SIZE_TYPE__)(__tempdst - __tempbuf) * sizeof(char);
			if (__templen > __dst_maxbytes)
				__templen = __dst_maxbytes;
			__dst = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__dst, __tempbuf, __templen);
		}
	}
	return __dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_writeutf8_n_defined
#define __local___localdep_unicode_writeutf8_n_defined
#define __localdep_unicode_writeutf8_n __LIBC_LOCAL_NAME(unicode_writeutf8_n)
#endif /* !__local___localdep_unicode_writeutf8_n_defined */
#endif /* !__local_unicode_writeutf8_n_defined */
