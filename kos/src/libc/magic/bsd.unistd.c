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
/* (#) Portability: libbsd  (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5 (/include/bsd/unistd.h) */
/*!always_includes <unistd.h>*/
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

/* >> optreset(3)
 * When set to non-zero, the next call to `getopt(3)' will reset the internal
 * parser. The resulting behavior is the same as when `optind' is set to `0'.
 * Once the reset is done, this variable is set to `0' again.
 *
 * Pre-initialized to `0' */
#ifndef optreset
#ifdef __LOCAL_optreset
#define optreset __LOCAL_optreset
#elif defined(__CRT_HAVE_optreset)
__CSDECLARE(,int,optreset)
#define optreset optreset
#endif /* ... */
#endif /* !optreset */

}

/* Like normal `getopt(3)', except guarantied to support `optreset(3)'
 * Since our `getopt(3)' already supports this by default, we can just
 * link in `bsd_getopt(3)' as an alias to it. */
%[insert:function(bsd_getopt = getopt)]

%[insert:extern(getmode)]
%[insert:extern(setmode)]

%[insert:extern(closefrom)]

%[insert:extern(setproctitle)]

%[insert:extern(getpeereid)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
