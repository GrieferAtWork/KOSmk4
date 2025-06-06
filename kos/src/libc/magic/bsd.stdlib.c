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
/* (#) Portability: libbsd  (/include/bsd/stdlib.h) */
/* (#) Portability: libc4/5 (/include/bsd/stdlib.h) */
/*!always_includes <stdlib.h>*/
}

%[insert:prefix(
#include <stdlib.h>
)]%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/stat.h>
)]%[insert:prefix(
#include <stdint.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

//TODO:%[insert:extern(arc4random)]
//TODO:%[insert:extern(arc4random_stir)]
//TODO:%[insert:extern(arc4random_addrandom)]
//TODO:%[insert:extern(arc4random_buf)]
//TODO:%[insert:extern(arc4random_uniform)]

%[insert:extern(dehumanize_number)]

%[insert:extern(getprogname)]
%[insert:extern(setprogname)]

%[insert:extern(heapsort)]
%[insert:extern(mergesort)]
%[insert:extern(radixsort)]
%[insert:extern(sradixsort)]

%[insert:extern(reallocf)]
%[insert:extern(reallocarray)]
%[insert:extern(recallocarray)]
%[insert:extern(freezero)]

%[insert:extern(strtonum)]
%[insert:extern(getbsize)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
