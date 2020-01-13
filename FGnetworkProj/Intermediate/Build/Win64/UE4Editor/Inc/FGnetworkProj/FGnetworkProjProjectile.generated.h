// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef FGNETWORKPROJ_FGnetworkProjProjectile_generated_h
#error "FGnetworkProjProjectile.generated.h already included, missing '#pragma once' in FGnetworkProjProjectile.h"
#endif
#define FGNETWORKPROJ_FGnetworkProjProjectile_generated_h

#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_SPARSE_DATA
#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFGnetworkProjProjectile(); \
	friend struct Z_Construct_UClass_AFGnetworkProjProjectile_Statics; \
public: \
	DECLARE_CLASS(AFGnetworkProjProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FGnetworkProj"), NO_API) \
	DECLARE_SERIALIZER(AFGnetworkProjProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAFGnetworkProjProjectile(); \
	friend struct Z_Construct_UClass_AFGnetworkProjProjectile_Statics; \
public: \
	DECLARE_CLASS(AFGnetworkProjProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FGnetworkProj"), NO_API) \
	DECLARE_SERIALIZER(AFGnetworkProjProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFGnetworkProjProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFGnetworkProjProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFGnetworkProjProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFGnetworkProjProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFGnetworkProjProjectile(AFGnetworkProjProjectile&&); \
	NO_API AFGnetworkProjProjectile(const AFGnetworkProjProjectile&); \
public:


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFGnetworkProjProjectile(AFGnetworkProjProjectile&&); \
	NO_API AFGnetworkProjProjectile(const AFGnetworkProjProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFGnetworkProjProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFGnetworkProjProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFGnetworkProjProjectile)


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(AFGnetworkProjProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AFGnetworkProjProjectile, ProjectileMovement); }


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_9_PROLOG
#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_SPARSE_DATA \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_RPC_WRAPPERS \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_INCLASS \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_SPARSE_DATA \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_INCLASS_NO_PURE_DECLS \
	FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FGNETWORKPROJ_API UClass* StaticClass<class AFGnetworkProjProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FGnetworkProj_Source_FGnetworkProj_FGnetworkProjProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
