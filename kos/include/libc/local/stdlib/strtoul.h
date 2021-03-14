/* HASH CRC-32:0x5c5d2b54 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtoul_defined
#define __local_strtoul_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtou32 from stdlib */
#ifndef __local___localdep_strtou32_defined
#define __local___localdep_strtou32_defined 1
#ifdef __CRT_HAVE_strtou32
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
#define __localdep_strtou32 __LIBC_LOCAL_NAME(strtou32)
#endif /* !... */
#endif /* !__local___localdep_strtou32_defined */
/* Dependency: strtou64 from stdlib */
#ifndef __local___localdep_strtou64_defined
#define __local___localdep_strtou64_defined 1
#ifdef __CRT_HAVE_strtou64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
#define __localdep_strtou64 __LIBC_LOCAL_NAME(strtou64)
#endif /* !... */
#endif /* !__local___localdep_strtou64_defined */
__LOCAL_LIBC(strtoul) __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoul))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)__localdep_strtou32(__nptr, __endptr, __base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)__localdep_strtou64(__nptr, __endptr, __base);
#endif /* __SIZEOF_LONG__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoul_defined
#define __local___localdep_strtoul_defined 1
#define __localdep_strtoul __LIBC_LOCAL_NAME(strtoul)
#endif /* !__local___localdep_strtoul_defined */
#endif /* !__local_strtoul_defined */
