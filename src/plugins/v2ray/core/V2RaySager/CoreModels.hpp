#pragma once

#include "QvPlugin/Common/CommonTypes.hpp"
#include "QvPlugin/Utils/BindableProps.hpp"

namespace Qv2ray::Models
{
    struct SSHClientObject
    {
        Bindable<QString> user;
        Bindable<QString> password;
        Bindable<QString> privateKey;
        Bindable<QString> publicKey;
        Bindable<QString> clientVersion;
        Bindable<QStringList> hostKeyAlgorithms;
        QJS_JSON(P(user, password, privateKey, publicKey, clientVersion, hostKeyAlgorithms))
    };

}