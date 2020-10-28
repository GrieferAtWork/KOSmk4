/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_INCLUDE_ERROR_H
#define GUARD_MODDBX_INCLUDE_ERROR_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

#define DBX_EISERR(x) ((x) < 0) /* Check for error */

#define DBX_EOK      (0)  /* Success */
#define DBX_ENOMEM   (-1) /* Out of memory */
#define DBX_ESYNTAX  (-2) /* Syntax error */
#define DBX_EDIVZERO (-3) /* Divide by zero */
#define DBX_ENOENT   (-4) /* No such object */
#define DBX_ERDONLY  (-5) /* Read-only */
#define DBX_EINTERN  (-6) /* Internal error */
#define DBX_EFAULT   (-7) /* Segmentation fault */
typedef int dbx_errno_t;

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_ERROR_H */
