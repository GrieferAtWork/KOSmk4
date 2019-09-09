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
      F(kos, "raminfo", DT_REG, kos_raminfo)
      F_END)
MKREG_RO(kos_raminfo, 0444, ProcFS_Kos_RamInfo_Printer)

#define PROCFS_NO_CUSTOM 1 /* Delete if we ever get CUSTOM() entries */

#undef ROOT_DIRECTORY_ENTRY
#undef CUSTOM
#undef DYNAMIC_SYMLINK
#undef MKREG_RO
#undef MKDIR
