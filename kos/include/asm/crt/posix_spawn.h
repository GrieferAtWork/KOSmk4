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
#ifndef _ASM_CRT_POSIX_SPAWN_H
#define _ASM_CRT_POSIX_SPAWN_H 1

#include <__crt.h>

/* Figure out if we should use libc's implementation of posix_spawn()
 * If    not,   we   must    implement   _everything_   in   headers! */
#if !(defined(__CRT_HAVE_posix_spawn) &&                       \
      defined(__CRT_HAVE_posix_spawnp) &&                      \
      defined(__CRT_HAVE_posix_spawnattr_init) &&              \
      defined(__CRT_HAVE_posix_spawnattr_destroy) &&           \
      defined(__CRT_HAVE_posix_spawnattr_getsigdefault) &&     \
      defined(__CRT_HAVE_posix_spawnattr_setsigdefault) &&     \
      defined(__CRT_HAVE_posix_spawnattr_getsigmask) &&        \
      defined(__CRT_HAVE_posix_spawnattr_setsigmask) &&        \
      defined(__CRT_HAVE_posix_spawnattr_getflags) &&          \
      defined(__CRT_HAVE_posix_spawnattr_setflags) &&          \
      defined(__CRT_HAVE_posix_spawnattr_getpgroup) &&         \
      defined(__CRT_HAVE_posix_spawnattr_setpgroup) &&         \
      defined(__CRT_HAVE_posix_spawnattr_getschedpolicy) &&    \
      defined(__CRT_HAVE_posix_spawnattr_setschedpolicy) &&    \
      defined(__CRT_HAVE_posix_spawnattr_getschedparam) &&     \
      defined(__CRT_HAVE_posix_spawnattr_setschedparam) &&     \
      defined(__CRT_HAVE_posix_spawn_file_actions_init) &&     \
      defined(__CRT_HAVE_posix_spawn_file_actions_destroy) &&  \
      defined(__CRT_HAVE_posix_spawn_file_actions_addopen) &&  \
      defined(__CRT_HAVE_posix_spawn_file_actions_addclose) && \
      defined(__CRT_HAVE_posix_spawn_file_actions_adddup2))
#undef __CRT_HAVE_posix_spawn
#undef __CRT_HAVE_posix_spawnp
#undef __CRT_HAVE_posix_spawnattr_init
#undef __CRT_HAVE_posix_spawnattr_destroy
#undef __CRT_HAVE_posix_spawnattr_getsigdefault
#undef __CRT_HAVE_posix_spawnattr_setsigdefault
#undef __CRT_HAVE_posix_spawnattr_getsigmask
#undef __CRT_HAVE_posix_spawnattr_setsigmask
#undef __CRT_HAVE_posix_spawnattr_getflags
#undef __CRT_HAVE_posix_spawnattr_setflags
#undef __CRT_HAVE_posix_spawnattr_getpgroup
#undef __CRT_HAVE_posix_spawnattr_setpgroup
#undef __CRT_HAVE_posix_spawnattr_getschedpolicy
#undef __CRT_HAVE_posix_spawnattr_setschedpolicy
#undef __CRT_HAVE_posix_spawnattr_getschedparam
#undef __CRT_HAVE_posix_spawnattr_setschedparam
#undef __CRT_HAVE_posix_spawn_file_actions_init
#undef __CRT_HAVE_posix_spawn_file_actions_destroy
#undef __CRT_HAVE_posix_spawn_file_actions_addopen
#undef __CRT_HAVE_posix_spawn_file_actions_addclose
#undef __CRT_HAVE_posix_spawn_file_actions_adddup2
#undef __POSIX_SPAWN_USE_KOS
#elif defined(__CRT_KOS) || defined(__CRT_GLC)
#define __POSIX_SPAWN_USE_KOS 1
#endif /* ... */

/* Flags to be set in the `posix_spawnattr_t'. */
#ifdef __POSIX_SPAWN_USE_KOS
#define __POSIX_SPAWN_RESETIDS      0x0001 /* Perform 2 calls `seteuid(getuid())' and `setegid(getgid())' */
#define __POSIX_SPAWN_SETPGROUP     0x0002 /* s.a. `posix_spawnattr_setpgroup(3)' */
#define __POSIX_SPAWN_SETSIGDEF     0x0004 /* s.a. `posix_spawnattr_setsigdefault(3)' */
#define __POSIX_SPAWN_SETSIGMASK    0x0008 /* s.a. `posix_spawnattr_setsigmask(3)' */
#define __POSIX_SPAWN_SETSCHEDPARAM 0x0010 /* s.a. `posix_spawnattr_setschedparam(3)' */
#define __POSIX_SPAWN_SETSCHEDULER  0x0020 /* s.a. `posix_spawnattr_setschedpolicy(3)' */
#define __POSIX_SPAWN_USEVFORK      0x0040 /* Ignored */
#ifdef __CRT_KOS
#define __POSIX_SPAWN_NOEXECERR     0x1000 /* Don't propagate exec() error, and leave the
                                            * child as  unreaped with  exit status  `127' */
#endif /* __CRT_KOS */
#elif defined(__CRT_CYG)
#define __POSIX_SPAWN_RESETIDS      0x0001 /* Perform 2 calls `seteuid(getuid())' and `setegid(getgid())' */
#define __POSIX_SPAWN_SETPGROUP     0x0002 /* s.a. `posix_spawnattr_setpgroup(3)' */
#define __POSIX_SPAWN_SETSCHEDPARAM 0x0004 /* s.a. `posix_spawnattr_setschedparam(3)' */
#define __POSIX_SPAWN_SETSCHEDULER  0x0008 /* s.a. `posix_spawnattr_setschedpolicy(3)' */
#define __POSIX_SPAWN_SETSIGDEF     0x0010 /* s.a. `posix_spawnattr_setsigdefault(3)' */
#define __POSIX_SPAWN_SETSIGMASK    0x0020 /* s.a. `posix_spawnattr_setsigmask(3)' */
#endif /* ... */



#endif /* !_ASM_CRT_POSIX_SPAWN_H */
