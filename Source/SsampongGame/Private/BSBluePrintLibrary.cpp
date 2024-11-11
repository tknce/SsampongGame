// Fill out your copyright notice in the Description page of Project Settings.


#include "BSBluePrintLibrary.h"



bool UBSBluePrintLibrary::IsInEditor()
{
	return GIsEditor;
}

FString UBSBluePrintLibrary::GetProjectVersion()
{
	FString ProjectVersion;

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);

	return ProjectVersion;
}
