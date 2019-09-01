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
#ifndef GUARD_LIBC_USER_EXECINFO_C
#define GUARD_LIBC_USER_EXECINFO_C 1

#include "../api.h"
#include "execinfo.h"

DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:backtrace,hash:0x67627a6]]]*/
/* Store up to SIZE return address of the current program state
 * in ARRAY and return the exact number of values stored */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.backtrace") int
NOTHROW_NCX(LIBCCALL libc_backtrace)(void **array,
                                     int size)
/*[[[body:backtrace]]]*/
{
	CRT_UNIMPLEMENTED("backtrace"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:backtrace]]]*/

/*[[[head:backtrace_symbols,hash:0x3368db8e]]]*/
/* Return names of functions from the backtrace list
 * in ARRAY in a newly malloc()ed memory block */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.backtrace_symbols") char **
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols)(void *const *array,
                                             int size)
/*[[[body:backtrace_symbols]]]*/
{
	CRT_UNIMPLEMENTED("backtrace_symbols"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:backtrace_symbols]]]*/

/*[[[head:backtrace_symbols_fd,hash:0xfe3257f3]]]*/
/* This function is similar to backtrace_symbols()
 * but it writes the result immediately to a file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.backtrace_symbols_fd") void
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd)(void *const *array,
                                                int size,
                                                fd_t fd)
/*[[[body:backtrace_symbols_fd]]]*/
{
	CRT_UNIMPLEMENTED("backtrace_symbols_fd"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:backtrace_symbols_fd]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x6a5101cf]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(backtrace, libc_backtrace);
DEFINE_PUBLIC_WEAK_ALIAS(backtrace_symbols, libc_backtrace_symbols);
DEFINE_PUBLIC_WEAK_ALIAS(backtrace_symbols_fd, libc_backtrace_symbols_fd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_EXECINFO_C */
