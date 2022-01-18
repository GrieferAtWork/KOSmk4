/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SELECT_C
#define GUARD_LIBC_USER_SYS_SELECT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h> /* SYS_* */

#include "sys.select.h"

#ifndef SYS__newselect
/* Pull in information to figure out what kind of
 * select() function is  exported by the  kernel. */
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#include <asm/syscalls-proto.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* !SYS__newselect */

DECL_BEGIN

/*[[[head:libc_select,hash:CRC-32=0x9c2d65fd]]]*/
INTERN ATTR_SECTION(".text.crt.io.poll") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_select)(__STDC_INT_AS_SIZE_T nfds,
                                  fd_set *__restrict readfds,
                                  fd_set *__restrict writefds,
                                  fd_set *__restrict exceptfds,
                                  struct timeval *__restrict timeout)
/*[[[body:libc_select]]]*/
{
	ssize_t result;
#ifdef SYS__newselect
	result = sys__newselect(nfds, readfds, writefds, exceptfds, timeout);
#elif __NRAC_select == 5
	result = sys_select(nfds, readfds, writefds, exceptfds, timeout);
#elif __NRAC_select == 1
	/* Must use `struct sel_arg_struct' */
	struct sel_arg_struct arg;
	arg.n    = (ulongptr_t)nfds;
	arg.inp  = readfds;
	arg.outp = writefds;
	arg.exp  = exceptfds;
	arg.tvp  = timeout;
	result   = sys_select(&arg);
#else /* ... */
#error "Unrecognized sys_select() variant"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_select]]]*/

struct sigset_and_len {
	sigset_t const *ss_ptr;
	size_t          ss_len;
};


/*[[[head:libc_pselect,hash:CRC-32=0x945cfb8b]]]*/
INTERN ATTR_SECTION(".text.crt.io.poll") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_pselect)(__STDC_INT_AS_SIZE_T nfds,
                                   fd_set *__restrict readfds,
                                   fd_set *__restrict writefds,
                                   fd_set *__restrict exceptfds,
                                   struct timespec const *__restrict timeout,
                                   sigset_t const *__restrict sigmask)
/*[[[body:libc_pselect]]]*/
{
	ssize_t result;
	struct sigset_and_len ss;
	ss.ss_ptr = sigmask;
	ss.ss_len = sizeof(sigset_t);
	result = sys_pselect6(nfds, readfds, writefds, exceptfds, timeout, &ss);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pselect]]]*/

/*[[[head:libc_select64,hash:CRC-32=0x6a377a28]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_select64, libc_select);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.poll") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_select64)(__STDC_INT_AS_SIZE_T nfds,
                                    fd_set *__restrict readfds,
                                    fd_set *__restrict writefds,
                                    fd_set *__restrict exceptfds,
                                    struct timeval64 *__restrict timeout)
/*[[[body:libc_select64]]]*/
{
	ssize_t result;
#ifdef SYS_select64
	result = sys_select64(nfds, readfds, writefds, exceptfds, timeout);
#elif defined(SYS_select_time64)
	result = sys_select_time64(nfds, readfds, writefds, exceptfds, timeout);
#else /* ... */
#error "No way to implement `select64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_select64]]]*/

/*[[[head:libc_pselect64,hash:CRC-32=0xdc174be2]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pselect64, libc_pselect);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.poll") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_pselect64)(__STDC_INT_AS_SIZE_T nfds,
                                     fd_set *__restrict readfds,
                                     fd_set *__restrict writefds,
                                     fd_set *__restrict exceptfds,
                                     struct timespec64 const *__restrict timeout,
                                     sigset_t const *__restrict sigmask)
/*[[[body:libc_pselect64]]]*/
{
	ssize_t result;
	struct sigset_and_len ss;
	ss.ss_ptr = sigmask;
	ss.ss_len = sizeof(sigset_t);
#ifdef SYS_pselect6_64
	result = sys_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, &ss);
#elif defined(SYS_pselect6_time64)
	result = sys_pselect6_time64(nfds, readfds, writefds, exceptfds, timeout, &ss);
#else /* ... */
#error "No way to implement `pselect64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pselect64]]]*/





/*[[[start:exports,hash:CRC-32=0x80a21f10]]]*/
DEFINE_PUBLIC_ALIAS(__select, libc_select);
DEFINE_PUBLIC_ALIAS(select, libc_select);
DEFINE_PUBLIC_ALIAS(pselect, libc_pselect);
DEFINE_PUBLIC_ALIAS(select64, libc_select64);
DEFINE_PUBLIC_ALIAS(pselect64, libc_pselect64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SELECT_C */
