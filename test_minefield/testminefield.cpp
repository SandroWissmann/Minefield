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

#include "testminefield.h"

#include "cell.h"
#include "minefield.h"

#include <QTest>
#include <QSignalSpy>

constexpr auto delayClickRightAndLeftTogether = 70;

void TestMinefield::fieldWidth()
{
    QVector<Cell *> cells;

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    constexpr auto height = 2;
    constexpr auto width = 5;

    Minefield obj{ cells, width, height };

    QCOMPARE(obj.fieldWidth(), width);
}

void TestMinefield::fieldHeight()
{
    QVector<Cell *> cells;

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    constexpr auto height = 2;
    constexpr auto width = 5;

    Minefield obj{ cells, width, height };

    QCOMPARE(obj.fieldHeight(), height);
}

void TestMinefield::countOfMines()
{
    QVector<Cell *> cells;

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    constexpr auto height = 2;
    constexpr auto width = 5;

    Minefield obj{ cells, width, height };

    QCOMPARE(obj.countOfMines(), 2);
}

void TestMinefield::minesLeft()
{
    QVector<Cell *> cells;

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    constexpr auto height = 2;
    constexpr auto width = 5;

    Minefield obj{ cells, width, height };

    QCOMPARE(obj.minesLeft(), 2);
}

void TestMinefield::signal_uncoveredFirstCell()
{
    QVector<Cell *> cells;

    cells << new Cell{ Cell::State::empty };
    cells << new Cell{ Cell::State::mine };

    cells << new Cell{ Cell::State::mine };
    cells << new Cell{ Cell::State::empty };

    constexpr auto height = 2;
    constexpr auto width = 2;

    auto cellWidth = cells[0]->width();
    auto cellHeight = cells[0]->height();

    Minefield obj{ cells, width, height };

    QSignalSpy spy(&obj, &Minefield::uncoveredFirstCell);

    QPoint pos = {obj.pos().x() + cellWidth/2,
            obj.pos().y() + cellHeight/2};

    auto child = obj.childAt(pos);  // I checked here that theres actually a child

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier, pos);
    QTest::qWait(delayClickRightAndLeftTogether);
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier, pos);

    QCOMPARE(spy.count(), 1);
}

void TestMinefield::signal_uncoveredEmptyCell()
{

}

void TestMinefield::signal_uncoveredAllSafeCells()
{

}

void TestMinefield::signal_pressedCell()
{

}

void TestMinefield::signal_releasedCell()
{

}

void TestMinefield::signal_mineExploded()
{

}

void TestMinefield::signal_minesLeftChanged()
{

}

QVector<Cell *> makeTestCells()
{
    QVector<Cell *> cells;

    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::mine};

    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::mine};
    cells << new Cell{Cell::State::empty};

    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::mine};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};

    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::mine};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};

    cells << new Cell{Cell::State::mine};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};
    cells << new Cell{Cell::State::empty};

    return cells;
}

QTEST_MAIN(TestMinefield)
