/* HASH CRC-32:0xe0ecf01b */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_abort_defined
#define __local_abort_defined
#include <__crt.h>
#if defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep__Exit,(int __status),_Exit,{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stdlib.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(abort) __ATTR_NORETURN void
(__LIBCCALL __LIBC_LOCAL_NAME(abort))(void) {
	(__NAMESPACE_LOCAL_SYM __localdep__Exit)(__EXIT_FAILURE);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_abort_defined
#define __local___localdep_abort_defined
#define __localdep_abort __LIBC_LOCAL_NAME(abort)
#endif /* !__local___localdep_abort_defined */
#else /* __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit */
#undef __local_abort_defined
#endif /* !__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit */
#endif /* !__local_abort_defined */
