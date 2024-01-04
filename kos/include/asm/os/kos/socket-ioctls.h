/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_SOCKET_IOCTLS_H
#define _ASM_OS_KOS_SOCKET_IOCTLS_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>

#define __FIOSETOWN          _IO(0x89, 0x01) /* ... */
#define __SIOCSPGRP          _IO(0x89, 0x02) /* ... */
#define __FIOGETOWN          _IO(0x89, 0x03) /* ... */
#define __SIOCGPGRP          _IO(0x89, 0x04) /* ... */
#define __SIOCATMARK         _IO(0x89, 0x05) /* ... */
#define __SIOCGSTAMP32       _IO(0x89, 0x06) /* [struct timeval32 *arg] Get stamp */
#define __SIOCGSTAMPNS32     _IO(0x89, 0x07) /* [struct timespec32 *arg] Get stamp */
/* Routing table functions. */
#define __SIOCADDRT          _IO(0x89, 0x0b) /* ??? */
#define __SIOCDELRT          _IO(0x89, 0x0c) /* ??? */
#define __SIOCRTMSG          _IO(0x89, 0x0d) /* ??? */
/* Socket configuration functions. */
#define __SIOCGIFNAME        _IO(0x89, 0x10) /* ??? */
#define __SIOCSIFLINK        _IO(0x89, 0x11) /* ??? */
#define __SIOCGIFCONF        _IO(0x89, 0x12) /* ??? */
#define __SIOCGIFFLAGS       _IO(0x89, 0x13) /* ??? */
#define __SIOCSIFFLAGS       _IO(0x89, 0x14) /* ??? */
#define __SIOCGIFADDR        _IO(0x89, 0x15) /* ??? */
#define __SIOCSIFADDR        _IO(0x89, 0x16) /* ??? */
#define __SIOCGIFDSTADDR     _IO(0x89, 0x17) /* ??? */
#define __SIOCSIFDSTADDR     _IO(0x89, 0x18) /* ??? */
#define __SIOCGIFBRDADDR     _IO(0x89, 0x19) /* ??? */
#define __SIOCSIFBRDADDR     _IO(0x89, 0x1a) /* ??? */
#define __SIOCGIFNETMASK     _IO(0x89, 0x1b) /* ??? */
#define __SIOCSIFNETMASK     _IO(0x89, 0x1c) /* ??? */
#define __SIOCGIFMETRIC      _IO(0x89, 0x1d) /* ??? */
#define __SIOCSIFMETRIC      _IO(0x89, 0x1e) /* ??? */
#define __SIOCGIFMEM         _IO(0x89, 0x1f) /* ??? */
#define __SIOCSIFMEM         _IO(0x89, 0x20) /* ??? */
#define __SIOCGIFMTU         _IO(0x89, 0x21) /* ??? */
#define __SIOCSIFMTU         _IO(0x89, 0x22) /* ??? */
#define __SIOCSIFNAME        _IO(0x89, 0x23) /* ??? */
#define __SIOCSIFHWADDR      _IO(0x89, 0x24) /* ??? */
#define __SIOCGIFENCAP       _IO(0x89, 0x25) /* ??? */
#define __SIOCSIFENCAP       _IO(0x89, 0x26) /* ??? */
#define __SIOCGIFHWADDR      _IO(0x89, 0x27) /* ??? */
#define __SIOCGIFSLAVE       _IO(0x89, 0x29) /* ??? */
#define __SIOCSIFSLAVE       _IO(0x89, 0x30) /* ??? */
#define __SIOCADDMULTI       _IO(0x89, 0x31) /* ??? */
#define __SIOCDELMULTI       _IO(0x89, 0x32) /* ??? */
#define __SIOCGIFINDEX       _IO(0x89, 0x33) /* ??? */
#define __SIOCSIFPFLAGS      _IO(0x89, 0x34) /* ??? */
#define __SIOCGIFPFLAGS      _IO(0x89, 0x35) /* ??? */
#define __SIOCDIFADDR        _IO(0x89, 0x36) /* ??? */
#define __SIOCSIFHWBROADCAST _IO(0x89, 0x37) /* ??? */
#define __SIOCGIFCOUNT       _IO(0x89, 0x38) /* ??? */
#define __SIOCGIFBR          _IO(0x89, 0x40) /* ??? */
#define __SIOCSIFBR          _IO(0x89, 0x41) /* ??? */
#define __SIOCGIFTXQLEN      _IO(0x89, 0x42) /* ??? */
#define __SIOCSIFTXQLEN      _IO(0x89, 0x43) /* ??? */
#ifdef __linux__
/*      __SIOCGIFDIVERT      _IO(0x89, 0x44)  * ??? */
/*      __SIOCSIFDIVERT      _IO(0x89, 0x45)  * ??? */
#define __SIOCETHTOOL        _IO(0x89, 0x46) /* ??? */
#define __SIOCGMIIPHY        _IO(0x89, 0x47) /* ??? */
#define __SIOCGMIIREG        _IO(0x89, 0x48) /* ??? */
#define __SIOCSMIIREG        _IO(0x89, 0x49) /* ??? */
#define __SIOCWANDEV         _IO(0x89, 0x4a) /* ??? */
#define __SIOCOUTQNSD        _IO(0x89, 0x4b) /* ??? */
#endif /* __linux__ */
/* ARP cache control calls. */
/*                           _IO(0x89, 0x50)  * ... */
/*                           _IO(0x89, 0x51)  * ... */
/*                           _IO(0x89, 0x52)  * ... */
#define __SIOCDARP           _IO(0x89, 0x53) /* ??? */
#define __SIOCGARP           _IO(0x89, 0x54) /* ??? */
#define __SIOCSARP           _IO(0x89, 0x55) /* ??? */
/* RARP cache control calls. */
#define __SIOCDRARP          _IO(0x89, 0x60) /* ??? */
#define __SIOCGRARP          _IO(0x89, 0x61) /* ??? */
#define __SIOCSRARP          _IO(0x89, 0x62) /* ??? */
/* Driver configuration calls */
#define __SIOCGIFMAP         _IO(0x89, 0x70) /* ??? */
#define __SIOCSIFMAP         _IO(0x89, 0x71) /* ??? */
/* DLCI configuration calls */
#define __SIOCADDDLCI        _IO(0x89, 0x80) /* ??? */
#define __SIOCDELDLCI        _IO(0x89, 0x81) /* ??? */
#ifdef __linux__
#define __SIOCGIFVLAN        _IO(0x89, 0x82) /* ??? */
#define __SIOCSIFVLAN        _IO(0x89, 0x83) /* ??? */
/* bonding calls */
#define __SIOCBONDENSLAVE        _IO(0x89, 0x90) /* ??? */
#define __SIOCBONDRELEASE        _IO(0x89, 0x91) /* ??? */
#define __SIOCBONDSETHWADDR      _IO(0x89, 0x92) /* ??? */
#define __SIOCBONDSLAVEINFOQUERY _IO(0x89, 0x93) /* ??? */
#define __SIOCBONDINFOQUERY      _IO(0x89, 0x94) /* ??? */
#define __SIOCBONDCHANGEACTIVE   _IO(0x89, 0x95) /* ??? */
/* bridge calls */
#define __SIOCBRADDBR        _IO(0x89, 0xa0) /* ??? */
#define __SIOCBRDELBR        _IO(0x89, 0xa1) /* ??? */
#define __SIOCBRADDIF        _IO(0x89, 0xa2) /* ??? */
#define __SIOCBRDELIF        _IO(0x89, 0xa3) /* ??? */
/* hardware time stamping */
#define __SIOCSHWTSTAMP      _IO(0x89, 0xb0) /* ??? */
#define __SIOCGHWTSTAMP      _IO(0x89, 0xb1) /* ??? */
#endif /* __linux__ */
#define __SIOCDEVPRIVATE     _IO(0x89, 0xf0) /* to _IO(0x89, 0xff): Device-private ioctls. */
#define __SIOCPROTOPRIVATE   _IO(0x89, 0xe0) /* to _IO(0x89, 0xef): Protocol-private ioctls. */

#ifdef __KOS__
#undef __SIOCGSTAMP32
#undef __SIOCGSTAMPNS32
#define __SIOCGSTAMP32       _IOR(0x89, 0x06, struct __timeval32) /* [struct timeval32 *arg] Get stamp */
#define __SIOCGSTAMP64       _IOR(0x89, 0x06, struct __timeval64) /* [struct timeval64 *arg] Get stamp */
#define __SIOCGSTAMPNS32     _IOR(0x89, 0x07, struct __timeval32) /* [struct timespec32 *arg] Get stamp */
#define __SIOCGSTAMPNS64     _IOR(0x89, 0x07, struct __timeval64) /* [struct timespec64 *arg] Get stamp */
#else /* __KOS__ */
#include <bits/typesizes.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __SIOCGSTAMP64       __SIOCGSTAMP32    /* [struct timeval64 *arg] Get stamp */
#define __SIOCGSTAMPNS64     __SIOCGSTAMPNS32  /* [struct timespec64 *arg] Get stamp */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* !__KOS__ */

#endif /* !_ASM_OS_KOS_SOCKET_IOCTLS_H */
