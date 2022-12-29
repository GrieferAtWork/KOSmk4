/* HASH CRC-32:0x2cc9adfa */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/langinfo.h) */
/* (#) Portability: DragonFly BSD (/include/langinfo.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/langinfo.h) */
/* (#) Portability: FreeBSD       (/include/langinfo.h) */
/* (#) Portability: GNU C Library (/locale/langinfo.h) */
/* (#) Portability: GNU Hurd      (/usr/include/langinfo.h) */
/* (#) Portability: NetBSD        (/include/langinfo.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/langinfo.h) */
/* (#) Portability: OpenBSD       (/include/langinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/langinfo.h) */
/* (#) Portability: diet libc     (/include/langinfo.h) */
/* (#) Portability: libc6         (/include/langinfo.h) */
/* (#) Portability: musl libc     (/include/langinfo.h) */
/* (#) Portability: uClibc        (/include/langinfo.h) */
#ifndef _LANGINFO_H
#define _LANGINFO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/langinfo.h>
#include <nl_types.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

#ifdef __CC__
__SYSDECL_BEGIN

/* Construct an index for use with `nl_langinfo(3)' or `nl_langinfo_l(3)',
 * that will return the name of the locale currently used for  `category'.
 * @param: category: One of `LC_*' from <locale.h> */
#define _NL_LOCALE_NAME(category) _NL_ITEM(category, 0xffff)
#ifdef __USE_GNU
#define NL_LOCALE_NAME(category) _NL_LOCALE_NAME(category)
#endif /* __USE_GNU */

/* Possible values for `nl_langinfo(3)' */
#define ABDAY_1              _NL_TIME_ABDAY_1                /* "Sun" */
#define ABDAY_2              _NL_TIME_ABDAY_2                /* "Mon" */
#define ABDAY_3              _NL_TIME_ABDAY_3                /* "Tue" */
#define ABDAY_4              _NL_TIME_ABDAY_4                /* "Wed" */
#define ABDAY_5              _NL_TIME_ABDAY_5                /* "Thu" */
#define ABDAY_6              _NL_TIME_ABDAY_6                /* "Fri" */
#define ABDAY_7              _NL_TIME_ABDAY_7                /* "Sat" */
#define DAY_1                _NL_TIME_DAY_1                  /* "Sunday" */
#define DAY_2                _NL_TIME_DAY_2                  /* "Monday" */
#define DAY_3                _NL_TIME_DAY_3                  /* "Tuesday" */
#define DAY_4                _NL_TIME_DAY_4                  /* "Wednesday" */
#define DAY_5                _NL_TIME_DAY_5                  /* "Thursday" */
#define DAY_6                _NL_TIME_DAY_6                  /* "Friday" */
#define DAY_7                _NL_TIME_DAY_7                  /* "Saturday" */
#define ABMON_1              _NL_TIME_ABMON_1                /* "Jan" */
#define ABMON_2              _NL_TIME_ABMON_2                /* "Feb" */
#define ABMON_3              _NL_TIME_ABMON_3                /* "Mar" */
#define ABMON_4              _NL_TIME_ABMON_4                /* "Apr" */
#define ABMON_5              _NL_TIME_ABMON_5                /* "May" */
#define ABMON_6              _NL_TIME_ABMON_6                /* "Jun" */
#define ABMON_7              _NL_TIME_ABMON_7                /* "Jul" */
#define ABMON_8              _NL_TIME_ABMON_8                /* "Aug" */
#define ABMON_9              _NL_TIME_ABMON_9                /* "Sep" */
#define ABMON_10             _NL_TIME_ABMON_10               /* "Oct" */
#define ABMON_11             _NL_TIME_ABMON_11               /* "Nov" */
#define ABMON_12             _NL_TIME_ABMON_12               /* "Dec" */
#define MON_1                _NL_TIME_MON_1                  /* "January" */
#define MON_2                _NL_TIME_MON_2                  /* "February" */
#define MON_3                _NL_TIME_MON_3                  /* "March" */
#define MON_4                _NL_TIME_MON_4                  /* "April" */
#define MON_5                _NL_TIME_MON_5                  /* "May" */
#define MON_6                _NL_TIME_MON_6                  /* "June" */
#define MON_7                _NL_TIME_MON_7                  /* "July" */
#define MON_8                _NL_TIME_MON_8                  /* "August" */
#define MON_9                _NL_TIME_MON_9                  /* "September" */
#define MON_10               _NL_TIME_MON_10                 /* "October" */
#define MON_11               _NL_TIME_MON_11                 /* "November" */
#define MON_12               _NL_TIME_MON_12                 /* "December" */
#define AM_STR               _NL_TIME_AM_STR                 /* "AM" */
#define PM_STR               _NL_TIME_PM_STR                 /* "PM" */
#define D_T_FMT              _NL_TIME_D_T_FMT                /* "%a %b %e %H:%M:%S %Y" */
#define D_FMT                _NL_TIME_D_FMT                  /* "%m/%d/%y" */
#define T_FMT                _NL_TIME_T_FMT                  /* "%H:%M:%S" */
#define T_FMT_AMPM           _NL_TIME_T_FMT_AMPM             /* "%I:%M:%S %p" */
#define ERA                  _NL_TIME_ERA                    /* "" */
#define __ERA_YEAR           _NL_TIME_ERA_YEAR               /* "" */
#define ERA_D_FMT            _NL_TIME_ERA_D_FMT              /* "" */
#define ALT_DIGITS           _NL_TIME_ALT_DIGITS             /* "" */
#define ERA_D_T_FMT          _NL_TIME_ERA_D_T_FMT            /* "" */
#define ERA_T_FMT            _NL_TIME_ERA_T_FMT              /* "" */
#define _NL_WABDAY_1         _NL_TIME_WABDAY_1               /* L"Sun" */
#define _NL_WABDAY_2         _NL_TIME_WABDAY_2               /* L"Mon" */
#define _NL_WABDAY_3         _NL_TIME_WABDAY_3               /* L"Tue" */
#define _NL_WABDAY_4         _NL_TIME_WABDAY_4               /* L"Wed" */
#define _NL_WABDAY_5         _NL_TIME_WABDAY_5               /* L"Thu" */
#define _NL_WABDAY_6         _NL_TIME_WABDAY_6               /* L"Fri" */
#define _NL_WABDAY_7         _NL_TIME_WABDAY_7               /* L"Sat" */
#define _NL_WDAY_1           _NL_TIME_WDAY_1                 /* L"Sunday" */
#define _NL_WDAY_2           _NL_TIME_WDAY_2                 /* L"Monday" */
#define _NL_WDAY_3           _NL_TIME_WDAY_3                 /* L"Tuesday" */
#define _NL_WDAY_4           _NL_TIME_WDAY_4                 /* L"Wednesday" */
#define _NL_WDAY_5           _NL_TIME_WDAY_5                 /* L"Thursday" */
#define _NL_WDAY_6           _NL_TIME_WDAY_6                 /* L"Friday" */
#define _NL_WDAY_7           _NL_TIME_WDAY_7                 /* L"Saturday" */
#define _NL_WABMON_1         _NL_TIME_WABMON_1               /* L"Jan" */
#define _NL_WABMON_2         _NL_TIME_WABMON_2               /* L"Feb" */
#define _NL_WABMON_3         _NL_TIME_WABMON_3               /* L"Mar" */
#define _NL_WABMON_4         _NL_TIME_WABMON_4               /* L"Apr" */
#define _NL_WABMON_5         _NL_TIME_WABMON_5               /* L"May" */
#define _NL_WABMON_6         _NL_TIME_WABMON_6               /* L"Jun" */
#define _NL_WABMON_7         _NL_TIME_WABMON_7               /* L"Jul" */
#define _NL_WABMON_8         _NL_TIME_WABMON_8               /* L"Aug" */
#define _NL_WABMON_9         _NL_TIME_WABMON_9               /* L"Sep" */
#define _NL_WABMON_10        _NL_TIME_WABMON_10              /* L"Oct" */
#define _NL_WABMON_11        _NL_TIME_WABMON_11              /* L"Nov" */
#define _NL_WABMON_12        _NL_TIME_WABMON_12              /* L"Dec" */
#define _NL_WMON_1           _NL_TIME_WMON_1                 /* L"January" */
#define _NL_WMON_2           _NL_TIME_WMON_2                 /* L"February" */
#define _NL_WMON_3           _NL_TIME_WMON_3                 /* L"March" */
#define _NL_WMON_4           _NL_TIME_WMON_4                 /* L"April" */
#define _NL_WMON_5           _NL_TIME_WMON_5                 /* L"May" */
#define _NL_WMON_6           _NL_TIME_WMON_6                 /* L"June" */
#define _NL_WMON_7           _NL_TIME_WMON_7                 /* L"July" */
#define _NL_WMON_8           _NL_TIME_WMON_8                 /* L"August" */
#define _NL_WMON_9           _NL_TIME_WMON_9                 /* L"September" */
#define _NL_WMON_10          _NL_TIME_WMON_10                /* L"October" */
#define _NL_WMON_11          _NL_TIME_WMON_11                /* L"November" */
#define _NL_WMON_12          _NL_TIME_WMON_12                /* L"December" */
#define _NL_WAM_STR          _NL_TIME_WAM_STR                /* L"AM" */
#define _NL_WPM_STR          _NL_TIME_WPM_STR                /* L"PM" */
#define _NL_WD_T_FMT         _NL_TIME_WD_T_FMT               /* L"%a %b %e %H:%M:%S %Y" */
#define _NL_WD_FMT           _NL_TIME_WD_FMT                 /* L"%m/%d/%y" */
#define _NL_WT_FMT           _NL_TIME_WT_FMT                 /* L"%H:%M:%S" */
#define _NL_WT_FMT_AMPM      _NL_TIME_WT_FMT_AMPM            /* L"%I:%M:%S %p" */
#define _NL_WERA_YEAR        _NL_TIME_WERA_YEAR              /* L"" */
#define _NL_WERA_D_FMT       _NL_TIME_WERA_D_FMT             /* L"" */
#define _NL_WALT_DIGITS      _NL_TIME_WALT_DIGITS            /* L"" */
#define _NL_WERA_D_T_FMT     _NL_TIME_WERA_D_T_FMT           /* L"" */
#define _NL_WERA_T_FMT       _NL_TIME_WERA_T_FMT             /* L"" */
#define _DATE_FMT            _NL_TIME_DATE_FMT               /* "%a %b %e %H:%M:%S %Z %Y" */
#define _NL_W_DATE_FMT       _NL_TIME_W_DATE_FMT             /* L"%a %b %e %H:%M:%S %Z %Y" */
#define __INT_CURR_SYMBOL    _NL_MONETARY_INT_CURR_SYMBOL    /* "" */
#define __CURRENCY_SYMBOL    _NL_MONETARY_CURRENCY_SYMBOL    /* "" */
#define __MON_DECIMAL_POINT  _NL_MONETARY_MON_DECIMAL_POINT  /* "" */
#define __MON_THOUSANDS_SEP  _NL_MONETARY_MON_THOUSANDS_SEP  /* "" */
#define __MON_GROUPING       _NL_MONETARY_MON_GROUPING       /* [0x00] [array-of-uint8_t] */
#define __POSITIVE_SIGN      _NL_MONETARY_POSITIVE_SIGN      /* "" */
#define __NEGATIVE_SIGN      _NL_MONETARY_NEGATIVE_SIGN      /* "" */
#define __INT_FRAC_DIGITS    _NL_MONETARY_INT_FRAC_DIGITS    /* 0xff [pointer-to-uint8_t] */
#define __FRAC_DIGITS        _NL_MONETARY_FRAC_DIGITS        /* 0xff [pointer-to-uint8_t] */
#define __P_CS_PRECEDES      _NL_MONETARY_P_CS_PRECEDES      /* 0xff [pointer-to-uint8_t] */
#define __P_SEP_BY_SPACE     _NL_MONETARY_P_SEP_BY_SPACE     /* 0xff [pointer-to-uint8_t] */
#define __N_CS_PRECEDES      _NL_MONETARY_N_CS_PRECEDES      /* 0xff [pointer-to-uint8_t] */
#define __N_SEP_BY_SPACE     _NL_MONETARY_N_SEP_BY_SPACE     /* 0xff [pointer-to-uint8_t] */
#define __P_SIGN_POSN        _NL_MONETARY_P_SIGN_POSN        /* 0xff [pointer-to-uint8_t] */
#define __N_SIGN_POSN        _NL_MONETARY_N_SIGN_POSN        /* 0xff [pointer-to-uint8_t] */
#define __INT_P_CS_PRECEDES  _NL_MONETARY_INT_P_CS_PRECEDES  /* 0xff [pointer-to-uint8_t] */
#define __INT_P_SEP_BY_SPACE _NL_MONETARY_INT_P_SEP_BY_SPACE /* 0xff [pointer-to-uint8_t] */
#define __INT_N_CS_PRECEDES  _NL_MONETARY_INT_N_CS_PRECEDES  /* 0xff [pointer-to-uint8_t] */
#define __INT_N_SEP_BY_SPACE _NL_MONETARY_INT_N_SEP_BY_SPACE /* 0xff [pointer-to-uint8_t] */
#define __INT_P_SIGN_POSN    _NL_MONETARY_INT_P_SIGN_POSN    /* 0xff [pointer-to-uint8_t] */
#define __INT_N_SIGN_POSN    _NL_MONETARY_INT_N_SIGN_POSN    /* 0xff [pointer-to-uint8_t] */
#define __DECIMAL_POINT      _NL_NUMERIC_DECIMAL_POINT       /* "." */
#define __THOUSANDS_SEP      _NL_NUMERIC_THOUSANDS_SEP       /* "" */
#define __GROUPING           _NL_NUMERIC_GROUPING            /* [0x00] [array-of-uint8_t] */
#define __YESEXPR            _NL_MESSAGES_YESEXPR            /* "^[yY]" */
#define __NOEXPR             _NL_MESSAGES_NOEXPR             /* "^[nN]" */
#define __YESSTR             _NL_MESSAGES_YESSTR             /* "" */
#define __NOSTR              _NL_MESSAGES_NOSTR              /* "" */
#define __ALTMON_1           _NL_TIME_ALTMON_1               /* "January" */
#define __ALTMON_2           _NL_TIME_ALTMON_2               /* "February" */
#define __ALTMON_3           _NL_TIME_ALTMON_3               /* "March" */
#define __ALTMON_4           _NL_TIME_ALTMON_4               /* "April" */
#define __ALTMON_5           _NL_TIME_ALTMON_5               /* "May" */
#define __ALTMON_6           _NL_TIME_ALTMON_6               /* "June" */
#define __ALTMON_7           _NL_TIME_ALTMON_7               /* "July" */
#define __ALTMON_8           _NL_TIME_ALTMON_8               /* "August" */
#define __ALTMON_9           _NL_TIME_ALTMON_9               /* "September" */
#define __ALTMON_10          _NL_TIME_ALTMON_10              /* "October" */
#define __ALTMON_11          _NL_TIME_ALTMON_11              /* "November" */
#define __ALTMON_12          _NL_TIME_ALTMON_12              /* "December" */

/* Some more unescaped aliases for `nl_langinfo(3)' */
#define CODESET   _NL_CTYPE_CODESET_NAME /* "utf-8" */
#define CRNCYSTR  _NL_MONETARY_CRNCYSTR  /* "-" */
#define RADIXCHAR __DECIMAL_POINT        /* "." */
#define THOUSEP   __THOUSANDS_SEP        /* "" */
#define YESEXPR   __YESEXPR              /* "^[yY]" */
#define NOEXPR    __NOEXPR               /* "^[nN]" */

/* Feature-specific aliases for `nl_langinfo(3)' */
#ifdef __USE_GNU
#define ERA_YEAR           __ERA_YEAR           /* "" */
#define INT_CURR_SYMBOL    __INT_CURR_SYMBOL    /* "" */
#define CURRENCY_SYMBOL    __CURRENCY_SYMBOL    /* "" */
#define MON_DECIMAL_POINT  __MON_DECIMAL_POINT  /* "" */
#define MON_THOUSANDS_SEP  __MON_THOUSANDS_SEP  /* "" */
#define MON_GROUPING       __MON_GROUPING       /* [0x00] [array-of-uint8_t] */
#define POSITIVE_SIGN      __POSITIVE_SIGN      /* "" */
#define NEGATIVE_SIGN      __NEGATIVE_SIGN      /* "" */
#define INT_FRAC_DIGITS    __INT_FRAC_DIGITS    /* 0xff [pointer-to-uint8_t] */
#define FRAC_DIGITS        __FRAC_DIGITS        /* 0xff [pointer-to-uint8_t] */
#define P_CS_PRECEDES      __P_CS_PRECEDES      /* 0xff [pointer-to-uint8_t] */
#define P_SEP_BY_SPACE     __P_SEP_BY_SPACE     /* 0xff [pointer-to-uint8_t] */
#define N_CS_PRECEDES      __N_CS_PRECEDES      /* 0xff [pointer-to-uint8_t] */
#define N_SEP_BY_SPACE     __N_SEP_BY_SPACE     /* 0xff [pointer-to-uint8_t] */
#define P_SIGN_POSN        __P_SIGN_POSN        /* 0xff [pointer-to-uint8_t] */
#define N_SIGN_POSN        __N_SIGN_POSN        /* 0xff [pointer-to-uint8_t] */
#define INT_P_CS_PRECEDES  __INT_P_CS_PRECEDES  /* 0xff [pointer-to-uint8_t] */
#define INT_P_SEP_BY_SPACE __INT_P_SEP_BY_SPACE /* 0xff [pointer-to-uint8_t] */
#define INT_N_CS_PRECEDES  __INT_N_CS_PRECEDES  /* 0xff [pointer-to-uint8_t] */
#define INT_N_SEP_BY_SPACE __INT_N_SEP_BY_SPACE /* 0xff [pointer-to-uint8_t] */
#define INT_P_SIGN_POSN    __INT_P_SIGN_POSN    /* 0xff [pointer-to-uint8_t] */
#define INT_N_SIGN_POSN    __INT_N_SIGN_POSN    /* 0xff [pointer-to-uint8_t] */
#define DECIMAL_POINT      __DECIMAL_POINT      /* "." */
#define THOUSANDS_SEP      __THOUSANDS_SEP      /* "" */
#define GROUPING           __GROUPING           /* [0x00] [array-of-uint8_t] */
#define ALTMON_1           _NL_TIME_ALTMON_1    /* "January" */
#define ALTMON_2           _NL_TIME_ALTMON_2    /* "February" */
#define ALTMON_3           _NL_TIME_ALTMON_3    /* "March" */
#define ALTMON_4           _NL_TIME_ALTMON_4    /* "April" */
#define ALTMON_5           _NL_TIME_ALTMON_5    /* "May" */
#define ALTMON_6           _NL_TIME_ALTMON_6    /* "June" */
#define ALTMON_7           _NL_TIME_ALTMON_7    /* "July" */
#define ALTMON_8           _NL_TIME_ALTMON_8    /* "August" */
#define ALTMON_9           _NL_TIME_ALTMON_9    /* "September" */
#define ALTMON_10          _NL_TIME_ALTMON_10   /* "October" */
#define ALTMON_11          _NL_TIME_ALTMON_11   /* "November" */
#define ALTMON_12          _NL_TIME_ALTMON_12   /* "December" */
#endif /* __USE_GNU */
#if defined(__USE_GNU) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#define YESSTR __YESSTR /* "" */
#define NOSTR  __NOSTR  /* "" */
#endif /* __USE_GNU || (__USE_XOPEN && !__USE_XOPEN2K) */

#ifdef __CRT_HAVE_nl_langinfo
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
__CDECLARE(__ATTR_RETNONNULL,char __KOS_FIXED_CONST *,__NOTHROW_NCX,nl_langinfo,(__STDC_INT_AS_UINT_T __item),(__item))
#else /* __CRT_HAVE_nl_langinfo */
#include <libc/local/langinfo/nl_langinfo.h>
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(nl_langinfo, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char __KOS_FIXED_CONST *__NOTHROW_NCX(__LIBCCALL nl_langinfo)(__STDC_INT_AS_UINT_T __item) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nl_langinfo))(__item); })
#endif /* !__CRT_HAVE_nl_langinfo */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_nl_langinfo_l
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
__CDECLARE(__ATTR_RETNONNULL,char __KOS_FIXED_CONST *,__NOTHROW_NCX,nl_langinfo_l,(__STDC_INT_AS_UINT_T __item, __locale_t __locale),(__item,__locale))
#elif defined(__CRT_HAVE___nl_langinfo_l)
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
__CREDIRECT(__ATTR_RETNONNULL,char __KOS_FIXED_CONST *,__NOTHROW_NCX,nl_langinfo_l,(__STDC_INT_AS_UINT_T __item, __locale_t __locale),__nl_langinfo_l,(__item,__locale))
#else /* ... */
#include <libc/local/langinfo/nl_langinfo_l.h>
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(nl_langinfo_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char __KOS_FIXED_CONST *__NOTHROW_NCX(__LIBCCALL nl_langinfo_l)(__STDC_INT_AS_UINT_T __item, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nl_langinfo_l))(__item, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LANGINFO_H */
