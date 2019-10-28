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
