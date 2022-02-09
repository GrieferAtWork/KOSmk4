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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_USER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_USER_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <compat/config.h>
#include <kos/kernel/paging.h>

DECL_BEGIN

/* Skew a  kernel pointer  such that  it remains  unique, continues  to
 * point into kernel-space, but doesn't necessarily indicate the proper
 * address of the pointed-to kernel object.
 * For this purpose, these functions usually just:
 *   - xor the pointer with some key-mask.
 *   - switch bits at random positions within the pointer with each other.
 * Note that what exactly is done depends on how the kernel was configured,
 * and a one-time-initialized blob of random data that will not change ever
 * until the next reboot.
 * Also note that these functions may simply  not do anything at all, or  do
 * something 100% predictable, especially in situations where the kernel was
 * configured for debugging, rather than security.
 *
 * NOTE: These functions guaranty not to modify the least significant 3
 *       bits of the input pointer, such that `(return & 7) == (p & 7)' */
#define skew_kernel_pointer(p)   (void *)(p) /* TODO */
#define unskew_kernel_pointer(p) (void *)(p) /* TODO */


#ifdef __CC__
FUNDEF ATTR_COLD ATTR_NORETURN void FCALL
__except_throw_unmapped_user_rd(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_UNMAPPED)
		ASMNAME("except_throw_unmapped_user_rd");
FUNDEF ATTR_COLD ATTR_NORETURN void FCALL
__except_throw_unmapped_user_wr(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_UNMAPPED)
		ASMNAME("except_throw_unmapped_user_wr");
FUNDEF ATTR_COLD ATTR_NORETURN void FCALL
__except_throw_noexec_user(UNCHECKED USER void const *addr)
		THROWS(E_SEGFAULT_NOTEXECUTABLE)
		ASMNAME("except_throw_noexec_user");

#ifdef KERNELSPACE_HIGHMEM
#define __ADDR_ISUSER(addr) (__CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_BASE)
#elif defined(KERNELSPACE_LOWMEM)
#define __ADDR_ISUSER(addr) (__CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_END)
#else /* KERNELSPACE_...MEM */
#define __ADDR_ISUSER(addr) (__CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_END)
#endif /* !KERNELSPACE_...MEM */



/* Validate user-pointers for being allowed to be used for the specified operations.
 * Since the kernel  is allowed to  access memory that  is marked as  `PROT_NOUSER',
 * user-pointers passed from user-space must  be checked for the same  restrictions.
 * In order words: If  the  user passes  a pointer  that  is part  of kernel-space,
 *                 these functions are used to deny the user access to such memory.
 * @throw E_SEGFAULT: User-space has not been granted access to the given address range. */
#ifdef __INTELLISENSE__
FUNDEF CHECKED USER void const *FCALL validate_user(UNCHECKED USER void const *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_user_opt(UNCHECKED USER void const *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_userm(UNCHECKED USER void const *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_userm_opt(UNCHECKED USER void const *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_useraddr(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_useraddr_opt(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readable(UNCHECKED USER void const *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readable_opt(UNCHECKED USER void const *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readablem(UNCHECKED USER void const *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readablem_opt(UNCHECKED USER void const *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readableaddr(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_readableaddr_opt(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writable(UNCHECKED USER void *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writable_opt(UNCHECKED USER void *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writablem(UNCHECKED USER void *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writablem_opt(UNCHECKED USER void *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writableaddr(UNCHECKED USER void *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_writableaddr_opt(UNCHECKED USER void *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwrite(UNCHECKED USER void *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwrite_opt(UNCHECKED USER void *base, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwritem(UNCHECKED USER void *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwritem_opt(UNCHECKED USER void *base, size_t num_items, size_t item_size_in_bytes) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwriteaddr(UNCHECKED USER void *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void *FCALL validate_readwriteaddr_opt(UNCHECKED USER void *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_executable(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
FUNDEF CHECKED USER void const *FCALL validate_executable_opt(UNCHECKED USER void const *addr) THROWS(E_SEGFAULT);
#else /* __INTELLISENSE__ */
EIDECLARE(, USER CHECKED void const *, , FCALL, validate_readableaddr, (UNCHECKED USER void const *addr), THROWS(E_SEGFAULT) { if unlikely(!__ADDR_ISUSER(addr)) __except_throw_unmapped_user_rd(addr); return addr; })
EIDECLARE(, USER CHECKED void *, , FCALL, validate_writableaddr, (UNCHECKED USER void *addr), THROWS(E_SEGFAULT) { if unlikely(!__ADDR_ISUSER(addr)) __except_throw_unmapped_user_wr(addr); return addr; })
EIDECLARE(, USER CHECKED void const *, , FCALL, validate_executable, (UNCHECKED USER void const *addr), THROWS(E_SEGFAULT) { if unlikely(!__ADDR_ISUSER(addr)) __except_throw_noexec_user(addr); return addr; })
#define validate_user(base, num_bytes)                           validate_readableaddr(base)
#define validate_userm(base, num_items, item_size_in_bytes)      validate_readableaddr(base)
#define validate_useraddr(addr)                                  validate_readableaddr(addr)
#define validate_readable(base, num_bytes)                       validate_readableaddr(base)
#define validate_readablem(base, num_items, item_size_in_bytes)  validate_readableaddr(base)
#define validate_writable(base, num_bytes)                       validate_writableaddr(base)
#define validate_writablem(base, num_items, item_size_in_bytes)  validate_writableaddr(base)
#define validate_readwrite(base, num_bytes)                      validate_readableaddr(base) /* Read is assumed to come first */
#define validate_readwritem(base, num_items, item_size_in_bytes) validate_readableaddr(base) /* Read is assumed to come first */
#define validate_readwriteaddr(addr)                             validate_readableaddr(addr) /* Read is assumed to come first */


/* Same as the function above, but explicitly accept `NULL' as a user-space address */
#ifdef KERNELSPACE_HIGHMEM
#define validate_user_opt(base, num_bytes)                           validate_user(base, num_bytes)
#define validate_userm_opt(base, num_items, item_size_in_bytes)      validate_userm(base, num_items, item_size_in_bytes)
#define validate_useraddr_opt(base, num_bytes)                       validate_useraddr(base, num_bytes)
#define validate_readable_opt(base, num_bytes)                       validate_readable(base, num_bytes)
#define validate_readablem_opt(base, num_items, item_size_in_bytes)  validate_readablem(base, num_items, item_size_in_bytes)
#define validate_readableaddr_opt(addr)                              validate_readableaddr(addr)
#define validate_writable_opt(base, num_bytes)                       validate_writable(base, num_bytes)
#define validate_writablem_opt(base, num_items, item_size_in_bytes)  validate_writablem(base, num_items, item_size_in_bytes)
#define validate_writableaddr_opt(addr)                              validate_writableaddr(addr)
#define validate_readwrite_opt(base, num_bytes)                      validate_readwrite(base, num_bytes)
#define validate_readwritem_opt(base, num_items, item_size_in_bytes) validate_readwritem(base, num_items, item_size_in_bytes)
#define validate_readwriteaddr_opt(addr)                             validate_readwriteaddr(addr)
#define validate_executable_opt(addr)                                validate_executable(addr)
#else /* KERNELSPACE_HIGHMEM */
#define validate_user_opt(base, num_bytes)                           (void)(!(base) || (validate_user(base, num_bytes), 0))
#define validate_userm_opt(base, num_items, item_size_in_bytes)      (void)(!(base) || (validate_userm(base, num_items, item_size_in_bytes), 0))
#define validate_useraddr_opt(base, num_bytes)                       (void)(!(base) || (validate_useraddr(base, num_bytes), 0))
#define validate_readable_opt(base, num_bytes)                       (void)(!(base) || (validate_readable(base, num_bytes), 0))
#define validate_readablem_opt(base, num_items, item_size_in_bytes)  (void)(!(base) || (validate_readablem(base, num_items, item_size_in_bytes), 0))
#define validate_readableaddr_opt(addr)                              (void)(!(addr) || (validate_readableaddr(addr), 0))
#define validate_writable_opt(base, num_bytes)                       (void)(!(base) || (validate_writable(base, num_bytes), 0))
#define validate_writablem_opt(base, num_items, item_size_in_bytes)  (void)(!(base) || (validate_writablem(base, num_items, item_size_in_bytes), 0))
#define validate_writableaddr_opt(addr)                              (void)(!(addr) || (validate_writableaddr(addr), 0))
#define validate_readwrite_opt(base, num_bytes)                      (void)(!(base) || (validate_readwrite(base, num_bytes), 0))
#define validate_readwritem_opt(base, num_items, item_size_in_bytes) (void)(!(base) || (validate_readwritem(base, num_items, item_size_in_bytes), 0))
#define validate_readwriteaddr_opt(addr)                             (void)(!(addr) || (validate_readwriteaddr(addr), 0))
#define validate_executable_opt(addr)                                (void)(!(addr) || (validate_executable(addr), 0))
#endif /* !KERNELSPACE_HIGHMEM */
#endif /* !__INTELLISENSE__ */

/* Same as the regular validate functions, but are allowed to be used for verification
 * of  pointers originating from  compatibility mode (this  allows for an optimization
 * on x86_64 where  a 32-bit pointer  originating from user-space  doesn't need to  be
 * checked for overlap with kernel-space, since the kernel-space lies outside of  said
 * 32-bit address space, meaning that the check could never succeed)
 * If you're unsure if some given pointer is allowed to be checked using these functions,
 * first check if the code you're working on only gets compiled with `__ARCH_HAVE_COMPAT'
 * is  defined. If it  doesn't and also gets  compiled at other  times, _dont_ use these.
 * If  the code only gets compiled when  `__ARCH_HAVE_COMPAT' is defined and you're still
 * not sure if these could be used, better  do the safe thing and don't use them  either. */
#ifdef __ARCH_HAVE_COMPAT
#if (defined(KERNELSPACE_HIGHMEM) && (__ARCH_COMPAT_SIZEOF_POINTER < __SIZEOF_POINTER__) && \
     ((1ull << (__ARCH_COMPAT_SIZEOF_POINTER * 8)) - 1) < KERNELSPACE_BASE)
/* The kernel resides in high memory, and the greatest possible compatibility-mode
 * address doesn't overlap with the native kernel address range. As such, there is
 * no need to verify if some given compatibility-mode pointer actually points into
 * kernel-space, since it's literally impossible to construct one that would.
 *
 * Note  that in case of large `num_bytes', we may assume that the kernel will access
 * user-space memory sequentially, such that at least 1 access happens for each  page
 * starting at `base'. This, combined with the fact that the first page of the kernel
 * is mapped as non-present, means  that should (supposed) user-memory overflow  into
 * the  kernel, we'll fault no later than when  we try to access the first (unmapped)
 * page of kernel-space, putting an end to  user-space trying to trick us into  using
 * our own memory!
 *
 * NOTE: If any of these assertions fail, you might be applying sign extension to a
 *       compatibility-mode pointer, or a given pointer isn't actually proper compat-
 *       mode.
 *       Also note that system interfaces that allow compatibility-mode to define
 *       native-sized pointers mustn't use these validation macros, since obviously
 *       those pointers can't be considered compatibility-mode.
 */
#define __compat_assert_user(base, num_bytes)                      __hybrid_assert(ADDR_ISUSER(base))
#define __compat_assert_user_opt                                   __compat_assert_user
#define __compat_assert_userm(base, num_items, item_size_in_bytes) __hybrid_assert(ADDR_ISUSER(base))
#define __compat_assert_userm_opt                                  __compat_assert_userm
#define __compat_assert_useraddr(addr)                             __hybrid_assert(ADDR_ISUSER(addr))
#define __compat_assert_useraddr_opt                               __compat_assert_useraddr

#define compat_validate_user(base, num_bytes)                               __compat_assert_user(base, num_bytes)
#define compat_validate_user_opt(base, num_bytes)                           __compat_assert_user_opt(base, num_bytes)
#define compat_validate_userm(base, num_items, item_size_in_bytes)          __compat_assert_userm(base, num_items, item_size_in_bytes)
#define compat_validate_userm_opt(base, num_items, item_size_in_bytes)      __compat_assert_userm_opt(base, num_items, item_size_in_bytes)
#define compat_validate_useraddr(addr)                                      __compat_assert_useraddr(addr)
#define compat_validate_useraddr_opt(base, num_bytes)                       __compat_assert_useraddr_opt(addr)
#define compat_validate_readable(base, num_bytes)                           __compat_assert_user(base, num_bytes)
#define compat_validate_readable_opt(base, num_bytes)                       __compat_assert_user_opt(base, num_bytes)
#define compat_validate_readablem(base, num_items, item_size_in_bytes)      __compat_assert_userm(base, num_items, item_size_in_bytes)
#define compat_validate_readablem_opt(base, num_items, item_size_in_bytes)  __compat_assert_userm_opt(base, num_items, item_size_in_bytes)
#define compat_validate_readableaddr(addr)                                  __compat_assert_useraddr(addr)
#define compat_validate_readableaddr_opt(addr)                              __compat_assert_useraddr_opt(addr)
#define compat_validate_writable(base, num_bytes)                           __compat_assert_user(base, num_bytes)
#define compat_validate_writable_opt(base, num_bytes)                       __compat_assert_user_opt(base, num_bytes)
#define compat_validate_writablem(base, num_items, item_size_in_bytes)      __compat_assert_userm(base, num_items, item_size_in_bytes)
#define compat_validate_writablem_opt(base, num_items, item_size_in_bytes)  __compat_assert_userm_opt(base, num_items, item_size_in_bytes)
#define compat_validate_writableaddr(addr)                                  __compat_assert_useraddr(addr)
#define compat_validate_writableaddr_opt(addr)                              __compat_assert_useraddr_opt(addr)
#define compat_validate_readwrite(base, num_bytes)                          __compat_assert_user(base, num_bytes)
#define compat_validate_readwrite_opt(base, num_bytes)                      __compat_assert_user_opt(base, num_bytes)
#define compat_validate_readwritem(base, num_items, item_size_in_bytes)     __compat_assert_userm(base, num_items, item_size_in_bytes)
#define compat_validate_readwritem_opt(base, num_items, item_size_in_bytes) __compat_assert_userm_opt(base, num_items, item_size_in_bytes)
#define compat_validate_readwriteaddr(addr)                                 __compat_assert_useraddr(addr)
#define compat_validate_readwriteaddr_opt(addr)                             __compat_assert_useraddr_opt(addr)
#define compat_validate_executable(addr)                                    __compat_assert_useraddr(addr)
#define compat_validate_executable_opt(addr)                                __compat_assert_useraddr_opt(addr)
#else /* ... */
#define compat_validate_user(base, num_bytes)                               validate_user(base, num_bytes)
#define compat_validate_user_opt(base, num_bytes)                           validate_user_opt(base, num_bytes)
#define compat_validate_userm(base, num_items, item_size_in_bytes)          validate_userm(base, num_items, item_size_in_bytes)
#define compat_validate_userm_opt(base, num_items, item_size_in_bytes)      validate_userm_opt(base, num_items, item_size_in_bytes)
#define compat_validate_useraddr(addr)                                      validate_useraddr(addr)
#define compat_validate_useraddr_opt(base, num_bytes)                       validate_useraddr_opt(base, num_bytes)
#define compat_validate_readable(base, num_bytes)                           validate_readable(base, num_bytes)
#define compat_validate_readable_opt(base, num_bytes)                       validate_readable_opt(base, num_bytes)
#define compat_validate_readablem(base, num_items, item_size_in_bytes)      validate_readablem(base, num_items, item_size_in_bytes)
#define compat_validate_readablem_opt(base, num_items, item_size_in_bytes)  validate_readablem_opt(base, num_items, item_size_in_bytes)
#define compat_validate_readableaddr(addr)                                  validate_readableaddr(addr)
#define compat_validate_readableaddr_opt(addr)                              validate_readableaddr_opt(addr)
#define compat_validate_writable(base, num_bytes)                           validate_writable(base, num_bytes)
#define compat_validate_writable_opt(base, num_bytes)                       validate_writable_opt(base, num_bytes)
#define compat_validate_writablem(base, num_items, item_size_in_bytes)      validate_writablem(base, num_items, item_size_in_bytes)
#define compat_validate_writablem_opt(base, num_items, item_size_in_bytes)  validate_writablem_opt(base, num_items, item_size_in_bytes)
#define compat_validate_writableaddr(addr)                                  validate_writableaddr(addr)
#define compat_validate_writableaddr_opt(addr)                              validate_writableaddr_opt(addr)
#define compat_validate_readwrite(base, num_bytes)                          validate_readwrite(base, num_bytes)
#define compat_validate_readwrite_opt(base, num_bytes)                      validate_readwrite_opt(base, num_bytes)
#define compat_validate_readwritem(base, num_items, item_size_in_bytes)     validate_readwritem(base, num_items, item_size_in_bytes)
#define compat_validate_readwritem_opt(base, num_items, item_size_in_bytes) validate_readwritem_opt(base, num_items, item_size_in_bytes)
#define compat_validate_readwriteaddr(addr)                                 validate_readwriteaddr(addr)
#define compat_validate_readwriteaddr_opt(addr)                             validate_readwrite_opt(addr)
#define compat_validate_executable(addr)                                    validate_executable(addr)
#define compat_validate_executable_opt(addr)                                validate_executable_opt(addr)
#endif /* !... */
#endif /* __ARCH_HAVE_COMPAT */


/************************************************************************/
/* Helper functions for interacting with ioctl() arguments.             */
/************************************************************************/

/* Read a boolean value from a a variable-sized (but defaulting to sizeof(int)) buffer `arg' */
FUNDEF WUNUSED __BOOL FCALL
ioctl_intarg_getbool(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT);

/* Write a boolean 0/1 value into a variable-sized (but defaulting to sizeof(int)) buffer `arg'
 * @return: 0 : Always returns `0' */
FUNDEF syscall_slong_t FCALL
ioctl_intarg_setbool(ioctl_t cmd, USER UNCHECKED void *arg, __BOOL value)
		THROWS(E_SEGFAULT);

/* Read a 32-bit-value from a a variable-sized (but defaulting to 4) buffer `arg'
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
FUNDEF WUNUSED u32 FCALL
ioctl_intarg_getu32(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

/* Read a 64-bit-value from a a variable-sized (but defaulting to 8) buffer `arg'
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
FUNDEF WUNUSED u64 FCALL
ioctl_intarg_getu64(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

/* Write a 32-bit-value into a variable-sized (but defaulting to 4) buffer `arg'
 * @return: 0 : Always returns `0' */
FUNDEF syscall_slong_t FCALL
ioctl_intarg_setu32(ioctl_t cmd, USER UNCHECKED void *arg, u32 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

/* Write a 75-bit-value into a variable-sized (but defaulting to 8) buffer `arg'
 * @return: 0 : Always returns `0' */
FUNDEF syscall_slong_t FCALL
ioctl_intarg_setu64(ioctl_t cmd, USER UNCHECKED void *arg, u64 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

#if __SIZEOF_INT__ >= 8
#define ioctl_intarg_getint                   (int)(unsigned int)ioctl_intarg_getu64
#define ioctl_intarg_getuint                  (unsigned int)ioctl_intarg_getu64
#define ioctl_intarg_setuint(cmd, arg, value) ioctl_intarg_setu64(cmd, arg, (u64)(value))
#else /* __SIZEOF_INT__ >= 8 */
#define ioctl_intarg_getint                   (int)(unsigned int)ioctl_intarg_getu32
#define ioctl_intarg_getuint                  (unsigned int)ioctl_intarg_getu32
#define ioctl_intarg_setuint(cmd, arg, value) ioctl_intarg_setu32(cmd, arg, (u32)(value))
#endif /* __SIZEOF_INT__ <= 8 */
#define ioctl_intarg_setint(cmd, arg, value) ioctl_intarg_setu64(cmd, arg, (u64)(s64)(int)(value))


/* Read a size_t-value from a a variable-sized (but defaulting to sizeof(size_t)) buffer `arg'
 * - This function includes special handling for compatibility (if present and necessary)
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
FUNDEF WUNUSED size_t FCALL
ioctl_intarg_getsize(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

/* Write a size_t-value into a variable-sized (but defaulting to sizeof(size_t)) buffer `arg'
 * @return: 0 : Always returns `0' */
FUNDEF syscall_slong_t FCALL
ioctl_intarg_setsize(ioctl_t cmd, USER UNCHECKED void *arg, size_t value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND);


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_USER_H */
