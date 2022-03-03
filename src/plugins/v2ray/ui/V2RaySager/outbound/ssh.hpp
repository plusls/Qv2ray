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
    void Load() override;

    void Store() override
    {
        settings = IOProtocolSettings{ ssh.toJson() };
    }

  protected:
    void changeEvent(QEvent *e) override;

  private slots:
    void on_textHostKeyAlgorithms_textChanged();

  private:
    Qv2ray::Models::SSHClientObject ssh;
};
