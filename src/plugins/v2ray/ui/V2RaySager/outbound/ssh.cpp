#include "ssh.hpp"

SSHOutboundEditor::SSHOutboundEditor(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
    setProperty("QV2RAY_INTERNAL_HAS_STREAMSETTINGS", true);
    ssh.user.ReadWriteBind(textUser, "text", &QLineEdit::textEdited);
    ssh.password.ReadWriteBind(textPassword, "text", &QLineEdit::textEdited);
    ssh.privateKey.ReadWriteBind(textPrivateKey, "plainText", &QPlainTextEdit::textChanged);
    ssh.publicKey.ReadWriteBind(textPublicKey, "text", &QLineEdit::textEdited);
    ssh.clientVersion.ReadWriteBind(textClientVersion, "text", &QLineEdit::textEdited);
    ssh.userLevel.ReadWriteBind(spinBoxUserLevel, "value", &QSpinBox::valueChanged);
}

void SSHOutboundEditor::Load()
{
    ssh.loadJson(settings);
    textHostKeyAlgorithms->setPlainText(ssh.hostKeyAlgorithms->join(u"\n"_qs));
}

void SSHOutboundEditor::changeEvent(QEvent *e)
{

    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void SSHOutboundEditor::on_textHostKeyAlgorithms_textChanged()
{
    ssh.hostKeyAlgorithms = textHostKeyAlgorithms->toPlainText().split(QRegularExpression{ u"[\r\n]"_qs }, Qt::SkipEmptyParts);
}