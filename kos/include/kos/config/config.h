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
#ifndef _KOS_CONFIG_CONFIG_H
#define _KOS_CONFIG_CONFIG_H 1

/* Config-specific macro overrides (e.g. '#define CONFIG_NO_KERNEL_EPOLL_RPC') go here */
#ifdef __KOS__
#ifdef CONFIG_HEADER
/* Pull in the config header (one of <kos/config/features/xxx.h>)
 * This  macro should  have be  defined on  the commandline like:
 * - `-DCONFIG_HEADER="features/myconfig.h"'
 */
#include CONFIG_HEADER

#ifndef CONFIG_NAME
#error "`#include CONFIG_HEADER' should have at least set the configuration's name"
#endif /* !CONFIG_NAME */
#else /* CONFIG_HEADER */

/* No explicit configuration given; must be one of the default configs
 * -> Figure out its name! */
#ifdef __OPTIMIZE__
#ifdef NDEBUG
#define CONFIG_NAME "OnD"
#else /* NDEBUG */
#define CONFIG_NAME "OD"
#endif /* !NDEBUG */
#else /* __OPTIMIZE__ */
#ifdef NDEBUG
#define CONFIG_NAME "nOnD"
#else /* NDEBUG */
#define CONFIG_NAME "nOD"
#endif /* !NDEBUG */
#endif /* !__OPTIMIZE__ */

#endif /* !CONFIG_HEADER */
#endif /* __KOS__ */

#endif /* !_KOS_CONFIG_CONFIG_H */
