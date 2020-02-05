/* HASH CRC-32:0xe08ffa8c */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_c32hexdump_defined
#define __local_format_c32hexdump_defined 1
#include <bits/format-printer.h>
#include <bits/format-printer.h>
#include <hybrid/__alloca.h>

#include <hybrid/__unaligned.h>

#include <hybrid/byteorder.h>
/* Dependency: "format_wrepeat" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_c32repeat_defined
#define ____localdep_format_c32repeat_defined 1
#if defined(__CRT_HAVE_format_wrepeat) && (__SIZEOF_WCHAR_T__ == 4)
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32repeat,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wrepeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
#define __localdep_format_c32repeat(printer, arg, ch, num_repetitions) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)(printer), arg, (__WCHAR_TYPE__)(ch), num_repetitions)
#else /* LIBC: format_c32repeat */
#include <local/parts.wchar.format-printer/format_c32repeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
#define __localdep_format_c32repeat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32repeat))
#endif /* format_c32repeat... */
#endif /* !____localdep_format_c32repeat_defined */

/* Dependency: "iswprint" from "wctype" */
#ifndef ____localdep_iswprint_defined
#define ____localdep_iswprint_defined 1
#if __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswprint,(__WINT_TYPE__ __wc),iswprint,{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswprint,(__WINT_TYPE__ __wc),iswprint,(__wc))
#else /* LIBC: iswprint */
#include <local/wctype/iswprint.h>
#define __localdep_iswprint (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint))
#endif /* iswprint... */
#endif /* !____localdep_iswprint_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__LOCAL_LIBC(format_c32hexdump) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_c32hexdump))(__pc32formatprinter __printer,
                                                               void *__arg,
                                                               void const *__restrict __data,
                                                               __SIZE_TYPE__ __size,
                                                               __SIZE_TYPE__ __linesize,
                                                               unsigned int __flags) {
#line 507 "kos/src/libc/magic/format-printer.c"
#ifndef __FORMAT_HEXDUMP_FNORMAL
#define __FORMAT_HEXDUMP_FNORMAL    0x0000 /* Normal hexdump flags. */
#define __FORMAT_HEXDUMP_FHEXLOWER  0x0001 /* Print hex text of the dump in lowercase (does not affect address/offset). */
#define __FORMAT_HEXDUMP_FNOADDRESS 0x0002 /* Don't include the absolute address at the start of every line. */
#define __FORMAT_HEXDUMP_FOFFSETS   0x0004 /* Include offsets from the base address at the start of every line (after the address when also shown). */
#define __FORMAT_HEXDUMP_FNOHEX     0x0008 /* Don't print the actual hex dump (hex data representation). */
#define __FORMAT_HEXDUMP_FNOASCII   0x0010 /* Don't print ascii representation of printable characters at the end of lines. */
#define __FORMAT_HEXDUMP_BYTES      0x0000 /* Dump data as bytes. */
#define __FORMAT_HEXDUMP_WORDS      0x1000 /* Dump data as words (uint16_t). */
#define __FORMAT_HEXDUMP_DWORDS     0x2000 /* Dump data as dwords (uint32_t). */
#define __FORMAT_HEXDUMP_QWORDS     0x3000 /* Dump data as qwords (uint64_t). */
#define __FORMAT_HEXDUMP_SIZEMASK   0x3000 /* Mask for the dump size. */
#endif /* !FORMAT_HEXDUMP_FNORMAL */
#ifndef __DECIMALS_SELECTOR
#define __LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define __DECIMALS_SELECTOR  __decimals
	__PRIVATE char const __decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE __CHAR32_TYPE__ const __lf[1] = { '\n' };
	char const *__dec;
	__BYTE_TYPE__ const *__line_data;
	__CHAR32_TYPE__ __buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *__dst;
	__SSIZE_TYPE__ __temp, __result = 0;
	unsigned int __i; __UINTPTR_TYPE__ __value;
	unsigned int __offset_digits = 0;
	if (!__size) goto __done;
	if (!__linesize) __linesize = 16;
	__dec = __DECIMALS_SELECTOR[!(__flags & __FORMAT_HEXDUMP_FHEXLOWER)];
	if (__flags & __FORMAT_HEXDUMP_FOFFSETS) {
		__value = __size;
		do ++__offset_digits;
		while ((__value >>= 4) != 0);
	}
	__line_data = (__BYTE_TYPE__ const *)__data;
	for (;;) {
		__SIZE_TYPE__ __line_len = __linesize;
		if (__line_len > __size)
			__line_len = __size;
		if (!(__flags & __FORMAT_HEXDUMP_FNOADDRESS)) {
			__value = (__UINTPTR_TYPE__)__line_data;
			__dst = __buffer + sizeof(void *) * 2;
			*__dst = ' ';
			while (__dst > __buffer) {
				*--__dst = __dec[__value & 0xf];
				__value >>= 4;
			}
			__temp = (*__printer)(__arg, __buffer, (sizeof(void *) * 2) + 1);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		if (__flags & __FORMAT_HEXDUMP_FOFFSETS) {
			__dst = __buffer + 1 + __offset_digits;
			*__dst = ' ';
			__value = (__line_data - (__BYTE_TYPE__ const *)__data);
			while (__dst > __buffer + 1) {
				*--__dst = __dec[__value & 0xf];
				__value >>= 4;
			}
			__buffer[0] = '+';
			__temp = (*__printer)(__arg, __buffer, 2 + __offset_digits);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		if (!(__flags & __FORMAT_HEXDUMP_FNOHEX)) {
			__SIZE_TYPE__ __i = 0;
			__SIZE_TYPE__ __tailspace_count;
			switch (__flags & __FORMAT_HEXDUMP_SIZEMASK) {
			default:
				__tailspace_count = __linesize * 3;
				break;
			case __FORMAT_HEXDUMP_WORDS:
				__tailspace_count = (__linesize / 2) * 5 + (__linesize % 2) * 3;
				__buffer[4] = ' ';
				for (; __i + 2 <= __line_len; __i += 2) {
					__UINT16_TYPE__ __w = __hybrid_unaligned_get16((__UINT16_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 4;
					while (__dst > __buffer) {
						*--__dst = __dec[__w & 0xf];
						__w >>= 4;
					}
					__temp = (*__printer)(__arg, __buffer, 5);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					__tailspace_count -= 5;
				}
				break;
			case __FORMAT_HEXDUMP_DWORDS:
				__tailspace_count = (__linesize / 4) * 9 + (__linesize % 4) * 3;
				__buffer[8] = ' ';
				for (; __i + 4 <= __line_len; __i += 4) {
					__UINT32_TYPE__ __l = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 8;
					while (__dst > __buffer) {
						*--__dst = __dec[__l & 0xf];
						__l >>= 4;
					}
					__temp = (*__printer)(__arg, __buffer, 9);
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
					__tailspace_count -= 9;
				}
				break;
			case __FORMAT_HEXDUMP_QWORDS:
				__tailspace_count = (__linesize / 8) * 17 + (__linesize % 8) * 3;
				__buffer[16] = ' ';
				for (; __i + 8 <= __line_len; __i += 8) {
#if __SIZEOF_POINTER__ >= 8
					__UINT64_TYPE__ __q = __hybrid_unaligned_get64((__UINT64_TYPE__ *)(__line_data + __i));
					__dst = __buffer + 16;
					while (__dst > __buffer) {
						*--__dst = __dec[__q & 0xf];
						__q >>= 4;
					}
#else
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					__UINT32_TYPE__ __b = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
					__UINT32_TYPE__ __a = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i + 4));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					__UINT32_TYPE__ __a = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i));
					__UINT32_TYPE__ __b = __hybrid_unaligned_get32((__UINT32_TYPE__ *)(__line_data + __i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					__dst = __buffer + 16;
					while (__dst > __buffer + 8) {
						*--__dst = __dec[__b & 0xf];
						__b >>= 4;
					}
					while (__dst > __buffer) {
						*--__dst = __dec[__a & 0xf];
						__a >>= 4;
					}
#endif
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
				__buffer[0] = __dec[__b >> 4];
				__buffer[1] = __dec[__b & 0xf];
				__temp = (*__printer)(__arg, __buffer, 3);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__tailspace_count -= 3;
			}
			if (__tailspace_count) {
				__temp = __localdep_format_c32repeat(__printer, __arg, ' ', __tailspace_count);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
		}
		if (!(__flags & __FORMAT_HEXDUMP_FNOASCII)) {
			for (__i = 0; __i < __line_len; ++__i) {
				__BYTE_TYPE__ __b = __line_data[__i];
				if (!__localdep_iswprint(__b))
					__b = '.';
				__temp = (*__printer)(__arg, (__CHAR32_TYPE__ const *)&__b, 1);
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
#ifdef __LOCAL_DECIMALS_SELECTOR_DEFINED
#undef __LOCAL_DECIMALS_SELECTOR_DEFINED
#undef __DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_c32hexdump_defined */
