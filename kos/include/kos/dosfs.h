/* HASH CRC-32:0xc39318fe */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_DOSFS_H
#define _KOS_DOSFS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */


/* Possible values for `dosfs_(get|set)enabled(3)' */
#define DOSFS_DISABLED 0 /* Disabled (default for ELF) */
#define DOSFS_ENABLED  1 /* Enabled (default for PE; implicitly pass `O_DOSPATH'+
                          * `AT_DOSPATH' in  syscalls  made  by  DOS$-functions). */
/* For `dosfs_setenabled(3)': only query the current mode; don't change it. */
#define DOSFS_QUERY    (__CCAST(unsigned int)-1)

#ifdef __CC__
__SYSDECL_BEGIN

/* >> dosfs_getenabled(3)
 * Get the current dosfs-emulation mode, as used by
 * libc filesystem functions  whose names are  pre-
 * fixed with `DOS$' (s.a.  `dosfs_setenabled(3)').
 * @return: * : The current mode (one of `DOSFS_*') */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,unsigned int,__NOTHROW,dosfs_getenabled,(void),())
/* >> dosfs_setenabled(3)
 * Set the is-enabled  state for filesystem  emulation.
 * When enabled, all DOS$-prefixed filesystem functions
 * will include  `O_DOSPATH' /  `AT_DOSPATH' in  system
 * calls,  meaning they accept/return DOS paths, rather
 * than unix paths.
 *
 * The default state of dosfs emulation depends on the
 * binary format of the main application. If the  main
 * application is an ELF binary, the default state  is
 * set  to  `DOSFS_DISABLED'. When  it's a  PE binary,
 * the default state is `DOSFS_ENABLED'
 *
 * Note that this function does not affect programs  that
 * explicitly pass  `O_DOSPATH'  /  `AT_DOSPATH'  to  API
 * functions.  -  This  only affects  the  implicit flags
 * added to caller-given arguments within DOS$ functions.
 *
 * @param: newmode: The new mode to set (one of `DOSFS_*')
 * @return: * :     The old mode (one of `DOSFS_*') */
__CDECLARE_OPT(,unsigned int,__NOTHROW,dosfs_setenabled,(unsigned int __newmode),(__newmode))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_DOSFS_H */
