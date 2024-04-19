#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QObject>
#include <QQuickVTKRenderItem.h>

class ModelViewer : public QQuickVTKRenderItem {
  Q_OBJECT
public:
  explicit ModelViewer(QQuickItem *parent = nullptr);
};

#endif // MODELVIEWER_H
