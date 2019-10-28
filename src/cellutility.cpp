#include "cellutility.h"

#include "cell.h"

#include <QtGlobal>
#include <QDebug>

#include <random>

QVector<Cell* > createCells(int width, int height, int countOfMines)
{
    Q_ASSERT(width > 1);
    Q_ASSERT(height > 1);
    Q_ASSERT(countOfMines > 1);
    Q_ASSERT(countOfMines <= width * height);

    QVector<Cell *> cells;
    auto size = static_cast<int>(width * height);
    cells.reserve(size);

    for(auto i = 0; i < size; ++i) {
        if(i < countOfMines) {
            cells.push_back(new Cell(Cell::State::mine));
        }
        else {
            cells.push_back(new Cell(Cell::State::empty));
        }
    }
    return cells;
}

void randomizeCells(QVector<Cell *> &cells)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cells.begin(), cells.end(), g);
}

void connectCellsWithNeighbourCells(
        QVector<Cell *> &cells, int fieldWidth, int fieldHeight)
{
    for(auto i = 0; i < cells.size(); ++i) {
        connectCellWithNeighbourCells(cells, i, fieldWidth, fieldHeight);
        if(cells[i]->hasMine()) {
            continue;
        }
        auto neighbourMines =
                getMinesOfSourroundingCells(cells, i, fieldWidth, fieldHeight);
        cells[i]->setCountOfNeighbourMines(neighbourMines);
    }
}

void connectCellWithNeighbourCells(
        QVector<Cell *> &cells, int index, int fieldWidth, int fieldHeight)
{
    auto neigbourIndexes = getNeigbourIndexes(index, fieldWidth, fieldHeight);

    for(const auto neigbourIndex : neigbourIndexes) {
        QObject::connect(cells[index], &Cell::uncoverAreaWithNoMines,
                cells[neigbourIndex], &Cell::uncoverIfCoveredAndNoMine);

        QObject::connect(cells[index], &Cell::uncoverNotFlaggedNeighbours,
                cells[neigbourIndex], &Cell::uncoverIfNotFlagged);

        QObject::connect(cells[neigbourIndex], &Cell::flagged,
                cells[index], &Cell::increaseCountOfFlaggedNeighbours);

        QObject::connect(cells[neigbourIndex], &Cell::unflagged,
                cells[index], &Cell::decreaseCountOfFlaggedNeighbours);

        QObject::connect(cells[index], &Cell::pressNeighbours,
                cells[neigbourIndex], &Cell::pressIfCoveredOrQuestionmark);

        QObject::connect(cells[index], &Cell::releaseNeighbours,
                cells[neigbourIndex], &Cell::releaseIfCoveredOrQuestionmarkPressed);
    }
}

int getMinesOfSourroundingCells(
        QVector<Cell *> &cells, int index, int fieldWidth, int fieldHeight)
{
    auto mines = 0;

    auto neighbourIndexes = getNeigbourIndexes(index, fieldWidth, fieldHeight);

    for(const auto &neighbourIndex : neighbourIndexes) {
        if(cells[neighbourIndex]->hasMine()) {
            ++mines;
        }
    }
    return mines;
}

QVector<int> getNeigbourIndexes(int index, int fieldWidth, int fieldHeight)
{
    QVector<int> indexes;

    auto topLeft = index - fieldWidth - 1;
    auto top = index - fieldWidth;
    auto topRight = index - fieldWidth + 1;
    auto left = index - 1;
    auto right = index + 1;
    auto bottomLeft = index + fieldWidth - 1;
    auto bottom = index + fieldWidth;
    auto bottomRight = index + fieldWidth + 1;

    if (!isFirstRow(index, fieldWidth) &&
            !isFirstElementOfRow(index, fieldWidth)) {
        indexes.push_back(topLeft);
    }
    if (!isFirstRow(index, fieldWidth)) {
        indexes.push_back(top);
    }
    if (!isFirstRow(index, fieldWidth) &&
            !isLastElementOfRow(index, fieldWidth)) {
        indexes.push_back(topRight);
    }
    if (!isFirstElementOfRow(index, fieldWidth)) {
        indexes.push_back(left);
    }
    if (!isLastElementOfRow(index, fieldWidth)) {
        indexes.push_back(right);
    }
    if (!isLastRow(index, fieldWidth, fieldHeight) &&
            !isFirstElementOfRow(index, fieldWidth)) {
        indexes.push_back(bottomLeft);
    }
    if (!isLastRow(index, fieldWidth, fieldHeight)) {
        indexes.push_back(bottom);
    }
    if (!isLastRow(index, fieldWidth, fieldHeight) &&
            !isLastElementOfRow(index, fieldWidth)) {
        indexes.push_back(bottomRight);
    }

    return indexes;
}

bool isFirstRow(int index, int fieldWidth)
{
    return index / fieldWidth == 0;
}

bool isLastRow(int index, int fieldWidth, int fieldHeight)
{
    return index / fieldWidth == fieldHeight -1;
}

bool isFirstElementOfRow(int index, int fieldWidth)
{
    return index % fieldWidth == 0 || index == 0;
}

bool isLastElementOfRow(int index, int fieldWidth)
{
    return (index + 1) % fieldWidth == 0;
}

bool allSafeCellsUncovered(const QVector<Cell *> &cells)
{
    auto coveredEmpty = [](const auto &cell) {
        if(cell->hasMine()) {
            return false;
        }
        return cell->isCovered() || cell->isFLagged() ||
                cell->hasQuestionmark();
    };

    auto itCoveredEmptyCell =
            std::find_if(cells.begin(), cells.end(), coveredEmpty);

    return itCoveredEmptyCell == cells.end();
}
