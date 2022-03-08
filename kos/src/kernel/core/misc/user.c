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
#ifndef GUARD_KERNEL_SRC_MISC_USER_C
#define GUARD_KERNEL_SRC_MISC_USER_C 1

#include <kernel/compiler.h>

#include <kernel/compat.h>
#include <kernel/user.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <asm/ioctl.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <stdbool.h>

DECL_BEGIN

/* Read a boolean value from a a variable-sized (but defaulting to sizeof(int)) buffer `arg' */
PUBLIC WUNUSED bool FCALL
ioctl_intarg_getbool(ioctl_t cmd,
                     USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT) {
	size_t i, argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = sizeof(int);
	validate_readable(arg, argsz);
	if likely(argsz == sizeof(int))
		return UNALIGNED_GET((USER CHECKED unsigned int const *)arg) != 0;
	for (i = 0; i < argsz; ++i) {
		if (((USER CHECKED byte_t const *)arg)[i] != 0)
			return true;
	}
	return false;
}

/* Write a boolean 0/1 value into a variable-sized (but defaulting to sizeof(int)) buffer `arg'
 * @return: 0 : Always returns `0' */
PUBLIC syscall_slong_t FCALL
ioctl_intarg_setbool(ioctl_t cmd,
                     USER UNCHECKED void *arg,
                     bool value)
		THROWS(E_SEGFAULT) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = sizeof(int);
	validate_writable(arg, argsz);
	if likely(argsz == sizeof(int))
		UNALIGNED_SET((USER CHECKED unsigned int *)arg, value ? 1 : 0);
	else {
		size_t i;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		((USER CHECKED byte_t *)arg)[0] = value ? 1 : 0;
		for (i = 1; i < argsz; ++i)
			((USER CHECKED byte_t *)arg)[i] = 0;
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		for (i = 0; i < argsz - 1; ++i)
			((USER CHECKED byte_t *)arg)[i] = 0;
		((USER CHECKED byte_t *)arg)[i] = value ? 1 : 0;
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	}
	return 0;
}


/* Read a 32-bit-value from a a variable-sized (but defaulting to 4) buffer `arg'
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
PUBLIC WUNUSED u32 FCALL
ioctl_intarg_getu32(ioctl_t cmd,
                    USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	u32 result;
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 4;
	validate_readable(arg, argsz);
	switch (__builtin_expect(argsz, 4)) {
	case sizeof(u8):  result = (u32)*(USER CHECKED u8 const *)arg; break;
	case sizeof(u16): result = (u32)UNALIGNED_GET16((USER CHECKED u16 const *)arg); break;
	case sizeof(u32): result = (u32)UNALIGNED_GET32((USER CHECKED u32 const *)arg); break;
	case sizeof(u64): result = (u32)UNALIGNED_GET64((USER CHECKED u64 const *)arg); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}

PUBLIC WUNUSED u16 FCALL
ioctl_intarg_getu16(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	u16 result;
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 2;
	validate_readable(arg, argsz);
	switch (__builtin_expect(argsz, 2)) {
	case sizeof(u8):  result = (u16)*(USER CHECKED u8 const *)arg; break;
	case sizeof(u16): result = (u16)UNALIGNED_GET16((USER CHECKED u16 const *)arg); break;
	case sizeof(u32): result = (u16)UNALIGNED_GET32((USER CHECKED u32 const *)arg); break;
	case sizeof(u64): result = (u16)UNALIGNED_GET64((USER CHECKED u64 const *)arg); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}

PUBLIC WUNUSED u8 FCALL
ioctl_intarg_getu8(ioctl_t cmd, USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	u8 result;
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 1;
	validate_readable(arg, argsz);
	switch (__builtin_expect(argsz, 1)) {
	case sizeof(u8):  result = *(USER CHECKED u8 const *)arg; break;
	case sizeof(u16): result = (u8)UNALIGNED_GET16((USER CHECKED u16 const *)arg); break;
	case sizeof(u32): result = (u8)UNALIGNED_GET32((USER CHECKED u32 const *)arg); break;
	case sizeof(u64): result = (u8)UNALIGNED_GET64((USER CHECKED u64 const *)arg); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}




/* Read a 64-bit-value from a a variable-sized (but defaulting to 8) buffer `arg'
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
PUBLIC WUNUSED u64 FCALL
ioctl_intarg_getu64(ioctl_t cmd,
                    USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	u64 result;
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 4;
	validate_readable(arg, argsz);
	switch (__builtin_expect(argsz, 4)) {
	case sizeof(u8):  result = (u64)*(USER CHECKED u8 const *)arg; break;
	case sizeof(u16): result = (u64)UNALIGNED_GET16((USER CHECKED u16 const *)arg); break;
	case sizeof(u32): result = (u64)UNALIGNED_GET32((USER CHECKED u32 const *)arg); break;
	case sizeof(u64): result = (u64)UNALIGNED_GET64((USER CHECKED u64 const *)arg); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}


/* Write a 32-bit-value into a variable-sized (but defaulting to 4) buffer `arg'
 * @return: 0 : Always returns `0' */
PUBLIC syscall_slong_t FCALL
ioctl_intarg_setu32(ioctl_t cmd, USER UNCHECKED void *arg, u32 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 4;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 4)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

/* Write a 64-bit-value into a variable-sized (but defaulting to 8) buffer `arg'
 * @return: 0 : Always returns `0' */
PUBLIC syscall_slong_t FCALL
ioctl_intarg_setu64(ioctl_t cmd, USER UNCHECKED void *arg, u64 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 8;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 8)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

/* For now, this is an alias. If we ever support integers > 64-bit, this
 * would  become its own function which then does sign-extension in case
 * we're to write to one such super-large integer. */
DEFINE_PUBLIC_ALIAS(ioctl_intarg_sets64, ioctl_intarg_setu64);

PUBLIC syscall_slong_t FCALL
ioctl_intarg_sets32(ioctl_t cmd, USER UNCHECKED void *arg, s32 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 4;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 4)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)(u32)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)(u32)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)(s64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

PUBLIC syscall_slong_t FCALL
ioctl_intarg_setu16(ioctl_t cmd, USER UNCHECKED void *arg, u16 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 2;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 2)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

PUBLIC syscall_slong_t FCALL
ioctl_intarg_sets16(ioctl_t cmd, USER UNCHECKED void *arg, s16 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 2;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 2)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)(u16)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)(s32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)(s64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

PUBLIC syscall_slong_t FCALL
ioctl_intarg_setu8(ioctl_t cmd, USER UNCHECKED void *arg, u8 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 1;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 1)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}

PUBLIC syscall_slong_t FCALL
ioctl_intarg_sets8(ioctl_t cmd, USER UNCHECKED void *arg, s8 value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0)
		argsz = 1;
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, 1)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)(s16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)(s32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)(s64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}


#if !defined(__ARCH_HAVE_COMPAT) || (__ARCH_COMPAT_SIZEOF_SIZE_T == __SIZEOF_SIZE_T__)
#if __SIZEOF_SIZE_T__ == 4
#define HAVE_IOCTL_INTARG_GETSETSIZE
DEFINE_PUBLIC_ALIAS(ioctl_intarg_getsize, ioctl_intarg_getu32);
DEFINE_PUBLIC_ALIAS(ioctl_intarg_setsize, ioctl_intarg_setu32);
#elif __SIZEOF_SIZE_T__ == 8
#define HAVE_IOCTL_INTARG_GETSETSIZE
DEFINE_PUBLIC_ALIAS(ioctl_intarg_getsize, ioctl_intarg_getu64);
DEFINE_PUBLIC_ALIAS(ioctl_intarg_setsize, ioctl_intarg_setu64);
#endif /* __SIZEOF_SIZE_T__ == ... */
#endif /* !__ARCH_HAVE_COMPAT || (__ARCH_COMPAT_SIZEOF_SIZE_T == __SIZEOF_SIZE_T__) */

#ifndef HAVE_IOCTL_INTARG_GETSETSIZE
/* Read a size_t-value from a a variable-sized (but defaulting to sizeof(size_t)) buffer `arg'
 * - This function includes special handling for compatibility (if present and necessary)
 * - When an invalid size is encoded in `cmd', throw `E_INVALID_ARGUMENT_UNKNOWN_COMMAND' */
PUBLIC WUNUSED size_t FCALL
ioctl_intarg_getsize(ioctl_t cmd,
                     USER UNCHECKED void *arg)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t result;
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0) {
#if defined(__ARCH_HAVE_COMPAT) && (__ARCH_COMPAT_SIZEOF_SIZE_T != __SIZEOF_SIZE_T__)
		if (syscall_iscompat()) {
			argsz = __ARCH_COMPAT_SIZEOF_SIZE_T;
		} else
#endif /* __ARCH_HAVE_COMPAT && (__ARCH_COMPAT_SIZEOF_SIZE_T != __SIZEOF_SIZE_T__) */
		{
			argsz = __SIZEOF_SIZE_T__;
		}
	}
	validate_readable(arg, argsz);
	switch (__builtin_expect(argsz, __SIZEOF_SIZE_T__)) {
	case sizeof(u8):  result = (size_t)*(USER CHECKED u8 const *)arg; break;
	case sizeof(u16): result = (size_t)UNALIGNED_GET16((USER CHECKED u16 const *)arg); break;
	case sizeof(u32): result = (size_t)UNALIGNED_GET32((USER CHECKED u32 const *)arg); break;
	case sizeof(u64): result = (size_t)UNALIGNED_GET64((USER CHECKED u64 const *)arg); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}


/* Write a size_t-value into a variable-sized (but defaulting to sizeof(size_t)) buffer `arg'
 * @return: 0 : Always returns `0' */
PUBLIC syscall_slong_t FCALL
ioctl_intarg_setsize(ioctl_t cmd, USER UNCHECKED void *arg, size_t value)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t argsz = _IOC_SIZE(cmd);
	if (argsz == 0) {
#if defined(__ARCH_HAVE_COMPAT) && (__ARCH_COMPAT_SIZEOF_SIZE_T != __SIZEOF_SIZE_T__)
		if (syscall_iscompat()) {
			argsz = __ARCH_COMPAT_SIZEOF_SIZE_T;
		} else
#endif /* __ARCH_HAVE_COMPAT && (__ARCH_COMPAT_SIZEOF_SIZE_T != __SIZEOF_SIZE_T__) */
		{
			argsz = __SIZEOF_SIZE_T__;
		}
	}
	validate_writable(arg, argsz);
	switch (__builtin_expect(argsz, __SIZEOF_SIZE_T__)) {
	case sizeof(u8):  *(USER CHECKED u8 *)arg = (u8)value; break;
	case sizeof(u16): UNALIGNED_SET16((USER CHECKED u16 *)arg, (u16)value); break;
	case sizeof(u32): UNALIGNED_SET32((USER CHECKED u32 *)arg, (u32)value); break;
	case sizeof(u64): UNALIGNED_SET64((USER CHECKED u64 *)arg, (u64)value); break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}
#endif /* !HAVE_IOCTL_INTARG_GETSETSIZE */



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_USER_C */
