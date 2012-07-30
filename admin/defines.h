#pragma once

namespace delta3 {

const qint16 TELNET_HISTORY_LENGTH  = 4200;

const qint8 CSPYP1_PROTOCOL_ID      = 1;
const qint8 CSPYP1_PROTOCOL_VERSION = 3;
const qint8 CSPYP2_PROTOCOL_ID      = 1;
const qint8 CSPYP2_PROTOCOL_VERSION = 2;

const qint16 CMD1_CLIENT_INFO_SIZE = 92;    // Client info struct size

const int MOUSE_ACCURACY                  = 30000;

enum ProtocolMode
{
    MOD_TELNET   = 1,
    MOD_GRAPHICS = 2,
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
    CMD1_DISCONNECT = 7,
    CMD1_SETINFO = 8
};

enum Cspyp2Command
{
    CMD2_LIST       = 1,
    CMD2_MODES      = 2,
    CMD2_ACTIVATE   = 3,
    CMD2_DEACTIVATE = 4,
    CMD2_TRANSMIT   = 5
};

enum FileMode
{
    FMOD_ROOT   = 1,
    FMOD_CD     = 2,
    FMOD_MKDIR  = 3,
    FMOD_RMDIR  = 4,
    FMOD_GET    = 5,
    FMOD_SEND   = 6,
    FMOD_FILE   = 7,
    FMOD_ABS_WAY= 8
};

/*!
  \enum GraphicsMode

  Foo Bar Baz
*/
enum GraphicsMode
{
    GMOD_INFO       = 1, /* Команда передачи информации о администраторе */
    GMOD_IMGFULL    = 2, /* Команда приема полного изображения */
    GMOD_IMGDIFF    = 3, /* Команда приема разницы изображений */
    GMOD_KEYEV      = 4, /* Команда передачи события нажатии клавиши */
    GMOD_MMOV       = 5, /* Команда передачи сибытия перемещения мыши */
    GMOD_MCLICK     = 6  /* Команды передачи клика */
};

enum GMCLICK {
    GMCLICK_LEFT    = 1,
    GMCLICK_MIDDLE  = 2,
    GMCLICK_RIGHT   = 4,
    GMCLICK_DOWN    = 8,
    GMCLICK_UP      = 16,
    GMCLICK_CLICK   = 32,
    GMCLICK_DCLICK  = 64
};


}
