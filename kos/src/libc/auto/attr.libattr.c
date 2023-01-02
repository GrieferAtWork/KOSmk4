/* HASH CRC-32:0x655a364e */
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
#ifndef GUARD_LIBC_AUTO_ATTR_LIBATTR_C
#define GUARD_LIBC_AUTO_ATTR_LIBATTR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "attr.libattr.h"
#include "../user/ctype.h"
#include "fnmatch.h"
#include "format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.xattr.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> attr_copy_file(3)
 * Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
 * returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
 * copied.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_file)(char const *src_path,
                                          char const *dst_path,
                                          int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                                          struct error_context *ctx) {
	return libc_attr_copy_impl(src_path, -1, dst_path, -1, check, ctx);
}
/* >> attr_copy_fd(3)
 * Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
 * returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
 * copied.
 * @param: src_path: The name of `src_fd' (only used for error messages)
 * @param: dst_path: The name of `dst_fd' (only used for error messages)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_INOUT_OPT(6) ATTR_IN_OPT(1) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_fd)(char const *src_path,
                                        fd_t src_fd,
                                        char const *dst_path,
                                        fd_t dst_fd,
                                        int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                                        struct error_context *ctx) {
	return libc_attr_copy_impl(src_path, src_fd, dst_path, dst_fd, check, ctx);
}
#include <libc/errno.h>
#include <bits/types.h>
#include <attr/error_context.h>
#include <bits/crt/inttypes.h>
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_INOUT_OPT(6) ATTR_IN_OPT(1) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_impl)(char const *src_path,
                                          fd_t src_fd,
                                          char const *dst_path,
                                          fd_t dst_fd,
                                          int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                                          struct error_context *ctx) {
	int result = 0;
	ssize_t nameslen, nameslen2;
	char *namesbuf, *iter, *end;
	void *valbuf = NULL;
	size_t valbuflen = 0;
	if (check == NULL)
		check = &libc_attr_copy_check_permissions;

	/* Ask kernel know much space we need for names */
	nameslen = src_fd != -1 ? libc_flistxattr(src_fd, NULL, 0)
	                        : libc_llistxattr(src_path, NULL, 0);
	if unlikely(nameslen == -1) {
err_listxattr_failed:
		/* Special handling for ENOSYS, ENOTSUP and EOPNOTSUPP
		 * - ENOSYS indicates that the kernel doesn't support extended attributes
		 * - ENOTSUP and EOPNOTSUPP  indicate that `src_path'  / `src_fd'  don't
		 *   support extended attributes (which we must treat the same as though
		 *   the source file didn't have any attributes at all) */


		{
			errno_t err = __libc_geterrno();
			if (err == ENOSYS)
				return 0;

			if (err == ENOTSUP)
				return 0;

#if EOPNOTSUPP != ENOTSUP
			if (err == EOPNOTSUPP)
				return 0;
#endif /* EOPNOTSUPP != ENOTSUP */
		}

















		{
			char const *src_path_q = __attr_quote(ctx, src_path);
			__attr_error(ctx, "%s: cannot list attributes: %m", src_path_q);
			__attr_quote_free(ctx, src_path_q);
		}
		return -1;
	}

malloc_again:
	namesbuf = (char *)__malloca(((size_t)nameslen + 1) * sizeof(char));
#ifdef __malloca_mayfail
	if unlikely(!namesbuf)
		return -1;
#endif /* __malloca_mayfail */

	/* Load names form kernel-space */
	nameslen2 = src_fd != -1 ? libc_flistxattr(src_fd, namesbuf, (size_t)nameslen)
	                         : libc_llistxattr(src_path, namesbuf, (size_t)nameslen);
	if unlikely(nameslen2 == -1) {
		__freea(namesbuf);
		goto err_listxattr_failed;
	}
	if unlikely((size_t)nameslen2 > (size_t)nameslen) {
		__freea(namesbuf);
		goto malloc_again;
	}

	/* Ensure that the names-buffer is NUL terminated */
	namesbuf[(size_t)nameslen2] = '\0';
	end = namesbuf + nameslen2;

	/* Allocate an initial buffer */
	if (nameslen2) {

		valbuf = libc_malloc(512);



		if likely(valbuf)
			valbuflen = 512;
	}

	/* Enumerate attribute names */
	for (iter = namesbuf; iter < end; iter = libc_strend(iter) + 1) {
		ssize_t attrlen;
		int seterr;
		if unlikely(!*iter)
			continue; /* Skip empty names (shouldn't happen) */
		if (!(*check)(iter, ctx))
			continue; /* Skip attributes which our caller doesn't want us to copy. */

		/* Ask the kernel for the attribute's value */
again_read_attr:
		attrlen = src_fd != -1 ? libc_fgetxattr(src_fd, iter, valbuf, valbuflen)
		                       : libc_lgetxattr(src_path, iter, valbuf, valbuflen);
		if (attrlen == -1) {
			char const *src_path_q = __attr_quote(ctx, src_path);
			char const *iter_q     = __attr_quote(ctx, iter);
			__attr_error(ctx, "%s: failed to get attribute %s: %m", src_path_q, iter_q);
			__attr_quote_free(ctx, iter_q);
			__attr_quote_free(ctx, src_path_q);
			result = -1;
			continue;
		}

		/* Handle case where our buffer is too small. */
		if ((size_t)attrlen > valbuflen) {
			void *new_valbuf;
			new_valbuf = libc_realloc(valbuf, (size_t)attrlen);
			if unlikely(!new_valbuf) {
				char const *src_path_q = __attr_quote(ctx, src_path);
				char const *iter_q     = __attr_quote(ctx, iter);
				__attr_error(ctx, "%s: failed to allocate %" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u "
				                  "bytes for attribute %s: %m",
				             src_path_q, (size_t)attrlen, iter_q);
				__attr_quote_free(ctx, iter_q);
				__attr_quote_free(ctx, src_path_q);
				result = -1;
				continue;
			}
			valbuf    = new_valbuf;
			valbuflen = (size_t)attrlen;
			goto again_read_attr;
		}

		seterr = dst_fd != -1 ? libc_fsetxattr(dst_fd, iter, valbuf, valbuflen, 0)
		                      : libc_lsetxattr(dst_path, iter, valbuf, valbuflen, 0);
		if unlikely(seterr != 0) {
			char const *dst_path_q = __attr_quote(ctx, dst_path);
			char const *iter_q     = __attr_quote(ctx, iter);
			__attr_error(ctx, "%s: failed to set attribute %s: %m", dst_path_q, iter_q);
			__attr_quote_free(ctx, iter_q);
			__attr_quote_free(ctx, dst_path_q);
			result = -1;
		}
	}


	libc_free(valbuf);

	__freea(namesbuf);
	return result;
}
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
				char const *config_filename_q = __attr_quote(ctx, config_filename);
				__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: I/O error: %m",
				             config_filename_q, lno);
				__attr_quote_free(ctx, config_filename_q);
				break;
			}

			/* Check for error */
			if (!*line) {
				char *result;
				libc_free(line);

				libc_fclose(fp);

				result = libc_format_aprintf_pack(&printer, NULL);
				if unlikely(!result) {
					char const *config_filename_q = __attr_quote(ctx, config_filename);
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename_q, lno);
					__attr_quote_free(ctx, config_filename_q);
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
					char const *config_filename_q = __attr_quote(ctx, config_filename);
					char const *line_q            = __attr_quote(ctx, line);
					char const *action_q          = __attr_quote(ctx, action);
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: "
					             "rule %s specifies unknown action %s",
					             config_filename_q, lno, line_q, action_q);
					__attr_quote_free(ctx, action_q);
					__attr_quote_free(ctx, line_q);
					__attr_quote_free(ctx, config_filename_q);
					goto next_line;
				}

				/* Print the rule into the result buffer. */
				if unlikely(libc_format_aprintf_printer(&printer, line, (size_t)(action_endp - line)) < 0) {
					char const *config_filename_q = __attr_quote(ctx, config_filename);
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename_q, lno);
					__attr_quote_free(ctx, config_filename_q);
					break;
				}
			}
next_line:
			libc_free(line);
		}

		libc_fclose(fp);


		libc_free(printer.ap_base);

	} else {
		char const *config_filename_q = __attr_quote(ctx, config_filename);
		__attr_error(ctx, "%s: cannot open file: %m", config_filename_q);
		__attr_quote_free(ctx, config_filename_q);
	}
return_fallback:
#endif /* __FPARSELN_UNESCALL */

	/* Fallback: return default actions */
	return default_actions;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(attr_copy_file, libc_attr_copy_file);
DEFINE_PUBLIC_ALIAS(attr_copy_fd, libc_attr_copy_fd);
DEFINE_PUBLIC_ALIAS(attr_copy_check_permissions, libc_attr_copy_check_permissions);
DEFINE_PUBLIC_ALIAS(attr_copy_action, libc_attr_copy_action);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ATTR_LIBATTR_C */
