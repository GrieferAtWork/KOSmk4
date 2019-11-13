/* HASH CRC-32:0x2bdc6e50 */
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
#ifndef __local_wcwidth_defined
#define __local_wcwidth_defined 1
#include <libc/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcwidth) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcwidth))(__WCHAR_TYPE__ __ch) {
#line 870 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	if (__ch >= 0xd800 &&
	    __ch <= 0xdfff)
		return 0;
#endif /* __SIZEOF_WCHAR_T__ == 2 */
	if (__libc_unicode_isprint(__ch))
		return 1;
	if (__ch == 0)
		return 0;
	return -1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcwidth_defined */
