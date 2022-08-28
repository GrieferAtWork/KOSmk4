/* HASH CRC-32:0x25ea8911 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/search.h) */
/* (#) Portability: DJGPP         (/include/search.h) */
/* (#) Portability: DragonFly BSD (/include/search.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/search.h) */
/* (#) Portability: FreeBSD       (/include/search.h) */
/* (#) Portability: GNU C Library (/misc/search.h) */
/* (#) Portability: MSVC          (/include/search.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/search.h) */
/* (#) Portability: NetBSD        (/include/search.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/search.h) */
/* (#) Portability: OpenBSD       (/include/search.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/search.h) */
/* (#) Portability: Windows Kits  (/ucrt/search.h) */
/* (#) Portability: diet libc     (/include/search.h) */
/* (#) Portability: libc4/5       (/include/search.h) */
/* (#) Portability: libc6         (/include/search.h) */
/* (#) Portability: mintlib       (/include/search.h) */
/* (#) Portability: musl libc     (/include/search.h) */
/* (#) Portability: uClibc        (/include/search.h) */
#ifndef _SEARCH_H
#define _SEARCH_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>

/* Documentation taken from Glibc /usr/include/search.h */
/* Declarations for System V style searching functions.
   Copyright (C) 1995-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Separately, the implementation is also derived from Glibc */
/* Copyright (C) 1993-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1993.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("preorder")
#pragma push_macro("postorder")
#pragma push_macro("endorder")
#pragma push_macro("leaf")
#pragma push_macro("VISIT")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef preorder
#undef postorder
#undef endorder
#undef leaf
#undef VISIT

/* Action which shall be performed in the call the hsearch. */
#ifndef __ACTION_defined
#define __ACTION_defined
typedef enum {
	FIND  = 0,
	ENTER = 1
} ACTION;
#endif /* !__ACTION_defined */

/* For tsearch */
#ifndef __VISIT_defined
#define __VISIT_defined
typedef enum {
	preorder  = 0,
	postorder = 1,
	endorder  = 2,
	leaf      = 3
} VISIT;
#endif /* !__VISIT_defined */


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __USE_GNU
/* Prototype structure for a linked-list data structure. This
 * is the type used by  the `insque' and `remque'  functions. */
struct qelem {
	struct qelem *q_forw;     /* [0..1] Forward link */
	struct qelem *q_back;     /* [0..1] Backward link */
	char          q_data[1];  /* Element data */
};
#endif /* __USE_GNU */

#ifdef __CRT_HAVE_insque
/* >> insque(3)
 * Insert ELEM into a doubly-linked list, after PREV */
__CDECLARE_VOID(,__NOTHROW_NCX,insque,(void *__restrict __elem, void *__prev),(__elem,__prev))
#else /* __CRT_HAVE_insque */
#include <libc/local/search/insque.h>
/* >> insque(3)
 * Insert ELEM into a doubly-linked list, after PREV */
__NAMESPACE_LOCAL_USING_OR_IMPL(insque, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL insque)(void *__restrict __elem, void *__prev) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(insque))(__elem, __prev); })
#endif /* !__CRT_HAVE_insque */
#ifdef __CRT_HAVE_remque
/* >> remque(3)
 * Unlink ELEM from the doubly-linked list that it is in */
__CDECLARE_VOID(,__NOTHROW_NCX,remque,(void *__restrict __elem),(__elem))
#else /* __CRT_HAVE_remque */
#include <libc/local/search/remque.h>
/* >> remque(3)
 * Unlink ELEM from the doubly-linked list that it is in */
__NAMESPACE_LOCAL_USING_OR_IMPL(remque, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL remque)(void *__restrict __elem) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remque))(__elem); })
#endif /* !__CRT_HAVE_remque */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
/* For use with hsearch(3).  */
#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef __ENTRY_defined
#define __ENTRY_defined
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */

/* Opaque type for internal use. */
struct _ENTRY;

/* Family of hash table  handling functions. The functions  also
 * have reentrant counterparts ending with _r. The non-reentrant
 * functions all work on a signle internal hashing table. */

#ifdef __CRT_HAVE_hsearch
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If  `action'  is  `ENTER' replace  existing  data (if  any)  with `item.data' */
__CDECLARE(,ENTRY *,__NOTHROW_NCX,hsearch,(ENTRY __item, ACTION __action),(__item,__action))
#else /* __CRT_HAVE_hsearch */
#include <libc/local/search/hsearch.h>
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If  `action'  is  `ENTER' replace  existing  data (if  any)  with `item.data' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hsearch, __FORCELOCAL __ATTR_ARTIFICIAL ENTRY *__NOTHROW_NCX(__LIBCCALL hsearch)(ENTRY __item, ACTION __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hsearch))(__item, __action); })
#endif /* !__CRT_HAVE_hsearch */
#ifdef __CRT_HAVE_hcreate
/* >> hcreate(3)
 * Create a new hashing table which will at most contain `nel' elements */
__CDECLARE(,int,__NOTHROW_NCX,hcreate,(size_t __nel),(__nel))
#elif defined(__CRT_HAVE_hcreate_r) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/hcreate.h>
/* >> hcreate(3)
 * Create a new hashing table which will at most contain `nel' elements */
__NAMESPACE_LOCAL_USING_OR_IMPL(hcreate, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL hcreate)(size_t __nel) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hcreate))(__nel); })
#endif /* ... */
#ifdef __CRT_HAVE_hdestroy
/* >> hdestroy(3)
 * Destroy current internal hashing table */
__CDECLARE_VOID(,__NOTHROW_NCX,hdestroy,(void),())
#else /* __CRT_HAVE_hdestroy */
#include <libc/local/search/hdestroy.h>
/* >> hdestroy(3)
 * Destroy current internal hashing table */
__NAMESPACE_LOCAL_USING_OR_IMPL(hdestroy, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL hdestroy)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hdestroy))(); })
#endif /* !__CRT_HAVE_hdestroy */
#ifdef __USE_GNU
/* Data type for reentrant functions.  */
#ifndef __hsearch_data_defined
#define __hsearch_data_defined
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int   size;
	unsigned int   filled;
};
#endif /* !__hsearch_data_defined */
#ifdef __CRT_HAVE_hsearch_r
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
__CDECLARE(__ATTR_INOUT(4) __ATTR_OUT(3),int,__NOTHROW_NCX,hsearch_r,(ENTRY __item, ACTION __action, ENTRY **__retval, struct hsearch_data *__htab),(__item,__action,__retval,__htab))
#else /* __CRT_HAVE_hsearch_r */
#include <libc/local/search/hsearch_r.h>
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
__NAMESPACE_LOCAL_USING_OR_IMPL(hsearch_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(4) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL hsearch_r)(ENTRY __item, ACTION __action, ENTRY **__retval, struct hsearch_data *__htab) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hsearch_r))(__item, __action, __retval, __htab); })
#endif /* !__CRT_HAVE_hsearch_r */
#ifdef __CRT_HAVE_hcreate_r
/* >> hcreate_r(3) */
__CDECLARE(,int,__NOTHROW_NCX,hcreate_r,(size_t __nel, struct hsearch_data *__htab),(__nel,__htab))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/hcreate_r.h>
/* >> hcreate_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(hcreate_r, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL hcreate_r)(size_t __nel, struct hsearch_data *__htab) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hcreate_r))(__nel, __htab); })
#endif /* ... */
#ifdef __CRT_HAVE_hdestroy_r
/* >> hdestroy_r(3) */
__CDECLARE_VOID(,__NOTHROW_NCX,hdestroy_r,(struct hsearch_data *__htab),(__htab))
#else /* __CRT_HAVE_hdestroy_r */
#include <libc/local/search/hdestroy_r.h>
/* >> hdestroy_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(hdestroy_r, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL hdestroy_r)(struct hsearch_data *__htab) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hdestroy_r))(__htab); })
#endif /* !__CRT_HAVE_hdestroy_r */
#endif /* __USE_GNU */
/* The tsearch routines are very interesting. They make  many
 * assumptions about the compiler. It assumes that the  first
 * field in node must be the "key" field, which points to the
 * datum. Everything depends on that. */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_tsearch_r
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tsearch_r,(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),(__key,__vrootp,__compar,__arg))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/tsearch_r.h>
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
__NAMESPACE_LOCAL_USING_OR_IMPL(tsearch_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *(__LIBCCALL tsearch_r)(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tsearch_r))(__key, __vrootp, __compar, __arg); })
#endif /* ... */
#ifdef __CRT_HAVE_tfind_r
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)),void *,__THROWING,tfind_r,(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),(__key,__vrootp,__compar,__arg))
#else /* __CRT_HAVE_tfind_r */
#include <libc/local/search/tfind_r.h>
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tfind_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)) void *(__LIBCCALL tfind_r)(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tfind_r))(__key, __vrootp, __compar, __arg); })
#endif /* !__CRT_HAVE_tfind_r */
#ifdef __CRT_HAVE_tdelete_r
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tdelete_r,(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),(__key,__vrootp,__compar,__arg))
#else /* __CRT_HAVE_tdelete_r */
#include <libc/local/search/tdelete_r.h>
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdelete_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *(__LIBCCALL tdelete_r)(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdelete_r))(__key, __vrootp, __compar, __arg); })
#endif /* !__CRT_HAVE_tdelete_r */
#ifdef __CRT_HAVE_twalk_r
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
__CDECLARE_VOID(__ATTR_IN_OPT(1),__THROWING,twalk_r,(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg), void *__arg),(__root,__action,__arg))
#else /* __CRT_HAVE_twalk_r */
#include <libc/local/search/twalk_r.h>
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(twalk_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) void (__LIBCCALL twalk_r)(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg), void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(twalk_r))(__root, __action, __arg); })
#endif /* !__CRT_HAVE_twalk_r */
#ifdef __CRT_HAVE_tdestroy_r
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
__CDECLARE_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((2)),__THROWING,tdestroy_r,(void *__root, void (__LIBCCALL *__freefct)(void *__nodep, void *__arg), void *__arg),(__root,__freefct,__arg))
#else /* __CRT_HAVE_tdestroy_r */
#include <libc/local/search/tdestroy_r.h>
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdestroy_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_NONNULL((2)) void (__LIBCCALL tdestroy_r)(void *__root, void (__LIBCCALL *__freefct)(void *__nodep, void *__arg), void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdestroy_r))(__root, __freefct, __arg); })
#endif /* !__CRT_HAVE_tdestroy_r */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_tsearch
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tsearch,(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tsearch)
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tsearch,(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),__tsearch,(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE_tsearch_r) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/tsearch.h>
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
__NAMESPACE_LOCAL_USING_OR_IMPL(tsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *(__LIBCCALL tsearch)(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tsearch))(__key, __vrootp, __compar); })
#endif /* ... */
#ifdef __CRT_HAVE_tfind
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)),void *,__THROWING,tfind,(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tfind)
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)),void *,__THROWING,tfind,(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),__tfind,(__key,__vrootp,__compar))
#else /* ... */
#include <libc/local/search/tfind.h>
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tfind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)) void *(__LIBCCALL tfind)(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tfind))(__key, __vrootp, __compar); })
#endif /* !... */
#ifdef __CRT_HAVE_tdelete
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tdelete,(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tdelete)
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__THROWING,tdelete,(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),__tdelete,(__key,__vrootp,__compar))
#else /* ... */
#include <libc/local/search/tdelete.h>
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdelete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *(__LIBCCALL tdelete)(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdelete))(__key, __vrootp, __compar); })
#endif /* !... */
#ifndef __ACTION_FN_T
#define __ACTION_FN_T 1
typedef void (__LIBCCALL *__action_fn_t)(void const *nodep, VISIT value, int level);
#endif /* !__ACTION_FN_T */
#ifdef __CRT_HAVE_twalk
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
__CDECLARE_VOID(__ATTR_IN_OPT(1),__THROWING,twalk,(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level)),(__root,__action))
#elif defined(__CRT_HAVE___twalk)
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
__CREDIRECT_VOID(__ATTR_IN_OPT(1),__THROWING,twalk,(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level)),__twalk,(__root,__action))
#else /* ... */
#include <libc/local/search/twalk.h>
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(twalk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) void (__LIBCCALL twalk)(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level)) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(twalk))(__root, __action); })
#endif /* !... */
#ifdef __USE_GNU
/* Callback type for function to free a tree node.
 * If the keys are atomic data this function should do nothing. */
#ifndef ____free_fn_t_defined
#define ____free_fn_t_defined
typedef void (__LIBCCALL *__free_fn_t)(void *__nodep);
#endif /* !____free_fn_t_defined */
#ifdef __CRT_HAVE_tdestroy
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
__CDECLARE_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((2)),__THROWING,tdestroy,(void *__root, void (__LIBCCALL *__freefct)(void *__nodep)),(__root,__freefct))
#else /* __CRT_HAVE_tdestroy */
#include <libc/local/search/tdestroy.h>
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdestroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_NONNULL((2)) void (__LIBCCALL tdestroy)(void *__root, void (__LIBCCALL *__freefct)(void *__nodep)) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdestroy))(__root, __freefct); })
#endif /* !__CRT_HAVE_tdestroy */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_lfind
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,lfind,(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__pbase,__pitem_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#elif defined(__CRT_HAVE__lfind)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,lfind,(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#else /* ... */
#include <libc/local/search/lfind.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL lfind)(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); }
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void const *(__LIBCCALL lfind)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lfind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL lfind)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_lsearch
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)),void *,__THROWING,lsearch,(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__pbase,__pitem_count,__item_size,__compar))
#elif defined(__CRT_HAVE__lsearch)
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)),void *,__THROWING,lsearch,(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lsearch,(__key,__pbase,__pitem_count,__item_size,__compar))
#else /* ... */
#include <libc/local/search/lsearch.h>
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__NAMESPACE_LOCAL_USING_OR_IMPL(lsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)) void *(__LIBCCALL lsearch)(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lsearch))(__key, __pbase, __pitem_count, __item_size, __compar); })
#endif /* !... */

#ifdef __USE_DOS
typedef int (__LIBCCALL *_CoreCrtSecureSearchSortCompareFunction)(void *__arg, void const *__a, void const *__b);
typedef __compar_fn_t _CoreCrtMgdNonSecureSearchSortCompareFunction;
#ifdef __CRT_HAVE_lfind
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind,(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,_lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#elif defined(__CRT_HAVE__lfind)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind,(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,_lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__pbase,__pitem_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#else /* ... */
#include <libc/local/search/lfind.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL _lfind)(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); }
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void const *(__LIBCCALL _lfind)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL _lfind)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __pbase, __pitem_count, __item_size, __compar); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_lsearch
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)),void *,__THROWING,_lsearch,(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lsearch,(__key,__pbase,__pitem_count,__item_size,__compar))
#elif defined(__CRT_HAVE__lsearch)
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)),void *,__THROWING,_lsearch,(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__key,__pbase,__pitem_count,__item_size,__compar))
#else /* ... */
#include <libc/local/search/lsearch.h>
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)) void *(__LIBCCALL _lsearch)(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lsearch))(__key, __pbase, __pitem_count, __item_size, __compar); }
#endif /* !... */
#ifndef __qsort_defined
#define __qsort_defined
#ifdef __std_qsort_defined
__NAMESPACE_STD_USING(qsort)
#elif defined(__CRT_HAVE_qsort)
__CDECLARE_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__THROWING,qsort,(void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* ... */
#include <libc/local/stdlib/qsort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)) void (__LIBCCALL qsort)(void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !... */
#endif /* !__qsort_defined */
#ifndef __bsearch_defined
#define __bsearch_defined
#ifdef __std_bsearch_defined
__NAMESPACE_STD_USING(bsearch)
#elif defined(__CRT_HAVE_bsearch)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,bsearch,(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),bsearch,(__pkey,__pbase,__item_count,__item_size,__compar))
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),bsearch,(__pkey,__pbase,__item_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pkey,__pbase,__item_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#else /* ... */
#include <libc/local/stdlib/bsearch.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL bsearch)(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void const *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* !... */
#endif /* !__bsearch_defined */
#ifdef __CRT_HAVE__lfind_s
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind_s,(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),_lfind_s,(__key,__pbase,__pitem_count,__item_size,__compar,__arg))
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void const *,__THROWING,_lfind_s,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),_lfind_s,(__key,__pbase,__pitem_count,__item_size,__compar,__arg))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,_lfind_s,(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__key,__pbase,__pitem_count,__item_size,__compar,__arg))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#else /* __CRT_HAVE__lfind_s */
#include <libc/local/search/_lfind_s.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL _lfind_s)(void const *__key, void *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lfind_s))(__key, __pbase, __pitem_count, __item_size, __compar, __arg); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void const *(__LIBCCALL _lfind_s)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lfind_s))(__key, __pbase, __pitem_count, __item_size, __compar, __arg); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(_lfind_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL _lfind_s)(void const *__key, void const *__pbase, size_t __KOS_FIXED_CONST *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lfind_s))(__key, __pbase, __pitem_count, __item_size, __compar, __arg); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#endif /* !__CRT_HAVE__lfind_s */
#ifdef __CRT_HAVE__lsearch_s
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)),void *,__THROWING,_lsearch_s,(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__key,__pbase,__pitem_count,__item_size,__compar,__arg))
#else /* __CRT_HAVE__lsearch_s */
#include <libc/local/search/_lsearch_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lsearch_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)) void *(__LIBCCALL _lsearch_s)(void const *__key, void *__pbase, size_t *__pitem_count, size_t __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lsearch_s))(__key, __pbase, __pitem_count, __item_size, __compar, __arg); })
#endif /* !__CRT_HAVE__lsearch_s */
#ifdef __USE_DOS_SLIB
#ifndef __qsort_s_defined
#define __qsort_s_defined
#ifdef __CRT_HAVE_qsort_s
__CDECLARE_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__THROWING,qsort_s,(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_qsort_s */
#include <libc/local/stdlib/qsort_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)) void (__LIBCCALL qsort_s)(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_s))(__base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_qsort_s */
#endif /* !__qsort_s_defined */
#ifndef __bsearch_s_defined
#define __bsearch_s_defined
#ifdef __CRT_HAVE_bsearch_s
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,bsearch_s,(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__key,__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_bsearch_s */
#include <libc/local/stdlib/bsearch_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *(__LIBCCALL bsearch_s)(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_s))(__key, __base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_bsearch_s */
#endif /* !__bsearch_s_defined */
#endif /* __USE_DOS_SLIB */
#endif /* __USE_DOS */

#endif /* __CC__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("VISIT")
#pragma pop_macro("leaf")
#pragma pop_macro("endorder")
#pragma pop_macro("postorder")
#pragma pop_macro("preorder")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END

#endif /* !_SEARCH_H */
