#ifndef TESTCELL_H
#define TESTCELL_H

#include <QtTest>

class Cell;

class TestCell : public QObject
{
    Q_OBJECT
private slots:

    void countOfNeighbourMines_data();
    void countOfNeighbourMines();

    void hasMine_data();
    void hasMine();

    void hasQuestionmark_data();
    void hasQuestionmark();

    void isCovered_data();
    void isCovered();

    void isFlagged_data();
    void isFlagged();

    void isPressed_data();
    void isPressed();

    void neighbourHasMine_data();
    void neighbourHasMine();

    void slot_toggleNewQuestionMarks_data();
    void slot_toggleNewQuestionMarks();

    void slot_increaseCountOfFlaggedNeighbours_data();
    void slot_increaseCountOfFlaggedNeighbours();

    void slot_decreaseCountOfFlaggedNeighbours_data();
    void slot_decreaseCountOfFlaggedNeighbours();

    void slot_uncoverIfCoveredAndNoMine_data();
    void slot_uncoverIfCoveredAndNoMine();

    void slot_uncoverIfNotFlagged_data();
    void slot_uncoverIfNotFlagged();

    void slot_pressIfCoveredOrQuestionmark_data();
    void slot_pressIfCoveredOrQuestionmark();

    void slot_releaseIfCoveredOrQuestionmarkPressed_data();
    void slot_releaseIfCoveredOrQuestionmarkPressed();

    void signal_hitMine_data();
    void signal_hitMine();

    void signal_flagged_data();
    void signal_flagged();

    void signal_unflagged_data();
    void signal_unflagged();

    void signal_uncovered_data();
    void signal_uncovered();

    void signal_uncoveredEmptyCell_data();
    void signal_uncoveredEmptyCell();

    void signal_uncoverAreaWithNoMines_data();
    void signal_uncoverAreaWithNoMines();

    void signal_uncoverNotFlaggedNeighbours_data();
    void signal_uncoverNotFlaggedNeighbours();

    void signal_pressed_data();
    void signal_pressed();

    void signal_released_data();
    void signal_released();

    void signal_pressNeighbours_data();
    void signal_pressNeighbours();

    void signal_releaseNeighbours_data();
    void signal_releaseNeighbours();
};

void doNRightClicks(Cell &cell, int n);

#endif // TESTCELL_H
