/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C
#define GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__va_size.h>
#include <hybrid/typecore.h>

#include <kos/dev.h>
#include <kos/io.h>
#include <kos/kernel/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <format-printer.h>
#include <inttypes.h>
#include <string.h>

#include "sctrace.h"

#ifdef __KERNEL__
#include <dev/block.h>
#include <dev/char.h>
#include <kernel/user.h>
#else /* __KERNEL__ */
#define validate_readable(base, num_bytes)                          (void)0
#define validate_readablem(base, num_items, item_size_in_bytes)     (void)0
#define validate_readable_opt(base, num_bytes)                      (void)0
#define validate_readablem_opt(base, num_items, item_size_in_bytes) (void)0
#endif /* !__KERNEL__ */

DECL_BEGIN




/* The representation of bit-wide OR in flagsets */
#if 1
#define PIPESTR "|"
#else
#define PIPESTR " | "
#endif


/* Ensure that `PIPESTR' doesn't get allocated multiple times. */
PRIVATE ATTR_UNUSED char const PIPESTR_[] = PIPESTR;
#undef PIPESTR
#define PIPESTR PIPESTR_



/* Helper macros. */
#define DO(...) do{ if unlikely((temp = (__VA_ARGS__)) < 0) goto err; result += temp; }__WHILE0
#define DOPRINT(str) (*printer)(arg, str, COMPILER_STRLEN(str))
#define PRINT(str)   DO(DOPRINT(str))
#define PRINTF(...)  DO(format_printf(printer, arg, __VA_ARGS__))


#if __VA_SIZE == 4
typedef uint32_t va_uint_t;
#elif __VA_SIZE == 8
typedef uint64_t va_uint_t;
#elif __VA_SIZE == 2
typedef uint16_t va_uint_t;
#elif __VA_SIZE == 1
typedef uint8_t va_uint_t;
#else
#error "Unsupported `__VA_SIZE'"
#endif

PRIVATE ATTR_UNUSED NONNULL((1)) ssize_t CC
print_dev_blk(pformatprinter printer, void *arg, dev_t devno) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "blk"
	                       ":%" PRIuN(__SIZEOF_MAJOR_T__)
	                       ":%" PRIuN(__SIZEOF_MINOR_T__),
	                       MAJOR(devno),
	                       MINOR(devno));
#ifdef __KERNEL__
	if likely(result >= 0) {
		REF struct basic_block_device *dev;
		dev = block_device_lookup_nx(devno);
		if (dev) {
			ssize_t temp;
			FINALLY_DECREF_UNLIKELY(dev);
			temp = format_printf(printer, arg, ":\"/dev/%#q\"",
			                     dev->bd_name);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	}
#endif /* __KERNEL__ */
	return result;
}

PRIVATE ATTR_UNUSED NONNULL((1)) ssize_t CC
print_dev_chr(pformatprinter printer, void *arg, dev_t devno) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "chr"
	                       ":%" PRIuN(__SIZEOF_MAJOR_T__)
	                       ":%" PRIuN(__SIZEOF_MINOR_T__),
	                       MAJOR(devno),
	                       MINOR(devno));
#ifdef __KERNEL__
	if likely(result >= 0) {
		REF struct character_device *dev;
		dev = character_device_lookup_nx(devno);
		if (dev) {
			ssize_t temp;
			FINALLY_DECREF_UNLIKELY(dev);
			temp = format_printf(printer, arg, ":\"/dev/%#q\"",
			                     dev->cd_name);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	}
#endif /* __KERNEL__ */
	return result;
}


PRIVATE struct {
	mode_t mn_mode;    /* Flag value */
	char   mn_name[8]; /* Flag name */
} const mode_names[] = {
	{ S_ISVTX, "S_ISVTX" },
	{ S_ISGID, "S_ISGID" },
	{ S_ISUID, "S_ISUID" }
};

PRIVATE ATTR_UNUSED ssize_t CC
print_mode_t(pformatprinter printer, void *arg, mode_t mode) {
	ssize_t temp, result = 0;
	char const *name;
	bool is_first;
	unsigned int i;
	enum { VALID_MASK = S_IFMT | S_ISVTX | S_ISGID | S_ISUID | 0777 };
	switch (mode & S_IFMT) {
	case S_IFIFO:  name = "IFO"; break;  /* 0010000: FIFO. */
	case S_IFCHR:  name = "CHR"; break;  /* 0020000: Character device. */
	case S_IFDIR:  name = "DIR"; break;  /* 0040000: Directory. */
	case S_IFBLK:  name = "BLK"; break;  /* 0060000: Block device. */
	case S_IFREG:  name = "REG"; break;  /* 0100000: Regular file. */
	case S_IFLNK:  name = "LNK"; break;  /* 0120000: Symbolic link. */
	case S_IFSOCK: name = "SOCK"; break; /* 0140000: Socket. */
	default: name = NULL; break;
	}
	is_first = true;
	if likely(name) {
		result = format_printf(printer, arg, "S_IF%s", name);
		if unlikely(result < 0)
			goto done;
		is_first = false;
	} else if ((mode & S_IFMT) != 0) {
		result = format_printf(printer, arg,
		                       "0%" PRIoN(__SIZEOF_MODE_T__),
		                       (mode_t)(mode & S_IFMT));
		if unlikely(result < 0)
			goto done;
	}
	for (i = 0; i < COMPILER_LENOF(mode_names); ++i) {
		char const *name;
		if (!(mode & mode_names[i].mn_mode))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = mode_names[i].mn_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if (mode & 0777) {
		/* Print the permissions suffix as a raw string. */
		PRINTF("%s0%" PRIoN(__SIZEOF_MODE_T__),
		       is_first ? "" : PIPESTR,
		       (mode_t)(mode & 0777));
		is_first = false;
	}
	if unlikely(mode & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("0%" PRIoN(__SIZEOF_MODE_T__),
		       (mode_t)(mode & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}


PRIVATE struct {
	oflag_t on_flag;     /* Flag value */
	char    on_name[12]; /* Flag name */
} const oflag_names[] = {
	{ O_TRUNC,     "O_TRUNC" },
	{ O_CREAT,     "O_CREAT" },
	{ O_EXCL,      "O_EXCL" },
	{ O_NOCTTY,    "O_NOCTTY" },
	{ O_APPEND,    "O_APPEND" },
	{ O_NONBLOCK,  "O_NONBLOCK" },
	{ O_SYNC,      "O_SYNC" },
	{ O_DSYNC,     "O_DSYNC" },
	{ O_ASYNC,     "O_ASYNC" },
	{ O_DIRECT,    "O_DIRECT" },
	{ O_LARGEFILE, "O_LARGEFILE" },
	{ O_DIRECTORY, "O_DIRECTORY" },
	{ O_NOFOLLOW,  "O_NOFOLLOW" },
	{ O_NOATIME,   "O_NOATIME" },
	{ O_CLOEXEC,   "O_CLOEXEC" },
	{ O_PATH,      "O_PATH" },
	{ O_TMPFILE,   "O_TMPFILE" },
	{ O_CLOFORK,   "O_CLOFORK" },
	{ O_SYMLINK,   "O_SYMLINK" },
	{ O_DOSPATH,   "O_DOSPATH" },
};


PRIVATE ATTR_UNUSED ssize_t CC
print_oflag_t_impl(pformatprinter printer, void *arg,
                   oflag_t oflags, bool force_accmode) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	enum {
		VALID_MASK = (O_ACCMODE | O_TRUNC | O_CREAT | O_EXCL |
		              O_NOCTTY | O_APPEND | O_NONBLOCK | O_SYNC |
		              O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
		              O_DIRECTORY | O_NOFOLLOW | O_NOATIME |
		              O_CLOEXEC | O_PATH | O_TMPFILE |
		              O_CLOFORK | O_SYMLINK | O_DOSPATH)
	};
	if (force_accmode || (oflags & O_ACCMODE) != 0) {
		/* Print the access mode */
		char const *accname;
		switch (oflags & O_ACCMODE) {
		case O_RDONLY: accname = "RDONLY"; break;
		case O_WRONLY: accname = "WRONLY"; break;
		case O_RDWR:   accname = "RDWR"; break;
		default: accname = NULL; break;
		}
		if likely(accname) {
			result = format_printf(printer, arg, "O_%s", accname);
		} else {
			result = format_printf(printer, arg, "%#" PRIoN(__SIZEOF_OFLAG_T__),
			                       (oflag_t)(oflags & O_ACCMODE));
		}
		if unlikely(result < 0)
			goto done;
		is_first = false;
	}
	for (i = 0; i < COMPILER_LENOF(oflag_names); ++i) {
		char const *name;
		if (!(oflags & oflag_names[i].on_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = oflag_names[i].on_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if unlikely(oflags & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_OFLAG_T__),
		       (oflag_t)(oflags & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}

PRIVATE ATTR_UNUSED ssize_t CC
print_oflag_t(pformatprinter printer, void *arg,
              oflag_t oflags, oflag_t allowed_oflags) {
	ssize_t temp, result;
	bool force_accmode;
	force_accmode = (allowed_oflags & O_ACCMODE) != 0;
	result = print_oflag_t_impl(printer, arg, oflags, force_accmode);
	if (likely(result >= 0) && unlikely((oflags & ~allowed_oflags) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_oflag_t_impl(printer, arg,
		                      oflags & ~allowed_oflags,
		                      false));
		PRINT(">");
	}
	return result;
err:
	return temp;
}



PRIVATE struct {
	atflag_t an_flag;     /* Flag value */
	char     an_name[20]; /* Flag name */
} const atflag_names[] = {
	{ AT_SYMLINK_NOFOLLOW, "AT_SYMLINK_NOFOLLOW" },
	{ AT_REMOVEDIR,        "AT_REMOVEDIR" },
	{ AT_SYMLINK_FOLLOW,   "AT_SYMLINK_FOLLOW" },
	{ AT_NO_AUTOMOUNT,     "AT_NO_AUTOMOUNT" },
	{ AT_EMPTY_PATH,       "AT_EMPTY_PATH" },
	{ AT_SYMLINK_REGULAR,  "AT_SYMLINK_REGULAR" },
	{ AT_REMOVEREG,        "AT_REMOVEREG" },
	{ AT_ALTPATH,          "AT_ALTPATH" },
	{ AT_DOSPATH,          "AT_DOSPATH" },
};

PRIVATE ATTR_UNUSED ssize_t CC
print_atflag_t_impl(pformatprinter printer, void *arg,
                    atflag_t atflags,
                    char const *nameof_AT_READLINK_REQSIZE) {
	STATIC_ASSERT(AT_READLINK_REQSIZE == AT_CHANGE_CTIME);
	STATIC_ASSERT(AT_READLINK_REQSIZE == AT_EACCESS);
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	atflag_t valid_mask;
	valid_mask = (AT_SYMLINK_NOFOLLOW | AT_REMOVEDIR |
	              AT_SYMLINK_FOLLOW | AT_NO_AUTOMOUNT |
	              AT_EMPTY_PATH | AT_SYMLINK_REGULAR |
	              AT_REMOVEREG | AT_ALTPATH | AT_DOSPATH);
	if (nameof_AT_READLINK_REQSIZE)
		valid_mask |= AT_READLINK_REQSIZE;
	for (i = 0; i < COMPILER_LENOF(atflag_names); ++i) {
		char const *name;
		if (!(atflags & atflag_names[i].an_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = atflag_names[i].an_name;
		DO((*printer)(arg, name, strlen(name)));
		is_first = false;
	}
	if ((atflags & AT_READLINK_REQSIZE) && nameof_AT_READLINK_REQSIZE) {
		if (!is_first)
			PRINT(PIPESTR);
		DO((*printer)(arg, nameof_AT_READLINK_REQSIZE,
		              strlen(nameof_AT_READLINK_REQSIZE)));
		is_first = false;
	}
	if unlikely(atflags & ~valid_mask) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_ATFLAG_T__),
		       (atflag_t)(atflags & ~valid_mask));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
	return result;
err:
	return temp;
}

PRIVATE ATTR_UNUSED ssize_t CC
print_atflag_t(pformatprinter printer, void *arg,
               atflag_t atflags, atflag_t allowed_atflags,
               char const *nameof_AT_READLINK_REQSIZE) {
	ssize_t temp, result;
	result = print_atflag_t_impl(printer, arg, atflags,
	                             nameof_AT_READLINK_REQSIZE);
	if (likely(result >= 0) && unlikely((atflags & ~allowed_atflags) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_atflag_t_impl(printer, arg,
		                       atflags & ~allowed_atflags,
		                       nameof_AT_READLINK_REQSIZE));
		PRINT(">");
	}
	return result;
err:
	return temp;
}


PRIVATE struct {
	iomode_t on_flag;     /* Flag value */
	char    on_name[12]; /* Flag name */
} const iomode_names[] = {
	{ IO_CLOEXEC,    "CLOEXEC" },
	{ IO_CLOFORK,    "CLOFORK" },
	{ IO_APPEND,     "APPEND" },
	{ IO_NONBLOCK,   "NONBLOCK" },
	{ IO_SYNC,       "SYNC" },
	{ IO_ASYNC,      "ASYNC" },
	{ IO_DIRECT,     "DIRECT" },
	{ IO_NODATAZERO, "NODATAZERO" },
};


PRIVATE ATTR_UNUSED ssize_t CC
print_iomode_t_impl(pformatprinter printer, void *arg,
                   iomode_t iomodes, bool force_accmode) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	enum {
		VALID_MASK = (IO_ACCMODE | IO_CLOEXEC | IO_CLOFORK |
		              IO_APPEND | IO_NONBLOCK | IO_SYNC |
		              IO_ASYNC | IO_DIRECT | IO_NODATAZERO)
	};
	if (force_accmode || (iomodes & IO_ACCMODE) != 0) {
		/* Print the access mode */
		char const *accname;
		switch (iomodes & IO_ACCMODE) {
		case IO_RDONLY:   accname = "RDONLY"; break;
		case IO_WRONLY:   accname = "WRONLY"; break;
		case IO_RDWR:     accname = "RDWR"; break;
		case IO_RDWR_ALT: accname = "RDWR_ALT"; break;
		default: accname = NULL; break;
		}
		if likely(accname) {
			result = format_printf(printer, arg, "IO_%s", accname);
		} else {
			result = format_printf(printer, arg, "%#" PRIoN(__SIZEOF_IOMODE_T__),
			                       (iomode_t)(iomodes & IO_ACCMODE));
		}
		if unlikely(result < 0)
			goto done;
		is_first = false;
	}
	for (i = 0; i < COMPILER_LENOF(iomode_names); ++i) {
		char const *name;
		if (!(iomodes & iomode_names[i].on_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = iomode_names[i].on_name;
		PRINTF("IO_%s", name);
		is_first = false;
	}
	if unlikely(iomodes & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIxN(__SIZEOF_IOMODE_T__),
		       (iomode_t)(iomodes & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
done:
	return result;
err:
	return temp;
}

PRIVATE ATTR_UNUSED ssize_t CC
print_iomode_t(pformatprinter printer, void *arg,
              iomode_t iomodes, iomode_t allowed_iomodes) {
	ssize_t temp, result;
	bool force_accmode;
	force_accmode = (allowed_iomodes & IO_ACCMODE) != 0;
	result = print_iomode_t_impl(printer, arg, iomodes, force_accmode);
	if (likely(result >= 0) && unlikely((iomodes & ~allowed_iomodes) != 0)) {
		/* Disallowed flags passed. (print the set of bad flags explicitly) */
		PRINT(" <BAD:");
		DO(print_iomode_t_impl(printer, arg,
		                       iomodes & ~allowed_iomodes,
		                       false));
		PRINT(">");
	}
	return result;
err:
	return temp;
}

PRIVATE ATTR_UNUSED ssize_t CC
print_fd_t(pformatprinter printer, void *arg, fd_t fd) {
	ssize_t result;
	char const *name;
	switch (fd) {
		/* Deal with symbolic file handles. */
	case AT_FDCWD:          name = "AT_FDCWD"; break;
	case AT_FDROOT:         name = "AT_FDROOT"; break;
	case AT_THIS_TASK:      name = "AT_THIS_TASK"; break;
	case AT_THIS_PROCESS:   name = "AT_THIS_PROCESS"; break;
	case AT_PARENT_PROCESS: name = "AT_PARENT_PROCESS"; break;
	case AT_GROUP_LEADER:   name = "AT_GROUP_LEADER"; break;
	case AT_SESSION_LEADER: name = "AT_SESSION_LEADER"; break;

	default:
		/* Deal with DOS drive file handles. */
		if (fd >= AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN) &&
		    fd <= AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)) {
			result = format_printf(printer, arg, "AT_FDDRIVE_CWD('%c')",
			                       'A' + (fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)));
		} else if (fd >= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) &&
		           fd <= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)) {
			result = format_printf(printer, arg, "AT_FDDRIVE_ROOT('%c')",
			                       'A' + (fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)));
		} else {
			result = format_printf(printer, arg,
			                       "%" PRIdN(__SIZEOF_FD_T__),
			                       fd);
		}
		goto done;
	}
	result = (*printer)(arg, name, strlen(name));
done:
	return result;
}


PRIVATE struct {
	clockid_t cn_clid;     /* Clock ID */
	char      cn_name[20]; /* Clock ID name. */
} const clockid_names[] = {
	{ CLOCK_REALTIME,           "REALTIME" },
	{ CLOCK_MONOTONIC,          "MONOTONIC" },
	{ CLOCK_PROCESS_CPUTIME_ID, "PROCESS_CPUTIME_ID" },
	{ CLOCK_THREAD_CPUTIME_ID,  "THREAD_CPUTIME_ID" },
	{ CLOCK_MONOTONIC_RAW,      "MONOTONIC_RAW" },
	{ CLOCK_REALTIME_COARSE,    "REALTIME_COARSE" },
	{ CLOCK_MONOTONIC_COARSE,   "MONOTONIC_COARSE" },
	{ CLOCK_BOOTTIME,           "BOOTTIME" },
	{ CLOCK_REALTIME_ALARM,     "REALTIME_ALARM" },
	{ CLOCK_BOOTTIME_ALARM,     "BOOTTIME_ALARM" },
	{ CLOCK_TAI,                "TAI" },
};

PRIVATE ATTR_UNUSED ssize_t CC
print_clockid_t(pformatprinter printer, void *arg, clockid_t clockid) {
	ssize_t result;
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(clockid_names); ++i) {
		if (clockid_names[i].cn_clid == clockid) {
			char const *name;
			name = clockid_names[i].cn_name;
			result = format_printf(printer, arg, "CLOCK_%s", name);
			goto done;
		}
	}
	result = format_printf(printer, arg,
	                       "%" PRIuN(__SIZEOF_CLOCKID_T__),
	                       clockid);
done:
	return result;
}

PRIVATE ATTR_UNUSED ssize_t CC
print_string(pformatprinter printer, void *arg, char const *str) {
	ssize_t result;
	if (!str) {
		result = (*printer)(arg, "NULL", 4);
	} else {
		size_t len;
		validate_readable(str, 1);
		len    = strlen(str);
		result = format_printf(printer, arg, "%$q", len, str);
	}
	return result;
}




/* Print the representation of a given system call argument
 * value, given both its `argtype' (one of `*'), and `value'
 * WARNING: Depending on `argtype', an exception may be thrown
 *          if the system call invoker has passed some invalid
 *          argument to a system call (i.e. a faulty pointer
 *          when a structure pointer or string was expected) */
INTERN NONNULL((1)) ssize_t CC
libsc_printvalue(pformatprinter printer, void *arg,
                 uintptr_t argtype, union sc_argval value,
                 struct sc_argument *link) {
	ssize_t result;
	char const *format;
	(void)link;
	switch (argtype) {

	// TODO: #define HAVE_SC_REPR_ACCEPT4_FLAGS 1
	// TODO: #define HAVE_SC_REPR_ACCESS_TYPE 1
	// TODO: #define HAVE_SC_REPR_CLONE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_CLONE_FLAGS_UNSHARE 1
	// TODO: #define HAVE_SC_REPR_EPOLL_OP 1
	// TODO: #define HAVE_SC_REPR_EVENTFD2_FLAGS 1
	// TODO: #define HAVE_SC_REPR_EXIT_STATUS 1
	// TODO: #define HAVE_SC_REPR_GETRUSAGE_WHO 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR16 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR32 1
	// TODO: #define HAVE_SC_REPR_HOP_ARG 1
	// TODO: #define HAVE_SC_REPR_HOP_COMMAND 1
	// TODO: #define HAVE_SC_REPR_IDTYPE_T 1
	// TODO: #define HAVE_SC_REPR_ID_T 1
	// TODO: #define HAVE_SC_REPR_INBUF 1
	// TODO: #define HAVE_SC_REPR_KREADDIR_MODE 1
	// TODO: #define HAVE_SC_REPR_LFUTEX_OP 1
	// TODO: #define HAVE_SC_REPR_MAPLIBRARY_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MEMFD_CREATE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MMAP_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MMAP_PROT 1
	// TODO: #define HAVE_SC_REPR_MOUNT_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MREMAP_FLAGS 1
	// TODO: #define HAVE_SC_REPR_OUTBUF 1
	// TODO: #define HAVE_SC_REPR_REBOOT_HOW 1
	// TODO: #define HAVE_SC_REPR_RENAMEAT2_FLAGS 1
	// TODO: #define HAVE_SC_REPR_RLIMIT_RESOURCE 1
	// TODO: #define HAVE_SC_REPR_RPC_SCHEDULE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SEEK_WHENCE 1
	// TODO: #define HAVE_SC_REPR_SET_EXCEPTION_HANDLER_MODE 1
	// TODO: #define HAVE_SC_REPR_SIGNALFD4_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SIGNO 1
	// TODO: #define HAVE_SC_REPR_SIGPROCMASK_HOW 1
	// TODO: #define HAVE_SC_REPR_SOCKET_DOMAIN 1
	// TODO: #define HAVE_SC_REPR_SOCKET_PROTOCOL 1
	// TODO: #define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2 1
	// TODO: #define HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SOCKET_SHUTDOWN_HOW 1
	// TODO: #define HAVE_SC_REPR_SOCKET_TYPE 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_LEVEL 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_OPTNAME 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_OPTVAL 1
	// TODO: #define HAVE_SC_REPR_STRING_VECTOR32 1
	// TODO: #define HAVE_SC_REPR_STRING_VECTOR64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR32_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR64_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_FDSET 1
	// TODO: #define HAVE_SC_REPR_STRUCT_FPUSTATE 1
	// TODO: #define HAVE_SC_REPR_STRUCT_FPUSTATE32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_IOVEC 1
	// TODO: #define HAVE_SC_REPR_STRUCT_IOVECX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_IOVECX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERSPECX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ITIMERVALX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_LFUTEXEXPRX32_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_LFUTEXEXPRX64_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_LIBRARY_LISTDEF32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_LIBRARY_LISTDEF64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MMSGHDRX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MMSGHDRX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_POLLFD 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGACTIONX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGACTIONX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGMASK_SIGSET_AND_LEN 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGSET 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SOCKADDR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SPAWN_ACTIONSX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SPAWN_ACTIONSX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TERMIOS 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMESPECX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMESPECX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMESPECX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEVALX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEVALX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEVALX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEZONE 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_WINSIZE 1
	// TODO: #define HAVE_SC_REPR_SWAPFLAGS 1
	// TODO: #define HAVE_SC_REPR_SYSLOG_LEVEL 1
	// TODO: #define HAVE_SC_REPR_TIMEVALX32_64_VEC2 1
	// TODO: #define HAVE_SC_REPR_TIMEVALX32_VEC2 1
	// TODO: #define HAVE_SC_REPR_TIMEVALX64_VEC2 1
	// TODO: #define HAVE_SC_REPR_UNWIND_ERROR 1
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR32 1
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR64 1
	// TODO: #define HAVE_SC_REPR_WAITFLAG 1
	// TODO: #define HAVE_SC_REPR_WAITID_OPTIONS 1


#ifdef HAVE_SC_REPR_FILENAME
	case SC_REPR_FILENAME:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FILENAME */

#ifdef HAVE_SC_REPR_STRING
	case SC_REPR_STRING:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_STRING */

#ifdef HAVE_SC_REPR_CLOCKID_T
	case SC_REPR_CLOCKID_T:
		result = print_clockid_t(printer, arg, (clockid_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_CLOCKID_T */

#ifdef HAVE_SC_REPR_FD_T
	case SC_REPR_FD_T:
		result = print_fd_t(printer, arg, (fd_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FD_T */

#ifdef HAVE_SC_REPR_ERRNO_T
	case SC_REPR_ERRNO_T: {
		char const *name;
		ssize_t temp;
		errno_t eno;
		eno = (errno_t)value.sv_u64;
		result = 0;
		if (eno < 0) {
			result = (*printer)(arg, "-", 1);
			if unlikely(result < 0)
				goto done;
			eno = -eno;
		}
		name = strerrorname_s(eno);
		if likely(name) {
			temp = (*printer)(arg, name, strlen(name));
		} else {
			temp = format_printf("%" PRIuN(__SIZEOF_ERRNO_T__), eno);
		}
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}	break;
#endif /* HAVE_SC_REPR_ERRNO_T */

#ifdef HAVE_SC_REPR_IOMODE_T
	case SC_REPR_IOMODE_T:
		result = print_iomode_t(printer, arg, (iomode_t)value.sv_u64, ~0);
		break;
#endif /* HAVE_SC_REPR_IOMODE_T */

#ifdef HAVE_SC_REPR_ATFLAG_T
	case SC_REPR_ATFLAG_T:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64, ~0, NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG_T */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__DOSPATH
	case SC_REPR_ATFLAG__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_DOSPATH, NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH
	case SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH
	case SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH
	case SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_READLINK_REQSIZE | AT_DOSPATH,
		                        "AT_READLINK_REQSIZE");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH
	case SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH,
		                        "AT_CHANGE_CTIME");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
		                        NULL);
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH
	case SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH:
		result = print_atflag_t(printer, arg, (oflag_t)value.sv_u64,
		                        AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH,
		                        "AT_EACCESS");
		break;
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH */

#ifdef HAVE_SC_REPR_OFLAG_T
	case SC_REPR_OFLAG_T:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64, ~0);
		break;
#endif /* HAVE_SC_REPR_OFLAG_T */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK | O_NONBLOCK);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT
	case SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT:
		result = print_oflag_t(printer, arg, (oflag_t)value.sv_u64,
		                       O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT);
		break;
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT */

#ifdef HAVE_SC_REPR_MODE_T
	case SC_REPR_MODE_T:
		result = print_mode_t(printer, arg, (mode_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_MODE_T */

#ifdef HAVE_SC_REPR_DEV_T
	case SC_REPR_DEV_T: {
		dev_t devno = (dev_t)value.sv_u64;
		if (link) {
			mode_t linked_mode = (mode_t)link->sa_value.sv_u64;
			if (S_ISBLK(linked_mode)) {
				result = print_dev_blk(printer, arg, devno);
				break;
			} else if (S_ISCHR(linked_mode)) {
				result = print_dev_chr(printer, arg, devno);
				break;
			}
		}
		result = format_printf(printer, arg,
		                       "?"
		                       ":%" PRIuN(__SIZEOF_MAJOR_T__)
		                       ":%" PRIuN(__SIZEOF_MINOR_T__),
		                       MAJOR(devno),
		                       MINOR(devno));
	}	break;
#endif /* HAVE_SC_REPR_DEV_T */

#ifdef HAVE_SC_REPR_DEV_BLK
	case SC_REPR_DEV_BLK: {
		dev_t devno = (dev_t)value.sv_u64;
		result = print_dev_blk(printer, arg, devno);
	}	break;
#endif /* HAVE_SC_REPR_DEV_BLK */

#ifdef HAVE_SC_REPR_DEV_CHR
	case SC_REPR_DEV_CHR: {
		dev_t devno = (dev_t)value.sv_u64;
		result = print_dev_chr(printer, arg, devno);
	}	break;
#endif /* HAVE_SC_REPR_DEV_CHR */

#ifdef HAVE_SC_REPR_TIME_T
	case SC_REPR_TIME_T:
#if __SIZEOF_TIME_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_TIME_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_TIME_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_TIME_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_TIME_T__ == ... */
#error "Unsupported `__SIZEOF_TIME_T__'"
#endif /* __SIZEOF_TIME_T__ != ... */
#endif /* HAVE_SC_REPR_TIME_T */


		/* Escape character constants. */
#ifdef HAVE_SC_REPR_CHAR
	case SC_REPR_CHAR:
		format = "%Q";
#if __SIZEOF_CHAR__ == 1
#define NEED_do_format8
		goto do_format8;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_format64
		goto do_format64;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_CHAR */

#ifdef HAVE_SC_REPR_GID_T
		case SC_REPR_GID_T:
#if __SIZEOF_GID_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_GID_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_GID_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_GID_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_GID_T__ == ... */
#error "Unsupported `__SIZEOF_GID_T__'"
#endif /* __SIZEOF_GID_T__ != ... */
#endif /* HAVE_SC_REPR_GID_T */

#ifdef HAVE_SC_REPR_UID_T
		case SC_REPR_UID_T:
#if __SIZEOF_UID_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_UID_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_UID_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_UID_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_UID_T__ == ... */
#error "Unsupported `__SIZEOF_UID_T__'"
#endif /* __SIZEOF_UID_T__ != ... */
#endif /* HAVE_SC_REPR_UID_T */

#ifdef HAVE_SC_REPR_PID_T
		case SC_REPR_PID_T:
#if __SIZEOF_PID_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_PID_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_PID_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_PID_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_PID_T__ == ... */
#error "Unsupported `__SIZEOF_PID_T__'"
#endif /* __SIZEOF_PID_T__ != ... */
#endif /* HAVE_SC_REPR_PID_T */

#ifdef HAVE_SC_REPR_SIGHANDLER_T
	case SC_REPR_SIGHANDLER_T:
		goto do_syscall_ulong_t;
#define NEED_do_syscall_ulong_t
#endif /* HAVE_SC_REPR_SIGHANDLER_T */

#ifdef HAVE_SC_REPR_EXCEPT_HANDLER_T
	case SC_REPR_EXCEPT_HANDLER_T:
		goto do_syscall_ulong_t;
#define NEED_do_syscall_ulong_t
#endif /* HAVE_SC_REPR_EXCEPT_HANDLER_T */

#ifdef HAVE_SC_REPR_TIMER_T
	case SC_REPR_TIMER_T:
		goto do_syscall_ulong_t;
#define NEED_do_syscall_ulong_t
#endif /* HAVE_SC_REPR_TIMER_T */

#ifdef HAVE_SC_REPR_POINTER
	case SC_REPR_POINTER:
		goto do_syscall_ulong_t;
#define NEED_do_syscall_ulong_t
#endif /* HAVE_SC_REPR_POINTER */

#ifdef HAVE_SC_REPR_INTPTR_T
	case SC_REPR_INTPTR_T:
		goto do_syscall_slong_t;
#define NEED_do_syscall_slong_t
#endif /* HAVE_SC_REPR_INTPTR_T */

#ifdef HAVE_SC_REPR_UINTPTR_T
	case SC_REPR_UINTPTR_T:
		goto do_syscall_ulong_t;
#define NEED_do_syscall_ulong_t
#endif /* HAVE_SC_REPR_UINTPTR_T */

#if defined(HAVE_SC_REPR_SYSCALL_SLONG_T) || defined(NEED_do_syscall_slong_t)
#ifdef HAVE_SC_REPR_SYSCALL_SLONG_T
	case SC_REPR_SYSCALL_SLONG_T:
#endif /* HAVE_SC_REPR_SYSCALL_SLONG_T */
#ifdef NEED_do_syscall_slong_t
do_syscall_slong_t:
#endif /* NEED_do_syscall_slong_t */
		format = "%#tx"; /* Signed, ptrdiff_t-sized printf */
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_SYSCALL_SLONG_T || NEED_do_syscall_slong_t */

#if defined(HAVE_SC_REPR_SYSCALL_ULONG_T) || defined(NEED_do_syscall_ulong_t)
#ifdef HAVE_SC_REPR_SYSCALL_ULONG_T
	case SC_REPR_SYSCALL_ULONG_T:
#endif /* HAVE_SC_REPR_SYSCALL_ULONG_T */
#ifdef NEED_do_syscall_ulong_t
do_syscall_ulong_t:
#endif /* NEED_do_syscall_ulong_t */
		format = "%#" PRIxPTR;
#if __SIZEOF_POINTER__ == 4
#define NEED_do_format32
		goto do_format32;
#elif __SIZEOF_POINTER__ == 8
#define NEED_do_format64
		goto do_format64;
#elif __SIZEOF_POINTER__ == 2
#define NEED_do_format16
		goto do_format16;
#elif __SIZEOF_POINTER__ == 1
#define NEED_do_format8
		goto do_format8;
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* HAVE_SC_REPR_SYSCALL_ULONG_T || NEED_do_syscall_ulong_t */

#ifdef HAVE_SC_REPR_SIGNED_CHAR
		case SC_REPR_SIGNED_CHAR:
#if __SIZEOF_CHAR__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_SIGNED_CHAR */

#ifdef HAVE_SC_REPR_UNSIGNED_CHAR
		case SC_REPR_UNSIGNED_CHAR:
#if __SIZEOF_CHAR__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_CHAR__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_CHAR__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_CHAR__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_CHAR__ == ... */
#error "Unsupported `__SIZEOF_CHAR__'"
#endif /* __SIZEOF_CHAR__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_CHAR */

#ifdef HAVE_SC_REPR_SHORT
		case SC_REPR_SHORT:
#if __SIZEOF_SHORT__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_SHORT__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_SHORT__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_SHORT__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_SHORT__ == ... */
#error "Unsupported `__SIZEOF_SHORT__'"
#endif /* __SIZEOF_SHORT__ != ... */
#endif /* HAVE_SC_REPR_SHORT */

#ifdef HAVE_SC_REPR_UNSIGNED_SHORT
		case SC_REPR_UNSIGNED_SHORT:
#if __SIZEOF_SHORT__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SHORT__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SHORT__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SHORT__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SHORT__ == ... */
#error "Unsupported `__SIZEOF_SHORT__'"
#endif /* __SIZEOF_SHORT__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_SHORT */

#ifdef HAVE_SC_REPR_INT
		case SC_REPR_INT:
#if __SIZEOF_INT__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_INT__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_INT__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_INT__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported `__SIZEOF_INT__'"
#endif /* __SIZEOF_INT__ != ... */
#endif /* HAVE_SC_REPR_INT */

#ifdef HAVE_SC_REPR_UNSIGNED_INT
		case SC_REPR_UNSIGNED_INT:
#if __SIZEOF_INT__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_INT__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_INT__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_INT__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported `__SIZEOF_INT__'"
#endif /* __SIZEOF_INT__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_INT */

#ifdef HAVE_SC_REPR_LONG
		case SC_REPR_LONG:
#if __SIZEOF_LONG__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_LONG__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_LONG__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_LONG__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG__'"
#endif /* __SIZEOF_LONG__ != ... */
#endif /* HAVE_SC_REPR_LONG */

#ifdef HAVE_SC_REPR_UNSIGNED_LONG
		case SC_REPR_UNSIGNED_LONG:
#if __SIZEOF_LONG__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_LONG__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_LONG__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_LONG__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG__'"
#endif /* __SIZEOF_LONG__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_LONG */

#ifdef HAVE_SC_REPR_LONG_LONG
		case SC_REPR_LONG_LONG:
#if __SIZEOF_LONG_LONG__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_LONG_LONG__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_LONG_LONG__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_LONG_LONG__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_LONG_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG_LONG__'"
#endif /* __SIZEOF_LONG_LONG__ != ... */
#endif /* HAVE_SC_REPR_LONG_LONG */

#ifdef HAVE_SC_REPR_UNSIGNED_LONG_LONG
		case SC_REPR_UNSIGNED_LONG_LONG:
#if __SIZEOF_LONG_LONG__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_LONG_LONG__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_LONG_LONG__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_LONG_LONG__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_LONG_LONG__ == ... */
#error "Unsupported `__SIZEOF_LONG_LONG__'"
#endif /* __SIZEOF_LONG_LONG__ != ... */
#endif /* HAVE_SC_REPR_UNSIGNED_LONG_LONG */

#ifdef HAVE_SC_REPR_PTRDIFF_T
		case SC_REPR_PTRDIFF_T:
#if __SIZEOF_PTRDIFF_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_PTRDIFF_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_PTRDIFF_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_PTRDIFF_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_PTRDIFF_T__ == ... */
#error "Unsupported `__SIZEOF_PTRDIFF_T__'"
#endif /* __SIZEOF_PTRDIFF_T__ != ... */
#endif /* HAVE_SC_REPR_PTRDIFF_T */

#ifdef HAVE_SC_REPR_SSIZE_T
		case SC_REPR_SSIZE_T:
#if __SIZEOF_SSIZE_T__ == 1
#define NEED_do_int8_t
		goto do_int8_t;
#elif __SIZEOF_SSIZE_T__ == 2
#define NEED_do_int16_t
		goto do_int16_t;
#elif __SIZEOF_SSIZE_T__ == 4
#define NEED_do_int32_t
		goto do_int32_t;
#elif __SIZEOF_SSIZE_T__ == 8
#define NEED_do_int64_t
		goto do_int64_t;
#else /* __SIZEOF_SSIZE_T__ == ... */
#error "Unsupported `__SIZEOF_SSIZE_T__'"
#endif /* __SIZEOF_SSIZE_T__ != ... */
#endif /* HAVE_SC_REPR_SSIZE_T */

#ifdef HAVE_SC_REPR_SIZE_T
		case SC_REPR_SIZE_T:
#if __SIZEOF_SIZE_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SIZE_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SIZE_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SIZE_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SIZE_T__ == ... */
#error "Unsupported `__SIZEOF_SIZE_T__'"
#endif /* __SIZEOF_SIZE_T__ != ... */
#endif /* HAVE_SC_REPR_SIZE_T */

#ifdef HAVE_SC_REPR_SOCKLEN_T
		case SC_REPR_SOCKLEN_T:
#if __SIZEOF_SOCKLEN_T__ == 1
#define NEED_do_uint8_t
		goto do_uint8_t;
#elif __SIZEOF_SOCKLEN_T__ == 2
#define NEED_do_uint16_t
		goto do_uint16_t;
#elif __SIZEOF_SOCKLEN_T__ == 4
#define NEED_do_uint32_t
		goto do_uint32_t;
#elif __SIZEOF_SOCKLEN_T__ == 8
#define NEED_do_uint64_t
		goto do_uint64_t;
#else /* __SIZEOF_SOCKLEN_T__ == ... */
#error "Unsupported `__SIZEOF_SOCKLEN_T__'"
#endif /* __SIZEOF_SOCKLEN_T__ != ... */
#endif /* HAVE_SC_REPR_SOCKLEN_T */


		/* ========== SC_REPR_INT8_T ========== */
#if defined(HAVE_SC_REPR_INT8_T) || defined(NEED_do_int8_t)
#ifdef HAVE_SC_REPR_INT8_T
	case SC_REPR_INT8_T:
#endif /* HAVE_SC_REPR_INT8_T */
#ifdef NEED_do_int8_t
do_int8_t:
#endif /* NEED_do_int8_t */
		format = "%" PRId8;
#define NEED_do_format8
		goto do_format8;
#endif /* HAVE_SC_REPR_INT8_T || NEED_do_int8_t */


		/* ========== SC_REPR_INT16_T ========== */
#if defined(HAVE_SC_REPR_INT16_T) || defined(NEED_do_int16_t)
#ifdef HAVE_SC_REPR_INT16_T
	case SC_REPR_INT16_T:
#endif /* HAVE_SC_REPR_INT16_T */
#ifdef NEED_do_int16_t
do_int16_t:
#endif /* NEED_do_int16_t */
		format = "%" PRId16;
#define NEED_do_format16
		goto do_format16;
#endif /* HAVE_SC_REPR_INT16_T || NEED_do_int16_t */


		/* ========== SC_REPR_INT32_T ========== */
#if defined(HAVE_SC_REPR_INT32_T) || defined(NEED_do_int32_t)
#ifdef HAVE_SC_REPR_INT32_T
	case SC_REPR_INT32_T:
#endif /* HAVE_SC_REPR_INT32_T */
#ifdef NEED_do_int32_t
do_int32_t:
#endif /* NEED_do_int32_t */
		format = "%" PRId32;
#define NEED_do_format32
		goto do_format32;
#endif /* HAVE_SC_REPR_INT32_T || NEED_do_int32_t */


		/* ========== SC_REPR_INT64_T ========== */
#if defined(HAVE_SC_REPR_INT64_T) || defined(NEED_do_int64_t)
#ifdef HAVE_SC_REPR_INT64_T
	case SC_REPR_INT64_T:
#endif /* HAVE_SC_REPR_INT64_T */
#ifdef NEED_do_int64_t
do_int64_t:
#endif /* NEED_do_int64_t */
		format = "%" PRId64;
#define NEED_do_format64
		goto do_format64;
#endif /* HAVE_SC_REPR_INT64_T || NEED_do_int64_t */


		/* ========== SC_REPR_UINT8_T ========== */
#if defined(HAVE_SC_REPR_UINT8_T) || defined(NEED_do_uint8_t)
#ifdef HAVE_SC_REPR_UINT8_T
	case SC_REPR_UINT8_T:
#endif /* HAVE_SC_REPR_UINT8_T */
#ifdef NEED_do_uint8_t
do_uint8_t:
#endif /* NEED_do_uint8_t */
		format = "%" PRIu8;
#define NEED_do_format8
		goto do_format8;
#endif /* HAVE_SC_REPR_UINT8_T || NEED_do_uint8_t */


		/* ========== SC_REPR_UINT16_T ========== */
#if defined(HAVE_SC_REPR_UINT16_T) || defined(NEED_do_uint16_t)
#ifdef HAVE_SC_REPR_UINT16_T
	case SC_REPR_UINT16_T:
#endif /* HAVE_SC_REPR_UINT16_T */
#ifdef NEED_do_uint16_t
do_uint16_t:
#endif /* NEED_do_uint16_t */
		format = "%" PRIu16;
#define NEED_do_format16
		goto do_format16;
#endif /* HAVE_SC_REPR_UINT16_T || NEED_do_uint16_t */


		/* ========== SC_REPR_UINT32_T ========== */
#if defined(HAVE_SC_REPR_UINT32_T) || defined(NEED_do_uint32_t)
#ifdef HAVE_SC_REPR_UINT32_T
	case SC_REPR_UINT32_T:
#endif /* HAVE_SC_REPR_UINT32_T */
#ifdef NEED_do_uint32_t
do_uint32_t:
#endif /* NEED_do_uint32_t */
		format = "%" PRIu32;
#define NEED_do_format32
		goto do_format32;
#endif /* HAVE_SC_REPR_UINT32_T || NEED_do_uint32_t */


		/* ========== SC_REPR_UINT64_T ========== */
#if defined(HAVE_SC_REPR_UINT64_T) || defined(NEED_do_uint64_t)
#ifdef HAVE_SC_REPR_UINT64_T
	case SC_REPR_UINT64_T:
#endif /* HAVE_SC_REPR_UINT64_T */
#ifdef NEED_do_uint64_t
do_uint64_t:
#endif /* NEED_do_uint64_t */
		format = "%" PRIu64;
#define NEED_do_format64
		goto do_format64;
#endif /* HAVE_SC_REPR_UINT64_T || NEED_do_uint64_t */





#ifdef NEED_do_format64
#undef NEED_do_format64
do_format64:
		result = format_printf(printer, arg, format, value.sv_u64);
		break;
#endif /* NEED_do_format64 */

#ifdef NEED_do_format32
#undef NEED_do_format32
do_format32:
		result = format_printf(printer, arg, format, (u32)value.sv_u64);
		break;
#endif /* NEED_do_format32 */

#ifdef NEED_do_format16
#undef NEED_do_format16
do_format16:
		result = format_printf(printer, arg, format, (u16)value.sv_u64);
		break;
#endif /* NEED_do_format16 */

#ifdef NEED_do_format8
#undef NEED_do_format8
do_format8:
		result = format_printf(printer, arg, format, (u8)value.sv_u64);
		break;
#endif /* NEED_do_format8 */

	default:
		result = DOPRINT("?");
		break;
	}
done: ATTR_UNUSED;
	return result;
}

DEFINE_PUBLIC_ALIAS(sc_printvalue, libsc_printvalue);

DECL_END

#endif /* !GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C */
