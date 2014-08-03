
  #SET(CMAKE_AUTOMOC ON)
  #SET(CMAKE_AUTOUIC ON)

#add_definitions(-DQT_PLUGIN)
#add_definitions(-DQT_NO_DEBUG)
#add_definitions(-DQT_SHARED)
#add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

INCLUDE_DIRECTORIES( ui include ../widgets ${QWT_INCLUDE_DIRS} )
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

  ## Seismoview
  SET(
    seismoview_CUSTOM_WIDGETS
    mainwindow
    about
    segycolormap
  )
  PROCESS_CUSTOM_WIDGETS( seismoview_CUSTOM_WIDGETS seismoview ui )

  QT5_WRAP_UI(UI ${seismoview_UI})
  QT5_WRAP_CPP(MOC ${seismoview_HEADERS})

  SET(
    seismoview_HEADERS
    ${seismoview_HEADERS}
    include/TraceBuffer.h
  )

  ADD_EXECUTABLE(
    seismoview.x
    seismoview.cpp
    ${seismoview_SOURCES}
    ${seismoview_HEADERS}
    ${seismoview_UI}
    ${UI}
    ${MOC}
  )
  TARGET_LINK_LIBRARIES( seismoview.x seismic_widgets ${QWT_LIBRARIES}/libqwt.so Qt5::Widgets SeismicTraces )
