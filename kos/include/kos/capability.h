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
#ifndef _KOS_CAPABILITY_H
#define _KOS_CAPABILITY_H 1

#include <__stdinc.h>

/* User program capabilities.
 * Note that linux has a similar feature and that KOS tries to maintain
 * binary compatibility with linux's capability codes. As such, KOS extends
 * the valid range of capability IDs to negative values, which are used to
 * encode KOS-specific kernel capability codes. */

/* Capability aliases */
#define CAP_ALLOW_OPEN_BY_HANDLE_AT CAP_DAC_READ_SEARCH /* Allow use of `open_by_handle_at(2)' */
#define CAP_ALLOW_LINK_FD           CAP_DAC_READ_SEARCH /* Allow use of `linkat(AT_EMPTY_PATH)' */
#define CAP_IGNORE_STICKY_ON_DELETE CAP_FOWNER          /* Ignore directory `S_ISVTX' during file deletion */
#define CAP_ALLOW_O_NOATIME         CAP_FOWNER          /* Allow use of `O_NOATIME' with any file. */
#define CAP_ALLOW_PR_CAPBSET_DROP   CAP_SETPCAP         /* Allow use of `prctl(PR_CAPBSET_DROP)'. */
#define CAP_ALLOW_PR_SET_SECUREBITS CAP_SETPCAP         /* Allow use of `prctl(PR_SET_SECUREBITS)'. */


/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __KOS__
	CAP_FIRST_CAP = 0,             /* Lowest capability in use */
#endif /* __KOS__ */
	CAP_CHOWN           = 0,       /* chown() is allowed, no matter what the file's previous user/group was. */
	CAP_DAC_OVERRIDE    = 1,       /* Skip checks for read, write or execute on files */
	CAP_DAC_READ_SEARCH = 2,       /* Skip checks for read and execute on directories */
	CAP_FOWNER          = 3,       /* Ignore filesystem-uid checks (s.a. `sys_getfsuid()'), allowing
	                                * `chmod()', `utime()', etc. on files not owned by the calling thread.
	                                * Checks controlled by `CAP_DAC_OVERRIDE' and `CAP_DAC_READ_SEARCH'
	                                * are not affected by this. */
	CAP_FSETID          = 4,       /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
	CAP_KILL            = 5,       /* Skip checks done by `kill(2)' */
	CAP_SETGID          = 6,       /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
	CAP_SETUID          = 7,       /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
	CAP_SETPCAP         = 8,       /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
	CAP_LINUX_IMMUTABLE = 9,       /* TODO: For now, only here as placeholder for fsuid-root transitions */
	CAP_MKNOD           = 27,      /* TODO: For now, only here as placeholder for fsuid-root transitions */
	CAP_MAC_OVERRIDE    = 32,      /* TODO: For now, only here as placeholder for fsuid-root transitions */
	_CAP_COUNT,                    /* Greatest positive capability, plus 1 */
	CAP_LAST_CAP = _CAP_COUNT - 1, /* Greatest positive capability */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __KOS__
#define CAP_FIRST_CAP       CAP_FIRST_CAP       /* Lowest capability in use */
#endif /* __KOS__ */
#define CAP_CHOWN           CAP_CHOWN           /* chown() is allowed, no matter what the file's previous user/group was. */
#define CAP_DAC_OVERRIDE    CAP_DAC_OVERRIDE    /* Skip checks for read, write or execute on files */
#define CAP_DAC_READ_SEARCH CAP_DAC_READ_SEARCH /* Skip checks for read and execute on directories */
#define CAP_FOWNER          CAP_FOWNER          /* Ignore filesystem-uid checks (s.a. `sys_getfsuid()'), allowing
                                                 * `chmod()', `utime()', etc. on files not owned by the calling thread.
                                                 * Checks controlled by `CAP_DAC_OVERRIDE' and `CAP_DAC_READ_SEARCH'
                                                 * are not affected by this. */
#define CAP_FSETID          CAP_FSETID          /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
#define CAP_KILL            CAP_KILL            /* Skip checks done by `kill(2)' */
#define CAP_SETGID          CAP_SETGID          /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
#define CAP_SETUID          CAP_SETUID          /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
#define CAP_SETPCAP         CAP_SETPCAP         /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
#define CAP_LINUX_IMMUTABLE CAP_LINUX_IMMUTABLE /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MKNOD           CAP_MKNOD           /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MAC_OVERRIDE    CAP_MAC_OVERRIDE    /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define _CAP_COUNT          _CAP_COUNT          /* Greatest positive capability, plus 1 */
#define CAP_LAST_CAP        CAP_LAST_CAP        /* Greatest positive capability */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __KOS__
#define CAP_FIRST_CAP       0                /* Lowest capability in use */
#endif /* __KOS__ */
#define CAP_CHOWN           0                /* chown() is allowed, no matter what the file's previous user/group was. */
#define CAP_DAC_OVERRIDE    1                /* Skip checks for read, write or execute on files */
#define CAP_DAC_READ_SEARCH 2                /* Skip checks for read and execute on directories */
#define CAP_FOWNER          3                /* Ignore filesystem-uid checks (s.a. `sys_getfsuid()'), allowing
                                              * `chmod()', `utime()', etc. on files not owned by the calling thread.
                                              * Checks controlled by `CAP_DAC_OVERRIDE' and `CAP_DAC_READ_SEARCH'
                                              * are not affected by this. */
#define CAP_FSETID          4                /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
#define CAP_KILL            5                /* Skip checks done by `kill(2)' */
#define CAP_SETGID          6                /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
#define CAP_SETUID          7                /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
#define CAP_SETPCAP         8                /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
#define CAP_LINUX_IMMUTABLE 9                /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MKNOD           27               /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MAC_OVERRIDE    32               /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define _CAP_COUNT          33               /* Greatest positive capability, plus 1 */
#define CAP_LAST_CAP        (_CAP_COUNT - 1) /* Greatest positive capability */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Linux-compatible `securebits' flags.
 * These flags can be get/set through use of `prctl(PR_GET_SECUREBITS)' and `prctl(PR_SET_SECUREBITS)'
 * NOTE: Use of the later requires `CAP_ALLOW_PR_SET_SECUREBITS' (== `CAP_SETPCAP') capabilities. */
#define SECBIT_NOROOT                 0x0001 /* Disable special handling for exec() with euid=0 */
#define SECBIT_NOROOT_LOCKED          0x0002 /* Make `SECBIT_NOROOT' immutable (this flag cannot be unset) */
#define SECBIT_NO_SETUID_FIXUP        0x0004 /* Disable changes to capabilities when any of (r|e|s)uid
                                              * becomes 0 / all of (r|e|s)uid become non-0 */
#define SECBIT_NO_SETUID_FIXUP_LOCKED 0x0008 /* Make `SECBIT_NO_SETUID_FIXUP' immutable (this flag cannot be unset) */
#define SECBIT_KEEP_CAPS              0x0010 /* Don't clear permitted capabilities when all of (r|e|s)uid become non-0  */
#define SECBIT_KEEP_CAPS_LOCKED       0x0020 /* Make `SECBIT_KEEP_CAPS' immutable (this flag cannot be unset) */



#endif /* !_KOS_CAPABILITY_H */
