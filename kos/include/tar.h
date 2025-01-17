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
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/tar.h) */
/* (#) Portability: DragonFly BSD (/include/tar.h) */
/* (#) Portability: FreeBSD       (/include/tar.h) */
/* (#) Portability: GNU C Library (/posix/tar.h) */
/* (#) Portability: GNU Hurd      (/usr/include/tar.h) */
/* (#) Portability: NetBSD        (/include/tar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/tar.h) */
/* (#) Portability: OpenBSD       (/include/tar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/tar.h) */
/* (#) Portability: diet libc     (/include/tar.h) */
/* (#) Portability: libc4/5       (/include/tar.h) */
/* (#) Portability: libc6         (/include/tar.h) */
/* (#) Portability: mintlib       (/include/tar.h) */
/* (#) Portability: musl libc     (/include/tar.h) */
/* (#) Portability: uClibc        (/include/tar.h) */
#ifndef _TAR_H
#define _TAR_H 1

#include <__stdinc.h>
#include <features.h>

/* Compatibility header for newlib:<tar.h>
 * https://github.com/bminor/newlib/blob/master/newlib/libc/include/tar.h
 * Documentation is derived from that same header. */


/* General definitions */
#define TMAGIC   "ustar" /* ustar plus null byte. (s.a. `struct tarhdr::th_ustar') */
#define TMAGLEN  6       /* Length of `TMAGIC'. (s.a. `struct tarhdr::th_ustar') */
#define TVERSION "00"    /* 00 without a null byte. (s.a. `struct tarhdr::th_uvers') */
#define TVERSLEN 2       /* Length of `TVERSION'. (s.a. `struct tarhdr::th_uvers') */

/* Typeflag field definitions (s.a. `struct tarhdr::th_type') */
#ifdef __USE_KOS /* Q: Why? A: look at all of the other constants; they're all prefixed with "T" */
#define TREGTYPE  '0'  /* Regular file. */
#define TAREGTYPE '\0' /* Regular file. */
#define TLNKTYPE  '1'  /* Link. */
#define TSYMTYPE  '2'  /* Symbolic link. */
#define TCHRTYPE  '3'  /* Character special. (ustar-only) */
#define TBLKTYPE  '4'  /* Block special. (ustar-only) */
#define TDIRTYPE  '5'  /* Directory. (ustar-only) */
#define TFIFOTYPE '6'  /* FIFO special. (ustar-only) */
#define TCONTTYPE '7'  /* Reserved. (ustar-only) */
#endif /* __USE_KOS */
#ifndef __USE_KOS_PURE
#define REGTYPE   '0'  /* Regular file. */
#define AREGTYPE  '\0' /* Regular file. */
#define LNKTYPE   '1'  /* Link. */
#define SYMTYPE   '2'  /* Symbolic link. */
#define CHRTYPE   '3'  /* Character special. (ustar-only) */
#define BLKTYPE   '4'  /* Block special. (ustar-only) */
#define DIRTYPE   '5'  /* Directory. (ustar-only) */
#define FIFOTYPE  '6'  /* FIFO special. (ustar-only) */
#define CONTTYPE  '7'  /* Reserved. (ustar-only) */
#endif /* !__USE_KOS_PURE */

/* Mode field bit definitions (octal) (s.a. `struct tarhdr::th_mode') */
#define TSUID   04000 /* Set UID on execution. */
#define TSGID   02000 /* Set GID on execution. */
#if defined(__USE_XOPEN) || (!defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE + 0) < 200112)
#define TSVTX   01000 /* On directories, restricted deletion flag. */
#endif /* __USE_XOPEN || _POSIX_C_SOURCE < 200112 */
#define TUREAD  00400 /* Read by owner. */
#define TUWRITE 00200 /* Write by owner. */
#define TUEXEC  00100 /* Execute/search by owner. */
#define TGREAD  00040 /* Read by group. */
#define TGWRITE 00020 /* Write by group. */
#define TGEXEC  00010 /* Execute/search by group. */
#define TOREAD  00004 /* Read by other. */
#define TOWRITE 00002 /* Write by other. */
#define TOEXEC  00001 /* Execute/search by other. */



/************************************************************************/
/* KOS-specific additions                                               */
/************************************************************************/
#ifdef __USE_KOS

/* Tar filesystem constants. */
#define TBLOCKSIZE  512
#define TBLOCKSHIFT 9 /* == log2(TBLOCKSIZE) */

#ifdef __CC__
__DECL_BEGIN

/* Tar file header */
struct tarhdr {
	char th_filename[100];   /* Absolute filename. */
	char th_mode[8];         /* File mode (octal-ascii). */
	char th_uid[8];          /* File uid (octal-ascii). */
	char th_gid[8];          /* File gid (octal-ascii). */
	char th_size[12];        /* File size (in bytes; octal-ascii). */
	char th_mtime[12];       /* Last-modified time (seconds-since-01.01.1970T00:00; octal-ascii). */
	char th_chksum[8];       /* Checksum (octal-ascii). */
	char th_type[1];         /* File type (s.a. "Typeflag field definitions" above). */
	char th_lnkname[100];    /* [valid_if(th_type == TLNKTYPE || th_type == TSYMTYPE)]
	                          * Linked file filename, or symlink text. */
	/* Everything that follows is [valid_if(th_ustar == TMAGIC)] */
	char th_ustar[TMAGLEN];  /* The string TMAGIC (if ustar format is used) */
	char th_uvers[TVERSLEN]; /* ustar version string ("00") */
	char th_uname[32];       /* Name for `th_uid' */
	char th_gname[32];       /* Name for `th_gid' */
	char th_devmajor[8];     /* [valid_if(TCHRTYPE || TBLKTYPE)] Major number for device. */
	char th_devminor[8];     /* [valid_if(TCHRTYPE || TBLKTYPE)] Minor number for device. */
	char th_filepfx[155];    /* Prefix for `th_filename' */

	/* 12 more bytes of padding go here... (making a total of 512 from the start of this struct) */

	/* File data goes here, in the form of `CEIL_ALIGN(th_size, 512)'
	 * bytes, which are  then followed by  the next  `struct tarhdr'. */
};

__DECL_END
#endif /* __CC__ */
#endif /* __USE_KOS */

#endif /* !_TAR_H */
