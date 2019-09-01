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
#ifndef GUARD_LIBC_USER_SYS_SELECT_C
#define GUARD_LIBC_USER_SYS_SELECT_C 1

#include "../api.h"
#include "sys.select.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:select,hash:0x5421679c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.select") int
NOTHROW_RPC(LIBCCALL libc_select)(int nfds,
                                  fd_set *__restrict readfds,
                                  fd_set *__restrict writefds,
                                  fd_set *__restrict exceptfds,
                                  struct timeval *__restrict timeout)
/*[[[body:select]]]*/
{
	CRT_UNIMPLEMENTED("select"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:select]]]*/

/*[[[head:pselect,hash:0x1a16c04e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.pselect") int
NOTHROW_RPC(LIBCCALL libc_pselect)(int nfds,
                                   fd_set *__restrict readfds,
                                   fd_set *__restrict writefds,
                                   fd_set *__restrict exceptfds,
                                   struct timespec const *__restrict timeout,
                                   sigset_t const *__restrict sigmask)
/*[[[body:pselect]]]*/
{
	CRT_UNIMPLEMENTED("pselect"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pselect]]]*/

/*[[[head:select64,hash:0x79d5277]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_select64, libc_select);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.select64") int
NOTHROW_RPC(LIBCCALL libc_select64)(int nfds,
                                    fd_set *__restrict readfds,
                                    fd_set *__restrict writefds,
                                    fd_set *__restrict exceptfds,
                                    struct timeval64 *__restrict timeout)
/*[[[body:select64]]]*/
{
	CRT_UNIMPLEMENTED("select64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:select64]]]*/

/*[[[head:pselect64,hash:0x8ae0c101]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pselect64, libc_pselect);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.pselect64") int
NOTHROW_RPC(LIBCCALL libc_pselect64)(int nfds,
                                     fd_set *__restrict readfds,
                                     fd_set *__restrict writefds,
                                     fd_set *__restrict exceptfds,
                                     struct timespec64 const *__restrict timeout,
                                     sigset_t const *__restrict sigmask)
/*[[[body:pselect64]]]*/
{
	CRT_UNIMPLEMENTED("pselect64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:pselect64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xe1ac2eb]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(select, libc_select);
DEFINE_PUBLIC_WEAK_ALIAS(pselect, libc_pselect);
DEFINE_PUBLIC_WEAK_ALIAS(select64, libc_select64);
DEFINE_PUBLIC_WEAK_ALIAS(pselect64, libc_pselect64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SELECT_C */
