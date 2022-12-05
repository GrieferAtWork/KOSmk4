/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_ASMVIEW_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_ASMVIEW_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/paging.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/keyboard.h>

#include <alloca.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/debug_info.h>
#include <libdisasm/disassembler.h>
#include <libdisasm/format.h>
#include <libinstrlen/instrlen.h>

/*[[[config CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER = true
 * Use the disassembly printer to determine the length  of
 * instructions,  rather than making  use of libdisasm. In
 * theory, this shouldn't really make a difference, but in
 * practice, there can easily occur cases where the length
 * of  an instruction determined  by libdisasm will differ
 * from the length determined for the same instruction  by
 * libinstrlen.
 *
 * So to prevent inconsistencies during disassembly printing, we
 * instead always make use of the disassembly printer to provide
 * us with information about the length of an instruction.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#undef CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#elif !defined(CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER)
#define CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#elif (-CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER - 1) == -1
#undef CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#define CONFIG_NO_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#endif /* ... */
/*[[[end]]]*/


/*[[[config CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY = false
 * The building addr2line function of the debugger's disasm viewer only
 * translates kernel-space addresses to their source locations (user-
 * space addresses aren't translated)
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
#undef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
#elif !defined(CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY)
#define CONFIG_NO_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
#elif (-CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY - 1) == -1
#undef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
#define CONFIG_NO_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
#endif /* ... */
/*[[[end]]]*/


#ifndef CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER
#include <libinstrlen/instrlen.h>
#endif /* !CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER */

#if defined(__i386__) && !defined(__x86_64__)
#include <asm/cpu-flags.h>
#endif /* __i386__ && !__x86_64__ */

DECL_BEGIN



PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL av_disasm_print_instruction)(struct disassembler *__restrict self) {
	enum { MAXTEXTSIZ = 128 };
	/* This `12' must  be >=  the max number  of remaining  zero-bytes
	 * following  after  any  other  sequence  of  instruction  bytes.
	 * This is used to ensure that libdisasm sees that our instruction
	 * sequence terminates after a certain offset. */
	enum { TEXTTAILSIZE = 12 };
	byte_t textbuf[MAXTEXTSIZ + TEXTTAILSIZE];
	byte_t const *old_pc;
	size_t textsiz;
	textsiz = MAXTEXTSIZ - dbg_readmemory(self->d_pc, textbuf, MAXTEXTSIZ);
	if (!textsiz)
		return false;

	/* zero-fill a small tail area after the text to
	 * ensure  that  instructions  are   terminated. */
	bzero(textbuf + textsiz, TEXTTAILSIZE);

	/* Print instructions from our text buffer. */
	old_pc          = self->d_pc;
	self->d_pc      = textbuf;
	self->d_baseoff = (uintptr_t)old_pc - (uintptr_t)textbuf;

	/* Print the assembly. */
	disasm_print_instruction(self);

	/* Restore the proper PC value and account for distance moved. */
	self->d_pc = old_pc + (size_t)(self->d_pc - textbuf);

	/*self->d_baseoff = 0;*/
	return true;
}



#ifdef CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER

/* # of  instructions  to  unwind  for  the  purpose  of
 * verifying the program counter when walking backwards. */
#define AV_VERIFY_DISTANCE 8

PRIVATE NOBLOCK ssize_t
NOTHROW(KCALL stub_printer)(void *UNUSED(arg),
                            /*utf-8*/ char const *__restrict UNUSED(data),
                            size_t UNUSED(datalen)) {
	return 0;
}

PRIVATE NOBLOCK ssize_t
NOTHROW(LIBDISASM_CC stub_symbol_printer)(struct disassembler *__restrict UNUSED(self),
                                          void const *UNUSED(symbol_addr)) {
	return 0;
}

PRIVATE ATTR_DBGDATA struct disassembler av_instrlen_da = {
	.d_pc       = NULL,            /* Fill in as-needed */
	.d_baseoff  = 0,
	.d_printer  = &stub_printer,
	.d_arg      = NULL,
	.d_result   = 0,
	.d_symbol   = &stub_symbol_printer,
	.d_format   = NULL,
	.d_target   = DISASSEMBLER_TARGET_CURRENT,
	.d_flags    = DISASSEMBLER_FNOADDR | DISASSEMBLER_FNOBYTES,
	.d_maxbytes = 0,
};

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_core_instr_trysucc)(void const *addr) {
	av_instrlen_da.d_pc = (byte_t const *)addr;
	if (!av_disasm_print_instruction(&av_instrlen_da))
		return (byte_t *)addr + 1;
	return (void *)av_instrlen_da.d_pc;
}

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_core_instr_trypred)(void const *addr) {
	byte_t *result;
	unsigned int i = 15; /* 15 is the max instruction length on X86 */
	do {
		result = (byte_t *)addr - i;
		if (av_core_instr_trysucc(result) == addr)
			goto done;
	} while (--i);
done:
	return result;
}

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_core_instr_trypred_n)(void *addr, unsigned int n) {
	while (n--) {
		addr = av_core_instr_trypred(addr);
	}
	return addr;
}



#define av_instr_succ(addr) av_core_instr_trysucc(addr)

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_instr_pred)(void *addr) {
	void *baseline, *result;
	baseline = av_core_instr_trypred_n(addr, AV_VERIFY_DISTANCE);
	for (;;) {
		result = baseline;
		baseline = av_instr_succ(baseline);
		if (baseline >= addr)
			break;
	}
	return result;
}

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_instr_pred_n)(void *addr, unsigned int n) {
	if (n > 1)
		addr = av_core_instr_trypred_n(addr, n - 1);
	if (n > 0)
		addr = av_instr_pred(addr);
	return addr;
}

#else /* CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER */

#define av_instr_succ(addr) ((void *)dbg_instruction_trysucc(addr, INSTRLEN_ISA_DEFAULT))
#define av_instr_pred(addr) ((void *)dbg_instruction_trypred(addr, INSTRLEN_ISA_DEFAULT))

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_instr_pred_n)(void *addr, unsigned int n) {
	while (n--)
		addr = (void *)dbg_instruction_trypred(addr, INSTRLEN_ISA_DEFAULT);
	return addr;
}

#endif /* !CONFIG_KERNEL_DEBUGGER_ASMVIEW_INSTRLEN_USES_DISASM_PRINTER */



PRIVATE NONNULL((1)) ssize_t LIBDISASM_CC
av_format(struct disassembler *__restrict UNUSED(self), unsigned int format_option) {
	switch (format_option) {

	case DISASSEMBLER_FORMAT_REGISTER_PREFIX:
		dbg_setfgcolor(ANSITTY_CL_TEAL);
		break;

	case DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX:
	case DISASSEMBLER_FORMAT_OFFSET_PREFIX:
	case DISASSEMBLER_FORMAT_SCALE_PREFIX:
		dbg_setfgcolor(ANSITTY_CL_RED);
		break;

	case DISASSEMBLER_FORMAT_SYMBOL_PREFIX:
		dbg_setfgcolor(ANSITTY_CL_WHITE);
		break;

	case DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX:
		dbg_setfgcolor(ANSITTY_CL_DARK_GRAY);
		break;

	case DISASSEMBLER_FORMAT_MNEMONIC_PREFIX:
		dbg_setfgcolor(ANSITTY_CL_PURPLE);
		break;

	default:
		dbg_setcolor(dbg_getdefaultcolor());
		break;
	}
	return 0;
}

LOCAL ATTR_DBGTEXT bool
NOTHROW(FCALL av_getbyte)(void const *addr, byte_t *pvalue) {
	return dbg_readmemory(addr, pvalue, 1) == 0;
}


struct av_symbol {
	char const   *s_name;  /* [1..1] Symbol name (set to (char const *)-1 if unknown). (Set to NULL if entry is used) */
	byte_t const *s_start; /* Symbol start address. (absolute) */
	byte_t const *s_end;   /* Symbol end address. (absolute) */
};

struct av_sections_lock {
	REF module_t              *sl_module;  /* [1..1] The associated module. (Set to NULL if entry is used) */
	di_addr2line_dl_sections_t sl_dlsect;  /* DL sections data */
	di_addr2line_sections_t    sl_dbsect;  /* Debug sections data */
};

PRIVATE struct av_symbol av_symbol_cache[128];
PRIVATE struct av_sections_lock av_sections_cache[8];

DBG_FINI(finalize_av_symbol_cache) {
	unsigned int i;
	for (i = 0; i < lengthof(av_sections_cache); ++i) {
		if (!av_sections_cache[i].sl_module)
			continue;
		debug_addr2line_sections_unlock(&av_sections_cache[i].sl_dlsect);
		module_decref_unlikely(av_sections_cache[i].sl_module);
	}
	bzero(av_symbol_cache, sizeof(av_symbol_cache));
	bzero(av_sections_cache, sizeof(av_sections_cache));
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL av_do_lock_sections)(struct av_sections_lock *__restrict info,
                                   void const *symbol_addr) {
	unsigned int lock_error;
	REF module_t *symbol_module;
	symbol_module = module_fromaddr_nx(symbol_addr);
	if (!symbol_module)
		return false;
	lock_error = debug_addr2line_sections_lock(symbol_module,
	                                           &info->sl_dbsect,
	                                           &info->sl_dlsect);
	if (lock_error != DEBUG_INFO_ERROR_SUCCESS) {
		module_decref_unlikely(symbol_module);
		return false;
	}
	info->sl_module = symbol_module;
	return true;
}

PRIVATE ATTR_DBGTEXT struct av_sections_lock *
NOTHROW(FCALL av_lock_sections)(void const *symbol_addr) {
	unsigned int i;
	struct av_sections_lock *resent = NULL;
#ifdef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
	if unlikely(!ADDR_ISKERN(symbol_addr))
		goto done;
#endif /* CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY */
	for (i = 0; i < lengthof(av_sections_cache); ++i) {
		if (!av_sections_cache[i].sl_module) {
			if (!resent)
				resent = &av_sections_cache[i];
			continue;
		}
		if ((byte_t const *)symbol_addr >= module_getloadmin(av_sections_cache[i].sl_module) &&
		    (byte_t const *)symbol_addr <= module_getloadmax(av_sections_cache[i].sl_module))
			return &av_sections_cache[i];
	}
	if (!resent) {
		debug_addr2line_sections_unlock(&av_sections_cache[0].sl_dlsect);
		module_decref_unlikely(av_sections_cache[0].sl_module);
		memmovedown(&av_sections_cache[0], &av_sections_cache[1],
		            sizeof(av_sections_cache) - sizeof(av_sections_cache[0]));
		resent = COMPILER_ENDOF(av_sections_cache) - 1;
	}
	resent->sl_module = NULL;
	if (!av_do_lock_sections(resent, symbol_addr))
		resent = NULL;
#ifdef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
done:
#endif /* CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY */
	return resent;
}


PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL av_addr2line)(di_debug_addr2line_t *__restrict info,
                            void const *symbol_addr) {
	unsigned int addr2line_error;
	struct av_sections_lock *sections;
	uintptr_t module_relative_pc, loadaddr;
	sections = av_lock_sections(symbol_addr);
	if (!sections)
		return false;
	loadaddr           = module_getloadaddr(sections->sl_module);
	module_relative_pc = (uintptr_t)symbol_addr - loadaddr;
	addr2line_error    = debug_addr2line(&sections->sl_dbsect, info, module_relative_pc,
	                                     DEBUG_ADDR2LINE_LEVEL_SOURCE, DEBUG_ADDR2LINE_FNORMAL);
	if (addr2line_error != DEBUG_INFO_ERROR_SUCCESS)
		return false;
	info->al_symstart += loadaddr;
	info->al_symend += loadaddr;
	return true;
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL av_do_lookup_symbol)(struct av_symbol *__restrict info,
                                   void const *symbol_addr) {
	di_debug_addr2line_t a2l_info;
	if (!av_addr2line(&a2l_info, symbol_addr))
		return false;
	if (!a2l_info.al_rawname)
		a2l_info.al_rawname = a2l_info.al_name;
	if (!a2l_info.al_rawname)
		a2l_info.al_rawname = (char *)-1;
	info->s_name  = a2l_info.al_rawname;
	info->s_start = (byte_t const *)a2l_info.al_symstart;
	info->s_end   = (byte_t const *)a2l_info.al_symend;
	return true;
}

PRIVATE ATTR_DBGTEXT struct av_symbol *
NOTHROW(FCALL av_lookup_symbol)(void const *symbol_addr) {
	unsigned int i;
	struct av_symbol *resent = NULL;
#ifdef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
	if unlikely(!ADDR_ISKERN(symbol_addr))
		goto done;
#endif /* CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY */
	for (i = 0; i < lengthof(av_symbol_cache); ++i) {
		if (!av_symbol_cache[i].s_name) {
			if (!resent)
				resent = &av_symbol_cache[i];
			continue;
		}
		if ((byte_t const *)symbol_addr < av_symbol_cache[i].s_start)
			continue;
		if ((byte_t const *)symbol_addr >= av_symbol_cache[i].s_end)
			continue;
		if (av_symbol_cache[i].s_name == (char *)-2)
			return NULL;
		return &av_symbol_cache[i];
	}
	if (!resent) {
		memmovedown(&av_symbol_cache[0], &av_symbol_cache[1],
		            sizeof(av_symbol_cache) - sizeof(av_symbol_cache[0]));
		resent = COMPILER_ENDOF(av_symbol_cache) - 1;
	}
	resent->s_name = NULL;
	if (!av_do_lookup_symbol(resent, symbol_addr)) {
		/* Cache the fact that the given address is unknown. */
		resent->s_name  = (char *)-2;
		resent->s_start = (byte_t const *)symbol_addr;
		resent->s_end   = (byte_t const *)symbol_addr + 1;
		resent = NULL;
	}
#ifdef CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY
done:
#endif /* CONFIG_KERNEL_DEBUGGER_ASMVIEW_ADDR2LINE_IS_KERNEL_ONLY */
	return resent;
}


PRIVATE ATTR_DBGTEXT NONNULL((1)) ssize_t
NOTHROW(LIBDISASM_CC av_symbol_printer)(struct disassembler *__restrict self,
                                        void const *symbol_addr) {
	struct av_symbol *sym;
	/* Semantically speaking, this function behaves identical to the default
	 * symbol printer, in that it will  try to lookup debug information  and
	 * use those to display the names of symbols.
	 * However, since KOS's addr2line function really is quite slow, we extend
	 * on that default functionality by  making use of an intermediate  cache. */
	sym = av_lookup_symbol(symbol_addr);
	if (sym) {
		uintptr_t symbol_offset;
		dbg_putc('<');
		if (sym->s_name != (char *)-1) {
			dbg_print(sym->s_name);
		} else {
			/* If we can't determine the symbol's name, generate one using its address. */
			dbg_printf(DBGSTR("sym_%p"), sym->s_start);
		}
		/* Include the symbol offset (if non-zero) */
		symbol_offset = (size_t)((byte_t const *)symbol_addr - sym->s_start);
		if (symbol_offset != 0)
			disasm_printf(self, "+%#" PRIxPTR, symbol_offset);
		disasm_print(self, ">", 1);
	} else {
		disasm_printf(self, "%#p", symbol_addr);
	}
	return 0;
}


PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_printscreen)(void const *start_addr,
                              void const **psel_addr,
                              bool display_addr2line) {
	struct disassembler da;
	unsigned int line;
	byte_t const *current_line_base = NULL;
	size_t current_line_size = 0;
	void const *sel_addr = *psel_addr;
	size_t maxbytes;
	maxbytes = disasm_default_maxbytes(av_instrlen_da.d_target);
	disasm_init(&da, &dbg_printer, NULL, start_addr,
	            av_instrlen_da.d_target,
	            DISASSEMBLER_FNOADDR | DISASSEMBLER_FNOBYTES, 0);
	da.d_format = &av_format;
	da.d_symbol = &av_symbol_printer;
	dbg_setcur_visible(false);
	line = 0;
	if (display_addr2line)
		line = 1;
	for (; line < dbg_screen_height - 1; ++line) {
		void *line_endaddr;
		size_t i, ilen;
		bool is_current_line;
		dbg_color_t old_default_color;
		byte_t const *line_start = da.d_pc;
		line_endaddr = av_instr_succ(line_start);
		ilen = (size_t)((byte_t *)line_endaddr - line_start);
		is_current_line = sel_addr >= line_start && sel_addr < line_endaddr;
		if (is_current_line) /* Fix a potential address drift. */
			*psel_addr = sel_addr = line_start;
		old_default_color = dbg_getdefaultcolor();
		dbg_setcolor(old_default_color);
		if (is_current_line) {
			current_line_base = line_start;
			current_line_size = ilen;
			dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
		} else {
			dbg_setbgcolor(ANSITTY_CL_BLACK);
		}
		dbg_setdefaultcolor(dbg_getcolor());
		dbg_setcur(0, line);
		dbg_printf(DBGSTR("%p "), line_start);
		if (ilen > maxbytes) {
			for (i = 0; i < maxbytes - 1; ++i) {
				byte_t value;
				if (av_getbyte(da.d_pc + i, &value)) {
					dbg_printf(DBGSTR("%.2" PRIx8 " "), value);
				} else {
					dbg_print(DBGSTR("?? "));
				}
			}
			dbg_print(DBGSTR(".. "));
		} else {
			for (i = 0; i < ilen; ++i) {
				byte_t value;
				if (av_getbyte(da.d_pc + i, &value)) {
					dbg_printf(DBGSTR("%.2" PRIx8 " "), value);
				} else {
					dbg_print(DBGSTR("?? "));
				}
			}
			for (; i < maxbytes; ++i)
				dbg_print(DBGSTR("   "));
		}
		if (!av_disasm_print_instruction(&da)) {
			dbg_print(DBGSTR("??"));
			da.d_pc = (byte_t *)line_endaddr;
		}
		dbg_setdefaultcolor(old_default_color);
		dbg_setcolor(old_default_color);
		{
			unsigned int x;
			for (x = dbg_getcur_x(); x < dbg_screen_width; ++x)
				dbg_putuni(' ');
		}
	}
	dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
	dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
	dbg_pprint(dbg_screen_width - 7, dbg_screen_height - 1, DBGSTR("F1:help"));
	if (current_line_size) {
		size_t i;
		dbg_setcur(0, dbg_screen_height - 1);
		dbg_printf(DBGSTR("%p:"), current_line_base);
		for (i = 0; i < current_line_size; ++i) {
			byte_t value;
			if (i != 0)
				dbg_putc(' ');
			if (av_getbyte(current_line_base + i, &value)) {
				dbg_printf(DBGSTR("%.2" PRIx8), value);
			} else {
				dbg_print(DBGSTR("??"));
			}
		}
	}
	if (display_addr2line) {
		di_debug_addr2line_t a2l;
		if (av_addr2line(&a2l, sel_addr)) {
			dbg_hline(0, 0, dbg_screen_width, ' ');
			dbg_setcur(0, 0);
			dbg_print(a2l.al_srcfile ? a2l.al_srcfile : DBGSTR("?"));
			if (a2l.al_srcline) {
				dbg_printf(DBGSTR(":%3" PRIuPTR), a2l.al_srcline);
				if (a2l.al_srccol)
					dbg_printf(DBGSTR(":%2" PRIuPTR), a2l.al_srccol);
			}
			if (!a2l.al_name)
				a2l.al_name = a2l.al_rawname;
			if (a2l.al_name) {
				dbg_putc(':');
				dbg_print(a2l.al_name);
			}
		}
	}
	return (void *)da.d_pc;
}


/* Re-use the address dialog from hexedit. */
INTDEF ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_hd_addrdiag)(uintptr_t *paddr);



PRIVATE ATTR_DBGRODATA char const av_help[] =
"Esc:        Exit              F1:           Help\n"
"Arrow Keys: Navigate          Pg-Up/Down:   Navigate\n"
"Ctrl+Pg-Up: Go to top         Ctrl+Pg-Down: Go to bottom\n"
"Esc/F1:     Close Help        F2:           Go to address\n"
"A:          Toggle Addr2Line  E:            Open HexEdit"
;

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL av_main)(void *addr) {
	void *start_addr, *end_addr = (void *)-1;
	bool display_addr2line = false;

	/* Fill in the appropriate target for the disassembler. */
	av_instrlen_da.d_target = DISASSEMBLER_TARGET_CURRENT;
#ifdef __x86_64__
	if (dbg_current_iscompat())
		av_instrlen_da.d_target = DISASSEMBLER_TARGET_I386;
#elif defined(__i386__)
#ifndef __I386_NO_VM86
	if (dbg_rt_getregbyidp(DBG_RT_REGLEVEL_VIEW, X86_REGISTER_MISC_EFLAGS) & EFLAGS_VM)
		av_instrlen_da.d_target = DISASSEMBLER_TARGET_8086;
#endif /* !__I386_NO_VM86 */
#endif /* ... */

	start_addr = av_instr_pred_n(addr, (dbg_screen_height - 1) / 2);
	for (;;) {
		unsigned int key;
		if (start_addr > addr)
			start_addr = addr;
		dbg_beginupdate();
		end_addr = av_printscreen(start_addr, (void const **)&addr, display_addr2line);
		if (addr >= end_addr) {
			unsigned int n = dbg_screen_height;
			if (display_addr2line)
				--n;
			while (n) {
				/* Slowly move the screen upwards until the start-address is displayed on-screen. */
				start_addr = av_instr_pred_n(addr, n);
				end_addr   = av_printscreen(start_addr, (void const **)&addr, display_addr2line);
				if (addr < end_addr)
					break;
				--n;
			}
		}
		dbg_endupdate(true);
		do {
			key = dbg_getkey();
		} while (key & KEY_FRELEASED);
		/* TODO: When pressing ENTER, the user should be able to immediately
		 *       go the  target  location  of a  JMP  or  CALL  instruction.
		 *       When  this is done, the previous address should be saved on
		 *       a stack of already-visited locations, which can be returned
		 *       to by pressing BACKSPACE.
		 *       Additionally, there should be a menu to display the current
		 *       contents of said stack. */
		switch (key) {

		case KEY_A:
			display_addr2line = !display_addr2line;
			continue;

		case KEY_E:
			/* Edit the current address in the hex editor.
			 * NOTE: Disable  read-only by default,  since the user may
			 *       with to keep switching back  and forth to look  at
			 *       the generated assembly (in case they choose to use
			 *       this mechanism to re-write assembly code) */
			addr = dbg_hexedit(addr, false);
			continue;

		case KEY_ESC:
			goto done;

		case KEY_UP:
			if (dbg_isholding_ctrl()) {
				start_addr = av_instr_pred(start_addr);
			} else {
				addr = av_instr_pred(addr);
				if (addr < start_addr)
					start_addr = addr;
			}
			continue;

		case KEY_DOWN:
			if (dbg_isholding_ctrl()) {
				start_addr = av_instr_succ(start_addr);
			} else {
				addr = av_instr_succ(addr);
				if (addr >= end_addr)
					start_addr = av_instr_succ(start_addr);
			}
			continue;

		case KEY_PAGEUP:
			if (dbg_isholding_ctrl()) {
				addr = start_addr;
			} else {
				unsigned int n, start_addr_offset;
				n = dbg_screen_height - 1;
				if (display_addr2line)
					--n;
				start_addr_offset = 0;
				while (n) {
					if (addr > start_addr)
						++start_addr_offset;
					addr = av_instr_pred(addr);
					--n;
				}
				start_addr = addr;
				while (start_addr_offset--)
					start_addr = av_instr_pred(start_addr);
			}
			continue;

		case KEY_PAGEDOWN:
			if (dbg_isholding_ctrl()) {
				addr = av_instr_pred(end_addr);
			} else {
				unsigned int n;
				n = dbg_screen_height - 1;
				if (display_addr2line)
					--n;
				while (n--) {
					start_addr = av_instr_succ(start_addr);
					addr       = av_instr_succ(addr);
				}
			}
			break;

		case KEY_F1:
			dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
			dbg_messagebox(DBGSTR("Help"), av_help);
			/* Wait until the user presses ESC or F1 */
			do {
				key = dbg_getkey();
			} while (key != KEY_F1 && key != KEY_ESC);
			continue;

		case KEY_F2: {
			uintptr_t newaddr;
			if (dbg_hd_addrdiag(&newaddr))
				addr = (void *)newaddr;
		}	continue;

		default:
			break;
		}
	}
done:
	return addr;
}





/* Open an interactive assembly viewer at `addr'
 * @return: * : The final selected address when the viewer was closed. */
PUBLIC void *NOTHROW(FCALL dbg_asmview)(void *addr) {
	bool was_cursor_visible;
	void *buf, *result;
	u32 oldcur;

	/* Save terminal settings and display contents. */
	was_cursor_visible = dbg_getcur_visible();
	buf = alloca(dbg_screen_width * dbg_screen_height * dbg_screen_cellsize);
	oldcur = dbg_getcur();
	dbg_logecho_pushoff();
	dbg_savecolor();
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);

	result = av_main(addr);

	/* Restore display contents and terminal settings. */
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_loadcolor();
	dbg_logecho_pop();
	dbg_setcur(DBG_GETCUR_X(oldcur), DBG_GETCUR_Y(oldcur));
	dbg_setcur_visible(was_cursor_visible);
	return result;
}


DBG_COMMAND(a,
            "a [ADDR=faultpc]\n"
            "\tOpen an interactive assembly view at ADDR\n",
            argc, argv) {
	void *addr = dbg_getfaultpcreg(DBG_RT_REGLEVEL_VIEW);
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], (uintptr_t *)&addr))
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	dbg_asmview(addr);
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_ASMVIEW_C */
