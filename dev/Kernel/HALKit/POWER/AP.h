/* -------------------------------------------

	Copyright (C) 2024-2025, Amlal EL Mahrouss, all rights reserved.

	File: AP.h
	Purpose: POWER hardware threads.

	Revision History:

	14/04/24: Added file (amlel)

------------------------------------------- */

#pragma once

#include <NewKit/Defines.h>

namespace NeOS
{
	struct HAL_HARDWARE_THREAD;

	/// @brief hardware thread indentification type.
	typedef NeOS::Int32 hal_ap_kind;

	/// @brief Hardware thread information structure.
	typedef struct HAL_HARDWARE_THREAD
	{
		NeOS::UIntPtr fStartAddress;
		NeOS::UInt8	  fPrivleged : 1;
		NeOS::UInt32  fPageMemoryFlags;
		hal_ap_kind	  fIdentNumber;
	} HAL_HARDWARE_THREAD;

	/// @brief Set PC to specific hart.
	/// @param hart the hart
	/// @param epc the pc.
	/// @return
	EXTERN_C NeOS::Void hal_set_pc_to_hart(HAL_HARDWARE_THREAD* hart, NeOS::VoidPtr epc);
} // namespace NeOS
