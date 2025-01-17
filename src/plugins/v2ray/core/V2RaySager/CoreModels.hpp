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

    struct WireGuardObject
    {
        Bindable<QStringList> localAddresses;
        Bindable<QString> peerPublicKey;
        Bindable<QString> preSharedKey;
        Bindable<QString> privateKey;
        Bindable<int> mtu { 1420 };
        QJS_JSON(P(localAddresses, peerPublicKey, preSharedKey, privateKey, mtu))
    };
}