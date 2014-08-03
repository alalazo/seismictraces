#ifndef SEISMIC_WIDGETS_DESIGNER_PLUGIN_H
#define SEISMIC_WIDGETS_DESIGNER_PLUGIN_H

#include <QDesignerCustomWidgetInterface>
#include <QObject>

class TracePlotInterface : public QObject, public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_INTERFACES( QDesignerCustomWidgetInterface )
public:
    explicit TracePlotInterface( QObject* parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    //void initialize(QDesignerFormEditorInterface *core);
};


#endif // SEISMIC_WIDGETS_DESIGNER_PLUGIN_H
