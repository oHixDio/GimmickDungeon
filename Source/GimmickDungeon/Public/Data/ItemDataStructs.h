#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

/*
* 修正項目なし
*/

UENUM()
enum class EItemQuality : uint8
{
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	SuperRare UMETA(DisplayName = "SuperRare"),
	Masterwork UMETA(DisplayName = "Masterwork"),
};

UENUM()
enum class EItemType : uint8
{
	Gold UMETA(DisplayName = "Gold"),
	Gimmick UMETA(DisplayName = "Gimmick"),
	Material UMETA(DisplayName = "Material"),
	Consumable UMETA(DisplayName = "Consumable"),
};

// 未使用
USTRUCT()
struct FItemStatistics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float SaleValue;

	UPROPERTY(EditAnywhere)
	float SellValue;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText; // 未使用
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Weight; // 不使用

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* InventoryIcon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh; // 不使用

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ItemEffect;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnableClass;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData ItemAssetData;
};
