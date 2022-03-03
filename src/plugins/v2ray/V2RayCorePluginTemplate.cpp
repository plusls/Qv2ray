#include "V2RayCorePluginTemplate.hpp"

#include "Kernel.hpp"
#include "ui/w_V2RayKernelSettings.hpp"

using namespace V2RayPluginNamespace;

const QvPluginMetadata V2RayCorePluginClass::GetMetadata() const
{
    return
    {
#if V2RayCoreType == CORETYPE_V2Ray
        u"V2Ray v4 Support"_qs, u"Moody"_qs, PluginId{ u"builtin_v2ray_support"_qs }, u"V2Ray kernel support"_qs,
#elif V2RayCoreType == CORETYPE_V2Ray5
        u"V2Ray v5 Support"_qs, u"Moody"_qs, PluginId{ u"builtin_v2ray5_support"_qs }, u"V2Ray v5 kernel support"_qs,
#elif V2RayCoreType == CORETYPE_V2RayGo
        u"V2Ray-Go Support"_qs, u"Moody"_qs, PluginId{ u"builtin_v2raygo_support"_qs }, u"V2Ray-Go kernel support"_qs,
#elif V2RayCoreType == CORETYPE_V2RaySager
        u"V2Ray Sager Support"_qs, u"Moody"_qs, PluginId{ u"builtin_sager_support"_qs }, u"V2Ray Sager kernel support"_qs,
#else
#error Unexpected
#endif
            u""_qs, { COMPONENT_KERNEL, COMPONENT_GUI },
    };
}

bool V2RayCorePluginClass::InitializePlugin()
{
    m_KernelInterface = std::make_shared<V2RayKernelInterface>();
    m_GUIInterface = new GuiInterface;
    return true;
}

void V2RayCorePluginClass::SettingsUpdated()
{
    settings.loadJson(m_Settings);
}

QList<KernelFactory> V2RayKernelInterface::PluginKernels() const
{
    QList<Qv2rayPlugin::Kernel::KernelFactory> factories;

#if V2RayCoreType == CORETYPE_V2Ray
    Qv2rayPlugin::Kernel::KernelFactory v2ray;
    v2ray.Capabilities.setFlag(Qv2rayPlugin::Kernel::KERNELCAP_ROUTER);
    v2ray.Id = v2ray_kernel_id;
    v2ray.Name = u"V2Ray"_qs;
    v2ray.Create = std::function{ []() { return std::make_unique<V2RayKernel>(); } };
    v2ray.SupportedProtocols << u"blackhole"_qs << u"dns"_qs << u"freedom"_qs     //
                             << u"http"_qs << u"loopback"_qs << u"shadowsocks"_qs //
                             << u"socks"_qs << u"trojan"_qs << u"vmess"_qs;
    factories << v2ray;
#endif

#if V2RayCoreType == CORETYPE_V2RayGo
    Qv2rayPlugin::Kernel::KernelFactory v2raygo;
    v2raygo.Capabilities.setFlag(Qv2rayPlugin::Kernel::KERNELCAP_ROUTER);
    v2raygo.Id = v2ray_go_kernel_id;
    v2raygo.Name = u"V2Ray Go"_qs;
    v2raygo.Create = std::function{ []() { return std::make_unique<V2RayGoKernel>(); } };
    v2raygo.SupportedProtocols << u"blackhole"_qs << u"dns"_qs << u"freedom"_qs     //
                               << u"http"_qs << u"loopback"_qs << u"shadowsocks"_qs //
                               << u"socks"_qs << u"trojan"_qs << u"vmess"_qs;
    factories << v2raygo;
#endif

#if V2RayCoreType == CORETYPE_V2Ray5
    Qv2rayPlugin::Kernel::KernelFactory v2ray5;
    v2ray5.Capabilities.setFlag(Qv2rayPlugin::Kernel::KERNELCAP_ROUTER);
    v2ray5.Id = v2ray_5_kernel_id;
    v2ray5.Name = u"V2Ray v5"_qs;
    v2ray5.Create = std::function{ []() { return std::make_unique<V2Ray5Kernel>(); } };
    v2ray5.SupportedProtocols << u"blackhole"_qs << u"dns"_qs << u"freedom"_qs     //
                              << u"http"_qs << u"loopback"_qs << u"shadowsocks"_qs //
                              << u"socks"_qs << u"trojan"_qs << u"vmess"_qs;
    factories << v2ray5;
#endif

#if V2RayCoreType == CORETYPE_V2RaySager
    Qv2rayPlugin::Kernel::KernelFactory v2raySager;
    v2raySager.Capabilities.setFlag(Qv2rayPlugin::Kernel::KERNELCAP_ROUTER);
    v2raySager.Id = v2ray_sager_kernel_id;
    v2raySager.Name = u"V2Ray Sager"_qs;
    v2raySager.Create = std::function{ []() { return std::make_unique<V2RaySagerKernel>(); } };
    v2raySager.SupportedProtocols << u"blackhole"_qs << u"dns"_qs << u"freedom"_qs     //
                                  << u"http"_qs << u"loopback"_qs << u"shadowsocks"_qs //
                                  << u"socks"_qs << u"trojan"_qs << u"vmess"_qs << u"ssh"_qs;
    factories << v2raySager;
#endif

    return factories;
}

QIcon GuiInterface::Icon() const
{
    return QIcon(u":/qv2ray.png"_qs);
}

QList<PLUGIN_GUI_COMPONENT_TYPE> GuiInterface::GetComponents() const
{
    return { GUI_COMPONENT_SETTINGS, GUI_COMPONENT_OUTBOUND_EDITOR };
}

std::unique_ptr<Gui::PluginSettingsWidget> GuiInterface::GetSettingsWidget() const
{
    return std::make_unique<V2RayKernelSettings>();
}

Gui::Qv2rayGUIInterface::PluginEditorDescriptor GuiInterface::GetInboundEditors() const
{
    return {};
}

Gui::Qv2rayGUIInterface::PluginEditorDescriptor GuiInterface::GetOutboundEditors() const
{
#if V2RayCoreType == CORETYPE_V2RaySager
    return V2RaySagerKernel::GetOutboundEditors();
#else
    return {};
#endif
}

std::unique_ptr<Gui::PluginMainWindowWidget> GuiInterface::GetMainWindowWidget() const
{
    return nullptr;
}
