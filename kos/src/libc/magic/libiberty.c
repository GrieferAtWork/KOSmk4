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
/* (#) Portability: EMX kLIBC     (/libc/include/libintl.h) */
/* (#) Portability: GNU C Library (/intl/libintl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libintl.h) */
/* (#) Portability: diet libc     (/include/libintl.h) */
/* (#) Portability: libc6         (/include/libintl.h) */
/* (#) Portability: musl libc     (/include/libintl.h) */
/* (#) Portability: uClibc        (/include/libintl.h) */
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

%(auto_source){
#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".bss.crt.libiberty") char const *libc_libiberty_optr      = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") char *libc_libiberty_nptr            = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") __ULONGPTR_TYPE__ libc_libiberty_len = 0;
DEFINE_PUBLIC_ALIAS(libiberty_optr, libc_libiberty_optr);
DEFINE_PUBLIC_ALIAS(libiberty_nptr, libc_libiberty_nptr);
DEFINE_PUBLIC_ALIAS(libiberty_len, libc_libiberty_len);
#endif /* !__KERNEL__ */
}


[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
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
[[crt_impl_if(!defined(_WIN32))]]
const char *dos_lbasename(const char *filename) {
@@pp_ifdef _WIN32@@
	return basename(filename);
@@pp_else@@
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;
	/* Skip drive letter. */
	if (((iter[0] >= 'A' && iter[0] <= 'Z') ||
	     (iter[0] >= 'a' && iter[0] <= 'z')) &&
	    iter[1] == ':')
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
[[crt_impl_if(defined(_WIN32))]]
const char *unix_lbasename(const char *filename) {
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

[[ATTR_ALLOC_SIZE((1)), wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[nonnull, requires_function(malloc, xmalloc_failed)]]
[[impl_include("<asm/crt/malloc.h>")]]
void *xmalloc(size_t num_bytes) {
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

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((1, 2))]]
[[nonnull, requires_function(calloc, xmalloc_failed)]]
[[impl_include("<asm/crt/malloc.h>", "<hybrid/__overflow.h>")]]
void *xcalloc(size_t elem_count, size_t elem_size) {
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
char *xvasprintf([[nonnull, format("printf")]] const char *format, $va_list args) {
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
char **buildargv(char const *a); /* TODO */

void expandargv([[nonnull]] int *p_argc, [[nonnull]] char ***p_argv); /* TODO */

int writeargv(char *const *argv, FILE *fp); /* TODO */

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

[[nonnull]]
char *concat_copy([[nonnull]] char *dst, char const *first, ...) {
	char *ptr = dst;
	va_list args;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		ptr = (char *)mempcpyc(ptr, first, strlen(first), sizeof(char));
	va_end(args);
	*ptr = '\0';
	return dst;
}


char *concat_copy2(char const *first, ...); /* TODO: `return concat_copy(libiberty_concat_ptr, ...)' */


%{
#ifndef libiberty_concat_ptr
#ifdef __CRT_HAVE_libiberty_concat_ptr
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

long get_run_time(void); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_relative_prefix(char const *a, char const *b, char const *c); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_relative_prefix_ignore_links(const char *a, const char *b, const char *c); /* TODO */

[[wunused, nonnull]]
const char *choose_tmpdir(void); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *choose_temp_base(void); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_temp_file(char const *a); /* TODO */

[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
char *make_temp_file_with_prefix(const char *a, const char *b); /* TODO */

int unlink_if_ordinary(char const *a); /* TODO */

[[wunused, const]]
double physmem_total(void); /* TODO */

[[wunused, pure]]
double physmem_available(void); /* TODO */

unsigned int xcrc32(unsigned char const *a, int b, unsigned int c); /* TODO */


%{
#define _hex_array_size 256
#define _hex_bad        99
extern unsigned char const _hex_value[_hex_array_size];
#define hex_value(c) ((unsigned int)_hex_value[(unsigned char)(c)])
#define hex_p(c)     (hex_value(c) != _hex_bad)

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


void hex_init(void);

const char *pex_run(struct pex_obj *obj, int flags, const char *executable, char *const *argv,
                    const char *outname, const char *errname, int *err); /* TODO */

const char *pex_run_in_environment(struct pex_obj *obj, int flags, const char *executable,
                                   char *const *argv, char *const *env, const char *outname,
                                   const char *errname, int *err); /* TODO */

FILE *pex_input_file(struct pex_obj *obj, int flags, const char *in_name); /* TODO */

FILE *pex_input_pipe(struct pex_obj *obj, int binary); /* TODO */

FILE *pex_read_output(struct pex_obj *obj, int binary); /* TODO */

FILE *pex_read_err(struct pex_obj *obj, int binary); /* TODO */

int pex_get_status(struct pex_obj *obj, int count, int *vector); /* TODO */

struct pex_obj *pex_init(int flags, char const *pname, char const *tempbase); /* TODO */

int pex_get_times(struct pex_obj *obj, int count, struct pex_time *vector); /* TODO */

void pex_free(struct pex_obj *obj); /* TODO */

const char *pex_one(int flags, const char *executable, char *const *argv, const char *pname,
                    const char *outname, const char *errname, int *status, int *err); /* TODO */

int pexecute(char const *a, char *const *b, char const *c,
             char const *d, char **e, char **f, int g); /* TODO */

int pwait(int a, int *b, int c); /* TODO */



%{

__SYSDECL_END
#endif /* __CC__ */

}
