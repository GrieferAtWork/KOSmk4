/* HASH CRC-32:0x6bf29a10 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sendfile_defined
#define __local_sendfile_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sendfile64) || defined(__CRT_HAVE_sendfile)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sendfile32 from sys.sendfile */
#if !defined(__local___localdep_sendfile32_defined) && defined(__CRT_HAVE_sendfile)
#define __local___localdep_sendfile32_defined 1
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_sendfile32,(__fd_t __out_fd, __fd_t __in_fd, __off32_t *__offset, __SIZE_TYPE__ __count),sendfile,(__out_fd,__in_fd,__offset,__count))
#endif /* !__local___localdep_sendfile32_defined && __CRT_HAVE_sendfile */
/* Dependency: sendfile64 from sys.sendfile */
#ifndef __local___localdep_sendfile64_defined
#define __local___localdep_sendfile64_defined 1
#ifdef __CRT_HAVE_sendfile64
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, __SIZE_TYPE__ __count),sendfile64,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, __SIZE_TYPE__ __count),sendfile,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.sendfile/sendfile64.h>
__NAMESPACE_LOCAL_BEGIN
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
#define __localdep_sendfile64 __LIBC_LOCAL_NAME(sendfile64)
#else /* ... */
#undef __local___localdep_sendfile64_defined
#endif /* !... */
#endif /* !__local___localdep_sendfile64_defined */
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__LOCAL_LIBC(sendfile) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sendfile))(__fd_t __out_fd, __fd_t __in_fd, __FS_TYPE(off) *__offset, __SIZE_TYPE__ __count) {

	__SSIZE_TYPE__ __result;
	if (__offset) {
		__off64_t __temp = *__offset;
		__result = __localdep_sendfile64(__out_fd, __in_fd, &__temp, __count);
		*__offset = (__FS_TYPE(off))__temp;
	} else {
		__result = __localdep_sendfile64(__out_fd, __in_fd, __NULLPTR, __count);
	}
	return __result;











}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sendfile_defined
#define __local___localdep_sendfile_defined 1
#define __localdep_sendfile __LIBC_LOCAL_NAME(sendfile)
#endif /* !__local___localdep_sendfile_defined */
#else /* __CRT_HAVE_sendfile64 || __CRT_HAVE_sendfile */
#undef __local_sendfile_defined
#endif /* !__CRT_HAVE_sendfile64 && !__CRT_HAVE_sendfile */
#endif /* !__local_sendfile_defined */
