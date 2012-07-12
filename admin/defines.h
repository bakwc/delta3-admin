#pragma once

enum ProtocolMode
{
    MOD_TELNET=1,
    MOD_GRAPH=2,
    MOD_FILE=3,
    MOD_MEDIA=4,
    MOD_PROXY=5,
    MOD_REDIRECT=6
};

const qint16 TELNET_HISTORY_LENGTH=4200;
