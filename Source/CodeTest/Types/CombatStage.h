#pragma once

UENUM(BlueprintType)
enum class ECombatStage : uint8
{
	ECS_Free UMETA(DisplayName = "Free"),
	ECS_Attack UMETA(DisplayName = "Attack"),
	ECS_MAX UMETA(DisplayName = "MAX"),
};