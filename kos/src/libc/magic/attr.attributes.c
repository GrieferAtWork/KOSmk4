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
/* (#) Portability: libattr (/include/attributes.h) */
}

%[default:section(".text.crt{|.dos}.libattr")]
%[define_replacement(fd_t = __fd_t)]

%[define_decl_include_implication("<attr/bits/attributes.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<attr/bits/attributes.h>": [
	"struct attrlist",
	"struct attrlist_ent",
	"struct attrlist_cursor",
	"struct attr_multiop",
])]


%[insert:prefix(
#include <attr/asm/attributes.h>
)]%[insert:prefix(
#include <attr/bits/attributes.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <errno.h>
)]%{

#if !defined(ENOATTR) && defined(ENODATA)
#define ENOATTR ENODATA
#endif /* !ENOATTR && ENODATA */

/* Max size for attribute values */
#if !defined(ATTR_MAX_VALUELEN) && defined(__ATTR_MAX_VALUELEN)
#define ATTR_MAX_VALUELEN __ATTR_MAX_VALUELEN /* Max size for attribute values */
#endif /* !ATTR_MAX_VALUELEN && __ATTR_MAX_VALUELEN */

/* Possible values for the `flags' arguments of functions from `<attr/attributes.h>' */
#if !defined(ATTR_DONTFOLLOW) && defined(__ATTR_DONTFOLLOW)
#define ATTR_DONTFOLLOW __ATTR_DONTFOLLOW /* Don't follow symbolic links */
#endif /* !ATTR_DONTFOLLOW && __ATTR_DONTFOLLOW */
#if !defined(ATTR_ROOT) && defined(__ATTR_ROOT)
#define ATTR_ROOT __ATTR_ROOT /* Prefix attribute names with "trusted." or "xfsroot." (else: ATTR_SECURE) */
#endif /* !ATTR_ROOT && __ATTR_ROOT */
#if !defined(ATTR_TRUST) && defined(__ATTR_TRUST)
#define ATTR_TRUST __ATTR_TRUST /* Ignored... */
#endif /* !ATTR_TRUST && __ATTR_TRUST */
#if !defined(ATTR_SECURE) && defined(__ATTR_SECURE)
#define ATTR_SECURE __ATTR_SECURE /* Prefix attribute names with "security." (else: prefix with "user.") */
#endif /* !ATTR_SECURE && __ATTR_SECURE */
#if !defined(ATTR_CREATE) && defined(__ATTR_CREATE)
#define ATTR_CREATE __ATTR_CREATE /* Create new attribute, fail if attribute already exists (s.a. `XATTR_CREATE') */
#endif /* !ATTR_CREATE && __ATTR_CREATE */
#if !defined(ATTR_REPLACE) && defined(__ATTR_REPLACE)
#define ATTR_REPLACE __ATTR_REPLACE /* Replace existing attribute, fail if attribute doesn't already exists (s.a. `XATTR_REPLACE') */
#endif /* !ATTR_REPLACE && __ATTR_REPLACE */

/* Max allowed value for `attr_multi[f]::count' */
#if !defined(ATTR_MAX_MULTIOPS) && defined(__ATTR_MAX_MULTIOPS)
#define ATTR_MAX_MULTIOPS __ATTR_MAX_MULTIOPS /* Max allowed value for `attr_multi[f]::count' */
#endif /* !ATTR_MAX_MULTIOPS && __ATTR_MAX_MULTIOPS */

/* Possible values for `struct attr_multiop::am_opcode' */
#if !defined(ATTR_OP_GET) && defined(__ATTR_OP_GET)
#define ATTR_OP_GET __ATTR_OP_GET /* Perform a call to `attr_get(3)' or `attr_getf(3)' */
#endif /* !ATTR_OP_GET && __ATTR_OP_GET */
#if !defined(ATTR_OP_SET) && defined(__ATTR_OP_SET)
#define ATTR_OP_SET __ATTR_OP_SET /* Perform a call to `attr_set(3)' or `attr_setf(3)' */
#endif /* !ATTR_OP_SET && __ATTR_OP_SET */
#if !defined(ATTR_OP_REMOVE) && defined(__ATTR_OP_REMOVE)
#define ATTR_OP_REMOVE __ATTR_OP_REMOVE /* Perform a call to `attr_remove(3)' or `attr_removef(3)' */
#endif /* !ATTR_OP_REMOVE && __ATTR_OP_REMOVE */

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct attrlist attrlist_t;
typedef struct attrlist_ent attrlist_ent_t;
typedef struct attrlist_cursor attrlist_cursor_t;
typedef struct attr_multiop attr_multiop_t;

#define ATTR_ENTRY(buf, i) \
	((struct attrlist_ent *)((__BYTE_TYPE__ *)(buf) + ((struct attrlist const *)(buf))->al_offset[i]))

}

%[define_replacement(ATTR_MAX_VALUELEN = __ATTR_MAX_VALUELEN)] /* Max size for attribute values */
%[define_replacement(ATTR_DONTFOLLOW = __ATTR_DONTFOLLOW)]     /* Don't follow symbolic links */
%[define_replacement(ATTR_ROOT = __ATTR_ROOT)]                 /* Prefix attribute names with "trusted." or "xfsroot." (else: ATTR_SECURE) */
%[define_replacement(ATTR_TRUST = __ATTR_TRUST)]               /* Ignored... */
%[define_replacement(ATTR_SECURE = __ATTR_SECURE)]             /* Prefix attribute names with "security." (else: prefix with "user.") */
%[define_replacement(ATTR_CREATE = __ATTR_CREATE)]             /* Create new attribute, fail if attribute already exists (s.a. `XATTR_CREATE') */
%[define_replacement(ATTR_REPLACE = __ATTR_REPLACE)]           /* Replace existing attribute, fail if attribute doesn't already exists (s.a. `XATTR_REPLACE') */
%[define_replacement(ATTR_MAX_MULTIOPS = __ATTR_MAX_MULTIOPS)] /* Max allowed value for `attr_multi[f]::count' */
%[define_replacement(ATTR_OP_GET = __ATTR_OP_GET)]             /* Perform a call to `attr_get(3)' or `attr_getf(3)' */
%[define_replacement(ATTR_OP_SET = __ATTR_OP_SET)]             /* Perform a call to `attr_set(3)' or `attr_setf(3)' */
%[define_replacement(ATTR_OP_REMOVE = __ATTR_OP_REMOVE)]       /* Perform a call to `attr_remove(3)' or `attr_removef(3)' */


@@>> attr_get(3), attr_getf(3)
@@@param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[deprecated("Use `getxattr(2)' or `lgetxattr(2)' instead")]]
int attr_get([[in]] char const *path, [[in]] char const *attrname,
             [[out(*valuelength <= *valuelength)]] char *attrvalue,
             [[inout]] int *valuelength, int flags);

[[doc_alias("attr_get")]]
[[deprecated("Use `fgetxattr(2)' instead")]]
[[decl_include("<bits/types.h>")]]
int attr_getf($fd_t fd, [[in]] char const *attrname,
              [[out(*valuelength <= *valuelength)]] char *attrvalue,
              [[inout]] int *valuelength, int flags);





@@>> attr_set(3), attr_setf(3)
@@@param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_CREATE | ATTR_REPLACE | ATTR_SECURE | ATTR_ROOT'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[deprecated("Use `setxattr(2)' or `lsetxattr(2)' instead")]]
int attr_set([[in]] char const *path, [[in]] char const *attrname,
             [[in(valuelength)]] char const *attrvalue, int valuelength,
             int flags);

[[doc_alias("attr_set")]]
[[deprecated("Use `fsetxattr(2)' instead")]]
[[decl_include("<bits/types.h>")]]
int attr_setf($fd_t fd, [[in]] char const *attrname,
              [[in(valuelength)]] char const *attrvalue, int valuelength,
              int flags);





@@>> attr_remove(3), attr_removef(3)
@@@param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[deprecated("Use `removexattr(2)' or `lremovexattr(2)' instead")]]
int attr_remove([[in]] char const *path, [[in]] char const *attrname, int flags);

[[doc_alias("attr_remove")]]
[[deprecated("Use `fremovexattr(2)' instead")]]
[[decl_include("<bits/types.h>")]]
int attr_removef($fd_t fd, [[in]] char const *attrname, int flags);





@@>> attr_list(3), attr_listf(3)
@@@param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[deprecated("Use `listxattr(2)' or `llistxattr(2)' instead")]]
[[decl_include("<attr/bits/attributes.h>")]]
int attr_list([[in]] char const *path,
              [[out(? <= buffersize)]] char *buffer, int buffersize,
              int flags, [[inout]] struct attrlist_cursor *cursor);

[[doc_alias("attr_list")]]
[[deprecated("Use `flistxattr(2)' instead")]]
[[decl_include("<bits/types.h>", "<attr/bits/attributes.h>")]]
int attr_listf($fd_t fd,
               [[out(? <= buffersize)]] char *buffer, int buffersize,
               int flags, [[inout]] struct attrlist_cursor *cursor);





@@>> attr_multi(3), attr_multif(3)
@@@param: flags: Set of `0 | ATTR_DONTFOLLOW'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[deprecated("Use `getxattr(2)', `setxattr(2)' and `removexattr(2)' instead")]]
[[decl_include("<attr/bits/attributes.h>")]]
[[impl_include("<attr/bits/attributes.h>")]]
[[impl_include("<libc/errno.h>", "<attr/asm/attributes.h>")]]
[[requires_include("<attr/asm/attributes.h>")]]
[[requires(defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) &&
           defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) &&
           $has_function(attr_get, attr_set, attr_remove))]]
int attr_multi([[in]] char const *path, [[inout(count)]] struct attr_multiop *oplist, int count, int flags) {
	int i, result = 0;
	if (unlikely(flags & ~ATTR_DONTFOLLOW) ||
	    unlikely(count < 0)
@@pp_ifdef ATTR_MAX_MULTIOPS@@
	    || unlikely(count > ATTR_MAX_MULTIOPS)
@@pp_endif@@
	    ) {
@@pp_ifdef EINVAL@@
		return __libc_seterrno(EINVAL);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
	for (i = 0; i < count; ++i) {
		struct attr_multiop *ent = &oplist[i];
		int ent_flags = ent->@am_flags@ | flags;
		switch (ent->@am_opcode@) {

		case ATTR_OP_GET:
			result |= attr_get(path,
			                   ent->@am_attrname@,
			                   ent->@am_attrvalue@,
			                   &ent->@am_length@,
			                   ent_flags);
			break;

		case ATTR_OP_SET:
			result |= attr_set(path,
			                   ent->@am_attrname@,
			                   ent->@am_attrvalue@,
			                   ent->@am_length@,
			                   ent_flags);
			break;

		case ATTR_OP_REMOVE:
			result |= attr_remove(path,
			                      ent->@am_attrname@,
			                      ent_flags);
			break;

		default:
@@pp_ifdef EINVAL@@
			result = __libc_seterrno(EINVAL);
@@pp_else@@
			result = __libc_seterrno(1);
@@pp_endif@@
			break;
		}
	}
	return result;
}


[[doc_alias("attr_multi")]]
[[deprecated("Use `fgetxattr(2)', `fsetxattr(2)' and `fremovexattr(2)' instead")]]
[[decl_include("<bits/types.h>", "<attr/bits/attributes.h>")]]
[[impl_include("<attr/bits/attributes.h>")]]
[[impl_include("<libc/errno.h>", "<attr/asm/attributes.h>")]]
[[requires_include("<attr/asm/attributes.h>")]]
[[requires(defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) &&
           defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) &&
           $has_function(attr_getf, attr_setf, attr_removef))]]
int attr_multif($fd_t fd, [[inout(count)]] struct attr_multiop *oplist, int count, int flags) {
	int i, result = 0;
	if (unlikely(flags & ~ATTR_DONTFOLLOW) ||
	    unlikely(count < 0)
@@pp_ifdef ATTR_MAX_MULTIOPS@@
	    || unlikely(count > ATTR_MAX_MULTIOPS)
@@pp_endif@@
	    ) {
@@pp_ifdef EINVAL@@
		return __libc_seterrno(EINVAL);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
	for (i = 0; i < count; ++i) {
		struct attr_multiop *ent = &oplist[i];
		int ent_flags = ent->@am_flags@ | flags;
		switch (ent->@am_opcode@) {

		case ATTR_OP_GET:
			result |= attr_getf(fd,
			                    ent->@am_attrname@,
			                    ent->@am_attrvalue@,
			                    &ent->@am_length@,
			                    ent_flags);
			break;

		case ATTR_OP_SET:
			result |= attr_setf(fd,
			                    ent->@am_attrname@,
			                    ent->@am_attrvalue@,
			                    ent->@am_length@,
			                    ent_flags);
			break;

		case ATTR_OP_REMOVE:
			result |= attr_removef(fd,
			                       ent->@am_attrname@,
			                       ent_flags);
			break;

		default:
@@pp_ifdef EINVAL@@
			result = __libc_seterrno(EINVAL);
@@pp_else@@
			result = __libc_seterrno(1);
@@pp_endif@@
			break;
		}
		ent->@am_error@ = __libc_geterrno_or(0);
	}
	return result;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
