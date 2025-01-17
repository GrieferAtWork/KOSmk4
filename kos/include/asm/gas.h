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
#ifndef _ASM_GAS_H
#define _ASM_GAS_H 1

#include <__stdinc.h>

/* Implemented as of 2022-08-13T19:16
 *
 * >> .ifc_startswith "foobar", "foo"           -- String starts-with
 * >> .ifc_endswith   "foobar", "bar"           -- String ends-with
 * >> .ifc_contains   "foobar", "oob"           -- String contains
 * >> .ifc_skipspace  "[ a ,b ,c ]", "[a,b,c]"  -- Compare, but skip over space characters
 * >> .ifc_bcontains  "r1,r10,r101", "r1"       -- word-Boundary contains-check
 * >> .ifc_i          "FOO", "foo"              -- Case-insensitive
 */
#if defined(__KOS__) && defined(__GCC_VERSION_NUM) && (__GCC_VERSION_NUM >= 120100)
#define __GAS_HAVE_IFC_ACCEPTS_STRINGS /* `.ifc "a,b", "c,d"' */
#define __GAS_HAVE_IFC_STARTSWITH      /* `.ifc_startswith', `.ifnc_startswith' */
#define __GAS_HAVE_IFC_ENDSWITH        /* `.ifc_endswith', `.ifnc_endswith' */
#define __GAS_HAVE_IFC_CONTAINS        /* `.ifc_contains', `.ifnc_contains' */
#define __GAS_HAVE_IFC_SKIPSPACE       /* `.ifc_skipspace', `.ifnc_skipspace' */
#define __GAS_HAVE_IFC_BCONTAINS       /* `.ifc_bcontains', `.ifnc_bcontains' */
#define __GAS_HAVE_IFC_I               /* `.ifc_i', `.ifnc_i' */
#define __GAS_HAVE_IFC_ISTARTSWITH     /* `.ifc_istartswith', `.ifnc_istartswith' */
#define __GAS_HAVE_IFC_IENDSWITH       /* `.ifc_iendswith', `.ifnc_iendswith' */
#define __GAS_HAVE_IFC_ICONTAINS       /* `.ifc_icontains', `.ifnc_icontains' */
#define __GAS_HAVE_IFC_ISKIPSPACE      /* `.ifc_iskipspace', `.ifnc_iskipspace' */
#define __GAS_HAVE_IFC_IBCONTAINS      /* `.ifc_ibcontains', `.ifnc_ibcontains' */
#endif /* __KOS__ && GCC >= 12.1.0 */

/* GAS/LD (though mostly LD)  produce corrupted CFI data  if
 * you try to use `.cfi_*' directives in comdat text section */
#define __GAS_HAVE_BROKEN_CFI_IN_COMDAT

#endif /* !_ASM_GAS_H */
