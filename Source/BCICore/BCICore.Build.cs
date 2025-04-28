// SPDX-License-Identifier: MPL-2.0

#region

using System.IO;
using System.Linq;
using UnrealBuildTool;

#endregion

public class BCICore : ModuleRules
{
	public BCICore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Logging", "Private"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Logging", "Public"));
		
		PublicDependencyModuleNames.AddRange(new[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			});
		
		if (Target.OptionalPlugins.Contains("spdlog"))
		{
	    	bEnableExceptions = true;
			PublicIncludePaths.Add(spdlog.IncludePath(Path.Combine(PluginDirectory, "../../ThirdParty")));
			PublicDefinitions.Add("WITH_SPDLOG");
			PublicDependencyModuleNames.Add("spdlog");
		}

		PublicDefinitions.Add("BCICORELOG_FORWARD_TO=" + LOG_FORWARD_MACRO);
	}

	public static string LOG_FORWARD_MACRO = "UE_LOG";
}
