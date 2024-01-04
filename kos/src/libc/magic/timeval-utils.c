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
%(c_prefix){
/* (#) Portability: libiberty (/include/timeval-utils.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/timeval.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[no_crt_self_import, decl_include("<bits/os/timeval.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timeval_add")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timeval_add64")]]
[[impl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
void timeval_add([[out]] struct timeval *result,
                 [[in]] struct timeval const *lhs,
                 [[in]] struct timeval const *rhs) {
	result->@tv_sec@  = lhs->@tv_sec@  + rhs->@tv_sec@;
	result->@tv_usec@ = lhs->@tv_usec@ + rhs->@tv_usec@;
	if ((__suseconds_t)result->@tv_usec@ >= (__suseconds_t)USEC_PER_SEC) {
		result->@tv_usec@ -= USEC_PER_SEC;
		++result->@tv_sec@;
	}
}

[[no_crt_self_import, decl_include("<bits/os/timeval.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timeval_sub")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timeval_sub64")]]
[[impl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
void timeval_sub([[out]] struct timeval *result,
                 [[in]] struct timeval const *lhs,
                 [[in]] struct timeval const *rhs) {
	result->@tv_sec@  = lhs->@tv_sec@  - rhs->@tv_sec@;
	result->@tv_usec@ = lhs->@tv_usec@ - rhs->@tv_usec@;
	if ((__suseconds_t)result->@tv_usec@ < 0) {
		result->@tv_usec@ += USEC_PER_SEC;
		--result->@tv_sec@;
	}
}


%
%#ifdef __USE_TIME64

[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(timeval_add), doc_alias("timeval_add")]]
[[impl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
void timeval_add64([[out]] struct timeval64 *result,
                   [[in]] struct timeval64 const *lhs,
                   [[in]] struct timeval64 const *rhs) {
	result->@tv_sec@  = lhs->@tv_sec@  + rhs->@tv_sec@;
	result->@tv_usec@ = lhs->@tv_usec@ + rhs->@tv_usec@;
	if ((__suseconds_t)result->@tv_usec@ >= (__suseconds_t)USEC_PER_SEC) {
		result->@tv_usec@ -= USEC_PER_SEC;
		++result->@tv_sec@;
	}
}

[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(timeval_sub), doc_alias("timeval_sub")]]
[[impl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
void timeval_sub64([[out]] struct timeval64 *result,
                   [[in]] struct timeval64 const *lhs,
                   [[in]] struct timeval64 const *rhs) {
	result->@tv_sec@  = lhs->@tv_sec@  - rhs->@tv_sec@;
	result->@tv_usec@ = lhs->@tv_usec@ - rhs->@tv_usec@;
	if ((__suseconds_t)result->@tv_usec@ < (__suseconds_t)USEC_PER_SEC) {
		result->@tv_usec@ += USEC_PER_SEC;
		--result->@tv_sec@;
	}
}

%#endif /* __USE_TIME64 */

%{

__SYSDECL_END
#endif /* __CC__ */

}
