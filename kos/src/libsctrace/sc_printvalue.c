/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1
#define _DOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _FILE_OFFSET_BITS 32 /* We also need the 32-bit file structures */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__va_size.h>
#include <hybrid/typecore.h>

#include <arpa/inet.h>
#include <asm/ioctl.h>
#include <asm/ioctls/socket.h>
#include <asm/ioctls/socket_ex.h>
#include <asm/ioctls/tty.h>
#include <bits/itimerspec.h>
#include <bits/itimerval.h>
#include <bits/timespec.h>
#include <bits/timeval.h>
#include <kos/anno.h>
#include <kos/dev.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/io.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <linux/fd.h>
#include <linux/fs.h>
#include <linux/futex.h>
#include <linux/hdreg.h>
#include <linux/kd.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <ctype.h>
#include <fcntl.h>
#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sctrace.h"

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/itimerspec.h>
#include <compat/bits/itimerval.h>
#include <compat/bits/timespec.h>
#include <compat/bits/timeval.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifdef __KERNEL__
#include <dev/block.h>
#include <dev/char.h>
#include <kernel/except.h>
#include <kernel/user.h>
#else /* __KERNEL__ */
#define validate_readable(base, num_bytes)                          (void)0
#define validate_readablem(base, num_items, item_size_in_bytes)     (void)0
#define validate_readable_opt(base, num_bytes)                      (void)0
#define validate_readablem_opt(base, num_items, item_size_in_bytes) (void)0
#endif /* !__KERNEL__ */

#ifndef USER
#define USER __USER
#endif /* !USER */

#ifndef CHECKED
#define CHECKED __CHECKED
#endif /* !CHECKED */

#ifndef UNCHECKED
#define UNCHECKED __UNCHECKED
#endif /* !UNCHECKED */


/* Representation limits before printed data is truncated */
#define LIMIT_STRLEN       64 /* Max # of bytes to print from user-supplied strings. */
#define LIMIT_POLLFDS      16 /* Max # of `struct pollfd' structures to print from a vector. */
#define LIMIT_STRINGVECTOR 32 /* Max # of strings to print from a string-vector (such as `argv' and `envp' in `sys_execve()'). */



/* Figure out what we actually need to define. */
#ifdef HAVE_SC_REPR_DEV_T
#define NEED_print_dev_blk
#define NEED_print_dev_chr
#endif /* HAVE_SC_REPR_DEV_T */

#ifdef HAVE_SC_REPR_DEV_BLK
#define NEED_print_dev_blk
#endif /* HAVE_SC_REPR_DEV_BLK */

#ifdef HAVE_SC_REPR_DEV_CHR
#define NEED_print_dev_chr
#endif /* HAVE_SC_REPR_DEV_CHR */

#ifdef HAVE_SC_REPR_MODE_T
#define NEED_print_mode_t
#endif /* HAVE_SC_REPR_MODE_T */

#ifdef HAVE_SC_REPR_OFLAG_T
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG_T */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK */

#ifdef HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT
#define NEED_print_oflag_t
#endif /* HAVE_SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT */

#ifdef HAVE_SC_REPR_ATFLAG_T
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG_T */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH */

#ifdef HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH
#define NEED_print_atflag_t
#endif /* HAVE_SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH */

#ifdef HAVE_SC_REPR_IOMODE_T
#define NEED_print_iomode_t
#endif /* HAVE_SC_REPR_IOMODE_T */

#ifdef HAVE_SC_REPR_FD_T
#define NEED_print_fd_t
#endif /* HAVE_SC_REPR_FD_T */

#ifdef HAVE_SC_REPR_CLOCKID_T
#define NEED_print_clockid_t
#endif /* HAVE_SC_REPR_CLOCKID_T */

#ifdef HAVE_SC_REPR_FILENAME
#define NEED_print_string
#endif /* HAVE_SC_REPR_FILENAME */

#ifdef HAVE_SC_REPR_BUFFER
#define NEED_print_string
#endif /* HAVE_SC_REPR_BUFFER */

#ifdef HAVE_SC_REPR_STRING
#define NEED_print_string
#endif /* HAVE_SC_REPR_STRING */

#ifdef HAVE_SC_REPR_SIGHANDLER_T
#define NEED_print_sighandler_t
#endif /* HAVE_SC_REPR_SIGHANDLER_T */

#ifdef HAVE_SC_REPR_STRUCT_POLLFD
#define NEED_print_pollfds
#endif /* HAVE_SC_REPR_STRUCT_POLLFD */

#ifdef HAVE_SC_REPR_IOCTL_COMMAND
#define NEED_print_ioctl_command
#endif /* HAVE_SC_REPR_IOCTL_COMMAND */

#ifdef HAVE_SC_REPR_STRING_VECTOR
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR */

#ifdef HAVE_SC_REPR_STRING_VECTOR32
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR32 */

#ifdef HAVE_SC_REPR_STRING_VECTOR64
#define NEED_print_string_vector
#endif /* HAVE_SC_REPR_STRING_VECTOR64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3
#define NEED_print_timespec_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64
#define NEED_print_timespec
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2
#define NEED_print_timeval_vector
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64
#define NEED_print_timeval
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 */

#ifdef HAVE_SC_REPR_SIGNO_T
#define NEED_print_signo_t
#endif /* HAVE_SC_REPR_SIGNO_T */

#ifdef HAVE_SC_REPR_SOCKET_DOMAIN
#define NEED_print_socket_domain
#endif /* HAVE_SC_REPR_SOCKET_DOMAIN */

#ifdef HAVE_SC_REPR_SOCKET_PROTOCOL
#define NEED_print_socket_proto
#endif /* HAVE_SC_REPR_SOCKET_PROTOCOL */

#ifdef HAVE_SC_REPR_SOCKET_TYPE
#define NEED_print_socket_type
#endif /* HAVE_SC_REPR_SOCKET_TYPE */

#ifdef HAVE_SC_REPR_STRUCT_SOCKADDR
#define NEED_print_sockaddr
#endif /* HAVE_SC_REPR_STRUCT_SOCKADDR */

#if defined(HAVE_SC_REPR_FCNTL64_COMMAND) || defined(HAVE_SC_REPR_FCNTL_COMMAND)
#define NEED_print_fcntl_command
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND || HAVE_SC_REPR_FCNTL_COMMAND */

#if defined(HAVE_SC_REPR_FCNTL64_ARG) || defined(HAVE_SC_REPR_FCNTL_ARG)
#define NEED_print_fcntl_arg
#endif /* HAVE_SC_REPR_FCNTL64_ARG || HAVE_SC_REPR_FCNTL_ARG */

#ifdef HAVE_SC_REPR_SEEK_WHENCE
#define NEED_print_seek_whence
#endif /* HAVE_SC_REPR_SEEK_WHENCE */





/* Inter-printer dependencies */
#ifdef NEED_print_pollfds
#define NEED_print_pollfd
#endif /* NEED_print_pollfds */

#ifdef NEED_print_pollfd
#define NEED_print_fd_t
#define NEED_print_poll_events
#endif /* NEED_print_pollfd */

#ifdef NEED_print_string_vector
#define NEED_print_string
#endif /* NEED_print_string_vector */

#ifdef NEED_print_timespec_vector
#define NEED_print_timespec
#endif /* NEED_print_timespec_vector */

#ifdef NEED_print_timeval_vector
#define NEED_print_timeval
#endif /* NEED_print_timeval_vector */

#ifdef NEED_print_sockaddr
#define NEED_print_bytes
#define NEED_print_socket_domain
#endif /* NEED_print_sockaddr */

#ifdef NEED_print_socket_domain
#define NEED_print_socket_af_pf
#endif /* NEED_print_socket_domain */

#ifdef NEED_print_socket_proto
#define NEED_print_socket_af_pf
#endif /* NEED_print_socket_proto */

#ifdef NEED_print_fcntl_arg
#define NEED_print_oflag_t
#define NEED_print_fd_flags
#define NEED_print_dn_flags
#define NEED_print_signo_t
#define NEED_print_fd_t
#define NEED_print_f_owner_ex
#define NEED_print_f_lock
#define NEED_print_flock64
#endif /* NEED_print_fcntl_arg */

#ifdef NEED_print_f_owner_ex
#define NEED_print_f_owner_type
#endif /* NEED_print_f_owner_ex */

#ifdef NEED_print_flock64
#define NEED_print_f_lock
#define NEED_print_seek_whence
#endif /* NEED_print_flock64 */




/* Configure special printer extensions */
#undef HAVE_STRING_VECTOR_POINTER_SIZE
#if ((defined(HAVE_SC_REPR_STRING_VECTOR32) && defined(HAVE_SC_REPR_STRING_VECTOR64)) ||                            \
     (defined(HAVE_SC_REPR_STRING_VECTOR) && (defined(HAVE_SC_REPR_STRING_VECTOR32) && __SIZEOF_POINTER__ != 4)) || \
     (defined(HAVE_SC_REPR_STRING_VECTOR) && (defined(HAVE_SC_REPR_STRING_VECTOR64) && __SIZEOF_POINTER__ != 8)))
#define HAVE_STRING_VECTOR_POINTER_SIZE 1
#endif /* ... */

DECL_BEGIN

#define LINUX_FUTEX_USES_TIMEOUT(futex_op)    \
	(((futex_op)&127) == FUTEX_WAIT ||        \
	 ((futex_op)&127) == FUTEX_LOCK_PI ||     \
	 ((futex_op)&127) == FUTEX_WAIT_BITSET || \
	 ((futex_op)&127) == FUTEX_WAIT_REQUEUE_PI)



/* Spacing strings inserted in places to prettify representations. */
#if 0
#define SYNSPACE  ""
#define SYNSPACE2 ""
#elif 1
#define SYNSPACE  ""
#define SYNSPACE2 " "
#else
#define SYNSPACE  " "
#define SYNSPACE2 " "
#endif


/* The syntax to use for struct field names. */
#if 1
#define HAVE_SYNFIELD 1
#define SYNFIELD(name) name ":" SYNSPACE
#elif 1
#define HAVE_SYNFIELD 1
#define SYNFIELD(name) "." name SYNSPACE "=" SYNSPACE
#else
#define SYNFIELD(name) ""
#endif


/* The representation of bit-wide OR in flagsets */
#define PIPESTR_S SYNSPACE "|" SYNSPACE
#define PIPESTR   PIPESTR_S


/* Ensure that `PIPESTR' doesn't get allocated multiple times. */
PRIVATE ATTR_UNUSED char const PIPESTR_[] = PIPESTR;
PRIVATE /*ATTR_UNUSED*/ char const NULLSTR[]  = "NULL";
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
#elif !defined(__DEEMON__)
#error "Unsupported `__VA_SIZE'"
#endif



#ifdef NEED_print_dev_blk
PRIVATE NONNULL((1)) ssize_t CC
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
#endif /* NEED_print_dev_blk */


#ifdef NEED_print_dev_chr
PRIVATE NONNULL((1)) ssize_t CC
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
#endif /* NEED_print_dev_chr */




#ifdef NEED_print_mode_t
PRIVATE struct {
	mode_t mn_mode;    /* Flag value */
	char   mn_name[8]; /* Flag name */
} const mode_names[] = {
	{ S_ISVTX, "S_ISVTX" },
	{ S_ISGID, "S_ISGID" },
	{ S_ISUID, "S_ISUID" }
};

PRIVATE ssize_t CC
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
		is_first = false;
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
#endif /* NEED_print_mode_t */



#ifdef NEED_print_oflag_t
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

PRIVATE ssize_t CC
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
		if ((oflags & oflag_names[i].on_flag) !=
		    /*     */ oflag_names[i].on_flag)
			continue;
#if (O_TMPFILE & O_DIRECTORY) != 0
		if (oflag_names[i].on_flag == O_DIRECTORY &&
		    (oflags & O_TMPFILE) == O_TMPFILE)
			continue;
#endif /* (O_TMPFILE & O_DIRECTORY) != 0 */
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

PRIVATE ssize_t CC
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
#endif /* NEED_print_oflag_t */



#ifdef NEED_print_atflag_t
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

PRIVATE ssize_t CC
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

PRIVATE ssize_t CC
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
#endif /* NEED_print_atflag_t */



#ifdef NEED_print_iomode_t
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

PRIVATE ssize_t CC
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

PRIVATE ssize_t CC
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
#endif /* NEED_print_iomode_t */



#ifdef NEED_print_fd_t
PRIVATE ssize_t CC
print_fd_t(pformatprinter printer, void *arg, fd_t fd) {
	ssize_t result;
	char const *name;
	/* XXX: Don't use a switch() here? */
	switch (fd) {
		/* Deal with symbolic file handles. */
	case AT_FDCWD:          name = "AT_FDCWD"; break;
	case AT_FDROOT:         name = "AT_FDROOT"; break;
	case AT_THIS_TASK:      name = "AT_THIS_TASK"; break;
	case AT_THIS_PROCESS:   name = "AT_THIS_PROCESS"; break;
	case AT_PARENT_PROCESS: name = "AT_PARENT_PROCESS"; break;
	case AT_GROUP_LEADER:   name = "AT_GROUP_LEADER"; break;
	case AT_SESSION_LEADER: name = "AT_SESSION_LEADER"; break;

#if 1 /* <unistd.h> names for certain file handles. */
	case STDIN_FILENO:  name = "STDIN_FILENO"; break;
	case STDOUT_FILENO: name = "STDOUT_FILENO"; break;
	case STDERR_FILENO: name = "STDERR_FILENO"; break;
#endif

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
#endif /* NEED_print_fd_t */



#ifdef NEED_print_clockid_t
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

PRIVATE ssize_t CC
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
#endif /* NEED_print_clockid_t */



#ifdef NEED_print_string
PRIVATE ssize_t CC
print_string(pformatprinter printer, void *arg,
             USER UNCHECKED char const *str,
             struct sc_argument *length_link) {
	ssize_t result;
	if (!str) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else {
		size_t len;
		if (length_link) {
			len = (size_t)length_link->sa_value.sv_u64;
			validate_readable(str, len);
		} else {
			validate_readable(str, 1);
			len = strlen(str);
		}
		if (len > LIMIT_STRLEN) {
			result = format_printf(printer, arg, "%$q...", LIMIT_STRLEN, str);
		} else {
			result = format_printf(printer, arg, "%$q", len, str);
		}
	}
	return result;
}
#endif /* NEED_print_string */



#ifdef NEED_print_sighandler_t
PRIVATE struct {
	sighandler_t sn_hand;    /* Signal handler constant */
	char         sn_name[8]; /* Signal handler name. */
} const sighandler_names[] = {
	{ SIG_ERR,  "ERR" },
	{ SIG_DFL,  "DFL" },
	{ SIG_IGN,  "IGN" },
	{ SIG_HOLD, "HOLD" },
	{ SIG_TERM, "TERM" },
	{ SIG_EXIT, "EXIT" },
	{ SIG_CONT, "CONT" },
	{ SIG_STOP, "STOP" },
	{ SIG_CORE, "CORE" },
	{ SIG_GET,  "GET" }
};

PRIVATE ssize_t CC
print_sighandler_t(pformatprinter printer, void *arg,
                   sighandler_t hand) {
	ssize_t result;
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(sighandler_names); ++i) {
		if (sighandler_names[i].sn_hand == hand) {
			char const *name;
			name   = sighandler_names[i].sn_name;
			result = format_printf(printer, arg, "SIG_%s", name);
			goto done;
		}
	}
	result = format_printf(printer, arg, "%#" PRIxPTR,
	                       *(void **)&hand);
done:
	return result;
}
#endif /* NEED_print_sighandler_t */



#ifdef NEED_print_poll_events
#ifndef POLLRDNORM
#define POLLRDNORM __POLLRDNORM /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* !POLLRDNORM */
#ifndef POLLRDBAND
#define POLLRDBAND __POLLRDBAND /* Priority data may be read. */
#endif /* !POLLRDBAND */
#ifndef POLLWRNORM
#define POLLWRNORM __POLLWRNORM /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* !POLLWRNORM */
#ifndef POLLWRBAND
#define POLLWRBAND __POLLWRBAND /* Priority data may be written. */
#endif /* !POLLWRBAND */

PRIVATE struct {
	uint16_t   pn_flag;
	char const pn_name[8];
} const poll_event_flag_names[] = {
	{ POLLIN,     "IN" },
	{ POLLPRI,    "PRI" },
	{ POLLOUT,    "OUT" },
	{ POLLRDNORM, "RDNORM" },
	{ POLLRDBAND, "RDBAND" },
	{ POLLWRNORM, "WRNORM" },
	{ POLLWRBAND, "WRBAND" },
	{ POLLMSG,    "MSG" },
	{ POLLREMOVE, "REMOVE" },
	{ POLLRDHUP,  "RDHUP" },
	{ POLLERR,    "ERR" },
	{ POLLHUP,    "HUP" },
	{ POLLNVAL,   "NVAL" }
};

PRIVATE ssize_t CC
print_poll_events(pformatprinter printer, void *arg, uint16_t events) {
	enum {
		VALID_MASK = (POLLIN | POLLPRI | POLLOUT | POLLRDNORM |
		              POLLRDBAND | POLLWRNORM | POLLWRBAND |
		              POLLMSG | POLLREMOVE | POLLRDHUP |
		              POLLERR | POLLHUP | POLLNVAL)
	};
	ssize_t temp, result = 0;
	unsigned int i;
	bool is_first = true;
	for (i = 0; i < COMPILER_LENOF(poll_event_flag_names); ++i) {
		char const *name;
		if (!(events & poll_event_flag_names[i].pn_flag))
			continue;
		if (!is_first)
			PRINT(PIPESTR);
		name = poll_event_flag_names[i].pn_name;
		PRINTF("POLL%s", name);
		is_first = false;
	}
	if unlikely(events & ~VALID_MASK) {
		if (!is_first)
			PRINT(PIPESTR);
		PRINTF("%#" PRIx16,
		       (uint16_t)(events & ~VALID_MASK));
		is_first = false;
	}
	if (is_first)
		result = DOPRINT("0");
	return result;
err:
	return temp;
}
#endif /* NEED_print_poll_events */



#ifdef NEED_print_pollfd
PRIVATE ssize_t CC
print_pollfd(pformatprinter printer, void *arg,
             struct pollfd const *__restrict pfd) {
	ssize_t temp, result;
	result = DOPRINT("{" SYNSPACE SYNFIELD("fd"));
	if unlikely(result < 0)
		goto done;
	DO(print_fd_t(printer, arg, pfd->fd));
	PRINT("," SYNSPACE SYNFIELD("events"));
	DO(print_poll_events(printer, arg, pfd->events));
	PRINT(SYNSPACE "}");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_pollfd */



#ifdef NEED_print_pollfds
PRIVATE ssize_t CC
print_pollfds(pformatprinter printer, void *arg,
              USER CHECKED struct pollfd const *fds, size_t count) {
	ssize_t temp, result = 0;
	size_t i, used_count = count;
	if (used_count > LIMIT_POLLFDS)
		used_count = LIMIT_POLLFDS;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < used_count; ++i) {
		struct pollfd pfd;
		if (i != 0)
			PRINT("," SYNSPACE2);
		TRY {
			memcpy(&pfd, &fds[i], sizeof(struct pollfd));
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			PRINT("<segfault>");
			goto done_rbracket;
		}
		DO(print_pollfd(printer, arg, &pfd));
	}
	if (used_count < count)
		PRINT("," SYNSPACE2 "...");
done_rbracket:
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_pollfds */



#ifdef NEED_print_timespec
PRIVATE ssize_t CC
print_timespec(pformatprinter printer, void *arg,
               struct timespec const *__restrict ts) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("tv_sec") "%" PRIdN(__SIZEOF_TIME64_T__)
	                       "," SYNSPACE SYNFIELD("tv_nsec") "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__)
	                       SYNSPACE "}",
	                       ts->tv_sec, ts->tv_nsec);
	return result;
}
#endif /* NEED_print_timespec */




#ifdef NEED_print_timespec_vector
PRIVATE ssize_t CC
print_timespec_vector(pformatprinter printer, void *arg,
                      struct timespec const *__restrict tsv,
                      size_t count) {
	size_t i;
	ssize_t temp, result;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < count; ++i) {
		if (i != 0)
			PRINT("," SYNSPACE2);
		DO(print_timespec(printer, arg, &tsv[i]));
	}
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_timespec_vector */



#ifdef NEED_print_timeval
PRIVATE ssize_t CC
print_timeval(pformatprinter printer, void *arg,
              struct timeval const *__restrict ts) {
	ssize_t result;
	result = format_printf(printer, arg,
	                       "{" SYNSPACE SYNFIELD("tv_sec") "%" PRIdN(__SIZEOF_TIME64_T__)
	                       "," SYNSPACE SYNFIELD("tv_usec") "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__)
	                       SYNSPACE "}",
	                       ts->tv_sec, ts->tv_usec);
	return result;
}
#endif /* NEED_print_timeval */



#ifdef NEED_print_timeval_vector
PRIVATE ssize_t CC
print_timeval_vector(pformatprinter printer, void *arg,
                     struct timeval const *__restrict tsv,
                     size_t count) {
	size_t i;
	ssize_t temp, result;
	result = DOPRINT("[");
	if unlikely(result < 0)
		goto done;
	for (i = 0; i < count; ++i) {
		if (i != 0)
			PRINT("," SYNSPACE2);
		DO(print_timeval(printer, arg, &tsv[i]));
	}
	PRINT("]");
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_timeval_vector */



#if defined(NEED_print_ioctl_command) || defined(__DEEMON__)
/* Use the same trick as also used in libdebuginfo/repr.c to encode
 * symbolic constant names (such as those for ioctl() commands) as
 * efficiently as possible. */

/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
import util;
local ioctls = [];
local kos_ioctls = [];

for (local macroName, macroValue: enumerateMacrosFromFiles({
	"../../include/asm/ioctls/" "*.h",
	"../../include/linux/kd.h",
	"../../include/linux/fd.h",
	"../../include/linux/hdreg.h",
	"../../include/linux/msdos_fs.h",
	"../../include/linux/vt.h",
	"../../include/kos/ioctl/" "*.h",
})) {
	local ns = ioctls;
	for (local prefix: {
		"_IO(", "_IOR(", "_IOW(", "_IOWR(",
		"_IO_KOS(", "_IOR_KOS(", "_IOW_KOS(", "_IOWR_KOS(" }) {
		if (!macroValue.startswith(prefix))
			continue;
		local a, b;
		try {
			a, b = macroValue[#prefix:].scanf(" %[^,], %[^,)] ")...;
			a = getMacroIntValue(a);
			b = getMacroIntValue(b);
		} catch (...) {
			continue;
		}
		if (a < 0 || a > 0xff || b < 0 || b > 0xff)
			continue;
		macroValue = a << 8 | b;
		if ("KOS" in prefix)
			ns = kos_ioctls;
		break;
	}
	if (macroValue !is int)
		continue;
	if (macroValue >= #ns)
		ns.resize(macroValue + 1);
	if (ns[macroValue] is none)
		ns[macroValue] = macroName;
}

printStrendNDatabase("IOCTLS", ioctls);
printStrendNDatabase("KOS_IOCTLS", kos_ioctls);
]]]*/
#define GETBASE_IOCTLS(result, index) \
	(((index) <= 0x2) ? ((result) = repr_IOCTLS_0h, true) : \
	 ((index) >= 0x204 && (index) <= 0x217) ? ((index) -= 0x204, (result) = repr_IOCTLS_204h, true) : \
	 ((index) >= 0x241 && (index) <= 0x25a) ? ((index) -= 0x241, (result) = repr_IOCTLS_241h, true) : \
	 ((index) == 0x290) ? ((index) = 0, (result) = repr_IOCTLS_290h, true) : \
	 ((index) >= 0x301 && (index) <= 0x32b) ? ((index) -= 0x301, (result) = repr_IOCTLS_301h, true) : \
	 ((index) >= 0x125d && (index) <= 0x127f) ? ((index) -= 0x125d, (result) = repr_IOCTLS_125dh, true) : \
	 ((index) >= 0x4300 && (index) <= 0x4303) ? ((index) -= 0x4300, (result) = repr_IOCTLS_4300h, true) : \
	 ((index) >= 0x4b2f && (index) <= 0x4b72) ? ((index) -= 0x4b2f, (result) = repr_IOCTLS_4b2fh, true) : \
	 ((index) >= 0x4bfa && (index) <= 0x4bfb) ? ((index) -= 0x4bfa, (result) = repr_IOCTLS_4bfah, true) : \
	 ((index) >= 0x5401 && (index) <= 0x5460) ? ((index) -= 0x5401, (result) = repr_IOCTLS_5401h, true) : \
	 ((index) >= 0x5600 && (index) <= 0x560f) ? ((index) -= 0x5600, (result) = repr_IOCTLS_5600h, true) : \
	 ((index) >= 0x5877 && (index) <= 0x5879) ? ((index) -= 0x5877, (result) = repr_IOCTLS_5877h, true) : \
	 ((index) >= 0x6601 && (index) <= 0x660b) ? ((index) -= 0x6601, (result) = repr_IOCTLS_6601h, true) : \
	 ((index) >= 0x7201 && (index) <= 0x7213) ? ((index) -= 0x7201, (result) = repr_IOCTLS_7201h, true) : \
	 ((index) >= 0x7601 && (index) <= 0x7602) ? ((index) -= 0x7601, (result) = repr_IOCTLS_7601h, true) : \
	 ((index) >= 0x8901 && (index) <= 0x89b1) ? ((index) -= 0x8901, (result) = repr_IOCTLS_8901h, true) : \
	 ((index) >= 0x89e0 && (index) <= 0x89f0) ? ((index) -= 0x89e0, (result) = repr_IOCTLS_89e0h, true) : false)
PRIVATE char const repr_IOCTLS_0h[] =
"\0FIBMAP\0FIGETBSZ";
PRIVATE char const repr_IOCTLS_204h[] =
"FDGETPRM\0\0\0\0\0\0\0\0\0\0FDGETMAXERRS\0FDGETDRVTYP\0\0FDGETDRVPRM\0FDGETDRV"
"STAT\0FDPOLLDRVSTAT\0\0FDGETFDCSTAT\0\0FDWERRORGET";
PRIVATE char const repr_IOCTLS_241h[] =
"FDCLRPRM\0FDSETPRM\0FDDEFPRM\0\0FDMSGON\0FDMSGOFF\0FDFMTBEG\0FDFMTTRK\0F"
"DFMTEND\0FDSETEMSGTRESH\0FDFLUSH\0FDSETMAXERRS\0\0\0\0\0\0\0\0FDRESET\0\0FDWE"
"RRORCLR\0\0FDRAWCMD\0FDTWADDLE\0FDEJECT";
PRIVATE char const repr_IOCTLS_290h[] =
"FDSETDRVPRM";
PRIVATE char const repr_IOCTLS_301h[] =
"HDIO_GETGEO\0\0\0\0\0\0\0\0\0\0HDIO_GET_DMA\0\0HDIO_GET_IDENTITY\0HDIO_GET_WC"
"ACHE\0\0\0\0\0\0\0\0\0\0\0\0HDIO_GET_BUSSTATE\0\0HDIO_DRIVE_RESET\0\0\0\0\0\0\0\0\0\0\0\0\0"
"\0\0HDIO_SET_WCACHE";
PRIVATE char const repr_IOCTLS_125dh[] =
"BLKROSET\0BLKROGET\0BLKRRPART\0BLKGETSIZE\0BLKFLSBUF\0BLKRASET\0BLKRAG"
"ET\0BLKFRASET\0BLKFRAGET\0BLKSECTSET\0BLKSECTGET\0BLKSSZGET\0\0\0\0\0\0\0\0BL"
"KBSZGET\0BLKBSZSET\0BLKGETSIZE64\0BLKTRACESETUP\0BLKTRACESTART\0BLKTR"
"ACESTOP\0BLKTRACETEARDOWN\0BLKDISCARD\0BLKIOMIN\0BLKIOOPT\0BLKALIGNOF"
"F\0BLKPBSZGET\0BLKDISCARDZEROES\0BLKSECDISCARD\0BLKROTATIONAL\0BLKZER"
"OOUT";
PRIVATE char const repr_IOCTLS_4300h[] =
"CDIO_GETTIME\0\0CDIO_GETBASE\0CDIO_SETWALLCLOCK";
PRIVATE char const repr_IOCTLS_4b2fh[] =
"KIOCSOUND\0KDMKTONE\0KDGETLED\0KDSETLED\0KDGKBTYPE\0KDADDIO\0KDDELIO\0K"
"DENABIO\0KDDISABIO\0\0\0KDSETMODE\0KDGETMODE\0KDMAPDISP\0KDUNMAPDISP\0\0\0"
"GIO_SCRNMAP\0PIO_SCRNMAP\0\0\0KDGKBMODE\0KDSKBMODE\0KDGKBENT\0KDSKBENT\0"
"KDGKBSENT\0KDSKBSENT\0KDGKBDIACR\0KDSKBDIACR\0KDGETKEYCODE\0KDSETKEYC"
"ODE\0KDSIGACCEPT\0\0\0\0KDKBDREP\0\0\0\0\0\0\0\0\0\0\0\0\0\0GIO_FONT\0PIO_FONT\0KDGKB"
"META\0KDSKBMETA\0KDGKBLED\0KDSKBLED\0GIO_UNIMAP\0PIO_UNIMAP\0PIO_UNIMA"
"PCLR\0GIO_UNISCRNMAP\0PIO_UNISCRNMAP\0GIO_FONTX\0PIO_FONTX\0PIO_FONTR"
"ESET\0\0\0GIO_CMAP\0PIO_CMAP\0KDFONTOP";
PRIVATE char const repr_IOCTLS_4bfah[] =
"KDGKBDIACRUC\0KDSKBDIACRUC";
PRIVATE char const repr_IOCTLS_5401h[] =
"TCGETS\0TCSETS\0TCSETSW\0TCSETSF\0TCGETA\0TCSETA\0TCSETAW\0TCSETAF\0TCSB"
"RK\0TCXONC\0TCFLSH\0TIOCEXCL\0TIOCNXCL\0TIOCSCTTY\0TIOCGPGRP\0TIOCSPGRP"
"\0TIOCOUTQ\0TIOCSTI\0TIOCGWINSZ\0TIOCSWINSZ\0TIOCMGET\0TIOCMBIS\0TIOCMB"
"IC\0TIOCMSET\0TIOCGSOFTCAR\0TIOCSSOFTCAR\0TIOCINQ\0TIOCLINUX\0TIOCCONS"
"\0TIOCGSERIAL\0TIOCSSERIAL\0TIOCPKT\0FIONBIO\0TIOCNOTTY\0TIOCSETD\0TIOC"
"GETD\0TCSBRKP\0\0TIOCSBRK\0TIOCCBRK\0TIOCGSID\0TCGETS2\0TCSETS2\0TCSETSW"
"2\0TCSETSF2\0TIOCGRS485\0TIOCSRS485\0TIOCGPTN\0TIOCSPTLCK\0TIOCGDEV\0TC"
"SETX\0TCSETXF\0TCSETXW\0TIOCSIG\0TIOCVHANGUP\0TIOCGPKT\0TIOCGPTLCK\0\0\0\0"
"\0\0\0TIOCGEXCL\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0FIONCLEX\0FIOCLEX\0FIOASYNC\0TIOCSERCON"
"FIG\0TIOCSERGWILD\0TIOCSERSWILD\0TIOCGLCKTRMIOS\0TIOCSLCKTRMIOS\0TIOC"
"SERGSTRUCT\0TIOCSERGETLSR\0TIOCSERGETMULTI\0TIOCSERSETMULTI\0TIOCMIW"
"AIT\0TIOCGICOUNT\0\0\0FIOQSIZE";
PRIVATE char const repr_IOCTLS_5600h[] =
"VT_OPENQRY\0VT_GETMODE\0VT_SETMODE\0VT_GETSTATE\0VT_SENDSIG\0VT_RELDI"
"SP\0VT_ACTIVATE\0VT_WAITACTIVE\0VT_DISALLOCATE\0VT_RESIZE\0VT_RESIZEX"
"\0VT_LOCKSWITCH\0VT_UNLOCKSWITCH\0VT_GETHIFONTMASK\0VT_WAITEVENT\0VT_"
"SETACTIVATE";
PRIVATE char const repr_IOCTLS_5877h[] =
"FIFREEZE\0FITHAW\0FITRIM";
PRIVATE char const repr_IOCTLS_6601h[] =
"FS_IOC_GETFLAGS\0FS_IOC_SETFLAGS\0\0\0\0\0\0\0\0\0FS_IOC_FIEMAP";
PRIVATE char const repr_IOCTLS_7201h[] =
"VFAT_IOCTL_READDIR_BOTH\0VFAT_IOCTL_READDIR_SHORT\0\0\0\0\0\0\0\0\0\0\0\0\0\0FA"
"T_IOCTL_GET_ATTRIBUTES\0FAT_IOCTL_SET_ATTRIBUTES\0\0FAT_IOCTL_GET_V"
"OLUME_ID";
PRIVATE char const repr_IOCTLS_7601h[] =
"FS_IOC_GETVERSION\0FS_IOC_SETVERSION";
PRIVATE char const repr_IOCTLS_8901h[] =
"FIOSETOWN\0SIOCSPGRP\0FIOGETOWN\0SIOCGPGRP\0SIOCATMARK\0__SIOCGSTAMP3"
"2\0__SIOCGSTAMPNS32\0\0\0\0SIOCADDRT\0SIOCDELRT\0SIOCRTMSG\0\0\0SIOCGIFNAM"
"E\0SIOCSIFLINK\0SIOCGIFCONF\0SIOCGIFFLAGS\0SIOCSIFFLAGS\0SIOCGIFADDR\0"
"SIOCSIFADDR\0SIOCGIFDSTADDR\0SIOCSIFDSTADDR\0SIOCGIFBRDADDR\0SIOCSIF"
"BRDADDR\0SIOCGIFNETMASK\0SIOCSIFNETMASK\0SIOCGIFMETRIC\0SIOCSIFMETRI"
"C\0SIOCGIFMEM\0SIOCSIFMEM\0SIOCGIFMTU\0SIOCSIFMTU\0SIOCSIFNAME\0SIOCSI"
"FHWADDR\0SIOCGIFENCAP\0SIOCSIFENCAP\0SIOCGIFHWADDR\0\0SIOCGIFSLAVE\0\0\0"
"\0\0\0\0SIOCSIFSLAVE\0SIOCADDMULTI\0SIOCDELMULTI\0SIOCGIFINDEX\0SIOCSIFP"
"FLAGS\0SIOCGIFPFLAGS\0SIOCDIFADDR\0SIOCSIFHWBROADCAST\0SIOCGIFCOUNT\0"
"\0\0\0\0\0\0\0SIOCGIFBR\0SIOCSIFBR\0SIOCGIFTXQLEN\0SIOCSIFTXQLEN\0\0\0SIOCETH"
"TOOL\0SIOCGMIIPHY\0SIOCGMIIREG\0SIOCSMIIREG\0SIOCWANDEV\0SIOCOUTQNSD\0"
"\0\0\0\0\0\0\0SIOCDARP\0SIOCGARP\0SIOCSARP\0\0\0\0\0\0\0\0\0\0\0SIOCDRARP\0SIOCGRARP\0"
"SIOCSRARP\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCGIFMAP\0SIOCSIFMAP\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCA"
"DDDLCI\0SIOCDELDLCI\0SIOCGIFVLAN\0SIOCSIFVLAN\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCBONDE"
"NSLAVE\0SIOCBONDRELEASE\0SIOCBONDSETHWADDR\0SIOCBONDSLAVEINFOQUERY\0"
"SIOCBONDINFOQUERY\0SIOCBONDCHANGEACTIVE\0\0\0\0\0\0\0\0\0\0\0SIOCBRADDBR\0SIO"
"CBRDELBR\0SIOCBRADDIF\0SIOCBRDELIF\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCSHWTSTAMP\0SIOCG"
"HWTSTAMP";
PRIVATE char const repr_IOCTLS_89e0h[] =
"SIOCPROTOPRIVATE\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SIOCDEVPRIVATE";

#define GETBASE_KOS_IOCTLS(result, index) \
	(((index) >= 0x4b00 && (index) <= 0x4b08) ? ((index) -= 0x4b00, (result) = repr_KOS_IOCTLS_4b00h, true) : \
	 ((index) >= 0x4d00 && (index) <= 0x4d07) ? ((index) -= 0x4d00, (result) = repr_KOS_IOCTLS_4d00h, true) : \
	 ((index) >= 0x5400 && (index) <= 0x5403) ? ((index) -= 0x5400, (result) = repr_KOS_IOCTLS_5400h, true) : \
	 ((index) >= 0x5600 && (index) <= 0x5602) ? ((index) -= 0x5600, (result) = repr_KOS_IOCTLS_5600h, true) : false)
PRIVATE char const repr_KOS_IOCTLS_4b00h[] =
"KBDIO_TRYGETKEY\0KBDIO_GETKEY\0KBDIO_GETLED\0KBDIO_GETKEYMAP\0KBDIO_"
"FLUSHPENDING\0KBDIO_PUTCHAR\0KBDIO_PUTKEY\0KBDIO_GETDBGF12\0KBDIO_GE"
"TMOD";
PRIVATE char const repr_KOS_IOCTLS_4d00h[] =
"MOUSEIO_GETABSMODE\0MOUSEIO_GETABSRECT\0MOUSEIO_PUTMOTION\0MOUSEIO_"
"GETPOS\0MOUSEIO_GETBUTTONS\0MOUSEIO_PUTVWHEEL\0MOUSEIO_PUTHWHEEL\0MO"
"USEIO_FLUSHPENDING";
PRIVATE char const repr_KOS_IOCTLS_5400h[] =
"TTYIO_IBUF_GETLIMIT\0TTYIO_CANON_GETLIMIT\0TTYIO_OPEND_GETLIMIT\0TT"
"YIO_IPEND_GETLIMIT";
PRIVATE char const repr_KOS_IOCTLS_5600h[] =
"VIDEOIO_LISTFORMAT\0VIDEOIO_GETFORMAT\0VIDEOIO_GETPAL";
//[[[end]]]

PRIVATE ATTR_CONST WUNUSED char const *CC
get_ioctl_command_name(syscall_ulong_t command) {
	char const *result = NULL;
	if (_IOC_ISKOS(command)) {
		command &= 0xffff;
		if (!GETBASE_KOS_IOCTLS(result, command))
			goto done;
	} else {
		command &= 0xffff;
		if (!GETBASE_IOCTLS(result, command))
			goto done;
	}
	for (; command; --command)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ssize_t CC
print_ioctl_command_size(pformatprinter printer, void *arg, size_t size) {
	ssize_t result;
	char const *name;
	switch (size) {
	case 1:  name = "uint8_t"; break;
	case 2:  name = "uint16_t"; break;
	case 4:  name = "uint32_t"; break;
	case 8:  name = "uint64_t"; break;
	default: name = NULL; break;
	}
	if (name) {
		result = (*printer)(arg, name, strlen(name));
	} else {
		result = format_printf(printer, arg, "byte_t[%" PRIuSIZ "]", size);
	}
	return result;
}

PRIVATE ssize_t CC
print_ioctl_type(pformatprinter printer, void *arg,
                 syscall_ulong_t type) {
	ssize_t result;
	if (type <= 0x7f && isprint((int)(unsigned int)type)) {
		result = format_printf(printer, arg, "'%c'",
		                       (int)(unsigned int)type);
	} else {
		result = format_printf(printer, arg, "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		                       type);
	}
	return result;
}

PRIVATE ssize_t CC
print_ioctl_command(pformatprinter printer, void *arg,
                    syscall_ulong_t command) {
	char const *name;
	ssize_t temp, result;
	name = get_ioctl_command_name(command);
	if (name) {
		result = (*printer)(arg, name, strlen(name));
#if __SIZEOF_SYSCALL_LONG_T__ > 4
	} else if (command > UINT32_MAX) {
		goto do_print_hex_repr;
#endif /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
	} else {
		syscall_ulong_t nr, type, size, kos, dir;
		nr   = _IOC_NR(command);
		type = _IOC_TYPE(command);
		size = _IOC_SIZE(command);
		kos  = _IOC_ISKOS(command);
		dir  = _IOC_DIR(command);
		if (dir || kos || size || type) {
			result = DOPRINT("_IO");
			if unlikely(result < 0)
				goto done;
			if (dir == _IOC_NONE) {
				if (size != 0) {
					PRINT("C");
					if (kos)
						PRINT("_KOS");
					PRINT("(_IOC_NONE," SYNSPACE);
					DO(print_ioctl_type(printer, arg, type));
					DO(format_printf(printer, arg,
					                 "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__)
					                 "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__) ")",
					                 nr, size));
					goto done;
				}
				temp = 0;
			} else if (dir == _IOC_READ) {
				temp = DOPRINT("R");
			} else if (dir == _IOC_WRITE) {
				temp = DOPRINT("W");
			} else /*if (dir == (_IOC_WRITE | _IOC_READ))*/ {
				temp = DOPRINT("WR");
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
			if (kos)
				PRINT("_KOS");
			PRINT("(");
			DO(print_ioctl_type(printer, arg, type));
			DO(format_printf(printer, arg, "," SYNSPACE "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__), nr));
			if (dir != _IOC_NONE) {
				PRINT("," SYNSPACE);
				DO(print_ioctl_command_size(printer, arg, size));
			}
			PRINT(")");
		} else {
#if __SIZEOF_SYSCALL_LONG_T__ > 4
do_print_hex_repr:
#endif /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
			result = format_printf(printer, arg,
			                       "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
			                       command);
		}
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_ioctl_command */



#ifdef NEED_print_string_vector
PRIVATE ssize_t CC
print_string_vector(pformatprinter printer, void *arg,
                    USER UNCHECKED char const *USER UNCHECKED const *vector
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
                    ,
                    size_t sizeof_pointer
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
                    ) {
#ifndef HAVE_STRING_VECTOR_POINTER_SIZE
	enum { sizeof_pointer = sizeof(void *) };
#endif /* !HAVE_STRING_VECTOR_POINTER_SIZE */
	ssize_t temp, result;
	if (!vector) {
		result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
	} else {
		size_t i;
		validate_readable(vector, sizeof_pointer);
		result = (*printer)(arg, "[", 1);
		if unlikely(result < 0)
			goto done;
		for (i = 0;; ++i) {
			USER UNCHECKED char const *string;
			TRY {
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
				if (sizeof_pointer == 4) {
					string = (USER UNCHECKED char const *)(uintptr_t)((uint32_t *)vector)[i];
				} else {
					string = (USER UNCHECKED char const *)(uintptr_t)((uint64_t *)vector)[i];
				}
#else /* HAVE_STRING_VECTOR_POINTER_SIZE */
				string = vector[i];
#endif /* !HAVE_STRING_VECTOR_POINTER_SIZE */
			} EXCEPT {
				if (!was_thrown(E_SEGFAULT))
					RETHROW();
				PRINT("<segfault>");
				break;
			}
			if (!string)
				break;
			if (i != 0)
				PRINT("," SYNSPACE2);
			if (i >= LIMIT_STRINGVECTOR) {
				PRINT("...");
				break;
			}
			TRY {
				DO(print_string(printer, arg, string, NULL));
			} EXCEPT {
				if (!was_thrown(E_SEGFAULT))
					RETHROW();
				PRINT("<segfault>");
			}
		}
		PRINT("]");
	}
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_string_vector */



#if defined(NEED_print_signo_t) || defined(__DEEMON__)
#if defined(__KERNEL__) || defined(__DEEMON__) || defined(__INTELLISENSE__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;

function getSigno(filename: string, prefix: string): {string...} {
	local result = [];
	for (local macroName, macroValue: enumerateMacrosFromFile(filename)) {
		if (!macroName.startswith(prefix))
			continue;
		macroName = macroName[#prefix:];
		if (macroName in ["RTMIN", "RTMAX"])
			continue;
		if (macroName.startswith("_"))
			continue;
		macroValue = getMacroIntValue(macroValue);
		if (macroValue !is int)
			continue;
		if (macroValue >= #result)
			result.resize(macroValue + 1);
		if (result[macroValue] is none)
			result[macroValue] = macroName;
	}
	return result;
}

print("#if defined(__x86_64__) || defined(__i386__)");
printStrendNDatabase("SIGNO", getSigno("../../include/i386-kos/asm/signum-values-kos.h", "__KOS_SIG"));
print("#else /" "* ... *" "/");
printStrendNDatabase("SIGNO", getSigno("../../include/asm/signum-values.h", "__SIG"));
print("#endif /" "* !... *" "/");

]]]*/
#if defined(__x86_64__) || defined(__i386__)
#define GETBASE_SIGNO(result, index) \
	(((index) <= 0x1f) ? ((result) = repr_SIGNO_0h, true) : false)
PRIVATE char const repr_SIGNO_0h[] =
"\0HUP\0INT\0QUIT\0ILL\0TRAP\0ABRT\0BUS\0FPE\0KILL\0USR1\0SEGV\0USR2\0PIPE\0ALR"
"M\0TERM\0STKFLT\0CHLD\0CONT\0STOP\0TSTP\0TTIN\0TTOU\0URG\0XCPU\0XFSZ\0VTALRM"
"\0PROF\0WINCH\0IO\0PWR\0SYS";

#else /* ... */
#define GETBASE_SIGNO(result, index) \
	(((index) <= 0x1f) ? ((result) = repr_SIGNO_0h, true) : false)
PRIVATE char const repr_SIGNO_0h[] =
"\0HUP\0INT\0QUIT\0ILL\0TRAP\0ABRT\0BUS\0FPE\0KILL\0USR1\0SEGV\0USR2\0PIPE\0ALR"
"M\0TERM\0STKFLT\0CHLD\0CONT\0STOP\0TSTP\0TTIN\0TTOU\0URG\0XCPU\0XFSZ\0VTALRM"
"\0PROF\0WINCH\0IO\0PWR\0SYS";

#endif /* !... */
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *CC
get_signo_name(syscall_ulong_t signo) {
	char const *result = NULL;
	if (!GETBASE_SIGNO(result, signo))
		goto done;
	for (; signo; --signo)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#else /* __KERNEL__ || ... */
#define get_signo_name(signo) strsignal_s(signo)
#endif /* !__KERNEL__ && !... */

PRIVATE ssize_t CC
print_signo_t(pformatprinter printer, void *arg, signo_t signo) {
	char const *name = get_signo_name(signo);
	if (name) {
#ifdef __KERNEL__
		return format_printf(printer, arg, "SIG%s", name);
#else /* __KERNEL__ */
		return (*printer)(arg, name, strlen(name));
#endif /* !__KERNEL__ */
	}
	if (signo >= __SIGRTMIN && signo <= __SIGRTMAX) {
		return format_printf(printer, arg, "SIGRTMIN+%d",
		                     (int)(signo - __SIGRTMIN));
	} else {
		/* Fallback: Print the integer value */
		return format_printf(printer, arg, "%d", signo);
	}
}
#endif /* NEED_print_signo_t */



#if defined(NEED_print_socket_af_pf) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local sockaf = getPrefixedMacrosFromFile("../../include/asm/socket.h", "__AF_");
local sockpf = getPrefixedMacrosFromFile("../../include/asm/socket.h", "__PF_");

printStrendNDatabase("SOCKAF", sockaf);
if (sockaf == sockpf) {
	print("#define GETBASE_SOCKPF_IS_SOCKAF");
	print("#define GETBASE_SOCKPF GETBASE_SOCKAF");
} else {
	printStrendNDatabase("SOCKPF", sockpf);
}
]]]*/
#define GETBASE_SOCKAF(result, index) \
	(((index) <= 0x29) ? ((result) = repr_SOCKAF_0h, true) : false)
PRIVATE char const repr_SOCKAF_0h[] =
"UNSPEC\0LOCAL\0INET\0AX25\0IPX\0APPLETALK\0NETROM\0BRIDGE\0ATMPVC\0X25\0IN"
"ET6\0ROSE\0DECnet\0NETBEUI\0SECURITY\0KEY\0NETLINK\0PACKET\0ASH\0ECONET\0A"
"TMSVC\0RDS\0SNA\0IRDA\0PPPOX\0WANPIPE\0LLC\0IB\0MPLS\0CAN\0TIPC\0BLUETOOTH\0"
"IUCV\0RXRPC\0ISDN\0PHONET\0IEEE802154\0CAIF\0ALG\0NFC\0VSOCK\0MAX";

#define GETBASE_SOCKPF_IS_SOCKAF
#define GETBASE_SOCKPF GETBASE_SOCKAF
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *CC
get_socket_domain_name(syscall_ulong_t domain) {
	char const *result = NULL;
	if (!GETBASE_SOCKAF(result, domain))
		goto done;
	for (; domain; --domain)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#ifdef GETBASE_SOCKPF_IS_SOCKAF
#define get_socket_proto_name get_socket_domain_name
#else /* GETBASE_SOCKPF_IS_SOCKAF */
PRIVATE ATTR_CONST WUNUSED char const *CC
get_socket_proto_name(syscall_ulong_t proto) {
	char const *result = NULL;
	if (!GETBASE_SOCKPF(result, proto))
		goto done;
	for (; proto; --proto)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}
#endif /* !GETBASE_SOCKPF_IS_SOCKAF */

#endif /* NEED_print_socket_af_pf */



#ifdef NEED_print_socket_domain
PRIVATE ssize_t CC
print_socket_domain(pformatprinter printer, void *arg,
                    syscall_ulong_t domain) {
	char const *name;
	name = get_socket_domain_name(domain);
	if (name)
		return format_printf(printer, arg, "AF_%s", name);
	/* Fallback: Print the integer value */
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     domain);
}
#endif /* NEED_print_socket_domain */



#ifdef NEED_print_socket_proto
PRIVATE ssize_t CC
print_socket_proto(pformatprinter printer, void *arg,
                   syscall_ulong_t proto) {
	char const *name;
	name = get_socket_proto_name(proto);
	if (name)
		return format_printf(printer, arg, "PF_%s", name);
	/* Fallback: Print the integer value */
	return format_printf(printer, arg,
	                     "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__),
	                     proto);
}
#endif /* NEED_print_socket_proto */



#if defined(NEED_print_socket_type) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFile("../../include/asm/socket.h", "__SOCK_");
printStrendNDatabase("SOCKTYPE", typ[:255]);
]]]*/
#define GETBASE_SOCKTYPE(result, index) \
	(((index) <= 0xa) ? ((result) = repr_SOCKTYPE_0h, true) : false)
PRIVATE char const repr_SOCKTYPE_0h[] =
"\0STREAM\0DGRAM\0RAW\0RDM\0SEQPACKET\0DCCP\0\0\0\0PACKET";
/*[[[end]]]*/


PRIVATE ATTR_CONST WUNUSED char const *CC
get_socket_type_name(syscall_ulong_t type) {
	char const *result = NULL;
	if (!GETBASE_SOCKTYPE(result, type))
		goto done;
	for (; type; --type)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ssize_t CC
print_socket_type(pformatprinter printer, void *arg,
                  syscall_ulong_t type) {
	syscall_ulong_t flags;
	char const *type_name;
	ssize_t temp, result;
	flags = type & (SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK);
	type &= ~(SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK);
	type_name = get_socket_type_name(type & SOCK_TYPEMASK);
	if (type_name) {
		result = format_printf(printer, arg,
		                       "SOCK_%s",
		                       type_name);
	} else {
		result = format_printf(printer, arg,
		                       "%#x",
		                       (unsigned int)(type & SOCK_TYPEMASK));
	}
	type &= ~SOCK_TYPEMASK;
	if (type != 0) {
		DO(format_printf(printer, arg,
		                 PIPESTR_S "%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		                 type));
	}
	/* Append flags */
	if (flags & SOCK_CLOEXEC)
		PRINT(PIPESTR_S "SOCK_CLOEXEC");
	if (flags & SOCK_CLOFORK)
		PRINT(PIPESTR_S "SOCK_CLOFORK");
	if (flags & SOCK_NONBLOCK)
		PRINT(PIPESTR_S "SOCK_NONBLOCK");
	return result;
err:
	return temp;
}
#endif /* NEED_print_socket_type */



#ifdef NEED_print_bytes
PRIVATE ssize_t CC
print_bytes(pformatprinter printer, void *arg,
            USER CHECKED void const *buf, size_t len) {
	ssize_t temp, result = 0;
	size_t i;
	for (i = 0; i < len; ++i) {
		byte_t b;
		b = ((USER CHECKED byte_t const *)buf)[i];
		if (i != 0)
			PRINT("," SYNSPACE);
		PRINTF("%#.2" PRIx8, b);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_bytes */



#ifdef NEED_print_sockaddr
PRIVATE ssize_t CC
print_sockaddr(pformatprinter printer, void *arg,
               USER CHECKED struct sockaddr const *sa,
               socklen_t len) {
	ssize_t temp, result = 0;
	sa_family_t family = AF_UNSPEC;
	USER CHECKED byte_t const *payload_data;
	size_t payload_len = 0;
#ifdef HAVE_SYNFIELD
	char const *family_prefix;
#endif /* HAVE_SYNFIELD */
	payload_data = (USER CHECKED byte_t const *)sa + offsetafter(struct sockaddr, sa_family);
	if likely(len >= offsetafter(struct sockaddr, sa_family)) {
		payload_len = len - offsetafter(struct sockaddr, sa_family);
		family      = sa->sa_family;
	}
#ifdef HAVE_SYNFIELD
	family_prefix = "sa";
	switch (family) {
	case AF_UNIX: family_prefix = "sun"; break; /* struct sockaddr_un */
	case AF_INET: family_prefix = "sin"; break; /* struct sockaddr_in */
	default: break;
	}
	PRINTF("{" SYNSPACE SYNFIELD("%s_family"), family_prefix);
#else /* HAVE_SYNFIELD */
	PRINT("{" SYNSPACE SYNFIELD(-));
#endif /* !HAVE_SYNFIELD */
	DO(print_socket_domain(printer, arg, family));
	switch (family) {

	case AF_UNIX:
		/* struct sockaddr_un */
		PRINTF("," SYNSPACE SYNFIELD("sun_path") "%.?q",
		       payload_len, payload_data);
		break;

	case AF_INET: {
		/* struct sockaddr_in */
		char buf[INET_NTOA_R_MAXLEN];
		USER CHECKED struct sockaddr_in const *sin;
		if unlikely(len < offsetafter(struct sockaddr_in, sin_addr))
			goto fallback;
		sin = (USER CHECKED struct sockaddr_in const *)sa;
		PRINTF("," SYNSPACE SYNFIELD("sin_port") "%" PRIu16
		       "," SYNSPACE SYNFIELD("sin_addr") "%q",
		       sin->sin_port, inet_ntoa_r(sin->sin_addr, buf));
	}	break;

	default:
fallback:
#ifdef HAVE_SYNFIELD
		PRINTF("," SYNSPACE SYNFIELD("%s_data") "{" SYNSPACE, family_prefix);
#else /* HAVE_SYNFIELD */
		PRINT("," SYNSPACE SYNFIELD(-) "{" SYNSPACE);
#endif /* !HAVE_SYNFIELD */
		DO(print_bytes(printer, arg, payload_data, payload_len));
		PRINT(SYNSPACE "}");
		break;
	}
	PRINT(SYNSPACE "}");
	return result;
err:
	return temp;
}
#endif /* NEED_print_sockaddr */



#if defined(NEED_print_seek_whence) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFile("../../include/asm/stdio.h", "__SEEK_");
printStrendNDatabase("SEEK", typ);
]]]*/
#define GETBASE_SEEK(result, index) \
	(((index) <= 0x4) ? ((result) = repr_SEEK_0h, true) : false)
PRIVATE char const repr_SEEK_0h[] =
"SET\0CUR\0END\0DATA\0HOLE";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *CC
get_seek_whence_name(syscall_ulong_t whence) {
	char const *result = NULL;
	if (!GETBASE_SEEK(result, whence))
		goto done;
	for (; whence; --whence)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ssize_t CC
print_seek_whence(pformatprinter printer, void *arg,
                  syscall_ulong_t whence) {
	char const *name;
	name = get_seek_whence_name(whence);
	if (name)
		return format_printf(printer, arg, "SEEK_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), whence);
}
#endif /* NEED_print_seek_whence */





#if defined(NEED_print_fcntl_command) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFile("../../include/asm/fcntl.h", "__F_");
printStrendNDatabase("FCNTL", typ);
]]]*/
#define GETBASE_FCNTL(result, index) \
	(((index) <= 0x26) ? ((result) = repr_FCNTL_0h, true) : \
	 ((index) >= 0x400 && (index) <= 0x408) ? ((index) -= 0x400, (result) = repr_FCNTL_400h, true) : \
	 ((index) >= 0x142b && (index) <= 0x1430) ? ((index) -= 0x142b, (result) = repr_FCNTL_142bh, true) : false)
PRIVATE char const repr_FCNTL_0h[] =
"DUPFD\0GETFD\0SETFD\0GETFL\0SETFL\0GETLK\0SETLK\0SETLKW\0SETOWN\0GETOWN\0S"
"ETSIG\0GETSIG\0GETLK64\0SETLK64\0SETLKW64\0SETOWN_EX\0GETOWN_EX\0\0\0\0\0\0\0"
"\0\0\0\0\0\0\0\0\0\0\0\0\0OFD_GETLK\0OFD_SETLK\0OFD_SETLKW";
PRIVATE char const repr_FCNTL_400h[] =
"SETLEASE\0GETLEASE\0NOTIFY\0\0\0\0DUPFD_CLOEXEC\0SETPIPE_SZ\0GETPIPE_SZ";
PRIVATE char const repr_FCNTL_142bh[] =
"SETFL_XCH\0NEXT\0CLOSEM\0MAXFD\0DUP2FD\0DUP2FD_CLOEXEC";
/*[[[end]]]*/

PRIVATE ATTR_CONST WUNUSED char const *CC
get_fcntl_command_name(syscall_ulong_t cmd) {
	char const *result = NULL;
	if (!GETBASE_FCNTL(result, cmd))
		goto done;
	for (; cmd; --cmd)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ssize_t CC
print_fcntl_command(pformatprinter printer, void *arg,
                    syscall_ulong_t cmd) {
	char const *name;
	name = get_fcntl_command_name(cmd);
	if (name)
		return format_printf(printer, arg, "F_%s", name);
	return format_printf(printer, arg, "%" PRIuN(__SIZEOF_SYSCALL_LONG_T__), cmd);
}
#endif /* NEED_print_fcntl_command */





#ifdef NEED_print_fd_flags
PRIVATE ssize_t CC
print_fd_flags(pformatprinter printer, void *arg,
               syscall_ulong_t fd_flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	if (fd_flags & FD_CLOEXEC) {
		PRINT("FD_CLOEXEC");
		fd_flags &= ~FD_CLOEXEC;
		is_first = false;
	}
	if (fd_flags & FD_CLOFORK) {
		PRINTF("%sFD_CLOFORK", is_first ? "" : PIPESTR);
		fd_flags &= ~FD_CLOFORK;
		is_first = false;
	}
	if (fd_flags) {
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, fd_flags);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_fd_flags */





#ifdef NEED_print_dn_flags
struct dn_flag_name {
	__uint32_t dfn_flag;
	char       dfn_name[12];
};
PRIVATE struct dn_flag_name const dn_flag_names[] = {
	{ DN_ACCESS, /*   */ "ACCESS" },
	{ DN_MODIFY, /*   */ "MODIFY" },
	{ DN_CREATE, /*   */ "CREATE" },
	{ DN_DELETE, /*   */ "DELETE" },
	{ DN_RENAME, /*   */ "RENAME" },
	{ DN_ATTRIB, /*   */ "ATTRIB" },
	{ DN_MULTISHOT, /**/ "MULTISHOT" },
};

PRIVATE ssize_t CC
print_dn_flags(pformatprinter printer, void *arg,
               syscall_ulong_t dn_flags) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(dn_flag_names); ++i) {
		if (!(dn_flags & dn_flag_names[i].dfn_flag))
			continue;
		PRINTF("%sDN_%s", is_first ? "" : PIPESTR,
		       dn_flag_names[i].dfn_name);
		dn_flags &= ~dn_flag_names[i].dfn_flag;
		is_first = false;
	}
	if (dn_flags) {
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, dn_flags);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_dn_flags */





#if defined(NEED_print_f_owner_type) || defined(__DEEMON__)
/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
local typ = getPrefixedMacrosFromFile("../../include/asm/fcntl.h", "__F_OWNER_");
printStrendNDatabase("F_OWNER", typ);
]]]*/
#define GETBASE_F_OWNER(result, index) \
	(((index) <= 0x2) ? ((result) = repr_F_OWNER_0h, true) : false)
PRIVATE char const repr_F_OWNER_0h[] =
"TID\0PID\0PGRP";
/*[[[end]]]*/
PRIVATE ATTR_CONST WUNUSED char const *CC
get_f_owner_name(unsigned int type) {
	char const *result = NULL;
	if (!GETBASE_FCNTL(result, type))
		goto done;
	for (; type; --type)
		result = strend(result) + 1;
	if (!*result)
		result = NULL;
done:
	return result;
}

PRIVATE ssize_t CC
print_f_owner_type(pformatprinter printer, void *arg,
                   unsigned int type) {
	char const *name;
	name = get_f_owner_name(type);
	if (name)
		return format_printf(printer, arg, "F_OWNER_%s", name);
	return format_printf(printer, arg, "%u", type);
}
#endif /* NEED_print_f_owner_type */





#ifdef NEED_print_f_lock
struct f_lock_name {
	__uint8_t f_lock;
	char      f_name[3];
};
PRIVATE struct f_lock_name const f_lock_names[] = {
	{ F_RDLCK, "RD" },
	{ F_WRLCK, "WR" },
	{ F_UNLCK, "UN" },
	{ F_EXLCK, "EX" },
	{ F_SHLCK, "SH" }
};

PRIVATE ssize_t CC
print_f_lock(pformatprinter printer, void *arg,
             syscall_ulong_t lock) {
	ssize_t temp, result = 0;
	bool is_first = true;
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(f_lock_names); ++i) {
		if (!(lock & f_lock_names[i].f_lock))
			continue;
		PRINTF("%sF_%sLCK", is_first ? "" : PIPESTR,
		       f_lock_names[i].f_name);
		lock &= ~f_lock_names[i].f_lock;
		is_first = false;
	}
	if (lock) {
		PRINTF("%s%#" PRIxN(__SIZEOF_SYSCALL_LONG_T__),
		       is_first ? "" : PIPESTR, lock);
	}
	return result;
err:
	return temp;
}
#endif /* NEED_print_f_lock */





#ifdef NEED_print_flock64
PRIVATE ssize_t CC
print_flock64(pformatprinter printer, void *arg,
              USER CHECKED struct flock64 const *obj) {
	ssize_t result, temp;
	result = DOPRINT("{" SYNSPACE SYNFIELD("l_type"));
	if unlikely(result < 0)
		goto done;
	DO(print_f_lock(printer, arg, (unsigned int)obj->l_type));
	PRINT("," SYNSPACE SYNFIELD("l_whence"));
	DO(print_seek_whence(printer, arg, (unsigned int)obj->l_whence));
	DO(format_printf(printer, arg,
	                 "," SYNSPACE SYNFIELD("l_start") "%" PRIu64
	                 "," SYNSPACE SYNFIELD("l_len") "%" PRIu64
	                 "," SYNSPACE SYNFIELD("l_pid") "%" PRIuN(__SIZEOF_PID_T__)
	                 SYNSPACE "}",
	                 obj->l_start, obj->l_len, obj->l_pid));
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_flock64 */





#ifdef NEED_print_f_owner_ex
PRIVATE ssize_t CC
print_f_owner_ex(pformatprinter printer, void *arg,
                 USER CHECKED struct f_owner_ex const *obj) {
	ssize_t result, temp;
	result = DOPRINT("{" SYNSPACE SYNFIELD("type"));
	if unlikely(result < 0)
		goto done;
	DO(print_f_owner_type(printer, arg, (unsigned int)obj->type));
	DO(format_printf(printer, arg,
	                 "," SYNSPACE SYNFIELD("pid") "%" PRIuN(__SIZEOF_PID_T__)
	                 SYNSPACE "}",
	                 obj->pid));
done:
	return result;
err:
	return temp;
}
#endif /* NEED_print_f_owner_ex */





#ifdef NEED_print_fcntl_arg
PRIVATE ssize_t CC
print_fcntl_arg(pformatprinter printer, void *arg,
                syscall_ulong_t cmd,
                USER UNCHECKED void *fcntl_arg) {
	ssize_t result;
	switch (cmd) {

	case F_DUPFD:
	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GETSIG:
	case F_GETLEASE:
	case F_DUPFD_CLOEXEC:
	case F_GETPIPE_SZ:
	case F_NEXT:
	case F_CLOSEM:
	case F_MAXFD:
		result = (*printer)(arg, "(void)0", 7);
		break;

	case F_SETFL:
	case F_SETFL_XCH:
		result = print_oflag_t(printer, arg,
		                       (oflag_t)(uintptr_t)fcntl_arg,
		                       IO_SETFL_MASK);
		break;

	case F_SETFD:
		result = print_fd_flags(printer, arg,
		                        (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_SETSIG:
		result = print_signo_t(printer, arg,
		                       (signo_t)(uintptr_t)fcntl_arg);
		break;

	case F_GETLK:
	case F_OFD_GETLK:
		result = format_printf(printer, arg, "(struct flock *)%#" PRIxPTR, fcntl_arg);
		break;

	case F_GETLK64:
		result = format_printf(printer, arg,
		                       "(struct flock64 *)%#" PRIxPTR,
		                       fcntl_arg);
		break;

	case F_SETLK:
	case F_SETLKW:
	case F_OFD_SETLK:
	case F_OFD_SETLKW: {
		struct flock64 lck64;
		USER CHECKED struct flock const *ulck;
		validate_readable(fcntl_arg, sizeof(struct flock));
		ulck = (USER CHECKED struct flock const *)fcntl_arg;
		lck64.l_type   = ulck->l_type;
		lck64.l_whence = ulck->l_whence;
		lck64.l_start  = ulck->l_start;
		lck64.l_len    = ulck->l_len;
		lck64.l_pid    = ulck->l_pid;
		result = print_flock64(printer, arg, &lck64);
	}	break;

	case F_SETLK64:
	case F_SETLKW64:
		validate_readable(fcntl_arg, sizeof(struct flock64));
		result = print_flock64(printer, arg, (USER CHECKED struct flock64 const *)fcntl_arg);
		break;

	case F_SETOWN_EX:
		validate_readable(fcntl_arg, sizeof(struct f_owner_ex));
		result = print_f_owner_ex(printer, arg, (USER CHECKED struct f_owner_ex const *)fcntl_arg);
		break;

	case F_SETOWN:
		result = format_printf(printer, arg,
		                       "(pid_t)%" PRIuN(__SIZEOF_PID_T__),
		                       (pid_t)(uintptr_t)fcntl_arg);
		break;

	case F_GETOWN_EX:
		result = format_printf(printer, arg,
		                       "(struct f_owner_ex *)%#" PRIxPTR,
		                       fcntl_arg);
		break;

	case F_SETLEASE:
		result = print_f_lock(printer, arg, (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_NOTIFY:
		result = print_dn_flags(printer, arg, (syscall_ulong_t)(uintptr_t)fcntl_arg);
		break;

	case F_SETPIPE_SZ:
		result = format_printf(printer, arg, "%" PRIuSIZ,
		                       (size_t)(uintptr_t)fcntl_arg);
		break;

	case F_DUP2FD:
	case F_DUP2FD_CLOEXEC:
		result = print_fd_t(printer, arg, (fd_t)(uintptr_t)fcntl_arg);
		break;

	default:
		result = format_printf(printer, arg, "(void *)%#" PRIxPTR, fcntl_arg);
		break;
	}
	return result;
}
#endif /* NEED_print_fcntl_command */









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
	// TODO: #define HAVE_SC_REPR_CLONE_FLAGS_SETNS 1
	// TODO: #define HAVE_SC_REPR_CLONE_FLAGS_UNSHARE 1
	// TODO: #define HAVE_SC_REPR_CPUSET 1
	// TODO: #define HAVE_SC_REPR_EPOLL_OP 1
	// TODO: #define HAVE_SC_REPR_EVENTFD2_FLAGS 1
	// TODO: #define HAVE_SC_REPR_EXCEPTION_HANDLER_MODE 1
	// TODO: #define HAVE_SC_REPR_EXIT_STATUS 1
	// TODO: #define HAVE_SC_REPR_FALLOCATE_MODE 1
	// TODO: #define HAVE_SC_REPR_FSMODE 1
	// TODO: #define HAVE_SC_REPR_FUTEX_OP 1
	// TODO: #define HAVE_SC_REPR_GETRANDOM_FLAGS 1
	// TODO: #define HAVE_SC_REPR_GETRUSAGE_WHO 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR16 1
	// TODO: #define HAVE_SC_REPR_GID_VECTOR32 1
	// TODO: #define HAVE_SC_REPR_IDTYPE_T 1
	// TODO: #define HAVE_SC_REPR_ID_T 1
	// TODO: #define HAVE_SC_REPR_IOPRIO_ID 1
	// TODO: #define HAVE_SC_REPR_IOPRIO_VALUE 1
	// TODO: #define HAVE_SC_REPR_IOPRIO_WHO 1
	// TODO: #define HAVE_SC_REPR_ITIMER_WHICH 1
	// TODO: #define HAVE_SC_REPR_KCMP_TYPE 1
	// TODO: #define HAVE_SC_REPR_KREADDIR_MODE 1
	// TODO: #define HAVE_SC_REPR_KSYSCTL_ARG 1
	// TODO: #define HAVE_SC_REPR_KSYSCTL_COMMAND 1
	// TODO: #define HAVE_SC_REPR_LFUTEX_OP 1
	// TODO: #define HAVE_SC_REPR_LFUTEX_TIMEOUT_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MAPLIBRARY_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MEMFD_CREATE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MLOCKALL_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MMAP_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MMAP_PROT 1
	// TODO: #define HAVE_SC_REPR_MOUNT_FLAGS 1
	// TODO: #define HAVE_SC_REPR_MREMAP_FLAGS 1
	// TODO: #define HAVE_SC_REPR_REBOOT_HOW 1
	// TODO: #define HAVE_SC_REPR_RENAMEAT2_FLAGS 1
	// TODO: #define HAVE_SC_REPR_RLIMIT_RESOURCE 1
	// TODO: #define HAVE_SC_REPR_RPC_SCHEDULE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SCHED_POLICY 1
	// TODO: #define HAVE_SC_REPR_SCHED_PRIORITY_WHICH 1
	// TODO: #define HAVE_SC_REPR_SIGMASK 1
	// TODO: #define HAVE_SC_REPR_SIGNALFD4_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SIGPROCMASK_HOW 1
	// TODO: #define HAVE_SC_REPR_SOCKETCALL_ARGS 1
	// TODO: #define HAVE_SC_REPR_SOCKETCALL_CALL 1
	// TODO: #define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SOCKET_RECVMSG_FLAGS2 1
	// TODO: #define HAVE_SC_REPR_SOCKET_SENDMSG_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SOCKET_SHUTDOWN_HOW 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_LEVEL 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_OPTNAME 1
	// TODO: #define HAVE_SC_REPR_SOCKOPT_OPTVAL 1
	// TODO: #define HAVE_SC_REPR_SPLICE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_DEBUGTRAP_REASON64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR32_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_ELF_PHDR64_VECTOR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_EXCEPTION_DATA64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_FDSET 1
	// TODO: #define HAVE_SC_REPR_STRUCT_FILE_HANDLE 1
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
	// TODO: #define HAVE_SC_REPR_STRUCT_MQ_ATTR 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_MSGHDRX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RLIMIT64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO 1
	// TODO: #define HAVE_SC_REPR_STRUCT_RPC_SYSCALL_INFO32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SCHED_PARAM 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGACTIONX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGACTIONX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGALTSTACKX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGALTSTACKX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGEVENT 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGINFOX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGMASK_SIGSET_AND_LEN 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SIGSET 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SPAWN_ACTIONSX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_SPAWN_ACTIONSX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TERMIOS 1
	// TODO: #define HAVE_SC_REPR_STRUCT_TIMEZONE 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UCPUSTATE64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX32_64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_UTIMBUFX64 1
	// TODO: #define HAVE_SC_REPR_STRUCT_WINSIZE 1
	// TODO: #define HAVE_SC_REPR_SWAPFLAGS 1
	// TODO: #define HAVE_SC_REPR_SYNC_FILE_RANGE_FLAGS 1
	// TODO: #define HAVE_SC_REPR_SYSLOG_LEVEL 1
	// TODO: #define HAVE_SC_REPR_TIME32_T_PTR 1
	// TODO: #define HAVE_SC_REPR_TIME64_T_PTR 1
	// TODO: #define HAVE_SC_REPR_TIMERFD_FLAGS 1
	// TODO: #define HAVE_SC_REPR_TIMERFD_TIMER_FLAGS 1
	// TODO: #define HAVE_SC_REPR_TIMER_FLAGS 1
	// TODO: #define HAVE_SC_REPR_UNWIND_ERROR 1
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR32 1
	// TODO: #define HAVE_SC_REPR_VOID_VECTOR64 1
	// TODO: #define HAVE_SC_REPR_WAITFLAG 1
	// TODO: #define HAVE_SC_REPR_WAITID_OPTIONS 1
	// TODO: #define HAVE_SC_REPR_XATTR_FLAGS 1

#ifdef HAVE_SC_REPR_SEEK_WHENCE
	case SC_REPR_SEEK_WHENCE:
		result = print_seek_whence(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SEEK_WHENCE */

#ifdef HAVE_SC_REPR_STRUCT_SOCKADDR
	case SC_REPR_STRUCT_SOCKADDR: {
		USER UNCHECKED struct sockaddr *sa;
		socklen_t len;
		if (!link)
			goto do_pointer;
		sa  = (USER UNCHECKED struct sockaddr *)(uintptr_t)value.sv_u64;
		len = (socklen_t)link->sa_value.sv_u64;
		validate_readable(sa, len);
		result = print_sockaddr(printer, arg, sa, len);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_SOCKADDR */

#ifdef HAVE_SC_REPR_IOCTL_COMMAND
	case SC_REPR_IOCTL_COMMAND:
		result = print_ioctl_command(printer, arg,
		                             (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_IOCTL_COMMAND */

	// TODO: #define HAVE_SC_REPR_IOCTL_ARG 1

#if defined(HAVE_SC_REPR_FCNTL64_COMMAND) || defined(HAVE_SC_REPR_FCNTL_COMMAND)
#ifdef HAVE_SC_REPR_FCNTL64_COMMAND
	case SC_REPR_FCNTL64_COMMAND:
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND */
#ifdef HAVE_SC_REPR_FCNTL_COMMAND
	case SC_REPR_FCNTL_COMMAND:
#endif /* HAVE_SC_REPR_FCNTL_COMMAND */
		result = print_fcntl_command(printer, arg,
		                             (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FCNTL64_COMMAND || HAVE_SC_REPR_FCNTL_COMMAND */

#if defined(HAVE_SC_REPR_FCNTL64_ARG) || defined(HAVE_SC_REPR_FCNTL_ARG)
#ifdef HAVE_SC_REPR_FCNTL64_ARG
	case SC_REPR_FCNTL64_ARG:
#endif /* HAVE_SC_REPR_FCNTL64_ARG */
#ifdef HAVE_SC_REPR_FCNTL_ARG
	case SC_REPR_FCNTL_ARG:
#endif /* HAVE_SC_REPR_FCNTL_ARG */
		if unlikely(!link)
			goto do_pointer;
		result = print_fcntl_arg(printer, arg,
		                         (syscall_ulong_t)link->sa_value.sv_u64,
		                         (void *)(uintptr_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_FCNTL64_ARG || HAVE_SC_REPR_FCNTL_ARG */

	// TODO: #define HAVE_SC_REPR_HOP_COMMAND 1
	// TODO: #define HAVE_SC_REPR_HOP_ARG 1

#ifdef HAVE_SC_REPR_SIGNO_T
	case SC_REPR_SIGNO_T:
		result = print_signo_t(printer, arg, (signo_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SIGNO_T */

#ifdef HAVE_SC_REPR_SOCKET_DOMAIN
	case SC_REPR_SOCKET_DOMAIN:
		result = print_socket_domain(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_DOMAIN */

#ifdef HAVE_SC_REPR_SOCKET_PROTOCOL
	case SC_REPR_SOCKET_PROTOCOL:
		result = print_socket_proto(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_PROTOCOL */

#ifdef HAVE_SC_REPR_SOCKET_TYPE
	case SC_REPR_SOCKET_TYPE:
		result = print_socket_type(printer, arg, (syscall_ulong_t)value.sv_u64);
		break;
#endif /* HAVE_SC_REPR_SOCKET_TYPE */

#ifdef HAVE_SC_REPR_STRING_VECTOR
	case SC_REPR_STRING_VECTOR:
		result = print_string_vector(printer, arg,
		                             (USER UNCHECKED char const *USER UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             sizeof(void *)
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR */

#ifdef HAVE_SC_REPR_STRING_VECTOR32
	case SC_REPR_STRING_VECTOR32:
		result = print_string_vector(printer, arg,
		                             (USER UNCHECKED char const *USER UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             4
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR32 */

#ifdef HAVE_SC_REPR_STRING_VECTOR64
	case SC_REPR_STRING_VECTOR64:
		result = print_string_vector(printer, arg,
		                             (USER UNCHECKED char const *USER UNCHECKED const *)(uintptr_t)value.sv_u64
#ifdef HAVE_STRING_VECTOR_POINTER_SIZE
		                             ,
		                             8
#endif /* HAVE_STRING_VECTOR_POINTER_SIZE */
		                             );
		break;
#endif /* HAVE_SC_REPR_STRING_VECTOR64 */


#define DO_REPR_STRUCT_TIMEVAL_VEC2(struct_timeval_typecode)                      \
	do {                                                                          \
		struct timeval tsv[2];                                                    \
		USER UNCHECKED struct_timeval_typecode *utms;                             \
		utms = (USER UNCHECKED struct_timeval_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                        \
			goto do_null_pointer;                                                 \
		validate_readable(utms, 2 * sizeof(struct_timeval_typecode));             \
		COMPILER_READ_BARRIER();                                                  \
		tsv[0].tv_sec  = (time_t)utms[0].tv_sec;                                  \
		tsv[0].tv_usec = (syscall_ulong_t)utms[0].tv_usec;                        \
		tsv[1].tv_sec  = (time_t)utms[1].tv_sec;                                  \
		tsv[1].tv_usec = (syscall_ulong_t)utms[1].tv_usec;                        \
		COMPILER_READ_BARRIER();                                                  \
		result = print_timeval_vector(printer, arg, tsv, 2);                      \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2
	case SC_REPR_STRUCT_TIMEVAL_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2
	case SC_REPR_STRUCT_TIMEVAL32_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2
	case SC_REPR_STRUCT_TIMEVAL64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timeval64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2
	case SC_REPR_STRUCT_TIMEVALX32_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2
	case SC_REPR_STRUCT_TIMEVALX32_64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64_VEC2 */

#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2
	case SC_REPR_STRUCT_TIMEVALX64_VEC2:
		DO_REPR_STRUCT_TIMEVAL_VEC2(struct timevalx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64_VEC2 */
#undef DO_REPR_STRUCT_TIMEVAL_VEC2


#define DO_REPR_STRUCT_TIMEVAL(struct_timeval_typecode)                           \
	do {                                                                          \
		struct timeval ts;                                                        \
		USER UNCHECKED struct_timeval_typecode *utms;                             \
		utms = (USER UNCHECKED struct_timeval_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                        \
			goto do_null_pointer;                                                 \
		validate_readable(utms, sizeof(struct_timeval_typecode));                 \
		COMPILER_READ_BARRIER();                                                  \
		ts.tv_sec  = (time_t)utms->tv_sec;                                        \
		ts.tv_usec = (syscall_ulong_t)utms->tv_usec;                              \
		COMPILER_READ_BARRIER();                                                  \
		result = print_timeval(printer, arg, &ts);                                \
	}	__WHILE0

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL) || defined(NEED_do_struct_timeval)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL
	case SC_REPR_STRUCT_TIMEVAL:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL */
#ifdef NEED_do_struct_timeval
do_struct_timeval:
#endif /* NEED_do_struct_timeval */
		DO_REPR_STRUCT_TIMEVAL(struct timeval);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL || NEED_do_struct_timeval */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL32) || defined(NEED_do_struct_timeval32)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL32
	case SC_REPR_STRUCT_TIMEVAL32:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 */
#ifdef NEED_do_struct_timeval32
do_struct_timeval32:
#endif /* NEED_do_struct_timeval32 */
		DO_REPR_STRUCT_TIMEVAL(struct timeval32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL32 || NEED_do_struct_timeval32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVAL64) || defined(NEED_do_struct_timeval64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVAL64
	case SC_REPR_STRUCT_TIMEVAL64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 */
#ifdef NEED_do_struct_timeval64
do_struct_timeval64:
#endif /* NEED_do_struct_timeval64 */
		DO_REPR_STRUCT_TIMEVAL(struct timeval64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVAL64 || NEED_do_struct_timeval64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX32) || defined(NEED_do_struct_timevalx32)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32
	case SC_REPR_STRUCT_TIMEVALX32:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 */
#ifdef NEED_do_struct_timevalx32
do_struct_timevalx32:
#endif /* NEED_do_struct_timevalx32 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32 || NEED_do_struct_timevalx32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX32_64) || defined(NEED_do_struct_timevalx32_64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX32_64
	case SC_REPR_STRUCT_TIMEVALX32_64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 */
#ifdef NEED_do_struct_timevalx32_64
do_struct_timevalx32_64:
#endif /* NEED_do_struct_timevalx32_64 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX32_64 || NEED_do_struct_timevalx32_64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMEVALX64) || defined(NEED_do_struct_timevalx64)
#ifdef HAVE_SC_REPR_STRUCT_TIMEVALX64
	case SC_REPR_STRUCT_TIMEVALX64:
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 */
#ifdef NEED_do_struct_timevalx64
do_struct_timevalx64:
#endif /* NEED_do_struct_timevalx64 */
		DO_REPR_STRUCT_TIMEVAL(struct timevalx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMEVALX64 || NEED_do_struct_timevalx64 */
#undef DO_REPR_STRUCT_TIMEVAL



#define DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct_timespec_typecode)                \
	do {                                                                           \
		size_t count = 2;                                                          \
		struct timespec tsv[3];                                                    \
		USER UNCHECKED struct_timespec_typecode *utms;                             \
		utms = (USER UNCHECKED struct_timespec_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                         \
			goto do_null_pointer;                                                  \
		if (link && ((syscall_ulong_t)link->sa_value.sv_u64 & AT_CHANGE_CTIME))    \
			count = 3;                                                             \
		validate_readablem(utms, count, sizeof(struct_timespec_typecode));         \
		COMPILER_READ_BARRIER();                                                   \
		tsv[0].tv_sec  = (time_t)utms[0].tv_sec;                                   \
		tsv[0].tv_nsec = (syscall_ulong_t)utms[0].tv_nsec;                         \
		tsv[1].tv_sec  = (time_t)utms[1].tv_sec;                                   \
		tsv[1].tv_nsec = (syscall_ulong_t)utms[1].tv_nsec;                         \
		if (count >= 3) {                                                          \
			tsv[2].tv_sec  = (time_t)utms[2].tv_sec;                               \
			tsv[2].tv_nsec = (syscall_ulong_t)utms[2].tv_nsec;                     \
		}                                                                          \
		COMPILER_READ_BARRIER();                                                   \
		result = print_timespec_vector(printer, arg, tsv, count);                  \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespec64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3
	case SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3:
		DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3(struct timespecx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_VEC2_OR_3 */
#undef DO_REPR_STRUCT_TIMESPEC_VEC2_OR_3



#define DO_REPR_STRUCT_TIMESPEC_OR_UINT32()                                            \
	do {                                                                               \
		if (!link || LINUX_FUTEX_USES_TIMEOUT((syscall_ulong_t)link->sa_value.sv_u64)) \
			goto do_uint32_t;                                                          \
	}	__WHILE0
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32
	case SC_REPR_STRUCT_TIMESPEC32_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespec32;
#define NEED_do_struct_timespec32
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPEC64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespec64;
#define NEED_do_struct_timespec64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX32_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx32;
#define NEED_do_struct_timespecx32
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx32_64;
#define NEED_do_struct_timespecx32_64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32 */

#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32
	case SC_REPR_STRUCT_TIMESPECX64_OR_UINT32:
		DO_REPR_STRUCT_TIMESPEC_OR_UINT32();
		goto do_struct_timespecx64;
#define NEED_do_struct_timespecx64
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64_OR_UINT32 */
#undef DO_REPR_STRUCT_TIMESPEC_OR_UINT32



#define DO_REPR_STRUCT_TIMESPEC(struct_timespec_typecode)                          \
	do {                                                                           \
		struct timespec ts;                                                        \
		USER UNCHECKED struct_timespec_typecode *utms;                             \
		utms = (USER UNCHECKED struct_timespec_typecode *)(uintptr_t)value.sv_u64; \
		if unlikely(!utms)                                                         \
			goto do_null_pointer;                                                  \
		validate_readable(utms, sizeof(struct_timespec_typecode));                 \
		COMPILER_READ_BARRIER();                                                   \
		ts.tv_sec  = (time_t)utms->tv_sec;                                         \
		ts.tv_nsec = (syscall_ulong_t)utms->tv_nsec;                               \
		COMPILER_READ_BARRIER();                                                   \
		result = print_timespec(printer, arg, &ts);                                \
	}	__WHILE0

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC) || defined(NEED_do_struct_timespec)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC
	case SC_REPR_STRUCT_TIMESPEC:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC */
#ifdef NEED_do_struct_timespec
do_struct_timespec:
#endif /* NEED_do_struct_timespec */
		DO_REPR_STRUCT_TIMESPEC(struct timespec);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC || NEED_do_struct_timespec */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC32) || defined(NEED_do_struct_timespec32)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC32
	case SC_REPR_STRUCT_TIMESPEC32:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 */
#ifdef NEED_do_struct_timespec32
do_struct_timespec32:
#endif /* NEED_do_struct_timespec32 */
		DO_REPR_STRUCT_TIMESPEC(struct timespec32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC32 || NEED_do_struct_timespec32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPEC64) || defined(NEED_do_struct_timespec64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPEC64
	case SC_REPR_STRUCT_TIMESPEC64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 */
#ifdef NEED_do_struct_timespec64
do_struct_timespec64:
#endif /* NEED_do_struct_timespec64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespec64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPEC64 || NEED_do_struct_timespec64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX32) || defined(NEED_do_struct_timespecx32)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32
	case SC_REPR_STRUCT_TIMESPECX32:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 */
#ifdef NEED_do_struct_timespecx32
do_struct_timespecx32:
#endif /* NEED_do_struct_timespecx32 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx32);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32 || NEED_do_struct_timespecx32 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX32_64) || defined(NEED_do_struct_timespecx32_64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX32_64
	case SC_REPR_STRUCT_TIMESPECX32_64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 */
#ifdef NEED_do_struct_timespecx32_64
do_struct_timespecx32_64:
#endif /* NEED_do_struct_timespecx32_64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx32_64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX32_64 || NEED_do_struct_timespecx32_64 */

#if defined(HAVE_SC_REPR_STRUCT_TIMESPECX64) || defined(NEED_do_struct_timespecx64)
#ifdef HAVE_SC_REPR_STRUCT_TIMESPECX64
	case SC_REPR_STRUCT_TIMESPECX64:
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 */
#ifdef NEED_do_struct_timespecx64
do_struct_timespecx64:
#endif /* NEED_do_struct_timespecx64 */
		DO_REPR_STRUCT_TIMESPEC(struct timespecx64);
		break;
#endif /* HAVE_SC_REPR_STRUCT_TIMESPECX64 || NEED_do_struct_timespecx64 */
#undef DO_REPR_STRUCT_TIMESPEC



#ifdef HAVE_SC_REPR_STRUCT_POLLFD
	case SC_REPR_STRUCT_POLLFD: {
		USER UNCHECKED struct pollfd *fds;
		size_t count = 1;
		if (link)
			count = (size_t)link->sa_value.sv_u64;
		fds = (USER UNCHECKED struct pollfd *)(uintptr_t)value.sv_u64;
		if unlikely(!fds)
			goto do_null_pointer;
		validate_readablem(fds, count, sizeof(struct pollfd));
		result = print_pollfds(printer, arg, fds, count);
	}	break;
#endif /* HAVE_SC_REPR_STRUCT_POLLFD */

#ifdef HAVE_SC_REPR_SIGHANDLER_T
	case SC_REPR_SIGHANDLER_T: {
		sighandler_t hand;
		*(void **)&hand = (void *)(uintptr_t)value.sv_u64;
		result = print_sighandler_t(printer, arg, hand);
	}	break;
#endif /* HAVE_SC_REPR_SIGHANDLER_T */

#ifdef HAVE_SC_REPR_EXCEPT_HANDLER_T
	case SC_REPR_EXCEPT_HANDLER_T:
		goto do_pointer;
#endif /* HAVE_SC_REPR_EXCEPT_HANDLER_T */

#ifdef HAVE_SC_REPR_FILENAME
	case SC_REPR_FILENAME:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64, NULL);
		break;
#endif /* HAVE_SC_REPR_FILENAME */

#ifdef HAVE_SC_REPR_BUFFER
	case SC_REPR_BUFFER:
		if unlikely(!link)
			goto do_pointer;
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64, link);
		break;
#endif /* HAVE_SC_REPR_BUFFER */

#ifdef HAVE_SC_REPR_STRING
	case SC_REPR_STRING:
		result = print_string(printer, arg, (char const *)(uintptr_t)value.sv_u64, link);
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
		/* Handle the special case of the 3rd argument
		 * to sys_open(), where the mode value is ignored */
		if (link &&
		    (link->sa_value.sv_u64 & O_CREAT) != O_CREAT &&
		    (link->sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
			value.sv_u64 = 0;
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

#ifdef HAVE_SC_REPR_TIMER_T
	case SC_REPR_TIMER_T:
		goto do_uintptr_t;
#define NEED_do_uintptr_t
#endif /* HAVE_SC_REPR_TIMER_T */

	case SC_REPR_POINTER:
do_pointer: ATTR_UNUSED;
		if (value.sv_u64 == 0) {
do_null_pointer: ATTR_UNUSED;
			result = (*printer)(arg, NULLSTR, COMPILER_STRLEN(NULLSTR));
			break;
		}
		goto do_uintptr_t;
#define NEED_do_uintptr_t

#if defined(HAVE_SC_REPR_INTPTR_T) || defined(NEED_do_intptr_t)
#ifdef HAVE_SC_REPR_INTPTR_T
	case SC_REPR_INTPTR_T:
#endif /* HAVE_SC_REPR_INTPTR_T */
#ifdef NEED_do_intptr_t
do_intptr_t:
#endif /* NEED_do_intptr_t */
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
#endif /* HAVE_SC_REPR_INTPTR_T || NEED_do_intptr_t */

#if defined(HAVE_SC_REPR_UINTPTR_T) || defined(NEED_do_uintptr_t)
#ifdef HAVE_SC_REPR_UINTPTR_T
	case SC_REPR_UINTPTR_T:
#endif /* HAVE_SC_REPR_UINTPTR_T */
#ifdef NEED_do_uintptr_t
do_uintptr_t:
#endif /* NEED_do_uintptr_t */
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
#elif !defined(__DEEMON__)
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* ... */
#endif /* HAVE_SC_REPR_UINTPTR_T || NEED_do_uintptr_t */

#if defined(HAVE_SC_REPR_SYSCALL_SLONG_T) || defined(NEED_do_syscall_slong_t)
#ifdef HAVE_SC_REPR_SYSCALL_SLONG_T
	case SC_REPR_SYSCALL_SLONG_T:
#endif /* HAVE_SC_REPR_SYSCALL_SLONG_T */
#ifdef NEED_do_syscall_slong_t
do_syscall_slong_t:
#endif /* NEED_do_syscall_slong_t */
		format = "%" PRIdPTR;
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
		format = "%" PRIuPTR;
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
#if 1
		result = format_printf(printer, arg, "%p",
		                       (uintptr_t)value.sv_u64);
#else
		result = DOPRINT("?");
#endif
		break;
	}
done: ATTR_UNUSED;
	return result;
}

DEFINE_PUBLIC_ALIAS(sc_printvalue, libsc_printvalue);

DECL_END

#endif /* !GUARD_LIBSCTRACE_SC_REPR_PRINTVALUE_C */
