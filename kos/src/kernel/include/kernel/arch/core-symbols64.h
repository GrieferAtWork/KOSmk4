.section .rodata.kernel_symtab
PUBLIC_OBJECT(kernel_symbol_table)
	.quad 0
	/* Symbol table */
	.quad 0
	.quad 0
	.quad 0
	.quad 0
END(kernel_symbol_table)
.section .rodata.kernel_strtab
