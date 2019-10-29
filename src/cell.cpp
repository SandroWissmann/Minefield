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

#include "cell.h"

#include "converttograyscale.h"
#include "cellinputhandler.h"

#include <QApplication>
#include <QIcon>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QImage>

#include <QDebug>

Cell::Cell(Cell::State state, QWidget *parent)
    :QWidget{ parent },
      mHasMine{ static_cast<bool>(state) },
      mNeighboursPressed{ false },
      mQuestionMarksOn{ true },
      mColorOn{ true },
      mCountOfNeighbourMines{ 0 },
      mCountOfNeigboursFlagged{ 0 },
      mDisplayType{ DisplayType::covered }
{
    setFixedSize(displayImage(mDisplayType).size());

    mElapsedTimer.start();

    constexpr auto intervall = 50;
    for(QTimer* timer : {&mSingleMouseTimerRight, &mSingleMouseTimerLeft}){
        timer->setInterval(intervall);
        timer->setSingleShot(true);
    }

    connect(&mSingleMouseTimerLeft, &QTimer::timeout,
            this, &Cell::pressIfCoveredOrQuestionmark);
    connect(&mSingleMouseTimerRight, &QTimer::timeout,
            this, &Cell::mark);

    setMouseTracking(true);
}

void Cell::setCountOfNeighbourMines(int count)
{
    constexpr auto minNeighbourMines = 0;
    constexpr auto maxNeighbourMines = 8;

    Q_ASSERT(count >= minNeighbourMines && count <= maxNeighbourMines);

    mCountOfNeighbourMines = count;
}

int Cell::countOfNeighbourMines() const
{
    return mCountOfNeighbourMines;
}

bool Cell::hasMine() const
{
    return mHasMine;
}

bool Cell::hasQuestionmark() const
{
    return mDisplayType == DisplayType::questionmark;
}

bool Cell::isCovered() const
{
    return mDisplayType == DisplayType::covered;
}

bool Cell::isFLagged() const
{
    return mDisplayType == DisplayType::flagged;
}

bool Cell::isPressed() const
{
    return mDisplayType == DisplayType::coveredPressed ||
            mDisplayType == DisplayType::questionmarkPressed;
}

bool Cell::neighbourHasMine() const
{
    return mCountOfNeighbourMines != 0;
}

bool Cell::neighbourIsFlagged() const
{
    return mCountOfNeigboursFlagged != 0;
}

void Cell::toggleColor(bool value)
{
    mColorOn = value;
    update();
}

void Cell::toggleNewQuestionMarks(bool value)
{
    mQuestionMarksOn = value;
}

void Cell::increaseCountOfFlaggedNeighbours()
{
    ++mCountOfNeigboursFlagged;
    Q_ASSERT(mCountOfNeigboursFlagged <= 8);
}

void Cell::decreaseCountOfFlaggedNeighbours()
{
    --mCountOfNeigboursFlagged;
    Q_ASSERT(mCountOfNeigboursFlagged >= 0);
}

void Cell::uncoverIfCoveredAndNoMine()
{
    if (hasMine() || !isCovered()) {
        return;
    }

    setToUncoveredDisplayType();
    update();

    if(!neighbourHasMine()) {
        emit uncoverAreaWithNoMines();
    }
}

void Cell::uncoverIfNotFlagged()
{
    if (isFLagged() || mDisplayType == DisplayType::flaggedWrong) {
        return;
    }

    uncover();
    update();

    if(!neighbourHasMine()) {
        emit uncoverAreaWithNoMines();
    }
}

void Cell::pressIfCoveredOrQuestionmark()
{ 
    if(mSingleMouseTimerLeft.isActive()) {
        mSingleMouseTimerLeft.stop();
    }

    if(mDisplayType == DisplayType::covered) {
        mDisplayType = DisplayType::coveredPressed;
        emit pressed();
        update();
    }
    else if(mDisplayType == DisplayType::questionmark) {
        mDisplayType = DisplayType::questionmarkPressed;
        emit pressed();
        update();
    }
}

void Cell::releaseIfCoveredOrQuestionmarkPressed()
{
    if(mSingleMouseTimerLeft.isActive()) {
        mSingleMouseTimerLeft.stop();
    }

    if(mDisplayType == DisplayType::coveredPressed) {
        mDisplayType = DisplayType::covered;
        emit released();
        update();
    }
    else if(mDisplayType == DisplayType::questionmarkPressed) {
        mDisplayType = DisplayType::questionmark;
        emit released();
        update();
    }
}

void Cell::showMine()
{
    if(hasMine()) {
        mDisplayType = DisplayType::mine;
        update();
    }
}

void Cell::setToFlaggedWrong()
{
    mDisplayType = DisplayType::flaggedWrong;
    update();
}

void Cell::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter{ this };

    auto image = displayImage(mDisplayType);

    if(!mColorOn) {
        image = convertToGrayscale(image);
    }

    painter.drawImage(rect(), image);
}

void Cell::mark()
{
    switch (mDisplayType) {
    case DisplayType::covered:
        mDisplayType = DisplayType::flagged;
        emit flagged();
        update();
        break;
    case DisplayType::flagged:
        if(mQuestionMarksOn) {
            mDisplayType = DisplayType::questionmark;
        }
        else {
            mDisplayType = DisplayType::covered;
        }
        emit unflagged();
        update();
        break;
    case DisplayType::questionmark:
        mDisplayType = DisplayType::covered;
        update();
        break;
    default:
        break;
    }
}

QImage Cell::displayImage(Cell::DisplayType type)
{
    switch(type){
        case DisplayType::covered:
            return QImage{":/ressources/cell_covered.png"};
        case DisplayType::coveredPressed:
            return QImage{":/ressources/cell_covered_pressed.png"};
        case DisplayType::neigboursHave0Mines:
            return QImage{":/ressources/cell_0.png"};
        case DisplayType::neigboursHave1Mine:
            return QImage{":/ressources/cell_1.png"};
        case DisplayType::neigboursHave2Mines:
            return QImage{":/ressources/cell_2.png"};
        case DisplayType::neigboursHave3Mines:
            return QImage{":/ressources/cell_3.png"};
        case DisplayType::neigboursHave4Mines:
            return QImage{":/ressources/cell_4.png"};
        case DisplayType::neigboursHave5Mines:
            return QImage{":/ressources/cell_5.png"};
        case DisplayType::neigboursHave6Mines:
            return QImage{":/ressources/cell_6.png"};
        case DisplayType::neigboursHave7Mines:
            return QImage{":/ressources/cell_7.png"};
        case DisplayType::neigboursHave8Mines:
            return QImage{":/ressources/cell_8.png"};
        case DisplayType::questionmark:
            return QImage{":/ressources/cell_questionmark.png"};
        case DisplayType::questionmarkPressed:
            return QImage{":/ressources/cell_questionmark_pressed.png"};
        case DisplayType::flagged:
            return QImage{":/ressources/cell_flagged.png"};
        case DisplayType::mine:
            return QImage{":/ressources/cell_mine.png"};
        case DisplayType::mineExploded:
            return QImage{":/ressources/cell_mine_explode.png"};
        case DisplayType::flaggedWrong:
            return QImage{":/ressources/cell_nomine.png"};
    }
    return QImage{};
}

void Cell::uncover()
{
    if(hasMine()) {
        uncoverMine();
    }
    else {
        setToUncoveredDisplayType();
    }
    emit uncovered();
    update();
}

void Cell::uncoverMine()
{
    mDisplayType = DisplayType::mineExploded;
    emit hitMine();
}

void Cell::setToUncoveredDisplayType()
{
    mDisplayType = static_cast<DisplayType>(
    static_cast<int>(
        DisplayType::neigboursHave0Mines) + mCountOfNeighbourMines);
    emit uncoveredEmptyCell();
}


void Cell::handleMousePressEvent(QMouseEvent *event)
{
    if(!(event->buttons().testFlag(Qt::LeftButton) ||
         event->buttons().testFlag(Qt::RightButton))) {
        return;
    }

    if(event->buttons().testFlag(Qt::LeftButton)) {
        mSingleMouseTimerLeft.start();
    }
    else if (event->buttons().testFlag(Qt::RightButton)){
        mSingleMouseTimerRight.start();
    }

    const auto elapsedTime = mElapsedTimer.restart();

    if(elapsedTime >= QApplication::doubleClickInterval()) {
        return;
    }

    if((mSingleMouseTimerLeft.isActive() &&
        event->buttons().testFlag(Qt::RightButton)) ||
        (mSingleMouseTimerRight.isActive() &&
         event->buttons().testFlag(Qt::LeftButton))){

        if(!isPressed()) {
            pressIfCoveredOrQuestionmark();
            mNeighboursPressed = true;
            emit pressNeighbours();
        }
        for(QTimer* timer : { &mSingleMouseTimerRight,
            &mSingleMouseTimerLeft }) {
            timer->stop();
        }
    }
}

void Cell::handleMouseReleaseEvent(QMouseEvent *event)
{
    if(mNeighboursPressed) {
        if(event->button() == Qt::LeftButton ||
                event->button() == Qt::RightButton)
        {
            mNeighboursPressed = false;

            if(mCountOfNeigboursFlagged == mCountOfNeighbourMines) {
                if(isPressed()) {
                    uncover();
                }
                emit uncoverNotFlaggedNeighbours();
                emit uncoverAreaWithNoMines();
            }
            else {
                if(isPressed()) {
                    releaseIfCoveredOrQuestionmarkPressed();
                }
                emit releaseNeighbours();
            }
        }
    }
    else if(event->button() == Qt::LeftButton) {
        uncover();

        if(mDisplayType == DisplayType::neigboursHave0Mines) {
            emit uncoverAreaWithNoMines();
        }
    }
}

void Cell::handleMouseMoveEventInsideLeftButton(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(!isPressed()) {
        pressIfCoveredOrQuestionmark();
    }
}

void Cell::handleMouseMoveEventOutsideLeftButton(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(mSingleMouseTimerLeft.isActive()) {
        mSingleMouseTimerLeft.stop();
    }

    if(isPressed()) {
        releaseIfCoveredOrQuestionmarkPressed();
    }
}

void Cell::handleMouseMoveEventInsideBothButtons(QMouseEvent *event)
{
    handleMouseMoveEventInsideLeftButton(event);

    mNeighboursPressed = true;
    emit pressNeighbours();

}

void Cell::handleMouseMoveEventOutsideBothButtons(QMouseEvent *event)
{
    handleMouseMoveEventOutsideLeftButton(event);

    if(mNeighboursPressed) {
        mNeighboursPressed = false;
        emit releaseNeighbours();
    }
}


