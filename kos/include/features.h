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
#ifndef _FEATURES_H
#define _FEATURES_H 1

#include "__stdinc.h"
#include "__crt.h"
#include <hybrid/typecore.h>

//#undef __USE_KOS        /* __KOS_VERSION__ >= 100 */
//#undef __USE_KXS        /* __KOS_VERSION__ >= 200/300 */
//#undef __USE_KOS_KERNEL /* __KOS_VERSION__ >= 400 */
//#undef __USE_STRING_BWLQ
//#undef __USE_STRING_XCHR
//#undef __USE_XOPEN2K8
//#undef __USE_MISC
//#undef __USE_GNU
//#undef __USE_DOS
//#undef __USE_XOPEN2K
//#undef __USE_ISOC99
//#undef __CORRECT_ISO_CPP_STRING_H_PROTO
//#undef __USE_CTYPE_MACROS


#ifdef _KOS_SOURCE
#define __USE_KOS 1
#define __USE_STRING_BWLQ 1
#define __USE_STRING_XCHR 1
#endif /* _KOS_SOURCE */

#if defined(_KOS_KERNEL_SOURCE) || \
   (defined(__KOS__) && defined(__KERNEL__))
#define __USE_KOS_KERNEL 1
#endif /* _KOS_KERNEL_SOURCE || (__KOS__ && __KERNEL__) */

#ifdef _STRING_BWLQ_SOURCE
#define __USE_STRING_BWLQ 1
#endif /* _STRING_BWLQ_SOURCE */

#ifdef _STRING_XCHR_SOURCE
#define __USE_STRING_XCHR 1
#endif /* _STRING_XCHR_SOURCE */


/* In C++, still define ctype macros. */
#ifdef _CTYPE_MACRO_SOURCE
#define __USE_CTYPE_MACROS 1
#endif /* _CTYPE_MACRO_SOURCE */

#ifdef _DOS_SOURCE
#if (_DOS_SOURCE+0) != 0
#define __USE_DOS 1
#define __USE_DOS_SLIB 1
#endif
#elif defined(_MSC_VER)
#define __USE_DOS 1
#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__ 1
#endif
#if (__STDC_WANT_SECURE_LIB__+0) != 0
#define __USE_DOS_SLIB 1
#endif
#endif

/* 64-bit time_t extensions for KOS
 * (By the time of this writing, but I'm guessing by 2038 this'll be
 *  similar to what glibc will have to do if it doesn't wan'na roll over) */
#ifdef _TIME64_SOURCE
#define __USE_TIME64 1
#endif
#ifdef _TIME_T_BITS
#if (_TIME_T_BITS+0) == 64
#define __USE_TIME_BITS64 1
#else
#undef __USE_TIME_BITS64
#endif
#elif defined(_USE_32BIT_TIME_T)
#undef __USE_TIME_BITS64
#elif defined(_USE_64BIT_TIME_T)
#define __USE_TIME_BITS64 1
#elif defined(__USE_DOS) || defined(__USE_KOS_KERNEL)
#define __USE_TIME_BITS64 1
#endif

#if (defined(_BSD_SOURCE) || defined(_SVID_SOURCE)) && \
    !defined(_DEFAULT_SOURCE)
#undef  _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#endif

#ifdef _GNU_SOURCE
#undef  _ISOC95_SOURCE
#define _ISOC95_SOURCE 1
#undef  _ISOC99_SOURCE
#define _ISOC99_SOURCE 1
#undef  _ISOC11_SOURCE
#define _ISOC11_SOURCE 1
#undef  _POSIX_SOURCE
#define _POSIX_SOURCE 1
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#undef  _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#undef  _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#undef  _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#undef  _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef  _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#endif

#if (defined(_DEFAULT_SOURCE) || (!defined(__STRICT_ANSI__) && !defined(_ISOC99_SOURCE) && \
    !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)))
#undef  _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#endif

#if (defined(_ISOC11_SOURCE) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L))
#define __USE_ISOC11 1
#endif
#if (defined(_ISOC99_SOURCE) || defined(_ISOC11_SOURCE) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L))
#define __USE_ISOC99 1
#endif
#if (defined(_ISOC99_SOURCE) || defined(_ISOC11_SOURCE) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L))
#define __USE_ISOC95 1
#endif
#if (defined(_ISOCXX11_SOURCE) || defined(_ISOCXX14_SOURCE)) || \
     defined(__GXX_EXPERIMENTAL_CXX0X__) || \
    (defined(__cplusplus) && __cplusplus >= 201103L)
#define __USE_ISOCXX11 1
#endif
#if defined(_ISOCXX14_SOURCE) || \
   (defined(__cplusplus) && __cplusplus >= 201103L)
#define __USE_ISOCXX14 1
#endif
#if defined(_ISOCXX17_SOURCE) || \
   (defined(__cplusplus) && __cplusplus >= 201703L)
#define __USE_ISOCXX17 1
#endif
#if defined(__cplusplus) && \
  (!defined(__GNUC__) || __GCC_VERSION(4,4,0))
/* Enable proper C++ prototype declarations. */
#define __CORRECT_ISO_CPP_STRING_H_PROTO  1
#define __CORRECT_ISO_CPP_STRINGS_H_PROTO 1
#define __CORRECT_ISO_CPP_WCHAR_H_PROTO   1
#define __CORRECT_ISO_CPP_STDLIB_H_PROTO  1
#define __CORRECT_ISO_CPP_UNICODE_H_PROTO 1
#define __CORRECT_ISO_CPP_MATH_H_PROTO    1
#endif

#ifdef _DEFAULT_SOURCE
#if !defined(_POSIX_SOURCE) && \
    !defined(_POSIX_C_SOURCE)
#define __USE_POSIX_IMPLICITLY 1
#endif
#undef  _POSIX_SOURCE
#define _POSIX_SOURCE 1
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#if (!defined(__STRICT_ANSI__) || \
     (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 >= 500)) && \
     !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define _POSIX_SOURCE 1
#if defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 500
#define _POSIX_C_SOURCE 2
#elif defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 600
#define _POSIX_C_SOURCE 199506L
#elif defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 700
#define _POSIX_C_SOURCE 200112L
#else
#define _POSIX_C_SOURCE 200809L
#endif
#define __USE_POSIX_IMPLICITLY 1
#endif

#if defined(_POSIX_SOURCE) || \
   (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 1) || \
    defined(_XOPEN_SOURCE)
# define __USE_POSIX 1
#endif

#if defined(_XOPEN_SOURCE) || \
   (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 2)
# define __USE_POSIX2 1
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 199309L
# define __USE_POSIX199309 1
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 199506L
# define __USE_POSIX199506 1
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 200112L
# define __USE_XOPEN2K  1
# undef __USE_ISOC95
# define __USE_ISOC95  1
# undef __USE_ISOC99
# define __USE_ISOC99  1
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 >= 200809L
# define __USE_XOPEN2K8  1
# undef  _ATFILE_SOURCE
# define _ATFILE_SOURCE 1
#endif

#ifdef _XOPEN_SOURCE
# define __USE_XOPEN 1
# if _XOPEN_SOURCE+0 >= 500
#  define __USE_XOPEN_EXTENDED 1
#  define __USE_UNIX98 1
#  undef _LARGEFILE_SOURCE
#  define _LARGEFILE_SOURCE 1
#  if _XOPEN_SOURCE+0 >= 600
#   if _XOPEN_SOURCE+0 >= 700
#    define __USE_XOPEN2K8 1
#    define __USE_XOPEN2K8XSI 1
#   endif
#   define __USE_XOPEN2K 1
#   define __USE_XOPEN2KXSI 1
#   undef __USE_ISOC95
#   define __USE_ISOC95  1
#   undef __USE_ISOC99
#   define __USE_ISOC99  1
#  endif
# else
#  ifdef _XOPEN_SOURCE_EXTENDED
#   define __USE_XOPEN_EXTENDED 1
#  endif
# endif
#endif

#ifdef _LARGEFILE_SOURCE
#define __USE_LARGEFILE 1
#endif
#ifdef _LARGEFILE64_SOURCE
#define __USE_LARGEFILE64 1
#endif
#ifdef _FILE_OFFSET_BITS
#if (_FILE_OFFSET_BITS+0) == 64
#define __USE_FILE_OFFSET64 1
#endif
#elif defined(__USE_KOS_KERNEL)
#define __USE_FILE_OFFSET64 1
#endif
#ifdef _DEFAULT_SOURCE
#define __USE_MISC 1
#endif
#ifdef _ATFILE_SOURCE
#define __USE_ATFILE 1
#endif
#ifdef _GNU_SOURCE
#define __USE_GNU 1
#endif
#if (defined(_REENTRANT) || defined(_THREAD_SAFE)) || \
    (defined(__CRT_CYG) && defined(__DYNAMIC_REENT__) && !defined(__SINGLE_THREAD__))
#define __USE_REENTRANT 1
#endif

/* Enable additional utf16/32 functions in system headers. */
#ifdef _UTF_SOURCE
#undef __USE_UTF
#define __USE_UTF 1
#endif


#ifdef _ALL_SOURCE
#undef __USE_KOS
#undef __USE_STRING_BWLQ
#undef __USE_STRING_XCHR
#undef __USE_KOS_KERNEL
#undef __USE_CTYPE_MACROS
#undef __USE_DOS
#undef __USE_DOS_SLIB
#undef __USE_TIME64
#undef __USE_ISOC11
#undef __USE_ISOC99
#undef __USE_ISOC95
#undef __USE_ISOCXX11
#undef __USE_ISOCXX14
#undef __USE_ISOCXX17
#undef __USE_POSIX_IMPLICITLY
#undef __USE_POSIX
#undef __USE_POSIX2
#undef __USE_POSIX199309
#undef __USE_POSIX199506
#undef __USE_XOPEN2K
#undef __USE_XOPEN2K8
#undef __USE_XOPEN
#undef __USE_XOPEN_EXTENDED
#undef __USE_UNIX98
#undef __USE_XOPEN2K8XSI
#undef __USE_XOPEN2KXSI
#undef __USE_LARGEFILE
#undef __USE_LARGEFILE64
#undef __USE_MISC
#undef __USE_ATFILE
#undef __USE_GNU
#undef __USE_REENTRANT
#undef __USE_UTF

#define __USE_KOS 1
#define __USE_STRING_BWLQ 1
#define __USE_STRING_XCHR 1
#define __USE_KOS_KERNEL 1
#define __USE_CTYPE_MACROS 1
#define __USE_DOS 1
#define __USE_DOS_SLIB 1
#define __USE_TIME64 1
#define __USE_ISOC11 1
#define __USE_ISOC99 1
#define __USE_ISOC95 1
#define __USE_ISOCXX11 1
#define __USE_ISOCXX14 1
#define __USE_ISOCXX17 1
#define __USE_POSIX 1
#define __USE_POSIX2 1
#define __USE_POSIX199309 1
#define __USE_POSIX199506 1
#define __USE_XOPEN2K  1
#define __USE_XOPEN2K8  1
#define __USE_XOPEN 1
#define __USE_XOPEN_EXTENDED 1
#define __USE_UNIX98 1
#define __USE_XOPEN2K8XSI 1
#define __USE_XOPEN2KXSI 1
#define __USE_LARGEFILE 1
#define __USE_LARGEFILE64 1
#define __USE_MISC 1
#define __USE_ATFILE 1
#define __USE_GNU 1
#define __USE_REENTRANT 1
#define __USE_UTF 1
#endif /* _ALL_SOURCE */



#if !defined(__KERNEL__) || !defined(__KOS__)
#ifdef __USE_FILE_OFFSET64
#   define __FS_TYPE(x)      __##x##64_t
#   define __FS_SIZEOF(x)    __SIZEOF_##x##64_T__
#   define __FS_ALTTYPE(x)   __##x##32_t
#   define __FS_ALTSIZEOF(x) __SIZEOF_##x##32_T__
#else
#   define __FS_TYPE(x)      __##x##32_t
#   define __FS_SIZEOF(x)    __SIZEOF_##x##32_T__
#   define __FS_ALTTYPE(x)   __##x##64_t
#   define __FS_ALTSIZEOF(x) __SIZEOF_##x##64_T__
#endif
#ifdef __USE_TIME_BITS64
#   define __TM_TYPE(x)      __##x##64_t
#   define __TM_SIZEOF(x)    __SIZEOF_##x##64_T__
#   define __TM_ALTTYPE(x)   __##x##32_t
#   define __TM_ALTSIZEOF(x) __SIZEOF_##x##32_T__
#else
#   define __TM_TYPE(x)      __##x##32_t
#   define __TM_SIZEOF(x)    __SIZEOF_##x##32_T__
#   define __TM_ALTTYPE(x)   __##x##64_t
#   define __TM_ALTSIZEOF(x) __SIZEOF_##x##64_T__
#endif
#else
#   define __FS_TYPE(x)      __##x##64_t
#   define __FS_SIZEOF(x)    __SIZEOF_##x##64_T__
#   define __FS_ALTTYPE(x)   __##x##32_t
#   define __FS_ALTSIZEOF(x) __SIZEOF_##x##32_T__
#   define __TM_TYPE(x)      __##x##64_t
#   define __TM_SIZEOF(x)    __SIZEOF_##x##64_T__
#   define __TM_ALTTYPE(x)   __##x##32_t
#   define __TM_ALTSIZEOF(x) __SIZEOF_##x##32_T__
#endif


#ifdef __USE_KOS
#if __SIZEOF_SIZE_T__ <= __SIZEOF_INT__
#define __STDC_INT_AS_SSIZE_T   __ssize_t
#define __STDC_INT_AS_SIZE_T    __size_t
#else /* __SIZEOF_SIZE_T__ <= __SIZEOF_INT__ */
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    unsigned int
#endif /* __SIZEOF_SIZE_T__ > __SIZEOF_INT__ */
#if __SIZEOF_SIZE_T__ <= 4
#define __STDC_INT32_AS_SSIZE_T __ssize_t
#define __STDC_INT32_AS_SIZE_T  __size_t
#else /* __SIZEOF_SIZE_T__ <= 4 */
#define __STDC_INT32_AS_SSIZE_T __INT32_TYPE__
#define __STDC_INT32_AS_SIZE_T  __UINT32_TYPE__
#endif /* __SIZEOF_SIZE_T__ > 4 */
#define __STDC_UINT_AS_SIZE_T   __STDC_INT_AS_SIZE_T
#define __STDC_UINT32_AS_SIZE_T __STDC_INT32_AS_SIZE_T
#else /* __USE_KOS */
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    int
#define __STDC_INT32_AS_SSIZE_T __INT32_TYPE__
#define __STDC_INT32_AS_SIZE_T  __INT32_TYPE__
#define __STDC_UINT_AS_SIZE_T   unsigned int
#define __STDC_UINT32_AS_SIZE_T __UINT32_TYPE__
#endif /* !__USE_KOS */

#ifndef __KOS_FIXED_CONST
#ifdef __USE_KOS
#define __KOS_FIXED_CONST const
#else /* __USE_KOS */
#define __KOS_FIXED_CONST /* Nothing */
#endif /* !__USE_KOS */
#endif /* !__KOS_FIXED_CONST */

//#define __USE_KOS 1
//#define __USE_KXS 1
//#define __USE_EXCEPT 1
//#define __USE_STRING_BWLQ 1
//#define __USE_STRING_XCHR 1
//#define __USE_XOPEN2K8 1
//#define __USE_MISC 1
//#define __USE_DOS 1
//#define __USE_GNU 1
//#define __USE_XOPEN2K 1
//#define __USE_ISOC99 1
//#define __CORRECT_ISO_CPP_STRING_H_PROTO 1
//#define _USE_32BIT_TIME_T 1

#endif /* !_FEATURES_H */
