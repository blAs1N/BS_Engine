#pragma once

#include <optional>
#include "BSBase/Type.h"
#include "Name.h"

enum class KeyCode : BSBase::uint8
{
	Escape = 1,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Zero,
	Minus,
	Equals,
	Back,
	Tab,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	LBracket,
	RBracket,
	Return,
	LControl,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Semicolon,
	Apostrophe,
	Grave,
	LShift,
	Backslash,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	Comma,
	Reriod,
	Slash,
	RShift,
	Multiply,
	LMenu,
	Space,
	Capital,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	Numlock,
	Scroll,
	KP7,
	KP8,
	KP9,
	Subtract,
	KP4,
	KP5,
	KP6,
	Add,
	KP1,
	KP2,
	KP3,
	KP0,
	Decimal,
	F11,
	F12,
	F13,
	F14,
	F15,
	Kana,
	Convert,
	NoConvert,
	Yen,
	NumpadEquals,
	CircumFlex,
	At,
	Colon,
	Underline,
	Kanji,
	Stop,
	Ax,
	UnLabeled,
	NumpadeEnter,
	RControl,
	NumpadComma,
	Divide,
	SysRq,
	RMenu,
	Pause,
	Home,
	Up,
	Prior,
	Left,
	Right,
	End,
	Down,
	Next,
	Insert,
	Delete,
	LWin,
	RWin,
	Apps,
	Power,
	Sleep
};

enum class MouseCode : BSBase::uint8 { L, R, M, X1, X2, X3, X4 };
enum class MouseAxis : BSBase::uint8 { X, Y };

NO_ODR Name FromKeyCode(KeyCode code) noexcept
{
	return static_cast<ReservedName>(static_cast<BSBase::int32>
		(ReservedName::Escape) + static_cast<BSBase::int8>(code) - 1);
}

INPUT_API Name FromMouseCode(MouseCode code) noexcept;
INPUT_API Name FromMouseAxis(MouseAxis axis) noexcept;

INPUT_API std::optional<KeyCode> ToKeyCode(Name name) noexcept;
INPUT_API std::optional<MouseCode> ToMouseCode(Name name) noexcept;
INPUT_API std::optional<MouseAxis> ToMouseAxis(Name name) noexcept;