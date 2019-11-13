/* HASH CRC-32:0x9fdbacfd */
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
#ifndef __local_cfmakeraw_defined
#define __local_cfmakeraw_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__LOCAL_LIBC(cfmakeraw) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakeraw))(struct termios *__restrict __termios_p) {
#line 100 "kos/src/libc/magic/termios.c"
	/* As documented here: http://man7.org/linux/man-pages/man3/termios.3.html
	 * Note that the following additions were made:
	 *  - Clear `IXOFF' (ensuring that TTY output can be streamed)
	 *  - Always set `CREAD' (ensuring that data can be received) */
	__termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
	                          INLCR | IGNCR | ICRNL | IXON | IXOFF);
	__termios_p->c_oflag &= ~(OPOST);
	__termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	__termios_p->c_cflag &= ~(CSIZE | PARENB);
	__termios_p->c_cflag |= CS8 | CREAD;
	__termios_p->c_cc[VMIN]  = 1; /* Read returns when one byte was read. */
	__termios_p->c_cc[VTIME] = 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_cfmakeraw_defined */
