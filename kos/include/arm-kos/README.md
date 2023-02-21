
## Cheat sheet

Cheat sheet for someone that knows a lot about x86 assembly, but is pretty much a total noob when it comes to arm. -- Like me ;)

### Registers

| Group               | Registers
|---------------------|----------------------------------------------
| GeneralPurpose      | `r0`, `r1`, `r2`, ..., `r15`
| StackPointer        | `sp = r13`
| LinkRegister        | `lr = r14` (return address for leaf functions)
| ProgramCounter      | `pc = r15`

| Name                | Description
|---------------------|----------------------------------------------
| APSR                | x86's `%eflags` (contains condition)
| CPSR                | Super-set of APSR, w/ access to execute-mode bits (e.g. kernel- vs. user-space)


### Thumb vs. ARM

- [Really interesting & insightful explaination](https://stackoverflow.com/a/9370417/3296587)
	- TLDR: The `bx @ADDR@` essentially `@ADDR@ & 1` into `APSR.T`
- Important: in assembly, enter thumb-mode with `.thumb`
- Important: in thumb-mode assembly, thumb function labels must be preceded by `.thumb_func`
	- This causes the function's address label to be or'd with `1`, and its use by `bx` to force-enable thumb-mode


### Calling convention

| Category | Registers
|----------|----------------------------------------------
| args     | `r0, r1, r2, r3, [stack...]`
| return   | `r0, r1`
| clobber  | `r0, r1, r2, r3, r12`
| preserve | `r4, r5, r6, r7, r8, r9, r10, r11, sp=r13, lr=r14`


### Syscall call calling convention

| Category | Registers
|----------|----------------------------------------------
| args     | `r0, r1, r2, r3, r4, r5, r6` (yes: 7 argument registers)
| return   | `r0, r1`
| sysno    | `r7` (EABI), `swi #NR` (OABI)
| except   | `(r7 & 0x800000) != 0` \[*\]

\[*\]: KOS-specific (s.a. `ARM_XSYSCALL_FLAG` from `<arm-kos/kos/asm/syscall.h>`)



### Push / pop

- `push   {r0, r1, r2, r3}`
	- same as:
	  ```asm
	  push   {r3}
	  push   {r2}
	  push   {r1}
	  push   {r0}
	  ```
	- Creates on-stach:
	  ```c
	  struct buf {
	      uint32_t r0;
	      uint32_t r1;
	      uint32_t r2;
	      uint32_t r3;
	  };
	  ```
	- Registeres are always pushed from highest-number to lowerest-number
	- It doesn't make a difference which order you write them in `push`


### Condition code suffixes

| Code          | Mnemonic   | Meaning                           | Operation           | Check (in `APSR`)
|---------------|------------|-----------------------------------|---------------------|-------------------
| `0b0000[0x0]` | `EQ`       | Equal                             | `x == y`, `x == 0`  | `Z == 1`
| `0b0001[0x1]` | `NE`       | NotEqual                          | `x != y`, `x != 0`  | `Z == 0`
| `0b0010[0x2]` | `CS`, `HS` | CarrySet, unsigned_Higher_or_Same | `(unsigned)x >= y`  | `C == 1`
| `0b0011[0x3]` | `CC`, `LO` | CarryClear, unsigned_LOwer        | `(unsigned)x < y`   | `C == 0`
| `0b0100[0x4]` | `MI`       | Minus                             | `(signed)x < 0`     | `N == 1`
| `0b0101[0x5]` | `PL`       | Plus                              | `(signed)x >= 0`    | `N == 0`
| `0b0110[0x6]` | `VS`       | ValueStripped                     | *Overflow*          | `V == 1`
| `0b0111[0x7]` | `VC`       | ValueCorrect                      | *No overflow*       | `V == 0`
| `0b1000[0x8]` | `HI`       | unsigned_HIgher                   | `(unsigned)x > y`   | `C == 1 && Z == 0`
| `0b1001[0x9]` | `LS`       | unsigned_Lower_or_Same            | `(unsigned)x <= y`  | `C == 0 || Z == 1`
| `0b1010[0xa]` | `GE`       | signed_Greater_than_or_Equal      | `(signed)x >= y`    | `N == V`
| `0b1011[0xb]` | `LT`       | signed_LessThan                   | `(signed)x < y`     | `N != V`
| `0b1100[0xc]` | `GT`       | signed_GreaterThan                | `(signed)x > y`     | `Z == 0 and N == V`
| `0b1101[0xd]` | `LE`       | signed_Less_than_or_Equal         | `(signed)x <= y`    | `Z == 1 or N != V`
| `0b1110[0xe]` | `AL`       | ALways                            | -                   | `true`


**\[From\]**: Table A8-1 Condition codes

### Operand size suffix

| Width | canonical name   | arm                    | x86
|-------|------------------|------------------------|-------------------
| `1`   | `b`, byte        | `ldrb   r0,     [r2]`  | `movb (%r2), %r0`
| `1`   | `b`, byte        | `strb   r0,     [r2]`  | `movb %r0, (%r2)`
| `2`   | `w`, word        | `ldrh   r0,     [r2]`  | `movw (%r2), %r0`
| `4`   | `l`, dword       | `ldr    r0,     [r2]`  | `movl (%r2), %r0`
| `8`   | `q`, qword       | `ldrd   r0, r1, [r2]`  | `movl 0(%r2), %r0; movl 4(%r2), %r1`


### Operands

```asm
	mov    r0, #0x000000ff  // x86: `movl $0x000000ff, %r0'   r0 = 0x000000ff;
	ldr    r0, =0x12345678  // x86: `movl $0x12345678, %r0'   r0 = 0x12345678;
	ldr    r0, .Lmyconst    // x86: `movl $0x12345678, %r0'   r0 = 0x12345678;
	ldr    r0, [r1, #42]    // x86: `movl 42(%r1), %r0'       r0 = *(uint32_t *)(r1 + 42);
	ldr    r0, [r1, r2]     // x86: `movl (%r1,%r2), %r0'     r0 = *(uint32_t *)(r1 + r2);
	ldr    r0, [r1, #42]!   //                                r0 = *(uint32_t *)(r1 + 42); r1 += 42;
	ldr    r0, [r1, r2]!    //                                r0 = *(uint32_t *)(r1 + r2); r1 += r2;
	ldr    r0, [r1], #42    //                                r0 = *(uint32_t *)(r1); r1 += 42;
	ldr    r0, [r1], r2     //                                r0 = *(uint32_t *)(r1); r1 += r2;
.Lmyconst:
	.int 0x12345678
```


### Simple instructions:

| arm               | C                   | x86
|-------------------|---------------------|-------------------------------
| `add r0, r1, r2`  | `r0 = r1 + r2;`     | `movl %r2, %r0; addl %r1, %r0`
| `adc r0, r1, r2`  | `r0 = r1 + r2 + C;` | `movl %r2, %r0; adcl %r1, %r0`
| `sub r0, r1, r2`  | `r0 = r1 - r2;`     | `movl %r2, %r0; subl %r1, %r0`
| `sbc r0, r1, r2`  | `r0 = r1 - r2 - C;` | `movl %r2, %r0; sbbl %r1, %r0`
| `and r0, r1, r2`  | `r0 = r1 & r2;`     | `movl %r2, %r0; andl %r1, %r0`
| `orr r0, r1, r2`  | `r0 = r1 \| r2;`    | `movl %r2, %r0; orl  %r1, %r0`
| `eor r0, r1, r2`  | `r0 = r1 ^ r2;`     | `movl %r2, %r0; xorl %r1, %r0`
| `bic r0, r1, r2`  | `r0 = r1 & ~r2;`    | `movl %r2, %r0; notl %r0; andl %r1, %r0`
| `mvn r0, r1`      | `r0 = ~r1;`         | `movl %r1, %r0; notl %r0`



### Exception handling / unwinding

Instead of simply using CFI, arm uses its own arch-specific (and much LESS powerful) system, that can't even keep up when trying to define different unwind rules for different positions within a function (ugh; I ALREADY don't like you, `.ARM.extab`)

Because of that, in order to acutally get full debug information, you need to define BOTH arm's weird (and underpowered) debug info, as WELL as regular CFI.

Anyways: here's what you need to know:

| ARM                 | CFI
|---------------------|----------------------------------------------
| `.fnstart`          | `.cfi_startproc`
| `.fnend`            | `.cfi_endproc`
| `.save {fp, lr}`    | `.cfi_rel_offset fp, 0; .cfi_rel_offset lr, 4;`
| `.pad #64`          | `.cfi_adjust_cfa_offset 64`



### Interrupts/exceptions

The interrupt vector is (conventionally) located at `(VIRT void *)0` and consists of `8` 32-bit instructions (that get branched to when interrupts/exceptions are triggered, and usually are themselves instructions that branch once again to the actual interrupt handler)

- Interrupt: Triggered by hardware (can happen at any moment interrupts aren't disabled; also includes preemptive interrupts)
- Exception: Triggered explicitly as the result of actions taken by software

| Address\[index\]    | Name  | Interrupt/exception   | Description
|---------------------|-------|-----------------------|-----------------------
| `0x00000000[0]`     | `RES` | Exception             | Reset
| `0x00000004[1]`     | `UND` | Exception             | Undefined instruction
| `0x00000008[2]`     | `SWI` | Exception             | Software interrupt (`swi`)
| `0x0000000C[3]`     | `PAB` | Exception             | Prefetch abort
| `0x00000010[4]`     | `DAB` | Exception             | Data abort (#PF)
| `0x00000014[5]`     | -     | -                     | -
| `0x00000018[6]`     | `IRQ` | Interrupt             | Interrupt
| `0x0000001C[7]`     | `FIQ` | Interrupt             | Fast interrupt

**\[From\]**: Table B1-3 Offsets from exception base addresses




### Atomic operations how-to

| ARMv?               | Bit-width             | Howto
|---------------------|-----------------------|-----------------------
| `armv4`, `armv5`    | 8, 16, 32, 64         | **\[1\]** Kernel support
| `armv6`             | 8, 16                 | **\[2\]** Align(32)
| `armv6`             | 32                    | **\[3\]** `ldrex` + `strex`
| `armv6`             | 64                    | **\[1\]** Kernel support
| `armv7`             | 8, 16, 32, 64         | **\[3\]** `ldrex` + `strex`
| `armv8+`            | 8, 16, 32, 64         | **\[4\]** `ldaex` + `stlex`


**\[1\]** Kernel support:
> Implement `atomic_cmpxch` (64-bit):
> ```asm
> .Lcritical_begin:
>     ldmia  @BASE@, {@REAL_OLDVAL_LO32@, @REAL_OLDVAL_HI32@}
>     cmp    @REAL_OLDVAL_LO32@, @OLDVAL_LO32@
>     cmpeq  @REAL_OLDVAL_HI32@, @OLDVAL_HI32@
> .Lcritical_end:
>     stmiaeq @BASE@, {@NEWVAL_LO32@, @NEWVAL_HI32@}
> ```
> All handlers for interrupts that can happened witin `.Lcritical_begin ... .Lcritical_end` (iow: PAB, DAB, IRQ, FIQ) must check if this was the case, and if so: reset the return-pc to `.Lcritical_begin`. \
> 8-, 16- and 32-bit atomics can be implemented using the same trick, or by aligning addresses and calling the 64-bit variant above. \
> IMPORTANT: Architectures that use this trick can't (and don't) support SMP. \
> NOTE: Linux-compatible kernel support is exposed in `<arm-kos/kos/asm/kuser.h>`

**\[2\]** Align(N):
> Align address to N bits and perform an N-bit-wide atomic operation

**\[3\]** `ldrex` + `strex`:
> Implement `atomic_cmpxch_weak`:
> ```asm
>     dmb    ish                  /* on armv6: `mcr p15, 0, r0, c7, c10, 5` */
> 1:  ldrex* @REAL_OLDVAL@, [@BASE@]
>     cmp    @REAL_OLDVAL@, @OLDVAL@
>     bne    2f
>     strex* @TEMP_REGISTER@, @NEWVAL@, [@BASE_REGISTER@]
>     cmp    @TEMP_REGISTER@, #0  /* Check status */
>     bne    1b                   /* Repeat if STATUS != 0 */
> 2:  dmb    ish                  /* on armv6: `mcr p15, 0, r0, c7, c10, 5` */
> ```
> Where `*` is either `""` (nothing) for 32-bit, or `b` / `h` for 8/16-bit. \
> Note that 8/16/64-bit are only supported starting with `armv7`! \
> The 64-bit variant or this uses suffix `d` and requires register-pairs.

**\[4\]** `ldaex` + `stlex`:
> Same as **\[3\]**, except that `dmb ish` can be omitted, and `ldaex` + `stlex` are used instead of `ldrex` + `strex`.




### Cache control

TODO: This seems to be on the level of atomics when it comes to complexity

Figure this out and document here (for reference: `linux:/arch/arm/mm/cache-*`)

