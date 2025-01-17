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
/* (#) Portability: Linux (/usr/include/linux/xattr.h) */
#ifndef _LINUX_XATTR_H
#define _LINUX_XATTR_H 1

#include <__stdinc.h>

#include <asm/os/xattr.h>
/*#include <linux/libc-compat.h>*/

#if !defined(XATTR_CREATE) && defined(__XATTR_CREATE)
#define XATTR_CREATE __XATTR_CREATE /* set value, fail if attr already exists. */
#endif /* !XATTR_CREATE && __XATTR_CREATE */
#if !defined(XATTR_REPLACE) && defined(__XATTR_REPLACE)
#define XATTR_REPLACE __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* !XATTR_REPLACE && __XATTR_REPLACE */

/* XATTR Namespaces. */
#define XATTR_OS2_PREFIX          "os2."
#define XATTR_OS2_PREFIX_LEN      __COMPILER_STRLEN(XATTR_OS2_PREFIX)
#define XATTR_MAC_OSX_PREFIX      "osx."
#define XATTR_MAC_OSX_PREFIX_LEN  __COMPILER_STRLEN(XATTR_MAC_OSX_PREFIX)
#define XATTR_BTRFS_PREFIX        "btrfs."
#define XATTR_BTRFS_PREFIX_LEN    __COMPILER_STRLEN(XATTR_BTRFS_PREFIX)
#define XATTR_SECURITY_PREFIX     "security."
#define XATTR_SECURITY_PREFIX_LEN __COMPILER_STRLEN(XATTR_SECURITY_PREFIX)
#define XATTR_SYSTEM_PREFIX       "system."
#define XATTR_SYSTEM_PREFIX_LEN   __COMPILER_STRLEN(XATTR_SYSTEM_PREFIX)
#define XATTR_TRUSTED_PREFIX      "trusted."
#define XATTR_TRUSTED_PREFIX_LEN  __COMPILER_STRLEN(XATTR_TRUSTED_PREFIX)
#define XATTR_USER_PREFIX         "user."
#define XATTR_USER_PREFIX_LEN     __COMPILER_STRLEN(XATTR_USER_PREFIX)

#define XATTR_EVM_SUFFIX             "evm"
#define XATTR_NAME_EVM               XATTR_SECURITY_PREFIX XATTR_EVM_SUFFIX
#define XATTR_IMA_SUFFIX             "ima"
#define XATTR_NAME_IMA               XATTR_SECURITY_PREFIX XATTR_IMA_SUFFIX
#define XATTR_SELINUX_SUFFIX         "selinux"
#define XATTR_NAME_SELINUX           XATTR_SECURITY_PREFIX XATTR_SELINUX_SUFFIX
#define XATTR_SMACK_SUFFIX           "SMACK64"
#define XATTR_SMACK_IPIN             "SMACK64IPIN"
#define XATTR_SMACK_IPOUT            "SMACK64IPOUT"
#define XATTR_SMACK_EXEC             "SMACK64EXEC"
#define XATTR_SMACK_TRANSMUTE        "SMACK64TRANSMUTE"
#define XATTR_SMACK_MMAP             "SMACK64MMAP"
#define XATTR_NAME_SMACK             XATTR_SECURITY_PREFIX XATTR_SMACK_SUFFIX
#define XATTR_NAME_SMACKIPIN         XATTR_SECURITY_PREFIX XATTR_SMACK_IPIN
#define XATTR_NAME_SMACKIPOUT        XATTR_SECURITY_PREFIX XATTR_SMACK_IPOUT
#define XATTR_NAME_SMACKEXEC         XATTR_SECURITY_PREFIX XATTR_SMACK_EXEC
#define XATTR_NAME_SMACKTRANSMUTE    XATTR_SECURITY_PREFIX XATTR_SMACK_TRANSMUTE
#define XATTR_NAME_SMACKMMAP         XATTR_SECURITY_PREFIX XATTR_SMACK_MMAP
#define XATTR_CAPS_SUFFIX            "capability"
#define XATTR_NAME_CAPS              XATTR_SECURITY_PREFIX XATTR_CAPS_SUFFIX
#define XATTR_POSIX_ACL_ACCESS       "posix_acl_access"
#define XATTR_NAME_POSIX_ACL_ACCESS  XATTR_SYSTEM_PREFIX XATTR_POSIX_ACL_ACCESS
#define XATTR_POSIX_ACL_DEFAULT      "posix_acl_default"
#define XATTR_NAME_POSIX_ACL_DEFAULT XATTR_SYSTEM_PREFIX XATTR_POSIX_ACL_DEFAULT

#endif /* _LINUX_XATTR_H */
