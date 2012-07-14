#pragma once


const qint16 TELNET_HISTORY_LENGTH  = 4200;
const qint8 CSPYP1_PROTOCOL_ID      = 1;
const qint8 CSPYP1_PROTOCOL_VERSION = 3;
const qint8 CSPYP2_PROTOCOL_ID      = 1;
const qint8 CSPYP2_PROTOCOL_VERSION = 2;

const qint16 CMD1_CLIENT_INFO_SIZE = 92;    // Client info struct size

enum ProtocolMode
{
    MOD_TELNET   = 1,
    MOD_GRAPH    = 2,
    MOD_FILE     = 3,
    MOD_MEDIA    = 4,
    MOD_PROXY    = 5,
    MOD_REDIRECT = 6
};

enum Cspyp1Command
{
    CMD1_AUTH       = 1,
    CMD1_ADM        = 2,
    CMD1_LIST       = 3,
    CMD1_PING       = 4,
    CMD1_RLIST      = 5,
    CMD1_TRANSMIT   = 6,
    CMD1_DISCONNECT = 7
};

enum Cspyp2Command
{
    CMD2_LIST       = 1,
    CMD2_MODES      = 2,
    CMD2_ACTIVATE   = 3,
    CMD2_DEACTIVATE = 4,
    CMD2_TRANSMIT   = 5
};

enum FILE_MOD
{
    ROOT   =1,
    CD     =2,
    MKDIR  =3,
    RMDIR  =4,
    GET    =5,
    SEND   =6,
    FILE   =7,
    ABS_WAY=8

};
