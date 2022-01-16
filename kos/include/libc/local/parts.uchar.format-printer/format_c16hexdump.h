/* HASH CRC-32:0xb36d338f */
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
#ifndef __local_format_c16hexdump_defined
#define __local_format_c16hexdump_defined
#include <__crt.h>
#include <kos/anno.h>
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_c16repeat_defined
#define __local___localdep_format_c16repeat_defined
#if defined(__CRT_HAVE_format_wrepeat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16repeat,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif defined(__CRT_HAVE_DOS$format_wrepeat)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16repeat,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_wrepeat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16repeat __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBDCALL*)(__pc16formatprinter,void *,__CHAR16_TYPE__,__SIZE_TYPE__),__SSIZE_TYPE__(__LIBDCALL&)(__pc16formatprinter,void *,__CHAR16_TYPE__,__SIZE_TYPE__),format_wrepeat)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c16repeat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16repeat __LIBC_LOCAL_NAME(format_c16repeat)
#endif /* !... */
#endif /* !__local___localdep_format_c16repeat_defined */
#ifndef __local___localdep_isprint16_defined
#define __local___localdep_isprint16_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswprint) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,__localdep_isprint16,(__WINT16_TYPE__ __wc),iswprint,{ return __crt_iswprint(__wc); })
#elif defined(__crt_iswprint) && __SIZEOF_WCHAR_T__ == 2
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL __localdep_isprint16)(__WINT16_TYPE__ __wc) { return __crt_iswprint(__wc); }
#elif __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,__localdep_isprint16,(__WINT16_TYPE__ __wc),iswprint,{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint16,(__WINT16_TYPE__ __wc),iswprint,(__wc))
#elif defined(__CRT_HAVE_DOS$iswprint)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint16,(__WINT16_TYPE__ __wc),iswprint,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint16 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__WINT16_TYPE__),int(__LIBDCALL&)(__WINT16_TYPE__),iswprint)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isprint16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint16 __LIBC_LOCAL_NAME(isprint16)
#endif /* !... */
#endif /* !__local___localdep_isprint16_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__alloca.h>
#include <hybrid/__unaligned.h>
#include <hybrid/byteorder.h>
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_c16hexdump) __ATTR_NONNULL((1)) __SSIZE_TYPE__
(__LIBDCALL __LIBC_LOCAL_NAME(format_c16hexdump))(__pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) __THROWS(...) {
	__PRIVATE __CHAR16_TYPE__ const __lf[1] = { '\n' };
	__BYTE_TYPE__ const *__line_data;
	__CHAR16_TYPE__ __buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *__dst;
	__SSIZE_TYPE__ __temp, __result = 0;
	unsigned int __i; __UINTPTR_TYPE__ __value;
	unsigned int __offset_digits = 0;
	if (!__size) goto __done;
	if (!__linesize) __linesize = 16;
	if (__flags & 0x0004) {
		__value = __size;
		do {
			++__offset_digits;
		} while ((__value >>= 4) != 0);
	}
	__line_data = (__BYTE_TYPE__ const *)__data;
	for (;;) {
		__SIZE_TYPE__ __line_len = __linesize;
		if (__line_len > __size)
			__line_len = __size;
		if (!(__flags & 0x0002)) {
			__value = (__UINTPTR_TYPE__)__line_data;
			__dst = __buffer + sizeof(void *) * 2;
			*__dst = ' ';
			while (__dst > __buffer) {
				*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __value & 0xf);
				__value >>= 4;
			}
			__temp = (*__printer)(__arg, __buffer, (sizeof(void *) * 2) + 1);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		if (__flags & 0x0004) {
			__dst = __buffer + 1 + __offset_digits;
			*__dst = ' ';
			__value = (__line_data - (__BYTE_TYPE__ const *)__data);
			while (__dst > __buffer + 1) {
				*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __value & 0xf);
				__value >>= 4;
			}
			__buffer[0] = '+';
			__temp = (*__printer)(__arg, __buffer, (__SIZE_TYPE__)2 + __offset_digits);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		if (!(__flags & 0x0008)) {
			__SIZE_TYPE__ __i = 0;
			__SIZE_TYPE__ __tailspace_count;
			switch (__flags & 0x3000) {

			default:
				__tailspace_count = __linesize * 3;
				break;

			case 0x1000:
				__tailspace_count = (__linesize / 2) * 5 + (__linesize % 2) * 3;
				__buffer[4] = ' ';
				for (; __i + 2 <= __line_len; __i += 2) {
					__UINT16_TYPE__ __w = __hybrid_unaligned_get16((__UINT16_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 4;
					while (__dst > __buffer) {
						*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __w & 0xf);
						__w >>= 4;
					}
					__temp = (*__printer)(__arg, __buffer, 5);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					__tailspace_count -= 5;
				}
				break;

			case 0x2000:
				__tailspace_count = (__linesize / 4) * 9 + (__linesize % 4) * 3;
				__buffer[8] = ' ';
				for (; __i + 4 <= __line_len; __i += 4) {
					__UINT32_TYPE__ __l = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 8;
					while (__dst > __buffer) {
						*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __l & 0xf);
						__l >>= 4;
					}
					__temp = (*__printer)(__arg, __buffer, 9);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					__tailspace_count -= 9;
				}
				break;

			case 0x3000:
				__tailspace_count = (__linesize / 8) * 17 + (__linesize % 8) * 3;
				__buffer[16] = ' ';
				for (; __i + 8 <= __line_len; __i += 8) {
#if __SIZEOF_POINTER__ >= 8
					__UINT64_TYPE__ __q = __hybrid_unaligned_get64((__UINT64_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 16;
					while (__dst > __buffer) {
						*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __q & 0xf);
						__q >>= 4;
					}
#else /* __SIZEOF_POINTER__ >= 8 */
					__UINT32_TYPE__ __a, __b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					__a = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i + 4));
					__b = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					__a = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
					__b = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					__dst = __buffer + 16;
					while (__dst > __buffer + 8) {
						*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __b & 0xf);
						__b >>= 4;
					}
					while (__dst > __buffer) {
						*--__dst = __LOCAL_itoa_digit(!(__flags & 0x0001), __a & 0xf);
						__a >>= 4;
					}
#endif /* __SIZEOF_POINTER__ < 8 */
					__temp = (*__printer)(__arg, __buffer, 17);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					__tailspace_count -= 17;
				}
				break;
			}
			__buffer[2] = ' ';
			for (; __i < __line_len; ++__i) {
				__BYTE_TYPE__ __b = __line_data[__i];
				__buffer[0] = __LOCAL_itoa_digit(!(__flags & 0x0001), __b >> 4);
				__buffer[1] = __LOCAL_itoa_digit(!(__flags & 0x0001), __b & 0xf);
				__temp = (*__printer)(__arg, __buffer, 3);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__tailspace_count -= 3;
			}
			if (__tailspace_count) {
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_c16repeat)(__printer, __arg, ' ', __tailspace_count);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
		}
		if (!(__flags & 0x0010)) {
			for (__i = 0; __i < __line_len; ++__i) {
				__BYTE_TYPE__ __b = __line_data[__i];
				if (!(__NAMESPACE_LOCAL_SYM __localdep_isprint16)(__b))
					__b = '.';
				__temp = (*__printer)(__arg, (__CHAR16_TYPE__ const *)&__b, 1);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
		}
		if (__line_len >= __size)
			break;
		__line_data += __line_len;
		__size      -= __line_len;
		__temp = (*__printer)(__arg, __lf, 1);
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
#ifndef __local___localdep_format_c16hexdump_defined
#define __local___localdep_format_c16hexdump_defined
#define __localdep_format_c16hexdump __LIBC_LOCAL_NAME(format_c16hexdump)
#endif /* !__local___localdep_format_c16hexdump_defined */
#endif /* !__local_format_c16hexdump_defined */
