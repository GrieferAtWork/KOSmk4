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
[[nodos]] /* TODO */
int attr_copy_file([[in]] char const *src_path, [[in]] char const *dst_path,
                   [[nullable]] int (LIBKCALL *check)(char const *, struct error_context *),
                   [[inout_opt]] struct error_context *ctx);

@@>> attr_copy_fd(3)
@@Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
@@returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
@@copied.
@@@param: src_path: The name of `src_fd' (only used for error messages)
@@@param: dst_path: The name of `dst_fd' (only used for error messages)
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno' and `ctx')
[[decl_include("<attr/error_context.h>", "<bits/types.h>")]]
[[nodos]] /* TODO */
int attr_copy_fd([[in_opt]] char const *src_path, $fd_t src_fd,
                 [[in_opt]] char const *dst_path, $fd_t dst_fd,
                 [[nullable]] int (LIBKCALL *check)(char const *, struct error_context *),
                 [[inout_opt]] struct error_context *ctx);

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
				__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: I/O error: %m",
				             config_filename, lno);
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
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename, lno);
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
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: "
					             "rule %q specifies unknown action %q",
					             config_filename, lno, line, action);
					goto next_line;
				}

				/* Print the rule into the result buffer. */
				if unlikely(format_aprintf_printer(&printer, line, (size_t)(action_endp - line)) < 0) {
					__attr_error(ctx, "%s:%" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u: print error: %m",
					             config_filename, lno);
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
		__attr_error(ctx, "%s: cannot open file: %m", config_filename);
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
