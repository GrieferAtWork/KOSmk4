/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_STROPTS_H
#define _BITS_STROPTS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <bits/xtitypes.h>


/* Documentation taken from Glibc /usr/include/i386-linux-gnu/bits/stropts.h */
/* Copyright (C) 1998-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* Macros used as `request' argument to `ioctl'. */
#define __SID       ('S' << 8)

#define I_NREAD     (__SID | 1)  /* Counts the number of data bytes in the data block in the first message. */
#define I_PUSH      (__SID | 2)  /* Push STREAMS module onto top of the current STREAM, just below the STREAM head. */
#define I_POP       (__SID | 3)  /* Remove STREAMS module from just below the STREAM head. */
#define I_LOOK      (__SID | 4)  /* Retrieve the name of the module just below the STREAM head and place it in a character string. */
#define I_FLUSH     (__SID | 5)  /* Flush all input and/or output. */
#define I_SRDOPT    (__SID | 6)  /* Sets the read mode. */
#define I_GRDOPT    (__SID | 7)  /* Returns the current read mode setting. */
#define I_STR       (__SID | 8)  /* Construct an internal STREAMS `ioctl' message and send that message downstream. */
#define I_SETSIG    (__SID | 9)  /* Inform the STREAM head that the process wants the SIGPOLL signal issued. */
#define I_GETSIG    (__SID | 10) /* Return the events for which the calling process is currently registered to be sent a SIGPOLL signal. */
#define I_FIND      (__SID | 11) /* Compares the names of all modules currently present in the STREAM to the name pointed to by `arg'. */
#define I_LINK      (__SID | 12) /* Connect two STREAMs. */
#define I_UNLINK    (__SID | 13) /* Disconnects the two STREAMs. */
#define I_PEEK      (__SID | 15) /* Allows a process to retrieve the information in the first message on the STREAM head read queue without taking the message off the queue. */
#define I_FDINSERT  (__SID | 16) /* Create a message from the specified buffer(s), adds information about another STREAM, and send the message downstream. */
#define I_SENDFD    (__SID | 17) /* Requests the STREAM associated with `fildes' to send a message, containing a file pointer, to the STREAM head at the other end of a STREAMS pipe. */
#define I_RECVFD    (__SID | 14) /* Non-EFT definition. */
#define I_SWROPT    (__SID | 19) /* Set the write mode. */
#define I_GWROPT    (__SID | 20) /* Return the current write mode setting. */
#define I_LIST      (__SID | 21) /* List all the module names on the STREAM, up to and including the topmost driver name. */
#define I_PLINK     (__SID | 22) /* Connect two STREAMs with a persistent link. */
#define I_PUNLINK   (__SID | 23) /* Disconnect the two STREAMs that were connected with a persistent link. */
#define I_FLUSHBAND (__SID | 28) /* Flush only band specified. */
#define I_CKBAND    (__SID | 29) /* Check if the message of a given priority band exists on the STREAM head read queue. */
#define I_GETBAND   (__SID | 30) /* Return the priority band of the first message on the STREAM head read queue. */
#define I_ATMARK    (__SID | 31) /* See if the current message on the STREAM head read queue is "marked" by some module downstream. */
#define I_SETCLTIME (__SID | 32) /* Set the time the STREAM head will delay when a STREAM is closing and there is data on the write queues. */
#define I_GETCLTIME (__SID | 33) /* Get current value for closing timeout. */
#define I_CANPUT    (__SID | 34) /* Check if a certain band is writable. */


/* Used in `I_LOOK' request. */
#define FMNAMESZ 8 /* compatibility w/UnixWare/Solaris. */

/* Flush options. */
#define FLUSHR    0x01 /* Flush read queues. */
#define FLUSHW    0x02 /* Flush write queues. */
#define FLUSHRW   0x03 /* Flush read and write queues. */
#ifdef __USE_GNU
#define FLUSHBAND 0x04 /* Flush only specified band. */
#endif /* __USE_GNU */

/* Possible arguments for `I_SETSIG'. */
#define S_INPUT   0x0001 /* A message, other than a high-priority message, has arrived. */
#define S_HIPRI   0x0002 /* A high-priority message is present. */
#define S_OUTPUT  0x0004 /* The write queue for normal data is no longer full. */
#define S_MSG     0x0008 /* A STREAMS signal message that contains the SIGPOLL signal reaches the front of the STREAM head read queue. */
#define S_ERROR   0x0010 /* Notification of an error condition. */
#define S_HANGUP  0x0020 /* Notification of a hangup. */
#define S_RDNORM  0x0040 /* A normal message has arrived. */
#define S_WRNORM  S_OUTPUT
#define S_RDBAND  0x0080 /* A message with a non-zero priority has arrived. */
#define S_WRBAND  0x0100 /* The write queue for a non-zero priority band is no longer full. */
#define S_BANDURG 0x0200 /* When used in conjunction with S_RDBAND, SIGURG is generated instead of SIGPOLL when a priority message reaches the front of the STREAM head read queue. */

/* Option for `I_PEEK'. */
#define RS_HIPRI 0x01 /* Only look for high-priority messages. */

/* Options for `I_SRDOPT'. */
#define RNORM     0x0000 /* Byte-STREAM mode, the default. */
#define RMSGD     0x0001 /* Message-discard mode.   */
#define RMSGN     0x0002 /* Message-nondiscard mode.   */
#define RPROTDAT  0x0004 /* Deliver the control part of a message as data. */
#define RPROTDIS  0x0008 /* Discard the control part of a message, delivering any data part. */
#define RPROTNORM 0x0010 /* Fail `read' with EBADMSG if a message containing a control part is at the front of the STREAM head read queue. */
#ifdef __USE_GNU
#define RPROTMASK 0x001C /* The RPROT bits */
#endif /* __USE_GNU */

/* Possible mode for `I_SWROPT'. */
#define SNDZERO 0x001 /* Send a zero-length message downstream when a `write' of 0 bytes occurs. */
#ifdef __USE_GNU
#define SNDPIPE 0x002 /* Send SIGPIPE on write and putmsg if sd_werror is set. */
#endif /* __USE_GNU */

/* Arguments for `I_ATMARK'. */
#define ANYMARK  0x01 /* Check if the message is marked. */
#define LASTMARK 0x02 /* Check if the message is the last one marked on the queue. */

/* Argument for `I_UNLINK'. */
#ifdef __USE_GNU
#define MUXID_ALL (-1) /* Unlink all STREAMs linked to the STREAM associated with `fildes'. */
#endif /* __USE_GNU */


/* Macros for `getmsg', `getpmsg', `putmsg' and `putpmsg'. */
#define MSG_HIPRI 0x01 /* Send/receive high priority message. */
#define MSG_ANY   0x02 /* Receive any message. */
#define MSG_BAND  0x04 /* Receive message from specified band. */

/* Values returned by getmsg and getpmsg */
#define MORECTL  1 /* More control information is left in message. */
#define MOREDATA 2 /* More data is left in message. */


#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("bandinfo")
#pragma push_macro("bi_pri")
#pragma push_macro("bi_flag")
#pragma push_macro("strbuf")
#pragma push_macro("maxlen")
#pragma push_macro("len")
#pragma push_macro("buf")
#pragma push_macro("strpeek")
#pragma push_macro("ctlbuf")
#pragma push_macro("databuf")
#pragma push_macro("flags")
#pragma push_macro("strfdinsert")
#pragma push_macro("fildes")
#pragma push_macro("offset")
#pragma push_macro("strioctl")
#pragma push_macro("ic_cmd")
#pragma push_macro("ic_timout")
#pragma push_macro("ic_len")
#pragma push_macro("ic_dp")
#pragma push_macro("strrecvfd")
#pragma push_macro("fd")
#pragma push_macro("uid")
#pragma push_macro("gid")
#pragma push_macro("str_mlist")
#pragma push_macro("l_name")
#pragma push_macro("str_list")
#pragma push_macro("sl_modlist")
#pragma push_macro("sl_nmods")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef bandinfo
#undef bi_pri
#undef bi_flag
#undef strbuf
#undef maxlen
#undef len
#undef buf
#undef strpeek
#undef ctlbuf
#undef databuf
#undef flags
#undef strfdinsert
#undef fildes
#undef offset
#undef strioctl
#undef ic_cmd
#undef ic_timout
#undef ic_len
#undef ic_dp
#undef strrecvfd
#undef fd
#undef uid
#undef gid
#undef str_mlist
#undef l_name
#undef str_list
#undef sl_nmods
#undef sl_modlist

/* Structure used for the I_FLUSHBAND ioctl on streams. */
struct bandinfo {
	unsigned char bi_pri;
#if __SIZEOF_INT__ > 1
	unsigned char __bi_pad[(sizeof(int) / sizeof(unsigned char)) - 1];
#endif /* __SIZEOF_INT__ > 1 */
	int           bi_flag;
};

struct strbuf {
	int   maxlen; /* Maximum buffer length. */
	int   len;    /* Length of data. */
	char *buf;    /* Pointer to buffer. */
};

struct strpeek {
	struct strbuf ctlbuf;
	struct strbuf databuf;
	__t_uscalar_t flags; /* UnixWare/Solaris compatibility. */
};

struct strfdinsert {
	struct strbuf ctlbuf;
	struct strbuf databuf;
	__t_uscalar_t flags; /* UnixWare/Solaris compatibility. */
	int           fildes;
	int           offset;
};

struct strioctl {
	int   ic_cmd;
	int   ic_timout;
	int   ic_len;
	char *ic_dp;
};

struct strrecvfd {
	int     fd;
	__uid_t uid;
	__gid_t gid;
	char    __fill[8]; /* UnixWare/Solaris compatibility */
};

struct str_mlist {
	char l_name[FMNAMESZ + 1];
};

struct str_list {
	int               sl_nmods;
	struct str_mlist *sl_modlist;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("sl_nmods")
#pragma pop_macro("sl_modlist")
#pragma pop_macro("str_list")
#pragma pop_macro("l_name")
#pragma pop_macro("str_mlist")
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("fd")
#pragma pop_macro("strrecvfd")
#pragma pop_macro("ic_dp")
#pragma pop_macro("ic_len")
#pragma pop_macro("ic_timout")
#pragma pop_macro("ic_cmd")
#pragma pop_macro("strioctl")
#pragma pop_macro("offset")
#pragma pop_macro("fildes")
#pragma pop_macro("strfdinsert")
#pragma pop_macro("flags")
#pragma pop_macro("databuf")
#pragma pop_macro("ctlbuf")
#pragma pop_macro("strpeek")
#pragma pop_macro("buf")
#pragma pop_macro("len")
#pragma pop_macro("maxlen")
#pragma pop_macro("strbuf")
#pragma pop_macro("bi_flag")
#pragma pop_macro("bi_pri")
#pragma pop_macro("bandinfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_STROPTS_H */
