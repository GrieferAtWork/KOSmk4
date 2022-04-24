/* HASH CRC-32:0xa00c8854 */
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
#ifndef __local_l64a_r_defined
#define __local_l64a_r_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(l64a_r) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(l64a_r))(long __n, char *__buf, __STDC_INT_AS_SIZE_T __bufsize) {
	unsigned long __un;
	/* Mapping from digit values --> base-64 characters. */
	static char const __chrs[64] = {
		'.', '/', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', 'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};
	__un = (unsigned long )__n;
	while (__bufsize) {
		--__bufsize;
		if (!__un) {
			/* Done! */
			*__buf = '\0';
			return 0;
		}
		/* Encode 1 character. */
		*__buf++ = __chrs[__un & 0x3f];
		__un >>= 6;
	}
	return -1;

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_l64a_r_defined
#define __local___localdep_l64a_r_defined
#define __localdep_l64a_r __LIBC_LOCAL_NAME(l64a_r)
#endif /* !__local___localdep_l64a_r_defined */
#endif /* !__local_l64a_r_defined */
