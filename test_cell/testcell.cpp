#include "testcell.h"

#include "cell.h"
#include "cellinputhandler.h"

#include <QTest>
#include <QThread>
#include <QSignalSpy>

#include <QDebug>

constexpr auto delayClickRightAndLeftTogether = 70;

enum RichtClickState{
    covered,
    flagged,
    questionmark
};

Q_DECLARE_METATYPE(RichtClickState)
Q_DECLARE_METATYPE(Cell::State)

void TestCell::countOfNeighbourMines_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::newRow("has mine") << Cell::State::mine;
    QTest::newRow("is empty") << Cell::State::empty;
}

void TestCell::countOfNeighbourMines()
{
    QFETCH(Cell::State, cellState);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QCOMPARE(obj.countOfNeighbourMines(), 0);
    obj.setCountOfNeighbourMines(1);
    QCOMPARE(obj.countOfNeighbourMines(), 1);
}

void TestCell::hasMine_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine") << Cell::State::mine << true;
    QTest::newRow("is empty") << Cell::State::empty << false;
}

void TestCell::hasMine()
{
    QFETCH(Cell::State, cellState);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QCOMPARE(obj.hasMine(), result);
}

void TestCell::hasQuestionmark_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine covered")
            << Cell::State::mine << covered << false;
    QTest::newRow("has mine flagged")
            << Cell::State::mine << flagged << false;
    QTest::newRow("has mine questionmark")
            << Cell::State::mine << questionmark << true;
    QTest::newRow("is empty covered")
            << Cell::State::empty << covered << false;
    QTest::newRow("is empty flagged")
            << Cell::State::empty << flagged << false;
    QTest::newRow("is empty questionmark")
            << Cell::State::empty << questionmark << true;
}

void TestCell::hasQuestionmark()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);
    QCOMPARE(obj.hasQuestionmark(), result);
}

void TestCell::isCovered_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine covered")
            << Cell::State::mine << covered << true;
    QTest::newRow("has mine flagged")
            << Cell::State::mine << flagged << false;
    QTest::newRow("has mine questionmark")
            << Cell::State::mine << questionmark << false;
    QTest::newRow("is empty covered")
            << Cell::State::empty << covered << true;
    QTest::newRow("is empty flagged")
            << Cell::State::empty << flagged << false;
    QTest::newRow("is empty questionmark")
            << Cell::State::empty << questionmark << false;
}

void TestCell::isCovered()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);
    QCOMPARE(obj.isCovered(), result);

    // uncover
    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::qWait(delayClickRightAndLeftTogether);
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QCOMPARE(obj.isCovered(), false);
}

void TestCell::isFlagged_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine covered")
            << Cell::State::mine << covered << false;
    QTest::newRow("has mine flagged")
            << Cell::State::mine << flagged << true;
    QTest::newRow("has mine questionmark")
            << Cell::State::mine << questionmark << false;
    QTest::newRow("is empty covered")
            << Cell::State::empty << covered << false;
    QTest::newRow("is empty flagged")
            << Cell::State::empty << flagged << true;
    QTest::newRow("is empty questionmark")
            << Cell::State::empty << questionmark << false;
}

void TestCell::isFlagged()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);
    QCOMPARE(obj.isFLagged(), result);

    // uncover
    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::qWait(delayClickRightAndLeftTogether);
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QCOMPARE(obj.isFLagged(), false);
}

void TestCell::isPressed_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("rightClickResult");
    QTest::addColumn<bool>("pressBothResult");
    QTest::newRow("has mine covered")
            << Cell::State::mine << covered << false << true;
    QTest::newRow("has mine flagged")
            << Cell::State::mine << flagged << false << false;
    QTest::newRow("has mine questionmark")
            << Cell::State::mine << questionmark << false << true;
    QTest::newRow("is empty covered")
            << Cell::State::empty << covered << false << true;
    QTest::newRow("is empty flagged")
            << Cell::State::empty << flagged << false << false;
    QTest::newRow("is empty questionmark")
            << Cell::State::empty << questionmark << false << true;
}

void TestCell::isPressed()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, rightClickResult);
    QFETCH(bool, pressBothResult);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);
    QCOMPARE(obj.isPressed(), rightClickResult);

    // press both
    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(obj.isPressed(), pressBothResult);

    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QCOMPARE(obj.isPressed(), false);
}


void TestCell::neighbourHasMine_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("countOfNeighbours");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine 0 Neighbours with Mine")
            << Cell::State::mine << 0 << false;
    QTest::newRow("has mine 1 Neighbours with Mine")
            << Cell::State::mine << 1 << true;
    QTest::newRow("has mine 2 Neighbours with Mine")
            << Cell::State::mine << 2 << true;
    QTest::newRow("has mine 3 Neighbours with Mine")
            << Cell::State::mine << 3 << true;
    QTest::newRow("has mine 4 Neighbours with Mine")
            << Cell::State::mine << 4 << true;
    QTest::newRow("has mine 5 Neighbours with Mine")
            << Cell::State::mine << 5 << true;
    QTest::newRow("has mine 6 Neighbours with Mine")
            << Cell::State::mine << 6 << true;
    QTest::newRow("has mine 7 Neighbours with Mine")
            << Cell::State::mine << 7 << true;
    QTest::newRow("has mine 8 Neighbours with Mine")
            << Cell::State::mine << 8 << true;
    QTest::newRow("is empty 0 Neighbours with Mine")
            << Cell::State::empty << 0 << false;
    QTest::newRow("is empty 1 Neighbours with Mine")
            << Cell::State::empty << 1 << true;
    QTest::newRow("is empty 2 Neighbours with Mine")
            << Cell::State::empty << 2 << true;
    QTest::newRow("is empty 3 Neighbours with Mine")
            << Cell::State::empty << 3 << true;
    QTest::newRow("is empty 4 Neighbours with Mine")
            << Cell::State::empty << 4 << true;
    QTest::newRow("is empty 5 Neighbours with Mine")
            << Cell::State::empty << 5 << true;
    QTest::newRow("is empty 6 Neighbours with Mine")
            << Cell::State::empty << 6 << true;
    QTest::newRow("is empty 7 Neighbours with Mine")
            << Cell::State::empty << 7 << true;
    QTest::newRow("is empty 8 Neighbours with Mine")
            << Cell::State::empty << 8 << true;
}

void TestCell::neighbourHasMine()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, countOfNeighbours);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    obj.setCountOfNeighbourMines(countOfNeighbours);
    QCOMPARE(obj.neighbourHasMine(), result);
}

void TestCell::slot_toggleNewQuestionMarks_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<bool>("toggled");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine toggled on")
            << Cell::State::mine << true << true;
    QTest::newRow("has mine toggled off")
            << Cell::State::mine << false << false;
    QTest::newRow("is empty toggled on")
            << Cell::State::empty << true << true;
    QTest::newRow("is empty toggled off")
            << Cell::State::empty << false << false;
}

void TestCell::slot_toggleNewQuestionMarks()
{
    QFETCH(Cell::State, cellState);
    QFETCH(bool, toggled);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    // go to state flagged
    doNRightClicks(obj, 1);
    QCOMPARE(obj.hasQuestionmark(), false);

    // go to state question mark
    doNRightClicks(obj, 1);
    obj.toggleNewQuestionMarks(toggled);
    QCOMPARE(obj.hasQuestionmark(), true);

    // go to state covered again
    doNRightClicks(obj, 1);
    QCOMPARE(obj.hasQuestionmark(), false);

    // go to state flagged again
    doNRightClicks(obj, 1);
    QCOMPARE(obj.hasQuestionmark(), false);

    // next state questionmark or covered
    doNRightClicks(obj, 1);
    QCOMPARE(obj.hasQuestionmark(), result);
}

void TestCell::slot_increaseCountOfFlaggedNeighbours_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("countOfFlaggedNeighbours");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine 0 Neigbours flagged")
            << Cell::State::mine << 0 << false;
    QTest::newRow("has mine 1 Neigbours flagged")
            << Cell::State::mine << 1 << true;
    QTest::newRow("has mine 2 Neigbours flagged")
            << Cell::State::mine << 2 << true;
    QTest::newRow("has mine 3 Neigbours flagged")
            << Cell::State::mine << 3 << true;
    QTest::newRow("has mine 4 Neigbours flagged")
            << Cell::State::mine << 4 << true;
    QTest::newRow("has mine 5 Neigbours flagged")
            << Cell::State::mine << 5 << true;
    QTest::newRow("has mine 6 Neigbours flagged")
            << Cell::State::mine << 6 << true;
    QTest::newRow("has mine 7 Neigbours flagged")
            << Cell::State::mine << 7 << true;
    QTest::newRow("has mine 8 Neigbours flagged")
            << Cell::State::mine << 8 << true;
    QTest::newRow("is empty 0 Neigbours flagged")
            << Cell::State::empty << 0 << false;
    QTest::newRow("is empty 1 Neigbours flagged")
            << Cell::State::empty << 1 << true;
    QTest::newRow("is empty 2 Neigbours flagged")
            << Cell::State::empty << 2 << true;
    QTest::newRow("is empty 3 Neigbours flagged")
            << Cell::State::empty << 3 << true;
    QTest::newRow("is empty 4 Neigbours flagged")
            << Cell::State::empty << 4 << true;
    QTest::newRow("is empty 5 Neigbours flagged")
            << Cell::State::empty << 5 << true;
    QTest::newRow("is empty 6 Neigbours flagged")
            << Cell::State::empty << 6 << true;
    QTest::newRow("is empty 7 Neigbours flagged")
            << Cell::State::empty << 7 << true;
    QTest::newRow("is empty 8 Neigbours flagged")
            << Cell::State::empty << 8 << true;
}

void TestCell::slot_increaseCountOfFlaggedNeighbours()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, countOfFlaggedNeighbours);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    for(int i = 0; i < countOfFlaggedNeighbours; ++i) {
        obj.increaseCountOfFlaggedNeighbours();
    }

    QCOMPARE(obj.neighbourIsFlagged(), result);
}

void TestCell::slot_decreaseCountOfFlaggedNeighbours_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("countOfFlaggedNeighbours");
    QTest::addColumn<bool>("result");
    QTest::newRow("has mine 0 Neigbours flagged")
            << Cell::State::mine << 0 << false;
    QTest::newRow("has mine 1 Neigbours flagged")
            << Cell::State::mine << 1 << true;
    QTest::newRow("has mine 2 Neigbours flagged")
            << Cell::State::mine << 2 << true;
    QTest::newRow("has mine 3 Neigbours flagged")
            << Cell::State::mine << 3 << true;
    QTest::newRow("has mine 4 Neigbours flagged")
            << Cell::State::mine << 4 << true;
    QTest::newRow("has mine 5 Neigbours flagged")
            << Cell::State::mine << 5 << true;
    QTest::newRow("has mine 6 Neigbours flagged")
            << Cell::State::mine << 6 << true;
    QTest::newRow("has mine 7 Neigbours flagged")
            << Cell::State::mine << 7 << true;
    QTest::newRow("has mine 8 Neigbours flagged")
            << Cell::State::mine << 8 << true;
    QTest::newRow("is empty 0 Neigbours flagged")
            << Cell::State::empty << 0 << false;
    QTest::newRow("is empty 1 Neigbours flagged")
            << Cell::State::empty << 1 << true;
    QTest::newRow("is empty 2 Neigbours flagged")
            << Cell::State::empty << 2 << true;
    QTest::newRow("is empty 3 Neigbours flagged")
            << Cell::State::empty << 3 << true;
    QTest::newRow("is empty 4 Neigbours flagged")
            << Cell::State::empty << 4 << true;
    QTest::newRow("is empty 5 Neigbours flagged")
            << Cell::State::empty << 5 << true;
    QTest::newRow("is empty 6 Neigbours flagged")
            << Cell::State::empty << 6 << true;
    QTest::newRow("is empty 7 Neigbours flagged")
            << Cell::State::empty << 7 << true;
    QTest::newRow("is empty 8 Neigbours flagged")
            << Cell::State::empty << 8 << true;
}

void TestCell::slot_decreaseCountOfFlaggedNeighbours()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, countOfFlaggedNeighbours);
    QFETCH(bool, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    constexpr auto maxFlaggedNeighbours = 8;

    for(int i = 0; i < maxFlaggedNeighbours; ++i) {
        obj.increaseCountOfFlaggedNeighbours();
    }

    for(int i = maxFlaggedNeighbours;
        i > countOfFlaggedNeighbours; --i) {
        obj.decreaseCountOfFlaggedNeighbours();
    }

    QCOMPARE(obj.neighbourIsFlagged(), result);
}

void TestCell::slot_uncoverIfCoveredAndNoMine_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("neighbourHasMine");
    QTest::addColumn<int>("sigUncoveredEmptyCell");
    QTest::addColumn<int>("sigUncoverAreaWithNoMines");
    QTest::addColumn<bool>("resultCovered");

    QTest::newRow("has mine covered Neigbour has mine")
            << Cell::State::mine << covered << true << 0 << 0 << true;
    QTest::newRow("has mine flagged Neigbour has mine")
            << Cell::State::mine << flagged << true << 0 << 0 << false;
    QTest::newRow("has mine questionmark Neigbour has mine")
            << Cell::State::mine << questionmark << true << 0 << 0 << false;

    QTest::newRow("has mine covered Neigbour has no mine")
            << Cell::State::mine << covered << false << 0 << 0 << true;
    QTest::newRow("has mine flagged Neigbour has no mine")
            << Cell::State::mine << flagged << false << 0 << 0 << false;
    QTest::newRow("has mine questionmark Neigbour has no mine")
            << Cell::State::mine << questionmark << false << 0 << 0 << false;

    QTest::newRow("is empty covered Neigbour has mine")
            << Cell::State::empty << covered << true << 1 << 0 << false;
    QTest::newRow("is empty flagged Neigbour has mine")
            << Cell::State::empty << flagged << true << 0 << 0 << false;
    QTest::newRow("is empty questionmark Neigbour has mine")
            << Cell::State::empty << questionmark << true << 0 << 0 << false;

    QTest::newRow("is empty covered Neigbour has no mine")
            << Cell::State::empty << covered << false << 1 << 1 << false;
    QTest::newRow("is empty flagged Neigbour has no mine")
            << Cell::State::empty << flagged << false << 0 << 0 << false;
    QTest::newRow("is empty questionmark Neigbour has no mine")
            << Cell::State::empty << questionmark << false << 0 << 0 << false;
}

void TestCell::slot_uncoverIfCoveredAndNoMine()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, neighbourHasMine);
    QFETCH(int, sigUncoveredEmptyCell);
    QFETCH(int, sigUncoverAreaWithNoMines);
    QFETCH(bool, resultCovered);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    if(neighbourHasMine) {
        obj.setCountOfNeighbourMines(1);
    }

    doNRightClicks(obj, rightClickState);

    QSignalSpy spyHitMine(&obj, &Cell::hitMine);
    QSignalSpy spyFlagged(&obj, &Cell::flagged);
    QSignalSpy spyUnflagged(&obj, &Cell::unflagged);
    QSignalSpy spyUncovered(&obj, &Cell::uncovered);
    QSignalSpy spyUncoveredEmptyCell(&obj, &Cell::uncoveredEmptyCell);
    QSignalSpy spyUncoverAreaWithNoMines(&obj, &Cell::uncoverAreaWithNoMines);
    QSignalSpy spyUncoverNotFlaggedNeighbours(
                &obj, &Cell::uncoverNotFlaggedNeighbours);
    QSignalSpy spyPressed(&obj, &Cell::pressed);
    QSignalSpy spyReleased(&obj, &Cell::released);
    QSignalSpy spyPressNeighbours(&obj, &Cell::pressNeighbours);
    QSignalSpy spyReleaseNeighbours(&obj, &Cell::releaseNeighbours);

    obj.uncoverIfCoveredAndNoMine();

    QCOMPARE(obj.isCovered(), resultCovered);

    QCOMPARE(spyHitMine.count(), 0);
    QCOMPARE(spyFlagged.count(), 0);
    QCOMPARE(spyUnflagged.count(), 0);
    QCOMPARE(spyUncovered.count(), 0);
    QCOMPARE(spyUncoveredEmptyCell.count(), sigUncoveredEmptyCell);
    QCOMPARE(spyUncoverAreaWithNoMines.count(), sigUncoverAreaWithNoMines);
    QCOMPARE(spyUncoverNotFlaggedNeighbours.count(), 0);
    QCOMPARE(spyPressed.count(), 0);
    QCOMPARE(spyReleased.count(), 0);
    QCOMPARE(spyPressNeighbours.count(), 0);
    QCOMPARE(spyReleaseNeighbours.count(), 0);
}

void TestCell::slot_uncoverIfNotFlagged_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("neighbourHasMine");
    QTest::addColumn<int>("sigHitMine");
    QTest::addColumn<int>("sigUncovered");
    QTest::addColumn<int>("sigUncoveredEmptyCell");
    QTest::addColumn<int>("sigUncoverAreaWithNoMines");
    QTest::addColumn<bool>("resultCovered");

    QTest::newRow("has mine covered Neigbour has mine")
            << Cell::State::mine << covered << true
            << 1 << 1 << 0 << 0;
    QTest::newRow("has mine flagged Neigbour has mine")
            << Cell::State::mine << flagged << true
            << 0 << 0 << 0 << 0;
    QTest::newRow("has mine questionmark Neigbour has mine")
            << Cell::State::mine << questionmark << true
            << 1 << 1 << 0 << 0;

    QTest::newRow("has mine covered Neigbour has no mine")
            << Cell::State::mine << covered << false
            << 1 << 1 << 0 << 1;
    QTest::newRow("has mine flagged Neigbour has no mine")
            << Cell::State::mine << flagged << false
            << 0 << 0 << 0 << 0;
    QTest::newRow("has mine questionmark Neigbour has no mine")
            << Cell::State::mine << questionmark << false
            << 1 << 1 << 0 << 1;

    QTest::newRow("is empty covered Neigbour has mine")
            << Cell::State::empty << covered << true
            << 0 << 1 << 1 << 0;
    QTest::newRow("is empty flagged Neigbour has mine")
            << Cell::State::empty << flagged << true
            << 0 << 0 << 0 << 0;
    QTest::newRow("is empty questionmark Neigbour has mine")
            << Cell::State::empty << questionmark << true
            << 0 << 1 << 1 << 0;

    QTest::newRow("is empty covered Neigbour has no mine")
            << Cell::State::empty << covered << false
            << 0 << 1 << 1 << 1;
    QTest::newRow("is empty flagged Neigbour has no mine")
            << Cell::State::empty << flagged << false
            << 0 << 0 << 0 << 0;
    QTest::newRow("is empty questionmark Neigbour has no mine")
            << Cell::State::empty << questionmark << false
            << 0 << 1 << 1 << 1;
}

void TestCell::slot_uncoverIfNotFlagged()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, neighbourHasMine);
    QFETCH(int, sigHitMine);
    QFETCH(int, sigUncovered);
    QFETCH(int, sigUncoveredEmptyCell);
    QFETCH(int, sigUncoverAreaWithNoMines);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    if(neighbourHasMine) {
        obj.setCountOfNeighbourMines(1);
    }

    doNRightClicks(obj, rightClickState);

    QSignalSpy spyHitMine(&obj, &Cell::hitMine);
    QSignalSpy spyFlagged(&obj, &Cell::flagged);
    QSignalSpy spyUnflagged(&obj, &Cell::unflagged);
    QSignalSpy spyUncovered(&obj, &Cell::uncovered);
    QSignalSpy spyUncoveredEmptyCell(&obj, &Cell::uncoveredEmptyCell);
    QSignalSpy spyUncoverAreaWithNoMines(&obj, &Cell::uncoverAreaWithNoMines);
    QSignalSpy spyUncoverNotFlaggedNeighbours(
                &obj, &Cell::uncoverNotFlaggedNeighbours);
    QSignalSpy spyPressed(&obj, &Cell::pressed);
    QSignalSpy spyReleased(&obj, &Cell::released);
    QSignalSpy spyPressNeighbours(&obj, &Cell::pressNeighbours);
    QSignalSpy spyReleaseNeighbours(&obj, &Cell::releaseNeighbours);

    obj.uncoverIfNotFlagged();

    QCOMPARE(obj.isCovered(), false);

    QCOMPARE(spyHitMine.count(), sigHitMine);
    QCOMPARE(spyFlagged.count(), 0);
    QCOMPARE(spyUnflagged.count(), 0);
    QCOMPARE(spyUncovered.count(), sigUncovered);
    QCOMPARE(spyUncoveredEmptyCell.count(), sigUncoveredEmptyCell);
    QCOMPARE(spyUncoverAreaWithNoMines.count(), sigUncoverAreaWithNoMines);
    QCOMPARE(spyUncoverNotFlaggedNeighbours.count(), 0);
    QCOMPARE(spyPressed.count(), 0);
    QCOMPARE(spyReleased.count(), 0);
    QCOMPARE(spyPressNeighbours.count(), 0);
    QCOMPARE(spyReleaseNeighbours.count(), 0);
}

void TestCell::slot_pressIfCoveredOrQuestionmark_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<int>("sigPressed");

    QTest::newRow("has mine covered")
            << Cell::State::mine << covered << 1;
    QTest::newRow("has mine flagged")
            << Cell::State::mine << flagged << 0;
    QTest::newRow("has mine questionmark")
            << Cell::State::mine << questionmark << 1;

    QTest::newRow("is empty covered")
            << Cell::State::empty << covered << 1;
    QTest::newRow("is empty flagged")
            << Cell::State::empty << flagged << 0;
    QTest::newRow("is empty questionmark")
            << Cell::State::empty << questionmark << 1;
}

void TestCell::slot_pressIfCoveredOrQuestionmark()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(int, sigPressed);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);

    QSignalSpy spyHitMine(&obj, &Cell::hitMine);
    QSignalSpy spyFlagged(&obj, &Cell::flagged);
    QSignalSpy spyUnflagged(&obj, &Cell::unflagged);
    QSignalSpy spyUncovered(&obj, &Cell::uncovered);
    QSignalSpy spyUncoveredEmptyCell(&obj, &Cell::uncoveredEmptyCell);
    QSignalSpy spyUncoverAreaWithNoMines(&obj, &Cell::uncoverAreaWithNoMines);
    QSignalSpy spyUncoverNotFlaggedNeighbours(
                &obj, &Cell::uncoverNotFlaggedNeighbours);
    QSignalSpy spyPressed(&obj, &Cell::pressed);
    QSignalSpy spyReleased(&obj, &Cell::released);
    QSignalSpy spyPressNeighbours(&obj, &Cell::pressNeighbours);
    QSignalSpy spyReleaseNeighbours(&obj, &Cell::releaseNeighbours);

    obj.pressIfCoveredOrQuestionmark();

    QCOMPARE(spyHitMine.count(), 0);
    QCOMPARE(spyFlagged.count(), 0);
    QCOMPARE(spyUnflagged.count(), 0);
    QCOMPARE(spyUncovered.count(), 0);
    QCOMPARE(spyUncoveredEmptyCell.count(), 0);
    QCOMPARE(spyUncoverAreaWithNoMines.count(), 0);
    QCOMPARE(spyUncoverNotFlaggedNeighbours.count(), 0);
    QCOMPARE(spyPressed.count(), sigPressed);
    QCOMPARE(spyReleased.count(), 0);
    QCOMPARE(spyPressNeighbours.count(), 0);
    QCOMPARE(spyReleaseNeighbours.count(), 0);
}

void TestCell::slot_releaseIfCoveredOrQuestionmarkPressed_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<RichtClickState>("rightClickState");
    QTest::addColumn<bool>("pressed");
    QTest::addColumn<int>("sigReleased");

    QTest::newRow("has mine covered pressed")
            << Cell::State::mine << covered << true << 1;
    QTest::newRow("has mine flagged pressed")
            << Cell::State::mine << flagged << true << 0;
    QTest::newRow("has mine questionmark pressed")
            << Cell::State::mine << questionmark << true <<1;

    QTest::newRow("has mine covered not pressed")
            << Cell::State::mine << covered << false << 0;
    QTest::newRow("has mine flagged not pressed")
            << Cell::State::mine << flagged << false << 0;
    QTest::newRow("has mine questionmark not pressed")
            << Cell::State::mine << questionmark << false <<0;

    QTest::newRow("is empty covered pressed")
            << Cell::State::empty << covered << true << 1;
    QTest::newRow("is empty flagged pressed")
            << Cell::State::empty << flagged << true << 0;
    QTest::newRow("is empty questionmark pressed")
            << Cell::State::empty << questionmark << true << 1;

    QTest::newRow("is empty covered not pressed")
            << Cell::State::empty << covered << false << 0;
    QTest::newRow("is empty flagged not pressed")
            << Cell::State::empty << flagged << false << 0;
    QTest::newRow("is empty questionmark not pressed")
            << Cell::State::empty << questionmark << false << 0;
}

void TestCell::slot_releaseIfCoveredOrQuestionmarkPressed()
{
    QFETCH(Cell::State, cellState);
    QFETCH(RichtClickState, rightClickState);
    QFETCH(bool, pressed);
    QFETCH(int, sigReleased);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    doNRightClicks(obj, rightClickState);

    if(pressed) {
        obj.pressIfCoveredOrQuestionmark();
    }

    QSignalSpy spyHitMine(&obj, &Cell::hitMine);
    QSignalSpy spyFlagged(&obj, &Cell::flagged);
    QSignalSpy spyUnflagged(&obj, &Cell::unflagged);
    QSignalSpy spyUncovered(&obj, &Cell::uncovered);
    QSignalSpy spyUncoveredEmptyCell(&obj, &Cell::uncoveredEmptyCell);
    QSignalSpy spyUncoverAreaWithNoMines(&obj, &Cell::uncoverAreaWithNoMines);
    QSignalSpy spyUncoverNotFlaggedNeighbours(
                &obj, &Cell::uncoverNotFlaggedNeighbours);
    QSignalSpy spyPressed(&obj, &Cell::pressed);
    QSignalSpy spyReleased(&obj, &Cell::released);
    QSignalSpy spyPressNeighbours(&obj, &Cell::pressNeighbours);
    QSignalSpy spyReleaseNeighbours(&obj, &Cell::releaseNeighbours);

    obj.releaseIfCoveredOrQuestionmarkPressed();

    QCOMPARE(spyHitMine.count(), 0);
    QCOMPARE(spyFlagged.count(), 0);
    QCOMPARE(spyUnflagged.count(), 0);
    QCOMPARE(spyUncovered.count(), 0);
    QCOMPARE(spyUncoveredEmptyCell.count(), 0);
    QCOMPARE(spyUncoverAreaWithNoMines.count(), 0);
    QCOMPARE(spyUncoverNotFlaggedNeighbours.count(), 0);
    QCOMPARE(spyPressed.count(), 0);
    QCOMPARE(spyReleased.count(), sigReleased);
    QCOMPARE(spyPressNeighbours.count(), 0);
    QCOMPARE(spyReleaseNeighbours.count(), 0);
}

void TestCell::signal_hitMine_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 0;
}

void TestCell::signal_hitMine()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::hitMine);

    QTest::mouseClick(&obj, Qt::LeftButton, Qt::NoModifier);

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_flagged_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_flagged()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::flagged);

    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::qWait(delayClickRightAndLeftTogether);

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_unflagged_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_unflagged()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::unflagged);

    doNRightClicks(obj, flagged);

    // unflagged
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::qWait(delayClickRightAndLeftTogether);


    QCOMPARE(spy.count(), result);
}

void TestCell::signal_uncovered_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_uncovered()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::uncovered);

    QTest::mouseClick(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_uncoveredEmptyCell_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 0;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_uncoveredEmptyCell()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::uncoveredEmptyCell);

    QTest::mouseClick(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_uncoverAreaWithNoMines_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("countOfNeighbourMines");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine 0 neighbour mines") << Cell::State::mine << 0 << 0;
    QTest::newRow("has mine 1 neighbour mines") << Cell::State::mine << 1 << 0;
    QTest::newRow("has mine 2 neighbour mines") << Cell::State::mine << 2 << 0;
    QTest::newRow("has mine 3 neighbour mines") << Cell::State::mine << 3 << 0;
    QTest::newRow("has mine 4 neighbour mines") << Cell::State::mine << 4 << 0;
    QTest::newRow("has mine 5 neighbour mines") << Cell::State::mine << 5 << 0;
    QTest::newRow("has mine 6 neighbour mines") << Cell::State::mine << 6 << 0;
    QTest::newRow("has mine 7 neighbour mines") << Cell::State::mine << 7 << 0;
    QTest::newRow("has mine 8 neighbour mines") << Cell::State::mine << 8 << 0;
    QTest::newRow("is empty 0 neighbour mines") << Cell::State::empty << 0 << 1;
    QTest::newRow("is empty 1 neighbour mines") << Cell::State::empty << 1 << 0;
    QTest::newRow("is empty 2 neighbour mines") << Cell::State::empty << 2 << 0;
    QTest::newRow("is empty 3 neighbour mines") << Cell::State::empty << 3 << 0;
    QTest::newRow("is empty 4 neighbour mines") << Cell::State::empty << 4 << 0;
    QTest::newRow("is empty 5 neighbour mines") << Cell::State::empty << 5 << 0;
    QTest::newRow("is empty 6 neighbour mines") << Cell::State::empty << 6 << 0;
    QTest::newRow("is empty 7 neighbour mines") << Cell::State::empty << 7 << 0;
    QTest::newRow("is empty 8 neighbour mines") << Cell::State::empty << 8 << 0;
}

void TestCell::signal_uncoverAreaWithNoMines()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, countOfNeighbourMines);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);
    obj.setCountOfNeighbourMines(countOfNeighbourMines);

    QSignalSpy spy(&obj, &Cell::uncoverAreaWithNoMines);

    QTest::mouseClick(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_uncoverNotFlaggedNeighbours_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("countOfNeighbourMines");
    QTest::addColumn<int>("countOfFlaggedNeighbours");
    QTest::addColumn<int>("result");

    QTest::newRow("has mine 0 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 0 << 0 << 1;
    QTest::newRow("has mine 0 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 0 << 1 << 0;
    QTest::newRow("has mine 0 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 0 << 2 << 0;
    QTest::newRow("has mine 0 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 0 << 3 << 0;
    QTest::newRow("has mine 0 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 0 << 4 << 0;
    QTest::newRow("has mine 0 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 0 << 5 << 0;
    QTest::newRow("has mine 0 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 0 << 6 << 0;
    QTest::newRow("has mine 0 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 0 << 7 << 0;
    QTest::newRow("has mine 0 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 0 << 8 << 0;

    QTest::newRow("has mine 1 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 1 << 0 << 0;
    QTest::newRow("has mine 1 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 1 << 1 << 1;
    QTest::newRow("has mine 1 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 1 << 2 << 0;
    QTest::newRow("has mine 1 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 1 << 3 << 0;
    QTest::newRow("has mine 1 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 1 << 4 << 0;
    QTest::newRow("has mine 1 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 1 << 5 << 0;
    QTest::newRow("has mine 1 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 1 << 6 << 0;
    QTest::newRow("has mine 1 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 1 << 7 << 0;
    QTest::newRow("has mine 1 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 1 << 8 << 0;

    QTest::newRow("has mine 2 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 2 << 0 << 0;
    QTest::newRow("has mine 2 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 2 << 1 << 0;
    QTest::newRow("has mine 2 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 2 << 2 << 1;
    QTest::newRow("has mine 2 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 2 << 3 << 0;
    QTest::newRow("has mine 2 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 2 << 4 << 0;
    QTest::newRow("has mine 2 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 2 << 5 << 0;
    QTest::newRow("has mine 2 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 2 << 6 << 0;
    QTest::newRow("has mine 2 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 2 << 7 << 0;
    QTest::newRow("has mine 2 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 2 << 8 << 0;

    QTest::newRow("has mine 3 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 3 << 0 << 0;
    QTest::newRow("has mine 3 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 3 << 1 << 0;
    QTest::newRow("has mine 3 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 3 << 2 << 0;
    QTest::newRow("has mine 3 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 3 << 3 << 1;
    QTest::newRow("has mine 3 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 3 << 4 << 0;
    QTest::newRow("has mine 3 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 3 << 5 << 0;
    QTest::newRow("has mine 3 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 3 << 6 << 0;
    QTest::newRow("has mine 3 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 3 << 7 << 0;
    QTest::newRow("has mine 3 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 3 << 8 << 0;

    QTest::newRow("has mine 4 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 4 << 0 << 0;
    QTest::newRow("has mine 4 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 4 << 1 << 0;
    QTest::newRow("has mine 4 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 4 << 2 << 0;
    QTest::newRow("has mine 4 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 4 << 3 << 0;
    QTest::newRow("has mine 4 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 4 << 4 << 1;
    QTest::newRow("has mine 4 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 4 << 5 << 0;
    QTest::newRow("has mine 4 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 4 << 6 << 0;
    QTest::newRow("has mine 4 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 4 << 7 << 0;
    QTest::newRow("has mine 4 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 4 << 8 << 0;

    QTest::newRow("has mine 5 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 5 << 0 << 0;
    QTest::newRow("has mine 5 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 5 << 1 << 0;
    QTest::newRow("has mine 5 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 5 << 2 << 0;
    QTest::newRow("has mine 5 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 5 << 3 << 0;
    QTest::newRow("has mine 5 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 5 << 4 << 0;
    QTest::newRow("has mine 5 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 5 << 5 << 1;
    QTest::newRow("has mine 5 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 5 << 6 << 0;
    QTest::newRow("has mine 5 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 5 << 7 << 0;
    QTest::newRow("has mine 5 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 5 << 8 << 0;

    QTest::newRow("has mine 6 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 6 << 0 << 0;
    QTest::newRow("has mine 6 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 6 << 1 << 0;
    QTest::newRow("has mine 6 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 6 << 2 << 0;
    QTest::newRow("has mine 6 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 6 << 3 << 0;
    QTest::newRow("has mine 6 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 6 << 4 << 0;
    QTest::newRow("has mine 6 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 6 << 5 << 0;
    QTest::newRow("has mine 6 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 6 << 6 << 1;
    QTest::newRow("has mine 6 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 6 << 7 << 0;
    QTest::newRow("has mine 6 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 6 << 8 << 0;

    QTest::newRow("has mine 7 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 7 << 0 << 0;
    QTest::newRow("has mine 7 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 7 << 1 << 0;
    QTest::newRow("has mine 7 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 7 << 2 << 0;
    QTest::newRow("has mine 7 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 7 << 3 << 0;
    QTest::newRow("has mine 7 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 7 << 4 << 0;
    QTest::newRow("has mine 7 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 7 << 5 << 0;
    QTest::newRow("has mine 7 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 7 << 6 << 0;
    QTest::newRow("has mine 7 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 7 << 7 << 1;
    QTest::newRow("has mine 7 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 7 << 8 << 0;

    QTest::newRow("has mine 8 neighbour mines 0 flagged neighbours")
            << Cell::State::mine << 8 << 0 << 0;
    QTest::newRow("has mine 8 neighbour mines 1 flagged neighbours")
            << Cell::State::mine << 8 << 1 << 0;
    QTest::newRow("has mine 8 neighbour mines 2 flagged neighbours")
            << Cell::State::mine << 8 << 2 << 0;
    QTest::newRow("has mine 8 neighbour mines 3 flagged neighbours")
            << Cell::State::mine << 8 << 3 << 0;
    QTest::newRow("has mine 8 neighbour mines 4 flagged neighbours")
            << Cell::State::mine << 8 << 4 << 0;
    QTest::newRow("has mine 8 neighbour mines 5 flagged neighbours")
            << Cell::State::mine << 8 << 5 << 0;
    QTest::newRow("has mine 8 neighbour mines 6 flagged neighbours")
            << Cell::State::mine << 8 << 6 << 0;
    QTest::newRow("has mine 8 neighbour mines 7 flagged neighbours")
            << Cell::State::mine << 8 << 7 << 0;
    QTest::newRow("has mine 8 neighbour mines 8 flagged neighbours")
            << Cell::State::mine << 8 << 8 << 1;

    QTest::newRow("is empty 0 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 0 << 0 << 1;
    QTest::newRow("is empty 0 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 0 << 1 << 0;
    QTest::newRow("is empty 0 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 0 << 2 << 0;
    QTest::newRow("is empty 0 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 0 << 3 << 0;
    QTest::newRow("is empty 0 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 0 << 4 << 0;
    QTest::newRow("is empty 0 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 0 << 5 << 0;
    QTest::newRow("is empty 0 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 0 << 6 << 0;
    QTest::newRow("is empty 0 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 0 << 7 << 0;
    QTest::newRow("is empty 0 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 0 << 8 << 0;

    QTest::newRow("is empty 1 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 1 << 0 << 0;
    QTest::newRow("is empty 1 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 1 << 1 << 1;
    QTest::newRow("is empty 1 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 1 << 2 << 0;
    QTest::newRow("is empty 1 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 1 << 3 << 0;
    QTest::newRow("is empty 1 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 1 << 4 << 0;
    QTest::newRow("is empty 1 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 1 << 5 << 0;
    QTest::newRow("is empty 1 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 1 << 6 << 0;
    QTest::newRow("is empty 1 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 1 << 7 << 0;
    QTest::newRow("is empty 1 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 1 << 8 << 0;

    QTest::newRow("is empty 2 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 2 << 0 << 0;
    QTest::newRow("is empty 2 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 2 << 1 << 0;
    QTest::newRow("is empty 2 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 2 << 2 << 1;
    QTest::newRow("is empty 2 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 2 << 3 << 0;
    QTest::newRow("is empty 2 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 2 << 4 << 0;
    QTest::newRow("is empty 2 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 2 << 5 << 0;
    QTest::newRow("is empty 2 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 2 << 6 << 0;
    QTest::newRow("is empty 2 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 2 << 7 << 0;
    QTest::newRow("is empty 2 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 2 << 8 << 0;

    QTest::newRow("is empty 3 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 3 << 0 << 0;
    QTest::newRow("is empty 3 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 3 << 1 << 0;
    QTest::newRow("is empty 3 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 3 << 2 << 0;
    QTest::newRow("is empty 3 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 3 << 3 << 1;
    QTest::newRow("is empty 3 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 3 << 4 << 0;
    QTest::newRow("is empty 3 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 3 << 5 << 0;
    QTest::newRow("is empty 3 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 3 << 6 << 0;
    QTest::newRow("is empty 3 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 3 << 7 << 0;
    QTest::newRow("is empty 3 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 3 << 8 << 0;

    QTest::newRow("is empty 4 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 4 << 0 << 0;
    QTest::newRow("is empty 4 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 4 << 1 << 0;
    QTest::newRow("is empty 4 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 4 << 2 << 0;
    QTest::newRow("is empty 4 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 4 << 3 << 0;
    QTest::newRow("is empty 4 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 4 << 4 << 1;
    QTest::newRow("is empty 4 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 4 << 5 << 0;
    QTest::newRow("is empty 4 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 4 << 6 << 0;
    QTest::newRow("is empty 4 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 4 << 7 << 0;
    QTest::newRow("is empty 4 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 4 << 8 << 0;

    QTest::newRow("is empty 5 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 5 << 0 << 0;
    QTest::newRow("is empty 5 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 5 << 1 << 0;
    QTest::newRow("is empty 5 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 5 << 2 << 0;
    QTest::newRow("is empty 5 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 5 << 3 << 0;
    QTest::newRow("is empty 5 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 5 << 4 << 0;
    QTest::newRow("is empty 5 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 5 << 5 << 1;
    QTest::newRow("is empty 5 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 5 << 6 << 0;
    QTest::newRow("is empty 5 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 5 << 7 << 0;
    QTest::newRow("is empty 5 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 5 << 8 << 0;

    QTest::newRow("is empty 6 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 6 << 0 << 0;
    QTest::newRow("is empty 6 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 6 << 1 << 0;
    QTest::newRow("is empty 6 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 6 << 2 << 0;
    QTest::newRow("is empty 6 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 6 << 3 << 0;
    QTest::newRow("is empty 6 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 6 << 4 << 0;
    QTest::newRow("is empty 6 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 6 << 5 << 0;
    QTest::newRow("is empty 6 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 6 << 6 << 1;
    QTest::newRow("is empty 6 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 6 << 7 << 0;
    QTest::newRow("is empty 6 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 6 << 8 << 0;

    QTest::newRow("is empty 7 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 7 << 0 << 0;
    QTest::newRow("is empty 7 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 7 << 1 << 0;
    QTest::newRow("is empty 7 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 7 << 2 << 0;
    QTest::newRow("is empty 7 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 7 << 3 << 0;
    QTest::newRow("is empty 7 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 7 << 4 << 0;
    QTest::newRow("is empty 7 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 7 << 5 << 0;
    QTest::newRow("is empty 7 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 7 << 6 << 0;
    QTest::newRow("is empty 7 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 7 << 7 << 1;
    QTest::newRow("is empty 7 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 7 << 8 << 0;

    QTest::newRow("is empty 8 neighbour mines 0 flagged neighbours")
            << Cell::State::empty << 8 << 0 << 0;
    QTest::newRow("is empty 8 neighbour mines 1 flagged neighbours")
            << Cell::State::empty << 8 << 1 << 0;
    QTest::newRow("is empty 8 neighbour mines 2 flagged neighbours")
            << Cell::State::empty << 8 << 2 << 0;
    QTest::newRow("is empty 8 neighbour mines 3 flagged neighbours")
            << Cell::State::empty << 8 << 3 << 0;
    QTest::newRow("is empty 8 neighbour mines 4 flagged neighbours")
            << Cell::State::empty << 8 << 4 << 0;
    QTest::newRow("is empty 8 neighbour mines 5 flagged neighbours")
            << Cell::State::empty << 8 << 5 << 0;
    QTest::newRow("is empty 8 neighbour mines 6 flagged neighbours")
            << Cell::State::empty << 8 << 6 << 0;
    QTest::newRow("is empty 8 neighbour mines 7 flagged neighbours")
            << Cell::State::empty << 8 << 7 << 0;
    QTest::newRow("is empty 8 neighbour mines 8 flagged neighbours")
            << Cell::State::empty << 8 << 8 << 1;
}

void TestCell::signal_uncoverNotFlaggedNeighbours()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, countOfNeighbourMines);
    QFETCH(int, countOfFlaggedNeighbours);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);
    obj.setCountOfNeighbourMines(countOfNeighbourMines);

    for(int i = 0; i < countOfFlaggedNeighbours; ++i) {
        obj.increaseCountOfFlaggedNeighbours();
    }

    QSignalSpy spy(&obj, &Cell::uncoverNotFlaggedNeighbours);

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_pressed_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_pressed()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::pressed);

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::qWait(delayClickRightAndLeftTogether);

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_released_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_released()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);
    obj.setCountOfNeighbourMines(1);

    QSignalSpy spy(&obj, &Cell::released);

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_pressNeighbours_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_pressNeighbours()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);

    QSignalSpy spy(&obj, &Cell::pressNeighbours);

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void TestCell::signal_releaseNeighbours_data()
{
    QTest::addColumn<Cell::State>("cellState");
    QTest::addColumn<int>("result");
    QTest::newRow("has mine") << Cell::State::mine << 1;
    QTest::newRow("is empty") << Cell::State::empty << 1;
}

void TestCell::signal_releaseNeighbours()
{
    QFETCH(Cell::State, cellState);
    QFETCH(int, result);

    CellInputHandler filter;
    Cell obj{ cellState };
    obj.installEventFilter(&filter);
    obj.setCountOfNeighbourMines(1);

    QSignalSpy spy(&obj, &Cell::releaseNeighbours);

    QTest::mousePress(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mousePress(&obj, Qt::RightButton, Qt::NoModifier,
                      obj.rect().center());
    QTest::mouseRelease(&obj, Qt::LeftButton, Qt::NoModifier,
                      obj.rect().center());

    QCOMPARE(spy.count(), result);
}

void doNRightClicks(Cell &cell, int n)
{
    for(int i = 0; i < n; ++i) {
        QTest::mousePress(&cell, Qt::RightButton, Qt::NoModifier,
                          cell.rect().center());
        QTest::qWait(delayClickRightAndLeftTogether);
        QTest::mouseRelease(&cell, Qt::RightButton, Qt::NoModifier,
                          cell.rect().center());
    }
}

QTEST_MAIN(TestCell)
