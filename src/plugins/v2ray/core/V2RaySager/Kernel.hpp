#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "QvPlugin/Handlers/KernelHandler.hpp"
#include "outbound/ssh.hpp"
#include "outbound/wireguard.hpp"

class QProcess;

namespace V2RayPluginNamespace
{
    class APIWorker;
}

const inline KernelId v2ray_sager_kernel_id{ u"v2ray_sager_kernel"_qs };

class V2RaySagerKernel : public Qv2rayPlugin::Kernel::PluginKernel
{
    Q_OBJECT
  public:
    V2RaySagerKernel();
    ~V2RaySagerKernel();

  public:
    virtual void SetConnectionSettings(const QMap<Qv2rayPlugin::Kernel::KernelOptionFlags, QVariant> &, const IOConnectionSettings &) override{};
    virtual void SetProfileContent(const ProfileContent &) override;
    virtual bool PrepareConfigurations() override;
    virtual void Start() override;
    virtual bool Stop() override;
    virtual KernelId GetKernelId() const override
    {
        return v2ray_sager_kernel_id;
    }
    static Qv2rayPlugin::Gui::Qv2rayGUIInterface::PluginEditorDescriptor GetOutboundEditors()
    {
        return {
            Qv2rayPlugin::Gui::Qv2rayGUIInterface::make_editor_info<SSHOutboundEditor>(u"ssh"_qs, u"SSH"_qs),
            Qv2rayPlugin::Gui::Qv2rayGUIInterface::make_editor_info<WireGuardOutboundEditor>(u"wireguard"_qs, u"WireGuard"_qs),
        };
    }

  signals:
    void OnCrashed(const QString &);
    void OnLog(const QString &);
    void OnStatsAvailable(StatisticsObject);

  private:
    std::optional<QString> ValidateConfig(const QString &path);

  private:
    ProfileContent profile;
    V2RayPluginNamespace::APIWorker *apiWorker;
    QProcess *vProcess;
    bool apiEnabled;
    bool kernelStarted = false;
    QMap<QString, QString> tagProtocolMap;
    QString configFilePath;
};
