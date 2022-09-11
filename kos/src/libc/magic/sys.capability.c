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
/* (#) Portability: diet libc (/include/sys/capability.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.capability")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/xattr.h>
)]%[insert:prefix(
#include <linux/capability.h>
)]%[insert:prefix(
#include <linux/xattr.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <stdint.h>
#include <linux/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

struct _cap_struct;
typedef struct _cap_struct *cap_t;
typedef int cap_value_t;
typedef enum {
	CAP_EFFECTIVE   = 0, /* TODO:DOC */
	CAP_PERMITTED   = 1, /* TODO:DOC */
	CAP_INHERITABLE = 2  /* TODO:DOC */
} cap_flag_t;
typedef enum {
	CAP_CLEAR = 0, /* TODO:DOC */
	CAP_SET   = 1  /* TODO:DOC */
} cap_flag_value_t;

#define CAP_DIFFERS(result, flag) (((result) & (1 << (flag))) != 0)

#define CAP_IS_SUPPORTED(cap) (cap_get_bound(cap) >= 0)

#if 1 /* From libcap (currently missing on KOS) */
extern cap_t cap_dup(cap_t __a);
extern int cap_free(void *__a);
extern cap_t cap_init(void);
extern int cap_get_flag(cap_t __a, cap_value_t __b, cap_flag_t __c, cap_flag_value_t *__d);
extern int cap_set_flag(cap_t __a, cap_flag_t __b, int __c, cap_value_t const *__d, cap_flag_value_t __e);
extern int cap_clear(cap_t __a);
extern int cap_clear_flag(cap_t __a, cap_flag_t __b);
extern cap_t cap_get_fd(int __a);
extern cap_t cap_get_file(char const *__a);
extern int cap_set_fd(int __a, cap_t __b);
extern int cap_set_file(char const *__a, cap_t __b);
extern cap_t cap_get_proc(void);
extern cap_t cap_get_pid(pid_t __a);
extern int cap_set_proc(cap_t __a);
extern int cap_get_bound(cap_value_t __a);
extern int cap_drop_bound(cap_value_t __a);
extern ssize_t cap_size(cap_t __a);
extern ssize_t cap_copy_ext(void *__a, cap_t __b, ssize_t __c);
extern cap_t cap_copy_int(void const *__a);
extern cap_t cap_from_text(char const *__a);
extern char *cap_to_text(cap_t __a, ssize_t *__b);
extern int cap_from_name(char const *__a, cap_value_t *__b);
extern char *cap_to_name(cap_value_t __a);
extern int cap_compare(cap_t __a, cap_t __b);
extern int capgetp(pid_t __pid, cap_t __cap_d);
extern int capsetp(pid_t __pid, cap_t __cap_d);
#endif /* libcap... */


}

%[define_replacement(cap_t = "struct _cap_struct *")]
%[define_replacement(cap_value_t = int)]
%[define_replacement(cap_flag_t = int)]
%[define_replacement(cap_flag_value_t = int)]
%[define_replacement(cap_user_header_t = "struct __user_cap_header_struct *")]
%[define_replacement(cap_user_data_t = "struct __user_cap_data_struct *")]
%[define_replacement("cap_user_data_t const" = "struct __user_cap_data_struct const *")]

/* Only the actual system calls are defined by libc. */

@@>> capset(2)
int capset(cap_user_header_t header, cap_user_data_t data);

@@>> capget(2)
int capget(cap_user_header_t header, cap_user_data_t const data);

%{

__SYSDECL_END
#endif /* __CC__ */

}
