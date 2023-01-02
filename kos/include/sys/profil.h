/* HASH CRC-32:0x8a859482 */
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
/* (#) Portability: GNU C Library (/gmon/sys/profil.h) */
#ifndef _SYS_PROFIL_H
#define _SYS_PROFIL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/time.h>
#include <sys/types.h>
#include <bits/os/timeval.h>

#define PROF_USHORT 0 /* use 16-bit counters (default) */
#define PROF_UINT   1 /* use 32-bit counters */
#define PROF_FAST   2 /* profile faster than usual */

#ifdef __CC__
__SYSDECL_BEGIN

struct prof {
	void             *pr_base;  /* ??? */
	size_t            pr_size;  /* ??? */
	size_t            pr_off;   /* ??? */
	__ULONGPTR_TYPE__ pr_scale; /* ??? */
};

__CDECLARE_OPT(,int,__NOTHROW_NCX,sprofil,(struct prof *__profp, int __profcnt, struct timeval *__tvp, unsigned int __flags),(__profp,__profcnt,__tvp,__flags))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_PROFIL_H */
