/* HASH CRC-32:0x11e64e00 */
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
#ifndef __local_getdtablesize_defined
#define __local_getdtablesize_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdtablesize) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getdtablesize))(void) {
#line 1429 "kos/src/libc/magic/unistd.c"
#if defined(__KOS__)
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(__linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else
	return 256;        /* UINT8_MAX + 1 */
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_getdtablesize_defined */
