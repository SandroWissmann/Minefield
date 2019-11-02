/* Minefield, free Minesweeper clone.
 * Copyright (C) 2019  Sandro Wißmann
 *
 * Minefield is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minefield is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Minefield. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/sandro4912/Minefield
 */

#include "cellinputhandler.h"

#include "cell.h"

#include <QApplication>
#include <QEvent>
#include <QMouseEvent>

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

    mLastCell = cell;
}

void CellInputHandler::handleMouseButtonReleaseEvents(
        QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    auto mouseEvent = static_cast<QMouseEvent*>(event);    
    auto widget = QApplication::widgetAt(mouseEvent->globalPos());
    auto cell = qobject_cast<Cell *>(widget);

    if(cell) {
        cell->handleMouseReleaseEvent(mouseEvent);
        mLastCell = cell;
    }
    else if(mLastCell) {
        mLastCell->handleMouseReleaseEvent(mouseEvent);
    }
}

void CellInputHandler::handleMouseMoveEvents(QEvent *event)
{
    auto mouseEvent = static_cast<QMouseEvent*>(event);

    if(mouseEvent->buttons().testFlag(Qt::LeftButton)) {
        auto widget = QApplication::widgetAt(mouseEvent->globalPos());

        if(widget) {
            auto cell = qobject_cast<Cell *>(widget);

            if(mLastCell && (!cell || cell != mLastCell)) {
                cellMoveOutsideHandle(mLastCell, mouseEvent);
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

