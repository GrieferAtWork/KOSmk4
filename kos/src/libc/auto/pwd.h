/* HASH CRC-32:0x6a1ed7a7 */
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
#ifndef GUARD_LIBC_AUTO_PWD_H
#define GUARD_LIBC_AUTO_PWD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pwd.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getpwuid(3)
 * Search for an entry with a matching user ID
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `uid' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED struct passwd *NOTHROW_RPC(LIBDCALL libd_getpwuid)(uid_t uid);
/* >> getpwnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) struct passwd *NOTHROW_RPC(LIBDCALL libd_getpwnam)(char const *name);
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_INOUT(1) struct passwd *NOTHROW_RPC(LIBDCALL libd_fgetpwent)(FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN_OPT(1) bool NOTHROW_NCX(LIBCCALL libc_nss_checkfield)(char const *field);
INTDEF ATTR_PURE WUNUSED ATTR_IN_OPT(1) bool NOTHROW_NCX(LIBCCALL libc_nss_checkfieldlist)(char *const *list);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_CB_NCX(LIBDCALL libd_putpwent)(struct passwd const *__restrict ent, FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_CB_NCX(LIBCCALL libc_putpwent)(struct passwd const *__restrict ent, FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_getpwuid_r)(uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* >> getpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_getpwnam_r)(char const *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* >> getpwent_r(3)
 * Read an entry from the password-file stream, opening it if necessary.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `setpwent()' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) errno_t NOTHROW_RPC(LIBDCALL libd_getpwent_r)(struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_fgetpwent_r)(FILE *__restrict stream, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBDCALL libd_fgetpwuid_r)(FILE *__restrict stream, uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBCCALL libc_fgetpwuid_r)(FILE *__restrict stream, uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBDCALL libd_fgetpwnam_r)(FILE *__restrict stream, char const *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBCCALL libc_fgetpwnam_r)(FILE *__restrict stream, char const *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* >> fgetpwfiltered_r(3)
 * Filtered read from `stream'
 * @param: filtered_uid:  When not equal to `(uid_t)-1', require this UID
 * @param: filtered_name: When not `NULL', require this username
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_fgetpwfiltered_r)(FILE *__restrict stream, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result, uid_t filtered_uid, char const *filtered_name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd_getpw)(uid_t uid, char *buffer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBCCALL libc_getpw)(uid_t uid, char *buffer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sgetpwent(3)
 * Old libc4/5 function (only here for compat) */
INTDEF ATTR_IN(1) struct passwd *NOTHROW_NCX(LIBDCALL libd_sgetpwent)(char const *line);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sgetpwent(3)
 * Old libc4/5 function (only here for compat) */
INTDEF ATTR_IN(1) struct passwd *NOTHROW_NCX(LIBCCALL libc_sgetpwent)(char const *line);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_setpassent)(int keep_open);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpassent)(int keep_open);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_uid_from_user)(char const *name, uid_t *p_uid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_uid_from_user)(char const *name, uid_t *p_uid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED char const *NOTHROW_NCX(LIBDCALL libd_user_from_uid)(uid_t uid, int nouser);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_user_from_uid)(uid_t uid, int nouser);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) struct passwd *NOTHROW_NCX(LIBDCALL libd_pw_dup)(struct passwd const *ent);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) struct passwd *NOTHROW_NCX(LIBCCALL libc_pw_dup)(struct passwd const *ent);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PWD_H */
