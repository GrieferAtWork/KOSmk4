/* HASH CRC-32:0xe15f4363 */
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
#ifndef __local_fflush_unlocked_defined
#define __local_fflush_unlocked_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_flushall_defined
#define __local___localdep_crt_flushall_defined
#ifdef __CRT_HAVE__flushall
__CREDIRECT(,int,__NOTHROW_CB,__localdep_crt_flushall,(void),_flushall,())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__NOTHROW_CB,__localdep_crt_flushall,(void),_IO_flush_all,())
#else /* ... */
#undef __local___localdep_crt_flushall_defined
#endif /* !... */
#endif /* !__local___localdep_crt_flushall_defined */
__LOCAL_LIBC(fflush_unlocked) int
__NOTHROW_CB(__LIBCCALL __LIBC_LOCAL_NAME(fflush_unlocked))(__FILE *__stream) {
	/* NO-OP  (When  not  implemented  by  the  CRT,  assume  no
	 * buffering being done, meaning this function isn't needed) */
#if defined(__CRT_HAVE__flushall) || defined(__CRT_HAVE__IO_flush_all)
	if (!__stream)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_flushall)();
#endif /* __CRT_HAVE__flushall || __CRT_HAVE__IO_flush_all */
	(void)__stream;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fflush_unlocked_defined
#define __local___localdep_fflush_unlocked_defined
#define __localdep_fflush_unlocked __LIBC_LOCAL_NAME(fflush_unlocked)
#endif /* !__local___localdep_fflush_unlocked_defined */
#endif /* !__local_fflush_unlocked_defined */
