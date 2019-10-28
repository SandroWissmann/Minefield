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
