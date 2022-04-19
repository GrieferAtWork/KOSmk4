/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/newlib/libc/include/paths.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/paths.h) */
/* (#) Portability: FreeBSD       (/include/paths.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/paths.h) */
/* (#) Portability: NetBSD        (/include/paths.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/paths.h) */
/* (#) Portability: OpenBSD       (/include/paths.h) */
/* (#) Portability: diet libc     (/include/paths.h) */
/* (#) Portability: libc4/5       (/include/paths.h) */
/* (#) Portability: libc6         (/include/paths.h) */
/* (#) Portability: mintlib       (/include/paths.h) */
/* (#) Portability: musl libc     (/include/paths.h) */
/* (#) Portability: uClibc        (/include/paths.h) */
#ifndef _PATHS_H
#define _PATHS_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

/* NOTES:
 *  - _PATH_STDPATH: Standard system utility paths (for root login)
 *  - _PATH_DEFPATH: Standard system utility paths (for normal login)
 */

#ifdef _WIN32
#define _PATH_DEFPATH "C:\\Windows\\system32;C:\\Windows"
#define _PATH_STDPATH "C:\\Windows\\system32;C:\\Windows"
#define _PATH_SYSPATH "C:\\Windows\\system32;C:\\Windows"
#define _PATH_DEVNULL "NUL"
#define _PATH_TTY     "CON"
#define _PATH_CONSOLE "CON"
#else /* _WIN32 */

#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#define _PATH_BSHELL  "/bin/sh"
#define _PATH_CSHELL  "/bin/csh"
#define _PATH_DEFPATH "/bin"
#define _PATH_DEV     "/dev/"
#define _PATH_DEVNULL "/dev/null"
#define _PATH_LASTLOG "/var/log/lastlog"
#define _PATH_MAILDIR "/var/spool/mail/"
#define _PATH_MAN     "/usr/share/man"
#define _PATH_MEM     "/dev/mem"
#define _PATH_MNTTAB  "/etc/fstab"
#define _PATH_MOUNTED "/etc/mtab"
#define _PATH_SHELLS  "/etc/shells"
#define _PATH_STDPATH "/bin:/usr/sbin:/sbin"
#define _PATH_TMP     "/tmp/"
#define _PATH_TTY     "/dev/tty"
#define _PATH_UTMP    "/var/run/utmp"
#define _PATH_VARRUN  "/var/run/"
#define _PATH_VARTMP  "/var/tmp/"
#define _PATH_VI      "/bin/vi"
#define _PATH_WTMP    "/var/log/wtmp"
#elif defined(__linux__)
#define _PATH_DEFPATH  "/usr/bin:/bin"
#define _PATH_STDPATH  "/usr/bin:/bin:/usr/sbin:/sbin"
#define _PATH_BSHELL   "/bin/sh"
#define _PATH_CONSOLE  "/dev/console"
#define _PATH_CSHELL   "/bin/csh"
#define _PATH_DEVDB    "/var/run/dev.db"
#define _PATH_DEVNULL  "/dev/null"
#define _PATH_DRUM     "/dev/drum"
#define _PATH_GSHADOW  "/etc/gshadow"
#define _PATH_KLOG     "/proc/kmsg"
#define _PATH_KMEM     "/dev/kmem"
#define _PATH_LASTLOG  "/var/log/lastlog"
#define _PATH_MAILDIR  "/var/mail"
#define _PATH_MAN      "/usr/share/man"
#define _PATH_MEM      "/dev/mem"
#define _PATH_MNTTAB   "/etc/fstab"
#define _PATH_MOUNTED  "/etc/mtab"
#define _PATH_NOLOGIN  "/etc/nologin"
#define _PATH_PRESERVE "/var/lib"
#define _PATH_RWHODIR  "/var/spool/rwho"
#define _PATH_SENDMAIL "/usr/sbin/sendmail"
#define _PATH_SHADOW   "/etc/shadow"
#define _PATH_SHELLS   "/etc/shells"
#define _PATH_TTY      "/dev/tty"
#define _PATH_UNIX     "/boot/vmlinux"
#define _PATH_UTMP     "/var/run/utmp"
#define _PATH_VI       "/usr/bin/vi"
#define _PATH_WTMP     "/var/log/wtmp"
#define _PATH_DEV      "/dev/"
#define _PATH_TMP      "/tmp/"
#define _PATH_VARDB    "/var/lib/misc/"
#define _PATH_VARRUN   "/var/run/"
#define _PATH_VARTMP   "/var/tmp/"
#elif defined(__KOS__)
#define _PATH_DEFPATH    "/bin:/usr/bin"
#define _PATH_STDPATH    "/bin:/usr/bin:/usr/sbin:/sbin"
#define _PATH_MAILDIR    "/var/mail"         /* Missing */
#define _PATH_MOUNTED    "/proc/self/mounts" /* Supported! */
#define _PATH_VI         "/bin/vi"           /* Supported! */
#define _PATH_BSHELL     "/bin/sh"           /* Supported! */
#define _PATH_CSHELL     "/bin/csh"          /* Missing */
#define _PATH_DEV        "/dev/"             /* Supported! */
#define _PATH_CONSOLE    "/dev/console"      /* Supported! */
#define _PATH_MEM        "/dev/mem"          /* Supported! */
#define _PATH_DEVNULL    "/dev/null"         /* Supported! */
#define _PATH_TTY        "/dev/tty"          /* Supported! */
#define _PATH_DEVZERO    "/dev/zero"         /* Supported! */
#define _PATH_KMEM       "/dev/kmem"         /* Supported! */
#define _PATH_KLOG       "/dev/klog"         /* Supported! */
#define _PATH_PASSWD     "/etc/passwd"       /* Supported! */
#define _PATH_GROUP      "/etc/group"        /* TODO */
#define _PATH_MNTTAB     "/etc/fstab"        /* TODO */
#define _PATH_MAN        "/usr/share/man"    /* Ignored */
#define _PATH_TEXTDOMAIN "/usr/share/locale" /* Supported! */
/*efine _PATH_LASTLOG    "/var/log/lastlog"*/
/*efine _PATH_WTMP       "/var/log/wtmp"*/
#define _PATH_VARRUN     "/var/run/"
/*efine _PATH_UTMP       "/var/run/utmp"*/
#define _PATH_VARTMP     "/var/tmp/"
#define _PATH_TMP        "/tmp/"
#elif defined(__FreeBSD__)
#define _PATH_LOCALBASE     "/usr/local"
#define _PATH_DEFPATH       "/sbin:/bin:/usr/sbin:/usr/bin:" _PATH_LOCALBASE "/sbin:" _PATH_LOCALBASE "/bin"
#define _PATH_STDPATH       "/usr/bin:/bin:/usr/sbin:/sbin"
#define _PATH_SYSPATH       "/sbin:/usr/sbin"
#define _PATH_BSHELL        "/bin/sh"
#define _PATH_CAPABILITY    "/etc/capability"
#define _PATH_CAPABILITY_DB "/etc/capability.db"
#define _PATH_CONSOLE       "/dev/console"
#define _PATH_CP            "/bin/cp"
#define _PATH_CSHELL        "/bin/csh"
#define _PATH_CSMAPPER      "/usr/share/i18n/csmapper"
#define _PATH_DEFTAPE       "/dev/sa0"
#define _PATH_DEVGPIOC      "/dev/gpioc"
#define _PATH_DEVNULL       "/dev/null"
#define _PATH_DEVZERO       "/dev/zero"
#define _PATH_DRUM          "/dev/drum"
#define _PATH_ESDB          "/usr/share/i18n/esdb"
#define _PATH_ETC           "/etc"
#define _PATH_FIRMWARE      "/usr/share/firmware"
#define _PATH_FTPUSERS      "/etc/ftpusers"
#define _PATH_FWMEM         "/dev/fwmem"
#define _PATH_GBDE          "/sbin/gbde"
#define _PATH_GELI          "/sbin/geli"
#define _PATH_HALT          "/sbin/halt"
#define _PATH_IFCONFIG      "/sbin/ifconfig"
#define _PATH_KMEM          "/dev/kmem"
#define _PATH_LIBMAP_CONF   "/etc/libmap.conf"
#define _PATH_LOCALE        "/usr/share/locale"
#define _PATH_LOGIN         "/usr/bin/login"
#define _PATH_MAILDIR       "/var/mail"
#define _PATH_MAN           "/usr/share/man"
#define _PATH_MDCONFIG      "/sbin/mdconfig"
#define _PATH_MEM           "/dev/mem"
#define _PATH_MKSNAP_FFS    "/sbin/mksnap_ffs"
#define _PATH_MOUNT         "/sbin/mount"
#define _PATH_NEWFS         "/sbin/newfs"
#define _PATH_NOLOGIN       "/var/run/nologin"
#define _PATH_RCP           "/bin/rcp"
#define _PATH_REBOOT        "/sbin/reboot"
#define _PATH_RLOGIN        "/usr/bin/rlogin"
#define _PATH_RM            "/bin/rm"
#define _PATH_RSH           "/usr/bin/rsh"
#define _PATH_SENDMAIL      "/usr/sbin/sendmail"
#define _PATH_SHELLS        "/etc/shells"
#define _PATH_TTY           "/dev/tty"
#define _PATH_UFSSUSPEND    "/dev/ufssuspend"
#define _PATH_VI            "/usr/bin/vi"
#define _PATH_WALL          "/usr/bin/wall"
#define _PATH_DEV           "/dev/"
#define _PATH_TMP           "/tmp/"
#define _PATH_VARDB         "/var/db/"
#define _PATH_VARRUN        "/var/run/"
#define _PATH_VARTMP        "/var/tmp/"
#define _PATH_DEVVMM        "/dev/vmm/"
#define _PATH_YP            "/var/yp/"
#define _PATH_UUCPLOCK      "/var/spool/lock/"
#ifdef COMPAT_32BIT
#define _PATH_I18NMODULE "/usr/lib32/i18n"
#else /* COMPAT_32BIT */
#define _PATH_I18NMODULE "/usr/lib/i18n"
#endif /* !COMPAT_32BIT */
#if !defined(__getbootfile_defined) && defined(__CRT_HAVE_getbootfile)
#define __getbootfile_defined
#ifdef __CC__
__SYSDECL_BEGIN
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,getbootfile,(void),())
__SYSDECL_END
#endif /* __CC__ */
#endif /* !__getbootfile_defined && __CRT_HAVE_getbootfile */
#elif defined(__NetBSD__)
#define _PATH_DEFPATH    "/usr/bin:/bin:/usr/pkg/bin:/usr/local/bin"
#define _PATH_STDPATH    "/usr/bin:/bin:/usr/sbin:/sbin:/usr/pkg/bin:/usr/pkg/sbin:/usr/local/bin:/usr/local/sbin"
#define _PATH_AUDIO      "/dev/audio"
#define _PATH_AUDIO0     "/dev/audio0"
#define _PATH_AUDIOCTL   "/dev/audioctl"
#define _PATH_AUDIOCTL0  "/dev/audioctl0"
#define _PATH_BPF        "/dev/bpf"
#define _PATH_CLOCKCTL   "/dev/clockctl"
#define _PATH_CONSOLE    "/dev/console"
#define _PATH_CONSTTY    "/dev/constty"
#define _PATH_CPUCTL     "/dev/cpuctl"
#define _PATH_CSMAPPER   "/usr/share/i18n/csmapper"
#define _PATH_DEFTAPE    "/dev/nrst0"
#define _PATH_DEVCDB     "/var/run/dev.cdb"
#define _PATH_DEVDB      "/var/run/dev.db"
#define _PATH_DEVNULL    "/dev/null"
#define _PATH_DEVZERO    "/dev/zero"
#define _PATH_DRUM       "/dev/drum"
#define _PATH_ESDB       "/usr/share/i18n/esdb"
#define _PATH_FTPUSERS   "/etc/ftpusers"
#define _PATH_GETTYTAB   "/etc/gettytab"
#define _PATH_I18NMODULE "/usr/lib/i18n"
#define _PATH_ICONV      "/usr/share/i18n/iconv"
#define _PATH_KMEM       "/dev/kmem"
#define _PATH_KSYMS      "/dev/ksyms"
#define _PATH_KVMDB      "/var/db/kvm.db"
#define _PATH_LOCALE     "/usr/share/locale"
#define _PATH_MAILDIR    "/var/mail"
#define _PATH_MAN        "/usr/share/man"
#define _PATH_MEM        "/dev/mem"
#define _PATH_MIXER      "/dev/mixer"
#define _PATH_MIXER0     "/dev/mixer0"
#define _PATH_NOLOGIN    "/etc/nologin"
#define _PATH_POWER      "/dev/power"
#define _PATH_PRINTCAP   "/etc/printcap"
#define _PATH_PUD        "/dev/pud"
#define _PATH_PUFFS      "/dev/puffs"
#define _PATH_RANDOM     "/dev/random"
#define _PATH_SENDMAIL   "/usr/sbin/sendmail"
#define _PATH_SHELLS     "/etc/shells"
#define _PATH_SKEYKEYS   "/etc/skeykeys"
#define _PATH_SOUND      "/dev/sound"
#define _PATH_SOUND0     "/dev/sound0"
#define _PATH_SYSMON     "/dev/sysmon"
#define _PATH_TTY        "/dev/tty"
#define _PATH_UNIX       "/netbsd"
#define _PATH_URANDOM    "/dev/urandom"
#define _PATH_VIDEO      "/dev/video"
#define _PATH_VIDEO0     "/dev/video0"
#define _PATH_WATCHDOG   "/dev/watchdog"
#define _PATH_DEV        "/dev/"
#define _PATH_DEV_PTS    "/dev/pts/"
#define _PATH_EMUL_AOUT  "/emul/aout/"
#define _PATH_TMP        "/tmp/"
#define _PATH_VARDB      "/var/db/"
#define _PATH_VARRUN     "/var/run/"
#define _PATH_VARTMP     "/var/tmp/"
#define _PATH_BSHELL     "/bin/sh"
#define _PATH_CSHELL     "/bin/csh"
#define _PATH_VI         "/usr/bin/vi"
#elif defined(__OpenBSD__)
#define _PATH_DEFPATH  "/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:/usr/local/bin:/usr/local/sbin"
#define _PATH_STDPATH  "/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:/usr/local/bin:/usr/local/sbin"
#define _PATH_BSHELL   "/bin/sh"
#define _PATH_CONSOLE  "/dev/console"
#define _PATH_CSHELL   "/bin/csh"
#define _PATH_DEFTAPE  "/dev/rst0"
#define _PATH_DEVDB    "/var/run/dev.db"
#define _PATH_DEVNULL  "/dev/null"
#define _PATH_FSIRAND  "/sbin/fsirand"
#define _PATH_KLOG     "/dev/klog"
#define _PATH_KMEM     "/dev/kmem"
#define _PATH_KSHELL   "/bin/ksh"
#define _PATH_KSYMS    "/dev/ksyms"
#define _PATH_KVMDB    "/var/db/kvm_bsd.db"
#define _PATH_LOCALE   "/usr/share/locale"
#define _PATH_LOGCONF  "/etc/syslog.conf"
#define _PATH_LOGPID   "/var/run/syslog.pid"
#define _PATH_MAILDIR  "/var/mail"
#define _PATH_MAN      "/usr/share/man"
#define _PATH_MEM      "/dev/mem"
#define _PATH_NOLOGIN  "/etc/nologin"
#define _PATH_RSH      "/usr/bin/ssh"
#define _PATH_SENDMAIL "/usr/sbin/sendmail"
#define _PATH_SHELLS   "/etc/shells"
#define _PATH_TTY      "/dev/tty"
#define _PATH_UNIX     "/bsd"
#define _PATH_VI       "/usr/bin/vi"
#define _PATH_BOOTDIR  "/usr/mdec/"
#define _PATH_DEV      "/dev/"
#define _PATH_DEVFD    "/dev/fd/"
#define _PATH_TMP      "/tmp/"
#define _PATH_UUCPLOCK "/var/spool/lock/"
#define _PATH_VARDB    "/var/db/"
#define _PATH_VAREMPTY "/var/empty/"
#define _PATH_VARRUN   "/var/run/"
#define _PATH_VARTMP   "/var/tmp/"
#endif /* ... */


/************************************************************************/
/* Fallbacks // defaults                                                */
/************************************************************************/

/* $PATH */
#ifndef _PATH_DEFPATH
#define _PATH_DEFPATH "/usr/bin:/bin"
#endif /* !_PATH_DEFPATH */
#ifndef _PATH_STDPATH
#define _PATH_STDPATH "/usr/bin:/bin:/usr/sbin:/sbin"
#endif /* !_PATH_STDPATH */

/* /bin */
#ifndef _PATH_BSHELL
#define _PATH_BSHELL "/bin/sh"
#endif /* !_PATH_BSHELL */
#ifndef _PATH_VI
#define _PATH_VI "/usr/bin/vi"
#endif /* !_PATH_VI */
#ifndef _PATH_CP
#define _PATH_CP "/bin/cp"
#endif /* !_PATH_CP */
#ifndef _PATH_RM
#define _PATH_RM "/bin/rm"
#endif /* !_PATH_RM */
#ifndef _PATH_LN
#define _PATH_LN "/bin/ln"
#endif /* !_PATH_LN */
#ifndef _PATH_CAT
#define _PATH_CAT "/bin/cat"
#endif /* !_PATH_CAT */
#ifndef _PATH_RMDIR
#define _PATH_RMDIR "/bin/rmdir"
#endif /* !_PATH_RMDIR */
#ifndef _PATH_MKDIR
#define _PATH_MKDIR "/bin/mkdir"
#endif /* !_PATH_MKDIR */
#ifndef _PATH_LOGIN
#define _PATH_LOGIN "/bin/login"
#endif /* !_PATH_LOGIN */


/* /dev */
#ifndef _PATH_DEV
#define _PATH_DEV "/dev/"
#endif /* !_PATH_DEV */
#ifndef _PATH_CONSOLE
#define _PATH_CONSOLE _PATH_DEV "console"
#endif /* !_PATH_CONSOLE */
#ifndef _PATH_MEM
#define _PATH_MEM _PATH_DEV "mem"
#endif /* !_PATH_MEM */
#ifndef _PATH_DEVNULL
#define _PATH_DEVNULL _PATH_DEV "null"
#endif /* !_PATH_DEVNULL */
#ifndef _PATH_TTY
#define _PATH_TTY _PATH_DEV "tty"
#endif /* !_PATH_TTY */
#ifndef _PATH_DEVZERO
#define _PATH_DEVZERO _PATH_DEV "zero"
#endif /* !_PATH_DEVZERO */

/* /tmp */
#ifndef _PATH_TMP
#define _PATH_TMP "/tmp/"
#endif /* !_PATH_TMP */

/* /var */
#ifndef _PATH_VARTMP
#define _PATH_VARTMP "/var/tmp/"
#endif /* !_PATH_VARTMP */
#ifndef _PATH_VARRUN
#define _PATH_VARRUN "/var/run/"
#endif /* !_PATH_VARRUN */
#ifndef _PATH_MAILDIR
#define _PATH_MAILDIR "/var/mail"
#endif /* !_PATH_MAILDIR */

/* /etc */
#ifndef _PATH_PASSWD
#define _PATH_PASSWD "/etc/passwd"
#endif /* !_PATH_PASSWD */
#ifndef _PATH_GROUP
#define _PATH_GROUP "/etc/group"
#endif /* !_PATH_GROUP */
#ifndef _PATH_SHADOW
#define _PATH_SHADOW "/etc/shadow"
#endif /* !_PATH_SHADOW */
#ifndef _PATH_SHELLS
#define _PATH_SHELLS "/etc/shells"
#endif /* !_PATH_SHELLS */
#ifndef _PATH_GSHADOW
#define _PATH_GSHADOW "/etc/gshadow"
#endif /* !_PATH_GSHADOW */
#ifndef _PATH_UTMP
#define _PATH_UTMP "/var/run/utmp"
#endif /* !_PATH_UTMP */
#ifndef _PATH_WTMP
#define _PATH_WTMP "/var/log/wtmp"
#endif /* !_PATH_WTMP */

/* .../share */
#ifndef _PATH_MAN
#define _PATH_MAN "/usr/share/man"
#endif /* !_PATH_MAN */

#endif /* !_WIN32 */


/************************************************************************/
/* Aliases                                                              */
/************************************************************************/
#ifdef __USE_BSD
#if !defined(UTMP_FILE) && defined(_PATH_UTMP)
#define UTMP_FILE _PATH_UTMP
#endif /* !UTMP_FILE && _PATH_UTMP */
#if !defined(WTMP_FILE) && defined(_PATH_WTMP)
#define WTMP_FILE _PATH_WTMP
#endif /* !WTMP_FILE && _PATH_WTMP */
#endif /* __USE_BSD */
#if !defined(_PATH_UTMPX) && defined(_PATH_UTMP)
#define _PATH_UTMPX _PATH_UTMP
#endif /* !_PATH_UTMPX && _PATH_UTMP */
#if !defined(_PATH_WTMPX) && defined(_PATH_WTMP)
#define _PATH_WTMPX _PATH_WTMP
#endif /* !_PATH_WTMPX && _PATH_WTMP */


#endif /* !_PATHS_H */
