/* HASH CRC-32:0xf834f235 */
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
#ifndef __local_utimes64_defined
#ifdef __CRT_HAVE_utimes
#define __local_utimes64_defined 1
/* Dependency: "utimes32" from "sys.time" */
#ifndef ____localdep_utimes32_defined
#define ____localdep_utimes32_defined 1
#ifdef __CRT_HAVE_utimes
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_utimes32,(char const *__file, struct __timeval32 const __tvp[2]),utimes,(__file,__tvp))
#else /* LIBC: utimes */
#undef ____localdep_utimes32_defined
#endif /* utimes32... */
#endif /* !____localdep_utimes32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__LOCAL_LIBC(utimes64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(utimes64))(char const *__file,
                                                      struct __timeval64 const __tvp[2]) {
#line 482 "kos/src/libc/magic/sys.time.c"
	struct __timeval32 __tv32[2];
	if (!__tvp)
		return __localdep_utimes32(__file, __NULLPTR);
	__tv32[0].tv_sec  = (__time32_t)__tvp[0].tv_sec;
	__tv32[0].tv_usec = __tvp[0].tv_usec;
	__tv32[1].tv_sec  = (__time32_t)__tvp[1].tv_sec;
	__tv32[1].tv_usec = __tvp[1].tv_usec;
	return __localdep_utimes32(__file, __tv32);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_utimes */
#endif /* !__local_utimes64_defined */
