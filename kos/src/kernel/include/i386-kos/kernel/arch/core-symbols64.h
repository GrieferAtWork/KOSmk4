.section .rodata.kernel_symtab
PUBLIC_OBJECT(kernel_symbol_table)
	.quad 0xfff
	/* Symbol table */
	.quad 0 /* index: 0 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3 /* index: 3 */
	.weak handle_get_superblock; .quad handle_get_superblock
	.reloc ., R_X86_64_SIZE32, handle_get_superblock; .int 0
	.int 0x4bd62ab
	.quad .Lname4 /* index: 4 */
	.weak regdump_gdt; .quad regdump_gdt
	.reloc ., R_X86_64_SIZE32, regdump_gdt; .int 0
	.int 0xc3ee004
	.quad .Lname5 /* index: 5 */
	.weak krealloc_in_place; .quad krealloc_in_place
	.reloc ., R_X86_64_SIZE32, krealloc_in_place; .int 0
	.int 0x1023915
	.quad .Lname6 /* index: 6 */
	.weak slab_malloc16; .quad slab_malloc16
	.reloc ., R_X86_64_SIZE32, slab_malloc16; .int 0
	.int 0xe16d006
	.quad 0 /* index: 7 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname8 /* index: 8 */
	.weak sys_mknodat; .quad sys_mknodat
	.reloc ., R_X86_64_SIZE32, sys_mknodat; .int 0
	.int 0x48053e4
	.quad .Lname9 /* index: 9 */
	.weak sys32_shutdown; .quad sys32_shutdown
	.reloc ., R_X86_64_SIZE32, sys32_shutdown; .int 0
	.int 0xfac37fe
	.quad 0 /* index: 10 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname11 /* index: 11 */
	.weak inode_writek; .quad inode_writek
	.reloc ., R_X86_64_SIZE32, inode_writek; .int 0
	.int 0x1ee500b
	.quad .Lname12 /* index: 12 */
	.weak sys32_lremovexattr; .quad sys32_lremovexattr
	.reloc ., R_X86_64_SIZE32, sys32_lremovexattr; .int 0
	.int 0xf466d52
	.quad .Lname13 /* index: 13 */
	.weak handle_installinto_sym; .quad handle_installinto_sym
	.reloc ., R_X86_64_SIZE32, handle_installinto_sym; .int 0
	.int 0x440c00d
	.quad 0 /* index: 14 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname15 /* index: 15 */
	.weak vm_kernel_sync; .quad vm_kernel_sync
	.reloc ., R_X86_64_SIZE32, vm_kernel_sync; .int 0
	.int 0x98780d3
	.quad .Lname16 /* index: 16 */
	.weak directory_getentry_p; .quad directory_getentry_p
	.reloc ., R_X86_64_SIZE32, directory_getentry_p; .int 0
	.int 0x325f010
	.quad 0 /* index: 17 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 18 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname19 /* index: 19 */
	.weak regdump_coregs; .quad regdump_coregs
	.reloc ., R_X86_64_SIZE32, regdump_coregs; .int 0
	.int 0xe5d4803
	.quad .Lname20 /* index: 20 */
	.weak slab_malloc24; .quad slab_malloc24
	.reloc ., R_X86_64_SIZE32, slab_malloc24; .int 0
	.int 0xe16d014
	.quad .Lname21 /* index: 21 */
	.weak pidns_tryupgrade; .quad pidns_tryupgrade
	.reloc ., R_X86_64_SIZE32, pidns_tryupgrade; .int 0
	.int 0x9ff5015
	.quad 0 /* index: 22 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 23 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 24 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname25 /* index: 25 */
	.weak sys32_fmknodat; .quad sys32_fmknodat
	.reloc ., R_X86_64_SIZE32, sys32_fmknodat; .int 0
	.int 0x483d804
	.quad .Lname26 /* index: 26 */
	.weak sys32_splice; .quad sys32_splice
	.reloc ., R_X86_64_SIZE32, sys32_splice; .int 0
	.int 0x1174915
	.quad 0 /* index: 27 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname28 /* index: 28 */
	.weak vm_getfutex_existing; .quad vm_getfutex_existing
	.reloc ., R_X86_64_SIZE32, vm_getfutex_existing; .int 0
	.int 0x2fb8887
	.quad 0 /* index: 29 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname30 /* index: 30 */
	.weak ramfs_type; .quad ramfs_type
	.reloc ., R_X86_64_SIZE32, ramfs_type; .int 0
	.int 0xd914855
	.quad .Lname31 /* index: 31 */
	.weak sys32_pipe; .quad sys32_pipe
	.reloc ., R_X86_64_SIZE32, sys32_pipe; .int 0
	.int 0x681e005
	.quad .Lname32 /* index: 32 */
	.weak sys_setresgid; .quad sys_setresgid
	.reloc ., R_X86_64_SIZE32, sys_setresgid; .int 0
	.int 0x85f444
	.quad .Lname33 /* index: 33 */
	.weak ttybase_device_iread; .quad ttybase_device_iread
	.reloc ., R_X86_64_SIZE32, ttybase_device_iread; .int 0
	.int 0x514cac4
	.quad .Lname34 /* index: 34 */
	.weak slab_malloc32; .quad slab_malloc32
	.reloc ., R_X86_64_SIZE32, slab_malloc32; .int 0
	.int 0xe16d022
	.quad .Lname35 /* index: 35 */
	.weak qtime_to_timespec; .quad qtime_to_timespec
	.reloc ., R_X86_64_SIZE32, qtime_to_timespec; .int 0
	.int 0x528a023
	.quad .Lname36 /* index: 36 */
	.weak sys32_bind; .quad sys32_bind
	.reloc ., R_X86_64_SIZE32, sys32_bind; .int 0
	.int 0x6824024
	.quad .Lname37 /* index: 37 */
	.weak handle_get_inode; .quad handle_get_inode
	.reloc ., R_X86_64_SIZE32, handle_get_inode; .int 0
	.int 0x3740025
	.quad .Lname38 /* index: 38 */
	.weak sys32_query_module; .quad sys32_query_module
	.reloc ., R_X86_64_SIZE32, sys32_query_module; .int 0
	.int 0x51e1555
	.quad .Lname39 /* index: 39 */
	.weak vio_readq; .quad vio_readq
	.reloc ., R_X86_64_SIZE32, vio_readq; .int 0
	.int 0x568cab1
	.quad .Lname40 /* index: 40 */
	.weak strcmp; .quad strcmp
	.reloc ., R_X86_64_SIZE32, strcmp; .int 0
	.int 0x7ab8a40
	.quad .Lname41 /* index: 41 */
	.weak sys_pivot_root; .quad sys_pivot_root
	.reloc ., R_X86_64_SIZE32, sys_pivot_root; .int 0
	.int 0x61103e4
	.quad .Lname42 /* index: 42 */
	.weak sys32_linux_lstat32; .quad sys32_linux_lstat32
	.reloc ., R_X86_64_SIZE32, sys32_linux_lstat32; .int 0
	.int 0x9a92112
	.quad .Lname43 /* index: 43 */
	.weak sys32_link; .quad sys32_link
	.reloc ., R_X86_64_SIZE32, sys32_link; .int 0
	.int 0x683a02b
	.quad .Lname44 /* index: 44 */
	.weak memmoveupl; .quad memmoveupl
	.reloc ., R_X86_64_SIZE32, memmoveupl; .int 0
	.int 0x46bf02c
	.quad .Lname45 /* index: 45 */
	.weak syscall_emulate_r; .quad syscall_emulate_r
	.reloc ., R_X86_64_SIZE32, syscall_emulate_r; .int 0
	.int 0x443fab2
	.quad 0 /* index: 46 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 47 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname48 /* index: 48 */
	.weak slab_malloc40; .quad slab_malloc40
	.reloc ., R_X86_64_SIZE32, slab_malloc40; .int 0
	.int 0xe16d030
	.quad .Lname49 /* index: 49 */
	.weak memmoveupq; .quad memmoveupq
	.reloc ., R_X86_64_SIZE32, memmoveupq; .int 0
	.int 0x46bf031
	.quad .Lname50 /* index: 50 */
	.weak vm_pagesinphys; .quad vm_pagesinphys
	.reloc ., R_X86_64_SIZE32, vm_pagesinphys; .int 0
	.int 0xaa31613
	.quad .Lname51 /* index: 51 */
	.weak driver_finalized_callbacks; .quad driver_finalized_callbacks
	.reloc ., R_X86_64_SIZE32, driver_finalized_callbacks; .int 0
	.int 0x59ae2b3
	.quad .Lname52 /* index: 52 */
	.weak page_ismapped; .quad page_ismapped
	.reloc ., R_X86_64_SIZE32, page_ismapped; .int 0
	.int 0x45c034
	.quad .Lname53 /* index: 53 */
	.weak sys_create_module; .quad sys_create_module
	.reloc ., R_X86_64_SIZE32, sys_create_module; .int 0
	.int 0xd54035
	.quad 0 /* index: 54 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname55 /* index: 55 */
	.weak getreg_sgregs; .quad getreg_sgregs
	.reloc ., R_X86_64_SIZE32, getreg_sgregs; .int 0
	.int 0xb550053
	.quad .Lname56 /* index: 56 */
	.weak slab_malloc48; .quad slab_malloc48
	.reloc ., R_X86_64_SIZE32, slab_malloc48; .int 0
	.int 0xe16d038
	.quad .Lname57 /* index: 57 */
	.weak path_recent; .quad path_recent
	.reloc ., R_X86_64_SIZE32, path_recent; .int 0
	.int 0x6fd12b4
	.quad .Lname58 /* index: 58 */
	.weak sys32_signal; .quad sys32_signal
	.reloc ., R_X86_64_SIZE32, sys32_signal; .int 0
	.int 0x12fc2fc
	.quad .Lname59 /* index: 59 */
	.weak sys32_setsockopt; .quad sys32_setsockopt
	.reloc ., R_X86_64_SIZE32, sys32_setsockopt; .int 0
	.int 0xd94a94
	.quad .Lname60 /* index: 60 */
	.weak vm_datapart_do_write_nopf; .quad vm_datapart_do_write_nopf
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_write_nopf; .int 0
	.int 0xa9fadf6
	.quad 0 /* index: 61 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname62 /* index: 62 */
	.weak vm_mapat_subrange; .quad vm_mapat_subrange
	.reloc ., R_X86_64_SIZE32, vm_mapat_subrange; .int 0
	.int 0x38dd445
	.quad .Lname63 /* index: 63 */
	.weak pagedir_unwrite; .quad pagedir_unwrite
	.reloc ., R_X86_64_SIZE32, pagedir_unwrite; .int 0
	.int 0x7e602b5
	.quad .Lname64 /* index: 64 */
	.weak vmb_fini; .quad vmb_fini
	.reloc ., R_X86_64_SIZE32, vmb_fini; .int 0
	.int 0x385c999
	.quad 0 /* index: 65 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname66 /* index: 66 */
	.weak cpu_delete_idle_job; .quad cpu_delete_idle_job
	.reloc ., R_X86_64_SIZE32, cpu_delete_idle_job; .int 0
	.int 0x3997042
	.quad 0 /* index: 67 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname68 /* index: 68 */
	.weak sys_getresgid; .quad sys_getresgid
	.reloc ., R_X86_64_SIZE32, sys_getresgid; .int 0
	.int 0x85c044
	.quad .Lname69 /* index: 69 */
	.weak lookup_pci_device; .quad lookup_pci_device
	.reloc ., R_X86_64_SIZE32, lookup_pci_device; .int 0
	.int 0x999c045
	.quad 0 /* index: 70 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname71 /* index: 71 */
	.weak vio_addq; .quad vio_addq
	.reloc ., R_X86_64_SIZE32, vio_addq; .int 0
	.int 0x557d61
	.quad .Lname72 /* index: 72 */
	.weak sys_fmkdirat; .quad sys_fmkdirat
	.reloc ., R_X86_64_SIZE32, sys_fmkdirat; .int 0
	.int 0x5ab9d54
	.quad 0 /* index: 73 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 74 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname75 /* index: 75 */
	.weak kernel_slab_break; .quad kernel_slab_break
	.reloc ., R_X86_64_SIZE32, kernel_slab_break; .int 0
	.int 0xc2ee04b
	.quad .Lname76 /* index: 76 */
	.weak sys32_kill; .quad sys32_kill
	.reloc ., R_X86_64_SIZE32, sys32_kill; .int 0
	.int 0x683b04c
	.quad .Lname77 /* index: 77 */
	.weak sys32_mkdir; .quad sys32_mkdir
	.reloc ., R_X86_64_SIZE32, sys32_mkdir; .int 0
	.int 0x8391d62
	.quad .Lname78 /* index: 78 */
	.weak boot_partition; .quad boot_partition
	.reloc ., R_X86_64_SIZE32, boot_partition; .int 0
	.int 0xfdad04e
	.quad .Lname79 /* index: 79 */
	.weak kernel_debugtraps_get; .quad kernel_debugtraps_get
	.reloc ., R_X86_64_SIZE32, kernel_debugtraps_get; .int 0
	.int 0xab0c224
	.quad .Lname80 /* index: 80 */
	.weak sys_modify_ldt; .quad sys_modify_ldt
	.reloc ., R_X86_64_SIZE32, sys_modify_ldt; .int 0
	.int 0xf4920a4
	.quad .Lname81 /* index: 81 */
	.weak vm_datablock_read; .quad vm_datablock_read
	.reloc ., R_X86_64_SIZE32, vm_datablock_read; .int 0
	.int 0x2ec4384
	.quad .Lname82 /* index: 82 */
	.weak x86_userexcept_callhandler32; .quad x86_userexcept_callhandler32
	.reloc ., R_X86_64_SIZE32, x86_userexcept_callhandler32; .int 0
	.int 0x5a3e052
	.quad .Lname83 /* index: 83 */
	.weak fs_filesystems; .quad fs_filesystems
	.reloc ., R_X86_64_SIZE32, fs_filesystems; .int 0
	.int 0x457b053
	.quad .Lname84 /* index: 84 */
	.weak sys32_prctl; .quad sys32_prctl
	.reloc ., R_X86_64_SIZE32, sys32_prctl; .int 0
	.int 0x81c8ccc
	.quad .Lname85 /* index: 85 */
	.weak sys32_time; .quad sys32_time
	.reloc ., R_X86_64_SIZE32, sys32_time; .int 0
	.int 0x6812055
	.quad 0 /* index: 86 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 87 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 88 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname89 /* index: 89 */
	.weak pagedir_ismapped; .quad pagedir_ismapped
	.reloc ., R_X86_64_SIZE32, pagedir_ismapped; .int 0
	.int 0x38f5564
	.quad .Lname90 /* index: 90 */
	.weak vio_readw_aligned; .quad vio_readw_aligned
	.reloc ., R_X86_64_SIZE32, vio_readw_aligned; .int 0
	.int 0xe57ef4
	.quad .Lname91 /* index: 91 */
	.weak vpage_alloc_untraced; .quad vpage_alloc_untraced
	.reloc ., R_X86_64_SIZE32, vpage_alloc_untraced; .int 0
	.int 0xd03da4
	.quad .Lname92 /* index: 92 */
	.weak error_as_signal; .quad error_as_signal
	.reloc ., R_X86_64_SIZE32, error_as_signal; .int 0
	.int 0xff7f05c
	.quad 0 /* index: 93 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname94 /* index: 94 */
	.weak error_thrown; .quad error_thrown
	.reloc ., R_X86_64_SIZE32, error_thrown; .int 0
	.int 0x66205e
	.quad .Lname95 /* index: 95 */
	.weak sys_ftruncate; .quad sys_ftruncate
	.reloc ., R_X86_64_SIZE32, sys_ftruncate; .int 0
	.int 0x2cdc565
	.quad .Lname96 /* index: 96 */
	.weak strend; .quad strend
	.reloc ., R_X86_64_SIZE32, strend; .int 0
	.int 0x7ab8c44
	.quad .Lname97 /* index: 97 */
	.weak handle_lookup; .quad handle_lookup
	.reloc ., R_X86_64_SIZE32, handle_lookup; .int 0
	.int 0xcb2f010
	.quad 0 /* index: 98 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname99 /* index: 99 */
	.weak sys_getdents; .quad sys_getdents
	.reloc ., R_X86_64_SIZE32, sys_getdents; .int 0
	.int 0xb1a3063
	.quad .Lname100 /* index: 100 */
	.weak sys32_rt_sigtimedwait; .quad sys32_rt_sigtimedwait
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigtimedwait; .int 0
	.int 0x34c3064
	.quad .Lname101 /* index: 101 */
	.weak aio_multihandle_done; .quad aio_multihandle_done
	.reloc ., R_X86_64_SIZE32, aio_multihandle_done; .int 0
	.int 0x81e0065
	.quad .Lname102 /* index: 102 */
	.weak dbg_screen_cellsize; .quad dbg_screen_cellsize
	.reloc ., R_X86_64_SIZE32, dbg_screen_cellsize; .int 0
	.int 0xa250d55
	.quad .Lname103 /* index: 103 */
	.weak __cxa_rethrow; .quad __cxa_rethrow
	.reloc ., R_X86_64_SIZE32, __cxa_rethrow; .int 0
	.int 0xd902067
	.quad 0 /* index: 104 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 105 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname106 /* index: 106 */
	.weak sys_lgetxattr; .quad sys_lgetxattr
	.reloc ., R_X86_64_SIZE32, sys_lgetxattr; .int 0
	.int 0x7b7e912
	.quad .Lname107 /* index: 107 */
	.weak vio_addw; .quad vio_addw
	.reloc ., R_X86_64_SIZE32, vio_addw; .int 0
	.int 0x557d67
	.quad 0 /* index: 108 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname109 /* index: 109 */
	.weak fpustate_save; .quad fpustate_save
	.reloc ., R_X86_64_SIZE32, fpustate_save; .int 0
	.int 0x7ea3225
	.quad .Lname110 /* index: 110 */
	.weak unwind_getreg_ucpustate; .quad unwind_getreg_ucpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_ucpustate; .int 0
	.int 0xb8c41b5
	.quad .Lname111 /* index: 111 */
	.weak sys_maplibrary; .quad sys_maplibrary
	.reloc ., R_X86_64_SIZE32, sys_maplibrary; .int 0
	.int 0x26fb779
	.quad .Lname112 /* index: 112 */
	.weak handle_installhop; .quad handle_installhop
	.reloc ., R_X86_64_SIZE32, handle_installhop; .int 0
	.int 0x8bab070
	.quad .Lname113 /* index: 113 */
	.weak sys32_fsync; .quad sys32_fsync
	.reloc ., R_X86_64_SIZE32, sys32_fsync; .int 0
	.int 0x826aa23
	.quad 0 /* index: 114 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname115 /* index: 115 */
	.weak x86_sysroute1_c; .quad x86_sysroute1_c
	.reloc ., R_X86_64_SIZE32, x86_sysroute1_c; .int 0
	.int 0xaa1f813
	.quad .Lname116 /* index: 116 */
	.weak driver_delmod; .quad driver_delmod
	.reloc ., R_X86_64_SIZE32, driver_delmod; .int 0
	.int 0xe3d0074
	.quad .Lname117 /* index: 117 */
	.weak directory_creatfile; .quad directory_creatfile
	.reloc ., R_X86_64_SIZE32, directory_creatfile; .int 0
	.int 0x61d3075
	.quad .Lname118 /* index: 118 */
	.weak inode_writev; .quad inode_writev
	.reloc ., R_X86_64_SIZE32, inode_writev; .int 0
	.int 0x1ee5076
	.quad .Lname119 /* index: 119 */
	.weak sys32_getresgid; .quad sys32_getresgid
	.reloc ., R_X86_64_SIZE32, sys32_getresgid; .int 0
	.int 0xde4bb34
	.quad 0 /* index: 120 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname121 /* index: 121 */
	.weak cpu_broadcastipi; .quad cpu_broadcastipi
	.reloc ., R_X86_64_SIZE32, cpu_broadcastipi; .int 0
	.int 0xc156079
	.quad 0 /* index: 122 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname123 /* index: 123 */
	.weak sys_break; .quad sys_break
	.reloc ., R_X86_64_SIZE32, sys_break; .int 0
	.int 0x959f07b
	.quad .Lname124 /* index: 124 */
	.weak path_print; .quad path_print
	.reloc ., R_X86_64_SIZE32, path_print; .int 0
	.int 0xe60e8f4
	.quad 0 /* index: 125 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname126 /* index: 126 */
	.weak task_rpc_exec_here_onexit; .quad task_rpc_exec_here_onexit
	.reloc ., R_X86_64_SIZE32, task_rpc_exec_here_onexit; .int 0
	.int 0x125e004
	.quad .Lname127 /* index: 127 */
	.weak dbg_active; .quad dbg_active
	.reloc ., R_X86_64_SIZE32, dbg_active; .int 0
	.int 0x57c1815
	.quad .Lname128 /* index: 128 */
	.weak mempmoveup; .quad mempmoveup
	.reloc ., R_X86_64_SIZE32, mempmoveup; .int 0
	.int 0x741f080
	.quad .Lname129 /* index: 129 */
	.weak sys32_setsid; .quad sys32_setsid
	.reloc ., R_X86_64_SIZE32, sys32_setsid; .int 0
	.int 0x12cdf74
	.quad .Lname130 /* index: 130 */
	.weak character_device_unregister; .quad character_device_unregister
	.reloc ., R_X86_64_SIZE32, character_device_unregister; .int 0
	.int 0x26b6082
	.quad .Lname131 /* index: 131 */
	.weak debug_dlunlocksections; .quad debug_dlunlocksections
	.reloc ., R_X86_64_SIZE32, debug_dlunlocksections; .int 0
	.int 0xaac8083
	.quad .Lname132 /* index: 132 */
	.weak sys32_getrusage; .quad sys32_getrusage
	.reloc ., R_X86_64_SIZE32, sys32_getrusage; .int 0
	.int 0xdf4b115
	.quad 0 /* index: 133 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname134 /* index: 134 */
	.weak vm_copyfromphys_nopf; .quad vm_copyfromphys_nopf
	.reloc ., R_X86_64_SIZE32, vm_copyfromphys_nopf; .int 0
	.int 0xe867086
	.quad .Lname135 /* index: 135 */
	.weak mall_validate_padding; .quad mall_validate_padding
	.reloc ., R_X86_64_SIZE32, mall_validate_padding; .int 0
	.int 0xaf49087
	.quad .Lname136 /* index: 136 */
	.weak sys_inotify_add_watch; .quad sys_inotify_add_watch
	.reloc ., R_X86_64_SIZE32, sys_inotify_add_watch; .int 0
	.int 0xd29088
	.quad .Lname137 /* index: 137 */
	.weak sys32_maplibrary; .quad sys32_maplibrary
	.reloc ., R_X86_64_SIZE32, sys32_maplibrary; .int 0
	.int 0x47a0089
	.quad .Lname138 /* index: 138 */
	.weak sys_sendmsg; .quad sys_sendmsg
	.reloc ., R_X86_64_SIZE32, sys_sendmsg; .int 0
	.int 0x9dfbdf7
	.quad .Lname139 /* index: 139 */
	.weak sys32_sigprocmask; .quad sys32_sigprocmask
	.reloc ., R_X86_64_SIZE32, sys32_sigprocmask; .int 0
	.int 0x14cc08b
	.quad 0 /* index: 140 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 141 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 142 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname143 /* index: 143 */
	.weak sys32_mbind; .quad sys32_mbind
	.reloc ., R_X86_64_SIZE32, sys32_mbind; .int 0
	.int 0x8388a24
	.quad .Lname144 /* index: 144 */
	.weak vm_datapart_read; .quad vm_datapart_read
	.reloc ., R_X86_64_SIZE32, vm_datapart_read; .int 0
	.int 0x32bdea4
	.quad 0 /* index: 145 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 146 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname147 /* index: 147 */
	.weak task_schedule_user_rpc; .quad task_schedule_user_rpc
	.reloc ., R_X86_64_SIZE32, task_schedule_user_rpc; .int 0
	.int 0x32cc9b3
	.quad .Lname148 /* index: 148 */
	.weak sys32_nanosleep64; .quad sys32_nanosleep64
	.reloc ., R_X86_64_SIZE32, sys32_nanosleep64; .int 0
	.int 0x2144094
	.quad .Lname149 /* index: 149 */
	.weak block_device_acquire_partlock_write; .quad block_device_acquire_partlock_write
	.reloc ., R_X86_64_SIZE32, block_device_acquire_partlock_write; .int 0
	.int 0xd5bb095
	.quad 0 /* index: 150 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname151 /* index: 151 */
	.weak sys_getpeername; .quad sys_getpeername
	.reloc ., R_X86_64_SIZE32, sys_getpeername; .int 0
	.int 0x296f855
	.quad .Lname152 /* index: 152 */
	.weak path_traversefull_ex; .quad path_traversefull_ex
	.reloc ., R_X86_64_SIZE32, path_traversefull_ex; .int 0
	.int 0xde1f098
	.quad .Lname153 /* index: 153 */
	.weak error_unwind; .quad error_unwind
	.reloc ., R_X86_64_SIZE32, error_unwind; .int 0
	.int 0x8c4ac4
	.quad .Lname154 /* index: 154 */
	.weak thiscpu_x86_ldt; .quad thiscpu_x86_ldt
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_ldt; .int 0
	.int 0xb226324
	.quad 0 /* index: 155 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 156 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 157 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 158 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname159 /* index: 159 */
	.weak getreg_xfpustate; .quad getreg_xfpustate
	.reloc ., R_X86_64_SIZE32, getreg_xfpustate; .int 0
	.int 0xf711ac5
	.quad .Lname160 /* index: 160 */
	.weak regdump_drregs; .quad regdump_drregs
	.reloc ., R_X86_64_SIZE32, regdump_drregs; .int 0
	.int 0xe624803
	.quad 0 /* index: 161 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname162 /* index: 162 */
	.weak sys_renameat2; .quad sys_renameat2
	.reloc ., R_X86_64_SIZE32, sys_renameat2; .int 0
	.int 0xf8ad0a2
	.quad .Lname163 /* index: 163 */
	.weak ringbuffer_write_nonblock_noalloc; .quad ringbuffer_write_nonblock_noalloc
	.reloc ., R_X86_64_SIZE32, ringbuffer_write_nonblock_noalloc; .int 0
	.int 0x4af0a3
	.quad .Lname164 /* index: 164 */
	.weak cmdline_encode_argument; .quad cmdline_encode_argument
	.reloc ., R_X86_64_SIZE32, cmdline_encode_argument; .int 0
	.int 0x291f0a4
	.quad .Lname165 /* index: 165 */
	.weak vm_pagefromphys_nopf; .quad vm_pagefromphys_nopf
	.reloc ., R_X86_64_SIZE32, vm_pagefromphys_nopf; .int 0
	.int 0xe828ac6
	.quad .Lname166 /* index: 166 */
	.weak block_device_awritev; .quad block_device_awritev
	.reloc ., R_X86_64_SIZE32, block_device_awritev; .int 0
	.int 0x77e80a6
	.quad .Lname167 /* index: 167 */
	.weak heap_realloc_untraced; .quad heap_realloc_untraced
	.reloc ., R_X86_64_SIZE32, heap_realloc_untraced; .int 0
	.int 0xeeb0ac4
	.quad 0 /* index: 168 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname169 /* index: 169 */
	.weak mempmoveupl; .quad mempmoveupl
	.reloc ., R_X86_64_SIZE32, mempmoveupl; .int 0
	.int 0x41f081c
	.quad 0 /* index: 170 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname171 /* index: 171 */
	.weak vm_kernel_treelock_tryupgrade; .quad vm_kernel_treelock_tryupgrade
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_tryupgrade; .int 0
	.int 0xcfa0495
	.quad 0 /* index: 172 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname173 /* index: 173 */
	.weak vio_addb; .quad vio_addb
	.reloc ., R_X86_64_SIZE32, vio_addb; .int 0
	.int 0x557d72
	.quad .Lname174 /* index: 174 */
	.weak unwind_setreg_ucpustate_exclusive; .quad unwind_setreg_ucpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_ucpustate_exclusive; .int 0
	.int 0x98e5125
	.quad .Lname175 /* index: 175 */
	.weak sys_sched_getaffinity; .quad sys_sched_getaffinity
	.reloc ., R_X86_64_SIZE32, sys_sched_getaffinity; .int 0
	.int 0xdfc7f79
	.quad 0 /* index: 176 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname177 /* index: 177 */
	.weak vm_startdmav_nx; .quad vm_startdmav_nx
	.reloc ., R_X86_64_SIZE32, vm_startdmav_nx; .int 0
	.int 0xd9252c8
	.quad .Lname178 /* index: 178 */
	.weak kernel_driver; .quad kernel_driver
	.reloc ., R_X86_64_SIZE32, kernel_driver; .int 0
	.int 0x47240b2
	.quad .Lname179 /* index: 179 */
	.weak pagedir_unmap_userspace_nosync; .quad pagedir_unmap_userspace_nosync
	.reloc ., R_X86_64_SIZE32, pagedir_unmap_userspace_nosync; .int 0
	.int 0x477a0b3
	.quad .Lname180 /* index: 180 */
	.weak pagedir_init; .quad pagedir_init
	.reloc ., R_X86_64_SIZE32, pagedir_init; .int 0
	.int 0x72240b4
	.quad .Lname181 /* index: 181 */
	.weak _bootidle; .quad _bootidle
	.reloc ., R_X86_64_SIZE32, _bootidle; .int 0
	.int 0x66aa0b5
	.quad 0 /* index: 182 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname183 /* index: 183 */
	.weak sighand_destroy; .quad sighand_destroy
	.reloc ., R_X86_64_SIZE32, sighand_destroy; .int 0
	.int 0x7228ac9
	.quad .Lname184 /* index: 184 */
	.weak task_alloc_synchronous_rpc_nx; .quad task_alloc_synchronous_rpc_nx
	.reloc ., R_X86_64_SIZE32, task_alloc_synchronous_rpc_nx; .int 0
	.int 0xa6230b8
	.quad .Lname185 /* index: 185 */
	.weak superblock_set_unmounted; .quad superblock_set_unmounted
	.reloc ., R_X86_64_SIZE32, superblock_set_unmounted; .int 0
	.int 0xb403d74
	.quad 0 /* index: 186 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 187 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname188 /* index: 188 */
	.weak sys_nfsservctl; .quad sys_nfsservctl
	.reloc ., R_X86_64_SIZE32, sys_nfsservctl; .int 0
	.int 0x95f80bc
	.quad 0 /* index: 189 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname190 /* index: 190 */
	.weak sys32_chown; .quad sys32_chown
	.reloc ., R_X86_64_SIZE32, sys32_chown; .int 0
	.int 0x822f0be
	.quad .Lname191 /* index: 191 */
	.weak vm_datapart_read_unsafe; .quad vm_datapart_read_unsafe
	.reloc ., R_X86_64_SIZE32, vm_datapart_read_unsafe; .int 0
	.int 0x4187d75
	.quad .Lname192 /* index: 192 */
	.weak directory_readnext_p; .quad directory_readnext_p
	.reloc ., R_X86_64_SIZE32, directory_readnext_p; .int 0
	.int 0x431e0c0
	.quad .Lname193 /* index: 193 */
	.weak thiscpu_idle_x86_kernel_psp0; .quad thiscpu_idle_x86_kernel_psp0
	.reloc ., R_X86_64_SIZE32, thiscpu_idle_x86_kernel_psp0; .int 0
	.int 0xd0cc020
	.quad .Lname194 /* index: 194 */
	.weak kmalloc_noslab; .quad kmalloc_noslab
	.reloc ., R_X86_64_SIZE32, kmalloc_noslab; .int 0
	.int 0x7d5b0c2
	.quad .Lname195 /* index: 195 */
	.weak aio_handle_generic_func; .quad aio_handle_generic_func
	.reloc ., R_X86_64_SIZE32, aio_handle_generic_func; .int 0
	.int 0x48d30c3
	.quad .Lname196 /* index: 196 */
	.weak driver_try_decref_and_delmod; .quad driver_try_decref_and_delmod
	.reloc ., R_X86_64_SIZE32, driver_try_decref_and_delmod; .int 0
	.int 0xd9720c4
	.quad .Lname197 /* index: 197 */
	.weak superblock_nodeslock_write; .quad superblock_nodeslock_write
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_write; .int 0
	.int 0x1a890c5
	.quad .Lname198 /* index: 198 */
	.weak slab_malloc56; .quad slab_malloc56
	.reloc ., R_X86_64_SIZE32, slab_malloc56; .int 0
	.int 0xe16d0c6
	.quad 0 /* index: 199 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 200 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname201 /* index: 201 */
	.weak sys_getpriority; .quad sys_getpriority
	.reloc ., R_X86_64_SIZE32, sys_getpriority; .int 0
	.int 0x1bb40c9
	.quad 0 /* index: 202 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname203 /* index: 203 */
	.weak getreg_drregs; .quad getreg_drregs
	.reloc ., R_X86_64_SIZE32, getreg_drregs; .int 0
	.int 0x8720053
	.quad .Lname204 /* index: 204 */
	.weak mempcpyl; .quad mempcpyl
	.reloc ., R_X86_64_SIZE32, mempcpyl; .int 0
	.int 0xc46a0cc
	.quad .Lname205 /* index: 205 */
	.weak vm_readphysb; .quad vm_readphysb
	.reloc ., R_X86_64_SIZE32, vm_readphysb; .int 0
	.int 0x65a822
	.quad .Lname206 /* index: 206 */
	.weak sys_kfstatat; .quad sys_kfstatat
	.reloc ., R_X86_64_SIZE32, sys_kfstatat; .int 0
	.int 0xa1a1c94
	.quad 0 /* index: 207 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 208 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 209 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname210 /* index: 210 */
	.weak kernel_pty_oprinter; .quad kernel_pty_oprinter
	.reloc ., R_X86_64_SIZE32, kernel_pty_oprinter; .int 0
	.int 0x3ee0d2
	.quad .Lname211 /* index: 211 */
	.weak aio_multihandle_generic_func; .quad aio_multihandle_generic_func
	.reloc ., R_X86_64_SIZE32, aio_multihandle_generic_func; .int 0
	.int 0x227c0d3
	.quad .Lname212 /* index: 212 */
	.weak devfs_lock_end; .quad devfs_lock_end
	.reloc ., R_X86_64_SIZE32, devfs_lock_end; .int 0
	.int 0x96ed0d4
	.quad .Lname213 /* index: 213 */
	.weak strnlen; .quad strnlen
	.reloc ., R_X86_64_SIZE32, strnlen; .int 0
	.int 0xab952ce
	.quad .Lname214 /* index: 214 */
	.weak block_device_partition_readv; .quad block_device_partition_readv
	.reloc ., R_X86_64_SIZE32, block_device_partition_readv; .int 0
	.int 0x5240d6
	.quad .Lname215 /* index: 215 */
	.weak terminal_poll_iwrite; .quad terminal_poll_iwrite
	.reloc ., R_X86_64_SIZE32, terminal_poll_iwrite; .int 0
	.int 0xcfdf3a5
	.quad .Lname216 /* index: 216 */
	.weak superblock_nodeslock_write_nx; .quad superblock_nodeslock_write_nx
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_write_nx; .int 0
	.int 0x90cd0d8
	.quad .Lname217 /* index: 217 */
	.weak swap_malloc_part; .quad swap_malloc_part
	.reloc ., R_X86_64_SIZE32, swap_malloc_part; .int 0
	.int 0x3f29824
	.quad 0 /* index: 218 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname219 /* index: 219 */
	.weak sys_unlink; .quad sys_unlink
	.reloc ., R_X86_64_SIZE32, sys_unlink; .int 0
	.int 0x6c4a0db
	.quad 0 /* index: 220 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname221 /* index: 221 */
	.weak vm_syncmem; .quad vm_syncmem
	.reloc ., R_X86_64_SIZE32, vm_syncmem; .int 0
	.int 0xb0350dd
	.quad .Lname222 /* index: 222 */
	.weak sys_shmctl; .quad sys_shmctl
	.reloc ., R_X86_64_SIZE32, sys_shmctl; .int 0
	.int 0x69a8a3c
	.quad .Lname223 /* index: 223 */
	.weak vm_datablock_vio_write; .quad vm_datablock_vio_write
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_write; .int 0
	.int 0xc405025
	.quad 0 /* index: 224 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 225 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname226 /* index: 226 */
	.weak sys32_pipe2; .quad sys32_pipe2
	.reloc ., R_X86_64_SIZE32, sys32_pipe2; .int 0
	.int 0x81e00e2
	.quad .Lname227 /* index: 227 */
	.weak page_malloc; .quad page_malloc
	.reloc ., R_X86_64_SIZE32, page_malloc; .int 0
	.int 0x64270e3
	.quad 0 /* index: 228 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname229 /* index: 229 */
	.weak page_ffree; .quad page_ffree
	.reloc ., R_X86_64_SIZE32, page_ffree; .int 0
	.int 0xb5bbf65
	.quad .Lname230 /* index: 230 */
	.weak unregister_filesystem_type; .quad unregister_filesystem_type
	.reloc ., R_X86_64_SIZE32, unregister_filesystem_type; .int 0
	.int 0x7be1165
	.quad 0 /* index: 231 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname232 /* index: 232 */
	.weak validate_writable; .quad validate_writable
	.reloc ., R_X86_64_SIZE32, validate_writable; .int 0
	.int 0x3fc4d35
	.quad .Lname233 /* index: 233 */
	.weak vio_addl; .quad vio_addl
	.reloc ., R_X86_64_SIZE32, vio_addl; .int 0
	.int 0x557d7c
	.quad 0 /* index: 234 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname235 /* index: 235 */
	.weak sys32_vfork; .quad sys32_vfork
	.reloc ., R_X86_64_SIZE32, sys32_vfork; .int 0
	.int 0x817d0eb
	.quad 0 /* index: 236 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname237 /* index: 237 */
	.weak sys32_setpgid; .quad sys32_setpgid
	.reloc ., R_X86_64_SIZE32, sys32_setpgid; .int 0
	.int 0x2cd05e4
	.quad .Lname238 /* index: 238 */
	.weak unwind_fde_scan; .quad unwind_fde_scan
	.reloc ., R_X86_64_SIZE32, unwind_fde_scan; .int 0
	.int 0x4b260ee
	.quad .Lname239 /* index: 239 */
	.weak this_exception_trace; .quad this_exception_trace
	.reloc ., R_X86_64_SIZE32, this_exception_trace; .int 0
	.int 0x6a572b5
	.quad .Lname240 /* index: 240 */
	.weak pagedir_prepare_map_p; .quad pagedir_prepare_map_p
	.reloc ., R_X86_64_SIZE32, pagedir_prepare_map_p; .int 0
	.int 0x174a0f0
	.quad .Lname241 /* index: 241 */
	.weak sys32_epoll_create1; .quad sys32_epoll_create1
	.reloc ., R_X86_64_SIZE32, sys32_epoll_create1; .int 0
	.int 0xdffd0f1
	.quad 0 /* index: 242 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname243 /* index: 243 */
	.weak sys32_utimes64; .quad sys32_utimes64
	.reloc ., R_X86_64_SIZE32, sys32_utimes64; .int 0
	.int 0xaa547e4
	.quad .Lname244 /* index: 244 */
	.weak path_lock_tryread; .quad path_lock_tryread
	.reloc ., R_X86_64_SIZE32, path_lock_tryread; .int 0
	.int 0xe03a0f4
	.quad .Lname245 /* index: 245 */
	.weak kernel_debugtrap_kcpustate; .quad kernel_debugtrap_kcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_kcpustate; .int 0
	.int 0x96390f5
	.quad .Lname246 /* index: 246 */
	.weak vmb_getfree; .quad vmb_getfree
	.reloc ., R_X86_64_SIZE32, vmb_getfree; .int 0
	.int 0xdb7e0e5
	.quad 0 /* index: 247 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname248 /* index: 248 */
	.weak directory_entry_hash; .quad directory_entry_hash
	.reloc ., R_X86_64_SIZE32, directory_entry_hash; .int 0
	.int 0xabc0f8
	.quad .Lname249 /* index: 249 */
	.weak json_parser_leavearray; .quad json_parser_leavearray
	.reloc ., R_X86_64_SIZE32, json_parser_leavearray; .int 0
	.int 0x49d20f9
	.quad .Lname250 /* index: 250 */
	.weak vsnprintf; .quad vsnprintf
	.reloc ., R_X86_64_SIZE32, vsnprintf; .int 0
	.int 0x5789806
	.quad 0 /* index: 251 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname252 /* index: 252 */
	.weak thisvm_x86_dr3; .quad thisvm_x86_dr3
	.reloc ., R_X86_64_SIZE32, thisvm_x86_dr3; .int 0
	.int 0x4b28d93
	.quad 0 /* index: 253 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 254 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname255 /* index: 255 */
	.weak debug_sections_addr2line; .quad debug_sections_addr2line
	.reloc ., R_X86_64_SIZE32, debug_sections_addr2line; .int 0
	.int 0xd324ad5
	.quad 0 /* index: 256 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname257 /* index: 257 */
	.weak vm_tasklock_upgrade_nx; .quad vm_tasklock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, vm_tasklock_upgrade_nx; .int 0
	.int 0xce3c288
	.quad .Lname258 /* index: 258 */
	.weak sys32_linux_fstat32; .quad sys32_linux_fstat32
	.reloc ., R_X86_64_SIZE32, sys32_linux_fstat32; .int 0
	.int 0x7a92102
	.quad 0 /* index: 259 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname260 /* index: 260 */
	.weak devfs_insert; .quad devfs_insert
	.reloc ., R_X86_64_SIZE32, devfs_insert; .int 0
	.int 0x3695104
	.quad .Lname261 /* index: 261 */
	.weak sys_timer_gettime; .quad sys_timer_gettime
	.reloc ., R_X86_64_SIZE32, sys_timer_gettime; .int 0
	.int 0x7536105
	.quad 0 /* index: 262 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname263 /* index: 263 */
	.weak dbg_changedview; .quad dbg_changedview
	.reloc ., R_X86_64_SIZE32, dbg_changedview; .int 0
	.int 0xe24107
	.quad .Lname264 /* index: 264 */
	.weak sys32_adjtimex; .quad sys32_adjtimex
	.reloc ., R_X86_64_SIZE32, sys32_adjtimex; .int 0
	.int 0xb7c8108
	.quad .Lname265 /* index: 265 */
	.weak vm_node_destroy; .quad vm_node_destroy
	.reloc ., R_X86_64_SIZE32, vm_node_destroy; .int 0
	.int 0xc9f6109
	.quad 0 /* index: 266 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 267 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 268 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname269 /* index: 269 */
	.weak sys_pipe2; .quad sys_pipe2
	.reloc ., R_X86_64_SIZE32, sys_pipe2; .int 0
	.int 0x9677d82
	.quad .Lname270 /* index: 270 */
	.weak sys_open; .quad sys_open
	.reloc ., R_X86_64_SIZE32, sys_open; .int 0
	.int 0x96610e
	.quad .Lname271 /* index: 271 */
	.weak vm86_outb; .quad vm86_outb
	.reloc ., R_X86_64_SIZE32, vm86_outb; .int 0
	.int 0xbc611a2
	.quad .Lname272 /* index: 272 */
	.weak cpu_deepsleep; .quad cpu_deepsleep
	.reloc ., R_X86_64_SIZE32, cpu_deepsleep; .int 0
	.int 0x6037110
	.quad 0 /* index: 273 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname274 /* index: 274 */
	.weak dbg_getpagedir; .quad dbg_getpagedir
	.reloc ., R_X86_64_SIZE32, dbg_getpagedir; .int 0
	.int 0xea86112
	.quad 0 /* index: 275 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname276 /* index: 276 */
	.weak sys32_mknod; .quad sys32_mknod
	.reloc ., R_X86_64_SIZE32, sys32_mknod; .int 0
	.int 0x8392334
	.quad .Lname277 /* index: 277 */
	.weak cpu_apply_kcpustate; .quad cpu_apply_kcpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_kcpustate; .int 0
	.int 0xa8cb115
	.quad .Lname278 /* index: 278 */
	.weak slab_kmalloc56; .quad slab_kmalloc56
	.reloc ., R_X86_64_SIZE32, slab_kmalloc56; .int 0
	.int 0x66b3116
	.quad .Lname279 /* index: 279 */
	.weak this_exception_info; .quad this_exception_info
	.reloc ., R_X86_64_SIZE32, this_exception_info; .int 0
	.int 0x2692b9f
	.quad .Lname280 /* index: 280 */
	.weak instruction_length; .quad instruction_length
	.reloc ., R_X86_64_SIZE32, instruction_length; .int 0
	.int 0xa852118
	.quad .Lname281 /* index: 281 */
	.weak sys_faccessat; .quad sys_faccessat
	.reloc ., R_X86_64_SIZE32, sys_faccessat; .int 0
	.int 0x295f584
	.quad .Lname282 /* index: 282 */
	.weak task_isconnected; .quad task_isconnected
	.reloc ., R_X86_64_SIZE32, task_isconnected; .int 0
	.int 0x62c99b4
	.quad .Lname283 /* index: 283 */
	.weak sys_sigaltstack; .quad sys_sigaltstack
	.reloc ., R_X86_64_SIZE32, sys_sigaltstack; .int 0
	.int 0xad3211b
	.quad .Lname284 /* index: 284 */
	.weak path_traversenfull_at; .quad path_traversenfull_at
	.reloc ., R_X86_64_SIZE32, path_traversenfull_at; .int 0
	.int 0xbae53c4
	.quad 0 /* index: 285 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 286 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname287 /* index: 287 */
	.weak this_exception_state; .quad this_exception_state
	.reloc ., R_X86_64_SIZE32, this_exception_state; .int 0
	.int 0x6a45d85
	.quad 0 /* index: 288 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 289 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname290 /* index: 290 */
	.weak vm_datablock_vio_read_phys; .quad vm_datablock_vio_read_phys
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_read_phys; .int 0
	.int 0x72a2a73
	.quad .Lname291 /* index: 291 */
	.weak sys32_umount2; .quad sys32_umount2
	.reloc ., R_X86_64_SIZE32, sys32_umount2; .int 0
	.int 0x140ed62
	.quad .Lname292 /* index: 292 */
	.weak isr_register_greedy_at; .quad isr_register_greedy_at
	.reloc ., R_X86_64_SIZE32, isr_register_greedy_at; .int 0
	.int 0x7f76124
	.quad .Lname293 /* index: 293 */
	.weak driver_with_filename; .quad driver_with_filename
	.reloc ., R_X86_64_SIZE32, driver_with_filename; .int 0
	.int 0xb2e6125
	.quad .Lname294 /* index: 294 */
	.weak vm_copyfromphys_onepage; .quad vm_copyfromphys_onepage
	.reloc ., R_X86_64_SIZE32, vm_copyfromphys_onepage; .int 0
	.int 0x8228fb5
	.quad .Lname295 /* index: 295 */
	.weak vm_map_subrange; .quad vm_map_subrange
	.reloc ., R_X86_64_SIZE32, vm_map_subrange; .int 0
	.int 0xda05f45
	.quad .Lname296 /* index: 296 */
	.weak vm_datapart_do_read_nopf; .quad vm_datapart_do_read_nopf
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_read_nopf; .int 0
	.int 0xea90df6
	.quad .Lname297 /* index: 297 */
	.weak path_traversenfull; .quad path_traversenfull
	.reloc ., R_X86_64_SIZE32, path_traversenfull; .int 0
	.int 0x564badc
	.quad .Lname298 /* index: 298 */
	.weak vm_datablock_readp; .quad vm_datablock_readp
	.reloc ., R_X86_64_SIZE32, vm_datablock_readp; .int 0
	.int 0xec43890
	.quad 0 /* index: 299 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname300 /* index: 300 */
	.weak x86_bootcpu_cpufeatures; .quad x86_bootcpu_cpufeatures
	.reloc ., R_X86_64_SIZE32, x86_bootcpu_cpufeatures; .int 0
	.int 0xfeca523
	.quad .Lname301 /* index: 301 */
	.weak sys_mprotect; .quad sys_mprotect
	.reloc ., R_X86_64_SIZE32, sys_mprotect; .int 0
	.int 0x463de4
	.quad .Lname302 /* index: 302 */
	.weak dbg_fillscreen; .quad dbg_fillscreen
	.reloc ., R_X86_64_SIZE32, dbg_fillscreen; .int 0
	.int 0xb4f412e
	.quad .Lname303 /* index: 303 */
	.weak vm_datablock_anonymous_zero; .quad vm_datablock_anonymous_zero
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous_zero; .int 0
	.int 0x142212f
	.quad 0 /* index: 304 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname305 /* index: 305 */
	.weak error_data; .quad error_data
	.reloc ., R_X86_64_SIZE32, error_data; .int 0
	.int 0x6836131
	.quad 0 /* index: 306 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname307 /* index: 307 */
	.weak instruction_trysucc; .quad instruction_trysucc
	.reloc ., R_X86_64_SIZE32, instruction_trysucc; .int 0
	.int 0x1765033
	.quad 0 /* index: 308 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname309 /* index: 309 */
	.weak sys_bind; .quad sys_bind
	.reloc ., R_X86_64_SIZE32, sys_bind; .int 0
	.int 0x9589f4
	.quad .Lname310 /* index: 310 */
	.weak sys32_preadv; .quad sys32_preadv
	.reloc ., R_X86_64_SIZE32, sys32_preadv; .int 0
	.int 0x1c8d136
	.quad .Lname311 /* index: 311 */
	.weak mempcpyw; .quad mempcpyw
	.reloc ., R_X86_64_SIZE32, mempcpyw; .int 0
	.int 0xc46a137
	.quad 0 /* index: 312 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname313 /* index: 313 */
	.weak __predict_update_si; .quad __predict_update_si
	.reloc ., R_X86_64_SIZE32, __predict_update_si; .int 0
	.int 0x455139
	.quad .Lname314 /* index: 314 */
	.weak unwind_setreg_sfpustate; .quad unwind_setreg_sfpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_sfpustate; .int 0
	.int 0xb8d03c5
	.quad .Lname315 /* index: 315 */
	.weak sys32_mq_unlink; .quad sys32_mq_unlink
	.reloc ., R_X86_64_SIZE32, sys32_mq_unlink; .int 0
	.int 0xed113b
	.quad 0 /* index: 316 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname317 /* index: 317 */
	.weak slab_ffree; .quad slab_ffree
	.reloc ., R_X86_64_SIZE32, slab_ffree; .int 0
	.int 0x85b7ac5
	.quad 0 /* index: 318 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname319 /* index: 319 */
	.weak page_iszero; .quad page_iszero
	.reloc ., R_X86_64_SIZE32, page_iszero; .int 0
	.int 0x67d713f
	.quad 0 /* index: 320 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname321 /* index: 321 */
	.weak vio_xorq; .quad vio_xorq
	.reloc ., R_X86_64_SIZE32, vio_xorq; .int 0
	.int 0x56f141
	.quad .Lname322 /* index: 322 */
	.weak character_device_register; .quad character_device_register
	.reloc ., R_X86_64_SIZE32, character_device_register; .int 0
	.int 0x4292142
	.quad .Lname323 /* index: 323 */
	.weak sys_vfork; .quad sys_vfork
	.reloc ., R_X86_64_SIZE32, sys_vfork; .int 0
	.int 0x96ccd8b
	.quad .Lname324 /* index: 324 */
	.weak debuginfo_cu_parser_nextparent; .quad debuginfo_cu_parser_nextparent
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_nextparent; .int 0
	.int 0x564a144
	.quad 0 /* index: 325 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 326 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname327 /* index: 327 */
	.weak vio_xorw; .quad vio_xorw
	.reloc ., R_X86_64_SIZE32, vio_xorw; .int 0
	.int 0x56f147
	.quad .Lname328 /* index: 328 */
	.weak sys32_linux_oldlstat; .quad sys32_linux_oldlstat
	.reloc ., R_X86_64_SIZE32, sys32_linux_oldlstat; .int 0
	.int 0x2a9c284
	.quad 0 /* index: 329 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 330 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname331 /* index: 331 */
	.weak memmoveupw; .quad memmoveupw
	.reloc ., R_X86_64_SIZE32, memmoveupw; .int 0
	.int 0x46bf037
	.quad .Lname332 /* index: 332 */
	.weak x86_userexcept_propagate; .quad x86_userexcept_propagate
	.reloc ., R_X86_64_SIZE32, x86_userexcept_propagate; .int 0
	.int 0x46cb745
	.quad .Lname333 /* index: 333 */
	.weak sys32_setgroups32; .quad sys32_setgroups32
	.reloc ., R_X86_64_SIZE32, sys32_setgroups32; .int 0
	.int 0x17ebae2
	.quad 0 /* index: 334 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 335 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 336 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname337 /* index: 337 */
	.weak ioperm_bitmap_allocf_nx; .quad ioperm_bitmap_allocf_nx
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_allocf_nx; .int 0
	.int 0x9b82838
	.quad .Lname338 /* index: 338 */
	.weak vio_xorb; .quad vio_xorb
	.reloc ., R_X86_64_SIZE32, vio_xorb; .int 0
	.int 0x56f152
	.quad .Lname339 /* index: 339 */
	.weak this_exception_subclass; .quad this_exception_subclass
	.reloc ., R_X86_64_SIZE32, this_exception_subclass; .int 0
	.int 0x4dc42e3
	.quad .Lname340 /* index: 340 */
	.weak kernel_syscall1_regcnt; .quad kernel_syscall1_regcnt
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_regcnt; .int 0
	.int 0xbda8154
	.quad .Lname341 /* index: 341 */
	.weak sys32_getgroups; .quad sys32_getgroups
	.reloc ., R_X86_64_SIZE32, sys32_getgroups; .int 0
	.int 0xc814ab3
	.quad .Lname342 /* index: 342 */
	.weak memeq_ku_nopf; .quad memeq_ku_nopf
	.reloc ., R_X86_64_SIZE32, memeq_ku_nopf; .int 0
	.int 0x1779156
	.quad .Lname343 /* index: 343 */
	.weak vpage_free; .quad vpage_free
	.reloc ., R_X86_64_SIZE32, vpage_free; .int 0
	.int 0xdb20ec5
	.quad 0 /* index: 344 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname345 /* index: 345 */
	.weak devfs_lock_read; .quad devfs_lock_read
	.reloc ., R_X86_64_SIZE32, devfs_lock_read; .int 0
	.int 0x6efc2e4
	.quad .Lname346 /* index: 346 */
	.weak vm_datapart_do_enumdma; .quad vm_datapart_do_enumdma
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_enumdma; .int 0
	.int 0x97339b1
	.quad 0 /* index: 347 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname348 /* index: 348 */
	.weak vio_xorl; .quad vio_xorl
	.reloc ., R_X86_64_SIZE32, vio_xorl; .int 0
	.int 0x56f15c
	.quad .Lname349 /* index: 349 */
	.weak sys_get_kernel_syms; .quad sys_get_kernel_syms
	.reloc ., R_X86_64_SIZE32, sys_get_kernel_syms; .int 0
	.int 0x98e3ab3
	.quad .Lname350 /* index: 350 */
	.weak dbg_main; .quad dbg_main
	.reloc ., R_X86_64_SIZE32, dbg_main; .int 0
	.int 0x8d6315e
	.quad .Lname351 /* index: 351 */
	.weak sys_timerfd_create; .quad sys_timerfd_create
	.reloc ., R_X86_64_SIZE32, sys_timerfd_create; .int 0
	.int 0xc24a2e5
	.quad 0 /* index: 352 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 353 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname354 /* index: 354 */
	.weak sys32_unlinkat; .quad sys32_unlinkat
	.reloc ., R_X86_64_SIZE32, sys32_unlinkat; .int 0
	.int 0x54ad094
	.quad .Lname355 /* index: 355 */
	.weak handle_get_vfs; .quad handle_get_vfs
	.reloc ., R_X86_64_SIZE32, handle_get_vfs; .int 0
	.int 0x5834163
	.quad 0 /* index: 356 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname357 /* index: 357 */
	.weak debuginfo_location_getvalue; .quad debuginfo_location_getvalue
	.reloc ., R_X86_64_SIZE32, debuginfo_location_getvalue; .int 0
	.int 0xabab165
	.quad .Lname358 /* index: 358 */
	.weak vm_copytophys_onepage_nopf; .quad vm_copytophys_onepage_nopf
	.reloc ., R_X86_64_SIZE32, vm_copytophys_onepage_nopf; .int 0
	.int 0xdee3166
	.quad .Lname359 /* index: 359 */
	.weak error_rethrow; .quad error_rethrow
	.reloc ., R_X86_64_SIZE32, error_rethrow; .int 0
	.int 0x4539167
	.quad 0 /* index: 360 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname361 /* index: 361 */
	.weak unwind_cfa_sigframe_apply; .quad unwind_cfa_sigframe_apply
	.reloc ., R_X86_64_SIZE32, unwind_cfa_sigframe_apply; .int 0
	.int 0xd478169
	.quad 0 /* index: 362 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname363 /* index: 363 */
	.weak sys32_set_tid_address; .quad sys32_set_tid_address
	.reloc ., R_X86_64_SIZE32, sys32_set_tid_address; .int 0
	.int 0x7a96023
	.quad .Lname364 /* index: 364 */
	.weak sys32_afs_syscall; .quad sys32_afs_syscall
	.reloc ., R_X86_64_SIZE32, sys32_afs_syscall; .int 0
	.int 0x325492c
	.quad .Lname365 /* index: 365 */
	.weak vm_pageinphys; .quad vm_pageinphys
	.reloc ., R_X86_64_SIZE32, vm_pageinphys; .int 0
	.int 0x6d309a3
	.quad 0 /* index: 366 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 367 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname368 /* index: 368 */
	.weak vm_datapart_map_ram_autoprop; .quad vm_datapart_map_ram_autoprop
	.reloc ., R_X86_64_SIZE32, vm_datapart_map_ram_autoprop; .int 0
	.int 0x9192170
	.quad 0 /* index: 369 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname370 /* index: 370 */
	.weak __rawmemchr; .quad __rawmemchr
	.reloc ., R_X86_64_SIZE32, __rawmemchr; .int 0
	.int 0xe5f5172
	.quad .Lname371 /* index: 371 */
	.weak sys_exit; .quad sys_exit
	.reloc ., R_X86_64_SIZE32, sys_exit; .int 0
	.int 0x95cab4
	.quad .Lname372 /* index: 372 */
	.weak sys32_clock_getres64; .quad sys32_clock_getres64
	.reloc ., R_X86_64_SIZE32, sys32_clock_getres64; .int 0
	.int 0xff85174
	.quad .Lname373 /* index: 373 */
	.weak inode_file_pwritev_with_pwrite; .quad inode_file_pwritev_with_pwrite
	.reloc ., R_X86_64_SIZE32, inode_file_pwritev_with_pwrite; .int 0
	.int 0x9350175
	.quad 0 /* index: 374 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname375 /* index: 375 */
	.weak sys_lsetxattr; .quad sys_lsetxattr
	.reloc ., R_X86_64_SIZE32, sys_lsetxattr; .int 0
	.int 0x7b7e852
	.quad .Lname376 /* index: 376 */
	.weak heap_align_nx; .quad heap_align_nx
	.reloc ., R_X86_64_SIZE32, heap_align_nx; .int 0
	.int 0xc466178
	.quad .Lname377 /* index: 377 */
	.weak x86_dbg_owner_lapicid; .quad x86_dbg_owner_lapicid
	.reloc ., R_X86_64_SIZE32, x86_dbg_owner_lapicid; .int 0
	.int 0x818b944
	.quad 0 /* index: 378 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 379 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname380 /* index: 380 */
	.weak vm_datapart_allocswap_nx; .quad vm_datapart_allocswap_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_allocswap_nx; .int 0
	.int 0x2e164d8
	.quad 0 /* index: 381 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname382 /* index: 382 */
	.weak unwind_getreg_scpustate_exclusive; .quad unwind_getreg_scpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_scpustate_exclusive; .int 0
	.int 0xb8e5065
	.quad .Lname383 /* index: 383 */
	.weak sys_lookup_dcookie; .quad sys_lookup_dcookie
	.reloc ., R_X86_64_SIZE32, sys_lookup_dcookie; .int 0
	.int 0x9781595
	.quad .Lname384 /* index: 384 */
	.weak sys32_rpc_service; .quad sys32_rpc_service
	.reloc ., R_X86_64_SIZE32, sys32_rpc_service; .int 0
	.int 0x1dba095
	.quad 0 /* index: 385 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname386 /* index: 386 */
	.weak vm_datapart_pageaddr; .quad vm_datapart_pageaddr
	.reloc ., R_X86_64_SIZE32, vm_datapart_pageaddr; .int 0
	.int 0x2085182
	.quad .Lname387 /* index: 387 */
	.weak character_device_sync; .quad character_device_sync
	.reloc ., R_X86_64_SIZE32, character_device_sync; .int 0
	.int 0x98ba183
	.quad .Lname388 /* index: 388 */
	.weak driver_symbol_at; .quad driver_symbol_at
	.reloc ., R_X86_64_SIZE32, driver_symbol_at; .int 0
	.int 0xf58d184
	.quad .Lname389 /* index: 389 */
	.weak sys_init_module; .quad sys_init_module
	.reloc ., R_X86_64_SIZE32, sys_init_module; .int 0
	.int 0xd65f185
	.quad .Lname390 /* index: 390 */
	.weak sys_process_vm_readv; .quad sys_process_vm_readv
	.reloc ., R_X86_64_SIZE32, sys_process_vm_readv; .int 0
	.int 0xc34a186
	.quad .Lname391 /* index: 391 */
	.weak unwind_getreg_lcpustate; .quad unwind_getreg_lcpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_lcpustate; .int 0
	.int 0xb8c48b5
	.quad .Lname392 /* index: 392 */
	.weak __predict_update_eax; .quad __predict_update_eax
	.reloc ., R_X86_64_SIZE32, __predict_update_eax; .int 0
	.int 0x4552188
	.quad .Lname393 /* index: 393 */
	.weak task_setup_kernel; .quad task_setup_kernel
	.reloc ., R_X86_64_SIZE32, task_setup_kernel; .int 0
	.int 0x4fac2ec
	.quad .Lname394 /* index: 394 */
	.weak pagedir_unmap; .quad pagedir_unmap
	.reloc ., R_X86_64_SIZE32, pagedir_unmap; .int 0
	.int 0x21808f0
	.quad .Lname395 /* index: 395 */
	.weak syscall_trace_compat; .quad syscall_trace_compat
	.reloc ., R_X86_64_SIZE32, syscall_trace_compat; .int 0
	.int 0x3c5b9a4
	.quad 0 /* index: 396 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname397 /* index: 397 */
	.weak kernel_syscall1_restartmode32; .quad kernel_syscall1_restartmode32
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_restartmode32; .int 0
	.int 0x8fa9042
	.quad 0 /* index: 398 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname399 /* index: 399 */
	.weak handle_lookup_nosym; .quad handle_lookup_nosym
	.reloc ., R_X86_64_SIZE32, handle_lookup_nosym; .int 0
	.int 0xaf79aed
	.quad 0 /* index: 400 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname401 /* index: 401 */
	.weak sys32_create_module; .quad sys32_create_module
	.reloc ., R_X86_64_SIZE32, sys32_create_module; .int 0
	.int 0x5c85ab5
	.quad 0 /* index: 402 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname403 /* index: 403 */
	.weak keymap_init_en_US; .quad keymap_init_en_US
	.reloc ., R_X86_64_SIZE32, keymap_init_en_US; .int 0
	.int 0x2701193
	.quad 0 /* index: 404 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname405 /* index: 405 */
	.weak inode_datablock_type; .quad inode_datablock_type
	.reloc ., R_X86_64_SIZE32, inode_datablock_type; .int 0
	.int 0x60c0195
	.quad .Lname406 /* index: 406 */
	.weak vm_readphysq; .quad vm_readphysq
	.reloc ., R_X86_64_SIZE32, vm_readphysq; .int 0
	.int 0x65a811
	.quad .Lname407 /* index: 407 */
	.weak ttybase_device_stat; .quad ttybase_device_stat
	.reloc ., R_X86_64_SIZE32, ttybase_device_stat; .int 0
	.int 0xb53ee94
	.quad .Lname408 /* index: 408 */
	.weak cpu_private_function_callbuf_ex; .quad cpu_private_function_callbuf_ex
	.reloc ., R_X86_64_SIZE32, cpu_private_function_callbuf_ex; .int 0
	.int 0x1a95198
	.quad .Lname409 /* index: 409 */
	.weak krand; .quad krand
	.reloc ., R_X86_64_SIZE32, krand; .int 0
	.int 0x728844
	.quad 0 /* index: 410 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname411 /* index: 411 */
	.weak inode_awritek; .quad inode_awritek
	.reloc ., R_X86_64_SIZE32, inode_awritek; .int 0
	.int 0x8bea19b
	.quad .Lname412 /* index: 412 */
	.weak vm86_pic_intr; .quad vm86_pic_intr
	.reloc ., R_X86_64_SIZE32, vm86_pic_intr; .int 0
	.int 0x29e43a2
	.quad .Lname413 /* index: 413 */
	.weak x86_userexcept_seterrno64; .quad x86_userexcept_seterrno64
	.reloc ., R_X86_64_SIZE32, x86_userexcept_seterrno64; .int 0
	.int 0xc2f6b14
	.quad .Lname414 /* index: 414 */
	.weak mempmovedown; .quad mempmovedown
	.reloc ., R_X86_64_SIZE32, mempmovedown; .int 0
	.int 0x1f7f19e
	.quad .Lname415 /* index: 415 */
	.weak mall_dump_leaks; .quad mall_dump_leaks
	.reloc ., R_X86_64_SIZE32, mall_dump_leaks; .int 0
	.int 0x7877fe3
	.quad 0 /* index: 416 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname417 /* index: 417 */
	.weak rawmemrchrq; .quad rawmemrchrq
	.reloc ., R_X86_64_SIZE32, rawmemrchrq; .int 0
	.int 0xc3011a1
	.quad .Lname418 /* index: 418 */
	.weak sys32_getegid32; .quad sys32_getegid32
	.reloc ., R_X86_64_SIZE32, sys32_getegid32; .int 0
	.int 0xcd5d1a2
	.quad .Lname419 /* index: 419 */
	.weak aio_pbuffer_copytovphys; .quad aio_pbuffer_copytovphys
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copytovphys; .int 0
	.int 0x9c6c1a3
	.quad .Lname420 /* index: 420 */
	.weak page_malloc_at; .quad page_malloc_at
	.reloc ., R_X86_64_SIZE32, page_malloc_at; .int 0
	.int 0x70ef1a4
	.quad .Lname421 /* index: 421 */
	.weak path_getcasechild_and_parent_inode; .quad path_getcasechild_and_parent_inode
	.reloc ., R_X86_64_SIZE32, path_getcasechild_and_parent_inode; .int 0
	.int 0xc54a1a5
	.quad .Lname422 /* index: 422 */
	.weak x86_fpustate_save; .quad x86_fpustate_save
	.reloc ., R_X86_64_SIZE32, x86_fpustate_save; .int 0
	.int 0x7b18e15
	.quad .Lname423 /* index: 423 */
	.weak rawmemrchrw; .quad rawmemrchrw
	.reloc ., R_X86_64_SIZE32, rawmemrchrw; .int 0
	.int 0xc3011a7
	.quad .Lname424 /* index: 424 */
	.weak __predict_update_ecx; .quad __predict_update_ecx
	.reloc ., R_X86_64_SIZE32, __predict_update_ecx; .int 0
	.int 0x45521a8
	.quad .Lname425 /* index: 425 */
	.weak sys32_truncate; .quad sys32_truncate
	.reloc ., R_X86_64_SIZE32, sys32_truncate; .int 0
	.int 0x9e219a5
	.quad .Lname426 /* index: 426 */
	.weak sys_open_by_handle_at; .quad sys_open_by_handle_at
	.reloc ., R_X86_64_SIZE32, sys_open_by_handle_at; .int 0
	.int 0x86bfac4
	.quad .Lname427 /* index: 427 */
	.weak vm_addhwbreak; .quad vm_addhwbreak
	.reloc ., R_X86_64_SIZE32, vm_addhwbreak; .int 0
	.int 0x2ecf1ab
	.quad .Lname428 /* index: 428 */
	.weak aio_multihandle_cancel; .quad aio_multihandle_cancel
	.reloc ., R_X86_64_SIZE32, aio_multihandle_cancel; .int 0
	.int 0xdde61ac
	.quad .Lname429 /* index: 429 */
	.weak vm_unmap_kernel_ram; .quad vm_unmap_kernel_ram
	.reloc ., R_X86_64_SIZE32, vm_unmap_kernel_ram; .int 0
	.int 0x1d6b1ad
	.quad 0 /* index: 430 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 431 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname432 /* index: 432 */
	.weak sys32_readdir; .quad sys32_readdir
	.reloc ., R_X86_64_SIZE32, sys32_readdir; .int 0
	.int 0x3b1c312
	.quad 0 /* index: 433 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname434 /* index: 434 */
	.weak block_device_awritev_sector; .quad block_device_awritev_sector
	.reloc ., R_X86_64_SIZE32, block_device_awritev_sector; .int 0
	.int 0x173a1b2
	.quad .Lname435 /* index: 435 */
	.weak sys32_fstatfs; .quad sys32_fstatfs
	.reloc ., R_X86_64_SIZE32, sys32_fstatfs; .int 0
	.int 0x6ace2f3
	.quad 0 /* index: 436 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname437 /* index: 437 */
	.weak handle_get_regular_node; .quad handle_get_regular_node
	.reloc ., R_X86_64_SIZE32, handle_get_regular_node; .int 0
	.int 0xc3701b5
	.quad .Lname438 /* index: 438 */
	.weak sys_sched_getattr; .quad sys_sched_getattr
	.reloc ., R_X86_64_SIZE32, sys_sched_getattr; .int 0
	.int 0x42f3a82
	.quad .Lname439 /* index: 439 */
	.weak vm86_outw; .quad vm86_outw
	.reloc ., R_X86_64_SIZE32, vm86_outw; .int 0
	.int 0xbc611b7
	.quad .Lname440 /* index: 440 */
	.weak __predict_update_edx; .quad __predict_update_edx
	.reloc ., R_X86_64_SIZE32, __predict_update_edx; .int 0
	.int 0x45521b8
	.quad .Lname441 /* index: 441 */
	.weak dbg_trygetuni; .quad dbg_trygetuni
	.reloc ., R_X86_64_SIZE32, dbg_trygetuni; .int 0
	.int 0x551d1b9
	.quad .Lname442 /* index: 442 */
	.weak sys32_statfs64; .quad sys32_statfs64
	.reloc ., R_X86_64_SIZE32, sys32_statfs64; .int 0
	.int 0xaec5784
	.quad 0 /* index: 443 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname444 /* index: 444 */
	.weak rawmemrchrl; .quad rawmemrchrl
	.reloc ., R_X86_64_SIZE32, rawmemrchrl; .int 0
	.int 0xc3011bc
	.quad 0 /* index: 445 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 446 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname447 /* index: 447 */
	.weak symtab_scantable; .quad symtab_scantable
	.reloc ., R_X86_64_SIZE32, symtab_scantable; .int 0
	.int 0xe2ba2f5
	.quad .Lname448 /* index: 448 */
	.weak sys_getsockname; .quad sys_getsockname
	.reloc ., R_X86_64_SIZE32, sys_getsockname; .int 0
	.int 0xcddf895
	.quad 0 /* index: 449 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname450 /* index: 450 */
	.weak sys_setuid; .quad sys_setuid
	.reloc ., R_X86_64_SIZE32, sys_setuid; .int 0
	.int 0x69b0b64
	.quad .Lname451 /* index: 451 */
	.weak dbg_trygetc; .quad dbg_trygetc
	.reloc ., R_X86_64_SIZE32, dbg_trygetc; .int 0
	.int 0xbf551c3
	.quad .Lname452 /* index: 452 */
	.weak json_parser_getfloat; .quad json_parser_getfloat
	.reloc ., R_X86_64_SIZE32, json_parser_getfloat; .int 0
	.int 0xf5511c4
	.quad .Lname453 /* index: 453 */
	.weak memset_nopf; .quad memset_nopf
	.reloc ., R_X86_64_SIZE32, memset_nopf; .int 0
	.int 0xcf792f6
	.quad .Lname454 /* index: 454 */
	.weak sys32_readf; .quad sys32_readf
	.reloc ., R_X86_64_SIZE32, sys32_readf; .int 0
	.int 0x813b1c6
	.quad .Lname455 /* index: 455 */
	.weak sys32_sigpending; .quad sys32_sigpending
	.reloc ., R_X86_64_SIZE32, sys32_sigpending; .int 0
	.int 0x4581c7
	.quad .Lname456 /* index: 456 */
	.weak driver_symbol_ex; .quad driver_symbol_ex
	.reloc ., R_X86_64_SIZE32, driver_symbol_ex; .int 0
	.int 0xf58d1c8
	.quad 0 /* index: 457 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname458 /* index: 458 */
	.weak sys_klstat; .quad sys_klstat
	.reloc ., R_X86_64_SIZE32, sys_klstat; .int 0
	.int 0x6241a14
	.quad .Lname459 /* index: 459 */
	.weak vm_datapart_lock_trywrite; .quad vm_datapart_lock_trywrite
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_trywrite; .int 0
	.int 0x20bd485
	.quad 0 /* index: 460 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname461 /* index: 461 */
	.weak sys_vserver; .quad sys_vserver
	.reloc ., R_X86_64_SIZE32, sys_vserver; .int 0
	.int 0xde795a2
	.quad 0 /* index: 462 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname463 /* index: 463 */
	.weak vm_datapart_allocram; .quad vm_datapart_allocram
	.reloc ., R_X86_64_SIZE32, vm_datapart_allocram; .int 0
	.int 0x906804d
	.quad 0 /* index: 464 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname465 /* index: 465 */
	.weak vm_tasklock_tryservice; .quad vm_tasklock_tryservice
	.reloc ., R_X86_64_SIZE32, vm_tasklock_tryservice; .int 0
	.int 0xd50a3a5
	.quad 0 /* index: 466 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname467 /* index: 467 */
	.weak sys32_get_kernel_syms; .quad sys32_get_kernel_syms
	.reloc ., R_X86_64_SIZE32, sys32_get_kernel_syms; .int 0
	.int 0xc6f41d3
	.quad .Lname468 /* index: 468 */
	.weak directory_readnext; .quad directory_readnext
	.reloc ., R_X86_64_SIZE32, directory_readnext; .int 0
	.int 0x6a431d4
	.quad .Lname469 /* index: 469 */
	.weak superblock_mountlock_write; .quad superblock_mountlock_write
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_write; .int 0
	.int 0x33791d5
	.quad .Lname470 /* index: 470 */
	.weak disasm_print_line_nolf; .quad disasm_print_line_nolf
	.reloc ., R_X86_64_SIZE32, disasm_print_line_nolf; .int 0
	.int 0xc69e1d6
	.quad 0 /* index: 471 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 472 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname473 /* index: 473 */
	.weak ioperm_bitmap_copy; .quad ioperm_bitmap_copy
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_copy; .int 0
	.int 0xe1b01d9
	.quad 0 /* index: 474 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname475 /* index: 475 */
	.weak sys_msgget; .quad sys_msgget
	.reloc ., R_X86_64_SIZE32, sys_msgget; .int 0
	.int 0x64e6d54
	.quad .Lname476 /* index: 476 */
	.weak sys_iopl; .quad sys_iopl
	.reloc ., R_X86_64_SIZE32, sys_iopl; .int 0
	.int 0x9601dc
	.quad 0 /* index: 477 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname478 /* index: 478 */
	.weak sys32_swapon; .quad sys32_swapon
	.reloc ., R_X86_64_SIZE32, sys32_swapon; .int 0
	.int 0x11de1de
	.quad .Lname479 /* index: 479 */
	.weak kernel_debugtrap_r_ucpustate; .quad kernel_debugtrap_r_ucpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_ucpustate; .int 0
	.int 0xed53da5
	.quad .Lname480 /* index: 480 */
	.weak pagedir_iswritable_p; .quad pagedir_iswritable_p
	.reloc ., R_X86_64_SIZE32, pagedir_iswritable_p; .int 0
	.int 0x9aa4b40
	.quad .Lname481 /* index: 481 */
	.weak this_sigqueue; .quad this_sigqueue
	.reloc ., R_X86_64_SIZE32, this_sigqueue; .int 0
	.int 0x5182a55
	.quad 0 /* index: 482 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 483 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname484 /* index: 484 */
	.weak sys32_linux_lstat64; .quad sys32_linux_lstat64
	.reloc ., R_X86_64_SIZE32, sys32_linux_lstat64; .int 0
	.int 0x9a921e4
	.quad .Lname485 /* index: 485 */
	.weak sys32_ioctlf; .quad sys32_ioctlf
	.reloc ., R_X86_64_SIZE32, sys32_ioctlf; .int 0
	.int 0x255cda6
	.quad .Lname486 /* index: 486 */
	.weak getreg_sfpuenv; .quad getreg_sfpuenv
	.reloc ., R_X86_64_SIZE32, getreg_sfpuenv; .int 0
	.int 0x56f01e6
	.quad 0 /* index: 487 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname488 /* index: 488 */
	.weak rwlock_upgrade_nx; .quad rwlock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, rwlock_upgrade_nx; .int 0
	.int 0x2f591e8
	.quad .Lname489 /* index: 489 */
	.weak character_device_destroy; .quad character_device_destroy
	.reloc ., R_X86_64_SIZE32, character_device_destroy; .int 0
	.int 0xa3621e9
	.quad .Lname490 /* index: 490 */
	.weak vm_datablock_read_unsafe; .quad vm_datablock_read_unsafe
	.reloc ., R_X86_64_SIZE32, vm_datablock_read_unsafe; .int 0
	.int 0x881af05
	.quad .Lname491 /* index: 491 */
	.weak x86_emulock_cmpxchg128; .quad x86_emulock_cmpxchg128
	.reloc ., R_X86_64_SIZE32, x86_emulock_cmpxchg128; .int 0
	.int 0x3483ab8
	.quad .Lname492 /* index: 492 */
	.weak heap_validate_all; .quad heap_validate_all
	.reloc ., R_X86_64_SIZE32, heap_validate_all; .int 0
	.int 0xe01c1ec
	.quad .Lname493 /* index: 493 */
	.weak sys32_rmdir; .quad sys32_rmdir
	.reloc ., R_X86_64_SIZE32, sys32_rmdir; .int 0
	.int 0x8143d62
	.quad 0 /* index: 494 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname495 /* index: 495 */
	.weak vm_datapart_freeram; .quad vm_datapart_freeram
	.reloc ., R_X86_64_SIZE32, vm_datapart_freeram; .int 0
	.int 0x8d6fafd
	.quad .Lname496 /* index: 496 */
	.weak regdump_gpregs_with_sp; .quad regdump_gpregs_with_sp
	.reloc ., R_X86_64_SIZE32, regdump_gpregs_with_sp; .int 0
	.int 0x242e1f0
	.quad 0 /* index: 497 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname498 /* index: 498 */
	.weak slab_kmalloc32; .quad slab_kmalloc32
	.reloc ., R_X86_64_SIZE32, slab_kmalloc32; .int 0
	.int 0x66b31f2
	.quad .Lname499 /* index: 499 */
	.weak dbg_getallregs; .quad dbg_getallregs
	.reloc ., R_X86_64_SIZE32, dbg_getallregs; .int 0
	.int 0x10651f3
	.quad .Lname500 /* index: 500 */
	.weak dbg_editfield; .quad dbg_editfield
	.reloc ., R_X86_64_SIZE32, dbg_editfield; .int 0
	.int 0xa21a1f4
	.quad .Lname501 /* index: 501 */
	.weak cpu_schedule_idle_job_simple; .quad cpu_schedule_idle_job_simple
	.reloc ., R_X86_64_SIZE32, cpu_schedule_idle_job_simple; .int 0
	.int 0xabc61f5
	.quad 0 /* index: 502 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname503 /* index: 503 */
	.weak sys32_setpriority; .quad sys32_setpriority
	.reloc ., R_X86_64_SIZE32, sys32_setpriority; .int 0
	.int 0xf45da9
	.quad 0 /* index: 504 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname505 /* index: 505 */
	.weak sys32_mprotect; .quad sys32_mprotect
	.reloc ., R_X86_64_SIZE32, sys32_mprotect; .int 0
	.int 0x7f02854
	.quad .Lname506 /* index: 506 */
	.weak sys_lfutexexpr; .quad sys_lfutexexpr
	.reloc ., R_X86_64_SIZE32, sys_lfutexexpr; .int 0
	.int 0xa58e502
	.quad .Lname507 /* index: 507 */
	.weak this_sigmask; .quad this_sigmask
	.reloc ., R_X86_64_SIZE32, this_sigmask; .int 0
	.int 0xe5331fb
	.quad .Lname508 /* index: 508 */
	.weak x86_syscall_emulate_sysvabi; .quad x86_syscall_emulate_sysvabi
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate_sysvabi; .int 0
	.int 0x3794689
	.quad 0 /* index: 509 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname510 /* index: 510 */
	.weak unicode_readutf16_swap_n; .quad unicode_readutf16_swap_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_swap_n; .int 0
	.int 0x1561fe
	.quad .Lname511 /* index: 511 */
	.weak dbg_setregbyname; .quad dbg_setregbyname
	.reloc ., R_X86_64_SIZE32, dbg_setregbyname; .int 0
	.int 0xb065855
	.quad .Lname512 /* index: 512 */
	.weak sys_signalfd; .quad sys_signalfd
	.reloc ., R_X86_64_SIZE32, sys_signalfd; .int 0
	.int 0x874f454
	.quad 0 /* index: 513 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname514 /* index: 514 */
	.weak linebuffer_rewrite; .quad linebuffer_rewrite
	.reloc ., R_X86_64_SIZE32, linebuffer_rewrite; .int 0
	.int 0x4321d55
	.quad .Lname515 /* index: 515 */
	.weak sys32_munlock; .quad sys32_munlock
	.reloc ., R_X86_64_SIZE32, sys32_munlock; .int 0
	.int 0xfc35dab
	.quad .Lname516 /* index: 516 */
	.weak regdump_idt; .quad regdump_idt
	.reloc ., R_X86_64_SIZE32, regdump_idt; .int 0
	.int 0xc3ee204
	.quad .Lname517 /* index: 517 */
	.weak acpi_mode; .quad acpi_mode
	.reloc ., R_X86_64_SIZE32, acpi_mode; .int 0
	.int 0x6f66205
	.quad .Lname518 /* index: 518 */
	.weak snprintf; .quad snprintf
	.reloc ., R_X86_64_SIZE32, snprintf; .int 0
	.int 0x5790206
	.quad .Lname519 /* index: 519 */
	.weak error_throw; .quad error_throw
	.reloc ., R_X86_64_SIZE32, error_throw; .int 0
	.int 0x8066207
	.quad .Lname520 /* index: 520 */
	.weak __predict_update_cx; .quad __predict_update_cx
	.reloc ., R_X86_64_SIZE32, __predict_update_cx; .int 0
	.int 0x455208
	.quad 0 /* index: 521 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname522 /* index: 522 */
	.weak unicode_readutf16_n; .quad unicode_readutf16_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_n; .int 0
	.int 0xb8e5a3e
	.quad .Lname523 /* index: 523 */
	.weak inode_readk; .quad inode_readk
	.reloc ., R_X86_64_SIZE32, inode_readk; .int 0
	.int 0xb18e20b
	.quad .Lname524 /* index: 524 */
	.weak __predict_update_dl; .quad __predict_update_dl
	.reloc ., R_X86_64_SIZE32, __predict_update_dl; .int 0
	.int 0x45520c
	.quad 0 /* index: 525 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname526 /* index: 526 */
	.weak cpu_idlemain; .quad cpu_idlemain
	.reloc ., R_X86_64_SIZE32, cpu_idlemain; .int 0
	.int 0xd8d820e
	.quad .Lname527 /* index: 527 */
	.weak task_tryyield_or_pause; .quad task_tryyield_or_pause
	.reloc ., R_X86_64_SIZE32, task_tryyield_or_pause; .int 0
	.int 0xa8862a5
	.quad .Lname528 /* index: 528 */
	.weak vm_datablock_writevp; .quad vm_datablock_writevp
	.reloc ., R_X86_64_SIZE32, vm_datablock_writevp; .int 0
	.int 0x21f8210
	.quad 0 /* index: 529 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname530 /* index: 530 */
	.weak dbg_enter_lcpustate_c; .quad dbg_enter_lcpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_lcpustate_c; .int 0
	.int 0x1b63ed3
	.quad .Lname531 /* index: 531 */
	.weak sprintf_s; .quad sprintf_s
	.reloc ., R_X86_64_SIZE32, sprintf_s; .int 0
	.int 0x905d213
	.quad .Lname532 /* index: 532 */
	.weak driver_fde_find; .quad driver_fde_find
	.reloc ., R_X86_64_SIZE32, driver_fde_find; .int 0
	.int 0xa79e214
	.quad .Lname533 /* index: 533 */
	.weak cpu_apply_lcpustate; .quad cpu_apply_lcpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_lcpustate; .int 0
	.int 0xa8cb215
	.quad .Lname534 /* index: 534 */
	.weak inode_readv; .quad inode_readv
	.reloc ., R_X86_64_SIZE32, inode_readv; .int 0
	.int 0xb18e216
	.quad .Lname535 /* index: 535 */
	.weak sys_recvmmsg; .quad sys_recvmmsg
	.reloc ., R_X86_64_SIZE32, sys_recvmmsg; .int 0
	.int 0xc1db217
	.quad .Lname536 /* index: 536 */
	.weak __predict_update_dx; .quad __predict_update_dx
	.reloc ., R_X86_64_SIZE32, __predict_update_dx; .int 0
	.int 0x455218
	.quad .Lname537 /* index: 537 */
	.weak sys32_sched_getaffinity; .quad sys32_sched_getaffinity
	.reloc ., R_X86_64_SIZE32, sys32_sched_getaffinity; .int 0
	.int 0xe812219
	.quad 0 /* index: 538 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname539 /* index: 539 */
	.weak __cpuset_full_mask; .quad __cpuset_full_mask
	.reloc ., R_X86_64_SIZE32, __cpuset_full_mask; .int 0
	.int 0xe99c21b
	.quad 0 /* index: 540 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 541 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 542 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname543 /* index: 543 */
	.weak task_sleep_cputime; .quad task_sleep_cputime
	.reloc ., R_X86_64_SIZE32, task_sleep_cputime; .int 0
	.int 0x5ffcb05
	.quad .Lname544 /* index: 544 */
	.weak cred_require_debugtrap; .quad cred_require_debugtrap
	.reloc ., R_X86_64_SIZE32, cred_require_debugtrap; .int 0
	.int 0x35b8220
	.quad .Lname545 /* index: 545 */
	.weak vm_datapart_do_read; .quad vm_datapart_do_read
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_read; .int 0
	.int 0x2bb9e4
	.quad .Lname546 /* index: 546 */
	.weak vmb_node_remove; .quad vmb_node_remove
	.reloc ., R_X86_64_SIZE32, vmb_node_remove; .int 0
	.int 0xeef2165
	.quad .Lname547 /* index: 547 */
	.weak inode_readv_phys; .quad inode_readv_phys
	.reloc ., R_X86_64_SIZE32, inode_readv_phys; .int 0
	.int 0x117e223
	.quad .Lname548 /* index: 548 */
	.weak block_device_read; .quad block_device_read
	.reloc ., R_X86_64_SIZE32, block_device_read; .int 0
	.int 0x8a57224
	.quad .Lname549 /* index: 549 */
	.weak debuginfo_location_setvalue; .quad debuginfo_location_setvalue
	.reloc ., R_X86_64_SIZE32, debuginfo_location_setvalue; .int 0
	.int 0xabab225
	.quad 0 /* index: 550 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname551 /* index: 551 */
	.weak cpu_assert_sleeping; .quad cpu_assert_sleeping
	.reloc ., R_X86_64_SIZE32, cpu_assert_sleeping; .int 0
	.int 0x10eb227
	.quad .Lname552 /* index: 552 */
	.weak __predict_update_ax; .quad __predict_update_ax
	.reloc ., R_X86_64_SIZE32, __predict_update_ax; .int 0
	.int 0x455228
	.quad .Lname553 /* index: 553 */
	.weak sys_setfsuid; .quad sys_setfsuid
	.reloc ., R_X86_64_SIZE32, sys_setfsuid; .int 0
	.int 0xb1d3d64
	.quad .Lname554 /* index: 554 */
	.weak strto64; .quad strto64
	.reloc ., R_X86_64_SIZE32, strto64; .int 0
	.int 0xab9b2e4
	.quad 0 /* index: 555 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname556 /* index: 556 */
	.weak sys32_socketcall; .quad sys32_socketcall
	.reloc ., R_X86_64_SIZE32, sys32_socketcall; .int 0
	.int 0x74ba22c
	.quad .Lname557 /* index: 557 */
	.weak dbg_enter_icpustate_cr; .quad dbg_enter_icpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_icpustate_cr; .int 0
	.int 0xab3edb2
	.quad .Lname558 /* index: 558 */
	.weak x86_userexcept_seterrno32; .quad x86_userexcept_seterrno32
	.reloc ., R_X86_64_SIZE32, x86_userexcept_seterrno32; .int 0
	.int 0xc2f6be2
	.quad .Lname559 /* index: 559 */
	.weak vm_kernel_treelock_tryread; .quad vm_kernel_treelock_tryread
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_tryread; .int 0
	.int 0x8338234
	.quad .Lname560 /* index: 560 */
	.weak vio_xchb; .quad vio_xchb
	.reloc ., R_X86_64_SIZE32, vio_xchb; .int 0
	.int 0x56ee32
	.quad 0 /* index: 561 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname562 /* index: 562 */
	.weak vm_exec_assert_regular; .quad vm_exec_assert_regular
	.reloc ., R_X86_64_SIZE32, vm_exec_assert_regular; .int 0
	.int 0xecfc232
	.quad 0 /* index: 563 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname564 /* index: 564 */
	.weak cpu_quantum_elapsed; .quad cpu_quantum_elapsed
	.reloc ., R_X86_64_SIZE32, cpu_quantum_elapsed; .int 0
	.int 0x6089234
	.quad .Lname565 /* index: 565 */
	.weak driver_getfilename; .quad driver_getfilename
	.reloc ., R_X86_64_SIZE32, driver_getfilename; .int 0
	.int 0xed08235
	.quad .Lname566 /* index: 566 */
	.weak block_device_readv; .quad block_device_readv
	.reloc ., R_X86_64_SIZE32, block_device_readv; .int 0
	.int 0xa572236
	.quad 0 /* index: 567 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname568 /* index: 568 */
	.weak pagedir_prepare_mapone; .quad pagedir_prepare_mapone
	.reloc ., R_X86_64_SIZE32, pagedir_prepare_mapone; .int 0
	.int 0x749dd55
	.quad .Lname569 /* index: 569 */
	.weak fs_destroy; .quad fs_destroy
	.reloc ., R_X86_64_SIZE32, fs_destroy; .int 0
	.int 0xacc6239
	.quad 0 /* index: 570 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname571 /* index: 571 */
	.weak sys_ioctl; .quad sys_ioctl
	.reloc ., R_X86_64_SIZE32, sys_ioctl; .int 0
	.int 0x96021ac
	.quad .Lname572 /* index: 572 */
	.weak __predict_update_cl; .quad __predict_update_cl
	.reloc ., R_X86_64_SIZE32, __predict_update_cl; .int 0
	.int 0x45523c
	.quad 0 /* index: 573 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname574 /* index: 574 */
	.weak blocking_cleanup_chain; .quad blocking_cleanup_chain
	.reloc ., R_X86_64_SIZE32, blocking_cleanup_chain; .int 0
	.int 0x268423e
	.quad .Lname575 /* index: 575 */
	.weak handle_close; .quad handle_close
	.reloc ., R_X86_64_SIZE32, handle_close; .int 0
	.int 0xdb27db5
	.quad .Lname576 /* index: 576 */
	.weak sys_debugtrap; .quad sys_debugtrap
	.reloc ., R_X86_64_SIZE32, sys_debugtrap; .int 0
	.int 0x2b7e240
	.quad .Lname577 /* index: 577 */
	.weak superblock_statfs; .quad superblock_statfs
	.reloc ., R_X86_64_SIZE32, superblock_statfs; .int 0
	.int 0xfa32a03
	.quad .Lname578 /* index: 578 */
	.weak format_sprintf_printer; .quad format_sprintf_printer
	.reloc ., R_X86_64_SIZE32, format_sprintf_printer; .int 0
	.int 0xcfb4242
	.quad 0 /* index: 579 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname580 /* index: 580 */
	.weak sys_setresuid; .quad sys_setresuid
	.reloc ., R_X86_64_SIZE32, sys_setresuid; .int 0
	.int 0x85c244
	.quad .Lname581 /* index: 581 */
	.weak ansitty_device_write; .quad ansitty_device_write
	.reloc ., R_X86_64_SIZE32, ansitty_device_write; .int 0
	.int 0xb630245
	.quad .Lname582 /* index: 582 */
	.weak _ZSt9terminatev; .quad _ZSt9terminatev
	.reloc ., R_X86_64_SIZE32, _ZSt9terminatev; .int 0
	.int 0x9844246
	.quad .Lname583 /* index: 583 */
	.weak validate_executable; .quad validate_executable
	.reloc ., R_X86_64_SIZE32, validate_executable; .int 0
	.int 0xcfd4d65
	.quad .Lname584 /* index: 584 */
	.weak ringbuffer_setwritten; .quad ringbuffer_setwritten
	.reloc ., R_X86_64_SIZE32, ringbuffer_setwritten; .int 0
	.int 0x64fe3ce
	.quad .Lname585 /* index: 585 */
	.weak pidns_destroy; .quad pidns_destroy
	.reloc ., R_X86_64_SIZE32, pidns_destroy; .int 0
	.int 0xc31e249
	.quad 0 /* index: 586 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname587 /* index: 587 */
	.weak unwind_setreg_kcpustate; .quad unwind_setreg_kcpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_kcpustate; .int 0
	.int 0xb8d0bb5
	.quad .Lname588 /* index: 588 */
	.weak vm_tasklock_end; .quad vm_tasklock_end
	.reloc ., R_X86_64_SIZE32, vm_tasklock_end; .int 0
	.int 0x349a764
	.quad .Lname589 /* index: 589 */
	.weak x86_memcpy_nopf; .quad x86_memcpy_nopf
	.reloc ., R_X86_64_SIZE32, x86_memcpy_nopf; .int 0
	.int 0xb97ae76
	.quad 0 /* index: 590 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 591 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 592 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname593 /* index: 593 */
	.weak fpustate_alloc_nx; .quad fpustate_alloc_nx
	.reloc ., R_X86_64_SIZE32, fpustate_alloc_nx; .int 0
	.int 0x9d27db8
	.quad 0 /* index: 594 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname595 /* index: 595 */
	.weak inode_write_phys; .quad inode_write_phys
	.reloc ., R_X86_64_SIZE32, inode_write_phys; .int 0
	.int 0x278253
	.quad .Lname596 /* index: 596 */
	.weak pidns_endread; .quad pidns_endread
	.reloc ., R_X86_64_SIZE32, pidns_endread; .int 0
	.int 0xeb0d254
	.quad .Lname597 /* index: 597 */
	.weak fpustate_free; .quad fpustate_free
	.reloc ., R_X86_64_SIZE32, fpustate_free; .int 0
	.int 0x7e97255
	.quad .Lname598 /* index: 598 */
	.weak sys_select; .quad sys_select
	.reloc ., R_X86_64_SIZE32, sys_select; .int 0
	.int 0x69d9b34
	.quad .Lname599 /* index: 599 */
	.weak taskpid_destroy; .quad taskpid_destroy
	.reloc ., R_X86_64_SIZE32, taskpid_destroy; .int 0
	.int 0xec3db9
	.quad .Lname600 /* index: 600 */
	.weak syscall_emulate64; .quad syscall_emulate64
	.reloc ., R_X86_64_SIZE32, syscall_emulate64; .int 0
	.int 0x443fb44
	.quad .Lname601 /* index: 601 */
	.weak keyboard_device_init; .quad keyboard_device_init
	.reloc ., R_X86_64_SIZE32, keyboard_device_init; .int 0
	.int 0xf167864
	.quad 0 /* index: 602 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 603 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 604 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname605 /* index: 605 */
	.weak vm_node_update_write_access_locked_vm; .quad vm_node_update_write_access_locked_vm
	.reloc ., R_X86_64_SIZE32, vm_node_update_write_access_locked_vm; .int 0
	.int 0xd08a25d
	.quad .Lname606 /* index: 606 */
	.weak sys32_mincore; .quad sys32_mincore
	.reloc ., R_X86_64_SIZE32, sys32_mincore; .int 0
	.int 0x9030eb5
	.quad .Lname607 /* index: 607 */
	.weak lookup_filesystem_type; .quad lookup_filesystem_type
	.reloc ., R_X86_64_SIZE32, lookup_filesystem_type; .int 0
	.int 0xc3ce065
	.quad 0 /* index: 608 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname609 /* index: 609 */
	.weak sys_munmap; .quad sys_munmap
	.reloc ., R_X86_64_SIZE32, sys_munmap; .int 0
	.int 0x64e0310
	.quad .Lname610 /* index: 610 */
	.weak cpu_schedule_idle_job; .quad cpu_schedule_idle_job
	.reloc ., R_X86_64_SIZE32, cpu_schedule_idle_job; .int 0
	.int 0xbc24262
	.quad .Lname611 /* index: 611 */
	.weak sys_clock_getres; .quad sys_clock_getres
	.reloc ., R_X86_64_SIZE32, sys_clock_getres; .int 0
	.int 0x7a5263
	.quad .Lname612 /* index: 612 */
	.weak pidns_tryread; .quad pidns_tryread
	.reloc ., R_X86_64_SIZE32, pidns_tryread; .int 0
	.int 0xd7bd264
	.quad .Lname613 /* index: 613 */
	.weak dbg_vmenuf; .quad dbg_vmenuf
	.reloc ., R_X86_64_SIZE32, dbg_vmenuf; .int 0
	.int 0x6d52d66
	.quad .Lname614 /* index: 614 */
	.weak block_device_writev; .quad block_device_writev
	.reloc ., R_X86_64_SIZE32, block_device_writev; .int 0
	.int 0x5125266
	.quad .Lname615 /* index: 615 */
	.weak sys_utime; .quad sys_utime
	.reloc ., R_X86_64_SIZE32, sys_utime; .int 0
	.int 0x96cd535
	.quad 0 /* index: 616 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 617 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 618 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname619 /* index: 619 */
	.weak dbg_getreg; .quad dbg_getreg
	.reloc ., R_X86_64_SIZE32, dbg_getreg; .int 0
	.int 0x5da1067
	.quad .Lname620 /* index: 620 */
	.weak sys32_sched_rr_get_interval; .quad sys32_sched_rr_get_interval
	.reloc ., R_X86_64_SIZE32, sys32_sched_rr_get_interval; .int 0
	.int 0x8a2626c
	.quad .Lname621 /* index: 621 */
	.weak sys32_fchmodat; .quad sys32_fchmodat
	.reloc ., R_X86_64_SIZE32, sys32_fchmodat; .int 0
	.int 0x996d8f4
	.quad 0 /* index: 622 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname623 /* index: 623 */
	.weak validate_readable_opt; .quad validate_readable_opt
	.reloc ., R_X86_64_SIZE32, validate_readable_opt; .int 0
	.int 0xd5cea34
	.quad .Lname624 /* index: 624 */
	.weak vm_kernel_syncone; .quad vm_kernel_syncone
	.reloc ., R_X86_64_SIZE32, vm_kernel_syncone; .int 0
	.int 0x80d1e35
	.quad .Lname625 /* index: 625 */
	.weak sys32_clock_gettime; .quad sys32_clock_gettime
	.reloc ., R_X86_64_SIZE32, sys32_clock_gettime; .int 0
	.int 0xeffa745
	.quad 0 /* index: 626 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname627 /* index: 627 */
	.weak cpu_enable_preemptive_interrupts; .quad cpu_enable_preemptive_interrupts
	.reloc ., R_X86_64_SIZE32, cpu_enable_preemptive_interrupts; .int 0
	.int 0xb08e273
	.quad .Lname628 /* index: 628 */
	.weak cpu_run_current; .quad cpu_run_current
	.reloc ., R_X86_64_SIZE32, cpu_run_current; .int 0
	.int 0x1a06274
	.quad .Lname629 /* index: 629 */
	.weak vm_datablock_anonymous_zero_type; .quad vm_datablock_anonymous_zero_type
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous_zero_type; .int 0
	.int 0x362a275
	.quad .Lname630 /* index: 630 */
	.weak sys32_idle; .quad sys32_idle
	.reloc ., R_X86_64_SIZE32, sys32_idle; .int 0
	.int 0x6824b45
	.quad 0 /* index: 631 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname632 /* index: 632 */
	.weak sys32_waitpid; .quad sys32_waitpid
	.reloc ., R_X86_64_SIZE32, sys32_waitpid; .int 0
	.int 0x686dee4
	.quad .Lname633 /* index: 633 */
	.weak mouse_device_read; .quad mouse_device_read
	.reloc ., R_X86_64_SIZE32, mouse_device_read; .int 0
	.int 0x2982b14
	.quad .Lname634 /* index: 634 */
	.weak oneshot_directory_file_destroy; .quad oneshot_directory_file_destroy
	.reloc ., R_X86_64_SIZE32, oneshot_directory_file_destroy; .int 0
	.int 0x6ae8499
	.quad 0 /* index: 635 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 636 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname637 /* index: 637 */
	.weak unwind_getreg_icpustate; .quad unwind_getreg_icpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_icpustate; .int 0
	.int 0xb8c75b5
	.quad 0 /* index: 638 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname639 /* index: 639 */
	.weak fs_filesystems_lock_trywrite; .quad fs_filesystems_lock_trywrite
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_trywrite; .int 0
	.int 0xe4fb15
	.quad .Lname640 /* index: 640 */
	.weak sys_kstat; .quad sys_kstat
	.reloc ., R_X86_64_SIZE32, sys_kstat; .int 0
	.int 0x962d184
	.quad .Lname641 /* index: 641 */
	.weak sys_io_setup; .quad sys_io_setup
	.reloc ., R_X86_64_SIZE32, sys_io_setup; .int 0
	.int 0x4d95dc0
	.quad .Lname642 /* index: 642 */
	.weak vpage_ffree_untraced; .quad vpage_ffree_untraced
	.reloc ., R_X86_64_SIZE32, vpage_ffree_untraced; .int 0
	.int 0xe4e5d04
	.quad .Lname643 /* index: 643 */
	.weak block_device_awrite_phys; .quad block_device_awrite_phys
	.reloc ., R_X86_64_SIZE32, block_device_awrite_phys; .int 0
	.int 0xd11283
	.quad .Lname644 /* index: 644 */
	.weak format_repeat; .quad format_repeat
	.reloc ., R_X86_64_SIZE32, format_repeat; .int 0
	.int 0xbe55284
	.quad .Lname645 /* index: 645 */
	.weak sys32_memfd_create; .quad sys32_memfd_create
	.reloc ., R_X86_64_SIZE32, sys32_memfd_create; .int 0
	.int 0x624e285
	.quad 0 /* index: 646 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname647 /* index: 647 */
	.weak sys32_kfstatat; .quad sys32_kfstatat
	.reloc ., R_X86_64_SIZE32, sys32_kfstatat; .int 0
	.int 0xdcc0924
	.quad .Lname648 /* index: 648 */
	.weak __predict_update_rax; .quad __predict_update_rax
	.reloc ., R_X86_64_SIZE32, __predict_update_rax; .int 0
	.int 0x4551288
	.quad 0 /* index: 649 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname650 /* index: 650 */
	.weak vm_pagetophys; .quad vm_pagetophys
	.reloc ., R_X86_64_SIZE32, vm_pagetophys; .int 0
	.int 0x1a009a3
	.quad .Lname651 /* index: 651 */
	.weak sys32_brk; .quad sys32_brk
	.reloc ., R_X86_64_SIZE32, sys32_brk; .int 0
	.int 0x668228b
	.quad 0 /* index: 652 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname653 /* index: 653 */
	.weak sys32_getsockname; .quad sys32_getsockname
	.reloc ., R_X86_64_SIZE32, sys32_getsockname; .int 0
	.int 0xdc88a35
	.quad 0 /* index: 654 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 655 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname656 /* index: 656 */
	.weak sys_frealpath4; .quad sys_frealpath4
	.reloc ., R_X86_64_SIZE32, sys_frealpath4; .int 0
	.int 0x8a355b4
	.quad .Lname657 /* index: 657 */
	.weak slab_kmalloc8; .quad slab_kmalloc8
	.reloc ., R_X86_64_SIZE32, slab_kmalloc8; .int 0
	.int 0x966b318
	.quad .Lname658 /* index: 658 */
	.weak vio_readl; .quad vio_readl
	.reloc ., R_X86_64_SIZE32, vio_readl; .int 0
	.int 0x568caac
	.quad 0 /* index: 659 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 660 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname661 /* index: 661 */
	.weak slab_free; .quad slab_free
	.reloc ., R_X86_64_SIZE32, slab_free; .int 0
	.int 0x785a295
	.quad 0 /* index: 662 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname663 /* index: 663 */
	.weak dbg_asmview; .quad dbg_asmview
	.reloc ., R_X86_64_SIZE32, dbg_asmview; .int 0
	.int 0x90e4297
	.quad .Lname664 /* index: 664 */
	.weak task_push_asynchronous_rpc_v; .quad task_push_asynchronous_rpc_v
	.reloc ., R_X86_64_SIZE32, task_push_asynchronous_rpc_v; .int 0
	.int 0x4e99cb6
	.quad .Lname665 /* index: 665 */
	.weak isr_vector_state_destroy; .quad isr_vector_state_destroy
	.reloc ., R_X86_64_SIZE32, isr_vector_state_destroy; .int 0
	.int 0xcc3f299
	.quad .Lname666 /* index: 666 */
	.weak sys_pause; .quad sys_pause
	.reloc ., R_X86_64_SIZE32, sys_pause; .int 0
	.int 0x966f795
	.quad .Lname667 /* index: 667 */
	.weak sys32_init_module; .quad sys32_init_module
	.reloc ., R_X86_64_SIZE32, sys32_init_module; .int 0
	.int 0xe20ed25
	.quad 0 /* index: 668 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 669 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname670 /* index: 670 */
	.weak memmovedown; .quad memmovedown
	.reloc ., R_X86_64_SIZE32, memmovedown; .int 0
	.int 0x6b8729e
	.quad .Lname671 /* index: 671 */
	.weak getreg_sfpustate; .quad getreg_sfpustate
	.reloc ., R_X86_64_SIZE32, getreg_sfpustate; .int 0
	.int 0xf711dc5
	.quad .Lname672 /* index: 672 */
	.weak sys32_vmsplice; .quad sys32_vmsplice
	.reloc ., R_X86_64_SIZE32, sys32_vmsplice; .int 0
	.int 0x4c1ae15
	.quad 0 /* index: 673 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 674 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname675 /* index: 675 */
	.weak inode_awrite_phys; .quad inode_awrite_phys
	.reloc ., R_X86_64_SIZE32, inode_awrite_phys; .int 0
	.int 0x19ed2a3
	.quad .Lname676 /* index: 676 */
	.weak sig_broadcast; .quad sig_broadcast
	.reloc ., R_X86_64_SIZE32, sig_broadcast; .int 0
	.int 0xc87c2a4
	.quad .Lname677 /* index: 677 */
	.weak directory_getcasenode; .quad directory_getcasenode
	.reloc ., R_X86_64_SIZE32, directory_getcasenode; .int 0
	.int 0xf7d62a5
	.quad .Lname678 /* index: 678 */
	.weak sys_preadvf; .quad sys_preadvf
	.reloc ., R_X86_64_SIZE32, sys_preadvf; .int 0
	.int 0x7f072a6
	.quad .Lname679 /* index: 679 */
	.weak sys_prctl; .quad sys_prctl
	.reloc ., R_X86_64_SIZE32, sys_prctl; .int 0
	.int 0x967f1ac
	.quad .Lname680 /* index: 680 */
	.weak __predict_update_rcx; .quad __predict_update_rcx
	.reloc ., R_X86_64_SIZE32, __predict_update_rcx; .int 0
	.int 0x45512a8
	.quad .Lname681 /* index: 681 */
	.weak ttybase_device_ioctl; .quad ttybase_device_ioctl
	.reloc ., R_X86_64_SIZE32, ttybase_device_ioctl; .int 0
	.int 0x50c1b1c
	.quad 0 /* index: 682 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname683 /* index: 683 */
	.weak handle_get_datablock; .quad handle_get_datablock
	.reloc ., R_X86_64_SIZE32, handle_get_datablock; .int 0
	.int 0xffc62ab
	.quad 0 /* index: 684 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 685 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 686 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname687 /* index: 687 */
	.weak vm_mapres; .quad vm_mapres
	.reloc ., R_X86_64_SIZE32, vm_mapres; .int 0
	.int 0x63805f3
	.quad .Lname688 /* index: 688 */
	.weak pagedir_unprepare_mapone_p; .quad pagedir_unprepare_mapone_p
	.reloc ., R_X86_64_SIZE32, pagedir_unprepare_mapone_p; .int 0
	.int 0xfa432b0
	.quad .Lname689 /* index: 689 */
	.weak vm_tasklock_read_nx; .quad vm_tasklock_read_nx
	.reloc ., R_X86_64_SIZE32, vm_tasklock_read_nx; .int 0
	.int 0x594edc8
	.quad .Lname690 /* index: 690 */
	.weak debuginfo_cu_parser_skipattr; .quad debuginfo_cu_parser_skipattr
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_skipattr; .int 0
	.int 0x7e882b2
	.quad .Lname691 /* index: 691 */
	.weak disasm_default_maxbytes; .quad disasm_default_maxbytes
	.reloc ., R_X86_64_SIZE32, disasm_default_maxbytes; .int 0
	.int 0xa1542b3
	.quad .Lname692 /* index: 692 */
	.weak cred_require_mount; .quad cred_require_mount
	.reloc ., R_X86_64_SIZE32, cred_require_mount; .int 0
	.int 0x54472b4
	.quad .Lname693 /* index: 693 */
	.weak cpu_wake; .quad cpu_wake
	.reloc ., R_X86_64_SIZE32, cpu_wake; .int 0
	.int 0x7b6d2b5
	.quad .Lname694 /* index: 694 */
	.weak sys32_linkat; .quad sys32_linkat
	.reloc ., R_X86_64_SIZE32, sys32_linkat; .int 0
	.int 0x3a03704
	.quad 0 /* index: 695 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname696 /* index: 696 */
	.weak __predict_update_rdx; .quad __predict_update_rdx
	.reloc ., R_X86_64_SIZE32, __predict_update_rdx; .int 0
	.int 0x45512b8
	.quad .Lname697 /* index: 697 */
	.weak driver_insmod; .quad driver_insmod
	.reloc ., R_X86_64_SIZE32, driver_insmod; .int 0
	.int 0xe757074
	.quad 0 /* index: 698 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 699 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname700 /* index: 700 */
	.weak debuginfo_cu_parser_loadattr_type; .quad debuginfo_cu_parser_loadattr_type
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_type; .int 0
	.int 0xe700815
	.quad 0 /* index: 701 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname702 /* index: 702 */
	.weak handle_existsin; .quad handle_existsin
	.reloc ., R_X86_64_SIZE32, handle_existsin; .int 0
	.int 0xbb862be
	.quad .Lname703 /* index: 703 */
	.weak sys32_timer_gettime; .quad sys32_timer_gettime
	.reloc ., R_X86_64_SIZE32, sys32_timer_gettime; .int 0
	.int 0xfce2075
	.quad .Lname704 /* index: 704 */
	.weak __gxx_personality_v0; .quad __gxx_personality_v0
	.reloc ., R_X86_64_SIZE32, __gxx_personality_v0; .int 0
	.int 0xc7c32c0
	.quad 0 /* index: 705 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 706 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname707 /* index: 707 */
	.weak task_deliver_rpc; .quad task_deliver_rpc
	.reloc ., R_X86_64_SIZE32, task_deliver_rpc; .int 0
	.int 0xd9b42c3
	.quad .Lname708 /* index: 708 */
	.weak sys32_setrlimit; .quad sys32_setrlimit
	.reloc ., R_X86_64_SIZE32, sys32_setrlimit; .int 0
	.int 0xdfaf2c4
	.quad .Lname709 /* index: 709 */
	.weak sys_sendfile; .quad sys_sendfile
	.reloc ., R_X86_64_SIZE32, sys_sendfile; .int 0
	.int 0xdfa5ab5
	.quad .Lname710 /* index: 710 */
	.weak x86_iopl_keep_after_clone; .quad x86_iopl_keep_after_clone
	.reloc ., R_X86_64_SIZE32, x86_iopl_keep_after_clone; .int 0
	.int 0xcb59555
	.quad .Lname711 /* index: 711 */
	.weak debuginfo_cu_parser_getflag; .quad debuginfo_cu_parser_getflag
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getflag; .int 0
	.int 0xbb432c7
	.quad .Lname712 /* index: 712 */
	.weak sys32_frealpathat; .quad sys32_frealpathat
	.reloc ., R_X86_64_SIZE32, sys32_frealpathat; .int 0
	.int 0xb4e23a4
	.quad 0 /* index: 713 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 714 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname715 /* index: 715 */
	.weak vm_datablock_getfutex_existing; .quad vm_datablock_getfutex_existing
	.reloc ., R_X86_64_SIZE32, vm_datablock_getfutex_existing; .int 0
	.int 0xd571077
	.quad 0 /* index: 716 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname717 /* index: 717 */
	.weak sys32_lsetxattr; .quad sys32_lsetxattr
	.reloc ., R_X86_64_SIZE32, sys32_lsetxattr; .int 0
	.int 0xad6b322
	.quad .Lname718 /* index: 718 */
	.weak memrlen; .quad memrlen
	.reloc ., R_X86_64_SIZE32, memrlen; .int 0
	.int 0x3c492ce
	.quad 0 /* index: 719 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 720 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname721 /* index: 721 */
	.weak sys32_set_thread_area; .quad sys32_set_thread_area
	.reloc ., R_X86_64_SIZE32, sys32_set_thread_area; .int 0
	.int 0x7a762d1
	.quad .Lname722 /* index: 722 */
	.weak sys32_lfutexexpr; .quad sys32_lfutexexpr
	.reloc ., R_X86_64_SIZE32, sys32_lfutexexpr; .int 0
	.int 0xc4d52d2
	.quad .Lname723 /* index: 723 */
	.weak inode_areadv_phys; .quad inode_areadv_phys
	.reloc ., R_X86_64_SIZE32, inode_areadv_phys; .int 0
	.int 0xaeb2d3
	.quad .Lname724 /* index: 724 */
	.weak sys_linux_lstat64; .quad sys_linux_lstat64
	.reloc ., R_X86_64_SIZE32, sys_linux_lstat64; .int 0
	.int 0x13442d4
	.quad 0 /* index: 725 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname726 /* index: 726 */
	.weak sys32_pwritev; .quad sys32_pwritev
	.reloc ., R_X86_64_SIZE32, sys32_pwritev; .int 0
	.int 0xcef62d6
	.quad 0 /* index: 727 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 728 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname729 /* index: 729 */
	.weak sys32_fsymlinkat; .quad sys32_fsymlinkat
	.reloc ., R_X86_64_SIZE32, sys32_fsymlinkat; .int 0
	.int 0x6ae3b24
	.quad 0 /* index: 730 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 731 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname732 /* index: 732 */
	.weak __predict_update_al; .quad __predict_update_al
	.reloc ., R_X86_64_SIZE32, __predict_update_al; .int 0
	.int 0x4552dc
	.quad 0 /* index: 733 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname734 /* index: 734 */
	.weak vm_syncone; .quad vm_syncone
	.reloc ., R_X86_64_SIZE32, vm_syncone; .int 0
	.int 0xb035725
	.quad .Lname735 /* index: 735 */
	.weak getreg_sgbase; .quad getreg_sgbase
	.reloc ., R_X86_64_SIZE32, getreg_sgbase; .int 0
	.int 0xb560325
	.quad .Lname736 /* index: 736 */
	.weak unwind_setreg_icpustate_exclusive; .quad unwind_setreg_icpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_icpustate_exclusive; .int 0
	.int 0xd8e5115
	.quad 0 /* index: 737 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname738 /* index: 738 */
	.weak format_snprintf_printer; .quad format_snprintf_printer
	.reloc ., R_X86_64_SIZE32, format_snprintf_printer; .int 0
	.int 0x587f2e2
	.quad .Lname739 /* index: 739 */
	.weak sys_rt_sigprocmask; .quad sys_rt_sigprocmask
	.reloc ., R_X86_64_SIZE32, sys_rt_sigprocmask; .int 0
	.int 0x881507b
	.quad .Lname740 /* index: 740 */
	.weak cpu_add_quantum_offset; .quad cpu_add_quantum_offset
	.reloc ., R_X86_64_SIZE32, cpu_add_quantum_offset; .int 0
	.int 0xc4522e4
	.quad .Lname741 /* index: 741 */
	.weak sys32_chroot; .quad sys32_chroot
	.reloc ., R_X86_64_SIZE32, sys32_chroot; .int 0
	.int 0x22ff4e4
	.quad .Lname742 /* index: 742 */
	.weak keymap_translate_buf; .quad keymap_translate_buf
	.reloc ., R_X86_64_SIZE32, keymap_translate_buf; .int 0
	.int 0xe3082e6
	.quad .Lname743 /* index: 743 */
	.weak inode_read_blocking; .quad inode_read_blocking
	.reloc ., R_X86_64_SIZE32, inode_read_blocking; .int 0
	.int 0xbbc52e7
	.quad .Lname744 /* index: 744 */
	.weak vm_kernel_treelock_writef; .quad vm_kernel_treelock_writef
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_writef; .int 0
	.int 0x4d43a26
	.quad .Lname745 /* index: 745 */
	.weak driver_state_destroy; .quad driver_state_destroy
	.reloc ., R_X86_64_SIZE32, driver_state_destroy; .int 0
	.int 0x96ed2e9
	.quad 0 /* index: 746 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname747 /* index: 747 */
	.weak sys32_pause; .quad sys32_pause
	.reloc ., R_X86_64_SIZE32, sys32_pause; .int 0
	.int 0x81d8af5
	.quad .Lname748 /* index: 748 */
	.weak sys32__sysctl; .quad sys32__sysctl
	.reloc ., R_X86_64_SIZE32, sys32__sysctl; .int 0
	.int 0xdb6f2ec
	.quad 0 /* index: 749 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname750 /* index: 750 */
	.weak sys_hopf; .quad sys_hopf
	.reloc ., R_X86_64_SIZE32, sys_hopf; .int 0
	.int 0x95f1d6
	.quad .Lname751 /* index: 751 */
	.weak sys32_listxattr; .quad sys32_listxattr
	.reloc ., R_X86_64_SIZE32, sys32_listxattr; .int 0
	.int 0xcd6b1b2
	.quad .Lname752 /* index: 752 */
	.weak pagedir_unsetchanged_p; .quad pagedir_unsetchanged_p
	.reloc ., R_X86_64_SIZE32, pagedir_unsetchanged_p; .int 0
	.int 0xa6632f0
	.quad 0 /* index: 753 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname754 /* index: 754 */
	.weak sys32_lchown32; .quad sys32_lchown32
	.reloc ., R_X86_64_SIZE32, sys32_lchown32; .int 0
	.int 0x99062f2
	.quad .Lname755 /* index: 755 */
	.weak block_device_areadv_phys; .quad block_device_areadv_phys
	.reloc ., R_X86_64_SIZE32, block_device_areadv_phys; .int 0
	.int 0x1e172f3
	.quad .Lname756 /* index: 756 */
	.weak sys32_clock_nanosleep64; .quad sys32_clock_nanosleep64
	.reloc ., R_X86_64_SIZE32, sys32_clock_nanosleep64; .int 0
	.int 0x1ac92f4
	.quad .Lname757 /* index: 757 */
	.weak rwlock_downgrade; .quad rwlock_downgrade
	.reloc ., R_X86_64_SIZE32, rwlock_downgrade; .int 0
	.int 0x9e642f5
	.quad .Lname758 /* index: 758 */
	.weak json_parser_next; .quad json_parser_next
	.reloc ., R_X86_64_SIZE32, json_parser_next; .int 0
	.int 0x825df04
	.quad .Lname759 /* index: 759 */
	.weak keyboard_buffer_putkey; .quad keyboard_buffer_putkey
	.reloc ., R_X86_64_SIZE32, keyboard_buffer_putkey; .int 0
	.int 0x6a00b29
	.quad 0 /* index: 760 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname761 /* index: 761 */
	.weak sys32_getpgid; .quad sys32_getpgid
	.reloc ., R_X86_64_SIZE32, sys32_getpgid; .int 0
	.int 0x6cd05d4
	.quad 0 /* index: 762 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 763 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname764 /* index: 764 */
	.weak sys32_geteuid; .quad sys32_geteuid
	.reloc ., R_X86_64_SIZE32, sys32_geteuid; .int 0
	.int 0x6cca3d4
	.quad .Lname765 /* index: 765 */
	.weak sys_move_pages; .quad sys_move_pages
	.reloc ., R_X86_64_SIZE32, sys_move_pages; .int 0
	.int 0xbf03cb3
	.quad .Lname766 /* index: 766 */
	.weak superblock_mountlock_trywrite; .quad superblock_mountlock_trywrite
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_trywrite; .int 0
	.int 0xa19c385
	.quad .Lname767 /* index: 767 */
	.weak vm_datablock_anonymize; .quad vm_datablock_anonymize
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymize; .int 0
	.int 0xb72ddd5
	.quad 0 /* index: 768 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 769 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 770 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname771 /* index: 771 */
	.weak sys_fanotify_mark; .quad sys_fanotify_mark
	.reloc ., R_X86_64_SIZE32, sys_fanotify_mark; .int 0
	.int 0x1d65b2b
	.quad .Lname772 /* index: 772 */
	.weak addr2line_end; .quad addr2line_end
	.reloc ., R_X86_64_SIZE32, addr2line_end; .int 0
	.int 0x9e20304
	.quad .Lname773 /* index: 773 */
	.weak pagedir_unmap_userspace; .quad pagedir_unmap_userspace
	.reloc ., R_X86_64_SIZE32, pagedir_unmap_userspace; .int 0
	.int 0x4621305
	.quad 0 /* index: 774 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 775 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 776 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname777 /* index: 777 */
	.weak block_device_destroy; .quad block_device_destroy
	.reloc ., R_X86_64_SIZE32, block_device_destroy; .int 0
	.int 0x55f3309
	.quad 0 /* index: 778 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 779 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname780 /* index: 780 */
	.weak task_disconnectall; .quad task_disconnectall
	.reloc ., R_X86_64_SIZE32, task_disconnectall; .int 0
	.int 0xa1be30c
	.quad .Lname781 /* index: 781 */
	.weak sys32_fanotify_mark; .quad sys32_fanotify_mark
	.reloc ., R_X86_64_SIZE32, sys32_fanotify_mark; .int 0
	.int 0xa773a5b
	.quad 0 /* index: 782 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 783 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname784 /* index: 784 */
	.weak sys_mremap; .quad sys_mremap
	.reloc ., R_X86_64_SIZE32, sys_mremap; .int 0
	.int 0x64f1310
	.quad .Lname785 /* index: 785 */
	.weak vm_datablock_getfutex; .quad vm_datablock_getfutex
	.reloc ., R_X86_64_SIZE32, vm_datablock_getfutex; .int 0
	.int 0x45f25d8
	.quad .Lname786 /* index: 786 */
	.weak sigmask_getwr; .quad sigmask_getwr
	.reloc ., R_X86_64_SIZE32, sigmask_getwr; .int 0
	.int 0xaa3f312
	.quad .Lname787 /* index: 787 */
	.weak sys_finit_module; .quad sys_finit_module
	.reloc ., R_X86_64_SIZE32, sys_finit_module; .int 0
	.int 0x20fbc35
	.quad .Lname788 /* index: 788 */
	.weak instruction_trypred; .quad instruction_trypred
	.reloc ., R_X86_64_SIZE32, instruction_trypred; .int 0
	.int 0x1768314
	.quad .Lname789 /* index: 789 */
	.weak fs_filesystems_remove; .quad fs_filesystems_remove
	.reloc ., R_X86_64_SIZE32, fs_filesystems_remove; .int 0
	.int 0x3f14315
	.quad 0 /* index: 790 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname791 /* index: 791 */
	.weak rwlock_downgrade_readonly; .quad rwlock_downgrade_readonly
	.reloc ., R_X86_64_SIZE32, rwlock_downgrade_readonly; .int 0
	.int 0xf562dd9
	.quad .Lname792 /* index: 792 */
	.weak dbg_menuex; .quad dbg_menuex
	.reloc ., R_X86_64_SIZE32, dbg_menuex; .int 0
	.int 0x63ef318
	.quad .Lname793 /* index: 793 */
	.weak sys32_stime64; .quad sys32_stime64
	.reloc ., R_X86_64_SIZE32, sys32_stime64; .int 0
	.int 0x1aa5084
	.quad .Lname794 /* index: 794 */
	.weak sys_unlinkat; .quad sys_unlinkat
	.reloc ., R_X86_64_SIZE32, sys_unlinkat; .int 0
	.int 0x4a0e744
	.quad .Lname795 /* index: 795 */
	.weak path_lock; .quad path_lock
	.reloc ., R_X86_64_SIZE32, path_lock; .int 0
	.int 0xae6631b
	.quad 0 /* index: 796 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 797 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname798 /* index: 798 */
	.weak page_malloc_part_between; .quad page_malloc_part_between
	.reloc ., R_X86_64_SIZE32, page_malloc_part_between; .int 0
	.int 0xa84431e
	.quad .Lname799 /* index: 799 */
	.weak ttybase_device_poll; .quad ttybase_device_poll
	.reloc ., R_X86_64_SIZE32, ttybase_device_poll; .int 0
	.int 0xb53323c
	.quad .Lname800 /* index: 800 */
	.weak sys32_utimensat64; .quad sys32_utimensat64
	.reloc ., R_X86_64_SIZE32, sys32_utimensat64; .int 0
	.int 0x44e2dc4
	.quad 0 /* index: 801 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname802 /* index: 802 */
	.weak path_clear; .quad path_clear
	.reloc ., R_X86_64_SIZE32, path_clear; .int 0
	.int 0xe5f4322
	.quad .Lname803 /* index: 803 */
	.weak kmalloc; .quad kmalloc
	.reloc ., R_X86_64_SIZE32, kmalloc; .int 0
	.int 0x2383323
	.quad .Lname804 /* index: 804 */
	.weak cmdline_split; .quad cmdline_split
	.reloc ., R_X86_64_SIZE32, cmdline_split; .int 0
	.int 0x1516324
	.quad .Lname805 /* index: 805 */
	.weak debug_print_filename; .quad debug_print_filename
	.reloc ., R_X86_64_SIZE32, debug_print_filename; .int 0
	.int 0xd561325
	.quad .Lname806 /* index: 806 */
	.weak error_printf; .quad error_printf
	.reloc ., R_X86_64_SIZE32, error_printf; .int 0
	.int 0xb17326
	.quad .Lname807 /* index: 807 */
	.weak json_writer_putstring; .quad json_writer_putstring
	.reloc ., R_X86_64_SIZE32, json_writer_putstring; .int 0
	.int 0x7297327
	.quad 0 /* index: 808 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname809 /* index: 809 */
	.weak sys32_epoll_ctl; .quad sys32_epoll_ctl
	.reloc ., R_X86_64_SIZE32, sys32_epoll_ctl; .int 0
	.int 0x45a7ddc
	.quad 0 /* index: 810 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname811 /* index: 811 */
	.weak vm_datapart_lockwrite_setcore_unsharecow; .quad vm_datapart_lockwrite_setcore_unsharecow
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockwrite_setcore_unsharecow; .int 0
	.int 0xe802087
	.quad 0 /* index: 812 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 813 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 814 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 815 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname816 /* index: 816 */
	.weak unicode_8to16; .quad unicode_8to16
	.reloc ., R_X86_64_SIZE32, unicode_8to16; .int 0
	.int 0x7601796
	.quad 0 /* index: 817 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname818 /* index: 818 */
	.weak validate_user; .quad validate_user
	.reloc ., R_X86_64_SIZE32, validate_user; .int 0
	.int 0x6343332
	.quad .Lname819 /* index: 819 */
	.weak swap_malloc; .quad swap_malloc
	.reloc ., R_X86_64_SIZE32, swap_malloc; .int 0
	.int 0x64f0b33
	.quad .Lname820 /* index: 820 */
	.weak driver_local_symbol_at; .quad driver_local_symbol_at
	.reloc ., R_X86_64_SIZE32, driver_local_symbol_at; .int 0
	.int 0x6529334
	.quad .Lname821 /* index: 821 */
	.weak driver_with_name; .quad driver_with_name
	.reloc ., R_X86_64_SIZE32, driver_with_name; .int 0
	.int 0x6289335
	.quad .Lname822 /* index: 822 */
	.weak unwind_getreg_xfpustate_exclusive; .quad unwind_getreg_xfpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_xfpustate_exclusive; .int 0
	.int 0xefe5065
	.quad 0 /* index: 823 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 824 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname825 /* index: 825 */
	.weak krand_seed; .quad krand_seed
	.reloc ., R_X86_64_SIZE32, krand_seed; .int 0
	.int 0x4a1b334
	.quad .Lname826 /* index: 826 */
	.weak vm_set_aslr_disabled; .quad vm_set_aslr_disabled
	.reloc ., R_X86_64_SIZE32, vm_set_aslr_disabled; .int 0
	.int 0xc9d5884
	.quad .Lname827 /* index: 827 */
	.weak cpu_addsleepingtask; .quad cpu_addsleepingtask
	.reloc ., R_X86_64_SIZE32, cpu_addsleepingtask; .int 0
	.int 0xfb7433b
	.quad .Lname828 /* index: 828 */
	.weak sys32_ioprio_get; .quad sys32_ioprio_get
	.reloc ., R_X86_64_SIZE32, sys32_ioprio_get; .int 0
	.int 0xe870bd4
	.quad 0 /* index: 829 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname830 /* index: 830 */
	.weak getreg_irregs; .quad getreg_irregs
	.reloc ., R_X86_64_SIZE32, getreg_irregs; .int 0
	.int 0x9c20053
	.quad .Lname831 /* index: 831 */
	.weak handle_get_pipe; .quad handle_get_pipe
	.reloc ., R_X86_64_SIZE32, handle_get_pipe; .int 0
	.int 0x834cb35
	.quad 0 /* index: 832 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname833 /* index: 833 */
	.weak thiscpu_x86_dfstackpart; .quad thiscpu_x86_dfstackpart
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_dfstackpart; .int 0
	.int 0x5d92914
	.quad 0 /* index: 834 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname835 /* index: 835 */
	.weak inode_readallv_phys; .quad inode_readallv_phys
	.reloc ., R_X86_64_SIZE32, inode_readallv_phys; .int 0
	.int 0xb646343
	.quad .Lname836 /* index: 836 */
	.weak regdump_sgregs_with_cs_ss_tr_ldt; .quad regdump_sgregs_with_cs_ss_tr_ldt
	.reloc ., R_X86_64_SIZE32, regdump_sgregs_with_cs_ss_tr_ldt; .int 0
	.int 0x5368ac4
	.quad .Lname837 /* index: 837 */
	.weak sys_fsymlinkat; .quad sys_fsymlinkat
	.reloc ., R_X86_64_SIZE32, sys_fsymlinkat; .int 0
	.int 0x4bbacd4
	.quad .Lname838 /* index: 838 */
	.weak this_taskpid; .quad this_taskpid
	.reloc ., R_X86_64_SIZE32, this_taskpid; .int 0
	.int 0xd272f94
	.quad 0 /* index: 839 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 840 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname841 /* index: 841 */
	.weak sys32_tee; .quad sys32_tee
	.reloc ., R_X86_64_SIZE32, sys32_tee; .int 0
	.int 0x66811b5
	.quad 0 /* index: 842 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname843 /* index: 843 */
	.weak sys_sched_get_priority_max; .quad sys_sched_get_priority_max
	.reloc ., R_X86_64_SIZE32, sys_sched_get_priority_max; .int 0
	.int 0xdd6a7e8
	.quad 0 /* index: 844 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname845 /* index: 845 */
	.weak sys32_remap_file_pages; .quad sys32_remap_file_pages
	.reloc ., R_X86_64_SIZE32, sys32_remap_file_pages; .int 0
	.int 0x58289b3
	.quad .Lname846 /* index: 846 */
	.weak cred_require_sysadmin; .quad cred_require_sysadmin
	.reloc ., R_X86_64_SIZE32, cred_require_sysadmin; .int 0
	.int 0x13a034e
	.quad 0 /* index: 847 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname848 /* index: 848 */
	.weak task_raisesignalprocessgroup; .quad task_raisesignalprocessgroup
	.reloc ., R_X86_64_SIZE32, task_raisesignalprocessgroup; .int 0
	.int 0x417a350
	.quad .Lname849 /* index: 849 */
	.weak sys32_setxattr; .quad sys32_setxattr
	.reloc ., R_X86_64_SIZE32, sys32_setxattr; .int 0
	.int 0xcd80a92
	.quad 0 /* index: 850 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname851 /* index: 851 */
	.weak handle_manager_alloc; .quad handle_manager_alloc
	.reloc ., R_X86_64_SIZE32, handle_manager_alloc; .int 0
	.int 0xd198353
	.quad .Lname852 /* index: 852 */
	.weak heap_realign_untraced; .quad heap_realign_untraced
	.reloc ., R_X86_64_SIZE32, heap_realign_untraced; .int 0
	.int 0xf249ac4
	.quad .Lname853 /* index: 853 */
	.weak setreg_sgbase; .quad setreg_sgbase
	.reloc ., R_X86_64_SIZE32, setreg_sgbase; .int 0
	.int 0xf560355
	.quad 0 /* index: 854 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 855 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 856 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname857 /* index: 857 */
	.weak sys32_creat; .quad sys32_creat
	.reloc ., R_X86_64_SIZE32, sys32_creat; .int 0
	.int 0x8218de4
	.quad 0 /* index: 858 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 859 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 860 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 861 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname862 /* index: 862 */
	.weak sys_query_module; .quad sys_query_module
	.reloc ., R_X86_64_SIZE32, sys_query_module; .int 0
	.int 0x4c9c3a5
	.quad .Lname863 /* index: 863 */
	.weak sys_semctl; .quad sys_semctl
	.reloc ., R_X86_64_SIZE32, sys_semctl; .int 0
	.int 0x69d8a3c
	.quad .Lname864 /* index: 864 */
	.weak task_sleep; .quad task_sleep
	.reloc ., R_X86_64_SIZE32, task_sleep; .int 0
	.int 0x16f8360
	.quad .Lname865 /* index: 865 */
	.weak task_serve; .quad task_serve
	.reloc ., R_X86_64_SIZE32, task_serve; .int 0
	.int 0x16e6165
	.quad 0 /* index: 866 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname867 /* index: 867 */
	.weak sigqueue_fini; .quad sigqueue_fini
	.reloc ., R_X86_64_SIZE32, sigqueue_fini; .int 0
	.int 0x26b45f9
	.quad .Lname868 /* index: 868 */
	.weak json_parser_getuint64; .quad json_parser_getuint64
	.reloc ., R_X86_64_SIZE32, json_parser_getuint64; .int 0
	.int 0x43e1364
	.quad .Lname869 /* index: 869 */
	.weak pagedir_mapone; .quad pagedir_mapone
	.reloc ., R_X86_64_SIZE32, pagedir_mapone; .int 0
	.int 0x3e3e365
	.quad 0 /* index: 870 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname871 /* index: 871 */
	.weak sys_recvmsg; .quad sys_recvmsg
	.reloc ., R_X86_64_SIZE32, sys_recvmsg; .int 0
	.int 0x8c1ddf7
	.quad .Lname872 /* index: 872 */
	.weak dbg_messagebox; .quad dbg_messagebox
	.reloc ., R_X86_64_SIZE32, dbg_messagebox; .int 0
	.int 0x1ab8368
	.quad .Lname873 /* index: 873 */
	.weak keyboard_device_trygetkey; .quad keyboard_device_trygetkey
	.reloc ., R_X86_64_SIZE32, keyboard_device_trygetkey; .int 0
	.int 0x92e0369
	.quad 0 /* index: 874 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname875 /* index: 875 */
	.weak sigmask_check; .quad sigmask_check
	.reloc ., R_X86_64_SIZE32, sigmask_check; .int 0
	.int 0xaa7d36b
	.quad .Lname876 /* index: 876 */
	.weak tty_device_poll; .quad tty_device_poll
	.reloc ., R_X86_64_SIZE32, tty_device_poll; .int 0
	.int 0x70ce36c
	.quad .Lname877 /* index: 877 */
	.weak task_getvm; .quad task_getvm
	.reloc ., R_X86_64_SIZE32, task_getvm; .int 0
	.int 0x15a636d
	.quad .Lname878 /* index: 878 */
	.weak vm_datablock_destroy; .quad vm_datablock_destroy
	.reloc ., R_X86_64_SIZE32, vm_datablock_destroy; .int 0
	.int 0x6459799
	.quad .Lname879 /* index: 879 */
	.weak sys_sched_setaffinity; .quad sys_sched_setaffinity
	.reloc ., R_X86_64_SIZE32, sys_sched_setaffinity; .int 0
	.int 0xdd07f79
	.quad .Lname880 /* index: 880 */
	.weak sys_writef; .quad sys_writef
	.reloc ., R_X86_64_SIZE32, sys_writef; .int 0
	.int 0x6f0ba26
	.quad 0 /* index: 881 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname882 /* index: 882 */
	.weak setreg_xfpustate; .quad setreg_xfpustate
	.reloc ., R_X86_64_SIZE32, setreg_xfpustate; .int 0
	.int 0xf765ac5
	.quad .Lname883 /* index: 883 */
	.weak sys32_rt_sigaction; .quad sys32_rt_sigaction
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigaction; .int 0
	.int 0xc50a12e
	.quad .Lname884 /* index: 884 */
	.weak vm_datapart_lock_read; .quad vm_datapart_lock_read
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_read; .int 0
	.int 0x5441374
	.quad 0 /* index: 885 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname886 /* index: 886 */
	.weak dbg_vpprintf; .quad dbg_vpprintf
	.reloc ., R_X86_64_SIZE32, dbg_vpprintf; .int 0
	.int 0x1d03376
	.quad .Lname887 /* index: 887 */
	.weak mouse_device_hwheel; .quad mouse_device_hwheel
	.reloc ., R_X86_64_SIZE32, mouse_device_hwheel; .int 0
	.int 0xb5d892c
	.quad .Lname888 /* index: 888 */
	.weak x86_syscall_emulate_int80h; .quad x86_syscall_emulate_int80h
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate_int80h; .int 0
	.int 0x3824378
	.quad .Lname889 /* index: 889 */
	.weak sys32_sync; .quad sys32_sync
	.reloc ., R_X86_64_SIZE32, sys32_sync; .int 0
	.int 0x6812023
	.quad 0 /* index: 890 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname891 /* index: 891 */
	.weak driver_section_lock; .quad driver_section_lock
	.reloc ., R_X86_64_SIZE32, driver_section_lock; .int 0
	.int 0x94f537b
	.quad .Lname892 /* index: 892 */
	.weak vio_andl; .quad vio_andl
	.reloc ., R_X86_64_SIZE32, vio_andl; .int 0
	.int 0x55837c
	.quad .Lname893 /* index: 893 */
	.weak thiscpu_state; .quad thiscpu_state
	.reloc ., R_X86_64_SIZE32, thiscpu_state; .int 0
	.int 0x19a32a5
	.quad .Lname894 /* index: 894 */
	.weak inode_chown; .quad inode_chown
	.reloc ., R_X86_64_SIZE32, inode_chown; .int 0
	.int 0xb29c37e
	.quad .Lname895 /* index: 895 */
	.weak superblock_mountlock_endwrite; .quad superblock_mountlock_endwrite
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_endwrite; .int 0
	.int 0x4a9c095
	.quad .Lname896 /* index: 896 */
	.weak vm_map; .quad vm_map
	.reloc ., R_X86_64_SIZE32, vm_map; .int 0
	.int 0x7d36380
	.quad .Lname897 /* index: 897 */
	.weak memrendq; .quad memrendq
	.reloc ., R_X86_64_SIZE32, memrendq; .int 0
	.int 0xc48c381
	.quad 0 /* index: 898 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname899 /* index: 899 */
	.weak sys_fstatfs; .quad sys_fstatfs
	.reloc ., R_X86_64_SIZE32, sys_fstatfs; .int 0
	.int 0xdd18383
	.quad .Lname900 /* index: 900 */
	.weak rwlock_tryread; .quad rwlock_tryread
	.reloc ., R_X86_64_SIZE32, rwlock_tryread; .int 0
	.int 0x5b52384
	.quad .Lname901 /* index: 901 */
	.weak kernel_panic_here; .quad kernel_panic_here
	.reloc ., R_X86_64_SIZE32, kernel_panic_here; .int 0
	.int 0x4024385
	.quad 0 /* index: 902 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname903 /* index: 903 */
	.weak cpu_loadpending; .quad cpu_loadpending
	.reloc ., R_X86_64_SIZE32, cpu_loadpending; .int 0
	.int 0xde79387
	.quad .Lname904 /* index: 904 */
	.weak path_traversenfull_ex; .quad path_traversenfull_ex
	.reloc ., R_X86_64_SIZE32, path_traversenfull_ex; .int 0
	.int 0xbae5388
	.quad .Lname905 /* index: 905 */
	.weak json_parser_findkey; .quad json_parser_findkey
	.reloc ., R_X86_64_SIZE32, json_parser_findkey; .int 0
	.int 0x5db3389
	.quad .Lname906 /* index: 906 */
	.weak sys_rpc_service; .quad sys_rpc_service
	.reloc ., R_X86_64_SIZE32, sys_rpc_service; .int 0
	.int 0xa0dbf5
	.quad 0 /* index: 907 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname908 /* index: 908 */
	.weak kernel_debugtraps_uninstall; .quad kernel_debugtraps_uninstall
	.reloc ., R_X86_64_SIZE32, kernel_debugtraps_uninstall; .int 0
	.int 0x6ea538c
	.quad .Lname909 /* index: 909 */
	.weak sys_alarm; .quad sys_alarm
	.reloc ., R_X86_64_SIZE32, sys_alarm; .int 0
	.int 0x958538d
	.quad 0 /* index: 910 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 911 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname912 /* index: 912 */
	.weak vm_kernel_treelock_write; .quad vm_kernel_treelock_write
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_write; .int 0
	.int 0x94d43a5
	.quad .Lname913 /* index: 913 */
	.weak x86_fpustate_variant; .quad x86_fpustate_variant
	.reloc ., R_X86_64_SIZE32, x86_fpustate_variant; .int 0
	.int 0xde58d44
	.quad .Lname914 /* index: 914 */
	.weak sys32_membarrier; .quad sys32_membarrier
	.reloc ., R_X86_64_SIZE32, sys32_membarrier; .int 0
	.int 0xe0a0392
	.quad .Lname915 /* index: 915 */
	.weak vio_copyfromvio_to_phys; .quad vio_copyfromvio_to_phys
	.reloc ., R_X86_64_SIZE32, vio_copyfromvio_to_phys; .int 0
	.int 0xb207393
	.quad .Lname916 /* index: 916 */
	.weak sys32_raiseat; .quad sys32_raiseat
	.reloc ., R_X86_64_SIZE32, sys32_raiseat; .int 0
	.int 0x386f394
	.quad .Lname917 /* index: 917 */
	.weak sys_rt_sigreturn; .quad sys_rt_sigreturn
	.reloc ., R_X86_64_SIZE32, sys_rt_sigreturn; .int 0
	.int 0x81365ee
	.quad 0 /* index: 918 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname919 /* index: 919 */
	.weak sys_add_key; .quad sys_add_key
	.reloc ., R_X86_64_SIZE32, sys_add_key; .int 0
	.int 0x7d36899
	.quad 0 /* index: 920 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname921 /* index: 921 */
	.weak __predict_update_rsi; .quad __predict_update_rsi
	.reloc ., R_X86_64_SIZE32, __predict_update_rsi; .int 0
	.int 0x4551399
	.quad .Lname922 /* index: 922 */
	.weak thiscpu_x86_fputhread; .quad thiscpu_x86_fputhread
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_fputhread; .int 0
	.int 0x78dd794
	.quad .Lname923 /* index: 923 */
	.weak directory_link; .quad directory_link
	.reloc ., R_X86_64_SIZE32, directory_link; .int 0
	.int 0x97f839b
	.quad .Lname924 /* index: 924 */
	.weak memrendl; .quad memrendl
	.reloc ., R_X86_64_SIZE32, memrendl; .int 0
	.int 0xc48c39c
	.quad 0 /* index: 925 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 926 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname927 /* index: 927 */
	.weak path_lock_endwrite; .quad path_lock_endwrite
	.reloc ., R_X86_64_SIZE32, path_lock_endwrite; .int 0
	.int 0x28c4b45
	.quad .Lname928 /* index: 928 */
	.weak vm86_outl; .quad vm86_outl
	.reloc ., R_X86_64_SIZE32, vm86_outl; .int 0
	.int 0xbc611ac
	.quad .Lname929 /* index: 929 */
	.weak sys_rename; .quad sys_rename
	.reloc ., R_X86_64_SIZE32, sys_rename; .int 0
	.int 0x68df8a5
	.quad .Lname930 /* index: 930 */
	.weak cpu_disable_preemptive_interrupts_nopr; .quad cpu_disable_preemptive_interrupts_nopr
	.reloc ., R_X86_64_SIZE32, cpu_disable_preemptive_interrupts_nopr; .int 0
	.int 0x985f3a2
	.quad .Lname931 /* index: 931 */
	.weak handle_manager_cloexec; .quad handle_manager_cloexec
	.reloc ., R_X86_64_SIZE32, handle_manager_cloexec; .int 0
	.int 0x785c3a3
	.quad .Lname932 /* index: 932 */
	.weak cpu_online_count; .quad cpu_online_count
	.reloc ., R_X86_64_SIZE32, cpu_online_count; .int 0
	.int 0xd3be3a4
	.quad .Lname933 /* index: 933 */
	.weak inode_recent_tryremove; .quad inode_recent_tryremove
	.reloc ., R_X86_64_SIZE32, inode_recent_tryremove; .int 0
	.int 0x263e3a5
	.quad .Lname934 /* index: 934 */
	.weak sys_pwritev; .quad sys_pwritev
	.reloc ., R_X86_64_SIZE32, sys_pwritev; .int 0
	.int 0x79403a6
	.quad .Lname935 /* index: 935 */
	.weak cpu_assert_running; .quad cpu_assert_running
	.reloc ., R_X86_64_SIZE32, cpu_assert_running; .int 0
	.int 0x5a063a7
	.quad 0 /* index: 936 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 937 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 938 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 939 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname940 /* index: 940 */
	.weak vm_node_remove; .quad vm_node_remove
	.reloc ., R_X86_64_SIZE32, vm_node_remove; .int 0
	.int 0x5ef7b45
	.quad 0 /* index: 941 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname942 /* index: 942 */
	.weak sys_userfaultfd; .quad sys_userfaultfd
	.reloc ., R_X86_64_SIZE32, sys_userfaultfd; .int 0
	.int 0x5e8dd44
	.quad 0 /* index: 943 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname944 /* index: 944 */
	.weak sys32_clock_adjtime; .quad sys32_clock_adjtime
	.reloc ., R_X86_64_SIZE32, sys32_clock_adjtime; .int 0
	.int 0x4a5a745
	.quad 0 /* index: 945 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 946 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname947 /* index: 947 */
	.weak sys_fchownat; .quad sys_fchownat
	.reloc ., R_X86_64_SIZE32, sys_fchownat; .int 0
	.int 0xe665144
	.quad .Lname948 /* index: 948 */
	.weak rwlock_endread; .quad rwlock_endread
	.reloc ., R_X86_64_SIZE32, rwlock_endread; .int 0
	.int 0x67e23b4
	.quad .Lname949 /* index: 949 */
	.weak blocking_cleanup_prioritize; .quad blocking_cleanup_prioritize
	.reloc ., R_X86_64_SIZE32, blocking_cleanup_prioritize; .int 0
	.int 0xab5d3b5
	.quad .Lname950 /* index: 950 */
	.weak vm_datablock_anonymous_type; .quad vm_datablock_anonymous_type
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous_type; .int 0
	.int 0x141adc5
	.quad 0 /* index: 951 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname952 /* index: 952 */
	.weak path_lock_tryupgrade; .quad path_lock_tryupgrade
	.reloc ., R_X86_64_SIZE32, path_lock_tryupgrade; .int 0
	.int 0xed66795
	.quad .Lname953 /* index: 953 */
	.weak sys32_linux_stat64; .quad sys32_linux_stat64
	.reloc ., R_X86_64_SIZE32, sys32_linux_stat64; .int 0
	.int 0x50abdf4
	.quad .Lname954 /* index: 954 */
	.weak sys_clock_settime; .quad sys_clock_settime
	.reloc ., R_X86_64_SIZE32, sys_clock_settime; .int 0
	.int 0x3a50605
	.quad 0 /* index: 955 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 956 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 957 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 958 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname959 /* index: 959 */
	.weak kernel_panic_icpustate; .quad kernel_panic_icpustate
	.reloc ., R_X86_64_SIZE32, kernel_panic_icpustate; .int 0
	.int 0x78a8df5
	.quad 0 /* index: 960 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname961 /* index: 961 */
	.weak sys_times; .quad sys_times
	.reloc ., R_X86_64_SIZE32, sys_times; .int 0
	.int 0x96a98c3
	.quad .Lname962 /* index: 962 */
	.weak x86_syscall32_sysenter_traced; .quad x86_syscall32_sysenter_traced
	.reloc ., R_X86_64_SIZE32, x86_syscall32_sysenter_traced; .int 0
	.int 0xb0b92f4
	.quad .Lname963 /* index: 963 */
	.weak vio_copytovio_from_phys; .quad vio_copytovio_from_phys
	.reloc ., R_X86_64_SIZE32, vio_copytovio_from_phys; .int 0
	.int 0x33623c3
	.quad .Lname964 /* index: 964 */
	.weak acpi_root; .quad acpi_root
	.reloc ., R_X86_64_SIZE32, acpi_root; .int 0
	.int 0x6f6f3c4
	.quad .Lname965 /* index: 965 */
	.weak superblock_mountlock_downgrade; .quad superblock_mountlock_downgrade
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_downgrade; .int 0
	.int 0xd3d83c5
	.quad 0 /* index: 966 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname967 /* index: 967 */
	.weak sys_syslog; .quad sys_syslog
	.reloc ., R_X86_64_SIZE32, sys_syslog; .int 0
	.int 0x6b733c7
	.quad .Lname968 /* index: 968 */
	.weak dbg_enter_ucpustate_c; .quad dbg_enter_ucpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_ucpustate_c; .int 0
	.int 0x19f3ed3
	.quad .Lname969 /* index: 969 */
	.weak sys32_readv; .quad sys32_readv
	.reloc ., R_X86_64_SIZE32, sys32_readv; .int 0
	.int 0x813b1d6
	.quad 0 /* index: 970 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname971 /* index: 971 */
	.weak handle_get_task; .quad handle_get_task
	.reloc ., R_X86_64_SIZE32, handle_get_task; .int 0
	.int 0x83473cb
	.quad .Lname972 /* index: 972 */
	.weak sys32_fcntl; .quad sys32_fcntl
	.reloc ., R_X86_64_SIZE32, sys32_fcntl; .int 0
	.int 0x827a3cc
	.quad .Lname973 /* index: 973 */
	.weak fpustate_loadfrom; .quad fpustate_loadfrom
	.reloc ., R_X86_64_SIZE32, fpustate_loadfrom; .int 0
	.int 0xf9d33cd
	.quad .Lname974 /* index: 974 */
	.weak kernel_debugtrap_on; .quad kernel_debugtrap_on
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_on; .int 0
	.int 0xfea93ce
	.quad .Lname975 /* index: 975 */
	.weak sys_quotactl; .quad sys_quotactl
	.reloc ., R_X86_64_SIZE32, sys_quotactl; .int 0
	.int 0xddaec2c
	.quad 0 /* index: 976 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname977 /* index: 977 */
	.weak vm_prefault; .quad vm_prefault
	.reloc ., R_X86_64_SIZE32, vm_prefault; .int 0
	.int 0x8c1be44
	.quad .Lname978 /* index: 978 */
	.weak sys32_stty; .quad sys32_stty
	.reloc ., R_X86_64_SIZE32, sys32_stty; .int 0
	.int 0x6811bd9
	.quad .Lname979 /* index: 979 */
	.weak directory_entry_alloc_s; .quad directory_entry_alloc_s
	.reloc ., R_X86_64_SIZE32, directory_entry_alloc_s; .int 0
	.int 0x6b553d3
	.quad .Lname980 /* index: 980 */
	.weak json_parser_getint64; .quad json_parser_getint64
	.reloc ., R_X86_64_SIZE32, json_parser_getint64; .int 0
	.int 0xf5873d4
	.quad 0 /* index: 981 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname982 /* index: 982 */
	.weak sys32_preadvf; .quad sys32_preadvf
	.reloc ., R_X86_64_SIZE32, sys32_preadvf; .int 0
	.int 0xc8d13d6
	.quad .Lname983 /* index: 983 */
	.weak inode_truncate; .quad inode_truncate
	.reloc ., R_X86_64_SIZE32, inode_truncate; .int 0
	.int 0xcfe2915
	.quad .Lname984 /* index: 984 */
	.weak slab_kmalloc_nx8; .quad slab_kmalloc_nx8
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx8; .int 0
	.int 0xb40d3d8
	.quad .Lname985 /* index: 985 */
	.weak directory_entry_destroy; .quad directory_entry_destroy
	.reloc ., R_X86_64_SIZE32, directory_entry_destroy; .int 0
	.int 0x84cb3d9
	.quad .Lname986 /* index: 986 */
	.weak sys_sched_yield; .quad sys_sched_yield
	.reloc ., R_X86_64_SIZE32, sys_sched_yield; .int 0
	.int 0x1061f94
	.quad .Lname987 /* index: 987 */
	.weak x86_syscall32_lcall7_iret; .quad x86_syscall32_lcall7_iret
	.reloc ., R_X86_64_SIZE32, x86_syscall32_lcall7_iret; .int 0
	.int 0x95cdcf4
	.quad .Lname988 /* index: 988 */
	.weak driver_with_namel; .quad driver_with_namel
	.reloc ., R_X86_64_SIZE32, driver_with_namel; .int 0
	.int 0x28933dc
	.quad 0 /* index: 989 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname990 /* index: 990 */
	.weak thiscpu_x86_lapicversion; .quad thiscpu_x86_lapicversion
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_lapicversion; .int 0
	.int 0xaf843de
	.quad .Lname991 /* index: 991 */
	.weak sys32_madvise; .quad sys32_madvise
	.reloc ., R_X86_64_SIZE32, sys32_madvise; .int 0
	.int 0x87db8a5
	.quad .Lname992 /* index: 992 */
	.weak sys32_mmap; .quad sys32_mmap
	.reloc ., R_X86_64_SIZE32, sys32_mmap; .int 0
	.int 0x68393e0
	.quad 0 /* index: 993 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname994 /* index: 994 */
	.weak x86_userexcept_callhandler; .quad x86_userexcept_callhandler
	.reloc ., R_X86_64_SIZE32, x86_userexcept_callhandler; .int 0
	.int 0x535a3e2
	.quad .Lname995 /* index: 995 */
	.weak inode_aread_phys; .quad inode_aread_phys
	.reloc ., R_X86_64_SIZE32, inode_aread_phys; .int 0
	.int 0xd34e3e3
	.quad .Lname996 /* index: 996 */
	.weak aio_pbuffer_memset; .quad aio_pbuffer_memset
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_memset; .int 0
	.int 0xb08d3e4
	.quad .Lname997 /* index: 997 */
	.weak json_decode; .quad json_decode
	.reloc ., R_X86_64_SIZE32, json_decode; .int 0
	.int 0x5da43e5
	.quad 0 /* index: 998 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname999 /* index: 999 */
	.weak task_setprocess; .quad task_setprocess
	.reloc ., R_X86_64_SIZE32, task_setprocess; .int 0
	.int 0xda37a93
	.quad .Lname1000 /* index: 1000 */
	.weak path_traversen_ex; .quad path_traversen_ex
	.reloc ., R_X86_64_SIZE32, path_traversen_ex; .int 0
	.int 0xf5643e8
	.quad .Lname1001 /* index: 1001 */
	.weak x86_pagedir_syncall_maybe_global; .quad x86_pagedir_syncall_maybe_global
	.reloc ., R_X86_64_SIZE32, x86_pagedir_syncall_maybe_global; .int 0
	.int 0x3e6c5fc
	.quad 0 /* index: 1002 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1003 /* index: 1003 */
	.weak x86_pit_lock; .quad x86_pit_lock
	.reloc ., R_X86_64_SIZE32, x86_pit_lock; .int 0
	.int 0x73ff3eb
	.quad .Lname1004 /* index: 1004 */
	.weak x86_userexcept_callhandler64; .quad x86_userexcept_callhandler64
	.reloc ., R_X86_64_SIZE32, x86_userexcept_callhandler64; .int 0
	.int 0x5a3e0a4
	.quad .Lname1005 /* index: 1005 */
	.weak validate_userm; .quad validate_userm
	.reloc ., R_X86_64_SIZE32, validate_userm; .int 0
	.int 0x34333ed
	.quad 0 /* index: 1006 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1007 /* index: 1007 */
	.weak timespec_to_qtime; .quad timespec_to_qtime
	.reloc ., R_X86_64_SIZE32, timespec_to_qtime; .int 0
	.int 0xf783b45
	.quad .Lname1008 /* index: 1008 */
	.weak vmb_map; .quad vmb_map
	.reloc ., R_X86_64_SIZE32, vmb_map; .int 0
	.int 0xd3863f0
	.quad 0 /* index: 1009 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1010 /* index: 1010 */
	.weak block_device_awrite_phys_sector; .quad block_device_awrite_phys_sector
	.reloc ., R_X86_64_SIZE32, block_device_awrite_phys_sector; .int 0
	.int 0xb8a83f2
	.quad .Lname1011 /* index: 1011 */
	.weak sys_utimes; .quad sys_utimes
	.reloc ., R_X86_64_SIZE32, sys_utimes; .int 0
	.int 0x6cd5353
	.quad 0 /* index: 1012 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1013 /* index: 1013 */
	.weak kernel_debugtrap_lcpustate; .quad kernel_debugtrap_lcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_lcpustate; .int 0
	.int 0x96393f5
	.quad 0 /* index: 1014 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1015 /* index: 1015 */
	.weak sys32_mq_notify; .quad sys32_mq_notify
	.reloc ., R_X86_64_SIZE32, sys32_mq_notify; .int 0
	.int 0x43e90a9
	.quad .Lname1016 /* index: 1016 */
	.weak getreg_gpregs; .quad getreg_gpregs
	.reloc ., R_X86_64_SIZE32, getreg_gpregs; .int 0
	.int 0x82c0053
	.quad .Lname1017 /* index: 1017 */
	.weak sys32_timer_settime64; .quad sys32_timer_settime64
	.reloc ., R_X86_64_SIZE32, sys32_timer_settime64; .int 0
	.int 0xe204354
	.quad .Lname1018 /* index: 1018 */
	.weak sys32_setreuid32; .quad sys32_setreuid32
	.reloc ., R_X86_64_SIZE32, sys32_setreuid32; .int 0
	.int 0xe4adbb2
	.quad .Lname1019 /* index: 1019 */
	.weak sys32__llseek; .quad sys32__llseek
	.reloc ., R_X86_64_SIZE32, sys32__llseek; .int 0
	.int 0xf35f3fb
	.quad .Lname1020 /* index: 1020 */
	.weak __predict_update_sil; .quad __predict_update_sil
	.reloc ., R_X86_64_SIZE32, __predict_update_sil; .int 0
	.int 0x45513fc
	.quad .Lname1021 /* index: 1021 */
	.weak sys32_timerfd_gettime; .quad sys32_timerfd_gettime
	.reloc ., R_X86_64_SIZE32, sys32_timerfd_gettime; .int 0
	.int 0x86b7465
	.quad .Lname1022 /* index: 1022 */
	.weak sys32_rt_sigreturn; .quad sys32_rt_sigreturn
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigreturn; .int 0
	.int 0xfa6b3fe
	.quad .Lname1023 /* index: 1023 */
	.weak ringbuffer_unwrite; .quad ringbuffer_unwrite
	.reloc ., R_X86_64_SIZE32, ringbuffer_unwrite; .int 0
	.int 0x8021b55
	.quad 0 /* index: 1024 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1025 /* index: 1025 */
	.weak memcmpq; .quad memcmpq
	.reloc ., R_X86_64_SIZE32, memcmpq; .int 0
	.int 0x3c3a401
	.quad 0 /* index: 1026 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1027 /* index: 1027 */
	.weak task_connect_ghost_c; .quad task_connect_ghost_c
	.reloc ., R_X86_64_SIZE32, task_connect_ghost_c; .int 0
	.int 0x1c6403
	.quad .Lname1028 /* index: 1028 */
	.weak block_device_partition_read; .quad block_device_partition_read
	.reloc ., R_X86_64_SIZE32, block_device_partition_read; .int 0
	.int 0x6052404
	.quad .Lname1029 /* index: 1029 */
	.weak sys32_mq_timedreceive; .quad sys32_mq_timedreceive
	.reloc ., R_X86_64_SIZE32, sys32_mq_timedreceive; .int 0
	.int 0x871c405
	.quad 0 /* index: 1030 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1031 /* index: 1031 */
	.weak memcmpw; .quad memcmpw
	.reloc ., R_X86_64_SIZE32, memcmpw; .int 0
	.int 0x3c3a407
	.quad .Lname1032 /* index: 1032 */
	.weak sys_mkdir; .quad sys_mkdir
	.reloc ., R_X86_64_SIZE32, sys_mkdir; .int 0
	.int 0x9646202
	.quad .Lname1033 /* index: 1033 */
	.weak sys32_get_mempolicy; .quad sys32_get_mempolicy
	.reloc ., R_X86_64_SIZE32, sys32_get_mempolicy; .int 0
	.int 0x2c66409
	.quad 0 /* index: 1034 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1035 /* index: 1035 */
	.weak x86_fxsave_mxcsr_mask; .quad x86_fxsave_mxcsr_mask
	.reloc ., R_X86_64_SIZE32, x86_fxsave_mxcsr_mask; .int 0
	.int 0xb8df40b
	.quad 0 /* index: 1036 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1037 /* index: 1037 */
	.weak sys32_eventfd2; .quad sys32_eventfd2
	.reloc ., R_X86_64_SIZE32, sys32_eventfd2; .int 0
	.int 0xce32e02
	.quad 0 /* index: 1038 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1039 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1040 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1041 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1042 /* index: 1042 */
	.weak keyboard_device_trygetchar; .quad keyboard_device_trygetchar
	.reloc ., R_X86_64_SIZE32, keyboard_device_trygetchar; .int 0
	.int 0x2dfb412
	.quad 0 /* index: 1043 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1044 /* index: 1044 */
	.weak ringbuffer_skipread; .quad ringbuffer_skipread
	.reloc ., R_X86_64_SIZE32, ringbuffer_skipread; .int 0
	.int 0x5cf3414
	.quad 0 /* index: 1045 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1046 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1047 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1048 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1049 /* index: 1049 */
	.weak sys32_set_mempolicy; .quad sys32_set_mempolicy
	.reloc ., R_X86_64_SIZE32, sys32_set_mempolicy; .int 0
	.int 0x6c66419
	.quad .Lname1050 /* index: 1050 */
	.weak vm86_hw_intr; .quad vm86_hw_intr
	.reloc ., R_X86_64_SIZE32, vm86_hw_intr; .int 0
	.int 0x82559e2
	.quad .Lname1051 /* index: 1051 */
	.weak sys_setxattr; .quad sys_setxattr
	.reloc ., R_X86_64_SIZE32, sys_setxattr; .int 0
	.int 0xb0e1d22
	.quad .Lname1052 /* index: 1052 */
	.weak memcmpl; .quad memcmpl
	.reloc ., R_X86_64_SIZE32, memcmpl; .int 0
	.int 0x3c3a41c
	.quad .Lname1053 /* index: 1053 */
	.weak handle_get_vm; .quad handle_get_vm
	.reloc ., R_X86_64_SIZE32, handle_get_vm; .int 0
	.int 0xb58341d
	.quad .Lname1054 /* index: 1054 */
	.weak addr2line_begin; .quad addr2line_begin
	.reloc ., R_X86_64_SIZE32, addr2line_begin; .int 0
	.int 0x201f41e
	.quad .Lname1055 /* index: 1055 */
	.weak heap_validate; .quad heap_validate
	.reloc ., R_X86_64_SIZE32, heap_validate; .int 0
	.int 0xa97ce05
	.quad .Lname1056 /* index: 1056 */
	.weak thisvm_pdir_phys_ptr; .quad thisvm_pdir_phys_ptr
	.reloc ., R_X86_64_SIZE32, thisvm_pdir_phys_ptr; .int 0
	.int 0x7b3d712
	.quad .Lname1057 /* index: 1057 */
	.weak setreg_coregs; .quad setreg_coregs
	.reloc ., R_X86_64_SIZE32, setreg_coregs; .int 0
	.int 0xc6d0023
	.quad 0 /* index: 1058 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1059 /* index: 1059 */
	.weak sys_clock_adjtime; .quad sys_clock_adjtime
	.reloc ., R_X86_64_SIZE32, sys_clock_adjtime; .int 0
	.int 0xddf0635
	.quad 0 /* index: 1060 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1061 /* index: 1061 */
	.weak sys32_clone; .quad sys32_clone
	.reloc ., R_X86_64_SIZE32, sys32_clone; .int 0
	.int 0x8233425
	.quad .Lname1062 /* index: 1062 */
	.weak sys32_vm86; .quad sys32_vm86
	.reloc ., R_X86_64_SIZE32, sys32_vm86; .int 0
	.int 0x68180d6
	.quad .Lname1063 /* index: 1063 */
	.weak vm_kernel_treelock_downgrade; .quad vm_kernel_treelock_downgrade
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_downgrade; .int 0
	.int 0xf47fd75
	.quad .Lname1064 /* index: 1064 */
	.weak vio_readq_aligned; .quad vio_readq_aligned
	.reloc ., R_X86_64_SIZE32, vio_readq_aligned; .int 0
	.int 0xe570f4
	.quad .Lname1065 /* index: 1065 */
	.weak sys_rmdir; .quad sys_rmdir
	.reloc ., R_X86_64_SIZE32, sys_rmdir; .int 0
	.int 0x9694202
	.quad 0 /* index: 1066 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1067 /* index: 1067 */
	.weak sys_chroot; .quad sys_chroot
	.reloc ., R_X86_64_SIZE32, sys_chroot; .int 0
	.int 0x59846f4
	.quad .Lname1068 /* index: 1068 */
	.weak superblock_syncall; .quad superblock_syncall
	.reloc ., R_X86_64_SIZE32, superblock_syncall; .int 0
	.int 0xa7e9bdc
	.quad .Lname1069 /* index: 1069 */
	.weak task_setsessionleader; .quad task_setsessionleader
	.reloc ., R_X86_64_SIZE32, task_setsessionleader; .int 0
	.int 0x8f700b2
	.quad .Lname1070 /* index: 1070 */
	.weak driver_getsection; .quad driver_getsection
	.reloc ., R_X86_64_SIZE32, driver_getsection; .int 0
	.int 0x594e42e
	.quad .Lname1071 /* index: 1071 */
	.weak handle_installinto; .quad handle_installinto
	.reloc ., R_X86_64_SIZE32, handle_installinto; .int 0
	.int 0xbaaf42f
	.quad .Lname1072 /* index: 1072 */
	.weak acpi_lookup; .quad acpi_lookup
	.reloc ., R_X86_64_SIZE32, acpi_lookup; .int 0
	.int 0x6540430
	.quad .Lname1073 /* index: 1073 */
	.weak sys32_gettimeofday64; .quad sys32_gettimeofday64
	.reloc ., R_X86_64_SIZE32, sys32_gettimeofday64; .int 0
	.int 0x9160d74
	.quad .Lname1074 /* index: 1074 */
	.weak this_user_except_handler; .quad this_user_except_handler
	.reloc ., R_X86_64_SIZE32, this_user_except_handler; .int 0
	.int 0xbeb6432
	.quad .Lname1075 /* index: 1075 */
	.weak vm_datablock_sync; .quad vm_datablock_sync
	.reloc ., R_X86_64_SIZE32, vm_datablock_sync; .int 0
	.int 0x2ec68b3
	.quad .Lname1076 /* index: 1076 */
	.weak sys_futimesat; .quad sys_futimesat
	.reloc ., R_X86_64_SIZE32, sys_futimesat; .int 0
	.int 0x20a9434
	.quad .Lname1077 /* index: 1077 */
	.weak pagedir_unprepare_mapone; .quad pagedir_unprepare_mapone
	.reloc ., R_X86_64_SIZE32, pagedir_unprepare_mapone; .int 0
	.int 0xbdfa435
	.quad 0 /* index: 1078 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1079 /* index: 1079 */
	.weak sys32_settimeofday; .quad sys32_settimeofday
	.reloc ., R_X86_64_SIZE32, sys32_settimeofday; .int 0
	.int 0x2a91609
	.quad 0 /* index: 1080 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1081 /* index: 1081 */
	.weak file_destroy; .quad file_destroy
	.reloc ., R_X86_64_SIZE32, file_destroy; .int 0
	.int 0xc1a9439
	.quad 0 /* index: 1082 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1083 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1084 /* index: 1084 */
	.weak setreg_gpregs; .quad setreg_gpregs
	.reloc ., R_X86_64_SIZE32, setreg_gpregs; .int 0
	.int 0xc2c0023
	.quad 0 /* index: 1085 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1086 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1087 /* index: 1087 */
	.weak kffree; .quad kffree
	.reloc ., R_X86_64_SIZE32, kffree; .int 0
	.int 0x71cd8b5
	.quad .Lname1088 /* index: 1088 */
	.weak sys32_nanosleep; .quad sys32_nanosleep
	.reloc ., R_X86_64_SIZE32, sys32_nanosleep; .int 0
	.int 0x3021440
	.quad 0 /* index: 1089 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1090 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1091 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1092 /* index: 1092 */
	.weak sys_io_submit; .quad sys_io_submit
	.reloc ., R_X86_64_SIZE32, sys_io_submit; .int 0
	.int 0xda2f444
	.quad .Lname1093 /* index: 1093 */
	.weak sys_timer_settime; .quad sys_timer_settime
	.reloc ., R_X86_64_SIZE32, sys_timer_settime; .int 0
	.int 0x3536135
	.quad 0 /* index: 1094 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1095 /* index: 1095 */
	.weak vio_andq; .quad vio_andq
	.reloc ., R_X86_64_SIZE32, vio_andq; .int 0
	.int 0x558361
	.quad .Lname1096 /* index: 1096 */
	.weak path_printentex; .quad path_printentex
	.reloc ., R_X86_64_SIZE32, path_printentex; .int 0
	.int 0xf4e5448
	.quad 0 /* index: 1097 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1098 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1099 /* index: 1099 */
	.weak rwlock_writing; .quad rwlock_writing
	.reloc ., R_X86_64_SIZE32, rwlock_writing; .int 0
	.int 0xc508b7
	.quad .Lname1100 /* index: 1100 */
	.weak sys32_ppoll; .quad sys32_ppoll
	.reloc ., R_X86_64_SIZE32, sys32_ppoll; .int 0
	.int 0x81c744c
	.quad 0 /* index: 1101 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1102 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1103 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1104 /* index: 1104 */
	.weak vm_unmap; .quad vm_unmap
	.reloc ., R_X86_64_SIZE32, vm_unmap; .int 0
	.int 0x36c5450
	.quad 0 /* index: 1105 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1106 /* index: 1106 */
	.weak inode_recent_getcur; .quad inode_recent_getcur
	.reloc ., R_X86_64_SIZE32, inode_recent_getcur; .int 0
	.int 0xd308452
	.quad .Lname1107 /* index: 1107 */
	.weak sys32_ipc; .quad sys32_ipc
	.reloc ., R_X86_64_SIZE32, sys32_ipc; .int 0
	.int 0x6683b63
	.quad .Lname1108 /* index: 1108 */
	.weak sys32_epoll_pwait; .quad sys32_epoll_pwait
	.reloc ., R_X86_64_SIZE32, sys32_epoll_pwait; .int 0
	.int 0xa40a454
	.quad .Lname1109 /* index: 1109 */
	.weak sys32_timerfd_settime; .quad sys32_timerfd_settime
	.reloc ., R_X86_64_SIZE32, sys32_timerfd_settime; .int 0
	.int 0xc6b7455
	.quad 0 /* index: 1110 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1111 /* index: 1111 */
	.weak sys32_personality; .quad sys32_personality
	.reloc ., R_X86_64_SIZE32, sys32_personality; .int 0
	.int 0xe5c00b9
	.quad 0 /* index: 1112 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1113 /* index: 1113 */
	.weak mouse_buffer_trygetpacket; .quad mouse_buffer_trygetpacket
	.reloc ., R_X86_64_SIZE32, mouse_buffer_trygetpacket; .int 0
	.int 0xe4b64
	.quad .Lname1114 /* index: 1114 */
	.weak sys_ioprio_set; .quad sys_ioprio_set
	.reloc ., R_X86_64_SIZE32, sys_ioprio_set; .int 0
	.int 0x8736804
	.quad 0 /* index: 1115 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1116 /* index: 1116 */
	.weak sys_fchmodat; .quad sys_fchmodat
	.reloc ., R_X86_64_SIZE32, sys_fchmodat; .int 0
	.int 0xe64cf44
	.quad .Lname1117 /* index: 1117 */
	.weak handle_tryclose_nosym; .quad handle_tryclose_nosym
	.reloc ., R_X86_64_SIZE32, handle_tryclose_nosym; .int 0
	.int 0x82a645d
	.quad .Lname1118 /* index: 1118 */
	.weak heap_align; .quad heap_align
	.reloc ., R_X86_64_SIZE32, heap_align; .int 0
	.int 0x652c45e
	.quad .Lname1119 /* index: 1119 */
	.weak sys_setdomainname; .quad sys_setdomainname
	.reloc ., R_X86_64_SIZE32, sys_setdomainname; .int 0
	.int 0xe56fb65
	.quad 0 /* index: 1120 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1121 /* index: 1121 */
	.weak x86_sysroute1_asm32_int80; .quad x86_sysroute1_asm32_int80
	.reloc ., R_X86_64_SIZE32, x86_sysroute1_asm32_int80; .int 0
	.int 0x4e1610
	.quad 0 /* index: 1122 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1123 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1124 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1125 /* index: 1125 */
	.weak driver_clear_fde_cache; .quad driver_clear_fde_cache
	.reloc ., R_X86_64_SIZE32, driver_clear_fde_cache; .int 0
	.int 0xe1fc465
	.quad 0 /* index: 1126 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1127 /* index: 1127 */
	.weak sys_epoll_pwait; .quad sys_epoll_pwait
	.reloc ., R_X86_64_SIZE32, sys_epoll_pwait; .int 0
	.int 0x93bf934
	.quad 0 /* index: 1128 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1129 /* index: 1129 */
	.weak keyboard_buffer_trygetkey; .quad keyboard_buffer_trygetkey
	.reloc ., R_X86_64_SIZE32, keyboard_buffer_trygetkey; .int 0
	.int 0xa72d469
	.quad 0 /* index: 1130 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1131 /* index: 1131 */
	.weak userkern_segment_block; .quad userkern_segment_block
	.reloc ., R_X86_64_SIZE32, userkern_segment_block; .int 0
	.int 0xb00546b
	.quad .Lname1132 /* index: 1132 */
	.weak handle_manager_kernel; .quad handle_manager_kernel
	.reloc ., R_X86_64_SIZE32, handle_manager_kernel; .int 0
	.int 0x2e9946c
	.quad .Lname1133 /* index: 1133 */
	.weak pipe_writer_create; .quad pipe_writer_create
	.reloc ., R_X86_64_SIZE32, pipe_writer_create; .int 0
	.int 0xfa87f85
	.quad 0 /* index: 1134 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1135 /* index: 1135 */
	.weak vm_delhwbreak; .quad vm_delhwbreak
	.reloc ., R_X86_64_SIZE32, vm_delhwbreak; .int 0
	.int 0x2ec272b
	.quad 0 /* index: 1136 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1137 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1138 /* index: 1138 */
	.weak sys32_uselib; .quad sys32_uselib
	.reloc ., R_X86_64_SIZE32, sys32_uselib; .int 0
	.int 0x179e472
	.quad .Lname1139 /* index: 1139 */
	.weak dbg_ungetc; .quad dbg_ungetc
	.reloc ., R_X86_64_SIZE32, dbg_ungetc; .int 0
	.int 0x6c27473
	.quad .Lname1140 /* index: 1140 */
	.weak sys_readvf; .quad sys_readvf
	.reloc ., R_X86_64_SIZE32, sys_readvf; .int 0
	.int 0x68ccb56
	.quad .Lname1141 /* index: 1141 */
	.weak inode_file_pwrite_with_write; .quad inode_file_pwrite_with_write
	.reloc ., R_X86_64_SIZE32, inode_file_pwrite_with_write; .int 0
	.int 0x7ea9475
	.quad .Lname1142 /* index: 1142 */
	.weak zlib_reader_init; .quad zlib_reader_init
	.reloc ., R_X86_64_SIZE32, zlib_reader_init; .int 0
	.int 0x4256254
	.quad 0 /* index: 1143 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1144 /* index: 1144 */
	.weak system_clearcaches_s; .quad system_clearcaches_s
	.reloc ., R_X86_64_SIZE32, system_clearcaches_s; .int 0
	.int 0xd1f8713
	.quad .Lname1145 /* index: 1145 */
	.weak sys32_time64; .quad sys32_time64
	.reloc ., R_X86_64_SIZE32, sys32_time64; .int 0
	.int 0x1205e14
	.quad .Lname1146 /* index: 1146 */
	.weak vpage_ffree; .quad vpage_ffree
	.reloc ., R_X86_64_SIZE32, vpage_ffree; .int 0
	.int 0xb21bf65
	.quad 0 /* index: 1147 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1148 /* index: 1148 */
	.weak x86_idt_syscall_traced; .quad x86_idt_syscall_traced
	.reloc ., R_X86_64_SIZE32, x86_idt_syscall_traced; .int 0
	.int 0x3dd19c4
	.quad .Lname1149 /* index: 1149 */
	.weak sys32_getsockopt; .quad sys32_getsockopt
	.reloc ., R_X86_64_SIZE32, sys32_getsockopt; .int 0
	.int 0xdc8a94
	.quad 0 /* index: 1150 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1151 /* index: 1151 */
	.weak pipe_create; .quad pipe_create
	.reloc ., R_X86_64_SIZE32, pipe_create; .int 0
	.int 0x5dfbe15
	.quad .Lname1152 /* index: 1152 */
	.weak pagedir_maphintone_p; .quad pagedir_maphintone_p
	.reloc ., R_X86_64_SIZE32, pagedir_maphintone_p; .int 0
	.int 0x6579480
	.quad .Lname1153 /* index: 1153 */
	.weak sys32_dup; .quad sys32_dup
	.reloc ., R_X86_64_SIZE32, sys32_dup; .int 0
	.int 0x66820c0
	.quad 0 /* index: 1154 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1155 /* index: 1155 */
	.weak vm_writephysb; .quad vm_writephysb
	.reloc ., R_X86_64_SIZE32, vm_writephysb; .int 0
	.int 0x7f029e2
	.quad .Lname1156 /* index: 1156 */
	.weak dbg_indent; .quad dbg_indent
	.reloc ., R_X86_64_SIZE32, dbg_indent; .int 0
	.int 0x6020484
	.quad .Lname1157 /* index: 1157 */
	.weak dbg_endupdate; .quad dbg_endupdate
	.reloc ., R_X86_64_SIZE32, dbg_endupdate; .int 0
	.int 0x14bf485
	.quad 0 /* index: 1158 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1159 /* index: 1159 */
	.weak regdump_gpreg; .quad regdump_gpreg
	.reloc ., R_X86_64_SIZE32, regdump_gpreg; .int 0
	.int 0xee3c487
	.quad .Lname1160 /* index: 1160 */
	.weak vm_datapart_getfutex; .quad vm_datapart_getfutex
	.reloc ., R_X86_64_SIZE32, vm_datapart_getfutex; .int 0
	.int 0x97ee248
	.quad 0 /* index: 1161 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1162 /* index: 1162 */
	.weak sys_shutdown; .quad sys_shutdown
	.reloc ., R_X86_64_SIZE32, sys_shutdown; .int 0
	.int 0x87a404e
	.quad .Lname1163 /* index: 1163 */
	.weak sys32_sigaction; .quad sys32_sigaction
	.reloc ., R_X86_64_SIZE32, sys32_sigaction; .int 0
	.int 0xb12beae
	.quad 0 /* index: 1164 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1165 /* index: 1165 */
	.weak this_exception_faultaddr; .quad this_exception_faultaddr
	.reloc ., R_X86_64_SIZE32, this_exception_faultaddr; .int 0
	.int 0xf1ce8c2
	.quad 0 /* index: 1166 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1167 /* index: 1167 */
	.weak task_setvm; .quad task_setvm
	.reloc ., R_X86_64_SIZE32, task_setvm; .int 0
	.int 0x16e636d
	.quad .Lname1168 /* index: 1168 */
	.weak pagedir_prepare_map; .quad pagedir_prepare_map
	.reloc ., R_X86_64_SIZE32, pagedir_prepare_map; .int 0
	.int 0xa917490
	.quad 0 /* index: 1169 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1170 /* index: 1170 */
	.weak vmb_node_insert; .quad vmb_node_insert
	.reloc ., R_X86_64_SIZE32, vmb_node_insert; .int 0
	.int 0xda0bb34
	.quad .Lname1171 /* index: 1171 */
	.weak aio_buffer_copytovphys; .quad aio_buffer_copytovphys
	.reloc ., R_X86_64_SIZE32, aio_buffer_copytovphys; .int 0
	.int 0xaa84493
	.quad .Lname1172 /* index: 1172 */
	.weak sys_fadvise64; .quad sys_fadvise64
	.reloc ., R_X86_64_SIZE32, sys_fadvise64; .int 0
	.int 0xd9c494
	.quad .Lname1173 /* index: 1173 */
	.weak fs_clone; .quad fs_clone
	.reloc ., R_X86_64_SIZE32, fs_clone; .int 0
	.int 0x95a3495
	.quad .Lname1174 /* index: 1174 */
	.weak isr_usage_of; .quad isr_usage_of
	.reloc ., R_X86_64_SIZE32, isr_usage_of; .int 0
	.int 0xe773496
	.quad .Lname1175 /* index: 1175 */
	.weak sys32_delete_module; .quad sys32_delete_module
	.reloc ., R_X86_64_SIZE32, sys32_delete_module; .int 0
	.int 0x6011ab5
	.quad .Lname1176 /* index: 1176 */
	.weak mall_trace_nx; .quad mall_trace_nx
	.reloc ., R_X86_64_SIZE32, mall_trace_nx; .int 0
	.int 0xbfa9498
	.quad .Lname1177 /* index: 1177 */
	.weak dbg_getuni; .quad dbg_getuni
	.reloc ., R_X86_64_SIZE32, dbg_getuni; .int 0
	.int 0x5da1499
	.quad .Lname1178 /* index: 1178 */
	.weak unicode_16to32; .quad unicode_16to32
	.reloc ., R_X86_64_SIZE32, unicode_16to32; .int 0
	.int 0x6b80f12
	.quad 0 /* index: 1179 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1180 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1181 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1182 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1183 /* index: 1183 */
	.weak sys_setfsgid; .quad sys_setfsgid
	.reloc ., R_X86_64_SIZE32, sys_setfsgid; .int 0
	.int 0xb1d0b64
	.quad 0 /* index: 1184 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1185 /* index: 1185 */
	.weak unicode_readutf16_swap_rev_n; .quad unicode_readutf16_swap_rev_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_swap_rev_n; .int 0
	.int 0x1c8df3e
	.quad .Lname1186 /* index: 1186 */
	.weak sys_epoll_ctl; .quad sys_epoll_ctl
	.reloc ., R_X86_64_SIZE32, sys_epoll_ctl; .int 0
	.int 0xf39068c
	.quad .Lname1187 /* index: 1187 */
	.weak x86_iopl_keep_after_exec; .quad x86_iopl_keep_after_exec
	.reloc ., R_X86_64_SIZE32, x86_iopl_keep_after_exec; .int 0
	.int 0x1cb14a3
	.quad .Lname1188 /* index: 1188 */
	.weak sys_getegid; .quad sys_getegid
	.reloc ., R_X86_64_SIZE32, sys_getegid; .int 0
	.int 0xdb1b4a4
	.quad .Lname1189 /* index: 1189 */
	.weak dbg_vprintf; .quad dbg_vprintf
	.reloc ., R_X86_64_SIZE32, dbg_vprintf; .int 0
	.int 0xd1288c6
	.quad .Lname1190 /* index: 1190 */
	.weak setreg_drregs; .quad setreg_drregs
	.reloc ., R_X86_64_SIZE32, setreg_drregs; .int 0
	.int 0xc720023
	.quad .Lname1191 /* index: 1191 */
	.weak instruction_succ; .quad instruction_succ
	.reloc ., R_X86_64_SIZE32, instruction_succ; .int 0
	.int 0xfba04f3
	.quad .Lname1192 /* index: 1192 */
	.weak path_printex; .quad path_printex
	.reloc ., R_X86_64_SIZE32, path_printex; .int 0
	.int 0xe8f4a8
	.quad .Lname1193 /* index: 1193 */
	.weak json_writer_endarray; .quad json_writer_endarray
	.reloc ., R_X86_64_SIZE32, json_writer_endarray; .int 0
	.int 0xe60b4a9
	.quad 0 /* index: 1194 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1195 /* index: 1195 */
	.weak inode_readallk; .quad inode_readallk
	.reloc ., R_X86_64_SIZE32, inode_readallk; .int 0
	.int 0xe20d4ab
	.quad .Lname1196 /* index: 1196 */
	.weak rawmemlenl; .quad rawmemlenl
	.reloc ., R_X86_64_SIZE32, rawmemlenl; .int 0
	.int 0x3c5a4ac
	.quad .Lname1197 /* index: 1197 */
	.weak vio_andb; .quad vio_andb
	.reloc ., R_X86_64_SIZE32, vio_andb; .int 0
	.int 0x558372
	.quad .Lname1198 /* index: 1198 */
	.weak page_malloc_between; .quad page_malloc_between
	.reloc ., R_X86_64_SIZE32, page_malloc_between; .int 0
	.int 0xabb34ae
	.quad 0 /* index: 1199 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1200 /* index: 1200 */
	.weak sys_clock_gettime; .quad sys_clock_gettime
	.reloc ., R_X86_64_SIZE32, sys_clock_gettime; .int 0
	.int 0x7a50635
	.quad .Lname1201 /* index: 1201 */
	.weak rawmemlenq; .quad rawmemlenq
	.reloc ., R_X86_64_SIZE32, rawmemlenq; .int 0
	.int 0x3c5a4b1
	.quad .Lname1202 /* index: 1202 */
	.weak task_waitfor; .quad task_waitfor
	.reloc ., R_X86_64_SIZE32, task_waitfor; .int 0
	.int 0xae80e02
	.quad 0 /* index: 1203 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1204 /* index: 1204 */
	.weak character_device_read; .quad character_device_read
	.reloc ., R_X86_64_SIZE32, character_device_read; .int 0
	.int 0x98b84b4
	.quad .Lname1205 /* index: 1205 */
	.weak regdump_kcpustate; .quad regdump_kcpustate
	.reloc ., R_X86_64_SIZE32, regdump_kcpustate; .int 0
	.int 0xbf454b5
	.quad .Lname1206 /* index: 1206 */
	.weak inode_readallv; .quad inode_readallv
	.reloc ., R_X86_64_SIZE32, inode_readallv; .int 0
	.int 0xe20d4b6
	.quad .Lname1207 /* index: 1207 */
	.weak rawmemlenw; .quad rawmemlenw
	.reloc ., R_X86_64_SIZE32, rawmemlenw; .int 0
	.int 0x3c5a4b7
	.quad .Lname1208 /* index: 1208 */
	.weak superblock_nodeslock_upgrade_nx; .quad superblock_nodeslock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_upgrade_nx; .int 0
	.int 0xe6014b8
	.quad .Lname1209 /* index: 1209 */
	.weak superblock_nodeslock_read; .quad superblock_nodeslock_read
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_read; .int 0
	.int 0x61aeb74
	.quad 0 /* index: 1210 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1211 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1212 /* index: 1212 */
	.weak sys_sched_setscheduler; .quad sys_sched_setscheduler
	.reloc ., R_X86_64_SIZE32, sys_sched_setscheduler; .int 0
	.int 0xeb96042
	.quad 0 /* index: 1213 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1214 /* index: 1214 */
	.weak sys32_timer_getoverrun; .quad sys32_timer_getoverrun
	.reloc ., R_X86_64_SIZE32, sys32_timer_getoverrun; .int 0
	.int 0xdc864be
	.quad .Lname1215 /* index: 1215 */
	.weak sys32_oldolduname; .quad sys32_oldolduname
	.reloc ., R_X86_64_SIZE32, sys32_oldolduname; .int 0
	.int 0xa856b75
	.quad 0 /* index: 1216 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1217 /* index: 1217 */
	.weak memendq; .quad memendq
	.reloc ., R_X86_64_SIZE32, memendq; .int 0
	.int 0x3c3c4c1
	.quad 0 /* index: 1218 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1219 /* index: 1219 */
	.weak mzones; .quad mzones
	.reloc ., R_X86_64_SIZE32, mzones; .int 0
	.int 0x75164c3
	.quad .Lname1220 /* index: 1220 */
	.weak pidns_read; .quad pidns_read
	.reloc ., R_X86_64_SIZE32, pidns_read; .int 0
	.int 0x591e4c4
	.quad .Lname1221 /* index: 1221 */
	.weak sys32_timerfd_settime64; .quad sys32_timerfd_settime64
	.reloc ., R_X86_64_SIZE32, sys32_timerfd_settime64; .int 0
	.int 0xb7454f4
	.quad .Lname1222 /* index: 1222 */
	.weak sys_sched_get_priority_min; .quad sys_sched_get_priority_min
	.reloc ., R_X86_64_SIZE32, sys_sched_get_priority_min; .int 0
	.int 0xdd6a79e
	.quad .Lname1223 /* index: 1223 */
	.weak memendw; .quad memendw
	.reloc ., R_X86_64_SIZE32, memendw; .int 0
	.int 0x3c3c4c7
	.quad 0 /* index: 1224 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1225 /* index: 1225 */
	.weak vm86_fullstep; .quad vm86_fullstep
	.reloc ., R_X86_64_SIZE32, vm86_fullstep; .int 0
	.int 0x7386f60
	.quad 0 /* index: 1226 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1227 /* index: 1227 */
	.weak regdump_sreg; .quad regdump_sreg
	.reloc ., R_X86_64_SIZE32, regdump_sreg; .int 0
	.int 0x3ed7377
	.quad .Lname1228 /* index: 1228 */
	.weak __stack_chk_fail; .quad __stack_chk_fail
	.reloc ., R_X86_64_SIZE32, __stack_chk_fail; .int 0
	.int 0x595a4cc
	.quad .Lname1229 /* index: 1229 */
	.weak vm_datapart_decref_and_merge; .quad vm_datapart_decref_and_merge
	.reloc ., R_X86_64_SIZE32, vm_datapart_decref_and_merge; .int 0
	.int 0x3d762e5
	.quad .Lname1230 /* index: 1230 */
	.weak vm_datapart_lockread_setcore; .quad vm_datapart_lockread_setcore
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockread_setcore; .int 0
	.int 0x8687cb5
	.quad .Lname1231 /* index: 1231 */
	.weak minfo; .quad minfo
	.reloc ., R_X86_64_SIZE32, minfo; .int 0
	.int 0x7404cf
	.quad .Lname1232 /* index: 1232 */
	.weak x86_syscall_emulate_sysenter_r; .quad x86_syscall_emulate_sysenter_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate_sysenter_r; .int 0
	.int 0x44af1c2
	.quad 0 /* index: 1233 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1234 /* index: 1234 */
	.weak sys32_vserver; .quad sys32_vserver
	.reloc ., R_X86_64_SIZE32, sys32_vserver; .int 0
	.int 0x69af4d2
	.quad .Lname1235 /* index: 1235 */
	.weak task_alloc_synchronous_rpc; .quad task_alloc_synchronous_rpc
	.reloc ., R_X86_64_SIZE32, task_alloc_synchronous_rpc; .int 0
	.int 0x9aea623
	.quad .Lname1236 /* index: 1236 */
	.weak sys32_rt_sigtimedwait64; .quad sys32_rt_sigtimedwait64
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigtimedwait64; .int 0
	.int 0xc3064d4
	.quad .Lname1237 /* index: 1237 */
	.weak fpustate_savecpu; .quad fpustate_savecpu
	.reloc ., R_X86_64_SIZE32, fpustate_savecpu; .int 0
	.int 0x322c4d5
	.quad .Lname1238 /* index: 1238 */
	.weak sys32_writevf; .quad sys32_writevf
	.reloc ., R_X86_64_SIZE32, sys32_writevf; .int 0
	.int 0x596c4d6
	.quad 0 /* index: 1239 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1240 /* index: 1240 */
	.weak sys_epoll_wait; .quad sys_epoll_wait
	.reloc ., R_X86_64_SIZE32, sys_epoll_wait; .int 0
	.int 0x39316f4
	.quad .Lname1241 /* index: 1241 */
	.weak block_device_acquire_partlock_tryread; .quad block_device_acquire_partlock_tryread
	.reloc ., R_X86_64_SIZE32, block_device_acquire_partlock_tryread; .int 0
	.int 0xec0b624
	.quad 0 /* index: 1242 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1243 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1244 /* index: 1244 */
	.weak memendl; .quad memendl
	.reloc ., R_X86_64_SIZE32, memendl; .int 0
	.int 0x3c3c4dc
	.quad .Lname1245 /* index: 1245 */
	.weak sys32_signalfd; .quad sys32_signalfd
	.reloc ., R_X86_64_SIZE32, sys32_signalfd; .int 0
	.int 0xfc303e4
	.quad 0 /* index: 1246 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1247 /* index: 1247 */
	.weak error_print_into; .quad error_print_into
	.reloc ., R_X86_64_SIZE32, error_print_into; .int 0
	.int 0x32554df
	.quad 0 /* index: 1248 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1249 /* index: 1249 */
	.weak rwlock_reading_r; .quad rwlock_reading_r
	.reloc ., R_X86_64_SIZE32, rwlock_reading_r; .int 0
	.int 0x208bbe2
	.quad 0 /* index: 1250 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1251 /* index: 1251 */
	.weak task_start_default_flags; .quad task_start_default_flags
	.reloc ., R_X86_64_SIZE32, task_start_default_flags; .int 0
	.int 0xfe194e3
	.quad .Lname1252 /* index: 1252 */
	.weak rwlock_pollread; .quad rwlock_pollread
	.reloc ., R_X86_64_SIZE32, rwlock_pollread; .int 0
	.int 0x78904e4
	.quad 0 /* index: 1253 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1254 /* index: 1254 */
	.weak sys_wait4; .quad sys_wait4
	.reloc ., R_X86_64_SIZE32, sys_wait4; .int 0
	.int 0x96d1b74
	.quad .Lname1255 /* index: 1255 */
	.weak pidns_endwrite; .quad pidns_endwrite
	.reloc ., R_X86_64_SIZE32, pidns_endwrite; .int 0
	.int 0xb0b2245
	.quad 0 /* index: 1256 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1257 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1258 /* index: 1258 */
	.weak ramfs_dev_type; .quad ramfs_dev_type
	.reloc ., R_X86_64_SIZE32, ramfs_dev_type; .int 0
	.int 0x49b3245
	.quad 0 /* index: 1259 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1260 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1261 /* index: 1261 */
	.weak sys32_llistxattr; .quad sys32_llistxattr
	.reloc ., R_X86_64_SIZE32, sys32_llistxattr; .int 0
	.int 0xc3d28d2
	.quad .Lname1262 /* index: 1262 */
	.weak sys_getgroups; .quad sys_getgroups
	.reloc ., R_X86_64_SIZE32, sys_getgroups; .int 0
	.int 0x1e231c3
	.quad .Lname1263 /* index: 1263 */
	.weak vm_datapart_lock_endwrite; .quad vm_datapart_lock_endwrite
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_endwrite; .int 0
	.int 0xcbbd795
	.quad 0 /* index: 1264 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1265 /* index: 1265 */
	.weak unwind_cfa_calculate_cfa; .quad unwind_cfa_calculate_cfa
	.reloc ., R_X86_64_SIZE32, unwind_cfa_calculate_cfa; .int 0
	.int 0xe55d4f1
	.quad .Lname1266 /* index: 1266 */
	.weak handle_get_driver; .quad handle_get_driver
	.reloc ., R_X86_64_SIZE32, handle_get_driver; .int 0
	.int 0x76454f2
	.quad .Lname1267 /* index: 1267 */
	.weak handle_get_pidns; .quad handle_get_pidns
	.reloc ., R_X86_64_SIZE32, handle_get_pidns; .int 0
	.int 0x34b50d3
	.quad .Lname1268 /* index: 1268 */
	.weak path_mount; .quad path_mount
	.reloc ., R_X86_64_SIZE32, path_mount; .int 0
	.int 0xe6504f4
	.quad .Lname1269 /* index: 1269 */
	.weak kernel_uname; .quad kernel_uname
	.reloc ., R_X86_64_SIZE32, kernel_uname; .int 0
	.int 0x778d4f5
	.quad .Lname1270 /* index: 1270 */
	.weak sys32_getuid; .quad sys32_getuid
	.reloc ., R_X86_64_SIZE32, sys32_getuid; .int 0
	.int 0x26cdd74
	.quad 0 /* index: 1271 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1272 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1273 /* index: 1273 */
	.weak callback_list_detroy; .quad callback_list_detroy
	.reloc ., R_X86_64_SIZE32, callback_list_detroy; .int 0
	.int 0xcdd34f9
	.quad 0 /* index: 1274 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1275 /* index: 1275 */
	.weak vm_datapart_lock_upgrade; .quad vm_datapart_lock_upgrade
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_upgrade; .int 0
	.int 0x5eed3e5
	.quad 0 /* index: 1276 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1277 /* index: 1277 */
	.weak vpage_realloc; .quad vpage_realloc
	.reloc ., R_X86_64_SIZE32, vpage_realloc; .int 0
	.int 0x5d20a43
	.quad 0 /* index: 1278 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1279 /* index: 1279 */
	.weak vm_copytophys_onepage; .quad vm_copytophys_onepage
	.reloc ., R_X86_64_SIZE32, vm_copytophys_onepage; .int 0
	.int 0x78670d5
	.quad .Lname1280 /* index: 1280 */
	.weak cpu_apply_icpustate_rsp; .quad cpu_apply_icpustate_rsp
	.reloc ., R_X86_64_SIZE32, cpu_apply_icpustate_rsp; .int 0
	.int 0xf11e500
	.quad 0 /* index: 1281 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1282 /* index: 1282 */
	.weak sys32_getgid32; .quad sys32_getgid32
	.reloc ., R_X86_64_SIZE32, sys32_getgid32; .int 0
	.int 0xccb7502
	.quad 0 /* index: 1283 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1284 /* index: 1284 */
	.weak path_freelist; .quad path_freelist
	.reloc ., R_X86_64_SIZE32, path_freelist; .int 0
	.int 0xe32d504
	.quad .Lname1285 /* index: 1285 */
	.weak inode_write; .quad inode_write
	.reloc ., R_X86_64_SIZE32, inode_write; .int 0
	.int 0xb1ee505
	.quad 0 /* index: 1286 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1287 /* index: 1287 */
	.weak mempsetq; .quad mempsetq
	.reloc ., R_X86_64_SIZE32, mempsetq; .int 0
	.int 0xc479b81
	.quad .Lname1288 /* index: 1288 */
	.weak heap_alloc_untraced_nx; .quad heap_alloc_untraced_nx
	.reloc ., R_X86_64_SIZE32, heap_alloc_untraced_nx; .int 0
	.int 0x8a12508
	.quad 0 /* index: 1289 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1290 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1291 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1292 /* index: 1292 */
	.weak slab_kmalloc24; .quad slab_kmalloc24
	.reloc ., R_X86_64_SIZE32, slab_kmalloc24; .int 0
	.int 0x66b31c4
	.quad .Lname1293 /* index: 1293 */
	.weak sys_dup2; .quad sys_dup2
	.reloc ., R_X86_64_SIZE32, sys_dup2; .int 0
	.int 0x95bb82
	.quad 0 /* index: 1294 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1295 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1296 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1297 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1298 /* index: 1298 */
	.weak vm_write_nopf; .quad vm_write_nopf
	.reloc ., R_X86_64_SIZE32, vm_write_nopf; .int 0
	.int 0x7a4bf16
	.quad .Lname1299 /* index: 1299 */
	.weak vm_node_update_write_access; .quad vm_node_update_write_access
	.reloc ., R_X86_64_SIZE32, vm_node_update_write_access; .int 0
	.int 0x9a1c513
	.quad .Lname1300 /* index: 1300 */
	.weak sys_rt_sigtimedwait; .quad sys_rt_sigtimedwait
	.reloc ., R_X86_64_SIZE32, sys_rt_sigtimedwait; .int 0
	.int 0xe2d5514
	.quad .Lname1301 /* index: 1301 */
	.weak task_sethandlemanager; .quad task_sethandlemanager
	.reloc ., R_X86_64_SIZE32, task_sethandlemanager; .int 0
	.int 0x7162962
	.quad .Lname1302 /* index: 1302 */
	.weak format_vprintf; .quad format_vprintf
	.reloc ., R_X86_64_SIZE32, format_vprintf; .int 0
	.int 0xbeb7516
	.quad 0 /* index: 1303 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1304 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1305 /* index: 1305 */
	.weak sys32_connect; .quad sys32_connect
	.reloc ., R_X86_64_SIZE32, sys32_connect; .int 0
	.int 0x3632384
	.quad 0 /* index: 1306 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1307 /* index: 1307 */
	.weak vm_startdmav; .quad vm_startdmav
	.reloc ., R_X86_64_SIZE32, vm_startdmav; .int 0
	.int 0xf49d926
	.quad .Lname1308 /* index: 1308 */
	.weak driver_local_symbol; .quad driver_local_symbol
	.reloc ., R_X86_64_SIZE32, driver_local_symbol; .int 0
	.int 0x96b651c
	.quad 0 /* index: 1309 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1310 /* index: 1310 */
	.weak vm_datapart_do_read_phys; .quad vm_datapart_do_read_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_read_phys; .int 0
	.int 0xea4d593
	.quad .Lname1311 /* index: 1311 */
	.weak path_lock_write; .quad path_lock_write
	.reloc ., R_X86_64_SIZE32, path_lock_write; .int 0
	.int 0xb88f385
	.quad .Lname1312 /* index: 1312 */
	.weak x86_userexcept_unwind_interrupt_esp; .quad x86_userexcept_unwind_interrupt_esp
	.reloc ., R_X86_64_SIZE32, x86_userexcept_unwind_interrupt_esp; .int 0
	.int 0x3239520
	.quad 0 /* index: 1313 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1314 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1315 /* index: 1315 */
	.weak sys32_getcpu; .quad sys32_getcpu
	.reloc ., R_X86_64_SIZE32, sys32_getcpu; .int 0
	.int 0x26cccf5
	.quad .Lname1316 /* index: 1316 */
	.weak cred_require_vmread; .quad cred_require_vmread
	.reloc ., R_X86_64_SIZE32, cred_require_vmread; .int 0
	.int 0xd52524
	.quad .Lname1317 /* index: 1317 */
	.weak aio_noop_type; .quad aio_noop_type
	.reloc ., R_X86_64_SIZE32, aio_noop_type; .int 0
	.int 0xe63e525
	.quad .Lname1318 /* index: 1318 */
	.weak inode_pathconf; .quad inode_pathconf
	.reloc ., R_X86_64_SIZE32, inode_pathconf; .int 0
	.int 0xdf43526
	.quad 0 /* index: 1319 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1320 /* index: 1320 */
	.weak block_device_autopart_ex; .quad block_device_autopart_ex
	.reloc ., R_X86_64_SIZE32, block_device_autopart_ex; .int 0
	.int 0xcef0528
	.quad 0 /* index: 1321 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1322 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1323 /* index: 1323 */
	.weak memrendw; .quad memrendw
	.reloc ., R_X86_64_SIZE32, memrendw; .int 0
	.int 0xc48c387
	.quad .Lname1324 /* index: 1324 */
	.weak sys_tkill; .quad sys_tkill
	.reloc ., R_X86_64_SIZE32, sys_tkill; .int 0
	.int 0x96b652c
	.quad .Lname1325 /* index: 1325 */
	.weak setreg_irregs; .quad setreg_irregs
	.reloc ., R_X86_64_SIZE32, setreg_irregs; .int 0
	.int 0xdc20023
	.quad 0 /* index: 1326 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1327 /* index: 1327 */
	.weak sys_symlinkat; .quad sys_symlinkat
	.reloc ., R_X86_64_SIZE32, sys_symlinkat; .int 0
	.int 0x9273b14
	.quad .Lname1328 /* index: 1328 */
	.weak cpu_apply_scpustate_rsp; .quad cpu_apply_scpustate_rsp
	.reloc ., R_X86_64_SIZE32, cpu_apply_scpustate_rsp; .int 0
	.int 0x911e530
	.quad 0 /* index: 1329 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1330 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1331 /* index: 1331 */
	.weak fs_filesystems_delblocks; .quad fs_filesystems_delblocks
	.reloc ., R_X86_64_SIZE32, fs_filesystems_delblocks; .int 0
	.int 0x2f05533
	.quad .Lname1332 /* index: 1332 */
	.weak sys32_setfsuid; .quad sys32_setfsuid
	.reloc ., R_X86_64_SIZE32, sys32_setfsuid; .int 0
	.int 0xccb2ad4
	.quad .Lname1333 /* index: 1333 */
	.weak dbg_enter_kcpustate; .quad dbg_enter_kcpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_kcpustate; .int 0
	.int 0x781b535
	.quad .Lname1334 /* index: 1334 */
	.weak vm_mapresat; .quad vm_mapresat
	.reloc ., R_X86_64_SIZE32, vm_mapresat; .int 0
	.int 0x805ffb4
	.quad 0 /* index: 1335 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1336 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1337 /* index: 1337 */
	.weak sys32_chmod; .quad sys32_chmod
	.reloc ., R_X86_64_SIZE32, sys32_chmod; .int 0
	.int 0x822f634
	.quad .Lname1338 /* index: 1338 */
	.weak unwind_getreg_sfpustate_exclusive; .quad unwind_getreg_sfpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_sfpustate_exclusive; .int 0
	.int 0xbfe5065
	.quad .Lname1339 /* index: 1339 */
	.weak vm_getfree; .quad vm_getfree
	.reloc ., R_X86_64_SIZE32, vm_getfree; .int 0
	.int 0xdcd0be5
	.quad .Lname1340 /* index: 1340 */
	.weak sys32_userfaultfd; .quad sys32_userfaultfd
	.reloc ., R_X86_64_SIZE32, sys32_userfaultfd; .int 0
	.int 0x49da024
	.quad 0 /* index: 1341 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1342 /* index: 1342 */
	.weak vm_datapart_lock_end; .quad vm_datapart_lock_end
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_end; .int 0
	.int 0x5473c4
	.quad .Lname1343 /* index: 1343 */
	.weak devfs_lock_tryupgrade; .quad devfs_lock_tryupgrade
	.reloc ., R_X86_64_SIZE32, devfs_lock_tryupgrade; .int 0
	.int 0xa817635
	.quad .Lname1344 /* index: 1344 */
	.weak dbg_getregbynamep; .quad dbg_getregbynamep
	.reloc ., R_X86_64_SIZE32, dbg_getregbynamep; .int 0
	.int 0x4658540
	.quad 0 /* index: 1345 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1346 /* index: 1346 */
	.weak json_parser_enter; .quad json_parser_enter
	.reloc ., R_X86_64_SIZE32, json_parser_enter; .int 0
	.int 0x2436542
	.quad .Lname1347 /* index: 1347 */
	.weak sys32_utimes; .quad sys32_utimes
	.reloc ., R_X86_64_SIZE32, sys32_utimes; .int 0
	.int 0x17aa543
	.quad .Lname1348 /* index: 1348 */
	.weak character_device_stat; .quad character_device_stat
	.reloc ., R_X86_64_SIZE32, character_device_stat; .int 0
	.int 0x98ba544
	.quad .Lname1349 /* index: 1349 */
	.weak block_device_acquire_partlock_trywrite; .quad block_device_acquire_partlock_trywrite
	.reloc ., R_X86_64_SIZE32, block_device_acquire_partlock_trywrite; .int 0
	.int 0xc0d6545
	.quad .Lname1350 /* index: 1350 */
	.weak sys32_pwrite64f; .quad sys32_pwrite64f
	.reloc ., R_X86_64_SIZE32, sys32_pwrite64f; .int 0
	.int 0xf629546
	.quad .Lname1351 /* index: 1351 */
	.weak sys32_select; .quad sys32_select
	.reloc ., R_X86_64_SIZE32, sys32_select; .int 0
	.int 0x12c4d24
	.quad 0 /* index: 1352 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1353 /* index: 1353 */
	.weak sys_set_mempolicy; .quad sys_set_mempolicy
	.reloc ., R_X86_64_SIZE32, sys_set_mempolicy; .int 0
	.int 0xde74549
	.quad 0 /* index: 1354 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1355 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1356 /* index: 1356 */
	.weak sys32_acct; .quad sys32_acct
	.reloc ., R_X86_64_SIZE32, sys32_acct; .int 0
	.int 0x682c9c4
	.quad .Lname1357 /* index: 1357 */
	.weak keymap_openblob; .quad keymap_openblob
	.reloc ., R_X86_64_SIZE32, keymap_openblob; .int 0
	.int 0x69cc8e2
	.quad .Lname1358 /* index: 1358 */
	.weak vm_getfutex; .quad vm_getfutex
	.reloc ., R_X86_64_SIZE32, vm_getfutex; .int 0
	.int 0xcd0ff18
	.quad .Lname1359 /* index: 1359 */
	.weak validate_writablem; .quad validate_writablem
	.reloc ., R_X86_64_SIZE32, validate_writablem; .int 0
	.int 0xfc4d38d
	.quad .Lname1360 /* index: 1360 */
	.weak kernel_locked_heap; .quad kernel_locked_heap
	.reloc ., R_X86_64_SIZE32, kernel_locked_heap; .int 0
	.int 0xcda2550
	.quad .Lname1361 /* index: 1361 */
	.weak vm_datapart_allocram_nx; .quad vm_datapart_allocram_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_allocram_nx; .int 0
	.int 0x805c638
	.quad .Lname1362 /* index: 1362 */
	.weak sys_accept4; .quad sys_accept4
	.reloc ., R_X86_64_SIZE32, sys_accept4; .int 0
	.int 0x7e2ce24
	.quad .Lname1363 /* index: 1363 */
	.weak directory_entry_alloc; .quad directory_entry_alloc
	.reloc ., R_X86_64_SIZE32, directory_entry_alloc; .int 0
	.int 0xab6b553
	.quad .Lname1364 /* index: 1364 */
	.weak sys_utimensat; .quad sys_utimensat
	.reloc ., R_X86_64_SIZE32, sys_utimensat; .int 0
	.int 0x5333554
	.quad .Lname1365 /* index: 1365 */
	.weak keymap_codesize; .quad keymap_codesize
	.reloc ., R_X86_64_SIZE32, keymap_codesize; .int 0
	.int 0x594b555
	.quad 0 /* index: 1366 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1367 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1368 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1369 /* index: 1369 */
	.weak sys_get_mempolicy; .quad sys_get_mempolicy
	.reloc ., R_X86_64_SIZE32, sys_get_mempolicy; .int 0
	.int 0x9e74559
	.quad .Lname1370 /* index: 1370 */
	.weak vm_datablock_physical_type; .quad vm_datablock_physical_type
	.reloc ., R_X86_64_SIZE32, vm_datablock_physical_type; .int 0
	.int 0xea91135
	.quad 0 /* index: 1371 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1372 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1373 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1374 /* index: 1374 */
	.weak path_traversen; .quad path_traversen
	.reloc ., R_X86_64_SIZE32, path_traversen; .int 0
	.int 0x62f55e
	.quad .Lname1375 /* index: 1375 */
	.weak regdump_lcpustate; .quad regdump_lcpustate
	.reloc ., R_X86_64_SIZE32, regdump_lcpustate; .int 0
	.int 0xbf457b5
	.quad .Lname1376 /* index: 1376 */
	.weak unicode_readutf16_swap; .quad unicode_readutf16_swap
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_swap; .int 0
	.int 0x5a01560
	.quad 0 /* index: 1377 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1378 /* index: 1378 */
	.weak sys32_linux_fstat64; .quad sys32_linux_fstat64
	.reloc ., R_X86_64_SIZE32, sys32_linux_fstat64; .int 0
	.int 0x7a921f4
	.quad 0 /* index: 1379 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1380 /* index: 1380 */
	.weak mouse_device_init; .quad mouse_device_init
	.reloc ., R_X86_64_SIZE32, mouse_device_init; .int 0
	.int 0x29b6564
	.quad .Lname1381 /* index: 1381 */
	.weak sys32_timerfd_create; .quad sys32_timerfd_create
	.reloc ., R_X86_64_SIZE32, sys32_timerfd_create; .int 0
	.int 0x5f2b565
	.quad 0 /* index: 1382 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1383 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1384 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1385 /* index: 1385 */
	.weak pagedir_syncall; .quad pagedir_syncall
	.reloc ., R_X86_64_SIZE32, pagedir_syncall; .int 0
	.int 0x75fe63c
	.quad .Lname1386 /* index: 1386 */
	.weak vm_tasklock_trywrite; .quad vm_tasklock_trywrite
	.reloc ., R_X86_64_SIZE32, vm_tasklock_trywrite; .int 0
	.int 0xc3a29c5
	.quad 0 /* index: 1387 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1388 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1389 /* index: 1389 */
	.weak keyboard_device_putkey_nopr; .quad keyboard_device_putkey_nopr
	.reloc ., R_X86_64_SIZE32, keyboard_device_putkey_nopr; .int 0
	.int 0xdcccb92
	.quad 0 /* index: 1390 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1391 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1392 /* index: 1392 */
	.weak dbg_setregbynamep; .quad dbg_setregbynamep
	.reloc ., R_X86_64_SIZE32, dbg_setregbynamep; .int 0
	.int 0x658570
	.quad .Lname1393 /* index: 1393 */
	.weak vpage_alloc_nx; .quad vpage_alloc_nx
	.reloc ., R_X86_64_SIZE32, vpage_alloc_nx; .int 0
	.int 0x56848e8
	.quad 0 /* index: 1394 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1395 /* index: 1395 */
	.weak vm_datapart_writev_phys; .quad vm_datapart_writev_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_writev_phys; .int 0
	.int 0xe1d8393
	.quad .Lname1396 /* index: 1396 */
	.weak handle_print; .quad handle_print
	.reloc ., R_X86_64_SIZE32, handle_print; .int 0
	.int 0xd8fc574
	.quad 0 /* index: 1397 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1398 /* index: 1398 */
	.weak vm_syncone_locked; .quad vm_syncone_locked
	.reloc ., R_X86_64_SIZE32, vm_syncone_locked; .int 0
	.int 0x620f394
	.quad .Lname1399 /* index: 1399 */
	.weak validate_readable; .quad validate_readable
	.reloc ., R_X86_64_SIZE32, validate_readable; .int 0
	.int 0x18c4d55
	.quad 0 /* index: 1400 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1401 /* index: 1401 */
	.weak sys_eventfd; .quad sys_eventfd
	.reloc ., R_X86_64_SIZE32, sys_eventfd; .int 0
	.int 0xcb15394
	.quad 0 /* index: 1402 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1403 /* index: 1403 */
	.weak mouse_device_moveto; .quad mouse_device_moveto
	.reloc ., R_X86_64_SIZE32, mouse_device_moveto; .int 0
	.int 0xca6ae3f
	.quad .Lname1404 /* index: 1404 */
	.weak driver_symbol; .quad driver_symbol
	.reloc ., R_X86_64_SIZE32, driver_symbol; .int 0
	.int 0xd40f57c
	.quad 0 /* index: 1405 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1406 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1407 /* index: 1407 */
	.weak vm_clone; .quad vm_clone
	.reloc ., R_X86_64_SIZE32, vm_clone; .int 0
	.int 0x35a3395
	.quad 0 /* index: 1408 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1409 /* index: 1409 */
	.weak kfree; .quad kfree
	.reloc ., R_X86_64_SIZE32, kfree; .int 0
	.int 0x71d8b5
	.quad 0 /* index: 1410 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1411 /* index: 1411 */
	.weak fs_alloc; .quad fs_alloc
	.reloc ., R_X86_64_SIZE32, fs_alloc; .int 0
	.int 0x9583583
	.quad .Lname1412 /* index: 1412 */
	.weak devfs_lock_tryread; .quad devfs_lock_tryread
	.reloc ., R_X86_64_SIZE32, devfs_lock_tryread; .int 0
	.int 0xf19e584
	.quad .Lname1413 /* index: 1413 */
	.weak superblock_mountlock_tryservice; .quad superblock_mountlock_tryservice
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_tryservice; .int 0
	.int 0xefae585
	.quad .Lname1414 /* index: 1414 */
	.weak sys32_unshare; .quad sys32_unshare
	.reloc ., R_X86_64_SIZE32, sys32_unshare; .int 0
	.int 0x15f8095
	.quad 0 /* index: 1415 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1416 /* index: 1416 */
	.weak __cxa_end_catch; .quad __cxa_end_catch
	.reloc ., R_X86_64_SIZE32, __cxa_end_catch; .int 0
	.int 0x4beb588
	.quad 0 /* index: 1417 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1418 /* index: 1418 */
	.weak sys_msgsnd; .quad sys_msgsnd
	.reloc ., R_X86_64_SIZE32, sys_msgsnd; .int 0
	.int 0x64e5ad4
	.quad .Lname1419 /* index: 1419 */
	.weak x86_syscall32_lcall7; .quad x86_syscall32_lcall7
	.reloc ., R_X86_64_SIZE32, x86_syscall32_lcall7; .int 0
	.int 0x8ed4397
	.quad .Lname1420 /* index: 1420 */
	.weak sys_arch_prctl; .quad sys_arch_prctl
	.reloc ., R_X86_64_SIZE32, sys_arch_prctl; .int 0
	.int 0xef2058c
	.quad .Lname1421 /* index: 1421 */
	.weak ringbuffer_unread; .quad ringbuffer_unread
	.reloc ., R_X86_64_SIZE32, ringbuffer_unread; .int 0
	.int 0xf8043c4
	.quad 0 /* index: 1422 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1423 /* index: 1423 */
	.weak sys_rt_sigqueueinfo; .quad sys_rt_sigqueueinfo
	.reloc ., R_X86_64_SIZE32, sys_rt_sigqueueinfo; .int 0
	.int 0x12d858f
	.quad 0 /* index: 1424 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1425 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1426 /* index: 1426 */
	.weak vm_datapart_write_buffered; .quad vm_datapart_write_buffered
	.reloc ., R_X86_64_SIZE32, vm_datapart_write_buffered; .int 0
	.int 0x5155694
	.quad .Lname1427 /* index: 1427 */
	.weak sys32_move_pages; .quad sys32_move_pages
	.reloc ., R_X86_64_SIZE32, sys32_move_pages; .int 0
	.int 0xde5eb63
	.quad .Lname1428 /* index: 1428 */
	.weak acpi_sdt_count; .quad acpi_sdt_count
	.reloc ., R_X86_64_SIZE32, acpi_sdt_count; .int 0
	.int 0x4370594
	.quad .Lname1429 /* index: 1429 */
	.weak superblock_nodeslock_tryservice; .quad superblock_nodeslock_tryservice
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_tryservice; .int 0
	.int 0xfd31595
	.quad .Lname1430 /* index: 1430 */
	.weak sys_openpty; .quad sys_openpty
	.reloc ., R_X86_64_SIZE32, sys_openpty; .int 0
	.int 0x6115ed9
	.quad 0 /* index: 1431 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1432 /* index: 1432 */
	.weak vpage_realloc_untraced_nx; .quad vpage_realloc_untraced_nx
	.reloc ., R_X86_64_SIZE32, vpage_realloc_untraced_nx; .int 0
	.int 0x921d598
	.quad .Lname1433 /* index: 1433 */
	.weak sys32_timer_delete; .quad sys32_timer_delete
	.reloc ., R_X86_64_SIZE32, sys32_timer_delete; .int 0
	.int 0x48c77a5
	.quad 0 /* index: 1434 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1435 /* index: 1435 */
	.weak get_current_stack; .quad get_current_stack
	.reloc ., R_X86_64_SIZE32, get_current_stack; .int 0
	.int 0x4cee59b
	.quad 0 /* index: 1436 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1437 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1438 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1439 /* index: 1439 */
	.weak handle_manager_clone; .quad handle_manager_clone
	.reloc ., R_X86_64_SIZE32, handle_manager_clone; .int 0
	.int 0xd178645
	.quad 0 /* index: 1440 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1441 /* index: 1441 */
	.weak kernel_syscall1_iscp; .quad kernel_syscall1_iscp
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_iscp; .int 0
	.int 0x90958f0
	.quad .Lname1442 /* index: 1442 */
	.weak json_writer_putnumber; .quad json_writer_putnumber
	.reloc ., R_X86_64_SIZE32, json_writer_putnumber; .int 0
	.int 0x7dac5a2
	.quad .Lname1443 /* index: 1443 */
	.weak sys32_times; .quad sys32_times
	.reloc ., R_X86_64_SIZE32, sys32_times; .int 0
	.int 0x81205a3
	.quad .Lname1444 /* index: 1444 */
	.weak devfs_lock_endread; .quad devfs_lock_endread
	.reloc ., R_X86_64_SIZE32, devfs_lock_endread; .int 0
	.int 0xd2e5a4
	.quad .Lname1445 /* index: 1445 */
	.weak cred_require_vmwrite; .quad cred_require_vmwrite
	.reloc ., R_X86_64_SIZE32, cred_require_vmwrite; .int 0
	.int 0xd5475a5
	.quad .Lname1446 /* index: 1446 */
	.weak sys_writevf; .quad sys_writevf
	.reloc ., R_X86_64_SIZE32, sys_writevf; .int 0
	.int 0xf0ba5a6
	.quad .Lname1447 /* index: 1447 */
	.weak sys32_recvmmsg; .quad sys32_recvmmsg
	.reloc ., R_X86_64_SIZE32, sys32_recvmmsg; .int 0
	.int 0xbcbc5a7
	.quad .Lname1448 /* index: 1448 */
	.weak path_traverse_ex; .quad path_traverse_ex
	.reloc ., R_X86_64_SIZE32, path_traverse_ex; .int 0
	.int 0x2f555a8
	.quad .Lname1449 /* index: 1449 */
	.weak mempsetl; .quad mempsetl
	.reloc ., R_X86_64_SIZE32, mempsetl; .int 0
	.int 0xc479b9c
	.quad .Lname1450 /* index: 1450 */
	.weak task_exit; .quad task_exit
	.reloc ., R_X86_64_SIZE32, task_exit; .int 0
	.int 0xa15b584
	.quad .Lname1451 /* index: 1451 */
	.weak printk; .quad printk
	.reloc ., R_X86_64_SIZE32, printk; .int 0
	.int 0x77905ab
	.quad 0 /* index: 1452 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1453 /* index: 1453 */
	.weak validate_readablem; .quad validate_readablem
	.reloc ., R_X86_64_SIZE32, validate_readablem; .int 0
	.int 0x8c4d5ad
	.quad .Lname1454 /* index: 1454 */
	.weak sys_mount; .quad sys_mount
	.reloc ., R_X86_64_SIZE32, sys_mount; .int 0
	.int 0x9641154
	.quad 0 /* index: 1455 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1456 /* index: 1456 */
	.weak vm_datapart_map_ram_p; .quad vm_datapart_map_ram_p
	.reloc ., R_X86_64_SIZE32, vm_datapart_map_ram_p; .int 0
	.int 0x95af5b0
	.quad .Lname1457 /* index: 1457 */
	.weak vm_writephysq_unaligned; .quad vm_writephysq_unaligned
	.reloc ., R_X86_64_SIZE32, vm_writephysq_unaligned; .int 0
	.int 0xffd58d4
	.quad .Lname1458 /* index: 1458 */
	.weak pci_writeaddr; .quad pci_writeaddr
	.reloc ., R_X86_64_SIZE32, pci_writeaddr; .int 0
	.int 0x63415b2
	.quad .Lname1459 /* index: 1459 */
	.weak vm_datapart_destroy; .quad vm_datapart_destroy
	.reloc ., R_X86_64_SIZE32, vm_datapart_destroy; .int 0
	.int 0xf978be9
	.quad .Lname1460 /* index: 1460 */
	.weak ansitty_init; .quad ansitty_init
	.reloc ., R_X86_64_SIZE32, ansitty_init; .int 0
	.int 0xd7065b4
	.quad .Lname1461 /* index: 1461 */
	.weak getreg_kcpustate; .quad getreg_kcpustate
	.reloc ., R_X86_64_SIZE32, getreg_kcpustate; .int 0
	.int 0xf7135b5
	.quad 0 /* index: 1462 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1463 /* index: 1463 */
	.weak sys32_sendmmsg; .quad sys32_sendmmsg
	.reloc ., R_X86_64_SIZE32, sys32_sendmmsg; .int 0
	.int 0xc2dc5b7
	.quad .Lname1464 /* index: 1464 */
	.weak x86_sysroute1_asm32_sysenter; .quad x86_sysroute1_asm32_sysenter
	.reloc ., R_X86_64_SIZE32, x86_sysroute1_asm32_sysenter; .int 0
	.int 0x4825d52
	.quad .Lname1465 /* index: 1465 */
	.weak handle_get_directory_entry; .quad handle_get_directory_entry
	.reloc ., R_X86_64_SIZE32, handle_get_directory_entry; .int 0
	.int 0x463b5b9
	.quad .Lname1466 /* index: 1466 */
	.weak x86_idt_modify_end; .quad x86_idt_modify_end
	.reloc ., R_X86_64_SIZE32, x86_idt_modify_end; .int 0
	.int 0x39f5c14
	.quad .Lname1467 /* index: 1467 */
	.weak sys32_removexattr; .quad sys32_removexattr
	.reloc ., R_X86_64_SIZE32, sys32_removexattr; .int 0
	.int 0x4dd4db2
	.quad .Lname1468 /* index: 1468 */
	.weak sys32_mlockall; .quad sys32_mlockall
	.reloc ., R_X86_64_SIZE32, sys32_mlockall; .int 0
	.int 0x34095bc
	.quad .Lname1469 /* index: 1469 */
	.weak vm_datapart_write; .quad vm_datapart_write
	.reloc ., R_X86_64_SIZE32, vm_datapart_write; .int 0
	.int 0x2bbed95
	.quad 0 /* index: 1470 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1471 /* index: 1471 */
	.weak kernel_panic_lcpustate; .quad kernel_panic_lcpustate
	.reloc ., R_X86_64_SIZE32, kernel_panic_lcpustate; .int 0
	.int 0x78a90f5
	.quad 0 /* index: 1472 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1473 /* index: 1473 */
	.weak x86_dbgidt; .quad x86_dbgidt
	.reloc ., R_X86_64_SIZE32, x86_dbgidt; .int 0
	.int 0x5af6474
	.quad .Lname1474 /* index: 1474 */
	.weak mouse_buffer_putpacket_nopr; .quad mouse_buffer_putpacket_nopr
	.reloc ., R_X86_64_SIZE32, mouse_buffer_putpacket_nopr; .int 0
	.int 0x8565c2
	.quad .Lname1475 /* index: 1475 */
	.weak sys_setgroups; .quad sys_setgroups
	.reloc ., R_X86_64_SIZE32, sys_setgroups; .int 0
	.int 0x1e205c3
	.quad .Lname1476 /* index: 1476 */
	.weak sys32_sigsuspend; .quad sys32_sigsuspend
	.reloc ., R_X86_64_SIZE32, sys32_sigsuspend; .int 0
	.int 0xc4b45c4
	.quad .Lname1477 /* index: 1477 */
	.weak pagedir_unmapone; .quad pagedir_unmapone
	.reloc ., R_X86_64_SIZE32, pagedir_unmapone; .int 0
	.int 0x8f55c5
	.quad 0 /* index: 1478 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1479 /* index: 1479 */
	.weak unwind_fde_find; .quad unwind_fde_find
	.reloc ., R_X86_64_SIZE32, unwind_fde_find; .int 0
	.int 0x4b137d4
	.quad 0 /* index: 1480 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1481 /* index: 1481 */
	.weak sys32_poll; .quad sys32_poll
	.reloc ., R_X86_64_SIZE32, sys32_poll; .int 0
	.int 0x681e64c
	.quad 0 /* index: 1482 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1483 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1484 /* index: 1484 */
	.weak sys32_mlock; .quad sys32_mlock
	.reloc ., R_X86_64_SIZE32, sys32_mlock; .int 0
	.int 0x83933fb
	.quad .Lname1485 /* index: 1485 */
	.weak sys32_setfsuid32; .quad sys32_setfsuid32
	.reloc ., R_X86_64_SIZE32, sys32_setfsuid32; .int 0
	.int 0xb2adba2
	.quad 0 /* index: 1486 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1487 /* index: 1487 */
	.weak unwind_setreg_lcpustate_exclusive; .quad unwind_setreg_lcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_lcpustate_exclusive; .int 0
	.int 0x28e5125
	.quad 0 /* index: 1488 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1489 /* index: 1489 */
	.weak unicode_16to8; .quad unicode_16to8
	.reloc ., R_X86_64_SIZE32, unicode_16to8; .int 0
	.int 0x76b80f8
	.quad .Lname1490 /* index: 1490 */
	.weak inode_recent_tryclear; .quad inode_recent_tryclear
	.reloc ., R_X86_64_SIZE32, inode_recent_tryclear; .int 0
	.int 0x5d8b5d2
	.quad .Lname1491 /* index: 1491 */
	.weak debug_dllocksections; .quad debug_dllocksections
	.reloc ., R_X86_64_SIZE32, debug_dllocksections; .int 0
	.int 0x164b5d3
	.quad .Lname1492 /* index: 1492 */
	.weak sys32_getegid; .quad sys32_getegid
	.reloc ., R_X86_64_SIZE32, sys32_getegid; .int 0
	.int 0x6ccd5d4
	.quad .Lname1493 /* index: 1493 */
	.weak driver_delmod_inode; .quad driver_delmod_inode
	.reloc ., R_X86_64_SIZE32, driver_delmod_inode; .int 0
	.int 0x86355d5
	.quad .Lname1494 /* index: 1494 */
	.weak format_scanf; .quad format_scanf
	.reloc ., R_X86_64_SIZE32, format_scanf; .int 0
	.int 0xbf05d6
	.quad .Lname1495 /* index: 1495 */
	.weak sys32_syslog; .quad sys32_syslog
	.reloc ., R_X86_64_SIZE32, sys32_syslog; .int 0
	.int 0x12105d7
	.quad .Lname1496 /* index: 1496 */
	.weak pidns_write_nx; .quad pidns_write_nx
	.reloc ., R_X86_64_SIZE32, pidns_write_nx; .int 0
	.int 0x8bf45d8
	.quad .Lname1497 /* index: 1497 */
	.weak path_lock_tryservice; .quad path_lock_tryservice
	.reloc ., R_X86_64_SIZE32, path_lock_tryservice; .int 0
	.int 0xb712fa5
	.quad .Lname1498 /* index: 1498 */
	.weak unicode_readutf16_rev_n; .quad unicode_readutf16_rev_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_rev_n; .int 0
	.int 0xa03460e
	.quad .Lname1499 /* index: 1499 */
	.weak vprintk; .quad vprintk
	.reloc ., R_X86_64_SIZE32, vprintk; .int 0
	.int 0xd7905db
	.quad .Lname1500 /* index: 1500 */
	.weak vm_datablock_physical; .quad vm_datablock_physical
	.reloc ., R_X86_64_SIZE32, vm_datablock_physical; .int 0
	.int 0x8fb15dc
	.quad .Lname1501 /* index: 1501 */
	.weak swap_write; .quad swap_write
	.reloc ., R_X86_64_SIZE32, swap_write; .int 0
	.int 0x6693d25
	.quad 0 /* index: 1502 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1503 /* index: 1503 */
	.weak sys32_timer_create; .quad sys32_timer_create
	.reloc ., R_X86_64_SIZE32, sys32_timer_create; .int 0
	.int 0x488e3a5
	.quad .Lname1504 /* index: 1504 */
	.weak sys_clock_nanosleep; .quad sys_clock_nanosleep
	.reloc ., R_X86_64_SIZE32, sys_clock_nanosleep; .int 0
	.int 0xbc435e0
	.quad 0 /* index: 1505 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1506 /* index: 1506 */
	.weak block_device_aread_phys_sector; .quad block_device_aread_phys_sector
	.reloc ., R_X86_64_SIZE32, block_device_aread_phys_sector; .int 0
	.int 0x29a55e2
	.quad 0 /* index: 1507 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1508 /* index: 1508 */
	.weak path_traverse_at; .quad path_traverse_at
	.reloc ., R_X86_64_SIZE32, path_traverse_at; .int 0
	.int 0x2f555e4
	.quad .Lname1509 /* index: 1509 */
	.weak task_tryyield; .quad task_tryyield
	.reloc ., R_X86_64_SIZE32, task_tryyield; .int 0
	.int 0x485eee4
	.quad 0 /* index: 1510 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1511 /* index: 1511 */
	.weak unwind_fde_load; .quad unwind_fde_load
	.reloc ., R_X86_64_SIZE32, unwind_fde_load; .int 0
	.int 0x4b2ece4
	.quad .Lname1512 /* index: 1512 */
	.weak sys_readlinkat; .quad sys_readlinkat
	.reloc ., R_X86_64_SIZE32, sys_readlinkat; .int 0
	.int 0xbbadd44
	.quad .Lname1513 /* index: 1513 */
	.weak directory_getentry; .quad directory_getentry
	.reloc ., R_X86_64_SIZE32, directory_getentry; .int 0
	.int 0x17325e9
	.quad .Lname1514 /* index: 1514 */
	.weak sys_uselib; .quad sys_uselib
	.reloc ., R_X86_64_SIZE32, sys_uselib; .int 0
	.int 0x6ce1262
	.quad .Lname1515 /* index: 1515 */
	.weak vm_datapart_lock_upgrade_nx; .quad vm_datapart_lock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_upgrade_nx; .int 0
	.int 0xd3f0cb8
	.quad 0 /* index: 1516 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1517 /* index: 1517 */
	.weak sys_fsetxattr; .quad sys_fsetxattr
	.reloc ., R_X86_64_SIZE32, sys_fsetxattr; .int 0
	.int 0x7b7d652
	.quad .Lname1518 /* index: 1518 */
	.weak sys_gettimeofday; .quad sys_gettimeofday
	.reloc ., R_X86_64_SIZE32, sys_gettimeofday; .int 0
	.int 0x67ec0f9
	.quad 0 /* index: 1519 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1520 /* index: 1520 */
	.weak vm_datablock_locatepart_exact; .quad vm_datablock_locatepart_exact
	.reloc ., R_X86_64_SIZE32, vm_datablock_locatepart_exact; .int 0
	.int 0x4007254
	.quad 0 /* index: 1521 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1522 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1523 /* index: 1523 */
	.weak cpu_broadcastipi_notthis; .quad cpu_broadcastipi_notthis
	.reloc ., R_X86_64_SIZE32, cpu_broadcastipi_notthis; .int 0
	.int 0x20bde53
	.quad .Lname1524 /* index: 1524 */
	.weak sys_signalfd4; .quad sys_signalfd4
	.reloc ., R_X86_64_SIZE32, sys_signalfd4; .int 0
	.int 0x74f45f4
	.quad .Lname1525 /* index: 1525 */
	.weak mall_untrace; .quad mall_untrace
	.reloc ., R_X86_64_SIZE32, mall_untrace; .int 0
	.int 0xd63b5f5
	.quad .Lname1526 /* index: 1526 */
	.weak syscall_emulate32; .quad syscall_emulate32
	.reloc ., R_X86_64_SIZE32, syscall_emulate32; .int 0
	.int 0x443fbb2
	.quad .Lname1527 /* index: 1527 */
	.weak debuginfo_cu_parser_getstring; .quad debuginfo_cu_parser_getstring
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getstring; .int 0
	.int 0x54b35f7
	.quad .Lname1528 /* index: 1528 */
	.weak superblock_nodeslock_read_nx; .quad superblock_nodeslock_read_nx
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_read_nx; .int 0
	.int 0xeb805f8
	.quad .Lname1529 /* index: 1529 */
	.weak pagedir_fini; .quad pagedir_fini
	.reloc ., R_X86_64_SIZE32, pagedir_fini; .int 0
	.int 0x72215f9
	.quad 0 /* index: 1530 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1531 /* index: 1531 */
	.weak sys32_lock; .quad sys32_lock
	.reloc ., R_X86_64_SIZE32, sys32_lock; .int 0
	.int 0x683a5fb
	.quad .Lname1532 /* index: 1532 */
	.weak x86_idt_syscall; .quad x86_idt_syscall
	.reloc ., R_X86_64_SIZE32, x86_idt_syscall; .int 0
	.int 0x75655fc
	.quad .Lname1533 /* index: 1533 */
	.weak dbg_enter_ucpustate_cr; .quad dbg_enter_ucpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_ucpustate_cr; .int 0
	.int 0x9f3edb2
	.quad .Lname1534 /* index: 1534 */
	.weak sys_removexattr; .quad sys_removexattr
	.reloc ., R_X86_64_SIZE32, sys_removexattr; .int 0
	.int 0x5a652d2
	.quad .Lname1535 /* index: 1535 */
	.weak vm_datapart_loadpage; .quad vm_datapart_loadpage
	.reloc ., R_X86_64_SIZE32, vm_datapart_loadpage; .int 0
	.int 0xa84e55
	.quad .Lname1536 /* index: 1536 */
	.weak path_umount; .quad path_umount
	.reloc ., R_X86_64_SIZE32, path_umount; .int 0
	.int 0x6d6e2b4
	.quad .Lname1537 /* index: 1537 */
	.weak kernel_panic; .quad kernel_panic
	.reloc ., R_X86_64_SIZE32, kernel_panic; .int 0
	.int 0x77af033
	.quad 0 /* index: 1538 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1539 /* index: 1539 */
	.weak this_exception_pointers; .quad this_exception_pointers
	.reloc ., R_X86_64_SIZE32, this_exception_pointers; .int 0
	.int 0xab7c603
	.quad .Lname1540 /* index: 1540 */
	.weak pidns_trylookup_task_locked; .quad pidns_trylookup_task_locked
	.reloc ., R_X86_64_SIZE32, pidns_trylookup_task_locked; .int 0
	.int 0x5d25604
	.quad .Lname1541 /* index: 1541 */
	.weak heap_free; .quad heap_free
	.reloc ., R_X86_64_SIZE32, heap_free; .int 0
	.int 0x865b605
	.quad .Lname1542 /* index: 1542 */
	.weak sys32_hopf; .quad sys32_hopf
	.reloc ., R_X86_64_SIZE32, sys32_hopf; .int 0
	.int 0x6826606
	.quad 0 /* index: 1543 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1544 /* index: 1544 */
	.weak mouse_device_button_ex; .quad mouse_device_button_ex
	.reloc ., R_X86_64_SIZE32, mouse_device_button_ex; .int 0
	.int 0xd9d9608
	.quad .Lname1545 /* index: 1545 */
	.weak sys32_gettimeofday; .quad sys32_gettimeofday
	.reloc ., R_X86_64_SIZE32, sys32_gettimeofday; .int 0
	.int 0x1e91609
	.quad .Lname1546 /* index: 1546 */
	.weak vm_kernel_treelock_end; .quad vm_kernel_treelock_end
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_end; .int 0
	.int 0x30979f4
	.quad .Lname1547 /* index: 1547 */
	.weak sys_linux_fstatat; .quad sys_linux_fstatat
	.reloc ., R_X86_64_SIZE32, sys_linux_fstatat; .int 0
	.int 0xf344fb4
	.quad .Lname1548 /* index: 1548 */
	.weak sys32_iopl; .quad sys32_iopl
	.reloc ., R_X86_64_SIZE32, sys32_iopl; .int 0
	.int 0x682560c
	.quad .Lname1549 /* index: 1549 */
	.weak sys32_setitimer; .quad sys32_setitimer
	.reloc ., R_X86_64_SIZE32, sys32_setitimer; .int 0
	.int 0xd62f102
	.quad .Lname1550 /* index: 1550 */
	.weak sys32_uname; .quad sys32_uname
	.reloc ., R_X86_64_SIZE32, sys32_uname; .int 0
	.int 0x8114255
	.quad .Lname1551 /* index: 1551 */
	.weak vio_copyfromvio; .quad vio_copyfromvio
	.reloc ., R_X86_64_SIZE32, vio_copyfromvio; .int 0
	.int 0x8f0560f
	.quad .Lname1552 /* index: 1552 */
	.weak vm_datablock_locatepart; .quad vm_datablock_locatepart
	.reloc ., R_X86_64_SIZE32, vm_datablock_locatepart; .int 0
	.int 0xa5c95f4
	.quad 0 /* index: 1553 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1554 /* index: 1554 */
	.weak block_device_unregister; .quad block_device_unregister
	.reloc ., R_X86_64_SIZE32, block_device_unregister; .int 0
	.int 0x385f612
	.quad .Lname1555 /* index: 1555 */
	.weak inode_access; .quad inode_access
	.reloc ., R_X86_64_SIZE32, inode_access; .int 0
	.int 0x27cc613
	.quad .Lname1556 /* index: 1556 */
	.weak sys32_wait4; .quad sys32_wait4
	.reloc ., R_X86_64_SIZE32, sys32_wait4; .int 0
	.int 0x8168614
	.quad .Lname1557 /* index: 1557 */
	.weak syscall_printtrace; .quad syscall_printtrace
	.reloc ., R_X86_64_SIZE32, syscall_printtrace; .int 0
	.int 0x30d6615
	.quad .Lname1558 /* index: 1558 */
	.weak sys_setreuid; .quad sys_setreuid
	.reloc ., R_X86_64_SIZE32, sys_setreuid; .int 0
	.int 0xb085d64
	.quad .Lname1559 /* index: 1559 */
	.weak rwlock_reading_any; .quad rwlock_reading_any
	.reloc ., R_X86_64_SIZE32, rwlock_reading_any; .int 0
	.int 0x8bbd659
	.quad .Lname1560 /* index: 1560 */
	.weak validate_writablem_opt; .quad validate_writablem_opt
	.reloc ., R_X86_64_SIZE32, validate_writablem_opt; .int 0
	.int 0x39ea2a4
	.quad .Lname1561 /* index: 1561 */
	.weak krealign_offset; .quad krealign_offset
	.reloc ., R_X86_64_SIZE32, krealign_offset; .int 0
	.int 0xfde4904
	.quad 0 /* index: 1562 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1563 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1564 /* index: 1564 */
	.weak vm86_sw_intr; .quad vm86_sw_intr
	.reloc ., R_X86_64_SIZE32, vm86_sw_intr; .int 0
	.int 0xd2559d2
	.quad 0 /* index: 1565 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1566 /* index: 1566 */
	.weak x86_fpustate_init; .quad x86_fpustate_init
	.reloc ., R_X86_64_SIZE32, x86_fpustate_init; .int 0
	.int 0x7b2f3d4
	.quad .Lname1567 /* index: 1567 */
	.weak sys32_fstatfs64; .quad sys32_fstatfs64
	.reloc ., R_X86_64_SIZE32, sys32_fstatfs64; .int 0
	.int 0xce2f034
	.quad .Lname1568 /* index: 1568 */
	.weak sys32_eventfd; .quad sys32_eventfd
	.reloc ., R_X86_64_SIZE32, sys32_eventfd; .int 0
	.int 0x7ce32e4
	.quad 0 /* index: 1569 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1570 /* index: 1570 */
	.weak block_device_aread_sector; .quad block_device_aread_sector
	.reloc ., R_X86_64_SIZE32, block_device_aread_sector; .int 0
	.int 0xea4622
	.quad .Lname1571 /* index: 1571 */
	.weak driver_clear_fde_caches; .quad driver_clear_fde_caches
	.reloc ., R_X86_64_SIZE32, driver_clear_fde_caches; .int 0
	.int 0x1fc4623
	.quad .Lname1572 /* index: 1572 */
	.weak _strtoui64; .quad _strtoui64
	.reloc ., R_X86_64_SIZE32, _strtoui64; .int 0
	.int 0x9b0d624
	.quad .Lname1573 /* index: 1573 */
	.weak sys_process_vm_writev; .quad sys_process_vm_writev
	.reloc ., R_X86_64_SIZE32, sys_process_vm_writev; .int 0
	.int 0x32a6906
	.quad 0 /* index: 1574 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1575 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1576 /* index: 1576 */
	.weak unwind_getreg_xfpustate; .quad unwind_getreg_xfpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_xfpustate; .int 0
	.int 0xb8c44c5
	.quad .Lname1577 /* index: 1577 */
	.weak sys_security; .quad sys_security
	.reloc ., R_X86_64_SIZE32, sys_security; .int 0
	.int 0xc1c2629
	.quad .Lname1578 /* index: 1578 */
	.weak sys_syncfs; .quad sys_syncfs
	.reloc ., R_X86_64_SIZE32, sys_syncfs; .int 0
	.int 0x6a9f943
	.quad 0 /* index: 1579 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1580 /* index: 1580 */
	.weak task_yield; .quad task_yield
	.reloc ., R_X86_64_SIZE32, task_yield; .int 0
	.int 0x1685484
	.quad .Lname1581 /* index: 1581 */
	.weak kernel_syscall0_iscp32; .quad kernel_syscall0_iscp32
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_iscp32; .int 0
	.int 0x958fbb2
	.quad .Lname1582 /* index: 1582 */
	.weak sys32_mremap; .quad sys32_mremap
	.reloc ., R_X86_64_SIZE32, sys32_mremap; .int 0
	.int 0x3f8e500
	.quad 0 /* index: 1583 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1584 /* index: 1584 */
	.weak sys32_getdents64; .quad sys32_getdents64
	.reloc ., R_X86_64_SIZE32, sys32_getdents64; .int 0
	.int 0xc47da54
	.quad .Lname1585 /* index: 1585 */
	.weak sys32_inotify_rm_watch; .quad sys32_inotify_rm_watch
	.reloc ., R_X86_64_SIZE32, sys32_inotify_rm_watch; .int 0
	.int 0xf124908
	.quad .Lname1586 /* index: 1586 */
	.weak superblock_nodeslock_downgrade; .quad superblock_nodeslock_downgrade
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_downgrade; .int 0
	.int 0xe2f1ac5
	.quad .Lname1587 /* index: 1587 */
	.weak driver_at_address; .quad driver_at_address
	.reloc ., R_X86_64_SIZE32, driver_at_address; .int 0
	.int 0xb859633
	.quad .Lname1588 /* index: 1588 */
	.weak pagedir_unsetchanged; .quad pagedir_unsetchanged
	.reloc ., R_X86_64_SIZE32, pagedir_unsetchanged; .int 0
	.int 0x89a6634
	.quad .Lname1589 /* index: 1589 */
	.weak dbg_enter_lcpustate; .quad dbg_enter_lcpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_lcpustate; .int 0
	.int 0x781b635
	.quad 0 /* index: 1590 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1591 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1592 /* index: 1592 */
	.weak dbg_fillbox; .quad dbg_fillbox
	.reloc ., R_X86_64_SIZE32, dbg_fillbox; .int 0
	.int 0xca9a638
	.quad .Lname1593 /* index: 1593 */
	.weak sys_readahead; .quad sys_readahead
	.reloc ., R_X86_64_SIZE32, sys_readahead; .int 0
	.int 0xcae83b4
	.quad 0 /* index: 1594 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1595 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1596 /* index: 1596 */
	.weak character_device_ioctl; .quad character_device_ioctl
	.reloc ., R_X86_64_SIZE32, character_device_ioctl; .int 0
	.int 0x890a63c
	.quad .Lname1597 /* index: 1597 */
	.weak sys_delete_module; .quad sys_delete_module
	.reloc ., R_X86_64_SIZE32, sys_delete_module; .int 0
	.int 0xfc8035
	.quad 0 /* index: 1598 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1599 /* index: 1599 */
	.weak kernel_terminal_raise; .quad kernel_terminal_raise
	.reloc ., R_X86_64_SIZE32, kernel_terminal_raise; .int 0
	.int 0x5b7f3b5
	.quad 0 /* index: 1600 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1601 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1602 /* index: 1602 */
	.weak sys32_setgid32; .quad sys32_setgid32
	.reloc ., R_X86_64_SIZE32, sys32_setgid32; .int 0
	.int 0xccb7642
	.quad 0 /* index: 1603 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1604 /* index: 1604 */
	.weak sys_getresuid; .quad sys_getresuid
	.reloc ., R_X86_64_SIZE32, sys_getresuid; .int 0
	.int 0x85f644
	.quad .Lname1605 /* index: 1605 */
	.weak error_active; .quad error_active
	.reloc ., R_X86_64_SIZE32, error_active; .int 0
	.int 0x3b34645
	.quad .Lname1606 /* index: 1606 */
	.weak vm_enumdmav; .quad vm_enumdmav
	.reloc ., R_X86_64_SIZE32, vm_enumdmav; .int 0
	.int 0x5dea646
	.quad .Lname1607 /* index: 1607 */
	.weak rawmemrlenq; .quad rawmemrlenq
	.reloc ., R_X86_64_SIZE32, rawmemrlenq; .int 0
	.int 0xc31a661
	.quad .Lname1608 /* index: 1608 */
	.weak json_writer_endobject; .quad json_writer_endobject
	.reloc ., R_X86_64_SIZE32, json_writer_endobject; .int 0
	.int 0x7dbc944
	.quad 0 /* index: 1609 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1610 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1611 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1612 /* index: 1612 */
	.weak mouse_device_poll; .quad mouse_device_poll
	.reloc ., R_X86_64_SIZE32, mouse_device_poll; .int 0
	.int 0x298d64c
	.quad .Lname1613 /* index: 1613 */
	.weak heap_trim; .quad heap_trim
	.reloc ., R_X86_64_SIZE32, heap_trim; .int 0
	.int 0x866d64d
	.quad .Lname1614 /* index: 1614 */
	.weak sys32_utime; .quad sys32_utime
	.reloc ., R_X86_64_SIZE32, sys32_utime; .int 0
	.int 0x817aa55
	.quad 0 /* index: 1615 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1616 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1617 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1618 /* index: 1618 */
	.weak driver_insmod_blob; .quad driver_insmod_blob
	.reloc ., R_X86_64_SIZE32, driver_insmod_blob; .int 0
	.int 0x782e652
	.quad .Lname1619 /* index: 1619 */
	.weak sys_remap_file_pages; .quad sys_remap_file_pages
	.reloc ., R_X86_64_SIZE32, sys_remap_file_pages; .int 0
	.int 0x3b53e63
	.quad 0 /* index: 1620 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1621 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1622 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1623 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1624 /* index: 1624 */
	.weak sys32_pselect6_64; .quad sys32_pselect6_64
	.reloc ., R_X86_64_SIZE32, sys32_pselect6_64; .int 0
	.int 0x3bb3cd4
	.quad .Lname1625 /* index: 1625 */
	.weak pagedir_maphint; .quad pagedir_maphint
	.reloc ., R_X86_64_SIZE32, pagedir_maphint; .int 0
	.int 0xe3d9e64
	.quad .Lname1626 /* index: 1626 */
	.weak vmb_overlay; .quad vmb_overlay
	.reloc ., R_X86_64_SIZE32, vmb_overlay; .int 0
	.int 0x6b1cae9
	.quad 0 /* index: 1627 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1628 /* index: 1628 */
	.weak terminal_owrite; .quad terminal_owrite
	.reloc ., R_X86_64_SIZE32, terminal_owrite; .int 0
	.int 0xd2ece45
	.quad .Lname1629 /* index: 1629 */
	.weak vio_cmpxch_or_writeq; .quad vio_cmpxch_or_writeq
	.reloc ., R_X86_64_SIZE32, vio_cmpxch_or_writeq; .int 0
	.int 0x8230f21
	.quad 0 /* index: 1630 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1631 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1632 /* index: 1632 */
	.weak sys32_hop; .quad sys32_hop
	.reloc ., R_X86_64_SIZE32, sys32_hop; .int 0
	.int 0x6682660
	.quad .Lname1633 /* index: 1633 */
	.weak handle_trylookup; .quad handle_trylookup
	.reloc ., R_X86_64_SIZE32, handle_trylookup; .int 0
	.int 0x519e110
	.quad .Lname1634 /* index: 1634 */
	.weak sys_lfutexlockexpr; .quad sys_lfutexlockexpr
	.reloc ., R_X86_64_SIZE32, sys_lfutexlockexpr; .int 0
	.int 0xffb9662
	.quad 0 /* index: 1635 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1636 /* index: 1636 */
	.weak cpu_quantum_end; .quad cpu_quantum_end
	.reloc ., R_X86_64_SIZE32, cpu_quantum_end; .int 0
	.int 0xeb8664
	.quad 0 /* index: 1637 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1638 /* index: 1638 */
	.weak dbg_enter_lcpustate_r; .quad dbg_enter_lcpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_lcpustate_r; .int 0
	.int 0x1b63ee2
	.quad .Lname1639 /* index: 1639 */
	.weak rawmemrlenw; .quad rawmemrlenw
	.reloc ., R_X86_64_SIZE32, rawmemrlenw; .int 0
	.int 0xc31a667
	.quad 0 /* index: 1640 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1641 /* index: 1641 */
	.weak aio_multihandle_fini; .quad aio_multihandle_fini
	.reloc ., R_X86_64_SIZE32, aio_multihandle_fini; .int 0
	.int 0x81d8669
	.quad .Lname1642 /* index: 1642 */
	.weak sys32_getuid32; .quad sys32_getuid32
	.reloc ., R_X86_64_SIZE32, sys32_getuid32; .int 0
	.int 0xcdd7502
	.quad 0 /* index: 1643 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1644 /* index: 1644 */
	.weak sys_writev; .quad sys_writev
	.reloc ., R_X86_64_SIZE32, sys_writev; .int 0
	.int 0x6f0ba56
	.quad .Lname1645 /* index: 1645 */
	.weak rawmemrchr; .quad rawmemrchr
	.reloc ., R_X86_64_SIZE32, rawmemrchr; .int 0
	.int 0x3c30112
	.quad 0 /* index: 1646 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1647 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1648 /* index: 1648 */
	.weak inode_awritev_phys; .quad inode_awritev_phys
	.reloc ., R_X86_64_SIZE32, inode_awritev_phys; .int 0
	.int 0xe4d8613
	.quad .Lname1649 /* index: 1649 */
	.weak vio_cmpxch128; .quad vio_cmpxch128
	.reloc ., R_X86_64_SIZE32, vio_cmpxch128; .int 0
	.int 0xaecee68
	.quad .Lname1650 /* index: 1650 */
	.weak sys32_readlinkat; .quad sys32_readlinkat
	.reloc ., R_X86_64_SIZE32, sys32_readlinkat; .int 0
	.int 0xdaf8a94
	.quad .Lname1651 /* index: 1651 */
	.weak krealloc; .quad krealloc
	.reloc ., R_X86_64_SIZE32, krealloc; .int 0
	.int 0x8b83673
	.quad .Lname1652 /* index: 1652 */
	.weak rwlock_end; .quad rwlock_end
	.reloc ., R_X86_64_SIZE32, rwlock_end; .int 0
	.int 0x5a8c674
	.quad 0 /* index: 1653 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1654 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1655 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1656 /* index: 1656 */
	.weak krealloc_in_place_nx; .quad krealloc_in_place_nx
	.reloc ., R_X86_64_SIZE32, krealloc_in_place_nx; .int 0
	.int 0x391c678
	.quad .Lname1657 /* index: 1657 */
	.weak handle_manager_destroy; .quad handle_manager_destroy
	.reloc ., R_X86_64_SIZE32, handle_manager_destroy; .int 0
	.int 0x59ab679
	.quad 0 /* index: 1658 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1659 /* index: 1659 */
	.weak vm_node_free; .quad vm_node_free
	.reloc ., R_X86_64_SIZE32, vm_node_free; .int 0
	.int 0xd86bde5
	.quad .Lname1660 /* index: 1660 */
	.weak rawmemrlenl; .quad rawmemrlenl
	.reloc ., R_X86_64_SIZE32, rawmemrlenl; .int 0
	.int 0xc31a67c
	.quad 0 /* index: 1661 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1662 /* index: 1662 */
	.weak sys_kexec_file_load; .quad sys_kexec_file_load
	.reloc ., R_X86_64_SIZE32, sys_kexec_file_load; .int 0
	.int 0x7282824
	.quad .Lname1663 /* index: 1663 */
	.weak fs_filesystems_lock_upgrade; .quad fs_filesystems_lock_upgrade
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_upgrade; .int 0
	.int 0xd002115
	.quad .Lname1664 /* index: 1664 */
	.weak sys_io_destroy; .quad sys_io_destroy
	.reloc ., R_X86_64_SIZE32, sys_io_destroy; .int 0
	.int 0xa5cbd89
	.quad 0 /* index: 1665 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1666 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1667 /* index: 1667 */
	.weak vm_alloc; .quad vm_alloc
	.reloc ., R_X86_64_SIZE32, vm_alloc; .int 0
	.int 0x3583683
	.quad .Lname1668 /* index: 1668 */
	.weak sys32_ulimit; .quad sys32_ulimit
	.reloc ., R_X86_64_SIZE32, sys32_ulimit; .int 0
	.int 0x112a684
	.quad .Lname1669 /* index: 1669 */
	.weak inode_chtime; .quad inode_chtime
	.reloc ., R_X86_64_SIZE32, inode_chtime; .int 0
	.int 0x29af685
	.quad .Lname1670 /* index: 1670 */
	.weak sys_io_getevents; .quad sys_io_getevents
	.reloc ., R_X86_64_SIZE32, sys_io_getevents; .int 0
	.int 0xcc868e3
	.quad 0 /* index: 1671 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1672 /* index: 1672 */
	.weak path_lock_upgrade_nx; .quad path_lock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, path_lock_upgrade_nx; .int 0
	.int 0xac21688
	.quad .Lname1673 /* index: 1673 */
	.weak unwind_setreg_sfpustate_exclusive; .quad unwind_setreg_sfpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_sfpustate_exclusive; .int 0
	.int 0xbfe5125
	.quad 0 /* index: 1674 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1675 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1676 /* index: 1676 */
	.weak dbg_isholding_ctrl; .quad dbg_isholding_ctrl
	.reloc ., R_X86_64_SIZE32, dbg_isholding_ctrl; .int 0
	.int 0xbab568c
	.quad 0 /* index: 1677 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1678 /* index: 1678 */
	.weak keymap_instrlen; .quad keymap_instrlen
	.reloc ., R_X86_64_SIZE32, keymap_instrlen; .int 0
	.int 0x593c68e
	.quad .Lname1679 /* index: 1679 */
	.weak x86_memcpy_nopf_ret_pointer; .quad x86_memcpy_nopf_ret_pointer
	.reloc ., R_X86_64_SIZE32, x86_memcpy_nopf_ret_pointer; .int 0
	.int 0x8a132d2
	.quad 0 /* index: 1680 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1681 /* index: 1681 */
	.weak sys32_detach; .quad sys32_detach
	.reloc ., R_X86_64_SIZE32, sys32_detach; .int 0
	.int 0x21cc118
	.quad 0 /* index: 1682 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1683 /* index: 1683 */
	.weak swap_sync; .quad swap_sync
	.reloc ., R_X86_64_SIZE32, swap_sync; .int 0
	.int 0x866d693
	.quad .Lname1684 /* index: 1684 */
	.weak abort; .quad abort
	.reloc ., R_X86_64_SIZE32, abort; .int 0
	.int 0x679694
	.quad .Lname1685 /* index: 1685 */
	.weak vm_sync_endone; .quad vm_sync_endone
	.reloc ., R_X86_64_SIZE32, vm_sync_endone; .int 0
	.int 0x6efb725
	.quad .Lname1686 /* index: 1686 */
	.weak sys32_rename; .quad sys32_rename
	.reloc ., R_X86_64_SIZE32, sys32_rename; .int 0
	.int 0x13c22b5
	.quad .Lname1687 /* index: 1687 */
	.weak sys32_sched_get_priority_max; .quad sys32_sched_get_priority_max
	.reloc ., R_X86_64_SIZE32, sys32_sched_get_priority_max; .int 0
	.int 0xbe35038
	.quad .Lname1688 /* index: 1688 */
	.weak vio_readl_aligned; .quad vio_readl_aligned
	.reloc ., R_X86_64_SIZE32, vio_readl_aligned; .int 0
	.int 0xe571f4
	.quad .Lname1689 /* index: 1689 */
	.weak __predict_update_esi; .quad __predict_update_esi
	.reloc ., R_X86_64_SIZE32, __predict_update_esi; .int 0
	.int 0x4552699
	.quad .Lname1690 /* index: 1690 */
	.weak sys_fork; .quad sys_fork
	.reloc ., R_X86_64_SIZE32, sys_fork; .int 0
	.int 0x95d13b
	.quad 0 /* index: 1691 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1692 /* index: 1692 */
	.weak this_trampoline_page; .quad this_trampoline_page
	.reloc ., R_X86_64_SIZE32, this_trampoline_page; .int 0
	.int 0xe062935
	.quad 0 /* index: 1693 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1694 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1695 /* index: 1695 */
	.weak unwind_getreg_sfpustate; .quad unwind_getreg_sfpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_sfpustate; .int 0
	.int 0xb8c43c5
	.quad 0 /* index: 1696 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1697 /* index: 1697 */
	.weak setreg_ucpustate; .quad setreg_ucpustate
	.reloc ., R_X86_64_SIZE32, setreg_ucpustate; .int 0
	.int 0xf765fb5
	.quad .Lname1698 /* index: 1698 */
	.weak debuginfo_cu_parser_loadattr_member; .quad debuginfo_cu_parser_loadattr_member
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_member; .int 0
	.int 0xd7446a2
	.quad 0 /* index: 1699 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1700 /* index: 1700 */
	.weak sys32_kexec_load; .quad sys32_kexec_load
	.reloc ., R_X86_64_SIZE32, sys32_kexec_load; .int 0
	.int 0xd1799f4
	.quad .Lname1701 /* index: 1701 */
	.weak path_freesize; .quad path_freesize
	.reloc ., R_X86_64_SIZE32, path_freesize; .int 0
	.int 0xe3686a5
	.quad 0 /* index: 1702 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1703 /* index: 1703 */
	.weak vm_memsetphys; .quad vm_memsetphys
	.reloc ., R_X86_64_SIZE32, vm_memsetphys; .int 0
	.int 0x4fd5433
	.quad 0 /* index: 1704 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1705 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1706 /* index: 1706 */
	.weak sys_flistxattr; .quad sys_flistxattr
	.reloc ., R_X86_64_SIZE32, sys_flistxattr; .int 0
	.int 0xa2b5d02
	.quad .Lname1707 /* index: 1707 */
	.weak symlink_node_readlink; .quad symlink_node_readlink
	.reloc ., R_X86_64_SIZE32, symlink_node_readlink; .int 0
	.int 0xa11d6ab
	.quad .Lname1708 /* index: 1708 */
	.weak inode_areadall; .quad inode_areadall
	.reloc ., R_X86_64_SIZE32, inode_areadall; .int 0
	.int 0xded16ac
	.quad .Lname1709 /* index: 1709 */
	.weak sys32_sched_getscheduler; .quad sys32_sched_getscheduler
	.reloc ., R_X86_64_SIZE32, sys32_sched_getscheduler; .int 0
	.int 0xa4e9672
	.quad 0 /* index: 1710 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1711 /* index: 1711 */
	.weak mouse_device_vwheel; .quad mouse_device_vwheel
	.reloc ., R_X86_64_SIZE32, mouse_device_vwheel; .int 0
	.int 0x87d892c
	.quad .Lname1712 /* index: 1712 */
	.weak sys32_getpgrp; .quad sys32_getpgrp
	.reloc ., R_X86_64_SIZE32, sys32_getpgrp; .int 0
	.int 0x6cd06b0
	.quad .Lname1713 /* index: 1713 */
	.weak task_alloc_user_rpc_nx; .quad task_alloc_user_rpc_nx
	.reloc ., R_X86_64_SIZE32, task_alloc_user_rpc_nx; .int 0
	.int 0xcab93c8
	.quad 0 /* index: 1714 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1715 /* index: 1715 */
	.weak superblock_clear_caches; .quad superblock_clear_caches
	.reloc ., R_X86_64_SIZE32, superblock_clear_caches; .int 0
	.int 0x93c8673
	.quad .Lname1716 /* index: 1716 */
	.weak path_sprint; .quad path_sprint
	.reloc ., R_X86_64_SIZE32, path_sprint; .int 0
	.int 0x6d106b4
	.quad .Lname1717 /* index: 1717 */
	.weak getreg_lcpustate; .quad getreg_lcpustate
	.reloc ., R_X86_64_SIZE32, getreg_lcpustate; .int 0
	.int 0xf7136b5
	.quad .Lname1718 /* index: 1718 */
	.weak debuginfo_cu_parser_getref; .quad debuginfo_cu_parser_getref
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getref; .int 0
	.int 0xbbb56b6
	.quad .Lname1719 /* index: 1719 */
	.weak vfs_clearmounts; .quad vfs_clearmounts
	.reloc ., R_X86_64_SIZE32, vfs_clearmounts; .int 0
	.int 0x27cf2e3
	.quad .Lname1720 /* index: 1720 */
	.weak sys_adjtimex; .quad sys_adjtimex
	.reloc ., R_X86_64_SIZE32, sys_adjtimex; .int 0
	.int 0xeaa76b8
	.quad .Lname1721 /* index: 1721 */
	.weak sys_frenameat; .quad sys_frenameat
	.reloc ., R_X86_64_SIZE32, sys_frenameat; .int 0
	.int 0x14f6674
	.quad 0 /* index: 1722 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1723 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1724 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1725 /* index: 1725 */
	.weak this_vm; .quad this_vm
	.reloc ., R_X86_64_SIZE32, this_vm; .int 0
	.int 0xaf096bd
	.quad 0 /* index: 1726 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1727 /* index: 1727 */
	.weak x86_sysroute0_asm32_int80; .quad x86_sysroute0_asm32_int80
	.reloc ., R_X86_64_SIZE32, x86_sysroute0_asm32_int80; .int 0
	.int 0x34e1620
	.quad 0 /* index: 1728 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1729 /* index: 1729 */
	.weak sys_inotify_init1; .quad sys_inotify_init1
	.reloc ., R_X86_64_SIZE32, sys_inotify_init1; .int 0
	.int 0xf13f6c1
	.quad .Lname1730 /* index: 1730 */
	.weak block_device_areadv_phys_sector; .quad block_device_areadv_phys_sector
	.reloc ., R_X86_64_SIZE32, block_device_areadv_phys_sector; .int 0
	.int 0x88c86c2
	.quad 0 /* index: 1731 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1732 /* index: 1732 */
	.weak page_isfree; .quad page_isfree
	.reloc ., R_X86_64_SIZE32, page_isfree; .int 0
	.int 0x67fa505
	.quad .Lname1733 /* index: 1733 */
	.weak dbg_hline; .quad dbg_hline
	.reloc ., R_X86_64_SIZE32, dbg_hline; .int 0
	.int 0xd5f46c5
	.quad 0 /* index: 1734 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1735 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1736 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1737 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1738 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1739 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1740 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1741 /* index: 1741 */
	.weak sys_sysinfo; .quad sys_sysinfo
	.reloc ., R_X86_64_SIZE32, sys_sysinfo; .int 0
	.int 0xb730daf
	.quad .Lname1742 /* index: 1742 */
	.weak sys_acct; .quad sys_acct
	.reloc ., R_X86_64_SIZE32, sys_acct; .int 0
	.int 0x957e14
	.quad 0 /* index: 1743 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1744 /* index: 1744 */
	.weak sys32_vhangup; .quad sys32_vhangup
	.reloc ., R_X86_64_SIZE32, sys32_vhangup; .int 0
	.int 0x7e226d0
	.quad .Lname1745 /* index: 1745 */
	.weak sys32_get_thread_area; .quad sys32_get_thread_area
	.reloc ., R_X86_64_SIZE32, sys32_get_thread_area; .int 0
	.int 0x7a756d1
	.quad .Lname1746 /* index: 1746 */
	.weak dbg_fillrect2; .quad dbg_fillrect2
	.reloc ., R_X86_64_SIZE32, dbg_fillrect2; .int 0
	.int 0x9b5e6d2
	.quad .Lname1747 /* index: 1747 */
	.weak slab_malloc; .quad slab_malloc
	.reloc ., R_X86_64_SIZE32, slab_malloc; .int 0
	.int 0x64e16d3
	.quad .Lname1748 /* index: 1748 */
	.weak dbg_print; .quad dbg_print
	.reloc ., R_X86_64_SIZE32, dbg_print; .int 0
	.int 0xd67e6d4
	.quad .Lname1749 /* index: 1749 */
	.weak inode_recent; .quad inode_recent
	.reloc ., R_X86_64_SIZE32, inode_recent; .int 0
	.int 0x18ec2e4
	.quad 0 /* index: 1750 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1751 /* index: 1751 */
	.weak vm_datablock_vio_writev_phys; .quad vm_datablock_vio_writev_phys
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_writev_phys; .int 0
	.int 0x1064023
	.quad 0 /* index: 1752 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1753 /* index: 1753 */
	.weak pipe_max_bufsize_unprivileged; .quad pipe_max_bufsize_unprivileged
	.reloc ., R_X86_64_SIZE32, pipe_max_bufsize_unprivileged; .int 0
	.int 0x7d03124
	.quad 0 /* index: 1754 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1755 /* index: 1755 */
	.weak syscall_emulate; .quad syscall_emulate
	.reloc ., R_X86_64_SIZE32, syscall_emulate; .int 0
	.int 0x3d443f5
	.quad 0 /* index: 1756 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1757 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1758 /* index: 1758 */
	.weak sys32_open; .quad sys32_open
	.reloc ., R_X86_64_SIZE32, sys32_open; .int 0
	.int 0x683d6de
	.quad .Lname1759 /* index: 1759 */
	.weak character_device_pwrite; .quad character_device_pwrite
	.reloc ., R_X86_64_SIZE32, character_device_pwrite; .int 0
	.int 0xb715925
	.quad 0 /* index: 1760 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1761 /* index: 1761 */
	.weak vio_orq; .quad vio_orq
	.reloc ., R_X86_64_SIZE32, vio_orq; .int 0
	.int 0xd0566e1
	.quad .Lname1762 /* index: 1762 */
	.weak sys_set_exception_handler; .quad sys_set_exception_handler
	.reloc ., R_X86_64_SIZE32, sys_set_exception_handler; .int 0
	.int 0xa9f56e2
	.quad .Lname1763 /* index: 1763 */
	.weak pty_alloc; .quad pty_alloc
	.reloc ., R_X86_64_SIZE32, pty_alloc; .int 0
	.int 0xf5866e3
	.quad .Lname1764 /* index: 1764 */
	.weak x86_dbg_getregbyid; .quad x86_dbg_getregbyid
	.reloc ., R_X86_64_SIZE32, x86_dbg_getregbyid; .int 0
	.int 0x73386e4
	.quad .Lname1765 /* index: 1765 */
	.weak coredump_create; .quad coredump_create
	.reloc ., R_X86_64_SIZE32, coredump_create; .int 0
	.int 0xd1356e5
	.quad .Lname1766 /* index: 1766 */
	.weak regdump_dr6; .quad regdump_dr6
	.reloc ., R_X86_64_SIZE32, regdump_dr6; .int 0
	.int 0xc3ee6e6
	.quad .Lname1767 /* index: 1767 */
	.weak regdump_dr7; .quad regdump_dr7
	.reloc ., R_X86_64_SIZE32, regdump_dr7; .int 0
	.int 0xc3ee6e7
	.quad 0 /* index: 1768 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1769 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1770 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1771 /* index: 1771 */
	.weak sys32_fork; .quad sys32_fork
	.reloc ., R_X86_64_SIZE32, sys32_fork; .int 0
	.int 0x68286eb
	.quad .Lname1772 /* index: 1772 */
	.weak sys32_ftruncate; .quad sys32_ftruncate
	.reloc ., R_X86_64_SIZE32, sys32_ftruncate; .int 0
	.int 0xfecbe15
	.quad 0 /* index: 1773 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1774 /* index: 1774 */
	.weak path_lock_read_nx; .quad path_lock_read_nx
	.reloc ., R_X86_64_SIZE32, path_lock_read_nx; .int 0
	.int 0xed4cfd8
	.quad .Lname1775 /* index: 1775 */
	.weak vio_copytovio; .quad vio_copytovio
	.reloc ., R_X86_64_SIZE32, vio_copytovio; .int 0
	.int 0xb1036ef
	.quad .Lname1776 /* index: 1776 */
	.weak sys32_getxattr; .quad sys32_getxattr
	.reloc ., R_X86_64_SIZE32, sys32_getxattr; .int 0
	.int 0xcd809d2
	.quad 0 /* index: 1777 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1778 /* index: 1778 */
	.weak vio_orb; .quad vio_orb
	.reloc ., R_X86_64_SIZE32, vio_orb; .int 0
	.int 0xd0566f2
	.quad .Lname1779 /* index: 1779 */
	.weak aio_pbuffer_copytophys; .quad aio_pbuffer_copytophys
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copytophys; .int 0
	.int 0xa9cd6f3
	.quad .Lname1780 /* index: 1780 */
	.weak sys32_fchownat; .quad sys32_fchownat
	.reloc ., R_X86_64_SIZE32, sys32_fchownat; .int 0
	.int 0x99066f4
	.quad .Lname1781 /* index: 1781 */
	.weak get_stack_inuse; .quad get_stack_inuse
	.reloc ., R_X86_64_SIZE32, get_stack_inuse; .int 0
	.int 0xb3696f5
	.quad .Lname1782 /* index: 1782 */
	.weak vm_pagetophys_nopf; .quad vm_pagetophys_nopf
	.reloc ., R_X86_64_SIZE32, vm_pagetophys_nopf; .int 0
	.int 0xab056f6
	.quad .Lname1783 /* index: 1783 */
	.weak vm_pagefromphys; .quad vm_pagefromphys
	.reloc ., R_X86_64_SIZE32, vm_pagefromphys; .int 0
	.int 0xf43cae3
	.quad 0 /* index: 1784 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1785 /* index: 1785 */
	.weak pidns_root; .quad pidns_root
	.reloc ., R_X86_64_SIZE32, pidns_root; .int 0
	.int 0x591fbd4
	.quad 0 /* index: 1786 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1787 /* index: 1787 */
	.weak strto32; .quad strto32
	.reloc ., R_X86_64_SIZE32, strto32; .int 0
	.int 0xab9b212
	.quad .Lname1788 /* index: 1788 */
	.weak sys_restart_syscall; .quad sys_restart_syscall
	.reloc ., R_X86_64_SIZE32, sys_restart_syscall; .int 0
	.int 0xca866fc
	.quad .Lname1789 /* index: 1789 */
	.weak thiscpu_current; .quad thiscpu_current
	.reloc ., R_X86_64_SIZE32, thiscpu_current; .int 0
	.int 0xa538bf4
	.quad 0 /* index: 1790 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1791 /* index: 1791 */
	.weak inode_file_writev_with_write; .quad inode_file_writev_with_write
	.reloc ., R_X86_64_SIZE32, inode_file_writev_with_write; .int 0
	.int 0x1142bd5
	.quad 0 /* index: 1792 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1793 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1794 /* index: 1794 */
	.weak ringbuffer_read_nonblock; .quad ringbuffer_read_nonblock
	.reloc ., R_X86_64_SIZE32, ringbuffer_read_nonblock; .int 0
	.int 0x2a41a5b
	.quad .Lname1795 /* index: 1795 */
	.weak handle_get_fs; .quad handle_get_fs
	.reloc ., R_X86_64_SIZE32, handle_get_fs; .int 0
	.int 0xb583703
	.quad .Lname1796 /* index: 1796 */
	.weak callback_list_insert; .quad callback_list_insert
	.reloc ., R_X86_64_SIZE32, callback_list_insert; .int 0
	.int 0xc941704
	.quad .Lname1797 /* index: 1797 */
	.weak sys_ptrace; .quad sys_ptrace
	.reloc ., R_X86_64_SIZE32, sys_ptrace; .int 0
	.int 0x67c3705
	.quad .Lname1798 /* index: 1798 */
	.weak vio_andw; .quad vio_andw
	.reloc ., R_X86_64_SIZE32, vio_andw; .int 0
	.int 0x558367
	.quad 0 /* index: 1799 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1800 /* index: 1800 */
	.weak sys_detach; .quad sys_detach
	.reloc ., R_X86_64_SIZE32, sys_detach; .int 0
	.int 0x5ab1708
	.quad .Lname1801 /* index: 1801 */
	.weak dbg_getfunc_fuzzy; .quad dbg_getfunc_fuzzy
	.reloc ., R_X86_64_SIZE32, dbg_getfunc_fuzzy; .int 0
	.int 0x6fda709
	.quad 0 /* index: 1802 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1803 /* index: 1803 */
	.weak x86_sysroute1_asm64_syscall; .quad x86_sysroute1_asm64_syscall
	.reloc ., R_X86_64_SIZE32, x86_sysroute1_asm64_syscall; .int 0
	.int 0x948f65c
	.quad 0 /* index: 1804 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1805 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1806 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1807 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1808 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1809 /* index: 1809 */
	.weak vio_cmpxch_or_writew; .quad vio_cmpxch_or_writew
	.reloc ., R_X86_64_SIZE32, vio_cmpxch_or_writew; .int 0
	.int 0x8230f27
	.quad .Lname1810 /* index: 1810 */
	.weak sys_fgetxattr; .quad sys_fgetxattr
	.reloc ., R_X86_64_SIZE32, sys_fgetxattr; .int 0
	.int 0x7b7d712
	.quad .Lname1811 /* index: 1811 */
	.weak block_device_sync; .quad block_device_sync
	.reloc ., R_X86_64_SIZE32, block_device_sync; .int 0
	.int 0x8a55713
	.quad .Lname1812 /* index: 1812 */
	.weak sig_altsend; .quad sig_altsend
	.reloc ., R_X86_64_SIZE32, sig_altsend; .int 0
	.int 0x8426714
	.quad .Lname1813 /* index: 1813 */
	.weak superblock_nodeslock_endread; .quad superblock_nodeslock_endread
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_endread; .int 0
	.int 0xe4beae4
	.quad .Lname1814 /* index: 1814 */
	.weak sys32_frealpath4; .quad sys32_frealpath4
	.reloc ., R_X86_64_SIZE32, sys32_frealpath4; .int 0
	.int 0x2b4e264
	.quad .Lname1815 /* index: 1815 */
	.weak sys32_gtty; .quad sys32_gtty
	.reloc ., R_X86_64_SIZE32, sys32_gtty; .int 0
	.int 0x6825bd9
	.quad .Lname1816 /* index: 1816 */
	.weak aio_multihandle_allochandle_nx; .quad aio_multihandle_allochandle_nx
	.reloc ., R_X86_64_SIZE32, aio_multihandle_allochandle_nx; .int 0
	.int 0xdcf3718
	.quad .Lname1817 /* index: 1817 */
	.weak userkern_segment_part; .quad userkern_segment_part
	.reloc ., R_X86_64_SIZE32, userkern_segment_part; .int 0
	.int 0xfac1e84
	.quad 0 /* index: 1818 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1819 /* index: 1819 */
	.weak pidns_write; .quad pidns_write
	.reloc ., R_X86_64_SIZE32, pidns_write; .int 0
	.int 0x9188bf5
	.quad .Lname1820 /* index: 1820 */
	.weak sys_setregid; .quad sys_setregid
	.reloc ., R_X86_64_SIZE32, sys_setregid; .int 0
	.int 0xb082b64
	.quad .Lname1821 /* index: 1821 */
	.weak sys_llistxattr; .quad sys_llistxattr
	.reloc ., R_X86_64_SIZE32, sys_llistxattr; .int 0
	.int 0xa28bd02
	.quad 0 /* index: 1822 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1823 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1824 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1825 /* index: 1825 */
	.weak sys_inotify_init; .quad sys_inotify_init
	.reloc ., R_X86_64_SIZE32, sys_inotify_init; .int 0
	.int 0xbf13f64
	.quad .Lname1826 /* index: 1826 */
	.weak sys32_pwritevf; .quad sys32_pwritevf
	.reloc ., R_X86_64_SIZE32, sys32_pwritevf; .int 0
	.int 0xef62d06
	.quad .Lname1827 /* index: 1827 */
	.weak tty_device_alloc; .quad tty_device_alloc
	.reloc ., R_X86_64_SIZE32, tty_device_alloc; .int 0
	.int 0xfd6723
	.quad .Lname1828 /* index: 1828 */
	.weak syscall_printtrace_compat; .quad syscall_printtrace_compat
	.reloc ., R_X86_64_SIZE32, syscall_printtrace_compat; .int 0
	.int 0x5542724
	.quad .Lname1829 /* index: 1829 */
	.weak json_parser_state; .quad json_parser_state
	.reloc ., R_X86_64_SIZE32, json_parser_state; .int 0
	.int 0x2739725
	.quad .Lname1830 /* index: 1830 */
	.weak sys_preadv; .quad sys_preadv
	.reloc ., R_X86_64_SIZE32, sys_preadv; .int 0
	.int 0x67f0726
	.quad .Lname1831 /* index: 1831 */
	.weak mempcpyq; .quad mempcpyq
	.reloc ., R_X86_64_SIZE32, mempcpyq; .int 0
	.int 0xc46a131
	.quad .Lname1832 /* index: 1832 */
	.weak slab_kmalloc16; .quad slab_kmalloc16
	.reloc ., R_X86_64_SIZE32, slab_kmalloc16; .int 0
	.int 0x66b31d6
	.quad .Lname1833 /* index: 1833 */
	.weak dbg_pputuni; .quad dbg_pputuni
	.reloc ., R_X86_64_SIZE32, dbg_pputuni; .int 0
	.int 0x7163729
	.quad .Lname1834 /* index: 1834 */
	.weak vm_oninit_callbacks; .quad vm_oninit_callbacks
	.reloc ., R_X86_64_SIZE32, vm_oninit_callbacks; .int 0
	.int 0x96845d3
	.quad .Lname1835 /* index: 1835 */
	.weak sys_symlink; .quad sys_symlink
	.reloc ., R_X86_64_SIZE32, sys_symlink; .int 0
	.int 0xa99272b
	.quad 0 /* index: 1836 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1837 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1838 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1839 /* index: 1839 */
	.weak x86_bootcpu_gdt; .quad x86_bootcpu_gdt
	.reloc ., R_X86_64_SIZE32, x86_bootcpu_gdt; .int 0
	.int 0x62460a4
	.quad 0 /* index: 1840 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1841 /* index: 1841 */
	.weak zlib_reader_setpos; .quad zlib_reader_setpos
	.reloc ., R_X86_64_SIZE32, zlib_reader_setpos; .int 0
	.int 0x639e343
	.quad .Lname1842 /* index: 1842 */
	.weak x86_fxrstor; .quad x86_fxrstor
	.reloc ., R_X86_64_SIZE32, x86_fxrstor; .int 0
	.int 0xd821732
	.quad .Lname1843 /* index: 1843 */
	.weak task_popconnections; .quad task_popconnections
	.reloc ., R_X86_64_SIZE32, task_popconnections; .int 0
	.int 0x74eb733
	.quad .Lname1844 /* index: 1844 */
	.weak sys32_sched_rr_get_interval64; .quad sys32_sched_rr_get_interval64
	.reloc ., R_X86_64_SIZE32, sys32_sched_rr_get_interval64; .int 0
	.int 0x2626734
	.quad .Lname1845 /* index: 1845 */
	.weak vm_kernel_treelock_endwrite; .quad vm_kernel_treelock_endwrite
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_endwrite; .int 0
	.int 0xf8e2735
	.quad .Lname1846 /* index: 1846 */
	.weak vm_datablock_vio_readv; .quad vm_datablock_vio_readv
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_readv; .int 0
	.int 0xc467736
	.quad .Lname1847 /* index: 1847 */
	.weak ttybase_device_setctty; .quad ttybase_device_setctty
	.reloc ., R_X86_64_SIZE32, ttybase_device_setctty; .int 0
	.int 0xd8b1e89
	.quad 0 /* index: 1848 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1849 /* index: 1849 */
	.weak ansitty_putuni; .quad ansitty_putuni
	.reloc ., R_X86_64_SIZE32, ansitty_putuni; .int 0
	.int 0x3dc0739
	.quad .Lname1850 /* index: 1850 */
	.weak vm_library_enumerate; .quad vm_library_enumerate
	.reloc ., R_X86_64_SIZE32, vm_library_enumerate; .int 0
	.int 0x1c12ea5
	.quad .Lname1851 /* index: 1851 */
	.weak ringbuffer_rseek; .quad ringbuffer_rseek
	.reloc ., R_X86_64_SIZE32, ringbuffer_rseek; .int 0
	.int 0xbf5c73b
	.quad .Lname1852 /* index: 1852 */
	.weak this_taskgroup; .quad this_taskgroup
	.reloc ., R_X86_64_SIZE32, this_taskgroup; .int 0
	.int 0x717fbe0
	.quad .Lname1853 /* index: 1853 */
	.weak sys32_lchown; .quad sys32_lchown
	.reloc ., R_X86_64_SIZE32, sys32_lchown; .int 0
	.int 0x399905e
	.quad .Lname1854 /* index: 1854 */
	.weak sys32_perf_event_open; .quad sys32_perf_event_open
	.reloc ., R_X86_64_SIZE32, sys32_perf_event_open; .int 0
	.int 0xb89b73e
	.quad .Lname1855 /* index: 1855 */
	.weak ramfs_directory_type; .quad ramfs_directory_type
	.reloc ., R_X86_64_SIZE32, ramfs_directory_type; .int 0
	.int 0x1609935
	.quad 0 /* index: 1856 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1857 /* index: 1857 */
	.weak pagedir_unmapone_p; .quad pagedir_unmapone_p
	.reloc ., R_X86_64_SIZE32, pagedir_unmapone_p; .int 0
	.int 0xf55cbe0
	.quad .Lname1858 /* index: 1858 */
	.weak vm_kernel_treelock_read; .quad vm_kernel_treelock_read
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_read; .int 0
	.int 0x94b044
	.quad 0 /* index: 1859 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1860 /* index: 1860 */
	.weak path_sprintent; .quad path_sprintent
	.reloc ., R_X86_64_SIZE32, path_sprintent; .int 0
	.int 0x6bc744
	.quad .Lname1861 /* index: 1861 */
	.weak fs_filesystems_lock_tryupgrade; .quad fs_filesystems_lock_tryupgrade
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_tryupgrade; .int 0
	.int 0x6053745
	.quad 0 /* index: 1862 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1863 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1864 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1865 /* index: 1865 */
	.weak handle_fcntl; .quad handle_fcntl
	.reloc ., R_X86_64_SIZE32, handle_fcntl; .int 0
	.int 0xdb4ee8c
	.quad 0 /* index: 1866 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1867 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1868 /* index: 1868 */
	.weak keyboard_device_poll; .quad keyboard_device_poll
	.reloc ., R_X86_64_SIZE32, keyboard_device_poll; .int 0
	.int 0xf16074c
	.quad .Lname1869 /* index: 1869 */
	.weak handle_close_nosym; .quad handle_close_nosym
	.reloc ., R_X86_64_SIZE32, handle_close_nosym; .int 0
	.int 0x8f7174d
	.quad 0 /* index: 1870 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1871 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1872 /* index: 1872 */
	.weak pidns_lookup; .quad pidns_lookup
	.reloc ., R_X86_64_SIZE32, pidns_lookup; .int 0
	.int 0x35bf750
	.quad 0 /* index: 1873 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1874 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1875 /* index: 1875 */
	.weak vm_datapart_read_phys; .quad vm_datapart_read_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_read_phys; .int 0
	.int 0xab4d3e3
	.quad .Lname1876 /* index: 1876 */
	.weak sys32_io_submit; .quad sys32_io_submit
	.reloc ., R_X86_64_SIZE32, sys32_io_submit; .int 0
	.int 0xc3b754
	.quad .Lname1877 /* index: 1877 */
	.weak thiscpu_x86_iob; .quad thiscpu_x86_iob
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_iob; .int 0
	.int 0xb225fc2
	.quad 0 /* index: 1878 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1879 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1880 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1881 /* index: 1881 */
	.weak isr_unregister_at; .quad isr_unregister_at
	.reloc ., R_X86_64_SIZE32, isr_unregister_at; .int 0
	.int 0x68473e4
	.quad 0 /* index: 1882 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1883 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1884 /* index: 1884 */
	.weak coredump_create_for_signal; .quad coredump_create_for_signal
	.reloc ., R_X86_64_SIZE32, coredump_create_for_signal; .int 0
	.int 0x81ae75c
	.quad .Lname1885 /* index: 1885 */
	.weak vm_enumdma; .quad vm_enumdma
	.reloc ., R_X86_64_SIZE32, vm_enumdma; .int 0
	.int 0xc5dea61
	.quad 0 /* index: 1886 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1887 /* index: 1887 */
	.weak json_encode; .quad json_encode
	.reloc ., R_X86_64_SIZE32, json_encode; .int 0
	.int 0x5d543e5
	.quad .Lname1888 /* index: 1888 */
	.weak getreg_gpregsnsp; .quad getreg_gpregsnsp
	.reloc ., R_X86_64_SIZE32, getreg_gpregsnsp; .int 0
	.int 0x52760
	.quad .Lname1889 /* index: 1889 */
	.weak sys32_setgid; .quad sys32_setgid
	.reloc ., R_X86_64_SIZE32, sys32_setgid; .int 0
	.int 0x12ccb74
	.quad .Lname1890 /* index: 1890 */
	.weak vm_free; .quad vm_free
	.reloc ., R_X86_64_SIZE32, vm_free; .int 0
	.int 0xd35d8c5
	.quad .Lname1891 /* index: 1891 */
	.weak inode_tryaccess; .quad inode_tryaccess
	.reloc ., R_X86_64_SIZE32, inode_tryaccess; .int 0
	.int 0xad28763
	.quad .Lname1892 /* index: 1892 */
	.weak task_trywait; .quad task_trywait
	.reloc ., R_X86_64_SIZE32, task_trywait; .int 0
	.int 0xc487764
	.quad 0 /* index: 1893 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1894 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1895 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1896 /* index: 1896 */
	.weak superblock_mountlock_read_nx; .quad superblock_mountlock_read_nx
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_read_nx; .int 0
	.int 0x1b6f768
	.quad 0 /* index: 1897 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1898 /* index: 1898 */
	.weak sys_personality; .quad sys_personality
	.reloc ., R_X86_64_SIZE32, sys_personality; .int 0
	.int 0xd22a219
	.quad 0 /* index: 1899 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1900 /* index: 1900 */
	.weak rawmemchrl; .quad rawmemchrl
	.reloc ., R_X86_64_SIZE32, rawmemchrl; .int 0
	.int 0x3c4176c
	.quad 0 /* index: 1901 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1902 /* index: 1902 */
	.weak vm_datapart_lockread_setcore_nx; .quad vm_datapart_lockread_setcore_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockread_setcore_nx; .int 0
	.int 0x7cb34d8
	.quad 0 /* index: 1903 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1904 /* index: 1904 */
	.weak vm_startdma; .quad vm_startdma
	.reloc ., R_X86_64_SIZE32, vm_startdma; .int 0
	.int 0xaf49d91
	.quad .Lname1905 /* index: 1905 */
	.weak rawmemchrq; .quad rawmemchrq
	.reloc ., R_X86_64_SIZE32, rawmemchrq; .int 0
	.int 0x3c41771
	.quad 0 /* index: 1906 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1907 /* index: 1907 */
	.weak thiscpu_x86_cpuid; .quad thiscpu_x86_cpuid
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_cpuid; .int 0
	.int 0x25be0d4
	.quad .Lname1908 /* index: 1908 */
	.weak sys32_ftruncate64; .quad sys32_ftruncate64
	.reloc ., R_X86_64_SIZE32, sys32_ftruncate64; .int 0
	.int 0xcbe1774
	.quad .Lname1909 /* index: 1909 */
	.weak sys32_clock_settime; .quad sys32_clock_settime
	.reloc ., R_X86_64_SIZE32, sys32_clock_settime; .int 0
	.int 0xaffa775
	.quad .Lname1910 /* index: 1910 */
	.weak zlib_reader_feed; .quad zlib_reader_feed
	.reloc ., R_X86_64_SIZE32, zlib_reader_feed; .int 0
	.int 0x4256ee4
	.quad .Lname1911 /* index: 1911 */
	.weak rawmemchrw; .quad rawmemchrw
	.reloc ., R_X86_64_SIZE32, rawmemchrw; .int 0
	.int 0x3c41777
	.quad 0 /* index: 1912 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1913 /* index: 1913 */
	.weak inode_changed; .quad inode_changed
	.reloc ., R_X86_64_SIZE32, inode_changed; .int 0
	.int 0x9b3e694
	.quad 0 /* index: 1914 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1915 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1916 /* index: 1916 */
	.weak x86_fsgsbase_patch; .quad x86_fsgsbase_patch
	.reloc ., R_X86_64_SIZE32, x86_fsgsbase_patch; .int 0
	.int 0x534c7d8
	.quad 0 /* index: 1917 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1918 /* index: 1918 */
	.weak sys_munlockall; .quad sys_munlockall
	.reloc ., R_X86_64_SIZE32, sys_munlockall; .int 0
	.int 0x3d05a2c
	.quad .Lname1919 /* index: 1919 */
	.weak task_wake; .quad task_wake
	.reloc ., R_X86_64_SIZE32, task_wake; .int 0
	.int 0xa16ae95
	.quad 0 /* index: 1920 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1921 /* index: 1921 */
	.weak sys32_inotify_init1; .quad sys32_inotify_init1
	.reloc ., R_X86_64_SIZE32, sys32_inotify_init1; .int 0
	.int 0xc109781
	.quad 0 /* index: 1922 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1923 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1924 /* index: 1924 */
	.weak sys32_ppoll64; .quad sys32_ppoll64
	.reloc ., R_X86_64_SIZE32, sys32_ppoll64; .int 0
	.int 0xc744784
	.quad .Lname1925 /* index: 1925 */
	.weak debuginfo_cu_parser_loadattr_inlined_subroutine; .quad debuginfo_cu_parser_loadattr_inlined_subroutine
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_inlined_subroutine; .int 0
	.int 0x75785
	.quad 0 /* index: 1926 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1927 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1928 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1929 /* index: 1929 */
	.weak sys32_recvmmsg64; .quad sys32_recvmmsg64
	.reloc ., R_X86_64_SIZE32, sys32_recvmmsg64; .int 0
	.int 0xbc5a154
	.quad 0 /* index: 1930 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1931 /* index: 1931 */
	.weak x86_sysroute0_asm32_sysenter; .quad x86_sysroute0_asm32_sysenter
	.reloc ., R_X86_64_SIZE32, x86_sysroute0_asm32_sysenter; .int 0
	.int 0x4836d52
	.quad .Lname1932 /* index: 1932 */
	.weak memcpyl; .quad memcpyl
	.reloc ., R_X86_64_SIZE32, memcpyl; .int 0
	.int 0x3c3a78c
	.quad .Lname1933 /* index: 1933 */
	.weak sys32_chown32; .quad sys32_chown32
	.reloc ., R_X86_64_SIZE32, sys32_chown32; .int 0
	.int 0x2f0c942
	.quad .Lname1934 /* index: 1934 */
	.weak sys32_fanotify_init; .quad sys32_fanotify_init
	.reloc ., R_X86_64_SIZE32, sys32_fanotify_init; .int 0
	.int 0xa7707d4
	.quad .Lname1935 /* index: 1935 */
	.weak sys32_flock; .quad sys32_flock
	.reloc ., R_X86_64_SIZE32, sys32_flock; .int 0
	.int 0x82833fb
	.quad 0 /* index: 1936 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1937 /* index: 1937 */
	.weak vsprintf_s; .quad vsprintf_s
	.reloc ., R_X86_64_SIZE32, vsprintf_s; .int 0
	.int 0x9027213
	.quad 0 /* index: 1938 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1939 /* index: 1939 */
	.weak sys_mq_notify; .quad sys_mq_notify
	.reloc ., R_X86_64_SIZE32, sys_mq_notify; .int 0
	.int 0xf5fcbf9
	.quad .Lname1940 /* index: 1940 */
	.weak sys_pwrite64; .quad sys_pwrite64
	.reloc ., R_X86_64_SIZE32, sys_pwrite64; .int 0
	.int 0x9403ee4
	.quad .Lname1941 /* index: 1941 */
	.weak block_device_lookup_name; .quad block_device_lookup_name
	.reloc ., R_X86_64_SIZE32, block_device_lookup_name; .int 0
	.int 0x63c9795
	.quad .Lname1942 /* index: 1942 */
	.weak addr2line_vprintf; .quad addr2line_vprintf
	.reloc ., R_X86_64_SIZE32, addr2line_vprintf; .int 0
	.int 0x4312796
	.quad 0 /* index: 1943 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1944 /* index: 1944 */
	.weak sys32_sched_setscheduler; .quad sys32_sched_setscheduler
	.reloc ., R_X86_64_SIZE32, sys32_sched_setscheduler; .int 0
	.int 0x90e9672
	.quad .Lname1945 /* index: 1945 */
	.weak heap_free_untraced; .quad heap_free_untraced
	.reloc ., R_X86_64_SIZE32, heap_free_untraced; .int 0
	.int 0xed84944
	.quad .Lname1946 /* index: 1946 */
	.weak sys_setpriority; .quad sys_setpriority
	.reloc ., R_X86_64_SIZE32, sys_setpriority; .int 0
	.int 0x1af40c9
	.quad .Lname1947 /* index: 1947 */
	.weak sys_getrlimit; .quad sys_getrlimit
	.reloc ., R_X86_64_SIZE32, sys_getrlimit; .int 0
	.int 0x9bbfb4
	.quad .Lname1948 /* index: 1948 */
	.weak __afail; .quad __afail
	.reloc ., R_X86_64_SIZE32, __afail; .int 0
	.int 0x557c79c
	.quad 0 /* index: 1949 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1950 /* index: 1950 */
	.weak mempatw; .quad mempatw
	.reloc ., R_X86_64_SIZE32, mempatw; .int 0
	.int 0x3c468c7
	.quad .Lname1951 /* index: 1951 */
	.weak sys_vmsplice; .quad sys_vmsplice
	.reloc ., R_X86_64_SIZE32, sys_vmsplice; .int 0
	.int 0x317b945
	.quad .Lname1952 /* index: 1952 */
	.weak sys_vhangup; .quad sys_vhangup
	.reloc ., R_X86_64_SIZE32, sys_vhangup; .int 0
	.int 0xc9d47a0
	.quad 0 /* index: 1953 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1954 /* index: 1954 */
	.weak dbg_printer; .quad dbg_printer
	.reloc ., R_X86_64_SIZE32, dbg_printer; .int 0
	.int 0x7e6d7a2
	.quad .Lname1955 /* index: 1955 */
	.weak sys_mlock; .quad sys_mlock
	.reloc ., R_X86_64_SIZE32, sys_mlock; .int 0
	.int 0x9646e9b
	.quad .Lname1956 /* index: 1956 */
	.weak sigmask_check_after_except; .quad sigmask_check_after_except
	.reloc ., R_X86_64_SIZE32, sigmask_check_after_except; .int 0
	.int 0xace07a4
	.quad .Lname1957 /* index: 1957 */
	.weak kernel_debugtrap_r_kcpustate; .quad kernel_debugtrap_r_kcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_kcpustate; .int 0
	.int 0xed517a5
	.quad 0 /* index: 1958 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1959 /* index: 1959 */
	.weak x86_userexcept_unwind; .quad x86_userexcept_unwind
	.reloc ., R_X86_64_SIZE32, x86_userexcept_unwind; .int 0
	.int 0x64100f4
	.quad 0 /* index: 1960 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1961 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1962 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1963 /* index: 1963 */
	.weak sys_pread64; .quad sys_pread64
	.reloc ., R_X86_64_SIZE32, sys_pread64; .int 0
	.int 0x7f07ef4
	.quad .Lname1964 /* index: 1964 */
	.weak sys_sync_file_range; .quad sys_sync_file_range
	.reloc ., R_X86_64_SIZE32, sys_sync_file_range; .int 0
	.int 0x6f4e265
	.quad .Lname1965 /* index: 1965 */
	.weak ttybase_device_cinit; .quad ttybase_device_cinit
	.reloc ., R_X86_64_SIZE32, ttybase_device_cinit; .int 0
	.int 0x50dc6b4
	.quad .Lname1966 /* index: 1966 */
	.weak sighand_default_action; .quad sighand_default_action
	.reloc ., R_X86_64_SIZE32, sighand_default_action; .int 0
	.int 0x3117ae
	.quad 0 /* index: 1967 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1968 /* index: 1968 */
	.weak vpage_alloc_untraced_nx; .quad vpage_alloc_untraced_nx
	.reloc ., R_X86_64_SIZE32, vpage_alloc_untraced_nx; .int 0
	.int 0x3daa958
	.quad 0 /* index: 1969 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1970 /* index: 1970 */
	.weak unicode_8to32; .quad unicode_8to32
	.reloc ., R_X86_64_SIZE32, unicode_8to32; .int 0
	.int 0x76017b2
	.quad .Lname1971 /* index: 1971 */
	.weak path_alloc; .quad path_alloc
	.reloc ., R_X86_64_SIZE32, path_alloc; .int 0
	.int 0xe515bf3
	.quad .Lname1972 /* index: 1972 */
	.weak sys32_fcntl64; .quad sys32_fcntl64
	.reloc ., R_X86_64_SIZE32, sys32_fcntl64; .int 0
	.int 0x7a3c7b4
	.quad .Lname1973 /* index: 1973 */
	.weak cmdline_decode; .quad cmdline_decode
	.reloc ., R_X86_64_SIZE32, cmdline_decode; .int 0
	.int 0x618a7b5
	.quad .Lname1974 /* index: 1974 */
	.weak sys32_process_vm_readv; .quad sys32_process_vm_readv
	.reloc ., R_X86_64_SIZE32, sys32_process_vm_readv; .int 0
	.int 0xe23d7b6
	.quad .Lname1975 /* index: 1975 */
	.weak page_cfree; .quad page_cfree
	.reloc ., R_X86_64_SIZE32, page_cfree; .int 0
	.int 0xb5ebf65
	.quad 0 /* index: 1976 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1977 /* index: 1977 */
	.weak getreg_ucpustate; .quad getreg_ucpustate
	.reloc ., R_X86_64_SIZE32, getreg_ucpustate; .int 0
	.int 0xf711fb5
	.quad 0 /* index: 1978 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1979 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1980 /* index: 1980 */
	.weak sys_readv; .quad sys_readv
	.reloc ., R_X86_64_SIZE32, sys_readv; .int 0
	.int 0x968ccb6
	.quad 0 /* index: 1981 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1982 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1983 /* index: 1983 */
	.weak kernel_panic_kcpustate; .quad kernel_panic_kcpustate
	.reloc ., R_X86_64_SIZE32, kernel_panic_kcpustate; .int 0
	.int 0x78a93f5
	.quad .Lname1984 /* index: 1984 */
	.weak sys_getpgrp; .quad sys_getpgrp
	.reloc ., R_X86_64_SIZE32, sys_getpgrp; .int 0
	.int 0xdb067c0
	.quad 0 /* index: 1985 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1986 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1987 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1988 /* index: 1988 */
	.weak pci_list; .quad pci_list
	.reloc ., R_X86_64_SIZE32, pci_list; .int 0
	.int 0x9f637c4
	.quad .Lname1989 /* index: 1989 */
	.weak block_device_partition_write; .quad block_device_partition_write
	.reloc ., R_X86_64_SIZE32, block_device_partition_write; .int 0
	.int 0x5487c5
	.quad .Lname1990 /* index: 1990 */
	.weak sys_readlink; .quad sys_readlink
	.reloc ., R_X86_64_SIZE32, sys_readlink; .int 0
	.int 0xccbbacb
	.quad 0 /* index: 1991 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1992 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1993 /* index: 1993 */
	.weak krealloc_nx; .quad krealloc_nx
	.reloc ., R_X86_64_SIZE32, krealloc_nx; .int 0
	.int 0x3671fd8
	.quad 0 /* index: 1994 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1995 /* index: 1995 */
	.weak sys32_rt_sigprocmask; .quad sys32_rt_sigprocmask
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigprocmask; .int 0
	.int 0x35747cb
	.quad 0 /* index: 1996 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 1997 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname1998 /* index: 1998 */
	.weak sys_swapon; .quad sys_swapon
	.reloc ., R_X86_64_SIZE32, sys_swapon; .int 0
	.int 0x6aa37ce
	.quad 0 /* index: 1999 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2000 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2001 /* index: 2001 */
	.weak handle_get_path; .quad handle_get_path
	.reloc ., R_X86_64_SIZE32, handle_get_path; .int 0
	.int 0x834b3f8
	.quad 0 /* index: 2002 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2003 /* index: 2003 */
	.weak sys32_getdents; .quad sys32_getdents
	.reloc ., R_X86_64_SIZE32, sys32_getdents; .int 0
	.int 0xccc47d3
	.quad .Lname2004 /* index: 2004 */
	.weak instruction_pred; .quad instruction_pred
	.reloc ., R_X86_64_SIZE32, instruction_pred; .int 0
	.int 0xfbad7d4
	.quad .Lname2005 /* index: 2005 */
	.weak ramfs_regular_type; .quad ramfs_regular_type
	.reloc ., R_X86_64_SIZE32, ramfs_regular_type; .int 0
	.int 0x98577d5
	.quad .Lname2006 /* index: 2006 */
	.weak system_trimheaps; .quad system_trimheaps
	.reloc ., R_X86_64_SIZE32, system_trimheaps; .int 0
	.int 0x6f86353
	.quad .Lname2007 /* index: 2007 */
	.weak dbg_applyview; .quad dbg_applyview
	.reloc ., R_X86_64_SIZE32, dbg_applyview; .int 0
	.int 0xdcd97d7
	.quad .Lname2008 /* index: 2008 */
	.weak kmalloc_nx; .quad kmalloc_nx
	.reloc ., R_X86_64_SIZE32, kmalloc_nx; .int 0
	.int 0x332b7d8
	.quad .Lname2009 /* index: 2009 */
	.weak sys32_lseek64; .quad sys32_lseek64
	.reloc ., R_X86_64_SIZE32, sys32_lseek64; .int 0
	.int 0x89dd6a4
	.quad 0 /* index: 2010 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2011 /* index: 2011 */
	.weak vm_memset; .quad vm_memset
	.reloc ., R_X86_64_SIZE32, vm_memset; .int 0
	.int 0x63c34f4
	.quad 0 /* index: 2012 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2013 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2014 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2015 /* index: 2015 */
	.weak register_filesystem_type; .quad register_filesystem_type
	.reloc ., R_X86_64_SIZE32, register_filesystem_type; .int 0
	.int 0x5be16a5
	.quad .Lname2016 /* index: 2016 */
	.weak regdump_cr0; .quad regdump_cr0
	.reloc ., R_X86_64_SIZE32, regdump_cr0; .int 0
	.int 0xc3ee7e0
	.quad 0 /* index: 2017 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2018 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2019 /* index: 2019 */
	.weak superblock_sync; .quad superblock_sync
	.reloc ., R_X86_64_SIZE32, superblock_sync; .int 0
	.int 0xdfa7e3
	.quad .Lname2020 /* index: 2020 */
	.weak ansitty_device_cinit; .quad ansitty_device_cinit
	.reloc ., R_X86_64_SIZE32, ansitty_device_cinit; .int 0
	.int 0xb5597e4
	.quad .Lname2021 /* index: 2021 */
	.weak pci_getclassname; .quad pci_getclassname
	.reloc ., R_X86_64_SIZE32, pci_getclassname; .int 0
	.int 0xd7387e5
	.quad .Lname2022 /* index: 2022 */
	.weak vmb_getnodeof; .quad vmb_getnodeof
	.reloc ., R_X86_64_SIZE32, vmb_getnodeof; .int 0
	.int 0x88df7e6
	.quad 0 /* index: 2023 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2024 /* index: 2024 */
	.weak character_device_lookup_nx; .quad character_device_lookup_nx
	.reloc ., R_X86_64_SIZE32, character_device_lookup_nx; .int 0
	.int 0xab4d7e8
	.quad .Lname2025 /* index: 2025 */
	.weak sys__sysctl; .quad sys__sysctl
	.reloc ., R_X86_64_SIZE32, sys__sysctl; .int 0
	.int 0x6eb93fc
	.quad 0 /* index: 2026 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2027 /* index: 2027 */
	.weak pidns_lookup_task; .quad pidns_lookup_task
	.reloc ., R_X86_64_SIZE32, pidns_lookup_task; .int 0
	.int 0x57317eb
	.quad 0 /* index: 2028 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2029 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2030 /* index: 2030 */
	.weak vm_datapart_haschanged; .quad vm_datapart_haschanged
	.reloc ., R_X86_64_SIZE32, vm_datapart_haschanged; .int 0
	.int 0xad0f0f4
	.quad .Lname2031 /* index: 2031 */
	.weak swap_free; .quad swap_free
	.reloc ., R_X86_64_SIZE32, swap_free; .int 0
	.int 0x865a265
	.quad .Lname2032 /* index: 2032 */
	.weak unwind_setreg_scpustate; .quad unwind_setreg_scpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_scpustate; .int 0
	.int 0xb8d03b5
	.quad .Lname2033 /* index: 2033 */
	.weak this_exception_data; .quad this_exception_data
	.reloc ., R_X86_64_SIZE32, this_exception_data; .int 0
	.int 0x26947f1
	.quad 0 /* index: 2034 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2035 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2036 /* index: 2036 */
	.weak inode_chmod; .quad inode_chmod
	.reloc ., R_X86_64_SIZE32, inode_chmod; .int 0
	.int 0xb29c7f4
	.quad .Lname2037 /* index: 2037 */
	.weak thiscpu_x86_iobnode; .quad thiscpu_x86_iobnode
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_iobnode; .int 0
	.int 0xfc477f5
	.quad 0 /* index: 2038 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2039 /* index: 2039 */
	.weak sys32_lookup_dcookie; .quad sys32_lookup_dcookie
	.reloc ., R_X86_64_SIZE32, sys32_lookup_dcookie; .int 0
	.int 0xce22605
	.quad 0 /* index: 2040 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2041 /* index: 2041 */
	.weak sys32_getgid; .quad sys32_getgid
	.reloc ., R_X86_64_SIZE32, sys32_getgid; .int 0
	.int 0x26ccb74
	.quad 0 /* index: 2042 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2043 /* index: 2043 */
	.weak thisvm_execinfo; .quad thisvm_execinfo
	.reloc ., R_X86_64_SIZE32, thisvm_execinfo; .int 0
	.int 0xe14abff
	.quad 0 /* index: 2044 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2045 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2046 /* index: 2046 */
	.weak superblock_nodeslock_upgrade; .quad superblock_nodeslock_upgrade
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_upgrade; .int 0
	.int 0xa6ee605
	.quad 0 /* index: 2047 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2048 /* index: 2048 */
	.weak thiscpu_x86_ioperm_bitmap; .quad thiscpu_x86_ioperm_bitmap
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_ioperm_bitmap; .int 0
	.int 0xa8d5800
	.quad .Lname2049 /* index: 2049 */
	.weak mempmoveupq; .quad mempmoveupq
	.reloc ., R_X86_64_SIZE32, mempmoveupq; .int 0
	.int 0x41f0801
	.quad 0 /* index: 2050 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2051 /* index: 2051 */
	.weak block_device_awritev_phys; .quad block_device_awritev_phys
	.reloc ., R_X86_64_SIZE32, block_device_awritev_phys; .int 0
	.int 0xad18803
	.quad .Lname2052 /* index: 2052 */
	.weak handle_typekind; .quad handle_typekind
	.reloc ., R_X86_64_SIZE32, handle_typekind; .int 0
	.int 0x4dac804
	.quad .Lname2053 /* index: 2053 */
	.weak block_device_awrite; .quad block_device_awrite
	.reloc ., R_X86_64_SIZE32, block_device_awrite; .int 0
	.int 0x677e805
	.quad .Lname2054 /* index: 2054 */
	.weak __vsnprintf; .quad __vsnprintf
	.reloc ., R_X86_64_SIZE32, __vsnprintf; .int 0
	.int 0x51da806
	.quad .Lname2055 /* index: 2055 */
	.weak mempmoveupw; .quad mempmoveupw
	.reloc ., R_X86_64_SIZE32, mempmoveupw; .int 0
	.int 0x41f0807
	.quad 0 /* index: 2056 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2057 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2058 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2059 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2060 /* index: 2060 */
	.weak sys32_name_to_handle_at; .quad sys32_name_to_handle_at
	.reloc ., R_X86_64_SIZE32, sys32_name_to_handle_at; .int 0
	.int 0xa1e8e34
	.quad .Lname2061 /* index: 2061 */
	.weak sys32_bpf; .quad sys32_bpf
	.reloc ., R_X86_64_SIZE32, sys32_bpf; .int 0
	.int 0x6682266
	.quad .Lname2062 /* index: 2062 */
	.weak sys_shmget; .quad sys_shmget
	.reloc ., R_X86_64_SIZE32, sys_shmget; .int 0
	.int 0x69a8d54
	.quad 0 /* index: 2063 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2064 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2065 /* index: 2065 */
	.weak sys_gettid; .quad sys_gettid
	.reloc ., R_X86_64_SIZE32, sys_gettid; .int 0
	.int 0x5db0a64
	.quad 0 /* index: 2066 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2067 /* index: 2067 */
	.weak sys_migrate_pages; .quad sys_migrate_pages
	.reloc ., R_X86_64_SIZE32, sys_migrate_pages; .int 0
	.int 0xae3fc03
	.quad .Lname2068 /* index: 2068 */
	.weak keyboard_device_read; .quad keyboard_device_read
	.reloc ., R_X86_64_SIZE32, keyboard_device_read; .int 0
	.int 0xf151814
	.quad .Lname2069 /* index: 2069 */
	.weak cred_require_resource; .quad cred_require_resource
	.reloc ., R_X86_64_SIZE32, cred_require_resource; .int 0
	.int 0xd489815
	.quad 0 /* index: 2070 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2071 /* index: 2071 */
	.weak vm_readphysw; .quad vm_readphysw
	.reloc ., R_X86_64_SIZE32, vm_readphysw; .int 0
	.int 0x65a817
	.quad .Lname2072 /* index: 2072 */
	.weak heap_realign_untraced_nx; .quad heap_realign_untraced_nx
	.reloc ., R_X86_64_SIZE32, heap_realign_untraced_nx; .int 0
	.int 0x9ac7818
	.quad .Lname2073 /* index: 2073 */
	.weak sys32_klstat; .quad sys32_klstat
	.reloc ., R_X86_64_SIZE32, sys32_klstat; .int 0
	.int 0x3b3cc04
	.quad .Lname2074 /* index: 2074 */
	.weak this_tid_address; .quad this_tid_address
	.reloc ., R_X86_64_SIZE32, this_tid_address; .int 0
	.int 0xec6dbf3
	.quad .Lname2075 /* index: 2075 */
	.weak vm_protect; .quad vm_protect
	.reloc ., R_X86_64_SIZE32, vm_protect; .int 0
	.int 0x79178c4
	.quad .Lname2076 /* index: 2076 */
	.weak json_parser_getbool; .quad json_parser_getbool
	.reloc ., R_X86_64_SIZE32, json_parser_getbool; .int 0
	.int 0x4f5181c
	.quad .Lname2077 /* index: 2077 */
	.weak aio_pbuffer_copytomem; .quad aio_pbuffer_copytomem
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copytomem; .int 0
	.int 0xfaa081d
	.quad .Lname2078 /* index: 2078 */
	.weak sys32_timer_settime; .quad sys32_timer_settime
	.reloc ., R_X86_64_SIZE32, sys32_timer_settime; .int 0
	.int 0xbce2045
	.quad .Lname2079 /* index: 2079 */
	.weak unwind; .quad unwind
	.reloc ., R_X86_64_SIZE32, unwind; .int 0
	.int 0x7c5e044
	.quad .Lname2080 /* index: 2080 */
	.weak vm_datablock_writep; .quad vm_datablock_writep
	.reloc ., R_X86_64_SIZE32, vm_datablock_writep; .int 0
	.int 0xc21f820
	.quad 0 /* index: 2081 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2082 /* index: 2082 */
	.weak handle_type_db; .quad handle_type_db
	.reloc ., R_X86_64_SIZE32, handle_type_db; .int 0
	.int 0x44d9822
	.quad .Lname2083 /* index: 2083 */
	.weak thiscpu_x86_cpufeatures; .quad thiscpu_x86_cpufeatures
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_cpufeatures; .int 0
	.int 0x9d02823
	.quad .Lname2084 /* index: 2084 */
	.weak rwlock_read; .quad rwlock_read
	.reloc ., R_X86_64_SIZE32, rwlock_read; .int 0
	.int 0xa8f6824
	.quad .Lname2085 /* index: 2085 */
	.weak pidns_tryservice; .quad pidns_tryservice
	.reloc ., R_X86_64_SIZE32, pidns_tryservice; .int 0
	.int 0xc581825
	.quad .Lname2086 /* index: 2086 */
	.weak vm_datablock_writev; .quad vm_datablock_writev
	.reloc ., R_X86_64_SIZE32, vm_datablock_writev; .int 0
	.int 0xc21f826
	.quad .Lname2087 /* index: 2087 */
	.weak vpage_realloc_untraced; .quad vpage_realloc_untraced
	.reloc ., R_X86_64_SIZE32, vpage_realloc_untraced; .int 0
	.int 0x51c9214
	.quad .Lname2088 /* index: 2088 */
	.weak sys32_pwrite64; .quad sys32_pwrite64
	.reloc ., R_X86_64_SIZE32, sys32_pwrite64; .int 0
	.int 0xef62954
	.quad 0 /* index: 2089 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2090 /* index: 2090 */
	.weak vm_datapart_write_unsafe; .quad vm_datapart_write_unsafe
	.reloc ., R_X86_64_SIZE32, vm_datapart_write_unsafe; .int 0
	.int 0xd1b4e55
	.quad .Lname2091 /* index: 2091 */
	.weak vsprintf; .quad vsprintf
	.reloc ., R_X86_64_SIZE32, vsprintf; .int 0
	.int 0xa790276
	.quad .Lname2092 /* index: 2092 */
	.weak vm_readphysl; .quad vm_readphysl
	.reloc ., R_X86_64_SIZE32, vm_readphysl; .int 0
	.int 0x65a82c
	.quad .Lname2093 /* index: 2093 */
	.weak x86_syscall32_sysenter; .quad x86_syscall32_sysenter
	.reloc ., R_X86_64_SIZE32, x86_syscall32_sysenter; .int 0
	.int 0x4db3eb2
	.quad 0 /* index: 2094 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2095 /* index: 2095 */
	.weak sys_getrusage; .quad sys_getrusage
	.reloc ., R_X86_64_SIZE32, sys_getrusage; .int 0
	.int 0x95ca65
	.quad 0 /* index: 2096 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2097 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2098 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2099 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2100 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2101 /* index: 2101 */
	.weak dbg_enter_fcpustate; .quad dbg_enter_fcpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_fcpustate; .int 0
	.int 0x781a835
	.quad .Lname2102 /* index: 2102 */
	.weak sys_msgrcv; .quad sys_msgrcv
	.reloc ., R_X86_64_SIZE32, sys_msgrcv; .int 0
	.int 0x64e5836
	.quad 0 /* index: 2103 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2104 /* index: 2104 */
	.weak format_width; .quad format_width
	.reloc ., R_X86_64_SIZE32, format_width; .int 0
	.int 0xbb6838
	.quad .Lname2105 /* index: 2105 */
	.weak ringbuffer_read; .quad ringbuffer_read
	.reloc ., R_X86_64_SIZE32, ringbuffer_read; .int 0
	.int 0x8bf4eb4
	.quad 0 /* index: 2106 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2107 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2108 /* index: 2108 */
	.weak sys32_sendmsg; .quad sys32_sendmsg
	.reloc ., R_X86_64_SIZE32, sys32_sendmsg; .int 0
	.int 0x2c2dc87
	.quad .Lname2109 /* index: 2109 */
	.weak sys32_settimeofday64; .quad sys32_settimeofday64
	.reloc ., R_X86_64_SIZE32, sys32_settimeofday64; .int 0
	.int 0x9160e34
	.quad .Lname2110 /* index: 2110 */
	.weak mall_untrace_n; .quad mall_untrace_n
	.reloc ., R_X86_64_SIZE32, mall_untrace_n; .int 0
	.int 0x3b5f83e
	.quad .Lname2111 /* index: 2111 */
	.weak memmove; .quad memmove
	.reloc ., R_X86_64_SIZE32, memmove; .int 0
	.int 0x3c446b5
	.quad .Lname2112 /* index: 2112 */
	.weak pagedir_translate_p; .quad pagedir_translate_p
	.reloc ., R_X86_64_SIZE32, pagedir_translate_p; .int 0
	.int 0xc3e9840
	.quad 0 /* index: 2113 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2114 /* index: 2114 */
	.weak isr_unregister; .quad isr_unregister
	.reloc ., R_X86_64_SIZE32, isr_unregister; .int 0
	.int 0x1666842
	.quad .Lname2115 /* index: 2115 */
	.weak dump_branch_stats; .quad dump_branch_stats
	.reloc ., R_X86_64_SIZE32, dump_branch_stats; .int 0
	.int 0x9996843
	.quad .Lname2116 /* index: 2116 */
	.weak json_writer_putint64; .quad json_writer_putint64
	.reloc ., R_X86_64_SIZE32, json_writer_putint64; .int 0
	.int 0x6687844
	.quad .Lname2117 /* index: 2117 */
	.weak kernel_vpanic_icpustate; .quad kernel_vpanic_icpustate
	.reloc ., R_X86_64_SIZE32, kernel_vpanic_icpustate; .int 0
	.int 0xf5ae845
	.quad .Lname2118 /* index: 2118 */
	.weak sys_get_exception_handler; .quad sys_get_exception_handler
	.reloc ., R_X86_64_SIZE32, sys_get_exception_handler; .int 0
	.int 0xa9f6ae2
	.quad .Lname2119 /* index: 2119 */
	.weak vfs_kernel; .quad vfs_kernel
	.reloc ., R_X86_64_SIZE32, vfs_kernel; .int 0
	.int 0x61b592c
	.quad 0 /* index: 2120 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2121 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2122 /* index: 2122 */
	.weak sys32_fsmode; .quad sys32_fsmode
	.reloc ., R_X86_64_SIZE32, sys32_fsmode; .int 0
	.int 0x26a6325
	.quad 0 /* index: 2123 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2124 /* index: 2124 */
	.weak ansitty_device_ioctl; .quad ansitty_device_ioctl
	.reloc ., R_X86_64_SIZE32, ansitty_device_ioctl; .int 0
	.int 0xb54284c
	.quad .Lname2125 /* index: 2125 */
	.weak task_gethandlemanager; .quad task_gethandlemanager
	.reloc ., R_X86_64_SIZE32, task_gethandlemanager; .int 0
	.int 0x7156962
	.quad 0 /* index: 2126 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2127 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2128 /* index: 2128 */
	.weak pagedir_maphint_p; .quad pagedir_maphint_p
	.reloc ., R_X86_64_SIZE32, pagedir_maphint_p; .int 0
	.int 0xd9e6850
	.quad 0 /* index: 2129 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2130 /* index: 2130 */
	.weak cpu_enable_preemptive_interrupts_nopr; .quad cpu_enable_preemptive_interrupts_nopr
	.reloc ., R_X86_64_SIZE32, cpu_enable_preemptive_interrupts_nopr; .int 0
	.int 0x746d852
	.quad .Lname2131 /* index: 2131 */
	.weak sys32_clock_getres; .quad sys32_clock_getres
	.reloc ., R_X86_64_SIZE32, sys32_clock_getres; .int 0
	.int 0x7eff853
	.quad .Lname2132 /* index: 2132 */
	.weak dbg_hexedit; .quad dbg_hexedit
	.reloc ., R_X86_64_SIZE32, dbg_hexedit; .int 0
	.int 0xea43854
	.quad .Lname2133 /* index: 2133 */
	.weak dbg_getregbyname; .quad dbg_getregbyname
	.reloc ., R_X86_64_SIZE32, dbg_getregbyname; .int 0
	.int 0x8465855
	.quad 0 /* index: 2134 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2135 /* index: 2135 */
	.weak sys_epoll_wait_old; .quad sys_epoll_wait_old
	.reloc ., R_X86_64_SIZE32, sys_epoll_wait_old; .int 0
	.int 0x6fbd734
	.quad .Lname2136 /* index: 2136 */
	.weak sys_waitid; .quad sys_waitid
	.reloc ., R_X86_64_SIZE32, sys_waitid; .int 0
	.int 0x6d1ba64
	.quad .Lname2137 /* index: 2137 */
	.weak sys_setsid; .quad sys_setsid
	.reloc ., R_X86_64_SIZE32, sys_setsid; .int 0
	.int 0x69b0964
	.quad .Lname2138 /* index: 2138 */
	.weak userkern_segment_vio; .quad userkern_segment_vio
	.reloc ., R_X86_64_SIZE32, userkern_segment_vio; .int 0
	.int 0x1facb9f
	.quad .Lname2139 /* index: 2139 */
	.weak sys32_symlink; .quad sys32_symlink
	.reloc ., R_X86_64_SIZE32, sys32_symlink; .int 0
	.int 0x206485b
	.quad .Lname2140 /* index: 2140 */
	.weak vmb_find_first_node_greater_equal; .quad vmb_find_first_node_greater_equal
	.reloc ., R_X86_64_SIZE32, vmb_find_first_node_greater_equal; .int 0
	.int 0x12eabdc
	.quad 0 /* index: 2141 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2142 /* index: 2142 */
	.weak path_lock_trywrite; .quad path_lock_trywrite
	.reloc ., R_X86_64_SIZE32, path_lock_trywrite; .int 0
	.int 0x3c4845
	.quad .Lname2143 /* index: 2143 */
	.weak debuginfo_print_value; .quad debuginfo_print_value
	.reloc ., R_X86_64_SIZE32, debuginfo_print_value; .int 0
	.int 0x8b66165
	.quad .Lname2144 /* index: 2144 */
	.weak x86_userexcept_unwind_interrupt_kernel_esp; .quad x86_userexcept_unwind_interrupt_kernel_esp
	.reloc ., R_X86_64_SIZE32, x86_userexcept_unwind_interrupt_kernel_esp; .int 0
	.int 0x69cd860
	.quad 0 /* index: 2145 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2146 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2147 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2148 /* index: 2148 */
	.weak json_parser_rewind; .quad json_parser_rewind
	.reloc ., R_X86_64_SIZE32, json_parser_rewind; .int 0
	.int 0x71f2864
	.quad .Lname2149 /* index: 2149 */
	.weak x86_dbg_exitstate; .quad x86_dbg_exitstate
	.reloc ., R_X86_64_SIZE32, x86_dbg_exitstate; .int 0
	.int 0xa424865
	.quad .Lname2150 /* index: 2150 */
	.weak sys32_pread64f; .quad sys32_pread64f
	.reloc ., R_X86_64_SIZE32, sys32_pread64f; .int 0
	.int 0x8d1f866
	.quad .Lname2151 /* index: 2151 */
	.weak handle_installxchg; .quad handle_installxchg
	.reloc ., R_X86_64_SIZE32, handle_installxchg; .int 0
	.int 0xbabf867
	.quad .Lname2152 /* index: 2152 */
	.weak x86_idt_ptr; .quad x86_idt_ptr
	.reloc ., R_X86_64_SIZE32, x86_idt_ptr; .int 0
	.int 0xfc3dbe2
	.quad .Lname2153 /* index: 2153 */
	.weak vm_futex_destroy; .quad vm_futex_destroy
	.reloc ., R_X86_64_SIZE32, vm_futex_destroy; .int 0
	.int 0x707a869
	.quad 0 /* index: 2154 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2155 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2156 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2157 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2158 /* index: 2158 */
	.weak x86_syscall_emulate32_sysenter_r; .quad x86_syscall_emulate32_sysenter_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_sysenter_r; .int 0
	.int 0xb5b70d2
	.quad 0 /* index: 2159 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2160 /* index: 2160 */
	.weak pagedir_unmap_p; .quad pagedir_unmap_p
	.reloc ., R_X86_64_SIZE32, pagedir_unmap_p; .int 0
	.int 0x808f870
	.quad .Lname2161 /* index: 2161 */
	.weak memcpyq; .quad memcpyq
	.reloc ., R_X86_64_SIZE32, memcpyq; .int 0
	.int 0x3c3a871
	.quad 0 /* index: 2162 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2163 /* index: 2163 */
	.weak block_device_partition_write_phys; .quad block_device_partition_write_phys
	.reloc ., R_X86_64_SIZE32, block_device_partition_write_phys; .int 0
	.int 0xcb32873
	.quad .Lname2164 /* index: 2164 */
	.weak superblock_mountlock_endread; .quad superblock_mountlock_endread
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_endread; .int 0
	.int 0x34af874
	.quad .Lname2165 /* index: 2165 */
	.weak disasm_single; .quad disasm_single
	.reloc ., R_X86_64_SIZE32, disasm_single; .int 0
	.int 0xd97c875
	.quad .Lname2166 /* index: 2166 */
	.weak cpu_schedule_idle_job_and_incref; .quad cpu_schedule_idle_job_and_incref
	.reloc ., R_X86_64_SIZE32, cpu_schedule_idle_job_and_incref; .int 0
	.int 0x33dc876
	.quad .Lname2167 /* index: 2167 */
	.weak memcpyw; .quad memcpyw
	.reloc ., R_X86_64_SIZE32, memcpyw; .int 0
	.int 0x3c3a877
	.quad 0 /* index: 2168 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2169 /* index: 2169 */
	.weak symlink_node_load; .quad symlink_node_load
	.reloc ., R_X86_64_SIZE32, symlink_node_load; .int 0
	.int 0xafa5414
	.quad 0 /* index: 2170 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2171 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2172 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2173 /* index: 2173 */
	.weak sys_sched_setparam; .quad sys_sched_setparam
	.reloc ., R_X86_64_SIZE32, sys_sched_setparam; .int 0
	.int 0x2ed987d
	.quad 0 /* index: 2174 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2175 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2176 /* index: 2176 */
	.weak ttybase_device_owrite; .quad ttybase_device_owrite
	.reloc ., R_X86_64_SIZE32, ttybase_device_owrite; .int 0
	.int 0x12aabf5
	.quad .Lname2177 /* index: 2177 */
	.weak superblock_mountlock_read; .quad superblock_mountlock_read
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_read; .int 0
	.int 0x7331b64
	.quad .Lname2178 /* index: 2178 */
	.weak inode_loadattr; .quad inode_loadattr
	.reloc ., R_X86_64_SIZE32, inode_loadattr; .int 0
	.int 0x203882
	.quad .Lname2179 /* index: 2179 */
	.weak kernel_vpanic; .quad kernel_vpanic
	.reloc ., R_X86_64_SIZE32, kernel_vpanic; .int 0
	.int 0x71f4883
	.quad .Lname2180 /* index: 2180 */
	.weak dbg_pprint; .quad dbg_pprint
	.reloc ., R_X86_64_SIZE32, dbg_pprint; .int 0
	.int 0x6712884
	.quad 0 /* index: 2181 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2182 /* index: 2182 */
	.weak vio_writeq_aligned; .quad vio_writeq_aligned
	.reloc ., R_X86_64_SIZE32, vio_writeq_aligned; .int 0
	.int 0x8f55514
	.quad .Lname2183 /* index: 2183 */
	.weak task_exec_asynchronous_rpc; .quad task_exec_asynchronous_rpc
	.reloc ., R_X86_64_SIZE32, task_exec_asynchronous_rpc; .int 0
	.int 0x1640cf3
	.quad .Lname2184 /* index: 2184 */
	.weak vm_ramfile_type; .quad vm_ramfile_type
	.reloc ., R_X86_64_SIZE32, vm_ramfile_type; .int 0
	.int 0x43f01b5
	.quad 0 /* index: 2185 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2186 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2187 /* index: 2187 */
	.weak vm_clrhwbreak; .quad vm_clrhwbreak
	.reloc ., R_X86_64_SIZE32, vm_clrhwbreak; .int 0
	.int 0x2ec288b
	.quad .Lname2188 /* index: 2188 */
	.weak disasm_print_symbol; .quad disasm_print_symbol
	.reloc ., R_X86_64_SIZE32, disasm_print_symbol; .int 0
	.int 0xbdfb88c
	.quad .Lname2189 /* index: 2189 */
	.weak keyboard_buffer_putkey_nopr; .quad keyboard_buffer_putkey_nopr
	.reloc ., R_X86_64_SIZE32, keyboard_buffer_putkey_nopr; .int 0
	.int 0x2a056c2
	.quad 0 /* index: 2190 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2191 /* index: 2191 */
	.weak dbg_enter_lcpustate_cr; .quad dbg_enter_lcpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_lcpustate_cr; .int 0
	.int 0xb63edb2
	.quad .Lname2192 /* index: 2192 */
	.weak sys_semtimedop; .quad sys_semtimedop
	.reloc ., R_X86_64_SIZE32, sys_semtimedop; .int 0
	.int 0xa752890
	.quad 0 /* index: 2193 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2194 /* index: 2194 */
	.weak directory_mkdir; .quad directory_mkdir
	.reloc ., R_X86_64_SIZE32, directory_mkdir; .int 0
	.int 0x7fac892
	.quad .Lname2195 /* index: 2195 */
	.weak vm_exec; .quad vm_exec
	.reloc ., R_X86_64_SIZE32, vm_exec; .int 0
	.int 0xd35cec3
	.quad .Lname2196 /* index: 2196 */
	.weak terminal_iread; .quad terminal_iread
	.reloc ., R_X86_64_SIZE32, terminal_iread; .int 0
	.int 0xed48894
	.quad .Lname2197 /* index: 2197 */
	.weak dbg_scroll_maxline; .quad dbg_scroll_maxline
	.reloc ., R_X86_64_SIZE32, dbg_scroll_maxline; .int 0
	.int 0xfb22895
	.quad .Lname2198 /* index: 2198 */
	.weak vm_datablock_readv; .quad vm_datablock_readv
	.reloc ., R_X86_64_SIZE32, vm_datablock_readv; .int 0
	.int 0xec43896
	.quad .Lname2199 /* index: 2199 */
	.weak vm_datapart_lock_tryread; .quad vm_datapart_lock_tryread
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_tryread; .int 0
	.int 0x220df34
	.quad .Lname2200 /* index: 2200 */
	.weak task_schedule_user_rpc_nx; .quad task_schedule_user_rpc_nx
	.reloc ., R_X86_64_SIZE32, task_schedule_user_rpc_nx; .int 0
	.int 0xc9bc898
	.quad .Lname2201 /* index: 2201 */
	.weak sys32_getrlimit; .quad sys32_getrlimit
	.reloc ., R_X86_64_SIZE32, sys32_getrlimit; .int 0
	.int 0xdfae6c4
	.quad .Lname2202 /* index: 2202 */
	.weak this_sched_runprv; .quad this_sched_runprv
	.reloc ., R_X86_64_SIZE32, this_sched_runprv; .int 0
	.int 0x794c86
	.quad 0 /* index: 2203 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2204 /* index: 2204 */
	.weak driver_initialize; .quad driver_initialize
	.reloc ., R_X86_64_SIZE32, driver_initialize; .int 0
	.int 0x6da66c5
	.quad .Lname2205 /* index: 2205 */
	.weak disasm; .quad disasm
	.reloc ., R_X86_64_SIZE32, disasm; .int 0
	.int 0x6b0989d
	.quad .Lname2206 /* index: 2206 */
	.weak vm_syncall_locked; .quad vm_syncall_locked
	.reloc ., R_X86_64_SIZE32, vm_syncall_locked; .int 0
	.int 0x621d404
	.quad .Lname2207 /* index: 2207 */
	.weak dbg_vline; .quad dbg_vline
	.reloc ., R_X86_64_SIZE32, dbg_vline; .int 0
	.int 0xd6d46c5
	.quad .Lname2208 /* index: 2208 */
	.weak pagedir_haschanged_p; .quad pagedir_haschanged_p
	.reloc ., R_X86_64_SIZE32, pagedir_haschanged_p; .int 0
	.int 0x67e98a0
	.quad .Lname2209 /* index: 2209 */
	.weak memrchrq; .quad memrchrq
	.reloc ., R_X86_64_SIZE32, memrchrq; .int 0
	.int 0xc4898a1
	.quad .Lname2210 /* index: 2210 */
	.weak vio_cmpxchb; .quad vio_cmpxchb
	.reloc ., R_X86_64_SIZE32, vio_cmpxchb; .int 0
	.int 0xa3aecb2
	.quad .Lname2211 /* index: 2211 */
	.weak kernel_debug_sections; .quad kernel_debug_sections
	.reloc ., R_X86_64_SIZE32, kernel_debug_sections; .int 0
	.int 0x97d48a3
	.quad .Lname2212 /* index: 2212 */
	.weak sys_fanotify_init; .quad sys_fanotify_init
	.reloc ., R_X86_64_SIZE32, sys_fanotify_init; .int 0
	.int 0x1d5a8a4
	.quad .Lname2213 /* index: 2213 */
	.weak debuginfo_cu_parser_loadattr_variable; .quad debuginfo_cu_parser_loadattr_variable
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_variable; .int 0
	.int 0xf118a5
	.quad .Lname2214 /* index: 2214 */
	.weak setreg_sfpuenv; .quad setreg_sfpuenv
	.reloc ., R_X86_64_SIZE32, setreg_sfpuenv; .int 0
	.int 0x56f08a6
	.quad .Lname2215 /* index: 2215 */
	.weak memrchrw; .quad memrchrw
	.reloc ., R_X86_64_SIZE32, memrchrw; .int 0
	.int 0xc4898a7
	.quad .Lname2216 /* index: 2216 */
	.weak cpu_private_function_do_finibuf_ex; .quad cpu_private_function_do_finibuf_ex
	.reloc ., R_X86_64_SIZE32, cpu_private_function_do_finibuf_ex; .int 0
	.int 0x28858a8
	.quad 0 /* index: 2217 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2218 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2219 /* index: 2219 */
	.weak zlib_reader_fini; .quad zlib_reader_fini
	.reloc ., R_X86_64_SIZE32, zlib_reader_fini; .int 0
	.int 0x4256b19
	.quad .Lname2220 /* index: 2220 */
	.weak json_writer_putbool; .quad json_writer_putbool
	.reloc ., R_X86_64_SIZE32, json_writer_putbool; .int 0
	.int 0xd6618ac
	.quad .Lname2221 /* index: 2221 */
	.weak rawmemchr; .quad rawmemchr
	.reloc ., R_X86_64_SIZE32, rawmemchr; .int 0
	.int 0xe3c4172
	.quad 0 /* index: 2222 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2223 /* index: 2223 */
	.weak path_lock_end; .quad path_lock_end
	.reloc ., R_X86_64_SIZE32, path_lock_end; .int 0
	.int 0x32bbe24
	.quad 0 /* index: 2224 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2225 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2226 /* index: 2226 */
	.weak vm_datapart_map_ram; .quad vm_datapart_map_ram
	.reloc ., R_X86_64_SIZE32, vm_datapart_map_ram; .int 0
	.int 0x6d95aed
	.quad .Lname2227 /* index: 2227 */
	.weak path_lock_upgrade; .quad path_lock_upgrade
	.reloc ., R_X86_64_SIZE32, path_lock_upgrade; .int 0
	.int 0xa0dac25
	.quad .Lname2228 /* index: 2228 */
	.weak sys_shmdt; .quad sys_shmdt
	.reloc ., R_X86_64_SIZE32, sys_shmdt; .int 0
	.int 0x969a8b4
	.quad .Lname2229 /* index: 2229 */
	.weak getreg_fcpustate; .quad getreg_fcpustate
	.reloc ., R_X86_64_SIZE32, getreg_fcpustate; .int 0
	.int 0xf7128b5
	.quad .Lname2230 /* index: 2230 */
	.weak vm_datapart_write_nopf; .quad vm_datapart_write_nopf
	.reloc ., R_X86_64_SIZE32, vm_datapart_write_nopf; .int 0
	.int 0x9a008b6
	.quad .Lname2231 /* index: 2231 */
	.weak rwlock_reading; .quad rwlock_reading
	.reloc ., R_X86_64_SIZE32, rwlock_reading; .int 0
	.int 0x68208b7
	.quad 0 /* index: 2232 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2233 /* index: 2233 */
	.weak sys32_inotify_init; .quad sys32_inotify_init
	.reloc ., R_X86_64_SIZE32, sys32_inotify_init; .int 0
	.int 0xfc10974
	.quad 0 /* index: 2234 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2235 /* index: 2235 */
	.weak sys_clone; .quad sys_clone
	.reloc ., R_X86_64_SIZE32, sys_clone; .int 0
	.int 0x95a6f45
	.quad .Lname2236 /* index: 2236 */
	.weak memrchrl; .quad memrchrl
	.reloc ., R_X86_64_SIZE32, memrchrl; .int 0
	.int 0xc4898bc
	.quad 0 /* index: 2237 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2238 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2239 /* index: 2239 */
	.weak pidns_trywrite; .quad pidns_trywrite
	.reloc ., R_X86_64_SIZE32, pidns_trywrite; .int 0
	.int 0x7bb2175
	.quad 0 /* index: 2240 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2241 /* index: 2241 */
	.weak mempatq; .quad mempatq
	.reloc ., R_X86_64_SIZE32, mempatq; .int 0
	.int 0x3c468c1
	.quad .Lname2242 /* index: 2242 */
	.weak sys_listxattr; .quad sys_listxattr
	.reloc ., R_X86_64_SIZE32, sys_listxattr; .int 0
	.int 0x1b7e8c2
	.quad .Lname2243 /* index: 2243 */
	.weak error_subclass; .quad error_subclass
	.reloc ., R_X86_64_SIZE32, error_subclass; .int 0
	.int 0x220a8c3
	.quad .Lname2244 /* index: 2244 */
	.weak sys32_mq_timedsend; .quad sys32_mq_timedsend
	.reloc ., R_X86_64_SIZE32, sys32_mq_timedsend; .int 0
	.int 0x4c98c4
	.quad .Lname2245 /* index: 2245 */
	.weak superblock_opennode; .quad superblock_opennode
	.reloc ., R_X86_64_SIZE32, superblock_opennode; .int 0
	.int 0xf25a8c5
	.quad .Lname2246 /* index: 2246 */
	.weak dbg_pprintf; .quad dbg_pprintf
	.reloc ., R_X86_64_SIZE32, dbg_pprintf; .int 0
	.int 0x71288c6
	.quad .Lname2247 /* index: 2247 */
	.weak memlenq; .quad memlenq
	.reloc ., R_X86_64_SIZE32, memlenq; .int 0
	.int 0x3c42c21
	.quad .Lname2248 /* index: 2248 */
	.weak heap_allat_untraced_nx; .quad heap_allat_untraced_nx
	.reloc ., R_X86_64_SIZE32, heap_allat_untraced_nx; .int 0
	.int 0x7a128c8
	.quad 0 /* index: 2249 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2250 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2251 /* index: 2251 */
	.weak sys_capset; .quad sys_capset
	.reloc ., R_X86_64_SIZE32, sys_capset; .int 0
	.int 0x59fc954
	.quad 0 /* index: 2252 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2253 /* index: 2253 */
	.weak sys_mkdirat; .quad sys_mkdirat
	.reloc ., R_X86_64_SIZE32, sys_mkdirat; .int 0
	.int 0x46201e4
	.quad 0 /* index: 2254 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2255 /* index: 2255 */
	.weak sys32_setuid; .quad sys32_setuid
	.reloc ., R_X86_64_SIZE32, sys32_setuid; .int 0
	.int 0x12cdd74
	.quad .Lname2256 /* index: 2256 */
	.weak task_raisesignalthread_nx; .quad task_raisesignalthread_nx
	.reloc ., R_X86_64_SIZE32, task_raisesignalthread_nx; .int 0
	.int 0xc7281a8
	.quad .Lname2257 /* index: 2257 */
	.weak heap_allat_nx; .quad heap_allat_nx
	.reloc ., R_X86_64_SIZE32, heap_allat_nx; .int 0
	.int 0xd910178
	.quad .Lname2258 /* index: 2258 */
	.weak sys32_flistxattr; .quad sys32_flistxattr
	.reloc ., R_X86_64_SIZE32, sys32_flistxattr; .int 0
	.int 0xc3c08d2
	.quad .Lname2259 /* index: 2259 */
	.weak block_device_alloc; .quad block_device_alloc
	.reloc ., R_X86_64_SIZE32, block_device_alloc; .int 0
	.int 0xa69c8d3
	.quad .Lname2260 /* index: 2260 */
	.weak vm_datablock_createpart; .quad vm_datablock_createpart
	.reloc ., R_X86_64_SIZE32, vm_datablock_createpart; .int 0
	.int 0xa4308d4
	.quad .Lname2261 /* index: 2261 */
	.weak ringbuffer_writesome; .quad ringbuffer_writesome
	.reloc ., R_X86_64_SIZE32, ringbuffer_writesome; .int 0
	.int 0xc2778d5
	.quad .Lname2262 /* index: 2262 */
	.weak unicode_readutf16_swap_rev; .quad unicode_readutf16_swap_rev
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_swap_rev; .int 0
	.int 0x561c8d6
	.quad 0 /* index: 2263 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2264 /* index: 2264 */
	.weak dbg_screen_width; .quad dbg_screen_width
	.reloc ., R_X86_64_SIZE32, dbg_screen_width; .int 0
	.int 0x6f1d8d8
	.quad 0 /* index: 2265 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2266 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2267 /* index: 2267 */
	.weak vio_orl; .quad vio_orl
	.reloc ., R_X86_64_SIZE32, vio_orl; .int 0
	.int 0xd0566fc
	.quad .Lname2268 /* index: 2268 */
	.weak mempatl; .quad mempatl
	.reloc ., R_X86_64_SIZE32, mempatl; .int 0
	.int 0x3c468dc
	.quad 0 /* index: 2269 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2270 /* index: 2270 */
	.weak sys32_linux_oldstat; .quad sys32_linux_oldstat
	.reloc ., R_X86_64_SIZE32, sys32_linux_oldstat; .int 0
	.int 0x280c04
	.quad .Lname2271 /* index: 2271 */
	.weak handle_datasize; .quad handle_datasize
	.reloc ., R_X86_64_SIZE32, handle_datasize; .int 0
	.int 0xc1a5c25
	.quad 0 /* index: 2272 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2273 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2274 /* index: 2274 */
	.weak cpu_quantum_reset_nopr; .quad cpu_quantum_reset_nopr
	.reloc ., R_X86_64_SIZE32, cpu_quantum_reset_nopr; .int 0
	.int 0x23f38e2
	.quad .Lname2275 /* index: 2275 */
	.weak inode_read_phys; .quad inode_read_phys
	.reloc ., R_X86_64_SIZE32, inode_read_phys; .int 0
	.int 0x24d78e3
	.quad .Lname2276 /* index: 2276 */
	.weak path_traversefull_at; .quad path_traversefull_at
	.reloc ., R_X86_64_SIZE32, path_traversefull_at; .int 0
	.int 0xde1f0d4
	.quad .Lname2277 /* index: 2277 */
	.weak unwind_getreg_scpustate; .quad unwind_getreg_scpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_scpustate; .int 0
	.int 0xb8c43b5
	.quad 0 /* index: 2278 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2279 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2280 /* index: 2280 */
	.weak unicode_readutf8; .quad unicode_readutf8
	.reloc ., R_X86_64_SIZE32, unicode_readutf8; .int 0
	.int 0x126b8e8
	.quad 0 /* index: 2281 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2282 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2283 /* index: 2283 */
	.weak sys_unshare; .quad sys_unshare
	.reloc ., R_X86_64_SIZE32, sys_unshare; .int 0
	.int 0xc22e1e5
	.quad .Lname2284 /* index: 2284 */
	.weak kernel_debugtraps_install; .quad kernel_debugtraps_install
	.reloc ., R_X86_64_SIZE32, kernel_debugtraps_install; .int 0
	.int 0x1b018ec
	.quad .Lname2285 /* index: 2285 */
	.weak sys_getrandom; .quad sys_getrandom
	.reloc ., R_X86_64_SIZE32, sys_getrandom; .int 0
	.int 0x8f18ed
	.quad .Lname2286 /* index: 2286 */
	.weak vm_memsetphys_onepage; .quad vm_memsetphys_onepage
	.reloc ., R_X86_64_SIZE32, vm_memsetphys_onepage; .int 0
	.int 0x9185a65
	.quad 0 /* index: 2287 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2288 /* index: 2288 */
	.weak kernel_syscall0_iscp; .quad kernel_syscall0_iscp
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_iscp; .int 0
	.int 0x8d958f0
	.quad .Lname2289 /* index: 2289 */
	.weak sys_getpgid; .quad sys_getpgid
	.reloc ., R_X86_64_SIZE32, sys_getpgid; .int 0
	.int 0xdb064a4
	.quad 0 /* index: 2290 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2291 /* index: 2291 */
	.weak dbg_enter_icpustate_c; .quad dbg_enter_icpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_icpustate_c; .int 0
	.int 0x1ab3ed3
	.quad .Lname2292 /* index: 2292 */
	.weak json_parser_init; .quad json_parser_init
	.reloc ., R_X86_64_SIZE32, json_parser_init; .int 0
	.int 0x82478f4
	.quad .Lname2293 /* index: 2293 */
	.weak kernel_debugtrap_scpustate; .quad kernel_debugtrap_scpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_scpustate; .int 0
	.int 0x963b8f5
	.quad 0 /* index: 2294 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2295 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2296 /* index: 2296 */
	.weak sys_inotify_rm_watch; .quad sys_inotify_rm_watch
	.reloc ., R_X86_64_SIZE32, sys_inotify_rm_watch; .int 0
	.int 0x90678f8
	.quad .Lname2297 /* index: 2297 */
	.weak sys32_fchmod; .quad sys32_fchmod
	.reloc ., R_X86_64_SIZE32, sys32_fchmod; .int 0
	.int 0x27996d4
	.quad 0 /* index: 2298 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2299 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2300 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2301 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2302 /* index: 2302 */
	.weak krealign; .quad krealign
	.reloc ., R_X86_64_SIZE32, krealign; .int 0
	.int 0x8b828fe
	.quad 0 /* index: 2303 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2304 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2305 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2306 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2307 /* index: 2307 */
	.weak vm_datablock_debugheap_type; .quad vm_datablock_debugheap_type
	.reloc ., R_X86_64_SIZE32, vm_datablock_debugheap_type; .int 0
	.int 0xb4f91b5
	.quad .Lname2308 /* index: 2308 */
	.weak heap_allat; .quad heap_allat
	.reloc ., R_X86_64_SIZE32, heap_allat; .int 0
	.int 0x652d904
	.quad 0 /* index: 2309 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2310 /* index: 2310 */
	.weak sys32_kreaddirf; .quad sys32_kreaddirf
	.reloc ., R_X86_64_SIZE32, sys32_kreaddirf; .int 0
	.int 0xd12a906
	.quad 0 /* index: 2311 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2312 /* index: 2312 */
	.weak kmalloc_noslab_nx; .quad kmalloc_noslab_nx
	.reloc ., R_X86_64_SIZE32, kmalloc_noslab_nx; .int 0
	.int 0xb0c1908
	.quad .Lname2313 /* index: 2313 */
	.weak sighand_ptr_destroy; .quad sighand_ptr_destroy
	.reloc ., R_X86_64_SIZE32, sighand_ptr_destroy; .int 0
	.int 0xb50d909
	.quad .Lname2314 /* index: 2314 */
	.weak sys32_truncate64; .quad sys32_truncate64
	.reloc ., R_X86_64_SIZE32, sys32_truncate64; .int 0
	.int 0x219a174
	.quad 0 /* index: 2315 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2316 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2317 /* index: 2317 */
	.weak task_start; .quad task_start
	.reloc ., R_X86_64_SIZE32, task_start; .int 0
	.int 0x16d0034
	.quad 0 /* index: 2318 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2319 /* index: 2319 */
	.weak kmalloc_usable_size; .quad kmalloc_usable_size
	.reloc ., R_X86_64_SIZE32, kmalloc_usable_size; .int 0
	.int 0xa0245b5
	.quad 0 /* index: 2320 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2321 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2322 /* index: 2322 */
	.weak sys_epoll_create; .quad sys_epoll_create
	.reloc ., R_X86_64_SIZE32, sys_epoll_create; .int 0
	.int 0x6a4b35
	.quad .Lname2323 /* index: 2323 */
	.weak keyboard_device_readchars; .quad keyboard_device_readchars
	.reloc ., R_X86_64_SIZE32, keyboard_device_readchars; .int 0
	.int 0x158b913
	.quad .Lname2324 /* index: 2324 */
	.weak sys32_fadvise64_64; .quad sys32_fadvise64_64
	.reloc ., R_X86_64_SIZE32, sys32_fadvise64_64; .int 0
	.int 0xbfe5914
	.quad .Lname2325 /* index: 2325 */
	.weak cpu_apply_scpustate; .quad cpu_apply_scpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_scpustate; .int 0
	.int 0xa8c9915
	.quad .Lname2326 /* index: 2326 */
	.weak dbg_addr2line_vprintf; .quad dbg_addr2line_vprintf
	.reloc ., R_X86_64_SIZE32, dbg_addr2line_vprintf; .int 0
	.int 0xb018916
	.quad .Lname2327 /* index: 2327 */
	.weak keyboard_device_getkey; .quad keyboard_device_getkey
	.reloc ., R_X86_64_SIZE32, keyboard_device_getkey; .int 0
	.int 0x64fded9
	.quad .Lname2328 /* index: 2328 */
	.weak vm_kernel_treelock_writef_nx; .quad vm_kernel_treelock_writef_nx
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_writef_nx; .int 0
	.int 0x3a30918
	.quad .Lname2329 /* index: 2329 */
	.weak dbg_getkey; .quad dbg_getkey
	.reloc ., R_X86_64_SIZE32, dbg_getkey; .int 0
	.int 0x5da1919
	.quad .Lname2330 /* index: 2330 */
	.weak terminal_poll_owrite; .quad terminal_poll_owrite
	.reloc ., R_X86_64_SIZE32, terminal_poll_owrite; .int 0
	.int 0xc9df3a5
	.quad 0 /* index: 2331 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2332 /* index: 2332 */
	.weak sys_sched_rr_get_interval; .quad sys_sched_rr_get_interval
	.reloc ., R_X86_64_SIZE32, sys_sched_rr_get_interval; .int 0
	.int 0x5c1391c
	.quad .Lname2333 /* index: 2333 */
	.weak vm_futex_broadcast; .quad vm_futex_broadcast
	.reloc ., R_X86_64_SIZE32, vm_futex_broadcast; .int 0
	.int 0x8659cf4
	.quad .Lname2334 /* index: 2334 */
	.weak sys_reboot; .quad sys_reboot
	.reloc ., R_X86_64_SIZE32, sys_reboot; .int 0
	.int 0x68c46f4
	.quad .Lname2335 /* index: 2335 */
	.weak this_kernel_stacknode; .quad this_kernel_stacknode
	.reloc ., R_X86_64_SIZE32, this_kernel_stacknode; .int 0
	.int 0x3ba5985
	.quad .Lname2336 /* index: 2336 */
	.weak pagedir_isuseraccessible_p; .quad pagedir_isuseraccessible_p
	.reloc ., R_X86_64_SIZE32, pagedir_isuseraccessible_p; .int 0
	.int 0x251c920
	.quad .Lname2337 /* index: 2337 */
	.weak sys_mmap; .quad sys_mmap
	.reloc ., R_X86_64_SIZE32, sys_mmap; .int 0
	.int 0x964430
	.quad 0 /* index: 2338 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2339 /* index: 2339 */
	.weak block_device_read_phys; .quad block_device_read_phys
	.reloc ., R_X86_64_SIZE32, block_device_read_phys; .int 0
	.int 0x22c3923
	.quad .Lname2340 /* index: 2340 */
	.weak cpu_quantum_reset; .quad cpu_quantum_reset
	.reloc ., R_X86_64_SIZE32, cpu_quantum_reset; .int 0
	.int 0xbb6e924
	.quad .Lname2341 /* index: 2341 */
	.weak ansitty_translate; .quad ansitty_translate
	.reloc ., R_X86_64_SIZE32, ansitty_translate; .int 0
	.int 0xd8f1925
	.quad .Lname2342 /* index: 2342 */
	.weak sys_sched_getscheduler; .quad sys_sched_getscheduler
	.reloc ., R_X86_64_SIZE32, sys_sched_getscheduler; .int 0
	.int 0xdf96042
	.quad 0 /* index: 2343 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2344 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2345 /* index: 2345 */
	.weak ringbuffer_wseek; .quad ringbuffer_wseek
	.reloc ., R_X86_64_SIZE32, ringbuffer_wseek; .int 0
	.int 0xbf2c73b
	.quad 0 /* index: 2346 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2347 /* index: 2347 */
	.weak vm86_inw; .quad vm86_inw
	.reloc ., R_X86_64_SIZE32, vm86_inw; .int 0
	.int 0xbc5987
	.quad .Lname2348 /* index: 2348 */
	.weak fs_kernel; .quad fs_kernel
	.reloc ., R_X86_64_SIZE32, fs_kernel; .int 0
	.int 0x61cf92c
	.quad .Lname2349 /* index: 2349 */
	.weak pci_readaddr; .quad pci_readaddr
	.reloc ., R_X86_64_SIZE32, pci_readaddr; .int 0
	.int 0xc138c32
	.quad .Lname2350 /* index: 2350 */
	.weak kernel_version; .quad kernel_version
	.reloc ., R_X86_64_SIZE32, kernel_version; .int 0
	.int 0x5d592e
	.quad .Lname2351 /* index: 2351 */
	.weak rwlock_write; .quad rwlock_write
	.reloc ., R_X86_64_SIZE32, rwlock_write; .int 0
	.int 0x8f0c505
	.quad .Lname2352 /* index: 2352 */
	.weak sys32_debugtrap; .quad sys32_debugtrap
	.reloc ., R_X86_64_SIZE32, sys32_debugtrap; .int 0
	.int 0xfd69930
	.quad .Lname2353 /* index: 2353 */
	.weak heap_realign_nx; .quad heap_realign_nx
	.reloc ., R_X86_64_SIZE32, heap_realign_nx; .int 0
	.int 0xa9ce188
	.quad .Lname2354 /* index: 2354 */
	.weak sys32_vm86old; .quad sys32_vm86old
	.reloc ., R_X86_64_SIZE32, sys32_vm86old; .int 0
	.int 0x80dbe34
	.quad .Lname2355 /* index: 2355 */
	.weak sys_access; .quad sys_access
	.reloc ., R_X86_64_SIZE32, sys_access; .int 0
	.int 0x57e2c33
	.quad .Lname2356 /* index: 2356 */
	.weak sys32_setresuid; .quad sys32_setresuid
	.reloc ., R_X86_64_SIZE32, sys32_setresuid; .int 0
	.int 0xde4b934
	.quad .Lname2357 /* index: 2357 */
	.weak boot_device; .quad boot_device
	.reloc ., R_X86_64_SIZE32, boot_device; .int 0
	.int 0x5c5a935
	.quad .Lname2358 /* index: 2358 */
	.weak sys32_prof; .quad sys32_prof
	.reloc ., R_X86_64_SIZE32, sys32_prof; .int 0
	.int 0x681c936
	.quad 0 /* index: 2359 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2360 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2361 /* index: 2361 */
	.weak sighand_ptr_lockread; .quad sighand_ptr_lockread
	.reloc ., R_X86_64_SIZE32, sighand_ptr_lockread; .int 0
	.int 0xc448c34
	.quad 0 /* index: 2362 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2363 /* index: 2363 */
	.weak sys32_rt_sigqueueinfo; .quad sys32_rt_sigqueueinfo
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigqueueinfo; .int 0
	.int 0xc4c1edf
	.quad 0 /* index: 2364 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2365 /* index: 2365 */
	.weak tty_device_startfwd; .quad tty_device_startfwd
	.reloc ., R_X86_64_SIZE32, tty_device_startfwd; .int 0
	.int 0xdcea1c4
	.quad 0 /* index: 2366 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2367 /* index: 2367 */
	.weak error_code; .quad error_code
	.reloc ., R_X86_64_SIZE32, error_code; .int 0
	.int 0x6836c35
	.quad .Lname2368 /* index: 2368 */
	.weak sys32_finit_module; .quad sys32_finit_module
	.reloc ., R_X86_64_SIZE32, sys32_finit_module; .int 0
	.int 0x8c58e05
	.quad .Lname2369 /* index: 2369 */
	.weak vm_kernel_treelock_trywrite; .quad vm_kernel_treelock_trywrite
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_trywrite; .int 0
	.int 0x33e2425
	.quad .Lname2370 /* index: 2370 */
	.weak path_recent_clear; .quad path_recent_clear
	.reloc ., R_X86_64_SIZE32, path_recent_clear; .int 0
	.int 0xa53942
	.quad .Lname2371 /* index: 2371 */
	.weak superblock_mountlock_tryread; .quad superblock_mountlock_tryread
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_tryread; .int 0
	.int 0x2a1f844
	.quad .Lname2372 /* index: 2372 */
	.weak cpu_sendipi_cpuset; .quad cpu_sendipi_cpuset
	.reloc ., R_X86_64_SIZE32, cpu_sendipi_cpuset; .int 0
	.int 0xb497944
	.quad .Lname2373 /* index: 2373 */
	.weak superblock_nodeslock_endwrite; .quad superblock_nodeslock_endwrite
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_endwrite; .int 0
	.int 0x4b8a945
	.quad 0 /* index: 2374 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2375 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2376 /* index: 2376 */
	.weak sys_rt_sigsuspend; .quad sys_rt_sigsuspend
	.reloc ., R_X86_64_SIZE32, sys_rt_sigsuspend; .int 0
	.int 0x337fec4
	.quad .Lname2377 /* index: 2377 */
	.weak x86_syscall_emulate32_cdecl; .quad x86_syscall_emulate32_cdecl
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_cdecl; .int 0
	.int 0x2a298c
	.quad 0 /* index: 2378 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2379 /* index: 2379 */
	.weak cpu_addpendingtask; .quad cpu_addpendingtask
	.reloc ., R_X86_64_SIZE32, cpu_addpendingtask; .int 0
	.int 0x45fb94b
	.quad .Lname2380 /* index: 2380 */
	.weak quantum_global_to_local; .quad quantum_global_to_local
	.reloc ., R_X86_64_SIZE32, quantum_global_to_local; .int 0
	.int 0xb1d594c
	.quad .Lname2381 /* index: 2381 */
	.weak aio_pbuffer_copytovmem; .quad aio_pbuffer_copytovmem
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copytovmem; .int 0
	.int 0xa9c894d
	.quad 0 /* index: 2382 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2383 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2384 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2385 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2386 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2387 /* index: 2387 */
	.weak sys32_select64; .quad sys32_select64
	.reloc ., R_X86_64_SIZE32, sys32_select64; .int 0
	.int 0xc4d26b4
	.quad .Lname2388 /* index: 2388 */
	.weak debuginfo_cu_parser_loadunit; .quad debuginfo_cu_parser_loadunit
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadunit; .int 0
	.int 0x295c954
	.quad .Lname2389 /* index: 2389 */
	.weak devfs_lock_upgrade; .quad devfs_lock_upgrade
	.reloc ., R_X86_64_SIZE32, devfs_lock_upgrade; .int 0
	.int 0x8f7e955
	.quad 0 /* index: 2390 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2391 /* index: 2391 */
	.weak pipe_destroy; .quad pipe_destroy
	.reloc ., R_X86_64_SIZE32, pipe_destroy; .int 0
	.int 0xdbad439
	.quad .Lname2392 /* index: 2392 */
	.weak vm_datablock_write; .quad vm_datablock_write
	.reloc ., R_X86_64_SIZE32, vm_datablock_write; .int 0
	.int 0xec21f85
	.quad .Lname2393 /* index: 2393 */
	.weak json_parser_enterobject; .quad json_parser_enterobject
	.reloc ., R_X86_64_SIZE32, json_parser_enterobject; .int 0
	.int 0xb1c6ee4
	.quad .Lname2394 /* index: 2394 */
	.weak this_idle_sched_state; .quad this_idle_sched_state
	.reloc ., R_X86_64_SIZE32, this_idle_sched_state; .int 0
	.int 0x396b7c5
	.quad 0 /* index: 2395 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2396 /* index: 2396 */
	.weak ttybase_device_tryioctl; .quad ttybase_device_tryioctl
	.reloc ., R_X86_64_SIZE32, ttybase_device_tryioctl; .int 0
	.int 0xde5095c
	.quad 0 /* index: 2397 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2398 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2399 /* index: 2399 */
	.weak vio_writeb; .quad vio_writeb
	.reloc ., R_X86_64_SIZE32, vio_writeb; .int 0
	.int 0x6f0dae2
	.quad .Lname2400 /* index: 2400 */
	.weak sys_semop; .quad sys_semop
	.reloc ., R_X86_64_SIZE32, sys_semop; .int 0
	.int 0x969d960
	.quad 0 /* index: 2401 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2402 /* index: 2402 */
	.weak inode_recent_clear; .quad inode_recent_clear
	.reloc ., R_X86_64_SIZE32, inode_recent_clear; .int 0
	.int 0x9d8e962
	.quad .Lname2403 /* index: 2403 */
	.weak block_device_read_sync; .quad block_device_read_sync
	.reloc ., R_X86_64_SIZE32, block_device_read_sync; .int 0
	.int 0x22cf963
	.quad .Lname2404 /* index: 2404 */
	.weak sys_getsid; .quad sys_getsid
	.reloc ., R_X86_64_SIZE32, sys_getsid; .int 0
	.int 0x5db0964
	.quad 0 /* index: 2405 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2406 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2407 /* index: 2407 */
	.weak vm_tasklock_write; .quad vm_tasklock_write
	.reloc ., R_X86_64_SIZE32, vm_tasklock_write; .int 0
	.int 0x993b3e5
	.quad 0 /* index: 2408 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2409 /* index: 2409 */
	.weak path_newchild; .quad path_newchild
	.reloc ., R_X86_64_SIZE32, path_newchild; .int 0
	.int 0xa530a14
	.quad .Lname2410 /* index: 2410 */
	.weak unwind_setreg_xfpustate_exclusive; .quad unwind_setreg_xfpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_xfpustate_exclusive; .int 0
	.int 0xefe5125
	.quad .Lname2411 /* index: 2411 */
	.weak json_parser_yield; .quad json_parser_yield
	.reloc ., R_X86_64_SIZE32, json_parser_yield; .int 0
	.int 0x276c5a4
	.quad 0 /* index: 2412 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2413 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2414 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2415 /* index: 2415 */
	.weak sys_get_robust_list; .quad sys_get_robust_list
	.reloc ., R_X86_64_SIZE32, sys_get_robust_list; .int 0
	.int 0xa0834d4
	.quad 0 /* index: 2416 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2417 /* index: 2417 */
	.weak setreg_lcpustate; .quad setreg_lcpustate
	.reloc ., R_X86_64_SIZE32, setreg_lcpustate; .int 0
	.int 0xf7676b5
	.quad .Lname2418 /* index: 2418 */
	.weak sys_mlock2; .quad sys_mlock2
	.reloc ., R_X86_64_SIZE32, sys_mlock2; .int 0
	.int 0x646e972
	.quad .Lname2419 /* index: 2419 */
	.weak vm_datablock_vio_readv_phys; .quad vm_datablock_vio_readv_phys
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_readv_phys; .int 0
	.int 0x3820973
	.quad .Lname2420 /* index: 2420 */
	.weak block_device_acquire_partlock_read; .quad block_device_acquire_partlock_read
	.reloc ., R_X86_64_SIZE32, block_device_acquire_partlock_read; .int 0
	.int 0x3d5d974
	.quad 0 /* index: 2421 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2422 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2423 /* index: 2423 */
	.weak sys32_open_by_handle_at; .quad sys32_open_by_handle_at
	.reloc ., R_X86_64_SIZE32, sys32_open_by_handle_at; .int 0
	.int 0x916a5a4
	.quad .Lname2424 /* index: 2424 */
	.weak vpage_realloc_nx; .quad vpage_realloc_nx
	.reloc ., R_X86_64_SIZE32, vpage_realloc_nx; .int 0
	.int 0xa4e978
	.quad .Lname2425 /* index: 2425 */
	.weak sys_fchdir; .quad sys_fchdir
	.reloc ., R_X86_64_SIZE32, sys_fchdir; .int 0
	.int 0x5ce5b92
	.quad 0 /* index: 2426 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2427 /* index: 2427 */
	.weak sys_accept; .quad sys_accept
	.reloc ., R_X86_64_SIZE32, sys_accept; .int 0
	.int 0x57e2ce4
	.quad .Lname2428 /* index: 2428 */
	.weak sys_socketpair; .quad sys_socketpair
	.reloc ., R_X86_64_SIZE32, sys_socketpair; .int 0
	.int 0x15dc632
	.quad 0 /* index: 2429 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2430 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2431 /* index: 2431 */
	.weak vpage_alloc; .quad vpage_alloc
	.reloc ., R_X86_64_SIZE32, vpage_alloc; .int 0
	.int 0xb2b5683
	.quad 0 /* index: 2432 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2433 /* index: 2433 */
	.weak ringbuffer_write; .quad ringbuffer_write
	.reloc ., R_X86_64_SIZE32, ringbuffer_write; .int 0
	.int 0xbf2ec25
	.quad .Lname2434 /* index: 2434 */
	.weak memrchr; .quad memrchr
	.reloc ., R_X86_64_SIZE32, memrchr; .int 0
	.int 0x3c48982
	.quad .Lname2435 /* index: 2435 */
	.weak ringbuffer_write_nonblock; .quad ringbuffer_write_nonblock
	.reloc ., R_X86_64_SIZE32, ringbuffer_write_nonblock; .int 0
	.int 0xc8b1eeb
	.quad 0 /* index: 2436 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2437 /* index: 2437 */
	.weak sys_time; .quad sys_time
	.reloc ., R_X86_64_SIZE32, sys_time; .int 0
	.int 0x96a985
	.quad 0 /* index: 2438 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2439 /* index: 2439 */
	.weak vio_subq; .quad vio_subq
	.reloc ., R_X86_64_SIZE32, vio_subq; .int 0
	.int 0x56ac41
	.quad .Lname2440 /* index: 2440 */
	.weak vm_kernel_treelock_upgrade_nx; .quad vm_kernel_treelock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_upgrade_nx; .int 0
	.int 0x8ee6988
	.quad .Lname2441 /* index: 2441 */
	.weak vm_datapart_lock_tryupgrade; .quad vm_datapart_lock_tryupgrade
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_tryupgrade; .int 0
	.int 0x92aa5a5
	.quad .Lname2442 /* index: 2442 */
	.weak vm_isused; .quad vm_isused
	.reloc ., R_X86_64_SIZE32, vm_isused; .int 0
	.int 0x60ab484
	.quad .Lname2443 /* index: 2443 */
	.weak sys32_ssetmask; .quad sys32_ssetmask
	.reloc ., R_X86_64_SIZE32, sys32_ssetmask; .int 0
	.int 0x9adb98b
	.quad .Lname2444 /* index: 2444 */
	.weak vm_kernel; .quad vm_kernel
	.reloc ., R_X86_64_SIZE32, vm_kernel; .int 0
	.int 0x61d098c
	.quad .Lname2445 /* index: 2445 */
	.weak fpustate32_loadfrom; .quad fpustate32_loadfrom
	.reloc ., R_X86_64_SIZE32, fpustate32_loadfrom; .int 0
	.int 0x280298d
	.quad 0 /* index: 2446 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2447 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2448 /* index: 2448 */
	.weak sys32_io_setup; .quad sys32_io_setup
	.reloc ., R_X86_64_SIZE32, sys32_io_setup; .int 0
	.int 0x50f4990
	.quad .Lname2449 /* index: 2449 */
	.weak vm_datapart_do_write; .quad vm_datapart_do_write
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_write; .int 0
	.int 0x2bdb9a5
	.quad .Lname2450 /* index: 2450 */
	.weak vm86_inb; .quad vm86_inb
	.reloc ., R_X86_64_SIZE32, vm86_inb; .int 0
	.int 0xbc5992
	.quad .Lname2451 /* index: 2451 */
	.weak task_push_asynchronous_rpc; .quad task_push_asynchronous_rpc
	.reloc ., R_X86_64_SIZE32, task_push_asynchronous_rpc; .int 0
	.int 0x3d4e993
	.quad .Lname2452 /* index: 2452 */
	.weak vio_memset; .quad vio_memset
	.reloc ., R_X86_64_SIZE32, vio_memset; .int 0
	.int 0x63d9994
	.quad 0 /* index: 2453 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2454 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2455 /* index: 2455 */
	.weak vm_datapart_do_write_phys; .quad vm_datapart_do_write_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_write_phys; .int 0
	.int 0xa9db593
	.quad .Lname2456 /* index: 2456 */
	.weak sys32_break; .quad sys32_break
	.reloc ., R_X86_64_SIZE32, sys32_break; .int 0
	.int 0x8228d1b
	.quad .Lname2457 /* index: 2457 */
	.weak json_writer_beginarray; .quad json_writer_beginarray
	.reloc ., R_X86_64_SIZE32, json_writer_beginarray; .int 0
	.int 0x864b999
	.quad .Lname2458 /* index: 2458 */
	.weak sys32_symlinkat; .quad sys32_symlinkat
	.reloc ., R_X86_64_SIZE32, sys32_symlinkat; .int 0
	.int 0x6486384
	.quad .Lname2459 /* index: 2459 */
	.weak directory_symlink; .quad directory_symlink
	.reloc ., R_X86_64_SIZE32, directory_symlink; .int 0
	.int 0x3fb99b
	.quad .Lname2460 /* index: 2460 */
	.weak sys_kill; .quad sys_kill
	.reloc ., R_X86_64_SIZE32, sys_kill; .int 0
	.int 0x96199c
	.quad 0 /* index: 2461 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2462 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2463 /* index: 2463 */
	.weak sys32_execve; .quad sys32_execve
	.reloc ., R_X86_64_SIZE32, sys32_execve; .int 0
	.int 0x27edc45
	.quad .Lname2464 /* index: 2464 */
	.weak task_connect; .quad task_connect
	.reloc ., R_X86_64_SIZE32, task_connect; .int 0
	.int 0xdeac4
	.quad 0 /* index: 2465 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2466 /* index: 2466 */
	.weak sys_linkat; .quad sys_linkat
	.reloc ., R_X86_64_SIZE32, sys_linkat; .int 0
	.int 0x62a0114
	.quad .Lname2467 /* index: 2467 */
	.weak block_device_write_phys_sync; .quad block_device_write_phys_sync
	.reloc ., R_X86_64_SIZE32, block_device_write_phys_sync; .int 0
	.int 0x5b799a3
	.quad .Lname2468 /* index: 2468 */
	.weak dbg_exit; .quad dbg_exit
	.reloc ., R_X86_64_SIZE32, dbg_exit; .int 0
	.int 0x8d5c9a4
	.quad .Lname2469 /* index: 2469 */
	.weak kernel_debugtrap_r_icpustate; .quad kernel_debugtrap_r_icpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_icpustate; .int 0
	.int 0xed509a5
	.quad 0 /* index: 2470 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2471 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2472 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2473 /* index: 2473 */
	.weak setreg_fcpustate; .quad setreg_fcpustate
	.reloc ., R_X86_64_SIZE32, setreg_fcpustate; .int 0
	.int 0xf7668b5
	.quad 0 /* index: 2474 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2475 /* index: 2475 */
	.weak vio_subw; .quad vio_subw
	.reloc ., R_X86_64_SIZE32, vio_subw; .int 0
	.int 0x56ac47
	.quad 0 /* index: 2476 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2477 /* index: 2477 */
	.weak unwind_fde_exec; .quad unwind_fde_exec
	.reloc ., R_X86_64_SIZE32, unwind_fde_exec; .int 0
	.int 0x4b13723
	.quad 0 /* index: 2478 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2479 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2480 /* index: 2480 */
	.weak sys32_exit_group; .quad sys32_exit_group
	.reloc ., R_X86_64_SIZE32, sys32_exit_group; .int 0
	.int 0xdd09b0
	.quad .Lname2481 /* index: 2481 */
	.weak regdump_ucpustate; .quad regdump_ucpustate
	.reloc ., R_X86_64_SIZE32, regdump_ucpustate; .int 0
	.int 0xbf47eb5
	.quad .Lname2482 /* index: 2482 */
	.weak sys_eventfd2; .quad sys_eventfd2
	.reloc ., R_X86_64_SIZE32, sys_eventfd2; .int 0
	.int 0xb1539b2
	.quad .Lname2483 /* index: 2483 */
	.weak driver_loaded_callbacks; .quad driver_loaded_callbacks
	.reloc ., R_X86_64_SIZE32, driver_loaded_callbacks; .int 0
	.int 0x5bfe6f3
	.quad .Lname2484 /* index: 2484 */
	.weak mempset; .quad mempset
	.reloc ., R_X86_64_SIZE32, mempset; .int 0
	.int 0x3c479b4
	.quad .Lname2485 /* index: 2485 */
	.weak pagedir_pop_mapone; .quad pagedir_pop_mapone
	.reloc ., R_X86_64_SIZE32, pagedir_pop_mapone; .int 0
	.int 0x319b9b5
	.quad 0 /* index: 2486 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2487 /* index: 2487 */
	.weak sys32_rt_sigpending; .quad sys32_rt_sigpending
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigpending; .int 0
	.int 0x42459b7
	.quad .Lname2488 /* index: 2488 */
	.weak krealign_offset_nx; .quad krealign_offset_nx
	.reloc ., R_X86_64_SIZE32, krealign_offset_nx; .int 0
	.int 0x49079b8
	.quad .Lname2489 /* index: 2489 */
	.weak debuginfo_cu_abbrev_fini; .quad debuginfo_cu_abbrev_fini
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_abbrev_fini; .int 0
	.int 0xd1aa9b9
	.quad 0 /* index: 2490 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2491 /* index: 2491 */
	.weak sys32_sgetmask; .quad sys32_sgetmask
	.reloc ., R_X86_64_SIZE32, sys32_sgetmask; .int 0
	.int 0xdadb9bb
	.quad 0 /* index: 2492 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2493 /* index: 2493 */
	.weak ringbuffer_poll; .quad ringbuffer_poll
	.reloc ., R_X86_64_SIZE32, ringbuffer_poll; .int 0
	.int 0x8bfb1ec
	.quad .Lname2494 /* index: 2494 */
	.weak heap_realign; .quad heap_realign
	.reloc ., R_X86_64_SIZE32, heap_realign; .int 0
	.int 0xe5da9be
	.quad .Lname2495 /* index: 2495 */
	.weak vm_datapart_lockwrite_setcore; .quad vm_datapart_lockwrite_setcore
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockwrite_setcore; .int 0
	.int 0x5e236f5
	.quad 0 /* index: 2496 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2497 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2498 /* index: 2498 */
	.weak getreg_coregs; .quad getreg_coregs
	.reloc ., R_X86_64_SIZE32, getreg_coregs; .int 0
	.int 0x86d0053
	.quad .Lname2499 /* index: 2499 */
	.weak block_device_partition_writev_phys; .quad block_device_partition_writev_phys
	.reloc ., R_X86_64_SIZE32, block_device_partition_writev_phys; .int 0
	.int 0xcf2e9c3
	.quad .Lname2500 /* index: 2500 */
	.weak kmemalign_offset; .quad kmemalign_offset
	.reloc ., R_X86_64_SIZE32, kmemalign_offset; .int 0
	.int 0x7d939c4
	.quad .Lname2501 /* index: 2501 */
	.weak devfs_lock_write; .quad devfs_lock_write
	.reloc ., R_X86_64_SIZE32, devfs_lock_write; .int 0
	.int 0xefa29c5
	.quad 0 /* index: 2502 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2503 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2504 /* index: 2504 */
	.weak kmemalign_offset_nx; .quad kmemalign_offset_nx
	.reloc ., R_X86_64_SIZE32, kmemalign_offset_nx; .int 0
	.int 0x39cf9c8
	.quad .Lname2505 /* index: 2505 */
	.weak superblock_nodeslock_tryupgrade; .quad superblock_nodeslock_tryupgrade
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_tryupgrade; .int 0
	.int 0xa745da5
	.quad 0 /* index: 2506 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2507 /* index: 2507 */
	.weak x86_sysroute0_asm64_syscall; .quad x86_sysroute0_asm64_syscall
	.reloc ., R_X86_64_SIZE32, x86_sysroute0_asm64_syscall; .int 0
	.int 0x948fb5c
	.quad 0 /* index: 2508 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2509 /* index: 2509 */
	.weak sys32_geteuid32; .quad sys32_geteuid32
	.reloc ., R_X86_64_SIZE32, sys32_geteuid32; .int 0
	.int 0xca3d1a2
	.quad .Lname2510 /* index: 2510 */
	.weak mouse_device_button; .quad mouse_device_button
	.reloc ., R_X86_64_SIZE32, mouse_device_button; .int 0
	.int 0xb3cd9ce
	.quad 0 /* index: 2511 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2512 /* index: 2512 */
	.weak unwind_emulator_exec_autostack; .quad unwind_emulator_exec_autostack
	.reloc ., R_X86_64_SIZE32, unwind_emulator_exec_autostack; .int 0
	.int 0x49816fb
	.quad .Lname2513 /* index: 2513 */
	.weak vm_writephysq; .quad vm_writephysq
	.reloc ., R_X86_64_SIZE32, vm_writephysq; .int 0
	.int 0x7f029d1
	.quad .Lname2514 /* index: 2514 */
	.weak cpu_quantum_remaining_nopr; .quad cpu_quantum_remaining_nopr
	.reloc ., R_X86_64_SIZE32, cpu_quantum_remaining_nopr; .int 0
	.int 0xf0d29d2
	.quad .Lname2515 /* index: 2515 */
	.weak this_read_locks; .quad this_read_locks
	.reloc ., R_X86_64_SIZE32, this_read_locks; .int 0
	.int 0xad5a9a3
	.quad .Lname2516 /* index: 2516 */
	.weak unwind_getreg_icpustate_exclusive; .quad unwind_getreg_icpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_icpustate_exclusive; .int 0
	.int 0xd8e5055
	.quad .Lname2517 /* index: 2517 */
	.weak debugaranges_locate; .quad debugaranges_locate
	.reloc ., R_X86_64_SIZE32, debugaranges_locate; .int 0
	.int 0x908f9d5
	.quad 0 /* index: 2518 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2519 /* index: 2519 */
	.weak vm_writephysw; .quad vm_writephysw
	.reloc ., R_X86_64_SIZE32, vm_writephysw; .int 0
	.int 0x7f029d7
	.quad .Lname2520 /* index: 2520 */
	.weak inode_recent_clear_nx; .quad inode_recent_clear_nx
	.reloc ., R_X86_64_SIZE32, inode_recent_clear_nx; .int 0
	.int 0xe96f9d8
	.quad .Lname2521 /* index: 2521 */
	.weak swap_read; .quad swap_read
	.reloc ., R_X86_64_SIZE32, swap_read; .int 0
	.int 0x866f1a4
	.quad .Lname2522 /* index: 2522 */
	.weak x86_userexcept_unwind_i; .quad x86_userexcept_unwind_i
	.reloc ., R_X86_64_SIZE32, x86_userexcept_unwind_i; .int 0
	.int 0x1010019
	.quad .Lname2523 /* index: 2523 */
	.weak sys32_linux_oldfstat; .quad sys32_linux_oldfstat
	.reloc ., R_X86_64_SIZE32, sys32_linux_oldfstat; .int 0
	.int 0x297c284
	.quad .Lname2524 /* index: 2524 */
	.weak vm_copyinphys; .quad vm_copyinphys
	.reloc ., R_X86_64_SIZE32, vm_copyinphys; .int 0
	.int 0x2d0ca03
	.quad 0 /* index: 2525 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2526 /* index: 2526 */
	.weak page_free; .quad page_free
	.reloc ., R_X86_64_SIZE32, page_free; .int 0
	.int 0xdb5aec5
	.quad .Lname2527 /* index: 2527 */
	.weak fpustate32_saveinto; .quad fpustate32_saveinto
	.reloc ., R_X86_64_SIZE32, fpustate32_saveinto; .int 0
	.int 0xf3129df
	.quad .Lname2528 /* index: 2528 */
	.weak sys_mknod; .quad sys_mknod
	.reloc ., R_X86_64_SIZE32, sys_mknod; .int 0
	.int 0x9648054
	.quad 0 /* index: 2529 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2530 /* index: 2530 */
	.weak setreg_sgregs; .quad setreg_sgregs
	.reloc ., R_X86_64_SIZE32, setreg_sgregs; .int 0
	.int 0xf550023
	.quad .Lname2531 /* index: 2531 */
	.weak sys32_fdatasync; .quad sys32_fdatasync
	.reloc ., R_X86_64_SIZE32, sys32_fdatasync; .int 0
	.int 0xec089e3
	.quad .Lname2532 /* index: 2532 */
	.weak dbg_isholding_alt; .quad dbg_isholding_alt
	.reloc ., R_X86_64_SIZE32, dbg_isholding_alt; .int 0
	.int 0xbab9e4
	.quad .Lname2533 /* index: 2533 */
	.weak addr2line; .quad addr2line
	.reloc ., R_X86_64_SIZE32, addr2line; .int 0
	.int 0xb5949e5
	.quad .Lname2534 /* index: 2534 */
	.weak vm_datapart_writev; .quad vm_datapart_writev
	.reloc ., R_X86_64_SIZE32, vm_datapart_writev; .int 0
	.int 0xbbed9e6
	.quad .Lname2535 /* index: 2535 */
	.weak format_escape; .quad format_escape
	.reloc ., R_X86_64_SIZE32, format_escape; .int 0
	.int 0x8a0a165
	.quad 0 /* index: 2536 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2537 /* index: 2537 */
	.weak sys32_add_key; .quad sys32_add_key
	.reloc ., R_X86_64_SIZE32, sys32_add_key; .int 0
	.int 0xcb049e9
	.quad 0 /* index: 2538 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2539 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2540 /* index: 2540 */
	.weak vm_writephysl; .quad vm_writephysl
	.reloc ., R_X86_64_SIZE32, vm_writephysl; .int 0
	.int 0x7f029ec
	.quad .Lname2541 /* index: 2541 */
	.weak sys_kreaddirf; .quad sys_kreaddirf
	.reloc ., R_X86_64_SIZE32, sys_kreaddirf; .int 0
	.int 0x73d276
	.quad .Lname2542 /* index: 2542 */
	.weak vm_enumdmav_nx; .quad vm_enumdmav_nx
	.reloc ., R_X86_64_SIZE32, vm_enumdmav_nx; .int 0
	.int 0xa64f9b8
	.quad .Lname2543 /* index: 2543 */
	.weak this_kernel_stackpart; .quad this_kernel_stackpart
	.reloc ., R_X86_64_SIZE32, this_kernel_stackpart; .int 0
	.int 0x3ba64b4
	.quad 0 /* index: 2544 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2545 /* index: 2545 */
	.weak sys32_setresuid32; .quad sys32_setresuid32
	.reloc ., R_X86_64_SIZE32, sys32_setresuid32; .int 0
	.int 0x4b93a82
	.quad .Lname2546 /* index: 2546 */
	.weak memchr; .quad memchr
	.reloc ., R_X86_64_SIZE32, memchr; .int 0
	.int 0x73c39f2
	.quad .Lname2547 /* index: 2547 */
	.weak sys32_statfs; .quad sys32_statfs
	.reloc ., R_X86_64_SIZE32, sys32_statfs; .int 0
	.int 0x11aec53
	.quad .Lname2548 /* index: 2548 */
	.weak sys32_execveat; .quad sys32_execveat
	.reloc ., R_X86_64_SIZE32, sys32_execveat; .int 0
	.int 0xedc49f4
	.quad .Lname2549 /* index: 2549 */
	.weak kernel_panic_ucpustate; .quad kernel_panic_ucpustate
	.reloc ., R_X86_64_SIZE32, kernel_panic_ucpustate; .int 0
	.int 0x78ab9f5
	.quad 0 /* index: 2550 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2551 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2552 /* index: 2552 */
	.weak x86_bootcpu_cpuid; .quad x86_bootcpu_cpuid
	.reloc ., R_X86_64_SIZE32, x86_bootcpu_cpuid; .int 0
	.int 0x4676dd4
	.quad .Lname2553 /* index: 2553 */
	.weak sys32_getcwd; .quad sys32_getcwd
	.reloc ., R_X86_64_SIZE32, sys32_getcwd; .int 0
	.int 0x26ccc54
	.quad 0 /* index: 2554 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2555 /* index: 2555 */
	.weak sys_brk; .quad sys_brk
	.reloc ., R_X86_64_SIZE32, sys_brk; .int 0
	.int 0xb0959fb
	.quad .Lname2556 /* index: 2556 */
	.weak sys_io_cancel; .quad sys_io_cancel
	.reloc ., R_X86_64_SIZE32, sys_io_cancel; .int 0
	.int 0xe9f29fc
	.quad 0 /* index: 2557 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2558 /* index: 2558 */
	.weak sys_timer_delete; .quad sys_timer_delete
	.reloc ., R_X86_64_SIZE32, sys_timer_delete; .int 0
	.int 0x303a055
	.quad .Lname2559 /* index: 2559 */
	.weak sys_timer_create; .quad sys_timer_create
	.reloc ., R_X86_64_SIZE32, sys_timer_create; .int 0
	.int 0x3013455
	.quad 0 /* index: 2560 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2561 /* index: 2561 */
	.weak pagedir_unmap_userspace_p; .quad pagedir_unmap_userspace_p
	.reloc ., R_X86_64_SIZE32, pagedir_unmap_userspace_p; .int 0
	.int 0x2130f00
	.quad .Lname2562 /* index: 2562 */
	.weak debuginfo_cu_parser_getaddr; .quad debuginfo_cu_parser_getaddr
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getaddr; .int 0
	.int 0xbb49a02
	.quad .Lname2563 /* index: 2563 */
	.weak dbg_getc; .quad dbg_getc
	.reloc ., R_X86_64_SIZE32, dbg_getc; .int 0
	.int 0x8d5da03
	.quad .Lname2564 /* index: 2564 */
	.weak sys32_fmkdirat; .quad sys32_fmkdirat
	.reloc ., R_X86_64_SIZE32, sys32_fmkdirat; .int 0
	.int 0x47d8a04
	.quad .Lname2565 /* index: 2565 */
	.weak serial_probe; .quad serial_probe
	.reloc ., R_X86_64_SIZE32, serial_probe; .int 0
	.int 0x7fb1a05
	.quad .Lname2566 /* index: 2566 */
	.weak task_exec_asynchronous_rpc_v; .quad task_exec_asynchronous_rpc_v
	.reloc ., R_X86_64_SIZE32, task_exec_asynchronous_rpc_v; .int 0
	.int 0x40cfa06
	.quad .Lname2567 /* index: 2567 */
	.weak sys32_setreuid; .quad sys32_setreuid
	.reloc ., R_X86_64_SIZE32, sys32_setreuid; .int 0
	.int 0xcde4ad4
	.quad .Lname2568 /* index: 2568 */
	.weak vm_datapart_do_allocram_nx; .quad vm_datapart_do_allocram_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_allocram_nx; .int 0
	.int 0x8034a08
	.quad .Lname2569 /* index: 2569 */
	.weak mempcpy; .quad mempcpy
	.reloc ., R_X86_64_SIZE32, mempcpy; .int 0
	.int 0x3c46a09
	.quad .Lname2570 /* index: 2570 */
	.weak x86_sysroute0_c; .quad x86_sysroute0_c
	.reloc ., R_X86_64_SIZE32, x86_sysroute0_c; .int 0
	.int 0xaa1f513
	.quad .Lname2571 /* index: 2571 */
	.weak inode_readv_blocking; .quad inode_readv_blocking
	.reloc ., R_X86_64_SIZE32, inode_readv_blocking; .int 0
	.int 0xd790c57
	.quad .Lname2572 /* index: 2572 */
	.weak x86_setiopl; .quad x86_setiopl
	.reloc ., R_X86_64_SIZE32, x86_setiopl; .int 0
	.int 0x9b15a0c
	.quad .Lname2573 /* index: 2573 */
	.weak sys32_ioperm; .quad sys32_ioperm
	.reloc ., R_X86_64_SIZE32, sys32_ioperm; .int 0
	.int 0x2560a0d
	.quad .Lname2574 /* index: 2574 */
	.weak x86_rpc_user_redirection; .quad x86_rpc_user_redirection
	.reloc ., R_X86_64_SIZE32, x86_rpc_user_redirection; .int 0
	.int 0xf9f1a0e
	.quad .Lname2575 /* index: 2575 */
	.weak superblock_nodeslock_trywrite; .quad superblock_nodeslock_trywrite
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_trywrite; .int 0
	.int 0xa08aa75
	.quad 0 /* index: 2576 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2577 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2578 /* index: 2578 */
	.weak krand_r; .quad krand_r
	.reloc ., R_X86_64_SIZE32, krand_r; .int 0
	.int 0x2884a12
	.quad .Lname2579 /* index: 2579 */
	.weak driver_unloaded_callbacks; .quad driver_unloaded_callbacks
	.reloc ., R_X86_64_SIZE32, driver_unloaded_callbacks; .int 0
	.int 0x6a5da13
	.quad .Lname2580 /* index: 2580 */
	.weak heap_align_untraced; .quad heap_align_untraced
	.reloc ., R_X86_64_SIZE32, heap_align_untraced; .int 0
	.int 0x9fe1a14
	.quad .Lname2581 /* index: 2581 */
	.weak inode_awrite; .quad inode_awrite
	.reloc ., R_X86_64_SIZE32, inode_awrite; .int 0
	.int 0x28bea15
	.quad .Lname2582 /* index: 2582 */
	.weak ioperm_bitmap_allocf; .quad ioperm_bitmap_allocf
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_allocf; .int 0
	.int 0xa269b86
	.quad .Lname2583 /* index: 2583 */
	.weak ttybase_device_fini; .quad ttybase_device_fini
	.reloc ., R_X86_64_SIZE32, ttybase_device_fini; .int 0
	.int 0xb508c59
	.quad .Lname2584 /* index: 2584 */
	.weak dbg_putuni; .quad dbg_putuni
	.reloc ., R_X86_64_SIZE32, dbg_putuni; .int 0
	.int 0x67a1499
	.quad .Lname2585 /* index: 2585 */
	.weak dbg_current; .quad dbg_current
	.reloc ., R_X86_64_SIZE32, dbg_current; .int 0
	.int 0xaa30704
	.quad 0 /* index: 2586 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2587 /* index: 2587 */
	.weak sys32__newselect; .quad sys32__newselect
	.reloc ., R_X86_64_SIZE32, sys32__newselect; .int 0
	.int 0x820df04
	.quad .Lname2588 /* index: 2588 */
	.weak task_detach_children; .quad task_detach_children
	.reloc ., R_X86_64_SIZE32, task_detach_children; .int 0
	.int 0xc3a204e
	.quad 0 /* index: 2589 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2590 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2591 /* index: 2591 */
	.weak sys_splice; .quad sys_splice
	.reloc ., R_X86_64_SIZE32, sys_splice; .int 0
	.int 0x6a29f05
	.quad .Lname2592 /* index: 2592 */
	.weak sys32_kcmp; .quad sys32_kcmp
	.reloc ., R_X86_64_SIZE32, sys32_kcmp; .int 0
	.int 0x683aa20
	.quad 0 /* index: 2593 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2594 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2595 /* index: 2595 */
	.weak sys32_access; .quad sys32_access
	.reloc ., R_X86_64_SIZE32, sys32_access; .int 0
	.int 0x2c9fa23
	.quad .Lname2596 /* index: 2596 */
	.weak json_writer_beginobject; .quad json_writer_beginobject
	.reloc ., R_X86_64_SIZE32, json_writer_beginobject; .int 0
	.int 0x79b1a24
	.quad 0 /* index: 2597 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2598 /* index: 2598 */
	.weak sys32_process_vm_writev; .quad sys32_process_vm_writev
	.reloc ., R_X86_64_SIZE32, sys32_process_vm_writev; .int 0
	.int 0x25f0a26
	.quad .Lname2599 /* index: 2599 */
	.weak sys_set_thread_area; .quad sys_set_thread_area
	.reloc ., R_X86_64_SIZE32, sys_set_thread_area; .int 0
	.int 0x50619b1
	.quad 0 /* index: 2600 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2601 /* index: 2601 */
	.weak ttybase_device_hupctty; .quad ttybase_device_hupctty
	.reloc ., R_X86_64_SIZE32, ttybase_device_hupctty; .int 0
	.int 0xb871eb9
	.quad .Lname2602 /* index: 2602 */
	.weak task_raisesignalprocess; .quad task_raisesignalprocess
	.reloc ., R_X86_64_SIZE32, task_raisesignalprocess; .int 0
	.int 0x8915943
	.quad .Lname2603 /* index: 2603 */
	.weak debuginfo_cu_parser_loadattr_lexical_block; .quad debuginfo_cu_parser_loadattr_lexical_block
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_lexical_block; .int 0
	.int 0x8124a2b
	.quad .Lname2604 /* index: 2604 */
	.weak memmovedownl; .quad memmovedownl
	.reloc ., R_X86_64_SIZE32, memmovedownl; .int 0
	.int 0xb872a2c
	.quad .Lname2605 /* index: 2605 */
	.weak sys32_lfutexlockexpr; .quad sys32_lfutexlockexpr
	.reloc ., R_X86_64_SIZE32, sys32_lfutexlockexpr; .int 0
	.int 0x84d81b2
	.quad .Lname2606 /* index: 2606 */
	.weak sys_listen; .quad sys_listen
	.reloc ., R_X86_64_SIZE32, sys_listen; .int 0
	.int 0x6371a2e
	.quad 0 /* index: 2607 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2608 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2609 /* index: 2609 */
	.weak memmovedownq; .quad memmovedownq
	.reloc ., R_X86_64_SIZE32, memmovedownq; .int 0
	.int 0xb872a31
	.quad 0 /* index: 2610 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2611 /* index: 2611 */
	.weak ioperm_bitmap_alloc; .quad ioperm_bitmap_alloc
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_alloc; .int 0
	.int 0x1a269b3
	.quad .Lname2612 /* index: 2612 */
	.weak _strtoi64; .quad _strtoi64
	.reloc ., R_X86_64_SIZE32, _strtoi64; .int 0
	.int 0xb9b3a34
	.quad .Lname2613 /* index: 2613 */
	.weak path_getcasechild_or_parent_inode; .quad path_getcasechild_or_parent_inode
	.reloc ., R_X86_64_SIZE32, path_getcasechild_or_parent_inode; .int 0
	.int 0x372aa35
	.quad 0 /* index: 2614 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2615 /* index: 2615 */
	.weak dbg_ungetkey; .quad dbg_ungetkey
	.reloc ., R_X86_64_SIZE32, dbg_ungetkey; .int 0
	.int 0x2748709
	.quad .Lname2616 /* index: 2616 */
	.weak sys32_socket; .quad sys32_socket
	.reloc ., R_X86_64_SIZE32, sys32_socket; .int 0
	.int 0x1360744
	.quad .Lname2617 /* index: 2617 */
	.weak dbg_trygetkey; .quad dbg_trygetkey
	.reloc ., R_X86_64_SIZE32, dbg_trygetkey; .int 0
	.int 0x551da39
	.quad .Lname2618 /* index: 2618 */
	.weak unicode_readutf16_rev; .quad unicode_readutf16_rev
	.reloc ., R_X86_64_SIZE32, unicode_readutf16_rev; .int 0
	.int 0xe5a0346
	.quad .Lname2619 /* index: 2619 */
	.weak cred_require_hwio; .quad cred_require_hwio
	.reloc ., R_X86_64_SIZE32, cred_require_hwio; .int 0
	.int 0xe53fc5f
	.quad .Lname2620 /* index: 2620 */
	.weak sys_keyctl; .quad sys_keyctl
	.reloc ., R_X86_64_SIZE32, sys_keyctl; .int 0
	.int 0x61b4a3c
	.quad 0 /* index: 2621 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2622 /* index: 2622 */
	.weak devfs_lock_downgrade; .quad devfs_lock_downgrade
	.reloc ., R_X86_64_SIZE32, devfs_lock_downgrade; .int 0
	.int 0x5204855
	.quad .Lname2623 /* index: 2623 */
	.weak regdump_fcpustate; .quad regdump_fcpustate
	.reloc ., R_X86_64_SIZE32, regdump_fcpustate; .int 0
	.int 0xbf449b5
	.quad .Lname2624 /* index: 2624 */
	.weak bcmp; .quad bcmp
	.reloc ., R_X86_64_SIZE32, bcmp; .int 0
	.int 0x68a40
	.quad .Lname2625 /* index: 2625 */
	.weak mempmovedownq; .quad mempmovedownq
	.reloc ., R_X86_64_SIZE32, mempmovedownq; .int 0
	.int 0xf7f1a41
	.quad 0 /* index: 2626 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2627 /* index: 2627 */
	.weak sys_statfs; .quad sys_statfs
	.reloc ., R_X86_64_SIZE32, sys_statfs; .int 0
	.int 0x6ad3a43
	.quad .Lname2628 /* index: 2628 */
	.weak sys_getcwd; .quad sys_getcwd
	.reloc ., R_X86_64_SIZE32, sys_getcwd; .int 0
	.int 0x5db1a44
	.quad .Lname2629 /* index: 2629 */
	.weak pagedir_iswritable; .quad pagedir_iswritable
	.reloc ., R_X86_64_SIZE32, pagedir_iswritable; .int 0
	.int 0x29aa45
	.quad 0 /* index: 2630 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2631 /* index: 2631 */
	.weak cpu_swipi_pending; .quad cpu_swipi_pending
	.reloc ., R_X86_64_SIZE32, cpu_swipi_pending; .int 0
	.int 0xc8eba47
	.quad 0 /* index: 2632 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2633 /* index: 2633 */
	.weak empty_directory_entry; .quad empty_directory_entry
	.reloc ., R_X86_64_SIZE32, empty_directory_entry; .int 0
	.int 0x25ffa49
	.quad 0 /* index: 2634 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2635 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2636 /* index: 2636 */
	.weak sys32_tkill; .quad sys32_tkill
	.reloc ., R_X86_64_SIZE32, sys32_tkill; .int 0
	.int 0x8121a4c
	.quad .Lname2637 /* index: 2637 */
	.weak sys32_fgetxattr; .quad sys32_fgetxattr
	.reloc ., R_X86_64_SIZE32, sys32_fgetxattr; .int 0
	.int 0xad6ac62
	.quad .Lname2638 /* index: 2638 */
	.weak handle_lookupin; .quad handle_lookupin
	.reloc ., R_X86_64_SIZE32, handle_lookupin; .int 0
	.int 0x2f01a4e
	.quad .Lname2639 /* index: 2639 */
	.weak vm_datablock_findchanged; .quad vm_datablock_findchanged
	.reloc ., R_X86_64_SIZE32, vm_datablock_findchanged; .int 0
	.int 0x718c634
	.quad .Lname2640 /* index: 2640 */
	.weak x86_dbg_trapstatekind; .quad x86_dbg_trapstatekind
	.reloc ., R_X86_64_SIZE32, x86_dbg_trapstatekind; .int 0
	.int 0xf7a9e34
	.quad .Lname2641 /* index: 2641 */
	.weak superblock_mountlock_tryupgrade; .quad superblock_mountlock_tryupgrade
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_tryupgrade; .int 0
	.int 0xb5dadb5
	.quad .Lname2642 /* index: 2642 */
	.weak dbg_isholding_altgr; .quad dbg_isholding_altgr
	.reloc ., R_X86_64_SIZE32, dbg_isholding_altgr; .int 0
	.int 0xab9ea52
	.quad .Lname2643 /* index: 2643 */
	.weak task_connect_c; .quad task_connect_c
	.reloc ., R_X86_64_SIZE32, task_connect_c; .int 0
	.int 0xdeaca53
	.quad .Lname2644 /* index: 2644 */
	.weak json_parser_unyield; .quad json_parser_unyield
	.reloc ., R_X86_64_SIZE32, json_parser_unyield; .int 0
	.int 0x3607a54
	.quad .Lname2645 /* index: 2645 */
	.weak sys32_ftime; .quad sys32_ftime
	.reloc ., R_X86_64_SIZE32, sys32_ftime; .int 0
	.int 0x826aa55
	.quad .Lname2646 /* index: 2646 */
	.weak memeq_nopf; .quad memeq_nopf
	.reloc ., R_X86_64_SIZE32, memeq_nopf; .int 0
	.int 0xc738a56
	.quad 0 /* index: 2647 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2648 /* index: 2648 */
	.weak sys_lfutex; .quad sys_lfutex
	.reloc ., R_X86_64_SIZE32, sys_lfutex; .int 0
	.int 0x62a7a58
	.quad .Lname2649 /* index: 2649 */
	.weak zlib_reader_rewind; .quad zlib_reader_rewind
	.reloc ., R_X86_64_SIZE32, zlib_reader_rewind; .int 0
	.int 0x6298c64
	.quad 0 /* index: 2650 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2651 /* index: 2651 */
	.weak dbg_enter_scpustate_c; .quad dbg_enter_scpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_scpustate_c; .int 0
	.int 0x19d3ed3
	.quad .Lname2652 /* index: 2652 */
	.weak mempmovedownl; .quad mempmovedownl
	.reloc ., R_X86_64_SIZE32, mempmovedownl; .int 0
	.int 0xf7f1a5c
	.quad 0 /* index: 2653 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2654 /* index: 2654 */
	.weak rawmemrlen; .quad rawmemrlen
	.reloc ., R_X86_64_SIZE32, rawmemrlen; .int 0
	.int 0x3c31a5e
	.quad .Lname2655 /* index: 2655 */
	.weak sighand_ptr_lockwrite; .quad sighand_ptr_lockwrite
	.reloc ., R_X86_64_SIZE32, sighand_ptr_lockwrite; .int 0
	.int 0x44f0465
	.quad .Lname2656 /* index: 2656 */
	.weak block_device_lookup; .quad block_device_lookup
	.reloc ., R_X86_64_SIZE32, block_device_lookup; .int 0
	.int 0x7ed1a60
	.quad .Lname2657 /* index: 2657 */
	.weak sys_hop; .quad sys_hop
	.reloc ., R_X86_64_SIZE32, sys_hop; .int 0
	.int 0xb095f10
	.quad .Lname2658 /* index: 2658 */
	.weak kernel_syscall1_iscp32; .quad kernel_syscall1_iscp32
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_iscp32; .int 0
	.int 0x958fa62
	.quad 0 /* index: 2659 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2660 /* index: 2660 */
	.weak sys_epoll_ctl_old; .quad sys_epoll_ctl_old
	.reloc ., R_X86_64_SIZE32, sys_epoll_ctl_old; .int 0
	.int 0x69f7d24
	.quad .Lname2661 /* index: 2661 */
	.weak sys32_setregid32; .quad sys32_setregid32
	.reloc ., R_X86_64_SIZE32, sys32_setregid32; .int 0
	.int 0xe3cdbb2
	.quad 0 /* index: 2662 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2663 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2664 /* index: 2664 */
	.weak x86_syscall_emulate32_int80h; .quad x86_syscall_emulate32_int80h
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_int80h; .int 0
	.int 0x2dd5a68
	.quad 0 /* index: 2665 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2666 /* index: 2666 */
	.weak vm_find_first_node_greater_equal; .quad vm_find_first_node_greater_equal
	.reloc ., R_X86_64_SIZE32, vm_find_first_node_greater_equal; .int 0
	.int 0xe2f353c
	.quad .Lname2667 /* index: 2667 */
	.weak sys_kreaddir; .quad sys_kreaddir
	.reloc ., R_X86_64_SIZE32, sys_kreaddir; .int 0
	.int 0xf073d22
	.quad .Lname2668 /* index: 2668 */
	.weak json_parser_getnull; .quad json_parser_getnull
	.reloc ., R_X86_64_SIZE32, json_parser_getnull; .int 0
	.int 0x4f6da6c
	.quad .Lname2669 /* index: 2669 */
	.weak sys32_recvfrom; .quad sys32_recvfrom
	.reloc ., R_X86_64_SIZE32, sys32_recvfrom; .int 0
	.int 0xbca5a6d
	.quad .Lname2670 /* index: 2670 */
	.weak task_waitfor_norpc; .quad task_waitfor_norpc
	.reloc ., R_X86_64_SIZE32, task_waitfor_norpc; .int 0
	.int 0xecd6763
	.quad 0 /* index: 2671 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2672 /* index: 2672 */
	.weak sys32_coredump; .quad sys32_coredump
	.reloc ., R_X86_64_SIZE32, sys32_coredump; .int 0
	.int 0x6ed3a70
	.quad 0 /* index: 2673 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2674 /* index: 2674 */
	.weak sys_setitimer; .quad sys_setitimer
	.reloc ., R_X86_64_SIZE32, sys_setitimer; .int 0
	.int 0x203aa72
	.quad .Lname2675 /* index: 2675 */
	.weak dbg_getfunc; .quad dbg_getfunc
	.reloc ., R_X86_64_SIZE32, dbg_getfunc; .int 0
	.int 0xda05713
	.quad .Lname2676 /* index: 2676 */
	.weak debugline_scanunit; .quad debugline_scanunit
	.reloc ., R_X86_64_SIZE32, debugline_scanunit; .int 0
	.int 0xd2b0a74
	.quad .Lname2677 /* index: 2677 */
	.weak path_getchild_or_parent_inode; .quad path_getchild_or_parent_inode
	.reloc ., R_X86_64_SIZE32, path_getchild_or_parent_inode; .int 0
	.int 0x5b45a75
	.quad .Lname2678 /* index: 2678 */
	.weak __afailf; .quad __afailf
	.reloc ., R_X86_64_SIZE32, __afailf; .int 0
	.int 0x57c7a76
	.quad .Lname2679 /* index: 2679 */
	.weak cpu_hwipi_pending; .quad cpu_hwipi_pending
	.reloc ., R_X86_64_SIZE32, cpu_hwipi_pending; .int 0
	.int 0x98eba77
	.quad .Lname2680 /* index: 2680 */
	.weak sys32_futimesat; .quad sys32_futimesat
	.reloc ., R_X86_64_SIZE32, sys32_futimesat; .int 0
	.int 0xcabef44
	.quad .Lname2681 /* index: 2681 */
	.weak memcpy; .quad memcpy
	.reloc ., R_X86_64_SIZE32, memcpy; .int 0
	.int 0x73c3a79
	.quad 0 /* index: 2682 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2683 /* index: 2683 */
	.weak cpu_delrunningtask; .quad cpu_delrunningtask
	.reloc ., R_X86_64_SIZE32, cpu_delrunningtask; .int 0
	.int 0x2d0ba7b
	.quad .Lname2684 /* index: 2684 */
	.weak pipe_reader_create; .quad pipe_reader_create
	.reloc ., R_X86_64_SIZE32, pipe_reader_create; .int 0
	.int 0xa6f7f85
	.quad 0 /* index: 2685 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2686 /* index: 2686 */
	.weak sys_openat; .quad sys_openat
	.reloc ., R_X86_64_SIZE32, sys_openat; .int 0
	.int 0x6611414
	.quad .Lname2687 /* index: 2687 */
	.weak page_freeone; .quad page_freeone
	.reloc ., R_X86_64_SIZE32, page_freeone; .int 0
	.int 0xaec7f15
	.quad .Lname2688 /* index: 2688 */
	.weak pagedir_mapone_p; .quad pagedir_mapone_p
	.reloc ., R_X86_64_SIZE32, pagedir_mapone_p; .int 0
	.int 0x3e36a80
	.quad .Lname2689 /* index: 2689 */
	.weak x86_dbg_hostbackup; .quad x86_dbg_hostbackup
	.reloc ., R_X86_64_SIZE32, x86_dbg_hostbackup; .int 0
	.int 0x509b1c0
	.quad .Lname2690 /* index: 2690 */
	.weak sys32_getresgid32; .quad sys32_getresgid32
	.reloc ., R_X86_64_SIZE32, sys32_getresgid32; .int 0
	.int 0x4bb3a82
	.quad 0 /* index: 2691 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2692 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2693 /* index: 2693 */
	.weak cpu_ipi_service; .quad cpu_ipi_service
	.reloc ., R_X86_64_SIZE32, cpu_ipi_service; .int 0
	.int 0x2a9ca85
	.quad .Lname2694 /* index: 2694 */
	.weak sys_getuid; .quad sys_getuid
	.reloc ., R_X86_64_SIZE32, sys_getuid; .int 0
	.int 0x5db0b64
	.quad .Lname2695 /* index: 2695 */
	.weak dbg; .quad dbg
	.reloc ., R_X86_64_SIZE32, dbg; .int 0
	.int 0x6a87
	.quad .Lname2696 /* index: 2696 */
	.weak task_alloc_user_rpc; .quad task_alloc_user_rpc
	.reloc ., R_X86_64_SIZE32, task_alloc_user_rpc; .int 0
	.int 0x79cab3
	.quad .Lname2697 /* index: 2697 */
	.weak vm_datapart_freeswap; .quad vm_datapart_freeswap
	.reloc ., R_X86_64_SIZE32, vm_datapart_freeswap; .int 0
	.int 0xd6f8500
	.quad 0 /* index: 2698 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2699 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2700 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2701 /* index: 2701 */
	.weak sys32_sched_setattr; .quad sys32_sched_setattr
	.reloc ., R_X86_64_SIZE32, sys32_sched_setattr; .int 0
	.int 0xb5259c2
	.quad 0 /* index: 2702 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2703 /* index: 2703 */
	.weak sys32_mount; .quad sys32_mount
	.reloc ., R_X86_64_SIZE32, sys32_mount; .int 0
	.int 0x8396e34
	.quad 0 /* index: 2704 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2705 /* index: 2705 */
	.weak vio_writeq; .quad vio_writeq
	.reloc ., R_X86_64_SIZE32, vio_writeq; .int 0
	.int 0x6f0da91
	.quad .Lname2706 /* index: 2706 */
	.weak mouse_device_motion_nopr; .quad mouse_device_motion_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_motion_nopr; .int 0
	.int 0xe103a92
	.quad .Lname2707 /* index: 2707 */
	.weak error_class; .quad error_class
	.reloc ., R_X86_64_SIZE32, error_class; .int 0
	.int 0x836b1c3
	.quad .Lname2708 /* index: 2708 */
	.weak dbg_screen_height; .quad dbg_screen_height
	.reloc ., R_X86_64_SIZE32, dbg_screen_height; .int 0
	.int 0xc29ca94
	.quad .Lname2709 /* index: 2709 */
	.weak kernel_syscall1_restartmode; .quad kernel_syscall1_restartmode
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_restartmode; .int 0
	.int 0x828fa95
	.quad .Lname2710 /* index: 2710 */
	.weak cpu_private_function_callbuf; .quad cpu_private_function_callbuf
	.reloc ., R_X86_64_SIZE32, cpu_private_function_callbuf; .int 0
	.int 0xf451a96
	.quad .Lname2711 /* index: 2711 */
	.weak sys32_request_key; .quad sys32_request_key
	.reloc ., R_X86_64_SIZE32, sys32_request_key; .int 0
	.int 0x4bbaf19
	.quad 0 /* index: 2712 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2713 /* index: 2713 */
	.weak memset; .quad memset
	.reloc ., R_X86_64_SIZE32, memset; .int 0
	.int 0x73c49c4
	.quad 0 /* index: 2714 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2715 /* index: 2715 */
	.weak sys_afs_syscall; .quad sys_afs_syscall
	.reloc ., R_X86_64_SIZE32, sys_afs_syscall; .int 0
	.int 0x45e344c
	.quad 0 /* index: 2716 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2717 /* index: 2717 */
	.weak vm_tasklock_endwrite; .quad vm_tasklock_endwrite
	.reloc ., R_X86_64_SIZE32, vm_tasklock_endwrite; .int 0
	.int 0x68a2ad5
	.quad .Lname2718 /* index: 2718 */
	.weak x86_userexcept_raisesignal_from_exception; .quad x86_userexcept_raisesignal_from_exception
	.reloc ., R_X86_64_SIZE32, x86_userexcept_raisesignal_from_exception; .int 0
	.int 0x1898a9e
	.quad .Lname2719 /* index: 2719 */
	.weak pagedir_isuseraccessible; .quad pagedir_isuseraccessible
	.reloc ., R_X86_64_SIZE32, pagedir_isuseraccessible; .int 0
	.int 0x24251c5
	.quad .Lname2720 /* index: 2720 */
	.weak directory_getcaseentry_p; .quad directory_getcaseentry_p
	.reloc ., R_X86_64_SIZE32, directory_getcaseentry_p; .int 0
	.int 0xb2b6aa0
	.quad 0 /* index: 2721 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2722 /* index: 2722 */
	.weak vio_readb; .quad vio_readb
	.reloc ., R_X86_64_SIZE32, vio_readb; .int 0
	.int 0x568caa2
	.quad .Lname2723 /* index: 2723 */
	.weak x86_dbgidt_ptr; .quad x86_dbgidt_ptr
	.reloc ., R_X86_64_SIZE32, x86_dbgidt_ptr; .int 0
	.int 0x47dc8d2
	.quad 0 /* index: 2724 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2725 /* index: 2725 */
	.weak kernel_debugtrap_r_fcpustate; .quad kernel_debugtrap_r_fcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_fcpustate; .int 0
	.int 0xed50aa5
	.quad .Lname2726 /* index: 2726 */
	.weak vm_datapart_lockread_setcore_unsharecow_nx; .quad vm_datapart_lockread_setcore_unsharecow_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockread_setcore_unsharecow_nx; .int 0
	.int 0xfc3afd8
	.quad .Lname2727 /* index: 2727 */
	.weak slab_kmalloc_nx64; .quad slab_kmalloc_nx64
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx64; .int 0
	.int 0x40d3d24
	.quad .Lname2728 /* index: 2728 */
	.weak path_sprintentex; .quad path_sprintentex
	.reloc ., R_X86_64_SIZE32, path_sprintentex; .int 0
	.int 0xbc74aa8
	.quad .Lname2729 /* index: 2729 */
	.weak x86_getiopl; .quad x86_getiopl
	.reloc ., R_X86_64_SIZE32, x86_getiopl; .int 0
	.int 0xdb15a3c
	.quad 0 /* index: 2730 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2731 /* index: 2731 */
	.weak cpu_addrunningtask; .quad cpu_addrunningtask
	.reloc ., R_X86_64_SIZE32, cpu_addrunningtask; .int 0
	.int 0x450baab
	.quad .Lname2732 /* index: 2732 */
	.weak sys32_tgkill; .quad sys32_tgkill
	.reloc ., R_X86_64_SIZE32, sys32_tgkill; .int 0
	.int 0x11e7aac
	.quad .Lname2733 /* index: 2733 */
	.weak path_free; .quad path_free
	.reloc ., R_X86_64_SIZE32, path_free; .int 0
	.int 0xae5ae35
	.quad 0 /* index: 2734 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2735 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2736 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2737 /* index: 2737 */
	.weak sys32_sched_getattr; .quad sys32_sched_getattr
	.reloc ., R_X86_64_SIZE32, sys32_sched_getattr; .int 0
	.int 0xf5259f2
	.quad .Lname2738 /* index: 2738 */
	.weak sys_sched_setattr; .quad sys_sched_setattr
	.reloc ., R_X86_64_SIZE32, sys_sched_setattr; .int 0
	.int 0x2f3ab2
	.quad .Lname2739 /* index: 2739 */
	.weak inode_areadallv_phys; .quad inode_areadallv_phys
	.reloc ., R_X86_64_SIZE32, inode_areadallv_phys; .int 0
	.int 0xe6b7ab3
	.quad .Lname2740 /* index: 2740 */
	.weak sys32_renameat; .quad sys32_renameat
	.reloc ., R_X86_64_SIZE32, sys32_renameat; .int 0
	.int 0xc22bab4
	.quad .Lname2741 /* index: 2741 */
	.weak regdump_icpustate; .quad regdump_icpustate
	.reloc ., R_X86_64_SIZE32, regdump_icpustate; .int 0
	.int 0xbf44ab5
	.quad .Lname2742 /* index: 2742 */
	.weak sys_pwritevf; .quad sys_pwritevf
	.reloc ., R_X86_64_SIZE32, sys_pwritevf; .int 0
	.int 0x9403ab6
	.quad .Lname2743 /* index: 2743 */
	.weak vio_readw; .quad vio_readw
	.reloc ., R_X86_64_SIZE32, vio_readw; .int 0
	.int 0x568cab7
	.quad .Lname2744 /* index: 2744 */
	.weak vm_copyfromphys_onepage_nopf; .quad vm_copyfromphys_onepage_nopf
	.reloc ., R_X86_64_SIZE32, vm_copyfromphys_onepage_nopf; .int 0
	.int 0xb387e96
	.quad .Lname2745 /* index: 2745 */
	.weak sys32_waitid; .quad sys32_waitid
	.reloc ., R_X86_64_SIZE32, sys32_waitid; .int 0
	.int 0x1686c74
	.quad 0 /* index: 2746 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2747 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2748 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2749 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2750 /* index: 2750 */
	.weak vio_writel_aligned; .quad vio_writel_aligned
	.reloc ., R_X86_64_SIZE32, vio_writel_aligned; .int 0
	.int 0x8f53c14
	.quad 0 /* index: 2751 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2752 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2753 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2754 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2755 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2756 /* index: 2756 */
	.weak directory_mknod; .quad directory_mknod
	.reloc ., R_X86_64_SIZE32, directory_mknod; .int 0
	.int 0x7fadac4
	.quad .Lname2757 /* index: 2757 */
	.weak dbg_readline; .quad dbg_readline
	.reloc ., R_X86_64_SIZE32, dbg_readline; .int 0
	.int 0xdd3fac5
	.quad .Lname2758 /* index: 2758 */
	.weak vm_copytophys_nopf; .quad vm_copytophys_nopf
	.reloc ., R_X86_64_SIZE32, vm_copytophys_nopf; .int 0
	.int 0x1708ac6
	.quad .Lname2759 /* index: 2759 */
	.weak sys_rt_sigpending; .quad sys_rt_sigpending
	.reloc ., R_X86_64_SIZE32, sys_rt_sigpending; .int 0
	.int 0xf593ac7
	.quad 0 /* index: 2760 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2761 /* index: 2761 */
	.weak ioperm_bitmap_destroy; .quad ioperm_bitmap_destroy
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_destroy; .int 0
	.int 0xcb05ac9
	.quad .Lname2762 /* index: 2762 */
	.weak vm_forcefault; .quad vm_forcefault
	.reloc ., R_X86_64_SIZE32, vm_forcefault; .int 0
	.int 0x4895ec4
	.quad .Lname2763 /* index: 2763 */
	.weak sys32_unlink; .quad sys32_unlink
	.reloc ., R_X86_64_SIZE32, sys32_unlink; .int 0
	.int 0x1154acb
	.quad .Lname2764 /* index: 2764 */
	.weak dbg_enter_scpustate_cr; .quad dbg_enter_scpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_scpustate_cr; .int 0
	.int 0x9d3edb2
	.quad .Lname2765 /* index: 2765 */
	.weak vm_do_allocram; .quad vm_do_allocram
	.reloc ., R_X86_64_SIZE32, vm_do_allocram; .int 0
	.int 0x28efacd
	.quad 0 /* index: 2766 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2767 /* index: 2767 */
	.weak sys_sync; .quad sys_sync
	.reloc ., R_X86_64_SIZE32, sys_sync; .int 0
	.int 0x96a9f3
	.quad .Lname2768 /* index: 2768 */
	.weak vm_kernel_syncall; .quad vm_kernel_syncall
	.reloc ., R_X86_64_SIZE32, vm_kernel_syncall; .int 0
	.int 0x80d105c
	.quad .Lname2769 /* index: 2769 */
	.weak sys_setgid; .quad sys_setgid
	.reloc ., R_X86_64_SIZE32, sys_setgid; .int 0
	.int 0x69b1d64
	.quad 0 /* index: 2770 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2771 /* index: 2771 */
	.weak heap_alloc; .quad heap_alloc
	.reloc ., R_X86_64_SIZE32, heap_alloc; .int 0
	.int 0x652dad3
	.quad .Lname2772 /* index: 2772 */
	.weak superblock_nodeslock_tryread; .quad superblock_nodeslock_tryread
	.reloc ., R_X86_64_SIZE32, superblock_nodeslock_tryread; .int 0
	.int 0xda0ead4
	.quad .Lname2773 /* index: 2773 */
	.weak _Unwind_Resume; .quad _Unwind_Resume
	.reloc ., R_X86_64_SIZE32, _Unwind_Resume; .int 0
	.int 0x8d2aad5
	.quad .Lname2774 /* index: 2774 */
	.weak vm_read; .quad vm_read
	.reloc ., R_X86_64_SIZE32, vm_read; .int 0
	.int 0xd368b04
	.quad 0 /* index: 2775 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2776 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2777 /* index: 2777 */
	.weak task_raisesignalthread; .quad task_raisesignalthread
	.reloc ., R_X86_64_SIZE32, task_raisesignalthread; .int 0
	.int 0xe5fc724
	.quad 0 /* index: 2778 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2779 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2780 /* index: 2780 */
	.weak json_writer_putnull; .quad json_writer_putnull
	.reloc ., R_X86_64_SIZE32, json_writer_putnull; .int 0
	.int 0xd67dadc
	.quad 0 /* index: 2781 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2782 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2783 /* index: 2783 */
	.weak sys32_fallocate; .quad sys32_fallocate
	.reloc ., R_X86_64_SIZE32, sys32_fallocate; .int 0
	.int 0x55dbf25
	.quad .Lname2784 /* index: 2784 */
	.weak x86_syscall_emulate32_int80h_r; .quad x86_syscall_emulate32_int80h_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_int80h_r; .int 0
	.int 0xd5a70b2
	.quad .Lname2785 /* index: 2785 */
	.weak dbg_enter_kcpustate_r; .quad dbg_enter_kcpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_kcpustate_r; .int 0
	.int 0x1b53ee2
	.quad .Lname2786 /* index: 2786 */
	.weak sys32_getgroups32; .quad sys32_getgroups32
	.reloc ., R_X86_64_SIZE32, sys32_getgroups32; .int 0
	.int 0x14abae2
	.quad .Lname2787 /* index: 2787 */
	.weak aio_buffer_copyfromphys; .quad aio_buffer_copyfromphys
	.reloc ., R_X86_64_SIZE32, aio_buffer_copyfromphys; .int 0
	.int 0x516dae3
	.quad .Lname2788 /* index: 2788 */
	.weak mouse_device_stat; .quad mouse_device_stat
	.reloc ., R_X86_64_SIZE32, mouse_device_stat; .int 0
	.int 0x2980ae4
	.quad .Lname2789 /* index: 2789 */
	.weak sys_getcpu; .quad sys_getcpu
	.reloc ., R_X86_64_SIZE32, sys_getcpu; .int 0
	.int 0x5db1ae5
	.quad 0 /* index: 2790 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2791 /* index: 2791 */
	.weak cpu_quantum_remaining; .quad cpu_quantum_remaining
	.reloc ., R_X86_64_SIZE32, cpu_quantum_remaining; .int 0
	.int 0x395fae7
	.quad .Lname2792 /* index: 2792 */
	.weak sys_tee; .quad sys_tee
	.reloc ., R_X86_64_SIZE32, sys_tee; .int 0
	.int 0xb096ac5
	.quad .Lname2793 /* index: 2793 */
	.weak rwlock_tryread_readonly; .quad rwlock_tryread_readonly
	.reloc ., R_X86_64_SIZE32, rwlock_tryread_readonly; .int 0
	.int 0x9439ae9
	.quad .Lname2794 /* index: 2794 */
	.weak sys_memfd_create; .quad sys_memfd_create
	.reloc ., R_X86_64_SIZE32, sys_memfd_create; .int 0
	.int 0x39534b5
	.quad .Lname2795 /* index: 2795 */
	.weak sys_freadlinkat; .quad sys_freadlinkat
	.reloc ., R_X86_64_SIZE32, sys_freadlinkat; .int 0
	.int 0x473c1f4
	.quad .Lname2796 /* index: 2796 */
	.weak vio_writel; .quad vio_writel
	.reloc ., R_X86_64_SIZE32, vio_writel; .int 0
	.int 0x6f0daec
	.quad .Lname2797 /* index: 2797 */
	.weak cpu_run_current_and_remember; .quad cpu_run_current_and_remember
	.reloc ., R_X86_64_SIZE32, cpu_run_current_and_remember; .int 0
	.int 0x5baf9d2
	.quad 0 /* index: 2798 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2799 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2800 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2801 /* index: 2801 */
	.weak superblock_mountlock_write_nx; .quad superblock_mountlock_write_nx
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_write_nx; .int 0
	.int 0x91da728
	.quad 0 /* index: 2802 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2803 /* index: 2803 */
	.weak unwind_instruction_succ; .quad unwind_instruction_succ
	.reloc ., R_X86_64_SIZE32, unwind_instruction_succ; .int 0
	.int 0xb64baf3
	.quad .Lname2804 /* index: 2804 */
	.weak json_writer_putuint64; .quad json_writer_putuint64
	.reloc ., R_X86_64_SIZE32, json_writer_putuint64; .int 0
	.int 0x73eaaf4
	.quad .Lname2805 /* index: 2805 */
	.weak kernel_debugtrap_ucpustate; .quad kernel_debugtrap_ucpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_ucpustate; .int 0
	.int 0x963baf5
	.quad 0 /* index: 2806 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2807 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2808 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2809 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2810 /* index: 2810 */
	.weak sys_name_to_handle_at; .quad sys_name_to_handle_at
	.reloc ., R_X86_64_SIZE32, sys_name_to_handle_at; .int 0
	.int 0xb83f354
	.quad 0 /* index: 2811 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2812 /* index: 2812 */
	.weak x86_dbg_setregbyidp; .quad x86_dbg_setregbyidp
	.reloc ., R_X86_64_SIZE32, x86_dbg_setregbyidp; .int 0
	.int 0x30c6ec0
	.quad .Lname2813 /* index: 2813 */
	.weak vm_datapart_do_copyram; .quad vm_datapart_do_copyram
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_copyram; .int 0
	.int 0xb4f0afd
	.quad 0 /* index: 2814 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2815 /* index: 2815 */
	.weak rwlock_pollwrite; .quad rwlock_pollwrite
	.reloc ., R_X86_64_SIZE32, rwlock_pollwrite; .int 0
	.int 0x89689d5
	.quad .Lname2816 /* index: 2816 */
	.weak pagedir_unprepare_map_p; .quad pagedir_unprepare_map_p
	.reloc ., R_X86_64_SIZE32, pagedir_unprepare_map_p; .int 0
	.int 0x7bdfb00
	.quad .Lname2817 /* index: 2817 */
	.weak task_rpc_exec_here; .quad task_rpc_exec_here
	.reloc ., R_X86_64_SIZE32, task_rpc_exec_here; .int 0
	.int 0x5541105
	.quad .Lname2818 /* index: 2818 */
	.weak sighand_reset_handler; .quad sighand_reset_handler
	.reloc ., R_X86_64_SIZE32, sighand_reset_handler; .int 0
	.int 0xb656b02
	.quad .Lname2819 /* index: 2819 */
	.weak inode_writev_phys; .quad inode_writev_phys
	.reloc ., R_X86_64_SIZE32, inode_writev_phys; .int 0
	.int 0x7b88b03
	.quad .Lname2820 /* index: 2820 */
	.weak sys32_prlimit64; .quad sys32_prlimit64
	.reloc ., R_X86_64_SIZE32, sys32_prlimit64; .int 0
	.int 0x4ac1b04
	.quad .Lname2821 /* index: 2821 */
	.weak __crt_unreachable; .quad __crt_unreachable
	.reloc ., R_X86_64_SIZE32, __crt_unreachable; .int 0
	.int 0xd917b05
	.quad 0 /* index: 2822 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2823 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2824 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2825 /* index: 2825 */
	.weak cpu_sendipi; .quad cpu_sendipi
	.reloc ., R_X86_64_SIZE32, cpu_sendipi; .int 0
	.int 0x9eeeb09
	.quad 0 /* index: 2826 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2827 /* index: 2827 */
	.weak sys_madvise; .quad sys_madvise
	.reloc ., R_X86_64_SIZE32, sys_madvise; .int 0
	.int 0x300d9f5
	.quad .Lname2828 /* index: 2828 */
	.weak sys32_fchown; .quad sys32_fchown
	.reloc ., R_X86_64_SIZE32, sys32_fchown; .int 0
	.int 0x279905e
	.quad .Lname2829 /* index: 2829 */
	.weak sys32_write; .quad sys32_write
	.reloc ., R_X86_64_SIZE32, sys32_write; .int 0
	.int 0x81596c5
	.quad 0 /* index: 2830 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2831 /* index: 2831 */
	.weak sys32_mkdirat; .quad sys32_mkdirat
	.reloc ., R_X86_64_SIZE32, sys32_mkdirat; .int 0
	.int 0x91d60b4
	.quad 0 /* index: 2832 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2833 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2834 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2835 /* index: 2835 */
	.weak inode_sync; .quad inode_sync
	.reloc ., R_X86_64_SIZE32, inode_sync; .int 0
	.int 0xab1ab13
	.quad .Lname2836 /* index: 2836 */
	.weak debuginfo_cu_parser_next; .quad debuginfo_cu_parser_next
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_next; .int 0
	.int 0xe0c2b14
	.quad .Lname2837 /* index: 2837 */
	.weak cpu_apply_ucpustate; .quad cpu_apply_ucpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_ucpustate; .int 0
	.int 0xa8c9b15
	.quad 0 /* index: 2838 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2839 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2840 /* index: 2840 */
	.weak vm_startdma_nx; .quad vm_startdma_nx
	.reloc ., R_X86_64_SIZE32, vm_startdma_nx; .int 0
	.int 0x9d9db18
	.quad .Lname2841 /* index: 2841 */
	.weak sys32_msync; .quad sys32_msync
	.reloc ., R_X86_64_SIZE32, sys32_msync; .int 0
	.int 0x83faa23
	.quad 0 /* index: 2842 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2843 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2844 /* index: 2844 */
	.weak slab_kmalloc64; .quad slab_kmalloc64
	.reloc ., R_X86_64_SIZE32, slab_kmalloc64; .int 0
	.int 0x66b3104
	.quad 0 /* index: 2845 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2846 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2847 /* index: 2847 */
	.weak thiscpu_idle; .quad thiscpu_idle
	.reloc ., R_X86_64_SIZE32, thiscpu_idle; .int 0
	.int 0x1af485
	.quad 0 /* index: 2848 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2849 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2850 /* index: 2850 */
	.weak sys32_faccessat; .quad sys32_faccessat
	.reloc ., R_X86_64_SIZE32, sys32_faccessat; .int 0
	.int 0xff48ef4
	.quad .Lname2851 /* index: 2851 */
	.weak block_device_writev_phys; .quad block_device_writev_phys
	.reloc ., R_X86_64_SIZE32, block_device_writev_phys; .int 0
	.int 0x6f74b23
	.quad .Lname2852 /* index: 2852 */
	.weak isr_register_at; .quad isr_register_at
	.reloc ., R_X86_64_SIZE32, isr_register_at; .int 0
	.int 0x2c4cb24
	.quad .Lname2853 /* index: 2853 */
	.weak driver_with_file; .quad driver_with_file
	.reloc ., R_X86_64_SIZE32, driver_with_file; .int 0
	.int 0x6271b25
	.quad 0 /* index: 2854 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2855 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2856 /* index: 2856 */
	.weak devfs_lock_upgrade_nx; .quad devfs_lock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, devfs_lock_upgrade_nx; .int 0
	.int 0xe953b28
	.quad .Lname2857 /* index: 2857 */
	.weak keyboard_buffer_getkey; .quad keyboard_buffer_getkey
	.reloc ., R_X86_64_SIZE32, keyboard_buffer_getkey; .int 0
	.int 0x5400b29
	.quad 0 /* index: 2858 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2859 /* index: 2859 */
	.weak sys32_recvmsg; .quad sys32_recvmsg
	.reloc ., R_X86_64_SIZE32, sys32_recvmsg; .int 0
	.int 0x3bcbc87
	.quad 0 /* index: 2860 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2861 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2862 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2863 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2864 /* index: 2864 */
	.weak this_task; .quad this_task
	.reloc ., R_X86_64_SIZE32, this_task; .int 0
	.int 0x96d26b
	.quad 0 /* index: 2865 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2866 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2867 /* index: 2867 */
	.weak slab_kmalloc; .quad slab_kmalloc
	.reloc ., R_X86_64_SIZE32, slab_kmalloc; .int 0
	.int 0x7966b33
	.quad .Lname2868 /* index: 2868 */
	.weak sys32_futimesat64; .quad sys32_futimesat64
	.reloc ., R_X86_64_SIZE32, sys32_futimesat64; .int 0
	.int 0xbef4b34
	.quad .Lname2869 /* index: 2869 */
	.weak dbg_enter_icpustate; .quad dbg_enter_icpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_icpustate; .int 0
	.int 0x781ab35
	.quad .Lname2870 /* index: 2870 */
	.weak json_parser_prev; .quad json_parser_prev
	.reloc ., R_X86_64_SIZE32, json_parser_prev; .int 0
	.int 0x827eb36
	.quad 0 /* index: 2871 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2872 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2873 /* index: 2873 */
	.weak sys32_setresgid; .quad sys32_setresgid
	.reloc ., R_X86_64_SIZE32, sys32_setresgid; .int 0
	.int 0xde48f34
	.quad 0 /* index: 2874 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2875 /* index: 2875 */
	.weak sys_rt_tgsigqueueinfo; .quad sys_rt_tgsigqueueinfo
	.reloc ., R_X86_64_SIZE32, sys_rt_tgsigqueueinfo; .int 0
	.int 0xb4df1df
	.quad .Lname2876 /* index: 2876 */
	.weak fs_filesystems_loadall; .quad fs_filesystems_loadall
	.reloc ., R_X86_64_SIZE32, fs_filesystems_loadall; .int 0
	.int 0x6e7fb3c
	.quad .Lname2877 /* index: 2877 */
	.weak sys_sched_getparam; .quad sys_sched_getparam
	.reloc ., R_X86_64_SIZE32, sys_sched_getparam; .int 0
	.int 0x2ed9b3d
	.quad .Lname2878 /* index: 2878 */
	.weak sys_chmod; .quad sys_chmod
	.reloc ., R_X86_64_SIZE32, sys_chmod; .int 0
	.int 0x959a954
	.quad .Lname2879 /* index: 2879 */
	.weak sys_sendto; .quad sys_sendto
	.reloc ., R_X86_64_SIZE32, sys_sendto; .int 0
	.int 0x69dfb3f
	.quad .Lname2880 /* index: 2880 */
	.weak character_device_lookup; .quad character_device_lookup
	.reloc ., R_X86_64_SIZE32, character_device_lookup; .int 0
	.int 0x93bab40
	.quad .Lname2881 /* index: 2881 */
	.weak slab_kmalloc40; .quad slab_kmalloc40
	.reloc ., R_X86_64_SIZE32, slab_kmalloc40; .int 0
	.int 0x66b31e0
	.quad 0 /* index: 2882 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2883 /* index: 2883 */
	.weak vm_tasklock_endread; .quad vm_tasklock_endread
	.reloc ., R_X86_64_SIZE32, vm_tasklock_endread; .int 0
	.int 0x768c2d4
	.quad .Lname2884 /* index: 2884 */
	.weak sys32_capget; .quad sys32_capget
	.reloc ., R_X86_64_SIZE32, sys32_capget; .int 0
	.int 0x2280b44
	.quad .Lname2885 /* index: 2885 */
	.weak handle_get_directory_node; .quad handle_get_directory_node
	.reloc ., R_X86_64_SIZE32, handle_get_directory_node; .int 0
	.int 0x247eb45
	.quad .Lname2886 /* index: 2886 */
	.weak sys32_getdrives; .quad sys32_getdrives
	.reloc ., R_X86_64_SIZE32, sys32_getdrives; .int 0
	.int 0xcd12a03
	.quad .Lname2887 /* index: 2887 */
	.weak inode_readv_phys_blocking; .quad inode_readv_phys_blocking
	.reloc ., R_X86_64_SIZE32, inode_readv_phys_blocking; .int 0
	.int 0xd7cbb47
	.quad 0 /* index: 2888 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2889 /* index: 2889 */
	.weak dbg_readmemory; .quad dbg_readmemory
	.reloc ., R_X86_64_SIZE32, dbg_readmemory; .int 0
	.int 0x3eecb49
	.quad 0 /* index: 2890 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2891 /* index: 2891 */
	.weak handle_get_taskpid; .quad handle_get_taskpid
	.reloc ., R_X86_64_SIZE32, handle_get_taskpid; .int 0
	.int 0x73da5b4
	.quad 0 /* index: 2892 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2893 /* index: 2893 */
	.weak strlen; .quad strlen
	.reloc ., R_X86_64_SIZE32, strlen; .int 0
	.int 0x7ab92be
	.quad 0 /* index: 2894 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2895 /* index: 2895 */
	.weak dbg_enter_kcpustate_cr; .quad dbg_enter_kcpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_kcpustate_cr; .int 0
	.int 0xb53edb2
	.quad 0 /* index: 2896 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2897 /* index: 2897 */
	.weak x86_userexcept_unwind_interrupt; .quad x86_userexcept_unwind_interrupt
	.reloc ., R_X86_64_SIZE32, x86_userexcept_unwind_interrupt; .int 0
	.int 0xbc98324
	.quad .Lname2898 /* index: 2898 */
	.weak block_device_awritev_phys_sector; .quad block_device_awritev_phys_sector
	.reloc ., R_X86_64_SIZE32, block_device_awritev_phys_sector; .int 0
	.int 0xb832b52
	.quad 0 /* index: 2899 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2900 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2901 /* index: 2901 */
	.weak devfs_remove; .quad devfs_remove
	.reloc ., R_X86_64_SIZE32, devfs_remove; .int 0
	.int 0x290b55
	.quad .Lname2902 /* index: 2902 */
	.weak sys32_close; .quad sys32_close
	.reloc ., R_X86_64_SIZE32, sys32_close; .int 0
	.int 0x82330f5
	.quad .Lname2903 /* index: 2903 */
	.weak path_destroy; .quad path_destroy
	.reloc ., R_X86_64_SIZE32, path_destroy; .int 0
	.int 0xda21739
	.quad .Lname2904 /* index: 2904 */
	.weak rwlock_write_nx; .quad rwlock_write_nx
	.reloc ., R_X86_64_SIZE32, rwlock_write_nx; .int 0
	.int 0xc503b58
	.quad .Lname2905 /* index: 2905 */
	.weak keyboard_device_stat; .quad keyboard_device_stat
	.reloc ., R_X86_64_SIZE32, keyboard_device_stat; .int 0
	.int 0xf1539e4
	.quad 0 /* index: 2906 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2907 /* index: 2907 */
	.weak vm_datapart_write_phys; .quad vm_datapart_write_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_write_phys; .int 0
	.int 0x99dd2d3
	.quad .Lname2908 /* index: 2908 */
	.weak sys32_ioprio_set; .quad sys32_ioprio_set
	.reloc ., R_X86_64_SIZE32, sys32_ioprio_set; .int 0
	.int 0xe873fd4
	.quad 0 /* index: 2909 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2910 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2911 /* index: 2911 */
	.weak sys_swapoff; .quad sys_swapoff
	.reloc ., R_X86_64_SIZE32, sys_swapoff; .int 0
	.int 0xaa37ca6
	.quad 0 /* index: 2912 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2913 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2914 /* index: 2914 */
	.weak x86_syscall_emulate32_sysenter; .quad x86_syscall_emulate32_sysenter
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_sysenter; .int 0
	.int 0x8bb5b62
	.quad .Lname2915 /* index: 2915 */
	.weak block_device_writev_sync; .quad block_device_writev_sync
	.reloc ., R_X86_64_SIZE32, block_device_writev_sync; .int 0
	.int 0x6f78b63
	.quad .Lname2916 /* index: 2916 */
	.weak handle_get_superblock_relaxed; .quad handle_get_superblock_relaxed
	.reloc ., R_X86_64_SIZE32, handle_get_superblock_relaxed; .int 0
	.int 0x5e03b64
	.quad .Lname2917 /* index: 2917 */
	.weak inode_awritev; .quad inode_awritev
	.reloc ., R_X86_64_SIZE32, inode_awritev; .int 0
	.int 0x8bea1e6
	.quad 0 /* index: 2918 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2919 /* index: 2919 */
	.weak vm_datapart_free; .quad vm_datapart_free
	.reloc ., R_X86_64_SIZE32, vm_datapart_free; .int 0
	.int 0x3288d65
	.quad 0 /* index: 2920 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2921 /* index: 2921 */
	.weak directory_getcaseentry; .quad directory_getcaseentry
	.reloc ., R_X86_64_SIZE32, directory_getcaseentry; .int 0
	.int 0x7cb2b69
	.quad 0 /* index: 2922 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2923 /* index: 2923 */
	.weak tty_device_stopfwd; .quad tty_device_stopfwd
	.reloc ., R_X86_64_SIZE32, tty_device_stopfwd; .int 0
	.int 0x1e21d14
	.quad .Lname2924 /* index: 2924 */
	.weak vm_datapart_lock_write; .quad vm_datapart_lock_write
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_write; .int 0
	.int 0x44710f5
	.quad .Lname2925 /* index: 2925 */
	.weak vm_destroy; .quad vm_destroy
	.reloc ., R_X86_64_SIZE32, vm_destroy; .int 0
	.int 0xacd6c39
	.quad 0 /* index: 2926 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2927 /* index: 2927 */
	.weak sys32_utimensat; .quad sys32_utimensat
	.reloc ., R_X86_64_SIZE32, sys32_utimensat; .int 0
	.int 0xa544e24
	.quad .Lname2928 /* index: 2928 */
	.weak unwind_setreg_kcpustate_exclusive; .quad unwind_setreg_kcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_kcpustate_exclusive; .int 0
	.int 0x38e5125
	.quad .Lname2929 /* index: 2929 */
	.weak slab_kmalloc48; .quad slab_kmalloc48
	.reloc ., R_X86_64_SIZE32, slab_kmalloc48; .int 0
	.int 0x66b31e8
	.quad 0 /* index: 2930 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2931 /* index: 2931 */
	.weak sys_fdatasync; .quad sys_fdatasync
	.reloc ., R_X86_64_SIZE32, sys_fdatasync; .int 0
	.int 0x3a1f493
	.quad .Lname2932 /* index: 2932 */
	.weak regdump_sgregs_with_cs_ss; .quad regdump_sgregs_with_cs_ss
	.reloc ., R_X86_64_SIZE32, regdump_sgregs_with_cs_ss; .int 0
	.int 0xe382283
	.quad .Lname2933 /* index: 2933 */
	.weak cfmakesane; .quad cfmakesane
	.reloc ., R_X86_64_SIZE32, cfmakesane; .int 0
	.int 0x81a0b75
	.quad 0 /* index: 2934 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2935 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2936 /* index: 2936 */
	.weak vm_datapart_split; .quad vm_datapart_split
	.reloc ., R_X86_64_SIZE32, vm_datapart_split; .int 0
	.int 0x2bf5034
	.quad .Lname2937 /* index: 2937 */
	.weak sys32_freadlinkat; .quad sys32_freadlinkat
	.reloc ., R_X86_64_SIZE32, sys32_freadlinkat; .int 0
	.int 0x30adc94
	.quad .Lname2938 /* index: 2938 */
	.weak vm_syncall; .quad vm_syncall
	.reloc ., R_X86_64_SIZE32, vm_syncall; .int 0
	.int 0xb03454c
	.quad 0 /* index: 2939 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2940 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2941 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2942 /* index: 2942 */
	.weak lookup_taskpid; .quad lookup_taskpid
	.reloc ., R_X86_64_SIZE32, lookup_taskpid; .int 0
	.int 0xcece5a4
	.quad .Lname2943 /* index: 2943 */
	.weak superblock_mountlock_upgrade; .quad superblock_mountlock_upgrade
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_upgrade; .int 0
	.int 0x56ff495
	.quad .Lname2944 /* index: 2944 */
	.weak path_remove; .quad path_remove
	.reloc ., R_X86_64_SIZE32, path_remove; .int 0
	.int 0x6fecc25
	.quad .Lname2945 /* index: 2945 */
	.weak kernel_debugtrap_r_lcpustate; .quad kernel_debugtrap_r_lcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_lcpustate; .int 0
	.int 0xed514a5
	.quad .Lname2946 /* index: 2946 */
	.weak sys32_set_exception_handler; .quad sys32_set_exception_handler
	.reloc ., R_X86_64_SIZE32, sys32_set_exception_handler; .int 0
	.int 0x9f82b82
	.quad .Lname2947 /* index: 2947 */
	.weak sys_dup3; .quad sys_dup3
	.reloc ., R_X86_64_SIZE32, sys_dup3; .int 0
	.int 0x95bb83
	.quad 0 /* index: 2948 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2949 /* index: 2949 */
	.weak quantum_time; .quad quantum_time
	.reloc ., R_X86_64_SIZE32, quantum_time; .int 0
	.int 0xdbd2b85
	.quad .Lname2950 /* index: 2950 */
	.weak addr2line_printf; .quad addr2line_printf
	.reloc ., R_X86_64_SIZE32, addr2line_printf; .int 0
	.int 0x3ec7b86
	.quad .Lname2951 /* index: 2951 */
	.weak mempsetw; .quad mempsetw
	.reloc ., R_X86_64_SIZE32, mempsetw; .int 0
	.int 0xc479b87
	.quad .Lname2952 /* index: 2952 */
	.weak linebuffer_writesome; .quad linebuffer_writesome
	.reloc ., R_X86_64_SIZE32, linebuffer_writesome; .int 0
	.int 0xc2178b5
	.quad .Lname2953 /* index: 2953 */
	.weak driver_destroy; .quad driver_destroy
	.reloc ., R_X86_64_SIZE32, driver_destroy; .int 0
	.int 0x3c67b89
	.quad .Lname2954 /* index: 2954 */
	.weak sys_connect; .quad sys_connect
	.reloc ., R_X86_64_SIZE32, sys_connect; .int 0
	.int 0xa4042f4
	.quad .Lname2955 /* index: 2955 */
	.weak sys_getdrives; .quad sys_getdrives
	.reloc ., R_X86_64_SIZE32, sys_getdrives; .int 0
	.int 0x1b25173
	.quad .Lname2956 /* index: 2956 */
	.weak memmovel; .quad memmovel
	.reloc ., R_X86_64_SIZE32, memmovel; .int 0
	.int 0xc446b8c
	.quad .Lname2957 /* index: 2957 */
	.weak sys_lremovexattr; .quad sys_lremovexattr
	.reloc ., R_X86_64_SIZE32, sys_lremovexattr; .int 0
	.int 0xaf19f42
	.quad 0 /* index: 2958 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2959 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2960 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2961 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2962 /* index: 2962 */
	.weak kernel_syscall0_regcnt; .quad kernel_syscall0_regcnt
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_regcnt; .int 0
	.int 0xbda8284
	.quad .Lname2963 /* index: 2963 */
	.weak vm_datapart_sync; .quad vm_datapart_sync
	.reloc ., R_X86_64_SIZE32, vm_datapart_sync; .int 0
	.int 0x32bfb93
	.quad .Lname2964 /* index: 2964 */
	.weak kernel_debugtrap_enabled; .quad kernel_debugtrap_enabled
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_enabled; .int 0
	.int 0x3b93b94
	.quad .Lname2965 /* index: 2965 */
	.weak sys_futex; .quad sys_futex
	.reloc ., R_X86_64_SIZE32, sys_futex; .int 0
	.int 0x95db1c8
	.quad .Lname2966 /* index: 2966 */
	.weak sys32_setresgid32; .quad sys32_setresgid32
	.reloc ., R_X86_64_SIZE32, sys32_setresgid32; .int 0
	.int 0x48f3a82
	.quad .Lname2967 /* index: 2967 */
	.weak dbg_hasuni; .quad dbg_hasuni
	.reloc ., R_X86_64_SIZE32, dbg_hasuni; .int 0
	.int 0x5ee0499
	.quad .Lname2968 /* index: 2968 */
	.weak thiscpu_x86_tss; .quad thiscpu_x86_tss
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_tss; .int 0
	.int 0xb226a33
	.quad .Lname2969 /* index: 2969 */
	.weak pipe_writer_destroy; .quad pipe_writer_destroy
	.reloc ., R_X86_64_SIZE32, pipe_writer_destroy; .int 0
	.int 0xac6cb99
	.quad .Lname2970 /* index: 2970 */
	.weak x86_fxsave; .quad x86_fxsave
	.reloc ., R_X86_64_SIZE32, x86_fxsave; .int 0
	.int 0x5d82305
	.quad 0 /* index: 2971 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2972 /* index: 2972 */
	.weak handle_install; .quad handle_install
	.reloc ., R_X86_64_SIZE32, handle_install; .int 0
	.int 0x8118b9c
	.quad .Lname2973 /* index: 2973 */
	.weak debuginfo_cu_parser_loadattr_subprogram; .quad debuginfo_cu_parser_loadattr_subprogram
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_subprogram; .int 0
	.int 0x9fa0b9d
	.quad 0 /* index: 2974 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2975 /* index: 2975 */
	.weak json_parser_leave; .quad json_parser_leave
	.reloc ., R_X86_64_SIZE32, json_parser_leave; .int 0
	.int 0x25b8745
	.quad 0 /* index: 2976 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2977 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2978 /* index: 2978 */
	.weak sys32_setfsgid32; .quad sys32_setfsgid32
	.reloc ., R_X86_64_SIZE32, sys32_setfsgid32; .int 0
	.int 0xb1cdba2
	.quad 0 /* index: 2979 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2980 /* index: 2980 */
	.weak pidns_trylookup_locked; .quad pidns_trylookup_locked
	.reloc ., R_X86_64_SIZE32, pidns_trylookup_locked; .int 0
	.int 0xf007ba4
	.quad .Lname2981 /* index: 2981 */
	.weak sys_write; .quad sys_write
	.reloc ., R_X86_64_SIZE32, sys_write; .int 0
	.int 0x96f0ba5
	.quad .Lname2982 /* index: 2982 */
	.weak validate_readablem_opt; .quad validate_readablem_opt
	.reloc ., R_X86_64_SIZE32, validate_readablem_opt; .int 0
	.int 0x5bba2a4
	.quad 0 /* index: 2983 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2984 /* index: 2984 */
	.weak unicode_writeutf8; .quad unicode_writeutf8
	.reloc ., R_X86_64_SIZE32, unicode_writeutf8; .int 0
	.int 0x57beba8
	.quad .Lname2985 /* index: 2985 */
	.weak setreg_scpustate; .quad setreg_scpustate
	.reloc ., R_X86_64_SIZE32, setreg_scpustate; .int 0
	.int 0xf765db5
	.quad .Lname2986 /* index: 2986 */
	.weak terminal_flush_icanon; .quad terminal_flush_icanon
	.reloc ., R_X86_64_SIZE32, terminal_flush_icanon; .int 0
	.int 0x96a941e
	.quad 0 /* index: 2987 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 2988 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2989 /* index: 2989 */
	.weak strchr; .quad strchr
	.reloc ., R_X86_64_SIZE32, strchr; .int 0
	.int 0x7ab89f2
	.quad 0 /* index: 2990 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2991 /* index: 2991 */
	.weak validate_executable_opt; .quad validate_executable_opt
	.reloc ., R_X86_64_SIZE32, validate_executable_opt; .int 0
	.int 0xd67bb34
	.quad .Lname2992 /* index: 2992 */
	.weak sys_dup; .quad sys_dup
	.reloc ., R_X86_64_SIZE32, sys_dup; .int 0
	.int 0xb095bb0
	.quad 0 /* index: 2993 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname2994 /* index: 2994 */
	.weak block_device_awrite_sector; .quad block_device_awrite_sector
	.reloc ., R_X86_64_SIZE32, block_device_awrite_sector; .int 0
	.int 0x1e52bb2
	.quad .Lname2995 /* index: 2995 */
	.weak dbg_setallregs; .quad dbg_setallregs
	.reloc ., R_X86_64_SIZE32, dbg_setallregs; .int 0
	.int 0x10511f3
	.quad .Lname2996 /* index: 2996 */
	.weak sys32_set_robust_list; .quad sys32_set_robust_list
	.reloc ., R_X86_64_SIZE32, sys32_set_robust_list; .int 0
	.int 0xaa57bb4
	.quad .Lname2997 /* index: 2997 */
	.weak getreg_icpustate; .quad getreg_icpustate
	.reloc ., R_X86_64_SIZE32, getreg_icpustate; .int 0
	.int 0xf712bb5
	.quad .Lname2998 /* index: 2998 */
	.weak sys32_pselect6; .quad sys32_pselect6
	.reloc ., R_X86_64_SIZE32, sys32_pselect6; .int 0
	.int 0x9e43bb6
	.quad 0 /* index: 2999 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3000 /* index: 3000 */
	.weak heap_align_untraced_nx; .quad heap_align_untraced_nx
	.reloc ., R_X86_64_SIZE32, heap_align_untraced_nx; .int 0
	.int 0x1a11bb8
	.quad .Lname3001 /* index: 3001 */
	.weak isr_unregister_any_at; .quad isr_unregister_any_at
	.reloc ., R_X86_64_SIZE32, isr_unregister_any_at; .int 0
	.int 0x32371f4
	.quad .Lname3002 /* index: 3002 */
	.weak thiscpu_x86_lapicid; .quad thiscpu_x86_lapicid
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_lapicid; .int 0
	.int 0x31ddb94
	.quad .Lname3003 /* index: 3003 */
	.weak vm_readphysl_unaligned; .quad vm_readphysl_unaligned
	.reloc ., R_X86_64_SIZE32, vm_readphysl_unaligned; .int 0
	.int 0x1deb44
	.quad .Lname3004 /* index: 3004 */
	.weak sigmask_check_after_syscall; .quad sigmask_check_after_syscall
	.reloc ., R_X86_64_SIZE32, sigmask_check_after_syscall; .int 0
	.int 0xb002bbc
	.quad 0 /* index: 3005 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3006 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3007 /* index: 3007 */
	.weak mempmove; .quad mempmove
	.reloc ., R_X86_64_SIZE32, mempmove; .int 0
	.int 0xc4741f5
	.quad 0 /* index: 3008 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3009 /* index: 3009 */
	.weak vm_kernel_treelock_tryservice; .quad vm_kernel_treelock_tryservice
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_tryservice; .int 0
	.int 0x95d4ca5
	.quad .Lname3010 /* index: 3010 */
	.weak dbg_default_attr; .quad dbg_default_attr
	.reloc ., R_X86_64_SIZE32, dbg_default_attr; .int 0
	.int 0x648ebc2
	.quad .Lname3011 /* index: 3011 */
	.weak sigmask_check_s; .quad sigmask_check_s
	.reloc ., R_X86_64_SIZE32, sigmask_check_s; .int 0
	.int 0x7d37bc3
	.quad .Lname3012 /* index: 3012 */
	.weak sys_linux_stat64; .quad sys_linux_stat64
	.reloc ., R_X86_64_SIZE32, sys_linux_stat64; .int 0
	.int 0x836bc4
	.quad 0 /* index: 3013 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3014 /* index: 3014 */
	.weak sys_mlockall; .quad sys_mlockall
	.reloc ., R_X86_64_SIZE32, sys_mlockall; .int 0
	.int 0x6ea826c
	.quad .Lname3015 /* index: 3015 */
	.weak rwlock_write_aggressive; .quad rwlock_write_aggressive
	.reloc ., R_X86_64_SIZE32, rwlock_write_aggressive; .int 0
	.int 0x8f0f175
	.quad 0 /* index: 3016 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3017 /* index: 3017 */
	.weak pipe_reader_destroy; .quad pipe_reader_destroy
	.reloc ., R_X86_64_SIZE32, pipe_reader_destroy; .int 0
	.int 0x6b6cbc9
	.quad 0 /* index: 3018 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3019 /* index: 3019 */
	.weak x86_fpustate_save_noreset; .quad x86_fpustate_save_noreset
	.reloc ., R_X86_64_SIZE32, x86_fpustate_save_noreset; .int 0
	.int 0x6e6d734
	.quad .Lname3020 /* index: 3020 */
	.weak x86_sysroute1_c32; .quad x86_sysroute1_c32
	.reloc ., R_X86_64_SIZE32, x86_sysroute1_c32; .int 0
	.int 0x1f81cc2
	.quad 0 /* index: 3021 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3022 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3023 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3024 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3025 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3026 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3027 /* index: 3027 */
	.weak regdump_flags; .quad regdump_flags
	.reloc ., R_X86_64_SIZE32, regdump_flags; .int 0
	.int 0xee29bd3
	.quad .Lname3028 /* index: 3028 */
	.weak __stack_chk_guard; .quad __stack_chk_guard
	.reloc ., R_X86_64_SIZE32, __stack_chk_guard; .int 0
	.int 0x9588bd4
	.quad .Lname3029 /* index: 3029 */
	.weak dbg_setcur_visible; .quad dbg_setcur_visible
	.reloc ., R_X86_64_SIZE32, dbg_setcur_visible; .int 0
	.int 0x70bebd5
	.quad 0 /* index: 3030 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3031 /* index: 3031 */
	.weak task_alloc; .quad task_alloc
	.reloc ., R_X86_64_SIZE32, task_alloc; .int 0
	.int 0x1519bf3
	.quad .Lname3032 /* index: 3032 */
	.weak vm_tasklock_tryupgrade; .quad vm_tasklock_tryupgrade
	.reloc ., R_X86_64_SIZE32, vm_tasklock_tryupgrade; .int 0
	.int 0x8f7eb95
	.quad .Lname3033 /* index: 3033 */
	.weak dev_tty; .quad dev_tty
	.reloc ., R_X86_64_SIZE32, dev_tty; .int 0
	.int 0xacc6bd9
	.quad .Lname3034 /* index: 3034 */
	.weak vm_sync_locked; .quad vm_sync_locked
	.reloc ., R_X86_64_SIZE32, vm_sync_locked; .int 0
	.int 0x75ea2d4
	.quad .Lname3035 /* index: 3035 */
	.weak superblock_mountlock_upgrade_nx; .quad superblock_mountlock_upgrade_nx
	.reloc ., R_X86_64_SIZE32, superblock_mountlock_upgrade_nx; .int 0
	.int 0xf4a04a8
	.quad .Lname3036 /* index: 3036 */
	.weak memlen; .quad memlen
	.reloc ., R_X86_64_SIZE32, memlen; .int 0
	.int 0x73c42be
	.quad 0 /* index: 3037 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3038 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3039 /* index: 3039 */
	.weak inode_readall_phys; .quad inode_readall_phys
	.reloc ., R_X86_64_SIZE32, inode_readall_phys; .int 0
	.int 0x4a850d3
	.quad .Lname3040 /* index: 3040 */
	.weak pagedir_ismapped_p; .quad pagedir_ismapped_p
	.reloc ., R_X86_64_SIZE32, pagedir_ismapped_p; .int 0
	.int 0xf556be0
	.quad 0 /* index: 3041 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3042 /* index: 3042 */
	.weak mouse_device_button_nopr; .quad mouse_device_button_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_button_nopr; .int 0
	.int 0xd979be2
	.quad .Lname3043 /* index: 3043 */
	.weak sys_link; .quad sys_link
	.reloc ., R_X86_64_SIZE32, sys_link; .int 0
	.int 0x9629fb
	.quad 0 /* index: 3044 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3045 /* index: 3045 */
	.weak sys_readf; .quad sys_readf
	.reloc ., R_X86_64_SIZE32, sys_readf; .int 0
	.int 0x968cca6
	.quad .Lname3046 /* index: 3046 */
	.weak inode_areadallv; .quad inode_areadallv
	.reloc ., R_X86_64_SIZE32, inode_areadallv; .int 0
	.int 0xed16be6
	.quad .Lname3047 /* index: 3047 */
	.weak x86_userexcept_raisesignal; .quad x86_userexcept_raisesignal
	.reloc ., R_X86_64_SIZE32, x86_userexcept_raisesignal; .int 0
	.int 0x7fff6ec
	.quad 0 /* index: 3048 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3049 /* index: 3049 */
	.weak ramfs_symlink_type; .quad ramfs_symlink_type
	.reloc ., R_X86_64_SIZE32, ramfs_symlink_type; .int 0
	.int 0x63ebf15
	.quad 0 /* index: 3050 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3051 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3052 /* index: 3052 */
	.weak character_device_poll; .quad character_device_poll
	.reloc ., R_X86_64_SIZE32, character_device_poll; .int 0
	.int 0x98b7bec
	.quad .Lname3053 /* index: 3053 */
	.weak vio_cmpxch_or_writeb; .quad vio_cmpxch_or_writeb
	.reloc ., R_X86_64_SIZE32, vio_cmpxch_or_writeb; .int 0
	.int 0x8230f52
	.quad 0 /* index: 3054 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3055 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3056 /* index: 3056 */
	.weak vm_memsetphyspage; .quad vm_memsetphyspage
	.reloc ., R_X86_64_SIZE32, vm_memsetphyspage; .int 0
	.int 0x43e9a85
	.quad .Lname3057 /* index: 3057 */
	.weak memmoveq; .quad memmoveq
	.reloc ., R_X86_64_SIZE32, memmoveq; .int 0
	.int 0xc446bf1
	.quad 0 /* index: 3058 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3059 /* index: 3059 */
	.weak aio_pbuffer_copyfromphys; .quad aio_pbuffer_copyfromphys
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copyfromphys; .int 0
	.int 0x3fe8bf3
	.quad .Lname3060 /* index: 3060 */
	.weak sys32_setuid32; .quad sys32_setuid32
	.reloc ., R_X86_64_SIZE32, sys32_setuid32; .int 0
	.int 0xcdd7642
	.quad .Lname3061 /* index: 3061 */
	.weak kernel_panic_scpustate; .quad kernel_panic_scpustate
	.reloc ., R_X86_64_SIZE32, kernel_panic_scpustate; .int 0
	.int 0x78abbf5
	.quad 0 /* index: 3062 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3063 /* index: 3063 */
	.weak memmovew; .quad memmovew
	.reloc ., R_X86_64_SIZE32, memmovew; .int 0
	.int 0xc446bf7
	.quad .Lname3064 /* index: 3064 */
	.weak devfs_lock_write_nx; .quad devfs_lock_write_nx
	.reloc ., R_X86_64_SIZE32, devfs_lock_write_nx; .int 0
	.int 0x29c5bf8
	.quad .Lname3065 /* index: 3065 */
	.weak path_movemount; .quad path_movemount
	.reloc ., R_X86_64_SIZE32, path_movemount; .int 0
	.int 0x42e0f54
	.quad .Lname3066 /* index: 3066 */
	.weak unwind_setreg_fcpustate_exclusive; .quad unwind_setreg_fcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_fcpustate_exclusive; .int 0
	.int 0x8e5125
	.quad .Lname3067 /* index: 3067 */
	.weak inode_areadallk; .quad inode_areadallk
	.reloc ., R_X86_64_SIZE32, inode_areadallk; .int 0
	.int 0xed16bfb
	.quad 0 /* index: 3068 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3069 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3070 /* index: 3070 */
	.weak vm_datapart_read_buffered; .quad vm_datapart_read_buffered
	.reloc ., R_X86_64_SIZE32, vm_datapart_read_buffered; .int 0
	.int 0x6267f94
	.quad .Lname3071 /* index: 3071 */
	.weak path_traverse; .quad path_traverse
	.reloc ., R_X86_64_SIZE32, path_traverse; .int 0
	.int 0xe062f55
	.quad .Lname3072 /* index: 3072 */
	.weak task_sigstop; .quad task_sigstop
	.reloc ., R_X86_64_SIZE32, task_sigstop; .int 0
	.int 0xe560c00
	.quad 0 /* index: 3073 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3074 /* index: 3074 */
	.weak unwind_getreg_fcpustate_exclusive; .quad unwind_getreg_fcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_fcpustate_exclusive; .int 0
	.int 0x8e5065
	.quad .Lname3075 /* index: 3075 */
	.weak block_device_partition_readv_phys; .quad block_device_partition_readv_phys
	.reloc ., R_X86_64_SIZE32, block_device_partition_readv_phys; .int 0
	.int 0xdc34c03
	.quad .Lname3076 /* index: 3076 */
	.weak sys32_kfstat; .quad sys32_kfstat
	.reloc ., R_X86_64_SIZE32, sys32_kfstat; .int 0
	.int 0x3adcc04
	.quad .Lname3077 /* index: 3077 */
	.weak sys_rpc_schedule; .quad sys_rpc_schedule
	.reloc ., R_X86_64_SIZE32, sys_rpc_schedule; .int 0
	.int 0xf7afe25
	.quad .Lname3078 /* index: 3078 */
	.weak sys_pselect6; .quad sys_pselect6
	.reloc ., R_X86_64_SIZE32, sys_pselect6; .int 0
	.int 0xe122c06
	.quad 0 /* index: 3079 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3080 /* index: 3080 */
	.weak driver_library_path; .quad driver_library_path
	.reloc ., R_X86_64_SIZE32, driver_library_path; .int 0
	.int 0x6693c08
	.quad .Lname3081 /* index: 3081 */
	.weak vmb_apply; .quad vmb_apply
	.reloc ., R_X86_64_SIZE32, vmb_apply; .int 0
	.int 0x8580c09
	.quad .Lname3082 /* index: 3082 */
	.weak vm_kernel_treelock_write_nx; .quad vm_kernel_treelock_write_nx
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_write_nx; .int 0
	.int 0x43a4288
	.quad .Lname3083 /* index: 3083 */
	.weak unwind_getreg_kcpustate_exclusive; .quad unwind_getreg_kcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_kcpustate_exclusive; .int 0
	.int 0x38e5065
	.quad .Lname3084 /* index: 3084 */
	.weak sys_getsockopt; .quad sys_getsockopt
	.reloc ., R_X86_64_SIZE32, sys_getsockopt; .int 0
	.int 0xacddd74
	.quad .Lname3085 /* index: 3085 */
	.weak sys32_socketpair; .quad sys32_socketpair
	.reloc ., R_X86_64_SIZE32, sys32_socketpair; .int 0
	.int 0x74a5202
	.quad .Lname3086 /* index: 3086 */
	.weak dbg_beginshowscreen; .quad dbg_beginshowscreen
	.reloc ., R_X86_64_SIZE32, dbg_beginshowscreen; .int 0
	.int 0x9124c0e
	.quad .Lname3087 /* index: 3087 */
	.weak error_as_errno; .quad error_as_errno
	.reloc ., R_X86_64_SIZE32, error_as_errno; .int 0
	.int 0x2ca1c0f
	.quad 0 /* index: 3088 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3089 /* index: 3089 */
	.weak vm_sync_end; .quad vm_sync_end
	.reloc ., R_X86_64_SIZE32, vm_sync_end; .int 0
	.int 0x366ef4
	.quad .Lname3090 /* index: 3090 */
	.weak sys_umount2; .quad sys_umount2
	.reloc ., R_X86_64_SIZE32, sys_umount2; .int 0
	.int 0xc5dcc12
	.quad .Lname3091 /* index: 3091 */
	.weak ansitty_putc; .quad ansitty_putc
	.reloc ., R_X86_64_SIZE32, ansitty_putc; .int 0
	.int 0xd73dc13
	.quad .Lname3092 /* index: 3092 */
	.weak unwind_setreg_fcpustate; .quad unwind_setreg_fcpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_fcpustate; .int 0
	.int 0xb8d36b5
	.quad .Lname3093 /* index: 3093 */
	.weak cpu_apply_fcpustate; .quad cpu_apply_fcpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_fcpustate; .int 0
	.int 0xa8cac15
	.quad 0 /* index: 3094 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3095 /* index: 3095 */
	.weak json_parser_eqstring; .quad json_parser_eqstring
	.reloc ., R_X86_64_SIZE32, json_parser_eqstring; .int 0
	.int 0xb53ac17
	.quad .Lname3096 /* index: 3096 */
	.weak path_sprintex; .quad path_sprintex
	.reloc ., R_X86_64_SIZE32, path_sprintex; .int 0
	.int 0x106bc18
	.quad .Lname3097 /* index: 3097 */
	.weak sys32_openat; .quad sys32_openat
	.reloc ., R_X86_64_SIZE32, sys32_openat; .int 0
	.int 0x3d6e204
	.quad 0 /* index: 3098 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3099 /* index: 3099 */
	.weak dbg_setreg; .quad dbg_setreg
	.reloc ., R_X86_64_SIZE32, dbg_setreg; .int 0
	.int 0x69a1067
	.quad .Lname3100 /* index: 3100 */
	.weak sys32_munlockall; .quad sys32_munlockall
	.reloc ., R_X86_64_SIZE32, sys32_munlockall; .int 0
	.int 0x5dbec1c
	.quad .Lname3101 /* index: 3101 */
	.weak sys_ioperm; .quad sys_ioperm
	.reloc ., R_X86_64_SIZE32, sys_ioperm; .int 0
	.int 0x601dc1d
	.quad 0 /* index: 3102 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3103 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3104 /* index: 3104 */
	.weak vm_copytophys; .quad vm_copytophys
	.reloc ., R_X86_64_SIZE32, vm_copytophys; .int 0
	.int 0xda3ca13
	.quad .Lname3105 /* index: 3105 */
	.weak heap_alloc_nx; .quad heap_alloc_nx
	.reloc ., R_X86_64_SIZE32, heap_alloc_nx; .int 0
	.int 0xdadf178
	.quad .Lname3106 /* index: 3106 */
	.weak sys32_getitimer64; .quad sys32_getitimer64
	.reloc ., R_X86_64_SIZE32, sys32_getitimer64; .int 0
	.int 0x2e508f4
	.quad .Lname3107 /* index: 3107 */
	.weak unicode_32to16; .quad unicode_32to16
	.reloc ., R_X86_64_SIZE32, unicode_32to16; .int 0
	.int 0x6940f36
	.quad .Lname3108 /* index: 3108 */
	.weak thiscpu_x86_gdt; .quad thiscpu_x86_gdt
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_gdt; .int 0
	.int 0xb225c24
	.quad .Lname3109 /* index: 3109 */
	.weak _bootcpu; .quad _bootcpu
	.reloc ., R_X86_64_SIZE32, _bootcpu; .int 0
	.int 0x966ac25
	.quad 0 /* index: 3110 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3111 /* index: 3111 */
	.weak memlenw; .quad memlenw
	.reloc ., R_X86_64_SIZE32, memlenw; .int 0
	.int 0x3c42c27
	.quad 0 /* index: 3112 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3113 /* index: 3113 */
	.weak vm_datablock_vio_write_phys; .quad vm_datablock_vio_write_phys
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_write_phys; .int 0
	.int 0x2726b03
	.quad 0 /* index: 3114 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3115 /* index: 3115 */
	.weak sys_sendmmsg; .quad sys_sendmmsg
	.reloc ., R_X86_64_SIZE32, sys_sendmmsg; .int 0
	.int 0xdfbb207
	.quad .Lname3116 /* index: 3116 */
	.weak sys32_keyctl; .quad sys32_keyctl
	.reloc ., R_X86_64_SIZE32, sys32_keyctl; .int 0
	.int 0x3ac9c2c
	.quad .Lname3117 /* index: 3117 */
	.weak kernel_syscall0_regcnt32; .quad kernel_syscall0_regcnt32
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_regcnt32; .int 0
	.int 0xa828cb2
	.quad .Lname3118 /* index: 3118 */
	.weak validate_writable_opt; .quad validate_writable_opt
	.reloc ., R_X86_64_SIZE32, validate_writable_opt; .int 0
	.int 0xd3aba34
	.quad 0 /* index: 3119 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3120 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3121 /* index: 3121 */
	.weak task_redirect_usercode_rpc; .quad task_redirect_usercode_rpc
	.reloc ., R_X86_64_SIZE32, task_redirect_usercode_rpc; .int 0
	.int 0xcb7473
	.quad .Lname3122 /* index: 3122 */
	.weak json_parser_getnumber; .quad json_parser_getnumber
	.reloc ., R_X86_64_SIZE32, json_parser_getnumber; .int 0
	.int 0x6da7c32
	.quad .Lname3123 /* index: 3123 */
	.weak pagedir_kernel_phys; .quad pagedir_kernel_phys
	.reloc ., R_X86_64_SIZE32, pagedir_kernel_phys; .int 0
	.int 0xa3a1c33
	.quad .Lname3124 /* index: 3124 */
	.weak memrend; .quad memrend
	.reloc ., R_X86_64_SIZE32, memrend; .int 0
	.int 0x3c48c34
	.quad .Lname3125 /* index: 3125 */
	.weak character_device_write; .quad character_device_write
	.reloc ., R_X86_64_SIZE32, character_device_write; .int 0
	.int 0x8be8c35
	.quad .Lname3126 /* index: 3126 */
	.weak sys32_writef; .quad sys32_writef
	.reloc ., R_X86_64_SIZE32, sys32_writef; .int 0
	.int 0x1596c36
	.quad .Lname3127 /* index: 3127 */
	.weak vm_datapart_lockread_setcore_unsharecow; .quad vm_datapart_lockread_setcore_unsharecow
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockread_setcore_unsharecow; .int 0
	.int 0x5b8fc37
	.quad .Lname3128 /* index: 3128 */
	.weak unwind_getreg_lcpustate_exclusive; .quad unwind_getreg_lcpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_lcpustate_exclusive; .int 0
	.int 0x28e5065
	.quad .Lname3129 /* index: 3129 */
	.weak sys32_sendfile64; .quad sys32_sendfile64
	.reloc ., R_X86_64_SIZE32, sys32_sendfile64; .int 0
	.int 0xc4f04b4
	.quad .Lname3130 /* index: 3130 */
	.weak sys32_fchown32; .quad sys32_fchown32
	.reloc ., R_X86_64_SIZE32, sys32_fchown32; .int 0
	.int 0x9906312
	.quad .Lname3131 /* index: 3131 */
	.weak x86_userexcept_seterrno; .quad x86_userexcept_seterrno
	.reloc ., R_X86_64_SIZE32, x86_userexcept_seterrno; .int 0
	.int 0x98c2f5f
	.quad .Lname3132 /* index: 3132 */
	.weak memlenl; .quad memlenl
	.reloc ., R_X86_64_SIZE32, memlenl; .int 0
	.int 0x3c42c3c
	.quad .Lname3133 /* index: 3133 */
	.weak sys_setsockopt; .quad sys_setsockopt
	.reloc ., R_X86_64_SIZE32, sys_setsockopt; .int 0
	.int 0xad09d74
	.quad .Lname3134 /* index: 3134 */
	.weak sys32_listen; .quad sys32_listen
	.reloc ., R_X86_64_SIZE32, sys32_listen; .int 0
	.int 0x3a0cc3e
	.quad .Lname3135 /* index: 3135 */
	.weak sys_fallocate; .quad sys_fallocate
	.reloc ., R_X86_64_SIZE32, sys_fallocate; .int 0
	.int 0xa3cc4b5
	.quad .Lname3136 /* index: 3136 */
	.weak character_device_mmap; .quad character_device_mmap
	.reloc ., R_X86_64_SIZE32, character_device_mmap; .int 0
	.int 0x9894c40
	.quad .Lname3137 /* index: 3137 */
	.weak setreg_gpregsnsp; .quad setreg_gpregsnsp
	.reloc ., R_X86_64_SIZE32, setreg_gpregsnsp; .int 0
	.int 0x26760
	.quad .Lname3138 /* index: 3138 */
	.weak isr_register; .quad isr_register
	.reloc ., R_X86_64_SIZE32, isr_register; .int 0
	.int 0xcea2c42
	.quad 0 /* index: 3139 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3140 /* index: 3140 */
	.weak memend; .quad memend
	.reloc ., R_X86_64_SIZE32, memend; .int 0
	.int 0x73c3c44
	.quad .Lname3141 /* index: 3141 */
	.weak kernel_vpanic_ucpustate; .quad kernel_vpanic_ucpustate
	.reloc ., R_X86_64_SIZE32, kernel_vpanic_ucpustate; .int 0
	.int 0xf5adc45
	.quad .Lname3142 /* index: 3142 */
	.weak sys32_writev; .quad sys32_writev
	.reloc ., R_X86_64_SIZE32, sys32_writev; .int 0
	.int 0x1596c46
	.quad .Lname3143 /* index: 3143 */
	.weak terminal_init; .quad terminal_init
	.reloc ., R_X86_64_SIZE32, terminal_init; .int 0
	.int 0xeecc534
	.quad .Lname3144 /* index: 3144 */
	.weak sys32_lfutex; .quad sys32_lfutex
	.reloc ., R_X86_64_SIZE32, sys32_lfutex; .int 0
	.int 0x39dac48
	.quad .Lname3145 /* index: 3145 */
	.weak disasm_print_until; .quad disasm_print_until
	.reloc ., R_X86_64_SIZE32, disasm_print_until; .int 0
	.int 0xdbd420c
	.quad 0 /* index: 3146 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3147 /* index: 3147 */
	.weak sys32_getpmsg; .quad sys32_getpmsg
	.reloc ., R_X86_64_SIZE32, sys32_getpmsg; .int 0
	.int 0x6cd1cb7
	.quad .Lname3148 /* index: 3148 */
	.weak sys_umask; .quad sys_umask
	.reloc ., R_X86_64_SIZE32, sys_umask; .int 0
	.int 0x96c439b
	.quad .Lname3149 /* index: 3149 */
	.weak sys32_mlock2; .quad sys32_mlock2
	.reloc ., R_X86_64_SIZE32, sys32_mlock2; .int 0
	.int 0x3933f62
	.quad .Lname3150 /* index: 3150 */
	.weak kernel_vpanic_kcpustate; .quad kernel_vpanic_kcpustate
	.reloc ., R_X86_64_SIZE32, kernel_vpanic_kcpustate; .int 0
	.int 0xf5af645
	.quad 0 /* index: 3151 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3152 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3153 /* index: 3153 */
	.weak sys32_bdflush; .quad sys32_bdflush
	.reloc ., R_X86_64_SIZE32, sys32_bdflush; .int 0
	.int 0x3ab54b8
	.quad .Lname3154 /* index: 3154 */
	.weak sys32_dup2; .quad sys32_dup2
	.reloc ., R_X86_64_SIZE32, sys32_dup2; .int 0
	.int 0x6820c52
	.quad .Lname3155 /* index: 3155 */
	.weak sys32_dup3; .quad sys32_dup3
	.reloc ., R_X86_64_SIZE32, sys32_dup3; .int 0
	.int 0x6820c53
	.quad .Lname3156 /* index: 3156 */
	.weak cred_require_mmap_uninitialized; .quad cred_require_mmap_uninitialized
	.reloc ., R_X86_64_SIZE32, cred_require_mmap_uninitialized; .int 0
	.int 0xf8d8c54
	.quad .Lname3157 /* index: 3157 */
	.weak x86_lapicbase; .quad x86_lapicbase
	.reloc ., R_X86_64_SIZE32, x86_lapicbase; .int 0
	.int 0xd45ea65
	.quad .Lname3158 /* index: 3158 */
	.weak x86_dbggdt; .quad x86_dbggdt
	.reloc ., R_X86_64_SIZE32, x86_dbggdt; .int 0
	.int 0x5af6674
	.quad .Lname3159 /* index: 3159 */
	.weak inode_readk_blocking; .quad inode_readk_blocking
	.reloc ., R_X86_64_SIZE32, inode_readk_blocking; .int 0
	.int 0xd79dc57
	.quad .Lname3160 /* index: 3160 */
	.weak sys32_accept4; .quad sys32_accept4
	.reloc ., R_X86_64_SIZE32, sys32_accept4; .int 0
	.int 0xc9faf54
	.quad .Lname3161 /* index: 3161 */
	.weak sys32_exit; .quad sys32_exit
	.reloc ., R_X86_64_SIZE32, sys32_exit; .int 0
	.int 0x6827f64
	.quad .Lname3162 /* index: 3162 */
	.weak sys_ioprio_get; .quad sys_ioprio_get
	.reloc ., R_X86_64_SIZE32, sys_ioprio_get; .int 0
	.int 0x8735c04
	.quad 0 /* index: 3163 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3164 /* index: 3164 */
	.weak keyboard_device_ioctl; .quad keyboard_device_ioctl
	.reloc ., R_X86_64_SIZE32, keyboard_device_ioctl; .int 0
	.int 0x1676c5c
	.quad 0 /* index: 3165 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3166 /* index: 3166 */
	.weak vio_subb; .quad vio_subb
	.reloc ., R_X86_64_SIZE32, vio_subb; .int 0
	.int 0x56ac52
	.quad .Lname3167 /* index: 3167 */
	.weak block_device_register_auto; .quad block_device_register_auto
	.reloc ., R_X86_64_SIZE32, block_device_register_auto; .int 0
	.int 0xb6c0c5f
	.quad .Lname3168 /* index: 3168 */
	.weak task_schedule_synchronous_rpc_nx; .quad task_schedule_synchronous_rpc_nx
	.reloc ., R_X86_64_SIZE32, task_schedule_synchronous_rpc_nx; .int 0
	.int 0xf655db8
	.quad 0 /* index: 3169 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3170 /* index: 3170 */
	.weak dbg_verifypagedir; .quad dbg_verifypagedir
	.reloc ., R_X86_64_SIZE32, dbg_verifypagedir; .int 0
	.int 0xadfcc62
	.quad .Lname3171 /* index: 3171 */
	.weak vm_copyinphys_onepage; .quad vm_copyinphys_onepage
	.reloc ., R_X86_64_SIZE32, vm_copyinphys_onepage; .int 0
	.int 0x6866c45
	.quad .Lname3172 /* index: 3172 */
	.weak task_connect_ghost; .quad task_connect_ghost
	.reloc ., R_X86_64_SIZE32, task_connect_ghost; .int 0
	.int 0xa501c64
	.quad .Lname3173 /* index: 3173 */
	.weak driver_get_state; .quad driver_get_state
	.reloc ., R_X86_64_SIZE32, driver_get_state; .int 0
	.int 0x6a84c65
	.quad .Lname3174 /* index: 3174 */
	.weak sys_set_library_listdef; .quad sys_set_library_listdef
	.reloc ., R_X86_64_SIZE32, sys_set_library_listdef; .int 0
	.int 0x3315c66
	.quad .Lname3175 /* index: 3175 */
	.weak sys_socket; .quad sys_socket
	.reloc ., R_X86_64_SIZE32, sys_socket; .int 0
	.int 0x6a23154
	.quad 0 /* index: 3176 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3177 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3178 /* index: 3178 */
	.weak pagedir_kernel; .quad pagedir_kernel
	.reloc ., R_X86_64_SIZE32, pagedir_kernel; .int 0
	.int 0x3c7439c
	.quad .Lname3179 /* index: 3179 */
	.weak sys_mq_unlink; .quad sys_mq_unlink
	.reloc ., R_X86_64_SIZE32, sys_mq_unlink; .int 0
	.int 0xdce4c6b
	.quad 0 /* index: 3180 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3181 /* index: 3181 */
	.weak dbg_getcur; .quad dbg_getcur
	.reloc ., R_X86_64_SIZE32, dbg_getcur; .int 0
	.int 0x5da0212
	.quad 0 /* index: 3182 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3183 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3184 /* index: 3184 */
	.weak sys_exit_group; .quad sys_exit_group
	.reloc ., R_X86_64_SIZE32, sys_exit_group; .int 0
	.int 0xacb5c70
	.quad .Lname3185 /* index: 3185 */
	.weak x86_memcpy_nopf_rep_pointer; .quad x86_memcpy_nopf_rep_pointer
	.reloc ., R_X86_64_SIZE32, x86_memcpy_nopf_rep_pointer; .int 0
	.int 0x8a136d2
	.quad .Lname3186 /* index: 3186 */
	.weak unwind_setreg_icpustate; .quad unwind_setreg_icpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_icpustate; .int 0
	.int 0xb8d35b5
	.quad .Lname3187 /* index: 3187 */
	.weak keyboard_device_readkeys; .quad keyboard_device_readkeys
	.reloc ., R_X86_64_SIZE32, keyboard_device_readkeys; .int 0
	.int 0x8160a13
	.quad .Lname3188 /* index: 3188 */
	.weak sys32_gettid; .quad sys32_gettid
	.reloc ., R_X86_64_SIZE32, sys32_gettid; .int 0
	.int 0x26cdc74
	.quad .Lname3189 /* index: 3189 */
	.weak slab_malloc64; .quad slab_malloc64
	.reloc ., R_X86_64_SIZE32, slab_malloc64; .int 0
	.int 0xe16d0d4
	.quad .Lname3190 /* index: 3190 */
	.weak rwlock_upgrade; .quad rwlock_upgrade
	.reloc ., R_X86_64_SIZE32, rwlock_upgrade; .int 0
	.int 0x25b2f55
	.quad 0 /* index: 3191 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3192 /* index: 3192 */
	.weak vm_datapart_lockwrite_setcore_nx; .quad vm_datapart_lockwrite_setcore_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockwrite_setcore_nx; .int 0
	.int 0x3700c78
	.quad .Lname3193 /* index: 3193 */
	.weak heap_allat_untraced; .quad heap_allat_untraced
	.reloc ., R_X86_64_SIZE32, heap_allat_untraced; .int 0
	.int 0x8297a14
	.quad .Lname3194 /* index: 3194 */
	.weak sys32_timer_gettime64; .quad sys32_timer_gettime64
	.reloc ., R_X86_64_SIZE32, sys32_timer_gettime64; .int 0
	.int 0xe207754
	.quad 0 /* index: 3195 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3196 /* index: 3196 */
	.weak unwind_cfa_apply; .quad unwind_cfa_apply
	.reloc ., R_X86_64_SIZE32, unwind_cfa_apply; .int 0
	.int 0x717eb19
	.quad .Lname3197 /* index: 3197 */
	.weak thiscpu_x86_dfstacknode; .quad thiscpu_x86_dfstacknode
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_dfstacknode; .int 0
	.int 0x5db1425
	.quad 0 /* index: 3198 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3199 /* index: 3199 */
	.weak sys32_setdomainname; .quad sys32_setdomainname
	.reloc ., R_X86_64_SIZE32, sys32_setdomainname; .int 0
	.int 0x5499a15
	.quad .Lname3200 /* index: 3200 */
	.weak pagedir_prepare_map_keep; .quad pagedir_prepare_map_keep
	.reloc ., R_X86_64_SIZE32, pagedir_prepare_map_keep; .int 0
	.int 0xa0d0c80
	.quad .Lname3201 /* index: 3201 */
	.weak sys_mq_timedreceive; .quad sys_mq_timedreceive
	.reloc ., R_X86_64_SIZE32, sys_mq_timedreceive; .int 0
	.int 0x51eff55
	.quad .Lname3202 /* index: 3202 */
	.weak block_device_areadv_sector; .quad block_device_areadv_sector
	.reloc ., R_X86_64_SIZE32, block_device_areadv_sector; .int 0
	.int 0x1855c82
	.quad .Lname3203 /* index: 3203 */
	.weak vm_memset_nopf; .quad vm_memset_nopf
	.reloc ., R_X86_64_SIZE32, vm_memset_nopf; .int 0
	.int 0x79536
	.quad 0 /* index: 3204 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3205 /* index: 3205 */
	.weak sys32_readahead; .quad sys32_readahead
	.reloc ., R_X86_64_SIZE32, sys32_readahead; .int 0
	.int 0x1cff8c4
	.quad .Lname3206 /* index: 3206 */
	.weak sys_timerfd_gettime; .quad sys_timerfd_gettime
	.reloc ., R_X86_64_SIZE32, sys_timerfd_gettime; .int 0
	.int 0x50a0cf5
	.quad .Lname3207 /* index: 3207 */
	.weak sys32_putpmsg; .quad sys32_putpmsg
	.reloc ., R_X86_64_SIZE32, sys32_putpmsg; .int 0
	.int 0xccd1c87
	.quad .Lname3208 /* index: 3208 */
	.weak block_device_lookup_nx; .quad block_device_lookup_nx
	.reloc ., R_X86_64_SIZE32, block_device_lookup_nx; .int 0
	.int 0x1a63c88
	.quad .Lname3209 /* index: 3209 */
	.weak sys32_nfsservctl; .quad sys32_nfsservctl
	.reloc ., R_X86_64_SIZE32, sys32_nfsservctl; .int 0
	.int 0xf4a376c
	.quad 0 /* index: 3210 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3211 /* index: 3211 */
	.weak sys32_futex; .quad sys32_futex
	.reloc ., R_X86_64_SIZE32, sys32_futex; .int 0
	.int 0x826cca8
	.quad .Lname3212 /* index: 3212 */
	.weak mouse_device_ioctl; .quad mouse_device_ioctl
	.reloc ., R_X86_64_SIZE32, mouse_device_ioctl; .int 0
	.int 0x9b65c8c
	.quad .Lname3213 /* index: 3213 */
	.weak sys32_sched_getparam; .quad sys32_sched_getparam
	.reloc ., R_X86_64_SIZE32, sys32_sched_getparam; .int 0
	.int 0x53bac8d
	.quad .Lname3214 /* index: 3214 */
	.weak sys_timer_getoverrun; .quad sys_timer_getoverrun
	.reloc ., R_X86_64_SIZE32, sys_timer_getoverrun; .int 0
	.int 0xa3fec8e
	.quad 0 /* index: 3215 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3216 /* index: 3216 */
	.weak sys32_clock_nanosleep; .quad sys32_clock_nanosleep
	.reloc ., R_X86_64_SIZE32, sys32_clock_nanosleep; .int 0
	.int 0x161ac90
	.quad .Lname3217 /* index: 3217 */
	.weak vm_datapart_lock_read_nx; .quad vm_datapart_lock_read_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_read_nx; .int 0
	.int 0x137d218
	.quad .Lname3218 /* index: 3218 */
	.weak mouse_device_moveto_nopr; .quad mouse_device_moveto_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_moveto_nopr; .int 0
	.int 0x4a03c92
	.quad .Lname3219 /* index: 3219 */
	.weak task_free_rpc; .quad task_free_rpc
	.reloc ., R_X86_64_SIZE32, task_free_rpc; .int 0
	.int 0x2317cc3
	.quad .Lname3220 /* index: 3220 */
	.weak pagedir_isuserwritable; .quad pagedir_isuserwritable
	.reloc ., R_X86_64_SIZE32, pagedir_isuserwritable; .int 0
	.int 0xa749315
	.quad .Lname3221 /* index: 3221 */
	.weak dbg_getcur_visible; .quad dbg_getcur_visible
	.reloc ., R_X86_64_SIZE32, dbg_getcur_visible; .int 0
	.int 0x70bec95
	.quad 0 /* index: 3222 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3223 /* index: 3223 */
	.weak sys32_sched_setaffinity; .quad sys32_sched_setaffinity
	.reloc ., R_X86_64_SIZE32, sys32_sched_setaffinity; .int 0
	.int 0xeb52219
	.quad 0 /* index: 3224 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3225 /* index: 3225 */
	.weak sys_fchmod; .quad sys_fchmod
	.reloc ., R_X86_64_SIZE32, sys_fchmod; .int 0
	.int 0x5ce64c4
	.quad 0 /* index: 3226 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3227 /* index: 3227 */
	.weak x86_iopl_keep_after_fork; .quad x86_iopl_keep_after_fork
	.reloc ., R_X86_64_SIZE32, x86_iopl_keep_after_fork; .int 0
	.int 0x1cb2c9b
	.quad 0 /* index: 3228 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3229 /* index: 3229 */
	.weak sys_sysfs; .quad sys_sysfs
	.reloc ., R_X86_64_SIZE32, sys_sysfs; .int 0
	.int 0x96b72d3
	.quad .Lname3230 /* index: 3230 */
	.weak sys_mktty; .quad sys_mktty
	.reloc ., R_X86_64_SIZE32, sys_mktty; .int 0
	.int 0x96450b9
	.quad .Lname3231 /* index: 3231 */
	.weak sys_timerfd_settime; .quad sys_timerfd_settime
	.reloc ., R_X86_64_SIZE32, sys_timerfd_settime; .int 0
	.int 0x10a0cc5
	.quad .Lname3232 /* index: 3232 */
	.weak sys_geteuid; .quad sys_geteuid
	.reloc ., R_X86_64_SIZE32, sys_geteuid; .int 0
	.int 0xdb1c2a4
	.quad .Lname3233 /* index: 3233 */
	.weak vio_cmpxchq; .quad vio_cmpxchq
	.reloc ., R_X86_64_SIZE32, vio_cmpxchq; .int 0
	.int 0xa3aeca1
	.quad 0 /* index: 3234 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3235 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3236 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3237 /* index: 3237 */
	.weak sys32_sethostname; .quad sys32_sethostname
	.reloc ., R_X86_64_SIZE32, sys32_sethostname; .int 0
	.int 0xeb98ca5
	.quad .Lname3238 /* index: 3238 */
	.weak format_printf; .quad format_printf
	.reloc ., R_X86_64_SIZE32, format_printf; .int 0
	.int 0xb11dca6
	.quad .Lname3239 /* index: 3239 */
	.weak vio_cmpxchw; .quad vio_cmpxchw
	.reloc ., R_X86_64_SIZE32, vio_cmpxchw; .int 0
	.int 0xa3aeca7
	.quad .Lname3240 /* index: 3240 */
	.weak devfs_lock_read_nx; .quad devfs_lock_read_nx
	.reloc ., R_X86_64_SIZE32, devfs_lock_read_nx; .int 0
	.int 0xc2f0ca8
	.quad .Lname3241 /* index: 3241 */
	.weak vm_datapart_lock_endread; .quad vm_datapart_lock_endread
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_endread; .int 0
	.int 0x3cbdf04
	.quad .Lname3242 /* index: 3242 */
	.weak sys32_quotactl; .quad sys32_quotactl
	.reloc ., R_X86_64_SIZE32, sys32_quotactl; .int 0
	.int 0xc0cfb9c
	.quad .Lname3243 /* index: 3243 */
	.weak mall_print_traceback; .quad mall_print_traceback
	.reloc ., R_X86_64_SIZE32, mall_print_traceback; .int 0
	.int 0xff78cab
	.quad 0 /* index: 3244 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3245 /* index: 3245 */
	.weak task_schedule_synchronous_rpc; .quad task_schedule_synchronous_rpc
	.reloc ., R_X86_64_SIZE32, task_schedule_synchronous_rpc; .int 0
	.int 0xc9ef653
	.quad .Lname3246 /* index: 3246 */
	.weak sys_perf_event_open; .quad sys_perf_event_open
	.reloc ., R_X86_64_SIZE32, sys_perf_event_open; .int 0
	.int 0x66accae
	.quad 0 /* index: 3247 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3248 /* index: 3248 */
	.weak dbg_putc; .quad dbg_putc
	.reloc ., R_X86_64_SIZE32, dbg_putc; .int 0
	.int 0x8d67a03
	.quad 0 /* index: 3249 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3250 /* index: 3250 */
	.weak dbg_pprinter; .quad dbg_pprinter
	.reloc ., R_X86_64_SIZE32, dbg_pprinter; .int 0
	.int 0x1288cb2
	.quad .Lname3251 /* index: 3251 */
	.weak kernel_heaps; .quad kernel_heaps
	.reloc ., R_X86_64_SIZE32, kernel_heaps; .int 0
	.int 0x7422cb3
	.quad 0 /* index: 3252 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3253 /* index: 3253 */
	.weak regdump_scpustate; .quad regdump_scpustate
	.reloc ., R_X86_64_SIZE32, regdump_scpustate; .int 0
	.int 0xbf47cb5
	.quad .Lname3254 /* index: 3254 */
	.weak sys32_read; .quad sys32_read
	.reloc ., R_X86_64_SIZE32, sys32_read; .int 0
	.int 0x6813b14
	.quad .Lname3255 /* index: 3255 */
	.weak json_parser_getstring; .quad json_parser_getstring
	.reloc ., R_X86_64_SIZE32, json_parser_getstring; .int 0
	.int 0x429ccb7
	.quad .Lname3256 /* index: 3256 */
	.weak vm_datablock_write_unsafe; .quad vm_datablock_write_unsafe
	.reloc ., R_X86_64_SIZE32, vm_datablock_write_unsafe; .int 0
	.int 0xaa46f95
	.quad .Lname3257 /* index: 3257 */
	.weak dbg_writememory; .quad dbg_writememory
	.reloc ., R_X86_64_SIZE32, dbg_writememory; .int 0
	.int 0x756dcb9
	.quad 0 /* index: 3258 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3259 /* index: 3259 */
	.weak sys32_sigaltstack; .quad sys32_sigaltstack
	.reloc ., R_X86_64_SIZE32, sys32_sigaltstack; .int 0
	.int 0xba85cbb
	.quad .Lname3260 /* index: 3260 */
	.weak vio_cmpxchl; .quad vio_cmpxchl
	.reloc ., R_X86_64_SIZE32, vio_cmpxchl; .int 0
	.int 0xa3aecbc
	.quad .Lname3261 /* index: 3261 */
	.weak linebuffer_write; .quad linebuffer_write
	.reloc ., R_X86_64_SIZE32, linebuffer_write; .int 0
	.int 0xdf28c25
	.quad .Lname3262 /* index: 3262 */
	.weak unwind_fde_rule; .quad unwind_fde_rule
	.reloc ., R_X86_64_SIZE32, unwind_fde_rule; .int 0
	.int 0x4b263b5
	.quad .Lname3263 /* index: 3263 */
	.weak sys32_rt_tgsigqueueinfo; .quad sys32_rt_tgsigqueueinfo
	.reloc ., R_X86_64_SIZE32, sys32_rt_tgsigqueueinfo; .int 0
	.int 0xa36ccbf
	.quad .Lname3264 /* index: 3264 */
	.weak format_hexdump; .quad format_hexdump
	.reloc ., R_X86_64_SIZE32, format_hexdump; .int 0
	.int 0x85d2cc0
	.quad .Lname3265 /* index: 3265 */
	.weak memsetq; .quad memsetq
	.reloc ., R_X86_64_SIZE32, memsetq; .int 0
	.int 0x3c49cc1
	.quad .Lname3266 /* index: 3266 */
	.weak vm_find_last_node_lower_equal; .quad vm_find_last_node_lower_equal
	.reloc ., R_X86_64_SIZE32, vm_find_last_node_lower_equal; .int 0
	.int 0x7a8a44c
	.quad .Lname3267 /* index: 3267 */
	.weak slab_kmalloc_nx56; .quad slab_kmalloc_nx56
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx56; .int 0
	.int 0x40d3d36
	.quad .Lname3268 /* index: 3268 */
	.weak sys_read; .quad sys_read
	.reloc ., R_X86_64_SIZE32, sys_read; .int 0
	.int 0x968cc4
	.quad .Lname3269 /* index: 3269 */
	.weak rwlock_endwrite; .quad rwlock_endwrite
	.reloc ., R_X86_64_SIZE32, rwlock_endwrite; .int 0
	.int 0x7e41cc5
	.quad .Lname3270 /* index: 3270 */
	.weak block_device_partition_writev; .quad block_device_partition_writev
	.reloc ., R_X86_64_SIZE32, block_device_partition_writev; .int 0
	.int 0x5487cc6
	.quad .Lname3271 /* index: 3271 */
	.weak memsetw; .quad memsetw
	.reloc ., R_X86_64_SIZE32, memsetw; .int 0
	.int 0x3c49cc7
	.quad .Lname3272 /* index: 3272 */
	.weak fpustate_init_nx; .quad fpustate_init_nx
	.reloc ., R_X86_64_SIZE32, fpustate_init_nx; .int 0
	.int 0x6fefcc8
	.quad .Lname3273 /* index: 3273 */
	.weak sys32_ioctl; .quad sys32_ioctl
	.reloc ., R_X86_64_SIZE32, sys32_ioctl; .int 0
	.int 0x8255ccc
	.quad .Lname3274 /* index: 3274 */
	.weak vm_datablock_vio_writev; .quad vm_datablock_vio_writev
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_writev; .int 0
	.int 0x4050206
	.quad .Lname3275 /* index: 3275 */
	.weak sys_ustat; .quad sys_ustat
	.reloc ., R_X86_64_SIZE32, sys_ustat; .int 0
	.int 0x96cd184
	.quad .Lname3276 /* index: 3276 */
	.weak sys32_fchdirat; .quad sys32_fchdirat
	.reloc ., R_X86_64_SIZE32, sys32_fchdirat; .int 0
	.int 0x98d8af4
	.quad .Lname3277 /* index: 3277 */
	.weak inodes_recent_lim; .quad inodes_recent_lim
	.reloc ., R_X86_64_SIZE32, inodes_recent_lim; .int 0
	.int 0x7609ccd
	.quad 0 /* index: 3278 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3279 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3280 /* index: 3280 */
	.weak vm_datablock_anonymous_zero_type_vec; .quad vm_datablock_anonymous_zero_type_vec
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous_zero_type_vec; .int 0
	.int 0x27a0e13
	.quad .Lname3281 /* index: 3281 */
	.weak this_sched_state; .quad this_sched_state
	.reloc ., R_X86_64_SIZE32, this_sched_state; .int 0
	.int 0x1049915
	.quad 0 /* index: 3282 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3283 /* index: 3283 */
	.weak devfs; .quad devfs
	.reloc ., R_X86_64_SIZE32, devfs; .int 0
	.int 0x6accd3
	.quad .Lname3284 /* index: 3284 */
	.weak dbg_autocomplete_command; .quad dbg_autocomplete_command
	.reloc ., R_X86_64_SIZE32, dbg_autocomplete_command; .int 0
	.int 0x573ccd4
	.quad .Lname3285 /* index: 3285 */
	.weak rwlock_canwrite; .quad rwlock_canwrite
	.reloc ., R_X86_64_SIZE32, rwlock_canwrite; .int 0
	.int 0x5041cd5
	.quad 0 /* index: 3286 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3287 /* index: 3287 */
	.weak isr_register_greedy; .quad isr_register_greedy
	.reloc ., R_X86_64_SIZE32, isr_register_greedy; .int 0
	.int 0xb4a7f79
	.quad .Lname3288 /* index: 3288 */
	.weak task_waitfor_nx; .quad task_waitfor_nx
	.reloc ., R_X86_64_SIZE32, task_waitfor_nx; .int 0
	.int 0xe0ecd8
	.quad .Lname3289 /* index: 3289 */
	.weak cpu_count; .quad cpu_count
	.reloc ., R_X86_64_SIZE32, cpu_count; .int 0
	.int 0xb5a0224
	.quad 0 /* index: 3290 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3291 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3292 /* index: 3292 */
	.weak memsetl; .quad memsetl
	.reloc ., R_X86_64_SIZE32, memsetl; .int 0
	.int 0x3c49cdc
	.quad .Lname3293 /* index: 3293 */
	.weak vm_do_ccfreeram; .quad vm_do_ccfreeram
	.reloc ., R_X86_64_SIZE32, vm_do_ccfreeram; .int 0
	.int 0x83eecdd
	.quad .Lname3294 /* index: 3294 */
	.weak this_exception_code; .quad this_exception_code
	.reloc ., R_X86_64_SIZE32, this_exception_code; .int 0
	.int 0x2698af5
	.quad .Lname3295 /* index: 3295 */
	.weak error_register_state; .quad error_register_state
	.reloc ., R_X86_64_SIZE32, error_register_state; .int 0
	.int 0x63c8225
	.quad 0 /* index: 3296 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3297 /* index: 3297 */
	.weak vmb_mapat; .quad vmb_mapat
	.reloc ., R_X86_64_SIZE32, vmb_mapat; .int 0
	.int 0x863fbb4
	.quad 0 /* index: 3298 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3299 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3300 /* index: 3300 */
	.weak json_parser_leaveobject; .quad json_parser_leaveobject
	.reloc ., R_X86_64_SIZE32, json_parser_leaveobject; .int 0
	.int 0xa048ce4
	.quad .Lname3301 /* index: 3301 */
	.weak json_writer_addfield; .quad json_writer_addfield
	.reloc ., R_X86_64_SIZE32, json_writer_addfield; .int 0
	.int 0x64d8f4
	.quad 0 /* index: 3302 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3303 /* index: 3303 */
	.weak vmb_isused; .quad vmb_isused
	.reloc ., R_X86_64_SIZE32, vmb_isused; .int 0
	.int 0x60d1a34
	.quad .Lname3304 /* index: 3304 */
	.weak heap_realloc_untraced_nx; .quad heap_realloc_untraced_nx
	.reloc ., R_X86_64_SIZE32, heap_realloc_untraced_nx; .int 0
	.int 0xac8ce8
	.quad 0 /* index: 3305 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3306 /* index: 3306 */
	.weak sys32_ptrace; .quad sys32_ptrace
	.reloc ., R_X86_64_SIZE32, sys32_ptrace; .int 0
	.int 0x1cbe115
	.quad 0 /* index: 3307 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3308 /* index: 3308 */
	.weak sys32_io_cancel; .quad sys32_io_cancel
	.reloc ., R_X86_64_SIZE32, sys32_io_cancel; .int 0
	.int 0x4006cec
	.quad 0 /* index: 3309 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3310 /* index: 3310 */
	.weak coredump_create_for_exception; .quad coredump_create_for_exception
	.reloc ., R_X86_64_SIZE32, coredump_create_for_exception; .int 0
	.int 0x9f51cee
	.quad 0 /* index: 3311 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3312 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3313 /* index: 3313 */
	.weak vm_datapart_lock_write_nx; .quad vm_datapart_lock_write_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_write_nx; .int 0
	.int 0x10ff228
	.quad 0 /* index: 3314 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3315 /* index: 3315 */
	.weak aio_handle_multiple_func; .quad aio_handle_multiple_func
	.reloc ., R_X86_64_SIZE32, aio_handle_multiple_func; .int 0
	.int 0x43decf3
	.quad .Lname3316 /* index: 3316 */
	.weak page_stat; .quad page_stat
	.reloc ., R_X86_64_SIZE32, page_stat; .int 0
	.int 0xdb6dcf4
	.quad .Lname3317 /* index: 3317 */
	.weak aio_multihandle_allochandle; .quad aio_multihandle_allochandle
	.reloc ., R_X86_64_SIZE32, aio_multihandle_allochandle; .int 0
	.int 0x834dcf5
	.quad .Lname3318 /* index: 3318 */
	.weak vm_tasklock_upgrade; .quad vm_tasklock_upgrade
	.reloc ., R_X86_64_SIZE32, vm_tasklock_upgrade; .int 0
	.int 0x14dce35
	.quad 0 /* index: 3319 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3320 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3321 /* index: 3321 */
	.weak debugline_loadunit; .quad debugline_loadunit
	.reloc ., R_X86_64_SIZE32, debugline_loadunit; .int 0
	.int 0x1150cd4
	.quad .Lname3322 /* index: 3322 */
	.weak x86_dbg_setregbyid; .quad x86_dbg_setregbyid
	.reloc ., R_X86_64_SIZE32, x86_dbg_setregbyid; .int 0
	.int 0x730c6e4
	.quad .Lname3323 /* index: 3323 */
	.weak sys_munlock; .quad sys_munlock
	.reloc ., R_X86_64_SIZE32, sys_munlock; .int 0
	.int 0x4e03cfb
	.quad 0 /* index: 3324 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3325 /* index: 3325 */
	.weak regdump_cr4; .quad regdump_cr4
	.reloc ., R_X86_64_SIZE32, regdump_cr4; .int 0
	.int 0xc3ee7e4
	.quad .Lname3326 /* index: 3326 */
	.weak sys_creat; .quad sys_creat
	.reloc ., R_X86_64_SIZE32, sys_creat; .int 0
	.int 0x95af084
	.quad .Lname3327 /* index: 3327 */
	.weak terminal_poll_iread; .quad terminal_poll_iread
	.reloc ., R_X86_64_SIZE32, terminal_poll_iread; .int 0
	.int 0xcfbd44
	.quad .Lname3328 /* index: 3328 */
	.weak this_x86_ioperm_bitmap; .quad this_x86_ioperm_bitmap
	.reloc ., R_X86_64_SIZE32, this_x86_ioperm_bitmap; .int 0
	.int 0x29a8d00
	.quad 0 /* index: 3329 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3330 /* index: 3330 */
	.weak sys32_linux_stat32; .quad sys32_linux_stat32
	.reloc ., R_X86_64_SIZE32, sys32_linux_stat32; .int 0
	.int 0x50abd02
	.quad .Lname3331 /* index: 3331 */
	.weak pagedir_push_mapone; .quad pagedir_push_mapone
	.reloc ., R_X86_64_SIZE32, pagedir_push_mapone; .int 0
	.int 0x82228f5
	.quad .Lname3332 /* index: 3332 */
	.weak sys32_frenameat; .quad sys32_frenameat
	.reloc ., R_X86_64_SIZE32, sys32_frenameat; .int 0
	.int 0xe301d04
	.quad .Lname3333 /* index: 3333 */
	.weak sys32_epoll_create; .quad sys32_epoll_create
	.reloc ., R_X86_64_SIZE32, sys32_epoll_create; .int 0
	.int 0x7dffd05
	.quad .Lname3334 /* index: 3334 */
	.weak inode_areadv; .quad inode_areadv
	.reloc ., R_X86_64_SIZE32, inode_areadv; .int 0
	.int 0x28ded06
	.quad 0 /* index: 3335 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3336 /* index: 3336 */
	.weak pidns_upgrade_nx; .quad pidns_upgrade_nx
	.reloc ., R_X86_64_SIZE32, pidns_upgrade_nx; .int 0
	.int 0xdeb1d08
	.quad .Lname3337 /* index: 3337 */
	.weak quantum_local_to_global; .quad quantum_local_to_global
	.reloc ., R_X86_64_SIZE32, quantum_local_to_global; .int 0
	.int 0x77aca2c
	.quad 0 /* index: 3338 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3339 /* index: 3339 */
	.weak _boottask; .quad _boottask
	.reloc ., R_X86_64_SIZE32, _boottask; .int 0
	.int 0x66bcd0b
	.quad .Lname3340 /* index: 3340 */
	.weak unwind_setreg_scpustate_exclusive; .quad unwind_setreg_scpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_setreg_scpustate_exclusive; .int 0
	.int 0xb8e5125
	.quad 0 /* index: 3341 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3342 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3343 /* index: 3343 */
	.weak vm_datapart_read_nopf; .quad vm_datapart_read_nopf
	.reloc ., R_X86_64_SIZE32, vm_datapart_read_nopf; .int 0
	.int 0xab90b86
	.quad .Lname3344 /* index: 3344 */
	.weak pagedir_unmap_userspace_nosync_p; .quad pagedir_unmap_userspace_nosync_p
	.reloc ., R_X86_64_SIZE32, pagedir_unmap_userspace_nosync_p; .int 0
	.int 0x7a0bd10
	.quad .Lname3345 /* index: 3345 */
	.weak task_yield_nx; .quad task_yield_nx
	.reloc ., R_X86_64_SIZE32, task_yield_nx; .int 0
	.int 0x54894d8
	.quad .Lname3346 /* index: 3346 */
	.weak dbg_attr; .quad dbg_attr
	.reloc ., R_X86_64_SIZE32, dbg_attr; .int 0
	.int 0x8d58d12
	.quad .Lname3347 /* index: 3347 */
	.weak vfs_alloc; .quad vfs_alloc
	.reloc ., R_X86_64_SIZE32, vfs_alloc; .int 0
	.int 0x9586f83
	.quad .Lname3348 /* index: 3348 */
	.weak sys32_pivot_root; .quad sys32_pivot_root
	.reloc ., R_X86_64_SIZE32, sys32_pivot_root; .int 0
	.int 0x2776d4
	.quad .Lname3349 /* index: 3349 */
	.weak debuginfo_print_typename; .quad debuginfo_print_typename
	.reloc ., R_X86_64_SIZE32, debuginfo_print_typename; .int 0
	.int 0x247cd15
	.quad .Lname3350 /* index: 3350 */
	.weak ioperm_bitmap_copyf; .quad ioperm_bitmap_copyf
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_copyf; .int 0
	.int 0x1b01d16
	.quad .Lname3351 /* index: 3351 */
	.weak cpu_assert_integrity; .quad cpu_assert_integrity
	.reloc ., R_X86_64_SIZE32, cpu_assert_integrity; .int 0
	.int 0x19364d9
	.quad .Lname3352 /* index: 3352 */
	.weak thiscpu_quantum_length; .quad thiscpu_quantum_length
	.reloc ., R_X86_64_SIZE32, thiscpu_quantum_length; .int 0
	.int 0x8cfed18
	.quad .Lname3353 /* index: 3353 */
	.weak sys32_pread64; .quad sys32_pread64
	.reloc ., R_X86_64_SIZE32, sys32_pread64; .int 0
	.int 0xc8d1f84
	.quad 0 /* index: 3354 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3355 /* index: 3355 */
	.weak dbg_stack; .quad dbg_stack
	.reloc ., R_X86_64_SIZE32, dbg_stack; .int 0
	.int 0xd6acd1b
	.quad 0 /* index: 3356 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3357 /* index: 3357 */
	.weak unicode_32to8; .quad unicode_32to8
	.reloc ., R_X86_64_SIZE32, unicode_32to8; .int 0
	.int 0x76940f8
	.quad .Lname3358 /* index: 3358 */
	.weak pagedir_haschanged; .quad pagedir_haschanged
	.reloc ., R_X86_64_SIZE32, pagedir_haschanged; .int 0
	.int 0xec67e94
	.quad .Lname3359 /* index: 3359 */
	.weak dbg_enter_here_c; .quad dbg_enter_here_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_here_c; .int 0
	.int 0x2f8fe3
	.quad .Lname3360 /* index: 3360 */
	.weak sys_seccomp; .quad sys_seccomp
	.reloc ., R_X86_64_SIZE32, sys_seccomp; .int 0
	.int 0x9c2ad20
	.quad .Lname3361 /* index: 3361 */
	.weak sys_truncate; .quad sys_truncate
	.reloc ., R_X86_64_SIZE32, sys_truncate; .int 0
	.int 0xe140e15
	.quad .Lname3362 /* index: 3362 */
	.weak driver_getshstrtab; .quad driver_getshstrtab
	.reloc ., R_X86_64_SIZE32, driver_getshstrtab; .int 0
	.int 0xd4f5d22
	.quad .Lname3363 /* index: 3363 */
	.weak fpustate_alloc; .quad fpustate_alloc
	.reloc ., R_X86_64_SIZE32, fpustate_alloc; .int 0
	.int 0xe9e9d23
	.quad .Lname3364 /* index: 3364 */
	.weak dbg_draweditfield; .quad dbg_draweditfield
	.reloc ., R_X86_64_SIZE32, dbg_draweditfield; .int 0
	.int 0xb4ead24
	.quad .Lname3365 /* index: 3365 */
	.weak ioperm_bitmap_setrange; .quad ioperm_bitmap_setrange
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_setrange; .int 0
	.int 0xb167d25
	.quad .Lname3366 /* index: 3366 */
	.weak sys32_syncfs; .quad sys32_syncfs
	.reloc ., R_X86_64_SIZE32, sys32_syncfs; .int 0
	.int 0x1202f53
	.quad 0 /* index: 3367 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3368 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3369 /* index: 3369 */
	.weak keyboard_device_fini; .quad keyboard_device_fini
	.reloc ., R_X86_64_SIZE32, keyboard_device_fini; .int 0
	.int 0xf165d29
	.quad .Lname3370 /* index: 3370 */
	.weak unwind_setreg_ucpustate; .quad unwind_setreg_ucpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_ucpustate; .int 0
	.int 0xb8d01b5
	.quad 0 /* index: 3371 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3372 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3373 /* index: 3373 */
	.weak vm_datablock_vio_read; .quad vm_datablock_vio_read
	.reloc ., R_X86_64_SIZE32, vm_datablock_vio_read; .int 0
	.int 0x8c46774
	.quad 0 /* index: 3374 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3375 /* index: 3375 */
	.weak sys32_sendto; .quad sys32_sendto
	.reloc ., R_X86_64_SIZE32, sys32_sendto; .int 0
	.int 0x12c2d2f
	.quad .Lname3376 /* index: 3376 */
	.weak vm_datapart_do_allocram; .quad vm_datapart_do_allocram
	.reloc ., R_X86_64_SIZE32, vm_datapart_do_allocram; .int 0
	.int 0x1c5802d
	.quad 0 /* index: 3377 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3378 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3379 /* index: 3379 */
	.weak sys32_setns; .quad sys32_setns
	.reloc ., R_X86_64_SIZE32, sys32_setns; .int 0
	.int 0x812cd33
	.quad .Lname3380 /* index: 3380 */
	.weak sys32_getresuid; .quad sys32_getresuid
	.reloc ., R_X86_64_SIZE32, sys32_getresuid; .int 0
	.int 0xde48d34
	.quad .Lname3381 /* index: 3381 */
	.weak dbg_enter_scpustate; .quad dbg_enter_scpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_scpustate; .int 0
	.int 0x7819d35
	.quad .Lname3382 /* index: 3382 */
	.weak dbg_enter_kcpustate_c; .quad dbg_enter_kcpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_kcpustate_c; .int 0
	.int 0x1b53ed3
	.quad .Lname3383 /* index: 3383 */
	.weak sys32_renameat2; .quad sys32_renameat2
	.reloc ., R_X86_64_SIZE32, sys32_renameat2; .int 0
	.int 0x22babb2
	.quad .Lname3384 /* index: 3384 */
	.weak slab_kmalloc_nx; .quad slab_kmalloc_nx
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx; .int 0
	.int 0x6b40d38
	.quad .Lname3385 /* index: 3385 */
	.weak sys_mq_timedsend; .quad sys_mq_timedsend
	.reloc ., R_X86_64_SIZE32, sys_mq_timedsend; .int 0
	.int 0x5f94234
	.quad 0 /* index: 3386 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3387 /* index: 3387 */
	.weak sys32_sysinfo; .quad sys32_sysinfo
	.reloc ., R_X86_64_SIZE32, sys32_sysinfo; .int 0
	.int 0x20facdf
	.quad .Lname3388 /* index: 3388 */
	.weak driver_insmod_file; .quad driver_insmod_file
	.reloc ., R_X86_64_SIZE32, driver_insmod_file; .int 0
	.int 0x7829925
	.quad .Lname3389 /* index: 3389 */
	.weak sys32_fadvise64; .quad sys32_fadvise64
	.reloc ., R_X86_64_SIZE32, sys32_fadvise64; .int 0
	.int 0xdb8bfe4
	.quad 0 /* index: 3390 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3391 /* index: 3391 */
	.weak pidns_downgrade; .quad pidns_downgrade
	.reloc ., R_X86_64_SIZE32, pidns_downgrade; .int 0
	.int 0x717aa35
	.quad .Lname3392 /* index: 3392 */
	.weak cpu_enter_deepsleep; .quad cpu_enter_deepsleep
	.reloc ., R_X86_64_SIZE32, cpu_enter_deepsleep; .int 0
	.int 0xcc52d40
	.quad 0 /* index: 3393 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3394 /* index: 3394 */
	.weak kernel_syscall0_restartmode32; .quad kernel_syscall0_restartmode32
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_restartmode32; .int 0
	.int 0x8fa8d42
	.quad .Lname3395 /* index: 3395 */
	.weak sys_set_tid_address; .quad sys_set_tid_address
	.reloc ., R_X86_64_SIZE32, sys_set_tid_address; .int 0
	.int 0x4c81d43
	.quad .Lname3396 /* index: 3396 */
	.weak path_lock_read; .quad path_lock_read
	.reloc ., R_X86_64_SIZE32, path_lock_read; .int 0
	.int 0x2b8ed44
	.quad 0 /* index: 3397 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3398 /* index: 3398 */
	.weak __acheckf; .quad __acheckf
	.reloc ., R_X86_64_SIZE32, __acheckf; .int 0
	.int 0x79edd46
	.quad .Lname3399 /* index: 3399 */
	.weak kernel_syscall1_regcnt32; .quad kernel_syscall1_regcnt32
	.reloc ., R_X86_64_SIZE32, kernel_syscall1_regcnt32; .int 0
	.int 0xa815cb2
	.quad .Lname3400 /* index: 3400 */
	.weak pidns_read_nx; .quad pidns_read_nx
	.reloc ., R_X86_64_SIZE32, pidns_read_nx; .int 0
	.int 0xe4cdd48
	.quad .Lname3401 /* index: 3401 */
	.weak sys32_umount; .quad sys32_umount
	.reloc ., R_X86_64_SIZE32, sys32_umount; .int 0
	.int 0x1140ed4
	.quad .Lname3402 /* index: 3402 */
	.weak path_getchild_and_parent_inode; .quad path_getchild_and_parent_inode
	.reloc ., R_X86_64_SIZE32, path_getchild_and_parent_inode; .int 0
	.int 0x871b5c5
	.quad .Lname3403 /* index: 3403 */
	.weak memmovedownw; .quad memmovedownw
	.reloc ., R_X86_64_SIZE32, memmovedownw; .int 0
	.int 0xb872a37
	.quad .Lname3404 /* index: 3404 */
	.weak setreg_kcpustate; .quad setreg_kcpustate
	.reloc ., R_X86_64_SIZE32, setreg_kcpustate; .int 0
	.int 0xf7675b5
	.quad 0 /* index: 3405 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3406 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3407 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3408 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3409 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3410 /* index: 3410 */
	.weak sys32_fremovexattr; .quad sys32_fremovexattr
	.reloc ., R_X86_64_SIZE32, sys32_fremovexattr; .int 0
	.int 0xea66d52
	.quad .Lname3411 /* index: 3411 */
	.weak sys32_migrate_pages; .quad sys32_migrate_pages
	.reloc ., R_X86_64_SIZE32, sys32_migrate_pages; .int 0
	.int 0x39e9d53
	.quad .Lname3412 /* index: 3412 */
	.weak sys32_getppid; .quad sys32_getppid
	.reloc ., R_X86_64_SIZE32, sys32_getppid; .int 0
	.int 0x6cd1ed4
	.quad .Lname3413 /* index: 3413 */
	.weak callback_list_remove; .quad callback_list_remove
	.reloc ., R_X86_64_SIZE32, callback_list_remove; .int 0
	.int 0xffbcd55
	.quad 0 /* index: 3414 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3415 /* index: 3415 */
	.weak isr_unregister_any; .quad isr_unregister_any
	.reloc ., R_X86_64_SIZE32, isr_unregister_any; .int 0
	.int 0x8473239
	.quad 0 /* index: 3416 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3417 /* index: 3417 */
	.weak ioperm_bitmap_empty; .quad ioperm_bitmap_empty
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_empty; .int 0
	.int 0x1ae3d59
	.quad .Lname3418 /* index: 3418 */
	.weak sys32_olduname; .quad sys32_olduname
	.reloc ., R_X86_64_SIZE32, sys32_olduname; .int 0
	.int 0x2dec5c5
	.quad .Lname3419 /* index: 3419 */
	.weak path_traversen_at; .quad path_traversen_at
	.reloc ., R_X86_64_SIZE32, path_traversen_at; .int 0
	.int 0xf5643a4
	.quad .Lname3420 /* index: 3420 */
	.weak sys_fchown; .quad sys_fchown
	.reloc ., R_X86_64_SIZE32, sys_fchown; .int 0
	.int 0x5ce664e
	.quad .Lname3421 /* index: 3421 */
	.weak vm_do_freeram; .quad vm_do_freeram
	.reloc ., R_X86_64_SIZE32, vm_do_freeram; .int 0
	.int 0xbe7d5d
	.quad .Lname3422 /* index: 3422 */
	.weak vm_datapart_lock_downgrade; .quad vm_datapart_lock_downgrade
	.reloc ., R_X86_64_SIZE32, vm_datapart_lock_downgrade; .int 0
	.int 0xe1af345
	.quad .Lname3423 /* index: 3423 */
	.weak error_info; .quad error_info
	.reloc ., R_X86_64_SIZE32, error_info; .int 0
	.int 0x6834d5f
	.quad 0 /* index: 3424 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3425 /* index: 3425 */
	.weak memrlenq; .quad memrlenq
	.reloc ., R_X86_64_SIZE32, memrlenq; .int 0
	.int 0xc492d61
	.quad .Lname3426 /* index: 3426 */
	.weak sys32_chdir; .quad sys32_chdir
	.reloc ., R_X86_64_SIZE32, sys32_chdir; .int 0
	.int 0x822ed62
	.quad 0 /* index: 3427 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3428 /* index: 3428 */
	.weak sys_getgid; .quad sys_getgid
	.reloc ., R_X86_64_SIZE32, sys_getgid; .int 0
	.int 0x5db1d64
	.quad .Lname3429 /* index: 3429 */
	.weak boot_cpustate; .quad boot_cpustate
	.reloc ., R_X86_64_SIZE32, boot_cpustate; .int 0
	.int 0xeac0d65
	.quad .Lname3430 /* index: 3430 */
	.weak dbg_addr2line_printf; .quad dbg_addr2line_printf
	.reloc ., R_X86_64_SIZE32, dbg_addr2line_printf; .int 0
	.int 0xb1f7d66
	.quad .Lname3431 /* index: 3431 */
	.weak memrlenw; .quad memrlenw
	.reloc ., R_X86_64_SIZE32, memrlenw; .int 0
	.int 0xc492d67
	.quad .Lname3432 /* index: 3432 */
	.weak vm_tasklock_write_nx; .quad vm_tasklock_write_nx
	.reloc ., R_X86_64_SIZE32, vm_tasklock_write_nx; .int 0
	.int 0xb3e4d68
	.quad .Lname3433 /* index: 3433 */
	.weak sys_msgctl; .quad sys_msgctl
	.reloc ., R_X86_64_SIZE32, sys_msgctl; .int 0
	.int 0x64e6a3c
	.quad .Lname3434 /* index: 3434 */
	.weak sys32_rpc_schedule; .quad sys32_rpc_schedule
	.reloc ., R_X86_64_SIZE32, sys32_rpc_schedule; .int 0
	.int 0x8cd4c35
	.quad .Lname3435 /* index: 3435 */
	.weak pidns_trylookup_task; .quad pidns_trylookup_task
	.reloc ., R_X86_64_SIZE32, pidns_trylookup_task; .int 0
	.int 0xa1e7d6b
	.quad .Lname3436 /* index: 3436 */
	.weak sys32_fallocate64; .quad sys32_fallocate64
	.reloc ., R_X86_64_SIZE32, sys32_fallocate64; .int 0
	.int 0xdbf2dc4
	.quad .Lname3437 /* index: 3437 */
	.weak vm_onexec_callbacks; .quad vm_onexec_callbacks
	.reloc ., R_X86_64_SIZE32, vm_onexec_callbacks; .int 0
	.int 0x2a745f3
	.quad .Lname3438 /* index: 3438 */
	.weak vm_datapart_readv; .quad vm_datapart_readv
	.reloc ., R_X86_64_SIZE32, vm_datapart_readv; .int 0
	.int 0x2bdea86
	.quad 0 /* index: 3439 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3440 /* index: 3440 */
	.weak vm_datapart_map_ram_autoprop_p; .quad vm_datapart_map_ram_autoprop_p
	.reloc ., R_X86_64_SIZE32, vm_datapart_map_ram_autoprop_p; .int 0
	.int 0x9217d70
	.quad .Lname3441 /* index: 3441 */
	.weak unwind_getreg_ucpustate_exclusive; .quad unwind_getreg_ucpustate_exclusive
	.reloc ., R_X86_64_SIZE32, unwind_getreg_ucpustate_exclusive; .int 0
	.int 0x98e5065
	.quad .Lname3442 /* index: 3442 */
	.weak mouse_buffer_putpackets_nopr; .quad mouse_buffer_putpackets_nopr
	.reloc ., R_X86_64_SIZE32, mouse_buffer_putpackets_nopr; .int 0
	.int 0x5a58d72
	.quad 0 /* index: 3443 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3444 /* index: 3444 */
	.weak debuginfo_location_select; .quad debuginfo_location_select
	.reloc ., R_X86_64_SIZE32, debuginfo_location_select; .int 0
	.int 0x19e2d74
	.quad .Lname3445 /* index: 3445 */
	.weak rawmemlen; .quad rawmemlen
	.reloc ., R_X86_64_SIZE32, rawmemlen; .int 0
	.int 0xe3c5a3e
	.quad .Lname3446 /* index: 3446 */
	.weak dbg_printf; .quad dbg_printf
	.reloc ., R_X86_64_SIZE32, dbg_printf; .int 0
	.int 0x67e6d76
	.quad .Lname3447 /* index: 3447 */
	.weak vm_get_aslr_disabled; .quad vm_get_aslr_disabled
	.reloc ., R_X86_64_SIZE32, vm_get_aslr_disabled; .int 0
	.int 0xb495884
	.quad 0 /* index: 3448 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3449 /* index: 3449 */
	.weak sys_prlimit64; .quad sys_prlimit64
	.reloc ., R_X86_64_SIZE32, sys_prlimit64; .int 0
	.int 0xa0b6f94
	.quad .Lname3450 /* index: 3450 */
	.weak this_sched_runnxt; .quad this_sched_runnxt
	.reloc ., R_X86_64_SIZE32, this_sched_runnxt; .int 0
	.int 0x796ee4
	.quad 0 /* index: 3451 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3452 /* index: 3452 */
	.weak memrlenl; .quad memrlenl
	.reloc ., R_X86_64_SIZE32, memrlenl; .int 0
	.int 0xc492d7c
	.quad .Lname3453 /* index: 3453 */
	.weak thiscpu_override; .quad thiscpu_override
	.reloc ., R_X86_64_SIZE32, thiscpu_override; .int 0
	.int 0x56994c5
	.quad .Lname3454 /* index: 3454 */
	.weak unicode_readutf8_n; .quad unicode_readutf8_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf8_n; .int 0
	.int 0x6b8ed7e
	.quad .Lname3455 /* index: 3455 */
	.weak pagedir_maphintone; .quad pagedir_maphintone
	.reloc ., R_X86_64_SIZE32, pagedir_maphintone; .int 0
	.int 0x9e65795
	.quad .Lname3456 /* index: 3456 */
	.weak thiscpu_x86_spurious_interrupts; .quad thiscpu_x86_spurious_interrupts
	.reloc ., R_X86_64_SIZE32, thiscpu_x86_spurious_interrupts; .int 0
	.int 0xbebac13
	.quad .Lname3457 /* index: 3457 */
	.weak memcmp; .quad memcmp
	.reloc ., R_X86_64_SIZE32, memcmp; .int 0
	.int 0x73c3a40
	.quad .Lname3458 /* index: 3458 */
	.weak sys32_fchdir; .quad sys32_fchdir
	.reloc ., R_X86_64_SIZE32, sys32_fchdir; .int 0
	.int 0x2798d82
	.quad .Lname3459 /* index: 3459 */
	.weak this_exception_class; .quad this_exception_class
	.reloc ., R_X86_64_SIZE32, this_exception_class; .int 0
	.int 0x698dd83
	.quad .Lname3460 /* index: 3460 */
	.weak sys_getdents64; .quad sys_getdents64
	.reloc ., R_X86_64_SIZE32, sys_getdents64; .int 0
	.int 0xa306d84
	.quad .Lname3461 /* index: 3461 */
	.weak kernel_terminal_check_sigttou; .quad kernel_terminal_check_sigttou
	.reloc ., R_X86_64_SIZE32, kernel_terminal_check_sigttou; .int 0
	.int 0xf867d85
	.quad 0 /* index: 3462 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3463 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3464 /* index: 3464 */
	.weak task_detach; .quad task_detach
	.reloc ., R_X86_64_SIZE32, task_detach; .int 0
	.int 0x5d62d88
	.quad .Lname3465 /* index: 3465 */
	.weak driver_section_destroy; .quad driver_section_destroy
	.reloc ., R_X86_64_SIZE32, driver_section_destroy; .int 0
	.int 0xca42d89
	.quad .Lname3466 /* index: 3466 */
	.weak setreg_sfpustate; .quad setreg_sfpustate
	.reloc ., R_X86_64_SIZE32, setreg_sfpustate; .int 0
	.int 0xf765dc5
	.quad .Lname3467 /* index: 3467 */
	.weak sys32_utime64; .quad sys32_utime64
	.reloc ., R_X86_64_SIZE32, sys32_utime64; .int 0
	.int 0x7aa5084
	.quad .Lname3468 /* index: 3468 */
	.weak sys32_restart_syscall; .quad sys32_restart_syscall
	.reloc ., R_X86_64_SIZE32, sys32_restart_syscall; .int 0
	.int 0x7c91d8c
	.quad .Lname3469 /* index: 3469 */
	.weak sys_membarrier; .quad sys_membarrier
	.reloc ., R_X86_64_SIZE32, sys_membarrier; .int 0
	.int 0x81fb242
	.quad 0 /* index: 3470 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3471 /* index: 3471 */
	.weak sys32_sysctl; .quad sys32_sysctl
	.reloc ., R_X86_64_SIZE32, sys32_sysctl; .int 0
	.int 0x120fc2c
	.quad .Lname3472 /* index: 3472 */
	.weak thisvm_x86_dr0; .quad thisvm_x86_dr0
	.reloc ., R_X86_64_SIZE32, thisvm_x86_dr0; .int 0
	.int 0x4b28d90
	.quad .Lname3473 /* index: 3473 */
	.weak thisvm_x86_dr1; .quad thisvm_x86_dr1
	.reloc ., R_X86_64_SIZE32, thisvm_x86_dr1; .int 0
	.int 0x4b28d91
	.quad .Lname3474 /* index: 3474 */
	.weak thisvm_x86_dr2; .quad thisvm_x86_dr2
	.reloc ., R_X86_64_SIZE32, thisvm_x86_dr2; .int 0
	.int 0x4b28d92
	.quad .Lname3475 /* index: 3475 */
	.weak cpu_disable_preemptive_interrupts; .quad cpu_disable_preemptive_interrupts
	.reloc ., R_X86_64_SIZE32, cpu_disable_preemptive_interrupts; .int 0
	.int 0xf1a5d93
	.quad .Lname3476 /* index: 3476 */
	.weak fs_filesystems_lock_read; .quad fs_filesystems_lock_read
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_read; .int 0
	.int 0xa6b9d94
	.quad .Lname3477 /* index: 3477 */
	.weak sys_close; .quad sys_close
	.reloc ., R_X86_64_SIZE32, sys_close; .int 0
	.int 0x95a6d95
	.quad .Lname3478 /* index: 3478 */
	.weak this_trampoline_node; .quad this_trampoline_node
	.reloc ., R_X86_64_SIZE32, this_trampoline_node; .int 0
	.int 0xe061b45
	.quad .Lname3479 /* index: 3479 */
	.weak thisvm_x86_dr7; .quad thisvm_x86_dr7
	.reloc ., R_X86_64_SIZE32, thisvm_x86_dr7; .int 0
	.int 0x4b28d97
	.quad 0 /* index: 3480 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3481 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3482 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3483 /* index: 3483 */
	.weak sys_chdir; .quad sys_chdir
	.reloc ., R_X86_64_SIZE32, sys_chdir; .int 0
	.int 0x9599202
	.quad .Lname3484 /* index: 3484 */
	.weak get_stack_avail; .quad get_stack_avail
	.reloc ., R_X86_64_SIZE32, get_stack_avail; .int 0
	.int 0xb320d9c
	.quad .Lname3485 /* index: 3485 */
	.weak sys32_getrandom; .quad sys32_getrandom
	.reloc ., R_X86_64_SIZE32, sys32_getrandom; .int 0
	.int 0xdf06d9d
	.quad 0 /* index: 3486 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3487 /* index: 3487 */
	.weak directory_getnode; .quad directory_getnode
	.reloc ., R_X86_64_SIZE32, directory_getnode; .int 0
	.int 0x718e245
	.quad 0 /* index: 3488 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3489 /* index: 3489 */
	.weak sys32_getpid; .quad sys32_getpid
	.reloc ., R_X86_64_SIZE32, sys32_getpid; .int 0
	.int 0x26cd074
	.quad .Lname3490 /* index: 3490 */
	.weak rwlock_writing_r; .quad rwlock_writing_r
	.reloc ., R_X86_64_SIZE32, rwlock_writing_r; .int 0
	.int 0x508bda2
	.quad 0 /* index: 3491 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3492 /* index: 3492 */
	.weak debuginfo_cu_parser_loadattr_compile_unit; .quad debuginfo_cu_parser_loadattr_compile_unit
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_loadattr_compile_unit; .int 0
	.int 0xe589da4
	.quad .Lname3493 /* index: 3493 */
	.weak devfs_lock_endwrite; .quad devfs_lock_endwrite
	.reloc ., R_X86_64_SIZE32, devfs_lock_endwrite; .int 0
	.int 0xd287da5
	.quad .Lname3494 /* index: 3494 */
	.weak error_vprintf; .quad error_vprintf
	.reloc ., R_X86_64_SIZE32, error_vprintf; .int 0
	.int 0x1e1ada6
	.quad .Lname3495 /* index: 3495 */
	.weak sys_settimeofday; .quad sys_settimeofday
	.reloc ., R_X86_64_SIZE32, sys_settimeofday; .int 0
	.int 0x53ec0f9
	.quad 0 /* index: 3496 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3497 /* index: 3497 */
	.weak sys32_getpriority; .quad sys32_getpriority
	.reloc ., R_X86_64_SIZE32, sys32_getpriority; .int 0
	.int 0xe05da9
	.quad 0 /* index: 3498 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3499 /* index: 3499 */
	.weak mempmovedownw; .quad mempmovedownw
	.reloc ., R_X86_64_SIZE32, mempmovedownw; .int 0
	.int 0xf7f1a47
	.quad 0 /* index: 3500 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3501 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3502 /* index: 3502 */
	.weak sys_execve; .quad sys_execve
	.reloc ., R_X86_64_SIZE32, sys_execve; .int 0
	.int 0x5c90a55
	.quad .Lname3503 /* index: 3503 */
	.weak fs_filesystems_lock_endwrite; .quad fs_filesystems_lock_endwrite
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_endwrite; .int 0
	.int 0x254f815
	.quad .Lname3504 /* index: 3504 */
	.weak vm_datablock_debugheap; .quad vm_datablock_debugheap
	.reloc ., R_X86_64_SIZE32, vm_datablock_debugheap; .int 0
	.int 0x6931db0
	.quad .Lname3505 /* index: 3505 */
	.weak sys_get_thread_area; .quad sys_get_thread_area
	.reloc ., R_X86_64_SIZE32, sys_get_thread_area; .int 0
	.int 0x5062db1
	.quad .Lname3506 /* index: 3506 */
	.weak dbg_enter_fcpustate_cr; .quad dbg_enter_fcpustate_cr
	.reloc ., R_X86_64_SIZE32, dbg_enter_fcpustate_cr; .int 0
	.int 0xa83edb2
	.quad .Lname3507 /* index: 3507 */
	.weak block_device_writev_phys_sync; .quad block_device_writev_phys_sync
	.reloc ., R_X86_64_SIZE32, block_device_writev_phys_sync; .int 0
	.int 0x2f9dcf3
	.quad .Lname3508 /* index: 3508 */
	.weak sys32_rt_sigsuspend; .quad sys32_rt_sigsuspend
	.reloc ., R_X86_64_SIZE32, sys32_rt_sigsuspend; .int 0
	.int 0x86a9db4
	.quad .Lname3509 /* index: 3509 */
	.weak getreg_scpustate; .quad getreg_scpustate
	.reloc ., R_X86_64_SIZE32, getreg_scpustate; .int 0
	.int 0xf711db5
	.quad 0 /* index: 3510 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3511 /* index: 3511 */
	.weak vm_writephysl_unaligned; .quad vm_writephysl_unaligned
	.reloc ., R_X86_64_SIZE32, vm_writephysl_unaligned; .int 0
	.int 0xfd858d4
	.quad .Lname3512 /* index: 3512 */
	.weak __cxa_begin_catch; .quad __cxa_begin_catch
	.reloc ., R_X86_64_SIZE32, __cxa_begin_catch; .int 0
	.int 0x5646db8
	.quad .Lname3513 /* index: 3513 */
	.weak sys32_sched_yield; .quad sys32_sched_yield
	.reloc ., R_X86_64_SIZE32, sys32_sched_yield; .int 0
	.int 0x27d64f4
	.quad 0 /* index: 3514 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3515 /* index: 3515 */
	.weak task_serve_nx; .quad task_serve_nx
	.reloc ., R_X86_64_SIZE32, task_serve_nx; .int 0
	.int 0x616c4b8
	.quad .Lname3516 /* index: 3516 */
	.weak sys_fmknodat; .quad sys_fmknodat
	.reloc ., R_X86_64_SIZE32, sys_fmknodat; .int 0
	.int 0x5b5cf54
	.quad 0 /* index: 3517 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3518 /* index: 3518 */
	.weak disasm_instrlen; .quad disasm_instrlen
	.reloc ., R_X86_64_SIZE32, disasm_instrlen; .int 0
	.int 0xc21edbe
	.quad .Lname3519 /* index: 3519 */
	.weak rwlock_tryupgrade; .quad rwlock_tryupgrade
	.reloc ., R_X86_64_SIZE32, rwlock_tryupgrade; .int 0
	.int 0x6e1dcf5
	.quad .Lname3520 /* index: 3520 */
	.weak slab_kmalloc_nx40; .quad slab_kmalloc_nx40
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx40; .int 0
	.int 0x40d3dc0
	.quad .Lname3521 /* index: 3521 */
	.weak this_x86_kernel_psp0; .quad this_x86_kernel_psp0
	.reloc ., R_X86_64_SIZE32, this_x86_kernel_psp0; .int 0
	.int 0xf8edf60
	.quad 0 /* index: 3522 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3523 /* index: 3523 */
	.weak fs_filesystem_types; .quad fs_filesystem_types
	.reloc ., R_X86_64_SIZE32, fs_filesystem_types; .int 0
	.int 0x42f7dc3
	.quad .Lname3524 /* index: 3524 */
	.weak fs_filesystems_lock_tryread; .quad fs_filesystems_lock_tryread
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_tryread; .int 0
	.int 0xb0e2dc4
	.quad .Lname3525 /* index: 3525 */
	.weak blocking_cleanup_service; .quad blocking_cleanup_service
	.reloc ., R_X86_64_SIZE32, blocking_cleanup_service; .int 0
	.int 0x86c0dc5
	.quad 0 /* index: 3526 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3527 /* index: 3527 */
	.weak sys_getpmsg; .quad sys_getpmsg
	.reloc ., R_X86_64_SIZE32, sys_getpmsg; .int 0
	.int 0xdb07dc7
	.quad .Lname3528 /* index: 3528 */
	.weak slab_kmalloc_nx48; .quad slab_kmalloc_nx48
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx48; .int 0
	.int 0x40d3dc8
	.quad 0 /* index: 3529 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3530 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3531 /* index: 3531 */
	.weak __acheck; .quad __acheck
	.reloc ., R_X86_64_SIZE32, __acheck; .int 0
	.int 0x579edcb
	.quad .Lname3532 /* index: 3532 */
	.weak block_device_partition_ioctl; .quad block_device_partition_ioctl
	.reloc ., R_X86_64_SIZE32, block_device_partition_ioctl; .int 0
	.int 0x66adcc
	.quad .Lname3533 /* index: 3533 */
	.weak get_stack_for; .quad get_stack_for
	.reloc ., R_X86_64_SIZE32, get_stack_for; .int 0
	.int 0xa6b37a2
	.quad .Lname3534 /* index: 3534 */
	.weak sys_kexec_load; .quad sys_kexec_load
	.reloc ., R_X86_64_SIZE32, sys_kexec_load; .int 0
	.int 0xb244e24
	.quad .Lname3535 /* index: 3535 */
	.weak task_setprocessgroupleader; .quad task_setprocessgroupleader
	.reloc ., R_X86_64_SIZE32, task_setprocessgroupleader; .int 0
	.int 0x6fbbb2
	.quad 0 /* index: 3536 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3537 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3538 /* index: 3538 */
	.weak slab_kmalloc_nx32; .quad slab_kmalloc_nx32
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx32; .int 0
	.int 0x40d3dd2
	.quad .Lname3539 /* index: 3539 */
	.weak block_device_read_phys_sync; .quad block_device_read_phys_sync
	.reloc ., R_X86_64_SIZE32, block_device_read_phys_sync; .int 0
	.int 0x2b46dd3
	.quad .Lname3540 /* index: 3540 */
	.weak sig_send; .quad sig_send
	.reloc ., R_X86_64_SIZE32, sig_send; .int 0
	.int 0xfd69dd4
	.quad .Lname3541 /* index: 3541 */
	.weak this_cpu; .quad this_cpu
	.reloc ., R_X86_64_SIZE32, this_cpu; .int 0
	.int 0xf095dd5
	.quad .Lname3542 /* index: 3542 */
	.weak sys32_swapoff; .quad sys32_swapoff
	.reloc ., R_X86_64_SIZE32, sys32_swapoff; .int 0
	.int 0x1de1dd6
	.quad 0 /* index: 3543 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3544 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3545 /* index: 3545 */
	.weak kernel_personality; .quad kernel_personality
	.reloc ., R_X86_64_SIZE32, kernel_personality; .int 0
	.int 0x33e8dd9
	.quad .Lname3546 /* index: 3546 */
	.weak vm_datablock_readvp; .quad vm_datablock_readvp
	.reloc ., R_X86_64_SIZE32, vm_datablock_readvp; .int 0
	.int 0xc438930
	.quad .Lname3547 /* index: 3547 */
	.weak sys32_lseek; .quad sys32_lseek
	.reloc ., R_X86_64_SIZE32, sys32_lseek; .int 0
	.int 0x8389ddb
	.quad .Lname3548 /* index: 3548 */
	.weak aio_multihandle_fail; .quad aio_multihandle_fail
	.reloc ., R_X86_64_SIZE32, aio_multihandle_fail; .int 0
	.int 0x81d8ddc
	.quad .Lname3549 /* index: 3549 */
	.weak sys32_sched_get_priority_min; .quad sys32_sched_get_priority_min
	.reloc ., R_X86_64_SIZE32, sys32_sched_get_priority_min; .int 0
	.int 0xbe3504e
	.quad .Lname3550 /* index: 3550 */
	.weak sys_chown; .quad sys_chown
	.reloc ., R_X86_64_SIZE32, sys_chown; .int 0
	.int 0x959adde
	.quad .Lname3551 /* index: 3551 */
	.weak mall_trace; .quad mall_trace
	.reloc ., R_X86_64_SIZE32, mall_trace; .int 0
	.int 0x26cbfa5
	.quad 0 /* index: 3552 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3553 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3554 /* index: 3554 */
	.weak kprinter; .quad kprinter
	.reloc ., R_X86_64_SIZE32, kprinter; .int 0
	.int 0x7905de2
	.quad .Lname3555 /* index: 3555 */
	.weak task_enable_redirect_usercode_rpc; .quad task_enable_redirect_usercode_rpc
	.reloc ., R_X86_64_SIZE32, task_enable_redirect_usercode_rpc; .int 0
	.int 0x92cade3
	.quad .Lname3556 /* index: 3556 */
	.weak slab_kmalloc_nx24; .quad slab_kmalloc_nx24
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx24; .int 0
	.int 0x40d3de4
	.quad .Lname3557 /* index: 3557 */
	.weak this_x86_fpustate; .quad this_x86_fpustate
	.reloc ., R_X86_64_SIZE32, this_x86_fpustate; .int 0
	.int 0x10bfde5
	.quad 0 /* index: 3558 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3559 /* index: 3559 */
	.weak vm_stopdma; .quad vm_stopdma
	.reloc ., R_X86_64_SIZE32, vm_stopdma; .int 0
	.int 0xab1ba51
	.quad 0 /* index: 3560 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3561 /* index: 3561 */
	.weak x86_fpustate_load; .quad x86_fpustate_load
	.reloc ., R_X86_64_SIZE32, x86_fpustate_load; .int 0
	.int 0x7b343a4
	.quad .Lname3562 /* index: 3562 */
	.weak keyboard_device_putkey; .quad keyboard_device_putkey
	.reloc ., R_X86_64_SIZE32, keyboard_device_putkey; .int 0
	.int 0x5efded9
	.quad 0 /* index: 3563 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3564 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3565 /* index: 3565 */
	.weak aio_pbuffer_copyfrommem; .quad aio_pbuffer_copyfrommem
	.reloc ., R_X86_64_SIZE32, aio_pbuffer_copyfrommem; .int 0
	.int 0xf3faded
	.quad .Lname3566 /* index: 3566 */
	.weak kmemalign; .quad kmemalign
	.reloc ., R_X86_64_SIZE32, kmemalign; .int 0
	.int 0xc385dee
	.quad 0 /* index: 3567 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3568 /* index: 3568 */
	.weak pagedir_unprepare_map; .quad pagedir_unprepare_map
	.reloc ., R_X86_64_SIZE32, pagedir_unprepare_map; .int 0
	.int 0xf67bdf0
	.quad .Lname3569 /* index: 3569 */
	.weak x86_syscall_emulate32_cdecl_r; .quad x86_syscall_emulate32_cdecl_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate32_cdecl_r; .int 0
	.int 0xa299242
	.quad .Lname3570 /* index: 3570 */
	.weak ansitty_printer; .quad ansitty_printer
	.reloc ., R_X86_64_SIZE32, ansitty_printer; .int 0
	.int 0xd858df2
	.quad .Lname3571 /* index: 3571 */
	.weak sys_setns; .quad sys_setns
	.reloc ., R_X86_64_SIZE32, sys_setns; .int 0
	.int 0x969b253
	.quad .Lname3572 /* index: 3572 */
	.weak fs_filesystems_lock_endread; .quad fs_filesystems_lock_endread
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_endread; .int 0
	.int 0xb252df4
	.quad .Lname3573 /* index: 3573 */
	.weak kernel_debugtrap_fcpustate; .quad kernel_debugtrap_fcpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_fcpustate; .int 0
	.int 0x9638df5
	.quad .Lname3574 /* index: 3574 */
	.weak slab_kmalloc_nx16; .quad slab_kmalloc_nx16
	.reloc ., R_X86_64_SIZE32, slab_kmalloc_nx16; .int 0
	.int 0x40d3df6
	.quad .Lname3575 /* index: 3575 */
	.weak sys_putpmsg; .quad sys_putpmsg
	.reloc ., R_X86_64_SIZE32, sys_putpmsg; .int 0
	.int 0x7b07df7
	.quad .Lname3576 /* index: 3576 */
	.weak sys32_inotify_add_watch; .quad sys32_inotify_add_watch
	.reloc ., R_X86_64_SIZE32, sys32_inotify_add_watch; .int 0
	.int 0xf918df8
	.quad .Lname3577 /* index: 3577 */
	.weak json_writer_putfloat; .quad json_writer_putfloat
	.reloc ., R_X86_64_SIZE32, json_writer_putfloat; .int 0
	.int 0x6651a54
	.quad 0 /* index: 3578 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3579 /* index: 3579 */
	.weak sys_fsmode; .quad sys_fsmode
	.reloc ., R_X86_64_SIZE32, sys_fsmode; .int 0
	.int 0x5df9535
	.quad 0 /* index: 3580 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3581 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3582 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3583 /* index: 3583 */
	.weak sys32_stime; .quad sys32_stime
	.reloc ., R_X86_64_SIZE32, sys32_stime; .int 0
	.int 0x811aa55
	.quad .Lname3584 /* index: 3584 */
	.weak unwind_getreg_kcpustate; .quad unwind_getreg_kcpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_kcpustate; .int 0
	.int 0xb8c4bb5
	.quad .Lname3585 /* index: 3585 */
	.weak sys32_mknodat; .quad sys32_mknodat
	.reloc ., R_X86_64_SIZE32, sys32_mknodat; .int 0
	.int 0x92332b4
	.quad .Lname3586 /* index: 3586 */
	.weak heap_realloc_nx; .quad heap_realloc_nx
	.reloc ., R_X86_64_SIZE32, heap_realloc_nx; .int 0
	.int 0xb537188
	.quad .Lname3587 /* index: 3587 */
	.weak task_disconnect_c; .quad task_disconnect_c
	.reloc ., R_X86_64_SIZE32, task_disconnect_c; .int 0
	.int 0x2a1be03
	.quad .Lname3588 /* index: 3588 */
	.weak sys_frealpathat; .quad sys_frealpathat
	.reloc ., R_X86_64_SIZE32, sys_frealpathat; .int 0
	.int 0xa355e04
	.quad .Lname3589 /* index: 3589 */
	.weak fs_filesystems_lock_write; .quad fs_filesystems_lock_write
	.reloc ., R_X86_64_SIZE32, fs_filesystems_lock_write; .int 0
	.int 0x6bffe05
	.quad .Lname3590 /* index: 3590 */
	.weak thisvm_library_listdef; .quad thisvm_library_listdef
	.reloc ., R_X86_64_SIZE32, thisvm_library_listdef; .int 0
	.int 0x2553e06
	.quad .Lname3591 /* index: 3591 */
	.weak sys_lchown; .quad sys_lchown
	.reloc ., R_X86_64_SIZE32, sys_lchown; .int 0
	.int 0x62e664e
	.quad 0 /* index: 3592 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3593 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3594 /* index: 3594 */
	.weak sys_msync; .quad sys_msync
	.reloc ., R_X86_64_SIZE32, sys_msync; .int 0
	.int 0x964d543
	.quad 0 /* index: 3595 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3596 /* index: 3596 */
	.weak path_traversefull; .quad path_traversefull
	.reloc ., R_X86_64_SIZE32, path_traversefull; .int 0
	.int 0xf55de0c
	.quad .Lname3597 /* index: 3597 */
	.weak sys32_getitimer; .quad sys32_getitimer
	.reloc ., R_X86_64_SIZE32, sys32_getitimer; .int 0
	.int 0xd62e502
	.quad 0 /* index: 3598 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3599 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3600 /* index: 3600 */
	.weak vm_datapart_allocswap; .quad vm_datapart_allocswap
	.reloc ., R_X86_64_SIZE32, vm_datapart_allocswap; .int 0
	.int 0x682e10
	.quad 0 /* index: 3601 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3602 /* index: 3602 */
	.weak x86_syscall_emulate_sysvabi_r; .quad x86_syscall_emulate_sysvabi_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate_sysvabi_r; .int 0
	.int 0x9468e12
	.quad .Lname3603 /* index: 3603 */
	.weak block_device_write_sync; .quad block_device_write_sync
	.reloc ., R_X86_64_SIZE32, block_device_write_sync; .int 0
	.int 0x213be13
	.quad .Lname3604 /* index: 3604 */
	.weak debuginfo_cu_parser_getconst; .quad debuginfo_cu_parser_getconst
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getconst; .int 0
	.int 0xb486e14
	.quad .Lname3605 /* index: 3605 */
	.weak kernel_symbol_table; .quad kernel_symbol_table
	.reloc ., R_X86_64_SIZE32, kernel_symbol_table; .int 0
	.int 0x70d0e15
	.quad 0 /* index: 3606 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3607 /* index: 3607 */
	.weak sys_getppid; .quad sys_getppid
	.reloc ., R_X86_64_SIZE32, sys_getppid; .int 0
	.int 0xdb07fa4
	.quad 0 /* index: 3608 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3609 /* index: 3609 */
	.weak sys_renameat; .quad sys_renameat
	.reloc ., R_X86_64_SIZE32, sys_renameat; .int 0
	.int 0xdf8ad04
	.quad 0 /* index: 3610 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3611 /* index: 3611 */
	.weak cpu_delsleepingtask; .quad cpu_delsleepingtask
	.reloc ., R_X86_64_SIZE32, cpu_delsleepingtask; .int 0
	.int 0x7b74e1b
	.quad 0 /* index: 3612 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3613 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3614 /* index: 3614 */
	.weak disasm_print_instruction; .quad disasm_print_instruction
	.reloc ., R_X86_64_SIZE32, disasm_print_instruction; .int 0
	.int 0x433ee1e
	.quad .Lname3615 /* index: 3615 */
	.weak page_ccfree; .quad page_ccfree
	.reloc ., R_X86_64_SIZE32, page_ccfree; .int 0
	.int 0x5efa505
	.quad .Lname3616 /* index: 3616 */
	.weak pagedir_prepare_mapone_p; .quad pagedir_prepare_mapone_p
	.reloc ., R_X86_64_SIZE32, pagedir_prepare_mapone_p; .int 0
	.int 0x9dd5e20
	.quad .Lname3617 /* index: 3617 */
	.weak vio_xchq; .quad vio_xchq
	.reloc ., R_X86_64_SIZE32, vio_xchq; .int 0
	.int 0x56ee21
	.quad 0 /* index: 3618 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3619 /* index: 3619 */
	.weak block_device_readv_phys; .quad block_device_readv_phys
	.reloc ., R_X86_64_SIZE32, block_device_readv_phys; .int 0
	.int 0x3231e23
	.quad .Lname3620 /* index: 3620 */
	.weak inode_read; .quad inode_read
	.reloc ., R_X86_64_SIZE32, inode_read; .int 0
	.int 0xab18e24
	.quad .Lname3621 /* index: 3621 */
	.weak keymap_translate; .quad keymap_translate
	.reloc ., R_X86_64_SIZE32, keymap_translate; .int 0
	.int 0x5db5e25
	.quad .Lname3622 /* index: 3622 */
	.weak vm_readphysw_unaligned; .quad vm_readphysw_unaligned
	.reloc ., R_X86_64_SIZE32, vm_readphysw_unaligned; .int 0
	.int 0x32eb44
	.quad .Lname3623 /* index: 3623 */
	.weak vio_xchw; .quad vio_xchw
	.reloc ., R_X86_64_SIZE32, vio_xchw; .int 0
	.int 0x56ee27
	.quad .Lname3624 /* index: 3624 */
	.weak sys_mbind; .quad sys_mbind
	.reloc ., R_X86_64_SIZE32, sys_mbind; .int 0
	.int 0x963f544
	.quad .Lname3625 /* index: 3625 */
	.weak sys32_epoll_wait; .quad sys32_epoll_wait
	.reloc ., R_X86_64_SIZE32, sys32_epoll_wait; .int 0
	.int 0x5a4a144
	.quad 0 /* index: 3626 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3627 /* index: 3627 */
	.weak empty_kernel_sigmask; .quad empty_kernel_sigmask
	.reloc ., R_X86_64_SIZE32, empty_kernel_sigmask; .int 0
	.int 0xf36e2b
	.quad 0 /* index: 3628 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3629 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3630 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3631 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3632 /* index: 3632 */
	.weak pagedir_map; .quad pagedir_map
	.reloc ., R_X86_64_SIZE32, pagedir_map; .int 0
	.int 0xb723e30
	.quad .Lname3633 /* index: 3633 */
	.weak slab_malloc8; .quad slab_malloc8
	.reloc ., R_X86_64_SIZE32, slab_malloc8; .int 0
	.int 0x4e16d08
	.quad .Lname3634 /* index: 3634 */
	.weak dbg_setcur; .quad dbg_setcur
	.reloc ., R_X86_64_SIZE32, dbg_setcur; .int 0
	.int 0x69a0212
	.quad .Lname3635 /* index: 3635 */
	.weak sys32_sysfs; .quad sys32_sysfs
	.reloc ., R_X86_64_SIZE32, sys32_sysfs; .int 0
	.int 0x8120fb3
	.quad .Lname3636 /* index: 3636 */
	.weak heap_truncate_untraced; .quad heap_truncate_untraced
	.reloc ., R_X86_64_SIZE32, heap_truncate_untraced; .int 0
	.int 0xa5f9e34
	.quad .Lname3637 /* index: 3637 */
	.weak cpu_quantum_time; .quad cpu_quantum_time
	.reloc ., R_X86_64_SIZE32, cpu_quantum_time; .int 0
	.int 0xebb4e35
	.quad .Lname3638 /* index: 3638 */
	.weak sys_pwrite64f; .quad sys_pwrite64f
	.reloc ., R_X86_64_SIZE32, sys_pwrite64f; .int 0
	.int 0x403ee36
	.quad .Lname3639 /* index: 3639 */
	.weak vm_memsetphyspages; .quad vm_memsetphyspages
	.reloc ., R_X86_64_SIZE32, vm_memsetphyspages; .int 0
	.int 0x3e9a883
	.quad .Lname3640 /* index: 3640 */
	.weak vm_enumdma_nx; .quad vm_enumdma_nx
	.reloc ., R_X86_64_SIZE32, vm_enumdma_nx; .int 0
	.int 0xea6b188
	.quad .Lname3641 /* index: 3641 */
	.weak dbg_purgeuni; .quad dbg_purgeuni
	.reloc ., R_X86_64_SIZE32, dbg_purgeuni; .int 0
	.int 0xa251e39
	.quad 0 /* index: 3642 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3643 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3644 /* index: 3644 */
	.weak vio_xchl; .quad vio_xchl
	.reloc ., R_X86_64_SIZE32, vio_xchl; .int 0
	.int 0x56ee3c
	.quad 0 /* index: 3645 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3646 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3647 /* index: 3647 */
	.weak cmdline_encode; .quad cmdline_encode
	.reloc ., R_X86_64_SIZE32, cmdline_encode; .int 0
	.int 0x617a7b5
	.quad 0 /* index: 3648 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3649 /* index: 3649 */
	.weak sys_epoll_create1; .quad sys_epoll_create1
	.reloc ., R_X86_64_SIZE32, sys_epoll_create1; .int 0
	.int 0x6a4b381
	.quad .Lname3650 /* index: 3650 */
	.weak task_schedule_asynchronous_rpc; .quad task_schedule_asynchronous_rpc
	.reloc ., R_X86_64_SIZE32, task_schedule_asynchronous_rpc; .int 0
	.int 0xef54f13
	.quad .Lname3651 /* index: 3651 */
	.weak block_device_partition_read_phys; .quad block_device_partition_read_phys
	.reloc ., R_X86_64_SIZE32, block_device_partition_read_phys; .int 0
	.int 0x1063e43
	.quad .Lname3652 /* index: 3652 */
	.weak sys_execveat; .quad sys_execveat
	.reloc ., R_X86_64_SIZE32, sys_execveat; .int 0
	.int 0x90a5e44
	.quad .Lname3653 /* index: 3653 */
	.weak kernel_vpanic_scpustate; .quad kernel_vpanic_scpustate
	.reloc ., R_X86_64_SIZE32, kernel_vpanic_scpustate; .int 0
	.int 0xf5ade45
	.quad .Lname3654 /* index: 3654 */
	.weak kernel_vpanic_lcpustate; .quad kernel_vpanic_lcpustate
	.reloc ., R_X86_64_SIZE32, kernel_vpanic_lcpustate; .int 0
	.int 0xf5af545
	.quad .Lname3655 /* index: 3655 */
	.weak unwind_emulator_exec; .quad unwind_emulator_exec
	.reloc ., R_X86_64_SIZE32, unwind_emulator_exec; .int 0
	.int 0x9e9a9f3
	.quad 0 /* index: 3656 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3657 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3658 /* index: 3658 */
	.weak sys_set_robust_list; .quad sys_set_robust_list
	.reloc ., R_X86_64_SIZE32, sys_set_robust_list; .int 0
	.int 0xa0820d4
	.quad 0 /* index: 3659 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3660 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3661 /* index: 3661 */
	.weak sys32_lgetxattr; .quad sys32_lgetxattr
	.reloc ., R_X86_64_SIZE32, sys32_lgetxattr; .int 0
	.int 0xad6b262
	.quad 0 /* index: 3662 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3663 /* index: 3663 */
	.weak vm_writephysw_unaligned; .quad vm_writephysw_unaligned
	.reloc ., R_X86_64_SIZE32, vm_writephysw_unaligned; .int 0
	.int 0xff358d4
	.quad .Lname3664 /* index: 3664 */
	.weak sys32_seccomp; .quad sys32_seccomp
	.reloc ., R_X86_64_SIZE32, sys32_seccomp; .int 0
	.int 0x2c00e50
	.quad 0 /* index: 3665 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3666 /* index: 3666 */
	.weak sys32_mmap2; .quad sys32_mmap2
	.reloc ., R_X86_64_SIZE32, sys32_mmap2; .int 0
	.int 0x8393e52
	.quad .Lname3667 /* index: 3667 */
	.weak block_device_write_phys; .quad block_device_write_phys
	.reloc ., R_X86_64_SIZE32, block_device_write_phys; .int 0
	.int 0x2137e53
	.quad .Lname3668 /* index: 3668 */
	.weak path_printent; .quad path_printent
	.reloc ., R_X86_64_SIZE32, path_printent; .int 0
	.int 0xe8f4e54
	.quad .Lname3669 /* index: 3669 */
	.weak vm_datapart_loaddatapage; .quad vm_datapart_loaddatapage
	.reloc ., R_X86_64_SIZE32, vm_datapart_loaddatapage; .int 0
	.int 0x128ce55
	.quad .Lname3670 /* index: 3670 */
	.weak unicode_readutf16; .quad unicode_readutf16
	.reloc ., R_X86_64_SIZE32, unicode_readutf16; .int 0
	.int 0x26b8e56
	.quad .Lname3671 /* index: 3671 */
	.weak handle_lookup_type; .quad handle_lookup_type
	.reloc ., R_X86_64_SIZE32, handle_lookup_type; .int 0
	.int 0x1adaf65
	.quad .Lname3672 /* index: 3672 */
	.weak vm_datapart_lockwrite_setcore_unsharecow_nx; .quad vm_datapart_lockwrite_setcore_unsharecow_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_lockwrite_setcore_unsharecow_nx; .int 0
	.int 0x2083e58
	.quad .Lname3673 /* index: 3673 */
	.weak sys32_clock_settime64; .quad sys32_clock_settime64
	.reloc ., R_X86_64_SIZE32, sys32_clock_settime64; .int 0
	.int 0xfa77264
	.quad .Lname3674 /* index: 3674 */
	.weak terminal_setios; .quad terminal_setios
	.reloc ., R_X86_64_SIZE32, terminal_setios; .int 0
	.int 0xfdc9283
	.quad 0 /* index: 3675 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3676 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3677 /* index: 3677 */
	.weak task_pause; .quad task_pause
	.reloc ., R_X86_64_SIZE32, task_pause; .int 0
	.int 0x1612435
	.quad .Lname3678 /* index: 3678 */
	.weak page_stat_between; .quad page_stat_between
	.reloc ., R_X86_64_SIZE32, page_stat_between; .int 0
	.int 0xe172e5e
	.quad .Lname3679 /* index: 3679 */
	.weak page_mallocone; .quad page_mallocone
	.reloc ., R_X86_64_SIZE32, page_mallocone; .int 0
	.int 0x70f0265
	.quad .Lname3680 /* index: 3680 */
	.weak sys_tgkill; .quad sys_tgkill
	.reloc ., R_X86_64_SIZE32, sys_tgkill; .int 0
	.int 0x6abb0bc
	.quad .Lname3681 /* index: 3681 */
	.weak x86_dbg_regfromname; .quad x86_dbg_regfromname
	.reloc ., R_X86_64_SIZE32, x86_dbg_regfromname; .int 0
	.int 0x198a115
	.quad .Lname3682 /* index: 3682 */
	.weak sys_getxattr; .quad sys_getxattr
	.reloc ., R_X86_64_SIZE32, sys_getxattr; .int 0
	.int 0xb0e1e62
	.quad .Lname3683 /* index: 3683 */
	.weak block_device_readv_sync; .quad block_device_readv_sync
	.reloc ., R_X86_64_SIZE32, block_device_readv_sync; .int 0
	.int 0x323de63
	.quad .Lname3684 /* index: 3684 */
	.weak dbg_fillrect; .quad dbg_fillrect
	.reloc ., R_X86_64_SIZE32, dbg_fillrect; .int 0
	.int 0xa9b5e64
	.quad .Lname3685 /* index: 3685 */
	.weak dbg_tabsize; .quad dbg_tabsize
	.reloc ., R_X86_64_SIZE32, dbg_tabsize; .int 0
	.int 0xa132e65
	.quad 0 /* index: 3686 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3687 /* index: 3687 */
	.weak vm_datapart_getfutex_existing; .quad vm_datapart_getfutex_existing
	.reloc ., R_X86_64_SIZE32, vm_datapart_getfutex_existing; .int 0
	.int 0x12efe67
	.quad .Lname3688 /* index: 3688 */
	.weak sys_fchdirat; .quad sys_fchdirat
	.reloc ., R_X86_64_SIZE32, sys_fchdirat; .int 0
	.int 0xe5b9d44
	.quad .Lname3689 /* index: 3689 */
	.weak sys_semget; .quad sys_semget
	.reloc ., R_X86_64_SIZE32, sys_semget; .int 0
	.int 0x69d8d54
	.quad .Lname3690 /* index: 3690 */
	.weak vm_mapat; .quad vm_mapat
	.reloc ., R_X86_64_SIZE32, vm_mapat; .int 0
	.int 0x3638154
	.quad 0 /* index: 3691 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3692 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3693 /* index: 3693 */
	.weak this_handle_manager; .quad this_handle_manager
	.reloc ., R_X86_64_SIZE32, this_handle_manager; .int 0
	.int 0xddfbd12
	.quad .Lname3694 /* index: 3694 */
	.weak unwind_fde_exec_landing_pad_adjustment; .quad unwind_fde_exec_landing_pad_adjustment
	.reloc ., R_X86_64_SIZE32, unwind_fde_exec_landing_pad_adjustment; .int 0
	.int 0x3144214
	.quad .Lname3695 /* index: 3695 */
	.weak unicode_readutf8_rev_n; .quad unicode_readutf8_rev_n
	.reloc ., R_X86_64_SIZE32, unicode_readutf8_rev_n; .int 0
	.int 0xd4e74be
	.quad 0 /* index: 3696 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3697 /* index: 3697 */
	.weak regdump_sgregs; .quad regdump_sgregs
	.reloc ., R_X86_64_SIZE32, regdump_sgregs; .int 0
	.int 0xd454803
	.quad .Lname3698 /* index: 3698 */
	.weak sys_getitimer; .quad sys_getitimer
	.reloc ., R_X86_64_SIZE32, sys_getitimer; .int 0
	.int 0x203be72
	.quad .Lname3699 /* index: 3699 */
	.weak thiscpu_jiffies; .quad thiscpu_jiffies
	.reloc ., R_X86_64_SIZE32, thiscpu_jiffies; .int 0
	.int 0x66ce73
	.quad .Lname3700 /* index: 3700 */
	.weak pagedir_gethint; .quad pagedir_gethint
	.reloc ., R_X86_64_SIZE32, pagedir_gethint; .int 0
	.int 0x719e74
	.quad .Lname3701 /* index: 3701 */
	.weak heap_truncate; .quad heap_truncate
	.reloc ., R_X86_64_SIZE32, heap_truncate; .int 0
	.int 0x71cfe75
	.quad .Lname3702 /* index: 3702 */
	.weak unicode_readutf8_rev; .quad unicode_readutf8_rev
	.reloc ., R_X86_64_SIZE32, unicode_readutf8_rev; .int 0
	.int 0x8ed4e76
	.quad 0 /* index: 3703 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3704 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3705 /* index: 3705 */
	.weak task_setthread; .quad task_setthread
	.reloc ., R_X86_64_SIZE32, task_setthread; .int 0
	.int 0x30ee514
	.quad .Lname3706 /* index: 3706 */
	.weak x86_pagedir_sync; .quad x86_pagedir_sync
	.reloc ., R_X86_64_SIZE32, x86_pagedir_sync; .int 0
	.int 0x626d033
	.quad .Lname3707 /* index: 3707 */
	.weak sys32_reboot; .quad sys32_reboot
	.reloc ., R_X86_64_SIZE32, sys32_reboot; .int 0
	.int 0x13bf4e4
	.quad 0 /* index: 3708 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3709 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3710 /* index: 3710 */
	.weak sys32_sigreturn; .quad sys32_sigreturn
	.reloc ., R_X86_64_SIZE32, sys32_sigreturn; .int 0
	.int 0x8e4ae7e
	.quad .Lname3711 /* index: 3711 */
	.weak strnend; .quad strnend
	.reloc ., R_X86_64_SIZE32, strnend; .int 0
	.int 0xab94c34
	.quad .Lname3712 /* index: 3712 */
	.weak pagedir_unwrite_p; .quad pagedir_unwrite_p
	.reloc ., R_X86_64_SIZE32, pagedir_unwrite_p; .int 0
	.int 0x602be80
	.quad .Lname3713 /* index: 3713 */
	.weak vm86_step; .quad vm86_step
	.reloc ., R_X86_64_SIZE32, vm86_step; .int 0
	.int 0xbc6d7c0
	.quad .Lname3714 /* index: 3714 */
	.weak this_x86_rpc_redirection_iret; .quad this_x86_rpc_redirection_iret
	.reloc ., R_X86_64_SIZE32, this_x86_rpc_redirection_iret; .int 0
	.int 0x6fa7f94
	.quad .Lname3715 /* index: 3715 */
	.weak this_fs; .quad this_fs
	.reloc ., R_X86_64_SIZE32, this_fs; .int 0
	.int 0xaf095a3
	.quad .Lname3716 /* index: 3716 */
	.weak sys32_signalfd4; .quad sys32_signalfd4
	.reloc ., R_X86_64_SIZE32, sys32_signalfd4; .int 0
	.int 0xc303e84
	.quad .Lname3717 /* index: 3717 */
	.weak character_device_lookup_name; .quad character_device_lookup_name
	.reloc ., R_X86_64_SIZE32, character_device_lookup_name; .int 0
	.int 0x4d7fe85
	.quad .Lname3718 /* index: 3718 */
	.weak mouse_buffer_getpacket; .quad mouse_buffer_getpacket
	.reloc ., R_X86_64_SIZE32, mouse_buffer_getpacket; .int 0
	.int 0xe112104
	.quad 0 /* index: 3719 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3720 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3721 /* index: 3721 */
	.weak dbg_ungetuni; .quad dbg_ungetuni
	.reloc ., R_X86_64_SIZE32, dbg_ungetuni; .int 0
	.int 0x2746e89
	.quad .Lname3722 /* index: 3722 */
	.weak pagedir_unwriteone; .quad pagedir_unwriteone
	.reloc ., R_X86_64_SIZE32, pagedir_unwriteone; .int 0
	.int 0x2bdc25
	.quad 0 /* index: 3723 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3724 /* index: 3724 */
	.weak dbg_bell; .quad dbg_bell
	.reloc ., R_X86_64_SIZE32, dbg_bell; .int 0
	.int 0x8d58e8c
	.quad .Lname3725 /* index: 3725 */
	.weak strtou32; .quad strtou32
	.reloc ., R_X86_64_SIZE32, strtou32; .int 0
	.int 0xb9b6fc2
	.quad .Lname3726 /* index: 3726 */
	.weak sys32_mq_open; .quad sys32_mq_open
	.reloc ., R_X86_64_SIZE32, sys32_mq_open; .int 0
	.int 0xf740e8e
	.quad .Lname3727 /* index: 3727 */
	.weak vm_do_ffreeram; .quad vm_do_ffreeram
	.reloc ., R_X86_64_SIZE32, vm_do_ffreeram; .int 0
	.int 0xed09a6d
	.quad .Lname3728 /* index: 3728 */
	.weak this_connections; .quad this_connections
	.reloc ., R_X86_64_SIZE32, this_connections; .int 0
	.int 0x2cb0a13
	.quad .Lname3729 /* index: 3729 */
	.weak vm_kernel_treelock_read_nx; .quad vm_kernel_treelock_read_nx
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_read_nx; .int 0
	.int 0xb04ad18
	.quad 0 /* index: 3730 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3731 /* index: 3731 */
	.weak vm_datablock_anonymous_zero_vec; .quad vm_datablock_anonymous_zero_vec
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous_zero_vec; .int 0
	.int 0x1362e93
	.quad .Lname3732 /* index: 3732 */
	.weak debuginfo_cu_parser_nextchild; .quad debuginfo_cu_parser_nextchild
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_nextchild; .int 0
	.int 0x1492e94
	.quad .Lname3733 /* index: 3733 */
	.weak pagedir_translate; .quad pagedir_translate
	.reloc ., R_X86_64_SIZE32, pagedir_translate; .int 0
	.int 0xd2c3e95
	.quad .Lname3734 /* index: 3734 */
	.weak sys_ioctlf; .quad sys_ioctlf
	.reloc ., R_X86_64_SIZE32, sys_ioctlf; .int 0
	.int 0x6021bb6
	.quad 0 /* index: 3735 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3736 /* index: 3736 */
	.weak sys32_sync_file_range; .quad sys32_sync_file_range
	.reloc ., R_X86_64_SIZE32, sys32_sync_file_range; .int 0
	.int 0x995baf5
	.quad .Lname3737 /* index: 3737 */
	.weak x86_idt; .quad x86_idt
	.reloc ., R_X86_64_SIZE32, x86_idt; .int 0
	.int 0xbbc5fc4
	.quad .Lname3738 /* index: 3738 */
	.weak sys_sysctl; .quad sys_sysctl
	.reloc ., R_X86_64_SIZE32, sys_sysctl; .int 0
	.int 0x6b72a3c
	.quad .Lname3739 /* index: 3739 */
	.weak sys_flock; .quad sys_flock
	.reloc ., R_X86_64_SIZE32, sys_flock; .int 0
	.int 0x95d6e9b
	.quad .Lname3740 /* index: 3740 */
	.weak sys32_linux_fstatat64; .quad sys32_linux_fstatat64
	.reloc ., R_X86_64_SIZE32, sys32_linux_fstatat64; .int 0
	.int 0x92ce034
	.quad .Lname3741 /* index: 3741 */
	.weak sys32_getpeername; .quad sys32_getpeername
	.reloc ., R_X86_64_SIZE32, sys32_getpeername; .int 0
	.int 0x3ef8b35
	.quad .Lname3742 /* index: 3742 */
	.weak sys32_setregid; .quad sys32_setregid
	.reloc ., R_X86_64_SIZE32, sys32_setregid; .int 0
	.int 0xcde3cd4
	.quad .Lname3743 /* index: 3743 */
	.weak sys_sethostname; .quad sys_sethostname
	.reloc ., R_X86_64_SIZE32, sys_sethostname; .int 0
	.int 0xfc4f7c5
	.quad .Lname3744 /* index: 3744 */
	.weak kernel_debugtrap; .quad kernel_debugtrap
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap; .int 0
	.int 0xd79fea0
	.quad .Lname3745 /* index: 3745 */
	.weak sys_raiseat; .quad sys_raiseat
	.reloc ., R_X86_64_SIZE32, sys_raiseat; .int 0
	.int 0x81b92e4
	.quad 0 /* index: 3746 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3747 /* index: 3747 */
	.weak inode_areadk; .quad inode_areadk
	.reloc ., R_X86_64_SIZE32, inode_areadk; .int 0
	.int 0x28ded1b
	.quad .Lname3748 /* index: 3748 */
	.weak sys32_readvf; .quad sys32_readvf
	.reloc ., R_X86_64_SIZE32, sys32_readvf; .int 0
	.int 0x13b1d46
	.quad .Lname3749 /* index: 3749 */
	.weak handle_tryclose; .quad handle_tryclose
	.reloc ., R_X86_64_SIZE32, handle_tryclose; .int 0
	.int 0xd4d0ea5
	.quad 0 /* index: 3750 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3751 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3752 /* index: 3752 */
	.weak rwlock_read_nx; .quad rwlock_read_nx
	.reloc ., R_X86_64_SIZE32, rwlock_read_nx; .int 0
	.int 0x6824ea8
	.quad 0 /* index: 3753 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3754 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3755 /* index: 3755 */
	.weak sys_bpf; .quad sys_bpf
	.reloc ., R_X86_64_SIZE32, sys_bpf; .int 0
	.int 0xb095916
	.quad .Lname3756 /* index: 3756 */
	.weak sys_fcntl; .quad sys_fcntl
	.reloc ., R_X86_64_SIZE32, sys_fcntl; .int 0
	.int 0x95cfeac
	.quad 0 /* index: 3757 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3758 /* index: 3758 */
	.weak heap_alloc_untraced; .quad heap_alloc_untraced
	.reloc ., R_X86_64_SIZE32, heap_alloc_untraced; .int 0
	.int 0x8158a14
	.quad 0 /* index: 3759 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3760 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3761 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3762 /* index: 3762 */
	.weak sys32_ustat; .quad sys32_ustat
	.reloc ., R_X86_64_SIZE32, sys32_ustat; .int 0
	.int 0x817ace4
	.quad .Lname3763 /* index: 3763 */
	.weak sys32_setgroups; .quad sys32_setgroups
	.reloc ., R_X86_64_SIZE32, sys32_setgroups; .int 0
	.int 0xc817eb3
	.quad .Lname3764 /* index: 3764 */
	.weak pidns_end; .quad pidns_end
	.reloc ., R_X86_64_SIZE32, pidns_end; .int 0
	.int 0xb592eb4
	.quad .Lname3765 /* index: 3765 */
	.weak pidns_upgrade; .quad pidns_upgrade
	.reloc ., R_X86_64_SIZE32, pidns_upgrade; .int 0
	.int 0xa95deb5
	.quad 0 /* index: 3766 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3767 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3768 /* index: 3768 */
	.weak vm_do_allocram_nx; .quad vm_do_allocram_nx
	.reloc ., R_X86_64_SIZE32, vm_do_allocram_nx; .int 0
	.int 0xfad1eb8
	.quad .Lname3769 /* index: 3769 */
	.weak thiscpu_quantum_offset; .quad thiscpu_quantum_offset
	.reloc ., R_X86_64_SIZE32, thiscpu_quantum_offset; .int 0
	.int 0x8b97a74
	.quad .Lname3770 /* index: 3770 */
	.weak unwind_fde_exec_cfa; .quad unwind_fde_exec_cfa
	.reloc ., R_X86_64_SIZE32, unwind_fde_exec_cfa; .int 0
	.int 0x72de8f1
	.quad 0 /* index: 3771 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3772 /* index: 3772 */
	.weak sighand_raise_signal; .quad sighand_raise_signal
	.reloc ., R_X86_64_SIZE32, sighand_raise_signal; .int 0
	.int 0xfc56ebc
	.quad 0 /* index: 3773 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3774 /* index: 3774 */
	.weak vm_sync; .quad vm_sync
	.reloc ., R_X86_64_SIZE32, vm_sync; .int 0
	.int 0xd36b033
	.quad .Lname3775 /* index: 3775 */
	.weak character_device_register_auto; .quad character_device_register_auto
	.reloc ., R_X86_64_SIZE32, character_device_register_auto; .int 0
	.int 0x4471ebf
	.quad .Lname3776 /* index: 3776 */
	.weak x86_dbg_getregbyidp; .quad x86_dbg_getregbyidp
	.reloc ., R_X86_64_SIZE32, x86_dbg_getregbyidp; .int 0
	.int 0x3386ec0
	.quad 0 /* index: 3777 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3778 /* index: 3778 */
	.weak vmb_alloc_peb; .quad vmb_alloc_peb
	.reloc ., R_X86_64_SIZE32, vmb_alloc_peb; .int 0
	.int 0x613ec2
	.quad .Lname3779 /* index: 3779 */
	.weak aio_buffer_copytophys; .quad aio_buffer_copytophys
	.reloc ., R_X86_64_SIZE32, aio_buffer_copytophys; .int 0
	.int 0x9aa3ec3
	.quad .Lname3780 /* index: 3780 */
	.weak sig_altbroadcast; .quad sig_altbroadcast
	.reloc ., R_X86_64_SIZE32, sig_altbroadcast; .int 0
	.int 0xfeaec4
	.quad .Lname3781 /* index: 3781 */
	.weak driver_getfile; .quad driver_getfile
	.reloc ., R_X86_64_SIZE32, driver_getfile; .int 0
	.int 0x4c60ec5
	.quad 0 /* index: 3782 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3783 /* index: 3783 */
	.weak vm_kernel_treelock_endread; .quad vm_kernel_treelock_endread
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_endread; .int 0
	.int 0x9f88204
	.quad 0 /* index: 3784 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3785 /* index: 3785 */
	.weak unwind_setreg_xfpustate; .quad unwind_setreg_xfpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_xfpustate; .int 0
	.int 0xb8d04c5
	.quad .Lname3786 /* index: 3786 */
	.weak terminal_iwrite; .quad terminal_iwrite
	.reloc ., R_X86_64_SIZE32, terminal_iwrite; .int 0
	.int 0xd4ece45
	.quad .Lname3787 /* index: 3787 */
	.weak vm_datablock_haschanged; .quad vm_datablock_haschanged
	.reloc ., R_X86_64_SIZE32, vm_datablock_haschanged; .int 0
	.int 0xb096dd4
	.quad 0 /* index: 3788 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3789 /* index: 3789 */
	.weak sys32_fsetxattr; .quad sys32_fsetxattr
	.reloc ., R_X86_64_SIZE32, sys32_fsetxattr; .int 0
	.int 0xad6ad22
	.quad .Lname3790 /* index: 3790 */
	.weak mouse_device_motion; .quad mouse_device_motion
	.reloc ., R_X86_64_SIZE32, mouse_device_motion; .int 0
	.int 0xca6cece
	.quad .Lname3791 /* index: 3791 */
	.weak this_exception_flags; .quad this_exception_flags
	.reloc ., R_X86_64_SIZE32, this_exception_flags; .int 0
	.int 0x693d2c3
	.quad .Lname3792 /* index: 3792 */
	.weak x86_asm_except_personality; .quad x86_asm_except_personality
	.reloc ., R_X86_64_SIZE32, x86_asm_except_personality; .int 0
	.int 0xe2c0ae9
	.quad 0 /* index: 3793 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3794 /* index: 3794 */
	.weak cpu_vector; .quad cpu_vector
	.reloc ., R_X86_64_SIZE32, cpu_vector; .int 0
	.int 0x6cd0ed2
	.quad .Lname3795 /* index: 3795 */
	.weak dbg_enter_fcpustate_c; .quad dbg_enter_fcpustate_c
	.reloc ., R_X86_64_SIZE32, dbg_enter_fcpustate_c; .int 0
	.int 0x1a83ed3
	.quad .Lname3796 /* index: 3796 */
	.weak inode_aread; .quad inode_aread
	.reloc ., R_X86_64_SIZE32, inode_aread; .int 0
	.int 0xb28ded4
	.quad .Lname3797 /* index: 3797 */
	.weak path_rename; .quad path_rename
	.reloc ., R_X86_64_SIZE32, path_rename; .int 0
	.int 0x6feced5
	.quad .Lname3798 /* index: 3798 */
	.weak vm_read_nopf; .quad vm_read_nopf
	.reloc ., R_X86_64_SIZE32, vm_read_nopf; .int 0
	.int 0x573ed6
	.quad .Lname3799 /* index: 3799 */
	.weak sys_request_key; .quad sys_request_key
	.reloc ., R_X86_64_SIZE32, sys_request_key; .int 0
	.int 0x5c2f279
	.quad .Lname3800 /* index: 3800 */
	.weak path_lock_write_nx; .quad path_lock_write_nx
	.reloc ., R_X86_64_SIZE32, path_lock_write_nx; .int 0
	.int 0xf382ed8
	.quad .Lname3801 /* index: 3801 */
	.weak json_parser_enterarray; .quad json_parser_enterarray
	.reloc ., R_X86_64_SIZE32, json_parser_enterarray; .int 0
	.int 0x4acaed9
	.quad .Lname3802 /* index: 3802 */
	.weak vm_node_insert; .quad vm_node_insert
	.reloc ., R_X86_64_SIZE32, vm_node_insert; .int 0
	.int 0x6a0c114
	.quad 0 /* index: 3803 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3804 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3805 /* index: 3805 */
	.weak sys_lseek64; .quad sys_lseek64
	.reloc ., R_X86_64_SIZE32, sys_lseek64; .int 0
	.int 0x3e0b7f4
	.quad 0 /* index: 3806 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3807 /* index: 3807 */
	.weak block_device_write; .quad block_device_write
	.reloc ., R_X86_64_SIZE32, block_device_write; .int 0
	.int 0xa512525
	.quad 0 /* index: 3808 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3809 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3810 /* index: 3810 */
	.weak dbg_enter_fcpustate_r; .quad dbg_enter_fcpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_fcpustate_r; .int 0
	.int 0x1a83ee2
	.quad .Lname3811 /* index: 3811 */
	.weak vm_copyfromphys; .quad vm_copyfromphys
	.reloc ., R_X86_64_SIZE32, vm_copyfromphys; .int 0
	.int 0xf026ee3
	.quad .Lname3812 /* index: 3812 */
	.weak block_device_autopart; .quad block_device_autopart
	.reloc ., R_X86_64_SIZE32, block_device_autopart; .int 0
	.int 0x60ecee4
	.quad .Lname3813 /* index: 3813 */
	.weak vm_kernel_treelock_upgrade; .quad vm_kernel_treelock_upgrade
	.reloc ., R_X86_64_SIZE32, vm_kernel_treelock_upgrade; .int 0
	.int 0xfdd8ee5
	.quad .Lname3814 /* index: 3814 */
	.weak sys32_io_destroy; .quad sys32_io_destroy
	.reloc ., R_X86_64_SIZE32, sys32_io_destroy; .int 0
	.int 0xc48ee59
	.quad 0 /* index: 3815 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3816 /* index: 3816 */
	.weak sys32_munmap; .quad sys32_munmap
	.reloc ., R_X86_64_SIZE32, sys32_munmap; .int 0
	.int 0x3fc3500
	.quad .Lname3817 /* index: 3817 */
	.weak sys32_profil; .quad sys32_profil
	.reloc ., R_X86_64_SIZE32, sys32_profil; .int 0
	.int 0x1c93a7c
	.quad .Lname3818 /* index: 3818 */
	.weak unicode_writeutf16; .quad unicode_writeutf16
	.reloc ., R_X86_64_SIZE32, unicode_writeutf16; .int 0
	.int 0x7beba16
	.quad .Lname3819 /* index: 3819 */
	.weak linebuffer_write_nonblock; .quad linebuffer_write_nonblock
	.reloc ., R_X86_64_SIZE32, linebuffer_write_nonblock; .int 0
	.int 0xe8bbeeb
	.quad 0 /* index: 3820 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3821 /* index: 3821 */
	.weak sys32_alarm; .quad sys32_alarm
	.reloc ., R_X86_64_SIZE32, sys32_alarm; .int 0
	.int 0x82d2eed
	.quad .Lname3822 /* index: 3822 */
	.weak driver_getshdrs; .quad driver_getshdrs
	.reloc ., R_X86_64_SIZE32, driver_getshdrs; .int 0
	.int 0xc75c5d3
	.quad 0 /* index: 3823 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3824 /* index: 3824 */
	.weak pagedir_unwriteone_p; .quad pagedir_unwriteone_p
	.reloc ., R_X86_64_SIZE32, pagedir_unwriteone_p; .int 0
	.int 0xbdc2b40
	.quad .Lname3825 /* index: 3825 */
	.weak task_raisesignalprocessgroup_nx; .quad task_raisesignalprocessgroup_nx
	.reloc ., R_X86_64_SIZE32, task_raisesignalprocessgroup_nx; .int 0
	.int 0xa352528
	.quad 0 /* index: 3826 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3827 /* index: 3827 */
	.weak sys32_io_getevents; .quad sys32_io_getevents
	.reloc ., R_X86_64_SIZE32, sys32_io_getevents; .int 0
	.int 0x8999ef3
	.quad .Lname3828 /* index: 3828 */
	.weak block_device_aread; .quad block_device_aread
	.reloc ., R_X86_64_SIZE32, block_device_aread; .int 0
	.int 0xa671ef4
	.quad .Lname3829 /* index: 3829 */
	.weak kernel_debugtrap_icpustate; .quad kernel_debugtrap_icpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_icpustate; .int 0
	.int 0x9638ef5
	.quad 0 /* index: 3830 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3831 /* index: 3831 */
	.weak task_pushconnections; .quad task_pushconnections
	.reloc ., R_X86_64_SIZE32, task_pushconnections; .int 0
	.int 0xae3c173
	.quad 0 /* index: 3832 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3833 /* index: 3833 */
	.weak dbg_enter_icpustate_r; .quad dbg_enter_icpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_icpustate_r; .int 0
	.int 0x1ab3ee2
	.quad 0 /* index: 3834 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3835 /* index: 3835 */
	.weak sys32_umask; .quad sys32_umask
	.reloc ., R_X86_64_SIZE32, sys32_umask; .int 0
	.int 0x8113efb
	.quad .Lname3836 /* index: 3836 */
	.weak dbg_scroll; .quad dbg_scroll
	.reloc ., R_X86_64_SIZE32, dbg_scroll; .int 0
	.int 0x69c3efc
	.quad 0 /* index: 3837 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3838 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3839 /* index: 3839 */
	.weak sys_pipe; .quad sys_pipe
	.reloc ., R_X86_64_SIZE32, sys_pipe; .int 0
	.int 0x9677d5
	.quad .Lname3840 /* index: 3840 */
	.weak memmoveup; .quad memmoveup
	.reloc ., R_X86_64_SIZE32, memmoveup; .int 0
	.int 0x446bf00
	.quad .Lname3841 /* index: 3841 */
	.weak mempmoveq; .quad mempmoveq
	.reloc ., R_X86_64_SIZE32, mempmoveq; .int 0
	.int 0x4741f01
	.quad .Lname3842 /* index: 3842 */
	.weak sys_mq_getsetattr; .quad sys_mq_getsetattr
	.reloc ., R_X86_64_SIZE32, sys_mq_getsetattr; .int 0
	.int 0xde45e62
	.quad 0 /* index: 3843 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3844 /* index: 3844 */
	.weak error_throw_current; .quad error_throw_current
	.reloc ., R_X86_64_SIZE32, error_throw_current; .int 0
	.int 0xcab8f04
	.quad .Lname3845 /* index: 3845 */
	.weak sys32_sendfile; .quad sys32_sendfile
	.reloc ., R_X86_64_SIZE32, sys32_sendfile; .int 0
	.int 0xc2c4f05
	.quad 0 /* index: 3846 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3847 /* index: 3847 */
	.weak mempmovew; .quad mempmovew
	.reloc ., R_X86_64_SIZE32, mempmovew; .int 0
	.int 0x4741f07
	.quad 0 /* index: 3848 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3849 /* index: 3849 */
	.weak callback_list_empty; .quad callback_list_empty
	.reloc ., R_X86_64_SIZE32, callback_list_empty; .int 0
	.int 0x9cd5f09
	.quad .Lname3850 /* index: 3850 */
	.weak unwind_setreg_lcpustate; .quad unwind_setreg_lcpustate
	.reloc ., R_X86_64_SIZE32, unwind_setreg_lcpustate; .int 0
	.int 0xb8d08b5
	.quad 0 /* index: 3851 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3852 /* index: 3852 */
	.weak inode_ioctl; .quad inode_ioctl
	.reloc ., R_X86_64_SIZE32, inode_ioctl; .int 0
	.int 0xb300f0c
	.quad .Lname3853 /* index: 3853 */
	.weak sys32_getresuid32; .quad sys32_getresuid32
	.reloc ., R_X86_64_SIZE32, sys32_getresuid32; .int 0
	.int 0x48d3a82
	.quad .Lname3854 /* index: 3854 */
	.weak sys_kfstat; .quad sys_kfstat
	.reloc ., R_X86_64_SIZE32, sys_kfstat; .int 0
	.int 0x61a1a14
	.quad 0 /* index: 3855 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3856 /* index: 3856 */
	.weak pagedir_map_p; .quad pagedir_map_p
	.reloc ., R_X86_64_SIZE32, pagedir_map_p; .int 0
	.int 0x23e3f10
	.quad .Lname3857 /* index: 3857 */
	.weak kmemalign_nx; .quad kmemalign_nx
	.reloc ., R_X86_64_SIZE32, kmemalign_nx; .int 0
	.int 0x5e007d8
	.quad .Lname3858 /* index: 3858 */
	.weak mouse_device_button_ex_nopr; .quad mouse_device_button_ex_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_button_ex_nopr; .int 0
	.int 0x1daf12
	.quad .Lname3859 /* index: 3859 */
	.weak debuginfo_enum_locals; .quad debuginfo_enum_locals
	.reloc ., R_X86_64_SIZE32, debuginfo_enum_locals; .int 0
	.int 0xcd26283
	.quad .Lname3860 /* index: 3860 */
	.weak vio_writew_aligned; .quad vio_writew_aligned
	.reloc ., R_X86_64_SIZE32, vio_writew_aligned; .int 0
	.int 0x8f55f14
	.quad .Lname3861 /* index: 3861 */
	.weak cpu_apply_icpustate; .quad cpu_apply_icpustate
	.reloc ., R_X86_64_SIZE32, cpu_apply_icpustate; .int 0
	.int 0xa8caf15
	.quad .Lname3862 /* index: 3862 */
	.weak block_device_areadv; .quad block_device_areadv
	.reloc ., R_X86_64_SIZE32, block_device_areadv; .int 0
	.int 0x671ef16
	.quad .Lname3863 /* index: 3863 */
	.weak debuginfo_cu_parser_nextsibling; .quad debuginfo_cu_parser_nextsibling
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_nextsibling; .int 0
	.int 0x93b9f17
	.quad .Lname3864 /* index: 3864 */
	.weak json_parser_findindex; .quad json_parser_findindex
	.reloc ., R_X86_64_SIZE32, json_parser_findindex; .int 0
	.int 0xb2e0f18
	.quad .Lname3865 /* index: 3865 */
	.weak __mempcpy; .quad __mempcpy
	.reloc ., R_X86_64_SIZE32, __mempcpy; .int 0
	.int 0x3c40f19
	.quad .Lname3866 /* index: 3866 */
	.weak vm86_inl; .quad vm86_inl
	.reloc ., R_X86_64_SIZE32, vm86_inl; .int 0
	.int 0xbc599c
	.quad 0 /* index: 3867 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3868 /* index: 3868 */
	.weak task_destroy; .quad task_destroy
	.reloc ., R_X86_64_SIZE32, task_destroy; .int 0
	.int 0xd621a39
	.quad .Lname3869 /* index: 3869 */
	.weak vm86_exec; .quad vm86_exec
	.reloc ., R_X86_64_SIZE32, vm86_exec; .int 0
	.int 0xbc5b3b3
	.quad .Lname3870 /* index: 3870 */
	.weak superblock_open; .quad superblock_open
	.reloc ., R_X86_64_SIZE32, superblock_open; .int 0
	.int 0xdd6f1e
	.quad .Lname3871 /* index: 3871 */
	.weak kernel_syscall0_restartmode; .quad kernel_syscall0_restartmode
	.reloc ., R_X86_64_SIZE32, kernel_syscall0_restartmode; .int 0
	.int 0x528fa85
	.quad 0 /* index: 3872 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3873 /* index: 3873 */
	.weak sys_linux_fstat64; .quad sys_linux_fstat64
	.reloc ., R_X86_64_SIZE32, sys_linux_fstat64; .int 0
	.int 0xf3442a4
	.quad 0 /* index: 3874 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3875 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3876 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3877 /* index: 3877 */
	.weak dbg_beginupdate; .quad dbg_beginupdate
	.reloc ., R_X86_64_SIZE32, dbg_beginupdate; .int 0
	.int 0x89e7f25
	.quad .Lname3878 /* index: 3878 */
	.weak vm_datablock_anonymous; .quad vm_datablock_anonymous
	.reloc ., R_X86_64_SIZE32, vm_datablock_anonymous; .int 0
	.int 0xb72da13
	.quad .Lname3879 /* index: 3879 */
	.weak inode_read_phys_blocking; .quad inode_read_phys_blocking
	.reloc ., R_X86_64_SIZE32, inode_read_phys_blocking; .int 0
	.int 0x6d8af27
	.quad .Lname3880 /* index: 3880 */
	.weak x86_sysroute0_c32; .quad x86_sysroute0_c32
	.reloc ., R_X86_64_SIZE32, x86_sysroute0_c32; .int 0
	.int 0x1f51cc2
	.quad .Lname3881 /* index: 3881 */
	.weak cpu_do_assert_integrity; .quad cpu_do_assert_integrity
	.reloc ., R_X86_64_SIZE32, cpu_do_assert_integrity; .int 0
	.int 0xd193f29
	.quad 0 /* index: 3882 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3883 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3884 /* index: 3884 */
	.weak sys_ppoll; .quad sys_ppoll
	.reloc ., R_X86_64_SIZE32, sys_ppoll; .int 0
	.int 0x9672f2c
	.quad .Lname3885 /* index: 3885 */
	.weak tty_device_forward_destroy; .quad tty_device_forward_destroy
	.reloc ., R_X86_64_SIZE32, tty_device_forward_destroy; .int 0
	.int 0x762cb29
	.quad .Lname3886 /* index: 3886 */
	.weak unwind_fde_sigframe_exec; .quad unwind_fde_sigframe_exec
	.reloc ., R_X86_64_SIZE32, unwind_fde_sigframe_exec; .int 0
	.int 0x5d15dd3
	.quad .Lname3887 /* index: 3887 */
	.weak sys_recvfrom; .quad sys_recvfrom
	.reloc ., R_X86_64_SIZE32, sys_recvfrom; .int 0
	.int 0xc1c4fdd
	.quad 0 /* index: 3888 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3889 /* index: 3889 */
	.weak task_waitfor_norpc_nx; .quad task_waitfor_norpc_nx
	.reloc ., R_X86_64_SIZE32, task_waitfor_norpc_nx; .int 0
	.int 0x6767a88
	.quad .Lname3890 /* index: 3890 */
	.weak sys32_mq_getsetattr; .quad sys32_mq_getsetattr
	.reloc ., R_X86_64_SIZE32, sys32_mq_getsetattr; .int 0
	.int 0x6b93f32
	.quad .Lname3891 /* index: 3891 */
	.weak heap_realloc; .quad heap_realloc
	.reloc ., R_X86_64_SIZE32, heap_realloc; .int 0
	.int 0xe5db533
	.quad .Lname3892 /* index: 3892 */
	.weak strtou64; .quad strtou64
	.reloc ., R_X86_64_SIZE32, strtou64; .int 0
	.int 0xb9b6f34
	.quad .Lname3893 /* index: 3893 */
	.weak dbg_enter_ucpustate; .quad dbg_enter_ucpustate
	.reloc ., R_X86_64_SIZE32, dbg_enter_ucpustate; .int 0
	.int 0x7819f35
	.quad .Lname3894 /* index: 3894 */
	.weak dbg_menuf; .quad dbg_menuf
	.reloc ., R_X86_64_SIZE32, dbg_menuf; .int 0
	.int 0xd63ef36
	.quad .Lname3895 /* index: 3895 */
	.weak unwind_getreg_fcpustate; .quad unwind_getreg_fcpustate
	.reloc ., R_X86_64_SIZE32, unwind_getreg_fcpustate; .int 0
	.int 0xb8c76b5
	.quad 0 /* index: 3896 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3897 /* index: 3897 */
	.weak task_sigcont; .quad task_sigcont
	.reloc ., R_X86_64_SIZE32, task_sigcont; .int 0
	.int 0xe554534
	.quad .Lname3898 /* index: 3898 */
	.weak sys32_timerfd_gettime64; .quad sys32_timerfd_gettime64
	.reloc ., R_X86_64_SIZE32, sys32_timerfd_gettime64; .int 0
	.int 0xb7460f4
	.quad .Lname3899 /* index: 3899 */
	.weak syscall_trace; .quad syscall_trace
	.reloc ., R_X86_64_SIZE32, syscall_trace; .int 0
	.int 0xb621ff5
	.quad 0 /* index: 3900 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3901 /* index: 3901 */
	.weak sys_uname; .quad sys_uname
	.reloc ., R_X86_64_SIZE32, sys_uname; .int 0
	.int 0x96c3d35
	.quad .Lname3902 /* index: 3902 */
	.weak syscall_tracing_setenabled; .quad syscall_tracing_setenabled
	.reloc ., R_X86_64_SIZE32, syscall_tracing_setenabled; .int 0
	.int 0xab0f144
	.quad .Lname3903 /* index: 3903 */
	.weak format_quote; .quad format_quote
	.reloc ., R_X86_64_SIZE32, format_quote; .int 0
	.int 0xbe3535
	.quad 0 /* index: 3904 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3905 /* index: 3905 */
	.weak dbg_setscreendata; .quad dbg_setscreendata
	.reloc ., R_X86_64_SIZE32, dbg_setscreendata; .int 0
	.int 0x225bf41
	.quad .Lname3906 /* index: 3906 */
	.weak sys_fremovexattr; .quad sys_fremovexattr
	.reloc ., R_X86_64_SIZE32, sys_fremovexattr; .int 0
	.int 0x9119f42
	.quad 0 /* index: 3907 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3908 /* index: 3908 */
	.weak sys32_capset; .quad sys32_capset
	.reloc ., R_X86_64_SIZE32, sys32_capset; .int 0
	.int 0x2281f44
	.quad .Lname3909 /* index: 3909 */
	.weak directory_rename; .quad directory_rename
	.reloc ., R_X86_64_SIZE32, directory_rename; .int 0
	.int 0xd279f45
	.quad .Lname3910 /* index: 3910 */
	.weak format_vscanf; .quad format_vscanf
	.reloc ., R_X86_64_SIZE32, format_vscanf; .int 0
	.int 0xbb0af46
	.quad 0 /* index: 3911 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3912 /* index: 3912 */
	.weak sprintf; .quad sprintf
	.reloc ., R_X86_64_SIZE32, sprintf; .int 0
	.int 0xa7905d6
	.quad 0 /* index: 3913 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3914 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3915 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3916 /* index: 3916 */
	.weak sys_tuxcall; .quad sys_tuxcall
	.reloc ., R_X86_64_SIZE32, sys_tuxcall; .int 0
	.int 0xbb59f4c
	.quad .Lname3917 /* index: 3917 */
	.weak x86_syscall_emulate_int80h_r; .quad x86_syscall_emulate_int80h_r
	.reloc ., R_X86_64_SIZE32, x86_syscall_emulate_int80h_r; .int 0
	.int 0x2437fe2
	.quad 0 /* index: 3918 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3919 /* index: 3919 */
	.weak vio_orw; .quad vio_orw
	.reloc ., R_X86_64_SIZE32, vio_orw; .int 0
	.int 0xd0566e7
	.quad .Lname3920 /* index: 3920 */
	.weak kernel_default_heap; .quad kernel_default_heap
	.reloc ., R_X86_64_SIZE32, kernel_default_heap; .int 0
	.int 0x8076f50
	.quad 0 /* index: 3921 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3922 /* index: 3922 */
	.weak cpu_quantum_elapsed_nopr; .quad cpu_quantum_elapsed_nopr
	.reloc ., R_X86_64_SIZE32, cpu_quantum_elapsed_nopr; .int 0
	.int 0x406df52
	.quad .Lname3923 /* index: 3923 */
	.weak block_device_delparts; .quad block_device_delparts
	.reloc ., R_X86_64_SIZE32, block_device_delparts; .int 0
	.int 0x36e2fe3
	.quad .Lname3924 /* index: 3924 */
	.weak block_device_makepart; .quad block_device_makepart
	.reloc ., R_X86_64_SIZE32, block_device_makepart; .int 0
	.int 0xf44cf54
	.quad .Lname3925 /* index: 3925 */
	.weak devfs_lock_trywrite; .quad devfs_lock_trywrite
	.reloc ., R_X86_64_SIZE32, devfs_lock_trywrite; .int 0
	.int 0x1987f55
	.quad 0 /* index: 3926 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3927 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3928 /* index: 3928 */
	.weak ioperm_bitmap_copyf_nx; .quad ioperm_bitmap_copyf_nx
	.reloc ., R_X86_64_SIZE32, ioperm_bitmap_copyf_nx; .int 0
	.int 0x1d1bf58
	.quad .Lname3929 /* index: 3929 */
	.weak character_device_pread; .quad character_device_pread
	.reloc ., R_X86_64_SIZE32, character_device_pread; .int 0
	.int 0x8b777e4
	.quad 0 /* index: 3930 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3931 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3932 /* index: 3932 */
	.weak vio_cmpxch_or_writel; .quad vio_cmpxch_or_writel
	.reloc ., R_X86_64_SIZE32, vio_cmpxch_or_writel; .int 0
	.int 0x8230f5c
	.quad .Lname3933 /* index: 3933 */
	.weak pmembank_type_names; .quad pmembank_type_names
	.reloc ., R_X86_64_SIZE32, pmembank_type_names; .int 0
	.int 0xf2efbb3
	.quad 0 /* index: 3934 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3935 /* index: 3935 */
	.weak vm_tasklock_downgrade; .quad vm_tasklock_downgrade
	.reloc ., R_X86_64_SIZE32, vm_tasklock_downgrade; .int 0
	.int 0xf072fe5
	.quad .Lname3936 /* index: 3936 */
	.weak sys_setrlimit; .quad sys_setrlimit
	.reloc ., R_X86_64_SIZE32, sys_setrlimit; .int 0
	.int 0x9babb4
	.quad .Lname3937 /* index: 3937 */
	.weak vmb_find_last_node_lower_equal; .quad vmb_find_last_node_lower_equal
	.reloc ., R_X86_64_SIZE32, vmb_find_last_node_lower_equal; .int 0
	.int 0xe02545c
	.quad .Lname3938 /* index: 3938 */
	.weak isr_vector_trigger; .quad isr_vector_trigger
	.reloc ., R_X86_64_SIZE32, isr_vector_trigger; .int 0
	.int 0x72e3f62
	.quad .Lname3939 /* index: 3939 */
	.weak inode_areadall_phys; .quad inode_areadall_phys
	.reloc ., R_X86_64_SIZE32, inode_areadall_phys; .int 0
	.int 0xbd8bf63
	.quad .Lname3940 /* index: 3940 */
	.weak dbg_isholding_shift; .quad dbg_isholding_shift
	.reloc ., R_X86_64_SIZE32, dbg_isholding_shift; .int 0
	.int 0xa863f64
	.quad .Lname3941 /* index: 3941 */
	.weak driver_finalize; .quad driver_finalize
	.reloc ., R_X86_64_SIZE32, driver_finalize; .int 0
	.int 0x8c1f65
	.quad .Lname3942 /* index: 3942 */
	.weak sys_poll; .quad sys_poll
	.reloc ., R_X86_64_SIZE32, sys_poll; .int 0
	.int 0x96739c
	.quad 0 /* index: 3943 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3944 /* index: 3944 */
	.weak task_setpid; .quad task_setpid
	.reloc ., R_X86_64_SIZE32, task_setpid; .int 0
	.int 0x6e63ce4
	.quad .Lname3945 /* index: 3945 */
	.weak inode_readall; .quad inode_readall
	.reloc ., R_X86_64_SIZE32, inode_readall; .int 0
	.int 0x8e20d3c
	.quad .Lname3946 /* index: 3946 */
	.weak path_lock_endread; .quad path_lock_endread
	.reloc ., R_X86_64_SIZE32, path_lock_endread; .int 0
	.int 0xe28a0c4
	.quad .Lname3947 /* index: 3947 */
	.weak vm_tasklock_read; .quad vm_tasklock_read
	.reloc ., R_X86_64_SIZE32, vm_tasklock_read; .int 0
	.int 0x4995944
	.quad 0 /* index: 3948 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3949 /* index: 3949 */
	.weak sys32_kreaddir; .quad sys32_kreaddir
	.reloc ., R_X86_64_SIZE32, sys32_kreaddir; .int 0
	.int 0x8d12a92
	.quad .Lname3950 /* index: 3950 */
	.weak sys32_mktty; .quad sys32_mktty
	.reloc ., R_X86_64_SIZE32, sys32_mktty; .int 0
	.int 0x8392dd9
	.quad 0 /* index: 3951 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3952 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3953 /* index: 3953 */
	.weak dbg_getscreendata; .quad dbg_getscreendata
	.reloc ., R_X86_64_SIZE32, dbg_getscreendata; .int 0
	.int 0x625bf71
	.quad .Lname3954 /* index: 3954 */
	.weak dbg_evaladdr; .quad dbg_evaladdr
	.reloc ., R_X86_64_SIZE32, dbg_evaladdr; .int 0
	.int 0xaeaaf72
	.quad .Lname3955 /* index: 3955 */
	.weak pidns_alloc; .quad pidns_alloc
	.reloc ., R_X86_64_SIZE32, pidns_alloc; .int 0
	.int 0x922ea03
	.quad .Lname3956 /* index: 3956 */
	.weak sys32_getsid; .quad sys32_getsid
	.reloc ., R_X86_64_SIZE32, sys32_getsid; .int 0
	.int 0x26cdf74
	.quad .Lname3957 /* index: 3957 */
	.weak x86_dbg_trapstate; .quad x86_dbg_trapstate
	.reloc ., R_X86_64_SIZE32, x86_dbg_trapstate; .int 0
	.int 0x2827f75
	.quad .Lname3958 /* index: 3958 */
	.weak sys32_set_library_listdef; .quad sys32_set_library_listdef
	.reloc ., R_X86_64_SIZE32, sys32_set_library_listdef; .int 0
	.int 0xa527f76
	.quad 0 /* index: 3959 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3960 /* index: 3960 */
	.weak sys32_mpx; .quad sys32_mpx
	.reloc ., R_X86_64_SIZE32, sys32_mpx; .int 0
	.int 0x6683f78
	.quad .Lname3961 /* index: 3961 */
	.weak handle_installat; .quad handle_installat
	.reloc ., R_X86_64_SIZE32, handle_installat; .int 0
	.int 0x18baa94
	.quad 0 /* index: 3962 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3963 /* index: 3963 */
	.weak sys32_readlink; .quad sys32_readlink
	.reloc ., R_X86_64_SIZE32, sys32_readlink; .int 0
	.int 0xb1daf7b
	.quad .Lname3964 /* index: 3964 */
	.weak mempmovel; .quad mempmovel
	.reloc ., R_X86_64_SIZE32, mempmovel; .int 0
	.int 0x4741f7c
	.quad 0 /* index: 3965 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3966 /* index: 3966 */
	.weak sys_shmat; .quad sys_shmat
	.reloc ., R_X86_64_SIZE32, sys_shmat; .int 0
	.int 0x969a884
	.quad .Lname3967 /* index: 3967 */
	.weak vfs_clone; .quad vfs_clone
	.reloc ., R_X86_64_SIZE32, vfs_clone; .int 0
	.int 0x95a6a95
	.quad 0 /* index: 3968 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3969 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3970 /* index: 3970 */
	.weak sys32_get_exception_handler; .quad sys32_get_exception_handler
	.reloc ., R_X86_64_SIZE32, sys32_get_exception_handler; .int 0
	.int 0x9f81f82
	.quad .Lname3971 /* index: 3971 */
	.weak system_clearcaches; .quad system_clearcaches
	.reloc ., R_X86_64_SIZE32, system_clearcaches; .int 0
	.int 0xe7d1f83
	.quad .Lname3972 /* index: 3972 */
	.weak dbg_getfunc_start; .quad dbg_getfunc_start
	.reloc ., R_X86_64_SIZE32, dbg_getfunc_start; .int 0
	.int 0x6caff84
	.quad .Lname3973 /* index: 3973 */
	.weak dbg_enter_here; .quad dbg_enter_here
	.reloc ., R_X86_64_SIZE32, dbg_enter_here; .int 0
	.int 0x4b02f85
	.quad 0 /* index: 3974 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3975 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3976 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3977 /* index: 3977 */
	.weak sys32_openpty; .quad sys32_openpty
	.reloc ., R_X86_64_SIZE32, sys32_openpty; .int 0
	.int 0xd6e3f89
	.quad 0 /* index: 3978 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3979 /* index: 3979 */
	.weak vio_writew; .quad vio_writew
	.reloc ., R_X86_64_SIZE32, vio_writew; .int 0
	.int 0x6f0da97
	.quad .Lname3980 /* index: 3980 */
	.weak sys_setpgid; .quad sys_setpgid
	.reloc ., R_X86_64_SIZE32, sys_setpgid; .int 0
	.int 0x9b06494
	.quad .Lname3981 /* index: 3981 */
	.weak debuginfo_cu_parser_skipform; .quad debuginfo_cu_parser_skipform
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_skipform; .int 0
	.int 0x7e8df8d
	.quad .Lname3982 /* index: 3982 */
	.weak dbg_endshowscreen; .quad dbg_endshowscreen
	.reloc ., R_X86_64_SIZE32, dbg_endshowscreen; .int 0
	.int 0x2bb9f8e
	.quad 0 /* index: 3983 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3984 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3985 /* index: 3985 */
	.weak sys_rt_sigaction; .quad sys_rt_sigaction
	.reloc ., R_X86_64_SIZE32, sys_rt_sigaction; .int 0
	.int 0xbe5773e
	.quad 0 /* index: 3986 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3987 /* index: 3987 */
	.weak sys_fsync; .quad sys_fsync
	.reloc ., R_X86_64_SIZE32, sys_fsync; .int 0
	.int 0x95dd543
	.quad .Lname3988 /* index: 3988 */
	.weak page_malloc_part; .quad page_malloc_part
	.reloc ., R_X86_64_SIZE32, page_malloc_part; .int 0
	.int 0xef24f94
	.quad .Lname3989 /* index: 3989 */
	.weak dbg_newline_mode; .quad dbg_newline_mode
	.reloc ., R_X86_64_SIZE32, dbg_newline_mode; .int 0
	.int 0x300cf95
	.quad 0 /* index: 3990 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3991 /* index: 3991 */
	.weak json_parser_printstring; .quad json_parser_printstring
	.reloc ., R_X86_64_SIZE32, json_parser_printstring; .int 0
	.int 0x9d53f97
	.quad .Lname3992 /* index: 3992 */
	.weak x86_idt_modify_begin; .quad x86_idt_modify_begin
	.reloc ., R_X86_64_SIZE32, x86_idt_modify_begin; .int 0
	.int 0xf58ee6e
	.quad .Lname3993 /* index: 3993 */
	.weak setreg_icpustate; .quad setreg_icpustate
	.reloc ., R_X86_64_SIZE32, setreg_icpustate; .int 0
	.int 0xf766bb5
	.quad 0 /* index: 3994 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3995 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3996 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 3997 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname3998 /* index: 3998 */
	.weak sys32_setitimer64; .quad sys32_setitimer64
	.reloc ., R_X86_64_SIZE32, sys32_setitimer64; .int 0
	.int 0x2f108f4
	.quad .Lname3999 /* index: 3999 */
	.weak fpustate_saveinto; .quad fpustate_saveinto
	.reloc ., R_X86_64_SIZE32, fpustate_saveinto; .int 0
	.int 0x22c2f9f
	.quad .Lname4000 /* index: 4000 */
	.weak pidns_trylookup; .quad pidns_trylookup
	.reloc ., R_X86_64_SIZE32, pidns_trylookup; .int 0
	.int 0x58d5fa0
	.quad .Lname4001 /* index: 4001 */
	.weak vm_readphysq_unaligned; .quad vm_readphysq_unaligned
	.reloc ., R_X86_64_SIZE32, vm_readphysq_unaligned; .int 0
	.int 0x38eb44
	.quad .Lname4002 /* index: 4002 */
	.weak mouse_device_vwheel_nopr; .quad mouse_device_vwheel_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_vwheel_nopr; .int 0
	.int 0x3a3aee2
	.quad .Lname4003 /* index: 4003 */
	.weak block_device_readv_phys_sync; .quad block_device_readv_phys_sync
	.reloc ., R_X86_64_SIZE32, block_device_readv_phys_sync; .int 0
	.int 0x2c49fa3
	.quad .Lname4004 /* index: 4004 */
	.weak sys32_ugetrlimit; .quad sys32_ugetrlimit
	.reloc ., R_X86_64_SIZE32, sys32_ugetrlimit; .int 0
	.int 0xd140fa4
	.quad .Lname4005 /* index: 4005 */
	.weak kernel_debugtrap_r_scpustate; .quad kernel_debugtrap_r_scpustate
	.reloc ., R_X86_64_SIZE32, kernel_debugtrap_r_scpustate; .int 0
	.int 0xed53fa5
	.quad 0 /* index: 4006 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4007 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4008 /* index: 4008 */
	.weak vm_datapart_split_nx; .quad vm_datapart_split_nx
	.reloc ., R_X86_64_SIZE32, vm_datapart_split_nx; .int 0
	.int 0x503cfa8
	.quad 0 /* index: 4009 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4010 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4011 /* index: 4011 */
	.weak vm_onfini_callbacks; .quad vm_onfini_callbacks
	.reloc ., R_X86_64_SIZE32, vm_onfini_callbacks; .int 0
	.int 0x25145f3
	.quad 0 /* index: 4012 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4013 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4014 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4015 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4016 /* index: 4016 */
	.weak regdump_gpregs; .quad regdump_gpregs
	.reloc ., R_X86_64_SIZE32, regdump_gpregs; .int 0
	.int 0xe3c4803
	.quad .Lname4017 /* index: 4017 */
	.weak task_raisesignalprocess_nx; .quad task_raisesignalprocess_nx
	.reloc ., R_X86_64_SIZE32, task_raisesignalprocess_nx; .int 0
	.int 0x5941d48
	.quad .Lname4018 /* index: 4018 */
	.weak block_device_register; .quad block_device_register
	.reloc ., R_X86_64_SIZE32, block_device_register; .int 0
	.int 0x2980fb2
	.quad .Lname4019 /* index: 4019 */
	.weak jiffies; .quad jiffies
	.reloc ., R_X86_64_SIZE32, jiffies; .int 0
	.int 0xfccfb3
	.quad .Lname4020 /* index: 4020 */
	.weak sys32_get_robust_list; .quad sys32_get_robust_list
	.reloc ., R_X86_64_SIZE32, sys32_get_robust_list; .int 0
	.int 0xaa56fb4
	.quad .Lname4021 /* index: 4021 */
	.weak directory_remove; .quad directory_remove
	.reloc ., R_X86_64_SIZE32, directory_remove; .int 0
	.int 0xd27ffb5
	.quad .Lname4022 /* index: 4022 */
	.weak vm_getnodeof; .quad vm_getnodeof
	.reloc ., R_X86_64_SIZE32, vm_getnodeof; .int 0
	.int 0xea6f796
	.quad .Lname4023 /* index: 4023 */
	.weak sys_getpid; .quad sys_getpid
	.reloc ., R_X86_64_SIZE32, sys_getpid; .int 0
	.int 0x5db0664
	.quad 0 /* index: 4024 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4025 /* index: 4025 */
	.weak sys32_setfsgid; .quad sys32_setfsgid
	.reloc ., R_X86_64_SIZE32, sys32_setfsgid; .int 0
	.int 0xccb1cd4
	.quad .Lname4026 /* index: 4026 */
	.weak vm_datablock_lock_trywrite_parts; .quad vm_datablock_lock_trywrite_parts
	.reloc ., R_X86_64_SIZE32, vm_datablock_lock_trywrite_parts; .int 0
	.int 0xebf40a3
	.quad 0 /* index: 4027 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4028 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4029 /* index: 4029 */
	.weak sys32_kstat; .quad sys32_kstat
	.reloc ., R_X86_64_SIZE32, sys32_kstat; .int 0
	.int 0x839ace4
	.quad .Lname4030 /* index: 4030 */
	.weak vpage_free_untraced; .quad vpage_free_untraced
	.reloc ., R_X86_64_SIZE32, vpage_free_untraced; .int 0
	.int 0x554f414
	.quad .Lname4031 /* index: 4031 */
	.weak sys32_nice; .quad sys32_nice
	.reloc ., R_X86_64_SIZE32, sys32_nice; .int 0
	.int 0x683fff5
	.quad 0 /* index: 4032 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4033 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4034 /* index: 4034 */
	.weak debuginfo_cu_parser_getexpr; .quad debuginfo_cu_parser_getexpr
	.reloc ., R_X86_64_SIZE32, debuginfo_cu_parser_getexpr; .int 0
	.int 0xbb42fc2
	.quad .Lname4035 /* index: 4035 */
	.weak character_device_alloc; .quad character_device_alloc
	.reloc ., R_X86_64_SIZE32, character_device_alloc; .int 0
	.int 0x888efc3
	.quad .Lname4036 /* index: 4036 */
	.weak cred_require_driveroot; .quad cred_require_driveroot
	.reloc ., R_X86_64_SIZE32, cred_require_driveroot; .int 0
	.int 0xa29cfc4
	.quad .Lname4037 /* index: 4037 */
	.weak disasm_print_line; .quad disasm_print_line
	.reloc ., R_X86_64_SIZE32, disasm_print_line; .int 0
	.int 0xfd95fc5
	.quad 0 /* index: 4038 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4039 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4040 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4041 /* index: 4041 */
	.weak vm_sync_endall; .quad vm_sync_endall
	.reloc ., R_X86_64_SIZE32, vm_sync_endall; .int 0
	.int 0x6efa54c
	.quad 0 /* index: 4042 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4043 /* index: 4043 */
	.weak zlib_reader_read; .quad zlib_reader_read
	.reloc ., R_X86_64_SIZE32, zlib_reader_read; .int 0
	.int 0x4262e24
	.quad .Lname4044 /* index: 4044 */
	.weak this_sighand_ptr; .quad this_sighand_ptr
	.reloc ., R_X86_64_SIZE32, this_sighand_ptr; .int 0
	.int 0xf283552
	.quad .Lname4045 /* index: 4045 */
	.weak sys32_sched_setparam; .quad sys32_sched_setparam
	.reloc ., R_X86_64_SIZE32, sys32_sched_setparam; .int 0
	.int 0x53bafcd
	.quad 0 /* index: 4046 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4047 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4048 /* index: 4048 */
	.weak regdump_ip; .quad regdump_ip
	.reloc ., R_X86_64_SIZE32, regdump_ip; .int 0
	.int 0xbc3efd0
	.quad 0 /* index: 4049 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4050 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4051 /* index: 4051 */
	.weak vm_datapart_readv_phys; .quad vm_datapart_readv_phys
	.reloc ., R_X86_64_SIZE32, vm_datapart_readv_phys; .int 0
	.int 0x8adb2a3
	.quad .Lname4052 /* index: 4052 */
	.weak inode_stat; .quad inode_stat
	.reloc ., R_X86_64_SIZE32, inode_stat; .int 0
	.int 0xab1afd4
	.quad .Lname4053 /* index: 4053 */
	.weak inode_changed_chmtime; .quad inode_changed_chmtime
	.reloc ., R_X86_64_SIZE32, inode_changed_chmtime; .int 0
	.int 0xa123fd5
	.quad .Lname4054 /* index: 4054 */
	.weak sys_pread64f; .quad sys_pread64f
	.reloc ., R_X86_64_SIZE32, sys_pread64f; .int 0
	.int 0xf07efd6
	.quad .Lname4055 /* index: 4055 */
	.weak thiscpu_pending; .quad thiscpu_pending
	.reloc ., R_X86_64_SIZE32, thiscpu_pending; .int 0
	.int 0x63eafd7
	.quad .Lname4056 /* index: 4056 */
	.weak krealign_nx; .quad krealign_nx
	.reloc ., R_X86_64_SIZE32, krealign_nx; .int 0
	.int 0x290cfd8
	.quad .Lname4057 /* index: 4057 */
	.weak sys32_modify_ldt; .quad sys32_modify_ldt
	.reloc ., R_X86_64_SIZE32, sys32_modify_ldt; .int 0
	.int 0x95ed774
	.quad 0 /* index: 4058 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4059 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4060 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4061 /* index: 4061 */
	.weak sys_nanosleep; .quad sys_nanosleep
	.reloc ., R_X86_64_SIZE32, sys_nanosleep; .int 0
	.int 0x614fe0
	.quad .Lname4062 /* index: 4062 */
	.weak sys_mq_open; .quad sys_mq_open
	.reloc ., R_X86_64_SIZE32, sys_mq_open; .int 0
	.int 0x42f6fde
	.quad .Lname4063 /* index: 4063 */
	.weak path_lock_downgrade; .quad path_lock_downgrade
	.reloc ., R_X86_64_SIZE32, path_lock_downgrade; .int 0
	.int 0xf653aa5
	.quad .Lname4064 /* index: 4064 */
	.weak sys_coredump; .quad sys_coredump
	.reloc ., R_X86_64_SIZE32, sys_coredump; .int 0
	.int 0x13b2fe0
	.quad .Lname4065 /* index: 4065 */
	.weak memchrq; .quad memchrq
	.reloc ., R_X86_64_SIZE32, memchrq; .int 0
	.int 0x3c39fe1
	.quad .Lname4066 /* index: 4066 */
	.weak keyboard_device_getchar; .quad keyboard_device_getchar
	.reloc ., R_X86_64_SIZE32, keyboard_device_getchar; .int 0
	.int 0x4fc6fe2
	.quad .Lname4067 /* index: 4067 */
	.weak block_device_aread_phys; .quad block_device_aread_phys
	.reloc ., R_X86_64_SIZE32, block_device_aread_phys; .int 0
	.int 0xf401fe3
	.quad .Lname4068 /* index: 4068 */
	.weak fpustate_init; .quad fpustate_init
	.reloc ., R_X86_64_SIZE32, fpustate_init; .int 0
	.int 0x7e96fe4
	.quad .Lname4069 /* index: 4069 */
	.weak sys_mincore; .quad sys_mincore
	.reloc ., R_X86_64_SIZE32, sys_mincore; .int 0
	.int 0x39fafe5
	.quad 0 /* index: 4070 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4071 /* index: 4071 */
	.weak memchrw; .quad memchrw
	.reloc ., R_X86_64_SIZE32, memchrw; .int 0
	.int 0x3c39fe7
	.quad 0 /* index: 4072 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4073 /* index: 4073 */
	.weak memchrl; .quad memchrl
	.reloc ., R_X86_64_SIZE32, memchrl; .int 0
	.int 0x3c39ffc
	.quad 0 /* index: 4074 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4075 /* index: 4075 */
	.weak vm_tasklock_tryread; .quad vm_tasklock_tryread
	.reloc ., R_X86_64_SIZE32, vm_tasklock_tryread; .int 0
	.int 0x6c3c2e4
	.quad 0 /* index: 4076 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4077 /* index: 4077 */
	.weak mouse_device_hwheel_nopr; .quad mouse_device_hwheel_nopr
	.reloc ., R_X86_64_SIZE32, mouse_device_hwheel_nopr; .int 0
	.int 0x3b1aee2
	.quad 0 /* index: 4078 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4079 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4080 /* index: 4080 */
	.weak sys_kcmp; .quad sys_kcmp
	.reloc ., R_X86_64_SIZE32, sys_kcmp; .int 0
	.int 0x961ff0
	.quad .Lname4081 /* index: 4081 */
	.weak sys32_clock_gettime64; .quad sys32_clock_gettime64
	.reloc ., R_X86_64_SIZE32, sys32_clock_gettime64; .int 0
	.int 0xfa74664
	.quad 0 /* index: 4082 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4083 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4084 /* index: 4084 */
	.weak vio_subl; .quad vio_subl
	.reloc ., R_X86_64_SIZE32, vio_subl; .int 0
	.int 0x56ac5c
	.quad .Lname4085 /* index: 4085 */
	.weak rwlock_trywrite; .quad rwlock_trywrite
	.reloc ., R_X86_64_SIZE32, rwlock_trywrite; .int 0
	.int 0xb541ff5
	.quad 0 /* index: 4086 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4087 /* index: 4087 */
	.weak vm_write; .quad vm_write
	.reloc ., R_X86_64_SIZE32, vm_write; .int 0
	.int 0x36e9775
	.quad .Lname4088 /* index: 4088 */
	.weak syscall_tracing_getenabled; .quad syscall_tracing_getenabled
	.reloc ., R_X86_64_SIZE32, syscall_tracing_getenabled; .int 0
	.int 0xab3b144
	.quad .Lname4089 /* index: 4089 */
	.weak sys_capget; .quad sys_capget
	.reloc ., R_X86_64_SIZE32, sys_capget; .int 0
	.int 0x59fdd54
	.quad 0 /* index: 4090 */
	.quad 0
	.int 0
	.int 0
	.quad 0 /* index: 4091 */
	.quad 0
	.int 0
	.int 0
	.quad .Lname4092 /* index: 4092 */
	.weak dbg_enter_ucpustate_r; .quad dbg_enter_ucpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_ucpustate_r; .int 0
	.int 0x19f3ee2
	.quad .Lname4093 /* index: 4093 */
	.weak thiscpu_id; .quad thiscpu_id
	.reloc ., R_X86_64_SIZE32, thiscpu_id; .int 0
	.int 0x9a01af4
	.quad .Lname4094 /* index: 4094 */
	.weak x86_dbggdt_ptr; .quad x86_dbggdt_ptr
	.reloc ., R_X86_64_SIZE32, x86_dbggdt_ptr; .int 0
	.int 0x67dc8d2
	.quad .Lname4095 /* index: 4095 */
	.weak dbg_enter_scpustate_r; .quad dbg_enter_scpustate_r
	.reloc ., R_X86_64_SIZE32, dbg_enter_scpustate_r; .int 0
	.int 0x19d3ee2
END(kernel_symbol_table)
.section .rodata.kernel_strtab
.Lname3:
	.string "handle_get_superblock"
.Lname4:
	.string "regdump_gdt"
.Lname5:
	.string "krealloc_in_place"
.Lname6:
	.string "slab_malloc16"
.Lname8:
	.string "sys_mknodat"
.Lname9:
	.string "sys32_shutdown"
.Lname11:
	.string "inode_writek"
.Lname12:
	.string "sys32_lremovexattr"
.Lname13:
	.string "handle_installinto_sym"
.Lname15:
	.string "vm_kernel_sync"
.Lname16:
	.string "directory_getentry_p"
.Lname19:
	.string "regdump_coregs"
.Lname20:
	.string "slab_malloc24"
.Lname21:
	.string "pidns_tryupgrade"
.Lname25:
	.string "sys32_fmknodat"
.Lname26:
	.string "sys32_splice"
.Lname28:
	.string "vm_getfutex_existing"
.Lname30:
	.string "ramfs_type"
.Lname31:
	.string "sys32_pipe"
.Lname32:
	.string "sys_setresgid"
.Lname33:
	.string "ttybase_device_iread"
.Lname34:
	.string "slab_malloc32"
.Lname35:
	.string "qtime_to_timespec"
.Lname36:
	.string "sys32_bind"
.Lname37:
	.string "handle_get_inode"
.Lname38:
	.string "sys32_query_module"
.Lname39:
	.string "vio_readq"
.Lname40:
	.string "strcmp"
.Lname41:
	.string "sys_pivot_root"
.Lname42:
	.string "sys32_linux_lstat32"
.Lname43:
	.string "sys32_link"
.Lname44:
	.string "memmoveupl"
.Lname45:
	.string "syscall_emulate_r"
.Lname48:
	.string "slab_malloc40"
.Lname49:
	.string "memmoveupq"
.Lname50:
	.string "vm_pagesinphys"
.Lname51:
	.string "driver_finalized_callbacks"
.Lname52:
	.string "page_ismapped"
.Lname53:
	.string "sys_create_module"
.Lname55:
	.string "getreg_sgregs"
.Lname56:
	.string "slab_malloc48"
.Lname57:
	.string "path_recent"
.Lname58:
	.string "sys32_signal"
.Lname59:
	.string "sys32_setsockopt"
.Lname60:
	.string "vm_datapart_do_write_nopf"
.Lname62:
	.string "vm_mapat_subrange"
.Lname63:
	.string "pagedir_unwrite"
.Lname64:
	.string "vmb_fini"
.Lname66:
	.string "cpu_delete_idle_job"
.Lname68:
	.string "sys_getresgid"
.Lname69:
	.string "lookup_pci_device"
.Lname71:
	.string "vio_addq"
.Lname72:
	.string "sys_fmkdirat"
.Lname75:
	.string "kernel_slab_break"
.Lname76:
	.string "sys32_kill"
.Lname77:
	.string "sys32_mkdir"
.Lname78:
	.string "boot_partition"
.Lname79:
	.string "kernel_debugtraps_get"
.Lname80:
	.string "sys_modify_ldt"
.Lname81:
	.string "vm_datablock_read"
.Lname82:
	.string "x86_userexcept_callhandler32"
.Lname83:
	.string "fs_filesystems"
.Lname84:
	.string "sys32_prctl"
.Lname85:
	.string "sys32_time"
.Lname89:
	.string "pagedir_ismapped"
.Lname90:
	.string "vio_readw_aligned"
.Lname91:
	.string "vpage_alloc_untraced"
.Lname92:
	.string "error_as_signal"
.Lname94:
	.string "error_thrown"
.Lname95:
	.string "sys_ftruncate"
.Lname96:
	.string "strend"
.Lname97:
	.string "handle_lookup"
.Lname99:
	.string "sys_getdents"
.Lname100:
	.string "sys32_rt_sigtimedwait"
.Lname101:
	.string "aio_multihandle_done"
.Lname102:
	.string "dbg_screen_cellsize"
.Lname103:
	.string "__cxa_rethrow"
.Lname106:
	.string "sys_lgetxattr"
.Lname107:
	.string "vio_addw"
.Lname109:
	.string "fpustate_save"
.Lname110:
	.string "unwind_getreg_ucpustate"
.Lname111:
	.string "sys_maplibrary"
.Lname112:
	.string "handle_installhop"
.Lname113:
	.string "sys32_fsync"
.Lname115:
	.string "x86_sysroute1_c"
.Lname116:
	.string "driver_delmod"
.Lname117:
	.string "directory_creatfile"
.Lname118:
	.string "inode_writev"
.Lname119:
	.string "sys32_getresgid"
.Lname121:
	.string "cpu_broadcastipi"
.Lname123:
	.string "sys_break"
.Lname124:
	.string "path_print"
.Lname126:
	.string "task_rpc_exec_here_onexit"
.Lname127:
	.string "dbg_active"
.Lname128:
	.string "mempmoveup"
.Lname129:
	.string "sys32_setsid"
.Lname130:
	.string "character_device_unregister"
.Lname131:
	.string "debug_dlunlocksections"
.Lname132:
	.string "sys32_getrusage"
.Lname134:
	.string "vm_copyfromphys_nopf"
.Lname135:
	.string "mall_validate_padding"
.Lname136:
	.string "sys_inotify_add_watch"
.Lname137:
	.string "sys32_maplibrary"
.Lname138:
	.string "sys_sendmsg"
.Lname139:
	.string "sys32_sigprocmask"
.Lname143:
	.string "sys32_mbind"
.Lname144:
	.string "vm_datapart_read"
.Lname147:
	.string "task_schedule_user_rpc"
.Lname148:
	.string "sys32_nanosleep64"
.Lname149:
	.string "block_device_acquire_partlock_write"
.Lname151:
	.string "sys_getpeername"
.Lname152:
	.string "path_traversefull_ex"
.Lname153:
	.string "error_unwind"
.Lname154:
	.string "thiscpu_x86_ldt"
.Lname159:
	.string "getreg_xfpustate"
.Lname160:
	.string "regdump_drregs"
.Lname162:
	.string "sys_renameat2"
.Lname163:
	.string "ringbuffer_write_nonblock_noalloc"
.Lname164:
	.string "cmdline_encode_argument"
.Lname165:
	.string "vm_pagefromphys_nopf"
.Lname166:
	.string "block_device_awritev"
.Lname167:
	.string "heap_realloc_untraced"
.Lname169:
	.string "mempmoveupl"
.Lname171:
	.string "vm_kernel_treelock_tryupgrade"
.Lname173:
	.string "vio_addb"
.Lname174:
	.string "unwind_setreg_ucpustate_exclusive"
.Lname175:
	.string "sys_sched_getaffinity"
.Lname177:
	.string "vm_startdmav_nx"
.Lname178:
	.string "kernel_driver"
.Lname179:
	.string "pagedir_unmap_userspace_nosync"
.Lname180:
	.string "pagedir_init"
.Lname181:
	.string "_bootidle"
.Lname183:
	.string "sighand_destroy"
.Lname184:
	.string "task_alloc_synchronous_rpc_nx"
.Lname185:
	.string "superblock_set_unmounted"
.Lname188:
	.string "sys_nfsservctl"
.Lname190:
	.string "sys32_chown"
.Lname191:
	.string "vm_datapart_read_unsafe"
.Lname192:
	.string "directory_readnext_p"
.Lname193:
	.string "thiscpu_idle_x86_kernel_psp0"
.Lname194:
	.string "kmalloc_noslab"
.Lname195:
	.string "aio_handle_generic_func"
.Lname196:
	.string "driver_try_decref_and_delmod"
.Lname197:
	.string "superblock_nodeslock_write"
.Lname198:
	.string "slab_malloc56"
.Lname201:
	.string "sys_getpriority"
.Lname203:
	.string "getreg_drregs"
.Lname204:
	.string "mempcpyl"
.Lname205:
	.string "vm_readphysb"
.Lname206:
	.string "sys_kfstatat"
.Lname210:
	.string "kernel_pty_oprinter"
.Lname211:
	.string "aio_multihandle_generic_func"
.Lname212:
	.string "devfs_lock_end"
.Lname213:
	.string "strnlen"
.Lname214:
	.string "block_device_partition_readv"
.Lname215:
	.string "terminal_poll_iwrite"
.Lname216:
	.string "superblock_nodeslock_write_nx"
.Lname217:
	.string "swap_malloc_part"
.Lname219:
	.string "sys_unlink"
.Lname221:
	.string "vm_syncmem"
.Lname222:
	.string "sys_shmctl"
.Lname223:
	.string "vm_datablock_vio_write"
.Lname226:
	.string "sys32_pipe2"
.Lname227:
	.string "page_malloc"
.Lname229:
	.string "page_ffree"
.Lname230:
	.string "unregister_filesystem_type"
.Lname232:
	.string "validate_writable"
.Lname233:
	.string "vio_addl"
.Lname235:
	.string "sys32_vfork"
.Lname237:
	.string "sys32_setpgid"
.Lname238:
	.string "unwind_fde_scan"
.Lname239:
	.string "this_exception_trace"
.Lname240:
	.string "pagedir_prepare_map_p"
.Lname241:
	.string "sys32_epoll_create1"
.Lname243:
	.string "sys32_utimes64"
.Lname244:
	.string "path_lock_tryread"
.Lname245:
	.string "kernel_debugtrap_kcpustate"
.Lname246:
	.string "vmb_getfree"
.Lname248:
	.string "directory_entry_hash"
.Lname249:
	.string "json_parser_leavearray"
.Lname250:
	.string "vsnprintf"
.Lname252:
	.string "thisvm_x86_dr3"
.Lname255:
	.string "debug_sections_addr2line"
.Lname257:
	.string "vm_tasklock_upgrade_nx"
.Lname258:
	.string "sys32_linux_fstat32"
.Lname260:
	.string "devfs_insert"
.Lname261:
	.string "sys_timer_gettime"
.Lname263:
	.string "dbg_changedview"
.Lname264:
	.string "sys32_adjtimex"
.Lname265:
	.string "vm_node_destroy"
.Lname269:
	.string "sys_pipe2"
.Lname270:
	.string "sys_open"
.Lname271:
	.string "vm86_outb"
.Lname272:
	.string "cpu_deepsleep"
.Lname274:
	.string "dbg_getpagedir"
.Lname276:
	.string "sys32_mknod"
.Lname277:
	.string "cpu_apply_kcpustate"
.Lname278:
	.string "slab_kmalloc56"
.Lname279:
	.string "this_exception_info"
.Lname280:
	.string "instruction_length"
.Lname281:
	.string "sys_faccessat"
.Lname282:
	.string "task_isconnected"
.Lname283:
	.string "sys_sigaltstack"
.Lname284:
	.string "path_traversenfull_at"
.Lname287:
	.string "this_exception_state"
.Lname290:
	.string "vm_datablock_vio_read_phys"
.Lname291:
	.string "sys32_umount2"
.Lname292:
	.string "isr_register_greedy_at"
.Lname293:
	.string "driver_with_filename"
.Lname294:
	.string "vm_copyfromphys_onepage"
.Lname295:
	.string "vm_map_subrange"
.Lname296:
	.string "vm_datapart_do_read_nopf"
.Lname297:
	.string "path_traversenfull"
.Lname298:
	.string "vm_datablock_readp"
.Lname300:
	.string "x86_bootcpu_cpufeatures"
.Lname301:
	.string "sys_mprotect"
.Lname302:
	.string "dbg_fillscreen"
.Lname303:
	.string "vm_datablock_anonymous_zero"
.Lname305:
	.string "error_data"
.Lname307:
	.string "instruction_trysucc"
.Lname309:
	.string "sys_bind"
.Lname310:
	.string "sys32_preadv"
.Lname311:
	.string "mempcpyw"
.Lname313:
	.string "__predict_update_si"
.Lname314:
	.string "unwind_setreg_sfpustate"
.Lname315:
	.string "sys32_mq_unlink"
.Lname317:
	.string "slab_ffree"
.Lname319:
	.string "page_iszero"
.Lname321:
	.string "vio_xorq"
.Lname322:
	.string "character_device_register"
.Lname323:
	.string "sys_vfork"
.Lname324:
	.string "debuginfo_cu_parser_nextparent"
.Lname327:
	.string "vio_xorw"
.Lname328:
	.string "sys32_linux_oldlstat"
.Lname331:
	.string "memmoveupw"
.Lname332:
	.string "x86_userexcept_propagate"
.Lname333:
	.string "sys32_setgroups32"
.Lname337:
	.string "ioperm_bitmap_allocf_nx"
.Lname338:
	.string "vio_xorb"
.Lname339:
	.string "this_exception_subclass"
.Lname340:
	.string "kernel_syscall1_regcnt"
.Lname341:
	.string "sys32_getgroups"
.Lname342:
	.string "memeq_ku_nopf"
.Lname343:
	.string "vpage_free"
.Lname345:
	.string "devfs_lock_read"
.Lname346:
	.string "vm_datapart_do_enumdma"
.Lname348:
	.string "vio_xorl"
.Lname349:
	.string "sys_get_kernel_syms"
.Lname350:
	.string "dbg_main"
.Lname351:
	.string "sys_timerfd_create"
.Lname354:
	.string "sys32_unlinkat"
.Lname355:
	.string "handle_get_vfs"
.Lname357:
	.string "debuginfo_location_getvalue"
.Lname358:
	.string "vm_copytophys_onepage_nopf"
.Lname359:
	.string "error_rethrow"
.Lname361:
	.string "unwind_cfa_sigframe_apply"
.Lname363:
	.string "sys32_set_tid_address"
.Lname364:
	.string "sys32_afs_syscall"
.Lname365:
	.string "vm_pageinphys"
.Lname368:
	.string "vm_datapart_map_ram_autoprop"
.Lname370:
	.string "__rawmemchr"
.Lname371:
	.string "sys_exit"
.Lname372:
	.string "sys32_clock_getres64"
.Lname373:
	.string "inode_file_pwritev_with_pwrite"
.Lname375:
	.string "sys_lsetxattr"
.Lname376:
	.string "heap_align_nx"
.Lname377:
	.string "x86_dbg_owner_lapicid"
.Lname380:
	.string "vm_datapart_allocswap_nx"
.Lname382:
	.string "unwind_getreg_scpustate_exclusive"
.Lname383:
	.string "sys_lookup_dcookie"
.Lname384:
	.string "sys32_rpc_service"
.Lname386:
	.string "vm_datapart_pageaddr"
.Lname387:
	.string "character_device_sync"
.Lname388:
	.string "driver_symbol_at"
.Lname389:
	.string "sys_init_module"
.Lname390:
	.string "sys_process_vm_readv"
.Lname391:
	.string "unwind_getreg_lcpustate"
.Lname392:
	.string "__predict_update_eax"
.Lname393:
	.string "task_setup_kernel"
.Lname394:
	.string "pagedir_unmap"
.Lname395:
	.string "syscall_trace_compat"
.Lname397:
	.string "kernel_syscall1_restartmode32"
.Lname399:
	.string "handle_lookup_nosym"
.Lname401:
	.string "sys32_create_module"
.Lname403:
	.string "keymap_init_en_US"
.Lname405:
	.string "inode_datablock_type"
.Lname406:
	.string "vm_readphysq"
.Lname407:
	.string "ttybase_device_stat"
.Lname408:
	.string "cpu_private_function_callbuf_ex"
.Lname409:
	.string "krand"
.Lname411:
	.string "inode_awritek"
.Lname412:
	.string "vm86_pic_intr"
.Lname413:
	.string "x86_userexcept_seterrno64"
.Lname414:
	.string "mempmovedown"
.Lname415:
	.string "mall_dump_leaks"
.Lname417:
	.string "rawmemrchrq"
.Lname418:
	.string "sys32_getegid32"
.Lname419:
	.string "aio_pbuffer_copytovphys"
.Lname420:
	.string "page_malloc_at"
.Lname421:
	.string "path_getcasechild_and_parent_inode"
.Lname422:
	.string "x86_fpustate_save"
.Lname423:
	.string "rawmemrchrw"
.Lname424:
	.string "__predict_update_ecx"
.Lname425:
	.string "sys32_truncate"
.Lname426:
	.string "sys_open_by_handle_at"
.Lname427:
	.string "vm_addhwbreak"
.Lname428:
	.string "aio_multihandle_cancel"
.Lname429:
	.string "vm_unmap_kernel_ram"
.Lname432:
	.string "sys32_readdir"
.Lname434:
	.string "block_device_awritev_sector"
.Lname435:
	.string "sys32_fstatfs"
.Lname437:
	.string "handle_get_regular_node"
.Lname438:
	.string "sys_sched_getattr"
.Lname439:
	.string "vm86_outw"
.Lname440:
	.string "__predict_update_edx"
.Lname441:
	.string "dbg_trygetuni"
.Lname442:
	.string "sys32_statfs64"
.Lname444:
	.string "rawmemrchrl"
.Lname447:
	.string "symtab_scantable"
.Lname448:
	.string "sys_getsockname"
.Lname450:
	.string "sys_setuid"
.Lname451:
	.string "dbg_trygetc"
.Lname452:
	.string "json_parser_getfloat"
.Lname453:
	.string "memset_nopf"
.Lname454:
	.string "sys32_readf"
.Lname455:
	.string "sys32_sigpending"
.Lname456:
	.string "driver_symbol_ex"
.Lname458:
	.string "sys_klstat"
.Lname459:
	.string "vm_datapart_lock_trywrite"
.Lname461:
	.string "sys_vserver"
.Lname463:
	.string "vm_datapart_allocram"
.Lname465:
	.string "vm_tasklock_tryservice"
.Lname467:
	.string "sys32_get_kernel_syms"
.Lname468:
	.string "directory_readnext"
.Lname469:
	.string "superblock_mountlock_write"
.Lname470:
	.string "disasm_print_line_nolf"
.Lname473:
	.string "ioperm_bitmap_copy"
.Lname475:
	.string "sys_msgget"
.Lname476:
	.string "sys_iopl"
.Lname478:
	.string "sys32_swapon"
.Lname479:
	.string "kernel_debugtrap_r_ucpustate"
.Lname480:
	.string "pagedir_iswritable_p"
.Lname481:
	.string "this_sigqueue"
.Lname484:
	.string "sys32_linux_lstat64"
.Lname485:
	.string "sys32_ioctlf"
.Lname486:
	.string "getreg_sfpuenv"
.Lname488:
	.string "rwlock_upgrade_nx"
.Lname489:
	.string "character_device_destroy"
.Lname490:
	.string "vm_datablock_read_unsafe"
.Lname491:
	.string "x86_emulock_cmpxchg128"
.Lname492:
	.string "heap_validate_all"
.Lname493:
	.string "sys32_rmdir"
.Lname495:
	.string "vm_datapart_freeram"
.Lname496:
	.string "regdump_gpregs_with_sp"
.Lname498:
	.string "slab_kmalloc32"
.Lname499:
	.string "dbg_getallregs"
.Lname500:
	.string "dbg_editfield"
.Lname501:
	.string "cpu_schedule_idle_job_simple"
.Lname503:
	.string "sys32_setpriority"
.Lname505:
	.string "sys32_mprotect"
.Lname506:
	.string "sys_lfutexexpr"
.Lname507:
	.string "this_sigmask"
.Lname508:
	.string "x86_syscall_emulate_sysvabi"
.Lname510:
	.string "unicode_readutf16_swap_n"
.Lname511:
	.string "dbg_setregbyname"
.Lname512:
	.string "sys_signalfd"
.Lname514:
	.string "linebuffer_rewrite"
.Lname515:
	.string "sys32_munlock"
.Lname516:
	.string "regdump_idt"
.Lname517:
	.string "acpi_mode"
.Lname518:
	.string "snprintf"
.Lname519:
	.string "error_throw"
.Lname520:
	.string "__predict_update_cx"
.Lname522:
	.string "unicode_readutf16_n"
.Lname523:
	.string "inode_readk"
.Lname524:
	.string "__predict_update_dl"
.Lname526:
	.string "cpu_idlemain"
.Lname527:
	.string "task_tryyield_or_pause"
.Lname528:
	.string "vm_datablock_writevp"
.Lname530:
	.string "dbg_enter_lcpustate_c"
.Lname531:
	.string "sprintf_s"
.Lname532:
	.string "driver_fde_find"
.Lname533:
	.string "cpu_apply_lcpustate"
.Lname534:
	.string "inode_readv"
.Lname535:
	.string "sys_recvmmsg"
.Lname536:
	.string "__predict_update_dx"
.Lname537:
	.string "sys32_sched_getaffinity"
.Lname539:
	.string "__cpuset_full_mask"
.Lname543:
	.string "task_sleep_cputime"
.Lname544:
	.string "cred_require_debugtrap"
.Lname545:
	.string "vm_datapart_do_read"
.Lname546:
	.string "vmb_node_remove"
.Lname547:
	.string "inode_readv_phys"
.Lname548:
	.string "block_device_read"
.Lname549:
	.string "debuginfo_location_setvalue"
.Lname551:
	.string "cpu_assert_sleeping"
.Lname552:
	.string "__predict_update_ax"
.Lname553:
	.string "sys_setfsuid"
.Lname554:
	.string "strto64"
.Lname556:
	.string "sys32_socketcall"
.Lname557:
	.string "dbg_enter_icpustate_cr"
.Lname558:
	.string "x86_userexcept_seterrno32"
.Lname559:
	.string "vm_kernel_treelock_tryread"
.Lname560:
	.string "vio_xchb"
.Lname562:
	.string "vm_exec_assert_regular"
.Lname564:
	.string "cpu_quantum_elapsed"
.Lname565:
	.string "driver_getfilename"
.Lname566:
	.string "block_device_readv"
.Lname568:
	.string "pagedir_prepare_mapone"
.Lname569:
	.string "fs_destroy"
.Lname571:
	.string "sys_ioctl"
.Lname572:
	.string "__predict_update_cl"
.Lname574:
	.string "blocking_cleanup_chain"
.Lname575:
	.string "handle_close"
.Lname576:
	.string "sys_debugtrap"
.Lname577:
	.string "superblock_statfs"
.Lname578:
	.string "format_sprintf_printer"
.Lname580:
	.string "sys_setresuid"
.Lname581:
	.string "ansitty_device_write"
.Lname582:
	.string "_ZSt9terminatev"
.Lname583:
	.string "validate_executable"
.Lname584:
	.string "ringbuffer_setwritten"
.Lname585:
	.string "pidns_destroy"
.Lname587:
	.string "unwind_setreg_kcpustate"
.Lname588:
	.string "vm_tasklock_end"
.Lname589:
	.string "x86_memcpy_nopf"
.Lname593:
	.string "fpustate_alloc_nx"
.Lname595:
	.string "inode_write_phys"
.Lname596:
	.string "pidns_endread"
.Lname597:
	.string "fpustate_free"
.Lname598:
	.string "sys_select"
.Lname599:
	.string "taskpid_destroy"
.Lname600:
	.string "syscall_emulate64"
.Lname601:
	.string "keyboard_device_init"
.Lname605:
	.string "vm_node_update_write_access_locked_vm"
.Lname606:
	.string "sys32_mincore"
.Lname607:
	.string "lookup_filesystem_type"
.Lname609:
	.string "sys_munmap"
.Lname610:
	.string "cpu_schedule_idle_job"
.Lname611:
	.string "sys_clock_getres"
.Lname612:
	.string "pidns_tryread"
.Lname613:
	.string "dbg_vmenuf"
.Lname614:
	.string "block_device_writev"
.Lname615:
	.string "sys_utime"
.Lname619:
	.string "dbg_getreg"
.Lname620:
	.string "sys32_sched_rr_get_interval"
.Lname621:
	.string "sys32_fchmodat"
.Lname623:
	.string "validate_readable_opt"
.Lname624:
	.string "vm_kernel_syncone"
.Lname625:
	.string "sys32_clock_gettime"
.Lname627:
	.string "cpu_enable_preemptive_interrupts"
.Lname628:
	.string "cpu_run_current"
.Lname629:
	.string "vm_datablock_anonymous_zero_type"
.Lname630:
	.string "sys32_idle"
.Lname632:
	.string "sys32_waitpid"
.Lname633:
	.string "mouse_device_read"
.Lname634:
	.string "oneshot_directory_file_destroy"
.Lname637:
	.string "unwind_getreg_icpustate"
.Lname639:
	.string "fs_filesystems_lock_trywrite"
.Lname640:
	.string "sys_kstat"
.Lname641:
	.string "sys_io_setup"
.Lname642:
	.string "vpage_ffree_untraced"
.Lname643:
	.string "block_device_awrite_phys"
.Lname644:
	.string "format_repeat"
.Lname645:
	.string "sys32_memfd_create"
.Lname647:
	.string "sys32_kfstatat"
.Lname648:
	.string "__predict_update_rax"
.Lname650:
	.string "vm_pagetophys"
.Lname651:
	.string "sys32_brk"
.Lname653:
	.string "sys32_getsockname"
.Lname656:
	.string "sys_frealpath4"
.Lname657:
	.string "slab_kmalloc8"
.Lname658:
	.string "vio_readl"
.Lname661:
	.string "slab_free"
.Lname663:
	.string "dbg_asmview"
.Lname664:
	.string "task_push_asynchronous_rpc_v"
.Lname665:
	.string "isr_vector_state_destroy"
.Lname666:
	.string "sys_pause"
.Lname667:
	.string "sys32_init_module"
.Lname670:
	.string "memmovedown"
.Lname671:
	.string "getreg_sfpustate"
.Lname672:
	.string "sys32_vmsplice"
.Lname675:
	.string "inode_awrite_phys"
.Lname676:
	.string "sig_broadcast"
.Lname677:
	.string "directory_getcasenode"
.Lname678:
	.string "sys_preadvf"
.Lname679:
	.string "sys_prctl"
.Lname680:
	.string "__predict_update_rcx"
.Lname681:
	.string "ttybase_device_ioctl"
.Lname683:
	.string "handle_get_datablock"
.Lname687:
	.string "vm_mapres"
.Lname688:
	.string "pagedir_unprepare_mapone_p"
.Lname689:
	.string "vm_tasklock_read_nx"
.Lname690:
	.string "debuginfo_cu_parser_skipattr"
.Lname691:
	.string "disasm_default_maxbytes"
.Lname692:
	.string "cred_require_mount"
.Lname693:
	.string "cpu_wake"
.Lname694:
	.string "sys32_linkat"
.Lname696:
	.string "__predict_update_rdx"
.Lname697:
	.string "driver_insmod"
.Lname700:
	.string "debuginfo_cu_parser_loadattr_type"
.Lname702:
	.string "handle_existsin"
.Lname703:
	.string "sys32_timer_gettime"
.Lname704:
	.string "__gxx_personality_v0"
.Lname707:
	.string "task_deliver_rpc"
.Lname708:
	.string "sys32_setrlimit"
.Lname709:
	.string "sys_sendfile"
.Lname710:
	.string "x86_iopl_keep_after_clone"
.Lname711:
	.string "debuginfo_cu_parser_getflag"
.Lname712:
	.string "sys32_frealpathat"
.Lname715:
	.string "vm_datablock_getfutex_existing"
.Lname717:
	.string "sys32_lsetxattr"
.Lname718:
	.string "memrlen"
.Lname721:
	.string "sys32_set_thread_area"
.Lname722:
	.string "sys32_lfutexexpr"
.Lname723:
	.string "inode_areadv_phys"
.Lname724:
	.string "sys_linux_lstat64"
.Lname726:
	.string "sys32_pwritev"
.Lname729:
	.string "sys32_fsymlinkat"
.Lname732:
	.string "__predict_update_al"
.Lname734:
	.string "vm_syncone"
.Lname735:
	.string "getreg_sgbase"
.Lname736:
	.string "unwind_setreg_icpustate_exclusive"
.Lname738:
	.string "format_snprintf_printer"
.Lname739:
	.string "sys_rt_sigprocmask"
.Lname740:
	.string "cpu_add_quantum_offset"
.Lname741:
	.string "sys32_chroot"
.Lname742:
	.string "keymap_translate_buf"
.Lname743:
	.string "inode_read_blocking"
.Lname744:
	.string "vm_kernel_treelock_writef"
.Lname745:
	.string "driver_state_destroy"
.Lname747:
	.string "sys32_pause"
.Lname748:
	.string "sys32__sysctl"
.Lname750:
	.string "sys_hopf"
.Lname751:
	.string "sys32_listxattr"
.Lname752:
	.string "pagedir_unsetchanged_p"
.Lname754:
	.string "sys32_lchown32"
.Lname755:
	.string "block_device_areadv_phys"
.Lname756:
	.string "sys32_clock_nanosleep64"
.Lname757:
	.string "rwlock_downgrade"
.Lname758:
	.string "json_parser_next"
.Lname759:
	.string "keyboard_buffer_putkey"
.Lname761:
	.string "sys32_getpgid"
.Lname764:
	.string "sys32_geteuid"
.Lname765:
	.string "sys_move_pages"
.Lname766:
	.string "superblock_mountlock_trywrite"
.Lname767:
	.string "vm_datablock_anonymize"
.Lname771:
	.string "sys_fanotify_mark"
.Lname772:
	.string "addr2line_end"
.Lname773:
	.string "pagedir_unmap_userspace"
.Lname777:
	.string "block_device_destroy"
.Lname780:
	.string "task_disconnectall"
.Lname781:
	.string "sys32_fanotify_mark"
.Lname784:
	.string "sys_mremap"
.Lname785:
	.string "vm_datablock_getfutex"
.Lname786:
	.string "sigmask_getwr"
.Lname787:
	.string "sys_finit_module"
.Lname788:
	.string "instruction_trypred"
.Lname789:
	.string "fs_filesystems_remove"
.Lname791:
	.string "rwlock_downgrade_readonly"
.Lname792:
	.string "dbg_menuex"
.Lname793:
	.string "sys32_stime64"
.Lname794:
	.string "sys_unlinkat"
.Lname795:
	.string "path_lock"
.Lname798:
	.string "page_malloc_part_between"
.Lname799:
	.string "ttybase_device_poll"
.Lname800:
	.string "sys32_utimensat64"
.Lname802:
	.string "path_clear"
.Lname803:
	.string "kmalloc"
.Lname804:
	.string "cmdline_split"
.Lname805:
	.string "debug_print_filename"
.Lname806:
	.string "error_printf"
.Lname807:
	.string "json_writer_putstring"
.Lname809:
	.string "sys32_epoll_ctl"
.Lname811:
	.string "vm_datapart_lockwrite_setcore_unsharecow"
.Lname816:
	.string "unicode_8to16"
.Lname818:
	.string "validate_user"
.Lname819:
	.string "swap_malloc"
.Lname820:
	.string "driver_local_symbol_at"
.Lname821:
	.string "driver_with_name"
.Lname822:
	.string "unwind_getreg_xfpustate_exclusive"
.Lname825:
	.string "krand_seed"
.Lname826:
	.string "vm_set_aslr_disabled"
.Lname827:
	.string "cpu_addsleepingtask"
.Lname828:
	.string "sys32_ioprio_get"
.Lname830:
	.string "getreg_irregs"
.Lname831:
	.string "handle_get_pipe"
.Lname833:
	.string "thiscpu_x86_dfstackpart"
.Lname835:
	.string "inode_readallv_phys"
.Lname836:
	.string "regdump_sgregs_with_cs_ss_tr_ldt"
.Lname837:
	.string "sys_fsymlinkat"
.Lname838:
	.string "this_taskpid"
.Lname841:
	.string "sys32_tee"
.Lname843:
	.string "sys_sched_get_priority_max"
.Lname845:
	.string "sys32_remap_file_pages"
.Lname846:
	.string "cred_require_sysadmin"
.Lname848:
	.string "task_raisesignalprocessgroup"
.Lname849:
	.string "sys32_setxattr"
.Lname851:
	.string "handle_manager_alloc"
.Lname852:
	.string "heap_realign_untraced"
.Lname853:
	.string "setreg_sgbase"
.Lname857:
	.string "sys32_creat"
.Lname862:
	.string "sys_query_module"
.Lname863:
	.string "sys_semctl"
.Lname864:
	.string "task_sleep"
.Lname865:
	.string "task_serve"
.Lname867:
	.string "sigqueue_fini"
.Lname868:
	.string "json_parser_getuint64"
.Lname869:
	.string "pagedir_mapone"
.Lname871:
	.string "sys_recvmsg"
.Lname872:
	.string "dbg_messagebox"
.Lname873:
	.string "keyboard_device_trygetkey"
.Lname875:
	.string "sigmask_check"
.Lname876:
	.string "tty_device_poll"
.Lname877:
	.string "task_getvm"
.Lname878:
	.string "vm_datablock_destroy"
.Lname879:
	.string "sys_sched_setaffinity"
.Lname880:
	.string "sys_writef"
.Lname882:
	.string "setreg_xfpustate"
.Lname883:
	.string "sys32_rt_sigaction"
.Lname884:
	.string "vm_datapart_lock_read"
.Lname886:
	.string "dbg_vpprintf"
.Lname887:
	.string "mouse_device_hwheel"
.Lname888:
	.string "x86_syscall_emulate_int80h"
.Lname889:
	.string "sys32_sync"
.Lname891:
	.string "driver_section_lock"
.Lname892:
	.string "vio_andl"
.Lname893:
	.string "thiscpu_state"
.Lname894:
	.string "inode_chown"
.Lname895:
	.string "superblock_mountlock_endwrite"
.Lname896:
	.string "vm_map"
.Lname897:
	.string "memrendq"
.Lname899:
	.string "sys_fstatfs"
.Lname900:
	.string "rwlock_tryread"
.Lname901:
	.string "kernel_panic_here"
.Lname903:
	.string "cpu_loadpending"
.Lname904:
	.string "path_traversenfull_ex"
.Lname905:
	.string "json_parser_findkey"
.Lname906:
	.string "sys_rpc_service"
.Lname908:
	.string "kernel_debugtraps_uninstall"
.Lname909:
	.string "sys_alarm"
.Lname912:
	.string "vm_kernel_treelock_write"
.Lname913:
	.string "x86_fpustate_variant"
.Lname914:
	.string "sys32_membarrier"
.Lname915:
	.string "vio_copyfromvio_to_phys"
.Lname916:
	.string "sys32_raiseat"
.Lname917:
	.string "sys_rt_sigreturn"
.Lname919:
	.string "sys_add_key"
.Lname921:
	.string "__predict_update_rsi"
.Lname922:
	.string "thiscpu_x86_fputhread"
.Lname923:
	.string "directory_link"
.Lname924:
	.string "memrendl"
.Lname927:
	.string "path_lock_endwrite"
.Lname928:
	.string "vm86_outl"
.Lname929:
	.string "sys_rename"
.Lname930:
	.string "cpu_disable_preemptive_interrupts_nopr"
.Lname931:
	.string "handle_manager_cloexec"
.Lname932:
	.string "cpu_online_count"
.Lname933:
	.string "inode_recent_tryremove"
.Lname934:
	.string "sys_pwritev"
.Lname935:
	.string "cpu_assert_running"
.Lname940:
	.string "vm_node_remove"
.Lname942:
	.string "sys_userfaultfd"
.Lname944:
	.string "sys32_clock_adjtime"
.Lname947:
	.string "sys_fchownat"
.Lname948:
	.string "rwlock_endread"
.Lname949:
	.string "blocking_cleanup_prioritize"
.Lname950:
	.string "vm_datablock_anonymous_type"
.Lname952:
	.string "path_lock_tryupgrade"
.Lname953:
	.string "sys32_linux_stat64"
.Lname954:
	.string "sys_clock_settime"
.Lname959:
	.string "kernel_panic_icpustate"
.Lname961:
	.string "sys_times"
.Lname962:
	.string "x86_syscall32_sysenter_traced"
.Lname963:
	.string "vio_copytovio_from_phys"
.Lname964:
	.string "acpi_root"
.Lname965:
	.string "superblock_mountlock_downgrade"
.Lname967:
	.string "sys_syslog"
.Lname968:
	.string "dbg_enter_ucpustate_c"
.Lname969:
	.string "sys32_readv"
.Lname971:
	.string "handle_get_task"
.Lname972:
	.string "sys32_fcntl"
.Lname973:
	.string "fpustate_loadfrom"
.Lname974:
	.string "kernel_debugtrap_on"
.Lname975:
	.string "sys_quotactl"
.Lname977:
	.string "vm_prefault"
.Lname978:
	.string "sys32_stty"
.Lname979:
	.string "directory_entry_alloc_s"
.Lname980:
	.string "json_parser_getint64"
.Lname982:
	.string "sys32_preadvf"
.Lname983:
	.string "inode_truncate"
.Lname984:
	.string "slab_kmalloc_nx8"
.Lname985:
	.string "directory_entry_destroy"
.Lname986:
	.string "sys_sched_yield"
.Lname987:
	.string "x86_syscall32_lcall7_iret"
.Lname988:
	.string "driver_with_namel"
.Lname990:
	.string "thiscpu_x86_lapicversion"
.Lname991:
	.string "sys32_madvise"
.Lname992:
	.string "sys32_mmap"
.Lname994:
	.string "x86_userexcept_callhandler"
.Lname995:
	.string "inode_aread_phys"
.Lname996:
	.string "aio_pbuffer_memset"
.Lname997:
	.string "json_decode"
.Lname999:
	.string "task_setprocess"
.Lname1000:
	.string "path_traversen_ex"
.Lname1001:
	.string "x86_pagedir_syncall_maybe_global"
.Lname1003:
	.string "x86_pit_lock"
.Lname1004:
	.string "x86_userexcept_callhandler64"
.Lname1005:
	.string "validate_userm"
.Lname1007:
	.string "timespec_to_qtime"
.Lname1008:
	.string "vmb_map"
.Lname1010:
	.string "block_device_awrite_phys_sector"
.Lname1011:
	.string "sys_utimes"
.Lname1013:
	.string "kernel_debugtrap_lcpustate"
.Lname1015:
	.string "sys32_mq_notify"
.Lname1016:
	.string "getreg_gpregs"
.Lname1017:
	.string "sys32_timer_settime64"
.Lname1018:
	.string "sys32_setreuid32"
.Lname1019:
	.string "sys32__llseek"
.Lname1020:
	.string "__predict_update_sil"
.Lname1021:
	.string "sys32_timerfd_gettime"
.Lname1022:
	.string "sys32_rt_sigreturn"
.Lname1023:
	.string "ringbuffer_unwrite"
.Lname1025:
	.string "memcmpq"
.Lname1027:
	.string "task_connect_ghost_c"
.Lname1028:
	.string "block_device_partition_read"
.Lname1029:
	.string "sys32_mq_timedreceive"
.Lname1031:
	.string "memcmpw"
.Lname1032:
	.string "sys_mkdir"
.Lname1033:
	.string "sys32_get_mempolicy"
.Lname1035:
	.string "x86_fxsave_mxcsr_mask"
.Lname1037:
	.string "sys32_eventfd2"
.Lname1042:
	.string "keyboard_device_trygetchar"
.Lname1044:
	.string "ringbuffer_skipread"
.Lname1049:
	.string "sys32_set_mempolicy"
.Lname1050:
	.string "vm86_hw_intr"
.Lname1051:
	.string "sys_setxattr"
.Lname1052:
	.string "memcmpl"
.Lname1053:
	.string "handle_get_vm"
.Lname1054:
	.string "addr2line_begin"
.Lname1055:
	.string "heap_validate"
.Lname1056:
	.string "thisvm_pdir_phys_ptr"
.Lname1057:
	.string "setreg_coregs"
.Lname1059:
	.string "sys_clock_adjtime"
.Lname1061:
	.string "sys32_clone"
.Lname1062:
	.string "sys32_vm86"
.Lname1063:
	.string "vm_kernel_treelock_downgrade"
.Lname1064:
	.string "vio_readq_aligned"
.Lname1065:
	.string "sys_rmdir"
.Lname1067:
	.string "sys_chroot"
.Lname1068:
	.string "superblock_syncall"
.Lname1069:
	.string "task_setsessionleader"
.Lname1070:
	.string "driver_getsection"
.Lname1071:
	.string "handle_installinto"
.Lname1072:
	.string "acpi_lookup"
.Lname1073:
	.string "sys32_gettimeofday64"
.Lname1074:
	.string "this_user_except_handler"
.Lname1075:
	.string "vm_datablock_sync"
.Lname1076:
	.string "sys_futimesat"
.Lname1077:
	.string "pagedir_unprepare_mapone"
.Lname1079:
	.string "sys32_settimeofday"
.Lname1081:
	.string "file_destroy"
.Lname1084:
	.string "setreg_gpregs"
.Lname1087:
	.string "kffree"
.Lname1088:
	.string "sys32_nanosleep"
.Lname1092:
	.string "sys_io_submit"
.Lname1093:
	.string "sys_timer_settime"
.Lname1095:
	.string "vio_andq"
.Lname1096:
	.string "path_printentex"
.Lname1099:
	.string "rwlock_writing"
.Lname1100:
	.string "sys32_ppoll"
.Lname1104:
	.string "vm_unmap"
.Lname1106:
	.string "inode_recent_getcur"
.Lname1107:
	.string "sys32_ipc"
.Lname1108:
	.string "sys32_epoll_pwait"
.Lname1109:
	.string "sys32_timerfd_settime"
.Lname1111:
	.string "sys32_personality"
.Lname1113:
	.string "mouse_buffer_trygetpacket"
.Lname1114:
	.string "sys_ioprio_set"
.Lname1116:
	.string "sys_fchmodat"
.Lname1117:
	.string "handle_tryclose_nosym"
.Lname1118:
	.string "heap_align"
.Lname1119:
	.string "sys_setdomainname"
.Lname1121:
	.string "x86_sysroute1_asm32_int80"
.Lname1125:
	.string "driver_clear_fde_cache"
.Lname1127:
	.string "sys_epoll_pwait"
.Lname1129:
	.string "keyboard_buffer_trygetkey"
.Lname1131:
	.string "userkern_segment_block"
.Lname1132:
	.string "handle_manager_kernel"
.Lname1133:
	.string "pipe_writer_create"
.Lname1135:
	.string "vm_delhwbreak"
.Lname1138:
	.string "sys32_uselib"
.Lname1139:
	.string "dbg_ungetc"
.Lname1140:
	.string "sys_readvf"
.Lname1141:
	.string "inode_file_pwrite_with_write"
.Lname1142:
	.string "zlib_reader_init"
.Lname1144:
	.string "system_clearcaches_s"
.Lname1145:
	.string "sys32_time64"
.Lname1146:
	.string "vpage_ffree"
.Lname1148:
	.string "x86_idt_syscall_traced"
.Lname1149:
	.string "sys32_getsockopt"
.Lname1151:
	.string "pipe_create"
.Lname1152:
	.string "pagedir_maphintone_p"
.Lname1153:
	.string "sys32_dup"
.Lname1155:
	.string "vm_writephysb"
.Lname1156:
	.string "dbg_indent"
.Lname1157:
	.string "dbg_endupdate"
.Lname1159:
	.string "regdump_gpreg"
.Lname1160:
	.string "vm_datapart_getfutex"
.Lname1162:
	.string "sys_shutdown"
.Lname1163:
	.string "sys32_sigaction"
.Lname1165:
	.string "this_exception_faultaddr"
.Lname1167:
	.string "task_setvm"
.Lname1168:
	.string "pagedir_prepare_map"
.Lname1170:
	.string "vmb_node_insert"
.Lname1171:
	.string "aio_buffer_copytovphys"
.Lname1172:
	.string "sys_fadvise64"
.Lname1173:
	.string "fs_clone"
.Lname1174:
	.string "isr_usage_of"
.Lname1175:
	.string "sys32_delete_module"
.Lname1176:
	.string "mall_trace_nx"
.Lname1177:
	.string "dbg_getuni"
.Lname1178:
	.string "unicode_16to32"
.Lname1183:
	.string "sys_setfsgid"
.Lname1185:
	.string "unicode_readutf16_swap_rev_n"
.Lname1186:
	.string "sys_epoll_ctl"
.Lname1187:
	.string "x86_iopl_keep_after_exec"
.Lname1188:
	.string "sys_getegid"
.Lname1189:
	.string "dbg_vprintf"
.Lname1190:
	.string "setreg_drregs"
.Lname1191:
	.string "instruction_succ"
.Lname1192:
	.string "path_printex"
.Lname1193:
	.string "json_writer_endarray"
.Lname1195:
	.string "inode_readallk"
.Lname1196:
	.string "rawmemlenl"
.Lname1197:
	.string "vio_andb"
.Lname1198:
	.string "page_malloc_between"
.Lname1200:
	.string "sys_clock_gettime"
.Lname1201:
	.string "rawmemlenq"
.Lname1202:
	.string "task_waitfor"
.Lname1204:
	.string "character_device_read"
.Lname1205:
	.string "regdump_kcpustate"
.Lname1206:
	.string "inode_readallv"
.Lname1207:
	.string "rawmemlenw"
.Lname1208:
	.string "superblock_nodeslock_upgrade_nx"
.Lname1209:
	.string "superblock_nodeslock_read"
.Lname1212:
	.string "sys_sched_setscheduler"
.Lname1214:
	.string "sys32_timer_getoverrun"
.Lname1215:
	.string "sys32_oldolduname"
.Lname1217:
	.string "memendq"
.Lname1219:
	.string "mzones"
.Lname1220:
	.string "pidns_read"
.Lname1221:
	.string "sys32_timerfd_settime64"
.Lname1222:
	.string "sys_sched_get_priority_min"
.Lname1223:
	.string "memendw"
.Lname1225:
	.string "vm86_fullstep"
.Lname1227:
	.string "regdump_sreg"
.Lname1228:
	.string "__stack_chk_fail"
.Lname1229:
	.string "vm_datapart_decref_and_merge"
.Lname1230:
	.string "vm_datapart_lockread_setcore"
.Lname1231:
	.string "minfo"
.Lname1232:
	.string "x86_syscall_emulate_sysenter_r"
.Lname1234:
	.string "sys32_vserver"
.Lname1235:
	.string "task_alloc_synchronous_rpc"
.Lname1236:
	.string "sys32_rt_sigtimedwait64"
.Lname1237:
	.string "fpustate_savecpu"
.Lname1238:
	.string "sys32_writevf"
.Lname1240:
	.string "sys_epoll_wait"
.Lname1241:
	.string "block_device_acquire_partlock_tryread"
.Lname1244:
	.string "memendl"
.Lname1245:
	.string "sys32_signalfd"
.Lname1247:
	.string "error_print_into"
.Lname1249:
	.string "rwlock_reading_r"
.Lname1251:
	.string "task_start_default_flags"
.Lname1252:
	.string "rwlock_pollread"
.Lname1254:
	.string "sys_wait4"
.Lname1255:
	.string "pidns_endwrite"
.Lname1258:
	.string "ramfs_dev_type"
.Lname1261:
	.string "sys32_llistxattr"
.Lname1262:
	.string "sys_getgroups"
.Lname1263:
	.string "vm_datapart_lock_endwrite"
.Lname1265:
	.string "unwind_cfa_calculate_cfa"
.Lname1266:
	.string "handle_get_driver"
.Lname1267:
	.string "handle_get_pidns"
.Lname1268:
	.string "path_mount"
.Lname1269:
	.string "kernel_uname"
.Lname1270:
	.string "sys32_getuid"
.Lname1273:
	.string "callback_list_detroy"
.Lname1275:
	.string "vm_datapart_lock_upgrade"
.Lname1277:
	.string "vpage_realloc"
.Lname1279:
	.string "vm_copytophys_onepage"
.Lname1280:
	.string "cpu_apply_icpustate_rsp"
.Lname1282:
	.string "sys32_getgid32"
.Lname1284:
	.string "path_freelist"
.Lname1285:
	.string "inode_write"
.Lname1287:
	.string "mempsetq"
.Lname1288:
	.string "heap_alloc_untraced_nx"
.Lname1292:
	.string "slab_kmalloc24"
.Lname1293:
	.string "sys_dup2"
.Lname1298:
	.string "vm_write_nopf"
.Lname1299:
	.string "vm_node_update_write_access"
.Lname1300:
	.string "sys_rt_sigtimedwait"
.Lname1301:
	.string "task_sethandlemanager"
.Lname1302:
	.string "format_vprintf"
.Lname1305:
	.string "sys32_connect"
.Lname1307:
	.string "vm_startdmav"
.Lname1308:
	.string "driver_local_symbol"
.Lname1310:
	.string "vm_datapart_do_read_phys"
.Lname1311:
	.string "path_lock_write"
.Lname1312:
	.string "x86_userexcept_unwind_interrupt_esp"
.Lname1315:
	.string "sys32_getcpu"
.Lname1316:
	.string "cred_require_vmread"
.Lname1317:
	.string "aio_noop_type"
.Lname1318:
	.string "inode_pathconf"
.Lname1320:
	.string "block_device_autopart_ex"
.Lname1323:
	.string "memrendw"
.Lname1324:
	.string "sys_tkill"
.Lname1325:
	.string "setreg_irregs"
.Lname1327:
	.string "sys_symlinkat"
.Lname1328:
	.string "cpu_apply_scpustate_rsp"
.Lname1331:
	.string "fs_filesystems_delblocks"
.Lname1332:
	.string "sys32_setfsuid"
.Lname1333:
	.string "dbg_enter_kcpustate"
.Lname1334:
	.string "vm_mapresat"
.Lname1337:
	.string "sys32_chmod"
.Lname1338:
	.string "unwind_getreg_sfpustate_exclusive"
.Lname1339:
	.string "vm_getfree"
.Lname1340:
	.string "sys32_userfaultfd"
.Lname1342:
	.string "vm_datapart_lock_end"
.Lname1343:
	.string "devfs_lock_tryupgrade"
.Lname1344:
	.string "dbg_getregbynamep"
.Lname1346:
	.string "json_parser_enter"
.Lname1347:
	.string "sys32_utimes"
.Lname1348:
	.string "character_device_stat"
.Lname1349:
	.string "block_device_acquire_partlock_trywrite"
.Lname1350:
	.string "sys32_pwrite64f"
.Lname1351:
	.string "sys32_select"
.Lname1353:
	.string "sys_set_mempolicy"
.Lname1356:
	.string "sys32_acct"
.Lname1357:
	.string "keymap_openblob"
.Lname1358:
	.string "vm_getfutex"
.Lname1359:
	.string "validate_writablem"
.Lname1360:
	.string "kernel_locked_heap"
.Lname1361:
	.string "vm_datapart_allocram_nx"
.Lname1362:
	.string "sys_accept4"
.Lname1363:
	.string "directory_entry_alloc"
.Lname1364:
	.string "sys_utimensat"
.Lname1365:
	.string "keymap_codesize"
.Lname1369:
	.string "sys_get_mempolicy"
.Lname1370:
	.string "vm_datablock_physical_type"
.Lname1374:
	.string "path_traversen"
.Lname1375:
	.string "regdump_lcpustate"
.Lname1376:
	.string "unicode_readutf16_swap"
.Lname1378:
	.string "sys32_linux_fstat64"
.Lname1380:
	.string "mouse_device_init"
.Lname1381:
	.string "sys32_timerfd_create"
.Lname1385:
	.string "pagedir_syncall"
.Lname1386:
	.string "vm_tasklock_trywrite"
.Lname1389:
	.string "keyboard_device_putkey_nopr"
.Lname1392:
	.string "dbg_setregbynamep"
.Lname1393:
	.string "vpage_alloc_nx"
.Lname1395:
	.string "vm_datapart_writev_phys"
.Lname1396:
	.string "handle_print"
.Lname1398:
	.string "vm_syncone_locked"
.Lname1399:
	.string "validate_readable"
.Lname1401:
	.string "sys_eventfd"
.Lname1403:
	.string "mouse_device_moveto"
.Lname1404:
	.string "driver_symbol"
.Lname1407:
	.string "vm_clone"
.Lname1409:
	.string "kfree"
.Lname1411:
	.string "fs_alloc"
.Lname1412:
	.string "devfs_lock_tryread"
.Lname1413:
	.string "superblock_mountlock_tryservice"
.Lname1414:
	.string "sys32_unshare"
.Lname1416:
	.string "__cxa_end_catch"
.Lname1418:
	.string "sys_msgsnd"
.Lname1419:
	.string "x86_syscall32_lcall7"
.Lname1420:
	.string "sys_arch_prctl"
.Lname1421:
	.string "ringbuffer_unread"
.Lname1423:
	.string "sys_rt_sigqueueinfo"
.Lname1426:
	.string "vm_datapart_write_buffered"
.Lname1427:
	.string "sys32_move_pages"
.Lname1428:
	.string "acpi_sdt_count"
.Lname1429:
	.string "superblock_nodeslock_tryservice"
.Lname1430:
	.string "sys_openpty"
.Lname1432:
	.string "vpage_realloc_untraced_nx"
.Lname1433:
	.string "sys32_timer_delete"
.Lname1435:
	.string "get_current_stack"
.Lname1439:
	.string "handle_manager_clone"
.Lname1441:
	.string "kernel_syscall1_iscp"
.Lname1442:
	.string "json_writer_putnumber"
.Lname1443:
	.string "sys32_times"
.Lname1444:
	.string "devfs_lock_endread"
.Lname1445:
	.string "cred_require_vmwrite"
.Lname1446:
	.string "sys_writevf"
.Lname1447:
	.string "sys32_recvmmsg"
.Lname1448:
	.string "path_traverse_ex"
.Lname1449:
	.string "mempsetl"
.Lname1450:
	.string "task_exit"
.Lname1451:
	.string "printk"
.Lname1453:
	.string "validate_readablem"
.Lname1454:
	.string "sys_mount"
.Lname1456:
	.string "vm_datapart_map_ram_p"
.Lname1457:
	.string "vm_writephysq_unaligned"
.Lname1458:
	.string "pci_writeaddr"
.Lname1459:
	.string "vm_datapart_destroy"
.Lname1460:
	.string "ansitty_init"
.Lname1461:
	.string "getreg_kcpustate"
.Lname1463:
	.string "sys32_sendmmsg"
.Lname1464:
	.string "x86_sysroute1_asm32_sysenter"
.Lname1465:
	.string "handle_get_directory_entry"
.Lname1466:
	.string "x86_idt_modify_end"
.Lname1467:
	.string "sys32_removexattr"
.Lname1468:
	.string "sys32_mlockall"
.Lname1469:
	.string "vm_datapart_write"
.Lname1471:
	.string "kernel_panic_lcpustate"
.Lname1473:
	.string "x86_dbgidt"
.Lname1474:
	.string "mouse_buffer_putpacket_nopr"
.Lname1475:
	.string "sys_setgroups"
.Lname1476:
	.string "sys32_sigsuspend"
.Lname1477:
	.string "pagedir_unmapone"
.Lname1479:
	.string "unwind_fde_find"
.Lname1481:
	.string "sys32_poll"
.Lname1484:
	.string "sys32_mlock"
.Lname1485:
	.string "sys32_setfsuid32"
.Lname1487:
	.string "unwind_setreg_lcpustate_exclusive"
.Lname1489:
	.string "unicode_16to8"
.Lname1490:
	.string "inode_recent_tryclear"
.Lname1491:
	.string "debug_dllocksections"
.Lname1492:
	.string "sys32_getegid"
.Lname1493:
	.string "driver_delmod_inode"
.Lname1494:
	.string "format_scanf"
.Lname1495:
	.string "sys32_syslog"
.Lname1496:
	.string "pidns_write_nx"
.Lname1497:
	.string "path_lock_tryservice"
.Lname1498:
	.string "unicode_readutf16_rev_n"
.Lname1499:
	.string "vprintk"
.Lname1500:
	.string "vm_datablock_physical"
.Lname1501:
	.string "swap_write"
.Lname1503:
	.string "sys32_timer_create"
.Lname1504:
	.string "sys_clock_nanosleep"
.Lname1506:
	.string "block_device_aread_phys_sector"
.Lname1508:
	.string "path_traverse_at"
.Lname1509:
	.string "task_tryyield"
.Lname1511:
	.string "unwind_fde_load"
.Lname1512:
	.string "sys_readlinkat"
.Lname1513:
	.string "directory_getentry"
.Lname1514:
	.string "sys_uselib"
.Lname1515:
	.string "vm_datapart_lock_upgrade_nx"
.Lname1517:
	.string "sys_fsetxattr"
.Lname1518:
	.string "sys_gettimeofday"
.Lname1520:
	.string "vm_datablock_locatepart_exact"
.Lname1523:
	.string "cpu_broadcastipi_notthis"
.Lname1524:
	.string "sys_signalfd4"
.Lname1525:
	.string "mall_untrace"
.Lname1526:
	.string "syscall_emulate32"
.Lname1527:
	.string "debuginfo_cu_parser_getstring"
.Lname1528:
	.string "superblock_nodeslock_read_nx"
.Lname1529:
	.string "pagedir_fini"
.Lname1531:
	.string "sys32_lock"
.Lname1532:
	.string "x86_idt_syscall"
.Lname1533:
	.string "dbg_enter_ucpustate_cr"
.Lname1534:
	.string "sys_removexattr"
.Lname1535:
	.string "vm_datapart_loadpage"
.Lname1536:
	.string "path_umount"
.Lname1537:
	.string "kernel_panic"
.Lname1539:
	.string "this_exception_pointers"
.Lname1540:
	.string "pidns_trylookup_task_locked"
.Lname1541:
	.string "heap_free"
.Lname1542:
	.string "sys32_hopf"
.Lname1544:
	.string "mouse_device_button_ex"
.Lname1545:
	.string "sys32_gettimeofday"
.Lname1546:
	.string "vm_kernel_treelock_end"
.Lname1547:
	.string "sys_linux_fstatat"
.Lname1548:
	.string "sys32_iopl"
.Lname1549:
	.string "sys32_setitimer"
.Lname1550:
	.string "sys32_uname"
.Lname1551:
	.string "vio_copyfromvio"
.Lname1552:
	.string "vm_datablock_locatepart"
.Lname1554:
	.string "block_device_unregister"
.Lname1555:
	.string "inode_access"
.Lname1556:
	.string "sys32_wait4"
.Lname1557:
	.string "syscall_printtrace"
.Lname1558:
	.string "sys_setreuid"
.Lname1559:
	.string "rwlock_reading_any"
.Lname1560:
	.string "validate_writablem_opt"
.Lname1561:
	.string "krealign_offset"
.Lname1564:
	.string "vm86_sw_intr"
.Lname1566:
	.string "x86_fpustate_init"
.Lname1567:
	.string "sys32_fstatfs64"
.Lname1568:
	.string "sys32_eventfd"
.Lname1570:
	.string "block_device_aread_sector"
.Lname1571:
	.string "driver_clear_fde_caches"
.Lname1572:
	.string "_strtoui64"
.Lname1573:
	.string "sys_process_vm_writev"
.Lname1576:
	.string "unwind_getreg_xfpustate"
.Lname1577:
	.string "sys_security"
.Lname1578:
	.string "sys_syncfs"
.Lname1580:
	.string "task_yield"
.Lname1581:
	.string "kernel_syscall0_iscp32"
.Lname1582:
	.string "sys32_mremap"
.Lname1584:
	.string "sys32_getdents64"
.Lname1585:
	.string "sys32_inotify_rm_watch"
.Lname1586:
	.string "superblock_nodeslock_downgrade"
.Lname1587:
	.string "driver_at_address"
.Lname1588:
	.string "pagedir_unsetchanged"
.Lname1589:
	.string "dbg_enter_lcpustate"
.Lname1592:
	.string "dbg_fillbox"
.Lname1593:
	.string "sys_readahead"
.Lname1596:
	.string "character_device_ioctl"
.Lname1597:
	.string "sys_delete_module"
.Lname1599:
	.string "kernel_terminal_raise"
.Lname1602:
	.string "sys32_setgid32"
.Lname1604:
	.string "sys_getresuid"
.Lname1605:
	.string "error_active"
.Lname1606:
	.string "vm_enumdmav"
.Lname1607:
	.string "rawmemrlenq"
.Lname1608:
	.string "json_writer_endobject"
.Lname1612:
	.string "mouse_device_poll"
.Lname1613:
	.string "heap_trim"
.Lname1614:
	.string "sys32_utime"
.Lname1618:
	.string "driver_insmod_blob"
.Lname1619:
	.string "sys_remap_file_pages"
.Lname1624:
	.string "sys32_pselect6_64"
.Lname1625:
	.string "pagedir_maphint"
.Lname1626:
	.string "vmb_overlay"
.Lname1628:
	.string "terminal_owrite"
.Lname1629:
	.string "vio_cmpxch_or_writeq"
.Lname1632:
	.string "sys32_hop"
.Lname1633:
	.string "handle_trylookup"
.Lname1634:
	.string "sys_lfutexlockexpr"
.Lname1636:
	.string "cpu_quantum_end"
.Lname1638:
	.string "dbg_enter_lcpustate_r"
.Lname1639:
	.string "rawmemrlenw"
.Lname1641:
	.string "aio_multihandle_fini"
.Lname1642:
	.string "sys32_getuid32"
.Lname1644:
	.string "sys_writev"
.Lname1645:
	.string "rawmemrchr"
.Lname1648:
	.string "inode_awritev_phys"
.Lname1649:
	.string "vio_cmpxch128"
.Lname1650:
	.string "sys32_readlinkat"
.Lname1651:
	.string "krealloc"
.Lname1652:
	.string "rwlock_end"
.Lname1656:
	.string "krealloc_in_place_nx"
.Lname1657:
	.string "handle_manager_destroy"
.Lname1659:
	.string "vm_node_free"
.Lname1660:
	.string "rawmemrlenl"
.Lname1662:
	.string "sys_kexec_file_load"
.Lname1663:
	.string "fs_filesystems_lock_upgrade"
.Lname1664:
	.string "sys_io_destroy"
.Lname1667:
	.string "vm_alloc"
.Lname1668:
	.string "sys32_ulimit"
.Lname1669:
	.string "inode_chtime"
.Lname1670:
	.string "sys_io_getevents"
.Lname1672:
	.string "path_lock_upgrade_nx"
.Lname1673:
	.string "unwind_setreg_sfpustate_exclusive"
.Lname1676:
	.string "dbg_isholding_ctrl"
.Lname1678:
	.string "keymap_instrlen"
.Lname1679:
	.string "x86_memcpy_nopf_ret_pointer"
.Lname1681:
	.string "sys32_detach"
.Lname1683:
	.string "swap_sync"
.Lname1684:
	.string "abort"
.Lname1685:
	.string "vm_sync_endone"
.Lname1686:
	.string "sys32_rename"
.Lname1687:
	.string "sys32_sched_get_priority_max"
.Lname1688:
	.string "vio_readl_aligned"
.Lname1689:
	.string "__predict_update_esi"
.Lname1690:
	.string "sys_fork"
.Lname1692:
	.string "this_trampoline_page"
.Lname1695:
	.string "unwind_getreg_sfpustate"
.Lname1697:
	.string "setreg_ucpustate"
.Lname1698:
	.string "debuginfo_cu_parser_loadattr_member"
.Lname1700:
	.string "sys32_kexec_load"
.Lname1701:
	.string "path_freesize"
.Lname1703:
	.string "vm_memsetphys"
.Lname1706:
	.string "sys_flistxattr"
.Lname1707:
	.string "symlink_node_readlink"
.Lname1708:
	.string "inode_areadall"
.Lname1709:
	.string "sys32_sched_getscheduler"
.Lname1711:
	.string "mouse_device_vwheel"
.Lname1712:
	.string "sys32_getpgrp"
.Lname1713:
	.string "task_alloc_user_rpc_nx"
.Lname1715:
	.string "superblock_clear_caches"
.Lname1716:
	.string "path_sprint"
.Lname1717:
	.string "getreg_lcpustate"
.Lname1718:
	.string "debuginfo_cu_parser_getref"
.Lname1719:
	.string "vfs_clearmounts"
.Lname1720:
	.string "sys_adjtimex"
.Lname1721:
	.string "sys_frenameat"
.Lname1725:
	.string "this_vm"
.Lname1727:
	.string "x86_sysroute0_asm32_int80"
.Lname1729:
	.string "sys_inotify_init1"
.Lname1730:
	.string "block_device_areadv_phys_sector"
.Lname1732:
	.string "page_isfree"
.Lname1733:
	.string "dbg_hline"
.Lname1741:
	.string "sys_sysinfo"
.Lname1742:
	.string "sys_acct"
.Lname1744:
	.string "sys32_vhangup"
.Lname1745:
	.string "sys32_get_thread_area"
.Lname1746:
	.string "dbg_fillrect2"
.Lname1747:
	.string "slab_malloc"
.Lname1748:
	.string "dbg_print"
.Lname1749:
	.string "inode_recent"
.Lname1751:
	.string "vm_datablock_vio_writev_phys"
.Lname1753:
	.string "pipe_max_bufsize_unprivileged"
.Lname1755:
	.string "syscall_emulate"
.Lname1758:
	.string "sys32_open"
.Lname1759:
	.string "character_device_pwrite"
.Lname1761:
	.string "vio_orq"
.Lname1762:
	.string "sys_set_exception_handler"
.Lname1763:
	.string "pty_alloc"
.Lname1764:
	.string "x86_dbg_getregbyid"
.Lname1765:
	.string "coredump_create"
.Lname1766:
	.string "regdump_dr6"
.Lname1767:
	.string "regdump_dr7"
.Lname1771:
	.string "sys32_fork"
.Lname1772:
	.string "sys32_ftruncate"
.Lname1774:
	.string "path_lock_read_nx"
.Lname1775:
	.string "vio_copytovio"
.Lname1776:
	.string "sys32_getxattr"
.Lname1778:
	.string "vio_orb"
.Lname1779:
	.string "aio_pbuffer_copytophys"
.Lname1780:
	.string "sys32_fchownat"
.Lname1781:
	.string "get_stack_inuse"
.Lname1782:
	.string "vm_pagetophys_nopf"
.Lname1783:
	.string "vm_pagefromphys"
.Lname1785:
	.string "pidns_root"
.Lname1787:
	.string "strto32"
.Lname1788:
	.string "sys_restart_syscall"
.Lname1789:
	.string "thiscpu_current"
.Lname1791:
	.string "inode_file_writev_with_write"
.Lname1794:
	.string "ringbuffer_read_nonblock"
.Lname1795:
	.string "handle_get_fs"
.Lname1796:
	.string "callback_list_insert"
.Lname1797:
	.string "sys_ptrace"
.Lname1798:
	.string "vio_andw"
.Lname1800:
	.string "sys_detach"
.Lname1801:
	.string "dbg_getfunc_fuzzy"
.Lname1803:
	.string "x86_sysroute1_asm64_syscall"
.Lname1809:
	.string "vio_cmpxch_or_writew"
.Lname1810:
	.string "sys_fgetxattr"
.Lname1811:
	.string "block_device_sync"
.Lname1812:
	.string "sig_altsend"
.Lname1813:
	.string "superblock_nodeslock_endread"
.Lname1814:
	.string "sys32_frealpath4"
.Lname1815:
	.string "sys32_gtty"
.Lname1816:
	.string "aio_multihandle_allochandle_nx"
.Lname1817:
	.string "userkern_segment_part"
.Lname1819:
	.string "pidns_write"
.Lname1820:
	.string "sys_setregid"
.Lname1821:
	.string "sys_llistxattr"
.Lname1825:
	.string "sys_inotify_init"
.Lname1826:
	.string "sys32_pwritevf"
.Lname1827:
	.string "tty_device_alloc"
.Lname1828:
	.string "syscall_printtrace_compat"
.Lname1829:
	.string "json_parser_state"
.Lname1830:
	.string "sys_preadv"
.Lname1831:
	.string "mempcpyq"
.Lname1832:
	.string "slab_kmalloc16"
.Lname1833:
	.string "dbg_pputuni"
.Lname1834:
	.string "vm_oninit_callbacks"
.Lname1835:
	.string "sys_symlink"
.Lname1839:
	.string "x86_bootcpu_gdt"
.Lname1841:
	.string "zlib_reader_setpos"
.Lname1842:
	.string "x86_fxrstor"
.Lname1843:
	.string "task_popconnections"
.Lname1844:
	.string "sys32_sched_rr_get_interval64"
.Lname1845:
	.string "vm_kernel_treelock_endwrite"
.Lname1846:
	.string "vm_datablock_vio_readv"
.Lname1847:
	.string "ttybase_device_setctty"
.Lname1849:
	.string "ansitty_putuni"
.Lname1850:
	.string "vm_library_enumerate"
.Lname1851:
	.string "ringbuffer_rseek"
.Lname1852:
	.string "this_taskgroup"
.Lname1853:
	.string "sys32_lchown"
.Lname1854:
	.string "sys32_perf_event_open"
.Lname1855:
	.string "ramfs_directory_type"
.Lname1857:
	.string "pagedir_unmapone_p"
.Lname1858:
	.string "vm_kernel_treelock_read"
.Lname1860:
	.string "path_sprintent"
.Lname1861:
	.string "fs_filesystems_lock_tryupgrade"
.Lname1865:
	.string "handle_fcntl"
.Lname1868:
	.string "keyboard_device_poll"
.Lname1869:
	.string "handle_close_nosym"
.Lname1872:
	.string "pidns_lookup"
.Lname1875:
	.string "vm_datapart_read_phys"
.Lname1876:
	.string "sys32_io_submit"
.Lname1877:
	.string "thiscpu_x86_iob"
.Lname1881:
	.string "isr_unregister_at"
.Lname1884:
	.string "coredump_create_for_signal"
.Lname1885:
	.string "vm_enumdma"
.Lname1887:
	.string "json_encode"
.Lname1888:
	.string "getreg_gpregsnsp"
.Lname1889:
	.string "sys32_setgid"
.Lname1890:
	.string "vm_free"
.Lname1891:
	.string "inode_tryaccess"
.Lname1892:
	.string "task_trywait"
.Lname1896:
	.string "superblock_mountlock_read_nx"
.Lname1898:
	.string "sys_personality"
.Lname1900:
	.string "rawmemchrl"
.Lname1902:
	.string "vm_datapart_lockread_setcore_nx"
.Lname1904:
	.string "vm_startdma"
.Lname1905:
	.string "rawmemchrq"
.Lname1907:
	.string "thiscpu_x86_cpuid"
.Lname1908:
	.string "sys32_ftruncate64"
.Lname1909:
	.string "sys32_clock_settime"
.Lname1910:
	.string "zlib_reader_feed"
.Lname1911:
	.string "rawmemchrw"
.Lname1913:
	.string "inode_changed"
.Lname1916:
	.string "x86_fsgsbase_patch"
.Lname1918:
	.string "sys_munlockall"
.Lname1919:
	.string "task_wake"
.Lname1921:
	.string "sys32_inotify_init1"
.Lname1924:
	.string "sys32_ppoll64"
.Lname1925:
	.string "debuginfo_cu_parser_loadattr_inlined_subroutine"
.Lname1929:
	.string "sys32_recvmmsg64"
.Lname1931:
	.string "x86_sysroute0_asm32_sysenter"
.Lname1932:
	.string "memcpyl"
.Lname1933:
	.string "sys32_chown32"
.Lname1934:
	.string "sys32_fanotify_init"
.Lname1935:
	.string "sys32_flock"
.Lname1937:
	.string "vsprintf_s"
.Lname1939:
	.string "sys_mq_notify"
.Lname1940:
	.string "sys_pwrite64"
.Lname1941:
	.string "block_device_lookup_name"
.Lname1942:
	.string "addr2line_vprintf"
.Lname1944:
	.string "sys32_sched_setscheduler"
.Lname1945:
	.string "heap_free_untraced"
.Lname1946:
	.string "sys_setpriority"
.Lname1947:
	.string "sys_getrlimit"
.Lname1948:
	.string "__afail"
.Lname1950:
	.string "mempatw"
.Lname1951:
	.string "sys_vmsplice"
.Lname1952:
	.string "sys_vhangup"
.Lname1954:
	.string "dbg_printer"
.Lname1955:
	.string "sys_mlock"
.Lname1956:
	.string "sigmask_check_after_except"
.Lname1957:
	.string "kernel_debugtrap_r_kcpustate"
.Lname1959:
	.string "x86_userexcept_unwind"
.Lname1963:
	.string "sys_pread64"
.Lname1964:
	.string "sys_sync_file_range"
.Lname1965:
	.string "ttybase_device_cinit"
.Lname1966:
	.string "sighand_default_action"
.Lname1968:
	.string "vpage_alloc_untraced_nx"
.Lname1970:
	.string "unicode_8to32"
.Lname1971:
	.string "path_alloc"
.Lname1972:
	.string "sys32_fcntl64"
.Lname1973:
	.string "cmdline_decode"
.Lname1974:
	.string "sys32_process_vm_readv"
.Lname1975:
	.string "page_cfree"
.Lname1977:
	.string "getreg_ucpustate"
.Lname1980:
	.string "sys_readv"
.Lname1983:
	.string "kernel_panic_kcpustate"
.Lname1984:
	.string "sys_getpgrp"
.Lname1988:
	.string "pci_list"
.Lname1989:
	.string "block_device_partition_write"
.Lname1990:
	.string "sys_readlink"
.Lname1993:
	.string "krealloc_nx"
.Lname1995:
	.string "sys32_rt_sigprocmask"
.Lname1998:
	.string "sys_swapon"
.Lname2001:
	.string "handle_get_path"
.Lname2003:
	.string "sys32_getdents"
.Lname2004:
	.string "instruction_pred"
.Lname2005:
	.string "ramfs_regular_type"
.Lname2006:
	.string "system_trimheaps"
.Lname2007:
	.string "dbg_applyview"
.Lname2008:
	.string "kmalloc_nx"
.Lname2009:
	.string "sys32_lseek64"
.Lname2011:
	.string "vm_memset"
.Lname2015:
	.string "register_filesystem_type"
.Lname2016:
	.string "regdump_cr0"
.Lname2019:
	.string "superblock_sync"
.Lname2020:
	.string "ansitty_device_cinit"
.Lname2021:
	.string "pci_getclassname"
.Lname2022:
	.string "vmb_getnodeof"
.Lname2024:
	.string "character_device_lookup_nx"
.Lname2025:
	.string "sys__sysctl"
.Lname2027:
	.string "pidns_lookup_task"
.Lname2030:
	.string "vm_datapart_haschanged"
.Lname2031:
	.string "swap_free"
.Lname2032:
	.string "unwind_setreg_scpustate"
.Lname2033:
	.string "this_exception_data"
.Lname2036:
	.string "inode_chmod"
.Lname2037:
	.string "thiscpu_x86_iobnode"
.Lname2039:
	.string "sys32_lookup_dcookie"
.Lname2041:
	.string "sys32_getgid"
.Lname2043:
	.string "thisvm_execinfo"
.Lname2046:
	.string "superblock_nodeslock_upgrade"
.Lname2048:
	.string "thiscpu_x86_ioperm_bitmap"
.Lname2049:
	.string "mempmoveupq"
.Lname2051:
	.string "block_device_awritev_phys"
.Lname2052:
	.string "handle_typekind"
.Lname2053:
	.string "block_device_awrite"
.Lname2054:
	.string "__vsnprintf"
.Lname2055:
	.string "mempmoveupw"
.Lname2060:
	.string "sys32_name_to_handle_at"
.Lname2061:
	.string "sys32_bpf"
.Lname2062:
	.string "sys_shmget"
.Lname2065:
	.string "sys_gettid"
.Lname2067:
	.string "sys_migrate_pages"
.Lname2068:
	.string "keyboard_device_read"
.Lname2069:
	.string "cred_require_resource"
.Lname2071:
	.string "vm_readphysw"
.Lname2072:
	.string "heap_realign_untraced_nx"
.Lname2073:
	.string "sys32_klstat"
.Lname2074:
	.string "this_tid_address"
.Lname2075:
	.string "vm_protect"
.Lname2076:
	.string "json_parser_getbool"
.Lname2077:
	.string "aio_pbuffer_copytomem"
.Lname2078:
	.string "sys32_timer_settime"
.Lname2079:
	.string "unwind"
.Lname2080:
	.string "vm_datablock_writep"
.Lname2082:
	.string "handle_type_db"
.Lname2083:
	.string "thiscpu_x86_cpufeatures"
.Lname2084:
	.string "rwlock_read"
.Lname2085:
	.string "pidns_tryservice"
.Lname2086:
	.string "vm_datablock_writev"
.Lname2087:
	.string "vpage_realloc_untraced"
.Lname2088:
	.string "sys32_pwrite64"
.Lname2090:
	.string "vm_datapart_write_unsafe"
.Lname2091:
	.string "vsprintf"
.Lname2092:
	.string "vm_readphysl"
.Lname2093:
	.string "x86_syscall32_sysenter"
.Lname2095:
	.string "sys_getrusage"
.Lname2101:
	.string "dbg_enter_fcpustate"
.Lname2102:
	.string "sys_msgrcv"
.Lname2104:
	.string "format_width"
.Lname2105:
	.string "ringbuffer_read"
.Lname2108:
	.string "sys32_sendmsg"
.Lname2109:
	.string "sys32_settimeofday64"
.Lname2110:
	.string "mall_untrace_n"
.Lname2111:
	.string "memmove"
.Lname2112:
	.string "pagedir_translate_p"
.Lname2114:
	.string "isr_unregister"
.Lname2115:
	.string "dump_branch_stats"
.Lname2116:
	.string "json_writer_putint64"
.Lname2117:
	.string "kernel_vpanic_icpustate"
.Lname2118:
	.string "sys_get_exception_handler"
.Lname2119:
	.string "vfs_kernel"
.Lname2122:
	.string "sys32_fsmode"
.Lname2124:
	.string "ansitty_device_ioctl"
.Lname2125:
	.string "task_gethandlemanager"
.Lname2128:
	.string "pagedir_maphint_p"
.Lname2130:
	.string "cpu_enable_preemptive_interrupts_nopr"
.Lname2131:
	.string "sys32_clock_getres"
.Lname2132:
	.string "dbg_hexedit"
.Lname2133:
	.string "dbg_getregbyname"
.Lname2135:
	.string "sys_epoll_wait_old"
.Lname2136:
	.string "sys_waitid"
.Lname2137:
	.string "sys_setsid"
.Lname2138:
	.string "userkern_segment_vio"
.Lname2139:
	.string "sys32_symlink"
.Lname2140:
	.string "vmb_find_first_node_greater_equal"
.Lname2142:
	.string "path_lock_trywrite"
.Lname2143:
	.string "debuginfo_print_value"
.Lname2144:
	.string "x86_userexcept_unwind_interrupt_kernel_esp"
.Lname2148:
	.string "json_parser_rewind"
.Lname2149:
	.string "x86_dbg_exitstate"
.Lname2150:
	.string "sys32_pread64f"
.Lname2151:
	.string "handle_installxchg"
.Lname2152:
	.string "x86_idt_ptr"
.Lname2153:
	.string "vm_futex_destroy"
.Lname2158:
	.string "x86_syscall_emulate32_sysenter_r"
.Lname2160:
	.string "pagedir_unmap_p"
.Lname2161:
	.string "memcpyq"
.Lname2163:
	.string "block_device_partition_write_phys"
.Lname2164:
	.string "superblock_mountlock_endread"
.Lname2165:
	.string "disasm_single"
.Lname2166:
	.string "cpu_schedule_idle_job_and_incref"
.Lname2167:
	.string "memcpyw"
.Lname2169:
	.string "symlink_node_load"
.Lname2173:
	.string "sys_sched_setparam"
.Lname2176:
	.string "ttybase_device_owrite"
.Lname2177:
	.string "superblock_mountlock_read"
.Lname2178:
	.string "inode_loadattr"
.Lname2179:
	.string "kernel_vpanic"
.Lname2180:
	.string "dbg_pprint"
.Lname2182:
	.string "vio_writeq_aligned"
.Lname2183:
	.string "task_exec_asynchronous_rpc"
.Lname2184:
	.string "vm_ramfile_type"
.Lname2187:
	.string "vm_clrhwbreak"
.Lname2188:
	.string "disasm_print_symbol"
.Lname2189:
	.string "keyboard_buffer_putkey_nopr"
.Lname2191:
	.string "dbg_enter_lcpustate_cr"
.Lname2192:
	.string "sys_semtimedop"
.Lname2194:
	.string "directory_mkdir"
.Lname2195:
	.string "vm_exec"
.Lname2196:
	.string "terminal_iread"
.Lname2197:
	.string "dbg_scroll_maxline"
.Lname2198:
	.string "vm_datablock_readv"
.Lname2199:
	.string "vm_datapart_lock_tryread"
.Lname2200:
	.string "task_schedule_user_rpc_nx"
.Lname2201:
	.string "sys32_getrlimit"
.Lname2202:
	.string "this_sched_runprv"
.Lname2204:
	.string "driver_initialize"
.Lname2205:
	.string "disasm"
.Lname2206:
	.string "vm_syncall_locked"
.Lname2207:
	.string "dbg_vline"
.Lname2208:
	.string "pagedir_haschanged_p"
.Lname2209:
	.string "memrchrq"
.Lname2210:
	.string "vio_cmpxchb"
.Lname2211:
	.string "kernel_debug_sections"
.Lname2212:
	.string "sys_fanotify_init"
.Lname2213:
	.string "debuginfo_cu_parser_loadattr_variable"
.Lname2214:
	.string "setreg_sfpuenv"
.Lname2215:
	.string "memrchrw"
.Lname2216:
	.string "cpu_private_function_do_finibuf_ex"
.Lname2219:
	.string "zlib_reader_fini"
.Lname2220:
	.string "json_writer_putbool"
.Lname2221:
	.string "rawmemchr"
.Lname2223:
	.string "path_lock_end"
.Lname2226:
	.string "vm_datapart_map_ram"
.Lname2227:
	.string "path_lock_upgrade"
.Lname2228:
	.string "sys_shmdt"
.Lname2229:
	.string "getreg_fcpustate"
.Lname2230:
	.string "vm_datapart_write_nopf"
.Lname2231:
	.string "rwlock_reading"
.Lname2233:
	.string "sys32_inotify_init"
.Lname2235:
	.string "sys_clone"
.Lname2236:
	.string "memrchrl"
.Lname2239:
	.string "pidns_trywrite"
.Lname2241:
	.string "mempatq"
.Lname2242:
	.string "sys_listxattr"
.Lname2243:
	.string "error_subclass"
.Lname2244:
	.string "sys32_mq_timedsend"
.Lname2245:
	.string "superblock_opennode"
.Lname2246:
	.string "dbg_pprintf"
.Lname2247:
	.string "memlenq"
.Lname2248:
	.string "heap_allat_untraced_nx"
.Lname2251:
	.string "sys_capset"
.Lname2253:
	.string "sys_mkdirat"
.Lname2255:
	.string "sys32_setuid"
.Lname2256:
	.string "task_raisesignalthread_nx"
.Lname2257:
	.string "heap_allat_nx"
.Lname2258:
	.string "sys32_flistxattr"
.Lname2259:
	.string "block_device_alloc"
.Lname2260:
	.string "vm_datablock_createpart"
.Lname2261:
	.string "ringbuffer_writesome"
.Lname2262:
	.string "unicode_readutf16_swap_rev"
.Lname2264:
	.string "dbg_screen_width"
.Lname2267:
	.string "vio_orl"
.Lname2268:
	.string "mempatl"
.Lname2270:
	.string "sys32_linux_oldstat"
.Lname2271:
	.string "handle_datasize"
.Lname2274:
	.string "cpu_quantum_reset_nopr"
.Lname2275:
	.string "inode_read_phys"
.Lname2276:
	.string "path_traversefull_at"
.Lname2277:
	.string "unwind_getreg_scpustate"
.Lname2280:
	.string "unicode_readutf8"
.Lname2283:
	.string "sys_unshare"
.Lname2284:
	.string "kernel_debugtraps_install"
.Lname2285:
	.string "sys_getrandom"
.Lname2286:
	.string "vm_memsetphys_onepage"
.Lname2288:
	.string "kernel_syscall0_iscp"
.Lname2289:
	.string "sys_getpgid"
.Lname2291:
	.string "dbg_enter_icpustate_c"
.Lname2292:
	.string "json_parser_init"
.Lname2293:
	.string "kernel_debugtrap_scpustate"
.Lname2296:
	.string "sys_inotify_rm_watch"
.Lname2297:
	.string "sys32_fchmod"
.Lname2302:
	.string "krealign"
.Lname2307:
	.string "vm_datablock_debugheap_type"
.Lname2308:
	.string "heap_allat"
.Lname2310:
	.string "sys32_kreaddirf"
.Lname2312:
	.string "kmalloc_noslab_nx"
.Lname2313:
	.string "sighand_ptr_destroy"
.Lname2314:
	.string "sys32_truncate64"
.Lname2317:
	.string "task_start"
.Lname2319:
	.string "kmalloc_usable_size"
.Lname2322:
	.string "sys_epoll_create"
.Lname2323:
	.string "keyboard_device_readchars"
.Lname2324:
	.string "sys32_fadvise64_64"
.Lname2325:
	.string "cpu_apply_scpustate"
.Lname2326:
	.string "dbg_addr2line_vprintf"
.Lname2327:
	.string "keyboard_device_getkey"
.Lname2328:
	.string "vm_kernel_treelock_writef_nx"
.Lname2329:
	.string "dbg_getkey"
.Lname2330:
	.string "terminal_poll_owrite"
.Lname2332:
	.string "sys_sched_rr_get_interval"
.Lname2333:
	.string "vm_futex_broadcast"
.Lname2334:
	.string "sys_reboot"
.Lname2335:
	.string "this_kernel_stacknode"
.Lname2336:
	.string "pagedir_isuseraccessible_p"
.Lname2337:
	.string "sys_mmap"
.Lname2339:
	.string "block_device_read_phys"
.Lname2340:
	.string "cpu_quantum_reset"
.Lname2341:
	.string "ansitty_translate"
.Lname2342:
	.string "sys_sched_getscheduler"
.Lname2345:
	.string "ringbuffer_wseek"
.Lname2347:
	.string "vm86_inw"
.Lname2348:
	.string "fs_kernel"
.Lname2349:
	.string "pci_readaddr"
.Lname2350:
	.string "kernel_version"
.Lname2351:
	.string "rwlock_write"
.Lname2352:
	.string "sys32_debugtrap"
.Lname2353:
	.string "heap_realign_nx"
.Lname2354:
	.string "sys32_vm86old"
.Lname2355:
	.string "sys_access"
.Lname2356:
	.string "sys32_setresuid"
.Lname2357:
	.string "boot_device"
.Lname2358:
	.string "sys32_prof"
.Lname2361:
	.string "sighand_ptr_lockread"
.Lname2363:
	.string "sys32_rt_sigqueueinfo"
.Lname2365:
	.string "tty_device_startfwd"
.Lname2367:
	.string "error_code"
.Lname2368:
	.string "sys32_finit_module"
.Lname2369:
	.string "vm_kernel_treelock_trywrite"
.Lname2370:
	.string "path_recent_clear"
.Lname2371:
	.string "superblock_mountlock_tryread"
.Lname2372:
	.string "cpu_sendipi_cpuset"
.Lname2373:
	.string "superblock_nodeslock_endwrite"
.Lname2376:
	.string "sys_rt_sigsuspend"
.Lname2377:
	.string "x86_syscall_emulate32_cdecl"
.Lname2379:
	.string "cpu_addpendingtask"
.Lname2380:
	.string "quantum_global_to_local"
.Lname2381:
	.string "aio_pbuffer_copytovmem"
.Lname2387:
	.string "sys32_select64"
.Lname2388:
	.string "debuginfo_cu_parser_loadunit"
.Lname2389:
	.string "devfs_lock_upgrade"
.Lname2391:
	.string "pipe_destroy"
.Lname2392:
	.string "vm_datablock_write"
.Lname2393:
	.string "json_parser_enterobject"
.Lname2394:
	.string "this_idle_sched_state"
.Lname2396:
	.string "ttybase_device_tryioctl"
.Lname2399:
	.string "vio_writeb"
.Lname2400:
	.string "sys_semop"
.Lname2402:
	.string "inode_recent_clear"
.Lname2403:
	.string "block_device_read_sync"
.Lname2404:
	.string "sys_getsid"
.Lname2407:
	.string "vm_tasklock_write"
.Lname2409:
	.string "path_newchild"
.Lname2410:
	.string "unwind_setreg_xfpustate_exclusive"
.Lname2411:
	.string "json_parser_yield"
.Lname2415:
	.string "sys_get_robust_list"
.Lname2417:
	.string "setreg_lcpustate"
.Lname2418:
	.string "sys_mlock2"
.Lname2419:
	.string "vm_datablock_vio_readv_phys"
.Lname2420:
	.string "block_device_acquire_partlock_read"
.Lname2423:
	.string "sys32_open_by_handle_at"
.Lname2424:
	.string "vpage_realloc_nx"
.Lname2425:
	.string "sys_fchdir"
.Lname2427:
	.string "sys_accept"
.Lname2428:
	.string "sys_socketpair"
.Lname2431:
	.string "vpage_alloc"
.Lname2433:
	.string "ringbuffer_write"
.Lname2434:
	.string "memrchr"
.Lname2435:
	.string "ringbuffer_write_nonblock"
.Lname2437:
	.string "sys_time"
.Lname2439:
	.string "vio_subq"
.Lname2440:
	.string "vm_kernel_treelock_upgrade_nx"
.Lname2441:
	.string "vm_datapart_lock_tryupgrade"
.Lname2442:
	.string "vm_isused"
.Lname2443:
	.string "sys32_ssetmask"
.Lname2444:
	.string "vm_kernel"
.Lname2445:
	.string "fpustate32_loadfrom"
.Lname2448:
	.string "sys32_io_setup"
.Lname2449:
	.string "vm_datapart_do_write"
.Lname2450:
	.string "vm86_inb"
.Lname2451:
	.string "task_push_asynchronous_rpc"
.Lname2452:
	.string "vio_memset"
.Lname2455:
	.string "vm_datapart_do_write_phys"
.Lname2456:
	.string "sys32_break"
.Lname2457:
	.string "json_writer_beginarray"
.Lname2458:
	.string "sys32_symlinkat"
.Lname2459:
	.string "directory_symlink"
.Lname2460:
	.string "sys_kill"
.Lname2463:
	.string "sys32_execve"
.Lname2464:
	.string "task_connect"
.Lname2466:
	.string "sys_linkat"
.Lname2467:
	.string "block_device_write_phys_sync"
.Lname2468:
	.string "dbg_exit"
.Lname2469:
	.string "kernel_debugtrap_r_icpustate"
.Lname2473:
	.string "setreg_fcpustate"
.Lname2475:
	.string "vio_subw"
.Lname2477:
	.string "unwind_fde_exec"
.Lname2480:
	.string "sys32_exit_group"
.Lname2481:
	.string "regdump_ucpustate"
.Lname2482:
	.string "sys_eventfd2"
.Lname2483:
	.string "driver_loaded_callbacks"
.Lname2484:
	.string "mempset"
.Lname2485:
	.string "pagedir_pop_mapone"
.Lname2487:
	.string "sys32_rt_sigpending"
.Lname2488:
	.string "krealign_offset_nx"
.Lname2489:
	.string "debuginfo_cu_abbrev_fini"
.Lname2491:
	.string "sys32_sgetmask"
.Lname2493:
	.string "ringbuffer_poll"
.Lname2494:
	.string "heap_realign"
.Lname2495:
	.string "vm_datapart_lockwrite_setcore"
.Lname2498:
	.string "getreg_coregs"
.Lname2499:
	.string "block_device_partition_writev_phys"
.Lname2500:
	.string "kmemalign_offset"
.Lname2501:
	.string "devfs_lock_write"
.Lname2504:
	.string "kmemalign_offset_nx"
.Lname2505:
	.string "superblock_nodeslock_tryupgrade"
.Lname2507:
	.string "x86_sysroute0_asm64_syscall"
.Lname2509:
	.string "sys32_geteuid32"
.Lname2510:
	.string "mouse_device_button"
.Lname2512:
	.string "unwind_emulator_exec_autostack"
.Lname2513:
	.string "vm_writephysq"
.Lname2514:
	.string "cpu_quantum_remaining_nopr"
.Lname2515:
	.string "this_read_locks"
.Lname2516:
	.string "unwind_getreg_icpustate_exclusive"
.Lname2517:
	.string "debugaranges_locate"
.Lname2519:
	.string "vm_writephysw"
.Lname2520:
	.string "inode_recent_clear_nx"
.Lname2521:
	.string "swap_read"
.Lname2522:
	.string "x86_userexcept_unwind_i"
.Lname2523:
	.string "sys32_linux_oldfstat"
.Lname2524:
	.string "vm_copyinphys"
.Lname2526:
	.string "page_free"
.Lname2527:
	.string "fpustate32_saveinto"
.Lname2528:
	.string "sys_mknod"
.Lname2530:
	.string "setreg_sgregs"
.Lname2531:
	.string "sys32_fdatasync"
.Lname2532:
	.string "dbg_isholding_alt"
.Lname2533:
	.string "addr2line"
.Lname2534:
	.string "vm_datapart_writev"
.Lname2535:
	.string "format_escape"
.Lname2537:
	.string "sys32_add_key"
.Lname2540:
	.string "vm_writephysl"
.Lname2541:
	.string "sys_kreaddirf"
.Lname2542:
	.string "vm_enumdmav_nx"
.Lname2543:
	.string "this_kernel_stackpart"
.Lname2545:
	.string "sys32_setresuid32"
.Lname2546:
	.string "memchr"
.Lname2547:
	.string "sys32_statfs"
.Lname2548:
	.string "sys32_execveat"
.Lname2549:
	.string "kernel_panic_ucpustate"
.Lname2552:
	.string "x86_bootcpu_cpuid"
.Lname2553:
	.string "sys32_getcwd"
.Lname2555:
	.string "sys_brk"
.Lname2556:
	.string "sys_io_cancel"
.Lname2558:
	.string "sys_timer_delete"
.Lname2559:
	.string "sys_timer_create"
.Lname2561:
	.string "pagedir_unmap_userspace_p"
.Lname2562:
	.string "debuginfo_cu_parser_getaddr"
.Lname2563:
	.string "dbg_getc"
.Lname2564:
	.string "sys32_fmkdirat"
.Lname2565:
	.string "serial_probe"
.Lname2566:
	.string "task_exec_asynchronous_rpc_v"
.Lname2567:
	.string "sys32_setreuid"
.Lname2568:
	.string "vm_datapart_do_allocram_nx"
.Lname2569:
	.string "mempcpy"
.Lname2570:
	.string "x86_sysroute0_c"
.Lname2571:
	.string "inode_readv_blocking"
.Lname2572:
	.string "x86_setiopl"
.Lname2573:
	.string "sys32_ioperm"
.Lname2574:
	.string "x86_rpc_user_redirection"
.Lname2575:
	.string "superblock_nodeslock_trywrite"
.Lname2578:
	.string "krand_r"
.Lname2579:
	.string "driver_unloaded_callbacks"
.Lname2580:
	.string "heap_align_untraced"
.Lname2581:
	.string "inode_awrite"
.Lname2582:
	.string "ioperm_bitmap_allocf"
.Lname2583:
	.string "ttybase_device_fini"
.Lname2584:
	.string "dbg_putuni"
.Lname2585:
	.string "dbg_current"
.Lname2587:
	.string "sys32__newselect"
.Lname2588:
	.string "task_detach_children"
.Lname2591:
	.string "sys_splice"
.Lname2592:
	.string "sys32_kcmp"
.Lname2595:
	.string "sys32_access"
.Lname2596:
	.string "json_writer_beginobject"
.Lname2598:
	.string "sys32_process_vm_writev"
.Lname2599:
	.string "sys_set_thread_area"
.Lname2601:
	.string "ttybase_device_hupctty"
.Lname2602:
	.string "task_raisesignalprocess"
.Lname2603:
	.string "debuginfo_cu_parser_loadattr_lexical_block"
.Lname2604:
	.string "memmovedownl"
.Lname2605:
	.string "sys32_lfutexlockexpr"
.Lname2606:
	.string "sys_listen"
.Lname2609:
	.string "memmovedownq"
.Lname2611:
	.string "ioperm_bitmap_alloc"
.Lname2612:
	.string "_strtoi64"
.Lname2613:
	.string "path_getcasechild_or_parent_inode"
.Lname2615:
	.string "dbg_ungetkey"
.Lname2616:
	.string "sys32_socket"
.Lname2617:
	.string "dbg_trygetkey"
.Lname2618:
	.string "unicode_readutf16_rev"
.Lname2619:
	.string "cred_require_hwio"
.Lname2620:
	.string "sys_keyctl"
.Lname2622:
	.string "devfs_lock_downgrade"
.Lname2623:
	.string "regdump_fcpustate"
.Lname2624:
	.string "bcmp"
.Lname2625:
	.string "mempmovedownq"
.Lname2627:
	.string "sys_statfs"
.Lname2628:
	.string "sys_getcwd"
.Lname2629:
	.string "pagedir_iswritable"
.Lname2631:
	.string "cpu_swipi_pending"
.Lname2633:
	.string "empty_directory_entry"
.Lname2636:
	.string "sys32_tkill"
.Lname2637:
	.string "sys32_fgetxattr"
.Lname2638:
	.string "handle_lookupin"
.Lname2639:
	.string "vm_datablock_findchanged"
.Lname2640:
	.string "x86_dbg_trapstatekind"
.Lname2641:
	.string "superblock_mountlock_tryupgrade"
.Lname2642:
	.string "dbg_isholding_altgr"
.Lname2643:
	.string "task_connect_c"
.Lname2644:
	.string "json_parser_unyield"
.Lname2645:
	.string "sys32_ftime"
.Lname2646:
	.string "memeq_nopf"
.Lname2648:
	.string "sys_lfutex"
.Lname2649:
	.string "zlib_reader_rewind"
.Lname2651:
	.string "dbg_enter_scpustate_c"
.Lname2652:
	.string "mempmovedownl"
.Lname2654:
	.string "rawmemrlen"
.Lname2655:
	.string "sighand_ptr_lockwrite"
.Lname2656:
	.string "block_device_lookup"
.Lname2657:
	.string "sys_hop"
.Lname2658:
	.string "kernel_syscall1_iscp32"
.Lname2660:
	.string "sys_epoll_ctl_old"
.Lname2661:
	.string "sys32_setregid32"
.Lname2664:
	.string "x86_syscall_emulate32_int80h"
.Lname2666:
	.string "vm_find_first_node_greater_equal"
.Lname2667:
	.string "sys_kreaddir"
.Lname2668:
	.string "json_parser_getnull"
.Lname2669:
	.string "sys32_recvfrom"
.Lname2670:
	.string "task_waitfor_norpc"
.Lname2672:
	.string "sys32_coredump"
.Lname2674:
	.string "sys_setitimer"
.Lname2675:
	.string "dbg_getfunc"
.Lname2676:
	.string "debugline_scanunit"
.Lname2677:
	.string "path_getchild_or_parent_inode"
.Lname2678:
	.string "__afailf"
.Lname2679:
	.string "cpu_hwipi_pending"
.Lname2680:
	.string "sys32_futimesat"
.Lname2681:
	.string "memcpy"
.Lname2683:
	.string "cpu_delrunningtask"
.Lname2684:
	.string "pipe_reader_create"
.Lname2686:
	.string "sys_openat"
.Lname2687:
	.string "page_freeone"
.Lname2688:
	.string "pagedir_mapone_p"
.Lname2689:
	.string "x86_dbg_hostbackup"
.Lname2690:
	.string "sys32_getresgid32"
.Lname2693:
	.string "cpu_ipi_service"
.Lname2694:
	.string "sys_getuid"
.Lname2695:
	.string "dbg"
.Lname2696:
	.string "task_alloc_user_rpc"
.Lname2697:
	.string "vm_datapart_freeswap"
.Lname2701:
	.string "sys32_sched_setattr"
.Lname2703:
	.string "sys32_mount"
.Lname2705:
	.string "vio_writeq"
.Lname2706:
	.string "mouse_device_motion_nopr"
.Lname2707:
	.string "error_class"
.Lname2708:
	.string "dbg_screen_height"
.Lname2709:
	.string "kernel_syscall1_restartmode"
.Lname2710:
	.string "cpu_private_function_callbuf"
.Lname2711:
	.string "sys32_request_key"
.Lname2713:
	.string "memset"
.Lname2715:
	.string "sys_afs_syscall"
.Lname2717:
	.string "vm_tasklock_endwrite"
.Lname2718:
	.string "x86_userexcept_raisesignal_from_exception"
.Lname2719:
	.string "pagedir_isuseraccessible"
.Lname2720:
	.string "directory_getcaseentry_p"
.Lname2722:
	.string "vio_readb"
.Lname2723:
	.string "x86_dbgidt_ptr"
.Lname2725:
	.string "kernel_debugtrap_r_fcpustate"
.Lname2726:
	.string "vm_datapart_lockread_setcore_unsharecow_nx"
.Lname2727:
	.string "slab_kmalloc_nx64"
.Lname2728:
	.string "path_sprintentex"
.Lname2729:
	.string "x86_getiopl"
.Lname2731:
	.string "cpu_addrunningtask"
.Lname2732:
	.string "sys32_tgkill"
.Lname2733:
	.string "path_free"
.Lname2737:
	.string "sys32_sched_getattr"
.Lname2738:
	.string "sys_sched_setattr"
.Lname2739:
	.string "inode_areadallv_phys"
.Lname2740:
	.string "sys32_renameat"
.Lname2741:
	.string "regdump_icpustate"
.Lname2742:
	.string "sys_pwritevf"
.Lname2743:
	.string "vio_readw"
.Lname2744:
	.string "vm_copyfromphys_onepage_nopf"
.Lname2745:
	.string "sys32_waitid"
.Lname2750:
	.string "vio_writel_aligned"
.Lname2756:
	.string "directory_mknod"
.Lname2757:
	.string "dbg_readline"
.Lname2758:
	.string "vm_copytophys_nopf"
.Lname2759:
	.string "sys_rt_sigpending"
.Lname2761:
	.string "ioperm_bitmap_destroy"
.Lname2762:
	.string "vm_forcefault"
.Lname2763:
	.string "sys32_unlink"
.Lname2764:
	.string "dbg_enter_scpustate_cr"
.Lname2765:
	.string "vm_do_allocram"
.Lname2767:
	.string "sys_sync"
.Lname2768:
	.string "vm_kernel_syncall"
.Lname2769:
	.string "sys_setgid"
.Lname2771:
	.string "heap_alloc"
.Lname2772:
	.string "superblock_nodeslock_tryread"
.Lname2773:
	.string "_Unwind_Resume"
.Lname2774:
	.string "vm_read"
.Lname2777:
	.string "task_raisesignalthread"
.Lname2780:
	.string "json_writer_putnull"
.Lname2783:
	.string "sys32_fallocate"
.Lname2784:
	.string "x86_syscall_emulate32_int80h_r"
.Lname2785:
	.string "dbg_enter_kcpustate_r"
.Lname2786:
	.string "sys32_getgroups32"
.Lname2787:
	.string "aio_buffer_copyfromphys"
.Lname2788:
	.string "mouse_device_stat"
.Lname2789:
	.string "sys_getcpu"
.Lname2791:
	.string "cpu_quantum_remaining"
.Lname2792:
	.string "sys_tee"
.Lname2793:
	.string "rwlock_tryread_readonly"
.Lname2794:
	.string "sys_memfd_create"
.Lname2795:
	.string "sys_freadlinkat"
.Lname2796:
	.string "vio_writel"
.Lname2797:
	.string "cpu_run_current_and_remember"
.Lname2801:
	.string "superblock_mountlock_write_nx"
.Lname2803:
	.string "unwind_instruction_succ"
.Lname2804:
	.string "json_writer_putuint64"
.Lname2805:
	.string "kernel_debugtrap_ucpustate"
.Lname2810:
	.string "sys_name_to_handle_at"
.Lname2812:
	.string "x86_dbg_setregbyidp"
.Lname2813:
	.string "vm_datapart_do_copyram"
.Lname2815:
	.string "rwlock_pollwrite"
.Lname2816:
	.string "pagedir_unprepare_map_p"
.Lname2817:
	.string "task_rpc_exec_here"
.Lname2818:
	.string "sighand_reset_handler"
.Lname2819:
	.string "inode_writev_phys"
.Lname2820:
	.string "sys32_prlimit64"
.Lname2821:
	.string "__crt_unreachable"
.Lname2825:
	.string "cpu_sendipi"
.Lname2827:
	.string "sys_madvise"
.Lname2828:
	.string "sys32_fchown"
.Lname2829:
	.string "sys32_write"
.Lname2831:
	.string "sys32_mkdirat"
.Lname2835:
	.string "inode_sync"
.Lname2836:
	.string "debuginfo_cu_parser_next"
.Lname2837:
	.string "cpu_apply_ucpustate"
.Lname2840:
	.string "vm_startdma_nx"
.Lname2841:
	.string "sys32_msync"
.Lname2844:
	.string "slab_kmalloc64"
.Lname2847:
	.string "thiscpu_idle"
.Lname2850:
	.string "sys32_faccessat"
.Lname2851:
	.string "block_device_writev_phys"
.Lname2852:
	.string "isr_register_at"
.Lname2853:
	.string "driver_with_file"
.Lname2856:
	.string "devfs_lock_upgrade_nx"
.Lname2857:
	.string "keyboard_buffer_getkey"
.Lname2859:
	.string "sys32_recvmsg"
.Lname2864:
	.string "this_task"
.Lname2867:
	.string "slab_kmalloc"
.Lname2868:
	.string "sys32_futimesat64"
.Lname2869:
	.string "dbg_enter_icpustate"
.Lname2870:
	.string "json_parser_prev"
.Lname2873:
	.string "sys32_setresgid"
.Lname2875:
	.string "sys_rt_tgsigqueueinfo"
.Lname2876:
	.string "fs_filesystems_loadall"
.Lname2877:
	.string "sys_sched_getparam"
.Lname2878:
	.string "sys_chmod"
.Lname2879:
	.string "sys_sendto"
.Lname2880:
	.string "character_device_lookup"
.Lname2881:
	.string "slab_kmalloc40"
.Lname2883:
	.string "vm_tasklock_endread"
.Lname2884:
	.string "sys32_capget"
.Lname2885:
	.string "handle_get_directory_node"
.Lname2886:
	.string "sys32_getdrives"
.Lname2887:
	.string "inode_readv_phys_blocking"
.Lname2889:
	.string "dbg_readmemory"
.Lname2891:
	.string "handle_get_taskpid"
.Lname2893:
	.string "strlen"
.Lname2895:
	.string "dbg_enter_kcpustate_cr"
.Lname2897:
	.string "x86_userexcept_unwind_interrupt"
.Lname2898:
	.string "block_device_awritev_phys_sector"
.Lname2901:
	.string "devfs_remove"
.Lname2902:
	.string "sys32_close"
.Lname2903:
	.string "path_destroy"
.Lname2904:
	.string "rwlock_write_nx"
.Lname2905:
	.string "keyboard_device_stat"
.Lname2907:
	.string "vm_datapart_write_phys"
.Lname2908:
	.string "sys32_ioprio_set"
.Lname2911:
	.string "sys_swapoff"
.Lname2914:
	.string "x86_syscall_emulate32_sysenter"
.Lname2915:
	.string "block_device_writev_sync"
.Lname2916:
	.string "handle_get_superblock_relaxed"
.Lname2917:
	.string "inode_awritev"
.Lname2919:
	.string "vm_datapart_free"
.Lname2921:
	.string "directory_getcaseentry"
.Lname2923:
	.string "tty_device_stopfwd"
.Lname2924:
	.string "vm_datapart_lock_write"
.Lname2925:
	.string "vm_destroy"
.Lname2927:
	.string "sys32_utimensat"
.Lname2928:
	.string "unwind_setreg_kcpustate_exclusive"
.Lname2929:
	.string "slab_kmalloc48"
.Lname2931:
	.string "sys_fdatasync"
.Lname2932:
	.string "regdump_sgregs_with_cs_ss"
.Lname2933:
	.string "cfmakesane"
.Lname2936:
	.string "vm_datapart_split"
.Lname2937:
	.string "sys32_freadlinkat"
.Lname2938:
	.string "vm_syncall"
.Lname2942:
	.string "lookup_taskpid"
.Lname2943:
	.string "superblock_mountlock_upgrade"
.Lname2944:
	.string "path_remove"
.Lname2945:
	.string "kernel_debugtrap_r_lcpustate"
.Lname2946:
	.string "sys32_set_exception_handler"
.Lname2947:
	.string "sys_dup3"
.Lname2949:
	.string "quantum_time"
.Lname2950:
	.string "addr2line_printf"
.Lname2951:
	.string "mempsetw"
.Lname2952:
	.string "linebuffer_writesome"
.Lname2953:
	.string "driver_destroy"
.Lname2954:
	.string "sys_connect"
.Lname2955:
	.string "sys_getdrives"
.Lname2956:
	.string "memmovel"
.Lname2957:
	.string "sys_lremovexattr"
.Lname2962:
	.string "kernel_syscall0_regcnt"
.Lname2963:
	.string "vm_datapart_sync"
.Lname2964:
	.string "kernel_debugtrap_enabled"
.Lname2965:
	.string "sys_futex"
.Lname2966:
	.string "sys32_setresgid32"
.Lname2967:
	.string "dbg_hasuni"
.Lname2968:
	.string "thiscpu_x86_tss"
.Lname2969:
	.string "pipe_writer_destroy"
.Lname2970:
	.string "x86_fxsave"
.Lname2972:
	.string "handle_install"
.Lname2973:
	.string "debuginfo_cu_parser_loadattr_subprogram"
.Lname2975:
	.string "json_parser_leave"
.Lname2978:
	.string "sys32_setfsgid32"
.Lname2980:
	.string "pidns_trylookup_locked"
.Lname2981:
	.string "sys_write"
.Lname2982:
	.string "validate_readablem_opt"
.Lname2984:
	.string "unicode_writeutf8"
.Lname2985:
	.string "setreg_scpustate"
.Lname2986:
	.string "terminal_flush_icanon"
.Lname2989:
	.string "strchr"
.Lname2991:
	.string "validate_executable_opt"
.Lname2992:
	.string "sys_dup"
.Lname2994:
	.string "block_device_awrite_sector"
.Lname2995:
	.string "dbg_setallregs"
.Lname2996:
	.string "sys32_set_robust_list"
.Lname2997:
	.string "getreg_icpustate"
.Lname2998:
	.string "sys32_pselect6"
.Lname3000:
	.string "heap_align_untraced_nx"
.Lname3001:
	.string "isr_unregister_any_at"
.Lname3002:
	.string "thiscpu_x86_lapicid"
.Lname3003:
	.string "vm_readphysl_unaligned"
.Lname3004:
	.string "sigmask_check_after_syscall"
.Lname3007:
	.string "mempmove"
.Lname3009:
	.string "vm_kernel_treelock_tryservice"
.Lname3010:
	.string "dbg_default_attr"
.Lname3011:
	.string "sigmask_check_s"
.Lname3012:
	.string "sys_linux_stat64"
.Lname3014:
	.string "sys_mlockall"
.Lname3015:
	.string "rwlock_write_aggressive"
.Lname3017:
	.string "pipe_reader_destroy"
.Lname3019:
	.string "x86_fpustate_save_noreset"
.Lname3020:
	.string "x86_sysroute1_c32"
.Lname3027:
	.string "regdump_flags"
.Lname3028:
	.string "__stack_chk_guard"
.Lname3029:
	.string "dbg_setcur_visible"
.Lname3031:
	.string "task_alloc"
.Lname3032:
	.string "vm_tasklock_tryupgrade"
.Lname3033:
	.string "dev_tty"
.Lname3034:
	.string "vm_sync_locked"
.Lname3035:
	.string "superblock_mountlock_upgrade_nx"
.Lname3036:
	.string "memlen"
.Lname3039:
	.string "inode_readall_phys"
.Lname3040:
	.string "pagedir_ismapped_p"
.Lname3042:
	.string "mouse_device_button_nopr"
.Lname3043:
	.string "sys_link"
.Lname3045:
	.string "sys_readf"
.Lname3046:
	.string "inode_areadallv"
.Lname3047:
	.string "x86_userexcept_raisesignal"
.Lname3049:
	.string "ramfs_symlink_type"
.Lname3052:
	.string "character_device_poll"
.Lname3053:
	.string "vio_cmpxch_or_writeb"
.Lname3056:
	.string "vm_memsetphyspage"
.Lname3057:
	.string "memmoveq"
.Lname3059:
	.string "aio_pbuffer_copyfromphys"
.Lname3060:
	.string "sys32_setuid32"
.Lname3061:
	.string "kernel_panic_scpustate"
.Lname3063:
	.string "memmovew"
.Lname3064:
	.string "devfs_lock_write_nx"
.Lname3065:
	.string "path_movemount"
.Lname3066:
	.string "unwind_setreg_fcpustate_exclusive"
.Lname3067:
	.string "inode_areadallk"
.Lname3070:
	.string "vm_datapart_read_buffered"
.Lname3071:
	.string "path_traverse"
.Lname3072:
	.string "task_sigstop"
.Lname3074:
	.string "unwind_getreg_fcpustate_exclusive"
.Lname3075:
	.string "block_device_partition_readv_phys"
.Lname3076:
	.string "sys32_kfstat"
.Lname3077:
	.string "sys_rpc_schedule"
.Lname3078:
	.string "sys_pselect6"
.Lname3080:
	.string "driver_library_path"
.Lname3081:
	.string "vmb_apply"
.Lname3082:
	.string "vm_kernel_treelock_write_nx"
.Lname3083:
	.string "unwind_getreg_kcpustate_exclusive"
.Lname3084:
	.string "sys_getsockopt"
.Lname3085:
	.string "sys32_socketpair"
.Lname3086:
	.string "dbg_beginshowscreen"
.Lname3087:
	.string "error_as_errno"
.Lname3089:
	.string "vm_sync_end"
.Lname3090:
	.string "sys_umount2"
.Lname3091:
	.string "ansitty_putc"
.Lname3092:
	.string "unwind_setreg_fcpustate"
.Lname3093:
	.string "cpu_apply_fcpustate"
.Lname3095:
	.string "json_parser_eqstring"
.Lname3096:
	.string "path_sprintex"
.Lname3097:
	.string "sys32_openat"
.Lname3099:
	.string "dbg_setreg"
.Lname3100:
	.string "sys32_munlockall"
.Lname3101:
	.string "sys_ioperm"
.Lname3104:
	.string "vm_copytophys"
.Lname3105:
	.string "heap_alloc_nx"
.Lname3106:
	.string "sys32_getitimer64"
.Lname3107:
	.string "unicode_32to16"
.Lname3108:
	.string "thiscpu_x86_gdt"
.Lname3109:
	.string "_bootcpu"
.Lname3111:
	.string "memlenw"
.Lname3113:
	.string "vm_datablock_vio_write_phys"
.Lname3115:
	.string "sys_sendmmsg"
.Lname3116:
	.string "sys32_keyctl"
.Lname3117:
	.string "kernel_syscall0_regcnt32"
.Lname3118:
	.string "validate_writable_opt"
.Lname3121:
	.string "task_redirect_usercode_rpc"
.Lname3122:
	.string "json_parser_getnumber"
.Lname3123:
	.string "pagedir_kernel_phys"
.Lname3124:
	.string "memrend"
.Lname3125:
	.string "character_device_write"
.Lname3126:
	.string "sys32_writef"
.Lname3127:
	.string "vm_datapart_lockread_setcore_unsharecow"
.Lname3128:
	.string "unwind_getreg_lcpustate_exclusive"
.Lname3129:
	.string "sys32_sendfile64"
.Lname3130:
	.string "sys32_fchown32"
.Lname3131:
	.string "x86_userexcept_seterrno"
.Lname3132:
	.string "memlenl"
.Lname3133:
	.string "sys_setsockopt"
.Lname3134:
	.string "sys32_listen"
.Lname3135:
	.string "sys_fallocate"
.Lname3136:
	.string "character_device_mmap"
.Lname3137:
	.string "setreg_gpregsnsp"
.Lname3138:
	.string "isr_register"
.Lname3140:
	.string "memend"
.Lname3141:
	.string "kernel_vpanic_ucpustate"
.Lname3142:
	.string "sys32_writev"
.Lname3143:
	.string "terminal_init"
.Lname3144:
	.string "sys32_lfutex"
.Lname3145:
	.string "disasm_print_until"
.Lname3147:
	.string "sys32_getpmsg"
.Lname3148:
	.string "sys_umask"
.Lname3149:
	.string "sys32_mlock2"
.Lname3150:
	.string "kernel_vpanic_kcpustate"
.Lname3153:
	.string "sys32_bdflush"
.Lname3154:
	.string "sys32_dup2"
.Lname3155:
	.string "sys32_dup3"
.Lname3156:
	.string "cred_require_mmap_uninitialized"
.Lname3157:
	.string "x86_lapicbase"
.Lname3158:
	.string "x86_dbggdt"
.Lname3159:
	.string "inode_readk_blocking"
.Lname3160:
	.string "sys32_accept4"
.Lname3161:
	.string "sys32_exit"
.Lname3162:
	.string "sys_ioprio_get"
.Lname3164:
	.string "keyboard_device_ioctl"
.Lname3166:
	.string "vio_subb"
.Lname3167:
	.string "block_device_register_auto"
.Lname3168:
	.string "task_schedule_synchronous_rpc_nx"
.Lname3170:
	.string "dbg_verifypagedir"
.Lname3171:
	.string "vm_copyinphys_onepage"
.Lname3172:
	.string "task_connect_ghost"
.Lname3173:
	.string "driver_get_state"
.Lname3174:
	.string "sys_set_library_listdef"
.Lname3175:
	.string "sys_socket"
.Lname3178:
	.string "pagedir_kernel"
.Lname3179:
	.string "sys_mq_unlink"
.Lname3181:
	.string "dbg_getcur"
.Lname3184:
	.string "sys_exit_group"
.Lname3185:
	.string "x86_memcpy_nopf_rep_pointer"
.Lname3186:
	.string "unwind_setreg_icpustate"
.Lname3187:
	.string "keyboard_device_readkeys"
.Lname3188:
	.string "sys32_gettid"
.Lname3189:
	.string "slab_malloc64"
.Lname3190:
	.string "rwlock_upgrade"
.Lname3192:
	.string "vm_datapart_lockwrite_setcore_nx"
.Lname3193:
	.string "heap_allat_untraced"
.Lname3194:
	.string "sys32_timer_gettime64"
.Lname3196:
	.string "unwind_cfa_apply"
.Lname3197:
	.string "thiscpu_x86_dfstacknode"
.Lname3199:
	.string "sys32_setdomainname"
.Lname3200:
	.string "pagedir_prepare_map_keep"
.Lname3201:
	.string "sys_mq_timedreceive"
.Lname3202:
	.string "block_device_areadv_sector"
.Lname3203:
	.string "vm_memset_nopf"
.Lname3205:
	.string "sys32_readahead"
.Lname3206:
	.string "sys_timerfd_gettime"
.Lname3207:
	.string "sys32_putpmsg"
.Lname3208:
	.string "block_device_lookup_nx"
.Lname3209:
	.string "sys32_nfsservctl"
.Lname3211:
	.string "sys32_futex"
.Lname3212:
	.string "mouse_device_ioctl"
.Lname3213:
	.string "sys32_sched_getparam"
.Lname3214:
	.string "sys_timer_getoverrun"
.Lname3216:
	.string "sys32_clock_nanosleep"
.Lname3217:
	.string "vm_datapart_lock_read_nx"
.Lname3218:
	.string "mouse_device_moveto_nopr"
.Lname3219:
	.string "task_free_rpc"
.Lname3220:
	.string "pagedir_isuserwritable"
.Lname3221:
	.string "dbg_getcur_visible"
.Lname3223:
	.string "sys32_sched_setaffinity"
.Lname3225:
	.string "sys_fchmod"
.Lname3227:
	.string "x86_iopl_keep_after_fork"
.Lname3229:
	.string "sys_sysfs"
.Lname3230:
	.string "sys_mktty"
.Lname3231:
	.string "sys_timerfd_settime"
.Lname3232:
	.string "sys_geteuid"
.Lname3233:
	.string "vio_cmpxchq"
.Lname3237:
	.string "sys32_sethostname"
.Lname3238:
	.string "format_printf"
.Lname3239:
	.string "vio_cmpxchw"
.Lname3240:
	.string "devfs_lock_read_nx"
.Lname3241:
	.string "vm_datapart_lock_endread"
.Lname3242:
	.string "sys32_quotactl"
.Lname3243:
	.string "mall_print_traceback"
.Lname3245:
	.string "task_schedule_synchronous_rpc"
.Lname3246:
	.string "sys_perf_event_open"
.Lname3248:
	.string "dbg_putc"
.Lname3250:
	.string "dbg_pprinter"
.Lname3251:
	.string "kernel_heaps"
.Lname3253:
	.string "regdump_scpustate"
.Lname3254:
	.string "sys32_read"
.Lname3255:
	.string "json_parser_getstring"
.Lname3256:
	.string "vm_datablock_write_unsafe"
.Lname3257:
	.string "dbg_writememory"
.Lname3259:
	.string "sys32_sigaltstack"
.Lname3260:
	.string "vio_cmpxchl"
.Lname3261:
	.string "linebuffer_write"
.Lname3262:
	.string "unwind_fde_rule"
.Lname3263:
	.string "sys32_rt_tgsigqueueinfo"
.Lname3264:
	.string "format_hexdump"
.Lname3265:
	.string "memsetq"
.Lname3266:
	.string "vm_find_last_node_lower_equal"
.Lname3267:
	.string "slab_kmalloc_nx56"
.Lname3268:
	.string "sys_read"
.Lname3269:
	.string "rwlock_endwrite"
.Lname3270:
	.string "block_device_partition_writev"
.Lname3271:
	.string "memsetw"
.Lname3272:
	.string "fpustate_init_nx"
.Lname3273:
	.string "sys32_ioctl"
.Lname3274:
	.string "vm_datablock_vio_writev"
.Lname3275:
	.string "sys_ustat"
.Lname3276:
	.string "sys32_fchdirat"
.Lname3277:
	.string "inodes_recent_lim"
.Lname3280:
	.string "vm_datablock_anonymous_zero_type_vec"
.Lname3281:
	.string "this_sched_state"
.Lname3283:
	.string "devfs"
.Lname3284:
	.string "dbg_autocomplete_command"
.Lname3285:
	.string "rwlock_canwrite"
.Lname3287:
	.string "isr_register_greedy"
.Lname3288:
	.string "task_waitfor_nx"
.Lname3289:
	.string "cpu_count"
.Lname3292:
	.string "memsetl"
.Lname3293:
	.string "vm_do_ccfreeram"
.Lname3294:
	.string "this_exception_code"
.Lname3295:
	.string "error_register_state"
.Lname3297:
	.string "vmb_mapat"
.Lname3300:
	.string "json_parser_leaveobject"
.Lname3301:
	.string "json_writer_addfield"
.Lname3303:
	.string "vmb_isused"
.Lname3304:
	.string "heap_realloc_untraced_nx"
.Lname3306:
	.string "sys32_ptrace"
.Lname3308:
	.string "sys32_io_cancel"
.Lname3310:
	.string "coredump_create_for_exception"
.Lname3313:
	.string "vm_datapart_lock_write_nx"
.Lname3315:
	.string "aio_handle_multiple_func"
.Lname3316:
	.string "page_stat"
.Lname3317:
	.string "aio_multihandle_allochandle"
.Lname3318:
	.string "vm_tasklock_upgrade"
.Lname3321:
	.string "debugline_loadunit"
.Lname3322:
	.string "x86_dbg_setregbyid"
.Lname3323:
	.string "sys_munlock"
.Lname3325:
	.string "regdump_cr4"
.Lname3326:
	.string "sys_creat"
.Lname3327:
	.string "terminal_poll_iread"
.Lname3328:
	.string "this_x86_ioperm_bitmap"
.Lname3330:
	.string "sys32_linux_stat32"
.Lname3331:
	.string "pagedir_push_mapone"
.Lname3332:
	.string "sys32_frenameat"
.Lname3333:
	.string "sys32_epoll_create"
.Lname3334:
	.string "inode_areadv"
.Lname3336:
	.string "pidns_upgrade_nx"
.Lname3337:
	.string "quantum_local_to_global"
.Lname3339:
	.string "_boottask"
.Lname3340:
	.string "unwind_setreg_scpustate_exclusive"
.Lname3343:
	.string "vm_datapart_read_nopf"
.Lname3344:
	.string "pagedir_unmap_userspace_nosync_p"
.Lname3345:
	.string "task_yield_nx"
.Lname3346:
	.string "dbg_attr"
.Lname3347:
	.string "vfs_alloc"
.Lname3348:
	.string "sys32_pivot_root"
.Lname3349:
	.string "debuginfo_print_typename"
.Lname3350:
	.string "ioperm_bitmap_copyf"
.Lname3351:
	.string "cpu_assert_integrity"
.Lname3352:
	.string "thiscpu_quantum_length"
.Lname3353:
	.string "sys32_pread64"
.Lname3355:
	.string "dbg_stack"
.Lname3357:
	.string "unicode_32to8"
.Lname3358:
	.string "pagedir_haschanged"
.Lname3359:
	.string "dbg_enter_here_c"
.Lname3360:
	.string "sys_seccomp"
.Lname3361:
	.string "sys_truncate"
.Lname3362:
	.string "driver_getshstrtab"
.Lname3363:
	.string "fpustate_alloc"
.Lname3364:
	.string "dbg_draweditfield"
.Lname3365:
	.string "ioperm_bitmap_setrange"
.Lname3366:
	.string "sys32_syncfs"
.Lname3369:
	.string "keyboard_device_fini"
.Lname3370:
	.string "unwind_setreg_ucpustate"
.Lname3373:
	.string "vm_datablock_vio_read"
.Lname3375:
	.string "sys32_sendto"
.Lname3376:
	.string "vm_datapart_do_allocram"
.Lname3379:
	.string "sys32_setns"
.Lname3380:
	.string "sys32_getresuid"
.Lname3381:
	.string "dbg_enter_scpustate"
.Lname3382:
	.string "dbg_enter_kcpustate_c"
.Lname3383:
	.string "sys32_renameat2"
.Lname3384:
	.string "slab_kmalloc_nx"
.Lname3385:
	.string "sys_mq_timedsend"
.Lname3387:
	.string "sys32_sysinfo"
.Lname3388:
	.string "driver_insmod_file"
.Lname3389:
	.string "sys32_fadvise64"
.Lname3391:
	.string "pidns_downgrade"
.Lname3392:
	.string "cpu_enter_deepsleep"
.Lname3394:
	.string "kernel_syscall0_restartmode32"
.Lname3395:
	.string "sys_set_tid_address"
.Lname3396:
	.string "path_lock_read"
.Lname3398:
	.string "__acheckf"
.Lname3399:
	.string "kernel_syscall1_regcnt32"
.Lname3400:
	.string "pidns_read_nx"
.Lname3401:
	.string "sys32_umount"
.Lname3402:
	.string "path_getchild_and_parent_inode"
.Lname3403:
	.string "memmovedownw"
.Lname3404:
	.string "setreg_kcpustate"
.Lname3410:
	.string "sys32_fremovexattr"
.Lname3411:
	.string "sys32_migrate_pages"
.Lname3412:
	.string "sys32_getppid"
.Lname3413:
	.string "callback_list_remove"
.Lname3415:
	.string "isr_unregister_any"
.Lname3417:
	.string "ioperm_bitmap_empty"
.Lname3418:
	.string "sys32_olduname"
.Lname3419:
	.string "path_traversen_at"
.Lname3420:
	.string "sys_fchown"
.Lname3421:
	.string "vm_do_freeram"
.Lname3422:
	.string "vm_datapart_lock_downgrade"
.Lname3423:
	.string "error_info"
.Lname3425:
	.string "memrlenq"
.Lname3426:
	.string "sys32_chdir"
.Lname3428:
	.string "sys_getgid"
.Lname3429:
	.string "boot_cpustate"
.Lname3430:
	.string "dbg_addr2line_printf"
.Lname3431:
	.string "memrlenw"
.Lname3432:
	.string "vm_tasklock_write_nx"
.Lname3433:
	.string "sys_msgctl"
.Lname3434:
	.string "sys32_rpc_schedule"
.Lname3435:
	.string "pidns_trylookup_task"
.Lname3436:
	.string "sys32_fallocate64"
.Lname3437:
	.string "vm_onexec_callbacks"
.Lname3438:
	.string "vm_datapart_readv"
.Lname3440:
	.string "vm_datapart_map_ram_autoprop_p"
.Lname3441:
	.string "unwind_getreg_ucpustate_exclusive"
.Lname3442:
	.string "mouse_buffer_putpackets_nopr"
.Lname3444:
	.string "debuginfo_location_select"
.Lname3445:
	.string "rawmemlen"
.Lname3446:
	.string "dbg_printf"
.Lname3447:
	.string "vm_get_aslr_disabled"
.Lname3449:
	.string "sys_prlimit64"
.Lname3450:
	.string "this_sched_runnxt"
.Lname3452:
	.string "memrlenl"
.Lname3453:
	.string "thiscpu_override"
.Lname3454:
	.string "unicode_readutf8_n"
.Lname3455:
	.string "pagedir_maphintone"
.Lname3456:
	.string "thiscpu_x86_spurious_interrupts"
.Lname3457:
	.string "memcmp"
.Lname3458:
	.string "sys32_fchdir"
.Lname3459:
	.string "this_exception_class"
.Lname3460:
	.string "sys_getdents64"
.Lname3461:
	.string "kernel_terminal_check_sigttou"
.Lname3464:
	.string "task_detach"
.Lname3465:
	.string "driver_section_destroy"
.Lname3466:
	.string "setreg_sfpustate"
.Lname3467:
	.string "sys32_utime64"
.Lname3468:
	.string "sys32_restart_syscall"
.Lname3469:
	.string "sys_membarrier"
.Lname3471:
	.string "sys32_sysctl"
.Lname3472:
	.string "thisvm_x86_dr0"
.Lname3473:
	.string "thisvm_x86_dr1"
.Lname3474:
	.string "thisvm_x86_dr2"
.Lname3475:
	.string "cpu_disable_preemptive_interrupts"
.Lname3476:
	.string "fs_filesystems_lock_read"
.Lname3477:
	.string "sys_close"
.Lname3478:
	.string "this_trampoline_node"
.Lname3479:
	.string "thisvm_x86_dr7"
.Lname3483:
	.string "sys_chdir"
.Lname3484:
	.string "get_stack_avail"
.Lname3485:
	.string "sys32_getrandom"
.Lname3487:
	.string "directory_getnode"
.Lname3489:
	.string "sys32_getpid"
.Lname3490:
	.string "rwlock_writing_r"
.Lname3492:
	.string "debuginfo_cu_parser_loadattr_compile_unit"
.Lname3493:
	.string "devfs_lock_endwrite"
.Lname3494:
	.string "error_vprintf"
.Lname3495:
	.string "sys_settimeofday"
.Lname3497:
	.string "sys32_getpriority"
.Lname3499:
	.string "mempmovedownw"
.Lname3502:
	.string "sys_execve"
.Lname3503:
	.string "fs_filesystems_lock_endwrite"
.Lname3504:
	.string "vm_datablock_debugheap"
.Lname3505:
	.string "sys_get_thread_area"
.Lname3506:
	.string "dbg_enter_fcpustate_cr"
.Lname3507:
	.string "block_device_writev_phys_sync"
.Lname3508:
	.string "sys32_rt_sigsuspend"
.Lname3509:
	.string "getreg_scpustate"
.Lname3511:
	.string "vm_writephysl_unaligned"
.Lname3512:
	.string "__cxa_begin_catch"
.Lname3513:
	.string "sys32_sched_yield"
.Lname3515:
	.string "task_serve_nx"
.Lname3516:
	.string "sys_fmknodat"
.Lname3518:
	.string "disasm_instrlen"
.Lname3519:
	.string "rwlock_tryupgrade"
.Lname3520:
	.string "slab_kmalloc_nx40"
.Lname3521:
	.string "this_x86_kernel_psp0"
.Lname3523:
	.string "fs_filesystem_types"
.Lname3524:
	.string "fs_filesystems_lock_tryread"
.Lname3525:
	.string "blocking_cleanup_service"
.Lname3527:
	.string "sys_getpmsg"
.Lname3528:
	.string "slab_kmalloc_nx48"
.Lname3531:
	.string "__acheck"
.Lname3532:
	.string "block_device_partition_ioctl"
.Lname3533:
	.string "get_stack_for"
.Lname3534:
	.string "sys_kexec_load"
.Lname3535:
	.string "task_setprocessgroupleader"
.Lname3538:
	.string "slab_kmalloc_nx32"
.Lname3539:
	.string "block_device_read_phys_sync"
.Lname3540:
	.string "sig_send"
.Lname3541:
	.string "this_cpu"
.Lname3542:
	.string "sys32_swapoff"
.Lname3545:
	.string "kernel_personality"
.Lname3546:
	.string "vm_datablock_readvp"
.Lname3547:
	.string "sys32_lseek"
.Lname3548:
	.string "aio_multihandle_fail"
.Lname3549:
	.string "sys32_sched_get_priority_min"
.Lname3550:
	.string "sys_chown"
.Lname3551:
	.string "mall_trace"
.Lname3554:
	.string "kprinter"
.Lname3555:
	.string "task_enable_redirect_usercode_rpc"
.Lname3556:
	.string "slab_kmalloc_nx24"
.Lname3557:
	.string "this_x86_fpustate"
.Lname3559:
	.string "vm_stopdma"
.Lname3561:
	.string "x86_fpustate_load"
.Lname3562:
	.string "keyboard_device_putkey"
.Lname3565:
	.string "aio_pbuffer_copyfrommem"
.Lname3566:
	.string "kmemalign"
.Lname3568:
	.string "pagedir_unprepare_map"
.Lname3569:
	.string "x86_syscall_emulate32_cdecl_r"
.Lname3570:
	.string "ansitty_printer"
.Lname3571:
	.string "sys_setns"
.Lname3572:
	.string "fs_filesystems_lock_endread"
.Lname3573:
	.string "kernel_debugtrap_fcpustate"
.Lname3574:
	.string "slab_kmalloc_nx16"
.Lname3575:
	.string "sys_putpmsg"
.Lname3576:
	.string "sys32_inotify_add_watch"
.Lname3577:
	.string "json_writer_putfloat"
.Lname3579:
	.string "sys_fsmode"
.Lname3583:
	.string "sys32_stime"
.Lname3584:
	.string "unwind_getreg_kcpustate"
.Lname3585:
	.string "sys32_mknodat"
.Lname3586:
	.string "heap_realloc_nx"
.Lname3587:
	.string "task_disconnect_c"
.Lname3588:
	.string "sys_frealpathat"
.Lname3589:
	.string "fs_filesystems_lock_write"
.Lname3590:
	.string "thisvm_library_listdef"
.Lname3591:
	.string "sys_lchown"
.Lname3594:
	.string "sys_msync"
.Lname3596:
	.string "path_traversefull"
.Lname3597:
	.string "sys32_getitimer"
.Lname3600:
	.string "vm_datapart_allocswap"
.Lname3602:
	.string "x86_syscall_emulate_sysvabi_r"
.Lname3603:
	.string "block_device_write_sync"
.Lname3604:
	.string "debuginfo_cu_parser_getconst"
.Lname3605:
	.string "kernel_symbol_table"
.Lname3607:
	.string "sys_getppid"
.Lname3609:
	.string "sys_renameat"
.Lname3611:
	.string "cpu_delsleepingtask"
.Lname3614:
	.string "disasm_print_instruction"
.Lname3615:
	.string "page_ccfree"
.Lname3616:
	.string "pagedir_prepare_mapone_p"
.Lname3617:
	.string "vio_xchq"
.Lname3619:
	.string "block_device_readv_phys"
.Lname3620:
	.string "inode_read"
.Lname3621:
	.string "keymap_translate"
.Lname3622:
	.string "vm_readphysw_unaligned"
.Lname3623:
	.string "vio_xchw"
.Lname3624:
	.string "sys_mbind"
.Lname3625:
	.string "sys32_epoll_wait"
.Lname3627:
	.string "empty_kernel_sigmask"
.Lname3632:
	.string "pagedir_map"
.Lname3633:
	.string "slab_malloc8"
.Lname3634:
	.string "dbg_setcur"
.Lname3635:
	.string "sys32_sysfs"
.Lname3636:
	.string "heap_truncate_untraced"
.Lname3637:
	.string "cpu_quantum_time"
.Lname3638:
	.string "sys_pwrite64f"
.Lname3639:
	.string "vm_memsetphyspages"
.Lname3640:
	.string "vm_enumdma_nx"
.Lname3641:
	.string "dbg_purgeuni"
.Lname3644:
	.string "vio_xchl"
.Lname3647:
	.string "cmdline_encode"
.Lname3649:
	.string "sys_epoll_create1"
.Lname3650:
	.string "task_schedule_asynchronous_rpc"
.Lname3651:
	.string "block_device_partition_read_phys"
.Lname3652:
	.string "sys_execveat"
.Lname3653:
	.string "kernel_vpanic_scpustate"
.Lname3654:
	.string "kernel_vpanic_lcpustate"
.Lname3655:
	.string "unwind_emulator_exec"
.Lname3658:
	.string "sys_set_robust_list"
.Lname3661:
	.string "sys32_lgetxattr"
.Lname3663:
	.string "vm_writephysw_unaligned"
.Lname3664:
	.string "sys32_seccomp"
.Lname3666:
	.string "sys32_mmap2"
.Lname3667:
	.string "block_device_write_phys"
.Lname3668:
	.string "path_printent"
.Lname3669:
	.string "vm_datapart_loaddatapage"
.Lname3670:
	.string "unicode_readutf16"
.Lname3671:
	.string "handle_lookup_type"
.Lname3672:
	.string "vm_datapart_lockwrite_setcore_unsharecow_nx"
.Lname3673:
	.string "sys32_clock_settime64"
.Lname3674:
	.string "terminal_setios"
.Lname3677:
	.string "task_pause"
.Lname3678:
	.string "page_stat_between"
.Lname3679:
	.string "page_mallocone"
.Lname3680:
	.string "sys_tgkill"
.Lname3681:
	.string "x86_dbg_regfromname"
.Lname3682:
	.string "sys_getxattr"
.Lname3683:
	.string "block_device_readv_sync"
.Lname3684:
	.string "dbg_fillrect"
.Lname3685:
	.string "dbg_tabsize"
.Lname3687:
	.string "vm_datapart_getfutex_existing"
.Lname3688:
	.string "sys_fchdirat"
.Lname3689:
	.string "sys_semget"
.Lname3690:
	.string "vm_mapat"
.Lname3693:
	.string "this_handle_manager"
.Lname3694:
	.string "unwind_fde_exec_landing_pad_adjustment"
.Lname3695:
	.string "unicode_readutf8_rev_n"
.Lname3697:
	.string "regdump_sgregs"
.Lname3698:
	.string "sys_getitimer"
.Lname3699:
	.string "thiscpu_jiffies"
.Lname3700:
	.string "pagedir_gethint"
.Lname3701:
	.string "heap_truncate"
.Lname3702:
	.string "unicode_readutf8_rev"
.Lname3705:
	.string "task_setthread"
.Lname3706:
	.string "x86_pagedir_sync"
.Lname3707:
	.string "sys32_reboot"
.Lname3710:
	.string "sys32_sigreturn"
.Lname3711:
	.string "strnend"
.Lname3712:
	.string "pagedir_unwrite_p"
.Lname3713:
	.string "vm86_step"
.Lname3714:
	.string "this_x86_rpc_redirection_iret"
.Lname3715:
	.string "this_fs"
.Lname3716:
	.string "sys32_signalfd4"
.Lname3717:
	.string "character_device_lookup_name"
.Lname3718:
	.string "mouse_buffer_getpacket"
.Lname3721:
	.string "dbg_ungetuni"
.Lname3722:
	.string "pagedir_unwriteone"
.Lname3724:
	.string "dbg_bell"
.Lname3725:
	.string "strtou32"
.Lname3726:
	.string "sys32_mq_open"
.Lname3727:
	.string "vm_do_ffreeram"
.Lname3728:
	.string "this_connections"
.Lname3729:
	.string "vm_kernel_treelock_read_nx"
.Lname3731:
	.string "vm_datablock_anonymous_zero_vec"
.Lname3732:
	.string "debuginfo_cu_parser_nextchild"
.Lname3733:
	.string "pagedir_translate"
.Lname3734:
	.string "sys_ioctlf"
.Lname3736:
	.string "sys32_sync_file_range"
.Lname3737:
	.string "x86_idt"
.Lname3738:
	.string "sys_sysctl"
.Lname3739:
	.string "sys_flock"
.Lname3740:
	.string "sys32_linux_fstatat64"
.Lname3741:
	.string "sys32_getpeername"
.Lname3742:
	.string "sys32_setregid"
.Lname3743:
	.string "sys_sethostname"
.Lname3744:
	.string "kernel_debugtrap"
.Lname3745:
	.string "sys_raiseat"
.Lname3747:
	.string "inode_areadk"
.Lname3748:
	.string "sys32_readvf"
.Lname3749:
	.string "handle_tryclose"
.Lname3752:
	.string "rwlock_read_nx"
.Lname3755:
	.string "sys_bpf"
.Lname3756:
	.string "sys_fcntl"
.Lname3758:
	.string "heap_alloc_untraced"
.Lname3762:
	.string "sys32_ustat"
.Lname3763:
	.string "sys32_setgroups"
.Lname3764:
	.string "pidns_end"
.Lname3765:
	.string "pidns_upgrade"
.Lname3768:
	.string "vm_do_allocram_nx"
.Lname3769:
	.string "thiscpu_quantum_offset"
.Lname3770:
	.string "unwind_fde_exec_cfa"
.Lname3772:
	.string "sighand_raise_signal"
.Lname3774:
	.string "vm_sync"
.Lname3775:
	.string "character_device_register_auto"
.Lname3776:
	.string "x86_dbg_getregbyidp"
.Lname3778:
	.string "vmb_alloc_peb"
.Lname3779:
	.string "aio_buffer_copytophys"
.Lname3780:
	.string "sig_altbroadcast"
.Lname3781:
	.string "driver_getfile"
.Lname3783:
	.string "vm_kernel_treelock_endread"
.Lname3785:
	.string "unwind_setreg_xfpustate"
.Lname3786:
	.string "terminal_iwrite"
.Lname3787:
	.string "vm_datablock_haschanged"
.Lname3789:
	.string "sys32_fsetxattr"
.Lname3790:
	.string "mouse_device_motion"
.Lname3791:
	.string "this_exception_flags"
.Lname3792:
	.string "x86_asm_except_personality"
.Lname3794:
	.string "cpu_vector"
.Lname3795:
	.string "dbg_enter_fcpustate_c"
.Lname3796:
	.string "inode_aread"
.Lname3797:
	.string "path_rename"
.Lname3798:
	.string "vm_read_nopf"
.Lname3799:
	.string "sys_request_key"
.Lname3800:
	.string "path_lock_write_nx"
.Lname3801:
	.string "json_parser_enterarray"
.Lname3802:
	.string "vm_node_insert"
.Lname3805:
	.string "sys_lseek64"
.Lname3807:
	.string "block_device_write"
.Lname3810:
	.string "dbg_enter_fcpustate_r"
.Lname3811:
	.string "vm_copyfromphys"
.Lname3812:
	.string "block_device_autopart"
.Lname3813:
	.string "vm_kernel_treelock_upgrade"
.Lname3814:
	.string "sys32_io_destroy"
.Lname3816:
	.string "sys32_munmap"
.Lname3817:
	.string "sys32_profil"
.Lname3818:
	.string "unicode_writeutf16"
.Lname3819:
	.string "linebuffer_write_nonblock"
.Lname3821:
	.string "sys32_alarm"
.Lname3822:
	.string "driver_getshdrs"
.Lname3824:
	.string "pagedir_unwriteone_p"
.Lname3825:
	.string "task_raisesignalprocessgroup_nx"
.Lname3827:
	.string "sys32_io_getevents"
.Lname3828:
	.string "block_device_aread"
.Lname3829:
	.string "kernel_debugtrap_icpustate"
.Lname3831:
	.string "task_pushconnections"
.Lname3833:
	.string "dbg_enter_icpustate_r"
.Lname3835:
	.string "sys32_umask"
.Lname3836:
	.string "dbg_scroll"
.Lname3839:
	.string "sys_pipe"
.Lname3840:
	.string "memmoveup"
.Lname3841:
	.string "mempmoveq"
.Lname3842:
	.string "sys_mq_getsetattr"
.Lname3844:
	.string "error_throw_current"
.Lname3845:
	.string "sys32_sendfile"
.Lname3847:
	.string "mempmovew"
.Lname3849:
	.string "callback_list_empty"
.Lname3850:
	.string "unwind_setreg_lcpustate"
.Lname3852:
	.string "inode_ioctl"
.Lname3853:
	.string "sys32_getresuid32"
.Lname3854:
	.string "sys_kfstat"
.Lname3856:
	.string "pagedir_map_p"
.Lname3857:
	.string "kmemalign_nx"
.Lname3858:
	.string "mouse_device_button_ex_nopr"
.Lname3859:
	.string "debuginfo_enum_locals"
.Lname3860:
	.string "vio_writew_aligned"
.Lname3861:
	.string "cpu_apply_icpustate"
.Lname3862:
	.string "block_device_areadv"
.Lname3863:
	.string "debuginfo_cu_parser_nextsibling"
.Lname3864:
	.string "json_parser_findindex"
.Lname3865:
	.string "__mempcpy"
.Lname3866:
	.string "vm86_inl"
.Lname3868:
	.string "task_destroy"
.Lname3869:
	.string "vm86_exec"
.Lname3870:
	.string "superblock_open"
.Lname3871:
	.string "kernel_syscall0_restartmode"
.Lname3873:
	.string "sys_linux_fstat64"
.Lname3877:
	.string "dbg_beginupdate"
.Lname3878:
	.string "vm_datablock_anonymous"
.Lname3879:
	.string "inode_read_phys_blocking"
.Lname3880:
	.string "x86_sysroute0_c32"
.Lname3881:
	.string "cpu_do_assert_integrity"
.Lname3884:
	.string "sys_ppoll"
.Lname3885:
	.string "tty_device_forward_destroy"
.Lname3886:
	.string "unwind_fde_sigframe_exec"
.Lname3887:
	.string "sys_recvfrom"
.Lname3889:
	.string "task_waitfor_norpc_nx"
.Lname3890:
	.string "sys32_mq_getsetattr"
.Lname3891:
	.string "heap_realloc"
.Lname3892:
	.string "strtou64"
.Lname3893:
	.string "dbg_enter_ucpustate"
.Lname3894:
	.string "dbg_menuf"
.Lname3895:
	.string "unwind_getreg_fcpustate"
.Lname3897:
	.string "task_sigcont"
.Lname3898:
	.string "sys32_timerfd_gettime64"
.Lname3899:
	.string "syscall_trace"
.Lname3901:
	.string "sys_uname"
.Lname3902:
	.string "syscall_tracing_setenabled"
.Lname3903:
	.string "format_quote"
.Lname3905:
	.string "dbg_setscreendata"
.Lname3906:
	.string "sys_fremovexattr"
.Lname3908:
	.string "sys32_capset"
.Lname3909:
	.string "directory_rename"
.Lname3910:
	.string "format_vscanf"
.Lname3912:
	.string "sprintf"
.Lname3916:
	.string "sys_tuxcall"
.Lname3917:
	.string "x86_syscall_emulate_int80h_r"
.Lname3919:
	.string "vio_orw"
.Lname3920:
	.string "kernel_default_heap"
.Lname3922:
	.string "cpu_quantum_elapsed_nopr"
.Lname3923:
	.string "block_device_delparts"
.Lname3924:
	.string "block_device_makepart"
.Lname3925:
	.string "devfs_lock_trywrite"
.Lname3928:
	.string "ioperm_bitmap_copyf_nx"
.Lname3929:
	.string "character_device_pread"
.Lname3932:
	.string "vio_cmpxch_or_writel"
.Lname3933:
	.string "pmembank_type_names"
.Lname3935:
	.string "vm_tasklock_downgrade"
.Lname3936:
	.string "sys_setrlimit"
.Lname3937:
	.string "vmb_find_last_node_lower_equal"
.Lname3938:
	.string "isr_vector_trigger"
.Lname3939:
	.string "inode_areadall_phys"
.Lname3940:
	.string "dbg_isholding_shift"
.Lname3941:
	.string "driver_finalize"
.Lname3942:
	.string "sys_poll"
.Lname3944:
	.string "task_setpid"
.Lname3945:
	.string "inode_readall"
.Lname3946:
	.string "path_lock_endread"
.Lname3947:
	.string "vm_tasklock_read"
.Lname3949:
	.string "sys32_kreaddir"
.Lname3950:
	.string "sys32_mktty"
.Lname3953:
	.string "dbg_getscreendata"
.Lname3954:
	.string "dbg_evaladdr"
.Lname3955:
	.string "pidns_alloc"
.Lname3956:
	.string "sys32_getsid"
.Lname3957:
	.string "x86_dbg_trapstate"
.Lname3958:
	.string "sys32_set_library_listdef"
.Lname3960:
	.string "sys32_mpx"
.Lname3961:
	.string "handle_installat"
.Lname3963:
	.string "sys32_readlink"
.Lname3964:
	.string "mempmovel"
.Lname3966:
	.string "sys_shmat"
.Lname3967:
	.string "vfs_clone"
.Lname3970:
	.string "sys32_get_exception_handler"
.Lname3971:
	.string "system_clearcaches"
.Lname3972:
	.string "dbg_getfunc_start"
.Lname3973:
	.string "dbg_enter_here"
.Lname3977:
	.string "sys32_openpty"
.Lname3979:
	.string "vio_writew"
.Lname3980:
	.string "sys_setpgid"
.Lname3981:
	.string "debuginfo_cu_parser_skipform"
.Lname3982:
	.string "dbg_endshowscreen"
.Lname3985:
	.string "sys_rt_sigaction"
.Lname3987:
	.string "sys_fsync"
.Lname3988:
	.string "page_malloc_part"
.Lname3989:
	.string "dbg_newline_mode"
.Lname3991:
	.string "json_parser_printstring"
.Lname3992:
	.string "x86_idt_modify_begin"
.Lname3993:
	.string "setreg_icpustate"
.Lname3998:
	.string "sys32_setitimer64"
.Lname3999:
	.string "fpustate_saveinto"
.Lname4000:
	.string "pidns_trylookup"
.Lname4001:
	.string "vm_readphysq_unaligned"
.Lname4002:
	.string "mouse_device_vwheel_nopr"
.Lname4003:
	.string "block_device_readv_phys_sync"
.Lname4004:
	.string "sys32_ugetrlimit"
.Lname4005:
	.string "kernel_debugtrap_r_scpustate"
.Lname4008:
	.string "vm_datapart_split_nx"
.Lname4011:
	.string "vm_onfini_callbacks"
.Lname4016:
	.string "regdump_gpregs"
.Lname4017:
	.string "task_raisesignalprocess_nx"
.Lname4018:
	.string "block_device_register"
.Lname4019:
	.string "jiffies"
.Lname4020:
	.string "sys32_get_robust_list"
.Lname4021:
	.string "directory_remove"
.Lname4022:
	.string "vm_getnodeof"
.Lname4023:
	.string "sys_getpid"
.Lname4025:
	.string "sys32_setfsgid"
.Lname4026:
	.string "vm_datablock_lock_trywrite_parts"
.Lname4029:
	.string "sys32_kstat"
.Lname4030:
	.string "vpage_free_untraced"
.Lname4031:
	.string "sys32_nice"
.Lname4034:
	.string "debuginfo_cu_parser_getexpr"
.Lname4035:
	.string "character_device_alloc"
.Lname4036:
	.string "cred_require_driveroot"
.Lname4037:
	.string "disasm_print_line"
.Lname4041:
	.string "vm_sync_endall"
.Lname4043:
	.string "zlib_reader_read"
.Lname4044:
	.string "this_sighand_ptr"
.Lname4045:
	.string "sys32_sched_setparam"
.Lname4048:
	.string "regdump_ip"
.Lname4051:
	.string "vm_datapart_readv_phys"
.Lname4052:
	.string "inode_stat"
.Lname4053:
	.string "inode_changed_chmtime"
.Lname4054:
	.string "sys_pread64f"
.Lname4055:
	.string "thiscpu_pending"
.Lname4056:
	.string "krealign_nx"
.Lname4057:
	.string "sys32_modify_ldt"
.Lname4061:
	.string "sys_nanosleep"
.Lname4062:
	.string "sys_mq_open"
.Lname4063:
	.string "path_lock_downgrade"
.Lname4064:
	.string "sys_coredump"
.Lname4065:
	.string "memchrq"
.Lname4066:
	.string "keyboard_device_getchar"
.Lname4067:
	.string "block_device_aread_phys"
.Lname4068:
	.string "fpustate_init"
.Lname4069:
	.string "sys_mincore"
.Lname4071:
	.string "memchrw"
.Lname4073:
	.string "memchrl"
.Lname4075:
	.string "vm_tasklock_tryread"
.Lname4077:
	.string "mouse_device_hwheel_nopr"
.Lname4080:
	.string "sys_kcmp"
.Lname4081:
	.string "sys32_clock_gettime64"
.Lname4084:
	.string "vio_subl"
.Lname4085:
	.string "rwlock_trywrite"
.Lname4087:
	.string "vm_write"
.Lname4088:
	.string "syscall_tracing_getenabled"
.Lname4089:
	.string "sys_capget"
.Lname4092:
	.string "dbg_enter_ucpustate_r"
.Lname4093:
	.string "thiscpu_id"
.Lname4094:
	.string "x86_dbggdt_ptr"
.Lname4095:
	.string "dbg_enter_scpustate_r"
