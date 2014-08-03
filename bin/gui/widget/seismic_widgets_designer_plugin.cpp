#include <widget/seismic_widgets_designer_plugin.h>
#include <widget/trace_plot.h>

#include <QtPlugin>
TracePlotInterface::TracePlotInterface(QObject *parent) : QObject(parent) {
}

bool TracePlotInterface::isContainer() const {
    return false;
}

bool TracePlotInterface::isInitialized() const {
    return true;
}

QIcon TracePlotInterface::icon() const {
    return QIcon();
}

QString TracePlotInterface::domXml() const {
    QString domXml;
    domXml =
            "<widget class=\"trace_plot\" name=\"TracePlot\">\n"
            " <property name=\"geometry\">\n"
            "  <rect>\n"
            "   <x>0</x>\n"
            "   <y>0</y>\n"
            "   <width>400</width>\n"
            "   <height>200</height>\n"
            "  </rect>\n"
            " </property>\n"
            "</widget>\n";
    return domXml;
}

QString TracePlotInterface::group() const {
    return "Seismic widgets";
}

QString TracePlotInterface::includeFile() const {
    return "widget/trace_plot.h";
}

QString TracePlotInterface::name() const {
    return "trace_plot";
}

QString TracePlotInterface::toolTip() const {
    return "";
}

QString TracePlotInterface::whatsThis() const {
    return "";
}

QWidget * TracePlotInterface::createWidget(QWidget *parent) {
    return new trace_plot(parent);
}

