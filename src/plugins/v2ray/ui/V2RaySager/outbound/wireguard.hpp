#pragma once

#include "CoreModels.hpp"
#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui_wireguard.h"

class WireGuardOutboundEditor
    : public Qv2rayPlugin::Gui::PluginProtocolEditor
    , private Ui::WireGuardOutEditor
{
    Q_OBJECT

  public:
    explicit WireGuardOutboundEditor(QWidget *parent = nullptr);

  public:
    void Load() override;

    void Store() override
    {
        settings = IOProtocolSettings{ wireguard.toJson() };
    }

  protected:
    void changeEvent(QEvent *e) override;

  private slots:
    void on_textLocalAddresses_textChanged();

  private:
    Qv2ray::Models::WireGuardObject wireguard;
};
