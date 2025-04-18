/* HASH CRC-32:0xdb369747 */
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
/* (#) Portability: libbsd (/include/bsd/inttypes.h) */
/*!always_includes <inttypes.h>*/
#ifndef _BSD_INTTYPES_H
#define _BSD_INTTYPES_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <inttypes.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __strtoi_defined
#define __strtoi_defined
#ifdef __CRT_HAVE_strtoi
/* >> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
 * Safely convert `nptr'  to an integer  which is then  returned.
 * If no integer  could be read,  set `*rstatus' (if  non-`NULL')
 * to `ECANCELED'.  If non-`NULL',  `*endptr'  is made  to  point
 * past the  read  integer,  and  if it  points  to  a  non-'\0'-
 * character,  `*rstatus'  (if non-`NULL')  is set  to `ENOTSUP'.
 * Also  make  sure that  the  returned integer  lies  within the
 * bounds of `[lo,hi]'  (inclusively). If it  does not, clamp  it
 * to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
 * @param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
 * @param: rstatus: When non-`NULL', set to a conversion error (if any) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(6),__INTMAX_TYPE__,__NOTHROW_NCX,strtoi,(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __INTMAX_TYPE__ __lo, __INTMAX_TYPE__ __hi, __errno_t *__rstatus),(__nptr,__endptr,__base,__lo,__hi,__rstatus))
#else /* __CRT_HAVE_strtoi */
#include <libc/local/inttypes/strtoi.h>
/* >> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
 * Safely convert `nptr'  to an integer  which is then  returned.
 * If no integer  could be read,  set `*rstatus' (if  non-`NULL')
 * to `ECANCELED'.  If non-`NULL',  `*endptr'  is made  to  point
 * past the  read  integer,  and  if it  points  to  a  non-'\0'-
 * character,  `*rstatus'  (if non-`NULL')  is set  to `ENOTSUP'.
 * Also  make  sure that  the  returned integer  lies  within the
 * bounds of `[lo,hi]'  (inclusively). If it  does not, clamp  it
 * to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
 * @param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
 * @param: rstatus: When non-`NULL', set to a conversion error (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(6) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoi)(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __INTMAX_TYPE__ __lo, __INTMAX_TYPE__ __hi, __errno_t *__rstatus) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoi))(__nptr, __endptr, __base, __lo, __hi, __rstatus); })
#endif /* !__CRT_HAVE_strtoi */
#endif /* !__strtoi_defined */
#ifndef __strtou_defined
#define __strtou_defined
#ifdef __CRT_HAVE_strtou
/* >> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
 * Safely convert `nptr'  to an integer  which is then  returned.
 * If no integer  could be read,  set `*rstatus' (if  non-`NULL')
 * to `ECANCELED'.  If non-`NULL',  `*endptr'  is made  to  point
 * past the  read  integer,  and  if it  points  to  a  non-'\0'-
 * character,  `*rstatus'  (if non-`NULL')  is set  to `ENOTSUP'.
 * Also  make  sure that  the  returned integer  lies  within the
 * bounds of `[lo,hi]'  (inclusively). If it  does not, clamp  it
 * to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
 * @param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
 * @param: rstatus: When non-`NULL', set to a conversion error (if any) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(6),__UINTMAX_TYPE__,__NOTHROW_NCX,strtou,(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __UINTMAX_TYPE__ __lo, __UINTMAX_TYPE__ __hi, __errno_t *__rstatus),(__nptr,__endptr,__base,__lo,__hi,__rstatus))
#else /* __CRT_HAVE_strtou */
#include <libc/local/inttypes/strtou.h>
/* >> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
 * Safely convert `nptr'  to an integer  which is then  returned.
 * If no integer  could be read,  set `*rstatus' (if  non-`NULL')
 * to `ECANCELED'.  If non-`NULL',  `*endptr'  is made  to  point
 * past the  read  integer,  and  if it  points  to  a  non-'\0'-
 * character,  `*rstatus'  (if non-`NULL')  is set  to `ENOTSUP'.
 * Also  make  sure that  the  returned integer  lies  within the
 * bounds of `[lo,hi]'  (inclusively). If it  does not, clamp  it
 * to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
 * @param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
 * @param: rstatus: When non-`NULL', set to a conversion error (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(6) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou)(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __UINTMAX_TYPE__ __lo, __UINTMAX_TYPE__ __hi, __errno_t *__rstatus) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou))(__nptr, __endptr, __base, __lo, __hi, __rstatus); })
#endif /* !__CRT_HAVE_strtou */
#endif /* !__strtou_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_INTTYPES_H */
