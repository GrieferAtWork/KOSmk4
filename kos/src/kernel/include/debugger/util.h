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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_UTIL_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_UTIL_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <stdbool.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

#ifdef __CC__

/* Display a selections menu with a set of `options' (which is a NULL-terminated vector strings)
 * Options  are  on  top  of   each  other,  and  can  be   navigated  using  the  arrow   keys.
 * @return: * : The index of the selected option, or one of `DBG_MENU_SELECTION_*' */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(KCALL dbg_menuex)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          void (KCALL *print_message)(void *arg),
                          void *arg);
FUNDEF WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(VCALL dbg_menuf)(char const *__restrict title,
                         char const *const *__restrict options,
                         unsigned int default_option,
                         char const *__restrict message_format,
                         ...);
FUNDEF WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(KCALL dbg_vmenuf)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          char const *__restrict message_format,
                          __builtin_va_list args);
#define DBG_MENU_SELECTION_CANCEL  ((unsigned int)-1) /* The user pressed ESC */

/* Print a messagebox centered on-screen. */
FUNDEF void NOTHROW(KCALL dbg_messagebox)(char const *__restrict title,
                                          char const *__restrict text);

/* Open an interactive hex editor at `addr'
 * @param: is_readonly: When true, enable read-only mode by default
 * @return: * : The final selected address when the editor was closed. */
FUNDEF void *NOTHROW(FCALL dbg_hexedit)(void *addr, bool is_readonly DFL(false));

/* Open an interactive assembly viewer at `addr'
 * @return: * : The final selected address when the viewer was closed. */
FUNDEF void *NOTHROW(FCALL dbg_asmview)(void *addr);

/* Process input for an edit  field at the given position,  allowing
 * the user to type in input text, with that text then being written
 * to the given `buf'.
 * Note that if `buf' is non-empty (buf[0] != '\0') upon entry,
 * editing will  resume  with  the current  contents  of  `buf'
 * @param: pcursor_pos:  [0..1][in|out]: The index where the cursor starts out/ends up
 * @param: pscreen_left: [0..1][in|out]: The index of the left-most visible character
 * @param: return_on_changed: When true, return `DBG_EDITFIELD_RETURN_CHANGED' after any
 *                            kind  of user-input that  changes `buf', `pcursor_pos', or
 *                            `pscreen_left' and doesn't already return one of the other
 *                            return codes.
 * @return: * : One of `DBG_EDITFIELD_RETURN_*' */
FUNDEF unsigned int
NOTHROW(FCALL dbg_editfield)(int x, int y, unsigned int field_width,
                             char *buf, size_t buflen,
                             size_t *pcursor_pos DFL(__NULLPTR),
                             size_t *pscreen_left DFL(__NULLPTR),
                             __BOOL return_on_changed DFL(0));
#define DBG_EDITFIELD_RETURN_ENTER     0 /* Enter (confirm) */
#define DBG_EDITFIELD_RETURN_TAB       1 /* Tab (go to next field?) */
#define DBG_EDITFIELD_RETURN_SHIFT_TAB 2 /* Shift+Tab (go to next field?) */
#define DBG_EDITFIELD_RETURN_ESC       3 /* ESC was pressed */
#define DBG_EDITFIELD_RETURN_UP        4 /* Up was pressed */
#define DBG_EDITFIELD_RETURN_DOWN      5 /* Down was pressed */
#define DBG_EDITFIELD_RETURN_CTRL_C    6 /* CTRL+C was pressed */
#define DBG_EDITFIELD_RETURN_CTRL_D    7 /* CTRL+D was pressed */
#define DBG_EDITFIELD_RETURN_CHANGED   8 /* Text has changed (only when `return_on_changed' is `true') */
#define DBG_EDITFIELD_RETURN_F(n)      (16 + ((n)-1)) /* Fn key was pressed */

/* Same as `dbg_editfield()', but only draw the edit field. */
FUNDEF void
NOTHROW(FCALL dbg_draweditfield)(int x, int y, unsigned int field_width,
                                 char *buf, size_t buflen,
                                 size_t const *pcursor_pos DFL(__NULLPTR),
                                 size_t const *pscreen_left DFL(__NULLPTR));


/* Evaluate an address expression
 * @param: flags:  Set of `DBG_EVALADDR_FLAG_*'
 * @return: true:  Evaluation failed. (when `DBG_EVALADDR_FLAG_NO_ERROR' wasn't set,
 *                                     an error was already displayed to the user)
 * @return: false: Evaluation failed. */
FUNDEF bool NOTHROW(FCALL dbg_evaladdr)(char const *__restrict expr,
                                        uintptr_t *__restrict presult,
                                        unsigned int flags DFL(0));
#define dbg_evalexpr(expr, presult) dbg_evaladdr(expr, presult, DBG_EVALADDR_FLAG_NO_HEX)
#define DBG_EVALADDR_FLAG_NO_ERROR  0x0001 /* Don't show an error message describing what's wrong with the syntax. */
#define DBG_EVALADDR_FLAG_NO_HEX    0x0002 /* When not set, `512' is `0x512', else it is decimal. Regardless of this,
                                            * `5C2'  is  always  hex,  and  `+512'  or  `(512)'  are  always decimal.
                                            * This flag only affects top-level integral constants. */



/* Print addr2line optimized for the debugger.
 * Example   (of    an   inlined    function):
 * >> c010783a+4   [my_inline_function+8] [bar.c:9]
 * >> c0107828+38  [my_function+26] [bar.c:42]
 * This is similar to `addr2line_printf()', however doesn't include the full source path,
 * and doesn't follow the file(line,col) format, but instead opts for much shorter  lines
 * which can then (usually) be displayed in one continuous line, rather than having to be
 * split up into multiple lines.
 * Additionally, this function also highlights output using differing colors. */
FUNDEF void
NOTHROW(VCALL dbg_addr2line_printf)(void const *start_pc, void const *end_pc,
                                    char const *message_format, ...);
FUNDEF void
NOTHROW(KCALL dbg_addr2line_vprintf)(void const *start_pc, void const *end_pc,
                                     char const *message_format, __builtin_va_list args);


#ifndef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
/* Helper wrappers to  determine the predecessor/successor  of a given  `pc',
 * which is allowed to point into user-space, in which case user-space memory
 * is accessed through use of `dbg_readmemory()', rather than direct  access. */
FUNDEF ATTR_PURE WUNUSED byte_t *NOTHROW(LIBINSTRLEN_CC dbg_instruction_succ_nx)(void const *pc, isa_t isa);
FUNDEF ATTR_PURE WUNUSED byte_t *NOTHROW(LIBINSTRLEN_CC dbg_instruction_pred_nx)(void const *pc, isa_t isa);
FUNDEF ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *NOTHROW(LIBINSTRLEN_CC dbg_instruction_trysucc)(void const *pc, isa_t isa);
FUNDEF ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *NOTHROW(LIBINSTRLEN_CC dbg_instruction_trypred)(void const *pc, isa_t isa);
#else /* !LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
#define dbg_instruction_succ_nx(pc, isa) instruction_succ_nx(pc, isa)
#define dbg_instruction_pred_nx(pc, isa) instruction_pred_nx(pc, isa)
#define dbg_instruction_trysucc(pc, isa) instruction_trysucc(pc, isa)
#define dbg_instruction_trypred(pc, isa) instruction_trypred(pc, isa)
#endif /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */


#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_UTIL_H */
