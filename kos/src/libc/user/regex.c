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
#ifndef GUARD_LIBC_USER_REGEX_C
#define GUARD_LIBC_USER_REGEX_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <bits/os/iovec.h>
#include <kos/exec/idata.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <libregex/regcomp.h>
#include <libregex/regexec.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "regex.h"

DECL_BEGIN

#define REGEX_DATA   ATTR_SECTION(".data.crt.utility.regex")
#define REGEX_RODATA ATTR_SECTION(".rodata.crt.utility.regex")
#define REGEX_BSS    ATTR_SECTION(".bss.crt.utility.regex")

/* Define dynamic, lazy imports from `libregex.so' */
#define DEFINE_REGEX_BINDING(T, name)                     \
	PRIVATE REGEX_BSS T pdyn_##name               = NULL; \
	PRIVATE REGEX_RODATA char const name_##name[] = #name
PRIVATE REGEX_BSS void *libregex = NULL;
DEFINE_REGEX_BINDING(PRE_COMPILER_COMPILE, re_compiler_compile);
DEFINE_REGEX_BINDING(PRE_EXEC_MATCH, re_exec_match);
DEFINE_REGEX_BINDING(PRE_EXEC_SEARCH, re_exec_search);
DEFINE_REGEX_BINDING(PRE_EXEC_RSEARCH, re_exec_rsearch);
#undef DEFINE_REGEX_BINDING

#define re_compiler_compile (*pdyn_re_compiler_compile)
#define re_exec_match       (*pdyn_re_exec_match)
#define re_exec_search      (*pdyn_re_exec_search)
#define re_exec_rsearch     (*pdyn_re_exec_rsearch)

#define libregex_load() (likely(pdyn_re_exec_rsearch) || _libregex_load())
PRIVATE WUNUSED bool LIBCCALL _libregex_load(void) {
	void *lib;
again_read_libregex:
	lib = ATOMIC_READ(libregex);
	if unlikely(lib == (void *)-1)
		return false;
	if (lib == NULL) {
		lib = dlopen(LIBREGEX_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!lib)
			lib = (void *)-1;
		if unlikely(!ATOMIC_CMPXCH(libregex, NULL, lib)) {
			if (lib != (void *)-1)
				dlclose(lib);
			goto again_read_libregex;
		}
	}
#define BIND(pdyn_FUNC, name_FUNC)                    \
	do {                                              \
		*(void **)&pdyn_FUNC = dlsym(lib, name_FUNC); \
		if unlikely(!pdyn_FUNC)                       \
			goto err;                                 \
	}	__WHILE0
	BIND(pdyn_re_compiler_compile, name_re_compiler_compile);
	BIND(pdyn_re_exec_match, name_re_exec_match);
	BIND(pdyn_re_exec_search, name_re_exec_search);
	/* Make sure that `pdyn_re_exec_rsearch' is loaded last (since it's
	 * the one we check above  for our fast-pass already-loaded  check) */
	COMPILER_WRITE_BARRIER();
	BIND(pdyn_re_exec_rsearch, name_re_exec_rsearch);
	COMPILER_WRITE_BARRIER();
#undef BIND
	return true;
err:
	if (ATOMIC_CMPXCH(libregex, lib, (void *)-1))
		dlclose(lib);
	return false;
}


/************************************************************************/
/* Assert that constants from `<regex.h>' are compatible with `libregex.so' */
/************************************************************************/

/* Execution flags... */
static_assert(REG_NOTBOL == RE_EXEC_NOTBOL);
static_assert(REG_NOTEOL == RE_EXEC_NOTEOL);

/* Error codes... */
static_assert(REG_NOERROR == RE_NOERROR);
static_assert(REG_NOMATCH == RE_NOMATCH);
static_assert(REG_BADPAT == RE_BADPAT);
static_assert(REG_ECOLLATE == RE_ECOLLATE);
static_assert(REG_ECTYPE == RE_ECTYPE);
static_assert(REG_EESCAPE == RE_EESCAPE);
static_assert(REG_ESUBREG == RE_ESUBREG);
static_assert(REG_EBRACK == RE_EBRACK);
static_assert(REG_EPAREN == RE_EPAREN);
static_assert(REG_EBRACE == RE_EBRACE);
static_assert(REG_BADBR == RE_BADBR);
static_assert(REG_ERANGE == RE_ERANGE);
static_assert(REG_ESPACE == RE_ESPACE);
static_assert(REG_BADRPT == RE_BADRPT);
static_assert(REG_EEND == RE_EEND);
static_assert(REG_ESIZE == RE_ESIZE);
static_assert(REG_ERPAREN == RE_ERPAREN);
static_assert(REG_EILLSET == RE_EILLSET);

/* Syntax flags... */
static_assert(RE_BACKSLASH_ESCAPE_IN_LISTS == RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS);
static_assert(RE_BK_PLUS_QM == RE_SYNTAX_BK_PLUS_QM);
static_assert(RE_CHAR_CLASSES == RE_SYNTAX_CHAR_CLASSES);
static_assert(RE_CONTEXT_INDEP_ANCHORS == RE_SYNTAX_CONTEXT_INDEP_ANCHORS);
static_assert(RE_CONTEXT_INDEP_OPS == RE_SYNTAX_CONTEXT_INDEP_OPS);
static_assert(RE_CONTEXT_INVALID_OPS == RE_SYNTAX_CONTEXT_INVALID_OPS);
static_assert(RE_DOT_NEWLINE == RE_SYNTAX_DOT_NEWLINE);
static_assert(RE_DOT_NOT_NULL == RE_SYNTAX_DOT_NOT_NULL);
static_assert(RE_HAT_LISTS_NOT_NEWLINE == RE_SYNTAX_HAT_LISTS_NOT_NEWLINE);
static_assert(RE_INTERVALS == RE_SYNTAX_INTERVALS);
static_assert(RE_LIMITED_OPS == RE_SYNTAX_LIMITED_OPS);
static_assert(RE_NEWLINE_ALT == RE_SYNTAX_NEWLINE_ALT);
static_assert(RE_NO_BK_BRACES == RE_SYNTAX_NO_BK_BRACES);
static_assert(RE_NO_BK_PARENS == RE_SYNTAX_NO_BK_PARENS);
static_assert(RE_NO_BK_REFS == RE_SYNTAX_NO_BK_REFS);
static_assert(RE_NO_BK_VBAR == RE_SYNTAX_NO_BK_VBAR);
static_assert(RE_NO_EMPTY_RANGES == RE_SYNTAX_NO_EMPTY_RANGES);
static_assert(RE_UNMATCHED_RIGHT_PAREN_ORD == RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD);
static_assert(RE_NO_POSIX_BACKTRACKING == RE_SYNTAX_NO_POSIX_BACKTRACKING);
static_assert(RE_NO_GNU_OPS == RE_SYNTAX_NO_GNU_OPS);
static_assert(RE_DEBUG == RE_SYNTAX_DEBUG);
static_assert(RE_INVALID_INTERVAL_ORD == RE_SYNTAX_INVALID_INTERVAL_ORD);
static_assert(RE_ICASE == RE_SYNTAX_ICASE);
static_assert(RE_CARET_ANCHORS_HERE == RE_SYNTAX_CARET_ANCHORS_HERE);
static_assert(RE_CONTEXT_INVALID_DUP == RE_SYNTAX_CONTEXT_INVALID_DUP);
static_assert(RE_NO_SUB == RE_SYNTAX_NO_SUB);
static_assert(RE_ANCHORS_IGNORE_EFLAGS == RE_SYNTAX_ANCHORS_IGNORE_EFLAGS);
static_assert(RE_NO_UTF8 == RE_SYNTAX_NO_UTF8);
static_assert(RE_NO_KOS_OPS == RE_SYNTAX_NO_KOS_OPS);

/* Ensure that libregex's `re_regmatch_t' is binary-compatible with the `regmatch_t' exposed in `<regex.h>' */
#define sizeof_field(s, m) sizeof(((s *)0)->m)
static_assert(sizeof(re_regmatch_t) == sizeof(regmatch_t));
static_assert(alignof(re_regmatch_t) == alignof(regmatch_t));
static_assert(offsetof(re_regmatch_t, rm_so) == offsetof(regmatch_t, rm_so));
static_assert(offsetof(re_regmatch_t, rm_eo) == offsetof(regmatch_t, rm_eo));
static_assert(sizeof_field(re_regmatch_t, rm_so) == sizeof_field(regmatch_t, rm_so));
static_assert(sizeof_field(re_regmatch_t, rm_eo) == sizeof_field(regmatch_t, rm_eo));
#undef sizeof_field


/************************************************************************/
/* GLOBAL DATA SYMBOLS FOR `<regexp.h>'                                 */
/************************************************************************/
#undef loc1
#undef loc2
#undef locs
PUBLIC ATTR_SECTION(".bss.crt.compat.glibc.regex") char *loc1 = NULL;
PUBLIC ATTR_SECTION(".bss.crt.compat.glibc.regex") char *loc2 = NULL;
PUBLIC ATTR_SECTION(".bss.crt.compat.glibc.regex") char *locs = NULL; /* NOTE: Never used internally! */


/************************************************************************/
/* Symbols for compatibility with libc4/5                                */
/************************************************************************/
INTERN ATTR_SECTION(".bss.crt.compat.glibc.regex")
char const *libc_re_error_msg[__REG_ECOUNT] = {}; /* "libc-5.4.7/libc/regex/rx.c:3922" */
DEFINE_PUBLIC_IDATA(re_error_msg, libc_resolve_re_error_msg, __REG_ECOUNT * __SIZEOF_POINTER__);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux") char const **
NOTHROW_NCX(LIBCCALL libc_resolve_re_error_msg)(void) {
	if (!libc_re_error_msg[lengthof(libc_re_error_msg) - 1]) {
		size_t i;
		for (i = 0; i < lengthof(libc_re_error_msg); ++i) {
			COMPILER_WRITE_BARRIER();
			libc_re_error_msg[i] = regerrordesc_np(i);
			COMPILER_WRITE_BARRIER();
		}
	}
	return libc_re_error_msg;
}





/************************************************************************/
/* DEFAULT REGEX SYNTAX FOR `re_compile_pattern(3)'                     */
/************************************************************************/
#undef re_syntax_options
PUBLIC ATTR_WEAK ATTR_SECTION(".bss.crt.utility.regex") /* Weak so programs can override */
reg_syntax_t re_syntax_options = RE_SYNTAX_EMACS;       /* Must be `RE_SYNTAX_EMACS' for Glibc compat */
#define re_syntax_options GET_NOREL_GLOBAL(re_syntax_options)


/* For Glibc-compat, define a public symbol:
 *    >> extern unsigned int re_max_failures;
 *
 * This symbol is used by `libregex.so' to limit  the
 * max size of the regex interpreter's on-fail stack. */
PUBLIC ATTR_SECTION(".data.crt.utility.regex")
unsigned int re_max_failures = 2000;


/* Convert posix standard regex matches into Glibc's weird, proprietary format. */
PRIVATE ATTR_SECTION(".text.crt.utility.regex") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL regmatch2glibc)(regmatch_t const *__restrict matches,
                                     struct re_registers *__restrict regs) {
	size_t i;
	for (i = 0; i < regs->num_regs; ++i) {
		regs->start[i] = matches[i].rm_so;
		regs->end[i]   = matches[i].rm_eo;
	}
}

/*[[[head:libc_re_compile_pattern,hash:CRC-32=0xc2053a8c]]]*/
/* >> re_compile_pattern(3)
 * Compile a regular expression pattern (s.a. re_compiler_compile(3R)')
 * @param: pattern: Regex pattern string
 * @param: length:  Length of regex pattern string (in bytes)
 * @param: self:    The `regex_t' object to initialize.
 * @return: NULL:   Success
 * @return: * :     An error message, as would be produced by `regerror(3)' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_INS(1, 2) ATTR_OUT(3) char const *
NOTHROW_NCX(LIBCCALL libc_re_compile_pattern)(char const *pattern,
                                              size_t length,
                                              regex_t *self)
/*[[[body:libc_re_compile_pattern]]]*/
{
	re_errno_t error;
	struct re_compiler comp;
	struct re_code *code;
	char *used_pattern;
	if unlikely(!libregex_load())
		return regerrordesc_np(REG_ENOSYS);

	/* Initialize the regex compiler */
	{
		char const *pattern_end;
		size_t pagesize = getpagesize();
		size_t pagemask = pagesize - 1;
		used_pattern    = (char *)pattern;
		pattern_end     = pattern + length;
		/* Check if the `pattern + length - 1' and `pattern + length' are located within the
		 * same page. If so,  the we can (sneakily)  check if `pattern + length' might  just
		 * happen to be a NUL-character.
		 *
		 * If  it is, then we can just pass  the caller-given pattern to the regex compiler
		 * as-is. But if it isn't, then we have to allocate a temporary copy of the pattern
		 * that features an additional NUL-character at its end. */
		if ((((uintptr_t)(pattern_end - 0) & pagemask) !=
		     ((uintptr_t)(pattern_end - 1) & pagemask)) ||
		    (*pattern_end != '\0')) {
			/* Need to use a temp copy of `pattern' that actually has a NUL-byte where we need it. */
			used_pattern = (char *)malloc(length + 1, sizeof(char));
			if unlikely(!used_pattern) {
				error = REG_ESPACE;
				goto return_error;
			}
			*(char *)mempcpy(used_pattern, pattern, length, sizeof(char)) = '\0';
		}
	}
	re_compiler_init(&comp,
	                 used_pattern,
	                 used_pattern + length,
	                 re_syntax_options);

	/* Compile the pattern. */
	error = re_compiler_compile(&comp);

	/* If we had to use a custom pattern buffer, free that buffer now. */
	if (used_pattern != (char *)pattern)
		free(used_pattern);

	/* Check for errors */
	if unlikely(error != RE_NOERROR) {
		re_compiler_fini(&comp);
		goto return_error;
	}
	code = re_compiler_pack(&comp);

	/* Compilation was successful -> fill in `self' */
	self->buffer           = (typeof(self->buffer))code;
	self->syntax           = comp.rec_parser.rep_syntax;
	self->re_nsub          = code->rc_ngrps;
	self->can_be_null      = code->rc_minmatch == 0 ? 1 : 0;
	self->fastmap_accurate = 1;
	self->no_sub           = (comp.rec_parser.rep_syntax & RE_SYNTAX_NO_SUB) ? 1 : 0;
	self->newline_anchor   = (comp.rec_parser.rep_syntax & RE_SYNTAX_ANCHORS_IGNORE_EFLAGS) ? 1 : 0;
	return NULL;
return_error:
	return regerrordesc_np(error);
}
/*[[[end:libc_re_compile_pattern]]]*/

/*[[[head:libc_re_search,hash:CRC-32=0x979c31a9]]]*/
/* >> re_search(3)
 * Perform a regex search for the first matching byte-offset in `[start,start+range)'.
 * The  accessed area of  the input buffer  is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: range:  The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  Was able to discover a match at this offset. (always `< range')
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(1) ATTR_INS(2, 3) ATTR_OUT_OPT(6) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_re_search)(regex_t __KOS_FIXED_CONST *self,
                                     char const *string,
                                     __STDC_INT_AS_SIZE_T length,
                                     __STDC_INT_AS_SIZE_T start,
                                     __STDC_INT_AS_SIZE_T range,
                                     struct __re_registers *regs)
/*[[[body:libc_re_search]]]*/
{
	struct re_exec exec;
	struct iovec iov[1];
	ssize_t status;
	if unlikely(!libregex_load())
		return -2;

	/* Set-up in regex execution controller. */
	iov[0].iov_base  = (void *)string;
	iov[0].iov_len   = (size_t)length;
	exec.rx_code     = regex_getcode(self);
	exec.rx_iov      = iov;
	exec.rx_startoff = (size_t)start;
	exec.rx_endoff   = (size_t)start + (size_t)length;
	exec.rx_extra    = 0;
	exec.rx_eflags   = 0;
	if (self->not_bol)
		exec.rx_eflags |= RE_EXEC_NOTBOL;
	if (self->not_eol)
		exec.rx_eflags |= RE_EXEC_NOTEOL;

	/* Execute the search-request */
	if (regs && regs->num_regs) {
		re_regmatch_t *matches;
		matches = (re_regmatch_t *)malloc(regs->num_regs, sizeof(re_regmatch_t));
		if unlikely(!matches)
			return -2;
		exec.rx_nmatch = regs->num_regs;
		exec.rx_pmatch = matches;
		status = re_exec_search(&exec, (size_t)range, NULL);
		if (status >= 0)
			regmatch2glibc((regmatch_t const *)matches, regs);
		free(matches);
	} else {
		exec.rx_nmatch = 0;
		status = re_exec_search(&exec, (size_t)range, NULL);
	}
	if (status >= 0)
		return status;
	if (status == -RE_NOMATCH)
		return -1;
	return -2; /* "internal" error */
}
/*[[[end:libc_re_search]]]*/

/*[[[head:libc_re_search_2,hash:CRC-32=0xac92fcd5]]]*/
/* >> re_search_2(3)
 * Same as `re_search(3)',  but use the  virtual concatenation of  `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_search(3R)' from `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   Was able to discover a match at this offset. (always `< range')
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(1) ATTR_INS(2, 3) ATTR_INS(4, 5) ATTR_OUT_OPT(8) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_re_search_2)(regex_t __KOS_FIXED_CONST *self,
                                       char const *string1,
                                       __STDC_INT_AS_SIZE_T length1,
                                       char const *string2,
                                       __STDC_INT_AS_SIZE_T length2,
                                       __STDC_INT_AS_SIZE_T start,
                                       __STDC_INT_AS_SIZE_T range,
                                       struct __re_registers *regs,
                                       __STDC_INT_AS_SIZE_T stop)
/*[[[body:libc_re_search_2]]]*/
{
	struct re_exec exec;
	struct iovec iov[2];
	ssize_t status;
	if unlikely(!libregex_load())
		return -2;

	/* Set-up in regex execution controller. */
	iov[0].iov_base  = (void *)string1;
	iov[0].iov_len   = (size_t)length1;
	iov[1].iov_base  = (void *)string2;
	iov[1].iov_len   = (size_t)length2;
	exec.rx_code     = regex_getcode(self);
	exec.rx_iov      = iov;
	exec.rx_startoff = (size_t)start;
	exec.rx_endoff   = (size_t)start + (size_t)stop;
	exec.rx_extra    = (size_t)stop - ((size_t)length1 + (size_t)length2);
	exec.rx_eflags   = 0;
	if (self->not_bol)
		exec.rx_eflags |= RE_EXEC_NOTBOL;
	if (self->not_eol)
		exec.rx_eflags |= RE_EXEC_NOTEOL;

	/* Execute the search-request */
	if (regs && regs->num_regs) {
		re_regmatch_t *matches;
		matches = (re_regmatch_t *)malloc(regs->num_regs, sizeof(re_regmatch_t));
		if unlikely(!matches)
			return -2;
		exec.rx_nmatch = regs->num_regs;
		exec.rx_pmatch = matches;
		status = re_exec_search(&exec, (size_t)range, NULL);
		if (status >= 0)
			regmatch2glibc((regmatch_t const *)matches, regs);
		free(matches);
	} else {
		exec.rx_nmatch = 0;
		status = re_exec_search(&exec, (size_t)range, NULL);
	}
	if (status >= 0)
		return status;
	if (status == -RE_NOMATCH)
		return -1;
	return -2; /* "internal" error */
}
/*[[[end:libc_re_search_2]]]*/

/*[[[head:libc_re_match,hash:CRC-32=0x5074d92c]]]*/
/* >> re_match(3)
 * Match input data `[string+start,string+length)' against the regex pattern `self'
 * The accessed area of the input buffer is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  The number of bytes starting at `start' that were matched against `self'
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(1) ATTR_INS(2, 3) ATTR_OUT_OPT(5) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_re_match)(regex_t __KOS_FIXED_CONST *self,
                                    char const *string,
                                    __STDC_INT_AS_SIZE_T length,
                                    __STDC_INT_AS_SIZE_T start,
                                    struct __re_registers *regs)
/*[[[body:libc_re_match]]]*/
{
	struct re_exec exec;
	struct iovec iov[1];
	ssize_t status;
	if unlikely(!libregex_load())
		return -2;

	/* Set-up in regex execution controller. */
	iov[0].iov_base  = (void *)string;
	iov[0].iov_len   = (size_t)length;
	exec.rx_code     = regex_getcode(self);
	exec.rx_iov      = iov;
	exec.rx_startoff = (size_t)start;
	exec.rx_endoff   = (size_t)start + (size_t)length;
	exec.rx_extra    = 0;
	exec.rx_eflags   = 0;
	if (self->not_bol)
		exec.rx_eflags |= RE_EXEC_NOTBOL;
	if (self->not_eol)
		exec.rx_eflags |= RE_EXEC_NOTEOL;

	/* Execute the match-request */
	if (regs && regs->num_regs) {
		re_regmatch_t *matches;
		matches = (re_regmatch_t *)malloc(regs->num_regs, sizeof(re_regmatch_t));
		if unlikely(!matches)
			return -2;
		exec.rx_nmatch = regs->num_regs;
		exec.rx_pmatch = matches;
		status = re_exec_match(&exec);
		if (status >= 0)
			regmatch2glibc((regmatch_t const *)matches, regs);
		free(matches);
	} else {
		exec.rx_nmatch = 0;
		status = re_exec_match(&exec);
	}
	if (status >= 0)
		return status;
	if (status == -RE_NOMATCH)
		return -1;
	return -2; /* "internal" error */
}
/*[[[end:libc_re_match]]]*/

/*[[[head:libc_re_match_2,hash:CRC-32=0xca7bdc41]]]*/
/* >> re_match_2(3)
 * Same  as `re_match(3)',  but use  the virtual  concatenation of `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_match(3R)' from  `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   The number of bytes starting at `start' that were matched against `self'
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(1) ATTR_INS(2, 3) ATTR_INS(4, 5) ATTR_OUT_OPT(7) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_re_match_2)(regex_t __KOS_FIXED_CONST *self,
                                      char const *string1,
                                      __STDC_INT_AS_SIZE_T length1,
                                      char const *string2,
                                      __STDC_INT_AS_SIZE_T length2,
                                      __STDC_INT_AS_SIZE_T start,
                                      struct __re_registers *regs,
                                      __STDC_INT_AS_SIZE_T stop)
/*[[[body:libc_re_match_2]]]*/
{
	struct re_exec exec;
	struct iovec iov[2];
	ssize_t status;
	if unlikely(!libregex_load())
		return -2;

	/* Set-up in regex execution controller. */
	iov[0].iov_base  = (void *)string1;
	iov[0].iov_len   = (size_t)length1;
	iov[1].iov_base  = (void *)string2;
	iov[1].iov_len   = (size_t)length2;
	exec.rx_code     = regex_getcode(self);
	exec.rx_iov      = iov;
	exec.rx_startoff = (size_t)start;
	exec.rx_endoff   = (size_t)start + (size_t)stop;
	exec.rx_extra    = (size_t)stop - ((size_t)length1 + (size_t)length2);
	exec.rx_eflags   = 0;
	if (self->not_bol)
		exec.rx_eflags |= RE_EXEC_NOTBOL;
	if (self->not_eol)
		exec.rx_eflags |= RE_EXEC_NOTEOL;

	/* Execute the match-request */
	if (regs && regs->num_regs) {
		re_regmatch_t *matches;
		matches = (re_regmatch_t *)malloc(regs->num_regs, sizeof(re_regmatch_t));
		if unlikely(!matches)
			return -2;
		exec.rx_nmatch = regs->num_regs;
		exec.rx_pmatch = matches;
		status = re_exec_match(&exec);
		if (status >= 0)
			regmatch2glibc((regmatch_t const *)matches, regs);
		free(matches);
	} else {
		exec.rx_nmatch = 0;
		status = re_exec_match(&exec);
	}
	if (status >= 0)
		return status;
	if (status == -RE_NOMATCH)
		return -1;
	return -2; /* "internal" error */
}
/*[[[end:libc_re_match_2]]]*/

/*[[[head:libc_regcomp,hash:CRC-32=0x6d541a0b]]]*/
/* >> regcomp(3)
 * Compile a regular expression `pattern' and initialize `self'
 * @param: self:    Storage for the produced regex pattern.
 * @param: pattern: The pattern to compile.
 * @param: cflags:  Set of `REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB'
 * @return: REG_NOERROR: Success
 * @return: REG_BADPAT:  General pattern syntax error.
 * @return: REG_ECTYPE:  Invalid/unknown character class name.
 * @return: REG_EESCAPE: Trailing backslash.
 * @return: REG_ESUBREG: Invalid back reference.
 * @return: REG_EBRACK:  Unmatched '['.
 * @return: REG_EPAREN:  Unmatched '('.
 * @return: REG_EBRACE:  Unmatched '{'.
 * @return: REG_BADBR:   Invalid contents of '{...}'.
 * @return: REG_ERANGE:  Invalid range end (e.g. '[z-a]').
 * @return: REG_ESPACE:  Out of memory.
 * @return: REG_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
 * @return: REG_EEND:    Unexpected end of pattern.
 * @return: REG_ESIZE:   Compiled pattern bigger than 2^16 bytes.
 * @return: REG_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: REG_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]")
 * @return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_regcomp)(regex_t *__restrict self,
                                   char const *__restrict pattern,
                                   int cflags)
/*[[[body:libc_regcomp]]]*/
{
	re_errno_t error;
	struct re_compiler comp;
	struct re_code *code;
	reg_syntax_t syntax;
	if unlikely(!libregex_load())
		return REG_ENOSYS;

	/* Figure out syntax flags */
	syntax = RE_SYNTAX_POSIX_BASIC;
	if (cflags & REG_EXTENDED)
		syntax = RE_SYNTAX_POSIX_EXTENDED;
	if (cflags & REG_ICASE)
		syntax |= RE_SYNTAX_ICASE;
	if (cflags & REG_NEWLINE) {
		syntax &= ~RE_SYNTAX_DOT_NEWLINE;
		syntax |= RE_SYNTAX_HAT_LISTS_NOT_NEWLINE | RE_SYNTAX_ANCHORS_IGNORE_EFLAGS;
	}
	if (cflags & REG_NOSUB)
		syntax |= RE_SYNTAX_NO_SUB;

	/* Initialize the regex compiler */
	re_compiler_init(&comp, pattern, strend(pattern), syntax);

	/* Compile the pattern. */
	error = re_compiler_compile(&comp);
	if unlikely(error != RE_NOERROR) {
		re_compiler_fini(&comp);
		return error;
	}
	code = re_compiler_pack(&comp);

	/* Compilation was successful -> fill in `self' */
	self->buffer           = (typeof(self->buffer))code;
	self->syntax           = comp.rec_parser.rep_syntax;
	self->re_nsub          = code->rc_ngrps;
	self->can_be_null      = code->rc_minmatch == 0 ? 1 : 0;
	self->fastmap_accurate = 1;
	self->no_sub           = (comp.rec_parser.rep_syntax & RE_SYNTAX_NO_SUB) ? 1 : 0;
	self->newline_anchor   = (comp.rec_parser.rep_syntax & RE_SYNTAX_ANCHORS_IGNORE_EFLAGS) ? 1 : 0;
	return RE_NOERROR;
}
/*[[[end:libc_regcomp]]]*/

/*[[[head:libc_regexec,hash:CRC-32=0x28fdbea2]]]*/
/* >> regexec(3)
 * Execute a compiled regular expression `pattern' on the priveded string.
 * - This function searches for the FIRST position in `string' at which `self' can be matched.
 * - When `nmatch > 0' (and `REG_NOSUB' wasn't set), the matched address-range is stored in `pmatch[0]'
 * - When `nmatch > 1' (and `REG_NOSUB' wasn't set), the start/end-offsets of "(...)"-groups are stored
 *   here for up to the  first `nmatch - 1' groups. Non-existant groups  are assigned `-1' in  offsets.
 * - When nothing was matched, and `nmatch > 0' (and `REG_NOSUB' wasn't set), the offsets of all elements
 *   of `pmatch' are set to `-1' (thus indicating a lack of any sort of match).
 * @param: self:   The compiled regex pattern.
 * @param: string: Input data that should be matched (must be a NUL-terminated string, unless `REG_STARTEND' is given)
 * @param: nmatch: one plus max # of group start/end-offsets to write to `*pmatch' (ignored if `REG_NOSUB' was set)
 *                 When non-zero, `pmatch[0]' will receive the start/end offsets where `self' matched in  `string'.
 * @param: pmatch: Storage for at least `nmatch' group start/end-offsets (ignored if `REG_NOSUB' was set)
 * @param: eflags: Set of `REG_NOTBOL | REG_NOTEOL | REG_STARTEND'
 * @return: 0:           Success
 * @return: REG_NOMATCH: Nothing was matched, or some internal error happened */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_regexec)(regex_t const *__restrict self,
                                   char const *__restrict string,
                                   size_t nmatch,
                                   regmatch_t pmatch[__restrict_arr],
                                   int eflags)
/*[[[body:libc_regexec]]]*/
{
	struct re_exec exec;
	struct iovec iov[1];
	ssize_t status;
	size_t match_size;
	if unlikely(!libregex_load())
		return REG_NOMATCH;

	/* If compiled with `REG_NOSUB', don't fill in `pmatch' */
	if (self->no_sub)
		nmatch = 0;

	/* Set-up in regex execution controller. */
	if (eflags & REG_STARTEND) {
		exec.rx_startoff = (size_t)pmatch[0].rm_so;
		exec.rx_endoff   = (size_t)pmatch[0].rm_eo;
	} else {
		exec.rx_startoff = 0;
		exec.rx_endoff   = strlen(string);
	}
	iov[0].iov_base = (void *)string;
	iov[0].iov_len  = (size_t)exec.rx_endoff;
	exec.rx_code    = regex_getcode(self);
	exec.rx_iov     = iov;
	exec.rx_extra   = 0;
	exec.rx_eflags  = eflags;
	exec.rx_nmatch  = nmatch;
	exec.rx_pmatch  = (re_regmatch_t *)pmatch;
	if (nmatch) {
		/* Make space for the slot that will take the entire matched area. */
		--exec.rx_nmatch;
		++exec.rx_pmatch;
	}

	/* Execute the match-request */
	status = re_exec_search(&exec, exec.rx_endoff - exec.rx_startoff, &match_size);
	if (status < 0) {
		/* Mark all match registers as non-matching. */
		memsetc(pmatch, (regoff_t)-1, 2 * nmatch, sizeof(regoff_t));
		return REG_NOMATCH;
	}

	/* Fill in extra match information if the caller provided space for it. */
	if (nmatch) {
		/* "The entire regular expression's match addresses are stored in pmatch[0]." */
		pmatch[0].rm_so = (size_t)status;
		pmatch[0].rm_eo = (size_t)status + match_size;

		/* If space for more groups than actually exist  was
		 * given, must fill in unused groups as not-matched. */
		++pmatch;
		--nmatch;
		if (nmatch > self->re_nsub) {
			pmatch += self->re_nsub;
			nmatch -= self->re_nsub;
			memsetc(pmatch, (regoff_t)-1, 2 * nmatch, sizeof(regoff_t));
		}
	}
	return 0;
}
/*[[[end:libc_regexec]]]*/


/* The static buffer used by `re_comp(3)' and `re_exec(3)' */
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.regex")
struct re_code *libc_re_comp_buffer = NULL;

PRIVATE ATTR_SECTION(".rodata.crt.compat.glibc.regex")
char const libc_re_comp_no_pattern_errmsg[] = "No previous regular expression";


/*[[[head:libc_re_comp,hash:CRC-32=0xce6dd18]]]*/
/* >> re_comp(3)
 * Compare the given `pattern' and assign it to an internal regex buffer which can
 * then later be used in conjunction with `re_exec(3)'. The Syntax options used by
 * this function are  `re_syntax_options | RE_ANCHORS_IGNORE_EFLAGS'. By  default,
 * the global `re_syntax_options' is set to `RE_SYNTAX_EMACS'.
 * WARNING: This function is not thread-safe!
 * @param: pattern: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
 * @return: NULL:   Success
 * @return: * :     Error (returned pointer is the human-readable error message, as returned by `regerrordesc_np(3)')
 *                  In this case, the internal, static regex buffer is left unaltered. */
INTERN ATTR_SECTION(".text.crt.compat.glibc.regex") char __KOS_FIXED_CONST *
NOTHROW_NCX(LIBCCALL libc_re_comp)(const char *pattern)
/*[[[body:libc_re_comp]]]*/
{
	re_errno_t error;
	struct re_code *oldpat;
	struct re_compiler comp;
	if (pattern == NULL) {
		if (libc_re_comp_buffer == NULL)
			return NULL;
		return (char *)libc_re_comp_no_pattern_errmsg;
	}
	if unlikely(!libregex_load())
		return (char *)regerrordesc_np(REG_ENOSYS);

	/* Initialize the regex compiler */
	re_compiler_init(&comp, pattern, strend(pattern),
	                 re_syntax_options | RE_ANCHORS_IGNORE_EFLAGS);

	/* Compile the pattern. */
	error = re_compiler_compile(&comp);
	if unlikely(error != RE_NOERROR) {
		re_compiler_fini(&comp);
		return (char *)regerrordesc_np(error);
	}

	/* Remember the newly compiled regex code blob. */
	oldpat = libc_re_comp_buffer;
	libc_re_comp_buffer = re_compiler_pack(&comp);
	free(oldpat);

	/* Indicate no-error. */
	return NULL;
}
/*[[[end:libc_re_comp]]]*/

/*[[[head:libc_re_exec,hash:CRC-32=0xb1611a3c]]]*/
/* >> re_exec(3)
 * Try to match the regex previous compiled by `re_comp(3)'
 * against some sub-string of `string'. This is equivalent to:
 * >> re_search(&REGEX_COMPILED_BY_RE_COMP, // self
 * >>           string,                     // string
 * >>           strlen(string),             // length
 * >>           0,                          // start
 * >>           strlen(string),             // range
 * >>           NULL) >= 0                  // regs
 * Note that to  force matching to  only happen at  the start of  `string',
 * the pattern passed to `re_comp(3)' should begin with "^" (thus requiring
 * that the pattern only matches at the start, or after a line-feed).
 *
 * If `re_comp(3)' has never been called, always returns `0'
 * @param: string: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
 * @return: 1:     The given `string' contains (at least) one matching sub-string
 * @return: 0:     The given `string' does not contain a sub-string that matches the previously compiled pattern. */
INTERN ATTR_SECTION(".text.crt.compat.glibc.regex") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_re_exec)(const char *string)
/*[[[body:libc_re_exec]]]*/
{
	size_t len;
	struct re_exec exec;
	struct iovec iov[1];
	ssize_t status;

	/* Initialize the regex execution controller. */
	len              = strlen(string);
	exec.rx_startoff = 0;
	exec.rx_endoff   = len;
	iov[0].iov_base  = (void *)string;
	iov[0].iov_len   = len;
	exec.rx_code     = libc_re_comp_buffer;
	exec.rx_iov      = iov;
	exec.rx_extra    = 0;
	exec.rx_eflags   = 0;
	exec.rx_nmatch   = 0;
	if unlikely(!exec.rx_code)
		return 0; /* No pattern was ever compiled. */

#if 0 /* NOTE: Since we know that a pattern has been compiled, we can
       *       also safely assume that `libregex.so' has been loaded. */
	if unlikely(!libregex_load())
		return 0;
#endif

	/* Execute the match-request.
	 *
	 * Note how we use `re_exec_search()' here, since we
	 * don't just want to match at the start of `string' */
	status = re_exec_search(&exec, len, NULL);

	/* Return indicative of a match having happened somewhere */
	return status >= 0 ? 1 : 0;
}
/*[[[end:libc_re_exec]]]*/



/*[[[start:exports,hash:CRC-32=0x80680e6b]]]*/
DEFINE_PUBLIC_ALIAS(re_compile_pattern, libc_re_compile_pattern);
DEFINE_PUBLIC_ALIAS(re_search, libc_re_search);
DEFINE_PUBLIC_ALIAS(re_search_2, libc_re_search_2);
DEFINE_PUBLIC_ALIAS(re_match, libc_re_match);
DEFINE_PUBLIC_ALIAS(re_match_2, libc_re_match_2);
DEFINE_PUBLIC_ALIAS(regcomp, libc_regcomp);
DEFINE_PUBLIC_ALIAS(regexec, libc_regexec);
DEFINE_PUBLIC_ALIAS(re_comp, libc_re_comp);
DEFINE_PUBLIC_ALIAS(re_exec, libc_re_exec);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_REGEX_C */
