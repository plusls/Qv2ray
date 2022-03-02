#include "shadowsocks.hpp"

ShadowsocksOutboundEditor::ShadowsocksOutboundEditor(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
    setProperty("QV2RAY_INTERNAL_HAS_STREAMSETTINGS", true);
    shadowsocks.method.ReadWriteBind(ss_encryptionMethod, "currentText", &QComboBox::currentTextChanged);
    shadowsocks.password.ReadWriteBind(ss_passwordTxt, "text", &QLineEdit::textEdited);
    shadowsocks.plugin.ReadWriteBind(ss_pluginTxt, "text", &QLineEdit::textEdited);
    shadowsocks.pluginOpts.ReadWriteBind(ss_pluginOptsTxt, "text", &QLineEdit::textEdited);
    //connect(ipListTxt, &AutoCompleteTextEdit::textChanged, [&]() { (*dns.servers)[currentServerIndex].expectIPs = SplitLines(ipListTxt->toPlainText()); });
}

void ShadowsocksOutboundEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}
