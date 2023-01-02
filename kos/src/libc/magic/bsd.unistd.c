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
/* (#) Portability: libbsd  (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5 (/include/bsd/unistd.h) */
}

%[define_replacement(errno_t = __errno_t)]

%[insert:prefix(
#include <unistd.h>
)]%[insert:prefix(
#include <fcntl.h> /* As seen in `libc4/5' */
)]%[insert:prefix(
#include <sys/stat.h> /* As seen in `libc4/5' */
)]%[insert:prefix(
#include <sys/time.h> /* As seen in `libc4/5' */
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

//TODO:optreset
//TODO:%[insert:extern(bsd_getopt)]

%[insert:extern(getmode)]
%[insert:extern(setmode)]

%[insert:extern(closefrom)]

%[insert:extern(setproctitle)]

%[insert:extern(getpeereid)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
