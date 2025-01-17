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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/arpa/ftp.h) */
/* (#) Portability: DragonFly BSD (/include/arpa/ftp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/arpa/ftp.h) */
/* (#) Portability: FreeBSD       (/include/arpa/ftp.h) */
/* (#) Portability: GNU C Library (/inet/arpa/ftp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/arpa/ftp.h) */
/* (#) Portability: NetBSD        (/include/arpa/ftp.h) */
/* (#) Portability: OpenBSD       (/include/arpa/ftp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/arpa/ftp.h) */
/* (#) Portability: libc4/5       (/include/arpa/ftp.h) */
/* (#) Portability: libc6         (/include/arpa/ftp.h) */
/* (#) Portability: mintlib       (/include/arpa/ftp.h) */
/* (#) Portability: musl libc     (/include/arpa/ftp.h) */
/* (#) Portability: uClibc        (/include/arpa/ftp.h) */
#ifndef _ARPA_FTP_H
#define _ARPA_FTP_H 1

/* ??? */
#define PRELIM    1 /* ??? */
#define COMPLETE  2 /* ??? */
#define CONTINUE  3 /* ??? */
#define TRANSIENT 4 /* ??? */
#define ERROR     5 /* ??? */

/* ??? */
#define TYPE_A 1 /* ASCII */
#define TYPE_E 2 /* EBCDIC */
#define TYPE_I 3 /* Image */
#define TYPE_L 4 /* Local */

#ifdef FTP_NAMES
char *typenames[] = { "0", "ASCII", "EBCDIC", "Image", "Local" };
#endif /* FTP_NAMES */

/* ??? */
#define FORM_N 1 /* Nonprint */
#define FORM_T 2 /* Telnet */
#define FORM_C 3 /* Carriage-control */
#ifdef FTP_NAMES
char *formnames[] = { "0", "Nonprint", "Telnet", "Carriage-control" };
#endif /* FTP_NAMES */

/* ??? */
#define STRU_F 1 /* File */
#define STRU_R 2 /* Record */
#define STRU_P 3 /* Page */
#ifdef FTP_NAMES
char *strunames[] = { "0", "File", "Record", "Page" };
#endif /* FTP_NAMES */

/* ??? */
#define MODE_S 1 /* Stream */
#define MODE_B 2 /* Block */
#define MODE_C 3 /* Compressed */
#ifdef FTP_NAMES
char *modenames[] = { "0", "Stream", "Block", "Compressed" };
#endif /* FTP_NAMES */

/* ??? */
#define REC_ESC '\377' /* ??? */
#define REC_EOR '\001' /* ??? */
#define REC_EOF '\002' /* ??? */

/* ??? */
#define BLK_EOR     0x80 /* ??? */
#define BLK_EOF     0x40 /* ??? */
#define BLK_ERRORS  0x20 /* ??? */
#define BLK_RESTART 0x10 /* ??? */

#define BLK_BYTECOUNT 2 /* ??? */

#endif /* !_ARPA_FTP_H */
