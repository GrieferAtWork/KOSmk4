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
#ifndef GUARD_KERNEL_SRC_MISC_UNAME_C
#define GUARD_KERNEL_SRC_MISC_UNAME_C 1
#define _GNU_SOURCE 1 /* domainname */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/uname.h>
#include <kernel/user.h>
#include <kernel/version.h>
#include <sched/cred.h>

#include <hybrid/host.h>

#include <kos/build-config.h>
#include <sys/utsname.h>

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <syscall.h>

#if (defined(__ARCH_WANT_SYSCALL_OLDOLDUNAME) ||        \
     defined(__ARCH_WANT_SYSCALL_OLDUNAME) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDOLDUNAME) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDUNAME))
#include <kos/compat/linux-uname.h>
#endif /* __ARCH_WANT_[COMPAT_]SYSCALL_OLD[OLD]UNAME */


DECL_BEGIN

/* Effective kernel version.
 * Usually the same as `KOS_VERSION_CODE', but can be used  by
 * modules  to  detect version  differences between  what they
 * were compiled for and what they are actually running under. */
PUBLIC_CONST u32 const kernel_version = KOS_VERSION_CODE;


#ifdef __x86_64__
#define MACHINE_NAME "x86_64"
#elif defined(__i386__)
#define MACHINE_NAME "i386"
#elif defined(KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH)
#define MACHINE_NAME KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH
#else /* ... */
#warning "Unknown host architecture"
#define MACHINE_NAME "UNKNOWN"
#endif /* !... */



/* UNAME information about the KOS kernel. */
PUBLIC struct utsname kernel_uname = {
	/* .sysname    = */ "KOS",
	/* .nodename   = */ "(none)",
	/* .release    = */ "KOS Mk" PP_STR(KOS_VERSION_MAJOR) " - " KOS_VERSION_NAME,
	/* .version    = */ PP_STR(KOS_VERSION_MAJOR) "."
	                    PP_STR(KOS_VERSION_MINOR) "."
	                    PP_STR(KOS_VERSION_PATCH),
	/* .machine    = */ MACHINE_NAME,
	/* .domainname = */ "(none)"
};





/************************************************************************/
/* oldolduname(), olduname(), uname()                                   */
/************************************************************************/
#define COPY_UNAME_FIELD(dst, src)                 \
	do {                                           \
		static_assert(sizeof(dst) <= sizeof(src)); \
		memcpy(dst, src, sizeof(dst));             \
	}	__WHILE0

#ifdef __ARCH_WANT_SYSCALL_OLDOLDUNAME
DEFINE_SYSCALL1(errno_t, oldolduname,
                USER UNCHECKED struct linux_oldolduname *, name) {
	validate_writable(name, sizeof(*name));
	COPY_UNAME_FIELD(name->sysname, kernel_uname.sysname);
	COPY_UNAME_FIELD(name->nodename, kernel_uname.nodename);
	COPY_UNAME_FIELD(name->release, kernel_uname.release);
	COPY_UNAME_FIELD(name->version, kernel_uname.version);
	COPY_UNAME_FIELD(name->machine, kernel_uname.machine);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDOLDUNAME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDOLDUNAME
DEFINE_COMPAT_SYSCALL1(errno_t, oldolduname,
                       USER UNCHECKED struct linux_oldolduname *, name) {
	compat_validate_writable(name, sizeof(*name));
	COPY_UNAME_FIELD(name->sysname, kernel_uname.sysname);
	COPY_UNAME_FIELD(name->nodename, kernel_uname.nodename);
	COPY_UNAME_FIELD(name->release, kernel_uname.release);
	COPY_UNAME_FIELD(name->version, kernel_uname.version);
	COPY_UNAME_FIELD(name->machine, kernel_uname.machine);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDOLDUNAME */

#ifdef __ARCH_WANT_SYSCALL_OLDUNAME
DEFINE_SYSCALL1(errno_t, olduname,
                USER UNCHECKED struct linux_olduname *, name) {
	validate_writable(name, sizeof(*name));
	COPY_UNAME_FIELD(name->sysname, kernel_uname.sysname);
	COPY_UNAME_FIELD(name->nodename, kernel_uname.nodename);
	COPY_UNAME_FIELD(name->release, kernel_uname.release);
	COPY_UNAME_FIELD(name->version, kernel_uname.version);
	COPY_UNAME_FIELD(name->machine, kernel_uname.machine);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDUNAME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDUNAME
DEFINE_COMPAT_SYSCALL1(errno_t, olduname,
                       USER UNCHECKED struct linux_olduname *, name) {
	compat_validate_writable(name, sizeof(*name));
	COPY_UNAME_FIELD(name->sysname, kernel_uname.sysname);
	COPY_UNAME_FIELD(name->nodename, kernel_uname.nodename);
	COPY_UNAME_FIELD(name->release, kernel_uname.release);
	COPY_UNAME_FIELD(name->version, kernel_uname.version);
	COPY_UNAME_FIELD(name->machine, kernel_uname.machine);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDUNAME */
#undef COPY_UNAME_FIELD

#ifdef __ARCH_WANT_SYSCALL_UNAME
DEFINE_SYSCALL1(errno_t, uname,
                USER UNCHECKED struct utsname *, name) {
	validate_writable(name, sizeof(*name));
	memcpy(name, &kernel_uname, sizeof(*name));
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UNAME */





/************************************************************************/
/* sethostname(), setdomainname()                                       */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETHOSTNAME
DEFINE_SYSCALL2(errno_t, sethostname,
                USER UNCHECKED char const *, name,
                size_t, namelen) {
	char temp[_UTSNAME_NODENAME_LENGTH];
	validate_readable(name, namelen);
	if (namelen > _UTSNAME_NODENAME_LENGTH)
		THROW(E_BUFFER_TOO_SMALL, namelen, _UTSNAME_NODENAME_LENGTH);
	cred_require_sysadmin();
	memcpy(temp, name, namelen, sizeof(char));
	bzero(temp + namelen, _UTSNAME_NODENAME_LENGTH - namelen, sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(kernel_uname.nodename, temp, sizeof(temp));
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETHOSTNAME */

#ifdef __ARCH_WANT_SYSCALL_SETDOMAINNAME
DEFINE_SYSCALL2(errno_t, setdomainname,
                USER UNCHECKED char const *, name,
                size_t, namelen) {
	char temp[_UTSNAME_DOMAIN_LENGTH];
	validate_readable(name, namelen);
	if (namelen > _UTSNAME_DOMAIN_LENGTH)
		THROW(E_BUFFER_TOO_SMALL, namelen, _UTSNAME_DOMAIN_LENGTH);
	cred_require_sysadmin();
	memcpy(temp, name, namelen, sizeof(char));
	bzero(temp + namelen, _UTSNAME_DOMAIN_LENGTH - namelen, sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(kernel_uname.domainname, temp, sizeof(temp));
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETDOMAINNAME */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_UNAME_C */
