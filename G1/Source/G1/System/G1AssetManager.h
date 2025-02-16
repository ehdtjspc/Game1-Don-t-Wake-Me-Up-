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

	//���� ���
	static void LoadSyncByPath(const FSoftObjectPath& AssetPath);
	static void LoadSyncByName(const FName& AssetName);
	static void LoadSyncByLabel(const FName& Label);

	// �κ������� � ������ ������ �ٽ� �ε��ϰ� �� �̵������� �׷� �κ��� ó���� �� �̿�
	static void ReleaseByPath(const FSoftObjectPath& AssetPath);
	static void ReleaseByName(const FName& AssetName);
	static void ReleaseByLabel(const FName& Label);
	static void ReleaseAll();

private:
	void LoadPreloadAssets();  //Preload�±׸� ���ξֵ��� �ѹ��� ó���� �ε��ϰ� �����ϰڴٴ� �Լ�
	void AddLoadedAsset(const FName& AssetName, const UObject* Asset);
	

private:
	UPROPERTY()
	TObjectPtr<UG1AssetData> LoadedAssetData;    // �ε��� ������ ���⿡�� ����ִ´�.

	UPROPERTY()
	TMap<FName, TObjectPtr<const UObject>> NameToLoadedAsset;  // �̸��� ������ ĳ���ϴ� �κ���

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
