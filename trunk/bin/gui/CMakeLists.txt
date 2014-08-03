OPTION(
  BUILD_QT_BASED_GUI_APPLICATIONS
  "If ON builds the Qt based GUI applications shipped with the package"
  OFF
)

FUNCTION(PROCESS_CUSTOM_WIDGETS widget_list prefix directory )
  FOREACH( widget ${${widget_list}} )
    SET( _${prefix}_SOURCES ${_${prefix}_SOURCES} "${directory}/${widget}.cpp" )
    SET( _${prefix}_HEADERS ${_${prefix}_HEADERS} "${directory}/${widget}.h" )
    SET( _${prefix}_UI ${_${prefix}_UI} "${directory}/${widget}.ui" )
  ENDFOREACH()
  SET( ${prefix}_SOURCES ${_${prefix}_SOURCES} PARENT_SCOPE )
  SET( ${prefix}_HEADERS ${_${prefix}_HEADERS} PARENT_SCOPE )
  SET( ${prefix}_UI ${_${prefix}_UI} PARENT_SCOPE )
ENDFUNCTION( )

IF( BUILD_QT_BASED_GUI_APPLICATIONS )

  #SET(CMAKE_AUTOMOC ON)
  #SET(CMAKE_AUTOUIC ON)
  FIND_PACKAGE( Qt5 REQUIRED COMPONENTS Designer Widgets Core )
  FIND_PACKAGE( Qwt REQUIRED )

add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

  INCLUDE_DIRECTORIES( ui include ${QWT_INCLUDE_DIRS} )
  SET(CMAKE_INCLUDE_CURRENT_DIR ON)

  ## SeismicWidgets
  SET(
    seismic_widgets_CUSTOM_WIDGETS
    trace_plot
  )
  PROCESS_CUSTOM_WIDGETS( seismic_widgets_CUSTOM_WIDGETS seismic_widgets widget )
  QT5_WRAP_UI(swUI ${seismic_widgets_UI})
  QT5_WRAP_CPP(swMOC ${seismic_widgets_HEADERS})  
  ADD_LIBRARY(
    seismic_widgets
    ${seismic_widgets_HEADERS}
    ${seismic_widgets_SOURCES}
    ${seismic_widgets_UI}
    ${swUI}
    ${swMOC}
  )
  TARGET_LINK_LIBRARIES( seismic_widgets Qt5::Widgets )
  INSTALL(
    FILES ${seismic_widgets_HEADERS}
    DESTINATION include/widget
  )

  INSTALL(
    TARGETS seismic_widgets
    DESTINATION lib
  )

  ## SeismicWidgets designer plugin
  SET(
    swdp_SOURCES
    widget/seismic_widgets_designer_plugin.h
    widget/seismic_widgets_designer_plugin.cpp
  )
  ADD_LIBRARY( seismic_widgets_designer_plugin ${swdp_SOURCES} )
  TARGET_LINK_LIBRARIES( seismic_widgets_designer_plugin seismic_widgets Qt5::Designer )
  INSTALL(
    TARGETS seismic_widgets_designer_plugin
    DESTINATION lib/designer
  )

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

ENDIF()
