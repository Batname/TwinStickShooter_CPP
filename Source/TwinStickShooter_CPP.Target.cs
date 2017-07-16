// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TwinStickShooter_CPPTarget : TargetRules
{
	public TwinStickShooter_CPPTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TwinStickShooter_CPP" } );
	}
}
