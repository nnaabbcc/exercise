
#include <Windows.h>
#include <initguid.h>
#include <Cfgmgr32.h>
#include <devpkey.h>
#include <string>
#include <list>
#include <fstream>
#include <iomanip>
#include <iostream>

#pragma comment(lib, "OneCoreUAP.lib")

template <typename sType>
static sType ws2s(std::wstring ws, UINT codePage)
{
    auto size = WideCharToMultiByte(codePage, 0, ws.c_str(),
        -1, nullptr, 0, nullptr, nullptr);
    if (size == 0)
    {
        return sType();
    }

    auto buffer = static_cast<char*>(calloc(size, sizeof(char)));
    if (buffer == nullptr)
    {
        return sType();
    }

    auto size1 = WideCharToMultiByte(codePage, 0, ws.c_str(),
        -1, buffer, size, nullptr, nullptr);
    sType str;
    if (size1 == size)
    {
        str = buffer;
    }
    free(buffer);
    return str;
}

std::string fromWCharArray(
        const wchar_t* string)
{
    return ws2s<std::string>(string, CP_UTF8);
}

class Indent
{
    std::string m_indent = "    ";
    int m_level = 0;
public:
    Indent(
        std::string indent = "    ",
        int level = 0)
        : m_indent(indent)
        , m_level(level)
    {}

    Indent& operator++(){
        m_level++;
        return *this;
    }

    Indent operator++(int)
    {
        Indent tmp(*this);
        operator++();
        return tmp;
    }

    Indent& operator--()
    {
        m_level--;
        return *this;
    }

    Indent operator--(int)
    {
        Indent tmp(*this);
        operator--();
        return tmp;
    }

    std::string string() const
    {
        std::string res;
        for (int i = 0; i < m_level; i++)
        {
            res += m_indent;
        }
        return res;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Indent());
};

std::ostream& operator<< (std::ostream& stream, const Indent& indent)
{
    stream << indent.string();
    return stream;
}

std::list<std::string> getStatusList(ULONG status)
{
    std::list<std::string> lst;
    if (status & DN_ROOT_ENUMERATED)
    {
        lst.push_back("DN_ROOT_ENUMERATED");
    }
    if (status & DN_DRIVER_LOADED)
    {
        lst.push_back("DN_DRIVER_LOADED");
    }
    if (status & DN_ENUM_LOADED)
    {
        lst.push_back("DN_ENUM_LOADED");
    }
    if (status & DN_STARTED)
    {
        lst.push_back("DN_STARTED");
    }
    if (status & DN_MANUAL)
    {
        lst.push_back("DN_MANUAL");
    }
    if (status & DN_NEED_TO_ENUM)
    {
        lst.push_back("DN_NEED_TO_ENUM");
    }
    if (status & DN_NOT_FIRST_TIME)
    {
        lst.push_back("DN_NOT_FIRST_TIME");
    }
    if (status & DN_HARDWARE_ENUM)
    {
        lst.push_back("DN_HARDWARE_ENUM");
    }
    if (status & DN_LIAR)
    {
        lst.push_back("DN_LIAR");
    }
    if (status & DN_HAS_MARK)
    {
        lst.push_back("DN_HAS_MARK");
    }
    if (status & DN_HAS_PROBLEM)
    {
        lst.push_back("DN_HAS_PROBLEM");
    }
    if (status & DN_FILTERED)
    {
        lst.push_back("DN_FILTERED");
    }
    if (status & DN_MOVED)
    {
        lst.push_back("DN_MOVED");
    }
    if (status & DN_DISABLEABLE)
    {
        lst.push_back("DN_DISABLEABLE");
    }
    if (status & DN_REMOVABLE)
    {
        lst.push_back("DN_REMOVABLE");
    }
    if (status & DN_PRIVATE_PROBLEM)
    {
        lst.push_back("DN_PRIVATE_PROBLEM");
    }
    if (status & DN_MF_PARENT)
    {
        lst.push_back("DN_MF_PARENT");
    }
    if (status & DN_MF_CHILD)
    {
        lst.push_back("DN_MF_CHILD");
    }
    if (status & DN_WILL_BE_REMOVED)
    {
        lst.push_back("DN_WILL_BE_REMOVED");
    }
    if (status & DN_NOT_FIRST_TIMEE)
    {
        lst.push_back("DN_NOT_FIRST_TIMEE");
    }
    if (status & DN_STOP_FREE_RES)
    {
        lst.push_back("DN_STOP_FREE_RES");
    }
    if (status & DN_REBAL_CANDIDATE)
    {
        lst.push_back("DN_REBAL_CANDIDATE");
    }
    if (status & DN_BAD_PARTIAL)
    {
        lst.push_back("DN_BAD_PARTIAL");
    }
    if (status & DN_NT_ENUMERATOR)
    {
        lst.push_back("DN_NT_ENUMERATOR");
    }
    if (status & DN_NT_DRIVER)
    {
        lst.push_back("DN_NT_DRIVER");
    }
    if (status & DN_NEEDS_LOCKING)
    {
        lst.push_back("DN_NEEDS_LOCKING");
    }
    if (status & DN_ARM_WAKEUP)
    {
        lst.push_back("DN_ARM_WAKEUP");
    }
    if (status & DN_APM_ENUMERATOR)
    {
        lst.push_back("DN_APM_ENUMERATOR");
    }
    if (status & DN_APM_DRIVER)
    {
        lst.push_back("DN_APM_DRIVER");
    }
    if (status & DN_SILENT_INSTALL)
    {
        lst.push_back("DN_SILENT_INSTALL");
    }
    if (status & DN_NO_SHOW_IN_DM)
    {
        lst.push_back("DN_NO_SHOW_IN_DM");
    }
    if (status & DN_BOOT_LOG_PROB)
    {
        lst.push_back("DN_BOOT_LOG_PROB");
    }
    return lst;
}

std::string getProblem(ULONG problem)
{
    switch (problem)
    {
    case CM_PROB_NOT_CONFIGURED:
        return "CM_PROB_NOT_CONFIGURED";
    case CM_PROB_DEVLOADER_FAILED:
        return "CM_PROB_DEVLOADER_FAILED";
    case CM_PROB_OUT_OF_MEMORY:
        return "CM_PROB_OUT_OF_MEMORY";
    case CM_PROB_ENTRY_IS_WRONG_TYPE:
        return "CM_PROB_ENTRY_IS_WRONG_TYPE";
    case CM_PROB_LACKED_ARBITRATOR:
        return "CM_PROB_LACKED_ARBITRATOR";
    case CM_PROB_BOOT_CONFIG_CONFLICT:
        return "CM_PROB_BOOT_CONFIG_CONFLICT";
    case CM_PROB_FAILED_FILTER:
        return "CM_PROB_FAILED_FILTER";
    case CM_PROB_DEVLOADER_NOT_FOUND:
        return "CM_PROB_DEVLOADER_NOT_FOUND";
    case CM_PROB_INVALID_DATA:
        return "CM_PROB_INVALID_DATA";
    case CM_PROB_FAILED_START:
        return "CM_PROB_FAILED_START";
    case CM_PROB_LIAR:
        return "CM_PROB_LIAR";
    case CM_PROB_NORMAL_CONFLICT:
        return "CM_PROB_NORMAL_CONFLICT";
    case CM_PROB_NOT_VERIFIED:
        return "CM_PROB_NOT_VERIFIED";
    case CM_PROB_NEED_RESTART:
        return "CM_PROB_NEED_RESTART";
    case CM_PROB_REENUMERATION:
        return "CM_PROB_REENUMERATION";
    case CM_PROB_PARTIAL_LOG_CONF:
        return "CM_PROB_PARTIAL_LOG_CONF";
    case CM_PROB_UNKNOWN_RESOURCE:
        return "CM_PROB_UNKNOWN_RESOURCE";
    case CM_PROB_REINSTALL:
        return "CM_PROB_REINSTALL";
    case CM_PROB_REGISTRY:
        return "CM_PROB_REGISTRY";
    case CM_PROB_VXDLDR:
        return "CM_PROB_VXDLDR";
    case CM_PROB_WILL_BE_REMOVED:
        return "CM_PROB_WILL_BE_REMOVED";
    case CM_PROB_DISABLED:
        return "CM_PROB_DISABLED";
    case CM_PROB_DEVLOADER_NOT_READY:
        return "CM_PROB_DEVLOADER_NOT_READY";
    case CM_PROB_DEVICE_NOT_THERE:
        return "CM_PROB_DEVICE_NOT_THERE";
    case CM_PROB_MOVED:
        return "CM_PROB_MOVED";
    case CM_PROB_TOO_EARLY:
        return "CM_PROB_TOO_EARLY";
    case CM_PROB_NO_VALID_LOG_CONF:
        return "CM_PROB_NO_VALID_LOG_CONF";
    case CM_PROB_FAILED_INSTALL:
        return "CM_PROB_FAILED_INSTALL";
    case CM_PROB_HARDWARE_DISABLED:
        return "CM_PROB_HARDWARE_DISABLED";
    case CM_PROB_CANT_SHARE_IRQ:
        return "CM_PROB_CANT_SHARE_IRQ";
    case CM_PROB_FAILED_ADD:
        return "CM_PROB_FAILED_ADD";
    case CM_PROB_DISABLED_SERVICE:
        return "CM_PROB_DISABLED_SERVICE";
    case CM_PROB_TRANSLATION_FAILED:
        return "CM_PROB_TRANSLATION_FAILED";
    case CM_PROB_NO_SOFTCONFIG:
        return "CM_PROB_NO_SOFTCONFIG";
    case CM_PROB_BIOS_TABLE:
        return "CM_PROB_BIOS_TABLE";
    case CM_PROB_IRQ_TRANSLATION_FAILED:
        return "CM_PROB_IRQ_TRANSLATION_FAILED";
    case CM_PROB_FAILED_DRIVER_ENTRY:
        return "CM_PROB_FAILED_DRIVER_ENTRY";
    case CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD:
        return "CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD";
    case CM_PROB_DRIVER_FAILED_LOAD:
        return "CM_PROB_DRIVER_FAILED_LOAD";
    case CM_PROB_DRIVER_SERVICE_KEY_INVALID:
        return "CM_PROB_DRIVER_SERVICE_KEY_INVALID";
    case CM_PROB_LEGACY_SERVICE_NO_DEVICES:
        return "CM_PROB_LEGACY_SERVICE_NO_DEVICES";
    case CM_PROB_DUPLICATE_DEVICE:
        return "CM_PROB_DUPLICATE_DEVICE";
    case CM_PROB_FAILED_POST_START:
        return "CM_PROB_FAILED_POST_START";
    case CM_PROB_HALTED:
        return "CM_PROB_HALTED";
    case CM_PROB_PHANTOM:
        return "CM_PROB_PHANTOM";
    case CM_PROB_SYSTEM_SHUTDOWN:
        return "CM_PROB_SYSTEM_SHUTDOWN";
    case CM_PROB_HELD_FOR_EJECT:
        return "CM_PROB_HELD_FOR_EJECT";
    case CM_PROB_DRIVER_BLOCKED:
        return "CM_PROB_DRIVER_BLOCKED";
    case CM_PROB_REGISTRY_TOO_LARGE:
        return "CM_PROB_REGISTRY_TOO_LARGE";
    case CM_PROB_SETPROPERTIES_FAILED:
        return "CM_PROB_SETPROPERTIES_FAILED";
    case CM_PROB_WAITING_ON_DEPENDENCY:
        return "CM_PROB_WAITING_ON_DEPENDENCY";
    case CM_PROB_UNSIGNED_DRIVER:
        return "CM_PROB_UNSIGNED_DRIVER";
    case CM_PROB_USED_BY_DEBUGGER:
        return "CM_PROB_USED_BY_DEBUGGER";
    case CM_PROB_DEVICE_RESET:
        return "CM_PROB_DEVICE_RESET";
    case CM_PROB_CONSOLE_LOCKED:
        return "CM_PROB_CONSOLE_LOCKED";
    case CM_PROB_NEED_CLASS_CONFIG:
        return "CM_PROB_NEED_CLASS_CONFIG";
    default:
        return {};
    }
}

std::string getKnownKeyName(const DEVPROPKEY& key)
{
    if (key == DEVPKEY_NAME)
    {
        return "DEVPKEY_NAME";
    }
    if (key == DEVPKEY_Device_DeviceDesc)
    {
        return "DEVPKEY_Device_DeviceDesc";
    }
    if (key == DEVPKEY_Device_HardwareIds)
    {
        return "DEVPKEY_Device_HardwareIds";
    }
    if (key == DEVPKEY_Device_CompatibleIds)
    {
        return "DEVPKEY_Device_CompatibleIds";
    }
    if (key == DEVPKEY_Device_Service)
    {
        return "DEVPKEY_Device_Service";
    }
    if (key == DEVPKEY_Device_Class)
    {
        return "DEVPKEY_Device_Class";
    }
    if (key == DEVPKEY_Device_ClassGuid)
    {
        return "DEVPKEY_Device_ClassGuid";
    }
    if (key == DEVPKEY_Device_Driver)
    {
        return "DEVPKEY_Device_Driver";
    }
    if (key == DEVPKEY_Device_ConfigFlags)
    {
        return "DEVPKEY_Device_ConfigFlags";
    }
    if (key == DEVPKEY_Device_Manufacturer)
    {
        return "DEVPKEY_Device_Manufacturer";
    }
    if (key == DEVPKEY_Device_FriendlyName)
    {
        return "DEVPKEY_Device_FriendlyName";
    }
    if (key == DEVPKEY_Device_LocationInfo)
    {
        return "DEVPKEY_Device_LocationInfo";
    }
    if (key == DEVPKEY_Device_PDOName)
    {
        return "DEVPKEY_Device_PDOName";
    }
    if (key == DEVPKEY_Device_Capabilities)
    {
        return "DEVPKEY_Device_Capabilities";
    }
    if (key == DEVPKEY_Device_UINumber)
    {
        return "DEVPKEY_Device_UINumber";
    }
    if (key == DEVPKEY_Device_UpperFilters)
    {
        return "DEVPKEY_Device_UpperFilters";
    }
    if (key == DEVPKEY_Device_LowerFilters)
    {
        return "DEVPKEY_Device_LowerFilters";
    }
    if (key == DEVPKEY_Device_BusTypeGuid)
    {
        return "DEVPKEY_Device_BusTypeGuid";
    }
    if (key == DEVPKEY_Device_LegacyBusType)
    {
        return "DEVPKEY_Device_LegacyBusType";
    }
    if (key == DEVPKEY_Device_BusNumber)
    {
        return "DEVPKEY_Device_BusNumber";
    }
    if (key == DEVPKEY_Device_EnumeratorName)
    {
        return "DEVPKEY_Device_EnumeratorName";
    }
    if (key == DEVPKEY_Device_Security)
    {
        return "DEVPKEY_Device_Security";
    }
    if (key == DEVPKEY_Device_SecuritySDS)
    {
        return "DEVPKEY_Device_SecuritySDS";
    }
    if (key == DEVPKEY_Device_DevType)
    {
        return "DEVPKEY_Device_DevType";
    }
    if (key == DEVPKEY_Device_Exclusive)
    {
        return "DEVPKEY_Device_Exclusive";
    }
    if (key == DEVPKEY_Device_Characteristics)
    {
        return "DEVPKEY_Device_Characteristics";
    }
    if (key == DEVPKEY_Device_Address)
    {
        return "DEVPKEY_Device_Address";
    }
    if (key == DEVPKEY_Device_UINumberDescFormat)
    {
        return "DEVPKEY_Device_UINumberDescFormat";
    }
    if (key == DEVPKEY_Device_PowerData)
    {
        return "DEVPKEY_Device_PowerData";
    }
    if (key == DEVPKEY_Device_RemovalPolicy)
    {
        return "DEVPKEY_Device_RemovalPolicy";
    }
    if (key == DEVPKEY_Device_RemovalPolicyDefault)
    {
        return "DEVPKEY_Device_RemovalPolicyDefault";
    }
    if (key == DEVPKEY_Device_RemovalPolicyOverride)
    {
        return "DEVPKEY_Device_RemovalPolicyOverride";
    }
    if (key == DEVPKEY_Device_InstallState)
    {
        return "DEVPKEY_Device_InstallState";
    }
    if (key == DEVPKEY_Device_LocationPaths)
    {
        return "DEVPKEY_Device_LocationPaths";
    }
    if (key == DEVPKEY_Device_BaseContainerId)
    {
        return "DEVPKEY_Device_BaseContainerId";
    }
    if (key == DEVPKEY_Device_InstanceId)
    {
        return "DEVPKEY_Device_InstanceId";
    }
    if (key == DEVPKEY_Device_DevNodeStatus)
    {
        return "DEVPKEY_Device_DevNodeStatus";
    }
    if (key == DEVPKEY_Device_ProblemCode)
    {
        return "DEVPKEY_Device_ProblemCode";
    }
    if (key == DEVPKEY_Device_EjectionRelations)
    {
        return "DEVPKEY_Device_EjectionRelations";
    }
    if (key == DEVPKEY_Device_RemovalRelations)
    {
        return "DEVPKEY_Device_RemovalRelations";
    }
    if (key == DEVPKEY_Device_PowerRelations)
    {
        return "DEVPKEY_Device_PowerRelations";
    }
    if (key == DEVPKEY_Device_BusRelations)
    {
        return "DEVPKEY_Device_BusRelations";
    }
    if (key == DEVPKEY_Device_Parent)
    {
        return "DEVPKEY_Device_Parent";
    }
    if (key == DEVPKEY_Device_Children)
    {
        return "DEVPKEY_Device_Children";
    }
    if (key == DEVPKEY_Device_Siblings)
    {
        return "DEVPKEY_Device_Siblings";
    }
    if (key == DEVPKEY_Device_TransportRelations)
    {
        return "DEVPKEY_Device_TransportRelations";
    }
    if (key == DEVPKEY_Device_ProblemStatus)
    {
        return "DEVPKEY_Device_ProblemStatus";
    }
    if (key == DEVPKEY_Device_Reported)
    {
        return "DEVPKEY_Device_Reported";
    }
    if (key == DEVPKEY_Device_Legacy)
    {
        return "DEVPKEY_Device_Legacy";
    }
    if (key == DEVPKEY_Device_ContainerId)
    {
        return "DEVPKEY_Device_ContainerId";
    }
    if (key == DEVPKEY_Device_InLocalMachineContainer)
    {
        return "DEVPKEY_Device_InLocalMachineContainer";
    }
    if (key == DEVPKEY_Device_Model)
    {
        return "DEVPKEY_Device_Model";
    }
    if (key == DEVPKEY_Device_ModelId)
    {
        return "DEVPKEY_Device_ModelId";
    }
    if (key == DEVPKEY_Device_FriendlyNameAttributes)
    {
        return "DEVPKEY_Device_FriendlyNameAttributes";
    }
    if (key == DEVPKEY_Device_ManufacturerAttributes)
    {
        return "DEVPKEY_Device_ManufacturerAttributes";
    }
    if (key == DEVPKEY_Device_PresenceNotForDevice)
    {
        return "DEVPKEY_Device_PresenceNotForDevice";
    }
    if (key == DEVPKEY_Device_SignalStrength)
    {
        return "DEVPKEY_Device_SignalStrength";
    }
    if (key == DEVPKEY_Device_IsAssociateableByUserAction)
    {
        return "DEVPKEY_Device_IsAssociateableByUserAction";
    }
    if (key == DEVPKEY_Device_ShowInUninstallUI)
    {
        return "DEVPKEY_Device_ShowInUninstallUI";
    }
    if (key == DEVPKEY_Device_Numa_Proximity_Domain)
    {
        return "DEVPKEY_Device_Numa_Proximity_Domain, DEVPKEY_Numa_Proximity_Domain";
    }
    if (key == DEVPKEY_Device_DHP_Rebalance_Policy)
    {
        return "DEVPKEY_Device_DHP_Rebalance_Policy";
    }
    if (key == DEVPKEY_Device_Numa_Node)
    {
        return "DEVPKEY_Device_Numa_Node";
    }
    if (key == DEVPKEY_Device_BusReportedDeviceDesc)
    {
        return "DEVPKEY_Device_BusReportedDeviceDesc";
    }
    if (key == DEVPKEY_Device_IsPresent)
    {
        return "DEVPKEY_Device_IsPresent";
    }
    if (key == DEVPKEY_Device_HasProblem)
    {
        return "DEVPKEY_Device_HasProblem";
    }
    if (key == DEVPKEY_Device_ConfigurationId)
    {
        return "DEVPKEY_Device_ConfigurationId";
    }
    if (key == DEVPKEY_Device_ReportedDeviceIdsHash)
    {
        return "DEVPKEY_Device_ReportedDeviceIdsHash";
    }
    if (key == DEVPKEY_Device_PhysicalDeviceLocation)
    {
        return "DEVPKEY_Device_PhysicalDeviceLocation";
    }
    if (key == DEVPKEY_Device_BiosDeviceName)
    {
        return "DEVPKEY_Device_BiosDeviceName";
    }
    if (key == DEVPKEY_Device_DriverProblemDesc)
    {
        return "DEVPKEY_Device_DriverProblemDesc";
    }
    if (key == DEVPKEY_Device_DebuggerSafe)
    {
        return "DEVPKEY_Device_DebuggerSafe";
    }
    if (key == DEVPKEY_Device_PostInstallInProgress)
    {
        return "DEVPKEY_Device_PostInstallInProgress";
    }
    if (key == DEVPKEY_Device_Stack)
    {
        return "DEVPKEY_Device_Stack";
    }
    if (key == DEVPKEY_Device_ExtendedConfigurationIds)
    {
        return "DEVPKEY_Device_ExtendedConfigurationIds";
    }
    if (key == DEVPKEY_Device_IsRebootRequired)
    {
        return "DEVPKEY_Device_IsRebootRequired";
    }
    if (key == DEVPKEY_Device_FirmwareDate)
    {
        return "DEVPKEY_Device_FirmwareDate";
    }
    if (key == DEVPKEY_Device_FirmwareVersion)
    {
        return "DEVPKEY_Device_FirmwareVersion";
    }
    if (key == DEVPKEY_Device_FirmwareRevision)
    {
        return "DEVPKEY_Device_FirmwareRevision";
    }
    if (key == DEVPKEY_Device_DependencyProviders)
    {
        return "DEVPKEY_Device_DependencyProviders";
    }
    if (key == DEVPKEY_Device_DependencyDependents)
    {
        return "DEVPKEY_Device_DependencyDependents";
    }
    if (key == DEVPKEY_Device_SoftRestartSupported)
    {
        return "DEVPKEY_Device_SoftRestartSupported";
    }
    if (key == DEVPKEY_Device_ExtendedAddress)
    {
        return "DEVPKEY_Device_ExtendedAddress";
    }
    if (key == DEVPKEY_Device_AssignedToGuest)
    {
        return "DEVPKEY_Device_AssignedToGuest";
    }
    if (key == DEVPKEY_Device_SessionId)
    {
        return "DEVPKEY_Device_SessionId";
    }
    if (key == DEVPKEY_Device_InstallDate)
    {
        return "DEVPKEY_Device_InstallDate";
    }
    if (key == DEVPKEY_Device_FirstInstallDate)
    {
        return "DEVPKEY_Device_FirstInstallDate";
    }
    if (key == DEVPKEY_Device_LastArrivalDate)
    {
        return "DEVPKEY_Device_LastArrivalDate";
    }
    if (key == DEVPKEY_Device_LastRemovalDate)
    {
        return "DEVPKEY_Device_LastRemovalDate";
    }
    if (key == DEVPKEY_Device_DriverDate)
    {
        return "DEVPKEY_Device_DriverDate";
    }
    if (key == DEVPKEY_Device_DriverVersion)
    {
        return "DEVPKEY_Device_DriverVersion";
    }
    if (key == DEVPKEY_Device_DriverDesc)
    {
        return "DEVPKEY_Device_DriverDesc";
    }
    if (key == DEVPKEY_Device_DriverInfPath)
    {
        return "DEVPKEY_Device_DriverInfPath";
    }
    if (key == DEVPKEY_Device_DriverInfSection)
    {
        return "DEVPKEY_Device_DriverInfSection";
    }
    if (key == DEVPKEY_Device_DriverInfSectionExt)
    {
        return "DEVPKEY_Device_DriverInfSectionExt";
    }
    if (key == DEVPKEY_Device_MatchingDeviceId)
    {
        return "DEVPKEY_Device_MatchingDeviceId";
    }
    if (key == DEVPKEY_Device_DriverProvider)
    {
        return "DEVPKEY_Device_DriverProvider";
    }
    if (key == DEVPKEY_Device_DriverPropPageProvider)
    {
        return "DEVPKEY_Device_DriverPropPageProvider";
    }
    if (key == DEVPKEY_Device_DriverCoInstallers)
    {
        return "DEVPKEY_Device_DriverCoInstallers";
    }
    if (key == DEVPKEY_Device_ResourcePickerTags)
    {
        return "DEVPKEY_Device_ResourcePickerTags";
    }
    if (key == DEVPKEY_Device_ResourcePickerExceptions)
    {
        return "DEVPKEY_Device_ResourcePickerExceptions";
    }
    if (key == DEVPKEY_Device_DriverRank)
    {
        return "DEVPKEY_Device_DriverRank";
    }
    if (key == DEVPKEY_Device_DriverLogoLevel)
    {
        return "DEVPKEY_Device_DriverLogoLevel";
    }
    if (key == DEVPKEY_Device_NoConnectSound)
    {
        return "DEVPKEY_Device_NoConnectSound";
    }
    if (key == DEVPKEY_Device_GenericDriverInstalled)
    {
        return "DEVPKEY_Device_GenericDriverInstalled";
    }
    if (key == DEVPKEY_Device_AdditionalSoftwareRequested)
    {
        return "DEVPKEY_Device_AdditionalSoftwareRequested";
    }
    if (key == DEVPKEY_Device_SafeRemovalRequired)
    {
        return "DEVPKEY_Device_SafeRemovalRequired";
    }
    if (key == DEVPKEY_Device_SafeRemovalRequiredOverride)
    {
        return "DEVPKEY_Device_SafeRemovalRequiredOverride";
    }
    if (key == DEVPKEY_DrvPkg_Model)
    {
        return "DEVPKEY_DrvPkg_Model";
    }
    if (key == DEVPKEY_DrvPkg_VendorWebSite)
    {
        return "DEVPKEY_DrvPkg_VendorWebSite";
    }
    if (key == DEVPKEY_DrvPkg_DetailedDescription)
    {
        return "DEVPKEY_DrvPkg_DetailedDescription";
    }
    if (key == DEVPKEY_DrvPkg_DocumentationLink)
    {
        return "DEVPKEY_DrvPkg_DocumentationLink";
    }
    if (key == DEVPKEY_DrvPkg_Icon)
    {
        return "DEVPKEY_DrvPkg_Icon";
    }
    if (key == DEVPKEY_DrvPkg_BrandingIcon)
    {
        return "DEVPKEY_DrvPkg_BrandingIcon";
    }
    if (key == DEVPKEY_DeviceClass_UpperFilters)
    {
        return "DEVPKEY_DeviceClass_UpperFilters";
    }
    if (key == DEVPKEY_DeviceClass_LowerFilters)
    {
        return "DEVPKEY_DeviceClass_LowerFilters";
    }
    if (key == DEVPKEY_DeviceClass_Security)
    {
        return "DEVPKEY_DeviceClass_Security";
    }
    if (key == DEVPKEY_DeviceClass_SecuritySDS)
    {
        return "DEVPKEY_DeviceClass_SecuritySDS";
    }
    if (key == DEVPKEY_DeviceClass_DevType)
    {
        return "DEVPKEY_DeviceClass_DevType";
    }
    if (key == DEVPKEY_DeviceClass_Exclusive)
    {
        return "DEVPKEY_DeviceClass_Exclusive";
    }
    if (key == DEVPKEY_DeviceClass_Characteristics)
    {
        return "DEVPKEY_DeviceClass_Characteristics";
    }
    if (key == DEVPKEY_DeviceClass_Name)
    {
        return "DEVPKEY_DeviceClass_Name";
    }
    if (key == DEVPKEY_DeviceClass_ClassName)
    {
        return "DEVPKEY_DeviceClass_ClassName";
    }
    if (key == DEVPKEY_DeviceClass_Icon)
    {
        return "DEVPKEY_DeviceClass_Icon";
    }
    if (key == DEVPKEY_DeviceClass_ClassInstaller)
    {
        return "DEVPKEY_DeviceClass_ClassInstaller";
    }
    if (key == DEVPKEY_DeviceClass_PropPageProvider)
    {
        return "DEVPKEY_DeviceClass_PropPageProvider";
    }
    if (key == DEVPKEY_DeviceClass_NoInstallClass)
    {
        return "DEVPKEY_DeviceClass_NoInstallClass";
    }
    if (key == DEVPKEY_DeviceClass_NoDisplayClass)
    {
        return "DEVPKEY_DeviceClass_NoDisplayClass";
    }
    if (key == DEVPKEY_DeviceClass_SilentInstall)
    {
        return "DEVPKEY_DeviceClass_SilentInstall";
    }
    if (key == DEVPKEY_DeviceClass_NoUseClass)
    {
        return "DEVPKEY_DeviceClass_NoUseClass";
    }
    if (key == DEVPKEY_DeviceClass_DefaultService)
    {
        return "DEVPKEY_DeviceClass_DefaultService";
    }
    if (key == DEVPKEY_DeviceClass_IconPath)
    {
        return "DEVPKEY_DeviceClass_IconPath";
    }
    if (key == DEVPKEY_DeviceClass_DHPRebalanceOptOut)
    {
        return "DEVPKEY_DeviceClass_DHPRebalanceOptOut";
    }
    if (key == DEVPKEY_DeviceClass_ClassCoInstallers)
    {
        return "DEVPKEY_DeviceClass_ClassCoInstallers";
    }
    if (key == DEVPKEY_DeviceInterface_FriendlyName)
    {
        return "DEVPKEY_DeviceInterface_FriendlyName";
    }
    if (key == DEVPKEY_DeviceInterface_Enabled)
    {
        return "DEVPKEY_DeviceInterface_Enabled";
    }
    if (key == DEVPKEY_DeviceInterface_ClassGuid)
    {
        return "DEVPKEY_DeviceInterface_ClassGuid";
    }
    if (key == DEVPKEY_DeviceInterface_ReferenceString)
    {
        return "DEVPKEY_DeviceInterface_ReferenceString";
    }
    if (key == DEVPKEY_DeviceInterface_Restricted)
    {
        return "DEVPKEY_DeviceInterface_Restricted";
    }
    if (key == DEVPKEY_DeviceInterface_UnrestrictedAppCapabilities)
    {
        return "DEVPKEY_DeviceInterface_UnrestrictedAppCapabilities";
    }
    if (key == DEVPKEY_DeviceInterface_SchematicName)
    {
        return "DEVPKEY_DeviceInterface_SchematicName";
    }
    if (key == DEVPKEY_DeviceInterfaceClass_DefaultInterface)
    {
        return "DEVPKEY_DeviceInterfaceClass_DefaultInterface";
    }
    if (key == DEVPKEY_DeviceInterfaceClass_Name)
    {
        return "DEVPKEY_DeviceInterfaceClass_Name";
    }
    if (key == DEVPKEY_DeviceContainer_Address)
    {
        return "DEVPKEY_DeviceContainer_Address";
    }
    if (key == DEVPKEY_DeviceContainer_DiscoveryMethod)
    {
        return "DEVPKEY_DeviceContainer_DiscoveryMethod, DEVPKEY_DeviceDisplay_DiscoveryMethod";
    }
    if (key == DEVPKEY_DeviceContainer_IsEncrypted)
    {
        return "DEVPKEY_DeviceContainer_IsEncrypted";
    }
    if (key == DEVPKEY_DeviceContainer_IsAuthenticated)
    {
        return "DEVPKEY_DeviceContainer_IsAuthenticated";
    }
    if (key == DEVPKEY_DeviceContainer_IsConnected)
    {
        return "DEVPKEY_DeviceContainer_IsConnected";
    }
    if (key == DEVPKEY_DeviceContainer_IsPaired)
    {
        return "DEVPKEY_DeviceContainer_IsPaired";
    }
    if (key == DEVPKEY_DeviceContainer_Icon)
    {
        return "DEVPKEY_DeviceContainer_Icon";
    }
    if (key == DEVPKEY_DeviceContainer_Version)
    {
        return "DEVPKEY_DeviceContainer_Version";
    }
    if (key == DEVPKEY_DeviceContainer_Last_Seen)
    {
        return "DEVPKEY_DeviceContainer_Last_Seen";
    }
    if (key == DEVPKEY_DeviceContainer_Last_Connected)
    {
        return "DEVPKEY_DeviceContainer_Last_Connected";
    }
    if (key == DEVPKEY_DeviceContainer_IsShowInDisconnectedState)
    {
        return "DEVPKEY_DeviceContainer_IsShowInDisconnectedState, DEVPKEY_DeviceDisplay_IsShowInDisconnectedState";
    }
    if (key == DEVPKEY_DeviceContainer_IsLocalMachine)
    {
        return "DEVPKEY_DeviceContainer_IsLocalMachine";
    }
    if (key == DEVPKEY_DeviceContainer_MetadataPath)
    {
        return "DEVPKEY_DeviceContainer_MetadataPath";
    }
    if (key == DEVPKEY_DeviceContainer_IsMetadataSearchInProgress)
    {
        return "DEVPKEY_DeviceContainer_IsMetadataSearchInProgress";
    }
    if (key == DEVPKEY_DeviceContainer_MetadataChecksum)
    {
        return "DEVPKEY_DeviceContainer_MetadataChecksum";
    }
    if (key == DEVPKEY_DeviceContainer_IsNotInterestingForDisplay)
    {
        return "DEVPKEY_DeviceContainer_IsNotInterestingForDisplay, DEVPKEY_DeviceDisplay_IsNotInterestingForDisplay";
    }
    if (key == DEVPKEY_DeviceContainer_LaunchDeviceStageOnDeviceConnect)
    {
        return "DEVPKEY_DeviceContainer_LaunchDeviceStageOnDeviceConnect";
    }
    if (key == DEVPKEY_DeviceContainer_LaunchDeviceStageFromExplorer)
    {
        return "DEVPKEY_DeviceContainer_LaunchDeviceStageFromExplorer";
    }
    if (key == DEVPKEY_DeviceContainer_BaselineExperienceId)
    {
        return "DEVPKEY_DeviceContainer_BaselineExperienceId";
    }
    if (key == DEVPKEY_DeviceContainer_IsDeviceUniquelyIdentifiable)
    {
        return "DEVPKEY_DeviceContainer_IsDeviceUniquelyIdentifiable";
    }
    if (key == DEVPKEY_DeviceContainer_AssociationArray)
    {
        return "DEVPKEY_DeviceContainer_AssociationArray";
    }
    if (key == DEVPKEY_DeviceContainer_DeviceDescription1)
    {
        return "DEVPKEY_DeviceContainer_DeviceDescription1";
    }
    if (key == DEVPKEY_DeviceContainer_DeviceDescription2)
    {
        return "DEVPKEY_DeviceContainer_DeviceDescription2";
    }
    if (key == DEVPKEY_DeviceContainer_HasProblem)
    {
        return "DEVPKEY_DeviceContainer_HasProblem";
    }
    if (key == DEVPKEY_DeviceContainer_IsSharedDevice)
    {
        return "DEVPKEY_DeviceContainer_IsSharedDevice";
    }
    if (key == DEVPKEY_DeviceContainer_IsNetworkDevice)
    {
        return "DEVPKEY_DeviceContainer_IsNetworkDevice, DEVPKEY_DeviceDisplay_IsNetworkDevice";
    }
    if (key == DEVPKEY_DeviceContainer_IsDefaultDevice)
    {
        return "DEVPKEY_DeviceContainer_IsDefaultDevice";
    }
    if (key == DEVPKEY_DeviceContainer_MetadataCabinet)
    {
        return "DEVPKEY_DeviceContainer_MetadataCabinet";
    }
    if (key == DEVPKEY_DeviceContainer_RequiresPairingElevation)
    {
        return "DEVPKEY_DeviceContainer_RequiresPairingElevation";
    }
    if (key == DEVPKEY_DeviceContainer_ExperienceId)
    {
        return "DEVPKEY_DeviceContainer_ExperienceId";
    }
    if (key == DEVPKEY_DeviceContainer_Category)
    {
        return "DEVPKEY_DeviceContainer_Category, DEVPKEY_DeviceDisplay_Category";
    }
    if (key == DEVPKEY_DeviceContainer_Category_Desc_Singular)
    {
        return "DEVPKEY_DeviceContainer_Category_Desc_Singular";
    }
    if (key == DEVPKEY_DeviceContainer_Category_Desc_Plural)
    {
        return "DEVPKEY_DeviceContainer_Category_Desc_Plural";
    }
    if (key == DEVPKEY_DeviceContainer_Category_Icon)
    {
        return "DEVPKEY_DeviceContainer_Category_Icon";
    }
    if (key == DEVPKEY_DeviceContainer_CategoryGroup_Desc)
    {
        return "DEVPKEY_DeviceContainer_CategoryGroup_Desc";
    }
    if (key == DEVPKEY_DeviceContainer_CategoryGroup_Icon)
    {
        return "DEVPKEY_DeviceContainer_CategoryGroup_Icon";
    }
    if (key == DEVPKEY_DeviceContainer_PrimaryCategory)
    {
        return "DEVPKEY_DeviceContainer_PrimaryCategory";
    }
    if (key == DEVPKEY_DeviceContainer_UnpairUninstall)
    {
        return "DEVPKEY_DeviceContainer_UnpairUninstall, DEVPKEY_DeviceDisplay_UnpairUninstall";
    }
    if (key == DEVPKEY_DeviceContainer_RequiresUninstallElevation)
    {
        return "DEVPKEY_DeviceContainer_RequiresUninstallElevation, DEVPKEY_DeviceDisplay_RequiresUninstallElevation";
    }
    if (key == DEVPKEY_DeviceContainer_DeviceFunctionSubRank)
    {
        return "DEVPKEY_DeviceContainer_DeviceFunctionSubRank";
    }
    if (key == DEVPKEY_DeviceContainer_AlwaysShowDeviceAsConnected)
    {
        return "DEVPKEY_DeviceContainer_AlwaysShowDeviceAsConnected, DEVPKEY_DeviceDisplay_AlwaysShowDeviceAsConnected";
    }
    if (key == DEVPKEY_DeviceContainer_ConfigFlags)
    {
        return "DEVPKEY_DeviceContainer_ConfigFlags";
    }
    if (key == DEVPKEY_DeviceContainer_PrivilegedPackageFamilyNames)
    {
        return "DEVPKEY_DeviceContainer_PrivilegedPackageFamilyNames";
    }
    if (key == DEVPKEY_DeviceContainer_CustomPrivilegedPackageFamilyNames)
    {
        return "DEVPKEY_DeviceContainer_CustomPrivilegedPackageFamilyNames";
    }
    if (key == DEVPKEY_DeviceContainer_IsRebootRequired)
    {
        return "DEVPKEY_DeviceContainer_IsRebootRequired";
    }
    if (key == DEVPKEY_DeviceContainer_FriendlyName)
    {
        return "DEVPKEY_DeviceContainer_FriendlyName";
    }
    if (key == DEVPKEY_DeviceContainer_Manufacturer)
    {
        return "DEVPKEY_DeviceContainer_Manufacturer";
    }
    if (key == DEVPKEY_DeviceContainer_ModelName)
    {
        return "DEVPKEY_DeviceContainer_ModelName";
    }
    if (key == DEVPKEY_DeviceContainer_ModelNumber)
    {
        return "DEVPKEY_DeviceContainer_ModelNumber";
    }
    if (key == DEVPKEY_DeviceContainer_InstallInProgress)
    {
        return "DEVPKEY_DeviceContainer_InstallInProgress";
    }
    else
    {
        return {};
    }
}

void dumpDevNode(DEVINST devInst, std::ostream& os, Indent indent)
{
    ULONG status;
    ULONG problemNumber;
    auto r = CM_Get_DevNode_Status(&status,
        &problemNumber,
        devInst,
        0);
    if (r == CR_SUCCESS)
    {
        auto statusList = getStatusList(status);
        for (auto s : statusList)
        {
            os << indent << s << std::endl;
        }
        // os << StringHelper::fromList(statusList, ";") << std::endl;
        if (status & DN_HAS_PROBLEM)
        {
            auto problem = getProblem(problemNumber);
            os << indent << problem << std::endl;
        }
    }
    else
    {
        auto k = GetLastError();
        os << indent << "CM_Get_DevNode_status failed, returned: " << r
            << ", GetLastError returned " << k << std::endl;
    }

    ULONG depth;
    r = CM_Get_Depth(&depth, devInst, 0);
    if (r == CR_SUCCESS)
    {
        os << indent << "Depth: " << depth << std::endl;
    }
    else
    {
        os << indent << "CM_Get_Depth failed, returned: " << r << std::endl;
    }

    ULONG keysCount = 0;
    r = CM_Get_DevNode_Property_Keys(
        devInst,
        NULL,
        &keysCount,
        0);
    if (r == CR_SUCCESS)
    {

    }
    else if (r == CR_BUFFER_SMALL)
    {
        // os << indent << "CM_Get_DevNode_Property_Keys returned buffer small" << std::endl;
    }
    else
    {
        os << "CM_Get_DevNode_Property_Keys failed, returned " << r << std::endl;
    }

    auto keysArray = new DEVPROPKEY[keysCount];
    r = CM_Get_DevNode_Property_Keys(
        devInst,
        keysArray,
        &keysCount,
        0);
    if (r == CR_SUCCESS)
    {
        for (ULONG i = 0; i < keysCount; i++)
        {
            auto key = keysArray[i];
            DEVPROPTYPE type;
            ULONG bufferSize = 0;
            r = CM_Get_DevNode_PropertyW(
                devInst,
                &key,
                &type,
                NULL,
                &bufferSize,
                0);
            if (r == CR_SUCCESS)
            {

            }
            else if (r == CR_BUFFER_SMALL)
            {
                // os << indent << "CM_Get_DevNode_PropertyW"
                //     << " return buffer small"
                //     << std::endl;
            }
            else
            {
                os << indent << "CM_Get_DevNode_PropertyW"
                    " failed, returned " << r << std::endl;
            }

            auto buffer = reinterpret_cast<PBYTE>(malloc(bufferSize));
            r = CM_Get_DevNode_PropertyW(
                devInst,
                &key,
                &type,
                buffer,
                &bufferSize,
                0);
            if (r == CR_SUCCESS)
            {
                wchar_t keyStr[256] = {0};
                auto l = StringFromGUID2(
                    key.fmtid,
                    keyStr,
                    256);
                auto ks = fromWCharArray(keyStr);
                os << indent << ks << "." << key.pid;
                auto name = getKnownKeyName(key);
                if (!name.empty())
                {
                    os << " (" << name << ")";
                }
                os << std::endl;
                if (type == DEVPROP_TYPE_STRING)
                {
                    auto value = reinterpret_cast<wchar_t*>(buffer);
                    auto v = fromWCharArray(value);
                    os << indent << v << std::endl;
                }
                else if (type == DEVPROP_TYPE_UINT32)
                {
                    auto value = reinterpret_cast<uint32_t*>(buffer);
                    os << indent << *value << std::endl;
                }
                else if (type == DEVPROP_TYPE_FILETIME)
                {
                    auto value = reinterpret_cast<FILETIME*>(buffer);
                    SYSTEMTIME stUTC, stLocal;
                    auto ok = FileTimeToSystemTime(value, &stUTC);
                    if (ok)
                    {
                        ok = SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
                    }
                    if (ok)
                    {
                        os << indent << std::setfill('0')
                            << std::setw(4) << stLocal.wYear << "-"
                            << std::setw(2) << stLocal.wMonth << "-"
                            << std::setw(2) << stLocal.wDay << " "
                            << std::setw(2) << stLocal.wHour << ":"
                            << std::setw(2) << stLocal.wMinute << ":"
                            << std::setw(2) << stLocal.wSecond << "."
                            << std::setw(3) << stLocal.wMilliseconds
                            << std::endl;
                    }
                    else
                    {
                        os << indent << "Failed to convert File Time" << std::endl;
                    }
                }
                else if (type == DEVPROP_TYPE_BOOLEAN)
                {
                    auto value = reinterpret_cast<DEVPROP_BOOLEAN*>(buffer);
                    os << indent << ((*value) ? "TRUE" : "FALSE") << std::endl;
                }
                else if (type == DEVPROP_TYPE_GUID)
                {
                    auto value = reinterpret_cast<GUID*>(buffer);
                    wchar_t b[256] = {0};
                    auto lb = StringFromGUID2(*value, b, 256);
                    auto gs = fromWCharArray(b);
                    os << indent << gs << std::endl;
                }
                else if (type == DEVPROP_TYPE_SECURITY_DESCRIPTOR)
                {
                    // auto value = reinterpret_cast<SECURITY_DESCRIPTOR*>(buffer);
                    os << indent << "<<Security Descriptor>>" << std::endl;
                }
                else if (type & DEVPROP_TYPEMOD_ARRAY)
                {
                    os << indent << "<<Value is array>>" << std::endl;
                    type = type - DEVPROP_TYPEMOD_ARRAY;
                    if (type == DEVPROP_TYPE_BYTE)
                    {
                        auto value = reinterpret_cast<BYTE*>(buffer);
                        auto count = bufferSize / sizeof(BYTE);
                        for (size_t i = 0; i < count; i++)
                        {
                            os << indent << static_cast<int>(value[i]) << std::endl;
                        }
                    }
                    else
                    {
                        os << indent << "<<Unknown type of " << type << ">>" << std::endl;
                    }
                }
                else if (type & DEVPROP_TYPEMOD_LIST)
                {
                    os << indent << "<<Value is list>>" << std::endl;
                    type = type - DEVPROP_TYPEMOD_LIST;
                    if (type == DEVPROP_TYPE_STRING)
                    {
                        auto value = reinterpret_cast<wchar_t*>(buffer);
                        std::wstring temp;
                        auto count = bufferSize / sizeof(wchar_t);
                        for (size_t i = 0; i < count; i++)
                        {
                            auto c = value[i];
                            if (c == '\0')
                            {
                                if (temp.length() == 0)
                                {
                                    break;
                                }
                                os << indent << fromWCharArray(temp.c_str()) << std::endl;
                                temp.clear();
                            }
                            else
                            {
                                temp.push_back(c);
                            }
                        }
                    }
                }
                else
                {
                    os << indent << "Unknown type of " << type << std::endl;
                }
            }
            else
            {
                os << indent << "CM_Get_DevNode_PropertyW"
                    " failed, returned " << r << std::endl;
            }

            free(buffer);
        }
    }
    else
    {
        os << indent << "CM_Get_DevNode_Property_Keys failed, returned " << r << std::endl;
    }
    delete[] keysArray;

    // Dump Children
    {
        DEVINST child;
        r = CM_Get_Child(&child, devInst, 0);
        if (r == CR_SUCCESS)
        {
            indent++;
            dumpDevNode(child, os, indent);

            DEVINST sibling = child;
            while (true)
            {
                r = CM_Get_Sibling(&sibling, sibling, 0);
                if (r == CR_SUCCESS)
                {
                    dumpDevNode(sibling, os, indent);
                }
                else if (r == CR_NO_SUCH_DEVNODE)
                {
                    // End of Sibling
                    break;
                }
                else
                {
                    std::cout << "Failed to Get Sibling, returned " << r << std::endl;
                    break;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    std::string filePath = "device_tree.txt";
    if (argc > 1)
    {
        filePath = argv[1];
    }

    DEVINST devInst;
    auto r = CM_Locate_DevNodeA(&devInst,
        NULL,
        CM_LOCATE_DEVNODE_NORMAL);
    if (r == CR_SUCCESS)
    {
        std::ofstream out(filePath);
        dumpDevNode(devInst, out, Indent());
    }
    else
    {
        std::cout << "Failed to Locate Root Device Node" << std::endl;
    }

    return 0;
}
