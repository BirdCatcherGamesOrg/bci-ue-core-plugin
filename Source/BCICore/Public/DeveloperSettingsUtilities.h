// SPDX-License-Identifier: MPL-2.0

#pragma once

#define BCI_SETTINGS_NAMESPACE(SECTION_NAME) \
do { \
CategoryName = DEVELOPER_SETTINGS_CATEGORY; \
SectionName = TEXT("\"" STRINGIFY_MACRO(SECTION_NAME) "\""); \
} while(0)

/**
 * @brief Utility functions for any BCI plugin developer settings.
 */
struct BCICoreDeveloperSettingsUtilities
{
	
	/**
	 * @brief The category name to use.
	 */
	const static FName CategoryName;
	
};
