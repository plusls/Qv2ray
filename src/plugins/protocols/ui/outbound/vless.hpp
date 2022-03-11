#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "V2RayModels.hpp"
#include "ui_vless.h"

class VlessOutboundEditor
    : public Qv2rayPlugin::Gui::PluginProtocolEditor
    , private Ui::vlessOutEditor
{
    Q_OBJECT

  public:
    explicit VlessOutboundEditor(QWidget *parent = nullptr);

    void Load() override;
    void Store() override
    {
        settings = IOProtocolSettings{ vless.toJson() };
    }

  private:
    Qv2ray::Models::VlessClientObject vless;

  protected:
    void changeEvent(QEvent *e) override;
};
