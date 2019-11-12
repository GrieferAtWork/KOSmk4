/* HASH CRC-32:0x4db78888 */
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
#ifndef __local_memfrob_defined
#define __local_memfrob_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memfrob) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memfrob))(void *__buf,
                                                     __SIZE_TYPE__ __num_bytes) {
#line 750 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__buf;
	while (__num_bytes--)
		*__iter++ ^= 42; /* -_-   yeah... */
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memfrob_defined */
