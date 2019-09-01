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

%[define_replacement(pwformatprinter = __pwformatprinter)]
%[define_replacement(pc16formatprinter = __pc16formatprinter)]
%[define_replacement(pc32formatprinter = __pc32formatprinter)]

%[define_wchar_replacement(pwformatprinter = pc16formatprinter, pc32formatprinter)]
%[define_wchar_replacement(__pwformatprinter = __pc16formatprinter, __pc32formatprinter)]
%[define_wchar_replacement(format_wsnprintf_data = format_c16snprintf_data, format_c32snprintf_data)]


%(auto_header)#include <parts/uchar/format-printer.h>

%{
#include <features.h>
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/wformat-printer.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __pwformatprinter_defined
#define __pwformatprinter_defined 1
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
 *                  usual return value used to indicate success in 'DATALEN'. */
typedef __pwformatprinter pwformatprinter;
#endif /* !__pwformatprinter_defined */

}

[attribute(*)][wchar] format_wrepeat:(*) %{copy(format_repeat, str2wcs)}
[attribute(*)][wchar] format_wescape:(*) %{copy(format_escape, str2wcs)}
[attribute(*)][wchar] format_whexdump:(*) %{copy(format_hexdump, str2wcs)}

%
%
%
%

[attribute(*)][wchar] format_vwprintf:(*) %{copy(format_vprintf, str2wcs)}
[attribute(*)][wchar] format_wprintf:(*) %{copy(format_printf, str2wcs)}


%
%
%
@@Format-printer implementation for printing to a string buffer like `wsprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
[wchar]
format_wsprintf_printer:([nonnull] /*wchar_t ***/void *arg,
                         [nonnull] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{copy(format_sprintf_printer, str2wcs)}

%{


#ifndef __format_wsnprintf_data_defined
#define __format_wsnprintf_data_defined 1
/* Data structure for implementing wsnprintf() */
struct format_wsnprintf_data {
	wchar_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_wsnprintf_data_defined */
#define FORMAT_WSNPRINTF_INIT(buf, bufsize)       { buf, bufsize }
#define format_wsnprintf_init(self, buf, bufsize) ((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))

}


@@Format-printer implementation for printing to a string buffer like `wsnprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
@@NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
@@NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()'
[wchar][dependency_include(<hybrid/typecore.h>)]
format_wsnprintf_printer:([nonnull] /*struct format_wsnprintf_data**/void *arg,
                          [nonnull] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{copy(format_snprintf_printer, str2wcs)}


[doc_alias(format_width)]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(format_length)][wchar]
format_wwidth:(void *arg, [nonnull] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t {
#if __SIZEOF_WCHAR_T__ == 2
	size_t result = 0;
	wchar_t const *iter, *end;
	(void)arg;
	end = (iter = data) + datalen;
	while (iter < end) {
		wchar_t ch;
		ch = *iter++;
		if (ch >= 0xd800 && ch <= 0xd800 && iter < end) {
			ch = *iter;
			if (ch >= 0xdc00 && ch <= 0xdfff)
				++iter;
		}
		++result;
	}
	return (ssize_t)result;
#else
	(void)arg;
	(void)data;
	return (ssize_t)datalen;
#endif
}

[noexport][nocrt][nouser]
format_wlength:(void *arg, wchar_t const *__restrict data, $size_t datalen) -> $ssize_t = format_length;



%{

#endif /* __CC__ */

__SYSDECL_END

}

