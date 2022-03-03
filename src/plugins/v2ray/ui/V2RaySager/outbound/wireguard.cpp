#include "wireguard.hpp"

WireGuardOutboundEditor::WireGuardOutboundEditor(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
    setProperty("QV2RAY_INTERNAL_HAS_STREAMSETTINGS", true);
    wireguard.peerPublicKey.ReadWriteBind(textPeerPublicKey, "text", &QLineEdit::textEdited);
    wireguard.preSharedKey.ReadWriteBind(textPreSharedKey, "text", &QLineEdit::textEdited);
    wireguard.privateKey.ReadWriteBind(textPrivateKey, "text", &QLineEdit::textEdited);
    wireguard.mtu.ReadWriteBind(spinBoxMtu, "value", &QSpinBox::valueChanged);

}

void WireGuardOutboundEditor::Load()
{
    wireguard.loadJson(settings);
    textLocalAddresses->setPlainText(wireguard.localAddresses->join(u"\n"_qs));
}

void WireGuardOutboundEditor::changeEvent(QEvent *e)
{

    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void WireGuardOutboundEditor::on_textLocalAddresses_textChanged()
{
    wireguard.localAddresses = textLocalAddresses->toPlainText().split(QRegularExpression{ u"[\r\n]"_qs }, Qt::SkipEmptyParts);
}