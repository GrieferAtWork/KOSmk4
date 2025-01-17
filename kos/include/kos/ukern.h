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
#ifndef _KOS_UKERN_H
#define _KOS_UKERN_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/bits/ukern-struct.h>
#include <kos/bits/ukern.h>

__DECL_BEGIN


#ifndef USERKERN_SYSCALL_ENCODE
/* Encode a system call number for use as an offset to the userkern descriptor. */
#define USERKERN_SYSCALL_ENCODE(no)            ((no) & 0x1ffff)
#define USERKERN_SYSCALL_ENCODE_EX(no, except) (((no) & 0x1ffff) | ((except) ? USERKERN_SYSCALL_EXCEPTBIT : 0))
#if __SIZEOF_SYSCALL_LONG_T__ >= 8
#define USERKERN_SYSCALL_DECODE(no)  ((((no) & 0x10000) ? __UINT64_C(0xffffffffffff0000) : __UINT64_C(0)) | ((no) & __UINT64_C(0xffff)))
#else /* __SIZEOF_SYSCALL_LONG_T__ >= 8 */
#define USERKERN_SYSCALL_DECODE(no)  ((((no) & 0x10000) ? __UINT32_C(0xffff0000) : __UINT32_C(0)) | ((no) & __UINT32_C(0xffff)))
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
#define USERKERN_SYSCALL_ISVALID(no) ((no) <= USERKERN_SYSCALL_MAXVALID)
#define USERKERN_SYSCALL_MAXVALID    0x3ffff
#define USERKERN_SYSCALL_EXCEPTBIT   0x20000
#endif /* !USERKERN_SYSCALL_ENCODE */



#ifdef __CC__
/* Helper wrapper for  generating a callable  prototype for  any
 * given system call, using the userkern segment `base' as base.
 * >> #include <sys/syscall-proto.h>
 * >> #include <kos/ukern.h>
 * >>
 * >> ...
 * >>
 * >> struct userkern *me = userkern_self();
 * >> char buf[1024];
 * >> fd_t fd = userkern_syscall(me, open)("/bin/init", O_RDONLY, 0777);
 * >> userkern_syscall(me, read)(fd, buf, sizeof(buf));
 * >> userkern_syscall(me, close)(fd);
 * WARNING: Unlike the C library's `syscall()' function, this method of  invocation
 *          will not set the `errno' variable on error, but instead return negative
 *          E* error codes from <errno.h> upon failure. */
#define userkern_syscall(base, name)                                   \
	(*(SYSCALL_PROTO_POINTER(name))(void *)((__UINTPTR_TYPE__)(base) + \
	                                        USERKERN_SYSCALL_ENCODE(__NR_##name)))

/* Same as `userkern_syscall()',  but enable  exceptions (s.a.  `set_exception_handler()'),
 * as opposed to causing the system call to return a negative errno code (s.a. `E_ISERR()') */
#define userkern_Syscall(base, name)                                   \
	(*(SYSCALL_PROTO_POINTER(name))(void *)((__UINTPTR_TYPE__)(base) + \
	                                        USERKERN_SYSCALL_ENCODE_EX(__NR_##name, 1)))


/* Access  fields of- or  return the base address  of the userkern descriptor
 * for  the calling thread.  - Based on  architecture, these functions assume
 * that the internal register used to save the descriptor base address hasn't
 * been overwritten to point elsewhere:
 *   - x86_64:
 *      - Assume that the %fs segment base points into kernel-space
 *   - i386:
 *      - Assume that the %gs segment base points into kernel-space
 */
#ifndef userkern_self
#include <__crt.h>
#ifdef __CRT_HAVE_userkern_self
__CDECLARE(,struct userkern *,__NOTHROW_NCX,userkern_self,(void),())
#define userkern_self() userkern_self()
#endif /* __CRT_HAVE_userkern_self */
#endif /* !userkern_self */

/* Returns `true'  if  the  userkern segment  can  be  used.
 * When `false' is returned, you may call `userkern_reset()'
 * in order to reset the  userkern segment to a valid  value */
#ifndef userkern_valid
#include <__crt.h>
#ifdef __CRT_HAVE_userkern_valid
__CDECLARE(,__BOOL,__NOTHROW_NCX,userkern_valid,(void),())
#define userkern_valid() userkern_valid()
#endif /* __CRT_HAVE_userkern_valid */
#endif /* !userkern_valid */

/* Reset  the base address of the user-thread segment to a valid
 * value (in case the address had previously been re-assigned by
 * some other TLS mechanism) */
#ifndef userkern_reset
#include <__crt.h>
#ifdef __CRT_HAVE_userkern_reset
__CDECLARE_VOID(,__NOTHROW_NCX,userkern_reset,(void),())
#define userkern_reset() userkern_reset()
#endif /* __CRT_HAVE_userkern_reset */
#endif /* !userkern_reset */

#ifndef userkern_getfield
#define userkern_getfield(field) (userkern_self()->field)
#endif /* !userkern_getfield */

#ifndef userkern_setfield
#define userkern_setfield(field, v) (userkern_self()->field = (v))
#endif /* !userkern_setfield */

/*
#include <sys/syscall.h>
#include <unistd.h>

.rodata
str: .string "Hello World\0"
len = . - str
.text
_start:
	movl   $0xc0000000, %eax
	wrfsbasel %eax

	pushl  $len
	pushl  $str
	pushl  $STDOUT_FILENO
	call   sys_write
	addl   $12, %esp

	pushl  $0
	call   sys_exit

sys_write = 0xc0000000 + USERKERN_SYSCALL_ENCODE(SYS_write)
sys_exit  = 0xc0000000 + USERKERN_SYSCALL_ENCODE(SYS_exit)
*/

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_UKERN_H */
