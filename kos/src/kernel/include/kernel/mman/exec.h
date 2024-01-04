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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXEC_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <kernel/mman/mpart.h>

#ifdef __CC__
DECL_BEGIN

struct execargs; /* from <kernel/execabi.h> */

/* Load  an  executable   binary  into  a   temporary,  emulated   mman.
 * If this succeeds, clear all of the mappings from the given `ea_mman',
 * and  replace them with  the contents of  the temporary, emulated mman
 * (such that the entire process of  mapping the new contents is  always
 * able to either  seamlessly replace  the old memory  mappings, or  not
 * even touch them at all upon error)
 * -> This function is used to implement the exec() family of system calls
 *    in  such that exec() is always able  to allow the calling program to
 *    handle load errors (at least so  long as those errors aren't  caused
 *    by the executable's initialization, such as missing libraries)
 * NOTE: Upon successful return, all threads using `ea_mman' (excluding
 *       the caller themself if they are using the mman, too) will have
 *       been terminated.
 * @param: args:             Exec arguments.
 * @throw: E_BADALLOC:       Insufficient memory.
 * @throw: E_SEGFAULT:       The given `ea_argv', `ea_envp', or one of their pointed-to strings is faulty.
 * @throw: E_NOT_EXECUTABLE: The given `ea_xfile' was not recognized as an acceptable binary. */
FUNDEF BLOCKING NONNULL((1)) void KCALL
mman_exec(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT,
		       E_NOT_EXECUTABLE, E_IOERROR, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXEC_H */
