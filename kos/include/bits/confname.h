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
#ifndef _BITS_CONFNAME_H
#define _BITS_CONFNAME_H 1

#include <__stdinc.h>

/* Arguments accepted by `[f]pathconf()'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	_PC_LINK_MAX,
	_PC_MAX_CANON,
	_PC_MAX_INPUT,
	_PC_NAME_MAX,
	_PC_PATH_MAX,
	_PC_PIPE_BUF,
	_PC_CHOWN_RESTRICTED,
	_PC_NO_TRUNC,
	_PC_VDISABLE,
	_PC_SYNC_IO,
	_PC_ASYNC_IO,
	_PC_PRIO_IO,
	_PC_SOCK_MAXBUF,
	_PC_FILESIZEBITS,
	_PC_REC_INCR_XFER_SIZE,
	_PC_REC_MAX_XFER_SIZE,
	_PC_REC_MIN_XFER_SIZE,
	_PC_REC_XFER_ALIGN,
	_PC_ALLOC_SIZE_MIN,
	_PC_SYMLINK_MAX,
	_PC_2_SYMLINKS
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define _PC_LINK_MAX           _PC_LINK_MAX
#define _PC_MAX_CANON          _PC_MAX_CANON
#define _PC_MAX_INPUT          _PC_MAX_INPUT
#define _PC_NAME_MAX           _PC_NAME_MAX
#define _PC_PATH_MAX           _PC_PATH_MAX
#define _PC_PIPE_BUF           _PC_PIPE_BUF
#define _PC_CHOWN_RESTRICTED   _PC_CHOWN_RESTRICTED
#define _PC_NO_TRUNC           _PC_NO_TRUNC
#define _PC_VDISABLE           _PC_VDISABLE
#define _PC_SYNC_IO            _PC_SYNC_IO
#define _PC_ASYNC_IO           _PC_ASYNC_IO
#define _PC_PRIO_IO            _PC_PRIO_IO
#define _PC_SOCK_MAXBUF        _PC_SOCK_MAXBUF
#define _PC_FILESIZEBITS       _PC_FILESIZEBITS
#define _PC_REC_INCR_XFER_SIZE _PC_REC_INCR_XFER_SIZE
#define _PC_REC_MAX_XFER_SIZE  _PC_REC_MAX_XFER_SIZE
#define _PC_REC_MIN_XFER_SIZE  _PC_REC_MIN_XFER_SIZE
#define _PC_REC_XFER_ALIGN     _PC_REC_XFER_ALIGN
#define _PC_ALLOC_SIZE_MIN     _PC_ALLOC_SIZE_MIN
#define _PC_SYMLINK_MAX        _PC_SYMLINK_MAX
#define _PC_2_SYMLINKS         _PC_2_SYMLINKS
#else /* __COMPILER_PREFERR_ENUMS */
#define _PC_LINK_MAX           0
#define _PC_MAX_CANON          1
#define _PC_MAX_INPUT          2
#define _PC_NAME_MAX           3
#define _PC_PATH_MAX           4
#define _PC_PIPE_BUF           5
#define _PC_CHOWN_RESTRICTED   6
#define _PC_NO_TRUNC           7
#define _PC_VDISABLE           8
#define _PC_SYNC_IO            9
#define _PC_ASYNC_IO           10
#define _PC_PRIO_IO            11
#define _PC_SOCK_MAXBUF        12
#define _PC_FILESIZEBITS       13
#define _PC_REC_INCR_XFER_SIZE 14
#define _PC_REC_MAX_XFER_SIZE  15
#define _PC_REC_MIN_XFER_SIZE  16
#define _PC_REC_XFER_ALIGN     17
#define _PC_ALLOC_SIZE_MIN     18
#define _PC_SYMLINK_MAX        19
#define _PC_2_SYMLINKS         20
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Arguments accepted by `sysconf()'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	_SC_ARG_MAX,
	_SC_CHILD_MAX,
	_SC_CLK_TCK,
	_SC_NGROUPS_MAX,
	_SC_OPEN_MAX,
	_SC_STREAM_MAX,
	_SC_TZNAME_MAX,
	_SC_JOB_CONTROL,
	_SC_SAVED_IDS,
	_SC_REALTIME_SIGNALS,
	_SC_PRIORITY_SCHEDULING,
	_SC_TIMERS,
	_SC_ASYNCHRONOUS_IO,
	_SC_PRIORITIZED_IO,
	_SC_SYNCHRONIZED_IO,
	_SC_FSYNC,
	_SC_MAPPED_FILES,
	_SC_MEMLOCK,
	_SC_MEMLOCK_RANGE,
	_SC_MEMORY_PROTECTION,
	_SC_MESSAGE_PASSING,
	_SC_SEMAPHORES,
	_SC_SHARED_MEMORY_OBJECTS,
	_SC_AIO_LISTIO_MAX,
	_SC_AIO_MAX,
	_SC_AIO_PRIO_DELTA_MAX,
	_SC_DELAYTIMER_MAX,
	_SC_MQ_OPEN_MAX,
	_SC_MQ_PRIO_MAX,
	_SC_VERSION,
	_SC_PAGESIZE,
	_SC_PAGE_SIZE = _SC_PAGESIZE,
	_SC_RTSIG_MAX,
	_SC_SEM_NSEMS_MAX,
	_SC_SEM_VALUE_MAX,
	_SC_SIGQUEUE_MAX,
	_SC_TIMER_MAX,
	_SC_BC_BASE_MAX,
	_SC_BC_DIM_MAX,
	_SC_BC_SCALE_MAX,
	_SC_BC_STRING_MAX,
	_SC_COLL_WEIGHTS_MAX,
	_SC_EQUIV_CLASS_MAX,
	_SC_EXPR_NEST_MAX,
	_SC_LINE_MAX,
	_SC_RE_DUP_MAX,
	_SC_CHARCLASS_NAME_MAX,
	_SC_2_VERSION,
	_SC_2_C_BIND,
	_SC_2_C_DEV,
	_SC_2_FORT_DEV,
	_SC_2_FORT_RUN,
	_SC_2_SW_DEV,
	_SC_2_LOCALEDEF,
	_SC_PII,
	_SC_PII_XTI,
	_SC_PII_SOCKET,
	_SC_PII_INTERNET,
	_SC_PII_OSI,
	_SC_POLL,
	_SC_SELECT,
	_SC_UIO_MAXIOV,
	_SC_IOV_MAX = _SC_UIO_MAXIOV,
	_SC_PII_INTERNET_STREAM,
	_SC_PII_INTERNET_DGRAM,
	_SC_PII_OSI_COTS,
	_SC_PII_OSI_CLTS,
	_SC_PII_OSI_M,
	_SC_T_IOV_MAX,
	_SC_THREADS,
	_SC_THREAD_SAFE_FUNCTIONS,
	_SC_GETGR_R_SIZE_MAX,
	_SC_GETPW_R_SIZE_MAX,
	_SC_LOGIN_NAME_MAX,
	_SC_TTY_NAME_MAX,
	_SC_THREAD_DESTRUCTOR_ITERATIONS,
	_SC_THREAD_KEYS_MAX,
	_SC_THREAD_STACK_MIN,
	_SC_THREAD_THREADS_MAX,
	_SC_THREAD_ATTR_STACKADDR,
	_SC_THREAD_ATTR_STACKSIZE,
	_SC_THREAD_PRIORITY_SCHEDULING,
	_SC_THREAD_PRIO_INHERIT,
	_SC_THREAD_PRIO_PROTECT,
	_SC_THREAD_PROCESS_SHARED,
	_SC_NPROCESSORS_CONF,
	_SC_NPROCESSORS_ONLN,
	_SC_NPROC_ONLN = _SC_NPROCESSORS_ONLN,
	_SC_PHYS_PAGES,
	_SC_AVPHYS_PAGES,
	_SC_ATEXIT_MAX,
	_SC_PASS_MAX,
	_SC_XOPEN_VERSION,
	_SC_XOPEN_XCU_VERSION,
	_SC_XOPEN_UNIX,
	_SC_XOPEN_CRYPT,
	_SC_XOPEN_ENH_I18N,
	_SC_XOPEN_SHM,
	_SC_2_CHAR_TERM,
	_SC_2_C_VERSION,
	_SC_2_UPE,
	_SC_XOPEN_XPG2,
	_SC_XOPEN_XPG3,
	_SC_XOPEN_XPG4,
	_SC_CHAR_BIT,
	_SC_CHAR_MAX,
	_SC_CHAR_MIN,
	_SC_INT_MAX,
	_SC_INT_MIN,
	_SC_LONG_BIT,
	_SC_WORD_BIT,
	_SC_MB_LEN_MAX,
	_SC_NZERO,
	_SC_SSIZE_MAX,
	_SC_SCHAR_MAX,
	_SC_SCHAR_MIN,
	_SC_SHRT_MAX,
	_SC_SHRT_MIN,
	_SC_UCHAR_MAX,
	_SC_UINT_MAX,
	_SC_ULONG_MAX,
	_SC_USHRT_MAX,
	_SC_NL_ARGMAX,
	_SC_NL_LANGMAX,
	_SC_NL_MSGMAX,
	_SC_NL_NMAX,
	_SC_NL_SETMAX,
	_SC_NL_TEXTMAX,
	_SC_XBS5_ILP32_OFF32,
	_SC_XBS5_ILP32_OFFBIG,
	_SC_XBS5_LP64_OFF64,
	_SC_XBS5_LPBIG_OFFBIG,
	_SC_XOPEN_LEGACY,
	_SC_XOPEN_REALTIME,
	_SC_XOPEN_REALTIME_THREADS,
	_SC_ADVISORY_INFO,
	_SC_BARRIERS,
	_SC_BASE,
	_SC_C_LANG_SUPPORT,
	_SC_C_LANG_SUPPORT_R,
	_SC_CLOCK_SELECTION,
	_SC_CPUTIME,
	_SC_THREAD_CPUTIME,
	_SC_DEVICE_IO,
	_SC_DEVICE_SPECIFIC,
	_SC_DEVICE_SPECIFIC_R,
	_SC_FD_MGMT,
	_SC_FIFO,
	_SC_PIPE,
	_SC_FILE_ATTRIBUTES,
	_SC_FILE_LOCKING,
	_SC_FILE_SYSTEM,
	_SC_MONOTONIC_CLOCK,
	_SC_MULTI_PROCESS,
	_SC_SINGLE_PROCESS,
	_SC_NETWORKING,
	_SC_READER_WRITER_LOCKS,
	_SC_SPIN_LOCKS,
	_SC_REGEXP,
	_SC_REGEX_VERSION,
	_SC_SHELL,
	_SC_SIGNALS,
	_SC_SPAWN,
	_SC_SPORADIC_SERVER,
	_SC_THREAD_SPORADIC_SERVER,
	_SC_SYSTEM_DATABASE,
	_SC_SYSTEM_DATABASE_R,
	_SC_TIMEOUTS,
	_SC_TYPED_MEMORY_OBJECTS,
	_SC_USER_GROUPS,
	_SC_USER_GROUPS_R,
	_SC_2_PBS,
	_SC_2_PBS_ACCOUNTING,
	_SC_2_PBS_LOCATE,
	_SC_2_PBS_MESSAGE,
	_SC_2_PBS_TRACK,
	_SC_SYMLOOP_MAX,
	_SC_STREAMS,
	_SC_2_PBS_CHECKPOINT,
	_SC_V6_ILP32_OFF32,
	_SC_V6_ILP32_OFFBIG,
	_SC_V6_LP64_OFF64,
	_SC_V6_LPBIG_OFFBIG,
	_SC_HOST_NAME_MAX,
	_SC_TRACE,
	_SC_TRACE_EVENT_FILTER,
	_SC_TRACE_INHERIT,
	_SC_TRACE_LOG,
	_SC_LEVEL1_ICACHE_SIZE,
	_SC_LEVEL1_ICACHE_ASSOC,
	_SC_LEVEL1_ICACHE_LINESIZE,
	_SC_LEVEL1_DCACHE_SIZE,
	_SC_LEVEL1_DCACHE_ASSOC,
	_SC_LEVEL1_DCACHE_LINESIZE,
	_SC_LEVEL2_CACHE_SIZE,
	_SC_LEVEL2_CACHE_ASSOC,
	_SC_LEVEL2_CACHE_LINESIZE,
	_SC_LEVEL3_CACHE_SIZE,
	_SC_LEVEL3_CACHE_ASSOC,
	_SC_LEVEL3_CACHE_LINESIZE,
	_SC_LEVEL4_CACHE_SIZE,
	_SC_LEVEL4_CACHE_ASSOC,
	_SC_LEVEL4_CACHE_LINESIZE,
	_SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
	_SC_RAW_SOCKETS,
	_SC_V7_ILP32_OFF32,
	_SC_V7_ILP32_OFFBIG,
	_SC_V7_LP64_OFF64,
	_SC_V7_LPBIG_OFFBIG,
	_SC_SS_REPL_MAX,
	_SC_TRACE_EVENT_NAME_MAX,
	_SC_TRACE_NAME_MAX,
	_SC_TRACE_SYS_MAX,
	_SC_TRACE_USER_EVENT_MAX,
	_SC_XOPEN_STREAMS,
	_SC_THREAD_ROBUST_PRIO_INHERIT,
	_SC_THREAD_ROBUST_PRIO_PROTECT,
#ifdef __USE_KOS
	_SC_COUNT
#endif /* __USE_KOS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define _SC_ARG_MAX                      _SC_ARG_MAX
#define _SC_CHILD_MAX                    _SC_CHILD_MAX
#define _SC_CLK_TCK                      _SC_CLK_TCK
#define _SC_NGROUPS_MAX                  _SC_NGROUPS_MAX
#define _SC_OPEN_MAX                     _SC_OPEN_MAX
#define _SC_STREAM_MAX                   _SC_STREAM_MAX
#define _SC_TZNAME_MAX                   _SC_TZNAME_MAX
#define _SC_JOB_CONTROL                  _SC_JOB_CONTROL
#define _SC_SAVED_IDS                    _SC_SAVED_IDS
#define _SC_REALTIME_SIGNALS             _SC_REALTIME_SIGNALS
#define _SC_PRIORITY_SCHEDULING          _SC_PRIORITY_SCHEDULING
#define _SC_TIMERS                       _SC_TIMERS
#define _SC_ASYNCHRONOUS_IO              _SC_ASYNCHRONOUS_IO
#define _SC_PRIORITIZED_IO               _SC_PRIORITIZED_IO
#define _SC_SYNCHRONIZED_IO              _SC_SYNCHRONIZED_IO
#define _SC_FSYNC                        _SC_FSYNC
#define _SC_MAPPED_FILES                 _SC_MAPPED_FILES
#define _SC_MEMLOCK                      _SC_MEMLOCK
#define _SC_MEMLOCK_RANGE                _SC_MEMLOCK_RANGE
#define _SC_MEMORY_PROTECTION            _SC_MEMORY_PROTECTION
#define _SC_MESSAGE_PASSING              _SC_MESSAGE_PASSING
#define _SC_SEMAPHORES                   _SC_SEMAPHORES
#define _SC_SHARED_MEMORY_OBJECTS        _SC_SHARED_MEMORY_OBJECTS
#define _SC_AIO_LISTIO_MAX               _SC_AIO_LISTIO_MAX
#define _SC_AIO_MAX                      _SC_AIO_MAX
#define _SC_AIO_PRIO_DELTA_MAX           _SC_AIO_PRIO_DELTA_MAX
#define _SC_DELAYTIMER_MAX               _SC_DELAYTIMER_MAX
#define _SC_MQ_OPEN_MAX                  _SC_MQ_OPEN_MAX
#define _SC_MQ_PRIO_MAX                  _SC_MQ_PRIO_MAX
#define _SC_VERSION                      _SC_VERSION
#define _SC_PAGESIZE                     _SC_PAGESIZE
#define _SC_PAGE_SIZE                    _SC_PAGE_SIZE
#define _SC_RTSIG_MAX                    _SC_RTSIG_MAX
#define _SC_SEM_NSEMS_MAX                _SC_SEM_NSEMS_MAX
#define _SC_SEM_VALUE_MAX                _SC_SEM_VALUE_MAX
#define _SC_SIGQUEUE_MAX                 _SC_SIGQUEUE_MAX
#define _SC_TIMER_MAX                    _SC_TIMER_MAX
#define _SC_BC_BASE_MAX                  _SC_BC_BASE_MAX
#define _SC_BC_DIM_MAX                   _SC_BC_DIM_MAX
#define _SC_BC_SCALE_MAX                 _SC_BC_SCALE_MAX
#define _SC_BC_STRING_MAX                _SC_BC_STRING_MAX
#define _SC_COLL_WEIGHTS_MAX             _SC_COLL_WEIGHTS_MAX
#define _SC_EQUIV_CLASS_MAX              _SC_EQUIV_CLASS_MAX
#define _SC_EXPR_NEST_MAX                _SC_EXPR_NEST_MAX
#define _SC_LINE_MAX                     _SC_LINE_MAX
#define _SC_RE_DUP_MAX                   _SC_RE_DUP_MAX
#define _SC_CHARCLASS_NAME_MAX           _SC_CHARCLASS_NAME_MAX
#define _SC_2_VERSION                    _SC_2_VERSION
#define _SC_2_C_BIND                     _SC_2_C_BIND
#define _SC_2_C_DEV                      _SC_2_C_DEV
#define _SC_2_FORT_DEV                   _SC_2_FORT_DEV
#define _SC_2_FORT_RUN                   _SC_2_FORT_RUN
#define _SC_2_SW_DEV                     _SC_2_SW_DEV
#define _SC_2_LOCALEDEF                  _SC_2_LOCALEDEF
#define _SC_PII                          _SC_PII
#define _SC_PII_XTI                      _SC_PII_XTI
#define _SC_PII_SOCKET                   _SC_PII_SOCKET
#define _SC_PII_INTERNET                 _SC_PII_INTERNET
#define _SC_PII_OSI                      _SC_PII_OSI
#define _SC_POLL                         _SC_POLL
#define _SC_SELECT                       _SC_SELECT
#define _SC_UIO_MAXIOV                   _SC_UIO_MAXIOV
#define _SC_IOV_MAX                      _SC_IOV_MAX
#define _SC_PII_INTERNET_STREAM          _SC_PII_INTERNET_STREAM
#define _SC_PII_INTERNET_DGRAM           _SC_PII_INTERNET_DGRAM
#define _SC_PII_OSI_COTS                 _SC_PII_OSI_COTS
#define _SC_PII_OSI_CLTS                 _SC_PII_OSI_CLTS
#define _SC_PII_OSI_M                    _SC_PII_OSI_M
#define _SC_T_IOV_MAX                    _SC_T_IOV_MAX
#define _SC_THREADS                      _SC_THREADS
#define _SC_THREAD_SAFE_FUNCTIONS        _SC_THREAD_SAFE_FUNCTIONS
#define _SC_GETGR_R_SIZE_MAX             _SC_GETGR_R_SIZE_MAX
#define _SC_GETPW_R_SIZE_MAX             _SC_GETPW_R_SIZE_MAX
#define _SC_LOGIN_NAME_MAX               _SC_LOGIN_NAME_MAX
#define _SC_TTY_NAME_MAX                 _SC_TTY_NAME_MAX
#define _SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS
#define _SC_THREAD_KEYS_MAX              _SC_THREAD_KEYS_MAX
#define _SC_THREAD_STACK_MIN             _SC_THREAD_STACK_MIN
#define _SC_THREAD_THREADS_MAX           _SC_THREAD_THREADS_MAX
#define _SC_THREAD_ATTR_STACKADDR        _SC_THREAD_ATTR_STACKADDR
#define _SC_THREAD_ATTR_STACKSIZE        _SC_THREAD_ATTR_STACKSIZE
#define _SC_THREAD_PRIORITY_SCHEDULING   _SC_THREAD_PRIORITY_SCHEDULING
#define _SC_THREAD_PRIO_INHERIT          _SC_THREAD_PRIO_INHERIT
#define _SC_THREAD_PRIO_PROTECT          _SC_THREAD_PRIO_PROTECT
#define _SC_THREAD_PROCESS_SHARED        _SC_THREAD_PROCESS_SHARED
#define _SC_NPROCESSORS_CONF             _SC_NPROCESSORS_CONF
#define _SC_NPROCESSORS_ONLN             _SC_NPROCESSORS_ONLN
#define _SC_NPROC_ONLN                   _SC_NPROC_ONLN
#define _SC_PHYS_PAGES                   _SC_PHYS_PAGES
#define _SC_AVPHYS_PAGES                 _SC_AVPHYS_PAGES
#define _SC_ATEXIT_MAX                   _SC_ATEXIT_MAX
#define _SC_PASS_MAX                     _SC_PASS_MAX
#define _SC_XOPEN_VERSION                _SC_XOPEN_VERSION
#define _SC_XOPEN_XCU_VERSION            _SC_XOPEN_XCU_VERSION
#define _SC_XOPEN_UNIX                   _SC_XOPEN_UNIX
#define _SC_XOPEN_CRYPT                  _SC_XOPEN_CRYPT
#define _SC_XOPEN_ENH_I18N               _SC_XOPEN_ENH_I18N
#define _SC_XOPEN_SHM                    _SC_XOPEN_SHM
#define _SC_2_CHAR_TERM                  _SC_2_CHAR_TERM
#define _SC_2_C_VERSION                  _SC_2_C_VERSION
#define _SC_2_UPE                        _SC_2_UPE
#define _SC_XOPEN_XPG2                   _SC_XOPEN_XPG2
#define _SC_XOPEN_XPG3                   _SC_XOPEN_XPG3
#define _SC_XOPEN_XPG4                   _SC_XOPEN_XPG4
#define _SC_CHAR_BIT                     _SC_CHAR_BIT
#define _SC_CHAR_MAX                     _SC_CHAR_MAX
#define _SC_CHAR_MIN                     _SC_CHAR_MIN
#define _SC_INT_MAX                      _SC_INT_MAX
#define _SC_INT_MIN                      _SC_INT_MIN
#define _SC_LONG_BIT                     _SC_LONG_BIT
#define _SC_WORD_BIT                     _SC_WORD_BIT
#define _SC_MB_LEN_MAX                   _SC_MB_LEN_MAX
#define _SC_NZERO                        _SC_NZERO
#define _SC_SSIZE_MAX                    _SC_SSIZE_MAX
#define _SC_SCHAR_MAX                    _SC_SCHAR_MAX
#define _SC_SCHAR_MIN                    _SC_SCHAR_MIN
#define _SC_SHRT_MAX                     _SC_SHRT_MAX
#define _SC_SHRT_MIN                     _SC_SHRT_MIN
#define _SC_UCHAR_MAX                    _SC_UCHAR_MAX
#define _SC_UINT_MAX                     _SC_UINT_MAX
#define _SC_ULONG_MAX                    _SC_ULONG_MAX
#define _SC_USHRT_MAX                    _SC_USHRT_MAX
#define _SC_NL_ARGMAX                    _SC_NL_ARGMAX
#define _SC_NL_LANGMAX                   _SC_NL_LANGMAX
#define _SC_NL_MSGMAX                    _SC_NL_MSGMAX
#define _SC_NL_NMAX                      _SC_NL_NMAX
#define _SC_NL_SETMAX                    _SC_NL_SETMAX
#define _SC_NL_TEXTMAX                   _SC_NL_TEXTMAX
#define _SC_XBS5_ILP32_OFF32             _SC_XBS5_ILP32_OFF32
#define _SC_XBS5_ILP32_OFFBIG            _SC_XBS5_ILP32_OFFBIG
#define _SC_XBS5_LP64_OFF64              _SC_XBS5_LP64_OFF64
#define _SC_XBS5_LPBIG_OFFBIG            _SC_XBS5_LPBIG_OFFBIG
#define _SC_XOPEN_LEGACY                 _SC_XOPEN_LEGACY
#define _SC_XOPEN_REALTIME               _SC_XOPEN_REALTIME
#define _SC_XOPEN_REALTIME_THREADS       _SC_XOPEN_REALTIME_THREADS
#define _SC_ADVISORY_INFO                _SC_ADVISORY_INFO
#define _SC_BARRIERS                     _SC_BARRIERS
#define _SC_BASE                         _SC_BASE
#define _SC_C_LANG_SUPPORT               _SC_C_LANG_SUPPORT
#define _SC_C_LANG_SUPPORT_R             _SC_C_LANG_SUPPORT_R
#define _SC_CLOCK_SELECTION              _SC_CLOCK_SELECTION
#define _SC_CPUTIME                      _SC_CPUTIME
#define _SC_THREAD_CPUTIME               _SC_THREAD_CPUTIME
#define _SC_DEVICE_IO                    _SC_DEVICE_IO
#define _SC_DEVICE_SPECIFIC              _SC_DEVICE_SPECIFIC
#define _SC_DEVICE_SPECIFIC_R            _SC_DEVICE_SPECIFIC_R
#define _SC_FD_MGMT                      _SC_FD_MGMT
#define _SC_FIFO                         _SC_FIFO
#define _SC_PIPE                         _SC_PIPE
#define _SC_FILE_ATTRIBUTES              _SC_FILE_ATTRIBUTES
#define _SC_FILE_LOCKING                 _SC_FILE_LOCKING
#define _SC_FILE_SYSTEM                  _SC_FILE_SYSTEM
#define _SC_MONOTONIC_CLOCK              _SC_MONOTONIC_CLOCK
#define _SC_MULTI_PROCESS                _SC_MULTI_PROCESS
#define _SC_SINGLE_PROCESS               _SC_SINGLE_PROCESS
#define _SC_NETWORKING                   _SC_NETWORKING
#define _SC_READER_WRITER_LOCKS          _SC_READER_WRITER_LOCKS
#define _SC_SPIN_LOCKS                   _SC_SPIN_LOCKS
#define _SC_REGEXP                       _SC_REGEXP
#define _SC_REGEX_VERSION                _SC_REGEX_VERSION
#define _SC_SHELL                        _SC_SHELL
#define _SC_SIGNALS                      _SC_SIGNALS
#define _SC_SPAWN                        _SC_SPAWN
#define _SC_SPORADIC_SERVER              _SC_SPORADIC_SERVER
#define _SC_THREAD_SPORADIC_SERVER       _SC_THREAD_SPORADIC_SERVER
#define _SC_SYSTEM_DATABASE              _SC_SYSTEM_DATABASE
#define _SC_SYSTEM_DATABASE_R            _SC_SYSTEM_DATABASE_R
#define _SC_TIMEOUTS                     _SC_TIMEOUTS
#define _SC_TYPED_MEMORY_OBJECTS         _SC_TYPED_MEMORY_OBJECTS
#define _SC_USER_GROUPS                  _SC_USER_GROUPS
#define _SC_USER_GROUPS_R                _SC_USER_GROUPS_R
#define _SC_2_PBS                        _SC_2_PBS
#define _SC_2_PBS_ACCOUNTING             _SC_2_PBS_ACCOUNTING
#define _SC_2_PBS_LOCATE                 _SC_2_PBS_LOCATE
#define _SC_2_PBS_MESSAGE                _SC_2_PBS_MESSAGE
#define _SC_2_PBS_TRACK                  _SC_2_PBS_TRACK
#define _SC_SYMLOOP_MAX                  _SC_SYMLOOP_MAX
#define _SC_STREAMS                      _SC_STREAMS
#define _SC_2_PBS_CHECKPOINT             _SC_2_PBS_CHECKPOINT
#define _SC_V6_ILP32_OFF32               _SC_V6_ILP32_OFF32
#define _SC_V6_ILP32_OFFBIG              _SC_V6_ILP32_OFFBIG
#define _SC_V6_LP64_OFF64                _SC_V6_LP64_OFF64
#define _SC_V6_LPBIG_OFFBIG              _SC_V6_LPBIG_OFFBIG
#define _SC_HOST_NAME_MAX                _SC_HOST_NAME_MAX
#define _SC_TRACE                        _SC_TRACE
#define _SC_TRACE_EVENT_FILTER           _SC_TRACE_EVENT_FILTER
#define _SC_TRACE_INHERIT                _SC_TRACE_INHERIT
#define _SC_TRACE_LOG                    _SC_TRACE_LOG
#define _SC_LEVEL1_ICACHE_SIZE           _SC_LEVEL1_ICACHE_SIZE
#define _SC_LEVEL1_ICACHE_ASSOC          _SC_LEVEL1_ICACHE_ASSOC
#define _SC_LEVEL1_ICACHE_LINESIZE       _SC_LEVEL1_ICACHE_LINESIZE
#define _SC_LEVEL1_DCACHE_SIZE           _SC_LEVEL1_DCACHE_SIZE
#define _SC_LEVEL1_DCACHE_ASSOC          _SC_LEVEL1_DCACHE_ASSOC
#define _SC_LEVEL1_DCACHE_LINESIZE       _SC_LEVEL1_DCACHE_LINESIZE
#define _SC_LEVEL2_CACHE_SIZE            _SC_LEVEL2_CACHE_SIZE
#define _SC_LEVEL2_CACHE_ASSOC           _SC_LEVEL2_CACHE_ASSOC
#define _SC_LEVEL2_CACHE_LINESIZE        _SC_LEVEL2_CACHE_LINESIZE
#define _SC_LEVEL3_CACHE_SIZE            _SC_LEVEL3_CACHE_SIZE
#define _SC_LEVEL3_CACHE_ASSOC           _SC_LEVEL3_CACHE_ASSOC
#define _SC_LEVEL3_CACHE_LINESIZE        _SC_LEVEL3_CACHE_LINESIZE
#define _SC_LEVEL4_CACHE_SIZE            _SC_LEVEL4_CACHE_SIZE
#define _SC_LEVEL4_CACHE_ASSOC           _SC_LEVEL4_CACHE_ASSOC
#define _SC_LEVEL4_CACHE_LINESIZE        _SC_LEVEL4_CACHE_LINESIZE
#define _SC_IPV6                         _SC_IPV6
#define _SC_RAW_SOCKETS                  _SC_RAW_SOCKETS
#define _SC_V7_ILP32_OFF32               _SC_V7_ILP32_OFF32
#define _SC_V7_ILP32_OFFBIG              _SC_V7_ILP32_OFFBIG
#define _SC_V7_LP64_OFF64                _SC_V7_LP64_OFF64
#define _SC_V7_LPBIG_OFFBIG              _SC_V7_LPBIG_OFFBIG
#define _SC_SS_REPL_MAX                  _SC_SS_REPL_MAX
#define _SC_TRACE_EVENT_NAME_MAX         _SC_TRACE_EVENT_NAME_MAX
#define _SC_TRACE_NAME_MAX               _SC_TRACE_NAME_MAX
#define _SC_TRACE_SYS_MAX                _SC_TRACE_SYS_MAX
#define _SC_TRACE_USER_EVENT_MAX         _SC_TRACE_USER_EVENT_MAX
#define _SC_XOPEN_STREAMS                _SC_XOPEN_STREAMS
#define _SC_THREAD_ROBUST_PRIO_INHERIT   _SC_THREAD_ROBUST_PRIO_INHERIT
#define _SC_THREAD_ROBUST_PRIO_PROTECT   _SC_THREAD_ROBUST_PRIO_PROTECT
#ifdef __USE_KOS
#define _SC_COUNT                        _SC_COUNT
#endif /* __USE_KOS */
#else /* __COMPILER_PREFERR_ENUMS */
#define _SC_ARG_MAX                      0
#define _SC_CHILD_MAX                    1
#define _SC_CLK_TCK                      2
#define _SC_NGROUPS_MAX                  3
#define _SC_OPEN_MAX                     4
#define _SC_STREAM_MAX                   5
#define _SC_TZNAME_MAX                   6
#define _SC_JOB_CONTROL                  7
#define _SC_SAVED_IDS                    8
#define _SC_REALTIME_SIGNALS             9
#define _SC_PRIORITY_SCHEDULING          10
#define _SC_TIMERS                       11
#define _SC_ASYNCHRONOUS_IO              12
#define _SC_PRIORITIZED_IO               13
#define _SC_SYNCHRONIZED_IO              14
#define _SC_FSYNC                        15
#define _SC_MAPPED_FILES                 16
#define _SC_MEMLOCK                      17
#define _SC_MEMLOCK_RANGE                18
#define _SC_MEMORY_PROTECTION            19
#define _SC_MESSAGE_PASSING              20
#define _SC_SEMAPHORES                   21
#define _SC_SHARED_MEMORY_OBJECTS        22
#define _SC_AIO_LISTIO_MAX               23
#define _SC_AIO_MAX                      24
#define _SC_AIO_PRIO_DELTA_MAX           25
#define _SC_DELAYTIMER_MAX               26
#define _SC_MQ_OPEN_MAX                  27
#define _SC_MQ_PRIO_MAX                  28
#define _SC_VERSION                      29
#define _SC_PAGESIZE                     30
#define _SC_PAGE_SIZE                    30
#define _SC_RTSIG_MAX                    31
#define _SC_SEM_NSEMS_MAX                32
#define _SC_SEM_VALUE_MAX                33
#define _SC_SIGQUEUE_MAX                 34
#define _SC_TIMER_MAX                    35
#define _SC_BC_BASE_MAX                  36
#define _SC_BC_DIM_MAX                   37
#define _SC_BC_SCALE_MAX                 38
#define _SC_BC_STRING_MAX                39
#define _SC_COLL_WEIGHTS_MAX             40
#define _SC_EQUIV_CLASS_MAX              41
#define _SC_EXPR_NEST_MAX                42
#define _SC_LINE_MAX                     43
#define _SC_RE_DUP_MAX                   44
#define _SC_CHARCLASS_NAME_MAX           45
#define _SC_2_VERSION                    46
#define _SC_2_C_BIND                     47
#define _SC_2_C_DEV                      48
#define _SC_2_FORT_DEV                   49
#define _SC_2_FORT_RUN                   50
#define _SC_2_SW_DEV                     51
#define _SC_2_LOCALEDEF                  52
#define _SC_PII                          53
#define _SC_PII_XTI                      54
#define _SC_PII_SOCKET                   55
#define _SC_PII_INTERNET                 56
#define _SC_PII_OSI                      57
#define _SC_POLL                         58
#define _SC_SELECT                       59
#define _SC_UIO_MAXIOV                   60
#define _SC_IOV_MAX                      60
#define _SC_PII_INTERNET_STREAM          61
#define _SC_PII_INTERNET_DGRAM           62
#define _SC_PII_OSI_COTS                 63
#define _SC_PII_OSI_CLTS                 64
#define _SC_PII_OSI_M                    65
#define _SC_T_IOV_MAX                    66
#define _SC_THREADS                      67
#define _SC_THREAD_SAFE_FUNCTIONS        68
#define _SC_GETGR_R_SIZE_MAX             69
#define _SC_GETPW_R_SIZE_MAX             70
#define _SC_LOGIN_NAME_MAX               71
#define _SC_TTY_NAME_MAX                 72
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 73
#define _SC_THREAD_KEYS_MAX              74
#define _SC_THREAD_STACK_MIN             75
#define _SC_THREAD_THREADS_MAX           76
#define _SC_THREAD_ATTR_STACKADDR        77
#define _SC_THREAD_ATTR_STACKSIZE        78
#define _SC_THREAD_PRIORITY_SCHEDULING   79
#define _SC_THREAD_PRIO_INHERIT          80
#define _SC_THREAD_PRIO_PROTECT          81
#define _SC_THREAD_PROCESS_SHARED        82
#define _SC_NPROCESSORS_CONF             83
#define _SC_NPROCESSORS_ONLN             84
#define _SC_NPROC_ONLN                   84
#define _SC_PHYS_PAGES                   85
#define _SC_AVPHYS_PAGES                 86
#define _SC_ATEXIT_MAX                   87
#define _SC_PASS_MAX                     88
#define _SC_XOPEN_VERSION                89
#define _SC_XOPEN_XCU_VERSION            90
#define _SC_XOPEN_UNIX                   91
#define _SC_XOPEN_CRYPT                  92
#define _SC_XOPEN_ENH_I18N               93
#define _SC_XOPEN_SHM                    94
#define _SC_2_CHAR_TERM                  95
#define _SC_2_C_VERSION                  96
#define _SC_2_UPE                        97
#define _SC_XOPEN_XPG2                   98
#define _SC_XOPEN_XPG3                   99
#define _SC_XOPEN_XPG4                   100
#define _SC_CHAR_BIT                     101
#define _SC_CHAR_MAX                     102
#define _SC_CHAR_MIN                     103
#define _SC_INT_MAX                      104
#define _SC_INT_MIN                      105
#define _SC_LONG_BIT                     106
#define _SC_WORD_BIT                     107
#define _SC_MB_LEN_MAX                   108
#define _SC_NZERO                        109
#define _SC_SSIZE_MAX                    110
#define _SC_SCHAR_MAX                    111
#define _SC_SCHAR_MIN                    112
#define _SC_SHRT_MAX                     113
#define _SC_SHRT_MIN                     114
#define _SC_UCHAR_MAX                    115
#define _SC_UINT_MAX                     116
#define _SC_ULONG_MAX                    117
#define _SC_USHRT_MAX                    118
#define _SC_NL_ARGMAX                    119
#define _SC_NL_LANGMAX                   120
#define _SC_NL_MSGMAX                    121
#define _SC_NL_NMAX                      122
#define _SC_NL_SETMAX                    123
#define _SC_NL_TEXTMAX                   124
#define _SC_XBS5_ILP32_OFF32             125
#define _SC_XBS5_ILP32_OFFBIG            126
#define _SC_XBS5_LP64_OFF64              127
#define _SC_XBS5_LPBIG_OFFBIG            128
#define _SC_XOPEN_LEGACY                 129
#define _SC_XOPEN_REALTIME               130
#define _SC_XOPEN_REALTIME_THREADS       131
#define _SC_ADVISORY_INFO                132
#define _SC_BARRIERS                     133
#define _SC_BASE                         134
#define _SC_C_LANG_SUPPORT               135
#define _SC_C_LANG_SUPPORT_R             136
#define _SC_CLOCK_SELECTION              137
#define _SC_CPUTIME                      138
#define _SC_THREAD_CPUTIME               139
#define _SC_DEVICE_IO                    140
#define _SC_DEVICE_SPECIFIC              141
#define _SC_DEVICE_SPECIFIC_R            142
#define _SC_FD_MGMT                      143
#define _SC_FIFO                         144
#define _SC_PIPE                         145
#define _SC_FILE_ATTRIBUTES              146
#define _SC_FILE_LOCKING                 147
#define _SC_FILE_SYSTEM                  148
#define _SC_MONOTONIC_CLOCK              149
#define _SC_MULTI_PROCESS                150
#define _SC_SINGLE_PROCESS               151
#define _SC_NETWORKING                   152
#define _SC_READER_WRITER_LOCKS          153
#define _SC_SPIN_LOCKS                   154
#define _SC_REGEXP                       155
#define _SC_REGEX_VERSION                156
#define _SC_SHELL                        157
#define _SC_SIGNALS                      158
#define _SC_SPAWN                        159
#define _SC_SPORADIC_SERVER              160
#define _SC_THREAD_SPORADIC_SERVER       161
#define _SC_SYSTEM_DATABASE              162
#define _SC_SYSTEM_DATABASE_R            163
#define _SC_TIMEOUTS                     164
#define _SC_TYPED_MEMORY_OBJECTS         165
#define _SC_USER_GROUPS                  166
#define _SC_USER_GROUPS_R                167
#define _SC_2_PBS                        168
#define _SC_2_PBS_ACCOUNTING             169
#define _SC_2_PBS_LOCATE                 170
#define _SC_2_PBS_MESSAGE                171
#define _SC_2_PBS_TRACK                  172
#define _SC_SYMLOOP_MAX                  173
#define _SC_STREAMS                      174
#define _SC_2_PBS_CHECKPOINT             175
#define _SC_V6_ILP32_OFF32               176
#define _SC_V6_ILP32_OFFBIG              177
#define _SC_V6_LP64_OFF64                178
#define _SC_V6_LPBIG_OFFBIG              179
#define _SC_HOST_NAME_MAX                180
#define _SC_TRACE                        181
#define _SC_TRACE_EVENT_FILTER           182
#define _SC_TRACE_INHERIT                183
#define _SC_TRACE_LOG                    184
#define _SC_LEVEL1_ICACHE_SIZE           185
#define _SC_LEVEL1_ICACHE_ASSOC          186
#define _SC_LEVEL1_ICACHE_LINESIZE       187
#define _SC_LEVEL1_DCACHE_SIZE           188
#define _SC_LEVEL1_DCACHE_ASSOC          189
#define _SC_LEVEL1_DCACHE_LINESIZE       190
#define _SC_LEVEL2_CACHE_SIZE            191
#define _SC_LEVEL2_CACHE_ASSOC           192
#define _SC_LEVEL2_CACHE_LINESIZE        193
#define _SC_LEVEL3_CACHE_SIZE            194
#define _SC_LEVEL3_CACHE_ASSOC           195
#define _SC_LEVEL3_CACHE_LINESIZE        196
#define _SC_LEVEL4_CACHE_SIZE            197
#define _SC_LEVEL4_CACHE_ASSOC           198
#define _SC_LEVEL4_CACHE_LINESIZE        199
#define _SC_IPV6                         (_SC_LEVEL1_ICACHE_SIZE + 50)
#define _SC_RAW_SOCKETS                  (_SC_LEVEL1_ICACHE_SIZE + 51)
#define _SC_V7_ILP32_OFF32               (_SC_LEVEL1_ICACHE_SIZE + 52)
#define _SC_V7_ILP32_OFFBIG              (_SC_LEVEL1_ICACHE_SIZE + 53)
#define _SC_V7_LP64_OFF64                (_SC_LEVEL1_ICACHE_SIZE + 54)
#define _SC_V7_LPBIG_OFFBIG              (_SC_LEVEL1_ICACHE_SIZE + 55)
#define _SC_SS_REPL_MAX                  (_SC_LEVEL1_ICACHE_SIZE + 56)
#define _SC_TRACE_EVENT_NAME_MAX         (_SC_LEVEL1_ICACHE_SIZE + 57)
#define _SC_TRACE_NAME_MAX               (_SC_LEVEL1_ICACHE_SIZE + 58)
#define _SC_TRACE_SYS_MAX                (_SC_LEVEL1_ICACHE_SIZE + 59)
#define _SC_TRACE_USER_EVENT_MAX         (_SC_LEVEL1_ICACHE_SIZE + 60)
#define _SC_XOPEN_STREAMS                (_SC_LEVEL1_ICACHE_SIZE + 61)
#define _SC_THREAD_ROBUST_PRIO_INHERIT   (_SC_LEVEL1_ICACHE_SIZE + 62)
#define _SC_THREAD_ROBUST_PRIO_PROTECT   (_SC_LEVEL1_ICACHE_SIZE + 63)
#ifdef __USE_KOS
#define _SC_COUNT                        (_SC_LEVEL1_ICACHE_SIZE + 64)
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

#endif /* !_BITS_CONFNAME_H */
