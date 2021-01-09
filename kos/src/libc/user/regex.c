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
#ifndef GUARD_LIBC_USER_REGEX_C
#define GUARD_LIBC_USER_REGEX_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libregex/regex.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "regex.h"

DECL_BEGIN

#define REGEX_DATA   ATTR_SECTION(".data.crt.utility.regex")
#define REGEX_RODATA ATTR_SECTION(".rodata.crt.utility.regex")
#define REGEX_BSS    ATTR_SECTION(".bss.crt.utility.regex")

#ifndef LIBREGEX_WANT_PROTOTYPES
#define DEFINE_REGEX_BINDING(T, name)                     \
	PRIVATE REGEX_BSS T pdyn_##name               = NULL; \
	PRIVATE REGEX_RODATA char const name_##name[] = #name
PRIVATE REGEX_BSS void *libregex = NULL;
DEFINE_REGEX_BINDING(PREGEX_MATCHESPTR, regex_matchesptr);
DEFINE_REGEX_BINDING(PREGEX_FIND, regex_find);
DEFINE_REGEX_BINDING(PREGEX_RFIND, regex_rfind);
DEFINE_REGEX_BINDING(PREGEX_FINDPTR, regex_findptr);
DEFINE_REGEX_BINDING(PREGEX_RFINDPTR, regex_rfindptr);
DEFINE_REGEX_BINDING(PREGEX_FINDEX, regex_findex);
DEFINE_REGEX_BINDING(PREGEX_RFINDEX, regex_rfindex);
#define regex_matchesptr (*pdyn_regex_matchesptr)
#define regex_find       (*pdyn_regex_find)
#define regex_rfind      (*pdyn_regex_rfind)
#define regex_findptr    (*pdyn_regex_findptr)
#define regex_rfindptr   (*pdyn_regex_rfindptr)
#define regex_findex     (*pdyn_regex_findex)
#define regex_rfindex    (*pdyn_regex_rfindex)

#define REGEX_ONDEMAND()   regex_ondemand()
PRIVATE bool LIBCCALL regex_ondemand(void) {
	void *lregex;
	if likely(pdyn_regex_rfindex)
		return true;
again_read_libregex:
	lregex = ATOMIC_READ(libregex);
	if unlikely(lregex == (void *)-1)
		return false;
	if (lregex == NULL) {
		lregex = dlopen(LIBREGEX_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!lregex)
			lregex = (void *)-1;
		if unlikely(!ATOMIC_CMPXCH(libregex, NULL, lregex)) {
			if (lregex != (void *)-1)
				dlclose(lregex);
			goto again_read_libregex;
		}
	}
#define BIND(pdyn_FUNC, name_FUNC)                       \
	do {                                                 \
		*(void **)&pdyn_FUNC = dlsym(lregex, name_FUNC); \
		if unlikely(!pdyn_FUNC)                          \
			goto err;                                    \
	} __WHILE0
	BIND(pdyn_regex_matchesptr, name_regex_matchesptr);
	BIND(pdyn_regex_find, name_regex_find);
	BIND(pdyn_regex_rfind, name_regex_rfind);
	BIND(pdyn_regex_findptr, name_regex_findptr);
	BIND(pdyn_regex_rfindptr, name_regex_rfindptr);
	BIND(pdyn_regex_findex, name_regex_findex);
	/* Make sure that `pdyn_regex_rfindex' is loaded last (since it's
	 * the one we check above for our fast-pass already-loaded check) */
	COMPILER_WRITE_BARRIER();
	BIND(pdyn_regex_rfindex, name_regex_rfindex);
	COMPILER_WRITE_BARRIER();
#undef BIND
	return true;
err:
	if (ATOMIC_CMPXCH(libregex, lregex, (void *)-1))
		dlclose(lregex);
	return false;
}

#undef DEFINE_REGEX_BINDING
#else /* !LIBREGEX_WANT_PROTOTYPES */
#define REGEX_ONDEMAND()   true
#endif /* LIBREGEX_WANT_PROTOTYPES */


/*[[[start:implementation]]]*/

/*[[[head:libc_re_set_syntax,hash:CRC-32=0x1557e442]]]*/
/* Sets the current default syntax to SYNTAX, and return the old syntax.
 * You can also simply assign to the `re_syntax_options' variable */
INTERN ATTR_SECTION(".text.crt.utility.regex") reg_syntax_t
NOTHROW_NCX(LIBCCALL libc_re_set_syntax)(reg_syntax_t syntax)
/*[[[body:libc_re_set_syntax]]]*/
{
	return ATOMIC_XCH(re_syntax_options, syntax);
}
/*[[[end:libc_re_set_syntax]]]*/

/*[[[head:libc_re_compile_pattern,hash:CRC-32=0x290e93e8]]]*/
/* Compile the regular expression PATTERN, with length LENGTH
 * and syntax given by the global `re_syntax_options', into the buffer
 * BUFFER. Return NULL if successful, and an error string if not.
 * To free the allocated storage, you must call `regfree' on BUFFER.
 * Note that the translate table must either have been initialized by
 * `regcomp', with a malloc'd value, or set to NULL before calling `regfree' */
INTERN ATTR_SECTION(".text.crt.utility.regex") char const *
NOTHROW_NCX(LIBCCALL libc_re_compile_pattern)(char const *pattern,
                                              size_t length,
                                              struct re_pattern_buffer *buffer)
/*[[[body:libc_re_compile_pattern]]]*/
{
	if unlikely(!buffer)
		return strerrorname_s(EINVAL);
	buffer->buffer = (unsigned char *)strndup(pattern, length);
	if unlikely(!buffer->buffer)
		return strerrorname_s(libc_geterrno());
	return NULL;
}
/*[[[end:libc_re_compile_pattern]]]*/

/*[[[head:libc_re_compile_fastmap,hash:CRC-32=0x4d2da87b]]]*/
/* Compile a fastmap for the compiled pattern in BUFFER; used to
 * accelerate searches. Return 0 if successful and -2 if was an internal error */
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_re_compile_fastmap)(struct re_pattern_buffer *buffer)
/*[[[body:libc_re_compile_fastmap]]]*/
{
	(void)buffer; /* no-op */
	COMPILER_IMPURE();
	return 0;
}
/*[[[end:libc_re_compile_fastmap]]]*/

/*[[[head:libc_re_search,hash:CRC-32=0xdd579930]]]*/
/* Search in the string STRING (with length LENGTH) for the pattern
 * compiled into BUFFER. Start searching at position START, for RANGE
 * characters. Return the starting position of the match, -1 for no
 * match, or -2 for an internal error. Also return register
 * information in REGS (if REGS and BUFFER->no_sub are nonzero) */
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_re_search)(struct re_pattern_buffer *buffer,
                                     char const *string,
                                     int length,
                                     int start,
                                     int range,
                                     struct re_registers *regs)
/*[[[body:libc_re_search]]]*/
{
	return libc_re_search_2(buffer,
	                        string,
	                        length,
	                        NULL,
	                        0,
	                        start,
	                        range,
	                        regs,
	                        range);
}
/*[[[end:libc_re_search]]]*/

/*[[[head:libc_re_search_2,hash:CRC-32=0x18286ad5]]]*/
/* Like `re_search', but search in the concatenation of STRING1
 * and STRING2. Also, stop searching at index START + STOP */
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_re_search_2)(struct re_pattern_buffer *buffer,
                                       char const *string1,
                                       int length1,
                                       char const *string2,
                                       int length2,
                                       int start,
                                       int range,
                                       struct re_registers *regs,
                                       int stop)
/*[[[body:libc_re_search_2]]]*/
{
	if (!REGEX_ONDEMAND())
		return -2;
	(void)buffer;
	(void)string1;
	(void)length1;
	(void)string2;
	(void)length2;
	(void)start;
	(void)range;
	(void)regs;
	(void)stop;
	//TODO:regex_find(string, );
	CRT_UNIMPLEMENTED("re_search_2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_re_search_2]]]*/

/*[[[head:libc_re_match,hash:CRC-32=0x1897b9ec]]]*/
/* Like `re_search', but return how many characters in STRING
 * the regexp in BUFFER matched, starting at position START */
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_re_match)(struct re_pattern_buffer *buffer,
                                    char const *string,
                                    int length,
                                    int start,
                                    struct re_registers *regs)
/*[[[body:libc_re_match]]]*/
{
	return libc_re_match_2(buffer,
	                       string,
	                       length,
	                       NULL,
	                       0,
	                       start,
	                       regs,
	                       length);
}
/*[[[end:libc_re_match]]]*/

/*[[[head:libc_re_match_2,hash:CRC-32=0x572fd06d]]]*/
/* Relates to `re_match' as `re_search_2' relates to `re_search' */
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_re_match_2)(struct re_pattern_buffer *buffer,
                                      char const *string1,
                                      int length1,
                                      char const *string2,
                                      int length2,
                                      int start,
                                      struct re_registers *regs,
                                      int stop)
/*[[[body:libc_re_match_2]]]*/
/*AUTO*/{
	(void)buffer;
	(void)string1;
	(void)length1;
	(void)string2;
	(void)length2;
	(void)start;
	(void)regs;
	(void)stop;
	CRT_UNIMPLEMENTEDF("re_match_2(%p, %q, %x, %q, %x, %x, %p, %x)", buffer, string1, length1, string2, length2, start, regs, stop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_re_match_2]]]*/

/*[[[head:libc_re_set_registers,hash:CRC-32=0x5eab0051]]]*/
/* Set REGS to hold NUM_REGS registers, storing them in STARTS and
 * ENDS. Subsequent matches using BUFFER and REGS will use this memory
 * for recording register information. STARTS and ENDS must be allocated
 * with malloc, and must each be at least `NUM_REGS * sizeof(regoff_t)' bytes long.
 * If NUM_REGS == 0, then subsequent matches should allocate their own register data.
 * Unless this function is called, the first search or match using
 * PATTERN_BUFFER will allocate its own register data, without freeing the old data */
INTERN ATTR_SECTION(".text.crt.utility.regex") void
NOTHROW_NCX(LIBCCALL libc_re_set_registers)(struct re_pattern_buffer *buffer,
                                            struct re_registers *regs,
                                            unsigned int num_regs,
                                            regoff_t *starts,
                                            regoff_t *ends)
/*[[[body:libc_re_set_registers]]]*/
/*AUTO*/{
	(void)buffer;
	(void)regs;
	(void)num_regs;
	(void)starts;
	(void)ends;
	CRT_UNIMPLEMENTEDF("re_set_registers(%p, %p, %x, %p, %p)", buffer, regs, num_regs, starts, ends); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_re_set_registers]]]*/

/*[[[head:libc_regcomp,hash:CRC-32=0xd2f28c93]]]*/
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_regcomp)(regex_t *__restrict preg,
                                   char const *__restrict pattern,
                                   int cflags)
/*[[[body:libc_regcomp]]]*/
/*AUTO*/{
	(void)preg;
	(void)pattern;
	(void)cflags;
	CRT_UNIMPLEMENTEDF("regcomp(%p, %q, %x)", preg, pattern, cflags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_regcomp]]]*/

/*[[[head:libc_regexec,hash:CRC-32=0xec92f4c2]]]*/
INTERN ATTR_SECTION(".text.crt.utility.regex") int
NOTHROW_NCX(LIBCCALL libc_regexec)(regex_t const *__restrict preg,
                                   char const *__restrict string,
                                   size_t nmatch,
                                   regmatch_t pmatch[__restrict_arr],
                                   int eflags)
/*[[[body:libc_regexec]]]*/
{
	(void)preg;
	(void)string;
	(void)nmatch;
	(void)pmatch;
	(void)eflags;
	CRT_UNIMPLEMENTEDF("regexec(%p, %q, %Ix, %p, %x)", preg, string, nmatch, pmatch, eflags); /* TODO */
	libc_seterrno(ENOSYS);
	/* TODO: Implement this function proper.
	 *       Current, it returning -1 is a work-around for the Xorg server. */
	return -1;
}
/*[[[end:libc_regexec]]]*/

/*[[[head:libc_regerror,hash:CRC-32=0xbfc3249d]]]*/
INTERN ATTR_SECTION(".text.crt.utility.regex") size_t
NOTHROW_NCX(LIBCCALL libc_regerror)(int errcode,
                                    regex_t const *__restrict preg,
                                    char *__restrict errbuf,
                                    size_t errbuf_size)
/*[[[body:libc_regerror]]]*/
/*AUTO*/{
	(void)errcode;
	(void)preg;
	(void)errbuf;
	(void)errbuf_size;
	CRT_UNIMPLEMENTEDF("regerror(%x, %p, %q, %Ix)", errcode, preg, errbuf, errbuf_size); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_regerror]]]*/

/*[[[head:libc_regfree,hash:CRC-32=0xbb22ec1a]]]*/
INTERN ATTR_SECTION(".text.crt.utility.regex") void
NOTHROW_NCX(LIBCCALL libc_regfree)(regex_t *preg)
/*[[[body:libc_regfree]]]*/
{
	if (preg)
		free(preg->buffer);
}
/*[[[end:libc_regfree]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xac5be75f]]]*/
DEFINE_PUBLIC_ALIAS(re_set_syntax, libc_re_set_syntax);
DEFINE_PUBLIC_ALIAS(re_compile_pattern, libc_re_compile_pattern);
DEFINE_PUBLIC_ALIAS(re_compile_fastmap, libc_re_compile_fastmap);
DEFINE_PUBLIC_ALIAS(re_search, libc_re_search);
DEFINE_PUBLIC_ALIAS(re_search_2, libc_re_search_2);
DEFINE_PUBLIC_ALIAS(re_match, libc_re_match);
DEFINE_PUBLIC_ALIAS(re_match_2, libc_re_match_2);
DEFINE_PUBLIC_ALIAS(re_set_registers, libc_re_set_registers);
DEFINE_PUBLIC_ALIAS(regcomp, libc_regcomp);
DEFINE_PUBLIC_ALIAS(regexec, libc_regexec);
DEFINE_PUBLIC_ALIAS(regerror, libc_regerror);
DEFINE_PUBLIC_ALIAS(regfree, libc_regfree);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_REGEX_C */
