// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/G1AssetData.h"
#include "UObject/ObjectSaveContext.h"

void UG1AssetData::PreSave(FObjectPreSaveContext ObjectSaveContext)  // 이 PDA를 저장하는 순간에 호출이 된다.
{
	Super::PreSave(ObjectSaveContext);

	AssetNameToPath.Empty();    // ->  Empty : 삭제하는 함수임 비어있나 확인하는게 아니라
	AssetLabelToSet.Empty();

	AssetGroupNameToSet.KeySort([](const FName& A, const FName& B)
		{
			return (A.Compare(B) < 0);
		});

	for (const auto& Pair : AssetGroupNameToSet)
	{
		const FAssetSet& AssetSet = Pair.Value;
		for (FAssetEntry AssetEntry : AssetSet.AssetEntries)
		{
			FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
			/*const FString& AssetName = AssetPath.GetAssetName();
			if (AssetName.StartsWith(TEXT("BP_")) || AssetName.StartsWith(TEXT("B_")) || AssetName.StartsWith(TEXT("WBP_")) ||
				AssetName.StartsWith(TEXT("GE_")) || AssetName.StartsWith(TEXT("GA_")) || AssetName.StartsWith(TEXT("ABP_")))
			{
				FString AssetPathString = AssetPath.GetAssetPathString();
				AssetPathString.Append(TEXT("_C"));
				AssetPath = FSoftObjectPath(AssetPathString);
			}*/

			AssetNameToPath.Emplace(AssetEntry.AssetName, AssetEntry.AssetPath);  // Emplace : push_back랑 비슷함
			for (const FName& Label : AssetEntry.AssetLabels)
			{
				AssetLabelToSet.FindOrAdd(Label).AssetEntries.Emplace(AssetEntry);
			}
		}
	}
}    //값들을 하나하나 꺼내서 캐싱을 해줌, 최적화 부분 두번안찾아도 됨

FSoftObjectPath UG1AssetData::GetAssetPathByName(const FName& AssetName)
{
	FSoftObjectPath* AssetPath = AssetNameToPath.Find(AssetName);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't find Asset Path from Asset Name [%s]."), *AssetName.ToString());
	return *AssetPath;
}						 //캐싱 된 부분 긁어오기


const FAssetSet& UG1AssetData::GetAssetSetByLabel(const FName& Label)
{
	const FAssetSet* AssetSet = AssetLabelToSet.Find(Label);
	ensureAlwaysMsgf(AssetSet, TEXT("Can't find Asset Set from Label [%s]."), *Label.ToString());
	return *AssetSet;
}                        //캐싱 된 부분 긁어오기


