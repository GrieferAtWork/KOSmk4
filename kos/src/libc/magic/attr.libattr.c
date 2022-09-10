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
%(c_prefix){
/* (#) Portability: libattr (/include/libattr.h) */
}

%[default:nodos]
%[default:section(".text.crt{|.dos}.libattr")]
%[define_replacement(fd_t = __fd_t)]

%[define_decl_include("<attr/error_context.h>": [
	"struct error_context",
])]


%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <attr/asm/libattr.h>
)]%{

/* Return values  of `attr_copy_action'  (and the  `check'
 * cb passed to `attr_copy_file(3)' and `attr_copy_fd(3)') */
#if !defined(ATTR_ACTION_SKIP) && defined(__ATTR_ACTION_SKIP)
#define ATTR_ACTION_SKIP __ATTR_ACTION_SKIP
#endif /* !ATTR_ACTION_SKIP && __ATTR_ACTION_SKIP */
#if !defined(ATTR_ACTION_PERMISSIONS) && defined(__ATTR_ACTION_PERMISSIONS)
#define ATTR_ACTION_PERMISSIONS __ATTR_ACTION_PERMISSIONS
#endif /* !ATTR_ACTION_PERMISSIONS && __ATTR_ACTION_PERMISSIONS */


#ifdef __CC__
__SYSDECL_BEGIN

struct error_context;

}

@@>> attr_copy_file(3)
@@Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
@@returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
@@copied.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno' and `ctx')
[[decl_include("<attr/error_context.h>")]]
[[requires_function(attr_copy_impl)]]
int attr_copy_file([[in]] char const *src_path, [[in]] char const *dst_path,
                   [[nullable]] int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                   [[inout_opt]] struct error_context *ctx) {
	return attr_copy_impl(src_path, -1, dst_path, -1, check, ctx);
}

@@>> attr_copy_fd(3)
@@Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
@@returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
@@copied.
@@@param: src_path: The name of `src_fd' (only used for error messages)
@@@param: dst_path: The name of `dst_fd' (only used for error messages)
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno' and `ctx')
[[decl_include("<attr/error_context.h>", "<bits/types.h>")]]
[[requires_function(attr_copy_impl)]]
int attr_copy_fd([[in_opt]] char const *src_path, $fd_t src_fd,
                 [[in_opt]] char const *dst_path, $fd_t dst_fd,
                 [[nullable]] int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                 [[inout_opt]] struct error_context *ctx) {
	return attr_copy_impl(src_path, src_fd, dst_path, dst_fd, check, ctx);
}

[[static]]
[[decl_include("<attr/error_context.h>", "<bits/types.h>")]]
[[requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA) &&
           $has_function(attr_copy_check_permissions,
                         llistxattr, flistxattr,
                         lgetxattr, fgetxattr,
                         lsetxattr, fsetxattr,
                         realloc))]]
[[dependency(attr_copy_check_permissions)]]
[[impl_include("<libc/errno.h>", "<bits/types.h>")]]
[[impl_include("<attr/error_context.h>")]]
[[impl_include("<bits/crt/inttypes.h>")]]
int attr_copy_impl([[in_opt]] char const *src_path, $fd_t src_fd,
                   [[in_opt]] char const *dst_path, $fd_t dst_fd,
                   [[nullable]] int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx),
                   [[inout_opt]] struct error_context *ctx) {
	int result = 0;
	ssize_t nameslen, nameslen2;
	char *namesbuf, *iter, *end;
	void *valbuf = NULL;
	size_t valbuflen = 0;
	if (check == NULL)
		check = &attr_copy_check_permissions;

	/* Ask kernel know much space we need for names */
	nameslen = src_fd != -1 ? flistxattr(src_fd, NULL, 0)
	                        : llistxattr(src_path, NULL, 0);
	if unlikely(nameslen == -1) {
err_listxattr_failed:
		/* Special handling for ENOSYS, ENOTSUP and EOPNOTSUPP
		 * - ENOSYS indicates that the kernel doesn't support extended attributes
		 * - ENOTSUP and EOPNOTSUPP  indicate that `src_path'  / `src_fd'  don't
		 *   support extended attributes (which we must treat the same as though
		 *   the source file didn't have any attributes at all) */
@@pp_ifdef __libc_geterrno@@
@@pp_if defined(ENOSYS) && (defined(ENOTSUP) || defined(EOPNOTSUPP))@@
		{
			errno_t err = __libc_geterrno();
			if (err == ENOSYS)
				return 0;
@@pp_ifdef ENOTSUP@@
			if (err == ENOTSUP)
				return 0;
@@pp_endif@@
@@pp_if defined(EOPNOTSUPP) && (!defined(ENOTSUP) || EOPNOTSUPP != ENOTSUP)@@
			if (err == EOPNOTSUPP)
				return 0;
@@pp_endif@@
		}
@@pp_elif defined(ENOSYS)@@
		if (__libc_geterrno() == ENOSYS)
			return 0;
@@pp_elif defined(ENOTSUP) && defined(EOPNOTSUPP) && (ENOTSUP != EOPNOTSUPP)@@
		{
			errno_t err = __libc_geterrno();
			if (err == ENOTSUP || err == EOPNOTSUPP)
				return 0;
		}
@@pp_elif defined(ENOTSUP)@@
		if (__libc_geterrno() == ENOTSUP)
			return 0;
@@pp_elif defined(EOPNOTSUPP)@@
		if (__libc_geterrno() == EOPNOTSUPP)
			return 0;
@@pp_endif@@
@@pp_endif@@
		{
			char const *src_path_q = __attr_quote(ctx, src_path);
			__attr_error(ctx, "%s: cannot list attributes: %m", src_path_q);
			__attr_quote_free(ctx, src_path_q);
		}
		return -1;
	}

malloc_again:
	namesbuf = (char *)__malloca(((size_t)nameslen + 1) * sizeof(char));
@@pp_ifdef __malloca_mayfail@@
	if unlikely(!namesbuf)
		return -1;
@@pp_endif@@

	/* Load names form kernel-space */
	nameslen2 = src_fd != -1 ? flistxattr(src_fd, namesbuf, (size_t)nameslen)
	                         : llistxattr(src_path, namesbuf, (size_t)nameslen);
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
@@pp_if $has_function(malloc)@@
		valbuf = malloc(512);
@@pp_else@@
		valbuf = realloc(NULL, 512);
@@pp_endif@@
		if likely(valbuf)
			valbuflen = 512;
	}

	/* Enumerate attribute names */
	for (iter = namesbuf; iter < end; iter = strend(iter) + 1) {
		ssize_t attrlen;
		int seterr;
		if unlikely(!*iter)
			continue; /* Skip empty names (shouldn't happen) */
		if (!(*check)(iter, ctx))
			continue; /* Skip attributes which our caller doesn't want us to copy. */

		/* Ask the kernel for the attribute's value */
again_read_attr:
		attrlen = src_fd != -1 ? fgetxattr(src_fd, iter, valbuf, valbuflen)
		                       : lgetxattr(src_path, iter, valbuf, valbuflen);
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
			new_valbuf = realloc(valbuf, (size_t)attrlen);
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

		seterr = dst_fd != -1 ? fsetxattr(dst_fd, iter, valbuf, valbuflen, 0)
		                      : lsetxattr(dst_path, iter, valbuf, valbuflen, 0);
		if unlikely(seterr != 0) {
			char const *dst_path_q = __attr_quote(ctx, dst_path);
			char const *iter_q     = __attr_quote(ctx, iter);
			__attr_error(ctx, "%s: failed to set attribute %s: %m", dst_path_q, iter_q);
			__attr_quote_free(ctx, iter_q);
			__attr_quote_free(ctx, dst_path_q);
			result = -1;
		}
	}

@@pp_if $has_function(free)@@
	free(valbuf);
@@pp_endif@@
	__freea(namesbuf);
	return result;
}


@@>> attr_copy_check_permissions(3)
@@Returns non-zero if `attr_name' should be preserved (default handler
@@for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
@@Same as `attr_copy_action(attr_name, ctx) == 0'
@@@return: == 0 : `attr_name' should not be copied
@@@return: != 0 : `attr_name' should be copied
[[decl_include("<attr/error_context.h>")]]
[[requires_function(attr_copy_action)]]
int attr_copy_check_permissions([[in]] char const *attr_name,
                                [[inout_opt]] struct error_context *ctx) {
	return attr_copy_action(attr_name, ctx) == 0;
}

@@>> attr_copy_action(3)
@@Return the default action to-be taken for `attr_name'
@@@return: 0 : No special action
@@@return: * : One of `ATTR_ACTION_*'
[[decl_include("<attr/error_context.h>")]]
[[impl_include("<bits/types.h>")]]
int attr_copy_action([[in]] char const *attr_name,
                     [[inout_opt]] struct error_context *ctx) {
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
		actions = attr_load_actions(ctx); /* Lazily load actions. */

	/* Search for the requested action. */
	for (iter = actions; *iter; iter = strend(iter) + 2) {
		if (fnmatch(iter, attr_name, 0) == 0)
			return (int)(unsigned int)(unsigned char)strend(iter)[1];
	}

	/* No special action... */
	return 0;
}

[[static, wunused, nonnull]]
[[decl_include("<attr/error_context.h>")]]
[[impl_include("<attr/error_context.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<asm/crt/util.h>")]]
[[impl_include("<bits/crt/inttypes.h>")]]
[[impl_include("<attr/asm/libattr.h>")]]
[[impl_prefix(
@@pp_ifndef __format_aprintf_data_defined@@
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
@@pp_endif@@
)]]
char const *attr_load_actions([[inout_opt]] struct error_context *ctx) {
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
@@pp_if $has_function(fopen, fparseln, format_aprintf_pack, format_aprintf_printer) && defined(__FPARSELN_UNESCALL)@@
	static char const config_filename[] = "/etc/xattr.conf";
	FILE *fp = fopen(config_filename, "r");
	if (fp) {
		size_t lno = 1;
		struct format_aprintf_data printer;
		printer.@ap_base@  = NULL;
		printer.@ap_avail@ = 0;
		printer.@ap_used@  = 0;
		for (;;) {
			char *line, *action;
			line = fparseln(fp, NULL, &lno, NULL, __FPARSELN_UNESCALL);
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
				free(line);
@@pp_if $has_function(fclose)@@
				fclose(fp);
@@pp_endif@@
				result = format_aprintf_pack(&printer, NULL);
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
			while (*action && !isspace(*action))
				++action;
			if (*action) {
				char *action_endp;
				*action++ = '\0';
				action_endp = action;
				while (*action && isspace(*action))
					++action;
@@pp_ifdef __ATTR_ACTION_SKIP@@
				if (strcmp(action, "skip") == 0) {
					*action_endp++ = __ATTR_ACTION_SKIP;
				} else
@@pp_endif@@
@@pp_ifdef __ATTR_ACTION_PERMISSIONS@@
				if (strcmp(action, "permissions") == 0) {
					*action_endp++ = __ATTR_ACTION_PERMISSIONS;
				} else
@@pp_endif@@
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
				if unlikely(format_aprintf_printer(&printer, line, (size_t)(action_endp - line)) < 0) {
					char const *config_filename_q = __attr_quote(ctx, config_filename);
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename_q, lno);
					__attr_quote_free(ctx, config_filename_q);
					break;
				}
			}
next_line:
			free(line);
		}
@@pp_if $has_function(fclose)@@
		fclose(fp);
@@pp_endif@@
@@pp_if $has_function(free)@@
		free(printer.@ap_base@);
@@pp_endif@@
	} else {
		char const *config_filename_q = __attr_quote(ctx, config_filename);
		__attr_error(ctx, "%s: cannot open file: %m", config_filename_q);
		__attr_quote_free(ctx, config_filename_q);
	}
return_fallback:
@@pp_endif@@

	/* Fallback: return default actions */
	return default_actions;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
