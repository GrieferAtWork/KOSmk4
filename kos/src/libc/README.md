
### Runtime configuration options

This section documents how KOS's libc can be (re-)configured by hosted programs and/or the state of environment options at the time of program invocation

#### Program hooks

- `extern void __libc_tls_globals_alloc_failed(void);`
	- If defined, this callback is invoked when libc fails to allocate memory for TLS globals of a thread other than the main thread, and unsafe fallbacks are not enabled (s.a. `$LIBC_TLS_GLOBALS_ALLOW_UNSAFE`)
- `extern int __libc_tls_globals_alloc_failed;`
	- If defined with a non-zero value, and `$LIBC_TLS_GLOBALS_ALLOW_UNSAFE` is not set, still enable unsafe tls globals fallbacks (s.a. environment option: `$LIBC_TLS_GLOBALS_ALLOW_UNSAFE`)
- `extern int matherr(struct exception *exc);`
	- If defined, this function is called when errors arise in certain functions from `<math.h>`
	- The passed `struct exception` is defined in `<math.h>`, and under c++ becomes `struct __exception`
- `extern _LIB_VERSION_TYPE _LIB_VERSION;`
	- If defined, this global can be used to select implementation-specific quirks of functions from `<math.h>`
	- The enum type `_LIB_VERSION_TYPE` is defined in `<math.h>`, as are the possible values it may take, one of which needs to be used to initialize this variable when the main program wishes to override it.
- `extern void *malloc(size_t num_bytes);`
	- If defined, the first call to libc's `malloc(3)` will cause libc to re-configure itself in order to have all calls to standard heap functions pass through another user-defined `malloc()` function. When used, it becomes **impossible** to make use of libc's *normal* heap.
	- **Only** if `malloc` is overwritten with a custom function, will libc **then** also check which (if any) of the following functions are overwritten, and use them, or try to substitute them when they aren't defined:
	  ```c
	  extern void free(void *ptr); // or: "cfree"
	  extern void *calloc(size_t elem_count, size_t elem_size);
	  extern void *realloc(void *ptr, size_t num_bytes);
	  extern void *realloc_in_place(void *ptr, size_t num_bytes);
	  extern void *memalign(size_t alignment, size_t num_bytes); // or: "aligned_alloc"
	  extern errno_t posix_memalign(void **p_ptr, size_t alignment, size_t num_bytes);
	  extern void *valloc(size_t num_bytes);
	  extern void *pvalloc(size_t num_bytes);
	  extern int mallopt(int param_number, int value);
	  extern struct mallinfo mallinfo(void);
	  extern struct mallinfo2 mallinfo2(void);
	  extern int malloc_trim(size_t pad);
	  extern size_t malloc_usable_size(void *ptr); // or: "_msize"
	  extern void *memdup(void const *ptr, size_t n_bytes);
	  extern void *memcdup(void const *ptr, int needle, size_t n_bytes);
	  extern void *reallocarray(void *ptr, size_t elem_count, size_t elem_size);
	  extern void *recalloc(void *mallptr, size_t num_bytes);
	  extern void *recallocv(void *mallptr, size_t elem_count, size_t elem_size);
	  ```
	  Note that for full functionality, at least `malloc` and `malloc_usable_size` need to be defined by your application. Everything else is technically optional and will be implemented by fallback/noop-wrappers that call your `malloc` and `malloc_usable_size`.
	- IMPORTANT: You CANNOT use this mechanism to inject some extra wrapper around heap functions and then use `dlsym(RTLD_NEXT, "malloc")` to call the *real* malloc! If you try to do this, you'll get a stack-overflow, since what you believe to be the *real* malloc no longer exists, as it has been replaced with a proxy that's just going to call *your* malloc all the time.
- `extern void *(*__malloc_hook)(size_t num_bytes, void const *return_address);`
	- When this symbol (or any of the following symbols) is accessed by the main program, libc will re-configure its built-in set of malloc functions to invoke malloc hooks (when non-NULL) as a replacement for normal malloc behavior.
	- In order to do this, libc will load `libdlmalloc.so`, which gets used when hooks are defined to NULL. This must be done because libc has to trash its original heap implementation in order to inject extra hooks.
	- Note that internally, libc keeps track (using a TLS variable) when a thread is currently inside of a user-defined malloc-hook, and will *not* invoke the hook a second time if this is already the case.
		- As such, callbacks assigned to these hooks are allowed to simply call heap functions yet again (and are actually expected to do so, since these hooks must still allocate from the *normal* heap, since there is no hook for `malloc_usable_size`, which in turn expects its argument to be a valid heap pointer).
	- The following hooks are defined, and the linking against any one of these is enough to cause libc to enable support for malloc hooks:
		- `extern void *(*__malloc_hook)(size_t num_bytes, void const *return_address);`
			- Called by `malloc(3)`, `calloc(3)`, `memdup(3)` and `memcdup(3)`
		- `extern void (*__free_hook)(void *ptr, void const *return_address);`
			- Called by `free(3)`
		- `extern void *(*__realloc_hook)(void *ptr, size_t num_bytes, void const *return_address);`
			- Called by `realloc(3)`, `reallocarray(3)`, `recalloc(3)`, `recallocv(3)`
			- Also causes `realloc_in_place(3)` to always fail when `malloc_usable_size(ptr) < num_bytes`, and be a no-op when the heap-pointer contains sufficient memory
		- `extern void *(*__memalign_hook)(size_t alignment, size_t num_bytes, void const *return_address);`
			- Called by `memalign(3)` (and `aligned_alloc(3)`), `posix_memalign(3)`, `valloc(3)`, `pvalloc(3)`
		- `extern void (*__malloc_initialize_hook)(void);`
			- Called the first time (and *only* the first time) any heap function is used



#### Environment options

- `$LIBC_TLS_GLOBALS_ALLOW_UNSAFE` (...)
	- When define as non-empty, failure to allocate memory for TLS globals (e.g. `strtok(3)`'s internal buffer) in threads other than the main thread is handled fail-safe (but thread-unsafe) by simply re-using the main thread's TLS globals descriptor within the secondary thread.
	- In the absence of this environment variable (i.e. if not defined, as opposed to defined as an empty string), the same behavior is also be enabled when the hosted program exports a global variable `PUBLIC int __libc_tls_globals_allow_unsafe = 1;`
- `$POSIXLY_CORRECT` (`getopt(3)`)
	- Force posix-correct behavior for `getopt(3)`. This causes `getopt(3)` to *not* permutate program arguments, which normally allows mixing of options and arguments.
	- This causes `ls /bin -l` to behave:
		- like `ls -l /bin` (When `POSIXLY_CORRECT` is disabled; default)
		- like `ls -- /bin -l` (When `POSIXLY_CORRECT` is enabled)
	- The same behavior is also used when a program uses `__posix_getopt(3)` rather than `getopt(3)`, or when the `optstring` argument of `getopt(3)` is prefixed by `+` during the first call to `getopt(3)`
- `$TMPDIR`, `$TMP`, `$TEMP` (`choose_tmpdir(3)`)
	- All of these environment variables are considered as potential candidates for the directory returned by `choose_tmpdir(3)`
- `$PATH` (`execvp(3)`, `execvpe(3)`)
	- Specifies the list of directories that are searched for programs to execute
	- Directories are separated by `:`. There is no way to escape `:` if it appears in a directory name
- `$LOGNAME` (`getlogin(3)`)
	- When this variable is defined, `getlogin(3)` will return its value rather than forward the call to `cuserid(3)`
- `$PWD` (`get_current_dir_name(3)`)
	- When defined and *correct* (`stat(".")` and `stat(getenv("PWD"))` yield the same `st_dev` and `st_ino`), `get_current_dir_name(3)` will return the `strdup(3)`'d value of this environment variable, rather than return the value of `getcwd(NULL, 0)`
- `$MSGVERB`, `$SEV_LEVEL` (`fmtmsg(3)`)
	- Affects the behavior of `fmtmsg(3)`. For more details, see the documentation of `fmtmsg(3)`
- `$LANGUAGE`, `$LC_ALL`, `$LC_CTYPE`, `$LC_NUMERIC`, `$LC_TIME`, `$LC_COLLATE`, `$LC_MONETARY`, `$LC_MESSAGES`, `$LANG` (`gettext(3)`)
	- Select the name of the language that should be used for i18n translations
	- The used language can be configured for each message category type individually, or for all categories. Given some message category `category`, the used language is selected as follows:
		- `$LANGUAGE` (if defined)
		- `$LC_ALL` (if defined)
		- `$LC_*` (if defined, where the name of the environment variable matches the name of `category`)
		- `$LANG` (if defined)
		- otherwise: don't perform i18n translations
	- When setting these variables programmatically, it is recommended to always set `$LANG` and never set `$LANGUAGE`, thus allowing a user to override defaults by simply setting `$LANGUAGE` themselves.
- `$IFS` (`wordexp(3)`)
	- List of "InputFieldSeparators" that can be used to specify which characters should be capable of separating arguments from each other during word expansion
	- If not set, this defaults to `" \t\n\r"`, which differs from the traditional unix default where `"\r"` is not part of this set. The reason for this is that KOS's libc is aware of universal line feeds, meaning it supports both `\n`, `\r` and `\r\n` everywhere.
- `$HOME`, `$PWD`, `$OLDPWD` (`wordexp(3)`)
	- Used for expansion of `~`, `~+` and `~-` in `wordexp(3)`

##### Arch-specific

- x86:
	- `$HW_RTM` (`rtm_begin(3)`)
		- When defined as `0` or `1`, can be used to override the auto-detection of processor support for RTM instructions
	- `$HW_SSE` (`getcontext(3)`)
		- When defined as `0` or `1`, can be used to override the auto-detection of processor support for SSE instructions




#### Files

- `/etc/hostid`
	- Contents returned by `gethostid(3)`
	- Contents set by `sethostid(3)`
- `/etc/ethers`
	- Database file used by:
		- `ether_ntohost(3)`
		- `ether_hostton(3)`
- `/etc/group`
	- Database file used by:
		- `getgrent(3)`
		- `getgrgid(3)`
		- `getgrnam(3)`
- `/etc/passwd`
	- Database file used by:
		- `getpwent(3)`
		- `getpwuid(3)`
		- `getpwnam(3)`
- `/etc/shadow`
	- Database file used by:
		- `getspent(3)`
		- `getspnam(3)`
- `/etc/xattr.conf`
	- Configuration file used by `attr_copy_action(3)`


### Source file inclusion in kernel-/user-space

- `./auto`
	- `./auto/*.c`:
		- Kernel:yes
		- Fully automatically generated source files and headers
- `./hybrid`
	- `./hybrid/*.c`:
		- Kernel:yes
		- Hand-written libc-APIs that can't (easily) be generated automatically, but should appear in both the kernel- and userspace
	- `./hybrid/arch/$TARGET/*.c`, `./hybrid/arch/$TARGET/*.S`:
		- Kernel:yes
		- Arch-specific functions and hand-written, optimized assembly (for things such as `memcpy`)
	- `./hybrid/arch/$TARGET/config.h`
		- Included by the main `./api.h` header to define arch-specific features (mainly used for `#define LIBC_ARCH_HAVE_* 1` to specify which normally auto-generated functions are actually implemented via hand-written assembly; s.a. `magic/*.c`)
- `./libc`
	- `./libc/*.c`, `./libc/arch/$TARGET/*.c`, `./libc/arch/$TARGET/*.S`:
		- Kernel:no
		- Libc internal meta-APIs and functions not controlled by magic generators.
		- Contains things such as library intializers, system call exports and bindings, system tests, global variable interfaces, etc...
- `./magic`
	- `./magic/*.c`:
		- Kernel:no (meta definition files: parsed to generated other files, but not actually compiled in a traditional sense)
		- Input/Definition files for magic headers
- `./user`
	- `./user/*.c`:
		- Kernel:no
		- (partially) auto-generated source files for magic-generated functions that can't be implemented automatically. (i.e. are marked as `[[userimpl]]` or don't have a body in the associated `./magic/*.c` file)


### Relocation rationale

KOS's libc is designed and optimized to minimize the number of relocations that must be resolved in order to correctly load the library. This is similar to `libdl.so`, but unlike that library, libc is actually allowed to have *some* relocations. However, in the interest to minimize startup time, all relocations that *do* exist within libc need to have their existence rationalized (if only to add the hurdle of documentation/bureaucracy if one wishes to slow down libc load times because they were too lazy to come up with a relocation-less approach to implementing some feature\[\*\])

Running `readelf -rW bin/i386-kos-OD/lib/libc.so` yields:

```
Relocation section '.rel.dyn' at offset 0x13cb98 contains 8 entries:
 Offset     Info    Type                Sym. Value  Symbol's Name
0013d1bc  00000008 R_386_RELATIVE
0013d1dc  00000008 R_386_RELATIVE
0013d1fc  00000008 R_386_RELATIVE
0013d304  00000008 R_386_RELATIVE
0013d308  00000008 R_386_RELATIVE
0013d30c  00000008 R_386_RELATIVE
0013d0bc  00000023 R_386_TLS_DTPMOD32
0013d3a8  00132501 R_386_32               0002ba80   __gxx_personality_v0

Relocation section '.rel.plt' at offset 0x13cbd8 contains 2 entries:
 Offset     Info    Type                Sym. Value  Symbol's Name
0013d0b4  00000107 R_386_JUMP_SLOT        00000000   ___tls_get_addr
0013d0b8  00000207 R_386_JUMP_SLOT        00000000   dlsym
```

Other architectures display the same set of `10` relocations with slight deviations as the result of different names for individual relocations. Though the total number of relocations (`10`) must not deviate from the above base-line.

In the following, each of these relocations will be rationalized:

- The first `6` relocations (`R_386_RELATIVE`):
	- These are the result of the initialization of the `stdin`, `stdout` and `stderr` global variables, as available in `<stdio.h>`. No lazy/indirect initialization is performed for these symbols due to the fact that a majority of programs actually make use of these variables (though it may be argued that this only applies to `stdout` and `stderr`, but not necessarily `stdin`). As such, it stands to reason that using the `STT_KOS_IDATA`-trick for initializing these could actually degrade performance, rather than aid it. For reference, see the following snippet from `/kos/src/libc/libc/compat.c`:

	```c
	INTERN FILE libc_iob[3] = {
		[0] = __IO_FILE_INIT(NULL, 0, NULL, IO_LNBUF, STDIN_FILENO, { 0 }, 0, (struct iofile_data *)&default_stdin_data),             /* !Relocation: &default_stdin_io */
		[1] = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDOUT_FILENO, { 0 }, 0, (struct iofile_data *)&default_stdout_data), /* !Relocation: &default_stdout_io */
		[2] = __IO_FILE_INIT(NULL, 0, NULL, IO_RW | IO_LNIFTYY, STDERR_FILENO, { 0 }, 0, (struct iofile_data *)&default_stderr_data), /* !Relocation: &default_stderr_io */
	};
	INTERN FILE *libc_stdin  = &libc_iob[0]; /* !Relocation: &libc_iob[0] */
	INTERN FILE *libc_stdout = &libc_iob[1]; /* !Relocation: &libc_iob[1] */
	INTERN FILE *libc_stderr = &libc_iob[2]; /* !Relocation: &libc_iob[2] */
	```

	Every line marked with `!Relocation` is responsible for one of these `6` relocations.

- The `R_386_TLS_DTPMOD32` relocation:
	- In order to facility `<pthread.h>` and a thread-local `errno`, libc includes a TLS section which contains 1 variable `current`. This variable holds everything needed for TLS and cannot be removed or circumvented without making pretty much everything about libc thread-unsafe. Working around this relocation would force libc to stray away from standard ELF thread-local variables support, which would be a bad idea due to the ease in implementation, integration with `libdl.so`, and interoperability with third-party libraries due to its standardization originating from outside the bounds of KOS development (going as far as GCC support via its `__thread` keyword).  
	  Removal of this relocation is out of the question, and the only feasible approach would be to move all of libc's TLS stuff into `libdl.so`, which is also a bad idea since `libdl.so` is meant to be unconscious and entirely disconnected from the libc implementation is used (if any) and what that implementation of libc does.
- The `R_386_32` relocation against `__gxx_personality_v0`:
	- This one is the result of `.data.rel.local.DW.ref.__gxx_personality_v0`, which is required to allow exceptions to be propagated through functions from within libc.  
	  We are actually able to replace this relocation to simply become yet another `R_386_RELATIVE` by redirecting all of GCC's uses of `__gxx_personality_v0` to use `libc_gxx_personality_v0` instead. However, like I just said: it wouldn't actually get rid of the relocation, but simply replace it with a different one.
	  The only way I can currently think of solving this issue would be the same way libdl solves it, which is to pipe all GCC-generated assembly through a filter that edits its `.cfi_personality` directives such that they don't do indirect symbol referencing. This is what GCC does and also what causes `.data.rel.local.DW.ref.__gxx_personality_v0` to appear, which is a small section that essentially looks like this:

	  ```asm
	  .section ".data.rel.local.DW.ref.__gxx_personality_v0", "aw"
	  __CFI_IND__gxx_personality_v0:      # This symbol doesn't actually have a name, but it is what would be referenced by `.cfi_personality'
	      .wordptr __gxx_personality_v0   # And this causes the `R_386_32' relocation
	  ```

	  If we generate all code with `__asm__("__gxx_personality_v0 = libc_gxx_personality_v0")`, then the above would simply reference an `INTERN` symbol instead, but we'd still have a .data section object doing an absolute symbol reference. And since the pointed-to symbol is defined by the same module (i.e. library; i.e. libc), and because that definition is declared `INTERN`, `ld(1)` can replace it with a `R_386_RELATIVE` relocation (yet we want there to be no relocation at all).  
	  It sure is a dilemma, but if I find a way to get rid of this relocation without modifying gcc or piping all of libc assembly through a filter (which would be unacceptably slow), I'll be certain to apply that solution here, especially since this **really is** a suitable candidate for lazy symbol resolution.

- Jump relocations to `___tls_get_addr` (on other arches, this is `__tls_get_addr` -- one less leading underscore -- instead):
	- This relocation does (and must) exist for the same reason as `R_386_TLS_DTPMOD32`. In order to facility support for both static and dynamic TLS variables (which are implemented and handled by `libdl.so`), a function needs to exist to load the effective runtime address of a TLS variable when the associated library was loaded using the dynamic TLS model. This is that function. It is part of the ABI (being defined in `libdl.so`), and cannot (and should not) be removed.
	  The relocation itself could theoretically be gotten rid of by redirecting it to a libc-internal symbol like we do for `__cxa_begin_catch()`, `_Unwind_Resume()` and `__gxx_personality_v0()` (to name only a few), but given how deeply ingrained use of TLS variables is (don't forget: `errno` is TLS and part of `current`), and given that `___tls_get_addr` itself also makes use of a custom calling convention (meaning the lazy-symbol-resolve function would need to be implemented via non-portable, custom assembly), this would only serve to slow down uses of TLS variables such as `errno`, negatively affecting pretty much every program since almost everything implicitly makes use of `errno`.
- Jump relocation against `dlsym`:
	- You may have already noticed that many other important function exported by `libdl.so` are missing, such as `dlopen` or `dltlsallocseg` (which surely is used by libc's pthread implementation, which yes: it is being used for that). But the presence of one single remaining relocation against `dlsym` might give a hint as to how this is accomplished, and should that not be enough of a hint, an example `*(void **)&pdyn_dltlsallocseg = dlsym(RTLD_DEFAULT, "dltlsallocseg");` might give you the idea...  
	  Sufficed to say, `dlsym` cannot be loaded in the same lazy (and relocation-less) manner, given that it is the `dlsym` function which is used to load other functions that would otherwise appear as jump relocations themselves. As such, this is another relocation that cannot be gotten rid of without deviating from standards and going against my wishes to keep `libdl.so` blissfully unaware of the internal workings of `libc.so` (if not for this, it would be possible to have `libdl.so` pass knowledge regarding the address of `dlsym` to libc in some other manner).  
	  Yet if one would go so far as to consider such a solution, "what would be the point?" I may ask. For the entire point of minimizing relocations is to ensure the swift and efficient startup time of libc. The addition of unnecessary complexity in libdl would run counter to this goal, especially since (admittedly) relocations aren't *that* expensive.


\[\*\] There are ways to implemented pretty much any functionality without relocations. Even public symbols that need to be pre-initialized as arrays of pointers (e.g. `sys_errlist(3)`) fall under this category. Don't believe me? Well: libc **does** export a fully working `sys_errlist`, but doesn't have any relocations associated with how the strings of that array are set, and neither does it initialize them as part of `libc_init()` (as set via `-Wl,-init=libc_init`). Take a look at `/kos/src/libc/user/bits.crt.sys_errlist.c` and `STT_KOS_IDATA`, which are also further elaborated upon below.

If libc contains relocations not rationalized by this document, their presence must be considered a bug and be treated as such, either (preferably) by working around the need of the relocation(s), or (in case such a work-around would yield no advantage over simply ignoring it), by documenting and rationalizing its presence in this file.



### Relocation tricks

- The "redirect-to-INTERN" trick:
	- For reference, see file `/kos/src/libc/api.h`
	- Example:

	  ```c
	  __asm__("__stack_chk_fail = libc_stack_chk_fail");
	  ```

	- By inserting the above piece of code at the start of every file compiled to be part of libc (simply do this by inserting it into "api.h", which is included by all files in libc), we're able to define per-complication unit symbol replacements to-be performed by GNU as.
	- Essentially, the above example causes `as(1)` to replace all references to `__stack_chk_fail` to instead reference `libc_stack_chk_fail`. However, it does NOT encode any sort of information in regards to the visibility of `libc_stack_chk_fail` or `__stack_chk_fail`. As a matter of fact: `__stack_chk_fail` isn't referenced by the produced `*.o` file at all (keep this in mind).
	- We now add a new source file to `libc.so` that either (intentionally) breaks the mold by not including `api.h`, or makes it so that `api.h` doesn't emit the above mentioned symbol replacement for that compilation unit in particular (this later option being what existing instances of this trick do). Then, inside of the newly added source file, we make declarations `INTERN void libc_stack_chk_fail() { ... }` and `DEFINE_PUBLIC_ALIAS(__stack_chk_fail, libc_stack_chk_fail);`. Because no other object file makes mention of `__stack_chk_fail`, this will be the first (and only) time that `ld(1)` gets to see references to `__stack_chk_fail`, all other source files instead referencing `libc_stack_chk_fail` directly, which is now revealed to be INTERN, thus allowing it to be used without the need of any relocations. (s.a. the "always-use-INTERN-functions" trick further below)


- The `STT_KOS_IDATA`-trick:
	- libc is expected to export certain data symbols whose initialization would normally require use of relocations. Examples of this include `sys_errlist` and `stdout` (though we intentionally don't use this trick for the later; see the rationale for this above).
	- By declaring symbols of type `STT_KOS_IDATA`, it becomes possible to associate a lazy initializer (actually: a function that returns the pointer that should become the symbol's runtime address) with a symbol. This function can now be written to do what would have normally been done in regards to initialization of the data symbol via relocations, only that using this trick, this becomes possible without the need of **any** relocations.
	- Note that depending on the point in time programs might link against such a symbol, and because the resolver function may be invoked multiple times, it is important to ensure that the resolver function checks if it has already initialized the global data object. -- Since its use is related to preventing relocations, it should be easy to facilitate this by simply checking if pointers that would normally become `R_386_RELATIVE` relocations are still set to `NULL` or some other not-yet-initialized value.
		- But do consider if a user-program might have reason to modify pointers within the thus-initialized data-blob, including the case where your was-already-initialized marker gets reset back to its not-yet-initialized state.
		- In the event that this is a reasonable use case, you should make use of `pthread_once_t` in order to ensure that lazy initialization happens exactly once. (Though generally, the additional thread-safety accompanied by using this construct isn't necessary, since symbol resolution usually happens before a program gets a chance to spawn additional threads, and even in the event of use of `dlsym(3D)` to do symbol resolution at a later point in time, it's unlikely that this would be done by multiple threads at the same time, for the same symbol; yet if this can be expected to happen, then yes: you'd absolutely **need** to make use of `pthread_once_t`)
	- See file [/kos/src/libdl/README.md](../libdl/README.md) for more information on `STT_KOS_IDATA` symbols.

- The "always-use-INTERN-functions" trick:
	- This one is pretty much done automatically for you. If you look at any of libc's source files, you'll see lots of `libc_foo` (and sometimes `libd_foo`) symbols being declared, only to eventually appear in `DEFINE_PUBLIC_ALIAS(foo, libc_foo);` statements.
	- When a piece of code compiled as part of libc makes a function call, it will always call the libc-internal variant of that symbol (system headers, magic, and the `__CDECLARE` macro are designed to automatically redirect calls to e.g. `strlen()` made from inside of libc to the libc-internal symbol `libc_strlen()`)
	- This in turn makes it rather difficult (read: impossible) for programs to use the (badly designed and stupid if you ask me) ELF feature of overwriting library functions by simply declaring them yourself in your own program (I personally find the idea OK, but it shouldn't be the default; if you ask me: only `__attribute__((weak))` symbols should be subjugated to this special treatment). Anyways: I believe that this is a reasonable sacrifice, especially since practically no programs actually use this.
	- However, for those cases where symbols being overridable is actually important/necessary (e.g. `matherr(3)`), additional care must be taken, which brings me to the next trick...

- Use `dlsym(3D)` to access global data objects, and overridable symbols.
	- This might seem strange at first, but do make sure **not** to use the preceding `INTERN`-trick for PUBLIC data symbols. Because of COPY relocations (s.a. `R_386_COPY`), it is necessary to allow programs to essentially re-define these symbols to have new addresses that lie outside of libc (in particular: become part of the main program).
	- Conceptually, you can think of `R_386_COPY` to do the following:  

	  ```c
	  extern char **environ;
	  int main() {
	      printf("%p\n", &environ);
	  }
	  ```

	  The linker essentially encodes this as follows (NOTE: this only happens during linking; this isn't visible in `*.o` or `*.S` files, so do take this with a gain of salt)

	  ```asm
	  .section .got
	  environ:
	     .skip   ((Elf32_Sym *)LOOKUP_EXTERNAL_ELFSYM("libc.so", "environ"))->st_size

	  .section .rel.got
	     .long  MODULE_RELATIVE(environ)                                                # r_offset
	     .long  ELF32_R_INFO(R_386_COPY, LOOKUP_EXTERNAL_ELFSYM("libc.so", "environ"))  # r_info

	  .section .text
	  main:
	     ...
	     pushl  $environ    # This actually becomes a link-time constant w/o DT_TEXTREL.
	                        # The address printed isn't the address of libc's environ,
	                        # but rather that of the main program's copy of said symbol.
	                        # However, this also means that whenever libc wants to access
	                        # `environ', it needs to know the address of the main
	                        # program's override for said symbol, such that it can make
	                        # use of the same memory location and stay informed about any
	                        # potential alterations made by the main program.
	     pushl  $"%p\n"
	     call   printf
	     ...
	  ```

	  It should be obvious from the comments next to `pushl $environ`: because the main program essentially "re-defines" the effective runtime address of `environ` (and instructs `libdl` to initialize it by essentially `memcpy`-ing the contents of what libc's version of `environ` held at the time), any further modifications made by the main program (or libc, or any other library for that matter) must be visible to everyone else, even though the original symbol that was copied still exists in memory and (probably) still contains whatever it did at the time of becoming redundant.

	  And because copy relocations might be created for **any** PUBLIC data symbols (and are actually rather helpful since it allows `gcc(1)` and `ld(1)` to essentially know the runtime address of a library symbol, thus allowing them to generate more efficient assembly), we also have to deal with the possibility of **any** PUBLIC data symbol essentially being overwritten, meaning that when wanting to access them, we **have** to use `dlsym()`:

	  ```c
	  #if 0 /* <<< DON'T DO THIS. -- IT WON'T WORK FOR COPY RELOCATIONS */
	  INTERN int libc_mysymbol = 42;
	  DEFINE_PUBLIC_ALIAS(mysymbol, libc_mysymbol);
	  #else
	  PUBLIC int mysymbol = 42;
	  /* NOTE: This is essentially how every access must go, however you are allowed to
	   * cache the return value of `dlsym(3D)'. -- s.a. `/kos/src/libc/libc/globals.h' */
	  #define libc_mysymbol  (*(int **)dlsym(RTLD_DEFAULT, "mysymbol"))
	  #endif
	  ```

	- This way of accessing global symbols is simplified via the macros in `/kos/src/libc/libc/globals.h`, which you are encouraged to use, knowing that they will do their best to give you the most performance in terms of safely (and without relocations) accessing global data objects.
	- The same work-around also needs to be used to determine the final address of functions which programs may reasonably be expected to (or required to) override (such as `matherr(3)`).



### Special file: `/kos/src/libc/crt-features.h`

This file is the crt-features descriptor used while building libc. Because the act of building libc itself is considered to be a special case, and because libc's `INTERN` symbols mustn't share the same namespace as its public symbols (intern: `libc_strlen`; public: `strlen`), the `__CRT_HAVE_*` macros in here don't indicate a one-on-one mapping. Instead, the following mapping is implied:

- `__CRT_HAVE_foo` means that libc has a symbol `INTERN libc_foo` (*usually* exported as `foo`)
- `__CRT_HAVE_DOS$foo` means that libc has a symbol `INTERN libd_foo` (*usually* exported as `DOS$foo`)
- `__CRT_HAVE_KOS$foo` means a bug. -- Such a macro should never get defined in here

In conjunction with this, `<__crt.h>` has special handling for when `__BUILDING_LIBC` is defined, such that it understands that `__CRT_HAVE_*` symbols in this configuration exist in a special namespace. As such, -- assuming that `defined(__CRT_HAVE_strlen)` -- a declaration like:

```c
__CDECLARE(ATTR_PURE WUNUSED NONNULL((1)),size_t,NOTHROW_NCX,strlen,(char const *__restrict str),(str))
```

... normally expands to:

```c
__LIBC ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL strlen)(char const *__restrict str);
```

But when `__BUILDING_LIBC` was defined, it will instead expand to:

```c
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL strlen)(char const *__restrict str) ASMNAME("libc_strlen");
```

Because of the fact that export aliases exist, and not every symbol publicly exported from libc has an `INTERN` alias with `libc_` prefixed (e.g.: libc doesn't have a symbol `INTERN libc__ZSt9terminatev`, even though it does have a symbol `PUBLIC _ZSt9terminatev`), we can't make use of the public CRT feature listing (e.g.: as defined in `<i386-kos/crt-features/crt-kos32.h>`), but have to use our own, custom one that defines macros for exactly those symbols which **do** exist in the `libc_*` namespace.

Note however that in practise, you shouldn't need to worry about this file. -- It's one of the files that get created/updated automatically by `/kos/misc/magicgenerator/generate_headers.dee`, which is automatically run whenever one of the `/kos/src/libc/magic/*.c` files changes.

