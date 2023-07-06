/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
gcc_opt.remove("-g"); // Disable debug informations for this file!
]]]*/
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
#ifndef GUARD_LIBSCTRACE_SC_GETDESC_C
#define GUARD_LIBSCTRACE_SC_GETDESC_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE 1
#define __WANT_SYSCALL_ARGUMENT_NAMES 1
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/unaligned.h>

#include <compat/config.h>
#include <kos/asm/rpc-method.h>
#include <sys/mman.h>

#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libsctrace/repr-types.h>

#include "sctrace.h"

/* Pull in required system call meta-data */
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#include <asm/syscalls-proto.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */

#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#undef __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE 1
#include <asm/syscalls-trace.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE */

#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#undef __WANT_SYSCALL_ARGUMENT_NAMES
#define __WANT_SYSCALL_ARGUMENT_NAMES 1
#include <asm/syscalls-trace.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */

#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#undef __WANT_SYSCALL_ARGUMENT_FORMAT
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#include <asm/syscalls-trace.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */


#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>

#if __ARCH_COMPAT_SIZEOF_POINTER == 4

#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#include <asm/syscalls-proto32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */

#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#undef __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE 1
#include <asm/syscalls-trace32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE */

#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#undef __WANT_SYSCALL_ARGUMENT_NAMES
#define __WANT_SYSCALL_ARGUMENT_NAMES 1
#include <asm/syscalls-trace32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */

#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#undef __WANT_SYSCALL_ARGUMENT_FORMAT
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#include <asm/syscalls-trace32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */

#elif __ARCH_COMPAT_SIZEOF_POINTER == 8

#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#include <asm/syscalls-proto64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */

#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#undef __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE 1
#include <asm/syscalls-trace64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE */

#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#undef __WANT_SYSCALL_ARGUMENT_NAMES
#define __WANT_SYSCALL_ARGUMENT_NAMES 1
#include <asm/syscalls-trace64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */

#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#undef __WANT_SYSCALL_ARGUMENT_FORMAT
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#include <asm/syscalls-trace64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */

#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */



/* Pull in system call table meta-data */
#ifndef __NRFEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls.h>
#endif /* !__NRFEAT_SYSCALL_TABLE_COUNT */
#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#ifndef __NR32FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_SYSCALL_TABLE_COUNT */
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#ifndef __NR64FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls64_d.h>
#endif /* !__NR64FEAT_SYSCALL_TABLE_COUNT */
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */



DECL_BEGIN

#define ARG_PLACEHOLDER_   ,
#define ARG_PLACEHOLDER_0  ,
#define ARG_PLACEHOLDER_1  ,
#define ARG_PLACEHOLDER_2  ,
#define ARG_PLACEHOLDER_3  ,
#define ARG_PLACEHOLDER_4  ,
#define ARG_PLACEHOLDER_5  ,
#define ARG_PLACEHOLDER_6  ,
#define ARG_PLACEHOLDER_7  ,
#define ARG_PLACEHOLDER_8  ,
#define ARG_PLACEHOLDER_9  ,
#define ARG_PLACEHOLDER_10 ,
#define ARG_PLACEHOLDER_11 ,
#define ARG_PLACEHOLDER_12 ,
#define ARG_PLACEHOLDER_13 ,
#define ARG_PLACEHOLDER_14 ,
#define ARG_PLACEHOLDER_15 ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(...) TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)



/* Database entry layout for system call descriptors:
 *    unsigned int sc_argc: 3;                   // Argument count (0-6) (7 is unused)
 *    unsigned int sc_regdw: 5;                  // Bitset  of doube-wide arguments (5 is enough,
 *                                               // because the worst case is 5-arg,6-reg,dw=[4])
 *    char         sc_name[*] = "...";           // Name of the system call
 *    char         sc_namenul = '\0';            // NUL-byte
 * The following part is repeated `sc_argc' times.
 *    unsigned int sc_argItype: 13;              // Argument type (one of `SC_REPR_*')
 *    unsigned int sc_argIlink: 3;               // Linked argument (or 7 if no argument is linked)
 *    char         sc_argIname[*] = "...";       // Argument name
 *    char         sc_argInul     = '\0';        // NUL-byte
 *
 * This database is initialized from system call meta-data:
 *    sc_argc     = __NRAC_<name>
 *    sc_regdw    = __NRDW<arg{0-5}>_<name>
 *    sc_name     = <name>
 *    sc_argItype = __NRATR<argI>_<name>
 *    sc_argIlink = __NRATL<argI>_<name>
 *    sc_argIname = __NRAN<argI>_<name>
 */

#define SYSCALL_DB_DECL_ARG(prefix, name, i)     \
	unsigned int sc_##name##_arg##i##_type : 13; \
	unsigned int sc_##name##_arg##i##_link : 3;  \
	char sc_##name##_arg##i##_name[sizeof(PP_STR(prefix##AN##i##_##name))];

#define _SYSCALL_DB_DECL_ARGC0(prefix, name)
#define _SYSCALL_DB_DECL_ARGC1(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 0)
#define _SYSCALL_DB_DECL_ARGC2(prefix, name) _SYSCALL_DB_DECL_ARGC1(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 1)
#define _SYSCALL_DB_DECL_ARGC3(prefix, name) _SYSCALL_DB_DECL_ARGC2(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 2)
#define _SYSCALL_DB_DECL_ARGC4(prefix, name) _SYSCALL_DB_DECL_ARGC3(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 3)
#define _SYSCALL_DB_DECL_ARGC5(prefix, name) _SYSCALL_DB_DECL_ARGC4(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 4)
#define _SYSCALL_DB_DECL_ARGC6(prefix, name) _SYSCALL_DB_DECL_ARGC5(prefix, name) SYSCALL_DB_DECL_ARG(prefix, name, 5)
#define _SYSCALL_DB_DECL_ARGS2(prefix, name, argc) _SYSCALL_DB_DECL_ARGC##argc(prefix, name)
#define _SYSCALL_DB_DECL_ARGS(prefix, name, argc) _SYSCALL_DB_DECL_ARGS2(prefix, name, argc)

#define _SYSCALL_DB_INIT_ARGLINK_0(symbol) 7
#define _SYSCALL_DB_INIT_ARGLINK_1(symbol) symbol
#define _SYSCALL_DB_INIT_ARGLINK3(symbol, defined) _SYSCALL_DB_INIT_ARGLINK_##defined(symbol)
#define _SYSCALL_DB_INIT_ARGLINK2(symbol, defined) _SYSCALL_DB_INIT_ARGLINK3(symbol, defined)
#define _SYSCALL_DB_INIT_ARGLINK(symbol) _SYSCALL_DB_INIT_ARGLINK2(symbol, IS_DEFINED2(symbol))

#define SYSCALL_DB_INIT_ARG(prefix, name, i)                                              \
	/* .sc_##name##_arg##i##_type = */ prefix##ATR##i##_##name,                           \
	/* .sc_##name##_arg##i##_link = */ _SYSCALL_DB_INIT_ARGLINK(prefix##ATL##i##_##name), \
	/* .sc_##name##_arg##i##_name = */ PP_STR(prefix##AN##i##_##name),

#define _SYSCALL_DB_INIT_ARGC0(prefix, name)
#define _SYSCALL_DB_INIT_ARGC1(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 0)
#define _SYSCALL_DB_INIT_ARGC2(prefix, name) _SYSCALL_DB_INIT_ARGC1(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 1)
#define _SYSCALL_DB_INIT_ARGC3(prefix, name) _SYSCALL_DB_INIT_ARGC2(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 2)
#define _SYSCALL_DB_INIT_ARGC4(prefix, name) _SYSCALL_DB_INIT_ARGC3(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 3)
#define _SYSCALL_DB_INIT_ARGC5(prefix, name) _SYSCALL_DB_INIT_ARGC4(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 4)
#define _SYSCALL_DB_INIT_ARGC6(prefix, name) _SYSCALL_DB_INIT_ARGC5(prefix, name) SYSCALL_DB_INIT_ARG(prefix, name, 5)
#define _SYSCALL_DB_INIT_ARGS2(prefix, name, argc) _SYSCALL_DB_INIT_ARGC##argc(prefix, name)
#define _SYSCALL_DB_INIT_ARGS(prefix, name, argc) _SYSCALL_DB_INIT_ARGS2(prefix, name, argc)

#define _SYSCALL_DB_INIT_ARGDW(prefix, name) \
	((IS_DEFINED(prefix##DW0_##name) << 3) | \
	 (IS_DEFINED(prefix##DW1_##name) << 4) | \
	 (IS_DEFINED(prefix##DW2_##name) << 5) | \
	 (IS_DEFINED(prefix##DW3_##name) << 6) | \
	 (IS_DEFINED(prefix##DW4_##name) << 7))


/* Declare a system call database entry. */
#define SYSCALL_DB_DECL(prefix, name)                  \
	uint8_t sc_##name##_head; /* sc_argc + sc_regdw */ \
	char    sc_##name##_name[sizeof(#name)];           \
	_SYSCALL_DB_DECL_ARGS(prefix, name, prefix##AC_##name)

/* Initialize a system call database entry. */
#define SYSCALL_DB_INIT(prefix, name)                                                   \
	/* .sc_##name##_head = */ prefix##AC_##name | _SYSCALL_DB_INIT_ARGDW(prefix, name), \
	/* .sc_##name##_name = */ #name,                                                    \
	_SYSCALL_DB_INIT_ARGS(prefix, name, prefix##AC_##name)

#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct __ATTR_PACKED struct_syscalldb##table_id {
#define __SYSCALL(name) SYSCALL_DB_DECL(__NR, name)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include <asm/ls-syscalls.h>

#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PRIVATE struct struct_syscalldb##table_id const syscalldb##table_id = {
#define __SYSCALL(name) SYSCALL_DB_INIT(__NR, name)
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include <asm/ls-syscalls.h>

#ifdef __ARCH_HAVE_COMPAT
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	struct __ATTR_PACKED struct_compat_syscalldb##table_id {
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define __SYSCALL(name) SYSCALL_DB_DECL(__NR32, name)
#include <asm/ls-syscalls32.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define __SYSCALL(name) SYSCALL_DB_DECL(__NR64, name)
#include <asm/ls-syscalls64.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */

#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PRIVATE struct struct_compat_syscalldb##table_id const compat_syscalldb##table_id = {
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define __SYSCALL(name) SYSCALL_DB_INIT(__NR32, name)
#include <asm/ls-syscalls32.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define __SYSCALL(name) SYSCALL_DB_INIT(__NR64, name)
#include <asm/ls-syscalls64.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */




/* Define  offset lists for where to find specific
 * system call entries the database defined above. */
typedef uint16_t syscalldb_offset_t;

/* Make  sure that our  chosen offset type can  represent all possible offsets.
 * Note that an offset equal to `(syscalldb_offset_t)-1' indicates an undefined
 * system call!
 * If  any of these assertions fail, then  you must assign a larger type
 * for `syscalldb_offset_t', though  given that right  now it's  already
 * 16-bit, any of these assertions failing is rather likely to be caused
 * by some kind of problem with the system call table distribution. */
#define ASSERT_OFFSET_OK(table_id) \
	static_assert((syscalldb_offset_t)-1 >= sizeof(syscalldb##table_id));
__NRFEAT_SYSCALL_TABLE_FOREACH(ASSERT_OFFSET_OK)
#undef ASSERT_OFFSET_OK
#ifdef __ARCH_HAVE_COMPAT
#define COMPAT_ASSERT_OFFSET_OK(table_id) \
	static_assert((syscalldb_offset_t)-1 >= sizeof(compat_syscalldb##table_id));
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
__NR32FEAT_SYSCALL_TABLE_FOREACH(COMPAT_ASSERT_OFFSET_OK)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
__NR64FEAT_SYSCALL_TABLE_FOREACH(COMPAT_ASSERT_OFFSET_OK)
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#undef COMPAT_ASSERT_OFFSET_OK
#endif /* __ARCH_HAVE_COMPAT */

/* Define the system call database offset tables. */
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PRIVATE syscalldb_offset_t const offset_syscalldb##table_id[__NR_syscall##table_id##_cnt] = {
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) \
	offsetof(struct struct_syscalldb##table_id, sc_##name##_head),
#define __SYSCALL_UNUSED(sysno) (syscalldb_offset_t)-1,
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#include <asm/ls-syscalls.h>

#ifdef __ARCH_HAVE_COMPAT
#define __TSYSCALL(table_id, name, table_index, table_index_without_unused_leading) \
	offsetof(struct struct_compat_syscalldb##table_id, sc_##name##_head),
#define __SYSCALL_UNUSED(sysno) (syscalldb_offset_t)-1,
#define __TSYSCALL_TABLE_END(table_id, ...) \
	};
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PRIVATE syscalldb_offset_t const offset_compat_syscalldb##table_id[__NR32_syscall##table_id##_cnt] = {
#include <asm/ls-syscalls32.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PRIVATE syscalldb_offset_t const offset_compat_syscalldb##table_id[__NR64_syscall##table_id##_cnt] = {
#include <asm/ls-syscalls64.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */




/* Lookup  the   database  entry   for  the   given  system   call.
 * The returned pointer  points to  the start of  a structure  that
 * matches the `Database entry layout for system call descriptors',
 * as documented further up in this file. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) byte_t const *
NOTHROW_NCX(CC sc_lookup)(struct rpc_syscall_info const *__restrict sc_info) {
	byte_t const *result;
	syscalldb_offset_t offset;
	syscall_ulong_t sysno;
	sysno = sc_info->rsi_sysno;
#ifdef __ARCH_HAVE_COMPAT
	if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(sc_info->rsi_flags)) {
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define CHECK_SYSCALL_IN_TABLE(table_id)                                                        \
		if (sysno >= __NR32_syscall##table_id##_min &&                                          \
		    sysno <= __NR32_syscall##table_id##_max) {                                          \
			result = (byte_t const *)&compat_syscalldb##table_id;                               \
			offset = offset_compat_syscalldb##table_id[sysno - __NR32_syscall##table_id##_min]; \
		} else
		__NR32FEAT_SYSCALL_TABLE_FOREACH(CHECK_SYSCALL_IN_TABLE)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define CHECK_SYSCALL_IN_TABLE(table_id)                                                        \
		if (sysno >= __NR64_syscall##table_id##_min &&                                          \
		    sysno <= __NR64_syscall##table_id##_max) {                                          \
			result = (byte_t const *)&compat_syscalldb##table_id;                               \
			offset = offset_compat_syscalldb##table_id[sysno - __NR64_syscall##table_id##_min]; \
		} else
		__NR64FEAT_SYSCALL_TABLE_FOREACH(CHECK_SYSCALL_IN_TABLE)
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#undef CHECK_SYSCALL_IN_TABLE
		{
			/* System call number not apart of any known table. */
			goto unknown_syscall;
		}
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
#define CHECK_SYSCALL_IN_TABLE(table_id)                                               \
		if (sysno >= __NR_syscall##table_id##_min &&                                   \
		    sysno <= __NR_syscall##table_id##_max) {                                   \
			result = (byte_t const *)&syscalldb##table_id;                             \
			offset = offset_syscalldb##table_id[sysno - __NR_syscall##table_id##_min]; \
		} else
		__NRFEAT_SYSCALL_TABLE_FOREACH(CHECK_SYSCALL_IN_TABLE)
#undef CHECK_SYSCALL_IN_TABLE
		{
			/* System call number not apart of any known table. */
			goto unknown_syscall;
		}
	}
	if unlikely(offset == (syscalldb_offset_t)-1)
		goto unknown_syscall; /* Unknown system call */

	/* Apply the offset to the start of the system call's descriptor entry. */
	result += offset;
	return result;
unknown_syscall:
	return NULL;
}



/* Get a description  of the  system call  described by  `sc_info' in  `desc'
 * This  is  the main  function used  to access  the system  call description
 * database for the purpose of doing things such as printing a representation
 * of a system call invocation.
 * @return: true:  The system call was recognized, and `desc' was filled accordingly.
 * @return: false: Unknown system call (`desc' was filled with stub-values) */
INTERN NONNULL((1, 2)) bool
NOTHROW_NCX(CC libsc_getdesc)(struct rpc_syscall_info const *__restrict sc_info,
                              struct sc_desc *__restrict desc) {
	uint8_t header;
	byte_t const *sc;
	unsigned int i, regi;

	/* Lookup the system call within the system call descriptor database. */
	sc = sc_lookup(sc_info);
	if unlikely(!sc)
		goto unknown_syscall;

	/* Decode the system call database entry.
	 * NOTE: The exact format is documented at the top of this file! */
	header = *sc++;
	desc->sc_argc = header & 7; /* Mask 0xf8 describes double-wide arguments. */
	desc->sc_name = (char const *)sc;
	header >>= 3;

	/* Per-argument information. */
	for (i = 0, regi = 0; i < desc->sc_argc; ++i) {
		uint16_t word;
		sc = (byte_t const *)(strend((char const *)sc) + 1);
		word = UNALIGNED_GET16(sc);
		sc += 2;
		desc->sc_argv[i].sa_type = word & 0x1fff;
		desc->sc_argv[i].sa_link = NULL;
		if ((word & 0xe000) != 0xe000)
			desc->sc_argv[i].sa_link = &desc->sc_argv[(word & 0xe000) >> 13];
		desc->sc_argv[i].sa_name = (char const *)sc;
		if unlikely(regi >= 6)
			goto unknown_syscall; /* Shouldn't happen! */

		/* Load the argument value. */
		if ((header & ((uint8_t)1 << i)) != 0) {
			/* Double-wide argument */
#ifdef __ARCH_HAVE_COMPAT
			if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(sc_info->rsi_flags)) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)((uint64_t)(compat_uintptr_t)sc_info->rsi_regs[regi] |
				                                              (uint64_t)(compat_uintptr_t)sc_info->rsi_regs[regi + 1] << 32);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)((uint64_t)(compat_uintptr_t)sc_info->rsi_regs[regi] << 32 |
				                                              (uint64_t)(compat_uintptr_t)sc_info->rsi_regs[regi + 1]);
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported `__BYTE_ORDER__'"
#endif /* __BYTE_ORDER__ != ... */
			} else
#endif /* __ARCH_HAVE_COMPAT */
			{
				/* XXX: Technically,  double-wide  here  would  mean  double-syscall_ulong_t.
				 *      Only when syscall_ulong_t  is 32-bit would  that translate to  64-bit
				 *      in total.  However,  since  KOS doesn't  actually  have  any  128-bit
				 *      system calls when running with a 64-bit bus width, this functionality
				 *      is  unused, though  still partially  implemented in  case such system
				 *      calls ever need to be defined. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)((uint64_t)(uintptr_t)sc_info->rsi_regs[regi] |
				                                              (uint64_t)(uintptr_t)sc_info->rsi_regs[regi + 1] << 32);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)((uint64_t)(uintptr_t)sc_info->rsi_regs[regi] << 32 |
				                                              (uint64_t)(uintptr_t)sc_info->rsi_regs[regi + 1]);
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported `__BYTE_ORDER__'"
#endif /* __BYTE_ORDER__ != ... */
			}
			++regi;
		} else {
			/* Single-wide argument */
#ifdef __ARCH_HAVE_COMPAT
			if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(sc_info->rsi_flags)) {
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)(compat_uintptr_t)sc_info->rsi_regs[regi];
			} else
#endif /* __ARCH_HAVE_COMPAT */
			{
				desc->sc_argv[i].sa_value.sv_u64 = (uint64_t)(uintptr_t)sc_info->rsi_regs[regi];
			}
		}
		++regi;
	}

	/* Special handling for certain system calls. */
#ifdef __ARCH_HAVE_COMPAT
	if (RPC_SYSCALL_INFO_METHOD_ISCOMPAT(sc_info->rsi_flags)) {
		switch (sc_info->rsi_sysno) {
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define COMPAT_NR(x) __NR32_##x
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define COMPAT_NR(x) __NR64_##x
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported __ARCH_COMPAT_SIZEOF_POINTER"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */

#if __ARCH_COMPAT_SIZEOF_POINTER == 4 ? defined(__NR32_open) : defined(__NR64_open)
		case COMPAT_NR(open):
			/* sys_open() ignores the 3rd argument in certain cases */
			if (desc->sc_argc == 3 &&
			    (desc->sc_argv[1].sa_value.sv_u64 & O_CREAT) != O_CREAT &&
			    (desc->sc_argv[1].sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
				desc->sc_argc = 2;
			break;
#endif /* __NR(32|64)_open */

#if __ARCH_COMPAT_SIZEOF_POINTER == 4 ? defined(__NR32_openat) : defined(__NR64_openat)
		case COMPAT_NR(openat):
			/* sys_openat() ignores the 4th argument in certain cases */
			if (desc->sc_argc == 4 &&
			    (desc->sc_argv[2].sa_value.sv_u64 & O_CREAT) != O_CREAT &&
			    (desc->sc_argv[2].sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
				desc->sc_argc = 3;
			break;
#endif /* __NR(32|64)_openat */

#if __ARCH_COMPAT_SIZEOF_POINTER == 4 ? defined(__NR32_mremap) : defined(__NR64_mremap)
		case COMPAT_NR(mremap):
			/* sys_mremap() ignores the 5th argument when the FIXED flag isn't given */
			if (desc->sc_argc == 5 &&
			    !(desc->sc_argv[3].sa_value.sv_u64 & MREMAP_FIXED))
				desc->sc_argc = 4;
			break;
#endif /* __NR(32|64)_mremap */

		default:
			break;
		}
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		switch (sc_info->rsi_sysno) {

#ifdef __NR_open
		case __NR_open:
			/* sys_open() ignores the 3rd argument in certain cases */
			if (desc->sc_argc == 3 &&
			    (desc->sc_argv[1].sa_value.sv_u64 & O_CREAT) != O_CREAT &&
			    (desc->sc_argv[1].sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
				desc->sc_argc = 2;
			break;
#endif /* __NR_open */

#ifdef __NR_openat
		case __NR_openat:
			/* sys_openat() ignores the 4th argument in certain cases */
			if (desc->sc_argc == 4 &&
			    (desc->sc_argv[2].sa_value.sv_u64 & O_CREAT) != O_CREAT &&
			    (desc->sc_argv[2].sa_value.sv_u64 & O_TMPFILE) != O_TMPFILE)
				desc->sc_argc = 3;
			break;
#endif /* __NR_openat */

#ifdef __NR_mremap
		case __NR_mremap:
			/* sys_mremap() ignores the 5th argument when the FIXED flag isn't given */
			if (desc->sc_argc == 5 &&
			    !(desc->sc_argv[3].sa_value.sv_u64 & MREMAP_FIXED))
				desc->sc_argc = 4;
			break;
#endif /* __NR_mremap */

		default:
			break;
		}
	}

	return true;

	/* Fallback: Fill in `desc' with stub-values */
unknown_syscall:
	desc->sc_argc = 6;
	desc->sc_name = NULL;
	for (i = 0; i < 6; ++i) {
		desc->sc_argv[i].sa_name         = NULL;
		desc->sc_argv[i].sa_type         = SC_REPR_POINTER;
		desc->sc_argv[i].sa_link         = NULL;
		desc->sc_argv[i].sa_value.sv_u64 = sc_info->rsi_regs[i];
	}
	return false;
}


DEFINE_PUBLIC_ALIAS(sc_getdesc, libsc_getdesc);


DECL_END

#endif /* !GUARD_LIBSCTRACE_SC_GETDESC_C */
