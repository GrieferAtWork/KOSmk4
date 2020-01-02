/* HASH CRC-32:0x65c23e89 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef __local_gnu_dev_makedev_defined
#define __local_gnu_dev_makedev_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gnu_dev_makedev) __ATTR_CONST __ATTR_WUNUSED __dev_t
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(gnu_dev_makedev))(__major_t __major,
                                                         __minor_t __minor) {
#line 47 "kos/src/libc/magic/sys.sysmacros.c"
	return (__dev_t)__major << 20 | (__dev_t)__minor;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_gnu_dev_makedev_defined */
