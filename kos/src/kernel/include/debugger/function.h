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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_FUNCTION_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_FUNCTION_H 1

#include <kernel/compiler.h>
#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>

DECL_BEGIN

#define ATTR_DBGTEXT        ATTR_COLDTEXT
#define ATTR_DBGRODATA      ATTR_COLDRODATA
#define ATTR_DBGDATA        ATTR_COLDDATA
#define ATTR_DBGBSS         ATTR_COLDBSS
#define ATTR_DBGTEXT_S(x)   ATTR_COLDTEXT_S(x)
#define ATTR_DBGRODATA_S(x) ATTR_COLDRODATA_S(x)
#define ATTR_DBGDATA_S(x)   ATTR_COLDDATA_S(x)
#define ATTR_DBGBSS_S(x)    ATTR_COLDBSS_S(x)
#define DBGSTR(s)       XBLOCK({ PRIVATE ATTR_DBGRODATA char const _dbg_str[] = s; XRETURN _dbg_str; })

#define DBG_CALL VCALL

#ifdef __CC__
/* The prototype for the callback of a debugger service function. */
typedef uintptr_t (DBG_CALL *debug_func_t)(size_t argc, char *argv[]);
struct debug_function {
	debug_func_t df_main; /* [1..1][const] The function's callback. */
	char const  *df_name; /* [1..1][const] The function's name. */
	char const  *df_help; /* [0..1][const] An optional help string for the function. */
};

/* Search for a debug function matching the given name.
 * @return: NULL: No function exists that matches `name' */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc(char const *__restrict name);

/* Search for a debug function matching the given name most closely. */
FUNDEF ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_fuzzy(char const *__restrict name);

/* Search for a debug function who's name starts with `name'. */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_start(char const *__restrict name);


/* Special return values for debug functions. */
#define DBG_FUNCTION_INVALID_ARGUMENTS ((uintptr_t)-1)

#define _DBG_PRIVATE_FUNCTION_NAME3(x, y) x##y
#define _DBG_PRIVATE_FUNCTION_NAME2(x, y) _DBG_PRIVATE_FUNCTION_NAME3(x, y)
#define _DBG_PRIVATE_FUNCTION_NAME(x) _DBG_PRIVATE_FUNCTION_NAME2(x, __LINE__)

#define REGISTER_DEBUG_FUNCTION_EX(name, help, main)                                                                      \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_name_)[] = name; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_help_)[] = help; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_functions") ATTR_USED                                                        \
	struct debug_function const _DBG_PRIVATE_FUNCTION_NAME(_debug_def) =                                                  \
		{ &main, _DBG_PRIVATE_FUNCTION_NAME(_debug_name_), _DBG_PRIVATE_FUNCTION_NAME(_debug_help_) }
#define DEFINE_DEBUG_FUNCTION(name, help, argc, argv)                                                                     \
	PRIVATE uintptr_t DBG_CALL _DBG_PRIVATE_FUNCTION_NAME(_debug_main_)(size_t argc, char *argv[]);                     \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_name_)[] = name; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_help_)[] = help; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_functions") ATTR_USED                                                        \
	struct debug_function const _DBG_PRIVATE_FUNCTION_NAME(_debug_def) =                                                  \
		{	&_DBG_PRIVATE_FUNCTION_NAME(_debug_main_),                                                                    \
			_DBG_PRIVATE_FUNCTION_NAME(_debug_name_),                                                                     \
			_DBG_PRIVATE_FUNCTION_NAME(_debug_help_) };                                                                   \
	PRIVATE ATTR_DBGTEXT uintptr_t DBG_CALL _DBG_PRIVATE_FUNCTION_NAME(_debug_main_)(size_t argc, char *argv[])
#endif /* __CC__ */

/* >> void KCALL func(void);
 * Define a debug initializer/reset/finalizer function
 * INIT:  Called whenever the debugger is entered (not called upon recursive re-entry)
 * FINI:  Called whenever the debugger is exited
 * RESET: Called whenever the debugger is entered (after INIT, including on recursive re-entry) */
#define DEFINE_DBG_INIT(func)  DEFINE_CALLBACK(".rodata.cold.callback.dbg_init", func)
#define DEFINE_DBG_RESET(func) DEFINE_CALLBACK(".rodata.cold.callback.dbg_reset", func)
#define DEFINE_DBG_FINI(func)  DEFINE_CALLBACK(".rodata.cold.callback.dbg_fini", func)

DECL_END

#ifdef __CC__
#include <libc/string.h>
#define _DBG_PRIVATE_BZERO_NAME3(prefix, y) prefix##y
#define _DBG_PRIVATE_BZERO_NAME2(prefix, y) _DBG_PRIVATE_BZERO_NAME3(prefix, y)
#define _DBG_PRIVATE_BZERO_NAME(prefix) _DBG_PRIVATE_BZERO_NAME2(prefix, __LINE__)

/* Define the callbacks necessary to do `memset(p,0,size)' during a debugger
 * reset, as well as safely backup/restore the original contents of the
 * specified memory range upon initialization/finalization. */
#define DEFINE_DBG_BZERO(p, size)                                                    \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size];  \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {  \
		__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);        \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) { \
		__libc_memset(p, 0, size);                                                   \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {  \
		__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);        \
	}                                                                                \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                     \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                   \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_IF(cond, p, size)                                           \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size];  \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {  \
		if (cond)                                                                    \
			__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);    \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) { \
		if (cond)                                                                    \
			__libc_memset(p, 0, size);                                               \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {  \
		if (cond)                                                                    \
			__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);    \
	}                                                                                \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                     \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                   \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_VECTOR(vector_base, element_count, element_size, element_stride)                       \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[(element_count) * (element_size)]; \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {                             \
		size_t i;                                                                                               \
		byte_t *dst       = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                                       \
		byte_t const *src = (byte_t const *)(vector_base);                                                      \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memcpy(dst, src, element_size);                                                              \
			dst += (element_size);                                                                              \
			src += (element_stride);                                                                            \
		}                                                                                                       \
	}                                                                                                           \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) {                            \
		size_t i;                                                                                               \
		byte_t *dst = (byte_t *)(vector_base);                                                                  \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memset(dst, 0, element_size);                                                                \
			dst += (element_stride);                                                                            \
		}                                                                                                       \
	}                                                                                                           \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {                             \
		size_t i;                                                                                               \
		byte_t *dst       = (byte_t *)(vector_base);                                                            \
		byte_t const *src = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                                       \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memcpy(dst, src, element_size);                                                              \
			dst += (element_stride);                                                                            \
			src += (element_size);                                                                              \
		}                                                                                                       \
	}                                                                                                           \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                                                \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                                              \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_OBJECT(obj) \
	DEFINE_DBG_BZERO(&(obj), sizeof(obj))
#endif /* __CC__ */

#else /* CONFIG_HAVE_DEBUGGER */

#define DEFINE_DEBUG_FUNCTION(name, main, help)                                           /* nothing */
#define DEFINE_DBG_INIT(func)                                                             /* nothing */
#define DEFINE_DBG_RESET(func)                                                            /* nothing */
#define DEFINE_DBG_FINI(func)                                                             /* nothing */
#define DEFINE_DBG_BZERO(p, size)                                                         /* nothing */
#define DEFINE_DBG_BZERO_IF(cond, p, size)                                                /* nothing */
#define DEFINE_DBG_BZERO_VECTOR(vector_base, element_count, element_size, element_stride) /* nothing */
#define DEFINE_DBG_BZERO_OBJECT(obj)                                                      /* nothing */

#endif /* !CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_FUNCTION_H */
