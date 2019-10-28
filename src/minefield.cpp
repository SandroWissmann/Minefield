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

#include "minefield.h"

#include "cell.h"
#include "cellinputhandler.h"
#include "cellutility.h"

#include <QDebug>
#include <QGridLayout>

Minefield::Minefield(const QVector<Cell *> &cells, int width, int height,
                     QWidget *parent)
    :QWidget{ parent },
      mCells{ cells },
      mFieldWidth{ width },
      mFieldHeight{ height },
      mMinesLeft{ countOfMines()},
      mCellInputHandler{ new CellInputHandler{ this } }
{
    Q_ASSERT(mCells.size() == (mFieldWidth * mFieldHeight));

    connectCellsWithNeighbourCells(mCells, mFieldWidth, mFieldHeight);

    for(auto &cell : mCells) {
        cell->installEventFilter(mCellInputHandler);
    }

    connectWithCells();
    addCellsToLayout();
}

int Minefield::fieldWidth() const
{
    return mFieldWidth;
}

int Minefield::fieldHeight() const
{
    return mFieldHeight;
}

int Minefield::countOfMines() const
{
    auto count = 0;
    for(const auto& cell : mCells) {
        if(cell->hasMine()) {
            ++count;
        }
    }
    return count;
}

int Minefield::minesLeft() const
{
    return mMinesLeft;
}

void Minefield::flaggedCell()
{
    --mMinesLeft;
    emit minesLeftChanged(mMinesLeft);
}

void Minefield::unflaggedCell()
{
    ++mMinesLeft;
    emit minesLeftChanged(mMinesLeft);
}


void Minefield::checkIfFirstCellIsUncovered()
{
    if(!mFirstCellUncovered) {
        mFirstCellUncovered = true;

        for(const auto &cell : mCells) {
            disconnect(cell, &Cell::uncovered,
                       this, &Minefield::checkIfFirstCellIsUncovered);
        }

        emit uncoveredFirstCell();
    }
}

void Minefield::checkIfSafeCellsUncovered()
{
    if(!mSafeCellsUncovered && allSafeCellsUncovered(mCells)) {
        mSafeCellsUncovered = true;

        for(const auto &cell : mCells) {
            disconnect(cell, &Cell::uncovered,
                       this, &Minefield::checkIfSafeCellsUncovered);
        }

        disableInput();
        emit uncoveredAllSafeCells();
    }
}

void Minefield::connectWithCells()
{
    for(const auto &cell : mCells) {
        connect(cell, &Cell::pressed,
                this, &Minefield::pressedCell);
        connect(cell, &Cell::released,
                this, &Minefield::releasedCell);

        connect(cell, &Cell::uncoveredEmptyCell,
                this, &Minefield::uncoveredEmptyCell);

        connect(cell, &Cell::flagged,
                this, &Minefield::flaggedCell);
        connect(cell, &Cell::unflagged,
                this, &Minefield::unflaggedCell);

        connect(cell, &Cell::uncovered,
                this, &Minefield::checkIfFirstCellIsUncovered);
        connect(cell, &Cell::uncovered,
                this, &Minefield::checkIfSafeCellsUncovered);

        connect(this, &Minefield::toggleNewQuesionMarksInCells,
                cell, &Cell::toggleNewQuestionMarks);
        connect(this, &Minefield::toggleColorInCells,
                cell, &Cell::toggleColor);

        if(cell->hasMine()) {
            connect(cell, &Cell::hitMine,
                    [=](){

                showWrongFlaggedCells();
                showAllMines();
                disableInput();
                emit mineExploded();
            });
        }
    }
}

void Minefield::addCellsToLayout()
{
    auto layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    for(int i = 0; i < mCells.size(); ++i) {
        auto column = static_cast<int>(i %  mFieldWidth);
        auto row = static_cast<int>(i /  mFieldWidth);

        layout->addWidget(mCells[i], row, column);
    }
    setLayout(layout);
}

void Minefield::showAllMines()
{
    for(const auto cell : mCells) {
        if(cell->hasMine() && cell->isCovered()) {
            cell->showMine();
        }
    }
}

void Minefield::showWrongFlaggedCells()
{
    for(const auto &cell : mCells) {
        if(!cell->hasMine() && cell->isFLagged()) {
            cell->setToFlaggedWrong();
        }
    }
}

void Minefield::disableInput()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}
