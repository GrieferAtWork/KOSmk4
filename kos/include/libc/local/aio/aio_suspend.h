/* HASH CRC-32:0xc4783f32 */
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
#ifndef __local_aio_suspend_defined
#define __local_aio_suspend_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_aio_suspendt64) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
#include <bits/crt/aiocb.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_aio_suspendt32_defined
#define __local___localdep_aio_suspendt32_defined
#if defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_RPC,__localdep_aio_suspendt32,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec32 const *__restrict __timeout),aio_suspend,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_RPC,__localdep_aio_suspendt32,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec32 const *__restrict __timeout),aio_suspend64,(__list,__nent,__timeout))
#else /* ... */
#undef __local___localdep_aio_suspendt32_defined
#endif /* !... */
#endif /* !__local___localdep_aio_suspendt32_defined */
#ifndef __local___localdep_aio_suspendt64_defined
#define __local___localdep_aio_suspendt64_defined
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,__localdep_aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec64 const *__restrict __rel_timeout),aio_suspend,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,__localdep_aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec64 const *__restrict __rel_timeout),aio_suspend64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,__localdep_aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec64 const *__restrict __rel_timeout),aio_suspendt64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,__localdep_aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct __timespec64 const *__restrict __rel_timeout),aio_suspend64t64,(__list,__nent,__rel_timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
__NAMESPACE_LOCAL_END
#include <libc/local/aio/aio_suspendt64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_aio_suspendt64 __LIBC_LOCAL_NAME(aio_suspendt64)
#else /* ... */
#undef __local___localdep_aio_suspendt64_defined
#endif /* !... */
#endif /* !__local___localdep_aio_suspendt64_defined */
__LOCAL_LIBC(aio_suspend) __ATTR_INS(1, 2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(aio_suspend))(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout) {
#if (defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
	struct __timespec32 __rel_timeout32;
	if (!__rel_timeout)
		return (__NAMESPACE_LOCAL_SYM __localdep_aio_suspendt32)(__list, __nent, __NULLPTR);
	__rel_timeout32.tv_sec  = (__time32_t)__rel_timeout->tv_sec;
	__rel_timeout32.tv_nsec = __rel_timeout->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_aio_suspendt32)(__list, __nent, &__rel_timeout32);
#else /* (__CRT_HAVE_aio_suspend && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE_aio_suspend64 && (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) */
	struct __timespec64 __rel_timeout64;
	if (!__rel_timeout)
		return (__NAMESPACE_LOCAL_SYM __localdep_aio_suspendt64)(__list, __nent, __NULLPTR);
	__rel_timeout64.tv_sec  = (__time64_t)__rel_timeout->tv_sec;
	__rel_timeout64.tv_nsec = __rel_timeout->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_aio_suspendt64)(__list, __nent, &__rel_timeout64);
#endif /* (!__CRT_HAVE_aio_suspend || (__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) && (!__CRT_HAVE_aio_suspend64 || (!__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_aio_suspend_defined
#define __local___localdep_aio_suspend_defined
#define __localdep_aio_suspend __LIBC_LOCAL_NAME(aio_suspend)
#endif /* !__local___localdep_aio_suspend_defined */
#else /* (__CRT_HAVE_aio_suspendt64 && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE_aio_suspend64t64 && (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE_aio_suspend && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE_aio_suspend64 && (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) */
#undef __local_aio_suspend_defined
#endif /* (!__CRT_HAVE_aio_suspendt64 || (__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) && (!__CRT_HAVE_aio_suspend64t64 || (!__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) && (!__CRT_HAVE_aio_suspend || (__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) && (!__CRT_HAVE_aio_suspend64 || (!__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)) */
#endif /* !__local_aio_suspend_defined */
