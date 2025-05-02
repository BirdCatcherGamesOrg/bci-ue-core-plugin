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

		PublicDefinitions.Add("INNER_LOGGING_CATEGORY=" + INNER_LOGGING_CATEGORY);
		PublicDefinitions.Add("BCICORELOG_FORWARD_TO=" + LOG_FORWARD);
		PublicDefinitions.Add("DLLEXPORT_API=" + LOGGING_DLLEXPORT);
		
		PublicDefinitions.Add("CVAR_NAMESPACE_PREFIX=TEXT(\"" + CVAR_NAMESPACE + ".\")");
		
		PublicDefinitions.Add("DEVELOPER_SETTINGS_CATEGORY=TEXT(\"" + DEVELOPER_SETTINGS_CATEGORY + "\")");
		
		PublicDefinitions.Add("STRINGIFY_MACRO=" + STRINGIFY_MACRO);
	}

	/** Logging */
	public static string INNER_LOGGING_CATEGORY = "LogBCICore";
	public static string LOGGING_DLLEXPORT = "BCICORE_API";
	public static string LOG_FORWARD = "UE_LOG";

	/** CVar */
	public static string CVAR_NAMESPACE = "BCI";

	/** Configs */
	public static string DEVELOPER_SETTINGS_CATEGORY = "BCI Plugins";

	/** Macros */
	public static string STRINGIFY_MACRO = "UE_STRINGIZE";

}
