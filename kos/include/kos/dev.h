/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _KOS_DEV_H
#define _KOS_DEV_H 1

#include <__stdinc.h>
#include <bits/types.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

#define DEV_UNSET      __CCAST(dev_t)(0) /* Unset device number */
#define DEV_MAJOR_AUTO 256               /* The first automatically assigned device major-number */

#define MINORBITS      20
#define MAJORBITS      12
#define MINORMASK    ((1 << MINORBITS)-1)
#define MAJORMASK    ((1 << MAJORBITS)-1)

#define MAJOR(dev)   (__CCAST(uintptr_t)(dev) >> MINORBITS)
#define MINOR(dev)   (__CCAST(uintptr_t)(dev) &  MINORMASK)
#define MKDEV(ma,mi) (__CCAST(dev_t)((ma) << MINORBITS | (mi)))

#ifdef __CC__
__DECL_BEGIN

#ifndef __dev_t_defined
#define __dev_t_defined 1
typedef __typedef_dev_t dev_t;
#endif /* !__dev_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_DEV_H */
