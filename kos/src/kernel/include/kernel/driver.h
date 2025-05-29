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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h> /* ATTR_BLOCKLIKE_CC(...) */
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
#define _driver_as_module(self)  ((struct module *)(self))
#define _driver_destroy(self)    module_destroy((struct module *)(self))
#define _driver_free(self)       module_free((struct module *)(self))
#define _driver_refcnt(self)     ((struct module *)(self))->md_refcnt
#define _driver_weakrefcnt(self) ((struct module *)(self))->md_weakrefcnt
#define __DRIVER_REFCNT_FUNCTIONS_DEFINED
DEFINE_REFCNT_FUNCTIONS_P(struct driver, _driver_refcnt, _driver_destroy)
DEFINE_WEAKREFCNT_FUNCTIONS_P(struct driver, _driver_weakrefcnt, _driver_free)
#else /* !__driver_defined */
#ifndef _driver_destroy
#define _driver_destroy(self) module_destroy(_driver_as_module(self))
#endif /* !_driver_destroy */
#ifndef _driver_free
#define _driver_free(self) module_free(_driver_as_module(self))
#endif /* !_driver_free */
#ifndef _driver_refcnt
#define _driver_refcnt(self) _driver_as_module(self)->md_refcnt
#endif /* !_driver_refcnt */
#ifndef _driver_weakrefcnt
#define _driver_weakrefcnt(self) _driver_as_module(self)->md_weakrefcnt
#endif /* !_driver_weakrefcnt */
#endif /* __driver_defined */

/* The driver descriptor for the kernel core */
#ifndef __kernel_driver_defined
#define __kernel_driver_defined
DATDEF struct driver kernel_driver;
DATDEF struct module _kernel_driver_as_module ASMNAME("kernel_driver");
#define kernel_driver (*(struct driver *)&_kernel_driver_as_module)
#endif /* !__kernel_driver_defined */


/* Special driver symbols */
#ifndef BUILDING_KERNEL_CORE
#ifndef __drv_self_defined
#define __drv_self_defined
/* Self-pointer to the current driver's descriptor */
DATDEF struct driver drv_self;
DATDEF struct module _drv_self_as_module ASMNAME("drv_self");
#define drv_self (*(struct driver *)&_drv_self_as_module)
#endif /* !__drv_self_defined */

struct mfile;
DATDEF byte_t /*  */ drv_loadaddr[]; /* Absolute load-address of the driver (== drv_self.md_loadaddr) */
DATDEF byte_t /*  */ drv_loadmin[];  /* Absolute min-address of the driver program (== drv_self.md_loadmin) */
DATDEF byte_t /*  */ drv_loadmax[];  /* Absolute max-address of the driver program (== drv_self.md_loadmax) */
DATDEF char /*    */ drv_name[];     /* Name of the driver (== drv_self.d_name) */
DATDEF struct mfile *drv_file;       /* [0..1] File object of the driver (== drv_self.d_file) */
DATDEF char /*    */ drv_cmdline[];  /* Driver commandline as a \0\0-terminated, \0-separated string (== drv_self.d_cmdline) */
DATDEF size_t /*  */ drv_argc;       /* Driver argument count (== &drv_self.d_argc) */
DATDEF char /*   */ *drv_argv[];     /* [1..1][drv_argc] Driver argument vector (== drv_self.d_argv) */

struct ccinfo;

/* NOTE: This function may be implemented by individual drivers,
 *       and isn't  something that  is exported  by the  kernel!
 * Try to clear global caches. Called by `system_cc()' */
FUNDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL drv_cc)(struct ccinfo *__restrict info);

#ifndef DRIVER_INIT
#define DRIVER_INIT __attribute__((__constructor__))
#define DRIVER_FINI __attribute__((__destructor__))
#endif /* !DRIVER_INIT */
#else /* !BUILDING_KERNEL_CORE */
#ifndef __drv_self_defined
#define __drv_self_defined
DATDEF struct driver drv_self ASMNAME("kernel_driver");
DATDEF struct module _drv_self_as_module ASMNAME("kernel_driver");
#define drv_self (*(struct driver *)&_drv_self_as_module)
#endif /* !__drv_self_defined */
#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H */
