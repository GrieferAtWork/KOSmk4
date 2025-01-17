/* HASH CRC-32:0x7bc35f7a */
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
#ifndef __local___spin_unlock_defined
#define __local___spin_unlock_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__CRT_HAVE_shared_lock_release_ex) || defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_release_ex_defined
#define __local___localdep_shared_lock_release_ex_defined
#ifdef __CRT_HAVE_shared_lock_release_ex
__COMPILER_CREDIRECT(__LIBC,__ATTR_INOUT(1),__BOOL,__NOTHROW_NCX,__FCALL,__localdep_shared_lock_release_ex,(struct shared_lock *__restrict __self),shared_lock_release_ex,(__self))
#elif defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_release_ex.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_shared_lock_release_ex __LIBC_LOCAL_NAME(shared_lock_release_ex)
#else /* ... */
#undef __local___localdep_shared_lock_release_ex_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_release_ex_defined */
__LOCAL_LIBC(__spin_unlock) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__spin_unlock))(unsigned int *__lock) {
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_release_ex)((struct shared_lock *)__lock);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___spin_unlock_defined
#define __local___localdep___spin_unlock_defined
#define __localdep___spin_unlock __LIBC_LOCAL_NAME(__spin_unlock)
#endif /* !__local___localdep___spin_unlock_defined */
#else /* __CRT_HAVE_shared_lock_release_ex || __shared_lock_release_ex || (__shared_lock_sendone && __shared_lock_sendall) */
#undef __local___spin_unlock_defined
#endif /* !__CRT_HAVE_shared_lock_release_ex && !__shared_lock_release_ex && (!__shared_lock_sendone || !__shared_lock_sendall) */
#endif /* !__local___spin_unlock_defined */
