// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "ProtocolSocketBase.h"
#include "ProtocolTcpIpSocket.generated.h"

UCLASS(BlueprintType, Blueprintable)
class OBJECTDELIVERER_API UProtocolTcpIpSocket : public UProtocolSocketBase
{
	GENERATED_BODY()

public:
	UProtocolTcpIpSocket();
	virtual ~UProtocolTcpIpSocket();

	virtual void Close() override;
	virtual void Send(const TArray<uint8>& DataBuffer) const override;

	void OnConnected(FSocket* ConnectionSocket);

	virtual void RequestSend(const TArray<uint8>& DataBuffer) override;

	UFUNCTION(BlueprintPure, Category = "ObjectDeliverer")
	bool GetIPAddress(TArray<uint8>& IPAddress);

	UFUNCTION(BlueprintPure, Category = "ObjectDeliverer")
	bool GetIPAddressInString(FString& IPAddress);

	UFUNCTION(BlueprintPure, Category = "ObjectDeliverer")
	bool GetIPAddressAndPortInString(FString& IPAddressAndPort);

	UFUNCTION(BlueprintPure, Category = "ObjectDeliverer")
	bool GetPortNumber(int32& Port);

protected:
	void CloseSocket();
	void StartPollilng();
	bool ReceivedData();

protected:
	class FWorkerThread* CurrentInnerThread = nullptr;
	class FRunnableThread* CurrentThread = nullptr;

	TArray<uint8> ReceiveBuffer;
	FCriticalSection ct;
	bool IsSelfClose = false;
};
