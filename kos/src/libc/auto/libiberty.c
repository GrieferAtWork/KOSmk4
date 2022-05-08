/* HASH CRC-32:0x7feb14c7 */
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
#include "../user/ctype.h"
#include "../user/stdio.h"
#include "../user/stdio_ext.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.mman.h"
#include "../user/sys.resource.h"
#include "../user/sys.times.h"
#include "sys.vtimes.h"
#include "../user/time.h"
#include "../user/unistd.h"

DECL_BEGIN

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
#ifndef __KERNEL__
#include <hybrid/host.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *
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
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE ATTR_RETNONNULL WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_dos_lbasename)(char const *filename) {



	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;
	/* Skip drive letter. */
	if (libc_isalpha(iter[0]) && iter[1] == ':')
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
NOTHROW_NCX(LIBCCALL libc_xvasprintf)(char const *format,
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
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **
NOTHROW_NCX(LIBCCALL libc_buildargv)(char const *cmdline) {
	char **argv = NULL;
	size_t argc = 0;
	if (!cmdline)
		return NULL;
	while (libc_isspace(*cmdline))
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
				if (!libc_isspace(ch)) {
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
			argcopy_str = (char *)libc_xrealloc(argcopy_str, (argcopy_len + flushlen + 1) * sizeof(char));
			libc_memcpy(argcopy_str + argcopy_len, flush_start, flushlen);
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
				__hybrid_assert(libc_isspace(ch));
				__hybrid_assert(quote == 0);
				++cmdline;
				goto end_of_argument;
			}
			flush_start = cmdline;
		}
end_of_argument:
		argcopy_str[argcopy_len] = '\0';

		/* Append the argument. */
		argv = (char **)libc_xrealloc(argv, (argc + 2) * sizeof(char *));
		argv[argc++] = argcopy_str;

		/* Skip space past the argument. */
		while (libc_isspace(*cmdline))
			++cmdline;
		if (!*cmdline)
			break;
	}
	argv[argc] = NULL; /* Sentinel */
	return argv;
}
#include <libc/errno.h>
#include <hybrid/__assert.h>
#include <bits/crt/mapfile.h>
/* >> expandargv(3)
 * Expand special `@file' arguments passed on the commandline */
INTERN ATTR_SECTION(".text.crt.libiberty") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc_expandargv)(int *p_argc,
                                      char ***p_argv) {
	size_t i, argc = (size_t)*p_argc;
	char **argv = *p_argv;
	for (i = 0; i < argc; ++i) {
		struct mapfile mf;
		char *arg = argv[i];
		char **inject_argv;
		size_t inject_argc;
		if (arg[0] != '@')
			continue;
		++arg;

		/* Map the specified file into memory. - If doing so fails,
		 * (due to something other than out-of-memory), then we simply
		 * ignore the @-directive. */
		if (libc_mapfile(&mf, arg, 0, (size_t)-1, 1) != 0) {
#ifdef libc_geterrno
			if (libc_geterrno() == ENOMEM)
				libc_xmalloc_failed(1);
#endif /* libc_geterrno */
			continue;
		}

		/* Build an argument vector from the file.
		 * Note the forced trailing NUL-byte we requested for the mapping! */
		inject_argv = libc_buildargv((char *)mf.mf_addr);

		libc_unmapfile(&mf);


		/* Count the # of injected arguments. */
		__hybrid_assert(inject_argv);
		for (inject_argc = 0; inject_argv[inject_argc]; ++inject_argc)
			;

		/* Resize the argument vector. */
		if (argv == *p_argv) {
			size_t size;
			size = (argc + inject_argc + 1) * sizeof(char *);
			argv = (char **)libc_memcpy(libc_xmalloc(size), argv, size - sizeof(char *));
			argv[argc] = NULL; /* Sentinel */
		} else {
			argv = (char **)libc_xrealloc(argv, (argc + inject_argc + 1) * sizeof(char *));
		}
		/* Inject arguments */
		libc_memmoveupc(argv + i + inject_argc,
		           argv + i,
		           argc - i, sizeof(char *));
		libc_memcpyc(argv + i, inject_argv, inject_argc, sizeof(char *));

		libc_free(inject_argv);

		argc += inject_argc;
		i += inject_argc;
	}
	*p_argc = (int)(unsigned int)argc;
	*p_argv = argv;
}
#include <asm/crt/stdio.h>
/* @return: 0 : Success
 * @return: 1 : Error */
INTERN ATTR_SECTION(".text.crt.libiberty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_writeargv)(char *const *argv,
                                     FILE *fp) {
	if unlikely(!fp)
		goto err;
	for (; *argv; ++argv) {
		char const *arg = *argv;
		for (; *arg; ++arg) {
			char ch = *arg;
			if (libc_isspace(ch) || libc_strchr("\'\"\\", ch)) {
				if (libc_fputc('\\', fp) == EOF)
					goto err;
			}
			if (libc_fputc(ch, fp) == EOF)
				goto err;
		}
		if (libc_fputc('\n', fp) == EOF)
			goto err;
	}
	return 0;
err:
	return 1;
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
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_concat_vcopy)(char *dst,
                                        char const *first,
                                        va_list args) {
	char *ptr = dst;
	for (; first; first = va_arg(args, char *))
		ptr = (char *)libc_mempcpyc(ptr, first, libc_strlen(first), sizeof(char));
	*ptr = '\0';
	return dst;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(VLIBDCALL libd_concat_copy)(char *dst,
                                        char const *first,
                                        ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_concat_vcopy(dst, first, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(VLIBCCALL libc_concat_copy)(char *dst,
                                        char const *first,
                                        ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_concat_vcopy(dst, first, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") char *
NOTHROW_NCX(VLIBDCALL libd_concat_copy2)(char const *first,
                                         ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_concat_vcopy(libiberty_concat_ptr, first, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.libiberty") char *
NOTHROW_NCX(VLIBCCALL libc_concat_copy2)(char const *first,
                                         ...) {
	char *result;
	va_list args;
	va_start(args, first);
	result = libc_concat_vcopy(libiberty_concat_ptr, first, args);
	va_end(args);
	return result;
}
#include <asm/os/resource.h>
#include <bits/os/rusage.h>
#include <asm/crt/confname.h>
#include <bits/os/tms.h>
#include <bits/crt/vtimes.h>
/* >> get_run_time(3)
 * Return the amount of time the calling process has run (in microseconds)
 * If possible, time spent idling isn't counted, though if not possible, it
 * is included, also. */
INTERN ATTR_SECTION(".text.crt.libiberty") WUNUSED long
NOTHROW_NCX(LIBCCALL libc_get_run_time)(void) {
	uint64_t result;
#ifdef __RUSAGE_SELF
	struct rusage64 ru;
	libc_getrusage64(RUSAGE_SELF, &ru);
	result  = ((uint64_t)ru.ru_utime.tv_sec * 1000000) + ru.ru_utime.tv_usec;
	result += ((uint64_t)ru.ru_stime.tv_sec * 1000000) + ru.ru_stime.tv_usec;
#elif defined(times)
	struct tms ts;
	libc_times(&ts);
	result = ts.tms_utime + ts.tms_stime;
	result *= 1000000;
	result /= libc_sysconf(_SC_CLK_TCK);
#elif defined(__VTIMES_UNITS_PER_SECOND)
	struct libc_vtimes vt;
	libc_vtimes(&vt, NULL);
	result = vt->vm_utime + vt->vm_stime;
	result *= 1000000;
	result /= __VTIMES_UNITS_PER_SECOND;
#else /* ... */
	result = libc_clock();
	result *= 1000000;
	result /= __CLOCKS_PER_SEC;
#endif /* !... */
	return (long)result;
}
/* >> choose_temp_base(3)
 * Create a temporary filename in `choose_tmpdir(3)' by use of `mktemp(3)'
 * The returned string must always be freed, and if no filename could be
 * generated, an empty string is returned. */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_choose_temp_base)(void) {
	char const *tmpdir = libc_choose_tmpdir();
	size_t tmpdir_len = libc_strlen(tmpdir);
	char *result = (char *)libc_xmalloc((tmpdir_len + 6 + 1) * sizeof(char));
	libc_memcpyc(libc_mempcpyc(result, tmpdir, tmpdir_len, sizeof(char)),
	        "XXXXXX", 7, sizeof(char));
	return libc_mktemp(result);
}
/* >> choose_tmpdir(3)
 * Return the path to a suitable temp directory.
 * The returned path is guarantied to be non-NULL, and include a trailing slash. */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE ATTR_RETNONNULL WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_choose_tmpdir)(void) {
	static char const *result = NULL;
	if (result == NULL) {
		char const *path;
		size_t pathlen;
		char *pathcopy, *ptr;
		size_t i;

		static char const defdir_names[][10] = { "/tmp", "/var/tmp", "/usr/tmp" };




		static char const envvar_names[][8] = { "TMPDIR", "TMP", "TEMP" };
		for (i = 0; i < COMPILER_LENOF(envvar_names); ++i) {
			path = libc_getenv(envvar_names[i]);
			if (path && libc_access(path, __X_OK | __W_OK | __R_OK) == 0)
				goto got_tmppath;
		}

		for (i = 0; i < COMPILER_LENOF(defdir_names); ++i) {
			path = defdir_names[i];
			if (libc_access(path, __X_OK | __W_OK | __R_OK) == 0)
				goto got_tmppath;
		}

		/* Fallback: use the current directory. */
		path = ".";
got_tmppath:

		pathlen = libc_strlen(path);




		while (pathlen && path[pathlen - 1] == '/')
			--pathlen;


		/* Force-append a trailing slash. */
		pathcopy = (char *)libc_xmalloc((pathlen + 2) * sizeof(char));
		ptr = (char *)libc_mempcpyc(pathcopy, path, pathlen, sizeof(char));



		*ptr++ = '/';

		*ptr++ = '\0';
		result = pathcopy;
	}
	return result;
}
#include <parts/printf-config.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_temp_file_with_prefix)(char const *prefix,
                                                      char const *suffix) {
	fd_t tempfd;
	char *result, *p;
	const char *tmpdir = libc_choose_tmpdir();
	size_t tmpdir_len, prefix_len, suffix_len;
	if (prefix == NULL)
		prefix = "cc";
	if (suffix == NULL)
		suffix = "";
	tmpdir_len = libc_strlen(tmpdir);
	prefix_len = libc_strlen(prefix);
	suffix_len = libc_strlen(suffix);

	/* Construct the full filename. */
	result = (char *)libc_xmalloc((tmpdir_len +
	                          prefix_len + 6 +
	                          suffix_len + 1) *
	                         sizeof(char));
	p = (char *)libc_mempcpyc(result, tmpdir, tmpdir_len, sizeof(char));
	p = (char *)libc_mempcpyc(p, prefix, prefix_len, sizeof(char));
	p = (char *)libc_mempcpyc(p, "XXXXXX", 6, sizeof(char));
	p = (char *)libc_mempcpyc(p, suffix, suffix_len, sizeof(char));
	*p = '\0';
	tempfd = libc_mkstemps(result, suffix_len);
	if (tempfd < 0) {




		libc_fprintf(stderr, "Cannot create temporary file in %s: %m\n", tmpdir);

		libc_abort();
	}


	libc_close(tempfd);

	return result;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_temp_file)(char const *suffix) {
	return libc_make_temp_file_with_prefix(NULL, suffix);
}
#include <bits/os/stat.h>
#include <asm/os/stat.h>
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_unlink_if_ordinary)(char const *filename) {
	struct stat st;
	if (lstat(filename, &st) != 0)
		return 1;
	if (!__S_ISREG(st.st_mode) && !__S_ISLNK(st.st_mode))
		return 1;
	/* Sorry, no way to prevent the race where
	 * the file is replaced before we get here... */
	return libc_unlink(filename);
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_physmem_total)(void) {
	size_t pages    = libc_sysconf(_SC_PHYS_PAGES);
	size_t pagesize = libc_getpagesize();
	return (double)pages * (double)pagesize;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED double
NOTHROW_NCX(LIBCCALL libc_physmem_available)(void) {
	size_t pages    = libc_sysconf(_SC_AVPHYS_PAGES);
	size_t pagesize = libc_getpagesize();
	return (double)pages * (double)pagesize;
}
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED __UINT32_TYPE__
NOTHROW_NCX(LIBCCALL libc_xcrc32)(__BYTE_TYPE__ const *buf,
                                  __STDC_INT_AS_SIZE_T len,
                                  __UINT32_TYPE__ crc) {
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
/* >> hex_init(3)
 * Initialize the `_hex_value' array (unless it was already statically initialized) */
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_hex_init)(void) {
	/* Nothing :) */
	COMPILER_IMPURE();
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(C_alloca, libc_C_alloca);
DEFINE_PUBLIC_ALIAS(stack_limit_increase, libc_stack_limit_increase);
DEFINE_PUBLIC_ALIAS(dos_lbasename, libc_dos_lbasename);
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
DEFINE_PUBLIC_ALIAS(buildargv, libc_buildargv);
DEFINE_PUBLIC_ALIAS(expandargv, libc_expandargv);
DEFINE_PUBLIC_ALIAS(writeargv, libc_writeargv);
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
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$concat_copy2, libd_concat_copy2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(concat_copy2, libc_concat_copy2);
DEFINE_PUBLIC_ALIAS(get_run_time, libc_get_run_time);
DEFINE_PUBLIC_ALIAS(choose_temp_base, libc_choose_temp_base);
DEFINE_PUBLIC_ALIAS(choose_tmpdir, libc_choose_tmpdir);
DEFINE_PUBLIC_ALIAS(make_temp_file_with_prefix, libc_make_temp_file_with_prefix);
DEFINE_PUBLIC_ALIAS(make_temp_file, libc_make_temp_file);
DEFINE_PUBLIC_ALIAS(unlink_if_ordinary, libc_unlink_if_ordinary);
DEFINE_PUBLIC_ALIAS(physmem_total, libc_physmem_total);
DEFINE_PUBLIC_ALIAS(physmem_available, libc_physmem_available);
DEFINE_PUBLIC_ALIAS(xcrc32, libc_xcrc32);
DEFINE_PUBLIC_ALIAS(hex_init, libc_hex_init);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBIBERTY_C */
