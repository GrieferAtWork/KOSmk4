/* HASH CRC-32:0x3407d26 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sleep_defined
#if defined(__CRT_HAVE__sleep)
#define __local_sleep_defined 1
/* Dependency: "dos_sleep" from "unistd" */
#ifndef ____localdep_dos_sleep_defined
#define ____localdep_dos_sleep_defined 1
#if defined(__CRT_HAVE__sleep)
/* Sleep for up to `DURATION' seconds */
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_dos_sleep,(__UINT32_TYPE__ __duration),_sleep,(__duration))
#else /* LIBC: _sleep */
#undef ____localdep_dos_sleep_defined
#endif /* dos_sleep... */
#endif /* !____localdep_dos_sleep_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__LOCAL_LIBC(sleep) unsigned int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sleep))(unsigned int __seconds) {
#line 346 "kos/src/libc/magic/unistd.c"
	__localdep_dos_sleep((__UINT32_TYPE__)__seconds);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__sleep) */
#endif /* !__local_sleep_defined */
