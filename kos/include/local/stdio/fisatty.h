/* HASH CRC-32:0xb945bc44 */
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
#ifndef __local_fisatty_defined
#if (defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#define __local_fisatty_defined 1
/* Dependency: "isatty" */
#ifndef ____localdep_isatty_defined
#define ____localdep_isatty_defined 1
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#else /* LIBC: isatty */
#undef ____localdep_isatty_defined
#endif /* isatty... */
#endif /* !____localdep_isatty_defined */

/* Dependency: "fileno" */
#ifndef ____localdep_fileno_defined
#define ____localdep_fileno_defined 1
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* LIBC: fileno */
#undef ____localdep_fileno_defined
#endif /* fileno... */
#endif /* !____localdep_fileno_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fisatty) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fisatty))(__FILE *__restrict __stream) {
#line 1919 "kos/src/libc/magic/stdio.c"
	return __localdep_isatty(__localdep_fileno(__stream));
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_isatty || __CRT_HAVE__isatty) && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) */
#endif /* !__local_fisatty_defined */
