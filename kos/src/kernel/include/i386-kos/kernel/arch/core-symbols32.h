.section .rodata.kernel_symtab
PUBLIC_OBJECT(kernel_symbol_table)
	.long 0xfff
	/* Symbol table */
	.long .Lname0 /* index: 0 */
	.weak cpu_apply_icpustate_esp; .long cpu_apply_icpustate_esp
	.reloc ., R_386_SIZE32, cpu_apply_icpustate_esp; .long 0
	.long 0xf11d000
	.long 0 /* index: 1 */
	.long 0
	.long 0
	.long 0
	.long .Lname2 /* index: 2 */
	.weak slab_malloc12; .long slab_malloc12
	.reloc ., R_386_SIZE32, slab_malloc12; .long 0
	.long 0xe16d002
	.long .Lname3 /* index: 3 */
	.weak handle_get_datablock; .long handle_get_datablock
	.reloc ., R_386_SIZE32, handle_get_datablock; .long 0
	.long 0xffc62ab
	.long .Lname4 /* index: 4 */
	.weak regdump_gdt; .long regdump_gdt
	.reloc ., R_386_SIZE32, regdump_gdt; .long 0
	.long 0xc3ee004
	.long .Lname5 /* index: 5 */
	.weak cpu_apply_scpustate; .long cpu_apply_scpustate
	.reloc ., R_386_SIZE32, cpu_apply_scpustate; .long 0
	.long 0xa8c9915
	.long .Lname6 /* index: 6 */
	.weak slab_malloc16; .long slab_malloc16
	.reloc ., R_386_SIZE32, slab_malloc16; .long 0
	.long 0xe16d006
	.long 0 /* index: 7 */
	.long 0
	.long 0
	.long 0
	.long .Lname8 /* index: 8 */
	.weak aio_pbuffer_memset; .long aio_pbuffer_memset
	.reloc ., R_386_SIZE32, aio_pbuffer_memset; .long 0
	.long 0xb08d3e4
	.long 0 /* index: 9 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 10 */
	.long 0
	.long 0
	.long 0
	.long .Lname11 /* index: 11 */
	.weak inode_writek; .long inode_writek
	.reloc ., R_386_SIZE32, inode_writek; .long 0
	.long 0x1ee500b
	.long 0 /* index: 12 */
	.long 0
	.long 0
	.long 0
	.long .Lname13 /* index: 13 */
	.weak handle_installinto_sym; .long handle_installinto_sym
	.reloc ., R_386_SIZE32, handle_installinto_sym; .long 0
	.long 0x440c00d
	.long 0 /* index: 14 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 15 */
	.long 0
	.long 0
	.long 0
	.long .Lname16 /* index: 16 */
	.weak directory_getentry_p; .long directory_getentry_p
	.reloc ., R_386_SIZE32, directory_getentry_p; .long 0
	.long 0x325f010
	.long 0 /* index: 17 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 18 */
	.long 0
	.long 0
	.long 0
	.long .Lname19 /* index: 19 */
	.weak block_device_readv_sync; .long block_device_readv_sync
	.reloc ., R_386_SIZE32, block_device_readv_sync; .long 0
	.long 0x323de63
	.long 0 /* index: 20 */
	.long 0
	.long 0
	.long 0
	.long .Lname21 /* index: 21 */
	.weak pidns_tryupgrade; .long pidns_tryupgrade
	.reloc ., R_386_SIZE32, pidns_tryupgrade; .long 0
	.long 0x9ff5015
	.long 0 /* index: 22 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 23 */
	.long 0
	.long 0
	.long 0
	.long .Lname24 /* index: 24 */
	.weak cpu_quantum_length; .long cpu_quantum_length
	.reloc ., R_386_SIZE32, cpu_quantum_length; .long 0
	.long 0x9ca4018
	.long .Lname25 /* index: 25 */
	.weak sys_time64; .long sys_time64
	.reloc ., R_386_SIZE32, sys_time64; .long 0
	.long 0x6a98804
	.long 0 /* index: 26 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 27 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 28 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 29 */
	.long 0
	.long 0
	.long 0
	.long .Lname30 /* index: 30 */
	.weak devfs_lock_downgrade; .long devfs_lock_downgrade
	.reloc ., R_386_SIZE32, devfs_lock_downgrade; .long 0
	.long 0x5204855
	.long 0 /* index: 31 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 32 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 33 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 34 */
	.long 0
	.long 0
	.long 0
	.long .Lname35 /* index: 35 */
	.weak qtime_to_timespec; .long qtime_to_timespec
	.reloc ., R_386_SIZE32, qtime_to_timespec; .long 0
	.long 0x528a023
	.long 0 /* index: 36 */
	.long 0
	.long 0
	.long 0
	.long .Lname37 /* index: 37 */
	.weak vm_datablock_vio_write; .long vm_datablock_vio_write
	.reloc ., R_386_SIZE32, vm_datablock_vio_write; .long 0
	.long 0xc405025
	.long 0 /* index: 38 */
	.long 0
	.long 0
	.long 0
	.long .Lname39 /* index: 39 */
	.weak fs_filesystems_lock_trywrite; .long fs_filesystems_lock_trywrite
	.reloc ., R_386_SIZE32, fs_filesystems_lock_trywrite; .long 0
	.long 0xe4fb15
	.long 0 /* index: 40 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 41 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 42 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 43 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 44 */
	.long 0
	.long 0
	.long 0
	.long .Lname45 /* index: 45 */
	.weak vm_datapart_do_allocram; .long vm_datapart_do_allocram
	.reloc ., R_386_SIZE32, vm_datapart_do_allocram; .long 0
	.long 0x1c5802d
	.long 0 /* index: 46 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 47 */
	.long 0
	.long 0
	.long 0
	.long .Lname48 /* index: 48 */
	.weak cpu_apply_scpustate_esp; .long cpu_apply_scpustate_esp
	.reloc ., R_386_SIZE32, cpu_apply_scpustate_esp; .long 0
	.long 0x911d030
	.long .Lname49 /* index: 49 */
	.weak dbg_fillrect; .long dbg_fillrect
	.reloc ., R_386_SIZE32, dbg_fillrect; .long 0
	.long 0xa9b5e64
	.long 0 /* index: 50 */
	.long 0
	.long 0
	.long 0
	.long .Lname51 /* index: 51 */
	.weak kernel_panic; .long kernel_panic
	.reloc ., R_386_SIZE32, kernel_panic; .long 0
	.long 0x77af033
	.long .Lname52 /* index: 52 */
	.weak page_ismapped; .long page_ismapped
	.reloc ., R_386_SIZE32, page_ismapped; .long 0
	.long 0x45c034
	.long 0 /* index: 53 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 54 */
	.long 0
	.long 0
	.long 0
	.long .Lname55 /* index: 55 */
	.weak driver_local_symbol_at; .long driver_local_symbol_at
	.reloc ., R_386_SIZE32, driver_local_symbol_at; .long 0
	.long 0x6529334
	.long 0 /* index: 56 */
	.long 0
	.long 0
	.long 0
	.long .Lname57 /* index: 57 */
	.weak path_umount; .long path_umount
	.reloc ., R_386_SIZE32, path_umount; .long 0
	.long 0x6d6e2b4
	.long 0 /* index: 58 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 59 */
	.long 0
	.long 0
	.long 0
	.long .Lname60 /* index: 60 */
	.weak _this_sigmask; .long _this_sigmask
	.reloc ., R_386_SIZE32, _this_sigmask; .long 0
	.long 0xf53319b
	.long 0 /* index: 61 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 62 */
	.long 0
	.long 0
	.long 0
	.long .Lname63 /* index: 63 */
	.weak cpu_wake; .long cpu_wake
	.reloc ., R_386_SIZE32, cpu_wake; .long 0
	.long 0x7b6d2b5
	.long 0 /* index: 64 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 65 */
	.long 0
	.long 0
	.long 0
	.long .Lname66 /* index: 66 */
	.weak cpu_delete_idle_job; .long cpu_delete_idle_job
	.reloc ., R_386_SIZE32, cpu_delete_idle_job; .long 0
	.long 0x3997042
	.long 0 /* index: 67 */
	.long 0
	.long 0
	.long 0
	.long .Lname68 /* index: 68 */
	.weak unwind; .long unwind
	.reloc ., R_386_SIZE32, unwind; .long 0
	.long 0x7c5e044
	.long .Lname69 /* index: 69 */
	.weak lookup_pci_device; .long lookup_pci_device
	.reloc ., R_386_SIZE32, lookup_pci_device; .long 0
	.long 0x999c045
	.long 0 /* index: 70 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 71 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 72 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 73 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 74 */
	.long 0
	.long 0
	.long 0
	.long .Lname75 /* index: 75 */
	.weak kernel_slab_break; .long kernel_slab_break
	.reloc ., R_386_SIZE32, kernel_slab_break; .long 0
	.long 0xc2ee04b
	.long 0 /* index: 76 */
	.long 0
	.long 0
	.long 0
	.long .Lname77 /* index: 77 */
	.weak vm_datapart_allocram; .long vm_datapart_allocram
	.reloc ., R_386_SIZE32, vm_datapart_allocram; .long 0
	.long 0x906804d
	.long .Lname78 /* index: 78 */
	.weak task_detach_children; .long task_detach_children
	.reloc ., R_386_SIZE32, task_detach_children; .long 0
	.long 0xc3a204e
	.long .Lname79 /* index: 79 */
	.weak block_device_read; .long block_device_read
	.reloc ., R_386_SIZE32, block_device_read; .long 0
	.long 0x8a57224
	.long 0 /* index: 80 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 81 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 82 */
	.long 0
	.long 0
	.long 0
	.long .Lname83 /* index: 83 */
	.weak fs_filesystems; .long fs_filesystems
	.reloc ., R_386_SIZE32, fs_filesystems; .long 0
	.long 0x457b053
	.long .Lname84 /* index: 84 */
	.weak sys_utimes64; .long sys_utimes64
	.reloc ., R_386_SIZE32, sys_utimes64; .long 0
	.long 0xd535054
	.long .Lname85 /* index: 85 */
	.weak sys_timer_delete; .long sys_timer_delete
	.reloc ., R_386_SIZE32, sys_timer_delete; .long 0
	.long 0x303a055
	.long 0 /* index: 86 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 87 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 88 */
	.long 0
	.long 0
	.long 0
	.long .Lname89 /* index: 89 */
	.weak sys_setgid; .long sys_setgid
	.reloc ., R_386_SIZE32, sys_setgid; .long 0
	.long 0x69b1d64
	.long 0 /* index: 90 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 91 */
	.long 0
	.long 0
	.long 0
	.long .Lname92 /* index: 92 */
	.weak error_as_signal; .long error_as_signal
	.reloc ., R_386_SIZE32, error_as_signal; .long 0
	.long 0xff7f05c
	.long 0 /* index: 93 */
	.long 0
	.long 0
	.long 0
	.long .Lname94 /* index: 94 */
	.weak error_thrown; .long error_thrown
	.reloc ., R_386_SIZE32, error_thrown; .long 0
	.long 0x66205e
	.long .Lname95 /* index: 95 */
	.weak sys_ftruncate; .long sys_ftruncate
	.reloc ., R_386_SIZE32, sys_ftruncate; .long 0
	.long 0x2cdc565
	.long .Lname96 /* index: 96 */
	.weak strend; .long strend
	.reloc ., R_386_SIZE32, strend; .long 0
	.long 0x7ab8c44
	.long .Lname97 /* index: 97 */
	.weak slab_malloc20; .long slab_malloc20
	.reloc ., R_386_SIZE32, slab_malloc20; .long 0
	.long 0xe16d010
	.long 0 /* index: 98 */
	.long 0
	.long 0
	.long 0
	.long .Lname99 /* index: 99 */
	.weak x86_cputss; .long x86_cputss
	.reloc ., R_386_SIZE32, x86_cputss; .long 0
	.long 0x5a07063
	.long 0 /* index: 100 */
	.long 0
	.long 0
	.long 0
	.long .Lname101 /* index: 101 */
	.weak aio_multihandle_done; .long aio_multihandle_done
	.reloc ., R_386_SIZE32, aio_multihandle_done; .long 0
	.long 0x81e0065
	.long .Lname102 /* index: 102 */
	.weak dbg_screen_cellsize; .long dbg_screen_cellsize
	.reloc ., R_386_SIZE32, dbg_screen_cellsize; .long 0
	.long 0xa250d55
	.long .Lname103 /* index: 103 */
	.weak dbg_setreg; .long dbg_setreg
	.reloc ., R_386_SIZE32, dbg_setreg; .long 0
	.long 0x69a1067
	.long 0 /* index: 104 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 105 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 106 */
	.long 0
	.long 0
	.long 0
	.long .Lname107 /* index: 107 */
	.weak vio_addw; .long vio_addw
	.reloc ., R_386_SIZE32, vio_addw; .long 0
	.long 0x557d67
	.long 0 /* index: 108 */
	.long 0
	.long 0
	.long 0
	.long .Lname109 /* index: 109 */
	.weak error_register_state; .long error_register_state
	.reloc ., R_386_SIZE32, error_register_state; .long 0
	.long 0x63c8225
	.long .Lname110 /* index: 110 */
	.weak vm_ramfile_type; .long vm_ramfile_type
	.reloc ., R_386_SIZE32, vm_ramfile_type; .long 0
	.long 0x43f01b5
	.long 0 /* index: 111 */
	.long 0
	.long 0
	.long 0
	.long .Lname112 /* index: 112 */
	.weak handle_installhop; .long handle_installhop
	.reloc ., R_386_SIZE32, handle_installhop; .long 0
	.long 0x8bab070
	.long 0 /* index: 113 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 114 */
	.long 0
	.long 0
	.long 0
	.long .Lname115 /* index: 115 */
	.weak task_exec_asynchronous_srpc; .long task_exec_asynchronous_srpc
	.reloc ., R_386_SIZE32, task_exec_asynchronous_srpc; .long 0
	.long 0x640f073
	.long .Lname116 /* index: 116 */
	.weak driver_delmod; .long driver_delmod
	.reloc ., R_386_SIZE32, driver_delmod; .long 0
	.long 0xe3d0074
	.long .Lname117 /* index: 117 */
	.weak directory_creatfile; .long directory_creatfile
	.reloc ., R_386_SIZE32, directory_creatfile; .long 0
	.long 0x61d3075
	.long .Lname118 /* index: 118 */
	.weak inode_writev; .long inode_writev
	.reloc ., R_386_SIZE32, inode_writev; .long 0
	.long 0x1ee5076
	.long .Lname119 /* index: 119 */
	.weak sys_select; .long sys_select
	.reloc ., R_386_SIZE32, sys_select; .long 0
	.long 0x69d9b34
	.long .Lname120 /* index: 120 */
	.weak character_device_lookup_nx; .long character_device_lookup_nx
	.reloc ., R_386_SIZE32, character_device_lookup_nx; .long 0
	.long 0xab4d7e8
	.long .Lname121 /* index: 121 */
	.weak cpu_broadcastipi; .long cpu_broadcastipi
	.reloc ., R_386_SIZE32, cpu_broadcastipi; .long 0
	.long 0xc156079
	.long 0 /* index: 122 */
	.long 0
	.long 0
	.long 0
	.long .Lname123 /* index: 123 */
	.weak sys_rt_sigprocmask; .long sys_rt_sigprocmask
	.reloc ., R_386_SIZE32, sys_rt_sigprocmask; .long 0
	.long 0x881507b
	.long .Lname124 /* index: 124 */
	.weak json_parser_init; .long json_parser_init
	.reloc ., R_386_SIZE32, json_parser_init; .long 0
	.long 0x82478f4
	.long 0 /* index: 125 */
	.long 0
	.long 0
	.long 0
	.long .Lname126 /* index: 126 */
	.weak task_rpc_exec_here_onexit; .long task_rpc_exec_here_onexit
	.reloc ., R_386_SIZE32, task_rpc_exec_here_onexit; .long 0
	.long 0x125e004
	.long .Lname127 /* index: 127 */
	.weak fs_filesystems_lock_endwrite; .long fs_filesystems_lock_endwrite
	.reloc ., R_386_SIZE32, fs_filesystems_lock_endwrite; .long 0
	.long 0x254f815
	.long 0 /* index: 128 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 129 */
	.long 0
	.long 0
	.long 0
	.long .Lname130 /* index: 130 */
	.weak character_device_unregister; .long character_device_unregister
	.reloc ., R_386_SIZE32, character_device_unregister; .long 0
	.long 0x26b6082
	.long .Lname131 /* index: 131 */
	.weak debug_dlunlocksections; .long debug_dlunlocksections
	.reloc ., R_386_SIZE32, debug_dlunlocksections; .long 0
	.long 0xaac8083
	.long .Lname132 /* index: 132 */
	.weak sys_creat; .long sys_creat
	.reloc ., R_386_SIZE32, sys_creat; .long 0
	.long 0x95af084
	.long 0 /* index: 133 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 134 */
	.long 0
	.long 0
	.long 0
	.long .Lname135 /* index: 135 */
	.weak vm_datapart_lockwrite_setcore_unsharecow; .long vm_datapart_lockwrite_setcore_unsharecow
	.reloc ., R_386_SIZE32, vm_datapart_lockwrite_setcore_unsharecow; .long 0
	.long 0xe802087
	.long 0 /* index: 136 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 137 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 138 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 139 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 140 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 141 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 142 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 143 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 144 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 145 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 146 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 147 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 148 */
	.long 0
	.long 0
	.long 0
	.long .Lname149 /* index: 149 */
	.weak superblock_mountlock_endwrite; .long superblock_mountlock_endwrite
	.reloc ., R_386_SIZE32, superblock_mountlock_endwrite; .long 0
	.long 0x4a9c095
	.long 0 /* index: 150 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 151 */
	.long 0
	.long 0
	.long 0
	.long .Lname152 /* index: 152 */
	.weak path_traversefull_ex; .long path_traversefull_ex
	.reloc ., R_386_SIZE32, path_traversefull_ex; .long 0
	.long 0xde1f098
	.long .Lname153 /* index: 153 */
	.weak ttybase_device_iread; .long ttybase_device_iread
	.reloc ., R_386_SIZE32, ttybase_device_iread; .long 0
	.long 0x514cac4
	.long 0 /* index: 154 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 155 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 156 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 157 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 158 */
	.long 0
	.long 0
	.long 0
	.long .Lname159 /* index: 159 */
	.weak slab_ffree; .long slab_ffree
	.reloc ., R_386_SIZE32, slab_ffree; .long 0
	.long 0x85b7ac5
	.long .Lname160 /* index: 160 */
	.weak regdump_gpregs; .long regdump_gpregs
	.reloc ., R_386_SIZE32, regdump_gpregs; .long 0
	.long 0xe3c4803
	.long 0 /* index: 161 */
	.long 0
	.long 0
	.long 0
	.long .Lname162 /* index: 162 */
	.weak sys_renameat2; .long sys_renameat2
	.reloc ., R_386_SIZE32, sys_renameat2; .long 0
	.long 0xf8ad0a2
	.long .Lname163 /* index: 163 */
	.weak vm_datablock_lock_trywrite_parts; .long vm_datablock_lock_trywrite_parts
	.reloc ., R_386_SIZE32, vm_datablock_lock_trywrite_parts; .long 0
	.long 0xebf40a3
	.long .Lname164 /* index: 164 */
	.weak sys_modify_ldt; .long sys_modify_ldt
	.reloc ., R_386_SIZE32, sys_modify_ldt; .long 0
	.long 0xf4920a4
	.long 0 /* index: 165 */
	.long 0
	.long 0
	.long 0
	.long .Lname166 /* index: 166 */
	.weak block_device_awritev; .long block_device_awritev
	.reloc ., R_386_SIZE32, block_device_awritev; .long 0
	.long 0x77e80a6
	.long .Lname167 /* index: 167 */
	.weak heap_realloc_untraced; .long heap_realloc_untraced
	.reloc ., R_386_SIZE32, heap_realloc_untraced; .long 0
	.long 0xeeb0ac4
	.long 0 /* index: 168 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 169 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 170 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 171 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 172 */
	.long 0
	.long 0
	.long 0
	.long .Lname173 /* index: 173 */
	.weak _this_vm; .long _this_vm
	.reloc ., R_386_SIZE32, _this_vm; .long 0
	.long 0xaf090ad
	.long 0 /* index: 174 */
	.long 0
	.long 0
	.long 0
	.long .Lname175 /* index: 175 */
	.weak sys_sched_getaffinity; .long sys_sched_getaffinity
	.reloc ., R_386_SIZE32, sys_sched_getaffinity; .long 0
	.long 0xdfc7f79
	.long 0 /* index: 176 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 177 */
	.long 0
	.long 0
	.long 0
	.long .Lname178 /* index: 178 */
	.weak task_setsessionleader; .long task_setsessionleader
	.reloc ., R_386_SIZE32, task_setsessionleader; .long 0
	.long 0x8f700b2
	.long .Lname179 /* index: 179 */
	.weak pagedir_unmap_userspace_nosync; .long pagedir_unmap_userspace_nosync
	.reloc ., R_386_SIZE32, pagedir_unmap_userspace_nosync; .long 0
	.long 0x477a0b3
	.long .Lname180 /* index: 180 */
	.weak pagedir_init; .long pagedir_init
	.reloc ., R_386_SIZE32, pagedir_init; .long 0
	.long 0x72240b4
	.long .Lname181 /* index: 181 */
	.weak _bootidle; .long _bootidle
	.reloc ., R_386_SIZE32, _bootidle; .long 0
	.long 0x66aa0b5
	.long 0 /* index: 182 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 183 */
	.long 0
	.long 0
	.long 0
	.long .Lname184 /* index: 184 */
	.weak task_alloc_synchronous_rpc_nx; .long task_alloc_synchronous_rpc_nx
	.reloc ., R_386_SIZE32, task_alloc_synchronous_rpc_nx; .long 0
	.long 0xa6230b8
	.long .Lname185 /* index: 185 */
	.weak sys_mktty; .long sys_mktty
	.reloc ., R_386_SIZE32, sys_mktty; .long 0
	.long 0x96450b9
	.long 0 /* index: 186 */
	.long 0
	.long 0
	.long 0
	.long .Lname187 /* index: 187 */
	.weak sys_lseek; .long sys_lseek
	.reloc ., R_386_SIZE32, sys_lseek; .long 0
	.long 0x963e0bb
	.long .Lname188 /* index: 188 */
	.weak sys_tgkill; .long sys_tgkill
	.reloc ., R_386_SIZE32, sys_tgkill; .long 0
	.long 0x6abb0bc
	.long 0 /* index: 189 */
	.long 0
	.long 0
	.long 0
	.long .Lname190 /* index: 190 */
	.weak sys_ioprio_set; .long sys_ioprio_set
	.reloc ., R_386_SIZE32, sys_ioprio_set; .long 0
	.long 0x8736804
	.long .Lname191 /* index: 191 */
	.weak vm_datapart_read_unsafe; .long vm_datapart_read_unsafe
	.reloc ., R_386_SIZE32, vm_datapart_read_unsafe; .long 0
	.long 0x4187d75
	.long .Lname192 /* index: 192 */
	.weak directory_readnext_p; .long directory_readnext_p
	.reloc ., R_386_SIZE32, directory_readnext_p; .long 0
	.long 0x431e0c0
	.long 0 /* index: 193 */
	.long 0
	.long 0
	.long 0
	.long .Lname194 /* index: 194 */
	.weak kmalloc_noslab; .long kmalloc_noslab
	.reloc ., R_386_SIZE32, kmalloc_noslab; .long 0
	.long 0x7d5b0c2
	.long .Lname195 /* index: 195 */
	.weak aio_handle_generic_func; .long aio_handle_generic_func
	.reloc ., R_386_SIZE32, aio_handle_generic_func; .long 0
	.long 0x48d30c3
	.long .Lname196 /* index: 196 */
	.weak path_lock_endread; .long path_lock_endread
	.reloc ., R_386_SIZE32, path_lock_endread; .long 0
	.long 0xe28a0c4
	.long .Lname197 /* index: 197 */
	.weak superblock_nodeslock_write; .long superblock_nodeslock_write
	.reloc ., R_386_SIZE32, superblock_nodeslock_write; .long 0
	.long 0x1a890c5
	.long 0 /* index: 198 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 199 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 200 */
	.long 0
	.long 0
	.long 0
	.long .Lname201 /* index: 201 */
	.weak sys_setpriority; .long sys_setpriority
	.reloc ., R_386_SIZE32, sys_setpriority; .long 0
	.long 0x1af40c9
	.long 0 /* index: 202 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 203 */
	.long 0
	.long 0
	.long 0
	.long .Lname204 /* index: 204 */
	.weak mempcpyl; .long mempcpyl
	.reloc ., R_386_SIZE32, mempcpyl; .long 0
	.long 0xc46a0cc
	.long 0 /* index: 205 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 206 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 207 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 208 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 209 */
	.long 0
	.long 0
	.long 0
	.long .Lname210 /* index: 210 */
	.weak kernel_pty_oprinter; .long kernel_pty_oprinter
	.reloc ., R_386_SIZE32, kernel_pty_oprinter; .long 0
	.long 0x3ee0d2
	.long .Lname211 /* index: 211 */
	.weak inode_readall_phys; .long inode_readall_phys
	.reloc ., R_386_SIZE32, inode_readall_phys; .long 0
	.long 0x4a850d3
	.long .Lname212 /* index: 212 */
	.weak devfs_lock_end; .long devfs_lock_end
	.reloc ., R_386_SIZE32, devfs_lock_end; .long 0
	.long 0x96ed0d4
	.long .Lname213 /* index: 213 */
	.weak sys_reboot; .long sys_reboot
	.reloc ., R_386_SIZE32, sys_reboot; .long 0
	.long 0x68c46f4
	.long .Lname214 /* index: 214 */
	.weak block_device_partition_readv; .long block_device_partition_readv
	.reloc ., R_386_SIZE32, block_device_partition_readv; .long 0
	.long 0x5240d6
	.long .Lname215 /* index: 215 */
	.weak terminal_poll_owrite; .long terminal_poll_owrite
	.reloc ., R_386_SIZE32, terminal_poll_owrite; .long 0
	.long 0xc9df3a5
	.long .Lname216 /* index: 216 */
	.weak superblock_nodeslock_write_nx; .long superblock_nodeslock_write_nx
	.reloc ., R_386_SIZE32, superblock_nodeslock_write_nx; .long 0
	.long 0x90cd0d8
	.long .Lname217 /* index: 217 */
	.weak rwlock_read; .long rwlock_read
	.reloc ., R_386_SIZE32, rwlock_read; .long 0
	.long 0xa8f6824
	.long 0 /* index: 218 */
	.long 0
	.long 0
	.long 0
	.long .Lname219 /* index: 219 */
	.weak sys_unlink; .long sys_unlink
	.reloc ., R_386_SIZE32, sys_unlink; .long 0
	.long 0x6c4a0db
	.long 0 /* index: 220 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 221 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 222 */
	.long 0
	.long 0
	.long 0
	.long .Lname223 /* index: 223 */
	.weak handle_get_inode; .long handle_get_inode
	.reloc ., R_386_SIZE32, handle_get_inode; .long 0
	.long 0x3740025
	.long 0 /* index: 224 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 225 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 226 */
	.long 0
	.long 0
	.long 0
	.long .Lname227 /* index: 227 */
	.weak page_malloc; .long page_malloc
	.reloc ., R_386_SIZE32, page_malloc; .long 0
	.long 0x64270e3
	.long 0 /* index: 228 */
	.long 0
	.long 0
	.long 0
	.long .Lname229 /* index: 229 */
	.weak vmb_getfree; .long vmb_getfree
	.reloc ., R_386_SIZE32, vmb_getfree; .long 0
	.long 0xdb7e0e5
	.long 0 /* index: 230 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 231 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 232 */
	.long 0
	.long 0
	.long 0
	.long .Lname233 /* index: 233 */
	.weak vio_addl; .long vio_addl
	.reloc ., R_386_SIZE32, vio_addl; .long 0
	.long 0x557d7c
	.long 0 /* index: 234 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 235 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 236 */
	.long 0
	.long 0
	.long 0
	.long .Lname237 /* index: 237 */
	.weak sys_geteuid32; .long sys_geteuid32
	.reloc ., R_386_SIZE32, sys_geteuid32; .long 0
	.long 0x1c2aad2
	.long .Lname238 /* index: 238 */
	.weak unwind_fde_scan; .long unwind_fde_scan
	.reloc ., R_386_SIZE32, unwind_fde_scan; .long 0
	.long 0x4b260ee
	.long 0 /* index: 239 */
	.long 0
	.long 0
	.long 0
	.long .Lname240 /* index: 240 */
	.weak pagedir_prepare_map_p; .long pagedir_prepare_map_p
	.reloc ., R_386_SIZE32, pagedir_prepare_map_p; .long 0
	.long 0x174a0f0
	.long .Lname241 /* index: 241 */
	.weak superblock_nodeslock_tryupgrade; .long superblock_nodeslock_tryupgrade
	.reloc ., R_386_SIZE32, superblock_nodeslock_tryupgrade; .long 0
	.long 0xa745da5
	.long 0 /* index: 242 */
	.long 0
	.long 0
	.long 0
	.long .Lname243 /* index: 243 */
	.weak heap_alloc; .long heap_alloc
	.reloc ., R_386_SIZE32, heap_alloc; .long 0
	.long 0x652dad3
	.long .Lname244 /* index: 244 */
	.weak path_lock_tryread; .long path_lock_tryread
	.reloc ., R_386_SIZE32, path_lock_tryread; .long 0
	.long 0xe03a0f4
	.long .Lname245 /* index: 245 */
	.weak vm_datapart_lock_write; .long vm_datapart_lock_write
	.reloc ., R_386_SIZE32, vm_datapart_lock_write; .long 0
	.long 0x44710f5
	.long 0 /* index: 246 */
	.long 0
	.long 0
	.long 0
	.long .Lname247 /* index: 247 */
	.weak debuginfo_cu_parser_skipattr; .long debuginfo_cu_parser_skipattr
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_skipattr; .long 0
	.long 0x7e882b2
	.long .Lname248 /* index: 248 */
	.weak unicode_32to8; .long unicode_32to8
	.reloc ., R_386_SIZE32, unicode_32to8; .long 0
	.long 0x76940f8
	.long .Lname249 /* index: 249 */
	.weak sys_settimeofday; .long sys_settimeofday
	.reloc ., R_386_SIZE32, sys_settimeofday; .long 0
	.long 0x53ec0f9
	.long .Lname250 /* index: 250 */
	.weak x86_pagedir_syncone; .long x86_pagedir_syncone
	.reloc ., R_386_SIZE32, x86_pagedir_syncone; .long 0
	.long 0xd040825
	.long 0 /* index: 251 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 252 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 253 */
	.long 0
	.long 0
	.long 0
	.long .Lname254 /* index: 254 */
	.weak vio_copytovio_from_phys; .long vio_copytovio_from_phys
	.reloc ., R_386_SIZE32, vio_copytovio_from_phys; .long 0
	.long 0x33623c3
	.long .Lname255 /* index: 255 */
	.weak _Unwind_Resume; .long _Unwind_Resume
	.reloc ., R_386_SIZE32, _Unwind_Resume; .long 0
	.long 0x8d2aad5
	.long 0 /* index: 256 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 257 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 258 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 259 */
	.long 0
	.long 0
	.long 0
	.long .Lname260 /* index: 260 */
	.weak sys_select64; .long sys_select64
	.reloc ., R_386_SIZE32, sys_select64; .long 0
	.long 0xd9b3104
	.long .Lname261 /* index: 261 */
	.weak task_rpc_exec_here; .long task_rpc_exec_here
	.reloc ., R_386_SIZE32, task_rpc_exec_here; .long 0
	.long 0x5541105
	.long 0 /* index: 262 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 263 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 264 */
	.long 0
	.long 0
	.long 0
	.long .Lname265 /* index: 265 */
	.weak vm_node_destroy; .long vm_node_destroy
	.reloc ., R_386_SIZE32, vm_node_destroy; .long 0
	.long 0xc9f6109
	.long 0 /* index: 266 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 267 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 268 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 269 */
	.long 0
	.long 0
	.long 0
	.long .Lname270 /* index: 270 */
	.weak sys_open; .long sys_open
	.reloc ., R_386_SIZE32, sys_open; .long 0
	.long 0x96610e
	.long 0 /* index: 271 */
	.long 0
	.long 0
	.long 0
	.long .Lname272 /* index: 272 */
	.weak handle_trylookup; .long handle_trylookup
	.reloc ., R_386_SIZE32, handle_trylookup; .long 0
	.long 0x519e110
	.long 0 /* index: 273 */
	.long 0
	.long 0
	.long 0
	.long .Lname274 /* index: 274 */
	.weak rawmemrchr; .long rawmemrchr
	.reloc ., R_386_SIZE32, rawmemrchr; .long 0
	.long 0x3c30112
	.long 0 /* index: 275 */
	.long 0
	.long 0
	.long 0
	.long .Lname276 /* index: 276 */
	.weak vm_node_insert; .long vm_node_insert
	.reloc ., R_386_SIZE32, vm_node_insert; .long 0
	.long 0x6a0c114
	.long .Lname277 /* index: 277 */
	.weak cpu_apply_kcpustate; .long cpu_apply_kcpustate
	.reloc ., R_386_SIZE32, cpu_apply_kcpustate; .long 0
	.long 0xa8cb115
	.long 0 /* index: 278 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 279 */
	.long 0
	.long 0
	.long 0
	.long .Lname280 /* index: 280 */
	.weak instruction_length; .long instruction_length
	.reloc ., R_386_SIZE32, instruction_length; .long 0
	.long 0xa852118
	.long .Lname281 /* index: 281 */
	.weak sys_faccessat; .long sys_faccessat
	.reloc ., R_386_SIZE32, sys_faccessat; .long 0
	.long 0x295f584
	.long .Lname282 /* index: 282 */
	.weak task_isconnected; .long task_isconnected
	.reloc ., R_386_SIZE32, task_isconnected; .long 0
	.long 0x62c99b4
	.long .Lname283 /* index: 283 */
	.weak sys_sigaltstack; .long sys_sigaltstack
	.reloc ., R_386_SIZE32, sys_sigaltstack; .long 0
	.long 0xad3211b
	.long .Lname284 /* index: 284 */
	.weak ringbuffer_unread; .long ringbuffer_unread
	.reloc ., R_386_SIZE32, ringbuffer_unread; .long 0
	.long 0xf8043c4
	.long 0 /* index: 285 */
	.long 0
	.long 0
	.long 0
	.long .Lname286 /* index: 286 */
	.weak rwlock_trywrite; .long rwlock_trywrite
	.reloc ., R_386_SIZE32, rwlock_trywrite; .long 0
	.long 0xb541ff5
	.long .Lname287 /* index: 287 */
	.weak kernel_terminal_check_sigttou; .long kernel_terminal_check_sigttou
	.reloc ., R_386_SIZE32, kernel_terminal_check_sigttou; .long 0
	.long 0xf867d85
	.long 0 /* index: 288 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 289 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 290 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 291 */
	.long 0
	.long 0
	.long 0
	.long .Lname292 /* index: 292 */
	.weak isr_register_greedy_at; .long isr_register_greedy_at
	.reloc ., R_386_SIZE32, isr_register_greedy_at; .long 0
	.long 0x7f76124
	.long .Lname293 /* index: 293 */
	.weak driver_with_filename; .long driver_with_filename
	.reloc ., R_386_SIZE32, driver_with_filename; .long 0
	.long 0xb2e6125
	.long 0 /* index: 294 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 295 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 296 */
	.long 0
	.long 0
	.long 0
	.long .Lname297 /* index: 297 */
	.weak json_writer_putnull; .long json_writer_putnull
	.reloc ., R_386_SIZE32, json_writer_putnull; .long 0
	.long 0xd67dadc
	.long 0 /* index: 298 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 299 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 300 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 301 */
	.long 0
	.long 0
	.long 0
	.long .Lname302 /* index: 302 */
	.weak dbg_fillscreen; .long dbg_fillscreen
	.reloc ., R_386_SIZE32, dbg_fillscreen; .long 0
	.long 0xb4f412e
	.long .Lname303 /* index: 303 */
	.weak vm_datablock_anonymous_zero; .long vm_datablock_anonymous_zero
	.reloc ., R_386_SIZE32, vm_datablock_anonymous_zero; .long 0
	.long 0x142212f
	.long 0 /* index: 304 */
	.long 0
	.long 0
	.long 0
	.long .Lname305 /* index: 305 */
	.weak mempcpyq; .long mempcpyq
	.reloc ., R_386_SIZE32, mempcpyq; .long 0
	.long 0xc46a131
	.long .Lname306 /* index: 306 */
	.weak syscall_emulate_sysenter; .long syscall_emulate_sysenter
	.reloc ., R_386_SIZE32, syscall_emulate_sysenter; .long 0
	.long 0x4a5f132
	.long .Lname307 /* index: 307 */
	.weak vm_sync; .long vm_sync
	.reloc ., R_386_SIZE32, vm_sync; .long 0
	.long 0xd36b033
	.long .Lname308 /* index: 308 */
	.weak x86_syscall_register_count; .long x86_syscall_register_count
	.reloc ., R_386_SIZE32, x86_syscall_register_count; .long 0
	.long 0xf7d7134
	.long .Lname309 /* index: 309 */
	.weak vm_datablock_physical_type; .long vm_datablock_physical_type
	.reloc ., R_386_SIZE32, vm_datablock_physical_type; .long 0
	.long 0xea91135
	.long 0 /* index: 310 */
	.long 0
	.long 0
	.long 0
	.long .Lname311 /* index: 311 */
	.weak mempcpyw; .long mempcpyw
	.reloc ., R_386_SIZE32, mempcpyw; .long 0
	.long 0xc46a137
	.long 0 /* index: 312 */
	.long 0
	.long 0
	.long 0
	.long .Lname313 /* index: 313 */
	.weak vm_datapart_split; .long vm_datapart_split
	.reloc ., R_386_SIZE32, vm_datapart_split; .long 0
	.long 0x2bf5034
	.long .Lname314 /* index: 314 */
	.weak unwind_getreg_sfpustate; .long unwind_getreg_sfpustate
	.reloc ., R_386_SIZE32, unwind_getreg_sfpustate; .long 0
	.long 0xb8c43c5
	.long .Lname315 /* index: 315 */
	.weak sys_fork; .long sys_fork
	.reloc ., R_386_SIZE32, sys_fork; .long 0
	.long 0x95d13b
	.long 0 /* index: 316 */
	.long 0
	.long 0
	.long 0
	.long .Lname317 /* index: 317 */
	.weak dbg_readline; .long dbg_readline
	.reloc ., R_386_SIZE32, dbg_readline; .long 0
	.long 0xdd3fac5
	.long 0 /* index: 318 */
	.long 0
	.long 0
	.long 0
	.long .Lname319 /* index: 319 */
	.weak page_iszero; .long page_iszero
	.reloc ., R_386_SIZE32, page_iszero; .long 0
	.long 0x67d713f
	.long 0 /* index: 320 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 321 */
	.long 0
	.long 0
	.long 0
	.long .Lname322 /* index: 322 */
	.weak character_device_register; .long character_device_register
	.reloc ., R_386_SIZE32, character_device_register; .long 0
	.long 0x4292142
	.long 0 /* index: 323 */
	.long 0
	.long 0
	.long 0
	.long .Lname324 /* index: 324 */
	.weak syscall_tracing_getenabled; .long syscall_tracing_getenabled
	.reloc ., R_386_SIZE32, syscall_tracing_getenabled; .long 0
	.long 0xab3b144
	.long 0 /* index: 325 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 326 */
	.long 0
	.long 0
	.long 0
	.long .Lname327 /* index: 327 */
	.weak vio_xorw; .long vio_xorw
	.reloc ., R_386_SIZE32, vio_xorw; .long 0
	.long 0x56f147
	.long 0 /* index: 328 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 329 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 330 */
	.long 0
	.long 0
	.long 0
	.long .Lname331 /* index: 331 */
	.weak page_malloc_at; .long page_malloc_at
	.reloc ., R_386_SIZE32, page_malloc_at; .long 0
	.long 0x70ef1a4
	.long 0 /* index: 332 */
	.long 0
	.long 0
	.long 0
	.long .Lname333 /* index: 333 */
	.weak vio_writeb; .long vio_writeb
	.reloc ., R_386_SIZE32, vio_writeb; .long 0
	.long 0x6f0dae2
	.long 0 /* index: 334 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 335 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 336 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 337 */
	.long 0
	.long 0
	.long 0
	.long .Lname338 /* index: 338 */
	.weak vio_xorb; .long vio_xorb
	.reloc ., R_386_SIZE32, vio_xorb; .long 0
	.long 0x56f152
	.long 0 /* index: 339 */
	.long 0
	.long 0
	.long 0
	.long .Lname340 /* index: 340 */
	.weak sys_socket; .long sys_socket
	.reloc ., R_386_SIZE32, sys_socket; .long 0
	.long 0x6a23154
	.long .Lname341 /* index: 341 */
	.weak inode_areadallv_phys; .long inode_areadallv_phys
	.reloc ., R_386_SIZE32, inode_areadallv_phys; .long 0
	.long 0xe6b7ab3
	.long .Lname342 /* index: 342 */
	.weak mouse_device_hwheel; .long mouse_device_hwheel
	.reloc ., R_386_SIZE32, mouse_device_hwheel; .long 0
	.long 0xb5d892c
	.long .Lname343 /* index: 343 */
	.weak vpage_free; .long vpage_free
	.reloc ., R_386_SIZE32, vpage_free; .long 0
	.long 0xdb20ec5
	.long 0 /* index: 344 */
	.long 0
	.long 0
	.long 0
	.long .Lname345 /* index: 345 */
	.weak devfs_lock_read; .long devfs_lock_read
	.reloc ., R_386_SIZE32, devfs_lock_read; .long 0
	.long 0x6efc2e4
	.long 0 /* index: 346 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 347 */
	.long 0
	.long 0
	.long 0
	.long .Lname348 /* index: 348 */
	.weak vio_xorl; .long vio_xorl
	.reloc ., R_386_SIZE32, vio_xorl; .long 0
	.long 0x56f15c
	.long 0 /* index: 349 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 350 */
	.long 0
	.long 0
	.long 0
	.long .Lname351 /* index: 351 */
	.weak vm_datapart_decref_and_merge; .long vm_datapart_decref_and_merge
	.reloc ., R_386_SIZE32, vm_datapart_decref_and_merge; .long 0
	.long 0x3d762e5
	.long 0 /* index: 352 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 353 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 354 */
	.long 0
	.long 0
	.long 0
	.long .Lname355 /* index: 355 */
	.weak handle_get_vfs; .long handle_get_vfs
	.reloc ., R_386_SIZE32, handle_get_vfs; .long 0
	.long 0x5834163
	.long 0 /* index: 356 */
	.long 0
	.long 0
	.long 0
	.long .Lname357 /* index: 357 */
	.weak task_serve; .long task_serve
	.reloc ., R_386_SIZE32, task_serve; .long 0
	.long 0x16e6165
	.long 0 /* index: 358 */
	.long 0
	.long 0
	.long 0
	.long .Lname359 /* index: 359 */
	.weak error_rethrow; .long error_rethrow
	.reloc ., R_386_SIZE32, error_rethrow; .long 0
	.long 0x4539167
	.long 0 /* index: 360 */
	.long 0
	.long 0
	.long 0
	.long .Lname361 /* index: 361 */
	.weak unwind_cfa_sigframe_apply; .long unwind_cfa_sigframe_apply
	.reloc ., R_386_SIZE32, unwind_cfa_sigframe_apply; .long 0
	.long 0xd478169
	.long 0 /* index: 362 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 363 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 364 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 365 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 366 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 367 */
	.long 0
	.long 0
	.long 0
	.long .Lname368 /* index: 368 */
	.weak vm_datapart_map_ram_autoprop; .long vm_datapart_map_ram_autoprop
	.reloc ., R_386_SIZE32, vm_datapart_map_ram_autoprop; .long 0
	.long 0x9192170
	.long 0 /* index: 369 */
	.long 0
	.long 0
	.long 0
	.long .Lname370 /* index: 370 */
	.weak rawmemchr; .long rawmemchr
	.reloc ., R_386_SIZE32, rawmemchr; .long 0
	.long 0xe3c4172
	.long .Lname371 /* index: 371 */
	.weak task_pushconnections; .long task_pushconnections
	.reloc ., R_386_SIZE32, task_pushconnections; .long 0
	.long 0xae3c173
	.long .Lname372 /* index: 372 */
	.weak block_device_write_sync; .long block_device_write_sync
	.reloc ., R_386_SIZE32, block_device_write_sync; .long 0
	.long 0x213be13
	.long .Lname373 /* index: 373 */
	.weak rwlock_write_aggressive; .long rwlock_write_aggressive
	.reloc ., R_386_SIZE32, rwlock_write_aggressive; .long 0
	.long 0x8f0f175
	.long 0 /* index: 374 */
	.long 0
	.long 0
	.long 0
	.long .Lname375 /* index: 375 */
	.weak rwlock_tryread_readonly; .long rwlock_tryread_readonly
	.reloc ., R_386_SIZE32, rwlock_tryread_readonly; .long 0
	.long 0x9439ae9
	.long .Lname376 /* index: 376 */
	.weak heap_align_nx; .long heap_align_nx
	.reloc ., R_386_SIZE32, heap_align_nx; .long 0
	.long 0xc466178
	.long .Lname377 /* index: 377 */
	.weak sys_futimesat64; .long sys_futimesat64
	.reloc ., R_386_SIZE32, sys_futimesat64; .long 0
	.long 0xa943594
	.long 0 /* index: 378 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 379 */
	.long 0
	.long 0
	.long 0
	.long .Lname380 /* index: 380 */
	.weak vm_datapart_lockread_setcore_nx; .long vm_datapart_lockread_setcore_nx
	.reloc ., R_386_SIZE32, vm_datapart_lockread_setcore_nx; .long 0
	.long 0x7cb34d8
	.long 0 /* index: 381 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 382 */
	.long 0
	.long 0
	.long 0
	.long .Lname383 /* index: 383 */
	.weak sys_close; .long sys_close
	.reloc ., R_386_SIZE32, sys_close; .long 0
	.long 0x95a6d95
	.long 0 /* index: 384 */
	.long 0
	.long 0
	.long 0
	.long .Lname385 /* index: 385 */
	.weak pagedir_translate_p; .long pagedir_translate_p
	.reloc ., R_386_SIZE32, pagedir_translate_p; .long 0
	.long 0xc3e9840
	.long .Lname386 /* index: 386 */
	.weak vm_datapart_pageaddr; .long vm_datapart_pageaddr
	.reloc ., R_386_SIZE32, vm_datapart_pageaddr; .long 0
	.long 0x2085182
	.long .Lname387 /* index: 387 */
	.weak character_device_sync; .long character_device_sync
	.reloc ., R_386_SIZE32, character_device_sync; .long 0
	.long 0x98ba183
	.long .Lname388 /* index: 388 */
	.weak sys_kstat; .long sys_kstat
	.reloc ., R_386_SIZE32, sys_kstat; .long 0
	.long 0x962d184
	.long 0 /* index: 389 */
	.long 0
	.long 0
	.long 0
	.long .Lname390 /* index: 390 */
	.weak sys_process_vm_readv; .long sys_process_vm_readv
	.reloc ., R_386_SIZE32, sys_process_vm_readv; .long 0
	.long 0xc34a186
	.long .Lname391 /* index: 391 */
	.weak kffree; .long kffree
	.reloc ., R_386_SIZE32, kffree; .long 0
	.long 0x71cd8b5
	.long .Lname392 /* index: 392 */
	.weak heap_realign_nx; .long heap_realign_nx
	.reloc ., R_386_SIZE32, heap_realign_nx; .long 0
	.long 0xa9ce188
	.long .Lname393 /* index: 393 */
	.weak task_setup_kernel; .long task_setup_kernel
	.reloc ., R_386_SIZE32, task_setup_kernel; .long 0
	.long 0x4fac2ec
	.long 0 /* index: 394 */
	.long 0
	.long 0
	.long 0
	.long .Lname395 /* index: 395 */
	.weak x86_this_dfstack_part; .long x86_this_dfstack_part
	.reloc ., R_386_SIZE32, x86_this_dfstack_part; .long 0
	.long 0x1d169a4
	.long 0 /* index: 396 */
	.long 0
	.long 0
	.long 0
	.long .Lname397 /* index: 397 */
	.weak sys_sched_getscheduler; .long sys_sched_getscheduler
	.reloc ., R_386_SIZE32, sys_sched_getscheduler; .long 0
	.long 0xdf96042
	.long 0 /* index: 398 */
	.long 0
	.long 0
	.long 0
	.long .Lname399 /* index: 399 */
	.weak vm_datapart_map_ram; .long vm_datapart_map_ram
	.reloc ., R_386_SIZE32, vm_datapart_map_ram; .long 0
	.long 0x6d95aed
	.long 0 /* index: 400 */
	.long 0
	.long 0
	.long 0
	.long .Lname401 /* index: 401 */
	.weak regdump_icpustate; .long regdump_icpustate
	.reloc ., R_386_SIZE32, regdump_icpustate; .long 0
	.long 0xbf44ab5
	.long 0 /* index: 402 */
	.long 0
	.long 0
	.long 0
	.long .Lname403 /* index: 403 */
	.weak keymap_init_en_US; .long keymap_init_en_US
	.reloc ., R_386_SIZE32, keymap_init_en_US; .long 0
	.long 0x2701193
	.long 0 /* index: 404 */
	.long 0
	.long 0
	.long 0
	.long .Lname405 /* index: 405 */
	.weak inode_datablock_type; .long inode_datablock_type
	.reloc ., R_386_SIZE32, inode_datablock_type; .long 0
	.long 0x60c0195
	.long 0 /* index: 406 */
	.long 0
	.long 0
	.long 0
	.long .Lname407 /* index: 407 */
	.weak ttybase_device_stat; .long ttybase_device_stat
	.reloc ., R_386_SIZE32, ttybase_device_stat; .long 0
	.long 0xb53ee94
	.long 0 /* index: 408 */
	.long 0
	.long 0
	.long 0
	.long .Lname409 /* index: 409 */
	.weak krand; .long krand
	.reloc ., R_386_SIZE32, krand; .long 0
	.long 0x728844
	.long 0 /* index: 410 */
	.long 0
	.long 0
	.long 0
	.long .Lname411 /* index: 411 */
	.weak inode_awritek; .long inode_awritek
	.reloc ., R_386_SIZE32, inode_awritek; .long 0
	.long 0x8bea19b
	.long 0 /* index: 412 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 413 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 414 */
	.long 0
	.long 0
	.long 0
	.long .Lname415 /* index: 415 */
	.weak block_device_aread_phys; .long block_device_aread_phys
	.reloc ., R_386_SIZE32, block_device_aread_phys; .long 0
	.long 0xf401fe3
	.long 0 /* index: 416 */
	.long 0
	.long 0
	.long 0
	.long .Lname417 /* index: 417 */
	.weak rawmemrchrq; .long rawmemrchrq
	.reloc ., R_386_SIZE32, rawmemrchrq; .long 0
	.long 0xc3011a1
	.long .Lname418 /* index: 418 */
	.weak vm86_outb; .long vm86_outb
	.reloc ., R_386_SIZE32, vm86_outb; .long 0
	.long 0xbc611a2
	.long 0 /* index: 419 */
	.long 0
	.long 0
	.long 0
	.long .Lname420 /* index: 420 */
	.weak swap_read; .long swap_read
	.reloc ., R_386_SIZE32, swap_read; .long 0
	.long 0x866f1a4
	.long .Lname421 /* index: 421 */
	.weak path_getcasechild_and_parent_inode; .long path_getcasechild_and_parent_inode
	.reloc ., R_386_SIZE32, path_getcasechild_and_parent_inode; .long 0
	.long 0xc54a1a5
	.long .Lname422 /* index: 422 */
	.weak _this_library_listdef; .long _this_library_listdef
	.reloc ., R_386_SIZE32, _this_library_listdef; .long 0
	.long 0x58b71a6
	.long .Lname423 /* index: 423 */
	.weak rawmemrchrw; .long rawmemrchrw
	.reloc ., R_386_SIZE32, rawmemrchrw; .long 0
	.long 0xc3011a7
	.long .Lname424 /* index: 424 */
	.weak task_raisesignalthread_nx; .long task_raisesignalthread_nx
	.reloc ., R_386_SIZE32, task_raisesignalthread_nx; .long 0
	.long 0xc7281a8
	.long 0 /* index: 425 */
	.long 0
	.long 0
	.long 0
	.long .Lname426 /* index: 426 */
	.weak regdump_sgregs_with_cs_ss_tr_ldt; .long regdump_sgregs_with_cs_ss_tr_ldt
	.reloc ., R_386_SIZE32, regdump_sgregs_with_cs_ss_tr_ldt; .long 0
	.long 0x5368ac4
	.long .Lname427 /* index: 427 */
	.weak vm_addhwbreak; .long vm_addhwbreak
	.reloc ., R_386_SIZE32, vm_addhwbreak; .long 0
	.long 0x2ecf1ab
	.long .Lname428 /* index: 428 */
	.weak sys_ioctl; .long sys_ioctl
	.reloc ., R_386_SIZE32, sys_ioctl; .long 0
	.long 0x96021ac
	.long .Lname429 /* index: 429 */
	.weak vm_unmap_kernel_ram; .long vm_unmap_kernel_ram
	.reloc ., R_386_SIZE32, vm_unmap_kernel_ram; .long 0
	.long 0x1d6b1ad
	.long 0 /* index: 430 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 431 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 432 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 433 */
	.long 0
	.long 0
	.long 0
	.long .Lname434 /* index: 434 */
	.weak block_device_awritev_sector; .long block_device_awritev_sector
	.reloc ., R_386_SIZE32, block_device_awritev_sector; .long 0
	.long 0x173a1b2
	.long .Lname435 /* index: 435 */
	.weak block_device_areadv_phys; .long block_device_areadv_phys
	.reloc ., R_386_SIZE32, block_device_areadv_phys; .long 0
	.long 0x1e172f3
	.long 0 /* index: 436 */
	.long 0
	.long 0
	.long 0
	.long .Lname437 /* index: 437 */
	.weak vm_datablock_debugheap_type; .long vm_datablock_debugheap_type
	.reloc ., R_386_SIZE32, vm_datablock_debugheap_type; .long 0
	.long 0xb4f91b5
	.long 0 /* index: 438 */
	.long 0
	.long 0
	.long 0
	.long .Lname439 /* index: 439 */
	.weak vm86_outw; .long vm86_outw
	.reloc ., R_386_SIZE32, vm86_outw; .long 0
	.long 0xbc611b7
	.long .Lname440 /* index: 440 */
	.weak __predict_update_edx; .long __predict_update_edx
	.reloc ., R_386_SIZE32, __predict_update_edx; .long 0
	.long 0x45521b8
	.long .Lname441 /* index: 441 */
	.weak dbg_trygetuni; .long dbg_trygetuni
	.reloc ., R_386_SIZE32, dbg_trygetuni; .long 0
	.long 0x551d1b9
	.long 0 /* index: 442 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 443 */
	.long 0
	.long 0
	.long 0
	.long .Lname444 /* index: 444 */
	.weak rawmemrchrl; .long rawmemrchrl
	.reloc ., R_386_SIZE32, rawmemrchrl; .long 0
	.long 0xc3011bc
	.long 0 /* index: 445 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 446 */
	.long 0
	.long 0
	.long 0
	.long .Lname447 /* index: 447 */
	.weak rwlock_downgrade; .long rwlock_downgrade
	.reloc ., R_386_SIZE32, rwlock_downgrade; .long 0
	.long 0x9e642f5
	.long .Lname448 /* index: 448 */
	.weak slab_kmalloc20; .long slab_kmalloc20
	.reloc ., R_386_SIZE32, slab_kmalloc20; .long 0
	.long 0x66b31c0
	.long 0 /* index: 449 */
	.long 0
	.long 0
	.long 0
	.long .Lname450 /* index: 450 */
	.weak sys_setuid; .long sys_setuid
	.reloc ., R_386_SIZE32, sys_setuid; .long 0
	.long 0x69b0b64
	.long .Lname451 /* index: 451 */
	.weak sys_getgroups; .long sys_getgroups
	.reloc ., R_386_SIZE32, sys_getgroups; .long 0
	.long 0x1e231c3
	.long .Lname452 /* index: 452 */
	.weak json_parser_getfloat; .long json_parser_getfloat
	.reloc ., R_386_SIZE32, json_parser_getfloat; .long 0
	.long 0xf5511c4
	.long .Lname453 /* index: 453 */
	.weak pagedir_isuseraccessible; .long pagedir_isuseraccessible
	.reloc ., R_386_SIZE32, pagedir_isuseraccessible; .long 0
	.long 0x24251c5
	.long 0 /* index: 454 */
	.long 0
	.long 0
	.long 0
	.long .Lname455 /* index: 455 */
	.weak x86_vm86_outw; .long x86_vm86_outw
	.reloc ., R_386_SIZE32, x86_vm86_outw; .long 0
	.long 0x1a01c7
	.long .Lname456 /* index: 456 */
	.weak sys_futex; .long sys_futex
	.reloc ., R_386_SIZE32, sys_futex; .long 0
	.long 0x95db1c8
	.long 0 /* index: 457 */
	.long 0
	.long 0
	.long 0
	.long .Lname458 /* index: 458 */
	.weak heap_alloc_untraced; .long heap_alloc_untraced
	.reloc ., R_386_SIZE32, heap_alloc_untraced; .long 0
	.long 0x8158a14
	.long 0 /* index: 459 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 460 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 461 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 462 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 463 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 464 */
	.long 0
	.long 0
	.long 0
	.long .Lname465 /* index: 465 */
	.weak rwlock_end; .long rwlock_end
	.reloc ., R_386_SIZE32, rwlock_end; .long 0
	.long 0x5a8c674
	.long .Lname466 /* index: 466 */
	.weak x86_vm86_outb; .long x86_vm86_outb
	.reloc ., R_386_SIZE32, x86_vm86_outb; .long 0
	.long 0x1a01d2
	.long .Lname467 /* index: 467 */
	.weak unwind_setreg_ucpustate; .long unwind_setreg_ucpustate
	.reloc ., R_386_SIZE32, unwind_setreg_ucpustate; .long 0
	.long 0xb8d01b5
	.long .Lname468 /* index: 468 */
	.weak directory_readnext; .long directory_readnext
	.reloc ., R_386_SIZE32, directory_readnext; .long 0
	.long 0x6a431d4
	.long .Lname469 /* index: 469 */
	.weak _this_idle; .long _this_idle
	.reloc ., R_386_SIZE32, _this_idle; .long 0
	.long 0x9391d5
	.long .Lname470 /* index: 470 */
	.weak disasm_print_line_nolf; .long disasm_print_line_nolf
	.reloc ., R_386_SIZE32, disasm_print_line_nolf; .long 0
	.long 0xc69e1d6
	.long 0 /* index: 471 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 472 */
	.long 0
	.long 0
	.long 0
	.long .Lname473 /* index: 473 */
	.weak lookup_taskpid; .long lookup_taskpid
	.reloc ., R_386_SIZE32, lookup_taskpid; .long 0
	.long 0xcece5a4
	.long 0 /* index: 474 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 475 */
	.long 0
	.long 0
	.long 0
	.long .Lname476 /* index: 476 */
	.weak sys_iopl; .long sys_iopl
	.reloc ., R_386_SIZE32, sys_iopl; .long 0
	.long 0x9601dc
	.long 0 /* index: 477 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 478 */
	.long 0
	.long 0
	.long 0
	.long .Lname479 /* index: 479 */
	.weak vm_datapart_lock_tryupgrade; .long vm_datapart_lock_tryupgrade
	.reloc ., R_386_SIZE32, vm_datapart_lock_tryupgrade; .long 0
	.long 0x92aa5a5
	.long .Lname480 /* index: 480 */
	.weak pagedir_iswritable_p; .long pagedir_iswritable_p
	.reloc ., R_386_SIZE32, pagedir_iswritable_p; .long 0
	.long 0x9aa4b40
	.long .Lname481 /* index: 481 */
	.weak __asm32_syscallrouter_int80; .long __asm32_syscallrouter_int80
	.reloc ., R_386_SIZE32, __asm32_syscallrouter_int80; .long 0
	.long 0x8610850
	.long 0 /* index: 482 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 483 */
	.long 0
	.long 0
	.long 0
	.long .Lname484 /* index: 484 */
	.weak sys_mkdirat; .long sys_mkdirat
	.reloc ., R_386_SIZE32, sys_mkdirat; .long 0
	.long 0x46201e4
	.long .Lname485 /* index: 485 */
	.weak sys_unshare; .long sys_unshare
	.reloc ., R_386_SIZE32, sys_unshare; .long 0
	.long 0xc22e1e5
	.long .Lname486 /* index: 486 */
	.weak inode_awritev; .long inode_awritev
	.reloc ., R_386_SIZE32, inode_awritev; .long 0
	.long 0x8bea1e6
	.long 0 /* index: 487 */
	.long 0
	.long 0
	.long 0
	.long .Lname488 /* index: 488 */
	.weak rwlock_upgrade_nx; .long rwlock_upgrade_nx
	.reloc ., R_386_SIZE32, rwlock_upgrade_nx; .long 0
	.long 0x2f591e8
	.long .Lname489 /* index: 489 */
	.weak character_device_destroy; .long character_device_destroy
	.reloc ., R_386_SIZE32, character_device_destroy; .long 0
	.long 0xa3621e9
	.long 0 /* index: 490 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 491 */
	.long 0
	.long 0
	.long 0
	.long .Lname492 /* index: 492 */
	.weak ringbuffer_poll; .long ringbuffer_poll
	.reloc ., R_386_SIZE32, ringbuffer_poll; .long 0
	.long 0x8bfb1ec
	.long .Lname493 /* index: 493 */
	.weak cpu_enable_preemptive_interrupts_nopr; .long cpu_enable_preemptive_interrupts_nopr
	.reloc ., R_386_SIZE32, cpu_enable_preemptive_interrupts_nopr; .long 0
	.long 0x746d852
	.long 0 /* index: 494 */
	.long 0
	.long 0
	.long 0
	.long .Lname495 /* index: 495 */
	.weak vm_datapart_freeram; .long vm_datapart_freeram
	.reloc ., R_386_SIZE32, vm_datapart_freeram; .long 0
	.long 0x8d6fafd
	.long .Lname496 /* index: 496 */
	.weak regdump_gpregs_with_sp; .long regdump_gpregs_with_sp
	.reloc ., R_386_SIZE32, regdump_gpregs_with_sp; .long 0
	.long 0x242e1f0
	.long 0 /* index: 497 */
	.long 0
	.long 0
	.long 0
	.long .Lname498 /* index: 498 */
	.weak sys_setuid32; .long sys_setuid32
	.reloc ., R_386_SIZE32, sys_setuid32; .long 0
	.long 0xb0b61f2
	.long 0 /* index: 499 */
	.long 0
	.long 0
	.long 0
	.long .Lname500 /* index: 500 */
	.weak dbg_editfield; .long dbg_editfield
	.reloc ., R_386_SIZE32, dbg_editfield; .long 0
	.long 0xa21a1f4
	.long .Lname501 /* index: 501 */
	.weak mempmove; .long mempmove
	.reloc ., R_386_SIZE32, mempmove; .long 0
	.long 0xc4741f5
	.long 0 /* index: 502 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 503 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 504 */
	.long 0
	.long 0
	.long 0
	.long .Lname505 /* index: 505 */
	.weak sys_mknod; .long sys_mknod
	.reloc ., R_386_SIZE32, sys_mknod; .long 0
	.long 0x9648054
	.long .Lname506 /* index: 506 */
	.weak inode_readallv_phys; .long inode_readallv_phys
	.reloc ., R_386_SIZE32, inode_readallv_phys; .long 0
	.long 0xb646343
	.long 0 /* index: 507 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 508 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 509 */
	.long 0
	.long 0
	.long 0
	.long .Lname510 /* index: 510 */
	.weak unicode_readutf16_swap_n; .long unicode_readutf16_swap_n
	.reloc ., R_386_SIZE32, unicode_readutf16_swap_n; .long 0
	.long 0x1561fe
	.long .Lname511 /* index: 511 */
	.weak ramfs_type; .long ramfs_type
	.reloc ., R_386_SIZE32, ramfs_type; .long 0
	.long 0xd914855
	.long 0 /* index: 512 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 513 */
	.long 0
	.long 0
	.long 0
	.long .Lname514 /* index: 514 */
	.weak sys_chdir; .long sys_chdir
	.reloc ., R_386_SIZE32, sys_chdir; .long 0
	.long 0x9599202
	.long 0 /* index: 515 */
	.long 0
	.long 0
	.long 0
	.long .Lname516 /* index: 516 */
	.weak regdump_idt; .long regdump_idt
	.reloc ., R_386_SIZE32, regdump_idt; .long 0
	.long 0xc3ee204
	.long .Lname517 /* index: 517 */
	.weak acpi_mode; .long acpi_mode
	.reloc ., R_386_SIZE32, acpi_mode; .long 0
	.long 0x6f66205
	.long .Lname518 /* index: 518 */
	.weak vm_datablock_vio_writev; .long vm_datablock_vio_writev
	.reloc ., R_386_SIZE32, vm_datablock_vio_writev; .long 0
	.long 0x4050206
	.long .Lname519 /* index: 519 */
	.weak sys_sendmmsg; .long sys_sendmmsg
	.reloc ., R_386_SIZE32, sys_sendmmsg; .long 0
	.long 0xdfbb207
	.long 0 /* index: 520 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 521 */
	.long 0
	.long 0
	.long 0
	.long .Lname522 /* index: 522 */
	.weak unicode_readutf16_n; .long unicode_readutf16_n
	.reloc ., R_386_SIZE32, unicode_readutf16_n; .long 0
	.long 0xb8e5a3e
	.long .Lname523 /* index: 523 */
	.weak inode_readk; .long inode_readk
	.reloc ., R_386_SIZE32, inode_readk; .long 0
	.long 0xb18e20b
	.long .Lname524 /* index: 524 */
	.weak disasm_print_until; .long disasm_print_until
	.reloc ., R_386_SIZE32, disasm_print_until; .long 0
	.long 0xdbd420c
	.long 0 /* index: 525 */
	.long 0
	.long 0
	.long 0
	.long .Lname526 /* index: 526 */
	.weak cpu_idlemain; .long cpu_idlemain
	.reloc ., R_386_SIZE32, cpu_idlemain; .long 0
	.long 0xd8d820e
	.long 0 /* index: 527 */
	.long 0
	.long 0
	.long 0
	.long .Lname528 /* index: 528 */
	.weak vm_datablock_writevp; .long vm_datablock_writevp
	.reloc ., R_386_SIZE32, vm_datablock_writevp; .long 0
	.long 0x21f8210
	.long 0 /* index: 529 */
	.long 0
	.long 0
	.long 0
	.long .Lname530 /* index: 530 */
	.weak dbg_getcur; .long dbg_getcur
	.reloc ., R_386_SIZE32, dbg_getcur; .long 0
	.long 0x5da0212
	.long .Lname531 /* index: 531 */
	.weak inode_writev_phys; .long inode_writev_phys
	.reloc ., R_386_SIZE32, inode_writev_phys; .long 0
	.long 0x7b88b03
	.long .Lname532 /* index: 532 */
	.weak unwind_fde_exec_landing_pad_adjustment; .long unwind_fde_exec_landing_pad_adjustment
	.reloc ., R_386_SIZE32, unwind_fde_exec_landing_pad_adjustment; .long 0
	.long 0x3144214
	.long .Lname533 /* index: 533 */
	.weak cpu_apply_lcpustate; .long cpu_apply_lcpustate
	.reloc ., R_386_SIZE32, cpu_apply_lcpustate; .long 0
	.long 0xa8cb215
	.long .Lname534 /* index: 534 */
	.weak inode_readv; .long inode_readv
	.reloc ., R_386_SIZE32, inode_readv; .long 0
	.long 0xb18e216
	.long .Lname535 /* index: 535 */
	.weak sys_recvmmsg; .long sys_recvmmsg
	.reloc ., R_386_SIZE32, sys_recvmmsg; .long 0
	.long 0xc1db217
	.long .Lname536 /* index: 536 */
	.weak vm_datapart_lock_read_nx; .long vm_datapart_lock_read_nx
	.reloc ., R_386_SIZE32, vm_datapart_lock_read_nx; .long 0
	.long 0x137d218
	.long 0 /* index: 537 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 538 */
	.long 0
	.long 0
	.long 0
	.long .Lname539 /* index: 539 */
	.weak __cpuset_full_mask; .long __cpuset_full_mask
	.reloc ., R_386_SIZE32, __cpuset_full_mask; .long 0
	.long 0xe99c21b
	.long 0 /* index: 540 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 541 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 542 */
	.long 0
	.long 0
	.long 0
	.long .Lname543 /* index: 543 */
	.weak task_sleep_cputime; .long task_sleep_cputime
	.reloc ., R_386_SIZE32, task_sleep_cputime; .long 0
	.long 0x5ffcb05
	.long 0 /* index: 544 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 545 */
	.long 0
	.long 0
	.long 0
	.long .Lname546 /* index: 546 */
	.weak sys_linux_lstat32; .long sys_linux_lstat32
	.reloc ., R_386_SIZE32, sys_linux_lstat32; .long 0
	.long 0x1344222
	.long .Lname547 /* index: 547 */
	.weak inode_readv_phys; .long inode_readv_phys
	.reloc ., R_386_SIZE32, inode_readv_phys; .long 0
	.long 0x117e223
	.long .Lname548 /* index: 548 */
	.weak kernel_debugtraps_get; .long kernel_debugtraps_get
	.reloc ., R_386_SIZE32, kernel_debugtraps_get; .long 0
	.long 0xab0c224
	.long .Lname549 /* index: 549 */
	.weak debuginfo_location_setvalue; .long debuginfo_location_setvalue
	.reloc ., R_386_SIZE32, debuginfo_location_setvalue; .long 0
	.long 0xabab225
	.long 0 /* index: 550 */
	.long 0
	.long 0
	.long 0
	.long .Lname551 /* index: 551 */
	.weak cpu_assert_sleeping; .long cpu_assert_sleeping
	.reloc ., R_386_SIZE32, cpu_assert_sleeping; .long 0
	.long 0x10eb227
	.long .Lname552 /* index: 552 */
	.weak vm_datapart_lock_write_nx; .long vm_datapart_lock_write_nx
	.reloc ., R_386_SIZE32, vm_datapart_lock_write_nx; .long 0
	.long 0x10ff228
	.long .Lname553 /* index: 553 */
	.weak stack_avail; .long stack_avail
	.reloc ., R_386_SIZE32, stack_avail; .long 0
	.long 0x122605c
	.long .Lname554 /* index: 554 */
	.weak cpu_add_quantum_offset; .long cpu_add_quantum_offset
	.reloc ., R_386_SIZE32, cpu_add_quantum_offset; .long 0
	.long 0xc4522e4
	.long 0 /* index: 555 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 556 */
	.long 0
	.long 0
	.long 0
	.long .Lname557 /* index: 557 */
	.weak __asm32_exsyscallrouter_sysenter; .long __asm32_exsyscallrouter_sysenter
	.reloc ., R_386_SIZE32, __asm32_exsyscallrouter_sysenter; .long 0
	.long 0x57f55b2
	.long 0 /* index: 558 */
	.long 0
	.long 0
	.long 0
	.long .Lname559 /* index: 559 */
	.weak vm_kernel_treelock_tryread; .long vm_kernel_treelock_tryread
	.reloc ., R_386_SIZE32, vm_kernel_treelock_tryread; .long 0
	.long 0x8338234
	.long 0 /* index: 560 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 561 */
	.long 0
	.long 0
	.long 0
	.long .Lname562 /* index: 562 */
	.weak vm_exec_assert_regular; .long vm_exec_assert_regular
	.reloc ., R_386_SIZE32, vm_exec_assert_regular; .long 0
	.long 0xecfc232
	.long 0 /* index: 563 */
	.long 0
	.long 0
	.long 0
	.long .Lname564 /* index: 564 */
	.weak cpu_quantum_elapsed; .long cpu_quantum_elapsed
	.reloc ., R_386_SIZE32, cpu_quantum_elapsed; .long 0
	.long 0x6089234
	.long .Lname565 /* index: 565 */
	.weak driver_getfilename; .long driver_getfilename
	.reloc ., R_386_SIZE32, driver_getfilename; .long 0
	.long 0xed08235
	.long .Lname566 /* index: 566 */
	.weak block_device_readv; .long block_device_readv
	.reloc ., R_386_SIZE32, block_device_readv; .long 0
	.long 0xa572236
	.long 0 /* index: 567 */
	.long 0
	.long 0
	.long 0
	.long .Lname568 /* index: 568 */
	.weak callback_list_remove; .long callback_list_remove
	.reloc ., R_386_SIZE32, callback_list_remove; .long 0
	.long 0xffbcd55
	.long .Lname569 /* index: 569 */
	.weak handle_get_taskpid; .long handle_get_taskpid
	.reloc ., R_386_SIZE32, handle_get_taskpid; .long 0
	.long 0x73da5b4
	.long 0 /* index: 570 */
	.long 0
	.long 0
	.long 0
	.long .Lname571 /* index: 571 */
	.weak aio_multihandle_cancel; .long aio_multihandle_cancel
	.reloc ., R_386_SIZE32, aio_multihandle_cancel; .long 0
	.long 0xdde61ac
	.long .Lname572 /* index: 572 */
	.weak ttybase_device_poll; .long ttybase_device_poll
	.reloc ., R_386_SIZE32, ttybase_device_poll; .long 0
	.long 0xb53323c
	.long 0 /* index: 573 */
	.long 0
	.long 0
	.long 0
	.long .Lname574 /* index: 574 */
	.weak blocking_cleanup_chain; .long blocking_cleanup_chain
	.reloc ., R_386_SIZE32, blocking_cleanup_chain; .long 0
	.long 0x268423e
	.long .Lname575 /* index: 575 */
	.weak kmalloc_usable_size; .long kmalloc_usable_size
	.reloc ., R_386_SIZE32, kmalloc_usable_size; .long 0
	.long 0xa0245b5
	.long .Lname576 /* index: 576 */
	.weak sys_debugtrap; .long sys_debugtrap
	.reloc ., R_386_SIZE32, sys_debugtrap; .long 0
	.long 0x2b7e240
	.long .Lname577 /* index: 577 */
	.weak vm_copyinphys; .long vm_copyinphys
	.reloc ., R_386_SIZE32, vm_copyinphys; .long 0
	.long 0x2d0ca03
	.long .Lname578 /* index: 578 */
	.weak format_sprintf_printer; .long format_sprintf_printer
	.reloc ., R_386_SIZE32, format_sprintf_printer; .long 0
	.long 0xcfb4242
	.long 0 /* index: 579 */
	.long 0
	.long 0
	.long 0
	.long .Lname580 /* index: 580 */
	.weak sys_setresuid; .long sys_setresuid
	.reloc ., R_386_SIZE32, sys_setresuid; .long 0
	.long 0x85c244
	.long .Lname581 /* index: 581 */
	.weak ramfs_dev_type; .long ramfs_dev_type
	.reloc ., R_386_SIZE32, ramfs_dev_type; .long 0
	.long 0x49b3245
	.long .Lname582 /* index: 582 */
	.weak _ZSt9terminatev; .long _ZSt9terminatev
	.reloc ., R_386_SIZE32, _ZSt9terminatev; .long 0
	.long 0x9844246
	.long .Lname583 /* index: 583 */
	.weak validate_executable; .long validate_executable
	.reloc ., R_386_SIZE32, validate_executable; .long 0
	.long 0xcfd4d65
	.long .Lname584 /* index: 584 */
	.weak kernel_debugtrap_on; .long kernel_debugtrap_on
	.reloc ., R_386_SIZE32, kernel_debugtrap_on; .long 0
	.long 0xfea93ce
	.long .Lname585 /* index: 585 */
	.weak pidns_destroy; .long pidns_destroy
	.reloc ., R_386_SIZE32, pidns_destroy; .long 0
	.long 0xc31e249
	.long 0 /* index: 586 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 587 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 588 */
	.long 0
	.long 0
	.long 0
	.long .Lname589 /* index: 589 */
	.weak x86_memcpy_nopf; .long x86_memcpy_nopf
	.reloc ., R_386_SIZE32, x86_memcpy_nopf; .long 0
	.long 0xb97ae76
	.long 0 /* index: 590 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 591 */
	.long 0
	.long 0
	.long 0
	.long .Lname592 /* index: 592 */
	.weak _this_x86_dr0; .long _this_x86_dr0
	.reloc ., R_386_SIZE32, _this_x86_dr0; .long 0
	.long 0xd155250
	.long .Lname593 /* index: 593 */
	.weak fpustate_alloc_nx; .long fpustate_alloc_nx
	.reloc ., R_386_SIZE32, fpustate_alloc_nx; .long 0
	.long 0x9d27db8
	.long .Lname594 /* index: 594 */
	.weak _this_x86_dr2; .long _this_x86_dr2
	.reloc ., R_386_SIZE32, _this_x86_dr2; .long 0
	.long 0xd155252
	.long .Lname595 /* index: 595 */
	.weak inode_write_phys; .long inode_write_phys
	.reloc ., R_386_SIZE32, inode_write_phys; .long 0
	.long 0x278253
	.long .Lname596 /* index: 596 */
	.weak pidns_endread; .long pidns_endread
	.reloc ., R_386_SIZE32, pidns_endread; .long 0
	.long 0xeb0d254
	.long .Lname597 /* index: 597 */
	.weak sys_olduname; .long sys_olduname
	.reloc ., R_386_SIZE32, sys_olduname; .long 0
	.long 0x50cd255
	.long .Lname598 /* index: 598 */
	.weak sys_clock_settime64; .long sys_clock_settime64
	.reloc ., R_386_SIZE32, sys_clock_settime64; .long 0
	.long 0x5060b34
	.long .Lname599 /* index: 599 */
	.weak _this_x86_dr7; .long _this_x86_dr7
	.reloc ., R_386_SIZE32, _this_x86_dr7; .long 0
	.long 0xd155257
	.long 0 /* index: 600 */
	.long 0
	.long 0
	.long 0
	.long .Lname601 /* index: 601 */
	.weak json_parser_rewind; .long json_parser_rewind
	.reloc ., R_386_SIZE32, json_parser_rewind; .long 0
	.long 0x71f2864
	.long 0 /* index: 602 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 603 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 604 */
	.long 0
	.long 0
	.long 0
	.long .Lname605 /* index: 605 */
	.weak vm_node_update_write_access_locked_vm; .long vm_node_update_write_access_locked_vm
	.reloc ., R_386_SIZE32, vm_node_update_write_access_locked_vm; .long 0
	.long 0xd08a25d
	.long .Lname606 /* index: 606 */
	.weak task_alloc; .long task_alloc
	.reloc ., R_386_SIZE32, task_alloc; .long 0
	.long 0x1519bf3
	.long .Lname607 /* index: 607 */
	.weak memlen; .long memlen
	.reloc ., R_386_SIZE32, memlen; .long 0
	.long 0x73c42be
	.long 0 /* index: 608 */
	.long 0
	.long 0
	.long 0
	.long .Lname609 /* index: 609 */
	.weak sys_mremap; .long sys_mremap
	.reloc ., R_386_SIZE32, sys_mremap; .long 0
	.long 0x64f1310
	.long .Lname610 /* index: 610 */
	.weak cpu_schedule_idle_job; .long cpu_schedule_idle_job
	.reloc ., R_386_SIZE32, cpu_schedule_idle_job; .long 0
	.long 0xbc24262
	.long .Lname611 /* index: 611 */
	.weak sys_clock_getres; .long sys_clock_getres
	.reloc ., R_386_SIZE32, sys_clock_getres; .long 0
	.long 0x7a5263
	.long .Lname612 /* index: 612 */
	.weak pidns_tryread; .long pidns_tryread
	.reloc ., R_386_SIZE32, pidns_tryread; .long 0
	.long 0xd7bd264
	.long .Lname613 /* index: 613 */
	.weak page_mallocone; .long page_mallocone
	.reloc ., R_386_SIZE32, page_mallocone; .long 0
	.long 0x70f0265
	.long .Lname614 /* index: 614 */
	.weak block_device_writev; .long block_device_writev
	.reloc ., R_386_SIZE32, block_device_writev; .long 0
	.long 0x5125266
	.long .Lname615 /* index: 615 */
	.weak sys_utime; .long sys_utime
	.reloc ., R_386_SIZE32, sys_utime; .long 0
	.long 0x96cd535
	.long 0 /* index: 616 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 617 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 618 */
	.long 0
	.long 0
	.long 0
	.long .Lname619 /* index: 619 */
	.weak _this_task; .long _this_task
	.reloc ., R_386_SIZE32, _this_task; .long 0
	.long 0x90c26b
	.long .Lname620 /* index: 620 */
	.weak sys_mlockall; .long sys_mlockall
	.reloc ., R_386_SIZE32, sys_mlockall; .long 0
	.long 0x6ea826c
	.long 0 /* index: 621 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 622 */
	.long 0
	.long 0
	.long 0
	.long .Lname623 /* index: 623 */
	.weak validate_writable_opt; .long validate_writable_opt
	.reloc ., R_386_SIZE32, validate_writable_opt; .long 0
	.long 0xd3aba34
	.long 0 /* index: 624 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 625 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 626 */
	.long 0
	.long 0
	.long 0
	.long .Lname627 /* index: 627 */
	.weak cpu_enable_preemptive_interrupts; .long cpu_enable_preemptive_interrupts
	.reloc ., R_386_SIZE32, cpu_enable_preemptive_interrupts; .long 0
	.long 0xb08e273
	.long .Lname628 /* index: 628 */
	.weak cpu_run_current; .long cpu_run_current
	.reloc ., R_386_SIZE32, cpu_run_current; .long 0
	.long 0x1a06274
	.long .Lname629 /* index: 629 */
	.weak vm_datablock_anonymous_zero_type; .long vm_datablock_anonymous_zero_type
	.reloc ., R_386_SIZE32, vm_datablock_anonymous_zero_type; .long 0
	.long 0x362a275
	.long .Lname630 /* index: 630 */
	.weak sys_kreaddirf; .long sys_kreaddirf
	.reloc ., R_386_SIZE32, sys_kreaddirf; .long 0
	.long 0x73d276
	.long 0 /* index: 631 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 632 */
	.long 0
	.long 0
	.long 0
	.long .Lname633 /* index: 633 */
	.weak debuginfo_cu_parser_next; .long debuginfo_cu_parser_next
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_next; .long 0
	.long 0xe0c2b14
	.long .Lname634 /* index: 634 */
	.weak dbg_putuni; .long dbg_putuni
	.reloc ., R_386_SIZE32, dbg_putuni; .long 0
	.long 0x67a1499
	.long 0 /* index: 635 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 636 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 637 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 638 */
	.long 0
	.long 0
	.long 0
	.long .Lname639 /* index: 639 */
	.weak _this_fpustate; .long _this_fpustate
	.reloc ., R_386_SIZE32, _this_fpustate; .long 0
	.long 0xd3a3b15
	.long .Lname640 /* index: 640 */
	.weak driver_symbol_at; .long driver_symbol_at
	.reloc ., R_386_SIZE32, driver_symbol_at; .long 0
	.long 0xf58d184
	.long 0 /* index: 641 */
	.long 0
	.long 0
	.long 0
	.long .Lname642 /* index: 642 */
	.weak sys_renameat; .long sys_renameat
	.reloc ., R_386_SIZE32, sys_renameat; .long 0
	.long 0xdf8ad04
	.long .Lname643 /* index: 643 */
	.weak debuginfo_enum_locals; .long debuginfo_enum_locals
	.reloc ., R_386_SIZE32, debuginfo_enum_locals; .long 0
	.long 0xcd26283
	.long .Lname644 /* index: 644 */
	.weak format_repeat; .long format_repeat
	.reloc ., R_386_SIZE32, format_repeat; .long 0
	.long 0xbe55284
	.long 0 /* index: 645 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 646 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 647 */
	.long 0
	.long 0
	.long 0
	.long .Lname648 /* index: 648 */
	.weak vm_kernel_treelock_write_nx; .long vm_kernel_treelock_write_nx
	.reloc ., R_386_SIZE32, vm_kernel_treelock_write_nx; .long 0
	.long 0x43a4288
	.long 0 /* index: 649 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 650 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 651 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 652 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 653 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 654 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 655 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 656 */
	.long 0
	.long 0
	.long 0
	.long .Lname657 /* index: 657 */
	.weak slab_kmalloc8; .long slab_kmalloc8
	.reloc ., R_386_SIZE32, slab_kmalloc8; .long 0
	.long 0x966b318
	.long 0 /* index: 658 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 659 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 660 */
	.long 0
	.long 0
	.long 0
	.long .Lname661 /* index: 661 */
	.weak fs_filesystems_lock_upgrade; .long fs_filesystems_lock_upgrade
	.reloc ., R_386_SIZE32, fs_filesystems_lock_upgrade; .long 0
	.long 0xd002115
	.long 0 /* index: 662 */
	.long 0
	.long 0
	.long 0
	.long .Lname663 /* index: 663 */
	.weak dbg_asmview; .long dbg_asmview
	.reloc ., R_386_SIZE32, dbg_asmview; .long 0
	.long 0x90e4297
	.long 0 /* index: 664 */
	.long 0
	.long 0
	.long 0
	.long .Lname665 /* index: 665 */
	.weak isr_vector_state_destroy; .long isr_vector_state_destroy
	.reloc ., R_386_SIZE32, isr_vector_state_destroy; .long 0
	.long 0xcc3f299
	.long .Lname666 /* index: 666 */
	.weak path_lock_tryupgrade; .long path_lock_tryupgrade
	.reloc ., R_386_SIZE32, path_lock_tryupgrade; .long 0
	.long 0xed66795
	.long 0 /* index: 667 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 668 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 669 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 670 */
	.long 0
	.long 0
	.long 0
	.long .Lname671 /* index: 671 */
	.weak path_getchild_and_parent_inode; .long path_getchild_and_parent_inode
	.reloc ., R_386_SIZE32, path_getchild_and_parent_inode; .long 0
	.long 0x871b5c5
	.long .Lname672 /* index: 672 */
	.weak x86_fpustate_save; .long x86_fpustate_save
	.reloc ., R_386_SIZE32, x86_fpustate_save; .long 0
	.long 0x7b18e15
	.long 0 /* index: 673 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 674 */
	.long 0
	.long 0
	.long 0
	.long .Lname675 /* index: 675 */
	.weak vm_datapart_readv_phys; .long vm_datapart_readv_phys
	.reloc ., R_386_SIZE32, vm_datapart_readv_phys; .long 0
	.long 0x8adb2a3
	.long .Lname676 /* index: 676 */
	.weak validate_writablem_opt; .long validate_writablem_opt
	.reloc ., R_386_SIZE32, validate_writablem_opt; .long 0
	.long 0x39ea2a4
	.long .Lname677 /* index: 677 */
	.weak directory_getcasenode; .long directory_getcasenode
	.reloc ., R_386_SIZE32, directory_getcasenode; .long 0
	.long 0xf7d62a5
	.long .Lname678 /* index: 678 */
	.weak sys_preadvf; .long sys_preadvf
	.reloc ., R_386_SIZE32, sys_preadvf; .long 0
	.long 0x7f072a6
	.long .Lname679 /* index: 679 */
	.weak krealign_nx; .long krealign_nx
	.reloc ., R_386_SIZE32, krealign_nx; .long 0
	.long 0x290cfd8
	.long 0 /* index: 680 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 681 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 682 */
	.long 0
	.long 0
	.long 0
	.long .Lname683 /* index: 683 */
	.weak handle_get_superblock; .long handle_get_superblock
	.reloc ., R_386_SIZE32, handle_get_superblock; .long 0
	.long 0x4bd62ab
	.long 0 /* index: 684 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 685 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 686 */
	.long 0
	.long 0
	.long 0
	.long .Lname687 /* index: 687 */
	.weak vm_onexec_callbacks; .long vm_onexec_callbacks
	.reloc ., R_386_SIZE32, vm_onexec_callbacks; .long 0
	.long 0x2a745f3
	.long .Lname688 /* index: 688 */
	.weak pagedir_unprepare_mapone_p; .long pagedir_unprepare_mapone_p
	.reloc ., R_386_SIZE32, pagedir_unprepare_mapone_p; .long 0
	.long 0xfa432b0
	.long 0 /* index: 689 */
	.long 0
	.long 0
	.long 0
	.long .Lname690 /* index: 690 */
	.weak sys_getgid32; .long sys_getgid32
	.reloc ., R_386_SIZE32, sys_getgid32; .long 0
	.long 0xb1d62b2
	.long .Lname691 /* index: 691 */
	.weak driver_finalized_callbacks; .long driver_finalized_callbacks
	.reloc ., R_386_SIZE32, driver_finalized_callbacks; .long 0
	.long 0x59ae2b3
	.long .Lname692 /* index: 692 */
	.weak path_recent; .long path_recent
	.reloc ., R_386_SIZE32, path_recent; .long 0
	.long 0x6fd12b4
	.long .Lname693 /* index: 693 */
	.weak pagedir_unwrite; .long pagedir_unwrite
	.reloc ., R_386_SIZE32, pagedir_unwrite; .long 0
	.long 0x7e602b5
	.long 0 /* index: 694 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 695 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 696 */
	.long 0
	.long 0
	.long 0
	.long .Lname697 /* index: 697 */
	.weak driver_insmod; .long driver_insmod
	.reloc ., R_386_SIZE32, driver_insmod; .long 0
	.long 0xe757074
	.long 0 /* index: 698 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 699 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 700 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 701 */
	.long 0
	.long 0
	.long 0
	.long .Lname702 /* index: 702 */
	.weak strlen; .long strlen
	.reloc ., R_386_SIZE32, strlen; .long 0
	.long 0x7ab92be
	.long 0 /* index: 703 */
	.long 0
	.long 0
	.long 0
	.long .Lname704 /* index: 704 */
	.weak __gxx_personality_v0; .long __gxx_personality_v0
	.reloc ., R_386_SIZE32, __gxx_personality_v0; .long 0
	.long 0xc7c32c0
	.long 0 /* index: 705 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 706 */
	.long 0
	.long 0
	.long 0
	.long .Lname707 /* index: 707 */
	.weak task_deliver_rpc; .long task_deliver_rpc
	.reloc ., R_386_SIZE32, task_deliver_rpc; .long 0
	.long 0xd9b42c3
	.long 0 /* index: 708 */
	.long 0
	.long 0
	.long 0
	.long .Lname709 /* index: 709 */
	.weak isr_unregister_any; .long isr_unregister_any
	.reloc ., R_386_SIZE32, isr_unregister_any; .long 0
	.long 0x8473239
	.long 0 /* index: 710 */
	.long 0
	.long 0
	.long 0
	.long .Lname711 /* index: 711 */
	.weak debuginfo_cu_parser_getflag; .long debuginfo_cu_parser_getflag
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getflag; .long 0
	.long 0xbb432c7
	.long .Lname712 /* index: 712 */
	.weak vm_startdmav_nx; .long vm_startdmav_nx
	.reloc ., R_386_SIZE32, vm_startdmav_nx; .long 0
	.long 0xd9252c8
	.long 0 /* index: 713 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 714 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 715 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 716 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 717 */
	.long 0
	.long 0
	.long 0
	.long .Lname718 /* index: 718 */
	.weak memrlen; .long memrlen
	.reloc ., R_386_SIZE32, memrlen; .long 0
	.long 0x3c492ce
	.long 0 /* index: 719 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 720 */
	.long 0
	.long 0
	.long 0
	.long .Lname721 /* index: 721 */
	.weak slab_kmalloc_nx12; .long slab_kmalloc_nx12
	.reloc ., R_386_SIZE32, slab_kmalloc_nx12; .long 0
	.long 0x40d3df2
	.long .Lname722 /* index: 722 */
	.weak sys_removexattr; .long sys_removexattr
	.reloc ., R_386_SIZE32, sys_removexattr; .long 0
	.long 0x5a652d2
	.long .Lname723 /* index: 723 */
	.weak inode_areadv_phys; .long inode_areadv_phys
	.reloc ., R_386_SIZE32, inode_areadv_phys; .long 0
	.long 0xaeb2d3
	.long .Lname724 /* index: 724 */
	.weak vm_sync_locked; .long vm_sync_locked
	.reloc ., R_386_SIZE32, vm_sync_locked; .long 0
	.long 0x75ea2d4
	.long 0 /* index: 725 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 726 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 727 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 728 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 729 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 730 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 731 */
	.long 0
	.long 0
	.long 0
	.long .Lname732 /* index: 732 */
	.weak __predict_update_al; .long __predict_update_al
	.reloc ., R_386_SIZE32, __predict_update_al; .long 0
	.long 0x4552dc
	.long 0 /* index: 733 */
	.long 0
	.long 0
	.long 0
	.long .Lname734 /* index: 734 */
	.weak directory_entry_alloc_s; .long directory_entry_alloc_s
	.reloc ., R_386_SIZE32, directory_entry_alloc_s; .long 0
	.long 0x6b553d3
	.long 0 /* index: 735 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 736 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 737 */
	.long 0
	.long 0
	.long 0
	.long .Lname738 /* index: 738 */
	.weak format_snprintf_printer; .long format_snprintf_printer
	.reloc ., R_386_SIZE32, format_snprintf_printer; .long 0
	.long 0x587f2e2
	.long .Lname739 /* index: 739 */
	.weak vfs_clearmounts; .long vfs_clearmounts
	.reloc ., R_386_SIZE32, vfs_clearmounts; .long 0
	.long 0x27cf2e3
	.long .Lname740 /* index: 740 */
	.weak strto64; .long strto64
	.reloc ., R_386_SIZE32, strto64; .long 0
	.long 0xab9b2e4
	.long .Lname741 /* index: 741 */
	.weak sys_timerfd_create; .long sys_timerfd_create
	.reloc ., R_386_SIZE32, sys_timerfd_create; .long 0
	.long 0xc24a2e5
	.long .Lname742 /* index: 742 */
	.weak keymap_translate_buf; .long keymap_translate_buf
	.reloc ., R_386_SIZE32, keymap_translate_buf; .long 0
	.long 0xe3082e6
	.long .Lname743 /* index: 743 */
	.weak inode_read_blocking; .long inode_read_blocking
	.reloc ., R_386_SIZE32, inode_read_blocking; .long 0
	.long 0xbbc52e7
	.long .Lname744 /* index: 744 */
	.weak strto32; .long strto32
	.reloc ., R_386_SIZE32, strto32; .long 0
	.long 0xab9b212
	.long .Lname745 /* index: 745 */
	.weak driver_state_destroy; .long driver_state_destroy
	.reloc ., R_386_SIZE32, driver_state_destroy; .long 0
	.long 0x96ed2e9
	.long 0 /* index: 746 */
	.long 0
	.long 0
	.long 0
	.long .Lname747 /* index: 747 */
	.weak sys__llseek; .long sys__llseek
	.reloc ., R_386_SIZE32, sys__llseek; .long 0
	.long 0x66892eb
	.long .Lname748 /* index: 748 */
	.weak dbg_enter_icpustate; .long dbg_enter_icpustate
	.reloc ., R_386_SIZE32, dbg_enter_icpustate; .long 0
	.long 0x781ab35
	.long 0 /* index: 749 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 750 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 751 */
	.long 0
	.long 0
	.long 0
	.long .Lname752 /* index: 752 */
	.weak pagedir_unsetchanged_p; .long pagedir_unsetchanged_p
	.reloc ., R_386_SIZE32, pagedir_unsetchanged_p; .long 0
	.long 0xa6632f0
	.long .Lname753 /* index: 753 */
	.weak devfs_lock_upgrade_nx; .long devfs_lock_upgrade_nx
	.reloc ., R_386_SIZE32, devfs_lock_upgrade_nx; .long 0
	.long 0xe953b28
	.long 0 /* index: 754 */
	.long 0
	.long 0
	.long 0
	.long .Lname755 /* index: 755 */
	.weak debug_dllocksections; .long debug_dllocksections
	.reloc ., R_386_SIZE32, debug_dllocksections; .long 0
	.long 0x164b5d3
	.long .Lname756 /* index: 756 */
	.weak sys_connect; .long sys_connect
	.reloc ., R_386_SIZE32, sys_connect; .long 0
	.long 0xa4042f4
	.long .Lname757 /* index: 757 */
	.weak symtab_scantable; .long symtab_scantable
	.reloc ., R_386_SIZE32, symtab_scantable; .long 0
	.long 0xe2ba2f5
	.long .Lname758 /* index: 758 */
	.weak memset_nopf; .long memset_nopf
	.reloc ., R_386_SIZE32, memset_nopf; .long 0
	.long 0xcf792f6
	.long .Lname759 /* index: 759 */
	.weak keyboard_buffer_getkey; .long keyboard_buffer_getkey
	.reloc ., R_386_SIZE32, keyboard_buffer_getkey; .long 0
	.long 0x5400b29
	.long 0 /* index: 760 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 761 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 762 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 763 */
	.long 0
	.long 0
	.long 0
	.long .Lname764 /* index: 764 */
	.weak x86_lapic_id; .long x86_lapic_id
	.reloc ., R_386_SIZE32, x86_lapic_id; .long 0
	.long 0xfd453d4
	.long 0 /* index: 765 */
	.long 0
	.long 0
	.long 0
	.long .Lname766 /* index: 766 */
	.weak path_lock_write; .long path_lock_write
	.reloc ., R_386_SIZE32, path_lock_write; .long 0
	.long 0xb88f385
	.long 0 /* index: 767 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 768 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 769 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 770 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 771 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 772 */
	.long 0
	.long 0
	.long 0
	.long .Lname773 /* index: 773 */
	.weak x86_fxsave; .long x86_fxsave
	.reloc ., R_386_SIZE32, x86_fxsave; .long 0
	.long 0x5d82305
	.long 0 /* index: 774 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 775 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 776 */
	.long 0
	.long 0
	.long 0
	.long .Lname777 /* index: 777 */
	.weak block_device_destroy; .long block_device_destroy
	.reloc ., R_386_SIZE32, block_device_destroy; .long 0
	.long 0x55f3309
	.long 0 /* index: 778 */
	.long 0
	.long 0
	.long 0
	.long .Lname779 /* index: 779 */
	.weak x86_this_dfstack; .long x86_this_dfstack
	.reloc ., R_386_SIZE32, x86_this_dfstack; .long 0
	.long 0xc70130b
	.long .Lname780 /* index: 780 */
	.weak task_disconnectall; .long task_disconnectall
	.reloc ., R_386_SIZE32, task_disconnectall; .long 0
	.long 0xa1be30c
	.long 0 /* index: 781 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 782 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 783 */
	.long 0
	.long 0
	.long 0
	.long .Lname784 /* index: 784 */
	.weak sys_munmap; .long sys_munmap
	.reloc ., R_386_SIZE32, sys_munmap; .long 0
	.long 0x64e0310
	.long 0 /* index: 785 */
	.long 0
	.long 0
	.long 0
	.long .Lname786 /* index: 786 */
	.weak sigmask_getwr; .long sigmask_getwr
	.reloc ., R_386_SIZE32, sigmask_getwr; .long 0
	.long 0xaa3f312
	.long 0 /* index: 787 */
	.long 0
	.long 0
	.long 0
	.long .Lname788 /* index: 788 */
	.weak instruction_trypred; .long instruction_trypred
	.reloc ., R_386_SIZE32, instruction_trypred; .long 0
	.long 0x1768314
	.long .Lname789 /* index: 789 */
	.weak fs_filesystems_remove; .long fs_filesystems_remove
	.reloc ., R_386_SIZE32, fs_filesystems_remove; .long 0
	.long 0x3f14315
	.long 0 /* index: 790 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 791 */
	.long 0
	.long 0
	.long 0
	.long .Lname792 /* index: 792 */
	.weak dbg_menuex; .long dbg_menuex
	.reloc ., R_386_SIZE32, dbg_menuex; .long 0
	.long 0x63ef318
	.long .Lname793 /* index: 793 */
	.weak vm_set_aslr_disabled; .long vm_set_aslr_disabled
	.reloc ., R_386_SIZE32, vm_set_aslr_disabled; .long 0
	.long 0xc9d5884
	.long 0 /* index: 794 */
	.long 0
	.long 0
	.long 0
	.long .Lname795 /* index: 795 */
	.weak path_lock; .long path_lock
	.reloc ., R_386_SIZE32, path_lock; .long 0
	.long 0xae6631b
	.long 0 /* index: 796 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 797 */
	.long 0
	.long 0
	.long 0
	.long .Lname798 /* index: 798 */
	.weak page_malloc_part_between; .long page_malloc_part_between
	.reloc ., R_386_SIZE32, page_malloc_part_between; .long 0
	.long 0xa84431e
	.long 0 /* index: 799 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 800 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 801 */
	.long 0
	.long 0
	.long 0
	.long .Lname802 /* index: 802 */
	.weak path_clear; .long path_clear
	.reloc ., R_386_SIZE32, path_clear; .long 0
	.long 0xe5f4322
	.long .Lname803 /* index: 803 */
	.weak kmalloc; .long kmalloc
	.reloc ., R_386_SIZE32, kmalloc; .long 0
	.long 0x2383323
	.long .Lname804 /* index: 804 */
	.weak cmdline_split; .long cmdline_split
	.reloc ., R_386_SIZE32, cmdline_split; .long 0
	.long 0x1516324
	.long .Lname805 /* index: 805 */
	.weak debug_print_filename; .long debug_print_filename
	.reloc ., R_386_SIZE32, debug_print_filename; .long 0
	.long 0xd561325
	.long .Lname806 /* index: 806 */
	.weak error_printf; .long error_printf
	.reloc ., R_386_SIZE32, error_printf; .long 0
	.long 0xb17326
	.long .Lname807 /* index: 807 */
	.weak json_writer_putstring; .long json_writer_putstring
	.reloc ., R_386_SIZE32, json_writer_putstring; .long 0
	.long 0x7297327
	.long 0 /* index: 808 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 809 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 810 */
	.long 0
	.long 0
	.long 0
	.long .Lname811 /* index: 811 */
	.weak mall_validate_padding; .long mall_validate_padding
	.reloc ., R_386_SIZE32, mall_validate_padding; .long 0
	.long 0xaf49087
	.long 0 /* index: 812 */
	.long 0
	.long 0
	.long 0
	.long .Lname813 /* index: 813 */
	.weak validate_user; .long validate_user
	.reloc ., R_386_SIZE32, validate_user; .long 0
	.long 0x6343332
	.long 0 /* index: 814 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 815 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 816 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 817 */
	.long 0
	.long 0
	.long 0
	.long .Lname818 /* index: 818 */
	.weak sys_mmap2; .long sys_mmap2
	.reloc ., R_386_SIZE32, sys_mmap2; .long 0
	.long 0x9644332
	.long .Lname819 /* index: 819 */
	.weak swap_malloc; .long swap_malloc
	.reloc ., R_386_SIZE32, swap_malloc; .long 0
	.long 0x64f0b33
	.long .Lname820 /* index: 820 */
	.weak krand_seed; .long krand_seed
	.reloc ., R_386_SIZE32, krand_seed; .long 0
	.long 0x4a1b334
	.long .Lname821 /* index: 821 */
	.weak driver_with_name; .long driver_with_name
	.reloc ., R_386_SIZE32, driver_with_name; .long 0
	.long 0x6289335
	.long 0 /* index: 822 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 823 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 824 */
	.long 0
	.long 0
	.long 0
	.long .Lname825 /* index: 825 */
	.weak x86_syscall_is_cancellation_point; .long x86_syscall_is_cancellation_point
	.reloc ., R_386_SIZE32, x86_syscall_is_cancellation_point; .long 0
	.long 0x848b34
	.long 0 /* index: 826 */
	.long 0
	.long 0
	.long 0
	.long .Lname827 /* index: 827 */
	.weak strcmp; .long strcmp
	.reloc ., R_386_SIZE32, strcmp; .long 0
	.long 0x7ab8a40
	.long .Lname828 /* index: 828 */
	.weak sys_geteuid; .long sys_geteuid
	.reloc ., R_386_SIZE32, sys_geteuid; .long 0
	.long 0xdb1c2a4
	.long 0 /* index: 829 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 830 */
	.long 0
	.long 0
	.long 0
	.long .Lname831 /* index: 831 */
	.weak stack_inuse; .long stack_inuse
	.reloc ., R_386_SIZE32, stack_inuse; .long 0
	.long 0x126fb35
	.long 0 /* index: 832 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 833 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 834 */
	.long 0
	.long 0
	.long 0
	.long .Lname835 /* index: 835 */
	.weak system_trimheaps; .long system_trimheaps
	.reloc ., R_386_SIZE32, system_trimheaps; .long 0
	.long 0x6f86353
	.long .Lname836 /* index: 836 */
	.weak sys_open_by_handle_at; .long sys_open_by_handle_at
	.reloc ., R_386_SIZE32, sys_open_by_handle_at; .long 0
	.long 0x86bfac4
	.long .Lname837 /* index: 837 */
	.weak vm_datapart_lock_downgrade; .long vm_datapart_lock_downgrade
	.reloc ., R_386_SIZE32, vm_datapart_lock_downgrade; .long 0
	.long 0xe1af345
	.long .Lname838 /* index: 838 */
	.weak sys_waitpid; .long sys_waitpid
	.reloc ., R_386_SIZE32, sys_waitpid; .long 0
	.long 0xd1bbf94
	.long 0 /* index: 839 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 840 */
	.long 0
	.long 0
	.long 0
	.long .Lname841 /* index: 841 */
	.weak handle_get_regular_node; .long handle_get_regular_node
	.reloc ., R_386_SIZE32, handle_get_regular_node; .long 0
	.long 0xc3701b5
	.long 0 /* index: 842 */
	.long 0
	.long 0
	.long 0
	.long .Lname843 /* index: 843 */
	.weak sys_sched_get_priority_max; .long sys_sched_get_priority_max
	.reloc ., R_386_SIZE32, sys_sched_get_priority_max; .long 0
	.long 0xdd6a7e8
	.long 0 /* index: 844 */
	.long 0
	.long 0
	.long 0
	.long .Lname845 /* index: 845 */
	.weak dbg_newline_mode; .long dbg_newline_mode
	.reloc ., R_386_SIZE32, dbg_newline_mode; .long 0
	.long 0x300cf95
	.long 0 /* index: 846 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 847 */
	.long 0
	.long 0
	.long 0
	.long .Lname848 /* index: 848 */
	.weak task_raisesignalprocessgroup; .long task_raisesignalprocessgroup
	.reloc ., R_386_SIZE32, task_raisesignalprocessgroup; .long 0
	.long 0x417a350
	.long 0 /* index: 849 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 850 */
	.long 0
	.long 0
	.long 0
	.long .Lname851 /* index: 851 */
	.weak handle_manager_alloc; .long handle_manager_alloc
	.reloc ., R_386_SIZE32, handle_manager_alloc; .long 0
	.long 0xd198353
	.long .Lname852 /* index: 852 */
	.weak error_unwind; .long error_unwind
	.reloc ., R_386_SIZE32, error_unwind; .long 0
	.long 0x8c4ac4
	.long 0 /* index: 853 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 854 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 855 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 856 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 857 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 858 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 859 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 860 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 861 */
	.long 0
	.long 0
	.long 0
	.long .Lname862 /* index: 862 */
	.weak vm_tasklock_tryservice; .long vm_tasklock_tryservice
	.reloc ., R_386_SIZE32, vm_tasklock_tryservice; .long 0
	.long 0xd50a3a5
	.long 0 /* index: 863 */
	.long 0
	.long 0
	.long 0
	.long .Lname864 /* index: 864 */
	.weak task_sleep; .long task_sleep
	.reloc ., R_386_SIZE32, task_sleep; .long 0
	.long 0x16f8360
	.long .Lname865 /* index: 865 */
	.weak vmb_node_remove; .long vmb_node_remove
	.reloc ., R_386_SIZE32, vmb_node_remove; .long 0
	.long 0xeef2165
	.long 0 /* index: 866 */
	.long 0
	.long 0
	.long 0
	.long .Lname867 /* index: 867 */
	.weak __x86_bootcpu_idfeatures; .long __x86_bootcpu_idfeatures
	.reloc ., R_386_SIZE32, __x86_bootcpu_idfeatures; .long 0
	.long 0xfdae363
	.long .Lname868 /* index: 868 */
	.weak json_parser_getuint64; .long json_parser_getuint64
	.reloc ., R_386_SIZE32, json_parser_getuint64; .long 0
	.long 0x43e1364
	.long .Lname869 /* index: 869 */
	.weak pagedir_mapone; .long pagedir_mapone
	.reloc ., R_386_SIZE32, pagedir_mapone; .long 0
	.long 0x3e3e365
	.long 0 /* index: 870 */
	.long 0
	.long 0
	.long 0
	.long .Lname871 /* index: 871 */
	.weak vio_andw; .long vio_andw
	.reloc ., R_386_SIZE32, vio_andw; .long 0
	.long 0x558367
	.long .Lname872 /* index: 872 */
	.weak dbg_messagebox; .long dbg_messagebox
	.reloc ., R_386_SIZE32, dbg_messagebox; .long 0
	.long 0x1ab8368
	.long .Lname873 /* index: 873 */
	.weak keyboard_device_trygetkey; .long keyboard_device_trygetkey
	.reloc ., R_386_SIZE32, keyboard_device_trygetkey; .long 0
	.long 0x92e0369
	.long 0 /* index: 874 */
	.long 0
	.long 0
	.long 0
	.long .Lname875 /* index: 875 */
	.weak sigmask_check; .long sigmask_check
	.reloc ., R_386_SIZE32, sigmask_check; .long 0
	.long 0xaa7d36b
	.long .Lname876 /* index: 876 */
	.weak mouse_device_stat; .long mouse_device_stat
	.reloc ., R_386_SIZE32, mouse_device_stat; .long 0
	.long 0x2980ae4
	.long .Lname877 /* index: 877 */
	.weak task_setvm; .long task_setvm
	.reloc ., R_386_SIZE32, task_setvm; .long 0
	.long 0x16e636d
	.long 0 /* index: 878 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 879 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 880 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 881 */
	.long 0
	.long 0
	.long 0
	.long .Lname882 /* index: 882 */
	.weak vio_andb; .long vio_andb
	.reloc ., R_386_SIZE32, vio_andb; .long 0
	.long 0x558372
	.long 0 /* index: 883 */
	.long 0
	.long 0
	.long 0
	.long .Lname884 /* index: 884 */
	.weak vm_datapart_lock_read; .long vm_datapart_lock_read
	.reloc ., R_386_SIZE32, vm_datapart_lock_read; .long 0
	.long 0x5441374
	.long 0 /* index: 885 */
	.long 0
	.long 0
	.long 0
	.long .Lname886 /* index: 886 */
	.weak dbg_vpprintf; .long dbg_vpprintf
	.reloc ., R_386_SIZE32, dbg_vpprintf; .long 0
	.long 0x1d03376
	.long .Lname887 /* index: 887 */
	.weak vfs_kernel; .long vfs_kernel
	.reloc ., R_386_SIZE32, vfs_kernel; .long 0
	.long 0x61b592c
	.long 0 /* index: 888 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 889 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 890 */
	.long 0
	.long 0
	.long 0
	.long .Lname891 /* index: 891 */
	.weak driver_section_lock; .long driver_section_lock
	.reloc ., R_386_SIZE32, driver_section_lock; .long 0
	.long 0x94f537b
	.long .Lname892 /* index: 892 */
	.weak vio_andl; .long vio_andl
	.reloc ., R_386_SIZE32, vio_andl; .long 0
	.long 0x55837c
	.long .Lname893 /* index: 893 */
	.weak inode_readallv; .long inode_readallv
	.reloc ., R_386_SIZE32, inode_readallv; .long 0
	.long 0xe20d4b6
	.long .Lname894 /* index: 894 */
	.weak inode_chown; .long inode_chown
	.reloc ., R_386_SIZE32, inode_chown; .long 0
	.long 0xb29c37e
	.long .Lname895 /* index: 895 */
	.weak block_device_acquire_partlock_write; .long block_device_acquire_partlock_write
	.reloc ., R_386_SIZE32, block_device_acquire_partlock_write; .long 0
	.long 0xd5bb095
	.long .Lname896 /* index: 896 */
	.weak vm_map; .long vm_map
	.reloc ., R_386_SIZE32, vm_map; .long 0
	.long 0x7d36380
	.long .Lname897 /* index: 897 */
	.weak memrendq; .long memrendq
	.reloc ., R_386_SIZE32, memrendq; .long 0
	.long 0xc48c381
	.long 0 /* index: 898 */
	.long 0
	.long 0
	.long 0
	.long .Lname899 /* index: 899 */
	.weak sys_fstatfs; .long sys_fstatfs
	.reloc ., R_386_SIZE32, sys_fstatfs; .long 0
	.long 0xdd18383
	.long .Lname900 /* index: 900 */
	.weak vm_datablock_read; .long vm_datablock_read
	.reloc ., R_386_SIZE32, vm_datablock_read; .long 0
	.long 0x2ec4384
	.long .Lname901 /* index: 901 */
	.weak superblock_mountlock_trywrite; .long superblock_mountlock_trywrite
	.reloc ., R_386_SIZE32, superblock_mountlock_trywrite; .long 0
	.long 0xa19c385
	.long 0 /* index: 902 */
	.long 0
	.long 0
	.long 0
	.long .Lname903 /* index: 903 */
	.weak cpu_loadpending; .long cpu_loadpending
	.reloc ., R_386_SIZE32, cpu_loadpending; .long 0
	.long 0xde79387
	.long .Lname904 /* index: 904 */
	.weak path_traversenfull_ex; .long path_traversenfull_ex
	.reloc ., R_386_SIZE32, path_traversenfull_ex; .long 0
	.long 0xbae5388
	.long .Lname905 /* index: 905 */
	.weak json_parser_findkey; .long json_parser_findkey
	.reloc ., R_386_SIZE32, json_parser_findkey; .long 0
	.long 0x5db3389
	.long .Lname906 /* index: 906 */
	.weak cred_require_hwio; .long cred_require_hwio
	.reloc ., R_386_SIZE32, cred_require_hwio; .long 0
	.long 0xe53fc5f
	.long 0 /* index: 907 */
	.long 0
	.long 0
	.long 0
	.long .Lname908 /* index: 908 */
	.weak kernel_debugtraps_uninstall; .long kernel_debugtraps_uninstall
	.reloc ., R_386_SIZE32, kernel_debugtraps_uninstall; .long 0
	.long 0x6ea538c
	.long .Lname909 /* index: 909 */
	.weak sys_alarm; .long sys_alarm
	.reloc ., R_386_SIZE32, sys_alarm; .long 0
	.long 0x958538d
	.long 0 /* index: 910 */
	.long 0
	.long 0
	.long 0
	.long .Lname911 /* index: 911 */
	.weak aio_pbuffer_copyfrommem; .long aio_pbuffer_copyfrommem
	.reloc ., R_386_SIZE32, aio_pbuffer_copyfrommem; .long 0
	.long 0xf3faded
	.long 0 /* index: 912 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 913 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 914 */
	.long 0
	.long 0
	.long 0
	.long .Lname915 /* index: 915 */
	.weak vio_copyfromvio_to_phys; .long vio_copyfromvio_to_phys
	.reloc ., R_386_SIZE32, vio_copyfromvio_to_phys; .long 0
	.long 0xb207393
	.long .Lname916 /* index: 916 */
	.weak sys_eventfd; .long sys_eventfd
	.reloc ., R_386_SIZE32, sys_eventfd; .long 0
	.long 0xcb15394
	.long .Lname917 /* index: 917 */
	.weak vm_clone; .long vm_clone
	.reloc ., R_386_SIZE32, vm_clone; .long 0
	.long 0x35a3395
	.long 0 /* index: 918 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 919 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 920 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 921 */
	.long 0
	.long 0
	.long 0
	.long .Lname922 /* index: 922 */
	.weak sys_getitimer64; .long sys_getitimer64
	.reloc ., R_386_SIZE32, sys_getitimer64; .long 0
	.long 0x3be7794
	.long .Lname923 /* index: 923 */
	.weak directory_link; .long directory_link
	.reloc ., R_386_SIZE32, directory_link; .long 0
	.long 0x97f839b
	.long .Lname924 /* index: 924 */
	.weak memrendl; .long memrendl
	.reloc ., R_386_SIZE32, memrendl; .long 0
	.long 0xc48c39c
	.long 0 /* index: 925 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 926 */
	.long 0
	.long 0
	.long 0
	.long .Lname927 /* index: 927 */
	.weak vm_node_remove; .long vm_node_remove
	.reloc ., R_386_SIZE32, vm_node_remove; .long 0
	.long 0x5ef7b45
	.long 0 /* index: 928 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 929 */
	.long 0
	.long 0
	.long 0
	.long .Lname930 /* index: 930 */
	.weak vm86_pic_intr; .long vm86_pic_intr
	.reloc ., R_386_SIZE32, vm86_pic_intr; .long 0
	.long 0x29e43a2
	.long .Lname931 /* index: 931 */
	.weak x86_lapic_base_address; .long x86_lapic_base_address
	.reloc ., R_386_SIZE32, x86_lapic_base_address; .long 0
	.long 0x40cc3a3
	.long .Lname932 /* index: 932 */
	.weak x86_fpustate_load; .long x86_fpustate_load
	.reloc ., R_386_SIZE32, x86_fpustate_load; .long 0
	.long 0x7b343a4
	.long .Lname933 /* index: 933 */
	.weak terminal_poll_iwrite; .long terminal_poll_iwrite
	.reloc ., R_386_SIZE32, terminal_poll_iwrite; .long 0
	.long 0xcfdf3a5
	.long .Lname934 /* index: 934 */
	.weak sys_pwritev; .long sys_pwritev
	.reloc ., R_386_SIZE32, sys_pwritev; .long 0
	.long 0x79403a6
	.long .Lname935 /* index: 935 */
	.weak cpu_assert_running; .long cpu_assert_running
	.reloc ., R_386_SIZE32, cpu_assert_running; .long 0
	.long 0x5a063a7
	.long 0 /* index: 936 */
	.long 0
	.long 0
	.long 0
	.long .Lname937 /* index: 937 */
	.weak handle_manager_clone; .long handle_manager_clone
	.reloc ., R_386_SIZE32, handle_manager_clone; .long 0
	.long 0xd178645
	.long 0 /* index: 938 */
	.long 0
	.long 0
	.long 0
	.long .Lname939 /* index: 939 */
	.weak _this_kernel_stack; .long _this_kernel_stack
	.reloc ., R_386_SIZE32, _this_kernel_stack; .long 0
	.long 0x61c23ab
	.long 0 /* index: 940 */
	.long 0
	.long 0
	.long 0
	.long .Lname941 /* index: 941 */
	.weak x86_check_spurious_interrupt_PIC2; .long x86_check_spurious_interrupt_PIC2
	.reloc ., R_386_SIZE32, x86_check_spurious_interrupt_PIC2; .long 0
	.long 0x177adf2
	.long .Lname942 /* index: 942 */
	.weak sys_ftime; .long sys_ftime
	.reloc ., R_386_SIZE32, sys_ftime; .long 0
	.long 0x95dd535
	.long 0 /* index: 943 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 944 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 945 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 946 */
	.long 0
	.long 0
	.long 0
	.long .Lname947 /* index: 947 */
	.weak vm86_exec; .long vm86_exec
	.reloc ., R_386_SIZE32, vm86_exec; .long 0
	.long 0xbc5b3b3
	.long .Lname948 /* index: 948 */
	.weak rwlock_endread; .long rwlock_endread
	.reloc ., R_386_SIZE32, rwlock_endread; .long 0
	.long 0x67e23b4
	.long .Lname949 /* index: 949 */
	.weak unwind_setreg_scpustate; .long unwind_setreg_scpustate
	.reloc ., R_386_SIZE32, unwind_setreg_scpustate; .long 0
	.long 0xb8d03b5
	.long .Lname950 /* index: 950 */
	.weak vm_datablock_anonymous_type; .long vm_datablock_anonymous_type
	.reloc ., R_386_SIZE32, vm_datablock_anonymous_type; .long 0
	.long 0x141adc5
	.long 0 /* index: 951 */
	.long 0
	.long 0
	.long 0
	.long .Lname952 /* index: 952 */
	.weak vm_datapart_lock_endwrite; .long vm_datapart_lock_endwrite
	.reloc ., R_386_SIZE32, vm_datapart_lock_endwrite; .long 0
	.long 0xcbbd795
	.long 0 /* index: 953 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 954 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 955 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 956 */
	.long 0
	.long 0
	.long 0
	.long .Lname957 /* index: 957 */
	.weak memmem; .long memmem
	.reloc ., R_386_SIZE32, memmem; .long 0
	.long 0x73c43bd
	.long 0 /* index: 958 */
	.long 0
	.long 0
	.long 0
	.long .Lname959 /* index: 959 */
	.weak kernel_debugtrap_fcpustate; .long kernel_debugtrap_fcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_fcpustate; .long 0
	.long 0x9638df5
	.long 0 /* index: 960 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 961 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 962 */
	.long 0
	.long 0
	.long 0
	.long .Lname963 /* index: 963 */
	.weak pty_master_alloc; .long pty_master_alloc
	.reloc ., R_386_SIZE32, pty_master_alloc; .long 0
	.long 0x26a0463
	.long .Lname964 /* index: 964 */
	.weak acpi_root; .long acpi_root
	.reloc ., R_386_SIZE32, acpi_root; .long 0
	.long 0x6f6f3c4
	.long .Lname965 /* index: 965 */
	.weak unwind_setreg_sfpustate; .long unwind_setreg_sfpustate
	.reloc ., R_386_SIZE32, unwind_setreg_sfpustate; .long 0
	.long 0xb8d03c5
	.long 0 /* index: 966 */
	.long 0
	.long 0
	.long 0
	.long .Lname967 /* index: 967 */
	.weak sys_syslog; .long sys_syslog
	.reloc ., R_386_SIZE32, sys_syslog; .long 0
	.long 0x6b733c7
	.long .Lname968 /* index: 968 */
	.weak task_alloc_user_rpc_nx; .long task_alloc_user_rpc_nx
	.reloc ., R_386_SIZE32, task_alloc_user_rpc_nx; .long 0
	.long 0xcab93c8
	.long .Lname969 /* index: 969 */
	.weak sys_hopf; .long sys_hopf
	.reloc ., R_386_SIZE32, sys_hopf; .long 0
	.long 0x95f1d6
	.long 0 /* index: 970 */
	.long 0
	.long 0
	.long 0
	.long .Lname971 /* index: 971 */
	.weak sys_recvmsg; .long sys_recvmsg
	.reloc ., R_386_SIZE32, sys_recvmsg; .long 0
	.long 0x8c1ddf7
	.long 0 /* index: 972 */
	.long 0
	.long 0
	.long 0
	.long .Lname973 /* index: 973 */
	.weak fpustate_loadfrom; .long fpustate_loadfrom
	.reloc ., R_386_SIZE32, fpustate_loadfrom; .long 0
	.long 0xf9d33cd
	.long .Lname974 /* index: 974 */
	.weak ringbuffer_setwritten; .long ringbuffer_setwritten
	.reloc ., R_386_SIZE32, ringbuffer_setwritten; .long 0
	.long 0x64fe3ce
	.long 0 /* index: 975 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 976 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 977 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 978 */
	.long 0
	.long 0
	.long 0
	.long .Lname979 /* index: 979 */
	.weak ringbuffer_write_nonblock_noalloc; .long ringbuffer_write_nonblock_noalloc
	.reloc ., R_386_SIZE32, ringbuffer_write_nonblock_noalloc; .long 0
	.long 0x4af0a3
	.long .Lname980 /* index: 980 */
	.weak slab_kmalloc_nx4; .long slab_kmalloc_nx4
	.reloc ., R_386_SIZE32, slab_kmalloc_nx4; .long 0
	.long 0xb40d3d4
	.long 0 /* index: 981 */
	.long 0
	.long 0
	.long 0
	.long .Lname982 /* index: 982 */
	.weak unicode_8to16; .long unicode_8to16
	.reloc ., R_386_SIZE32, unicode_8to16; .long 0
	.long 0x7601796
	.long .Lname983 /* index: 983 */
	.weak krealign_in_place; .long krealign_in_place
	.reloc ., R_386_SIZE32, krealign_in_place; .long 0
	.long 0x2f7e915
	.long .Lname984 /* index: 984 */
	.weak slab_kmalloc_nx8; .long slab_kmalloc_nx8
	.reloc ., R_386_SIZE32, slab_kmalloc_nx8; .long 0
	.long 0xb40d3d8
	.long .Lname985 /* index: 985 */
	.weak directory_entry_destroy; .long directory_entry_destroy
	.reloc ., R_386_SIZE32, directory_entry_destroy; .long 0
	.long 0x84cb3d9
	.long .Lname986 /* index: 986 */
	.weak page_malloc_part; .long page_malloc_part
	.reloc ., R_386_SIZE32, page_malloc_part; .long 0
	.long 0xef24f94
	.long 0 /* index: 987 */
	.long 0
	.long 0
	.long 0
	.long .Lname988 /* index: 988 */
	.weak driver_with_namel; .long driver_with_namel
	.reloc ., R_386_SIZE32, driver_with_namel; .long 0
	.long 0x28933dc
	.long .Lname989 /* index: 989 */
	.weak memrchrw; .long memrchrw
	.reloc ., R_386_SIZE32, memrchrw; .long 0
	.long 0xc4898a7
	.long 0 /* index: 990 */
	.long 0
	.long 0
	.long 0
	.long .Lname991 /* index: 991 */
	.weak debuginfo_cu_parser_loadattr_variable; .long debuginfo_cu_parser_loadattr_variable
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_variable; .long 0
	.long 0xf118a5
	.long .Lname992 /* index: 992 */
	.weak debuginfo_print_value; .long debuginfo_print_value
	.reloc ., R_386_SIZE32, debuginfo_print_value; .long 0
	.long 0x8b66165
	.long 0 /* index: 993 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 994 */
	.long 0
	.long 0
	.long 0
	.long .Lname995 /* index: 995 */
	.weak vm_datapart_read_phys; .long vm_datapart_read_phys
	.reloc ., R_386_SIZE32, vm_datapart_read_phys; .long 0
	.long 0xab4d3e3
	.long .Lname996 /* index: 996 */
	.weak isr_unregister_at; .long isr_unregister_at
	.reloc ., R_386_SIZE32, isr_unregister_at; .long 0
	.long 0x68473e4
	.long .Lname997 /* index: 997 */
	.weak json_decode; .long json_decode
	.reloc ., R_386_SIZE32, json_decode; .long 0
	.long 0x5da43e5
	.long 0 /* index: 998 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 999 */
	.long 0
	.long 0
	.long 0
	.long .Lname1000 /* index: 1000 */
	.weak path_traversen_ex; .long path_traversen_ex
	.reloc ., R_386_SIZE32, path_traversen_ex; .long 0
	.long 0xf5643e8
	.long 0 /* index: 1001 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1002 */
	.long 0
	.long 0
	.long 0
	.long .Lname1003 /* index: 1003 */
	.weak x86_pit_lock; .long x86_pit_lock
	.reloc ., R_386_SIZE32, x86_pit_lock; .long 0
	.long 0x73ff3eb
	.long 0 /* index: 1004 */
	.long 0
	.long 0
	.long 0
	.long .Lname1005 /* index: 1005 */
	.weak validate_userm; .long validate_userm
	.reloc ., R_386_SIZE32, validate_userm; .long 0
	.long 0x34333ed
	.long 0 /* index: 1006 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1007 */
	.long 0
	.long 0
	.long 0
	.long .Lname1008 /* index: 1008 */
	.weak vmb_map; .long vmb_map
	.reloc ., R_386_SIZE32, vmb_map; .long 0
	.long 0xd3863f0
	.long 0 /* index: 1009 */
	.long 0
	.long 0
	.long 0
	.long .Lname1010 /* index: 1010 */
	.weak block_device_awrite_phys_sector; .long block_device_awrite_phys_sector
	.reloc ., R_386_SIZE32, block_device_awrite_phys_sector; .long 0
	.long 0xb8a83f2
	.long .Lname1011 /* index: 1011 */
	.weak sys_utimes; .long sys_utimes
	.reloc ., R_386_SIZE32, sys_utimes; .long 0
	.long 0x6cd5353
	.long .Lname1012 /* index: 1012 */
	.weak sys_nanosleep64; .long sys_nanosleep64
	.reloc ., R_386_SIZE32, sys_nanosleep64; .long 0
	.long 0x14fe3f4
	.long .Lname1013 /* index: 1013 */
	.weak kernel_panic_kcpustate; .long kernel_panic_kcpustate
	.reloc ., R_386_SIZE32, kernel_panic_kcpustate; .long 0
	.long 0x78a93f5
	.long 0 /* index: 1014 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1015 */
	.long 0
	.long 0
	.long 0
	.long .Lname1016 /* index: 1016 */
	.weak handle_get_path; .long handle_get_path
	.reloc ., R_386_SIZE32, handle_get_path; .long 0
	.long 0x834b3f8
	.long .Lname1017 /* index: 1017 */
	.weak sys_name_to_handle_at; .long sys_name_to_handle_at
	.reloc ., R_386_SIZE32, sys_name_to_handle_at; .long 0
	.long 0xb83f354
	.long 0 /* index: 1018 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1019 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1020 */
	.long 0
	.long 0
	.long 0
	.long .Lname1021 /* index: 1021 */
	.weak sighand_ptr_lockwrite; .long sighand_ptr_lockwrite
	.reloc ., R_386_SIZE32, sighand_ptr_lockwrite; .long 0
	.long 0x44f0465
	.long 0 /* index: 1022 */
	.long 0
	.long 0
	.long 0
	.long .Lname1023 /* index: 1023 */
	.weak ringbuffer_unwrite; .long ringbuffer_unwrite
	.reloc ., R_386_SIZE32, ringbuffer_unwrite; .long 0
	.long 0x8021b55
	.long 0 /* index: 1024 */
	.long 0
	.long 0
	.long 0
	.long .Lname1025 /* index: 1025 */
	.weak memcmpq; .long memcmpq
	.reloc ., R_386_SIZE32, memcmpq; .long 0
	.long 0x3c3a401
	.long 0 /* index: 1026 */
	.long 0
	.long 0
	.long 0
	.long .Lname1027 /* index: 1027 */
	.weak task_connect_ghost_c; .long task_connect_ghost_c
	.reloc ., R_386_SIZE32, task_connect_ghost_c; .long 0
	.long 0x1c6403
	.long .Lname1028 /* index: 1028 */
	.weak vm_syncall_locked; .long vm_syncall_locked
	.reloc ., R_386_SIZE32, vm_syncall_locked; .long 0
	.long 0x621d404
	.long 0 /* index: 1029 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1030 */
	.long 0
	.long 0
	.long 0
	.long .Lname1031 /* index: 1031 */
	.weak memcmpw; .long memcmpw
	.reloc ., R_386_SIZE32, memcmpw; .long 0
	.long 0x3c3a407
	.long .Lname1032 /* index: 1032 */
	.weak sys_rmdir; .long sys_rmdir
	.reloc ., R_386_SIZE32, sys_rmdir; .long 0
	.long 0x9694202
	.long .Lname1033 /* index: 1033 */
	.weak sys_getsockopt; .long sys_getsockopt
	.reloc ., R_386_SIZE32, sys_getsockopt; .long 0
	.long 0xacddd74
	.long 0 /* index: 1034 */
	.long 0
	.long 0
	.long 0
	.long .Lname1035 /* index: 1035 */
	.weak x86_fxsave_mxcsr_mask; .long x86_fxsave_mxcsr_mask
	.reloc ., R_386_SIZE32, x86_fxsave_mxcsr_mask; .long 0
	.long 0xb8df40b
	.long 0 /* index: 1036 */
	.long 0
	.long 0
	.long 0
	.long .Lname1037 /* index: 1037 */
	.weak task_waitfor; .long task_waitfor
	.reloc ., R_386_SIZE32, task_waitfor; .long 0
	.long 0xae80e02
	.long 0 /* index: 1038 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1039 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1040 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1041 */
	.long 0
	.long 0
	.long 0
	.long .Lname1042 /* index: 1042 */
	.weak keyboard_device_trygetchar; .long keyboard_device_trygetchar
	.reloc ., R_386_SIZE32, keyboard_device_trygetchar; .long 0
	.long 0x2dfb412
	.long 0 /* index: 1043 */
	.long 0
	.long 0
	.long 0
	.long .Lname1044 /* index: 1044 */
	.weak symlink_node_load; .long symlink_node_load
	.reloc ., R_386_SIZE32, symlink_node_load; .long 0
	.long 0xafa5414
	.long 0 /* index: 1045 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1046 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1047 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1048 */
	.long 0
	.long 0
	.long 0
	.long .Lname1049 /* index: 1049 */
	.weak sys_linux_oldfstat; .long sys_linux_oldfstat
	.reloc ., R_386_SIZE32, sys_linux_oldfstat; .long 0
	.long 0xb41fe04
	.long 0 /* index: 1050 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1051 */
	.long 0
	.long 0
	.long 0
	.long .Lname1052 /* index: 1052 */
	.weak memcmpl; .long memcmpl
	.reloc ., R_386_SIZE32, memcmpl; .long 0
	.long 0x3c3a41c
	.long .Lname1053 /* index: 1053 */
	.weak handle_get_vm; .long handle_get_vm
	.reloc ., R_386_SIZE32, handle_get_vm; .long 0
	.long 0xb58341d
	.long .Lname1054 /* index: 1054 */
	.weak terminal_flush_icanon; .long terminal_flush_icanon
	.reloc ., R_386_SIZE32, terminal_flush_icanon; .long 0
	.long 0x96a941e
	.long .Lname1055 /* index: 1055 */
	.weak sys_clock_settime; .long sys_clock_settime
	.reloc ., R_386_SIZE32, sys_clock_settime; .long 0
	.long 0x3a50605
	.long 0 /* index: 1056 */
	.long 0
	.long 0
	.long 0
	.long .Lname1057 /* index: 1057 */
	.weak vm_datablock_vio_writev_phys; .long vm_datablock_vio_writev_phys
	.reloc ., R_386_SIZE32, vm_datablock_vio_writev_phys; .long 0
	.long 0x1064023
	.long 0 /* index: 1058 */
	.long 0
	.long 0
	.long 0
	.long .Lname1059 /* index: 1059 */
	.weak dbg_enter_lcpustate; .long dbg_enter_lcpustate
	.reloc ., R_386_SIZE32, dbg_enter_lcpustate; .long 0
	.long 0x781b635
	.long 0 /* index: 1060 */
	.long 0
	.long 0
	.long 0
	.long .Lname1061 /* index: 1061 */
	.weak vm_kernel_treelock_trywrite; .long vm_kernel_treelock_trywrite
	.reloc ., R_386_SIZE32, vm_kernel_treelock_trywrite; .long 0
	.long 0x33e2425
	.long 0 /* index: 1062 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1063 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1064 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1065 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1066 */
	.long 0
	.long 0
	.long 0
	.long .Lname1067 /* index: 1067 */
	.weak sys_epoll_wait; .long sys_epoll_wait
	.reloc ., R_386_SIZE32, sys_epoll_wait; .long 0
	.long 0x39316f4
	.long .Lname1068 /* index: 1068 */
	.weak vmb_find_first_node_greater_equal; .long vmb_find_first_node_greater_equal
	.reloc ., R_386_SIZE32, vmb_find_first_node_greater_equal; .long 0
	.long 0x12eabdc
	.long .Lname1069 /* index: 1069 */
	.weak kernel_driver; .long kernel_driver
	.reloc ., R_386_SIZE32, kernel_driver; .long 0
	.long 0x47240b2
	.long .Lname1070 /* index: 1070 */
	.weak driver_getsection; .long driver_getsection
	.reloc ., R_386_SIZE32, driver_getsection; .long 0
	.long 0x594e42e
	.long .Lname1071 /* index: 1071 */
	.weak handle_installinto; .long handle_installinto
	.reloc ., R_386_SIZE32, handle_installinto; .long 0
	.long 0xbaaf42f
	.long .Lname1072 /* index: 1072 */
	.weak acpi_lookup; .long acpi_lookup
	.reloc ., R_386_SIZE32, acpi_lookup; .long 0
	.long 0x6540430
	.long .Lname1073 /* index: 1073 */
	.weak superblock_set_unmounted; .long superblock_set_unmounted
	.reloc ., R_386_SIZE32, superblock_set_unmounted; .long 0
	.long 0xb403d74
	.long .Lname1074 /* index: 1074 */
	.weak vpage_realloc; .long vpage_realloc
	.reloc ., R_386_SIZE32, vpage_realloc; .long 0
	.long 0x5d20a43
	.long .Lname1075 /* index: 1075 */
	.weak vm_memsetphys; .long vm_memsetphys
	.reloc ., R_386_SIZE32, vm_memsetphys; .long 0
	.long 0x4fd5433
	.long .Lname1076 /* index: 1076 */
	.weak sys_futimesat; .long sys_futimesat
	.reloc ., R_386_SIZE32, sys_futimesat; .long 0
	.long 0x20a9434
	.long .Lname1077 /* index: 1077 */
	.weak pagedir_unprepare_mapone; .long pagedir_unprepare_mapone
	.reloc ., R_386_SIZE32, pagedir_unprepare_mapone; .long 0
	.long 0xbdfa435
	.long 0 /* index: 1078 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1079 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1080 */
	.long 0
	.long 0
	.long 0
	.long .Lname1081 /* index: 1081 */
	.weak pipe_destroy; .long pipe_destroy
	.reloc ., R_386_SIZE32, pipe_destroy; .long 0
	.long 0xdbad439
	.long 0 /* index: 1082 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1083 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1084 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1085 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1086 */
	.long 0
	.long 0
	.long 0
	.long .Lname1087 /* index: 1087 */
	.weak kfree; .long kfree
	.reloc ., R_386_SIZE32, kfree; .long 0
	.long 0x71d8b5
	.long .Lname1088 /* index: 1088 */
	.weak syscall_emulate_int80; .long syscall_emulate_int80
	.reloc ., R_386_SIZE32, syscall_emulate_int80; .long 0
	.long 0xa8c1440
	.long 0 /* index: 1089 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1090 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1091 */
	.long 0
	.long 0
	.long 0
	.long .Lname1092 /* index: 1092 */
	.weak sys_setresgid; .long sys_setresgid
	.reloc ., R_386_SIZE32, sys_setresgid; .long 0
	.long 0x85f444
	.long .Lname1093 /* index: 1093 */
	.weak vm_mapat_subrange; .long vm_mapat_subrange
	.reloc ., R_386_SIZE32, vm_mapat_subrange; .long 0
	.long 0x38dd445
	.long 0 /* index: 1094 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1095 */
	.long 0
	.long 0
	.long 0
	.long .Lname1096 /* index: 1096 */
	.weak path_printentex; .long path_printentex
	.reloc ., R_386_SIZE32, path_printentex; .long 0
	.long 0xf4e5448
	.long 0 /* index: 1097 */
	.long 0
	.long 0
	.long 0
	.long .Lname1098 /* index: 1098 */
	.weak sys_setresuid32; .long sys_setresuid32
	.reloc ., R_386_SIZE32, sys_setresuid32; .long 0
	.long 0x5c247e2
	.long .Lname1099 /* index: 1099 */
	.weak sys_exit; .long sys_exit
	.reloc ., R_386_SIZE32, sys_exit; .long 0
	.long 0x95cab4
	.long .Lname1100 /* index: 1100 */
	.weak vm_find_last_node_lower_equal; .long vm_find_last_node_lower_equal
	.reloc ., R_386_SIZE32, vm_find_last_node_lower_equal; .long 0
	.long 0x7a8a44c
	.long 0 /* index: 1101 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1102 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1103 */
	.long 0
	.long 0
	.long 0
	.long .Lname1104 /* index: 1104 */
	.weak vm_unmap; .long vm_unmap
	.reloc ., R_386_SIZE32, vm_unmap; .long 0
	.long 0x36c5450
	.long 0 /* index: 1105 */
	.long 0
	.long 0
	.long 0
	.long .Lname1106 /* index: 1106 */
	.weak _this_user_except_handler; .long _this_user_except_handler
	.reloc ., R_386_SIZE32, _this_user_except_handler; .long 0
	.long 0xaeb6452
	.long .Lname1107 /* index: 1107 */
	.weak task_schedule_user_srpc; .long task_schedule_user_srpc
	.reloc ., R_386_SIZE32, task_schedule_user_srpc; .long 0
	.long 0x2cca453
	.long 0 /* index: 1108 */
	.long 0
	.long 0
	.long 0
	.long .Lname1109 /* index: 1109 */
	.weak sys_timer_create; .long sys_timer_create
	.reloc ., R_386_SIZE32, sys_timer_create; .long 0
	.long 0x3013455
	.long 0 /* index: 1110 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1111 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1112 */
	.long 0
	.long 0
	.long 0
	.long .Lname1113 /* index: 1113 */
	.weak handle_get_superblock_relaxed; .long handle_get_superblock_relaxed
	.reloc ., R_386_SIZE32, handle_get_superblock_relaxed; .long 0
	.long 0x5e03b64
	.long 0 /* index: 1114 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1115 */
	.long 0
	.long 0
	.long 0
	.long .Lname1116 /* index: 1116 */
	.weak vmb_find_last_node_lower_equal; .long vmb_find_last_node_lower_equal
	.reloc ., R_386_SIZE32, vmb_find_last_node_lower_equal; .long 0
	.long 0xe02545c
	.long 0 /* index: 1117 */
	.long 0
	.long 0
	.long 0
	.long .Lname1118 /* index: 1118 */
	.weak heap_align; .long heap_align
	.reloc ., R_386_SIZE32, heap_align; .long 0
	.long 0x652c45e
	.long .Lname1119 /* index: 1119 */
	.weak aio_multihandle_extension_destroy; .long aio_multihandle_extension_destroy
	.reloc ., R_386_SIZE32, aio_multihandle_extension_destroy; .long 0
	.long 0xe82a579
	.long 0 /* index: 1120 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1121 */
	.long 0
	.long 0
	.long 0
	.long .Lname1122 /* index: 1122 */
	.weak sys_readdir; .long sys_readdir
	.reloc ., R_386_SIZE32, sys_readdir; .long 0
	.long 0x8cca462
	.long .Lname1123 /* index: 1123 */
	.weak task_alloc_user_srpc; .long task_alloc_user_srpc
	.reloc ., R_386_SIZE32, task_alloc_user_srpc; .long 0
	.long 0x79c9463
	.long 0 /* index: 1124 */
	.long 0
	.long 0
	.long 0
	.long .Lname1125 /* index: 1125 */
	.weak driver_clear_fde_cache; .long driver_clear_fde_cache
	.reloc ., R_386_SIZE32, driver_clear_fde_cache; .long 0
	.long 0xe1fc465
	.long 0 /* index: 1126 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1127 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1128 */
	.long 0
	.long 0
	.long 0
	.long .Lname1129 /* index: 1129 */
	.weak keyboard_buffer_trygetkey; .long keyboard_buffer_trygetkey
	.reloc ., R_386_SIZE32, keyboard_buffer_trygetkey; .long 0
	.long 0xa72d469
	.long 0 /* index: 1130 */
	.long 0
	.long 0
	.long 0
	.long .Lname1131 /* index: 1131 */
	.weak userkern_segment_block; .long userkern_segment_block
	.reloc ., R_386_SIZE32, userkern_segment_block; .long 0
	.long 0xb00546b
	.long .Lname1132 /* index: 1132 */
	.weak handle_manager_kernel; .long handle_manager_kernel
	.reloc ., R_386_SIZE32, handle_manager_kernel; .long 0
	.long 0x2e9946c
	.long .Lname1133 /* index: 1133 */
	.weak pipe_writer_create; .long pipe_writer_create
	.reloc ., R_386_SIZE32, pipe_writer_create; .long 0
	.long 0xfa87f85
	.long 0 /* index: 1134 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1135 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1136 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1137 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1138 */
	.long 0
	.long 0
	.long 0
	.long .Lname1139 /* index: 1139 */
	.weak task_redirect_usercode_rpc; .long task_redirect_usercode_rpc
	.reloc ., R_386_SIZE32, task_redirect_usercode_rpc; .long 0
	.long 0xcb7473
	.long .Lname1140 /* index: 1140 */
	.weak dbg_impersonate_thread; .long dbg_impersonate_thread
	.reloc ., R_386_SIZE32, dbg_impersonate_thread; .long 0
	.long 0x6c9c474
	.long 0 /* index: 1141 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1142 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1143 */
	.long 0
	.long 0
	.long 0
	.long .Lname1144 /* index: 1144 */
	.weak block_device_sync; .long block_device_sync
	.reloc ., R_386_SIZE32, block_device_sync; .long 0
	.long 0x8a55713
	.long .Lname1145 /* index: 1145 */
	.weak sys_acct; .long sys_acct
	.reloc ., R_386_SIZE32, sys_acct; .long 0
	.long 0x957e14
	.long .Lname1146 /* index: 1146 */
	.weak page_cfree; .long page_cfree
	.reloc ., R_386_SIZE32, page_cfree; .long 0
	.long 0xb5ebf65
	.long 0 /* index: 1147 */
	.long 0
	.long 0
	.long 0
	.long .Lname1148 /* index: 1148 */
	.weak memset; .long memset
	.reloc ., R_386_SIZE32, memset; .long 0
	.long 0x73c49c4
	.long 0 /* index: 1149 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1150 */
	.long 0
	.long 0
	.long 0
	.long .Lname1151 /* index: 1151 */
	.weak pipe_create; .long pipe_create
	.reloc ., R_386_SIZE32, pipe_create; .long 0
	.long 0x5dfbe15
	.long .Lname1152 /* index: 1152 */
	.weak pagedir_maphintone_p; .long pagedir_maphintone_p
	.reloc ., R_386_SIZE32, pagedir_maphintone_p; .long 0
	.long 0x6579480
	.long 0 /* index: 1153 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1154 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1155 */
	.long 0
	.long 0
	.long 0
	.long .Lname1156 /* index: 1156 */
	.weak dbg_indent; .long dbg_indent
	.reloc ., R_386_SIZE32, dbg_indent; .long 0
	.long 0x6020484
	.long .Lname1157 /* index: 1157 */
	.weak vm_datapart_lock_trywrite; .long vm_datapart_lock_trywrite
	.reloc ., R_386_SIZE32, vm_datapart_lock_trywrite; .long 0
	.long 0x20bd485
	.long 0 /* index: 1158 */
	.long 0
	.long 0
	.long 0
	.long .Lname1159 /* index: 1159 */
	.weak regdump_gpreg; .long regdump_gpreg
	.reloc ., R_386_SIZE32, regdump_gpreg; .long 0
	.long 0xee3c487
	.long 0 /* index: 1160 */
	.long 0
	.long 0
	.long 0
	.long .Lname1161 /* index: 1161 */
	.weak tty_device_poll; .long tty_device_poll
	.reloc ., R_386_SIZE32, tty_device_poll; .long 0
	.long 0x70ce36c
	.long 0 /* index: 1162 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1163 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1164 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1165 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1166 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1167 */
	.long 0
	.long 0
	.long 0
	.long .Lname1168 /* index: 1168 */
	.weak pagedir_prepare_map; .long pagedir_prepare_map
	.reloc ., R_386_SIZE32, pagedir_prepare_map; .long 0
	.long 0xa917490
	.long 0 /* index: 1169 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1170 */
	.long 0
	.long 0
	.long 0
	.long .Lname1171 /* index: 1171 */
	.weak error_subclass; .long error_subclass
	.reloc ., R_386_SIZE32, error_subclass; .long 0
	.long 0x220a8c3
	.long .Lname1172 /* index: 1172 */
	.weak sys_setpgid; .long sys_setpgid
	.reloc ., R_386_SIZE32, sys_setpgid; .long 0
	.long 0x9b06494
	.long .Lname1173 /* index: 1173 */
	.weak vm_kernel_treelock_tryupgrade; .long vm_kernel_treelock_tryupgrade
	.reloc ., R_386_SIZE32, vm_kernel_treelock_tryupgrade; .long 0
	.long 0xcfa0495
	.long .Lname1174 /* index: 1174 */
	.weak isr_usage_of; .long isr_usage_of
	.reloc ., R_386_SIZE32, isr_usage_of; .long 0
	.long 0xe773496
	.long 0 /* index: 1175 */
	.long 0
	.long 0
	.long 0
	.long .Lname1176 /* index: 1176 */
	.weak mall_trace_nx; .long mall_trace_nx
	.reloc ., R_386_SIZE32, mall_trace_nx; .long 0
	.long 0xbfa9498
	.long .Lname1177 /* index: 1177 */
	.weak oneshot_directory_file_destroy; .long oneshot_directory_file_destroy
	.reloc ., R_386_SIZE32, oneshot_directory_file_destroy; .long 0
	.long 0x6ae8499
	.long .Lname1178 /* index: 1178 */
	.weak unicode_16to32; .long unicode_16to32
	.reloc ., R_386_SIZE32, unicode_16to32; .long 0
	.long 0x6b80f12
	.long 0 /* index: 1179 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1180 */
	.long 0
	.long 0
	.long 0
	.long .Lname1181 /* index: 1181 */
	.weak pidns_tryservice; .long pidns_tryservice
	.reloc ., R_386_SIZE32, pidns_tryservice; .long 0
	.long 0xc581825
	.long 0 /* index: 1182 */
	.long 0
	.long 0
	.long 0
	.long .Lname1183 /* index: 1183 */
	.weak vm_free; .long vm_free
	.reloc ., R_386_SIZE32, vm_free; .long 0
	.long 0xd35d8c5
	.long 0 /* index: 1184 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1185 */
	.long 0
	.long 0
	.long 0
	.long .Lname1186 /* index: 1186 */
	.weak dbg_isholding_ctrl; .long dbg_isholding_ctrl
	.reloc ., R_386_SIZE32, dbg_isholding_ctrl; .long 0
	.long 0xbab568c
	.long .Lname1187 /* index: 1187 */
	.weak cpu_jiffies; .long cpu_jiffies
	.reloc ., R_386_SIZE32, cpu_jiffies; .long 0
	.long 0x96b4a3
	.long .Lname1188 /* index: 1188 */
	.weak sys_getpgid; .long sys_getpgid
	.reloc ., R_386_SIZE32, sys_getpgid; .long 0
	.long 0xdb064a4
	.long .Lname1189 /* index: 1189 */
	.weak dbg_vprintf; .long dbg_vprintf
	.reloc ., R_386_SIZE32, dbg_vprintf; .long 0
	.long 0xd1288c6
	.long 0 /* index: 1190 */
	.long 0
	.long 0
	.long 0
	.long .Lname1191 /* index: 1191 */
	.weak instruction_succ; .long instruction_succ
	.reloc ., R_386_SIZE32, instruction_succ; .long 0
	.long 0xfba04f3
	.long .Lname1192 /* index: 1192 */
	.weak superblock_mountlock_upgrade_nx; .long superblock_mountlock_upgrade_nx
	.reloc ., R_386_SIZE32, superblock_mountlock_upgrade_nx; .long 0
	.long 0xf4a04a8
	.long .Lname1193 /* index: 1193 */
	.weak json_writer_endarray; .long json_writer_endarray
	.reloc ., R_386_SIZE32, json_writer_endarray; .long 0
	.long 0xe60b4a9
	.long 0 /* index: 1194 */
	.long 0
	.long 0
	.long 0
	.long .Lname1195 /* index: 1195 */
	.weak inode_readallk; .long inode_readallk
	.reloc ., R_386_SIZE32, inode_readallk; .long 0
	.long 0xe20d4ab
	.long .Lname1196 /* index: 1196 */
	.weak rawmemlenl; .long rawmemlenl
	.reloc ., R_386_SIZE32, rawmemlenl; .long 0
	.long 0x3c5a4ac
	.long 0 /* index: 1197 */
	.long 0
	.long 0
	.long 0
	.long .Lname1198 /* index: 1198 */
	.weak page_malloc_between; .long page_malloc_between
	.reloc ., R_386_SIZE32, page_malloc_between; .long 0
	.long 0xabb34ae
	.long 0 /* index: 1199 */
	.long 0
	.long 0
	.long 0
	.long .Lname1200 /* index: 1200 */
	.weak devfs_lock_tryupgrade; .long devfs_lock_tryupgrade
	.reloc ., R_386_SIZE32, devfs_lock_tryupgrade; .long 0
	.long 0xa817635
	.long .Lname1201 /* index: 1201 */
	.weak rawmemlenq; .long rawmemlenq
	.reloc ., R_386_SIZE32, rawmemlenq; .long 0
	.long 0x3c5a4b1
	.long 0 /* index: 1202 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1203 */
	.long 0
	.long 0
	.long 0
	.long .Lname1204 /* index: 1204 */
	.weak character_device_read; .long character_device_read
	.reloc ., R_386_SIZE32, character_device_read; .long 0
	.long 0x98b84b4
	.long .Lname1205 /* index: 1205 */
	.weak regdump_kcpustate; .long regdump_kcpustate
	.reloc ., R_386_SIZE32, regdump_kcpustate; .long 0
	.long 0xbf454b5
	.long .Lname1206 /* index: 1206 */
	.weak sigqueue_fini; .long sigqueue_fini
	.reloc ., R_386_SIZE32, sigqueue_fini; .long 0
	.long 0x26b45f9
	.long .Lname1207 /* index: 1207 */
	.weak rawmemlenw; .long rawmemlenw
	.reloc ., R_386_SIZE32, rawmemlenw; .long 0
	.long 0x3c5a4b7
	.long .Lname1208 /* index: 1208 */
	.weak superblock_nodeslock_upgrade_nx; .long superblock_nodeslock_upgrade_nx
	.reloc ., R_386_SIZE32, superblock_nodeslock_upgrade_nx; .long 0
	.long 0xe6014b8
	.long .Lname1209 /* index: 1209 */
	.weak superblock_nodeslock_read; .long superblock_nodeslock_read
	.reloc ., R_386_SIZE32, superblock_nodeslock_read; .long 0
	.long 0x61aeb74
	.long 0 /* index: 1210 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1211 */
	.long 0
	.long 0
	.long 0
	.long .Lname1212 /* index: 1212 */
	.weak vm_tasklock_tryread; .long vm_tasklock_tryread
	.reloc ., R_386_SIZE32, vm_tasklock_tryread; .long 0
	.long 0x6c3c2e4
	.long 0 /* index: 1213 */
	.long 0
	.long 0
	.long 0
	.long .Lname1214 /* index: 1214 */
	.weak unicode_readutf8_rev_n; .long unicode_readutf8_rev_n
	.reloc ., R_386_SIZE32, unicode_readutf8_rev_n; .long 0
	.long 0xd4e74be
	.long 0 /* index: 1215 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1216 */
	.long 0
	.long 0
	.long 0
	.long .Lname1217 /* index: 1217 */
	.weak memendq; .long memendq
	.reloc ., R_386_SIZE32, memendq; .long 0
	.long 0x3c3c4c1
	.long 0 /* index: 1218 */
	.long 0
	.long 0
	.long 0
	.long .Lname1219 /* index: 1219 */
	.weak mzones; .long mzones
	.reloc ., R_386_SIZE32, mzones; .long 0
	.long 0x75164c3
	.long .Lname1220 /* index: 1220 */
	.weak sys_fchmod; .long sys_fchmod
	.reloc ., R_386_SIZE32, sys_fchmod; .long 0
	.long 0x5ce64c4
	.long .Lname1221 /* index: 1221 */
	.weak unwind_getreg_xfpustate; .long unwind_getreg_xfpustate
	.reloc ., R_386_SIZE32, unwind_getreg_xfpustate; .long 0
	.long 0xb8c44c5
	.long 0 /* index: 1222 */
	.long 0
	.long 0
	.long 0
	.long .Lname1223 /* index: 1223 */
	.weak memendw; .long memendw
	.reloc ., R_386_SIZE32, memendw; .long 0
	.long 0x3c3c4c7
	.long 0 /* index: 1224 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1225 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1226 */
	.long 0
	.long 0
	.long 0
	.long .Lname1227 /* index: 1227 */
	.weak regdump_sreg; .long regdump_sreg
	.reloc ., R_386_SIZE32, regdump_sreg; .long 0
	.long 0x3ed7377
	.long .Lname1228 /* index: 1228 */
	.weak __stack_chk_fail; .long __stack_chk_fail
	.reloc ., R_386_SIZE32, __stack_chk_fail; .long 0
	.long 0x595a4cc
	.long .Lname1229 /* index: 1229 */
	.weak block_device_aread_sector; .long block_device_aread_sector
	.reloc ., R_386_SIZE32, block_device_aread_sector; .long 0
	.long 0xea4622
	.long 0 /* index: 1230 */
	.long 0
	.long 0
	.long 0
	.long .Lname1231 /* index: 1231 */
	.weak minfo; .long minfo
	.reloc ., R_386_SIZE32, minfo; .long 0
	.long 0x7404cf
	.long 0 /* index: 1232 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1233 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1234 */
	.long 0
	.long 0
	.long 0
	.long .Lname1235 /* index: 1235 */
	.weak pty_slave_alloc; .long pty_slave_alloc
	.reloc ., R_386_SIZE32, pty_slave_alloc; .long 0
	.long 0x63e8e23
	.long .Lname1236 /* index: 1236 */
	.weak sys_getuid32; .long sys_getuid32
	.reloc ., R_386_SIZE32, sys_getuid32; .long 0
	.long 0xb0b62b2
	.long .Lname1237 /* index: 1237 */
	.weak fpustate_savecpu; .long fpustate_savecpu
	.reloc ., R_386_SIZE32, fpustate_savecpu; .long 0
	.long 0x322c4d5
	.long .Lname1238 /* index: 1238 */
	.weak vm_datapart_write_phys; .long vm_datapart_write_phys
	.reloc ., R_386_SIZE32, vm_datapart_write_phys; .long 0
	.long 0x99dd2d3
	.long .Lname1239 /* index: 1239 */
	.weak heap_free_untraced; .long heap_free_untraced
	.reloc ., R_386_SIZE32, heap_free_untraced; .long 0
	.long 0xed84944
	.long .Lname1240 /* index: 1240 */
	.weak task_yield_nx; .long task_yield_nx
	.reloc ., R_386_SIZE32, task_yield_nx; .long 0
	.long 0x54894d8
	.long .Lname1241 /* index: 1241 */
	.weak cpu_assert_integrity; .long cpu_assert_integrity
	.reloc ., R_386_SIZE32, cpu_assert_integrity; .long 0
	.long 0x19364d9
	.long 0 /* index: 1242 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1243 */
	.long 0
	.long 0
	.long 0
	.long .Lname1244 /* index: 1244 */
	.weak memendl; .long memendl
	.reloc ., R_386_SIZE32, memendl; .long 0
	.long 0x3c3c4dc
	.long .Lname1245 /* index: 1245 */
	.weak sys_mknodat; .long sys_mknodat
	.reloc ., R_386_SIZE32, sys_mknodat; .long 0
	.long 0x48053e4
	.long .Lname1246 /* index: 1246 */
	.weak vio_readl_aligned; .long vio_readl_aligned
	.reloc ., R_386_SIZE32, vio_readl_aligned; .long 0
	.long 0xe571f4
	.long .Lname1247 /* index: 1247 */
	.weak error_print_into; .long error_print_into
	.reloc ., R_386_SIZE32, error_print_into; .long 0
	.long 0x32554df
	.long 0 /* index: 1248 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1249 */
	.long 0
	.long 0
	.long 0
	.long .Lname1250 /* index: 1250 */
	.weak handle_fcntl; .long handle_fcntl
	.reloc ., R_386_SIZE32, handle_fcntl; .long 0
	.long 0xdb4ee8c
	.long 0 /* index: 1251 */
	.long 0
	.long 0
	.long 0
	.long .Lname1252 /* index: 1252 */
	.weak rwlock_pollread; .long rwlock_pollread
	.reloc ., R_386_SIZE32, rwlock_pollread; .long 0
	.long 0x78904e4
	.long 0 /* index: 1253 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1254 */
	.long 0
	.long 0
	.long 0
	.long .Lname1255 /* index: 1255 */
	.weak task_exec_asynchronous_rpc; .long task_exec_asynchronous_rpc
	.reloc ., R_386_SIZE32, task_exec_asynchronous_rpc; .long 0
	.long 0x1640cf3
	.long 0 /* index: 1256 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1257 */
	.long 0
	.long 0
	.long 0
	.long .Lname1258 /* index: 1258 */
	.weak pidns_endwrite; .long pidns_endwrite
	.reloc ., R_386_SIZE32, pidns_endwrite; .long 0
	.long 0xb0b2245
	.long 0 /* index: 1259 */
	.long 0
	.long 0
	.long 0
	.long .Lname1260 /* index: 1260 */
	.weak sys_signal; .long sys_signal
	.reloc ., R_386_SIZE32, sys_signal; .long 0
	.long 0x69874ec
	.long 0 /* index: 1261 */
	.long 0
	.long 0
	.long 0
	.long .Lname1262 /* index: 1262 */
	.weak sys_frealpathat; .long sys_frealpathat
	.reloc ., R_386_SIZE32, sys_frealpathat; .long 0
	.long 0xa355e04
	.long .Lname1263 /* index: 1263 */
	.weak pagedir_maphintone; .long pagedir_maphintone
	.reloc ., R_386_SIZE32, pagedir_maphintone; .long 0
	.long 0x9e65795
	.long 0 /* index: 1264 */
	.long 0
	.long 0
	.long 0
	.long .Lname1265 /* index: 1265 */
	.weak unwind_cfa_calculate_cfa; .long unwind_cfa_calculate_cfa
	.reloc ., R_386_SIZE32, unwind_cfa_calculate_cfa; .long 0
	.long 0xe55d4f1
	.long .Lname1266 /* index: 1266 */
	.weak handle_get_driver; .long handle_get_driver
	.reloc ., R_386_SIZE32, handle_get_driver; .long 0
	.long 0x76454f2
	.long .Lname1267 /* index: 1267 */
	.weak handle_get_pidns; .long handle_get_pidns
	.reloc ., R_386_SIZE32, handle_get_pidns; .long 0
	.long 0x34b50d3
	.long .Lname1268 /* index: 1268 */
	.weak path_mount; .long path_mount
	.reloc ., R_386_SIZE32, path_mount; .long 0
	.long 0xe6504f4
	.long .Lname1269 /* index: 1269 */
	.weak kernel_uname; .long kernel_uname
	.reloc ., R_386_SIZE32, kernel_uname; .long 0
	.long 0x778d4f5
	.long .Lname1270 /* index: 1270 */
	.weak debuginfo_location_select; .long debuginfo_location_select
	.reloc ., R_386_SIZE32, debuginfo_location_select; .long 0
	.long 0x19e2d74
	.long 0 /* index: 1271 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1272 */
	.long 0
	.long 0
	.long 0
	.long .Lname1273 /* index: 1273 */
	.weak path_traversefull_at; .long path_traversefull_at
	.reloc ., R_386_SIZE32, path_traversefull_at; .long 0
	.long 0xde1f0d4
	.long 0 /* index: 1274 */
	.long 0
	.long 0
	.long 0
	.long .Lname1275 /* index: 1275 */
	.weak vm_tasklock_write; .long vm_tasklock_write
	.reloc ., R_386_SIZE32, vm_tasklock_write; .long 0
	.long 0x993b3e5
	.long 0 /* index: 1276 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1277 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1278 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1279 */
	.long 0
	.long 0
	.long 0
	.long .Lname1280 /* index: 1280 */
	.weak vm_datapart_freeswap; .long vm_datapart_freeswap
	.reloc ., R_386_SIZE32, vm_datapart_freeswap; .long 0
	.long 0xd6f8500
	.long 0 /* index: 1281 */
	.long 0
	.long 0
	.long 0
	.long .Lname1282 /* index: 1282 */
	.weak sys_lfutexexpr; .long sys_lfutexexpr
	.reloc ., R_386_SIZE32, sys_lfutexexpr; .long 0
	.long 0xa58e502
	.long 0 /* index: 1283 */
	.long 0
	.long 0
	.long 0
	.long .Lname1284 /* index: 1284 */
	.weak path_freelist; .long path_freelist
	.reloc ., R_386_SIZE32, path_freelist; .long 0
	.long 0xe32d504
	.long .Lname1285 /* index: 1285 */
	.weak page_ccfree; .long page_ccfree
	.reloc ., R_386_SIZE32, page_ccfree; .long 0
	.long 0x5efa505
	.long 0 /* index: 1286 */
	.long 0
	.long 0
	.long 0
	.long .Lname1287 /* index: 1287 */
	.weak sys_epoll_create1; .long sys_epoll_create1
	.reloc ., R_386_SIZE32, sys_epoll_create1; .long 0
	.long 0x6a4b381
	.long .Lname1288 /* index: 1288 */
	.weak heap_alloc_untraced_nx; .long heap_alloc_untraced_nx
	.reloc ., R_386_SIZE32, heap_alloc_untraced_nx; .long 0
	.long 0x8a12508
	.long 0 /* index: 1289 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1290 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1291 */
	.long 0
	.long 0
	.long 0
	.long .Lname1292 /* index: 1292 */
	.weak heap_validate; .long heap_validate
	.reloc ., R_386_SIZE32, heap_validate; .long 0
	.long 0xa97ce05
	.long 0 /* index: 1293 */
	.long 0
	.long 0
	.long 0
	.long .Lname1294 /* index: 1294 */
	.weak sys_sigreturn; .long sys_sigreturn
	.reloc ., R_386_SIZE32, sys_sigreturn; .long 0
	.long 0x585d50e
	.long 0 /* index: 1295 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1296 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1297 */
	.long 0
	.long 0
	.long 0
	.long .Lname1298 /* index: 1298 */
	.weak vm_write_nopf; .long vm_write_nopf
	.reloc ., R_386_SIZE32, vm_write_nopf; .long 0
	.long 0x7a4bf16
	.long .Lname1299 /* index: 1299 */
	.weak vm_node_update_write_access; .long vm_node_update_write_access
	.reloc ., R_386_SIZE32, vm_node_update_write_access; .long 0
	.long 0x9a1c513
	.long .Lname1300 /* index: 1300 */
	.weak task_setthread; .long task_setthread
	.reloc ., R_386_SIZE32, task_setthread; .long 0
	.long 0x30ee514
	.long 0 /* index: 1301 */
	.long 0
	.long 0
	.long 0
	.long .Lname1302 /* index: 1302 */
	.weak format_vprintf; .long format_vprintf
	.reloc ., R_386_SIZE32, format_vprintf; .long 0
	.long 0xbeb7516
	.long 0 /* index: 1303 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1304 */
	.long 0
	.long 0
	.long 0
	.long .Lname1305 /* index: 1305 */
	.weak rwlock_tryread; .long rwlock_tryread
	.reloc ., R_386_SIZE32, rwlock_tryread; .long 0
	.long 0x5b52384
	.long 0 /* index: 1306 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1307 */
	.long 0
	.long 0
	.long 0
	.long .Lname1308 /* index: 1308 */
	.weak driver_local_symbol; .long driver_local_symbol
	.reloc ., R_386_SIZE32, driver_local_symbol; .long 0
	.long 0x96b651c
	.long 0 /* index: 1309 */
	.long 0
	.long 0
	.long 0
	.long .Lname1310 /* index: 1310 */
	.weak vm_datapart_do_write_phys; .long vm_datapart_do_write_phys
	.reloc ., R_386_SIZE32, vm_datapart_do_write_phys; .long 0
	.long 0xa9db593
	.long .Lname1311 /* index: 1311 */
	.weak kernel_panic_here; .long kernel_panic_here
	.reloc ., R_386_SIZE32, kernel_panic_here; .long 0
	.long 0x4024385
	.long 0 /* index: 1312 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1313 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1314 */
	.long 0
	.long 0
	.long 0
	.long .Lname1315 /* index: 1315 */
	.weak aio_multihandle_allochandle; .long aio_multihandle_allochandle
	.reloc ., R_386_SIZE32, aio_multihandle_allochandle; .long 0
	.long 0x834dcf5
	.long .Lname1316 /* index: 1316 */
	.weak cred_require_vmread; .long cred_require_vmread
	.reloc ., R_386_SIZE32, cred_require_vmread; .long 0
	.long 0xd52524
	.long .Lname1317 /* index: 1317 */
	.weak block_device_write; .long block_device_write
	.reloc ., R_386_SIZE32, block_device_write; .long 0
	.long 0xa512525
	.long .Lname1318 /* index: 1318 */
	.weak inode_pathconf; .long inode_pathconf
	.reloc ., R_386_SIZE32, inode_pathconf; .long 0
	.long 0xdf43526
	.long 0 /* index: 1319 */
	.long 0
	.long 0
	.long 0
	.long .Lname1320 /* index: 1320 */
	.weak task_raisesignalprocessgroup_nx; .long task_raisesignalprocessgroup_nx
	.reloc ., R_386_SIZE32, task_raisesignalprocessgroup_nx; .long 0
	.long 0xa352528
	.long 0 /* index: 1321 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1322 */
	.long 0
	.long 0
	.long 0
	.long .Lname1323 /* index: 1323 */
	.weak memrendw; .long memrendw
	.reloc ., R_386_SIZE32, memrendw; .long 0
	.long 0xc48c387
	.long .Lname1324 /* index: 1324 */
	.weak sys_tkill; .long sys_tkill
	.reloc ., R_386_SIZE32, sys_tkill; .long 0
	.long 0x96b652c
	.long .Lname1325 /* index: 1325 */
	.weak vio_xchb; .long vio_xchb
	.reloc ., R_386_SIZE32, vio_xchb; .long 0
	.long 0x56ee32
	.long .Lname1326 /* index: 1326 */
	.weak cpu_addsleepingtask; .long cpu_addsleepingtask
	.reloc ., R_386_SIZE32, cpu_addsleepingtask; .long 0
	.long 0xfb7433b
	.long 0 /* index: 1327 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1328 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1329 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1330 */
	.long 0
	.long 0
	.long 0
	.long .Lname1331 /* index: 1331 */
	.weak fs_filesystems_delblocks; .long fs_filesystems_delblocks
	.reloc ., R_386_SIZE32, fs_filesystems_delblocks; .long 0
	.long 0x2f05533
	.long .Lname1332 /* index: 1332 */
	.weak terminal_init; .long terminal_init
	.reloc ., R_386_SIZE32, terminal_init; .long 0
	.long 0xeecc534
	.long .Lname1333 /* index: 1333 */
	.weak sys_stime; .long sys_stime
	.reloc ., R_386_SIZE32, sys_stime; .long 0
	.long 0x96ad535
	.long .Lname1334 /* index: 1334 */
	.weak vm_memset_nopf; .long vm_memset_nopf
	.reloc ., R_386_SIZE32, vm_memset_nopf; .long 0
	.long 0x79536
	.long 0 /* index: 1335 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1336 */
	.long 0
	.long 0
	.long 0
	.long .Lname1337 /* index: 1337 */
	.weak pagedir_unsetchanged; .long pagedir_unsetchanged
	.reloc ., R_386_SIZE32, pagedir_unsetchanged; .long 0
	.long 0x89a6634
	.long 0 /* index: 1338 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1339 */
	.long 0
	.long 0
	.long 0
	.long .Lname1340 /* index: 1340 */
	.weak vm_find_first_node_greater_equal; .long vm_find_first_node_greater_equal
	.reloc ., R_386_SIZE32, vm_find_first_node_greater_equal; .long 0
	.long 0xe2f353c
	.long 0 /* index: 1341 */
	.long 0
	.long 0
	.long 0
	.long .Lname1342 /* index: 1342 */
	.weak cpu_schedule_idle_job_simple; .long cpu_schedule_idle_job_simple
	.reloc ., R_386_SIZE32, cpu_schedule_idle_job_simple; .long 0
	.long 0xabc61f5
	.long .Lname1343 /* index: 1343 */
	.weak cpu_quantum_time; .long cpu_quantum_time
	.reloc ., R_386_SIZE32, cpu_quantum_time; .long 0
	.long 0xebb4e35
	.long 0 /* index: 1344 */
	.long 0
	.long 0
	.long 0
	.long .Lname1345 /* index: 1345 */
	.weak strnlen; .long strnlen
	.reloc ., R_386_SIZE32, strnlen; .long 0
	.long 0xab952ce
	.long .Lname1346 /* index: 1346 */
	.weak json_parser_enter; .long json_parser_enter
	.reloc ., R_386_SIZE32, json_parser_enter; .long 0
	.long 0x2436542
	.long .Lname1347 /* index: 1347 */
	.weak sys_msync; .long sys_msync
	.reloc ., R_386_SIZE32, sys_msync; .long 0
	.long 0x964d543
	.long .Lname1348 /* index: 1348 */
	.weak character_device_stat; .long character_device_stat
	.reloc ., R_386_SIZE32, character_device_stat; .long 0
	.long 0x98ba544
	.long .Lname1349 /* index: 1349 */
	.weak block_device_acquire_partlock_trywrite; .long block_device_acquire_partlock_trywrite
	.reloc ., R_386_SIZE32, block_device_acquire_partlock_trywrite; .long 0
	.long 0xc0d6545
	.long 0 /* index: 1350 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1351 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1352 */
	.long 0
	.long 0
	.long 0
	.long .Lname1353 /* index: 1353 */
	.weak driver_getshdrs; .long driver_getshdrs
	.reloc ., R_386_SIZE32, driver_getshdrs; .long 0
	.long 0xc75c5d3
	.long 0 /* index: 1354 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1355 */
	.long 0
	.long 0
	.long 0
	.long .Lname1356 /* index: 1356 */
	.weak vm_sync_endall; .long vm_sync_endall
	.reloc ., R_386_SIZE32, vm_sync_endall; .long 0
	.long 0x6efa54c
	.long .Lname1357 /* index: 1357 */
	.weak cpu_quantum_reset_nopr; .long cpu_quantum_reset_nopr
	.reloc ., R_386_SIZE32, cpu_quantum_reset_nopr; .long 0
	.long 0x23f38e2
	.long 0 /* index: 1358 */
	.long 0
	.long 0
	.long 0
	.long .Lname1359 /* index: 1359 */
	.weak validate_writablem; .long validate_writablem
	.reloc ., R_386_SIZE32, validate_writablem; .long 0
	.long 0xfc4d38d
	.long .Lname1360 /* index: 1360 */
	.weak kernel_locked_heap; .long kernel_locked_heap
	.reloc ., R_386_SIZE32, kernel_locked_heap; .long 0
	.long 0xcda2550
	.long .Lname1361 /* index: 1361 */
	.weak vm_datapart_allocram_nx; .long vm_datapart_allocram_nx
	.reloc ., R_386_SIZE32, vm_datapart_allocram_nx; .long 0
	.long 0x805c638
	.long .Lname1362 /* index: 1362 */
	.weak _this_sighand_ptr; .long _this_sighand_ptr
	.reloc ., R_386_SIZE32, _this_sighand_ptr; .long 0
	.long 0xf473552
	.long .Lname1363 /* index: 1363 */
	.weak directory_entry_alloc; .long directory_entry_alloc
	.reloc ., R_386_SIZE32, directory_entry_alloc; .long 0
	.long 0xab6b553
	.long .Lname1364 /* index: 1364 */
	.weak sys_utimensat; .long sys_utimensat
	.reloc ., R_386_SIZE32, sys_utimensat; .long 0
	.long 0x5333554
	.long .Lname1365 /* index: 1365 */
	.weak keymap_codesize; .long keymap_codesize
	.reloc ., R_386_SIZE32, keymap_codesize; .long 0
	.long 0x594b555
	.long 0 /* index: 1366 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1367 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1368 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1369 */
	.long 0
	.long 0
	.long 0
	.long .Lname1370 /* index: 1370 */
	.weak sys_timer_settime; .long sys_timer_settime
	.reloc ., R_386_SIZE32, sys_timer_settime; .long 0
	.long 0x3536135
	.long .Lname1371 /* index: 1371 */
	.weak kernel_debugtrap_scpustate; .long kernel_debugtrap_scpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_scpustate; .long 0
	.long 0x963b8f5
	.long 0 /* index: 1372 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1373 */
	.long 0
	.long 0
	.long 0
	.long .Lname1374 /* index: 1374 */
	.weak path_traversen; .long path_traversen
	.reloc ., R_386_SIZE32, path_traversen; .long 0
	.long 0x62f55e
	.long 0 /* index: 1375 */
	.long 0
	.long 0
	.long 0
	.long .Lname1376 /* index: 1376 */
	.weak unicode_readutf16_swap; .long unicode_readutf16_swap
	.reloc ., R_386_SIZE32, unicode_readutf16_swap; .long 0
	.long 0x5a01560
	.long 0 /* index: 1377 */
	.long 0
	.long 0
	.long 0
	.long .Lname1378 /* index: 1378 */
	.weak sys_freadlinkat; .long sys_freadlinkat
	.reloc ., R_386_SIZE32, sys_freadlinkat; .long 0
	.long 0x473c1f4
	.long 0 /* index: 1379 */
	.long 0
	.long 0
	.long 0
	.long .Lname1380 /* index: 1380 */
	.weak pagedir_ismapped; .long pagedir_ismapped
	.reloc ., R_386_SIZE32, pagedir_ismapped; .long 0
	.long 0x38f5564
	.long .Lname1381 /* index: 1381 */
	.weak vm_tasklock_upgrade; .long vm_tasklock_upgrade
	.reloc ., R_386_SIZE32, vm_tasklock_upgrade; .long 0
	.long 0x14dce35
	.long 0 /* index: 1382 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1383 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1384 */
	.long 0
	.long 0
	.long 0
	.long .Lname1385 /* index: 1385 */
	.weak pagedir_syncall; .long pagedir_syncall
	.reloc ., R_386_SIZE32, pagedir_syncall; .long 0
	.long 0x75fe63c
	.long .Lname1386 /* index: 1386 */
	.weak disasm_default_maxbytes; .long disasm_default_maxbytes
	.reloc ., R_386_SIZE32, disasm_default_maxbytes; .long 0
	.long 0xa1542b3
	.long 0 /* index: 1387 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1388 */
	.long 0
	.long 0
	.long 0
	.long .Lname1389 /* index: 1389 */
	.weak sys_fchdir; .long sys_fchdir
	.reloc ., R_386_SIZE32, sys_fchdir; .long 0
	.long 0x5ce5b92
	.long 0 /* index: 1390 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1391 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1392 */
	.long 0
	.long 0
	.long 0
	.long .Lname1393 /* index: 1393 */
	.weak vpage_alloc_nx; .long vpage_alloc_nx
	.reloc ., R_386_SIZE32, vpage_alloc_nx; .long 0
	.long 0x56848e8
	.long 0 /* index: 1394 */
	.long 0
	.long 0
	.long 0
	.long .Lname1395 /* index: 1395 */
	.weak vm_datapart_writev_phys; .long vm_datapart_writev_phys
	.reloc ., R_386_SIZE32, vm_datapart_writev_phys; .long 0
	.long 0xe1d8393
	.long 0 /* index: 1396 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1397 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1398 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1399 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1400 */
	.long 0
	.long 0
	.long 0
	.long .Lname1401 /* index: 1401 */
	.weak vm_syncone_locked; .long vm_syncone_locked
	.reloc ., R_386_SIZE32, vm_syncone_locked; .long 0
	.long 0x620f394
	.long 0 /* index: 1402 */
	.long 0
	.long 0
	.long 0
	.long .Lname1403 /* index: 1403 */
	.weak mouse_device_moveto; .long mouse_device_moveto
	.reloc ., R_386_SIZE32, mouse_device_moveto; .long 0
	.long 0xca6ae3f
	.long .Lname1404 /* index: 1404 */
	.weak driver_symbol; .long driver_symbol
	.reloc ., R_386_SIZE32, driver_symbol; .long 0
	.long 0xd40f57c
	.long 0 /* index: 1405 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1406 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1407 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1408 */
	.long 0
	.long 0
	.long 0
	.long .Lname1409 /* index: 1409 */
	.weak unwind_setreg_lcpustate; .long unwind_setreg_lcpustate
	.reloc ., R_386_SIZE32, unwind_setreg_lcpustate; .long 0
	.long 0xb8d08b5
	.long 0 /* index: 1410 */
	.long 0
	.long 0
	.long 0
	.long .Lname1411 /* index: 1411 */
	.weak fs_alloc; .long fs_alloc
	.reloc ., R_386_SIZE32, fs_alloc; .long 0
	.long 0x9583583
	.long .Lname1412 /* index: 1412 */
	.weak devfs_lock_tryread; .long devfs_lock_tryread
	.reloc ., R_386_SIZE32, devfs_lock_tryread; .long 0
	.long 0xf19e584
	.long .Lname1413 /* index: 1413 */
	.weak superblock_mountlock_tryservice; .long superblock_mountlock_tryservice
	.reloc ., R_386_SIZE32, superblock_mountlock_tryservice; .long 0
	.long 0xefae585
	.long 0 /* index: 1414 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1415 */
	.long 0
	.long 0
	.long 0
	.long .Lname1416 /* index: 1416 */
	.weak __cxa_end_catch; .long __cxa_end_catch
	.reloc ., R_386_SIZE32, __cxa_end_catch; .long 0
	.long 0x4beb588
	.long 0 /* index: 1417 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1418 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1419 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1420 */
	.long 0
	.long 0
	.long 0
	.long .Lname1421 /* index: 1421 */
	.weak path_traversenfull_at; .long path_traversenfull_at
	.reloc ., R_386_SIZE32, path_traversenfull_at; .long 0
	.long 0xbae53c4
	.long 0 /* index: 1422 */
	.long 0
	.long 0
	.long 0
	.long .Lname1423 /* index: 1423 */
	.weak sys_rt_sigqueueinfo; .long sys_rt_sigqueueinfo
	.reloc ., R_386_SIZE32, sys_rt_sigqueueinfo; .long 0
	.long 0x12d858f
	.long 0 /* index: 1424 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1425 */
	.long 0
	.long 0
	.long 0
	.long .Lname1426 /* index: 1426 */
	.weak vm_datapart_write_buffered; .long vm_datapart_write_buffered
	.reloc ., R_386_SIZE32, vm_datapart_write_buffered; .long 0
	.long 0x5155694
	.long .Lname1427 /* index: 1427 */
	.weak vm_datapart_do_read_phys; .long vm_datapart_do_read_phys
	.reloc ., R_386_SIZE32, vm_datapart_do_read_phys; .long 0
	.long 0xea4d593
	.long .Lname1428 /* index: 1428 */
	.weak acpi_sdt_count; .long acpi_sdt_count
	.reloc ., R_386_SIZE32, acpi_sdt_count; .long 0
	.long 0x4370594
	.long .Lname1429 /* index: 1429 */
	.weak superblock_nodeslock_tryservice; .long superblock_nodeslock_tryservice
	.reloc ., R_386_SIZE32, superblock_nodeslock_tryservice; .long 0
	.long 0xfd31595
	.long .Lname1430 /* index: 1430 */
	.weak keyboard_device_getkey; .long keyboard_device_getkey
	.reloc ., R_386_SIZE32, keyboard_device_getkey; .long 0
	.long 0x64fded9
	.long .Lname1431 /* index: 1431 */
	.weak pipe_writer_destroy; .long pipe_writer_destroy
	.reloc ., R_386_SIZE32, pipe_writer_destroy; .long 0
	.long 0xac6cb99
	.long .Lname1432 /* index: 1432 */
	.weak vpage_realloc_untraced_nx; .long vpage_realloc_untraced_nx
	.reloc ., R_386_SIZE32, vpage_realloc_untraced_nx; .long 0
	.long 0x921d598
	.long 0 /* index: 1433 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1434 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1435 */
	.long 0
	.long 0
	.long 0
	.long .Lname1436 /* index: 1436 */
	.weak inode_readv_blocking; .long inode_readv_blocking
	.reloc ., R_386_SIZE32, inode_readv_blocking; .long 0
	.long 0xd790c57
	.long 0 /* index: 1437 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1438 */
	.long 0
	.long 0
	.long 0
	.long .Lname1439 /* index: 1439 */
	.weak terminal_iwrite; .long terminal_iwrite
	.reloc ., R_386_SIZE32, terminal_iwrite; .long 0
	.long 0xd4ece45
	.long 0 /* index: 1440 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1441 */
	.long 0
	.long 0
	.long 0
	.long .Lname1442 /* index: 1442 */
	.weak json_writer_putnumber; .long json_writer_putnumber
	.reloc ., R_386_SIZE32, json_writer_putnumber; .long 0
	.long 0x7dac5a2
	.long .Lname1443 /* index: 1443 */
	.weak sys_umask; .long sys_umask
	.reloc ., R_386_SIZE32, sys_umask; .long 0
	.long 0x96c439b
	.long .Lname1444 /* index: 1444 */
	.weak json_parser_yield; .long json_parser_yield
	.reloc ., R_386_SIZE32, json_parser_yield; .long 0
	.long 0x276c5a4
	.long .Lname1445 /* index: 1445 */
	.weak cred_require_vmwrite; .long cred_require_vmwrite
	.reloc ., R_386_SIZE32, cred_require_vmwrite; .long 0
	.long 0xd5475a5
	.long .Lname1446 /* index: 1446 */
	.weak sys_writevf; .long sys_writevf
	.reloc ., R_386_SIZE32, sys_writevf; .long 0
	.long 0xf0ba5a6
	.long .Lname1447 /* index: 1447 */
	.weak unwind_fde_exec_cfa; .long unwind_fde_exec_cfa
	.reloc ., R_386_SIZE32, unwind_fde_exec_cfa; .long 0
	.long 0x72de8f1
	.long .Lname1448 /* index: 1448 */
	.weak path_traverse_ex; .long path_traverse_ex
	.reloc ., R_386_SIZE32, path_traverse_ex; .long 0
	.long 0x2f555a8
	.long .Lname1449 /* index: 1449 */
	.weak pagedir_kernel; .long pagedir_kernel
	.reloc ., R_386_SIZE32, pagedir_kernel; .long 0
	.long 0x3c7439c
	.long .Lname1450 /* index: 1450 */
	.weak task_exit; .long task_exit
	.reloc ., R_386_SIZE32, task_exit; .long 0
	.long 0xa15b584
	.long .Lname1451 /* index: 1451 */
	.weak printk; .long printk
	.reloc ., R_386_SIZE32, printk; .long 0
	.long 0x77905ab
	.long 0 /* index: 1452 */
	.long 0
	.long 0
	.long 0
	.long .Lname1453 /* index: 1453 */
	.weak validate_readablem; .long validate_readablem
	.reloc ., R_386_SIZE32, validate_readablem; .long 0
	.long 0x8c4d5ad
	.long 0 /* index: 1454 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1455 */
	.long 0
	.long 0
	.long 0
	.long .Lname1456 /* index: 1456 */
	.weak vm_datapart_map_ram_p; .long vm_datapart_map_ram_p
	.reloc ., R_386_SIZE32, vm_datapart_map_ram_p; .long 0
	.long 0x95af5b0
	.long 0 /* index: 1457 */
	.long 0
	.long 0
	.long 0
	.long .Lname1458 /* index: 1458 */
	.weak pci_writeaddr; .long pci_writeaddr
	.reloc ., R_386_SIZE32, pci_writeaddr; .long 0
	.long 0x63415b2
	.long 0 /* index: 1459 */
	.long 0
	.long 0
	.long 0
	.long .Lname1460 /* index: 1460 */
	.weak ansitty_init; .long ansitty_init
	.reloc ., R_386_SIZE32, ansitty_init; .long 0
	.long 0xd7065b4
	.long .Lname1461 /* index: 1461 */
	.weak unwind_getreg_icpustate; .long unwind_getreg_icpustate
	.reloc ., R_386_SIZE32, unwind_getreg_icpustate; .long 0
	.long 0xb8c75b5
	.long 0 /* index: 1462 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1463 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1464 */
	.long 0
	.long 0
	.long 0
	.long .Lname1465 /* index: 1465 */
	.weak json_writer_addfield; .long json_writer_addfield
	.reloc ., R_386_SIZE32, json_writer_addfield; .long 0
	.long 0x64d8f4
	.long 0 /* index: 1466 */
	.long 0
	.long 0
	.long 0
	.long .Lname1467 /* index: 1467 */
	.weak userkern_segment_vio; .long userkern_segment_vio
	.reloc ., R_386_SIZE32, userkern_segment_vio; .long 0
	.long 0x1facb9f
	.long 0 /* index: 1468 */
	.long 0
	.long 0
	.long 0
	.long .Lname1469 /* index: 1469 */
	.weak rwlock_writing; .long rwlock_writing
	.reloc ., R_386_SIZE32, rwlock_writing; .long 0
	.long 0xc508b7
	.long 0 /* index: 1470 */
	.long 0
	.long 0
	.long 0
	.long .Lname1471 /* index: 1471 */
	.weak kernel_debugtrap_kcpustate; .long kernel_debugtrap_kcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_kcpustate; .long 0
	.long 0x96390f5
	.long 0 /* index: 1472 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1473 */
	.long 0
	.long 0
	.long 0
	.long .Lname1474 /* index: 1474 */
	.weak mouse_buffer_putpacket_nopr; .long mouse_buffer_putpacket_nopr
	.reloc ., R_386_SIZE32, mouse_buffer_putpacket_nopr; .long 0
	.long 0x8565c2
	.long .Lname1475 /* index: 1475 */
	.weak sys_setgroups; .long sys_setgroups
	.reloc ., R_386_SIZE32, sys_setgroups; .long 0
	.long 0x1e205c3
	.long 0 /* index: 1476 */
	.long 0
	.long 0
	.long 0
	.long .Lname1477 /* index: 1477 */
	.weak pagedir_unmapone; .long pagedir_unmapone
	.reloc ., R_386_SIZE32, pagedir_unmapone; .long 0
	.long 0x8f55c5
	.long 0 /* index: 1478 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1479 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1480 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1481 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1482 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1483 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1484 */
	.long 0
	.long 0
	.long 0
	.long .Lname1485 /* index: 1485 */
	.weak cpu_disable_preemptive_interrupts_nopr; .long cpu_disable_preemptive_interrupts_nopr
	.reloc ., R_386_SIZE32, cpu_disable_preemptive_interrupts_nopr; .long 0
	.long 0x985f3a2
	.long 0 /* index: 1486 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1487 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1488 */
	.long 0
	.long 0
	.long 0
	.long .Lname1489 /* index: 1489 */
	.weak directory_entry_hash; .long directory_entry_hash
	.reloc ., R_386_SIZE32, directory_entry_hash; .long 0
	.long 0xabc0f8
	.long .Lname1490 /* index: 1490 */
	.weak inode_recent_tryclear; .long inode_recent_tryclear
	.reloc ., R_386_SIZE32, inode_recent_tryclear; .long 0
	.long 0x5d8b5d2
	.long .Lname1491 /* index: 1491 */
	.weak handle_manager_cloexec; .long handle_manager_cloexec
	.reloc ., R_386_SIZE32, handle_manager_cloexec; .long 0
	.long 0x785c3a3
	.long 0 /* index: 1492 */
	.long 0
	.long 0
	.long 0
	.long .Lname1493 /* index: 1493 */
	.weak driver_delmod_inode; .long driver_delmod_inode
	.reloc ., R_386_SIZE32, driver_delmod_inode; .long 0
	.long 0x86355d5
	.long .Lname1494 /* index: 1494 */
	.weak format_scanf; .long format_scanf
	.reloc ., R_386_SIZE32, format_scanf; .long 0
	.long 0xbf05d6
	.long .Lname1495 /* index: 1495 */
	.weak sys_gettimeofday; .long sys_gettimeofday
	.reloc ., R_386_SIZE32, sys_gettimeofday; .long 0
	.long 0x67ec0f9
	.long .Lname1496 /* index: 1496 */
	.weak pidns_write_nx; .long pidns_write_nx
	.reloc ., R_386_SIZE32, pidns_write_nx; .long 0
	.long 0x8bf45d8
	.long .Lname1497 /* index: 1497 */
	.weak cpu_online_count; .long cpu_online_count
	.reloc ., R_386_SIZE32, cpu_online_count; .long 0
	.long 0xd3be3a4
	.long .Lname1498 /* index: 1498 */
	.weak sys_hop; .long sys_hop
	.reloc ., R_386_SIZE32, sys_hop; .long 0
	.long 0xb095f10
	.long .Lname1499 /* index: 1499 */
	.weak vprintk; .long vprintk
	.reloc ., R_386_SIZE32, vprintk; .long 0
	.long 0xd7905db
	.long .Lname1500 /* index: 1500 */
	.weak vm_datablock_physical; .long vm_datablock_physical
	.reloc ., R_386_SIZE32, vm_datablock_physical; .long 0
	.long 0x8fb15dc
	.long 0 /* index: 1501 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1502 */
	.long 0
	.long 0
	.long 0
	.long .Lname1503 /* index: 1503 */
	.weak inode_recent_tryremove; .long inode_recent_tryremove
	.reloc ., R_386_SIZE32, inode_recent_tryremove; .long 0
	.long 0x263e3a5
	.long .Lname1504 /* index: 1504 */
	.weak sys_clock_nanosleep; .long sys_clock_nanosleep
	.reloc ., R_386_SIZE32, sys_clock_nanosleep; .long 0
	.long 0xbc435e0
	.long 0 /* index: 1505 */
	.long 0
	.long 0
	.long 0
	.long .Lname1506 /* index: 1506 */
	.weak block_device_aread_phys_sector; .long block_device_aread_phys_sector
	.reloc ., R_386_SIZE32, block_device_aread_phys_sector; .long 0
	.long 0x29a55e2
	.long 0 /* index: 1507 */
	.long 0
	.long 0
	.long 0
	.long .Lname1508 /* index: 1508 */
	.weak path_traverse_at; .long path_traverse_at
	.reloc ., R_386_SIZE32, path_traverse_at; .long 0
	.long 0x2f555e4
	.long 0 /* index: 1509 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1510 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1511 */
	.long 0
	.long 0
	.long 0
	.long .Lname1512 /* index: 1512 */
	.weak dbg_enter_kcpustate; .long dbg_enter_kcpustate
	.reloc ., R_386_SIZE32, dbg_enter_kcpustate; .long 0
	.long 0x781b535
	.long .Lname1513 /* index: 1513 */
	.weak directory_getentry; .long directory_getentry
	.reloc ., R_386_SIZE32, directory_getentry; .long 0
	.long 0x17325e9
	.long .Lname1514 /* index: 1514 */
	.weak debuginfo_location_getvalue; .long debuginfo_location_getvalue
	.reloc ., R_386_SIZE32, debuginfo_location_getvalue; .long 0
	.long 0xabab165
	.long 0 /* index: 1515 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1516 */
	.long 0
	.long 0
	.long 0
	.long .Lname1517 /* index: 1517 */
	.weak driver_insmod_blob; .long driver_insmod_blob
	.reloc ., R_386_SIZE32, driver_insmod_blob; .long 0
	.long 0x782e652
	.long 0 /* index: 1518 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1519 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1520 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1521 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1522 */
	.long 0
	.long 0
	.long 0
	.long .Lname1523 /* index: 1523 */
	.weak task_schedule_synchronous_rpc; .long task_schedule_synchronous_rpc
	.reloc ., R_386_SIZE32, task_schedule_synchronous_rpc; .long 0
	.long 0xc9ef653
	.long .Lname1524 /* index: 1524 */
	.weak vm_datablock_locatepart; .long vm_datablock_locatepart
	.reloc ., R_386_SIZE32, vm_datablock_locatepart; .long 0
	.long 0xa5c95f4
	.long .Lname1525 /* index: 1525 */
	.weak mall_untrace; .long mall_untrace
	.reloc ., R_386_SIZE32, mall_untrace; .long 0
	.long 0xd63b5f5
	.long 0 /* index: 1526 */
	.long 0
	.long 0
	.long 0
	.long .Lname1527 /* index: 1527 */
	.weak debuginfo_cu_parser_getstring; .long debuginfo_cu_parser_getstring
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getstring; .long 0
	.long 0x54b35f7
	.long .Lname1528 /* index: 1528 */
	.weak superblock_nodeslock_read_nx; .long superblock_nodeslock_read_nx
	.reloc ., R_386_SIZE32, superblock_nodeslock_read_nx; .long 0
	.long 0xeb805f8
	.long .Lname1529 /* index: 1529 */
	.weak pagedir_fini; .long pagedir_fini
	.reloc ., R_386_SIZE32, pagedir_fini; .long 0
	.long 0x72215f9
	.long 0 /* index: 1530 */
	.long 0
	.long 0
	.long 0
	.long .Lname1531 /* index: 1531 */
	.weak block_device_writev_sync; .long block_device_writev_sync
	.reloc ., R_386_SIZE32, block_device_writev_sync; .long 0
	.long 0x6f78b63
	.long .Lname1532 /* index: 1532 */
	.weak x86_pagedir_syncall_maybe_global; .long x86_pagedir_syncall_maybe_global
	.reloc ., R_386_SIZE32, x86_pagedir_syncall_maybe_global; .long 0
	.long 0x3e6c5fc
	.long 0 /* index: 1533 */
	.long 0
	.long 0
	.long 0
	.long .Lname1534 /* index: 1534 */
	.weak x86_memcpy_nopf_ret_pointer; .long x86_memcpy_nopf_ret_pointer
	.reloc ., R_386_SIZE32, x86_memcpy_nopf_ret_pointer; .long 0
	.long 0x8a132d2
	.long .Lname1535 /* index: 1535 */
	.weak vm_datapart_loadpage; .long vm_datapart_loadpage
	.reloc ., R_386_SIZE32, vm_datapart_loadpage; .long 0
	.long 0xa84e55
	.long .Lname1536 /* index: 1536 */
	.weak cred_require_mount; .long cred_require_mount
	.reloc ., R_386_SIZE32, cred_require_mount; .long 0
	.long 0x54472b4
	.long .Lname1537 /* index: 1537 */
	.weak x86_pagedir_sync; .long x86_pagedir_sync
	.reloc ., R_386_SIZE32, x86_pagedir_sync; .long 0
	.long 0x626d033
	.long 0 /* index: 1538 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1539 */
	.long 0
	.long 0
	.long 0
	.long .Lname1540 /* index: 1540 */
	.weak pidns_trylookup_task_locked; .long pidns_trylookup_task_locked
	.reloc ., R_386_SIZE32, pidns_trylookup_task_locked; .long 0
	.long 0x5d25604
	.long .Lname1541 /* index: 1541 */
	.weak heap_free; .long heap_free
	.reloc ., R_386_SIZE32, heap_free; .long 0
	.long 0x865b605
	.long 0 /* index: 1542 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1543 */
	.long 0
	.long 0
	.long 0
	.long .Lname1544 /* index: 1544 */
	.weak mouse_device_button_ex; .long mouse_device_button_ex
	.reloc ., R_386_SIZE32, mouse_device_button_ex; .long 0
	.long 0xd9d9608
	.long 0 /* index: 1545 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1546 */
	.long 0
	.long 0
	.long 0
	.long .Lname1547 /* index: 1547 */
	.weak vm_enumdma_nx; .long vm_enumdma_nx
	.reloc ., R_386_SIZE32, vm_enumdma_nx; .long 0
	.long 0xea6b188
	.long 0 /* index: 1548 */
	.long 0
	.long 0
	.long 0
	.long .Lname1549 /* index: 1549 */
	.weak task_schedule_asynchronous_rpc; .long task_schedule_asynchronous_rpc
	.reloc ., R_386_SIZE32, task_schedule_asynchronous_rpc; .long 0
	.long 0xef54f13
	.long .Lname1550 /* index: 1550 */
	.weak unicode_readutf16_rev_n; .long unicode_readutf16_rev_n
	.reloc ., R_386_SIZE32, unicode_readutf16_rev_n; .long 0
	.long 0xa03460e
	.long .Lname1551 /* index: 1551 */
	.weak vio_copyfromvio; .long vio_copyfromvio
	.reloc ., R_386_SIZE32, vio_copyfromvio; .long 0
	.long 0x8f0560f
	.long 0 /* index: 1552 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1553 */
	.long 0
	.long 0
	.long 0
	.long .Lname1554 /* index: 1554 */
	.weak block_device_unregister; .long block_device_unregister
	.reloc ., R_386_SIZE32, block_device_unregister; .long 0
	.long 0x385f612
	.long .Lname1555 /* index: 1555 */
	.weak x86_spurious_interrupts; .long x86_spurious_interrupts
	.reloc ., R_386_SIZE32, x86_spurious_interrupts; .long 0
	.long 0xa0b1613
	.long 0 /* index: 1556 */
	.long 0
	.long 0
	.long 0
	.long .Lname1557 /* index: 1557 */
	.weak syscall_printtrace; .long syscall_printtrace
	.reloc ., R_386_SIZE32, syscall_printtrace; .long 0
	.long 0x30d6615
	.long .Lname1558 /* index: 1558 */
	.weak sys_setreuid; .long sys_setreuid
	.reloc ., R_386_SIZE32, sys_setreuid; .long 0
	.long 0xb085d64
	.long 0 /* index: 1559 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1560 */
	.long 0
	.long 0
	.long 0
	.long .Lname1561 /* index: 1561 */
	.weak mouse_buffer_getpacket; .long mouse_buffer_getpacket
	.reloc ., R_386_SIZE32, mouse_buffer_getpacket; .long 0
	.long 0xe112104
	.long 0 /* index: 1562 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1563 */
	.long 0
	.long 0
	.long 0
	.long .Lname1564 /* index: 1564 */
	.weak sys_socketcall; .long sys_socketcall
	.reloc ., R_386_SIZE32, sys_socketcall; .long 0
	.long 0x15c361c
	.long 0 /* index: 1565 */
	.long 0
	.long 0
	.long 0
	.long .Lname1566 /* index: 1566 */
	.weak x86_fpustate_init; .long x86_fpustate_init
	.reloc ., R_386_SIZE32, x86_fpustate_init; .long 0
	.long 0x7b2f3d4
	.long .Lname1567 /* index: 1567 */
	.weak task_start; .long task_start
	.reloc ., R_386_SIZE32, task_start; .long 0
	.long 0x16d0034
	.long .Lname1568 /* index: 1568 */
	.weak inode_recent; .long inode_recent
	.reloc ., R_386_SIZE32, inode_recent; .long 0
	.long 0x18ec2e4
	.long 0 /* index: 1569 */
	.long 0
	.long 0
	.long 0
	.long .Lname1570 /* index: 1570 */
	.weak vm_datablock_write; .long vm_datablock_write
	.reloc ., R_386_SIZE32, vm_datablock_write; .long 0
	.long 0xec21f85
	.long .Lname1571 /* index: 1571 */
	.weak driver_clear_fde_caches; .long driver_clear_fde_caches
	.reloc ., R_386_SIZE32, driver_clear_fde_caches; .long 0
	.long 0x1fc4623
	.long .Lname1572 /* index: 1572 */
	.weak block_device_acquire_partlock_tryread; .long block_device_acquire_partlock_tryread
	.reloc ., R_386_SIZE32, block_device_acquire_partlock_tryread; .long 0
	.long 0xec0b624
	.long 0 /* index: 1573 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1574 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1575 */
	.long 0
	.long 0
	.long 0
	.long .Lname1576 /* index: 1576 */
	.weak vm_enumdmav_nx; .long vm_enumdmav_nx
	.reloc ., R_386_SIZE32, vm_enumdmav_nx; .long 0
	.long 0xa64f9b8
	.long 0 /* index: 1577 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1578 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1579 */
	.long 0
	.long 0
	.long 0
	.long .Lname1580 /* index: 1580 */
	.weak task_yield; .long task_yield
	.reloc ., R_386_SIZE32, task_yield; .long 0
	.long 0x1685484
	.long .Lname1581 /* index: 1581 */
	.weak block_device_awrite_sector; .long block_device_awrite_sector
	.reloc ., R_386_SIZE32, block_device_awrite_sector; .long 0
	.long 0x1e52bb2
	.long 0 /* index: 1582 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1583 */
	.long 0
	.long 0
	.long 0
	.long .Lname1584 /* index: 1584 */
	.weak json_writer_putfloat; .long json_writer_putfloat
	.reloc ., R_386_SIZE32, json_writer_putfloat; .long 0
	.long 0x6651a54
	.long 0 /* index: 1585 */
	.long 0
	.long 0
	.long 0
	.long .Lname1586 /* index: 1586 */
	.weak sys_socketpair; .long sys_socketpair
	.reloc ., R_386_SIZE32, sys_socketpair; .long 0
	.long 0x15dc632
	.long .Lname1587 /* index: 1587 */
	.weak _this_fs; .long _this_fs
	.reloc ., R_386_SIZE32, _this_fs; .long 0
	.long 0xaf093b3
	.long .Lname1588 /* index: 1588 */
	.weak vm_datablock_findchanged; .long vm_datablock_findchanged
	.reloc ., R_386_SIZE32, vm_datablock_findchanged; .long 0
	.long 0x718c634
	.long .Lname1589 /* index: 1589 */
	.weak sys_clock_gettime; .long sys_clock_gettime
	.reloc ., R_386_SIZE32, sys_clock_gettime; .long 0
	.long 0x7a50635
	.long 0 /* index: 1590 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1591 */
	.long 0
	.long 0
	.long 0
	.long .Lname1592 /* index: 1592 */
	.weak dbg_fillbox; .long dbg_fillbox
	.reloc ., R_386_SIZE32, dbg_fillbox; .long 0
	.long 0xca9a638
	.long .Lname1593 /* index: 1593 */
	.weak sys_readahead; .long sys_readahead
	.reloc ., R_386_SIZE32, sys_readahead; .long 0
	.long 0xcae83b4
	.long 0 /* index: 1594 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1595 */
	.long 0
	.long 0
	.long 0
	.long .Lname1596 /* index: 1596 */
	.weak character_device_ioctl; .long character_device_ioctl
	.reloc ., R_386_SIZE32, character_device_ioctl; .long 0
	.long 0x890a63c
	.long 0 /* index: 1597 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1598 */
	.long 0
	.long 0
	.long 0
	.long .Lname1599 /* index: 1599 */
	.weak unwind_getreg_scpustate; .long unwind_getreg_scpustate
	.reloc ., R_386_SIZE32, unwind_getreg_scpustate; .long 0
	.long 0xb8c43b5
	.long 0 /* index: 1600 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1601 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1602 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1603 */
	.long 0
	.long 0
	.long 0
	.long .Lname1604 /* index: 1604 */
	.weak sys_getresuid; .long sys_getresuid
	.reloc ., R_386_SIZE32, sys_getresuid; .long 0
	.long 0x85f644
	.long .Lname1605 /* index: 1605 */
	.weak error_active; .long error_active
	.reloc ., R_386_SIZE32, error_active; .long 0
	.long 0x3b34645
	.long .Lname1606 /* index: 1606 */
	.weak vm_enumdmav; .long vm_enumdmav
	.reloc ., R_386_SIZE32, vm_enumdmav; .long 0
	.long 0x5dea646
	.long .Lname1607 /* index: 1607 */
	.weak rawmemrlenq; .long rawmemrlenq
	.reloc ., R_386_SIZE32, rawmemrlenq; .long 0
	.long 0xc31a661
	.long .Lname1608 /* index: 1608 */
	.weak vm_tasklock_read; .long vm_tasklock_read
	.reloc ., R_386_SIZE32, vm_tasklock_read; .long 0
	.long 0x4995944
	.long 0 /* index: 1609 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1610 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1611 */
	.long 0
	.long 0
	.long 0
	.long .Lname1612 /* index: 1612 */
	.weak mouse_device_poll; .long mouse_device_poll
	.reloc ., R_386_SIZE32, mouse_device_poll; .long 0
	.long 0x298d64c
	.long .Lname1613 /* index: 1613 */
	.weak heap_trim; .long heap_trim
	.reloc ., R_386_SIZE32, heap_trim; .long 0
	.long 0x866d64d
	.long .Lname1614 /* index: 1614 */
	.weak sys_lchown; .long sys_lchown
	.reloc ., R_386_SIZE32, sys_lchown; .long 0
	.long 0x62e664e
	.long 0 /* index: 1615 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1616 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1617 */
	.long 0
	.long 0
	.long 0
	.long .Lname1618 /* index: 1618 */
	.weak sys_fsetxattr; .long sys_fsetxattr
	.reloc ., R_386_SIZE32, sys_fsetxattr; .long 0
	.long 0x7b7d652
	.long .Lname1619 /* index: 1619 */
	.weak task_push_asynchronous_srpc; .long task_push_asynchronous_srpc
	.reloc ., R_386_SIZE32, task_push_asynchronous_srpc; .long 0
	.long 0xd4ea653
	.long 0 /* index: 1620 */
	.long 0
	.long 0
	.long 0
	.long .Lname1621 /* index: 1621 */
	.weak sys_oldolduname; .long sys_oldolduname
	.reloc ., R_386_SIZE32, sys_oldolduname; .long 0
	.long 0xbde1655
	.long 0 /* index: 1622 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1623 */
	.long 0
	.long 0
	.long 0
	.long .Lname1624 /* index: 1624 */
	.weak dbg_autocomplete_command; .long dbg_autocomplete_command
	.reloc ., R_386_SIZE32, dbg_autocomplete_command; .long 0
	.long 0x573ccd4
	.long .Lname1625 /* index: 1625 */
	.weak sys_getpid; .long sys_getpid
	.reloc ., R_386_SIZE32, sys_getpid; .long 0
	.long 0x5db0664
	.long .Lname1626 /* index: 1626 */
	.weak dbg_getfunc; .long dbg_getfunc
	.reloc ., R_386_SIZE32, dbg_getfunc; .long 0
	.long 0xda05713
	.long 0 /* index: 1627 */
	.long 0
	.long 0
	.long 0
	.long .Lname1628 /* index: 1628 */
	.weak terminal_owrite; .long terminal_owrite
	.reloc ., R_386_SIZE32, terminal_owrite; .long 0
	.long 0xd2ece45
	.long 0 /* index: 1629 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1630 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1631 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1632 */
	.long 0
	.long 0
	.long 0
	.long .Lname1633 /* index: 1633 */
	.weak cpu_deepsleep; .long cpu_deepsleep
	.reloc ., R_386_SIZE32, cpu_deepsleep; .long 0
	.long 0x6037110
	.long .Lname1634 /* index: 1634 */
	.weak sys_lfutexlockexpr; .long sys_lfutexlockexpr
	.reloc ., R_386_SIZE32, sys_lfutexlockexpr; .long 0
	.long 0xffb9662
	.long 0 /* index: 1635 */
	.long 0
	.long 0
	.long 0
	.long .Lname1636 /* index: 1636 */
	.weak cpu_quantum_end; .long cpu_quantum_end
	.reloc ., R_386_SIZE32, cpu_quantum_end; .long 0
	.long 0xeb8664
	.long 0 /* index: 1637 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1638 */
	.long 0
	.long 0
	.long 0
	.long .Lname1639 /* index: 1639 */
	.weak rawmemrlenw; .long rawmemrlenw
	.reloc ., R_386_SIZE32, rawmemrlenw; .long 0
	.long 0xc31a667
	.long 0 /* index: 1640 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1641 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1642 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1643 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1644 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1645 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1646 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1647 */
	.long 0
	.long 0
	.long 0
	.long .Lname1648 /* index: 1648 */
	.weak inode_awritev_phys; .long inode_awritev_phys
	.reloc ., R_386_SIZE32, inode_awritev_phys; .long 0
	.long 0xe4d8613
	.long 0 /* index: 1649 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1650 */
	.long 0
	.long 0
	.long 0
	.long .Lname1651 /* index: 1651 */
	.weak krealloc; .long krealloc
	.reloc ., R_386_SIZE32, krealloc; .long 0
	.long 0x8b83673
	.long .Lname1652 /* index: 1652 */
	.weak x86_cpugdt; .long x86_cpugdt
	.reloc ., R_386_SIZE32, x86_cpugdt; .long 0
	.long 0x5a00674
	.long 0 /* index: 1653 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1654 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1655 */
	.long 0
	.long 0
	.long 0
	.long .Lname1656 /* index: 1656 */
	.weak krealloc_in_place_nx; .long krealloc_in_place_nx
	.reloc ., R_386_SIZE32, krealloc_in_place_nx; .long 0
	.long 0x391c678
	.long .Lname1657 /* index: 1657 */
	.weak handle_manager_destroy; .long handle_manager_destroy
	.reloc ., R_386_SIZE32, handle_manager_destroy; .long 0
	.long 0x59ab679
	.long 0 /* index: 1658 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1659 */
	.long 0
	.long 0
	.long 0
	.long .Lname1660 /* index: 1660 */
	.weak rawmemrlenl; .long rawmemrlenl
	.reloc ., R_386_SIZE32, rawmemrlenl; .long 0
	.long 0xc31a67c
	.long .Lname1661 /* index: 1661 */
	.weak dbg_enter_fcpustate; .long dbg_enter_fcpustate
	.reloc ., R_386_SIZE32, dbg_enter_fcpustate; .long 0
	.long 0x781a835
	.long .Lname1662 /* index: 1662 */
	.weak swap_malloc_part; .long swap_malloc_part
	.reloc ., R_386_SIZE32, swap_malloc_part; .long 0
	.long 0x3f29824
	.long .Lname1663 /* index: 1663 */
	.weak krealloc_in_place; .long krealloc_in_place
	.reloc ., R_386_SIZE32, krealloc_in_place; .long 0
	.long 0x1023915
	.long 0 /* index: 1664 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1665 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1666 */
	.long 0
	.long 0
	.long 0
	.long .Lname1667 /* index: 1667 */
	.weak vpage_alloc; .long vpage_alloc
	.reloc ., R_386_SIZE32, vpage_alloc; .long 0
	.long 0xb2b5683
	.long .Lname1668 /* index: 1668 */
	.weak sys_truncate64; .long sys_truncate64
	.reloc ., R_386_SIZE32, sys_truncate64; .long 0
	.long 0x40e1684
	.long .Lname1669 /* index: 1669 */
	.weak inode_chtime; .long inode_chtime
	.reloc ., R_386_SIZE32, inode_chtime; .long 0
	.long 0x29af685
	.long 0 /* index: 1670 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1671 */
	.long 0
	.long 0
	.long 0
	.long .Lname1672 /* index: 1672 */
	.weak path_lock_upgrade_nx; .long path_lock_upgrade_nx
	.reloc ., R_386_SIZE32, path_lock_upgrade_nx; .long 0
	.long 0xac21688
	.long 0 /* index: 1673 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1674 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1675 */
	.long 0
	.long 0
	.long 0
	.long .Lname1676 /* index: 1676 */
	.weak sys_epoll_ctl; .long sys_epoll_ctl
	.reloc ., R_386_SIZE32, sys_epoll_ctl; .long 0
	.long 0xf39068c
	.long 0 /* index: 1677 */
	.long 0
	.long 0
	.long 0
	.long .Lname1678 /* index: 1678 */
	.weak keymap_instrlen; .long keymap_instrlen
	.reloc ., R_386_SIZE32, keymap_instrlen; .long 0
	.long 0x593c68e
	.long 0 /* index: 1679 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1680 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1681 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1682 */
	.long 0
	.long 0
	.long 0
	.long .Lname1683 /* index: 1683 */
	.weak swap_sync; .long swap_sync
	.reloc ., R_386_SIZE32, swap_sync; .long 0
	.long 0x866d693
	.long .Lname1684 /* index: 1684 */
	.weak inode_changed; .long inode_changed
	.reloc ., R_386_SIZE32, inode_changed; .long 0
	.long 0x9b3e694
	.long .Lname1685 /* index: 1685 */
	.weak json_parser_state; .long json_parser_state
	.reloc ., R_386_SIZE32, json_parser_state; .long 0
	.long 0x2739725
	.long 0 /* index: 1686 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1687 */
	.long 0
	.long 0
	.long 0
	.long .Lname1688 /* index: 1688 */
	.weak sys_utime64; .long sys_utime64
	.reloc ., R_386_SIZE32, sys_utime64; .long 0
	.long 0xcd531f4
	.long .Lname1689 /* index: 1689 */
	.weak vm_datapart_lock_end; .long vm_datapart_lock_end
	.reloc ., R_386_SIZE32, vm_datapart_lock_end; .long 0
	.long 0x5473c4
	.long 0 /* index: 1690 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1691 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1692 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1693 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1694 */
	.long 0
	.long 0
	.long 0
	.long .Lname1695 /* index: 1695 */
	.weak superblock_mountlock_downgrade; .long superblock_mountlock_downgrade
	.reloc ., R_386_SIZE32, superblock_mountlock_downgrade; .long 0
	.long 0xd3d83c5
	.long 0 /* index: 1696 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1697 */
	.long 0
	.long 0
	.long 0
	.long .Lname1698 /* index: 1698 */
	.weak debuginfo_cu_parser_loadattr_member; .long debuginfo_cu_parser_loadattr_member
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_member; .long 0
	.long 0xd7446a2
	.long 0 /* index: 1699 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1700 */
	.long 0
	.long 0
	.long 0
	.long .Lname1701 /* index: 1701 */
	.weak path_freesize; .long path_freesize
	.reloc ., R_386_SIZE32, path_freesize; .long 0
	.long 0xe3686a5
	.long 0 /* index: 1702 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1703 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1704 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1705 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1706 */
	.long 0
	.long 0
	.long 0
	.long .Lname1707 /* index: 1707 */
	.weak symlink_node_readlink; .long symlink_node_readlink
	.reloc ., R_386_SIZE32, symlink_node_readlink; .long 0
	.long 0xa11d6ab
	.long .Lname1708 /* index: 1708 */
	.weak task_alloc_user_rpc; .long task_alloc_user_rpc
	.reloc ., R_386_SIZE32, task_alloc_user_rpc; .long 0
	.long 0x79cab3
	.long 0 /* index: 1709 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1710 */
	.long 0
	.long 0
	.long 0
	.long .Lname1711 /* index: 1711 */
	.weak mouse_device_vwheel; .long mouse_device_vwheel
	.reloc ., R_386_SIZE32, mouse_device_vwheel; .long 0
	.long 0x87d892c
	.long .Lname1712 /* index: 1712 */
	.weak slab_kmalloc12; .long slab_kmalloc12
	.reloc ., R_386_SIZE32, slab_kmalloc12; .long 0
	.long 0x66b31d2
	.long 0 /* index: 1713 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1714 */
	.long 0
	.long 0
	.long 0
	.long .Lname1715 /* index: 1715 */
	.weak superblock_clear_caches; .long superblock_clear_caches
	.reloc ., R_386_SIZE32, superblock_clear_caches; .long 0
	.long 0x93c8673
	.long .Lname1716 /* index: 1716 */
	.weak path_sprint; .long path_sprint
	.reloc ., R_386_SIZE32, path_sprint; .long 0
	.long 0x6d106b4
	.long .Lname1717 /* index: 1717 */
	.weak unwind_getreg_fcpustate; .long unwind_getreg_fcpustate
	.reloc ., R_386_SIZE32, unwind_getreg_fcpustate; .long 0
	.long 0xb8c76b5
	.long .Lname1718 /* index: 1718 */
	.weak debuginfo_cu_parser_getref; .long debuginfo_cu_parser_getref
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getref; .long 0
	.long 0xbbb56b6
	.long 0 /* index: 1719 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1720 */
	.long 0
	.long 0
	.long 0
	.long .Lname1721 /* index: 1721 */
	.weak sys_frenameat; .long sys_frenameat
	.reloc ., R_386_SIZE32, sys_frenameat; .long 0
	.long 0x14f6674
	.long 0 /* index: 1722 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1723 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1724 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1725 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1726 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1727 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1728 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1729 */
	.long 0
	.long 0
	.long 0
	.long .Lname1730 /* index: 1730 */
	.weak keyboard_buffer_putkey_nopr; .long keyboard_buffer_putkey_nopr
	.reloc ., R_386_SIZE32, keyboard_buffer_putkey_nopr; .long 0
	.long 0x2a056c2
	.long .Lname1731 /* index: 1731 */
	.weak handle_get_task; .long handle_get_task
	.reloc ., R_386_SIZE32, handle_get_task; .long 0
	.long 0x83473cb
	.long .Lname1732 /* index: 1732 */
	.weak rwlock_write; .long rwlock_write
	.reloc ., R_386_SIZE32, rwlock_write; .long 0
	.long 0x8f0c505
	.long .Lname1733 /* index: 1733 */
	.weak driver_initialize; .long driver_initialize
	.reloc ., R_386_SIZE32, driver_initialize; .long 0
	.long 0x6da66c5
	.long 0 /* index: 1734 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1735 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1736 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1737 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1738 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1739 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1740 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1741 */
	.long 0
	.long 0
	.long 0
	.long .Lname1742 /* index: 1742 */
	.weak sys_fchownat; .long sys_fchownat
	.reloc ., R_386_SIZE32, sys_fchownat; .long 0
	.long 0xe665144
	.long .Lname1743 /* index: 1743 */
	.weak sys_timer_settime64; .long sys_timer_settime64
	.reloc ., R_386_SIZE32, sys_timer_settime64; .long 0
	.long 0x3613bc4
	.long 0 /* index: 1744 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1745 */
	.long 0
	.long 0
	.long 0
	.long .Lname1746 /* index: 1746 */
	.weak x86_memcpy_nopf_rep_pointer; .long x86_memcpy_nopf_rep_pointer
	.reloc ., R_386_SIZE32, x86_memcpy_nopf_rep_pointer; .long 0
	.long 0x8a136d2
	.long .Lname1747 /* index: 1747 */
	.weak slab_malloc; .long slab_malloc
	.reloc ., R_386_SIZE32, slab_malloc; .long 0
	.long 0x64e16d3
	.long .Lname1748 /* index: 1748 */
	.weak dbg_print; .long dbg_print
	.reloc ., R_386_SIZE32, dbg_print; .long 0
	.long 0xd67e6d4
	.long .Lname1749 /* index: 1749 */
	.weak sys_sched_setscheduler; .long sys_sched_setscheduler
	.reloc ., R_386_SIZE32, sys_sched_setscheduler; .long 0
	.long 0xeb96042
	.long 0 /* index: 1750 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1751 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1752 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1753 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1754 */
	.long 0
	.long 0
	.long 0
	.long .Lname1755 /* index: 1755 */
	.weak syscall_emulate; .long syscall_emulate
	.reloc ., R_386_SIZE32, syscall_emulate; .long 0
	.long 0x3d443f5
	.long 0 /* index: 1756 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1757 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1758 */
	.long 0
	.long 0
	.long 0
	.long .Lname1759 /* index: 1759 */
	.weak character_device_pwrite; .long character_device_pwrite
	.reloc ., R_386_SIZE32, character_device_pwrite; .long 0
	.long 0xb715925
	.long 0 /* index: 1760 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1761 */
	.long 0
	.long 0
	.long 0
	.long .Lname1762 /* index: 1762 */
	.weak sys_set_exception_handler; .long sys_set_exception_handler
	.reloc ., R_386_SIZE32, sys_set_exception_handler; .long 0
	.long 0xa9f56e2
	.long 0 /* index: 1763 */
	.long 0
	.long 0
	.long 0
	.long .Lname1764 /* index: 1764 */
	.weak sys_clock_getres64; .long sys_clock_getres64
	.reloc ., R_386_SIZE32, sys_clock_getres64; .long 0
	.long 0xa5266e4
	.long .Lname1765 /* index: 1765 */
	.weak coredump_create; .long coredump_create
	.reloc ., R_386_SIZE32, coredump_create; .long 0
	.long 0xd1356e5
	.long .Lname1766 /* index: 1766 */
	.weak regdump_dr6; .long regdump_dr6
	.reloc ., R_386_SIZE32, regdump_dr6; .long 0
	.long 0xc3ee6e6
	.long .Lname1767 /* index: 1767 */
	.weak regdump_dr7; .long regdump_dr7
	.reloc ., R_386_SIZE32, regdump_dr7; .long 0
	.long 0xc3ee6e7
	.long 0 /* index: 1768 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1769 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1770 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1771 */
	.long 0
	.long 0
	.long 0
	.long .Lname1772 /* index: 1772 */
	.weak sys_truncate; .long sys_truncate
	.reloc ., R_386_SIZE32, sys_truncate; .long 0
	.long 0xe140e15
	.long 0 /* index: 1773 */
	.long 0
	.long 0
	.long 0
	.long .Lname1774 /* index: 1774 */
	.weak vm86_outl; .long vm86_outl
	.reloc ., R_386_SIZE32, vm86_outl; .long 0
	.long 0xbc611ac
	.long .Lname1775 /* index: 1775 */
	.weak vio_copytovio; .long vio_copytovio
	.reloc ., R_386_SIZE32, vio_copytovio; .long 0
	.long 0xb1036ef
	.long .Lname1776 /* index: 1776 */
	.weak cpu_quantum_remaining_nopr; .long cpu_quantum_remaining_nopr
	.reloc ., R_386_SIZE32, cpu_quantum_remaining_nopr; .long 0
	.long 0xf0d29d2
	.long 0 /* index: 1777 */
	.long 0
	.long 0
	.long 0
	.long .Lname1778 /* index: 1778 */
	.weak vio_orb; .long vio_orb
	.reloc ., R_386_SIZE32, vio_orb; .long 0
	.long 0xd0566f2
	.long .Lname1779 /* index: 1779 */
	.weak aio_pbuffer_copytophys; .long aio_pbuffer_copytophys
	.reloc ., R_386_SIZE32, aio_pbuffer_copytophys; .long 0
	.long 0xa9cd6f3
	.long .Lname1780 /* index: 1780 */
	.weak sys_ppoll64; .long sys_ppoll64
	.reloc ., R_386_SIZE32, sys_ppoll64; .long 0
	.long 0x72f26f4
	.long .Lname1781 /* index: 1781 */
	.weak vm_datapart_lockwrite_setcore; .long vm_datapart_lockwrite_setcore
	.reloc ., R_386_SIZE32, vm_datapart_lockwrite_setcore; .long 0
	.long 0x5e236f5
	.long 0 /* index: 1782 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1783 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1784 */
	.long 0
	.long 0
	.long 0
	.long .Lname1785 /* index: 1785 */
	.weak pidns_root; .long pidns_root
	.reloc ., R_386_SIZE32, pidns_root; .long 0
	.long 0x591fbd4
	.long 0 /* index: 1786 */
	.long 0
	.long 0
	.long 0
	.long .Lname1787 /* index: 1787 */
	.weak unwind_emulator_exec_autostack; .long unwind_emulator_exec_autostack
	.reloc ., R_386_SIZE32, unwind_emulator_exec_autostack; .long 0
	.long 0x49816fb
	.long .Lname1788 /* index: 1788 */
	.weak vio_orl; .long vio_orl
	.reloc ., R_386_SIZE32, vio_orl; .long 0
	.long 0xd0566fc
	.long 0 /* index: 1789 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1790 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1791 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1792 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1793 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1794 */
	.long 0
	.long 0
	.long 0
	.long .Lname1795 /* index: 1795 */
	.weak handle_get_fs; .long handle_get_fs
	.reloc ., R_386_SIZE32, handle_get_fs; .long 0
	.long 0xb583703
	.long .Lname1796 /* index: 1796 */
	.weak callback_list_insert; .long callback_list_insert
	.reloc ., R_386_SIZE32, callback_list_insert; .long 0
	.long 0xc941704
	.long .Lname1797 /* index: 1797 */
	.weak sys_ptrace; .long sys_ptrace
	.reloc ., R_386_SIZE32, sys_ptrace; .long 0
	.long 0x67c3705
	.long 0 /* index: 1798 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1799 */
	.long 0
	.long 0
	.long 0
	.long .Lname1800 /* index: 1800 */
	.weak sys_detach; .long sys_detach
	.reloc ., R_386_SIZE32, sys_detach; .long 0
	.long 0x5ab1708
	.long .Lname1801 /* index: 1801 */
	.weak dbg_ungetkey; .long dbg_ungetkey
	.reloc ., R_386_SIZE32, dbg_ungetkey; .long 0
	.long 0x2748709
	.long .Lname1802 /* index: 1802 */
	.weak superblock_mountlock_write; .long superblock_mountlock_write
	.reloc ., R_386_SIZE32, superblock_mountlock_write; .long 0
	.long 0x33791d5
	.long 0 /* index: 1803 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1804 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1805 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1806 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1807 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1808 */
	.long 0
	.long 0
	.long 0
	.long .Lname1809 /* index: 1809 */
	.weak vio_cmpxch_or_writew; .long vio_cmpxch_or_writew
	.reloc ., R_386_SIZE32, vio_cmpxch_or_writew; .long 0
	.long 0x8230f27
	.long .Lname1810 /* index: 1810 */
	.weak sys_fgetxattr; .long sys_fgetxattr
	.reloc ., R_386_SIZE32, sys_fgetxattr; .long 0
	.long 0x7b7d712
	.long .Lname1811 /* index: 1811 */
	.weak system_clearcaches_s; .long system_clearcaches_s
	.reloc ., R_386_SIZE32, system_clearcaches_s; .long 0
	.long 0xd1f8713
	.long .Lname1812 /* index: 1812 */
	.weak sig_altsend; .long sig_altsend
	.reloc ., R_386_SIZE32, sig_altsend; .long 0
	.long 0x8426714
	.long .Lname1813 /* index: 1813 */
	.weak superblock_nodeslock_endread; .long superblock_nodeslock_endread
	.reloc ., R_386_SIZE32, superblock_nodeslock_endread; .long 0
	.long 0xe4beae4
	.long 0 /* index: 1814 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1815 */
	.long 0
	.long 0
	.long 0
	.long .Lname1816 /* index: 1816 */
	.weak aio_multihandle_allochandle_nx; .long aio_multihandle_allochandle_nx
	.reloc ., R_386_SIZE32, aio_multihandle_allochandle_nx; .long 0
	.long 0xdcf3718
	.long .Lname1817 /* index: 1817 */
	.weak sys_recvmmsg64; .long sys_recvmmsg64
	.reloc ., R_386_SIZE32, sys_recvmmsg64; .long 0
	.long 0xdb21684
	.long 0 /* index: 1818 */
	.long 0
	.long 0
	.long 0
	.long .Lname1819 /* index: 1819 */
	.weak pidns_write; .long pidns_write
	.reloc ., R_386_SIZE32, pidns_write; .long 0
	.long 0x9188bf5
	.long .Lname1820 /* index: 1820 */
	.weak sys_setfsgid; .long sys_setfsgid
	.reloc ., R_386_SIZE32, sys_setfsgid; .long 0
	.long 0xb1d0b64
	.long 0 /* index: 1821 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1822 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1823 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1824 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1825 */
	.long 0
	.long 0
	.long 0
	.long .Lname1826 /* index: 1826 */
	.weak _this_handle_manager; .long _this_handle_manager
	.reloc ., R_386_SIZE32, _this_handle_manager; .long 0
	.long 0xddfc722
	.long .Lname1827 /* index: 1827 */
	.weak tty_device_alloc; .long tty_device_alloc
	.reloc ., R_386_SIZE32, tty_device_alloc; .long 0
	.long 0xfd6723
	.long .Lname1828 /* index: 1828 */
	.weak task_raisesignalthread; .long task_raisesignalthread
	.reloc ., R_386_SIZE32, task_raisesignalthread; .long 0
	.long 0xe5fc724
	.long .Lname1829 /* index: 1829 */
	.weak vm_sync_endone; .long vm_sync_endone
	.reloc ., R_386_SIZE32, vm_sync_endone; .long 0
	.long 0x6efb725
	.long .Lname1830 /* index: 1830 */
	.weak sys_preadv; .long sys_preadv
	.reloc ., R_386_SIZE32, sys_preadv; .long 0
	.long 0x67f0726
	.long .Lname1831 /* index: 1831 */
	.weak error_data; .long error_data
	.reloc ., R_386_SIZE32, error_data; .long 0
	.long 0x6836131
	.long .Lname1832 /* index: 1832 */
	.weak slab_kmalloc16; .long slab_kmalloc16
	.reloc ., R_386_SIZE32, slab_kmalloc16; .long 0
	.long 0x66b31d6
	.long .Lname1833 /* index: 1833 */
	.weak dbg_pputuni; .long dbg_pputuni
	.reloc ., R_386_SIZE32, dbg_pputuni; .long 0
	.long 0x7163729
	.long 0 /* index: 1834 */
	.long 0
	.long 0
	.long 0
	.long .Lname1835 /* index: 1835 */
	.weak vm_delhwbreak; .long vm_delhwbreak
	.reloc ., R_386_SIZE32, vm_delhwbreak; .long 0
	.long 0x2ec272b
	.long 0 /* index: 1836 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1837 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1838 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1839 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1840 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1841 */
	.long 0
	.long 0
	.long 0
	.long .Lname1842 /* index: 1842 */
	.weak x86_fxrstor; .long x86_fxrstor
	.reloc ., R_386_SIZE32, x86_fxrstor; .long 0
	.long 0xd821732
	.long .Lname1843 /* index: 1843 */
	.weak task_popconnections; .long task_popconnections
	.reloc ., R_386_SIZE32, task_popconnections; .long 0
	.long 0x74eb733
	.long .Lname1844 /* index: 1844 */
	.weak x86_fpustate_save_noreset; .long x86_fpustate_save_noreset
	.reloc ., R_386_SIZE32, x86_fpustate_save_noreset; .long 0
	.long 0x6e6d734
	.long .Lname1845 /* index: 1845 */
	.weak vm_kernel_treelock_endwrite; .long vm_kernel_treelock_endwrite
	.reloc ., R_386_SIZE32, vm_kernel_treelock_endwrite; .long 0
	.long 0xf8e2735
	.long .Lname1846 /* index: 1846 */
	.weak vm_datablock_vio_readv; .long vm_datablock_vio_readv
	.reloc ., R_386_SIZE32, vm_datablock_vio_readv; .long 0
	.long 0xc467736
	.long .Lname1847 /* index: 1847 */
	.weak ttybase_device_setctty; .long ttybase_device_setctty
	.reloc ., R_386_SIZE32, ttybase_device_setctty; .long 0
	.long 0xd8b1e89
	.long 0 /* index: 1848 */
	.long 0
	.long 0
	.long 0
	.long .Lname1849 /* index: 1849 */
	.weak path_destroy; .long path_destroy
	.reloc ., R_386_SIZE32, path_destroy; .long 0
	.long 0xda21739
	.long 0 /* index: 1850 */
	.long 0
	.long 0
	.long 0
	.long .Lname1851 /* index: 1851 */
	.weak ringbuffer_wseek; .long ringbuffer_wseek
	.reloc ., R_386_SIZE32, ringbuffer_wseek; .long 0
	.long 0xbf2c73b
	.long 0 /* index: 1852 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1853 */
	.long 0
	.long 0
	.long 0
	.long .Lname1854 /* index: 1854 */
	.weak sys_rt_sigaction; .long sys_rt_sigaction
	.reloc ., R_386_SIZE32, sys_rt_sigaction; .long 0
	.long 0xbe5773e
	.long .Lname1855 /* index: 1855 */
	.weak ramfs_directory_type; .long ramfs_directory_type
	.reloc ., R_386_SIZE32, ramfs_directory_type; .long 0
	.long 0x1609935
	.long 0 /* index: 1856 */
	.long 0
	.long 0
	.long 0
	.long .Lname1857 /* index: 1857 */
	.weak pagedir_ismapped_p; .long pagedir_ismapped_p
	.reloc ., R_386_SIZE32, pagedir_ismapped_p; .long 0
	.long 0xf556be0
	.long .Lname1858 /* index: 1858 */
	.weak sys_lchown32; .long sys_lchown32
	.reloc ., R_386_SIZE32, sys_lchown32; .long 0
	.long 0xe665742
	.long 0 /* index: 1859 */
	.long 0
	.long 0
	.long 0
	.long .Lname1860 /* index: 1860 */
	.weak path_sprintent; .long path_sprintent
	.reloc ., R_386_SIZE32, path_sprintent; .long 0
	.long 0x6bc744
	.long .Lname1861 /* index: 1861 */
	.weak fs_filesystems_lock_tryupgrade; .long fs_filesystems_lock_tryupgrade
	.reloc ., R_386_SIZE32, fs_filesystems_lock_tryupgrade; .long 0
	.long 0x6053745
	.long 0 /* index: 1862 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1863 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1864 */
	.long 0
	.long 0
	.long 0
	.long .Lname1865 /* index: 1865 */
	.weak sys_symlink; .long sys_symlink
	.reloc ., R_386_SIZE32, sys_symlink; .long 0
	.long 0xa99272b
	.long 0 /* index: 1866 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1867 */
	.long 0
	.long 0
	.long 0
	.long .Lname1868 /* index: 1868 */
	.weak keyboard_device_poll; .long keyboard_device_poll
	.reloc ., R_386_SIZE32, keyboard_device_poll; .long 0
	.long 0xf16074c
	.long .Lname1869 /* index: 1869 */
	.weak mouse_device_button_nopr; .long mouse_device_button_nopr
	.reloc ., R_386_SIZE32, mouse_device_button_nopr; .long 0
	.long 0xd979be2
	.long 0 /* index: 1870 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1871 */
	.long 0
	.long 0
	.long 0
	.long .Lname1872 /* index: 1872 */
	.weak pidns_lookup; .long pidns_lookup
	.reloc ., R_386_SIZE32, pidns_lookup; .long 0
	.long 0x35bf750
	.long 0 /* index: 1873 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1874 */
	.long 0
	.long 0
	.long 0
	.long .Lname1875 /* index: 1875 */
	.weak inode_aread_phys; .long inode_aread_phys
	.reloc ., R_386_SIZE32, inode_aread_phys; .long 0
	.long 0xd34e3e3
	.long .Lname1876 /* index: 1876 */
	.weak x86_idt_start; .long x86_idt_start
	.reloc ., R_386_SIZE32, x86_idt_start; .long 0
	.long 0x3d6f754
	.long 0 /* index: 1877 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1878 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1879 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1880 */
	.long 0
	.long 0
	.long 0
	.long .Lname1881 /* index: 1881 */
	.weak vm_datablock_read_buffered; .long vm_datablock_read_buffered
	.reloc ., R_386_SIZE32, vm_datablock_read_buffered; .long 0
	.long 0xff403e4
	.long 0 /* index: 1882 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1883 */
	.long 0
	.long 0
	.long 0
	.long .Lname1884 /* index: 1884 */
	.weak coredump_create_for_signal; .long coredump_create_for_signal
	.reloc ., R_386_SIZE32, coredump_create_for_signal; .long 0
	.long 0x81ae75c
	.long 0 /* index: 1885 */
	.long 0
	.long 0
	.long 0
	.long .Lname1886 /* index: 1886 */
	.weak driver_get_state; .long driver_get_state
	.reloc ., R_386_SIZE32, driver_get_state; .long 0
	.long 0x6a84c65
	.long .Lname1887 /* index: 1887 */
	.weak json_encode; .long json_encode
	.reloc ., R_386_SIZE32, json_encode; .long 0
	.long 0x5d543e5
	.long 0 /* index: 1888 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1889 */
	.long 0
	.long 0
	.long 0
	.long .Lname1890 /* index: 1890 */
	.weak superblock_opennode; .long superblock_opennode
	.reloc ., R_386_SIZE32, superblock_opennode; .long 0
	.long 0xf25a8c5
	.long .Lname1891 /* index: 1891 */
	.weak task_waitfor_norpc; .long task_waitfor_norpc
	.reloc ., R_386_SIZE32, task_waitfor_norpc; .long 0
	.long 0xecd6763
	.long .Lname1892 /* index: 1892 */
	.weak vm_tasklock_end; .long vm_tasklock_end
	.reloc ., R_386_SIZE32, vm_tasklock_end; .long 0
	.long 0x349a764
	.long 0 /* index: 1893 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1894 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1895 */
	.long 0
	.long 0
	.long 0
	.long .Lname1896 /* index: 1896 */
	.weak superblock_mountlock_read_nx; .long superblock_mountlock_read_nx
	.reloc ., R_386_SIZE32, superblock_mountlock_read_nx; .long 0
	.long 0x1b6f768
	.long 0 /* index: 1897 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1898 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1899 */
	.long 0
	.long 0
	.long 0
	.long .Lname1900 /* index: 1900 */
	.weak rawmemchrl; .long rawmemchrl
	.reloc ., R_386_SIZE32, rawmemchrl; .long 0
	.long 0x3c4176c
	.long 0 /* index: 1901 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1902 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1903 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1904 */
	.long 0
	.long 0
	.long 0
	.long .Lname1905 /* index: 1905 */
	.weak rawmemchrq; .long rawmemchrq
	.reloc ., R_386_SIZE32, rawmemchrq; .long 0
	.long 0x3c41771
	.long 0 /* index: 1906 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1907 */
	.long 0
	.long 0
	.long 0
	.long .Lname1908 /* index: 1908 */
	.weak cpu_quantum_offset; .long cpu_quantum_offset
	.reloc ., R_386_SIZE32, cpu_quantum_offset; .long 0
	.long 0x9bed774
	.long .Lname1909 /* index: 1909 */
	.weak vm_write; .long vm_write
	.reloc ., R_386_SIZE32, vm_write; .long 0
	.long 0x36e9775
	.long 0 /* index: 1910 */
	.long 0
	.long 0
	.long 0
	.long .Lname1911 /* index: 1911 */
	.weak rawmemchrw; .long rawmemchrw
	.reloc ., R_386_SIZE32, rawmemchrw; .long 0
	.long 0x3c41777
	.long 0 /* index: 1912 */
	.long 0
	.long 0
	.long 0
	.long .Lname1913 /* index: 1913 */
	.weak sys_maplibrary; .long sys_maplibrary
	.reloc ., R_386_SIZE32, sys_maplibrary; .long 0
	.long 0x26fb779
	.long 0 /* index: 1914 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1915 */
	.long 0
	.long 0
	.long 0
	.long .Lname1916 /* index: 1916 */
	.weak kmemalign_nx; .long kmemalign_nx
	.reloc ., R_386_SIZE32, kmemalign_nx; .long 0
	.long 0x5e007d8
	.long 0 /* index: 1917 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1918 */
	.long 0
	.long 0
	.long 0
	.long .Lname1919 /* index: 1919 */
	.weak task_wake; .long task_wake
	.reloc ., R_386_SIZE32, task_wake; .long 0
	.long 0xa16ae95
	.long 0 /* index: 1920 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1921 */
	.long 0
	.long 0
	.long 0
	.long .Lname1922 /* index: 1922 */
	.weak sys_setgroups32; .long sys_setgroups32
	.reloc ., R_386_SIZE32, sys_setgroups32; .long 0
	.long 0x205c782
	.long 0 /* index: 1923 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1924 */
	.long 0
	.long 0
	.long 0
	.long .Lname1925 /* index: 1925 */
	.weak debuginfo_cu_parser_loadattr_inlined_subroutine; .long debuginfo_cu_parser_loadattr_inlined_subroutine
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_inlined_subroutine; .long 0
	.long 0x75785
	.long 0 /* index: 1926 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1927 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1928 */
	.long 0
	.long 0
	.long 0
	.long .Lname1929 /* index: 1929 */
	.weak vm_mapat; .long vm_mapat
	.reloc ., R_386_SIZE32, vm_mapat; .long 0
	.long 0x3638154
	.long 0 /* index: 1930 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1931 */
	.long 0
	.long 0
	.long 0
	.long .Lname1932 /* index: 1932 */
	.weak memcpyl; .long memcpyl
	.reloc ., R_386_SIZE32, memcpyl; .long 0
	.long 0x3c3a78c
	.long .Lname1933 /* index: 1933 */
	.weak devfs_insert; .long devfs_insert
	.reloc ., R_386_SIZE32, devfs_insert; .long 0
	.long 0x3695104
	.long 0 /* index: 1934 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1935 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1936 */
	.long 0
	.long 0
	.long 0
	.long .Lname1937 /* index: 1937 */
	.weak sprintf_s; .long sprintf_s
	.reloc ., R_386_SIZE32, sprintf_s; .long 0
	.long 0x905d213
	.long 0 /* index: 1938 */
	.long 0
	.long 0
	.long 0
	.long .Lname1939 /* index: 1939 */
	.weak task_raisesignalprocess; .long task_raisesignalprocess
	.reloc ., R_386_SIZE32, task_raisesignalprocess; .long 0
	.long 0x8915943
	.long .Lname1940 /* index: 1940 */
	.weak sys_setitimer64; .long sys_setitimer64
	.reloc ., R_386_SIZE32, sys_setitimer64; .long 0
	.long 0x3aa7794
	.long .Lname1941 /* index: 1941 */
	.weak block_device_lookup_name; .long block_device_lookup_name
	.reloc ., R_386_SIZE32, block_device_lookup_name; .long 0
	.long 0x63c9795
	.long .Lname1942 /* index: 1942 */
	.weak vm_getnodeof; .long vm_getnodeof
	.reloc ., R_386_SIZE32, vm_getnodeof; .long 0
	.long 0xea6f796
	.long 0 /* index: 1943 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1944 */
	.long 0
	.long 0
	.long 0
	.long .Lname1945 /* index: 1945 */
	.weak vm_datablock_destroy; .long vm_datablock_destroy
	.reloc ., R_386_SIZE32, vm_datablock_destroy; .long 0
	.long 0x6459799
	.long .Lname1946 /* index: 1946 */
	.weak sys_getpriority; .long sys_getpriority
	.reloc ., R_386_SIZE32, sys_getpriority; .long 0
	.long 0x1bb40c9
	.long .Lname1947 /* index: 1947 */
	.weak sys_getrlimit; .long sys_getrlimit
	.reloc ., R_386_SIZE32, sys_getrlimit; .long 0
	.long 0x9bbfb4
	.long .Lname1948 /* index: 1948 */
	.weak __afail; .long __afail
	.reloc ., R_386_SIZE32, __afail; .long 0
	.long 0x557c79c
	.long 0 /* index: 1949 */
	.long 0
	.long 0
	.long 0
	.long .Lname1950 /* index: 1950 */
	.weak sys_sched_get_priority_min; .long sys_sched_get_priority_min
	.reloc ., R_386_SIZE32, sys_sched_get_priority_min; .long 0
	.long 0xdd6a79e
	.long .Lname1951 /* index: 1951 */
	.weak sys_vmsplice; .long sys_vmsplice
	.reloc ., R_386_SIZE32, sys_vmsplice; .long 0
	.long 0x317b945
	.long .Lname1952 /* index: 1952 */
	.weak sys_vhangup; .long sys_vhangup
	.reloc ., R_386_SIZE32, sys_vhangup; .long 0
	.long 0xc9d47a0
	.long 0 /* index: 1953 */
	.long 0
	.long 0
	.long 0
	.long .Lname1954 /* index: 1954 */
	.weak dbg_printer; .long dbg_printer
	.reloc ., R_386_SIZE32, dbg_printer; .long 0
	.long 0x7e6d7a2
	.long .Lname1955 /* index: 1955 */
	.weak sys_flock; .long sys_flock
	.reloc ., R_386_SIZE32, sys_flock; .long 0
	.long 0x95d6e9b
	.long .Lname1956 /* index: 1956 */
	.weak sigmask_check_after_except; .long sigmask_check_after_except
	.reloc ., R_386_SIZE32, sigmask_check_after_except; .long 0
	.long 0xace07a4
	.long .Lname1957 /* index: 1957 */
	.weak kernel_debugtrap_r_kcpustate; .long kernel_debugtrap_r_kcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_kcpustate; .long 0
	.long 0xed517a5
	.long 0 /* index: 1958 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1959 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1960 */
	.long 0
	.long 0
	.long 0
	.long .Lname1961 /* index: 1961 */
	.weak _this_x86_dr3; .long _this_x86_dr3
	.reloc ., R_386_SIZE32, _this_x86_dr3; .long 0
	.long 0xd155253
	.long 0 /* index: 1962 */
	.long 0
	.long 0
	.long 0
	.long .Lname1963 /* index: 1963 */
	.weak vm_sync_end; .long vm_sync_end
	.reloc ., R_386_SIZE32, vm_sync_end; .long 0
	.long 0x366ef4
	.long 0 /* index: 1964 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1965 */
	.long 0
	.long 0
	.long 0
	.long .Lname1966 /* index: 1966 */
	.weak sighand_default_action; .long sighand_default_action
	.reloc ., R_386_SIZE32, sighand_default_action; .long 0
	.long 0x3117ae
	.long 0 /* index: 1967 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1968 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1969 */
	.long 0
	.long 0
	.long 0
	.long .Lname1970 /* index: 1970 */
	.weak unicode_8to32; .long unicode_8to32
	.reloc ., R_386_SIZE32, unicode_8to32; .long 0
	.long 0x76017b2
	.long .Lname1971 /* index: 1971 */
	.weak aio_pbuffer_copyfromphys; .long aio_pbuffer_copyfromphys
	.reloc ., R_386_SIZE32, aio_pbuffer_copyfromphys; .long 0
	.long 0x3fe8bf3
	.long 0 /* index: 1972 */
	.long 0
	.long 0
	.long 0
	.long .Lname1973 /* index: 1973 */
	.weak regdump_lcpustate; .long regdump_lcpustate
	.reloc ., R_386_SIZE32, regdump_lcpustate; .long 0
	.long 0xbf457b5
	.long 0 /* index: 1974 */
	.long 0
	.long 0
	.long 0
	.long .Lname1975 /* index: 1975 */
	.weak vpage_ffree; .long vpage_ffree
	.reloc ., R_386_SIZE32, vpage_ffree; .long 0
	.long 0xb21bf65
	.long 0 /* index: 1976 */
	.long 0
	.long 0
	.long 0
	.long .Lname1977 /* index: 1977 */
	.weak handle_lookup; .long handle_lookup
	.reloc ., R_386_SIZE32, handle_lookup; .long 0
	.long 0xcb2f010
	.long 0 /* index: 1978 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1979 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1980 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1981 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1982 */
	.long 0
	.long 0
	.long 0
	.long .Lname1983 /* index: 1983 */
	.weak kernel_debugtrap_lcpustate; .long kernel_debugtrap_lcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_lcpustate; .long 0
	.long 0x96393f5
	.long .Lname1984 /* index: 1984 */
	.weak vm86_step; .long vm86_step
	.reloc ., R_386_SIZE32, vm86_step; .long 0
	.long 0xbc6d7c0
	.long 0 /* index: 1985 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1986 */
	.long 0
	.long 0
	.long 0
	.long .Lname1987 /* index: 1987 */
	.weak terminal_setios; .long terminal_setios
	.reloc ., R_386_SIZE32, terminal_setios; .long 0
	.long 0xfdc9283
	.long .Lname1988 /* index: 1988 */
	.weak pci_list; .long pci_list
	.reloc ., R_386_SIZE32, pci_list; .long 0
	.long 0x9f637c4
	.long .Lname1989 /* index: 1989 */
	.weak block_device_partition_write; .long block_device_partition_write
	.reloc ., R_386_SIZE32, block_device_partition_write; .long 0
	.long 0x5487c5
	.long 0 /* index: 1990 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1991 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1992 */
	.long 0
	.long 0
	.long 0
	.long .Lname1993 /* index: 1993 */
	.weak krealloc_nx; .long krealloc_nx
	.reloc ., R_386_SIZE32, krealloc_nx; .long 0
	.long 0x3671fd8
	.long .Lname1994 /* index: 1994 */
	.weak fs_filesystems_lock_read; .long fs_filesystems_lock_read
	.reloc ., R_386_SIZE32, fs_filesystems_lock_read; .long 0
	.long 0xa6b9d94
	.long 0 /* index: 1995 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1996 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 1997 */
	.long 0
	.long 0
	.long 0
	.long .Lname1998 /* index: 1998 */
	.weak sys_swapon; .long sys_swapon
	.reloc ., R_386_SIZE32, sys_swapon; .long 0
	.long 0x6aa37ce
	.long 0 /* index: 1999 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2000 */
	.long 0
	.long 0
	.long 0
	.long .Lname2001 /* index: 2001 */
	.weak vm_library_enumerate; .long vm_library_enumerate
	.reloc ., R_386_SIZE32, vm_library_enumerate; .long 0
	.long 0x1c12ea5
	.long 0 /* index: 2002 */
	.long 0
	.long 0
	.long 0
	.long .Lname2003 /* index: 2003 */
	.weak dbg_exitstate; .long dbg_exitstate
	.reloc ., R_386_SIZE32, dbg_exitstate; .long 0
	.long 0xa37f435
	.long .Lname2004 /* index: 2004 */
	.weak unwind_fde_find; .long unwind_fde_find
	.reloc ., R_386_SIZE32, unwind_fde_find; .long 0
	.long 0x4b137d4
	.long .Lname2005 /* index: 2005 */
	.weak ramfs_regular_type; .long ramfs_regular_type
	.reloc ., R_386_SIZE32, ramfs_regular_type; .long 0
	.long 0x98577d5
	.long 0 /* index: 2006 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2007 */
	.long 0
	.long 0
	.long 0
	.long .Lname2008 /* index: 2008 */
	.weak kmalloc_nx; .long kmalloc_nx
	.reloc ., R_386_SIZE32, kmalloc_nx; .long 0
	.long 0x332b7d8
	.long 0 /* index: 2009 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2010 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2011 */
	.long 0
	.long 0
	.long 0
	.long .Lname2012 /* index: 2012 */
	.weak x86_vm86_outl; .long x86_vm86_outl
	.reloc ., R_386_SIZE32, x86_vm86_outl; .long 0
	.long 0x1a01dc
	.long 0 /* index: 2013 */
	.long 0
	.long 0
	.long 0
	.long .Lname2014 /* index: 2014 */
	.weak sys_sigaction; .long sys_sigaction
	.reloc ., R_386_SIZE32, sys_sigaction; .long 0
	.long 0x673c7de
	.long .Lname2015 /* index: 2015 */
	.weak register_filesystem_type; .long register_filesystem_type
	.reloc ., R_386_SIZE32, register_filesystem_type; .long 0
	.long 0x5be16a5
	.long .Lname2016 /* index: 2016 */
	.weak sys_wait4; .long sys_wait4
	.reloc ., R_386_SIZE32, sys_wait4; .long 0
	.long 0x96d1b74
	.long 0 /* index: 2017 */
	.long 0
	.long 0
	.long 0
	.long .Lname2018 /* index: 2018 */
	.weak sys_getresuid32; .long sys_getresuid32
	.reloc ., R_386_SIZE32, sys_getresuid32; .long 0
	.long 0x5f647e2
	.long .Lname2019 /* index: 2019 */
	.weak superblock_sync; .long superblock_sync
	.reloc ., R_386_SIZE32, superblock_sync; .long 0
	.long 0xdfa7e3
	.long .Lname2020 /* index: 2020 */
	.weak regdump_cr4; .long regdump_cr4
	.reloc ., R_386_SIZE32, regdump_cr4; .long 0
	.long 0xc3ee7e4
	.long .Lname2021 /* index: 2021 */
	.weak pci_getclassname; .long pci_getclassname
	.reloc ., R_386_SIZE32, pci_getclassname; .long 0
	.long 0xd7387e5
	.long .Lname2022 /* index: 2022 */
	.weak vmb_getnodeof; .long vmb_getnodeof
	.reloc ., R_386_SIZE32, vmb_getnodeof; .long 0
	.long 0x88df7e6
	.long 0 /* index: 2023 */
	.long 0
	.long 0
	.long 0
	.long .Lname2024 /* index: 2024 */
	.weak sys_mount; .long sys_mount
	.reloc ., R_386_SIZE32, sys_mount; .long 0
	.long 0x9641154
	.long 0 /* index: 2025 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2026 */
	.long 0
	.long 0
	.long 0
	.long .Lname2027 /* index: 2027 */
	.weak pidns_lookup_task; .long pidns_lookup_task
	.reloc ., R_386_SIZE32, pidns_lookup_task; .long 0
	.long 0x57317eb
	.long 0 /* index: 2028 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2029 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2030 */
	.long 0
	.long 0
	.long 0
	.long .Lname2031 /* index: 2031 */
	.weak swap_free; .long swap_free
	.reloc ., R_386_SIZE32, swap_free; .long 0
	.long 0x865a265
	.long 0 /* index: 2032 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2033 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2034 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2035 */
	.long 0
	.long 0
	.long 0
	.long .Lname2036 /* index: 2036 */
	.weak inode_chmod; .long inode_chmod
	.reloc ., R_386_SIZE32, inode_chmod; .long 0
	.long 0xb29c7f4
	.long 0 /* index: 2037 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2038 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2039 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2040 */
	.long 0
	.long 0
	.long 0
	.long .Lname2041 /* index: 2041 */
	.weak debuginfo_cu_parser_loadunit; .long debuginfo_cu_parser_loadunit
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadunit; .long 0
	.long 0x295c954
	.long 0 /* index: 2042 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2043 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2044 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2045 */
	.long 0
	.long 0
	.long 0
	.long .Lname2046 /* index: 2046 */
	.weak superblock_nodeslock_upgrade; .long superblock_nodeslock_upgrade
	.reloc ., R_386_SIZE32, superblock_nodeslock_upgrade; .long 0
	.long 0xa6ee605
	.long 0 /* index: 2047 */
	.long 0
	.long 0
	.long 0
	.long .Lname2048 /* index: 2048 */
	.weak sys_getresgid; .long sys_getresgid
	.reloc ., R_386_SIZE32, sys_getresgid; .long 0
	.long 0x85c044
	.long .Lname2049 /* index: 2049 */
	.weak vm_kernel_treelock_read; .long vm_kernel_treelock_read
	.reloc ., R_386_SIZE32, vm_kernel_treelock_read; .long 0
	.long 0x94b044
	.long 0 /* index: 2050 */
	.long 0
	.long 0
	.long 0
	.long .Lname2051 /* index: 2051 */
	.weak regdump_sgregs; .long regdump_sgregs
	.reloc ., R_386_SIZE32, regdump_sgregs; .long 0
	.long 0xd454803
	.long .Lname2052 /* index: 2052 */
	.weak handle_typekind; .long handle_typekind
	.reloc ., R_386_SIZE32, handle_typekind; .long 0
	.long 0x4dac804
	.long .Lname2053 /* index: 2053 */
	.weak block_device_awrite; .long block_device_awrite
	.reloc ., R_386_SIZE32, block_device_awrite; .long 0
	.long 0x677e805
	.long .Lname2054 /* index: 2054 */
	.weak vsnprintf; .long vsnprintf
	.reloc ., R_386_SIZE32, vsnprintf; .long 0
	.long 0x5789806
	.long 0 /* index: 2055 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2056 */
	.long 0
	.long 0
	.long 0
	.long .Lname2057 /* index: 2057 */
	.weak inode_areadall; .long inode_areadall
	.reloc ., R_386_SIZE32, inode_areadall; .long 0
	.long 0xded16ac
	.long 0 /* index: 2058 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2059 */
	.long 0
	.long 0
	.long 0
	.long .Lname2060 /* index: 2060 */
	.weak x86_fpustate_variant; .long x86_fpustate_variant
	.reloc ., R_386_SIZE32, x86_fpustate_variant; .long 0
	.long 0xde58d44
	.long 0 /* index: 2061 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2062 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2063 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2064 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2065 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2066 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2067 */
	.long 0
	.long 0
	.long 0
	.long .Lname2068 /* index: 2068 */
	.weak keyboard_device_read; .long keyboard_device_read
	.reloc ., R_386_SIZE32, keyboard_device_read; .long 0
	.long 0xf151814
	.long .Lname2069 /* index: 2069 */
	.weak debuginfo_cu_parser_loadattr_type; .long debuginfo_cu_parser_loadattr_type
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_type; .long 0
	.long 0xe700815
	.long 0 /* index: 2070 */
	.long 0
	.long 0
	.long 0
	.long .Lname2071 /* index: 2071 */
	.weak sys_sigpending; .long sys_sigpending
	.reloc ., R_386_SIZE32, sys_sigpending; .long 0
	.long 0x6323817
	.long .Lname2072 /* index: 2072 */
	.weak heap_realign_untraced_nx; .long heap_realign_untraced_nx
	.reloc ., R_386_SIZE32, heap_realign_untraced_nx; .long 0
	.long 0x9ac7818
	.long .Lname2073 /* index: 2073 */
	.weak block_device_partition_read; .long block_device_partition_read
	.reloc ., R_386_SIZE32, block_device_partition_read; .long 0
	.long 0x6052404
	.long 0 /* index: 2074 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2075 */
	.long 0
	.long 0
	.long 0
	.long .Lname2076 /* index: 2076 */
	.weak json_parser_getbool; .long json_parser_getbool
	.reloc ., R_386_SIZE32, json_parser_getbool; .long 0
	.long 0x4f5181c
	.long .Lname2077 /* index: 2077 */
	.weak aio_pbuffer_copytomem; .long aio_pbuffer_copytomem
	.reloc ., R_386_SIZE32, aio_pbuffer_copytomem; .long 0
	.long 0xfaa081d
	.long 0 /* index: 2078 */
	.long 0
	.long 0
	.long 0
	.long .Lname2079 /* index: 2079 */
	.weak sys_fcntl64; .long sys_fcntl64
	.reloc ., R_386_SIZE32, sys_fcntl64; .long 0
	.long 0xcfea6c4
	.long .Lname2080 /* index: 2080 */
	.weak vm_datablock_writep; .long vm_datablock_writep
	.reloc ., R_386_SIZE32, vm_datablock_writep; .long 0
	.long 0xc21f820
	.long 0 /* index: 2081 */
	.long 0
	.long 0
	.long 0
	.long .Lname2082 /* index: 2082 */
	.weak handle_type_db; .long handle_type_db
	.reloc ., R_386_SIZE32, handle_type_db; .long 0
	.long 0x44d9822
	.long .Lname2083 /* index: 2083 */
	.weak handle_lookup_nosym; .long handle_lookup_nosym
	.reloc ., R_386_SIZE32, handle_lookup_nosym; .long 0
	.long 0xaf79aed
	.long .Lname2084 /* index: 2084 */
	.weak memeq_ku_nopf; .long memeq_ku_nopf
	.reloc ., R_386_SIZE32, memeq_ku_nopf; .long 0
	.long 0x1779156
	.long .Lname2085 /* index: 2085 */
	.weak sys_nice; .long sys_nice
	.reloc ., R_386_SIZE32, sys_nice; .long 0
	.long 0x964825
	.long .Lname2086 /* index: 2086 */
	.weak vm_datablock_writev; .long vm_datablock_writev
	.reloc ., R_386_SIZE32, vm_datablock_writev; .long 0
	.long 0xc21f826
	.long .Lname2087 /* index: 2087 */
	.weak driver_fde_find; .long driver_fde_find
	.reloc ., R_386_SIZE32, driver_fde_find; .long 0
	.long 0xa79e214
	.long 0 /* index: 2088 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2089 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2090 */
	.long 0
	.long 0
	.long 0
	.long .Lname2091 /* index: 2091 */
	.weak vsprintf; .long vsprintf
	.reloc ., R_386_SIZE32, vsprintf; .long 0
	.long 0xa790276
	.long 0 /* index: 2092 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2093 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2094 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2095 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2096 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2097 */
	.long 0
	.long 0
	.long 0
	.long .Lname2098 /* index: 2098 */
	.weak sys_chown32; .long sys_chown32
	.reloc ., R_386_SIZE32, sys_chown32; .long 0
	.long 0x9ade832
	.long 0 /* index: 2099 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2100 */
	.long 0
	.long 0
	.long 0
	.long .Lname2101 /* index: 2101 */
	.weak _this_trampoline_page; .long _this_trampoline_page
	.reloc ., R_386_SIZE32, _this_trampoline_page; .long 0
	.long 0xe060835
	.long .Lname2102 /* index: 2102 */
	.weak regdump_drregs; .long regdump_drregs
	.reloc ., R_386_SIZE32, regdump_drregs; .long 0
	.long 0xe624803
	.long 0 /* index: 2103 */
	.long 0
	.long 0
	.long 0
	.long .Lname2104 /* index: 2104 */
	.weak format_width; .long format_width
	.reloc ., R_386_SIZE32, format_width; .long 0
	.long 0xbb6838
	.long .Lname2105 /* index: 2105 */
	.weak ttybase_device_cinit; .long ttybase_device_cinit
	.reloc ., R_386_SIZE32, ttybase_device_cinit; .long 0
	.long 0x50dc6b4
	.long 0 /* index: 2106 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2107 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2108 */
	.long 0
	.long 0
	.long 0
	.long .Lname2109 /* index: 2109 */
	.weak sys_fchdirat; .long sys_fchdirat
	.reloc ., R_386_SIZE32, sys_fchdirat; .long 0
	.long 0xe5b9d44
	.long .Lname2110 /* index: 2110 */
	.weak mall_untrace_n; .long mall_untrace_n
	.reloc ., R_386_SIZE32, mall_untrace_n; .long 0
	.long 0x3b5f83e
	.long .Lname2111 /* index: 2111 */
	.weak regdump_ucpustate; .long regdump_ucpustate
	.reloc ., R_386_SIZE32, regdump_ucpustate; .long 0
	.long 0xbf47eb5
	.long .Lname2112 /* index: 2112 */
	.weak superblock_mountlock_tryread; .long superblock_mountlock_tryread
	.reloc ., R_386_SIZE32, superblock_mountlock_tryread; .long 0
	.long 0x2a1f844
	.long 0 /* index: 2113 */
	.long 0
	.long 0
	.long 0
	.long .Lname2114 /* index: 2114 */
	.weak isr_unregister; .long isr_unregister
	.reloc ., R_386_SIZE32, isr_unregister; .long 0
	.long 0x1666842
	.long .Lname2115 /* index: 2115 */
	.weak dump_branch_stats; .long dump_branch_stats
	.reloc ., R_386_SIZE32, dump_branch_stats; .long 0
	.long 0x9996843
	.long .Lname2116 /* index: 2116 */
	.weak json_writer_putint64; .long json_writer_putint64
	.reloc ., R_386_SIZE32, json_writer_putint64; .long 0
	.long 0x6687844
	.long .Lname2117 /* index: 2117 */
	.weak kernel_vpanic_icpustate; .long kernel_vpanic_icpustate
	.reloc ., R_386_SIZE32, kernel_vpanic_icpustate; .long 0
	.long 0xf5ae845
	.long 0 /* index: 2118 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2119 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2120 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2121 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2122 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2123 */
	.long 0
	.long 0
	.long 0
	.long .Lname2124 /* index: 2124 */
	.weak ansitty_device_ioctl; .long ansitty_device_ioctl
	.reloc ., R_386_SIZE32, ansitty_device_ioctl; .long 0
	.long 0xb54284c
	.long 0 /* index: 2125 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2126 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2127 */
	.long 0
	.long 0
	.long 0
	.long .Lname2128 /* index: 2128 */
	.weak pagedir_maphint_p; .long pagedir_maphint_p
	.reloc ., R_386_SIZE32, pagedir_maphint_p; .long 0
	.long 0xd9e6850
	.long .Lname2129 /* index: 2129 */
	.weak task_alloc_synchronous_rpc; .long task_alloc_synchronous_rpc
	.reloc ., R_386_SIZE32, task_alloc_synchronous_rpc; .long 0
	.long 0x9aea623
	.long .Lname2130 /* index: 2130 */
	.weak sys_lsetxattr; .long sys_lsetxattr
	.reloc ., R_386_SIZE32, sys_lsetxattr; .long 0
	.long 0x7b7e852
	.long .Lname2131 /* index: 2131 */
	.weak task_connect; .long task_connect
	.reloc ., R_386_SIZE32, task_connect; .long 0
	.long 0xdeac4
	.long .Lname2132 /* index: 2132 */
	.weak sys_clock_nanosleep64; .long sys_clock_nanosleep64
	.reloc ., R_386_SIZE32, sys_clock_nanosleep64; .long 0
	.long 0x435e854
	.long .Lname2133 /* index: 2133 */
	.weak sys_getpeername; .long sys_getpeername
	.reloc ., R_386_SIZE32, sys_getpeername; .long 0
	.long 0x296f855
	.long 0 /* index: 2134 */
	.long 0
	.long 0
	.long 0
	.long .Lname2135 /* index: 2135 */
	.weak sys_stime64; .long sys_stime64
	.reloc ., R_386_SIZE32, sys_stime64; .long 0
	.long 0xad531f4
	.long 0 /* index: 2136 */
	.long 0
	.long 0
	.long 0
	.long .Lname2137 /* index: 2137 */
	.weak sys_getsid; .long sys_getsid
	.reloc ., R_386_SIZE32, sys_getsid; .long 0
	.long 0x5db0964
	.long 0 /* index: 2138 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2139 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2140 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2141 */
	.long 0
	.long 0
	.long 0
	.long .Lname2142 /* index: 2142 */
	.weak path_lock_trywrite; .long path_lock_trywrite
	.reloc ., R_386_SIZE32, path_lock_trywrite; .long 0
	.long 0x3c4845
	.long .Lname2143 /* index: 2143 */
	.weak format_escape; .long format_escape
	.reloc ., R_386_SIZE32, format_escape; .long 0
	.long 0x8a0a165
	.long 0 /* index: 2144 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2145 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2146 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2147 */
	.long 0
	.long 0
	.long 0
	.long .Lname2148 /* index: 2148 */
	.weak keyboard_device_init; .long keyboard_device_init
	.reloc ., R_386_SIZE32, keyboard_device_init; .long 0
	.long 0xf167864
	.long 0 /* index: 2149 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2150 */
	.long 0
	.long 0
	.long 0
	.long .Lname2151 /* index: 2151 */
	.weak handle_installxchg; .long handle_installxchg
	.reloc ., R_386_SIZE32, handle_installxchg; .long 0
	.long 0xbabf867
	.long 0 /* index: 2152 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2153 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2154 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2155 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2156 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2157 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2158 */
	.long 0
	.long 0
	.long 0
	.long .Lname2159 /* index: 2159 */
	.weak _strtoui64; .long _strtoui64
	.reloc ., R_386_SIZE32, _strtoui64; .long 0
	.long 0x9b0d624
	.long .Lname2160 /* index: 2160 */
	.weak pagedir_unmap_p; .long pagedir_unmap_p
	.reloc ., R_386_SIZE32, pagedir_unmap_p; .long 0
	.long 0x808f870
	.long .Lname2161 /* index: 2161 */
	.weak memcpyq; .long memcpyq
	.reloc ., R_386_SIZE32, memcpyq; .long 0
	.long 0x3c3a871
	.long 0 /* index: 2162 */
	.long 0
	.long 0
	.long 0
	.long .Lname2163 /* index: 2163 */
	.weak block_device_partition_write_phys; .long block_device_partition_write_phys
	.reloc ., R_386_SIZE32, block_device_partition_write_phys; .long 0
	.long 0xcb32873
	.long .Lname2164 /* index: 2164 */
	.weak superblock_mountlock_endread; .long superblock_mountlock_endread
	.reloc ., R_386_SIZE32, superblock_mountlock_endread; .long 0
	.long 0x34af874
	.long .Lname2165 /* index: 2165 */
	.weak disasm_single; .long disasm_single
	.reloc ., R_386_SIZE32, disasm_single; .long 0
	.long 0xd97c875
	.long .Lname2166 /* index: 2166 */
	.weak cpu_schedule_idle_job_and_incref; .long cpu_schedule_idle_job_and_incref
	.reloc ., R_386_SIZE32, cpu_schedule_idle_job_and_incref; .long 0
	.long 0x33dc876
	.long .Lname2167 /* index: 2167 */
	.weak memcpyw; .long memcpyw
	.reloc ., R_386_SIZE32, memcpyw; .long 0
	.long 0x3c3a877
	.long .Lname2168 /* index: 2168 */
	.weak krealign_in_place_offset_nx; .long krealign_in_place_offset_nx
	.reloc ., R_386_SIZE32, krealign_in_place_offset_nx; .long 0
	.long 0x4853878
	.long .Lname2169 /* index: 2169 */
	.weak ringbuffer_skipread; .long ringbuffer_skipread
	.reloc ., R_386_SIZE32, ringbuffer_skipread; .long 0
	.long 0x5cf3414
	.long 0 /* index: 2170 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2171 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2172 */
	.long 0
	.long 0
	.long 0
	.long .Lname2173 /* index: 2173 */
	.weak sys_sched_setparam; .long sys_sched_setparam
	.reloc ., R_386_SIZE32, sys_sched_setparam; .long 0
	.long 0x2ed987d
	.long 0 /* index: 2174 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2175 */
	.long 0
	.long 0
	.long 0
	.long .Lname2176 /* index: 2176 */
	.weak ttybase_device_owrite; .long ttybase_device_owrite
	.reloc ., R_386_SIZE32, ttybase_device_owrite; .long 0
	.long 0x12aabf5
	.long .Lname2177 /* index: 2177 */
	.weak sys_getuid; .long sys_getuid
	.reloc ., R_386_SIZE32, sys_getuid; .long 0
	.long 0x5db0b64
	.long .Lname2178 /* index: 2178 */
	.weak inode_loadattr; .long inode_loadattr
	.reloc ., R_386_SIZE32, inode_loadattr; .long 0
	.long 0x203882
	.long .Lname2179 /* index: 2179 */
	.weak kernel_vpanic; .long kernel_vpanic
	.reloc ., R_386_SIZE32, kernel_vpanic; .long 0
	.long 0x71f4883
	.long .Lname2180 /* index: 2180 */
	.weak vm_get_aslr_disabled; .long vm_get_aslr_disabled
	.reloc ., R_386_SIZE32, vm_get_aslr_disabled; .long 0
	.long 0xb495884
	.long 0 /* index: 2181 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2182 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2183 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2184 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2185 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2186 */
	.long 0
	.long 0
	.long 0
	.long .Lname2187 /* index: 2187 */
	.weak vm_clrhwbreak; .long vm_clrhwbreak
	.reloc ., R_386_SIZE32, vm_clrhwbreak; .long 0
	.long 0x2ec288b
	.long .Lname2188 /* index: 2188 */
	.weak disasm_print_symbol; .long disasm_print_symbol
	.reloc ., R_386_SIZE32, disasm_print_symbol; .long 0
	.long 0xbdfb88c
	.long .Lname2189 /* index: 2189 */
	.weak block_device_areadv_phys_sector; .long block_device_areadv_phys_sector
	.reloc ., R_386_SIZE32, block_device_areadv_phys_sector; .long 0
	.long 0x88c86c2
	.long 0 /* index: 2190 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2191 */
	.long 0
	.long 0
	.long 0
	.long .Lname2192 /* index: 2192 */
	.weak vm_datablock_readp; .long vm_datablock_readp
	.reloc ., R_386_SIZE32, vm_datablock_readp; .long 0
	.long 0xec43890
	.long 0 /* index: 2193 */
	.long 0
	.long 0
	.long 0
	.long .Lname2194 /* index: 2194 */
	.weak directory_mkdir; .long directory_mkdir
	.reloc ., R_386_SIZE32, directory_mkdir; .long 0
	.long 0x7fac892
	.long .Lname2195 /* index: 2195 */
	.weak aio_buffer_copytophys; .long aio_buffer_copytophys
	.reloc ., R_386_SIZE32, aio_buffer_copytophys; .long 0
	.long 0x9aa3ec3
	.long .Lname2196 /* index: 2196 */
	.weak terminal_iread; .long terminal_iread
	.reloc ., R_386_SIZE32, terminal_iread; .long 0
	.long 0xed48894
	.long .Lname2197 /* index: 2197 */
	.weak sys_getsockname; .long sys_getsockname
	.reloc ., R_386_SIZE32, sys_getsockname; .long 0
	.long 0xcddf895
	.long .Lname2198 /* index: 2198 */
	.weak vm_datablock_readv; .long vm_datablock_readv
	.reloc ., R_386_SIZE32, vm_datablock_readv; .long 0
	.long 0xec43896
	.long .Lname2199 /* index: 2199 */
	.weak sys_clock_gettime64; .long sys_clock_gettime64
	.reloc ., R_386_SIZE32, sys_clock_gettime64; .long 0
	.long 0x5063f34
	.long .Lname2200 /* index: 2200 */
	.weak task_schedule_user_rpc_nx; .long task_schedule_user_rpc_nx
	.reloc ., R_386_SIZE32, task_schedule_user_rpc_nx; .long 0
	.long 0xc9bc898
	.long .Lname2201 /* index: 2201 */
	.weak sig_altbroadcast; .long sig_altbroadcast
	.reloc ., R_386_SIZE32, sig_altbroadcast; .long 0
	.long 0xfeaec4
	.long 0 /* index: 2202 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2203 */
	.long 0
	.long 0
	.long 0
	.long .Lname2204 /* index: 2204 */
	.weak dbg_vline; .long dbg_vline
	.reloc ., R_386_SIZE32, dbg_vline; .long 0
	.long 0xd6d46c5
	.long .Lname2205 /* index: 2205 */
	.weak disasm; .long disasm
	.reloc ., R_386_SIZE32, disasm; .long 0
	.long 0x6b0989d
	.long 0 /* index: 2206 */
	.long 0
	.long 0
	.long 0
	.long .Lname2207 /* index: 2207 */
	.weak dbg_hline; .long dbg_hline
	.reloc ., R_386_SIZE32, dbg_hline; .long 0
	.long 0xd5f46c5
	.long .Lname2208 /* index: 2208 */
	.weak pagedir_haschanged_p; .long pagedir_haschanged_p
	.reloc ., R_386_SIZE32, pagedir_haschanged_p; .long 0
	.long 0x67e98a0
	.long .Lname2209 /* index: 2209 */
	.weak memrchrq; .long memrchrq
	.reloc ., R_386_SIZE32, memrchrq; .long 0
	.long 0xc4898a1
	.long 0 /* index: 2210 */
	.long 0
	.long 0
	.long 0
	.long .Lname2211 /* index: 2211 */
	.weak kernel_debug_sections; .long kernel_debug_sections
	.reloc ., R_386_SIZE32, kernel_debug_sections; .long 0
	.long 0x97d48a3
	.long .Lname2212 /* index: 2212 */
	.weak sys_linux_fstatat64; .long sys_linux_fstatat64
	.reloc ., R_386_SIZE32, sys_linux_fstatat64; .long 0
	.long 0x44fb8a4
	.long .Lname2213 /* index: 2213 */
	.weak sys_rename; .long sys_rename
	.reloc ., R_386_SIZE32, sys_rename; .long 0
	.long 0x68df8a5
	.long 0 /* index: 2214 */
	.long 0
	.long 0
	.long 0
	.long .Lname2215 /* index: 2215 */
	.weak dbg_trygetc; .long dbg_trygetc
	.reloc ., R_386_SIZE32, dbg_trygetc; .long 0
	.long 0xbf551c3
	.long 0 /* index: 2216 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2217 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2218 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2219 */
	.long 0
	.long 0
	.long 0
	.long .Lname2220 /* index: 2220 */
	.weak json_writer_putbool; .long json_writer_putbool
	.reloc ., R_386_SIZE32, json_writer_putbool; .long 0
	.long 0xd6618ac
	.long 0 /* index: 2221 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2222 */
	.long 0
	.long 0
	.long 0
	.long .Lname2223 /* index: 2223 */
	.weak path_lock_end; .long path_lock_end
	.reloc ., R_386_SIZE32, path_lock_end; .long 0
	.long 0x32bbe24
	.long 0 /* index: 2224 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2225 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2226 */
	.long 0
	.long 0
	.long 0
	.long .Lname2227 /* index: 2227 */
	.weak vm_datablock_sync; .long vm_datablock_sync
	.reloc ., R_386_SIZE32, vm_datablock_sync; .long 0
	.long 0x2ec68b3
	.long 0 /* index: 2228 */
	.long 0
	.long 0
	.long 0
	.long .Lname2229 /* index: 2229 */
	.weak linebuffer_writesome; .long linebuffer_writesome
	.reloc ., R_386_SIZE32, linebuffer_writesome; .long 0
	.long 0xc2178b5
	.long 0 /* index: 2230 */
	.long 0
	.long 0
	.long 0
	.long .Lname2231 /* index: 2231 */
	.weak rwlock_reading; .long rwlock_reading
	.reloc ., R_386_SIZE32, rwlock_reading; .long 0
	.long 0x68208b7
	.long 0 /* index: 2232 */
	.long 0
	.long 0
	.long 0
	.long .Lname2233 /* index: 2233 */
	.weak x86_cpuldt; .long x86_cpuldt
	.reloc ., R_386_SIZE32, x86_cpuldt; .long 0
	.long 0x5a01974
	.long 0 /* index: 2234 */
	.long 0
	.long 0
	.long 0
	.long .Lname2235 /* index: 2235 */
	.weak directory_rename; .long directory_rename
	.reloc ., R_386_SIZE32, directory_rename; .long 0
	.long 0xd279f45
	.long .Lname2236 /* index: 2236 */
	.weak memrchrl; .long memrchrl
	.reloc ., R_386_SIZE32, memrchrl; .long 0
	.long 0xc4898bc
	.long 0 /* index: 2237 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2238 */
	.long 0
	.long 0
	.long 0
	.long .Lname2239 /* index: 2239 */
	.weak pidns_trywrite; .long pidns_trywrite
	.reloc ., R_386_SIZE32, pidns_trywrite; .long 0
	.long 0x7bb2175
	.long 0 /* index: 2240 */
	.long 0
	.long 0
	.long 0
	.long .Lname2241 /* index: 2241 */
	.weak mempatq; .long mempatq
	.reloc ., R_386_SIZE32, mempatq; .long 0
	.long 0x3c468c1
	.long .Lname2242 /* index: 2242 */
	.weak sys_listxattr; .long sys_listxattr
	.reloc ., R_386_SIZE32, sys_listxattr; .long 0
	.long 0x1b7e8c2
	.long .Lname2243 /* index: 2243 */
	.weak sys_times; .long sys_times
	.reloc ., R_386_SIZE32, sys_times; .long 0
	.long 0x96a98c3
	.long .Lname2244 /* index: 2244 */
	.weak vm_protect; .long vm_protect
	.reloc ., R_386_SIZE32, vm_protect; .long 0
	.long 0x79178c4
	.long .Lname2245 /* index: 2245 */
	.weak vm_tasklock_endread; .long vm_tasklock_endread
	.reloc ., R_386_SIZE32, vm_tasklock_endread; .long 0
	.long 0x768c2d4
	.long .Lname2246 /* index: 2246 */
	.weak dbg_pprintf; .long dbg_pprintf
	.reloc ., R_386_SIZE32, dbg_pprintf; .long 0
	.long 0x71288c6
	.long .Lname2247 /* index: 2247 */
	.weak mempatw; .long mempatw
	.reloc ., R_386_SIZE32, mempatw; .long 0
	.long 0x3c468c7
	.long .Lname2248 /* index: 2248 */
	.weak heap_allat_untraced_nx; .long heap_allat_untraced_nx
	.reloc ., R_386_SIZE32, heap_allat_untraced_nx; .long 0
	.long 0x7a128c8
	.long 0 /* index: 2249 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2250 */
	.long 0
	.long 0
	.long 0
	.long .Lname2251 /* index: 2251 */
	.weak mouse_buffer_trygetpacket; .long mouse_buffer_trygetpacket
	.reloc ., R_386_SIZE32, mouse_buffer_trygetpacket; .long 0
	.long 0xe4b64
	.long 0 /* index: 2252 */
	.long 0
	.long 0
	.long 0
	.long .Lname2253 /* index: 2253 */
	.weak keymap_translate; .long keymap_translate
	.reloc ., R_386_SIZE32, keymap_translate; .long 0
	.long 0x5db5e25
	.long 0 /* index: 2254 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2255 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2256 */
	.long 0
	.long 0
	.long 0
	.long .Lname2257 /* index: 2257 */
	.weak heap_alloc_nx; .long heap_alloc_nx
	.reloc ., R_386_SIZE32, heap_alloc_nx; .long 0
	.long 0xdadf178
	.long 0 /* index: 2258 */
	.long 0
	.long 0
	.long 0
	.long .Lname2259 /* index: 2259 */
	.weak unicode_32to16; .long unicode_32to16
	.reloc ., R_386_SIZE32, unicode_32to16; .long 0
	.long 0x6940f36
	.long 0 /* index: 2260 */
	.long 0
	.long 0
	.long 0
	.long .Lname2261 /* index: 2261 */
	.weak ringbuffer_writesome; .long ringbuffer_writesome
	.reloc ., R_386_SIZE32, ringbuffer_writesome; .long 0
	.long 0xc2778d5
	.long .Lname2262 /* index: 2262 */
	.weak unicode_readutf16_swap_rev; .long unicode_readutf16_swap_rev
	.reloc ., R_386_SIZE32, unicode_readutf16_swap_rev; .long 0
	.long 0x561c8d6
	.long 0 /* index: 2263 */
	.long 0
	.long 0
	.long 0
	.long .Lname2264 /* index: 2264 */
	.weak dbg_screen_width; .long dbg_screen_width
	.reloc ., R_386_SIZE32, dbg_screen_width; .long 0
	.long 0x6f1d8d8
	.long 0 /* index: 2265 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2266 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2267 */
	.long 0
	.long 0
	.long 0
	.long .Lname2268 /* index: 2268 */
	.weak mempatl; .long mempatl
	.reloc ., R_386_SIZE32, mempatl; .long 0
	.long 0x3c468dc
	.long 0 /* index: 2269 */
	.long 0
	.long 0
	.long 0
	.long .Lname2270 /* index: 2270 */
	.weak sys_ioprio_get; .long sys_ioprio_get
	.reloc ., R_386_SIZE32, sys_ioprio_get; .long 0
	.long 0x8735c04
	.long .Lname2271 /* index: 2271 */
	.weak handle_datasize; .long handle_datasize
	.reloc ., R_386_SIZE32, handle_datasize; .long 0
	.long 0xc1a5c25
	.long 0 /* index: 2272 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2273 */
	.long 0
	.long 0
	.long 0
	.long .Lname2274 /* index: 2274 */
	.weak keymap_openblob; .long keymap_openblob
	.reloc ., R_386_SIZE32, keymap_openblob; .long 0
	.long 0x69cc8e2
	.long .Lname2275 /* index: 2275 */
	.weak inode_read_phys; .long inode_read_phys
	.reloc ., R_386_SIZE32, inode_read_phys; .long 0
	.long 0x24d78e3
	.long 0 /* index: 2276 */
	.long 0
	.long 0
	.long 0
	.long .Lname2277 /* index: 2277 */
	.weak blocking_cleanup_prioritize; .long blocking_cleanup_prioritize
	.reloc ., R_386_SIZE32, blocking_cleanup_prioritize; .long 0
	.long 0xab5d3b5
	.long 0 /* index: 2278 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2279 */
	.long 0
	.long 0
	.long 0
	.long .Lname2280 /* index: 2280 */
	.weak unicode_readutf8; .long unicode_readutf8
	.reloc ., R_386_SIZE32, unicode_readutf8; .long 0
	.long 0x126b8e8
	.long 0 /* index: 2281 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2282 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2283 */
	.long 0
	.long 0
	.long 0
	.long .Lname2284 /* index: 2284 */
	.weak kernel_debugtraps_install; .long kernel_debugtraps_install
	.reloc ., R_386_SIZE32, kernel_debugtraps_install; .long 0
	.long 0x1b018ec
	.long .Lname2285 /* index: 2285 */
	.weak dbg_fillrect2; .long dbg_fillrect2
	.reloc ., R_386_SIZE32, dbg_fillrect2; .long 0
	.long 0x9b5e6d2
	.long 0 /* index: 2286 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2287 */
	.long 0
	.long 0
	.long 0
	.long .Lname2288 /* index: 2288 */
	.weak pagedir_unmap; .long pagedir_unmap
	.reloc ., R_386_SIZE32, pagedir_unmap; .long 0
	.long 0x21808f0
	.long .Lname2289 /* index: 2289 */
	.weak sys_getegid; .long sys_getegid
	.reloc ., R_386_SIZE32, sys_getegid; .long 0
	.long 0xdb1b4a4
	.long 0 /* index: 2290 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2291 */
	.long 0
	.long 0
	.long 0
	.long .Lname2292 /* index: 2292 */
	.weak path_print; .long path_print
	.reloc ., R_386_SIZE32, path_print; .long 0
	.long 0xe60e8f4
	.long .Lname2293 /* index: 2293 */
	.weak pagedir_push_mapone; .long pagedir_push_mapone
	.reloc ., R_386_SIZE32, pagedir_push_mapone; .long 0
	.long 0x82228f5
	.long 0 /* index: 2294 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2295 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2296 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2297 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2298 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2299 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2300 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2301 */
	.long 0
	.long 0
	.long 0
	.long .Lname2302 /* index: 2302 */
	.weak krealign; .long krealign
	.reloc ., R_386_SIZE32, krealign; .long 0
	.long 0x8b828fe
	.long 0 /* index: 2303 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2304 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2305 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2306 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2307 */
	.long 0
	.long 0
	.long 0
	.long .Lname2308 /* index: 2308 */
	.weak heap_allat; .long heap_allat
	.reloc ., R_386_SIZE32, heap_allat; .long 0
	.long 0x652d904
	.long 0 /* index: 2309 */
	.long 0
	.long 0
	.long 0
	.long .Lname2310 /* index: 2310 */
	.weak sys_process_vm_writev; .long sys_process_vm_writev
	.reloc ., R_386_SIZE32, sys_process_vm_writev; .long 0
	.long 0x32a6906
	.long 0 /* index: 2311 */
	.long 0
	.long 0
	.long 0
	.long .Lname2312 /* index: 2312 */
	.weak kmalloc_noslab_nx; .long kmalloc_noslab_nx
	.reloc ., R_386_SIZE32, kmalloc_noslab_nx; .long 0
	.long 0xb0c1908
	.long .Lname2313 /* index: 2313 */
	.weak sighand_ptr_destroy; .long sighand_ptr_destroy
	.reloc ., R_386_SIZE32, sighand_ptr_destroy; .long 0
	.long 0xb50d909
	.long 0 /* index: 2314 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2315 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2316 */
	.long 0
	.long 0
	.long 0
	.long .Lname2317 /* index: 2317 */
	.weak vm_datapart_do_read; .long vm_datapart_do_read
	.reloc ., R_386_SIZE32, vm_datapart_do_read; .long 0
	.long 0x2bb9e4
	.long .Lname2318 /* index: 2318 */
	.weak sys_timer_getoverrun; .long sys_timer_getoverrun
	.reloc ., R_386_SIZE32, sys_timer_getoverrun; .long 0
	.long 0xa3fec8e
	.long .Lname2319 /* index: 2319 */
	.weak unwind_setreg_icpustate; .long unwind_setreg_icpustate
	.reloc ., R_386_SIZE32, unwind_setreg_icpustate; .long 0
	.long 0xb8d35b5
	.long 0 /* index: 2320 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2321 */
	.long 0
	.long 0
	.long 0
	.long .Lname2322 /* index: 2322 */
	.weak sys_lgetxattr; .long sys_lgetxattr
	.reloc ., R_386_SIZE32, sys_lgetxattr; .long 0
	.long 0x7b7e912
	.long .Lname2323 /* index: 2323 */
	.weak keyboard_device_readchars; .long keyboard_device_readchars
	.reloc ., R_386_SIZE32, keyboard_device_readchars; .long 0
	.long 0x158b913
	.long 0 /* index: 2324 */
	.long 0
	.long 0
	.long 0
	.long .Lname2325 /* index: 2325 */
	.weak inode_truncate; .long inode_truncate
	.reloc ., R_386_SIZE32, inode_truncate; .long 0
	.long 0xcfe2915
	.long .Lname2326 /* index: 2326 */
	.weak dbg_addr2line_vprintf; .long dbg_addr2line_vprintf
	.reloc ., R_386_SIZE32, dbg_addr2line_vprintf; .long 0
	.long 0xb018916
	.long .Lname2327 /* index: 2327 */
	.weak keyboard_device_putkey; .long keyboard_device_putkey
	.reloc ., R_386_SIZE32, keyboard_device_putkey; .long 0
	.long 0x5efded9
	.long .Lname2328 /* index: 2328 */
	.weak vm_kernel_treelock_writef_nx; .long vm_kernel_treelock_writef_nx
	.reloc ., R_386_SIZE32, vm_kernel_treelock_writef_nx; .long 0
	.long 0x3a30918
	.long .Lname2329 /* index: 2329 */
	.weak dbg_getkey; .long dbg_getkey
	.reloc ., R_386_SIZE32, dbg_getkey; .long 0
	.long 0x5da1919
	.long .Lname2330 /* index: 2330 */
	.weak vm_kernel_treelock_write; .long vm_kernel_treelock_write
	.reloc ., R_386_SIZE32, vm_kernel_treelock_write; .long 0
	.long 0x94d43a5
	.long 0 /* index: 2331 */
	.long 0
	.long 0
	.long 0
	.long .Lname2332 /* index: 2332 */
	.weak sys_sched_rr_get_interval; .long sys_sched_rr_get_interval
	.reloc ., R_386_SIZE32, sys_sched_rr_get_interval; .long 0
	.long 0x5c1391c
	.long .Lname2333 /* index: 2333 */
	.weak vm_futex_broadcast; .long vm_futex_broadcast
	.reloc ., R_386_SIZE32, vm_futex_broadcast; .long 0
	.long 0x8659cf4
	.long .Lname2334 /* index: 2334 */
	.weak sys_chroot; .long sys_chroot
	.reloc ., R_386_SIZE32, sys_chroot; .long 0
	.long 0x59846f4
	.long 0 /* index: 2335 */
	.long 0
	.long 0
	.long 0
	.long .Lname2336 /* index: 2336 */
	.weak pagedir_isuseraccessible_p; .long pagedir_isuseraccessible_p
	.reloc ., R_386_SIZE32, pagedir_isuseraccessible_p; .long 0
	.long 0x251c920
	.long .Lname2337 /* index: 2337 */
	.weak sys_mmap; .long sys_mmap
	.reloc ., R_386_SIZE32, sys_mmap; .long 0
	.long 0x964430
	.long 0 /* index: 2338 */
	.long 0
	.long 0
	.long 0
	.long .Lname2339 /* index: 2339 */
	.weak block_device_read_phys; .long block_device_read_phys
	.reloc ., R_386_SIZE32, block_device_read_phys; .long 0
	.long 0x22c3923
	.long .Lname2340 /* index: 2340 */
	.weak cpu_quantum_reset; .long cpu_quantum_reset
	.reloc ., R_386_SIZE32, cpu_quantum_reset; .long 0
	.long 0xbb6e924
	.long .Lname2341 /* index: 2341 */
	.weak driver_insmod_file; .long driver_insmod_file
	.reloc ., R_386_SIZE32, driver_insmod_file; .long 0
	.long 0x7829925
	.long .Lname2342 /* index: 2342 */
	.weak vm_startdmav; .long vm_startdmav
	.reloc ., R_386_SIZE32, vm_startdmav; .long 0
	.long 0xf49d926
	.long 0 /* index: 2343 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2344 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2345 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2346 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2347 */
	.long 0
	.long 0
	.long 0
	.long .Lname2348 /* index: 2348 */
	.weak fs_kernel; .long fs_kernel
	.reloc ., R_386_SIZE32, fs_kernel; .long 0
	.long 0x61cf92c
	.long .Lname2349 /* index: 2349 */
	.weak json_parser_getnumber; .long json_parser_getnumber
	.reloc ., R_386_SIZE32, json_parser_getnumber; .long 0
	.long 0x6da7c32
	.long .Lname2350 /* index: 2350 */
	.weak kernel_version; .long kernel_version
	.reloc ., R_386_SIZE32, kernel_version; .long 0
	.long 0x5d592e
	.long .Lname2351 /* index: 2351 */
	.weak inode_write; .long inode_write
	.reloc ., R_386_SIZE32, inode_write; .long 0
	.long 0xb1ee505
	.long .Lname2352 /* index: 2352 */
	.weak vm_datablock_readvp; .long vm_datablock_readvp
	.reloc ., R_386_SIZE32, vm_datablock_readvp; .long 0
	.long 0xc438930
	.long .Lname2353 /* index: 2353 */
	.weak __predict_update_eax; .long __predict_update_eax
	.reloc ., R_386_SIZE32, __predict_update_eax; .long 0
	.long 0x4552188
	.long .Lname2354 /* index: 2354 */
	.weak sys_readlinkat; .long sys_readlinkat
	.reloc ., R_386_SIZE32, sys_readlinkat; .long 0
	.long 0xbbadd44
	.long .Lname2355 /* index: 2355 */
	.weak sys_access; .long sys_access
	.reloc ., R_386_SIZE32, sys_access; .long 0
	.long 0x57e2c33
	.long .Lname2356 /* index: 2356 */
	.weak sys_epoll_pwait; .long sys_epoll_pwait
	.reloc ., R_386_SIZE32, sys_epoll_pwait; .long 0
	.long 0x93bf934
	.long .Lname2357 /* index: 2357 */
	.weak boot_device; .long boot_device
	.reloc ., R_386_SIZE32, boot_device; .long 0
	.long 0x5c5a935
	.long 0 /* index: 2358 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2359 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2360 */
	.long 0
	.long 0
	.long 0
	.long .Lname2361 /* index: 2361 */
	.weak memrend; .long memrend
	.reloc ., R_386_SIZE32, memrend; .long 0
	.long 0x3c48c34
	.long 0 /* index: 2362 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2363 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2364 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2365 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2366 */
	.long 0
	.long 0
	.long 0
	.long .Lname2367 /* index: 2367 */
	.weak dbg_viewstate; .long dbg_viewstate
	.reloc ., R_386_SIZE32, dbg_viewstate; .long 0
	.long 0x667c435
	.long .Lname2368 /* index: 2368 */
	.weak fs_filesystems_lock_write; .long fs_filesystems_lock_write
	.reloc ., R_386_SIZE32, fs_filesystems_lock_write; .long 0
	.long 0x6bffe05
	.long 0 /* index: 2369 */
	.long 0
	.long 0
	.long 0
	.long .Lname2370 /* index: 2370 */
	.weak path_recent_clear; .long path_recent_clear
	.reloc ., R_386_SIZE32, path_recent_clear; .long 0
	.long 0xa53942
	.long .Lname2371 /* index: 2371 */
	.weak sys_syncfs; .long sys_syncfs
	.reloc ., R_386_SIZE32, sys_syncfs; .long 0
	.long 0x6a9f943
	.long .Lname2372 /* index: 2372 */
	.weak json_writer_endobject; .long json_writer_endobject
	.reloc ., R_386_SIZE32, json_writer_endobject; .long 0
	.long 0x7dbc944
	.long .Lname2373 /* index: 2373 */
	.weak superblock_nodeslock_endwrite; .long superblock_nodeslock_endwrite
	.reloc ., R_386_SIZE32, superblock_nodeslock_endwrite; .long 0
	.long 0x4b8a945
	.long 0 /* index: 2374 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2375 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2376 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2377 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2378 */
	.long 0
	.long 0
	.long 0
	.long .Lname2379 /* index: 2379 */
	.weak cpu_addpendingtask; .long cpu_addpendingtask
	.reloc ., R_386_SIZE32, cpu_addpendingtask; .long 0
	.long 0x45fb94b
	.long .Lname2380 /* index: 2380 */
	.weak quantum_global_to_local; .long quantum_global_to_local
	.reloc ., R_386_SIZE32, quantum_global_to_local; .long 0
	.long 0xb1d594c
	.long .Lname2381 /* index: 2381 */
	.weak vm_datapart_read_buffered; .long vm_datapart_read_buffered
	.reloc ., R_386_SIZE32, vm_datapart_read_buffered; .long 0
	.long 0x6267f94
	.long 0 /* index: 2382 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2383 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2384 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2385 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2386 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2387 */
	.long 0
	.long 0
	.long 0
	.long .Lname2388 /* index: 2388 */
	.weak sys_chmod; .long sys_chmod
	.reloc ., R_386_SIZE32, sys_chmod; .long 0
	.long 0x959a954
	.long .Lname2389 /* index: 2389 */
	.weak devfs_lock_upgrade; .long devfs_lock_upgrade
	.reloc ., R_386_SIZE32, devfs_lock_upgrade; .long 0
	.long 0x8f7e955
	.long 0 /* index: 2390 */
	.long 0
	.long 0
	.long 0
	.long .Lname2391 /* index: 2391 */
	.weak file_destroy; .long file_destroy
	.reloc ., R_386_SIZE32, file_destroy; .long 0
	.long 0xc1a9439
	.long .Lname2392 /* index: 2392 */
	.weak vpage_alloc_untraced_nx; .long vpage_alloc_untraced_nx
	.reloc ., R_386_SIZE32, vpage_alloc_untraced_nx; .long 0
	.long 0x3daa958
	.long .Lname2393 /* index: 2393 */
	.weak sys_pwrite64; .long sys_pwrite64
	.reloc ., R_386_SIZE32, sys_pwrite64; .long 0
	.long 0x9403ee4
	.long 0 /* index: 2394 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2395 */
	.long 0
	.long 0
	.long 0
	.long .Lname2396 /* index: 2396 */
	.weak ttybase_device_tryioctl; .long ttybase_device_tryioctl
	.reloc ., R_386_SIZE32, ttybase_device_tryioctl; .long 0
	.long 0xde5095c
	.long 0 /* index: 2397 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2398 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2399 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2400 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2401 */
	.long 0
	.long 0
	.long 0
	.long .Lname2402 /* index: 2402 */
	.weak inode_recent_clear; .long inode_recent_clear
	.reloc ., R_386_SIZE32, inode_recent_clear; .long 0
	.long 0x9d8e962
	.long .Lname2403 /* index: 2403 */
	.weak block_device_read_sync; .long block_device_read_sync
	.reloc ., R_386_SIZE32, block_device_read_sync; .long 0
	.long 0x22cf963
	.long .Lname2404 /* index: 2404 */
	.weak sys_setsid; .long sys_setsid
	.reloc ., R_386_SIZE32, sys_setsid; .long 0
	.long 0x69b0964
	.long 0 /* index: 2405 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2406 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2407 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2408 */
	.long 0
	.long 0
	.long 0
	.long .Lname2409 /* index: 2409 */
	.weak path_newchild; .long path_newchild
	.reloc ., R_386_SIZE32, path_newchild; .long 0
	.long 0xa530a14
	.long 0 /* index: 2410 */
	.long 0
	.long 0
	.long 0
	.long .Lname2411 /* index: 2411 */
	.weak vio_orw; .long vio_orw
	.reloc ., R_386_SIZE32, vio_orw; .long 0
	.long 0xd0566e7
	.long 0 /* index: 2412 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2413 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2414 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2415 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2416 */
	.long 0
	.long 0
	.long 0
	.long .Lname2417 /* index: 2417 */
	.weak memmove; .long memmove
	.reloc ., R_386_SIZE32, memmove; .long 0
	.long 0x3c446b5
	.long 0 /* index: 2418 */
	.long 0
	.long 0
	.long 0
	.long .Lname2419 /* index: 2419 */
	.weak vm_datablock_vio_readv_phys; .long vm_datablock_vio_readv_phys
	.reloc ., R_386_SIZE32, vm_datablock_vio_readv_phys; .long 0
	.long 0x3820973
	.long .Lname2420 /* index: 2420 */
	.weak block_device_acquire_partlock_read; .long block_device_acquire_partlock_read
	.reloc ., R_386_SIZE32, block_device_acquire_partlock_read; .long 0
	.long 0x3d5d974
	.long 0 /* index: 2421 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2422 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2423 */
	.long 0
	.long 0
	.long 0
	.long .Lname2424 /* index: 2424 */
	.weak vpage_realloc_nx; .long vpage_realloc_nx
	.reloc ., R_386_SIZE32, vpage_realloc_nx; .long 0
	.long 0xa4e978
	.long .Lname2425 /* index: 2425 */
	.weak sys_timerfd_settime64; .long sys_timerfd_settime64
	.reloc ., R_386_SIZE32, sys_timerfd_settime64; .long 0
	.long 0xa0cc994
	.long 0 /* index: 2426 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2427 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2428 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2429 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2430 */
	.long 0
	.long 0
	.long 0
	.long .Lname2431 /* index: 2431 */
	.weak vm_alloc; .long vm_alloc
	.reloc ., R_386_SIZE32, vm_alloc; .long 0
	.long 0x3583683
	.long 0 /* index: 2432 */
	.long 0
	.long 0
	.long 0
	.long .Lname2433 /* index: 2433 */
	.weak linebuffer_write; .long linebuffer_write
	.reloc ., R_386_SIZE32, linebuffer_write; .long 0
	.long 0xdf28c25
	.long .Lname2434 /* index: 2434 */
	.weak memrchr; .long memrchr
	.reloc ., R_386_SIZE32, memrchr; .long 0
	.long 0x3c48982
	.long .Lname2435 /* index: 2435 */
	.weak linebuffer_write_nonblock; .long linebuffer_write_nonblock
	.reloc ., R_386_SIZE32, linebuffer_write_nonblock; .long 0
	.long 0xe8bbeeb
	.long 0 /* index: 2436 */
	.long 0
	.long 0
	.long 0
	.long .Lname2437 /* index: 2437 */
	.weak sys_time; .long sys_time
	.reloc ., R_386_SIZE32, sys_time; .long 0
	.long 0x96a985
	.long 0 /* index: 2438 */
	.long 0
	.long 0
	.long 0
	.long .Lname2439 /* index: 2439 */
	.weak vm86_inw; .long vm86_inw
	.reloc ., R_386_SIZE32, vm86_inw; .long 0
	.long 0xbc5987
	.long .Lname2440 /* index: 2440 */
	.weak vm_kernel_treelock_upgrade_nx; .long vm_kernel_treelock_upgrade_nx
	.reloc ., R_386_SIZE32, vm_kernel_treelock_upgrade_nx; .long 0
	.long 0x8ee6988
	.long 0 /* index: 2441 */
	.long 0
	.long 0
	.long 0
	.long .Lname2442 /* index: 2442 */
	.weak cpu_delsleepingtask; .long cpu_delsleepingtask
	.reloc ., R_386_SIZE32, cpu_delsleepingtask; .long 0
	.long 0x7b74e1b
	.long 0 /* index: 2443 */
	.long 0
	.long 0
	.long 0
	.long .Lname2444 /* index: 2444 */
	.weak vm_kernel; .long vm_kernel
	.reloc ., R_386_SIZE32, vm_kernel; .long 0
	.long 0x61d098c
	.long .Lname2445 /* index: 2445 */
	.weak isr_register; .long isr_register
	.reloc ., R_386_SIZE32, isr_register; .long 0
	.long 0xcea2c42
	.long 0 /* index: 2446 */
	.long 0
	.long 0
	.long 0
	.long .Lname2447 /* index: 2447 */
	.weak sys_sendfile64; .long sys_sendfile64
	.reloc ., R_386_SIZE32, sys_sendfile64; .long 0
	.long 0xa5ab564
	.long 0 /* index: 2448 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2449 */
	.long 0
	.long 0
	.long 0
	.long .Lname2450 /* index: 2450 */
	.weak vm86_inb; .long vm86_inb
	.reloc ., R_386_SIZE32, vm86_inb; .long 0
	.long 0xbc5992
	.long .Lname2451 /* index: 2451 */
	.weak ringbuffer_read; .long ringbuffer_read
	.reloc ., R_386_SIZE32, ringbuffer_read; .long 0
	.long 0x8bf4eb4
	.long .Lname2452 /* index: 2452 */
	.weak vio_memset; .long vio_memset
	.reloc ., R_386_SIZE32, vio_memset; .long 0
	.long 0x63d9994
	.long 0 /* index: 2453 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2454 */
	.long 0
	.long 0
	.long 0
	.long .Lname2455 /* index: 2455 */
	.weak vmb_fini; .long vmb_fini
	.reloc ., R_386_SIZE32, vmb_fini; .long 0
	.long 0x385c999
	.long 0 /* index: 2456 */
	.long 0
	.long 0
	.long 0
	.long .Lname2457 /* index: 2457 */
	.weak json_writer_beginarray; .long json_writer_beginarray
	.reloc ., R_386_SIZE32, json_writer_beginarray; .long 0
	.long 0x864b999
	.long 0 /* index: 2458 */
	.long 0
	.long 0
	.long 0
	.long .Lname2459 /* index: 2459 */
	.weak directory_symlink; .long directory_symlink
	.reloc ., R_386_SIZE32, directory_symlink; .long 0
	.long 0x3fb99b
	.long .Lname2460 /* index: 2460 */
	.weak sys_kill; .long sys_kill
	.reloc ., R_386_SIZE32, sys_kill; .long 0
	.long 0x96199c
	.long 0 /* index: 2461 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2462 */
	.long 0
	.long 0
	.long 0
	.long .Lname2463 /* index: 2463 */
	.weak _this_sigqueue; .long _this_sigqueue
	.reloc ., R_386_SIZE32, _this_sigqueue; .long 0
	.long 0x5182c45
	.long .Lname2464 /* index: 2464 */
	.weak heap_realign_untraced; .long heap_realign_untraced
	.reloc ., R_386_SIZE32, heap_realign_untraced; .long 0
	.long 0xf249ac4
	.long 0 /* index: 2465 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2466 */
	.long 0
	.long 0
	.long 0
	.long .Lname2467 /* index: 2467 */
	.weak block_device_write_phys_sync; .long block_device_write_phys_sync
	.reloc ., R_386_SIZE32, block_device_write_phys_sync; .long 0
	.long 0x5b799a3
	.long .Lname2468 /* index: 2468 */
	.weak sys_settimeofday64; .long sys_settimeofday64
	.reloc ., R_386_SIZE32, sys_settimeofday64; .long 0
	.long 0xec0f9a4
	.long .Lname2469 /* index: 2469 */
	.weak vm_datapart_do_write; .long vm_datapart_do_write
	.reloc ., R_386_SIZE32, vm_datapart_do_write; .long 0
	.long 0x2bdb9a5
	.long 0 /* index: 2470 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2471 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2472 */
	.long 0
	.long 0
	.long 0
	.long .Lname2473 /* index: 2473 */
	.weak vm86_inl; .long vm86_inl
	.reloc ., R_386_SIZE32, vm86_inl; .long 0
	.long 0xbc599c
	.long .Lname2474 /* index: 2474 */
	.weak error_class; .long error_class
	.reloc ., R_386_SIZE32, error_class; .long 0
	.long 0x836b1c3
	.long .Lname2475 /* index: 2475 */
	.weak vpage_alloc_untraced; .long vpage_alloc_untraced
	.reloc ., R_386_SIZE32, vpage_alloc_untraced; .long 0
	.long 0xd03da4
	.long 0 /* index: 2476 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2477 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2478 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2479 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2480 */
	.long 0
	.long 0
	.long 0
	.long .Lname2481 /* index: 2481 */
	.weak vm_datapart_do_enumdma; .long vm_datapart_do_enumdma
	.reloc ., R_386_SIZE32, vm_datapart_do_enumdma; .long 0
	.long 0x97339b1
	.long .Lname2482 /* index: 2482 */
	.weak sys_eventfd2; .long sys_eventfd2
	.reloc ., R_386_SIZE32, sys_eventfd2; .long 0
	.long 0xb1539b2
	.long .Lname2483 /* index: 2483 */
	.weak driver_loaded_callbacks; .long driver_loaded_callbacks
	.reloc ., R_386_SIZE32, driver_loaded_callbacks; .long 0
	.long 0x5bfe6f3
	.long .Lname2484 /* index: 2484 */
	.weak mempset; .long mempset
	.reloc ., R_386_SIZE32, mempset; .long 0
	.long 0x3c479b4
	.long .Lname2485 /* index: 2485 */
	.weak regdump_fcpustate; .long regdump_fcpustate
	.reloc ., R_386_SIZE32, regdump_fcpustate; .long 0
	.long 0xbf449b5
	.long 0 /* index: 2486 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2487 */
	.long 0
	.long 0
	.long 0
	.long .Lname2488 /* index: 2488 */
	.weak krealign_offset_nx; .long krealign_offset_nx
	.reloc ., R_386_SIZE32, krealign_offset_nx; .long 0
	.long 0x49079b8
	.long .Lname2489 /* index: 2489 */
	.weak debuginfo_cu_abbrev_fini; .long debuginfo_cu_abbrev_fini
	.reloc ., R_386_SIZE32, debuginfo_cu_abbrev_fini; .long 0
	.long 0xd1aa9b9
	.long 0 /* index: 2490 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2491 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2492 */
	.long 0
	.long 0
	.long 0
	.long .Lname2493 /* index: 2493 */
	.weak heap_validate_all; .long heap_validate_all
	.reloc ., R_386_SIZE32, heap_validate_all; .long 0
	.long 0xe01c1ec
	.long .Lname2494 /* index: 2494 */
	.weak heap_realign; .long heap_realign
	.reloc ., R_386_SIZE32, heap_realign; .long 0
	.long 0xe5da9be
	.long 0 /* index: 2495 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2496 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2497 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2498 */
	.long 0
	.long 0
	.long 0
	.long .Lname2499 /* index: 2499 */
	.weak block_device_partition_writev_phys; .long block_device_partition_writev_phys
	.reloc ., R_386_SIZE32, block_device_partition_writev_phys; .long 0
	.long 0xcf2e9c3
	.long .Lname2500 /* index: 2500 */
	.weak kmemalign_offset; .long kmemalign_offset
	.reloc ., R_386_SIZE32, kmemalign_offset; .long 0
	.long 0x7d939c4
	.long .Lname2501 /* index: 2501 */
	.weak vm_tasklock_trywrite; .long vm_tasklock_trywrite
	.reloc ., R_386_SIZE32, vm_tasklock_trywrite; .long 0
	.long 0xc3a29c5
	.long 0 /* index: 2502 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2503 */
	.long 0
	.long 0
	.long 0
	.long .Lname2504 /* index: 2504 */
	.weak kmemalign_offset_nx; .long kmemalign_offset_nx
	.reloc ., R_386_SIZE32, kmemalign_offset_nx; .long 0
	.long 0x39cf9c8
	.long .Lname2505 /* index: 2505 */
	.weak kernel_debugtrap_r_ucpustate; .long kernel_debugtrap_r_ucpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_ucpustate; .long 0
	.long 0xed53da5
	.long 0 /* index: 2506 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2507 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2508 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2509 */
	.long 0
	.long 0
	.long 0
	.long .Lname2510 /* index: 2510 */
	.weak mouse_device_button; .long mouse_device_button
	.reloc ., R_386_SIZE32, mouse_device_button; .long 0
	.long 0xb3cd9ce
	.long 0 /* index: 2511 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2512 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2513 */
	.long 0
	.long 0
	.long 0
	.long .Lname2514 /* index: 2514 */
	.weak vm86_sw_intr; .long vm86_sw_intr
	.reloc ., R_386_SIZE32, vm86_sw_intr; .long 0
	.long 0xd2559d2
	.long .Lname2515 /* index: 2515 */
	.weak __x86_bootcpu_features; .long __x86_bootcpu_features
	.reloc ., R_386_SIZE32, __x86_bootcpu_features; .long 0
	.long 0xaef99d3
	.long 0 /* index: 2516 */
	.long 0
	.long 0
	.long 0
	.long .Lname2517 /* index: 2517 */
	.weak debugaranges_locate; .long debugaranges_locate
	.reloc ., R_386_SIZE32, debugaranges_locate; .long 0
	.long 0x908f9d5
	.long 0 /* index: 2518 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2519 */
	.long 0
	.long 0
	.long 0
	.long .Lname2520 /* index: 2520 */
	.weak inode_recent_clear_nx; .long inode_recent_clear_nx
	.reloc ., R_386_SIZE32, inode_recent_clear_nx; .long 0
	.long 0xe96f9d8
	.long .Lname2521 /* index: 2521 */
	.weak dbg_exit; .long dbg_exit
	.reloc ., R_386_SIZE32, dbg_exit; .long 0
	.long 0x8d5c9a4
	.long 0 /* index: 2522 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2523 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2524 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2525 */
	.long 0
	.long 0
	.long 0
	.long .Lname2526 /* index: 2526 */
	.weak driver_getfile; .long driver_getfile
	.reloc ., R_386_SIZE32, driver_getfile; .long 0
	.long 0x4c60ec5
	.long .Lname2527 /* index: 2527 */
	.weak kernel_debugtrap_r_icpustate; .long kernel_debugtrap_r_icpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_icpustate; .long 0
	.long 0xed509a5
	.long .Lname2528 /* index: 2528 */
	.weak __asm32_exsyscallrouter_int80; .long __asm32_exsyscallrouter_int80
	.reloc ., R_386_SIZE32, __asm32_exsyscallrouter_int80; .long 0
	.long 0xc409e0
	.long 0 /* index: 2529 */
	.long 0
	.long 0
	.long 0
	.long .Lname2530 /* index: 2530 */
	.weak vm86_hw_intr; .long vm86_hw_intr
	.reloc ., R_386_SIZE32, vm86_hw_intr; .long 0
	.long 0x82559e2
	.long 0 /* index: 2531 */
	.long 0
	.long 0
	.long 0
	.long .Lname2532 /* index: 2532 */
	.weak keyboard_device_stat; .long keyboard_device_stat
	.reloc ., R_386_SIZE32, keyboard_device_stat; .long 0
	.long 0xf1539e4
	.long .Lname2533 /* index: 2533 */
	.weak addr2line; .long addr2line
	.reloc ., R_386_SIZE32, addr2line; .long 0
	.long 0xb5949e5
	.long .Lname2534 /* index: 2534 */
	.weak vm_datapart_writev; .long vm_datapart_writev
	.reloc ., R_386_SIZE32, vm_datapart_writev; .long 0
	.long 0xbbed9e6
	.long .Lname2535 /* index: 2535 */
	.weak unregister_filesystem_type; .long unregister_filesystem_type
	.reloc ., R_386_SIZE32, unregister_filesystem_type; .long 0
	.long 0x7be1165
	.long 0 /* index: 2536 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2537 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2538 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2539 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2540 */
	.long 0
	.long 0
	.long 0
	.long .Lname2541 /* index: 2541 */
	.weak inode_recent_getcur; .long inode_recent_getcur
	.reloc ., R_386_SIZE32, inode_recent_getcur; .long 0
	.long 0xd308452
	.long 0 /* index: 2542 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2543 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2544 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2545 */
	.long 0
	.long 0
	.long 0
	.long .Lname2546 /* index: 2546 */
	.weak strchr; .long strchr
	.reloc ., R_386_SIZE32, strchr; .long 0
	.long 0x7ab89f2
	.long .Lname2547 /* index: 2547 */
	.weak unwind_emulator_exec; .long unwind_emulator_exec
	.reloc ., R_386_SIZE32, unwind_emulator_exec; .long 0
	.long 0x9e9a9f3
	.long .Lname2548 /* index: 2548 */
	.weak sys_bind; .long sys_bind
	.reloc ., R_386_SIZE32, sys_bind; .long 0
	.long 0x9589f4
	.long .Lname2549 /* index: 2549 */
	.weak kernel_panic_ucpustate; .long kernel_panic_ucpustate
	.reloc ., R_386_SIZE32, kernel_panic_ucpustate; .long 0
	.long 0x78ab9f5
	.long 0 /* index: 2550 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2551 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2552 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2553 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2554 */
	.long 0
	.long 0
	.long 0
	.long .Lname2555 /* index: 2555 */
	.weak sys_link; .long sys_link
	.reloc ., R_386_SIZE32, sys_link; .long 0
	.long 0x9629fb
	.long .Lname2556 /* index: 2556 */
	.weak sys_linkat; .long sys_linkat
	.reloc ., R_386_SIZE32, sys_linkat; .long 0
	.long 0x62a0114
	.long 0 /* index: 2557 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2558 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2559 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2560 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2561 */
	.long 0
	.long 0
	.long 0
	.long .Lname2562 /* index: 2562 */
	.weak debuginfo_cu_parser_getaddr; .long debuginfo_cu_parser_getaddr
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getaddr; .long 0
	.long 0xbb49a02
	.long .Lname2563 /* index: 2563 */
	.weak superblock_statfs; .long superblock_statfs
	.reloc ., R_386_SIZE32, superblock_statfs; .long 0
	.long 0xfa32a03
	.long 0 /* index: 2564 */
	.long 0
	.long 0
	.long 0
	.long .Lname2565 /* index: 2565 */
	.weak serial_probe; .long serial_probe
	.reloc ., R_386_SIZE32, serial_probe; .long 0
	.long 0x7fb1a05
	.long .Lname2566 /* index: 2566 */
	.weak task_exec_asynchronous_rpc_v; .long task_exec_asynchronous_rpc_v
	.reloc ., R_386_SIZE32, task_exec_asynchronous_rpc_v; .long 0
	.long 0x40cfa06
	.long 0 /* index: 2567 */
	.long 0
	.long 0
	.long 0
	.long .Lname2568 /* index: 2568 */
	.weak vm_datapart_do_allocram_nx; .long vm_datapart_do_allocram_nx
	.reloc ., R_386_SIZE32, vm_datapart_do_allocram_nx; .long 0
	.long 0x8034a08
	.long .Lname2569 /* index: 2569 */
	.weak mempcpy; .long mempcpy
	.reloc ., R_386_SIZE32, mempcpy; .long 0
	.long 0x3c46a09
	.long 0 /* index: 2570 */
	.long 0
	.long 0
	.long 0
	.long .Lname2571 /* index: 2571 */
	.weak linebuffer_rewrite; .long linebuffer_rewrite
	.reloc ., R_386_SIZE32, linebuffer_rewrite; .long 0
	.long 0x4321d55
	.long 0 /* index: 2572 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2573 */
	.long 0
	.long 0
	.long 0
	.long .Lname2574 /* index: 2574 */
	.weak x86_rpc_user_redirection; .long x86_rpc_user_redirection
	.reloc ., R_386_SIZE32, x86_rpc_user_redirection; .long 0
	.long 0xf9f1a0e
	.long .Lname2575 /* index: 2575 */
	.weak path_getchild_or_parent_inode; .long path_getchild_or_parent_inode
	.reloc ., R_386_SIZE32, path_getchild_or_parent_inode; .long 0
	.long 0x5b45a75
	.long 0 /* index: 2576 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2577 */
	.long 0
	.long 0
	.long 0
	.long .Lname2578 /* index: 2578 */
	.weak krand_r; .long krand_r
	.reloc ., R_386_SIZE32, krand_r; .long 0
	.long 0x2884a12
	.long .Lname2579 /* index: 2579 */
	.weak keyboard_device_readkeys; .long keyboard_device_readkeys
	.reloc ., R_386_SIZE32, keyboard_device_readkeys; .long 0
	.long 0x8160a13
	.long .Lname2580 /* index: 2580 */
	.weak heap_align_untraced; .long heap_align_untraced
	.reloc ., R_386_SIZE32, heap_align_untraced; .long 0
	.long 0x9fe1a14
	.long .Lname2581 /* index: 2581 */
	.weak inode_awrite; .long inode_awrite
	.reloc ., R_386_SIZE32, inode_awrite; .long 0
	.long 0x28bea15
	.long .Lname2582 /* index: 2582 */
	.weak unicode_writeutf16; .long unicode_writeutf16
	.reloc ., R_386_SIZE32, unicode_writeutf16; .long 0
	.long 0x7beba16
	.long .Lname2583 /* index: 2583 */
	.weak ttybase_device_fini; .long ttybase_device_fini
	.reloc ., R_386_SIZE32, ttybase_device_fini; .long 0
	.long 0xb508c59
	.long .Lname2584 /* index: 2584 */
	.weak dbg_hasuni; .long dbg_hasuni
	.reloc ., R_386_SIZE32, dbg_hasuni; .long 0
	.long 0x5ee0499
	.long .Lname2585 /* index: 2585 */
	.weak json_parser_next; .long json_parser_next
	.reloc ., R_386_SIZE32, json_parser_next; .long 0
	.long 0x825df04
	.long 0 /* index: 2586 */
	.long 0
	.long 0
	.long 0
	.long .Lname2587 /* index: 2587 */
	.weak x86_rpc_redirection_iret; .long x86_rpc_redirection_iret
	.reloc ., R_386_SIZE32, x86_rpc_redirection_iret; .long 0
	.long 0x604ef04
	.long 0 /* index: 2588 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2589 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2590 */
	.long 0
	.long 0
	.long 0
	.long .Lname2591 /* index: 2591 */
	.weak sys_splice; .long sys_splice
	.reloc ., R_386_SIZE32, sys_splice; .long 0
	.long 0x6a29f05
	.long .Lname2592 /* index: 2592 */
	.weak dbg_hexedit; .long dbg_hexedit
	.reloc ., R_386_SIZE32, dbg_hexedit; .long 0
	.long 0xea43854
	.long 0 /* index: 2593 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2594 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2595 */
	.long 0
	.long 0
	.long 0
	.long .Lname2596 /* index: 2596 */
	.weak json_writer_beginobject; .long json_writer_beginobject
	.reloc ., R_386_SIZE32, json_writer_beginobject; .long 0
	.long 0x79b1a24
	.long 0 /* index: 2597 */
	.long 0
	.long 0
	.long 0
	.long .Lname2598 /* index: 2598 */
	.weak vm_kernel_treelock_writef; .long vm_kernel_treelock_writef
	.reloc ., R_386_SIZE32, vm_kernel_treelock_writef; .long 0
	.long 0x4d43a26
	.long 0 /* index: 2599 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2600 */
	.long 0
	.long 0
	.long 0
	.long .Lname2601 /* index: 2601 */
	.weak keyboard_device_ioctl; .long keyboard_device_ioctl
	.reloc ., R_386_SIZE32, keyboard_device_ioctl; .long 0
	.long 0x1676c5c
	.long 0 /* index: 2602 */
	.long 0
	.long 0
	.long 0
	.long .Lname2603 /* index: 2603 */
	.weak debuginfo_cu_parser_loadattr_lexical_block; .long debuginfo_cu_parser_loadattr_lexical_block
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_lexical_block; .long 0
	.long 0x8124a2b
	.long .Lname2604 /* index: 2604 */
	.weak sys_munlockall; .long sys_munlockall
	.reloc ., R_386_SIZE32, sys_munlockall; .long 0
	.long 0x3d05a2c
	.long 0 /* index: 2605 */
	.long 0
	.long 0
	.long 0
	.long .Lname2606 /* index: 2606 */
	.weak sys_listen; .long sys_listen
	.reloc ., R_386_SIZE32, sys_listen; .long 0
	.long 0x6371a2e
	.long 0 /* index: 2607 */
	.long 0
	.long 0
	.long 0
	.long .Lname2608 /* index: 2608 */
	.weak sys_getdents; .long sys_getdents
	.reloc ., R_386_SIZE32, sys_getdents; .long 0
	.long 0xb1a3063
	.long .Lname2609 /* index: 2609 */
	.weak driver_at_address; .long driver_at_address
	.reloc ., R_386_SIZE32, driver_at_address; .long 0
	.long 0xb859633
	.long 0 /* index: 2610 */
	.long 0
	.long 0
	.long 0
	.long .Lname2611 /* index: 2611 */
	.weak task_schedule_user_rpc; .long task_schedule_user_rpc
	.reloc ., R_386_SIZE32, task_schedule_user_rpc; .long 0
	.long 0x32cc9b3
	.long .Lname2612 /* index: 2612 */
	.weak validate_readable_opt; .long validate_readable_opt
	.reloc ., R_386_SIZE32, validate_readable_opt; .long 0
	.long 0xd5cea34
	.long .Lname2613 /* index: 2613 */
	.weak path_getcasechild_or_parent_inode; .long path_getcasechild_or_parent_inode
	.reloc ., R_386_SIZE32, path_getcasechild_or_parent_inode; .long 0
	.long 0x372aa35
	.long 0 /* index: 2614 */
	.long 0
	.long 0
	.long 0
	.long .Lname2615 /* index: 2615 */
	.weak dbg_getfunc_fuzzy; .long dbg_getfunc_fuzzy
	.reloc ., R_386_SIZE32, dbg_getfunc_fuzzy; .long 0
	.long 0x6fda709
	.long .Lname2616 /* index: 2616 */
	.weak debug_original_thread; .long debug_original_thread
	.reloc ., R_386_SIZE32, debug_original_thread; .long 0
	.long 0xcc8744
	.long .Lname2617 /* index: 2617 */
	.weak task_destroy; .long task_destroy
	.reloc ., R_386_SIZE32, task_destroy; .long 0
	.long 0xd621a39
	.long .Lname2618 /* index: 2618 */
	.weak unicode_readutf16_rev; .long unicode_readutf16_rev
	.reloc ., R_386_SIZE32, unicode_readutf16_rev; .long 0
	.long 0xe5a0346
	.long .Lname2619 /* index: 2619 */
	.weak block_device_register_auto; .long block_device_register_auto
	.reloc ., R_386_SIZE32, block_device_register_auto; .long 0
	.long 0xb6c0c5f
	.long .Lname2620 /* index: 2620 */
	.weak sys_sysctl; .long sys_sysctl
	.reloc ., R_386_SIZE32, sys_sysctl; .long 0
	.long 0x6b72a3c
	.long 0 /* index: 2621 */
	.long 0
	.long 0
	.long 0
	.long .Lname2622 /* index: 2622 */
	.weak rawmemlen; .long rawmemlen
	.reloc ., R_386_SIZE32, rawmemlen; .long 0
	.long 0xe3c5a3e
	.long .Lname2623 /* index: 2623 */
	.weak pagedir_pop_mapone; .long pagedir_pop_mapone
	.reloc ., R_386_SIZE32, pagedir_pop_mapone; .long 0
	.long 0x319b9b5
	.long .Lname2624 /* index: 2624 */
	.weak bcmp; .long bcmp
	.reloc ., R_386_SIZE32, bcmp; .long 0
	.long 0x68a40
	.long 0 /* index: 2625 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2626 */
	.long 0
	.long 0
	.long 0
	.long .Lname2627 /* index: 2627 */
	.weak sys_statfs; .long sys_statfs
	.reloc ., R_386_SIZE32, sys_statfs; .long 0
	.long 0x6ad3a43
	.long .Lname2628 /* index: 2628 */
	.weak sys_getcwd; .long sys_getcwd
	.reloc ., R_386_SIZE32, sys_getcwd; .long 0
	.long 0x5db1a44
	.long .Lname2629 /* index: 2629 */
	.weak pagedir_iswritable; .long pagedir_iswritable
	.reloc ., R_386_SIZE32, pagedir_iswritable; .long 0
	.long 0x29aa45
	.long 0 /* index: 2630 */
	.long 0
	.long 0
	.long 0
	.long .Lname2631 /* index: 2631 */
	.weak cpu_swipi_pending; .long cpu_swipi_pending
	.reloc ., R_386_SIZE32, cpu_swipi_pending; .long 0
	.long 0xc8eba47
	.long 0 /* index: 2632 */
	.long 0
	.long 0
	.long 0
	.long .Lname2633 /* index: 2633 */
	.weak empty_directory_entry; .long empty_directory_entry
	.reloc ., R_386_SIZE32, empty_directory_entry; .long 0
	.long 0x25ffa49
	.long 0 /* index: 2634 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2635 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2636 */
	.long 0
	.long 0
	.long 0
	.long .Lname2637 /* index: 2637 */
	.weak sys_setreuid32; .long sys_setreuid32
	.reloc ., R_386_SIZE32, sys_setreuid32; .long 0
	.long 0x85d6c62
	.long .Lname2638 /* index: 2638 */
	.weak handle_lookupin; .long handle_lookupin
	.reloc ., R_386_SIZE32, handle_lookupin; .long 0
	.long 0x2f01a4e
	.long 0 /* index: 2639 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2640 */
	.long 0
	.long 0
	.long 0
	.long .Lname2641 /* index: 2641 */
	.weak vm_stopdma; .long vm_stopdma
	.reloc ., R_386_SIZE32, vm_stopdma; .long 0
	.long 0xab1ba51
	.long .Lname2642 /* index: 2642 */
	.weak dbg_isholding_altgr; .long dbg_isholding_altgr
	.reloc ., R_386_SIZE32, dbg_isholding_altgr; .long 0
	.long 0xab9ea52
	.long .Lname2643 /* index: 2643 */
	.weak task_connect_c; .long task_connect_c
	.reloc ., R_386_SIZE32, task_connect_c; .long 0
	.long 0xdeaca53
	.long .Lname2644 /* index: 2644 */
	.weak sys_sched_rr_get_interval64; .long sys_sched_rr_get_interval64
	.reloc ., R_386_SIZE32, sys_sched_rr_get_interval64; .long 0
	.long 0x1391a54
	.long .Lname2645 /* index: 2645 */
	.weak sys_execve; .long sys_execve
	.reloc ., R_386_SIZE32, sys_execve; .long 0
	.long 0x5c90a55
	.long .Lname2646 /* index: 2646 */
	.weak memeq_nopf; .long memeq_nopf
	.reloc ., R_386_SIZE32, memeq_nopf; .long 0
	.long 0xc738a56
	.long 0 /* index: 2647 */
	.long 0
	.long 0
	.long 0
	.long .Lname2648 /* index: 2648 */
	.weak sys_lfutex; .long sys_lfutex
	.reloc ., R_386_SIZE32, sys_lfutex; .long 0
	.long 0x62a7a58
	.long 0 /* index: 2649 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2650 */
	.long 0
	.long 0
	.long 0
	.long .Lname2651 /* index: 2651 */
	.weak ringbuffer_read_nonblock; .long ringbuffer_read_nonblock
	.reloc ., R_386_SIZE32, ringbuffer_read_nonblock; .long 0
	.long 0x2a41a5b
	.long 0 /* index: 2652 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2653 */
	.long 0
	.long 0
	.long 0
	.long .Lname2654 /* index: 2654 */
	.weak rawmemrlen; .long rawmemrlen
	.reloc ., R_386_SIZE32, rawmemrlen; .long 0
	.long 0x3c31a5e
	.long .Lname2655 /* index: 2655 */
	.weak x86_exsyscall_restart_mode; .long x86_exsyscall_restart_mode
	.reloc ., R_386_SIZE32, x86_exsyscall_restart_mode; .long 0
	.long 0x4566465
	.long .Lname2656 /* index: 2656 */
	.weak block_device_lookup; .long block_device_lookup
	.reloc ., R_386_SIZE32, block_device_lookup; .long 0
	.long 0x7ed1a60
	.long .Lname2657 /* index: 2657 */
	.weak vm_enumdma; .long vm_enumdma
	.reloc ., R_386_SIZE32, vm_enumdma; .long 0
	.long 0xc5dea61
	.long 0 /* index: 2658 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2659 */
	.long 0
	.long 0
	.long 0
	.long .Lname2660 /* index: 2660 */
	.weak sys_gettid; .long sys_gettid
	.reloc ., R_386_SIZE32, sys_gettid; .long 0
	.long 0x5db0a64
	.long .Lname2661 /* index: 2661 */
	.weak sys_getrusage; .long sys_getrusage
	.reloc ., R_386_SIZE32, sys_getrusage; .long 0
	.long 0x95ca65
	.long 0 /* index: 2662 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2663 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2664 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2665 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2666 */
	.long 0
	.long 0
	.long 0
	.long .Lname2667 /* index: 2667 */
	.weak sys_kreaddir; .long sys_kreaddir
	.reloc ., R_386_SIZE32, sys_kreaddir; .long 0
	.long 0xf073d22
	.long .Lname2668 /* index: 2668 */
	.weak json_parser_getnull; .long json_parser_getnull
	.reloc ., R_386_SIZE32, json_parser_getnull; .long 0
	.long 0x4f6da6c
	.long .Lname2669 /* index: 2669 */
	.weak vm_do_ffreeram; .long vm_do_ffreeram
	.reloc ., R_386_SIZE32, vm_do_ffreeram; .long 0
	.long 0xed09a6d
	.long 0 /* index: 2670 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2671 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2672 */
	.long 0
	.long 0
	.long 0
	.long .Lname2673 /* index: 2673 */
	.weak sys_setgid32; .long sys_setgid32
	.reloc ., R_386_SIZE32, sys_setgid32; .long 0
	.long 0xb1d61f2
	.long .Lname2674 /* index: 2674 */
	.weak sys_setitimer; .long sys_setitimer
	.reloc ., R_386_SIZE32, sys_setitimer; .long 0
	.long 0x203aa72
	.long .Lname2675 /* index: 2675 */
	.weak vm_datablock_vio_read_phys; .long vm_datablock_vio_read_phys
	.reloc ., R_386_SIZE32, vm_datablock_vio_read_phys; .long 0
	.long 0x72a2a73
	.long .Lname2676 /* index: 2676 */
	.weak debugline_scanunit; .long debugline_scanunit
	.reloc ., R_386_SIZE32, debugline_scanunit; .long 0
	.long 0xd2b0a74
	.long .Lname2677 /* index: 2677 */
	.weak superblock_nodeslock_trywrite; .long superblock_nodeslock_trywrite
	.reloc ., R_386_SIZE32, superblock_nodeslock_trywrite; .long 0
	.long 0xa08aa75
	.long .Lname2678 /* index: 2678 */
	.weak __afailf; .long __afailf
	.reloc ., R_386_SIZE32, __afailf; .long 0
	.long 0x57c7a76
	.long .Lname2679 /* index: 2679 */
	.weak cpu_hwipi_pending; .long cpu_hwipi_pending
	.reloc ., R_386_SIZE32, cpu_hwipi_pending; .long 0
	.long 0x98eba77
	.long 0 /* index: 2680 */
	.long 0
	.long 0
	.long 0
	.long .Lname2681 /* index: 2681 */
	.weak memcpy; .long memcpy
	.reloc ., R_386_SIZE32, memcpy; .long 0
	.long 0x73c3a79
	.long .Lname2682 /* index: 2682 */
	.weak pagedir_isuserwritable; .long pagedir_isuserwritable
	.reloc ., R_386_SIZE32, pagedir_isuserwritable; .long 0
	.long 0xa749315
	.long .Lname2683 /* index: 2683 */
	.weak cpu_delrunningtask; .long cpu_delrunningtask
	.reloc ., R_386_SIZE32, cpu_delrunningtask; .long 0
	.long 0x2d0ba7b
	.long .Lname2684 /* index: 2684 */
	.weak pipe_reader_create; .long pipe_reader_create
	.reloc ., R_386_SIZE32, pipe_reader_create; .long 0
	.long 0xa6f7f85
	.long 0 /* index: 2685 */
	.long 0
	.long 0
	.long 0
	.long .Lname2686 /* index: 2686 */
	.weak vpage_free_untraced; .long vpage_free_untraced
	.reloc ., R_386_SIZE32, vpage_free_untraced; .long 0
	.long 0x554f414
	.long .Lname2687 /* index: 2687 */
	.weak page_freeone; .long page_freeone
	.reloc ., R_386_SIZE32, page_freeone; .long 0
	.long 0xaec7f15
	.long .Lname2688 /* index: 2688 */
	.weak pagedir_mapone_p; .long pagedir_mapone_p
	.reloc ., R_386_SIZE32, pagedir_mapone_p; .long 0
	.long 0x3e36a80
	.long .Lname2689 /* index: 2689 */
	.weak sys_rpc_service; .long sys_rpc_service
	.reloc ., R_386_SIZE32, sys_rpc_service; .long 0
	.long 0xa0dbf5
	.long 0 /* index: 2690 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2691 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2692 */
	.long 0
	.long 0
	.long 0
	.long .Lname2693 /* index: 2693 */
	.weak cpu_ipi_service; .long cpu_ipi_service
	.reloc ., R_386_SIZE32, cpu_ipi_service; .long 0
	.long 0x2a9ca85
	.long .Lname2694 /* index: 2694 */
	.weak vm_datapart_readv; .long vm_datapart_readv
	.reloc ., R_386_SIZE32, vm_datapart_readv; .long 0
	.long 0x2bdea86
	.long .Lname2695 /* index: 2695 */
	.weak x86_vm86_inw; .long x86_vm86_inw
	.reloc ., R_386_SIZE32, x86_vm86_inw; .long 0
	.long 0x7019a87
	.long .Lname2696 /* index: 2696 */
	.weak task_waitfor_norpc_nx; .long task_waitfor_norpc_nx
	.reloc ., R_386_SIZE32, task_waitfor_norpc_nx; .long 0
	.long 0x6767a88
	.long 0 /* index: 2697 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2698 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2699 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2700 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2701 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2702 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2703 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2704 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2705 */
	.long 0
	.long 0
	.long 0
	.long .Lname2706 /* index: 2706 */
	.weak x86_vm86_inb; .long x86_vm86_inb
	.reloc ., R_386_SIZE32, x86_vm86_inb; .long 0
	.long 0x7019a92
	.long .Lname2707 /* index: 2707 */
	.weak task_setprocess; .long task_setprocess
	.reloc ., R_386_SIZE32, task_setprocess; .long 0
	.long 0xda37a93
	.long .Lname2708 /* index: 2708 */
	.weak handle_installat; .long handle_installat
	.reloc ., R_386_SIZE32, handle_installat; .long 0
	.long 0x18baa94
	.long .Lname2709 /* index: 2709 */
	.weak x86_syscall_restart_mode; .long x86_syscall_restart_mode
	.reloc ., R_386_SIZE32, x86_syscall_restart_mode; .long 0
	.long 0x84c6a95
	.long .Lname2710 /* index: 2710 */
	.weak sys_clone; .long sys_clone
	.reloc ., R_386_SIZE32, sys_clone; .long 0
	.long 0x95a6f45
	.long .Lname2711 /* index: 2711 */
	.weak vio_writew; .long vio_writew
	.reloc ., R_386_SIZE32, vio_writew; .long 0
	.long 0x6f0da97
	.long .Lname2712 /* index: 2712 */
	.weak task_schedule_user_srpc_nx; .long task_schedule_user_srpc_nx
	.reloc ., R_386_SIZE32, task_schedule_user_srpc_nx; .long 0
	.long 0xa45ba98
	.long .Lname2713 /* index: 2713 */
	.weak tty_device_startfwd; .long tty_device_startfwd
	.reloc ., R_386_SIZE32, tty_device_startfwd; .long 0
	.long 0xdcea1c4
	.long 0 /* index: 2714 */
	.long 0
	.long 0
	.long 0
	.long .Lname2715 /* index: 2715 */
	.weak sys_shutdown; .long sys_shutdown
	.reloc ., R_386_SIZE32, sys_shutdown; .long 0
	.long 0x87a404e
	.long .Lname2716 /* index: 2716 */
	.weak x86_vm86_inl; .long x86_vm86_inl
	.reloc ., R_386_SIZE32, x86_vm86_inl; .long 0
	.long 0x7019a9c
	.long .Lname2717 /* index: 2717 */
	.weak vm_tasklock_endwrite; .long vm_tasklock_endwrite
	.reloc ., R_386_SIZE32, vm_tasklock_endwrite; .long 0
	.long 0x68a2ad5
	.long 0 /* index: 2718 */
	.long 0
	.long 0
	.long 0
	.long .Lname2719 /* index: 2719 */
	.weak devfs_lock_write; .long devfs_lock_write
	.reloc ., R_386_SIZE32, devfs_lock_write; .long 0
	.long 0xefa29c5
	.long .Lname2720 /* index: 2720 */
	.weak directory_getcaseentry_p; .long directory_getcaseentry_p
	.reloc ., R_386_SIZE32, directory_getcaseentry_p; .long 0
	.long 0xb2b6aa0
	.long .Lname2721 /* index: 2721 */
	.weak x86_this_kernel_sp0; .long x86_this_kernel_sp0
	.reloc ., R_386_SIZE32, x86_this_kernel_sp0; .long 0
	.long 0xc1c70
	.long .Lname2722 /* index: 2722 */
	.weak vio_readb; .long vio_readb
	.reloc ., R_386_SIZE32, vio_readb; .long 0
	.long 0x568caa2
	.long .Lname2723 /* index: 2723 */
	.weak task_schedule_synchronous_srpc; .long task_schedule_synchronous_srpc
	.reloc ., R_386_SIZE32, task_schedule_synchronous_srpc; .long 0
	.long 0x9ef5aa3
	.long .Lname2724 /* index: 2724 */
	.weak _this_kernel_stack_part; .long _this_kernel_stack_part
	.reloc ., R_386_SIZE32, _this_kernel_stack_part; .long 0
	.long 0xb77aaa4
	.long .Lname2725 /* index: 2725 */
	.weak path_lock_downgrade; .long path_lock_downgrade
	.reloc ., R_386_SIZE32, path_lock_downgrade; .long 0
	.long 0xf653aa5
	.long 0 /* index: 2726 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2727 */
	.long 0
	.long 0
	.long 0
	.long .Lname2728 /* index: 2728 */
	.weak path_sprintentex; .long path_sprintentex
	.reloc ., R_386_SIZE32, path_sprintentex; .long 0
	.long 0xbc74aa8
	.long 0 /* index: 2729 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2730 */
	.long 0
	.long 0
	.long 0
	.long .Lname2731 /* index: 2731 */
	.weak cpu_addrunningtask; .long cpu_addrunningtask
	.reloc ., R_386_SIZE32, cpu_addrunningtask; .long 0
	.long 0x450baab
	.long .Lname2732 /* index: 2732 */
	.weak vio_readl; .long vio_readl
	.reloc ., R_386_SIZE32, vio_readl; .long 0
	.long 0x568caac
	.long .Lname2733 /* index: 2733 */
	.weak sys_setfsuid32; .long sys_setfsuid32
	.reloc ., R_386_SIZE32, sys_setfsuid32; .long 0
	.long 0xd3d6c72
	.long 0 /* index: 2734 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2735 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2736 */
	.long 0
	.long 0
	.long 0
	.long .Lname2737 /* index: 2737 */
	.weak driver_symbol_ex; .long driver_symbol_ex
	.reloc ., R_386_SIZE32, driver_symbol_ex; .long 0
	.long 0xf58d1c8
	.long 0 /* index: 2738 */
	.long 0
	.long 0
	.long 0
	.long .Lname2739 /* index: 2739 */
	.weak dbg_ungetc; .long dbg_ungetc
	.reloc ., R_386_SIZE32, dbg_ungetc; .long 0
	.long 0x6c27473
	.long .Lname2740 /* index: 2740 */
	.weak x86_fpu_current; .long x86_fpu_current
	.reloc ., R_386_SIZE32, x86_fpu_current; .long 0
	.long 0x6948ab4
	.long .Lname2741 /* index: 2741 */
	.weak sys_sendfile; .long sys_sendfile
	.reloc ., R_386_SIZE32, sys_sendfile; .long 0
	.long 0xdfa5ab5
	.long .Lname2742 /* index: 2742 */
	.weak sys_pwritevf; .long sys_pwritevf
	.reloc ., R_386_SIZE32, sys_pwritevf; .long 0
	.long 0x9403ab6
	.long .Lname2743 /* index: 2743 */
	.weak vio_readw; .long vio_readw
	.reloc ., R_386_SIZE32, vio_readw; .long 0
	.long 0x568cab7
	.long 0 /* index: 2744 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2745 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2746 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2747 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2748 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2749 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2750 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2751 */
	.long 0
	.long 0
	.long 0
	.long .Lname2752 /* index: 2752 */
	.weak sys_ftruncate64; .long sys_ftruncate64
	.reloc ., R_386_SIZE32, sys_ftruncate64; .long 0
	.long 0xdc56a54
	.long 0 /* index: 2753 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2754 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2755 */
	.long 0
	.long 0
	.long 0
	.long .Lname2756 /* index: 2756 */
	.weak directory_mknod; .long directory_mknod
	.reloc ., R_386_SIZE32, directory_mknod; .long 0
	.long 0x7fadac4
	.long .Lname2757 /* index: 2757 */
	.weak sys_tee; .long sys_tee
	.reloc ., R_386_SIZE32, sys_tee; .long 0
	.long 0xb096ac5
	.long 0 /* index: 2758 */
	.long 0
	.long 0
	.long 0
	.long .Lname2759 /* index: 2759 */
	.weak sys_rt_sigpending; .long sys_rt_sigpending
	.reloc ., R_386_SIZE32, sys_rt_sigpending; .long 0
	.long 0xf593ac7
	.long 0 /* index: 2760 */
	.long 0
	.long 0
	.long 0
	.long .Lname2761 /* index: 2761 */
	.weak sighand_destroy; .long sighand_destroy
	.reloc ., R_386_SIZE32, sighand_destroy; .long 0
	.long 0x7228ac9
	.long 0 /* index: 2762 */
	.long 0
	.long 0
	.long 0
	.long .Lname2763 /* index: 2763 */
	.weak sys_readlink; .long sys_readlink
	.reloc ., R_386_SIZE32, sys_readlink; .long 0
	.long 0xccbbacb
	.long 0 /* index: 2764 */
	.long 0
	.long 0
	.long 0
	.long .Lname2765 /* index: 2765 */
	.weak vm_do_allocram; .long vm_do_allocram
	.reloc ., R_386_SIZE32, vm_do_allocram; .long 0
	.long 0x28efacd
	.long 0 /* index: 2766 */
	.long 0
	.long 0
	.long 0
	.long .Lname2767 /* index: 2767 */
	.weak sys_sync; .long sys_sync
	.reloc ., R_386_SIZE32, sys_sync; .long 0
	.long 0x96a9f3
	.long .Lname2768 /* index: 2768 */
	.weak vm_kernel_syncall; .long vm_kernel_syncall
	.reloc ., R_386_SIZE32, vm_kernel_syncall; .long 0
	.long 0x80d105c
	.long .Lname2769 /* index: 2769 */
	.weak sys_getgid; .long sys_getgid
	.reloc ., R_386_SIZE32, sys_getgid; .long 0
	.long 0x5db1d64
	.long .Lname2770 /* index: 2770 */
	.weak sys_getegid32; .long sys_getegid32
	.reloc ., R_386_SIZE32, sys_getegid32; .long 0
	.long 0x1b4aad2
	.long .Lname2771 /* index: 2771 */
	.weak unwind_fde_exec; .long unwind_fde_exec
	.reloc ., R_386_SIZE32, unwind_fde_exec; .long 0
	.long 0x4b13723
	.long .Lname2772 /* index: 2772 */
	.weak superblock_nodeslock_tryread; .long superblock_nodeslock_tryread
	.reloc ., R_386_SIZE32, superblock_nodeslock_tryread; .long 0
	.long 0xda0ead4
	.long .Lname2773 /* index: 2773 */
	.weak debug_sections_addr2line; .long debug_sections_addr2line
	.reloc ., R_386_SIZE32, debug_sections_addr2line; .long 0
	.long 0xd324ad5
	.long 0 /* index: 2774 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2775 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2776 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2777 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2778 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2779 */
	.long 0
	.long 0
	.long 0
	.long .Lname2780 /* index: 2780 */
	.weak path_traversenfull; .long path_traversenfull
	.reloc ., R_386_SIZE32, path_traversenfull; .long 0
	.long 0x564badc
	.long 0 /* index: 2781 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2782 */
	.long 0
	.long 0
	.long 0
	.long .Lname2783 /* index: 2783 */
	.weak vm_syncone; .long vm_syncone
	.reloc ., R_386_SIZE32, vm_syncone; .long 0
	.long 0xb035725
	.long .Lname2784 /* index: 2784 */
	.weak _this_taskgroup; .long _this_taskgroup
	.reloc ., R_386_SIZE32, _this_taskgroup; .long 0
	.long 0x7179ae0
	.long .Lname2785 /* index: 2785 */
	.weak mouse_device_vwheel_nopr; .long mouse_device_vwheel_nopr
	.reloc ., R_386_SIZE32, mouse_device_vwheel_nopr; .long 0
	.long 0x3a3aee2
	.long .Lname2786 /* index: 2786 */
	.weak sys_get_exception_handler; .long sys_get_exception_handler
	.reloc ., R_386_SIZE32, sys_get_exception_handler; .long 0
	.long 0xa9f6ae2
	.long .Lname2787 /* index: 2787 */
	.weak aio_buffer_copyfromphys; .long aio_buffer_copyfromphys
	.reloc ., R_386_SIZE32, aio_buffer_copyfromphys; .long 0
	.long 0x516dae3
	.long .Lname2788 /* index: 2788 */
	.weak sys_gettimeofday64; .long sys_gettimeofday64
	.reloc ., R_386_SIZE32, sys_gettimeofday64; .long 0
	.long 0xec0fae4
	.long .Lname2789 /* index: 2789 */
	.weak sys_getcpu; .long sys_getcpu
	.reloc ., R_386_SIZE32, sys_getcpu; .long 0
	.long 0x5db1ae5
	.long 0 /* index: 2790 */
	.long 0
	.long 0
	.long 0
	.long .Lname2791 /* index: 2791 */
	.weak cpu_quantum_remaining; .long cpu_quantum_remaining
	.reloc ., R_386_SIZE32, cpu_quantum_remaining; .long 0
	.long 0x395fae7
	.long 0 /* index: 2792 */
	.long 0
	.long 0
	.long 0
	.long .Lname2793 /* index: 2793 */
	.weak x86_asm_except_personality; .long x86_asm_except_personality
	.reloc ., R_386_SIZE32, x86_asm_except_personality; .long 0
	.long 0xe2c0ae9
	.long 0 /* index: 2794 */
	.long 0
	.long 0
	.long 0
	.long .Lname2795 /* index: 2795 */
	.weak isr_unregister_any_at; .long isr_unregister_any_at
	.reloc ., R_386_SIZE32, isr_unregister_any_at; .long 0
	.long 0x32371f4
	.long .Lname2796 /* index: 2796 */
	.weak vio_writel; .long vio_writel
	.reloc ., R_386_SIZE32, vio_writel; .long 0
	.long 0x6f0daec
	.long .Lname2797 /* index: 2797 */
	.weak cpu_run_current_and_remember; .long cpu_run_current_and_remember
	.reloc ., R_386_SIZE32, cpu_run_current_and_remember; .long 0
	.long 0x5baf9d2
	.long 0 /* index: 2798 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2799 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2800 */
	.long 0
	.long 0
	.long 0
	.long .Lname2801 /* index: 2801 */
	.weak superblock_mountlock_write_nx; .long superblock_mountlock_write_nx
	.reloc ., R_386_SIZE32, superblock_mountlock_write_nx; .long 0
	.long 0x91da728
	.long 0 /* index: 2802 */
	.long 0
	.long 0
	.long 0
	.long .Lname2803 /* index: 2803 */
	.weak unwind_instruction_succ; .long unwind_instruction_succ
	.reloc ., R_386_SIZE32, unwind_instruction_succ; .long 0
	.long 0xb64baf3
	.long .Lname2804 /* index: 2804 */
	.weak json_writer_putuint64; .long json_writer_putuint64
	.reloc ., R_386_SIZE32, json_writer_putuint64; .long 0
	.long 0x73eaaf4
	.long .Lname2805 /* index: 2805 */
	.weak _this_exception_info; .long _this_exception_info
	.reloc ., R_386_SIZE32, _this_exception_info; .long 0
	.long 0x2692daf
	.long 0 /* index: 2806 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2807 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2808 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2809 */
	.long 0
	.long 0
	.long 0
	.long .Lname2810 /* index: 2810 */
	.weak path_free; .long path_free
	.reloc ., R_386_SIZE32, path_free; .long 0
	.long 0xae5ae35
	.long 0 /* index: 2811 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2812 */
	.long 0
	.long 0
	.long 0
	.long .Lname2813 /* index: 2813 */
	.weak vm_datapart_do_copyram; .long vm_datapart_do_copyram
	.reloc ., R_386_SIZE32, vm_datapart_do_copyram; .long 0
	.long 0xb4f0afd
	.long 0 /* index: 2814 */
	.long 0
	.long 0
	.long 0
	.long .Lname2815 /* index: 2815 */
	.weak rwlock_pollwrite; .long rwlock_pollwrite
	.reloc ., R_386_SIZE32, rwlock_pollwrite; .long 0
	.long 0x89689d5
	.long .Lname2816 /* index: 2816 */
	.weak pagedir_unprepare_map_p; .long pagedir_unprepare_map_p
	.reloc ., R_386_SIZE32, pagedir_unprepare_map_p; .long 0
	.long 0x7bdfb00
	.long 0 /* index: 2817 */
	.long 0
	.long 0
	.long 0
	.long .Lname2818 /* index: 2818 */
	.weak sighand_reset_handler; .long sighand_reset_handler
	.reloc ., R_386_SIZE32, sighand_reset_handler; .long 0
	.long 0xb656b02
	.long .Lname2819 /* index: 2819 */
	.weak vm_datablock_vio_write_phys; .long vm_datablock_vio_write_phys
	.reloc ., R_386_SIZE32, vm_datablock_vio_write_phys; .long 0
	.long 0x2726b03
	.long .Lname2820 /* index: 2820 */
	.weak vm_read; .long vm_read
	.reloc ., R_386_SIZE32, vm_read; .long 0
	.long 0xd368b04
	.long .Lname2821 /* index: 2821 */
	.weak __crt_unreachable; .long __crt_unreachable
	.reloc ., R_386_SIZE32, __crt_unreachable; .long 0
	.long 0xd917b05
	.long 0 /* index: 2822 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2823 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2824 */
	.long 0
	.long 0
	.long 0
	.long .Lname2825 /* index: 2825 */
	.weak cpu_sendipi; .long cpu_sendipi
	.reloc ., R_386_SIZE32, cpu_sendipi; .long 0
	.long 0x9eeeb09
	.long 0 /* index: 2826 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2827 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2828 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2829 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2830 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2831 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2832 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2833 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2834 */
	.long 0
	.long 0
	.long 0
	.long .Lname2835 /* index: 2835 */
	.weak inode_sync; .long inode_sync
	.reloc ., R_386_SIZE32, inode_sync; .long 0
	.long 0xab1ab13
	.long .Lname2836 /* index: 2836 */
	.weak sys_symlinkat; .long sys_symlinkat
	.reloc ., R_386_SIZE32, sys_symlinkat; .long 0
	.long 0x9273b14
	.long .Lname2837 /* index: 2837 */
	.weak cpu_apply_ucpustate; .long cpu_apply_ucpustate
	.reloc ., R_386_SIZE32, cpu_apply_ucpustate; .long 0
	.long 0xa8c9b15
	.long 0 /* index: 2838 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2839 */
	.long 0
	.long 0
	.long 0
	.long .Lname2840 /* index: 2840 */
	.weak vm_startdma_nx; .long vm_startdma_nx
	.reloc ., R_386_SIZE32, vm_startdma_nx; .long 0
	.long 0x9d9db18
	.long .Lname2841 /* index: 2841 */
	.weak unwind_cfa_apply; .long unwind_cfa_apply
	.reloc ., R_386_SIZE32, unwind_cfa_apply; .long 0
	.long 0x717eb19
	.long 0 /* index: 2842 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2843 */
	.long 0
	.long 0
	.long 0
	.long .Lname2844 /* index: 2844 */
	.weak ttybase_device_ioctl; .long ttybase_device_ioctl
	.reloc ., R_386_SIZE32, ttybase_device_ioctl; .long 0
	.long 0x50c1b1c
	.long 0 /* index: 2845 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2846 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2847 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2848 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2849 */
	.long 0
	.long 0
	.long 0
	.long .Lname2850 /* index: 2850 */
	.weak vio_readw_aligned; .long vio_readw_aligned
	.reloc ., R_386_SIZE32, vio_readw_aligned; .long 0
	.long 0xe57ef4
	.long .Lname2851 /* index: 2851 */
	.weak block_device_writev_phys; .long block_device_writev_phys
	.reloc ., R_386_SIZE32, block_device_writev_phys; .long 0
	.long 0x6f74b23
	.long .Lname2852 /* index: 2852 */
	.weak isr_register_at; .long isr_register_at
	.reloc ., R_386_SIZE32, isr_register_at; .long 0
	.long 0x2c4cb24
	.long .Lname2853 /* index: 2853 */
	.weak driver_with_file; .long driver_with_file
	.reloc ., R_386_SIZE32, driver_with_file; .long 0
	.long 0x6271b25
	.long 0 /* index: 2854 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2855 */
	.long 0
	.long 0
	.long 0
	.long .Lname2856 /* index: 2856 */
	.weak krealign_in_place_nx; .long krealign_in_place_nx
	.reloc ., R_386_SIZE32, krealign_in_place_nx; .long 0
	.long 0xe919b28
	.long .Lname2857 /* index: 2857 */
	.weak tty_device_forward_destroy; .long tty_device_forward_destroy
	.reloc ., R_386_SIZE32, tty_device_forward_destroy; .long 0
	.long 0x762cb29
	.long .Lname2858 /* index: 2858 */
	.weak vpage_realloc_untraced; .long vpage_realloc_untraced
	.reloc ., R_386_SIZE32, vpage_realloc_untraced; .long 0
	.long 0x51c9214
	.long 0 /* index: 2859 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2860 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2861 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2862 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2863 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2864 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2865 */
	.long 0
	.long 0
	.long 0
	.long .Lname2866 /* index: 2866 */
	.weak sys_linux_stat32; .long sys_linux_stat32
	.reloc ., R_386_SIZE32, sys_linux_stat32; .long 0
	.long 0x836b32
	.long .Lname2867 /* index: 2867 */
	.weak slab_kmalloc; .long slab_kmalloc
	.reloc ., R_386_SIZE32, slab_kmalloc; .long 0
	.long 0x7966b33
	.long .Lname2868 /* index: 2868 */
	.weak vmb_node_insert; .long vmb_node_insert
	.reloc ., R_386_SIZE32, vmb_node_insert; .long 0
	.long 0xda0bb34
	.long .Lname2869 /* index: 2869 */
	.weak sys_epoll_create; .long sys_epoll_create
	.reloc ., R_386_SIZE32, sys_epoll_create; .long 0
	.long 0x6a4b35
	.long .Lname2870 /* index: 2870 */
	.weak json_parser_prev; .long json_parser_prev
	.reloc ., R_386_SIZE32, json_parser_prev; .long 0
	.long 0x827eb36
	.long 0 /* index: 2871 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2872 */
	.long 0
	.long 0
	.long 0
	.long .Lname2873 /* index: 2873 */
	.weak strtou64; .long strtou64
	.reloc ., R_386_SIZE32, strtou64; .long 0
	.long 0xb9b6f34
	.long 0 /* index: 2874 */
	.long 0
	.long 0
	.long 0
	.long .Lname2875 /* index: 2875 */
	.weak sys_rt_tgsigqueueinfo; .long sys_rt_tgsigqueueinfo
	.reloc ., R_386_SIZE32, sys_rt_tgsigqueueinfo; .long 0
	.long 0xb4df1df
	.long .Lname2876 /* index: 2876 */
	.weak fs_filesystems_loadall; .long fs_filesystems_loadall
	.reloc ., R_386_SIZE32, fs_filesystems_loadall; .long 0
	.long 0x6e7fb3c
	.long .Lname2877 /* index: 2877 */
	.weak sys_sched_getparam; .long sys_sched_getparam
	.reloc ., R_386_SIZE32, sys_sched_getparam; .long 0
	.long 0x2ed9b3d
	.long .Lname2878 /* index: 2878 */
	.weak sys_setregid; .long sys_setregid
	.reloc ., R_386_SIZE32, sys_setregid; .long 0
	.long 0xb082b64
	.long .Lname2879 /* index: 2879 */
	.weak sys_sendto; .long sys_sendto
	.reloc ., R_386_SIZE32, sys_sendto; .long 0
	.long 0x69dfb3f
	.long .Lname2880 /* index: 2880 */
	.weak pagedir_unwriteone_p; .long pagedir_unwriteone_p
	.reloc ., R_386_SIZE32, pagedir_unwriteone_p; .long 0
	.long 0xbdc2b40
	.long 0 /* index: 2881 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2882 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2883 */
	.long 0
	.long 0
	.long 0
	.long .Lname2884 /* index: 2884 */
	.weak sys_fstatfs64; .long sys_fstatfs64
	.reloc ., R_386_SIZE32, sys_fstatfs64; .long 0
	.long 0x1838b44
	.long .Lname2885 /* index: 2885 */
	.weak timespec_to_qtime; .long timespec_to_qtime
	.reloc ., R_386_SIZE32, timespec_to_qtime; .long 0
	.long 0xf783b45
	.long 0 /* index: 2886 */
	.long 0
	.long 0
	.long 0
	.long .Lname2887 /* index: 2887 */
	.weak inode_readv_phys_blocking; .long inode_readv_phys_blocking
	.reloc ., R_386_SIZE32, inode_readv_phys_blocking; .long 0
	.long 0xd7cbb47
	.long 0 /* index: 2888 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2889 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2890 */
	.long 0
	.long 0
	.long 0
	.long .Lname2891 /* index: 2891 */
	.weak sys_frealpath4; .long sys_frealpath4
	.reloc ., R_386_SIZE32, sys_frealpath4; .long 0
	.long 0x8a355b4
	.long 0 /* index: 2892 */
	.long 0
	.long 0
	.long 0
	.long .Lname2893 /* index: 2893 */
	.weak abort; .long abort
	.reloc ., R_386_SIZE32, abort; .long 0
	.long 0x679694
	.long 0 /* index: 2894 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2895 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2896 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2897 */
	.long 0
	.long 0
	.long 0
	.long .Lname2898 /* index: 2898 */
	.weak block_device_awritev_phys_sector; .long block_device_awritev_phys_sector
	.reloc ., R_386_SIZE32, block_device_awritev_phys_sector; .long 0
	.long 0xb832b52
	.long 0 /* index: 2899 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2900 */
	.long 0
	.long 0
	.long 0
	.long .Lname2901 /* index: 2901 */
	.weak devfs_remove; .long devfs_remove
	.reloc ., R_386_SIZE32, devfs_remove; .long 0
	.long 0x290b55
	.long .Lname2902 /* index: 2902 */
	.weak sys_readvf; .long sys_readvf
	.reloc ., R_386_SIZE32, sys_readvf; .long 0
	.long 0x68ccb56
	.long .Lname2903 /* index: 2903 */
	.weak ansitty_putuni; .long ansitty_putuni
	.reloc ., R_386_SIZE32, ansitty_putuni; .long 0
	.long 0x3dc0739
	.long .Lname2904 /* index: 2904 */
	.weak rwlock_write_nx; .long rwlock_write_nx
	.reloc ., R_386_SIZE32, rwlock_write_nx; .long 0
	.long 0xc503b58
	.long .Lname2905 /* index: 2905 */
	.weak dbg_isholding_alt; .long dbg_isholding_alt
	.reloc ., R_386_SIZE32, dbg_isholding_alt; .long 0
	.long 0xbab9e4
	.long 0 /* index: 2906 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2907 */
	.long 0
	.long 0
	.long 0
	.long .Lname2908 /* index: 2908 */
	.weak aio_multihandle_generic_func; .long aio_multihandle_generic_func
	.reloc ., R_386_SIZE32, aio_multihandle_generic_func; .long 0
	.long 0x227c0d3
	.long 0 /* index: 2909 */
	.long 0
	.long 0
	.long 0
	.long .Lname2910 /* index: 2910 */
	.weak x86_lapic_version; .long x86_lapic_version
	.reloc ., R_386_SIZE32, x86_lapic_version; .long 0
	.long 0xe34db5e
	.long .Lname2911 /* index: 2911 */
	.weak sys_readf; .long sys_readf
	.reloc ., R_386_SIZE32, sys_readf; .long 0
	.long 0x968cca6
	.long 0 /* index: 2912 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2913 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2914 */
	.long 0
	.long 0
	.long 0
	.long .Lname2915 /* index: 2915 */
	.weak ringbuffer_rseek; .long ringbuffer_rseek
	.reloc ., R_386_SIZE32, ringbuffer_rseek; .long 0
	.long 0xbf5c73b
	.long .Lname2916 /* index: 2916 */
	.weak superblock_mountlock_read; .long superblock_mountlock_read
	.reloc ., R_386_SIZE32, superblock_mountlock_read; .long 0
	.long 0x7331b64
	.long .Lname2917 /* index: 2917 */
	.weak sys_setdomainname; .long sys_setdomainname
	.reloc ., R_386_SIZE32, sys_setdomainname; .long 0
	.long 0xe56fb65
	.long 0 /* index: 2918 */
	.long 0
	.long 0
	.long 0
	.long .Lname2919 /* index: 2919 */
	.weak boot_cpustate; .long boot_cpustate
	.reloc ., R_386_SIZE32, boot_cpustate; .long 0
	.long 0xeac0d65
	.long 0 /* index: 2920 */
	.long 0
	.long 0
	.long 0
	.long .Lname2921 /* index: 2921 */
	.weak directory_getcaseentry; .long directory_getcaseentry
	.reloc ., R_386_SIZE32, directory_getcaseentry; .long 0
	.long 0x7cb2b69
	.long 0 /* index: 2922 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2923 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2924 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2925 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2926 */
	.long 0
	.long 0
	.long 0
	.long .Lname2927 /* index: 2927 */
	.weak inode_read; .long inode_read
	.reloc ., R_386_SIZE32, inode_read; .long 0
	.long 0xab18e24
	.long 0 /* index: 2928 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2929 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2930 */
	.long 0
	.long 0
	.long 0
	.long .Lname2931 /* index: 2931 */
	.weak sys_fdatasync; .long sys_fdatasync
	.reloc ., R_386_SIZE32, sys_fdatasync; .long 0
	.long 0x3a1f493
	.long .Lname2932 /* index: 2932 */
	.weak stack_current; .long stack_current
	.reloc ., R_386_SIZE32, stack_current; .long 0
	.long 0x6e2b74
	.long 0 /* index: 2933 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2934 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2935 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2936 */
	.long 0
	.long 0
	.long 0
	.long .Lname2937 /* index: 2937 */
	.weak sys_kfstatat; .long sys_kfstatat
	.reloc ., R_386_SIZE32, sys_kfstatat; .long 0
	.long 0xa1a1c94
	.long 0 /* index: 2938 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2939 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2940 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2941 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2942 */
	.long 0
	.long 0
	.long 0
	.long .Lname2943 /* index: 2943 */
	.weak superblock_mountlock_upgrade; .long superblock_mountlock_upgrade
	.reloc ., R_386_SIZE32, superblock_mountlock_upgrade; .long 0
	.long 0x56ff495
	.long .Lname2944 /* index: 2944 */
	.weak path_lock_upgrade; .long path_lock_upgrade
	.reloc ., R_386_SIZE32, path_lock_upgrade; .long 0
	.long 0xa0dac25
	.long .Lname2945 /* index: 2945 */
	.weak mempsetq; .long mempsetq
	.reloc ., R_386_SIZE32, mempsetq; .long 0
	.long 0xc479b81
	.long .Lname2946 /* index: 2946 */
	.weak sys_dup2; .long sys_dup2
	.reloc ., R_386_SIZE32, sys_dup2; .long 0
	.long 0x95bb82
	.long .Lname2947 /* index: 2947 */
	.weak sys_dup3; .long sys_dup3
	.reloc ., R_386_SIZE32, sys_dup3; .long 0
	.long 0x95bb83
	.long 0 /* index: 2948 */
	.long 0
	.long 0
	.long 0
	.long .Lname2949 /* index: 2949 */
	.weak quantum_time; .long quantum_time
	.reloc ., R_386_SIZE32, quantum_time; .long 0
	.long 0xdbd2b85
	.long .Lname2950 /* index: 2950 */
	.weak addr2line_printf; .long addr2line_printf
	.reloc ., R_386_SIZE32, addr2line_printf; .long 0
	.long 0x3ec7b86
	.long .Lname2951 /* index: 2951 */
	.weak mempsetw; .long mempsetw
	.reloc ., R_386_SIZE32, mempsetw; .long 0
	.long 0xc479b87
	.long .Lname2952 /* index: 2952 */
	.weak unwind_getreg_lcpustate; .long unwind_getreg_lcpustate
	.reloc ., R_386_SIZE32, unwind_getreg_lcpustate; .long 0
	.long 0xb8c48b5
	.long .Lname2953 /* index: 2953 */
	.weak driver_destroy; .long driver_destroy
	.reloc ., R_386_SIZE32, driver_destroy; .long 0
	.long 0x3c67b89
	.long 0 /* index: 2954 */
	.long 0
	.long 0
	.long 0
	.long .Lname2955 /* index: 2955 */
	.weak sys_getdrives; .long sys_getdrives
	.reloc ., R_386_SIZE32, sys_getdrives; .long 0
	.long 0x1b25173
	.long .Lname2956 /* index: 2956 */
	.weak memmovel; .long memmovel
	.reloc ., R_386_SIZE32, memmovel; .long 0
	.long 0xc446b8c
	.long .Lname2957 /* index: 2957 */
	.weak sys_lremovexattr; .long sys_lremovexattr
	.reloc ., R_386_SIZE32, sys_lremovexattr; .long 0
	.long 0xaf19f42
	.long .Lname2958 /* index: 2958 */
	.weak ramfs_symlink_type; .long ramfs_symlink_type
	.reloc ., R_386_SIZE32, ramfs_symlink_type; .long 0
	.long 0x63ebf15
	.long 0 /* index: 2959 */
	.long 0
	.long 0
	.long 0
	.long .Lname2960 /* index: 2960 */
	.weak sys_rt_sigtimedwait64; .long sys_rt_sigtimedwait64
	.reloc ., R_386_SIZE32, sys_rt_sigtimedwait64; .long 0
	.long 0xd5519b4
	.long 0 /* index: 2961 */
	.long 0
	.long 0
	.long 0
	.long .Lname2962 /* index: 2962 */
	.weak keyboard_device_putkey_nopr; .long keyboard_device_putkey_nopr
	.reloc ., R_386_SIZE32, keyboard_device_putkey_nopr; .long 0
	.long 0xdcccb92
	.long .Lname2963 /* index: 2963 */
	.weak vm_datapart_sync; .long vm_datapart_sync
	.reloc ., R_386_SIZE32, vm_datapart_sync; .long 0
	.long 0x32bfb93
	.long .Lname2964 /* index: 2964 */
	.weak kernel_debugtrap_enabled; .long kernel_debugtrap_enabled
	.reloc ., R_386_SIZE32, kernel_debugtrap_enabled; .long 0
	.long 0x3b93b94
	.long .Lname2965 /* index: 2965 */
	.weak vm_tasklock_tryupgrade; .long vm_tasklock_tryupgrade
	.reloc ., R_386_SIZE32, vm_tasklock_tryupgrade; .long 0
	.long 0x8f7eb95
	.long 0 /* index: 2966 */
	.long 0
	.long 0
	.long 0
	.long .Lname2967 /* index: 2967 */
	.weak dbg_getuni; .long dbg_getuni
	.reloc ., R_386_SIZE32, dbg_getuni; .long 0
	.long 0x5da1499
	.long 0 /* index: 2968 */
	.long 0
	.long 0
	.long 0
	.long .Lname2969 /* index: 2969 */
	.weak sys_unlinkat; .long sys_unlinkat
	.reloc ., R_386_SIZE32, sys_unlinkat; .long 0
	.long 0x4a0e744
	.long .Lname2970 /* index: 2970 */
	.weak pagedir_unmap_userspace; .long pagedir_unmap_userspace
	.reloc ., R_386_SIZE32, pagedir_unmap_userspace; .long 0
	.long 0x4621305
	.long 0 /* index: 2971 */
	.long 0
	.long 0
	.long 0
	.long .Lname2972 /* index: 2972 */
	.weak handle_install; .long handle_install
	.reloc ., R_386_SIZE32, handle_install; .long 0
	.long 0x8118b9c
	.long .Lname2973 /* index: 2973 */
	.weak debuginfo_cu_parser_loadattr_subprogram; .long debuginfo_cu_parser_loadattr_subprogram
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_subprogram; .long 0
	.long 0x9fa0b9d
	.long 0 /* index: 2974 */
	.long 0
	.long 0
	.long 0
	.long .Lname2975 /* index: 2975 */
	.weak json_parser_leave; .long json_parser_leave
	.reloc ., R_386_SIZE32, json_parser_leave; .long 0
	.long 0x25b8745
	.long 0 /* index: 2976 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2977 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2978 */
	.long 0
	.long 0
	.long 0
	.long .Lname2979 /* index: 2979 */
	.weak cpuid_features; .long cpuid_features
	.reloc ., R_386_SIZE32, cpuid_features; .long 0
	.long 0xc346ba3
	.long .Lname2980 /* index: 2980 */
	.weak pidns_trylookup_locked; .long pidns_trylookup_locked
	.reloc ., R_386_SIZE32, pidns_trylookup_locked; .long 0
	.long 0xf007ba4
	.long .Lname2981 /* index: 2981 */
	.weak sys_write; .long sys_write
	.reloc ., R_386_SIZE32, sys_write; .long 0
	.long 0x96f0ba5
	.long .Lname2982 /* index: 2982 */
	.weak sys_fallocate64; .long sys_fallocate64
	.reloc ., R_386_SIZE32, sys_fallocate64; .long 0
	.long 0xcc4b2a4
	.long 0 /* index: 2983 */
	.long 0
	.long 0
	.long 0
	.long .Lname2984 /* index: 2984 */
	.weak unicode_writeutf8; .long unicode_writeutf8
	.reloc ., R_386_SIZE32, unicode_writeutf8; .long 0
	.long 0x57beba8
	.long .Lname2985 /* index: 2985 */
	.weak superblock_mountlock_tryupgrade; .long superblock_mountlock_tryupgrade
	.reloc ., R_386_SIZE32, superblock_mountlock_tryupgrade; .long 0
	.long 0xb5dadb5
	.long 0 /* index: 2986 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2987 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 2988 */
	.long 0
	.long 0
	.long 0
	.long .Lname2989 /* index: 2989 */
	.weak memchr; .long memchr
	.reloc ., R_386_SIZE32, memchr; .long 0
	.long 0x73c39f2
	.long 0 /* index: 2990 */
	.long 0
	.long 0
	.long 0
	.long .Lname2991 /* index: 2991 */
	.weak validate_executable_opt; .long validate_executable_opt
	.reloc ., R_386_SIZE32, validate_executable_opt; .long 0
	.long 0xd67bb34
	.long .Lname2992 /* index: 2992 */
	.weak sys_dup; .long sys_dup
	.reloc ., R_386_SIZE32, sys_dup; .long 0
	.long 0xb095bb0
	.long 0 /* index: 2993 */
	.long 0
	.long 0
	.long 0
	.long .Lname2994 /* index: 2994 */
	.weak task_setprocessgroupleader; .long task_setprocessgroupleader
	.reloc ., R_386_SIZE32, task_setprocessgroupleader; .long 0
	.long 0x6fbbb2
	.long .Lname2995 /* index: 2995 */
	.weak pmembank_type_names; .long pmembank_type_names
	.reloc ., R_386_SIZE32, pmembank_type_names; .long 0
	.long 0xf2efbb3
	.long .Lname2996 /* index: 2996 */
	.weak vmb_mapat; .long vmb_mapat
	.reloc ., R_386_SIZE32, vmb_mapat; .long 0
	.long 0x863fbb4
	.long .Lname2997 /* index: 2997 */
	.weak unwind_setreg_kcpustate; .long unwind_setreg_kcpustate
	.reloc ., R_386_SIZE32, unwind_setreg_kcpustate; .long 0
	.long 0xb8d0bb5
	.long .Lname2998 /* index: 2998 */
	.weak sys_ioctlf; .long sys_ioctlf
	.reloc ., R_386_SIZE32, sys_ioctlf; .long 0
	.long 0x6021bb6
	.long 0 /* index: 2999 */
	.long 0
	.long 0
	.long 0
	.long .Lname3000 /* index: 3000 */
	.weak heap_align_untraced_nx; .long heap_align_untraced_nx
	.reloc ., R_386_SIZE32, heap_align_untraced_nx; .long 0
	.long 0x1a11bb8
	.long .Lname3001 /* index: 3001 */
	.weak vm_kernel_treelock_end; .long vm_kernel_treelock_end
	.reloc ., R_386_SIZE32, vm_kernel_treelock_end; .long 0
	.long 0x30979f4
	.long 0 /* index: 3002 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3003 */
	.long 0
	.long 0
	.long 0
	.long .Lname3004 /* index: 3004 */
	.weak sigmask_check_after_syscall; .long sigmask_check_after_syscall
	.reloc ., R_386_SIZE32, sigmask_check_after_syscall; .long 0
	.long 0xb002bbc
	.long 0 /* index: 3005 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3006 */
	.long 0
	.long 0
	.long 0
	.long .Lname3007 /* index: 3007 */
	.weak sys_madvise; .long sys_madvise
	.reloc ., R_386_SIZE32, sys_madvise; .long 0
	.long 0x300d9f5
	.long 0 /* index: 3008 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3009 */
	.long 0
	.long 0
	.long 0
	.long .Lname3010 /* index: 3010 */
	.weak dbg_default_attr; .long dbg_default_attr
	.reloc ., R_386_SIZE32, dbg_default_attr; .long 0
	.long 0x648ebc2
	.long .Lname3011 /* index: 3011 */
	.weak sigmask_check_s; .long sigmask_check_s
	.reloc ., R_386_SIZE32, sigmask_check_s; .long 0
	.long 0x7d37bc3
	.long .Lname3012 /* index: 3012 */
	.weak sys_linux_stat64; .long sys_linux_stat64
	.reloc ., R_386_SIZE32, sys_linux_stat64; .long 0
	.long 0x836bc4
	.long 0 /* index: 3013 */
	.long 0
	.long 0
	.long 0
	.long .Lname3014 /* index: 3014 */
	.weak dbg_origstate; .long dbg_origstate
	.reloc ., R_386_SIZE32, dbg_origstate; .long 0
	.long 0x567ce45
	.long 0 /* index: 3015 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3016 */
	.long 0
	.long 0
	.long 0
	.long .Lname3017 /* index: 3017 */
	.weak pipe_reader_destroy; .long pipe_reader_destroy
	.reloc ., R_386_SIZE32, pipe_reader_destroy; .long 0
	.long 0x6b6cbc9
	.long 0 /* index: 3018 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3019 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3020 */
	.long 0
	.long 0
	.long 0
	.long .Lname3021 /* index: 3021 */
	.weak sys_fchown32; .long sys_fchown32
	.reloc ., R_386_SIZE32, sys_fchown32; .long 0
	.long 0xe6654a2
	.long 0 /* index: 3022 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3023 */
	.long 0
	.long 0
	.long 0
	.long .Lname3024 /* index: 3024 */
	.weak dbg_scroll_maxline; .long dbg_scroll_maxline
	.reloc ., R_386_SIZE32, dbg_scroll_maxline; .long 0
	.long 0xfb22895
	.long 0 /* index: 3025 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3026 */
	.long 0
	.long 0
	.long 0
	.long .Lname3027 /* index: 3027 */
	.weak regdump_flags; .long regdump_flags
	.reloc ., R_386_SIZE32, regdump_flags; .long 0
	.long 0xee29bd3
	.long .Lname3028 /* index: 3028 */
	.weak __stack_chk_guard; .long __stack_chk_guard
	.reloc ., R_386_SIZE32, __stack_chk_guard; .long 0
	.long 0x9588bd4
	.long .Lname3029 /* index: 3029 */
	.weak dbg_setcur_visible; .long dbg_setcur_visible
	.reloc ., R_386_SIZE32, dbg_setcur_visible; .long 0
	.long 0x70bebd5
	.long 0 /* index: 3030 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3031 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3032 */
	.long 0
	.long 0
	.long 0
	.long .Lname3033 /* index: 3033 */
	.weak dev_tty; .long dev_tty
	.reloc ., R_386_SIZE32, dev_tty; .long 0
	.long 0xacc6bd9
	.long .Lname3034 /* index: 3034 */
	.weak sys_linux_lstat64; .long sys_linux_lstat64
	.reloc ., R_386_SIZE32, sys_linux_lstat64; .long 0
	.long 0x13442d4
	.long .Lname3035 /* index: 3035 */
	.weak path_printex; .long path_printex
	.reloc ., R_386_SIZE32, path_printex; .long 0
	.long 0xe8f4a8
	.long .Lname3036 /* index: 3036 */
	.weak superblock_syncall; .long superblock_syncall
	.reloc ., R_386_SIZE32, superblock_syncall; .long 0
	.long 0xa7e9bdc
	.long 0 /* index: 3037 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3038 */
	.long 0
	.long 0
	.long 0
	.long .Lname3039 /* index: 3039 */
	.weak kernel_debugtrap_r_lcpustate; .long kernel_debugtrap_r_lcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_lcpustate; .long 0
	.long 0xed514a5
	.long .Lname3040 /* index: 3040 */
	.weak pagedir_unmapone_p; .long pagedir_unmapone_p
	.reloc ., R_386_SIZE32, pagedir_unmapone_p; .long 0
	.long 0xf55cbe0
	.long .Lname3041 /* index: 3041 */
	.weak handle_get_directory_entry; .long handle_get_directory_entry
	.reloc ., R_386_SIZE32, handle_get_directory_entry; .long 0
	.long 0x463b5b9
	.long .Lname3042 /* index: 3042 */
	.weak rwlock_reading_r; .long rwlock_reading_r
	.reloc ., R_386_SIZE32, rwlock_reading_r; .long 0
	.long 0x208bbe2
	.long .Lname3043 /* index: 3043 */
	.weak sys_brk; .long sys_brk
	.reloc ., R_386_SIZE32, sys_brk; .long 0
	.long 0xb0959fb
	.long 0 /* index: 3044 */
	.long 0
	.long 0
	.long 0
	.long .Lname3045 /* index: 3045 */
	.weak vm_getfree; .long vm_getfree
	.reloc ., R_386_SIZE32, vm_getfree; .long 0
	.long 0xdcd0be5
	.long .Lname3046 /* index: 3046 */
	.weak inode_areadallv; .long inode_areadallv
	.reloc ., R_386_SIZE32, inode_areadallv; .long 0
	.long 0xed16be6
	.long 0 /* index: 3047 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3048 */
	.long 0
	.long 0
	.long 0
	.long .Lname3049 /* index: 3049 */
	.weak vm_datapart_destroy; .long vm_datapart_destroy
	.reloc ., R_386_SIZE32, vm_datapart_destroy; .long 0
	.long 0xf978be9
	.long 0 /* index: 3050 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3051 */
	.long 0
	.long 0
	.long 0
	.long .Lname3052 /* index: 3052 */
	.weak character_device_poll; .long character_device_poll
	.reloc ., R_386_SIZE32, character_device_poll; .long 0
	.long 0x98b7bec
	.long .Lname3053 /* index: 3053 */
	.weak vio_cmpxch_or_writeb; .long vio_cmpxch_or_writeb
	.reloc ., R_386_SIZE32, vio_cmpxch_or_writeb; .long 0
	.long 0x8230f52
	.long 0 /* index: 3054 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3055 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3056 */
	.long 0
	.long 0
	.long 0
	.long .Lname3057 /* index: 3057 */
	.weak memmoveq; .long memmoveq
	.reloc ., R_386_SIZE32, memmoveq; .long 0
	.long 0xc446bf1
	.long 0 /* index: 3058 */
	.long 0
	.long 0
	.long 0
	.long .Lname3059 /* index: 3059 */
	.weak path_alloc; .long path_alloc
	.reloc ., R_386_SIZE32, path_alloc; .long 0
	.long 0xe515bf3
	.long 0 /* index: 3060 */
	.long 0
	.long 0
	.long 0
	.long .Lname3061 /* index: 3061 */
	.weak kernel_panic_scpustate; .long kernel_panic_scpustate
	.reloc ., R_386_SIZE32, kernel_panic_scpustate; .long 0
	.long 0x78abbf5
	.long 0 /* index: 3062 */
	.long 0
	.long 0
	.long 0
	.long .Lname3063 /* index: 3063 */
	.weak memmovew; .long memmovew
	.reloc ., R_386_SIZE32, memmovew; .long 0
	.long 0xc446bf7
	.long .Lname3064 /* index: 3064 */
	.weak devfs_lock_write_nx; .long devfs_lock_write_nx
	.reloc ., R_386_SIZE32, devfs_lock_write_nx; .long 0
	.long 0x29c5bf8
	.long .Lname3065 /* index: 3065 */
	.weak sys_fmknodat; .long sys_fmknodat
	.reloc ., R_386_SIZE32, sys_fmknodat; .long 0
	.long 0x5b5cf54
	.long 0 /* index: 3066 */
	.long 0
	.long 0
	.long 0
	.long .Lname3067 /* index: 3067 */
	.weak inode_areadallk; .long inode_areadallk
	.reloc ., R_386_SIZE32, inode_areadallk; .long 0
	.long 0xed16bfb
	.long 0 /* index: 3068 */
	.long 0
	.long 0
	.long 0
	.long .Lname3069 /* index: 3069 */
	.weak dbg_vmenuf; .long dbg_vmenuf
	.reloc ., R_386_SIZE32, dbg_vmenuf; .long 0
	.long 0x6d52d66
	.long 0 /* index: 3070 */
	.long 0
	.long 0
	.long 0
	.long .Lname3071 /* index: 3071 */
	.weak devfs_lock_trywrite; .long devfs_lock_trywrite
	.reloc ., R_386_SIZE32, devfs_lock_trywrite; .long 0
	.long 0x1987f55
	.long .Lname3072 /* index: 3072 */
	.weak task_sigstop; .long task_sigstop
	.reloc ., R_386_SIZE32, task_sigstop; .long 0
	.long 0xe560c00
	.long 0 /* index: 3073 */
	.long 0
	.long 0
	.long 0
	.long .Lname3074 /* index: 3074 */
	.weak lookup_filesystem_type; .long lookup_filesystem_type
	.reloc ., R_386_SIZE32, lookup_filesystem_type; .long 0
	.long 0xc3ce065
	.long .Lname3075 /* index: 3075 */
	.weak block_device_partition_readv_phys; .long block_device_partition_readv_phys
	.reloc ., R_386_SIZE32, block_device_partition_readv_phys; .long 0
	.long 0xdc34c03
	.long .Lname3076 /* index: 3076 */
	.weak x86_idt_start_traced; .long x86_idt_start_traced
	.reloc ., R_386_SIZE32, x86_idt_start_traced; .long 0
	.long 0xbd70c04
	.long 0 /* index: 3077 */
	.long 0
	.long 0
	.long 0
	.long .Lname3078 /* index: 3078 */
	.weak sys_pselect6; .long sys_pselect6
	.reloc ., R_386_SIZE32, sys_pselect6; .long 0
	.long 0xe122c06
	.long 0 /* index: 3079 */
	.long 0
	.long 0
	.long 0
	.long .Lname3080 /* index: 3080 */
	.weak driver_library_path; .long driver_library_path
	.reloc ., R_386_SIZE32, driver_library_path; .long 0
	.long 0x6693c08
	.long .Lname3081 /* index: 3081 */
	.weak vmb_apply; .long vmb_apply
	.reloc ., R_386_SIZE32, vmb_apply; .long 0
	.long 0x8580c09
	.long 0 /* index: 3082 */
	.long 0
	.long 0
	.long 0
	.long .Lname3083 /* index: 3083 */
	.weak vm_kernel_sync; .long vm_kernel_sync
	.reloc ., R_386_SIZE32, vm_kernel_sync; .long 0
	.long 0x98780d3
	.long 0 /* index: 3084 */
	.long 0
	.long 0
	.long 0
	.long .Lname3085 /* index: 3085 */
	.weak block_device_autopart; .long block_device_autopart
	.reloc ., R_386_SIZE32, block_device_autopart; .long 0
	.long 0x60ecee4
	.long 0 /* index: 3086 */
	.long 0
	.long 0
	.long 0
	.long .Lname3087 /* index: 3087 */
	.weak error_as_errno; .long error_as_errno
	.reloc ., R_386_SIZE32, error_as_errno; .long 0
	.long 0x2ca1c0f
	.long 0 /* index: 3088 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3089 */
	.long 0
	.long 0
	.long 0
	.long .Lname3090 /* index: 3090 */
	.weak sys_umount2; .long sys_umount2
	.reloc ., R_386_SIZE32, sys_umount2; .long 0
	.long 0xc5dcc12
	.long .Lname3091 /* index: 3091 */
	.weak ansitty_putc; .long ansitty_putc
	.reloc ., R_386_SIZE32, ansitty_putc; .long 0
	.long 0xd73dc13
	.long .Lname3092 /* index: 3092 */
	.weak vio_writel_aligned; .long vio_writel_aligned
	.reloc ., R_386_SIZE32, vio_writel_aligned; .long 0
	.long 0x8f53c14
	.long .Lname3093 /* index: 3093 */
	.weak cpu_apply_fcpustate; .long cpu_apply_fcpustate
	.reloc ., R_386_SIZE32, cpu_apply_fcpustate; .long 0
	.long 0xa8cac15
	.long 0 /* index: 3094 */
	.long 0
	.long 0
	.long 0
	.long .Lname3095 /* index: 3095 */
	.weak json_parser_eqstring; .long json_parser_eqstring
	.reloc ., R_386_SIZE32, json_parser_eqstring; .long 0
	.long 0xb53ac17
	.long .Lname3096 /* index: 3096 */
	.weak path_sprintex; .long path_sprintex
	.reloc ., R_386_SIZE32, path_sprintex; .long 0
	.long 0x106bc18
	.long .Lname3097 /* index: 3097 */
	.weak vm_kernel_treelock_endread; .long vm_kernel_treelock_endread
	.reloc ., R_386_SIZE32, vm_kernel_treelock_endread; .long 0
	.long 0x9f88204
	.long 0 /* index: 3098 */
	.long 0
	.long 0
	.long 0
	.long .Lname3099 /* index: 3099 */
	.weak dbg_getreg; .long dbg_getreg
	.reloc ., R_386_SIZE32, dbg_getreg; .long 0
	.long 0x5da1067
	.long 0 /* index: 3100 */
	.long 0
	.long 0
	.long 0
	.long .Lname3101 /* index: 3101 */
	.weak sys_ioperm; .long sys_ioperm
	.reloc ., R_386_SIZE32, sys_ioperm; .long 0
	.long 0x601dc1d
	.long 0 /* index: 3102 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3103 */
	.long 0
	.long 0
	.long 0
	.long .Lname3104 /* index: 3104 */
	.weak vm_datablock_anonymous; .long vm_datablock_anonymous
	.reloc ., R_386_SIZE32, vm_datablock_anonymous; .long 0
	.long 0xb72da13
	.long .Lname3105 /* index: 3105 */
	.weak heap_allat_nx; .long heap_allat_nx
	.reloc ., R_386_SIZE32, heap_allat_nx; .long 0
	.long 0xd910178
	.long 0 /* index: 3106 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3107 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3108 */
	.long 0
	.long 0
	.long 0
	.long .Lname3109 /* index: 3109 */
	.weak pagedir_unwriteone; .long pagedir_unwriteone
	.reloc ., R_386_SIZE32, pagedir_unwriteone; .long 0
	.long 0x2bdc25
	.long 0 /* index: 3110 */
	.long 0
	.long 0
	.long 0
	.long .Lname3111 /* index: 3111 */
	.weak memlenw; .long memlenw
	.reloc ., R_386_SIZE32, memlenw; .long 0
	.long 0x3c42c27
	.long 0 /* index: 3112 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3113 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3114 */
	.long 0
	.long 0
	.long 0
	.long .Lname3115 /* index: 3115 */
	.weak error_throw; .long error_throw
	.reloc ., R_386_SIZE32, error_throw; .long 0
	.long 0x8066207
	.long 0 /* index: 3116 */
	.long 0
	.long 0
	.long 0
	.long .Lname3117 /* index: 3117 */
	.weak dbg_pprinter; .long dbg_pprinter
	.reloc ., R_386_SIZE32, dbg_pprinter; .long 0
	.long 0x1288cb2
	.long .Lname3118 /* index: 3118 */
	.weak _strtoi64; .long _strtoi64
	.reloc ., R_386_SIZE32, _strtoi64; .long 0
	.long 0xb9b3a34
	.long 0 /* index: 3119 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3120 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3121 */
	.long 0
	.long 0
	.long 0
	.long .Lname3122 /* index: 3122 */
	.weak pci_readaddr; .long pci_readaddr
	.reloc ., R_386_SIZE32, pci_readaddr; .long 0
	.long 0xc138c32
	.long .Lname3123 /* index: 3123 */
	.weak pagedir_kernel_phys; .long pagedir_kernel_phys
	.reloc ., R_386_SIZE32, pagedir_kernel_phys; .long 0
	.long 0xa3a1c33
	.long .Lname3124 /* index: 3124 */
	.weak strnend; .long strnend
	.reloc ., R_386_SIZE32, strnend; .long 0
	.long 0xab94c34
	.long .Lname3125 /* index: 3125 */
	.weak error_code; .long error_code
	.reloc ., R_386_SIZE32, error_code; .long 0
	.long 0x6836c35
	.long 0 /* index: 3126 */
	.long 0
	.long 0
	.long 0
	.long .Lname3127 /* index: 3127 */
	.weak vm_datapart_lockread_setcore_unsharecow; .long vm_datapart_lockread_setcore_unsharecow
	.reloc ., R_386_SIZE32, vm_datapart_lockread_setcore_unsharecow; .long 0
	.long 0x5b8fc37
	.long 0 /* index: 3128 */
	.long 0
	.long 0
	.long 0
	.long .Lname3129 /* index: 3129 */
	.weak vm_destroy; .long vm_destroy
	.reloc ., R_386_SIZE32, vm_destroy; .long 0
	.long 0xacd6c39
	.long 0 /* index: 3130 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3131 */
	.long 0
	.long 0
	.long 0
	.long .Lname3132 /* index: 3132 */
	.weak memlenl; .long memlenl
	.reloc ., R_386_SIZE32, memlenl; .long 0
	.long 0x3c42c3c
	.long 0 /* index: 3133 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3134 */
	.long 0
	.long 0
	.long 0
	.long .Lname3135 /* index: 3135 */
	.weak sys_fallocate; .long sys_fallocate
	.reloc ., R_386_SIZE32, sys_fallocate; .long 0
	.long 0xa3cc4b5
	.long .Lname3136 /* index: 3136 */
	.weak character_device_mmap; .long character_device_mmap
	.reloc ., R_386_SIZE32, character_device_mmap; .long 0
	.long 0x9894c40
	.long 0 /* index: 3137 */
	.long 0
	.long 0
	.long 0
	.long .Lname3138 /* index: 3138 */
	.weak pty_register; .long pty_register
	.reloc ., R_386_SIZE32, pty_register; .long 0
	.long 0xcbb5c42
	.long 0 /* index: 3139 */
	.long 0
	.long 0
	.long 0
	.long .Lname3140 /* index: 3140 */
	.weak memend; .long memend
	.reloc ., R_386_SIZE32, memend; .long 0
	.long 0x73c3c44
	.long .Lname3141 /* index: 3141 */
	.weak task_push_asynchronous_rpc_v; .long task_push_asynchronous_rpc_v
	.reloc ., R_386_SIZE32, task_push_asynchronous_rpc_v; .long 0
	.long 0x4e99cb6
	.long 0 /* index: 3142 */
	.long 0
	.long 0
	.long 0
	.long .Lname3143 /* index: 3143 */
	.weak vio_subw; .long vio_subw
	.reloc ., R_386_SIZE32, vio_subw; .long 0
	.long 0x56ac47
	.long 0 /* index: 3144 */
	.long 0
	.long 0
	.long 0
	.long .Lname3145 /* index: 3145 */
	.weak __predict_update_dl; .long __predict_update_dl
	.reloc ., R_386_SIZE32, __predict_update_dl; .long 0
	.long 0x45520c
	.long 0 /* index: 3146 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3147 */
	.long 0
	.long 0
	.long 0
	.long .Lname3148 /* index: 3148 */
	.weak unwind_setreg_xfpustate; .long unwind_setreg_xfpustate
	.reloc ., R_386_SIZE32, unwind_setreg_xfpustate; .long 0
	.long 0xb8d04c5
	.long .Lname3149 /* index: 3149 */
	.weak sys_swapoff; .long sys_swapoff
	.reloc ., R_386_SIZE32, sys_swapoff; .long 0
	.long 0xaa37ca6
	.long .Lname3150 /* index: 3150 */
	.weak kernel_vpanic_kcpustate; .long kernel_vpanic_kcpustate
	.reloc ., R_386_SIZE32, kernel_vpanic_kcpustate; .long 0
	.long 0xf5af645
	.long 0 /* index: 3151 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3152 */
	.long 0
	.long 0
	.long 0
	.long .Lname3153 /* index: 3153 */
	.weak path_lock_endwrite; .long path_lock_endwrite
	.reloc ., R_386_SIZE32, path_lock_endwrite; .long 0
	.long 0x28c4b45
	.long .Lname3154 /* index: 3154 */
	.weak vio_subb; .long vio_subb
	.reloc ., R_386_SIZE32, vio_subb; .long 0
	.long 0x56ac52
	.long 0 /* index: 3155 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3156 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3157 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3158 */
	.long 0
	.long 0
	.long 0
	.long .Lname3159 /* index: 3159 */
	.weak inode_readk_blocking; .long inode_readk_blocking
	.reloc ., R_386_SIZE32, inode_readk_blocking; .long 0
	.long 0xd79dc57
	.long .Lname3160 /* index: 3160 */
	.weak path_movemount; .long path_movemount
	.reloc ., R_386_SIZE32, path_movemount; .long 0
	.long 0x42e0f54
	.long .Lname3161 /* index: 3161 */
	.weak task_trywait; .long task_trywait
	.reloc ., R_386_SIZE32, task_trywait; .long 0
	.long 0xc487764
	.long 0 /* index: 3162 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3163 */
	.long 0
	.long 0
	.long 0
	.long .Lname3164 /* index: 3164 */
	.weak vio_subl; .long vio_subl
	.reloc ., R_386_SIZE32, vio_subl; .long 0
	.long 0x56ac5c
	.long 0 /* index: 3165 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3166 */
	.long 0
	.long 0
	.long 0
	.long .Lname3167 /* index: 3167 */
	.weak page_ffree; .long page_ffree
	.reloc ., R_386_SIZE32, page_ffree; .long 0
	.long 0xb5bbf65
	.long .Lname3168 /* index: 3168 */
	.weak __cxa_begin_catch; .long __cxa_begin_catch
	.reloc ., R_386_SIZE32, __cxa_begin_catch; .long 0
	.long 0x5646db8
	.long 0 /* index: 3169 */
	.long 0
	.long 0
	.long 0
	.long .Lname3170 /* index: 3170 */
	.weak sys_setregid32; .long sys_setregid32
	.reloc ., R_386_SIZE32, sys_setregid32; .long 0
	.long 0x82b6c62
	.long .Lname3171 /* index: 3171 */
	.weak kernel_vpanic_ucpustate; .long kernel_vpanic_ucpustate
	.reloc ., R_386_SIZE32, kernel_vpanic_ucpustate; .long 0
	.long 0xf5adc45
	.long .Lname3172 /* index: 3172 */
	.weak task_connect_ghost; .long task_connect_ghost
	.reloc ., R_386_SIZE32, task_connect_ghost; .long 0
	.long 0xa501c64
	.long .Lname3173 /* index: 3173 */
	.weak sys_fsmode; .long sys_fsmode
	.reloc ., R_386_SIZE32, sys_fsmode; .long 0
	.long 0x5df9535
	.long .Lname3174 /* index: 3174 */
	.weak sys_set_library_listdef; .long sys_set_library_listdef
	.reloc ., R_386_SIZE32, sys_set_library_listdef; .long 0
	.long 0x3315c66
	.long 0 /* index: 3175 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3176 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3177 */
	.long 0
	.long 0
	.long 0
	.long .Lname3178 /* index: 3178 */
	.weak sys_poll; .long sys_poll
	.reloc ., R_386_SIZE32, sys_poll; .long 0
	.long 0x96739c
	.long 0 /* index: 3179 */
	.long 0
	.long 0
	.long 0
	.long .Lname3180 /* index: 3180 */
	.weak sys_profil; .long sys_profil
	.reloc ., R_386_SIZE32, sys_profil; .long 0
	.long 0x680ec6c
	.long .Lname3181 /* index: 3181 */
	.weak dbg_setcur; .long dbg_setcur
	.reloc ., R_386_SIZE32, dbg_setcur; .long 0
	.long 0x69a0212
	.long 0 /* index: 3182 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3183 */
	.long 0
	.long 0
	.long 0
	.long .Lname3184 /* index: 3184 */
	.weak sys_exit_group; .long sys_exit_group
	.reloc ., R_386_SIZE32, sys_exit_group; .long 0
	.long 0xacb5c70
	.long 0 /* index: 3185 */
	.long 0
	.long 0
	.long 0
	.long .Lname3186 /* index: 3186 */
	.weak sys_setfsgid32; .long sys_setfsgid32
	.reloc ., R_386_SIZE32, sys_setfsgid32; .long 0
	.long 0xd0b6c72
	.long .Lname3187 /* index: 3187 */
	.weak driver_unloaded_callbacks; .long driver_unloaded_callbacks
	.reloc ., R_386_SIZE32, driver_unloaded_callbacks; .long 0
	.long 0x6a5da13
	.long 0 /* index: 3188 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3189 */
	.long 0
	.long 0
	.long 0
	.long .Lname3190 /* index: 3190 */
	.weak slab_kmalloc4; .long slab_kmalloc4
	.reloc ., R_386_SIZE32, slab_kmalloc4; .long 0
	.long 0x966b314
	.long 0 /* index: 3191 */
	.long 0
	.long 0
	.long 0
	.long .Lname3192 /* index: 3192 */
	.weak vm_datapart_lockwrite_setcore_nx; .long vm_datapart_lockwrite_setcore_nx
	.reloc ., R_386_SIZE32, vm_datapart_lockwrite_setcore_nx; .long 0
	.long 0x3700c78
	.long .Lname3193 /* index: 3193 */
	.weak sys_kfstat; .long sys_kfstat
	.reloc ., R_386_SIZE32, sys_kfstat; .long 0
	.long 0x61a1a14
	.long 0 /* index: 3194 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3195 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3196 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3197 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3198 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3199 */
	.long 0
	.long 0
	.long 0
	.long .Lname3200 /* index: 3200 */
	.weak pagedir_prepare_map_keep; .long pagedir_prepare_map_keep
	.reloc ., R_386_SIZE32, pagedir_prepare_map_keep; .long 0
	.long 0xa0d0c80
	.long .Lname3201 /* index: 3201 */
	.weak debuginfo_cu_parser_nextparent; .long debuginfo_cu_parser_nextparent
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_nextparent; .long 0
	.long 0x564a144
	.long .Lname3202 /* index: 3202 */
	.weak block_device_areadv_sector; .long block_device_areadv_sector
	.reloc ., R_386_SIZE32, block_device_areadv_sector; .long 0
	.long 0x1855c82
	.long 0 /* index: 3203 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3204 */
	.long 0
	.long 0
	.long 0
	.long .Lname3205 /* index: 3205 */
	.weak regdump_cr0; .long regdump_cr0
	.reloc ., R_386_SIZE32, regdump_cr0; .long 0
	.long 0xc3ee7e0
	.long 0 /* index: 3206 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3207 */
	.long 0
	.long 0
	.long 0
	.long .Lname3208 /* index: 3208 */
	.weak block_device_lookup_nx; .long block_device_lookup_nx
	.reloc ., R_386_SIZE32, block_device_lookup_nx; .long 0
	.long 0x1a63c88
	.long .Lname3209 /* index: 3209 */
	.weak vm_datapart_lock_upgrade; .long vm_datapart_lock_upgrade
	.reloc ., R_386_SIZE32, vm_datapart_lock_upgrade; .long 0
	.long 0x5eed3e5
	.long 0 /* index: 3210 */
	.long 0
	.long 0
	.long 0
	.long .Lname3211 /* index: 3211 */
	.weak task_schedule_synchronous_srpc_nx; .long task_schedule_synchronous_srpc_nx
	.reloc ., R_386_SIZE32, task_schedule_synchronous_srpc_nx; .long 0
	.long 0x5aa2ca8
	.long .Lname3212 /* index: 3212 */
	.weak mouse_device_ioctl; .long mouse_device_ioctl
	.reloc ., R_386_SIZE32, mouse_device_ioctl; .long 0
	.long 0x9b65c8c
	.long 0 /* index: 3213 */
	.long 0
	.long 0
	.long 0
	.long .Lname3214 /* index: 3214 */
	.weak x86_this_user_gsbase; .long x86_this_user_gsbase
	.reloc ., R_386_SIZE32, x86_this_user_gsbase; .long 0
	.long 0x143be45
	.long 0 /* index: 3215 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3216 */
	.long 0
	.long 0
	.long 0
	.long .Lname3217 /* index: 3217 */
	.weak __predict_update_dx; .long __predict_update_dx
	.reloc ., R_386_SIZE32, __predict_update_dx; .long 0
	.long 0x455218
	.long .Lname3218 /* index: 3218 */
	.weak mouse_device_moveto_nopr; .long mouse_device_moveto_nopr
	.reloc ., R_386_SIZE32, mouse_device_moveto_nopr; .long 0
	.long 0x4a03c92
	.long .Lname3219 /* index: 3219 */
	.weak task_free_rpc; .long task_free_rpc
	.reloc ., R_386_SIZE32, task_free_rpc; .long 0
	.long 0x2317cc3
	.long .Lname3220 /* index: 3220 */
	.weak x86_exsyscall_is_cancellation_point; .long x86_exsyscall_is_cancellation_point
	.reloc ., R_386_SIZE32, x86_exsyscall_is_cancellation_point; .long 0
	.long 0x6b4c94
	.long 0 /* index: 3221 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3222 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3223 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3224 */
	.long 0
	.long 0
	.long 0
	.long .Lname3225 /* index: 3225 */
	.weak sys_read; .long sys_read
	.reloc ., R_386_SIZE32, sys_read; .long 0
	.long 0x968cc4
	.long 0 /* index: 3226 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3227 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3228 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3229 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3230 */
	.long 0
	.long 0
	.long 0
	.long .Lname3231 /* index: 3231 */
	.weak rwlock_endwrite; .long rwlock_endwrite
	.reloc ., R_386_SIZE32, rwlock_endwrite; .long 0
	.long 0x7e41cc5
	.long .Lname3232 /* index: 3232 */
	.weak validate_readablem_opt; .long validate_readablem_opt
	.reloc ., R_386_SIZE32, validate_readablem_opt; .long 0
	.long 0x5bba2a4
	.long .Lname3233 /* index: 3233 */
	.weak vio_cmpxchq; .long vio_cmpxchq
	.reloc ., R_386_SIZE32, vio_cmpxchq; .long 0
	.long 0xa3aeca1
	.long 0 /* index: 3234 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3235 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3236 */
	.long 0
	.long 0
	.long 0
	.long .Lname3237 /* index: 3237 */
	.weak vm_kernel_treelock_tryservice; .long vm_kernel_treelock_tryservice
	.reloc ., R_386_SIZE32, vm_kernel_treelock_tryservice; .long 0
	.long 0x95d4ca5
	.long .Lname3238 /* index: 3238 */
	.weak format_printf; .long format_printf
	.reloc ., R_386_SIZE32, format_printf; .long 0
	.long 0xb11dca6
	.long .Lname3239 /* index: 3239 */
	.weak vio_cmpxchw; .long vio_cmpxchw
	.reloc ., R_386_SIZE32, vio_cmpxchw; .long 0
	.long 0xa3aeca7
	.long .Lname3240 /* index: 3240 */
	.weak devfs_lock_read_nx; .long devfs_lock_read_nx
	.reloc ., R_386_SIZE32, devfs_lock_read_nx; .long 0
	.long 0xc2f0ca8
	.long .Lname3241 /* index: 3241 */
	.weak taskpid_destroy; .long taskpid_destroy
	.reloc ., R_386_SIZE32, taskpid_destroy; .long 0
	.long 0xec3db9
	.long .Lname3242 /* index: 3242 */
	.weak mempsetl; .long mempsetl
	.reloc ., R_386_SIZE32, mempsetl; .long 0
	.long 0xc479b9c
	.long .Lname3243 /* index: 3243 */
	.weak mall_print_traceback; .long mall_print_traceback
	.reloc ., R_386_SIZE32, mall_print_traceback; .long 0
	.long 0xff78cab
	.long 0 /* index: 3244 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3245 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3246 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3247 */
	.long 0
	.long 0
	.long 0
	.long .Lname3248 /* index: 3248 */
	.weak pidns_alloc; .long pidns_alloc
	.reloc ., R_386_SIZE32, pidns_alloc; .long 0
	.long 0x922ea03
	.long 0 /* index: 3249 */
	.long 0
	.long 0
	.long 0
	.long .Lname3250 /* index: 3250 */
	.weak vio_cmpxchb; .long vio_cmpxchb
	.reloc ., R_386_SIZE32, vio_cmpxchb; .long 0
	.long 0xa3aecb2
	.long .Lname3251 /* index: 3251 */
	.weak kernel_heaps; .long kernel_heaps
	.reloc ., R_386_SIZE32, kernel_heaps; .long 0
	.long 0x7422cb3
	.long 0 /* index: 3252 */
	.long 0
	.long 0
	.long 0
	.long .Lname3253 /* index: 3253 */
	.weak vm_datapart_lockread_setcore; .long vm_datapart_lockread_setcore
	.reloc ., R_386_SIZE32, vm_datapart_lockread_setcore; .long 0
	.long 0x8687cb5
	.long .Lname3254 /* index: 3254 */
	.weak sys_readv; .long sys_readv
	.reloc ., R_386_SIZE32, sys_readv; .long 0
	.long 0x968ccb6
	.long .Lname3255 /* index: 3255 */
	.weak json_parser_getstring; .long json_parser_getstring
	.reloc ., R_386_SIZE32, json_parser_getstring; .long 0
	.long 0x429ccb7
	.long .Lname3256 /* index: 3256 */
	.weak vm_datapart_lock_upgrade_nx; .long vm_datapart_lock_upgrade_nx
	.reloc ., R_386_SIZE32, vm_datapart_lock_upgrade_nx; .long 0
	.long 0xd3f0cb8
	.long .Lname3257 /* index: 3257 */
	.weak vm_datablock_vio_read; .long vm_datablock_vio_read
	.reloc ., R_386_SIZE32, vm_datablock_vio_read; .long 0
	.long 0x8c46774
	.long 0 /* index: 3258 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3259 */
	.long 0
	.long 0
	.long 0
	.long .Lname3260 /* index: 3260 */
	.weak vio_cmpxchl; .long vio_cmpxchl
	.reloc ., R_386_SIZE32, vio_cmpxchl; .long 0
	.long 0xa3aecbc
	.long .Lname3261 /* index: 3261 */
	.weak _bootcpu; .long _bootcpu
	.reloc ., R_386_SIZE32, _bootcpu; .long 0
	.long 0x966ac25
	.long .Lname3262 /* index: 3262 */
	.weak unwind_fde_rule; .long unwind_fde_rule
	.reloc ., R_386_SIZE32, unwind_fde_rule; .long 0
	.long 0x4b263b5
	.long 0 /* index: 3263 */
	.long 0
	.long 0
	.long 0
	.long .Lname3264 /* index: 3264 */
	.weak format_hexdump; .long format_hexdump
	.reloc ., R_386_SIZE32, format_hexdump; .long 0
	.long 0x85d2cc0
	.long .Lname3265 /* index: 3265 */
	.weak memsetq; .long memsetq
	.reloc ., R_386_SIZE32, memsetq; .long 0
	.long 0x3c49cc1
	.long 0 /* index: 3266 */
	.long 0
	.long 0
	.long 0
	.long .Lname3267 /* index: 3267 */
	.weak kernel_panic_lcpustate; .long kernel_panic_lcpustate
	.reloc ., R_386_SIZE32, kernel_panic_lcpustate; .long 0
	.long 0x78a90f5
	.long .Lname3268 /* index: 3268 */
	.weak sys_umount; .long sys_umount
	.reloc ., R_386_SIZE32, sys_umount; .long 0
	.long 0x6c5dcc4
	.long .Lname3269 /* index: 3269 */
	.weak sys_nanosleep; .long sys_nanosleep
	.reloc ., R_386_SIZE32, sys_nanosleep; .long 0
	.long 0x614fe0
	.long .Lname3270 /* index: 3270 */
	.weak block_device_partition_writev; .long block_device_partition_writev
	.reloc ., R_386_SIZE32, block_device_partition_writev; .long 0
	.long 0x5487cc6
	.long .Lname3271 /* index: 3271 */
	.weak memsetw; .long memsetw
	.reloc ., R_386_SIZE32, memsetw; .long 0
	.long 0x3c49cc7
	.long .Lname3272 /* index: 3272 */
	.weak fpustate_init_nx; .long fpustate_init_nx
	.reloc ., R_386_SIZE32, fpustate_init_nx; .long 0
	.long 0x6fefcc8
	.long 0 /* index: 3273 */
	.long 0
	.long 0
	.long 0
	.long .Lname3274 /* index: 3274 */
	.weak snprintf; .long snprintf
	.reloc ., R_386_SIZE32, snprintf; .long 0
	.long 0x5790206
	.long 0 /* index: 3275 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3276 */
	.long 0
	.long 0
	.long 0
	.long .Lname3277 /* index: 3277 */
	.weak inodes_recent_lim; .long inodes_recent_lim
	.reloc ., R_386_SIZE32, inodes_recent_lim; .long 0
	.long 0x7609ccd
	.long 0 /* index: 3278 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3279 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3280 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3281 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3282 */
	.long 0
	.long 0
	.long 0
	.long .Lname3283 /* index: 3283 */
	.weak devfs; .long devfs
	.reloc ., R_386_SIZE32, devfs; .long 0
	.long 0x6accd3
	.long .Lname3284 /* index: 3284 */
	.weak debugline_loadunit; .long debugline_loadunit
	.reloc ., R_386_SIZE32, debugline_loadunit; .long 0
	.long 0x1150cd4
	.long .Lname3285 /* index: 3285 */
	.weak _this_cpu; .long _this_cpu
	.reloc ., R_386_SIZE32, _this_cpu; .long 0
	.long 0xf093cd5
	.long 0 /* index: 3286 */
	.long 0
	.long 0
	.long 0
	.long .Lname3287 /* index: 3287 */
	.weak isr_register_greedy; .long isr_register_greedy
	.reloc ., R_386_SIZE32, isr_register_greedy; .long 0
	.long 0xb4a7f79
	.long .Lname3288 /* index: 3288 */
	.weak task_waitfor_nx; .long task_waitfor_nx
	.reloc ., R_386_SIZE32, task_waitfor_nx; .long 0
	.long 0xe0ecd8
	.long .Lname3289 /* index: 3289 */
	.weak cpu_count; .long cpu_count
	.reloc ., R_386_SIZE32, cpu_count; .long 0
	.long 0xb5a0224
	.long 0 /* index: 3290 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3291 */
	.long 0
	.long 0
	.long 0
	.long .Lname3292 /* index: 3292 */
	.weak memsetl; .long memsetl
	.reloc ., R_386_SIZE32, memsetl; .long 0
	.long 0x3c49cdc
	.long .Lname3293 /* index: 3293 */
	.weak vm_do_ccfreeram; .long vm_do_ccfreeram
	.reloc ., R_386_SIZE32, vm_do_ccfreeram; .long 0
	.long 0x83eecdd
	.long 0 /* index: 3294 */
	.long 0
	.long 0
	.long 0
	.long .Lname3295 /* index: 3295 */
	.weak fpustate_save; .long fpustate_save
	.reloc ., R_386_SIZE32, fpustate_save; .long 0
	.long 0x7ea3225
	.long 0 /* index: 3296 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3297 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3298 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3299 */
	.long 0
	.long 0
	.long 0
	.long .Lname3300 /* index: 3300 */
	.weak unwind_fde_load; .long unwind_fde_load
	.reloc ., R_386_SIZE32, unwind_fde_load; .long 0
	.long 0x4b2ece4
	.long .Lname3301 /* index: 3301 */
	.weak sys_writef; .long sys_writef
	.reloc ., R_386_SIZE32, sys_writef; .long 0
	.long 0x6f0ba26
	.long 0 /* index: 3302 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3303 */
	.long 0
	.long 0
	.long 0
	.long .Lname3304 /* index: 3304 */
	.weak heap_realloc_untraced_nx; .long heap_realloc_untraced_nx
	.reloc ., R_386_SIZE32, heap_realloc_untraced_nx; .long 0
	.long 0xac8ce8
	.long 0 /* index: 3305 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3306 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3307 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3308 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3309 */
	.long 0
	.long 0
	.long 0
	.long .Lname3310 /* index: 3310 */
	.weak coredump_create_for_exception; .long coredump_create_for_exception
	.reloc ., R_386_SIZE32, coredump_create_for_exception; .long 0
	.long 0x9f51cee
	.long 0 /* index: 3311 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3312 */
	.long 0
	.long 0
	.long 0
	.long .Lname3313 /* index: 3313 */
	.weak __predict_update_ax; .long __predict_update_ax
	.reloc ., R_386_SIZE32, __predict_update_ax; .long 0
	.long 0x455228
	.long 0 /* index: 3314 */
	.long 0
	.long 0
	.long 0
	.long .Lname3315 /* index: 3315 */
	.weak block_device_writev_phys_sync; .long block_device_writev_phys_sync
	.reloc ., R_386_SIZE32, block_device_writev_phys_sync; .long 0
	.long 0x2f9dcf3
	.long .Lname3316 /* index: 3316 */
	.weak page_stat; .long page_stat
	.reloc ., R_386_SIZE32, page_stat; .long 0
	.long 0xdb6dcf4
	.long .Lname3317 /* index: 3317 */
	.weak sys_timerfd_gettime; .long sys_timerfd_gettime
	.reloc ., R_386_SIZE32, sys_timerfd_gettime; .long 0
	.long 0x50a0cf5
	.long 0 /* index: 3318 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3319 */
	.long 0
	.long 0
	.long 0
	.long .Lname3320 /* index: 3320 */
	.weak task_alloc_synchronous_srpc_nx; .long task_alloc_synchronous_srpc_nx
	.reloc ., R_386_SIZE32, task_alloc_synchronous_srpc_nx; .long 0
	.long 0x5df3cf8
	.long .Lname3321 /* index: 3321 */
	.weak sys_fsymlinkat; .long sys_fsymlinkat
	.reloc ., R_386_SIZE32, sys_fsymlinkat; .long 0
	.long 0x4bbacd4
	.long 0 /* index: 3322 */
	.long 0
	.long 0
	.long 0
	.long .Lname3323 /* index: 3323 */
	.weak sys_munlock; .long sys_munlock
	.reloc ., R_386_SIZE32, sys_munlock; .long 0
	.long 0x4e03cfb
	.long 0 /* index: 3324 */
	.long 0
	.long 0
	.long 0
	.long .Lname3325 /* index: 3325 */
	.weak ansitty_device_cinit; .long ansitty_device_cinit
	.reloc ., R_386_SIZE32, ansitty_device_cinit; .long 0
	.long 0xb5597e4
	.long 0 /* index: 3326 */
	.long 0
	.long 0
	.long 0
	.long .Lname3327 /* index: 3327 */
	.weak rwlock_canwrite; .long rwlock_canwrite
	.reloc ., R_386_SIZE32, rwlock_canwrite; .long 0
	.long 0x5041cd5
	.long 0 /* index: 3328 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3329 */
	.long 0
	.long 0
	.long 0
	.long .Lname3330 /* index: 3330 */
	.weak sys_flistxattr; .long sys_flistxattr
	.reloc ., R_386_SIZE32, sys_flistxattr; .long 0
	.long 0xa2b5d02
	.long .Lname3331 /* index: 3331 */
	.weak cpu_features; .long cpu_features
	.reloc ., R_386_SIZE32, cpu_features; .long 0
	.long 0xd2c7d03
	.long .Lname3332 /* index: 3332 */
	.weak vpage_ffree_untraced; .long vpage_ffree_untraced
	.reloc ., R_386_SIZE32, vpage_ffree_untraced; .long 0
	.long 0xe4e5d04
	.long 0 /* index: 3333 */
	.long 0
	.long 0
	.long 0
	.long .Lname3334 /* index: 3334 */
	.weak inode_areadv; .long inode_areadv
	.reloc ., R_386_SIZE32, inode_areadv; .long 0
	.long 0x28ded06
	.long 0 /* index: 3335 */
	.long 0
	.long 0
	.long 0
	.long .Lname3336 /* index: 3336 */
	.weak pidns_upgrade_nx; .long pidns_upgrade_nx
	.reloc ., R_386_SIZE32, pidns_upgrade_nx; .long 0
	.long 0xdeb1d08
	.long .Lname3337 /* index: 3337 */
	.weak quantum_local_to_global; .long quantum_local_to_global
	.reloc ., R_386_SIZE32, quantum_local_to_global; .long 0
	.long 0x77aca2c
	.long 0 /* index: 3338 */
	.long 0
	.long 0
	.long 0
	.long .Lname3339 /* index: 3339 */
	.weak _boottask; .long _boottask
	.reloc ., R_386_SIZE32, _boottask; .long 0
	.long 0x66bcd0b
	.long 0 /* index: 3340 */
	.long 0
	.long 0
	.long 0
	.long .Lname3341 /* index: 3341 */
	.weak sys_getgroups32; .long sys_getgroups32
	.reloc ., R_386_SIZE32, sys_getgroups32; .long 0
	.long 0x231c782
	.long 0 /* index: 3342 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3343 */
	.long 0
	.long 0
	.long 0
	.long .Lname3344 /* index: 3344 */
	.weak pagedir_unmap_userspace_nosync_p; .long pagedir_unmap_userspace_nosync_p
	.reloc ., R_386_SIZE32, pagedir_unmap_userspace_nosync_p; .long 0
	.long 0x7a0bd10
	.long .Lname3345 /* index: 3345 */
	.weak vm_datapart_allocswap_nx; .long vm_datapart_allocswap_nx
	.reloc ., R_386_SIZE32, vm_datapart_allocswap_nx; .long 0
	.long 0x2e164d8
	.long .Lname3346 /* index: 3346 */
	.weak dbg_attr; .long dbg_attr
	.reloc ., R_386_SIZE32, dbg_attr; .long 0
	.long 0x8d58d12
	.long .Lname3347 /* index: 3347 */
	.weak vfs_alloc; .long vfs_alloc
	.reloc ., R_386_SIZE32, vfs_alloc; .long 0
	.long 0x9586f83
	.long .Lname3348 /* index: 3348 */
	.weak tty_device_stopfwd; .long tty_device_stopfwd
	.reloc ., R_386_SIZE32, tty_device_stopfwd; .long 0
	.long 0x1e21d14
	.long .Lname3349 /* index: 3349 */
	.weak debuginfo_print_typename; .long debuginfo_print_typename
	.reloc ., R_386_SIZE32, debuginfo_print_typename; .long 0
	.long 0x247cd15
	.long 0 /* index: 3350 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3351 */
	.long 0
	.long 0
	.long 0
	.long .Lname3352 /* index: 3352 */
	.weak vm_kernel_treelock_read_nx; .long vm_kernel_treelock_read_nx
	.reloc ., R_386_SIZE32, vm_kernel_treelock_read_nx; .long 0
	.long 0xb04ad18
	.long 0 /* index: 3353 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3354 */
	.long 0
	.long 0
	.long 0
	.long .Lname3355 /* index: 3355 */
	.weak inode_areadk; .long inode_areadk
	.reloc ., R_386_SIZE32, inode_areadk; .long 0
	.long 0x28ded1b
	.long 0 /* index: 3356 */
	.long 0
	.long 0
	.long 0
	.long .Lname3357 /* index: 3357 */
	.weak unicode_16to8; .long unicode_16to8
	.reloc ., R_386_SIZE32, unicode_16to8; .long 0
	.long 0x76b80f8
	.long .Lname3358 /* index: 3358 */
	.weak pagedir_haschanged; .long pagedir_haschanged
	.reloc ., R_386_SIZE32, pagedir_haschanged; .long 0
	.long 0xec67e94
	.long .Lname3359 /* index: 3359 */
	.weak block_device_delparts; .long block_device_delparts
	.reloc ., R_386_SIZE32, block_device_delparts; .long 0
	.long 0x36e2fe3
	.long 0 /* index: 3360 */
	.long 0
	.long 0
	.long 0
	.long .Lname3361 /* index: 3361 */
	.weak block_device_alloc; .long block_device_alloc
	.reloc ., R_386_SIZE32, block_device_alloc; .long 0
	.long 0xa69c8d3
	.long .Lname3362 /* index: 3362 */
	.weak sys_setxattr; .long sys_setxattr
	.reloc ., R_386_SIZE32, sys_setxattr; .long 0
	.long 0xb0e1d22
	.long .Lname3363 /* index: 3363 */
	.weak fpustate_alloc; .long fpustate_alloc
	.reloc ., R_386_SIZE32, fpustate_alloc; .long 0
	.long 0xe9e9d23
	.long .Lname3364 /* index: 3364 */
	.weak dbg_draweditfield; .long dbg_draweditfield
	.reloc ., R_386_SIZE32, dbg_draweditfield; .long 0
	.long 0xb4ead24
	.long .Lname3365 /* index: 3365 */
	.weak swap_write; .long swap_write
	.reloc ., R_386_SIZE32, swap_write; .long 0
	.long 0x6693d25
	.long 0 /* index: 3366 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3367 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3368 */
	.long 0
	.long 0
	.long 0
	.long .Lname3369 /* index: 3369 */
	.weak keyboard_device_fini; .long keyboard_device_fini
	.reloc ., R_386_SIZE32, keyboard_device_fini; .long 0
	.long 0xf165d29
	.long .Lname3370 /* index: 3370 */
	.weak unwind_getreg_ucpustate; .long unwind_getreg_ucpustate
	.reloc ., R_386_SIZE32, unwind_getreg_ucpustate; .long 0
	.long 0xb8c41b5
	.long 0 /* index: 3371 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3372 */
	.long 0
	.long 0
	.long 0
	.long .Lname3373 /* index: 3373 */
	.weak x86_debug_gdt; .long x86_debug_gdt
	.reloc ., R_386_SIZE32, x86_debug_gdt; .long 0
	.long 0x2010774
	.long 0 /* index: 3374 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3375 */
	.long 0
	.long 0
	.long 0
	.long .Lname3376 /* index: 3376 */
	.weak krealign_in_place_offset; .long krealign_in_place_offset
	.reloc ., R_386_SIZE32, krealign_in_place_offset; .long 0
	.long 0xb224854
	.long 0 /* index: 3377 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3378 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3379 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3380 */
	.long 0
	.long 0
	.long 0
	.long .Lname3381 /* index: 3381 */
	.weak validate_writable; .long validate_writable
	.reloc ., R_386_SIZE32, validate_writable; .long 0
	.long 0x3fc4d35
	.long 0 /* index: 3382 */
	.long 0
	.long 0
	.long 0
	.long .Lname3383 /* index: 3383 */
	.weak dbg_applyreg; .long dbg_applyreg
	.reloc ., R_386_SIZE32, dbg_applyreg; .long 0
	.long 0x1dcdd37
	.long .Lname3384 /* index: 3384 */
	.weak slab_kmalloc_nx; .long slab_kmalloc_nx
	.reloc ., R_386_SIZE32, slab_kmalloc_nx; .long 0
	.long 0x6b40d38
	.long .Lname3385 /* index: 3385 */
	.weak vmb_isused; .long vmb_isused
	.reloc ., R_386_SIZE32, vmb_isused; .long 0
	.long 0x60d1a34
	.long 0 /* index: 3386 */
	.long 0
	.long 0
	.long 0
	.long .Lname3387 /* index: 3387 */
	.weak json_parser_leavearray; .long json_parser_leavearray
	.reloc ., R_386_SIZE32, json_parser_leavearray; .long 0
	.long 0x49d20f9
	.long .Lname3388 /* index: 3388 */
	.weak inode_readall; .long inode_readall
	.reloc ., R_386_SIZE32, inode_readall; .long 0
	.long 0x8e20d3c
	.long 0 /* index: 3389 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3390 */
	.long 0
	.long 0
	.long 0
	.long .Lname3391 /* index: 3391 */
	.weak pidns_downgrade; .long pidns_downgrade
	.reloc ., R_386_SIZE32, pidns_downgrade; .long 0
	.long 0x717aa35
	.long .Lname3392 /* index: 3392 */
	.weak dbg_getc; .long dbg_getc
	.reloc ., R_386_SIZE32, dbg_getc; .long 0
	.long 0x8d5da03
	.long .Lname3393 /* index: 3393 */
	.weak mall_trace; .long mall_trace
	.reloc ., R_386_SIZE32, mall_trace; .long 0
	.long 0x26cbfa5
	.long 0 /* index: 3394 */
	.long 0
	.long 0
	.long 0
	.long .Lname3395 /* index: 3395 */
	.weak sys_set_tid_address; .long sys_set_tid_address
	.reloc ., R_386_SIZE32, sys_set_tid_address; .long 0
	.long 0x4c81d43
	.long .Lname3396 /* index: 3396 */
	.weak terminal_poll_iread; .long terminal_poll_iread
	.reloc ., R_386_SIZE32, terminal_poll_iread; .long 0
	.long 0xcfbd44
	.long 0 /* index: 3397 */
	.long 0
	.long 0
	.long 0
	.long .Lname3398 /* index: 3398 */
	.weak __acheckf; .long __acheckf
	.reloc ., R_386_SIZE32, __acheckf; .long 0
	.long 0x79edd46
	.long 0 /* index: 3399 */
	.long 0
	.long 0
	.long 0
	.long .Lname3400 /* index: 3400 */
	.weak task_raisesignalprocess_nx; .long task_raisesignalprocess_nx
	.reloc ., R_386_SIZE32, task_raisesignalprocess_nx; .long 0
	.long 0x5941d48
	.long 0 /* index: 3401 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3402 */
	.long 0
	.long 0
	.long 0
	.long .Lname3403 /* index: 3403 */
	.weak task_tryyield; .long task_tryyield
	.reloc ., R_386_SIZE32, task_tryyield; .long 0
	.long 0x485eee4
	.long 0 /* index: 3404 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3405 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3406 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3407 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3408 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3409 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3410 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3411 */
	.long 0
	.long 0
	.long 0
	.long .Lname3412 /* index: 3412 */
	.weak sys_fmkdirat; .long sys_fmkdirat
	.reloc ., R_386_SIZE32, sys_fmkdirat; .long 0
	.long 0x5ab9d54
	.long .Lname3413 /* index: 3413 */
	.weak pagedir_prepare_mapone; .long pagedir_prepare_mapone
	.reloc ., R_386_SIZE32, pagedir_prepare_mapone; .long 0
	.long 0x749dd55
	.long 0 /* index: 3414 */
	.long 0
	.long 0
	.long 0
	.long .Lname3415 /* index: 3415 */
	.weak dbg_trygetkey; .long dbg_trygetkey
	.reloc ., R_386_SIZE32, dbg_trygetkey; .long 0
	.long 0x551da39
	.long 0 /* index: 3416 */
	.long 0
	.long 0
	.long 0
	.long .Lname3417 /* index: 3417 */
	.weak json_parser_leaveobject; .long json_parser_leaveobject
	.reloc ., R_386_SIZE32, json_parser_leaveobject; .long 0
	.long 0xa048ce4
	.long 0 /* index: 3418 */
	.long 0
	.long 0
	.long 0
	.long .Lname3419 /* index: 3419 */
	.weak path_traversen_at; .long path_traversen_at
	.reloc ., R_386_SIZE32, path_traversen_at; .long 0
	.long 0xf5643a4
	.long .Lname3420 /* index: 3420 */
	.weak sys_fchown; .long sys_fchown
	.reloc ., R_386_SIZE32, sys_fchown; .long 0
	.long 0x5ce664e
	.long .Lname3421 /* index: 3421 */
	.weak vm_do_freeram; .long vm_do_freeram
	.reloc ., R_386_SIZE32, vm_do_freeram; .long 0
	.long 0xbe7d5d
	.long 0 /* index: 3422 */
	.long 0
	.long 0
	.long 0
	.long .Lname3423 /* index: 3423 */
	.weak error_info; .long error_info
	.reloc ., R_386_SIZE32, error_info; .long 0
	.long 0x6834d5f
	.long 0 /* index: 3424 */
	.long 0
	.long 0
	.long 0
	.long .Lname3425 /* index: 3425 */
	.weak memrlenq; .long memrlenq
	.reloc ., R_386_SIZE32, memrlenq; .long 0
	.long 0xc492d61
	.long .Lname3426 /* index: 3426 */
	.weak kernel_debugtrap_ucpustate; .long kernel_debugtrap_ucpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_ucpustate; .long 0
	.long 0x963baf5
	.long 0 /* index: 3427 */
	.long 0
	.long 0
	.long 0
	.long .Lname3428 /* index: 3428 */
	.weak sys_setfsuid; .long sys_setfsuid
	.reloc ., R_386_SIZE32, sys_setfsuid; .long 0
	.long 0xb1d3d64
	.long .Lname3429 /* index: 3429 */
	.weak vm_datapart_free; .long vm_datapart_free
	.reloc ., R_386_SIZE32, vm_datapart_free; .long 0
	.long 0x3288d65
	.long .Lname3430 /* index: 3430 */
	.weak dbg_addr2line_printf; .long dbg_addr2line_printf
	.reloc ., R_386_SIZE32, dbg_addr2line_printf; .long 0
	.long 0xb1f7d66
	.long .Lname3431 /* index: 3431 */
	.weak memrlenw; .long memrlenw
	.reloc ., R_386_SIZE32, memrlenw; .long 0
	.long 0xc492d67
	.long .Lname3432 /* index: 3432 */
	.weak vm_tasklock_write_nx; .long vm_tasklock_write_nx
	.reloc ., R_386_SIZE32, vm_tasklock_write_nx; .long 0
	.long 0xb3e4d68
	.long 0 /* index: 3433 */
	.long 0
	.long 0
	.long 0
	.long .Lname3434 /* index: 3434 */
	.weak character_device_write; .long character_device_write
	.reloc ., R_386_SIZE32, character_device_write; .long 0
	.long 0x8be8c35
	.long .Lname3435 /* index: 3435 */
	.weak pidns_trylookup_task; .long pidns_trylookup_task
	.reloc ., R_386_SIZE32, pidns_trylookup_task; .long 0
	.long 0xa1e7d6b
	.long 0 /* index: 3436 */
	.long 0
	.long 0
	.long 0
	.long .Lname3437 /* index: 3437 */
	.weak vm_mapres; .long vm_mapres
	.reloc ., R_386_SIZE32, vm_mapres; .long 0
	.long 0x63805f3
	.long 0 /* index: 3438 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3439 */
	.long 0
	.long 0
	.long 0
	.long .Lname3440 /* index: 3440 */
	.weak vm_datapart_map_ram_autoprop_p; .long vm_datapart_map_ram_autoprop_p
	.reloc ., R_386_SIZE32, vm_datapart_map_ram_autoprop_p; .long 0
	.long 0x9217d70
	.long 0 /* index: 3441 */
	.long 0
	.long 0
	.long 0
	.long .Lname3442 /* index: 3442 */
	.weak mouse_buffer_putpackets_nopr; .long mouse_buffer_putpackets_nopr
	.reloc ., R_386_SIZE32, mouse_buffer_putpackets_nopr; .long 0
	.long 0x5a58d72
	.long 0 /* index: 3443 */
	.long 0
	.long 0
	.long 0
	.long .Lname3444 /* index: 3444 */
	.weak sys_setsockopt; .long sys_setsockopt
	.reloc ., R_386_SIZE32, sys_setsockopt; .long 0
	.long 0xad09d74
	.long .Lname3445 /* index: 3445 */
	.weak vm_kernel_treelock_downgrade; .long vm_kernel_treelock_downgrade
	.reloc ., R_386_SIZE32, vm_kernel_treelock_downgrade; .long 0
	.long 0xf47fd75
	.long .Lname3446 /* index: 3446 */
	.weak dbg_printf; .long dbg_printf
	.reloc ., R_386_SIZE32, dbg_printf; .long 0
	.long 0x67e6d76
	.long 0 /* index: 3447 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3448 */
	.long 0
	.long 0
	.long 0
	.long .Lname3449 /* index: 3449 */
	.weak sys_sched_yield; .long sys_sched_yield
	.reloc ., R_386_SIZE32, sys_sched_yield; .long 0
	.long 0x1061f94
	.long 0 /* index: 3450 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3451 */
	.long 0
	.long 0
	.long 0
	.long .Lname3452 /* index: 3452 */
	.weak memrlenl; .long memrlenl
	.reloc ., R_386_SIZE32, memrlenl; .long 0
	.long 0xc492d7c
	.long 0 /* index: 3453 */
	.long 0
	.long 0
	.long 0
	.long .Lname3454 /* index: 3454 */
	.weak unicode_readutf8_n; .long unicode_readutf8_n
	.reloc ., R_386_SIZE32, unicode_readutf8_n; .long 0
	.long 0x6b8ed7e
	.long .Lname3455 /* index: 3455 */
	.weak sys_pause; .long sys_pause
	.reloc ., R_386_SIZE32, sys_pause; .long 0
	.long 0x966f795
	.long 0 /* index: 3456 */
	.long 0
	.long 0
	.long 0
	.long .Lname3457 /* index: 3457 */
	.weak memcmp; .long memcmp
	.reloc ., R_386_SIZE32, memcmp; .long 0
	.long 0x73c3a40
	.long .Lname3458 /* index: 3458 */
	.weak sys_pipe2; .long sys_pipe2
	.reloc ., R_386_SIZE32, sys_pipe2; .long 0
	.long 0x9677d82
	.long 0 /* index: 3459 */
	.long 0
	.long 0
	.long 0
	.long .Lname3460 /* index: 3460 */
	.weak sys_getdents64; .long sys_getdents64
	.reloc ., R_386_SIZE32, sys_getdents64; .long 0
	.long 0xa306d84
	.long .Lname3461 /* index: 3461 */
	.weak addr2line_vprintf; .long addr2line_vprintf
	.reloc ., R_386_SIZE32, addr2line_vprintf; .long 0
	.long 0x4312796
	.long 0 /* index: 3462 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3463 */
	.long 0
	.long 0
	.long 0
	.long .Lname3464 /* index: 3464 */
	.weak task_detach; .long task_detach
	.reloc ., R_386_SIZE32, task_detach; .long 0
	.long 0x5d62d88
	.long .Lname3465 /* index: 3465 */
	.weak driver_section_destroy; .long driver_section_destroy
	.reloc ., R_386_SIZE32, driver_section_destroy; .long 0
	.long 0xca42d89
	.long .Lname3466 /* index: 3466 */
	.weak sys_ustat; .long sys_ustat
	.reloc ., R_386_SIZE32, sys_ustat; .long 0
	.long 0x96cd184
	.long .Lname3467 /* index: 3467 */
	.weak sys_vfork; .long sys_vfork
	.reloc ., R_386_SIZE32, sys_vfork; .long 0
	.long 0x96ccd8b
	.long 0 /* index: 3468 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3469 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3470 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3471 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3472 */
	.long 0
	.long 0
	.long 0
	.long .Lname3473 /* index: 3473 */
	.weak vm_startdma; .long vm_startdma
	.reloc ., R_386_SIZE32, vm_startdma; .long 0
	.long 0xaf49d91
	.long 0 /* index: 3474 */
	.long 0
	.long 0
	.long 0
	.long .Lname3475 /* index: 3475 */
	.weak cpu_disable_preemptive_interrupts; .long cpu_disable_preemptive_interrupts
	.reloc ., R_386_SIZE32, cpu_disable_preemptive_interrupts; .long 0
	.long 0xf1a5d93
	.long .Lname3476 /* index: 3476 */
	.weak sys_timerfd_gettime64; .long sys_timerfd_gettime64
	.reloc ., R_386_SIZE32, sys_timerfd_gettime64; .long 0
	.long 0xa0cfd94
	.long .Lname3477 /* index: 3477 */
	.weak vm_datapart_write; .long vm_datapart_write
	.reloc ., R_386_SIZE32, vm_datapart_write; .long 0
	.long 0x2bbed95
	.long .Lname3478 /* index: 3478 */
	.weak handle_get_directory_node; .long handle_get_directory_node
	.reloc ., R_386_SIZE32, handle_get_directory_node; .long 0
	.long 0x247eb45
	.long 0 /* index: 3479 */
	.long 0
	.long 0
	.long 0
	.long .Lname3480 /* index: 3480 */
	.weak task_alloc_user_srpc_nx; .long task_alloc_user_srpc_nx
	.reloc ., R_386_SIZE32, task_alloc_user_srpc_nx; .long 0
	.long 0x9470d98
	.long 0 /* index: 3481 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3482 */
	.long 0
	.long 0
	.long 0
	.long .Lname3483 /* index: 3483 */
	.weak sys_mkdir; .long sys_mkdir
	.reloc ., R_386_SIZE32, sys_mkdir; .long 0
	.long 0x9646202
	.long 0 /* index: 3484 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3485 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3486 */
	.long 0
	.long 0
	.long 0
	.long .Lname3487 /* index: 3487 */
	.weak ansitty_device_write; .long ansitty_device_write
	.reloc ., R_386_SIZE32, ansitty_device_write; .long 0
	.long 0xb630245
	.long 0 /* index: 3488 */
	.long 0
	.long 0
	.long 0
	.long .Lname3489 /* index: 3489 */
	.weak regdump_scpustate; .long regdump_scpustate
	.reloc ., R_386_SIZE32, regdump_scpustate; .long 0
	.long 0xbf47cb5
	.long .Lname3490 /* index: 3490 */
	.weak rwlock_writing_r; .long rwlock_writing_r
	.reloc ., R_386_SIZE32, rwlock_writing_r; .long 0
	.long 0x508bda2
	.long .Lname3491 /* index: 3491 */
	.weak vm_datablock_haschanges; .long vm_datablock_haschanges
	.reloc ., R_386_SIZE32, vm_datablock_haschanges; .long 0
	.long 0xb096da3
	.long .Lname3492 /* index: 3492 */
	.weak debuginfo_cu_parser_loadattr_compile_unit; .long debuginfo_cu_parser_loadattr_compile_unit
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_loadattr_compile_unit; .long 0
	.long 0xe589da4
	.long .Lname3493 /* index: 3493 */
	.weak devfs_lock_endwrite; .long devfs_lock_endwrite
	.reloc ., R_386_SIZE32, devfs_lock_endwrite; .long 0
	.long 0xd287da5
	.long .Lname3494 /* index: 3494 */
	.weak error_vprintf; .long error_vprintf
	.reloc ., R_386_SIZE32, error_vprintf; .long 0
	.long 0x1e1ada6
	.long 0 /* index: 3495 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3496 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3497 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3498 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3499 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3500 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3501 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3502 */
	.long 0
	.long 0
	.long 0
	.long .Lname3503 /* index: 3503 */
	.weak sys_sysinfo; .long sys_sysinfo
	.reloc ., R_386_SIZE32, sys_sysinfo; .long 0
	.long 0xb730daf
	.long .Lname3504 /* index: 3504 */
	.weak vm_datablock_debugheap; .long vm_datablock_debugheap
	.reloc ., R_386_SIZE32, vm_datablock_debugheap; .long 0
	.long 0x6931db0
	.long 0 /* index: 3505 */
	.long 0
	.long 0
	.long 0
	.long .Lname3506 /* index: 3506 */
	.weak dbg_screen_height; .long dbg_screen_height
	.reloc ., R_386_SIZE32, dbg_screen_height; .long 0
	.long 0xc29ca94
	.long .Lname3507 /* index: 3507 */
	.weak aio_handle_multiple_func; .long aio_handle_multiple_func
	.reloc ., R_386_SIZE32, aio_handle_multiple_func; .long 0
	.long 0x43decf3
	.long 0 /* index: 3508 */
	.long 0
	.long 0
	.long 0
	.long .Lname3509 /* index: 3509 */
	.weak handle_close; .long handle_close
	.reloc ., R_386_SIZE32, handle_close; .long 0
	.long 0xdb27db5
	.long 0 /* index: 3510 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3511 */
	.long 0
	.long 0
	.long 0
	.long .Lname3512 /* index: 3512 */
	.weak task_schedule_synchronous_rpc_nx; .long task_schedule_synchronous_rpc_nx
	.reloc ., R_386_SIZE32, task_schedule_synchronous_rpc_nx; .long 0
	.long 0xf655db8
	.long .Lname3513 /* index: 3513 */
	.weak vm_memset; .long vm_memset
	.reloc ., R_386_SIZE32, vm_memset; .long 0
	.long 0x63c34f4
	.long 0 /* index: 3514 */
	.long 0
	.long 0
	.long 0
	.long .Lname3515 /* index: 3515 */
	.weak task_serve_nx; .long task_serve_nx
	.reloc ., R_386_SIZE32, task_serve_nx; .long 0
	.long 0x616c4b8
	.long 0 /* index: 3516 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3517 */
	.long 0
	.long 0
	.long 0
	.long .Lname3518 /* index: 3518 */
	.weak disasm_instrlen; .long disasm_instrlen
	.reloc ., R_386_SIZE32, disasm_instrlen; .long 0
	.long 0xc21edbe
	.long .Lname3519 /* index: 3519 */
	.weak rwlock_tryupgrade; .long rwlock_tryupgrade
	.reloc ., R_386_SIZE32, rwlock_tryupgrade; .long 0
	.long 0x6e1dcf5
	.long 0 /* index: 3520 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3521 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3522 */
	.long 0
	.long 0
	.long 0
	.long .Lname3523 /* index: 3523 */
	.weak fs_filesystem_types; .long fs_filesystem_types
	.reloc ., R_386_SIZE32, fs_filesystem_types; .long 0
	.long 0x42f7dc3
	.long .Lname3524 /* index: 3524 */
	.weak fs_filesystems_lock_tryread; .long fs_filesystems_lock_tryread
	.reloc ., R_386_SIZE32, fs_filesystems_lock_tryread; .long 0
	.long 0xb0e2dc4
	.long .Lname3525 /* index: 3525 */
	.weak blocking_cleanup_service; .long blocking_cleanup_service
	.reloc ., R_386_SIZE32, blocking_cleanup_service; .long 0
	.long 0x86c0dc5
	.long 0 /* index: 3526 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3527 */
	.long 0
	.long 0
	.long 0
	.long .Lname3528 /* index: 3528 */
	.weak vm_tasklock_read_nx; .long vm_tasklock_read_nx
	.reloc ., R_386_SIZE32, vm_tasklock_read_nx; .long 0
	.long 0x594edc8
	.long 0 /* index: 3529 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3530 */
	.long 0
	.long 0
	.long 0
	.long .Lname3531 /* index: 3531 */
	.weak __acheck; .long __acheck
	.reloc ., R_386_SIZE32, __acheck; .long 0
	.long 0x579edcb
	.long .Lname3532 /* index: 3532 */
	.weak block_device_partition_ioctl; .long block_device_partition_ioctl
	.reloc ., R_386_SIZE32, block_device_partition_ioctl; .long 0
	.long 0x66adcc
	.long 0 /* index: 3533 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3534 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3535 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3536 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3537 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3538 */
	.long 0
	.long 0
	.long 0
	.long .Lname3539 /* index: 3539 */
	.weak block_device_read_phys_sync; .long block_device_read_phys_sync
	.reloc ., R_386_SIZE32, block_device_read_phys_sync; .long 0
	.long 0x2b46dd3
	.long .Lname3540 /* index: 3540 */
	.weak sig_send; .long sig_send
	.reloc ., R_386_SIZE32, sig_send; .long 0
	.long 0xfd69dd4
	.long .Lname3541 /* index: 3541 */
	.weak vm_datablock_anonymize; .long vm_datablock_anonymize
	.reloc ., R_386_SIZE32, vm_datablock_anonymize; .long 0
	.long 0xb72ddd5
	.long 0 /* index: 3542 */
	.long 0
	.long 0
	.long 0
	.long .Lname3543 /* index: 3543 */
	.weak callback_list_detroy; .long callback_list_detroy
	.reloc ., R_386_SIZE32, callback_list_detroy; .long 0
	.long 0xcdd34f9
	.long 0 /* index: 3544 */
	.long 0
	.long 0
	.long 0
	.long .Lname3545 /* index: 3545 */
	.weak rwlock_downgrade_readonly; .long rwlock_downgrade_readonly
	.reloc ., R_386_SIZE32, rwlock_downgrade_readonly; .long 0
	.long 0xf562dd9
	.long .Lname3546 /* index: 3546 */
	.weak fs_destroy; .long fs_destroy
	.reloc ., R_386_SIZE32, fs_destroy; .long 0
	.long 0xacc6239
	.long 0 /* index: 3547 */
	.long 0
	.long 0
	.long 0
	.long .Lname3548 /* index: 3548 */
	.weak aio_multihandle_fail; .long aio_multihandle_fail
	.reloc ., R_386_SIZE32, aio_multihandle_fail; .long 0
	.long 0x81d8ddc
	.long .Lname3549 /* index: 3549 */
	.weak boot_partition; .long boot_partition
	.reloc ., R_386_SIZE32, boot_partition; .long 0
	.long 0xfdad04e
	.long .Lname3550 /* index: 3550 */
	.weak sys_chown; .long sys_chown
	.reloc ., R_386_SIZE32, sys_chown; .long 0
	.long 0x959adde
	.long .Lname3551 /* index: 3551 */
	.weak path_lock_tryservice; .long path_lock_tryservice
	.reloc ., R_386_SIZE32, path_lock_tryservice; .long 0
	.long 0xb712fa5
	.long .Lname3552 /* index: 3552 */
	.weak slab_kmalloc_nx20; .long slab_kmalloc_nx20
	.reloc ., R_386_SIZE32, slab_kmalloc_nx20; .long 0
	.long 0x40d3de0
	.long 0 /* index: 3553 */
	.long 0
	.long 0
	.long 0
	.long .Lname3554 /* index: 3554 */
	.weak kprinter; .long kprinter
	.reloc ., R_386_SIZE32, kprinter; .long 0
	.long 0x7905de2
	.long .Lname3555 /* index: 3555 */
	.weak task_enable_redirect_usercode_rpc; .long task_enable_redirect_usercode_rpc
	.reloc ., R_386_SIZE32, task_enable_redirect_usercode_rpc; .long 0
	.long 0x92cade3
	.long .Lname3556 /* index: 3556 */
	.weak sys_mprotect; .long sys_mprotect
	.reloc ., R_386_SIZE32, sys_mprotect; .long 0
	.long 0x463de4
	.long .Lname3557 /* index: 3557 */
	.weak vm_node_free; .long vm_node_free
	.reloc ., R_386_SIZE32, vm_node_free; .long 0
	.long 0xd86bde5
	.long 0 /* index: 3558 */
	.long 0
	.long 0
	.long 0
	.long .Lname3559 /* index: 3559 */
	.weak _this_x86_dr1; .long _this_x86_dr1
	.reloc ., R_386_SIZE32, _this_x86_dr1; .long 0
	.long 0xd155251
	.long 0 /* index: 3560 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3561 */
	.long 0
	.long 0
	.long 0
	.long .Lname3562 /* index: 3562 */
	.weak sys_openpty; .long sys_openpty
	.reloc ., R_386_SIZE32, sys_openpty; .long 0
	.long 0x6115ed9
	.long .Lname3563 /* index: 3563 */
	.weak sys_sigprocmask; .long sys_sigprocmask
	.reloc ., R_386_SIZE32, sys_sigprocmask; .long 0
	.long 0x231bdeb
	.long 0 /* index: 3564 */
	.long 0
	.long 0
	.long 0
	.long .Lname3565 /* index: 3565 */
	.weak sys_linux_fstat32; .long sys_linux_fstat32
	.reloc ., R_386_SIZE32, sys_linux_fstat32; .long 0
	.long 0xf344252
	.long .Lname3566 /* index: 3566 */
	.weak kmemalign; .long kmemalign
	.reloc ., R_386_SIZE32, kmemalign; .long 0
	.long 0xc385dee
	.long 0 /* index: 3567 */
	.long 0
	.long 0
	.long 0
	.long .Lname3568 /* index: 3568 */
	.weak pagedir_unprepare_map; .long pagedir_unprepare_map
	.reloc ., R_386_SIZE32, pagedir_unprepare_map; .long 0
	.long 0xf67bdf0
	.long .Lname3569 /* index: 3569 */
	.weak x86_check_spurious_interrupt_PIC1; .long x86_check_spurious_interrupt_PIC1
	.reloc ., R_386_SIZE32, x86_check_spurious_interrupt_PIC1; .long 0
	.long 0x177adf1
	.long .Lname3570 /* index: 3570 */
	.weak ansitty_printer; .long ansitty_printer
	.reloc ., R_386_SIZE32, ansitty_printer; .long 0
	.long 0xd858df2
	.long .Lname3571 /* index: 3571 */
	.weak task_alloc_synchronous_srpc; .long task_alloc_synchronous_srpc
	.reloc ., R_386_SIZE32, task_alloc_synchronous_srpc; .long 0
	.long 0xaea5df3
	.long .Lname3572 /* index: 3572 */
	.weak fs_filesystems_lock_endread; .long fs_filesystems_lock_endread
	.reloc ., R_386_SIZE32, fs_filesystems_lock_endread; .long 0
	.long 0xb252df4
	.long .Lname3573 /* index: 3573 */
	.weak kernel_panic_icpustate; .long kernel_panic_icpustate
	.reloc ., R_386_SIZE32, kernel_panic_icpustate; .long 0
	.long 0x78a8df5
	.long .Lname3574 /* index: 3574 */
	.weak slab_kmalloc_nx16; .long slab_kmalloc_nx16
	.reloc ., R_386_SIZE32, slab_kmalloc_nx16; .long 0
	.long 0x40d3df6
	.long .Lname3575 /* index: 3575 */
	.weak sys_sendmsg; .long sys_sendmsg
	.reloc ., R_386_SIZE32, sys_sendmsg; .long 0
	.long 0x9dfbdf7
	.long 0 /* index: 3576 */
	.long 0
	.long 0
	.long 0
	.long .Lname3577 /* index: 3577 */
	.weak vm_datablock_locatepart_exact; .long vm_datablock_locatepart_exact
	.reloc ., R_386_SIZE32, vm_datablock_locatepart_exact; .long 0
	.long 0x4007254
	.long 0 /* index: 3578 */
	.long 0
	.long 0
	.long 0
	.long .Lname3579 /* index: 3579 */
	.weak format_quote; .long format_quote
	.reloc ., R_386_SIZE32, format_quote; .long 0
	.long 0xbe3535
	.long 0 /* index: 3580 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3581 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3582 */
	.long 0
	.long 0
	.long 0
	.long .Lname3583 /* index: 3583 */
	.weak fpustate_free; .long fpustate_free
	.reloc ., R_386_SIZE32, fpustate_free; .long 0
	.long 0x7e97255
	.long .Lname3584 /* index: 3584 */
	.weak unwind_getreg_kcpustate; .long unwind_getreg_kcpustate
	.reloc ., R_386_SIZE32, unwind_getreg_kcpustate; .long 0
	.long 0xb8c4bb5
	.long 0 /* index: 3585 */
	.long 0
	.long 0
	.long 0
	.long .Lname3586 /* index: 3586 */
	.weak heap_realloc_nx; .long heap_realloc_nx
	.reloc ., R_386_SIZE32, heap_realloc_nx; .long 0
	.long 0xb537188
	.long .Lname3587 /* index: 3587 */
	.weak task_disconnect_c; .long task_disconnect_c
	.reloc ., R_386_SIZE32, task_disconnect_c; .long 0
	.long 0x2a1be03
	.long .Lname3588 /* index: 3588 */
	.weak sys_linux_oldlstat; .long sys_linux_oldlstat
	.reloc ., R_386_SIZE32, sys_linux_oldlstat; .long 0
	.long 0xb5ffe04
	.long .Lname3589 /* index: 3589 */
	.weak sys_writev; .long sys_writev
	.reloc ., R_386_SIZE32, sys_writev; .long 0
	.long 0x6f0ba56
	.long .Lname3590 /* index: 3590 */
	.weak instruction_trysucc; .long instruction_trysucc
	.reloc ., R_386_SIZE32, instruction_trysucc; .long 0
	.long 0x1765033
	.long 0 /* index: 3591 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3592 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3593 */
	.long 0
	.long 0
	.long 0
	.long .Lname3594 /* index: 3594 */
	.weak sys_timer_gettime; .long sys_timer_gettime
	.reloc ., R_386_SIZE32, sys_timer_gettime; .long 0
	.long 0x7536105
	.long .Lname3595 /* index: 3595 */
	.weak sys_sgetmask; .long sys_sgetmask
	.reloc ., R_386_SIZE32, sys_sgetmask; .long 0
	.long 0xa7bae0b
	.long .Lname3596 /* index: 3596 */
	.weak path_traversefull; .long path_traversefull
	.reloc ., R_386_SIZE32, path_traversefull; .long 0
	.long 0xf55de0c
	.long .Lname3597 /* index: 3597 */
	.weak sys_llistxattr; .long sys_llistxattr
	.reloc ., R_386_SIZE32, sys_llistxattr; .long 0
	.long 0xa28bd02
	.long 0 /* index: 3598 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3599 */
	.long 0
	.long 0
	.long 0
	.long .Lname3600 /* index: 3600 */
	.weak vm_datapart_allocswap; .long vm_datapart_allocswap
	.reloc ., R_386_SIZE32, vm_datapart_allocswap; .long 0
	.long 0x682e10
	.long 0 /* index: 3601 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3602 */
	.long 0
	.long 0
	.long 0
	.long .Lname3603 /* index: 3603 */
	.weak vm_datablock_anonymous_zero_type_vec; .long vm_datablock_anonymous_zero_type_vec
	.reloc ., R_386_SIZE32, vm_datablock_anonymous_zero_type_vec; .long 0
	.long 0x27a0e13
	.long .Lname3604 /* index: 3604 */
	.weak debuginfo_cu_parser_getconst; .long debuginfo_cu_parser_getconst
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getconst; .long 0
	.long 0xb486e14
	.long .Lname3605 /* index: 3605 */
	.weak kernel_symbol_table; .long kernel_symbol_table
	.reloc ., R_386_SIZE32, kernel_symbol_table; .long 0
	.long 0x70d0e15
	.long 0 /* index: 3606 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3607 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3608 */
	.long 0
	.long 0
	.long 0
	.long .Lname3609 /* index: 3609 */
	.weak slab_malloc4; .long slab_malloc4
	.reloc ., R_386_SIZE32, slab_malloc4; .long 0
	.long 0x4e16d04
	.long 0 /* index: 3610 */
	.long 0
	.long 0
	.long 0
	.long .Lname3611 /* index: 3611 */
	.weak memlenq; .long memlenq
	.reloc ., R_386_SIZE32, memlenq; .long 0
	.long 0x3c42c21
	.long 0 /* index: 3612 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3613 */
	.long 0
	.long 0
	.long 0
	.long .Lname3614 /* index: 3614 */
	.weak disasm_print_instruction; .long disasm_print_instruction
	.reloc ., R_386_SIZE32, disasm_print_instruction; .long 0
	.long 0x433ee1e
	.long .Lname3615 /* index: 3615 */
	.weak page_isfree; .long page_isfree
	.reloc ., R_386_SIZE32, page_isfree; .long 0
	.long 0x67fa505
	.long .Lname3616 /* index: 3616 */
	.weak pagedir_prepare_mapone_p; .long pagedir_prepare_mapone_p
	.reloc ., R_386_SIZE32, pagedir_prepare_mapone_p; .long 0
	.long 0x9dd5e20
	.long 0 /* index: 3617 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3618 */
	.long 0
	.long 0
	.long 0
	.long .Lname3619 /* index: 3619 */
	.weak block_device_readv_phys; .long block_device_readv_phys
	.reloc ., R_386_SIZE32, block_device_readv_phys; .long 0
	.long 0x3231e23
	.long .Lname3620 /* index: 3620 */
	.weak sys_accept4; .long sys_accept4
	.reloc ., R_386_SIZE32, sys_accept4; .long 0
	.long 0x7e2ce24
	.long .Lname3621 /* index: 3621 */
	.weak sys_rpc_schedule; .long sys_rpc_schedule
	.reloc ., R_386_SIZE32, sys_rpc_schedule; .long 0
	.long 0xf7afe25
	.long 0 /* index: 3622 */
	.long 0
	.long 0
	.long 0
	.long .Lname3623 /* index: 3623 */
	.weak vio_xchw; .long vio_xchw
	.reloc ., R_386_SIZE32, vio_xchw; .long 0
	.long 0x56ee27
	.long 0 /* index: 3624 */
	.long 0
	.long 0
	.long 0
	.long .Lname3625 /* index: 3625 */
	.weak syscall_tracing_setenabled; .long syscall_tracing_setenabled
	.reloc ., R_386_SIZE32, syscall_tracing_setenabled; .long 0
	.long 0xab0f144
	.long 0 /* index: 3626 */
	.long 0
	.long 0
	.long 0
	.long .Lname3627 /* index: 3627 */
	.weak empty_kernel_sigmask; .long empty_kernel_sigmask
	.reloc ., R_386_SIZE32, empty_kernel_sigmask; .long 0
	.long 0xf36e2b
	.long 0 /* index: 3628 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3629 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3630 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3631 */
	.long 0
	.long 0
	.long 0
	.long .Lname3632 /* index: 3632 */
	.weak pagedir_map; .long pagedir_map
	.reloc ., R_386_SIZE32, pagedir_map; .long 0
	.long 0xb723e30
	.long .Lname3633 /* index: 3633 */
	.weak slab_malloc8; .long slab_malloc8
	.reloc ., R_386_SIZE32, slab_malloc8; .long 0
	.long 0x4e16d08
	.long .Lname3634 /* index: 3634 */
	.weak cpu_broadcastipi_notthis; .long cpu_broadcastipi_notthis
	.reloc ., R_386_SIZE32, cpu_broadcastipi_notthis; .long 0
	.long 0x20bde53
	.long 0 /* index: 3635 */
	.long 0
	.long 0
	.long 0
	.long .Lname3636 /* index: 3636 */
	.weak heap_truncate_untraced; .long heap_truncate_untraced
	.reloc ., R_386_SIZE32, heap_truncate_untraced; .long 0
	.long 0xa5f9e34
	.long .Lname3637 /* index: 3637 */
	.weak vm_kernel_syncone; .long vm_kernel_syncone
	.reloc ., R_386_SIZE32, vm_kernel_syncone; .long 0
	.long 0x80d1e35
	.long .Lname3638 /* index: 3638 */
	.weak sys_pwrite64f; .long sys_pwrite64f
	.reloc ., R_386_SIZE32, sys_pwrite64f; .long 0
	.long 0x403ee36
	.long 0 /* index: 3639 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3640 */
	.long 0
	.long 0
	.long 0
	.long .Lname3641 /* index: 3641 */
	.weak dbg_purgeuni; .long dbg_purgeuni
	.reloc ., R_386_SIZE32, dbg_purgeuni; .long 0
	.long 0xa251e39
	.long 0 /* index: 3642 */
	.long 0
	.long 0
	.long 0
	.long .Lname3643 /* index: 3643 */
	.weak sys_ssetmask; .long sys_ssetmask
	.reloc ., R_386_SIZE32, sys_ssetmask; .long 0
	.long 0xe7bae3b
	.long .Lname3644 /* index: 3644 */
	.weak vio_xchl; .long vio_xchl
	.reloc ., R_386_SIZE32, vio_xchl; .long 0
	.long 0x56ee3c
	.long 0 /* index: 3645 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3646 */
	.long 0
	.long 0
	.long 0
	.long .Lname3647 /* index: 3647 */
	.weak cmdline_decode; .long cmdline_decode
	.reloc ., R_386_SIZE32, cmdline_decode; .long 0
	.long 0x618a7b5
	.long 0 /* index: 3648 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3649 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3650 */
	.long 0
	.long 0
	.long 0
	.long .Lname3651 /* index: 3651 */
	.weak block_device_partition_read_phys; .long block_device_partition_read_phys
	.reloc ., R_386_SIZE32, block_device_partition_read_phys; .long 0
	.long 0x1063e43
	.long .Lname3652 /* index: 3652 */
	.weak sys_execveat; .long sys_execveat
	.reloc ., R_386_SIZE32, sys_execveat; .long 0
	.long 0x90a5e44
	.long .Lname3653 /* index: 3653 */
	.weak x86_this_user_fsbase; .long x86_this_user_fsbase
	.reloc ., R_386_SIZE32, x86_this_user_fsbase; .long 0
	.long 0x173be45
	.long .Lname3654 /* index: 3654 */
	.weak kernel_vpanic_lcpustate; .long kernel_vpanic_lcpustate
	.reloc ., R_386_SIZE32, kernel_vpanic_lcpustate; .long 0
	.long 0xf5af545
	.long 0 /* index: 3655 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3656 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3657 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3658 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3659 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3660 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3661 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3662 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3663 */
	.long 0
	.long 0
	.long 0
	.long .Lname3664 /* index: 3664 */
	.weak vsprintf_s; .long vsprintf_s
	.reloc ., R_386_SIZE32, vsprintf_s; .long 0
	.long 0x9027213
	.long 0 /* index: 3665 */
	.long 0
	.long 0
	.long 0
	.long .Lname3666 /* index: 3666 */
	.weak path_traverse; .long path_traverse
	.reloc ., R_386_SIZE32, path_traverse; .long 0
	.long 0xe062f55
	.long .Lname3667 /* index: 3667 */
	.weak block_device_write_phys; .long block_device_write_phys
	.reloc ., R_386_SIZE32, block_device_write_phys; .long 0
	.long 0x2137e53
	.long .Lname3668 /* index: 3668 */
	.weak path_printent; .long path_printent
	.reloc ., R_386_SIZE32, path_printent; .long 0
	.long 0xe8f4e54
	.long .Lname3669 /* index: 3669 */
	.weak vm_datapart_loaddatapage; .long vm_datapart_loaddatapage
	.reloc ., R_386_SIZE32, vm_datapart_loaddatapage; .long 0
	.long 0x128ce55
	.long .Lname3670 /* index: 3670 */
	.weak unicode_readutf16; .long unicode_readutf16
	.reloc ., R_386_SIZE32, unicode_readutf16; .long 0
	.long 0x26b8e56
	.long .Lname3671 /* index: 3671 */
	.weak driver_finalize; .long driver_finalize
	.reloc ., R_386_SIZE32, driver_finalize; .long 0
	.long 0x8c1f65
	.long .Lname3672 /* index: 3672 */
	.weak vm_datapart_lockwrite_setcore_unsharecow_nx; .long vm_datapart_lockwrite_setcore_unsharecow_nx
	.reloc ., R_386_SIZE32, vm_datapart_lockwrite_setcore_unsharecow_nx; .long 0
	.long 0x2083e58
	.long .Lname3673 /* index: 3673 */
	.weak sys_waitid; .long sys_waitid
	.reloc ., R_386_SIZE32, sys_waitid; .long 0
	.long 0x6d1ba64
	.long .Lname3674 /* index: 3674 */
	.weak block_device_awrite_phys; .long block_device_awrite_phys
	.reloc ., R_386_SIZE32, block_device_awrite_phys; .long 0
	.long 0xd11283
	.long 0 /* index: 3675 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3676 */
	.long 0
	.long 0
	.long 0
	.long .Lname3677 /* index: 3677 */
	.weak task_pause; .long task_pause
	.reloc ., R_386_SIZE32, task_pause; .long 0
	.long 0x1612435
	.long .Lname3678 /* index: 3678 */
	.weak page_stat_between; .long page_stat_between
	.reloc ., R_386_SIZE32, page_stat_between; .long 0
	.long 0xe172e5e
	.long .Lname3679 /* index: 3679 */
	.weak sys_sync_file_range; .long sys_sync_file_range
	.reloc ., R_386_SIZE32, sys_sync_file_range; .long 0
	.long 0x6f4e265
	.long 0 /* index: 3680 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3681 */
	.long 0
	.long 0
	.long 0
	.long .Lname3682 /* index: 3682 */
	.weak sys_getxattr; .long sys_getxattr
	.reloc ., R_386_SIZE32, sys_getxattr; .long 0
	.long 0xb0e1e62
	.long .Lname3683 /* index: 3683 */
	.weak sys_remap_file_pages; .long sys_remap_file_pages
	.reloc ., R_386_SIZE32, sys_remap_file_pages; .long 0
	.long 0x3b53e63
	.long .Lname3684 /* index: 3684 */
	.weak pagedir_maphint; .long pagedir_maphint
	.reloc ., R_386_SIZE32, pagedir_maphint; .long 0
	.long 0xe3d9e64
	.long .Lname3685 /* index: 3685 */
	.weak dbg_tabsize; .long dbg_tabsize
	.reloc ., R_386_SIZE32, dbg_tabsize; .long 0
	.long 0xa132e65
	.long 0 /* index: 3686 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3687 */
	.long 0
	.long 0
	.long 0
	.long .Lname3688 /* index: 3688 */
	.weak path_lock_read; .long path_lock_read
	.reloc ., R_386_SIZE32, path_lock_read; .long 0
	.long 0x2b8ed44
	.long 0 /* index: 3689 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3690 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3691 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3692 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3693 */
	.long 0
	.long 0
	.long 0
	.long .Lname3694 /* index: 3694 */
	.weak vm_datapart_write_unsafe; .long vm_datapart_write_unsafe
	.reloc ., R_386_SIZE32, vm_datapart_write_unsafe; .long 0
	.long 0xd1b4e55
	.long 0 /* index: 3695 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3696 */
	.long 0
	.long 0
	.long 0
	.long .Lname3697 /* index: 3697 */
	.weak block_device_awritev_phys; .long block_device_awritev_phys
	.reloc ., R_386_SIZE32, block_device_awritev_phys; .long 0
	.long 0xad18803
	.long .Lname3698 /* index: 3698 */
	.weak sys_getitimer; .long sys_getitimer
	.reloc ., R_386_SIZE32, sys_getitimer; .long 0
	.long 0x203be72
	.long 0 /* index: 3699 */
	.long 0
	.long 0
	.long 0
	.long .Lname3700 /* index: 3700 */
	.weak pagedir_gethint; .long pagedir_gethint
	.reloc ., R_386_SIZE32, pagedir_gethint; .long 0
	.long 0x719e74
	.long .Lname3701 /* index: 3701 */
	.weak heap_truncate; .long heap_truncate
	.reloc ., R_386_SIZE32, heap_truncate; .long 0
	.long 0x71cfe75
	.long .Lname3702 /* index: 3702 */
	.weak unicode_readutf8_rev; .long unicode_readutf8_rev
	.reloc ., R_386_SIZE32, unicode_readutf8_rev; .long 0
	.long 0x8ed4e76
	.long 0 /* index: 3703 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3704 */
	.long 0
	.long 0
	.long 0
	.long .Lname3705 /* index: 3705 */
	.weak sys_rt_sigtimedwait; .long sys_rt_sigtimedwait
	.reloc ., R_386_SIZE32, sys_rt_sigtimedwait; .long 0
	.long 0xe2d5514
	.long 0 /* index: 3706 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3707 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3708 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3709 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3710 */
	.long 0
	.long 0
	.long 0
	.long .Lname3711 /* index: 3711 */
	.weak sighand_ptr_lockread; .long sighand_ptr_lockread
	.reloc ., R_386_SIZE32, sighand_ptr_lockread; .long 0
	.long 0xc448c34
	.long .Lname3712 /* index: 3712 */
	.weak pagedir_unwrite_p; .long pagedir_unwrite_p
	.reloc ., R_386_SIZE32, pagedir_unwrite_p; .long 0
	.long 0x602be80
	.long .Lname3713 /* index: 3713 */
	.weak sys_getpgrp; .long sys_getpgrp
	.reloc ., R_386_SIZE32, sys_getpgrp; .long 0
	.long 0xdb067c0
	.long 0 /* index: 3714 */
	.long 0
	.long 0
	.long 0
	.long .Lname3715 /* index: 3715 */
	.weak task_schedule_asynchronous_srpc; .long task_schedule_asynchronous_srpc
	.reloc ., R_386_SIZE32, task_schedule_asynchronous_srpc; .long 0
	.long 0xf54ce83
	.long .Lname3716 /* index: 3716 */
	.weak userkern_segment_part; .long userkern_segment_part
	.reloc ., R_386_SIZE32, userkern_segment_part; .long 0
	.long 0xfac1e84
	.long .Lname3717 /* index: 3717 */
	.weak character_device_lookup_name; .long character_device_lookup_name
	.reloc ., R_386_SIZE32, character_device_lookup_name; .long 0
	.long 0x4d7fe85
	.long .Lname3718 /* index: 3718 */
	.weak vm_datablock_write_buffered; .long vm_datablock_write_buffered
	.reloc ., R_386_SIZE32, vm_datablock_write_buffered; .long 0
	.long 0xa349104
	.long 0 /* index: 3719 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3720 */
	.long 0
	.long 0
	.long 0
	.long .Lname3721 /* index: 3721 */
	.weak dbg_ungetuni; .long dbg_ungetuni
	.reloc ., R_386_SIZE32, dbg_ungetuni; .long 0
	.long 0x2746e89
	.long .Lname3722 /* index: 3722 */
	.weak ringbuffer_write; .long ringbuffer_write
	.reloc ., R_386_SIZE32, ringbuffer_write; .long 0
	.long 0xbf2ec25
	.long 0 /* index: 3723 */
	.long 0
	.long 0
	.long 0
	.long .Lname3724 /* index: 3724 */
	.weak dbg_bell; .long dbg_bell
	.reloc ., R_386_SIZE32, dbg_bell; .long 0
	.long 0x8d58e8c
	.long .Lname3725 /* index: 3725 */
	.weak debuginfo_cu_parser_getexpr; .long debuginfo_cu_parser_getexpr
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_getexpr; .long 0
	.long 0xbb42fc2
	.long 0 /* index: 3726 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3727 */
	.long 0
	.long 0
	.long 0
	.long .Lname3728 /* index: 3728 */
	.weak vm_copytophys; .long vm_copytophys
	.reloc ., R_386_SIZE32, vm_copytophys; .long 0
	.long 0xda3ca13
	.long 0 /* index: 3729 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3730 */
	.long 0
	.long 0
	.long 0
	.long .Lname3731 /* index: 3731 */
	.weak vm_datablock_anonymous_zero_vec; .long vm_datablock_anonymous_zero_vec
	.reloc ., R_386_SIZE32, vm_datablock_anonymous_zero_vec; .long 0
	.long 0x1362e93
	.long .Lname3732 /* index: 3732 */
	.weak debuginfo_cu_parser_nextchild; .long debuginfo_cu_parser_nextchild
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_nextchild; .long 0
	.long 0x1492e94
	.long .Lname3733 /* index: 3733 */
	.weak pagedir_translate; .long pagedir_translate
	.reloc ., R_386_SIZE32, pagedir_translate; .long 0
	.long 0xd2c3e95
	.long 0 /* index: 3734 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3735 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3736 */
	.long 0
	.long 0
	.long 0
	.long .Lname3737 /* index: 3737 */
	.weak sys_timer_gettime64; .long sys_timer_gettime64
	.reloc ., R_386_SIZE32, sys_timer_gettime64; .long 0
	.long 0x3610fc4
	.long 0 /* index: 3738 */
	.long 0
	.long 0
	.long 0
	.long .Lname3739 /* index: 3739 */
	.weak sys_mlock; .long sys_mlock
	.reloc ., R_386_SIZE32, sys_mlock; .long 0
	.long 0x9646e9b
	.long .Lname3740 /* index: 3740 */
	.weak sys_statfs64; .long sys_statfs64
	.reloc ., R_386_SIZE32, sys_statfs64; .long 0
	.long 0xd3a4034
	.long .Lname3741 /* index: 3741 */
	.weak handle_get_pipe; .long handle_get_pipe
	.reloc ., R_386_SIZE32, handle_get_pipe; .long 0
	.long 0x834cb35
	.long .Lname3742 /* index: 3742 */
	.weak block_device_aread; .long block_device_aread
	.reloc ., R_386_SIZE32, block_device_aread; .long 0
	.long 0xa671ef4
	.long .Lname3743 /* index: 3743 */
	.weak sys_sethostname; .long sys_sethostname
	.reloc ., R_386_SIZE32, sys_sethostname; .long 0
	.long 0xfc4f7c5
	.long .Lname3744 /* index: 3744 */
	.weak kernel_debugtrap; .long kernel_debugtrap
	.reloc ., R_386_SIZE32, kernel_debugtrap; .long 0
	.long 0xd79fea0
	.long .Lname3745 /* index: 3745 */
	.weak sys_raiseat; .long sys_raiseat
	.reloc ., R_386_SIZE32, sys_raiseat; .long 0
	.long 0x81b92e4
	.long 0 /* index: 3746 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3747 */
	.long 0
	.long 0
	.long 0
	.long .Lname3748 /* index: 3748 */
	.weak vm_datapart_read; .long vm_datapart_read
	.reloc ., R_386_SIZE32, vm_datapart_read; .long 0
	.long 0x32bdea4
	.long .Lname3749 /* index: 3749 */
	.weak handle_tryclose; .long handle_tryclose
	.reloc ., R_386_SIZE32, handle_tryclose; .long 0
	.long 0xd4d0ea5
	.long 0 /* index: 3750 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3751 */
	.long 0
	.long 0
	.long 0
	.long .Lname3752 /* index: 3752 */
	.weak rwlock_read_nx; .long rwlock_read_nx
	.reloc ., R_386_SIZE32, rwlock_read_nx; .long 0
	.long 0x6824ea8
	.long .Lname3753 /* index: 3753 */
	.weak __cxa_rethrow; .long __cxa_rethrow
	.reloc ., R_386_SIZE32, __cxa_rethrow; .long 0
	.long 0xd902067
	.long 0 /* index: 3754 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3755 */
	.long 0
	.long 0
	.long 0
	.long .Lname3756 /* index: 3756 */
	.weak sys_fcntl; .long sys_fcntl
	.reloc ., R_386_SIZE32, sys_fcntl; .long 0
	.long 0x95cfeac
	.long 0 /* index: 3757 */
	.long 0
	.long 0
	.long 0
	.long .Lname3758 /* index: 3758 */
	.weak sys_klstat; .long sys_klstat
	.reloc ., R_386_SIZE32, sys_klstat; .long 0
	.long 0x6241a14
	.long 0 /* index: 3759 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3760 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3761 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3762 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3763 */
	.long 0
	.long 0
	.long 0
	.long .Lname3764 /* index: 3764 */
	.weak pidns_end; .long pidns_end
	.reloc ., R_386_SIZE32, pidns_end; .long 0
	.long 0xb592eb4
	.long .Lname3765 /* index: 3765 */
	.weak pidns_upgrade; .long pidns_upgrade
	.reloc ., R_386_SIZE32, pidns_upgrade; .long 0
	.long 0xa95deb5
	.long 0 /* index: 3766 */
	.long 0
	.long 0
	.long 0
	.long .Lname3767 /* index: 3767 */
	.weak sys_sigsuspend; .long sys_sigsuspend
	.reloc ., R_386_SIZE32, sys_sigsuspend; .long 0
	.long 0xa5cf414
	.long .Lname3768 /* index: 3768 */
	.weak vm_do_allocram_nx; .long vm_do_allocram_nx
	.reloc ., R_386_SIZE32, vm_do_allocram_nx; .long 0
	.long 0xfad1eb8
	.long .Lname3769 /* index: 3769 */
	.weak ttybase_device_hupctty; .long ttybase_device_hupctty
	.reloc ., R_386_SIZE32, ttybase_device_hupctty; .long 0
	.long 0xb871eb9
	.long 0 /* index: 3770 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3771 */
	.long 0
	.long 0
	.long 0
	.long .Lname3772 /* index: 3772 */
	.weak sighand_raise_signal; .long sighand_raise_signal
	.reloc ., R_386_SIZE32, sighand_raise_signal; .long 0
	.long 0xfc56ebc
	.long 0 /* index: 3773 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3774 */
	.long 0
	.long 0
	.long 0
	.long .Lname3775 /* index: 3775 */
	.weak character_device_register_auto; .long character_device_register_auto
	.reloc ., R_386_SIZE32, character_device_register_auto; .long 0
	.long 0x4471ebf
	.long 0 /* index: 3776 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3777 */
	.long 0
	.long 0
	.long 0
	.long .Lname3778 /* index: 3778 */
	.weak vmb_alloc_peb; .long vmb_alloc_peb
	.reloc ., R_386_SIZE32, vmb_alloc_peb; .long 0
	.long 0x613ec2
	.long .Lname3779 /* index: 3779 */
	.weak vm_exec; .long vm_exec
	.reloc ., R_386_SIZE32, vm_exec; .long 0
	.long 0xd35cec3
	.long .Lname3780 /* index: 3780 */
	.weak sys_rt_sigsuspend; .long sys_rt_sigsuspend
	.reloc ., R_386_SIZE32, sys_rt_sigsuspend; .long 0
	.long 0x337fec4
	.long .Lname3781 /* index: 3781 */
	.weak page_free; .long page_free
	.reloc ., R_386_SIZE32, page_free; .long 0
	.long 0xdb5aec5
	.long .Lname3782 /* index: 3782 */
	.weak krealign_offset; .long krealign_offset
	.reloc ., R_386_SIZE32, krealign_offset; .long 0
	.long 0xfde4904
	.long 0 /* index: 3783 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3784 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3785 */
	.long 0
	.long 0
	.long 0
	.long .Lname3786 /* index: 3786 */
	.weak kernel_vpanic_scpustate; .long kernel_vpanic_scpustate
	.reloc ., R_386_SIZE32, kernel_vpanic_scpustate; .long 0
	.long 0xf5ade45
	.long 0 /* index: 3787 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3788 */
	.long 0
	.long 0
	.long 0
	.long .Lname3789 /* index: 3789 */
	.weak driver_getshstrtab; .long driver_getshstrtab
	.reloc ., R_386_SIZE32, driver_getshstrtab; .long 0
	.long 0xd4f5d22
	.long .Lname3790 /* index: 3790 */
	.weak mouse_device_motion; .long mouse_device_motion
	.reloc ., R_386_SIZE32, mouse_device_motion; .long 0
	.long 0xca6cece
	.long 0 /* index: 3791 */
	.long 0
	.long 0
	.long 0
	.long .Lname3792 /* index: 3792 */
	.weak vmb_overlay; .long vmb_overlay
	.reloc ., R_386_SIZE32, vmb_overlay; .long 0
	.long 0x6b1cae9
	.long 0 /* index: 3793 */
	.long 0
	.long 0
	.long 0
	.long .Lname3794 /* index: 3794 */
	.weak cpu_vector; .long cpu_vector
	.reloc ., R_386_SIZE32, cpu_vector; .long 0
	.long 0x6cd0ed2
	.long 0 /* index: 3795 */
	.long 0
	.long 0
	.long 0
	.long .Lname3796 /* index: 3796 */
	.weak inode_aread; .long inode_aread
	.reloc ., R_386_SIZE32, inode_aread; .long 0
	.long 0xb28ded4
	.long .Lname3797 /* index: 3797 */
	.weak path_rename; .long path_rename
	.reloc ., R_386_SIZE32, path_rename; .long 0
	.long 0x6feced5
	.long .Lname3798 /* index: 3798 */
	.weak vm_read_nopf; .long vm_read_nopf
	.reloc ., R_386_SIZE32, vm_read_nopf; .long 0
	.long 0x573ed6
	.long 0 /* index: 3799 */
	.long 0
	.long 0
	.long 0
	.long .Lname3800 /* index: 3800 */
	.weak path_lock_write_nx; .long path_lock_write_nx
	.reloc ., R_386_SIZE32, path_lock_write_nx; .long 0
	.long 0xf382ed8
	.long .Lname3801 /* index: 3801 */
	.weak json_parser_enterarray; .long json_parser_enterarray
	.reloc ., R_386_SIZE32, json_parser_enterarray; .long 0
	.long 0x4acaed9
	.long 0 /* index: 3802 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3803 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3804 */
	.long 0
	.long 0
	.long 0
	.long .Lname3805 /* index: 3805 */
	.weak vm_isused; .long vm_isused
	.reloc ., R_386_SIZE32, vm_isused; .long 0
	.long 0x60ab484
	.long 0 /* index: 3806 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3807 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3808 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3809 */
	.long 0
	.long 0
	.long 0
	.long .Lname3810 /* index: 3810 */
	.weak mouse_device_hwheel_nopr; .long mouse_device_hwheel_nopr
	.reloc ., R_386_SIZE32, mouse_device_hwheel_nopr; .long 0
	.long 0x3b1aee2
	.long .Lname3811 /* index: 3811 */
	.weak vm_copyfromphys; .long vm_copyfromphys
	.reloc ., R_386_SIZE32, vm_copyfromphys; .long 0
	.long 0xf026ee3
	.long .Lname3812 /* index: 3812 */
	.weak json_parser_enterobject; .long json_parser_enterobject
	.reloc ., R_386_SIZE32, json_parser_enterobject; .long 0
	.long 0xb1c6ee4
	.long .Lname3813 /* index: 3813 */
	.weak vm_kernel_treelock_upgrade; .long vm_kernel_treelock_upgrade
	.reloc ., R_386_SIZE32, vm_kernel_treelock_upgrade; .long 0
	.long 0xfdd8ee5
	.long 0 /* index: 3814 */
	.long 0
	.long 0
	.long 0
	.long .Lname3815 /* index: 3815 */
	.weak x86_idt_start_debug; .long x86_idt_start_debug
	.reloc ., R_386_SIZE32, x86_idt_start_debug; .long 0
	.long 0xb8c4ee7
	.long 0 /* index: 3816 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3817 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3818 */
	.long 0
	.long 0
	.long 0
	.long .Lname3819 /* index: 3819 */
	.weak ringbuffer_write_nonblock; .long ringbuffer_write_nonblock
	.reloc ., R_386_SIZE32, ringbuffer_write_nonblock; .long 0
	.long 0xc8b1eeb
	.long 0 /* index: 3820 */
	.long 0
	.long 0
	.long 0
	.long .Lname3821 /* index: 3821 */
	.weak json_parser_getint64; .long json_parser_getint64
	.reloc ., R_386_SIZE32, json_parser_getint64; .long 0
	.long 0xf5873d4
	.long .Lname3822 /* index: 3822 */
	.weak vm_oninit_callbacks; .long vm_oninit_callbacks
	.reloc ., R_386_SIZE32, vm_oninit_callbacks; .long 0
	.long 0x96845d3
	.long 0 /* index: 3823 */
	.long 0
	.long 0
	.long 0
	.long .Lname3824 /* index: 3824 */
	.weak character_device_lookup; .long character_device_lookup
	.reloc ., R_386_SIZE32, character_device_lookup; .long 0
	.long 0x93bab40
	.long 0 /* index: 3825 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3826 */
	.long 0
	.long 0
	.long 0
	.long .Lname3827 /* index: 3827 */
	.weak json_parser_unyield; .long json_parser_unyield
	.reloc ., R_386_SIZE32, json_parser_unyield; .long 0
	.long 0x3607a54
	.long .Lname3828 /* index: 3828 */
	.weak sys_pread64; .long sys_pread64
	.reloc ., R_386_SIZE32, sys_pread64; .long 0
	.long 0x7f07ef4
	.long .Lname3829 /* index: 3829 */
	.weak kernel_debugtrap_icpustate; .long kernel_debugtrap_icpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_icpustate; .long 0
	.long 0x9638ef5
	.long 0 /* index: 3830 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3831 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3832 */
	.long 0
	.long 0
	.long 0
	.long .Lname3833 /* index: 3833 */
	.weak instruction_pred; .long instruction_pred
	.reloc ., R_386_SIZE32, instruction_pred; .long 0
	.long 0xfbad7d4
	.long 0 /* index: 3834 */
	.long 0
	.long 0
	.long 0
	.long .Lname3835 /* index: 3835 */
	.weak superblock_nodeslock_downgrade; .long superblock_nodeslock_downgrade
	.reloc ., R_386_SIZE32, superblock_nodeslock_downgrade; .long 0
	.long 0xe2f1ac5
	.long .Lname3836 /* index: 3836 */
	.weak dbg_scroll; .long dbg_scroll
	.reloc ., R_386_SIZE32, dbg_scroll; .long 0
	.long 0x69c3efc
	.long 0 /* index: 3837 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3838 */
	.long 0
	.long 0
	.long 0
	.long .Lname3839 /* index: 3839 */
	.weak sys_pipe; .long sys_pipe
	.reloc ., R_386_SIZE32, sys_pipe; .long 0
	.long 0x9677d5
	.long .Lname3840 /* index: 3840 */
	.weak pagedir_unmap_userspace_p; .long pagedir_unmap_userspace_p
	.reloc ., R_386_SIZE32, pagedir_unmap_userspace_p; .long 0
	.long 0x2130f00
	.long .Lname3841 /* index: 3841 */
	.weak mempmoveq; .long mempmoveq
	.reloc ., R_386_SIZE32, mempmoveq; .long 0
	.long 0x4741f01
	.long 0 /* index: 3842 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3843 */
	.long 0
	.long 0
	.long 0
	.long .Lname3844 /* index: 3844 */
	.weak error_throw_current; .long error_throw_current
	.reloc ., R_386_SIZE32, error_throw_current; .long 0
	.long 0xcab8f04
	.long .Lname3845 /* index: 3845 */
	.weak vm_datablock_read_unsafe; .long vm_datablock_read_unsafe
	.reloc ., R_386_SIZE32, vm_datablock_read_unsafe; .long 0
	.long 0x881af05
	.long 0 /* index: 3846 */
	.long 0
	.long 0
	.long 0
	.long .Lname3847 /* index: 3847 */
	.weak mempmovew; .long mempmovew
	.reloc ., R_386_SIZE32, mempmovew; .long 0
	.long 0x4741f07
	.long 0 /* index: 3848 */
	.long 0
	.long 0
	.long 0
	.long .Lname3849 /* index: 3849 */
	.weak callback_list_empty; .long callback_list_empty
	.reloc ., R_386_SIZE32, callback_list_empty; .long 0
	.long 0x9cd5f09
	.long 0 /* index: 3850 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3851 */
	.long 0
	.long 0
	.long 0
	.long .Lname3852 /* index: 3852 */
	.weak inode_ioctl; .long inode_ioctl
	.reloc ., R_386_SIZE32, inode_ioctl; .long 0
	.long 0xb300f0c
	.long 0 /* index: 3853 */
	.long 0
	.long 0
	.long 0
	.long .Lname3854 /* index: 3854 */
	.weak heap_allat_untraced; .long heap_allat_untraced
	.reloc ., R_386_SIZE32, heap_allat_untraced; .long 0
	.long 0x8297a14
	.long 0 /* index: 3855 */
	.long 0
	.long 0
	.long 0
	.long .Lname3856 /* index: 3856 */
	.weak pagedir_map_p; .long pagedir_map_p
	.reloc ., R_386_SIZE32, pagedir_map_p; .long 0
	.long 0x23e3f10
	.long .Lname3857 /* index: 3857 */
	.weak path_lock_read_nx; .long path_lock_read_nx
	.reloc ., R_386_SIZE32, path_lock_read_nx; .long 0
	.long 0xed4cfd8
	.long .Lname3858 /* index: 3858 */
	.weak mouse_device_button_ex_nopr; .long mouse_device_button_ex_nopr
	.reloc ., R_386_SIZE32, mouse_device_button_ex_nopr; .long 0
	.long 0x1daf12
	.long .Lname3859 /* index: 3859 */
	.weak regdump_sgregs_with_cs_ss; .long regdump_sgregs_with_cs_ss
	.reloc ., R_386_SIZE32, regdump_sgregs_with_cs_ss; .long 0
	.long 0xe382283
	.long .Lname3860 /* index: 3860 */
	.weak vio_writew_aligned; .long vio_writew_aligned
	.reloc ., R_386_SIZE32, vio_writew_aligned; .long 0
	.long 0x8f55f14
	.long .Lname3861 /* index: 3861 */
	.weak cpu_apply_icpustate; .long cpu_apply_icpustate
	.reloc ., R_386_SIZE32, cpu_apply_icpustate; .long 0
	.long 0xa8caf15
	.long .Lname3862 /* index: 3862 */
	.weak block_device_areadv; .long block_device_areadv
	.reloc ., R_386_SIZE32, block_device_areadv; .long 0
	.long 0x671ef16
	.long .Lname3863 /* index: 3863 */
	.weak debuginfo_cu_parser_nextsibling; .long debuginfo_cu_parser_nextsibling
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_nextsibling; .long 0
	.long 0x93b9f17
	.long .Lname3864 /* index: 3864 */
	.weak json_parser_findindex; .long json_parser_findindex
	.reloc ., R_386_SIZE32, json_parser_findindex; .long 0
	.long 0xb2e0f18
	.long .Lname3865 /* index: 3865 */
	.weak devfs_lock_endread; .long devfs_lock_endread
	.reloc ., R_386_SIZE32, devfs_lock_endread; .long 0
	.long 0xd2e5a4
	.long .Lname3866 /* index: 3866 */
	.weak vio_addb; .long vio_addb
	.reloc ., R_386_SIZE32, vio_addb; .long 0
	.long 0x557d72
	.long 0 /* index: 3867 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3868 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3869 */
	.long 0
	.long 0
	.long 0
	.long .Lname3870 /* index: 3870 */
	.weak superblock_open; .long superblock_open
	.reloc ., R_386_SIZE32, superblock_open; .long 0
	.long 0xdd6f1e
	.long 0 /* index: 3871 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3872 */
	.long 0
	.long 0
	.long 0
	.long .Lname3873 /* index: 3873 */
	.weak sys_linux_fstat64; .long sys_linux_fstat64
	.reloc ., R_386_SIZE32, sys_linux_fstat64; .long 0
	.long 0xf3442a4
	.long 0 /* index: 3874 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3875 */
	.long 0
	.long 0
	.long 0
	.long .Lname3876 /* index: 3876 */
	.weak pidns_read; .long pidns_read
	.reloc ., R_386_SIZE32, pidns_read; .long 0
	.long 0x591e4c4
	.long 0 /* index: 3877 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3878 */
	.long 0
	.long 0
	.long 0
	.long .Lname3879 /* index: 3879 */
	.weak inode_read_phys_blocking; .long inode_read_phys_blocking
	.reloc ., R_386_SIZE32, inode_read_phys_blocking; .long 0
	.long 0x6d8af27
	.long 0 /* index: 3880 */
	.long 0
	.long 0
	.long 0
	.long .Lname3881 /* index: 3881 */
	.weak cpu_do_assert_integrity; .long cpu_do_assert_integrity
	.reloc ., R_386_SIZE32, cpu_do_assert_integrity; .long 0
	.long 0xd193f29
	.long 0 /* index: 3882 */
	.long 0
	.long 0
	.long 0
	.long .Lname3883 /* index: 3883 */
	.weak dbg; .long dbg
	.reloc ., R_386_SIZE32, dbg; .long 0
	.long 0x6a87
	.long .Lname3884 /* index: 3884 */
	.weak sys_ppoll; .long sys_ppoll
	.reloc ., R_386_SIZE32, sys_ppoll; .long 0
	.long 0x9672f2c
	.long .Lname3885 /* index: 3885 */
	.weak keyboard_buffer_putkey; .long keyboard_buffer_putkey
	.reloc ., R_386_SIZE32, keyboard_buffer_putkey; .long 0
	.long 0x6a00b29
	.long .Lname3886 /* index: 3886 */
	.weak unwind_fde_sigframe_exec; .long unwind_fde_sigframe_exec
	.reloc ., R_386_SIZE32, unwind_fde_sigframe_exec; .long 0
	.long 0x5d15dd3
	.long 0 /* index: 3887 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3888 */
	.long 0
	.long 0
	.long 0
	.long .Lname3889 /* index: 3889 */
	.weak vm_tasklock_upgrade_nx; .long vm_tasklock_upgrade_nx
	.reloc ., R_386_SIZE32, vm_tasklock_upgrade_nx; .long 0
	.long 0xce3c288
	.long 0 /* index: 3890 */
	.long 0
	.long 0
	.long 0
	.long .Lname3891 /* index: 3891 */
	.weak heap_realloc; .long heap_realloc
	.reloc ., R_386_SIZE32, heap_realloc; .long 0
	.long 0xe5db533
	.long .Lname3892 /* index: 3892 */
	.weak vm_datapart_lock_tryread; .long vm_datapart_lock_tryread
	.reloc ., R_386_SIZE32, vm_datapart_lock_tryread; .long 0
	.long 0x220df34
	.long .Lname3893 /* index: 3893 */
	.weak dbg_enter_ucpustate; .long dbg_enter_ucpustate
	.reloc ., R_386_SIZE32, dbg_enter_ucpustate; .long 0
	.long 0x7819f35
	.long .Lname3894 /* index: 3894 */
	.weak dbg_menuf; .long dbg_menuf
	.reloc ., R_386_SIZE32, dbg_menuf; .long 0
	.long 0xd63ef36
	.long .Lname3895 /* index: 3895 */
	.weak unwind_setreg_fcpustate; .long unwind_setreg_fcpustate
	.reloc ., R_386_SIZE32, unwind_setreg_fcpustate; .long 0
	.long 0xb8d36b5
	.long 0 /* index: 3896 */
	.long 0
	.long 0
	.long 0
	.long .Lname3897 /* index: 3897 */
	.weak task_sigcont; .long task_sigcont
	.reloc ., R_386_SIZE32, task_sigcont; .long 0
	.long 0xe554534
	.long .Lname3898 /* index: 3898 */
	.weak vm_datapart_haschanged; .long vm_datapart_haschanged
	.reloc ., R_386_SIZE32, vm_datapart_haschanged; .long 0
	.long 0xad0f0f4
	.long .Lname3899 /* index: 3899 */
	.weak sys_pselect6_64; .long sys_pselect6_64
	.reloc ., R_386_SIZE32, sys_pselect6_64; .long 0
	.long 0x2c063b4
	.long 0 /* index: 3900 */
	.long 0
	.long 0
	.long 0
	.long .Lname3901 /* index: 3901 */
	.weak dbg_enter_scpustate; .long dbg_enter_scpustate
	.reloc ., R_386_SIZE32, dbg_enter_scpustate; .long 0
	.long 0x7819d35
	.long .Lname3902 /* index: 3902 */
	.weak unicode_readutf16_swap_rev_n; .long unicode_readutf16_swap_rev_n
	.reloc ., R_386_SIZE32, unicode_readutf16_swap_rev_n; .long 0
	.long 0x1c8df3e
	.long .Lname3903 /* index: 3903 */
	.weak sys_uname; .long sys_uname
	.reloc ., R_386_SIZE32, sys_uname; .long 0
	.long 0x96c3d35
	.long 0 /* index: 3904 */
	.long 0
	.long 0
	.long 0
	.long .Lname3905 /* index: 3905 */
	.weak dbg_setscreendata; .long dbg_setscreendata
	.reloc ., R_386_SIZE32, dbg_setscreendata; .long 0
	.long 0x225bf41
	.long .Lname3906 /* index: 3906 */
	.weak sys_fremovexattr; .long sys_fremovexattr
	.reloc ., R_386_SIZE32, sys_fremovexattr; .long 0
	.long 0x9119f42
	.long 0 /* index: 3907 */
	.long 0
	.long 0
	.long 0
	.long .Lname3908 /* index: 3908 */
	.weak sys_fchmodat; .long sys_fchmodat
	.reloc ., R_386_SIZE32, sys_fchmodat; .long 0
	.long 0xe64cf44
	.long .Lname3909 /* index: 3909 */
	.weak vm_map_subrange; .long vm_map_subrange
	.reloc ., R_386_SIZE32, vm_map_subrange; .long 0
	.long 0xda05f45
	.long .Lname3910 /* index: 3910 */
	.weak format_vscanf; .long format_vscanf
	.reloc ., R_386_SIZE32, format_vscanf; .long 0
	.long 0xbb0af46
	.long 0 /* index: 3911 */
	.long 0
	.long 0
	.long 0
	.long .Lname3912 /* index: 3912 */
	.weak sprintf; .long sprintf
	.reloc ., R_386_SIZE32, sprintf; .long 0
	.long 0xa7905d6
	.long 0 /* index: 3913 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3914 */
	.long 0
	.long 0
	.long 0
	.long .Lname3915 /* index: 3915 */
	.weak syscall_emulate_callback; .long syscall_emulate_callback
	.reloc ., R_386_SIZE32, syscall_emulate_callback; .long 0
	.long 0x42d2f4b
	.long 0 /* index: 3916 */
	.long 0
	.long 0
	.long 0
	.long .Lname3917 /* index: 3917 */
	.weak sys_getresgid32; .long sys_getresgid32
	.reloc ., R_386_SIZE32, sys_getresgid32; .long 0
	.long 0x5c047e2
	.long .Lname3918 /* index: 3918 */
	.weak vm_datapart_lock_endread; .long vm_datapart_lock_endread
	.reloc ., R_386_SIZE32, vm_datapart_lock_endread; .long 0
	.long 0x3cbdf04
	.long 0 /* index: 3919 */
	.long 0
	.long 0
	.long 0
	.long .Lname3920 /* index: 3920 */
	.weak kernel_default_heap; .long kernel_default_heap
	.reloc ., R_386_SIZE32, kernel_default_heap; .long 0
	.long 0x8076f50
	.long 0 /* index: 3921 */
	.long 0
	.long 0
	.long 0
	.long .Lname3922 /* index: 3922 */
	.weak cpu_quantum_elapsed_nopr; .long cpu_quantum_elapsed_nopr
	.reloc ., R_386_SIZE32, cpu_quantum_elapsed_nopr; .long 0
	.long 0x406df52
	.long .Lname3923 /* index: 3923 */
	.weak sys_utimensat64; .long sys_utimensat64
	.reloc ., R_386_SIZE32, sys_utimensat64; .long 0
	.long 0x33552a4
	.long .Lname3924 /* index: 3924 */
	.weak block_device_makepart; .long block_device_makepart
	.reloc ., R_386_SIZE32, block_device_makepart; .long 0
	.long 0xf44cf54
	.long .Lname3925 /* index: 3925 */
	.weak rwlock_upgrade; .long rwlock_upgrade
	.reloc ., R_386_SIZE32, rwlock_upgrade; .long 0
	.long 0x25b2f55
	.long 0 /* index: 3926 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3927 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3928 */
	.long 0
	.long 0
	.long 0
	.long .Lname3929 /* index: 3929 */
	.weak character_device_pread; .long character_device_pread
	.reloc ., R_386_SIZE32, character_device_pread; .long 0
	.long 0x8b777e4
	.long 0 /* index: 3930 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3931 */
	.long 0
	.long 0
	.long 0
	.long .Lname3932 /* index: 3932 */
	.weak vio_cmpxch_or_writel; .long vio_cmpxch_or_writel
	.reloc ., R_386_SIZE32, vio_cmpxch_or_writel; .long 0
	.long 0x8230f5c
	.long 0 /* index: 3933 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3934 */
	.long 0
	.long 0
	.long 0
	.long .Lname3935 /* index: 3935 */
	.weak sys_mincore; .long sys_mincore
	.reloc ., R_386_SIZE32, sys_mincore; .long 0
	.long 0x39fafe5
	.long .Lname3936 /* index: 3936 */
	.weak vm86_fullstep; .long vm86_fullstep
	.reloc ., R_386_SIZE32, vm86_fullstep; .long 0
	.long 0x7386f60
	.long 0 /* index: 3937 */
	.long 0
	.long 0
	.long 0
	.long .Lname3938 /* index: 3938 */
	.weak isr_vector_trigger; .long isr_vector_trigger
	.reloc ., R_386_SIZE32, isr_vector_trigger; .long 0
	.long 0x72e3f62
	.long .Lname3939 /* index: 3939 */
	.weak inode_areadall_phys; .long inode_areadall_phys
	.reloc ., R_386_SIZE32, inode_areadall_phys; .long 0
	.long 0xbd8bf63
	.long .Lname3940 /* index: 3940 */
	.weak dbg_isholding_shift; .long dbg_isholding_shift
	.reloc ., R_386_SIZE32, dbg_isholding_shift; .long 0
	.long 0xa863f64
	.long .Lname3941 /* index: 3941 */
	.weak handle_lookup_type; .long handle_lookup_type
	.reloc ., R_386_SIZE32, handle_lookup_type; .long 0
	.long 0x1adaf65
	.long 0 /* index: 3942 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3943 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3944 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3945 */
	.long 0
	.long 0
	.long 0
	.long .Lname3946 /* index: 3946 */
	.weak driver_try_decref_and_delmod; .long driver_try_decref_and_delmod
	.reloc ., R_386_SIZE32, driver_try_decref_and_delmod; .long 0
	.long 0xd9720c4
	.long .Lname3947 /* index: 3947 */
	.weak cpu_sendipi_cpuset; .long cpu_sendipi_cpuset
	.reloc ., R_386_SIZE32, cpu_sendipi_cpuset; .long 0
	.long 0xb497944
	.long 0 /* index: 3948 */
	.long 0
	.long 0
	.long 0
	.long .Lname3949 /* index: 3949 */
	.weak mouse_device_motion_nopr; .long mouse_device_motion_nopr
	.reloc ., R_386_SIZE32, mouse_device_motion_nopr; .long 0
	.long 0xe103a92
	.long 0 /* index: 3950 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3951 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3952 */
	.long 0
	.long 0
	.long 0
	.long .Lname3953 /* index: 3953 */
	.weak task_tryyield_or_pause; .long task_tryyield_or_pause
	.reloc ., R_386_SIZE32, task_tryyield_or_pause; .long 0
	.long 0xa8862a5
	.long .Lname3954 /* index: 3954 */
	.weak dbg_evaladdr; .long dbg_evaladdr
	.reloc ., R_386_SIZE32, dbg_evaladdr; .long 0
	.long 0xaeaaf72
	.long .Lname3955 /* index: 3955 */
	.weak dbg_putc; .long dbg_putc
	.reloc ., R_386_SIZE32, dbg_putc; .long 0
	.long 0x8d67a03
	.long 0 /* index: 3956 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3957 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3958 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3959 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3960 */
	.long 0
	.long 0
	.long 0
	.long .Lname3961 /* index: 3961 */
	.weak sys_sched_setaffinity; .long sys_sched_setaffinity
	.reloc ., R_386_SIZE32, sys_sched_setaffinity; .long 0
	.long 0xdd07f79
	.long 0 /* index: 3962 */
	.long 0
	.long 0
	.long 0
	.long .Lname3963 /* index: 3963 */
	.weak sys_setrlimit; .long sys_setrlimit
	.reloc ., R_386_SIZE32, sys_setrlimit; .long 0
	.long 0x9babb4
	.long .Lname3964 /* index: 3964 */
	.weak mempmovel; .long mempmovel
	.reloc ., R_386_SIZE32, mempmovel; .long 0
	.long 0x4741f7c
	.long 0 /* index: 3965 */
	.long 0
	.long 0
	.long 0
	.long .Lname3966 /* index: 3966 */
	.weak dbg_pprint; .long dbg_pprint
	.reloc ., R_386_SIZE32, dbg_pprint; .long 0
	.long 0x6712884
	.long .Lname3967 /* index: 3967 */
	.weak slab_free; .long slab_free
	.reloc ., R_386_SIZE32, slab_free; .long 0
	.long 0x785a295
	.long 0 /* index: 3968 */
	.long 0
	.long 0
	.long 0
	.long .Lname3969 /* index: 3969 */
	.weak cpu_enter_deepsleep; .long cpu_enter_deepsleep
	.reloc ., R_386_SIZE32, cpu_enter_deepsleep; .long 0
	.long 0xcc52d40
	.long .Lname3970 /* index: 3970 */
	.weak sys_timerfd_settime; .long sys_timerfd_settime
	.reloc ., R_386_SIZE32, sys_timerfd_settime; .long 0
	.long 0x10a0cc5
	.long .Lname3971 /* index: 3971 */
	.weak system_clearcaches; .long system_clearcaches
	.reloc ., R_386_SIZE32, system_clearcaches; .long 0
	.long 0xe7d1f83
	.long .Lname3972 /* index: 3972 */
	.weak dbg_getfunc_start; .long dbg_getfunc_start
	.reloc ., R_386_SIZE32, dbg_getfunc_start; .long 0
	.long 0x6caff84
	.long .Lname3973 /* index: 3973 */
	.weak dbg_enter_here; .long dbg_enter_here
	.reloc ., R_386_SIZE32, dbg_enter_here; .long 0
	.long 0x4b02f85
	.long .Lname3974 /* index: 3974 */
	.weak path_remove; .long path_remove
	.reloc ., R_386_SIZE32, path_remove; .long 0
	.long 0x6fecc25
	.long .Lname3975 /* index: 3975 */
	.weak sys_setns; .long sys_setns
	.reloc ., R_386_SIZE32, sys_setns; .long 0
	.long 0x969b253
	.long 0 /* index: 3976 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3977 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3978 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3979 */
	.long 0
	.long 0
	.long 0
	.long .Lname3980 /* index: 3980 */
	.weak task_push_asynchronous_rpc; .long task_push_asynchronous_rpc
	.reloc ., R_386_SIZE32, task_push_asynchronous_rpc; .long 0
	.long 0x3d4e993
	.long .Lname3981 /* index: 3981 */
	.weak debuginfo_cu_parser_skipform; .long debuginfo_cu_parser_skipform
	.reloc ., R_386_SIZE32, debuginfo_cu_parser_skipform; .long 0
	.long 0x7e8df8d
	.long 0 /* index: 3982 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3983 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3984 */
	.long 0
	.long 0
	.long 0
	.long .Lname3985 /* index: 3985 */
	.weak mouse_device_read; .long mouse_device_read
	.reloc ., R_386_SIZE32, mouse_device_read; .long 0
	.long 0x2982b14
	.long 0 /* index: 3986 */
	.long 0
	.long 0
	.long 0
	.long .Lname3987 /* index: 3987 */
	.weak sys_fsync; .long sys_fsync
	.reloc ., R_386_SIZE32, sys_fsync; .long 0
	.long 0x95dd543
	.long .Lname3988 /* index: 3988 */
	.weak sys_prlimit64; .long sys_prlimit64
	.reloc ., R_386_SIZE32, sys_prlimit64; .long 0
	.long 0xa0b6f94
	.long .Lname3989 /* index: 3989 */
	.weak vm_datablock_write_unsafe; .long vm_datablock_write_unsafe
	.reloc ., R_386_SIZE32, vm_datablock_write_unsafe; .long 0
	.long 0xaa46f95
	.long 0 /* index: 3990 */
	.long 0
	.long 0
	.long 0
	.long .Lname3991 /* index: 3991 */
	.weak json_parser_printstring; .long json_parser_printstring
	.reloc ., R_386_SIZE32, json_parser_printstring; .long 0
	.long 0x9d53f97
	.long 0 /* index: 3992 */
	.long 0
	.long 0
	.long 0
	.long .Lname3993 /* index: 3993 */
	.weak x86_exsyscall_register_count; .long x86_exsyscall_register_count
	.reloc ., R_386_SIZE32, x86_exsyscall_register_count; .long 0
	.long 0x1738d44
	.long 0 /* index: 3994 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3995 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3996 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3997 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 3998 */
	.long 0
	.long 0
	.long 0
	.long .Lname3999 /* index: 3999 */
	.weak fpustate_saveinto; .long fpustate_saveinto
	.reloc ., R_386_SIZE32, fpustate_saveinto; .long 0
	.long 0x22c2f9f
	.long .Lname4000 /* index: 4000 */
	.weak pidns_trylookup; .long pidns_trylookup
	.reloc ., R_386_SIZE32, pidns_trylookup; .long 0
	.long 0x58d5fa0
	.long 0 /* index: 4001 */
	.long 0
	.long 0
	.long 0
	.long .Lname4002 /* index: 4002 */
	.weak __asm32_syscallrouter_sysenter; .long __asm32_syscallrouter_sysenter
	.reloc ., R_386_SIZE32, __asm32_syscallrouter_sysenter; .long 0
	.long 0x566dfa2
	.long .Lname4003 /* index: 4003 */
	.weak block_device_readv_phys_sync; .long block_device_readv_phys_sync
	.reloc ., R_386_SIZE32, block_device_readv_phys_sync; .long 0
	.long 0x2c49fa3
	.long .Lname4004 /* index: 4004 */
	.weak sys_getppid; .long sys_getppid
	.reloc ., R_386_SIZE32, sys_getppid; .long 0
	.long 0xdb07fa4
	.long .Lname4005 /* index: 4005 */
	.weak kernel_debugtrap_r_scpustate; .long kernel_debugtrap_r_scpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_scpustate; .long 0
	.long 0xed53fa5
	.long .Lname4006 /* index: 4006 */
	.weak x86_cputss_df; .long x86_cputss_df
	.reloc ., R_386_SIZE32, x86_cputss_df; .long 0
	.long 0x706efa6
	.long 0 /* index: 4007 */
	.long 0
	.long 0
	.long 0
	.long .Lname4008 /* index: 4008 */
	.weak vm_datapart_split_nx; .long vm_datapart_split_nx
	.reloc ., R_386_SIZE32, vm_datapart_split_nx; .long 0
	.long 0x503cfa8
	.long 0 /* index: 4009 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4010 */
	.long 0
	.long 0
	.long 0
	.long .Lname4011 /* index: 4011 */
	.weak vm_onfini_callbacks; .long vm_onfini_callbacks
	.reloc ., R_386_SIZE32, vm_onfini_callbacks; .long 0
	.long 0x25145f3
	.long 0 /* index: 4012 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4013 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4014 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4015 */
	.long 0
	.long 0
	.long 0
	.long .Lname4016 /* index: 4016 */
	.weak regdump_coregs; .long regdump_coregs
	.reloc ., R_386_SIZE32, regdump_coregs; .long 0
	.long 0xe5d4803
	.long .Lname4017 /* index: 4017 */
	.weak pidns_read_nx; .long pidns_read_nx
	.reloc ., R_386_SIZE32, pidns_read_nx; .long 0
	.long 0xe4cdd48
	.long .Lname4018 /* index: 4018 */
	.weak block_device_register; .long block_device_register
	.reloc ., R_386_SIZE32, block_device_register; .long 0
	.long 0x2980fb2
	.long .Lname4019 /* index: 4019 */
	.weak jiffies; .long jiffies
	.reloc ., R_386_SIZE32, jiffies; .long 0
	.long 0xfccfb3
	.long .Lname4020 /* index: 4020 */
	.weak vm_mapresat; .long vm_mapresat
	.reloc ., R_386_SIZE32, vm_mapresat; .long 0
	.long 0x805ffb4
	.long .Lname4021 /* index: 4021 */
	.weak directory_remove; .long directory_remove
	.reloc ., R_386_SIZE32, directory_remove; .long 0
	.long 0xd27ffb5
	.long 0 /* index: 4022 */
	.long 0
	.long 0
	.long 0
	.long .Lname4023 /* index: 4023 */
	.weak kernel_terminal_raise; .long kernel_terminal_raise
	.reloc ., R_386_SIZE32, kernel_terminal_raise; .long 0
	.long 0x5b7f3b5
	.long 0 /* index: 4024 */
	.long 0
	.long 0
	.long 0
	.long .Lname4025 /* index: 4025 */
	.weak sys_lseek64; .long sys_lseek64
	.reloc ., R_386_SIZE32, sys_lseek64; .long 0
	.long 0x3e0b7f4
	.long 0 /* index: 4026 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4027 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4028 */
	.long 0
	.long 0
	.long 0
	.long .Lname4029 /* index: 4029 */
	.weak task_setpid; .long task_setpid
	.reloc ., R_386_SIZE32, task_setpid; .long 0
	.long 0x6e63ce4
	.long .Lname4030 /* index: 4030 */
	.weak sys_openat; .long sys_openat
	.reloc ., R_386_SIZE32, sys_openat; .long 0
	.long 0x6611414
	.long .Lname4031 /* index: 4031 */
	.weak dbg_getscreendata; .long dbg_getscreendata
	.reloc ., R_386_SIZE32, dbg_getscreendata; .long 0
	.long 0x625bf71
	.long 0 /* index: 4032 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4033 */
	.long 0
	.long 0
	.long 0
	.long .Lname4034 /* index: 4034 */
	.weak strtou32; .long strtou32
	.reloc ., R_386_SIZE32, strtou32; .long 0
	.long 0xb9b6fc2
	.long .Lname4035 /* index: 4035 */
	.weak character_device_alloc; .long character_device_alloc
	.reloc ., R_386_SIZE32, character_device_alloc; .long 0
	.long 0x888efc3
	.long .Lname4036 /* index: 4036 */
	.weak sys_linux_oldstat; .long sys_linux_oldstat
	.reloc ., R_386_SIZE32, sys_linux_oldstat; .long 0
	.long 0x8b56fc4
	.long .Lname4037 /* index: 4037 */
	.weak disasm_print_line; .long disasm_print_line
	.reloc ., R_386_SIZE32, disasm_print_line; .long 0
	.long 0xfd95fc5
	.long 0 /* index: 4038 */
	.long 0
	.long 0
	.long 0
	.long .Lname4039 /* index: 4039 */
	.weak sys_setresgid32; .long sys_setresgid32
	.reloc ., R_386_SIZE32, sys_setresgid32; .long 0
	.long 0x5f447e2
	.long 0 /* index: 4040 */
	.long 0
	.long 0
	.long 0
	.long .Lname4041 /* index: 4041 */
	.weak vm_syncall; .long vm_syncall
	.reloc ., R_386_SIZE32, vm_syncall; .long 0
	.long 0xb03454c
	.long 0 /* index: 4042 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4043 */
	.long 0
	.long 0
	.long 0
	.long .Lname4044 /* index: 4044 */
	.weak mouse_device_init; .long mouse_device_init
	.reloc ., R_386_SIZE32, mouse_device_init; .long 0
	.long 0x29b6564
	.long 0 /* index: 4045 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4046 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4047 */
	.long 0
	.long 0
	.long 0
	.long .Lname4048 /* index: 4048 */
	.weak regdump_ip; .long regdump_ip
	.reloc ., R_386_SIZE32, regdump_ip; .long 0
	.long 0xbc3efd0
	.long 0 /* index: 4049 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4050 */
	.long 0
	.long 0
	.long 0
	.long .Lname4051 /* index: 4051 */
	.weak inode_awrite_phys; .long inode_awrite_phys
	.reloc ., R_386_SIZE32, inode_awrite_phys; .long 0
	.long 0x19ed2a3
	.long .Lname4052 /* index: 4052 */
	.weak inode_stat; .long inode_stat
	.reloc ., R_386_SIZE32, inode_stat; .long 0
	.long 0xab1afd4
	.long .Lname4053 /* index: 4053 */
	.weak inode_changed_chmtime; .long inode_changed_chmtime
	.reloc ., R_386_SIZE32, inode_changed_chmtime; .long 0
	.long 0xa123fd5
	.long .Lname4054 /* index: 4054 */
	.weak sys_pread64f; .long sys_pread64f
	.reloc ., R_386_SIZE32, sys_pread64f; .long 0
	.long 0xf07efd6
	.long 0 /* index: 4055 */
	.long 0
	.long 0
	.long 0
	.long .Lname4056 /* index: 4056 */
	.weak vm_datapart_lockread_setcore_unsharecow_nx; .long vm_datapart_lockread_setcore_unsharecow_nx
	.reloc ., R_386_SIZE32, vm_datapart_lockread_setcore_unsharecow_nx; .long 0
	.long 0xfc3afd8
	.long .Lname4057 /* index: 4057 */
	.weak sig_broadcast; .long sig_broadcast
	.reloc ., R_386_SIZE32, sig_broadcast; .long 0
	.long 0xc87c2a4
	.long 0 /* index: 4058 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4059 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4060 */
	.long 0
	.long 0
	.long 0
	.long .Lname4061 /* index: 4061 */
	.weak sys_recvfrom; .long sys_recvfrom
	.reloc ., R_386_SIZE32, sys_recvfrom; .long 0
	.long 0xc1c4fdd
	.long 0 /* index: 4062 */
	.long 0
	.long 0
	.long 0
	.long .Lname4063 /* index: 4063 */
	.weak kernel_debugtrap_r_fcpustate; .long kernel_debugtrap_r_fcpustate
	.reloc ., R_386_SIZE32, kernel_debugtrap_r_fcpustate; .long 0
	.long 0xed50aa5
	.long .Lname4064 /* index: 4064 */
	.weak sys_coredump; .long sys_coredump
	.reloc ., R_386_SIZE32, sys_coredump; .long 0
	.long 0x13b2fe0
	.long .Lname4065 /* index: 4065 */
	.weak memchrq; .long memchrq
	.reloc ., R_386_SIZE32, memchrq; .long 0
	.long 0x3c39fe1
	.long .Lname4066 /* index: 4066 */
	.weak keyboard_device_getchar; .long keyboard_device_getchar
	.reloc ., R_386_SIZE32, keyboard_device_getchar; .long 0
	.long 0x4fc6fe2
	.long .Lname4067 /* index: 4067 */
	.weak mall_dump_leaks; .long mall_dump_leaks
	.reloc ., R_386_SIZE32, mall_dump_leaks; .long 0
	.long 0x7877fe3
	.long .Lname4068 /* index: 4068 */
	.weak fpustate_init; .long fpustate_init
	.reloc ., R_386_SIZE32, fpustate_init; .long 0
	.long 0x7e96fe4
	.long .Lname4069 /* index: 4069 */
	.weak vm_tasklock_downgrade; .long vm_tasklock_downgrade
	.reloc ., R_386_SIZE32, vm_tasklock_downgrade; .long 0
	.long 0xf072fe5
	.long .Lname4070 /* index: 4070 */
	.weak directory_getnode; .long directory_getnode
	.reloc ., R_386_SIZE32, directory_getnode; .long 0
	.long 0x718e245
	.long .Lname4071 /* index: 4071 */
	.weak memchrw; .long memchrw
	.reloc ., R_386_SIZE32, memchrw; .long 0
	.long 0x3c39fe7
	.long 0 /* index: 4072 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4073 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4074 */
	.long 0
	.long 0
	.long 0
	.long .Lname4075 /* index: 4075 */
	.weak sys_lfutexlock; .long sys_lfutexlock
	.reloc ., R_386_SIZE32, sys_lfutexlock; .long 0
	.long 0xa591feb
	.long 0 /* index: 4076 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4077 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4078 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4079 */
	.long 0
	.long 0
	.long 0
	.long .Lname4080 /* index: 4080 */
	.weak sys_kcmp; .long sys_kcmp
	.reloc ., R_386_SIZE32, sys_kcmp; .long 0
	.long 0x961ff0
	.long 0 /* index: 4081 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4082 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4083 */
	.long 0
	.long 0
	.long 0
	.long .Lname4084 /* index: 4084 */
	.weak _this_taskpid; .long _this_taskpid
	.reloc ., R_386_SIZE32, _this_taskpid; .long 0
	.long 0xc272ff4
	.long .Lname4085 /* index: 4085 */
	.weak syscall_trace; .long syscall_trace
	.reloc ., R_386_SIZE32, syscall_trace; .long 0
	.long 0xb621ff5
	.long 0 /* index: 4086 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4087 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4088 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4089 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4090 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4091 */
	.long 0
	.long 0
	.long 0
	.long .Lname4092 /* index: 4092 */
	.weak memchrl; .long memchrl
	.reloc ., R_386_SIZE32, memchrl; .long 0
	.long 0x3c39ffc
	.long 0 /* index: 4093 */
	.long 0
	.long 0
	.long 0
	.long 0 /* index: 4094 */
	.long 0
	.long 0
	.long 0
	.long .Lname4095 /* index: 4095 */
	.weak validate_readable; .long validate_readable
	.reloc ., R_386_SIZE32, validate_readable; .long 0
	.long 0x18c4d55
END(kernel_symbol_table)
.section .rodata.kernel_strtab
.Lname0:
	.string "cpu_apply_icpustate_esp"
.Lname2:
	.string "slab_malloc12"
.Lname3:
	.string "handle_get_datablock"
.Lname4:
	.string "regdump_gdt"
.Lname5:
	.string "cpu_apply_scpustate"
.Lname6:
	.string "slab_malloc16"
.Lname8:
	.string "aio_pbuffer_memset"
.Lname11:
	.string "inode_writek"
.Lname13:
	.string "handle_installinto_sym"
.Lname16:
	.string "directory_getentry_p"
.Lname19:
	.string "block_device_readv_sync"
.Lname21:
	.string "pidns_tryupgrade"
.Lname24:
	.string "cpu_quantum_length"
.Lname25:
	.string "sys_time64"
.Lname30:
	.string "devfs_lock_downgrade"
.Lname35:
	.string "qtime_to_timespec"
.Lname37:
	.string "vm_datablock_vio_write"
.Lname39:
	.string "fs_filesystems_lock_trywrite"
.Lname45:
	.string "vm_datapart_do_allocram"
.Lname48:
	.string "cpu_apply_scpustate_esp"
.Lname49:
	.string "dbg_fillrect"
.Lname51:
	.string "kernel_panic"
.Lname52:
	.string "page_ismapped"
.Lname55:
	.string "driver_local_symbol_at"
.Lname57:
	.string "path_umount"
.Lname60:
	.string "_this_sigmask"
.Lname63:
	.string "cpu_wake"
.Lname66:
	.string "cpu_delete_idle_job"
.Lname68:
	.string "unwind"
.Lname69:
	.string "lookup_pci_device"
.Lname75:
	.string "kernel_slab_break"
.Lname77:
	.string "vm_datapart_allocram"
.Lname78:
	.string "task_detach_children"
.Lname79:
	.string "block_device_read"
.Lname83:
	.string "fs_filesystems"
.Lname84:
	.string "sys_utimes64"
.Lname85:
	.string "sys_timer_delete"
.Lname89:
	.string "sys_setgid"
.Lname92:
	.string "error_as_signal"
.Lname94:
	.string "error_thrown"
.Lname95:
	.string "sys_ftruncate"
.Lname96:
	.string "strend"
.Lname97:
	.string "slab_malloc20"
.Lname99:
	.string "x86_cputss"
.Lname101:
	.string "aio_multihandle_done"
.Lname102:
	.string "dbg_screen_cellsize"
.Lname103:
	.string "dbg_setreg"
.Lname107:
	.string "vio_addw"
.Lname109:
	.string "error_register_state"
.Lname110:
	.string "vm_ramfile_type"
.Lname112:
	.string "handle_installhop"
.Lname115:
	.string "task_exec_asynchronous_srpc"
.Lname116:
	.string "driver_delmod"
.Lname117:
	.string "directory_creatfile"
.Lname118:
	.string "inode_writev"
.Lname119:
	.string "sys_select"
.Lname120:
	.string "character_device_lookup_nx"
.Lname121:
	.string "cpu_broadcastipi"
.Lname123:
	.string "sys_rt_sigprocmask"
.Lname124:
	.string "json_parser_init"
.Lname126:
	.string "task_rpc_exec_here_onexit"
.Lname127:
	.string "fs_filesystems_lock_endwrite"
.Lname130:
	.string "character_device_unregister"
.Lname131:
	.string "debug_dlunlocksections"
.Lname132:
	.string "sys_creat"
.Lname135:
	.string "vm_datapart_lockwrite_setcore_unsharecow"
.Lname149:
	.string "superblock_mountlock_endwrite"
.Lname152:
	.string "path_traversefull_ex"
.Lname153:
	.string "ttybase_device_iread"
.Lname159:
	.string "slab_ffree"
.Lname160:
	.string "regdump_gpregs"
.Lname162:
	.string "sys_renameat2"
.Lname163:
	.string "vm_datablock_lock_trywrite_parts"
.Lname164:
	.string "sys_modify_ldt"
.Lname166:
	.string "block_device_awritev"
.Lname167:
	.string "heap_realloc_untraced"
.Lname173:
	.string "_this_vm"
.Lname175:
	.string "sys_sched_getaffinity"
.Lname178:
	.string "task_setsessionleader"
.Lname179:
	.string "pagedir_unmap_userspace_nosync"
.Lname180:
	.string "pagedir_init"
.Lname181:
	.string "_bootidle"
.Lname184:
	.string "task_alloc_synchronous_rpc_nx"
.Lname185:
	.string "sys_mktty"
.Lname187:
	.string "sys_lseek"
.Lname188:
	.string "sys_tgkill"
.Lname190:
	.string "sys_ioprio_set"
.Lname191:
	.string "vm_datapart_read_unsafe"
.Lname192:
	.string "directory_readnext_p"
.Lname194:
	.string "kmalloc_noslab"
.Lname195:
	.string "aio_handle_generic_func"
.Lname196:
	.string "path_lock_endread"
.Lname197:
	.string "superblock_nodeslock_write"
.Lname201:
	.string "sys_setpriority"
.Lname204:
	.string "mempcpyl"
.Lname210:
	.string "kernel_pty_oprinter"
.Lname211:
	.string "inode_readall_phys"
.Lname212:
	.string "devfs_lock_end"
.Lname213:
	.string "sys_reboot"
.Lname214:
	.string "block_device_partition_readv"
.Lname215:
	.string "terminal_poll_owrite"
.Lname216:
	.string "superblock_nodeslock_write_nx"
.Lname217:
	.string "rwlock_read"
.Lname219:
	.string "sys_unlink"
.Lname223:
	.string "handle_get_inode"
.Lname227:
	.string "page_malloc"
.Lname229:
	.string "vmb_getfree"
.Lname233:
	.string "vio_addl"
.Lname237:
	.string "sys_geteuid32"
.Lname238:
	.string "unwind_fde_scan"
.Lname240:
	.string "pagedir_prepare_map_p"
.Lname241:
	.string "superblock_nodeslock_tryupgrade"
.Lname243:
	.string "heap_alloc"
.Lname244:
	.string "path_lock_tryread"
.Lname245:
	.string "vm_datapart_lock_write"
.Lname247:
	.string "debuginfo_cu_parser_skipattr"
.Lname248:
	.string "unicode_32to8"
.Lname249:
	.string "sys_settimeofday"
.Lname250:
	.string "x86_pagedir_syncone"
.Lname254:
	.string "vio_copytovio_from_phys"
.Lname255:
	.string "_Unwind_Resume"
.Lname260:
	.string "sys_select64"
.Lname261:
	.string "task_rpc_exec_here"
.Lname265:
	.string "vm_node_destroy"
.Lname270:
	.string "sys_open"
.Lname272:
	.string "handle_trylookup"
.Lname274:
	.string "rawmemrchr"
.Lname276:
	.string "vm_node_insert"
.Lname277:
	.string "cpu_apply_kcpustate"
.Lname280:
	.string "instruction_length"
.Lname281:
	.string "sys_faccessat"
.Lname282:
	.string "task_isconnected"
.Lname283:
	.string "sys_sigaltstack"
.Lname284:
	.string "ringbuffer_unread"
.Lname286:
	.string "rwlock_trywrite"
.Lname287:
	.string "kernel_terminal_check_sigttou"
.Lname292:
	.string "isr_register_greedy_at"
.Lname293:
	.string "driver_with_filename"
.Lname297:
	.string "json_writer_putnull"
.Lname302:
	.string "dbg_fillscreen"
.Lname303:
	.string "vm_datablock_anonymous_zero"
.Lname305:
	.string "mempcpyq"
.Lname306:
	.string "syscall_emulate_sysenter"
.Lname307:
	.string "vm_sync"
.Lname308:
	.string "x86_syscall_register_count"
.Lname309:
	.string "vm_datablock_physical_type"
.Lname311:
	.string "mempcpyw"
.Lname313:
	.string "vm_datapart_split"
.Lname314:
	.string "unwind_getreg_sfpustate"
.Lname315:
	.string "sys_fork"
.Lname317:
	.string "dbg_readline"
.Lname319:
	.string "page_iszero"
.Lname322:
	.string "character_device_register"
.Lname324:
	.string "syscall_tracing_getenabled"
.Lname327:
	.string "vio_xorw"
.Lname331:
	.string "page_malloc_at"
.Lname333:
	.string "vio_writeb"
.Lname338:
	.string "vio_xorb"
.Lname340:
	.string "sys_socket"
.Lname341:
	.string "inode_areadallv_phys"
.Lname342:
	.string "mouse_device_hwheel"
.Lname343:
	.string "vpage_free"
.Lname345:
	.string "devfs_lock_read"
.Lname348:
	.string "vio_xorl"
.Lname351:
	.string "vm_datapart_decref_and_merge"
.Lname355:
	.string "handle_get_vfs"
.Lname357:
	.string "task_serve"
.Lname359:
	.string "error_rethrow"
.Lname361:
	.string "unwind_cfa_sigframe_apply"
.Lname368:
	.string "vm_datapart_map_ram_autoprop"
.Lname370:
	.string "rawmemchr"
.Lname371:
	.string "task_pushconnections"
.Lname372:
	.string "block_device_write_sync"
.Lname373:
	.string "rwlock_write_aggressive"
.Lname375:
	.string "rwlock_tryread_readonly"
.Lname376:
	.string "heap_align_nx"
.Lname377:
	.string "sys_futimesat64"
.Lname380:
	.string "vm_datapart_lockread_setcore_nx"
.Lname383:
	.string "sys_close"
.Lname385:
	.string "pagedir_translate_p"
.Lname386:
	.string "vm_datapart_pageaddr"
.Lname387:
	.string "character_device_sync"
.Lname388:
	.string "sys_kstat"
.Lname390:
	.string "sys_process_vm_readv"
.Lname391:
	.string "kffree"
.Lname392:
	.string "heap_realign_nx"
.Lname393:
	.string "task_setup_kernel"
.Lname395:
	.string "x86_this_dfstack_part"
.Lname397:
	.string "sys_sched_getscheduler"
.Lname399:
	.string "vm_datapart_map_ram"
.Lname401:
	.string "regdump_icpustate"
.Lname403:
	.string "keymap_init_en_US"
.Lname405:
	.string "inode_datablock_type"
.Lname407:
	.string "ttybase_device_stat"
.Lname409:
	.string "krand"
.Lname411:
	.string "inode_awritek"
.Lname415:
	.string "block_device_aread_phys"
.Lname417:
	.string "rawmemrchrq"
.Lname418:
	.string "vm86_outb"
.Lname420:
	.string "swap_read"
.Lname421:
	.string "path_getcasechild_and_parent_inode"
.Lname422:
	.string "_this_library_listdef"
.Lname423:
	.string "rawmemrchrw"
.Lname424:
	.string "task_raisesignalthread_nx"
.Lname426:
	.string "regdump_sgregs_with_cs_ss_tr_ldt"
.Lname427:
	.string "vm_addhwbreak"
.Lname428:
	.string "sys_ioctl"
.Lname429:
	.string "vm_unmap_kernel_ram"
.Lname434:
	.string "block_device_awritev_sector"
.Lname435:
	.string "block_device_areadv_phys"
.Lname437:
	.string "vm_datablock_debugheap_type"
.Lname439:
	.string "vm86_outw"
.Lname440:
	.string "__predict_update_edx"
.Lname441:
	.string "dbg_trygetuni"
.Lname444:
	.string "rawmemrchrl"
.Lname447:
	.string "rwlock_downgrade"
.Lname448:
	.string "slab_kmalloc20"
.Lname450:
	.string "sys_setuid"
.Lname451:
	.string "sys_getgroups"
.Lname452:
	.string "json_parser_getfloat"
.Lname453:
	.string "pagedir_isuseraccessible"
.Lname455:
	.string "x86_vm86_outw"
.Lname456:
	.string "sys_futex"
.Lname458:
	.string "heap_alloc_untraced"
.Lname465:
	.string "rwlock_end"
.Lname466:
	.string "x86_vm86_outb"
.Lname467:
	.string "unwind_setreg_ucpustate"
.Lname468:
	.string "directory_readnext"
.Lname469:
	.string "_this_idle"
.Lname470:
	.string "disasm_print_line_nolf"
.Lname473:
	.string "lookup_taskpid"
.Lname476:
	.string "sys_iopl"
.Lname479:
	.string "vm_datapart_lock_tryupgrade"
.Lname480:
	.string "pagedir_iswritable_p"
.Lname481:
	.string "__asm32_syscallrouter_int80"
.Lname484:
	.string "sys_mkdirat"
.Lname485:
	.string "sys_unshare"
.Lname486:
	.string "inode_awritev"
.Lname488:
	.string "rwlock_upgrade_nx"
.Lname489:
	.string "character_device_destroy"
.Lname492:
	.string "ringbuffer_poll"
.Lname493:
	.string "cpu_enable_preemptive_interrupts_nopr"
.Lname495:
	.string "vm_datapart_freeram"
.Lname496:
	.string "regdump_gpregs_with_sp"
.Lname498:
	.string "sys_setuid32"
.Lname500:
	.string "dbg_editfield"
.Lname501:
	.string "mempmove"
.Lname505:
	.string "sys_mknod"
.Lname506:
	.string "inode_readallv_phys"
.Lname510:
	.string "unicode_readutf16_swap_n"
.Lname511:
	.string "ramfs_type"
.Lname514:
	.string "sys_chdir"
.Lname516:
	.string "regdump_idt"
.Lname517:
	.string "acpi_mode"
.Lname518:
	.string "vm_datablock_vio_writev"
.Lname519:
	.string "sys_sendmmsg"
.Lname522:
	.string "unicode_readutf16_n"
.Lname523:
	.string "inode_readk"
.Lname524:
	.string "disasm_print_until"
.Lname526:
	.string "cpu_idlemain"
.Lname528:
	.string "vm_datablock_writevp"
.Lname530:
	.string "dbg_getcur"
.Lname531:
	.string "inode_writev_phys"
.Lname532:
	.string "unwind_fde_exec_landing_pad_adjustment"
.Lname533:
	.string "cpu_apply_lcpustate"
.Lname534:
	.string "inode_readv"
.Lname535:
	.string "sys_recvmmsg"
.Lname536:
	.string "vm_datapart_lock_read_nx"
.Lname539:
	.string "__cpuset_full_mask"
.Lname543:
	.string "task_sleep_cputime"
.Lname546:
	.string "sys_linux_lstat32"
.Lname547:
	.string "inode_readv_phys"
.Lname548:
	.string "kernel_debugtraps_get"
.Lname549:
	.string "debuginfo_location_setvalue"
.Lname551:
	.string "cpu_assert_sleeping"
.Lname552:
	.string "vm_datapart_lock_write_nx"
.Lname553:
	.string "stack_avail"
.Lname554:
	.string "cpu_add_quantum_offset"
.Lname557:
	.string "__asm32_exsyscallrouter_sysenter"
.Lname559:
	.string "vm_kernel_treelock_tryread"
.Lname562:
	.string "vm_exec_assert_regular"
.Lname564:
	.string "cpu_quantum_elapsed"
.Lname565:
	.string "driver_getfilename"
.Lname566:
	.string "block_device_readv"
.Lname568:
	.string "callback_list_remove"
.Lname569:
	.string "handle_get_taskpid"
.Lname571:
	.string "aio_multihandle_cancel"
.Lname572:
	.string "ttybase_device_poll"
.Lname574:
	.string "blocking_cleanup_chain"
.Lname575:
	.string "kmalloc_usable_size"
.Lname576:
	.string "sys_debugtrap"
.Lname577:
	.string "vm_copyinphys"
.Lname578:
	.string "format_sprintf_printer"
.Lname580:
	.string "sys_setresuid"
.Lname581:
	.string "ramfs_dev_type"
.Lname582:
	.string "_ZSt9terminatev"
.Lname583:
	.string "validate_executable"
.Lname584:
	.string "kernel_debugtrap_on"
.Lname585:
	.string "pidns_destroy"
.Lname589:
	.string "x86_memcpy_nopf"
.Lname592:
	.string "_this_x86_dr0"
.Lname593:
	.string "fpustate_alloc_nx"
.Lname594:
	.string "_this_x86_dr2"
.Lname595:
	.string "inode_write_phys"
.Lname596:
	.string "pidns_endread"
.Lname597:
	.string "sys_olduname"
.Lname598:
	.string "sys_clock_settime64"
.Lname599:
	.string "_this_x86_dr7"
.Lname601:
	.string "json_parser_rewind"
.Lname605:
	.string "vm_node_update_write_access_locked_vm"
.Lname606:
	.string "task_alloc"
.Lname607:
	.string "memlen"
.Lname609:
	.string "sys_mremap"
.Lname610:
	.string "cpu_schedule_idle_job"
.Lname611:
	.string "sys_clock_getres"
.Lname612:
	.string "pidns_tryread"
.Lname613:
	.string "page_mallocone"
.Lname614:
	.string "block_device_writev"
.Lname615:
	.string "sys_utime"
.Lname619:
	.string "_this_task"
.Lname620:
	.string "sys_mlockall"
.Lname623:
	.string "validate_writable_opt"
.Lname627:
	.string "cpu_enable_preemptive_interrupts"
.Lname628:
	.string "cpu_run_current"
.Lname629:
	.string "vm_datablock_anonymous_zero_type"
.Lname630:
	.string "sys_kreaddirf"
.Lname633:
	.string "debuginfo_cu_parser_next"
.Lname634:
	.string "dbg_putuni"
.Lname639:
	.string "_this_fpustate"
.Lname640:
	.string "driver_symbol_at"
.Lname642:
	.string "sys_renameat"
.Lname643:
	.string "debuginfo_enum_locals"
.Lname644:
	.string "format_repeat"
.Lname648:
	.string "vm_kernel_treelock_write_nx"
.Lname657:
	.string "slab_kmalloc8"
.Lname661:
	.string "fs_filesystems_lock_upgrade"
.Lname663:
	.string "dbg_asmview"
.Lname665:
	.string "isr_vector_state_destroy"
.Lname666:
	.string "path_lock_tryupgrade"
.Lname671:
	.string "path_getchild_and_parent_inode"
.Lname672:
	.string "x86_fpustate_save"
.Lname675:
	.string "vm_datapart_readv_phys"
.Lname676:
	.string "validate_writablem_opt"
.Lname677:
	.string "directory_getcasenode"
.Lname678:
	.string "sys_preadvf"
.Lname679:
	.string "krealign_nx"
.Lname683:
	.string "handle_get_superblock"
.Lname687:
	.string "vm_onexec_callbacks"
.Lname688:
	.string "pagedir_unprepare_mapone_p"
.Lname690:
	.string "sys_getgid32"
.Lname691:
	.string "driver_finalized_callbacks"
.Lname692:
	.string "path_recent"
.Lname693:
	.string "pagedir_unwrite"
.Lname697:
	.string "driver_insmod"
.Lname702:
	.string "strlen"
.Lname704:
	.string "__gxx_personality_v0"
.Lname707:
	.string "task_deliver_rpc"
.Lname709:
	.string "isr_unregister_any"
.Lname711:
	.string "debuginfo_cu_parser_getflag"
.Lname712:
	.string "vm_startdmav_nx"
.Lname718:
	.string "memrlen"
.Lname721:
	.string "slab_kmalloc_nx12"
.Lname722:
	.string "sys_removexattr"
.Lname723:
	.string "inode_areadv_phys"
.Lname724:
	.string "vm_sync_locked"
.Lname732:
	.string "__predict_update_al"
.Lname734:
	.string "directory_entry_alloc_s"
.Lname738:
	.string "format_snprintf_printer"
.Lname739:
	.string "vfs_clearmounts"
.Lname740:
	.string "strto64"
.Lname741:
	.string "sys_timerfd_create"
.Lname742:
	.string "keymap_translate_buf"
.Lname743:
	.string "inode_read_blocking"
.Lname744:
	.string "strto32"
.Lname745:
	.string "driver_state_destroy"
.Lname747:
	.string "sys__llseek"
.Lname748:
	.string "dbg_enter_icpustate"
.Lname752:
	.string "pagedir_unsetchanged_p"
.Lname753:
	.string "devfs_lock_upgrade_nx"
.Lname755:
	.string "debug_dllocksections"
.Lname756:
	.string "sys_connect"
.Lname757:
	.string "symtab_scantable"
.Lname758:
	.string "memset_nopf"
.Lname759:
	.string "keyboard_buffer_getkey"
.Lname764:
	.string "x86_lapic_id"
.Lname766:
	.string "path_lock_write"
.Lname773:
	.string "x86_fxsave"
.Lname777:
	.string "block_device_destroy"
.Lname779:
	.string "x86_this_dfstack"
.Lname780:
	.string "task_disconnectall"
.Lname784:
	.string "sys_munmap"
.Lname786:
	.string "sigmask_getwr"
.Lname788:
	.string "instruction_trypred"
.Lname789:
	.string "fs_filesystems_remove"
.Lname792:
	.string "dbg_menuex"
.Lname793:
	.string "vm_set_aslr_disabled"
.Lname795:
	.string "path_lock"
.Lname798:
	.string "page_malloc_part_between"
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
.Lname811:
	.string "mall_validate_padding"
.Lname813:
	.string "validate_user"
.Lname818:
	.string "sys_mmap2"
.Lname819:
	.string "swap_malloc"
.Lname820:
	.string "krand_seed"
.Lname821:
	.string "driver_with_name"
.Lname825:
	.string "x86_syscall_is_cancellation_point"
.Lname827:
	.string "strcmp"
.Lname828:
	.string "sys_geteuid"
.Lname831:
	.string "stack_inuse"
.Lname835:
	.string "system_trimheaps"
.Lname836:
	.string "sys_open_by_handle_at"
.Lname837:
	.string "vm_datapart_lock_downgrade"
.Lname838:
	.string "sys_waitpid"
.Lname841:
	.string "handle_get_regular_node"
.Lname843:
	.string "sys_sched_get_priority_max"
.Lname845:
	.string "dbg_newline_mode"
.Lname848:
	.string "task_raisesignalprocessgroup"
.Lname851:
	.string "handle_manager_alloc"
.Lname852:
	.string "error_unwind"
.Lname862:
	.string "vm_tasklock_tryservice"
.Lname864:
	.string "task_sleep"
.Lname865:
	.string "vmb_node_remove"
.Lname867:
	.string "__x86_bootcpu_idfeatures"
.Lname868:
	.string "json_parser_getuint64"
.Lname869:
	.string "pagedir_mapone"
.Lname871:
	.string "vio_andw"
.Lname872:
	.string "dbg_messagebox"
.Lname873:
	.string "keyboard_device_trygetkey"
.Lname875:
	.string "sigmask_check"
.Lname876:
	.string "mouse_device_stat"
.Lname877:
	.string "task_setvm"
.Lname882:
	.string "vio_andb"
.Lname884:
	.string "vm_datapart_lock_read"
.Lname886:
	.string "dbg_vpprintf"
.Lname887:
	.string "vfs_kernel"
.Lname891:
	.string "driver_section_lock"
.Lname892:
	.string "vio_andl"
.Lname893:
	.string "inode_readallv"
.Lname894:
	.string "inode_chown"
.Lname895:
	.string "block_device_acquire_partlock_write"
.Lname896:
	.string "vm_map"
.Lname897:
	.string "memrendq"
.Lname899:
	.string "sys_fstatfs"
.Lname900:
	.string "vm_datablock_read"
.Lname901:
	.string "superblock_mountlock_trywrite"
.Lname903:
	.string "cpu_loadpending"
.Lname904:
	.string "path_traversenfull_ex"
.Lname905:
	.string "json_parser_findkey"
.Lname906:
	.string "cred_require_hwio"
.Lname908:
	.string "kernel_debugtraps_uninstall"
.Lname909:
	.string "sys_alarm"
.Lname911:
	.string "aio_pbuffer_copyfrommem"
.Lname915:
	.string "vio_copyfromvio_to_phys"
.Lname916:
	.string "sys_eventfd"
.Lname917:
	.string "vm_clone"
.Lname922:
	.string "sys_getitimer64"
.Lname923:
	.string "directory_link"
.Lname924:
	.string "memrendl"
.Lname927:
	.string "vm_node_remove"
.Lname930:
	.string "vm86_pic_intr"
.Lname931:
	.string "x86_lapic_base_address"
.Lname932:
	.string "x86_fpustate_load"
.Lname933:
	.string "terminal_poll_iwrite"
.Lname934:
	.string "sys_pwritev"
.Lname935:
	.string "cpu_assert_running"
.Lname937:
	.string "handle_manager_clone"
.Lname939:
	.string "_this_kernel_stack"
.Lname941:
	.string "x86_check_spurious_interrupt_PIC2"
.Lname942:
	.string "sys_ftime"
.Lname947:
	.string "vm86_exec"
.Lname948:
	.string "rwlock_endread"
.Lname949:
	.string "unwind_setreg_scpustate"
.Lname950:
	.string "vm_datablock_anonymous_type"
.Lname952:
	.string "vm_datapart_lock_endwrite"
.Lname957:
	.string "memmem"
.Lname959:
	.string "kernel_debugtrap_fcpustate"
.Lname963:
	.string "pty_master_alloc"
.Lname964:
	.string "acpi_root"
.Lname965:
	.string "unwind_setreg_sfpustate"
.Lname967:
	.string "sys_syslog"
.Lname968:
	.string "task_alloc_user_rpc_nx"
.Lname969:
	.string "sys_hopf"
.Lname971:
	.string "sys_recvmsg"
.Lname973:
	.string "fpustate_loadfrom"
.Lname974:
	.string "ringbuffer_setwritten"
.Lname979:
	.string "ringbuffer_write_nonblock_noalloc"
.Lname980:
	.string "slab_kmalloc_nx4"
.Lname982:
	.string "unicode_8to16"
.Lname983:
	.string "krealign_in_place"
.Lname984:
	.string "slab_kmalloc_nx8"
.Lname985:
	.string "directory_entry_destroy"
.Lname986:
	.string "page_malloc_part"
.Lname988:
	.string "driver_with_namel"
.Lname989:
	.string "memrchrw"
.Lname991:
	.string "debuginfo_cu_parser_loadattr_variable"
.Lname992:
	.string "debuginfo_print_value"
.Lname995:
	.string "vm_datapart_read_phys"
.Lname996:
	.string "isr_unregister_at"
.Lname997:
	.string "json_decode"
.Lname1000:
	.string "path_traversen_ex"
.Lname1003:
	.string "x86_pit_lock"
.Lname1005:
	.string "validate_userm"
.Lname1008:
	.string "vmb_map"
.Lname1010:
	.string "block_device_awrite_phys_sector"
.Lname1011:
	.string "sys_utimes"
.Lname1012:
	.string "sys_nanosleep64"
.Lname1013:
	.string "kernel_panic_kcpustate"
.Lname1016:
	.string "handle_get_path"
.Lname1017:
	.string "sys_name_to_handle_at"
.Lname1021:
	.string "sighand_ptr_lockwrite"
.Lname1023:
	.string "ringbuffer_unwrite"
.Lname1025:
	.string "memcmpq"
.Lname1027:
	.string "task_connect_ghost_c"
.Lname1028:
	.string "vm_syncall_locked"
.Lname1031:
	.string "memcmpw"
.Lname1032:
	.string "sys_rmdir"
.Lname1033:
	.string "sys_getsockopt"
.Lname1035:
	.string "x86_fxsave_mxcsr_mask"
.Lname1037:
	.string "task_waitfor"
.Lname1042:
	.string "keyboard_device_trygetchar"
.Lname1044:
	.string "symlink_node_load"
.Lname1049:
	.string "sys_linux_oldfstat"
.Lname1052:
	.string "memcmpl"
.Lname1053:
	.string "handle_get_vm"
.Lname1054:
	.string "terminal_flush_icanon"
.Lname1055:
	.string "sys_clock_settime"
.Lname1057:
	.string "vm_datablock_vio_writev_phys"
.Lname1059:
	.string "dbg_enter_lcpustate"
.Lname1061:
	.string "vm_kernel_treelock_trywrite"
.Lname1067:
	.string "sys_epoll_wait"
.Lname1068:
	.string "vmb_find_first_node_greater_equal"
.Lname1069:
	.string "kernel_driver"
.Lname1070:
	.string "driver_getsection"
.Lname1071:
	.string "handle_installinto"
.Lname1072:
	.string "acpi_lookup"
.Lname1073:
	.string "superblock_set_unmounted"
.Lname1074:
	.string "vpage_realloc"
.Lname1075:
	.string "vm_memsetphys"
.Lname1076:
	.string "sys_futimesat"
.Lname1077:
	.string "pagedir_unprepare_mapone"
.Lname1081:
	.string "pipe_destroy"
.Lname1087:
	.string "kfree"
.Lname1088:
	.string "syscall_emulate_int80"
.Lname1092:
	.string "sys_setresgid"
.Lname1093:
	.string "vm_mapat_subrange"
.Lname1096:
	.string "path_printentex"
.Lname1098:
	.string "sys_setresuid32"
.Lname1099:
	.string "sys_exit"
.Lname1100:
	.string "vm_find_last_node_lower_equal"
.Lname1104:
	.string "vm_unmap"
.Lname1106:
	.string "_this_user_except_handler"
.Lname1107:
	.string "task_schedule_user_srpc"
.Lname1109:
	.string "sys_timer_create"
.Lname1113:
	.string "handle_get_superblock_relaxed"
.Lname1116:
	.string "vmb_find_last_node_lower_equal"
.Lname1118:
	.string "heap_align"
.Lname1119:
	.string "aio_multihandle_extension_destroy"
.Lname1122:
	.string "sys_readdir"
.Lname1123:
	.string "task_alloc_user_srpc"
.Lname1125:
	.string "driver_clear_fde_cache"
.Lname1129:
	.string "keyboard_buffer_trygetkey"
.Lname1131:
	.string "userkern_segment_block"
.Lname1132:
	.string "handle_manager_kernel"
.Lname1133:
	.string "pipe_writer_create"
.Lname1139:
	.string "task_redirect_usercode_rpc"
.Lname1140:
	.string "dbg_impersonate_thread"
.Lname1144:
	.string "block_device_sync"
.Lname1145:
	.string "sys_acct"
.Lname1146:
	.string "page_cfree"
.Lname1148:
	.string "memset"
.Lname1151:
	.string "pipe_create"
.Lname1152:
	.string "pagedir_maphintone_p"
.Lname1156:
	.string "dbg_indent"
.Lname1157:
	.string "vm_datapart_lock_trywrite"
.Lname1159:
	.string "regdump_gpreg"
.Lname1161:
	.string "tty_device_poll"
.Lname1168:
	.string "pagedir_prepare_map"
.Lname1171:
	.string "error_subclass"
.Lname1172:
	.string "sys_setpgid"
.Lname1173:
	.string "vm_kernel_treelock_tryupgrade"
.Lname1174:
	.string "isr_usage_of"
.Lname1176:
	.string "mall_trace_nx"
.Lname1177:
	.string "oneshot_directory_file_destroy"
.Lname1178:
	.string "unicode_16to32"
.Lname1181:
	.string "pidns_tryservice"
.Lname1183:
	.string "vm_free"
.Lname1186:
	.string "dbg_isholding_ctrl"
.Lname1187:
	.string "cpu_jiffies"
.Lname1188:
	.string "sys_getpgid"
.Lname1189:
	.string "dbg_vprintf"
.Lname1191:
	.string "instruction_succ"
.Lname1192:
	.string "superblock_mountlock_upgrade_nx"
.Lname1193:
	.string "json_writer_endarray"
.Lname1195:
	.string "inode_readallk"
.Lname1196:
	.string "rawmemlenl"
.Lname1198:
	.string "page_malloc_between"
.Lname1200:
	.string "devfs_lock_tryupgrade"
.Lname1201:
	.string "rawmemlenq"
.Lname1204:
	.string "character_device_read"
.Lname1205:
	.string "regdump_kcpustate"
.Lname1206:
	.string "sigqueue_fini"
.Lname1207:
	.string "rawmemlenw"
.Lname1208:
	.string "superblock_nodeslock_upgrade_nx"
.Lname1209:
	.string "superblock_nodeslock_read"
.Lname1212:
	.string "vm_tasklock_tryread"
.Lname1214:
	.string "unicode_readutf8_rev_n"
.Lname1217:
	.string "memendq"
.Lname1219:
	.string "mzones"
.Lname1220:
	.string "sys_fchmod"
.Lname1221:
	.string "unwind_getreg_xfpustate"
.Lname1223:
	.string "memendw"
.Lname1227:
	.string "regdump_sreg"
.Lname1228:
	.string "__stack_chk_fail"
.Lname1229:
	.string "block_device_aread_sector"
.Lname1231:
	.string "minfo"
.Lname1235:
	.string "pty_slave_alloc"
.Lname1236:
	.string "sys_getuid32"
.Lname1237:
	.string "fpustate_savecpu"
.Lname1238:
	.string "vm_datapart_write_phys"
.Lname1239:
	.string "heap_free_untraced"
.Lname1240:
	.string "task_yield_nx"
.Lname1241:
	.string "cpu_assert_integrity"
.Lname1244:
	.string "memendl"
.Lname1245:
	.string "sys_mknodat"
.Lname1246:
	.string "vio_readl_aligned"
.Lname1247:
	.string "error_print_into"
.Lname1250:
	.string "handle_fcntl"
.Lname1252:
	.string "rwlock_pollread"
.Lname1255:
	.string "task_exec_asynchronous_rpc"
.Lname1258:
	.string "pidns_endwrite"
.Lname1260:
	.string "sys_signal"
.Lname1262:
	.string "sys_frealpathat"
.Lname1263:
	.string "pagedir_maphintone"
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
	.string "debuginfo_location_select"
.Lname1273:
	.string "path_traversefull_at"
.Lname1275:
	.string "vm_tasklock_write"
.Lname1280:
	.string "vm_datapart_freeswap"
.Lname1282:
	.string "sys_lfutexexpr"
.Lname1284:
	.string "path_freelist"
.Lname1285:
	.string "page_ccfree"
.Lname1287:
	.string "sys_epoll_create1"
.Lname1288:
	.string "heap_alloc_untraced_nx"
.Lname1292:
	.string "heap_validate"
.Lname1294:
	.string "sys_sigreturn"
.Lname1298:
	.string "vm_write_nopf"
.Lname1299:
	.string "vm_node_update_write_access"
.Lname1300:
	.string "task_setthread"
.Lname1302:
	.string "format_vprintf"
.Lname1305:
	.string "rwlock_tryread"
.Lname1308:
	.string "driver_local_symbol"
.Lname1310:
	.string "vm_datapart_do_write_phys"
.Lname1311:
	.string "kernel_panic_here"
.Lname1315:
	.string "aio_multihandle_allochandle"
.Lname1316:
	.string "cred_require_vmread"
.Lname1317:
	.string "block_device_write"
.Lname1318:
	.string "inode_pathconf"
.Lname1320:
	.string "task_raisesignalprocessgroup_nx"
.Lname1323:
	.string "memrendw"
.Lname1324:
	.string "sys_tkill"
.Lname1325:
	.string "vio_xchb"
.Lname1326:
	.string "cpu_addsleepingtask"
.Lname1331:
	.string "fs_filesystems_delblocks"
.Lname1332:
	.string "terminal_init"
.Lname1333:
	.string "sys_stime"
.Lname1334:
	.string "vm_memset_nopf"
.Lname1337:
	.string "pagedir_unsetchanged"
.Lname1340:
	.string "vm_find_first_node_greater_equal"
.Lname1342:
	.string "cpu_schedule_idle_job_simple"
.Lname1343:
	.string "cpu_quantum_time"
.Lname1345:
	.string "strnlen"
.Lname1346:
	.string "json_parser_enter"
.Lname1347:
	.string "sys_msync"
.Lname1348:
	.string "character_device_stat"
.Lname1349:
	.string "block_device_acquire_partlock_trywrite"
.Lname1353:
	.string "driver_getshdrs"
.Lname1356:
	.string "vm_sync_endall"
.Lname1357:
	.string "cpu_quantum_reset_nopr"
.Lname1359:
	.string "validate_writablem"
.Lname1360:
	.string "kernel_locked_heap"
.Lname1361:
	.string "vm_datapart_allocram_nx"
.Lname1362:
	.string "_this_sighand_ptr"
.Lname1363:
	.string "directory_entry_alloc"
.Lname1364:
	.string "sys_utimensat"
.Lname1365:
	.string "keymap_codesize"
.Lname1370:
	.string "sys_timer_settime"
.Lname1371:
	.string "kernel_debugtrap_scpustate"
.Lname1374:
	.string "path_traversen"
.Lname1376:
	.string "unicode_readutf16_swap"
.Lname1378:
	.string "sys_freadlinkat"
.Lname1380:
	.string "pagedir_ismapped"
.Lname1381:
	.string "vm_tasklock_upgrade"
.Lname1385:
	.string "pagedir_syncall"
.Lname1386:
	.string "disasm_default_maxbytes"
.Lname1389:
	.string "sys_fchdir"
.Lname1393:
	.string "vpage_alloc_nx"
.Lname1395:
	.string "vm_datapart_writev_phys"
.Lname1401:
	.string "vm_syncone_locked"
.Lname1403:
	.string "mouse_device_moveto"
.Lname1404:
	.string "driver_symbol"
.Lname1409:
	.string "unwind_setreg_lcpustate"
.Lname1411:
	.string "fs_alloc"
.Lname1412:
	.string "devfs_lock_tryread"
.Lname1413:
	.string "superblock_mountlock_tryservice"
.Lname1416:
	.string "__cxa_end_catch"
.Lname1421:
	.string "path_traversenfull_at"
.Lname1423:
	.string "sys_rt_sigqueueinfo"
.Lname1426:
	.string "vm_datapart_write_buffered"
.Lname1427:
	.string "vm_datapart_do_read_phys"
.Lname1428:
	.string "acpi_sdt_count"
.Lname1429:
	.string "superblock_nodeslock_tryservice"
.Lname1430:
	.string "keyboard_device_getkey"
.Lname1431:
	.string "pipe_writer_destroy"
.Lname1432:
	.string "vpage_realloc_untraced_nx"
.Lname1436:
	.string "inode_readv_blocking"
.Lname1439:
	.string "terminal_iwrite"
.Lname1442:
	.string "json_writer_putnumber"
.Lname1443:
	.string "sys_umask"
.Lname1444:
	.string "json_parser_yield"
.Lname1445:
	.string "cred_require_vmwrite"
.Lname1446:
	.string "sys_writevf"
.Lname1447:
	.string "unwind_fde_exec_cfa"
.Lname1448:
	.string "path_traverse_ex"
.Lname1449:
	.string "pagedir_kernel"
.Lname1450:
	.string "task_exit"
.Lname1451:
	.string "printk"
.Lname1453:
	.string "validate_readablem"
.Lname1456:
	.string "vm_datapart_map_ram_p"
.Lname1458:
	.string "pci_writeaddr"
.Lname1460:
	.string "ansitty_init"
.Lname1461:
	.string "unwind_getreg_icpustate"
.Lname1465:
	.string "json_writer_addfield"
.Lname1467:
	.string "userkern_segment_vio"
.Lname1469:
	.string "rwlock_writing"
.Lname1471:
	.string "kernel_debugtrap_kcpustate"
.Lname1474:
	.string "mouse_buffer_putpacket_nopr"
.Lname1475:
	.string "sys_setgroups"
.Lname1477:
	.string "pagedir_unmapone"
.Lname1485:
	.string "cpu_disable_preemptive_interrupts_nopr"
.Lname1489:
	.string "directory_entry_hash"
.Lname1490:
	.string "inode_recent_tryclear"
.Lname1491:
	.string "handle_manager_cloexec"
.Lname1493:
	.string "driver_delmod_inode"
.Lname1494:
	.string "format_scanf"
.Lname1495:
	.string "sys_gettimeofday"
.Lname1496:
	.string "pidns_write_nx"
.Lname1497:
	.string "cpu_online_count"
.Lname1498:
	.string "sys_hop"
.Lname1499:
	.string "vprintk"
.Lname1500:
	.string "vm_datablock_physical"
.Lname1503:
	.string "inode_recent_tryremove"
.Lname1504:
	.string "sys_clock_nanosleep"
.Lname1506:
	.string "block_device_aread_phys_sector"
.Lname1508:
	.string "path_traverse_at"
.Lname1512:
	.string "dbg_enter_kcpustate"
.Lname1513:
	.string "directory_getentry"
.Lname1514:
	.string "debuginfo_location_getvalue"
.Lname1517:
	.string "driver_insmod_blob"
.Lname1523:
	.string "task_schedule_synchronous_rpc"
.Lname1524:
	.string "vm_datablock_locatepart"
.Lname1525:
	.string "mall_untrace"
.Lname1527:
	.string "debuginfo_cu_parser_getstring"
.Lname1528:
	.string "superblock_nodeslock_read_nx"
.Lname1529:
	.string "pagedir_fini"
.Lname1531:
	.string "block_device_writev_sync"
.Lname1532:
	.string "x86_pagedir_syncall_maybe_global"
.Lname1534:
	.string "x86_memcpy_nopf_ret_pointer"
.Lname1535:
	.string "vm_datapart_loadpage"
.Lname1536:
	.string "cred_require_mount"
.Lname1537:
	.string "x86_pagedir_sync"
.Lname1540:
	.string "pidns_trylookup_task_locked"
.Lname1541:
	.string "heap_free"
.Lname1544:
	.string "mouse_device_button_ex"
.Lname1547:
	.string "vm_enumdma_nx"
.Lname1549:
	.string "task_schedule_asynchronous_rpc"
.Lname1550:
	.string "unicode_readutf16_rev_n"
.Lname1551:
	.string "vio_copyfromvio"
.Lname1554:
	.string "block_device_unregister"
.Lname1555:
	.string "x86_spurious_interrupts"
.Lname1557:
	.string "syscall_printtrace"
.Lname1558:
	.string "sys_setreuid"
.Lname1561:
	.string "mouse_buffer_getpacket"
.Lname1564:
	.string "sys_socketcall"
.Lname1566:
	.string "x86_fpustate_init"
.Lname1567:
	.string "task_start"
.Lname1568:
	.string "inode_recent"
.Lname1570:
	.string "vm_datablock_write"
.Lname1571:
	.string "driver_clear_fde_caches"
.Lname1572:
	.string "block_device_acquire_partlock_tryread"
.Lname1576:
	.string "vm_enumdmav_nx"
.Lname1580:
	.string "task_yield"
.Lname1581:
	.string "block_device_awrite_sector"
.Lname1584:
	.string "json_writer_putfloat"
.Lname1586:
	.string "sys_socketpair"
.Lname1587:
	.string "_this_fs"
.Lname1588:
	.string "vm_datablock_findchanged"
.Lname1589:
	.string "sys_clock_gettime"
.Lname1592:
	.string "dbg_fillbox"
.Lname1593:
	.string "sys_readahead"
.Lname1596:
	.string "character_device_ioctl"
.Lname1599:
	.string "unwind_getreg_scpustate"
.Lname1604:
	.string "sys_getresuid"
.Lname1605:
	.string "error_active"
.Lname1606:
	.string "vm_enumdmav"
.Lname1607:
	.string "rawmemrlenq"
.Lname1608:
	.string "vm_tasklock_read"
.Lname1612:
	.string "mouse_device_poll"
.Lname1613:
	.string "heap_trim"
.Lname1614:
	.string "sys_lchown"
.Lname1618:
	.string "sys_fsetxattr"
.Lname1619:
	.string "task_push_asynchronous_srpc"
.Lname1621:
	.string "sys_oldolduname"
.Lname1624:
	.string "dbg_autocomplete_command"
.Lname1625:
	.string "sys_getpid"
.Lname1626:
	.string "dbg_getfunc"
.Lname1628:
	.string "terminal_owrite"
.Lname1633:
	.string "cpu_deepsleep"
.Lname1634:
	.string "sys_lfutexlockexpr"
.Lname1636:
	.string "cpu_quantum_end"
.Lname1639:
	.string "rawmemrlenw"
.Lname1648:
	.string "inode_awritev_phys"
.Lname1651:
	.string "krealloc"
.Lname1652:
	.string "x86_cpugdt"
.Lname1656:
	.string "krealloc_in_place_nx"
.Lname1657:
	.string "handle_manager_destroy"
.Lname1660:
	.string "rawmemrlenl"
.Lname1661:
	.string "dbg_enter_fcpustate"
.Lname1662:
	.string "swap_malloc_part"
.Lname1663:
	.string "krealloc_in_place"
.Lname1667:
	.string "vpage_alloc"
.Lname1668:
	.string "sys_truncate64"
.Lname1669:
	.string "inode_chtime"
.Lname1672:
	.string "path_lock_upgrade_nx"
.Lname1676:
	.string "sys_epoll_ctl"
.Lname1678:
	.string "keymap_instrlen"
.Lname1683:
	.string "swap_sync"
.Lname1684:
	.string "inode_changed"
.Lname1685:
	.string "json_parser_state"
.Lname1688:
	.string "sys_utime64"
.Lname1689:
	.string "vm_datapart_lock_end"
.Lname1695:
	.string "superblock_mountlock_downgrade"
.Lname1698:
	.string "debuginfo_cu_parser_loadattr_member"
.Lname1701:
	.string "path_freesize"
.Lname1707:
	.string "symlink_node_readlink"
.Lname1708:
	.string "task_alloc_user_rpc"
.Lname1711:
	.string "mouse_device_vwheel"
.Lname1712:
	.string "slab_kmalloc12"
.Lname1715:
	.string "superblock_clear_caches"
.Lname1716:
	.string "path_sprint"
.Lname1717:
	.string "unwind_getreg_fcpustate"
.Lname1718:
	.string "debuginfo_cu_parser_getref"
.Lname1721:
	.string "sys_frenameat"
.Lname1730:
	.string "keyboard_buffer_putkey_nopr"
.Lname1731:
	.string "handle_get_task"
.Lname1732:
	.string "rwlock_write"
.Lname1733:
	.string "driver_initialize"
.Lname1742:
	.string "sys_fchownat"
.Lname1743:
	.string "sys_timer_settime64"
.Lname1746:
	.string "x86_memcpy_nopf_rep_pointer"
.Lname1747:
	.string "slab_malloc"
.Lname1748:
	.string "dbg_print"
.Lname1749:
	.string "sys_sched_setscheduler"
.Lname1755:
	.string "syscall_emulate"
.Lname1759:
	.string "character_device_pwrite"
.Lname1762:
	.string "sys_set_exception_handler"
.Lname1764:
	.string "sys_clock_getres64"
.Lname1765:
	.string "coredump_create"
.Lname1766:
	.string "regdump_dr6"
.Lname1767:
	.string "regdump_dr7"
.Lname1772:
	.string "sys_truncate"
.Lname1774:
	.string "vm86_outl"
.Lname1775:
	.string "vio_copytovio"
.Lname1776:
	.string "cpu_quantum_remaining_nopr"
.Lname1778:
	.string "vio_orb"
.Lname1779:
	.string "aio_pbuffer_copytophys"
.Lname1780:
	.string "sys_ppoll64"
.Lname1781:
	.string "vm_datapart_lockwrite_setcore"
.Lname1785:
	.string "pidns_root"
.Lname1787:
	.string "unwind_emulator_exec_autostack"
.Lname1788:
	.string "vio_orl"
.Lname1795:
	.string "handle_get_fs"
.Lname1796:
	.string "callback_list_insert"
.Lname1797:
	.string "sys_ptrace"
.Lname1800:
	.string "sys_detach"
.Lname1801:
	.string "dbg_ungetkey"
.Lname1802:
	.string "superblock_mountlock_write"
.Lname1809:
	.string "vio_cmpxch_or_writew"
.Lname1810:
	.string "sys_fgetxattr"
.Lname1811:
	.string "system_clearcaches_s"
.Lname1812:
	.string "sig_altsend"
.Lname1813:
	.string "superblock_nodeslock_endread"
.Lname1816:
	.string "aio_multihandle_allochandle_nx"
.Lname1817:
	.string "sys_recvmmsg64"
.Lname1819:
	.string "pidns_write"
.Lname1820:
	.string "sys_setfsgid"
.Lname1826:
	.string "_this_handle_manager"
.Lname1827:
	.string "tty_device_alloc"
.Lname1828:
	.string "task_raisesignalthread"
.Lname1829:
	.string "vm_sync_endone"
.Lname1830:
	.string "sys_preadv"
.Lname1831:
	.string "error_data"
.Lname1832:
	.string "slab_kmalloc16"
.Lname1833:
	.string "dbg_pputuni"
.Lname1835:
	.string "vm_delhwbreak"
.Lname1842:
	.string "x86_fxrstor"
.Lname1843:
	.string "task_popconnections"
.Lname1844:
	.string "x86_fpustate_save_noreset"
.Lname1845:
	.string "vm_kernel_treelock_endwrite"
.Lname1846:
	.string "vm_datablock_vio_readv"
.Lname1847:
	.string "ttybase_device_setctty"
.Lname1849:
	.string "path_destroy"
.Lname1851:
	.string "ringbuffer_wseek"
.Lname1854:
	.string "sys_rt_sigaction"
.Lname1855:
	.string "ramfs_directory_type"
.Lname1857:
	.string "pagedir_ismapped_p"
.Lname1858:
	.string "sys_lchown32"
.Lname1860:
	.string "path_sprintent"
.Lname1861:
	.string "fs_filesystems_lock_tryupgrade"
.Lname1865:
	.string "sys_symlink"
.Lname1868:
	.string "keyboard_device_poll"
.Lname1869:
	.string "mouse_device_button_nopr"
.Lname1872:
	.string "pidns_lookup"
.Lname1875:
	.string "inode_aread_phys"
.Lname1876:
	.string "x86_idt_start"
.Lname1881:
	.string "vm_datablock_read_buffered"
.Lname1884:
	.string "coredump_create_for_signal"
.Lname1886:
	.string "driver_get_state"
.Lname1887:
	.string "json_encode"
.Lname1890:
	.string "superblock_opennode"
.Lname1891:
	.string "task_waitfor_norpc"
.Lname1892:
	.string "vm_tasklock_end"
.Lname1896:
	.string "superblock_mountlock_read_nx"
.Lname1900:
	.string "rawmemchrl"
.Lname1905:
	.string "rawmemchrq"
.Lname1908:
	.string "cpu_quantum_offset"
.Lname1909:
	.string "vm_write"
.Lname1911:
	.string "rawmemchrw"
.Lname1913:
	.string "sys_maplibrary"
.Lname1916:
	.string "kmemalign_nx"
.Lname1919:
	.string "task_wake"
.Lname1922:
	.string "sys_setgroups32"
.Lname1925:
	.string "debuginfo_cu_parser_loadattr_inlined_subroutine"
.Lname1929:
	.string "vm_mapat"
.Lname1932:
	.string "memcpyl"
.Lname1933:
	.string "devfs_insert"
.Lname1937:
	.string "sprintf_s"
.Lname1939:
	.string "task_raisesignalprocess"
.Lname1940:
	.string "sys_setitimer64"
.Lname1941:
	.string "block_device_lookup_name"
.Lname1942:
	.string "vm_getnodeof"
.Lname1945:
	.string "vm_datablock_destroy"
.Lname1946:
	.string "sys_getpriority"
.Lname1947:
	.string "sys_getrlimit"
.Lname1948:
	.string "__afail"
.Lname1950:
	.string "sys_sched_get_priority_min"
.Lname1951:
	.string "sys_vmsplice"
.Lname1952:
	.string "sys_vhangup"
.Lname1954:
	.string "dbg_printer"
.Lname1955:
	.string "sys_flock"
.Lname1956:
	.string "sigmask_check_after_except"
.Lname1957:
	.string "kernel_debugtrap_r_kcpustate"
.Lname1961:
	.string "_this_x86_dr3"
.Lname1963:
	.string "vm_sync_end"
.Lname1966:
	.string "sighand_default_action"
.Lname1970:
	.string "unicode_8to32"
.Lname1971:
	.string "aio_pbuffer_copyfromphys"
.Lname1973:
	.string "regdump_lcpustate"
.Lname1975:
	.string "vpage_ffree"
.Lname1977:
	.string "handle_lookup"
.Lname1983:
	.string "kernel_debugtrap_lcpustate"
.Lname1984:
	.string "vm86_step"
.Lname1987:
	.string "terminal_setios"
.Lname1988:
	.string "pci_list"
.Lname1989:
	.string "block_device_partition_write"
.Lname1993:
	.string "krealloc_nx"
.Lname1994:
	.string "fs_filesystems_lock_read"
.Lname1998:
	.string "sys_swapon"
.Lname2001:
	.string "vm_library_enumerate"
.Lname2003:
	.string "dbg_exitstate"
.Lname2004:
	.string "unwind_fde_find"
.Lname2005:
	.string "ramfs_regular_type"
.Lname2008:
	.string "kmalloc_nx"
.Lname2012:
	.string "x86_vm86_outl"
.Lname2014:
	.string "sys_sigaction"
.Lname2015:
	.string "register_filesystem_type"
.Lname2016:
	.string "sys_wait4"
.Lname2018:
	.string "sys_getresuid32"
.Lname2019:
	.string "superblock_sync"
.Lname2020:
	.string "regdump_cr4"
.Lname2021:
	.string "pci_getclassname"
.Lname2022:
	.string "vmb_getnodeof"
.Lname2024:
	.string "sys_mount"
.Lname2027:
	.string "pidns_lookup_task"
.Lname2031:
	.string "swap_free"
.Lname2036:
	.string "inode_chmod"
.Lname2041:
	.string "debuginfo_cu_parser_loadunit"
.Lname2046:
	.string "superblock_nodeslock_upgrade"
.Lname2048:
	.string "sys_getresgid"
.Lname2049:
	.string "vm_kernel_treelock_read"
.Lname2051:
	.string "regdump_sgregs"
.Lname2052:
	.string "handle_typekind"
.Lname2053:
	.string "block_device_awrite"
.Lname2054:
	.string "vsnprintf"
.Lname2057:
	.string "inode_areadall"
.Lname2060:
	.string "x86_fpustate_variant"
.Lname2068:
	.string "keyboard_device_read"
.Lname2069:
	.string "debuginfo_cu_parser_loadattr_type"
.Lname2071:
	.string "sys_sigpending"
.Lname2072:
	.string "heap_realign_untraced_nx"
.Lname2073:
	.string "block_device_partition_read"
.Lname2076:
	.string "json_parser_getbool"
.Lname2077:
	.string "aio_pbuffer_copytomem"
.Lname2079:
	.string "sys_fcntl64"
.Lname2080:
	.string "vm_datablock_writep"
.Lname2082:
	.string "handle_type_db"
.Lname2083:
	.string "handle_lookup_nosym"
.Lname2084:
	.string "memeq_ku_nopf"
.Lname2085:
	.string "sys_nice"
.Lname2086:
	.string "vm_datablock_writev"
.Lname2087:
	.string "driver_fde_find"
.Lname2091:
	.string "vsprintf"
.Lname2098:
	.string "sys_chown32"
.Lname2101:
	.string "_this_trampoline_page"
.Lname2102:
	.string "regdump_drregs"
.Lname2104:
	.string "format_width"
.Lname2105:
	.string "ttybase_device_cinit"
.Lname2109:
	.string "sys_fchdirat"
.Lname2110:
	.string "mall_untrace_n"
.Lname2111:
	.string "regdump_ucpustate"
.Lname2112:
	.string "superblock_mountlock_tryread"
.Lname2114:
	.string "isr_unregister"
.Lname2115:
	.string "dump_branch_stats"
.Lname2116:
	.string "json_writer_putint64"
.Lname2117:
	.string "kernel_vpanic_icpustate"
.Lname2124:
	.string "ansitty_device_ioctl"
.Lname2128:
	.string "pagedir_maphint_p"
.Lname2129:
	.string "task_alloc_synchronous_rpc"
.Lname2130:
	.string "sys_lsetxattr"
.Lname2131:
	.string "task_connect"
.Lname2132:
	.string "sys_clock_nanosleep64"
.Lname2133:
	.string "sys_getpeername"
.Lname2135:
	.string "sys_stime64"
.Lname2137:
	.string "sys_getsid"
.Lname2142:
	.string "path_lock_trywrite"
.Lname2143:
	.string "format_escape"
.Lname2148:
	.string "keyboard_device_init"
.Lname2151:
	.string "handle_installxchg"
.Lname2159:
	.string "_strtoui64"
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
.Lname2168:
	.string "krealign_in_place_offset_nx"
.Lname2169:
	.string "ringbuffer_skipread"
.Lname2173:
	.string "sys_sched_setparam"
.Lname2176:
	.string "ttybase_device_owrite"
.Lname2177:
	.string "sys_getuid"
.Lname2178:
	.string "inode_loadattr"
.Lname2179:
	.string "kernel_vpanic"
.Lname2180:
	.string "vm_get_aslr_disabled"
.Lname2187:
	.string "vm_clrhwbreak"
.Lname2188:
	.string "disasm_print_symbol"
.Lname2189:
	.string "block_device_areadv_phys_sector"
.Lname2192:
	.string "vm_datablock_readp"
.Lname2194:
	.string "directory_mkdir"
.Lname2195:
	.string "aio_buffer_copytophys"
.Lname2196:
	.string "terminal_iread"
.Lname2197:
	.string "sys_getsockname"
.Lname2198:
	.string "vm_datablock_readv"
.Lname2199:
	.string "sys_clock_gettime64"
.Lname2200:
	.string "task_schedule_user_rpc_nx"
.Lname2201:
	.string "sig_altbroadcast"
.Lname2204:
	.string "dbg_vline"
.Lname2205:
	.string "disasm"
.Lname2207:
	.string "dbg_hline"
.Lname2208:
	.string "pagedir_haschanged_p"
.Lname2209:
	.string "memrchrq"
.Lname2211:
	.string "kernel_debug_sections"
.Lname2212:
	.string "sys_linux_fstatat64"
.Lname2213:
	.string "sys_rename"
.Lname2215:
	.string "dbg_trygetc"
.Lname2220:
	.string "json_writer_putbool"
.Lname2223:
	.string "path_lock_end"
.Lname2227:
	.string "vm_datablock_sync"
.Lname2229:
	.string "linebuffer_writesome"
.Lname2231:
	.string "rwlock_reading"
.Lname2233:
	.string "x86_cpuldt"
.Lname2235:
	.string "directory_rename"
.Lname2236:
	.string "memrchrl"
.Lname2239:
	.string "pidns_trywrite"
.Lname2241:
	.string "mempatq"
.Lname2242:
	.string "sys_listxattr"
.Lname2243:
	.string "sys_times"
.Lname2244:
	.string "vm_protect"
.Lname2245:
	.string "vm_tasklock_endread"
.Lname2246:
	.string "dbg_pprintf"
.Lname2247:
	.string "mempatw"
.Lname2248:
	.string "heap_allat_untraced_nx"
.Lname2251:
	.string "mouse_buffer_trygetpacket"
.Lname2253:
	.string "keymap_translate"
.Lname2257:
	.string "heap_alloc_nx"
.Lname2259:
	.string "unicode_32to16"
.Lname2261:
	.string "ringbuffer_writesome"
.Lname2262:
	.string "unicode_readutf16_swap_rev"
.Lname2264:
	.string "dbg_screen_width"
.Lname2268:
	.string "mempatl"
.Lname2270:
	.string "sys_ioprio_get"
.Lname2271:
	.string "handle_datasize"
.Lname2274:
	.string "keymap_openblob"
.Lname2275:
	.string "inode_read_phys"
.Lname2277:
	.string "blocking_cleanup_prioritize"
.Lname2280:
	.string "unicode_readutf8"
.Lname2284:
	.string "kernel_debugtraps_install"
.Lname2285:
	.string "dbg_fillrect2"
.Lname2288:
	.string "pagedir_unmap"
.Lname2289:
	.string "sys_getegid"
.Lname2292:
	.string "path_print"
.Lname2293:
	.string "pagedir_push_mapone"
.Lname2302:
	.string "krealign"
.Lname2308:
	.string "heap_allat"
.Lname2310:
	.string "sys_process_vm_writev"
.Lname2312:
	.string "kmalloc_noslab_nx"
.Lname2313:
	.string "sighand_ptr_destroy"
.Lname2317:
	.string "vm_datapart_do_read"
.Lname2318:
	.string "sys_timer_getoverrun"
.Lname2319:
	.string "unwind_setreg_icpustate"
.Lname2322:
	.string "sys_lgetxattr"
.Lname2323:
	.string "keyboard_device_readchars"
.Lname2325:
	.string "inode_truncate"
.Lname2326:
	.string "dbg_addr2line_vprintf"
.Lname2327:
	.string "keyboard_device_putkey"
.Lname2328:
	.string "vm_kernel_treelock_writef_nx"
.Lname2329:
	.string "dbg_getkey"
.Lname2330:
	.string "vm_kernel_treelock_write"
.Lname2332:
	.string "sys_sched_rr_get_interval"
.Lname2333:
	.string "vm_futex_broadcast"
.Lname2334:
	.string "sys_chroot"
.Lname2336:
	.string "pagedir_isuseraccessible_p"
.Lname2337:
	.string "sys_mmap"
.Lname2339:
	.string "block_device_read_phys"
.Lname2340:
	.string "cpu_quantum_reset"
.Lname2341:
	.string "driver_insmod_file"
.Lname2342:
	.string "vm_startdmav"
.Lname2348:
	.string "fs_kernel"
.Lname2349:
	.string "json_parser_getnumber"
.Lname2350:
	.string "kernel_version"
.Lname2351:
	.string "inode_write"
.Lname2352:
	.string "vm_datablock_readvp"
.Lname2353:
	.string "__predict_update_eax"
.Lname2354:
	.string "sys_readlinkat"
.Lname2355:
	.string "sys_access"
.Lname2356:
	.string "sys_epoll_pwait"
.Lname2357:
	.string "boot_device"
.Lname2361:
	.string "memrend"
.Lname2367:
	.string "dbg_viewstate"
.Lname2368:
	.string "fs_filesystems_lock_write"
.Lname2370:
	.string "path_recent_clear"
.Lname2371:
	.string "sys_syncfs"
.Lname2372:
	.string "json_writer_endobject"
.Lname2373:
	.string "superblock_nodeslock_endwrite"
.Lname2379:
	.string "cpu_addpendingtask"
.Lname2380:
	.string "quantum_global_to_local"
.Lname2381:
	.string "vm_datapart_read_buffered"
.Lname2388:
	.string "sys_chmod"
.Lname2389:
	.string "devfs_lock_upgrade"
.Lname2391:
	.string "file_destroy"
.Lname2392:
	.string "vpage_alloc_untraced_nx"
.Lname2393:
	.string "sys_pwrite64"
.Lname2396:
	.string "ttybase_device_tryioctl"
.Lname2402:
	.string "inode_recent_clear"
.Lname2403:
	.string "block_device_read_sync"
.Lname2404:
	.string "sys_setsid"
.Lname2409:
	.string "path_newchild"
.Lname2411:
	.string "vio_orw"
.Lname2417:
	.string "memmove"
.Lname2419:
	.string "vm_datablock_vio_readv_phys"
.Lname2420:
	.string "block_device_acquire_partlock_read"
.Lname2424:
	.string "vpage_realloc_nx"
.Lname2425:
	.string "sys_timerfd_settime64"
.Lname2431:
	.string "vm_alloc"
.Lname2433:
	.string "linebuffer_write"
.Lname2434:
	.string "memrchr"
.Lname2435:
	.string "linebuffer_write_nonblock"
.Lname2437:
	.string "sys_time"
.Lname2439:
	.string "vm86_inw"
.Lname2440:
	.string "vm_kernel_treelock_upgrade_nx"
.Lname2442:
	.string "cpu_delsleepingtask"
.Lname2444:
	.string "vm_kernel"
.Lname2445:
	.string "isr_register"
.Lname2447:
	.string "sys_sendfile64"
.Lname2450:
	.string "vm86_inb"
.Lname2451:
	.string "ringbuffer_read"
.Lname2452:
	.string "vio_memset"
.Lname2455:
	.string "vmb_fini"
.Lname2457:
	.string "json_writer_beginarray"
.Lname2459:
	.string "directory_symlink"
.Lname2460:
	.string "sys_kill"
.Lname2463:
	.string "_this_sigqueue"
.Lname2464:
	.string "heap_realign_untraced"
.Lname2467:
	.string "block_device_write_phys_sync"
.Lname2468:
	.string "sys_settimeofday64"
.Lname2469:
	.string "vm_datapart_do_write"
.Lname2473:
	.string "vm86_inl"
.Lname2474:
	.string "error_class"
.Lname2475:
	.string "vpage_alloc_untraced"
.Lname2481:
	.string "vm_datapart_do_enumdma"
.Lname2482:
	.string "sys_eventfd2"
.Lname2483:
	.string "driver_loaded_callbacks"
.Lname2484:
	.string "mempset"
.Lname2485:
	.string "regdump_fcpustate"
.Lname2488:
	.string "krealign_offset_nx"
.Lname2489:
	.string "debuginfo_cu_abbrev_fini"
.Lname2493:
	.string "heap_validate_all"
.Lname2494:
	.string "heap_realign"
.Lname2499:
	.string "block_device_partition_writev_phys"
.Lname2500:
	.string "kmemalign_offset"
.Lname2501:
	.string "vm_tasklock_trywrite"
.Lname2504:
	.string "kmemalign_offset_nx"
.Lname2505:
	.string "kernel_debugtrap_r_ucpustate"
.Lname2510:
	.string "mouse_device_button"
.Lname2514:
	.string "vm86_sw_intr"
.Lname2515:
	.string "__x86_bootcpu_features"
.Lname2517:
	.string "debugaranges_locate"
.Lname2520:
	.string "inode_recent_clear_nx"
.Lname2521:
	.string "dbg_exit"
.Lname2526:
	.string "driver_getfile"
.Lname2527:
	.string "kernel_debugtrap_r_icpustate"
.Lname2528:
	.string "__asm32_exsyscallrouter_int80"
.Lname2530:
	.string "vm86_hw_intr"
.Lname2532:
	.string "keyboard_device_stat"
.Lname2533:
	.string "addr2line"
.Lname2534:
	.string "vm_datapart_writev"
.Lname2535:
	.string "unregister_filesystem_type"
.Lname2541:
	.string "inode_recent_getcur"
.Lname2546:
	.string "strchr"
.Lname2547:
	.string "unwind_emulator_exec"
.Lname2548:
	.string "sys_bind"
.Lname2549:
	.string "kernel_panic_ucpustate"
.Lname2555:
	.string "sys_link"
.Lname2556:
	.string "sys_linkat"
.Lname2562:
	.string "debuginfo_cu_parser_getaddr"
.Lname2563:
	.string "superblock_statfs"
.Lname2565:
	.string "serial_probe"
.Lname2566:
	.string "task_exec_asynchronous_rpc_v"
.Lname2568:
	.string "vm_datapart_do_allocram_nx"
.Lname2569:
	.string "mempcpy"
.Lname2571:
	.string "linebuffer_rewrite"
.Lname2574:
	.string "x86_rpc_user_redirection"
.Lname2575:
	.string "path_getchild_or_parent_inode"
.Lname2578:
	.string "krand_r"
.Lname2579:
	.string "keyboard_device_readkeys"
.Lname2580:
	.string "heap_align_untraced"
.Lname2581:
	.string "inode_awrite"
.Lname2582:
	.string "unicode_writeutf16"
.Lname2583:
	.string "ttybase_device_fini"
.Lname2584:
	.string "dbg_hasuni"
.Lname2585:
	.string "json_parser_next"
.Lname2587:
	.string "x86_rpc_redirection_iret"
.Lname2591:
	.string "sys_splice"
.Lname2592:
	.string "dbg_hexedit"
.Lname2596:
	.string "json_writer_beginobject"
.Lname2598:
	.string "vm_kernel_treelock_writef"
.Lname2601:
	.string "keyboard_device_ioctl"
.Lname2603:
	.string "debuginfo_cu_parser_loadattr_lexical_block"
.Lname2604:
	.string "sys_munlockall"
.Lname2606:
	.string "sys_listen"
.Lname2608:
	.string "sys_getdents"
.Lname2609:
	.string "driver_at_address"
.Lname2611:
	.string "task_schedule_user_rpc"
.Lname2612:
	.string "validate_readable_opt"
.Lname2613:
	.string "path_getcasechild_or_parent_inode"
.Lname2615:
	.string "dbg_getfunc_fuzzy"
.Lname2616:
	.string "debug_original_thread"
.Lname2617:
	.string "task_destroy"
.Lname2618:
	.string "unicode_readutf16_rev"
.Lname2619:
	.string "block_device_register_auto"
.Lname2620:
	.string "sys_sysctl"
.Lname2622:
	.string "rawmemlen"
.Lname2623:
	.string "pagedir_pop_mapone"
.Lname2624:
	.string "bcmp"
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
.Lname2637:
	.string "sys_setreuid32"
.Lname2638:
	.string "handle_lookupin"
.Lname2641:
	.string "vm_stopdma"
.Lname2642:
	.string "dbg_isholding_altgr"
.Lname2643:
	.string "task_connect_c"
.Lname2644:
	.string "sys_sched_rr_get_interval64"
.Lname2645:
	.string "sys_execve"
.Lname2646:
	.string "memeq_nopf"
.Lname2648:
	.string "sys_lfutex"
.Lname2651:
	.string "ringbuffer_read_nonblock"
.Lname2654:
	.string "rawmemrlen"
.Lname2655:
	.string "x86_exsyscall_restart_mode"
.Lname2656:
	.string "block_device_lookup"
.Lname2657:
	.string "vm_enumdma"
.Lname2660:
	.string "sys_gettid"
.Lname2661:
	.string "sys_getrusage"
.Lname2667:
	.string "sys_kreaddir"
.Lname2668:
	.string "json_parser_getnull"
.Lname2669:
	.string "vm_do_ffreeram"
.Lname2673:
	.string "sys_setgid32"
.Lname2674:
	.string "sys_setitimer"
.Lname2675:
	.string "vm_datablock_vio_read_phys"
.Lname2676:
	.string "debugline_scanunit"
.Lname2677:
	.string "superblock_nodeslock_trywrite"
.Lname2678:
	.string "__afailf"
.Lname2679:
	.string "cpu_hwipi_pending"
.Lname2681:
	.string "memcpy"
.Lname2682:
	.string "pagedir_isuserwritable"
.Lname2683:
	.string "cpu_delrunningtask"
.Lname2684:
	.string "pipe_reader_create"
.Lname2686:
	.string "vpage_free_untraced"
.Lname2687:
	.string "page_freeone"
.Lname2688:
	.string "pagedir_mapone_p"
.Lname2689:
	.string "sys_rpc_service"
.Lname2693:
	.string "cpu_ipi_service"
.Lname2694:
	.string "vm_datapart_readv"
.Lname2695:
	.string "x86_vm86_inw"
.Lname2696:
	.string "task_waitfor_norpc_nx"
.Lname2706:
	.string "x86_vm86_inb"
.Lname2707:
	.string "task_setprocess"
.Lname2708:
	.string "handle_installat"
.Lname2709:
	.string "x86_syscall_restart_mode"
.Lname2710:
	.string "sys_clone"
.Lname2711:
	.string "vio_writew"
.Lname2712:
	.string "task_schedule_user_srpc_nx"
.Lname2713:
	.string "tty_device_startfwd"
.Lname2715:
	.string "sys_shutdown"
.Lname2716:
	.string "x86_vm86_inl"
.Lname2717:
	.string "vm_tasklock_endwrite"
.Lname2719:
	.string "devfs_lock_write"
.Lname2720:
	.string "directory_getcaseentry_p"
.Lname2721:
	.string "x86_this_kernel_sp0"
.Lname2722:
	.string "vio_readb"
.Lname2723:
	.string "task_schedule_synchronous_srpc"
.Lname2724:
	.string "_this_kernel_stack_part"
.Lname2725:
	.string "path_lock_downgrade"
.Lname2728:
	.string "path_sprintentex"
.Lname2731:
	.string "cpu_addrunningtask"
.Lname2732:
	.string "vio_readl"
.Lname2733:
	.string "sys_setfsuid32"
.Lname2737:
	.string "driver_symbol_ex"
.Lname2739:
	.string "dbg_ungetc"
.Lname2740:
	.string "x86_fpu_current"
.Lname2741:
	.string "sys_sendfile"
.Lname2742:
	.string "sys_pwritevf"
.Lname2743:
	.string "vio_readw"
.Lname2752:
	.string "sys_ftruncate64"
.Lname2756:
	.string "directory_mknod"
.Lname2757:
	.string "sys_tee"
.Lname2759:
	.string "sys_rt_sigpending"
.Lname2761:
	.string "sighand_destroy"
.Lname2763:
	.string "sys_readlink"
.Lname2765:
	.string "vm_do_allocram"
.Lname2767:
	.string "sys_sync"
.Lname2768:
	.string "vm_kernel_syncall"
.Lname2769:
	.string "sys_getgid"
.Lname2770:
	.string "sys_getegid32"
.Lname2771:
	.string "unwind_fde_exec"
.Lname2772:
	.string "superblock_nodeslock_tryread"
.Lname2773:
	.string "debug_sections_addr2line"
.Lname2780:
	.string "path_traversenfull"
.Lname2783:
	.string "vm_syncone"
.Lname2784:
	.string "_this_taskgroup"
.Lname2785:
	.string "mouse_device_vwheel_nopr"
.Lname2786:
	.string "sys_get_exception_handler"
.Lname2787:
	.string "aio_buffer_copyfromphys"
.Lname2788:
	.string "sys_gettimeofday64"
.Lname2789:
	.string "sys_getcpu"
.Lname2791:
	.string "cpu_quantum_remaining"
.Lname2793:
	.string "x86_asm_except_personality"
.Lname2795:
	.string "isr_unregister_any_at"
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
	.string "_this_exception_info"
.Lname2810:
	.string "path_free"
.Lname2813:
	.string "vm_datapart_do_copyram"
.Lname2815:
	.string "rwlock_pollwrite"
.Lname2816:
	.string "pagedir_unprepare_map_p"
.Lname2818:
	.string "sighand_reset_handler"
.Lname2819:
	.string "vm_datablock_vio_write_phys"
.Lname2820:
	.string "vm_read"
.Lname2821:
	.string "__crt_unreachable"
.Lname2825:
	.string "cpu_sendipi"
.Lname2835:
	.string "inode_sync"
.Lname2836:
	.string "sys_symlinkat"
.Lname2837:
	.string "cpu_apply_ucpustate"
.Lname2840:
	.string "vm_startdma_nx"
.Lname2841:
	.string "unwind_cfa_apply"
.Lname2844:
	.string "ttybase_device_ioctl"
.Lname2850:
	.string "vio_readw_aligned"
.Lname2851:
	.string "block_device_writev_phys"
.Lname2852:
	.string "isr_register_at"
.Lname2853:
	.string "driver_with_file"
.Lname2856:
	.string "krealign_in_place_nx"
.Lname2857:
	.string "tty_device_forward_destroy"
.Lname2858:
	.string "vpage_realloc_untraced"
.Lname2866:
	.string "sys_linux_stat32"
.Lname2867:
	.string "slab_kmalloc"
.Lname2868:
	.string "vmb_node_insert"
.Lname2869:
	.string "sys_epoll_create"
.Lname2870:
	.string "json_parser_prev"
.Lname2873:
	.string "strtou64"
.Lname2875:
	.string "sys_rt_tgsigqueueinfo"
.Lname2876:
	.string "fs_filesystems_loadall"
.Lname2877:
	.string "sys_sched_getparam"
.Lname2878:
	.string "sys_setregid"
.Lname2879:
	.string "sys_sendto"
.Lname2880:
	.string "pagedir_unwriteone_p"
.Lname2884:
	.string "sys_fstatfs64"
.Lname2885:
	.string "timespec_to_qtime"
.Lname2887:
	.string "inode_readv_phys_blocking"
.Lname2891:
	.string "sys_frealpath4"
.Lname2893:
	.string "abort"
.Lname2898:
	.string "block_device_awritev_phys_sector"
.Lname2901:
	.string "devfs_remove"
.Lname2902:
	.string "sys_readvf"
.Lname2903:
	.string "ansitty_putuni"
.Lname2904:
	.string "rwlock_write_nx"
.Lname2905:
	.string "dbg_isholding_alt"
.Lname2908:
	.string "aio_multihandle_generic_func"
.Lname2910:
	.string "x86_lapic_version"
.Lname2911:
	.string "sys_readf"
.Lname2915:
	.string "ringbuffer_rseek"
.Lname2916:
	.string "superblock_mountlock_read"
.Lname2917:
	.string "sys_setdomainname"
.Lname2919:
	.string "boot_cpustate"
.Lname2921:
	.string "directory_getcaseentry"
.Lname2927:
	.string "inode_read"
.Lname2931:
	.string "sys_fdatasync"
.Lname2932:
	.string "stack_current"
.Lname2937:
	.string "sys_kfstatat"
.Lname2943:
	.string "superblock_mountlock_upgrade"
.Lname2944:
	.string "path_lock_upgrade"
.Lname2945:
	.string "mempsetq"
.Lname2946:
	.string "sys_dup2"
.Lname2947:
	.string "sys_dup3"
.Lname2949:
	.string "quantum_time"
.Lname2950:
	.string "addr2line_printf"
.Lname2951:
	.string "mempsetw"
.Lname2952:
	.string "unwind_getreg_lcpustate"
.Lname2953:
	.string "driver_destroy"
.Lname2955:
	.string "sys_getdrives"
.Lname2956:
	.string "memmovel"
.Lname2957:
	.string "sys_lremovexattr"
.Lname2958:
	.string "ramfs_symlink_type"
.Lname2960:
	.string "sys_rt_sigtimedwait64"
.Lname2962:
	.string "keyboard_device_putkey_nopr"
.Lname2963:
	.string "vm_datapart_sync"
.Lname2964:
	.string "kernel_debugtrap_enabled"
.Lname2965:
	.string "vm_tasklock_tryupgrade"
.Lname2967:
	.string "dbg_getuni"
.Lname2969:
	.string "sys_unlinkat"
.Lname2970:
	.string "pagedir_unmap_userspace"
.Lname2972:
	.string "handle_install"
.Lname2973:
	.string "debuginfo_cu_parser_loadattr_subprogram"
.Lname2975:
	.string "json_parser_leave"
.Lname2979:
	.string "cpuid_features"
.Lname2980:
	.string "pidns_trylookup_locked"
.Lname2981:
	.string "sys_write"
.Lname2982:
	.string "sys_fallocate64"
.Lname2984:
	.string "unicode_writeutf8"
.Lname2985:
	.string "superblock_mountlock_tryupgrade"
.Lname2989:
	.string "memchr"
.Lname2991:
	.string "validate_executable_opt"
.Lname2992:
	.string "sys_dup"
.Lname2994:
	.string "task_setprocessgroupleader"
.Lname2995:
	.string "pmembank_type_names"
.Lname2996:
	.string "vmb_mapat"
.Lname2997:
	.string "unwind_setreg_kcpustate"
.Lname2998:
	.string "sys_ioctlf"
.Lname3000:
	.string "heap_align_untraced_nx"
.Lname3001:
	.string "vm_kernel_treelock_end"
.Lname3004:
	.string "sigmask_check_after_syscall"
.Lname3007:
	.string "sys_madvise"
.Lname3010:
	.string "dbg_default_attr"
.Lname3011:
	.string "sigmask_check_s"
.Lname3012:
	.string "sys_linux_stat64"
.Lname3014:
	.string "dbg_origstate"
.Lname3017:
	.string "pipe_reader_destroy"
.Lname3021:
	.string "sys_fchown32"
.Lname3024:
	.string "dbg_scroll_maxline"
.Lname3027:
	.string "regdump_flags"
.Lname3028:
	.string "__stack_chk_guard"
.Lname3029:
	.string "dbg_setcur_visible"
.Lname3033:
	.string "dev_tty"
.Lname3034:
	.string "sys_linux_lstat64"
.Lname3035:
	.string "path_printex"
.Lname3036:
	.string "superblock_syncall"
.Lname3039:
	.string "kernel_debugtrap_r_lcpustate"
.Lname3040:
	.string "pagedir_unmapone_p"
.Lname3041:
	.string "handle_get_directory_entry"
.Lname3042:
	.string "rwlock_reading_r"
.Lname3043:
	.string "sys_brk"
.Lname3045:
	.string "vm_getfree"
.Lname3046:
	.string "inode_areadallv"
.Lname3049:
	.string "vm_datapart_destroy"
.Lname3052:
	.string "character_device_poll"
.Lname3053:
	.string "vio_cmpxch_or_writeb"
.Lname3057:
	.string "memmoveq"
.Lname3059:
	.string "path_alloc"
.Lname3061:
	.string "kernel_panic_scpustate"
.Lname3063:
	.string "memmovew"
.Lname3064:
	.string "devfs_lock_write_nx"
.Lname3065:
	.string "sys_fmknodat"
.Lname3067:
	.string "inode_areadallk"
.Lname3069:
	.string "dbg_vmenuf"
.Lname3071:
	.string "devfs_lock_trywrite"
.Lname3072:
	.string "task_sigstop"
.Lname3074:
	.string "lookup_filesystem_type"
.Lname3075:
	.string "block_device_partition_readv_phys"
.Lname3076:
	.string "x86_idt_start_traced"
.Lname3078:
	.string "sys_pselect6"
.Lname3080:
	.string "driver_library_path"
.Lname3081:
	.string "vmb_apply"
.Lname3083:
	.string "vm_kernel_sync"
.Lname3085:
	.string "block_device_autopart"
.Lname3087:
	.string "error_as_errno"
.Lname3090:
	.string "sys_umount2"
.Lname3091:
	.string "ansitty_putc"
.Lname3092:
	.string "vio_writel_aligned"
.Lname3093:
	.string "cpu_apply_fcpustate"
.Lname3095:
	.string "json_parser_eqstring"
.Lname3096:
	.string "path_sprintex"
.Lname3097:
	.string "vm_kernel_treelock_endread"
.Lname3099:
	.string "dbg_getreg"
.Lname3101:
	.string "sys_ioperm"
.Lname3104:
	.string "vm_datablock_anonymous"
.Lname3105:
	.string "heap_allat_nx"
.Lname3109:
	.string "pagedir_unwriteone"
.Lname3111:
	.string "memlenw"
.Lname3115:
	.string "error_throw"
.Lname3117:
	.string "dbg_pprinter"
.Lname3118:
	.string "_strtoi64"
.Lname3122:
	.string "pci_readaddr"
.Lname3123:
	.string "pagedir_kernel_phys"
.Lname3124:
	.string "strnend"
.Lname3125:
	.string "error_code"
.Lname3127:
	.string "vm_datapart_lockread_setcore_unsharecow"
.Lname3129:
	.string "vm_destroy"
.Lname3132:
	.string "memlenl"
.Lname3135:
	.string "sys_fallocate"
.Lname3136:
	.string "character_device_mmap"
.Lname3138:
	.string "pty_register"
.Lname3140:
	.string "memend"
.Lname3141:
	.string "task_push_asynchronous_rpc_v"
.Lname3143:
	.string "vio_subw"
.Lname3145:
	.string "__predict_update_dl"
.Lname3148:
	.string "unwind_setreg_xfpustate"
.Lname3149:
	.string "sys_swapoff"
.Lname3150:
	.string "kernel_vpanic_kcpustate"
.Lname3153:
	.string "path_lock_endwrite"
.Lname3154:
	.string "vio_subb"
.Lname3159:
	.string "inode_readk_blocking"
.Lname3160:
	.string "path_movemount"
.Lname3161:
	.string "task_trywait"
.Lname3164:
	.string "vio_subl"
.Lname3167:
	.string "page_ffree"
.Lname3168:
	.string "__cxa_begin_catch"
.Lname3170:
	.string "sys_setregid32"
.Lname3171:
	.string "kernel_vpanic_ucpustate"
.Lname3172:
	.string "task_connect_ghost"
.Lname3173:
	.string "sys_fsmode"
.Lname3174:
	.string "sys_set_library_listdef"
.Lname3178:
	.string "sys_poll"
.Lname3180:
	.string "sys_profil"
.Lname3181:
	.string "dbg_setcur"
.Lname3184:
	.string "sys_exit_group"
.Lname3186:
	.string "sys_setfsgid32"
.Lname3187:
	.string "driver_unloaded_callbacks"
.Lname3190:
	.string "slab_kmalloc4"
.Lname3192:
	.string "vm_datapart_lockwrite_setcore_nx"
.Lname3193:
	.string "sys_kfstat"
.Lname3200:
	.string "pagedir_prepare_map_keep"
.Lname3201:
	.string "debuginfo_cu_parser_nextparent"
.Lname3202:
	.string "block_device_areadv_sector"
.Lname3205:
	.string "regdump_cr0"
.Lname3208:
	.string "block_device_lookup_nx"
.Lname3209:
	.string "vm_datapart_lock_upgrade"
.Lname3211:
	.string "task_schedule_synchronous_srpc_nx"
.Lname3212:
	.string "mouse_device_ioctl"
.Lname3214:
	.string "x86_this_user_gsbase"
.Lname3217:
	.string "__predict_update_dx"
.Lname3218:
	.string "mouse_device_moveto_nopr"
.Lname3219:
	.string "task_free_rpc"
.Lname3220:
	.string "x86_exsyscall_is_cancellation_point"
.Lname3225:
	.string "sys_read"
.Lname3231:
	.string "rwlock_endwrite"
.Lname3232:
	.string "validate_readablem_opt"
.Lname3233:
	.string "vio_cmpxchq"
.Lname3237:
	.string "vm_kernel_treelock_tryservice"
.Lname3238:
	.string "format_printf"
.Lname3239:
	.string "vio_cmpxchw"
.Lname3240:
	.string "devfs_lock_read_nx"
.Lname3241:
	.string "taskpid_destroy"
.Lname3242:
	.string "mempsetl"
.Lname3243:
	.string "mall_print_traceback"
.Lname3248:
	.string "pidns_alloc"
.Lname3250:
	.string "vio_cmpxchb"
.Lname3251:
	.string "kernel_heaps"
.Lname3253:
	.string "vm_datapart_lockread_setcore"
.Lname3254:
	.string "sys_readv"
.Lname3255:
	.string "json_parser_getstring"
.Lname3256:
	.string "vm_datapart_lock_upgrade_nx"
.Lname3257:
	.string "vm_datablock_vio_read"
.Lname3260:
	.string "vio_cmpxchl"
.Lname3261:
	.string "_bootcpu"
.Lname3262:
	.string "unwind_fde_rule"
.Lname3264:
	.string "format_hexdump"
.Lname3265:
	.string "memsetq"
.Lname3267:
	.string "kernel_panic_lcpustate"
.Lname3268:
	.string "sys_umount"
.Lname3269:
	.string "sys_nanosleep"
.Lname3270:
	.string "block_device_partition_writev"
.Lname3271:
	.string "memsetw"
.Lname3272:
	.string "fpustate_init_nx"
.Lname3274:
	.string "snprintf"
.Lname3277:
	.string "inodes_recent_lim"
.Lname3283:
	.string "devfs"
.Lname3284:
	.string "debugline_loadunit"
.Lname3285:
	.string "_this_cpu"
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
.Lname3295:
	.string "fpustate_save"
.Lname3300:
	.string "unwind_fde_load"
.Lname3301:
	.string "sys_writef"
.Lname3304:
	.string "heap_realloc_untraced_nx"
.Lname3310:
	.string "coredump_create_for_exception"
.Lname3313:
	.string "__predict_update_ax"
.Lname3315:
	.string "block_device_writev_phys_sync"
.Lname3316:
	.string "page_stat"
.Lname3317:
	.string "sys_timerfd_gettime"
.Lname3320:
	.string "task_alloc_synchronous_srpc_nx"
.Lname3321:
	.string "sys_fsymlinkat"
.Lname3323:
	.string "sys_munlock"
.Lname3325:
	.string "ansitty_device_cinit"
.Lname3327:
	.string "rwlock_canwrite"
.Lname3330:
	.string "sys_flistxattr"
.Lname3331:
	.string "cpu_features"
.Lname3332:
	.string "vpage_ffree_untraced"
.Lname3334:
	.string "inode_areadv"
.Lname3336:
	.string "pidns_upgrade_nx"
.Lname3337:
	.string "quantum_local_to_global"
.Lname3339:
	.string "_boottask"
.Lname3341:
	.string "sys_getgroups32"
.Lname3344:
	.string "pagedir_unmap_userspace_nosync_p"
.Lname3345:
	.string "vm_datapart_allocswap_nx"
.Lname3346:
	.string "dbg_attr"
.Lname3347:
	.string "vfs_alloc"
.Lname3348:
	.string "tty_device_stopfwd"
.Lname3349:
	.string "debuginfo_print_typename"
.Lname3352:
	.string "vm_kernel_treelock_read_nx"
.Lname3355:
	.string "inode_areadk"
.Lname3357:
	.string "unicode_16to8"
.Lname3358:
	.string "pagedir_haschanged"
.Lname3359:
	.string "block_device_delparts"
.Lname3361:
	.string "block_device_alloc"
.Lname3362:
	.string "sys_setxattr"
.Lname3363:
	.string "fpustate_alloc"
.Lname3364:
	.string "dbg_draweditfield"
.Lname3365:
	.string "swap_write"
.Lname3369:
	.string "keyboard_device_fini"
.Lname3370:
	.string "unwind_getreg_ucpustate"
.Lname3373:
	.string "x86_debug_gdt"
.Lname3376:
	.string "krealign_in_place_offset"
.Lname3381:
	.string "validate_writable"
.Lname3383:
	.string "dbg_applyreg"
.Lname3384:
	.string "slab_kmalloc_nx"
.Lname3385:
	.string "vmb_isused"
.Lname3387:
	.string "json_parser_leavearray"
.Lname3388:
	.string "inode_readall"
.Lname3391:
	.string "pidns_downgrade"
.Lname3392:
	.string "dbg_getc"
.Lname3393:
	.string "mall_trace"
.Lname3395:
	.string "sys_set_tid_address"
.Lname3396:
	.string "terminal_poll_iread"
.Lname3398:
	.string "__acheckf"
.Lname3400:
	.string "task_raisesignalprocess_nx"
.Lname3403:
	.string "task_tryyield"
.Lname3412:
	.string "sys_fmkdirat"
.Lname3413:
	.string "pagedir_prepare_mapone"
.Lname3415:
	.string "dbg_trygetkey"
.Lname3417:
	.string "json_parser_leaveobject"
.Lname3419:
	.string "path_traversen_at"
.Lname3420:
	.string "sys_fchown"
.Lname3421:
	.string "vm_do_freeram"
.Lname3423:
	.string "error_info"
.Lname3425:
	.string "memrlenq"
.Lname3426:
	.string "kernel_debugtrap_ucpustate"
.Lname3428:
	.string "sys_setfsuid"
.Lname3429:
	.string "vm_datapart_free"
.Lname3430:
	.string "dbg_addr2line_printf"
.Lname3431:
	.string "memrlenw"
.Lname3432:
	.string "vm_tasklock_write_nx"
.Lname3434:
	.string "character_device_write"
.Lname3435:
	.string "pidns_trylookup_task"
.Lname3437:
	.string "vm_mapres"
.Lname3440:
	.string "vm_datapart_map_ram_autoprop_p"
.Lname3442:
	.string "mouse_buffer_putpackets_nopr"
.Lname3444:
	.string "sys_setsockopt"
.Lname3445:
	.string "vm_kernel_treelock_downgrade"
.Lname3446:
	.string "dbg_printf"
.Lname3449:
	.string "sys_sched_yield"
.Lname3452:
	.string "memrlenl"
.Lname3454:
	.string "unicode_readutf8_n"
.Lname3455:
	.string "sys_pause"
.Lname3457:
	.string "memcmp"
.Lname3458:
	.string "sys_pipe2"
.Lname3460:
	.string "sys_getdents64"
.Lname3461:
	.string "addr2line_vprintf"
.Lname3464:
	.string "task_detach"
.Lname3465:
	.string "driver_section_destroy"
.Lname3466:
	.string "sys_ustat"
.Lname3467:
	.string "sys_vfork"
.Lname3473:
	.string "vm_startdma"
.Lname3475:
	.string "cpu_disable_preemptive_interrupts"
.Lname3476:
	.string "sys_timerfd_gettime64"
.Lname3477:
	.string "vm_datapart_write"
.Lname3478:
	.string "handle_get_directory_node"
.Lname3480:
	.string "task_alloc_user_srpc_nx"
.Lname3483:
	.string "sys_mkdir"
.Lname3487:
	.string "ansitty_device_write"
.Lname3489:
	.string "regdump_scpustate"
.Lname3490:
	.string "rwlock_writing_r"
.Lname3491:
	.string "vm_datablock_haschanges"
.Lname3492:
	.string "debuginfo_cu_parser_loadattr_compile_unit"
.Lname3493:
	.string "devfs_lock_endwrite"
.Lname3494:
	.string "error_vprintf"
.Lname3503:
	.string "sys_sysinfo"
.Lname3504:
	.string "vm_datablock_debugheap"
.Lname3506:
	.string "dbg_screen_height"
.Lname3507:
	.string "aio_handle_multiple_func"
.Lname3509:
	.string "handle_close"
.Lname3512:
	.string "task_schedule_synchronous_rpc_nx"
.Lname3513:
	.string "vm_memset"
.Lname3515:
	.string "task_serve_nx"
.Lname3518:
	.string "disasm_instrlen"
.Lname3519:
	.string "rwlock_tryupgrade"
.Lname3523:
	.string "fs_filesystem_types"
.Lname3524:
	.string "fs_filesystems_lock_tryread"
.Lname3525:
	.string "blocking_cleanup_service"
.Lname3528:
	.string "vm_tasklock_read_nx"
.Lname3531:
	.string "__acheck"
.Lname3532:
	.string "block_device_partition_ioctl"
.Lname3539:
	.string "block_device_read_phys_sync"
.Lname3540:
	.string "sig_send"
.Lname3541:
	.string "vm_datablock_anonymize"
.Lname3543:
	.string "callback_list_detroy"
.Lname3545:
	.string "rwlock_downgrade_readonly"
.Lname3546:
	.string "fs_destroy"
.Lname3548:
	.string "aio_multihandle_fail"
.Lname3549:
	.string "boot_partition"
.Lname3550:
	.string "sys_chown"
.Lname3551:
	.string "path_lock_tryservice"
.Lname3552:
	.string "slab_kmalloc_nx20"
.Lname3554:
	.string "kprinter"
.Lname3555:
	.string "task_enable_redirect_usercode_rpc"
.Lname3556:
	.string "sys_mprotect"
.Lname3557:
	.string "vm_node_free"
.Lname3559:
	.string "_this_x86_dr1"
.Lname3562:
	.string "sys_openpty"
.Lname3563:
	.string "sys_sigprocmask"
.Lname3565:
	.string "sys_linux_fstat32"
.Lname3566:
	.string "kmemalign"
.Lname3568:
	.string "pagedir_unprepare_map"
.Lname3569:
	.string "x86_check_spurious_interrupt_PIC1"
.Lname3570:
	.string "ansitty_printer"
.Lname3571:
	.string "task_alloc_synchronous_srpc"
.Lname3572:
	.string "fs_filesystems_lock_endread"
.Lname3573:
	.string "kernel_panic_icpustate"
.Lname3574:
	.string "slab_kmalloc_nx16"
.Lname3575:
	.string "sys_sendmsg"
.Lname3577:
	.string "vm_datablock_locatepart_exact"
.Lname3579:
	.string "format_quote"
.Lname3583:
	.string "fpustate_free"
.Lname3584:
	.string "unwind_getreg_kcpustate"
.Lname3586:
	.string "heap_realloc_nx"
.Lname3587:
	.string "task_disconnect_c"
.Lname3588:
	.string "sys_linux_oldlstat"
.Lname3589:
	.string "sys_writev"
.Lname3590:
	.string "instruction_trysucc"
.Lname3594:
	.string "sys_timer_gettime"
.Lname3595:
	.string "sys_sgetmask"
.Lname3596:
	.string "path_traversefull"
.Lname3597:
	.string "sys_llistxattr"
.Lname3600:
	.string "vm_datapart_allocswap"
.Lname3603:
	.string "vm_datablock_anonymous_zero_type_vec"
.Lname3604:
	.string "debuginfo_cu_parser_getconst"
.Lname3605:
	.string "kernel_symbol_table"
.Lname3609:
	.string "slab_malloc4"
.Lname3611:
	.string "memlenq"
.Lname3614:
	.string "disasm_print_instruction"
.Lname3615:
	.string "page_isfree"
.Lname3616:
	.string "pagedir_prepare_mapone_p"
.Lname3619:
	.string "block_device_readv_phys"
.Lname3620:
	.string "sys_accept4"
.Lname3621:
	.string "sys_rpc_schedule"
.Lname3623:
	.string "vio_xchw"
.Lname3625:
	.string "syscall_tracing_setenabled"
.Lname3627:
	.string "empty_kernel_sigmask"
.Lname3632:
	.string "pagedir_map"
.Lname3633:
	.string "slab_malloc8"
.Lname3634:
	.string "cpu_broadcastipi_notthis"
.Lname3636:
	.string "heap_truncate_untraced"
.Lname3637:
	.string "vm_kernel_syncone"
.Lname3638:
	.string "sys_pwrite64f"
.Lname3641:
	.string "dbg_purgeuni"
.Lname3643:
	.string "sys_ssetmask"
.Lname3644:
	.string "vio_xchl"
.Lname3647:
	.string "cmdline_decode"
.Lname3651:
	.string "block_device_partition_read_phys"
.Lname3652:
	.string "sys_execveat"
.Lname3653:
	.string "x86_this_user_fsbase"
.Lname3654:
	.string "kernel_vpanic_lcpustate"
.Lname3664:
	.string "vsprintf_s"
.Lname3666:
	.string "path_traverse"
.Lname3667:
	.string "block_device_write_phys"
.Lname3668:
	.string "path_printent"
.Lname3669:
	.string "vm_datapart_loaddatapage"
.Lname3670:
	.string "unicode_readutf16"
.Lname3671:
	.string "driver_finalize"
.Lname3672:
	.string "vm_datapart_lockwrite_setcore_unsharecow_nx"
.Lname3673:
	.string "sys_waitid"
.Lname3674:
	.string "block_device_awrite_phys"
.Lname3677:
	.string "task_pause"
.Lname3678:
	.string "page_stat_between"
.Lname3679:
	.string "sys_sync_file_range"
.Lname3682:
	.string "sys_getxattr"
.Lname3683:
	.string "sys_remap_file_pages"
.Lname3684:
	.string "pagedir_maphint"
.Lname3685:
	.string "dbg_tabsize"
.Lname3688:
	.string "path_lock_read"
.Lname3694:
	.string "vm_datapart_write_unsafe"
.Lname3697:
	.string "block_device_awritev_phys"
.Lname3698:
	.string "sys_getitimer"
.Lname3700:
	.string "pagedir_gethint"
.Lname3701:
	.string "heap_truncate"
.Lname3702:
	.string "unicode_readutf8_rev"
.Lname3705:
	.string "sys_rt_sigtimedwait"
.Lname3711:
	.string "sighand_ptr_lockread"
.Lname3712:
	.string "pagedir_unwrite_p"
.Lname3713:
	.string "sys_getpgrp"
.Lname3715:
	.string "task_schedule_asynchronous_srpc"
.Lname3716:
	.string "userkern_segment_part"
.Lname3717:
	.string "character_device_lookup_name"
.Lname3718:
	.string "vm_datablock_write_buffered"
.Lname3721:
	.string "dbg_ungetuni"
.Lname3722:
	.string "ringbuffer_write"
.Lname3724:
	.string "dbg_bell"
.Lname3725:
	.string "debuginfo_cu_parser_getexpr"
.Lname3728:
	.string "vm_copytophys"
.Lname3731:
	.string "vm_datablock_anonymous_zero_vec"
.Lname3732:
	.string "debuginfo_cu_parser_nextchild"
.Lname3733:
	.string "pagedir_translate"
.Lname3737:
	.string "sys_timer_gettime64"
.Lname3739:
	.string "sys_mlock"
.Lname3740:
	.string "sys_statfs64"
.Lname3741:
	.string "handle_get_pipe"
.Lname3742:
	.string "block_device_aread"
.Lname3743:
	.string "sys_sethostname"
.Lname3744:
	.string "kernel_debugtrap"
.Lname3745:
	.string "sys_raiseat"
.Lname3748:
	.string "vm_datapart_read"
.Lname3749:
	.string "handle_tryclose"
.Lname3752:
	.string "rwlock_read_nx"
.Lname3753:
	.string "__cxa_rethrow"
.Lname3756:
	.string "sys_fcntl"
.Lname3758:
	.string "sys_klstat"
.Lname3764:
	.string "pidns_end"
.Lname3765:
	.string "pidns_upgrade"
.Lname3767:
	.string "sys_sigsuspend"
.Lname3768:
	.string "vm_do_allocram_nx"
.Lname3769:
	.string "ttybase_device_hupctty"
.Lname3772:
	.string "sighand_raise_signal"
.Lname3775:
	.string "character_device_register_auto"
.Lname3778:
	.string "vmb_alloc_peb"
.Lname3779:
	.string "vm_exec"
.Lname3780:
	.string "sys_rt_sigsuspend"
.Lname3781:
	.string "page_free"
.Lname3782:
	.string "krealign_offset"
.Lname3786:
	.string "kernel_vpanic_scpustate"
.Lname3789:
	.string "driver_getshstrtab"
.Lname3790:
	.string "mouse_device_motion"
.Lname3792:
	.string "vmb_overlay"
.Lname3794:
	.string "cpu_vector"
.Lname3796:
	.string "inode_aread"
.Lname3797:
	.string "path_rename"
.Lname3798:
	.string "vm_read_nopf"
.Lname3800:
	.string "path_lock_write_nx"
.Lname3801:
	.string "json_parser_enterarray"
.Lname3805:
	.string "vm_isused"
.Lname3810:
	.string "mouse_device_hwheel_nopr"
.Lname3811:
	.string "vm_copyfromphys"
.Lname3812:
	.string "json_parser_enterobject"
.Lname3813:
	.string "vm_kernel_treelock_upgrade"
.Lname3815:
	.string "x86_idt_start_debug"
.Lname3819:
	.string "ringbuffer_write_nonblock"
.Lname3821:
	.string "json_parser_getint64"
.Lname3822:
	.string "vm_oninit_callbacks"
.Lname3824:
	.string "character_device_lookup"
.Lname3827:
	.string "json_parser_unyield"
.Lname3828:
	.string "sys_pread64"
.Lname3829:
	.string "kernel_debugtrap_icpustate"
.Lname3833:
	.string "instruction_pred"
.Lname3835:
	.string "superblock_nodeslock_downgrade"
.Lname3836:
	.string "dbg_scroll"
.Lname3839:
	.string "sys_pipe"
.Lname3840:
	.string "pagedir_unmap_userspace_p"
.Lname3841:
	.string "mempmoveq"
.Lname3844:
	.string "error_throw_current"
.Lname3845:
	.string "vm_datablock_read_unsafe"
.Lname3847:
	.string "mempmovew"
.Lname3849:
	.string "callback_list_empty"
.Lname3852:
	.string "inode_ioctl"
.Lname3854:
	.string "heap_allat_untraced"
.Lname3856:
	.string "pagedir_map_p"
.Lname3857:
	.string "path_lock_read_nx"
.Lname3858:
	.string "mouse_device_button_ex_nopr"
.Lname3859:
	.string "regdump_sgregs_with_cs_ss"
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
	.string "devfs_lock_endread"
.Lname3866:
	.string "vio_addb"
.Lname3870:
	.string "superblock_open"
.Lname3873:
	.string "sys_linux_fstat64"
.Lname3876:
	.string "pidns_read"
.Lname3879:
	.string "inode_read_phys_blocking"
.Lname3881:
	.string "cpu_do_assert_integrity"
.Lname3883:
	.string "dbg"
.Lname3884:
	.string "sys_ppoll"
.Lname3885:
	.string "keyboard_buffer_putkey"
.Lname3886:
	.string "unwind_fde_sigframe_exec"
.Lname3889:
	.string "vm_tasklock_upgrade_nx"
.Lname3891:
	.string "heap_realloc"
.Lname3892:
	.string "vm_datapart_lock_tryread"
.Lname3893:
	.string "dbg_enter_ucpustate"
.Lname3894:
	.string "dbg_menuf"
.Lname3895:
	.string "unwind_setreg_fcpustate"
.Lname3897:
	.string "task_sigcont"
.Lname3898:
	.string "vm_datapart_haschanged"
.Lname3899:
	.string "sys_pselect6_64"
.Lname3901:
	.string "dbg_enter_scpustate"
.Lname3902:
	.string "unicode_readutf16_swap_rev_n"
.Lname3903:
	.string "sys_uname"
.Lname3905:
	.string "dbg_setscreendata"
.Lname3906:
	.string "sys_fremovexattr"
.Lname3908:
	.string "sys_fchmodat"
.Lname3909:
	.string "vm_map_subrange"
.Lname3910:
	.string "format_vscanf"
.Lname3912:
	.string "sprintf"
.Lname3915:
	.string "syscall_emulate_callback"
.Lname3917:
	.string "sys_getresgid32"
.Lname3918:
	.string "vm_datapart_lock_endread"
.Lname3920:
	.string "kernel_default_heap"
.Lname3922:
	.string "cpu_quantum_elapsed_nopr"
.Lname3923:
	.string "sys_utimensat64"
.Lname3924:
	.string "block_device_makepart"
.Lname3925:
	.string "rwlock_upgrade"
.Lname3929:
	.string "character_device_pread"
.Lname3932:
	.string "vio_cmpxch_or_writel"
.Lname3935:
	.string "sys_mincore"
.Lname3936:
	.string "vm86_fullstep"
.Lname3938:
	.string "isr_vector_trigger"
.Lname3939:
	.string "inode_areadall_phys"
.Lname3940:
	.string "dbg_isholding_shift"
.Lname3941:
	.string "handle_lookup_type"
.Lname3946:
	.string "driver_try_decref_and_delmod"
.Lname3947:
	.string "cpu_sendipi_cpuset"
.Lname3949:
	.string "mouse_device_motion_nopr"
.Lname3953:
	.string "task_tryyield_or_pause"
.Lname3954:
	.string "dbg_evaladdr"
.Lname3955:
	.string "dbg_putc"
.Lname3961:
	.string "sys_sched_setaffinity"
.Lname3963:
	.string "sys_setrlimit"
.Lname3964:
	.string "mempmovel"
.Lname3966:
	.string "dbg_pprint"
.Lname3967:
	.string "slab_free"
.Lname3969:
	.string "cpu_enter_deepsleep"
.Lname3970:
	.string "sys_timerfd_settime"
.Lname3971:
	.string "system_clearcaches"
.Lname3972:
	.string "dbg_getfunc_start"
.Lname3973:
	.string "dbg_enter_here"
.Lname3974:
	.string "path_remove"
.Lname3975:
	.string "sys_setns"
.Lname3980:
	.string "task_push_asynchronous_rpc"
.Lname3981:
	.string "debuginfo_cu_parser_skipform"
.Lname3985:
	.string "mouse_device_read"
.Lname3987:
	.string "sys_fsync"
.Lname3988:
	.string "sys_prlimit64"
.Lname3989:
	.string "vm_datablock_write_unsafe"
.Lname3991:
	.string "json_parser_printstring"
.Lname3993:
	.string "x86_exsyscall_register_count"
.Lname3999:
	.string "fpustate_saveinto"
.Lname4000:
	.string "pidns_trylookup"
.Lname4002:
	.string "__asm32_syscallrouter_sysenter"
.Lname4003:
	.string "block_device_readv_phys_sync"
.Lname4004:
	.string "sys_getppid"
.Lname4005:
	.string "kernel_debugtrap_r_scpustate"
.Lname4006:
	.string "x86_cputss_df"
.Lname4008:
	.string "vm_datapart_split_nx"
.Lname4011:
	.string "vm_onfini_callbacks"
.Lname4016:
	.string "regdump_coregs"
.Lname4017:
	.string "pidns_read_nx"
.Lname4018:
	.string "block_device_register"
.Lname4019:
	.string "jiffies"
.Lname4020:
	.string "vm_mapresat"
.Lname4021:
	.string "directory_remove"
.Lname4023:
	.string "kernel_terminal_raise"
.Lname4025:
	.string "sys_lseek64"
.Lname4029:
	.string "task_setpid"
.Lname4030:
	.string "sys_openat"
.Lname4031:
	.string "dbg_getscreendata"
.Lname4034:
	.string "strtou32"
.Lname4035:
	.string "character_device_alloc"
.Lname4036:
	.string "sys_linux_oldstat"
.Lname4037:
	.string "disasm_print_line"
.Lname4039:
	.string "sys_setresgid32"
.Lname4041:
	.string "vm_syncall"
.Lname4044:
	.string "mouse_device_init"
.Lname4048:
	.string "regdump_ip"
.Lname4051:
	.string "inode_awrite_phys"
.Lname4052:
	.string "inode_stat"
.Lname4053:
	.string "inode_changed_chmtime"
.Lname4054:
	.string "sys_pread64f"
.Lname4056:
	.string "vm_datapart_lockread_setcore_unsharecow_nx"
.Lname4057:
	.string "sig_broadcast"
.Lname4061:
	.string "sys_recvfrom"
.Lname4063:
	.string "kernel_debugtrap_r_fcpustate"
.Lname4064:
	.string "sys_coredump"
.Lname4065:
	.string "memchrq"
.Lname4066:
	.string "keyboard_device_getchar"
.Lname4067:
	.string "mall_dump_leaks"
.Lname4068:
	.string "fpustate_init"
.Lname4069:
	.string "vm_tasklock_downgrade"
.Lname4070:
	.string "directory_getnode"
.Lname4071:
	.string "memchrw"
.Lname4075:
	.string "sys_lfutexlock"
.Lname4080:
	.string "sys_kcmp"
.Lname4084:
	.string "_this_taskpid"
.Lname4085:
	.string "syscall_trace"
.Lname4092:
	.string "memchrl"
.Lname4095:
	.string "validate_readable"
