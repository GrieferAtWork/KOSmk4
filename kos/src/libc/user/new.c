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
#ifndef GUARD_LIBC_USER_NEW_C
#define GUARD_LIBC_USER_NEW_C 1

#include "../api.h"
/**/

#include "new.h"

DECL_BEGIN

/*[[[head:libc__query_new_handler,hash:CRC-32=0x7c1b32c3]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.malloc") _PNH
NOTHROW_NCX(LIBDCALL libc__query_new_handler)(void)
/*[[[body:libc__query_new_handler]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_query_new_handler"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__query_new_handler]]]*/

/*[[[head:libc__set_new_handler,hash:CRC-32=0x8c8d8428]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.malloc") _PNH
NOTHROW_NCX(LIBDCALL libc__set_new_handler)(_PNH newhandler)
/*[[[body:libc__set_new_handler]]]*/
/*AUTO*/{
	(void)newhandler;
	CRT_UNIMPLEMENTEDF("_set_new_handler(%p)", newhandler); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_new_handler]]]*/

/*[[[head:libc__query_new_mode,hash:CRC-32=0xb07c83a7]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.malloc") int
NOTHROW_NCX(LIBDCALL libc__query_new_mode)(void)
/*[[[body:libc__query_new_mode]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_query_new_mode"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__query_new_mode]]]*/

/*[[[head:libc__set_new_mode,hash:CRC-32=0x7ecb692]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.malloc") int
NOTHROW_NCX(LIBDCALL libc__set_new_mode)(int newmode)
/*[[[body:libc__set_new_mode]]]*/
/*AUTO*/{
	(void)newmode;
	CRT_UNIMPLEMENTEDF("_set_new_mode(%x)", newmode); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_new_mode]]]*/

/*[[[start:exports,hash:CRC-32=0x1ef0ab6a]]]*/
DEFINE_PUBLIC_ALIAS(_query_new_handler, libc__query_new_handler);
DEFINE_PUBLIC_ALIAS(_set_new_handler, libc__set_new_handler);
DEFINE_PUBLIC_ALIAS(_query_new_mode, libc__query_new_mode);
DEFINE_PUBLIC_ALIAS(_set_new_mode, libc__set_new_mode);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NEW_C */
