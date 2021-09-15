
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

KOS's libc is designed and optimized to minimize the number of relocations that must be resolved in order to correctly load the library. This is similar to `libdl.so`, but unlike that library, libc is actually allowed to have *some* relocations. However, in the interest to minimize startup time, all relocations that *do* exist within libc need to have their existence rationalized (if only to add the hurdle of documentation/bureaucracy if one wishes to slow down libc load times because they were to lazy to come up with a relocation-less approach to implementing some feature\[\*\])

Running `readelf -rW bin/i386-kos-OD/lib/libc.so` yields:

```
Relocation section '.rel.dyn' at offset 0x113c88 contains 9 entries:
 Offset     Info    Type                Sym. Value  Symbol's Name
0011415c  00000008 R_386_RELATIVE
001141bc  00000008 R_386_RELATIVE
0011421c  00000008 R_386_RELATIVE
00114220  00000008 R_386_RELATIVE
00114224  00000008 R_386_RELATIVE
00114228  00000008 R_386_RELATIVE
001140c8  0014fd06 R_386_GLOB_DAT         001140e4   __stack_chk_guard
001140cc  00000023 R_386_TLS_DTPMOD32
001142dc  00101201 R_386_32               000482c3   __gxx_personality_v0

Relocation section '.rel.plt' at offset 0x113cd0 contains 5 entries:
 Offset     Info    Type                Sym. Value  Symbol's Name
001140b4  00016707 R_386_JUMP_SLOT        00047a07   __cxa_end_catch
001140b8  00000107 R_386_JUMP_SLOT        00000000   ___tls_get_addr
001140bc  00094507 R_386_JUMP_SLOT        00047977   __cxa_begin_catch
001140c0  00000207 R_386_JUMP_SLOT        00000000   dlsym
001140c4  000e2707 R_386_JUMP_SLOT        00047745   _Unwind_Resume
```

Other architectures display the same set of relocations with slight deviations as the result of different names for individual relocations. Though the total number of relocations should not deviate from the above base-line.

In the following, each of these relocations will be rationalized:

- The first `6` relocations (`R_386_RELATIVE`):
	- These are the result of the initialization of the `stdin`, `stdout` and `stderr` global variables, as available in `<stdio.h>`. No lazy/indirect initialization is performed for these symbols due to the fact that a majority of programs actually make use of these variables. As such, it stands to reason that by using the `STT_KOS_IDATA`-trick for initializing these could actually degrade performance, rather than aid it. For reference, see `/kos/src/libc/user/stdio.c`:

	```c
	#define DEFINE_DEFAULT_STD_FILE(name, io_flags, fd)                            \
		PRIVATE ATTR_SECTION(".data.crt.FILE.std_files")                           \
		struct iofile_data_novtab default_##name##_io = IOFILE_DATA_NOVTAB_INIT(); \
		INTERN ATTR_SECTION(".data.crt.FILE.std_files") FILE default_##name =      \
		__IO_FILE_INIT(NULL, 0, NULL, io_flags, fd, { 0 }, 0, (struct iofile_data *)&default_##name##_io)
	DEFINE_DEFAULT_STD_FILE(stdin, IO_LNBUF, STDIN_FILENO);             /* !Relocation: &default_stdin_io */
	DEFINE_DEFAULT_STD_FILE(stdout, IO_RW | IO_LNIFTYY, STDOUT_FILENO); /* !Relocation: &default_stdout_io */
	DEFINE_DEFAULT_STD_FILE(stderr, IO_RW | IO_LNIFTYY, STDERR_FILENO); /* !Relocation: &default_stderr_io */
	#undef DEFINE_DEFAULT_STD_FILE
	PUBLIC FILE *g_stdin  = &default_stdin;  /* !Relocation: &default_stdin */
	PUBLIC FILE *g_stdout = &default_stdout; /* !Relocation: &default_stdout */
	PUBLIC FILE *g_stderr = &default_stderr; /* !Relocation: &default_stderr */
	```

- The `R_386_GLOB_DAT` relocation against `__stack_chk_guard`:
	- A possible candidate for future removal, this relocation is the result of libc being compiled with `-fstack-protector-strong`. A global variable `extern uintptr_t __stack_chk_guard;` is defined that contains a random™ value which is used to detect stack corruption as the result of buffer overruns.  
	  Optimization potential exists because on KOS it is actually libc itself which defines this global variable, such that differently generated code could already resolve it at link-time (rather than run-time).  
	  A proposed solution to rid of this relocation would be to read GCC's source code and see if there is a way to alter the name of the symbol used and have it point at an `INTERN` alias of `__stack_chk_guard`. If this is not possible, an alternate solution might be to modify libc's assembly to hard-change the symbol's name prior to final assembly (similar to what `libdl.so` does to prevent relocations against `__gxx_personality_v0`; s.a. `COMPILE_WITH_ASM_FILTER from kos.misc.libmagic.steps.c`), though due to the large number of source files that partake in the creation of libc, this might add too much overhead to the build process, with too little gain in return. Further investigation might be warranted.
- The `R_386_TLS_DTPMOD32` relocation:
	- In order to facility `<pthread.h>` and a thread-local `errno`, libc includes a TLS section which contains 1 variable `current`. This variable holds everything needed for TLS and cannot be removed or circumvented without making pretty much everything about libc thread-unsafe. Working around this relocation would force libc to stray away from standard ELF thread-location variables support, which would be a bad idea due to the ease in implementation, integration with `libdl.so`, and interoperability with third-party libraries due to its standardization originating from outside the bounds of KOS development (going as far as GCC support).  
	  Removal of this relocation is out of the question, and the only feasible approach would be to move all of libc's TLS stuff into `libdl.so`, which is also a bad idea since `libdl.so` is meant to be unconscious and entirely disconnected of which libc is used (if any) and what libc does.
- The `R_386_32` relocation against `__gxx_personality_v0`:
	- This one is the result of `.data.rel.local.DW.ref.__gxx_personality_v0`, which is required to allow exceptions to be propagated through functions from within libc. the `__gxx_personality_v0` symbol, while already defined within `libc.so`, may actually be overwritten by `libstdc++` (if loaded), as the one provided by libc itself lacks support for c++ exceptions (and only supports KOS kernel exceptions).
- Jump relocations against symbols:
	- `__cxa_begin_catch`, `__cxa_end_catch`, `_Unwind_Resume`  
	  All of these symbols relate to c++ exception handling (which is used by libc to integrate into the KOS kernel exception system; s.a. exception-enabled system calls and CamelCase variants of standard functions found in `<kos/...>` headers, such as `Malloc` in `<kos/malloc.h>`)  
	  It stands to reason that these functions fall under the same category as `__stack_chk_guard`, in that their presence need not be necessary, and should the use of `COMPILE_WITH_ASM_FILTER` prove feasible for compiling libc, these relocations will surely be gotten rid of as well. But again: they bring along the same problems as `__stack_chk_guard`, in that they cannot be gotten rid of without somehow convincing gcc of using different names for the symbols apart of its internal ABI. Because just like with `__stack_chk_guard`, it is once again libc itself who exports these symbols for public used by other libraries, meaning they cannot safely be declared as `.hidden`, without simultaneously ridding the export table of their presence (which would break the ABI in a way that makes the system impossible to build).  
	  As such, the proposed solution is the same as with `__stack_chk_guard`, and these relocations might go away one day. But for the time being, they will stay.
- Jump relocations to `___tls_get_addr` (on other arches, this is `__tls_get_addr` instead):
	- This relocation does (and must) exist for the same reason as `R_386_TLS_DTPMOD32`. In order to facility support for both static and dynamic TLS variables (which are implemented and handled by `libdl.so`), a function needs to exist to load the effective runtime address of a TLS variable when the associated library was loaded using the dynamic TLS model. This is that function. It is part of the ABI (being defined in `libdl.so`), and cannot (and should not) be removed.
- Jump relocation against `dlsym`:
	- You may have already noticed that many other important function exported by `libdl.so` are missing, such as `dlopen` or `dltlsallocseg` (which surely is used by libc's pthread implementation, which yes: it is being used for that). The presences of one single remaining relocation against `dlsym` might give a hint as to how this is accomplished, and should that not be enough of a hint, an example `*(void **)&pdyn_dltlsallocseg = dlsym(NULL, "dltlsallocseg");` might...  
	  Sufficed to say, `dlsym` cannot be loaded in the same lazy (and relocation-less) manner, given that it is the `dlsym` function which is used to load other functions that would otherwise appear as jump relocations themselves. As such, this is another relocation that cannot be gotten rid of without deviating from standards going against my wishes to keep `libdl.so` blissfully unaware of the internal workings of `libc.so` (if not for this, it would be possible to have `libdl.so` pass knowledge regarding the address of `dlsym` to libc in some other manner).  
	  Yet if one would go so far as to consider such a solution, "what would be the point?" I may ask. For the entire point of minimizing relocations is to ensure the swift and efficient startup time of libc. The addition of unnecessary complexity in libdl would run counter to this goal, especially since (admittedly) relocations aren't *that* expensive.


\[\*\] There are ways to implemented pretty much any functionality without relocations. Even public symbols that need to be pre-initialized as arrays of pointers (e.g. `sys_errlist(3)`) fall under this category. Don't believe me? Well: libc does export a fully working `sys_errlist`, but doesn't have any relocations associated with how the strings of that array are set. Take a look at `/kos/src/libc/user/bits.crt.sys_errlist.c` and `STT_KOS_IDATA`


If relocations exist in libc that are not rationalized by this function, their presence may be considered a bug and be treated as such, either (preferably) by working around the need of such a relocation, or (in the case such a work-around would yield no advantage over simply ignoring it), by documenting its presence in this file.
