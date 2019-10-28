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

#ifndef TESTMINEFIELD_H
#define TESTMINEFIELD_H

#include <QObject>

#include <QVector>

class Cell;

class TestMinefield : public QObject
{
    Q_OBJECT
private slots:

    void fieldWidth();

    void fieldHeight();

    void countOfMines();

    void minesLeft();

    void signal_uncoveredFirstCell();

    void signal_uncoveredEmptyCell();
    void signal_uncoveredAllSafeCells();

    void signal_pressedCell();
    void signal_releasedCell();

    void signal_mineExploded();
    void signal_minesLeftChanged();
};

QVector<Cell *> makeTestCells();

#endif // TESTMINEFIELD_H
