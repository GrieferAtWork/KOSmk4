## X86 assembly cheatsheet

### push/pop %esp behavior:

Push with `%esp`-relative memory operand:

```asm
pushl  $42
pushl  0(%esp)  # (re-)pushes the `$42` (addr is calculated before %esp is changed)
```


Pop with `%esp`-relative memory operand:

```asm
pushl $0
pushl $42
popl  0(%esp) # Overrides the `pushl $0` from above with `$42`
popl  %eax    # %eax = 42
```

### Calling conventions

| i386  | cdecl           | stdcall         | fastcall             | int80h       | sysenter     | lcall7       |
| ----- | --------------- | --------------- | -------------------- | ------------ | ------------ | ------------ |
| retpc | `0(%esp)`       | `0(%esp)`       | `0(%esp)`            | *nextpc*     | `%edi`       | *nextpc*     |
| spoff | `0`             | `N*4` | `N<=2`: `0` <br> ` N>2`: `(N-2)*4` | `0`      | `=%ebp`      | `0`          |
| r32   | `%eax`          | `%eax`          | `%eax`               | `%eax`       | `%eax`       | `%eax`       |
| r64   | `%eax:%edx`     | `%eax:%edx`     | `%eax:%edx`          | `%eax:%edx`  | `%eax:%edx`  | `%eax:%edx`  |
| sysno |                 |                 |                      | `%eax`       | `%eax`       | `lcall $7, $0`: `%eax`<br>`lcall $7, $X`: `X` |
| excpt |                 |                 |                      | `%eflags.DF` | `%eflags.DF` | `%eflags.DF` |
| a0    | `4(%esp)`       | `4(%esp)`       | `%ecx`               | `%ebx`       | `%ebx`       | `0(%esp)`    |
| a1    | `8(%esp)`       | `8(%esp)`       | `%edx`               | `%ecx`       | `%ecx`       | `4(%esp)`    |
| a2    | `12(%esp)`      | `12(%esp)`      | `4(%esp)`            | `%edx`       | `%edx`       | `8(%esp)`    |
| a3    | `16(%esp)`      | `16(%esp)`      | `8(%esp)`            | `%esi`       | `%esi`       | `12(%esp)`   |
| a4    | `20(%esp)`      | `20(%esp)`      | `12(%esp)`           | `%edi`       | `0(%ebp)`    | `16(%esp)`   |
| a5    | `24(%esp)`      | `24(%esp)`      | `16(%esp)`           | `%ebp`       | `4(%ebp)`    | `20(%esp)`   |
| aN    | `(4+N*4)(%esp)` | `(4+N*4)(%esp)` | `(4+(N-2)*4)(%esp)`  |              |              |              |
| Uses  | `LIBCCALL`, `LIBDCALL`, `LIBKCALL` | `KCALL` | `FCALL`   | `int $0x80`  | `sysenter`  |`lcall $7, $...` |
| Keep  | `%ebx`, `%esi`, `%edi`, `%ebp` | *ditto* | *ditto*       | *all*        | ...          | *all*        |
| Clob  | `%eax`, `%ecx`, `%edx`, `%eflags` | *ditto* | *ditto*    | *none*       |`%ecx`, `%edx`| *none*       |


| x86_64| msabi               | sysvabi             | syscall             |
| ----- | ------------------- | ------------------- | ------------------- |
| retpc | `0(%rsp)`           | `0(%rsp)`           | *nextpc*            |
| r32   | `%eax`              | `%eax`              |                     |
| r64   | `%rax`              | `%rax`              | `%rax`              |
| r128  | `%rax:%rdx`         | `%rax:%rdx`         | `%rax:%rdx`         |
| sysno |                     |                     | `%rax`              |
| excpt |                     |                     | `%rflags.DF`        |
| a0    | `%rcx`              | `%rdi`              | `%rdi`              |
| a1    | `%rdx`              | `%rsi`              | `%rsi`              |
| a2    | `%r8`               | `%rdx`              | `%rdx`              |
| a3    | `%r9`               | `%rcx`              | `%r10`              |
| a4    | `8(%rsp)`           | `%r8`               | `%r8`               |
| a5    | `16(%rsp)`          | `%r9`               | `%r9`               |
| aN    | `(8+(N-4)*8)(%rsp)` | `(8+(N-6)*8)(%rsp)` |                     |
| Uses  |`LIBDCALL` | `LIBCCALL`, `LIBKCALL`, `KCALL`, `FCALL` | `syscall` |
| Keep  | `%rbx`, `%rdi`, `%rsi`, `%rbp`, `%r12`, `%r13`, `%r14`, `%r15` | `%rbx`, `%rbp`, `%r12`, `%r13`, `%r14`, `%r15` | ... |
| Clob  | `%rax`, `%rcx`, `%rdx`, `%r8`, `%r9`, `%r10`, `%r11`, `%rflags` | `%rax`, `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`, `%r10`, `%r11`, `%rflags` | `%rcx`, `%r11` |




