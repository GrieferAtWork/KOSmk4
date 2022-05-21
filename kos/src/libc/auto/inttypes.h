/* HASH CRC-32:0x37d51ff */
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
#ifndef GUARD_LIBC_AUTO_INTTYPES_H
#define GUARD_LIBC_AUTO_INTTYPES_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <inttypes.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST intmax_t NOTHROW(LIBDCALL libd_imaxabs)(intmax_t x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST intmax_t NOTHROW(LIBCCALL libc_imaxabs)(intmax_t x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST imaxdiv_t NOTHROW(LIBDCALL libd_imaxdiv)(intmax_t numer, intmax_t denom);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST imaxdiv_t NOTHROW(LIBCCALL libc_imaxdiv)(intmax_t numer, intmax_t denom);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBDCALL libd_strtoimax)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoimax)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBDCALL libd_strtoumax)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtoumax)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBDCALL libd_wcstoimax)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBKCALL libc_wcstoimax)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBDCALL libd_wcstoumax)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBKCALL libc_wcstoumax)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBDCALL libd_strtoimax_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoimax_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBDCALL libd_strtoumax_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtoumax_l)(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBDCALL libd_wcstoimax_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) intmax_t NOTHROW_NCX(LIBKCALL libc_wcstoimax_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBDCALL libd_wcstoumax_l)(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) uintmax_t NOTHROW_NCX(LIBKCALL libc_wcstoumax_l)(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) intmax_t NOTHROW_NCX(LIBDCALL libd_strtoi)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, intmax_t lo, intmax_t hi, errno_t *rstatus);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoi)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, intmax_t lo, intmax_t hi, errno_t *rstatus);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) uintmax_t NOTHROW_NCX(LIBDCALL libd_strtou)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, uintmax_t lo, uintmax_t hi, errno_t *rstatus);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtou)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, uintmax_t lo, uintmax_t hi, errno_t *rstatus);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) intmax_t NOTHROW_NCX(LIBDCALL libd_strtoi_l)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, intmax_t lo, intmax_t hi, errno_t *rstatus, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoi_l)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, intmax_t lo, intmax_t hi, errno_t *rstatus, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) uintmax_t NOTHROW_NCX(LIBDCALL libd_strtou_l)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, uintmax_t lo, uintmax_t hi, errno_t *rstatus, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_LEAF ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) ATTR_ACCESS_WR_OPT(6) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtou_l)(char const *__restrict nptr, char **__restrict endptr, __STDC_INT_AS_UINT_T base, uintmax_t lo, uintmax_t hi, errno_t *rstatus, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_INTTYPES_H */
