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
#ifndef _COMPAT_KOS_EXEC_BITS_PEB_H
#define _COMPAT_KOS_EXEC_BITS_PEB_H 1

#include <compat/config.h>

#ifdef __ARCH_HAVE_COMPAT
#include <kos/exec/bits/peb.h>
#define __compat_process_peb_defined
#define OFFSET_COMPAT_PROCESS_PEB_ARGC OFFSET_PROCESS_PEB_ARGC
#define OFFSET_COMPAT_PROCESS_PEB_ARGV OFFSET_PROCESS_PEB_ARGV
#define OFFSET_COMPAT_PROCESS_PEB_ENVC OFFSET_PROCESS_PEB_ENVC
#define OFFSET_COMPAT_PROCESS_PEB_ENVP OFFSET_PROCESS_PEB_ENVP
#define compat_process_peb             process_peb
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_KOS_EXEC_BITS_PEB_H */
