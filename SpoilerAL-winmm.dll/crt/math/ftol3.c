#include <stdint.h>
#include <float.h>

static const double   Int32ToUInt32[2] = { 0, (UINT64_C(1) << 32)/*0x41F0000000000000*/ };
#define DP2to32 (Int32ToUInt32 + 8)
static const uint64_t MantissaMask     = 0x000FFFFFFFFFFFFF;
static const uint64_t IntegerBit       = 0x0010000000000000;
static const uint64_t SignBit64        = 0x8000000000000000;
static const double   MinFP64          = DBL_MIN;                                   // 0x0010000000000000
static const double   MinInt64         = (double)INT64_MIN;                         // 0xC3E0000000000000
static const double   MaxInt64         = (double)INT64_MAX;                         // 0x43E0000000000000
static const double   MaxUInt64        = (double)UINT64_MAX;                        // 0x43F0000000000000
static const double   MaxFP32          = FLT_MAX + (double)FLT_MAX / 0x01FFFFFE;    // 0x47EFFFFFF0000000 ... 0x1.FFFFFFp+127 (C++17)
static const double   MinFP32          = FLT_MIN - (double)FLT_MIN / 0x02000000;    // 0x380FFFFFF0000000 ... 0x1.FFFFFFp-127 (C++17)
static const double   MinSubInexact    = 1.0 * 0x8000000000000000u * 0x01000000;    // 0x4560000000000000 ... 0x1.000000p+087 (C++17)
static const uint8_t  FpExcptTable[16] = { 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x20 };
static const uint32_t i1075            = 1075;
static const uint32_t i1087            = 1087;
static const uint32_t x0800            = 0x0800;
static const uint32_t x17FF            = 0x17FF;
static const uint16_t CWMask           = 0x133F;

double __cdecl _except1(unsigned long, int, double, double, unsigned long, void *);

void __cdecl _ftoui3();
void __cdecl _ftoul3();
void __cdecl _ftol3();
void __cdecl _dtoui3();
void __cdecl _dtoul3();
void __cdecl _dtol3();
void __cdecl _ultod3();
void __cdecl _ltod3();

static void __cdecl ftol3_NaN();
static void __cdecl ftol3_work();
static void __cdecl ftol3_common();
static void __cdecl ftol3_arg_error();
static void __cdecl ftol3_except();
static void __cdecl dtol3_NaN();

#pragma warning(disable:4102 4414)

__declspec(naked) void __cdecl _ftoui3()
{
	__asm
	{
		mov         ecx, 1
		movsd       xmm5, qword ptr [MaxInt64]
		jmp         ftol3_NaN
	}
}

__declspec(naked) void __cdecl _ftoul3()
{
	__asm
	{
		mov         ecx, 2
		movsd       xmm5, qword ptr [MaxUInt64]
		jmp         ftol3_NaN
	}
}

__declspec(naked) void __cdecl _ftol3()
{
	__asm
	{
		mov         ecx, 3
		movsd       xmm5, qword ptr [MaxInt64]
		jmp         ftol3_NaN
	}
}

__declspec(naked) static void __cdecl ftol3_NaN()
{
	__asm
	{
		movd        eax, xmm0
		and         eax, 7FFFFFFFh
		cmp         eax, 7F800000h
		jae         ftol3_arg_error
		cvtss2sd    xmm0, xmm0
		jmp         ftol3_work
	}
}

__declspec(naked) static void __cdecl ftol3_work()
{
	__asm
	{
		cmp         ecx, 2
		jne         ftol3_non_ftoul3
		movsd       xmm2, qword ptr [MinSubInexact]
		comisd      xmm0, xmm2
		jbe         ftol3_non_ftoul3
		mov         edx, 16
		call        ftol3_except

	ftol3_non_ftoul3:
		comisd      xmm0, xmm5
		jae         ftol3_arg_error
		movsd       xmm6, qword ptr [MinInt64]
		comisd      xmm0, xmm6
		jb          ftol3_arg_error
		movdqa      xmm1, xmm0
		psllq       xmm1, 1
		psrlq       xmm1, 1
		cmp         ecx, 1
		je          ftol3_common
		movsd       xmm2, qword ptr [MinFP32]
		comisd      xmm1, xmm2
		ja          ftol3_common
		xorpd       xmm2, xmm2
		comisd      xmm1, xmm2
		je          ftol3_common
		push        eax
		fwait
		fnstcw      word ptr [esp]
		mov         ax, word ptr [esp]
		test        ax, 10h
		pop         eax
		jnz         ftol3_common
		mov         edx, 2
		call        ftol3_except
		xor         eax, eax
		mov         edx, 80000000h
		ret
	}
}

__declspec(naked) static void __cdecl ftol3_common()
{
	__asm
	{
		xorpd       xmm6, xmm6
		comisd      xmm1, xmm6
		je          ftol3_exact
		movsd       xmm3, qword ptr [MantissaMask]
		movsd       xmm4, qword ptr [IntegerBit]
		movd        xmm5, dword ptr [i1075]
		movdqa      xmm6, xmm0
		cmpeqsd     xmm6, xmm1
		movdqa      xmm2, xmm1
		pand        xmm2, xmm3
		por         xmm2, xmm4
		psrlq       xmm1, 52
		movdqa      xmm4, xmm1
		psubq       xmm4, xmm5
		movdqa      xmm3, xmm2
		psllq       xmm3, xmm4
		movdqa      xmm4, xmm5
		psubq       xmm4, xmm1
		movdqa      xmm7, xmm2
		psrlq       xmm7, xmm4
		pcmpgtd     xmm1, xmm5
		punpckldq   xmm1, xmm1
		pand        xmm3, xmm1
		pandn       xmm1, xmm7
		por         xmm1, xmm3
		pxor        xmm5, xmm5
		psubq       xmm5, xmm1
		pand        xmm1, xmm6
		pandn       xmm6, xmm5
		por         xmm6, xmm1
		movd        eax, xmm4
		cmp         eax, 0
		jle         ftol3_exact
		psllq       xmm7, xmm4
		pxor        xmm2, xmm7
		movd        eax, xmm2
		psrldq      xmm2, 4
		movd        edx, xmm2
		or          eax, edx
		jz          ftol3_exact
		mov         edx, 16
		call        ftol3_except

	ftol3_zero:
	ftol3_exact:
		movd        eax, xmm6
		psrldq      xmm6, 4
		movd        edx, xmm6
		ret
	}
}

__declspec(naked) static void __cdecl ftol3_arg_error()
{
	__asm
	{
		mov         edx, 8
		call        ftol3_except
		xor         eax, eax
		mov         edx, 80000000h
		ret
	}
}

__declspec(naked) static void __cdecl ftol3_except()
{
	__asm
	{
		sub         esp, 32
		fwait
		fnstcw      word ptr [esp]
		movzx       eax, word ptr [esp]
		cmp         edx, 8
		je          ftol3_eh_gen
		test        byte ptr [FpExcptTable - 1h + edx], al
		jnz         ftol3_eh_cont

	ftol3_eh_gen:
		fldcw       word ptr [CWMask]
		mov         dword ptr [esp], edx
		mov         dword ptr [esp + 4h], 0
		movsd       qword ptr [esp + 8h], xmm0
		movsd       qword ptr [esp + 10h], xmm0
		mov         dword ptr [esp + 18h], eax
		call        _except1
		fstp        st(0)

	ftol3_eh_cont:
		add         esp, 32
		ret
	}
}

__declspec(naked) void __cdecl _dtoui3()
{
	__asm
	{
		mov         ecx, 1
		movsd       xmm5, qword ptr [MaxInt64]
		jmp         dtol3_NaN
	}
}

__declspec(naked) void __cdecl _dtoul3()
{
	__asm
	{
		mov         ecx, 4
		movsd       xmm5, qword ptr [MaxUInt64]
		jmp         dtol3_NaN
	}
}

__declspec(naked) void __cdecl _dtol3()
{
	__asm
	{
		mov         ecx, 5
		movsd       xmm5, qword ptr [MaxInt64]
		jmp         dtol3_NaN
	}
}

__declspec(naked) static void __cdecl dtol3_NaN()
{
	__asm
	{
		movdqa      xmm1, xmm0
		psrldq      xmm1, 4
		movd        eax, xmm1
		and         eax, 7FFFFFFFh
		cmp         eax, 7FF00000h
		jae         ftol3_arg_error

	dtol3_work:
		cmp         ecx, 1
		je          ftol3_work
		movdqa      xmm1, xmm0
		psllq       xmm1, 1
		psrlq       xmm1, 1
		movsd       xmm2, qword ptr [MaxFP32]
		comisd      xmm1, xmm2
		jbe         dtol3_underflow
		cmp         ecx, 4
		je          dtoul3_overflow
		mov         edx, 1
		call        ftol3_except
		mov         edx, 16
		call        ftol3_except
		jmp         dtol3_underflow

	dtoul3_overflow:
		mov         edx, 16
		call        ftol3_except
		mov         edx, 1
		call        ftol3_except

	dtol3_underflow:
		movsd       xmm2, qword ptr [MinFP32]
		comisd      xmm1, xmm2
		jae         dtol3_inexact
		xorpd       xmm2, xmm2
		comisd      xmm1, xmm2
		je          ftol3_common
		mov         edx, 2
		call        ftol3_except
		mov         edx, 16
		call        ftol3_except
		jmp         ftol3_common

	dtol3_inexact:
		movdqa      xmm3, xmm0
		cmp         ecx, 4
		jne         dtol3_inexact_1
		movsd       xmm2, qword ptr [MaxInt64]
		comisd      xmm3, xmm2
		jb          dtol3_inexact_1
		subpd       xmm3, xmm2

	dtol3_inexact_1:
		movdqa      xmm4, xmm3
		psllq       xmm4, 35
		psrlq       xmm4, 35
		movd        eax, xmm4
		or          eax, eax
		jz          dtol3_exact
		mov         edx, 16
		call        ftol3_except

	dtol3_exact:
		comisd      xmm0, xmm5
		jae         ftol3_arg_error
		movsd       xmm2, qword ptr [MinInt64]
		comisd      xmm0, xmm2
		jb          ftol3_arg_error
		jmp         ftol3_common
	}
}

__declspec(naked) void __cdecl _ultod3()
{
	__asm
	{
		xorps       xmm0, xmm0
		cvtsi2sd    xmm0, ecx
		shr         ecx, 31
		addsd       xmm0, qword ptr [Int32ToUInt32 + ecx * 8]
		test        edx, edx
		jz          ultod3_uint32
		xorps       xmm1, xmm1
		cvtsi2sd    xmm1, edx
		shr         edx, 31
		addsd       xmm1, qword ptr [Int32ToUInt32 + edx * 8]
		mulsd       xmm1, qword ptr [DP2to32]
		addsd       xmm0, xmm1

	ultod3_uint32:
		ret
	}
}

__declspec(naked) void __cdecl _ltod3()
{
	__asm
	{
		xorps       xmm1, xmm1
		cvtsi2sd    xmm1, edx
		xorps       xmm0, xmm0
		cvtsi2sd    xmm0, ecx
		shr         ecx, 31
		mulsd       xmm1, qword ptr [DP2to32]
		addsd       xmm0, qword ptr [Int32ToUInt32 + ecx * 8]
		addsd       xmm0, xmm1
		ret
	}
}
