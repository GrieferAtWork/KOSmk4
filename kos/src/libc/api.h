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
#ifndef GUARD_LIBC_API_H
#define GUARD_LIBC_API_H 1
#define __BUILDING_LIBC  1

#define __CRT_KOS_PRIMARY 1
#define __CRT_KOS         1
#ifdef __KERNEL__
#define __CRT_KOS_KERNEL 1
#endif /* __KERNEL__ */

#ifndef __OPTIMIZE_SIZE__
/* Enable system call inlining, causing calls to `sys_*' functions from <kos/syscalls.h>
 * to be inlined (as far as possible), rather than being declared as entry points to the
 * libc system call export table (libc also exports all system calls as `sys_*' symbols)
 * NOTE: When optimizing for size, we don't do this, in which case system calls used
 *       by libc library functions get linked against the system call wrappers that
 *       are always exported from libc unconditionally. */
#define __WANT_INLINE_SYSCALLS 1
#endif /* !__OPTIMIZE_SIZE__ */


/* Enable access to a variety of header functions normally
 * locked away behind various feature macros (us being libc,
 * we obviously want access to anything we intend on defining,
 * so we make our job simple by unlocking everything) */
#define _KOS_SOURCE         1
#define _KOS_KERNEL_SOURCE  1
#define _STRING_BWLQ_SOURCE 1
#define _STRING_XCHR_SOURCE 1
#define _CTYPE_MACRO_SOURCE 1
#define _DOS_SOURCE         1
#define _BSD_SOURCE         1
#define _SVID_SOURCE        1
#define _GNU_SOURCE         1
#define _LARGEFILE_SOURCE   1

/* Must load headers in 32-bit time/file-offset mode, so-as to prevent
 * any symbol re-directions from happening, which might otherwise screw
 * up libc linkage. - Instead, libc itself must always explicitly specify
 * the *64 variants of functions (e.g. `mmap64()'; `mmap()' is always the
 * 32-bit variant) */
#undef _LARGEFILE64_SOURCE
#undef _TIME64_SOURCE
#define _LARGEFILE64_SOURCE 1
#define _TIME64_SOURCE      1
#undef _TIME_T_BITS
#define _TIME_T_BITS 32
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 32

#include <__crt.h>
#include <features.h>
#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/anno.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

/* Pull in arch-specific LIBC feature information */
#if defined(__i386__) || defined(__x86_64__)
#include "hybrid/arch/i386/config.h"
#endif /* ARCH... */


/* TODO:REMOVE_ME:BEGIN */
/* Since a more consistent implementation of int-as-... has been
 * added as part of updating the magic generator, user-level function
 * implementations aren't being generated automatically, yet. As a
 * result of this, libc contains some inconsistent prototypes internally,
 * with regards to these macros.
 * To bypass that inconsistency (for the moment), override these macros
 * until user-level source files are once again automated as well. */
#pragma GCC system_header
#undef __STDC_INT_AS_SSIZE_T
#undef __STDC_INT_AS_SIZE_T
#undef __STDC_INT32_AS_SSIZE_T
#undef __STDC_INT32_AS_SIZE_T
#undef __STDC_UINT_AS_SIZE_T
#undef __STDC_UINT32_AS_SIZE_T
#undef __STDC_INT_AS_UINT_T
#define __STDC_INT_AS_SSIZE_T   int
#define __STDC_INT_AS_SIZE_T    int
#define __STDC_INT32_AS_SSIZE_T __INT32_TYPE__
#define __STDC_INT32_AS_SIZE_T  __INT32_TYPE__
#define __STDC_UINT_AS_SIZE_T   unsigned int
#define __STDC_UINT32_AS_SIZE_T __UINT32_TYPE__
#define __STDC_INT_AS_UINT_T    int
/* TODO:REMOVE_ME:END */

/* TODO:REMOVE_ME:BEGIN */
/* Find a better solution for dealing with libc-implementation dependencies on [[ignore]] functions...
 * (Maybe the old magic was onto something by escaping `strlen' into `libc_strlen' for auto/user impls...) */
#define _vscc16printf     libd__vscwprintf
#define _vscc32printf     libc__vscwprintf
#define _scc16printf      libd__scwprintf
#define _scc32printf      libc__scwprintf
#define _vscc16printf_p   libd__vscwprintf_p
#define _vscc32printf_p   libc__vscwprintf_p
#define _scc16printf_p    libd__scwprintf_p
#define _scc32printf_p    libc__scwprintf_p
#define _vscc16printf_l   libd__vscwprintf_l
#define _vscc32printf_l   libc__vscwprintf_l
#define _scc16printf_l    libd__scwprintf_l
#define _scc32printf_l    libc__scwprintf_l
#define _vscc16printf_p_l libd__vscwprintf_p_l
#define _vscc32printf_p_l libc__vscwprintf_p_l
#define _scc16printf_p_l  libd__scwprintf_p_l
#define _scc32printf_p_l  libc__scwprintf_p_l
#define _vsnc16printf_s   libd__vsnwprintf_s
#define _vsnc32printf_s   libc__vsnwprintf_s
#define _snc16printf_s    libd__snwprintf_s
#define _snc32printf_s    libc__snwprintf_s
#define _vfc16printf_p    libd__vfwprintf_p
#define _vfc32printf_p    libc__vfwprintf_p
#define _fc16printf_p     libd__fwprintf_p
#define _fc32printf_p     libc__fwprintf_p
#define _vc16printf_p     libd__vwprintf_p
#define _vc32printf_p     libc__vwprintf_p
#define _c16printf_p      libd__wprintf_p
#define _c32printf_p      libc__wprintf_p
#define _vsc16printf_p    libd__vswprintf_p
#define _vsc32printf_p    libc__vswprintf_p
#define _sc16printf_p     libd__swprintf_p
#define _sc32printf_p     libc__swprintf_p
#define _vc16printf_l     libd__vwprintf_l
#define _vc32printf_l     libc__vwprintf_l
#define _c16printf_l      libd__wprintf_l
#define _c32printf_l      libc__wprintf_l
#define _vc16printf_p_l   libd__vwprintf_p_l
#define _vc32printf_p_l   libc__vwprintf_p_l
#define _c16printf_p_l    libd__wprintf_p_l
#define _c32printf_p_l    libc__wprintf_p_l
#define _vc16printf_s_l   libd__vwprintf_s_l
#define _vc32printf_s_l   libc__vwprintf_s_l
#define _c16printf_s_l    libd__wprintf_s_l
#define _c32printf_s_l    libc__wprintf_s_l
#define _vfc16printf_l    libd__vfwprintf_l
#define _vfc32printf_l    libc__vfwprintf_l
#define _fc16printf_l     libd__fwprintf_l
#define _fc32printf_l     libc__fwprintf_l
#define _vfc16printf_p_l  libd__vfwprintf_p_l
#define _vfc32printf_p_l  libc__vfwprintf_p_l
#define _fc16printf_p_l   libd__fwprintf_p_l
#define _fc32printf_p_l   libc__fwprintf_p_l
#define _vfc16printf_s_l  libd__vfwprintf_s_l
#define _vfc32printf_s_l  libc__vfwprintf_s_l
#define _fc16printf_s_l   libd__fwprintf_s_l
#define _fc32printf_s_l   libc__fwprintf_s_l
#define _vsc16printf_c_l  libd__vswprintf_c_l
#define _vsc32printf_c_l  libc__vswprintf_c_l
#define _sc16printf_c_l   libd__swprintf_c_l
#define _sc32printf_c_l   libc__swprintf_c_l
#define _vsc16printf_p_l  libd__vswprintf_p_l
#define _vsc32printf_p_l  libc__vswprintf_p_l
#define _sc16printf_p_l   libd__swprintf_p_l
#define _sc32printf_p_l   libc__swprintf_p_l
#define _vsc16printf_s_l  libd__vswprintf_s_l
#define _vsc32printf_s_l  libc__vswprintf_s_l
#define _sc16printf_s_l   libd__swprintf_s_l
#define _sc32printf_s_l   libc__swprintf_s_l
#define _vsnc16printf_l   libd__vsnwprintf_l
#define _vsnc32printf_l   libc__vsnwprintf_l
#define _snc16printf_l    libd__snwprintf_l
#define _snc32printf_l    libc__snwprintf_l
#define _vsnc16printf_s_l libd__vsnwprintf_s_l
#define _vsnc32printf_s_l libc__vsnwprintf_s_l
#define _snc16printf_s_l  libd__snwprintf_s_l
#define _snc32printf_s_l  libc__snwprintf_s_l
#define _vfc16scanf_l     libd__vfwscanf_l
#define _vfc32scanf_l     libc__vfwscanf_l
#define _fc16scanf_l      libd__fwscanf_l
#define _fc32scanf_l      libc__fwscanf_l
#define _vsc16scanf_l     libd__vswscanf_l
#define _vsc32scanf_l     libc__vswscanf_l
#define _sc16scanf_l      libd__swscanf_l
#define _sc32scanf_l      libc__swscanf_l
#define _vsnc16scanf      libd__vsnwscanf
#define _vsnc32scanf      libc__vsnwscanf
#define _snc16scanf       libd__snwscanf
#define _snc32scanf       libc__snwscanf
#define _vsnc16scanf_l    libd__vsnwscanf_l
#define _vsnc32scanf_l    libc__vsnwscanf_l
#define _snc16scanf_l     libd__snwscanf_l
#define _snc32scanf_l     libc__snwscanf_l
#define _vsnc16scanf_s_l  libd__vsnwscanf_s_l
#define _vsnc32scanf_s_l  libc__vsnwscanf_s_l
#define _snc16scanf_s_l   libd__snwscanf_s_l
#define _snc32scanf_s_l   libc__snwscanf_s_l
#define _vc16scanf_l      libd__vwscanf_l
#define _vc32scanf_l      libc__vwscanf_l
#define _c16scanf_l       libd__wscanf_l
#define _c32scanf_l       libc__wscanf_l
#define _c16fsopen        libd__wfsopen
#define _c32fsopen        libc__wfsopen
#define _c16fdopen        libd__wfdopen
#define _c32fdopen        libc__wfdopen
#define _c16fopen_s       libd__wfopen_s
#define _c32fopen_s       libc__wfopen_s
#define _c16freopen_s     libd__wfreopen_s
#define _c32freopen_s     libc__wfreopen_s
#define _getc16s_s        libd__getws_s
#define _getc32s_s        libc__getws_s
#define _putc16s          libd__putws
#define _putc32s          libc__putws
#define _c16tempnam       libd__wtempnam
#define _c32tempnam       libc__wtempnam
#define _c16tmpnam_s      libd__wtmpnam_s
#define _c32tmpnam_s      libc__wtmpnam_s
#define __p___c16argv     libd___p___wargv
#define __p___c32argv     libc___p___wargv
#define __p__c16environ   libd___p__wenviron
#define __p__c32environ   libc___p__wenviron
#define __p__c16pgmptr    libd___p__wpgmptr
#define __p__c32pgmptr    libc___p__wpgmptr
#define _get_c16pgmptr    libd__get_wpgmptr
#define _get_c32pgmptr    libc__get_wpgmptr
#define _mbtoc16_l        libd__mbtowc_l
#define _mbtoc32_l        libc__mbtowc_l
#define _mbstoc16s_l      libd__mbstowcs_l
#define _mbstoc32s_l      libc__mbstowcs_l
#define _mbstoc16s_s      libd__mbstowcs_s
#define _mbstoc32s_s      libc__mbstowcs_s
#define _mbstoc16s_s_l    libd__mbstowcs_s_l
#define _mbstoc32s_s_l    libc__mbstowcs_s_l
#define c16tomb_s         libd_wctomb_s
#define c32tomb_s         libc_wctomb_s
#define _c16tomb_s_l      libd__wctomb_s_l
#define _c32tomb_s_l      libc__wctomb_s_l
#define _c16stombs_s_l    libd__wcstombs_s_l
#define _c32stombs_s_l    libc__wcstombs_s_l
#define _c16stombs_l      libd__wcstombs_l
#define _c32stombs_l      libc__wcstombs_l
#define c16stombs_s       libd_wcstombs_s
#define c32stombs_s       libc_wcstombs_s
#define _c16getenv        libd__wgetenv
#define _c32getenv        libc__wgetenv
#define _c16getenv_s      libd__wgetenv_s
#define _c32getenv_s      libc__wgetenv_s
#define _c16dupenv_s      libd__wdupenv_s
#define _c32dupenv_s      libc__wdupenv_s
#define _c16tof           libd__wtof
#define _c32tof           libc__wtof
#define _c16tof_l         libd__wtof_l
#define _c32tof_l         libc__wtof_l
#define _itoc16           libd__itow
#define _itoc32           libc__itow
#define _ltoc16           libd__ltow
#define _ltoc32           libc__ltow
#define _ultoc16          libd__ultow
#define _ultoc32          libc__ultow
#define _i64toc16         libd__i64tow
#define _i64toc32         libc__i64tow
#define _ui64toc16        libd__ui64tow
#define _ui64toc32        libc__ui64tow
#define _itoc16_s         libd__itow_s
#define _itoc32_s         libc__itow_s
#define _ltoc16_s         libd__ltow_s
#define _ltoc32_s         libc__ltow_s
#define _ultoc16_s        libd__ultow_s
#define _ultoc32_s        libc__ultow_s
#define _i64toc16_s       libd__i64tow_s
#define _i64toc32_s       libc__i64tow_s
#define _ui64toc16_s      libd__ui64tow_s
#define _ui64toc32_s      libc__ui64tow_s
#define _c16toi64         libd__wtoi64
#define _c32toi64         libc__wtoi64
#define _c16toi_l         libd__wtoi_l
#define _c32toi_l         libc__wtoi_l
#define _c16tol_l         libd__wtol_l
#define _c32tol_l         libc__wtol_l
#define _c16toi64_l       libd__wtoi64_l
#define _c32toi64_l       libc__wtoi64_l
#define _c16toll_l        libd__wtoll_l
#define _c32toll_l        libc__wtoll_l
#define _vscanf_l         libc__vscanf_l
#define _vfscanf_l        libc__vfscanf_l
#define _vsscanf_l        libc__vsscanf_l
#define _vscanf_s         libc__vscanf_s
#define _vscanf_s_l       libc__vscanf_s_l
#define _vfscanf          libc__vfscanf
#define _vfscanf_s        libc__vfscanf_s
#define _vfscanf_s_l      libc__vfscanf_s_l
#define _vsscanf          libc__vsscanf
#define _vsscanf_s        libc__vsscanf_s
#define _vsscanf_s_l      libc__vsscanf_s_l
#define _vsnscanf         libc__vsnscanf
#define _vsnscanf_s       libc__vsnscanf_s
#define _vsnscanf_l       libc__vsnscanf_l
#define _vsnscanf_s_l     libc__vsnscanf_s_l
#ifdef __CC__
#undef __DEFINE_PRIVATE_ALIAS
#undef __DEFINE_PUBLIC_ALIAS
#undef __DEFINE_INTERN_ALIAS
#undef __DEFINE_PRIVATE_WEAK_ALIAS
#undef __DEFINE_PUBLIC_WEAK_ALIAS
#undef __DEFINE_INTERN_WEAK_ALIAS
/* Work-around required due to the macros above! */
#define __DEFINE_PRIVATE_ALIAS(new, old)      __asm__(".local " #new "\n.set " #new "," #old "\n")
#define __DEFINE_PUBLIC_ALIAS(new, old)       __asm__(".global " #new "\n.set " #new "," #old "\n")
#define __DEFINE_INTERN_ALIAS(new, old)       __asm__(".global " #new "\n.hidden " #new "\n.set " #new "," #old "\n")
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) __asm__(".weak " #new "\n.local " #new "\n.set " #new "," #old "\n")
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __asm__(".weak " #new "\n.global " #new "\n.set " #new "," #old "\n")
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __asm__(".weak " #new "\n.global " #new "\n.hidden " #new "\n.set " #new "," #old "\n")
#endif /* __CC__ */
/* TODO:REMOVE_ME:END */


/* Delete CRT features for stuff that we don't implement (yet)
 * TODO: Once we do implement this stuff, delete this part! */
#undef __CRT_HAVE___ctype_b_loc
#undef __CRT_HAVE___ctype_tolower_loc
#undef __CRT_HAVE___ctype_toupper_loc
#undef __CRT_HAVE___locale_ctype_ptr
#undef __CRT_HAVE___locale_ctype_ptr_l
#undef __CRT_HAVE__isctype
#define __CRT_HAVE_unicode_utf8seqlen 1

/* Indicate that we have support for all of the different assert functions. */
#define __CRT_HAVE___afail       1
#define __CRT_HAVE___afailf      1
#define __CRT_HAVE___assert      1
#define __CRT_HAVE___assert_fail 1
#define __CRT_HAVE___assert_func 1
#define __CRT_HAVE___assertfail  1
#define __CRT_HAVE__assert       1

/* Do some quick probing if crt linkage was configured correctly */
#ifndef __CRT_HAVE_memmove
#error "Bad libc build environment"
#endif /* !__CRT_HAVE_memmove */


#ifdef __KERNEL__
#include <kernel/compiler.h>
#endif /* __KERNEL__ */

#define LIBCCALL  __LIBCCALL
#define LIBDCALL  __LIBDCALL
#define LIBKCALL  __LIBKCALL
#define VLIBCCALL __VLIBCCALL
#define VLIBDCALL __VLIBDCALL
#define VLIBKCALL __VLIBKCALL

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */
#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */

#define ATTR_LIBC_PRINTF(a, b)    __ATTR_LIBC_PRINTF(a, b)
#define ATTR_LIBC_PRINTF_P(a, b)  __ATTR_LIBC_PRINTF_P(a, b)
#define ATTR_LIBC_SCANF(a, b)     __ATTR_LIBC_SCANF(a, b)
#define ATTR_LIBC_STRFMON(a, b)   __ATTR_LIBC_STRFMON(a, b)
#define ATTR_LIBC_WPRINTF(a, b)   __ATTR_LIBC_WPRINTF(a, b)
#define ATTR_LIBC_WPRINTF_P(a, b) __ATTR_LIBC_WPRINTF_P(a, b)
#define ATTR_LIBC_WSCANF(a, b)    __ATTR_LIBC_WSCANF(a, b)

#include <ctype.h>

#define libc_isalnum(ch)  isalnum(ch)
#define libc_isalpha(ch)  isalpha(ch)
#define libc_isupper(ch)  isupper(ch)
#define libc_islower(ch)  islower(ch)
#define libc_isdigit(ch)  isdigit(ch)
#define libc_isxdigit(ch) isxdigit(ch)
#define libc_isspace(ch)  isspace(ch)
#define libc_ispunct(ch)  ispunct(ch)
#define libc_isprint(ch)  isprint(ch)
#define libc_isgraph(ch)  isgraph(ch)
#define libc_iscntrl(ch)  iscntrl(ch)
#ifdef __USE_ISOC99
#define libc_isblank(ch) isblank(ch)
#endif /* __USE_ISOC99 */


#include <parts/dos/errno.h>
#include <parts/errno.h>
#include <parts/generic/errno.h>

#include <errno.h>

#define libc_seterrno_syserr(e) \
	(likely(!E_ISERR(e)) ? (e) : libc_seterrno((errno_t) - (syscall_slong_t)(syscall_ulong_t)(e)))
#define libc_seterrno_syserr2(e, ERR) \
	(likely(!E_ISERR(e)) ? (e) : (libc_seterrno((errno_t) - (syscall_slong_t)(syscall_ulong_t)(e)), (ERR)))
#define ISSEP(x)           ((x) == '/') /* TODO: In DOS-mode, `\\' must also be accepted */
#define GET_PATHLIST_SEP() ':'          /* TODO: In DOS-mode, `;' must be used */


#define ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALL_DEFAULT_ALIGNED
#define ATTR_MALL_PAGEALIGNED     __ATTR_MALL_PAGEALIGNED

/* Attribute for global data that is mostly read from */
#ifndef ATTR_READMOSTLY
#define ATTR_READMOSTLY ATTR_SECTION(".data.read_mostly")
#endif /* !ATTR_READMOSTLY */


/* Re-bind errno memory locations. */
#undef errno
#undef __errno
#undef __libc_geterrno
#undef __libc_geterrno_or
#undef __libc_seterrno
#define errno                   (*libc_errno_p())
#define __errno                 (*libc_errno_p())
#define __libc_geterrno         libc_geterrno
#define __libc_geterrno_or(alt) libc_geterrno()
#define __libc_seterrno         libc_seterrno

#undef ____errno_location_defined
#define ____errno_location_defined 1
#define __errno_location()         libc_errno_p()

#ifdef __CC__
DECL_BEGIN

#ifndef __locale_t_defined
#define __locale_t_defined 1
typedef __locale_t locale_t;
#endif /* !__locale_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

#ifndef __KERNEL__
INTDEF NOBLOCK ATTR_CONST errno_t *NOTHROW(LIBCCALL libc_errno_p)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void);
/* Always returns (syscall_slong_t)-1 */
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(errno_t value);

#if 1
#define CONFIG_LOG_LIBC_UNIMPLEMENTED 1
INTDEF void LIBCCALL libc_unimplemented(char const *__restrict name);
#define CRT_UNIMPLEMENTED(name) libc_unimplemented(name)
#else
#define CRT_UNIMPLEMENTED(name) (void)0
#endif
#else /* !__KERNEL__ */
/* The kernel doesn't have an ERRNO binding */
#undef libc_seterrno_syserr
#undef libc_seterrno_syserr2
#undef errno
#undef __errno
#undef __libc_geterrno
#undef __libc_geterrno_or
#undef __libc_seterrno
#undef __errno_location
#define __libc_geterrno_or(alt) alt
#define __libc_seterrno(v)      (void)0
#endif /* __KERNEL__ */


DECL_END


#ifndef __KERNEL__
#if defined(__OPTIMIZE_SIZE__)
/* Disable norel access. */
#define GET_NOREL_GLOBAL(name)             __bind_##name
#define DECLARE_NOREL_GLOBAL_META(T, name) DATDEF T __bind_##name ASMNAME(#name)
#define DEFINE_NOREL_GLOBAL_META(T, name)  DATDEF T __bind_##name ASMNAME(#name)
#else /* __OPTIMIZE_SIZE__ */
#define GET_NOREL_GLOBAL(name) (*(__pdyn_##name ? __pdyn_##name : __##name##_impl()))
#define DECLARE_NOREL_GLOBAL_META(T, name) \
	INTDEF T *__pdyn_##name;               \
	INTDEF ATTR_CONST T *(LIBCCALL __##name##_impl)(void)
#ifdef __INTELLISENSE__
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                            \
	INTERN ATTR_SECTION(".bss" section "." #name) T *__pdyn_##name               = __NULLPTR; \
	PRIVATE ATTR_SECTION(".rodata" section "." #name) char const __name_##name[] = #name;     \
	INTERN ATTR_CONST ATTR_SECTION(".text" section "." #name) T *(LIBCCALL __##name##_impl)(void)
#else /* __INTELLISENSE__ */
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <dlfcn.h>
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                                  \
	INTERN ATTR_SECTION(".bss" section "." #name) T *__pdyn_##name               = __NULLPTR;       \
	PRIVATE ATTR_SECTION(".rodata" section "." #name) char const __name_##name[] = #name;           \
	INTERN ATTR_CONST ATTR_SECTION(".text" section "." #name) T *(LIBCCALL __##name##_impl)(void) { \
		T *ptr = (T *)dlsym(RTLD_DEFAULT, __name_##name);                                           \
		__hybrid_assert(ptr);                                                                       \
		__hybrid_atomic_store(__pdyn_##name, ptr, __ATOMIC_RELEASE);                                \
		return ptr;                                                                                 \
	}
#endif /* !__INTELLISENSE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__KERNEL__ */

#endif /* __CC__ */


#endif /* !GUARD_LIBC_API_H */
