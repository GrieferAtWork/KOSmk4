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
/* (#) Portability: libbsd (/include/bsd/libutil.h) */
}

%[define_replacement(errno_t = __errno_t)]

%[insert:prefix(
#include <asm/crt/humanize_number.h>
)]%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <libutil.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/types.h>
)]%[insert:prefix(
#include <stdint.h>
)]%[insert:prefix(
#include <stdio.h>
)]%{

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

#ifdef __CC__
__SYSDECL_BEGIN

}

/* Already unconditionally declared in `<libutil.h>' (aka. `<util.h>') */
//%[insert:extern(fparseln)]

%[insert:extern(humanize_number)]

//TODO:int expand_number(const char *buf, uint64_t *num);

[[cp, vartypes($mode_t)]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/oflags.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(flopenat)) ||
           (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) &&
            $has_function(openat, flock, fstat, stat) &&
            ($has_function(ftruncate) || !defined(__O_TRUNC))))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>", "<bits/types.h>", "<bits/os/stat.h>")]]
$fd_t flopen(const char *path, $oflag_t flags, ...) {
@@pp_if defined(__AT_FDCWD) && $has_function(flopenat)@@
	mode_t mode;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);
	return flopenat(__AT_FDCWD, path, flags, mode);
@@pp_else@@
@@pp_ifdef __O_TRUNC@@
	int should_trunc;
@@pp_endif@@
	int flock_op;
	fd_t result;
	mode_t mode;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);
	flock_op = __LOCK_EX;
@@pp_ifdef __O_EXLOCK@@
	flags &= ~__O_EXLOCK;
@@pp_endif@@
@@pp_if defined(__O_NONBLOCK) && defined(__LOCK_NB)@@
	if (flags & __O_NONBLOCK)
		flock_op |= __LOCK_NB;
@@pp_endif@@
@@pp_ifdef __O_TRUNC@@
	should_trunc = flags & __O_TRUNC;
	flags &= ~__O_TRUNC;
@@pp_endif@@

again:
	result = open(path, flags, mode);
	if likely(result != -1) {
		@struct stat@ st_path, st_fd;
		if unlikely(flock(result, flock_op))
			goto err_r;
		if unlikely(stat(path, &st_path))
			goto restart; /* Race condition: file was deleted */
		if unlikely(fstat(result, &st_fd))
			goto restart; /* Shouldn't happen */
		if unlikely(st_path.@st_dev@ != st_fd.@st_dev@ ||
		            st_path.@st_ino@ != st_fd.@st_ino@)
			goto restart; /* File changed in the mean-time. */
@@pp_ifdef __O_TRUNC@@
		if (should_trunc && st_fd.@st_size@ != 0) {
			if unlikely(ftruncate(result, 0))
				goto err_r; /* Shouldn't happen */
		}
@@pp_endif@@
	}
	return result;
err_r:
@@pp_if $has_function(close)@@
	(void)close(result);
@@pp_endif@@
	return -1;
restart:
@@pp_if $has_function(close)@@
	(void)close(result);
@@pp_endif@@
	goto again;
@@pp_endif@@
}


[[cp, vartypes($mode_t)]]
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/oflags.h>")]]
[[requires(defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) &&
           $has_function(openat, flock, fstat, fstatat) &&
           ($has_function(ftruncate) || !defined(__O_TRUNC)))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>", "<bits/types.h>", "<bits/os/stat.h>")]]
$fd_t flopenat([[dirfd]] $fd_t dirfd, const char *path, $oflag_t flags, ...) {
@@pp_ifdef __O_TRUNC@@
	int should_trunc;
@@pp_endif@@
	int flock_op;
	fd_t result;
	mode_t mode;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);
	flock_op = __LOCK_EX;
@@pp_ifdef __O_EXLOCK@@
	flags &= ~__O_EXLOCK;
@@pp_endif@@
@@pp_if defined(__O_NONBLOCK) && defined(__LOCK_NB)@@
	if (flags & __O_NONBLOCK)
		flock_op |= __LOCK_NB;
@@pp_endif@@
@@pp_ifdef __O_TRUNC@@
	should_trunc = flags & __O_TRUNC;
	flags &= ~__O_TRUNC;
@@pp_endif@@

again:
	result = openat(dirfd, path, flags, mode);
	if likely(result != -1) {
		@struct stat@ st_path, st_fd;
		if unlikely(flock(result, flock_op))
			goto err_r;
		if unlikely(fstatat(dirfd, path, &st_path, 0))
			goto restart; /* Race condition: file was deleted */
		if unlikely(fstat(result, &st_fd))
			goto restart; /* Shouldn't happen */
		if unlikely(st_path.@st_dev@ != st_fd.@st_dev@ ||
		            st_path.@st_ino@ != st_fd.@st_ino@)
			goto restart; /* File changed in the mean-time. */
@@pp_ifdef __O_TRUNC@@
		if (should_trunc && st_fd.@st_size@ != 0) {
			if unlikely(ftruncate(result, 0))
				goto err_r; /* Shouldn't happen */
		}
@@pp_endif@@
	}
	return result;
err_r:
@@pp_if $has_function(close)@@
	(void)close(result);
@@pp_endif@@
	return -1;
restart:
@@pp_if $has_function(close)@@
	(void)close(result);
@@pp_endif@@
	goto again;
}

//TODO:struct pidfh *pidfile_open(const char *path, mode_t mode, pid_t *pidptr);
//TODO:$fd_t pidfile_fileno(const struct pidfh *pfh);
//TODO:int pidfile_write(struct pidfh *pfh);
//TODO:int pidfile_close(struct pidfh *pfh);
//TODO:int pidfile_remove(struct pidfh *pfh);

%{

__SYSDECL_END
#endif /* __CC__ */

}
