/* HASH CRC-32:0xe6c23842 */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: OpenSolaris (/usr/src/head/stropts.h) */
/* (#) Portability: libc6       (/include/stropts.h) */
/* (#) Portability: musl libc   (/include/stropts.h) */
#ifndef _STROPTS_H
#define _STROPTS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/types.h>
#include <asm/os/stropts.h>
#include <bits/os/stropts.h>

/* ioctl(2) request codes */
#if !defined(I_NREAD) && defined(__I_NREAD)
#define I_NREAD    __I_NREAD    /* [int *arg] ??? */
#endif /* !I_NREAD && __I_NREAD */
#if !defined(I_PUSH) && defined(__I_PUSH)
#define I_PUSH     __I_PUSH     /* [char arg[FMNAMESZ+1]] ??? */
#endif /* !I_PUSH && __I_PUSH */
#if !defined(I_POP) && defined(__I_POP)
#define I_POP      __I_POP      /* ??? */
#endif /* !I_POP && __I_POP */
#if !defined(I_LOOK) && defined(__I_LOOK)
#define I_LOOK     __I_LOOK     /* [char arg[FMNAMESZ+1]] ??? */
#endif /* !I_LOOK && __I_LOOK */
#if !defined(I_FLUSH) && defined(__I_FLUSH)
#define I_FLUSH    __I_FLUSH    /* ??? */
#endif /* !I_FLUSH && __I_FLUSH */
#if !defined(I_SRDOPT) && defined(__I_SRDOPT)
#define I_SRDOPT   __I_SRDOPT   /* ??? */
#endif /* !I_SRDOPT && __I_SRDOPT */
#if !defined(I_GRDOPT) && defined(__I_GRDOPT)
#define I_GRDOPT   __I_GRDOPT   /* [int *arg] ??? */
#endif /* !I_GRDOPT && __I_GRDOPT */
#if !defined(I_STR) && defined(__I_STR)
#define I_STR      __I_STR      /* [struct strioctl *arg] ??? */
#endif /* !I_STR && __I_STR */
#if !defined(I_SETSIG) && defined(__I_SETSIG)
#define I_SETSIG   __I_SETSIG   /* ??? */
#endif /* !I_SETSIG && __I_SETSIG */
#if !defined(I_GETSIG) && defined(__I_GETSIG)
#define I_GETSIG   __I_GETSIG   /* [int *arg] ??? */
#endif /* !I_GETSIG && __I_GETSIG */
#if !defined(I_FIND) && defined(__I_FIND)
#define I_FIND     __I_FIND     /* [char arg[FMNAMESZ+1]] ??? */
#endif /* !I_FIND && __I_FIND */
#if !defined(I_LINK) && defined(__I_LINK)
#define I_LINK     __I_LINK     /* ??? */
#endif /* !I_LINK && __I_LINK */
#if !defined(I_UNLINK) && defined(__I_UNLINK)
#define I_UNLINK   __I_UNLINK   /* ??? */
#endif /* !I_UNLINK && __I_UNLINK */
#if !defined(I_PEEK) && defined(__I_PEEK)
#define I_PEEK     __I_PEEK     /* [struct strpeek *arg] ??? */
#endif /* !I_PEEK && __I_PEEK */
#if !defined(I_FDINSERT) && defined(__I_FDINSERT)
#define I_FDINSERT __I_FDINSERT /* [struct strfdinsert *arg] ??? */
#endif /* !I_FDINSERT && __I_FDINSERT */
#if !defined(I_SENDFD) && defined(__I_SENDFD)
#define I_SENDFD   __I_SENDFD   /* ??? */
#endif /* !I_SENDFD && __I_SENDFD */
#if !defined(I_RECVFD) && defined(__I_RECVFD)
#define I_RECVFD   __I_RECVFD   /* [struct strrecvfd *arg] ??? */
#endif /* !I_RECVFD && __I_RECVFD */
#if !defined(I_SWROPT) && defined(__I_SWROPT)
#define I_SWROPT    __I_SWROPT    /* ??? */
#endif /* !I_SWROPT && __I_SWROPT */
#if !defined(I_GWROPT) && defined(__I_GWROPT)
#define I_GWROPT    __I_GWROPT    /* ??? */
#endif /* !I_GWROPT && __I_GWROPT */
#if !defined(I_LIST) && defined(__I_LIST)
#define I_LIST      __I_LIST      /* ??? */
#endif /* !I_LIST && __I_LIST */
#if !defined(I_PLINK) && defined(__I_PLINK)
#define I_PLINK     __I_PLINK     /* ??? */
#endif /* !I_PLINK && __I_PLINK */
#if !defined(I_PUNLINK) && defined(__I_PUNLINK)
#define I_PUNLINK   __I_PUNLINK   /* ??? */
#endif /* !I_PUNLINK && __I_PUNLINK */
#if !defined(I_FLUSHBAND) && defined(__I_FLUSHBAND)
#define I_FLUSHBAND __I_FLUSHBAND /* ??? */
#endif /* !I_FLUSHBAND && __I_FLUSHBAND */
#if !defined(I_CKBAND) && defined(__I_CKBAND)
#define I_CKBAND    __I_CKBAND    /* ??? */
#endif /* !I_CKBAND && __I_CKBAND */
#if !defined(I_GETBAND) && defined(__I_GETBAND)
#define I_GETBAND   __I_GETBAND   /* ??? */
#endif /* !I_GETBAND && __I_GETBAND */
#if !defined(I_ATMARK) && defined(__I_ATMARK)
#define I_ATMARK    __I_ATMARK    /* ??? */
#endif /* !I_ATMARK && __I_ATMARK */
#if !defined(I_SETCLTIME) && defined(__I_SETCLTIME)
#define I_SETCLTIME __I_SETCLTIME /* ??? */
#endif /* !I_SETCLTIME && __I_SETCLTIME */
#if !defined(I_GETCLTIME) && defined(__I_GETCLTIME)
#define I_GETCLTIME __I_GETCLTIME /* ??? */
#endif /* !I_GETCLTIME && __I_GETCLTIME */
#if !defined(I_CANPUT) && defined(__I_CANPUT)
#define I_CANPUT    __I_CANPUT    /* ??? */
#endif /* !I_CANPUT && __I_CANPUT */

#if !defined(FMNAMESZ) && defined(__FMNAMESZ)
#define FMNAMESZ __FMNAMESZ /* Used by `I_LOOK' */
#endif /* !FMNAMESZ && __FMNAMESZ */

/* Flags for the argument used by `I_FLUSH' */
#if !defined(FLUSHR) && defined(__FLUSHR)
#define FLUSHR    __FLUSHR    /* ??? */
#endif /* !FLUSHR && __FLUSHR */
#if !defined(FLUSHW) && defined(__FLUSHW)
#define FLUSHW    __FLUSHW    /* ??? */
#endif /* !FLUSHW && __FLUSHW */
#if !defined(FLUSHRW) && defined(__FLUSHRW)
#define FLUSHRW   __FLUSHRW   /* ??? */
#endif /* !FLUSHRW && __FLUSHRW */
#ifdef __USE_GNU
#if !defined(FLUSHBAND) && defined(__FLUSHBAND)
#define FLUSHBAND __FLUSHBAND /* ??? */
#endif /* !FLUSHBAND && __FLUSHBAND */
#endif /* __USE_GNU */

/* Flags for the argument used by `I_SETSIG' */
#if !defined(S_INPUT) && defined(__S_INPUT)
#define S_INPUT   __S_INPUT   /* ??? */
#endif /* !S_INPUT && __S_INPUT */
#if !defined(S_HIPRI) && defined(__S_HIPRI)
#define S_HIPRI   __S_HIPRI   /* ??? */
#endif /* !S_HIPRI && __S_HIPRI */
#if !defined(S_OUTPUT) && defined(__S_OUTPUT)
#define S_OUTPUT  __S_OUTPUT  /* ??? */
#endif /* !S_OUTPUT && __S_OUTPUT */
#if !defined(S_MSG) && defined(__S_MSG)
#define S_MSG     __S_MSG     /* ??? */
#endif /* !S_MSG && __S_MSG */
#if !defined(S_ERROR) && defined(__S_ERROR)
#define S_ERROR   __S_ERROR   /* ??? */
#endif /* !S_ERROR && __S_ERROR */
#if !defined(S_HANGUP) && defined(__S_HANGUP)
#define S_HANGUP  __S_HANGUP  /* ??? */
#endif /* !S_HANGUP && __S_HANGUP */
#if !defined(S_RDNORM) && defined(__S_RDNORM)
#define S_RDNORM  __S_RDNORM  /* ??? */
#endif /* !S_RDNORM && __S_RDNORM */
#if !defined(S_RDBAND) && defined(__S_RDBAND)
#define S_RDBAND  __S_RDBAND  /* ??? */
#endif /* !S_RDBAND && __S_RDBAND */
#if !defined(S_WRBAND) && defined(__S_WRBAND)
#define S_WRBAND  __S_WRBAND  /* ??? */
#endif /* !S_WRBAND && __S_WRBAND */
#if !defined(S_BANDURG) && defined(__S_BANDURG)
#define S_BANDURG __S_BANDURG /* ??? */
#endif /* !S_BANDURG && __S_BANDURG */
#if !defined(S_WRNORM) && defined(__S_OUTPUT)
#define S_WRNORM  __S_OUTPUT  /* Alias */
#endif /* !S_WRNORM && __S_OUTPUT */

/* Flags for the argument used by `I_PEEK' */
#if !defined(RS_HIPRI) && defined(__RS_HIPRI)
#define RS_HIPRI __RS_HIPRI /* ??? */
#endif /* !RS_HIPRI && __RS_HIPRI */

/* Flags for the argument used by `I_SRDOPT' */
#if !defined(RNORM) && defined(__RNORM)
#define RNORM     __RNORM     /* ??? */
#endif /* !RNORM && __RNORM */
#if !defined(RMSGD) && defined(__RMSGD)
#define RMSGD     __RMSGD     /* ??? */
#endif /* !RMSGD && __RMSGD */
#if !defined(RMSGN) && defined(__RMSGN)
#define RMSGN     __RMSGN     /* ??? */
#endif /* !RMSGN && __RMSGN */
#if !defined(RPROTDAT) && defined(__RPROTDAT)
#define RPROTDAT  __RPROTDAT  /* ??? */
#endif /* !RPROTDAT && __RPROTDAT */
#if !defined(RPROTDIS) && defined(__RPROTDIS)
#define RPROTDIS  __RPROTDIS  /* ??? */
#endif /* !RPROTDIS && __RPROTDIS */
#if !defined(RPROTNORM) && defined(__RPROTNORM)
#define RPROTNORM __RPROTNORM /* ??? */
#endif /* !RPROTNORM && __RPROTNORM */
#ifdef __USE_GNU
#if !defined(RPROTMASK) && defined(__RPROTMASK)
#define RPROTMASK __RPROTMASK /* ??? */
#endif /* !RPROTMASK && __RPROTMASK */
#endif /* __USE_GNU */

/* Flags for the argument used by `I_SWROPT' */
#if !defined(SNDZERO) && defined(__SNDZERO)
#define SNDZERO __SNDZERO /* ??? */
#endif /* !SNDZERO && __SNDZERO */
#ifdef __USE_GNU
#if !defined(SNDPIPE) && defined(__SNDPIPE)
#define SNDPIPE __SNDPIPE /* ??? */
#endif /* !SNDPIPE && __SNDPIPE */
#endif /* __USE_GNU */

/* Flags for the argument used by `I_ATMARK' */
#if !defined(ANYMARK) && defined(__ANYMARK)
#define ANYMARK  __ANYMARK  /* ??? */
#endif /* !ANYMARK && __ANYMARK */
#if !defined(LASTMARK) && defined(__LASTMARK)
#define LASTMARK __LASTMARK /* ??? */
#endif /* !LASTMARK && __LASTMARK */

/* Flags for the argument used by `I_UNLINK' */
#ifdef __USE_GNU
#if !defined(MUXID_ALL) && defined(__MUXID_ALL)
#define MUXID_ALL __MUXID_ALL /* ??? */
#endif /* !MUXID_ALL && __MUXID_ALL */
#endif /* __USE_GNU */

/* Flags used by `getmsg()', `getpmsg()', `putmsg()' and `putpmsg()'. */
#if !defined(MSG_HIPRI) && defined(__MSG_HIPRI)
#define MSG_HIPRI __MSG_HIPRI /* ??? */
#endif /* !MSG_HIPRI && __MSG_HIPRI */
#if !defined(MSG_ANY) && defined(__MSG_ANY)
#define MSG_ANY   __MSG_ANY   /* ??? */
#endif /* !MSG_ANY && __MSG_ANY */
#if !defined(MSG_BAND) && defined(__MSG_BAND)
#define MSG_BAND  __MSG_BAND  /* ??? */
#endif /* !MSG_BAND && __MSG_BAND */

/* Return values for `getmsg()' and `getpmsg()' */
#if !defined(MORECTL) && defined(__MORECTL)
#define MORECTL  __MORECTL  /* ??? */
#endif /* !MORECTL && __MORECTL */
#if !defined(MOREDATA) && defined(__MOREDATA)
#define MOREDATA __MOREDATA /* ??? */
#endif /* !MOREDATA && __MOREDATA */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

typedef __t_scalar_t  t_scalar_t;
typedef __t_uscalar_t t_uscalar_t;

__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW,isastream,(__fd_t __fd),(__fd))
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,getmsg,(__fd_t __fd, struct strbuf *__restrict __ctlptr, struct strbuf *__restrict __dataptr, __STDC_INT_AS_UINT_T *__restrict __pflags),(__fd,__ctlptr,__dataptr,__pflags))
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,getpmsg,(__fd_t __fd, struct strbuf *__restrict __ctlptr, struct strbuf *__restrict __dataptr, int *__restrict __bandp, __STDC_INT_AS_UINT_T *__restrict __pflags),(__fd,__ctlptr,__dataptr,__bandp,__pflags))
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,putmsg,(__fd_t __fd, struct strbuf const *__ctlptr, struct strbuf const *__dataptr, __STDC_INT_AS_UINT_T __flags),(__fd,__ctlptr,__dataptr,__flags))
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,putpmsg,(__fd_t __fd, struct strbuf const *__ctlptr, struct strbuf const *__dataptr, __STDC_INT_AS_UINT_T __band, __STDC_INT_AS_UINT_T __flags),(__fd,__ctlptr,__dataptr,__band,__flags))
#if !defined(__fattach_defined) && defined(__CRT_HAVE_fattach)
#define __fattach_defined
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN(2),int,__NOTHROW_RPC_KOS,fattach,(__fd_t __fd, char const *__restrict __path),(__fd,__path))
#endif /* !__fattach_defined && __CRT_HAVE_fattach */
#if !defined(__fdetach_defined) && defined(__CRT_HAVE_fdetach)
#define __fdetach_defined
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC_KOS,fdetach,(char const *__restrict __path),(__path))
#endif /* !__fdetach_defined && __CRT_HAVE_fdetach */
#ifndef __ioctl_defined
#define __ioctl_defined
#ifdef __CRT_HAVE_ioctl
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__LIBC __ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL ioctl)(__fd_t __fd, __ioctl_t __request, ...) __CASMNAME_SAME("ioctl");
#elif defined(__CRT_HAVE___ioctl)
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __ioctl_defined
#endif /* !... */
#endif /* !__ioctl_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_STROPTS_H */
