/* HASH CRC-32:0xabeb458 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_attr_load_actions_defined
#define __local_attr_load_actions_defined
#include <__crt.h>
#include <attr/error_context.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fclose_defined
#define __local___localdep_fclose_defined
#ifdef __CRT_HAVE_fclose
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),_IO_fclose,(__stream))
#else /* ... */
#undef __local___localdep_fclose_defined
#endif /* !... */
#endif /* !__local___localdep_fclose_defined */
#ifndef __local___localdep_fopen_defined
#define __local___localdep_fopen_defined
__NAMESPACE_LOCAL_END
#include <features.h>
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#else /* ... */
#undef __local___localdep_fopen_defined
#endif /* !... */
#endif /* !__local___localdep_fopen_defined */
#ifndef __local___localdep_format_aprintf_pack_defined
#define __local___localdep_format_aprintf_pack_defined
#ifdef __CRT_HAVE_format_aprintf_pack
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char *,__NOTHROW_NCX,__localdep_format_aprintf_pack,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_aprintf_pack,(__self,__pstrlen))
#else /* __CRT_HAVE_format_aprintf_pack */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_pack.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_pack __LIBC_LOCAL_NAME(format_aprintf_pack)
#endif /* !__CRT_HAVE_format_aprintf_pack */
#endif /* !__local___localdep_format_aprintf_pack_defined */
#ifndef __local___localdep_format_aprintf_printer_defined
#define __local___localdep_format_aprintf_printer_defined
#ifdef __CRT_HAVE_format_aprintf_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_aprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_aprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_printer __LIBC_LOCAL_NAME(format_aprintf_printer)
#else /* ... */
#undef __local___localdep_format_aprintf_printer_defined
#endif /* !... */
#endif /* !__local___localdep_format_aprintf_printer_defined */
#ifndef __local___localdep_fparseln_defined
#define __local___localdep_fparseln_defined
#ifdef __CRT_HAVE_fparseln
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),char *,__NOTHROW_CB,__localdep_fparseln,(__FILE *__stream, __SIZE_TYPE__ *__plen, __SIZE_TYPE__ *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),fparseln,(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/util/fparseln.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fparseln __LIBC_LOCAL_NAME(fparseln)
#else /* ... */
#undef __local___localdep_fparseln_defined
#endif /* !... */
#endif /* !__local___localdep_fparseln_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <asm/crt/util.h>
#include <bits/crt/inttypes.h>
#include <attr/asm/libattr.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(attr_load_actions) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INOUT_OPT(1) char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_load_actions))(struct error_context *__ctx) {
	/* Default rules used when `/etc/xattr.conf' is missing or malformed */
	static char const __default_actions[] =
	"system.nfs4_acl\0\2"
	"system.nfs4acl\0\2"
	"system.posix_acl_access\0\2"
	"system.posix_acl_default\0\2"
	"trusted.SGI_ACL_DEFAULT\0\1"
	"trusted.SGI_ACL_FILE\0\1"
	"trusted.SGI_CAP_FILE\0\1"
	"trusted.SGI_DMI_*\0\1"
	"trusted.SGI_MAC_FILE\0\1"
	"xfsroot.*\0\1"
	"user.Beagle.*\0\1"
	"security.evm\0\1"
	"afs.*\0\1";
	(void)__ctx;

	/* Try to parse settings from `/etc/xattr.conf' */
#if ((defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__FPARSELN_UNESCALL)
	static char const __config_filename[] = "/etc/xattr.conf";
	__FILE *__fp = (__NAMESPACE_LOCAL_SYM __localdep_fopen)(__config_filename, "r");
	if (__fp) {
		__SIZE_TYPE__ __lno = 1;
		struct format_aprintf_data __printer;
		__printer.ap_base  = __NULLPTR;
		__printer.ap_avail = 0;
		__printer.ap_used  = 0;
		for (;;) {
			char *__line, *__action;
			__line = (__NAMESPACE_LOCAL_SYM __localdep_fparseln)(__fp, __NULLPTR, &__lno, __NULLPTR, __FPARSELN_UNESCALL);
			if __unlikely(!__line) {
				char const *__config_filename_q = __attr_quote(__ctx, __config_filename);
				__attr_error(__ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: I/O error: %m",
				             __config_filename_q, __lno);
				__attr_quote_free(__ctx, __config_filename_q);
				break;
			}

			/* Check for error */
			if (!*__line) {
				char *__result;
				(__NAMESPACE_LOCAL_SYM __localdep_free)(__line);
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
				(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__fp);
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
				__result = (__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_pack)(&__printer, __NULLPTR);
				if __unlikely(!__result) {
					char const *__config_filename_q = __attr_quote(__ctx, __config_filename);
					__attr_error(__ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             __config_filename_q, __lno);
					__attr_quote_free(__ctx, __config_filename_q);
					goto __return_fallback;
				}
				return __result;
			}

			/* Handle `line', which should be formatted like "<pattern> <action>" */
			__action = __line;
			while (*__action && !(__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__action))
				++__action;
			if (*__action) {
				char *__action_endp;
				*__action++ = '\0';
				__action_endp = __action;
				while (*__action && (__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__action))
					++__action;
#ifdef __ATTR_ACTION_SKIP
				if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__action, "skip") == 0) {
					*__action_endp++ = __ATTR_ACTION_SKIP;
				} else
#endif /* __ATTR_ACTION_SKIP */
#ifdef __ATTR_ACTION_PERMISSIONS
				if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__action, "permissions") == 0) {
					*__action_endp++ = __ATTR_ACTION_PERMISSIONS;
				} else
#endif /* __ATTR_ACTION_PERMISSIONS */
				{
					char const *__config_filename_q = __attr_quote(__ctx, __config_filename);
					char const *__line_q            = __attr_quote(__ctx, __line);
					char const *__action_q          = __attr_quote(__ctx, __action);
					__attr_error(__ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: "
					             "rule %s specifies unknown action %s",
					             __config_filename_q, __lno, __line_q, __action_q);
					__attr_quote_free(__ctx, __action_q);
					__attr_quote_free(__ctx, __line_q);
					__attr_quote_free(__ctx, __config_filename_q);
					goto __next_line;
				}

				/* Print the rule into the result buffer. */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_printer)(&__printer, __line, (__SIZE_TYPE__)(__action_endp - __line)) < 0) {
					char const *__config_filename_q = __attr_quote(__ctx, __config_filename);
					__attr_error(__ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             __config_filename_q, __lno);
					__attr_quote_free(__ctx, __config_filename_q);
					break;
				}
			}
__next_line:
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__line);
		}
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
		(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__fp);
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__printer.ap_base);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	} else {
		char const *__config_filename_q = __attr_quote(__ctx, __config_filename);
		__attr_error(__ctx, "%s: cannot open file: %m", __config_filename_q);
		__attr_quote_free(__ctx, __config_filename_q);
	}
__return_fallback:
#endif /* ((__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __FPARSELN_UNESCALL */

	/* Fallback: return default actions */
	return __default_actions;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_load_actions_defined
#define __local___localdep_attr_load_actions_defined
#define __localdep_attr_load_actions __LIBC_LOCAL_NAME(attr_load_actions)
#endif /* !__local___localdep_attr_load_actions_defined */
#endif /* !__local_attr_load_actions_defined */
