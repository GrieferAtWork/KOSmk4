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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXEC_BITS_LIBRARY_H
#define _KOS_EXEC_BITS_LIBRARY_H 1

#include <__stdinc.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __CC__

#ifdef __KERNEL__
struct driver;
typedef struct driver *library_handle_t;
typedef struct driver_section *section_handle_t;
#else /* __KERNEL__ */
#ifdef GUARD_LIBDL_API_H
struct dlmodule;
struct dlsection;
typedef struct dlmodule *library_handle_t;
typedef struct dlsection *section_handle_t;
#else /* GUARD_LIBDL_API_H */
#ifdef __INTELLISENSE__
struct __library_handle_struct;
typedef struct __library_handle_struct *library_handle_t;
#else /* __INTELLISENSE__ */
typedef void *library_handle_t;
#endif /* !__INTELLISENSE__ */
typedef struct dl_section *section_handle_t;
#endif /* !GUARD_LIBDL_API_H */
typedef __fd_t library_file_t;
#endif /* !__KERNEL__ */

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_EXEC_BITS_LIBRARY_H */
