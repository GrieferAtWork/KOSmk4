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
#ifndef _KOS_KSYSCTL_H
#define _KOS_KSYSCTL_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/hop/openfd.h>

#ifdef __CC__
#ifndef NO_KSYSCTL_HELPER_FUNCTIONS
#if defined(__CRT_HAVE_ksysctl) || defined(__CRT_HAVE_KSysctl)
#include <libc/string.h>
#endif /* __CRT_HAVE_ksysctl || __CRT_HAVE_KSysctl */
#endif /* !NO_KSYSCTL_HELPER_FUNCTIONS */
#endif /* __CC__ */

__SYSDECL_BEGIN

/* Special SYStemConTroL control codes for KOS.
 * These are function codes with may be used alongside
 * the `ksysctl()' system call provided by the KOSmk4 kernel.
 * WARNING: The interface exposed here is _extremely_ volatile!
 *          It may be changed without notice, get removed, or changed in other
 *          ways that may break existing code using it. - Use with caution! */
#if __SIZEOF_POINTER__ < 8
#define __KSYSCTL_PAD_POINTER(name) __uint32_t name;
#else /* __SIZEOF_POINTER__ < 8 */
#define __KSYSCTL_PAD_POINTER(name) /* nothing */
#endif /* __SIZEOF_POINTER__ >= 8 */


/* Kernel system control command codes. (For use with `ksysctl()') */

#define KSYSCTL_DRIVER_FORMAT_BLOB  1 /* Load a driver from an given data-blob (which should represent a valid ELF binary)
                                       * For more information on driver binaries, see the documentation in <kernel/driver.h> */
#define KSYSCTL_DRIVER_FORMAT_FILE  2 /* Load a driver from a given INode handle (or INode-compatible handle) */
#define KSYSCTL_DRIVER_FORMAT_NAME  3 /* Load a driver, given its name (either an absolute filename, or a
                                       * filename that is interpreted relative to the active driver library
                                       * path list (s.a. `KSYSCTL_DRIVER_(GET|SET)_LIBRARY_PATH')) */


#define KSYSCTL_DRIVER_INSMOD_FNORMAL 0x0000 /* Normal insmod flags. */
#define KSYSCTL_DRIVER_INSMOD_FNOINIT 0x0001 /* Don't initialize the driver (don't load dependencies, apply relocations, or run initializers).
                                              * When this flag is set, the caller must use `HOP_DRIVER_INITIALIZE()'
                                              * at some point in the future in order to initialize the driver.
                                              * NOTE: This flag is mainly intended to allow for inter-driver
                                              *       dependencies when multiple drivers are loaded from the
                                              *       bootloader, in which case all drivers must be loaded
                                              *       first, before they can detect each other as dependencies. */


#define __OFFSET_KSYSCTL_DRIVER_INSMOD_STRUCT_SIZE 0
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_FLAGS       4
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_FORMAT      8
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_NEWDRIVER   12
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_CMDLINE     16
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_DRIVER      24
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_BLOB_BASE   32 /* [FIELD(im_blob.b_base)] */
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_BLOB_SIZE   40 /* [FIELD(im_blob.b_size)] */
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_NODE   32 /* [FIELD(im_file.f_node)] */
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_PATH   36 /* [FIELD(im_file.f_path)] */
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_DENTRY 40 /* [FIELD(im_file.f_dentry)] */
#define __OFFSET_KSYSCTL_DRIVER_INSMOD_NAME        32
#define __SIZEOF_KSYSCTL_DRIVER_INSMOD             48
#ifdef __CC__
struct ksysctl_driver_insmod /*[PREFIX(im_)]*/ {
	__uint32_t             im_struct_size;     /* [== sizeof(struct ksysctl_driver_insmod)]
	                                            * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                            * this value is too small or doesn't match any recognized
	                                            * structure version. */
	__uint32_t             im_flags;           /* Driver load flags (Set of `KSYSCTL_DRIVER_INSMOD_F*') */
	__uint32_t             im_format;          /* Driver load format (One of `KSYSCTL_DRIVER_FORMAT_*') */
	__uint8_t              im_newdriver;       /* [OUT] Set to `1' if a new driver was loaded.
	                                            *       Otherwise set to `0' if another driver with an
	                                            *       identical name had already been loaded before. */
	__uint8_t            __im_pad1[3];         /* ... */
	char const            *im_cmdline;         /* [0..1] Commandline for the driver. */
	__KSYSCTL_PAD_POINTER(__im_pad2);           /* ... */
	struct hop_openfd     *im_driver;          /* [OUT|OPT] A handle to the loaded driver. */
	__KSYSCTL_PAD_POINTER(__im_pad3);           /* ... */
	union {
		struct {
			void const *b_base;               /* [1..b_size] Base address of the blob.
			                                   * NOTE: This should point to an `ElfW(Ehdr)' structure. */
			__KSYSCTL_PAD_POINTER(__b_pad1);
			__size_t    b_size;               /* Size of the blob (in bytes). */
			__KSYSCTL_PAD_POINTER(__b_pad2);
		}              im_blob;               /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_BLOB)]
		                                       * Data blob from which to load the driver. */
		struct {
			__uint32_t f_node;                /* [1..1] Handle to an INode from which the driver should be loaded. */
			__uint32_t f_path;                /* [0..1] Handle to the path containing `f_node', or (uint32_t)-1 if not given
			                                   * When not given, the kernel will try to retrieve the path from `f_node' */
			__uint32_t f_dentry;              /* [0..1] Handle to the directory entry describing `f_node', or (uint32_t)-1 if not given
			                                   * When not given, the kernel will try to retrieve the directory entry from `f_node' */
		}              im_file;               /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_FILE)]
		                                       * File handle data. */
		char const    *im_name;               /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_NAME)]
		                                       * [1..1] Name of the driver that should be loaded.
		                                       * If this string starts with '/', it is the absolute filename
		                                       * of the driver, loaded relative to the system root VFS, as
		                                       * can be opened by `KSYSCTL_OPEN_KERNEL_VFS' */
	};
};
#endif /* __CC__ */


/* Sysctl return values for `KSYSCTL_DRIVER_DELMOD' / `KSYSCTL_DRIVER_DELMOD_N' */
#define KSYSCTL_DRIVER_DELMOD_SUCCESS  0 /* Successfully unloaded the driver. */
#define KSYSCTL_DRIVER_DELMOD_UNKNOWN  1 /* The specified driver could not be found. */
#define KSYSCTL_DRIVER_DELMOD_INUSE    2 /* The specified driver has unaccounted references.
                                          * NOTE: in this case, driver finalizers were still executed,
                                          *       meaning that in all likelihood, the unaccounted references
                                          *       stem from another thread currently holding a reference to
                                          *       the driver, such as when trying to resolve addr2line for
                                          *       a static pointer apart of the driver's binary image. */

/* Delmod flags. */
#define KSYSCTL_DRIVER_DELMOD_FNORMAL   0x0000 /* Normal delmod flags. */
#define KSYSCTL_DRIVER_DELMOD_FDEPEND   0x0001 /* Also delete drivers that have dependencies on the given driver */
#define KSYSCTL_DRIVER_DELMOD_FFORCE    0x0200 /* Force unload the driver, even if unaccounted references remain
                                                * WARNING: Doing this may compromise system integrity! */
#define KSYSCTL_DRIVER_DELMOD_FNONBLOCK 0x0800 /* Don't wait for the driver to fully go away.
                                                * Instead, the driver will have gone away once it can no longer be
                                                * enumerated. In the event that the driver has a (possibly intentional)
                                                * reference leak, you must use `KSYSCTL_DRIVER_DELMOD_FFORCE' to
                                                * unload the driver (though doing this is _very_ dangerous) */
#define __OFFSET_KSYSCTL_DRIVER_DELMOD_STRUCT_SIZE 0
#define __OFFSET_KSYSCTL_DRIVER_DELMOD_FORMAT      4
#define __OFFSET_KSYSCTL_DRIVER_DELMOD_FLAGS       6
#define __OFFSET_KSYSCTL_DRIVER_DELMOD_FILE        8
#define __OFFSET_KSYSCTL_DRIVER_DELMOD_NAME        8
#define __SIZEOF_KSYSCTL_DRIVER_DELMOD             16
#ifdef __CC__
struct ksysctl_driver_delmod /*[PREFIX(dm_)]*/ {
	__uint32_t         dm_struct_size;     /* [== sizeof(struct ksysctl_driver_delmod)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	__uint16_t         dm_format;          /* Driver format (One of `KSYSCTL_DRIVER_FORMAT_*') */
	__uint16_t         dm_flags;           /* Delmod flags (Set of `KSYSCTL_DRIVER_DELMOD_F*') */
	union {
		__uint32_t     dm_file;            /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_FILE)]
		                                    * Handle to an INode from which the driver was loaded. */
		char const    *dm_name;            /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_NAME)]
		                                    * [1..1] Name of the driver to unload.
		                                    * If this string starts with '/', it is the absolute filename
		                                    * of the driver, loaded relative to the system root VFS, as
		                                    * can be opened by `KSYSCTL_OPEN_KERNEL_VFS' */
	};
	__KSYSCTL_PAD_POINTER(__dm_pad1);      /* ... */
};
#endif /* __CC__ */


#define __OFFSET_KSYSCTL_DRIVER_GETMOD_STRUCT_SIZE 0
#define __OFFSET_KSYSCTL_DRIVER_GETMOD_FORMAT      4
#define __OFFSET_KSYSCTL_DRIVER_GETMOD_DRIVER      8
#define __OFFSET_KSYSCTL_DRIVER_GETMOD_ADDR        16
#define __OFFSET_KSYSCTL_DRIVER_GETMOD_FILE        16
#define __OFFSET_KSYSCTL_DRIVER_GETMOD_NAME        16
#define __SIZEOF_KSYSCTL_DRIVER_GETMOD             24
#ifdef __CC__
struct ksysctl_driver_getmod /*[PREFIX(gm_)]*/ {
	__uint32_t             gm_struct_size; /* [== sizeof(struct ksysctl_driver_getmod)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	__uint16_t             gm_format;      /* Driver format (One of `KSYSCTL_DRIVER_FORMAT_*') */
	__uint16_t           __gm_pad1;
	struct hop_openfd      gm_driver;      /* [OUT] A handle to the loaded driver. */
	union {
		void              *gm_addr;        /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_BLOB)]
		                                    * A pointer apart of the driver's static binary image. */
		__uint32_t         gm_file;        /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_FILE)]
		                                    * Handle to an INode from which the driver should be loaded. */
		char const        *gm_name;        /* [valid_if(im_format == KSYSCTL_DRIVER_FORMAT_NAME)]
		                                    * [1..1] Name of the driver to lookup.
		                                    * If this string starts with '/', it is the absolute filename
		                                    * of the driver, loaded relative to the system root VFS, as
		                                    * can be opened by `KSYSCTL_OPEN_KERNEL_VFS' */
	};
	__KSYSCTL_PAD_POINTER(__gm_pad2);      /* ... */
};
#endif /* __CC__ */


#define __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_STRUCT_SIZE 0
#define __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_BUF         8
#define __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_SIZE        16
#define __SIZEOF_KSYSCTL_DRIVER_GET_LIBRARY_PATH             24
#ifdef __CC__
struct ksysctl_driver_get_library_path /*[PREFIX(glp_)]*/ {
	__uint32_t              glp_struct_size; /* [== sizeof(struct ksysctl_driver_get_library_path)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t            __glp_pad1;        /* ... */
	char                   *glp_buf;         /* [1..glp_size] User-space buffer to-be filled with the library path. */
	__KSYSCTL_PAD_POINTER(__glp_pad2);       /* ... */
	__size_t                glp_size;        /* [IN] Available buffer size (in bytes).
	                                          * [OUT] Required buffer size (in bytes; including a trailing NUL) */
	__KSYSCTL_PAD_POINTER(__glp_pad3);       /* ... */
};
#endif /* __CC__ */


/* Restore the default driver library path */
#define KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT (__CCAST(char const *)-1)

#define __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_STRUCT_SIZE 0
#define __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_NEWPATH     8
#define __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_OLDPATH     16
#define __SIZEOF_KSYSCTL_DRIVER_SET_LIBRARY_PATH             24
#ifdef __CC__
struct ksysctl_driver_set_library_path /*[PREFIX(slp_)]*/ {
	__uint32_t              slp_struct_size; /* [== sizeof(struct ksysctl_driver_set_library_path)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t            __slp_pad1;        /* ... */
	char const             *slp_newpath;     /* [1..1] The new library path to-be set (':' - separated list of paths).
	                                          * Separately, you may specify `KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT' for
	                                          * this field to restore the default library path (as set during booting
	                                          * when no `driver-libpath=...' option was passed) */
	__KSYSCTL_PAD_POINTER(__slp_pad2);       /* ... */
	char const             *slp_oldpath;     /* [0..1] The expected old library path.
	                                          * When non-NULL, only allow `slp_newpath' to-be set when the old path
	                                          * is equal to this value (this exchange is done atomically and allows
	                                          * the user to implement compare-exchange semantics for setting the driver
	                                          * library path, thus allowing user-code to add/remove individual paths
	                                          * without causing a potential race condition with other software which
	                                          * may be attempting to do the same) */
	__KSYSCTL_PAD_POINTER(__slp_pad3);       /* ... */
};
#endif /* __CC__ */
#undef __KSYSCTL_PAD_POINTER

/* KOS extensions */
#define KSYSCTL_UAIO_CREATE 0xe0010001 /* [syscall_ulong_t uaio_flags = UAIO_CREATE_*] Create and return a new UAIO object. */

/* Generic kernel house-keeping */
#define KSYSCTL_SYSTEM_CLEARCACHES             0xc05e0001 /* Invoke cache clear callbacks for each and every globally reachable
                                                           * component within the entire kernel.
                                                           * This function is called when the kernel has run out of physical/virtual
                                                           * memory, or some other kind of limited, and dynamically allocatable resource.
                                                           * @return: * : At least some amount of some kind of resource was released.
                                                           *              In this case the caller should re-attempt whatever lead them
                                                           *              to try and clear caches to reclaim resource (usually memory)
                                                           * @return: 0 : Nothing was released/freed.
                                                           *              In this case, the caller should indicate failure due to
                                                           *              lack of some necessary resource. */
#define KSYSCTL_SYSTEM_TRIMHEAPS               0xc05e0002 /* Trim known kernel-space heaps (also done as part of `KSYSCTL_SYSTEM_CLEARCACHES'; return the total number of trimmed bytes) */
#define KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS       0xc05ed001 /* Dump kernel-space memory leaks to the system log (return the number of leaked allocations) */
#define KSYSCTL_SYSTEM_MEMORY_VALIDATE_PADDING 0xc05ed002 /* Validate heap padding and panic if memory has been corrupted */
#define KSYSCTL_SYSTEM_BRANCH_DUMP_STATS       0xc05ef001 /* Dump kernel branch statistics to the system log */

/* Kernel configuration */
#define KSYSCTL_SYSCALL_GET_PERSONALITY        0x005f0001 /* [int kp << 1] Return 0/1 if the given personality code `kp' (one of `KP_*' from `<kos/personality>') is enabled or not. */
#define KSYSCTL_SYSCALL_SET_PERSONALITY        0x005f0002 /* [int kp << 1 | (enabled & 1)] Enable/Disable the given personality `kp'. (return 0/1 indicative of the old state) */

/* Driver related */
#define KSYSCTL_DRIVER_LSMOD                   0x000d0001 /* [struct hop_openfd *result] Capture a snapshot of all currently loaded kernel
                                                           * drivers, and return a `HANDLE_TYPE_DRIVER_STATE' handle for that snapshot.
                                                           * WARNING: None of the drivers loaded at the point this call is made can be
                                                           *          fully unloaded before the returned handle has been closed!
                                                           * @return: == result->of_hint */
#define KSYSCTL_DRIVER_INSMOD                  0x000d0002 /* [struct ksysctl_driver_insmod *data] Load a new driver into the kernel.
                                                           * @return: == data->im_driver ? data->im_driver->of_hint : 0 */
#define KSYSCTL_DRIVER_DELMOD                  0x000d0003 /* [struct ksysctl_driver_delmod *data] Delete a driver from the kernel.
                                                           * @return: * : One of `KSYSCTL_DRIVER_DELMOD_*' */
#define KSYSCTL_DRIVER_GETMOD                  0x000d0004 /* [struct ksysctl_driver_getmod *data] Lookup an existing driver.
                                                           * @return: == data->gm_driver.of_hint: Successfully found the driver (a handle was opened in `data->gm_driver')
                                                           * @return: -ENOENT: No such driver exists. */
#define KSYSCTL_DRIVER_GET_LIBRARY_PATH        0x000d0005 /* [struct ksysctl_driver_get_library_path *data] Read the kernel driver library path. */
#define KSYSCTL_DRIVER_SET_LIBRARY_PATH        0x000d0006 /* [struct ksysctl_driver_set_library_path *data] Set the kernel driver library path.
                                                           * @return: 0 :      Successfully set the new driver library path.
                                                           * @return: -EPERM: `glp_oldpath' was given, but the currently set path was different */
/* TODO: Wrapper for `block_device_lookup' */
/* TODO: Wrapper for `block_device_lookup_name' */
/* TODO: Wrapper for `character_device_lookup' */
/* TODO: Wrapper for `character_device_lookup_name' */

#define KSYSCTL_OPEN_KERNEL_VFS                0xfffe0001 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_PATH' to `vfs_kernel'
                                                           * @return: == result->of_hint */
#define KSYSCTL_OPEN_KERNEL_FS                 0xfffe0002 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_FS' to `fs_kernel'
                                                           * @return: == result->of_hint */
#define KSYSCTL_OPEN_KERNEL_VM                 0xfffe0003 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_VM' to `vm_kernel'
                                                           * @return: == result->of_hint */
#define KSYSCTL_OPEN_KERNEL_DRIVER             0xfffe0004 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_DRIVER' to `kernel_driver'
                                                           * @return: == result->of_hint */
#define KSYSCTL_OPEN_ROOT_PIDNS                0xfffe0005 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_PIDNS' to `pidns_root'
                                                           * @return: == result->of_hint */
#define KSYSCTL_OPEN_BOOT_TASK                 0xfffe0006 /* [struct hop_openfd *result] Open a handle `HANDLE_TYPE_TASK' to `_boottask'
                                                           * @return: == result->of_hint */


#ifdef __CC__

/* Perform a handle operation specified by `cmd'
 * @param: CMD: One of `KSYSCTL_*' (see above) */
#ifndef __ksysctl_defined
#ifdef __CRT_HAVE_ksysctl
#define __ksysctl_defined 1
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL ksysctl)(__syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("ksysctl");
#endif /* __CRT_HAVE_ksysctl */
#endif /* !__ksysctl_defined */
#ifndef __KSysctl_defined
#ifdef __CRT_HAVE_KSysctl
#define __KSysctl_defined 1
__LIBC __syscall_slong_t (__VLIBCCALL KSysctl)(__syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("KSysctl");
#endif /* __CRT_HAVE_KSysctl */
#endif /* !__KSysctl_defined */

#ifndef NO_KSYSCTL_HELPER_FUNCTIONS
#ifdef __ksysctl_defined

__LOCAL int
__NOTHROW_NCX(__LIBCCALL ksysctl_insmod)(char const *__driver_name,
                                         char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size = sizeof(__args);
	__args.im_flags       = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format      = KSYSCTL_DRIVER_FORMAT_NAME;
	__args.im_cmdline     = __driver_cmdline;
	__args.im_name        = __driver_name;
	return (int)ksysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL int
__NOTHROW_NCX(__LIBCCALL ksysctl_insmodf)(__fd_t __driver_file,
                                          char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size   = sizeof(__args);
	__args.im_flags         = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format        = KSYSCTL_DRIVER_FORMAT_FILE;
	__args.im_cmdline       = __driver_cmdline;
	__args.im_file.f_node   = __driver_file;
	__args.im_file.f_path   = (__uint32_t)-1;
	__args.im_file.f_dentry = (__uint32_t)-1;
	return (int)ksysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL int
__NOTHROW_NCX(__LIBCCALL ksysctl_insmodb)(void const *__driver_blob, __size_t __driver_size,
                                          char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size = sizeof(__args);
	__args.im_flags       = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format      = KSYSCTL_DRIVER_FORMAT_BLOB;
	__args.im_cmdline     = __driver_cmdline;
	__args.im_blob.b_base = __driver_blob;
	__args.im_blob.b_size = __driver_size;
	return (int)ksysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL int
__NOTHROW_NCX(__LIBCCALL ksysctl_delmod)(char const *__driver_name) {
	struct ksysctl_driver_delmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.dm_struct_size = sizeof(__args);
	__args.dm_flags       = KSYSCTL_DRIVER_DELMOD_FNORMAL;
	__args.dm_format      = KSYSCTL_DRIVER_FORMAT_NAME;
	__args.dm_name        = __driver_name;
	return (int)ksysctl(KSYSCTL_DRIVER_DELMOD, &__args);
}

/* @return: * : Required buffer size. */
__LOCAL __ssize_t
__NOTHROW_NCX(__LIBCCALL ksysctl_get_driver_library_path)(char *__buf, __size_t __bufsize) {
	struct ksysctl_driver_get_library_path __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.glp_struct_size = sizeof(__args);
	__args.glp_buf         = __buf;
	__args.glp_size        = __bufsize;
	if (ksysctl(KSYSCTL_DRIVER_GET_LIBRARY_PATH, &__args) < 0)
		return -1;
	return (__ssize_t)__args.glp_size;
}

/* @param: PATH: The set path to assign, or `KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT'
 *               if the default path should be restored (as set during booting
 *               when no `driver-libpath=...' option was passed) */
__LOCAL int
__NOTHROW_NCX(__LIBCCALL ksysctl_set_driver_library_path)(char const *__path) {
	struct ksysctl_driver_set_library_path __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.slp_struct_size = sizeof(__args);
	__args.slp_newpath     = __path;
	return (int)ksysctl(KSYSCTL_DRIVER_SET_LIBRARY_PATH, &__args);
}

#endif /* __ksysctl_defined */


#ifdef __KSysctl_defined

__LOCAL void __LIBCCALL
KSysctlInsmod(char const *__driver_name,
              char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size = sizeof(__args);
	__args.im_flags       = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format      = KSYSCTL_DRIVER_FORMAT_NAME;
	__args.im_cmdline     = __driver_cmdline;
	__args.im_name        = __driver_name;
	KSysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL void __LIBCCALL
KSysctlInsmodf(__fd_t __driver_file,
               char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size   = sizeof(__args);
	__args.im_flags         = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format        = KSYSCTL_DRIVER_FORMAT_FILE;
	__args.im_cmdline       = __driver_cmdline;
	__args.im_file.f_node   = __driver_file;
	__args.im_file.f_path   = (__uint32_t)-1;
	__args.im_file.f_dentry = (__uint32_t)-1;
	KSysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL void __LIBCCALL
KSysctlInsmodb(void const *__driver_blob, __size_t __driver_size,
               char const *__driver_cmdline __DFL(__NULLPTR)) {
	struct ksysctl_driver_insmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.im_struct_size = sizeof(__args);
	__args.im_flags       = KSYSCTL_DRIVER_INSMOD_FNORMAL;
	__args.im_format      = KSYSCTL_DRIVER_FORMAT_BLOB;
	__args.im_cmdline     = __driver_cmdline;
	__args.im_blob.b_base = __driver_blob;
	__args.im_blob.b_size = __driver_size;
	KSysctl(KSYSCTL_DRIVER_INSMOD, &__args);
}

__LOCAL void __LIBCCALL KSysctlDelmod(char const *__driver_name,
                                      unsigned int __flags __DFL(KSYSCTL_DRIVER_DELMOD_FNORMAL)) {
	struct ksysctl_driver_delmod __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.dm_struct_size = sizeof(__args);
	__args.dm_flags       = __flags;
	__args.dm_format      = KSYSCTL_DRIVER_FORMAT_NAME;
	__args.dm_name        = __driver_name;
	KSysctl(KSYSCTL_DRIVER_DELMOD, &__args);
}

/* @return: * : Required buffer size. */
__LOCAL __size_t __LIBCCALL
KSysctlGetDriverLibraryPath(char *__buf, __size_t __bufsize) {
	struct ksysctl_driver_get_library_path __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.glp_struct_size = sizeof(__args);
	__args.glp_buf         = __buf;
	__args.glp_size        = __bufsize;
	KSysctl(KSYSCTL_DRIVER_GET_LIBRARY_PATH, &__args);
	return __args.glp_size;
}

/* @param: PATH: The set path to assign, or `KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT'
 *               if the default path should be restored (as set during booting
 *               when no `driver-libpath=...' option was passed) */
__LOCAL void __LIBCCALL
KSysctlSetDriverLibraryPath(char const *__path) {
	struct ksysctl_driver_set_library_path __args;
	__libc_memset(&__args, 0, sizeof(__args));
	__args.slp_struct_size = sizeof(__args);
	__args.slp_newpath     = __path;
	KSysctl(KSYSCTL_DRIVER_SET_LIBRARY_PATH, &__args);
}

#endif /* __KSysctl_defined */
#endif /* !NO_KSYSCTL_HELPER_FUNCTIONS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_KSYSCTL_H */
