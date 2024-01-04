/* HASH CRC-32:0xd0368a27 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_c32repeat_defined
#define __local_format_c32repeat_defined
#include <__crt.h>
#include <bits/crt/uformat-printer.h>
#include <hybrid/__alloca.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_c32repeat) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_CB(__LIBKCALL __LIBC_LOCAL_NAME(format_c32repeat))(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions) {
	__SSIZE_TYPE__ __result, __temp;
#ifdef __hybrid_alloca
	__CHAR32_TYPE__ *__buffer;
	if __likely(__num_repetitions <= 64) {
		__buffer = (__CHAR32_TYPE__ *)__hybrid_alloca(__num_repetitions * sizeof(__CHAR32_TYPE__));
		__libc_memsetc(__buffer, __ch, __num_repetitions, 4);
		return (*__printer)(__arg, __buffer, __num_repetitions);
	}
	__buffer = (__CHAR32_TYPE__ *)__hybrid_alloca(64 * sizeof(__CHAR32_TYPE__));
	__libc_memsetc(__buffer, __ch, 64, 4);
#else /* __hybrid_alloca */
	__CHAR32_TYPE__ __buffer[64];
	if __likely(__num_repetitions <= 64) {
		__libc_memsetc(__buffer, __ch, __num_repetitions, 4);
		return (*__printer)(__arg, __buffer, __num_repetitions);
	}
	__libc_memsetc(__buffer, __ch, 64, 4);
#endif /* !__hybrid_alloca */
	__result = (*__printer)(__arg, __buffer, 64);
	if __unlikely(__result < 0)
		goto __done;
	for (;;) {
		__num_repetitions -= 64;
		if (__num_repetitions < 64)
			break;
		__temp = (*__printer)(__arg, __buffer, 64);
		if __unlikely(__temp < 0)
			goto __done;
		__result += __temp;
	}
	if (__num_repetitions) {
		__temp = (*__printer)(__arg, __buffer, __num_repetitions);
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
__done:
	return __result;
__err:
	return __temp;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_c32repeat_defined
#define __local___localdep_format_c32repeat_defined
#define __localdep_format_c32repeat __LIBC_LOCAL_NAME(format_c32repeat)
#endif /* !__local___localdep_format_c32repeat_defined */
#endif /* !__local_format_c32repeat_defined */
