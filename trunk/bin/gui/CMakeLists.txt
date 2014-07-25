OPTION(
  BUILD_QT_BASED_GUI_APPLICATIONS
  "If ON builds the Qt based GUI applications shipped with the package"
  OFF
)

FUNCTION(PROCESS_CUSTOM_WIDGETS widget_list )
  FOREACH( widget ${${widget_list}} )
    SET( _seismoview_SOURCES ${_seismoview_SOURCES} "ui/${widget}.cpp" )
    SET( _seismoview_HEADERS ${_seismoview_HEADERS} "ui/${widget}.h" )
    SET( _seismoview_UI ${_seismoview_UI} "ui/${widget}.ui" )
  ENDFOREACH()
  SET( seismoview_SOURCES ${_seismoview_SOURCES} PARENT_SCOPE )
  SET( seismoview_HEADERS ${_seismoview_HEADERS} PARENT_SCOPE )
  SET( seismoview_UI ${_seismoview_UI} PARENT_SCOPE )
ENDFUNCTION( )

IF( BUILD_QT_BASED_GUI_APPLICATIONS )

  #SET(CMAKE_AUTOMOC ON)
  #SET(CMAKE_AUTOUIC ON)
  FIND_PACKAGE( Qt5 REQUIRED COMPONENTS Widgets Core )
  FIND_PACKAGE( Qwt REQUIRED )
  ## Seismoview
  INCLUDE_DIRECTORIES( ui ${QWT_INCLUDE_DIRS} )
  SET(CMAKE_INCLUDE_CURRENT_DIR ON)

  SET(
    seismoview_CUSTOM_WIDGETS
    mainwindow
    about
  )
  PROCESS_CUSTOM_WIDGETS( seismoview_CUSTOM_WIDGETS )

  QT5_WRAP_UI(UI ${seismoview_UI})
  QT5_WRAP_CPP(MOC ${seismoview_HEADERS})

  ADD_EXECUTABLE(
    seismoview.x
    seismoview.cpp
    ${seismoview_SOURCES}
    ${seismoview_HEADERS}
    ${seismoview_UI}
    ${UI}
    ${MOC}
  )
  TARGET_LINK_LIBRARIES( seismoview.x ${QWT_LIBRARIES}/libqwt.so Qt5::Widgets SeismicTraces )

ENDIF()
