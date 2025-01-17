/* HASH CRC-32:0x465a9dd */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_regsubprintv_defined
#define __local_regsubprintv_defined
#include <__crt.h>
#include <bits/crt/format-printer.h>
#include <bits/crt/regex.h>
#include <bits/os/iovec.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(regsubprintv) __ATTR_IN(3) __ATTR_INS(6, 5) __ATTR_NONNULL((1, 4)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(regsubprintv))(__pformatprinter __printer, void *__arg, char const *__sed_format, struct iovec const *__srcbase, __SIZE_TYPE__ __nmatch, struct __regmatch const __pmatch[__restrict_arr]) {
	__SIZE_TYPE__ __imatch;
	__SSIZE_TYPE__ __temp, __result = 0;
	char __ch;
	char const *__flush_start;
	__flush_start = __sed_format;
__again:
	__ch = *__sed_format++;
	switch (__ch) {

	case '\0':
		--__sed_format;
		break;

	case '&':
		__imatch = 0;
__insert_imatch:
		/* Flush until the start of the insert-sequence */
		--__sed_format;
		if (__sed_format > __flush_start) {
			__temp = (*__printer)(__arg, __flush_start, (__SIZE_TYPE__)(__sed_format - __flush_start));
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		if (*__sed_format == '\\')
			++__sed_format;
		++__sed_format;
		__flush_start = __sed_format;

		/* Insert the `imatch'th element from `pmatch' */
		if (__imatch < __nmatch && (__pmatch[__imatch].rm_so != (__regoff_t)-1 &&
		                        __pmatch[__imatch].rm_eo != (__regoff_t)-1)) {
			__SIZE_TYPE__ __offset, __count;
			__offset = (__SIZE_TYPE__)__pmatch[__imatch].rm_so;
			__count  = (__SIZE_TYPE__)(__pmatch[__imatch].rm_eo - __pmatch[__imatch].rm_so);
			if (__count > 0) {
				/* Seek until the first source iov item. */
				struct iovec const *__iov = __srcbase;
				while (__offset >= __iov->iov_len) {
					__offset -= __iov->iov_len;
					++__iov;
				}
				/* Print the next `count' bytes starting at `iov[+offset]' */
				for (;;) {
					__SIZE_TYPE__ __partlen;
					__partlen = __iov->iov_len - __offset;
					if (__partlen > __count)
						__partlen = __count;
					__temp = (*__printer)(__arg, (char const *)((__BYTE_TYPE__ const *)__iov->iov_base + __offset), __partlen);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					if (__partlen >= __count)
						break;
					__count -= __partlen;
					__offset = 0;
					++__iov;
				}
			}
		}
		goto __again;

	case '\\':
		__ch = *__sed_format;
		if (__ch >= '0' && __ch <= '9') {
			__imatch = (__SIZE_TYPE__)(__ch - '0');
			goto __insert_imatch;
		} else if (__ch == '&' || __ch == '\\') {
			/* Escaped character */
			--__sed_format;
			if (__sed_format > __flush_start) {
				__temp = (*__printer)(__arg, __flush_start, (__SIZE_TYPE__)(__sed_format - __flush_start));
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			++__sed_format;
			__flush_start = __sed_format; /* Flush the escaped char the next time around */
			++__sed_format;
		}
		goto __again;

	default:
		goto __again;
	}

	/* Flush any left-over remainder. */
	if (__sed_format > __flush_start) {
		__temp = (*__printer)(__arg, __flush_start, (__SIZE_TYPE__)(__sed_format - __flush_start));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	return __result;
__err:
	return __temp;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regsubprintv_defined
#define __local___localdep_regsubprintv_defined
#define __localdep_regsubprintv __LIBC_LOCAL_NAME(regsubprintv)
#endif /* !__local___localdep_regsubprintv_defined */
#endif /* !__local_regsubprintv_defined */
