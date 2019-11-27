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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[default_impl_section({.text.crt.wchar.string.format|.text.crt.dos.wchar.string.format})]

%{
#include <features.h>
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#include <bits/uformat-printer.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined 1
/* Callback functions prototypes provided to format functions.
 * NOTE: '__pformatprinter' usually returns the number of characters printed, but isn't required to.
 * @param: DATA:    The base address of a DATALEN bytes long character vector that should be printed.
 * @param: DATALEN: The amount of characters that should be printed, starting at `data'.
 *                  Note that this is an exact value, meaning that a NUL-character appearing
 *                  before then should not terminate printing prematurely, but be printed as well.
 * @param: CLOSURE: The user-defined closure parameter passed alongside this function pointer.
 * @return: < 0:    An error occurred and the calling function shall return with this same value.
 * @return: >= 0:   The print was successful.
 *                  Usually, the return value is added to a sum of values which is then
 *                  returned by the calling function upon success, also meaning that the
 *                  usual return value used to indicate success is 'DATALEN'. */
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */


}

[attribute(*)] format_c16repeat:(*) %{uchar(format_wrepeat)}
[attribute(*)] format_c32repeat:(*) %{uchar(format_wrepeat)}
[attribute(*)] format_c16escape:(*) %{uchar(format_wescape)}
[attribute(*)] format_c32escape:(*) %{uchar(format_wescape)}
[attribute(*)] format_c16hexdump:(*) %{uchar(format_whexdump)}
[attribute(*)] format_c32hexdump:(*) %{uchar(format_whexdump)}

%
%
%

[attribute(*)] format_vc16printf:(*) %{uchar(format_vwprintf)}
[attribute(*)] format_vc32printf:(*) %{uchar(format_vwprintf)}
[attribute(*)] format_c16printf:(*) %{uchar(format_wprintf)}
[attribute(*)] format_c32printf:(*) %{uchar(format_wprintf)}

%
%
%
[attribute(*)]
format_c16sprintf_printer:(/*char16_t ***/ void *arg, char16_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{uchar(format_wsprintf_printer)}
[attribute(*)]
format_c32sprintf_printer:(/*char32_t ***/ void *arg, char32_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{uchar(format_wsprintf_printer)}


%{


#ifndef __format_c16snprintf_data_defined
#define __format_c16snprintf_data_defined 1
/* Data structure for implementing c16snprintf() */
struct format_c16snprintf_data {
	char16_t     *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
/* Data structure for implementing c32snprintf() */
struct format_c32snprintf_data {
	char32_t     *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_c16snprintf_data_defined */

#define FORMAT_C16SNPRINTF_INIT(buf,bufsize)       { buf, bufsize }
#define FORMAT_C32SNPRINTF_INIT(buf,bufsize)       { buf, bufsize }
#define format_c16snprintf_init(self,buf,bufsize) ((self)->sd_buffer = (buf),(self)->sd_bufsiz = (bufsize))
#define format_c32snprintf_init(self,buf,bufsize) ((self)->sd_buffer = (buf),(self)->sd_bufsiz = (bufsize))

}

[attribute(*)] format_c16snprintf_printer:(*) %{uchar(format_wsnprintf_printer)}
[attribute(*)] format_c32snprintf_printer:(*) %{uchar(format_wsnprintf_printer)}

[attribute(*)] format_c16width:(*) %{uchar(format_wwidth)}
[preferred_alias(format_length)][attribute(*)] format_c32width:(*) %{uchar(format_wwidth)}

[noexport][nocrt][nouser]
format_c16length:(void *arg, char16_t const *__restrict data, $size_t datalen) -> $ssize_t = format_length;
[noexport][nocrt][nouser]
format_c32length:(void *arg, char32_t const *__restrict data, $size_t datalen) -> $ssize_t = format_length;



%[define_wchar_replacement(__format_waprintf_data_defined = __format_c16aprintf_data_defined, __format_c32aprintf_data_defined)]
%[define_wchar_replacement(format_waprintf_data = format_c16aprintf_data, format_c32aprintf_data)]
%[define_wchar_replacement(FORMAT_WAPRINTF_DATA_INIT = FORMAT_C16APRINTF_DATA_INIT, FORMAT_C32APRINTF_DATA_INIT)]
%[define_wchar_replacement(format_waprintf_data_init = format_c16aprintf_data_init, format_c32aprintf_data_init)]
%[define_wchar_replacement(format_waprintf_data_cinit = format_c16aprintf_data_cinit, format_c32aprintf_data_cinit)]
%[define_wchar_replacement(format_waprintf_data_fini = format_c16aprintf_data_fini, format_c32aprintf_data_fini)]

%{

#ifndef __format_c16aprintf_data_defined
#define __format_c16aprintf_data_defined 1
struct format_c16aprintf_data {
	char16_t     *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};

struct format_c32aprintf_data {
	char32_t     *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_c32aprintf_data_defined */

#define FORMAT_C16APRINTF_DATA_INIT        { (char16_t *)__NULLPTR, 0, 0 }
#define FORMAT_C32APRINTF_DATA_INIT        { (char32_t *)__NULLPTR, 0, 0 }
#define format_c16aprintf_data_init(self)  ((self)->ap_base = (char16_t *)__NULLPTR, (self)->ap_avail = (self)->ap_used = 0)
#define format_c32aprintf_data_init(self)  ((self)->ap_base = (char32_t *)__NULLPTR, (self)->ap_avail = (self)->ap_used = 0)
#define format_c16aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char16_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#define format_c32aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char32_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#ifdef NDEBUG
#define format_c16aprintf_data_fini(self)  (__libc_free((self)->ap_base))
#define format_c32aprintf_data_fini(self)  (__libc_free((self)->ap_base))
#else /* NDEBUG */
#if __SIZEOF_POINTER__ == 4
#define format_c16aprintf_data_fini(self)                   \
	(__libc_free((self)->ap_base),                          \
	 (self)->ap_base  = (char16_t *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),             \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#define format_c32aprintf_data_fini(self)                   \
	(__libc_free((self)->ap_base),                          \
	 (self)->ap_base  = (char32_t *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),             \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define format_c16aprintf_data_fini(self)                           \
	(__libc_free((self)->ap_base),                                  \
	 (self)->ap_base  = (char16_t *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),             \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#define format_c32aprintf_data_fini(self)                           \
	(__libc_free((self)->ap_base),                                  \
	 (self)->ap_base  = (char32_t *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),             \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#else /* __SIZEOF_POINTER__ == ... */
#define format_c16aprintf_data_fini(self) (__libc_free((self)->ap_base))
#define format_c32aprintf_data_fini(self) (__libc_free((self)->ap_base))
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !NDEBUG */

}


[alias(*)][attribute(*)] format_c16aprintf_pack:(*) %{uchar(format_waprintf_pack)}
[alias(*)][attribute(*)] format_c32aprintf_pack:(*) %{uchar(format_waprintf_pack)}
[alias(*)][attribute(*)] format_c16aprintf_alloc:(*) %{uchar(format_waprintf_alloc)}
[alias(*)][attribute(*)] format_c32aprintf_alloc:(*) %{uchar(format_waprintf_alloc)}
[alias(*)][attribute(*)] format_c16aprintf_printer:(*) %{uchar(format_waprintf_printer)}
[alias(*)][attribute(*)] format_c32aprintf_printer:(*) %{uchar(format_waprintf_printer)}



%{

#endif /* __CC__ */

__SYSDECL_END

}

