/* HASH CRC-32:0xef468a84 */
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
#ifndef GUARD_LIBC_AUTO_UCHAR_H
#define GUARD_LIBC_AUTO_UCHAR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <uchar.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mbrtoc8(3)
 * Convert a multi-byte string into utf-8
 * @param: pc8:    Output buffer for utf-8 byte (or `NULL' to discard conversion output)
 * @param: str:    Multi-byte input string (when `NULL', same as `mbrtoc8(pc8, "", 1, mbs)')
 * @param: maxlen: The max # of bytes to read starting at `str'
 * @param: mbs:    Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes consumed from `str' to fill
 *              in `*pc8' and update `mbs' (always `<= maxlen')
 * @return: 0 : The character written to `*pc8' is the NUL-character, and `*mbs' was reset
 * @return: (size_t)-3: `*pc8' was populated from `mbs', but nothing was read from `str'
 * @return: (size_t)-2: Incomplete sequence; "mbs" was updated and all "maxlen"
 *                      bytes were read, but no  full utf-8 byte was  produced.
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+str+maxlen' cannot be decoded */
INTDEF ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1) size_t NOTHROW_NCX(LIBDCALL libd_mbrtoc8)(char8_t *pc8, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mbrtoc8(3)
 * Convert a multi-byte string into utf-8
 * @param: pc8:    Output buffer for utf-8 byte (or `NULL' to discard conversion output)
 * @param: str:    Multi-byte input string (when `NULL', same as `mbrtoc8(pc8, "", 1, mbs)')
 * @param: maxlen: The max # of bytes to read starting at `str'
 * @param: mbs:    Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes consumed from `str' to fill
 *              in `*pc8' and update `mbs' (always `<= maxlen')
 * @return: 0 : The character written to `*pc8' is the NUL-character, and `*mbs' was reset
 * @return: (size_t)-3: `*pc8' was populated from `mbs', but nothing was read from `str'
 * @return: (size_t)-2: Incomplete sequence; "mbs" was updated and all "maxlen"
 *                      bytes were read, but no  full utf-8 byte was  produced.
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+str+maxlen' cannot be decoded */
INTDEF ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1) size_t NOTHROW_NCX(LIBCCALL libc_mbrtoc8)(char8_t *pc8, char const *__restrict str, size_t maxlen, mbstate_t *mbs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> c8rtomb(3)
 * Convert utf-8 into a multi-byte string
 * @param: str: Multi-byte output buffer (when `NULL', same as `char buf[MB_CUR_MAX]; c8rtomb(buf, u8'\0', mbs);')
 * @param: c8:  UTF-8 byte to convert into its multi-byte representation
 * @param: mbs: Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes written starting at `str'
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+c8' cannot be encoded as multi-byte */
INTDEF ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1) size_t NOTHROW_NCX(LIBDCALL libd_c8rtomb)(char *__restrict str, char8_t c8, mbstate_t *mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> c8rtomb(3)
 * Convert utf-8 into a multi-byte string
 * @param: str: Multi-byte output buffer (when `NULL', same as `char buf[MB_CUR_MAX]; c8rtomb(buf, u8'\0', mbs);')
 * @param: c8:  UTF-8 byte to convert into its multi-byte representation
 * @param: mbs: Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes written starting at `str'
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+c8' cannot be encoded as multi-byte */
INTDEF ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1) size_t NOTHROW_NCX(LIBCCALL libc_c8rtomb)(char *__restrict str, char8_t c8, mbstate_t *mbs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_convert_freev)(void *vector);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_convert_freev)(void *vector);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_convert_freevn)(void *vector, size_t count);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_convert_freevn)(void *vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_convert_wcstombs)(char16_t const *str);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBKCALL libc_convert_wcstombs)(char32_t const *str);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *NOTHROW_NCX(LIBDCALL libd_convert_wcstombsn)(char16_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *NOTHROW_NCX(LIBKCALL libc_convert_wcstombsn)(char32_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBDCALL libd_convert_wcstombsv)(char16_t const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBKCALL libc_convert_wcstombsv)(char32_t const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **NOTHROW_NCX(LIBDCALL libd_convert_wcstombsvn)(char16_t const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **NOTHROW_NCX(LIBKCALL libc_convert_wcstombsvn)(char32_t const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t *NOTHROW_NCX(LIBDCALL libd_convert_mbstowcs)(char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t *NOTHROW_NCX(LIBKCALL libc_convert_mbstowcs)(char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char16_t *NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsn)(char const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char32_t *NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsn)(char const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t **NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsv)(char const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t **NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsv)(char const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char16_t **NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsvn)(char const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char32_t **NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsvn)(char const *const *__restrict vector, size_t count);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UCHAR_H */
