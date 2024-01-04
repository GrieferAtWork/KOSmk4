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
#ifndef _CXX_BITS_OPERATOR_NEW_H
#define _CXX_BITS_OPERATOR_NEW_H 1

#include <__stdcxx.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <kos/anno.h>
#include <bits/types.h>
#if defined(__KOS__) && defined(__KERNEL__)
#include <kernel/malloc.h>
#else /* __KOS__ && __KERNEL__ */
#include <libc/malloc.h>
#endif /* !__KOS__ || !__KERNEL__ */

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */

#ifndef __std_nothrow_t_defined
#define __std_nothrow_t_defined
struct nothrow_t {};
#endif /* !__std_nothrow_t_defined */

__NAMESPACE_STD_END

#if defined(__KOS__) && defined(__KERNEL__)
__CXX_FORCEINLINE __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_ALLOC_SIZE((1)) void *
__KCALL operator new(__size_t __num_bytes) __THROWS(E_BADALLOC) {
	return kmalloc(__num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_ALLOC_SIZE((1)) void *
__KCALL operator new[](__size_t __num_bytes) __THROWS(E_BADALLOC) {
	return kmalloc(__num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __NOBLOCK void __KCALL
operator delete(void *__heap_ptr) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE __NOBLOCK void __KCALL
operator delete[](void *__heap_ptr) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__KCALL operator new(__size_t __num_bytes, std::nothrow_t const &) __CXX_NOEXCEPT {
	return kmalloc_nx(__num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__KCALL operator new[](__size_t __num_bytes, std::nothrow_t const &) __CXX_NOEXCEPT {
	return kmalloc_nx(__num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __NOBLOCK void __KCALL
operator delete(void *__heap_ptr, std::nothrow_t const &) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE __NOBLOCK void __KCALL
operator delete[](void *__heap_ptr, std::nothrow_t const &) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
#else /* __KOS__ && __KERNEL__ */
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new(__size_t __num_bytes) /*throw(std::bad_alloc)*/;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new[](__size_t __num_bytes) /*throw(std::bad_alloc)*/;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new(__size_t __num_bytes, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new[](__size_t __num_bytes, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr, std::nothrow_t const &) __CXX_NOEXCEPT;
#endif /* !__KOS__ || !__KERNEL__ */

/* Placement new */
__CXX_FORCEINLINE __ATTR_CONST __ATTR_RETNONNULL __ATTR_NONNULL((2)) void *__LIBCCALL operator new(__size_t __UNUSED(__num_bytes), void *__ptr) __CXX_NOEXCEPT { return __ptr; }
__CXX_FORCEINLINE __ATTR_CONST __ATTR_RETNONNULL __ATTR_NONNULL((2)) void *__LIBCCALL operator new[](__size_t __UNUSED(__num_bytes), void *__ptr) __CXX_NOEXCEPT { return __ptr; }
__CXX_FORCEINLINE void __LIBCCALL operator delete(void *__UNUSED(__new_ptr), void *__UNUSED(__ptr)) __CXX_NOEXCEPT { }
__CXX_FORCEINLINE void __LIBCCALL operator delete[](void *__UNUSED(__new_ptr), void *__UNUSED(__ptr)) __CXX_NOEXCEPT { }


#if defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation+0)
#if defined(__KOS__) && defined(__KERNEL__)
__CXX_FORCEINLINE __ATTR_EXTERNALLY_VISIBLE void __KCALL
operator delete(void *__heap_ptr, __size_t __UNUSED(__num_bytes)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE __ATTR_EXTERNALLY_VISIBLE void __KCALL
operator delete[](void *__heap_ptr, __size_t __UNUSED(__num_bytes)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
#else /* __KOS__ && __KERNEL__ */
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr, __size_t __num_bytes) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr, __size_t __num_bytes) __CXX_NOEXCEPT;
#endif /* !__KOS__ || !__KERNEL__ */
#endif /* __cpp_sized_deallocation */
#if defined(__cpp_aligned_new) && (__cpp_aligned_new+0)
#ifndef __std_align_val_t_defined
#define __std_align_val_t_defined
__NAMESPACE_STD_BEGIN
#ifdef __COMPILER_HAVE_CXX_ENUM_CLASSES
enum class align_val_t: __size_t {};
#else /* __COMPILER_HAVE_CXX_ENUM_CLASSES */
enum align_val_t {};
#endif /* !__COMPILER_HAVE_CXX_ENUM_CLASSES */
__NAMESPACE_STD_END
#endif /* !__std_align_val_t_defined */
#if defined(__KOS__) && defined(__KERNEL__)
__CXX_FORCEINLINE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) __ATTR_RETNONNULL void *__KCALL
operator new(__size_t __num_bytes, std::align_val_t __min_alignment) __THROWS(E_BADALLOC) {
	return kmemalign((__size_t)__min_alignment, __num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__KCALL
operator new(__size_t __num_bytes, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT {
	return kmemalign_nx((__size_t)__min_alignment, __num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE void __KCALL
operator delete(void *__heap_ptr, std::align_val_t __UNUSED(__min_alignment)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE void __KCALL
operator delete(void *__heap_ptr, std::align_val_t __UNUSED(__min_alignment), std::nothrow_t const &) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) __ATTR_RETNONNULL void *__KCALL
operator new[](__size_t __num_bytes, std::align_val_t __min_alignment) __THROWS(E_BADALLOC) {
	return kmemalign((__size_t)__min_alignment, __num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__KCALL
operator new[](__size_t __num_bytes, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT {
	return kmemalign_nx((__size_t)__min_alignment, __num_bytes, GFP_NORMAL);
}
__CXX_FORCEINLINE void __KCALL
operator delete[](void *__heap_ptr, std::align_val_t __UNUSED(__min_alignment)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE void __KCALL
operator delete[](void *__heap_ptr, std::align_val_t __UNUSED(__min_alignment), std::nothrow_t const &) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
#if defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation+0)
__CXX_FORCEINLINE void __KCALL
operator delete(void *__heap_ptr, std::size_t __UNUSED(__num_bytes), std::align_val_t __UNUSED(__min_alignment)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
__CXX_FORCEINLINE void __KCALL
operator delete[](void *__heap_ptr, std::size_t __UNUSED(__num_bytes), std::align_val_t __UNUSED(__min_alignment)) __CXX_NOEXCEPT {
	kfree(__heap_ptr);
}
#endif /* __cpp_sized_deallocation */
#else /* __KOS__ && __KERNEL__ */
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) __ATTR_RETNONNULL void *__LIBCCALL operator new(__size_t __num_bytes, std::align_val_t __min_alignment) /*throw(std::bad_alloc)*/;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new(__size_t __num_bytes, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr, std::align_val_t __min_alignment) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) __ATTR_RETNONNULL void *__LIBCCALL operator new[](__size_t __num_bytes, std::align_val_t __min_alignment) /*throw(std::bad_alloc)*/;
extern __ATTR_EXTERNALLY_VISIBLE __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__LIBCCALL operator new[](__size_t __num_bytes, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr, std::align_val_t __min_alignment) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr, std::align_val_t __min_alignment, std::nothrow_t const &) __CXX_NOEXCEPT;
#if defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation+0)
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete(void *__heap_ptr, std::size_t __num_bytes, std::align_val_t __min_alignment) __CXX_NOEXCEPT;
extern __ATTR_EXTERNALLY_VISIBLE void __LIBCCALL operator delete[](void *__heap_ptr, std::size_t __num_bytes, std::align_val_t __min_alignment) __CXX_NOEXCEPT;
#endif /* __cpp_sized_deallocation */
#endif /* !__KOS__ || !__KERNEL__ */
#endif /* __cpp_aligned_new */


__CXXDECL_END

#endif /* !_CXX_BITS_OPERATOR_NEW_H */
