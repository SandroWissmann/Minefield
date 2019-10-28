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

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QVector>
#include <QWidget>

#include "cell.h"

#include <vector>

class CellInputHandler;

class Minefield : public QWidget
{
    Q_OBJECT
public:   
    Minefield(const QVector<Cell *> &cells, int width, int height,
              QWidget *parent = nullptr);

    [[nodiscard]] int fieldWidth() const;
    [[nodiscard]] int fieldHeight() const;
    [[nodiscard]] int countOfMines() const;
    [[nodiscard]] int minesLeft() const;

signals:
    void toggleColorInCells(int value);
    void toggleNewQuesionMarksInCells(int value);

    void uncoveredFirstCell();
    void uncoveredEmptyCell();
    void uncoveredAllSafeCells();

    void pressedCell();
    void releasedCell();

    void mineExploded();
    void minesLeftChanged(int minesLeft);  

private slots:
    void flaggedCell();
    void unflaggedCell();

    void checkIfFirstCellIsUncovered();
    void checkIfSafeCellsUncovered();    

private:   
    void connectWithCells();
    void addCellsToLayout();

    void showAllMines();
    void showWrongFlaggedCells();
    void disableInput();

    bool mFirstCellUncovered{ false };
    bool mSafeCellsUncovered{ false };
    QVector<Cell *> mCells;
    int mFieldWidth;
    int mFieldHeight;
    int mMinesLeft;
    CellInputHandler *mCellInputHandler;

};

#endif // MINEFIELD_H
