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


#ifndef CELL_H
#define CELL_H

#include <QWidget>

#include <QElapsedTimer>
#include <QTimer>

class CellInputHandler;

class Cell : public QWidget
{
    Q_OBJECT
public:
    enum class State{
        empty,
        mine
    };

    explicit Cell(State state, QWidget *parent = nullptr);

    void setCountOfNeighbourMines(int count);
    [[nodiscard]] int countOfNeighbourMines() const;

    [[nodiscard]] bool hasMine() const;
    [[nodiscard]] bool hasQuestionmark() const;
    [[nodiscard]] bool isCovered() const;
    [[nodiscard]] bool isFLagged() const;
    [[nodiscard]] bool isPressed() const;
    [[nodiscard]] bool neighbourHasMine() const;
    [[nodiscard]] bool neighbourIsFlagged() const;

public slots:
    void toggleColor(bool value);
    void toggleNewQuestionMarks(bool value);

    void increaseCountOfFlaggedNeighbours();
    void decreaseCountOfFlaggedNeighbours();
    void uncoverIfCoveredAndNoMine();
    void uncoverIfNotFlagged();

    void pressIfCoveredOrQuestionmark();
    void releaseIfCoveredOrQuestionmarkPressed();

    void showMine();
    void setToFlaggedWrong();

signals:
    void hitMine();
    void flagged();
    void unflagged();
    void uncovered();
    void uncoveredEmptyCell();
    void uncoverAreaWithNoMines();
    void uncoverNotFlaggedNeighbours();
    void pressed();
    void released();
    void pressNeighbours();
    void releaseNeighbours();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void mark();

private:
    enum class DisplayType{
        covered,
        coveredPressed,
        neigboursHave0Mines,
        neigboursHave1Mine,
        neigboursHave2Mines,
        neigboursHave3Mines,
        neigboursHave4Mines,
        neigboursHave5Mines,
        neigboursHave6Mines,
        neigboursHave7Mines,
        neigboursHave8Mines,
        questionmark,
        questionmarkPressed,
        flagged,
        mine,
        mineExploded,
        flaggedWrong,
    };

    QImage displayImage(DisplayType type);

    void uncover();
    void uncoverMine();
    void setToUncoveredDisplayType();

    friend class CellInputHandler;

    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);

    void handleMouseMoveEventInsideLeftButton(QMouseEvent *event);
    void handleMouseMoveEventOutsideLeftButton(QMouseEvent *event);

    void handleMouseMoveEventInsideBothButtons(QMouseEvent *event);
    void handleMouseMoveEventOutsideBothButtons(QMouseEvent *event);

    const bool mHasMine;
    bool mNeighboursPressed;
    bool mQuestionMarksOn;
    bool mColorOn;
    int mCountOfNeighbourMines;
    int mCountOfNeigboursFlagged;
    QElapsedTimer mElapsedTimer;
    QTimer mSingleMouseTimerLeft;
    QTimer mSingleMouseTimerRight;
    DisplayType mDisplayType;
};

#endif // CELL_H
