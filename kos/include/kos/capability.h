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
#ifndef _KOS_CAPABILITY_H
#define _KOS_CAPABILITY_H 1

#include <__stdinc.h>

/* User program capabilities.
 * Note that linux  has a similar  feature and that  KOS tries to  maintain
 * binary compatibility with linux's capability codes. As such, KOS extends
 * the valid range of capability IDs to negative values, which are used  to
 * encode KOS-specific kernel capability codes. */

/* Capability aliases */
#define CAP_ALLOW_OPEN_BY_HANDLE_AT CAP_DAC_READ_SEARCH /* TODO: Allow use of `open_by_handle_at(2)' */
#define CAP_IGNORE_STICKY_ON_DELETE CAP_FOWNER          /* TODO: Ignore directory `S_ISVTX' during file deletion */
#define CAP_MOUNT                   CAP_SYS_ADMIN       /* Modify mounted file systems. */
#define CAP_MOUNT_DRIVES            CAP_SYS_ADMIN       /* Re-bind `AT_FDDRIVE_ROOT(<letter>)' file handles. */
#define CAP_AT_CHANGE_BTIME         CAP_SYS_TIME        /* Allow use of `AT_CHANGE_BTIME' */

/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __KOS__
	CAP_FIRST_CAP          = -2,   /* Lowest capability in use */
	CAP_DEBUGTRAP          = -2,   /* Allowed to trigger `debugtrap(2)' for the following reasons:
	                                *   - DEBUGTRAP_REASON_FORK, DEBUGTRAP_REASON_VFORK
	                                *   - DEBUGTRAP_REASON_TEXITED, DEBUGTRAP_REASON_PEXITED
	                                *   - DEBUGTRAP_REASON_VFORKDONE DEBUGTRAP_REASON_SC_ENTRY
	                                *   - DEBUGTRAP_REASON_SC_EXIT DEBUGTRAP_REASON_CLONE
	                                *   - DEBUGTRAP_REASON_SWBREAK DEBUGTRAP_REASON_HWBREAK */
	CAP_MMAP_UNINITIALIZED = -1,   /* Allowed to use `MAP_UNINITIALIZED' (when not allowed, that flag is silently ignored) */
#else /* __KOS__ */
	CAP_FIRST_CAP = 0, /* Lowest capability in use */
#endif /* !__KOS__ */
	CAP_CHOWN           = 0,                /* chown() is allowed, no matter what the file's previous user/group was. */
	CAP_DAC_OVERRIDE    = 1,                /* Skip checks for read, write or execute on files */
	CAP_DAC_READ_SEARCH = 2,                /* Skip checks for read and execute on directories */
	CAP_FOWNER          = 3,                /* Ignore  filesystem-uid  checks  (s.a.  `sys_getfsuid()'),   allowing
	                                         * `chmod()', `utime()', etc. on files not owned by the calling thread.
	                                         * Checks  controlled  by `CAP_DAC_OVERRIDE'  and `CAP_DAC_READ_SEARCH'
	                                         * are not affected by this. */
	CAP_FSETID          = 4,                /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
	CAP_KILL            = 5,                /* Skip checks done by `kill(2)' */
	CAP_SETGID          = 6,                /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
	CAP_SETUID          = 7,                /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
	CAP_SETPCAP         = 8,                /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
	CAP_LINUX_IMMUTABLE = 9,                /* TODO: For now, only here as placeholder for fsuid-root transitions */
	CAP_NET_BIND_SERVICE = 10,              /* TODO: Placeholder */
	CAP_NET_BROADCAST   = 11,               /* TODO: Placeholder */
	CAP_NET_ADMIN       = 12,               /* Allow exceeding `socket_default_(rcv|snd)bufmax' */
	CAP_NET_RAW         = 13,               /* TODO: Placeholder */
	CAP_IPC_LOCK        = 14,               /* TODO: Placeholder */
	CAP_IPC_OWNER       = 15,               /* TODO: Placeholder */
	CAP_SYS_MODULE      = 16,               /* Allow use of `KSYSCTL_DRIVER_INSMOD', `KSYSCTL_DRIVER_DELMOD' and `KSYSCTL_DRIVER_SET_LIBRARY_PATH' */
	CAP_SYS_RAWIO       = 17,               /* Gain hardware I/O permissions via `ioperm(2)' and `iopl(2)' */
	CAP_SYS_CHROOT      = 18,               /* TODO: Placeholder */
	CAP_SYS_PTRACE      = 19,               /* Inspect data of arbitrary processes that you're not the parent of. */
	CAP_SYS_PACCT       = 20,               /* TODO: Placeholder */
	CAP_SYS_ADMIN       = 21,               /* A _lot_ of things */
	CAP_SYS_BOOT        = 22,               /* TODO: Placeholder */
	CAP_SYS_NICE        = 23,               /* TODO: Placeholder */
	CAP_SYS_RESOURCE    = 24,               /* Override and set resource limits. */
	CAP_SYS_TIME        = 25,               /* Change the system time. */
	CAP_SYS_TTY_CONFIG  = 26,               /* TODO: Placeholder */
	CAP_MKNOD           = 27,               /* TODO: For now, only here as placeholder for fsuid-root transitions */
	CAP_LEASE           = 28,               /* TODO: Placeholder */
	CAP_AUDIT_WRITE     = 29,               /* TODO: Placeholder */
	CAP_AUDIT_CONTROL   = 30,               /* TODO: Placeholder */
	CAP_SETFCAP	        = 31,               /* TODO: Placeholder */
	CAP_MAC_OVERRIDE    = 32,               /* TODO: For now, only here as placeholder for fsuid-root transitions */
	CAP_MAC_ADMIN       = 33,               /* TODO: Placeholder */
	CAP_SYSLOG          = 34,               /* TODO: Placeholder */
	CAP_WAKE_ALARM      = 35,               /* TODO: Placeholder */
	CAP_BLOCK_SUSPEND   = 36,               /* TODO: Placeholder */
	CAP_AUDIT_READ      = 37,               /* TODO: Placeholder */
	CAP_PERFMON         = 38,               /* TODO: Placeholder */
	CAP_BPF             = 39,               /* TODO: Placeholder */
	CAP_CHECKPOINT_RESTORE = 40,            /* TODO: Placeholder */
	CAP_LAST_CAP = CAP_CHECKPOINT_RESTORE,  /* Greatest positive capability */
	_CAP_COUNT                              /* Greatest positive capability, plus 1 */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __KOS__
#define CAP_FIRST_CAP          CAP_FIRST_CAP          /* Lowest capability in use */
#define CAP_DEBUGTRAP          CAP_DEBUGTRAP          /* Allowed to trigger `debugtrap(2)' for the following reasons:
                                                       *   - DEBUGTRAP_REASON_FORK, DEBUGTRAP_REASON_VFORK
                                                       *   - DEBUGTRAP_REASON_TEXITED, DEBUGTRAP_REASON_PEXITED
                                                       *   - DEBUGTRAP_REASON_VFORKDONE DEBUGTRAP_REASON_SC_ENTRY
                                                       *   - DEBUGTRAP_REASON_SC_EXIT DEBUGTRAP_REASON_CLONE
                                                       *   - DEBUGTRAP_REASON_SWBREAK DEBUGTRAP_REASON_HWBREAK */
#define CAP_MMAP_UNINITIALIZED CAP_MMAP_UNINITIALIZED /* Allowed to use `MAP_UNINITIALIZED' (when not allowed, that flag is silently ignored) */
#else /* __KOS__ */
#define CAP_FIRST_CAP          CAP_FIRST_CAP          /* Lowest capability in use */
#endif /* !__KOS__ */
#define CAP_CHOWN              CAP_CHOWN              /* chown() is allowed, no matter what the file's previous user/group was. */
#define CAP_DAC_OVERRIDE       CAP_DAC_OVERRIDE       /* Skip checks for read, write or execute on files */
#define CAP_DAC_READ_SEARCH    CAP_DAC_READ_SEARCH    /* Skip checks for read and execute on directories */
#define CAP_FOWNER             CAP_FOWNER             /* Ignore  filesystem-uid  checks  (s.a.  `sys_getfsuid()'),   allowing
                                                       * `chmod()', `utime()', etc. on files not owned by the calling thread.
                                                       * Checks  controlled  by `CAP_DAC_OVERRIDE'  and `CAP_DAC_READ_SEARCH'
                                                       * are not affected by this. */
#define CAP_FSETID             CAP_FSETID             /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
#define CAP_KILL               CAP_KILL               /* Skip checks done by `kill(2)' */
#define CAP_SETGID             CAP_SETGID             /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
#define CAP_SETUID             CAP_SETUID             /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
#define CAP_SETPCAP            CAP_SETPCAP            /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
#define CAP_LINUX_IMMUTABLE    CAP_LINUX_IMMUTABLE    /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_NET_BIND_SERVICE   CAP_NET_BIND_SERVICE   /* TODO: Placeholder */
#define CAP_NET_BROADCAST      CAP_NET_BROADCAST      /* TODO: Placeholder */
#define CAP_NET_ADMIN          CAP_NET_ADMIN          /* Allow exceeding `socket_default_(rcv|snd)bufmax' */
#define CAP_NET_RAW            CAP_NET_RAW            /* TODO: Placeholder */
#define CAP_IPC_LOCK           CAP_IPC_LOCK           /* TODO: Placeholder */
#define CAP_IPC_OWNER          CAP_IPC_OWNER          /* TODO: Placeholder */
#define CAP_SYS_MODULE         CAP_SYS_MODULE         /* Allow use of `KSYSCTL_DRIVER_INSMOD', `KSYSCTL_DRIVER_DELMOD' and `KSYSCTL_DRIVER_SET_LIBRARY_PATH' */
#define CAP_SYS_RAWIO          CAP_SYS_RAWIO          /* Gain hardware I/O permissions via `ioperm(2)' and `iopl(2)' */
#define CAP_SYS_CHROOT         CAP_SYS_CHROOT         /* TODO: Placeholder */
#define CAP_SYS_PTRACE         CAP_SYS_PTRACE         /* Inspect data of arbitrary processes that you're not the parent of. */
#define CAP_SYS_PACCT          CAP_SYS_PACCT          /* TODO: Placeholder */
#define CAP_SYS_ADMIN          CAP_SYS_ADMIN          /* A _lot_ of things */
#define CAP_SYS_BOOT           CAP_SYS_BOOT           /* TODO: Placeholder */
#define CAP_SYS_NICE           CAP_SYS_NICE           /* TODO: Placeholder */
#define CAP_SYS_RESOURCE       CAP_SYS_RESOURCE       /* Override and set resource limits. */
#define CAP_SYS_TIME           CAP_SYS_TIME           /* Change the system time. */
#define CAP_SYS_TTY_CONFIG     CAP_SYS_TTY_CONFIG     /* TODO: Placeholder */
#define CAP_MKNOD              CAP_MKNOD              /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_LEASE              CAP_LEASE              /* TODO: Placeholder */
#define CAP_AUDIT_WRITE        CAP_AUDIT_WRITE        /* TODO: Placeholder */
#define CAP_AUDIT_CONTROL      CAP_AUDIT_CONTROL      /* TODO: Placeholder */
#define CAP_SETFCAP            CAP_SETFCAP            /* TODO: Placeholder */
#define CAP_MAC_OVERRIDE       CAP_MAC_OVERRIDE       /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MAC_ADMIN          CAP_MAC_ADMIN          /* TODO: Placeholder */
#define CAP_SYSLOG             CAP_SYSLOG             /* TODO: Placeholder */
#define CAP_WAKE_ALARM         CAP_WAKE_ALARM         /* TODO: Placeholder */
#define CAP_BLOCK_SUSPEND      CAP_BLOCK_SUSPEND      /* TODO: Placeholder */
#define CAP_AUDIT_READ         CAP_AUDIT_READ         /* TODO: Placeholder */
#define CAP_PERFMON            CAP_PERFMON            /* TODO: Placeholder */
#define CAP_BPF                CAP_BPF                /* TODO: Placeholder */
#define CAP_CHECKPOINT_RESTORE CAP_CHECKPOINT_RESTORE /* TODO: Placeholder */
#define CAP_LAST_CAP           CAP_LAST_CAP           /* Greatest positive capability */
#define _CAP_COUNT             _CAP_COUNT             /* Greatest positive capability, plus 1 */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __KOS__
#define CAP_FIRST_CAP          (-2) /* Lowest capability in use */
#define CAP_DEBUGTRAP          (-2) /* Allowed to trigger `debugtrap(2)' for the following reasons:
                                     *   - DEBUGTRAP_REASON_FORK, DEBUGTRAP_REASON_VFORK
                                     *   - DEBUGTRAP_REASON_TEXITED, DEBUGTRAP_REASON_PEXITED
                                     *   - DEBUGTRAP_REASON_VFORKDONE DEBUGTRAP_REASON_SC_ENTRY
                                     *   - DEBUGTRAP_REASON_SC_EXIT DEBUGTRAP_REASON_CLONE
                                     *   - DEBUGTRAP_REASON_SWBREAK DEBUGTRAP_REASON_HWBREAK */
#define CAP_MMAP_UNINITIALIZED (-1) /* Allowed to use `MAP_UNINITIALIZED' (when not allowed, that flag is silently ignored) */
#else /* __KOS__ */
#define CAP_FIRST_CAP          0    /* Lowest capability in use */
#endif /* !__KOS__ */
#define CAP_CHOWN              0    /* chown() is allowed, no matter what the file's previous user/group was. */
#define CAP_DAC_OVERRIDE       1    /* Skip checks for read, write or execute on files */
#define CAP_DAC_READ_SEARCH    2    /* Skip checks for read and execute on directories */
#define CAP_FOWNER             3    /* Ignore  filesystem-uid  checks  (s.a.  `sys_getfsuid()'),   allowing
                                     * `chmod()', `utime()', etc. on files not owned by the calling thread.
                                     * Checks  controlled  by `CAP_DAC_OVERRIDE'  and `CAP_DAC_READ_SEARCH'
                                     * are not affected by this. */
#define CAP_FSETID             4    /* Don't clear `S_ISUID|S_ISGID' when a file is modified */
#define CAP_KILL               5    /* Skip checks done by `kill(2)' */
#define CAP_SETGID             6    /* Allow setting groups ids (`setgid(2)', `setfsgid(2)', `setgroups(2)', ...) */
#define CAP_SETUID             7    /* Allow setting user ids (`setuid(2)', `setfsuid(2)', ...) */
#define CAP_SETPCAP            8    /* capset(): Inheritable caps don't necessarily have to be apart of permitted caps */
#define CAP_LINUX_IMMUTABLE    9    /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_NET_BIND_SERVICE   10   /* TODO: Placeholder */
#define CAP_NET_BROADCAST      11   /* TODO: Placeholder */
#define CAP_NET_ADMIN          12   /* Allow exceeding `socket_default_(rcv|snd)bufmax' */
#define CAP_NET_RAW            13   /* TODO: Placeholder */
#define CAP_IPC_LOCK           14   /* TODO: Placeholder */
#define CAP_IPC_OWNER          15   /* TODO: Placeholder */
#define CAP_SYS_MODULE         16   /* Allow use of `KSYSCTL_DRIVER_INSMOD', `KSYSCTL_DRIVER_DELMOD' and `KSYSCTL_DRIVER_SET_LIBRARY_PATH' */
#define CAP_SYS_RAWIO          17   /* Gain hardware I/O permissions via `ioperm(2)' and `iopl(2)' */
#define CAP_SYS_CHROOT         18   /* TODO: Placeholder */
#define CAP_SYS_PTRACE         19   /* Inspect data of arbitrary processes that you're not the parent of. */
#define CAP_SYS_PACCT          20   /* TODO: Placeholder */
#define CAP_SYS_ADMIN          21   /* A _lot_ of things */
#define CAP_SYS_BOOT           22   /* TODO: Placeholder */
#define CAP_SYS_NICE           23   /* TODO: Placeholder */
#define CAP_SYS_RESOURCE       24   /* Override and set resource limits. */
#define CAP_SYS_TIME           25   /* Change the system time. */
#define CAP_SYS_TTY_CONFIG     26   /* TODO: Placeholder */
#define CAP_MKNOD              27   /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_LEASE              28   /* TODO: Placeholder */
#define CAP_AUDIT_WRITE        29   /* TODO: Placeholder */
#define CAP_AUDIT_CONTROL      30   /* TODO: Placeholder */
#define CAP_SETFCAP            31   /* TODO: Placeholder */
#define CAP_MAC_OVERRIDE       32   /* TODO: For now, only here as placeholder for fsuid-root transitions */
#define CAP_MAC_ADMIN          33   /* TODO: Placeholder */
#define CAP_SYSLOG             34   /* TODO: Placeholder */
#define CAP_WAKE_ALARM         35   /* TODO: Placeholder */
#define CAP_BLOCK_SUSPEND      36   /* TODO: Placeholder */
#define CAP_AUDIT_READ         37   /* TODO: Placeholder */
#define CAP_PERFMON            38   /* TODO: Placeholder */
#define CAP_BPF                39   /* TODO: Placeholder */
#define CAP_CHECKPOINT_RESTORE 40   /* TODO: Placeholder */
#define CAP_LAST_CAP           40   /* Greatest positive capability */
#define _CAP_COUNT             41   /* Greatest positive capability, plus 1 */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Linux-compatible `securebits' flags.
 * These flags can be get/set through use of `prctl(PR_GET_SECUREBITS)' and `prctl(PR_SET_SECUREBITS)'
 * NOTE: Use of the later requires `CAP_ALLOW_PR_SET_SECUREBITS' (== `CAP_SETPCAP') capabilities. */
#define SECBIT_NOROOT                      0x0001 /* Disable special handling for exec() with euid=0 */
#define SECBIT_NOROOT_LOCKED               0x0002 /* Make `SECBIT_NOROOT' immutable (this flag cannot be unset) */
#define SECBIT_NO_SETUID_FIXUP             0x0004 /* Disable changes to capabilities when any of (r|e|s)uid
                                                   * becomes   0   /   all  of   (r|e|s)uid   become  non-0 */
#define SECBIT_NO_SETUID_FIXUP_LOCKED      0x0008 /* Make `SECBIT_NO_SETUID_FIXUP' immutable (this flag cannot be unset) */
#define SECBIT_KEEP_CAPS                   0x0010 /* Don't clear permitted capabilities when all of (r|e|s)uid become non-0 */
#define SECBIT_KEEP_CAPS_LOCKED            0x0020 /* Make `SECBIT_KEEP_CAPS' immutable (this flag cannot be unset) */
#define SECBIT_NO_CAP_AMBIENT_RAISE        0x0040 /* Disallow `PR_CAP_AMBIENT_RAISE' */
#define SECBIT_NO_CAP_AMBIENT_RAISE_LOCKED 0x0080 /* Make `SECBIT_NO_CAP_AMBIENT_RAISE' immutable (this flag cannot be unset) */

#endif /* !_KOS_CAPABILITY_H */
