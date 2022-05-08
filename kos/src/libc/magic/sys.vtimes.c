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
/* (#) Portability: GNU C Library (/resource/sys/vtimes.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/vtimes.h>
)]%{

/* Granularity of `struct vtimes::vm_utime' and `struct vtimes::vm_stime' */
#if !defined(VTIMES_UNITS_PER_SECOND) && defined(__VTIMES_UNITS_PER_SECOND)
#define VTIMES_UNITS_PER_SECOND __VTIMES_UNITS_PER_SECOND
#endif /* !VTIMES_UNITS_PER_SECOND && __VTIMES_UNITS_PER_SECOND */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> vtimes(3)
@@Return  timing information about the calling process
@@(in `*current'), or its children (in `*child'). This
@@is an old function which  you should no longer  use,
@@and  is implemented as a wrapper for `getrusage(2)'.
@@
@@@param: current: When non-NULL, fill with timings for the calling process. (s.a. `RUSAGE_SELF')
@@@param: child:   When non-NULL, fill with timings for child processes. (s.a. `RUSAGE_CHILDREN')
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/crt/vtimes.h>")]]
[[requires_include("<asm/os/resource.h>")]]
[[requires(defined(__RUSAGE_SELF) && defined(__RUSAGE_CHILDREN) && $has_function(getrusage))]]
[[impl_include("<asm/os/resource.h>", "<bits/os/rusage.h>", "<bits/crt/vtimes.h>")]]
[[section(".text.crt.compat.glibc")]]
int vtimes(struct vtimes *current, struct vtimes *child) {
	int result = 0;
	unsigned int i;
	for (i = 0; i < 2; ++i) {
		struct rusage ru;
		@struct vtimes@ *slot = i ? child : current;
		if (!slot)
			continue;
		result = getrusage((__rusage_who_t)(i ? __RUSAGE_CHILDREN : __RUSAGE_SELF), &ru);
		if unlikely(result != 0)
			break;
		slot->@vm_utime@ = ((ru.@ru_utime@.@tv_sec@ * __VTIMES_UNITS_PER_SECOND) +
		                    ((ru.@ru_utime@.@tv_usec@ * __VTIMES_UNITS_PER_SECOND) / 1000000));
		slot->@vm_stime@ = ((ru.@ru_stime@.@tv_sec@ * __VTIMES_UNITS_PER_SECOND) +
		                    ((ru.@ru_stime@.@tv_usec@ * __VTIMES_UNITS_PER_SECOND) / 1000000));
		slot->@vm_idsrss@ = ru.@ru_idrss@ + ru.@ru_isrss@;
		slot->@vm_majflt@ = ru.@ru_majflt@;
		slot->@vm_minflt@ = ru.@ru_minflt@;
		slot->@vm_nswap@ = ru.@ru_nswap@;
		slot->@vm_inblk@ = ru.@ru_inblock@;
		slot->@vm_oublk@ = ru.@ru_oublock@;
	}
	return result;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
