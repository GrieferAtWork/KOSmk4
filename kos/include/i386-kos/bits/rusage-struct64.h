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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_RUSAGE_STRUCT64_H
#define _I386_KOS_BITS_RUSAGE_STRUCT64_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/timeval64.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef rusagex64
#pragma push_macro("rusagex64")
#define __PRIVATE_DID_PUSH_RUSAGEX64
#endif /* rusagex64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "rusage",
	name64:    "rusagex64",
	altname64: "__rusagex64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef rusagex64
#ifndef __x86_64__
#define rusagex64 __rusagex64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_RUSAGE_UTIME      __OFFSET_RUSAGEX64_UTIME
#define __OFFSET_RUSAGE_STIME      __OFFSET_RUSAGEX64_STIME
#define __OFFSET_RUSAGE_MAXRSS     __OFFSET_RUSAGEX64_MAXRSS
#define __OFFSET_RUSAGE_IXRSS      __OFFSET_RUSAGEX64_IXRSS
#define __OFFSET_RUSAGE_IDRSS      __OFFSET_RUSAGEX64_IDRSS
#define __OFFSET_RUSAGE_ISRSS      __OFFSET_RUSAGEX64_ISRSS
#define __OFFSET_RUSAGE_MINFLT     __OFFSET_RUSAGEX64_MINFLT
#define __OFFSET_RUSAGE_MAJFLT     __OFFSET_RUSAGEX64_MAJFLT
#define __OFFSET_RUSAGE_NSWAP      __OFFSET_RUSAGEX64_NSWAP
#define __OFFSET_RUSAGE_INBLOCK    __OFFSET_RUSAGEX64_INBLOCK
#define __OFFSET_RUSAGE_OUBLOCK    __OFFSET_RUSAGEX64_OUBLOCK
#define __OFFSET_RUSAGE_MSGSND     __OFFSET_RUSAGEX64_MSGSND
#define __OFFSET_RUSAGE_MSGRCV     __OFFSET_RUSAGEX64_MSGRCV
#define __OFFSET_RUSAGE_NSIGNALS   __OFFSET_RUSAGEX64_NSIGNALS
#define __OFFSET_RUSAGE_NVCSW      __OFFSET_RUSAGEX64_NVCSW
#define __OFFSET_RUSAGE_NIVCSW     __OFFSET_RUSAGEX64_NIVCSW
#define __SIZEOF_RUSAGE            __SIZEOF_RUSAGEX64
#define __ALIGNOF_RUSAGE           __ALIGNOF_RUSAGEX64
#define __OFFSET_RUSAGE32_UTIME    __OFFSET_RUSAGEX64_UTIME
#define __OFFSET_RUSAGE32_STIME    __OFFSET_RUSAGEX64_STIME
#define __OFFSET_RUSAGE32_MAXRSS   __OFFSET_RUSAGEX64_MAXRSS
#define __OFFSET_RUSAGE32_IXRSS    __OFFSET_RUSAGEX64_IXRSS
#define __OFFSET_RUSAGE32_IDRSS    __OFFSET_RUSAGEX64_IDRSS
#define __OFFSET_RUSAGE32_ISRSS    __OFFSET_RUSAGEX64_ISRSS
#define __OFFSET_RUSAGE32_MINFLT   __OFFSET_RUSAGEX64_MINFLT
#define __OFFSET_RUSAGE32_MAJFLT   __OFFSET_RUSAGEX64_MAJFLT
#define __OFFSET_RUSAGE32_NSWAP    __OFFSET_RUSAGEX64_NSWAP
#define __OFFSET_RUSAGE32_INBLOCK  __OFFSET_RUSAGEX64_INBLOCK
#define __OFFSET_RUSAGE32_OUBLOCK  __OFFSET_RUSAGEX64_OUBLOCK
#define __OFFSET_RUSAGE32_MSGSND   __OFFSET_RUSAGEX64_MSGSND
#define __OFFSET_RUSAGE32_MSGRCV   __OFFSET_RUSAGEX64_MSGRCV
#define __OFFSET_RUSAGE32_NSIGNALS __OFFSET_RUSAGEX64_NSIGNALS
#define __OFFSET_RUSAGE32_NVCSW    __OFFSET_RUSAGEX64_NVCSW
#define __OFFSET_RUSAGE32_NIVCSW   __OFFSET_RUSAGEX64_NIVCSW
#define __SIZEOF_RUSAGE32          __SIZEOF_RUSAGEX64
#define __ALIGNOF_RUSAGE32         __ALIGNOF_RUSAGEX64
#define __OFFSET_RUSAGE64_UTIME    __OFFSET_RUSAGEX64_UTIME
#define __OFFSET_RUSAGE64_STIME    __OFFSET_RUSAGEX64_STIME
#define __OFFSET_RUSAGE64_MAXRSS   __OFFSET_RUSAGEX64_MAXRSS
#define __OFFSET_RUSAGE64_IXRSS    __OFFSET_RUSAGEX64_IXRSS
#define __OFFSET_RUSAGE64_IDRSS    __OFFSET_RUSAGEX64_IDRSS
#define __OFFSET_RUSAGE64_ISRSS    __OFFSET_RUSAGEX64_ISRSS
#define __OFFSET_RUSAGE64_MINFLT   __OFFSET_RUSAGEX64_MINFLT
#define __OFFSET_RUSAGE64_MAJFLT   __OFFSET_RUSAGEX64_MAJFLT
#define __OFFSET_RUSAGE64_NSWAP    __OFFSET_RUSAGEX64_NSWAP
#define __OFFSET_RUSAGE64_INBLOCK  __OFFSET_RUSAGEX64_INBLOCK
#define __OFFSET_RUSAGE64_OUBLOCK  __OFFSET_RUSAGEX64_OUBLOCK
#define __OFFSET_RUSAGE64_MSGSND   __OFFSET_RUSAGEX64_MSGSND
#define __OFFSET_RUSAGE64_MSGRCV   __OFFSET_RUSAGEX64_MSGRCV
#define __OFFSET_RUSAGE64_NSIGNALS __OFFSET_RUSAGEX64_NSIGNALS
#define __OFFSET_RUSAGE64_NVCSW    __OFFSET_RUSAGEX64_NVCSW
#define __OFFSET_RUSAGE64_NIVCSW   __OFFSET_RUSAGEX64_NIVCSW
#define __SIZEOF_RUSAGE64          __SIZEOF_RUSAGEX64
#define __ALIGNOF_RUSAGE64         __ALIGNOF_RUSAGEX64
#define rusagex64                  rusage
#define __rusagex64                rusage
#define __rusage32                 rusage
#define __rusage_alt               rusage
#define _RUSAGE_MATCHES_RUSAGE64 1
#ifdef __USE_KOS
#define rusage32 rusage
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define rusage64   rusage
#define __rusage64 rusage
#else /* __USE_STRUCT64_MACRO */
#define __rusagex64_alt rusage64
#define __rusage64      rusage64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __rusage64 rusage
#endif /* !__USE_TIME64 */
#define __rusage_defined 1
#endif /* __x86_64__ */
/*[[[end]]]*/


#define __OFFSET_RUSAGEX64_UTIME    0
#define __OFFSET_RUSAGEX64_STIME    16
#define __OFFSET_RUSAGEX64_MAXRSS   32
#define __OFFSET_RUSAGEX64_IXRSS    40
#define __OFFSET_RUSAGEX64_IDRSS    48
#define __OFFSET_RUSAGEX64_ISRSS    56
#define __OFFSET_RUSAGEX64_MINFLT   64
#define __OFFSET_RUSAGEX64_MAJFLT   72
#define __OFFSET_RUSAGEX64_NSWAP    80
#define __OFFSET_RUSAGEX64_INBLOCK  88
#define __OFFSET_RUSAGEX64_OUBLOCK  96
#define __OFFSET_RUSAGEX64_MSGSND   104
#define __OFFSET_RUSAGEX64_MSGRCV   112
#define __OFFSET_RUSAGEX64_NSIGNALS 120
#define __OFFSET_RUSAGEX64_NVCSW    128
#define __OFFSET_RUSAGEX64_NIVCSW   136
#define __SIZEOF_RUSAGEX64          144
#define __ALIGNOF_RUSAGEX64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

/* rusage for x86_64 */
struct rusagex64 /*[PREFIX(ru_)]*/ {
	struct __timevalx64 ru_utime;    /* Total amount of user time used. */
	struct __timevalx64 ru_stime;    /* Total amount of system time used. */
	__LONG64_TYPE__     ru_maxrss;   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__LONG64_TYPE__     ru_ixrss;    /* Maximum resident set size (in kilobytes). */
	__LONG64_TYPE__     ru_idrss;    /* Amount of data segment memory used (kilobyte-seconds). */
	__LONG64_TYPE__     ru_isrss;    /* Amount of stack memory used (kilobyte-seconds). */
	__LONG64_TYPE__     ru_minflt;   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__LONG64_TYPE__     ru_majflt;   /* Number of hard page faults (i.e. those that required I/O). */
	__LONG64_TYPE__     ru_nswap;    /* Number of times a process was swapped out of physical memory. */
	__LONG64_TYPE__     ru_inblock;  /* Number of input operations via the file system.
	                                  * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__LONG64_TYPE__     ru_oublock;  /* Number of output operations via the file system. */
	__LONG64_TYPE__     ru_msgsnd;   /* Number of IPC messages sent. */
	__LONG64_TYPE__     ru_msgrcv;   /* Number of IPC messages received. */
	__LONG64_TYPE__     ru_nsignals; /* Number of signals delivered. */
	__LONG64_TYPE__     ru_nvcsw;    /* Number of voluntary context switches, i.e. because the process gave up the
	                                  * process before it had to (usually to wait for some resource to be available). */
	__LONG64_TYPE__     ru_nivcsw;   /* Number of involuntary context switches, i.e. a higher priority process
	                                  * became runnable or the current process used up its time slice. */
};

#ifdef __rusagex64_alt
struct __rusagex64_alt {
	struct __timevalx64 ru_utime;    /* Total amount of user time used. */
	struct __timevalx64 ru_stime;    /* Total amount of system time used. */
	__LONG64_TYPE__     ru_maxrss;   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__LONG64_TYPE__     ru_ixrss;    /* Maximum resident set size (in kilobytes). */
	__LONG64_TYPE__     ru_idrss;    /* Amount of data segment memory used (kilobyte-seconds). */
	__LONG64_TYPE__     ru_isrss;    /* Amount of stack memory used (kilobyte-seconds). */
	__LONG64_TYPE__     ru_minflt;   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__LONG64_TYPE__     ru_majflt;   /* Number of hard page faults (i.e. those that required I/O). */
	__LONG64_TYPE__     ru_nswap;    /* Number of times a process was swapped out of physical memory. */
	__LONG64_TYPE__     ru_inblock;  /* Number of input operations via the file system.
	                                  * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__LONG64_TYPE__     ru_oublock;  /* Number of output operations via the file system. */
	__LONG64_TYPE__     ru_msgsnd;   /* Number of IPC messages sent. */
	__LONG64_TYPE__     ru_msgrcv;   /* Number of IPC messages received. */
	__LONG64_TYPE__     ru_nsignals; /* Number of signals delivered. */
	__LONG64_TYPE__     ru_nvcsw;    /* Number of voluntary context switches, i.e. because the process gave up the
	                                  * process before it had to (usually to wait for some resource to be available). */
	__LONG64_TYPE__     ru_nivcsw;   /* Number of involuntary context switches, i.e. a higher priority process
	                                  * became runnable or the current process used up its time slice. */
};
#undef __rusagex64_alt
#endif /* __rusagex64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS
#undef rusagex64
#endif /* !__USE_KOS */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_RUSAGEX64
#undef __PRIVATE_DID_PUSH_RUSAGEX64
#pragma pop_macro("rusagex64")
#endif /* __PRIVATE_DID_PUSH_RUSAGEX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_RUSAGE_STRUCT64_H */
