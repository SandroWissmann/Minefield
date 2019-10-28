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
