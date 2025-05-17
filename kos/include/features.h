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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/features.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/features.h) */
/* (#) Portability: GNU C Library (/include/features.h) */
/* (#) Portability: GNU Hurd      (/usr/include/features.h) */
/* (#) Portability: diet libc     (/include/features.h) */
/* (#) Portability: libc4/5       (/include/features.h) */
/* (#) Portability: libc6         (/include/features.h) */
/* (#) Portability: libcmini      (/include/features.h) */
/* (#) Portability: musl libc     (/include/features.h) */
/* (#) Portability: uClibc        (/include/features.h) */
#ifndef _FEATURES_H
#define _FEATURES_H 1

#include "__stdinc.h"


/* Don't  implicitly  expose  any system  functionality  that isn't
 * strictly sanctioned by the C/C++ standard in C standard headers.
 * Headers that aren't  mentioned by the  C/C++ standards  continue
 * to  behave normally, and  any symbol that  starts with `__' also
 * isn't necessarily affected.
 * -> This functionality is mainly intended to get an idea of how
 *    C-standard compliant some given application source actually
 *    is, as well as aid in putting together configure tests.
 * NOTE: Any source file  using this should  also make sure  that
 *       no other *_SOURCE macro gets defined, since other macros
 *       may once again  manually enable  functionality that  was
 *       originally disabled by this option. */
#ifdef _ISOC_PURE_SOURCE
#undef __USE_ISOC_PURE
#define __USE_ISOC_PURE 1
#endif /* _ISOC_PURE_SOURCE */



/* Hacky work-around to  satisfy header  requirements for  libstdc++.
 * And  before you say that this is a  bad way of doing it, know that
 * on  linux,  g++  will _always_  pre-define  `_GNU_SOURCE' straight
 * from  within the compiler  itself, in order to  get access to some
 * of the symbols that are required to implement the inline functions
 * from headers. Don't believe me? - Compile the following on a linux
 * machine:
 * foo.cc:
 * >> #ifdef _GNU_SOURCE
 * >> #error "Well... I was right."
 * >> #endif
 * $ g++ foo.cc
 * So to satisfy libstdc++ in  this regard, but try  to be a bit  nicer
 * about it by only defining this macro when hosted by g++ (which still
 * must be  handled explicitly  so-as to  already expose  the  required
 * symbols  during the libstdc++  configure phase), or  when one of the
 * headers specific to  libstdc++ are apart  of the include-path  (thus
 * also supporting compilers other than g++). */
#if (defined(__cplusplus) && !defined(__INTELLISENSE__) &&   \
     !defined(_NO_IMPLICIT_GNU_SOURCE) &&                    \
     !defined(__USE_ISOC_PURE) && !defined(_EVERY_SOURCE) && \
     (defined(__GNUC__) || __has_include(<bits/vector.tcc>)))
#undef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif /* ... */


/* libstdc++ sucks and does stuff like this:
 * >> #include <cstddef>
 * >> ...
 * >> size_t foo;
 * This is wrong, since `size_t' might not appear in the global namespace,
 * but only within the  std:: namespace. I tried  to fix this by  patching
 * its  source, but after realizing how often it does this, I just gave up
 * and made this.
 *
 * When  this feature is enabled, <cstddef> will just behave the same
 * as <stddef.h>, meaning all symbols are declared in `std' AND `::'! */
#if defined(_BROKEN_CCOMPAT_SOURCE) || defined(_GLIBCXX_SHARED)
#undef __USE_BROKEN_CCOMPAT
#define __USE_BROKEN_CCOMPAT 1
#endif /* _BROKEN_CCOMPAT_SOURCE || _GLIBCXX_SHARED */


/* KOS System extensions */
#ifdef _KOS_SOURCE
#define __USE_KOS              1 /* Various KOS extensions (e.g. `strend()') */
#define __USE_STRING_BWLQ      1 /* `memcpy[bwlq]()' */
#define __USE_STRING_XCHR      1 /* `memxchr()' */
#define __USE_STRING_OVERLOADS 1 /* 4-argument `memcpy(dst, src, elem_count, elem_size)'
                                  * Also overloads `malloc()', `calloc()', and some more
                                  * libc functions. */
#endif /* _KOS_SOURCE */

/* KOS Kernel extensions/kernel-level data structures/functions
 * These become visible within the  KOS kernel by default,  and
 * can  manually   be  enabled   by  user-space   applications.
 * These  include internal ABI/API details normally hidden from
 * normal user-space applications and only need to be known  by
 * libc and the kernel,  such as `SA_RESTORER' or  `io_delay()' */
#if (defined(_KOS_KERNEL_SOURCE) || \
     (defined(__KOS__) && defined(__KERNEL__) && !defined(__USE_ISOC_PURE)))
#define __USE_KOS_KERNEL 1
#if !defined(_KOS_PURE_SOURCE) || (-_KOS_PURE_SOURCE - 1) != -1
#define __USE_KOS_PURE 1
#endif /* !_KOS_PURE_SOURCE || (-_KOS_PURE_SOURCE - 1) != -1 */
#else /* _KOS_KERNEL_SOURCE || (__KOS__ && __KERNEL__ && !__USE_ISOC_PURE) */
/* KOS header purification.
 * This feature causes some old, or badly namespace'd macros, structs and
 * struct  members to not  be visible in order  to prevent redundancy and
 * ensure that code uniformly uses the same symbols for referring to  the
 * same functionality.
 * This mainly affects network- and socket-related headers, where various
 * protocol descriptor  structures often  come  with varying  names  that
 * appear inconsistent with each other in how they've been named, as well
 * as if their members have been given a prefix.
 * This feature  is enabled  by default  when `__USE_KOS_KERNEL'  extensions
 * are  also enabled  (i.e. the default  when compiling code  for use within
 * the kernel; though in can be disabled with `#define _KOS_PURE_SOURCE 0'),
 * and disabled otherwise (i.e. when  compiling code for user-space;  though
 * can be enabled manually by `#define _KOS_PURE_SOURCE 1') */
#if defined(_KOS_PURE_SOURCE) && (-_KOS_PURE_SOURCE - 1) != -1
#define __USE_KOS_PURE 1
#endif /* _KOS_PURE_SOURCE && (-_KOS_PURE_SOURCE - 1) != -1 */
#endif /* !_KOS_KERNEL_SOURCE && (!__KOS__ || !__KERNEL__ || __USE_ISOC_PURE) */

/* Certain KOS extensions may alter the prototyping or invocation behavior
 * of functions or data structures.  By default, this behavior is  enabled
 * for kernel-space (when `_KOS_KERNEL_SOURCE' is also implied), but  must
 * be enabled explicitly for user-space.
 * Alterations include:
 *  - int sprintf() ->  size_t sprintf()
 *  - int printf()  -> ssize_t printf()
 *  - ...
 *  - feof(FILE *)  -> feof(FILE const *)
 *  - ...
 *  - Changing `int flags'-like arguments to `unsigned int flags'
 *  - Reversing the argument order of `outb()', `outw()', `outl()'
 *    and their `*_p'  versions, such that  the port comes  first.
 *  - ... */
#if (defined(_KOS_ALTERATIONS_SOURCE) || \
     (defined(__KOS__) && defined(__KERNEL__) && !defined(__USE_ISOC_PURE)))
#define __USE_KOS_ALTERATIONS 1
#endif /* _KOS_ALTERATIONS_SOURCE || (__KOS__ && __KERNEL__ && !__USE_ISOC_PURE) */

/* `memcpy[bwlq]()' (Also implied by `_KOS_SOURCE') */
#ifdef _STRING_BWLQ_SOURCE
#define __USE_STRING_BWLQ 1
#endif /* _STRING_BWLQ_SOURCE */

/* `memxchr()' (Also implied by `_KOS_SOURCE') */
#ifdef _STRING_XCHR_SOURCE
#define __USE_STRING_XCHR 1
#endif /* _STRING_XCHR_SOURCE */

/* Explicitly allow definition of ctype macros. */
#ifdef _CTYPE_MACRO_SOURCE
#define __USE_CTYPE_MACROS 1
#endif /* _CTYPE_MACRO_SOURCE */

/* DOS (NT) extensions and symbol visibility.
 * This is the stuff you'd also find in `msvcrt.dll' and its headers. */
#ifdef _DOS_SOURCE
#if (-_DOS_SOURCE - 1) != -1
#define __USE_DOS 1
#define __USE_DOS_SLIB 1
#endif /* (-_DOS_SOURCE - 1) != -1 */
#elif defined(_MSC_VER) && !defined(__USE_ISOC_PURE)
#define __USE_DOS 1
#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__ 1
#endif /* !__STDC_WANT_SECURE_LIB__ */
#if (__STDC_WANT_SECURE_LIB__ + 0) != 0
#define __USE_DOS_SLIB 1
#endif /* (__STDC_WANT_SECURE_LIB__ + 0) != 0 */
#endif /* ... */

/* DOS  extensions that change the way that certain symbols are declared.
 * This mainly affects the const-ness of argv-vectors taken by `execv(2)' */
#ifdef _DOS_ALTERATIONS_SOURCE
#if (_DOS_ALTERATIONS_SOURCE + 0) != 0
#define __USE_DOS_ALTERATIONS 1
#endif /* (_DOS_ALTERATIONS_SOURCE + 0) != 0 */
#elif defined(_MSC_VER) && !defined(__USE_ISOC_PURE)
#define __USE_DOS_ALTERATIONS 1
#endif /* ... */

/* 64-bit time_t extensions for KOS
 * (By the time of this writing, but I'm guessing by 2038-01-19T03:14:07 this'll
 * be similar to  what Glibc will  have to do  if it doesn't  wan'na roll  over)
 * Also available as extensions in other libcs:
 *  - defined(_TIME64_SOURCE):
 *    - KOS-specific feature macro
 *  - defined(_TIME64_T):
 *    - Compaq:     http://www.frascati.enea.it/documentation/tru6450/MAN/MAN3/0254____.HTM
 *    - Tru64 UNIX: http://nixdoc.net/man-pages/Tru64/man3/difftime.3.html
 *    - other:      https://www.unix.com/man-page/osf1/3/difftime/
 */
#if (defined(_TIME64_SOURCE) || \
     defined(_TIME64_T))
#define __USE_TIME64 1
#endif /* ... */

/* Control the typing of `time_t' to either be `__time32_t' or `__time64_t'
 * Note that despite their names, on some architectures `sizeof(__time32_t) == sizeof(__time64_t)',
 * such that  this  option  doesn't  actually  affect anything.  One  such  architecture  would  be
 * the  x86_64  CPU  where  `__time32_t'  is  defined  as  `__syscall_slong_t',  which  is  already
 * 8 bytes  big.  To  simplify the  porting  of  programs, a  properly  written  application  could
 * be  made  64-bit time_t-compliant  by  simply re-compiling  everything  with `-D_TIME_T_BITS=64'
 * Reminder: On  `2038-01-19T03:14:07', 32-bit unix time will roll  over, and this is a date
 *           that anyone reading this is likely to still experience, so be prepared and know
 *           that sooner or later _all_ applications will have to support this.
 * NOTE: As the aforementioned date creeps  closer and closer, `__USE_TIME_BITS64' will  eventually
 *       become the default, and if I (or someone else) will still be willing to maintain this file
 *       as  well as the KOS operating system at  that point, 32-bit time support may eventually be
 *       removed entirely, depending on adoption of 64-bit time by both KOS-specific and unix/linux
 *       software in general. */
#ifdef _TIME_T_BITS
#if (_TIME_T_BITS + 0) == 64
#define __USE_TIME_BITS64 1
#elif (_TIME_T_BITS + 0) == 32
#undef __USE_TIME_BITS64
#else /* _TIME_T_BITS == 32 */
#error "Must #define _TIME_T_BITS as either 32 or 64"
#endif /* _TIME_T_BITS != 32 */
#elif defined(_TIME_BITS)
#if (_TIME_BITS + 0) == 64
#define __USE_TIME_BITS64 1
#elif (_TIME_BITS + 0) == 32
#undef __USE_TIME_BITS64
#else /* _TIME_BITS == 32 */
#error "Must #define _TIME_BITS as either 32 or 64"
#endif /* _TIME_T_BITS != 32 */
#elif defined(_USE_32BIT_TIME_T)
#undef __USE_TIME_BITS64
#elif defined(_USE_64BIT_TIME_T)
#define __USE_TIME_BITS64 1
#elif defined(__USE_DOS) || defined(__USE_KOS_KERNEL)
#define __USE_TIME_BITS64 1
#elif defined(__KOS__) && defined(__KERNEL__)
#define __USE_TIME_BITS64 1
#endif /* ... */


#ifdef _OPENBSD_SOURCE
#define __USE_OPENBSD 1
#undef _BSD_SOURCE
#define _BSD_SOURCE 1
#endif /* _OPENBSD_SOURCE */

#ifdef _NETBSD_SOURCE
#define __USE_NETBSD 1
#undef _BSD_SOURCE
#define _BSD_SOURCE 1
#undef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#undef _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#if !defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE + 0 < 200809L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif /* _POSIX_C_SOURCE < 200809L */
#if !defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE + 0 < 700)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif /* _XOPEN_SOURCE < 200809L */
#endif /* _NETBSD_SOURCE */

#ifdef _MINIX_SOURCE
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef _BSD_SOURCE
#define _BSD_SOURCE 1
#undef __USE_MINIX
#define __USE_MINIX 1
#endif /* _MINIX_SOURCE */

/* Make available some BSD-specific extensions, such as `cfmakesane(3)' */
#ifdef _BSD_SOURCE
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef __USE_BSD
#define __USE_BSD 1
/* BSD  name (not used in headers, but may be checked by
 * applications as a sort-of ACK that the system headers
 * have understood the _BSD_SOURCE request) */
#define __BSD_VISIBLE 1 /* API alias (don't use in headers!) */
#endif /* _BSD_SOURCE */

/* Make available some Cygwin-specific extensions, such as `strtosigno(3)' */
#ifdef _CYG_SOURCE
#define __USE_CYGWIN 1
#endif /* _CYG_SOURCE */

/* Make available some newlib-specific extensions */
#ifdef _NEWLIB_SOURCE
#define __USE_NEWLIB 1
#endif /* _NEWLIB_SOURCE */

/* Enable additional extensions present on Solaris (or more specifically: OpenSolaris,
 * since Solaris is closed-source and I couldn't  get my hands on its system  headers) */
#ifdef __EXTENSIONS__
#define __USE_SOLARIS 1
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#undef _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#endif /* __EXTENSIONS__ */



#if ((defined(_BSD_SOURCE) || defined(_SVID_SOURCE)) && \
     !defined(_DEFAULT_SOURCE))
#define _DEFAULT_SOURCE 1
#endif /* (_BSD_SOURCE || _SVID_SOURCE) && !_DEFAULT_SOURCE */

#ifdef _GNU_SOURCE
#undef _ISOC95_SOURCE
#define _ISOC95_SOURCE 1
#undef _ISOC99_SOURCE
#define _ISOC99_SOURCE 1
#undef _ISOC11_SOURCE
#define _ISOC11_SOURCE 1
#undef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#if !defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE + 0 < 200809L)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif /* _POSIX_C_SOURCE < 200809L */
#if !defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE + 0 < 700)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif /* _XOPEN_SOURCE < 200809L */
#undef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#undef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#undef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#undef _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#endif /* _GNU_SOURCE */

#if (!defined(_DEFAULT_SOURCE) && !defined(__USE_ISOC_PURE) && \
     (!defined(__STRICT_ANSI__) && !defined(_ISOC99_SOURCE) && \
      !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)))
#define _DEFAULT_SOURCE 1
#endif /* ... */

#if (defined(_ISOC23_SOURCE) /* || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ >= TBA)*/)
#define __ISO_C_VISIBLE 2023 /* API alias (don't use in headers!) */
#define __USE_ISOC23 1
#endif /* _ISOC23_SOURCE || __STDC_VERSION__ >= 201112L */

#if (defined(_ISOC17_SOURCE) || defined(__USE_ISOC23) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201710L))
#ifndef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 2017 /* API alias (don't use in headers!) */
#endif /* !__ISO_C_VISIBLE */
#define __USE_ISOC17 1
#endif /* _ISOC17_SOURCE || __STDC_VERSION__ >= 201710L */

#if (defined(_ISOC11_SOURCE) || defined(__USE_ISOC17) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L))
#ifndef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 2011 /* API alias (don't use in headers!) */
#endif /* !__ISO_C_VISIBLE */
#define __USE_ISOC11 1
#endif /* _ISOC11_SOURCE || __USE_ISOC17 || __STDC_VERSION__ >= 201112L */

#if (defined(_ISOC99_SOURCE) || defined(__USE_ISOC11) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L))
#ifndef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 1999 /* API alias (don't use in headers!) */
#endif /* !__ISO_C_VISIBLE */
#define __USE_ISOC99 1
#endif /* _ISOC99_SOURCE || __USE_ISOC11 || __STDC_VERSION__ >= 199901L */

#if (defined(_ISOC95_SOURCE) || defined(__USE_ISOC99) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L))
#ifndef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 1995 /* API alias (don't use in headers!) */
#endif /* !__ISO_C_VISIBLE */
#define __USE_ISOC95 1
#endif /* _ISOC95_SOURCE || __USE_ISOC99 || __STDC_VERSION__ >= 199409L */

#if (defined(_ISOCXX2A_SOURCE) || defined(_ISOCXX20_SOURCE) || \
     (defined(__cplusplus) && __cplusplus > 202002L))
#define __USE_ISOCXX2A 1
#endif /* _ISOCXX2A_SOURCE || _ISOCXX20_SOURCE || __cplusplus > 202002L */

#if (defined(_ISOCXX17_SOURCE) || defined(__USE_ISOCXX2A) || \
     (defined(__cplusplus) && __cplusplus >= 201703L))
#define __USE_ISOCXX17 1
#endif /* _ISOCXX17_SOURCE || __USE_ISOCXX2A || __cplusplus > 201703L */

#if (defined(_ISOCXX14_SOURCE) || defined(__USE_ISOCXX17) || \
     (defined(__cplusplus) && __cplusplus >= 201103L))
#define __USE_ISOCXX14 1
#endif /* _ISOCXX14_SOURCE || __USE_ISOCXX17 || __cplusplus > 201103L */

#if (defined(_ISOCXX11_SOURCE) || defined(__USE_ISOCXX14) || \
     (defined(__cplusplus) && __cplusplus >= 201103L) || \
     defined(__GXX_EXPERIMENTAL_CXX0X__))
#define __USE_ISOCXX11 1
#endif /* _ISOCXX11_SOURCE || __USE_ISOCXX14 || __cplusplus >= 201103L || __GXX_EXPERIMENTAL_CXX0X__ */

#if defined(__cplusplus) && (!defined(__GCC_VERSION_NUM) || __GCC_VERSION_NUM >= 40400)
/* Enable proper C++ prototype declarations. */
#define __CORRECT_ISO_CPP_STRING_H_PROTO    1
#define __CORRECT_ISO_CPP_STRINGS_H_PROTO   1
#define __CORRECT_ISO_CPP_WCHAR_H_PROTO     1
#define __CORRECT_ISO_CPP_STDLIB_H_PROTO    1
#define __CORRECT_ISO_CPP_UNICODE_H_PROTO   1
#define __CORRECT_ISO_CPP_MATH_H_PROTO      1
#define __CORRECT_ISO_CPP_COMPLEX_H_PROTO   1
#define __CORRECT_ISO_CPP_UCHAR_H_PROTO     1
#define __CORRECT_ISO_CPP11_MATH_H_PROTO_FP 1
#endif /* ... */

#if defined(_DEFAULT_SOURCE) && !defined(__USE_ISOC_PURE)
#if !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define __USE_POSIX_IMPLICITLY 1
#endif /* !_POSIX_SOURCE && !_POSIX_C_SOURCE */
#undef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif /* _DEFAULT_SOURCE && !__USE_ISOC_PURE */

#if ((!defined(__STRICT_ANSI__) ||                             \
      (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE + 0 >= 500)) && \
     !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE) &&   \
     !defined(__USE_ISOC_PURE))
#define _POSIX_SOURCE 1
#if defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 500
#define _POSIX_C_SOURCE 2
#elif defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 600
#define _POSIX_C_SOURCE 199506L
#elif defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 700
#define _POSIX_C_SOURCE 200112L
#else /* ... */
#define _POSIX_C_SOURCE 200809L
#endif /* !... */
#define __USE_POSIX_IMPLICITLY 1
#endif /* ... */

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
#define __USE_POSIX 1
#endif /* _POSIX_SOURCE || _POSIX_C_SOURCE || _XOPEN_SOURCE */

#if (defined(_XOPEN_SOURCE) || \
     (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE + 0 >= 2))
#define __POSIX_VISIBLE 199209 /* API alias (don't use in headers!) */
#define __USE_POSIX2 1
#endif /* _XOPEN_SOURCE || _POSIX_C_SOURCE >= 2 */

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE + 0 >= 199309L
#undef __POSIX_VISIBLE
#define __POSIX_VISIBLE 199309 /* API alias (don't use in headers!) */
#define __USE_POSIX199309 1
#endif /* _POSIX_C_SOURCE >= 199309L */

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE + 0 >= 199506L
#undef __POSIX_VISIBLE
#define __POSIX_VISIBLE 199506 /* API alias (don't use in headers!) */
#define __USE_POSIX199506 1
#endif /* _POSIX_C_SOURCE >= 199506L */

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE + 0 >= 200112L
#undef __POSIX_VISIBLE
#define __POSIX_VISIBLE 200112 /* API alias (don't use in headers!) */
#define __USE_XOPEN2K 1
#undef __USE_ISOC95
#define __USE_ISOC95 1
#undef __USE_ISOC99
#define __USE_ISOC99 1
#endif /* _POSIX_C_SOURCE >= 200112L */

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE + 0 >= 200809L
#undef __POSIX_VISIBLE
#define __POSIX_VISIBLE 200809 /* API alias (don't use in headers!) */
#define __USE_XOPEN2K8 1
#undef _ATFILE_SOURCE
#define _ATFILE_SOURCE 1
#endif /* _POSIX_C_SOURCE >= 200809L */

#ifdef _XOPEN_SOURCE
#define __USE_XOPEN 1
#if _XOPEN_SOURCE + 0 >= 500
#define __USE_XOPEN_EXTENDED 1
#define __USE_UNIX98         1
#undef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE 1
#if _XOPEN_SOURCE + 0 >= 600
#if _XOPEN_SOURCE + 0 >= 700
#define __XSI_VISIBLE     700 /* API alias (don't use in headers!) */
#define __USE_XOPEN2K8    1
#define __USE_XOPEN2K8XSI 1
#else /* _XOPEN_SOURCE >= 700 */
#define __XSI_VISIBLE 600
#endif /* _XOPEN_SOURCE < 700 */
#define __USE_XOPEN2K    1
#define __USE_XOPEN2KXSI 1
#undef __USE_ISOC95
#define __USE_ISOC95 1
#undef __USE_ISOC99
#define __USE_ISOC99 1
#else /* _XOPEN_SOURCE >= 700 */
#define __XSI_VISIBLE 500
#endif /* _XOPEN_SOURCE >= 600 */
#else /* _XOPEN_SOURCE >= 500 */
#ifdef _XOPEN_SOURCE_EXTENDED
#define __USE_XOPEN_EXTENDED 1
#define __XSI_VISIBLE        4 /* API alias (don't use in headers!) */
#else /* _XOPEN_SOURCE_EXTENDED */
#define __XSI_VISIBLE 1 /* API alias (don't use in headers!) */
#endif /* !_XOPEN_SOURCE_EXTENDED */
#endif /* _XOPEN_SOURCE < 500 */
#endif /* _XOPEN_SOURCE */

#ifdef _LARGEFILE_SOURCE
#define __USE_LARGEFILE 1
#endif /* _LARGEFILE_SOURCE */

#ifdef _LARGEFILE64_SOURCE
#define __USE_LARGEFILE64 1
#define __LARGE64_FILES 1 /* API alias (don't use in headers!) */
#endif /* _LARGEFILE64_SOURCE */

#ifdef _FILE_OFFSET_BITS
#if _FILE_OFFSET_BITS + 0 == 64
#define __USE_FILE_OFFSET64 1
#endif /* _FILE_OFFSET_BITS == 64 */
#elif defined(__USE_KOS_KERNEL)
#define __USE_FILE_OFFSET64 1
#elif defined(__KOS__) && defined(__KERNEL__)
#define __USE_FILE_OFFSET64 1
#endif /* ... */

#ifdef _DEFAULT_SOURCE
#define __MISC_VISIBLE 1 /* API alias (don't use in headers!) */
#define __SVID_VISIBLE 1 /* API alias (don't use in headers!) */
#define __USE_MISC 1
#endif /* _DEFAULT_SOURCE */

#ifdef _ATFILE_SOURCE
#define __USE_ATFILE 1
#define __ATFILE_VISIBLE 1 /* API alias (don't use in headers!) */
#endif /* _ATFILE_SOURCE */

#ifdef _GNU_SOURCE
#define __USE_GNU 1
#define __GNU_VISIBLE 1 /* API alias (don't use in headers!) */
#endif /* _GNU_SOURCE */

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
#define __USE_REENTRANT 1
#elif defined(__DYNAMIC_REENT__) && !defined(__SINGLE_THREAD__)
#include "__crt.h"
#ifdef __CRT_CYG
#define __USE_REENTRANT 1
#endif /* __CRT_CYG */
#elif (defined(__GNUC__) && defined(__KOS__) && \
       !defined(__PIC__) && !defined(__pic__) && 0)
/* Can't safely do this: a program might use a library which internally  uses
 * additional threads. In this  case, the main program  might be able to  use
 * unlocked stdio, but if it does, there might be problems syncing stuff with
 * those internal threads of the library it uses... */
#undef _NO_THREADING
#define _NO_THREADING
#endif /* ... */

/* Test a couple of macros that can be used to explicitly disable thread-safety checks.
 *
 * Ways to enable:
 * - #define __SINGLE_THREAD__
 * - #define _NO_THREADING
 * - #define _NO_REENTRANT
 * - #define _REENTRANT 0   // only if defined to "0"; not recognized if defined as empty
 */
#if (defined(__SINGLE_THREAD__) || defined(_NO_REENTRANT) || \
     (defined(_REENTRANT) && ((-_REENTRANT - 1) == -1)))
#undef _REENTRANT
#ifndef _NO_THREADING
#define _NO_THREADING
#endif /* !_NO_THREADING */
#endif /* ... */

/* When  multi-threading is explicitly disabled (by one of these macros), then
 * we can safely override normal stdio functions with their unlocked variants. */
#if defined(_NO_THREADING) || defined(_USE_UNLOCKED_STDIO)
#undef __USE_STDIO_UNLOCKED
#define __USE_STDIO_UNLOCKED 1
#endif /* _NO_THREADING || _USE_UNLOCKED_STDIO */

/* Enable additional utf16/32 functions in system headers. */
#ifdef _UTF_SOURCE
#undef __USE_UTF
#define __USE_UTF 1
#endif /* _UTF_SOURCE */


/* Enable closer emulation of Glibc headers in cases  where
 * standards leave the  implementation behavior open.  This
 * mainly affects optional  include implications in  system
 * headers. For example, POSIX allows (but doesn't require)
 * <aio.h> to also #include <sys/types.h>, where Glibc does
 * perform  this inclusion, however doing so isn't actually
 * necessary under KOS.
 *
 * When `_GLIBC_BLOAT_SOURCE'  is defined,  non-portable,
 * implicit includes are emulated more closely to what is
 * also done by Glibc. Note however that this  additional
 * level of  compatibility is  not  backed by  any  fixed
 * standard, but depends  solely on  what Glibc  actually
 * does in relation  to fixed standards  (such as  POSIX) */
#ifdef _GLIBC_BLOAT_SOURCE
#undef __USE_GLIBC_BLOAT
#define __USE_GLIBC_BLOAT 1
#undef __USE_POSIX_BLOAT
#define __USE_POSIX_BLOAT 1
#endif /* _GLIBC_BLOAT_SOURCE */

/* Similar to "_GLIBC_BLOAT_SOURCE": any time the posix specs say that:
 * - "Inclusion of the [<foo.h>] header may make visible all symbols from the headers"
 * - "Inclusion of the [<foo.h>] header may also make visible all symbols from"
 * - ...
 * this feature macro causes that implicit include to happen.
 * Posix specs were grep'd for:
 * - "may make visible all symbols"
 * - "may also make visible all symbols"
 */
#ifdef _POSIX_BLOAT_SOURCE
#undef __USE_POSIX_BLOAT
#define __USE_POSIX_BLOAT 1
#endif /* _POSIX_BLOAT_SOURCE */


/* Some system headers  may define secondary  variants of  certain
 * struct types (often  ending with  *64, hence the  name of  this
 * feature test macro), that extend the non-suffixed types in some
 * way  (usually related to `__USE_LARGEFILE64' or `__USE_TIME64')
 *
 * According to existing standards and conventions, user-code should
 * always be able to forward-declare all structure types declared in
 * system headers. And this behavior extends to include such special
 * struct types:
 * >> // Declared before <sys/stat.h> was #included
 * >> struct stat64;
 * >> void my_print_stat64(struct stat64 *st);
 * >> ...
 * >> #include <sys/stat.h>
 * >> ...
 * >> void print_fileinfo(char const *filename) {
 * >>     struct stat64 st;
 * >>     stat64(filename, &st);
 * >>     my_print_stat64(&st);
 * >> }
 *
 * Long story short. When `__USE_STRUCT64_MACRO' is enabled (it isn't enabled
 * by  default), the  above code would  not be guarantied  to compile without
 * errors.  In  order to  fix the  code  to work  with `__USE_STRUCT64_MACRO'
 * enabled, one mustn't forward-declare struct types found in system  headers
 * before the respective headers have already been included.
 *
 * The longer story is this:
 *   - Take `struct timespec' and `struct timespec64' as an example
 *   - When `_TIME_T_BITS=64', then they  are mandated to share  binary
 *     compatibility, such that the offsetof for each field, and sizeof
 *     of the structures as a whole will be identical between the  two.
 *   - Knowing  this, it stands to reason to simply have the header
 *     define `struct timespec64' as `#define timespec64 timespec'.
 *   - The only problem with this is  that this would break any  forward
 *     declarations of `struct timespec64' prior to the declaring header
 *     being included.
 *   - That is where this feature test macro comes into play, essentially
 *     allowing headers to be configured as such:
 *     >> // In <bits/os/timespec.h>:
 *     >> ...    (#if SHOULD_DEFINE_TIMESPEC64_AS_ALIAS_FOR_TIMESPEC)
 *     >> #ifdef __USE_STRUCT64_MACRO
 *     >> #define timespec64 timespec
 *     >> #else // __USE_STRUCT64_MACRO
 *     >> struct timespec64 {
 *     >>     __time64_t        tv_sec;
 *     >>     __syscall_ulong_t tv_nsec;
 *     >>     ... // Potentially some more fields...
 *     >> };
 *     >> #endif // !__USE_STRUCT64_MACRO
 *   - As you can  see, when `__USE_STRUCT64_MACRO'  isn't defined  (which
 *     is the case by default when `_KOS_KERNEL_SOURCE' isn't enabled, and
 *     the  dedicated `_STRUCT64_MACRO_SOURCE' feature request is disabled
 *     as well), then  `struct timespec' and `struct timespec64'  continue
 *     to remain distinct  types such that  `struct timespec64' can  still
 *     be forward-declared prior to the header being included.
 *   - However,  when  `__USE_STRUCT64_MACRO' is  enabled, then  headers are
 *     allowed  to  simply macro-alias  binary-compatible  struct-types with
 *     each other, and the hosted source file is responsible to not forward-
 *     declare special  variants  of  struct types  (such  as  `timespec64')
 *     before the declaring header has also been included.
 * WARNING: KOS-specific types such  as `timespec32' are  _not_ affect  by
 *          this and may _always_ be declared as `#define timespec32 ...'!
 */
#if defined(__USE_KOS_KERNEL) || defined(_STRUCT64_MACRO_SOURCE)
#undef __USE_STRUCT64_MACRO
#define __USE_STRUCT64_MACRO 1
#endif /* __USE_KOS_KERNEL || _STRUCT64_MACRO_SOURCE */


#ifdef _EVERY_SOURCE
#undef __USE_KOS
#undef __USE_KOS_PURE
#undef __USE_STRING_BWLQ
#undef __USE_STRING_XCHR
#undef __USE_KOS_KERNEL
#undef __USE_CTYPE_MACROS
#undef __USE_DOS
#undef __USE_DOS_SLIB
#undef __USE_TIME64
#undef __USE_ISOC95
#undef __USE_ISOC99
#undef __USE_ISOC11
#undef __USE_ISOC17
#undef __USE_ISOCXX11
#undef __USE_ISOCXX14
#undef __USE_ISOCXX17
#undef __USE_ISOCXX2A
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
#undef __USE_ISOC_PURE
#undef __USE_BSD
#undef __USE_CYGWIN
#undef __USE_OPENBSD
#undef __USE_NETBSD
#undef __USE_SOLARIS
#undef __USE_MINIX

#define __USE_KOS 1
#define __USE_STRING_BWLQ 1
#define __USE_STRING_XCHR 1
#define __USE_KOS_KERNEL 1
#define __USE_CTYPE_MACROS 1
#define __USE_DOS 1
#define __USE_DOS_SLIB 1
#define __USE_TIME64 1
#define __USE_ISOC95 1
#define __USE_ISOC99 1
#define __USE_ISOC11 1
#define __USE_ISOC17 1
#define __USE_ISOCXX11 1
#define __USE_ISOCXX14 1
#define __USE_ISOCXX17 1
#define __USE_ISOCXX2A 1
#define __USE_POSIX 1
#define __USE_POSIX2 1
#define __USE_POSIX199309 1
#define __USE_POSIX199506 1
#define __USE_XOPEN2K 1
#define __USE_XOPEN2K8 1
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
#define __USE_BSD 1
#define __USE_CYGWIN 1
#define __USE_OPENBSD 1
#define __USE_NETBSD 1
#define __USE_SOLARIS 1
#define __USE_MINIX 1
#endif /* _EVERY_SOURCE */

/* You may `#define _DOS_SOURCE_CLEAN 1' alongside `_DOS_SOURCE' in order
 * to exclude select symbol definitions done by DOS that were only  there
 * in order to pollute  the global namespace (e.g.  `typedef ... size_t;'
 * in <crtdefs.h>, or the wchar-based functions in <stdio.h>, in addition
 * to already being declared in <wchar.h>)
 * Programs written  to only  use functions  after including  the  _correct_
 * header  should  be able  to enable  this  option without  issue. Programs
 * that accidentally rely on DOS's excessive use of function re-declarations
 * may use  this  option to  check  if  they might  be  making  non-portable
 * assumption on  which functions  are  being declared  following  inclusion
 * of a system header. */
#ifdef __USE_DOS
#ifdef _DOS_SOURCE_CLEAN
#define __USE_DOS_CLEAN 1
#endif /* _DOS_SOURCE_CLEAN */
#endif /* __USE_DOS */


#ifdef __USE_FILE_OFFSET64
#define __FS_TYPE(x)       __##x##64_t
#define __FS_SIZEOF(x)     __SIZEOF_##x##64_T__
#define __FS_ALIGNOF(x)    __ALIGNOF_##x##64_T__
#define __FS_ALTTYPE(x)    __##x##32_t
#define __FS_ALTSIZEOF(x)  __SIZEOF_##x##32_T__
#define __FS_ALTALIGNOF(x) __ALIGNOF_##x##32_T__
#else /* __USE_FILE_OFFSET64 */
#define __FS_TYPE(x)       __##x##32_t
#define __FS_SIZEOF(x)     __SIZEOF_##x##32_T__
#define __FS_ALIGNOF(x)    __ALIGNOF_##x##32_T__
#define __FS_ALTTYPE(x)    __##x##64_t
#define __FS_ALTSIZEOF(x)  __SIZEOF_##x##64_T__
#define __FS_ALTALIGNOF(x) __ALIGNOF_##x##64_T__
#endif /* !__USE_FILE_OFFSET64 */

#ifdef __USE_TIME_BITS64
#define __TM_TYPE(x)       __##x##64_t
#define __TM_SIZEOF(x)     __SIZEOF_##x##64_T__
#define __TM_ALIGNOF(x)    __ALIGNOF_##x##64_T__
#define __TM_ALTTYPE(x)    __##x##32_t
#define __TM_ALTSIZEOF(x)  __SIZEOF_##x##32_T__
#define __TM_ALTALIGNOF(x) __ALIGNOF_##x##32_T__
#else /* __USE_TIME_BITS64 */
#define __TM_TYPE(x)       __##x##32_t
#define __TM_SIZEOF(x)     __SIZEOF_##x##32_T__
#define __TM_ALIGNOF(x)    __ALIGNOF_##x##32_T__
#define __TM_ALTTYPE(x)    __##x##64_t
#define __TM_ALTSIZEOF(x)  __SIZEOF_##x##64_T__
#define __TM_ALTALIGNOF(x) __ALIGNOF_##x##64_T__
#endif /* !__USE_TIME_BITS64 */


#ifndef __CC__
#define __STDC_INT_AS_SSIZE_T   /* nothing */
#define __STDC_INT_AS_SIZE_T    /* nothing */
#define __STDC_LONG_AS_SIZE_T   /* nothing */
#define __STDC_INT32_AS_SSIZE_T /* nothing */
#define __STDC_INT32_AS_SIZE_T  /* nothing */
#define __STDC_UINT_AS_SIZE_T   /* nothing */
#define __STDC_UINT32_AS_SIZE_T /* nothing */
#define __STDC_INT_AS_UINT_T    /* nothing */
#elif defined(__INTELLISENSE__)
#ifdef __USE_KOS_ALTERATIONS
#ifdef __INTELLISENSE_SSIZE_TYPE__
#define __STDC_INT_AS_SSIZE_T   __INTELLISENSE_SSIZE_TYPE__
#define __STDC_INT32_AS_SSIZE_T __INTELLISENSE_SSIZE_TYPE__
#else /* __INTELLISENSE_SSIZE_TYPE__ */
#ifndef __SSIZE_TYPE__
#include "hybrid/typecore.h"
#endif /* !__SSIZE_TYPE__ */
#define __STDC_INT_AS_SSIZE_T   __SSIZE_TYPE__
#define __STDC_INT32_AS_SSIZE_T __SSIZE_TYPE__
#endif /* !__INTELLISENSE_SSIZE_TYPE__ */
#ifdef __INTELLISENSE_SIZE_TYPE__
#define __STDC_INT_AS_SIZE_T    __INTELLISENSE_SIZE_TYPE__
#define __STDC_LONG_AS_SIZE_T   __INTELLISENSE_SIZE_TYPE__
#define __STDC_INT32_AS_SIZE_T  __INTELLISENSE_SIZE_TYPE__
#define __STDC_UINT_AS_SIZE_T   __INTELLISENSE_SIZE_TYPE__
#define __STDC_UINT32_AS_SIZE_T __INTELLISENSE_SIZE_TYPE__
#else /* __INTELLISENSE_SIZE_TYPE__ */
#ifndef __SIZE_TYPE__
#include "hybrid/typecore.h"
#endif /* !__SIZE_TYPE__ */
#define __STDC_INT_AS_SIZE_T    __SIZE_TYPE__
#define __STDC_LONG_AS_SIZE_T   __SIZE_TYPE__
#define __STDC_INT32_AS_SIZE_T  __SIZE_TYPE__
#define __STDC_UINT_AS_SIZE_T   __SIZE_TYPE__
#define __STDC_UINT32_AS_SIZE_T __SIZE_TYPE__
#endif /* !__INTELLISENSE_SIZE_TYPE__ */
#define __STDC_INT_AS_UINT_T    unsigned int
#else /* __USE_KOS_ALTERATIONS */
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    int
#define __STDC_LONG_AS_SIZE_T   long
#define __STDC_INT32_AS_SSIZE_T int
#define __STDC_INT32_AS_SIZE_T  int
#define __STDC_UINT_AS_SIZE_T   unsigned int
#define __STDC_UINT32_AS_SIZE_T unsigned int
#define __STDC_INT_AS_UINT_T    int
#endif /* !__USE_KOS_ALTERATIONS */
#elif defined(__USE_KOS_ALTERATIONS)
#include "hybrid/typecore.h"
#if __SIZEOF_SIZE_T__ <= __SIZEOF_INT__
#define __STDC_INT_AS_SSIZE_T   __SSIZE_TYPE__
#define __STDC_INT_AS_SIZE_T    __SIZE_TYPE__
#else /* __SIZEOF_SIZE_T__ <= __SIZEOF_INT__ */
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    unsigned int
#endif /* __SIZEOF_SIZE_T__ > __SIZEOF_INT__ */
#if __SIZEOF_SIZE_T__ <= __SIZEOF_LONG__
#define __STDC_LONG_AS_SIZE_T   __SIZE_TYPE__
#else /* __SIZEOF_SIZE_T__ <= __SIZEOF_LONG__ */
#define __STDC_LONG_AS_SIZE_T   unsigned long
#endif /* __SIZEOF_SIZE_T__ > __SIZEOF_LONG__ */
#if __SIZEOF_SIZE_T__ <= 4
#define __STDC_INT32_AS_SSIZE_T __SSIZE_TYPE__
#define __STDC_INT32_AS_SIZE_T  __SIZE_TYPE__
#else /* __SIZEOF_SIZE_T__ <= 4 */
#define __STDC_INT32_AS_SSIZE_T __INT32_TYPE__
#define __STDC_INT32_AS_SIZE_T  __UINT32_TYPE__
#endif /* __SIZEOF_SIZE_T__ > 4 */
#define __STDC_UINT_AS_SIZE_T   __STDC_INT_AS_SIZE_T
#define __STDC_UINT32_AS_SIZE_T __STDC_INT32_AS_SIZE_T
#define __STDC_INT_AS_UINT_T    unsigned int
#else /* __USE_KOS_ALTERATIONS */
#if !defined(__INT32_TYPE__) || !defined(__UINT32_TYPE__)
#include "hybrid/typecore.h"
#endif /* !__INT32_TYPE__ || !__UINT32_TYPE__ */
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    int
#define __STDC_LONG_AS_SIZE_T   long
#define __STDC_INT32_AS_SSIZE_T __INT32_TYPE__
#define __STDC_INT32_AS_SIZE_T  __INT32_TYPE__
#define __STDC_UINT_AS_SIZE_T   unsigned int
#define __STDC_UINT32_AS_SIZE_T __UINT32_TYPE__
#define __STDC_INT_AS_UINT_T    int
#endif /* !__USE_KOS_ALTERATIONS */

#ifndef __KOS_FIXED_CONST
#ifdef __USE_KOS_ALTERATIONS
#define __KOS_FIXED_CONST const
#else /* __USE_KOS_ALTERATIONS */
#define __KOS_FIXED_CONST /* Nothing */
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__KOS_FIXED_CONST */


#ifndef _STDC_PREDEF_H
#include "stdc-predef.h"
#endif /* !_STDC_PREDEF_H */

/* KOS headers are always trying to emulate Glibc in some way... */
#undef __GNU_LIBRARY__
#define __GNU_LIBRARY__ 6
#define __GLIBC__       2
#define __GLIBC_MINOR__ 36
#define __GLIBC_PREREQ(major, minor) \
	((major) > __GLIBC__ || ((major) == __GLIBC__ && (minor) >= __GLIBC_MINOR__))

#endif /* !_FEATURES_H */
