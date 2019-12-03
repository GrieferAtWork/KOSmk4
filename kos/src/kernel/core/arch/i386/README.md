
### Conventions
- In places where code should compile for both i386 and x86_64, registers should be addressed using `p` instead of the `e` in their names:  

  ```c
  #include <kos/kernel/cpu-state.h>
  #include <kos/kernel/cpu-state-compat.h> // Defines `gp_pax'
  ...
  struct gpregs gp;
  gp.gp_pax = 42;
  // Same as:
  #ifdef __x86_64__
  struct gpregs64 gp;
  gp.gp_rax = 42;
  #else /* __x86_64__ */
  struct gpregs32 gp;
  gp.gp_eax = 42;
  #endif /* !__x86_64__ */
  ```

- In hand-written assembly, the indentation of instruction operands is aligned on the same column, such that an instruction should always be written as:  

  ```asm
  <TAB>movl   $42, %eax
  ```

	- Here, the first operand always starts 7 characters after the start of the mnemonic. Since this is somewhat difficult to remember, once can easily check if the correct alignment is used by code like this:  

    ```asm
    <TAB>EXTERN(foo)
    <TAB>movl   $foo, %eax
    <TAB>INTERN(bar)
    <TAB>movl   $bar, %eax
    ```

	  You can easily tell that the operands always start after the left-parenthesis of properly indented `EXTERN()` or `INTERN()` annotations

### Changes made to i386 ABI specifications in kernel-space

- The state of `EFLAGS.DF` is undefined at any point in time
	- All code must be compiled with gcc's `-mcld` flag
	- Hand-written assembly that uses `rep` instructions must always set the direction flag explicitly (using `std` or `cld`)
	- This is done since user-space might choose to change the state of `EFLAGS.DF`, and by specifying this flag as undefined whilst in kernel-space, as well as given the fact that user-space `EFLAGS` as a whole is always saved via the IRET tail, this prevents the need to explicitly `cld` the DF flag at every kernel entry point
	- STD: abi386-4:3-29 specifies that `EFLAGS.DF` may be assumed to be `0` on function entry
- FPU
	- The kernel-space use of floating point instructions/registers is technically allowed, however highly discouraged as any floating point instruction may `THROW()` an `E_BAD_ALLOC` exception, since floating point registers are lazily allocated on first use.
	- Additionally, FPU registers are *not* saved or emptied on kernel entry and must as such be used with care.
	- STD: abi386-4:3-12 specifies that _`%st(1)`_ _through_ _`%st(7)`_ _may_ _be_ _assumed_ _to_ _be_ _`0`_ _on_ _function_ _entry_
- Text addresses
	- All kernel-space code is linked above `0xc0000000` (3GiB..4Gib) on i386 and `0xffffffff80000000` (-2Gib..0)

### References
- [abi386-4](http://www.sco.com/developers/devspecs/abi386-4.pdf)




