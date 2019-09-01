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
#ifndef _I386_KOS_ASM_INTRIN_H
#define _I386_KOS_ASM_INTRIN_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__

__SYSDECL_BEGIN


#ifdef __COMPILER_HAVE_GCC_ASM
#ifdef __KERNEL__
#define __PRIVATE_PREFIX_REP_CLD "cld\n\t"
#else
#define __PRIVATE_PREFIX_REP_CLD /* nothing */
#endif


/* Read from / write to general purpose registers. */
#ifdef __x86_64__
#ifdef __COMPILER_HAVE_REGISTER_VARS
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsp)(void) { __register __UINTPTR_TYPE__ __rsp __asm__("%rsp"); return __rsp; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbp)(void) { __register __UINTPTR_TYPE__ __rbp __asm__("%rbp"); return __rbp; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbx)(void) { __register __UINTPTR_TYPE__ __rbx __asm__("%rbx"); return __rbx; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr12)(void) { __register __UINTPTR_TYPE__ __r12 __asm__("%r12"); return __r12; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr13)(void) { __register __UINTPTR_TYPE__ __r13 __asm__("%r13"); return __r13; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr14)(void) { __register __UINTPTR_TYPE__ __r14 __asm__("%r14"); return __r14; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr15)(void) { __register __UINTPTR_TYPE__ __r15 __asm__("%r15"); return __r15; }
__FORCELOCAL void (__wrsp)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __rsp __asm__("%rsp"); __rsp = __val; }
__FORCELOCAL void (__wrbp)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __rbp __asm__("%rbp"); __rbp = __val; }
__FORCELOCAL void (__wrbx)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __rbx __asm__("%rbx"); __rbx = __val; }
__FORCELOCAL void (__wrr12)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __r12 __asm__("%r12"); __r12 = __val; }
__FORCELOCAL void (__wrr13)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __r13 __asm__("%r13"); __r13 = __val; }
__FORCELOCAL void (__wrr14)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __r14 __asm__("%r14"); __r14 = __val; }
__FORCELOCAL void (__wrr15)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __r15 __asm__("%r15"); __r15 = __val; }
#else /* __COMPILER_HAVE_REGISTER_VARS */
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsp)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%rsp, %q0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbp)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%rbp, %q0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbx)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%rbx, %q0" : "=g" (__res)); return __res; }
__FORCELOCAL void (__wrsp)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%rsp" : : "g" (__val) : "%rsp"); }
__FORCELOCAL void (__wrbp)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%rbp" : : "g" (__val) : "%rbp"); }
__FORCELOCAL void (__wrbx)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%rbx" : : "g" (__val) : "%rbx"); }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr12)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%r12, %q0" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr13)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%r13, %q0" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr14)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%r14, %q0" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdr15)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movq %%r15, %q0" : "=r" (__res)); return __res; }
__FORCELOCAL void (__wrr12)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%r12" : : "r" (__val) : "%r12"); }
__FORCELOCAL void (__wrr13)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%r13" : : "r" (__val) : "%r13"); }
__FORCELOCAL void (__wrr14)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%r14" : : "r" (__val) : "%r14"); }
__FORCELOCAL void (__wrr15)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movq %q0, %%r15" : : "r" (__val) : "%r15"); }
#endif /* !__COMPILER_HAVE_REGISTER_VARS */
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdip)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("leaq .(%%rip), %q0" : "=r" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdflags)(void) { __UINTPTR_TYPE__ __result; __asm__ __volatile__("pushfq; popq %0" : "=g" (__result)); return __result; }
__FORCELOCAL void (__wrflags)(__UINTPTR_TYPE__ __fl) { __asm__ __volatile__("pushq %q0; popfq" : : "g" (__fl) : "cc"); }
#else /* __x86_64__ */
#ifdef __COMPILER_HAVE_REGISTER_VARS
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsp)(void) { __register __UINTPTR_TYPE__ __esp __asm__("%esp"); return __esp; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbp)(void) { __register __UINTPTR_TYPE__ __ebp __asm__("%ebp"); return __ebp; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rddi)(void) { __register __UINTPTR_TYPE__ __edi __asm__("%edi"); return __edi; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsi)(void) { __register __UINTPTR_TYPE__ __esi __asm__("%esi"); return __esi; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbx)(void) { __register __UINTPTR_TYPE__ __ebx __asm__("%ebx"); return __ebx; }
__FORCELOCAL void (__wrsp)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __esp __asm__("%esp"); __esp = __val; }
__FORCELOCAL void (__wrbp)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __ebp __asm__("%ebp"); __ebp = __val; }
__FORCELOCAL void (__wrdi)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __edi __asm__("%edi"); __edi = __val; }
__FORCELOCAL void (__wrsi)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __esi __asm__("%esi"); __esi = __val; }
__FORCELOCAL void (__wrbx)(__UINTPTR_TYPE__ __val) { __register __UINTPTR_TYPE__ __ebx __asm__("%ebx"); __ebx = __val; }
#else /* __COMPILER_HAVE_REGISTER_VARS */
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsp)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl %%esp, %k0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbp)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl %%ebp, %k0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rddi)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl %%edi, %k0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdsi)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl %%esi, %k0" : "=g" (__res)); return __res; }
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdbx)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl %%ebx, %k0" : "=g" (__res)); return __res; }
__FORCELOCAL void (__wrsp)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movl %k0, %%esp" : : "g" (__val) : "%esp"); }
__FORCELOCAL void (__wrbp)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movl %k0, %%ebp" : : "g" (__val) : "%ebp"); }
__FORCELOCAL void (__wrdi)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movl %k0, %%edi" : : "g" (__val) : "%edi"); }
__FORCELOCAL void (__wrsi)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movl %k0, %%esi" : : "g" (__val) : "%esi"); }
__FORCELOCAL void (__wrbx)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("movl %k0, %%ebx" : : "g" (__val) : "%ebx"); }
#endif /* !__COMPILER_HAVE_REGISTER_VARS */
#if defined(__PIC__) || defined(__PIE__) || defined(__pic__) || defined(__pie__)
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdip)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("call 1f; 1: popl %0" : "=g" (__res)); return __res; }
#else
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdip)(void) { __UINTPTR_TYPE__ __res; __asm__ __volatile__("movl $., %k0" : "=g" (__res)); return __res; }
#endif
__FORCELOCAL __ATTR_WUNUSED __UINTPTR_TYPE__ (__rdflags)(void) { __UINTPTR_TYPE__ __result; __asm__ __volatile__("pushfl; popl %0" : "=g" (__result)); return __result; }
__FORCELOCAL void (__wrflags)(__UINTPTR_TYPE__ __fl) { __asm__ __volatile__("pushl %k0; popfl" : : "g" (__fl) : "cc"); }
#endif /* !__x86_64__ */
__FORCELOCAL __ATTR_NORETURN void (__wrip)(__UINTPTR_TYPE__ __val) { __asm__ __volatile__("jmp *%0" : : "g" (__val)); __builtin_unreachable(); }


__FORCELOCAL __ATTR_WUNUSED __BOOL (__verr)(__UINT16_TYPE__ __seg) { __BOOL __result; __asm__ __volatile__("verr %w1" : "=@ccz" (__result) : "g" (__seg)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __BOOL (__verw)(__UINT16_TYPE__ __seg) { __BOOL __result; __asm__ __volatile__("verw %w1" : "=@ccz" (__result) : "g" (__seg)); return __result; }
__FORCELOCAL void (__clc)(void) { __asm__ __volatile__("clc" : : : "cc"); }
__FORCELOCAL void (__cmc)(void) { __asm__ __volatile__("cmc" : : : "cc"); }
__FORCELOCAL void (__stc)(void) { __asm__ __volatile__("stc" : : : "cc"); }
__FORCELOCAL void (__cld)(void) { __COMPILER_BARRIER(); __asm__ __volatile__("cld" /*: : : "cc"*/); __COMPILER_BARRIER(); }
__FORCELOCAL void (__std)(void) { __COMPILER_BARRIER(); __asm__ __volatile__("std" /*: : : "cc"*/); __COMPILER_BARRIER(); }
__FORCELOCAL void (__cli)(void) { __asm__ __volatile__("cli" : : : "memory"); }
__FORCELOCAL void (__sti)(void) { __asm__ __volatile__("sti" : : : "memory"); }
__FORCELOCAL void (__clflush)(void *__p) { struct __cl { __BYTE_TYPE__ __b[64]; }; __asm__ __volatile__("clflush %0" : : "m" (*(struct __cl *)__p)); }
__FORCELOCAL void (__cpuid)(__UINT32_TYPE__ __leaf_eax, __UINT32_TYPE__ *__peax, __UINT32_TYPE__ *__pecx, __UINT32_TYPE__ *__pedx, __UINT32_TYPE__ *__pebx) { __asm__("cpuid" : "=a" (*__peax), "=c" (*__pecx), "=d" (*__pedx), "=b" (*__pebx) : "a" (__leaf_eax)); }
__FORCELOCAL void (__cpuid2)(__UINT32_TYPE__ __leaf_eax, __UINT32_TYPE__ __leaf_ecx, __UINT32_TYPE__ *__peax, __UINT32_TYPE__ *__pecx, __UINT32_TYPE__ *__pedx, __UINT32_TYPE__ *__pebx) { __asm__("cpuid" : "=a" (*__peax), "=c" (*__pecx), "=d" (*__pedx), "=b" (*__pebx) : "a" (__leaf_eax), "c" (__leaf_ecx)); }
__FORCELOCAL __ATTR_WUNUSED __UINT8_TYPE__ (__daa)(__UINT8_TYPE__ __x) { __UINT8_TYPE__ __result; __asm__("daa" : "=a" (__result) : "0" (__x) : "cc"); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT8_TYPE__ (__dal)(__UINT8_TYPE__ __x) { __UINT8_TYPE__ __result; __asm__("dal" : "=a" (__result) : "0" (__x) : "cc"); return __result; }
__FORCELOCAL __ATTR_NORETURN void (__rsm)(void) { __asm__ __volatile__("rsm" : : : "memory"); __builtin_unreachable(); }
__FORCELOCAL void (__clac)(void) { __asm__ __volatile__("clac" : : : "memory"); }
__FORCELOCAL void (__stac)(void) { __asm__ __volatile__("stac" : : : "memory"); }
__FORCELOCAL void (__hlt)(void) { __asm__ __volatile__("hlt" : : : "memory"); }
__FORCELOCAL void (__into)(void) { __asm__ __volatile__("into"); }
__FORCELOCAL void (__int3)(void) { __asm__ __volatile__("int {$}3" : ); }
#ifdef __INTELLISENSE__
void (__int)(__UINT8_TYPE__ __intno);
#elif !defined(__NO_XBLOCK)
#define __int(intno)  __XBLOCK({ __asm__ __volatile__("int %0" : : "N" (intno)); (void)0; })
#else
#define __int(intno)  __asm__ __volatile__("int %0" : : "N" (intno))
#endif
__FORCELOCAL void (__invd)(void) { __asm__ __volatile__("invd"); }
__FORCELOCAL void (__wbinvd)(void) { __asm__ __volatile__("wbinvd"); }
__FORCELOCAL void (__invlpg)(void *__p) { __asm__ __volatile__("invlpg" : : "m" (*(int *)__p)); }
__FORCELOCAL void (__lfence)(void) { __COMPILER_READ_BARRIER(); __asm__ __volatile__("lfence"); __COMPILER_READ_BARRIER(); }
__FORCELOCAL void (__sfence)(void) { __COMPILER_WRITE_BARRIER(); __asm__ __volatile__("sfence"); __COMPILER_WRITE_BARRIER(); }
__FORCELOCAL void (__mfence)(void) { __COMPILER_BARRIER(); __asm__ __volatile__("mfence"); __COMPILER_BARRIER(); }
__FORCELOCAL void (__lgdt)(__UINT16_TYPE__ __limit, void *__base) { struct __ATTR_PACKED { __UINT16_TYPE__ __limit; void *__base; } __arg; __arg.__limit = __limit; __arg.__base = __base; __asm__ __volatile__("lgdt %0" : : "m" (__arg)); }
__FORCELOCAL void (__lidt)(__UINT16_TYPE__ __limit, void *__base) { struct __ATTR_PACKED { __UINT16_TYPE__ __limit; void *__base; } __arg; __arg.__limit = __limit; __arg.__base = __base; __asm__ __volatile__("lidt %0" : : "m" (__arg)); }
#ifdef __x86_64__
__FORCELOCAL void (__lgdt_p)(void const *__data) { typedef struct { __UINT16_TYPE__ __x[5]; } __T; __asm__ __volatile__("lgdt %0" : : "m" (*(__T *)__data)); }
__FORCELOCAL void (__lidt_p)(void const *__data) { typedef struct { __UINT16_TYPE__ __x[5]; } __T; __asm__ __volatile__("lidt %0" : : "m" (*(__T *)__data)); }
__FORCELOCAL void (__sgdt)(void *__p) { typedef struct { __UINT16_TYPE__ __x[5]; } __T; __asm__ __volatile__("sgdt %0" : "=m" (*(__T *)__p)); }
__FORCELOCAL void (__sidt)(void *__p) { typedef struct { __UINT16_TYPE__ __x[5]; } __T; __asm__ __volatile__("sidt %0" : "=m" (*(__T *)__p)); }
#else /* __x86_64__ */
__FORCELOCAL void (__lgdt_p)(void const *__data) { typedef struct { __UINT16_TYPE__ __x[3]; } __T; __asm__ __volatile__("lgdt %0" : : "m" (*(__T *)__data)); }
__FORCELOCAL void (__lidt_p)(void const *__data) { typedef struct { __UINT16_TYPE__ __x[3]; } __T; __asm__ __volatile__("lidt %0" : : "m" (*(__T *)__data)); }
__FORCELOCAL void (__sgdt)(void *__p) { typedef struct { __UINT16_TYPE__ __x[3]; } __T; __asm__ __volatile__("sgdt %0" : "=m" (*(__T *)__p)); }
__FORCELOCAL void (__sidt)(void *__p) { typedef struct { __UINT16_TYPE__ __x[3]; } __T; __asm__ __volatile__("sidt %0" : "=m" (*(__T *)__p)); }
#endif /* !__x86_64__ */
__FORCELOCAL void (__lldt)(__UINT16_TYPE__ __x) { __asm__ __volatile__("lldt %0" : : "rm" (__x)); }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__sldt)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("sldt %0" : "=g" (__result)); return __result; }
__FORCELOCAL void (__ud2)(void) { __asm__ __volatile__("ud2"); }
__FORCELOCAL void (__nop)(void) { __asm__ __volatile__("nop"); }
__FORCELOCAL void (__pause)(void) { __asm__ __volatile__("pause"); }
__FORCELOCAL void (__lmsw)(__UINT16_TYPE__ __x) { __asm__ __volatile__("lmsw %0" : : "rm" (__x)); }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__smsw)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("smsw %0" : "=g" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT8_TYPE__ (__lahf)(void) { __UINT16_TYPE__ __result; __asm__ __volatile__("lahf" : "=a" (__result)); return (__UINT8_TYPE__)(__result >> 8); }
__FORCELOCAL void (__sahf)(__UINT8_TYPE__ __fl) { __asm__ __volatile__("sahf" : : "a" ((__UINT16_TYPE__)__fl << 8) : "cc"); }
__FORCELOCAL __ATTR_NORETURN void (__sysenter)(void) { __asm__ __volatile__("sysenter"); __builtin_unreachable(); }
__FORCELOCAL __ATTR_NORETURN void (__sysexit)(__UINT32_TYPE__ __uesp, __UINT32_TYPE__ __ueip) { __asm__ __volatile__("sysexit" : : "c" (__uesp), "d" (__ueip)); __builtin_unreachable(); }
__FORCELOCAL void (__movsb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; movsb" : "+D" (__dst), "+S" (__src), "+c" (__n_bytes), "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__,__n_bytes,__dst)) : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__,__n_bytes,__src))); }
__FORCELOCAL void (__movsw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; movsw" : "+D" (__dst), "+S" (__src), "+c" (__n_words), "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__,__n_words,__dst)) : "m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__,__n_words,__src))); }
__FORCELOCAL void (__movsl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; movsl" : "+D" (__dst), "+S" (__src), "+c" (__n_dwords), "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__,__n_dwords,__dst)) : "m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__,__n_dwords,__src))); }
__FORCELOCAL void (__stosb)(void *__restrict __dst, __UINT8_TYPE__ __byteval, __SIZE_TYPE__ __n_bytes) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; stosb" : "+D" (__dst), "+c" (__n_bytes), "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__,__n_bytes,__dst)) : "a" (__byteval)); }
__FORCELOCAL void (__stosw)(void *__restrict __dst, __UINT16_TYPE__ __wordval, __SIZE_TYPE__ __n_words) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; stosw" : "+D" (__dst), "+c" (__n_words), "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__,__n_words,__dst)) : "a" (__wordval)); }
__FORCELOCAL void (__stosl)(void *__restrict __dst, __UINT32_TYPE__ __dwordval, __SIZE_TYPE__ __n_dwords) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; stosl" : "+D" (__dst), "+c" (__n_dwords), "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__,__n_dwords,__dst)) : "a" (__dwordval)); }
#ifdef __x86_64__
__FORCELOCAL void (__movsq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; movsq" : "+D" (__dst), "+S" (__src), "+c" (__n_qwords), "=m" (__COMPILER_ASM_BUFFER(__UINT64_TYPE__,__n_qwords,__dst)) : "m" (__COMPILER_ASM_BUFFER(__UINT64_TYPE__,__n_qwords,__src))); }
__FORCELOCAL void (__stosq)(void *__restrict __dst, __UINT64_TYPE__ __dword, __SIZE_TYPE__ __n_qwords) { __asm__(__PRIVATE_PREFIX_REP_CLD "rep; stosq" : "+D" (__dst), "+c" (__n_qwords), "=m" (__COMPILER_ASM_BUFFER(__UINT64_TYPE__,__n_qwords,__dst)) : "a" (__dword)); }
#else /* __x86_64__ */
__FORCELOCAL void (__boundw)(__INT16_TYPE__ const __limits[2], __INT16_TYPE__ __index) { __asm__ __volatile__("boundw %0, %w1" : : "m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, 2, __limits)), "r" (__index)); }
__FORCELOCAL void (__boundl)(__INT32_TYPE__ const __limits[2], __INT32_TYPE__ __index) { __asm__ __volatile__("boundl %0, %k1" : : "m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, 2, __limits)), "r" (__index)); }
#endif /* !__x86_64__ */

/* Read/Write control registers. */
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rdcr0)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%cr0, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rdcr2)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%cr2, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rdcr3)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%cr3, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rdcr4)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%cr4, %0" : "=r" (__result)); return __result; }
__FORCELOCAL void (__wrcr0)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%cr0" : : "r" (__val)); }
__FORCELOCAL void (__wrcr2)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%cr2" : : "r" (__val)); }
__FORCELOCAL void (__wrcr3)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%cr3" : : "r" (__val)); }
__FORCELOCAL void (__wrcr4)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%cr4" : : "r" (__val)); }

/* Read/Write debug registers. */
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr0)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr0, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr1)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr1, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr2)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr2, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr3)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr3, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr6)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr6, %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__rddr7)(void) { __register __REGISTER_TYPE__ __result; __asm__ __volatile__("mov %%dr7, %0" : "=r" (__result)); return __result; }
__FORCELOCAL void (__wrdr0)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr0" : : "r" (__val)); }
__FORCELOCAL void (__wrdr1)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr1" : : "r" (__val)); }
__FORCELOCAL void (__wrdr2)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr2" : : "r" (__val)); }
__FORCELOCAL void (__wrdr3)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr3" : : "r" (__val)); }
__FORCELOCAL void (__wrdr6)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr6" : : "r" (__val)); }
__FORCELOCAL void (__wrdr7)(__REGISTER_TYPE__ __val) { __asm__ __volatile__("mov %0, %%dr7" : : "r" (__val)); }

/* Read/Write segment registers. */
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdes)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%es, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdcs)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%cs, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdss)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%ss, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdds)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%ds, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdfs)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%fs, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__rdgs)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("movw %%gs, %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT16_TYPE__ (__str)(void) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("str %w0" : "=rm" (__result)); return __result; }
__FORCELOCAL void (__wres)(__UINT16_TYPE__ __val) { __asm__ __volatile__("movw %w0, %%es" : : "rm" (__val) : "memory"); }
__FORCELOCAL void (__wrss)(__UINT16_TYPE__ __val) { __asm__ __volatile__("movw %w0, %%ss" : : "rm" (__val) : "memory"); }
__FORCELOCAL void (__wrds)(__UINT16_TYPE__ __val) { __asm__ __volatile__("movw %w0, %%ds" : : "rm" (__val) : "memory"); }
__FORCELOCAL void (__wrfs)(__UINT16_TYPE__ __val) { __asm__ __volatile__("movw %w0, %%fs" : : "rm" (__val) : "memory"); }
__FORCELOCAL void (__wrgs)(__UINT16_TYPE__ __val) { __asm__ __volatile__("movw %w0, %%gs" : : "rm" (__val) : "memory"); }
__FORCELOCAL void (__wrcs)(__UINT16_TYPE__ __val) {
	if (__builtin_constant_p(__val)) {
		__asm__ __volatile__("ljmp %0, $1f\n\t"
		                     "1:"
		                     :
		                     : "i" (__val)
		                     : "memory");
	} else {
#ifdef _x86_64__
		__asm__ __volatile__("pushq %%esp\n\t"
		                     "pushq %%ss\n\t"
		                     "addq $8, 0(%%esp)\n\t"
		                     "pushfq\n\t"
		                     "pushq %q0\n\t"
		                     "pushq $1f\n\t"
		                     "iretq\n\t"
		                     "1:"
		                     :
		                     : "r" ((__UINT64_TYPE__)__val)
		                     : "memory");
#else
		__asm__ __volatile__("pushfl\n\t"
		                     "pushl %k0\n\t"
		                     "pushl $1f\n\t"
		                     "iret\n\t"
		                     "1:"
		                     :
		                     : "r" ((__UINT32_TYPE__)__val)
		                     : "memory");
#endif
	}
}
__FORCELOCAL void (__ltr)(__UINT16_TYPE__ __val) { __asm__ __volatile__("ltr %w0" : : "rm" (__val) : "memory"); }


/* Segment read/write operators. */
#ifndef __x86_64__
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rddsb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%ds:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rdesb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%es:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rdssb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%ss:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rdcsb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%cs:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rddsw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%ds:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdesw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%es:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdssw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%ss:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdcsw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%cs:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rddsl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%ds:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdesl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%es:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdssl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%ss:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdcsl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%cs:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL void (__wrdsb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%ds:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wresb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%es:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wrssb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%ss:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wrcsb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%cs:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wrdsw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%ds:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wresw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%es:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrssw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%ss:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrcsw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%cs:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrdsl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%ds:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wresl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%es:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrssl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%ss:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrcsl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%cs:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
#endif /* !__x86_64__ */
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rdfsb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%fs:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT8_TYPE__ (__rdgsb)(__UINTPTR_TYPE__ __offset) { __register __UINT8_TYPE__ __result; __asm__("movb %%gs:%1, %b0" : "=q" (__result) : "m" (*(__UINT8_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdfsw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%fs:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdgsw)(__UINTPTR_TYPE__ __offset) { __register __UINT16_TYPE__ __result; __asm__("movw %%gs:%1, %w0" : "=r" (__result) : "m" (*(__UINT16_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdfsl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%fs:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdgsl)(__UINTPTR_TYPE__ __offset) { __register __UINT32_TYPE__ __result; __asm__("movl %%gs:%1, %k0" : "=r" (__result) : "m" (*(__UINT32_TYPE__ *)__offset)); return __result; }
__FORCELOCAL void (__wrfsb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%fs:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wrgsb)(__UINTPTR_TYPE__ __offset, __UINT8_TYPE__ __val) { __asm__("movb %b1, %%gs:%b0" : : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)); }
__FORCELOCAL void (__wrfsw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%fs:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrgsw)(__UINTPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { __asm__("movw %w1, %%gs:%w0" : : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrfsl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%fs:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrgsl)(__UINTPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { __asm__("movl %k1, %%gs:%k0" : : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)); }
#ifdef __x86_64__
__FORCELOCAL __ATTR_PURE __UINT64_TYPE__ (__rdfsq)(__UINTPTR_TYPE__ __offset) { __register __UINT64_TYPE__ __result; __asm__("movq %%fs:%1, %q0" : "=r" (__result) : "m" (*(__UINT64_TYPE__ *)__offset)); return __result; }
__FORCELOCAL __ATTR_PURE __UINT64_TYPE__ (__rdgsq)(__UINTPTR_TYPE__ __offset) { __register __UINT64_TYPE__ __result; __asm__("movq %%gs:%1, %q0" : "=r" (__result) : "m" (*(__UINT64_TYPE__ *)__offset)); return __result; }
__FORCELOCAL void (__wrfsq)(__UINTPTR_TYPE__ __offset, __UINT64_TYPE__ __val) { __asm__("movq %q1, %%fs:%0" : : "m" (*(__UINT64_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL void (__wrgsq)(__UINTPTR_TYPE__ __offset, __UINT64_TYPE__ __val) { __asm__("movq %q1, %%gs:%0" : : "m" (*(__UINT64_TYPE__ *)__offset), "r" (__val)); }
__FORCELOCAL __ATTR_PURE void *(__rdfsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdfsq(__offset); }
__FORCELOCAL __ATTR_PURE void *(__rdgsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdgsq(__offset); }
__FORCELOCAL void (__wrfsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrfsq(__offset,(__UINT64_TYPE__)__val); }
__FORCELOCAL void (__wrgsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrgsq(__offset,(__UINT64_TYPE__)__val); }
#else /* __x86_64__ */
__FORCELOCAL __ATTR_PURE void *(__rdfsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdfsl(__offset); }
__FORCELOCAL __ATTR_PURE void *(__rdgsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdgsl(__offset); }
__FORCELOCAL void (__wrfsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrfsl(__offset,(__UINT32_TYPE__)__val); }
__FORCELOCAL void (__wrgsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrgsl(__offset,(__UINT32_TYPE__)__val); }
__FORCELOCAL __ATTR_PURE void *(__rddsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rddsl(__offset); }
__FORCELOCAL __ATTR_PURE void *(__rdesptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdesl(__offset); }
__FORCELOCAL __ATTR_PURE void *(__rdssptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdssl(__offset); }
__FORCELOCAL __ATTR_PURE void *(__rdcsptr)(__UINTPTR_TYPE__ __offset) { return (void *)__rdcsl(__offset); }
__FORCELOCAL void (__wrdsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrdsl(__offset,(__UINT32_TYPE__)__val); }
__FORCELOCAL void (__wresptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wresl(__offset,(__UINT32_TYPE__)__val); }
__FORCELOCAL void (__wrssptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrssl(__offset,(__UINT32_TYPE__)__val); }
__FORCELOCAL void (__wrcsptr)(__UINTPTR_TYPE__ __offset, void *__val) { __wrcsl(__offset,(__UINT32_TYPE__)__val); }
#endif /* !__x86_64__ */

__FORCELOCAL __UINT8_TYPE__ (__inb)(__UINT16_TYPE__ __port) { __register __UINT8_TYPE__ __result; __asm__ __volatile__("inb %w1, %b0" : "=a" (__result) : "Nd" (__port)); return __result; }
__FORCELOCAL __UINT16_TYPE__ (__inw)(__UINT16_TYPE__ __port) { __register __UINT16_TYPE__ __result; __asm__ __volatile__("inw %w1, %w0" : "=a" (__result) : "Nd" (__port)); return __result; }
__FORCELOCAL __UINT32_TYPE__ (__inl)(__UINT16_TYPE__ __port) { __register __UINT32_TYPE__ __result; __asm__ __volatile__("inl %w1, %k0" : "=a" (__result) : "Nd" (__port)); return __result; }
__FORCELOCAL void (__outb)(__UINT16_TYPE__ __port, __UINT8_TYPE__ __val) { __asm__ __volatile__("outb %b0, %w1" : : "a" (__val), "Nd" (__port)); }
__FORCELOCAL void (__outw)(__UINT16_TYPE__ __port, __UINT16_TYPE__ __val) { __asm__ __volatile__("outw %w0, %w1" : : "a" (__val), "Nd" (__port)); }
__FORCELOCAL void (__outl)(__UINT16_TYPE__ __port, __UINT32_TYPE__ __val) { __asm__ __volatile__("outl %k0, %w1" : : "a" (__val), "Nd" (__port)); }
__FORCELOCAL void (__insb)(__UINT16_TYPE__ __port, void *__restrict __dst, __SIZE_TYPE__ __n_bytes)  { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; insb" : "=D" (__dst), "=c" (__n_bytes), "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__,__n_bytes,__dst)) : "d" (__port), "0" (__dst), "1" (__n_bytes)); }
__FORCELOCAL void (__insw)(__UINT16_TYPE__ __port, void *__restrict __dst, __SIZE_TYPE__ __n_words)  { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; insw" : "=D" (__dst), "=c" (__n_words), "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__,__n_words,__dst)) : "d" (__port), "0" (__dst), "1" (__n_words)); }
__FORCELOCAL void (__insl)(__UINT16_TYPE__ __port, void *__restrict __dst, __SIZE_TYPE__ __n_dwords) { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; insl" : "=D" (__dst), "=c" (__n_dwords), "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__,__n_dwords,__dst)) : "d" (__port), "0" (__dst), "1" (__n_dwords)); }
__FORCELOCAL void (__outsb)(__UINT16_TYPE__ __port, void const *__restrict __src, __SIZE_TYPE__ __n_bytes)  { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; outsb" : "=S" (__src), "=c" (__n_bytes) : "d" (__port), "0" (__src), "1" (__n_bytes) , "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__,__n_bytes,__src))); }
__FORCELOCAL void (__outsw)(__UINT16_TYPE__ __port, void const *__restrict __src, __SIZE_TYPE__ __n_words)  { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; outsw" : "=S" (__src), "=c" (__n_words) : "d" (__port), "0" (__src), "1" (__n_words) , "m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__,__n_words,__src))); }
__FORCELOCAL void (__outsl)(__UINT16_TYPE__ __port, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { __asm__ __volatile__(__PRIVATE_PREFIX_REP_CLD "rep; outsl" : "=S" (__src), "=c" (__n_dwords) : "d" (__port), "0" (__src), "1" (__n_dwords) , "m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__,__n_dwords,__src))); }


/* FS/GS-base registers. */
#ifdef __x86_64__
#ifdef __KERNEL__
#include <kernel/arch/fsgsbase.h>
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdfsbasel)(void) { __register __UINT64_TYPE__ __result; __asm__("safe_rdfsbase %0" : "=r" (__result)); return (__UINT32_TYPE__)__result; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdgsbasel)(void) { __register __UINT64_TYPE__ __result; __asm__("safe_rdgsbase %0" : "=r" (__result)); return (__UINT32_TYPE__)__result; }
__FORCELOCAL void (__wrfsbasel)(__UINT32_TYPE__ __val) { __asm__("safe_wrfsbase %0" : : "r" ((__UINT64_TYPE__)__val)); }
__FORCELOCAL void (__wrgsbasel)(__UINT32_TYPE__ __val) { __asm__("safe_wrgsbase %0" : : "r" ((__UINT64_TYPE__)__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdfsbaseq)(void) { __register __UINT64_TYPE__ __result; __asm__("safe_rdfsbase %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdgsbaseq)(void) { __register __UINT64_TYPE__ __result; __asm__("safe_rdgsbase %0" : "=r" (__result)); return __result; }
__FORCELOCAL void (__wrfsbaseq)(__UINT64_TYPE__ __val) { __asm__("safe_wrfsbase %0" : : "r" (__val)); }
__FORCELOCAL void (__wrgsbaseq)(__UINT64_TYPE__ __val) { __asm__("safe_wrgsbase %0" : : "r" (__val)); }
#else
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdfsbasel)(void) { __register __UINT32_TYPE__ __result; __asm__("rdfsbase %d0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdgsbasel)(void) { __register __UINT32_TYPE__ __result; __asm__("rdgsbase %d0" : "=r" (__result)); return __result; }
__FORCELOCAL void (__wrfsbasel)(__UINT32_TYPE__ __val) { __asm__("wrfsbase %d0" : : "r" (__val)); }
__FORCELOCAL void (__wrgsbasel)(__UINT32_TYPE__ __val) { __asm__("wrgsbase %d0" : : "r" (__val)); }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdfsbaseq)(void) { __register __UINT64_TYPE__ __result; __asm__("rdfsbase %0" : "=r" (__result)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdgsbaseq)(void) { __register __UINT64_TYPE__ __result; __asm__("rdgsbase %0" : "=r" (__result)); return __result; }
__FORCELOCAL void (__wrfsbaseq)(__UINT64_TYPE__ __val) { __asm__("wrfsbase %0" : : "r" (__val)); }
__FORCELOCAL void (__wrgsbaseq)(__UINT64_TYPE__ __val) { __asm__("wrgsbase %0" : : "r" (__val)); }
#endif
__FORCELOCAL void (__swapgs)(void) { __asm__ __volatile__("swapgs"); }

/* Get/Set the fs/gs base as a pointer */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED void *(__rdfsbase)(void);
__ATTR_WUNUSED void *(__rdgsbase)(void);
void (__wrfsbase)(void *__val);
void (__wrgsbase)(void *__val);
#else
#define __rdfsbase()     ((void *)__rdfsbaseq())
#define __rdgsbase()     ((void *)__rdgsbaseq())
#define __wrfsbase(val)    __wrfsbaseq((__UINT64_TYPE__)(void *)(val))
#define __wrgsbase(val)    __wrgsbaseq((__UINT64_TYPE__)(void *)(val))
#endif

#elif defined(__KOS__)

#define __PRIVATE_EMIT_BYTE_REGISTER_SELECT(slot,b_eax,b_ecx,b_edx,b_ebx,b_esp,b_ebp,b_esi,b_edi) \
	".ifc " slot ",%%eax\n\t.byte " b_eax "\n\t.else\n\t" \
	".ifc " slot ",%%ecx\n\t.byte " b_ecx "\n\t.else\n\t" \
	".ifc " slot ",%%edx\n\t.byte " b_edx "\n\t.else\n\t" \
	".ifc " slot ",%%ebx\n\t.byte " b_ebx "\n\t.else\n\t" \
	".ifc " slot ",%%esp\n\t.byte " b_esp "\n\t.else\n\t" \
	".ifc " slot ",%%ebp\n\t.byte " b_ebp "\n\t.else\n\t" \
	".ifc " slot ",%%esi\n\t.byte " b_esi "\n\t.else\n\t" \
	".ifc " slot ",%%edi\n\t.byte " b_edi "\n\t.else\n\t" \
	".error \"Invalid register " slot "\"\n\t" \
	".endif\n\t.endif\n\t.endif\n\t.endif\n\t.endif\n\t.endif\n\t.endif\n\t.endif\n\t"

/* The KOS kernel emulates the `(wr|rd)(fs|gs)base' instructions in 32-bit mode!
 * As a matter of fact, this is the preferred way for user-space to change them!
 * NOTE: The byte sequences below are be what the `(wr|rd)(fs|gs)base' instructions
 *       would assembly to if they were valid for 32-bit code. However since Intel
 *       states that these instructions are not available in protected mode (32-bit mode),
 *       let's just be safe and encode them manually, rather than relying on the assembler
 *       to already provide them as an extension.
 * s.a.: https://www.felixcloutier.com/x86/rdfsbase:rdgsbase */
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdfsbasel)(void) {
	__register __UINT32_TYPE__ __result;
	__asm__(".byte 0xf3,0x0f,0xae\n\t"
	        __PRIVATE_EMIT_BYTE_REGISTER_SELECT("%k0"
	        , "0xc0" /* 0b_11_000_000 */
	        , "0xc1" /* 0b_11_000_001 */
	        , "0xc2" /* 0b_11_000_010 */
	        , "0xc3" /* 0b_11_000_011 */
	        , "0xc4" /* 0b_11_000_100 */
	        , "0xc5" /* 0b_11_000_101 */
	        , "0xc6" /* 0b_11_000_110 */
	        , "0xc7" /* 0b_11_000_111 */
	        ) : "=r" (__result));
	return __result;
}
__FORCELOCAL __ATTR_WUNUSED __UINT32_TYPE__ (__rdgsbasel)(void) {
	__register __UINT32_TYPE__ __result;
	__asm__(".byte 0xf3,0x0f,0xae\n\t"
	        __PRIVATE_EMIT_BYTE_REGISTER_SELECT("%k0"
	        , "0xc8" /* 0b_11_001_000 */
	        , "0xc9" /* 0b_11_001_001 */
	        , "0xca" /* 0b_11_001_010 */
	        , "0xcb" /* 0b_11_001_011 */
	        , "0xcc" /* 0b_11_001_100 */
	        , "0xcd" /* 0b_11_001_101 */
	        , "0xce" /* 0b_11_001_110 */
	        , "0xcf" /* 0b_11_001_111 */
	        ) : "=r" (__result));
	return __result;
}

__FORCELOCAL void (__wrfsbasel)(__UINT32_TYPE__ __val) {
	__asm__(".byte 0xf3,0x0f,0xae\n\t"
	        __PRIVATE_EMIT_BYTE_REGISTER_SELECT("%k0"
	        , "0xd0" /* 0b_11_010_000 */
	        , "0xd1" /* 0b_11_010_001 */
	        , "0xd2" /* 0b_11_010_010 */
	        , "0xd3" /* 0b_11_010_011 */
	        , "0xd4" /* 0b_11_010_100 */
	        , "0xd5" /* 0b_11_010_101 */
	        , "0xd6" /* 0b_11_010_110 */
	        , "0xd7" /* 0b_11_010_111 */
	        ) : : "r" (__val));
}

__FORCELOCAL void (__wrgsbasel)(__UINT32_TYPE__ __val) {
	__asm__(".byte 0xf3,0x0f,0xae\n\t"
	        __PRIVATE_EMIT_BYTE_REGISTER_SELECT("%k0"
	        , "0xd8" /* 0b_11_011_000 */
	        , "0xd9" /* 0b_11_011_001 */
	        , "0xda" /* 0b_11_011_010 */
	        , "0xdb" /* 0b_11_011_011 */
	        , "0xdc" /* 0b_11_011_100 */
	        , "0xdd" /* 0b_11_011_101 */
	        , "0xde" /* 0b_11_011_110 */
	        , "0xdf" /* 0b_11_011_111 */
	        ) : : "r" (__val));
}
#undef __PRIVATE_EMIT_BYTE_REGISTER_SELECT

/* Get/Set the fs/gs base as a pointer */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED void *(__rdfsbase)(void);
__ATTR_WUNUSED void *(__rdgsbase)(void);
void (__wrfsbase)(void *__val);
void (__wrgsbase)(void *__val);
#else
#define __rdfsbase()     ((void *)__rdfsbasel())
#define __rdgsbase()     ((void *)__rdgsbasel())
#define __wrfsbase(val)    __wrfsbasel((__UINT32_TYPE__)(void *)(val))
#define __wrgsbase(val)    __wrgsbasel((__UINT32_TYPE__)(void *)(val))
#endif
#endif

/* MachineSpecificRegisters (MSRs) */
#ifdef __x86_64__
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdmsr)(__UINT32_TYPE__ __id) { union __ATTR_PACKED { __UINT32_TYPE__ __lohi[2]; __UINT64_TYPE__ __result; } __res; __asm__ __volatile__("rdmsr" : "=a" (__res.__lohi[0]), "=d" (__res.__lohi[1]) : "c" (__id)); return __res.__result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdpmc)(__UINT32_TYPE__ __id) { union __ATTR_PACKED { __UINT32_TYPE__ __lohi[2]; __UINT64_TYPE__ __result; } __res; __asm__ __volatile__("rdpmc" : "=a" (__res.__lohi[0]), "=d" (__res.__lohi[1]) : "c" (__id)); return __res.__result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdtsc)(void) { union __ATTR_PACKED { __UINT32_TYPE__ __lohi[2]; __UINT64_TYPE__ __result; } __res; __asm__ __volatile__("rdtsc" : "=a" (__res.__lohi[0]), "=d" (__res.__lohi[1])); return __res.__result; }
__FORCELOCAL void (__wrmsr)(__UINT32_TYPE__ __id, __UINT64_TYPE__ __val) { union __ATTR_PACKED { __UINT32_TYPE__ __lohi[2]; __UINT64_TYPE__ __val; } __arg; __arg.__val = __val; __asm__ __volatile__("wrmsr" : : "c" (__id), "a" (__arg.__lohi[0]), "d" (__arg.__lohi[1])); }
#else
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdmsr)(__UINT32_TYPE__ __id) { __UINT64_TYPE__ __result; __asm__ __volatile__("rdmsr" : "=A" (__result) : "c" (__id)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdpmc)(__UINT32_TYPE__ __id) { __UINT64_TYPE__ __result; __asm__ __volatile__("rdpmc" : "=A" (__result) : "c" (__id)); return __result; }
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__rdtsc)(void) { __UINT64_TYPE__ __result; __asm__ __volatile__("rdtsc" : "=A" (__result)); return __result; }
__FORCELOCAL void (__wrmsr)(__UINT32_TYPE__ __id, __UINT64_TYPE__ __val) { __asm__ __volatile__("wrmsr" : : "c" (__id), "A" (__val)); }
#endif

#undef __PRIVATE_PREFIX_REP_CLD
#elif defined(_MSC_VER)
__NAMESPACE_INT_BEGIN
/* TODO */
__NAMESPACE_INT_END
#endif

__SYSDECL_END

#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_H */
