/* HASH CRC-32:0xf4040459 */
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
#ifndef __local__msize_dbg_defined
#if (defined(__CRT_HAVE__msize) || defined(__CRT_HAVE_malloc_usable_size))
#define __local__msize_dbg_defined 1
/* Dependency: "_msize" from "malloc" */
#ifndef ____localdep__msize_defined
#define ____localdep__msize_defined 1
#if defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__msize,(void *__restrict __mallptr),_msize,(__mallptr))
#elif defined(__CRT_HAVE_malloc_usable_size)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__msize,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#else /* LIBC: _msize */
#undef ____localdep__msize_defined
#endif /* _msize... */
#endif /* !____localdep__msize_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_msize_dbg) __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_msize_dbg))(void *__ptr,
                                                        int __block_type) {
#line 338 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	return __localdep__msize(__ptr);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__msize) || defined(__CRT_HAVE_malloc_usable_size)) */
#endif /* !__local__msize_dbg_defined */
