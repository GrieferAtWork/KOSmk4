/* HASH CRC-32:0x1a867505 */
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
#ifndef GUARD_LIBC_AUTO_LIBIBERTY_C
#define GUARD_LIBC_AUTO_LIBIBERTY_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/libiberty.h"
#include "../user/stdio.h"
#include "../user/stdio_ext.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/sys.resource.h"
#include "../user/unistd.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".bss.crt.libiberty") char const *libc_libiberty_optr      = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") char *libc_libiberty_nptr            = NULL;
INTERN ATTR_SECTION(".bss.crt.libiberty") __ULONGPTR_TYPE__ libc_libiberty_len = 0;
DEFINE_PUBLIC_ALIAS(libiberty_optr, libc_libiberty_optr);
DEFINE_PUBLIC_ALIAS(libiberty_nptr, libc_libiberty_nptr);
DEFINE_PUBLIC_ALIAS(libiberty_len, libc_libiberty_len);
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <hybrid/host.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_C_alloca)(size_t num_bytes) {

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
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	while (old && old->cah_sp < sp)
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	while (old && old->cah_sp > sp)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	{
		struct C_alloca_header *prev;
		prev = old->cah_prev;
		libc_free(old);
		old = prev;
	}

	/* Special case: C_alloca() must return NULL for 0-byte requests. */
	if (num_bytes == 0)
		return NULL;
	result = (struct C_alloca_header *)libc_xmalloc(sizeof(struct C_alloca_header) + num_bytes);

	/* Remember this allocation */
	result->cah_sp   = sp;
	result->cah_prev = old;
	old = result;

	/* Return a pointer to the user payload. */
	return (result + 1);





}
#include <asm/os/resource.h>
#include <bits/os/rlimit.h>
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_stack_limit_increase)(ulongptr_t newlim) {
	COMPILER_IMPURE();
	(void)newlim;

	{
		struct rlimit rl;
		if (libc_getrlimit((__rlimit_resource_t)__RLIMIT_STACK, &rl) == 0 &&
		    (rl.rlim_cur != __RLIM_INFINITY && rl.rlim_cur < newlim) &&
		    (rl.rlim_max == __RLIM_INFINITY || rl.rlim_cur < rl.rlim_max)) {
			rl.rlim_cur = newlim;
			if (rl.rlim_max != __RLIM_INFINITY && rl.rlim_cur > rl.rlim_max)
				rl.rlim_cur = rl.rlim_max;
			libc_setrlimit((__rlimit_resource_t)__RLIMIT_STACK, &rl);
		}
	}

}
#endif /* !__KERNEL__ */
#ifndef _WIN32
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE ATTR_RETNONNULL WUNUSED const char *
NOTHROW_NCX(LIBCCALL libc_dos_lbasename)(const char *filename) {



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

}
#endif /* !_WIN32 */
#ifdef _WIN32
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE ATTR_RETNONNULL WUNUSED const char *
NOTHROW_NCX(LIBCCALL libc_unix_lbasename)(const char *filename) {



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

}
#endif /* _WIN32 */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_lrealpath)(char const *path) {
	char *result = libc_canonicalize_file_name(path);
	if (result == NULL)
		result = libc_strdup(path);
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_getpwd)(void) {
	static char *result = NULL;
	if (result == NULL)
		result = libc_get_current_dir_name();
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_errno_max)(void) {
	return __ECOUNT - 1;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_signo_max)(void) {
	return __NSIG - 1;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED errno_t
NOTHROW_NCX(LIBCCALL libc_strtoerrno)(char const *name) {
	errno_t result = 0;
	if (name) {
		errno_t max = libc_errno_max();
		for (;; ++result) {
			char const *sysname;
			if (result > max) {
				result = 0;
				break;
			}
			sysname = libc_strerrorname_np(result);
			if (sysname && libc_strcmp(sysname, name) == 0)
				break;
		}
	}
	return result;
}
#include <asm/crt/stdio_ext.h>
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_unlock_stream)(FILE *fp) {
	COMPILER_IMPURE();
	(void)fp;
#ifdef __FSETLOCKING_BYCALLER
	libc___fsetlocking(fp, __FSETLOCKING_BYCALLER);
#endif /* __FSETLOCKING_BYCALLER */
}
#include <libc/template/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_unlock_std_streams)(void) {

	libc_unlock_stream(stdin);


	libc_unlock_stream(stdout);


	libc_unlock_stream(stderr);

}
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_fopen_unlocked)(char const *filename,
                                          char const *mode) {
	FILE *result = libc_fopen(filename, mode);
	if (result)
		libc_unlock_stream(result);
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_fdopen_unlocked)(fd_t fd,
                                           char const *mode) {
	FILE *result = libc_fdopen(fd, mode);
	if (result)
		libc_unlock_stream(result);
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_spaces)(__STDC_INT_AS_SIZE_T count) {
	static char *buf = NULL;
	static size_t buflen = 0; /* # of space characters in `buf' (followed by NUL) */
	if (buflen < count) {
		char *newbuf = (char *)libc_realloc(buf, (count + 1) * sizeof(char));
		if (!newbuf)
			return NULL;
		libc_memset(newbuf + buflen, ' ', count - buflen);
		buf    = newbuf;
		buflen = count;
	}
	return buf + buflen - count;
}
#include <asm/crt/malloc.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc_xmalloc)(size_t num_bytes) {
	void *result = libc_malloc(num_bytes);
	if (result == NULL) {
#ifndef __MALLOC_ZERO_IS_NONNULL
		if (num_bytes != 0 || ((result = libc_malloc(1)) == NULL))
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		{
			libc_xmalloc_failed(num_bytes);
		}
	}
	return result;
}
#include <asm/crt/malloc.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_xrealloc)(void *ptr,
                                    size_t num_bytes) {
	void *result;
#ifdef __REALLOC_ZERO_IS_NONNULL
	result = libc_realloc(ptr, num_bytes);
#else /* __REALLOC_ZERO_IS_NONNULL */
	result = libc_realloc(ptr, num_bytes ? num_bytes : 1);
#endif /* !__REALLOC_ZERO_IS_NONNULL */
	if (result == NULL)
		libc_xmalloc_failed(num_bytes);
	return result;
}
#include <asm/crt/malloc.h>
#include <hybrid/__overflow.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_xcalloc)(size_t elem_count,
                                   size_t elem_size) {
	void *result = libc_calloc(elem_count, elem_size);
	if (result == NULL) {
#ifndef __MALLOC_ZERO_IS_NONNULL
		if ((elem_count != 0 && elem_size != 0) || ((result = libc_calloc(1, 1)) == NULL))
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		{
			size_t total;
			if (__hybrid_overflow_umul(elem_count, elem_size, &total))
				total = (size_t)-1;
			libc_xmalloc_failed(total);
		}
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_xstrdup)(char const *__restrict string) {
	size_t copysize = (libc_strlen(string) + 1) * sizeof(char);
	return (char *)libc_memcpy(libc_xmalloc(copysize), string, copysize);
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_xstrndup)(char const *string,
                                    size_t max_chars) {
	size_t copylen = libc_strnlen(string, max_chars);
	char *result = (char *)libc_xmalloc((copylen + 1) * sizeof(char));
	*(char *)libc_mempcpyc(result, string, copylen, sizeof(char)) = '\0';
	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((3)) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_xmemdup)(void const *src,
                                   size_t src_bytes,
                                   size_t alloc_size) {
	void *result = libc_xmalloc(alloc_size);
	void *ptr = libc_mempcpy(result, src, src_bytes);
	if (alloc_size > src_bytes)
		libc_bzero(ptr, alloc_size - src_bytes);
	return result;
}
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_xvasprintf)(const char *format,
                                      va_list args) {
	va_list args2;
	char *result;
	va_copy(args2, args);
	result = libc_vstrdupf(format, args2);
	va_end(args2);
	if (result == NULL)
		libc_xmalloc_failed((libc_vsnprintf(NULL, 0, format, args) + 1) * sizeof(char));
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) char *
NOTHROW_NCX(VLIBDCALL libd_xasprintf)(char const *__restrict format,
                                      ...) {
	char * result;
	va_list args;
	va_start(args, format);
	result = libc_xvasprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) char *
NOTHROW_NCX(VLIBCCALL libc_xasprintf)(char const *__restrict format,
                                      ...) {
	char * result;
	va_list args;
	va_start(args, format);
	result = libc_xvasprintf(format, args);
	va_end(args);
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **
NOTHROW_NCX(LIBCCALL libc_dupargv)(char **argv) {
	char **result;
	size_t i, argc;
	if (!argv)
		return NULL;
	for (argc = 0; argv[argc]; ++argc)
		;
	result = (char **)libc_xmalloc((argc + 1) * sizeof(char *));
	for (i = 0; i < argc; ++i)
		result[i] = libc_xstrdup(argv[i]);
	result[argc] = NULL;
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_freeargv)(char **argv) {
	size_t i;
	if (!argv)
		return;
	for (i = 0; argv[i]; ++i)
		libc_free(argv[i]);
	libc_free(argv);
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_countargv)(char *const *argv) {
	__STDC_INT_AS_SIZE_T result = 0;
	if (argv != NULL) {
		for (; argv[result]; ++result)
			;
	}
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_vconcat)(char const *first,
                                   va_list args) {
	char *result, *ptr;
	size_t totlen = 0;
	va_list copy;
	va_copy(copy, args);
	for (ptr = (char *)first; ptr; ptr = va_arg(copy, char *))
		totlen += libc_strlen(ptr);
	va_end(copy);
	ptr = result = (char *)libc_xmalloc((totlen + 1) * sizeof(char));
	for (; first; first = va_arg(copy, char *))
		ptr = (char *)libc_mempcpyc(ptr, first, libc_strlen(first), sizeof(char));
	*ptr = '\0';
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *
NOTHROW_NCX(VLIBDCALL libd_concat)(char const *first,
                                   ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_vconcat(first, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *
NOTHROW_NCX(VLIBCCALL libc_concat)(char const *first,
                                   ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_vconcat(first, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *
NOTHROW_NCX(VLIBDCALL libd_reconcat)(char *old_ptr,
                                     char const *first,
                                     ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_vconcat(first, args);
	va_end(args);

	libc_free(old_ptr);

	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *
NOTHROW_NCX(VLIBCCALL libc_reconcat)(char *old_ptr,
                                     char const *first,
                                     ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_vconcat(first, args);
	va_end(args);

	libc_free(old_ptr);

	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ulongptr_t
NOTHROW_NCX(VLIBDCALL libd_concat_length)(char const *first,
                                          ...) {
	va_list args;
	size_t totlen = 0;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		totlen += libc_strlen(first);
	va_end(args);
	return (ulongptr_t)totlen;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ulongptr_t
NOTHROW_NCX(VLIBCCALL libc_concat_length)(char const *first,
                                          ...) {
	va_list args;
	size_t totlen = 0;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		totlen += libc_strlen(first);
	va_end(args);
	return (ulongptr_t)totlen;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(VLIBDCALL libd_concat_copy)(char *dst,
                                        char const *first,
                                        ...) {
	char *ptr = dst;
	va_list args;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		ptr = (char *)libc_mempcpyc(ptr, first, libc_strlen(first), sizeof(char));
	va_end(args);
	*ptr = '\0';
	return dst;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(VLIBCCALL libc_concat_copy)(char *dst,
                                        char const *first,
                                        ...) {
	char *ptr = dst;
	va_list args;
	va_start(args, first);
	for (; first; first = va_arg(args, char *))
		ptr = (char *)libc_mempcpyc(ptr, first, libc_strlen(first), sizeof(char));
	va_end(args);
	*ptr = '\0';
	return dst;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(C_alloca, libc_C_alloca);
DEFINE_PUBLIC_ALIAS(stack_limit_increase, libc_stack_limit_increase);
#endif /* !__KERNEL__ */
#ifndef _WIN32
DEFINE_PUBLIC_ALIAS(dos_lbasename, libc_dos_lbasename);
#endif /* !_WIN32 */
#ifdef _WIN32
DEFINE_PUBLIC_ALIAS(unix_lbasename, libc_unix_lbasename);
#endif /* _WIN32 */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(lrealpath, libc_lrealpath);
DEFINE_PUBLIC_ALIAS(getpwd, libc_getpwd);
DEFINE_PUBLIC_ALIAS(errno_max, libc_errno_max);
DEFINE_PUBLIC_ALIAS(signo_max, libc_signo_max);
DEFINE_PUBLIC_ALIAS(strtoerrno, libc_strtoerrno);
DEFINE_PUBLIC_ALIAS(unlock_stream, libc_unlock_stream);
DEFINE_PUBLIC_ALIAS(unlock_std_streams, libc_unlock_std_streams);
DEFINE_PUBLIC_ALIAS(fopen_unlocked, libc_fopen_unlocked);
DEFINE_PUBLIC_ALIAS(fdopen_unlocked, libc_fdopen_unlocked);
DEFINE_PUBLIC_ALIAS(spaces, libc_spaces);
DEFINE_PUBLIC_ALIAS(xmalloc, libc_xmalloc);
DEFINE_PUBLIC_ALIAS(xrealloc, libc_xrealloc);
DEFINE_PUBLIC_ALIAS(xcalloc, libc_xcalloc);
DEFINE_PUBLIC_ALIAS(xstrdup, libc_xstrdup);
DEFINE_PUBLIC_ALIAS(xstrndup, libc_xstrndup);
DEFINE_PUBLIC_ALIAS(xmemdup, libc_xmemdup);
DEFINE_PUBLIC_ALIAS(xvasprintf, libc_xvasprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$xasprintf, libd_xasprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(xasprintf, libc_xasprintf);
DEFINE_PUBLIC_ALIAS(dupargv, libc_dupargv);
DEFINE_PUBLIC_ALIAS(freeargv, libc_freeargv);
DEFINE_PUBLIC_ALIAS(countargv, libc_countargv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$concat, libd_concat);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(concat, libc_concat);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$reconcat, libd_reconcat);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(reconcat, libc_reconcat);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$concat_length, libd_concat_length);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(concat_length, libc_concat_length);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$concat_copy, libd_concat_copy);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(concat_copy, libc_concat_copy);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBIBERTY_C */
