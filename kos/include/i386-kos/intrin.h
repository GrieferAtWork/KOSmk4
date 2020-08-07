/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_INTRIN_H
#define _I386_KOS_INTRIN_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__byteswap.h>
#include <hybrid/__rotate.h>
#include <hybrid/host.h>

#include <asm/intrin-arith.h>
#include <asm/intrin-lock.h>
#include <asm/intrin-segarith.h>
#include <asm/intrin.h>


/* __MACHINE */
/* __MACHINE: void *_AddressOfReturnAddress(void) */
/* __MACHINE: unsigned char _BitScanForward(unsigned long *_Index, unsigned long mask) */
/* __MACHINE: unsigned char _BitScanReverse(unsigned long *_Index, unsigned long mask) */
#define _InterlockedAnd(value, mask)                                         __lock_andl(value, mask)
#define _InterlockedAnd16(value, mask)                                       __lock_andw(value, mask)
#define _InterlockedAnd8(value, mask)                                        __lock_andw(value, mask)
#define _InterlockedCompareExchange(destination, exchange, comparand)        __lock_cmpxchgl(destination, comparand, exchange)
#define _InterlockedCompareExchange16(destination, exchange, comparand)      __lock_cmpxchgw(destination, comparand, exchange)
#define _InterlockedCompareExchange64(destination, exchange, comparand)      __lock_cmpxchgq(destination, comparand, exchange)
#define _InterlockedCompareExchange8(destination, exchange, comparand)       __lock_cmpxchgb(destination, comparand, exchange)
#define _InterlockedCompareExchangePointer(destination, exchange, comparand) __lock_cmpxchgp(destination, comparand, exchange)
#define _InterlockedDecrement(addend)                                        __lock_dec_resultl(addend)
#define _InterlockedDecrement16(addend)                                      __lock_dec_resultw(addend)
#define _InterlockedExchange(target, value)                                  __lock_xchgl(target, value)
#define _InterlockedExchange16(target, value)                                __lock_xchgw(target, value)
#define _InterlockedExchange8(target, value)                                 __lock_xchgb(target, value)
#define _InterlockedExchangeAdd(addend, value)                               __lock_addl(addend, value)
#define _InterlockedExchangeAdd16(addend, value)                             __lock_addw(addend, value)
#define _InterlockedExchangeAdd8(addend, value)                              __lock_addb(addend, value)
#define _InterlockedExchangePointer(addend, value)                           __lock_addp(addend, value)
#define _InterlockedIncrement(addend)                                        __lock_inc_resultl(addend)
#define _InterlockedIncrement16(addend)                                      __lock_inc_resultw(addend)
#define _InterlockedOr(value, mask)                                          __lock_orl(value, mask)
#define _InterlockedOr16(value, mask)                                        __lock_orw(value, mask)
#define _InterlockedOr8(value, mask)                                         __lock_orb(value, mask)
#define _InterlockedXor(value, mask)                                         __lock_xorl(value, mask)
#define _InterlockedXor16(value, mask)                                       __lock_xorw(value, mask)
#define _InterlockedXor8(value, mask)                                        __lock_xorb(value, mask)
#define _ReadBarrier()                                                       __COMPILER_READ_BARRIER()
#define _ReadWriteBarrier()                                                  __COMPILER_BARRIER()
#define _WriteBarrier()                                                      __COMPILER_WRITE_BARRIER()
#if __has_builtin(__builtin_return_address)
#define _ReturnAddress() __builtin_return_address(0)
#endif /* __has_builtin(__builtin_return_address) */
/* __MACHINE: void __code_seg(const char *) */
#define __debugbreak() __int3()
#ifdef __COMPILER_HAVE_GCC_ASM
#if __has_builtin(__fastfail)
#define __fastfail(Code)  __x86_fastfail(Code)
__FORCELOCAL __ATTR_NORETURN void (__x86_fastfail)(unsigned int __code) {
	__asm__ __volatile__("int {$}0x29" : : "c" (__code) : "memory");
	__builtin_unreachable();
}
#else /* __has_builtin(__fastfail) */
#define __fastfail(Code)  __fastfail(Code)
__FORCELOCAL __ATTR_NORETURN void (__fastfail)(unsigned int __code) {
	__asm__ __volatile__("int {$}0x29" : : "c" (__code) : "memory");
	__builtin_unreachable();
}
#endif /* !__has_builtin(__fastfail) */
#endif /* __COMPILER_HAVE_GCC_ASM */
#define __nop() __nop()
/* __MACHINE: unsigned char _bittest(long const *, long) */
/* __MACHINE: unsigned char _bittestandcomplement(long *, long) */
/* __MACHINE: unsigned char _bittestandreset(long *, long) */
/* __MACHINE: unsigned char _bittestandset(long *, long) */
#define _byteswap_uint64(value) __hybrid_bswap64(value)
#define _byteswap_ulong(value)  __hybrid_bswap32(value)
#define _byteswap_ushort(value) __hybrid_bswap16(value)
#define _disable()              __cli()
#define _enable()               __sti()
/* __MACHINE: unsigned char _interlockedbittestandreset(long volatile *, long) */
/* __MACHINE: unsigned char _interlockedbittestandset(long volatile *, long) */
#define _lrotl(value, shift)  __hybrid_rol32(value, shift)
#define _rotl(value, shift)   __hybrid_rol32(value, shift)
#define _rotl16(value, shift) __hybrid_rol16(value, shift)
#define _rotl64(value, shift) __hybrid_rol64(value, shift)
#define _rotl8(value, shift)  __hybrid_rol8(value, shift)
#define _lrotr(value, shift)  __hybrid_rol32(value, shift)
#define _rotr(value, shift)   __hybrid_ror32(value, shift)
#define _rotr16(value, shift) __hybrid_ror16(value, shift)
#define _rotr64(value, shift) __hybrid_ror64(value, shift)
#define _rotr8(value, shift)  __hybrid_ror8(value, shift)
/* __MACHINE: int __cdecl _setjmp(jmp_buf) */




/* __MACHINEX86 / __MACHINEX64 */
#define __readcr0()       __rdcr0()
#define __readcr2()       __rdcr2()
#define __readcr3()       __rdcr3()
#define __readcr4()       __rdcr4()
#define __writecr0(value) __wrcr0(value)
#define __writecr3(value) __wrcr3(value)
#define __writecr4(value) __wrcr4(value)
#ifdef __x86_64__
#define __readcr8()       __rdcr8()
#define __writecr8(value) __wrcr8(value)
#endif /* __x86_64__ */
#define __readeflags()       __rdflags()
#define __writeeflags(value) __wrflags(value)
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__readdr)(unsigned int __N) {
	switch (__N) {
	case 0: return (__REGISTER_TYPE__)__rddr0();
	case 1: return (__REGISTER_TYPE__)__rddr1();
	case 2: return (__REGISTER_TYPE__)__rddr2();
	case 3: return (__REGISTER_TYPE__)__rddr3();
	case 6: return __rddr6();
	case 7: return __rddr7();
	default: __builtin_unreachable();
	}
}
__FORCELOCAL void (__writedr)(unsigned int __N, __REGISTER_TYPE__ __Val) {
	switch (__N) {
	case 0: __wrdr0((void *)__Val); break;
	case 1: __wrdr1((void *)__Val); break;
	case 2: __wrdr2((void *)__Val); break;
	case 3: __wrdr3((void *)__Val); break;
	case 6: __wrdr6(__Val); break;
	case 7: __wrdr7(__Val); break;
	default: __builtin_unreachable();
	}
}







/* __MACHINEX86 */
#if defined(__i386__) && !defined(__x86_64__)
#define __addfsbyte(Offset, value)  __addfsb(Offset, value)
#define __addfsdword(Offset, value) __addfsl(Offset, value)
#define __addfsword(Offset, value)  __addfsw(Offset, value)
#define __incfsbyte(Offset)         __incfsb(Offset)
#define __incfsdword(Offset)        __incfsl(Offset)
#define __incfsword(Offset)         __incfsw(Offset)
#define __readfsbyte(Offset)        __rdfsb(Offset)
#define __readfsdword(Offset)       __rdfsl(Offset)
#ifdef __x86_64__
#define __readfsqword(Offset) __rdfsq(Offset)
#else /* __x86_64__ */
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__readfsqword)(__ULONGPTR_TYPE__ __Offset) {
	union {
		__UINT64_TYPE__ __Val64;
		__UINT32_TYPE__ __Val32[2];
	} __Result;
	__Result.__Val32[0] = __rdfsl(__Offset + 0);
	__Result.__Val32[1] = __rdfsl(__Offset + 4);
	return __Result.__Val64;
}
#endif /* !__x86_64__ */
#define __readfsword(Offset)          __rdfsw(Offset)
#define __writefsbyte(Offset, value)  __wrfsb(Offset, value)
#define __writefsdword(Offset, value) __wrfsl(Offset, value)
#ifdef __x86_64__
#define __writefsqword(Offset, value) __wrfsq(Offset, value)
#else /* __x86_64__ */
__FORCELOCAL void (__writefsqword)(__ULONGPTR_TYPE__ __Offset, __UINT64_TYPE__ __value) {
	union {
		__UINT64_TYPE__ __Val64;
		__UINT32_TYPE__ __Val32[2];
	} __Data;
	__Data.__Val64 = __value;
	__wrfsl(__Offset + 0, __Data.__Val32[0]);
	__wrfsl(__Offset + 4, __Data.__Val32[1]);
}
#endif /* !__x86_64__ */
#define __writefsword(Offset, value) __wrfsw(Offset, value)
/* __MACHINEX86: void _m_empty(void) */
/* __MACHINEX86: void _m_femms(void) */
/* __MACHINEX86: __m64 _m_from_float(float) */
/* __MACHINEX86: __m64 _m_from_int(int) */
/* __MACHINEX86: void _m_maskmovq(__m64, __m64, char *) */
/* __MACHINEX86: __m64 _m_packssdw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_packsswb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_packuswb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddsb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddusw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pand(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pandn(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtw(__m64, __m64) */
/* __MACHINEX86: int _m_pextrw(__m64, int) */
/* __MACHINEX86: __m64 _m_pf2id(__m64) */
/* __MACHINEX86: __m64 _m_pf2iw(__m64) */
/* __MACHINEX86: __m64 _m_pfacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfadd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpeq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpge(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpgt(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmax(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmin(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmul(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfnacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfpnacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrcp(__m64) */
/* __MACHINEX86: __m64 _m_pfrcpit1(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrcpit2(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrsqit1(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrsqrt(__m64) */
/* __MACHINEX86: __m64 _m_pfsub(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfsubr(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pi2fd(__m64) */
/* __MACHINEX86: __m64 _m_pi2fw(__m64) */
/* __MACHINEX86: __m64 _m_pinsrw(__m64, int, int) */
/* __MACHINEX86: __m64 _m_pmaddwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmaxsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmaxub(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pminsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pminub(__m64, __m64) */
/* __MACHINEX86: int _m_pmovmskb(__m64) */
/* __MACHINEX86: __m64 _m_pmulhrw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmulhuw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmulhw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmullw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_por(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psadbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pshufw(__m64, int) */
/* __MACHINEX86: __m64 _m_pslld(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pslldi(__m64, int) */
/* __MACHINEX86: __m64 _m_psllq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psllqi(__m64, int) */
/* __MACHINEX86: __m64 _m_psllw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psllwi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrad(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psradi(__m64, int) */
/* __MACHINEX86: __m64 _m_psraw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrawi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrld(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrldi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrlq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrlqi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrlw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrlwi(__m64, int) */
/* __MACHINEX86: __m64 _m_psubb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubsb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubusw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pswapd(__m64) */
/* __MACHINEX86: __m64 _m_punpckhbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckhdq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckhwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpcklbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckldq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpcklwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pxor(__m64, __m64) */
/* __MACHINEX86: float _m_to_float(__m64) */
/* __MACHINEX86: int _m_to_int(__m64) */
/* __MACHINEX86: __m64 _mm_add_si64(__m64, __m64) */
/* __MACHINEX86: __m128 _mm_cvt_pi2ps(__m128, __m64) */
/* __MACHINEX86: __m64 _mm_cvt_ps2pi(__m128) */
/* __MACHINEX86: __m64 _mm_cvtpd_pi32(__m128d) */
/* __MACHINEX86: __m128d _mm_cvtpi32_pd(__m64) */
/* __MACHINEX86: __m64 _mm_cvtt_ps2pi(__m128) */
/* __MACHINEX86: __m64 _mm_cvttpd_pi32(__m128d) */
/* __MACHINEX86: __m64 _mm_movepi64_pi64(__m128i) */
/* __MACHINEX86: __m128i _mm_movpi64_epi64(__m64) */
/* __MACHINEX86: __m64 _mm_mul_su32(__m64, __m64) */
/* __MACHINEX86: __m128i _mm_set1_epi64(__m64) */
/* __MACHINEX86: __m64 _mm_set1_pi16(short) */
/* __MACHINEX86: __m64 _mm_set1_pi32(int) */
/* __MACHINEX86: __m64 _mm_set1_pi8(char) */
/* __MACHINEX86: __m128i _mm_set_epi64(__m64, __m64) */
/* __MACHINEX86: __m64 _mm_set_pi16(short, short, short, short) */
/* __MACHINEX86: __m64 _mm_set_pi32(int, int) */
/* __MACHINEX86: __m64 _mm_set_pi8(char, char, char, char, char, char, char, char) */
/* __MACHINEX86: __m128i _mm_setr_epi64(__m64, __m64) */
/* __MACHINEX86: __m64 _mm_setr_pi16(short, short, short, short) */
/* __MACHINEX86: __m64 _mm_setr_pi32(int, int) */
/* __MACHINEX86: __m64 _mm_setr_pi8(char, char, char, char, char, char, char, char) */
/* __MACHINEX86: __m64 _mm_setzero_si64(void) */
/* __MACHINEX86: void _mm_stream_pi(__m64 *, __m64) */
/* __MACHINEX86: __m64 _mm_sub_si64(__m64, __m64) */
#endif /* __i386__ && !__x86_64__ */




/* __MACHINEX64 */
#ifdef __x86_64__
#define __addgsbyte(Offset, value)    __addgsb(Offset, value)
#define __addgsdword(Offset, value)   __addgsl(Offset, value)
#define __addgsword(Offset, value)    __addgsw(Offset, value)
#define __addgsqword(Offset, value)   __addgsq(Offset, value)
#define __incgsbyte(Offset)           __incgsb(Offset)
#define __incgsdword(Offset)          __incgsl(Offset)
#define __incgsword(Offset)           __incgsw(Offset)
#define __incgsqword(Offset)          __incgsq(Offset)
#define __readgsbyte(Offset)          __rdgsb(Offset)
#define __readgsdword(Offset)         __rdgsl(Offset)
#define __readgsqword(Offset)         __rdgsq(Offset)
#define __readgsword(Offset)          __rdgsw(Offset)
#define __writegsbyte(Offset, value)  __wrgsb(Offset, value)
#define __writegsdword(Offset, value) __wrgsl(Offset, value)
#define __writegsqword(Offset, value) __wrgsq(Offset, value)
#define __writegsword(Offset, value)  __wrgsw(Offset, value)
/* __MACHINEX64: unsigned char _BitScanForward64(unsigned long *_Index, unsigned __int64 mask) */
/* __MACHINEX64: unsigned char _BitScanReverse64(unsigned long *_Index, unsigned __int64 mask) */
/* __MACHINEX64: short _InterlockedAnd16_np(short volatile *value, short mask) */
/* __MACHINEX64: __int64 _InterlockedAnd64_np(__int64 volatile *value, __int64 mask) */
/* __MACHINEX64: char _InterlockedAnd8_np(char volatile *value, char mask) */
/* __MACHINEX64: long _InterlockedAnd_np(long volatile *value, long mask) */
/* __MACHINEX64: unsigned char _InterlockedCompareExchange128(__int64 volatile *destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 *_ComparandResult) */
/* __MACHINEX64: unsigned char _InterlockedCompareExchange128_np(__int64 volatile *destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 *_ComparandResult) */
/* __MACHINEX64: __int64 _InterlockedCompareExchange64_np(__int64 volatile *destination, __int64 exchange, __int64 comparand) */
/* __MACHINEX64: void *_InterlockedCompareExchangePointer_np(void *volatile *destination, void *exchange, void *comparand) */
/* __MACHINEX64: long _InterlockedCompareExchange_np(long volatile *destination, long exchange, long comparand) */
/* __MACHINEX64: short _InterlockedOr16_np(short volatile *value, short mask) */
/* __MACHINEX64: __int64 _InterlockedOr64_np(__int64 volatile *value, __int64 mask) */
/* __MACHINEX64: char _InterlockedOr8_np(char volatile *value, char mask) */
/* __MACHINEX64: long _InterlockedOr_np(long volatile *value, long mask) */
/* __MACHINEX64: short _InterlockedXor16_np(short volatile *value, short mask) */
/* __MACHINEX64: __int64 _InterlockedXor64_np(__int64 volatile *value, __int64 mask) */
/* __MACHINEX64: char _InterlockedXor8_np(char volatile *value, char mask) */
/* __MACHINEX64: long _InterlockedXor_np(long volatile *value, long mask) */
/* __MACHINEX64: void __faststorefence(void) */
#define __lzcnt64(value)                    __lzcntq(value)
#define __movsq(Dest, Source, NumQuadWords) __movsq(Dest, Source, NumQuadWords)
/* __MACHINEX64: __int64 __mulh(__int64, __int64) */
#define __popcnt64(value) __popcntq(value)
/* __MACHINEX64: unsigned __int64 __shiftleft128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _shift) */
/* __MACHINEX64: unsigned __int64 __shiftright128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _shift) */
#define __stosq(Dest, QuadWord, NumQuadWords) __stosq(Dest, QuadWord, NumQuadWords)
/* __MACHINEX64: unsigned __int64 __umulh(unsigned __int64, unsigned __int64) */
/* __MACHINEX64: unsigned char __vmx_on(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmclear(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmlaunch(void) */
/* __MACHINEX64: unsigned char __vmx_vmptrld(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmread(size_t, size_t *) */
/* __MACHINEX64: unsigned char __vmx_vmresume(void) */
/* __MACHINEX64: unsigned char __vmx_vmwrite(size_t, size_t) */
/* __MACHINEX64: unsigned char _bittest64(__int64 const *, __int64) */
/* __MACHINEX64: unsigned char _bittestandcomplement64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _bittestandreset64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _bittestandset64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _interlockedbittestandreset64(__int64 volatile *, __int64) */
/* __MACHINEX64: unsigned char _interlockedbittestandset64(__int64 volatile *, __int64) */
/* __MACHINEX64: unsigned __int64 _mm_crc32_u64(unsigned __int64, unsigned __int64) */
/* __MACHINEX64: __int64 _mm_cvtsd_si64(__m128d) */
/* __MACHINEX64: __int64 _mm_cvtsd_si64x(__m128d) */
/* __MACHINEX64: __int64 _mm_cvtsi128_si64(__m128i) */
/* __MACHINEX64: __int64 _mm_cvtsi128_si64x(__m128i) */
/* __MACHINEX64: __m128d _mm_cvtsi64_sd(__m128d, __int64) */
/* __MACHINEX64: __m128i _mm_cvtsi64_si128(__int64) */
/* __MACHINEX64: __m128 _mm_cvtsi64_ss(__m128, __int64) */
/* __MACHINEX64: __m128d _mm_cvtsi64x_sd(__m128d, __int64) */
/* __MACHINEX64: __m128i _mm_cvtsi64x_si128(__int64) */
/* __MACHINEX64: __m128 _mm_cvtsi64x_ss(__m128, __int64) */
/* __MACHINEX64: __int64 _mm_cvtss_si64(__m128) */
/* __MACHINEX64: __int64 _mm_cvtss_si64x(__m128) */
/* __MACHINEX64: __int64 _mm_cvttsd_si64(__m128d) */
/* __MACHINEX64: __int64 _mm_cvttsd_si64x(__m128d) */
/* __MACHINEX64: __int64 _mm_cvttss_si64(__m128) */
/* __MACHINEX64: __int64 _mm_cvttss_si64x(__m128) */
/* __MACHINEX64: __int64 _mm_extract_epi64(__m128i, int) */
/* __MACHINEX64: __m128i _mm_insert_epi64(__m128i, __int64, int) */
/* __MACHINEX64: __int64 _mm_popcnt_u64(unsigned __int64) */
/* __MACHINEX64: __m128i _mm_set1_epi64x(__int64) */
/* __MACHINEX64: __m128i _mm_set_epi64x(__int64, __int64) */
/* __MACHINEX64: void _mm_stream_si64x(__int64 *, __int64) */
/* __MACHINEX64: __int64 _mul128(__int64 _Multiplier, __int64 _Multiplicand, __int64 *_HighProduct) */
/* __MACHINEX64: unsigned __int64 _umul128(unsigned __int64 _Multiplier, unsigned __int64 _Multiplicand, unsigned __int64 *_HighProduct) */
/* __MACHINEX64: unsigned char __cdecl _addcarry_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *) */
/* __MACHINEX64: unsigned char __cdecl _subborrow_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *) */
#define _InterlockedAnd64(value, mask)           __lock_andq(value, mask)
#define _InterlockedDecrement64(addend)          __lock_dec_resultq(addend)
#define _InterlockedExchange64(target, value)    __lock_xchgq(target, value)
#define _InterlockedExchangeAdd64(addend, value) __lock_addq(addend, value)
#define _InterlockedIncrement64(addend)          __lock_inc_resultq(addend)
#define _InterlockedOr64(value, mask)            __lock_orq(value, mask)
#define _InterlockedXor64(value, mask)           __lock_xorq(value, mask)
/* __MACHINEX64: int __cdecl _setjmpex(jmp_buf) */
#endif /* __x86_64__ */




/* __MACHINEX86_X64 */
/* __MACHINEX86_X64: void __cpuid(int[4], int) */
/* __MACHINEX86_X64: void __cpuidex(int[4], int, int) */
/* __MACHINEX86_X64: __int64 __emul(int, int) */
/* __MACHINEX86_X64: unsigned __int64 __emulu(unsigned int, unsigned int) */
/* __MACHINEX86_X64: unsigned int __getcallerseflags(void) */
#define __halt()                                    __hlt()
#define __inbyte(Port)                              __inb(Port)
#define __inbytestring(Port, Dest, NumBytes)        __insb(Port, Dest, NumBytes)
#define __indword(Port)                             __inl(Port)
#define __indwordstring(Port, Dest, NumDoubleWords) __insl(Port, Dest, NumDoubleWords)
#define __int2c()                                   __int(0x2c)
#define __invlpg()                                  __invlpg()
#define __inword(Port)                              __inw(Port)
#define __inwordstring(Port, Dest, NumWords)        __insw(Port, Dest, NumWords)
#define __lidt(Data)                                __lidt_p(Data)
/* __MACHINEX86_X64: unsigned __int64 __ll_lshift(unsigned __int64, int) */
/* __MACHINEX86_X64: __int64 __ll_rshift(__int64, int) */
/* __MACHINEX86_X64: unsigned int __lzcnt(unsigned int) */
/* __MACHINEX86_X64: unsigned short __lzcnt16(unsigned short) */
#define __movsb(Dest, Source, NumBytes)       __movsb(Dest, Source, NumBytes)
#define __movsd(Dest, Source, NumDoubleWords) __movsl(Dest, Source, NumDoubleWords)
#define __movsw(Dest, Source, NumWords)       __movsw(Dest, Source, NumWords)
/* __MACHINEX86_X64: void __nvreg_restore_fence(void) */
/* __MACHINEX86_X64: void __nvreg_save_fence(void) */
#define __outbyte(Port, Byte)                        __outb(Port, Byte)
#define __outbytestring(Port, Data, NumBytes)        __outsb(Port, Data, NumBytes)
#define __outdword(Port, DoubleWord)                 __outl(Port, DoubleWord)
#define __outdwordstring(Port, Data, NumDoubleWords) __outsl(Port, Data, NumDoubleWords)
#define __outword(Port, Word)                        __outw(Port, Word)
#define __outwordstring(Port, Data, NumWords)        __outsw(Port, Data, NumWords)
#define __popcnt(value)                              __popcntl(value)
#define __popcnt16(value)                            __popcntw(value)
#define __rdtsc()                                    __rdtsc()
/* __MACHINEX86_X64: unsigned __int64 __rdtscp(unsigned int *) */
#define __readmsr(Id) __rdmsr(Id)
#define __readpmc(Id) __rdpmc(Id)
/* __MACHINEX86_X64: unsigned long __segmentlimit(unsigned long) */
#define __sidt(P)                                 __sidt(P)
#define __stosb(Dest, Byte, NumBytes)             __stosb(Dest, Byte, NumBytes)
#define __stosd(Dest, DoubleWord, NumDoubleWords) __stosl(Dest, DoubleWord, NumDoubleWords)
#define __stosw(Dest, Word, NumWords)             __stosw(Dest, Word, NumWords)
/* __MACHINEX86_X64: void __svm_clgi(void) */
/* __MACHINEX86_X64: void __svm_invlpga(void *, int) */
/* __MACHINEX86_X64: void __svm_skinit(int) */
/* __MACHINEX86_X64: void __svm_stgi(void) */
/* __MACHINEX86_X64: void __svm_vmload(size_t) */
/* __MACHINEX86_X64: void __svm_vmrun(size_t) */
/* __MACHINEX86_X64: void __svm_vmsave(size_t) */
#define __ud2() __ud2()
/* __MACHINEX86_X64: unsigned __int64 __ull_rshift(unsigned __int64, int) */
/* __MACHINEX86_X64: void __vmx_off(void) */
/* __MACHINEX86_X64: void __vmx_vmptrst(unsigned __int64 *) */
/* __MACHINEX86_X64: void __wbinvd(void) */
/* __MACHINEX86_X64: void __writemsr(unsigned long, unsigned __int64) */
/* __MACHINEX86_X64: void _m_prefetch(void *) */
/* __MACHINEX86_X64: void _m_prefetchw(volatile const void *) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi8(__m128i) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi16(__m64) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi32(__m64) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi8(__m64) */
/* __MACHINEX86_X64: __m128i _mm_add_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_add_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_add_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_add_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_add_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_adds_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_addsub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_addsub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_alignr_epi8(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m64 _mm_alignr_pi8(__m64, __m64, int) */
/* __MACHINEX86_X64: __m128d _mm_and_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_and_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_and_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_andnot_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_andnot_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_andnot_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_avg_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_avg_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_blend_epi16(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_blend_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_blend_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128i _mm_blendv_epi8(__m128i, __m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_blendv_pd(__m128d, __m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_blendv_ps(__m128, __m128, __m128) */
/* __MACHINEX86_X64: void _mm_clflush(void const *) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmpeq_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpeq_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpeq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpeq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_cmpestra(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrc(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestri(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_cmpestrm(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestro(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrs(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrz(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: __m128d _mm_cmpge_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpge_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpge_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpge_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmpgt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpgt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpgt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpgt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_cmpistra(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrc(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistri(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_cmpistrm(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistro(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrs(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrz(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_cmple_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmple_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmple_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmple_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmplt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmplt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmplt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmplt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpneq_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpneq_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpneq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpneq_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnge_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnge_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnge_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnge_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpngt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpngt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpngt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpngt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnle_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnle_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnle_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnle_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnlt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnlt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnlt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnlt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpord_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpord_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpord_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpord_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpunord_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpunord_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpunord_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpunord_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comieq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comieq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comige_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comige_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comigt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comigt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comile_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comile_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comilt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comilt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comineq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comineq_ss(__m128, __m128) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u16(unsigned int, unsigned short) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u32(unsigned int, unsigned int) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u8(unsigned int, unsigned char) */
/* __MACHINEX86_X64: __m128 _mm_cvt_si2ss(__m128, int) */
/* __MACHINEX86_X64: int _mm_cvt_ss2si(__m128) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi16_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi16_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi32_epi64(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_cvtepi32_pd(__m128i) */
/* __MACHINEX86_X64: __m128 _mm_cvtepi32_ps(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu16_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu16_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu32_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtpd_epi32(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_cvtpd_ps(__m128d) */
/* __MACHINEX86_X64: __m128i _mm_cvtps_epi32(__m128) */
/* __MACHINEX86_X64: __m128d _mm_cvtps_pd(__m128) */
/* __MACHINEX86_X64: int _mm_cvtsd_si32(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_cvtsd_ss(__m128, __m128d) */
/* __MACHINEX86_X64: int _mm_cvtsi128_si32(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_cvtsi32_sd(__m128d, int) */
/* __MACHINEX86_X64: __m128i _mm_cvtsi32_si128(int) */
/* __MACHINEX86_X64: __m128d _mm_cvtss_sd(__m128d, __m128) */
/* __MACHINEX86_X64: int _mm_cvtt_ss2si(__m128) */
/* __MACHINEX86_X64: __m128i _mm_cvttpd_epi32(__m128d) */
/* __MACHINEX86_X64: __m128i _mm_cvttps_epi32(__m128) */
/* __MACHINEX86_X64: int _mm_cvttsd_si32(__m128d) */
/* __MACHINEX86_X64: __m128d _mm_div_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_div_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_div_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_div_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_dp_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_dp_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: int _mm_extract_epi16(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_epi32(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_epi8(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_ps(__m128, int) */
/* __MACHINEX86_X64: __m128i _mm_extract_si64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_extracti_si64(__m128i, int, int) */
/* __MACHINEX86_X64: unsigned int _mm_getcsr(void) */
/* __MACHINEX86_X64: __m128i _mm_hadd_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_hadd_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_hadd_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m64 _mm_hadd_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_hadd_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_hadd_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_hadds_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_hadds_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_hsub_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_hsub_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_hsub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m64 _mm_hsub_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_hsub_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_hsub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_hsubs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_hsubs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi16(__m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi32(__m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi8(__m128i, int, int) */
/* __MACHINEX86_X64: __m128 _mm_insert_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_si64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_inserti_si64(__m128i, __m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_lddqu_si128(__m128i const *) */
/* __MACHINEX86_X64: void _mm_lfence(void) */
/* __MACHINEX86_X64: __m128d _mm_load1_pd(double const *) */
/* __MACHINEX86_X64: __m128d _mm_load_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ps(float const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ps1(float const *) */
/* __MACHINEX86_X64: __m128d _mm_load_sd(double const *) */
/* __MACHINEX86_X64: __m128i _mm_load_si128(__m128i const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ss(float const *) */
/* __MACHINEX86_X64: __m128d _mm_loaddup_pd(double const *) */
/* __MACHINEX86_X64: __m128d _mm_loadh_pd(__m128d, double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadh_pi(__m128, __m64 const *) */
/* __MACHINEX86_X64: __m128i _mm_loadl_epi64(__m128i const *) */
/* __MACHINEX86_X64: __m128d _mm_loadl_pd(__m128d, double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadl_pi(__m128, __m64 const *) */
/* __MACHINEX86_X64: __m128d _mm_loadr_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadr_ps(float const *) */
/* __MACHINEX86_X64: __m128d _mm_loadu_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadu_ps(float const *) */
/* __MACHINEX86_X64: __m128i _mm_loadu_si128(__m128i const *) */
/* __MACHINEX86_X64: __m128i _mm_madd_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_maddubs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_maddubs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: void _mm_maskmoveu_si128(__m128i, __m128i, char *) */
/* __MACHINEX86_X64: __m128i _mm_max_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_max_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_max_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_max_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_max_ss(__m128, __m128) */
/* __MACHINEX86_X64: void _mm_mfence(void) */
/* __MACHINEX86_X64: __m128i _mm_min_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_min_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_min_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_min_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_min_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_minpos_epu16(__m128i) */
/* __MACHINEX86_X64: void _mm_monitor(void const *, unsigned int, unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_move_epi64(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_move_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_move_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_movedup_pd(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_movehdup_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_movehl_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128 _mm_moveldup_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_movelh_ps(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_movemask_epi8(__m128i) */
/* __MACHINEX86_X64: int _mm_movemask_pd(__m128d) */
/* __MACHINEX86_X64: int _mm_movemask_ps(__m128) */
/* __MACHINEX86_X64: __m128i _mm_mpsadbw_epu8(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_mul_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mul_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_mul_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_mul_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_mul_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_mul_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_mulhi_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mulhi_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mulhrs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_mulhrs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_mullo_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mullo_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: void _mm_mwait(unsigned int, unsigned int) */
/* __MACHINEX86_X64: __m128d _mm_or_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_or_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_or_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packs_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packus_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packus_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: void _mm_pause(void) */
/* __MACHINEX86_X64: int _mm_popcnt_u32(unsigned int) */
/* __MACHINEX86_X64: void _mm_prefetch(char const *, int) */
/* __MACHINEX86_X64: __m128 _mm_rcp_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_rcp_ss(__m128) */
/* __MACHINEX86_X64: __m128d _mm_round_pd(__m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_round_ps(__m128, int) */
/* __MACHINEX86_X64: __m128d _mm_round_sd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_round_ss(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128 _mm_rsqrt_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_rsqrt_ss(__m128) */
/* __MACHINEX86_X64: __m128i _mm_sad_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi16(short) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi32(int) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi8(char) */
/* __MACHINEX86_X64: __m128d _mm_set1_pd(double) */
/* __MACHINEX86_X64: __m128i _mm_set_epi16(short, short, short, short, short, short, short, short) */
/* __MACHINEX86_X64: __m128i _mm_set_epi32(int, int, int, int) */
/* __MACHINEX86_X64: __m128i _mm_set_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char) */
/* __MACHINEX86_X64: __m128d _mm_set_pd(double, double) */
/* __MACHINEX86_X64: __m128 _mm_set_ps(float, float, float, float) */
/* __MACHINEX86_X64: __m128 _mm_set_ps1(float) */
/* __MACHINEX86_X64: __m128d _mm_set_sd(double) */
/* __MACHINEX86_X64: __m128 _mm_set_ss(float) */
/* __MACHINEX86_X64: void _mm_setcsr(unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_setl_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi16(short, short, short, short, short, short, short, short) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi32(int, int, int, int) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char) */
/* __MACHINEX86_X64: __m128d _mm_setr_pd(double, double) */
/* __MACHINEX86_X64: __m128 _mm_setr_ps(float, float, float, float) */
/* __MACHINEX86_X64: __m128d _mm_setzero_pd(void) */
/* __MACHINEX86_X64: __m128 _mm_setzero_ps(void) */
/* __MACHINEX86_X64: __m128i _mm_setzero_si128(void) */
/* __MACHINEX86_X64: void _mm_sfence(void) */
/* __MACHINEX86_X64: __m128i _mm_shuffle_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_shuffle_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_shuffle_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m64 _mm_shuffle_pi8(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_shuffle_ps(__m128, __m128, unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_shufflehi_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_shufflelo_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi8(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi64(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_si128(__m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_sqrt_pd(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_sqrt_ps(__m128) */
/* __MACHINEX86_X64: __m128d _mm_sqrt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sqrt_ss(__m128) */
/* __MACHINEX86_X64: __m128i _mm_sra_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sra_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srai_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srai_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi64(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_si128(__m128i, int) */
/* __MACHINEX86_X64: void _mm_store1_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_store_ps1(float *, __m128) */
/* __MACHINEX86_X64: void _mm_store_sd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_store_ss(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeh_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storeh_pi(__m64 *, __m128) */
/* __MACHINEX86_X64: void _mm_storel_epi64(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_storel_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storel_pi(__m64 *, __m128) */
/* __MACHINEX86_X64: void _mm_storer_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storer_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeu_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storeu_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeu_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_stream_load_si128(__m128i *) */
/* __MACHINEX86_X64: void _mm_stream_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_stream_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_stream_sd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_stream_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_stream_si32(int *, int) */
/* __MACHINEX86_X64: void _mm_stream_ss(float *, __m128) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_sub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_sub_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sub_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_subs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testc_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testnzc_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testz_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_ucomieq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomieq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomige_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomige_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomigt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomigt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomile_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomile_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomilt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomilt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomineq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomineq_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_unpackhi_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_unpackhi_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_unpacklo_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_unpacklo_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_xor_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_xor_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_xor_si128(__m128i, __m128i) */
#define _rsm()      __rsm()
#define _lgdt(Data) __lgdt_p(Data)
#define _sgdt(P)    __sgdt(P)
#define _clac()     __clac()
#define _stac()     __stac()
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u8(unsigned char, unsigned char, unsigned char, unsigned char *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u8(unsigned char, unsigned char, unsigned char, unsigned char *) */
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u16(unsigned char, unsigned short, unsigned short, unsigned short *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u16(unsigned char, unsigned short, unsigned short, unsigned short *) */
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u32(unsigned char, unsigned int, unsigned int, unsigned int *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u32(unsigned char, unsigned int, unsigned int, unsigned int *) */


#ifdef __USE_DOS
#include <crtdefs.h>
#include <setjmp.h>
#include <stddef.h>
#endif /* __USE_DOS */

//TODO:#if !defined (_M_CEE_PURE)
//TODO:
//TODO:#if defined (_M_IX86) || defined (_M_X64)
//TODO:#include <immintrin.h>
//TODO:#include <ammintrin.h>
//TODO:#endif  /* defined (_M_IX86) || defined (_M_X64) */
//TODO:
//TODO:#if defined (_M_IX86)
//TODO:#include <mm3dnow.h>
//TODO:#endif  /* defined (_M_IX86) */
//TODO:
//TODO:#if defined (_M_ARM)
//TODO:#include <armintr.h>
//TODO:#endif  /* defined (_M_ARM) */
//TODO:
//TODO:#endif  /* !defined (_M_CEE_PURE) */


#endif /* !_I386_KOS_INTRIN_H */
