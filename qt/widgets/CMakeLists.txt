### SeismicWidgets
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES( ${QWT_INCLUDE_DIRS} )

SET(
    seismic_widgets_CUSTOM_WIDGETS
    BinaryFileHeaderViewer
    TracePlot
    SegySpectrogram
)

PROCESS_CUSTOM_WIDGETS( seismic_widgets_CUSTOM_WIDGETS seismic_widgets . )
QT5_WRAP_UI( UI ${seismic_widgets_UI})
QT5_WRAP_CPP( MOC ${seismic_widgets_HEADERS})

SET(
    seismic_widgets_HEADERS
    ${seismic_widgets_HEADERS}
    TraceBuffer.h
)

ADD_LIBRARY(
    seismic_widgets
    ${seismic_widgets_HEADERS}
    ${seismic_widgets_SOURCES}
    ${seismic_widgets_UI}
    ${UI}
    ${MOC}
)
TARGET_LINK_LIBRARIES( seismic_widgets Qt5::Widgets )

INSTALL(FILES ${seismic_widgets_HEADERS} DESTINATION include/widget)
INSTALL(TARGETS seismic_widgets DESTINATION lib)

#  ## SeismicWidgets designer plugin
#  SET(
#    swdp_SOURCES
#    widget/seismic_widgets_designer_plugin.h
#    widget/seismic_widgets_designer_plugin.cpp
#  )
#  ADD_LIBRARY( seismic_widgets_designer_plugin ${swdp_SOURCES} )
#  TARGET_LINK_LIBRARIES( seismic_widgets_designer_plugin seismic_widgets Qt5::Designer )
#  INSTALL(
#    TARGETS seismic_widgets_designer_plugin
#    DESTINATION lib/designer
#  )

  
