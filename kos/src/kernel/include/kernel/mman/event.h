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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EVENT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EVENT_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <kernel/driver-callbacks.h>

#ifdef __CC__
DECL_BEGIN

/* List of callbacks that should be invoked after mman_exec()
 * These  are called alongside stuff like `handman_cloexec()'
 * NOTE: The passed mman is always `THIS_MMAN', and is never `&mman_kernel' */
DATDEF CALLBACK_LIST(void KCALL(void)) mman_onexec_callbacks;
/* Mman initialization/finalization callbacks. */
DATDEF CALLBACK_LIST(void FCALL(struct mman *)) mman_oninit_callbacks;
DATDEF CALLBACK_LIST(void FCALL(struct mman *)) mman_onfini_callbacks;
DATDEF CALLBACK_LIST(void FCALL(struct mman * /*newmman*/, struct mman * /*oldmman*/)) mman_onclone_callbacks;

#ifdef BUILDING_KERNEL_CORE
/* >> void KCALL func(void);
 * Invoked before returning to user-space after a new application was loaded. */
#define DEFINE_PERMMAN_ONEXEC(func) DEFINE_CALLBACK(".rodata.callback.permman.onexec", func)
/* >> void KCALL func(struct mman *__restrict self); */
#define DEFINE_PERMMAN_INIT(func)   DEFINE_CALLBACK(".rodata.callback.permman.init", func)
/* >> NOBLOCK void NOTHROW(KCALL func)(struct mman *__restrict self); */
#define DEFINE_PERMMAN_FINI(func)   DEFINE_CALLBACK(".rodata.callback.permman.fini", func)
/* >> NOBLOCK void KCALL func(struct mman *__restrict newmman, struct mman *__restrict oldmman); */
#define DEFINE_PERMMAN_CLONE(func)  DEFINE_CALLBACK(".rodata.callback.permman.clone", func)
#endif /* BUILDING_KERNEL_CORE */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EVENT_H */
