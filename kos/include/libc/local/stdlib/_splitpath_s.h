/* HASH CRC-32:0x8efb519f */
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
#ifndef __local__splitpath_s_defined
#define __local__splitpath_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_splitpath_s) __ATTR_IN(1) __ATTR_OUTS(2, 3) __ATTR_OUTS(4, 5) __ATTR_OUTS(6, 7) __ATTR_OUTS(8, 9) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_splitpath_s))(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen) {
	__SIZE_TYPE__ __len, __last_slash, __last_dot;
	if __unlikely(!__abspath)
		goto __err_inval;
	if __unlikely((__drive != __NULLPTR) != (__drivelen != 0))
		goto __err_inval;
	if __unlikely((__dir != __NULLPTR) != (__dirlen != 0))
		goto __err_inval;
	if __unlikely((__file != __NULLPTR) != (__filelen != 0))
		goto __err_inval;
	if __unlikely((__ext != __NULLPTR) != (__extlen != 0))
		goto __err_inval;
	for (__len = 0; __len < 3; ++__len) {
		if (__abspath[__len] == ':') {
			if (__drive) {
				if __unlikely(__drivelen <= __len)
					goto __err_range;
				(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__drive, __abspath, __len, sizeof(char));
				__drive[__len] = 0;
			}
			__abspath += __len + 1;
			goto __got_drive;
		}
	}
	if (__drive)
		*__drive = 0;
__got_drive:
	__last_slash = 0;
	__last_dot = (__SIZE_TYPE__)-1;
	for (__len = 0;; ++__len) {
		char __ch = __abspath[__len];
		if (!__ch)
			break;
		if (__ch == '/' || __ch == '\\')
			__last_slash = __len + 1;
		if (__ch == '.')
			__last_dot = __len;
	}
	if (__last_slash) {
		if (__dir) {
			if __unlikely(__dirlen <= __last_slash)
				goto __err_range;
			(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__dir, __abspath, __last_slash, sizeof(char));
			__dir[__last_slash] = 0;
		}
	} else {
		if (__dir)
			*__dir = 0;
	}
	if (__last_dot != (__SIZE_TYPE__)-1 && __last_dot > __last_slash) {
		if (__ext) {
			__SIZE_TYPE__ __path_extlen = __len - __last_dot;
			if __unlikely(__extlen <= __path_extlen)
				goto __err_range;
			(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__ext, __abspath + __last_dot, __path_extlen, sizeof(char));
			__ext[__path_extlen] = 0;
		}
	} else {
		if (__ext)
			*__ext = 0;
		__last_dot = __len;
	}
	if (__file) {
		__len = __last_dot - __last_slash;
		if __unlikely(__filelen <= __len)
			goto __err_range;
		(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__file, __abspath + __last_slash, __len, sizeof(char));
		__file[__len] = 0;
	}
	return 0;
__err_inval:
#ifdef __EINVAL
	return __EINVAL;
#else /* __EINVAL */
	return 1;
#endif /* !__EINVAL */
__err_range:
#ifdef __ERANGE
	(void)__libc_seterrno(__ERANGE);
	return __ERANGE;
#else /* __ERANGE */
	return 1;
#endif /* !__ERANGE */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__splitpath_s_defined
#define __local___localdep__splitpath_s_defined
#define __localdep__splitpath_s __LIBC_LOCAL_NAME(_splitpath_s)
#endif /* !__local___localdep__splitpath_s_defined */
#endif /* !__local__splitpath_s_defined */
