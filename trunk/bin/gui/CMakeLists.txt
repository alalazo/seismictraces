OPTION(
  BUILD_QT_BASED_GUI_APPLICATIONS
  "If ON builds the Qt based GUI applications shipped with the package"
  OFF
)
IF( BUILD_QT_BASED_GUI_APPLICATIONS )

  #SET(CMAKE_AUTOMOC ON)
  #SET(CMAKE_AUTOUIC ON)
  FIND_PACKAGE( Qt5 REQUIRED COMPONENTS Widgets Core )

  ## Seismoview
  INCLUDE_DIRECTORIES( ui )
  SET(CMAKE_INCLUDE_CURRENT_DIR ON)

  SET(
    seismoview_SOURCES
    seismoview.cpp
    ui/mainwindow.cpp
    ui/about.cpp
  )

  SET(
    seismoview_HEADERS
    ui/mainwindow.h
    ui/about.h
  )

  SET(
    seismoview_UI
    ui/mainwindow.ui
    ui/about.ui
  )

  QT5_WRAP_UI(UI ${seismoview_UI})
  QT5_WRAP_CPP(MOC ${seismoview_HEADERS})

  ADD_EXECUTABLE(
    seismoview.x
    ${seismoview_SOURCES}
    ${seismoview_HEADERS}
    ${seismoview_UI}
    ${UI}
    ${MOC}
  )
  TARGET_LINK_LIBRARIES( seismoview.x Qt5::Widgets )

ENDIF()
