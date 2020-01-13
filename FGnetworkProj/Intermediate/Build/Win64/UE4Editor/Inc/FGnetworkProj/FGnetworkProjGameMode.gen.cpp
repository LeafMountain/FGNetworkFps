// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FGnetworkProj/FGnetworkProjGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFGnetworkProjGameMode() {}
// Cross Module References
	FGNETWORKPROJ_API UClass* Z_Construct_UClass_AFGnetworkProjGameMode_NoRegister();
	FGNETWORKPROJ_API UClass* Z_Construct_UClass_AFGnetworkProjGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_FGnetworkProj();
// End Cross Module References
	void AFGnetworkProjGameMode::StaticRegisterNativesAFGnetworkProjGameMode()
	{
	}
	UClass* Z_Construct_UClass_AFGnetworkProjGameMode_NoRegister()
	{
		return AFGnetworkProjGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AFGnetworkProjGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFGnetworkProjGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_FGnetworkProj,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFGnetworkProjGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "FGnetworkProjGameMode.h" },
		{ "ModuleRelativePath", "FGnetworkProjGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFGnetworkProjGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFGnetworkProjGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFGnetworkProjGameMode_Statics::ClassParams = {
		&AFGnetworkProjGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFGnetworkProjGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFGnetworkProjGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFGnetworkProjGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFGnetworkProjGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFGnetworkProjGameMode, 1079871456);
	template<> FGNETWORKPROJ_API UClass* StaticClass<AFGnetworkProjGameMode>()
	{
		return AFGnetworkProjGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFGnetworkProjGameMode(Z_Construct_UClass_AFGnetworkProjGameMode, &AFGnetworkProjGameMode::StaticClass, TEXT("/Script/FGnetworkProj"), TEXT("AFGnetworkProjGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFGnetworkProjGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
