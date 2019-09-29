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


/* @param: files: Space-seperated list of:
 *                  `F(parent_id, name, type, id)'
 *                Terminated by `F_END'
 *                The specified `parent_id' must match the `id' argument
 *                passed to the surrounding `MKDIR()' invocation. */
#ifndef MKDIR
#define MKDIR(id, mode, files)
#endif /* !MKDIR */

#ifndef MKREG_RO
#define MKREG_RO(id, mode, printer)
#endif /* !MKREG_RO */

#ifndef MKREG_RW
#define MKREG_RW(id, mode, reader, writer)
#endif /* !MKREG_RW */

#ifndef DYNAMIC_SYMLINK
#define DYNAMIC_SYMLINK(id, mode, readlink)
#endif /* !DYNAMIC_SYMLINK */

#ifndef CUSTOM
#define CUSTOM(id, inode_type)
#endif /* !CUSTOM */

#ifndef ROOT_DIRECTORY_ENTRY
#define ROOT_DIRECTORY_ENTRY(name, type, id)
#endif /* !ROOT_DIRECTORY_ENTRY */


ROOT_DIRECTORY_ENTRY("self", DT_LNK, self)
DYNAMIC_SYMLINK(self, 0777, ProcFS_Self_Printer)

ROOT_DIRECTORY_ENTRY("thread-self", DT_LNK, thread_self)
DYNAMIC_SYMLINK(thread_self, 0777, ProcFS_ThreadSelf_Printer)

ROOT_DIRECTORY_ENTRY("kcore", DT_REG, kcore)
MKREG_RO(kcore, 0400, ProcFS_KCore_Printer)

ROOT_DIRECTORY_ENTRY("cmdline", DT_REG, cmdline)
MKREG_RO(cmdline, 0444, ProcFS_Cmdline_Printer)

ROOT_DIRECTORY_ENTRY("kos", DT_DIR, kos)
MKDIR(kos, 0555,
      F(kos, "raminfo", DT_REG, kos_raminfo) /* /proc/kos/raminfo */
      F_END)
MKREG_RO(kos_raminfo, 0444, ProcFS_Kos_RamInfo_Printer)

ROOT_DIRECTORY_ENTRY("sys", DT_DIR, sys)

MKDIR(sys, 0555,
      F(sys, "fs", DT_DIR, sys_fs)         /* /proc/sys/fs */
      F(sys, "kernel", DT_DIR, sys_kernel) /* /proc/sys/kernel */
      F_END)

MKDIR(sys_fs, 0555,
      F(sys_fs, "pipe-max-size", DT_REG, sys_fs_pipe_max_size) /* /proc/sys/fs/pipe-max-size */
      F_END)
MKREG_RW(sys_fs_pipe_max_size, 0622, ProcFS_Sys_Fs_PipeMaxSize_Print, ProcFS_Sys_Fs_PipeMaxSize_Write)

MKDIR(sys_kernel, 0555,
      F(sys_kernel, "hostname", DT_REG, sys_kernel_hostname)
      F(sys_kernel, "domainname", DT_REG, sys_kernel_domainname)
      F(sys_kernel, "randomize_va_space", DT_REG, sys_kernel_randomize_va_space)
      F_END)
MKREG_RW(sys_kernel_hostname, 0622, ProcFS_Sys_Kernel_Hostname_Print, ProcFS_Sys_Kernel_Hostname_Write)
MKREG_RW(sys_kernel_domainname, 0622, ProcFS_Sys_Kernel_Domainname_Print, ProcFS_Sys_Kernel_Domainname_Write)
MKREG_RW(sys_kernel_randomize_va_space, 0622, ProcFS_Sys_Kernel_RandomizeVaSpace_Print, ProcFS_Sys_Kernel_RandomizeVaSpace_Write)


#define PROCFS_NO_CUSTOM 1 /* Delete if we ever get CUSTOM() entries */

#undef ROOT_DIRECTORY_ENTRY
#undef CUSTOM
#undef DYNAMIC_SYMLINK
#undef MKREG_RW
#undef MKREG_RO
#undef MKDIR
