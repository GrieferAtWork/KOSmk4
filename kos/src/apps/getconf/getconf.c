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
#ifndef GUARD_APPS_GETCONF_GETCONF_C
#define GUARD_APPS_GETCONF_GETCONF_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/__bitfield.h>
#include <hybrid/typecore.h>

#include <kos/types.h>

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CC /* nothing */

DECL_BEGIN

/* Fun fact: this  right here works  (but only on i386)  to force libc into
 *           using a custom non-thread-safe `errno' global variable, rather
 *           than using its normal per-thread `errno'.
 * s.a. `/kos/src/libc/libc/arch/i386/errno.c' */
#if !defined(__x86_64__) && defined(__i386__) && 0
#undef errno
extern int errno;
#endif


/*      CONFTYPE_...      0  * ... */
#define CONFTYPE_CONFSTR  1 /* Use `confstr()' to determine value */
#define CONFTYPE_PATHCONF 2 /* Use `pathconf()' to determine value */
#define CONFTYPE_SYSCONF  3 /* Use `sysconf()' to determine value */

struct conf {
	char const           *c_name;      /* [1..1] Config name */
	__HYBRID_BITFIELD32_T c_id : 30;   /* Configuration ID */
	__HYBRID_BITFIELD32_T c_type : 2;  /* Configuration type */
#if __SIZEOF_POINTER__ > 4
	uint32_t             _c_pad; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
};

#define LONGEST_CONF_NAME_NAMELENGTH_PLUS_1 34 /* "_POSIX_THREAD_ROBUST_PRIO_PROTECT" */

/* clang-format off */
PRIVATE struct conf const confs[] = {

	/* confstr() */
	{ "PATH",                             _CS_PATH,                            CONFTYPE_CONFSTR },
	{ "CS_PATH",                          _CS_PATH,                            CONFTYPE_CONFSTR },
	{ "_POSIX_V6_WIDTH_RESTRICTED_ENVS",  _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS,  CONFTYPE_CONFSTR },
	{ "POSIX_V6_WIDTH_RESTRICTED_ENVS",   _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS,  CONFTYPE_CONFSTR },
	{ "GNU_LIBC_VERSION",                 _CS_GNU_LIBC_VERSION,                CONFTYPE_CONFSTR },
	{ "GNU_LIBPTHREAD_VERSION",           _CS_GNU_LIBPTHREAD_VERSION,          CONFTYPE_CONFSTR },
	{ "_XBS5_WIDTH_RESTRICTED_ENVS",      _CS_V5_WIDTH_RESTRICTED_ENVS,        CONFTYPE_CONFSTR },
	{ "XBS5_WIDTH_RESTRICTED_ENVS",       _CS_V5_WIDTH_RESTRICTED_ENVS,        CONFTYPE_CONFSTR },
	{ "_POSIX_V7_WIDTH_RESTRICTED_ENVS",  _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS,  CONFTYPE_CONFSTR },
	{ "POSIX_V7_WIDTH_RESTRICTED_ENVS",   _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS,  CONFTYPE_CONFSTR },
	{ "LFS_CFLAGS",                       _CS_LFS_CFLAGS,                      CONFTYPE_CONFSTR },
	{ "LFS_LDFLAGS",                      _CS_LFS_LDFLAGS,                     CONFTYPE_CONFSTR },
	{ "LFS_LIBS",                         _CS_LFS_LIBS,                        CONFTYPE_CONFSTR },
	{ "LFS_LINTFLAGS",                    _CS_LFS_LINTFLAGS,                   CONFTYPE_CONFSTR },
	{ "LFS64_CFLAGS",                     _CS_LFS64_CFLAGS,                    CONFTYPE_CONFSTR },
	{ "LFS64_LDFLAGS",                    _CS_LFS64_LDFLAGS,                   CONFTYPE_CONFSTR },
	{ "LFS64_LIBS",                       _CS_LFS64_LIBS,                      CONFTYPE_CONFSTR },
	{ "LFS64_LINTFLAGS",                  _CS_LFS64_LINTFLAGS,                 CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFF32_CFLAGS",          _CS_XBS5_ILP32_OFF32_CFLAGS,         CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFF32_LDFLAGS",         _CS_XBS5_ILP32_OFF32_LDFLAGS,        CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFF32_LIBS",            _CS_XBS5_ILP32_OFF32_LIBS,           CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFF32_LINTFLAGS",       _CS_XBS5_ILP32_OFF32_LINTFLAGS,      CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFFBIG_CFLAGS",         _CS_XBS5_ILP32_OFFBIG_CFLAGS,        CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFFBIG_LDFLAGS",        _CS_XBS5_ILP32_OFFBIG_LDFLAGS,       CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFFBIG_LIBS",           _CS_XBS5_ILP32_OFFBIG_LIBS,          CONFTYPE_CONFSTR },
	{ "XBS5_ILP32_OFFBIG_LINTFLAGS",      _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,     CONFTYPE_CONFSTR },
	{ "XBS5_LP64_OFF64_CFLAGS",           _CS_XBS5_LP64_OFF64_CFLAGS,          CONFTYPE_CONFSTR },
	{ "XBS5_LP64_OFF64_LDFLAGS",          _CS_XBS5_LP64_OFF64_LDFLAGS,         CONFTYPE_CONFSTR },
	{ "XBS5_LP64_OFF64_LIBS",             _CS_XBS5_LP64_OFF64_LIBS,            CONFTYPE_CONFSTR },
	{ "XBS5_LP64_OFF64_LINTFLAGS",        _CS_XBS5_LP64_OFF64_LINTFLAGS,       CONFTYPE_CONFSTR },
	{ "XBS5_LPBIG_OFFBIG_CFLAGS",         _CS_XBS5_LPBIG_OFFBIG_CFLAGS,        CONFTYPE_CONFSTR },
	{ "XBS5_LPBIG_OFFBIG_LDFLAGS",        _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,       CONFTYPE_CONFSTR },
	{ "XBS5_LPBIG_OFFBIG_LIBS",           _CS_XBS5_LPBIG_OFFBIG_LIBS,          CONFTYPE_CONFSTR },
	{ "XBS5_LPBIG_OFFBIG_LINTFLAGS",      _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,     CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFF32_CFLAGS",      _CS_POSIX_V6_ILP32_OFF32_CFLAGS,     CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFF32_LDFLAGS",     _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFF32_LIBS",        _CS_POSIX_V6_ILP32_OFF32_LIBS,       CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFF32_LINTFLAGS",   _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,  CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFFBIG_CFLAGS",     _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFFBIG_LDFLAGS",    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFFBIG_LIBS",       _CS_POSIX_V6_ILP32_OFFBIG_LIBS,      CONFTYPE_CONFSTR },
	{ "POSIX_V6_ILP32_OFFBIG_LINTFLAGS",  _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS, CONFTYPE_CONFSTR },
	{ "POSIX_V6_LP64_OFF64_CFLAGS",       _CS_POSIX_V6_LP64_OFF64_CFLAGS,      CONFTYPE_CONFSTR },
	{ "POSIX_V6_LP64_OFF64_LDFLAGS",      _CS_POSIX_V6_LP64_OFF64_LDFLAGS,     CONFTYPE_CONFSTR },
	{ "POSIX_V6_LP64_OFF64_LIBS",         _CS_POSIX_V6_LP64_OFF64_LIBS,        CONFTYPE_CONFSTR },
	{ "POSIX_V6_LP64_OFF64_LINTFLAGS",    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V6_LPBIG_OFFBIG_CFLAGS",     _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V6_LPBIG_OFFBIG_LDFLAGS",    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V6_LPBIG_OFFBIG_LIBS",       _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,      CONFTYPE_CONFSTR },
	{ "POSIX_V6_LPBIG_OFFBIG_LINTFLAGS",  _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS, CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFF32_CFLAGS",      _CS_POSIX_V7_ILP32_OFF32_CFLAGS,     CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFF32_LDFLAGS",     _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFF32_LIBS",        _CS_POSIX_V7_ILP32_OFF32_LIBS,       CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFF32_LINTFLAGS",   _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,  CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFFBIG_CFLAGS",     _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFFBIG_LDFLAGS",    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFFBIG_LIBS",       _CS_POSIX_V7_ILP32_OFFBIG_LIBS,      CONFTYPE_CONFSTR },
	{ "POSIX_V7_ILP32_OFFBIG_LINTFLAGS",  _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS, CONFTYPE_CONFSTR },
	{ "POSIX_V7_LP64_OFF64_CFLAGS",       _CS_POSIX_V7_LP64_OFF64_CFLAGS,      CONFTYPE_CONFSTR },
	{ "POSIX_V7_LP64_OFF64_LDFLAGS",      _CS_POSIX_V7_LP64_OFF64_LDFLAGS,     CONFTYPE_CONFSTR },
	{ "POSIX_V7_LP64_OFF64_LIBS",         _CS_POSIX_V7_LP64_OFF64_LIBS,        CONFTYPE_CONFSTR },
	{ "POSIX_V7_LP64_OFF64_LINTFLAGS",    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V7_LPBIG_OFFBIG_CFLAGS",     _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,    CONFTYPE_CONFSTR },
	{ "POSIX_V7_LPBIG_OFFBIG_LDFLAGS",    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,   CONFTYPE_CONFSTR },
	{ "POSIX_V7_LPBIG_OFFBIG_LIBS",       _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,      CONFTYPE_CONFSTR },
	{ "POSIX_V7_LPBIG_OFFBIG_LINTFLAGS",  _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS, CONFTYPE_CONFSTR },
	{ "POSIX_V6_ENV",                     _CS_V6_ENV,                          CONFTYPE_CONFSTR },
	{ "POSIX_V7_ENV",                     _CS_V7_ENV,                          CONFTYPE_CONFSTR },

	/* sysconf() */
	{ "ARG_MAX",                           _SC_ARG_MAX,                      CONFTYPE_SYSCONF },
	{ "CHILD_MAX",                         _SC_CHILD_MAX,                    CONFTYPE_SYSCONF },
	{ "CLK_TCK",                           _SC_CLK_TCK,                      CONFTYPE_SYSCONF },
	{ "NGROUPS_MAX",                       _SC_NGROUPS_MAX,                  CONFTYPE_SYSCONF },
	{ "OPEN_MAX",                          _SC_OPEN_MAX,                     CONFTYPE_SYSCONF },
	{ "_POSIX_OPEN_MAX",                   _SC_OPEN_MAX,                     CONFTYPE_SYSCONF },
	{ "STREAM_MAX",                        _SC_STREAM_MAX,                   CONFTYPE_SYSCONF },
	{ "_POSIX_STREAM_MAX",                 _SC_STREAM_MAX,                   CONFTYPE_SYSCONF },
	{ "TZNAME_MAX",                        _SC_TZNAME_MAX,                   CONFTYPE_SYSCONF },
	{ "_POSIX_TZNAME_MAX",                 _SC_TZNAME_MAX,                   CONFTYPE_SYSCONF },
	{ "_POSIX_JOB_CONTROL",                _SC_JOB_CONTROL,                  CONFTYPE_SYSCONF },
	{ "_POSIX_SAVED_IDS",                  _SC_SAVED_IDS,                    CONFTYPE_SYSCONF },
	{ "_POSIX_REALTIME_SIGNALS",           _SC_REALTIME_SIGNALS,             CONFTYPE_SYSCONF },
	{ "_POSIX_PRIORITY_SCHEDULING",        _SC_PRIORITY_SCHEDULING,          CONFTYPE_SYSCONF },
	{ "_POSIX_TIMERS",                     _SC_TIMERS,                       CONFTYPE_SYSCONF },
	{ "_POSIX_ASYNCHRONOUS_IO",            _SC_ASYNCHRONOUS_IO,              CONFTYPE_SYSCONF },
	{ "_POSIX_PRIORITIZED_IO",             _SC_PRIORITIZED_IO,               CONFTYPE_SYSCONF },
	{ "_POSIX_SYNCHRONIZED_IO",            _SC_SYNCHRONIZED_IO,              CONFTYPE_SYSCONF },
	{ "_POSIX_FSYNC",                      _SC_FSYNC,                        CONFTYPE_SYSCONF },
	{ "_POSIX_MAPPED_FILES",               _SC_MAPPED_FILES,                 CONFTYPE_SYSCONF },
	{ "_POSIX_MEMLOCK",                    _SC_MEMLOCK,                      CONFTYPE_SYSCONF },
	{ "_POSIX_MEMLOCK_RANGE",              _SC_MEMLOCK_RANGE,                CONFTYPE_SYSCONF },
	{ "_POSIX_MEMORY_PROTECTION",          _SC_MEMORY_PROTECTION,            CONFTYPE_SYSCONF },
	{ "_POSIX_MESSAGE_PASSING",            _SC_MESSAGE_PASSING,              CONFTYPE_SYSCONF },
	{ "_POSIX_SEMAPHORES",                 _SC_SEMAPHORES,                   CONFTYPE_SYSCONF },
	{ "_POSIX_SHARED_MEMORY_OBJECTS",      _SC_SHARED_MEMORY_OBJECTS,        CONFTYPE_SYSCONF },
	{ "AIO_LISTIO_MAX",                    _SC_AIO_LISTIO_MAX,               CONFTYPE_SYSCONF },
	{ "AIO_MAX",                           _SC_AIO_MAX,                      CONFTYPE_SYSCONF },
	{ "AIO_PRIO_DELTA_MAX",                _SC_AIO_PRIO_DELTA_MAX,           CONFTYPE_SYSCONF },
	{ "DELAYTIMER_MAX",                    _SC_DELAYTIMER_MAX,               CONFTYPE_SYSCONF },
	{ "MQ_OPEN_MAX",                       _SC_MQ_OPEN_MAX,                  CONFTYPE_SYSCONF },
	{ "MQ_PRIO_MAX",                       _SC_MQ_PRIO_MAX,                  CONFTYPE_SYSCONF },
	{ "_POSIX_VERSION",                    _SC_VERSION,                      CONFTYPE_SYSCONF },
	{ "PAGESIZE",                          _SC_PAGESIZE,                     CONFTYPE_SYSCONF },
	{ "PAGE_SIZE",                         _SC_PAGE_SIZE,                    CONFTYPE_SYSCONF },
	{ "RTSIG_MAX",                         _SC_RTSIG_MAX,                    CONFTYPE_SYSCONF },
	{ "SEM_NSEMS_MAX",                     _SC_SEM_NSEMS_MAX,                CONFTYPE_SYSCONF },
	{ "SEM_VALUE_MAX",                     _SC_SEM_VALUE_MAX,                CONFTYPE_SYSCONF },
	{ "SIGQUEUE_MAX",                      _SC_SIGQUEUE_MAX,                 CONFTYPE_SYSCONF },
	{ "TIMER_MAX",                         _SC_TIMER_MAX,                    CONFTYPE_SYSCONF },
	{ "BC_BASE_MAX",                       _SC_BC_BASE_MAX,                  CONFTYPE_SYSCONF },
	{ "POSIX2_BC_BASE_MAX",                _SC_BC_BASE_MAX,                  CONFTYPE_SYSCONF },
	{ "BC_DIM_MAX",                        _SC_BC_DIM_MAX,                   CONFTYPE_SYSCONF },
	{ "POSIX2_BC_DIM_MAX",                 _SC_BC_DIM_MAX,                   CONFTYPE_SYSCONF },
	{ "BC_SCALE_MAX",                      _SC_BC_SCALE_MAX,                 CONFTYPE_SYSCONF },
	{ "POSIX2_BC_SCALE_MAX",               _SC_BC_SCALE_MAX,                 CONFTYPE_SYSCONF },
	{ "BC_STRING_MAX",                     _SC_BC_STRING_MAX,                CONFTYPE_SYSCONF },
	{ "POSIX2_BC_STRING_MAX",              _SC_BC_STRING_MAX,                CONFTYPE_SYSCONF },
	{ "COLL_WEIGHTS_MAX",                  _SC_COLL_WEIGHTS_MAX,             CONFTYPE_SYSCONF },
	{ "POSIX2_COLL_WEIGHTS_MAX",           _SC_COLL_WEIGHTS_MAX,             CONFTYPE_SYSCONF },
	{ "EQUIV_CLASS_MAX",                   _SC_EQUIV_CLASS_MAX,              CONFTYPE_SYSCONF },
	{ "EXPR_NEST_MAX",                     _SC_EXPR_NEST_MAX,                CONFTYPE_SYSCONF },
	{ "POSIX2_EXPR_NEST_MAX",              _SC_EXPR_NEST_MAX,                CONFTYPE_SYSCONF },
	{ "LINE_MAX",                          _SC_LINE_MAX,                     CONFTYPE_SYSCONF },
	{ "_POSIX2_LINE_MAX",                  _SC_LINE_MAX,                     CONFTYPE_SYSCONF },
	{ "POSIX2_LINE_MAX",                   _SC_LINE_MAX,                     CONFTYPE_SYSCONF },
	{ "POSIX2_RE_DUP_MAX",                 _SC_RE_DUP_MAX,                   CONFTYPE_SYSCONF },
	{ "RE_DUP_MAX",                        _SC_RE_DUP_MAX,                   CONFTYPE_SYSCONF },
	{ "CHARCLASS_NAME_MAX",                _SC_CHARCLASS_NAME_MAX,           CONFTYPE_SYSCONF },
	{ "POSIX2_VERSION",                    _SC_2_VERSION,                    CONFTYPE_SYSCONF },
	{ "POSIX2_C_BIND",                     _SC_2_C_BIND,                     CONFTYPE_SYSCONF },
	{ "POSIX2_C_DEV",                      _SC_2_C_DEV,                      CONFTYPE_SYSCONF },
	{ "POSIX2_FORT_DEV",                   _SC_2_FORT_DEV,                   CONFTYPE_SYSCONF },
	{ "POSIX2_FORT_RUN",                   _SC_2_FORT_RUN,                   CONFTYPE_SYSCONF },
	{ "POSIX2_SW_DEV",                     _SC_2_SW_DEV,                     CONFTYPE_SYSCONF },
	{ "POSIX2_LOCALEDEF",                  _SC_2_LOCALEDEF,                  CONFTYPE_SYSCONF },
	{ "_POSIX_PII",                        _SC_PII,                          CONFTYPE_SYSCONF },
	{ "_POSIX_PII_XTI",                    _SC_PII_XTI,                      CONFTYPE_SYSCONF },
	{ "_POSIX_PII_SOCKET",                 _SC_PII_SOCKET,                   CONFTYPE_SYSCONF },
	{ "_POSIX_PII_INTERNET",               _SC_PII_INTERNET,                 CONFTYPE_SYSCONF },
	{ "_POSIX_PII_OSI",                    _SC_PII_OSI,                      CONFTYPE_SYSCONF },
	{ "_POSIX_POLL",                       _SC_POLL,                         CONFTYPE_SYSCONF },
	{ "_POSIX_SELECT",                     _SC_SELECT,                       CONFTYPE_SYSCONF },
	{ "UIO_MAXIOV",                        _SC_UIO_MAXIOV,                   CONFTYPE_SYSCONF },
	{ "IOV_MAX",                           _SC_IOV_MAX,                      CONFTYPE_SYSCONF },
	{ "_POSIX_PII_INTERNET_STREAM",        _SC_PII_INTERNET_STREAM,          CONFTYPE_SYSCONF },
	{ "_POSIX_PII_INTERNET_DGRAM",         _SC_PII_INTERNET_DGRAM,           CONFTYPE_SYSCONF },
	{ "_POSIX_PII_OSI_COTS",               _SC_PII_OSI_COTS,                 CONFTYPE_SYSCONF },
	{ "_POSIX_PII_OSI_CLTS",               _SC_PII_OSI_CLTS,                 CONFTYPE_SYSCONF },
	{ "_POSIX_PII_OSI_M",                  _SC_PII_OSI_M,                    CONFTYPE_SYSCONF },
	{ "_T_IOV_MAX",                        _SC_T_IOV_MAX,                    CONFTYPE_SYSCONF },
	{ "_POSIX_THREADS",                    _SC_THREADS,                      CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_SAFE_FUNCTIONS",      _SC_THREAD_SAFE_FUNCTIONS,        CONFTYPE_SYSCONF },
	{ "NSS_BUFLEN_GROUP",                  _SC_GETGR_R_SIZE_MAX,             CONFTYPE_SYSCONF },
	{ "NSS_BUFLEN_PASSWD",                 _SC_GETPW_R_SIZE_MAX,             CONFTYPE_SYSCONF },
	{ "LOGIN_NAME_MAX",                    _SC_LOGIN_NAME_MAX,               CONFTYPE_SYSCONF },
	{ "TTY_NAME_MAX",                      _SC_TTY_NAME_MAX,                 CONFTYPE_SYSCONF },
	{ "PTHREAD_DESTRUCTOR_ITERATIONS",     _SC_THREAD_DESTRUCTOR_ITERATIONS, CONFTYPE_SYSCONF },
	{ "PTHREAD_KEYS_MAX",                  _SC_THREAD_KEYS_MAX,              CONFTYPE_SYSCONF },
	{ "PTHREAD_STACK_MIN",                 _SC_THREAD_STACK_MIN,             CONFTYPE_SYSCONF },
	{ "PTHREAD_THREADS_MAX",               _SC_THREAD_THREADS_MAX,           CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_ATTR_STACKADDR",      _SC_THREAD_ATTR_STACKADDR,        CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_ATTR_STACKSIZE",      _SC_THREAD_ATTR_STACKSIZE,        CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_PRIORITY_SCHEDULING", _SC_THREAD_PRIORITY_SCHEDULING,   CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_PRIO_INHERIT",        _SC_THREAD_PRIO_INHERIT,          CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_PRIO_PROTECT",        _SC_THREAD_PRIO_PROTECT,          CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_PROCESS_SHARED",      _SC_THREAD_PROCESS_SHARED,        CONFTYPE_SYSCONF },
	{ "_NPROCESSORS_CONF",                 _SC_NPROCESSORS_CONF,             CONFTYPE_SYSCONF },
	{ "NPROCESSORS_CONF",                  _SC_NPROCESSORS_CONF,             CONFTYPE_SYSCONF },
	{ "_NPROCESSORS_ONLN",                 _SC_NPROCESSORS_ONLN,             CONFTYPE_SYSCONF },
	{ "NPROCESSORS_ONLN",                  _SC_NPROCESSORS_ONLN,             CONFTYPE_SYSCONF },
	{ "_PHYS_PAGES",                       _SC_PHYS_PAGES,                   CONFTYPE_SYSCONF },
	{ "_AVPHYS_PAGES",                     _SC_AVPHYS_PAGES,                 CONFTYPE_SYSCONF },
	{ "ATEXIT_MAX",                        _SC_ATEXIT_MAX,                   CONFTYPE_SYSCONF },
	{ "PASS_MAX",                          _SC_PASS_MAX,                     CONFTYPE_SYSCONF },
	{ "_XOPEN_VERSION",                    _SC_XOPEN_VERSION,                CONFTYPE_SYSCONF },
	{ "_XOPEN_XCU_VERSION",                _SC_XOPEN_XCU_VERSION,            CONFTYPE_SYSCONF },
	{ "_XOPEN_UNIX",                       _SC_XOPEN_UNIX,                   CONFTYPE_SYSCONF },
	{ "_XOPEN_CRYPT",                      _SC_XOPEN_CRYPT,                  CONFTYPE_SYSCONF },
	{ "_XOPEN_ENH_I18N",                   _SC_XOPEN_ENH_I18N,               CONFTYPE_SYSCONF },
	{ "_XOPEN_SHM",                        _SC_XOPEN_SHM,                    CONFTYPE_SYSCONF },
	{ "POSIX2_CHAR_TERM",                  _SC_2_CHAR_TERM,                  CONFTYPE_SYSCONF },
	{ "POSIX2_C_VERSION",                  _SC_2_C_VERSION,                  CONFTYPE_SYSCONF },
	{ "POSIX2_UPE",                        _SC_2_UPE,                        CONFTYPE_SYSCONF },
	{ "_XOPEN_XPG2",                       _SC_XOPEN_XPG2,                   CONFTYPE_SYSCONF },
	{ "_XOPEN_XPG3",                       _SC_XOPEN_XPG3,                   CONFTYPE_SYSCONF },
	{ "_XOPEN_XPG4",                       _SC_XOPEN_XPG4,                   CONFTYPE_SYSCONF },
	{ "CHAR_BIT",                          _SC_CHAR_BIT,                     CONFTYPE_SYSCONF },
	{ "CHAR_MAX",                          _SC_CHAR_MAX,                     CONFTYPE_SYSCONF },
	{ "CHAR_MIN",                          _SC_CHAR_MIN,                     CONFTYPE_SYSCONF },
	{ "INT_MAX",                           _SC_INT_MAX,                      CONFTYPE_SYSCONF },
	{ "INT_MIN",                           _SC_INT_MIN,                      CONFTYPE_SYSCONF },
	{ "LONG_BIT",                          _SC_LONG_BIT,                     CONFTYPE_SYSCONF },
	{ "WORD_BIT",                          _SC_WORD_BIT,                     CONFTYPE_SYSCONF },
	{ "MB_LEN_MAX",                        _SC_MB_LEN_MAX,                   CONFTYPE_SYSCONF },
	{ "NZERO",                             _SC_NZERO,                        CONFTYPE_SYSCONF },
	{ "SSIZE_MAX",                         _SC_SSIZE_MAX,                    CONFTYPE_SYSCONF },
	{ "SCHAR_MAX",                         _SC_SCHAR_MAX,                    CONFTYPE_SYSCONF },
	{ "SCHAR_MIN",                         _SC_SCHAR_MIN,                    CONFTYPE_SYSCONF },
	{ "SHRT_MAX",                          _SC_SHRT_MAX,                     CONFTYPE_SYSCONF },
	{ "SHRT_MIN",                          _SC_SHRT_MIN,                     CONFTYPE_SYSCONF },
	{ "UCHAR_MAX",                         _SC_UCHAR_MAX,                    CONFTYPE_SYSCONF },
	{ "UINT_MAX",                          _SC_UINT_MAX,                     CONFTYPE_SYSCONF },
	{ "ULONG_MAX",                         _SC_ULONG_MAX,                    CONFTYPE_SYSCONF },
	{ "USHRT_MAX",                         _SC_USHRT_MAX,                    CONFTYPE_SYSCONF },
	{ "NL_ARGMAX",                         _SC_NL_ARGMAX,                    CONFTYPE_SYSCONF },
	{ "NL_LANGMAX",                        _SC_NL_LANGMAX,                   CONFTYPE_SYSCONF },
	{ "NL_MSGMAX",                         _SC_NL_MSGMAX,                    CONFTYPE_SYSCONF },
	{ "NL_NMAX",                           _SC_NL_NMAX,                      CONFTYPE_SYSCONF },
	{ "NL_SETMAX",                         _SC_NL_SETMAX,                    CONFTYPE_SYSCONF },
	{ "NL_TEXTMAX",                        _SC_NL_TEXTMAX,                   CONFTYPE_SYSCONF },
	{ "_XBS5_ILP32_OFF32",                 _SC_XBS5_ILP32_OFF32,             CONFTYPE_SYSCONF },
	{ "_XBS5_ILP32_OFFBIG",                _SC_XBS5_ILP32_OFFBIG,            CONFTYPE_SYSCONF },
	{ "_XBS5_LP64_OFF64",                  _SC_XBS5_LP64_OFF64,              CONFTYPE_SYSCONF },
	{ "_XBS5_LPBIG_OFFBIG",                _SC_XBS5_LPBIG_OFFBIG,            CONFTYPE_SYSCONF },
	{ "_XOPEN_LEGACY",                     _SC_XOPEN_LEGACY,                 CONFTYPE_SYSCONF },
	{ "_XOPEN_REALTIME",                   _SC_XOPEN_REALTIME,               CONFTYPE_SYSCONF },
	{ "_XOPEN_REALTIME_THREADS",           _SC_XOPEN_REALTIME_THREADS,       CONFTYPE_SYSCONF },
	{ "_POSIX_ADVISORY_INFO",              _SC_ADVISORY_INFO,                CONFTYPE_SYSCONF },
	{ "_POSIX_BARRIERS",                   _SC_BARRIERS,                     CONFTYPE_SYSCONF },
	{ "_POSIX_BASE",                       _SC_BASE,                         CONFTYPE_SYSCONF },
	{ "_POSIX_C_LANG_SUPPORT",             _SC_C_LANG_SUPPORT,               CONFTYPE_SYSCONF },
	{ "_POSIX_C_LANG_SUPPORT_R",           _SC_C_LANG_SUPPORT_R,             CONFTYPE_SYSCONF },
	{ "_POSIX_CLOCK_SELECTION",            _SC_CLOCK_SELECTION,              CONFTYPE_SYSCONF },
	{ "_POSIX_CPUTIME",                    _SC_CPUTIME,                      CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_CPUTIME",             _SC_THREAD_CPUTIME,               CONFTYPE_SYSCONF },
	{ "_POSIX_DEVICE_IO",                  _SC_DEVICE_IO,                    CONFTYPE_SYSCONF },
	{ "_POSIX_DEVICE_SPECIFIC",            _SC_DEVICE_SPECIFIC,              CONFTYPE_SYSCONF },
	{ "_POSIX_DEVICE_SPECIFIC_R",          _SC_DEVICE_SPECIFIC_R,            CONFTYPE_SYSCONF },
	{ "_POSIX_FD_MGMT",                    _SC_FD_MGMT,                      CONFTYPE_SYSCONF },
	{ "_POSIX_FIFO",                       _SC_FIFO,                         CONFTYPE_SYSCONF },
	{ "_POSIX_PIPE",                       _SC_PIPE,                         CONFTYPE_SYSCONF },
	{ "_POSIX_FILE_ATTRIBUTES",            _SC_FILE_ATTRIBUTES,              CONFTYPE_SYSCONF },
	{ "_POSIX_FILE_LOCKING",               _SC_FILE_LOCKING,                 CONFTYPE_SYSCONF },
	{ "_POSIX_FILE_SYSTEM",                _SC_FILE_SYSTEM,                  CONFTYPE_SYSCONF },
	{ "_POSIX_MONOTONIC_CLOCK",            _SC_MONOTONIC_CLOCK,              CONFTYPE_SYSCONF },
	{ "_POSIX_MULTI_PROCESS",              _SC_MULTI_PROCESS,                CONFTYPE_SYSCONF },
	{ "_POSIX_SINGLE_PROCESS",             _SC_SINGLE_PROCESS,               CONFTYPE_SYSCONF },
	{ "_POSIX_NETWORKING",                 _SC_NETWORKING,                   CONFTYPE_SYSCONF },
	{ "_POSIX_READER_WRITER_LOCKS",        _SC_READER_WRITER_LOCKS,          CONFTYPE_SYSCONF },
	{ "_POSIX_SPIN_LOCKS",                 _SC_SPIN_LOCKS,                   CONFTYPE_SYSCONF },
	{ "_POSIX_REGEXP",                     _SC_REGEXP,                       CONFTYPE_SYSCONF },
	{ "_POSIX_REGEX_VERSION",              _SC_REGEX_VERSION,                CONFTYPE_SYSCONF },
	{ "_POSIX_SHELL",                      _SC_SHELL,                        CONFTYPE_SYSCONF },
	{ "_POSIX_SIGNALS",                    _SC_SIGNALS,                      CONFTYPE_SYSCONF },
	{ "_POSIX_SPAWN",                      _SC_SPAWN,                        CONFTYPE_SYSCONF },
	{ "_POSIX_SPORADIC_SERVER",            _SC_SPORADIC_SERVER,              CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_SPORADIC_SERVER",     _SC_THREAD_SPORADIC_SERVER,       CONFTYPE_SYSCONF },
	{ "_POSIX_SYSTEM_DATABASE",            _SC_SYSTEM_DATABASE,              CONFTYPE_SYSCONF },
	{ "_POSIX_SYSTEM_DATABASE_R",          _SC_SYSTEM_DATABASE_R,            CONFTYPE_SYSCONF },
	{ "_POSIX_TIMEOUTS",                   _SC_TIMEOUTS,                     CONFTYPE_SYSCONF },
	{ "_POSIX_TYPED_MEMORY_OBJECTS",       _SC_TYPED_MEMORY_OBJECTS,         CONFTYPE_SYSCONF },
	{ "_POSIX_USER_GROUPS",                _SC_USER_GROUPS,                  CONFTYPE_SYSCONF },
	{ "_POSIX_USER_GROUPS_R",              _SC_USER_GROUPS_R,                CONFTYPE_SYSCONF },
	{ "POSIX2_PBS",                        _SC_2_PBS,                        CONFTYPE_SYSCONF },
	{ "POSIX2_PBS_ACCOUNTING",             _SC_2_PBS_ACCOUNTING,             CONFTYPE_SYSCONF },
	{ "POSIX2_PBS_LOCATE",                 _SC_2_PBS_LOCATE,                 CONFTYPE_SYSCONF },
	{ "POSIX2_PBS_MESSAGE",                _SC_2_PBS_MESSAGE,                CONFTYPE_SYSCONF },
	{ "POSIX2_PBS_TRACK",                  _SC_2_PBS_TRACK,                  CONFTYPE_SYSCONF },
	{ "SYMLOOP_MAX",                       _SC_SYMLOOP_MAX,                  CONFTYPE_SYSCONF },
	{ "_POSIX_STREAMS",                    _SC_STREAMS,                      CONFTYPE_SYSCONF },
	{ "POSIX2_PBS_CHECKPOINT",             _SC_2_PBS_CHECKPOINT,             CONFTYPE_SYSCONF },
	{ "_POSIX_V6_ILP32_OFF32",             _SC_V6_ILP32_OFF32,               CONFTYPE_SYSCONF },
	{ "_POSIX_V6_ILP32_OFFBIG",            _SC_V6_ILP32_OFFBIG,              CONFTYPE_SYSCONF },
	{ "_POSIX_V6_LP64_OFF64",              _SC_V6_LP64_OFF64,                CONFTYPE_SYSCONF },
	{ "_POSIX_V6_LPBIG_OFFBIG",            _SC_V6_LPBIG_OFFBIG,              CONFTYPE_SYSCONF },
	{ "HOST_NAME_MAX",                     _SC_HOST_NAME_MAX,                CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE",                      _SC_TRACE,                        CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_EVENT_FILTER",         _SC_TRACE_EVENT_FILTER,           CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_INHERIT",              _SC_TRACE_INHERIT,                CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_LOG",                  _SC_TRACE_LOG,                    CONFTYPE_SYSCONF },
	{ "LEVEL1_ICACHE_SIZE",                _SC_LEVEL1_ICACHE_SIZE,           CONFTYPE_SYSCONF },
	{ "LEVEL1_ICACHE_ASSOC",               _SC_LEVEL1_ICACHE_ASSOC,          CONFTYPE_SYSCONF },
	{ "LEVEL1_ICACHE_LINESIZE",            _SC_LEVEL1_ICACHE_LINESIZE,       CONFTYPE_SYSCONF },
	{ "LEVEL1_DCACHE_SIZE",                _SC_LEVEL1_DCACHE_SIZE,           CONFTYPE_SYSCONF },
	{ "LEVEL1_DCACHE_ASSOC",               _SC_LEVEL1_DCACHE_ASSOC,          CONFTYPE_SYSCONF },
	{ "LEVEL1_DCACHE_LINESIZE",            _SC_LEVEL1_DCACHE_LINESIZE,       CONFTYPE_SYSCONF },
	{ "LEVEL2_CACHE_SIZE",                 _SC_LEVEL2_CACHE_SIZE,            CONFTYPE_SYSCONF },
	{ "LEVEL2_CACHE_ASSOC",                _SC_LEVEL2_CACHE_ASSOC,           CONFTYPE_SYSCONF },
	{ "LEVEL2_CACHE_LINESIZE",             _SC_LEVEL2_CACHE_LINESIZE,        CONFTYPE_SYSCONF },
	{ "LEVEL3_CACHE_SIZE",                 _SC_LEVEL3_CACHE_SIZE,            CONFTYPE_SYSCONF },
	{ "LEVEL3_CACHE_ASSOC",                _SC_LEVEL3_CACHE_ASSOC,           CONFTYPE_SYSCONF },
	{ "LEVEL3_CACHE_LINESIZE",             _SC_LEVEL3_CACHE_LINESIZE,        CONFTYPE_SYSCONF },
	{ "LEVEL4_CACHE_SIZE",                 _SC_LEVEL4_CACHE_SIZE,            CONFTYPE_SYSCONF },
	{ "LEVEL4_CACHE_ASSOC",                _SC_LEVEL4_CACHE_ASSOC,           CONFTYPE_SYSCONF },
	{ "LEVEL4_CACHE_LINESIZE",             _SC_LEVEL4_CACHE_LINESIZE,        CONFTYPE_SYSCONF },
	{ "IPV6",                              _SC_IPV6,                         CONFTYPE_SYSCONF },
	{ "_POSIX_IPV6",                       _SC_IPV6,                         CONFTYPE_SYSCONF },
	{ "RAW_SOCKETS",                       _SC_RAW_SOCKETS,                  CONFTYPE_SYSCONF },
	{ "_POSIX_RAW_SOCKETS",                _SC_RAW_SOCKETS,                  CONFTYPE_SYSCONF },
	{ "_POSIX_V7_ILP32_OFF32",             _SC_V7_ILP32_OFF32,               CONFTYPE_SYSCONF },
	{ "_POSIX_V7_ILP32_OFFBIG",            _SC_V7_ILP32_OFFBIG,              CONFTYPE_SYSCONF },
	{ "_POSIX_V7_LP64_OFF64",              _SC_V7_LP64_OFF64,                CONFTYPE_SYSCONF },
	{ "_POSIX_V7_LPBIG_OFFBIG",            _SC_V7_LPBIG_OFFBIG,              CONFTYPE_SYSCONF },
	{ "_POSIX_SS_REPL_MAX",                _SC_SS_REPL_MAX,                  CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_EVENT_NAME_MAX",       _SC_TRACE_EVENT_NAME_MAX,         CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_NAME_MAX",             _SC_TRACE_NAME_MAX,               CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_SYS_MAX",              _SC_TRACE_SYS_MAX,                CONFTYPE_SYSCONF },
	{ "_POSIX_TRACE_USER_EVENT_MAX",       _SC_TRACE_USER_EVENT_MAX,         CONFTYPE_SYSCONF },
	{ "_XOPEN_STREAMS",                    _SC_XOPEN_STREAMS,                CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_ROBUST_PRIO_INHERIT", _SC_THREAD_ROBUST_PRIO_INHERIT,   CONFTYPE_SYSCONF },
	{ "_POSIX_THREAD_ROBUST_PRIO_PROTECT", _SC_THREAD_ROBUST_PRIO_PROTECT,   CONFTYPE_SYSCONF },

	/* pathconf() */
	{ "LINK_MAX",                 _PC_LINK_MAX,           CONFTYPE_PATHCONF },
	{ "_POSIX_LINK_MAX",          _PC_LINK_MAX,           CONFTYPE_PATHCONF },
	{ "MAX_CANON",                _PC_MAX_CANON,          CONFTYPE_PATHCONF },
	{ "_POSIX_MAX_CANON",         _PC_MAX_CANON,          CONFTYPE_PATHCONF },
	{ "MAX_INPUT",                _PC_MAX_INPUT,          CONFTYPE_PATHCONF },
	{ "_POSIX_MAX_INPUT",         _PC_MAX_INPUT,          CONFTYPE_PATHCONF },
	{ "NAME_MAX",                 _PC_NAME_MAX,           CONFTYPE_PATHCONF },
	{ "_POSIX_NAME_MAX",          _PC_NAME_MAX,           CONFTYPE_PATHCONF },
	{ "PATH_MAX",                 _PC_PATH_MAX,           CONFTYPE_PATHCONF },
	{ "_POSIX_PATH_MAX",          _PC_PATH_MAX,           CONFTYPE_PATHCONF },
	{ "PIPE_BUF",                 _PC_PIPE_BUF,           CONFTYPE_PATHCONF },
	{ "_POSIX_PIPE_BUF",          _PC_PIPE_BUF,           CONFTYPE_PATHCONF },
	{ "_POSIX_CHOWN_RESTRICTED",  _PC_CHOWN_RESTRICTED,   CONFTYPE_PATHCONF },
	{ "_POSIX_NO_TRUNC",          _PC_NO_TRUNC,           CONFTYPE_PATHCONF },
	{ "_POSIX_VDISABLE",          _PC_VDISABLE,           CONFTYPE_PATHCONF },
	{ "_POSIX_SYNC_IO",           _PC_SYNC_IO,            CONFTYPE_PATHCONF },
	{ "_POSIX_ASYNC_IO",          _PC_ASYNC_IO,           CONFTYPE_PATHCONF },
	{ "_POSIX_PRIO_IO",           _PC_PRIO_IO,            CONFTYPE_PATHCONF },
	{ "SOCK_MAXBUF",              _PC_SOCK_MAXBUF,        CONFTYPE_PATHCONF },
	{ "FILESIZEBITS",             _PC_FILESIZEBITS,       CONFTYPE_PATHCONF },
	{ "POSIX_REC_INCR_XFER_SIZE", _PC_REC_INCR_XFER_SIZE, CONFTYPE_PATHCONF },
	{ "POSIX_REC_MAX_XFER_SIZE",  _PC_REC_MAX_XFER_SIZE,  CONFTYPE_PATHCONF },
	{ "POSIX_REC_MIN_XFER_SIZE",  _PC_REC_MIN_XFER_SIZE,  CONFTYPE_PATHCONF },
	{ "POSIX_REC_XFER_ALIGN",     _PC_REC_XFER_ALIGN,     CONFTYPE_PATHCONF },
	{ "POSIX_ALLOC_SIZE_MIN",     _PC_ALLOC_SIZE_MIN,     CONFTYPE_PATHCONF },
	{ "SYMLINK_MAX",              _PC_SYMLINK_MAX,        CONFTYPE_PATHCONF },
	{ "POSIX2_SYMLINKS",          _PC_2_SYMLINKS,         CONFTYPE_PATHCONF },

};
/* clang-format on */

/* Find the configuration name identified by `name'
 * NOTE: If the name  isn't found during  the first pass,  search for it  as
 *       long as one of the following prefixes could be removed from `name':
 *       "_POSIX_", "_"
 * If no such configuration name exists, return `NULL' instead. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) struct conf const *CC
findconf(char const *__restrict name) {
	unsigned int i;
again:
	for (i = 0; i < lengthof(confs); ++i) {
		if (strcmp(confs[i].c_name, name) == 0)
			return &confs[i];
	}
	if (bcmp(name, "_POSIX_", 7, sizeof(char)) == 0) {
		name += 7;
		goto again;
	}
	if (*name == '_') {
		name += 1;
		goto again;
	}
	/* Not found */
	return NULL;
}

/* Print the configuration value for `type:id', followed by a line-feed
 * @param: path: The path to use when `type=CONFTYPE_PATHCONF' (ignored otherwise) */
PRIVATE ssize_t CC
printconfval(fd_t fd, unsigned int id,
             unsigned int type, char const *path) {
	ssize_t result;
	switch (type) {

	case CONFTYPE_CONFSTR: {
		char *buf;
		size_t reqlen, buflen = 256;
		buf = (char *)malloc(buflen, sizeof(char));
		if unlikely(!buf) {
			buflen = 1;
			buf = (char *)malloc(buflen);
			if unlikely(!buf)
				goto err;
		}
again_confstr:
		reqlen = confstr(id, buf, buflen);
		if (reqlen > buflen) {
			char *newbuf;
			newbuf = (char *)realloc(buf, reqlen, sizeof(char));
			if unlikely(!newbuf) {
				free(buf);
				goto err;
			}
			buf    = newbuf;
			buflen = reqlen;
			goto again_confstr;
		}
		buflen = strnlen(buf, buflen);
		buf[buflen] = '\n';
		result = write(fd, buf, (buflen + 1) * sizeof(char));
		free(buf);
	}	break;

	case CONFTYPE_PATHCONF:
	case CONFTYPE_SYSCONF: {
		long value;
		errno = EOK;
		value = type == CONFTYPE_PATHCONF ? pathconf(path, id)
		                                  : sysconf(id);
		if (value == -1 && errno != EOK)
			goto err;
		/* Check for unlimited/undefined config name. */
		if ((type == CONFTYPE_SYSCONF &&
		     (id >= _SC_CHAR_BIT && id <= _SC_USHRT_MAX)) ||
		    (type == CONFTYPE_PATHCONF &&
		     ((id >= _PC_LINK_MAX && id <= _PC_PIPE_BUF) ||
		      (id >= _PC_SOCK_MAXBUF && id <= _PC_SYMLINK_MAX)))) {
			/* Special case: Print (some of) these as unsigned! */
			if ((id == _SC_CHAR_MIN || id == _SC_INT_MIN ||
			     id == _SC_SCHAR_MIN || id == _SC_SHRT_MIN) &&
			    type == CONFTYPE_SYSCONF) {
				/* Still print these as signed! */
				result = dprintf(fd, "%ld\n", value);
			} else {
				result = dprintf(fd, "%lu\n", (unsigned long)value);
			}
		} else if (value == -1) {
			PRIVATE char const undefined[] = "undefined\n";
			result = write(fd, undefined, sizeof(undefined) - sizeof(char));
		} else {
			/* Print the value. */
			result = dprintf(fd, "%ld\n", value);
		}
	}	break;

	default:
		__builtin_unreachable();
	}
	return result;
err:
	return -1;
}

/* Print the configuration value to stdout, or an error message to stderr */
PRIVATE ssize_t CC
printconfval_or_error(fd_t stdout_fileno,
                      fd_t stderr_fileno,
                      unsigned int id,
                      unsigned int type,
                      char const *path) {
	ssize_t error;
	error = printconfval(stdout_fileno, id, type, path);
	if (error == -1) {
		/* Error. */
		dprintf(stderr_fileno, "%s: %s\n",
		        type == CONFTYPE_PATHCONF
		        ? "pathconf"
		        : type == CONFTYPE_CONFSTR
		          ? "constr"
		          : "sysconf",
		        strerrordesc_np(errno));
	}
	return error;
}

/* Print all conf */
PRIVATE void CC printall(char const *path) {
	unsigned int i;
	for (i = 0; i < lengthof(confs); ++i) {
		if (confs[i].c_type == CONFTYPE_PATHCONF && !path)
			continue; /* Skip */
		dprintf(STDOUT_FILENO,
		        "%-" PP_STR(LONGEST_CONF_NAME_NAMELENGTH_PLUS_1) "s",
		        confs[i].c_name);
		printconfval_or_error(STDOUT_FILENO,
		                      STDOUT_FILENO,
		                      confs[i].c_id,
		                      confs[i].c_type,
		                      path);
	}
}

PRIVATE void CC usage(void) {
	PRIVATE char const message[] =
	"Usage: getconf [-v ignored] confname [path]\n"
	"       getconf [-v ignored] -a [path=/]\n";
	write(STDOUT_FILENO, message, sizeof(message) - sizeof(char));
}


int main(int argc, char *argv[]) {
	if likely(argc) {
		--argc;
		++argv;
	}
	if unlikely(!argc) {
		usage();
		return 0;
	}
	if (strcmp(argv[0], "-v") == 0) {
		if (argc <= 2)
			goto bad_usage;
		argv += 2;
		argc -= 2;
	}
	if (strcmp(argv[0], "-a") == 0) {
		char const *path = "/";
		if unlikely(argc > 2)
			goto bad_usage;
		if (argc == 2)
			path = argv[1];
		printall(path);
	} else {
		struct conf const *cfg;
		char const *name;
		char const *path = NULL;
		/* Print some specific configuration name */
		if (strcmp(argv[0], "--") == 0) {
			if (argc <= 1)
				goto bad_usage;
			--argc;
			++argv;
		}
		if unlikely(argc > 2)
			goto bad_usage;
		name = argv[0];
		if (argc == 2)
			path = argv[1];
		cfg = findconf(name);
		if unlikely(!cfg) {
			dprintf(STDERR_FILENO, "getconf: Unrecognized variable `%s'\n",
			        name);
			return 2;
		}
		if (cfg->c_type == CONFTYPE_PATHCONF && !path) {
			dprintf(STDERR_FILENO, "getconf: Variable `%s' requires a path\n",
			        name);
			return 2;
		}
		if (printconfval_or_error(STDOUT_FILENO,
		                          STDERR_FILENO,
		                          cfg->c_id,
		                          cfg->c_type,
		                          path) < 0)
			return 3;
	}
	return 0;
bad_usage:
	usage();
	return 1;
}


DECL_END

#endif /* !GUARD_APPS_GETCONF_GETCONF_C */
