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
#ifndef _OPTIMIZED_SSP_STRING_H
#define _OPTIMIZED_SSP_STRING_H 1

#include <__stdinc.h>

/* Platform-independent, optimized ssp/string.h functions. */
#if (!defined(__NO_ATTR_FORCEINLINE) && \
     !defined(__NO_builtin_constant_p))
#include <hybrid/typecore.h>

#include <optimized/string.h>
#include <ssp/chk.h>

#include <libc/core/ssp.string.h>

__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN

/*[[[deemon
local aligned1 = "/" "*aligned(1)*" "/ ";
local aligned2 = "/" "*aligned(2)*" "/ ";
local aligned4 = "/" "*aligned(4)*" "/ ";
local aligned8 = "/" "*aligned(8)*" "/ ";
local funcs = {
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned1 + "void *", "__NOTHROW_NCX", "memset", { (aligned1 + "void *__restrict", "__dst"), ("int", "__byte"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned1 + "void *", "__NOTHROW_NCX", "mempset", { (aligned1 + "void *__restrict", "__dst"), ("int", "__byte"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memcpy", { (aligned1 + "void *__restrict", "__dst"), (aligned1 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memcpyc", { (aligned1 + "void *__restrict", "__dst"), (aligned1 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempcpy", { (aligned1 + "void *__restrict", "__dst"), (aligned1 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempcpyc", { (aligned1 + "void *__restrict", "__dst"), (aligned1 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmove", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmoveup", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmovedown", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmovec", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmoveupc", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "memmovedownc", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmove", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmoveup", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmovedown", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_bytes") }, "__dst", { "__n_bytes" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmovec", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmoveupc", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned1 + "void *", "__NOTHROW_NCX", "mempmovedownc", { (aligned1 + "void *", "__dst"), (aligned1 + "void const *", "__src"), ("__SIZE_TYPE__", "__elem_count"), ("__SIZE_TYPE__", "__elem_size") }, "__dst", { "__elem_count", "__elem_size" }, 1),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "memsetw", { (aligned2 + "void *__restrict", "__dst"), ("__UINT16_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "mempsetw", { (aligned2 + "void *__restrict", "__dst"), ("__UINT16_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "memcpyw", { (aligned2 + "void *__restrict", "__dst"), (aligned2 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "mempcpyw", { (aligned2 + "void *__restrict", "__dst"), (aligned2 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "memmovew", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "memmoveupw", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "memmovedownw", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "mempmovew", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "mempmoveupw", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned2 + "__UINT16_TYPE__ *", "__NOTHROW_NCX", "mempmovedownw", { (aligned2 + "void *", "__dst"), (aligned2 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_words") }, "__dst", { "__n_words" }, 2),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "memsetl", { (aligned4 + "void *__restrict", "__dst"), ("__UINT32_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "mempsetl", { (aligned4 + "void *__restrict", "__dst"), ("__UINT32_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "memcpyl", { (aligned4 + "void *__restrict", "__dst"), (aligned4 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "mempcpyl", { (aligned4 + "void *__restrict", "__dst"), (aligned4 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "memmovel", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "memmoveupl", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "memmovedownl", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "mempmovel", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "mempmoveupl", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned4 + "__UINT32_TYPE__ *", "__NOTHROW_NCX", "mempmovedownl", { (aligned4 + "void *", "__dst"), (aligned4 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_dwords") }, "__dst", { "__n_dwords" }, 4),
};
local funcs64 = {
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "memsetq", { (aligned8 + "void *__restrict", "__dst"), ("__UINT64_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "mempsetq", { (aligned8 + "void *__restrict", "__dst"), ("__UINT64_TYPE__", "__word"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "memcpyq", { (aligned8 + "void *__restrict", "__dst"), (aligned8 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "mempcpyq", { (aligned8 + "void *__restrict", "__dst"), (aligned8 + "void const *__restrict", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "memmoveq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "memmoveupq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "memmovedownq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "mempmoveq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "mempmoveupq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
	("__ATTR_RETNONNULL __ATTR_NONNULL((1, 2))", aligned8 + "__UINT64_TYPE__ *", "__NOTHROW_NCX", "mempmovedownq", { (aligned8 + "void *", "__dst"), (aligned8 + "void const *", "__src"), ("__SIZE_TYPE__", "__n_qwords") }, "__dst", { "__n_qwords" }, 8),
};

function printFunction(local attr, returnType, nothrow, name, args, dst, n_bytes_vars, multiplier) {
	print "#ifndef __fast___",;
	print name,;
	print "_chk_defined";
	print "#ifdef __fast_",;
	print name,;
	print "_defined";
	print "#define __fast___",;
	print name,;
	print "_chk_defined";

	print "__FORCELOCAL __ATTR_ARTIFICIAL ",;
	print attr,;
	if (attr)
		print " ",;
	print returnType;
	print "__NOTHROW_NCX(__LIBC_FAST_NAME(__",;
	print name,;
	print "_chk))(",;
	local argsIndentSize = #name + 40;
	for (local typ, name: args) {
		print typ,;
		if (!typ.endswith("*"))
			print " ",;
		print name,;
		print ",";
		print " " * argsIndentSize,;
	}
	print "__SIZE_TYPE__ ",;
	print dst,;
	print "_objsize) {";
	print "	if __untraced(",;
	local isFirst = true;
	for (local v: n_bytes_vars) {
		if (!isFirst)
			print " && ",;
		isFirst = false;
		print "__builtin_constant_p(",;
		print v,;
		print ")",;
	}
	print ") {";
	print "		__ssp_chk_dstbuf(",;
	print repr name,;
	print ", ",;
	print dst,;
	print ", ",;
	local isFirst = true;
	for (local v: n_bytes_vars) {
		if (!isFirst)
			print " * ",;
		isFirst = false;
		print v,;
	}
	if (multiplier > 1)
		print " *", multiplier,;
	print ", ",;
	print dst,;
	print "_objsize);";
	print "		return __LIBC_FAST_NAME(",;
	print name,;
	print ")(",;
	local isFirst = true;
	for (local typ, name: args) {
		if (!isFirst)
			print ", ",;
		isFirst = false;
		print name,;
	}
	print ");";
	print "	}";
	print "	return __libc_core___",;
	print name,;
	print "_chk(",;
	for (local none, name: args) {
		print name,;
		print ", ",;
	}
	print dst,;
	print "_objsize);";
	print "}";
	print "#endif /" "* __fast_",;
	print name,;
	print "_defined *" "/";
	print "#endif /" "* !__fast___",;
	print name,;
	print "_chk_defined *" "/";
	print;
}
for (local info: funcs)
	printFunction(info...);
print "#ifdef __UINT64_TYPE__";
for (local info: funcs64)
	printFunction(info...);
print "#endif /" "* __UINT64_TYPE__ *" "/";

]]]*/
#ifndef __fast___memset_chk_defined
#ifdef __fast_memset_defined
#define __fast___memset_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memset_chk))(/*aligned(1)*/ void *__restrict __dst,
                                              int __byte,
                                              __SIZE_TYPE__ __n_bytes,
                                              __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("memset", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(memset)(__dst, __byte, __n_bytes);
	}
	return __libc_core___memset_chk(__dst, __byte, __n_bytes, __dst_objsize);
}
#endif /* __fast_memset_defined */
#endif /* !__fast___memset_chk_defined */

#ifndef __fast___mempset_chk_defined
#ifdef __fast_mempset_defined
#define __fast___mempset_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempset_chk))(/*aligned(1)*/ void *__restrict __dst,
                                               int __byte,
                                               __SIZE_TYPE__ __n_bytes,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("mempset", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(mempset)(__dst, __byte, __n_bytes);
	}
	return __libc_core___mempset_chk(__dst, __byte, __n_bytes, __dst_objsize);
}
#endif /* __fast_mempset_defined */
#endif /* !__fast___mempset_chk_defined */

#ifndef __fast___memcpy_chk_defined
#ifdef __fast_memcpy_defined
#define __fast___memcpy_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memcpy_chk))(/*aligned(1)*/ void *__restrict __dst,
                                              /*aligned(1)*/ void const *__restrict __src,
                                              __SIZE_TYPE__ __n_bytes,
                                              __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("memcpy", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(memcpy)(__dst, __src, __n_bytes);
	}
	return __libc_core___memcpy_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_memcpy_defined */
#endif /* !__fast___memcpy_chk_defined */

#ifndef __fast___memcpyc_chk_defined
#ifdef __fast_memcpyc_defined
#define __fast___memcpyc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memcpyc_chk))(/*aligned(1)*/ void *__restrict __dst,
                                               /*aligned(1)*/ void const *__restrict __src,
                                               __SIZE_TYPE__ __elem_count,
                                               __SIZE_TYPE__ __elem_size,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("memcpyc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(memcpyc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___memcpyc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_memcpyc_defined */
#endif /* !__fast___memcpyc_chk_defined */

#ifndef __fast___mempcpy_chk_defined
#ifdef __fast_mempcpy_defined
#define __fast___mempcpy_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempcpy_chk))(/*aligned(1)*/ void *__restrict __dst,
                                               /*aligned(1)*/ void const *__restrict __src,
                                               __SIZE_TYPE__ __n_bytes,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("mempcpy", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(mempcpy)(__dst, __src, __n_bytes);
	}
	return __libc_core___mempcpy_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_mempcpy_defined */
#endif /* !__fast___mempcpy_chk_defined */

#ifndef __fast___mempcpyc_chk_defined
#ifdef __fast_mempcpyc_defined
#define __fast___mempcpyc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempcpyc_chk))(/*aligned(1)*/ void *__restrict __dst,
                                                /*aligned(1)*/ void const *__restrict __src,
                                                __SIZE_TYPE__ __elem_count,
                                                __SIZE_TYPE__ __elem_size,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("mempcpyc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(mempcpyc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___mempcpyc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_mempcpyc_defined */
#endif /* !__fast___mempcpyc_chk_defined */

#ifndef __fast___memmove_chk_defined
#ifdef __fast_memmove_defined
#define __fast___memmove_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmove_chk))(/*aligned(1)*/ void *__dst,
                                               /*aligned(1)*/ void const *__src,
                                               __SIZE_TYPE__ __n_bytes,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("memmove", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(memmove)(__dst, __src, __n_bytes);
	}
	return __libc_core___memmove_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_memmove_defined */
#endif /* !__fast___memmove_chk_defined */

#ifndef __fast___memmoveup_chk_defined
#ifdef __fast_memmoveup_defined
#define __fast___memmoveup_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveup_chk))(/*aligned(1)*/ void *__dst,
                                                 /*aligned(1)*/ void const *__src,
                                                 __SIZE_TYPE__ __n_bytes,
                                                 __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("memmoveup", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveup)(__dst, __src, __n_bytes);
	}
	return __libc_core___memmoveup_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_memmoveup_defined */
#endif /* !__fast___memmoveup_chk_defined */

#ifndef __fast___memmovedown_chk_defined
#ifdef __fast_memmovedown_defined
#define __fast___memmovedown_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovedown_chk))(/*aligned(1)*/ void *__dst,
                                                   /*aligned(1)*/ void const *__src,
                                                   __SIZE_TYPE__ __n_bytes,
                                                   __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("memmovedown", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(memmovedown)(__dst, __src, __n_bytes);
	}
	return __libc_core___memmovedown_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_memmovedown_defined */
#endif /* !__fast___memmovedown_chk_defined */

#ifndef __fast___memmovec_chk_defined
#ifdef __fast_memmovec_defined
#define __fast___memmovec_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovec_chk))(/*aligned(1)*/ void *__dst,
                                                /*aligned(1)*/ void const *__src,
                                                __SIZE_TYPE__ __elem_count,
                                                __SIZE_TYPE__ __elem_size,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("memmovec", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(memmovec)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___memmovec_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_memmovec_defined */
#endif /* !__fast___memmovec_chk_defined */

#ifndef __fast___memmoveupc_chk_defined
#ifdef __fast_memmoveupc_defined
#define __fast___memmoveupc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveupc_chk))(/*aligned(1)*/ void *__dst,
                                                  /*aligned(1)*/ void const *__src,
                                                  __SIZE_TYPE__ __elem_count,
                                                  __SIZE_TYPE__ __elem_size,
                                                  __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("memmoveupc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveupc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___memmoveupc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_memmoveupc_defined */
#endif /* !__fast___memmoveupc_chk_defined */

#ifndef __fast___memmovedownc_chk_defined
#ifdef __fast_memmovedownc_defined
#define __fast___memmovedownc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovedownc_chk))(/*aligned(1)*/ void *__dst,
                                                    /*aligned(1)*/ void const *__src,
                                                    __SIZE_TYPE__ __elem_count,
                                                    __SIZE_TYPE__ __elem_size,
                                                    __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("memmovedownc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(memmovedownc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___memmovedownc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_memmovedownc_defined */
#endif /* !__fast___memmovedownc_chk_defined */

#ifndef __fast___mempmove_chk_defined
#ifdef __fast_mempmove_defined
#define __fast___mempmove_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmove_chk))(/*aligned(1)*/ void *__dst,
                                                /*aligned(1)*/ void const *__src,
                                                __SIZE_TYPE__ __n_bytes,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("mempmove", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(mempmove)(__dst, __src, __n_bytes);
	}
	return __libc_core___mempmove_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_mempmove_defined */
#endif /* !__fast___mempmove_chk_defined */

#ifndef __fast___mempmoveup_chk_defined
#ifdef __fast_mempmoveup_defined
#define __fast___mempmoveup_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveup_chk))(/*aligned(1)*/ void *__dst,
                                                  /*aligned(1)*/ void const *__src,
                                                  __SIZE_TYPE__ __n_bytes,
                                                  __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("mempmoveup", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveup)(__dst, __src, __n_bytes);
	}
	return __libc_core___mempmoveup_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_mempmoveup_defined */
#endif /* !__fast___mempmoveup_chk_defined */

#ifndef __fast___mempmovedown_chk_defined
#ifdef __fast_mempmovedown_defined
#define __fast___mempmovedown_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovedown_chk))(/*aligned(1)*/ void *__dst,
                                                    /*aligned(1)*/ void const *__src,
                                                    __SIZE_TYPE__ __n_bytes,
                                                    __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__ssp_chk_dstbuf("mempmovedown", __dst, __n_bytes, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovedown)(__dst, __src, __n_bytes);
	}
	return __libc_core___mempmovedown_chk(__dst, __src, __n_bytes, __dst_objsize);
}
#endif /* __fast_mempmovedown_defined */
#endif /* !__fast___mempmovedown_chk_defined */

#ifndef __fast___mempmovec_chk_defined
#ifdef __fast_mempmovec_defined
#define __fast___mempmovec_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovec_chk))(/*aligned(1)*/ void *__dst,
                                                 /*aligned(1)*/ void const *__src,
                                                 __SIZE_TYPE__ __elem_count,
                                                 __SIZE_TYPE__ __elem_size,
                                                 __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("mempmovec", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovec)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___mempmovec_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_mempmovec_defined */
#endif /* !__fast___mempmovec_chk_defined */

#ifndef __fast___mempmoveupc_chk_defined
#ifdef __fast_mempmoveupc_defined
#define __fast___mempmoveupc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveupc_chk))(/*aligned(1)*/ void *__dst,
                                                   /*aligned(1)*/ void const *__src,
                                                   __SIZE_TYPE__ __elem_count,
                                                   __SIZE_TYPE__ __elem_size,
                                                   __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("mempmoveupc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveupc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___mempmoveupc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_mempmoveupc_defined */
#endif /* !__fast___mempmoveupc_chk_defined */

#ifndef __fast___mempmovedownc_chk_defined
#ifdef __fast_mempmovedownc_defined
#define __fast___mempmovedownc_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovedownc_chk))(/*aligned(1)*/ void *__dst,
                                                     /*aligned(1)*/ void const *__src,
                                                     __SIZE_TYPE__ __elem_count,
                                                     __SIZE_TYPE__ __elem_size,
                                                     __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__elem_count) && __builtin_constant_p(__elem_size)) {
		__ssp_chk_dstbuf("mempmovedownc", __dst, __elem_count * __elem_size, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovedownc)(__dst, __src, __elem_count, __elem_size);
	}
	return __libc_core___mempmovedownc_chk(__dst, __src, __elem_count, __elem_size, __dst_objsize);
}
#endif /* __fast_mempmovedownc_defined */
#endif /* !__fast___mempmovedownc_chk_defined */

#ifndef __fast___memsetw_chk_defined
#ifdef __fast_memsetw_defined
#define __fast___memsetw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memsetw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                               __UINT16_TYPE__ __word,
                                               __SIZE_TYPE__ __n_words,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("memsetw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(memsetw)(__dst, __word, __n_words);
	}
	return __libc_core___memsetw_chk(__dst, __word, __n_words, __dst_objsize);
}
#endif /* __fast_memsetw_defined */
#endif /* !__fast___memsetw_chk_defined */

#ifndef __fast___mempsetw_chk_defined
#ifdef __fast_mempsetw_defined
#define __fast___mempsetw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempsetw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                                __UINT16_TYPE__ __word,
                                                __SIZE_TYPE__ __n_words,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("mempsetw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(mempsetw)(__dst, __word, __n_words);
	}
	return __libc_core___mempsetw_chk(__dst, __word, __n_words, __dst_objsize);
}
#endif /* __fast_mempsetw_defined */
#endif /* !__fast___mempsetw_chk_defined */

#ifndef __fast___memcpyw_chk_defined
#ifdef __fast_memcpyw_defined
#define __fast___memcpyw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memcpyw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                               /*aligned(2)*/ void const *__restrict __src,
                                               __SIZE_TYPE__ __n_words,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("memcpyw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(memcpyw)(__dst, __src, __n_words);
	}
	return __libc_core___memcpyw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_memcpyw_defined */
#endif /* !__fast___memcpyw_chk_defined */

#ifndef __fast___mempcpyw_chk_defined
#ifdef __fast_mempcpyw_defined
#define __fast___mempcpyw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempcpyw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                                /*aligned(2)*/ void const *__restrict __src,
                                                __SIZE_TYPE__ __n_words,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("mempcpyw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(mempcpyw)(__dst, __src, __n_words);
	}
	return __libc_core___mempcpyw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_mempcpyw_defined */
#endif /* !__fast___mempcpyw_chk_defined */

#ifndef __fast___memmovew_chk_defined
#ifdef __fast_memmovew_defined
#define __fast___memmovew_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovew_chk))(/*aligned(2)*/ void *__dst,
                                                /*aligned(2)*/ void const *__src,
                                                __SIZE_TYPE__ __n_words,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("memmovew", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(memmovew)(__dst, __src, __n_words);
	}
	return __libc_core___memmovew_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_memmovew_defined */
#endif /* !__fast___memmovew_chk_defined */

#ifndef __fast___memmoveupw_chk_defined
#ifdef __fast_memmoveupw_defined
#define __fast___memmoveupw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveupw_chk))(/*aligned(2)*/ void *__dst,
                                                  /*aligned(2)*/ void const *__src,
                                                  __SIZE_TYPE__ __n_words,
                                                  __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("memmoveupw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveupw)(__dst, __src, __n_words);
	}
	return __libc_core___memmoveupw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_memmoveupw_defined */
#endif /* !__fast___memmoveupw_chk_defined */

#ifndef __fast___memmovedownw_chk_defined
#ifdef __fast_memmovedownw_defined
#define __fast___memmovedownw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovedownw_chk))(/*aligned(2)*/ void *__dst,
                                                    /*aligned(2)*/ void const *__src,
                                                    __SIZE_TYPE__ __n_words,
                                                    __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("memmovedownw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(memmovedownw)(__dst, __src, __n_words);
	}
	return __libc_core___memmovedownw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_memmovedownw_defined */
#endif /* !__fast___memmovedownw_chk_defined */

#ifndef __fast___mempmovew_chk_defined
#ifdef __fast_mempmovew_defined
#define __fast___mempmovew_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovew_chk))(/*aligned(2)*/ void *__dst,
                                                 /*aligned(2)*/ void const *__src,
                                                 __SIZE_TYPE__ __n_words,
                                                 __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("mempmovew", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovew)(__dst, __src, __n_words);
	}
	return __libc_core___mempmovew_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_mempmovew_defined */
#endif /* !__fast___mempmovew_chk_defined */

#ifndef __fast___mempmoveupw_chk_defined
#ifdef __fast_mempmoveupw_defined
#define __fast___mempmoveupw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveupw_chk))(/*aligned(2)*/ void *__dst,
                                                   /*aligned(2)*/ void const *__src,
                                                   __SIZE_TYPE__ __n_words,
                                                   __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("mempmoveupw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveupw)(__dst, __src, __n_words);
	}
	return __libc_core___mempmoveupw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_mempmoveupw_defined */
#endif /* !__fast___mempmoveupw_chk_defined */

#ifndef __fast___mempmovedownw_chk_defined
#ifdef __fast_mempmovedownw_defined
#define __fast___mempmovedownw_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovedownw_chk))(/*aligned(2)*/ void *__dst,
                                                     /*aligned(2)*/ void const *__src,
                                                     __SIZE_TYPE__ __n_words,
                                                     __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__ssp_chk_dstbuf("mempmovedownw", __dst, __n_words * 2, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovedownw)(__dst, __src, __n_words);
	}
	return __libc_core___mempmovedownw_chk(__dst, __src, __n_words, __dst_objsize);
}
#endif /* __fast_mempmovedownw_defined */
#endif /* !__fast___mempmovedownw_chk_defined */

#ifndef __fast___memsetl_chk_defined
#ifdef __fast_memsetl_defined
#define __fast___memsetl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memsetl_chk))(/*aligned(4)*/ void *__restrict __dst,
                                               __UINT32_TYPE__ __word,
                                               __SIZE_TYPE__ __n_dwords,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("memsetl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(memsetl)(__dst, __word, __n_dwords);
	}
	return __libc_core___memsetl_chk(__dst, __word, __n_dwords, __dst_objsize);
}
#endif /* __fast_memsetl_defined */
#endif /* !__fast___memsetl_chk_defined */

#ifndef __fast___mempsetl_chk_defined
#ifdef __fast_mempsetl_defined
#define __fast___mempsetl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempsetl_chk))(/*aligned(4)*/ void *__restrict __dst,
                                                __UINT32_TYPE__ __word,
                                                __SIZE_TYPE__ __n_dwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("mempsetl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(mempsetl)(__dst, __word, __n_dwords);
	}
	return __libc_core___mempsetl_chk(__dst, __word, __n_dwords, __dst_objsize);
}
#endif /* __fast_mempsetl_defined */
#endif /* !__fast___mempsetl_chk_defined */

#ifndef __fast___memcpyl_chk_defined
#ifdef __fast_memcpyl_defined
#define __fast___memcpyl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memcpyl_chk))(/*aligned(4)*/ void *__restrict __dst,
                                               /*aligned(4)*/ void const *__restrict __src,
                                               __SIZE_TYPE__ __n_dwords,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("memcpyl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(memcpyl)(__dst, __src, __n_dwords);
	}
	return __libc_core___memcpyl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_memcpyl_defined */
#endif /* !__fast___memcpyl_chk_defined */

#ifndef __fast___mempcpyl_chk_defined
#ifdef __fast_mempcpyl_defined
#define __fast___mempcpyl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempcpyl_chk))(/*aligned(4)*/ void *__restrict __dst,
                                                /*aligned(4)*/ void const *__restrict __src,
                                                __SIZE_TYPE__ __n_dwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("mempcpyl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(mempcpyl)(__dst, __src, __n_dwords);
	}
	return __libc_core___mempcpyl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_mempcpyl_defined */
#endif /* !__fast___mempcpyl_chk_defined */

#ifndef __fast___memmovel_chk_defined
#ifdef __fast_memmovel_defined
#define __fast___memmovel_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovel_chk))(/*aligned(4)*/ void *__dst,
                                                /*aligned(4)*/ void const *__src,
                                                __SIZE_TYPE__ __n_dwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("memmovel", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(memmovel)(__dst, __src, __n_dwords);
	}
	return __libc_core___memmovel_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_memmovel_defined */
#endif /* !__fast___memmovel_chk_defined */

#ifndef __fast___memmoveupl_chk_defined
#ifdef __fast_memmoveupl_defined
#define __fast___memmoveupl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveupl_chk))(/*aligned(4)*/ void *__dst,
                                                  /*aligned(4)*/ void const *__src,
                                                  __SIZE_TYPE__ __n_dwords,
                                                  __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("memmoveupl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveupl)(__dst, __src, __n_dwords);
	}
	return __libc_core___memmoveupl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_memmoveupl_defined */
#endif /* !__fast___memmoveupl_chk_defined */

#ifndef __fast___memmovedownl_chk_defined
#ifdef __fast_memmovedownl_defined
#define __fast___memmovedownl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovedownl_chk))(/*aligned(4)*/ void *__dst,
                                                    /*aligned(4)*/ void const *__src,
                                                    __SIZE_TYPE__ __n_dwords,
                                                    __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("memmovedownl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(memmovedownl)(__dst, __src, __n_dwords);
	}
	return __libc_core___memmovedownl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_memmovedownl_defined */
#endif /* !__fast___memmovedownl_chk_defined */

#ifndef __fast___mempmovel_chk_defined
#ifdef __fast_mempmovel_defined
#define __fast___mempmovel_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovel_chk))(/*aligned(4)*/ void *__dst,
                                                 /*aligned(4)*/ void const *__src,
                                                 __SIZE_TYPE__ __n_dwords,
                                                 __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("mempmovel", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovel)(__dst, __src, __n_dwords);
	}
	return __libc_core___mempmovel_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_mempmovel_defined */
#endif /* !__fast___mempmovel_chk_defined */

#ifndef __fast___mempmoveupl_chk_defined
#ifdef __fast_mempmoveupl_defined
#define __fast___mempmoveupl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveupl_chk))(/*aligned(4)*/ void *__dst,
                                                   /*aligned(4)*/ void const *__src,
                                                   __SIZE_TYPE__ __n_dwords,
                                                   __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("mempmoveupl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveupl)(__dst, __src, __n_dwords);
	}
	return __libc_core___mempmoveupl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_mempmoveupl_defined */
#endif /* !__fast___mempmoveupl_chk_defined */

#ifndef __fast___mempmovedownl_chk_defined
#ifdef __fast_mempmovedownl_defined
#define __fast___mempmovedownl_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovedownl_chk))(/*aligned(4)*/ void *__dst,
                                                     /*aligned(4)*/ void const *__src,
                                                     __SIZE_TYPE__ __n_dwords,
                                                     __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__ssp_chk_dstbuf("mempmovedownl", __dst, __n_dwords * 4, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovedownl)(__dst, __src, __n_dwords);
	}
	return __libc_core___mempmovedownl_chk(__dst, __src, __n_dwords, __dst_objsize);
}
#endif /* __fast_mempmovedownl_defined */
#endif /* !__fast___mempmovedownl_chk_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast___memsetq_chk_defined
#ifdef __fast_memsetq_defined
#define __fast___memsetq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memsetq_chk))(/*aligned(8)*/ void *__restrict __dst,
                                               __UINT64_TYPE__ __word,
                                               __SIZE_TYPE__ __n_qwords,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("memsetq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(memsetq)(__dst, __word, __n_qwords);
	}
	return __libc_core___memsetq_chk(__dst, __word, __n_qwords, __dst_objsize);
}
#endif /* __fast_memsetq_defined */
#endif /* !__fast___memsetq_chk_defined */

#ifndef __fast___mempsetq_chk_defined
#ifdef __fast_mempsetq_defined
#define __fast___mempsetq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempsetq_chk))(/*aligned(8)*/ void *__restrict __dst,
                                                __UINT64_TYPE__ __word,
                                                __SIZE_TYPE__ __n_qwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("mempsetq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(mempsetq)(__dst, __word, __n_qwords);
	}
	return __libc_core___mempsetq_chk(__dst, __word, __n_qwords, __dst_objsize);
}
#endif /* __fast_mempsetq_defined */
#endif /* !__fast___mempsetq_chk_defined */

#ifndef __fast___memcpyq_chk_defined
#ifdef __fast_memcpyq_defined
#define __fast___memcpyq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memcpyq_chk))(/*aligned(8)*/ void *__restrict __dst,
                                               /*aligned(8)*/ void const *__restrict __src,
                                               __SIZE_TYPE__ __n_qwords,
                                               __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("memcpyq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(memcpyq)(__dst, __src, __n_qwords);
	}
	return __libc_core___memcpyq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_memcpyq_defined */
#endif /* !__fast___memcpyq_chk_defined */

#ifndef __fast___mempcpyq_chk_defined
#ifdef __fast_mempcpyq_defined
#define __fast___mempcpyq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempcpyq_chk))(/*aligned(8)*/ void *__restrict __dst,
                                                /*aligned(8)*/ void const *__restrict __src,
                                                __SIZE_TYPE__ __n_qwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("mempcpyq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(mempcpyq)(__dst, __src, __n_qwords);
	}
	return __libc_core___mempcpyq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_mempcpyq_defined */
#endif /* !__fast___mempcpyq_chk_defined */

#ifndef __fast___memmoveq_chk_defined
#ifdef __fast_memmoveq_defined
#define __fast___memmoveq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveq_chk))(/*aligned(8)*/ void *__dst,
                                                /*aligned(8)*/ void const *__src,
                                                __SIZE_TYPE__ __n_qwords,
                                                __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("memmoveq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveq)(__dst, __src, __n_qwords);
	}
	return __libc_core___memmoveq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_memmoveq_defined */
#endif /* !__fast___memmoveq_chk_defined */

#ifndef __fast___memmoveupq_chk_defined
#ifdef __fast_memmoveupq_defined
#define __fast___memmoveupq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmoveupq_chk))(/*aligned(8)*/ void *__dst,
                                                  /*aligned(8)*/ void const *__src,
                                                  __SIZE_TYPE__ __n_qwords,
                                                  __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("memmoveupq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(memmoveupq)(__dst, __src, __n_qwords);
	}
	return __libc_core___memmoveupq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_memmoveupq_defined */
#endif /* !__fast___memmoveupq_chk_defined */

#ifndef __fast___memmovedownq_chk_defined
#ifdef __fast_memmovedownq_defined
#define __fast___memmovedownq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__memmovedownq_chk))(/*aligned(8)*/ void *__dst,
                                                    /*aligned(8)*/ void const *__src,
                                                    __SIZE_TYPE__ __n_qwords,
                                                    __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("memmovedownq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(memmovedownq)(__dst, __src, __n_qwords);
	}
	return __libc_core___memmovedownq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_memmovedownq_defined */
#endif /* !__fast___memmovedownq_chk_defined */

#ifndef __fast___mempmoveq_chk_defined
#ifdef __fast_mempmoveq_defined
#define __fast___mempmoveq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveq_chk))(/*aligned(8)*/ void *__dst,
                                                 /*aligned(8)*/ void const *__src,
                                                 __SIZE_TYPE__ __n_qwords,
                                                 __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("mempmoveq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveq)(__dst, __src, __n_qwords);
	}
	return __libc_core___mempmoveq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_mempmoveq_defined */
#endif /* !__fast___mempmoveq_chk_defined */

#ifndef __fast___mempmoveupq_chk_defined
#ifdef __fast_mempmoveupq_defined
#define __fast___mempmoveupq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmoveupq_chk))(/*aligned(8)*/ void *__dst,
                                                   /*aligned(8)*/ void const *__src,
                                                   __SIZE_TYPE__ __n_qwords,
                                                   __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("mempmoveupq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(mempmoveupq)(__dst, __src, __n_qwords);
	}
	return __libc_core___mempmoveupq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_mempmoveupq_defined */
#endif /* !__fast___mempmoveupq_chk_defined */

#ifndef __fast___mempmovedownq_chk_defined
#ifdef __fast_mempmovedownq_defined
#define __fast___mempmovedownq_chk_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(__mempmovedownq_chk))(/*aligned(8)*/ void *__dst,
                                                     /*aligned(8)*/ void const *__src,
                                                     __SIZE_TYPE__ __n_qwords,
                                                     __SIZE_TYPE__ __dst_objsize) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__ssp_chk_dstbuf("mempmovedownq", __dst, __n_qwords * 8, __dst_objsize);
		return __LIBC_FAST_NAME(mempmovedownq)(__dst, __src, __n_qwords);
	}
	return __libc_core___mempmovedownq_chk(__dst, __src, __n_qwords, __dst_objsize);
}
#endif /* __fast_mempmovedownq_defined */
#endif /* !__fast___mempmovedownq_chk_defined */

#endif /* __UINT64_TYPE__ */
//[[[end]]]

//TODO: [[libc, fast, ATTR_LEAF]] __strcat_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ dst_objsize) -> [[== buf]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}
//TODO: [[libc, fast, ATTR_LEAF]] __strcpy_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ dst_objsize) -> [[== buf]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}
//TODO: [[libc, fast, ATTR_LEAF]] __strncat_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ buflen, __SIZE_TYPE__ dst_objsize) -> [[== buf]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}
//TODO: [[libc, fast, ATTR_LEAF]] __strncpy_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ buflen, __SIZE_TYPE__ dst_objsize) -> [[== buf]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}
//TODO: [[libc, fast, ATTR_LEAF]] __stpcpy_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ dst_objsize) -> [[== buf + strlen(src)]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}
//TODO: [[libc, fast, ATTR_LEAF]] __stpncpy_chk:([[nonnull]] char *__restrict dst, [[nonnull]] char const *__restrict src, __SIZE_TYPE__ buflen, __SIZE_TYPE__ dst_objsize) -> [[== buf + strlen(src)]] char * %{auto_block(chk(*, (void)dst_objsize; /* TODO */))}

__NAMESPACE_FAST_END
__SYSDECL_END
#endif /* !__NO_ATTR_FORCEINLINE && !__NO_builtin_constant_p */

#endif /* !_OPTIMIZED_SSP_STRING_H */
