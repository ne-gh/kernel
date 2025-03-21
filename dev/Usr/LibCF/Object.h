
/* -------------------------------------------

	Copyright (C) 2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <LibCF/Foundation.h>

#define CF_OBJECT : public LibCF::CFObject

namespace LibCF
{
	class CFObject;

	class CFObject
	{
	public:
		explicit CFObject() = default;
		virtual ~CFObject() = default;

		SCI_COPY_DEFAULT(CFObject);
	};
} // namespace LibCF