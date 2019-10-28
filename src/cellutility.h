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


#ifndef CELLUTILITY_H
#define CELLUTILITY_H

#include <QVector>

class Cell;

QVector<Cell* > createCells(int width, int height, int countOfMines);

void randomizeCells(QVector<Cell *> &cells);

void connectCellsWithNeighbourCells(
        QVector<Cell *> &cells, int fieldWidth, int fieldHeight);
void connectCellWithNeighbourCells(
        QVector<Cell *> &cells, int index, int fieldWidth, int fieldHeight);
int getMinesOfSourroundingCells(
        QVector<Cell *> &cells, int index, int fieldWidth, int fieldHeight);
QVector<int> getNeigbourIndexes(
        int index, int fieldWidth, int fieldHeight);

bool isFirstRow(int index, int fieldWidth);
bool isLastRow(int index, int fieldWidth, int fieldHeight);
bool isFirstElementOfRow(int index, int fieldWidth);
bool isLastElementOfRow(int index, int fieldWidth);
bool allSafeCellsUncovered(const QVector<Cell *> &cells);

#endif // CELLUTILITY_H
