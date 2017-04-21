// The plugin still works for ProcessHacker without being registered.
// Add this file only if you want to show it in the registered plugin list in PH.
// Required steps:
// - Add the necessary PH include directories to the projects.
// - Add the PH library to the linker.
// - Add the following lines of code at DLL_PROCESS_ATTACH in main.c
//        BOOL RegisterPlugin(__in HINSTANCE Instance);
//        if (!RegisterPlugin(Instance)) {
//            return FALSE;
//        }

#include <phdk.h>

PPH_PLUGIN PluginInstance;
PH_CALLBACK_REGISTRATION PluginUnloadCallbackRegistration;

VOID NTAPI UnloadCallback(
	__in_opt PVOID Parameter,
	__in_opt PVOID Context
)
{
}

BOOL RegisterPlugin(__in HINSTANCE Instance)
{
	PPH_PLUGIN_INFORMATION info;

	PluginInstance = PhRegisterPlugin(L"TT.MalHide", Instance, &info);

	if (!PluginInstance)
		return FALSE;

	info->DisplayName = L"MalHide";
	info->Author = L"TETYYS";
	info->Description = L"Changes window properties to prevent malware killing ProcessHacker, however you will not able to see user running PH.";
	info->HasOptions = FALSE;
	info->Url = L"http://wj32.org/processhacker/forums/viewtopic.php?f=18&t=1301&p=5731";

	PhRegisterCallback(
		PhGetPluginCallback(PluginInstance, PluginCallbackUnload),
		UnloadCallback,
		NULL,
		&PluginUnloadCallbackRegistration
	);

	return TRUE;
}
