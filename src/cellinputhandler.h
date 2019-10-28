#ifndef CELLINPUTHANDLER_H
#define CELLINPUTHANDLER_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>

class Cell;
class QMouseEvent;

class CellInputHandler : public QObject
{
    Q_OBJECT

public:
    explicit CellInputHandler(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void handleMouseButtonPressEvents(QObject *watched, QEvent *event);
    void handleMouseButtonReleaseEvents(QObject *watched, QEvent *event);
    void handleMouseMoveEvents(QEvent *event);

    void cellMoveInsideHandle(Cell *cell, QMouseEvent *mouseEvent);
    void cellMoveOutsideHandle(Cell *cell, QMouseEvent *mouseEvent);

    Cell *mLastCell;
};

#endif // CELLINPUTHANDLER_H
