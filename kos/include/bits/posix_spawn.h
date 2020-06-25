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
#ifndef _BITS_POSIX_SPAWN_H
#define _BITS_POSIX_SPAWN_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/sched_param.h>
#include <bits/sigset.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Flags to be set in the `posix_spawnattr_t'. */
#if defined(__CRT_KOS) || defined(__CRT_GLC)
#define POSIX_SPAWN_RESETIDS      0x01
#define POSIX_SPAWN_SETPGROUP     0x02
#define POSIX_SPAWN_SETSIGDEF     0x04
#define POSIX_SPAWN_SETSIGMASK    0x08
#define POSIX_SPAWN_SETSCHEDPARAM 0x10
#define POSIX_SPAWN_SETSCHEDULER  0x20
#ifdef __USE_GNU
#define POSIX_SPAWN_USEVFORK 0x40
#endif /* __USE_GNU */
#elif defined(__CRT_CYG)
#define POSIX_SPAWN_RESETIDS      0x01
#define POSIX_SPAWN_SETPGROUP     0x02
#define POSIX_SPAWN_SETSCHEDPARAM 0x04
#define POSIX_SPAWN_SETSCHEDULER  0x08
#define POSIX_SPAWN_SETSIGDEF     0x10
#define POSIX_SPAWN_SETSIGMASK    0x20
#endif /* ... */


/* Data structure to contain attributes for thread creation. */
typedef struct __posix_spawnattr {
#if defined(__CRT_KOS) || defined(__CRT_GLC)
	__UINT16_TYPE__    __flags;
#if __SIZEOF_PID_T__ > 2
	__UINT16_TYPE__    __pad1[(sizeof(__pid_t) - 2) / 2];
#endif /* __SIZEOF_PID_T__ > 2 */
	__pid_t            __pgrp;
	__sigset_t         __sd;
	__sigset_t         __ss;
	struct sched_param __sp;
	int                __policy;
	int                __pad[16];
#elif defined(__CRT_CYG)
	/* TODO: Cygwin structure layout! */
	int __placeholder[64];
#else /* ... */
	int __placeholder[64];
#endif /* !... */
} posix_spawnattr_t;

/* Data structure to contain information about the actions to be
 * performed in the new process with respect to file descriptors. */
#if defined(__CRT_KOS) || defined(__CRT_GLC)
struct __spawn_action;
#endif /* __CRT_KOS || __CRT_GLC */
typedef struct __posix_spawn_file_actions {
#if defined(__CRT_KOS) || defined(__CRT_GLC)
	int                    __allocated;
	int                    __used;
	struct __spawn_action *__actions;
	int                    __pad[16];
#elif defined(__CRT_CYG)
	/* TODO: Cygwin structure layout! */
	int __placeholder[64];
#else /* ... */
	int __placeholder[64];
#endif /* !... */
} posix_spawn_file_actions_t;


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_POSIX_SPAWN_H */
