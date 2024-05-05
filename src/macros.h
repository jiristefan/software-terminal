#ifndef MACROS_H
#define MACROS_H

#define APP_ORGANIZATION "CVUT FEL"
#define APP_NAME "Serial-UDP-TCP Terminal"

#define FONT_MONOSPACE "Courier New"

#define COLOR_RECEIVED_DATA Qt::red
#define COLOR_SENT_DATA Qt::black

#define REGEX_MESSAGE "(?<![$])([$]{1}(\\d|[A-F]|[a-f]){2})"
#define REGEX_MESSAGE_HEX "([^0-9a-fA-F])"

#define STYLESHEET_DEFAULT ""
#define STYLESHEET_RED "QLineEdit{background: rgb(255, 205, 205);}"
#define STYLESHEET_BLUE "QLineEdit{background: rgb(205, 205, 255);}"
#define STYLESHEET_GRAY "QLineEdit{background: rgb(235, 235, 235);}"

// Numbers
#define MESSAGE_HEIGHT 29                  // pixels (do not change)
#define INT_FILE_SYNC_TIME 50              // ms
#define INT_GUI_SYNC_TIME 50               // ms
#define INT_MAX_CONSOLE_CHARACTERS 2000    // characters
#define INT_MIN_TIMER_VALUE 0              // ms
#define INT_MAX_TIMER_VALUE 10000          // ms
#define INT_DEFAULT_TIMER_VALUE 10         // ms
#define INT_MAX_MESSAGE_CHARACTERS 500     // characters
#define INT_MAX_STATUS_FILE_CHARACTERS 20  // characters

// Icons
#define ICON_MESSAGE "://img/messages.png"
#define ICON_FILE "://img/files.png"
#define ICON_LIST "://img/list.png"
#define ICON_DELETE "://img/delete.png"
#define ICON_SELECTED "://img/selected.png"
#define ICON_NOT_SELECTED "://img/not_selected.png"
#define ICON_LED_OFF "://img/led_off.png"
#define ICON_LED_WAITING "://img/led_waiting.png"
#define ICON_LED_ON "://img/led_on.png"

// Default settings
#define DEFAULT_GEOMETRY QRect(QPoint(200, 200), QSize(0, 0))

#define DEFAULT_MAINWINDOW_TAB 0

#define DEFAULT_SERIAL_PORT ""
#define DEFAULT_SERIAL_BAUD "115200"
#define DEFAULT_SERIAL_DATASIZE "8"
#define DEFAULT_SERIAL_PARITY "None"

#define DEFAULT_UDP_MAIN_ADDRESS ""
#define DEFAULT_UDP_MAIN_PORT ""
#define DEFAULT_UDP_LOCAL_PORT ""

#define DEFAULT_TCP_CLIENT_ADDRESS ""
#define DEFAULT_TCP_CLIENT_PORT ""

#define DEFAULT_TCP_SERVER_PORT ""

// Setting keys
#define SETTING_MAINWINDOW "mainwindow"
#define SETTING_SERIAL "serial"
#define SETTING_UDP "UDP"
#define SETTING_TCP_CLIENT "TCP_client"
#define SETTING_TCP_SERVER "TCP_server"

#define SETTING_GEOMETRY "geometry"
#define SETTING_TAB "tab"

#define SETTING_COM "COM"
#define SETTING_BAUD "baud"
#define SETTING_DATASIZE "datasize"
#define SETTING_PARITY "parity"
#define SETTING_ADDRESS "address"
#define SETTING_PORT "port"
#define SETTING_LOCAL_PORT "localport"

#define SETTING_MESSAGE_LIST "message/list"
#define SETTING_MESSAGE_GEOMETRY "message/geometry"

#define SETTING_FILE "file/settings"
#define SETTING_FILE_GEOMETRY "file/geometry"

#define SETTING_ADDRESS_LIST "address/settings"
#define SETTING_ADDRESS_GEOMETRY "address/geometry"

#define SETTING_CONSOLE "console"

#endif // MACROS_H
