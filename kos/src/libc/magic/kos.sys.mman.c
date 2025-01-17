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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(dev_t = __dev_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = "__time_t")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <sys/mman.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt.except.system.mman")]


[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[doc_alias("mmap"), ignore, nocrt, alias("MMap")]]
void *MMap32([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
             __STDC_INT_AS_UINT_T flags, [[fdarg]] $fd_t fd, $pos32_t offset);

[[throws, wunused, doc_alias("mmap"), decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("MMap")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("MMap64")]]
[[userimpl, requires($has_function(MMap32) || $has_function(MMap64))]]
[[section(".text.crt.except.heap.mman")]]
void *MMap([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
           __STDC_INT_AS_UINT_T flags, [[fdarg]] $fd_t fd, $pos_t offset) {
@@pp_if $has_function(MMap64)@@
	return MMap64(addr, len, prot, flags, fd, (pos64_t)offset);
@@pp_else@@
	return MMap32(addr, len, prot, flags, fd, (pos32_t)offset);
@@pp_endif@@
}

[[throws, doc_alias("munmap"), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.except.heap.mman")]]
void MUnmap([[access(none)]] void *addr, size_t len);

[[throws, doc_alias("mprotect"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
void MProtect([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot);

[[cp, throws, doc_alias("msync"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
void MSync([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T flags);

[[throws, doc_alias("mlock"), decl_include("<hybrid/typecore.h>")]]
void MLock([[access(none)]] void const *addr, size_t len);

[[throws, doc_alias("munlock"), decl_include("<hybrid/typecore.h>")]]
void MUnlock([[access(none)]] void const *addr, size_t len);

[[throws, doc_alias("mlockall"), decl_include("<features.h>")]]
void MLockAll(__STDC_INT_AS_UINT_T flags);

[[throws, doc_alias("munlockall")]]
void MUnlockAll();

[[cp, throws, decl_include("<bits/types.h>"), requires_function(Open)]]
[[impl_include("<asm/os/paths.h>", "<asm/os/oflags.h>")]]
[[impl_include("<kos/parts/malloca.h>", "<libc/errno.h>")]]
[[impl_include("<bits/types.h>")]]
$fd_t ShmOpen([[in]] char const *name,
              $oflag_t oflags, mode_t mode) {
	fd_t result;
	char *fullname;
	size_t namelen;
@@pp_if defined(O_DOSPATH)@@
	if (oflags & O_DOSPATH) {
		while (*name == '/' || *name == '\\')
			++name;
	} else {
		while (*name == '/')
			++name;
	}
@@pp_elif defined(_WIN32)@@
	while (*name == '/' || *name == '\\')
		++name;
@@pp_else@@
	while (*name == '/')
		++name;
@@pp_endif@@
	namelen  = strlen(name);
	fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	memcpy(mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = Open(fullname, oflags, mode);
@@pp_if defined(ENOENT) && defined(O_CREAT) && $has_function(MkDir)@@
	if (result < 0 && (oflags & O_CREAT) != 0 && __libc_geterrno_or(ENOENT) == ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		MkDir(__PATH_SHM, 0777);
		result = Open(fullname, oflags, mode);
	}
@@pp_endif@@
	__freea(fullname);
	return result;
}

[[cp, throws, requires_function(Unlink)]]
[[impl_include("<asm/os/paths.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<kos/parts/malloca.h>")]]
void ShmUnlink([[in]] char const *name) {
	char *fullname;
	size_t namelen;
@@pp_ifdef _WIN32@@
	while (*name == '/' || *name == '\\')
		++name;
@@pp_else@@
	while (*name == '/')
		++name;
@@pp_endif@@
	namelen  = strlen(name);
	fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	memcpy(mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	Unlink(fullname);
	__freea(fullname);
}


%
%#ifdef __USE_MISC

[[throws, doc_alias("madvise")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[userimpl]]
void MAdvise([[access(none)]] void *addr, size_t len,
             __STDC_INT_AS_UINT_T advice) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
}

[[throws, doc_alias("mincore")]]
[[decl_include("<hybrid/typecore.h>")]]
void MInCore([[access(none)]] void *start, size_t len, unsigned char *vec);

%#endif /* __USE_MISC */


%
%#ifdef __USE_LARGEFILE64
[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[wunused, section(".text.crt.except.heap.mman")]]
[[doc_alias("mmap"), preferred_off64_variant_of(MMap)]]
[[userimpl, requires_function(MMap32)]]
void *MMap64([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
             __STDC_INT_AS_UINT_T flags, [[fdarg]] $fd_t fd, $pos64_t offset) {
	return MMap32(addr, len, prot, flags, fd, (pos32_t)offset);
}
%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_XOPEN2K

[[throws, doc_alias("posix_madvise")]]
[[userimpl, decl_include("<features.h>", "<hybrid/typecore.h>")]]
void PosixMAdvise([[access(none)]] void *addr, size_t len,
                  __STDC_INT_AS_UINT_T advice) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
}

%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_GNU

[[throws, doc_alias("mremap"), vartypes(void *)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt.except.heap.mman")]]
void *MRemap([[access(none)]] void *addr, size_t old_len, size_t new_len,
             __STDC_INT_AS_UINT_T flags, ... /* void *new_address */);

[[throws, doc_alias("remap_file_pages")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
void RemapFilePages([[access(none)]] void *start, size_t size,
                    __STDC_INT_AS_UINT_T prot, size_t pgoff,
                    __STDC_INT_AS_UINT_T flags);

[[throws, doc_alias("memfd_create"), decl_include("<bits/types.h>")]]
$fd_t MemFdCreate(char const *name, unsigned int flags);

[[throws, doc_alias("mlock2")]]
[[decl_include("<hybrid/typecore.h>")]]
void MLock2([[access(none)]] void const *addr, size_t length, unsigned int flags);

[[throws, doc_alias("pkey_alloc")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
int PKeyAlloc(unsigned int flags, unsigned int access_rights);

[[throws(E_INVALID_ARGUMENT_BAD_VALUE), doc_alias("pkey_set")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
[[impl_include("<asm/pkey.h>", "<kos/except/codes.h>", "<kos/except/reason/inval.h>")]]
[[requires_include("<asm/pkey.h>")]]
[[requires(defined(__ARCH_HAVE_PKEY) && $has_function(except_thrown))]]
void PKeySet(int pkey, unsigned int access_rights) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		except_thrown(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_BAD_VALUE@), 2, @E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_PKEY@, pkey);
	if unlikely(!__arch_pkey_verify_rights(access_rights))
		except_thrown(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_BAD_VALUE@), 2, @E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_ACCESS_RIGHTS@, access_rights);
	__arch_pkey_set(pkey, access_rights);
}

[[throws(E_INVALID_ARGUMENT_BAD_VALUE), doc_alias("pkey_get")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
[[impl_include("<asm/pkey.h>", "<kos/except/codes.h>", "<kos/except/reason/inval.h>")]]
[[requires_include("<asm/pkey.h>")]]
[[requires(defined(__ARCH_HAVE_PKEY) && $has_function(except_thrown))]]
unsigned int PKeyGet(int pkey) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		except_thrown(@EXCEPT_CODEOF@(@E_INVALID_ARGUMENT_BAD_VALUE@), 2, @E_INVALID_ARGUMENT_CONTEXT_PKEY_GET_PKEY@, pkey);
	return __arch_pkey_get(pkey);
}

[[throws, doc_alias("pkey_free")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
void PKeyFree(int pkey);

[[throws, doc_alias("pkey_mprotect"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
void PKeyMProtect([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot, int pkey);

%#endif /* __USE_GNU */



%{

__SYSDECL_END
#endif /* __CC__ */

}
