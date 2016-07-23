#ifndef __XINDA_REMOTE_H
#define __XINDA_REMOTE_H

enum IrXindaRemoteCode
{
    ircUnknown  = 0,
    ircOk       = 0xFF02FD,
    ircUp       = 0xFF629D,
    ircDown     = 0xFFA857,
    ircLeft     = 0xFF22DD,
    ircRight    = 0xFFC23D,
    irc0        = 0xFF4AB5,
    irc1        = 0xFF6897,
    irc2        = 0xFF9867,
    irc3        = 0xFFB04F,
    irc4        = 0xFF30CF,
    irc5        = 0xFF18E7,
    irc6        = 0xFF7A85,
    irc7        = 0xFF10EF,
    irc8        = 0xFF38C7,
    irc9        = 0xFF5AA5,
    ircAsterisk = 0xFF42BD,
    ircSharp    = 0xFF52AD,
    ircLast = 0xFFFFFFFF  // Если кнопка удерживается
};

IrXindaRemoteCode getXindaCode(unsigned long value)
{
    switch (value)
    {
        case ircOk       :
        case ircUp       :
        case ircDown     :
        case ircLeft     :
        case ircRight    :
        case irc0        :
        case irc1        :
        case irc2        :
        case irc3        :
        case irc4        :
        case irc5        :
        case irc6        :
        case irc7        :
        case irc8        :
        case irc9        :
        case ircAsterisk :
        case ircSharp    :
        case ircLast     : return IrXindaRemoteCode(value);
        default: return ircUnknown;
    }
}

#endif // __XINDA_REMOTE_H

