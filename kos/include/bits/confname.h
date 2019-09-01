/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CONFNAME_H
#define _BITS_CONFNAME_H 1

#include <__stdinc.h>

/* `sysconf', `pathconf', and `confstr' NAME values.  Generic version.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Values for the NAME argument to `pathconf' and `fpathconf'.  */
#define _PC_LINK_MAX                             0
#define _PC_MAX_CANON                            1
#define _PC_MAX_INPUT                            2
#define _PC_NAME_MAX                             3
#define _PC_PATH_MAX                             4
#define _PC_PIPE_BUF                             5
#define _PC_CHOWN_RESTRICTED                     6
#define _PC_NO_TRUNC                             8
#define _PC_VDISABLE                             9
#define _PC_SYNC_IO                              10
#define _PC_ASYNC_IO                             11
#define _PC_PRIO_IO                              12
#define _PC_SOCK_MAXBUF                          13
#define _PC_FILESIZEBITS                         14
#define _PC_REC_INCR_XFER_SIZE                   15
#define _PC_REC_MAX_XFER_SIZE                    16
#define _PC_REC_MIN_XFER_SIZE                    17
#define _PC_REC_XFER_ALIGN                       18
#define _PC_ALLOC_SIZE_MIN                       19
#define _PC_SYMLINK_MAX                          20
#define _PC_2_SYMLINKS                           21

/* Values for the argument to `sysconf'.  */
#define _SC_ARG_MAX                              0
#define _SC_CHILD_MAX                            1
#define _SC_CLK_TCK                              2
#define _SC_NGROUPS_MAX                          3
#define _SC_OPEN_MAX                             4
#define _SC_STREAM_MAX                           5
#define _SC_TZNAME_MAX                           6
#define _SC_JOB_CONTROL                          7
#define _SC_SAVED_IDS                            8
#define _SC_REALTIME_SIGNALS                     9
#define _SC_PRIORITY_SCHEDULING                  10
#define _SC_TIMERS                               11
#define _SC_ASYNCHRONOUS_IO                      12
#define _SC_PRIORITIZED_IO                       13
#define _SC_SYNCHRONIZED_IO                      14
#define _SC_FSYNC                                15
#define _SC_MAPPED_FILES                         16
#define _SC_MEMLOCK                              17
#define _SC_MEMLOCK_RANGE                        18
#define _SC_MEMORY_PROTECTION                    19
#define _SC_MESSAGE_PASSING                      20
#define _SC_SEMAPHORES                           21
#define _SC_SHARED_MEMORY_OBJECTS                22
#define _SC_AIO_LISTIO_MAX                       23
#define _SC_AIO_MAX                              24
#define _SC_AIO_PRIO_DELTA_MAX                   25
#define _SC_DELAYTIMER_MAX                       26
#define _SC_MQ_OPEN_MAX                          27
#define _SC_MQ_PRIO_MAX                          28
#define _SC_VERSION                              29
#define _SC_PAGESIZE                             30
#define _SC_PAGE_SIZE                            _SC_PAGESIZE
#define _SC_RTSIG_MAX                            40
#define _SC_SEM_NSEMS_MAX                        41
#define _SC_SEM_VALUE_MAX                        42
#define _SC_SIGQUEUE_MAX                         43
#define _SC_TIMER_MAX                            44
#define _SC_BC_BASE_MAX                          45
#define _SC_BC_DIM_MAX                           46
#define _SC_BC_SCALE_MAX                         47
#define _SC_BC_STRING_MAX                        48
#define _SC_COLL_WEIGHTS_MAX                     49
#define _SC_EQUIV_CLASS_MAX                      50
#define _SC_EXPR_NEST_MAX                        51
#define _SC_LINE_MAX                             52
#define _SC_RE_DUP_MAX                           53
#define _SC_CHARCLASS_NAME_MAX                   54
#define _SC_2_VERSION                            55
#define _SC_2_C_BIND                             56
#define _SC_2_C_DEV                              57
#define _SC_2_FORT_DEV                           58
#define _SC_2_FORT_RUN                           59
#define _SC_2_SW_DEV                             60
#define _SC_2_LOCALEDEF                          61
#define _SC_PII                                  62
#define _SC_PII_XTI                              63
#define _SC_PII_SOCKET                           64
#define _SC_PII_INTERNET                         65
#define _SC_PII_OSI                              66
#define _SC_POLL                                 67
#define _SC_SELECT                               68
#define _SC_UIO_MAXIOV                           69
#define _SC_IOV_MAX                              _SC_UIO_MAXIOV
#define _SC_PII_INTERNET_STREAM                  70
#define _SC_PII_INTERNET_DGRAM                   71
#define _SC_PII_OSI_COTS                         72
#define _SC_PII_OSI_CLTS                         73
#define _SC_PII_OSI_M                            74
#define _SC_T_IOV_MAX                            75
#define _SC_THREADS                              76
#define _SC_THREAD_SAFE_FUNCTIONS                77
#define _SC_GETGR_R_SIZE_MAX                     78
#define _SC_GETPW_R_SIZE_MAX                     79
#define _SC_LOGIN_NAME_MAX                       80
#define _SC_TTY_NAME_MAX                         81
#define _SC_THREAD_DESTRUCTOR_ITERATIONS         82
#define _SC_THREAD_KEYS_MAX                      83
#define _SC_THREAD_STACK_MIN                     84
#define _SC_THREAD_THREADS_MAX                   85
#define _SC_THREAD_ATTR_STACKADDR                86
#define _SC_THREAD_ATTR_STACKSIZE                87
#define _SC_THREAD_PRIORITY_SCHEDULING           88
#define _SC_THREAD_PRIO_INHERIT                  89
#define _SC_THREAD_PRIO_PROTECT                  90
#define _SC_THREAD_PROCESS_SHARED                91
#define _SC_NPROCESSORS_CONF                     92
#define _SC_NPROCESSORS_ONLN                     93
#define _SC_NPROC_ONLN                           _SC_NPROCESSORS_ONLN
#define _SC_PHYS_PAGES                           94
#define _SC_AVPHYS_PAGES                         95
#define _SC_ATEXIT_MAX                           96
#define _SC_PASS_MAX                             97
#define _SC_XOPEN_VERSION                        98
#define _SC_XOPEN_XCU_VERSION                    99
#define _SC_XOPEN_UNIX                           100
#define _SC_XOPEN_CRYPT                          101
#define _SC_XOPEN_ENH_I18N                       102
#define _SC_XOPEN_SHM                            103
#define _SC_2_CHAR_TERM                          104
#define _SC_2_C_VERSION                          105
#define _SC_2_UPE                                106
#define _SC_XOPEN_XPG2                           107
#define _SC_XOPEN_XPG3                           108
#define _SC_XOPEN_XPG4                           109
#define _SC_CHAR_BIT                             110
#define _SC_CHAR_MAX                             111
#define _SC_CHAR_MIN                             112
#define _SC_INT_MAX                              113
#define _SC_INT_MIN                              114
#define _SC_LONG_BIT                             115
#define _SC_WORD_BIT                             116
#define _SC_MB_LEN_MAX                           117
#define _SC_NZERO                                118
#define _SC_SSIZE_MAX                            119
#define _SC_SCHAR_MAX                            120
#define _SC_SCHAR_MIN                            121
#define _SC_SHRT_MAX                             122
#define _SC_SHRT_MIN                             123
#define _SC_UCHAR_MAX                            124
#define _SC_UINT_MAX                             125
#define _SC_ULONG_MAX                            126
#define _SC_USHRT_MAX                            127
#define _SC_NL_ARGMAX                            128
#define _SC_NL_LANGMAX                           129
#define _SC_NL_MSGMAX                            130
#define _SC_NL_NMAX                              131
#define _SC_NL_SETMAX                            132
#define _SC_NL_TEXTMAX                           133
#define _SC_XBS5_ILP32_OFF32                     134
#define _SC_XBS5_ILP32_OFFBIG                    135
#define _SC_XBS5_LP64_OFF64                      136
#define _SC_XBS5_LPBIG_OFFBIG                    137
#define _SC_XOPEN_LEGACY                         138
#define _SC_XOPEN_REALTIME                       139
#define _SC_XOPEN_REALTIME_THREADS               140
#define _SC_ADVISORY_INFO                        141
#define _SC_BARRIERS                             142
#define _SC_BASE                                 143
#define _SC_C_LANG_SUPPORT                       144
#define _SC_C_LANG_SUPPORT_R                     145
#define _SC_CLOCK_SELECTION                      146
#define _SC_CPUTIME                              147
#define _SC_THREAD_CPUTIME                       148
#define _SC_DEVICE_IO                            149
#define _SC_DEVICE_SPECIFIC                      150
#define _SC_DEVICE_SPECIFIC_R                    151
#define _SC_FD_MGMT                              152
#define _SC_FIFO                                 153
#define _SC_PIPE                                 154
#define _SC_FILE_ATTRIBUTES                      155
#define _SC_FILE_LOCKING                         156
#define _SC_FILE_SYSTEM                          157
#define _SC_MONOTONIC_CLOCK                      158
#define _SC_MULTI_PROCESS                        159
#define _SC_SINGLE_PROCESS                       160
#define _SC_NETWORKING                           161
#define _SC_READER_WRITER_LOCKS                  162
#define _SC_SPIN_LOCKS                           163
#define _SC_REGEXP                               164
#define _SC_REGEX_VERSION                        165
#define _SC_SHELL                                166
#define _SC_SIGNALS                              167
#define _SC_SPAWN                                168
#define _SC_SPORADIC_SERVER                      169
#define _SC_THREAD_SPORADIC_SERVER               170
#define _SC_SYSTEM_DATABASE                      171
#define _SC_SYSTEM_DATABASE_R                    172
#define _SC_TIMEOUTS                             173
#define _SC_TYPED_MEMORY_OBJECTS                 174
#define _SC_USER_GROUPS                          175
#define _SC_USER_GROUPS_R                        176
#define _SC_2_PBS                                177
#define _SC_2_PBS_ACCOUNTING                     178
#define _SC_2_PBS_LOCATE                         179
#define _SC_2_PBS_MESSAGE                        180
#define _SC_2_PBS_TRACK                          181
#define _SC_SYMLOOP_MAX                          182
#define _SC_STREAMS                              183
#define _SC_2_PBS_CHECKPOINT                     184
#define _SC_V6_ILP32_OFF32                       185
#define _SC_V6_ILP32_OFFBIG                      186
#define _SC_V6_LP64_OFF64                        187
#define _SC_V6_LPBIG_OFFBIG                      188
#define _SC_HOST_NAME_MAX                        189
#define _SC_TRACE                                190
#define _SC_TRACE_EVENT_FILTER                   191
#define _SC_TRACE_INHERIT                        192
#define _SC_TRACE_LOG                            193
#define _SC_LEVEL1_ICACHE_SIZE                   194
#define _SC_LEVEL1_ICACHE_ASSOC                  195
#define _SC_LEVEL1_ICACHE_LINESIZE               196
#define _SC_LEVEL1_DCACHE_SIZE                   197
#define _SC_LEVEL1_DCACHE_ASSOC                  198
#define _SC_LEVEL1_DCACHE_LINESIZE               199
#define _SC_LEVEL2_CACHE_SIZE                    200
#define _SC_LEVEL2_CACHE_ASSOC                   201
#define _SC_LEVEL2_CACHE_LINESIZE                202
#define _SC_LEVEL3_CACHE_SIZE                    203
#define _SC_LEVEL3_CACHE_ASSOC                   204
#define _SC_LEVEL3_CACHE_LINESIZE                205
#define _SC_LEVEL4_CACHE_SIZE                    206
#define _SC_LEVEL4_CACHE_ASSOC                   207
#define _SC_LEVEL4_CACHE_LINESIZE                208
#define _SC_IPV6                                 244 /* _SC_LEVEL1_ICACHE_SIZE + 50 */
#define _SC_RAW_SOCKETS                          245
#define _SC_V7_ILP32_OFF32                       246
#define _SC_V7_ILP32_OFFBIG                      247
#define _SC_V7_LP64_OFF64                        248
#define _SC_V7_LPBIG_OFFBIG                      249
#define _SC_SS_REPL_MAX                          250
#define _SC_TRACE_EVENT_NAME_MAX                 251
#define _SC_TRACE_NAME_MAX                       252
#define _SC_TRACE_SYS_MAX                        253
#define _SC_TRACE_USER_EVENT_MAX                 254
#define _SC_XOPEN_STREAMS                        255
#define _SC_THREAD_ROBUST_PRIO_INHERIT           256
#define _SC_THREAD_ROBUST_PRIO_PROTECT           257
#ifdef __USE_KOS
#define _SC_COUNT                                258
#endif

/* Values for the NAME argument to `confstr'.  */
#define _CS_PATH                                 0 /* The default search path.  */
#define _CS_V6_WIDTH_RESTRICTED_ENVS             1
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS       _CS_V6_WIDTH_RESTRICTED_ENVS
#define _CS_GNU_LIBC_VERSION                     2
#define _CS_GNU_LIBPTHREAD_VERSION               3
#define _CS_V5_WIDTH_RESTRICTED_ENVS             4
#define _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS       _CS_V5_WIDTH_RESTRICTED_ENVS
#define _CS_V7_WIDTH_RESTRICTED_ENVS             5
#define _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS       _CS_V7_WIDTH_RESTRICTED_ENVS
#define _CS_LFS_CFLAGS                           1000
#define _CS_LFS_LDFLAGS                          1001
#define _CS_LFS_LIBS                             1002
#define _CS_LFS_LINTFLAGS                        1003
#define _CS_LFS64_CFLAGS                         1004
#define _CS_LFS64_LDFLAGS                        1005
#define _CS_LFS64_LIBS                           1006
#define _CS_LFS64_LINTFLAGS                      1007
#define _CS_XBS5_ILP32_OFF32_CFLAGS              1100
#define _CS_XBS5_ILP32_OFF32_LDFLAGS             1101
#define _CS_XBS5_ILP32_OFF32_LIBS                1102
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS           1103
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS             1104
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS            1105
#define _CS_XBS5_ILP32_OFFBIG_LIBS               1106
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS          1107
#define _CS_XBS5_LP64_OFF64_CFLAGS               1108
#define _CS_XBS5_LP64_OFF64_LDFLAGS              1109
#define _CS_XBS5_LP64_OFF64_LIBS                 1110
#define _CS_XBS5_LP64_OFF64_LINTFLAGS            1111
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS             1112
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS            1113
#define _CS_XBS5_LPBIG_OFFBIG_LIBS               1114
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS          1115
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS          1116
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS         1117
#define _CS_POSIX_V6_ILP32_OFF32_LIBS            1118
#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS       1119
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS         1120
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS        1121
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS           1122
#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS      1123
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS           1124
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS          1125
#define _CS_POSIX_V6_LP64_OFF64_LIBS             1126
#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS        1127
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS         1128
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS        1129
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS           1130
#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS      1131
#define _CS_POSIX_V7_ILP32_OFF32_CFLAGS          1132
#define _CS_POSIX_V7_ILP32_OFF32_LDFLAGS         1133
#define _CS_POSIX_V7_ILP32_OFF32_LIBS            1134
#define _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS       1135
#define _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS         1136
#define _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS        1137
#define _CS_POSIX_V7_ILP32_OFFBIG_LIBS           1138
#define _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS      1139
#define _CS_POSIX_V7_LP64_OFF64_CFLAGS           1140
#define _CS_POSIX_V7_LP64_OFF64_LDFLAGS          1141
#define _CS_POSIX_V7_LP64_OFF64_LIBS             1142
#define _CS_POSIX_V7_LP64_OFF64_LINTFLAGS        1143
#define _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS         1144
#define _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS        1145
#define _CS_POSIX_V7_LPBIG_OFFBIG_LIBS           1146
#define _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS      1147
#define _CS_V6_ENV                               1148
#define _CS_V7_ENV                               1149

#endif /* !_BITS_CONFNAME_H */
