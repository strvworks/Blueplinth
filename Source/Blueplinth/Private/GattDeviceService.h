﻿#pragma once

#include "CoreMinimal.h"

#include "BluetoothAddress.h"
#include "GuidHelper.h"
#include "GuidOverloads.h"
#include "WinRT.h"
#include "ByteUtils.h"
#include "Kismet/ImportanceSamplingLibrary.h"

#include "GattDeviceService.generated.h"

UCLASS(BlueprintType)
class UGattDeviceService final : public UObject
{
	GENERATED_BODY()

private:
	using FGattDeviceService = winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattDeviceService;
	FGattDeviceService DeviceService{nullptr, winrt::take_ownership_from_abi};
	FString DeviceName;
	FBluetoothAddress BluetoothAddress;

	friend class ULatentGetGattDeviceServiceByUuid;

public:
	UGattDeviceService() {}

	UFUNCTION(BlueprintPure, Category="Blueplinth")
	FGuid GetServiceUuid() const
	{
		return BPLGuidHelper::GuidCast<FGuid>(DeviceService.Uuid());
	}

	UFUNCTION(BlueprintPure, Category="Blueplinth")
	FString GetDeviceId() const
	{
		return FString(DeviceService.DeviceId().c_str());
	}

	UFUNCTION(BlueprintPure, Category="Blueplinth")
	FString GetDeviceName() const
	{
		return DeviceName;
	}

	UFUNCTION(BlueprintPure, Category="Blueplinth")
	void GetBleAddress(FBluetoothAddress& Address) const
	{
		Address = BluetoothAddress;
	}
};
