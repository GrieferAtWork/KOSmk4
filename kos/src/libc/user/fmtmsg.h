/* HASH CRC-32:0x3ee8aec3 */
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
#ifndef GUARD_LIBC_USER_FMTMSG_H
#define GUARD_LIBC_USER_FMTMSG_H 1

#include "../api.h"
#include "../auto/fmtmsg.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fmtmsg.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> fmtmsg(3)
 * Print a message to `stderr(3)' and/or `syslog(3)'. The exact  format
 * in which the mssage is printed, alongside additional severity levels
 * depends on `$MSGVERB', `$SEV_LEVEL' and `addseverity(3)'.
 * @param: classification: Set of:
 *          - `MM_PRINT', `MM_CONSOLE', or `MM_PRINT | MM_CONSOLE'
 *          - `MM_HARD', `MM_FIRM' or `MM_SOFT'
 *          - `MM_APPL', `MM_UTIL' or `MM_OPSYS'
 *          - `MM_RECOVER' or `MM_NRECOV'
 * @param: label:    Message source, as "<domain>:<util>", where  "<domain>"
 *                   must not be longer than 10 chars, and "<util>" must not
 *                   be longer than 14 chars.
 * @param: severity: Message severity code (extra severity codes can be
 *                   defined by `addseverity(3)'  or via  `$SEV_LEVEL')
 * @param: text:     Error condition (e.g. "bad arguments given")
 * @param: action:   Steps to fix the error (if printed, is prefixed by "TO FIX: ")
 * @param: tag:      Reference to online docs for more info on error (should include `label')
 * @return: MM_NOTOK: Arguments are bad
 * @return: MM_OK:    Success
 * @return: MM_NOMSG: Failed to print message to `stderr(3)' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_fmtmsg)(long classification, const char *label, __STDC_INT_AS_UINT_T severity, char const *text, char const *action, char const *tag);
/* >> addseverity(3)
 * Add  (`s != NULL') or remove  (`s == NULL') custom severity levels.
 * By default (and these cannot be overwritten or removed), levels 0-4
 * are defined as:
 *  - 0: MM_NOSEV:   [""]        No severity level
 *  - 1: MM_HALT:    ["HALT"]    Application will halt as a result
 *  - 2: MM_ERROR:   ["ERROR"]   Non-fatal error encountered
 *  - 3: MM_WARNING: ["WARNING"] Unusual non-error condition (== warning)
 *  - 4: MM_INFO:    ["INFO"]    General information
 * Additionally,  `$SEV_LEVEL' is used  to define additional severity
 * levels  dynamically (just like  this function can  be used to) the
 * first time this function (or `fmtmsg(3)') is called. The format of
 * the `$SEV_LEVEL' variable follows posix specifications, and unlike
 * with the 5 default severity levels, these can be removed again, or
 * further overwritten by use of this function
 * @param: severity: The ID to assign for the new severity level (must be >= 5)
 * @param: s: - When non-NULL, define (or override) the label for `severity'.
 *            - When NULL, remove the definition for `severity'
 * @return: MM_OK:    Success
 * @return: MM_NOTOK: The given `severity' is `< 5' (errno was not modified)
 * @return: MM_NOTOK: Out of memory (errno was set to `ENOMEM')
 * @return: MM_NOTOK: No such `severity' and `s == NULL' (errno was not modified) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_addseverity)(__STDC_INT_AS_UINT_T severity, const char *s);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FMTMSG_H */
