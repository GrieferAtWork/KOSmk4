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
#ifndef GUARD_KERNEL_INCLUDE_FS_NODE_H
#define GUARD_KERNEL_INCLUDE_FS_NODE_H 1

#include <kernel/compiler.h>

/* TODO: Deprecated header! */
#include <kernel/fs/blkdev.h>
#include <kernel/fs/chrdev.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>

#define superblock_getmountloc(super, vfs) ((struct path *)vfs_mount_location(vfs, &(super)->fs_root))

/* struct fdirent */
#define de_refcnt  fd_refcnt
#define de_ino     fd_ino
#define de_hash    fd_hash
#define de_namelen fd_namelen
#define de_type    fd_type
#define de_name    fd_name

#define INODE_FNORMAL                                              MFILE_F_NORMAL
#define INODE_FPERSISTENT                                          MFILE_F_PERSISTENT
#define INODE_FCHANGED                                             MFILE_F_CHANGED
#define INODE_FATTRCHANGED                                         MFILE_F_ATTRCHANGED
#define INODE_FDELETED                                             MFILE_F_DELETED
#define vm_datablock_isinode                                       mfile_isnode
#define i_type                                                     _fnode_file_ mf_ops
#define i_super                                                    fn_super
#define i_flags                                                    _fnode_file_ mf_flags
#define i_fileino                                                  fn_ino
#define i_filesize                                                 _fnode_file_ mf_filesize.
#define i_filemode                                                 fn_mode
#define i_filenlink                                                fn_nlink
#define i_fileuid                                                  fn_uid
#define i_filegid                                                  fn_gid
#define i_filerdev                                                 dn_devno
#define i_fileatime                                                _fnode_file_ mf_atime
#define i_filemtime                                                _fnode_file_ mf_mtime
#define i_filectime                                                _fnode_file_ mf_ctime
#define i_fsdata                                                   fn_fsdata
#define INODE_ISSUPER                                              fnode_issuper
#define INODE_ISREG                                                fnode_isreg
#define INODE_ISDIR                                                fnode_isdir
#define INODE_ISLNK                                                fnode_islnk
#define INODE_ISFIFO                                               fnode_isfifo
#define INODE_ISSOCK                                               fnode_issock
#define inode_readk                                                mfile_read
#define inode_read                                                 mfile_read
#define inode_readv(self, buf, num_bytes, file_position)           mfile_readv(self, buf, 0, num_bytes, file_position)
#define inode_writek                                               mfile_write
#define inode_write                                                mfile_write
#define inode_writev(self, buf, num_bytes, file_position)          mfile_writev(self, buf, 0, num_bytes, file_position)
#define inode_readallk                                             mfile_readall
#define inode_readall                                              mfile_readall
#define inode_read_phys                                            mfile_read_p
#define inode_readv_phys(self, buf, num_bytes, file_position)      mfile_readv_p(self, buf, 0, num_bytes, file_position)
#define inode_write_phys                                           mfile_write_p
#define inode_writev_phys(self, buf, num_bytes, file_position)     mfile_writev_p(self, buf, 0, num_bytes, file_position)
#define inode_readall_phys                                         mfile_readall_p
#define inode_readallv_phys(self, buf, num_bytes, file_position)   mfile_readallv_p(self, buf, 0, num_bytes, file_position)
#define inode_read_blocking                                        mfile_tailread
#define inode_readv_blocking(self, buf, num_bytes, file_position)  mfile_tailreadv(self, buf, 0, num_bytes, file_position)
#define inode_pread_blocking                                       mfile_tailread_p
#define inode_preadv_blocking(self, buf, num_bytes, file_position) mfile_tailreadv_p(self, buf, 0, num_bytes, file_position)
#define inode_changed                                              mfile_changed
#define inode_changedattr(self)                                    mfile_changed(self, MFILE_F_ATTRCHANGED)
#define inode_loadattr(self)                                       (void)0
#define inode_access                                               fnode_access
#define inode_truncate                                             mfile_truncate
#define inode_ioctl                                                mfile_uioctl
#define inode_chmod                                                fnode_chmod
#define inode_chown                                                fnode_chown

#define s_rootdir             fs_root
//#define s_type                fs_root._fdirnode_node_ _fnode_file_ mf_ops
#define s_device              fs_dev
#define s_driver              fs_sys->ffs_drv
//#define s_flags               fs_root._fdirnode_node_ _fnode_file_ mf_flags
#define s_features            fs_feat
#define superblock_features   fsuperfeat
#define SUPERBLOCK_FNORMAL    MFILE_F_NORMAL
#define SUPERBLOCK_FNOMTIME   MFILE_F_NOMTIME
#define SUPERBLOCK_FNOSUID    MFILE_FS_NOSUID
#define SUPERBLOCK_FUNMOUNTED MFILE_F_DELETED

#define superblock_syncall fsuper_syncall

#endif /* !GUARD_KERNEL_INCLUDE_FS_NODE_H */
