#include "ssh.hpp"

SSHOutboundEditor::SSHOutboundEditor(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
    ssh.user.ReadWriteBind(textUser, "text", &QLineEdit::textEdited);
    ssh.password.ReadWriteBind(textPassword, "text", &QLineEdit::textEdited);
    ssh.privateKey.ReadWriteBind(textPrivateKey, "text", &QLineEdit::textEdited);
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
