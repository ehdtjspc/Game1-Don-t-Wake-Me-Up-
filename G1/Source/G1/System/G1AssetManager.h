// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/G1AssetData.h"
#include "Engine/AssetManager.h"
#include "G1AssetManager.generated.h"

class UG1AssetData;

/**
 * 
 */
UCLASS()
class G1_API UG1AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UG1AssetManager();

	static UG1AssetManager& Get();
	
public:
	static void Initialize();

	template<typename AssetType>
	static AssetType* GetAssetByName(const FName& AssetName);

	//동기 방식
	static void LoadSyncByPath(const FSoftObjectPath& AssetPath);
	static void LoadSyncByName(const FName& AssetName);
	static void LoadSyncByLabel(const FName& Label);

	// 부분적으로 어떤 에셋을 버리고 다시 로드하고 맵 이동했으면 그런 부분을 처리할 때 이용
	static void ReleaseByPath(const FSoftObjectPath& AssetPath);
	static void ReleaseByName(const FName& AssetName);
	static void ReleaseByLabel(const FName& Label);
	static void ReleaseAll();

private:
	void LoadPreloadAssets();  //Preload태그를 붙인애들을 한번에 처음에 로딩하고 시작하겠다는 함수
	void AddLoadedAsset(const FName& AssetName, const UObject* Asset);
	

private:
	UPROPERTY()
	TObjectPtr<UG1AssetData> LoadedAssetData;    // 로딩한 에셋을 여기에서 들고있는다.

	UPROPERTY()
	TMap<FName, TObjectPtr<const UObject>> NameToLoadedAsset;  // 이름과 에셋을 캐싱하는 부분임

};


template<typename AssetType>
AssetType* UG1AssetManager::GetAssetByName(const FName& AssetName)
{
	UG1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	if (AssetPath.IsValid())
	{
		LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());
		if (LoadedAsset == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted sync loading because asset hadn't loaded yet [%s]."), *AssetPath.ToString());
			LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
		}
	}
	return LoadedAsset;
}
