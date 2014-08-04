OPTION(
  BUILD_QT_BASED_GUI_APPLICATIONS
  "If ON builds the Qt based GUI applications shipped with the package"
  OFF
)

IF( BUILD_QT_BASED_GUI_APPLICATIONS )

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

    ## Search for Qt related pckages
    FIND_PACKAGE( Qt5 REQUIRED COMPONENTS Designer Widgets Core )
    FIND_PACKAGE( Qwt REQUIRED )

    ADD_SUBDIRECTORY( widgets )
    ADD_SUBDIRECTORY( bin )

ENDIF()
