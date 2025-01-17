/* HASH CRC-32:0xad9ec6b6 */
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
#ifndef GUARD_LIBC_AUTO_SHADOW_H
#define GUARD_LIBC_AUTO_SHADOW_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <shadow.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getspnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read shadow entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) struct spwd *NOTHROW_RPC(LIBDCALL libd_getspnam)(char const *__restrict name);
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_INOUT(1) struct spwd *NOTHROW_RPC(LIBDCALL libd_fgetspent)(FILE *__restrict stream);
INTDEF WUNUSED ATTR_IN(1) struct spwd *NOTHROW_RPC(LIBDCALL libd_sgetspent)(char const *__restrict string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) struct spwd *NOTHROW_RPC(LIBCCALL libc_sgetspent)(char const *__restrict string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_CB_NCX(LIBDCALL libd_putspent)(struct spwd const *__restrict ent, FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_CB_NCX(LIBCCALL libc_putspent)(struct spwd const *__restrict ent, FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) errno_t NOTHROW_RPC(LIBDCALL libd_getspent_r)(struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_getspnam_r)(char const *__restrict name, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_sgetspent_r)(char const *__restrict string, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_sgetspent_r)(char const *__restrict string, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd_fgetspent_r)(FILE *__restrict stream, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_fgetspent_r)(FILE *__restrict stream, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetspnam_r(3)
 * KOS-extension, base-level read-entry function. When `filtered_name != NULL',
 * filter to return the first  (and hopefully only) entry for  `filtered_name'.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_name'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_IN_OPT(2) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBDCALL libd_fgetspnam_r)(FILE *__restrict stream, char const *filtered_name, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetspnam_r(3)
 * KOS-extension, base-level read-entry function. When `filtered_name != NULL',
 * filter to return the first  (and hopefully only) entry for  `filtered_name'.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_name'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_IN_OPT(2) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBCCALL libc_fgetspnam_r)(FILE *__restrict stream, char const *filtered_name, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SHADOW_H */
