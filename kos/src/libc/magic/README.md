
Documentation for magic definition files found in this folder
For the purpose of this file, documentation uses a declaring filename of `string.c`, and a declared function `memcpy()`



### Direct output of text into

Syntax:

`%[(location-list)]{ text }`  
`%[(location-list)]text<\n>`

Where `location-list` defaults to `(c)`, such that `%(c){ ... }` is the same as `%{ ... }`. Multiple locations may be defined as seperated by a `,` character.

```
%{
This text will appear in /include/string.h
}
%And so will this text
```

The following locations are defined:

| Name | File | Description |
|------|------|------|
| `c` | `/include/string.h` | Default scope within headers |
| `std` | `/include/string.h` | Appears in the section for `%[insert:std]` |
| `ccompat` | `/include/string.h` | Used for importing components from `std::` into the root namespace |
| `libc_fast` | `/include/libc/string.h` | |
| `libc_slow` | `/include/libc/slow/string.h` | |
| `auto_header` | `/src/libc/auto/string.h` | |
| `auto_source` | `/src/libc/auto/string.c` | |
| `auto_libc_header` | `/src/libc/auto/string.h` | `#ifndef __KERNEL__`-section |
| `auto_libc_source` | `/src/libc/auto/string.c` | `#ifndef __KERNEL__`-section |
| `user` | `/src/libc/user/string.h` | |



### Directives

Syntax:

`%[directive-name]`  
`%[directive-name(arguments)]`

Directives are used to tell the magic generator special information that does not relate to a specific function. The following directives are defined:

| Name | Description |
|------|-------|
| `%[insert:std]` | Insert all functions marked as `[std]` at the current location as part of the `std`-namespace. Additionally, all text blocks with `std` as one of their locations will also be output (output happens as part of `/include/string.h`) |
| `%[insert:extern(name[,...])]` | Insert a declaration of each function `name` that is actually defined by a different source file.<br>The function is always inserted in the root namespace, even if it was originally defined as `[std]`.<br>The function is also required to carry the `[guard]` tag |
| `%[declare_known_section(name)]` | For the purpose of generating `/include/crt-features/crt-kos-sections-order.h`, declare the fact that a section `name` exists.<br>The given `name` must start with one of `.text.crt`, `.xdata.crt`, `.data.crt`, `.rodata.crt` or `.bss.crt` |
| `%[define_ccompat_header(name)]`<br>`%[define_ccompat_header(name,g)]`<br>`%[define_ccompat_header(name,g,sg)]` | Generate a seperate header file `/include/<name>`, as well as wrappers for importing `std::` symbols (s.a. the `ccompat` text location), such that a header `<cstring>` and `<string.h>` can properly function together.<br>`g` is the `#include`-guard for `<cstring>` and defaults to `_CXX_<NAME>`.<br>`sg` is a guard to remember if symbols have already been defined as part of `std::` thus far |
| `%[default_impl_section(name)]` | Set the default section that functions without a `[section(...)]` tag are placed into.<br>This directive only applies on a per-file-scope, and defaults to `{.text.crt.unsorted|.text.crt.dos.unsorted}`.<br>To specify both the names of the KOS and DOS implementations of `wchar_t`-functions, you may use `{KOS_NAME|DOS_NAME}` |
| `%[nosys_errno(name)]` | Set the `name` for the `errno` value that is set by the stub-implementations in `/src/libc/user/string.c` of functions not yet implemented.<br>This directive only applies on a per-file-scope, and defaults to `ENOSYS`.<br>If an empty string is assigned `%[nosys_errno()]`, `errno` will not be modified by an unimplemented function.<br>This directive can also be overwritten on a per-function basis using `[nosys_errno(...)]` and `[no_nosys_errno]` |
| `%[crt_feature(name[,...])]` | Define additional CRT features that should appear in `/include/crt-features/all.h` as `#define __CRT_HAVE_<name> 1` |
| `%[define_wchar_replacement(c = w16, w32)]` | Define the replacement for `c` in code blocks for 16-bit (dos) and 32-bit (unix) `wchar_t` mode.<br>Examples for this are:<br>`%[define_wchar_replacement(wchar_t = char16_t, char32_t)]`<br>`%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = 2, 4)]`<br>Note that these definitions are persistent across all magic source files, and are only applied once all files have been parsed |
| `%[define_replacement(a = b)]` | Define the replacement for `a` to-be applied in `/include/libc/string.h`, `/include/libc/slow/string.h`, `/include/local/string/memcpy.h`, as well as `/include/string.h` (though here the replacement only applies to `$a` (the symbol prefixed by a `$`)) |
| `%[define_str2wcs_replacement(a = b)]` | Define a replacement for `a` when it appears as a word in a piece of code that is used by the `%{copy(foo,str2wcs)}` code generator |
| `%[push_macro [@opt [@...]] { name [...] }]`<br>`%[push_macro([@opt [@...]] { name [...] })]` | Output code to the `c` location to make use of `#pragma push_macro()` in order to preserve the definitions of every given `name`.<br>This directive should then be followed by another directive `%[pop_macro]` to restore those definitions.<br>When `@undef` is given as an `@opt`, then also ensure that the definitions of all given macros are `#undef`-ed (irregardlessly of the even host-compiler actually supporting `#pragma push_macro(...)`) |
| `%[pop_macro]` | s.a. `%[push_macro ...]` |
| `%[enum [@opt [@...]] [name] { defs... }]`<br>`%[enum([@opt [@...]] { defs... })]` | Declare a C `enum`-type such that it may also be used if the header is included by an assembler.<br>When `name` is given, it will be used as `enum <name> { FOO, BAR, ... }`.<br>The following values are defined for `@opt`:<br>- `@typedef(name)` Declare the enum as `typedef enum { ... } <name>;`<br>- `@undef` Delete macro definitions for enum values beforehand<br>- `@macro` Always provide enum values as macros for testing purposes `enum{ FOO }; #define FOO FOO`.<br>- `@guard` Surround the enum's definitions with a guard `#ifndef __<name>_defined`, where name is the `@typedef` name first, and the `enum <name>` second. |
| `%[define(a = b)]` | Define a replacement for `a` to-be applied irregardless of context |







### Functions

Syntax:

```
[@@Doc-string line 1]
[@@Doc-string line 2]
[tags] function_name:(arguments) -> return_type [cpp_overloads] impl
```
`tags` is a sequence of bracketed (`[...]`) annotations for the following function. Every tag can either appear as `[tag1][tag2]`, or as `[tag1, tag2]`. Note that some tags take arguments and are written as `[tag(args)]`. Also note that the `[if(...)]` tag is scoped to only apply to tags written as `[if(...), tag]`, but will not apply to tags written as `[if(...)][tag]`

The following is a list of recognized tags:

| Name | Description |
|------|-------------|
| TODO | TODO |


`arguments` is a comma-seperated (and possibly empty) list of the C-like arguments taken by the function.  
Note that arguments in this list should be written as un-escaped (i.e. no `__`-prefix), as the magic generator will automatically escape when in all places where this needs to be done.

Additionally, any argument may be prefixed by its own set of tags (mainly intended to be used for simplified annotation of `NONNULL((...))` attributes):

| Name | Description |
|------|-------------|
| TODO | TODO |



`cpp_overloads` is a bracketed (`[...]`) sequence of `[(arguments) -> return_type]` definitions declaring overloads usually intended to properly carry `const` arguments into return types. An example of this is the `strchr()` function:

```
strchr:(char const *s, int c) -> char *
	[(char *s, int c) -> char *]
	[(char const *s, int c) -> char const *]
{
	...
}
```

`impl` is used to provide the default implementation for the function and must be one of:

- No implementation is given (the function will appear as unimplemented in `/src/libc/user/string.c`)  
  ```
  foo:();
  ```

- The implementation is aliasing another function (This will cause `bar` to be exposed with the alias `foo` (unless the `[nocrt]` tag was used), and `foo` to use the implementation of `bar` (if any))  
  ```
  foo:() = bar;
  ```

- The implementation is given locally  
  ```
  foo:() { do_something(); }
  ```  
  The given `do_something` will appear in `/include/local/string/memcpy.h` and in `/src/libc/auto/string.c` (if the possible). Otherwise (if the `[same_impl]` tag is given), the same implementation will also appear as the `/*AUTO*/` implementation in `/src/libc/user/string.c`

- The implementation uses a generator  
  ```
  foo:() %{...}
  ```
	- For this purpose, the following generators are defined:
		- `foo:() %{copy(name)}`, `foo:() %{copy(name, direct)}`  
		  Copy the implementation of another function `name`
		- `foo:() %{copy(name, str2wcs)}`  
		  Copy from `name`, but convert `char` to `wchar_t` (s.a. `%[define_wchar_replacement(...)]`).  
		  When `name` is `%auto`, replace a leading `wcs` with `str` (`wcslen()` derives from `strlen()`)
		- `foo:() %{copy(name, double2float)}`  
		  Copy from `name`, but convert `double` to `float` (used for functions from `<math.h>`).  
		  When `name` is `%auto`, strip a trailing `f` from the function name (`powf` derives from `pow`)
		- `foo:() %{copy(name, double2ldouble)}`  
		  Copy from `name`, but convert `double` to `long double` (used for functions from `<math.h>`).  
		  When `name` is `%auto`, strip a trailing `l` from the function name (`powl` derives from `pow`)
		- `foo:() %{uchar}`, `foo:() %{uchar16}`, `foo:() %{uchar32}`, `foo:() %{uchar(base)}`, `foo:() %{uchar16(base)}`, `foo:() %{uchar32(base)}`  
		  Declare the 16- or 32-bit uchar-variant of a wchar function  
		  When `base` is not given or is `%auto`, try to automatically determine the original function
		- `foo:() %{auto_block(any({ ... }))}`  
		  Use the given implementation `...` the same way it is given in all places (s.a. `[libc_impl({ ... })]`, `[user_impl({ ... })]`)
		- `foo:() %{auto_block(printf(name))}`  
		  Generate a `va_list` wrapper for a varargs function (e.g. `printf()` is declared as `printf:(char const *format, ...) -> int %{auto_block(printf(vprintf))}`)  
		  When `name` is `%auto`, try to automatically determine the base function
		- `foo:() %{auto_block(math)}`, `foo:() %{auto_block(math(mytype, basefunc))}`  
		  Automatically generate a math function as either a wrapper, or direct implementation of another math function






