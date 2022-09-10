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
int attr_copy_check_permissions([[in]] char const *attr_name,
                                [[inout_opt]] struct error_context *ctx);

@@>> attr_copy_action(3)
@@Return the default action to-be taken for `attr_name'
@@@return: 0 : No special action
@@@return: * : One of `ATTR_ACTION_*'
[[decl_include("<attr/error_context.h>")]]
int attr_copy_action([[in]] char const *attr_name,
                     [[inout_opt]] struct error_context *ctx);


%{

__SYSDECL_END
#endif /* __CC__ */

}
