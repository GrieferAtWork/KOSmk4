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
#ifndef _LIBPHYS_API_H
#define _LIBPHYS_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

/* Simple  wrapper library for facilitating access to physical
 * memory  from user-space. Note  that in order  to be able to
 * use this library, your program needs sufficient permissions
 * to be allowed to used /dev/mem
 *
 * NOTE: For simplicity, API  functions do not  include return  values
 *       for the  purpose of  error checking.  Instead, when  physical
 *       memory access isn't possible, then API functions will instead
 *       leave  `errno' as it  was set by  the underlying system call,
 *       which will usually  be `EACCES' or  `EPERM', and turn  writes
 *       into  no-ops, and  reads into  acting as  though all physical
 *       memory was made up of 0-bytes.
 *       The only exception to this rule is `mmapphys', which will
 *       return with a permissions-error set.
 * Also note that upon success, none of the API functions will  ever
 * modify `errno', meaning that you might also check for errors via:
 * >> errno = EOK;
 * >> pokephysl(0x12345, 42);
 * >> if (errno != EOK) {
 * >>     ...
 * >> } */

#if defined(__i386__) && !defined(__x86_64__)
#define LIBPHYS_CC __ATTR_FASTCALL
#else /* ... */
#define LIBPHYS_CC /* nothing */
#endif /* !... */

/* NOTE: In kernel-space, libpciaccess doesn't exist per-se, but (most) functions
 *       exist with identical names, and are also declared when  <libphys/phys.h>
 *       is #included, so act as though prototypes were provided. */
#if defined(__KOS__) && defined(__KERNEL__)
#define LIBPHYS_WANT_PROTOTYPES
#endif /* __KOS__ && __KERNEL__ */

#ifdef __LIBPHYS_STATIC
#define LIBPHYS_DECL __INTDEF
#else /* ... */
#define LIBPHYS_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBPHYS_LIBRARY_NAME "libphys.so"

#endif /* !_LIBPHYS_API_H */
