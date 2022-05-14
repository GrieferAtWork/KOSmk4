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
%(c_prefix){
/* (#) Portability: EMX kLIBC (/libc/include/libiberty.h) */
/* (#) Portability: libiberty (/include/libiberty.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <stdio.h>
)]%[insert:prefix(
#include <libc/string.h>
)]%[insert:prefix(
#include <hybrid/__alloca.h>
)]%{

#ifdef __USE_GLIBC
#include <stddef.h>
#include <stdarg.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#define ARRAY_SIZE __COMPILER_LENOF

#define MAX_ALLOCA_SIZE 4032

}

%[declare_user_export("libiberty_optr")]
%[declare_user_export("libiberty_nptr")]
%[declare_user_export("libiberty_len")]
%[declare_user_export("libiberty_concat_ptr")]
%[declare_user_export("_hex_value")]

%(auto_source){
#ifndef __KERNEL__
#include "../libc/globals.h"
#include <sys/stat.h>
#undef libiberty_optr
#undef libiberty_nptr
#undef libiberty_len
#undef libiberty_concat_ptr
INTERN ATTR_SECTION(".bss.crt.libiberty") char const *libc_libiberty_optr      = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") char *libc_libiberty_nptr            = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") __ULONGPTR_TYPE__ libc_libiberty_len = 0;
INTERN ATTR_SECTION(".bss.crt.libiberty") char *libc_libiberty_concat_ptr      = NULL;
DEFINE_PUBLIC_ALIAS(libiberty_optr, libc_libiberty_optr);
DEFINE_PUBLIC_ALIAS(libiberty_nptr, libc_libiberty_nptr);
DEFINE_PUBLIC_ALIAS(libiberty_len, libc_libiberty_len);
DEFINE_PUBLIC_ALIAS(libiberty_concat_ptr, libc_libiberty_concat_ptr);
#define libiberty_concat_ptr GET_NOREL_GLOBAL(libiberty_concat_ptr)

#undef _hex_value
DEFINE_PUBLIC_ALIAS(_hex_value, libc__hex_value);
INTDEF unsigned char const libc__hex_value[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.libiberty")
unsigned char const libc__hex_value[256] =
#include <libc/template/_hex-values.h>
;

#endif /* !__KERNEL__ */
}


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1))]]
[[requires_function(xmalloc), impl_include("<hybrid/host.h>")]]
void *C_alloca(size_t num_bytes) {
@@pp_if $has_function(free)@@
	struct C_alloca_header {
		struct C_alloca_header *cah_prev; /* [0..1] Previous chunk */
		void                   *cah_sp;   /* Stack pointer during allocation */
#if (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__)) != 0
		/* Pad to ensure that user-pointers are properly aligned. */
		__BYTE_TYPE__ cah_ad[__LIBC_MALLOC_ALIGNMENT - (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__))];
#endif /* (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__)) != 0 */
	};

	/* [0..n] Old allocations. */
	static struct C_alloca_header *old = NULL;
	struct C_alloca_header *result;
	void *sp = &num_bytes; /* Stack position probe. */

	/* Reclaim old allocations. */
@@pp_ifdef __ARCH_STACK_GROWS_DOWNWARDS@@
	while (old && old->cah_sp < sp)
@@pp_else@@
	while (old && old->cah_sp > sp)
@@pp_endif@@
	{
		struct C_alloca_header *prev;
		prev = old->cah_prev;
		free(old);
		old = prev;
	}

	/* Special case: C_alloca() must return NULL for 0-byte requests. */
	if (num_bytes == 0)
		return NULL;
	result = (struct C_alloca_header *)xmalloc(sizeof(struct C_alloca_header) + num_bytes);

	/* Remember this allocation */
	result->cah_sp   = sp;
	result->cah_prev = old;
	old = result;

	/* Return a pointer to the user payload. */
	return (result + 1);
@@pp_else@@
	if (num_bytes == 0)
		return NULL;
	return xmalloc(num_bytes);
@@pp_endif@@
}

%#undef C_ALLOCA
%[insert:pp_if(defined(__hybrid_alloca) && !defined(USE_C_ALLOCA))]
%#undef alloca
%#define alloca(num_bytes) __hybrid_alloca(num_bytes)
%[insert:pp_elif($has_function(C_alloca))]
%#undef alloca
%#define alloca(x) C_alloca(x)
%#undef USE_C_ALLOCA
%#define USE_C_ALLOCA 1
%#undef C_ALLOCA
%#define C_ALLOCA 1
%[insert:pp_endif]

%{
#ifdef alloca
#ifdef __NO_XBLOCK
#ifdef __CRT_HAVE_libiberty_optr
__CSDECLARE(,char const *,libiberty_optr)
#define ASTRDUP(str) \
	(libiberty_optr = (str), __libc_strcpy((char *)__hybrid_alloca((__libc_strlen(libiberty_optr) + 1) * sizeof(char)), libiberty_optr))
#else /* __CRT_HAVE_libiberty_optr */
#define ASTRDUP(str) \
	(__libc_strcpy((char *)__hybrid_alloca((__libc_strlen(str) + 1) * sizeof(char)), str))
#endif /* !__CRT_HAVE_libiberty_optr */
#else /* __NO_XBLOCK */
#define ASTRDUP(str)                                                         \
	__XBLOCK({                                                               \
		char const *__orig_s = (str);                                        \
		__size_t __orig_len  = (__libc_strlen(__orig_s) + 1) * sizeof(char); \
		__XRETURN (char *)__libc_memcpy(__hybrid_alloca(__orig_len),         \
		                                __orig_s, __orig_len);               \
	})
#endif /* !__NO_XBLOCK */


#ifdef __NO_XBLOCK
#define ASTRDUP(str)                                     \
	(libiberty_optr = (str),                             \
	 libiberty_len  = __libc_strlen(libiberty_optr) + 1, \
	 libiberty_nptr = (char *)alloca(libiberty_len),     \
	 (char *)__libc_memcpy(libiberty_nptr, libiberty_optr, libiberty_len))
#else /* __NO_XBLOCK */
#define ASTRDUP(str)                                                                           \
	__XBLOCK({                                                                                 \
		char const *__astrdup_str = (str);                                                     \
		size_t __astrdup_siz      = (__libc_strlen(__astrdup_str) + 1) * sizeof(char);         \
		__XRETURN((char *)__libc_memcpy(alloca(__astrdup_siz), __astrdup_str, __astrdup_siz)); \
	})
#endif /* !__NO_XBLOCK */
#endif /* alloca */
}


%[insert:extern(asprintf)]
%[insert:extern(vasprintf)]
%[insert:extern(snprintf)]
%[insert:extern(vsnprintf)]
%[insert:extern(strverscmp)]
%[insert:extern(basename)]
%[insert:extern(ffs)]
%[insert:extern(strtosigno)]
%[insert:extern(strnlen)]
%[insert:extern(strtol)]
%[insert:extern(strtoul)]
%#ifdef __LONGLONG
%[insert:extern(strtoll)]
%[insert:extern(strtoull)]
%#endif /* __LONGLONG */
%[insert:extern(setproctitle)]

%[insert:function(xstrerror = strerror)]
%[insert:function(strerrno = strerrorname_np)]
%[insert:function(strsigno = sigabbrev_np)]
%[insert:function(xatexit = atexit)]
%[insert:function(xexit = exit)]

[[pure, wunused, nonnull]]
char const *lbasename([[nonnull]] char const *filename) = basename;


[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<asm/os/resource.h>")]]
[[impl_include("<bits/os/rlimit.h>")]]
void stack_limit_increase($ulongptr_t newlim) {
	COMPILER_IMPURE();
	(void)newlim;
@@pp_if $has_function(getrlimit, setrlimit) defined(__RLIMIT_STACK)@@
	{
		struct rlimit rl;
		if (getrlimit((__rlimit_resource_t)__RLIMIT_STACK, &rl) == 0 &&
		    (rl.@rlim_cur@ != __RLIM_INFINITY && rl.@rlim_cur@ < newlim) &&
		    (rl.@rlim_max@ == __RLIM_INFINITY || rl.@rlim_cur@ < rl.@rlim_max@)) {
			rl.@rlim_cur@ = newlim;
			if (rl.@rlim_max@ != __RLIM_INFINITY && rl.@rlim_cur@ > rl.@rlim_max@)
				rl.@rlim_cur@ = rl.@rlim_max@;
			setrlimit((__rlimit_resource_t)__RLIMIT_STACK, &rl);
		}
	}
@@pp_endif@@
}





[[pure, wunused, nonnull]]
[[if(defined(_WIN32)), alias("basename", "__basename", "lbasename")]]
[[crt_impl_if(!defined(__KERNEL__) && !defined(_WIN32))]]
char const *dos_lbasename(char const *filename) {
@@pp_ifdef _WIN32@@
	return basename(filename);
@@pp_else@@
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;
	/* Skip drive letter. */
	if (isalpha(iter[0]) && iter[1] == ':')
		iter += 2;
	result = iter;
	for (;;) {
		char ch = *iter++;
		if (ch == '/' || ch == '\\')
			result = iter;
		if (!ch)
			break;
	}
	return result;
@@pp_endif@@
}

[[pure, wunused, nonnull]]
[[if(!defined(_WIN32)), alias("basename", "__basename", "lbasename")]]
[[crt_impl_if(!defined(__KERNEL__) && defined(_WIN32))]]
char const *unix_lbasename(char const *filename) {
@@pp_ifndef _WIN32@@
	return basename(filename);
@@pp_else@@
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;
	result = iter;
	for (;;) {
		char ch = *iter++;
		if (ch == '/')
			result = iter;
		if (!ch)
			break;
	}
	return result;
@@pp_endif@@
}




[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_function(canonicalize_file_name, strdup)]]
char *lrealpath([[nonnull]] char const *path) {
	char *result = canonicalize_file_name(path);
	if (result == NULL)
		result = strdup(path);
	return result;
}


[[wunused]]
[[requires_function(get_current_dir_name)]]
char *getpwd(void) {
	static char *result = NULL;
	if (result == NULL)
		result = get_current_dir_name();
	return result;
}


[[wunused, const]]
[[requires_include("<asm/os/errno.h>")]]
[[requires(defined(__ECOUNT))]]
int errno_max(void) {
	return __ECOUNT - 1;
}

[[wunused, const]]
[[requires_include("<asm/os/signal.h>")]]
[[requires(defined(__NSIG))]]
int signo_max(void) {
	return __NSIG - 1;
}


[[wunused, pure]]
[[requires_function(errno_max, strerrorname_np)]]
$errno_t strtoerrno([[nullable]] char const *name) {
	errno_t result = 0;
	if (name) {
		errno_t max = errno_max();
		for (;; ++result) {
			char const *sysname;
			if (result > max) {
				result = 0;
				break;
			}
			sysname = strerrorname_np(result);
			if (sysname && strcmp(sysname, name) == 0)
				break;
		}
	}
	return result;
}

[[impl_include("<asm/crt/stdio_ext.h>")]]
void unlock_stream(FILE *fp) {
	COMPILER_IMPURE();
	(void)fp;
@@pp_if defined(__FSETLOCKING_BYCALLER) && $has_function(__fsetlocking)@@
	__fsetlocking(fp, __FSETLOCKING_BYCALLER);
@@pp_endif@@
}

[[requires_function(unlock_stream)]]
[[impl_include("<libc/template/stdstreams.h>")]]
void unlock_std_streams(void) {
@@pp_ifdef stdin@@
	unlock_stream(stdin);
@@pp_endif@@
@@pp_ifdef stdout@@
	unlock_stream(stdout);
@@pp_endif@@
@@pp_ifdef stderr@@
	unlock_stream(stderr);
@@pp_endif@@
}

[[requires_function(fopen, unlock_stream)]]
FILE *fopen_unlocked(char const *filename, char const *mode) {
	FILE *result = fopen(filename, mode);
	if (result)
		unlock_stream(result);
	return result;
}

[[requires_function(fdopen, unlock_stream)]]
FILE *fdopen_unlocked($fd_t fd, char const *mode) {
	FILE *result = fdopen(fd, mode);
	if (result)
		unlock_stream(result);
	return result;
}


%[insert:extern(freopen_unlocked)]
/*
[[requires_function(freopen, unlock_stream)]]
FILE *freopen_unlocked(char const *filename, char const *mode, FILE *fp) {
	FILE *result = freopen(filename, mode, fp);
	if (result)
		unlock_stream(result);
	return result;
}*/


[[decl_include("<features.h>")]]
[[wunused, requires_function(realloc)]]
char const *spaces(__STDC_INT_AS_SIZE_T count) {
	static char *buf = NULL;
	static size_t buflen = 0; /* # of space characters in `buf' (followed by NUL) */
	if (buflen < count) {
		char *newbuf = (char *)realloc(buf, (count + 1) * sizeof(char));
		if (!newbuf)
			return NULL;
		memset(newbuf + buflen, ' ', count - buflen);
		buf    = newbuf;
		buflen = count;
	}
	return buf + buflen - count;
}


void xmalloc_set_program_name(char const *progname);

[[noreturn, throws]]
void xmalloc_failed(size_t num_bytes);

[[ignore, nocrt, alias("xmalloc")]]
[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
void *crt_xmalloc(size_t num_bytes);

[[ignore, nocrt, alias("xcalloc")]]
[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
void *crt_xcalloc(size_t elem_count, size_t elem_size);

[[ignore, nocrt, alias("xrealloc")]]
[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
void *crt_xrealloc(void *ptr, size_t num_bytes);


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1))]]
[[requires($has_function(crt_xrealloc) ||
           $has_function(crt_xcalloc) ||
           $has_function(malloc, xmalloc_failed))]]
[[nonnull, impl_include("<asm/crt/malloc.h>")]]
void *xmalloc(size_t num_bytes) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_xrealloc)@@
	return crt_xrealloc(NULL, num_bytes);
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_xcalloc)@@
	return crt_xcalloc(1, num_bytes);
@@pp_else@@
	void *result = malloc(num_bytes);
	if (result == NULL) {
@@pp_ifndef __MALLOC_ZERO_IS_NONNULL@@
		if (num_bytes != 0 || ((result = malloc(1)) == NULL))
@@pp_endif@@
		{
			xmalloc_failed(num_bytes);
		}
	}
	return result;
@@pp_endif@@
}

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
[[nonnull, requires_function(realloc, xmalloc_failed)]]
[[impl_include("<asm/crt/malloc.h>")]]
void *xrealloc(void *ptr, size_t num_bytes) {
	void *result;
@@pp_ifdef __REALLOC_ZERO_IS_NONNULL@@
	result = realloc(ptr, num_bytes);
@@pp_else@@
	result = realloc(ptr, num_bytes ? num_bytes : 1);
@@pp_endif@@
	if (result == NULL)
		xmalloc_failed(num_bytes);
	return result;
}

[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
[[requires($has_function(crt_xmalloc) ||
           $has_function(crt_xrealloc) ||
           $has_function(calloc, xmalloc_failed))]]
[[impl_include("<asm/crt/malloc.h>", "<hybrid/__overflow.h>")]]
void *xcalloc(size_t elem_count, size_t elem_size) {
@@pp_if !defined(__BUILDING_LIBC) && ($has_function(crt_xmalloc) || $has_function(crt_xrealloc))@@
	void *result;
	size_t total;
	if (__hybrid_overflow_umul(elem_count, elem_size, &total))
		total = (size_t)-1;
@@pp_if $has_function(crt_xmalloc)@@
	result = crt_xmalloc(total);
@@pp_else@@
	result = crt_xrealloc(NULL, total);
@@pp_endif@@
	bzero(result, total);
	return result;
@@pp_else@@
	void *result = calloc(elem_count, elem_size);
	if (result == NULL) {
@@pp_ifndef __MALLOC_ZERO_IS_NONNULL@@
		if ((elem_count != 0 && elem_size != 0) || ((result = calloc(1, 1)) == NULL))
@@pp_endif@@
		{
			size_t total;
			if (__hybrid_overflow_umul(elem_count, elem_size, &total))
				total = (size_t)-1;
			xmalloc_failed(total);
		}
	}
	return result;
@@pp_endif@@
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(xmalloc)]]
xstrdup([[nonnull]] char const *__restrict string)
	-> [[nonnull, malloc/*((strlen(string) + 1) * sizeof(char))*/]] char *
{
	size_t copysize = (strlen(string) + 1) * sizeof(char);
	return (char *)memcpy(xmalloc(copysize), string, copysize);
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(xmalloc)]]
xstrndup(char const *string, size_t max_chars)
	-> [[nonnull, malloc/*((strnlen(string, max_chars) + 1) * sizeof(char))*/]] char *
{
	size_t copylen = strnlen(string, max_chars);
	char *result = (char *)xmalloc((copylen + 1) * sizeof(char));
	*(char *)mempcpyc(result, string, copylen, sizeof(char)) = '\0';
	return result;
}

[[decl_include("<hybrid/typecore.h>"), requires_function(xmalloc)]]
xmemdup([[inp(src_bytes)]] void const *src, size_t src_bytes, size_t alloc_size)
	-> [[nonnull, malloc(alloc_size)]] void *
{
	void *result = xmalloc(alloc_size);
	void *ptr = mempcpy(result, src, src_bytes);
	if (alloc_size > src_bytes)
		bzero(ptr, alloc_size - src_bytes);
	return result;
}

[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[doc_alias("strdupf"), requires_function(vstrdupf, xmalloc_failed)]]
char *xvasprintf([[nonnull, format("printf")]] char const *format, $va_list args) {
	va_list args2;
	char *result;
	va_copy(args2, args);
	result = vstrdupf(format, args2);
	va_end(args2);
	if (result == NULL)
		xmalloc_failed((vsnprintf(NULL, 0, format, args) + 1) * sizeof(char));
	return result;
}

[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *xasprintf([[nonnull, format("printf")]] char const *__restrict format, ...)
	%{printf(xvasprintf)}


%[insert:extern(free)]


%[insert:pp_if($has_function(xmalloc))]
%#define XNEW(T)             ((T *)xmalloc(sizeof(T)))
%#define XNEWVEC(T, n)       ((T *)xmalloc(sizeof(T) * (n)))
%#define XNEWVAR(T, s)       ((T *)xmalloc(s))
%[insert:pp_endif]
%[insert:pp_if($has_function(xcalloc))]
%#define XCNEW(T)            ((T *)xcalloc(1, sizeof(T)))
%#define XCNEWVEC(T, n)      ((T *)xcalloc(n, sizeof(T)))
%#define XCNEWVAR(T, s)      ((T *)xcalloc(1, s))
%[insert:pp_endif]
%[insert:pp_if($has_function(xrealloc))]
%#define XRESIZEVEC(T, p, n) ((T *)xrealloc((void *)(p), sizeof(T) * (n)))
%#define XRESIZEVAR(T, p, s) ((T *)xrealloc(p, s))
%[insert:pp_endif]
%[insert:pp_if($has_function(free))]
%#define XDELETE(p)          free((void *)(p))
%#define XDELETEVEC(p)       free((void *)(p))
%[insert:pp_endif]
%#define XOBNEW(self, T)    ((T *)obstack_alloc(self, sizeof(T)))
%#define XOBFINISH(self, T) ((T)obstack_finish(self))



[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_function(xmalloc, xstrdup)]]
[[impl_include("<hybrid/typecore.h>")]]
char **dupargv(char **argv) {
	char **result;
	size_t i, argc;
	if (!argv)
		return NULL;
	for (argc = 0; argv[argc]; ++argc)
		;
	result = (char **)xmalloc((argc + 1) * sizeof(char *));
	for (i = 0; i < argc; ++i)
		result[i] = xstrdup(argv[i]);
	result[argc] = NULL;
	return result;
}

[[requires_function(free)]]
[[impl_include("<hybrid/typecore.h>")]]
void freeargv(char **argv) {
	size_t i;
	if (!argv)
		return;
	for (i = 0; argv[i]; ++i)
		free(argv[i]);
	free(argv);
}

[[pure, wunused]]
__STDC_INT_AS_SIZE_T countargv(char *const *argv) {
	__STDC_INT_AS_SIZE_T result = 0;
	if (argv != NULL) {
		for (; argv[result]; ++result)
			;
	}
	return result;
}


[[wunused, userimpl]] /* `userimpl' because we want to use `kcmp()' (if available) */
[[requires_function(fstat)]]
[[impl_include("<bits/os/stat.h>")]]
int fdmatch($fd_t fd1, $fd_t fd2) {
	@struct stat@ st1, st2;
	if (fstat(fd1, &st1) == 0 && fstat(fd2, &st2) == 0) {
		return st1.@st_dev@ == st2.@st_dev@ &&
		       st1.@st_ino@ == st2.@st_ino@;
	}
	return 0;
}


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_function(xrealloc)]]
[[impl_include("<hybrid/__assert.h>")]]
char **buildargv(char const *cmdline) {
	char **argv = NULL;
	size_t argc = 0;
	if (!cmdline)
		return NULL;
	while (isspace(*cmdline))
		++cmdline;
	for (;;) {
		char const *flush_start = cmdline;
		char *argcopy_str = NULL;
		size_t argcopy_len = 0;
		int quote = 0; /* 0: foo; 1: "foo"; 2: 'foo' */
		for (;; ++cmdline) {
			char ch = *cmdline;
			size_t flushlen;
			switch (ch) {
			case '\0':
				break;
			case '\'':
				if (quote == 1)
					goto cmdline_advance;
				break;
			case '\"':
				if (quote == 2)
					goto cmdline_advance;
				break;
			case '\\':
				break;
			default:
				if (!isspace(ch)) {
cmdline_advance:
					++cmdline;
					continue;
				}
				if (quote != 0)
					goto cmdline_advance;
				break;
			}

			/* Flush until this position. */
			flushlen    = (size_t)(cmdline - flush_start);
			argcopy_str = (char *)xrealloc(argcopy_str, (argcopy_len + flushlen + 1) * sizeof(char));
			memcpy(argcopy_str + argcopy_len, flush_start, flushlen);
			argcopy_len += flushlen;
			switch (ch) {
			case '\0':
				goto end_of_argument;
			case '\'':
				quote ^= 2;
				flush_start = ++cmdline;
				break;
			case '\"':
				quote ^= 1;
				flush_start = ++cmdline;
				break;
			case '\\':
				++cmdline;
				flush_start = cmdline; /* Start flushing on escaped character. */
				if (*cmdline)
					++cmdline; /* Skip escaped character */
				break;
			default:
				__hybrid_assert(isspace(ch));
				__hybrid_assert(quote == 0);
				++cmdline;
				goto end_of_argument;
			}
			flush_start = cmdline;
		}
end_of_argument:
		argcopy_str[argcopy_len] = '\0';

		/* Append the argument. */
		argv = (char **)xrealloc(argv, (argc + 2) * sizeof(char *));
		argv[argc++] = argcopy_str;

		/* Skip space past the argument. */
		while (isspace(*cmdline))
			++cmdline;
		if (!*cmdline)
			break;
	}
	argv[argc] = NULL; /* Sentinel */
	return argv;
}


@@>> expandargv(3)
@@Expand special `@file' arguments passed on the commandline
[[requires_function(mapfile, xrealloc, xmalloc)]]
[[impl_include("<libc/errno.h>", "<hybrid/__assert.h>")]]
[[impl_include("<bits/crt/mapfile.h>")]]
void expandargv([[nonnull]] int *p_argc, [[nonnull]] char ***p_argv) {
	size_t i, argc = (size_t)*p_argc;
	char **argv = *p_argv;
	for (i = 0; i < argc; ++i) {
		@struct mapfile@ mf;
		char *arg = argv[i];
		char **inject_argv;
		size_t inject_argc;
		if (arg[0] != '@')
			continue;
		++arg;

		/* Map  the specified file  into memory. -  If doing so fails,
		 * (due to something other than out-of-memory), then we simply
		 * ignore the @-directive. */
		if (mapfile(&mf, arg, 0, (size_t)-1, 1) != 0) {
@@pp_if defined(libc_geterrno) && $has_function(xmalloc_failed)@@
			if (libc_geterrno() == ENOMEM)
				xmalloc_failed(1);
@@pp_endif@@
			continue;
		}

		/* Build an argument vector from the file.
		 * Note the forced trailing NUL-byte we requested for the mapping! */
		inject_argv = buildargv((char *)mf.@mf_addr@);
@@pp_if $has_function(unmapfile)@@
		unmapfile(&mf);
@@pp_endif@@

		/* Count the # of injected arguments. */
		__hybrid_assert(inject_argv);
		for (inject_argc = 0; inject_argv[inject_argc]; ++inject_argc)
			;

		/* Resize the argument vector. */
		if (argv == *p_argv) {
			size_t size;
			size = (argc + inject_argc + 1) * sizeof(char *);
			argv = (char **)memcpy(xmalloc(size), argv, size - sizeof(char *));
			argv[argc] = NULL; /* Sentinel */
		} else {
			argv = (char **)xrealloc(argv, (argc + inject_argc + 1) * sizeof(char *));
		}
		/* Inject arguments */
		memmoveupc(argv + i + inject_argc,
		           argv + i,
		           argc - i, sizeof(char *));
		memcpyc(argv + i, inject_argv, inject_argc, sizeof(char *));
@@pp_if $has_function(free)@@
		free(inject_argv);
@@pp_endif@@
		argc += inject_argc;
		i += inject_argc;
	}
	*p_argc = (int)(unsigned int)argc;
	*p_argv = argv;
}


@@@return: 0 : Success
@@@return: 1 : Error
[[requires_function(fputc), impl_include("<asm/crt/stdio.h>")]]
int writeargv([[nonnull]] char *const *argv, FILE *fp) {
	if unlikely(!fp)
		goto err;
	for (; *argv; ++argv) {
		char const *arg = *argv;
		for (; *arg; ++arg) {
			char ch = *arg;
			if (isspace(ch) || strchr("\'\"\\", ch)) {
				if (fputc('\\', fp) == EOF)
					goto err;
			}
			if (fputc(ch, fp) == EOF)
				goto err;
		}
		if (fputc('\n', fp) == EOF)
			goto err;
	}
	return 0;
err:
	return 1;
}

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[nonnull, static, requires_function(xmalloc)]]
[[impl_include("<hybrid/typecore.h>")]]
char *vconcat(char const *first, va_list args) {
	char *result, *ptr;
	size_t totlen = 0;
	va_list copy;
	va_copy(copy, args);
	for (ptr = (char *)first; ptr; ptr = va_arg(copy, char *))
		totlen += strlen(ptr);
	va_end(copy);
	ptr = result = (char *)xmalloc((totlen + 1) * sizeof(char));
	for (; first; first = va_arg(copy, char *))
		ptr = (char *)mempcpyc(ptr, first, strlen(first), sizeof(char));
	*ptr = '\0';
	return result;
}


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_SENTINEL]]
[[nonnull, requires_function(vconcat)]]
char *concat([[nullable]] char const *first, ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = vconcat(first, args);
	va_end(args);
	return result;
}

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_SENTINEL]]
[[nonnull, requires_function(vconcat)]]
char *reconcat([[nullable]] char *old_ptr, char const *first, ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = vconcat(first, args);
	va_end(args);
@@pp_if $has_function(free)@@
	free(old_ptr);
@@pp_endif@@
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
$ulongptr_t concat_length(char const *first, ...) {
	va_list args;
	size_t totlen = 0;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		totlen += strlen(first);
	va_end(args);
	return (ulongptr_t)totlen;
}

[[static, nonnull]]
char *concat_vcopy([[nonnull]] char *dst, char const *first, va_list args) {
	char *ptr = dst;
	for (; first; first = va_arg(args, char *))
		ptr = (char *)mempcpyc(ptr, first, strlen(first), sizeof(char));
	*ptr = '\0';
	return dst;
}

[[nonnull, requires_function(concat_vcopy)]]
char *concat_copy([[nonnull]] char *dst, char const *first, ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = concat_vcopy(dst, first, args);
	va_end(args);
	return result;
}

%[define_replacement(libiberty_concat_ptr = __LOCAL_libiberty_concat_ptr)]

[[requires_include("<libc/template/libiberty_concat_ptr.h>")]]
[[requires($has_function(concat_copy) && defined(__LOCAL_libiberty_concat_ptr))]]
char *concat_copy2(char const *first, ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = concat_vcopy(libiberty_concat_ptr, first, args);
	va_end(args);
	return result;
}


%{
#ifndef libiberty_concat_ptr
#ifdef __LOCAL_libiberty_concat_ptr
#define libiberty_concat_ptr __LOCAL_libiberty_concat_ptr
#elif defined(__CRT_HAVE_libiberty_concat_ptr)
__CSDECLARE(,char *,libiberty_concat_ptr)
#define libiberty_concat_ptr libiberty_concat_ptr
#endif /* __CRT_HAVE_libiberty_concat_ptr */
#endif /* !libiberty_concat_ptr */

}
%[insert:pp_if(defined(alloca) && defined(libiberty_concat_ptr) && $has_function(concat_copy2))]
%{
#define ACONCAT(paren_args)                                               \
	(libiberty_concat_ptr = (char *)alloca(concat_length paren_args + 1), \
	 concat_copy2 paren_args)
}
%[insert:pp_endif]

@@>> get_run_time(3)
@@Return the amount of time the calling process has run (in  microseconds)
@@If possible, time spent idling isn't counted, though if not possible, it
@@is included, also.
[[wunused]]
[[requires_include("<asm/os/resource.h>", "<asm/crt/confname.h>")]]
[[requires_include("<asm/os/clock.h>", "<bits/crt/vtimes.h>")]]
[[requires((defined(__RUSAGE_SELF) && $has_function(getrusage64)) ||
           (defined(_SC_CLK_TCK) && $has_function(sysconf, times)) ||
           (defined(__VTIMES_UNITS_PER_SECOND) && $has_function(vtimes)) ||
           (defined(__CLOCKS_PER_SEC) && $has_function(clock)))]]
[[impl_include("<asm/os/resource.h>", "<bits/os/rusage.h>")]]
[[impl_include("<asm/crt/confname.h>", "<bits/os/tms.h>")]]
[[impl_include("<bits/crt/vtimes.h>")]]
long get_run_time(void) {
	uint64_t result;
@@pp_if defined(__RUSAGE_SELF) && $has_function(getrusage64)@@
	struct rusage64 ru;
	getrusage64(RUSAGE_SELF, &ru);
	result  = ((uint64_t)ru.@ru_utime@.@tv_sec@ * 1000000) + ru.@ru_utime@.@tv_usec@;
	result += ((uint64_t)ru.@ru_stime@.@tv_sec@ * 1000000) + ru.@ru_stime@.@tv_usec@;
@@pp_elif defined(times)@@
	struct tms ts;
	times(&ts);
	result = ts.@tms_utime@ + ts.@tms_stime@;
	result *= 1000000;
	result /= sysconf(_SC_CLK_TCK);
@@pp_elif defined(__VTIMES_UNITS_PER_SECOND) && $has_function(vtimes)@@
	struct vtimes vt;
	vtimes(&vt, NULL);
	result = vt->@vm_utime@ + vt->@vm_stime@;
	result *= 1000000;
	result /= __VTIMES_UNITS_PER_SECOND;
@@pp_else@@
	result = clock();
	result *= 1000000;
	result /= __CLOCKS_PER_SEC;
@@pp_endif@@
	return (long)result;
}

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_relative_prefix(char const *a, char const *b, char const *c); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_relative_prefix_ignore_links(char const *a, char const *b, char const *c); /* TODO */


@@>> choose_temp_base(3)
@@Create a temporary filename in `choose_tmpdir(3)' by use of `mktemp(3)'
@@The  returned string must always be freed,  and if no filename could be
@@generated, an empty string is returned.
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_function(choose_tmpdir, xmalloc, mktemp)]]
char *choose_temp_base(void) {
	char const *tmpdir = choose_tmpdir();
	size_t tmpdir_len = strlen(tmpdir);
	char *result = (char *)xmalloc((tmpdir_len + 6 + 1) * sizeof(char));
	memcpyc(mempcpyc(result, tmpdir, tmpdir_len, sizeof(char)),
	        "XXXXXX", 7, sizeof(char));
	return mktemp(result);
}

@@>> choose_tmpdir(3)
@@Return the path to a suitable temp directory.
@@The returned path is guarantied to be non-NULL, and include a trailing slash.
[[wunused, nonnull, pure]]
[[requires($has_function(access, xmalloc) && !defined(_WIN32) &&
           defined(__X_OK) && defined(__W_OK) && defined(__R_OK))]]
char const *choose_tmpdir(void) {
	static char const *result = NULL;
	if (result == NULL) {
		char const *path;
		size_t pathlen;
		char *pathcopy, *ptr;
		size_t i;
@@pp_ifdef __KOS__@@
		static char const defdir_names[][10] = { "/tmp", "/var/tmp", "/usr/tmp" };
@@pp_else@@
		static char const defdir_names[][10] = { "/var/tmp", "/usr/tmp", "/tmp" };
@@pp_endif@@
@@pp_if $has_function(getenv)@@
		static char const envvar_names[][8] = { "TMPDIR", "TMP", "TEMP" };
		for (i = 0; i < COMPILER_LENOF(envvar_names); ++i) {
			path = getenv(envvar_names[i]);
			if (path && access(path, __X_OK | __W_OK | __R_OK) == 0)
				goto got_tmppath;
		}
@@pp_endif@@
		for (i = 0; i < COMPILER_LENOF(defdir_names); ++i) {
			path = defdir_names[i];
			if (access(path, __X_OK | __W_OK | __R_OK) == 0)
				goto got_tmppath;
		}

		/* Fallback: use the current directory. */
		path = ".";
got_tmppath:

		pathlen = strlen(path);
@@pp_ifdef _WIN32@@
		while (pathlen && (path[pathlen - 1] == '/' || path[pathlen - 1] == '\\'))
			--pathlen;
@@pp_else@@
		while (pathlen && path[pathlen - 1] == '/')
			--pathlen;
@@pp_endif@@

		/* Force-append a trailing slash. */
		pathcopy = (char *)xmalloc((pathlen + 2) * sizeof(char));
		ptr = (char *)mempcpyc(pathcopy, path, pathlen, sizeof(char));
@@pp_ifdef _WIN32@@
		*ptr++ = '\\';
@@pp_else@@
		*ptr++ = '/';
@@pp_endif@@
		*ptr++ = '\0';
		result = pathcopy;
	}
	return result;
}

[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires($has_function(choose_tmpdir, xmalloc, mkstemps, open, fprintf, abort) &&
           defined(__LOCAL_stderr))]]
[[impl_include("<parts/printf-config.h>", "<libc/errno.h>")]]
char *make_temp_file_with_prefix([[nullable]] char const *prefix,
                                 [[nullable]] char const *suffix) {
	fd_t tempfd;
	char *result, *p;
	const char *tmpdir = choose_tmpdir();
	size_t tmpdir_len, prefix_len, suffix_len;
	if (prefix == NULL)
		prefix = "cc";
	if (suffix == NULL)
		suffix = "";
	tmpdir_len = strlen(tmpdir);
	prefix_len = strlen(prefix);
	suffix_len = strlen(suffix);

	/* Construct the full filename. */
	result = (char *)xmalloc((tmpdir_len +
	                          prefix_len + 6 +
	                          suffix_len + 1) *
	                         sizeof(char));
	p = (char *)mempcpyc(result, tmpdir, tmpdir_len, sizeof(char));
	p = (char *)mempcpyc(p, prefix, prefix_len, sizeof(char));
	p = (char *)mempcpyc(p, "XXXXXX", 6, sizeof(char));
	p = (char *)mempcpyc(p, suffix, suffix_len, sizeof(char));
	*p = '\0';
	tempfd = mkstemps(result, suffix_len);
	if (tempfd < 0) {
@@pp_ifdef __NO_PRINTF_STRERROR@@
		fprintf(stderr, "Cannot create temporary file in %s: %s\n",
		        tmpdir, strerror(__libc_geterrno_or(1)));
@@pp_else@@
		fprintf(stderr, "Cannot create temporary file in %s: %m\n", tmpdir);
@@pp_endif@@
		abort();
	}

@@pp_if $has_function(close)@@
	close(tempfd);
@@pp_endif@@
	return result;
}

[[nonnull, wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[requires_function(make_temp_file_with_prefix)]]
char *make_temp_file([[nullable]] char const *suffix) {
	return make_temp_file_with_prefix(NULL, suffix);
}

@@>> unlink_if_ordinary(3)
@@Delete a file, but only if it's S_ISREG or S_ISLNK
@@@return:  0: File was deleted
@@@return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
@@@return: -1: Unlink failed (s.a. `errno')
[[impl_include("<bits/os/stat.h>")]]
[[impl_include("<asm/os/stat.h>")]]
[[requires_function(lstat, unlink)]]
int unlink_if_ordinary(char const *filename) {
	@struct stat@ st;
	if (lstat(filename, &st) != 0)
		return 1;
	if (!__S_ISREG(st.@st_mode@) && !__S_ISLNK(st.@st_mode@))
		return 1;
	/* Sorry, no way  to prevent  the race  where
	 * the file is replaced before we get here... */
	return unlink(filename);
}

[[wunused, const, requires_include("<asm/crt/confname.h>")]]
[[requires($has_function(getpagesize, sysconf) && defined(_SC_PHYS_PAGES))]]
double physmem_total(void) {
	size_t pages    = sysconf(_SC_PHYS_PAGES);
	size_t pagesize = getpagesize();
	return (double)pages * (double)pagesize;
}

[[wunused, pure, requires_include("<asm/crt/confname.h>")]]
[[requires($has_function(getpagesize, sysconf) && defined(_SC_AVPHYS_PAGES))]]
double physmem_available(void) {
	size_t pages    = sysconf(_SC_AVPHYS_PAGES);
	size_t pagesize = getpagesize();
	return (double)pages * (double)pagesize;
}

[[wunused, pure, decl_include("<hybrid/typecore.h>")]]
__UINT32_TYPE__ xcrc32(__BYTE_TYPE__ const *buf, __STDC_INT_AS_SIZE_T len, __UINT32_TYPE__ crc) {
	/* Taken from `libiberty' (which is the  same library also used by  `gdbserver')
	 * Note that even though `libiberty' is the origin of the contents of this file,
	 * heavy  changes  have been  made to  better incorporate  the system  into KOS.
	 * Find the origin of information here:
	 *   https://code.woboq.org/gcc/libiberty/crc32.c.html
	 * And see the (unmodified) copyright notice taken form the start of that file below.
	 */
	/* crc32.c
	   Copyright (C) 2009-2017 Free Software Foundation, Inc.
	   This file is part of the libiberty library.
	   This file is free software; you can redistribute it and/or modify
	   it under the terms of the GNU General Public License as published by
	   the Free Software Foundation; either version 2 of the License, or
	   (at your option) any later version.
	   In addition to the permissions in the GNU General Public License, the
	   Free Software Foundation gives you unlimited permission to link the
	   compiled version of this file into combinations with other programs,
	   and to distribute those combinations without any restriction coming
	   from the use of this file.  (The General Public License restrictions
	   do apply in other respects; for example, they cover modification of
	   the file, and distribution when not linked into a combined
	   executable.)
	   This program is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	   GNU General Public License for more details.
	   You should have received a copy of the GNU General Public License
	   along with this program; if not, write to the Free Software
	   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
	*/
	static u32 const crc32_table[] = {
		__UINT32_C(0x00000000), __UINT32_C(0x04c11db7), __UINT32_C(0x09823b6e), __UINT32_C(0x0d4326d9),
		__UINT32_C(0x130476dc), __UINT32_C(0x17c56b6b), __UINT32_C(0x1a864db2), __UINT32_C(0x1e475005),
		__UINT32_C(0x2608edb8), __UINT32_C(0x22c9f00f), __UINT32_C(0x2f8ad6d6), __UINT32_C(0x2b4bcb61),
		__UINT32_C(0x350c9b64), __UINT32_C(0x31cd86d3), __UINT32_C(0x3c8ea00a), __UINT32_C(0x384fbdbd),
		__UINT32_C(0x4c11db70), __UINT32_C(0x48d0c6c7), __UINT32_C(0x4593e01e), __UINT32_C(0x4152fda9),
		__UINT32_C(0x5f15adac), __UINT32_C(0x5bd4b01b), __UINT32_C(0x569796c2), __UINT32_C(0x52568b75),
		__UINT32_C(0x6a1936c8), __UINT32_C(0x6ed82b7f), __UINT32_C(0x639b0da6), __UINT32_C(0x675a1011),
		__UINT32_C(0x791d4014), __UINT32_C(0x7ddc5da3), __UINT32_C(0x709f7b7a), __UINT32_C(0x745e66cd),
		__UINT32_C(0x9823b6e0), __UINT32_C(0x9ce2ab57), __UINT32_C(0x91a18d8e), __UINT32_C(0x95609039),
		__UINT32_C(0x8b27c03c), __UINT32_C(0x8fe6dd8b), __UINT32_C(0x82a5fb52), __UINT32_C(0x8664e6e5),
		__UINT32_C(0xbe2b5b58), __UINT32_C(0xbaea46ef), __UINT32_C(0xb7a96036), __UINT32_C(0xb3687d81),
		__UINT32_C(0xad2f2d84), __UINT32_C(0xa9ee3033), __UINT32_C(0xa4ad16ea), __UINT32_C(0xa06c0b5d),
		__UINT32_C(0xd4326d90), __UINT32_C(0xd0f37027), __UINT32_C(0xddb056fe), __UINT32_C(0xd9714b49),
		__UINT32_C(0xc7361b4c), __UINT32_C(0xc3f706fb), __UINT32_C(0xceb42022), __UINT32_C(0xca753d95),
		__UINT32_C(0xf23a8028), __UINT32_C(0xf6fb9d9f), __UINT32_C(0xfbb8bb46), __UINT32_C(0xff79a6f1),
		__UINT32_C(0xe13ef6f4), __UINT32_C(0xe5ffeb43), __UINT32_C(0xe8bccd9a), __UINT32_C(0xec7dd02d),
		__UINT32_C(0x34867077), __UINT32_C(0x30476dc0), __UINT32_C(0x3d044b19), __UINT32_C(0x39c556ae),
		__UINT32_C(0x278206ab), __UINT32_C(0x23431b1c), __UINT32_C(0x2e003dc5), __UINT32_C(0x2ac12072),
		__UINT32_C(0x128e9dcf), __UINT32_C(0x164f8078), __UINT32_C(0x1b0ca6a1), __UINT32_C(0x1fcdbb16),
		__UINT32_C(0x018aeb13), __UINT32_C(0x054bf6a4), __UINT32_C(0x0808d07d), __UINT32_C(0x0cc9cdca),
		__UINT32_C(0x7897ab07), __UINT32_C(0x7c56b6b0), __UINT32_C(0x71159069), __UINT32_C(0x75d48dde),
		__UINT32_C(0x6b93dddb), __UINT32_C(0x6f52c06c), __UINT32_C(0x6211e6b5), __UINT32_C(0x66d0fb02),
		__UINT32_C(0x5e9f46bf), __UINT32_C(0x5a5e5b08), __UINT32_C(0x571d7dd1), __UINT32_C(0x53dc6066),
		__UINT32_C(0x4d9b3063), __UINT32_C(0x495a2dd4), __UINT32_C(0x44190b0d), __UINT32_C(0x40d816ba),
		__UINT32_C(0xaca5c697), __UINT32_C(0xa864db20), __UINT32_C(0xa527fdf9), __UINT32_C(0xa1e6e04e),
		__UINT32_C(0xbfa1b04b), __UINT32_C(0xbb60adfc), __UINT32_C(0xb6238b25), __UINT32_C(0xb2e29692),
		__UINT32_C(0x8aad2b2f), __UINT32_C(0x8e6c3698), __UINT32_C(0x832f1041), __UINT32_C(0x87ee0df6),
		__UINT32_C(0x99a95df3), __UINT32_C(0x9d684044), __UINT32_C(0x902b669d), __UINT32_C(0x94ea7b2a),
		__UINT32_C(0xe0b41de7), __UINT32_C(0xe4750050), __UINT32_C(0xe9362689), __UINT32_C(0xedf73b3e),
		__UINT32_C(0xf3b06b3b), __UINT32_C(0xf771768c), __UINT32_C(0xfa325055), __UINT32_C(0xfef34de2),
		__UINT32_C(0xc6bcf05f), __UINT32_C(0xc27dede8), __UINT32_C(0xcf3ecb31), __UINT32_C(0xcbffd686),
		__UINT32_C(0xd5b88683), __UINT32_C(0xd1799b34), __UINT32_C(0xdc3abded), __UINT32_C(0xd8fba05a),
		__UINT32_C(0x690ce0ee), __UINT32_C(0x6dcdfd59), __UINT32_C(0x608edb80), __UINT32_C(0x644fc637),
		__UINT32_C(0x7a089632), __UINT32_C(0x7ec98b85), __UINT32_C(0x738aad5c), __UINT32_C(0x774bb0eb),
		__UINT32_C(0x4f040d56), __UINT32_C(0x4bc510e1), __UINT32_C(0x46863638), __UINT32_C(0x42472b8f),
		__UINT32_C(0x5c007b8a), __UINT32_C(0x58c1663d), __UINT32_C(0x558240e4), __UINT32_C(0x51435d53),
		__UINT32_C(0x251d3b9e), __UINT32_C(0x21dc2629), __UINT32_C(0x2c9f00f0), __UINT32_C(0x285e1d47),
		__UINT32_C(0x36194d42), __UINT32_C(0x32d850f5), __UINT32_C(0x3f9b762c), __UINT32_C(0x3b5a6b9b),
		__UINT32_C(0x0315d626), __UINT32_C(0x07d4cb91), __UINT32_C(0x0a97ed48), __UINT32_C(0x0e56f0ff),
		__UINT32_C(0x1011a0fa), __UINT32_C(0x14d0bd4d), __UINT32_C(0x19939b94), __UINT32_C(0x1d528623),
		__UINT32_C(0xf12f560e), __UINT32_C(0xf5ee4bb9), __UINT32_C(0xf8ad6d60), __UINT32_C(0xfc6c70d7),
		__UINT32_C(0xe22b20d2), __UINT32_C(0xe6ea3d65), __UINT32_C(0xeba91bbc), __UINT32_C(0xef68060b),
		__UINT32_C(0xd727bbb6), __UINT32_C(0xd3e6a601), __UINT32_C(0xdea580d8), __UINT32_C(0xda649d6f),
		__UINT32_C(0xc423cd6a), __UINT32_C(0xc0e2d0dd), __UINT32_C(0xcda1f604), __UINT32_C(0xc960ebb3),
		__UINT32_C(0xbd3e8d7e), __UINT32_C(0xb9ff90c9), __UINT32_C(0xb4bcb610), __UINT32_C(0xb07daba7),
		__UINT32_C(0xae3afba2), __UINT32_C(0xaafbe615), __UINT32_C(0xa7b8c0cc), __UINT32_C(0xa379dd7b),
		__UINT32_C(0x9b3660c6), __UINT32_C(0x9ff77d71), __UINT32_C(0x92b45ba8), __UINT32_C(0x9675461f),
		__UINT32_C(0x8832161a), __UINT32_C(0x8cf30bad), __UINT32_C(0x81b02d74), __UINT32_C(0x857130c3),
		__UINT32_C(0x5d8a9099), __UINT32_C(0x594b8d2e), __UINT32_C(0x5408abf7), __UINT32_C(0x50c9b640),
		__UINT32_C(0x4e8ee645), __UINT32_C(0x4a4ffbf2), __UINT32_C(0x470cdd2b), __UINT32_C(0x43cdc09c),
		__UINT32_C(0x7b827d21), __UINT32_C(0x7f436096), __UINT32_C(0x7200464f), __UINT32_C(0x76c15bf8),
		__UINT32_C(0x68860bfd), __UINT32_C(0x6c47164a), __UINT32_C(0x61043093), __UINT32_C(0x65c52d24),
		__UINT32_C(0x119b4be9), __UINT32_C(0x155a565e), __UINT32_C(0x18197087), __UINT32_C(0x1cd86d30),
		__UINT32_C(0x029f3d35), __UINT32_C(0x065e2082), __UINT32_C(0x0b1d065b), __UINT32_C(0x0fdc1bec),
		__UINT32_C(0x3793a651), __UINT32_C(0x3352bbe6), __UINT32_C(0x3e119d3f), __UINT32_C(0x3ad08088),
		__UINT32_C(0x2497d08d), __UINT32_C(0x2056cd3a), __UINT32_C(0x2d15ebe3), __UINT32_C(0x29d4f654),
		__UINT32_C(0xc5a92679), __UINT32_C(0xc1683bce), __UINT32_C(0xcc2b1d17), __UINT32_C(0xc8ea00a0),
		__UINT32_C(0xd6ad50a5), __UINT32_C(0xd26c4d12), __UINT32_C(0xdf2f6bcb), __UINT32_C(0xdbee767c),
		__UINT32_C(0xe3a1cbc1), __UINT32_C(0xe760d676), __UINT32_C(0xea23f0af), __UINT32_C(0xeee2ed18),
		__UINT32_C(0xf0a5bd1d), __UINT32_C(0xf464a0aa), __UINT32_C(0xf9278673), __UINT32_C(0xfde69bc4),
		__UINT32_C(0x89b8fd09), __UINT32_C(0x8d79e0be), __UINT32_C(0x803ac667), __UINT32_C(0x84fbdbd0),
		__UINT32_C(0x9abc8bd5), __UINT32_C(0x9e7d9662), __UINT32_C(0x933eb0bb), __UINT32_C(0x97ffad0c),
		__UINT32_C(0xafb010b1), __UINT32_C(0xab710d06), __UINT32_C(0xa6322bdf), __UINT32_C(0xa2f33668),
		__UINT32_C(0xbcb4666d), __UINT32_C(0xb8757bda), __UINT32_C(0xb5365d03), __UINT32_C(0xb1f740b4)
	};

	/*
	@deftypefn Extension {unsigned int} crc32 (const unsigned char *@var{buf}, @
	  int @var{len}, unsigned int @var{init})
	Compute the 32-bit CRC of @var{buf} which has length @var{len}.  The
	starting value is @var{init}; this may be used to compute the CRC of
	data split across multiple buffers by passing the return value of each
	call as the @var{init} parameter of the next.
	This is used by the @command{gdb} remote protocol for the @samp{qCRC}
	command.  In order to get the same results as gdb for a block of data,
	you must pass the first CRC parameter as @code{0xffffffff}.
	This CRC can be specified as:
	  Width  : 32
	  Poly   : 0x04c11db7
	  Init   : parameter, typically 0xffffffff
	  RefIn  : false
	  RefOut : false
	  XorOut : 0
	This differs from the "standard" CRC-32 algorithm in that the values
	are not reflected, and there is no final XOR value.  These differences
	make it easy to compose the values of multiple blocks.
	@end deftypefn
	*/
	while (len--) {
		crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *buf) & 255];
		buf++;
	}
	return crc;
}


%{
#define _hex_array_size 256 /* # of elements in `_hex_value' */
#define _hex_bad        99  /* Returned by `hex_value()' for bad characters */

/* Return integer values of hex character `ch', or `_hex_bad' if invalid. */
#define hex_value(ch) ((unsigned int)_hex_value[(unsigned char)(ch)])

/* Check if `ch' is a valid hex-character. */
#define hex_p(ch) (hex_value(ch) != _hex_bad)

/* >> _hex_value(3)
 * Lookup array for characters -> hex values. */
#ifndef _hex_value
#ifdef __CRT_HAVE__hex_value
__CSDECLARE2(,unsigned char const _hex_value[_hex_array_size],_hex_value)
#define _hex_value _hex_value
#else /* __CRT_HAVE__hex_value */
#include <libc/template/_hex_value.h>
#define _hex_value __LOCAL__hex_value
#endif /* !__CRT_HAVE__hex_value */
#endif /* !_hex_value */

}


@@>> hex_init(3)
@@Initialize the `_hex_value' array (unless it was already statically initialized)
void hex_init(void) {
	/* Nothing :) */
	COMPILER_IMPURE();
}


%{


#define PEX_RECORD_TIMES 0x1
#define PEX_USE_PIPES    0x2
#define PEX_SAVE_TEMPS   0x4

#define PEXECUTE_FIRST   1
#define PEXECUTE_LAST    2
#define PEXECUTE_ONE     3 /* (PEXECUTE_FIRST + PEXECUTE_LAST) */
#define PEXECUTE_SEARCH  4
#define PEXECUTE_VERBOSE 8

#define PEX_LAST             0x1
#define PEX_SEARCH           0x2
#define PEX_SUFFIX           0x4
#define PEX_STDERR_TO_STDOUT 0x8
#define PEX_BINARY_INPUT     0x10
#define PEX_BINARY_OUTPUT    0x20
#define PEX_STDERR_TO_PIPE   0x40
#define PEX_BINARY_ERROR     0x80
#define PEX_STDOUT_APPEND    0x100
#define PEX_STDERR_APPEND    0x200
struct pex_time {
	unsigned long user_seconds;
	unsigned long user_microseconds;
	unsigned long system_seconds;
	unsigned long system_microseconds;
};

}

%[define(_hex_array_size = 256)]
%[define(_hex_bad        = 99)]

%[define(PEX_RECORD_TIMES = 0x1)]
%[define(PEX_USE_PIPES    = 0x2)]
%[define(PEX_SAVE_TEMPS   = 0x4)]

%[define(PEXECUTE_FIRST   = 1)]
%[define(PEXECUTE_LAST    = 2)]
%[define(PEXECUTE_ONE     = 3)] /* (PEXECUTE_FIRST + PEXECUTE_LAST) */
%[define(PEXECUTE_SEARCH  = 4)]
%[define(PEXECUTE_VERBOSE = 8)]

%[define(PEX_LAST             = 0x1)]
%[define(PEX_SEARCH           = 0x2)]
%[define(PEX_SUFFIX           = 0x4)]
%[define(PEX_STDERR_TO_STDOUT = 0x8)]
%[define(PEX_BINARY_INPUT     = 0x10)]
%[define(PEX_BINARY_OUTPUT    = 0x20)]
%[define(PEX_STDERR_TO_PIPE   = 0x40)]
%[define(PEX_BINARY_ERROR     = 0x80)]
%[define(PEX_STDOUT_APPEND    = 0x100)]
%[define(PEX_STDERR_APPEND    = 0x200)]


char const *pex_run(struct pex_obj *obj, int flags, char const *executable, char *const *argv,
                    char const *outname, char const *errname, int *err); /* TODO */

char const *pex_run_in_environment(struct pex_obj *obj, int flags, char const *executable,
                                   char *const *argv, char *const *env, char const *outname,
                                   char const *errname, int *err); /* TODO */

FILE *pex_input_file(struct pex_obj *obj, int flags, char const *in_name); /* TODO */

FILE *pex_input_pipe(struct pex_obj *obj, int binary); /* TODO */

FILE *pex_read_output(struct pex_obj *obj, int binary); /* TODO */

FILE *pex_read_err(struct pex_obj *obj, int binary); /* TODO */

int pex_get_status(struct pex_obj *obj, int count, int *vector); /* TODO */

struct pex_obj *pex_init(int flags, char const *pname, char const *tempbase); /* TODO */

int pex_get_times(struct pex_obj *obj, int count, struct pex_time *vector); /* TODO */

void pex_free(struct pex_obj *obj); /* TODO */

char const *pex_one(int flags, char const *executable, char *const *argv, char const *pname,
                    char const *outname, char const *errname, int *status, int *err); /* TODO */

int pexecute(char const *a, char *const *b, char const *c,
             char const *d, char **e, char **f, int g); /* TODO */

int pwait(int a, int *b, int c); /* TODO */



%{

__SYSDECL_END
#endif /* __CC__ */

}
