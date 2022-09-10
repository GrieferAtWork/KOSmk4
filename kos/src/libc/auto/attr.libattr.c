/* HASH CRC-32:0xb85d005b */
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
#ifndef GUARD_LIBC_AUTO_ATTR_LIBATTR_C
#define GUARD_LIBC_AUTO_ATTR_LIBATTR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/attr.libattr.h"
#include "../user/ctype.h"
#include "fnmatch.h"
#include "format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_IN(1) ATTR_INOUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_check_permissions)(char const *attr_name,
                                                       struct error_context *ctx) {
	return libc_attr_copy_action(attr_name, ctx) == 0;
}
#include <bits/types.h>
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_IN(1) ATTR_INOUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_action)(char const *attr_name,
                                            struct error_context *ctx) {
	/* NOTE: `actions' has the following format:
	 * >> actions_base:     [
	 * >>                       {NAME}
	 * >>                       \0
	 * >>                       {CODE}
	 * >>                   ]...
	 * >> actions_end:      \0
	 * Where NAME is a C-string, and CODE is \1 or \2
	 */
	static char const *actions = NULL;
	char const *iter;
	if (actions == NULL)
		actions = libc_attr_load_actions(ctx); /* Lazily load actions. */

	/* Search for the requested action. */
	for (iter = actions; *iter; iter = libc_strend(iter) + 2) {
		if (libc_fnmatch(iter, attr_name, 0) == 0)
			return (int)(unsigned int)(unsigned char)libc_strend(iter)[1];
	}

	/* No special action... */
	return 0;
}
#include <attr/error_context.h>
#include <hybrid/typecore.h>
#include <asm/crt/util.h>
#include <bits/crt/inttypes.h>
#include <attr/asm/libattr.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_RETNONNULL WUNUSED ATTR_INOUT_OPT(1) char const *
NOTHROW_NCX(LIBCCALL libc_attr_load_actions)(struct error_context *ctx) {
	/* Default rules used when `/etc/xattr.conf' is missing or malformed */
	static char const default_actions[] =
	"system.nfs4_acl\0\2"
	"system.nfs4acl\0\2"
	"system.posix_acl_access\0\2"
	"system.posix_acl_default\0\2"
	"trusted.SGI_ACL_DEFAULT\0\1"
	"trusted.SGI_ACL_FILE\0\1"
	"trusted.SGI_CAP_FILE\0\1"
	"trusted.SGI_DMI_*\0\1"
	"trusted.SGI_MAC_FILE\0\1"
	"xfsroot.*\0\1"
	"user.Beagle.*\0\1"
	"security.evm\0\1"
	"afs.*\0\1";
	(void)ctx;

	/* Try to parse settings from `/etc/xattr.conf' */
#ifdef __FPARSELN_UNESCALL
	static char const config_filename[] = "/etc/xattr.conf";
	FILE *fp = libc_fopen(config_filename, "r");
	if (fp) {
		size_t lno = 1;
		struct format_aprintf_data printer;
		printer.ap_base  = NULL;
		printer.ap_avail = 0;
		printer.ap_used  = 0;
		for (;;) {
			char *line, *action;
			line = libc_fparseln(fp, NULL, &lno, NULL, __FPARSELN_UNESCALL);
			if unlikely(!line) {
				__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: I/O error: %m",
				             config_filename, lno);
				break;
			}

			/* Check for error */
			if (!*line) {
				char *result;
				libc_free(line);

				libc_fclose(fp);

				result = libc_format_aprintf_pack(&printer, NULL);
				if unlikely(!result) {
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename, lno);
					goto return_fallback;
				}
				return result;
			}

			/* Handle `line', which should be formatted like "<pattern> <action>" */
			action = line;
			while (*action && !libc_isspace(*action))
				++action;
			if (*action) {
				char *action_endp;
				*action++ = '\0';
				action_endp = action;
				while (*action && libc_isspace(*action))
					++action;
#ifdef __ATTR_ACTION_SKIP
				if (libc_strcmp(action, "skip") == 0) {
					*action_endp++ = __ATTR_ACTION_SKIP;
				} else
#endif /* __ATTR_ACTION_SKIP */
#ifdef __ATTR_ACTION_PERMISSIONS
				if (libc_strcmp(action, "permissions") == 0) {
					*action_endp++ = __ATTR_ACTION_PERMISSIONS;
				} else
#endif /* __ATTR_ACTION_PERMISSIONS */
				{
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: "
					             "rule %q specifies unknown action %q",
					             config_filename, lno, line, action);
					goto next_line;
				}

				/* Print the rule into the result buffer. */
				if unlikely(libc_format_aprintf_printer(&printer, line, (size_t)(action_endp - line)) < 0) {
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename, lno);
					break;
				}
			}
next_line:
			libc_free(line);
		}

		libc_fclose(fp);


		libc_free(printer.ap_base);

	} else {
		__attr_error(ctx, "%s: cannot open file: %m", config_filename);
	}
return_fallback:
#endif /* __FPARSELN_UNESCALL */

	/* Fallback: return default actions */
	return default_actions;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(attr_copy_check_permissions, libc_attr_copy_check_permissions);
DEFINE_PUBLIC_ALIAS(attr_copy_action, libc_attr_copy_action);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ATTR_LIBATTR_C */
