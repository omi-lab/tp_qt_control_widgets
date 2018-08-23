TARGET = tdp_control_widgets
TEMPLATE = lib

QT += widgets gui

DEFINES += TDP_CONTROL_WIDGETS_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tdp_control_widgets/Globals.h

SOURCES += src/SelectChannelCombo.cpp
HEADERS += inc/tdp_control_widgets/SelectChannelCombo.h

SOURCES += src/SelectChannelComboAndButton.cpp
HEADERS += inc/tdp_control_widgets/SelectChannelComboAndButton.h

SOURCES += src/ToolBar.cpp
HEADERS += inc/tdp_control_widgets/ToolBar.h

