
Documentation for magic definition files found in this folder

### Output namespaces

| Name             | Description                                               |
| ---------------- | --------------------------------------------------------- |
| `c_prefix`       | Guard-prefix in `<HEADER.h>`                              |
| `c`              | C-part in `<HEADER.h>`                                    |
| `std`            | `namespace std`-part in `<HEADER.h>`                      |
| `ccompat`        | c-compat-part in `<HEADER.h>`                             |
| `libc_fast`      | `<libc/HEADER.h>`                                         |
| `libc_core`      | `<libc/core/HEADER.h>`                                    |
| `auto_header`    | `/kos/src/libc/auto/HEADER.h`                             |
| `auto_source`    | `/kos/src/libc/auto/HEADER.c`                             |
| `user`           | `/kos/src/libc/user/HEADER.h`                             |

Usage (all of these are the same):

- ```
  %foobar
  ```
- ```
  %{
  foobar
  }
  ```
- ```
  %(c)foobar
  ```
- ```
  %(c){
  foobar
  }
  ```


### Directives

| Directive                                        | Description                                                  |
| ------------------------------------------------ | ------------------------------------------------------------ |
| `%[push_macro (a, b, c)]`                        | Emit portable code for `#pragma push_macro()`                |
| `%[push_macro (a b c)]`                          | You can also separate macros by whitespace                   |
| `%[push_macro(NAMESPACES) (a b c)]`              | This is how you specify which namespaces to output text to   |
| `%[push_macro(NAMESPACES) (a, b, c)]`            | ...                                                          |
| `%[push_macro @undef (a b c)]`                   | And this way you automatically `#undef` macros after pushing |
| `%[push_macro @undef (a, b, c)]`                 | ...                                                          |
| `%[push_macro(NAMESPACES) @undef (a b c)]`       | ...                                                          |
| `%[push_macro(NAMESPACES) @undef (a, b, c)]`     | ...                                                          |
|                                                  |                                                              |
| `%[pop_macro]`                                   | Generate code to restore previously pushed macros            |
|                                                  |                                                              |
| `%[define_header_guard(NAME)]`                   | Set the name of the header guard (default: `_HEADER_H`)      |
|                                                  |                                                              |
| `%[define_ccompat_header(FILENAME)]`             | Set the filename of a c++-c-compat header (e.g. `cstdio`)    |
|                                                  |                                                              |
| `%[pushdefault]`                                 | Push default settings (s.a. `%[default:...]`)                |
| `%[push_default]`                                | ...                                                          |
|                                                  |                                                              |
| `%[popdefault]`                                  | Restore pushed default settings (s.a. `%[push_default]`)     |
| `%[pop_default]`                                 | ...                                                          |
|                                                  |                                                              |
| `%[default:...]`                                 | Set default function annotations (`...` are annotations as in `Annotations (defaultable)`; s.a. below) |
|                                                  |                                                              |
| `%[include(FILENAME)]`                           | Include contents of another file here                        |
|                                                  |                                                              |
| `%[insert:prefix(TEXT)]`                         | Insert `TEXT` into the `c` namespace, and don't duplicate that text in function prefixes |
|                                                  |                                                              |
| `%[insert:pp_if(COND)]`                          | Insert a `#if` directive, including special operation support and expression optimization |
| `%[insert:pp_elif(COND)]`                        | Insert a `#elif` directive, including special operation support and expression optimization (s.a. `%[insert:pp_if(COND)]`) |
| `%[insert:pp_include(HEADER)]`                   | Insert a `#include` directive |
| `%[insert:pp_else]`                              | Insert a `#else` directive (s.a. `%[insert:pp_if(COND)]`) |
| `%[insert:pp_endif]`                             | Insert a `#endif` directive (s.a. `%[insert:pp_if(COND)]`) |
|                                                  |                                                              |
| `%[insert:function(NAME)]`                       | Insert a binding for a function `NAME` here (useful for functions declared in multiple headers) |
| `%[insert:function(NAME, ATTRIB)]`               | Where `ATTRIB` is: `',' ~~ (ATTR_NAME ':' ATTR_VALEXPR)...` (`ATTR_NAME` is a member of `ExposedFunction` from `cheaders.dee` and `ATTR_VALEXPR` is a deemon-expression passed to `deemon.exec()`) |
| `%[insert:function(EXPOSED_NAME = NAME)]`        | You can also specify a custom name by which the function is exposed (s.a. `ExposedFunction.exposedName`) |
| `%[insert:function(EXPOSED_NAME = NAME, ATTRIB)]`| ... |
| `%[insert:std_function(<Same as above...>)]`                 | Insert into the `std::` namespace and add `using` to also load it into the global namespace |
| `%[insert:std_function_nousing(<Same as above...>)]`         | Same, but don't import into the global namespace |
| `%[insert:guarded_function(<Same as above...>)]`             | Like above, but include `guardName: true` in `ATTRIB` |
| `%[insert:guarded_std_function(<Same as above...>)]`         | ... |
| `%[insert:guarded_std_function_nousing(<Same as above...>)]` | ... |
|                                                  |                                                              |
| `%[insert:extern(NAME)]`                         | Same as `%[insert:guarded_function(NAME)]`                   |
|                                                  |                                                              |
| `%[insert:std]`                                  | Marker for where to paste the std-namespace into the c-namespace in `<HEADER.h>` |
|                                                  |                                                              |
| `%[define_wchar_replacement_header(ORIG = C16,C32)]` | Define header names to replace a `wchar_t`-header with its `char16_t` and `char32_t` equivalents (s.a. `wcharReplacementHeaders` from `wchar.dee`) |
|                                                  |                                                              |
| `%[define_wchar_replacement(ORIG = C16,C32)]`    | Define type/constant/function names to replace a `wchar_t` with its `char16_t` and `char32_t` equivalents (s.a. `wcharReplacementEscapes` from `wchar.dee`) |
|                                                  |                                                              |
| `%[define_c_language_keyword(WORDS...)]`         | Mark `WORDS` as C language keywords, thus preventing these words from being escaped in headers (s.a. `cLanguageKeywords` from `escape.dee`) |
|                                                  |                                                              |
| `%[define_replacement(ORIG = ESCAPED)]`          | Define custom behavior for how to escape `ORIG` in headers (by default, escaping uses `__{ORIG}` or `_{ORIG[0].upper()}{ORIG[1:]}`) (s.a. `keywordEscapes` from `escape.dee`) |
|                                                  |                                                              |
| `%[define_partial_replacement(ORIG = ESCAPED)]`  | Similar to `define_replacement`, but these replacements also happen in partial replacement mode (used in `<HEADER.h>`, while full replacement is used in `<libc/local/HEADER/FUNCTION.h>`) (s.a. `partialKeywordEscapes` from `escape.dee`) |
|                                                  |                                                              |
| `%[define_type_class(TYPENAME = CLASS)]`         | Specify the classification for `TYPENAME` (usually you'll use `"TP"` for `CLASS` to indicate pointer types) (s.a. `knownTypeClasses` from `typeclass.dee`) |
|                                                  |                                                              |
| `%[define_str2wcs_replacement(STR = WCHAR)]`     | Specify replacement for automatic string to wchar generators (s.a. `str2wcsReplacementEscapes` from `generator.dee`) |
|                                                  |                                                              |
| `%[define_str2wcs_header_replacement(STR_HEADER = WCHAR_HEADER)]` | Specify replacement headers for automatic string to wchar generators (s.a. `str2wcsHeaderReplacementEscapes` from `generator.dee`) |
|                                                  |                                                              |
| `%[define_double_replacement(DOUBLE = FLOAT,LONG_DOUBLE)]` | Specify replacements for auto-generated math functions |
|                                                  |                                                              |
| `%[define_double2ldouble_replacement(DOUBLE = LONG_DOUBLE)]` | Specify replacements for auto-generated math functions |
|                                                  |                                                              |
| `%[define_double2float_replacement(DOUBLE = FLOAT)]` | Specify replacements for auto-generated math functions |
|                                                  |                                                              |
| `%[define(NAME = REPLACEMENT)]`                  | Specify a `REPLACEMENT` to use used in place of `NAME`, even in dont-escape modes |
|                                                  |                                                              |
| `%[define_crt_name_list(NAME = [A,B,C,...])]`    | Define a CRT name list `NAME` which expands to `A,B,C,...` in assembly name lists, if followed by `...` (3 dots) (s.a. `[alias(X,Y,Z)]`) |

TODO: Incomplete



### Annotations (parameters)

| Annotation               | Description                                               |
| ------------------------ | --------------------------------------------------------- |
| `[format_arg]`           | Add attribute `__ATTR_FORMAT_ARG(<argumentIndex>)`        |
| `[nullable]`             | no-op                                                     |
| `[null]`                 | no-op                                                     |
| `[nonnull]`              | Add arg index to `ATTR_NONNULL((...))`                    |
| `[in]`                   | `__ATTR_`                                       |
| `[inpb(...)]`            | Same as `[nonnull]`                                       |
| `[inp_opt(...)]`         | no-op                                                     |
| `[inpb_opt(...)]`        | no-op                                                     |
| `[outp(...)]`            | Same as `[nonnull]`                                       |
| `[outpb(...)]`           | Same as `[nonnull]`                                       |
| `[outp_opt(...)]`        | no-op                                                     |
| `[outpb_opt(...)]`       | no-op                                                     |
| `[inoutp(...)]`          | Same as `[nonnull]`                                       |
| `[inoutpb(...)]`         | Same as `[nonnull]`                                       |
| `[inoutp_opt(...)]`      | no-op                                                     |
| `[inoutpb_opt(...)]`     | no-op                                                     |

### Annotations (return types)

| Annotation                        | Description                                               |
| --------------------------------- | --------------------------------------------------------- |
| `[== argName]`                    | If `ATTR_NONNULL((<indexOf(argname)>))`, add `ATTR_RETNONNULL` |
| `[malloc_unaligned(size...)]`     | Add: `WUNUSED`, `ATTR_MALLOC`, `ATTR_ALLOC_SIZE(<join(indexOf(size))>)` |
| `[malloc(size...)]`               | Like `[malloc_unaligned(size...)]`, but also add `ATTR_MALL_DEFAULT_ALIGNED` |
| `[memalign(align, size...)]`      | Add `WUNUSED`, `ATTR_MALLOC`, `ATTR_ALLOC_SIZE(<join(indexOf(size))>)`, `ATTR_ALLOC_ALIGN(<indexOf(align)>)` (When `align` is `getpagesize()`, add `__ATTR_MALL_PAGEALIGNED` instead) |
| `[realloc_unaligned(p, size...)]` | Add `WUNUSED`, `ATTR_ALLOC_SIZE(<join(indexOf(size))>)` |
| `[realloc(p, size...)]`           | Like `[realloc_unaligned(size...)]`, but also add `ATTR_MALL_DEFAULT_ALIGNED` |
| `[realign(p, align, size...)]`    | Add `WUNUSED`, `ATTR_ALLOC_SIZE(<join(indexOf(size))>)`, `ATTR_ALLOC_ALIGN(<indexOf(align)>)` (When `align` is `getpagesize()`, add `__ATTR_MALL_PAGEALIGNED` instead) |


### Annotations (functions / return types)

| Annotation               | Description                                               |
| ------------------------ | --------------------------------------------------------- |
| `[nullable]`             | no-op                                                     |
| `[null]`                 | no-op                                                     |
| `[ATTR_MCONST]`          | no-op                                                     |
| `[ATTR_*]`               | Add attribute: `ATTR_*`                                   |
| `[nonnull]`              | Add attribute: `ATTR_RETNONNULL`                          |
| `[wunused]`              | Add attribute: `WUNUSED`                                  |
| `[attribute(...)]`       | Add attribute: `...`                                      |
| `[attributes(...)]`      | Add attribute: `...`                                      |
| `[noreturn]`             | Add attribute: `ATTR_NORETURN`                            |
| `[const]`                | Add attribute: `ATTR_CONST`                               |
| `[pure]`                 | Add attribute: `ATTR_PURE`                                |
| `[cold]`                 | Add attribute: `ATTR_COLD`                                |
| `[hot]`                  | Add attribute: `ATTR_HOT`                                 |
| `[leaf]`                 | Add attribute: `ATTR_LEAF`                                |
| `[deprecated]`           | Add attribute: `ATTR_DEPRECATED_`                         |
| `[deprecated("foo")]`    | Add attribute: `ATTR_DEPRECATED("foo")`                   |
| `[no_nothrow]`           | Set nothrow: /empty/                                      |
| `[nothrow(FOOBAR)]`      | Set nothrow: `FOOBAR`                                     |
| `[nothrow]`              | Set nothrow: `NOTHROW`                                    |
| `[nothrow_ncx]`          | Set nothrow: `NOTHROW_NCX` (__default__)                  |
| `[nothrow_rpc]`          | Set nothrow: `NOTHROW_RPC`                                |
| `[nothrow_rpc_kos]`      | Set nothrow: `NOTHROW_RPC_KOS`                            |
| `[nothrow_rpc_nokos]`    | Set nothrow: `NOTHROW_RPC_NOKOS`                          |
| `[nothrow_rpc_pure]`     | Set nothrow: `NOTHROW_RPC_PURE`                           |
| `[cp_stdio]`             | Set nothrow: `THROWING` (extension: `THROWS(...)`)        |
| `[stdio_throws]`         | Set nothrow: `THROWING` (extension: `THROWS(...)`)        |
| `[throws]`               | Set nothrow: `THROWING` (extension: `THROWS(...)`)        |
| `[throws(a,b,c)]`        | Set nothrow: `THROWING` (extension: `THROWS(a,b,c)`)      |
| `[cp]`                   | Set nothrow: `NOTHROW_RPC`                                |
| `[cancellation_point]`   | Set nothrow: `NOTHROW_RPC`                                |
| `[rpc]`                  | Set nothrow: `NOTHROW_RPC`                                |
| `[cp_kos]`               | Set nothrow: `NOTHROW_RPC_KOS`                            |
| `[cp_nokos]`             | Set nothrow: `NOTHROW_RPC_NOKOS`                          |
| `[rpc_pure]`             | Set nothrow: `NOTHROW_RPC_PURE`                           |
| `[cc(LIBCCALL)]`         | Set calling convention: `LIBCCALL`                        |
| `[vartypes(int,int)]`    | Set types for optional varargs: `[int, int]`  (s.a. `ioctl`) |
| `[decl_prefix(...)]`     | Add declaration prefix (emit `...` prior to declaring the function) |
| `[decl_include(HEADERS...)]` | same as `foreach h in HEADERS: [decl_prefix("#include {h}")]` |


### Annotations (defaultable)

| Annotation               | Description                                               |
| ------------------------ | --------------------------------------------------------- |
| `[nodecl]`               | Set declaration: `__LIBC`                                 |
| `[no_decl]`              | Set declaration: `__LIBC`                                 |
| `[ignore]`               | Set namespaces: `[]`                                      |
| `[no_ignore]`            | Set namespaces: `[""]`  (Global namespace) (__default__)  |
| `[libc]`                 | Export in `<libc/HEADER.h>`: `true`                       |
| `[nolibc]`               | Export in `<libc/HEADER.h>`: `false` (__default__)        |
| `[no_libc]`              | Export in `<libc/HEADER.h>`: `false` (__default__)        |
| `[inline]`               | Set inline mode: `LOCAL`                                  |
| `[forceinline]`          | Set inline mode: `FORCELOCAL`                             |
| `[noinline]`             | Disable inline (__default__)                              |
| `[no_inline]`            | Disable inline (__default__)                              |
| `[inline_truncate]`      | Remove linefeeds from inline body: `true`                 |
| `[no_inline_truncate]`   | Remove linefeeds from inline body: `false`                |
| `[extern_inline]`        | Allow inline functions as extern-inline: `true` (__default__) |
| `[no_extern_inline]`     | Allow inline functions as extern-inline: `false` |
| `[local]`                | Enable linking again `<libc/local/HEADER/FUNCTION.h>`: `true` (__default__) |
| `[noLocal]`              | Enable linking again `<libc/local/HEADER/FUNCTION.h>`: `false` |
| `[no_local]`             | Enable linking again `<libc/local/HEADER/FUNCTION.h>`: `false` |
| `[norequires]`           | Set requires pp-condition: `1` (__default__) |
| `[no_requires]`          | Set requires pp-condition: `1` (__default__) |
| `[no_requires_prefix]`   | Set requires prefix block: /empty/ (__default__) |
| `[no_impl_prefix]`       | Set implementation prefix block: /empty/ (__default__) |
| `[macro_bindings]`       | Allow function to be declared as a macro: `true` |
| `[no_macro_bindings]`    | Allow function to be declared as a macro: `false` (__default__) |
| `[noguard]`              | Enable declaration guard macros: `false` (__default__) |
| `[no_guard]`             | Enable declaration guard macros: `false` (__default__) |
| `[default_guard_names]`  | Set namespace-specific guard names: `__{{ns}_}{name}_defined` (__default__) |
| `[default_exposed_name]` | Set exposed name in headers: `<functionName>` (__default__) |
| `[wchar]`                | Enable special `wchar_t` treatment: `true` |
| `[no_wchar]`             | Enable special `wchar_t` treatment: `false` (__default__) |
| `[crt_dos_variant]`      | Enable dedicated DOS implementation in libc (i.e. `DOS$function`): `true` |
| `[no_crt_dos_variant]`   | Enable dedicated DOS implementation in libc (i.e. `DOS$function`): `false` (__default__) |
| `[crt_dos_wrapper]`      | Enable the libc DOS-wrapper when `!defined(__LIBCCALL_IS_LIBDCALL)`: `true` (__default__) (s.a. `/kos/src/libc/libc/dosabi-functions`) |
| `[no_crt_dos_wrapper]`   | Enable the libc DOS-wrapper when `!defined(__LIBCCALL_IS_LIBDCALL)`: `false` |
| `[default_crt_name]`     | Use `<functionName>` as the CRT name (the `DEFINE_PUBLIC_ALIAS()` name and the default asmname binding in headers; s.a. `[crt_name(...)]`) |
| `[crt_impl]`             | Provide an implementation in libc: `true` (__default__) |
| `[no_crt_impl]`          | Provide an implementation in libc: `false` |
| `[crt_self_import]`      | Bind against the function's primary asmname in headers: `true` (__default__) |
| `[no_crt_self_import]`   | Bind against the function's primary asmname in headers: `false` |
| `[crt_self_export]`      | Export the function from libc by its primary asmname: `true` (__default__) |
| `[no_crt_self_export]`   | Export the function from libc by its primary asmname: `false` |
| `[no_crt_impl_requires]` | Set requirements for automatic KOS+DOS variant impl inside of libc: `1` (__default__) |
| `[no_crt_kos_impl_requires]` | Set requirements for automatic KOS variant impl inside of libc: `1` (__default__) |
| `[no_crt_dos_impl_requires]` | Set requirements for automatic DOS variant impl inside of libc: `1` (__default__) |
| `[userimpl]`             | Force impl in `/src/libc/user/HEADER.c`: `true` |
| `[no_userimpl]`          | Force impl in `/src/libc/user/HEADER.c`: `false` (__default__) (also: provide impl in `/src/libc/auto/HEADER.c`) |
| `[default_kos_section]`  | Use `.text.crt.unsorted` for the KOS libc impl (__default__) |
| `[default_dos_section]`  | Use `.text.crt.dos.unsorted` for the DOS libc impl (__default__) |
| `[auto_dependency_scanning]`  | Enable automatic scanning for dependencies: `true` (__default__) (auto-local-binding in `<libc/local/HEADER/FUNCTION.h>`) |
| `[no_auto_dependency_scanning]`  | Enable automatic scanning for dependencies: `false` |
| `[nodos]`                | Alias for `[no_crt_dos_variant]`, `[no_crt_dos_wrapper]` |
| `[crt]`                  | Alias for `[crt_impl]`, `[crt_self_import]`, `[crt_self_export]` |
| `[static]`               | Alias for `[ignore]`, `[macro_bindings]`, `[no_guard]`, `[no_crt_self_import]`, `[no_crt_self_export]`, `[no_crt_dos_wrapper]` |
| `[nocrt]`                | Alias for `[no_crt_impl]`, `[no_crt_self_import]`, `[no_crt_self_export]` |
| `[no_crt]`               | Alias for `[no_crt_impl]`, `[no_crt_self_import]`, `[no_crt_self_export]` |
| `[hidden]`               | Remove `""` (global namespace) from namespaces |
| `[exposed]`              | Add `""` (global namespace) to namespaces |
| `[std]`                  | Add `"std"` (`std::` namespace) from namespaces |
| `[nostd]`                | Remove `"std"` (`std::` namespace) from namespaces |
| `[no_std]`               | Remove `"std"` (`std::` namespace) from namespaces |
| `[fast]`                 | Add `"fast"` (`__optimized_imp::` namespace) to namespaces (deprecated; use `[preferred_fastbind]`) |
| `[nofast]`               | Remove `"fast"` (`__optimized_imp::` namespace) to namespaces (deprecated; use `[preferred_fastbind]`) |
| `[requires(COND)]`       | Set `COND` as the preprocessor condition required for the local implementation (hint: `$has_function(NAME)`) (default: `[requires(1)]`) |
| `[requires_function(NAMES...)]` | Alias for `[requires(<"&&".join(for (n: NAMES) f"$has_function({n})")>)]` |
| `[requires_dependent_function(NAMES...)]` | Same as `[requires_function(NAMES...)]`, but also add each function as a dependency (bound in local implementation) |
| `[requires_include(HEADERS...)]` | same as `foreach h in HEADERS: [requires_prefix("#include {h}")]` |
| `[requires_prefix(...)]` | Add prefix needed by the `[requires(...)]` expression |
| `[impl_prefix(...)]`     | Add implementation prefix (emit `...` prior to implementing the function) |
| `[impl_include(HEADERS...)]` | Same as `foreach h in HEADERS: [impl_prefix("#include {h}")]` |
| `[section(NAME)]`        | Set the libc section name for the function. Note that `{KOS|DOS}` may be used to encode subsystem-specific strings |
| `[kos_section(NAME)]`    | Set the libc section name for the KOS version of the function |
| `[dos_section(NAME)]`    | Set the libc section name for the DOS version of the function |
| `[decl(PREFIX)]`         | Set the declaration PREFIX (defaults to `__LIBC`) |
| `[guard]`                | Enable declaration guard macros: `true` |
| `[guard(IS_FUNC_DEFINED)]` | Set the guard macro name for the global namespace to `IS_FUNC_DEFINED` |
| `[exposed_name(NAME)]`   | Set the name by which the function is exposed in headers (default: `<functionName>`) |
| `[crt_name(NAME)]`       | Set the default name by which the function is exported from libc (default: `<functionName>`) |
| `[crt_impl_requires(COND)]` | Set requirements for automatic KOS+DOS variant impl inside of libc: `COND` |
| `[crt_kos_impl_requires(COND)]` | Set requirements for automatic KOS variant impl inside of libc: `COND` |
| `[crt_dos_impl_requires(COND)]` | Set requirements for automatic DOS variant impl inside of libc: `COND` |
| `[dependency(NAMES...)]` | Add forced dependencies on each of the name functions (in local implementations) |
| `[not_dependency(NAMES...)]` | Force-mark the given NAMES as not being dependencies (in local implementations) |
| `[without_dependency(NAMES...)]` | Remove NAMES from the forced-dependencies list (s.a. `[dependency(NAMES...)]`) |
| `[without_not_dependency(NAMES...)]` | Remove NAMES from the forced-not-dependencies list (s.a. `[not_dependency(NAMES...)]`) |


### Annotations (non-defaultable)

Note on bindings:

- primary: Preferred bindings (e.g. `[preferred_alias(...)]`)
- secondary: The function itself (controlled via `[crt_self_import]` and `[no_crt_self_import]`)
- tertiary: Regular bindings (e.g. `[alias(...)]`)


| Annotation                                       | Description                                               |
| ------------------------------------------------ | --------------------------------------------------------- |
| `[if(COND), ...]`                                | Make `...` (more annotations) conditionally dependent on `COND` If not supported, error out |
| `[if_fast_defined(NAME), ...]`                   | Same as `[if(defined(__fast_{NAME}_defined))]`, but also include a prefix <br/>`#ifdef __LIBC_BIND_OPTIMIZATIONS`<br/>`#include <optimized/HEADER.h>`<br/>`#endif` |
| `[if_fast_defined_always(NAME), ...]`            | Same as `[if(defined(__fast_{NAME}_defined))]`, but also include a prefix <br/>`#include <optimized/HEADER.h>` |
| `[doc(TEXT)]`                                    | Append `TEXT` to the function's documentation (same as `@@TEXT`) |
| `[doc_alias(FUNC)]`                              | Re-use the documentation of `FUNC` for this one           |
| `[[...]]`                                        | Parenthesis...                                            |
| `[argument_names(NAMES...)]`                     | Override the names of function arguments (s.a. `execv()` for a usage example) |
| `[dos_only_export_as(ASMNAME)]`                  | Same as: `[dos_export_as("DOS$ASMNAME")]`, `[if(defined(__LIBCCALL_IS_LIBDCALL)), kos_export_as(ASMNAME)]` |
| `[dos_only_export_alias(ASMNAME)]`               | Same as: `[dos_only_export_as(ASMNAME)]`, `[alias(ASMNAME)]` |
| `[dos_only_export_raw_alias(ASMNAME)]`           | Same as: `[dos_only_export_as(ASMNAME)]`, `[raw_alias(ASMNAME)]` |
| `[preferred_dos_only_export_alias(ASMNAME)]`     | Same as: `[dos_only_export_as(ASMNAME)]`, `[preferred_alias(ASMNAME)]` |
| `[preferred_dos_only_export_raw_alias(ASMNAME)]` | Same as: `[dos_only_export_as(ASMNAME)]`, `[preferred_raw_alias(ASMNAME)]` |
| `[export_alias(ASMNAME)]`                        | Same as: `[export_as(ASMNAME)]`, `[alias(ASMNAME)]` |
| `[dos_export_alias(ASMNAME)]`                    | Same as: `[dos_export_as("DOS$ASMNAME")]`, `[alias(ASMNAME)]` |
| `[kos_export_alias(ASMNAME)]`                    | Same as: `[kos_export_as(ASMNAME)]`, `[alias(ASMNAME)]` |
| `[export_raw_alias(ASMNAME)]`                    | Same as: `[export_as(ASMNAME)]`, `[raw_alias(ASMNAME)]` |
| `[dos_export_raw_alias(ASMNAME)]`                | Same as: `[dos_export_as("DOS$ASMNAME")]`, `[raw_alias(ASMNAME)]` |
| `[kos_export_raw_alias(ASMNAME)]`                | Same as: `[kos_export_as(ASMNAME)]`, `[raw_alias(ASMNAME)]` |
| `[preferred_export_alias(ASMNAME)]`              | Same as: `[export_as(ASMNAME)]`, `[preferred_alias(ASMNAME)]` |
| `[preferred_dos_export_alias(ASMNAME)]`          | Same as: `[dos_export_as("DOS$ASMNAME")]`, `[preferred_alias(ASMNAME)]` |
| `[preferred_kos_export_alias(ASMNAME)]`          | Same as: `[kos_export_as(ASMNAME)]`, `[preferred_alias(ASMNAME)]` |
| `[preferred_export_raw_alias(ASMNAME)]`          | Same as: `[export_as(ASMNAME)]`, `[preferred_raw_alias(ASMNAME)]` |
| `[preferred_dos_export_raw_alias(ASMNAME)]`      | Same as: `[dos_export_as("DOS$ASMNAME")]`, `[preferred_raw_alias(ASMNAME)]` |
| `[preferred_kos_export_raw_alias(ASMNAME)]`      | Same as: `[kos_export_as(ASMNAME)]`, `[preferred_raw_alias(ASMNAME)]` |
| `[export_as(ASMNAME)]`                           | Same as: `[kos_export_as(ASMNAME)]`, `[dos_export_as("DOS$ASMNAME")]` |
| `[kos_export_as(ASMNAME)]`                       | Export the KOS variant of this function as `ASMNAME` from libc (via `DEFINE_PUBLIC_ALIAS()`) |
| `[dos_export_as(ASMNAME)]`                       | Export the DOS variant of this function as `ASMNAME` from libc (via `DEFINE_PUBLIC_ALIAS()`) |
| `[alias(ASMNAME)]`                               | Same as: `[if(defined(__CRT_HAVE_{ASMNAME})), raw_alias(ASMNAME)]` |
| `[preferred_alias(ASMNAME)]`                     | Same as: `[if(defined(__CRT_HAVE_{ASMNAME})), preferred_raw_alias(ASMNAME)]` |
| `[raw_alias(ASMNAME)]`                           | Link against `ASMNAME` in headers (tertiary binding) |
| `[preferred_raw_alias(ASMNAME)]`                 | Link against `ASMNAME` in headers (primary binding) |
| `[bind_local_function(NAME)]`                    | Link against the local implementation of function `NAME` (tertiary binding) |
| `[preferred_bind_local_function(NAME)]`          | Link against the local implementation of function `NAME` (primary binding) |
| `[fastbind]`                                     | Same as `[fastbind(<functionName>)]` |
| `[fastbind(NAME)]`                               | Same as `[fastbind(NAME(<functionArgumentNames>))]` (e.g. `[fastbind(memcpy(dst, src, num_bytes))]`) |
| `[fastbind(NAME(ARGS...))]`                      | Same as `[fastbind(NAME(ARGS...), [NAME])]` |
| `[fastbind(NAME(ARGS...), [ASMNAMES])]`          | Same as (`foreach ASMNAME in ASMNAME`) <br/>`[[if_fast_defined(NAME), fast_extern_inline(ASMNAME, { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]`<br/>`[[if_fast_defined(NAME), fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]` |
| `[fastbind_always]`                              | Same as `[fastbind_always(<functionName>)]` |
| `[fastbind_always(NAME)]`                        | Same as `[fastbind_always(NAME(<functionArgumentNames>))]` (e.g. `[fastbind(memcpy(dst, src, num_bytes))]`) |
| `[fastbind_always(NAME(ARGS...))]`               | Same as `[fastbind_always(NAME(ARGS...), [NAME])]` |
| `[fastbind_always(NAME(ARGS...), [ASMNAMES])]`   | Same as (`foreach ASMNAME in ASMNAME`) <br/>`[[if_fast_defined_always(NAME), fast_extern_inline(ASMNAME, { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]`<br/>`[[if_fast_defined_always(NAME), fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]` |
| `[preferred_fastbind]`                           | Same as `[preferred_fastbind(<functionName>)]` |
| `[preferred_fastbind(NAME)]`                     | Same as `[preferred_fastbind(NAME(<functionArgumentNames>))]` (e.g. `[fastbind(memcpy(dst, src, num_bytes))]`) |
| `[preferred_fastbind(NAME(ARGS...))]`            | Same as `[preferred_fastbind(NAME(ARGS...), [NAME])]` |
| `[preferred_fastbind(NAME(ARGS...), [ASMNAMES])]` | Same as (`foreach ASMNAME in ASMNAME`) <br/>`[[if_fast_defined(NAME), preferred_fast_extern_inline(ASMNAME, { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]`<br/>`[[if_fast_defined(NAME), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]` |
| `[preferred_fastbind_always]`                    | Same as `[preferred_fastbind_always(<functionName>)]` |
| `[preferred_fastbind_always(NAME)]`              | Same as `[preferred_fastbind_always(NAME(<functionArgumentNames>))]` (e.g. `[fastbind(memcpy(dst, src, num_bytes))]`) |
| `[preferred_fastbind_always(NAME(ARGS...))]`     | Same as `[preferred_fastbind_always(NAME(ARGS...), [NAME])]` |
| `[preferred_fastbind_always(NAME(ARGS...), [ASMNAMES])]` | Same as (`foreach ASMNAME in ASMNAME`) <br/>`[[if_fast_defined_always(NAME), preferred_fast_extern_inline(ASMNAME, { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]`<br/>`[[if_fast_defined_always(NAME), preferred_fast_forceinline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(@NAME@))(ARGS); })]]` |
| `[inline({ INLINE_IMPLEMENTATION })]`                               | Implement inline via `INLINE_IMPLEMENTATION` (tertiary binding) |
| `[forceinline({ INLINE_IMPLEMENTATION })]`                          | Implement force-inline via `INLINE_IMPLEMENTATION` (tertiary binding) |
| `[extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`               | same as `[if(__CRT_HAVE_{ASMNAME}), raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]` |
| `[raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`           | Implement as extern-inline, linking against `ASMNAME` and using `INLINE_IMPLEMENTATION` for inline (tertiary binding) |
| `[preferred_inline({ INLINE_IMPLEMENTATION })]`                     | Implement inline via `INLINE_IMPLEMENTATION` (primary binding) |
| `[preferred_forceinline({ INLINE_IMPLEMENTATION })]`                | Implement force-inline via `INLINE_IMPLEMENTATION` (primary binding) |
| `[preferred_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`     | same as `[if(__CRT_HAVE_{ASMNAME}), preferred_raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]` |
| `[preferred_raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]` | Implement as extern-inline, linking against `ASMNAME` and using `INLINE_IMPLEMENTATION` for inline (primary binding) |
| `[fast_inline({ INLINE_IMPLEMENTATION })]`                               | Like `[inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[fast_forceinline({ INLINE_IMPLEMENTATION })]`                          | Like `[forceinline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[fast_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`               | Like `[extern_inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[fast_raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`           | Like `[raw_extern_inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[preferred_fast_inline({ INLINE_IMPLEMENTATION })]`                     | Like `[preferred_inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[preferred_fast_forceinline({ INLINE_IMPLEMENTATION })]`                | Like `[preferred_forceinline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[preferred_fast_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]`     | Like `[preferred_extern_inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[preferred_fast_raw_extern_inline(ASMNAME, { INLINE_IMPLEMENTATION })]` | Like `[preferred_raw_extern_inline({ INLINE_IMPLEMENTATION })]`, but don't link in `<libc/core/HEADER.h>` |
| `[crtbuiltin]`                                   | Same as `[if(__has_builtin(__builtin_{<functionName>}) && defined(__LIBC_BIND_CRTBUILTINS)), preferred_extern_inline({<functionName>}, { return __builtin_{<functionName>}({<functionArgs>}); })]` |
| `[crt_intern_kos_alias(INTERN_ASMNAME)]`         | Use `DEFINE_INTERN_ALIAS()` with `INTERN_ASMNAME` to provide the KOS libc implementation (hint: use with `[if(...)]` to make this conditional) |
| `[crt_intern_dos_alias(INTERN_ASMNAME)]`         | Use `DEFINE_INTERN_ALIAS()` with `INTERN_ASMNAME` to provide the DOS libc implementation (hint: use with `[if(...)]` to make this conditional) |
| `[rlim64_variant_of(ASMNAME)]`                   | Same as `[alt_variant_of(__SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__, ASMNAME)]` |
| `[time64_variant_of(ASMNAME)]`                   | Same as `[alt_variant_of(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__, ASMNAME)]` |
| `[off64_variant_of(ASMNAME)]`                    | Same as `[alt_variant_of(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__, ASMNAME)]` |
| `[largefile64_variant_of(ASMNAME)]`              | Same as `[alt_variant_of(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0, ASMNAME)]` |
| `[fts64_variant_of(ASMNAME)]`                    | Same as `[alt_variant_of(defined(__FTS32_MATCHES_FTS64), ASMNAME)]` |
| `[dirent64_variant_of(ASMNAME)]`                 | Same as `[alt_variant_of(defined(_DIRENT_MATCHES_DIRENT64), ASMNAME)]` |
| `[statfs64_variant_of(ASMNAME)]`                 | Same as `[alt_variant_of(defined(_STATFS_MATCHES_STATFS64), ASMNAME)]` |
| `[longdouble_variant_of(ASMNAME)]`               | Same as `[alt_variant_of(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE), ASMNAME)]` |
| `[preferred_rlim64_variant_of(ASMNAME)]`         | Same as `[preferred_alt_variant_of(__SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__, ASMNAME)]` |
| `[preferred_time64_variant_of(ASMNAME)]`         | Same as `[preferred_alt_variant_of(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__, ASMNAME)]` |
| `[preferred_off64_variant_of(ASMNAME)]`          | Same as `[preferred_alt_variant_of(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__, ASMNAME)]` |
| `[preferred_largefile64_variant_of(ASMNAME)]`    | Same as `[preferred_alt_variant_of(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0, ASMNAME)]` |
| `[preferred_fts64_variant_of(ASMNAME)]`          | Same as `[preferred_alt_variant_of(defined(__FTS32_MATCHES_FTS64), ASMNAME)]` |
| `[preferred_dirent64_variant_of(ASMNAME)]`       | Same as `[preferred_alt_variant_of(defined(_DIRENT_MATCHES_DIRENT64), ASMNAME)]` |
| `[preferred_statfs64_variant_of(ASMNAME)]`       | Same as `[preferred_alt_variant_of(defined(_STATFS_MATCHES_STATFS64), ASMNAME)]` |
| `[preferred_longdouble_variant_of(ASMNAME)]`     | Same as `[preferred_alt_variant_of(defined(__ARCH_LONG_DOUBLE_IS_DOUBLE), ASMNAME)]` |
| `[alt_variant_of(COND, ASMNAME)]`                | Same as `[if(COND), alt_variant_of(ASMNAME)]` |
| `[preferred_alt_variant_of(COND, ASMNAME)]`      | Same as `[if(COND), preferred_alt_variant_of(ASMNAME)]` |
| `[alt_variant_of(ASMNAME)]`                      | Same as `[alias(ASMNAME)]`, `[crt_intern_kos_alias(libc_{ASMNAME})]` |
| `[preferred_alt_variant_of(ASMNAME)]`            | Same as `[preferred_alias(ASMNAME)]`, `[crt_intern_kos_alias(libc_{ASMNAME})]` |
| `[kernel]`                                       | Same as `[crt_kos_impl_if(1)]` (Note: default is `[crt_kos_impl_if(!defined(__KERNEL__))]`) |
| `[crt_impl_if(COND)]`                            | Same as `[crt_kos_impl_if(COND)]`, `[crt_dos_impl_if(!defined(__LIBCCALL_IS_LIBDCALL) && {COND})]` |
| `[crt_kos_impl_if(COND)]`                        | Set the wrapping pp-condition that must be met for the KOS-variant to be implemented in libc to `COND` (default: `1`) |
| `[crt_dos_impl_if(COND)]`                        | Set the wrapping pp-condition that must be met for the DOS-variant to be implemented in libc to `COND` (default: `!defined(__LIBCCALL_IS_LIBDCALL)`) |
| `[crt_dos_only]`                                 | Same as `[cc(LIBDCALL)]`, `[nodos]` |
| `[crt_dos_variant(*)]`                           | Custom implementations for dos variants (see below) |



### Custom DOS implementations

- `[crt_dos_variant(callback( ... ))]`: Automatic wrapper for when a DOS variant needs to be generated as a result of `LIBCCALL` differing from `LIBDCALL` (e.g. on `x86_64`). This annotation can be used to specify how that wrapper should be generated. The given `...` is a `,`-separated list of:
	- `decl: <dosPrototype>`  
	  Declare the function prototype used by the dos variant (optional)  
	  Usually, this tag isn't required as the DOS prototype is automatically generated from the KOS prototype by replacing KOS-types and calling conventions of arguments with their DOS equivalents.
	- `cook: struct { auto <name> = <init>, auto <name> = <init>, ... }`  
	  Specify a structure to-be used for cookie data, as well as that structure's fields and initializers. This is the set of data that is passed via the `$cook` parameter to the wrapper function.  
	  Note that `auto` may also be replaced with a custom type expression, though when `auto` is used, an attempt is made to deduce the effective type from `<init>`
	  Example: `cook: struct { auto compar = compar; auto arg = arg; }`  
	- `cook: auto = <init>`  
	  Use this instead of the `struct { ... }` form when only a single parameter needs to be passed to the wrapper function (e.g. the DOS-wrapper for `qsort(3)` is implemented in terms of `qsort_r(3)` and only needs a single parameter `compar`, as no secondary cookie pointer can be passed to `qsort(3)`)
	  Example: `cook: auto = compar`  
	- `wrap: <wrapperPrototype> { <wrapperImplementation> }`  
	  Specify the prototype and implementation of the wrapper. Within the prototype, `$cook` may be used as a placeholder for the cookie structure/argument type (the internal cookie `struct` or the evaluation of `auto` within the single-argument `cook` declaration)
	  Example: `wrap: ($cook c, void const *a, void const *b): int { return (*c)(a, b); }`  
	  Example: `wrap: ($cook *c, void const *a, void const *b): int { return (*c->compar)(c->arg, a, b); }`
	- `impl: <dosImplementation>`  
	  Implementation of the dos variant's function body (excluding the optional constructing and initialization of a cookie structure). This expression may either be of the form `{ ...; return ...; }`, or of the form `...`, in which case it is automatically wrapped by a `return` statement (unless the dos variant returns `void`)  
	  Additionally, the given expression may contain `$wrap`, which is replaced with the name of the wrapper function, as well as `$cook`, which is replaced with the name of the fully initialized local cookie variable (in case struct-cookies are used), or the `<init>` expression when the single cookie-argument version is used.  
	  Example: `_lfind_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, (void *)$cook)`
  With all of that in mind, given something like:  

  ```
  [[crt_dos_variant(callback(
      cook: struct { auto compar = compar; auto arg = arg; },
      wrap: ($cook *c, void const *a, void const *b): int { return (*c->compar)(c->arg, a, b); },
      impl: _lfind_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, &$cook),
  ))]]
  void *_lfind_s(void const *key, [[nonnull]] void const *pbase,
                 [[nonnull]] size_t *pitem_count, size_t item_size,
                 [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                 void *arg);
  ```

  Construct the following code automatically (in `/kos/src/libc/auto/*.c`):

  ```c
  #if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
  #ifndef __dwrap_sTPTP_TDTPTPTP_c0c1A1A2_defined
  #define __dwrap_sTPTP_TDTPTPTP_c0c1A1A2_defined
  struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A1A2 {
      int (LIBDCALL *compar)(void *arg, void const *a, void const *b);
      void *arg;
  };
  PRIVATE ATTR_SECTION(".text.crt.dos.utility.search") int
  (LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0c1A1A2)(struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A1A2 *c,
                                            void const *a,
                                            void const *b) THROWS(...){
      return (*c->compar)(c->arg, a, b);
  }
  #endif /* !__dwrap_sTPTP_TDTPTPTP_c0c1A1A2_defined */
  INTERN ATTR_SECTION(".text.crt.dos.utility.search") WUNUSED NONNULL((2, 3, 5)) void *
  (LIBDCALL libd__lfind_s)(void const *key,
                           void const *pbase,
                           size_t *pitem_count,
                           size_t item_size,
                           int (LIBDCALL *compar)(void *arg, void const *a, void const *b),
                           void *arg) THROWS(...) {
      struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A1A2 libd__lfind_s_cookie;
      libd__lfind_s_cookie.compar = compar;
      libd__lfind_s_cookie.arg = arg;
      return libc__lfind_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&_dwrap_sTPTP_TDTPTPTP_c0c1A1A2, &libd__lfind_s_cookie);
  }
  #endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
  ```

- `[crt_dos_variant({ ... })]`, where `...` is a `,`-separated list of
	- `decl: <dosPrototype>`  
	  Declare the function prototype used by the dos variant (optional)
	- `impl: ...`  
	  Set the implementation body of the dos variant (mandatory)
	- `prefix: { ... }`, `prefix: ...`  
	  Add an implementation prefix to-be prepended before the in-library implementation






### Function body

| Body                                             | Description                                               |
| ------------------------------------------------ | --------------------------------------------------------- |
| `;`                                              | No function body provided |
| `{ ... }`                                        | Normal body (used in `/kos/src/libc/auto/HEADER.c` (unless `[userimpl]`) and local impl) |
| `= NAME;`                                        | Bind against another function (NOTE: If possible use `%[insert:function(...)]` instead) |
| `%{chk(NAME,ARGS)}`                              | Generate a `__*_chk` style function body |
| `%{printf}`                                      | Same as `%{printf(VPRINTF_FUNCTION_NAME)}` (`VPRINTF_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{printf(*)}`                                   | Same as `%{printf(VPRINTF_FUNCTION_NAME)}` (`VPRINTF_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{printf(%auto)}`                               | Same as `%{printf(VPRINTF_FUNCTION_NAME)}` (`VPRINTF_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{printf(NAME)}`                                | Generate a call to a `vprintf`-style function `NAME` |
| `%{generate(GENERATOR)}`                         | Same as `%{generate(GENERATOR, BASE_FUNCTION_NAME)}` (`BASE_FUNCTION_NAME` is (based on `GENERATOR`) auto-generated from `<functionName>`) |
| `%{generate(GENERATOR(*))}`                      | Same as `%{generate(GENERATOR, BASE_FUNCTION_NAME)}` (`BASE_FUNCTION_NAME` is (based on `GENERATOR`) auto-generated from `<functionName>`) |
| `%{generate(GENERATOR(%auto))}`                  | Same as `%{generate(GENERATOR, BASE_FUNCTION_NAME)}` (`BASE_FUNCTION_NAME` is (based on `GENERATOR`) auto-generated from `<functionName>`) |
| `%{generate(GENERATOR(NAME))}`                   | Generate a function based on `GENERATOR` and `NAME` (generators are `str2wcs`, `double2float` and `double2ldouble`) |
| `%{uchar}`                                       | Either `%{uchar16}` or `%{uchar32}` (based on `<functionName>`) |
| `%{uchar16}`                                     | Same as `%{uchar16(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar16(*)}`                                  | Same as `%{uchar16(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar16(%auto)}`                              | Same as `%{uchar16(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar16(WCHAR_FUNCTION_NAME)}`                | Generate bindings and implementation for the `char16_t` variant of a wchar-function `WCHAR_FUNCTION_NAME` |
| `%{uchar32}`                                     | Same as `%{uchar32(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar32(*)}`                                  | Same as `%{uchar32(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar32(%auto)}`                              | Same as `%{uchar32(WCHAR_FUNCTION_NAME)}` (`WCHAR_FUNCTION_NAME` is auto-generated from `<functionName>`) |
| `%{uchar32(WCHAR_FUNCTION_NAME)}`                | Generate bindings and implementation for the `char32_t` variant of a wchar-function `WCHAR_FUNCTION_NAME` |





### Function/Prefix body directives

Note that anything inside of comments, or after `#import`, `#include` or `#include_next` is never escaped

| Body                                             | Description                                               |
| ------------------------------------------------ | --------------------------------------------------------- |
| `@foo@`                                          | Insert `foo` directly, without ever doing any escaping    |
| `$extended_prefix(TEXT)`                         | Add `TEXT` as a prefix for the current prefix             |
| `$extended_include_prefix(HEADER)`               | Alias for `$extended_prefix(#include HEADER)`             |
| `$has_function(NAME)`                            | Generate and insert a pp-condition that must be met for `NAME` to be available |
| `$crt_has_function(ASMNAME)`                     | Insert `defined(__CRT_HAVE_{ASMNAME})` |
| `@@exec CODE@@`                                  | Execute some deemon code to set-up variables which may be used by other directives |
| `@@push_namespace(NAMESPACE)@@`                  | Insert `__NAMESPACE_{...}_BEGIN` and friends to change the current namespace |
| `@@pop_namespace@@`                              | Restore a previous namespace |
| `@@if EXPR@@`                                    | Evaluate `EXPR` as a deemon expression. If false, skip to the next `@@elif@@`, `@@else@@` or `@@endif@@` |
| `@@elif EXPR@@`                                  | s.a. `@@if EXPR@@` |
| `@@else@@`                                       | s.a. `@@if EXPR@@` |
| `@@endif@@`                                      | s.a. `@@if EXPR@@` |
| `@@pp_if PP_COND@@`                              | Output an optimized preprocessor `#if PP_COND` |
| `@@pp_ifdef IDENT@@`                             | Same as `@@pp_if defined({IDENT})@@` |
| `@@pp_ifndef IDENT@@`                            | Same as `@@pp_if !defined({IDENT})@@` |
| `@@pp_elif PP_COND@@`                            | Output an optimized preprocessor `#elif PP_COND` |
| `@@pp_elifdef IDENT@@`                           | Same as `@@pp_elif defined({IDENT})@@` |
| `@@pp_elifndef IDENT@@`                          | Same as `@@pp_elif !defined({IDENT})@@` |
| `@@pp_else@@`                                    | Output an optimized preprocessor `#else` |
| `@@pp_endif@@`                                   | Output an optimized preprocessor `#endif` |


