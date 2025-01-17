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
#ifndef GUARD_KERNEL_SRC_MISC_CMDLINE_C
#define GUARD_KERNEL_SRC_MISC_CMDLINE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/mman/driver.h>
#include <kernel/panic.h>
#include <kernel/types.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

PRIVATE ATTR_FREETEXT ATTR_NOINLINE void
NOTHROW(KCALL malformed_argument)(char const *__restrict optname,
                                  char const *__restrict argstr) {
	kernel_panic(FREESTR("Malformed commandline argument for %q: %q"),
	             optname, argstr);
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE void
NOTHROW(KCALL initialize_cmdline)(struct kernel_commandline_option const *start,
                                  struct kernel_commandline_option const *end) {
	size_t i;
	char *arg;
	if (!kernel_driver.d_cmdline)
		return; /* No commandline provided. */
	while (start < end) {
		size_t namlen;
		namlen = strlen(start->co_name);
		assert(start->co_type <= KERNEL_COMMANDLINE_OPTION_TYPE_UINT64);
		if (start->co_type >= KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT &&
		    start->co_type <= KERNEL_COMMANDLINE_OPTION_TYPE_BOOL) {
			/* Check if the option is present. */
			for (i = 0, arg = kernel_driver.d_cmdline;
			     i < kernel_driver.d_argc; ++i, arg = strend(arg) + 1) {
				if (bcmp(arg, start->co_name, namlen, sizeof(char)) != 0)
					continue;
				if (arg[namlen] != 0)
					continue;
				switch (start->co_type) {

				case KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT:
					(*start->co_present)();
					break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_BOOL:
					*(bool *)start->co_option_addr = true;
					break;

				default: __builtin_unreachable();
				}
				goto next_option;
			}
			if (start->co_type == KERNEL_COMMANDLINE_OPTION_TYPE_BOOL)
				*(bool *)start->co_option_addr = false;
		} else {
			/* Check for an option that has an argument. */
			for (i = 0, arg = kernel_driver.d_cmdline;
			     i < kernel_driver.d_argc; ++i, arg = strend(arg) + 1) {
				char *eq = strchr(arg, '=');
				size_t optlen;
				if (!eq)
					continue;
				optlen = (size_t)(eq - arg);
				if (optlen != namlen)
					continue;
				if (bcmp(arg, start->co_name, optlen, sizeof(char)) != 0)
					continue;
				arg += optlen + 1;
				switch (start->co_type) {

				case KERNEL_COMMANDLINE_OPTION_TYPE_FUNC:
					(*start->co_handler)(arg);
					break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_STRING:
					*(char **)start->co_option_addr = arg;
					break;

#if __SIZEOF_POINTER__ < 8
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT64: {
					char *endp;
					int64_t value;
					value = strto64(arg, &endp, 0);
					if (*endp)
						malformed_argument(start->co_name, arg);
					*(int64_t *)start->co_option_addr = value;
				}	break;
#endif /* __SIZEOF_POINTER__ >= 8 */

#if __SIZEOF_POINTER__ < 8
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64: {
					char *endp;
					uint64_t value;
					value = strtou64(arg, &endp, 0);
					if (*endp)
						malformed_argument(start->co_name, arg);
					*(uint64_t *)start->co_option_addr = value;
				}	break;
#endif /* __SIZEOF_POINTER__ >= 8 */

				case KERNEL_COMMANDLINE_OPTION_TYPE_INT8:
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT16:
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT32: {
					char *endp;
#if __SIZEOF_POINTER__ < 8
					int32_t value;
					value = strto32(arg, &endp, 0);
#else /* __SIZEOF_POINTER__ < 8 */
					int64_t value;
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT64:
					value = strto64(arg, &endp, 0);
#endif /* __SIZEOF_POINTER__ >= 8 */
					if (*endp)
						malformed_argument(start->co_name, arg);
					switch (start->co_type) {
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT8:
						*(int8_t *)start->co_option_addr = (int8_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT16:
						*(int16_t *)start->co_option_addr = (int16_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT32:
						*(int32_t *)start->co_option_addr = (int32_t)value;
						break;
#if __SIZEOF_POINTER__ >= 8
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT64:
						*(int64_t *)start->co_option_addr = (int64_t)value;
						break;
#endif /* __SIZEOF_POINTER__ >= 8 */
					default: __builtin_unreachable();
					}
				}	break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT8:
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT16:
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT32: {
					char *endp;
#if __SIZEOF_POINTER__ < 8
					uint32_t value;
					value = strtou32(arg, &endp, 0);
#else /* __SIZEOF_POINTER__ < 8 */
					uint64_t value;
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64:
					value = strtou64(arg, &endp, 0);
#endif /* __SIZEOF_POINTER__ >= 8 */
					if (*endp)
						malformed_argument(start->co_name, arg);
					switch (start->co_type) {
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT8:
						*(uint8_t *)start->co_option_addr = (uint8_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT16:
						*(uint16_t *)start->co_option_addr = (uint16_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT32:
						*(uint32_t *)start->co_option_addr = (uint32_t)value;
						break;
#if __SIZEOF_POINTER__ >= 8
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64:
						*(uint64_t *)start->co_option_addr = (uint64_t)value;
						break;
#endif /* __SIZEOF_POINTER__ >= 8 */
					default: __builtin_unreachable();
					}
				}	break;

				default: __builtin_unreachable();
				}
				goto next_option;
			}
		}
next_option:
		start = (struct kernel_commandline_option const *)((uintptr_t)start +
		                                                   ((offsetof(struct kernel_commandline_option, co_name) +
		                                                     (namlen + 1) * sizeof(char) + (sizeof(void *) - 1)) &
		                                                    ~(sizeof(void *) - 1)));
	}
}


INTDEF FREE struct kernel_commandline_option const __kernel_commandline_very_early_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_very_early_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_very_early)(void) {
	initialize_cmdline(__kernel_commandline_very_early_start,
	                   __kernel_commandline_very_early_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_early_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_early_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_early)(void) {
	initialize_cmdline(__kernel_commandline_early_start,
	                   __kernel_commandline_early_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_stable_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_stable_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_stable)(void) {
	initialize_cmdline(__kernel_commandline_stable_start,
	                   __kernel_commandline_stable_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_late_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_late_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_late)(void) {
	initialize_cmdline(__kernel_commandline_late_start,
	                   __kernel_commandline_late_end);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_CMDLINE_C */
