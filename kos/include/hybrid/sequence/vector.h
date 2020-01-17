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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SEQUENCE_VECTOR_H
#define __GUARD_HYBRID_SEQUENCE_VECTOR_H 1

#include "../../__stdinc.h"
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#include "../typecore.h"
#include "../pp/__bubble.h"
#include "../pp/__va_nargs.h"
#include <stddef.h>

#ifdef __CC__

__DECL_BEGIN


/* Vector functions:
 *    (X)(malloc)(realloc)(free)
 *    (X)(malloc)(realloc)(free)(malloc_usable_size)
 *    (X)(malloc)(try_malloc)(realloc)(try_realloc)(free)
 *    (X)(malloc)(try_malloc)(realloc)(try_realloc)(free)(malloc_usable_size)
 *    The `malloc_usable_size' function is optional!
 *   int X;
 *     - Either 0 or 1.
 *       - When `0', behave like a regular malloc
 *       - When `1', malloc() and realloc() never return `NULL'
 *   void *malloc(size_t num_bytes);
 *   void *try_malloc(size_t num_bytes);             // Doesn't throw an error in X=1-mode / always returns normally
 *   void *realloc(void *ptr, size_t num_bytes);
 *   void *try_realloc(void *ptr, size_t num_bytes); // Doesn't throw an error in X=1-mode / always returns normally
 *   void free(void *ptr);
 *   size_t malloc_usable_size(void *ptr);           // Must return 0 when `ptr' is `NULL'
 * Examples:
 *   DEEMON: (1)(Dee_Malloc)(Dee_TryMalloc)(Dee_Realloc)(Dee_TryRealloc)(Dee_Free)
 *   KOS:    (1)(Xmalloc)(malloc)(Xrealloc)(realloc)(free)
 *   STD-C:  (0)(malloc)(realloc)(free)
 *   GNU-C:  (0)(malloc)(realloc)(free)(malloc_usable_size)  // If you want to use heap-allocation buffers
 */
#ifndef STDLIB_FUNCTIONS
#define STDLIB_FUNCTIONS    (0)(malloc)(realloc)(free)
#endif
#ifndef VECTOR_FUNCTIONS
#define VECTOR_FUNCTIONS    STDLIB_FUNCTIONS
#endif


#define __HYBRID_SEQ_VECTOR_SELECT3(m,x)  m##x
#define __HYBRID_SEQ_VECTOR_SELECT2(m,x)  __HYBRID_SEQ_VECTOR_SELECT3(m,x)
#define __HYBRID_SEQ_VECTOR_SELECT(m,f)   __HYBRID_SEQ_VECTOR_SELECT2(m,__HYBRID_PP_BUBBLE_SIZE(f))
#define __HYBRID_SEQ_VECTOR_XSELECT3(m,x) m##x
#define __HYBRID_SEQ_VECTOR_XSELECT2(m,x) __HYBRID_SEQ_VECTOR_XSELECT3(m,x)
#define __HYBRID_SEQ_VECTOR_XSELECT(m,f)  __HYBRID_SEQ_VECTOR_XSELECT2(m,__HYBRID_PP_BUBBLE_GET(f,0))


/* >> VECTOR(TYPE T, FUNCTIONS f = VECTOR_FUNCTIONS) --> struct { ... } */
#define VECTOR(...) __PP_CAT2(__HYBRID_SEQ_VECTOR,__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#define __HYBRID_SEQ_VECTOR1(T)    __HYBRID_SEQ_VECTOR2(T,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR2(T,f)  __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_IMPL,f)(T,f)
#define __HYBRID_SEQ_VECTOR_IMPL4(T,f)  __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_IMPL4_,f)(T,f)
#define __HYBRID_SEQ_VECTOR_IMPL4_0     __HYBRID_SEQ_VECTOR_IMPL6
#define __HYBRID_SEQ_VECTOR_IMPL4_1     __HYBRID_SEQ_VECTOR_IMPL7
#define __HYBRID_SEQ_VECTOR_IMPL5       __HYBRID_SEQ_VECTOR_IMPL7
#define __HYBRID_SEQ_VECTOR_IMPL6(T,f)  \
        struct { __SIZE_TYPE__ v_size;  /* Used number of items. */ \
                 __SIZE_TYPE__ v_alloc; /* [>= v_size] Allocated number of items. */ \
                 T            *v_elem;  /* [0..v_size|ALLOC(v_alloc)][owned] Vector elements. */ }
#define __HYBRID_SEQ_VECTOR_IMPL7(T,f)  \
        struct { __SIZE_TYPE__ v_size;  /* Used number of items. */ \
                 T            *v_elem;  /* [0..v_size][owned] Vector elements. */ }


/* >> VECTOR_INIT                --> { ... }
 * >> VECTOR_INIT_F(FUNCTIONS f) --> { ... }
 * Vector initializers. */
#define VECTOR_INIT      VECTOR_INIT_F(VECTOR_FUNCTIONS)
#define VECTOR_INIT_F(f)                     __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_INIT_IMPL,f)(f)
#define __HYBRID_SEQ_VECTOR_INIT_IMPL4(f)    __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_INIT_IMPL4_,f)(f)
#define __HYBRID_SEQ_VECTOR_INIT_IMPL4_0     __HYBRID_SEQ_VECTOR_INIT_IMPL6
#define __HYBRID_SEQ_VECTOR_INIT_IMPL4_1     __HYBRID_SEQ_VECTOR_INIT_IMPL7
#define __HYBRID_SEQ_VECTOR_INIT_IMPL5       __HYBRID_SEQ_VECTOR_INIT_IMPL7
#define __HYBRID_SEQ_VECTOR_INIT_IMPL6(f)    { 0, 0, NULL }
#define __HYBRID_SEQ_VECTOR_INIT_IMPL7(f)    { 0, NULL }

/* >> void VECTOR_FINI(VECTOR l, FUNCTIONS f = VECTOR_FUNCTIONS);
 * >> void VECTOR_FINI_F(VECTOR l, void fini_elem(T *__restrict elem), FUNCTIONS f = VECTOR_FUNCTIONS);
 * >> void VECTOR_FINI_P(VECTOR l, TYPE T, (elem)(expr) fini_elem, FUNCTIONS f = VECTOR_FUNCTIONS);
 * Finalize a given vector, optionally executing a given predicate/callback on each element. */
#define VECTOR_FINI(...)    __HYBRID_SEQ_VECTOR_FINI((__VA_ARGS__))
#define VECTOR_FINI_F(...)  __HYBRID_SEQ_VECTOR_FINI_F((__VA_ARGS__))
#define VECTOR_FINI_P(...)  __HYBRID_SEQ_VECTOR_FINI_P((__VA_ARGS__))
#define __HYBRID_SEQ_VECTOR_FINI(args)    __PP_CAT2(__HYBRID_SEQ_VECTOR_FINI_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_FINI_F(args)  __PP_CAT2(__HYBRID_SEQ_VECTOR_FINI_F_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_FINI_P(args)  __PP_CAT2(__HYBRID_SEQ_VECTOR_FINI_P_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_FINI_IMPL1(l)     __HYBRID_SEQ_VECTOR_FINI_IMPL2(l,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_FINI_IMPL2(l,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_FINI_IMPL2_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_FINI_IMPL2_4(l,f) __HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem)
#define __HYBRID_SEQ_VECTOR_FINI_IMPL2_5(l,f) __HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem)
#define __HYBRID_SEQ_VECTOR_FINI_IMPL2_6(l,f) __HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem)
#define __HYBRID_SEQ_VECTOR_FINI_IMPL2_7(l,f) __HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem)
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL2(l,fini_elem)     __HYBRID_SEQ_VECTOR_FINI_F_IMPL3(l,fini_elem,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL3(l,fini_elem,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_FINI_F_IMPL3_,f)(l,fini_elem,f)
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_4  __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_5
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_6  __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_7
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_5(l,fini_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_fini_i = (l).v_size; \
		while (__vec_fini_i > 0) { \
			--__vec_fini_i; \
			fini_elem(&(l).v_elem[__vec_fini_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_FINI_F_IMPL3_7(l,fini_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_fini_i = (l).v_size; \
		while (__vec_fini_i > 0) { \
			--__vec_fini_i; \
			fini_elem(&(l).v_elem[__vec_fini_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL3(l,T,fini_elem)     __HYBRID_SEQ_VECTOR_FINI_P_IMPL4(l,T,fini_elem,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL4(l,T,fini_elem,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_FINI_P_IMPL4_,f)(l,T,fini_elem,f)
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_4  __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_5
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_6  __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_7
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_5(l,T,fini_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(fini_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(fini_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(fini_elem,0); \
			__HYBRID_PP_BUBBLE_GET(fini_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_FINI_P_IMPL4_7(l,T,fini_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(fini_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(fini_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(fini_elem,0); \
			__HYBRID_PP_BUBBLE_GET(fini_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
	} \
}__WHILE0


/* >> void VECTOR_CLEAR(VECTOR l, FUNCTIONS f = VECTOR_FUNCTIONS);
 * >> void VECTOR_CLEAR_F(VECTOR l, void clear_elem(T *__restrict elem), FUNCTIONS f = VECTOR_FUNCTIONS);
 * >> void VECTOR_CLEAR_P(VECTOR l, TYPE T, (elem)(expr) clear_elem, FUNCTIONS f = VECTOR_FUNCTIONS);
 * Similar to `vector_fini()', but re-initialize the vector as being empty. */
#define VECTOR_CLEAR(...)    __HYBRID_SEQ_VECTOR_CLEAR((__VA_ARGS__))
#define VECTOR_CLEAR_F(...)  __HYBRID_SEQ_VECTOR_CLEAR_F((__VA_ARGS__))
#define VECTOR_CLEAR_P(...)  __HYBRID_SEQ_VECTOR_CLEAR_P((__VA_ARGS__))
#define __HYBRID_SEQ_VECTOR_CLEAR(args)    __PP_CAT2(__HYBRID_SEQ_VECTOR_CLEAR_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_CLEAR_F(args)  __PP_CAT2(__HYBRID_SEQ_VECTOR_CLEAR_F_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_CLEAR_P(args)  __PP_CAT2(__HYBRID_SEQ_VECTOR_CLEAR_P_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL1(l)     __HYBRID_SEQ_VECTOR_CLEAR_IMPL2(l,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2(l,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_CLEAR_IMPL2_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_4(l,f)   __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_CLEAR_IMPL2_4_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_4_0(l,f) ((l).v_elem ? (void)(__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem),(l).v_elem = NULL,(l).v_size = (l).v_alloc = 0) : (void)0)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_4_1      __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_5
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_5(l,f)   ((l).v_elem ? (void)(__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem),(l).v_elem = NULL,(l).v_size = 0) : (void)0)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_6(l,f)   ((l).v_elem ? (void)(__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem),(l).v_elem = NULL,(l).v_size = (l).v_alloc = 0) : (void)0)
#define __HYBRID_SEQ_VECTOR_CLEAR_IMPL2_7(l,f)   ((l).v_elem ? (void)(__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem),(l).v_elem = NULL,(l).v_size = 0) : (void)0)
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL2(l,clear_elem)     __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3(l,clear_elem,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3(l,clear_elem,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_,f)(l,clear_elem,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_4(l,clear_elem,f)  __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_4_,f)(l,clear_elem,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_4_0(l,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_clear_i = (l).v_size; \
		while (__vec_clear_i > 0) { \
			--__vec_clear_i; \
			clear_elem(&(l).v_elem[__vec_clear_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
		(l).v_elem = NULL; \
		(l).v_size = 0; \
		(l).v_alloc = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_4_1  __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_5
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_5(l,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_clear_i = (l).v_size; \
		while (__vec_clear_i > 0) { \
			--__vec_clear_i; \
			clear_elem(&(l).v_elem[__vec_clear_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
		(l).v_elem = NULL; \
		(l).v_size = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_6(l,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_clear_i = (l).v_size; \
		while (__vec_clear_i > 0) { \
			--__vec_clear_i; \
			clear_elem(&(l).v_elem[__vec_clear_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
		(l).v_elem  = NULL; \
		(l).v_size  = 0; \
		(l).v_alloc = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_F_IMPL3_7(l,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		__SIZE_TYPE__ __vec_clear_i = (l).v_size; \
		while (__vec_clear_i > 0) { \
			--__vec_clear_i; \
			clear_elem(&(l).v_elem[__vec_clear_i]); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
		(l).v_elem  = NULL; \
		(l).v_size  = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL3(l,T,clear_elem)     __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4(l,T,clear_elem,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4(l,T,clear_elem,f)   __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_,f)(l,T,clear_elem,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_4(l,T,clear_elem,f)  __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_4_,f)(l,T,clear_elem,f)
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_4_0(l,T,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(clear_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(clear_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(clear_elem,0); \
			__HYBRID_PP_BUBBLE_GET(clear_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
		(l).v_elem = NULL; \
		(l).v_size = 0; \
		(l).v_alloc = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_4_1  __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_5
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_5(l,T,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(clear_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(clear_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(clear_elem,0); \
			__HYBRID_PP_BUBBLE_GET(clear_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,3)((l).v_elem); \
		(l).v_elem = NULL; \
		(l).v_size = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_6(l,T,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(clear_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(clear_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(clear_elem,0); \
			__HYBRID_PP_BUBBLE_GET(clear_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
		(l).v_elem  = NULL; \
		(l).v_size  = 0; \
		(l).v_alloc = 0; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_CLEAR_P_IMPL4_7(l,T,clear_elem,f) \
do { \
	if ((l).v_elem) { \
		T *__HYBRID_PP_BUBBLE_GET(clear_elem,0) = (l).v_elem + (l).v_size; \
		while (__HYBRID_PP_BUBBLE_GET(clear_elem,0) > (l).v_elem) { \
			--__HYBRID_PP_BUBBLE_GET(clear_elem,0); \
			__HYBRID_PP_BUBBLE_GET(clear_elem,1); \
		} \
		__HYBRID_PP_BUBBLE_GET(f,5)((l).v_elem); \
		(l).v_elem  = NULL; \
		(l).v_size  = 0; \
	} \
}__WHILE0


/* >> void VECTOR_TRUNC(VECTOR l, FUNCTIONS f = VECTOR_FUNCTIONS);
 * Try to release unused memory from the given VECTOR `l' */
#define VECTOR_TRUNC(...) __HYBRID_SEQ_VECTOR_TRUNC((__VA_ARGS__))
#define __HYBRID_SEQ_VECTOR_TRUNC(args) __PP_CAT2(__HYBRID_SEQ_VECTOR_TRUNC_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL1(l)       __HYBRID_SEQ_VECTOR_TRUNC_IMPL2(l,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2(l,f)     __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_TRUNC_IMPL2_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_4(l,f)   __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_TRUNC_IMPL2_4_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_5(l,f)   __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_TRUNC_IMPL2_5_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_4_1(l,f) (void)0 /* No try_realloc() available in except-mode */
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_5_1(l,f) (void)0 /* No try_realloc() available in except-mode */
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_4_0(l,f) \
do { \
	if ((l).v_alloc > (l).v_size) { \
		void *__vector_trunc_newvec; \
		__vector_trunc_newvec = __HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,(l).v_size * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __likely(__vector_trunc_newvec) { \
			*(void **)&(l).v_elem = __vector_trunc_newvec; \
			(l).v_alloc = (l).v_size; \
		} \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_5_0(l,f) \
do { \
	void *__vector_trunc_newvec; \
	__vector_trunc_newvec = __HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,(l).v_size * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __likely(__vector_trunc_newvec) \
	   *(void **)&(l).v_elem = __vector_trunc_newvec; \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_6(l,f) \
do { \
	if ((l).v_alloc > (l).v_size) { \
		void *__vector_trunc_newvec; \
		__vector_trunc_newvec = __HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,(l).v_size * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __likely(__vector_trunc_newvec) { \
			*(void **)&(l).v_elem = __vector_trunc_newvec; \
			(l).v_alloc = (l).v_size; \
		} \
	} \
}__WHILE0
#define __HYBRID_SEQ_VECTOR_TRUNC_IMPL2_7(l,f) \
do { \
	void *__vector_trunc_newvec; \
	__vector_trunc_newvec = __HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,(l).v_size * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __likely(__vector_trunc_newvec) \
	   *(void **)&(l).v_elem = __vector_trunc_newvec; \
	} \
}__WHILE0


/* >> size_t VECTOR_ALLOC(VECTOR l, FUNCTIONS f = VECTOR_FUNCTIONS);
 * Returns the allocated number of vector elements. */
#define VECTOR_ALLOC(...) __HYBRID_SEQ_VECTOR_ALLOC_PRIV((__VA_ARGS__))
#define __HYBRID_SEQ_VECTOR_ALLOC_PRIV(args) __PP_CAT2(__HYBRID_SEQ_VECTOR_ALLOC,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_SEQ_VECTOR_ALLOC1(l)    __HYBRID_SEQ_VECTOR_ALLOC2(l,VECTOR_FUNCTIONS)
#define __HYBRID_SEQ_VECTOR_ALLOC2(l,f)  __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_SEQ_VECTOR_ALLOC_IMPL,f)(l,f)
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL4(l,f)    __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_SEQ_VECTOR_ALLOC_IMPL4_,f)(l,f)
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL4_0(l,f) ((l).v_alloc)
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL4_1(l,f) ((l).v_size)
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL5(l,f)   (__HYBRID_PP_BUBBLE_GET(f,4)((l).v_elem)/__HYBRID_VECTOR_ELEMSIZE(l))
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL6(l,f)   ((l).v_alloc)
#define __HYBRID_SEQ_VECTOR_ALLOC_IMPL7(l,f)   (__HYBRID_PP_BUBBLE_GET(f,6)((l).v_elem)/__HYBRID_VECTOR_ELEMSIZE(l))

/* >> size_t VECTOR_SIZE(VECTOR l);
 * Returns the used vector size. */
#define VECTOR_SIZE(l)        ((l).v_size)

/* Vector element access. */
#define VECTOR_ELEM(l)        ((l).v_elem)
#define VECTOR_GET(l,i)       ((l).v_elem[i])
#define VECTOR_SET(l,i,v)     ((l).v_elem[i]=(v))

#define __HYBRID_VECTOR_ELEMSIZE(l)               sizeof(*(l).v_elem)
#define __HYBRID_VECTOR_INITIAL_ALLOCSIZE(l,f)   ((64/__HYBRID_VECTOR_ELEMSIZE(l)) < 2 ? 2 : (64/__HYBRID_VECTOR_ELEMSIZE(l)))
#define __HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f)  (VECTOR_SIZE(l) ? (VECTOR_SIZE(l) * 2) : __HYBRID_VECTOR_INITIAL_ALLOCSIZE(l,f))

/* >> void VECTOR_REQUIRE1(VECTOR l, LABEL err = <undefined>, FUNCTIONS f = VECTOR_FUNCTIONS);
 * Allocate new memory to ensure that at least 1 element can be added. */
#define VECTOR_REQUIRE1(...) __HYBRID_VECTOR_REQUIRE1_PRIV((__VA_ARGS__))
#define __HYBRID_VECTOR_REQUIRE1_PRIV(args) __PP_CAT2(__HYBRID_VECTOR_REQUIRE1,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_VECTOR_REQUIRE11(l)        __HYBRID_VECTOR_REQUIRE13(l,-,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_REQUIRE12(l,err)    __HYBRID_VECTOR_REQUIRE13(l,err,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_REQUIRE13(l,err,f)  __HYBRID_SEQ_VECTOR_SELECT(__HYBRID_VECTOR_REQUIRE1_IMPL_,f)(l,err,f)
#define __HYBRID_VECTOR_REQUIRE1_IMPL_4(l,err,f) __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_VECTOR_REQUIRE1_IMPL_4_,f)(l,err,f)
#define __HYBRID_VECTOR_REQUIRE1_IMPL_5(l,err,f) __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_VECTOR_REQUIRE1_IMPL_5_,f)(l,err,f)
#define __HYBRID_VECTOR_REQUIRE1_IMPL_6(l,err,f) __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_VECTOR_REQUIRE1_IMPL_6_,f)(l,err,f)
#define __HYBRID_VECTOR_REQUIRE1_IMPL_7(l,err,f) __HYBRID_SEQ_VECTOR_XSELECT(__HYBRID_VECTOR_REQUIRE1_IMPL_7_,f)(l,err,f)

#define __HYBRID_VECTOR_REQUIRE1_IMPL_4_0(l,err,f) \
do { \
	__SIZE_TYPE__ __v_new_alloc; void *__v_new_vector; \
	__v_new_alloc = __HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f); \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_alloc = VECTOR_SIZE(l) + 1; \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __unlikely(!__v_new_vector) goto err; \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
	(l).v_alloc = __v_new_alloc; \
}__WHILE0
#define __HYBRID_VECTOR_REQUIRE1_IMPL_5_0(l,err,f) \
do { \
	void *__v_new_vector; \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,__HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f) * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,(VECTOR_SIZE(l) + 1) * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __unlikely(!__v_new_vector) goto err; \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
}__WHILE0
#define __HYBRID_VECTOR_REQUIRE1_IMPL_6_0(l,err,f) \
do { \
	__SIZE_TYPE__ __v_new_alloc; void *__v_new_vector; \
	__v_new_alloc = __HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f); \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_alloc = VECTOR_SIZE(l) + 1; \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,3)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __unlikely(!__v_new_vector) goto err; \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
	(l).v_alloc = __v_new_alloc; \
}__WHILE0
#define __HYBRID_VECTOR_REQUIRE1_IMPL_7_0(l,err,f) \
do { \
	void *__v_new_vector; \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,__HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f) * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,3)((void *)(l).v_elem,(VECTOR_SIZE(l) + 1) * __HYBRID_VECTOR_ELEMSIZE(l)); \
		if __unlikely(!__v_new_vector) goto err; \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
}__WHILE0
#define __HYBRID_VECTOR_REQUIRE1_IMPL_4_1(l,err,f) \
     (*(void **)&(l).v_elem = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,(VECTOR_SIZE(l) + 1) * __HYBRID_VECTOR_ELEMSIZE(l)))
#define __HYBRID_VECTOR_REQUIRE1_IMPL_5_1(l,err,f) \
     (*(void **)&(l).v_elem = (void *)__HYBRID_PP_BUBBLE_GET(f,2)((void *)(l).v_elem,(VECTOR_SIZE(l) + 1) * __HYBRID_VECTOR_ELEMSIZE(l)))
#define __HYBRID_VECTOR_REQUIRE1_IMPL_6_1(l,err,f) \
do { \
	__SIZE_TYPE__ __v_new_alloc; void *__v_new_vector; \
	__v_new_alloc = __HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f); \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_alloc = VECTOR_SIZE(l) + 1; \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,3)((void *)(l).v_elem,__v_new_alloc * __HYBRID_VECTOR_ELEMSIZE(l)); \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
	(l).v_alloc = __v_new_alloc; \
}__WHILE0
#define __HYBRID_VECTOR_REQUIRE1_IMPL_7_1(l,err,f) \
do { \
	void *__v_new_vector; \
	__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,4)((void *)(l).v_elem,__HYBRID_VECTOR_REQUIRE1_ALLOCSIZE(l,f) * __HYBRID_VECTOR_ELEMSIZE(l)); \
	if __unlikely(!__v_new_vector) { \
		__v_new_vector = (void *)__HYBRID_PP_BUBBLE_GET(f,3)((void *)(l).v_elem,(VECTOR_SIZE(l) + 1) * __HYBRID_VECTOR_ELEMSIZE(l)); \
	} \
	*(void **)&(l).v_elem = __v_new_vector; \
}__WHILE0

/* void VECTOR_MOVE(VECTOR l, size_t dst, size_t src, size_t count); */
#define VECTOR_MOVE(l,dst,src,count) \
  (void)memmove((l).v_elem+(dst),(l).v_elem+(src),(count)*__HYBRID_VECTOR_ELEMSIZE(l))


/* >> void VECTOR_APPEND(VECTOR l, T elem, LABEL err = <undefined>, FUNCTIONS f = VECTOR_FUNCTIONS); */
#define VECTOR_APPEND(...) __HYBRID_VECTOR_APPEND((__VA_ARGS__))
#define __HYBRID_VECTOR_APPEND(args) __PP_CAT2(__HYBRID_VECTOR_APPEND_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_VECTOR_APPEND_IMPL2(l,elem)       __HYBRID_VECTOR_APPEND_IMPL4(l,elem,-,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_APPEND_IMPL3(l,elem,err)   __HYBRID_VECTOR_APPEND_IMPL4(l,elem,err,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_APPEND_IMPL4(l,elem,err,f) \
do { \
	if ((l).v_size >= __HYBRID_SEQ_VECTOR_ALLOC2(l,f)) \
		__HYBRID_VECTOR_REQUIRE13(l,err,f); \
	(l).v_elem[(l).v_size++]=(elem); \
}__WHILE0

/* >> void VECTOR_EAPPEND(VECTOR l, TYPE T, (elem)(expr) pred, LABEL err = <undefined>, FUNCTIONS f = VECTOR_FUNCTIONS);
 * $ VECTOR(int) vec = VECTOR_INIT;
 * $ VECTOR_EAPPEND(vec,int,(elem)(*elem = 42),err);
 * WARNING: `pred' must return normally! */
#define VECTOR_EAPPEND(...) __HYBRID_VECTOR_EAPPEND((__VA_ARGS__))
#define __HYBRID_VECTOR_EAPPEND(args) __PP_CAT2(__HYBRID_VECTOR_EAPPEND_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_VECTOR_EAPPEND_IMPL3(l,T,pred)       __HYBRID_VECTOR_EAPPEND_IMPL5(l,T,pred,-,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_EAPPEND_IMPL4(l,T,pred,err)   __HYBRID_VECTOR_EAPPEND_IMPL5(l,T,pred,err,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_EAPPEND_IMPL5(l,T,pred,err,f) \
do { \
	T *__HYBRID_PP_BUBBLE_GET(pred,0); \
	if ((l).v_size >= __HYBRID_SEQ_VECTOR_ALLOC2(l,f)) \
		__HYBRID_VECTOR_REQUIRE13(l,err,f); \
	__HYBRID_PP_BUBBLE_GET(pred,0) = &(l).v_elem[(l).v_size]; \
	__HYBRID_PP_BUBBLE_GET(pred,1); \
	++(l).v_size; \
}__WHILE0


/* >> void VECTOR_INSERT(VECTOR l, size_t index, T elem, LABEL err = <undefined>, FUNCTIONS f = VECTOR_FUNCTIONS); */
#define VECTOR_INSERT(...) __HYBRID_VECTOR_INSERT((__VA_ARGS__))
#define __HYBRID_VECTOR_INSERT(args) __PP_CAT2(__HYBRID_VECTOR_INSERT_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_VECTOR_INSERT_IMPL3(l,index,elem)       __HYBRID_VECTOR_INSERT_IMPL5(l,index,elem,-,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_INSERT_IMPL4(l,index,elem,err)   __HYBRID_VECTOR_INSERT_IMPL5(l,index,elem,err,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_INSERT_IMPL5(l,index,elem,err,f) \
do { \
	assert((index) <= (l).v_size); \
	if ((l).v_size >= __HYBRID_SEQ_VECTOR_ALLOC2(l,f)) \
		__HYBRID_VECTOR_REQUIRE13(l,err,f); \
	VECTOR_MOVE(l,(index)+1,(index),(l).v_size-(index)); \
	(l).v_elem[index]=(elem); \
	++(l).v_size; \
}__WHILE0

/* >> void VECTOR_EINSERT(VECTOR l, TYPE T, size_t index, (elem)(expr) pred, LABEL err = <undefined>, FUNCTIONS f = VECTOR_FUNCTIONS);
 * $ VECTOR(int) vec = VECTOR_INIT;
 * $ VECTOR_EINSERT(vec,int,0,(elem)(*elem = 42),err);
 * WARNING: `pred' must return normally! */
#define VECTOR_EINSERT(...) __HYBRID_VECTOR_EINSERT((__VA_ARGS__))
#define __HYBRID_VECTOR_EINSERT(args) __PP_CAT2(__HYBRID_VECTOR_EINSERT_IMPL,__HYBRID_PP_VA_NARGS args)args
#define __HYBRID_VECTOR_EINSERT_IMPL4(l,T,index,pred)       __HYBRID_VECTOR_EINSERT_IMPL6(l,T,index,pred,-,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_EINSERT_IMPL5(l,T,index,pred,err)   __HYBRID_VECTOR_EINSERT_IMPL6(l,T,index,pred,err,VECTOR_FUNCTIONS)
#define __HYBRID_VECTOR_EINSERT_IMPL6(l,T,index,pred,err,f) \
do { \
	T *__HYBRID_PP_BUBBLE_GET(pred,0); \
	assert((index) <= (l).v_size); \
	if ((l).v_size >= __HYBRID_SEQ_VECTOR_ALLOC2(l,f)) \
		__HYBRID_VECTOR_REQUIRE13(l,err,f); \
	VECTOR_MOVE(l,(index)+1,(index),(l).v_size-(index)); \
	__HYBRID_PP_BUBBLE_GET(pred,0) = &(l).v_elem[index]; \
	__HYBRID_PP_BUBBLE_GET(pred,1); \
	++(l).v_size; \
}__WHILE0




__DECL_END
#endif /* __CC__ */
#endif /* __PREPROCESSOR_HAVE_VA_ARGS */

#endif /* !__GUARD_HYBRID_SEQUENCE_VECTOR_H */
