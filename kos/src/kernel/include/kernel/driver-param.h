/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_PARAM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_PARAM_H 1

#include <kernel/compiler.h>

#ifndef BUILDING_KERNEL_CORE
#ifndef DRIVER_INIT
#define DRIVER_INIT __attribute__((__constructor__))
#define DRIVER_FINI __attribute__((__destructor__))
#endif /* !DRIVER_INIT */

/* TODO: Re-work these macros into something that is more pretty. */
#define DEFINE_CMDLINE_FLAG_VAR(flagname, parname)              extern bool flagname ASMNAME("\"drv_arg$" parname "\"");
#define DEFINE_CMDLINE_PARAM_STRING_VAR(string_name, parname)   extern char string_name[] ASMNAME("\"drv_arg$" parname "$s\"");
#define DEFINE_CMDLINE_PARAM_INT8_VAR(varname, parname, defl)   extern int8_t varname ASMNAME("\"drv_arg$" parname "$I8d$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_INT16_VAR(varname, parname, defl)  extern int16_t varname ASMNAME("\"drv_arg$" parname "$I16d$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_INT32_VAR(varname, parname, defl)  extern int32_t varname ASMNAME("\"drv_arg$" parname "$I32d$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_INT64_VAR(varname, parname, defl)  extern int64_t varname ASMNAME("\"drv_arg$" parname "$I64d$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_UINT8_VAR(varname, parname, defl)  extern uint8_t varname ASMNAME("\"drv_arg$" parname "$I8u$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_UINT16_VAR(varname, parname, defl) extern uint16_t varname ASMNAME("\"drv_arg$" parname "$I16u$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_UINT32_VAR(varname, parname, defl) extern uint32_t varname ASMNAME("\"drv_arg$" parname "$I32u$" PP_STR(defl) "\"");
#define DEFINE_CMDLINE_PARAM_UINT64_VAR(varname, parname, defl) extern uint64_t varname ASMNAME("\"drv_arg$" parname "$I64u$" PP_STR(defl) "\"");

#define _DEFINE_CMDLINE_PARAM_INTN_VAR_1   DEFINE_CMDLINE_PARAM_INT8_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_2   DEFINE_CMDLINE_PARAM_INT16_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_4   DEFINE_CMDLINE_PARAM_INT32_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_8   DEFINE_CMDLINE_PARAM_INT64_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR(n)  _DEFINE_CMDLINE_PARAM_INTN_VAR_##n
#define DEFINE_CMDLINE_PARAM_INTN_VAR(n)   _DEFINE_CMDLINE_PARAM_INTN_VAR(n)
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_1  DEFINE_CMDLINE_PARAM_UINT8_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_2  DEFINE_CMDLINE_PARAM_UINT16_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_4  DEFINE_CMDLINE_PARAM_UINT32_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_8  DEFINE_CMDLINE_PARAM_UINT64_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR(n) _DEFINE_CMDLINE_PARAM_UINTN_VAR_##n
#define DEFINE_CMDLINE_PARAM_UINTN_VAR(n)  _DEFINE_CMDLINE_PARAM_UINTN_VAR(n)

#define DEFINE_CMDLINE_PARAM_INT_VAR(varname, parname, defl)      DEFINE_CMDLINE_PARAM_INTN_VAR(__SIZEOF_INT__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_UINT_VAR(varname, parname, defl)     DEFINE_CMDLINE_PARAM_UINTN_VAR(__SIZEOF_INT__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_INTPTR_VAR(varname, parname, defl)   DEFINE_CMDLINE_PARAM_INTN_VAR(__SIZEOF_POINTER__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_UINTPTR_VAR(varname, parname, defl)  DEFINE_CMDLINE_PARAM_UINTN_VAR(__SIZEOF_POINTER__)(varname, parname, defl)

#else /* BUILDING_KERNEL_CORE */

#include <kernel/arch/driver-param.h>

#include <hybrid/typecore.h>

DECL_BEGIN



#define KERNEL_COMMANDLINE_OPTION_TYPE_FUNC    0  /* co_handler(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_STRING  1  /* *(char **)co_option_addr = ARG_OF(co_name) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT 2  /* co_present() */
#define KERNEL_COMMANDLINE_OPTION_TYPE_BOOL    3  /* *(bool *)co_option_addr = IS_PRESENT(co_name) ? true : false; */
#define KERNEL_COMMANDLINE_OPTION_TYPE_INT8    4  /* *(int8_t *)co_option_addr = TO_INT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_INT16   5  /* *(int16_t *)co_option_addr = TO_INT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_INT32   6  /* *(int32_t *)co_option_addr = TO_INT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_INT64   7  /* *(int64_t *)co_option_addr = TO_INT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINT8   8  /* *(uint8_t *)co_option_addr = TO_UINT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINT16  9  /* *(uint16_t *)co_option_addr = TO_UINT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINT32  10 /* *(uint32_t *)co_option_addr = TO_UINT(ARG_OF(co_name)) */
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINT64  11 /* *(uint64_t *)co_option_addr = TO_UINT(ARG_OF(co_name)) */

#if __SIZEOF_SIZE_T__ == 4
#define KERNEL_COMMANDLINE_OPTION_TYPE_SSIZE_T KERNEL_COMMANDLINE_OPTION_TYPE_INT32
#define KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T  KERNEL_COMMANDLINE_OPTION_TYPE_UINT32
#elif __SIZEOF_SIZE_T__ == 8
#define KERNEL_COMMANDLINE_OPTION_TYPE_SSIZE_T KERNEL_COMMANDLINE_OPTION_TYPE_INT64
#define KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T  KERNEL_COMMANDLINE_OPTION_TYPE_UINT64
#elif __SIZEOF_SIZE_T__ == 2
#define KERNEL_COMMANDLINE_OPTION_TYPE_SSIZE_T KERNEL_COMMANDLINE_OPTION_TYPE_INT16
#define KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T  KERNEL_COMMANDLINE_OPTION_TYPE_UINT16
#elif __SIZEOF_SIZE_T__ == 1
#define KERNEL_COMMANDLINE_OPTION_TYPE_SSIZE_T KERNEL_COMMANDLINE_OPTION_TYPE_INT8
#define KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T  KERNEL_COMMANDLINE_OPTION_TYPE_UINT8
#else
#error "Unsupported sizeof(size_t)"
#endif

#if __SIZEOF_POINTER__ == 4
#define KERNEL_COMMANDLINE_OPTION_TYPE_INTPTR_T  KERNEL_COMMANDLINE_OPTION_TYPE_INT32
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINTPTR_T KERNEL_COMMANDLINE_OPTION_TYPE_UINT32
#elif __SIZEOF_POINTER__ == 8
#define KERNEL_COMMANDLINE_OPTION_TYPE_INTPTR_T  KERNEL_COMMANDLINE_OPTION_TYPE_INT64
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINTPTR_T KERNEL_COMMANDLINE_OPTION_TYPE_UINT64
#elif __SIZEOF_POINTER__ == 2
#define KERNEL_COMMANDLINE_OPTION_TYPE_INTPTR_T  KERNEL_COMMANDLINE_OPTION_TYPE_INT16
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINTPTR_T KERNEL_COMMANDLINE_OPTION_TYPE_UINT16
#elif __SIZEOF_POINTER__ == 1
#define KERNEL_COMMANDLINE_OPTION_TYPE_INTPTR_T  KERNEL_COMMANDLINE_OPTION_TYPE_INT8
#define KERNEL_COMMANDLINE_OPTION_TYPE_UINTPTR_T KERNEL_COMMANDLINE_OPTION_TYPE_UINT8
#else
#error "Unsupported sizeof(void *)"
#endif

/* Very early: Nothing is initialized, yet
 *    WARNING: Strings passed on  this level will  become invalid  invalidated
 *             once `DEFINE_KERNEL_COMMANDLINE_OPTION()' options are evaluated */
#ifndef DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION
#error "Forgot to #define DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(addr, type, name) ..."
#endif /* !DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION */

/* Early:      Memory and system information was gathered
 *    WARNING: Strings passed on  this level will  become invalid  invalidated
 *             once `DEFINE_KERNEL_COMMANDLINE_OPTION()' options are evaluated */
#ifndef DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION
#error "Forgot to #define DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION(addr, type, name) ..."
#endif /* !DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION */

/* Stable:     System  devices   have  gotten   at  least   minimal
 *             initialization, and kernel VM protections are active */
#ifndef DEFINE_KERNEL_COMMANDLINE_OPTION
#error "Forgot to #define DEFINE_KERNEL_COMMANDLINE_OPTION(addr, type, name) ..."
#endif /* !DEFINE_KERNEL_COMMANDLINE_OPTION */

/* NoFS:       All builtin and bootloader drivers  have been loaded and  initialized,
 *             however no filesystem has yet to be mounted (this boot stage is mainly
 *             intended  to implement the `boot' commandline option to allow the boot
 *             device that should get mounted under `/' to be overwritten) */
#ifndef DEFINE_LATE_KERNEL_COMMANDLINE_OPTION
#error "Forgot to #define DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(addr, type, name) ..."
#endif /* !DEFINE_LATE_KERNEL_COMMANDLINE_OPTION */


struct kernel_commandline_option {
	union __ATTR_PACKED {
		void (KCALL *co_handler)(char *__restrict arg); /* Address of a handler function */
		void (KCALL *co_present)(void);                 /* Address of a function invoked if the option is present */
		void *co_option_addr;                           /* Address of an integer/flag option */
	};
	char                          co_type;     /* Option type (One of `KERNEL_COMMANDLINE_OPTION_TYPE_*') */
	COMPILER_FLEXIBLE_ARRAY(char, co_name);    /* Option name. */
};



/* >> void KCALL flag_handler(void);
 * >> if (has_option("<parname>")) flag_handler(); */
#define DEFINE_CMDLINE_FLAG_HANDLER(flag_handler, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(flag_handler, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, parname)

/* >> bool flagname;
 * >> flagname = has_option("<parname>") ? true : false; */
#define DEFINE_CMDLINE_FLAG(flagname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(flagname, KERNEL_COMMANDLINE_OPTION_TYPE_BOOL, parname)
#define DEFINE_CMDLINE_FLAG_VAR(flagname, parname) \
	INTERN bool flagname = false;                  \
	DEFINE_CMDLINE_FLAG(flagname, parname)


/* >> char *varname;
 * >> if (has_option("<parname>=$VALUE")) varname = "$VALUE"; */
#define DEFINE_CMDLINE_PARAM_STRING(string_name, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(string_name, KERNEL_COMMANDLINE_OPTION_TYPE_STRING, parname)
#define DEFINE_CMDLINE_PARAM_STRING_VAR(string_name, parname) \
	INTERN char const *string_name = __NULLPTR;               \
	DEFINE_CMDLINE_PARAM_STRING(string_name, parname)

/* >> int8_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strto64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_INT8(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_INT8, parname)
#define DEFINE_CMDLINE_PARAM_INT8_VAR(varname, parname, defl) \
	INTERN int8_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_INT8(varname, parname)

/* >> int16_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strto64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_INT16(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_INT16, parname)
#define DEFINE_CMDLINE_PARAM_INT16_VAR(varname, parname, defl) \
	INTERN int16_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_INT16(varname, parname)

/* >> int32_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strto64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_INT32(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_INT32, parname)
#define DEFINE_CMDLINE_PARAM_INT32_VAR(varname, parname, defl) \
	INTERN int32_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_INT32(varname, parname)

/* >> int64_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strto64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_INT64(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_INT64, parname)
#define DEFINE_CMDLINE_PARAM_INT64_VAR(varname, parname, defl) \
	INTERN int64_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_INT64(varname, parname)

/* >> uint8_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strtou64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_UINT8(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_UINT8, parname)
#define DEFINE_CMDLINE_PARAM_UINT8_VAR(varname, parname, defl) \
	INTERN uint8_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_UINT8(varname, parname)

/* >> uint16_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strtou64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_UINT16(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_UINT16, parname)
#define DEFINE_CMDLINE_PARAM_UINT16_VAR(varname, parname, defl) \
	INTERN uint16_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_UINT16(varname, parname)

/* >> uint32_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strtou64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_UINT32(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_UINT32, parname)
#define DEFINE_CMDLINE_PARAM_UINT32_VAR(varname, parname, defl) \
	INTERN uint32_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_UINT32(varname, parname)

/* >> uint64_t varname;
 * >> if (has_option("<parname>=$VALUE")) varname = strtou64("$VALUE", NULL, 0); */
#define DEFINE_CMDLINE_PARAM_UINT64(varname, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(varname, KERNEL_COMMANDLINE_OPTION_TYPE_UINT64, parname)
#define DEFINE_CMDLINE_PARAM_UINT64_VAR(varname, parname, defl) \
	INTERN uint64_t varname = (defl);                           \
	DEFINE_CMDLINE_PARAM_UINT64(varname, parname)

/* >> void KCALL handler(char const *__restrict arg);
 * >> if (has_option("<parname>=$VALUE")) handler("$VALUE"); */
#define DEFINE_CMDLINE_PARAM(handler, parname) \
	DEFINE_KERNEL_COMMANDLINE_OPTION(handler, KERNEL_COMMANDLINE_OPTION_TYPE_FUNC, parname)

#define _DEFINE_CMDLINE_PARAM_INTN_VAR_1   DEFINE_CMDLINE_PARAM_INT8_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_2   DEFINE_CMDLINE_PARAM_INT16_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_4   DEFINE_CMDLINE_PARAM_INT32_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR_8   DEFINE_CMDLINE_PARAM_INT64_VAR
#define _DEFINE_CMDLINE_PARAM_INTN_VAR(n)  _DEFINE_CMDLINE_PARAM_INTN_VAR_##n
#define DEFINE_CMDLINE_PARAM_INTN_VAR(n)   _DEFINE_CMDLINE_PARAM_INTN_VAR(n)
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_1  DEFINE_CMDLINE_PARAM_UINT8_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_2  DEFINE_CMDLINE_PARAM_UINT16_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_4  DEFINE_CMDLINE_PARAM_UINT32_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR_8  DEFINE_CMDLINE_PARAM_UINT64_VAR
#define _DEFINE_CMDLINE_PARAM_UINTN_VAR(n) _DEFINE_CMDLINE_PARAM_UINTN_VAR_##n
#define DEFINE_CMDLINE_PARAM_UINTN_VAR(n)  _DEFINE_CMDLINE_PARAM_UINTN_VAR(n)

#define DEFINE_CMDLINE_PARAM_INT_VAR(varname, parname, defl)      DEFINE_CMDLINE_PARAM_INTN_VAR(__SIZEOF_INT__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_UINT_VAR(varname, parname, defl)     DEFINE_CMDLINE_PARAM_UINTN_VAR(__SIZEOF_INT__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_INTPTR_VAR(varname, parname, defl)   DEFINE_CMDLINE_PARAM_INTN_VAR(__SIZEOF_POINTER__)(varname, parname, defl)
#define DEFINE_CMDLINE_PARAM_UINTPTR_VAR(varname, parname, defl)  DEFINE_CMDLINE_PARAM_UINTN_VAR(__SIZEOF_POINTER__)(varname, parname, defl)

DECL_END
#endif /* BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_PARAM_H */
