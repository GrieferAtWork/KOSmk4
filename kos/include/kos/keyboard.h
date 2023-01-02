/* Copyright (c) 2019-2023 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_KEYBOARD_H
#define _KOS_KEYBOARD_H 1

/* Keyboard key modifier masks. */
#define KEYMOD_LCTRL      0x0001 /* KEY_LCTRL */
#define KEYMOD_RCTRL      0x0002 /* KEY_RCTRL */
#define KEYMOD_LSHIFT     0x0004 /* KEY_LSHIFT (flag is inverted when the caps-lock LED is enabled) */
#define KEYMOD_RSHIFT     0x0008 /* KEY_RSHIFT (flag is inverted when the caps-lock LED is enabled) */
#define KEYMOD_LGUI       0x0010 /* KEY_LGUI */
#define KEYMOD_RGUI       0x0020 /* KEY_RGUI */
#define KEYMOD_LALT       0x0040 /* KEY_LALT */
#define KEYMOD_RALT       0x0080 /* KEY_RALT */
#define KEYMOD_HELDMASK   0x00ff /* Mask key modifiers that must be held down */
#define KEYMOD_MAPMASK    0x04ff /* Mask of key modifiers used for translating keys to characters */
#define KEYMOD_SCROLLLOCK 0x0100 /* KEY_SCROLLLOCK */
#define KEYMOD_NUMLOCK    0x0200 /* KEY_NUMLOCK */
#define KEYMOD_CAPSLOCK   0x0400 /* KEY_CAPSLOCK */
/*      KEYMOD_           0xff00 */
#define KEYMOD_SHIFT     (KEYMOD_LSHIFT | KEYMOD_RSHIFT)
#define KEYMOD_CTRL      (KEYMOD_LCTRL | KEYMOD_RCTRL)
#define KEYMOD_GUI       (KEYMOD_LGUI | KEYMOD_RGUI)
#define KEYMOD_ALT       (KEYMOD_LALT | KEYMOD_RALT)
#define KEYMOD_MASK(x)      ((x) & KEYMOD_MAPMASK)
#define KEYMOD_ISNORMAL(x)      (KEYMOD_MASK(x) == 0)
/* Ctrl+Shift: 1 Control key + 1 Shift key (ignoring lock modifiers) */
#define KEYMOD_ISCTRL_SHIFT(x)  (KEYMOD_MASK(x) == (KEYMOD_LCTRL|KEYMOD_RSHIFT) || \
                                 KEYMOD_MASK(x) == (KEYMOD_RCTRL|KEYMOD_RSHIFT) || \
                                 KEYMOD_MASK(x) == (KEYMOD_LCTRL|KEYMOD_LSHIFT) || \
                                 KEYMOD_MASK(x) == (KEYMOD_RCTRL|KEYMOD_LSHIFT))
#define KEYMOD_ISCTRL(x)        (((x) & KEYMOD_CTRL) && !((x) & (KEYMOD_HELDMASK & ~KEYMOD_CTRL)))
#define KEYMOD_ISCTRL_ALT(x)    (((x) & KEYMOD_CTRL) != 0 && ((x) & KEYMOD_ALT) != 0 && ((x) & (KEYMOD_HELDMASK & ~(KEYMOD_CTRL|KEYMOD_ALT))) == 0)
#define KEYMOD_ISSHIFT(x)      ((((x) & KEYMOD_SHIFT) && !((x) & (KEYMOD_MAPMASK & ~KEYMOD_SHIFT))) || \
                                 ((x) & KEYMOD_MAPMASK) == KEYMOD_CAPSLOCK)
#define KEYMOD_ISGUI(x)         (((x) & KEYMOD_GUI) && !((x) & (KEYMOD_HELDMASK & ~KEYMOD_GUI)))
#define KEYMOD_ISALT(x)         (((x) & KEYMOD_ALT) && !((x) & (KEYMOD_HELDMASK & ~KEYMOD_ALT)))
/* AltGR: Either RALT alone, or a 1 ALT key, alongside 1 CTRL key */
#define KEYMOD_ISALTGR(x)       (((x) & KEYMOD_HELDMASK) == KEYMOD_RALT || \
                                 ((x) & KEYMOD_HELDMASK) == (KEYMOD_RALT|KEYMOD_LCTRL) || \
                                 ((x) & KEYMOD_HELDMASK) == (KEYMOD_RALT|KEYMOD_RCTRL) || \
                                 ((x) & KEYMOD_HELDMASK) == (KEYMOD_LALT|KEYMOD_LCTRL) || \
                                 ((x) & KEYMOD_HELDMASK) == (KEYMOD_LALT|KEYMOD_RCTRL))
#define KEYMOD_HASCTRL(x)       (((x) & KEYMOD_CTRL) != 0)
#define KEYMOD_HASCTRL_SHIFT(x) (((x) & (KEYMOD_CTRL|KEYMOD_SHIFT)) == (KEYMOD_LCTRL|KEYMOD_RSHIFT) || \
                                 ((x) & (KEYMOD_CTRL|KEYMOD_SHIFT)) == (KEYMOD_RCTRL|KEYMOD_RSHIFT) || \
                                 ((x) & (KEYMOD_CTRL|KEYMOD_SHIFT)) == (KEYMOD_LCTRL|KEYMOD_LSHIFT) || \
                                 ((x) & (KEYMOD_CTRL|KEYMOD_SHIFT)) == (KEYMOD_RCTRL|KEYMOD_LSHIFT))
#define KEYMOD_HASSHIFT(x)     ((((x) & KEYMOD_SHIFT) != 0) ^ (((x) & KEYMOD_CAPSLOCK) != 0))
#define KEYMOD_HASGUI(x)        (((x) & KEYMOD_GUI) != 0)
#define KEYMOD_HASALT(x)        (((x) & KEYMOD_ALT) != 0)
#define KEYMOD_HASALTGR(x)      (((x) & (KEYMOD_ALT|KEYMOD_CTRL)) == KEYMOD_RALT || \
                                 ((x) & (KEYMOD_ALT|KEYMOD_CTRL)) == (KEYMOD_RALT|KEYMOD_LCTRL) || \
                                 ((x) & (KEYMOD_ALT|KEYMOD_CTRL)) == (KEYMOD_RALT|KEYMOD_RCTRL) || \
                                 ((x) & (KEYMOD_ALT|KEYMOD_CTRL)) == (KEYMOD_LALT|KEYMOD_LCTRL) || \
                                 ((x) & (KEYMOD_ALT|KEYMOD_CTRL)) == (KEYMOD_LALT|KEYMOD_RCTRL))




#define KEY_FREPEAT      0x4000 /* FLAG: The  key  is  being  repeated  periodically,
                                 *       because the user is holding down the button.
                                 * WARNING: This flag may not be supported by all drivers! */
#define KEY_FRELEASED    0x8000 /* FLAG: The key was released. */
#define KEY_FMASK        0xc000 /* MASK: Key state flags. */
#define KEY_KMASK        0x3fff /* MASK: Key code. */
#define KEY_ISUP(k)     ((k) & KEY_FRELEASED)
#define KEY_ISDOWN(k) (!((k) & KEY_FRELEASED))
#define KEYCODE(k)      ((k) & KEY_KMASK)
#define KEYUP(k)        ((k) | KEY_FRELEASED)
#define KEYDOWN(k)       (k)

#define KEYBOARD_COL_BITS 5
#define KEYBOARD_ROW_BITS 3
#define KEY_GETROW(key) ((key) >> KEYBOARD_COL_BITS)
#define KEY_GETCOL(key) ((key) & ((1 << KEYBOARD_COL_BITS) - 1))
#define KEY(r, c)       (((r) << KEYBOARD_COL_BITS) | c)



/* NOTE: Key codes and names match those used by linux, where they
 *       can be  found  in  /usr/include/linux/input-event-codes.h */

#define KEY_NONE     0 /* No key (used internally). */
#define KEY_RESERVED 0 /* Reserved key code (never produced) */

#define KEY_ESC                      1
#define KEY_1                        2
#define KEY_2                        3
#define KEY_3                        4
#define KEY_4                        5
#define KEY_5                        6
#define KEY_6                        7
#define KEY_7                        8
#define KEY_8                        9
#define KEY_9                        10
#define KEY_0                        11
#define KEY_MINUS                    12
#define KEY_EQUAL                    13
#define KEY_BACKSPACE                14
#define KEY_TAB                      15
#define KEY_Q                        16
#define KEY_W                        17
#define KEY_E                        18
#define KEY_R                        19
#define KEY_T                        20
#define KEY_Y                        21
#define KEY_U                        22
#define KEY_I                        23
#define KEY_O                        24
#define KEY_P                        25
#define KEY_LEFTBRACE                26
#define KEY_RIGHTBRACE               27
#define KEY_ENTER                    28
#define KEY_LEFTCTRL                 29
#define KEY_A                        30
#define KEY_S                        31
#define KEY_D                        32
#define KEY_F                        33
#define KEY_G                        34
#define KEY_H                        35
#define KEY_J                        36
#define KEY_K                        37
#define KEY_L                        38
#define KEY_SEMICOLON                39
#define KEY_APOSTROPHE               40
#define KEY_GRAVE                    41
#define KEY_LEFTSHIFT                42
#define KEY_BACKSLASH                43
#define KEY_Z                        44
#define KEY_X                        45
#define KEY_C                        46
#define KEY_V                        47
#define KEY_B                        48
#define KEY_N                        49
#define KEY_M                        50
#define KEY_COMMA                    51
#define KEY_DOT                      52
#define KEY_SLASH                    53
#define KEY_RIGHTSHIFT               54
#define KEY_KPASTERISK               55
#define KEY_LEFTALT                  56
#define KEY_SPACE                    57
#define KEY_CAPSLOCK                 58
#define KEY_F1                       59
#define KEY_F2                       60
#define KEY_F3                       61
#define KEY_F4                       62
#define KEY_F5                       63
#define KEY_F6                       64
#define KEY_F7                       65
#define KEY_F8                       66
#define KEY_F9                       67
#define KEY_F10                      68
#define KEY_NUMLOCK                  69
#define KEY_SCROLLLOCK               70
#define KEY_KP7                      71
#define KEY_KP8                      72
#define KEY_KP9                      73
#define KEY_KPMINUS                  74
#define KEY_KP4                      75
#define KEY_KP5                      76
#define KEY_KP6                      77
#define KEY_KPPLUS                   78
#define KEY_KP1                      79
#define KEY_KP2                      80
#define KEY_KP3                      81
#define KEY_KP0                      82
#define KEY_KPDOT                    83
#define KEY_ZENKAKUHANKAKU           85
#define KEY_102ND                    86
#define KEY_F11                      87
#define KEY_F12                      88
#define KEY_RO                       89
#define KEY_KATAKANA                 90
#define KEY_HIRAGANA                 91
#define KEY_HENKAN                   92
#define KEY_KATAKANAHIRAGANA         93
#define KEY_MUHENKAN                 94
#define KEY_KPJPCOMMA                95
#define KEY_KPENTER                  96
#define KEY_RIGHTCTRL                97
#define KEY_KPSLASH                  98
#define KEY_SYSRQ                    99
#define KEY_RIGHTALT                 100
#define KEY_LINEFEED                 101
#define KEY_HOME                     102
#define KEY_UP                       103
#define KEY_PAGEUP                   104
#define KEY_LEFT                     105
#define KEY_RIGHT                    106
#define KEY_END                      107
#define KEY_DOWN                     108
#define KEY_PAGEDOWN                 109
#define KEY_INSERT                   110
#define KEY_DELETE                   111 /* aka: Del, Erase, Entf */
#define KEY_MACRO                    112
#define KEY_MUTE                     113
#define KEY_VOLUMEDOWN               114
#define KEY_VOLUMEUP                 115
#define KEY_POWER                    116 /* SC System Power Down */
#define KEY_KPEQUAL                  117
#define KEY_KPPLUSMINUS              118
#define KEY_PAUSE                    119
#define KEY_SCALE                    120 /* AL Compiz Scale (Expose) */
#define KEY_KPCOMMA                  121
#define KEY_HANGEUL                  122
#define KEY_HANGUEL                  KEY_HANGEUL
#define KEY_HANJA                    123
#define KEY_YEN                      124
#define KEY_LEFTMETA                 125
#define KEY_RIGHTMETA                126
#define KEY_COMPOSE                  127
#define KEY_STOP                     128 /* AC Stop */
#define KEY_AGAIN                    129
#define KEY_PROPS                    130 /* AC Properties */
#define KEY_UNDO                     131 /* AC Undo */
#define KEY_FRONT                    132
#define KEY_COPY                     133 /* AC Copy */
#define KEY_OPEN                     134 /* AC Open */
#define KEY_PASTE                    135 /* AC Paste */
#define KEY_FIND                     136 /* AC Search */
#define KEY_CUT                      137 /* AC Cut */
#define KEY_HELP                     138 /* AL Integrated Help Center */
#define KEY_MENU                     139 /* Menu (show menu) */
#define KEY_CALC                     140 /* AL Calculator */
#define KEY_SETUP                    141
#define KEY_SLEEP                    142 /* SC System Sleep */
#define KEY_WAKEUP                   143 /* System Wake Up */
#define KEY_FILE                     144 /* AL Local Machine Browser */
#define KEY_SENDFILE                 145
#define KEY_DELETEFILE               146
#define KEY_XFER                     147
#define KEY_PROG1                    148
#define KEY_PROG2                    149
#define KEY_WWW                      150 /* AL Internet Browser */
#define KEY_MSDOS                    151
#define KEY_COFFEE                   152 /* AL Terminal Lock/Screensaver */
#define KEY_SCREENLOCK               KEY_COFFEE
#define KEY_ROTATE_DISPLAY           153 /* Display orientation for e.g. tablets */
#define KEY_DIRECTION                KEY_ROTATE_DISPLAY
#define KEY_CYCLEWINDOWS             154
#define KEY_MAIL                     155
#define KEY_BOOKMARKS                156 /* AC Bookmarks */
#define KEY_COMPUTER                 157
#define KEY_BACK                     158 /* AC Back */
#define KEY_FORWARD                  159 /* AC Forward */
#define KEY_CLOSECD                  160
#define KEY_EJECTCD                  161
#define KEY_EJECTCLOSECD             162
#define KEY_NEXTSONG                 163
#define KEY_PLAYPAUSE                164
#define KEY_PREVIOUSSONG             165
#define KEY_STOPCD                   166
#define KEY_RECORD                   167
#define KEY_REWIND                   168
#define KEY_PHONE                    169 /* Media Select Telephone */
#define KEY_ISO                      170
#define KEY_CONFIG                   171 /* AL Consumer Control Configuration */
#define KEY_HOMEPAGE                 172 /* AC Home */
#define KEY_REFRESH                  173 /* AC Refresh */
#define KEY_EXIT                     174 /* AC Exit */
#define KEY_MOVE                     175
#define KEY_EDIT                     176
#define KEY_SCROLLUP                 177
#define KEY_SCROLLDOWN               178
#define KEY_KPLEFTPAREN              179
#define KEY_KPRIGHTPAREN             180
#define KEY_NEW                      181 /* AC New */
#define KEY_REDO                     182 /* AC Redo/Repeat */
#define KEY_F13                      183
#define KEY_F14                      184
#define KEY_F15                      185
#define KEY_F16                      186
#define KEY_F17                      187
#define KEY_F18                      188
#define KEY_F19                      189
#define KEY_F20                      190
#define KEY_F21                      191
#define KEY_F22                      192
#define KEY_F23                      193
#define KEY_F24                      194
#define KEY_PLAYCD                   200
#define KEY_PAUSECD                  201
#define KEY_PROG3                    202
#define KEY_PROG4                    203
#define KEY_DASHBOARD                204 /* AL Dashboard */
#define KEY_SUSPEND                  205
#define KEY_CLOSE                    206 /* AC Close */
#define KEY_PLAY                     207
#define KEY_FASTFORWARD              208
#define KEY_BASSBOOST                209
#define KEY_PRINT                    210 /* AC Print */
#define KEY_HP                       211
#define KEY_CAMERA                   212
#define KEY_SOUND                    213
#define KEY_QUESTION                 214
#define KEY_EMAIL                    215
#define KEY_CHAT                     216
#define KEY_SEARCH                   217
#define KEY_CONNECT                  218
#define KEY_FINANCE                  219 /* AL Checkbook/Finance */
#define KEY_SPORT                    220
#define KEY_SHOP                     221
#define KEY_ALTERASE                 222
#define KEY_CANCEL                   223 /* AC Cancel */
#define KEY_BRIGHTNESSDOWN           224
#define KEY_BRIGHTNESSUP             225
#define KEY_MEDIA                    226
#define KEY_SWITCHVIDEOMODE          227 /* Cycle between available video outputs (Monitor/LCD/TV-out/etc) */
#define KEY_KBDILLUMTOGGLE           228
#define KEY_KBDILLUMDOWN             229
#define KEY_KBDILLUMUP               230
#define KEY_SEND                     231 /* AC Send */
#define KEY_REPLY                    232 /* AC Reply */
#define KEY_FORWARDMAIL              233 /* AC Forward Msg */
#define KEY_SAVE                     234 /* AC Save */
#define KEY_DOCUMENTS                235
#define KEY_BATTERY                  236
#define KEY_BLUETOOTH                237
#define KEY_WLAN                     238
#define KEY_UWB                      239
#define KEY_UNKNOWN                  240 /* Unknown key press. */
#define KEY_VIDEO_NEXT               241 /* drive next video source */
#define KEY_VIDEO_PREV               242 /* drive previous video source */
#define KEY_BRIGHTNESS_CYCLE         243 /* brightness up, after max is min */
#define KEY_BRIGHTNESS_AUTO          244 /* Set Auto Brightness: manual brightness control is off, rely on ambient */
#define KEY_BRIGHTNESS_ZERO          KEY_BRIGHTNESS_AUTO
#define KEY_DISPLAY_OFF              245 /* display device to off state */
#define KEY_WWAN                     246 /* Wireless WAN (LTE, UMTS, GSM, etc.) */
#define KEY_WIMAX                    KEY_WWAN
#define KEY_RFKILL                   247 /* Key that controls all radios */
#define KEY_MICMUTE                  248 /* Mute / unmute the microphone */
#define BTN_MISC                     0x100
#define BTN_0                        0x100
#define BTN_1                        0x101
#define BTN_2                        0x102
#define BTN_3                        0x103
#define BTN_4                        0x104
#define BTN_5                        0x105
#define BTN_6                        0x106
#define BTN_7                        0x107
#define BTN_8                        0x108
#define BTN_9                        0x109
#define BTN_MOUSE                    0x110
#define BTN_LEFT                     0x110
#define BTN_RIGHT                    0x111
#define BTN_MIDDLE                   0x112
#define BTN_SIDE                     0x113
#define BTN_EXTRA                    0x114
#define BTN_FORWARD                  0x115
#define BTN_BACK                     0x116
#define BTN_TASK                     0x117
#define BTN_JOYSTICK                 0x120
#define BTN_TRIGGER                  0x120
#define BTN_THUMB                    0x121
#define BTN_THUMB2                   0x122
#define BTN_TOP                      0x123
#define BTN_TOP2                     0x124
#define BTN_PINKIE                   0x125
#define BTN_BASE                     0x126
#define BTN_BASE2                    0x127
#define BTN_BASE3                    0x128
#define BTN_BASE4                    0x129
#define BTN_BASE5                    0x12a
#define BTN_BASE6                    0x12b
#define BTN_DEAD                     0x12f
#define BTN_GAMEPAD                  0x130
#define BTN_SOUTH                    0x130
#define BTN_A                        BTN_SOUTH
#define BTN_EAST                     0x131
#define BTN_B                        BTN_EAST
#define BTN_C                        0x132
#define BTN_NORTH                    0x133
#define BTN_X                        BTN_NORTH
#define BTN_WEST                     0x134
#define BTN_Y                        BTN_WEST
#define BTN_Z                        0x135
#define BTN_TL                       0x136
#define BTN_TR                       0x137
#define BTN_TL2                      0x138
#define BTN_TR2                      0x139
#define BTN_SELECT                   0x13a
#define BTN_START                    0x13b
#define BTN_MODE                     0x13c
#define BTN_THUMBL                   0x13d
#define BTN_THUMBR                   0x13e
#define BTN_DIGI                     0x140
#define BTN_TOOL_PEN                 0x140
#define BTN_TOOL_RUBBER              0x141
#define BTN_TOOL_BRUSH               0x142
#define BTN_TOOL_PENCIL              0x143
#define BTN_TOOL_AIRBRUSH            0x144
#define BTN_TOOL_FINGER              0x145
#define BTN_TOOL_MOUSE               0x146
#define BTN_TOOL_LENS                0x147
#define BTN_TOOL_QUINTTAP            0x148 /* Five fingers on trackpad */
#define BTN_TOUCH                    0x14a
#define BTN_STYLUS                   0x14b
#define BTN_STYLUS2                  0x14c
#define BTN_TOOL_DOUBLETAP           0x14d
#define BTN_TOOL_TRIPLETAP           0x14e
#define BTN_TOOL_QUADTAP             0x14f /* Four fingers on trackpad */
#define BTN_WHEEL                    0x150
#define BTN_GEAR_DOWN                0x150
#define BTN_GEAR_UP                  0x151
#define KEY_OK                       0x160
#define KEY_SELECT                   0x161
#define KEY_GOTO                     0x162
#define KEY_CLEAR                    0x163
#define KEY_POWER2                   0x164
#define KEY_OPTION                   0x165
#define KEY_INFO                     0x166 /* AL OEM Features/Tips/Tutorial */
#define KEY_TIME                     0x167
#define KEY_VENDOR                   0x168
#define KEY_ARCHIVE                  0x169
#define KEY_PROGRAM                  0x16a /* Media Select Program Guide */
#define KEY_CHANNEL                  0x16b
#define KEY_FAVORITES                0x16c
#define KEY_EPG                      0x16d
#define KEY_PVR                      0x16e /* Media Select Home */
#define KEY_MHP                      0x16f
#define KEY_LANGUAGE                 0x170
#define KEY_TITLE                    0x171
#define KEY_SUBTITLE                 0x172
#define KEY_ANGLE                    0x173
#define KEY_ZOOM                     0x174
#define KEY_MODE                     0x175
#define KEY_KEYBOARD                 0x176
#define KEY_SCREEN                   0x177
#define KEY_PC                       0x178 /* Media Select Computer */
#define KEY_TV                       0x179 /* Media Select TV */
#define KEY_TV2                      0x17a /* Media Select Cable */
#define KEY_VCR                      0x17b /* Media Select VCR */
#define KEY_VCR2                     0x17c /* VCR Plus */
#define KEY_SAT                      0x17d /* Media Select Satellite */
#define KEY_SAT2                     0x17e
#define KEY_CD                       0x17f /* Media Select CD */
#define KEY_TAPE                     0x180 /* Media Select Tape */
#define KEY_RADIO                    0x181
#define KEY_TUNER                    0x182 /* Media Select Tuner */
#define KEY_PLAYER                   0x183
#define KEY_TEXT                     0x184
#define KEY_DVD                      0x185 /* Media Select DVD */
#define KEY_AUX                      0x186
#define KEY_MP3                      0x187
#define KEY_AUDIO                    0x188 /* AL Audio Browser */
#define KEY_VIDEO                    0x189 /* AL Movie Browser */
#define KEY_DIRECTORY                0x18a
#define KEY_LIST                     0x18b
#define KEY_MEMO                     0x18c /* Media Select Messages */
#define KEY_CALENDAR                 0x18d
#define KEY_RED                      0x18e
#define KEY_GREEN                    0x18f
#define KEY_YELLOW                   0x190
#define KEY_BLUE                     0x191
#define KEY_CHANNELUP                0x192 /* Channel Increment */
#define KEY_CHANNELDOWN              0x193 /* Channel Decrement */
#define KEY_FIRST                    0x194
#define KEY_LAST                     0x195 /* Recall Last */
#define KEY_AB                       0x196
#define KEY_NEXT                     0x197
#define KEY_RESTART                  0x198
#define KEY_SLOW                     0x199
#define KEY_SHUFFLE                  0x19a
#define KEY_BREAK                    0x19b
#define KEY_PREVIOUS                 0x19c /* aka: Prior */
#define KEY_DIGITS                   0x19d
#define KEY_TEEN                     0x19e
#define KEY_TWEN                     0x19f
#define KEY_VIDEOPHONE               0x1a0 /* Media Select Video Phone */
#define KEY_GAMES                    0x1a1 /* Media Select Games */
#define KEY_ZOOMIN                   0x1a2 /* AC Zoom In */
#define KEY_ZOOMOUT                  0x1a3 /* AC Zoom Out */
#define KEY_ZOOMRESET                0x1a4 /* AC Zoom */
#define KEY_WORDPROCESSOR            0x1a5 /* AL Word Processor */
#define KEY_EDITOR                   0x1a6 /* AL Text Editor */
#define KEY_SPREADSHEET              0x1a7 /* AL Spreadsheet */
#define KEY_GRAPHICSEDITOR           0x1a8 /* AL Graphics Editor */
#define KEY_PRESENTATION             0x1a9 /* AL Presentation App */
#define KEY_DATABASE                 0x1aa /* AL Database App */
#define KEY_NEWS                     0x1ab /* AL Newsreader */
#define KEY_VOICEMAIL                0x1ac /* AL Voicemail */
#define KEY_ADDRESSBOOK              0x1ad /* AL Contacts/Address Book */
#define KEY_MESSENGER                0x1ae /* AL Instant Messaging */
#define KEY_DISPLAYTOGGLE            0x1af /* Turn display (LCD) on and off */
#define KEY_BRIGHTNESS_TOGGLE        KEY_DISPLAYTOGGLE
#define KEY_SPELLCHECK               0x1b0 /* AL Spell Check */
#define KEY_LOGOFF                   0x1b1 /* AL Logoff */
#define KEY_DOLLAR                   0x1b2
#define KEY_EURO                     0x1b3
#define KEY_FRAMEBACK                0x1b4 /* Consumer - transport controls */
#define KEY_FRAMEFORWARD             0x1b5
#define KEY_CONTEXT_MENU             0x1b6 /* GenDesc - system context menu */
#define KEY_MEDIA_REPEAT             0x1b7 /* Consumer - transport control */
#define KEY_10CHANNELSUP             0x1b8 /* 10 channels up (10+) */
#define KEY_10CHANNELSDOWN           0x1b9 /* 10 channels down (10-) */
#define KEY_IMAGES                   0x1ba /* AL Image Browser */
#define KEY_DEL_EOL                  0x1c0
#define KEY_DEL_EOS                  0x1c1
#define KEY_INS_LINE                 0x1c2
#define KEY_DEL_LINE                 0x1c3
#define KEY_FN                       0x1d0
#define KEY_FN_ESC                   0x1d1
#define KEY_FN_F1                    0x1d2
#define KEY_FN_F2                    0x1d3
#define KEY_FN_F3                    0x1d4
#define KEY_FN_F4                    0x1d5
#define KEY_FN_F5                    0x1d6
#define KEY_FN_F6                    0x1d7
#define KEY_FN_F7                    0x1d8
#define KEY_FN_F8                    0x1d9
#define KEY_FN_F9                    0x1da
#define KEY_FN_F10                   0x1db
#define KEY_FN_F11                   0x1dc
#define KEY_FN_F12                   0x1dd
#define KEY_FN_1                     0x1de
#define KEY_FN_2                     0x1df
#define KEY_FN_D                     0x1e0
#define KEY_FN_E                     0x1e1
#define KEY_FN_F                     0x1e2
#define KEY_FN_S                     0x1e3
#define KEY_FN_B                     0x1e4
#define KEY_BRL_DOT1                 0x1f1
#define KEY_BRL_DOT2                 0x1f2
#define KEY_BRL_DOT3                 0x1f3
#define KEY_BRL_DOT4                 0x1f4
#define KEY_BRL_DOT5                 0x1f5
#define KEY_BRL_DOT6                 0x1f6
#define KEY_BRL_DOT7                 0x1f7
#define KEY_BRL_DOT8                 0x1f8
#define KEY_BRL_DOT9                 0x1f9
#define KEY_BRL_DOT10                0x1fa
#define KEY_NUMERIC_0                0x200 /* used by phones, remote controls, */
#define KEY_NUMERIC_1                0x201 /* and other keypads */
#define KEY_NUMERIC_2                0x202
#define KEY_NUMERIC_3                0x203
#define KEY_NUMERIC_4                0x204
#define KEY_NUMERIC_5                0x205
#define KEY_NUMERIC_6                0x206
#define KEY_NUMERIC_7                0x207
#define KEY_NUMERIC_8                0x208
#define KEY_NUMERIC_9                0x209
#define KEY_NUMERIC_STAR             0x20a
#define KEY_NUMERIC_POUND            0x20b
#define KEY_NUMERIC_A                0x20c /* Phone key A - HUT Telephony 0xb9 */
#define KEY_NUMERIC_B                0x20d
#define KEY_NUMERIC_C                0x20e
#define KEY_NUMERIC_D                0x20f
#define KEY_CAMERA_FOCUS             0x210
#define KEY_WPS_BUTTON               0x211 /* WiFi Protected Setup key */
#define KEY_TOUCHPAD_TOGGLE          0x212 /* Request switch touchpad on or off */
#define KEY_TOUCHPAD_ON              0x213
#define KEY_TOUCHPAD_OFF             0x214
#define KEY_CAMERA_ZOOMIN            0x215
#define KEY_CAMERA_ZOOMOUT           0x216
#define KEY_CAMERA_UP                0x217
#define KEY_CAMERA_DOWN              0x218
#define KEY_CAMERA_LEFT              0x219
#define KEY_CAMERA_RIGHT             0x21a
#define KEY_ATTENDANT_ON             0x21b
#define KEY_ATTENDANT_OFF            0x21c
#define KEY_ATTENDANT_TOGGLE         0x21d /* Attendant call on or off */
#define KEY_LIGHTS_TOGGLE            0x21e /* Reading light on or off */
#define BTN_DPAD_UP                  0x220
#define BTN_DPAD_DOWN                0x221
#define BTN_DPAD_LEFT                0x222
#define BTN_DPAD_RIGHT               0x223
#define KEY_ALS_TOGGLE               0x230 /* Ambient light sensor */
#define KEY_BUTTONCONFIG             0x240 /* AL Button Configuration */
#define KEY_TASKMANAGER              0x241 /* AL Task/Project Manager */
#define KEY_JOURNAL                  0x242 /* AL Log/Journal/Timecard */
#define KEY_CONTROLPANEL             0x243 /* AL Control Panel */
#define KEY_APPSELECT                0x244 /* AL Select Task/Application */
#define KEY_SCREENSAVER              0x245 /* AL Screen Saver */
#define KEY_VOICECOMMAND             0x246 /* Listening Voice Command */
#define KEY_BRIGHTNESS_MIN           0x250 /* Set Brightness to Minimum */
#define KEY_BRIGHTNESS_MAX           0x251 /* Set Brightness to Maximum */
#define KEY_KBDINPUTASSIST_PREV      0x260
#define KEY_KBDINPUTASSIST_NEXT      0x261
#define KEY_KBDINPUTASSIST_PREVGROUP 0x262
#define KEY_KBDINPUTASSIST_NEXTGROUP 0x263
#define KEY_KBDINPUTASSIST_ACCEPT    0x264
#define KEY_KBDINPUTASSIST_CANCEL    0x265
#define BTN_TRIGGER_HAPPY            0x2c0
#define BTN_TRIGGER_HAPPY1           0x2c0
#define BTN_TRIGGER_HAPPY2           0x2c1
#define BTN_TRIGGER_HAPPY3           0x2c2
#define BTN_TRIGGER_HAPPY4           0x2c3
#define BTN_TRIGGER_HAPPY5           0x2c4
#define BTN_TRIGGER_HAPPY6           0x2c5
#define BTN_TRIGGER_HAPPY7           0x2c6
#define BTN_TRIGGER_HAPPY8           0x2c7
#define BTN_TRIGGER_HAPPY9           0x2c8
#define BTN_TRIGGER_HAPPY10          0x2c9
#define BTN_TRIGGER_HAPPY11          0x2ca
#define BTN_TRIGGER_HAPPY12          0x2cb
#define BTN_TRIGGER_HAPPY13          0x2cc
#define BTN_TRIGGER_HAPPY14          0x2cd
#define BTN_TRIGGER_HAPPY15          0x2ce
#define BTN_TRIGGER_HAPPY16          0x2cf
#define BTN_TRIGGER_HAPPY17          0x2d0
#define BTN_TRIGGER_HAPPY18          0x2d1
#define BTN_TRIGGER_HAPPY19          0x2d2
#define BTN_TRIGGER_HAPPY20          0x2d3
#define BTN_TRIGGER_HAPPY21          0x2d4
#define BTN_TRIGGER_HAPPY22          0x2d5
#define BTN_TRIGGER_HAPPY23          0x2d6
#define BTN_TRIGGER_HAPPY24          0x2d7
#define BTN_TRIGGER_HAPPY25          0x2d8
#define BTN_TRIGGER_HAPPY26          0x2d9
#define BTN_TRIGGER_HAPPY27          0x2da
#define BTN_TRIGGER_HAPPY28          0x2db
#define BTN_TRIGGER_HAPPY29          0x2dc
#define BTN_TRIGGER_HAPPY30          0x2dd
#define BTN_TRIGGER_HAPPY31          0x2de
#define BTN_TRIGGER_HAPPY32          0x2df
#define BTN_TRIGGER_HAPPY33          0x2e0
#define BTN_TRIGGER_HAPPY34          0x2e1
#define BTN_TRIGGER_HAPPY35          0x2e2
#define BTN_TRIGGER_HAPPY36          0x2e3
#define BTN_TRIGGER_HAPPY37          0x2e4
#define BTN_TRIGGER_HAPPY38          0x2e5
#define BTN_TRIGGER_HAPPY39          0x2e6
#define BTN_TRIGGER_HAPPY40          0x2e7
/* We avoid low common keys in module aliases so they don't get huge. */
#define KEY_MIN_INTERESTING KEY_MUTE
#define KEY_MAX 0x2ff
#define KEY_CNT (KEY_MAX + 1)



#if 1 /* Backwards compatibility with KOS's old key names. */

#define KEY_EQUALS KEY_EQUAL

/* Special multi-media keys */
#define KEY_VOLUME_DOWN       KEY_VOLUMEDOWN
#define KEY_VOLUME_UP         KEY_VOLUMEUP
#define KEY_VOLUME_MUTE       KEY_MUTE
#define KEY_MM_PREVIOUS_TRACK KEY_PREVIOUSSONG
#define KEY_MM_NEXT_TRACK     KEY_NEXTSONG
#define KEY_MM_PLAY_PAUSE     KEY_PLAYPAUSE
#define KEY_MM_STOP           KEY_STOPCD /* ??? */
#define KEY_MM_SELECT         KEY_MEDIA

#define KEY_MY_COMPUTER       KEY_COMPUTER
#define KEY_MEDIA_PLAYER      KEY_PLAYER
#define KEY_EMAIL_CLIENT      KEY_MAIL
#define KEY_CALCULATOR        KEY_CALC
#define KEY_WWW_SEARCH        KEY_SEARCH
#define KEY_WWW_FAVORITES     KEY_BOOKMARKS
#define KEY_WWW_REFRESH       KEY_REFRESH
#define KEY_WWW_STOP          KEY_STOP
#define KEY_WWW_FORWARD       KEY_FORWARD
#define KEY_WWW_BACK          KEY_BACK
#define KEY_WWW_HOME          KEY_HOMEPAGE

/* Special APIC (power-control) keys */
#define KEY_APIC_POWER  KEY_POWER
#define KEY_APIC_SLEEP  KEY_SLEEP
#define KEY_APIC_WAKE   KEY_WAKEUP

#define KEY_PRINTSCREEN  KEY_SYSRQ
#define KEY_PGUP         KEY_PAGEUP
#define KEY_PGDOWN       KEY_PAGEDOWN
#define KEY_BACKTICK     KEY_GRAVE /* ` (back tick) */
#define KEY_GRAVE_ACCENT KEY_GRAVE
#define KEY_LBRACKET     KEY_LEFTBRACE
#define KEY_RBRACKET     KEY_RIGHTBRACE
#define KEY_SINGLEQUOTE  KEY_APOSTROPHE /* ' (single quote) */
#define KEY_NUMBERSIGN   KEY_BACKSLASH /* # (European keyboards have this located here...) */
#define KEY_LSHIFT       KEY_LEFTSHIFT
#define KEY_LESS         KEY_102ND /* <, >, | */
#define KEY_RSHIFT       KEY_RIGHTSHIFT


#define KEY_LCTRL       KEY_LEFTCTRL
#define KEY_LGUI        KEY_LEFTMETA
#define KEY_LALT        KEY_LEFTALT
#define KEY_RALT        KEY_RIGHTALT
#define KEY_RGUI        KEY_RIGHTMETA
#define KEY_APPS        KEY_MENU
#define KEY_RCTRL       KEY_RIGHTCTRL
#define KEY_ALTGR       KEY_RIGHTALT
#define KEY_LMETA       KEY_LEFTMETA
#define KEY_RMETA       KEY_RIGHTMETA

/* Keypad keys. */
#define KEY_KP_NUMLOCK  KEY_NUMLOCK
#define KEY_KP_SLASH    KEY_KPSLASH
#define KEY_KP_STAR     KEY_KPASTERISK
#define KEY_KP_MINUS    KEY_KPMINUS
#define KEY_KP_7        KEY_KP7
#define KEY_KP_8        KEY_KP8
#define KEY_KP_9        KEY_KP9
#define KEY_KP_PLUS     KEY_KPPLUS
#define KEY_KP_4        KEY_KP4
#define KEY_KP_5        KEY_KP5
#define KEY_KP_6        KEY_KP6
#define KEY_KP_1        KEY_KP1
#define KEY_KP_2        KEY_KP2
#define KEY_KP_3        KEY_KP3
#define KEY_KP_ENTER    KEY_KPENTER
#define KEY_KP_0        KEY_KP0
#define KEY_KP_DOT      KEY_KPDOT
#define KEY_KP_DIVIDE   KEY_KPSLASH
#define KEY_KP_MULTIPLY KEY_KPASTERISK
#define KEY_KP_SUBTRACT KEY_KPMINUS
#define KEY_KP_ADD      KEY_KPPLUS
#define KEY_KP_DECIMAL  KEY_KPDOT
#define KEY_KP_COMMA    KEY_KPDOT
#endif


#endif /* !_KOS_KEYBOARD_H */
