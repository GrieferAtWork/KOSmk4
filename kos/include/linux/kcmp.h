/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/kcmp.h) */
#ifndef _LINUX_KCMP_H
#define _LINUX_KCMP_H 1

#include <__stdinc.h>

#include <linux/types.h>

__DECL_BEGIN

/* Possible values for `kcmp(2):type' */
/*[[[enum]]]*/
#ifdef __CC__
enum kcmp_type {
	KCMP_FILE,      /* Compare `/proc/[pid1]/fd/[idx1]' with `/proc/[pid2]/fd/[idx2]' */
	KCMP_VM,        /* Compare `task_getmman()' */
	KCMP_FILES,     /* Compare `task_gethandman()' */
	KCMP_FS,        /* Compare `task_getfs()' */
	KCMP_SIGHAND,   /* Compare `task_getsighand_ptr()->sp_hand' */
	KCMP_IO,        /* Not (yet) implemented on KOS */
	KCMP_SYSVSEM,   /* Not (yet) implemented on KOS */
	KCMP_EPOLL_TFD, /* Not (yet) implemented on KOS */
	KCMP_TYPES,     /* # of different compare types */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define KCMP_FILE      KCMP_FILE      /* Compare `/proc/[pid1]/fd/[idx1]' with `/proc/[pid2]/fd/[idx2]' */
#define KCMP_VM        KCMP_VM        /* Compare `task_getmman()' */
#define KCMP_FILES     KCMP_FILES     /* Compare `task_gethandman()' */
#define KCMP_FS        KCMP_FS        /* Compare `task_getfs()' */
#define KCMP_SIGHAND   KCMP_SIGHAND   /* Compare `task_getsighand_ptr()->sp_hand' */
#define KCMP_IO        KCMP_IO        /* Not (yet) implemented on KOS */
#define KCMP_SYSVSEM   KCMP_SYSVSEM   /* Not (yet) implemented on KOS */
#define KCMP_EPOLL_TFD KCMP_EPOLL_TFD /* Not (yet) implemented on KOS */
#define KCMP_TYPES     KCMP_TYPES     /* # of different compare types */
#else /* __COMPILER_PREFERR_ENUMS */
#define KCMP_FILE      0 /* Compare `/proc/[pid1]/fd/[idx1]' with `/proc/[pid2]/fd/[idx2]' */
#define KCMP_VM        1 /* Compare `task_getmman()' */
#define KCMP_FILES     2 /* Compare `task_gethandman()' */
#define KCMP_FS        3 /* Compare `task_getfs()' */
#define KCMP_SIGHAND   4 /* Compare `task_getsighand_ptr()->sp_hand' */
#define KCMP_IO        5 /* Not (yet) implemented on KOS */
#define KCMP_SYSVSEM   6 /* Not (yet) implemented on KOS */
#define KCMP_EPOLL_TFD 7 /* Not (yet) implemented on KOS */
#define KCMP_TYPES     8 /* # of different compare types */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Structure pointed to by `kcmp(type: KCMP_EPOLL_TFD):idx2' */
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("efd")
#pragma push_macro("tfd")
#pragma push_macro("toff")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef efd
#undef tfd
#undef toff
struct kcmp_epoll_slot {
	__u32 efd;  /* [type(fd_t)] epoll handle number */
	__u32 tfd;  /* [type(fd_t)] target handle number */
	__u32 toff; /* ??? */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("toff")
#pragma pop_macro("tfd")
#pragma pop_macro("efd")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END

#endif /* !_LINUX_KCMP_H */
