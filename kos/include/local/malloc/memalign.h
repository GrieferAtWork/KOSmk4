/* HASH CRC-32:0xe72b73dc */
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
#ifndef __local_memalign_defined
#if defined(__CRT_HAVE_posix_memalign)
#define __local_memalign_defined 1
/* Dependency: "crt_posix_memalign" from "malloc" */
#ifndef ____localdep_crt_posix_memalign_defined
#define ____localdep_crt_posix_memalign_defined 1
#if defined(__CRT_HAVE_posix_memalign)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_crt_posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),posix_memalign,(__pp,__alignment,__n_bytes))
#else /* LIBC: posix_memalign */
#undef ____localdep_crt_posix_memalign_defined
#endif /* crt_posix_memalign... */
#endif /* !____localdep_crt_posix_memalign_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memalign) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memalign))(__SIZE_TYPE__ __alignment,
                                                      __SIZE_TYPE__ __n_bytes) {
#line 78 "kos/src/libc/magic/malloc.c"
	void *__result;
	if (__localdep_crt_posix_memalign(&__result, __alignment, __n_bytes))
		return __NULLPTR;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_posix_memalign) */
#endif /* !__local_memalign_defined */
