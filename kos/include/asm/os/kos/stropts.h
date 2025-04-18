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
/*!replace_with_include <asm/os/stropts.h>*/
#ifndef _ASM_OS_KOS_STROPTS_H
#define _ASM_OS_KOS_STROPTS_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>

/* ioctl(2) request codes */
#define __I_NREAD     _IO('S', 1)  /* [int *arg] ??? */
#define __I_PUSH      _IO('S', 2)  /* [char arg[FMNAMESZ+1]] ??? */
#define __I_POP       _IO('S', 3)  /* ??? */
#define __I_LOOK      _IO('S', 4)  /* [char arg[FMNAMESZ+1]] ??? */
#define __I_FLUSH     _IO('S', 5)  /* ??? */
#define __I_SRDOPT    _IO('S', 6)  /* ??? */
#define __I_GRDOPT    _IO('S', 7)  /* [int *arg] ??? */
#define __I_STR       _IO('S', 8)  /* [struct strioctl *arg] ??? */
#define __I_SETSIG    _IO('S', 9)  /* ??? */
#define __I_GETSIG    _IO('S', 10) /* [int *arg] ??? */
#define __I_FIND      _IO('S', 11) /* [char arg[FMNAMESZ+1]] ??? */
#define __I_LINK      _IO('S', 12) /* ??? */
#define __I_UNLINK    _IO('S', 13) /* ??? */
#define __I_PEEK      _IO('S', 15) /* [struct strpeek *arg] ??? */
#define __I_FDINSERT  _IO('S', 16) /* [struct strfdinsert *arg] ??? */
#define __I_SENDFD    _IO('S', 17) /* ??? */
#define __I_RECVFD    _IO('S', 14) /* [struct strrecvfd *arg] ??? */
#define __I_SWROPT    _IO('S', 19) /* ??? */
#define __I_GWROPT    _IO('S', 20) /* ??? */
#define __I_LIST      _IO('S', 21) /* ??? */
#define __I_PLINK     _IO('S', 22) /* ??? */
#define __I_PUNLINK   _IO('S', 23) /* ??? */
#define __I_FLUSHBAND _IO('S', 28) /* ??? */
#define __I_CKBAND    _IO('S', 29) /* ??? */
#define __I_GETBAND   _IO('S', 30) /* ??? */
#define __I_ATMARK    _IO('S', 31) /* ??? */
#define __I_SETCLTIME _IO('S', 32) /* ??? */
#define __I_GETCLTIME _IO('S', 33) /* ??? */
#define __I_CANPUT    _IO('S', 34) /* ??? */

#define __FMNAMESZ 8 /* Used by `I_LOOK' */

/* Flags for the argument used by `I_FLUSH' */
#define __FLUSHR    0x01 /* ??? */
#define __FLUSHW    0x02 /* ??? */
#define __FLUSHRW   0x03 /* ??? */
#define __FLUSHBAND 0x04 /* ??? */

/* Flags for the argument used by `I_SETSIG' */
#define __S_INPUT   0x0001   /* ??? */
#define __S_HIPRI   0x0002   /* ??? */
#define __S_OUTPUT  0x0004   /* ??? */
#define __S_MSG     0x0008   /* ??? */
#define __S_ERROR   0x0010   /* ??? */
#define __S_HANGUP  0x0020   /* ??? */
#define __S_RDNORM  0x0040   /* ??? */
#define __S_RDBAND  0x0080   /* ??? */
#define __S_WRBAND  0x0100   /* ??? */
#define __S_BANDURG 0x0200   /* ??? */

/* Flags for the argument used by `I_PEEK' */
#define __RS_HIPRI 0x01 /* ??? */

/* Flags for the argument used by `I_SRDOPT' */
#define __RNORM     0x0000 /* ??? */
#define __RMSGD     0x0001 /* ??? */
#define __RMSGN     0x0002 /* ??? */
#define __RPROTDAT  0x0004 /* ??? */
#define __RPROTDIS  0x0008 /* ??? */
#define __RPROTNORM 0x0010 /* ??? */
#define __RPROTMASK 0x001C /* ??? */

/* Flags for the argument used by `I_SWROPT' */
#define __SNDZERO 0x001 /* ??? */
#define __SNDPIPE 0x002 /* ??? */

/* Flags for the argument used by `I_ATMARK' */
#define __ANYMARK  0x01 /* ??? */
#define __LASTMARK 0x02 /* ??? */

/* Flags for the argument used by `I_UNLINK' */
#define __MUXID_ALL (-1) /* ??? */

/* Flags used by `getmsg()', `getpmsg()', `putmsg()' and `putpmsg()'. */
#define __MSG_HIPRI 0x01 /* ??? */
#define __MSG_ANY   0x02 /* ??? */
#define __MSG_BAND  0x04 /* ??? */

/* Return values for `getmsg()' and `getpmsg()' */
#define __MORECTL  1 /* ??? */
#define __MOREDATA 2 /* ??? */

#endif /* !_ASM_OS_KOS_STROPTS_H */
