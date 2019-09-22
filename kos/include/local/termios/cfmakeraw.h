/* HASH CRC-32:0xd8b992 */
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
__LOCAL_LIBC(cfmakeraw) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakeraw))(struct termios *__restrict __termios_p) {
#line 88 "kos/src/libc/magic/termios.c"
	__termios_p->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
	__termios_p->c_oflag &= ~(OPOST);
	__termios_p->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
	__termios_p->c_cflag &= ~(CSIZE|PARENB);
	__termios_p->c_cflag |= CS8;
	__termios_p->c_cc[VMIN]  = 1; /* Read returns when one byte was read. */
	__termios_p->c_cc[VTIME] = 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_cfmakeraw_defined */
