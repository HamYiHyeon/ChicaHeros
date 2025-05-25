// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ChicaHeros/HPwidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHPwidget() {}

// Begin Cross Module References
CHICAHEROS_API UClass* Z_Construct_UClass_UHPwidget();
CHICAHEROS_API UClass* Z_Construct_UClass_UHPwidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UProgressBar_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_ChicaHeros();
// End Cross Module References

// Begin Class UHPwidget
void UHPwidget::StaticRegisterNativesUHPwidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHPwidget);
UClass* Z_Construct_UClass_UHPwidget_NoRegister()
{
	return UHPwidget::StaticClass();
}
struct Z_Construct_UClass_UHPwidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "HPwidget.h" },
		{ "ModuleRelativePath", "HPwidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HealthBar_MetaData[] = {
		{ "Bindwidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "HPwidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HealthBar;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHPwidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UHPwidget_Statics::NewProp_HealthBar = { "HealthBar", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHPwidget, HealthBar), Z_Construct_UClass_UProgressBar_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HealthBar_MetaData), NewProp_HealthBar_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHPwidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHPwidget_Statics::NewProp_HealthBar,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHPwidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UHPwidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_ChicaHeros,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHPwidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHPwidget_Statics::ClassParams = {
	&UHPwidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UHPwidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UHPwidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHPwidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UHPwidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UHPwidget()
{
	if (!Z_Registration_Info_UClass_UHPwidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHPwidget.OuterSingleton, Z_Construct_UClass_UHPwidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHPwidget.OuterSingleton;
}
template<> CHICAHEROS_API UClass* StaticClass<UHPwidget>()
{
	return UHPwidget::StaticClass();
}
UHPwidget::UHPwidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UHPwidget);
UHPwidget::~UHPwidget() {}
// End Class UHPwidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HPwidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHPwidget, UHPwidget::StaticClass, TEXT("UHPwidget"), &Z_Registration_Info_UClass_UHPwidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHPwidget), 84983068U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HPwidget_h_1810845524(TEXT("/Script/ChicaHeros"),
	Z_CompiledInDeferFile_FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HPwidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ChicaHeros_ChicaHeros_Source_ChicaHeros_HPwidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
