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
#ifndef __GUARD_HYBRID_ALTINT_H
#define __GUARD_HYBRID_ALTINT_H 1

/* Alternative integer type
 * For use with Intellisense to aid in highlighting unwanted use of types
 * >> ALTINT_UID(myaltint1)
 * >> ALTINT_UID(myaltint2)
 * >> typedef ALTINT(myaltint1, uint32_t) my_uint32_t;
 * >> typedef ALTINT(myaltint2, uint32_t) my_uint32_alt_t;
 * >> ALTINT_COMPAT(my_uint32_t, my_uint32_alt_t)
 */
#include "__altint.h"
#define ALTINT         __HYBRID_ALTINT
#define ALTINT_UID     __HYBRID_ALTINT_UID
#define ALTINT_COMPAT  __HYBRID_ALTINT_COMPAT
#define ALTINT_TYPEDEF __HYBRID_ALTINT_TYPEDEF

#endif /* !__GUARD_HYBRID_ALTINT_H */
