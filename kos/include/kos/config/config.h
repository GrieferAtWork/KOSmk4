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
/*!ignore_unnecessary_include*/
#ifndef _KOS_CONFIG_CONFIG_H
#define _KOS_CONFIG_CONFIG_H 1

/* Pull in config-specific macro feature files
 *
 * NOTE: This header should not be used by third-party programs.
 *       It  is only here in order to implement a unified method
 *       by which the KOS kernel and its system libraries can be
 *       configured using a single-source-of-truth.
 *
 * If a third party program were to access this header, it  would
 * not get the information it desires, but would (probably)  just
 * get one of the default configurations below, based on how that
 * program is being compiled.
 *
 * For more information on KOS system configurations
 * see: configurations/readme.md
 */

#ifdef __KOS__
#ifdef CONFIG_HEADER
/* Pull in the config header (one of <kos/config/configurations/xxx.h>)
 * This  macro  should  have  be  defined  on  the  commandline   like:
 * - `-DCONFIG_HEADER="configurations/myconfig.h"'
 */
#include CONFIG_HEADER
#else /* CONFIG_HEADER */

/* No explicit configuration given; must be one of the default configs */
#ifdef __OPTIMIZE__
#ifdef NDEBUG
#include "configurations/OnD.h"
#else /* NDEBUG */
#include "configurations/OD.h"
#endif /* !NDEBUG */
#else /* __OPTIMIZE__ */
#ifdef NDEBUG
#include "configurations/nOnD.h"
#else /* NDEBUG */
#include "configurations/nOD.h"
#endif /* !NDEBUG */
#endif /* !__OPTIMIZE__ */
#endif /* !CONFIG_HEADER */

#ifndef CONFIG_NAME
#error "`#include CONFIG_HEADER' should have at least set the configuration's name"
#endif /* !CONFIG_NAME */

#ifndef CONFIG_PRETTY_NAME
#define CONFIG_PRETTY_NAME CONFIG_NAME
#endif /* !CONFIG_PRETTY_NAME */
#endif /* __KOS__ */

#endif /* !_KOS_CONFIG_CONFIG_H */
