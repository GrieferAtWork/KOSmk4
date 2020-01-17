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
#ifndef _BITS_IOCTLS_H
#define _BITS_IOCTLS_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/ioctls.h' */

#include <__stdinc.h>
#include <asm/ioctls.h>

/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

/* Routing table calls. */
#define SIOCADDRT      0x890b /* add routing table entry. */
#define SIOCDELRT      0x890c /* delete routing table entry. */
#define SIOCRTMSG      0x890d /* call to routing system. */

/* Socket configuration controls. */
#define SIOCGIFNAME    0x8910 /* get iface name. */
#define SIOCSIFLINK    0x8911 /* set iface channel. */
#define SIOCGIFCONF    0x8912 /* get iface list. */
#define SIOCGIFFLAGS   0x8913 /* get flags. */
#define SIOCSIFFLAGS   0x8914 /* set flags. */
#define SIOCGIFADDR    0x8915 /* get PA address. */
#define SIOCSIFADDR    0x8916 /* set PA address. */
#define SIOCGIFDSTADDR 0x8917 /* get remote PA address. */
#define SIOCSIFDSTADDR 0x8918 /* set remote PA address. */
#define SIOCGIFBRDADDR 0x8919 /* get broadcast PA address. */
#define SIOCSIFBRDADDR 0x891a /* set broadcast PA address. */
#define SIOCGIFNETMASK 0x891b /* get network PA mask. */
#define SIOCSIFNETMASK 0x891c /* set network PA mask. */
#define SIOCGIFMETRIC  0x891d /* get metric. */
#define SIOCSIFMETRIC  0x891e /* set metric. */
#define SIOCGIFMEM     0x891f /* get memory address (BSD). */
#define SIOCSIFMEM     0x8920 /* set memory address (BSD). */
#define SIOCGIFMTU     0x8921 /* get MTU size. */
#define SIOCSIFMTU     0x8922 /* set MTU size. */
#define SIOCSIFNAME    0x8923 /* set interface name. */
#define SIOCSIFHWADDR  0x8924 /* set hardware address. */
#define SIOCGIFENCAP   0x8925 /* get/set encapsulations. */
#define SIOCSIFENCAP   0x8926
#define SIOCGIFHWADDR  0x8927 /* Get hardware address. */
#define SIOCGIFSLAVE   0x8929 /* Driver slaving support. */
#define SIOCSIFSLAVE   0x8930
#define SIOCADDMULTI   0x8931 /* Multicast address lists. */
#define SIOCDELMULTI   0x8932
#define SIOCGIFINDEX   0x8933 /* name -> if_index mapping. */
#define SIOGIFINDEX    SIOCGIFINDEX
#define SIOCSIFPFLAGS  0x8934 /* set/get extended flags set. */
#define SIOCGIFPFLAGS  0x8935
#define SIOCDIFADDR    0x8936 /* delete PA address. */
#define SIOCSIFHWBROADCAST 0x8937 /* set hardware broadcast addr. */
#define SIOCGIFCOUNT   0x8938 /* get number of devices. */

#define SIOCGIFBR      0x8940 /* Bridging support. */
#define SIOCSIFBR      0x8941 /* Set bridging options. */

#define SIOCGIFTXQLEN  0x8942 /* Get the tx queue length. */
#define SIOCSIFTXQLEN  0x8943 /* Set the tx queue length. */


/* ARP cache control calls. */
          /*  0x8950 - 0x8952  *< obsolete calls, don't re-use. */
#define SIOCDARP       0x8953 /* delete ARP table entry. */
#define SIOCGARP       0x8954 /* get ARP table entry. */
#define SIOCSARP       0x8955 /* set ARP table entry. */

/* RARP cache control calls. */
#define SIOCDRARP      0x8960 /* delete RARP table entry. */
#define SIOCGRARP      0x8961 /* get RARP table entry. */
#define SIOCSRARP      0x8962 /* set RARP table entry. */

/* Driver configuration calls */
#define SIOCGIFMAP     0x8970 /* Get device parameters. */
#define SIOCSIFMAP     0x8971 /* Set device parameters. */

/* DLCI configuration calls */
#define SIOCADDDLCI    0x8980 /* Create new DLCI device. */
#define SIOCDELDLCI    0x8981 /* Delete DLCI device. */

/* Device private ioctl calls. */

#define SIOCDEVPRIVATE 0x89f0 /* to 89FF */
/* These 16 ioctl calls are protocol private */
#define SIOCPROTOPRIVATE 0x89e0 /* to 89EF */


#endif /* !_BITS_IOCTLS_H */
