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

%[define_replacement(pwformatprinter = __pwformatprinter)]
%[define_replacement(pc16formatprinter = __pc16formatprinter)]
%[define_replacement(pc32formatprinter = __pc32formatprinter)]

%[define_wchar_replacement(pwformatprinter = pc16formatprinter, pc32formatprinter)]
%[define_wchar_replacement(pwformatprinter = pc16formatprinter, pc32formatprinter)]
%[define_wchar_replacement(__pwformatprinter = __pc16formatprinter, __pc32formatprinter)]
%[define_wchar_replacement(format_wsnprintf_data = format_c16snprintf_data, format_c32snprintf_data)]
%[define_wchar_replacement(__format_waprintf_data_defined = __format_c16aprintf_data_defined, __format_c32aprintf_data_defined)]
%[define_wchar_replacement(WFORMATPRINTER_CC = C16FORMATPRINTER_CC, C32FORMATPRINTER_CC)]
%[define_wchar_replacement(__WFORMATPRINTER_CC = __C16FORMATPRINTER_CC, __C32FORMATPRINTER_CC)]

%[default:section(".text.crt{|.dos}.wchar.string.format")]

%[define_decl_include_implication("<bits/crt/wformat-printer.h>" => [
	"<hybrid/typecore.h>",
	"<bits/crt/format-printer.h>",
])]


%(auto_header){
#include <parts/uchar/format-printer.h>
#ifndef __KERNEL__
#include "format-printer.h"
INTDEF ATTR_CONST ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wwidth)(void *arg,
                                         char32_t const *__restrict data,
                                         size_t datalen)
	ASMNAME("libc_format_length");
#endif /* !__KERNEL__ */
}

%(auto_source){
#include "../libc/dl.h"      /* Use libc's relocation-optimized dl* functions. */
#include "../libc/string.h"  /* Dependency of `#include <libc/template/format-printf.h>' */
#include "../libc/unicode.h" /* Dependency of `#include <libc/template/format-scanf.h>' */
/**/
#include <hybrid/__assert.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/__alloca.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <bits/types.h>      /* Dependency of `#include <libc/template/format-printf.h>' */
#include <bits/math-constants.h>

#include <libc/template/itoa_digits.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libdisasm/disassembler.h>    /* Dependency of `#include <libc/template/format-printf.h>' */
#ifdef __KERNEL__
#include <kernel/addr2line.h>
#else /* __KERNEL__ */
#include <libdebuginfo/addr2line.h>
#endif /* !__KERNEL__ */
}



%[insert:prefix(
#include <features.h>
)]%{
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
}%[insert:prefix(
#include <hybrid/__assert.h>
)]%{

}%[insert:prefix(
#include <bits/crt/wformat-printer.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

}%[insert:prefix(
#include <libc/malloc.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

/* Calling convention used by `pwformatprinter' */
#ifndef WFORMATPRINTER_CC
#define WFORMATPRINTER_CC __WFORMATPRINTER_CC
#endif /* !WFORMATPRINTER_CC */

#ifndef __pwformatprinter_defined
#define __pwformatprinter_defined
/* Callback functions prototypes provided to format functions.
 * NOTE: 'pwformatprinter' usually returns the number of characters printed, but isn't required to.
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
typedef __pwformatprinter pwformatprinter;
#endif /* !__pwformatprinter_defined */

}

[[wchar]]
[[throws, decl_include("<bits/crt/wformat-printer.h>")]]
$ssize_t format_wrepeat([[nonnull]] pwformatprinter printer, void *arg,
                        wchar_t ch, $size_t num_repetitions)
	%{generate(str2wcs("format_repeat"))}

[[wchar]] format_wescape(*) %{generate(str2wcs("format_escape"))}
[[wchar]] format_whexdump(*) %{generate(str2wcs("format_hexdump"))}

%
%
%
%

[[throws, wchar, doc_alias("format_vprintf")]]
[[decl_include("<bits/crt/wformat-printer.h>")]]
[[impl_include("<parts/printf-config.h>", "<bits/types.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
[[impl_include("<libc/parts.uchar.string.h>")]]
[[impl_include("<libc/string.h>", "<libc/errno.h>")]]
[[impl_include("<hybrid/__assert.h>", "<hybrid/__alloca.h>")]]
[[impl_prefix(
@@pp_ifndef __NO_PRINTF_DISASM@@
@@pp_if !defined(__KERNEL__) || !defined(__KOS__)@@
@#include <dlfcn.h>@
@@pp_endif@@
@#include <libdisasm/disassembler.h>@
@@pp_endif@@
@@pp_ifndef __NO_PRINTF_VINFO@@
@@pp_if !defined(__KERNEL__) || !defined(__KOS__)@@
@#include <dlfcn.h>@
@#include <libdebuginfo/addr2line.h>@
@@pp_else@@
@#include <kernel/addr2line.h>@
@@pp_endif@@
@@pp_endif@@
)]]
$ssize_t format_vwprintf([[nonnull]] pwformatprinter printer, void *arg,
                         [[nonnull, format]] wchar_t const *__restrict format,
                         $va_list args) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#define __CHAR_TYPE                 wchar_t
#define __CHAR_SIZE                 __SIZEOF_WCHAR_T__
#define __FORMAT_STRERROR           strerror
#define __FORMAT_REPEAT             format_wrepeat
#define __FORMAT_HEXDUMP            format_whexdump
#define __FORMAT_WIDTH              format_wwidth
#define __FORMAT_ESCAPE             format_wescape
#define __FORMAT_WIDTH8             format_width
#define __FORMAT_ESCAPE8            format_escape
#define __FORMAT_UNICODE_FORMAT8    format_8tow
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
#define __FORMAT_WIDTH32            format_c32width
#define __FORMAT_ESCAPE32           format_c32escape
#define __FORMAT_UNICODE_WRITECHAR  unicode_writeutf16
#define __FORMAT_UNICODE_FORMAT32   format_32to16
@@pp_else@@
#define __FORMAT_WIDTH16            format_c16width
#define __FORMAT_ESCAPE16           format_c16escape
#define __FORMAT_UNICODE_WRITECHAR(dst, ch) ((dst)[0] = (ch), (dst) + 1)
#define __FORMAT_UNICODE_FORMAT16   format_16to32
@@pp_endif@@
@#include <libc/template/format-printf.h>@
#endif /* !__INTELLISENSE__ */
}


[[wchar, doc_alias("format_vwprintf")]]
format_wprintf(*) %{printf("format_vwprintf")}



[[throws, wchar, doc_alias("format_vscanf")]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/string.h>", "<libc/unicode.h>")]]
[[impl_include("<parts/printf-config.h>")]]
[[impl_include("<bits/math-constants.h>")]]
$ssize_t format_vwscanf([[nonnull]] pformatgetc pgetc,
                        [[nonnull]] pformatungetc pungetc, void *arg,
                        [[nonnull, format]] wchar_t const *__restrict format, $va_list args) {
#ifndef __INTELLISENSE__
#define __CHAR_TYPE      wchar_t
#define __CHAR_SIZE      __SIZEOF_WCHAR_T__
#define __FORMAT_PGETC   pgetc
#define __FORMAT_PUNGETC pungetc
#define __FORMAT_ARG     arg
#define __FORMAT_FORMAT  format
#define __FORMAT_ARGS    args
@#include <libc/template/format-scanf.h>@
#endif /* !__INTELLISENSE__ */
}

[[wchar, doc_alias("format_vwscanf")]]
format_wscanf(*) %{printf("format_vwscanf")}


%
%
%
@@Format-printer implementation for printing to a string buffer like `wsprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
[[wchar]]
[[decl_include("<bits/crt/wformat-printer.h>", "<hybrid/typecore.h>"), cc(__WFORMATPRINTER_CC)]]
$ssize_t format_wsprintf_printer([[nonnull]] /*wchar_t ***/ void *arg,
                                 [[nonnull]] wchar_t const *__restrict data,
                                 $size_t datalen)
	%{generate(str2wcs("format_sprintf_printer"))}

%{


#ifndef __format_wsnprintf_data_defined
#define __format_wsnprintf_data_defined
/* Data structure for implementing waprintf() */
struct format_wsnprintf_data {
	wchar_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_wsnprintf_data_defined */
#define FORMAT_WSNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define format_wsnprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf),                   \
	 (self)->sd_bufsiz = (bufsize))

}


@@Format-printer implementation for printing to a string buffer like `wsnprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
@@NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
@@NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
@@      alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)'
[[wchar]]
[[decl_include("<bits/crt/wformat-printer.h>", "<hybrid/typecore.h>"), cc(__WFORMATPRINTER_CC)]]
$ssize_t format_wsnprintf_printer([[nonnull]] /*struct format_wsnprintf_data**/ void *arg,
                                  [[nonnull]] wchar_t const *__restrict data,
                                  $size_t datalen)
	%{generate(str2wcs("format_snprintf_printer"))}

[[wchar, pure, doc_alias("format_width")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), preferred_alias("format_length")]]
/* Don't export in KOS-mode (in that mode, we're an alias for `libc_format_length') */
[[crt_kos_impl_if(0), crt_dos_impl_if(!defined(__KERNEL__))]]
[[decl_include("<bits/crt/wformat-printer.h>", "<hybrid/typecore.h>"), cc(__WFORMATPRINTER_CC)]]
$ssize_t format_wwidth(void *arg, [[nonnull]] wchar_t const *__restrict data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
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
@@pp_else@@
	(void)arg;
	(void)data;
	/* XXX: Not necessarily correct, as the 32-bit variant is actually ATTR_CONST.
	 *
	 * However,  magic headers don't  support conditional attributes, so  we can't just do
	 * [if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), pure]
	 * [if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ != 2), const] */
	COMPILER_IMPURE();
	return (ssize_t)datalen;
@@pp_endif@@
}


[[const, cc(__WFORMATPRINTER_CC), decl_include("<bits/crt/wformat-printer.h>")]]
$ssize_t format_wlength(void *arg, wchar_t const *__restrict data,
                        $size_t datalen) = format_length;



%{

#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined
struct format_waprintf_data {
	wchar_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */

#define FORMAT_WAPRINTF_DATA_INIT \
	{ __NULLPTR, 0, 0 }
#define format_waprintf_data_init(self) \
	((self)->ap_base  = __NULLPTR,      \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_waprintf_data_cinit(self)            \
	(__hybrid_assert((self)->ap_base == __NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),        \
	 __hybrid_assert((self)->ap_used == 0))
#if defined(NDEBUG) || defined(NDEBUG_FINI)
#define format_waprintf_data_fini(self) __libc_free((self)->ap_base)
#elif __SIZEOF_POINTER__ == 4
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
#else /* ... */
#define format_waprintf_data_fini(self) __libc_free((self)->ap_base)
#endif /* !... */

}


%[define(DEFINE_FORMAT_WAPRINTF_DATA =
#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined
struct format_waprintf_data {
	wchar_t      *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */
)]


@@Pack  and  finalize  a  given  aprintf  format printer
@@Together with `format_waprintf_printer()', the aprintf
@@format  printer sub-system should  be used as follows:
@@>> char *result;
@@>> ssize_t error;
@@>> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
@@>> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
@@>> if unlikely(error < 0) {
@@>>     format_waprintf_data_fini(&p);
@@>>     return NULL;
@@>> }
@@>> result = format_waprintf_pack(&p, NULL);
@@>> return result;
@@WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
@@         but  will  finalize  the  given   aprintf  printer  an  all   cases.
@@NOTE:    The caller must destroy the returned string by passing it to `free()'
@@@param: pstrlen: When non-NULL, store the length of the constructed string here
@@                 Note that this is the actual length if the constructed string,
@@                 but may differ from `wcslen(return)' when NUL characters  were
@@                 printed to the waprintf-printer at one point.
@@                 (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)')
[[wchar, impl_include("<hybrid/__assert.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[decl_include("<hybrid/typecore.h>")]]
[[decl_prefix(DEFINE_FORMAT_WAPRINTF_DATA)]]
[[requires_function(realloc)]]
wchar_t *format_waprintf_pack([[nonnull]] struct format_waprintf_data *__restrict self,
                              [[nullable]] $size_t *pstrlen) {
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
@@pp_if $has_function(malloc)@@
			self->@ap_base@ = (wchar_t *)malloc(1 * sizeof(wchar_t));
@@pp_else@@
			self->@ap_base@ = (wchar_t *)realloc(NULL, 1 * sizeof(wchar_t));
@@pp_endif@@
			if unlikely(!self->@ap_base@)
				return NULL;
		}
	}
	result = self->@ap_base@;
	__hybrid_assert(result);
	result[self->@ap_used@] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->@ap_used@;
@@pp_if !defined(NDEBUG) && !defined(NDEBUG_FINI)@@
@@pp_if __SIZEOF_POINTER__ == 4@@
	self->@ap_base@  = (wchar_t *)__UINT32_C(0xcccccccc);
	self->@ap_avail@ = __UINT32_C(0xcccccccc);
	self->@ap_used@  = __UINT32_C(0xcccccccc);
@@pp_elif __SIZEOF_POINTER__ == 8@@
	self->@ap_base@  = (wchar_t *)__UINT64_C(0xcccccccccccccccc);
	self->@ap_avail@ = __UINT64_C(0xcccccccccccccccc);
	self->@ap_used@  = __UINT64_C(0xcccccccccccccccc);
@@pp_endif@@
@@pp_endif@@
	return result;
}


@@>> format_waprintf_alloc(3)
@@Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
@@The returned pointer remains valid until the next time this function is called,
@@the format_aprintf buffer `self' is finalized,  or some other function is  used
@@to append additional data to the end of `self'
@@@return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM')
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, impl_include("<hybrid/__assert.h>")]]
[[decl_prefix(DEFINE_FORMAT_WAPRINTF_DATA), requires_function(realloc)]]
format_waprintf_alloc:([[nonnull]] struct format_waprintf_data *__restrict self,
                       $size_t num_wchars) -> [[malloc /*(num_wchars * sizeof(wchar_t))*/]] wchar_t * {
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
				goto err;
		}
		__hybrid_assert(new_alloc >= self->@ap_used@ + num_wchars);
		self->@ap_base@  = newbuf;
		self->@ap_avail@ = new_alloc - self->@ap_used@;
	}
	result = self->@ap_base@ + self->@ap_used@;
	self->@ap_avail@ -= num_wchars;
	self->@ap_used@  += num_wchars;
	return result;
err:
	return NULL;
}

@@>> format_waprintf_printer(3)
@@Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
@@This function is intended to be used as a pwformatprinter-compatible printer sink
@@@return: datalen: Success.
@@@return: -1: [errno=ENOMEM] Insufficient memory.
[[wchar, wunused, requires_function(format_waprintf_alloc), cc(__WFORMATPRINTER_CC)]]
[[decl_include("<bits/crt/wformat-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_waprintf_printer([[nonnull]] /*struct format_waprintf_data **/ void *arg,
                                 [[nonnull]] wchar_t const *__restrict data, $size_t datalen) {
	wchar_t *buf;
	buf = format_waprintf_alloc((struct $format_waprintf_data *)arg, datalen);
	if unlikely(!buf)
		goto err;
	wmemcpy(buf, data, datalen);
	return (ssize_t)datalen;
err:
	return -1;
}




%{

__SYSDECL_END
#endif /* __CC__ */

}
