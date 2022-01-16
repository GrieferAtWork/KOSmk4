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
#ifndef GUARD_LIBC_LIBC_COMPAT_C
#define GUARD_LIBC_LIBC_COMPAT_C 1

/*
 * Misc functions needed for ABI compatibility with other platforms.
 */

#include "../api.h"
/**/

#include <kos/exec/elf.h>
#include <kos/exec/idata.h>
#include <kos/exec/peb.h>
#include <kos/malloc.h>
#include <kos/syscalls.h>
#include <linux/net.h>

#include <elf.h>
#include <stdlib.h> /* exit() */
#include <string.h>
#include <syscall.h>
#include <unicode.h>
#include <unistd.h>

#include "../user/stdio-api.h"
#include "compat.h"
#include "dl.h"
#include "globals.h"

DECL_BEGIN



/************************************************************************/
/* KOS/DOS Default STDIO streams                                        */
/************************************************************************/
PRIVATE ATTR_SECTION(".data.crt.FILE.std_files") struct iofile_data_novtab default_stdin_data  = IOFILE_DATA_NOVTAB_INIT();
PRIVATE ATTR_SECTION(".data.crt.FILE.std_files") struct iofile_data_novtab default_stdout_data = IOFILE_DATA_NOVTAB_INIT();
PRIVATE ATTR_SECTION(".data.crt.FILE.std_files") struct iofile_data_novtab default_stderr_data = IOFILE_DATA_NOVTAB_INIT();
INTERN ATTR_SECTION(".data.crt.FILE.std_files") FILE libc_iob[3] = {
	[0] = __IO_FILE_INIT(NULL, 0, NULL, IO_LNBUF, STDIN_FILENO, { 0 }, 0, (struct iofile_data *)&default_stdin_data),             /* !Relocation: &default_stdin_io */
	[1] = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDOUT_FILENO, { 0 }, 0, (struct iofile_data *)&default_stdout_data), /* !Relocation: &default_stdout_io */
	[2] = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDERR_FILENO, { 0 }, 0, (struct iofile_data *)&default_stderr_data), /* !Relocation: &default_stderr_io */
};

/* These are the actual, exported std* stream symbols. */
#undef stdin
#undef stdout
#undef stderr
INTERN ATTR_SECTION(".data.crt.FILE.locked.read.read") FILE *libc_stdin    = &libc_iob[0]; /* !Relocation: &default_stdin */
INTERN ATTR_SECTION(".data.crt.FILE.locked.write.write") FILE *libc_stdout = &libc_iob[1]; /* !Relocation: &default_stdout */
INTERN ATTR_SECTION(".data.crt.FILE.locked.write.write") FILE *libc_stderr = &libc_iob[2]; /* !Relocation: &default_stderr */
DEFINE_PUBLIC_ALIAS(stdin, libc_stdin);
DEFINE_PUBLIC_ALIAS(stdout, libc_stdout);
DEFINE_PUBLIC_ALIAS(stderr, libc_stderr);
#define stdin  GET_NOREL_GLOBAL(stdin)
#define stdout GET_NOREL_GLOBAL(stdout)
#define stderr GET_NOREL_GLOBAL(stderr)


DEFINE_PUBLIC_ALIAS(_iob, libc_iob);              /* For DOS compatibility */
DEFINE_PUBLIC_ALIAS(__p__iob, libd___iob_func);   /* For DOS compatibility */
DEFINE_PUBLIC_ALIAS(__iob_func, libd___iob_func); /* For DOS compatibility */
INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL ATTR_SECTION(".text.crt.dos.FILE.std_files") FILE *
NOTHROW(LIBDCALL libd___iob_func)(void) {
	/* DOS doesn't have copy-relocations, we don't have
	 * to  worry  about   `dlsym("_iob") != &libc_iob'. */
	return libc_iob;
}




/************************************************************************/
/* Old glibc stdio compat                                               */
/************************************************************************/

/* NOTE: The `84' relates to the expected 32-bit struct size */
struct IO_FILE_84 {
	/*
	 * Code will directly access the fields:
	 *
	 * - io84_IO_read_ptr, io84_IO_read_end
	 *   >> #define getc(stream)                                       \
	 *   >>     ((stream->io84_IO_read_ptr < stream->io84_IO_read_end) \
	 *   >>         ? (*stream->io84_IO_read_ptr++)                    \
	 *   >>         : __uflow(stream))
	 *
	 * - io84_IO_write_ptr, io84_IO_write_end
	 *   >> #define putc(ch, stream)                                     \
	 *   >>     ((stream->io84_IO_write_ptr < stream->io84_IO_write_end) \
	 *   >>         ? (*stream->io84_IO_write_ptr++ = ch)                \
	 *   >>         : __overflow(stream, ch))
	 *   >>
	 *
	 * For compat, we want to define these fields such that:
	 *   - io84_IO_read_ptr >= io84_IO_read_end
	 *   - io84_IO_write_ptr >= io84_IO_write_end
	 *   This way, legacy code always invokes the library functions which
	 *   we're already defining to do the right thing in the above cases.
	 *
	 * ================== 64-bit:
	 * - For `io84_IO_write_ptr >= io84_IO_write_end':
	 *   - `io84_IO_buf_end = NULL;' in std-stream replacements
	 *   - For dynamically allocated streams this is actually already the case implicitly
	 *     because `struct iofile_data_novtab' is allocated immediately after the leading
	 *     FILE object, and starts  with a NULL-field that  is already mandatory for  DOS
	 *     compatibility!
	 *   - For the standard streams, we simply link custom instances of `struct IO_FILE_84'
	 * - For `io84_IO_read_ptr >= io84_IO_read_end':
	 *   - `__if_pad0 = 0xffffffff;' in std-stream  replacements, causing the  high
	 *     32 bits of `io84_IO_read_ptr' to be all 1es and following the assumption
	 *     that libc is loaded somewhere other than the last 4GiB of memory  (which
	 *     we  can always assume when hosted by  a high-memory kernel, which KOS is
	 *     on all supported architectures).
	 *     This way, a compare becomes `0xffffffff???????? >= if_base', which should
	 *     always equate `true'.
	 *
	 * ================== 32-bit:
	 * - It would be impossible to overlay the normal FILE object on-top of IO_FILE_84,
	 *   as (like can be seen  in the below comments),  this would create an  invariant
	 *   requiring  `if_cnt >= (uint32_t)if_base', which is  impossible to comply with.
	 * - Instead, define a non-zero `file_uoffset' and have the KOS-style FILE object
	 *   be padded with leading 0-bytes such that all of the important FILE-bytes are
	 *   set to ZEROes (which is one of the way to comply with I/O requirements).
	 */

	/*32|64-bit * ..................................... *     32-bit | 64-bit */
	/* 0|  0*/ uint32_t           io84_flags;          /* if_ptr     | if_ptr */
#if __SIZEOF_POINTER__ > 4
	/*     4*/ uint32_t          _io84_pad;            /* -          | if_ptr (cont.) */
#endif /* __SIZEOF_POINTER__ > 4 */
	/* 4|  8*/ byte_t            *io84_IO_read_ptr;    /* if_cnt     | if_cnt+__if_pad0 */
	/* 8| 16*/ byte_t            *io84_IO_read_end;    /* if_base    | if_base */
	/*12| 24*/ byte_t            *io84_IO_read_base;   /* if_flag    | if_flag+if_fd */
	/*16| 32*/ byte_t            *io84_IO_write_base;  /* if_fd      | if_charbuf+if_bufsiz */
	/*20| 40*/ byte_t            *io84_IO_write_ptr;   /* if_charbuf | if_exdata */
	/*24| 48*/ byte_t            *io84_IO_write_end;   /* if_bufsiz  | - */
	/*28| 56*/ byte_t            *io84_IO_buf_base;    /* if_exdata  | - */
	/*32| 64*/ byte_t            *io84_IO_buf_end;
	/*36| 72*/ byte_t            *io84_IO_save_base;
	/*40| 80*/ byte_t            *io84_IO_backup_base;
	/*44| 88*/ byte_t            *io84_IO_save_end;
	/*48| 96*/ void              *io84_markers;
	/*52|104*/ struct IO_FILE_84 *io84_chain;
	/*56|112*/ uint32_t           io84_fileno;
	/*60|116*/ uint32_t           io84_blksize;
	/*64|120*/ uint64_t           io84_offset;
	/*72|128*/ uint16_t           io84_cur_column;
	/*74|130*/ uint8_t            io84_unused;
	/*75|131*/ uint8_t            io84_shortbuf[1];
#if __SIZEOF_POINTER__ > 4
	/*  |132*/ uint32_t          _io84_pad2;
#endif /* __SIZEOF_POINTER__ > 4 */
	/*76|136*/ void              *io84_lock;
	/*80|144*/ void const *const *io84_vtable;
	/*84|152*/ /* End-of-struct */
};
#if __SIZEOF_POINTER__ == 4
#define SIZEOF_IO_FILE_84 84
#elif __SIZEOF_POINTER__ == 8
#define SIZEOF_IO_FILE_84 152
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */


struct linux_default_stdio_file {
#if __SIZEOF_POINTER__ == 4
	byte_t ldsf_zero[sizeof(struct IO_FILE_84) - sizeof(FILE)]; /* 0 bytes... */
	FILE   ldsf_stdio;                                          /* The actual file object */
#elif __SIZEOF_POINTER__ == 8
	FILE   ldsf_stdio;                                          /* The actual file object */
	byte_t ldsf_zero[sizeof(struct IO_FILE_84) - sizeof(FILE)]; /* Pad with 0-byts. */
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
};

STATIC_ASSERT(sizeof(struct IO_FILE_84) == sizeof(struct linux_default_stdio_file));
STATIC_ASSERT(sizeof(struct IO_FILE_84) == SIZEOF_IO_FILE_84);

#if __SIZEOF_POINTER__ == 4
#ifndef FILE_HAVE_UOFFSET
#error "Need FILE_HAVE_UOFFSET when sizeof(void *) == 4"
#endif /* !FILE_HAVE_UOFFSET */
INTERN ATTR_SECTION(".data.crt.FILE.std_files") ptrdiff_t file_uoffset = 0;
INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.std_files") FILE *__FCALL
file_calloc(size_t extsize) {
	FILE *result;
	result = (FILE *)calloc(1, file_uoffset + sizeof(FILE) + extsize);
	if (result)
		result = (FILE *)((byte_t *)result + file_uoffset);
	return result;
}
#else /* __SIZEOF_POINTER__ == 4 */
#ifdef FILE_HAVE_UOFFSET
#error "Why is this enabled? - We don't need it!"
#endif /* FILE_HAVE_UOFFSET */
#endif /* __SIZEOF_POINTER__ != 4 */


/* Lazily allocated linux STDIO file objects. */
PRIVATE ATTR_SECTION(".bss.crt.compat.linux.stdio") struct linux_default_stdio_file *
linux_stdio_files = NULL;


/* Helper for loading std stream addresses in compatibility mode. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") NONNULL((1, 2, 3)) FILE *
NOTHROW(LIBCCALL get_mainapp_std_stream_addr)(void *__restrict mainapp,
                                              char const *__restrict name1,
                                              char const *__restrict name2,
                                              struct linux_default_stdio_file *__restrict fallback) {
	byte_t *result;
	ElfW(Sym) const *sym;
	sym = (ElfW(Sym) const *)dlauxctrl(mainapp, DLAUXCTRL_ELF_GET_LSYMBOL, name1);
	if (sym == NULL || sym->st_shndx == SHN_UNDEF)
		sym = (ElfW(Sym) const *)dlauxctrl(mainapp, DLAUXCTRL_ELF_GET_LSYMBOL, name2);
	if (sym == NULL || sym->st_shndx == SHN_UNDEF)
		return (FILE *)fallback;
	result = (byte_t *)sym->st_value;
	if (sym->st_shndx != SHN_ABS)
		result += (uintptr_t)dlmodulebase(mainapp);

	/* Initialize the user-program STD stream. (This right here
	 * emulates the R_*_COPY relocation which was no doubt  the
	 * reason why we got here in the first place) */
	memcpy(result, fallback, SIZEOF_IO_FILE_84);
	return (FILE *)result;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.stdio") void
NOTHROW(LIBCCALL linux_stdio_init)(bool is_2_1) {
	void *mainapp;
	struct linux_default_stdio_file *result;
	if (linux_stdio_files)
		return; /* Already initialized */

	/* Remember what was linked. */
	libc_compat |= is_2_1 ? COMPAT_FLAG_LINKED_IO_FILE_84_2_1
	                      : COMPAT_FLAG_LINKED_IO_FILE_84;

	/* TODO: Figure out what's supposed to be different when `is_2_1 == true' */

	/* NOTE: Intentional crash if this Calloc() fails */
	result = (struct linux_default_stdio_file *)Calloc(3, sizeof(struct linux_default_stdio_file));
	memcpy(&result[0].ldsf_stdio, &libc_iob[0], sizeof(FILE));
	memcpy(&result[1].ldsf_stdio, &libc_iob[1], sizeof(FILE));
	memcpy(&result[2].ldsf_stdio, &libc_iob[2], sizeof(FILE));

	/* Remember custom stdio file table. */
	linux_stdio_files = result;
#ifdef FILE_HAVE_UOFFSET
	file_uoffset = offsetof(struct linux_default_stdio_file, ldsf_stdio);
#endif /* FILE_HAVE_UOFFSET */

	/* Load std stream addresses. */
	mainapp     = dlopen(NULL, 0);
	libc_stdin  = get_mainapp_std_stream_addr(mainapp, "_IO_stdin_", "_IO_2_1_stdin_", &result[0]);
	libc_stdout = get_mainapp_std_stream_addr(mainapp, "_IO_stdout_", "_IO_2_1_stdout_", &result[1]);
	libc_stderr = get_mainapp_std_stream_addr(mainapp, "_IO_stderr_", "_IO_2_1_stderr_", &result[2]);

	/* Update global std stream symbols with correct values. */
	stdin  = libc_stdin;
	stdout = libc_stdout;
	stderr = libc_stderr;
}

/* Initialize the linux stdio-compatibility system. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_2_1_stdin)(void) {
	linux_stdio_init(true);
	return libc_stdin;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_2_1_stdout)(void) {
	linux_stdio_init(true);
	return libc_stdout;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_2_1_stderr)(void) {
	linux_stdio_init(true);
	return libc_stderr;
}

/* Initialize the linux stdio-compatibility system. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_stdin)(void) {
	linux_stdio_init(false);
	return libc_stdin;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_stdout)(void) {
	linux_stdio_init(false);
	return libc_stdout;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") FILE *
NOTHROW(LIBCCALL linux_stdio_get_stderr)(void) {
	linux_stdio_init(false);
	return libc_stderr;
}

/* Export symbols. */
DEFINE_PUBLIC_IDATA_G(_IO_2_1_stdin_, linux_stdio_get_2_1_stdin, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA_G(_IO_2_1_stdout_, linux_stdio_get_2_1_stdout, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA_G(_IO_2_1_stderr_, linux_stdio_get_2_1_stderr, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA_G(_IO_stdin_, linux_stdio_get_stdin, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA_G(_IO_stdout_, linux_stdio_get_stdout, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA_G(_IO_stderr_, linux_stdio_get_stderr, SIZEOF_IO_FILE_84);






/************************************************************************/
/* __builtin_[vec_](new|delete)                                         */
/************************************************************************/
typedef void (LIBCCALL *PNEW_HANDLER)(void);
PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.heap") char const
default_new_handler_message[] = "Virtual memory exceeded in `new'\n";
PRIVATE ATTR_SECTION(".text.crt.compat.linux.heap") void LIBCCALL
libc_default_new_handler(void) {
	/* Yes: old-style c++ dynamic memory functions didn't raise exceptions
	 *      on  out-of-memory,  but  simply  terminated  the  application! */
	sys_write(STDERR_FILENO, default_new_handler_message,
	          sizeof(default_new_handler_message) - sizeof(char));
	sys_exit((syscall_ulong_t)-1);
}

#undef __new_handler
DEFINE_PUBLIC_IDATA_G(__new_handler, libc___new_handler, __SIZEOF_POINTER__);
INTERN ATTR_SECTION(".bss.crt.compat.linux.heap") PNEW_HANDLER libc___new_handler = NULL;
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") PNEW_HANDLER *LIBCCALL
libc___new_handler_cb(void) {
	if (libc___new_handler == NULL)
		libc___new_handler = &libc_default_new_handler;
	return &libc___new_handler;
}

PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.heap") char const
name___new_handler[] = "__new_handler";
PRIVATE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.heap")
PNEW_HANDLER *LIBCCALL libc_p_new_handler(void) {
	PNEW_HANDLER *result;
	result = (PNEW_HANDLER *)dlsym(RTLD_DEFAULT, name___new_handler);
	if unlikely(!result)
		result = libc___new_handler_cb(); /* Shouldn't happen */
	if unlikely(!*result)
		*result = &libc_default_new_handler;
	return result;
}
#define __new_handler (*libc_p_new_handler())

DEFINE_PUBLIC_ALIAS(set_new_handler, libc_set_new_handler);
INTERN ATTR_RETNONNULL ATTR_SECTION(".text.crt.compat.linux.heap")
PNEW_HANDLER LIBCCALL libc_set_new_handler(PNEW_HANDLER handler) {
	PNEW_HANDLER result, *phandler;
	phandler = &__new_handler;
	result   = *phandler;
	if (handler == NULL)
		handler = &libc_default_new_handler;
	*phandler = handler;
	return result;
}

DEFINE_PUBLIC_ALIAS(__builtin_new, libc___builtin_new);
INTERN ATTR_MALLOC ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.heap")
void *LIBCCALL libc___builtin_new(size_t sz) {
	void *result = malloc(sz);
	if unlikely(result == NULL)
		(*__new_handler)();
	return result;
}

DEFINE_PUBLIC_ALIAS(__builtin_vec_delete, libc___builtin_vec_delete);
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") void LIBCCALL
libc___builtin_vec_delete(void *ptr, size_t maxindex, size_t size,
                          void(LIBCCALL *dtor)(void *obj, int auto_delete),
                          int auto_delete_vec, int auto_delete) {
	size_t count = maxindex + 1;
	byte_t *iter = (byte_t *)ptr + count * size;
	while (count--) {
		(*dtor)(iter, auto_delete);
		iter -= size;
	}
	if (auto_delete_vec)
		free(iter); /* __builtin_delete(iter); */
}

DEFINE_PUBLIC_ALIAS(__builtin_vec_new, libc___builtin_vec_new);
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") void *LIBCCALL
libc___builtin_vec_new(void *ptr, size_t maxindex, size_t size,
                       void(LIBCCALL *ctor)(void *obj)) {
	byte_t *iter;
	size_t count = maxindex + 1;
	if (ptr == NULL)
		ptr = libc___builtin_new(count * size);
	iter = (byte_t *)ptr;
	while (count--) {
		(*ctor)(iter);
		iter += size;
	}
	return ptr;
}






/************************************************************************/
/* socketcall(2)                                                        */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(socketcall, libc_socketcall);
DEFINE_PUBLIC_ALIAS(__socketcall, libc_socketcall);
DEFINE_PUBLIC_ALIAS(__libc_socketcall, libc_socketcall);
INTERN ATTR_SECTION(".text.crt.compat.linux.misc") NONNULL((2)) longptr_t LIBCCALL
libc_socketcall(ulongptr_t call, ulongptr_t *__restrict argv) {
	longptr_t result;
#ifdef SYS_socketcall
	result = sys_socketcall(call, argv);
#else /* SYS_socketcall */
	/* Branch based on the requested call. */
	switch (call) {

#ifdef SYS_socket
	case SYS_SOCKET:
		result = sys_socket(argv[0], argv[1], argv[2]);
		break;
#endif /* SYS_socket */

#ifdef SYS_bind
	case SYS_BIND:
		result = sys_bind(argv[0], (struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* SYS_bind */

#ifdef SYS_connect
	case SYS_CONNECT:
		result = sys_connect(argv[0], (struct sockaddr *)(uintptr_t)argv[1], argv[2]);
		break;
#endif /* SYS_connect */

#ifdef SYS_listen
	case SYS_LISTEN:
		result = sys_listen(argv[0], argv[1]);
		break;
#endif /* SYS_listen */

#ifdef SYS_accept
	case SYS_ACCEPT:
		result = sys_accept(argv[0],
		                    (struct sockaddr *)(uintptr_t)argv[1],
		                    (socklen_t *)(uintptr_t)argv[2]);
		break;
#elif defined(SYS_accept4)
	case SYS_ACCEPT:
		result = sys_accept4(argv[0],
		                     (struct sockaddr *)(uintptr_t)argv[1],
		                     (socklen_t *)(uintptr_t)argv[2], 0);
		break;
#endif /* ... */

#ifdef SYS_getsockname
	case SYS_GETSOCKNAME:
		result = sys_getsockname(argv[0],
		                         (struct sockaddr *)(uintptr_t)argv[1],
		                         (socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* SYS_getsockname */

#ifdef SYS_getsockname
	case SYS_GETPEERNAME:
		result = sys_getpeername(argv[0],
		                         (struct sockaddr *)(uintptr_t)argv[1],
		                         (socklen_t *)(uintptr_t)argv[2]);
		break;
#endif /* SYS_getsockname */

#ifdef SYS_socketpair
	case SYS_SOCKETPAIR:
		result = sys_socketpair(argv[0], argv[1], argv[2],
		                        (fd_t *)(uintptr_t)argv[3]);
		break;
#endif /* SYS_socketpair */

#ifdef SYS_send
	case SYS_SEND:
		result = sys_send(argv[0],
		                  (void const *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(SYS_sendto)
	case SYS_SEND:
		result = sys_sendto(argv[0],
		                    (void const *)(uintptr_t)argv[1],
		                    argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef SYS_recv
	case SYS_RECV:
		result = sys_recv(argv[0],
		                  (void *)(uintptr_t)argv[1],
		                  argv[2], argv[3]);
		break;
#elif defined(SYS_recvfrom)
	case SYS_RECV:
		result = sys_recvfrom(argv[0],
		                      (void *)(uintptr_t)argv[1],
		                      argv[2], argv[3], NULL, 0);
		break;
#endif /* ... */

#ifdef SYS_sendto
	case SYS_SENDTO:
		result = sys_sendto(argv[0], (void const *)(uintptr_t)argv[1], argv[2],
		                    argv[3], (struct sockaddr const *)(uintptr_t)argv[4], argv[5]);
		break;
#endif /* SYS_sendto */

#ifdef SYS_recvfrom
	case SYS_RECVFROM:
		result = sys_recvfrom(argv[0], (void *)(uintptr_t)argv[1], argv[2],
		                      argv[3], (struct sockaddr *)(uintptr_t)argv[4],
		                      (socklen_t *)(uintptr_t)argv[5]);
		break;
#endif /* SYS_recvfrom */

#ifdef SYS_shutdown
	case SYS_SHUTDOWN:
		result = sys_shutdown(argv[0], argv[1]);
		break;
#endif /* SYS_shutdown */

#ifdef SYS_setsockopt
	case SYS_SETSOCKOPT:
		result = sys_setsockopt(argv[0], argv[1], argv[2],
		                        (void const *)(uintptr_t)argv[3],
		                        argv[4]);
		break;
#endif /* SYS_setsockopt */

#ifdef SYS_getsockopt
	case SYS_GETSOCKOPT:
		result = sys_getsockopt(argv[0], argv[1], argv[2],
		                        (void *)(uintptr_t)argv[3],
		                        (socklen_t *)(uintptr_t)argv[4]);
		break;
#endif /* SYS_getsockopt */

#ifdef SYS_sendmsg
	case SYS_SENDMSG:
		result = sys_sendmsg(argv[0],
		                     (struct msghdr const *)(uintptr_t)argv[1],
		                     argv[2]);
		break;
#endif /* SYS_sendmsg */

#ifdef SYS_recvmsg
	case SYS_RECVMSG:
		result = sys_recvmsg(argv[0],
		                     (struct msghdr *)(uintptr_t)argv[1],
		                     argv[2]);
		break;
#endif /* SYS_recvmsg */

#ifdef SYS_accept4
	case SYS_ACCEPT4:
		result = sys_accept4(argv[0],
		                     (struct sockaddr *)(uintptr_t)argv[1],
		                     (socklen_t *)(uintptr_t)argv[2],
		                     argv[3]);
		break;
#endif /* SYS_accept4 */

#ifdef SYS_recvmmsg
	case SYS_RECVMMSG:
		result = sys_recvmmsg(argv[0], (struct mmsghdr *)(uintptr_t)argv[1], argv[2],
		                      argv[3], (struct timespec32 const *)(uintptr_t)argv[4]);
		break;
#endif /* SYS_recvmmsg */

#ifdef SYS_sendmmsg
	case SYS_SENDMMSG:
		result = sys_sendmmsg(argv[0], (struct mmsghdr *)(uintptr_t)argv[1],
		                      argv[2], argv[3]);
		break;
#endif /* SYS_sendmmsg */

	default:
		result = -EINVAL;
	}
#endif /* !SYS_socketcall */
	return libc_seterrno_syserr(result);
}



/************************************************************************/
/* __shtab(3)                                                           */
/************************************************************************/

/* Shift lookup table?? No idea why code doesn't use `1 << i' instead of `__shtab[i]'... */
DEFINE_PUBLIC_ALIAS(__shtab, libc___shtab);
INTERN_CONST __UINT32_TYPE__ const libc___shtab[] = {
	UINT32_C(0x00000001), UINT32_C(0x00000002),
	UINT32_C(0x00000004), UINT32_C(0x00000008),
	UINT32_C(0x00000010), UINT32_C(0x00000020),
	UINT32_C(0x00000040), UINT32_C(0x00000080),
	UINT32_C(0x00000100), UINT32_C(0x00000200),
	UINT32_C(0x00000400), UINT32_C(0x00000800),
	UINT32_C(0x00001000), UINT32_C(0x00002000),
	UINT32_C(0x00004000), UINT32_C(0x00008000),
	UINT32_C(0x00010000), UINT32_C(0x00020000),
	UINT32_C(0x00040000), UINT32_C(0x00080000),
	UINT32_C(0x00100000), UINT32_C(0x00200000),
	UINT32_C(0x00400000), UINT32_C(0x00800000),
	UINT32_C(0x01000000), UINT32_C(0x02000000),
	UINT32_C(0x04000000), UINT32_C(0x08000000),
	UINT32_C(0x10000000), UINT32_C(0x20000000),
	UINT32_C(0x40000000), UINT32_C(0x80000000)
};



/************************************************************************/
/* __libc_start_main(3)                                                 */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(__libc_start_main, libc_start_main);
INTERN ATTR_SECTION(".text.crt.compat.linux.init") NONNULL((1)) int LIBCCALL
libc_start_main(int (*main)(int, char **, char **),
                int argc, char **ubp_av,
                void (*init)(void),
                void (*fini)(void),
                void (*rtld_fini)(void),
                void *stack_end) {
	int exit_code;
	struct process_peb *peb;
	libc_compat |= COMPAT_FLAG_CALLED___libc_start_main;

	/* All of these will contain garbage... */
	(void)argc;
	(void)ubp_av;
	(void)init;
	(void)fini;
	(void)rtld_fini;
	(void)stack_end;

	/* Use the PEB to pass the correct information. */
	peb       = &__peb;
	exit_code = (*main)(peb->pp_argc,
	                    peb->pp_argv,
	                    peb->pp_envp);
	exit(exit_code);
}



/************************************************************************/
/* __libc_init(3)                                                       */
/************************************************************************/
#if defined(__i386__) && !defined(__x86_64__)
/* >> void __libc_init(int argc, char *argv[], char *envp[]);
 * Instead of its usual purpose of initializing libc, we define
 * this  function  to write-back  parameters with  their proper
 * values onto the stack, thus allowing the caller to  continue
 * working with them.
 *
 * This may not look like it makes much sense since normally
 * parameters like this can't be  accessed by the caller  of
 * the  function, but `__libc_init()' is provided for compat
 * with old linux programs (1990-2001-ish) that had a custom
 * assembly _start function which essentially did this:
 * >> pushl   <envp>   # With the emulated stub-PEB, this pushes <TOP_OF_STACK>
 * >> pushl   <argv>   # With the emulated stub-PEB, this pushes <TOP_OF_STACK>
 * >> pushl   <argc>   # With the emulated stub-PEB, this pushes `0'
 * >> ...
 * >> call    __libc_init
 * >> ...
 * >> call    main     # Note that arguments for main are never re-loaded,
 * >>                  # meaning that modifications by `__libc_init' are
 * >>                  # preserved! */
DEFINE_PUBLIC_ALIAS(__libc_init, libc___libc_init);

/* Yes GCC. I know it looks like those assignments don't do anything...
 * But  trust me on this one. - Just don't try to optimize them away ;) */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/* Prevent GCC from (rightfully) optimizing  away
 * (seemingly unnecessary) parameter assignments. */
__attribute__((optimize("-O0")))
INTERN ATTR_SECTION(".text.crt.compat.linux.init") void LIBCCALL
libc___libc_init(int argc, char *argv[], char *envp[]) {
	struct process_peb *peb;
	libc_compat |= COMPAT_FLAG_CALLED___libc_init;

	peb  = &__peb;
	argc = peb->pp_argc;
	argv = peb->pp_argv;
	envp = peb->pp_envp;
}

#pragma GCC diagnostic pop
#endif /* __i386__ && !__x86_64__ */


/************************************************************************/
/* General compatibility flags                                          */
/************************************************************************/
INTERN ATTR_SECTION(".bss.crt.compat.linux.init") uintptr_t libc_compat = COMPAT_FLAG_NORMAL;


DECL_END


/************************************************************************/
/* <fpu_control.h>                                                      */
/************************************************************************/
#if __has_include(<fpu_control.h>)
#include <fpu_control.h>

DECL_BEGIN

#ifndef _FPU_DEFAULT
#ifndef _FPU_IEEE
#define _FPU_IEEE 0
#endif /* !_FPU_IEEE */
#define _FPU_DEFAULT _FPU_IEEE
#endif /* !_FPU_DEFAULT */
#ifndef _FPU_RESERVED
#define _FPU_RESERVED 0
#endif /* !_FPU_RESERVED */

/* >> __fpu_control(3)
 * Control word set during startup of old linux applications. */
#if _FPU_DEFAULT == 0
INTERN ATTR_SECTION(".bss.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#else /* _FPU_DEFAULT == 0 */
INTERN ATTR_SECTION(".data.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#endif /* _FPU_DEFAULT != 0 */
DEFINE_PUBLIC_ALIAS(__fpu_control, libc___fpu_control);

/* >> __setfpucw(3)
 * Function called by old linux applications to set `__fpu_control()'. */
DEFINE_PUBLIC_ALIAS(__setfpucw, libc___setfpucw);
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc___setfpucw)(fpu_control_t ctrl) {
#if _FPU_RESERVED != 0
	fpu_control_t word;
	_FPU_GETCW(word);
	word &= _FPU_RESERVED;
	word |= ctrl & ~_FPU_RESERVED;
	_FPU_SETCW(word);
#else /* _FPU_RESERVED != 0 */
	_FPU_SETCW(ctrl);
#endif /* _FPU_RESERVED == 0 */
}

DECL_END
#endif /* __has_include(<fpu_control.h>) */

#endif /* !GUARD_LIBC_LIBC_COMPAT_C */
