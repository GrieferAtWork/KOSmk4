/* HASH CRC-32:0x6292252b */
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
#ifndef __local_cfgetospeed_defined
#define __local_cfgetospeed_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfgetospeed) __ATTR_WUNUSED __ATTR_NONNULL((1)) speed_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfgetospeed))(struct termios const *__restrict __termios_p) {
#line 52 "kos/src/libc/magic/termios.c"
	return __termios_p->c_ospeed;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_cfgetospeed_defined */
