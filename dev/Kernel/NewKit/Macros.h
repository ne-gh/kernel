/* -------------------------------------------

	Copyright (C) 2024-2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#ifndef KIB
#define KIB(X) (NeOS::UInt64)((X) / 1024)
#endif

#ifndef kib_cast
#define kib_cast(X) (NeOS::UInt64)((X)*1024)
#endif

#ifndef MIB
#define MIB(X) (NeOS::UInt64)((NeOS::UInt64)KIB(X) / 1024)
#endif

#ifndef mib_cast
#define mib_cast(X) (NeOS::UInt64)((NeOS::UInt64)kib_cast(X) * 1024)
#endif

#ifndef GIB
#define GIB(X) (NeOS::UInt64)((NeOS::UInt64)MIB(X) / 1024)
#endif

#ifndef gib_cast
#define gib_cast(X) (NeOS::UInt64)((NeOS::UInt64)mib_cast(X) * 1024)
#endif

#ifndef TIB
#define TIB(X) (NeOS::UInt64)((NeOS::UInt64)GIB(X) / 1024)
#endif

#ifndef tib_cast
#define tib_cast(X) ((NeOS::UInt64)gib_cast(X) * 1024)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)              \
	(((sizeof(a) / sizeof(*(a))) / \
	  (static_cast<NeOS::Size>(!(sizeof(a) % sizeof(*(a)))))))
#endif

#define DEPRECATED ATTRIBUTE(deprecated)

#ifndef ALIGN
#define ALIGN(X) __attribute__((aligned(X)))
#endif // #ifndef ALIGN

#ifndef ATTRIBUTE
#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#endif // #ifndef ATTRIBUTE

#ifndef __NE_VER__
#define __NE_VER__ (2024)
#endif // !__NE_VER__

#ifndef EXTERN
#define EXTERN extern
#endif

#ifndef EXTERN_C
#define EXTERN_C extern "C"
#endif

#ifndef MAKE_ENUM
#define MAKE_ENUM(NAME) \
	enum NAME           \
	{
#endif

#ifndef END_ENUM
#define END_ENUM() \
	}              \
	;
#endif

#ifndef MAKE_STRING_ENUM
#define MAKE_STRING_ENUM(NAME) \
	namespace NAME             \
	{
#endif

#ifndef ENUM_STRING
#define ENUM_STRING(NAME, VAL) inline constexpr const char* e##NAME = VAL
#endif

#ifndef END_STRING_ENUM
#define END_STRING_ENUM() }
#endif

#ifndef RTL_ALLOCA
#define RTL_ALLOCA(sz) __builtin_alloca(sz)
#endif // #ifndef RTL_ALLOCA

#ifndef CANT_REACH
#define CANT_REACH() __builtin_unreachable()
#endif

#define kInvalidAddress 0xFBFBFBFBFBFBFBFB
#define kBadAddress		0x0000000000000000
#define kMaxAddr		0xFFFFFFFFFFFFFFFF
#define kPathLen		0x100

#define PACKED	ATTRIBUTE(packed)
#define NO_EXEC ATTRIBUTE(noexec)

#define EXTERN extern
#define STATIC static

#define CONST const

#define STRINGIFY(X) #X
#define NE_UNUSED(X) ((NeOS::Void)X)

#ifndef RGB
#define RGB(R, G, B) (NeOS::UInt32)(R | G << 0x8 | B << 0x10)
#endif // !RGB

#ifdef __NE_AMD64__
#define dbg_break_point() asm volatile("int $3")
#else
#define dbg_break_point() ((void)0)
#endif

#define RTL_ENDIAN(address, value)                            \
	(((reinterpret_cast<NeOS::Char*>(address)[0]) == (value)) \
		 ? (NeOS::Endian::kEndianBig)                         \
		 : (NeOS::Endian::kEndianLittle))

#define Yes true
#define No	false

#define YES true
#define NO	false

#define TRUE  true
#define FALSE false

#define BOOL NeOS::Boolean

#ifdef RTL_INIT_OBJECT
#undef RTL_INIT_OBJECT
#endif // ifdef RTL_INIT_OBJECT

#define RTL_INIT_OBJECT(OBJ, TYPE, ...) TYPE OBJ = TYPE(__VA_ARGS__)
