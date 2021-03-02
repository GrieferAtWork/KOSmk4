/* HASH CRC-32:0x804b177f */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/search.h) */
/* (#) Portability: DJGPP         (/include/search.h) */
/* (#) Portability: FreeBSD       (/include/search.h) */
/* (#) Portability: GNU C Library (/misc/search.h) */
/* (#) Portability: MSVC          (/include/search.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/search.h) */
/* (#) Portability: NetBSD        (/include/search.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/search.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/search.h) */
/* (#) Portability: diet libc     (/include/search.h) */
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
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
	FIND  = 0,
	ENTER = 1
} ACTION;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FIND  FIND
#define ENTER ENTER
#else /* __COMPILER_PREFERR_ENUMS */
#define FIND  0
#define ENTER 1
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* For tsearch */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
	preorder  = 0,
	postorder = 1,
	endorder  = 2,
	leaf      = 3
} VISIT;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define preorder  preorder
#define postorder postorder
#define endorder  endorder
#define leaf      leaf
#else /* __COMPILER_PREFERR_ENUMS */
#define preorder  0
#define postorder 1
#define endorder  2
#define leaf      3
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
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
/* Insert ELEM into a doubly-linked list, after PREV */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,insque,(void *__restrict __elem, void *__prev),(__elem,__prev))
#else /* __CRT_HAVE_insque */
#include <libc/local/search/insque.h>
/* Insert ELEM into a doubly-linked list, after PREV */
__NAMESPACE_LOCAL_USING_OR_IMPL(insque, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL insque)(void *__restrict __elem, void *__prev) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(insque))(__elem, __prev); })
#endif /* !__CRT_HAVE_insque */
#ifdef __CRT_HAVE_remque
/* Unlink ELEM from the doubly-linked list that it is in */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,remque,(void *__restrict __elem),(__elem))
#else /* __CRT_HAVE_remque */
#include <libc/local/search/remque.h>
/* Unlink ELEM from the doubly-linked list that it is in */
__NAMESPACE_LOCAL_USING_OR_IMPL(remque, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL remque)(void *__restrict __elem) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remque))(__elem); })
#endif /* !__CRT_HAVE_remque */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
/* For use with hsearch(3).  */
#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef __ENTRY_defined
#define __ENTRY_defined 1
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
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
__CDECLARE(,ENTRY *,__NOTHROW_NCX,hsearch,(ENTRY __item, ACTION __action),(__item,__action))
#else /* __CRT_HAVE_hsearch */
#include <libc/local/search/hsearch.h>
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
__NAMESPACE_LOCAL_USING_OR_IMPL(hsearch, __FORCELOCAL __ATTR_ARTIFICIAL ENTRY *__NOTHROW_NCX(__LIBCCALL hsearch)(ENTRY __item, ACTION __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hsearch))(__item, __action); })
#endif /* !__CRT_HAVE_hsearch */
#ifdef __CRT_HAVE_hcreate
/* Create a new hashing table which will at most contain NEL elements */
__CDECLARE(,int,__NOTHROW_NCX,hcreate,(size_t __nel),(__nel))
#elif defined(__CRT_HAVE_hcreate_r) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/hcreate.h>
/* Create a new hashing table which will at most contain NEL elements */
__NAMESPACE_LOCAL_USING_OR_IMPL(hcreate, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL hcreate)(size_t __nel) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hcreate))(__nel); })
#endif /* ... */
#ifdef __CRT_HAVE_hdestroy
/* Destroy current internal hashing table */
__CDECLARE_VOID(,__NOTHROW_NCX,hdestroy,(void),())
#elif defined(__CRT_HAVE_hdestroy_r) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <libc/local/search/hdestroy.h>
/* Destroy current internal hashing table */
__NAMESPACE_LOCAL_USING_OR_IMPL(hdestroy, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL hdestroy)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hdestroy))(); })
#endif /* ... */
#ifdef __USE_GNU
/* Data type for reentrant functions.  */
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int   size;
	unsigned int   filled;
};
#endif /* !__hsearch_data_defined */
#ifdef __CRT_HAVE_hsearch_r
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CDECLARE(__ATTR_NONNULL((3, 4)),int,__NOTHROW_NCX,hsearch_r,(ENTRY __item, ACTION __action, ENTRY **__retval, struct hsearch_data *__htab),(__item,__action,__retval,__htab))
#else /* __CRT_HAVE_hsearch_r */
#include <libc/local/search/hsearch_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
__NAMESPACE_LOCAL_USING_OR_IMPL(hsearch_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4)) int __NOTHROW_NCX(__LIBCCALL hsearch_r)(ENTRY __item, ACTION __action, ENTRY **__retval, struct hsearch_data *__htab) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hsearch_r))(__item, __action, __retval, __htab); })
#endif /* !__CRT_HAVE_hsearch_r */
#ifdef __CRT_HAVE_hcreate_r
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CDECLARE(,int,__NOTHROW_NCX,hcreate_r,(size_t __nel, struct hsearch_data *__htab),(__nel,__htab))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/hcreate_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
__NAMESPACE_LOCAL_USING_OR_IMPL(hcreate_r, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL hcreate_r)(size_t __nel, struct hsearch_data *__htab) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hcreate_r))(__nel, __htab); })
#endif /* ... */
#ifdef __CRT_HAVE_hdestroy_r
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CDECLARE_VOID(,__NOTHROW_NCX,hdestroy_r,(struct hsearch_data *__htab),(__htab))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <libc/local/search/hdestroy_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
__NAMESPACE_LOCAL_USING_OR_IMPL(hdestroy_r, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL hdestroy_r)(struct hsearch_data *__htab) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hdestroy_r))(__htab); })
#endif /* ... */
#endif /* __USE_GNU */
/* The tsearch routines are very interesting. They make  many
 * assumptions about the compiler. It assumes that the  first
 * field in node must be the "key" field, which points to the
 * datum. Everything depends on that. */
#ifdef __CRT_HAVE_tsearch
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
__CDECLARE(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tsearch,(void const *__key, void **__vrootp, __compar_fn_t __compar),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tsearch)
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
__CREDIRECT(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tsearch,(void const *__key, void **__vrootp, __compar_fn_t __compar),__tsearch,(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/search/tsearch.h>
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
__NAMESPACE_LOCAL_USING_OR_IMPL(tsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) void *__NOTHROW_NCX(__LIBCCALL tsearch)(void const *__key, void **__vrootp, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tsearch))(__key, __vrootp, __compar); })
#endif /* ... */
#ifdef __CRT_HAVE_tfind
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
__CDECLARE(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tfind,(void const *__key, void *const *__vrootp, __compar_fn_t __compar),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tfind)
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
__CREDIRECT(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tfind,(void const *__key, void *const *__vrootp, __compar_fn_t __compar),__tfind,(__key,__vrootp,__compar))
#else /* ... */
#include <libc/local/search/tfind.h>
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
__NAMESPACE_LOCAL_USING_OR_IMPL(tfind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) void *__NOTHROW_NCX(__LIBCCALL tfind)(void const *__key, void *const *__vrootp, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tfind))(__key, __vrootp, __compar); })
#endif /* !... */
#ifdef __CRT_HAVE_tdelete
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
__CDECLARE(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tdelete,(void const *__restrict __key, void **__restrict __vrootp, __compar_fn_t __compar),(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE___tdelete)
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
__CREDIRECT(__ATTR_NONNULL((3)),void *,__NOTHROW_NCX,tdelete,(void const *__restrict __key, void **__restrict __vrootp, __compar_fn_t __compar),__tdelete,(__key,__vrootp,__compar))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <libc/local/search/tdelete.h>
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdelete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) void *__NOTHROW_NCX(__LIBCCALL tdelete)(void const *__restrict __key, void **__restrict __vrootp, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdelete))(__key, __vrootp, __compar); })
#endif /* ... */
#ifndef __ACTION_FN_T
#define __ACTION_FN_T 1
typedef void (__LIBKCALL *__action_fn_t)(void const *nodep, VISIT value, int level);
#endif /* !__ACTION_FN_T */
#ifdef __CRT_HAVE_twalk
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__CDECLARE_VOID(,__NOTHROW_NCX,twalk,(void const *__root, __action_fn_t __action),(__root,__action))
#elif defined(__CRT_HAVE___twalk)
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__CREDIRECT_VOID(,__NOTHROW_NCX,twalk,(void const *__root, __action_fn_t __action),__twalk,(__root,__action))
#else /* ... */
#include <libc/local/search/twalk.h>
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(twalk, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL twalk)(void const *__root, __action_fn_t __action) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(twalk))(__root, __action); })
#endif /* !... */
#ifdef __USE_GNU
/* Callback type for function to free a tree node.
 * If the keys are atomic data this function should do nothing. */
#ifndef ____free_fn_t_defined
#define ____free_fn_t_defined 1
typedef void (__LIBKCALL *__free_fn_t)(void *__nodep);
#endif /* !____free_fn_t_defined */
#ifdef __CRT_HAVE_tdestroy
/* Destroy the whole tree, call FREEFCT for each node or leaf */
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,tdestroy,(void *__root, __free_fn_t __freefct),(__root,__freefct))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <libc/local/search/tdestroy.h>
/* Destroy the whole tree, call FREEFCT for each node or leaf */
__NAMESPACE_LOCAL_USING_OR_IMPL(tdestroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void __NOTHROW_NCX(__LIBCCALL tdestroy)(void *__root, __free_fn_t __freefct) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tdestroy))(__root, __freefct); })
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_lfind
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__CREDIRECT(__ATTR_NONNULL((2, 3, 5)),void *,__NOTHROW_NCX,lfind,(void const *__key, void *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar),lfind,(__key,__base,__nmemb,__size,__compar))
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__CREDIRECT(__ATTR_NONNULL((2, 3, 5)),void const *,__NOTHROW_NCX,lfind,(void const *__key, void const *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar),lfind,(__key,__base,__nmemb,__size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__CDECLARE(__ATTR_NONNULL((2, 3, 5)),void *,__NOTHROW_NCX,lfind,(void const *__key, void const *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar),(__key,__base,__nmemb,__size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#else /* __CRT_HAVE_lfind */
#include <libc/local/search/lfind.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_SEARCH_H_PROTO)
extern "C++" {
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 5)) void *__NOTHROW_NCX(__LIBCCALL lfind)(void const *__key, void *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __base, __nmemb, __size, __compar); }
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 5)) void const *__NOTHROW_NCX(__LIBCCALL lfind)(void const *__key, void const *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __base, __nmemb, __size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_SEARCH_H_PROTO */
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lfind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 5)) void *__NOTHROW_NCX(__LIBCCALL lfind)(void const *__key, void const *__base, size_t __KOS_FIXED_CONST *__nmemb, size_t __size, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))(__key, __base, __nmemb, __size, __compar); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_SEARCH_H_PROTO */
#endif /* !__CRT_HAVE_lfind */
#ifdef __CRT_HAVE_lsearch
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
__CDECLARE(__ATTR_NONNULL((2, 3, 5)),void *,__NOTHROW_NCX,lsearch,(void const *__key, void *__base, size_t *__nmemb, size_t __size, __compar_fn_t __compar),(__key,__base,__nmemb,__size,__compar))
#else /* __CRT_HAVE_lsearch */
#include <libc/local/search/lsearch.h>
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
__NAMESPACE_LOCAL_USING_OR_IMPL(lsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 5)) void *__NOTHROW_NCX(__LIBCCALL lsearch)(void const *__key, void *__base, size_t *__nmemb, size_t __size, __compar_fn_t __compar) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lsearch))(__key, __base, __nmemb, __size, __compar); })
#endif /* !__CRT_HAVE_lsearch */

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
