/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: libc4/5 (/include/bsd/signal.h) */
/*!always_includes <signal.h>*/
}

%[insert:prefix(
#include <signal.h>
)]%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sig_t_defined
#define __sig_t_defined
typedef __sighandler_t sig_t;
#endif /* !__sig_t_defined */

}


%[insert:function(__bsd_signal = bsd_signal)]
%[insert:pp_if($has_function(bsd_signal))]
%#undef signal
%#define signal __bsd_signal
%[insert:pp_endif]

%{

__SYSDECL_END
#endif /* __CC__ */

}
