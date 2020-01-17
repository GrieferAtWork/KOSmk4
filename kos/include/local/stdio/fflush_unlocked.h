/* HASH CRC-32:0xdc29ee10 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fflush_unlocked_defined
#define __local_fflush_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "crt_flushall" from "stdio" */
#ifndef ____localdep_crt_flushall_defined
#define ____localdep_crt_flushall_defined 1
#ifdef __CRT_HAVE__flushall
__CREDIRECT(,int,,__localdep_crt_flushall,(void),_flushall,()) __THROWS(...)
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,,__localdep_crt_flushall,(void),_IO_flush_all,()) __THROWS(...)
#else /* LIBC: _flushall */
#undef ____localdep_crt_flushall_defined
#endif /* crt_flushall... */
#endif /* !____localdep_crt_flushall_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__LOCAL_LIBC(fflush_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(fflush_unlocked))(__FILE *__stream) __THROWS(...) {
#line 1124 "kos/src/libc/magic/stdio.c"
	/* NO-OP (When not implemented by the CRT, assume no
	 * buffering being done, meaning this function isn't needed) */
#if defined(__CRT_HAVE__flushall) || defined(__CRT_HAVE__IO_flush_all)
	if (!__stream)
		return __localdep_crt_flushall();
#endif /* __CRT_HAVE__flushall || __CRT_HAVE__IO_flush_all */
	(void)__stream;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fflush_unlocked_defined */
