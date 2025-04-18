/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!included_by <confname.h>*/
/*!included_by <unistd.h>*/
#ifndef _ASM_CRT_CONFNAME_H
#define _ASM_CRT_CONFNAME_H 1

#include <__stdinc.h>

/* Arguments accepted by `[f]pathconf()'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	_PC_LINK_MAX,           /* [perfs] Max # of links a file may have */
	_PC_MAX_CANON,          /* [pertty] size of the canonical input queue (s.a. `struct mkttydev::t_term.t_canon.lb_limt') */
	_PC_MAX_INPUT,          /* [pertty] size of the type-ahead buffer (s.a. `struct mkttydev::t_term.t_ibuf.rb_limit') */
	_PC_NAME_MAX,           /* [perfs] Max # of chars in a file name */
	_PC_PATH_MAX,           /* [const] Max # of chars in a path name including nul (Unlimited in KOS) */
	_PC_PIPE_BUF,           /* [const] Max # of bytes in atomic write to a pipe */
	_PC_CHOWN_RESTRICTED,   /* [const] Is file access restricted by file ownership. */
	_PC_NO_TRUNC,           /* [const] Filenames are not silently truncated. */
	_PC_VDISABLE,           /* [const] `c_cc' member of `struct termios' structure can be disabled by using the value _POSIX_VDISABLE. */
	_PC_SYNC_IO,            /* [const][== _POSIX_SYNC_IO | -1] */
	_PC_ASYNC_IO,           /* [const][== _POSIX_ASYNC_IO | -1] */
	_PC_PRIO_IO,            /* [const][== _POSIX_PRIO_IO | -1] */
	_PC_SOCK_MAXBUF,        /* [const][== SOCK_MAXBUF | -1] */
	_PC_FILESIZEBITS,       /* [perfs] Max # of bits in a file's size field */
	_PC_REC_INCR_XFER_SIZE, /* [perfs] Buffer size increments for efficient disk transfer operations */
	_PC_REC_MAX_XFER_SIZE,  /* [perfs] Max buffer size for efficient disk transfer operations */
	_PC_REC_MIN_XFER_SIZE,  /* [perfs] Min buffer size for efficient disk transfer operations */
	_PC_REC_XFER_ALIGN,     /* [perfs] Required in-member buffer alignment for efficient disk transfer operations */
	_PC_ALLOC_SIZE_MIN,     /* Same as `_PC_REC_XFER_ALIGN' */
	_PC_SYMLINK_MAX,        /* [perfs] Max length of text contained within symbolic links */
	_PC_2_SYMLINKS          /* [perfs] Are symbolic links supported by the filesystem */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define _PC_LINK_MAX           _PC_LINK_MAX           /* [perfs] Max # of links a file may have */
#define _PC_MAX_CANON          _PC_MAX_CANON          /* [pertty] size of the canonical input queue (s.a. `struct mkttydev::t_term.t_canon.lb_limt') */
#define _PC_MAX_INPUT          _PC_MAX_INPUT          /* [pertty] size of the type-ahead buffer (s.a. `struct mkttydev::t_term.t_ibuf.rb_limit') */
#define _PC_NAME_MAX           _PC_NAME_MAX           /* [perfs] Max # of chars in a file name */
#define _PC_PATH_MAX           _PC_PATH_MAX           /* [const] Max # of chars in a path name including nul (Unlimited in KOS) */
#define _PC_PIPE_BUF           _PC_PIPE_BUF           /* [const] Max # of bytes in atomic write to a pipe */
#define _PC_CHOWN_RESTRICTED   _PC_CHOWN_RESTRICTED   /* [const] Is file access restricted by file ownership. */
#define _PC_NO_TRUNC           _PC_NO_TRUNC           /* [const] Filenames are not silently truncated. */
#define _PC_VDISABLE           _PC_VDISABLE           /* [const] `c_cc' member of `struct termios' structure can be disabled by using the value _POSIX_VDISABLE. */
#define _PC_SYNC_IO            _PC_SYNC_IO            /* [const][== _POSIX_SYNC_IO | -1] */
#define _PC_ASYNC_IO           _PC_ASYNC_IO           /* [const][== _POSIX_ASYNC_IO | -1] */
#define _PC_PRIO_IO            _PC_PRIO_IO            /* [const][== _POSIX_PRIO_IO | -1] */
#define _PC_SOCK_MAXBUF        _PC_SOCK_MAXBUF        /* [const][== SOCK_MAXBUF | -1] */
#define _PC_FILESIZEBITS       _PC_FILESIZEBITS       /* [perfs] Max # of bits in a file's size field */
#define _PC_REC_INCR_XFER_SIZE _PC_REC_INCR_XFER_SIZE /* [perfs] Buffer size increments for efficient disk transfer operations */
#define _PC_REC_MAX_XFER_SIZE  _PC_REC_MAX_XFER_SIZE  /* [perfs] Max buffer size for efficient disk transfer operations */
#define _PC_REC_MIN_XFER_SIZE  _PC_REC_MIN_XFER_SIZE  /* [perfs] Min buffer size for efficient disk transfer operations */
#define _PC_REC_XFER_ALIGN     _PC_REC_XFER_ALIGN     /* [perfs] Required in-member buffer alignment for efficient disk transfer operations */
#define _PC_ALLOC_SIZE_MIN     _PC_ALLOC_SIZE_MIN     /* Same as `_PC_REC_XFER_ALIGN' */
#define _PC_SYMLINK_MAX        _PC_SYMLINK_MAX        /* [perfs] Max length of text contained within symbolic links */
#define _PC_2_SYMLINKS         _PC_2_SYMLINKS         /* [perfs] Are symbolic links supported by the filesystem */
#else /* __COMPILER_PREFERR_ENUMS */
#define _PC_LINK_MAX           0  /* [perfs] Max # of links a file may have */
#define _PC_MAX_CANON          1  /* [pertty] size of the canonical input queue (s.a. `struct mkttydev::t_term.t_canon.lb_limt') */
#define _PC_MAX_INPUT          2  /* [pertty] size of the type-ahead buffer (s.a. `struct mkttydev::t_term.t_ibuf.rb_limit') */
#define _PC_NAME_MAX           3  /* [perfs] Max # of chars in a file name */
#define _PC_PATH_MAX           4  /* [const] Max # of chars in a path name including nul (Unlimited in KOS) */
#define _PC_PIPE_BUF           5  /* [const] Max # of bytes in atomic write to a pipe */
#define _PC_CHOWN_RESTRICTED   6  /* [const] Is file access restricted by file ownership. */
#define _PC_NO_TRUNC           7  /* [const] Filenames are not silently truncated. */
#define _PC_VDISABLE           8  /* [const] `c_cc' member of `struct termios' structure can be disabled by using the value _POSIX_VDISABLE. */
#define _PC_SYNC_IO            9  /* [const][== _POSIX_SYNC_IO | -1] */
#define _PC_ASYNC_IO           10 /* [const][== _POSIX_ASYNC_IO | -1] */
#define _PC_PRIO_IO            11 /* [const][== _POSIX_PRIO_IO | -1] */
#define _PC_SOCK_MAXBUF        12 /* [const][== SOCK_MAXBUF | -1] */
#define _PC_FILESIZEBITS       13 /* [perfs] Max # of bits in a file's size field */
#define _PC_REC_INCR_XFER_SIZE 14 /* [perfs] Buffer size increments for efficient disk transfer operations */
#define _PC_REC_MAX_XFER_SIZE  15 /* [perfs] Max buffer size for efficient disk transfer operations */
#define _PC_REC_MIN_XFER_SIZE  16 /* [perfs] Min buffer size for efficient disk transfer operations */
#define _PC_REC_XFER_ALIGN     17 /* [perfs] Required in-member buffer alignment for efficient disk transfer operations */
#define _PC_ALLOC_SIZE_MIN     18 /* Same as `_PC_REC_XFER_ALIGN' */
#define _PC_SYMLINK_MAX        19 /* [perfs] Max length of text contained within symbolic links */
#define _PC_2_SYMLINKS         20 /* [perfs] Are symbolic links supported by the filesystem */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Arguments accepted by `sysconf()'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	_SC_ARG_MAX,                            /* [== unlimited, ARG_MAX] */
	_SC_CHILD_MAX,                          /* [== unlimited, CHILD_MAX] */
	_SC_CLK_TCK,                            /* [== custom, CLK_TCK] */
	_SC_NGROUPS_MAX,                        /* [== unlimited, NGROUPS_MAX] */
	_SC_OPEN_MAX,                           /* [== unlimited, OPEN_MAX] */
	_SC_STREAM_MAX,                         /* [== unlimited, STREAM_MAX, FOPEN_MAX] */
	_SC_TZNAME_MAX,                         /* [== unlimited, _POSIX_TZNAME_MAX] */
	_SC_JOB_CONTROL,                        /* [== _POSIX_JOB_CONTROL] */
	_SC_SAVED_IDS,                          /* [== _POSIX_SAVED_IDS] */
	_SC_REALTIME_SIGNALS,                   /* [== _POSIX_REALTIME_SIGNALS] */
	_SC_PRIORITY_SCHEDULING,                /* [== _POSIX_PRIORITY_SCHEDULING] */
	_SC_TIMERS,                             /* [== _POSIX_TIMERS] */
	_SC_ASYNCHRONOUS_IO,                    /* [== _POSIX_ASYNCHRONOUS_IO] */
	_SC_PRIORITIZED_IO,                     /* [== _POSIX_PRIORITIZED_IO] */
	_SC_SYNCHRONIZED_IO,                    /* [== _POSIX_SYNCHRONIZED_IO] */
	_SC_FSYNC,                              /* [== _POSIX_FSYNC] */
	_SC_MAPPED_FILES,                       /* [== _POSIX_MAPPED_FILES] */
	_SC_MEMLOCK,                            /* [== _POSIX_MEMLOCK] */
	_SC_MEMLOCK_RANGE,                      /* [== _POSIX_MEMLOCK_RANGE] */
	_SC_MEMORY_PROTECTION,                  /* [== _POSIX_MEMORY_PROTECTION] */
	_SC_MESSAGE_PASSING,                    /* [== _POSIX_MESSAGE_PASSING] */
	_SC_SEMAPHORES,                         /* [== _POSIX_SEMAPHORES] */
	_SC_SHARED_MEMORY_OBJECTS,              /* [== _POSIX_SHARED_MEMORY_OBJECTS] */
	_SC_AIO_LISTIO_MAX,                     /* [== _POSIX_AIO_LISTIO_MAX] */
	_SC_AIO_MAX,                            /* [== _POSIX_AIO_MAX] */
	_SC_AIO_PRIO_DELTA_MAX,                 /* [== AIO_PRIO_DELTA_MAX] */
	_SC_DELAYTIMER_MAX,                     /* [== DELAYTIMER_MAX, _POSIX_DELAYTIMER_MAX] */
	_SC_MQ_OPEN_MAX,                        /* [== _POSIX_MQ_OPEN_MAX] */
	_SC_MQ_PRIO_MAX,                        /* [== MQ_PRIO_MAX, _POSIX_MQ_PRIO_MAX] */
	_SC_VERSION,                            /* [== _POSIX_VERSION] */
	_SC_PAGESIZE,                           /* [== __ARCH_PAGESIZE] */
	_SC_PAGE_SIZE = _SC_PAGESIZE,           /* ... */
	_SC_RTSIG_MAX,                          /* [== RTSIG_MAX, _POSIX_RTSIG_MAX] */
	_SC_SEM_NSEMS_MAX,                      /* [== _POSIX_SEM_NSEMS_MAX] */
	_SC_SEM_VALUE_MAX,                      /* [== SEM_VALUE_MAX, _POSIX_SEM_VALUE_MAX] */
	_SC_SIGQUEUE_MAX,                       /* [== _POSIX_SIGQUEUE_MAX] */
	_SC_TIMER_MAX,                          /* [== _POSIX_TIMER_MAX] */
	_SC_BC_BASE_MAX,                        /* [== BC_BASE_MAX, _POSIX2_BC_BASE_MAX] */
	_SC_BC_DIM_MAX,                         /* [== BC_DIM_MAX, _POSIX2_BC_DIM_MAX] */
	_SC_BC_SCALE_MAX,                       /* [== BC_SCALE_MAX, _POSIX2_BC_SCALE_MAX] */
	_SC_BC_STRING_MAX,                      /* [== BC_STRING_MAX, _POSIX2_BC_STRING_MAX] */
	_SC_COLL_WEIGHTS_MAX,                   /* [== COLL_WEIGHTS_MAX, _POSIX2_COLL_WEIGHTS_MAX] */
	_SC_EQUIV_CLASS_MAX,                    /* ... */
	_SC_EXPR_NEST_MAX,                      /* [== EXPR_NEST_MAX, _POSIX2_EXPR_NEST_MAX] */
	_SC_LINE_MAX,                           /* [== LINE_MAX, _POSIX2_LINE_MAX] */
	_SC_RE_DUP_MAX,                         /* [== RE_DUP_MAX, _POSIX_RE_DUP_MAX] */
	_SC_CHARCLASS_NAME_MAX,                 /* [== CHARCLASS_NAME_MAX, _POSIX2_CHARCLASS_NAME_MAX] */
	_SC_2_VERSION,                          /* [== _POSIX2_VERSION] */
	_SC_2_C_BIND,                           /* [== _POSIX2_C_BIND, unlimited] */
	_SC_2_C_DEV,                            /* [== _SC_2_C_DEV, unlimited] */
	_SC_2_FORT_DEV,                         /* [== _POSIX2_FORT_DEV, unlimited] */
	_SC_2_FORT_RUN,                         /* [== _POSIX2_FORT_RUN, unlimited] */
	_SC_2_SW_DEV,                           /* [== _POSIX2_SW_DEV, unlimited] */
	_SC_2_LOCALEDEF,                        /* [== _POSIX2_LOCALEDEF, unlimited] */
	_SC_PII,                                /* [== defined(_POSIX_PII)] */
	_SC_PII_XTI,                            /* [== defined(_POSIX_PII_XTI)] */
	_SC_PII_SOCKET,                         /* [== defined(_POSIX_PII_SOCKET)] */
	_SC_PII_INTERNET,                       /* [== defined(_POSIX_PII_INTERNET)] */
	_SC_PII_OSI,                            /* [== defined(_POSIX_PII_OSI)] */
	_SC_POLL,                               /* [== defined(_POSIX_POLL)] */
	_SC_SELECT,                             /* [== defined(_POSIX_SELECT)] */
	_SC_UIO_MAXIOV,                         /* [== unlimited, UIO_MAXIOV] */
	_SC_IOV_MAX = _SC_UIO_MAXIOV,           /* ... */
	_SC_PII_INTERNET_STREAM,                /* [== defined(_POSIX_PII_INTERNET_STREAM)] */
	_SC_PII_INTERNET_DGRAM,                 /* [== defined(_POSIX_PII_INTERNET_DGRAM)] */
	_SC_PII_OSI_COTS,                       /* [== defined(_POSIX_PII_OSI_COTS)] */
	_SC_PII_OSI_CLTS,                       /* [== defined(_POSIX_PII_OSI_CLTS)] */
	_SC_PII_OSI_M,                          /* [== defined(_POSIX_PII_OSI_M)] */
	_SC_T_IOV_MAX,                          /* [== unlimited, IOV_MAX] */
	_SC_THREADS,                            /* [== _POSIX_THREADS] */
	_SC_THREAD_SAFE_FUNCTIONS,              /* [== _POSIX_THREAD_SAFE_FUNCTIONS] */
	_SC_GETGR_R_SIZE_MAX,                   /* [== NSS_BUFLEN_GROUP] */
	_SC_GETPW_R_SIZE_MAX,                   /* [== NSS_BUFLEN_PASSWD] */
	_SC_LOGIN_NAME_MAX,                     /* [== LOGIN_NAME_MAX] */
	_SC_TTY_NAME_MAX,                       /* [== TTY_NAME_MAX] */
	_SC_THREAD_DESTRUCTOR_ITERATIONS,       /* [== _POSIX_THREAD_DESTRUCTOR_ITERATIONS] */
	_SC_THREAD_KEYS_MAX,                    /* [== _POSIX_THREAD_KEYS_MAX] */
	_SC_THREAD_STACK_MIN,                   /* [== PTHREAD_STACK_MIN] */
	_SC_THREAD_THREADS_MAX,                 /* [== unlimited, _POSIX_THREAD_THREADS_MAX] */
	_SC_THREAD_ATTR_STACKADDR,              /* [== _POSIX_THREAD_ATTR_STACKADDR] */
	_SC_THREAD_ATTR_STACKSIZE,              /* [== _POSIX_THREAD_ATTR_STACKSIZE] */
	_SC_THREAD_PRIORITY_SCHEDULING,         /* [== _POSIX_THREAD_PRIORITY_SCHEDULING] */
	_SC_THREAD_PRIO_INHERIT,                /* [== _POSIX_THREAD_PRIO_INHERIT] */
	_SC_THREAD_PRIO_PROTECT,                /* [== _POSIX_THREAD_PRIO_PROTECT] */
	_SC_THREAD_PROCESS_SHARED,              /* [== _POSIX_THREAD_PROCESS_SHARED] */
	_SC_NPROCESSORS_CONF,                   /* [== custom] */
	_SC_NPROCESSORS_ONLN,                   /* [== custom] */
	_SC_NPROC_ONLN = _SC_NPROCESSORS_ONLN,  /* ... */
	_SC_PHYS_PAGES,                         /* [== custom] */
	_SC_AVPHYS_PAGES,                       /* [== custom] */
	_SC_ATEXIT_MAX,                         /* [== unlimited] */
	_SC_PASS_MAX,                           /* [== BUFSIZ] */
	_SC_XOPEN_VERSION,                      /* [== _XOPEN_VERSION] */
	_SC_XOPEN_XCU_VERSION,                  /* [== _XOPEN_XCU_VERSION] */
	_SC_XOPEN_UNIX,                         /* [== _XOPEN_UNIX] */
	_SC_XOPEN_CRYPT,                        /* [== _XOPEN_CRYPT] */
	_SC_XOPEN_ENH_I18N,                     /* [== _XOPEN_ENH_I18N] */
	_SC_XOPEN_SHM,                          /* [== _XOPEN_SHM] */
	_SC_2_CHAR_TERM,                        /* [== _POSIX2_CHAR_TERM] */
	_SC_2_C_VERSION,                        /* [== _POSIX2_C_VERSION] */
	_SC_2_UPE,                              /* [== _POSIX2_UPE, unlimited] */
	_SC_XOPEN_XPG2,                         /* [== _XOPEN_XPG2] */
	_SC_XOPEN_XPG3,                         /* [== _XOPEN_XPG3] */
	_SC_XOPEN_XPG4,                         /* [== _XOPEN_XPG4] */
	_SC_CHAR_BIT,                           /* [== CHAR_BIT] */
	_SC_CHAR_MAX,                           /* [== CHAR_MAX] */
	_SC_CHAR_MIN,                           /* [== CHAR_MIN] */
	_SC_INT_MAX,                            /* [== INT_MAX] */
	_SC_INT_MIN,                            /* [== INT_MIN] */
	_SC_LONG_BIT,                           /* [== LONG_BIT] */
	_SC_WORD_BIT,                           /* [== WORD_BIT] */
	_SC_MB_LEN_MAX,                         /* [== MB_LEN_MAX] */
	_SC_NZERO,                              /* [== NZERO] */
	_SC_SSIZE_MAX,                          /* [== SSIZE_MAX] */
	_SC_SCHAR_MAX,                          /* [== SCHAR_MAX] */
	_SC_SCHAR_MIN,                          /* [== SCHAR_MIN] */
	_SC_SHRT_MAX,                           /* [== SHRT_MAX] */
	_SC_SHRT_MIN,                           /* [== SHRT_MIN] */
	_SC_UCHAR_MAX,                          /* [== UCHAR_MAX] */
	_SC_UINT_MAX,                           /* [== UINT_MAX] */
	_SC_ULONG_MAX,                          /* [== ULONG_MAX] */
	_SC_USHRT_MAX,                          /* [== USHRT_MAX] */
	_SC_NL_ARGMAX,                          /* [== NL_ARGMAX, unlimited] */
	_SC_NL_LANGMAX,                         /* [== NL_LANGMAX, unlimited] */
	_SC_NL_MSGMAX,                          /* [== NL_MSGMAX, unlimited] */
	_SC_NL_NMAX,                            /* [== NL_NMAX, unlimited] */
	_SC_NL_SETMAX,                          /* [== NL_SETMAX, unlimited] */
	_SC_NL_TEXTMAX,                         /* [== NL_TEXTMAX, unlimited] */
	_SC_XBS5_ILP32_OFF32,                   /* ... */
	_SC_XBS5_ILP32_OFFBIG,                  /* ... */
	_SC_XBS5_LP64_OFF64,                    /* ... */
	_SC_XBS5_LPBIG_OFFBIG,                  /* ... */
	_SC_XOPEN_LEGACY,                       /* [== _XOPEN_LEGACY] */
	_SC_XOPEN_REALTIME,                     /* [== _XOPEN_REALTIME, unlimited] */
	_SC_XOPEN_REALTIME_THREADS,             /* [== _XOPEN_REALTIME_THREADS, unlimited] */
	_SC_ADVISORY_INFO,                      /* [== _POSIX_ADVISORY_INFO] */
	_SC_BARRIERS,                           /* [== _POSIX_BARRIERS] */
	_SC_BASE,                               /* [== _POSIX_BASE, unlimited] */
	_SC_C_LANG_SUPPORT,                     /* [== _POSIX_C_LANG_SUPPORT, unlimited] */
	_SC_C_LANG_SUPPORT_R,                   /* [== _POSIX_C_LANG_SUPPORT_R, unlimited] */
	_SC_CLOCK_SELECTION,                    /* [== _POSIX_CLOCK_SELECTION, unlimited] */
	_SC_CPUTIME,                            /* [== _POSIX_CPUTIME, unlimited] */
	_SC_THREAD_CPUTIME,                     /* [== _POSIX_THREAD_CPUTIME, unlimited] */
	_SC_DEVICE_IO,                          /* [== _POSIX_DEVICE_IO, unlimited] */
	_SC_DEVICE_SPECIFIC,                    /* [== _POSIX_DEVICE_SPECIFIC, unlimited] */
	_SC_DEVICE_SPECIFIC_R,                  /* [== _POSIX_DEVICE_SPECIFIC_R, unlimited] */
	_SC_FD_MGMT,                            /* [== _POSIX_FD_MGMT, unlimited] */
	_SC_FIFO,                               /* [== _POSIX_FIFO, unlimited] */
	_SC_PIPE,                               /* [== _POSIX_PIPE, unlimited] */
	_SC_FILE_ATTRIBUTES,                    /* [== _POSIX_FILE_ATTRIBUTES, unlimited] */
	_SC_FILE_LOCKING,                       /* [== _POSIX_FILE_LOCKING, unlimited] */
	_SC_FILE_SYSTEM,                        /* [== _POSIX_FILE_SYSTEM, unlimited] */
	_SC_MONOTONIC_CLOCK,                    /* [== _POSIX_MONOTONIC_CLOCK, unlimited] */
	_SC_MULTI_PROCESS,                      /* [== _POSIX_MULTI_PROCESS, unlimited] */
	_SC_SINGLE_PROCESS,                     /* [== _POSIX_SINGLE_PROCESS, unlimited] */
	_SC_NETWORKING,                         /* [== _POSIX_NETWORKING, unlimited] */
	_SC_READER_WRITER_LOCKS,                /* [== _POSIX_READER_WRITER_LOCKS, unlimited] */
	_SC_SPIN_LOCKS,                         /* [== _POSIX_SPIN_LOCKS, unlimited] */
	_SC_REGEXP,                             /* [== _POSIX_REGEXP, unlimited] */
	_SC_REGEX_VERSION,                      /* [== unlimited] */
	_SC_SHELL,                              /* [== _POSIX_SHELL, unlimited] */
	_SC_SIGNALS,                            /* [== _POSIX_SIGNALS, unlimited] */
	_SC_SPAWN,                              /* [== _POSIX_SPAWN, unlimited] */
	_SC_SPORADIC_SERVER,                    /* [== _POSIX_SPORADIC_SERVER, unlimited] */
	_SC_THREAD_SPORADIC_SERVER,             /* [== _POSIX_THREAD_SPORADIC_SERVER, unlimited] */
	_SC_SYSTEM_DATABASE,                    /* [== _POSIX_SYSTEM_DATABASE, unlimited] */
	_SC_SYSTEM_DATABASE_R,                  /* [== _POSIX_SYSTEM_DATABASE_R, unlimited] */
	_SC_TIMEOUTS,                           /* [== _POSIX_TIMEOUTS, unlimited] */
	_SC_TYPED_MEMORY_OBJECTS,               /* [== _POSIX_TYPED_MEMORY_OBJECTS, unlimited] */
	_SC_USER_GROUPS,                        /* [== _POSIX_USER_GROUPS, unlimited] */
	_SC_USER_GROUPS_R,                      /* [== _POSIX_USER_GROUPS_R, unlimited] */
	_SC_2_PBS,                              /* [== _POSIX2_PBS, unlimited] */
	_SC_2_PBS_ACCOUNTING,                   /* [== _POSIX2_PBS_ACCOUNTING, unlimited] */
	_SC_2_PBS_LOCATE,                       /* [== _POSIX2_PBS_LOCATE, unlimited] */
	_SC_2_PBS_MESSAGE,                      /* [== _POSIX2_PBS_MESSAGE, unlimited] */
	_SC_2_PBS_TRACK,                        /* [== _POSIX2_PBS_TRACK, unlimited] */
	_SC_SYMLOOP_MAX,                        /* [== custom, MAXSYMLINKS, SYMLOOP_MAX] */
	_SC_STREAMS,                            /* [== unlimited] */
	_SC_2_PBS_CHECKPOINT,                   /* [== _POSIX2_PBS_CHECKPOINT, unlimited] */
	_SC_V6_ILP32_OFF32,                     /* ... */
	_SC_V6_ILP32_OFFBIG,                    /* ... */
	_SC_V6_LP64_OFF64,                      /* ... */
	_SC_V6_LPBIG_OFFBIG,                    /* ... */
	_SC_HOST_NAME_MAX,                      /* [== HOST_NAME_MAX, _POSIX_HOST_NAME_MAX] */
	_SC_TRACE,                              /* [== _POSIX_TRACE, unlimited] */
	_SC_TRACE_EVENT_FILTER,                 /* [== _POSIX_TRACE_EVENT_FILTER] */
	_SC_TRACE_INHERIT,                      /* [== _POSIX_TRACE_INHERIT] */
	_SC_TRACE_LOG,                          /* [== _POSIX_TRACE_LOG] */
	_SC_LEVEL1_ICACHE_SIZE,                 /* [== 0] */
	_SC_LEVEL1_ICACHE_ASSOC,                /* [== 0] */
	_SC_LEVEL1_ICACHE_LINESIZE,             /* [== 0] */
	_SC_LEVEL1_DCACHE_SIZE,                 /* [== 0] */
	_SC_LEVEL1_DCACHE_ASSOC,                /* [== 0] */
	_SC_LEVEL1_DCACHE_LINESIZE,             /* [== 0] */
	_SC_LEVEL2_CACHE_SIZE,                  /* [== 0] */
	_SC_LEVEL2_CACHE_ASSOC,                 /* [== 0] */
	_SC_LEVEL2_CACHE_LINESIZE,              /* [== 0] */
	_SC_LEVEL3_CACHE_SIZE,                  /* [== 0] */
	_SC_LEVEL3_CACHE_ASSOC,                 /* [== 0] */
	_SC_LEVEL3_CACHE_LINESIZE,              /* [== 0] */
	_SC_LEVEL4_CACHE_SIZE,                  /* [== 0] */
	_SC_LEVEL4_CACHE_ASSOC,                 /* [== 0] */
	_SC_LEVEL4_CACHE_LINESIZE,              /* [== 0] */
	_SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50, /* [== _POSIX_IPV6, unlimited] */
	_SC_RAW_SOCKETS,                        /* [== _POSIX_RAW_SOCKETS, unlimited] */
	_SC_V7_ILP32_OFF32,                     /* ... */
	_SC_V7_ILP32_OFFBIG,                    /* ... */
	_SC_V7_LP64_OFF64,                      /* ... */
	_SC_V7_LPBIG_OFFBIG,                    /* ... */
	_SC_SS_REPL_MAX,                        /* [== _POSIX_SS_REPL_MAX, unlimited] */
	_SC_TRACE_EVENT_NAME_MAX,               /* [== unlimited] */
	_SC_TRACE_NAME_MAX,                     /* [== unlimited] */
	_SC_TRACE_SYS_MAX,                      /* [== unlimited] */
	_SC_TRACE_USER_EVENT_MAX,               /* [== unlimited] */
	_SC_XOPEN_STREAMS,                      /* [== unlimited] */
	_SC_THREAD_ROBUST_PRIO_INHERIT,         /* [== _POSIX_THREAD_ROBUST_PRIO_INHERIT, unlimited] */
	_SC_THREAD_ROBUST_PRIO_PROTECT,         /* [== _POSIX_THREAD_ROBUST_PRIO_PROTECT, unlimited] */
#ifdef __USE_KOS
	_SC_COUNT
#endif /* __USE_KOS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define _SC_ARG_MAX                      _SC_ARG_MAX                      /* [== unlimited, ARG_MAX] */
#define _SC_CHILD_MAX                    _SC_CHILD_MAX                    /* [== unlimited, CHILD_MAX] */
#define _SC_CLK_TCK                      _SC_CLK_TCK                      /* [== custom, CLK_TCK] */
#define _SC_NGROUPS_MAX                  _SC_NGROUPS_MAX                  /* [== unlimited, NGROUPS_MAX] */
#define _SC_OPEN_MAX                     _SC_OPEN_MAX                     /* [== unlimited, OPEN_MAX] */
#define _SC_STREAM_MAX                   _SC_STREAM_MAX                   /* [== unlimited, STREAM_MAX, FOPEN_MAX] */
#define _SC_TZNAME_MAX                   _SC_TZNAME_MAX                   /* [== unlimited, _POSIX_TZNAME_MAX] */
#define _SC_JOB_CONTROL                  _SC_JOB_CONTROL                  /* [== _POSIX_JOB_CONTROL] */
#define _SC_SAVED_IDS                    _SC_SAVED_IDS                    /* [== _POSIX_SAVED_IDS] */
#define _SC_REALTIME_SIGNALS             _SC_REALTIME_SIGNALS             /* [== _POSIX_REALTIME_SIGNALS] */
#define _SC_PRIORITY_SCHEDULING          _SC_PRIORITY_SCHEDULING          /* [== _POSIX_PRIORITY_SCHEDULING] */
#define _SC_TIMERS                       _SC_TIMERS                       /* [== _POSIX_TIMERS] */
#define _SC_ASYNCHRONOUS_IO              _SC_ASYNCHRONOUS_IO              /* [== _POSIX_ASYNCHRONOUS_IO] */
#define _SC_PRIORITIZED_IO               _SC_PRIORITIZED_IO               /* [== _POSIX_PRIORITIZED_IO] */
#define _SC_SYNCHRONIZED_IO              _SC_SYNCHRONIZED_IO              /* [== _POSIX_SYNCHRONIZED_IO] */
#define _SC_FSYNC                        _SC_FSYNC                        /* [== _POSIX_FSYNC] */
#define _SC_MAPPED_FILES                 _SC_MAPPED_FILES                 /* [== _POSIX_MAPPED_FILES] */
#define _SC_MEMLOCK                      _SC_MEMLOCK                      /* [== _POSIX_MEMLOCK] */
#define _SC_MEMLOCK_RANGE                _SC_MEMLOCK_RANGE                /* [== _POSIX_MEMLOCK_RANGE] */
#define _SC_MEMORY_PROTECTION            _SC_MEMORY_PROTECTION            /* [== _POSIX_MEMORY_PROTECTION] */
#define _SC_MESSAGE_PASSING              _SC_MESSAGE_PASSING              /* [== _POSIX_MESSAGE_PASSING] */
#define _SC_SEMAPHORES                   _SC_SEMAPHORES                   /* [== _POSIX_SEMAPHORES] */
#define _SC_SHARED_MEMORY_OBJECTS        _SC_SHARED_MEMORY_OBJECTS        /* [== _POSIX_SHARED_MEMORY_OBJECTS] */
#define _SC_AIO_LISTIO_MAX               _SC_AIO_LISTIO_MAX               /* [== _POSIX_AIO_LISTIO_MAX] */
#define _SC_AIO_MAX                      _SC_AIO_MAX                      /* [== _POSIX_AIO_MAX] */
#define _SC_AIO_PRIO_DELTA_MAX           _SC_AIO_PRIO_DELTA_MAX           /* [== AIO_PRIO_DELTA_MAX] */
#define _SC_DELAYTIMER_MAX               _SC_DELAYTIMER_MAX               /* [== DELAYTIMER_MAX, _POSIX_DELAYTIMER_MAX] */
#define _SC_MQ_OPEN_MAX                  _SC_MQ_OPEN_MAX                  /* [== _POSIX_MQ_OPEN_MAX] */
#define _SC_MQ_PRIO_MAX                  _SC_MQ_PRIO_MAX                  /* [== MQ_PRIO_MAX, _POSIX_MQ_PRIO_MAX] */
#define _SC_VERSION                      _SC_VERSION                      /* [== _POSIX_VERSION] */
#define _SC_PAGESIZE                     _SC_PAGESIZE                     /* [== __ARCH_PAGESIZE] */
#define _SC_PAGE_SIZE                    _SC_PAGE_SIZE                    /* ... */
#define _SC_RTSIG_MAX                    _SC_RTSIG_MAX                    /* [== RTSIG_MAX, _POSIX_RTSIG_MAX] */
#define _SC_SEM_NSEMS_MAX                _SC_SEM_NSEMS_MAX                /* [== _POSIX_SEM_NSEMS_MAX] */
#define _SC_SEM_VALUE_MAX                _SC_SEM_VALUE_MAX                /* [== SEM_VALUE_MAX, _POSIX_SEM_VALUE_MAX] */
#define _SC_SIGQUEUE_MAX                 _SC_SIGQUEUE_MAX                 /* [== _POSIX_SIGQUEUE_MAX] */
#define _SC_TIMER_MAX                    _SC_TIMER_MAX                    /* [== _POSIX_TIMER_MAX] */
#define _SC_BC_BASE_MAX                  _SC_BC_BASE_MAX                  /* [== BC_BASE_MAX, _POSIX2_BC_BASE_MAX] */
#define _SC_BC_DIM_MAX                   _SC_BC_DIM_MAX                   /* [== BC_DIM_MAX, _POSIX2_BC_DIM_MAX] */
#define _SC_BC_SCALE_MAX                 _SC_BC_SCALE_MAX                 /* [== BC_SCALE_MAX, _POSIX2_BC_SCALE_MAX] */
#define _SC_BC_STRING_MAX                _SC_BC_STRING_MAX                /* [== BC_STRING_MAX, _POSIX2_BC_STRING_MAX] */
#define _SC_COLL_WEIGHTS_MAX             _SC_COLL_WEIGHTS_MAX             /* [== COLL_WEIGHTS_MAX, _POSIX2_COLL_WEIGHTS_MAX] */
#define _SC_EQUIV_CLASS_MAX              _SC_EQUIV_CLASS_MAX              /* ... */
#define _SC_EXPR_NEST_MAX                _SC_EXPR_NEST_MAX                /* [== EXPR_NEST_MAX, _POSIX2_EXPR_NEST_MAX] */
#define _SC_LINE_MAX                     _SC_LINE_MAX                     /* [== LINE_MAX, _POSIX2_LINE_MAX] */
#define _SC_RE_DUP_MAX                   _SC_RE_DUP_MAX                   /* [== RE_DUP_MAX, _POSIX_RE_DUP_MAX] */
#define _SC_CHARCLASS_NAME_MAX           _SC_CHARCLASS_NAME_MAX           /* [== CHARCLASS_NAME_MAX, _POSIX2_CHARCLASS_NAME_MAX] */
#define _SC_2_VERSION                    _SC_2_VERSION                    /* [== _POSIX2_VERSION] */
#define _SC_2_C_BIND                     _SC_2_C_BIND                     /* [== _POSIX2_C_BIND, unlimited] */
#define _SC_2_C_DEV                      _SC_2_C_DEV                      /* [== _SC_2_C_DEV, unlimited] */
#define _SC_2_FORT_DEV                   _SC_2_FORT_DEV                   /* [== _POSIX2_FORT_DEV, unlimited] */
#define _SC_2_FORT_RUN                   _SC_2_FORT_RUN                   /* [== _POSIX2_FORT_RUN, unlimited] */
#define _SC_2_SW_DEV                     _SC_2_SW_DEV                     /* [== _POSIX2_SW_DEV, unlimited] */
#define _SC_2_LOCALEDEF                  _SC_2_LOCALEDEF                  /* [== _POSIX2_LOCALEDEF, unlimited] */
#define _SC_PII                          _SC_PII                          /* [== defined(_POSIX_PII)] */
#define _SC_PII_XTI                      _SC_PII_XTI                      /* [== defined(_POSIX_PII_XTI)] */
#define _SC_PII_SOCKET                   _SC_PII_SOCKET                   /* [== defined(_POSIX_PII_SOCKET)] */
#define _SC_PII_INTERNET                 _SC_PII_INTERNET                 /* [== defined(_POSIX_PII_INTERNET)] */
#define _SC_PII_OSI                      _SC_PII_OSI                      /* [== defined(_POSIX_PII_OSI)] */
#define _SC_POLL                         _SC_POLL                         /* [== defined(_POSIX_POLL)] */
#define _SC_SELECT                       _SC_SELECT                       /* [== defined(_POSIX_SELECT)] */
#define _SC_UIO_MAXIOV                   _SC_UIO_MAXIOV                   /* [== unlimited, UIO_MAXIOV] */
#define _SC_IOV_MAX                      _SC_IOV_MAX                      /* ... */
#define _SC_PII_INTERNET_STREAM          _SC_PII_INTERNET_STREAM          /* [== defined(_POSIX_PII_INTERNET_STREAM)] */
#define _SC_PII_INTERNET_DGRAM           _SC_PII_INTERNET_DGRAM           /* [== defined(_POSIX_PII_INTERNET_DGRAM)] */
#define _SC_PII_OSI_COTS                 _SC_PII_OSI_COTS                 /* [== defined(_POSIX_PII_OSI_COTS)] */
#define _SC_PII_OSI_CLTS                 _SC_PII_OSI_CLTS                 /* [== defined(_POSIX_PII_OSI_CLTS)] */
#define _SC_PII_OSI_M                    _SC_PII_OSI_M                    /* [== defined(_POSIX_PII_OSI_M)] */
#define _SC_T_IOV_MAX                    _SC_T_IOV_MAX                    /* [== unlimited, IOV_MAX] */
#define _SC_THREADS                      _SC_THREADS                      /* [== _POSIX_THREADS] */
#define _SC_THREAD_SAFE_FUNCTIONS        _SC_THREAD_SAFE_FUNCTIONS        /* [== _POSIX_THREAD_SAFE_FUNCTIONS] */
#define _SC_GETGR_R_SIZE_MAX             _SC_GETGR_R_SIZE_MAX             /* [== NSS_BUFLEN_GROUP] */
#define _SC_GETPW_R_SIZE_MAX             _SC_GETPW_R_SIZE_MAX             /* [== NSS_BUFLEN_PASSWD] */
#define _SC_LOGIN_NAME_MAX               _SC_LOGIN_NAME_MAX               /* [== LOGIN_NAME_MAX] */
#define _SC_TTY_NAME_MAX                 _SC_TTY_NAME_MAX                 /* [== TTY_NAME_MAX] */
#define _SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS /* [== _POSIX_THREAD_DESTRUCTOR_ITERATIONS] */
#define _SC_THREAD_KEYS_MAX              _SC_THREAD_KEYS_MAX              /* [== _POSIX_THREAD_KEYS_MAX] */
#define _SC_THREAD_STACK_MIN             _SC_THREAD_STACK_MIN             /* [== PTHREAD_STACK_MIN] */
#define _SC_THREAD_THREADS_MAX           _SC_THREAD_THREADS_MAX           /* [== unlimited, _POSIX_THREAD_THREADS_MAX] */
#define _SC_THREAD_ATTR_STACKADDR        _SC_THREAD_ATTR_STACKADDR        /* [== _POSIX_THREAD_ATTR_STACKADDR] */
#define _SC_THREAD_ATTR_STACKSIZE        _SC_THREAD_ATTR_STACKSIZE        /* [== _POSIX_THREAD_ATTR_STACKSIZE] */
#define _SC_THREAD_PRIORITY_SCHEDULING   _SC_THREAD_PRIORITY_SCHEDULING   /* [== _POSIX_THREAD_PRIORITY_SCHEDULING] */
#define _SC_THREAD_PRIO_INHERIT          _SC_THREAD_PRIO_INHERIT          /* [== _POSIX_THREAD_PRIO_INHERIT] */
#define _SC_THREAD_PRIO_PROTECT          _SC_THREAD_PRIO_PROTECT          /* [== _POSIX_THREAD_PRIO_PROTECT] */
#define _SC_THREAD_PROCESS_SHARED        _SC_THREAD_PROCESS_SHARED        /* [== _POSIX_THREAD_PROCESS_SHARED] */
#define _SC_NPROCESSORS_CONF             _SC_NPROCESSORS_CONF             /* [== custom] */
#define _SC_NPROCESSORS_ONLN             _SC_NPROCESSORS_ONLN             /* [== custom] */
#define _SC_NPROC_ONLN                   _SC_NPROC_ONLN                   /* ... */
#define _SC_PHYS_PAGES                   _SC_PHYS_PAGES                   /* [== custom] */
#define _SC_AVPHYS_PAGES                 _SC_AVPHYS_PAGES                 /* [== custom] */
#define _SC_ATEXIT_MAX                   _SC_ATEXIT_MAX                   /* [== unlimited] */
#define _SC_PASS_MAX                     _SC_PASS_MAX                     /* [== BUFSIZ] */
#define _SC_XOPEN_VERSION                _SC_XOPEN_VERSION                /* [== _XOPEN_VERSION] */
#define _SC_XOPEN_XCU_VERSION            _SC_XOPEN_XCU_VERSION            /* [== _XOPEN_XCU_VERSION] */
#define _SC_XOPEN_UNIX                   _SC_XOPEN_UNIX                   /* [== _XOPEN_UNIX] */
#define _SC_XOPEN_CRYPT                  _SC_XOPEN_CRYPT                  /* [== _XOPEN_CRYPT] */
#define _SC_XOPEN_ENH_I18N               _SC_XOPEN_ENH_I18N               /* [== _XOPEN_ENH_I18N] */
#define _SC_XOPEN_SHM                    _SC_XOPEN_SHM                    /* [== _XOPEN_SHM] */
#define _SC_2_CHAR_TERM                  _SC_2_CHAR_TERM                  /* [== _POSIX2_CHAR_TERM] */
#define _SC_2_C_VERSION                  _SC_2_C_VERSION                  /* [== _POSIX2_C_VERSION] */
#define _SC_2_UPE                        _SC_2_UPE                        /* [== _POSIX2_UPE, unlimited] */
#define _SC_XOPEN_XPG2                   _SC_XOPEN_XPG2                   /* [== _XOPEN_XPG2] */
#define _SC_XOPEN_XPG3                   _SC_XOPEN_XPG3                   /* [== _XOPEN_XPG3] */
#define _SC_XOPEN_XPG4                   _SC_XOPEN_XPG4                   /* [== _XOPEN_XPG4] */
#define _SC_CHAR_BIT                     _SC_CHAR_BIT                     /* [== CHAR_BIT] */
#define _SC_CHAR_MAX                     _SC_CHAR_MAX                     /* [== CHAR_MAX] */
#define _SC_CHAR_MIN                     _SC_CHAR_MIN                     /* [== CHAR_MIN] */
#define _SC_INT_MAX                      _SC_INT_MAX                      /* [== INT_MAX] */
#define _SC_INT_MIN                      _SC_INT_MIN                      /* [== INT_MIN] */
#define _SC_LONG_BIT                     _SC_LONG_BIT                     /* [== LONG_BIT] */
#define _SC_WORD_BIT                     _SC_WORD_BIT                     /* [== WORD_BIT] */
#define _SC_MB_LEN_MAX                   _SC_MB_LEN_MAX                   /* [== MB_LEN_MAX] */
#define _SC_NZERO                        _SC_NZERO                        /* [== NZERO] */
#define _SC_SSIZE_MAX                    _SC_SSIZE_MAX                    /* [== SSIZE_MAX] */
#define _SC_SCHAR_MAX                    _SC_SCHAR_MAX                    /* [== SCHAR_MAX] */
#define _SC_SCHAR_MIN                    _SC_SCHAR_MIN                    /* [== SCHAR_MIN] */
#define _SC_SHRT_MAX                     _SC_SHRT_MAX                     /* [== SHRT_MAX] */
#define _SC_SHRT_MIN                     _SC_SHRT_MIN                     /* [== SHRT_MIN] */
#define _SC_UCHAR_MAX                    _SC_UCHAR_MAX                    /* [== UCHAR_MAX] */
#define _SC_UINT_MAX                     _SC_UINT_MAX                     /* [== UINT_MAX] */
#define _SC_ULONG_MAX                    _SC_ULONG_MAX                    /* [== ULONG_MAX] */
#define _SC_USHRT_MAX                    _SC_USHRT_MAX                    /* [== USHRT_MAX] */
#define _SC_NL_ARGMAX                    _SC_NL_ARGMAX                    /* [== NL_ARGMAX, unlimited] */
#define _SC_NL_LANGMAX                   _SC_NL_LANGMAX                   /* [== NL_LANGMAX, unlimited] */
#define _SC_NL_MSGMAX                    _SC_NL_MSGMAX                    /* [== NL_MSGMAX, unlimited] */
#define _SC_NL_NMAX                      _SC_NL_NMAX                      /* [== NL_NMAX, unlimited] */
#define _SC_NL_SETMAX                    _SC_NL_SETMAX                    /* [== NL_SETMAX, unlimited] */
#define _SC_NL_TEXTMAX                   _SC_NL_TEXTMAX                   /* [== NL_TEXTMAX, unlimited] */
#define _SC_XBS5_ILP32_OFF32             _SC_XBS5_ILP32_OFF32             /* ... */
#define _SC_XBS5_ILP32_OFFBIG            _SC_XBS5_ILP32_OFFBIG            /* ... */
#define _SC_XBS5_LP64_OFF64              _SC_XBS5_LP64_OFF64              /* ... */
#define _SC_XBS5_LPBIG_OFFBIG            _SC_XBS5_LPBIG_OFFBIG            /* ... */
#define _SC_XOPEN_LEGACY                 _SC_XOPEN_LEGACY                 /* [== _XOPEN_LEGACY] */
#define _SC_XOPEN_REALTIME               _SC_XOPEN_REALTIME               /* [== _XOPEN_REALTIME, unlimited] */
#define _SC_XOPEN_REALTIME_THREADS       _SC_XOPEN_REALTIME_THREADS       /* [== _XOPEN_REALTIME_THREADS, unlimited] */
#define _SC_ADVISORY_INFO                _SC_ADVISORY_INFO                /* [== _POSIX_ADVISORY_INFO] */
#define _SC_BARRIERS                     _SC_BARRIERS                     /* [== _POSIX_BARRIERS] */
#define _SC_BASE                         _SC_BASE                         /* [== _POSIX_BASE, unlimited] */
#define _SC_C_LANG_SUPPORT               _SC_C_LANG_SUPPORT               /* [== _POSIX_C_LANG_SUPPORT, unlimited] */
#define _SC_C_LANG_SUPPORT_R             _SC_C_LANG_SUPPORT_R             /* [== _POSIX_C_LANG_SUPPORT_R, unlimited] */
#define _SC_CLOCK_SELECTION              _SC_CLOCK_SELECTION              /* [== _POSIX_CLOCK_SELECTION, unlimited] */
#define _SC_CPUTIME                      _SC_CPUTIME                      /* [== _POSIX_CPUTIME, unlimited] */
#define _SC_THREAD_CPUTIME               _SC_THREAD_CPUTIME               /* [== _POSIX_THREAD_CPUTIME, unlimited] */
#define _SC_DEVICE_IO                    _SC_DEVICE_IO                    /* [== _POSIX_DEVICE_IO, unlimited] */
#define _SC_DEVICE_SPECIFIC              _SC_DEVICE_SPECIFIC              /* [== _POSIX_DEVICE_SPECIFIC, unlimited] */
#define _SC_DEVICE_SPECIFIC_R            _SC_DEVICE_SPECIFIC_R            /* [== _POSIX_DEVICE_SPECIFIC_R, unlimited] */
#define _SC_FD_MGMT                      _SC_FD_MGMT                      /* [== _POSIX_FD_MGMT, unlimited] */
#define _SC_FIFO                         _SC_FIFO                         /* [== _POSIX_FIFO, unlimited] */
#define _SC_PIPE                         _SC_PIPE                         /* [== _POSIX_PIPE, unlimited] */
#define _SC_FILE_ATTRIBUTES              _SC_FILE_ATTRIBUTES              /* [== _POSIX_FILE_ATTRIBUTES, unlimited] */
#define _SC_FILE_LOCKING                 _SC_FILE_LOCKING                 /* [== _POSIX_FILE_LOCKING, unlimited] */
#define _SC_FILE_SYSTEM                  _SC_FILE_SYSTEM                  /* [== _POSIX_FILE_SYSTEM, unlimited] */
#define _SC_MONOTONIC_CLOCK              _SC_MONOTONIC_CLOCK              /* [== _POSIX_MONOTONIC_CLOCK, unlimited] */
#define _SC_MULTI_PROCESS                _SC_MULTI_PROCESS                /* [== _POSIX_MULTI_PROCESS, unlimited] */
#define _SC_SINGLE_PROCESS               _SC_SINGLE_PROCESS               /* [== _POSIX_SINGLE_PROCESS, unlimited] */
#define _SC_NETWORKING                   _SC_NETWORKING                   /* [== _POSIX_NETWORKING, unlimited] */
#define _SC_READER_WRITER_LOCKS          _SC_READER_WRITER_LOCKS          /* [== _POSIX_READER_WRITER_LOCKS, unlimited] */
#define _SC_SPIN_LOCKS                   _SC_SPIN_LOCKS                   /* [== _POSIX_SPIN_LOCKS, unlimited] */
#define _SC_REGEXP                       _SC_REGEXP                       /* [== _POSIX_REGEXP, unlimited] */
#define _SC_REGEX_VERSION                _SC_REGEX_VERSION                /* [== unlimited] */
#define _SC_SHELL                        _SC_SHELL                        /* [== _POSIX_SHELL, unlimited] */
#define _SC_SIGNALS                      _SC_SIGNALS                      /* [== _POSIX_SIGNALS, unlimited] */
#define _SC_SPAWN                        _SC_SPAWN                        /* [== _POSIX_SPAWN, unlimited] */
#define _SC_SPORADIC_SERVER              _SC_SPORADIC_SERVER              /* [== _POSIX_SPORADIC_SERVER, unlimited] */
#define _SC_THREAD_SPORADIC_SERVER       _SC_THREAD_SPORADIC_SERVER       /* [== _POSIX_THREAD_SPORADIC_SERVER, unlimited] */
#define _SC_SYSTEM_DATABASE              _SC_SYSTEM_DATABASE              /* [== _POSIX_SYSTEM_DATABASE, unlimited] */
#define _SC_SYSTEM_DATABASE_R            _SC_SYSTEM_DATABASE_R            /* [== _POSIX_SYSTEM_DATABASE_R, unlimited] */
#define _SC_TIMEOUTS                     _SC_TIMEOUTS                     /* [== _POSIX_TIMEOUTS, unlimited] */
#define _SC_TYPED_MEMORY_OBJECTS         _SC_TYPED_MEMORY_OBJECTS         /* [== _POSIX_TYPED_MEMORY_OBJECTS, unlimited] */
#define _SC_USER_GROUPS                  _SC_USER_GROUPS                  /* [== _POSIX_USER_GROUPS, unlimited] */
#define _SC_USER_GROUPS_R                _SC_USER_GROUPS_R                /* [== _POSIX_USER_GROUPS_R, unlimited] */
#define _SC_2_PBS                        _SC_2_PBS                        /* [== _POSIX2_PBS, unlimited] */
#define _SC_2_PBS_ACCOUNTING             _SC_2_PBS_ACCOUNTING             /* [== _POSIX2_PBS_ACCOUNTING, unlimited] */
#define _SC_2_PBS_LOCATE                 _SC_2_PBS_LOCATE                 /* [== _POSIX2_PBS_LOCATE, unlimited] */
#define _SC_2_PBS_MESSAGE                _SC_2_PBS_MESSAGE                /* [== _POSIX2_PBS_MESSAGE, unlimited] */
#define _SC_2_PBS_TRACK                  _SC_2_PBS_TRACK                  /* [== _POSIX2_PBS_TRACK, unlimited] */
#define _SC_SYMLOOP_MAX                  _SC_SYMLOOP_MAX                  /* [== custom, MAXSYMLINKS, SYMLOOP_MAX] */
#define _SC_STREAMS                      _SC_STREAMS                      /* [== unlimited] */
#define _SC_2_PBS_CHECKPOINT             _SC_2_PBS_CHECKPOINT             /* [== _POSIX2_PBS_CHECKPOINT, unlimited] */
#define _SC_V6_ILP32_OFF32               _SC_V6_ILP32_OFF32               /* ... */
#define _SC_V6_ILP32_OFFBIG              _SC_V6_ILP32_OFFBIG              /* ... */
#define _SC_V6_LP64_OFF64                _SC_V6_LP64_OFF64                /* ... */
#define _SC_V6_LPBIG_OFFBIG              _SC_V6_LPBIG_OFFBIG              /* ... */
#define _SC_HOST_NAME_MAX                _SC_HOST_NAME_MAX                /* [== HOST_NAME_MAX, _POSIX_HOST_NAME_MAX] */
#define _SC_TRACE                        _SC_TRACE                        /* [== _POSIX_TRACE, unlimited] */
#define _SC_TRACE_EVENT_FILTER           _SC_TRACE_EVENT_FILTER           /* [== _POSIX_TRACE_EVENT_FILTER] */
#define _SC_TRACE_INHERIT                _SC_TRACE_INHERIT                /* [== _POSIX_TRACE_INHERIT] */
#define _SC_TRACE_LOG                    _SC_TRACE_LOG                    /* [== _POSIX_TRACE_LOG] */
#define _SC_LEVEL1_ICACHE_SIZE           _SC_LEVEL1_ICACHE_SIZE           /* [== 0] */
#define _SC_LEVEL1_ICACHE_ASSOC          _SC_LEVEL1_ICACHE_ASSOC          /* [== 0] */
#define _SC_LEVEL1_ICACHE_LINESIZE       _SC_LEVEL1_ICACHE_LINESIZE       /* [== 0] */
#define _SC_LEVEL1_DCACHE_SIZE           _SC_LEVEL1_DCACHE_SIZE           /* [== 0] */
#define _SC_LEVEL1_DCACHE_ASSOC          _SC_LEVEL1_DCACHE_ASSOC          /* [== 0] */
#define _SC_LEVEL1_DCACHE_LINESIZE       _SC_LEVEL1_DCACHE_LINESIZE       /* [== 0] */
#define _SC_LEVEL2_CACHE_SIZE            _SC_LEVEL2_CACHE_SIZE            /* [== 0] */
#define _SC_LEVEL2_CACHE_ASSOC           _SC_LEVEL2_CACHE_ASSOC           /* [== 0] */
#define _SC_LEVEL2_CACHE_LINESIZE        _SC_LEVEL2_CACHE_LINESIZE        /* [== 0] */
#define _SC_LEVEL3_CACHE_SIZE            _SC_LEVEL3_CACHE_SIZE            /* [== 0] */
#define _SC_LEVEL3_CACHE_ASSOC           _SC_LEVEL3_CACHE_ASSOC           /* [== 0] */
#define _SC_LEVEL3_CACHE_LINESIZE        _SC_LEVEL3_CACHE_LINESIZE        /* [== 0] */
#define _SC_LEVEL4_CACHE_SIZE            _SC_LEVEL4_CACHE_SIZE            /* [== 0] */
#define _SC_LEVEL4_CACHE_ASSOC           _SC_LEVEL4_CACHE_ASSOC           /* [== 0] */
#define _SC_LEVEL4_CACHE_LINESIZE        _SC_LEVEL4_CACHE_LINESIZE        /* [== 0] */
#define _SC_IPV6                         _SC_IPV6                         /* [== _POSIX_IPV6, unlimited] */
#define _SC_RAW_SOCKETS                  _SC_RAW_SOCKETS                  /* [== _POSIX_RAW_SOCKETS, unlimited] */
#define _SC_V7_ILP32_OFF32               _SC_V7_ILP32_OFF32               /* ... */
#define _SC_V7_ILP32_OFFBIG              _SC_V7_ILP32_OFFBIG              /* ... */
#define _SC_V7_LP64_OFF64                _SC_V7_LP64_OFF64                /* ... */
#define _SC_V7_LPBIG_OFFBIG              _SC_V7_LPBIG_OFFBIG              /* ... */
#define _SC_SS_REPL_MAX                  _SC_SS_REPL_MAX                  /* [== _POSIX_SS_REPL_MAX, unlimited] */
#define _SC_TRACE_EVENT_NAME_MAX         _SC_TRACE_EVENT_NAME_MAX         /* [== unlimited] */
#define _SC_TRACE_NAME_MAX               _SC_TRACE_NAME_MAX               /* [== unlimited] */
#define _SC_TRACE_SYS_MAX                _SC_TRACE_SYS_MAX                /* [== unlimited] */
#define _SC_TRACE_USER_EVENT_MAX         _SC_TRACE_USER_EVENT_MAX         /* [== unlimited] */
#define _SC_XOPEN_STREAMS                _SC_XOPEN_STREAMS                /* [== unlimited] */
#define _SC_THREAD_ROBUST_PRIO_INHERIT   _SC_THREAD_ROBUST_PRIO_INHERIT   /* [== _POSIX_THREAD_ROBUST_PRIO_INHERIT, unlimited] */
#define _SC_THREAD_ROBUST_PRIO_PROTECT   _SC_THREAD_ROBUST_PRIO_PROTECT   /* [== _POSIX_THREAD_ROBUST_PRIO_PROTECT, unlimited] */
#ifdef __USE_KOS
#define _SC_COUNT                        _SC_COUNT
#endif /* __USE_KOS */
#else /* __COMPILER_PREFERR_ENUMS */
#define _SC_ARG_MAX                      0   /* [== unlimited, ARG_MAX] */
#define _SC_CHILD_MAX                    1   /* [== unlimited, CHILD_MAX] */
#define _SC_CLK_TCK                      2   /* [== custom, CLK_TCK] */
#define _SC_NGROUPS_MAX                  3   /* [== unlimited, NGROUPS_MAX] */
#define _SC_OPEN_MAX                     4   /* [== unlimited, OPEN_MAX] */
#define _SC_STREAM_MAX                   5   /* [== unlimited, STREAM_MAX, FOPEN_MAX] */
#define _SC_TZNAME_MAX                   6   /* [== unlimited, _POSIX_TZNAME_MAX] */
#define _SC_JOB_CONTROL                  7   /* [== _POSIX_JOB_CONTROL] */
#define _SC_SAVED_IDS                    8   /* [== _POSIX_SAVED_IDS] */
#define _SC_REALTIME_SIGNALS             9   /* [== _POSIX_REALTIME_SIGNALS] */
#define _SC_PRIORITY_SCHEDULING          10  /* [== _POSIX_PRIORITY_SCHEDULING] */
#define _SC_TIMERS                       11  /* [== _POSIX_TIMERS] */
#define _SC_ASYNCHRONOUS_IO              12  /* [== _POSIX_ASYNCHRONOUS_IO] */
#define _SC_PRIORITIZED_IO               13  /* [== _POSIX_PRIORITIZED_IO] */
#define _SC_SYNCHRONIZED_IO              14  /* [== _POSIX_SYNCHRONIZED_IO] */
#define _SC_FSYNC                        15  /* [== _POSIX_FSYNC] */
#define _SC_MAPPED_FILES                 16  /* [== _POSIX_MAPPED_FILES] */
#define _SC_MEMLOCK                      17  /* [== _POSIX_MEMLOCK] */
#define _SC_MEMLOCK_RANGE                18  /* [== _POSIX_MEMLOCK_RANGE] */
#define _SC_MEMORY_PROTECTION            19  /* [== _POSIX_MEMORY_PROTECTION] */
#define _SC_MESSAGE_PASSING              20  /* [== _POSIX_MESSAGE_PASSING] */
#define _SC_SEMAPHORES                   21  /* [== _POSIX_SEMAPHORES] */
#define _SC_SHARED_MEMORY_OBJECTS        22  /* [== _POSIX_SHARED_MEMORY_OBJECTS] */
#define _SC_AIO_LISTIO_MAX               23  /* [== _POSIX_AIO_LISTIO_MAX] */
#define _SC_AIO_MAX                      24  /* [== _POSIX_AIO_MAX] */
#define _SC_AIO_PRIO_DELTA_MAX           25  /* [== AIO_PRIO_DELTA_MAX] */
#define _SC_DELAYTIMER_MAX               26  /* [== DELAYTIMER_MAX, _POSIX_DELAYTIMER_MAX] */
#define _SC_MQ_OPEN_MAX                  27  /* [== _POSIX_MQ_OPEN_MAX] */
#define _SC_MQ_PRIO_MAX                  28  /* [== MQ_PRIO_MAX, _POSIX_MQ_PRIO_MAX] */
#define _SC_VERSION                      29  /* [== _POSIX_VERSION] */
#define _SC_PAGESIZE                     30  /* [== __ARCH_PAGESIZE] */
#define _SC_PAGE_SIZE                    30  /* ... */
#define _SC_RTSIG_MAX                    31  /* [== RTSIG_MAX, _POSIX_RTSIG_MAX] */
#define _SC_SEM_NSEMS_MAX                32  /* [== _POSIX_SEM_NSEMS_MAX] */
#define _SC_SEM_VALUE_MAX                33  /* [== SEM_VALUE_MAX, _POSIX_SEM_VALUE_MAX] */
#define _SC_SIGQUEUE_MAX                 34  /* [== _POSIX_SIGQUEUE_MAX] */
#define _SC_TIMER_MAX                    35  /* [== _POSIX_TIMER_MAX] */
#define _SC_BC_BASE_MAX                  36  /* [== BC_BASE_MAX, _POSIX2_BC_BASE_MAX] */
#define _SC_BC_DIM_MAX                   37  /* [== BC_DIM_MAX, _POSIX2_BC_DIM_MAX] */
#define _SC_BC_SCALE_MAX                 38  /* [== BC_SCALE_MAX, _POSIX2_BC_SCALE_MAX] */
#define _SC_BC_STRING_MAX                39  /* [== BC_STRING_MAX, _POSIX2_BC_STRING_MAX] */
#define _SC_COLL_WEIGHTS_MAX             40  /* [== COLL_WEIGHTS_MAX, _POSIX2_COLL_WEIGHTS_MAX] */
#define _SC_EQUIV_CLASS_MAX              41  /* ... */
#define _SC_EXPR_NEST_MAX                42  /* [== EXPR_NEST_MAX, _POSIX2_EXPR_NEST_MAX] */
#define _SC_LINE_MAX                     43  /* [== LINE_MAX, _POSIX2_LINE_MAX] */
#define _SC_RE_DUP_MAX                   44  /* [== RE_DUP_MAX, _POSIX_RE_DUP_MAX] */
#define _SC_CHARCLASS_NAME_MAX           45  /* [== CHARCLASS_NAME_MAX, _POSIX2_CHARCLASS_NAME_MAX] */
#define _SC_2_VERSION                    46  /* [== _POSIX2_VERSION] */
#define _SC_2_C_BIND                     47  /* [== _POSIX2_C_BIND, unlimited] */
#define _SC_2_C_DEV                      48  /* [== _SC_2_C_DEV, unlimited] */
#define _SC_2_FORT_DEV                   49  /* [== _POSIX2_FORT_DEV, unlimited] */
#define _SC_2_FORT_RUN                   50  /* [== _POSIX2_FORT_RUN, unlimited] */
#define _SC_2_SW_DEV                     51  /* [== _POSIX2_SW_DEV, unlimited] */
#define _SC_2_LOCALEDEF                  52  /* [== _POSIX2_LOCALEDEF, unlimited] */
#define _SC_PII                          53  /* [== defined(_POSIX_PII)] */
#define _SC_PII_XTI                      54  /* [== defined(_POSIX_PII_XTI)] */
#define _SC_PII_SOCKET                   55  /* [== defined(_POSIX_PII_SOCKET)] */
#define _SC_PII_INTERNET                 56  /* [== defined(_POSIX_PII_INTERNET)] */
#define _SC_PII_OSI                      57  /* [== defined(_POSIX_PII_OSI)] */
#define _SC_POLL                         58  /* [== defined(_POSIX_POLL)] */
#define _SC_SELECT                       59  /* [== defined(_POSIX_SELECT)] */
#define _SC_UIO_MAXIOV                   60  /* [== unlimited, UIO_MAXIOV] */
#define _SC_IOV_MAX                      60  /* ... */
#define _SC_PII_INTERNET_STREAM          61  /* [== defined(_POSIX_PII_INTERNET_STREAM)] */
#define _SC_PII_INTERNET_DGRAM           62  /* [== defined(_POSIX_PII_INTERNET_DGRAM)] */
#define _SC_PII_OSI_COTS                 63  /* [== defined(_POSIX_PII_OSI_COTS)] */
#define _SC_PII_OSI_CLTS                 64  /* [== defined(_POSIX_PII_OSI_CLTS)] */
#define _SC_PII_OSI_M                    65  /* [== defined(_POSIX_PII_OSI_M)] */
#define _SC_T_IOV_MAX                    66  /* [== unlimited, IOV_MAX] */
#define _SC_THREADS                      67  /* [== _POSIX_THREADS] */
#define _SC_THREAD_SAFE_FUNCTIONS        68  /* [== _POSIX_THREAD_SAFE_FUNCTIONS] */
#define _SC_GETGR_R_SIZE_MAX             69  /* [== NSS_BUFLEN_GROUP] */
#define _SC_GETPW_R_SIZE_MAX             70  /* [== NSS_BUFLEN_PASSWD] */
#define _SC_LOGIN_NAME_MAX               71  /* [== LOGIN_NAME_MAX] */
#define _SC_TTY_NAME_MAX                 72  /* [== TTY_NAME_MAX] */
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 73  /* [== _POSIX_THREAD_DESTRUCTOR_ITERATIONS] */
#define _SC_THREAD_KEYS_MAX              74  /* [== _POSIX_THREAD_KEYS_MAX] */
#define _SC_THREAD_STACK_MIN             75  /* [== PTHREAD_STACK_MIN] */
#define _SC_THREAD_THREADS_MAX           76  /* [== unlimited, _POSIX_THREAD_THREADS_MAX] */
#define _SC_THREAD_ATTR_STACKADDR        77  /* [== _POSIX_THREAD_ATTR_STACKADDR] */
#define _SC_THREAD_ATTR_STACKSIZE        78  /* [== _POSIX_THREAD_ATTR_STACKSIZE] */
#define _SC_THREAD_PRIORITY_SCHEDULING   79  /* [== _POSIX_THREAD_PRIORITY_SCHEDULING] */
#define _SC_THREAD_PRIO_INHERIT          80  /* [== _POSIX_THREAD_PRIO_INHERIT] */
#define _SC_THREAD_PRIO_PROTECT          81  /* [== _POSIX_THREAD_PRIO_PROTECT] */
#define _SC_THREAD_PROCESS_SHARED        82  /* [== _POSIX_THREAD_PROCESS_SHARED] */
#define _SC_NPROCESSORS_CONF             83  /* [== custom] */
#define _SC_NPROCESSORS_ONLN             84  /* [== custom] */
#define _SC_NPROC_ONLN                   84  /* ... */
#define _SC_PHYS_PAGES                   85  /* [== custom] */
#define _SC_AVPHYS_PAGES                 86  /* [== custom] */
#define _SC_ATEXIT_MAX                   87  /* [== unlimited] */
#define _SC_PASS_MAX                     88  /* [== BUFSIZ] */
#define _SC_XOPEN_VERSION                89  /* [== _XOPEN_VERSION] */
#define _SC_XOPEN_XCU_VERSION            90  /* [== _XOPEN_XCU_VERSION] */
#define _SC_XOPEN_UNIX                   91  /* [== _XOPEN_UNIX] */
#define _SC_XOPEN_CRYPT                  92  /* [== _XOPEN_CRYPT] */
#define _SC_XOPEN_ENH_I18N               93  /* [== _XOPEN_ENH_I18N] */
#define _SC_XOPEN_SHM                    94  /* [== _XOPEN_SHM] */
#define _SC_2_CHAR_TERM                  95  /* [== _POSIX2_CHAR_TERM] */
#define _SC_2_C_VERSION                  96  /* [== _POSIX2_C_VERSION] */
#define _SC_2_UPE                        97  /* [== _POSIX2_UPE, unlimited] */
#define _SC_XOPEN_XPG2                   98  /* [== _XOPEN_XPG2] */
#define _SC_XOPEN_XPG3                   99  /* [== _XOPEN_XPG3] */
#define _SC_XOPEN_XPG4                   100 /* [== _XOPEN_XPG4] */
#define _SC_CHAR_BIT                     101 /* [== CHAR_BIT] */
#define _SC_CHAR_MAX                     102 /* [== CHAR_MAX] */
#define _SC_CHAR_MIN                     103 /* [== CHAR_MIN] */
#define _SC_INT_MAX                      104 /* [== INT_MAX] */
#define _SC_INT_MIN                      105 /* [== INT_MIN] */
#define _SC_LONG_BIT                     106 /* [== LONG_BIT] */
#define _SC_WORD_BIT                     107 /* [== WORD_BIT] */
#define _SC_MB_LEN_MAX                   108 /* [== MB_LEN_MAX] */
#define _SC_NZERO                        109 /* [== NZERO] */
#define _SC_SSIZE_MAX                    110 /* [== SSIZE_MAX] */
#define _SC_SCHAR_MAX                    111 /* [== SCHAR_MAX] */
#define _SC_SCHAR_MIN                    112 /* [== SCHAR_MIN] */
#define _SC_SHRT_MAX                     113 /* [== SHRT_MAX] */
#define _SC_SHRT_MIN                     114 /* [== SHRT_MIN] */
#define _SC_UCHAR_MAX                    115 /* [== UCHAR_MAX] */
#define _SC_UINT_MAX                     116 /* [== UINT_MAX] */
#define _SC_ULONG_MAX                    117 /* [== ULONG_MAX] */
#define _SC_USHRT_MAX                    118 /* [== USHRT_MAX] */
#define _SC_NL_ARGMAX                    119 /* [== NL_ARGMAX, unlimited] */
#define _SC_NL_LANGMAX                   120 /* [== NL_LANGMAX, unlimited] */
#define _SC_NL_MSGMAX                    121 /* [== NL_MSGMAX, unlimited] */
#define _SC_NL_NMAX                      122 /* [== NL_NMAX, unlimited] */
#define _SC_NL_SETMAX                    123 /* [== NL_SETMAX, unlimited] */
#define _SC_NL_TEXTMAX                   124 /* [== NL_TEXTMAX, unlimited] */
#define _SC_XBS5_ILP32_OFF32             125 /* ... */
#define _SC_XBS5_ILP32_OFFBIG            126 /* ... */
#define _SC_XBS5_LP64_OFF64              127 /* ... */
#define _SC_XBS5_LPBIG_OFFBIG            128 /* ... */
#define _SC_XOPEN_LEGACY                 129 /* [== _XOPEN_LEGACY] */
#define _SC_XOPEN_REALTIME               130 /* [== _XOPEN_REALTIME, unlimited] */
#define _SC_XOPEN_REALTIME_THREADS       131 /* [== _XOPEN_REALTIME_THREADS, unlimited] */
#define _SC_ADVISORY_INFO                132 /* [== _POSIX_ADVISORY_INFO] */
#define _SC_BARRIERS                     133 /* [== _POSIX_BARRIERS] */
#define _SC_BASE                         134 /* [== _POSIX_BASE, unlimited] */
#define _SC_C_LANG_SUPPORT               135 /* [== _POSIX_C_LANG_SUPPORT, unlimited] */
#define _SC_C_LANG_SUPPORT_R             136 /* [== _POSIX_C_LANG_SUPPORT_R, unlimited] */
#define _SC_CLOCK_SELECTION              137 /* [== _POSIX_CLOCK_SELECTION, unlimited] */
#define _SC_CPUTIME                      138 /* [== _POSIX_CPUTIME, unlimited] */
#define _SC_THREAD_CPUTIME               139 /* [== _POSIX_THREAD_CPUTIME, unlimited] */
#define _SC_DEVICE_IO                    140 /* [== _POSIX_DEVICE_IO, unlimited] */
#define _SC_DEVICE_SPECIFIC              141 /* [== _POSIX_DEVICE_SPECIFIC, unlimited] */
#define _SC_DEVICE_SPECIFIC_R            142 /* [== _POSIX_DEVICE_SPECIFIC_R, unlimited] */
#define _SC_FD_MGMT                      143 /* [== _POSIX_FD_MGMT, unlimited] */
#define _SC_FIFO                         144 /* [== _POSIX_FIFO, unlimited] */
#define _SC_PIPE                         145 /* [== _POSIX_PIPE, unlimited] */
#define _SC_FILE_ATTRIBUTES              146 /* [== _POSIX_FILE_ATTRIBUTES, unlimited] */
#define _SC_FILE_LOCKING                 147 /* [== _POSIX_FILE_LOCKING, unlimited] */
#define _SC_FILE_SYSTEM                  148 /* [== _POSIX_FILE_SYSTEM, unlimited] */
#define _SC_MONOTONIC_CLOCK              149 /* [== _POSIX_MONOTONIC_CLOCK, unlimited] */
#define _SC_MULTI_PROCESS                150 /* [== _POSIX_MULTI_PROCESS, unlimited] */
#define _SC_SINGLE_PROCESS               151 /* [== _POSIX_SINGLE_PROCESS, unlimited] */
#define _SC_NETWORKING                   152 /* [== _POSIX_NETWORKING, unlimited] */
#define _SC_READER_WRITER_LOCKS          153 /* [== _POSIX_READER_WRITER_LOCKS, unlimited] */
#define _SC_SPIN_LOCKS                   154 /* [== _POSIX_SPIN_LOCKS, unlimited] */
#define _SC_REGEXP                       155 /* [== _POSIX_REGEXP, unlimited] */
#define _SC_REGEX_VERSION                156 /* [== unlimited] */
#define _SC_SHELL                        157 /* [== _POSIX_SHELL, unlimited] */
#define _SC_SIGNALS                      158 /* [== _POSIX_SIGNALS, unlimited] */
#define _SC_SPAWN                        159 /* [== _POSIX_SPAWN, unlimited] */
#define _SC_SPORADIC_SERVER              160 /* [== _POSIX_SPORADIC_SERVER, unlimited] */
#define _SC_THREAD_SPORADIC_SERVER       161 /* [== _POSIX_THREAD_SPORADIC_SERVER, unlimited] */
#define _SC_SYSTEM_DATABASE              162 /* [== _POSIX_SYSTEM_DATABASE, unlimited] */
#define _SC_SYSTEM_DATABASE_R            163 /* [== _POSIX_SYSTEM_DATABASE_R, unlimited] */
#define _SC_TIMEOUTS                     164 /* [== _POSIX_TIMEOUTS, unlimited] */
#define _SC_TYPED_MEMORY_OBJECTS         165 /* [== _POSIX_TYPED_MEMORY_OBJECTS, unlimited] */
#define _SC_USER_GROUPS                  166 /* [== _POSIX_USER_GROUPS, unlimited] */
#define _SC_USER_GROUPS_R                167 /* [== _POSIX_USER_GROUPS_R, unlimited] */
#define _SC_2_PBS                        168 /* [== _POSIX2_PBS, unlimited] */
#define _SC_2_PBS_ACCOUNTING             169 /* [== _POSIX2_PBS_ACCOUNTING, unlimited] */
#define _SC_2_PBS_LOCATE                 170 /* [== _POSIX2_PBS_LOCATE, unlimited] */
#define _SC_2_PBS_MESSAGE                171 /* [== _POSIX2_PBS_MESSAGE, unlimited] */
#define _SC_2_PBS_TRACK                  172 /* [== _POSIX2_PBS_TRACK, unlimited] */
#define _SC_SYMLOOP_MAX                  173 /* [== custom, MAXSYMLINKS, SYMLOOP_MAX] */
#define _SC_STREAMS                      174 /* [== unlimited] */
#define _SC_2_PBS_CHECKPOINT             175 /* [== _POSIX2_PBS_CHECKPOINT, unlimited] */
#define _SC_V6_ILP32_OFF32               176 /* ... */
#define _SC_V6_ILP32_OFFBIG              177 /* ... */
#define _SC_V6_LP64_OFF64                178 /* ... */
#define _SC_V6_LPBIG_OFFBIG              179 /* ... */
#define _SC_HOST_NAME_MAX                180 /* [== HOST_NAME_MAX, _POSIX_HOST_NAME_MAX] */
#define _SC_TRACE                        181 /* [== _POSIX_TRACE, unlimited] */
#define _SC_TRACE_EVENT_FILTER           182 /* [== _POSIX_TRACE_EVENT_FILTER] */
#define _SC_TRACE_INHERIT                183 /* [== _POSIX_TRACE_INHERIT] */
#define _SC_TRACE_LOG                    184 /* [== _POSIX_TRACE_LOG] */
#define _SC_LEVEL1_ICACHE_SIZE           185 /* [== 0] */
#define _SC_LEVEL1_ICACHE_ASSOC          186 /* [== 0] */
#define _SC_LEVEL1_ICACHE_LINESIZE       187 /* [== 0] */
#define _SC_LEVEL1_DCACHE_SIZE           188 /* [== 0] */
#define _SC_LEVEL1_DCACHE_ASSOC          189 /* [== 0] */
#define _SC_LEVEL1_DCACHE_LINESIZE       190 /* [== 0] */
#define _SC_LEVEL2_CACHE_SIZE            191 /* [== 0] */
#define _SC_LEVEL2_CACHE_ASSOC           192 /* [== 0] */
#define _SC_LEVEL2_CACHE_LINESIZE        193 /* [== 0] */
#define _SC_LEVEL3_CACHE_SIZE            194 /* [== 0] */
#define _SC_LEVEL3_CACHE_ASSOC           195 /* [== 0] */
#define _SC_LEVEL3_CACHE_LINESIZE        196 /* [== 0] */
#define _SC_LEVEL4_CACHE_SIZE            197 /* [== 0] */
#define _SC_LEVEL4_CACHE_ASSOC           198 /* [== 0] */
#define _SC_LEVEL4_CACHE_LINESIZE        199 /* [== 0] */
#define _SC_IPV6                         235 /* [== _POSIX_IPV6, unlimited] */
#define _SC_RAW_SOCKETS                  236 /* [== _POSIX_RAW_SOCKETS, unlimited] */
#define _SC_V7_ILP32_OFF32               237 /* ... */
#define _SC_V7_ILP32_OFFBIG              238 /* ... */
#define _SC_V7_LP64_OFF64                239 /* ... */
#define _SC_V7_LPBIG_OFFBIG              240 /* ... */
#define _SC_SS_REPL_MAX                  241 /* [== _POSIX_SS_REPL_MAX, unlimited] */
#define _SC_TRACE_EVENT_NAME_MAX         242 /* [== unlimited] */
#define _SC_TRACE_NAME_MAX               243 /* [== unlimited] */
#define _SC_TRACE_SYS_MAX                244 /* [== unlimited] */
#define _SC_TRACE_USER_EVENT_MAX         245 /* [== unlimited] */
#define _SC_XOPEN_STREAMS                246 /* [== unlimited] */
#define _SC_THREAD_ROBUST_PRIO_INHERIT   247 /* [== _POSIX_THREAD_ROBUST_PRIO_INHERIT, unlimited] */
#define _SC_THREAD_ROBUST_PRIO_PROTECT   248 /* [== _POSIX_THREAD_ROBUST_PRIO_PROTECT, unlimited] */
#ifdef __USE_KOS
#define _SC_COUNT                        249
#endif /* __USE_KOS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Arguments accepted by `confstr()'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	_CS_PATH,
	_CS_V6_WIDTH_RESTRICTED_ENVS,
	_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS = _CS_V6_WIDTH_RESTRICTED_ENVS,
	_CS_GNU_LIBC_VERSION,
	_CS_GNU_LIBPTHREAD_VERSION,
	_CS_V5_WIDTH_RESTRICTED_ENVS,
	_CS_POSIX_V5_WIDTH_RESTRICTED_ENVS = _CS_V5_WIDTH_RESTRICTED_ENVS,
	_CS_V7_WIDTH_RESTRICTED_ENVS,
	_CS_POSIX_V7_WIDTH_RESTRICTED_ENVS = _CS_V7_WIDTH_RESTRICTED_ENVS,
	_CS_LFS_CFLAGS = 1000,
	_CS_LFS_LDFLAGS,
	_CS_LFS_LIBS,
	_CS_LFS_LINTFLAGS,
	_CS_LFS64_CFLAGS,
	_CS_LFS64_LDFLAGS,
	_CS_LFS64_LIBS,
	_CS_LFS64_LINTFLAGS,
	_CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
	_CS_XBS5_ILP32_OFF32_LDFLAGS,
	_CS_XBS5_ILP32_OFF32_LIBS,
	_CS_XBS5_ILP32_OFF32_LINTFLAGS,
	_CS_XBS5_ILP32_OFFBIG_CFLAGS,
	_CS_XBS5_ILP32_OFFBIG_LDFLAGS,
	_CS_XBS5_ILP32_OFFBIG_LIBS,
	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
	_CS_XBS5_LP64_OFF64_CFLAGS,
	_CS_XBS5_LP64_OFF64_LDFLAGS,
	_CS_XBS5_LP64_OFF64_LIBS,
	_CS_XBS5_LP64_OFF64_LINTFLAGS,
	_CS_XBS5_LPBIG_OFFBIG_CFLAGS,
	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
	_CS_XBS5_LPBIG_OFFBIG_LIBS,
	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
	_CS_POSIX_V6_ILP32_OFF32_CFLAGS,
	_CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
	_CS_POSIX_V6_ILP32_OFF32_LIBS,
	_CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
	_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
	_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
	_CS_POSIX_V6_ILP32_OFFBIG_LIBS,
	_CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
	_CS_POSIX_V6_LP64_OFF64_CFLAGS,
	_CS_POSIX_V6_LP64_OFF64_LDFLAGS,
	_CS_POSIX_V6_LP64_OFF64_LIBS,
	_CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
	_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
	_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
	_CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
	_CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
	_CS_POSIX_V7_ILP32_OFF32_CFLAGS,
	_CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
	_CS_POSIX_V7_ILP32_OFF32_LIBS,
	_CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
	_CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
	_CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
	_CS_POSIX_V7_ILP32_OFFBIG_LIBS,
	_CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
	_CS_POSIX_V7_LP64_OFF64_CFLAGS,
	_CS_POSIX_V7_LP64_OFF64_LDFLAGS,
	_CS_POSIX_V7_LP64_OFF64_LIBS,
	_CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
	_CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
	_CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
	_CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
	_CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
	_CS_V6_ENV,
	_CS_V7_ENV,
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define _CS_PATH                            _CS_PATH
#define _CS_V6_WIDTH_RESTRICTED_ENVS        _CS_V6_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS  _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS
#define _CS_GNU_LIBC_VERSION                _CS_GNU_LIBC_VERSION
#define _CS_GNU_LIBPTHREAD_VERSION          _CS_GNU_LIBPTHREAD_VERSION
#define _CS_V5_WIDTH_RESTRICTED_ENVS        _CS_V5_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS  _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS
#define _CS_V7_WIDTH_RESTRICTED_ENVS        _CS_V7_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS  _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS
#define _CS_LFS_CFLAGS                      _CS_LFS_CFLAGS
#define _CS_LFS_LDFLAGS                     _CS_LFS_LDFLAGS
#define _CS_LFS_LIBS                        _CS_LFS_LIBS
#define _CS_LFS_LINTFLAGS                   _CS_LFS_LINTFLAGS
#define _CS_LFS64_CFLAGS                    _CS_LFS64_CFLAGS
#define _CS_LFS64_LDFLAGS                   _CS_LFS64_LDFLAGS
#define _CS_LFS64_LIBS                      _CS_LFS64_LIBS
#define _CS_LFS64_LINTFLAGS                 _CS_LFS64_LINTFLAGS
#define _CS_XBS5_ILP32_OFF32_CFLAGS         _CS_XBS5_ILP32_OFF32_CFLAGS
#define _CS_XBS5_ILP32_OFF32_LDFLAGS        _CS_XBS5_ILP32_OFF32_LDFLAGS
#define _CS_XBS5_ILP32_OFF32_LIBS           _CS_XBS5_ILP32_OFF32_LIBS
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS      _CS_XBS5_ILP32_OFF32_LINTFLAGS
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS        _CS_XBS5_ILP32_OFFBIG_CFLAGS
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS       _CS_XBS5_ILP32_OFFBIG_LDFLAGS
#define _CS_XBS5_ILP32_OFFBIG_LIBS          _CS_XBS5_ILP32_OFFBIG_LIBS
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS     _CS_XBS5_ILP32_OFFBIG_LINTFLAGS
#define _CS_XBS5_LP64_OFF64_CFLAGS          _CS_XBS5_LP64_OFF64_CFLAGS
#define _CS_XBS5_LP64_OFF64_LDFLAGS         _CS_XBS5_LP64_OFF64_LDFLAGS
#define _CS_XBS5_LP64_OFF64_LIBS            _CS_XBS5_LP64_OFF64_LIBS
#define _CS_XBS5_LP64_OFF64_LINTFLAGS       _CS_XBS5_LP64_OFF64_LINTFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS        _CS_XBS5_LPBIG_OFFBIG_CFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS       _CS_XBS5_LPBIG_OFFBIG_LDFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_LIBS          _CS_XBS5_LPBIG_OFFBIG_LIBS
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS     _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS     _CS_POSIX_V6_ILP32_OFF32_CFLAGS
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS
#define _CS_POSIX_V6_ILP32_OFF32_LIBS       _CS_POSIX_V6_ILP32_OFF32_LIBS
#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS  _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS   _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS      _CS_POSIX_V6_ILP32_OFFBIG_LIBS
#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS      _CS_POSIX_V6_LP64_OFF64_CFLAGS
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS     _CS_POSIX_V6_LP64_OFF64_LDFLAGS
#define _CS_POSIX_V6_LP64_OFF64_LIBS        _CS_POSIX_V6_LP64_OFF64_LIBS
#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS   _CS_POSIX_V6_LP64_OFF64_LINTFLAGS
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS   _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS      _CS_POSIX_V6_LPBIG_OFFBIG_LIBS
#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS
#define _CS_POSIX_V7_ILP32_OFF32_CFLAGS     _CS_POSIX_V7_ILP32_OFF32_CFLAGS
#define _CS_POSIX_V7_ILP32_OFF32_LDFLAGS    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS
#define _CS_POSIX_V7_ILP32_OFF32_LIBS       _CS_POSIX_V7_ILP32_OFF32_LIBS
#define _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS  _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS
#define _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS
#define _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS   _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS
#define _CS_POSIX_V7_ILP32_OFFBIG_LIBS      _CS_POSIX_V7_ILP32_OFFBIG_LIBS
#define _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS
#define _CS_POSIX_V7_LP64_OFF64_CFLAGS      _CS_POSIX_V7_LP64_OFF64_CFLAGS
#define _CS_POSIX_V7_LP64_OFF64_LDFLAGS     _CS_POSIX_V7_LP64_OFF64_LDFLAGS
#define _CS_POSIX_V7_LP64_OFF64_LIBS        _CS_POSIX_V7_LP64_OFF64_LIBS
#define _CS_POSIX_V7_LP64_OFF64_LINTFLAGS   _CS_POSIX_V7_LP64_OFF64_LINTFLAGS
#define _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS
#define _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS   _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS
#define _CS_POSIX_V7_LPBIG_OFFBIG_LIBS      _CS_POSIX_V7_LPBIG_OFFBIG_LIBS
#define _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS
#define _CS_V6_ENV                          _CS_V6_ENV
#define _CS_V7_ENV                          _CS_V7_ENV
#else /* __COMPILER_PREFERR_ENUMS */
#define _CS_PATH                            0
#define _CS_V6_WIDTH_RESTRICTED_ENVS        1
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS  1
#define _CS_GNU_LIBC_VERSION                2
#define _CS_GNU_LIBPTHREAD_VERSION          3
#define _CS_V5_WIDTH_RESTRICTED_ENVS        4
#define _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS  4
#define _CS_V7_WIDTH_RESTRICTED_ENVS        5
#define _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS  5
#define _CS_LFS_CFLAGS                      1000
#define _CS_LFS_LDFLAGS                     1001
#define _CS_LFS_LIBS                        1002
#define _CS_LFS_LINTFLAGS                   1003
#define _CS_LFS64_CFLAGS                    1004
#define _CS_LFS64_LDFLAGS                   1005
#define _CS_LFS64_LIBS                      1006
#define _CS_LFS64_LINTFLAGS                 1007
#define _CS_XBS5_ILP32_OFF32_CFLAGS         1100
#define _CS_XBS5_ILP32_OFF32_LDFLAGS        1101
#define _CS_XBS5_ILP32_OFF32_LIBS           1102
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS      1103
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS        1104
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS       1105
#define _CS_XBS5_ILP32_OFFBIG_LIBS          1106
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS     1107
#define _CS_XBS5_LP64_OFF64_CFLAGS          1108
#define _CS_XBS5_LP64_OFF64_LDFLAGS         1109
#define _CS_XBS5_LP64_OFF64_LIBS            1110
#define _CS_XBS5_LP64_OFF64_LINTFLAGS       1111
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS        1112
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS       1113
#define _CS_XBS5_LPBIG_OFFBIG_LIBS          1114
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS     1115
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS     1116
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS    1117
#define _CS_POSIX_V6_ILP32_OFF32_LIBS       1118
#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS  1119
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS    1120
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS   1121
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS      1122
#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS 1123
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS      1124
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS     1125
#define _CS_POSIX_V6_LP64_OFF64_LIBS        1126
#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS   1127
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS    1128
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS   1129
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS      1130
#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS 1131
#define _CS_POSIX_V7_ILP32_OFF32_CFLAGS     1132
#define _CS_POSIX_V7_ILP32_OFF32_LDFLAGS    1133
#define _CS_POSIX_V7_ILP32_OFF32_LIBS       1134
#define _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS  1135
#define _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS    1136
#define _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS   1137
#define _CS_POSIX_V7_ILP32_OFFBIG_LIBS      1138
#define _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS 1139
#define _CS_POSIX_V7_LP64_OFF64_CFLAGS      1140
#define _CS_POSIX_V7_LP64_OFF64_LDFLAGS     1141
#define _CS_POSIX_V7_LP64_OFF64_LIBS        1142
#define _CS_POSIX_V7_LP64_OFF64_LINTFLAGS   1143
#define _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS    1144
#define _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS   1145
#define _CS_POSIX_V7_LPBIG_OFFBIG_LIBS      1146
#define _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS 1147
#define _CS_V6_ENV                          1148
#define _CS_V7_ENV                          1149
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#endif /* !_ASM_CRT_CONFNAME_H */
