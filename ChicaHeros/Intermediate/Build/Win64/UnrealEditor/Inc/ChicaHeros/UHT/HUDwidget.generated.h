// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HUDwidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHICAHEROS_HUDwidget_generated_h
#error "HUDwidget.generated.h already included, missing '#pragma once' in HUDwidget.h"
#endif
#define CHICAHEROS_HUDwidget_generated_h

#define FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHUDwidget(); \
	friend struct Z_Construct_UClass_UHUDwidget_Statics; \
public: \
	DECLARE_CLASS(UHUDwidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ChicaHeros"), NO_API) \
	DECLARE_SERIALIZER(UHUDwidget)


#define FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHUDwidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHUDwidget(UHUDwidget&&); \
	UHUDwidget(const UHUDwidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHUDwidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHUDwidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHUDwidget) \
	NO_API virtual ~UHUDwidget();


#define FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_12_PROLOG
#define FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_16_INCLASS_NO_PURE_DECLS \
	FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHICAHEROS_API UClass* StaticClass<class UHUDwidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HUDwidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
