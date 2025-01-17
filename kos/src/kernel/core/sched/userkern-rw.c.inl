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
#ifdef __INTELLISENSE__
#include "userkern.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
#endif /* __INTELLISENSE__ */

#include <sched/group.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <kos/except/reason/illop.h>

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define exactly one of `DEFINE_IO_READ' or `DEFINE_IO_WRITE' before #including this file"
#endif

#ifndef USERKERN_STRUCT
#define USERKERN_STRUCT struct userkern
#endif /* !USERKERN_STRUCT */

#ifndef USERKERN_WIDTH
#define USERKERN_WIDTH __SIZEOF_POINTER__
#endif /* !USERKERN_WIDTH */

DECL_BEGIN

#ifdef DEFINE_IO_READ
#define IFELSE_RW(r, w) r
#else /* DEFINE_IO_READ */
#define IFELSE_RW(r, w) w
#endif /* !DEFINE_IO_READ */


#ifdef DEFINE_IO_READ
#if USERKERN_WIDTH == 4
#define VALUE_TYPE   u32
PRIVATE NONNULL((1)) u32 LIBVIO_CC
userkern_segment_readl(struct vioargs *__restrict args,
                       pos_t addr)
#elif USERKERN_WIDTH == 8
#define VALUE_TYPE   u64
PRIVATE NONNULL((1)) u64 LIBVIO_CC
userkern_segment_readq(struct vioargs *__restrict args,
                       pos_t addr)
#endif /* USERKERN_WIDTH == ... */
#elif defined(DEFINE_IO_WRITE)
#if USERKERN_WIDTH == 4
#define VALUE_TYPE   u32
PRIVATE NONNULL((1)) void LIBVIO_CC
userkern_segment_writel(struct vioargs *__restrict args,
                        pos_t addr, u32 value)
#elif USERKERN_WIDTH == 8
#define VALUE_TYPE   u64
PRIVATE NONNULL((1)) void LIBVIO_CC
userkern_segment_writeq(struct vioargs *__restrict args,
                        pos_t addr, u64 value)
#endif /* USERKERN_WIDTH == ... */
#endif /* DEFINE_IO_WRITE */
{
#ifdef DEFINE_IO_READ
	VALUE_TYPE result;
#endif /* DEFINE_IO_READ */
	uintptr_t reladdr;
	uintptr_t base;
#if USERKERN_WIDTH == __SIZEOF_POINTER__
	base = get_userkern_base();
#else /* USERKERN_WIDTH == __SIZEOF_POINTER__ */
	base = get_compat_userkern_base();
#endif /* USERKERN_WIDTH != __SIZEOF_POINTER__ */
	if (!ADDR_ISKERN(base))
		goto err_invalid_addr;
#ifdef KERNELSPACE_HIGHMEM
	base -= KERNELSPACE_BASE;
#endif /* KERNELSPACE_HIGHMEM */
	if ((uintptr_t)addr < base)
		goto err_invalid_addr;
	reladdr = (uintptr_t)addr - base;
	switch (reladdr) {

	case offsetof(USERKERN_STRUCT, uk_base):
		/* Re-assign the base address of the user-thread segment. */
#ifdef DEFINE_IO_READ
		result = base;
#else /* DEFINE_IO_READ */
		if (!ADDR_ISKERN(value))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE,
			      value);
#if USERKERN_WIDTH == __SIZEOF_POINTER__
		set_userkern_base(value);
#else /* USERKERN_WIDTH == __SIZEOF_POINTER__ */
		set_compat_userkern_base(value);
#endif /* USERKERN_WIDTH != __SIZEOF_POINTER__ */
#endif /* !DEFINE_IO_READ */
		break;

#ifdef DEFINE_IO_READ
	case offsetof(USERKERN_STRUCT, uk_tid):
		result = task_gettid();
		break;
#endif /* DEFINE_IO_READ */

#ifdef DEFINE_IO_READ
	case offsetof(USERKERN_STRUCT, uk_pid):
		result = task_getpid();
		break;
#endif /* DEFINE_IO_READ */

	case offsetof(USERKERN_STRUCT, uk_ppid): {
#ifdef DEFINE_IO_READ
		result = task_getppid_s();
#else /* DEFINE_IO_READ */
		THROW(E_NOT_IMPLEMENTED_TODO);
#endif /* !DEFINE_IO_READ */
	}	break;

	case offsetof(USERKERN_STRUCT, uk_pgid): {
#ifdef DEFINE_IO_READ
		result = task_getpgid_s();
#else /* DEFINE_IO_READ */
		THROW(E_NOT_IMPLEMENTED_TODO);
#endif /* !DEFINE_IO_READ */
	}	break;

	case offsetof(USERKERN_STRUCT, uk_sid): {
#ifdef DEFINE_IO_READ
		result = task_getsid_s();
#else /* DEFINE_IO_READ */
		THROW(E_NOT_IMPLEMENTED_TODO);
#endif /* !DEFINE_IO_READ */
	}	break;

	case offsetof(USERKERN_STRUCT, uk_uid):
		IFELSE_RW(result = (VALUE_TYPE)cred_getruid(),
		          cred_setruid((uid_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_gid):
		IFELSE_RW(result = (VALUE_TYPE)cred_getrgid(),
		          cred_setrgid((gid_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_euid):
		IFELSE_RW(result = (VALUE_TYPE)cred_geteuid(),
		          cred_seteuid((uid_t)value));
		break;


	case offsetof(USERKERN_STRUCT, uk_egid):
		IFELSE_RW(result = (VALUE_TYPE)cred_getegid(),
		          cred_setegid((gid_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_suid):
		IFELSE_RW(result = (VALUE_TYPE)cred_getsuid(),
		          cred_setsuid((uid_t)value));
		break;

	case offsetof(USERKERN_STRUCT, uk_sgid):
		IFELSE_RW(result = (VALUE_TYPE)cred_getsgid(),
		          cred_setsgid((gid_t)value));
		break;

	default:
		/* Allow access to arch-specific fields. */
#ifdef DEFINE_IO_READ
#if defined(__ARCH_HAVE_COMPAT) && USERKERN_WIDTH == __ARCH_COMPAT_SIZEOF_POINTER
		if unlikely(!userkern_get_arch_specific_field_compat(args, reladdr, &result))
#else /* __ARCH_HAVE_COMPAT && USERKERN_WIDTH == __ARCH_COMPAT_SIZEOF_POINTER */
		if unlikely(!userkern_get_arch_specific_field(args, reladdr, &result))
#endif /* !__ARCH_HAVE_COMPAT || USERKERN_WIDTH != __ARCH_COMPAT_SIZEOF_POINTER */
#else /* DEFINE_IO_READ */
#if defined(__ARCH_HAVE_COMPAT) && USERKERN_WIDTH == __ARCH_COMPAT_SIZEOF_POINTER
		if unlikely(!userkern_set_arch_specific_field_compat(args, reladdr, value))
#else /* __ARCH_HAVE_COMPAT && USERKERN_WIDTH == __ARCH_COMPAT_SIZEOF_POINTER */
		if unlikely(!userkern_set_arch_specific_field(args, reladdr, value))
#endif /* !__ARCH_HAVE_COMPAT || USERKERN_WIDTH != __ARCH_COMPAT_SIZEOF_POINTER */
#endif /* !DEFINE_IO_READ */
		{
			if (reladdr < sizeof(USERKERN_STRUCT)) {
				void *ptr = vioargs_faultaddr(args, addr);
#ifdef DEFINE_IO_READ
				THROW(E_SEGFAULT_NOTREADABLE, ptr,
				      E_SEGFAULT_CONTEXT_USERCODE);
#else /* DEFINE_IO_READ */
				THROW(E_SEGFAULT_READONLY, ptr,
				      E_SEGFAULT_CONTEXT_USERCODE);
#endif /* !DEFINE_IO_READ */
			}
		}
		break;
	}
#ifdef DEFINE_IO_READ
	return result;
#else /* DEFINE_IO_READ */
	return;
#endif /* !DEFINE_IO_READ */
err_invalid_addr:
#ifdef DEFINE_IO_READ
	THROW(E_SEGFAULT_UNMAPPED,
	      vioargs_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
#else /* DEFINE_IO_READ */
	THROW(E_SEGFAULT_UNMAPPED,
	      vioargs_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_WRITING |
	      E_SEGFAULT_CONTEXT_USERCODE);
#endif /* !DEFINE_IO_READ */
}


DECL_END


#undef IFELSE_RW
#undef USERKERN_WIDTH
#undef USERKERN_STRUCT
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ
#undef VALUE_TYPE
