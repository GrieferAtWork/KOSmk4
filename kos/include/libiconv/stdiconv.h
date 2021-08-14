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
#ifndef _LIBICONV_STDICONV_H
#define _LIBICONV_STDICONV_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>

/* KOS's version of the <iconv.h> header!
 * NOTE: Link with `-liconv' to use this header! */

#ifdef __CC__
__DECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


/* Opaque object used by the functions below. */
typedef void *iconv_t;

/* >> iconv_open(3)
 * Create a new conversion descriptor for converting `fromcode' --> `tocode'. */
__IMPDEF __ATTR_WUNUSED iconv_t
__NOTHROW_NCX(__LIBCCALL iconv_open)(const char *__tocode, const char *__fromcode);

/* >> iconv_close(3)
 * Close an iconv descriptor, as previously opened by `iconv_open(3)'. */
__IMPDEF int
__NOTHROW_NCX(__LIBCCALL iconv_close)(iconv_t __self);


/* Convert data from one codec into another.
 *
 * Author's  note: don't use this interface if  you're targeting KOS. Use the much
 * better pformatprinter-based interface instead! Also: technically speaking, this
 * one is also  just a wrapper  around that one.  (though one that  adds a lot  of
 * overhead for functionality you probably don't actually be need)
 *
 * @param: self:         Conversion controller. (s.a. `iconv_open(3)')
 * @param: inbuf:        [0..*inbytesleft][0..1] When NULL (or pointing to NULL),
 *                       flush the encoder to  check that no multi-byte  sequence
 *                       is currently in progress, as  well as output bytes  that
 *                       might be needed to reset  the shift state; if outbuf  is
 *                       NULL  or points to NULL, then that data is silently send
 *                       into oblivion. Otherwise, pointer  to the start of  data
 *                       that has yet to be converted. (updated during the  call)
 *                       s.a. `iconv_encode_flush()'
 *                       s.a. `iconv_decode_isshiftzero()'
 * @param: inbytesleft:  [1..1][valid_if(inbuf)]
 *                       [in]  The max # of bytes to read from `*inbuf'
 *                       [out] # of bytes not taken  from `*inbuf'.
 *                             Always set to `0' on success.
 * @param: outbuf:       [1..*outbytesleft][1..1][valid_if(inbuf)]
 *                       Pointer to the start of a memory region that should be
 *                       filled with data to-be converted.
 * @param: outbytesleft: [1..1][valid_if(inbuf)] # of bytes available in `outbuf'.
 *                       Updated over the course of the call.
 * @return: * : The # of decoded+encoded unicode characters. (technically only the
 *              # of decoded characters, but that  should normally equal the #  of
 *              encoded ones, and should they not match, the specs don't say  what
 *              should be returned then, so...)
 * @return: (size_t)-1: [errno=EILSEQ] Invalid sequence  in input  (*inbuf now  points
 *                                     to the start of said sequence, but *inbytesleft
 *                                     is left unchanged)
 * @return: (size_t)-1: [errno=EINVAL] Incomplete multi-byte sequence encountered. This
 *                                     error only happens when `!inbuf || !*inbuf',  in
 *                                     which case a flush operation is performed. If it
 *                                     turns out that input data didn't properly finish
 *                                     a multi-byte sequence, then this error is set.
 * @return: (size_t)-1: [errno=E2BIG]  Output buffer is too small. (Arguments are left
 *                                     unchanged). */
__IMPDEF size_t
__NOTHROW_NCX(__LIBCCALL iconv)(iconv_t __self,
                                char **__restrict __inbuf, size_t *__restrict __inbytesleft,
                                char **__restrict __outbuf, size_t *__restrict __outbytesleft);

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBICONV_STDICONV_H */
