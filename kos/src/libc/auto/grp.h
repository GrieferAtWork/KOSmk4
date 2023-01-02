/* HASH CRC-32:0x243f0903 */
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
#ifndef GUARD_LIBC_AUTO_GRP_H
#define GUARD_LIBC_AUTO_GRP_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <grp.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getgrgid(3), getgrgid_r(3) */
INTDEF WUNUSED struct group *NOTHROW_RPC(LIBDCALL libd_getgrgid)(gid_t gid);
/* >> getgrnam(3), getgrnam_r(3) */
INTDEF WUNUSED ATTR_IN(1) struct group *NOTHROW_RPC(LIBDCALL libd_getgrnam)(char const *__restrict name);
/* >> putgrent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBDCALL libd_putgrent)(struct group const *__restrict entry, FILE *__restrict stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putgrent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBCCALL libc_putgrent)(struct group const *__restrict entry, FILE *__restrict stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getgrgid(3), getgrgid_r(3) */
INTDEF ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int NOTHROW_RPC(LIBDCALL libd_getgrgid_r)(gid_t gid, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> getgrnam(3), getgrnam_r(3) */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int NOTHROW_RPC(LIBDCALL libd_getgrnam_r)(char const *__restrict name, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> getgrent(3), getgrent_r(3) */
INTDEF ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) int NOTHROW_RPC(LIBDCALL libd_getgrent_r)(struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> fgetgrent(3), fgetgrent_r(3) */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int NOTHROW_RPC(LIBDCALL libd_fgetgrent_r)(FILE *__restrict stream, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetgrent(3), fgetgrent_r(3) */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int NOTHROW_RPC(LIBCCALL libc_fgetgrent_r)(FILE *__restrict stream, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetgrgid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `gid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBDCALL libd_fgetgrgid_r)(FILE *__restrict stream, gid_t gid, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetgrgid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `gid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBCCALL libc_fgetgrgid_r)(FILE *__restrict stream, gid_t gid, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetgrnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBDCALL libd_fgetgrnam_r)(FILE *__restrict stream, char const *__restrict name, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fgetgrnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_IN(2) ATTR_INOUT(1) ATTR_OUT(3) ATTR_OUT(6) ATTR_OUTS(4, 5) errno_t NOTHROW_RPC(LIBCCALL libc_fgetgrnam_r)(FILE *__restrict stream, char const *__restrict name, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> fgetgrfiltered_r(3)
 * Filtered read from `stream'
 * @param: filtered_gid:  When not equal to `(gid_t)-1', require this GID
 * @param: filtered_name: When not `NULL', require this username
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read, or no entry matches the given `filtered_*'
 *                  Note that in this case, `errno' will have not been changed
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 *                  Note that in this case, `errno' will have also been set to `ERANGE'
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF ATTR_INOUT(1) ATTR_IN_OPT(7) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_fgetgrfiltered_r)(FILE *__restrict stream, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result, gid_t filtered_gid, char const *filtered_name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fgetgrent(3), fgetgrent_r(3) */
INTDEF ATTR_INOUT(1) struct group *NOTHROW_RPC(LIBDCALL libd_fgetgrent)(FILE *__restrict stream);
/* >> setgroups(2) */
INTDEF ATTR_INS(2, 1) int NOTHROW_RPC(LIBDCALL libd_setgroups)(size_t count, gid_t const *groups);
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
INTDEF ATTR_IN(1) ATTR_INOUT(4) ATTR_OUT(3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_getgrouplist)(char const *user, gid_t group, gid_t *groups, __STDC_INT_AS_SIZE_T *ngroups);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
INTDEF ATTR_IN(1) ATTR_INOUT(4) ATTR_OUT(3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_getgrouplist)(char const *user, gid_t group, gid_t *groups, __STDC_INT_AS_SIZE_T *ngroups);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_initgroups)(char const *user, gid_t group);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_initgroups)(char const *user, gid_t group);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_setgroupent)(int keep_open);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_setgroupent)(int keep_open);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_gid_from_group)(char const *name, gid_t *p_gid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_gid_from_group)(char const *name, gid_t *p_gid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED char const *NOTHROW_NCX(LIBDCALL libd_group_from_gid)(gid_t gid, int nogroup);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_group_from_gid)(gid_t gid, int nogroup);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_GRP_H */
