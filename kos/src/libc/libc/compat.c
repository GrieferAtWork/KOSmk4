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

#include <hybrid/sync/atomic-once.h>

#include <kos/exec/elf.h>
#include <kos/exec/idata.h>
#include <kos/exec/ifunc.h>
#include <kos/exec/peb.h>
#include <kos/malloc.h>
#include <kos/syscalls.h>
#include <linux/net.h>
#include <nt/errhandlingapi.h>
#include <nt/handleapi.h>
#include <nt/libloaderapi.h>
#include <nt/types.h>

#include <elf.h>
#include <format-printer.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h> /* exit() */
#include <string.h>
#include <syscall.h>
#include <syslog.h>
#include <uchar.h>
#include <unicode.h>
#include <unistd.h>

#include <libcmdline/encode.h>

#include "../user/stdio-api.h"
#include "../user/stdlib.h"
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
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.dos.FILE.std_files")
FILE *NOTHROW(LIBDCALL libd___iob_func)(void) {
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

	/*32|64-bit * .................................... *     32-bit | 64-bit */
	/* 0|  0*/ uint32_t io84_flags;                   /* if_ptr     | if_ptr */
#if __SIZEOF_POINTER__ > 4
	/*     4*/ uint32_t _io84_pad;                    /* -          | if_ptr (cont.) */
#endif /* __SIZEOF_POINTER__ > 4 */
	/* 4|  8*/ byte_t            *io84_IO_read_ptr;   /* if_cnt     | if_cnt+__if_pad0 */
	/* 8| 16*/ byte_t            *io84_IO_read_end;   /* if_base    | if_base */
	/*12| 24*/ byte_t            *io84_IO_read_base;  /* if_flag    | if_flag+if_fd */
	/*16| 32*/ byte_t            *io84_IO_write_base; /* if_fd      | if_charbuf+if_bufsiz */
	/*20| 40*/ byte_t            *io84_IO_write_ptr;  /* if_charbuf | if_exdata */
	/*24| 48*/ byte_t            *io84_IO_write_end;  /* if_bufsiz  | - */
	/*28| 56*/ byte_t            *io84_IO_buf_base;   /* if_exdata  | - */
	/*32| 64*/ byte_t            *io84_IO_buf_end;
	/*36| 72*/ byte_t            *io84_IO_save_base;
	/*40| 80*/ byte_t            *io84_IO_backup_base;
	/*44| 88*/ byte_t            *io84_IO_save_end;
	/*48| 96*/ void              *io84_markers;
	/*52|104*/ struct IO_FILE_84 *io84_chain;
	/*56|112*/ uint32_t           io84_fileno;
	/*60|116*/ uint32_t           io84_blksize;
	/*64|120*/ uint64_t           io84_offset ATTR_PACKED;
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
PRIVATE ATTR_SECTION(".bss.crt.compat.linux.stdio")
struct linux_default_stdio_file *linux_stdio_files = NULL;


/* Helper for loading std stream addresses in compatibility mode. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux.stdio") NONNULL((1, 2, 3)) FILE *
NOTHROW(CC get_mainapp_std_stream_addr)(void *__restrict mainapp,
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
NOTHROW(CC linux_stdio_init)(bool is_2_1) {
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

DEFINE_PUBLIC_ALIAS(__default_new_handler, libc_default_new_handler);
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") void LIBCCALL
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
ATTR_SECTION(".text.crt.compat.linux.heap")
INTERN ATTR_MALLOC ATTR_RETNONNULL WUNUSED void *LIBCCALL
libc___builtin_new(size_t sz) {
	void *result = malloc(sz);
	if unlikely(result == NULL)
		(*__new_handler)();
	return result;
}

DEFINE_PUBLIC_ALIAS(__builtin_vec_delete, libc___builtin_vec_delete);
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") void LIBCCALL
libc___builtin_vec_delete(void *ptr, size_t maxindex, size_t size,
                          void (LIBCCALL *dtor)(void *obj, int auto_delete),
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
                       void (LIBCCALL *ctor)(void *obj)) {
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

DEFINE_PUBLIC_ALIAS(__throw_type_match, libc___throw_type_match);
INTERN ATTR_PURE ATTR_SECTION(".text.crt.compat.linux.except") void *LIBCCALL
libc___throw_type_match(void const *catch_type,
                        void const *throw_type, void *obj) {
	if (strcmp((char const *)catch_type, (char const *)throw_type) == 0)
		return obj;
	return NULL;
}

DEFINE_PUBLIC_ALIAS(__cyg_profile_func_enter, libc___cyg_profile_func_enter);
DEFINE_PUBLIC_ALIAS(__cyg_profile_func_exit, libc___cyg_profile_func_enter);
INTERN ATTR_SECTION(".text.crt.compat.linux.misc") void LIBCCALL
libc___cyg_profile_func_enter(void *this_fn, void *call_site) {
	COMPILER_IMPURE();
	(void)this_fn;
	(void)call_site;
}






/************************************************************************/
/* sigvec(3)                                                            */
/************************************************************************/
struct sigvec {
	__sighandler_t sv_handler; /* Signal handler. */
	int            sv_mask;    /* (too small) signal mask. */
	int            sv_flags;   /* Set of `SV_*' */
};
#define SV_ONSTACK   0x0001 /* s.a. `SA_ONSTACK' */
#define SV_INTERRUPT 0x0002 /* inverse of `SA_RESTART' */
#define SV_RESETHAND 0x0004 /* s.a. `SA_RESETHAND' */

DEFINE_PUBLIC_ALIAS(sigvec, libc_sigvec);
INTERN ATTR_SECTION(".text.crt.compat.linux.signal") int LIBCCALL
libc_sigvec(signo_t sig, struct sigvec const *nvec, struct sigvec *ovec) {
	int result;
	struct sigaction nsa, osa;
	if (nvec) {
		bzero(&nsa, sizeof(nsa));
		sigfillset(&nsa.sa_mask);
		nsa.sa_handler = nvec->sv_handler;
		memcpy(&nsa.sa_mask, &nvec->sv_mask, sizeof(int));
		if (nvec->sv_flags & SV_ONSTACK)
			nsa.sa_flags |= SA_ONSTACK;
		if (!(nvec->sv_flags & SV_INTERRUPT))
			nsa.sa_flags |= SA_RESTART;
		if (nvec->sv_flags & SV_RESETHAND)
			nsa.sa_flags |= SA_RESETHAND;
	}
	result = sigaction(sig, nvec ? &nsa : NULL, ovec ? &osa : NULL);
	if (result == 0 && ovec) {
		ovec->sv_handler = osa.sa_handler;
		memcpy(&ovec->sv_mask, &osa.sa_mask, sizeof(int));
		ovec->sv_flags = 0;
		if (osa.sa_flags & SA_ONSTACK)
			ovec->sv_flags |= SV_ONSTACK;
		if (!(osa.sa_flags & SA_RESTART))
			ovec->sv_flags |= SV_INTERRUPT;
		if (osa.sa_flags & SA_RESETHAND)
			ovec->sv_flags |= SV_RESETHAND;
	}
	return result;
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
INTERN
ATTR_SECTION(".text.crt.compat.linux.init") void LIBCCALL
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
INTERN ATTR_SECTION(".bss.crt.compat.linux.init")
uintptr_t libc_compat = COMPAT_FLAG_NORMAL;


DECL_END


/************************************************************************/
/* <fpu_control.h>                                                      */
/************************************************************************/
#ifndef __NO_FPU
#include <fpu_control.h>

DECL_BEGIN

#ifdef _FPU_GETCW

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
#else  /* _FPU_DEFAULT == 0 */
INTERN ATTR_SECTION(".data.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#endif /* _FPU_DEFAULT != 0 */
DEFINE_PUBLIC_ALIAS(__fpu_control, libc___fpu_control);

DEFINE_PUBLIC_ALIAS(__getfpucw, libc___getfpucw);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.math.float") fpu_control_t
NOTHROW_NCX(LIBCCALL libc___getfpucw)(void) {
	fpu_control_t word;
	_FPU_GETCW(word);
	return word;
}

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
#else  /* _FPU_RESERVED != 0 */
	_FPU_SETCW(ctrl);
#endif /* _FPU_RESERVED == 0 */
}
#endif /* _FPU_GETCW */

/* s.a. `__ieee754_inf()' in `<libm/inf.h>'
 *
 * User-programs would actually link against this symbol like:
 * >> extern double __huge_val;
 * (Assuming `double' is `__IEEE754_DOUBLE_TYPE__') */
DEFINE_PUBLIC_ALIAS(__huge_val, libc___huge_val);
INTERN_CONST ATTR_SECTION(".rodata.crt.math.float")
uint32_t const libc___huge_val[2] = {
	UINT32_C(0x7FF00000),
	UINT32_C(0x00000000)
};

DECL_END
#endif /* !__NO_FPU */




/************************************************************************/
/* Misc MSVCRT functions                                                */
/************************************************************************/
DECL_BEGIN

typedef struct {
	int newmode;
} _startupinfo;

DEFINE_PUBLIC_ALIAS(DOS$__lconv_init, libd___lconv_init);
DEFINE_PUBLIC_ALIAS(DOS$_query_app_type, libd__query_app_type);
DEFINE_PUBLIC_ALIAS(DOS$_set_app_type, libd___set_app_type);
DEFINE_PUBLIC_ALIAS(DOS$__set_app_type, libd___set_app_type);
DEFINE_PUBLIC_ALIAS(DOS$__getmainargs, libd___getmainargs);
DEFINE_PUBLIC_ALIAS(DOS$__wgetmainargs, libd___wgetmainargs);
DEFINE_PUBLIC_ALIAS(DOS$_XcptFilter, libd__XcptFilter);
DEFINE_PUBLIC_ALIAS(DOS$_seh_filter_dll, libd__seh_filter_dll);
DEFINE_PUBLIC_ALIAS(DOS$_seh_filter_exe, libd__seh_filter_exe);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler2, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler3, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler_3, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler4, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler4_common, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$__C_specific_handler, libd__except_handler4);

INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd___lconv_init(void) {
	CRT_UNIMPLEMENTED("__lconv_init()");
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd__query_app_type(void) {
	COMPILER_IMPURE();
	return 1; /* _crt_console_app */
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd___set_app_type(int typ) {
	(void)typ;
	COMPILER_IMPURE();
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd___getmainargs(int *pargc, char ***pargv,
                   char ***penvp, int dowildcard,
                   _startupinfo *pstartinfo) {
	struct process_peb *peb = &__peb;
	(void)dowildcard;
	if (pargc != NULL)
		*pargc = peb->pp_argc;
	if (pargv != NULL)
		*pargv = peb->pp_argv;
	if (penvp != NULL)
		*penvp = peb->pp_envp;
	if (pstartinfo != NULL)
		libd___set_app_type(pstartinfo->newmode);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd___wgetmainargs(int *pargc, char16_t ***pargv,
                    char16_t ***penvp, int dowildcard,
                    _startupinfo *pstartinfo) {
	(void)dowildcard;
	if (pargc != NULL)
		*pargc = *libc___p___argc();
	if (pargv != NULL)
		*pargv = *libd___p___wargv();
	if (penvp != NULL)
		*penvp = *libd___p___winitenv();
	if (pstartinfo != NULL)
		libd___set_app_type(pstartinfo->newmode);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.except") int LIBDCALL
libd__XcptFilter(u32 xno, struct _EXCEPTION_POINTERS *infp_ptrs) {
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_XcptFilter(%" PRIu32 ", %p)", xno, infp_ptrs);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.except") int LIBDCALL
libd__seh_filter_dll(u32 xno, struct _EXCEPTION_POINTERS *infp_ptrs) {
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_seh_filter_dll(%" PRIu32 ", %p)", xno, infp_ptrs);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.except") int LIBDCALL
libd__seh_filter_exe(u32 xno, struct _EXCEPTION_POINTERS *infp_ptrs) {
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_seh_filter_exe(%" PRIu32 ", %p)", xno, infp_ptrs);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.except") EXCEPTION_DISPOSITION LIBCCALL
libd__except_handler4(struct _EXCEPTION_RECORD *ExceptionRecord,
                      void *EstablisherFrame,
                      struct _CONTEXT *ContextRecord,
                      void *DispatcherContext) {
	(void)ExceptionRecord;
	(void)EstablisherFrame;
	(void)ContextRecord;
	(void)DispatcherContext;
	CRT_UNIMPLEMENTEDF("_except_handler4(%p, %p, %p, %p)",
	                   ExceptionRecord, EstablisherFrame,
	                   ContextRecord, DispatcherContext);
	return EXCEPTION_CONTINUE_SEARCH;
}



/************************************************************************/
/* _acmdln                                                              */
/************************************************************************/
PRIVATE ATTR_SECTION(".text.crt.dos.application.init") char *LIBDCALL
construct_dos_commandline(void) {
	struct process_peb *peb = &__peb;
	char *result            = NULL;
	void *libcmdline;
	PCMDLINE_ENCODE cmdline_encode;
	libcmdline = dlopen(LIBCMDLINE_LIBRARY_NAME, RTLD_LAZY | RTLD_LOCAL);
	if (!libcmdline)
		return NULL;
	*(void **)&cmdline_encode = dlsym(libcmdline, "cmdline_encode");
	if (cmdline_encode) {
		ssize_t error;
		struct format_aprintf_data printer;
		/* Encode the commandline. */
		format_aprintf_data_init(&printer);
		error = (*cmdline_encode)(&format_aprintf_printer, &printer,
		                          peb->pp_argc, peb->pp_argv);
		if unlikely(error < 0) {
			format_aprintf_data_fini(&printer);
		} else {
			result = format_aprintf_pack(&printer, NULL);
		}
	}
	dlclose(libcmdline);
	return result;
}

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
struct atomic_once libd___p__acmdln_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char *libd__acmdln = NULL;
DEFINE_PUBLIC_IDATA_G(DOS$_acmdln, libd___p__acmdln, __SIZEOF_POINTER__);
DEFINE_PUBLIC_ALIAS(DOS$__p__acmdln, libd___p__acmdln);
INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.application.init") char **LIBDCALL
libd___p__acmdln(void) {
	ATOMIC_ONCE_RUN(&libd___p__acmdln_initialized, {
		libd__acmdln = construct_dos_commandline();
	});
	return &libd__acmdln;
}



/************************************************************************/
/* _wcmdln                                                              */
/************************************************************************/
PRIVATE ATTR_SECTION(".text.crt.dos.application.init") char16_t *LIBDCALL
construct_dos_wcommandline(void) {
	char *acmdln = *libd___p__acmdln();
	return acmdln ? convert_mbstoc16(acmdln) : NULL;
}

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
struct atomic_once libd___p__wcmdln_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char16_t *libd__wcmdln = NULL;
DEFINE_PUBLIC_IDATA_G(DOS$_wcmdln, libd___p__wcmdln, __SIZEOF_POINTER__);
DEFINE_PUBLIC_ALIAS(DOS$__p__wcmdln, libd___p__wcmdln);
INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.application.init") char16_t **LIBDCALL
libd___p__wcmdln(void) {
	ATOMIC_ONCE_RUN(&libd___p__wcmdln_initialized, {
		libd__wcmdln = construct_dos_wcommandline();
	});
	return &libd__wcmdln;
}


/************************************************************************/
/* _commode                                                             */
/************************************************************************/
INTERN ATTR_SECTION(".bss.crt.dos.application.init") int libd__commode = 0;
/*DEFINE_PUBLIC_IDATA_G(DOS$_commode, libd___p__commode, __SIZEOF_POINTER__);*/
DEFINE_PUBLIC_ALIAS(DOS$_commode, libd__commode);
DEFINE_PUBLIC_ALIAS(DOS$__p__commode, libd___p__commode);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.application.init") int *LIBDCALL
libd___p__commode(void) {
	return &libd__commode;
}


/************************************************************************/
/* __mb_cur_max                                                         */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(__mb_cur_max, libd___mb_cur_max);
DEFINE_PUBLIC_ALIAS(__p___mb_cur_max, libd___p___mb_cur_max);
DEFINE_PUBLIC_ALIAS(___mb_cur_max_func, libd____mb_cur_max_func);
DEFINE_PUBLIC_ALIAS(___mb_cur_max_l_func, libd____mb_cur_max_l_func);
INTERN ATTR_SECTION(".data.crt.dos.application.init") int libd___mb_cur_max = 7;
INTERN ATTR_SECTION(".text.crt.dos.application.init") int *LIBDCALL
libd___p___mb_cur_max(void) {
	COMPILER_IMPURE();
	return &libd___mb_cur_max;
}
INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd____mb_cur_max_func(void) {
	COMPILER_IMPURE();
	return libd___mb_cur_max;
}
INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd____mb_cur_max_l_func(locale_t locale) {
	(void)locale;
	return libd____mb_cur_max_func();
}


/************************************************************************/
/* _setusermatherr()                                                    */
/************************************************************************/
#ifndef __NO_FPU
#ifdef __cplusplus
struct __exception;
#define STRUCT_EXCEPTION struct __exception
#else /* __cplusplus */
struct exception;
#define STRUCT_EXCEPTION struct exception
#endif /* !__cplusplus */

struct _exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};
#define _DOMAIN    1
#define _SING      2
#define _OVERFLOW  3
#define _UNDERFLOW 4
#define _TLOSS     5
#define _PLOSS     6

/* Assert that DOS's `struct _exception' is ABI-compatible with ours (which it should be) */
STATIC_ASSERT(offsetof(struct _exception, type) == offsetof(STRUCT_EXCEPTION, type));
STATIC_ASSERT(offsetafter(struct _exception, type) == offsetafter(STRUCT_EXCEPTION, type));
STATIC_ASSERT(offsetof(struct _exception, name) == offsetof(STRUCT_EXCEPTION, name));
STATIC_ASSERT(offsetafter(struct _exception, name) == offsetafter(STRUCT_EXCEPTION, name));
STATIC_ASSERT(offsetof(struct _exception, arg1) == offsetof(STRUCT_EXCEPTION, arg1));
STATIC_ASSERT(offsetafter(struct _exception, arg1) == offsetafter(STRUCT_EXCEPTION, arg1));
STATIC_ASSERT(offsetof(struct _exception, arg2) == offsetof(STRUCT_EXCEPTION, arg2));
STATIC_ASSERT(offsetafter(struct _exception, arg2) == offsetafter(STRUCT_EXCEPTION, arg2));
STATIC_ASSERT(offsetof(struct _exception, retval) == offsetof(STRUCT_EXCEPTION, retval));
STATIC_ASSERT(offsetafter(struct _exception, retval) == offsetafter(STRUCT_EXCEPTION, retval));
STATIC_ASSERT(_DOMAIN == __MATH_EXCEPT_DOMAIN);
STATIC_ASSERT(_SING == __MATH_EXCEPT_SING);
STATIC_ASSERT(_OVERFLOW == __MATH_EXCEPT_OVERFLOW);
STATIC_ASSERT(_UNDERFLOW == __MATH_EXCEPT_UNDERFLOW);
STATIC_ASSERT(_TLOSS == __MATH_EXCEPT_TLOSS);
STATIC_ASSERT(_PLOSS == __MATH_EXCEPT_PLOSS);

/* If non-NULL, the currently used `matherr(3)' handler in  "libc/matherr.c"
 * When `NULL', lazily load the matherr handler via `dlsym()', and fall back
 * to a no-op handler when no override was defined.
 *
 * To facilitate DOS's `__setusermatherr(3)', we simply re-assign this pointer
 * with  another function that  will invoke the  DOS-given math error handler. */
typedef int (LIBKCALL *LPMATHERR)(STRUCT_EXCEPTION *exc);
INTDEF LPMATHERR libc_pdyn_matherr;


DEFINE_PUBLIC_ALIAS(__setusermatherr, libc___setusermatherr);
INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libc___setusermatherr(int (LIBKCALL *fptr)(struct _exception *)) {
	/* We've already asserted  that DOS's `struct _exception'  and
	 * our `STRUCT_EXCEPTION'  are  binary  compatible  (s.a.  the
	 * static asserts above), so  if the calling conventions  also
	 * match, then we can simply cast+assign the function pointer. */
	libc_pdyn_matherr = (LPMATHERR)fptr;
}

#ifndef __LIBDCALL_IS_LIBKCALL
/* When calling conventions don't match, then we need to do some extra
 * work  in order to  set-up a wrapper that  calls DOS's error handler
 * using the proper calling convention. */
INTERN ATTR_SECTION(".bss.crt.dos.application.init")
int (LIBDCALL *libd_usermatherr_fptr)(struct _exception *) = NULL;
INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBKCALL
libd_usermatherr_wrapper(STRUCT_EXCEPTION *exc) {
	/* Even when calling conventions don't match, we still know that
	 * our `STRUCT_EXCEPTION' matches DOS's `struct _exception',  so
	 * no need to do some extra conversion in here.
	 *
	 * If they didn't match, this compat function could still  be
	 * provided, only that we'd need to do some extra fiddling in
	 * order to achive ABI compatibility. */
	return (*libd_usermatherr_fptr)((struct _exception *)exc);
}

DEFINE_PUBLIC_ALIAS(DOS$__setusermatherr, libd___setusermatherr);
INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd___setusermatherr(int (LIBDCALL *fptr)(struct _exception *)) {
	/* Assign the function pointer to-be called by the wrapper. */
	libd_usermatherr_fptr = fptr;

	/* Assign the wrapper to-be called as `matherr(3)' handler. */
	libc_pdyn_matherr = &libd_usermatherr_wrapper;
}
#endif /* !__LIBDCALL_IS_LIBKCALL */
#endif /* !__NO_FPU */



/************************************************************************/
/* _amsg_exit()                                                         */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(DOS$_amsg_exit, libd__amsg_exit);
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd__amsg_exit(int errnum) {
	CRT_UNIMPLEMENTEDF("DOS$_amsg_exit(%p)\n", errnum);
	_Exit(-1);
}



/************************************************************************/
/* _initterm()                                                          */
/************************************************************************/
typedef void (LIBDCALL *_INITTERMFUN)(void);
typedef int (LIBDCALL *_INITTERM_E_FN)(void);

DEFINE_PUBLIC_ALIAS(DOS$_initterm, libd__initterm);
INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd__initterm(_INITTERMFUN *start, _INITTERMFUN *end) {
	_INITTERMFUN *iter = start;
	for (iter = start; iter < end; ++iter) {
		if (!*iter)
			continue;
		syslog(LOG_DEBUG, "[libc] DOS$_initterm: call %p\n", *iter);
		(**iter)();
	}
	syslog(LOG_DEBUG, "[libc] DOS$_initterm: done\n");
}

DEFINE_PUBLIC_ALIAS(DOS$_initterm_e, libd__initterm_e);
INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBDCALL
libd__initterm_e(_INITTERM_E_FN *start, _INITTERM_E_FN *end) {
	_INITTERM_E_FN *iter;
	int result = 0;
	for (iter = start; iter < end; ++iter) {
		if (!*iter)
			continue;
		syslog(LOG_DEBUG, "[libc] DOS$_initterm_e: call %p\n", *iter);
		result = (**iter)();
		if (result != 0) {
			syslog(LOG_DEBUG, "[libc] DOS$_initterm_e: call %p failed -> %d\n", *iter, result);
			break;
		}
	}
	syslog(LOG_DEBUG, "[libc] DOS$_initterm_e: done\n");
	return result;
}



/************************************************************************/
/* _lock()                                                              */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(DOS$_lock, libd__lock);
DEFINE_PUBLIC_ALIAS(DOS$_unlock, libd__unlock);
INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd__lock(int locknum) {
	CRT_UNIMPLEMENTEDF("DOS$_lock(%d)", locknum);
}
INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd__unlock(int locknum) {
	CRT_UNIMPLEMENTEDF("DOS$_unlock(%d)", locknum);
}


/************************************************************************/
/* New-style MSVC stdio-FILE access                                     */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(DOS$__acrt_iob_func, libd___acrt_iob_func);
INTERN ATTR_CONST WUNUSED ATTR_SECTION(".text.crt.dos.compat.dos") FILE *
NOTHROW(LIBDCALL libd___acrt_iob_func)(unsigned int index) {
	return &libc_iob[index];
}



/************************************************************************/
/* KERNEL32 forwarders exported from libc                               */
/************************************************************************/
PRIVATE ATTR_SECTION(".bss.crt.dos.compat.dos") void *libkernel32 = NULL;
PRIVATE ATTR_SECTION(".text.crt.dos.compat.dos") void *CC libd_getk32(void) {
	void *k32 = ATOMIC_READ(libkernel32);
	if (k32)
		return k32;
	k32 = dlopen("libkernel32.so", RTLD_LAZY | RTLD_LOCAL);
	if (!k32) {
		syslog(LOG_CRIT, "[libc] Failed to load 'libkernel32.so': %s\n", dlerror());
		sys_exit_group(1);
	}
	if (!ATOMIC_CMPXCH(libkernel32, NULL, k32)) {
		dlclose(k32);
		k32 = ATOMIC_READ(libkernel32);
	}
	return k32;
}

/* Lazily load `libkernel32.so' (if not done already), and return the
 * address  of the named  `symbol_name'. If non-existent, `_Exit(1)'. */
ATTR_SECTION(".text.crt.dos.compat.dos")
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *LIBCCALL
libd_requirek32(char const *__restrict symbol_name) {
	void *result = dlsym(libd_getk32(), symbol_name);
	if (!result) {
		char *msg = dlerror();
		if (msg) {
			syslog(LOG_CRIT, "[libc] Failed to load '%s' from 'libkernel32.so': %s\n",
			       symbol_name, msg);
			sys_exit_group(1);
		}
	}
	return result;
}

#define DEFINE_KERNEL32_FORWARDER_FUNCTION(T_RETURN, cc, name, params, k32name, args) \
	DEFINE_PUBLIC_ALIAS(DOS$##name, libd_##name);                                     \
	INTERN ATTR_SECTION(".text.crt.dos.compat.dos")                                   \
	T_RETURN cc libd_##name params {                                                  \
		typedef T_RETURN (WINAPI *LPK32##name) params;                                \
		static LPK32##name pdynK32##name = NULL;                                      \
		if (!pdynK32##name)                                                           \
			*(void **)&pdynK32##name = libd_requirek32(k32name);                      \
		return (*pdynK32##name)args;                                                  \
	}

DEFINE_KERNEL32_FORWARDER_FUNCTION(DWORD, LIBDCALL, __vcrt_GetModuleFileNameW,
                                   (HMODULE hModule, LPWSTR lpFilename, DWORD nSize),
                                   "GetModuleFileNameW", (hModule, lpFilename, nSize))
DEFINE_KERNEL32_FORWARDER_FUNCTION(HMODULE, LIBDCALL, __vcrt_GetModuleHandleW,
                                   (LPCWSTR lpFilename),
                                   "GetModuleHandleW", (lpFilename))
DEFINE_KERNEL32_FORWARDER_FUNCTION(HMODULE, LIBDCALL, __vcrt_LoadLibraryExW,
                                   (LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags),
                                   "LoadLibraryExW", (lpLibFileName, hFile, dwFlags))
DEFINE_KERNEL32_FORWARDER_FUNCTION(WINBOOL, LIBDCALL, __vcrt_InitializeCriticalSectionEx,
                                   (/*LPCRITICAL_SECTION*/ void *lpCriticalSection, DWORD dwSpinCount, DWORD dwFlags),
                                   "InitializeCriticalSectionEx", (lpCriticalSection, dwSpinCount, dwFlags))
DEFINE_KERNEL32_FORWARDER_FUNCTION(uintptr_t, LIBDCALL, __threadhandle, (void), "GetCurrentThread", ())
#undef DEFINE_KERNEL32_FORWARDER_FUNCTION



/************************************************************************/
/* DOS Math error handling                                              */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(DOS$_except1, libd__except1);
DEFINE_PUBLIC_ALIAS(DOS$_except2, libd__except2);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") double LIBCCALL
libd__except1(int unknown_flags, int fpu_opcode, double arg1, double result, uintptr_t fpu_cw) {
	/* This function seems related to DOS math error handling... */
	CRT_UNIMPLEMENTEDF("DOS$_except1(%d,%d,%f,%f,%p)",
	                   unknown_flags, fpu_opcode, arg1, result, fpu_cw);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") double LIBCCALL
libd__except2(int unknown_flags, int fpu_opcode, double arg1, double arg2, double result, uintptr_t fpu_cw) {
	/* This function seems related to DOS math error handling... */
	CRT_UNIMPLEMENTEDF("DOS$_except2(%d,%d,%f,%f,%f,%p)",
	                   unknown_flags, fpu_opcode, arg1, arg2, result, fpu_cw);
	return result;
}



/************************************************************************/
/* New-style DOS CRT initialization                                     */
/************************************************************************/
#define _crt_argv_no_arguments         0
#define _crt_argv_unexpanded_arguments 1
#define _crt_argv_expanded_arguments   2
typedef int _crt_argv_mode;

DEFINE_PUBLIC_ALIAS(DOS$_configure_narrow_argv, libd__configure_narrow_argv);
DEFINE_PUBLIC_ALIAS(DOS$_configure_wide_argv, libd__configure_wide_argv);
DEFINE_PUBLIC_ALIAS(DOS$_initialize_narrow_environment, libd__initialize_narrow_environment);
DEFINE_PUBLIC_ALIAS(DOS$_initialize_wide_environment, libd__initialize_wide_environment);
DEFINE_PUBLIC_ALIAS(DOS$_get_initial_narrow_environment, libd__get_initial_narrow_environment);
DEFINE_PUBLIC_ALIAS(DOS$_get_initial_wide_environment, libd__get_initial_wide_environment);
DEFINE_PUBLIC_ALIAS(DOS$_get_narrow_winmain_command_line, libd__get_narrow_winmain_command_line);
DEFINE_PUBLIC_ALIAS(DOS$_get_wide_winmain_command_line, libd__get_wide_winmain_command_line);

DEFINE_INTERN_ALIAS(libd__configure_wide_argv, libd__configure_narrow_argv);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") errno_t LIBDCALL
libd__configure_narrow_argv(_crt_argv_mode mode) {
	COMPILER_IMPURE();
	(void)mode;
	return 0;
}

DEFINE_INTERN_ALIAS(libd__initialize_wide_environment, libd__initialize_narrow_environment);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") int LIBDCALL
libd__initialize_narrow_environment(void) {
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.compat.dos") char **LIBDCALL
libd__get_initial_narrow_environment(void) {
	return *libc___p___initenv();
}

INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.compat.dos") char16_t **LIBDCALL
libd__get_initial_wide_environment(void) {
	return *libd___p___winitenv();
}

INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.compat.dos") char *LIBDCALL
libd__get_narrow_winmain_command_line(void) {
	return *libd___p__acmdln();
}

INTERN ATTR_PURE ATTR_SECTION(".text.crt.dos.compat.dos") char16_t *LIBDCALL
libd__get_wide_winmain_command_line(void) {
	return *libd___p__wcmdln();
}

typedef struct _onexit_table_t {
	_onexit_t *_first;
	_onexit_t *_last;
	_onexit_t *_end;
} _onexit_table_t;

DEFINE_PUBLIC_ALIAS(DOS$_initialize_onexit_table, libd__initialize_onexit_table);
DEFINE_PUBLIC_ALIAS(DOS$_register_onexit_function, libd__register_onexit_function);
DEFINE_PUBLIC_ALIAS(DOS$_execute_onexit_table, libd__execute_onexit_table);

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") int LIBDCALL
libd__initialize_onexit_table(_onexit_table_t *self) {
	if unlikely(!self)
		return -1;
	bzero(self, sizeof(*self));
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") int LIBDCALL
libd__register_onexit_function(_onexit_table_t *self, _onexit_t function) {
	if unlikely(!self)
		return -1;
	if (self->_last >= self->_end) {
		_onexit_t *newtab;
		size_t newcnt;
		newcnt = (size_t)(self->_last - self->_first) + 1;
		newtab = (_onexit_t *)realloc(self->_first, newcnt + 1, sizeof(_onexit_t));
		if (!newtab)
			return -1;
		newcnt       = malloc_usable_size(newtab) / sizeof(_onexit_t);
		self->_last  = newtab + (self->_last - self->_first);
		self->_end   = newtab + newcnt;
		self->_first = newtab;
	}
	*self->_last++ = function;
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") int LIBDCALL
libd__execute_onexit_table(_onexit_table_t *self) {
	int result;
	_onexit_t *_first = self->_first;
	_onexit_t *_last  = self->_last;
	libd__initialize_onexit_table(self);
	result = libd__initterm_e(_first, _last);
	free(_first);
	return result;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_COMPAT_C */
