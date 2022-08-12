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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_HOOK_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_HOOK_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/mman/driver.h>
#include <kernel/types.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>
#include <hybrid/pp/__va_nargs.h>

#include <asm/asmword.h>

#include <libc/string.h>

DECL_BEGIN

/* General calling convention for debugger hooks. */
#ifndef DBG_CALL
#define DBG_CALL VCALL
#endif /* !DBG_CALL */


/* Attributes to-be given to debugger-related data/text objects. */
#define ATTR_DBGTEXT        ATTR_COLDTEXT
#define ATTR_DBGRODATA      ATTR_COLDRODATA
#define ATTR_DBGSTRINGS     ATTR_DBGRODATA
#define ATTR_DBGDATA        ATTR_COLDDATA
#define ATTR_DBGBSS         ATTR_COLDBSS
#define ATTR_DBGTEXT_S(x)   ATTR_COLDTEXT_S(x)
#define ATTR_DBGRODATA_S(x) ATTR_COLDRODATA_S(x)
#define ATTR_DBGDATA_S(x)   ATTR_COLDDATA_S(x)
#define ATTR_DBGBSS_S(x)    ATTR_COLDBSS_S(x)
#define DBGSTR(s)           XBLOCK({ PRIVATE ATTR_DBGSTRINGS char const _dbg_str[] = s; XRETURN _dbg_str; })





/* Optional,  per-module  section  containing  debugger  hooks.
 * This section  contains an  arbitrary number  of hooks,  each
 * of which follows the layout mandated by `struct dbg_hookhdr'
 * The hooks array can be terminated in a couple of ways:
 *   - By simply reaching the end of the .dbg.hooks section (intended method)
 *   - By encountering a hook with a `dh_size' field `< sizeof(struct dbg_hookhdr)'
 *   - By encountering a hook with a `dh_size' field `> REMAINING_SPACE_IN_SECTION' */
#define DBG_SECTION_HOOKS    ".dbg.hooks"
#define DBG_SECTION_HOOKS_RAW .dbg.hooks

/* Place some object into the .dbg.hooks section. */
#define ATTR_DBG_HOOK ATTR_SECTION(DBG_SECTION_HOOKS)


/* Values for `dbg_hookhdr::dh_flag' */
#define DBG_HOOKFLAG_NORMAL   0x00 /* Normal hook flags */
#define DBG_HOOKFLAG_RELATIVE 0x01 /* Pointers to other components defined in this hook are
                                    * relative to the base-address (i.e. `drv_loadaddr') of
                                    * the module containing the hook. */
#define DBG_HOOKFLAG_OFFSET   0x02 /* Pointers to other components defined in this hook are self-relative. */
#define DBG_HOOKFLAG_SPECIFIC 0xf0 /* Mask  of  flags who's  meaning depends  on `dh_type'
                                    * If not specified otherwise, undefined bits masked by
                                    * this must be set to 0 */


/* Values for `dbg_hookhdr::dh_type' */
#define DBG_HOOK_IGNORED 0x00 /* Ignore this hook. */
#define DBG_HOOK_MORE    0x01 /* `struct dbg_morehook' (Dynamically define additional debugger hooks) */
#define DBG_HOOK_COMMAND 0x02 /* `struct dbg_commandhook' */
#define DBG_HOOK_INIT    0x03 /* `struct dbg_inithook' (invoke a function after debugger initialization) */
#define DBG_HOOK_RESET   0x04 /* `struct dbg_resethook' (invoke a function during debugger reset (an initial reset always happens after init!)) */
#define DBG_HOOK_FINI    0x05 /* `struct dbg_finihook' (invoke a function before debugger finalization) */
#define DBG_HOOK_CLEAR   0x06 /* `struct dbg_clearhook' (specify a data block that should be bzero()-ed while inside the debugger, but restored after) */
#define DBG_HOOK_CLEARIF 0x07 /* `struct dbg_clearifhook' (Same as `DBG_HOOK_CLEAR', but determine the object to-be cleared dynamically) */

#define _DBG_PRIVATE_HOOKSTRUCT_0x01 struct dbg_morehook
#define _DBG_PRIVATE_HOOKSTRUCT_0x02 struct dbg_commandhook
#define _DBG_PRIVATE_HOOKSTRUCT_0x03 struct dbg_inithook
#define _DBG_PRIVATE_HOOKSTRUCT_0x04 struct dbg_resethook
#define _DBG_PRIVATE_HOOKSTRUCT_0x05 struct dbg_finihook
#define _DBG_PRIVATE_HOOKSTRUCT_0x06 struct dbg_clearhook
#define _DBG_PRIVATE_HOOKSTRUCT_0x07 struct dbg_clearifhook
#define _DBG_PRIVATE_HOOKSTRUCT(type) _DBG_PRIVATE_HOOKSTRUCT_##type


/* Helper macros for defining embedded debugger hooks. */
#if __SIZEOF_POINTER__ <= 4
#define _DBG_HOOK_ASMWORD_TYPE .word8
#define _DBG_HOOK_ASMWORD_FLAG .word8
#define _DBG_HOOK_ASMWORD_SIZE .word16
#else /* __SIZEOF_POINTER__ <= 4 */
#define _DBG_HOOK_ASMWORD_TYPE .word16
#define _DBG_HOOK_ASMWORD_FLAG .word16
#define _DBG_HOOK_ASMWORD_SIZE .word32
#endif /* __SIZEOF_POINTER__ > 4 */

#ifdef BUILDING_KERNEL_CORE
#define _DBG_HOOK_ASMWORD_RELPTR                .wordptr
#define _DBG_HOOK_ASMWORD_RELPTRO(base, offset) .wordptr base + offset
#define _DBG_HOOK_ASMWORD_FLAGS                 0
#else /* BUILDING_KERNEL_CORE */
#ifdef __ARCH_HAVE_wordrel
#define _DBG_HOOK_ASMWORD_RELPTR                .wordrel
#define _DBG_HOOK_ASMWORD_RELPTRO(base, offset) .wordrel base, offset
#define _DBG_HOOK_ASMWORD_FLAGS                 DBG_HOOKFLAG_RELATIVE
#elif defined(__ARCH_HAVE_wordoff)
#define _DBG_HOOK_ASMWORD_RELPTR                .wordoff
#define _DBG_HOOK_ASMWORD_RELPTRO(base, offset) .wordoff base, offset
#define _DBG_HOOK_ASMWORD_FLAGS                 DBG_HOOKFLAG_OFFSET
#else /* ... */
#error "No way to implement `_DBG_HOOK_ASMWORD_RELPTR'"
#endif /* !... */
#endif /* !BUILDING_KERNEL_CORE */


#ifdef __CC__
typedef uintptr_quarter_t dbg_hook_type_t;
typedef uintptr_quarter_t dbg_hook_flag_t;
typedef uintptr_half_t    dbg_hook_size_t;
struct dbg_hookhdr {
	dbg_hook_type_t                 dh_type;  /* Hook descriptor type (one of `DBG_HOOK_*') */
	dbg_hook_flag_t                 dh_flag;  /* Hook descriptor type (one of `DBG_HOOKFLAG_*') */
	dbg_hook_size_t                 dh_size;  /* Hook descriptor size (including this header) */
	COMPILER_FLEXIBLE_ARRAY(byte_t, dh_data); /* [dh_size] Hook data payload. */
};
#endif /* __CC__ */




/* Provide additional (possibly dynamically extended) debugger hooks.
 * WARNING: This type of hook _CANNOT_ be used recursively!
 *          When encountered recursively, the hook will simply be ignored,
 *          thus preventing loops from being formed, which might otherwise
 *          cause the debugger to hang. */
#ifdef __CC__
struct dbg_morehook {
	dbg_hook_type_t     dm_type; /* == DBG_HOOK_MORE */
	dbg_hook_flag_t     dm_flag; /* ... */
	dbg_hook_size_t     dm_size; /* == sizeof(struct dbg_morehook) */
	struct dbg_hookhdr *dm_more; /* [1..dm_limt] Pointer to additional debugger hooks. */
	size_t              dm_limt; /* # of bytes of additional debugger hooks. */
};
#endif /* __CC__ */





/* Special return values for debug functions. */
#define DBG_STATUS_ISOK(status)      ((status) >= 0)
#define DBG_STATUS_INVALID_ARGUMENTS (-1) /* Invalid argument list (when returned by `dbg_command_t()',
                                           * caller will print a generic error message) */
#define DBG_STATUS_BAD_COMMAND       (-2) /* No command exists that matches the typed up command name. */



/* Additional flags for `struct dbg_commandhook::dh_flag' */
#define DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE 0x10 /* Options listed  by the  auto-completion callback  are exclusive,  in
                                                 * that no other options are accepted than those that can be enumerated
                                                 * by the auto-completion callback (if no auto-completion callback  was
                                                 * specified, then the  function doesn't accept  any argument and  will
                                                 * return  `DBG_STATUS_INVALID_ARGUMENTS'   whenever  `argc != 1'   (1,
                                                 * because argv[0] is the name of the function))
                                                 * When this flag is set, the commandline changes its color (to red)
                                                 * whenever  the word currently being written can no longer be auto-
                                                 * completed (the same way it  changes color when the typed  command
                                                 * name doesn't match any known command) */

/* Debugger command provider hook */
#ifdef __CC__
/* The prototype for the callback of a debugger service function.
 * @return: * :                             Command exit code.
 * @return: DBG_STATUS_INVALID_ARGUMENTS: Invalid arguments (caller should print a generic error message) */
typedef intptr_t (DBG_CALL *dbg_command_t)(size_t argc, char *argv[]);

/* Callback prototype for `dbg_autocomplete_t()' */
typedef void (DBG_CALL *dbg_autocomplete_cb_t)(void *arg, char const *name, size_t namelen);

/* Enumerate a  list of  possible words  that may  follow  after
 * argc+argv by invoking `(*cb)(arg, ...)' for each possibility.
 * @param: starts_with: (optional) When non-NULL (and non-empty), the function
 *                       is allowed to only enumerate auto-completion options
 *                       that   start   with   the   C-string   `starts_with' */
typedef void (DBG_CALL *dbg_autocomplete_t)(size_t argc, char *argv[],
                                            dbg_autocomplete_cb_t cb, void *arg,
                                            char const *starts_with,
                                            size_t starts_with_len);

#define _DBG_PRIVATE_AUTOCOMPLETE_5(name, argc, argv, cb, arg) \
	PRIVATE ATTR_USED void DBG_CALL                            \
	autocomplete_##name(size_t argc, char *argv[], dbg_autocomplete_cb_t cb, void *arg)
#define _DBG_PRIVATE_AUTOCOMPLETE_6(name, argc, argv, cb, arg, starts_with)  \
	PRIVATE ATTR_USED void DBG_CALL                                          \
	autocomplete_##name(size_t argc, char *argv[], dbg_autocomplete_cb_t cb, \
	                    void *arg, void *arg, char const *starts_with)
#define _DBG_PRIVATE_AUTOCOMPLETE_7(name, argc, argv, cb, arg, starts_with, starts_with_len) \
	PRIVATE ATTR_USED void DBG_CALL                                                          \
	autocomplete_##name(size_t argc, char *argv[], dbg_autocomplete_cb_t cb,                 \
	                    void *arg, char const *starts_with, size_t starts_with_len)

/* Overload:
 * >> DBG_AUTOCOMPLETE(Symbol name, Symbol argc, Symbol argv, Symbol cb, Symbol arg) { ... }
 * >> DBG_AUTOCOMPLETE(Symbol name, Symbol argc, Symbol argv, Symbol cb, Symbol arg, Symbol starts_with) { ... }
 * >> DBG_AUTOCOMPLETE(Symbol name, Symbol argc, Symbol argv, Symbol cb, Symbol arg, Symbol starts_with, Symbol starts_with_len) { ... }
 * NOTE: All arguments (except for `name') are the names of the parameters passed to the function. */
#define DBG_AUTOCOMPLETE(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_AUTOCOMPLETE_, (__VA_ARGS__))(__VA_ARGS__)

struct dbg_commandhook {
	dbg_hook_type_t    dc_type; /* == DBG_HOOK_COMMAND */
	dbg_hook_flag_t    dc_flag; /* ... */
	dbg_hook_size_t    dc_size; /* >= offsetafter(struct dbg_commandhook, dc_main) &&
	                             * <=  offsetafter(struct  dbg_commandhook,  dc_auto) */
	char const        *dc_name; /* [1..1][const] The function's name. */
	dbg_command_t      dc_main; /* [1..1][const] The function's callback. */
	char const        *dc_help; /* [0..1][const] An optional help string for the function. */
	dbg_autocomplete_t dc_auto; /* [0..1][const] An optional callback for tab-auto-completion. */
};
#define dbg_commandhook_hashelp(self) ((self)->dc_size >= COMPILER_OFFSETAFTER(struct dbg_commandhook, dc_help))
#define dbg_commandhook_hasauto(self) ((self)->dc_size >= COMPILER_OFFSETAFTER(struct dbg_commandhook, dc_auto))

/* Invoke the given debugger command hook with the given argc/argv */
#define dbg_commandhook_exec(self, argc, argv)                  \
	((((self)->dc_flag & DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE) && \
	  (argc) > 1 && !dbg_commandhook_hasauto(self))             \
	 ? DBG_STATUS_INVALID_ARGUMENTS                             \
	 : (*(self)->dc_main)(argc, argv))

#endif /* __CC__ */

#define _DBG_PRIVATE_DEFHOOK_COMMAND_3(name, main, flags)                                 \
	__ASM_BEGIN                                                                           \
	__ASM_L(.pushsection DBG_SECTION_HOOKS_RAW, "a")                                      \
	__ASM_L(	/*dc_type*/ _DBG_HOOK_ASMWORD_TYPE   DBG_HOOK_COMMAND)                    \
	__ASM_L(	/*dc_flag*/ _DBG_HOOK_ASMWORD_FLAG   ((flags) | _DBG_HOOK_ASMWORD_FLAGS)) \
	__ASM_L(	/*dc_size*/ _DBG_HOOK_ASMWORD_SIZE   (3 * __SIZEOF_POINTER__))            \
	__ASM_L(	/*dc_name*/ _DBG_HOOK_ASMWORD_RELPTR name)                                \
	__ASM_L(	/*dc_main*/ _DBG_HOOK_ASMWORD_RELPTR main)                                \
	__ASM_L(.popsection)                                                                  \
	__ASM_END
#define _DBG_PRIVATE_DEFHOOK_COMMAND_4(name, main, flags, help)                           \
	__ASM_BEGIN                                                                           \
	__ASM_L(.pushsection DBG_SECTION_HOOKS_RAW, "a")                                      \
	__ASM_L(	/*dc_type*/ _DBG_HOOK_ASMWORD_TYPE   DBG_HOOK_COMMAND)                    \
	__ASM_L(	/*dc_flag*/ _DBG_HOOK_ASMWORD_FLAG   ((flags) | _DBG_HOOK_ASMWORD_FLAGS)) \
	__ASM_L(	/*dc_size*/ _DBG_HOOK_ASMWORD_SIZE   (4 * __SIZEOF_POINTER__))            \
	__ASM_L(	/*dc_name*/ _DBG_HOOK_ASMWORD_RELPTR name)                                \
	__ASM_L(	/*dc_main*/ _DBG_HOOK_ASMWORD_RELPTR main)                                \
	__ASM_L(	/*dc_help*/ _DBG_HOOK_ASMWORD_RELPTR help)                                \
	__ASM_L(.popsection)                                                                  \
	__ASM_END
#define _DBG_PRIVATE_DEFHOOK_COMMAND_5(name, main, flags, help, auto)                     \
	__ASM_BEGIN                                                                           \
	__ASM_L(.pushsection DBG_SECTION_HOOKS_RAW, "a")                                      \
	__ASM_L(	/*dc_type*/ _DBG_HOOK_ASMWORD_TYPE   DBG_HOOK_COMMAND)                    \
	__ASM_L(	/*dc_flag*/ _DBG_HOOK_ASMWORD_FLAG   ((flags) | _DBG_HOOK_ASMWORD_FLAGS)) \
	__ASM_L(	/*dc_size*/ _DBG_HOOK_ASMWORD_SIZE   (5 * __SIZEOF_POINTER__))            \
	__ASM_L(	/*dc_name*/ _DBG_HOOK_ASMWORD_RELPTR name)                                \
	__ASM_L(	/*dc_main*/ _DBG_HOOK_ASMWORD_RELPTR main)                                \
	__ASM_L(	/*dc_help*/ _DBG_HOOK_ASMWORD_RELPTR help)                                \
	__ASM_L(	/*dc_help*/ _DBG_HOOK_ASMWORD_RELPTR auto)                                \
	__ASM_L(.popsection)                                                                  \
	__ASM_END

/* Overload:
 * >> DBG_DEFHOOK_COMMAND(char const name[], dbg_command_t main, unsigned int flags);
 * >> DBG_DEFHOOK_COMMAND(char const name[], dbg_command_t main, unsigned int flags, char const help[]);
 * >> DBG_DEFHOOK_COMMAND(char const name[], dbg_command_t main, unsigned int flags, char const help[], dbg_autocomplete_t auto);
 * NOTE: All arguments must be pre-defined symbols. */
#define DBG_DEFHOOK_COMMAND(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_DEFHOOK_COMMAND_, (__VA_ARGS__))(__VA_ARGS__)


#ifdef __CC__
#define _DBG_PRIVATE_COMMAND_IMPL3_NOARGS(flags, id, name)                                                      \
	PRIVATE intptr_t DBG_CALL dbg_command_##id(void);                                                           \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandname_##id[] ASMNAME("dbg_commandname_" #id) = name; \
	_DBG_PRIVATE_DEFHOOK_COMMAND_3(dbg_commandname_##id, dbg_command_##id,                                      \
	                               flags);                                                                      \
	PRIVATE ATTR_USED ATTR_DBGTEXT intptr_t DBG_CALL dbg_command_##id(void)
#define _DBG_PRIVATE_COMMAND_IMPL4_NOARGS(flags, id, name, help)                                                \
	PRIVATE intptr_t DBG_CALL dbg_command_##id(void);                                                           \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandname_##id[] ASMNAME("dbg_commandname_" #id) = name; \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandhelp_##id[] ASMNAME("dbg_commandhelp_" #id) = help; \
	_DBG_PRIVATE_DEFHOOK_COMMAND_4(dbg_commandname_##id, dbg_command_##id,                                      \
	                               flags, dbg_commandhelp_##id);                                                \
	PRIVATE ATTR_USED ATTR_DBGTEXT intptr_t DBG_CALL dbg_command_##id(void)
#define _DBG_PRIVATE_COMMAND_IMPL4(flags, id, name, help, argc, argv)                                           \
	PRIVATE intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[]);                                      \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandname_##id[] ASMNAME("dbg_commandname_" #id) = name; \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandhelp_##id[] ASMNAME("dbg_commandhelp_" #id) = help; \
	_DBG_PRIVATE_DEFHOOK_COMMAND_4(dbg_commandname_##id, dbg_command_##id,                                      \
	                               flags, dbg_commandhelp_##id);                                                \
	PRIVATE ATTR_USED ATTR_DBGTEXT intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[])
#define _DBG_PRIVATE_COMMAND_IMPL5(id, name, auto, flags, help, argc, argv)                                     \
	PRIVATE intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[]);                                      \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandname_##id[] ASMNAME("dbg_commandname_" #id) = name; \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandhelp_##id[] ASMNAME("dbg_commandhelp_" #id) = help; \
	_DBG_PRIVATE_DEFHOOK_COMMAND_5(dbg_commandname_##id, dbg_command_##id,                                      \
	                               flags, dbg_commandhelp_##id, auto);                                          \
	PRIVATE ATTR_USED ATTR_DBGTEXT intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[])
#define _DBG_PRIVATE_COMMAND_IMPL5_NOHELP(id, name, auto, flags, argc, argv)                                    \
	PRIVATE intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[]);                                      \
	PRIVATE ATTR_USED ATTR_DBGSTRINGS char const dbg_commandname_##id[] ASMNAME("dbg_commandname_" #id) = name; \
	_DBG_PRIVATE_DEFHOOK_COMMAND_5(dbg_commandname_##id, dbg_command_##id,                                      \
	                               flags, 0, auto);                                                             \
	PRIVATE ATTR_USED ATTR_DBGTEXT intptr_t DBG_CALL dbg_command_##id(size_t argc, char *argv[])
#define _DBG_PRIVATE_COMMAND_1(id)                                _DBG_PRIVATE_COMMAND_IMPL3_NOARGS(DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE, id, #id)
#define _DBG_PRIVATE_COMMAND_2(id, help)                          _DBG_PRIVATE_COMMAND_IMPL4_NOARGS(DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE, id, #id, help)
#define _DBG_PRIVATE_COMMAND_4(id, help, argc, argv)              _DBG_PRIVATE_COMMAND_IMPL4(0, id, #id, help, argc, argv)
#define _DBG_PRIVATE_COMMAND_5(id, auto, help, argc, argv)        _DBG_PRIVATE_COMMAND_IMPL5(id, #id, auto, 0, help, argc, argv)
#define _DBG_PRIVATE_COMMAND_6(id, auto, flags, help, argc, argv) _DBG_PRIVATE_COMMAND_IMPL5(id, #id, auto, flags, help, argc, argv)

#define _DBG_PRIVATE_COMMAND_AUTO_3(id, argc, argv)              _DBG_PRIVATE_COMMAND_IMPL5_NOHELP(id, #id, autocomplete_##id, 0, argc, argv)
#define _DBG_PRIVATE_COMMAND_AUTO_4(id, help, argc, argv)        _DBG_PRIVATE_COMMAND_IMPL5(id, #id, autocomplete_##id, 0, help, argc, argv)
#define _DBG_PRIVATE_COMMAND_AUTO_5(id, flags, help, argc, argv) _DBG_PRIVATE_COMMAND_IMPL5(id, #id, autocomplete_##id, flags, help, argc, argv)

#define _DBG_PRIVATE_NAMED_COMMAND_2(id, name)                                _DBG_PRIVATE_COMMAND_IMPL3_NOARGS(DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE, id, name)
#define _DBG_PRIVATE_NAMED_COMMAND_3(id, name, help)                          _DBG_PRIVATE_COMMAND_IMPL4_NOARGS(DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE, id, name, help)
#define _DBG_PRIVATE_NAMED_COMMAND_5(id, name, help, argc, argv)              _DBG_PRIVATE_COMMAND_IMPL4(0, id, name, help, argc, argv)
#define _DBG_PRIVATE_NAMED_COMMAND_6(id, name, auto, help, argc, argv)        _DBG_PRIVATE_COMMAND_IMPL5(id, name, auto, 0, help, argc, argv)
#define _DBG_PRIVATE_NAMED_COMMAND_7(id, name, auto, flags, help, argc, argv) _DBG_PRIVATE_COMMAND_IMPL5(id, name, auto, flags, help, argc, argv)

#define _DBG_PRIVATE_NAMED_COMMAND_AUTO_4(id, name, argc, argv)              _DBG_PRIVATE_COMMAND_IMPL5_NOHELP(id, name, autocomplete_##id, 0, argc, argv)
#define _DBG_PRIVATE_NAMED_COMMAND_AUTO_5(id, name, help, argc, argv)        _DBG_PRIVATE_COMMAND_IMPL5(id, name, autocomplete_##id, 0, help, argc, argv)
#define _DBG_PRIVATE_NAMED_COMMAND_AUTO_6(id, name, flags, help, argc, argv) _DBG_PRIVATE_COMMAND_IMPL5(id, name, autocomplete_##id, flags, help, argc, argv)

/* Overload:
 * >> DBG_COMMAND(Keyword name) { ... }
 * >> DBG_COMMAND(Keyword name, char const help[]) { ... }
 * >> DBG_COMMAND(Keyword name, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_COMMAND(Keyword name, Keyword autocomplete, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_COMMAND(Keyword name, Keyword autocomplete, unsigned int flags, char const help[], Keyword argc, Keyword argv) { ... } */
#define DBG_COMMAND(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_COMMAND_, (__VA_ARGS__))(__VA_ARGS__)

/* Overload:
 * >> DBG_COMMAND_AUTO(Keyword name, Keyword argc, Keyword argv) { ... }
 * >> DBG_COMMAND_AUTO(Keyword name, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_COMMAND_AUTO(Keyword name, unsigned int flags, char const help[], Keyword argc, Keyword argv) { ... } */
#define DBG_COMMAND_AUTO(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_COMMAND_AUTO_, (__VA_ARGS__))(__VA_ARGS__)

/* Overload:
 * >> DBG_NAMED_COMMAND(Keyword id, String name) { ... }
 * >> DBG_NAMED_COMMAND(Keyword id, String name, char const help[]) { ... }
 * >> DBG_NAMED_COMMAND(Keyword id, String name, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_NAMED_COMMAND(Keyword id, String name, Keyword autocomplete, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_NAMED_COMMAND(Keyword id, String name, Keyword autocomplete, unsigned int flags, char const help[], Keyword argc, Keyword argv) { ... } */
#define DBG_NAMED_COMMAND(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_NAMED_COMMAND_, (__VA_ARGS__))(__VA_ARGS__)

/* Overload:
 * >> DBG_NAMED_COMMAND_AUTO(Keyword id, String name, Keyword argc, Keyword argv) { ... }
 * >> DBG_NAMED_COMMAND_AUTO(Keyword id, String name, char const help[], Keyword argc, Keyword argv) { ... }
 * >> DBG_NAMED_COMMAND_AUTO(Keyword id, String name, unsigned int flags, char const help[], Keyword argc, Keyword argv) { ... } */
#define DBG_NAMED_COMMAND_AUTO(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_NAMED_COMMAND_AUTO_, (__VA_ARGS__))(__VA_ARGS__)

#endif /* __CC__ */




#ifdef __CC__
typedef void (DBG_CALL *dbg_init_t)(void);
typedef void (DBG_CALL *dbg_reset_t)(void);
typedef void (DBG_CALL *dbg_fini_t)(void);
struct dbg_inithook {
	dbg_hook_type_t di_type; /* == DBG_HOOK_INIT */
	dbg_hook_flag_t di_flag; /* ... */
	dbg_hook_size_t di_size; /* == sizeof(struct dbg_inithook) */
	dbg_init_t      di_func; /* [1..1][const] The function that should be invoked. */
};
struct dbg_resethook {
	dbg_hook_type_t dr_type; /* == DBG_HOOK_RESET */
	dbg_hook_flag_t dr_flag; /* ... */
	dbg_hook_size_t dr_size; /* == sizeof(struct dbg_resethook) */
	dbg_reset_t     dr_func; /* [1..1][const] The function that should be invoked. */
};
struct dbg_finihook {
	dbg_hook_type_t df_type; /* == DBG_HOOK_FINI */
	dbg_hook_flag_t df_flag; /* ... */
	dbg_hook_size_t df_size; /* == sizeof(struct dbg_finihook) */
	dbg_fini_t      df_func; /* [1..1][const] The function that should be invoked. */
};
#endif /* __CC__ */
#define __DBG_DEFHOOK_CB(type, func)                                           \
	__ASM_BEGIN                                                                \
	__ASM_L(.pushsection DBG_SECTION_HOOKS_RAW, "a")                           \
	__ASM_L(	/*d?_type*/ _DBG_HOOK_ASMWORD_TYPE   type)                     \
	__ASM_L(	/*d?_flag*/ _DBG_HOOK_ASMWORD_FLAG   _DBG_HOOK_ASMWORD_FLAGS)  \
	__ASM_L(	/*d?_size*/ _DBG_HOOK_ASMWORD_SIZE   (2 * __SIZEOF_POINTER__)) \
	__ASM_L(	/*d?_func*/ _DBG_HOOK_ASMWORD_RELPTR func)                     \
	__ASM_L(.popsection)                                                       \
	__ASM_END
#define DBG_DEFHOOK_INIT(func)  __DBG_DEFHOOK_CB(DBG_HOOK_INIT, func)
#define DBG_DEFHOOK_RESET(func) __DBG_DEFHOOK_CB(DBG_HOOK_RESET, func)
#define DBG_DEFHOOK_FINI(func)  __DBG_DEFHOOK_CB(DBG_HOOK_FINI, func)

#ifdef __CC__
#define _DBG_PRIVATE_INIT(func)                  \
	PRIVATE void DBG_CALL dbg_init_##func(void); \
	DBG_DEFHOOK_INIT(dbg_init_##func);           \
	PRIVATE ATTR_USED ATTR_DBGTEXT void DBG_CALL dbg_init_##func(void)
#define _DBG_PRIVATE_RESET(func)                  \
	PRIVATE void DBG_CALL dbg_reset_##func(void); \
	DBG_DEFHOOK_RESET(dbg_reset_##func);          \
	PRIVATE ATTR_USED ATTR_DBGTEXT void DBG_CALL dbg_reset_##func(void)
#define _DBG_PRIVATE_FINI(func)                  \
	PRIVATE void DBG_CALL dbg_fini_##func(void); \
	DBG_DEFHOOK_FINI(dbg_fini_##func);           \
	PRIVATE ATTR_USED ATTR_DBGTEXT void DBG_CALL dbg_fini_##func(void)
/* >> void KCALL func(void);
 * Define a debug initializer/reset/finalizer function
 * INIT: Called whenever the debugger is entered (not called upon recursive re-entry)
 * FINI:  Called whenever the debugger is exited
 * RESET: Called whenever the debugger is entered (after INIT, including on recursive re-entry) */
#define DBG_INIT(func)  _DBG_PRIVATE_INIT(func)
#define DBG_RESET(func) _DBG_PRIVATE_RESET(func)
#define DBG_FINI(func)  _DBG_PRIVATE_FINI(func)
#endif /* __CC__ */


#define DEFINE_DBG_FINI(func)  DEFINE_CALLBACK(DBG_SECTION_FINI, func)






#ifdef __CC__
struct dbg_clearhook {
	dbg_hook_type_t                 dc_type;  /* == DBG_HOOK_CLEAR */
	dbg_hook_flag_t                 dc_flag;  /* ... */
	dbg_hook_size_t                 dc_size;  /* == offsetof(struct dbg_clearhook, dc_data) + CLEAR_OBJECT_SIZE */
	void                           *dc_cobj;  /* [1..1][const] Pointer to the object that should be cleared. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, dc_data); /* Object data backup blob. (valid while inside of the debugger) */
};
#endif /* __CC__ */

#define _DBG_PRIVATE_CLEAR_2(start_symbol, size) \
	_DBG_PRIVATE_CLEAR_3(start_symbol, 0, size)
#define _DBG_PRIVATE_CLEAR_3(start_symbol, start_offset, size)                          \
	__ASM_BEGIN                                                                         \
	__ASM_L(.if (size) != 0)                                                            \
	__ASM_L(.pushsection DBG_SECTION_HOOKS_RAW, "a")                                    \
	__ASM_L(	/*dc_type*/ _DBG_HOOK_ASMWORD_TYPE   DBG_HOOK_CLEAR)                    \
	__ASM_L(	/*dc_flag*/ _DBG_HOOK_ASMWORD_FLAG   _DBG_HOOK_ASMWORD_FLAGS)           \
	__ASM_L(	/*dc_size*/ _DBG_HOOK_ASMWORD_SIZE   (size) + (2 * __SIZEOF_POINTER__)) \
	__ASM_L(	/*dc_cobj*/ _DBG_HOOK_ASMWORD_RELPTRO(start_symbol, start_offset))      \
	__ASM_L(	/*dc_data*/ .skip (size))                                               \
	__ASM_L(.popsection)                                                                \
	__ASM_L(.endif (size) != 0)                                                         \
	__ASM_END

/* Overload:
 * >> DBG_CLEAR(Symbol start_symbol, Int size);
 * >> DBG_CLEAR(Symbol start_symbol, Int start_offset, Int size); */
#define DBG_CLEAR(...) __HYBRID_PP_VA_OVERLOAD(_DBG_PRIVATE_CLEAR_, (__VA_ARGS__))(__VA_ARGS__)



/* TODO: Refactor the name of, and use `DBG_HOOK_CLEAR' if possible for the following */
#define _DBG_PRIVATE_BZERO_NAME3(prefix, y) prefix##y
#define _DBG_PRIVATE_BZERO_NAME2(prefix, y) _DBG_PRIVATE_BZERO_NAME3(prefix, y)
#define _DBG_PRIVATE_BZERO_NAME(prefix) _DBG_PRIVATE_BZERO_NAME2(prefix, __LINE__)

/* Define the callbacks necessary to do `bzero(p, size)' during a debugger
 * reset,  as well as  safely backup/restore the  original contents of the
 * specified memory range upon initialization/finalization. */
#define DEFINE_DBG_BZERO(p, size)                                                   \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size]; \
	DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)) {                          \
		__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);       \
		__libc_memset(p, 0, size);                                                  \
	}                                                                               \
	DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)) {                        \
		__libc_memset(p, 0, size);                                                  \
	}                                                                               \
	DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))  {                         \
		__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);       \
	}
#define DEFINE_DBG_BZERO_IF(cond, p, size)                                          \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size]; \
	DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)) {                          \
		if (cond) {                                                                 \
			__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);   \
			__libc_memset(p, 0, size);                                              \
		}                                                                           \
	}                                                                               \
	DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)) {                        \
		if (cond)                                                                   \
			__libc_memset(p, 0, size);                                              \
	}                                                                               \
	DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)) {                          \
		if (cond)                                                                   \
			__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);   \
	}
#define DEFINE_DBG_BZERO_VECTOR(vector_base, element_count, element_size, element_stride)      \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[(element_count) * \
	                                                                         (element_size)];  \
	DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)) {                                     \
		size_t i;                                                                              \
		byte_t *dst       = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                      \
		byte_t const *src = (byte_t const *)(vector_base);                                     \
		for (i = 0; i < (element_count); ++i) {                                                \
			__libc_memcpy(dst, src, element_size);                                             \
			__libc_memset(dst, 0, element_size);                                               \
			dst += (element_size);                                                             \
			src += (element_stride);                                                           \
		}                                                                                      \
	}                                                                                          \
	DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)) {                                   \
		size_t i;                                                                              \
		byte_t *dst = (byte_t *)(vector_base);                                                 \
		for (i = 0; i < (element_count); ++i) {                                                \
			__libc_memset(dst, 0, element_size);                                               \
			dst += (element_stride);                                                           \
		}                                                                                      \
	}                                                                                          \
	DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)) {                                     \
		size_t i;                                                                              \
		byte_t *dst       = (byte_t *)(vector_base);                                           \
		byte_t const *src = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                      \
		for (i = 0; i < (element_count); ++i) {                                                \
			__libc_memcpy(dst, src, element_size);                                             \
			dst += (element_stride);                                                           \
			src += (element_size);                                                             \
		}                                                                                      \
	}
#define DEFINE_DBG_BZERO_OBJECT(obj) \
	DEFINE_DBG_BZERO(&(obj), sizeof(obj))









/* Helpers for enumerating system-wide debugger hooks. */
#ifdef __CC__

struct driver_loadlist;
struct driver_section;
struct dbg_hookiterator {
	REF struct driver_loadlist *dhi_drivers;    /* [1..1] Loaded drivers. */
	size_t                      dhi_nextdriver; /* Index for the next driver to scan. */
	REF struct driver_section  *dhi_section;    /* [1..1] Section currently being scanned.
	                                             * HINT: This is 1..1, since the kernel _always_ defines
	                                             *       a `.dbg.hook' section, so we know that at least
	                                             *       one such section will exist at run-time! */
	struct dbg_hookhdr         *dhi_sectnext;   /* [1..1] Pointer to the next hook to enumerate. */
	struct dbg_hookhdr         *dhi_sectend;    /* [== dhi_section->ds_data + dhi_section->ds_size]
	                                             * Pointer  to  the  end  of  the  current  driver's  .dbg.hook  section.
	                                             * Set to point to the end of the MORE-vector when `dhi_sectprev != NULL' */
	struct dbg_hookhdr         *dhi_sectprev;   /* [0..1] Return-pointer for DBG_HOOK_MORE-hooks. */
};

/* Initialize a given `struct dbg_hookiterator *self' */
#define dbg_hookiterator_init(self)                                                                     \
	(void)((self)->dhi_drivers    = get_driver_loadlist(),                                              \
	       (self)->dhi_nextdriver = 0,                                                                  \
	       (self)->dhi_section    = (REF struct driver_section *)incref(&kernel_section_dbg_hooks),     \
	       (self)->dhi_sectnext   = (struct dbg_hookhdr *)kernel_section_dbg_hooks.ds_addr,             \
	       (self)->dhi_sectend    = (struct dbg_hookhdr *)((byte_t *)kernel_section_dbg_hooks.ds_addr + \
	                                                       kernel_section_dbg_hooks.ms_size),           \
	       (self)->dhi_sectprev   = __NULLPTR)

/* Finalize a given `struct dbg_hookiterator *self' */
#define dbg_hookiterator_fini(self)              \
	(void)(decref_unlikely((self)->dhi_section), \
	       decref_unlikely((self)->dhi_drivers))


/* Return a pointer to the next debugger hook, or `NULL' if the iterator has been exhausted.
 * NOTE: The pointers of the returned hook will have been relocated automatically
 *       for all known, builtin hook types! */
FUNDEF WUNUSED NONNULL((1)) struct dbg_hookhdr const *FCALL
dbg_hookiterator_next(struct dbg_hookiterator *__restrict self);

/* Same as `dbg_hookiterator_next()', but skip all hooks of a different type than `type' */
FUNDEF WUNUSED NONNULL((1)) struct dbg_hookhdr const *FCALL
dbg_hookiterator_next_filtered(struct dbg_hookiterator *__restrict self,
                               dbg_hook_type_t type);

#define DBG_HOOKITERATOR_NEXT_FILTERED(self, type) \
	((_DBG_PRIVATE_HOOKSTRUCT(type) const *)dbg_hookiterator_next_filtered(self, type))

/* Returns the driver belonging to the last-iterated hook. */
FUNDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct driver *FCALL
dbg_hookiterator_driver(struct dbg_hookiterator const *__restrict self);

/* Search for a debug command matching the given name.
 * @return: NULL: No command exists that matches `name' */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command(char const *__restrict name);

/* Search for a debug command matching the given name most closely. */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command_fuzzy(char const *__restrict similar_to_name);

/* Search  for  a  debug  command   who's  name  starts  with   `name'.
 * If more than one command matches this criteria, return NULL instead. */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command_startswith(char const *__restrict name_start);

#endif /* __CC__ */


DECL_END

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_HOOK_H */
