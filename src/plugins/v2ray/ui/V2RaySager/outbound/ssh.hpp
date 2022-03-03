#pragma once

#include "CoreModels.hpp"
#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui_ssh.h"

class SSHOutboundEditor
    : public Qv2rayPlugin::Gui::PluginProtocolEditor
    , private Ui::SSHOutEditor
{
    Q_OBJECT

  public:
    explicit SSHOutboundEditor(QWidget *parent = nullptr);

  public:
    void Load() override
    {
        ssh.loadJson(settings);
    }

    void Store() override
    {
        settings = IOProtocolSettings{ ssh.toJson() };
    }

  protected:
    void changeEvent(QEvent *e) override;

  private:
    Qv2ray::Models::SSHClientObject ssh;
};
