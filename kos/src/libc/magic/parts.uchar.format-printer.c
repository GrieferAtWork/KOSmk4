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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[default:section(".text.crt{|.dos}.wchar.string.format")]

%[define_decl_include_implication("<bits/crt/uformat-printer.h>" => [
	"<hybrid/typecore.h>",
	"<bits/crt/format-printer.h>",
	"<bits/crt/wformat-printer.h>",
])]


%[insert:prefix(
#include <features.h>
)]%{
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

}%[insert:prefix(
#include <bits/crt/uformat-printer.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

}%[insert:prefix(
#include <libc/malloc.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

/* Calling convention used by `pc16formatprinter' */
#ifndef C16FORMATPRINTER_CC
#define C16FORMATPRINTER_CC __C16FORMATPRINTER_CC
#endif /* !C16FORMATPRINTER_CC */

/* Calling convention used by `pc32formatprinter' */
#ifndef C32FORMATPRINTER_CC
#define C32FORMATPRINTER_CC __C32FORMATPRINTER_CC
#endif /* !C32FORMATPRINTER_CC */

#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined
/* Callback functions prototypes provided to format functions.
 * NOTE: 'pc(16|32)formatprinter' usually returns the number of characters printed, but isn't required to.
 * @param: arg:     The user-defined closure parameter passed alongside this function pointer.
 * @param: data:    The base address of a `datalen' bytes long character vector that should be printed.
 * @param: datalen: The  amount  of  characters  that  should  be  printed,  starting  at  `data'.
 *                  Note  that  this is  an exact  value, meaning  that a  NUL-character appearing
 *                  before then should not terminate printing prematurely, but be printed as well.
 * @return: < 0:    An error occurred and the calling function shall return with this same value.
 * @return: >= 0:   The print was successful.
 *                  Usually,  the return value is added to a sum of values which is then
 *                  returned by the calling function upon success, also meaning that the
 *                  usual return value used to indicate success is `datalen'. */
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */


}

format_c16repeat(*) %{uchar16("format_wrepeat")}
format_c32repeat(*) %{uchar32("format_wrepeat")}
format_c16escape(*) %{uchar16("format_wescape")}
format_c32escape(*) %{uchar32("format_wescape")}
format_c16hexdump(*) %{uchar16("format_whexdump")}
format_c32hexdump(*) %{uchar32("format_whexdump")}

%
%
%

format_vc16printf(*) %{uchar16("format_vwprintf")}
format_vc32printf(*) %{uchar32("format_vwprintf")}
format_c16printf(*) %{uchar16("format_wprintf")}
format_c32printf(*) %{uchar32("format_wprintf")}

format_vc16scanf(*) %{uchar16("format_vwscanf")}
format_vc32scanf(*) %{uchar32("format_vwscanf")}
format_c16scanf(*) %{uchar16("format_wscanf")}
format_c32scanf(*) %{uchar32("format_wscanf")}

%
%
%
format_c16sprintf_printer(*) %{uchar16("format_wsprintf_printer")}
format_c32sprintf_printer(*) %{uchar32("format_wsprintf_printer")}

//$ssize_t format_c16sprintf_printer(/*char16_t ***/ void *arg, char16_t const *__restrict data, $size_t datalen)
//	%{uchar16("format_wsprintf_printer")}
//$ssize_t format_c32sprintf_printer(/*char32_t ***/ void *arg, char32_t const *__restrict data, $size_t datalen)
//	%{uchar32("format_wsprintf_printer")}


%{


#ifndef __format_c16snprintf_data_defined
#define __format_c16snprintf_data_defined
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

#define FORMAT_C16SNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define FORMAT_C32SNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define format_c16snprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))
#define format_c32snprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))

}

format_c16snprintf_printer(*) %{uchar16("format_wsnprintf_printer")}
format_c32snprintf_printer(*) %{uchar32("format_wsnprintf_printer")}

format_c16width(*) %{uchar16("format_wwidth")}
format_c32width(*) %{uchar32("format_wwidth")}

[[const, cc(__C16FORMATPRINTER_CC), decl_include("<bits/crt/uformat-printer.h>")]]
$ssize_t format_c16length(void *arg, [[in(datalen)]] char16_t const *__restrict data, $size_t datalen) = format_length;

[[const, cc(__C32FORMATPRINTER_CC), decl_include("<bits/crt/uformat-printer.h>")]]
$ssize_t format_c32length(void *arg, [[in(datalen)]] char32_t const *__restrict data, $size_t datalen) = format_length;


%[define_wchar_replacement(__format_waprintf_data_defined = __format_c16aprintf_data_defined, __format_c32aprintf_data_defined)]
%[define_wchar_replacement(format_waprintf_data = format_c16aprintf_data, format_c32aprintf_data)]
%[define_wchar_replacement(FORMAT_WAPRINTF_DATA_INIT = FORMAT_C16APRINTF_DATA_INIT, FORMAT_C32APRINTF_DATA_INIT)]
%[define_wchar_replacement(format_waprintf_data_init = format_c16aprintf_data_init, format_c32aprintf_data_init)]
%[define_wchar_replacement(format_waprintf_data_cinit = format_c16aprintf_data_cinit, format_c32aprintf_data_cinit)]
%[define_wchar_replacement(format_waprintf_data_fini = format_c16aprintf_data_fini, format_c32aprintf_data_fini)]
%[define_wchar_replacement(DEFINE_FORMAT_WAPRINTF_DATA = DEFINE_FORMAT_C16APRINTF_DATA, DEFINE_FORMAT_C32APRINTF_DATA)]

%[define(DEFINE_FORMAT_C16APRINTF_DATA =
@@pp_ifndef __format_c16aprintf_data_defined@@
#define __format_c16aprintf_data_defined
struct format_c16aprintf_data {
	char16_t     *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
@@pp_endif@@
)]

%[define(DEFINE_FORMAT_C32APRINTF_DATA =
@@pp_ifndef __format_c32aprintf_data_defined@@
#define __format_c32aprintf_data_defined
struct format_c32aprintf_data {
	char32_t     *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
@@pp_endif@@
)]

%
%[insert:prefix(DEFINE_FORMAT_C16APRINTF_DATA)]
%[insert:prefix(DEFINE_FORMAT_C32APRINTF_DATA)]
%{
#define FORMAT_C16APRINTF_DATA_INIT \
	{ (char16_t *)__NULLPTR, 0, 0 }
#define FORMAT_C32APRINTF_DATA_INIT \
	{ (char32_t *)__NULLPTR, 0, 0 }
#define format_c16aprintf_data_init(self)      \
	((self)->ap_base  = (char16_t *)__NULLPTR, \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_c32aprintf_data_init(self)      \
	((self)->ap_base  = (char32_t *)__NULLPTR, \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_c16aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char16_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#define format_c32aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char32_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#if defined(NDEBUG) || defined(NDEBUG_FINI)
#define format_c16aprintf_data_fini(self) __libc_free((self)->ap_base)
#define format_c32aprintf_data_fini(self) __libc_free((self)->ap_base)
#elif __SIZEOF_POINTER__ == 4
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
#else /* ... */
#define format_c16aprintf_data_fini(self) __libc_free((self)->ap_base)
#define format_c32aprintf_data_fini(self) __libc_free((self)->ap_base)
#endif /* !... */

}


format_c16aprintf_pack(*) %{uchar16("format_waprintf_pack")}
format_c32aprintf_pack(*) %{uchar32("format_waprintf_pack")}
format_c16aprintf_alloc(*) %{uchar16("format_waprintf_alloc")}
format_c32aprintf_alloc(*) %{uchar32("format_waprintf_alloc")}
format_c16aprintf_printer(*) %{uchar16("format_waprintf_printer")}
format_c32aprintf_printer(*) %{uchar32("format_waprintf_printer")}



%{

__SYSDECL_END
#endif /* __CC__ */

}
