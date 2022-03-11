#include "vless.hpp"

#include "BuiltinProtocolPlugin.hpp"

VlessOutboundEditor::VlessOutboundEditor(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
    setProperty("QV2RAY_INTERNAL_HAS_STREAMSETTINGS", true);
}

void VlessOutboundEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void VlessOutboundEditor::Load()
{
    vless.loadJson(settings);

    vless.id.ReadWriteBind(idLineEdit, "text", &QLineEdit::textEdited);
}
