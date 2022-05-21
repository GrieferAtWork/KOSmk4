/* HASH CRC-32:0xbe8640c7 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_movetext_defined
#define __local_movetext_defined
#include <__crt.h>
#include <features.h>
#if defined(__KOS__) && defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_fileno_defined
#define __local___localdep_fileno_defined
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fileno_defined
#endif /* !... */
#endif /* !__local___localdep_fileno_defined */
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined
#ifdef __CRT_HAVE_ioctl
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __local___localdep_ioctl_defined
#endif /* !... */
#endif /* !__local___localdep_ioctl_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <libc/template/stdtty.h>
#include <kos/ioctl/video.h>
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(movetext) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(movetext))(int __left, int __top, int __right, int __bottom, int __destleft, int __desttop) {
	struct vidttyinfo __info;
	struct vidttycelldata __data;
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_fileno)(__LOCAL_stdtty);
	__UINT16_TYPE__ __args[6], __i, __error;
	if ((__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, VID_IOC_GETTTYINFO, &__info) != 0)
		goto __err;
	__args[0] = (__UINT16_TYPE__)(unsigned int)__left;
	__args[1] = (__UINT16_TYPE__)(unsigned int)__right;
	__args[2] = (__UINT16_TYPE__)(unsigned int)__destleft;
	__args[3] = (__UINT16_TYPE__)(unsigned int)__top;
	__args[4] = (__UINT16_TYPE__)(unsigned int)__bottom;
	__args[5] = (__UINT16_TYPE__)(unsigned int)__desttop;
	for (__i = 0; __i < 6; ++__i) {
		__UINT16_TYPE__ __v = __args[__i] - 1;
		if (__v < 0) {
			__v = 0;
		} else {
			__UINT16_TYPE__ __maxval;
			__maxval = __i >= 3 ? __info.vti_cellh : __info.vti_cellw;
			if (__v > __maxval)
				__v = __maxval;
		}
		__args[__i] = __v;
	}
	if (__args[0]/*left*/ >= __args[1]/*right*/)
		goto __done;
	if (__args[3]/*top*/ >= __args[4]/*bottom*/)
		goto __done;
	(__NAMESPACE_LOCAL_SYM __localdep_bzero)(&__data, sizeof(__data));
	__data.vcd_x = __args[0]/*left*/;
	__data.vcd_y = __args[3]/*top*/;
	__data.vcd_w = __args[1]/*right*/ - __args[0]/*left*/;
	__data.vcd_h = __args[4]/*bottom*/ - __args[3]/*top*/;
	__data.vcd_dat = (__BYTE_TYPE__ *)__malloca(__data.vcd_w * __data.vcd_h * __info.vti_cellsize);
	if __unlikely(!__data.vcd_dat)
		goto __err;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, VID_IOC_GETCELLDATA, &__data);
	if __likely(__error == 0) {
		__data.vcd_x = __args[2]/*destleft*/;
		__data.vcd_y = __args[5]/*desttop*/;
		__error = (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, VID_IOC_SETCELLDATA, &__data);
	}
	__freea(__data.vcd_dat);
	if __unlikely(__error != 0)
		goto __err;
__done:
	return 0;
__err:
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_movetext_defined
#define __local___localdep_movetext_defined
#define __localdep_movetext __LIBC_LOCAL_NAME(movetext)
#endif /* !__local___localdep_movetext_defined */
#else /* __KOS__ && __CRT_HAVE_stdtty && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#undef __local_movetext_defined
#endif /* !__KOS__ || !__CRT_HAVE_stdtty || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) */
#endif /* !__local_movetext_defined */
