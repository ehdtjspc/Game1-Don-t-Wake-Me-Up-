// Fill out your copyright notice in the Description page of Project Settings.


#include "System/G1AssetManager.h"

UG1AssetManager::UG1AssetManager() : Super()
{

}

UG1AssetManager& UG1AssetManager::Get()
{
	if (UG1AssetManager* Singleton = Cast<UG1AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Can't find UG1AssetManager"));

	return *NewObject<UG1AssetManager>();
}

void UG1AssetManager::Initialize()
{
	Get().LoadPreloadAssets();
}

void UG1AssetManager::LoadSyncByPath(const FSoftObjectPath& AssetPath)  //������
{
	if (AssetPath.IsValid())
	{
		UObject* LoadedAsset = AssetPath.ResolveObject();  // ResolveObject  : ���� �̰�ο� �ִ°� �̹� �ε��� ���� �ִ��� �޸𸮿� ��� �ִ����� �ִ��� ã�� �Լ�
		if (LoadedAsset == nullptr)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false); //�𸮾󿡼� �����ϴ� �Լ��� ����ؼ� ���� ó�����Ѵ�.
			}
			else
			{
				LoadedAsset = AssetPath.TryLoad();  // ���������� ����ó��
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAsset(AssetPath.GetAssetFName(), LoadedAsset);  // �ε��� ���̸� GetAssetFName�� �̸����� ����� �ϰڴ�.
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
		}
	}
}

void UG1AssetManager::LoadSyncByName(const FName& AssetName)
{
	UG1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadSyncByPath(AssetPath);
}




void UG1AssetManager::AddLoadedAsset(const FName& AssetName, const UObject* Asset)
{
	if (AssetName.IsValid() && Asset)
	{
		//FScopeLock LoadedAssetsLock(&LoadedAssetsCritical); ���� ��´�.

		if (NameToLoadedAsset.Contains(AssetName) == false)  //Contains : Ű�� �ִ��� Ȯ�� ��/�������� ��ȯ���� 
		{
			NameToLoadedAsset.Add(AssetName, Asset);
		}
	}
}

//�±װ� ���� �ֵ��� �� �� �ܾ���� ����
void UG1AssetManager::LoadSyncByLabel(const FName& Label)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UG1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;

	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabel(Label);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadSyncByPath(AssetPath);
		if (AssetPath.IsValid())
		{
			AssetPaths.Emplace(AssetPath);
		}
	}

	GetStreamableManager().RequestSyncLoad(AssetPaths);     // Unreal Engine���� ������ ���������� �ε��ϴµ� ���ȴ�.

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			if (UObject* LoadedAsset = AssetPath.ResolveObject())
			{
				Get().AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
			}
		}
	}
}


void UG1AssetManager::ReleaseByPath(const FSoftObjectPath& AssetPath)
{
	FName AssetName = AssetPath.GetAssetFName();
	ReleaseByName(AssetName);
}


void UG1AssetManager::ReleaseByName(const FName& AssetName)
{
	UG1AssetManager& AssetManager = Get();
	if (AssetManager.NameToLoadedAsset.Contains(AssetName))
	{
		AssetManager.NameToLoadedAsset.Remove(AssetName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
	}
}

void UG1AssetManager::ReleaseByLabel(const FName& Label)
{
	UG1AssetManager& AssetManager = Get();
	UG1AssetData* LoadedAssetData = AssetManager.LoadedAssetData;
	const FAssetSet& AssetSet = LoadedAssetData->GetAssetSetByLabel(Label);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FName& AssetName = AssetEntry.AssetName;
		if (AssetManager.NameToLoadedAsset.Contains(AssetName))
		{
			AssetManager.NameToLoadedAsset.Remove(AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
		}
	}
}

void UG1AssetManager::ReleaseAll()
{
	UG1AssetManager& AssetManager = Get();
	AssetManager.NameToLoadedAsset.Reset();
}

void UG1AssetManager::LoadPreloadAssets()
{
	if (LoadedAssetData)
		return;

	UG1AssetData* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UG1AssetData::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UG1AssetData>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		LoadedAssetData = AssetData;
		LoadSyncByLabel("Preload");
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load AssetData asset type [%s]."), *PrimaryAssetType.ToString());
	}
}