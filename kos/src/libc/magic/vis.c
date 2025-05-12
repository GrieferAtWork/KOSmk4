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
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/vis.h) */
/* (#) Portability: NetBSD        (/include/vis.h) */
/* (#) Portability: OpenBSD       (/include/vis.h) */
/* (#) Portability: libbsd        (/include/bsd/vis.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.bsd.vis")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/vis.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __INTELLISENSE__
#include <bits/types/size_t.h>
#endif /* __INTELLISENSE__ */

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

/* Flags for `vis(3)' */
#if !defined(VIS_OCTAL) && defined(__VIS_OCTAL)
#define VIS_OCTAL     __VIS_OCTAL     /* Always use octal encoding (e.g. "\123") */
#endif /* !VIS_OCTAL && __VIS_OCTAL */
#if !defined(VIS_CSTYLE) && defined(__VIS_CSTYLE)
#define VIS_CSTYLE    __VIS_CSTYLE    /* Enable support for c-style escape aliases (e.h. "\n" instead of "\012") */
#endif /* !VIS_CSTYLE && __VIS_CSTYLE */
#if !defined(VIS_SP) && defined(__VIS_SP)
#define VIS_SP        __VIS_SP        /* The character " " (space) needs to be \-escaped */
#endif /* !VIS_SP && __VIS_SP */
#if !defined(VIS_TAB) && defined(__VIS_TAB)
#define VIS_TAB       __VIS_TAB       /* The character "\t" (tab) needs to be \-escaped */
#endif /* !VIS_TAB && __VIS_TAB */
#if !defined(VIS_NL) && defined(__VIS_NL)
#define VIS_NL        __VIS_NL        /* The character "\n" (new-line) needs to be \-escaped */
#endif /* !VIS_NL && __VIS_NL */
#if !defined(VIS_SAFE) && defined(__VIS_SAFE)
#define VIS_SAFE      __VIS_SAFE      /* Character "\b", "\a" and "\r" don't need to be escaped */
#endif /* !VIS_SAFE && __VIS_SAFE */
#if !defined(VIS_NOSLASH) && defined(__VIS_NOSLASH)
#define VIS_NOSLASH   __VIS_NOSLASH   /* The character "\\" (backslash) doesn't need to be \-escaped */
#endif /* !VIS_NOSLASH && __VIS_NOSLASH */
#if !defined(VIS_HTTP1808) && defined(__VIS_HTTPSTYLE)
#define VIS_HTTP1808  __VIS_HTTPSTYLE /* Enable support for '%AB'-escape sequences */
#endif /* !VIS_HTTP1808 && __VIS_HTTPSTYLE */
#if !defined(VIS_HTTPSTYLE) && defined(__VIS_HTTPSTYLE)
#define VIS_HTTPSTYLE __VIS_HTTPSTYLE /* Enable support for '%AB'-escape sequences */
#endif /* !VIS_HTTPSTYLE && __VIS_HTTPSTYLE */
#if !defined(VIS_MIMESTYLE) && defined(__VIS_MIMESTYLE)
#define VIS_MIMESTYLE __VIS_MIMESTYLE /* Enable support for '=AB'-escape sequences */
#endif /* !VIS_MIMESTYLE && __VIS_MIMESTYLE */
#if !defined(VIS_HTTP1866) && defined(__VIS_HTTP1866)
#define VIS_HTTP1866  __VIS_HTTP1866  /* Enable support for '&amp;'-escape sequences */
#endif /* !VIS_HTTP1866 && __VIS_HTTP1866 */
#if !defined(VIS_NOESCAPE) && defined(__VIS_NOESCAPE)
#define VIS_NOESCAPE  __VIS_NOESCAPE  /* Disable support for '\'-escape sequences */
#endif /* !VIS_NOESCAPE && __VIS_NOESCAPE */
#if !defined(_VIS_END) && defined(__VIS_END)
#define _VIS_END      __VIS_END       /* s.a. `UNVIS_END' */
#endif /* !_VIS_END && __VIS_END */
#if !defined(VIS_GLOB) && defined(__VIS_GLOB)
#define VIS_GLOB      __VIS_GLOB      /* Characters >>>*?[#<<<                need to be \-escaped */
#endif /* !VIS_GLOB && __VIS_GLOB */
#if !defined(VIS_SHELL) && defined(__VIS_SHELL)
#define VIS_SHELL     __VIS_SHELL     /* Characters >>>'`";&<>()|{}]\\$!^~<<< need to be \-escaped */
#endif /* !VIS_SHELL && __VIS_SHELL */
#if !defined(VIS_NOLOCALE) && defined(__VIS_NOLOCALE)
#define VIS_NOLOCALE  __VIS_NOLOCALE  /* ??? */
#endif /* !VIS_NOLOCALE && __VIS_NOLOCALE */
#if !defined(VIS_DQ) && defined(__VIS_DQ)
#define VIS_DQ        __VIS_DQ        /* The character '"' (double-quote) needs to be \-escaped */
#endif /* !VIS_DQ && __VIS_DQ */
#if !defined(VIS_WHITE) && defined(__VIS_WHITE)
#define VIS_WHITE     __VIS_WHITE     /* Alias for `VIS_SP | VIS_TAB | VIS_NL' */
#endif /* !VIS_WHITE && __VIS_WHITE */
#if !defined(VIS_META) && defined(__VIS_META)
#define VIS_META      __VIS_META      /* Alias for `VIS_WHITE | VIS_GLOB | VIS_SHELL' */
#endif /* !VIS_META && __VIS_META */



/* Return values for `unvis(3)' */
#if !defined(UNVIS_ERROR) && defined(__UNVIS_ERROR)
#define UNVIS_ERROR     __UNVIS_ERROR     /* /unused/ */
#endif /* !UNVIS_ERROR && __UNVIS_ERROR */
#if !defined(UNVIS_SYNBAD) && defined(__UNVIS_SYNBAD)
#define UNVIS_SYNBAD    __UNVIS_SYNBAD    /* Syntax error */
#endif /* !UNVIS_SYNBAD && __UNVIS_SYNBAD */
#if !defined(UNVIS_VALID) && defined(__UNVIS_VALID)
#define UNVIS_VALID     __UNVIS_VALID     /* Output byte produced; consume input byte */
#endif /* !UNVIS_VALID && __UNVIS_VALID */
#if !defined(UNVIS_VALIDPUSH) && defined(__UNVIS_VALIDPUSH)
#define UNVIS_VALIDPUSH __UNVIS_VALIDPUSH /* Output byte produced */
#endif /* !UNVIS_VALIDPUSH && __UNVIS_VALIDPUSH */
#if !defined(UNVIS_NOCHAR) && defined(__UNVIS_NOCHAR)
#define UNVIS_NOCHAR    __UNVIS_NOCHAR    /* Consume input byte */
#endif /* !UNVIS_NOCHAR && __UNVIS_NOCHAR */

/* Extra flags for `unvis(3)' */
#if !defined(UNVIS_END) && defined(__UNVIS_END)
#define UNVIS_END __UNVIS_END /* Special marker for `unvis()' flush and pending character. */
#endif /* !UNVIS_END && __UNVIS_END */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


/* Figure out which parameter-order the caller wants for `strnvis(3)' and `strnunvis(3)' */
#if defined(LIBBSD_OPENBSD_VIS)
#undef LIBBSD_NETBSD_VIS
#elif defined(LIBBSD_NETBSD_VIS)
/*#undef LIBBSD_OPENBSD_VIS*/
#elif defined(__CRT_NETBSD)
#define LIBBSD_NETBSD_VIS
#elif defined(__CRT_OPENBSD)
#define LIBBSD_OPENBSD_VIS
#elif defined(__NetBSD__) || defined(__MacOS__) || defined(__OSX__)
#define LIBBSD_NETBSD_VIS
#elif defined(__KOS__)
#define LIBBSD_NETBSD_VIS /* I personally like NetBSD's argument-order more, so make it the default on KOS */
#elif defined(__OpenBSD__) || defined(__solaris__)
#define LIBBSD_OPENBSD_VIS
#else /* ... */
#define LIBBSD_NETBSD_VIS /*  */
/*[[[warning(warn("
	Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)'
	Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as
	though `LIBBSD_NETBSD_VIS' had been defined)
"))]]]*/
#ifndef __NO_WARNINGS
#ifdef __PREPROCESSOR_HAVE_WARNING
#warning "\
Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)' \
Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as \
though `LIBBSD_NETBSD_VIS' had been defined)"
#elif defined(__PREPROCESSOR_HAVE_PRAGMA_WARNING)
#pragma warning("\
Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)' \
Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as \
though `LIBBSD_NETBSD_VIS' had been defined)")
#endif /* ... */
#endif /* !__NO_WARNINGS */
/*[[[end]]]*/
#endif /* !... */


}

[[requires_function(nvis)]]
char *vis([[nonnull/*out(5)*/]] char *dst,
          int c, int flags, int nextc) {
	return nvis(dst, 5, c, flags, nextc);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(snvis)]]
char *nvis([[out(? <= dstsize)]] char *dst,
           size_t dstsize, int c, int flags, int nextc) {
	return snvis(dst, dstsize, c, flags, nextc, "");
}


[[requires_function(snvis)]]
char *svis([[nonnull/*out(5)*/]] char *dst, int c, int flags,
           int nextc, [[in]] char const *mbextra) {
	return snvis(dst, 5, c, flags, nextc, mbextra);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsnvisx)]]
[[impl_include("<asm/crt/vis.h>")]]
char *snvis([[out(? <= dstsize)]] char *dst, size_t dstsize, int c,
            int flags, int nextc, [[in]] char const *mbextra) {
	int len;
	char src[2];
	src[0] = (char)(unsigned char)(unsigned int)c;
	src[1] = (char)(unsigned char)(unsigned int)nextc;
	flags |= __VIS_SRCEXTRA;
	len = strsnvisx(dst, dstsize, src, 1, flags, mbextra);
	if unlikely(len == -1)
		return NULL;
	return dst + (unsigned int)len;
}


[[requires($has_function(strnvis) || $has_function(strnvis_netbsd))]]
[[impl_include("<hybrid/typecore.h>")]]
int strvis([[nonnull/*out(*)*/]] char *dst, [[in]] char const *src, int flags) {
@@pp_if $has_function(strnvis)@@
	return strnvis(dst, src, (size_t)-1, flags);
@@pp_else@@
	return strnvis_netbsd(dst, (size_t)-1, src, flags);
@@pp_endif@@
}


[[requires_function(malloc, strnvisx)]]
[[impl_include("<hybrid/typecore.h>")]]
int stravis([[out]] char **p_resstr, [[in_opt]] char const *src, int flags) {
	int result;
	char *dst;
	size_t srclen, dstsize;
	if unlikely(!src || *src) {
		if unlikely((*p_resstr = (char *)calloc(1, sizeof(char))) == NULL)
			return -1;
		return 0;
	}
	srclen  = strlen(src);
	dstsize = (srclen * 4) + 1;
	dst     = (char *)malloc(dstsize);
	if unlikely(!dst)
		return -1;
	result = strnvisx(dst, dstsize, src, srclen, flags);
	if unlikely(result == -1) {
@@pp_if $has_function(free)@@
		free(dst);
@@pp_endif@@
		return -1;
	}

	/* Free unused trailing memory. */
@@pp_if $has_function(realloc)@@
	{
		char *trimmed_dst;
		trimmed_dst = (char *)realloc(dst, ((size_t)result + 1) * sizeof(char));
		if likely(trimmed_dst)
			dst = trimmed_dst;
	}
@@pp_endif@@
	*p_resstr = dst;
	return result;
}



%#ifdef LIBBSD_NETBSD_VIS
[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsnvis)]]
[[exposed_name("strnvis")]]
[[if(defined(__CRT_NETBSD)), preferred_alias("strnvis")]]
int strnvis_netbsd([[out(? <= dstsize)]] char *dst, size_t dstsize,
                   char const *src, int flags) {
	return strsnvis(dst, dstsize, src, flags, "");
}

%#else /* LIBBSD_NETBSD_VIS */

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsnvis), no_crt_self_import]]
[[if(!defined(__CRT_NETBSD)), alias("strnvis")]]
int strnvis([[out(? <= dstsize)]] char *dst,
            char const *src, size_t dstsize, int flags) {
	return strsnvis(dst, dstsize, src, flags, "");
}

%#endif /* !LIBBSD_NETBSD_VIS */




[[requires_function(strsnvis)]]
[[impl_include("<hybrid/typecore.h>")]]
int strsvis([[nonnull/*out(return)*/]] char *dst, [[in_opt]] char const *src,
            int flags, [[in]] char const *mbextra) {
	return strsnvis(dst, (size_t)-1, src, flags, mbextra);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsnvisx)]]
int strsnvis([[out(return <= dstsize)]] char *dst, size_t dstsize,
             [[in_opt]] char const *src, int flags, [[in]] char const *mbextra) {
	return strsnvisx(dst, dstsize, src, src ? strlen(src) : 0, flags, mbextra);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strnvisx)]]
[[impl_include("<hybrid/typecore.h>")]]
int strvisx([[nonnull/*out(*)*/]] char *dst,
            [[in(srclen)]] char const *src, size_t srclen, int flags) {
	return strnvisx(dst, (size_t)-1, src, srclen, flags);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strenvisx)]]
int strnvisx([[out(return <= dstsize)]] char *dst, size_t dstsize,
             [[in(srclen)]] char const *src, size_t srclen, int flags) {
	return strenvisx(dst, dstsize, src, srclen, flags, NULL);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsenvisx)]]
int strenvisx([[out(return <= dstsize)]] char *dst, size_t dstsize,
              [[in(srclen)]] char const *src, size_t srclen, int flags,
              [[out_opt]] int *cerr_ptr) {
	return strsenvisx(dst, dstsize, src, srclen, flags, "", cerr_ptr);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsnvisx)]]
[[impl_include("<hybrid/typecore.h>")]]
int strsvisx([[nonnull/*out(*)*/]]char *dst, char const *src,
             size_t srclen, int flags, [[in]] char const *mbextra) {
	return strsnvisx(dst, (size_t)-1, src, srclen, flags, mbextra);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strsenvisx)]]
int strsnvisx([[out(return <= dstsize)]] char *dst, size_t dstsize,
              [[in(srclen)]] char const *src, size_t srclen, int flags,
              [[in]] char const *mbextra) {
	return strsenvisx(dst, dstsize, src, srclen, flags, mbextra, NULL);
}


[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<asm/crt/vis.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
int strsenvisx([[out(return <= dstsize)]] char *dst, size_t dstsize,
               [[in(srclen)]] char const *src, size_t srclen, int flags,
               [[in]] char const *mbextra, [[nullable]] int *cerr_ptr) {
	byte_t *writer, *dstend;
	char const *src_end = src + srclen;
	(void)cerr_ptr; /* Unused in this implementation (something about multi-byte characters?) */
	writer = (byte_t *)dst;
	dstend = (byte_t *)dst + dstsize;
handle_next_byte:
	while (src < src_end) {
		byte_t byte = (byte_t)*src++;
		byte_t next = (src < src_end || (flags & __VIS_SRCEXTRA)) ? *src : 0;
		if (flags & __VIS_HTTPSTYLE) {
			if (isalnum(byte))
				goto encode_byte;
			if (strchr("$-_.+!*'(),", byte))
				goto encode_byte;
			/* Must encode as "%AB" */
			if unlikely((size_t)(dstend - writer) < 3)
				goto err_nospace;
			*writer++ = '%';
			*writer++ = __LOCAL_itoa_digit(false, (byte & 0xf0) >> 4);
			*writer++ = __LOCAL_itoa_digit(false, (byte & 0x0f));
			goto handle_next_byte;
		} else if (flags & __VIS_MIMESTYLE) {
			if (byte == '\n')
				goto encode_byte;
			if (isspace(byte)) {
				/* Only have to escape space if followed by a line-feed */
				if (next != '\r' && next != '\n')
					goto encode_byte;
			} else if (strchr("#$@[\\]^`{|}~=", byte) != NULL) {
				/* Always have to escape these. */
			} else {
				if (byte >= 0x20 && byte <= 0x7e)
					goto encode_byte; /* Normal ASCII doesn't need to be escaped. */
			}
			*writer++ = '=';
			*writer++ = __LOCAL_itoa_digit(true, (byte & 0xf0) >> 4);
			*writer++ = __LOCAL_itoa_digit(true, (byte & 0x0f));
			goto handle_next_byte;
		}

encode_byte:
		if unlikely(writer == dstend)
			goto err_nospace;
		/* Check if `byte' may not need to be escaped. */
		if (isgraph(byte) || strchr("\t\n ", byte) ||
		    ((flags & __VIS_SAFE) && strchr("\x08\x07\r", byte))) {
			if (strchr(mbextra, byte))
				goto escape_byte;
			if ((flags & __VIS_GLOB) && strchr("*?[#", byte))
				goto escape_byte;
			if ((flags & __VIS_SHELL) && strchr("'`\";&<>()|{}]\\$!^~", byte))
				goto escape_byte;
			if ((flags & __VIS_SP) && byte == ' ')
				goto escape_byte;
			if ((flags & __VIS_TAB) && byte == '\t')
				goto escape_byte;
			if ((flags & __VIS_NL) && byte == '\n')
				goto escape_byte;
			if ((flags & __VIS_DQ) && byte == '"')
				goto escape_byte;
			if (!(flags & __VIS_NOSLASH) && byte == '\\')
				goto escape_byte;

			/* Allowed to directly encode `byte' */
			*writer++ = byte;
			goto handle_next_byte;
		}

escape_byte:
		/* Must escape `byte' */
		if (flags & __VIS_CSTYLE) {
			switch (byte) {

			case 0x0a: byte = 'n'; goto escape_bk_byte;
			case 0x0d: byte = 'r'; goto escape_bk_byte;
			case 0x08: byte = 'b'; goto escape_bk_byte;
			case 0x07: byte = 'a'; goto escape_bk_byte;
			case 0x0b: byte = 'v'; goto escape_bk_byte;
			case 0x09: byte = 't'; goto escape_bk_byte;
			case 0x0c: byte = 'f'; goto escape_bk_byte;
			case 0x20: byte = 's'; goto escape_bk_byte;
			case 0x1b: byte = 'E'; goto escape_bk_byte;
			case 0x00:
				if unlikely((size_t)(dstend - writer) < 2)
					goto err_nospace;
				*writer++ = '\\';
				*writer++ = '0';
				if (next >= '0' && next <= '0') {
					if unlikely((size_t)(dstend - writer) < 2)
						goto err_nospace;
					*writer++ = '0';
					*writer++ = '0';
				}
				goto handle_next_byte;

			case 'E': case 'e': case 'n': case 'r':
			case 'b': case 'a': case 'v': case 't':
			case 'f': case 's': case '0': case '1':
			case '2': case '3': case '4': case '5':
			case '6': case '7': case 'M': case '^':
			case '$':
				/* Can't do normal escaping for these characters. */
				break;

			default:
				if (!isgraph(byte))
					break;
escape_bk_byte:
				if unlikely((size_t)(dstend - writer) < 2)
					goto err_nospace;
				*writer++ = '\\';
				*writer++ = byte;
				goto handle_next_byte;
			}
		}

		/* Escape using the octal representation */
		if ((flags & __VIS_OCTAL) || strchr("\x20\xA0", byte) || strchr(mbextra, byte)) {
			if unlikely((size_t)(dstend - writer) < 4)
				goto err_nospace;
			*writer++ = '\\';
			*writer++ = (byte_t)('0' + ((byte & 0700) >> 6));
			*writer++ = (byte_t)('0' + ((byte & 0070) >> 3));
			*writer++ = (byte_t)('0' + ((byte & 0007)));
			goto handle_next_byte;
		}

		if (!(flags & __VIS_NOSLASH)) {
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = '\\';
		}

		if (byte & 0x80) {
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = 'M';
			byte &= 0x7f;
		}

		if unlikely((size_t)(dstend - writer) < 2)
			goto err_nospace;
		if (iscntrl(byte)) {
			*writer++ = '^';
			if (byte == 0x7f) {
				*writer++ = '?';
			} else {
				*writer++ = '@' + byte;
			}
		} else {
			*writer++ = '-';
			*writer++ = byte;
		}
	}
	if unlikely(writer == dstend)
		goto err_nospace;
	*writer = '\0';
	return (int)(unsigned int)(size_t)(writer - (byte_t *)dst);
err_nospace:
@@pp_ifdef ENOSPC@@
	return __libc_seterrno(ENOSPC);
@@pp_else@@
	return __libc_seterrno(1);
@@pp_endif@@
}


[[requires($has_function(strnunvis) || $has_function(strnunvis_netbsd))]]
[[impl_include("<hybrid/typecore.h>")]]
int strunvis([[nonnull/*out(return)*/]] char *dst, [[in]] char const *src) {
@@pp_if $has_function(strnunvis)@@
	return strnunvis(dst, src, (size_t)-1);
@@pp_else@@
	return strnunvis_netbsd(dst, (size_t)-1, src);
@@pp_endif@@
}



%#ifdef LIBBSD_NETBSD_VIS
[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strnunvisx)]]
[[exposed_name("strnunvis")]]
[[if(defined(__CRT_NETBSD)), preferred_alias("strnunvis")]]
int strnunvis_netbsd([[out(return <= dstsize)]] char *dst,
                     size_t dstsize, [[in]] char const *src) {
	return strnunvisx(dst, dstsize, src, 0);
}

%#else /* LIBBSD_NETBSD_VIS */

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strnunvisx), no_crt_self_import]]
[[if(!defined(__CRT_NETBSD)), alias("strnunvis")]]
int strnunvis([[out(return <= dstsize)]] char *dst,
              [[in]] char const *src, size_t dstsize) {
	return strnunvisx(dst, dstsize, src, 0);
}

%#endif /* !LIBBSD_NETBSD_VIS */


[[requires_function(strnunvisx)]]
[[impl_include("<hybrid/typecore.h>")]]
int strunvisx([[nonnull/*out(return)*/]] char *dst,
              [[in]] char const *src, int flags) {
	return strnunvisx(dst, (size_t)-1, src, flags);
}


[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(unvis)]]
[[impl_include("<asm/crt/vis.h>")]]
[[impl_include("<libc/errno.h>")]]
int strnunvisx([[out(return <= dstsize)]] char *dst, size_t dstsize,
               [[in]] char const *src, int flags) {
	int error, state = 0;
	char inchar, outchar, *writer, *dstend;
	writer = dst;
	dstend    = dst + dstsize;
	while ((inchar = *src++) != '\0') {
		error = unvis(&outchar, (unsigned char)inchar, &state, flags);
		switch (error) {

		case __UNVIS_VALID:
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = outchar;
			break;

		case __UNVIS_VALIDPUSH:
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = outchar;
			continue;

		case __UNVIS_NOCHAR:
			break;

@@pp_ifdef __CRT_KOS@@
		case __UNVIS_SYNBAD:
@@pp_ifdef EINVAL@@
			return __libc_seterrno(EINVAL);
@@pp_else@@
			return __libc_seterrno(1);
@@pp_endif@@
		default:
			__builtin_unreachable();
@@pp_else@@
		default:
@@pp_ifdef EINVAL@@
			return __libc_seterrno(EINVAL);
@@pp_else@@
			return __libc_seterrno(1);
@@pp_endif@@
@@pp_endif@@
		}
	}
	error = unvis(&outchar, (unsigned char)inchar, &state, __UNVIS_END);
	if (error == UNVIS_VALID) {
		if unlikely(writer == dstend)
			goto err_nospace;
		*writer++ = outchar;
	}
	if unlikely(writer == dstend)
		goto err_nospace;
	*writer = '\0';
	return (int)(unsigned int)(size_t)(writer - dst);
err_nospace:
@@pp_ifdef ENOSPC@@
	return __libc_seterrno(ENOSPC);
@@pp_else@@
	return __libc_seterrno(1);
@@pp_endif@@
}


@@>> unvis(3)
@@WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
@@         has to be copied alongside `*p_state' if you wish to state (and later restore) the
@@         state of this function!
@@@param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
@@@return: UNVIS_SYNBAD:    [...]
@@@return: UNVIS_VALID:     [...]
@@@return: UNVIS_VALIDPUSH: [...]
@@@return: UNVIS_NOCHAR:    [...]
[[impl_include("<asm/crt/vis.h>")]]
[[impl_include("<hybrid/__overflow.h>")]]
[[impl_include("<libc/template/hex.h>")]]
int unvis([[nonnull/*out*/]] char *p_outbyte, int inbyte,
          [[inout]] int *p_state, int flags) {
	unsigned int bstate = ((unsigned int)*p_state) & 0xff;
	byte_t ch = (byte_t)(unsigned int)inbyte;
#define UNVIS_BSTATE_INIT   0x00 /* Initial zero-shift state */
#define UNVIS_BSTATE_BK     0x01 /* After '\' */
#define UNVIS_BSTATE_OCT2   0x02 /* After '\1' */
#define UNVIS_BSTATE_OCT3   0x03 /* After '\12' */
#define UNVIS_BSTATE_BKM    0x04 /* After '\M' */
#define UNVIS_BSTATE_BKMD   0x05 /* After '\M-' */
#define UNVIS_BSTATE_BKC    0x06 /* After '\^' (C: Circumflex) */
#define UNVIS_BSTATE_HEXP   0x07 /* After '%' */
#define UNVIS_BSTATE_HEX1   0x08 /* After '\x' */
#define UNVIS_BSTATE_HEX2   0x09 /* After '\xA' or '%A' */
#define UNVIS_BSTATE_EQ     0x0a /* After '=' */
#define UNVIS_BSTATE_EQX    0x0b /* After '=A' */
#define UNVIS_BSTATE_EQLF   0x0c /* After '=[CR|LF]' */
#define UNVIS_BSTATE_AMP    0x0d /* After '&' */
#define UNVIS_BSTATE_AMPP   0x0e /* After '&#' */
#define UNVIS_BSTATE_AMPPX  0x0f /* After '&#x' */
#define UNVIS_BSTATE_AMPPXX 0x10 /* After '&#x<0-9a-fA-F>' */
#define UNVIS_BSTATE_AMPPD  0x11 /* After '&#<0-9>' */
#define UNVIS_BSTATE_AMPN   0x12 /* After '&foo' */

	/* Check for the special end-marker flag. */
	if (flags & __UNVIS_END) {
		switch (bstate) {

		case UNVIS_BSTATE_OCT2:
		case UNVIS_BSTATE_OCT3:
		case UNVIS_BSTATE_HEX2:
			/* NOTE: Technically, `UNVIS_VALIDPUSH' would have made more
			 *       sense here (since we're not "consuming" the end  of
			 *       the input string), but better not change the abi... */
			goto done_valid_and_reset; /* goto done_valid_noconsume_and_reset; */

		case UNVIS_BSTATE_INIT:
done_nochar:
			return __UNVIS_NOCHAR;
		default:
			goto err_synbad;
		}
	}

	switch (__builtin_expect(bstate, UNVIS_BSTATE_INIT)) {

	case UNVIS_BSTATE_INIT:
		/* Check for escape sequence start characters. */
		switch (ch) {

		case '\\':
			if (!(flags & __VIS_NOESCAPE)) {
				*p_state = UNVIS_BSTATE_BK;
				goto done_nochar;
			}
			break;

		case '%':
			if (flags & __VIS_HTTPSTYLE) {
				*p_outbyte = 0x00;
				*p_state = UNVIS_BSTATE_HEXP;
				goto done_nochar;
			}
			break;

		case '=':
			if (flags & __VIS_MIMESTYLE) {
				*p_state = UNVIS_BSTATE_EQ;
				goto done_nochar;
			}
			break;

		case '&':
			if (flags & __VIS_HTTP1866) {
				*p_state = UNVIS_BSTATE_AMP;
				goto done_nochar;
			}
			break;

		default:
			break;
		}
		break;

	case UNVIS_BSTATE_BK:
		switch (ch) {

		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*p_outbyte = (char)(unsigned char)(ch - '0');
			*p_state   = UNVIS_BSTATE_OCT2;
			goto done_nochar;

		case 'M':
			*p_outbyte = 0x80;
			*p_state   = UNVIS_BSTATE_BKM;
			goto done_nochar;
		case '^':
			*p_outbyte = 0x00;
			*p_state   = UNVIS_BSTATE_BKC;
			goto done_nochar;
		case 'x':
			*p_outbyte = 0x00;
			*p_state   = UNVIS_BSTATE_HEX1;
			goto done_nochar;
		case 'n': ch = 0x0a; goto reset_and_return_ch;
		case 'r': ch = 0x0d; goto reset_and_return_ch;
		case 'b': ch = 0x08; goto reset_and_return_ch;
		case 'a': ch = 0x07; goto reset_and_return_ch;
		case 'v': ch = 0x0b; goto reset_and_return_ch;
		case 't': ch = 0x09; goto reset_and_return_ch;
		case 'f': ch = 0x0c; goto reset_and_return_ch;
		case 's': ch = 0x20; goto reset_and_return_ch; /* BSD-extension */
		case 'e': /* KOS-extension */
		case 'E': ch = 0x1b; goto reset_and_return_ch; /* BSD-extension */
		case '$':
		case '\n': *p_state = UNVIS_BSTATE_INIT; goto done_nochar;

		default:
			if (!isgraph(ch))
				goto err_synbad;
			/* Fallthru to re-return `ch' */
reset_and_return_ch:
			*p_state = UNVIS_BSTATE_INIT;
		}
		break;

	case UNVIS_BSTATE_OCT2:
	case UNVIS_BSTATE_OCT3:
		if (ch >= '0' && ch <= '7') {
			*p_outbyte <<= 3;
			*p_outbyte |= (char)(unsigned char)(ch - '0');
			if (*p_state == UNVIS_BSTATE_OCT3)
				goto done_valid_and_reset;
			*p_state = UNVIS_BSTATE_OCT3;
			goto done_nochar;
		}
done_valid_noconsume_and_reset:
		*p_state = UNVIS_BSTATE_INIT;
		return __UNVIS_VALIDPUSH;

	case UNVIS_BSTATE_BKM:
		if (ch == '-') {
			*p_state = UNVIS_BSTATE_BKMD;
			goto done_nochar;
		}
		if (ch == '^') {
			*p_state = UNVIS_BSTATE_BKC;
			goto done_nochar;
		}
		goto err_synbad;

	case UNVIS_BSTATE_BKMD:
		*p_outbyte |= (char)ch;
done_valid_and_reset:
		*p_state = UNVIS_BSTATE_INIT;
/*done_valid:*/
		return __UNVIS_VALID;

	case UNVIS_BSTATE_BKC:
		if (ch == '?') {
			*p_outbyte |= 0x7f;
		} else {
			*p_outbyte |= (char)(ch & 0x1f);
		}
		goto done_valid_and_reset;

	case UNVIS_BSTATE_HEX1:
		if (!isxdigit(ch))
			goto err_synbad;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_HEXP:
	case UNVIS_BSTATE_HEX2: {
		byte_t nibble;
		if (!__libc_hex2int(ch, &nibble))
			goto done_valid_noconsume_and_reset;
		*p_outbyte <<= 4;
		*p_outbyte |= (char)nibble;
		if (*p_state == UNVIS_BSTATE_HEX2)
			goto done_valid_and_reset;
		*p_state = UNVIS_BSTATE_HEX2;
		goto done_nochar;
	}

	case UNVIS_BSTATE_EQ:
		if (ch == '\r' || ch == '\n') {
			*p_state = UNVIS_BSTATE_EQLF;
			goto done_nochar;
		}
		if (isdigit(ch)) {
			*p_outbyte = (char)(byte_t)(ch - '0') << 4;
			*p_state   = UNVIS_BSTATE_EQX;
			goto done_nochar;
		}
		if (ch >= 'A' && ch <= 'F') {
			*p_outbyte = (char)(byte_t)(10 + ch - 'A') << 4;
			*p_state   = UNVIS_BSTATE_EQX;
			goto done_nochar;
		}
		goto err_synbad;

	case UNVIS_BSTATE_EQX:
		if (isdigit(ch)) {
			*p_outbyte |= (char)(byte_t)(ch - '0');
			goto done_valid_and_reset;
		}
		if (ch >= 'A' && ch <= 'F') {
			*p_outbyte |= (char)(byte_t)(10 + ch - 'A');
			goto done_valid_and_reset;
		}
		goto err_synbad;

	case UNVIS_BSTATE_EQLF:
		if (ch == '\r' || ch == '\n')
			goto done_nochar;
		if (ch == '=') {
			*p_state = UNVIS_BSTATE_EQ;
			goto done_nochar;
		}
		goto reset_and_return_ch;

	case UNVIS_BSTATE_AMP:
		*p_outbyte = (char)0;
		if (ch == '#') {
			*p_state = UNVIS_BSTATE_AMPP;
			goto done_nochar;
		}
		*p_state = UNVIS_BSTATE_AMPN;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_AMPN: {
		/* We only support names for ASCII characters (because we want to remain  codec-neutral)
		 * Note also that KOS's libiconv contains a full database of XML characters, though that
		 * one would already be too large for us to use here. */
		struct xml_ent {
			char   xe_name[7]; /* Entity name */
			byte_t xe_byte;    /* Entity byte */
		};
		static struct xml_ent const xml_entities[] = {
			/* NOTE: This table must be sorted ascendingly by `xe_name' */
			{ "Hat", /*    */ 0x5e },
			{ { 'N', 'e', 'w', 'L', 'i', 'n', 'e' }, /**/ 0x0a },
			{ "Tab", /*    */ 0x09 },
			{ "amp", /*    */ 0x26 },
			{ "apos", /*   */ 0x27 },
			{ "ast", /*    */ 0x2a },
			{ "bne", /*    */ 0x3d },
			{ "bsol", /*   */ 0x5c },
			{ "colon", /*  */ 0x3a },
			{ "comma", /*  */ 0x2c },
			{ "commat", /* */ 0x40 },
			{ "dollar", /* */ 0x24 },
			{ "excl", /*   */ 0x21 },
			{ "fjlig", /*  */ 0x66 },
			{ "grave", /*  */ 0x60 },
			{ "gt", /*     */ 0x3e },
			{ "lcub", /*   */ 0x7b },
			{ "lowbar", /* */ 0x5f },
			{ "lpar", /*   */ 0x28 },
			{ "lsqb", /*   */ 0x5b },
			{ "lt", /*     */ 0x3c },
			{ "num", /*    */ 0x23 },
			{ "percnt", /* */ 0x25 },
			{ "period", /* */ 0x2e },
			{ "plus", /*   */ 0x2b },
			{ "quest", /*  */ 0x3f },
			{ "quot", /*   */ 0x22 },
			{ "rcub", /*   */ 0x7d },
			{ "rpar", /*   */ 0x29 },
			{ "rsqb", /*   */ 0x5d },
			{ "semi", /*   */ 0x3b },
			{ "sol", /*    */ 0x2f },
			{ "vert", /*   */ 0x7c },
		};
		byte_t pos = (byte_t)*p_outbyte;
		byte_t len = ((unsigned int)*p_state) >> 8;
		if unlikely(len >= lengthof(xml_entities[0].xe_name))
			goto err_synbad;
		if unlikely(pos >= lengthof(xml_entities))
			goto err_synbad;
		if unlikely(ch == '\0')
			goto err_synbad;
		if (ch == ';')
			ch = '\0';
		for (;;) {
			if (xml_entities[pos].xe_name[len] == (char)ch)
				break; /* Found it! */
			++pos;
			if unlikely(pos >= lengthof(xml_entities))
				goto err_synbad; /* No such name. */
			if (bcmp(xml_entities[pos - 1].xe_name,
			         xml_entities[pos - 0].xe_name,
			         sizeof(xml_entities[0].xe_name)) != 0)
				goto err_synbad; /* Prefix changed */
		}
		++len;
		if (ch == '\0') {
			/* Found entity! */
			ch = xml_entities[pos].xe_byte;
			goto reset_and_return_ch;
		}

		/* Write back the updated database cursor. */
		*p_outbyte = (char)pos;
		*p_state   = ((unsigned int)len << 8) | UNVIS_BSTATE_AMPN;
	}	goto done_nochar;

	case UNVIS_BSTATE_AMPP:
		if (ch == 'x') {
			*p_state = UNVIS_BSTATE_AMPPX;
			goto done_nochar;
		}
		if (!isdigit(ch))
			goto err_synbad;
		*p_state = UNVIS_BSTATE_AMPPD;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_AMPPD:
		if (ch == ';')
			goto done_valid_and_reset;
		if (!isdigit(ch))
			goto err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*p_outbyte, 10, (unsigned char *)p_outbyte))
			goto err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*p_outbyte, (unsigned char)(ch - '0'), (unsigned char *)p_outbyte))
			goto err_synbad;
		goto done_nochar;
	case UNVIS_BSTATE_AMPPX:
		if (!__libc_hex2int(ch, p_outbyte))
			goto err_synbad;
		*p_state = UNVIS_BSTATE_AMPPXX;
		goto done_nochar;
	case UNVIS_BSTATE_AMPPXX: {
		byte_t nibble;
		if (ch == ';')
			goto done_valid_and_reset;
		if (!__libc_hex2int(ch, &nibble))
			goto err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*p_outbyte, 16, (unsigned char *)p_outbyte))
			goto err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*p_outbyte, nibble, (unsigned char *)p_outbyte))
			goto err_synbad;
	}	goto done_nochar;

	default:
err_synbad:
		*p_state = UNVIS_BSTATE_INIT;
		return __UNVIS_SYNBAD;
	}
	*p_outbyte = (char)ch;
	return __UNVIS_VALID;
#undef UNVIS_BSTATE_INIT
#undef UNVIS_BSTATE_BK
#undef UNVIS_BSTATE_OCT2
#undef UNVIS_BSTATE_OCT3
#undef UNVIS_BSTATE_BKM
#undef UNVIS_BSTATE_BKMD
#undef UNVIS_BSTATE_BKC
#undef UNVIS_BSTATE_HEXP
#undef UNVIS_BSTATE_HEX1
#undef UNVIS_BSTATE_HEX2
#undef UNVIS_BSTATE_EQ
#undef UNVIS_BSTATE_EQX
#undef UNVIS_BSTATE_EQLF
#undef UNVIS_BSTATE_AMP
#undef UNVIS_BSTATE_AMPP
#undef UNVIS_BSTATE_AMPPX
#undef UNVIS_BSTATE_AMPPXX
#undef UNVIS_BSTATE_AMPPD
#undef UNVIS_BSTATE_AMPN
}



%{

__SYSDECL_END
#endif /* __CC__ */

}
