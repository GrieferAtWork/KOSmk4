/*[[[magic
// This file is all about compat stuff, so optimize it for size rather than speed!
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBC_LIBC_COMPAT_C
#define GUARD_LIBC_LIBC_COMPAT_C 1
#define _KOS_SOURCE 1

/*
 * Misc functions needed for ABI compatibility with other platforms.
 */

#include "../api.h"
/**/

#include <hybrid/host.h>
#include <hybrid/sched/atomic-once.h>

#include <asm/pagesize.h>
#include <kos/except.h>
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
#include <nt/processthreadsapi.h>
#include <nt/synchapi.h>
#include <nt/sysinfoapi.h>
#include <nt/types.h>

#include <assert.h>
#include <atomic.h>
#include <elf.h>
#include <fcntl.h>
#include <format-printer.h>
#include <locale.h>
#include <math.h>
#include <paths.h>
#include <pthread.h>
#include <pthread_np.h>
#include <siginfo.h>
#include <signal.h>
#include <stdlib.h> /* exit() */
#include <string.h>
#include <syscall.h>
#include <syslog.h>
#include <uchar.h>
#include <unicode.h>
#include <unistd.h>

#include <libcmdline/encode.h>
#include <libiconv/api.h>

#include "../user/corecrt_startup.h"
#include "../user/stdio-api.h"
#include "../user/stdlib.h"
#include "compat.h"
#include "dl.h"
#include "globals.h"
#include "tls.h"

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

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
INTERN ATTR_SECTION(".data.crt.FILE.locked.read.read") FILE *libc_stdin    = &libc_iob[0]; /* !Relocation: &libc_iob[0] */
INTERN ATTR_SECTION(".data.crt.FILE.locked.write.write") FILE *libc_stdout = &libc_iob[1]; /* !Relocation: &libc_iob[1] */
INTERN ATTR_SECTION(".data.crt.FILE.locked.write.write") FILE *libc_stderr = &libc_iob[2]; /* !Relocation: &libc_iob[2] */
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
	/* DOS doesn't  have copy-relocations,  so we  don't
	 * have to worry about `dlsym("_iob") != &libc_iob'. */
	return libc_iob;
}



/************************************************************************/
/* stdtty (for <conio.h>)                                               */
/************************************************************************/
PRIVATE ATTR_SECTION(".data.crt.dos.conio")
struct iofile_data_novtab libc_stdttyfile_data = IOFILE_DATA_NOVTAB_INIT();
#ifdef AT_FDCTTY
PRIVATE ATTR_SECTION(".data.crt.dos.conio")
FILE libc_stdttyfile = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNBUF | IO_ISATTY, AT_FDCTTY, { 0 }, 0, NULL /*(struct iofile_data *)&libc_stdttyfile_data*/);
#else /* AT_FDCTTY */
PRIVATE ATTR_SECTION(".data.crt.dos.conio")
FILE libc_stdttyfile = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNBUF | IO_ISATTY, -1, { 0 }, 0, NULL /*(struct iofile_data *)&libc_stdttyfile_data*/);
#endif /* !AT_FDCTTY */
PRIVATE ATTR_SECTION(".bss.crt.dos.conio")
FILE *libc_stdtty = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.conio")
pthread_once_t libc_stdtty_initialized = PTHREAD_ONCE_INIT;

#ifndef _PATH_TTY
#define _PATH_TTY "/dev/tty"
#endif /* !_PATH_TTY */

PRIVATE ATTR_SECTION(".text.crt.dos.conio") void
NOTHROW(LIBCCALL libc_stdtty_initialize)(void) {
	/* When KOS's AT_FDCTTY extension is active, every process
	 * can make use of an  implicit file descriptor with  this
	 * name in order to refer to its controlling terminal.
	 *
	 * Trying to use that file descriptor when one does not have
	 * a controlling terminal will fail with EBADF at use  time. */

#ifndef AT_FDCTTY
	/* Lazily open /dev/tty on first access. Note that we
	 * set `O_CLOEXEC' to ensure that the file handle  is
	 * not inherited by child processes! */
	fd_t ttyfd = sys_open(_PATH_TTY, O_RDWR | O_CLOEXEC, 0);
	if likely(E_ISOK(ttyfd))
		libc_stdttyfile.if_fd = ttyfd;
#endif /* !AT_FDCTTY */

	/* Initialize FILE pointers so they don't require relocations. */
	libc_stdttyfile.if_exdata = (struct iofile_data *)&libc_stdttyfile_data;
	libc_stdtty               = &libc_stdttyfile;
}

#undef stdtty
DEFINE_PUBLIC_IDATA(stdtty, libc_resolve_stdtty, __SIZEOF_POINTER__);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.dos.conio")
FILE **NOTHROW(LIBDCALL libc_resolve_stdtty)(void) {
	pthread_once(&libc_stdtty_initialized, &libc_stdtty_initialize);
	return &libc_stdtty;
}







/************************************************************************/
/* Old Glibc stdio compat                                               */
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
	 *   - `__if_pad0 = 0xffffffff;'  in std-stream replacements, causing the high
	 *     32 bits of `io84_IO_read_ptr' to be all 1s and following the assumption
	 *     that libc is loaded somewhere other than the last 4GiB of memory (which
	 *     we can always assume when hosted by a high-memory kernel, which KOS  is
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
	 *   set to ZEROes (which is one of the ways to comply with I/O requirements).
	 */

	/*32|64-bit * .................................... *     32-bit | 64-bit */
	/* 0|  0*/ uint32_t           io84_flags;         /* if_ptr     | if_ptr */
#if __SIZEOF_POINTER__ > 4
	/*     4*/ uint32_t          _io84_pad;           /* -          | if_ptr (cont.) */
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
	byte_t ldsf_zero[sizeof(struct IO_FILE_84) - sizeof(FILE)]; /* Pad with 0-bytes. */
	FILE   ldsf_stdio;                                          /* The actual file object */
#elif __SIZEOF_POINTER__ == 8
	FILE   ldsf_stdio;                                          /* The actual file object */
	byte_t ldsf_zero[sizeof(struct IO_FILE_84) - sizeof(FILE)]; /* Pad with 0-bytes. */
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
};

static_assert(sizeof(struct IO_FILE_84) == sizeof(struct linux_default_stdio_file));
static_assert(sizeof(struct IO_FILE_84) == SIZEOF_IO_FILE_84);

#if __SIZEOF_POINTER__ == 4
#ifndef FILE_HAVE_UOFFSET
#error "Need FILE_HAVE_UOFFSET when sizeof(void *) == 4"
#endif /* !FILE_HAVE_UOFFSET */
INTERN ATTR_SECTION(".data.crt.FILE.std_files") ptrdiff_t file_uoffset = 0;
INTERN WUNUSED ATTR_SECTION(".text.crt.FILE.std_files") FILE *__FCALL
file_calloc(size_t extsize) {
	FILE *result;
	result = (FILE *)calloc(1, file_uoffset + sizeof(FILE) + extsize);
	if likely(result)
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
	result = (byte_t *)dlauxctrl(mainapp, DLAUXCTRL_ELF_SYMADDR, sym);
	if (result == NULL)
		return (FILE *)fallback;

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

	/* XXX: Figure out what's supposed to be different when `is_2_1 == true' */

	/* NOTE: Intentional crash if this Calloc() fails */
	NOEXCEPT_DO(result = (struct linux_default_stdio_file *)Calloc(3, sizeof(struct linux_default_stdio_file)));
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
DEFINE_PUBLIC_IDATA(_IO_2_1_stdin_, linux_stdio_get_2_1_stdin, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA(_IO_2_1_stdout_, linux_stdio_get_2_1_stdout, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA(_IO_2_1_stderr_, linux_stdio_get_2_1_stderr, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA(_IO_stdin_, linux_stdio_get_stdin, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA(_IO_stdout_, linux_stdio_get_stdout, SIZEOF_IO_FILE_84);
DEFINE_PUBLIC_IDATA(_IO_stderr_, linux_stdio_get_stderr, SIZEOF_IO_FILE_84);






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
DEFINE_PUBLIC_IDATA(__new_handler, libc___new_handler, __SIZEOF_POINTER__);
INTERN ATTR_SECTION(".bss.crt.compat.linux.heap") PNEW_HANDLER libc___new_handler = NULL;
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") PNEW_HANDLER *
NOTHROW(LIBCCALL libc___new_handler_cb)(void) {
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
INTERN ATTR_PURE ATTR_SECTION(".text.crt.compat.linux.except") void *
NOTHROW_NCX(LIBCCALL libc___throw_type_match)(void const *catch_type,
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
DEFINE_PUBLIC_ALIAS(__sigvec, libc_sigvec); /* From Glibc 2.0.4 */
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
__pragma_GCC_diagnostic_push_ignored(Wunused_but_set_parameter)

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

__pragma_GCC_diagnostic_pop_ignored(Wunused_but_set_parameter)
#endif /* __i386__ && !__x86_64__ */


/************************************************************************/
/* General compatibility flags                                          */
/************************************************************************/
INTERN ATTR_SECTION(".bss.crt.compat.linux.init")
uintptr_t libc_compat = COMPAT_FLAG_NORMAL;




/************************************************************************/
/* <fpu_control.h>                                                      */
/************************************************************************/
#ifndef __NO_FPU
DECL_END
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
#else /* _FPU_DEFAULT == 0 */
INTERN ATTR_SECTION(".data.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#endif /* _FPU_DEFAULT != 0 */
DEFINE_PUBLIC_ALIAS(__fpu_control, libc___fpu_control);

DEFINE_PUBLIC_ALIAS(__getfpucw, libc___getfpucw);
INTERN ATTR_PURE ATTR_SECTION(".text.crt.math.float") fpu_control_t
NOTHROW_NCX(LIBCCALL libc___getfpucw)(void) {
	fpu_control_t word;
	_FPU_GETCW(word);
	return word;
}

/* >> __setfpucw(3)
 * Function called by old linux applications with `__fpu_control' as argument. */
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
#endif /* _FPU_GETCW */

/* s.a. `__ieee754_inf()' in `<libm/inf.h>'
 *
 * User-programs would actually link against this symbol like:
 * >> extern double __huge_val;
 * (Assuming `double' is `__IEEE754_DOUBLE_TYPE__') */
DEFINE_PUBLIC_ALIAS(__huge_val, libc___huge_val);
DEFINE_PUBLIC_ALIAS(_HUGE, libc___huge_val); /* DOS alias for the same constant */
INTERN_CONST ATTR_SECTION(".rodata.crt.math.float")
uint32_t const libc___huge_val[2] = {
	UINT32_C(0x7ff00000),
	UINT32_C(0x00000000)
};

#endif /* !__NO_FPU */





/************************************************************************/
/* Misc Glibc functions that don't appear in headers                    */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(create_module, libc_create_module);
INTERN ATTR_SECTION(".text.crt.compat.glibc") caddr_t
NOTHROW_NCX(LIBCCALL libc_create_module)(char const *name, size_t size) {
	/* Not implemented on KOS (and won't be because not implemented on (modern) linux, either) */
	(void)name;
	(void)size;
	return (caddr_t)libc_seterrno(ENOSYS);
}

DEFINE_PUBLIC_ALIAS(delete_module, libc_delete_module);
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_delete_module)(char const *name, oflag_t flags) {
	errno_t error = sys_delete_module(name, flags);
	return libc_seterrno_syserr(error);
}

struct kernel_sym;
DEFINE_PUBLIC_ALIAS(get_kernel_syms, libc_get_kernel_syms);
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_get_kernel_syms)(struct kernel_sym *table) {
	/* Not implemented on KOS (and won't be because not implemented on (modern) linux, either) */
	(void)table;
	return libc_seterrno(ENOSYS);
}

DEFINE_PUBLIC_ALIAS(init_module, libc_init_module);
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_init_module)(void const *module_image,
                                       size_t len, char const *uargs) {
	errno_t error = sys_init_module(module_image, len, uargs);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(query_module, libc_query_module);
INTERN ATTR_SECTION(".text.crt.compat.glibc") int
NOTHROW_NCX(LIBCCALL libc_query_module)(char const *name, int which, void *buf,
                                        size_t bufsize, size_t *ret) {
	/* Not implemented on KOS (and won't be because not implemented on (modern) linux, either) */
	(void)name;
	(void)which;
	(void)buf;
	(void)bufsize;
	(void)ret;
	return libc_seterrno(ENOSYS);
}

DEFINE_PUBLIC_ALIAS(__call_tls_dtors, libc___call_tls_dtors);
INTERN ATTR_SECTION(".text.crt.compat.glibc")
void LIBCCALL libc___call_tls_dtors(void) {
	/* Finalize TLS objects for the calling thread (c++11-specific) */
	dlauxctrl(NULL, DLAUXCTRL_RUNTLSFINI);
}

/************************************************************************/
/* >> extern void *__libc_stack_end;                                    */
/* Resolves to the main thread's stack end address                      */
/************************************************************************/
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc") void *libc___libc_stack_end = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc")
pthread_once_t libc___libc_stack_end_initialized = PTHREAD_ONCE_INIT;
PRIVATE ATTR_SECTION(".text.crt.compat.glibc") void
NOTHROW_NCX(LIBCCALL libc___libc_stack_end_initialize)(void) {
	stack_t info;
	void *end_of_stack = NULL;
	if (pthread_stackseg_np(pthread_mainthread_np(), &info) == 0)
		end_of_stack = (byte_t *)info.ss_sp + info.ss_size;
	libc___libc_stack_end = end_of_stack;
}

DEFINE_PUBLIC_IDATA(__libc_stack_end, libc_resolve___libc_stack_end, __SIZEOF_POINTER__);
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc")
void **NOTHROW_NCX(LIBCCALL libc_resolve___libc_stack_end)(void) {
	pthread_once(&libc___libc_stack_end_initialized,
	             &libc___libc_stack_end_initialize);
	return &libc___libc_stack_end;
}







/************************************************************************/
/* Misc libc4/5 stuff that doesn't appear in headers                    */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(getdents, libc_getdents);
DEFINE_PUBLIC_ALIAS(__getdents, libc_getdents);
DEFINE_PUBLIC_ALIAS(__libc_getdents, libc_getdents);
INTERN ATTR_SECTION(".text.crt.compat.linux") ssize_t
NOTHROW_NCX(LIBCCALL libc_getdents)(fd_t fd, struct linux_dirent *buf, size_t count) {
	ssize_t error = sys_getdents(fd, buf, count);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(getdents64, libc_getdents64);
INTERN ATTR_SECTION(".text.crt.compat.linux") ssize_t
NOTHROW_NCX(LIBCCALL libc_getdents64)(fd_t fd, struct linux_dirent64 *buf, size_t count) {
	ssize_t error = sys_getdents64(fd, buf, count);
	return libc_seterrno_syserr(error);
}






/* At  least that's the  one I've been  using for ABI reference.
 * Note however that KOS's libc _is_ providing various functions
 * that have since been removed from Glibc, meaning that this is
 * really kind-of meaningless in terms of information... */
INTDEF char const libc_gnu_libc_version_full[];
INTDEF char const libc_gnu_nptl_version_full[];
INTERN_CONST ATTR_SECTION(".rodata.crt.compat.glibc") char const libc_gnu_libc_version_full[] = "glibc 2.32"; /* _CS_GNU_LIBC_VERSION */
INTERN_CONST ATTR_SECTION(".rodata.crt.compat.glibc") char const libc_gnu_nptl_version_full[] = "NPTL 2.32";  /* _CS_GNU_LIBPTHREAD_VERSION */
#define libc_gnu_libc_version (libc_gnu_libc_version_full + 6)

PRIVATE ATTR_SECTION(".rodata.crt.compat.glibc")
char const libc_gnu_libc_release[] = "KOS";

DEFINE_PUBLIC_ALIAS(gnu_get_libc_version, libc_gnu_get_libc_version);
DEFINE_PUBLIC_ALIAS(gnu_get_libc_release, libc_gnu_get_libc_release);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc") char const *
NOTHROW_NCX(LIBCCALL libc_gnu_get_libc_version)(void) {
	return libc_gnu_libc_version;
}
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc") char const *
NOTHROW_NCX(LIBCCALL libc_gnu_get_libc_release)(void) {
	return libc_gnu_libc_release;
}

/* String stolen from the shared `libc.so.5' file I'm using as reference.
 * If  there's one version  which KOS's emulation of  linux libc tries to
 * follow in terms of ABI specs, it's this one.
 *
 * Oh: and this string is exported as:
 * >> extern char const *__linux_C_lib_version; */
PRIVATE ATTR_SECTION(".rodata.crt.compat.linux") char const
libc_linux_C_lib_version_string[] = "@(#) The Linux C library 5.3.12";
PRIVATE ATTR_SECTION(".bss.crt.compat.linux") char const *
libc___linux_C_lib_version = NULL;

DEFINE_PUBLIC_IDATA(__linux_C_lib_version, libc___p___linux_C_lib_version, __SIZEOF_POINTER__);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.linux") char const **
NOTHROW_NCX(LIBCCALL libc___p___linux_C_lib_version)(void) {
	if (libc___linux_C_lib_version == NULL)
		libc___linux_C_lib_version = libc_linux_C_lib_version_string;
	return &libc___linux_C_lib_version;
}




/* Glibc contains exports `iconv()', `iconv_open()' and `iconv_close()'.
 * On  KOS, these functions are normally exported by `libiconv', but for
 * binary compatibility, libc  also exports them  as IFUNC symbols  that
 * lazily load+resolve-to the symbols from libiconv at runtime. */
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc") void *libc_libiconv = NULL;
PRIVATE ATTR_SECTION(".rodata.crt.compat.glibc")
char const libc_init_libiconv_failed_msg[] = "[libc] failed to load libiconv: %s\n";
PRIVATE ATTR_NORETURN ATTR_SECTION(".text.crt.compat.glibc")
void LIBCCALL libc_init_libiconv_failed(void) {
	abortf(libc_init_libiconv_failed_msg, dlerror());
}
PRIVATE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc")
void *LIBCCALL libc_get_libiconv(void) {
	void *result = libc_libiconv;
	if (!result) {
		result = dlopen(LIBICONV_LIBRARY_NAME, RTLD_LAZY | RTLD_LOCAL);
		if unlikely(!result)
			libc_init_libiconv_failed();
		if (!atomic_cmpxch(&libc_libiconv, NULL, result)) {
			dlclose(result);
			result = libc_libiconv;
		}
	}
	return result;
}
INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc") NONNULL((1))
void *FCALL libc_get_libiconv_symbol(char const *__restrict name) {
	void *lib, *res;
	lib = libc_get_libiconv();
	res = dlsym(lib, name);
	if unlikely(!res)
		libc_init_libiconv_failed();
	return res;
}

#define DEFINE_LIBICONV_AUTORESOLVE_SYMBOL(symbol_name)                       \
	DEFINE_PUBLIC_IFUNC(symbol_name, libc_resolve_libiconv_##symbol_name);    \
	PRIVATE ATTR_SECTION(".rodata.crt.compat.glibc") char const               \
	libc_libiconv_symname_##symbol_name[] = #symbol_name;                     \
	INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc")     \
	void *LIBCCALL libc_resolve_libiconv_##symbol_name(void) {                \
		return libc_get_libiconv_symbol(libc_libiconv_symname_##symbol_name); \
	}
DEFINE_LIBICONV_AUTORESOLVE_SYMBOL(iconv)
DEFINE_LIBICONV_AUTORESOLVE_SYMBOL(iconv_open)
DEFINE_LIBICONV_AUTORESOLVE_SYMBOL(iconv_close)
#undef DEFINE_LIBICONV_AUTORESOLVE_SYMBOL






/* Glibc's version of `dlgethandle(3D)' */
DEFINE_PUBLIC_ALIAS(_dl_find_dso_for_object, libc__dl_find_dso_for_object);
INTERN ATTR_SECTION(".text.crt.compat.glibc") struct link_map *
NOTHROW(LIBCCALL libc__dl_find_dso_for_object)(ElfW(Addr) addr) {
	void *handle;
	struct link_map *result;
	handle = dlgethandle((void *)addr, DLGETHANDLE_FNORMAL);
	result = (struct link_map *)handle;
	if unlikely(dlinfo(handle, RTLD_DI_LINKMAP, &result))
		result = (struct link_map *)handle;
	return result;
}






/* Some old Glibc dl function wrappers */
DEFINE_PUBLIC_ALIAS(_dl_tls_symaddr, libc__dl_tls_symaddr);
INTERN ATTR_SECTION(".text.crt.compat.glibc") void * /* From: `Glibc-2.3.2' */
NOTHROW(LIBCCALL libc__dl_tls_symaddr)(struct link_map *lm, ElfW(Sym) const *sym) {
	void *base = dltlsaddr((void *)lm);
	if unlikely(!base)
		abortf("[_dl_tls_symaddr] failed to allocate tls: %s", dlerror());
	return (byte_t *)base + sym->st_value;
}

#ifdef __ARCH_PAGESIZE
DEFINE_PUBLIC_ALIAS(_dl_pagesize, libc__dl_pagesize);
INTERN ATTR_SECTION(".data.crt.compat.glibc") size_t libc__dl_pagesize = __ARCH_PAGESIZE;
#else /* __ARCH_PAGESIZE */
DEFINE_PUBLIC_IDATA(_dl_pagesize, libc_resolve__dl_pagesize, __SIZEOF_SIZE_T__);
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc") size_t libc_saved__dl_pagesize = 0;
INTERN ATTR_SECTION(".text.crt.compat.glibc") size_t *
NOTHROW(LIBCCALL libc_resolve__dl_pagesize)(void) {
	if (libc_saved__dl_pagesize == 0)
		libc_saved__dl_pagesize = getpagesize();
	return &libc_saved__dl_pagesize;
}
#endif /* !__ARCH_PAGESIZE */

DEFINE_PUBLIC_ALIAS(_dl_get_origin, libc__dl_get_origin);
INTERN ATTR_SECTION(".text.crt.compat.glibc") char * /* From: `Glibc-2.3.2' */
NOTHROW(LIBCCALL libc__dl_get_origin)(void) {
	char *result;
	char *progname = program_invocation_name;
	size_t pathlen = strroff(progname, '/');
	if (pathlen == (size_t)-1) {
		result = strdup("/");
	} else {
		/* Return without trailing slash in this case! */
		result = (char *)malloc(pathlen + 1, sizeof(char));
		if likely(result)
			*(char *)mempcpy(result, progname, pathlen, sizeof(char)) = '\0';
	}
	/* For some reason, this function returns `(char *)-1' on malloc error. */
	if unlikely(!result)
		result = (char *)-1;
	return result;
}






/* Glibc "fast" string functions from before Glibc 2.24 */
#undef GLIBC_MEMCPY_SMALL_USE_UNALIGNED
#if (defined(__i386__) || defined(__x86_64__) || \
     defined(__mc68020__) || defined(__s390__))
#define GLIBC_MEMCPY_SMALL_USE_UNALIGNED
#endif /* ... */

DEFINE_PUBLIC_ALIAS(__strcpy_small, libc___strcpy_small);
DEFINE_PUBLIC_ALIAS(__mempcpy_small, libc___mempcpy_small);
DEFINE_PUBLIC_ALIAS(__stpcpy_small, libc___stpcpy_small);
#ifdef GLIBC_MEMCPY_SMALL_USE_UNALIGNED
INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___strcpy_small)(void *dest,
                                          uint16_t src0_2, uint16_t src4_2,
                                          uint32_t src0_4, uint32_t src4_4,
                                          size_t srclen) {
#define W(T, off) (*(T *)((byte_t *)dest + off))
	switch (srclen) {
	case 1: W(uint8_t, 0) = '\0'; break;
	case 2: W(uint16_t, 0) = src0_2; break;
	case 3: W(uint16_t, 0) = src0_2; W(uint8_t, 2) = '\0'; break;
	case 4: W(uint32_t, 0) = src0_4; break;
	case 5: W(uint32_t, 0) = src0_4; W(uint8_t, 4) = '\0'; break;
	case 6: W(uint32_t, 0) = src0_4; W(uint16_t, 4) = src4_2; break;
	case 7: W(uint32_t, 0) = src0_4; W(uint16_t, 4) = src4_2; W(uint8_t, 6) = '\0'; break;
	case 8: W(uint32_t, 0) = src0_4; W(uint32_t, 4) = src4_4; break;
	default: break;
	}
	return dest;
#undef W
}

INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___mempcpy_small)(void *dest, uint8_t src0_1, uint8_t src2_1,
                                           uint8_t src4_1, uint8_t src6_1, uint16_t src0_2,
                                           uint16_t src4_2, uint32_t src0_4,
                                           uint32_t src4_4, size_t srclen) {
#define W(T, off) (*(T *)((byte_t *)dest + off))
	switch (srclen) {
	case 1: W(uint8_t, 0) = src0_1; break;
	case 2: W(uint16_t, 0) = src0_2; break;
	case 3: W(uint16_t, 0) = src0_2; W(uint8_t, 2) = src2_1; break;
	case 4: W(uint32_t, 0) = src0_4; break;
	case 5: W(uint32_t, 0) = src0_4; W(uint8_t, 4) = src4_1; break;
	case 6: W(uint32_t, 0) = src0_4; W(uint16_t, 4) = src4_2; break;
	case 7: W(uint32_t, 0) = src0_4; W(uint16_t, 4) = src4_2; W(uint8_t, 6) = src6_1; break;
	case 8: W(uint32_t, 0) = src0_4; W(uint32_t, 4) = src4_4; break;
	default: break;
	}
	return dest;
#undef W
}

INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___stpcpy_small)(void *dest,
                                          uint16_t src0_2, uint16_t src4_2,
                                          uint32_t src0_4, uint32_t src4_4,
                                          size_t srclen) {
	return (byte_t *)libc___strcpy_small(dest, src0_2, src4_2, src0_4, src4_4, srclen) + srclen;
}
#else /* GLIBC_MEMCPY_SMALL_USE_UNALIGNED */
#define DEFINE_glibc_memcpy_small_arr(N) \
	typedef struct __ATTR_PACKED {       \
		byte_t arr[N];                   \
	} glibc_memcpy_small_arr##N
DEFINE_glibc_memcpy_small_arr(2);
DEFINE_glibc_memcpy_small_arr(3);
DEFINE_glibc_memcpy_small_arr(4);
DEFINE_glibc_memcpy_small_arr(5);
DEFINE_glibc_memcpy_small_arr(6);
DEFINE_glibc_memcpy_small_arr(7);
DEFINE_glibc_memcpy_small_arr(8);
#undef DEFINE_glibc_memcpy_small_arr

INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___strcpy_small)(void *dest,
                                          glibc_memcpy_small_arr2 src2, glibc_memcpy_small_arr3 src3,
                                          glibc_memcpy_small_arr4 src4, glibc_memcpy_small_arr5 src5,
                                          glibc_memcpy_small_arr6 src6, glibc_memcpy_small_arr7 src7,
                                          glibc_memcpy_small_arr8 src8, size_t srclen) {
#define W(T) (*(T *)dest)
	switch (srclen) {
	case 1: W(uint8_t) = '\0'; break;
	case 2: W(glibc_memcpy_small_arr2) = src2; break;
	case 3: W(glibc_memcpy_small_arr3) = src3; break;
	case 4: W(glibc_memcpy_small_arr4) = src4; break;
	case 5: W(glibc_memcpy_small_arr5) = src5; break;
	case 6: W(glibc_memcpy_small_arr6) = src6; break;
	case 7: W(glibc_memcpy_small_arr7) = src7; break;
	case 8: W(glibc_memcpy_small_arr8) = src8; break;
	}
	return dest;
#undef W
}

INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___mempcpy_small)(void *dest, uint8_t src1,
                                           glibc_memcpy_small_arr2 src2, glibc_memcpy_small_arr3 src3,
                                           glibc_memcpy_small_arr4 src4, glibc_memcpy_small_arr5 src5,
                                           glibc_memcpy_small_arr6 src6, glibc_memcpy_small_arr7 src7,
                                           glibc_memcpy_small_arr8 src8, size_t srclen) {
#define W(T) (*(T *)dest)
	switch (srclen) {
	case 1: W(uint8_t) = src1; break;
	case 2: W(glibc_memcpy_small_arr2) = src2; break;
	case 3: W(glibc_memcpy_small_arr3) = src3; break;
	case 4: W(glibc_memcpy_small_arr4) = src4; break;
	case 5: W(glibc_memcpy_small_arr5) = src5; break;
	case 6: W(glibc_memcpy_small_arr6) = src6; break;
	case 7: W(glibc_memcpy_small_arr7) = src7; break;
	case 8: W(glibc_memcpy_small_arr8) = src8; break;
	}
	return (byte_t *)dest + srclen;
#undef W
}

INTERN ATTR_SECTION(".text.crt.compat.glibc") void *
NOTHROW_NCX(LIBCCALL libc___stpcpy_small)(void *dest,
                                          glibc_memcpy_small_arr2 src2, glibc_memcpy_small_arr3 src3,
                                          glibc_memcpy_small_arr4 src4, glibc_memcpy_small_arr5 src5,
                                          glibc_memcpy_small_arr6 src6, glibc_memcpy_small_arr7 src7,
                                          glibc_memcpy_small_arr8 src8, size_t srclen) {
	return libc___strcpy_small(dest, src2, src3, src4, src5, src6, src7, src8, srclen) + srclen;
}
#endif /* !GLIBC_MEMCPY_SMALL_USE_UNALIGNED */









/************************************************************************/
/* Libc `_start()' function handling.                                   */
/************************************************************************/
PRIVATE ATTR_SECTION(".rodata.crt.compat.glibc") char const libc_banner[] =
"==========================================================================\n"
"KOS System C Library.\n"
"==========================================================================\n"
"Copyright (c) 2019-2024 Griefer@Work\n"
"\n"
"This software is provided 'as-is', without any express or implied\n"
"warranty. In no event will the authors be held liable for any damages\n"
"arising from the use of this software.\n"
"\n"
"Permission is granted to anyone to use this software for any purpose,\n"
"including commercial applications, and to alter it and redistribute it\n"
"freely, subject to the following restrictions:\n"
"\n"
"1. The origin of this software must not be misrepresented; you must not\n"
"   claim that you wrote the original software. If you use this software\n"
"   in a product, an acknowledgement (see the following) in the product\n"
"   documentation is required:\n"
"   Portions Copyright (c) 2019-2024 Griefer@Work\n"
"2. Altered source versions must be plainly marked as such, and must not be\n"
"   misrepresented as being the original software.\n"
"3. This notice may not be removed or altered from any source distribution.\n"
"==========================================================================\n"
;

/* Program entry point for when you do `exec("/lib/libc.so")' */
DEFINE_PUBLIC_ALIAS(__libc_print_version, libc_exec_print_version); /* From Glibc 2.0.4 */
DEFINE_PUBLIC_ALIAS(__libc_main, libc_exec_main);                   /* From Glibc 2.0.4 */
INTERN ATTR_SECTION(".text.crt.compat.glibc")
void libc_exec_print_version(void) {
	sys_write(STDOUT_FILENO, libc_banner, sizeof(libc_banner) - sizeof(char));
	sys_exit_group(0);
}
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.compat.glibc")
void libc_exec_main(void) {
	libc_exec_print_version();
	sys_exit_group(0);
}




/************************************************************************/
/* Misc MSVCRT functions                                                */
/************************************************************************/

typedef struct {
	_crt_app_type newmode;
} _startupinfo;

DEFINE_PUBLIC_ALIAS(DOS$__lconv_init, libd___lconv_init);
DEFINE_PUBLIC_ALIAS(DOS$__getmainargs, libd___getmainargs);
DEFINE_PUBLIC_ALIAS(DOS$__wgetmainargs, libd___wgetmainargs);
DEFINE_PUBLIC_ALIAS(DOS$_XcptFilter, libd__XcptFilter);
DEFINE_PUBLIC_ALIAS(DOS$__CppXcptFilter, libd__XcptFilter);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler2, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler3, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler_3, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler4, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$_except_handler4_common, libd__except_handler4);
DEFINE_PUBLIC_ALIAS(DOS$__C_specific_handler, libd__except_handler4);

INTERN ATTR_SECTION(".text.crt.dos.application.init") void LIBDCALL
libd___lconv_init(void) {
	CRT_UNIMPLEMENTED("__lconv_init");
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libd___getmainargs)(int *pargc, char ***pargv,
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
		libc__set_app_type(pstartinfo->newmode);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libd___wgetmainargs)(int *pargc, char16_t ***pargv,
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
		libc__set_app_type(pstartinfo->newmode);
	return 0;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.except") int LIBDCALL
libd__XcptFilter(u32 xno, struct _EXCEPTION_POINTERS *infp_ptrs) {
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_XcptFilter(%" PRIu32 ", %p)", xno, infp_ptrs);
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

DEFINE_PUBLIC_ALIAS(DOS$_vacopy, libd__vacopy);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") NONNULL((1)) void
NOTHROW(LIBDCALL libd__vacopy)(void **p_dstap, void *srcap) {
	*p_dstap = srcap;
}

DEFINE_PUBLIC_ALIAS(DOS$_freea, libd__freea);
DEFINE_PUBLIC_ALIAS(DOS$_freea_s, libd__freea);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void
NOTHROW(LIBDCALL libd__freea)(void *ptr) {
	if (ptr) {
		ptr = (byte_t *)ptr - (2 * sizeof(void *));
		if (*(uint32_t const *)ptr == 0xDDDD)
			free(ptr);
	}
}

PRIVATE ATTR_SECTION(".bss.crt.dos.compat.dos") struct lconv *libd___lconv = NULL;
DEFINE_PUBLIC_IDATA(__lconv, libd___p___lconv, __SIZEOF_POINTER__);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") struct lconv **
NOTHROW(LIBDCALL libd___p___lconv)(void) {
	if (libd___lconv == NULL)
		libd___lconv = localeconv();
	return &libd___lconv;
}

DEFINE_PUBLIC_ALIAS(DOS$__initialize_lconv_for_unsigned_char, libd___initialize_lconv_for_unsigned_char);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void
NOTHROW(LIBDCALL libd___initialize_lconv_for_unsigned_char)(void) {
	struct lconv *lc       = localeconv();
	lc->int_frac_digits    = (char)(unsigned char)0xff;
	lc->frac_digits        = (char)(unsigned char)0xff;
	lc->p_cs_precedes      = (char)(unsigned char)0xff;
	lc->p_sep_by_space     = (char)(unsigned char)0xff;
	lc->n_cs_precedes      = (char)(unsigned char)0xff;
	lc->n_sep_by_space     = (char)(unsigned char)0xff;
	lc->p_sign_posn        = (char)(unsigned char)0xff;
	lc->n_sign_posn        = (char)(unsigned char)0xff;
/*	lc->int_p_cs_precedes  = (char)(unsigned char)0xff; */
/*	lc->int_p_sep_by_space = (char)(unsigned char)0xff; */
/*	lc->int_n_cs_precedes  = (char)(unsigned char)0xff; */
/*	lc->int_n_sep_by_space = (char)(unsigned char)0xff; */
/*	lc->int_p_sign_posn    = (char)(unsigned char)0xff; */
/*	lc->int_n_sign_posn    = (char)(unsigned char)0xff; */
}

#ifdef __LIBCCALL_IS_LIBDCALL
#define libd_exit libc_exit
#endif /* __LIBCCALL_IS_LIBDCALL */

PRIVATE ATTR_SECTION(".bss.crt.dos.compat.dos") void (LIBDCALL *libd__aexit_rtn)(int) = NULL;
DEFINE_PUBLIC_IDATA(DOS$_aexit_rtn, libd___p__aexit_rtn, __SIZEOF_POINTER__);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void *
NOTHROW(LIBDCALL libd___p__aexit_rtn)(void) {
	if (libd__aexit_rtn == NULL)
		libd__aexit_rtn = &libd_exit;
	return &libd__aexit_rtn;
}

DEFINE_PUBLIC_ALIAS(DOS$__CxxCallUnwindDelDtor, libd___CxxCallUnwindDelDtor);
DEFINE_PUBLIC_ALIAS(DOS$__CxxCallUnwindStdDelDtor, libd___CxxCallUnwindDelDtor);
DEFINE_PUBLIC_ALIAS(DOS$__CxxCallUnwindDtor, libd___CxxCallUnwindDtor);
DEFINE_PUBLIC_ALIAS(DOS$__CxxCallUnwindVecDtor, libd___CxxCallUnwindVecDtor);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void *
NOTHROW(LIBDCALL libd___CxxCallUnwindVecDtor)(void *(LIBDCALL *func)(void *a, void *b, void *c, void *d),
                                              void *a, void *b, void *c, void *d) {
	return (*func)(a, b, c, d);
}
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd___CxxCallUnwindDelDtor, libd___CxxCallUnwindVecDtor);
DEFINE_INTERN_ALIAS(libd___CxxCallUnwindDtor, libd___CxxCallUnwindVecDtor);
#else /* __LIBDCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void *
NOTHROW(LIBDCALL libd___CxxCallUnwindDelDtor)(void *(LIBDCALL *func)(void *arg), void *arg) {
	return (*func)(arg);
}
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void *
NOTHROW(LIBDCALL libd___CxxCallUnwindDtor)(void *(LIBDCALL *func)(void)) {
	return (*func)();
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */


/************************************************************************/
/* _commode                                                             */
/************************************************************************/
INTERN ATTR_SECTION(".bss.crt.dos.application.init") int libd__commode = 0;
/*DEFINE_PUBLIC_IDATA(DOS$_commode, libd___p__commode, __SIZEOF_POINTER__);*/
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
INTERN ATTR_SECTION(".data.crt.dos.application.init") unsigned int libd___mb_cur_max = 7;
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.dos.application.init")
int *LIBDCALL libd___p___mb_cur_max(void) {
	COMPILER_IMPURE();
	return (int *)&libd___mb_cur_max;
}


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
	void *k32 = atomic_read(&libkernel32);
	if (k32)
		return k32;
	k32 = dlopen("libkernel32.so", RTLD_LAZY | RTLD_LOCAL);
	if unlikely(!k32)
		abortf("[libc] Failed to load 'libkernel32.so': %s", dlerror());
	if (!atomic_cmpxch(&libkernel32, NULL, k32)) {
		dlclose(k32);
		k32 = atomic_read(&libkernel32);
	}
	return k32;
}

/* Lazily load `libkernel32.so' (if not done already), and return the
 * address  of the named  `symbol_name'. If non-existent, `_Exit(1)'. */
ATTR_SECTION(".text.crt.dos.compat.dos")
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *LIBCCALL
libd_requirek32(char const *__restrict symbol_name) {
	void *result = dlsym(libd_getk32(), symbol_name);
	if unlikely(!result)
		abortf("[libc] Failed to load '%s' from 'libkernel32.so': %s", symbol_name, dlerror());
	return result;
}

#define DEFINE_KERNEL32_RESOLVER(name)                         \
	INTERN ATTR_SECTION(".text.crt.dos.compat.dos")            \
	typeof(&name) libd_resolve_##name(void) {                  \
		static typeof(&name) pdynK32##name = NULL;             \
		if (!pdynK32##name)                                    \
			*(void **)&pdynK32##name = libd_requirek32(#name); \
		return pdynK32##name;                                  \
	}
/*[[[deemon
for (local name: {
	"GetModuleFileNameW",
	"GetModuleHandleW",
	"LoadLibraryExW",
	"InitializeCriticalSectionEx",
	"GetCurrentThread",
	"SetUnhandledExceptionFilter",
	"UnhandledExceptionFilter",
	"TerminateProcess",
	"GetCurrentProcess",
	"GetTickCount64",
}) {
	print("#undef ", name);
	print("DEFINE_KERNEL32_RESOLVER(", name, ")");
	print("#define ", name, " (*libd_resolve_", name, "())");
}
]]]*/
#undef GetModuleFileNameW
DEFINE_KERNEL32_RESOLVER(GetModuleFileNameW)
#define GetModuleFileNameW (*libd_resolve_GetModuleFileNameW())
#undef GetModuleHandleW
DEFINE_KERNEL32_RESOLVER(GetModuleHandleW)
#define GetModuleHandleW (*libd_resolve_GetModuleHandleW())
#undef LoadLibraryExW
DEFINE_KERNEL32_RESOLVER(LoadLibraryExW)
#define LoadLibraryExW (*libd_resolve_LoadLibraryExW())
#undef InitializeCriticalSectionEx
DEFINE_KERNEL32_RESOLVER(InitializeCriticalSectionEx)
#define InitializeCriticalSectionEx (*libd_resolve_InitializeCriticalSectionEx())
#undef GetCurrentThread
DEFINE_KERNEL32_RESOLVER(GetCurrentThread)
#define GetCurrentThread (*libd_resolve_GetCurrentThread())
#undef SetUnhandledExceptionFilter
DEFINE_KERNEL32_RESOLVER(SetUnhandledExceptionFilter)
#define SetUnhandledExceptionFilter (*libd_resolve_SetUnhandledExceptionFilter())
#undef UnhandledExceptionFilter
DEFINE_KERNEL32_RESOLVER(UnhandledExceptionFilter)
#define UnhandledExceptionFilter (*libd_resolve_UnhandledExceptionFilter())
#undef TerminateProcess
DEFINE_KERNEL32_RESOLVER(TerminateProcess)
#define TerminateProcess (*libd_resolve_TerminateProcess())
#undef GetCurrentProcess
DEFINE_KERNEL32_RESOLVER(GetCurrentProcess)
#define GetCurrentProcess (*libd_resolve_GetCurrentProcess())
#undef GetTickCount64
DEFINE_KERNEL32_RESOLVER(GetTickCount64)
#define GetTickCount64 (*libd_resolve_GetTickCount64())
/*[[[end]]]*/
#undef DEFINE_KERNEL32_RESOLVER

DEFINE_PUBLIC_ALIAS(DOS$__crtUnhandledException, libd___crtUnhandledException);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos")
LONG LIBDCALL libd___crtUnhandledException(struct _EXCEPTION_POINTERS *pointers) {
	SetUnhandledExceptionFilter(NULL);
	return UnhandledExceptionFilter((struct _EXCEPTION_POINTERS *)pointers);
}

DEFINE_PUBLIC_ALIAS(DOS$__crtTerminateProcess, libd___crtTerminateProcess);
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.dos.compat.dos")
void LIBDCALL libd___crtTerminateProcess(UINT exit_code) {
	TerminateProcess(GetCurrentProcess(), exit_code);
	abort();
}

#ifdef __x86_64__
#define __LIBDCALL_IS_WINAPI
#elif defined(__i386__)
#undef __LIBDCALL_IS_WINAPI
#endif /* ... */

#ifdef __LIBDCALL_IS_WINAPI
#define DEFINE_KERNEL32_FORWARDER_FUNCTION(T_RETURN, cc, name, params, k32name, args) \
	DEFINE_PUBLIC_IFUNC(DOS$##name, libd_resolve_##k32name);
#else /* __LIBDCALL_IS_WINAPI */
#define DEFINE_KERNEL32_FORWARDER_FUNCTION(T_RETURN, cc, name, params, k32name, args) \
	DEFINE_PUBLIC_ALIAS(DOS$##name, libd_##name);                                     \
	INTERN ATTR_SECTION(".text.crt.dos.compat.dos")                                   \
	T_RETURN cc libd_##name params {                                                  \
		return k32name args;                                                          \
	}
#endif /* !__LIBDCALL_IS_WINAPI */

/* TODO: __crtCreateEventExW */
/* TODO: __crtGetFileInformationByHandleEx */
/* TODO: __crtSetFileInformationByHandle */

/* TODO: __crtCompareStringA */
/* TODO: __crtCompareStringW */
/* TODO: __crtLCMapStringA */
/* TODO: __crtLCMapStringW */

/* TODO: __crtCreateSemaphoreExW */

/* TODO: ___crtCreateSemaphoreExW$A24 */

/* TODO: __crtGetLocaleInfoW */
/* TODO: __crtGetStringTypeW */

/* TODO: __crtCaptureCurrentContext */
/* TODO: __crtCapturePreviousContext */

/* TODO: __crtCompareStringEx */
/* TODO: __crtCreateSymbolicLinkW */
/* TODO: __crtEnumSystemLocalesEx */
/* TODO: __crtFlsAlloc */
/* TODO: __crtFlsFree */
/* TODO: __crtFlsGetValue */
/* TODO: __crtFlsSetValue */
/* TODO: __crtGetDateFormatEx */
/* TODO: __crtGetLocaleInfoEx */
/* TODO: __crtGetShowWindowMode */
/* TODO: __crtGetTimeFormatEx */
/* TODO: __crtGetUserDefaultLocaleName */
/* TODO: __crtIsPackagedApp */
/* TODO: __crtIsValidLocaleName */
/* TODO: __crtLCMapStringEx */
/* TODO: __crtSetThreadStackGuarantee */
DEFINE_KERNEL32_FORWARDER_FUNCTION(DWORD, LIBDCALL, __vcrt_GetModuleFileNameW,
                                   (HMODULE hModule, LPWSTR lpFilename, DWORD nSize),
                                   GetModuleFileNameW, (hModule, lpFilename, nSize))
DEFINE_KERNEL32_FORWARDER_FUNCTION(HMODULE, LIBDCALL, __vcrt_GetModuleHandleW,
                                   (LPCWSTR lpFilename),
                                   GetModuleHandleW, (lpFilename))
DEFINE_KERNEL32_FORWARDER_FUNCTION(HMODULE, LIBDCALL, __vcrt_LoadLibraryExW,
                                   (LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags),
                                   LoadLibraryExW, (lpLibFileName, hFile, dwFlags))
#ifdef __LIBDCALL_IS_WINAPI
DEFINE_PUBLIC_IFUNC(DOS$__crtInitializeCriticalSectionEx, libd_resolve_InitializeCriticalSectionEx);
#else /* __LIBDCALL_IS_WINAPI */
DEFINE_PUBLIC_ALIAS(DOS$__crtInitializeCriticalSectionEx, libd___vcrt_InitializeCriticalSectionEx);
#endif /* !__LIBDCALL_IS_WINAPI */
DEFINE_KERNEL32_FORWARDER_FUNCTION(WINBOOL, LIBDCALL, __vcrt_InitializeCriticalSectionEx,
                                   (LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD dwFlags),
                                   InitializeCriticalSectionEx, (lpCriticalSection, dwSpinCount, dwFlags))
DEFINE_KERNEL32_FORWARDER_FUNCTION(LPTOP_LEVEL_EXCEPTION_FILTER, LIBDCALL, __crtSetUnhandledExceptionFilter,
                                   (LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter),
                                   SetUnhandledExceptionFilter, (lpTopLevelExceptionFilter))
/*DEFINE_KERNEL32_FORWARDER_FUNCTION(HANDLE, LIBDCALL, __threadhandle, (void), GetCurrentThread, ())*/
DEFINE_PUBLIC_IFUNC(DOS$__threadhandle, libd_resolve_GetCurrentThread);
/*DEFINE_KERNEL32_FORWARDER_FUNCTION(ULONGLONG, LIBDCALL, __crtGetTickCount64, (void), GetTickCount64, ())*/
DEFINE_PUBLIC_IFUNC(DOS$__crtGetTickCount64, libd_resolve_GetTickCount64);
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
/* <sys/io.h> functions (for DOS compatibility)                         */
/************************************************************************/
#if !defined(__x86_64__) && defined(__i386__)
DECL_END
#include <sys/io.h>
DECL_BEGIN

DEFINE_PUBLIC_ALIAS(DOS$_inp, libd__inp);
DEFINE_PUBLIC_ALIAS(DOS$_inpd, libd__inpd);
DEFINE_PUBLIC_ALIAS(DOS$_inpw, libd__inpw);
DEFINE_PUBLIC_ALIAS(DOS$_outp, libd__outp);
DEFINE_PUBLIC_ALIAS(DOS$_outpd, libd__outpd);
DEFINE_PUBLIC_ALIAS(DOS$_outpw, libd__outpw);
INTERN ATTR_SECTION(".text.crt.dos.compat.dos") uint8_t LIBDCALL
libd__inp(uint16_t port) {
	return inb(port);
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") uint16_t LIBDCALL
libd__inpw(uint16_t port) {
	return inw(port);
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") uint32_t LIBDCALL
libd__inpd(uint16_t port) {
	return inl(port);
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void LIBDCALL
libd__outp(uint16_t port, uint8_t value) {
	outb(port, value);
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void LIBDCALL
libd__outpw(uint16_t port, uint16_t value) {
	outw(port, value);
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos") void LIBDCALL
libd__outpd(uint16_t port, uint32_t value) {
	outl(port, value);
}

#endif /* !__x86_64__ && __i386__ */



/************************************************************************/
/* OpenSolaris's string arrays from <siginfo.h>                         */
/************************************************************************/
#define N_SYS_ILLLIST 8
static_assert(ILL_ILLOPC < (N_SYS_ILLLIST + 1));
static_assert(ILL_ILLOPN < (N_SYS_ILLLIST + 1));
static_assert(ILL_ILLADR < (N_SYS_ILLLIST + 1));
static_assert(ILL_ILLTRP < (N_SYS_ILLLIST + 1));
static_assert(ILL_PRVOPC < (N_SYS_ILLLIST + 1));
static_assert(ILL_PRVREG < (N_SYS_ILLLIST + 1));
static_assert(ILL_COPROC < (N_SYS_ILLLIST + 1));
static_assert(ILL_BADSTK < (N_SYS_ILLLIST + 1));

#define N_SYS_FPELIST 8
static_assert(FPE_INTDIV < (N_SYS_FPELIST + 1));
static_assert(FPE_INTOVF < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTDIV < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTOVF < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTUND < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTRES < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTINV < (N_SYS_FPELIST + 1));
static_assert(FPE_FLTSUB < (N_SYS_FPELIST + 1));

#define N_SYS_SEGVLIST 2
static_assert(SEGV_MAPERR < (N_SYS_SEGVLIST + 1));
static_assert(SEGV_ACCERR < (N_SYS_SEGVLIST + 1));

#define N_SYS_BUSLIST 5
static_assert(BUS_ADRALN < (N_SYS_BUSLIST + 1));
static_assert(BUS_ADRERR < (N_SYS_BUSLIST + 1));
static_assert(BUS_OBJERR < (N_SYS_BUSLIST + 1));
static_assert(BUS_MCEERR_AR < (N_SYS_BUSLIST + 1));
static_assert(BUS_MCEERR_AO < (N_SYS_BUSLIST + 1));

#define N_SYS_TRAPLIST 2
static_assert(TRAP_BRKPT < (N_SYS_TRAPLIST + 1));
static_assert(TRAP_TRACE < (N_SYS_TRAPLIST + 1));

#define N_SYS_CLDLIST 6
static_assert(CLD_EXITED < (N_SYS_CLDLIST + 1));
static_assert(CLD_KILLED < (N_SYS_CLDLIST + 1));
static_assert(CLD_DUMPED < (N_SYS_CLDLIST + 1));
static_assert(CLD_TRAPPED < (N_SYS_CLDLIST + 1));
static_assert(CLD_STOPPED < (N_SYS_CLDLIST + 1));
static_assert(CLD_CONTINUED < (N_SYS_CLDLIST + 1));

#define N_SYS_POLLLIST 6
static_assert(POLL_IN < (N_SYS_POLLLIST + 1));
static_assert(POLL_OUT < (N_SYS_POLLLIST + 1));
static_assert(POLL_MSG < (N_SYS_POLLLIST + 1));
static_assert(POLL_ERR < (N_SYS_POLLLIST + 1));
static_assert(POLL_PRI < (N_SYS_POLLLIST + 1));
static_assert(POLL_HUP < (N_SYS_POLLLIST + 1));

PRIVATE ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL NONNULL((1)) char const **
NOTHROW(LIBCCALL libc_siginfolist_init)(char const **list, unsigned int count, signo_t signo) {
	if (!list[count - 1]) {
		unsigned int i;
		for (i = 0; i < count; ++i) {
			char const *str = sigcodedesc_np(signo, i + 1);
			COMPILER_WRITE_BARRIER();
			list[i] = str;
			COMPILER_WRITE_BARRIER();
		}
	}
	return list;
}

#if defined(__OPTIMIZE_SIZE__) || 1
/* No need to  cache symbol  addresses. -  These only  get used  by
 * `libc__sys_siginfolistp_init()', and (ignoring race conditions),
 * that function only needs them once. */
#define DEFINE_LIBC_SIGINFO_LIST_LOOKUP(name)                                            \
	PRIVATE ATTR_SECTION(".rodata.crt.solaris") char const libc_##name##_name[] = #name; \
	PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.solaris")          \
	char const **LIBCCALL libc_##name##_lookup(void) {                                   \
		char const **result = (char const **)dlsym(RTLD_DEFAULT, libc_##name##_name);    \
		assert(result);                                                                  \
		return result;                                                                   \
	}
#else /* ... */
#define DEFINE_LIBC_SIGINFO_LIST_LOOKUP(name)                                            \
	PRIVATE ATTR_SECTION(".rodata.crt.solaris") char const libc_##name##_name[] = #name; \
	PRIVATE ATTR_SECTION(".bss.crt.solaris") char const **libc_##name##_addr = NULL;     \
	PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.solaris")          \
	char const **LIBCCALL libc_##name##_lookup(void) {                                   \
		if (!libc_##name##_addr) {                                                       \
			libc_##name##_addr = (char const **)dlsym(RTLD_DEFAULT, libc_##name##_name); \
			assert(libc_##name##_addr);                                                  \
		}                                                                                \
		return libc_##name##_addr;                                                       \
	}
#endif /* !... */
#define DEFINE_LIBC_SIGINFO_LIST(name, N, signo)                                         \
	PRIVATE ATTR_SECTION(".bss.crt.solaris") char const *libc_##name[N] = {};            \
	DEFINE_PUBLIC_IDATA(name, libc_##name##_init, N * __SIZEOF_POINTER__);               \
	INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.solaris")           \
	char const **LIBCCALL libc_##name##_init(void) {                                     \
		return libc_siginfolist_init(libc_##name, N, signo);                             \
	}                                                                                    \
	DEFINE_LIBC_SIGINFO_LIST_LOOKUP(name)
#undef _sys_illlist
#undef _sys_fpelist
#undef _sys_segvlist
#undef _sys_buslist
#undef _sys_traplist
#undef _sys_cldlist
#undef _sys_polllist
DEFINE_LIBC_SIGINFO_LIST(_sys_illlist, N_SYS_ILLLIST, SIGILL)
DEFINE_LIBC_SIGINFO_LIST(_sys_fpelist, N_SYS_FPELIST, SIGFPE)
DEFINE_LIBC_SIGINFO_LIST(_sys_segvlist, N_SYS_SEGVLIST, SIGSEGV)
DEFINE_LIBC_SIGINFO_LIST(_sys_buslist, N_SYS_BUSLIST, SIGBUS)
DEFINE_LIBC_SIGINFO_LIST(_sys_traplist, N_SYS_TRAPLIST, SIGTRAP)
DEFINE_LIBC_SIGINFO_LIST(_sys_cldlist, N_SYS_CLDLIST, SIGCLD)
DEFINE_LIBC_SIGINFO_LIST(_sys_polllist, N_SYS_POLLLIST, SIGPOLL)
#define _sys_illlist  libc__sys_illlist_lookup()
#define _sys_fpelist  libc__sys_fpelist_lookup()
#define _sys_segvlist libc__sys_segvlist_lookup()
#define _sys_buslist  libc__sys_buslist_lookup()
#define _sys_traplist libc__sys_traplist_lookup()
#define _sys_cldlist  libc__sys_cldlist_lookup()
#define _sys_polllist libc__sys_polllist_lookup()
#undef DEFINE_LIBC_SIGINFO_LIST_LOOKUP
#undef DEFINE_LIBC_SIGINFO_LIST

/* Define the per-signal information lookup table. */
PRIVATE ATTR_SECTION(".bss.crt.solaris") struct siginfolist libc__sys_siginfolist[NSIG - 1] = {};
PRIVATE ATTR_SECTION(".bss.crt.solaris") struct siginfolist const *libc__sys_siginfolistp   = NULL;
DEFINE_PUBLIC_IDATA(_sys_siginfolistp, libc__sys_siginfolistp_init, __SIZEOF_POINTER__);
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.solaris")
struct siginfolist const **LIBCCALL libc__sys_siginfolistp_init(void) {
	if (!libc__sys_siginfolistp) {
		/* Populate string vectors. */
		libc__sys_siginfolist[SIGILL - 1].nsiginfo  = N_SYS_ILLLIST;
		libc__sys_siginfolist[SIGILL - 1].vsiginfo  = (char **)_sys_illlist;
		libc__sys_siginfolist[SIGFPE - 1].nsiginfo  = N_SYS_FPELIST;
		libc__sys_siginfolist[SIGFPE - 1].vsiginfo  = (char **)_sys_fpelist;
		libc__sys_siginfolist[SIGSEGV - 1].nsiginfo = N_SYS_SEGVLIST;
		libc__sys_siginfolist[SIGSEGV - 1].vsiginfo = (char **)_sys_segvlist;
		libc__sys_siginfolist[SIGBUS - 1].nsiginfo  = N_SYS_BUSLIST;
		libc__sys_siginfolist[SIGBUS - 1].vsiginfo  = (char **)_sys_buslist;
		libc__sys_siginfolist[SIGTRAP - 1].nsiginfo = N_SYS_TRAPLIST;
		libc__sys_siginfolist[SIGTRAP - 1].vsiginfo = (char **)_sys_traplist;
		libc__sys_siginfolist[SIGCLD - 1].nsiginfo  = N_SYS_CLDLIST;
		libc__sys_siginfolist[SIGCLD - 1].vsiginfo  = (char **)_sys_cldlist;
		libc__sys_siginfolist[SIGPOLL - 1].nsiginfo = N_SYS_POLLLIST;
		libc__sys_siginfolist[SIGPOLL - 1].vsiginfo = (char **)_sys_polllist;
		COMPILER_WRITE_BARRIER();
		/* Initialize the string-list-pointer. */
		libc__sys_siginfolistp = libc__sys_siginfolist;
	}
	return &libc__sys_siginfolistp;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_COMPAT_C */
