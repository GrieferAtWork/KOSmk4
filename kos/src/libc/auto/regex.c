/* HASH CRC-32:0xea831f30 */
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
#ifndef GUARD_LIBC_AUTO_REGEX_C
#define GUARD_LIBC_AUTO_REGEX_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/regex.h"
#include "format-printer.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/re_syntax_options.h>
/* >> re_set_syntax(3)
 * Set  the  regex  syntax used  by  `re_compile_pattern(3)', and
 * return the old default syntax (same as `re_syntax_options(3)') */
INTERN ATTR_SECTION(".text.crt.utility.regex") reg_syntax_t
NOTHROW_NCX(LIBCCALL libc_re_set_syntax)(reg_syntax_t syntax) {
	reg_syntax_t result = re_syntax_options;
	re_syntax_options   = syntax;
	return result;
}
/* >> re_compile_fastmap(3)
 * Compile the fast-map of `self'. No-op on KOS, where the fastmap is always compiled immediatly.
 * @return: 0 : Always returns `0' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_re_compile_fastmap)(regex_t *self) {
	(void)self;
	COMPILER_IMPURE();
	return 0;
}
/* >> re_set_registers(3)
 * Initializes `regs', and sets some weird internal flag in `self' (which it doesn't do on KOS) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_INOUT(1) ATTR_OUT(2) void
NOTHROW_NCX(LIBCCALL libc_re_set_registers)(regex_t *self,
                                            struct __re_registers *regs,
                                            unsigned int num_regs,
                                            regoff_t *starts,
                                            regoff_t *ends) {
	(void)self;
	regs->num_regs = num_regs;
	if (num_regs) {
		regs->start = starts;
		regs->end   = ends;
	} else {
		regs->start = NULL;
		regs->end   = NULL;
	}
}
/* >> regerror(3)
 * Produce a human-readable description for a regex error code `errcode' (s.a. `regerrordesc_np(3)')
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @param: self:    The compiled regex pattern that produced the error (unused in this impl)
 * @return: * :     The required buffer size (including a trailing '\0'-byte) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(2) ATTR_OUTS(3, 4) size_t
NOTHROW_NCX(LIBCCALL libc_regerror)(int errcode,
                                    regex_t const *__restrict self,
                                    char *__restrict errbuf,
                                    size_t errbuf_size) {
	char const *msg;
	size_t msglen;
	(void)self;
	msg = libc_regerrordesc_np(errcode);
	if unlikely(!msg)
		msg = "?";
	msglen = libc_strlen(msg);
	if (errbuf_size > (msglen + 1))
		errbuf_size = (msglen + 1);
	libc_memcpy(errbuf, msg, errbuf_size);
	return msglen;
}
/* >> regfree(3)
 * Free dynamic memory allocated during a successful call to `regcomp(3)'
 * @param: self: The compiled regex pattern to destroy */
INTERN ATTR_SECTION(".text.crt.utility.regex") void
NOTHROW_NCX(LIBCCALL libc_regfree)(regex_t *self) {
	libc_free(self->__REPB_PREFIX(buffer));
}
#include <asm/crt/regex.h>
/* >> regerrordesc_np(3)
 * Return a human-readable description for a given regex `errcode'
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @return: * :   The human-readable description for `errcode'
 * @return: NULL: No description is available for `errcode' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_regerrordesc_np)(int errcode) {
	char const *result;
	switch (errcode) {

	case __REG_ENOSYS: /*  */ result = "Unable to load regex sub-system"; break;


	case __REG_NOERROR: /* */ result = "Success"; break;


	case __REG_NOMATCH: /* */ result = "No match"; break;


	case __REG_BADPAT: /*  */ result = "Invalid regex pattern"; break;


	case __REG_ECOLLATE: /**/ result = "Invalid collation character"; break;


	case __REG_ECTYPE: /*  */ result = "Invalid character class name"; break;


	case __REG_EESCAPE: /* */ result = "Trailing backslash"; break;


	case __REG_ESUBREG: /* */ result = "Invalid back reference"; break;


	case __REG_EBRACK: /*  */ result = "Unmatched [, [^, [:, [., or [="; break;


	case __REG_EPAREN: /*  */ result = "Unmatched ("; break;


	case __REG_EBRACE: /*  */ result = "Unmatched {"; break;


	case __REG_BADBR: /*   */ result = "Invalid content of {...}"; break;


	case __REG_ERANGE: /*  */ result = "Set-range start is greater than its end"; break;


	case __REG_ESPACE: /*  */ result = "Out of memory"; break;


	case __REG_BADRPT: /*  */ result = "Nothing precedes +, *, ?, or {"; break;


	case __REG_EEND: /*    */ result = "Unexpected end of pattern"; break;


	case __REG_ESIZE: /*   */ result = "Regular expression violates a hard upper limit"; break;


	case __REG_ERPAREN: /* */ result = "Unmatched )"; break;


	case __REG_EILLSEQ: /* */ result = "Illegal unicode character"; break;


	case __REG_EILLSET: /* */ result = "Cannot combine raw bytes with unicode characters in charsets"; break;

#ifdef __REG_EMPTY
	case __REG_EMPTY: /*   */ result = "?"; break;
#endif /* __REG_EMPTY */
#ifdef __REG_ASSERT
	case __REG_ASSERT: /*  */ result = "?"; break;
#endif /* __REG_ASSERT */
#ifdef __REG_INVARG
	case __REG_INVARG: /*  */ result = "?"; break;
#endif /* __REG_INVARG */
	default: result = NULL; break;
	}
	return result;
}
#include <hybrid/typecore.h>
/* >> regsubprint(3), regsubprintv(3)
 * Perform sed-like substitution of from `sed_format' using matches previously obtained from `regexec(3)'.
 * This  function  writes  the  NUL-terminated   string  `sed_format'  to  `printer',  whilst   replacing:
 *  - '&'  with the contents of `pmatch[0]' (or an empty string when `nmatch == 0')
 *  - '\N' with the contents of `pmatch[N]' (or an empty string when `nmatch <= N'; N must be in `[0,9]')
 *  - '\&' Prints a literal '&'
 *  - '\\' Prints a literal '\'
 * NOTE: Matches that are unset (i.e. use start/end offset `-1') produce empty strings
 * @param: printer:    Output printer
 * @param: arg:        Cookie argument for `printer'
 * @param: sed_format: Sed format string
 * @param: srcbase:    IOV base (offsets from `pmatch' point into this)
 * @param: nmatch:     The # of matches defined by `pmatch'
 * @param: pmatch:     Vector of matches
 * @return: >= 0:      Sum of positive return values of `printer'
 * @return: -1:        First negative return value of `printer' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(3) ATTR_INS(6, 5) NONNULL((1, 4)) ssize_t
NOTHROW_NCX(LIBCCALL libc_regsubprintv)(__pformatprinter printer,
                                        void *arg,
                                        char const *sed_format,
                                        struct iovec const *srcbase,
                                        size_t nmatch,
                                        regmatch_t const pmatch[__restrict_arr]) {
	size_t imatch;
	ssize_t temp, result = 0;
	char ch;
	char const *flush_start;
	flush_start = sed_format;
again:
	ch = *sed_format++;
	switch (ch) {

	case '\0':
		--sed_format;
		break;

	case '&':
		imatch = 0;
insert_imatch:
		/* Flush until the start of the insert-sequence */
		--sed_format;
		if (sed_format > flush_start) {
			temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (*sed_format == '\\')
			++sed_format;
		++sed_format;
		flush_start = sed_format;

		/* Insert the `imatch'th element from `pmatch' */
		if (imatch < nmatch && (pmatch[imatch].rm_so != (regoff_t)-1 &&
		                        pmatch[imatch].rm_eo != (regoff_t)-1)) {
			size_t offset, count;
			offset = (size_t)pmatch[imatch].rm_so;
			count  = (size_t)(pmatch[imatch].rm_eo - pmatch[imatch].rm_so);
			if (count > 0) {
				/* Seek until the first source iov item. */
				struct iovec const *iov = srcbase;
				while (offset >= iov->iov_len) {
					offset -= iov->iov_len;
					++iov;
				}
				/* Print the next `count' bytes starting at `iov[+offset]' */
				for (;;) {
					size_t partlen;
					partlen = iov->iov_len - offset;
					if (partlen > count)
						partlen = count;
					temp = (*printer)(arg, (char const *)((byte_t const *)iov->iov_base + offset), partlen);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					if (partlen >= count)
						break;
					count -= partlen;
					offset = 0;
					++iov;
				}
			}
		}
		goto again;

	case '\\':
		ch = *sed_format;
		if (ch >= '0' && ch <= '9') {
			imatch = (size_t)(ch - '0');
			goto insert_imatch;
		} else if (ch == '&' || ch == '\\') {
			/* Escaped character */
			--sed_format;
			if (sed_format > flush_start) {
				temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			++sed_format;
			flush_start = sed_format; /* Flush the escaped char the next time around */
			++sed_format;
		}
		goto again;

	default:
		goto again;
	}

	/* Flush any left-over remainder. */
	if (sed_format > flush_start) {
		temp = (*printer)(arg, flush_start, (size_t)(sed_format - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}
#include <bits/os/iovec.h>
#include <hybrid/typecore.h>
/* >> regsubprint(3), regsubprintv(3)
 * Perform sed-like substitution of from `sed_format' using matches previously obtained from `regexec(3)'.
 * This  function  writes  the  NUL-terminated   string  `sed_format'  to  `printer',  whilst   replacing:
 *  - '&'  with the contents of `pmatch[0]' (or an empty string when `nmatch == 0')
 *  - '\N' with the contents of `pmatch[N]' (or an empty string when `nmatch <= N'; N must be in `[0,9]')
 *  - '\&' Prints a literal '&'
 *  - '\\' Prints a literal '\'
 * NOTE: Matches that are unset (i.e. use start/end offset `-1') produce empty strings
 * @param: printer:    Output printer
 * @param: arg:        Cookie argument for `printer'
 * @param: sed_format: Sed format string
 * @param: srcbase:    IOV base (offsets from `pmatch' point into this)
 * @param: nmatch:     The # of matches defined by `pmatch'
 * @param: pmatch:     Vector of matches
 * @return: >= 0:      Sum of positive return values of `printer'
 * @return: -1:        First negative return value of `printer' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(3) ATTR_INS(6, 5) NONNULL((1, 4)) ssize_t
NOTHROW_NCX(LIBCCALL libc_regsubprint)(__pformatprinter printer,
                                       void *arg,
                                       char const *sed_format,
                                       void const *srcbase,
                                       size_t nmatch,
                                       regmatch_t const pmatch[__restrict_arr]) {
	struct iovec iov[1];
	iov[0].iov_base = (void *)srcbase;
	iov[0].iov_len  = (size_t)-1;
	return libc_regsubprintv(printer, arg, sed_format, iov, nmatch, pmatch);
}
#include <hybrid/typecore.h>
/* >> regnsub(3)
 * Wrapper for `regsubprint(3)' that writes the produced string into `buf...+=len'
 * @param: buf:        Output buffer base pointer
 * @param: len:        Length of `buf'
 * @param: sed_format: Sed format string
 * @param: pmatch:     A 10-element-long list of matches
 * @param: srcbase:    Source base pointer
 * @return: * :        Required buffer length (excluding a trailing NUL-character).
 *                     NOTE: On NetBSD, the return value is signed, but that didn't make
 *                           sense  since there is no error-case, so I made it unsigned. */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(3) ATTR_IN(5) ATTR_OUTS(1, 2) NONNULL((4)) size_t
NOTHROW_NCX(LIBCCALL libc_regnsub)(char *buf,
                                   size_t len,
                                   char const *sed_format,
                                   regmatch_t const *pmatch,
                                   char const *srcbase) {
	size_t result;
	struct __local_format_snprintf_data {
		char  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	} pdata;
	pdata.sd_buffer = buf;
	pdata.sd_bufsiz = len;

	/* Do the substitution-print. */
	result = (size_t)libc_regsubprint(&libc_format_snprintf_printer, &pdata,
	                             sed_format, srcbase, 10, pmatch);

	/* Append trailing NUL-terminator (if there is still space for it). */
	if (pdata.sd_bufsiz)
		*pdata.sd_buffer = '\0';

	/* Return required buffer size (excluding the trailing NUL) */
	return result;
}
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
/* >> regasub(3)
 * Wrapper for `regsubprint(3)' that dynamically allocates a buffer and stores it in `*p_buf'
 * @param: p_buf:      Pointer to output buffer of sed-replaced text (terminated by '\0')
 *                     On error, `NULL' will be stored in this pointer.
 * @param: sed_format: Sed format string
 * @param: pmatch:     A 10-element-long list of matches
 * @param: srcbase:    Source base pointer
 * @return: * :        Length of the string stored in `*p_buf' (excluding the trailing '\0')
 * @return: -1:        [errno=ENOMEM] Out of memory */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(2) ATTR_IN(4) ATTR_OUT(1) NONNULL((3)) ssize_t
NOTHROW_NCX(LIBCCALL libc_regasub)(char **p_buf,
                                   char const *sed_format,
                                   regmatch_t const *pmatch,
                                   char const *srcbase) {
	struct format_aprintf_data pdata;
	ssize_t result;
	char *resstr;

	/* Setup malloc-based printer. */
	pdata.ap_base  = NULL;
	pdata.ap_avail = 0;
	pdata.ap_used  = 0;

	/* Do the substitution-print. */
	result = libc_regsubprint(&libc_format_aprintf_printer, &pdata,
	                     sed_format, srcbase, 10, pmatch);
	if unlikely(result < 0)
		goto err;

	/* package the produced string. */
	resstr = libc_format_aprintf_pack(&pdata, (size_t *)&result);
	*p_buf = resstr;
	if unlikely(!resstr)
		result = -1;
	return result;
err:

	libc_free(pdata.ap_base);

	*p_buf = NULL;
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(re_set_syntax,libc_re_set_syntax,,reg_syntax_t,NOTHROW_NCX,LIBCCALL,(reg_syntax_t syntax),(syntax));
DEFINE_PUBLIC_ALIAS_P(re_compile_fastmap,libc_re_compile_fastmap,ATTR_INOUT(1),int,NOTHROW_NCX,LIBCCALL,(regex_t *self),(self));
DEFINE_PUBLIC_ALIAS_P_VOID(re_set_registers,libc_re_set_registers,ATTR_INOUT(1) ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(regex_t *self, struct __re_registers *regs, unsigned int num_regs, regoff_t *starts, regoff_t *ends),(self,regs,num_regs,starts,ends));
DEFINE_PUBLIC_ALIAS_P(regerror,libc_regerror,ATTR_IN(2) ATTR_OUTS(3, 4),size_t,NOTHROW_NCX,LIBCCALL,(int errcode, regex_t const *__restrict self, char *__restrict errbuf, size_t errbuf_size),(errcode,self,errbuf,errbuf_size));
DEFINE_PUBLIC_ALIAS_P_VOID(regfree,libc_regfree,,NOTHROW_NCX,LIBCCALL,(regex_t *self),(self));
DEFINE_PUBLIC_ALIAS_P(regerrordesc_np,libc_regerrordesc_np,ATTR_CONST WUNUSED,char const *,NOTHROW,LIBCCALL,(int errcode),(errcode));
DEFINE_PUBLIC_ALIAS_P(regsubprintv,libc_regsubprintv,ATTR_IN(3) ATTR_INS(6, 5) NONNULL((1, 4)),ssize_t,NOTHROW_NCX,LIBCCALL,(__pformatprinter printer, void *arg, char const *sed_format, struct iovec const *srcbase, size_t nmatch, regmatch_t const pmatch[__restrict_arr]),(printer,arg,sed_format,srcbase,nmatch,pmatch));
DEFINE_PUBLIC_ALIAS_P(regsubprint,libc_regsubprint,ATTR_IN(3) ATTR_INS(6, 5) NONNULL((1, 4)),ssize_t,NOTHROW_NCX,LIBCCALL,(__pformatprinter printer, void *arg, char const *sed_format, void const *srcbase, size_t nmatch, regmatch_t const pmatch[__restrict_arr]),(printer,arg,sed_format,srcbase,nmatch,pmatch));
DEFINE_PUBLIC_ALIAS_P(regnsub,libc_regnsub,ATTR_IN(3) ATTR_IN(5) ATTR_OUTS(1, 2) NONNULL((4)),size_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t len, char const *sed_format, regmatch_t const *pmatch, char const *srcbase),(buf,len,sed_format,pmatch,srcbase));
DEFINE_PUBLIC_ALIAS_P(regasub,libc_regasub,ATTR_IN(2) ATTR_IN(4) ATTR_OUT(1) NONNULL((3)),ssize_t,NOTHROW_NCX,LIBCCALL,(char **p_buf, char const *sed_format, regmatch_t const *pmatch, char const *srcbase),(p_buf,sed_format,pmatch,srcbase));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_REGEX_C */
