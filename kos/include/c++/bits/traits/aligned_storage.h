/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _CXX_BITS_ALIGNED_STORAGE_H
#define _CXX_BITS_ALIGNED_STORAGE_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>


__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
#if defined(__GNUC__) && !defined(__INTELLISENSE__) && (defined(__NO_has_attribute) || !__has_attribute(__aligned__))
#define __PRIVATE_MAX_ALIGN_FOR_LENGTH(size) \
	__COMPILER_ALIGNOF(typename __NAMESPACE_INT_SYM __aligned_storage_msa<(size)>::__type)
template<__SIZE_TYPE__ __StorageSize>
struct __aligned_storage_msa {
	union __type {
		unsigned char __data[__StorageSize];
		struct __attribute__((__aligned__)) {
		} __align;
	};
};
#else
#define __PRIVATE_MAX_ALIGN_FOR_LENGTH(size) __ALIGNOF_MAX_ALIGN_T__
#endif
#ifndef __std_aligned_union_defined
#ifdef __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES
template<class... __Types> struct __strictest_alignment {
	__CXX_STATIC_CONST(__SIZE_TYPE__, __max_alignment = 0);
	__CXX_STATIC_CONST(__SIZE_TYPE__, __max_size = 0);
};
template<class __T, class... __Types> struct __strictest_alignment<__T, __Types...> {
	__CXX_STATIC_CONST(__SIZE_TYPE__, __max_alignment =
	                                  __COMPILER_ALIGNOF(__T) > __strictest_alignment<__Types...>::__max_alignment
	                                  ? __COMPILER_ALIGNOF(__T)
	                                  : __strictest_alignment<__Types...>::__max_alignment);
	__CXX_STATIC_CONST(__SIZE_TYPE__, __max_size =
	                                  sizeof(__T) > __strictest_alignment<__Types...>::__max_size
	                                  ? sizeof(__T)
	                                  : __strictest_alignment<__Types...>::__max_size);
};
#endif /* __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES */
#endif /* !__std_aligned_union_defined */
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<__SIZE_TYPE__ __StorageSize,
         __SIZE_TYPE__ __Alignment = __PRIVATE_MAX_ALIGN_FOR_LENGTH(__StorageSize)>
struct aligned_storage {
	union type {
		unsigned char __data[__StorageSize];
		struct __ATTR_ALIGNED(__Alignment) {
		} __align;
	};
};
#ifndef __std_aligned_union_defined
#ifdef __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES
#define __std_aligned_union_defined
template<__SIZE_TYPE__ __StorageSize, class... __Types> struct aligned_union {
private:
	static_assert(sizeof...(__Types) != 0, "At least one type is required");
	typedef __NAMESPACE_INT_SYM __strictest_alignment<__Types...> __strictest;
	__CXX_STATIC_CONST(__SIZE_TYPE__, __max_size =
	                                  __StorageSize > __strictest::__max_size
	                                  ? __StorageSize
	                                  : __strictest::__max_size);

public:
	__CXX_STATIC_CONST(__SIZE_TYPE__, alignment_value = __strictest::__max_alignment);
	typedef typename aligned_storage<__max_size, alignment_value>::type type;
};
#ifdef __COMPILER_HAVE_CXX_STATIC_CONST
template<__SIZE_TYPE__ __StorageSize, class... __Types>
__CXX11_CONSTEXPR_OR_CONST __SIZE_TYPE__ aligned_union<__StorageSize, __Types...>::alignment_value;
#endif /* __COMPILER_HAVE_CXX_STATIC_CONST */
#endif /* __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES */
#endif /* !__std_aligned_union_defined */

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_ALIGNED_STORAGE_H */
