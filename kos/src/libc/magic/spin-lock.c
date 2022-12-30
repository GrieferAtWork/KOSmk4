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
/* (#) Portability: GNU C Library (/mach/spin-lock.h) */
/* (#) Portability: GNU Hurd      (/usr/include/spin-lock.h) */
}

%[default:section(".text.crt{|.dos}.compat.hurd.futex")]
%[default:nodos]

%{
#include <lock-intern.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef __spin_lock_t spin_lock_t;
#define SPIN_LOCK_INITIALIZER __SPIN_LOCK_INITIALIZER

}

%[insert:pp_if($has_function(__spin_lock_init))]
%#define spin_lock_init(lock) __spin_lock_init(lock)
%[insert:pp_endif]
%[insert:pp_if($has_function(__spin_lock))]
%#define spin_lock(lock) __spin_lock(lock)
%[insert:pp_endif]
%[insert:pp_if($has_function(__spin_try_lock))]
%#define spin_try_lock(lock) __spin_try_lock(lock)
%[insert:pp_endif]
%[insert:pp_if($has_function(__spin_unlock))]
%#define spin_unlock(lock) __spin_unlock(lock)
%[insert:pp_endif]
%[insert:pp_if($has_function(__spin_lock_locked))]
%#define spin_lock_locked(lock) __spin_lock_locked(lock)
%[insert:pp_endif]

%{

__SYSDECL_END
#endif /* __CC__ */

}
