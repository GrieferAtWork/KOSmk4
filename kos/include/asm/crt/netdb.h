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
#ifndef _ASM_CRT_NETDB_H
#define _ASM_CRT_NETDB_H 1

/* Possible values for `h_errno'. */
#define __ENETDB_NETDB_INTERNAL (-1) /* s.a. `errno' */
#define __ENETDB_NETDB_SUCCESS  0    /* Success */
#define __ENETDB_HOST_NOT_FOUND 1    /* ??? */
#define __ENETDB_TRY_AGAIN      2    /* ??? */
#define __ENETDB_NO_RECOVERY    3    /* ??? */
#define __ENETDB_NO_DATA        4    /* ??? */

/* Possible values for `getaddrinfo_a(3)::mode' */
#define __GAI_WAIT   0
#define __GAI_NOWAIT 1

/* Flags for `struct addrinfo::ai_flags' */
#define __AI_PASSIVE                  0x0001 /* ??? */
#define __AI_CANONNAME                0x0002 /* ??? */
#define __AI_NUMERICHOST              0x0004 /* ??? */
#define __AI_V4MAPPED                 0x0008 /* ??? */
#define __AI_ALL                      0x0010 /* ??? */
#define __AI_ADDRCONFIG               0x0020 /* ??? */
#define __AI_IDN                      0x0040 /* ??? */
#define __AI_CANONIDN                 0x0080 /* ??? */
#define __AI_IDN_ALLOW_UNASSIGNED     0x0100 /* ??? */
#define __AI_IDN_USE_STD3_ASCII_RULES 0x0200 /* ??? */
#define __AI_NUMERICSERV              0x0400 /* ??? */

/* Possible return values for `getaddrinfo(3)' */
#define __EAI_BADFLAGS     (-1)   /* ??? */
#define __EAI_NONAME       (-2)   /* ??? */
#define __EAI_AGAIN        (-3)   /* ??? */
#define __EAI_FAIL         (-4)   /* ??? */
#define __EAI_NODATA       (-5)   /* ??? */
#define __EAI_FAMILY       (-6)   /* ??? */
#define __EAI_SOCKTYPE     (-7)   /* ??? */
#define __EAI_SERVICE      (-8)   /* ??? */
#define __EAI_ADDRFAMILY   (-9)   /* ??? */
#define __EAI_MEMORY       (-10)  /* ??? */
#define __EAI_SYSTEM       (-11)  /* ??? */
#define __EAI_OVERFLOW     (-12)  /* ??? */
#define __EAI_INPROGRESS   (-100) /* ??? */
#define __EAI_CANCELED     (-101) /* ??? */
#define __EAI_NOTCANCELED  (-102) /* ??? */
#define __EAI_ALLDONE      (-103) /* ??? */
#define __EAI_INTR         (-104) /* ??? */
#define __EAI_IDN_ENCODE   (-105) /* ??? */


#define __NI_MAXHOST 1025 /* Max length for `getnameinfo::host' */
#define __NI_MAXSERV 32   /* Max length for `getnameinfo::serv' */

#define __NI_NUMERICHOST              0x0001 /* ??? */
#define __NI_NUMERICSERV              0x0002 /* ??? */
#define __NI_NOFQDN                   0x0004 /* ??? */
#define __NI_NAMEREQD                 0x0008 /* ??? */
#define __NI_DGRAM                    0x0010 /* ??? */
#ifdef __USE_GNU
#define __NI_IDN                      0x0020 /* ??? */
#define __NI_IDN_ALLOW_UNASSIGNED     0x0040 /* ??? */
#define __NI_IDN_USE_STD3_ASCII_RULES 0x0080 /* ??? */
#endif /* __USE_GNU */

/* Paths for network configuration files. */
#define __PATH_HEQUIV        "/etc/hosts.equiv"
#define __PATH_HOSTS         "/etc/hosts"
#define __PATH_NETWORKS      "/etc/networks"
#define __PATH_NSSWITCH_CONF "/etc/nsswitch.conf"
#define __PATH_PROTOCOLS     "/etc/protocols"
#define __PATH_SERVICES      "/etc/services"


#endif /* !_ASM_CRT_NETDB_H */
