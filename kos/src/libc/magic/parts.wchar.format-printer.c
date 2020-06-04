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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[define_replacement(pwformatprinter = __pwformatprinter)]
%[define_replacement(pc16formatprinter = __pc16formatprinter)]
%[define_replacement(pc32formatprinter = __pc32formatprinter)]

%[define_wchar_replacement(pwformatprinter = pc16formatprinter, pc32formatprinter)]
%[define_wchar_replacement(__pwformatprinter = __pc16formatprinter, __pc32formatprinter)]
%[define_wchar_replacement(format_wsnprintf_data = format_c16snprintf_data, format_c32snprintf_data)]
%[define_wchar_replacement(__format_waprintf_data_defined = __format_c16aprintf_data_defined, __format_c32aprintf_data_defined)]
%[default_impl_section({.text.crt.wchar.string.format|.text.crt.dos.wchar.string.format})]


%(auto_header)#include <parts/uchar/format-printer.h>

%(auto_source){
#include <parts/uchar/format-printer.h>
#include <unicode.h>
#define libc_format_8to16     format_8to16
#define libc_format_8to32     format_8to32
#define libc_format_16to8     format_16to8
#define libc_format_16to32    format_16to32
#define libc_format_32to8     format_32to8
#define libc_format_32to16    format_32to16
#define libc_format_c16escape format_c16escape
#define libc_format_c16width  format_c16width
#define libc_format_c32escape format_c32escape
#define libc_format_c32width  format_c32width
}


%{
#include <features.h>
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/wformat-printer.h>
#include <libc/malloc.h>
#include <hybrid/__assert.h>

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
 *                  usual return value used to indicate success is 'DATALEN'. */
typedef __pwformatprinter pwformatprinter;
#endif /* !__pwformatprinter_defined */

}

[wchar] format_wrepeat:(*) %{generate(str2wcs("format_repeat"))}
[wchar] format_wescape:(*) %{generate(str2wcs("format_escape"))}
[wchar] format_whexdump:(*) %{generate(str2wcs("format_hexdump"))}

%
%
%
%

[wchar] format_vwprintf:(*) %{generate(str2wcs("format_vprintf"))}
[wchar] format_wprintf:(*) %{generate(str2wcs("format_printf"))}


%
%
%
@@Format-printer implementation for printing to a string buffer like `wsprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
[wchar]
format_wsprintf_printer:([[nonnull]] /*wchar_t ***/ void *arg,
                         [[nonnull]] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{generate(str2wcs("format_sprintf_printer"))}

%{


#ifndef __format_wsnprintf_data_defined
#define __format_wsnprintf_data_defined 1
/* Data structure for implementing waprintf() */
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
[wchar]
format_wsnprintf_printer:([[nonnull]] /*struct format_wsnprintf_data**/ void *arg,
                          [[nonnull]] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t
	%{generate(str2wcs("format_snprintf_printer"))}


[doc_alias(format_width)][ATTR_PURE]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(format_length)][wchar]
format_wwidth:(void *arg, [[nonnull]] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t {
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
	/* XXX: Not necessarily correct, as the 32-bit variant is actually ATTR_CONST.
	 *      However, magic headers don't support conditional attributes, so we can't just do
	 *      [if(__SIZEOF_WCHAR_T__ == 2), ATTR_PURE]
	 *      [if(__SIZEOF_WCHAR_T__ != 2), ATTR_CONST] */
	COMPILER_IMPURE();
	return (ssize_t)datalen;
#endif
}


[[ATTR_CONST]]
$ssize_t format_wlength(void *arg, wchar_t const *__restrict data, $size_t datalen) = format_length;



%{

#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	wchar_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */

#define FORMAT_WAPRINTF_DATA_INIT        { __NULLPTR, 0, 0 }
#define format_waprintf_data_init(self)  ((self)->ap_base = __NULLPTR, (self)->ap_avail = (self)->ap_used = 0)
#define format_waprintf_data_cinit(self)            \
	(__hybrid_assert((self)->ap_base == __NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),        \
	 __hybrid_assert((self)->ap_used == 0))
#ifdef NDEBUG
#define format_waprintf_data_fini(self)  (__libc_free((self)->ap_base))
#else /* NDEBUG */
#if __SIZEOF_POINTER__ == 4
#define format_waprintf_data_fini(self)                 \
	(__libc_free((self)->ap_base),                      \
	 (self)->ap_base  = (char *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),         \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define format_waprintf_data_fini(self)                         \
	(__libc_free((self)->ap_base),                              \
	 (self)->ap_base  = (char *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),         \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#else /* __SIZEOF_POINTER__ == ... */
#define format_waprintf_data_fini(self) (__libc_free((self)->ap_base))
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !NDEBUG */

}


%[define(DEFINE_FORMAT_WAPRINTF_DATA =
#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	wchar_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */
)]


@@Pack and finalize a given aprintf format printer
@@Together with `format_waprintf_printer()', the aprintf
@@format printer sub-system should be used as follows:
@@>> char *result; ssize_t error;
@@>> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
@@>> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
@@>> if unlikely(error < 0) {
@@>>     format_waprintf_data_fini(&p);
@@>>     return NULL;
@@>> }
@@>> result = format_waprintf_pack(&p, NULL);
@@>> return result;
@@WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
@@         but will finalize the given aprintf printer an all cases.
@@NOTE:    The caller must destroy the returned string by passing it to `free()'
@@@param: pstrlen: When non-NULL, store the length of the constructed string here
@@                 Note that this is the actual length if the constructed string,
@@                 but may differ from `wcslen(return)' when NUL characters were
@@                 printed to the waprintf-printer at one point.
@@                 (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)')
[requires_function("realloc")][userimpl]
[impl_include("<hybrid/__assert.h>")][wchar]
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC]
[dependency_prefix(DEFINE_FORMAT_WAPRINTF_DATA)]
format_waprintf_pack:([[nonnull]] struct format_waprintf_data *__restrict self,
                      [[nullable]] $size_t *pstrlen) -> wchar_t * {
	/* Free unused buffer memory. */
	wchar_t *result;
	if (self->@ap_avail@ != 0) {
		wchar_t *newbuf;
		newbuf = (wchar_t *)realloc(self->@ap_base@,
		                         (self->@ap_used@ + 1) * sizeof(wchar_t));
		if likely(newbuf)
			self->@ap_base@ = newbuf;
	} else {
		if unlikely(!self->@ap_used@) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->@ap_base@);
#ifdef __CRT_HAVE_malloc
			self->@ap_base@ = (wchar_t *)malloc(1 * sizeof(wchar_t));
#else /* __CRT_HAVE_malloc */
			self->@ap_base@ = (wchar_t *)realloc(NULL, 1 * sizeof(wchar_t));
#endif /* !__CRT_HAVE_malloc */
			if unlikely(!self->@ap_base@)
				return NULL;
		}
	}
	result = self->@ap_base@;
	__hybrid_assert(result);
	result[self->@ap_used@] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->@ap_used@;
#ifndef NDEBUG
#if __SIZEOF_POINTER__ == 4
	self->@ap_base@  = (wchar_t *)__UINT32_C(0xcccccccc);
	self->@ap_avail@ = __UINT32_C(0xcccccccc);
	self->@ap_used@  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->@ap_base@  = (wchar_t *)__UINT64_C(0xcccccccccccccccc);
	self->@ap_avail@ = __UINT64_C(0xcccccccccccccccc);
	self->@ap_used@  = __UINT64_C(0xcccccccccccccccc);
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !NDEBUG */
	return result;
}


@@Allocate a buffer of `num_wchars' wide-characters at the end of `self'
@@The returned pointer remains valid until the next time this function is called,
@@the format_aprintf buffer `self' is finalized, or some other function is used
@@to append additional data to the end of `self'
@@@return: NULL: Failed to allocate additional memory
[requires_function("realloc")][userimpl][wchar]
[impl_include("<hybrid/__assert.h>")][ATTR_WUNUSED]
[dependency_prefix(DEFINE_FORMAT_WAPRINTF_DATA)]
format_waprintf_alloc:([[nonnull]] struct format_waprintf_data *__restrict self,
                       $size_t num_wchars) -> [malloc /*(num_wchars * sizeof(wchar_t))*/] wchar_t * {
	wchar_t *result;
	if (self->@ap_avail@ < num_wchars) {
		wchar_t *newbuf;
		size_t min_alloc = self->@ap_used@ + num_wchars;
		size_t new_alloc = self->@ap_used@ + self->@ap_avail@;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (wchar_t *)realloc(self->@ap_base@, (new_alloc + 1) * sizeof(wchar_t));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (wchar_t *)realloc(self->@ap_base@, (new_alloc + 1) * sizeof(wchar_t));
			if unlikely(!newbuf)
				return NULL;
		}
		__hybrid_assert(new_alloc >= self->@ap_used@ + num_wchars);
		self->@ap_base@  = newbuf;
		self->@ap_avail@ = new_alloc - self->@ap_used@;
	}
	result = self->@ap_base@ + self->@ap_used@;
	self->@ap_avail@ -= num_wchars;
	self->@ap_used@  += num_wchars;
	return result;
}

@@Print data to a dynamically allocated heap buffer. On error, -1 is returned
[requires_function("format_waprintf_alloc")][userimpl][wchar][ATTR_WUNUSED]
format_waprintf_printer:([[nonnull]] /*struct format_waprintf_data **/ void *arg,
                         [[nonnull]] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t {
	wchar_t *buf;
	buf = format_waprintf_alloc((struct $format_waprintf_data *)arg, datalen);
	if unlikely(!buf)
		return -1;
	wmemcpy(buf, data, datalen);
	return (ssize_t)datalen;
}




%{

#endif /* __CC__ */

__SYSDECL_END

}

