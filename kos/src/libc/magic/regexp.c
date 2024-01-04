/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: EMX kLIBC     (/libc/include/regexp.h) */
/* (#) Portability: GNU C Library (/misc/regexp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/regexp.h) */
/* (#) Portability: NetBSD        (/include/regexp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/regexp.h) */
/* (#) Portability: libc4/5       (/include/regexp.h) */
/* (#) Portability: libc6         (/include/regexp.h) */
/* (#) Portability: mintlib       (/include/regexp.h) */
/* (#) Portability: uClibc        (/include/regexp.h) */
}

%[define_replacement(regex_t = "struct re_pattern_buffer")]
%[define_replacement(regoff_t = __regoff_t)]
%[define_replacement(regmatch_t = "struct __regmatch")]

%[default:section(".text.crt{|.dos}.compat.glibc.regex")]

%(auto_source){
#include "../libc/globals.h"
}

%{
#include <features.h>

#include <hybrid/__alloca.h>
#include <hybrid/typecore.h>

#include <regex.h>

#include <libc/string.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Old, deprecated, (weird), and in many places since-removed posix API for regex.
 *
 * Before this header can be #include'ed, the user has to first define the
 * following set of macros:
 *
 * >> int GETC();
 *    Return the next character from the pattern string;
 *    Returns `__eof' (the 4th argument of `compile(3)') once the end has been reached
 *    Additionally,  `compile(3)' will also  stop reading from this  macro once it has
 *    returned either '\0' or '\n'.
 *
 * >> int PEEKC();
 *    [optional] (this macro is never used by KOS's implementation)
 *    Same as `GETC()', but  don't actually consume the  character.
 *
 * >> void UNGETC(int ch);
 *    Unread a the last-read character `ch' from `GETC()'. It is guarantied that `ch'
 *    is equal to the character last-returned by `GETC()'
 *
 * >> void RETURN(char *endp)
 *    Called once `compile(3)' is  done. The given  `endp' is supposed  to be a  pointer
 *    to the end of the internal compiled regular expression buffer, but there literally
 *    is  no reason you  would ever need to  know that (since  the actual code-buffer is
 *    allocated and filled  entirely internally). As  such, on KOS,  we simply return  a
 *    pointer to the end of the internal `regex_t' object.
 *
 * >> void ERROR(int errcode);
 *    Called by `compile(3)' for abnormal termination. The given `errcode' is one of:
 *    - 11: REG_ERANGE
 *    - 16: Never returned (meant to be "Bad number")
 *    - 25: REG_ESUBREG
 *    - 36: Everything else (meant to be "Illegal or missing delimiter")
 *    - 41: Never returned (meant to be "No remembered search string")
 *    - 42: REG_EPAREN
 *    - 43: REG_ESIZE
 *    - 44: REG_EBRACE
 *    - 45: Never returned (meant to be "} expected after \")
 *    - 46: REG_BADBR
 *    - 49: REG_EBRACK
 *    - 50: REG_ESPACE
 */
#if (defined(__BUILDING_LIBC) || defined(__DO_NOT_DEFINE_COMPILE) || \
     (defined(GETC) && defined(PEEKC) && defined(RETURN) && defined(ERROR)))

/* Variables used by `step(3)' and `advance(3)' */
#ifndef loc1
#ifdef __LOCAL_loc1
#define loc1 __LOCAL_loc1
#elif defined(__CRT_HAVE_loc1)
__CSDECLARE(,char *,loc1);
#define loc1 loc1
#endif /* __CRT_HAVE_loc1 */
#endif /* !loc1 */

#ifndef loc2
#ifdef __LOCAL_loc2
#define loc2 __LOCAL_loc2
#elif defined(__CRT_HAVE_loc2)
__CSDECLARE(,char *,loc2);
#define loc2 loc2
#endif /* __CRT_HAVE_loc2 */
#endif /* !loc2 */

#ifndef locs
#ifdef __LOCAL_locs
#define locs __LOCAL_locs
#elif defined(__CRT_HAVE_locs)
__CSDECLARE(,char *,locs); /* NOTE: Never used internally! */
#define locs locs
#endif /* __CRT_HAVE_locs */
#endif /* !locs */


#if !defined(__DO_NOT_DEFINE_COMPILE) && !defined(__BUILDING_LIBC)
}
%[insert:pp_if($has_function(regcomp) && defined(__hybrid_alloca))]
%{

/* Compile a regular expression
 * @param: instring: Completely unused, and meaningless
 * @param: expbuf:   Start pointer for compiled-regular-expression buffer.  This
 *                   argument must later be passed to `step(3)' and `advance(3)'
 * @param: endbuf:   End pointer for compiled-regular-expression buffer
 * @param: eof:      Value returned by `GETC()' to indicate end-of-input.
 *                   But note that additionally,  '\0' and '\n' are  also
 *                   treated as end-of-input  markers (though those  will
 *                   be  `UNGETC()'d, unlike when `GETC()' returns `eof') */
__ATTR_NOINLINE /* noinline because of our use of `alloca(3)' */
char *(compile)(char *__instring, char *__expbuf, char const *__endbuf, int __eof) {
	char *__pattern_str = __NULLPTR;
	__SIZE_TYPE__ __pattern_size = 0;
	__SIZE_TYPE__ __pattern_alloc = 0;
	int __ch, __error;
	regex_t *__re;
	/* Align the input buffer (this will also be done by `step(3)' and `advance(3)') */
	__expbuf = (char *)((__UINTPTR_TYPE__)(__expbuf + __COMPILER_ALIGNOF(regex_t) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                    ~(__COMPILER_ALIGNOF(regex_t) - 1));
	if ((__expbuf + sizeof(regex_t)) > __endbuf) {
		ERROR(50);
	}
	__re = (regex_t *)__expbuf;
	while ((__ch = (GETC())) != __eof) {
		if (__ch == '\0' || __ch == '\n') {
			UNGETC(__ch);
			break;
		}
		if (__pattern_size >= __pattern_alloc) {
			char *__new_pattern_buf;
			__SIZE_TYPE__ __new_pattern_alloc;
			__new_pattern_alloc = __pattern_size * 2;
			if (__new_pattern_alloc < 128)
				__new_pattern_alloc = 128;
			__new_pattern_buf = (char *)__hybrid_alloca((__new_pattern_alloc + 1) * sizeof(char));
			__new_pattern_buf = (char *)__libc_memcpy(__new_pattern_buf, __pattern_str,
			                                          __pattern_size * sizeof(char));
			__pattern_str   = __new_pattern_buf;
			__pattern_alloc = __new_pattern_alloc;
		}
		__pattern_str[__pattern_size++] = (char)(unsigned char)(unsigned int)__ch;
	}
	__pattern_str[__pattern_size] = '\0';

	/* With the entire pattern string read, compile it */
	__error = regcomp(__re, __pattern_str, REG_NEWLINE);
	if (__error != REG_NOERROR) {
		switch (__error) {
		case REG_ERANGE:  /* */ { ERROR(11); }
		case REG_ESUBREG:  /**/ { ERROR(25); }
		default:  /*         */ { ERROR(36); }
		case REG_EPAREN:  /* */ { ERROR(42); }
		case REG_ESIZE:  /*  */ { ERROR(43); }
		case REG_EBRACE:  /* */ { ERROR(44); }
		case REG_BADBR:  /*  */ { ERROR(46); }
		case REG_EBRACK:  /* */ { ERROR(49); }
		case REG_ESPACE:  /* */ { ERROR(50); }
		}
	}

	/* Everything is ok.  */
	RETURN((char *)(__re + 1));
}
}
%[insert:pp_endif]
%{
#endif /* !__DO_NOT_DEFINE_COMPILE && !__BUILDING_LIBC */

}

%[define_replacement(loc1 = __LOCAL_loc1)]
%[define_replacement(loc2 = __LOCAL_loc2)]
%[define_replacement(locs = __LOCAL_locs)]

@@>> step(3)
@@Find the next matching position in `string', given `expbuf' as previously passed to `compile(3)'
@@@return: 0: No match
@@@return: 1: Match was found in range `[loc1,loc2)' (yes: these are global variables)
[[requires_include("<asm/crt/regex.h>")]]
[[requires_include("<libc/template/locN.h>")]]
[[requires(defined(__LOCAL_loc1) && defined(__LOCAL_loc2) &&
           defined(__REG_NOTEOL) && $has_function(regexec))]]
[[impl_include("<libc/template/locN.h>")]]
[[export_alias("__step")]] /* From Glibc 2.0.4 */
int step(char const *string, char const *expbuf) {
	regmatch_t match;
	expbuf = (char *)((__UINTPTR_TYPE__)(expbuf + __COMPILER_ALIGNOF(regex_t) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                  ~(__COMPILER_ALIGNOF(regex_t) - 1));
	if (regexec((regex_t const *)expbuf, string, 1, &match, __REG_NOTEOL) != 0)
		return 0;
	loc1 = (char *)string + match.@rm_so@;
	loc2 = (char *)string + match.@rm_eo@;
	return 1;
}


@@>> advance(3)
@@Match the beginning of `string' against `expbuf' as previously passed to `compile(3)'
@@@return: 0: No match (or just not at the beginning of `string')
@@@return: 1: Match was found in range `[string,loc2)' (`string' being the first
@@            argument  to this  function, and  `loc2' being  a global variable)
[[requires_include("<asm/crt/regex.h>")]]
[[requires_include("<libc/template/locN.h>")]]
[[requires(defined(__LOCAL_loc2) && defined(__REG_NOTEOL) && $has_function(regexec))]]
[[impl_include("<libc/template/locN.h>")]]
[[export_alias("__advance")]] /* From Glibc 2.0.4 */
int advance(char const *string, char const *expbuf) {
	regmatch_t match;
	expbuf = (char *)((__UINTPTR_TYPE__)(expbuf + __COMPILER_ALIGNOF(regex_t) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                  ~(__COMPILER_ALIGNOF(regex_t) - 1));
	if (regexec((regex_t const *)expbuf, string, 1, &match, __REG_NOTEOL) != 0)
		return 0;
	if (match.@rm_so@ != 0)
		return 0;
	loc2 = (char *)string + match.@rm_eo@;
	return 1;
}

%{

#endif /* __BUILDING_LIBC || __DO_NOT_DEFINE_COMPILE || (GETC && PEEKC && RETURN && ERROR) */

/* TODO: Rather   than  what's  above,  NetBSD  defines  another,
 *       deprecated interface here that conflicts with <regex.h>:
 * >> typedef struct regexp { ... } regexp;
 * >> regexp *regcomp(char const *pattern) __COMPILER_ASMNAME("__compat_regcomp");
 * >> int regexec(regexp const *re, char const *input) __COMPILER_ASMNAME("__compat_regexec");
 * >> void regsub(regexp const *re, char const *???, char *???) __COMPILER_ASMNAME("__compat_regsub");
 * >> void regerror(char const *???) __COMPILER_ASMNAME("__compat_regerror");
 *
 * KOS should implement this API for compatibility
 */

__SYSDECL_END
#endif /* __CC__ */

}
