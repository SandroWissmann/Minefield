#include "cellinputhandler.h"

#include "cell.h"

#include <QApplication>
#include <QEvent>
#include <QMouseEvent>

#include <QDebug>

CellInputHandler::CellInputHandler(QObject *parent)
    : QObject{ parent },
      mLastCell{ nullptr }
{
}

bool CellInputHandler::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){       
       handleMouseButtonPressEvents(watched, event);
       return true;
    }
    if(event->type() == QEvent::MouseButtonRelease){      
        handleMouseButtonReleaseEvents(watched, event);
       return true;
    }
    if(event->type() == QEvent::MouseMove) {
        handleMouseMoveEvents(event);
        return true;
    }
    return false;
}

void CellInputHandler::handleMouseButtonPressEvents(
        QObject *watched, QEvent *event)
{
    auto mouseEvent = static_cast<QMouseEvent*>(event);
    auto cell = qobject_cast<Cell *>(watched);
    cell->handleMousePressEvent(mouseEvent);
}

void CellInputHandler::handleMouseButtonReleaseEvents(
        QObject *watched, QEvent *event)
{
    auto mouseEvent = static_cast<QMouseEvent*>(event);
    auto cell = qobject_cast<Cell *>(watched);
    QRect rect{ cell->mapToGlobal(QPoint(0, 0)), cell->size() };

    if(rect.contains(mouseEvent->globalPos())) {
       cell->handleMouseReleaseEvent(mouseEvent);
    }
    else {
        auto widget = QApplication::widgetAt(QCursor::pos());
        auto otherCell = static_cast<Cell *>(widget);
        if(otherCell) {
            otherCell->handleMouseReleaseEvent(mouseEvent);
        }
    }
}

void CellInputHandler::handleMouseMoveEvents(QEvent *event)
{
    auto mouseEvent = static_cast<QMouseEvent*>(event);

    if(mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        auto widget = QApplication::widgetAt(mouseEvent->globalPos());

        if(widget) {
            auto cell = qobject_cast<Cell *>(widget);

            if(!cell || cell != mLastCell) {
                if(mLastCell) {
                    cellMoveOutsideHandle(mLastCell, mouseEvent);
                }
            }
            if(!cell) {
                mLastCell = nullptr;
            }
            else if(cell != mLastCell) {
                cellMoveInsideHandle(cell, mouseEvent);
                mLastCell = cell;
            }
        }
    }
}

void CellInputHandler::cellMoveInsideHandle(
        Cell *cell, QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons().testFlag(Qt::RightButton)) {
        cell->handleMouseMoveEventInsideBothButtons(mouseEvent);
    }
    else {
        cell->handleMouseMoveEventInsideLeftButton(mouseEvent);
    }
}

void CellInputHandler::cellMoveOutsideHandle(
        Cell *cell, QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons().testFlag(Qt::RightButton)) {
        cell->handleMouseMoveEventOutsideBothButtons(mouseEvent);
    }
    else {
        cell->handleMouseMoveEventOutsideLeftButton(mouseEvent);
    }
}

