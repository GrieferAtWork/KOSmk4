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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H 1

#include <kernel/compiler.h>

#include <kernel/mman/module.h>

/* This header only defines the bare minimum to get  interactions
 * with driver objects going. (such as refcnt support for the all
 * important `struct driver', as well as the magical `drv_self')
 *
 * All of the other stuff, including loading/unloading of drivers
 * is contained in <kernel/mman/driver.h>! */

#ifdef __CC__
DECL_BEGIN

/* Enable reference count interface support without
 * having to define  the layout of  `struct driver' */
#ifndef __driver_defined
struct driver;
#define __driver_as_module(self)  ((struct module *)(self))
#define __driver_destroy(self)    module_destroy((struct module *)(self))
#define __driver_free(self)       module_free((struct module *)(self))
#define __driver_refcnt(self)     ((struct module *)(self))->md_refcnt
#define __driver_weakrefcnt(self) ((struct module *)(self))->md_weakrefcnt
#define __DRIVER_REFCNT_FUNCTIONS_DEFINED
DEFINE_REFCNT_FUNCTIONS_P(struct driver, __driver_refcnt, __driver_destroy)
DEFINE_WEAKREFCNT_FUNCTIONS_P(struct driver, __driver_weakrefcnt, __driver_free)
#else /* !__driver_defined */
#ifndef __driver_destroy
#define __driver_destroy(self)    module_destroy(__driver_as_module(self))
#endif /* !__driver_destroy */
#ifndef __driver_free
#define __driver_free(self)       module_free(__driver_as_module(self))
#endif /* !__driver_free */
#ifndef __driver_refcnt
#define __driver_refcnt(self)     __driver_as_module(self)->md_refcnt
#endif /* !__driver_refcnt */
#ifndef __driver_weakrefcnt
#define __driver_weakrefcnt(self) __driver_as_module(self)->md_weakrefcnt
#endif /* !__driver_weakrefcnt */
#endif /* __driver_defined */

/* The driver descriptor for the kernel core */
#ifndef __kernel_driver_defined
#define __kernel_driver_defined
DATDEF struct driver kernel_driver;
DATDEF struct module __kernel_driver ASMNAME("kernel_driver");
#define kernel_driver (*(struct driver *)&__kernel_driver)
#endif /* !__kernel_driver_defined */


/* Special driver symbols */
#ifndef CONFIG_BUILDING_KERNEL_CORE
#ifndef __drv_self_defined
#define __drv_self_defined
/* Self-pointer to the current driver's descriptor */
DATDEF struct driver drv_self;
DATDEF struct module __drv_self ASMNAME("drv_self");
#define drv_self (*(struct driver *)&__drv_self)
#endif /* !__drv_self_defined */

struct mfile;
DATDEF byte_t /*  */ drv_loadaddr[]; /* Absolute load-address of the driver (== drv_self.md_loadaddr) */
DATDEF byte_t /*  */ drv_loadmin[];  /* Absolute min-address of the driver program (== drv_self.md_loadmin) */
DATDEF byte_t /*  */ drv_loadmax[];  /* Absolute max-address of the driver program (== drv_self.md_loadmax) */
DATDEF char /*    */ drv_name[];     /* Name of the driver (== drv_self.d_name) */
DATDEF struct mfile *drv_file;       /* [0..1] File object of the driver (== drv_self.d_file) */
DATDEF char /*    */ drv_cmdline[];  /* Driver commandline as a \0\0-terminated, \0-seperated string (== drv_self.d_cmdline) */
DATDEF size_t /*  */ drv_argc;       /* Driver argument count (== &drv_self.d_argc) */
DATDEF char /*   */ *drv_argv[];     /* [1..1][drv_argc] Driver argument vector (== drv_self.d_argv) */

struct ccinfo;

/* NOTE: This function may be implemented by individual drivers,
 *       and isn't  something that  is exported  by the  kernel!
 * Try to clear global caches. Called by `system_cc()' */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL drv_cc)(struct ccinfo *__restrict info);

#ifndef DRIVER_INIT
#define DRIVER_INIT __attribute__((__constructor__))
#define DRIVER_FINI __attribute__((__destructor__))
#endif /* !DRIVER_INIT */
#else /* !CONFIG_BUILDING_KERNEL_CORE */
#ifndef __drv_self_defined
#define __drv_self_defined
DATDEF struct driver drv_self ASMNAME("kernel_driver");
DATDEF struct module __drv_self ASMNAME("kernel_driver");
#define drv_self (*(struct driver *)&__drv_self)
#endif /* !__drv_self_defined */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H */
