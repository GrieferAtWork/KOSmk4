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
#ifndef GUARD_LIBICONV_STDICONV_H
#define GUARD_LIBICONV_STDICONV_H 1

#include "api.h"
/**/

#include <__crt.h>

#include <libiconv/iconv.h>
#include <libiconv/stdiconv.h>

#ifndef LIBCCALL
#define LIBCCALL __LIBCCALL
#endif /* !LIBCCALL */

DECL_BEGIN

/* Opaque object used by the functions below. */
struct stdiconv;

/* Create a new conversion descriptor for converting `fromcode' --> `tocode'. */
INTDEF WUNUSED struct stdiconv *
NOTHROW_NCX(LIBCCALL libiconv_stdiconv_open)(const char *tocode, const char *fromcode);

/* Close an iconv descriptor, as previously opened by `iconv_open(3)'. */
INTDEF int NOTHROW_NCX(LIBCCALL libiconv_stdiconv_close)(struct stdiconv *self);


/* Convert data from one codec into another.
 *
 * Author's  note: don't use this interface if  you're targeting KOS. Use the much
 * better pformatprinter-based interface instead! Also: technically speaking, this
 * one is also  just a wrapper  around that one.  (though one that  adds a lot  of
 * overhead for functionality you probably don't actually be need)
 *
 * @param: self:         Conversion controller. (s.a. `iconv_open(3)')
 * @param: inbuf:        [0..*inbytesleft][0..1] When NULL (or pointing to NULL),
 *                       do nothing. Otherwise, pointer to the start of data that
 *                       has yet to be converted. (updated during the call)
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
 *                                     error doesn't happen  on KOS because  incomplete
 *                                     sequences are  handled by  remembering the  part
 *                                     already encountered and  expecting a later  call
 *                                     to  provide  the missing  part. If  that doesn't
 *                                     happen,  then it's an invalid sequence (EILSEQ).
 * @return: (size_t)-1: [errno=E2BIG]  Output buffer is too small. (Arguments are left
 *                                     unchanged). */
INTDEF size_t
NOTHROW_NCX(LIBCCALL libiconv_stdiconv)(struct stdiconv *self,
                                        char **__restrict inbuf, size_t *__restrict inbytesleft,
                                        char **__restrict outbuf, size_t *__restrict outbytesleft);

DECL_END

#endif /* !GUARD_LIBICONV_STDICONV_H */