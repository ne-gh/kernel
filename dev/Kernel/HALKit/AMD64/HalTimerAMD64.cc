/* -------------------------------------------

	Copyright (C) 2024-2025, Amlal EL Mahrouss, all rights reserved.

	File: HalTimer.cc
	Purpose: HAL timer

	Revision History:

	07/07/24: Added file (amlel)

------------------------------------------- */

#include <Mod/ACPI/ACPIFactoryInterface.h>
#include <ArchKit/ArchKit.h>
#include <KernelKit/Timer.h>

// timer slot 0

#define cHPETCounterRegValue   (0x00)
#define cHPETConfigRegValue	   (0x20)
#define cHPETCompRegValue	   (0x24)
#define cHPETInterruptRegValue (0x2C)

///! BUGS: 0
///! @file HalTimer.cc
///! @brief Hardware Timer (HPET)

namespace NeOS::Detail
{
	struct HPET_BLOCK : public NeOS::SDT
	{
		NeOS::UInt8	 hardware_rev_id;
		NeOS::UInt8	 comparator_count : 5;
		NeOS::UInt8	 counter_size : 1;
		NeOS::UInt8	 reserved : 1;
		NeOS::UInt8	 legacy_replacement : 1;
		NeOS::UInt16 pci_vendor_id;
		ACPI_ADDRESS address;
		NeOS::UInt8	 hpet_number;
		NeOS::UInt16 minimum_tick;
		NeOS::UInt8	 page_protection;
	} PACKED;
} // namespace NeOS::Detail

using namespace NeOS;

HardwareTimer::HardwareTimer(Int64 ms)
	: fWaitFor(ms)
{
	auto power = PowerFactoryInterface(kHandoverHeader->f_HardwareTables.f_VendorPtr);

	auto hpet = (Detail::HPET_BLOCK*)power.Find("HPET").Leak().Leak();
	MUST_PASS(hpet);

	fDigitalTimer = (IntPtr*)hpet->address.Address;
}

HardwareTimer::~HardwareTimer()
{
	fDigitalTimer = nullptr;
	fWaitFor	  = 0;
}

BOOL HardwareTimer::Wait() noexcept
{
	if (fWaitFor < 1)
		return NO;

	// if not enabled yet.
	if (!(*(fDigitalTimer + cHPETConfigRegValue) & (1 << 0)))
	{
		*(fDigitalTimer + cHPETConfigRegValue) |= (1 << 0); // enable it
		*(fDigitalTimer + cHPETConfigRegValue) |= (1 << 3); // one shot conf
	}

	UInt64 ticks = fWaitFor / ((*(fDigitalTimer) >> 32) & __UINT32_MAX__);
	UInt64 prev	 = *(fDigitalTimer + cHPETCounterRegValue);

	prev += ticks;

	while (*(fDigitalTimer + cHPETCounterRegValue) < (ticks))
		;

	return YES;
}
