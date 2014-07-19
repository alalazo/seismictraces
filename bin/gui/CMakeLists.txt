OPTION(
  BUILD_QT_BASED_GUI_APPLICATIONS
  "If ON builds the Qt based GUI applications shipped with the package"
  OFF
)
IF( BUILD_QT_BASED_GUI_APPLICATIONS )

  SET(CMAKE_AUTOMOC ON)
  SET(CMAKE_AUTOUIC ON)
  FIND_PACKAGE( Qt5 REQUIRED COMPONENTS Widgets Core )

  ## Seismoview
  SET(CMAKE_INCLUDE_CURRENT_DIR ON)
  SET(
    seismoview_SOURCES
    seismoview.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
  )
  ADD_EXECUTABLE(
    seismoview.x
    ${seismoview_SOURCES}
  )
  TARGET_LINK_LIBRARIES( seismoview.x Qt5::Widgets )

ENDIF()
