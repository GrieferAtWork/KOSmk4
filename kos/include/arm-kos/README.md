
## Cheat sheet

Cheat sheet for someone that know a lot about x86 assembly, but is pretty much totally new to arm. -- like me ;)

### Registers

| Group               | Registers
|---------------------|----------------------------------------------
| General purpose     | `r0`, `r1`, `r2`, ..., `r15`
| SP                  | `sp`, `r13`
| LR                  | `lr`, `r14` (return address for leaf functions)
| PC                  | `pc`, `r15`

| Name                | Description
|---------------------|----------------------------------------------
| APSR                | x86's `%eflags` (contains condition)
| CPSR                | Super-set of APSR, w/ access to execute-mode bits (kernel vs. user-space)


### Calling convention

| Category | Registers
|----------|----------------------------------------------
| args     | `r0, r1, r2, r3, [stack...]`
| return   | `r0, r1`
| clobber  | `r0, r1, r2, r3, r12`
| preserve | `r4, r5, r6, r7, r8, r9, r10, r11, r13=sp, r14=lr`


### Syscall call calling convention

| Category | Registers
|----------|----------------------------------------------
| args     | `r0, r1, r2, r3, r4, r5, r6` (yes: 7 argument registers)
| return   | `r0, r1`
| sysno    | `r7` (EABI), `swi #NR` (OABI)
| except   | `(r7 & 0x800000) != 0`



### Push / pop

- `push   {r0, r1, r2, r3}`
	- same as:
	  ```asm
	  push   {r0}
	  push   {r1}
	  push   {r2}
	  push   {r3}
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


### Operand size suffix

| Width | canonical name   | arm                    | x86
|-------|------------------|------------------------|-------------------
| `1`   | `b`, byte        | `ldrb   r0,     [r2]`  | `movb (%r2), %r0`
| `1`   | `b`, byte        | `strb   r0,     [r2]`  | `movl %r0, (%r2)`
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
