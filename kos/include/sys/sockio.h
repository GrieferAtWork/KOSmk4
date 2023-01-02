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
/* (#) Portability: DragonFly BSD (/sys/sys/sockio.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/sockio.h) */
/* (#) Portability: FreeBSD       (/sys/sys/sockio.h) */
/* (#) Portability: NetBSD        (/sys/sys/sockio.h) */
/* (#) Portability: OpenBSD       (/sys/sys/sockio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sockio.h) */
#ifndef _SYS_SOCKIO_H
#define _SYS_SOCKIO_H 1

#include <__stdinc.h>

#include <asm/os/socket-ioctls.h>
#include <sys/ioccom.h>

/* socket i/o controls */
#if !defined(SIOCSHIWAT) && defined(__SIOCSHIWAT)
#define SIOCSHIWAT __SIOCSHIWAT /* [int *arg] ... */
#endif /* !SIOCSHIWAT && __SIOCSHIWAT */
#if !defined(SIOCGHIWAT) && defined(__SIOCGHIWAT)
#define SIOCGHIWAT __SIOCGHIWAT /* [int *arg] ... */
#endif /* !SIOCGHIWAT && __SIOCGHIWAT */
#if !defined(SIOCSLOWAT) && defined(__SIOCSLOWAT)
#define SIOCSLOWAT __SIOCSLOWAT /* [int *arg] ... */
#endif /* !SIOCSLOWAT && __SIOCSLOWAT */
#if !defined(SIOCGLOWAT) && defined(__SIOCGLOWAT)
#define SIOCGLOWAT __SIOCGLOWAT /* [int *arg] ... */
#endif /* !SIOCGLOWAT && __SIOCGLOWAT */
#if !defined(SIOCATMARK) && defined(__SIOCATMARK)
#define SIOCATMARK __SIOCATMARK /* ... */
#endif /* !SIOCATMARK && __SIOCATMARK */
#if !defined(SIOCSPGRP) && defined(__SIOCSPGRP)
#define SIOCSPGRP  __SIOCSPGRP  /* ... */
#endif /* !SIOCSPGRP && __SIOCSPGRP */
#if !defined(SIOCGPGRP) && defined(__SIOCGPGRP)
#define SIOCGPGRP  __SIOCGPGRP  /* ... */
#endif /* !SIOCGPGRP && __SIOCGPGRP */

#if !defined(SIOCADDRT) && defined(__SIOCADDRT)
#define SIOCADDRT __SIOCADDRT /* ??? */
#endif /* !SIOCADDRT && __SIOCADDRT */
#if !defined(SIOCDELRT) && defined(__SIOCDELRT)
#define SIOCDELRT __SIOCDELRT /* ??? */
#endif /* !SIOCDELRT && __SIOCDELRT */

#if !defined(SIOCSIFADDR) && defined(__SIOCSIFADDR)
#define SIOCSIFADDR        __SIOCSIFADDR        /* ??? */
#endif /* !SIOCSIFADDR && __SIOCSIFADDR */
#if !defined(SIOCGIFADDR) && defined(__SIOCGIFADDR)
#define SIOCGIFADDR        __SIOCGIFADDR        /* ??? */
#endif /* !SIOCGIFADDR && __SIOCGIFADDR */
#if !defined(SIOCSIFDSTADDR) && defined(__SIOCSIFDSTADDR)
#define SIOCSIFDSTADDR     __SIOCSIFDSTADDR     /* ??? */
#endif /* !SIOCSIFDSTADDR && __SIOCSIFDSTADDR */
#if !defined(SIOCGIFDSTADDR) && defined(__SIOCGIFDSTADDR)
#define SIOCGIFDSTADDR     __SIOCGIFDSTADDR     /* ??? */
#endif /* !SIOCGIFDSTADDR && __SIOCGIFDSTADDR */
#if !defined(SIOCSIFFLAGS) && defined(__SIOCSIFFLAGS)
#define SIOCSIFFLAGS       __SIOCSIFFLAGS       /* ??? */
#endif /* !SIOCSIFFLAGS && __SIOCSIFFLAGS */
#if !defined(SIOCGIFFLAGS) && defined(__SIOCGIFFLAGS)
#define SIOCGIFFLAGS       __SIOCGIFFLAGS       /* ??? */
#endif /* !SIOCGIFFLAGS && __SIOCGIFFLAGS */
#if !defined(SIOCSIFMEM) && defined(__SIOCSIFMEM)
#define SIOCSIFMEM         __SIOCSIFMEM         /* ??? */
#endif /* !SIOCSIFMEM && __SIOCSIFMEM */
#if !defined(SIOCGIFMEM) && defined(__SIOCGIFMEM)
#define SIOCGIFMEM         __SIOCGIFMEM         /* ??? */
#endif /* !SIOCGIFMEM && __SIOCGIFMEM */
#if !defined(SIOCGIFCONF) && defined(__SIOCGIFCONF)
#define SIOCGIFCONF        __SIOCGIFCONF        /* ??? */
#endif /* !SIOCGIFCONF && __SIOCGIFCONF */
#if !defined(SIOCSIFMTU) && defined(__SIOCSIFMTU)
#define SIOCSIFMTU         __SIOCSIFMTU         /* ??? */
#endif /* !SIOCSIFMTU && __SIOCSIFMTU */
#if !defined(SIOCGIFMTU) && defined(__SIOCGIFMTU)
#define SIOCGIFMTU         __SIOCGIFMTU         /* ??? */
#endif /* !SIOCGIFMTU && __SIOCGIFMTU */

#if !defined(SIOCGIFBRDADDR) && defined(__SIOCGIFBRDADDR)
#define SIOCGIFBRDADDR     __SIOCGIFBRDADDR     /* ??? */
#endif /* !SIOCGIFBRDADDR && __SIOCGIFBRDADDR */
#if !defined(SIOCSIFBRDADDR) && defined(__SIOCSIFBRDADDR)
#define SIOCSIFBRDADDR     __SIOCSIFBRDADDR     /* ??? */
#endif /* !SIOCSIFBRDADDR && __SIOCSIFBRDADDR */
#if !defined(SIOCGIFNETMASK) && defined(__SIOCGIFNETMASK)
#define SIOCGIFNETMASK     __SIOCGIFNETMASK     /* ??? */
#endif /* !SIOCGIFNETMASK && __SIOCGIFNETMASK */
#if !defined(SIOCSIFNETMASK) && defined(__SIOCSIFNETMASK)
#define SIOCSIFNETMASK     __SIOCSIFNETMASK     /* ??? */
#endif /* !SIOCSIFNETMASK && __SIOCSIFNETMASK */
#if !defined(SIOCGIFMETRIC) && defined(__SIOCGIFMETRIC)
#define SIOCGIFMETRIC      __SIOCGIFMETRIC      /* ??? */
#endif /* !SIOCGIFMETRIC && __SIOCGIFMETRIC */
#if !defined(SIOCSIFMETRIC) && defined(__SIOCSIFMETRIC)
#define SIOCSIFMETRIC      __SIOCSIFMETRIC      /* ??? */
#endif /* !SIOCSIFMETRIC && __SIOCSIFMETRIC */

#if !defined(SIOCSARP) && defined(__SIOCSARP)
#define SIOCSARP __SIOCSARP /* ??? */
#endif /* !SIOCSARP && __SIOCSARP */
#if !defined(SIOCGARP) && defined(__SIOCGARP)
#define SIOCGARP __SIOCGARP /* ??? */
#endif /* !SIOCGARP && __SIOCGARP */
#if !defined(SIOCDARP) && defined(__SIOCDARP)
#define SIOCDARP __SIOCDARP /* ??? */
#endif /* !SIOCDARP && __SIOCDARP */
#if !defined(SIOCUPPER) && defined(__SIOCUPPER)
#define SIOCUPPER    __SIOCUPPER    /* [struct ifreq *arg] ... */
#endif /* !SIOCUPPER && __SIOCUPPER */
#if !defined(SIOCLOWER) && defined(__SIOCLOWER)
#define SIOCLOWER    __SIOCLOWER    /* [struct ifreq *arg] ... */
#endif /* !SIOCLOWER && __SIOCLOWER */
#if !defined(SIOCSETSYNC) && defined(__SIOCSETSYNC)
#define SIOCSETSYNC  __SIOCSETSYNC  /* [struct ifreq *arg] ... */
#endif /* !SIOCSETSYNC && __SIOCSETSYNC */
#if !defined(SIOCGETSYNC) && defined(__SIOCGETSYNC)
#define SIOCGETSYNC  __SIOCGETSYNC  /* [struct ifreq *arg] ... */
#endif /* !SIOCGETSYNC && __SIOCGETSYNC */
#if !defined(SIOCSSDSTATS) && defined(__SIOCSSDSTATS)
#define SIOCSSDSTATS __SIOCSSDSTATS /* [struct ifreq *arg] ... */
#endif /* !SIOCSSDSTATS && __SIOCSSDSTATS */
#if !defined(SIOCSSESTATS) && defined(__SIOCSSESTATS)
#define SIOCSSESTATS __SIOCSSESTATS /* [struct ifreq *arg] ... */
#endif /* !SIOCSSESTATS && __SIOCSSESTATS */
#if !defined(SIOCSPROMISC) && defined(__SIOCSPROMISC)
#define SIOCSPROMISC __SIOCSPROMISC /* [int *arg] ... */
#endif /* !SIOCSPROMISC && __SIOCSPROMISC */
#if !defined(SIOCADDMULTI) && defined(__SIOCADDMULTI)
#define SIOCADDMULTI       __SIOCADDMULTI       /* ??? */
#endif /* !SIOCADDMULTI && __SIOCADDMULTI */
#if !defined(SIOCDELMULTI) && defined(__SIOCDELMULTI)
#define SIOCDELMULTI       __SIOCDELMULTI       /* ??? */
#endif /* !SIOCDELMULTI && __SIOCDELMULTI */

#if !defined(SIOCFDRESET) && defined(__SIOCFDRESET)
#define SIOCFDRESET   __SIOCFDRESET /* [struct ifreq *arg] ... */
#endif /* !SIOCFDRESET && __SIOCFDRESET */
#if !defined(SIOCFDSLEEP) && defined(__SIOCFDSLEEP)
#define SIOCFDSLEEP   __SIOCFDSLEEP /* [struct ifreq *arg] ... */
#endif /* !SIOCFDSLEEP && __SIOCFDSLEEP */
#if !defined(SIOCSTRTFMWAR) && defined(__SIOCSTRTFMWAR)
#define SIOCSTRTFMWAR __SIOCSTRTFMWAR /* [struct ifreq *arg] ... */
#endif /* !SIOCSTRTFMWAR && __SIOCSTRTFMWAR */
#if !defined(SIOCLDNSTRTFW) && defined(__SIOCLDNSTRTFW)
#define SIOCLDNSTRTFW __SIOCLDNSTRTFW /* [struct ifreq *arg] ... */
#endif /* !SIOCLDNSTRTFW && __SIOCLDNSTRTFW */
#if !defined(SIOCGETFDSTAT) && defined(__SIOCGETFDSTAT)
#define SIOCGETFDSTAT __SIOCGETFDSTAT /* [struct ifreq *arg] ... */
#endif /* !SIOCGETFDSTAT && __SIOCGETFDSTAT */
#if !defined(SIOCFDNMIINT) && defined(__SIOCFDNMIINT)
#define SIOCFDNMIINT  __SIOCFDNMIINT /* [struct ifreq *arg] ... */
#endif /* !SIOCFDNMIINT && __SIOCFDNMIINT */
#if !defined(SIOCFDEXUSER) && defined(__SIOCFDEXUSER)
#define SIOCFDEXUSER  __SIOCFDEXUSER /* [struct ifreq *arg] ... */
#endif /* !SIOCFDEXUSER && __SIOCFDEXUSER */
#if !defined(SIOCFDGNETMAP) && defined(__SIOCFDGNETMAP)
#define SIOCFDGNETMAP __SIOCFDGNETMAP /* [struct ifreq *arg] ... */
#endif /* !SIOCFDGNETMAP && __SIOCFDGNETMAP */
#if !defined(SIOCFDGIOCTL) && defined(__SIOCFDGIOCTL)
#define SIOCFDGIOCTL  __SIOCFDGIOCTL /* [struct ifreq *arg] ... */
#endif /* !SIOCFDGIOCTL && __SIOCFDGIOCTL */
#if !defined(SIOCSNIT) && defined(__SIOCSNIT)
#define SIOCSNIT      __SIOCSNIT /* [struct nit_ioc *arg] ... */
#endif /* !SIOCSNIT && __SIOCSNIT */
#if !defined(SIOCGNIT) && defined(__SIOCGNIT)
#define SIOCGNIT      __SIOCGNIT /* [struct nit_ioc *arg] ... */
#endif /* !SIOCGNIT && __SIOCGNIT */

#endif /* !_SYS_SOCKIO_H */
