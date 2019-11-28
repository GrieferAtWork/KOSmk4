/* HASH CRC-32:0x679d930d */
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
#ifndef __local_dup3_defined
#if defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2)
#define __local_dup3_defined 1
/* Dependency: "dup2" */
#ifndef ____localdep_dup2_defined
#define ____localdep_dup2_defined 1
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#else /* LIBC: dup2 */
#undef ____localdep_dup2_defined
#endif /* dup2... */
#endif /* !____localdep_dup2_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dup3) __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dup3))(__fd_t __oldfd,
                                                  __fd_t __newfd,
                                                  __oflag_t __flags) {
#line 1124 "kos/src/libc/magic/unistd.c"
	return __newfd != __oldfd ? __localdep_dup2(__oldfd, __newfd) : -1;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 */
#endif /* !__local_dup3_defined */
