/* HASH CRC-32:0x7c00cf2d */
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
#ifndef __local_format_wrepeat_defined
#define __local_format_wrepeat_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <bits/format-printer.h>
#include <hybrid/__alloca.h>
/* Dependency: "wmemset" from "wchar" */
#ifndef ____localdep_wmemset_defined
#define ____localdep_wmemset_defined 1
#if defined(__CRT_HAVE_wmemset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* LIBC: wmemset */
#include <local/wchar/wmemset.h>
#define __localdep_wmemset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))
#endif /* wmemset... */
#endif /* !____localdep_wmemset_defined */

/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#if defined(__fast_memset_defined)
/* Fill memory with a given byte */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

__NAMESPACE_LOCAL_BEGIN
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__LOCAL_LIBC(format_wrepeat) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_wrepeat))(__pwformatprinter __printer,
                                                            void *__arg,
                                                            __WCHAR_TYPE__ __ch,
                                                            __SIZE_TYPE__ __num_repetitions) {
#line 93 "kos/src/libc/magic/format-printer.c"
#ifndef __FORMAT_REPEAT_BUFSIZE
#define __FORMAT_REPEAT_BUFSIZE 64
#endif
	__SSIZE_TYPE__ __result, __temp;
#ifndef __NO_hybrid_alloca
	__WCHAR_TYPE__ *__buffer;
	if __likely(__num_repetitions <= __FORMAT_REPEAT_BUFSIZE) {
		__buffer = (__WCHAR_TYPE__ *)__hybrid_alloca(__num_repetitions);

		__localdep_wmemset(__buffer, __ch, __num_repetitions);



		return (*__printer)(__arg, __buffer, __num_repetitions);
	}
	__buffer = (__WCHAR_TYPE__ *)__hybrid_alloca(__FORMAT_REPEAT_BUFSIZE);
	__localdep_memset(__buffer, __ch, __FORMAT_REPEAT_BUFSIZE);
#else
	__WCHAR_TYPE__ __buffer[__FORMAT_REPEAT_BUFSIZE];
	if __likely(__num_repetitions <= __FORMAT_REPEAT_BUFSIZE) {

		__localdep_wmemset(__buffer, __ch, __num_repetitions);



		return (*__printer)(__arg, __buffer, __num_repetitions);
	}
	__localdep_memset(__buffer, __ch, __FORMAT_REPEAT_BUFSIZE);
#endif
	__result = (*__printer)(__arg, __buffer, __FORMAT_REPEAT_BUFSIZE);
	if __unlikely(__result < 0)
		goto __done;
	for (;;) {
		__num_repetitions -= __FORMAT_REPEAT_BUFSIZE;
		if (__num_repetitions < __FORMAT_REPEAT_BUFSIZE)
			break;
		__temp = (*__printer)(__arg, __buffer, __FORMAT_REPEAT_BUFSIZE);
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
#endif /* !__local_format_wrepeat_defined */
