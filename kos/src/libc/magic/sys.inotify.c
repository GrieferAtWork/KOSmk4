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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/inotify.h) */
/* (#) Portability: diet libc     (/include/sys/inotify.h) */
/* (#) Portability: musl libc     (/include/sys/inotify.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <linux/inotify.h>
)]%[insert:prefix(
#include <bits/types.h>   /* fd_t */
)]%{

#ifdef __USE_GLIBC
#include <stdint.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

#define __watchfd_t int
#ifdef __USE_KOS
typedef __watchfd_t watchfd_t;
#endif /* __USE_KOS */

}

%[define_replacement(__watchfd_t = int)]
%[define_replacement(watchfd_t   = int)]


@@>> inotify_init(2)
[[decl_include("<bits/types.h>")]]
[[userimpl, requires_function(inotify_init1)]]
$fd_t inotify_init(void) {
	return inotify_init1(0);
}

@@>> inotify_init1(2)
@@@param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK'
[[decl_include("<features.h>", "<bits/types.h>")]]
$fd_t inotify_init1(__STDC_INT_AS_UINT_T flags);

@@>> inotify_add_watch(2)
@@@param: mask: Set of `IN_ALL_EVENTS | ...'
[[decl_include("<bits/types.h>")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(inotify_add_watch_at))]]
[[impl_include("<linux/inotify.h>"), crt_dos_variant]]
__watchfd_t inotify_add_watch($fd_t notify_fd, char const *pathname, $uint32_t mask) {
	$atflag_t atflags = 0;
@@pp_if defined(@IN_DONT_FOLLOW@) && defined(__AT_SYMLINK_NOFOLLOW)@@
	if (mask & @IN_DONT_FOLLOW@) {
		atflags |= __AT_SYMLINK_NOFOLLOW;
		mask &= ~@IN_DONT_FOLLOW@;
	}
@@pp_endif@@
	return inotify_add_watch_at(notify_fd, __AT_FDCWD, pathname, atflags, mask);
}

@@>> inotify_rm_watch(2)
@@@param: wd: Watch fd (as returned by `inotify_add_watch{_at}')
[[decl_include("<bits/types.h>")]]
int inotify_rm_watch($fd_t notify_fd, __watchfd_t wd);



%
%#ifdef __USE_KOS
@@>> inotify_add_watch_at(2)
@@@param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH | AT_EMPTY_PATH'
@@@param: mask:    Set of `IN_ALL_EVENTS | ...'
[[crt_dos_variant, decl_include("<bits/types.h>")]]
__watchfd_t inotify_add_watch_at($fd_t notify_fd, $fd_t dirfd, char const *pathname,
                                 $atflag_t atflags, $uint32_t mask);
%#endif /* __USE_KOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
