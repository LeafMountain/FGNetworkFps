// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FGnetworkProj/FGnetworkProjHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFGnetworkProjHUD() {}
// Cross Module References
	FGNETWORKPROJ_API UClass* Z_Construct_UClass_AFGnetworkProjHUD_NoRegister();
	FGNETWORKPROJ_API UClass* Z_Construct_UClass_AFGnetworkProjHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_FGnetworkProj();
// End Cross Module References
	void AFGnetworkProjHUD::StaticRegisterNativesAFGnetworkProjHUD()
	{
	}
	UClass* Z_Construct_UClass_AFGnetworkProjHUD_NoRegister()
	{
		return AFGnetworkProjHUD::StaticClass();
	}
	struct Z_Construct_UClass_AFGnetworkProjHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFGnetworkProjHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_FGnetworkProj,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFGnetworkProjHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "FGnetworkProjHUD.h" },
		{ "ModuleRelativePath", "FGnetworkProjHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFGnetworkProjHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFGnetworkProjHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFGnetworkProjHUD_Statics::ClassParams = {
		&AFGnetworkProjHUD::StaticClass,
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
		0x008002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFGnetworkProjHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFGnetworkProjHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFGnetworkProjHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFGnetworkProjHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFGnetworkProjHUD, 3115795443);
	template<> FGNETWORKPROJ_API UClass* StaticClass<AFGnetworkProjHUD>()
	{
		return AFGnetworkProjHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFGnetworkProjHUD(Z_Construct_UClass_AFGnetworkProjHUD, &AFGnetworkProjHUD::StaticClass, TEXT("/Script/FGnetworkProj"), TEXT("AFGnetworkProjHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFGnetworkProjHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
