/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/limits.h) */
#ifndef _LINUX_LIMITS_H
#define _LINUX_LIMITS_H 1

#include <__stdinc.h>

#include <asm/os/limits.h>

/* Max # of open files handles */
#if !defined(NR_OPEN) && defined(__OPEN_MAX) && (__OPEN_MAX + 0) != -1
#define NR_OPEN __OPEN_MAX
#endif /* !NR_OPEN && __OPEN_MAX != -1 */

/* Max # of supplemental group IDs that may be set () */
#if !defined(NGROUPS_MAX) && defined(__NGROUPS_MAX) && (__NGROUPS_MAX + 0) != -1
#define NGROUPS_MAX __NGROUPS_MAX
#endif /* !NGROUPS_MAX && __NGROUPS_MAX != -1 */

/* Max # of bytes of args + environ for exec(); */
#if !defined(ARG_MAX) && defined(__ARG_MAX) && (__ARG_MAX + 0) != -1
#define ARG_MAX __ARG_MAX
#endif /* !ARG_MAX && __ARG_MAX != -1 */

/* Max # of links a file may have (fs-dependent) */
#if !defined(LINK_MAX) && defined(__LINK_MAX) && (__LINK_MAX + 0) != -1
#define LINK_MAX __LINK_MAX
#endif /* !LINK_MAX && __LINK_MAX != -1 */

/* Max size of the canonical input queue */
#if !defined(MAX_CANON) && defined(__MAX_CANON) && (__MAX_CANON + 0) != -1
#define MAX_CANON __MAX_CANON
#endif /* !MAX_CANON && __MAX_CANON != -1 */

/* Max size of the type-ahead buffer */
#if !defined(MAX_INPUT) && defined(__MAX_INPUT) && (__MAX_INPUT + 0) != -1
#define MAX_INPUT __MAX_INPUT
#endif /* !MAX_INPUT && __MAX_INPUT != -1 */

/* Max # of chars in a file name */
#if !defined(NAME_MAX) && defined(__NAME_MAX) && (__NAME_MAX + 0) != -1
#define NAME_MAX __NAME_MAX
#endif /* !NAME_MAX && __NAME_MAX != -1 */

/* Max # of chars in a path name including nul */
#if !defined(PATH_MAX) && defined(__PATH_MAX) && (__PATH_MAX + 0) != -1
#define PATH_MAX __PATH_MAX
#endif /* !PATH_MAX && __PATH_MAX != -1 */

/* Max # of bytes in atomic write to a pipe (Default value, assuming
 * that backing  memory  isn't  VIO or  re-mapped  during  a  write) */
#if !defined(PIPE_BUF) && defined(__PIPE_BUF) && (__PIPE_BUF + 0) != -1
#define PIPE_BUF __PIPE_BUF
#endif /* !PIPE_BUF && __PIPE_BUF != -1 */

/* # of realtime signals */
#if !defined(RTSIG_MAX) && defined(__RTSIG_MAX) && (__RTSIG_MAX + 0) != -1
#define RTSIG_MAX __RTSIG_MAX
#endif /* !RTSIG_MAX && __RTSIG_MAX != -1 */

#if 0
/* Max # of chars in an extended attribute name */
#if !defined(XATTR_NAME_MAX) && defined(__XATTR_NAME_MAX) && (__XATTR_NAME_MAX + 0) != -1
#define XATTR_NAME_MAX __XATTR_NAME_MAX
#endif /* !XATTR_NAME_MAX && __XATTR_NAME_MAX != -1 */
/* Max size of an extended attribute value (64k) */
#if !defined(XATTR_SIZE_MAX) && defined(__XATTR_SIZE_MAX) && (__XATTR_SIZE_MAX + 0) != -1
#define XATTR_SIZE_MAX __XATTR_SIZE_MAX
#endif /* !XATTR_SIZE_MAX && __XATTR_SIZE_MAX != -1 */
/* Max size of extended attribute namelist (64k) */
#if !defined(XATTR_LIST_MAX) && defined(__XATTR_LIST_MAX) && (__XATTR_LIST_MAX + 0) != -1
#define XATTR_LIST_MAX __XATTR_LIST_MAX
#endif /* !XATTR_LIST_MAX && __XATTR_LIST_MAX != -1 */
#endif

#endif /* !_LINUX_LIMITS_H */
