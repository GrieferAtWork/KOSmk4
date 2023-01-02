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
/* (#) Portability: NetBSD (/sys/sys/ansi.h) */
#ifndef _SYS_ANSI_H
#define _SYS_ANSI_H 1

#include <__stdinc.h>

#include <bits/crt/mbstate.h>
#include <bits/crt/wctype.h> /* __wctype_t, __wctrans_t */
#include <bits/types.h>
#include <machine/_types.h>
#include <net/bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __off_t
#define __off_t __off_t
typedef __off64_t __off_t;
#endif /* !__off_t */

typedef __u_net32_t __in_addr_t;
typedef __u_net16_t __in_port_t;
#ifndef __machine_fsblkcnt_t_defined
#define __machine_fsblkcnt_t_defined
#endif /* !__machine_fsblkcnt_t_defined */
#ifndef __machine_fsfilcnt_t_defined
#define __machine_fsfilcnt_t_defined
#endif /* !__machine_fsfilcnt_t_defined */
#ifndef ____mbstate_t_defined
#define ____mbstate_t_defined
typedef struct __mbstate __mbstate_t;
#endif /* !____mbstate_t_defined */
#define _BSD_WCTRANS_T_ __wctrans_t
#define _BSD_WCTYPE_T_  __wctype_t
#define _BSD_MBSTATE_T_ __mbstate_t
#ifndef ____va_list_defined
#define ____va_list_defined
typedef __builtin_va_list __va_list;
#endif /* !____va_list_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_ANSI_H */
