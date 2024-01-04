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
#ifndef _I386_KOS_BITS_OS_KOS_RUSAGE32_H
#define _I386_KOS_BITS_OS_KOS_RUSAGE32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/generic/timeval32.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef rusagex32
#pragma push_macro("rusagex32")
#define __PRIVATE_DID_PUSH_RUSAGEX32
#endif /* rusagex32 */
#ifdef rusagex32_64
#pragma push_macro("rusagex32_64")
#define __PRIVATE_DID_PUSH_RUSAGEX32_64
#endif /* rusagex32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "rusage",
	name32:    "rusagex32",
	name64:    "rusagex32_64",
	altname64: "__rusagex32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef rusagex32
#undef rusagex32_64
#if !defined(__i386__) || defined(__x86_64__)
#define rusagex32    __rusagex32
#define rusagex32_64 __rusagex32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `rusagex32_64' as `rusage'
 *   - `rusagex32' as `__rusage32' */
#define rusagex32      __rusage32
#define rusagex32_64   rusage
#define __rusagex32    __rusage32
#define __rusagex32_64 rusage
#define __rusage32     __rusage32
#define __rusage_alt   __rusage32
#ifdef __USE_KOS
#define rusage32 __rusage32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define rusage64   rusage
#define __rusage64 rusage
#else /* __USE_STRUCT64_MACRO */
#define __rusagex32_64_alt rusage64
#define __rusage64         rusage64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __rusage64 rusage
#endif /* !__USE_TIME64 */

#define __OFFSET_RUSAGE_UTIME    __OFFSET_RUSAGEX32_64_UTIME
#define __OFFSET_RUSAGE_STIME    __OFFSET_RUSAGEX32_64_STIME
#define __OFFSET_RUSAGE_MAXRSS   __OFFSET_RUSAGEX32_64_MAXRSS
#define __OFFSET_RUSAGE_IXRSS    __OFFSET_RUSAGEX32_64_IXRSS
#define __OFFSET_RUSAGE_IDRSS    __OFFSET_RUSAGEX32_64_IDRSS
#define __OFFSET_RUSAGE_ISRSS    __OFFSET_RUSAGEX32_64_ISRSS
#define __OFFSET_RUSAGE_MINFLT   __OFFSET_RUSAGEX32_64_MINFLT
#define __OFFSET_RUSAGE_MAJFLT   __OFFSET_RUSAGEX32_64_MAJFLT
#define __OFFSET_RUSAGE_NSWAP    __OFFSET_RUSAGEX32_64_NSWAP
#define __OFFSET_RUSAGE_INBLOCK  __OFFSET_RUSAGEX32_64_INBLOCK
#define __OFFSET_RUSAGE_OUBLOCK  __OFFSET_RUSAGEX32_64_OUBLOCK
#define __OFFSET_RUSAGE_MSGSND   __OFFSET_RUSAGEX32_64_MSGSND
#define __OFFSET_RUSAGE_MSGRCV   __OFFSET_RUSAGEX32_64_MSGRCV
#define __OFFSET_RUSAGE_NSIGNALS __OFFSET_RUSAGEX32_64_NSIGNALS
#define __OFFSET_RUSAGE_NVCSW    __OFFSET_RUSAGEX32_64_NVCSW
#define __OFFSET_RUSAGE_NIVCSW   __OFFSET_RUSAGEX32_64_NIVCSW
#define __SIZEOF_RUSAGE          __SIZEOF_RUSAGEX32_64
#define __ALIGNOF_RUSAGE         __ALIGNOF_RUSAGEX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `rusagex32_64' as `rusage64' or `__rusage64'
 *   - `rusagex32' as `rusage' */
#define rusagex32   rusage
#define __rusage32  rusage
#define __rusagex32 rusage
#ifdef __USE_KOS
#define rusage32 rusage
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __rusagex32_64 rusage64
#define rusagex32_64   rusage64
#define __rusage64     rusage64
#define __rusage_alt   rusage64
#else /* __USE_TIME64 */
#define __rusagex32_64 __rusage64
#define rusagex32_64   __rusage64
#define __rusage64     __rusage64
#define __rusage_alt   __rusage64
#endif /* !__USE_TIME64 */

#define __OFFSET_RUSAGE_UTIME    __OFFSET_RUSAGEX32_UTIME
#define __OFFSET_RUSAGE_STIME    __OFFSET_RUSAGEX32_STIME
#define __OFFSET_RUSAGE_MAXRSS   __OFFSET_RUSAGEX32_MAXRSS
#define __OFFSET_RUSAGE_IXRSS    __OFFSET_RUSAGEX32_IXRSS
#define __OFFSET_RUSAGE_IDRSS    __OFFSET_RUSAGEX32_IDRSS
#define __OFFSET_RUSAGE_ISRSS    __OFFSET_RUSAGEX32_ISRSS
#define __OFFSET_RUSAGE_MINFLT   __OFFSET_RUSAGEX32_MINFLT
#define __OFFSET_RUSAGE_MAJFLT   __OFFSET_RUSAGEX32_MAJFLT
#define __OFFSET_RUSAGE_NSWAP    __OFFSET_RUSAGEX32_NSWAP
#define __OFFSET_RUSAGE_INBLOCK  __OFFSET_RUSAGEX32_INBLOCK
#define __OFFSET_RUSAGE_OUBLOCK  __OFFSET_RUSAGEX32_OUBLOCK
#define __OFFSET_RUSAGE_MSGSND   __OFFSET_RUSAGEX32_MSGSND
#define __OFFSET_RUSAGE_MSGRCV   __OFFSET_RUSAGEX32_MSGRCV
#define __OFFSET_RUSAGE_NSIGNALS __OFFSET_RUSAGEX32_NSIGNALS
#define __OFFSET_RUSAGE_NVCSW    __OFFSET_RUSAGEX32_NVCSW
#define __OFFSET_RUSAGE_NIVCSW   __OFFSET_RUSAGEX32_NIVCSW
#define __SIZEOF_RUSAGE          __SIZEOF_RUSAGEX32
#define __ALIGNOF_RUSAGE         __ALIGNOF_RUSAGEX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_RUSAGE32_UTIME    __OFFSET_RUSAGEX32_UTIME
#define __OFFSET_RUSAGE32_STIME    __OFFSET_RUSAGEX32_STIME
#define __OFFSET_RUSAGE32_MAXRSS   __OFFSET_RUSAGEX32_MAXRSS
#define __OFFSET_RUSAGE32_IXRSS    __OFFSET_RUSAGEX32_IXRSS
#define __OFFSET_RUSAGE32_IDRSS    __OFFSET_RUSAGEX32_IDRSS
#define __OFFSET_RUSAGE32_ISRSS    __OFFSET_RUSAGEX32_ISRSS
#define __OFFSET_RUSAGE32_MINFLT   __OFFSET_RUSAGEX32_MINFLT
#define __OFFSET_RUSAGE32_MAJFLT   __OFFSET_RUSAGEX32_MAJFLT
#define __OFFSET_RUSAGE32_NSWAP    __OFFSET_RUSAGEX32_NSWAP
#define __OFFSET_RUSAGE32_INBLOCK  __OFFSET_RUSAGEX32_INBLOCK
#define __OFFSET_RUSAGE32_OUBLOCK  __OFFSET_RUSAGEX32_OUBLOCK
#define __OFFSET_RUSAGE32_MSGSND   __OFFSET_RUSAGEX32_MSGSND
#define __OFFSET_RUSAGE32_MSGRCV   __OFFSET_RUSAGEX32_MSGRCV
#define __OFFSET_RUSAGE32_NSIGNALS __OFFSET_RUSAGEX32_NSIGNALS
#define __OFFSET_RUSAGE32_NVCSW    __OFFSET_RUSAGEX32_NVCSW
#define __OFFSET_RUSAGE32_NIVCSW   __OFFSET_RUSAGEX32_NIVCSW
#define __SIZEOF_RUSAGE32          __SIZEOF_RUSAGEX32
#define __ALIGNOF_RUSAGE32         __ALIGNOF_RUSAGEX32
#define __OFFSET_RUSAGE64_UTIME    __OFFSET_RUSAGEX32_64_UTIME
#define __OFFSET_RUSAGE64_STIME    __OFFSET_RUSAGEX32_64_STIME
#define __OFFSET_RUSAGE64_MAXRSS   __OFFSET_RUSAGEX32_64_MAXRSS
#define __OFFSET_RUSAGE64_IXRSS    __OFFSET_RUSAGEX32_64_IXRSS
#define __OFFSET_RUSAGE64_IDRSS    __OFFSET_RUSAGEX32_64_IDRSS
#define __OFFSET_RUSAGE64_ISRSS    __OFFSET_RUSAGEX32_64_ISRSS
#define __OFFSET_RUSAGE64_MINFLT   __OFFSET_RUSAGEX32_64_MINFLT
#define __OFFSET_RUSAGE64_MAJFLT   __OFFSET_RUSAGEX32_64_MAJFLT
#define __OFFSET_RUSAGE64_NSWAP    __OFFSET_RUSAGEX32_64_NSWAP
#define __OFFSET_RUSAGE64_INBLOCK  __OFFSET_RUSAGEX32_64_INBLOCK
#define __OFFSET_RUSAGE64_OUBLOCK  __OFFSET_RUSAGEX32_64_OUBLOCK
#define __OFFSET_RUSAGE64_MSGSND   __OFFSET_RUSAGEX32_64_MSGSND
#define __OFFSET_RUSAGE64_MSGRCV   __OFFSET_RUSAGEX32_64_MSGRCV
#define __OFFSET_RUSAGE64_NSIGNALS __OFFSET_RUSAGEX32_64_NSIGNALS
#define __OFFSET_RUSAGE64_NVCSW    __OFFSET_RUSAGEX32_64_NVCSW
#define __OFFSET_RUSAGE64_NIVCSW   __OFFSET_RUSAGEX32_64_NIVCSW
#define __SIZEOF_RUSAGE64          __SIZEOF_RUSAGEX32_64
#define __ALIGNOF_RUSAGE64         __ALIGNOF_RUSAGEX32_64

#define __rusage_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_RUSAGEX32_UTIME       0
#define __OFFSET_RUSAGEX32_STIME       8
#define __OFFSET_RUSAGEX32_MAXRSS      16
#define __OFFSET_RUSAGEX32_IXRSS       20
#define __OFFSET_RUSAGEX32_IDRSS       24
#define __OFFSET_RUSAGEX32_ISRSS       28
#define __OFFSET_RUSAGEX32_MINFLT      32
#define __OFFSET_RUSAGEX32_MAJFLT      36
#define __OFFSET_RUSAGEX32_NSWAP       40
#define __OFFSET_RUSAGEX32_INBLOCK     44
#define __OFFSET_RUSAGEX32_OUBLOCK     48
#define __OFFSET_RUSAGEX32_MSGSND      52
#define __OFFSET_RUSAGEX32_MSGRCV      56
#define __OFFSET_RUSAGEX32_NSIGNALS    60
#define __OFFSET_RUSAGEX32_NVCSW       64
#define __OFFSET_RUSAGEX32_NIVCSW      68
#define __SIZEOF_RUSAGEX32             72
#define __ALIGNOF_RUSAGEX32            __ALIGNOF_INT32__

#define __OFFSET_RUSAGEX32_64_UTIME    0
#define __OFFSET_RUSAGEX32_64_STIME    16
#define __OFFSET_RUSAGEX32_64_MAXRSS   32
#define __OFFSET_RUSAGEX32_64_IXRSS    36
#define __OFFSET_RUSAGEX32_64_IDRSS    40
#define __OFFSET_RUSAGEX32_64_ISRSS    44
#define __OFFSET_RUSAGEX32_64_MINFLT   48
#define __OFFSET_RUSAGEX32_64_MAJFLT   52
#define __OFFSET_RUSAGEX32_64_NSWAP    56
#define __OFFSET_RUSAGEX32_64_INBLOCK  60
#define __OFFSET_RUSAGEX32_64_OUBLOCK  64
#define __OFFSET_RUSAGEX32_64_MSGSND   68
#define __OFFSET_RUSAGEX32_64_MSGRCV   72
#define __OFFSET_RUSAGEX32_64_NSIGNALS 76
#define __OFFSET_RUSAGEX32_64_NVCSW    80
#define __OFFSET_RUSAGEX32_64_NIVCSW   84
#define __SIZEOF_RUSAGEX32_64          88
#define __ALIGNOF_RUSAGEX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

/* 32-bit rusage for i386 */
struct rusagex32 /*[PREFIX(ru_)]*/ {
	struct __timevalx32 ru_utime;    /* ??? */
	struct __timevalx32 ru_stime;    /* ??? */
	__LONG32_TYPE__     ru_maxrss;   /* ??? */
	__LONG32_TYPE__     ru_ixrss;    /* ??? */
	__LONG32_TYPE__     ru_idrss;    /* ??? */
	__LONG32_TYPE__     ru_isrss;    /* ??? */
	__LONG32_TYPE__     ru_minflt;   /* ??? */
	__LONG32_TYPE__     ru_majflt;   /* ??? */
	__LONG32_TYPE__     ru_nswap;    /* ??? */
	__LONG32_TYPE__     ru_inblock;  /* ??? */
	__LONG32_TYPE__     ru_oublock;  /* ??? */
	__LONG32_TYPE__     ru_msgsnd;   /* ??? */
	__LONG32_TYPE__     ru_msgrcv;   /* ??? */
	__LONG32_TYPE__     ru_nsignals; /* ??? */
	__LONG32_TYPE__     ru_nvcsw;    /* ??? */
	__LONG32_TYPE__     ru_nivcsw;   /* ??? */
};

/* 64-bit rusage for i386 */
struct rusagex32_64 /*[PREFIX(ru_)]*/ {
	struct __timevalx32_64 ru_utime;    /* ??? */
	struct __timevalx32_64 ru_stime;    /* ??? */
	__LONG32_TYPE__        ru_maxrss;   /* ??? */
	__LONG32_TYPE__        ru_ixrss;    /* ??? */
	__LONG32_TYPE__        ru_idrss;    /* ??? */
	__LONG32_TYPE__        ru_isrss;    /* ??? */
	__LONG32_TYPE__        ru_minflt;   /* ??? */
	__LONG32_TYPE__        ru_majflt;   /* ??? */
	__LONG32_TYPE__        ru_nswap;    /* ??? */
	__LONG32_TYPE__        ru_inblock;  /* ??? */
	__LONG32_TYPE__        ru_oublock;  /* ??? */
	__LONG32_TYPE__        ru_msgsnd;   /* ??? */
	__LONG32_TYPE__        ru_msgrcv;   /* ??? */
	__LONG32_TYPE__        ru_nsignals; /* ??? */
	__LONG32_TYPE__        ru_nvcsw;    /* ??? */
	__LONG32_TYPE__        ru_nivcsw;   /* ??? */
};

#ifdef __rusagex32_64_alt
struct __rusagex32_64_alt {
	struct __timevalx32_64 ru_utime;    /* ??? */
	struct __timevalx32_64 ru_stime;    /* ??? */
	__LONG32_TYPE__        ru_maxrss;   /* ??? */
	__LONG32_TYPE__        ru_ixrss;    /* ??? */
	__LONG32_TYPE__        ru_idrss;    /* ??? */
	__LONG32_TYPE__        ru_isrss;    /* ??? */
	__LONG32_TYPE__        ru_minflt;   /* ??? */
	__LONG32_TYPE__        ru_majflt;   /* ??? */
	__LONG32_TYPE__        ru_nswap;    /* ??? */
	__LONG32_TYPE__        ru_inblock;  /* ??? */
	__LONG32_TYPE__        ru_oublock;  /* ??? */
	__LONG32_TYPE__        ru_msgsnd;   /* ??? */
	__LONG32_TYPE__        ru_msgrcv;   /* ??? */
	__LONG32_TYPE__        ru_nsignals; /* ??? */
	__LONG32_TYPE__        ru_nvcsw;    /* ??? */
	__LONG32_TYPE__        ru_nivcsw;   /* ??? */
};
#undef __rusagex32_64_alt
#endif /* __rusagex32_64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef rusagex32
#undef rusagex32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_RUSAGEX32_64
#undef __PRIVATE_DID_PUSH_RUSAGEX32_64
#pragma pop_macro("rusagex32_64")
#endif /* __PRIVATE_DID_PUSH_RUSAGEX32_64 */
#ifdef __PRIVATE_DID_PUSH_RUSAGEX32
#undef __PRIVATE_DID_PUSH_RUSAGEX32
#pragma pop_macro("rusagex32")
#endif /* __PRIVATE_DID_PUSH_RUSAGEX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_RUSAGE32_H */
