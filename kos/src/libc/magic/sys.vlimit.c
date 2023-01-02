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
%(c_prefix){
/* (#) Portability: GNU C Library (/resource/sys/vlimit.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/vlimit.h>
)]%{


/* Accepted codes for `resource' argument of `vlimit(3)' */
#if !defined(LIM_NORAISE) && defined(__LIM_NORAISE)
#define LIM_NORAISE __LIM_NORAISE /* Unsupported */
#endif /* !LIM_NORAISE && __LIM_NORAISE */
#if !defined(LIM_CPU) && defined(__LIM_CPU)
#define LIM_CPU     __LIM_CPU     /* s.a. `RLIMIT_CPU' */
#endif /* !LIM_CPU && __LIM_CPU */
#if !defined(LIM_FSIZE) && defined(__LIM_FSIZE)
#define LIM_FSIZE   __LIM_FSIZE   /* s.a. `RLIMIT_FSIZE' */
#endif /* !LIM_FSIZE && __LIM_FSIZE */
#if !defined(LIM_DATA) && defined(__LIM_DATA)
#define LIM_DATA    __LIM_DATA    /* s.a. `RLIMIT_DATA' */
#endif /* !LIM_DATA && __LIM_DATA */
#if !defined(LIM_STACK) && defined(__LIM_STACK)
#define LIM_STACK   __LIM_STACK   /* s.a. `RLIMIT_STACK' */
#endif /* !LIM_STACK && __LIM_STACK */
#if !defined(LIM_CORE) && defined(__LIM_CORE)
#define LIM_CORE    __LIM_CORE    /* s.a. `RLIMIT_CORE' */
#endif /* !LIM_CORE && __LIM_CORE */
#if !defined(LIM_MAXRSS) && defined(__LIM_MAXRSS)
#define LIM_MAXRSS  __LIM_MAXRSS  /* s.a. `RLIMIT_RSS' */
#endif /* !LIM_MAXRSS && __LIM_MAXRSS */


/* No limit.
 * WARNING: <math.h> also defines a macro `INFINITY'. - Both are guarded by #ifndef,
 *          but if you include both headers, you'll only get the first one's #define
 *          for this macro! */
#if !defined(INFINITY) && defined(__VLIMIT_INFINITY)
#define INFINITY __VLIMIT_INFINITY
#endif /* !INFINITY && __VLIMIT_INFINITY */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> vlimit(3)
@@Ancient wrapper for `setrlimit(2)' (s.a. `struct rlimit::rlim_cur')
@@@param: resource: One of `LIM_*' (see above)
@@@param: value:    Value to assign to `resource'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[requires_include("<asm/os/resource.h>")]]
[[requires($has_function(getrlimit) && $has_function(setrlimit))]]
[[impl_include("<asm/os/vlimit.h>", "<asm/os/resource.h>")]]
[[impl_include("<bits/os/rlimit.h>", "<libc/errno.h>")]]
[[section(".text.crt.compat.glibc")]]
int vlimit(int resource, int value) {
	@struct rlimit@ rlim;
	int rlimit_resource, result;
@@pp_ifdef __LIM_TO_RLIMIT@@
	rlimit_resource = __LIM_TO_RLIMIT(resource);
@@pp_else@@
	switch (resource) {

@@pp_if defined(__LIM_CPU) && defined(__RLIMIT_CPU)@@
	case __LIM_CPU:
		rlimit_resource = __RLIMIT_CPU;
@@pp_endif@@

@@pp_if defined(__LIM_FSIZE) && defined(__RLIMIT_FSIZE)@@
	case __LIM_FSIZE:
		rlimit_resource = __RLIMIT_FSIZE;
@@pp_endif@@

@@pp_if defined(__LIM_DATA) && defined(__RLIMIT_DATA)@@
	case __LIM_DATA:
		rlimit_resource = __RLIMIT_DATA;
@@pp_endif@@

@@pp_if defined(__LIM_STACK) && defined(__RLIMIT_STACK)@@
	case __LIM_STACK:
		rlimit_resource = __RLIMIT_STACK;
@@pp_endif@@

@@pp_if defined(__LIM_CORE) && defined(__RLIMIT_CORE)@@
	case __LIM_CORE:
		rlimit_resource = __RLIMIT_CORE;
@@pp_endif@@

@@pp_if defined(__LIM_MAXRSS) && defined(__RLIMIT_RSS)@@
	case __LIM_MAXRSS:
		rlimit_resource = __RLIMIT_RSS;
@@pp_endif@@

	default:
@@pp_ifdef EINVAL@@
		return __libc_seterrno(EINVAL);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}
@@pp_endif@@
	result = getrlimit((__rlimit_resource_t)rlimit_resource, &rlim);
	if likely(result == 0) {
		rlim.@rlim_cur@ = (__rlim_t)                     /* Cast to correct type. */
		                  (__CRT_PRIVATE_SINT(__SIZEOF_RLIM_T__)) /* Sign expansion... */
		                  (int)value;
		result = setrlimit((__rlimit_resource_t)rlimit_resource, &rlim);
	}
	return result;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
