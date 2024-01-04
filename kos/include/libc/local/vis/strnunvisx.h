/* HASH CRC-32:0xc148343c */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strnunvisx_defined
#define __local_strnunvisx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unvis_defined
#define __local___localdep_unvis_defined
#ifdef __CRT_HAVE_unvis
__CREDIRECT(__ATTR_INOUT(3) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_unvis,(char *__p_outbyte, int __inbyte, int *__p_state, int __flags),unvis,(__p_outbyte,__inbyte,__p_state,__flags))
#else /* __CRT_HAVE_unvis */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/unvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unvis __LIBC_LOCAL_NAME(unvis)
#endif /* !__CRT_HAVE_unvis */
#endif /* !__local___localdep_unvis_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/vis.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnunvisx) __ATTR_IN(3) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnunvisx))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags) {
	int __error, __state = 0;
	char __inchar, __outchar, *__writer, *__dstend;
	__writer = __dst;
	__dstend    = __dst + __dstsize;
	while ((__inchar = *__src++) != '\0') {
		__error = (__NAMESPACE_LOCAL_SYM __localdep_unvis)(&__outchar, (unsigned char)__inchar, &__state, __flags);
		switch (__error) {

		case __UNVIS_VALID:
			if __unlikely(__writer == __dstend)
				goto __err_nospace;
			*__writer++ = __outchar;
			break;

		case __UNVIS_VALIDPUSH:
			if __unlikely(__writer == __dstend)
				goto __err_nospace;
			*__writer++ = __outchar;
			continue;

		case __UNVIS_NOCHAR:
			break;

#ifdef __CRT_KOS
		case __UNVIS_SYNBAD:
#ifdef __EINVAL
			return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
			return __libc_seterrno(1);
#endif /* !__EINVAL */
		default:
			__builtin_unreachable();
#else /* __CRT_KOS */
		default:
#ifdef __EINVAL
			return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
			return __libc_seterrno(1);
#endif /* !__EINVAL */
#endif /* !__CRT_KOS */
		}
	}
	__error = (__NAMESPACE_LOCAL_SYM __localdep_unvis)(&__outchar, (unsigned char)__inchar, &__state, __UNVIS_END);
	if (__error == __UNVIS_VALID) {
		if __unlikely(__writer == __dstend)
			goto __err_nospace;
		*__writer++ = __outchar;
	}
	if __unlikely(__writer == __dstend)
		goto __err_nospace;
	*__writer = '\0';
	return (int)(unsigned int)(__SIZE_TYPE__)(__writer - __dst);
__err_nospace:
#ifdef __ENOSPC
	return __libc_seterrno(__ENOSPC);
#else /* __ENOSPC */
	return __libc_seterrno(1);
#endif /* !__ENOSPC */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnunvisx_defined
#define __local___localdep_strnunvisx_defined
#define __localdep_strnunvisx __LIBC_LOCAL_NAME(strnunvisx)
#endif /* !__local___localdep_strnunvisx_defined */
#endif /* !__local_strnunvisx_defined */
