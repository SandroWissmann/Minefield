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
