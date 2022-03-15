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
#ifndef GUARD_LIBC_USER_CONIO_C
#define GUARD_LIBC_USER_CONIO_C 1

#include "../api.h"
/**/

#include "conio.h"

DECL_BEGIN

/* TODO: _kbhit()  --> readf(IO_NONBLOCK) */
/* TODO: _getch()  --> tcgetattr(SAVED) + tcsetattr(~ECHO) + read() + tcsetattr(SAVED) */
/* TODO: _getche() --> tcgetattr(SAVED) + tcsetattr(ECHO) + read() + tcsetattr(SAVED) */

/* NOTE: The race condition where _getch() / _getche() don't affect the echoing of characters
 *       entered while not inside of the read-character loop actually also exists on  windows
 *       (as  far as I can tell). By looking  at the disassembly of those functions, it seems
 *       like they do pretty much the same as we do, except that:
 *        - `tcgetattr()' becomes `GetConsoleMode()'
 *        - `tcsetattr()' becomes `SetConsoleMode()'
 *        - `~ECHO' becomes `0'
 *        - `ECHO' becomes `ENABLE_ECHO_INPUT' (well... actually it also becomes
 *           `0', and the read character is manually echoed via `_putch()', but
 *           you should get the idea...) */

/*[[[head:libc__kbhit,hash:CRC-32=0xbcfa11c8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__kbhit)(void)
/*[[[body:libc__kbhit]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_kbhit"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__kbhit]]]*/

/*[[[head:libc__getch,hash:CRC-32=0xf7f370e]]]*/
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getch)(void)
/*[[[body:libc__getch]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_getch"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getch]]]*/

/*[[[head:libc__getch_nolock,hash:CRC-32=0x34c07390]]]*/
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getch_nolock)(void)
/*[[[body:libc__getch_nolock]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_getch_nolock"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getch_nolock]]]*/

/*[[[head:libc__getche,hash:CRC-32=0x6705b2e5]]]*/
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getche)(void)
/*[[[body:libc__getche]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_getche"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getche]]]*/

/*[[[head:libc__getche_nolock,hash:CRC-32=0x36ea2394]]]*/
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getche_nolock)(void)
/*[[[body:libc__getche_nolock]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_getche_nolock"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getche_nolock]]]*/


/*[[[start:exports,hash:CRC-32=0x4c976570]]]*/
DEFINE_PUBLIC_ALIAS(_kbhit, libc__kbhit);
DEFINE_PUBLIC_ALIAS(_getch, libc__getch);
DEFINE_PUBLIC_ALIAS(_getch_nolock, libc__getch_nolock);
DEFINE_PUBLIC_ALIAS(_getche, libc__getche);
DEFINE_PUBLIC_ALIAS(_getche_nolock, libc__getche_nolock);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CONIO_C */
