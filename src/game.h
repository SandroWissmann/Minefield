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

#ifndef GAME_H
#define GAME_H

#include "gamesettings.h"

#include <QWidget>

class Minefield;
class LcdDisplay;
class SmileyPushButton;

class QFrame;
class QTime;
class QTimer;

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);

    int mineFieldWidth();
    int mineFieldHeight();
    int mineFieldCountOfMines();
    void makeNewMinefield(int width, int height, int countOfMines);

signals:
    void toggleColor(int value);
    void toggleNewQuesionMarksInCells(bool value);

private slots:
    void win();
    void startTimer();
    void stopTimer();
    void updateLcdDisplayElapsedTime();
    void resetLcdDisplayElapsedTime();

    void makeNewMinefieldWithSameParameters();
private:
    void connectToMinefield();

    bool mInsideRender;

    GameSettings mGameSettings;

    LcdDisplay *mLcdDisplayMinesLeft;
    LcdDisplay *mLcdDisplayElapsedTime;
    SmileyPushButton *mSmileyPushButton;
    Minefield *mMinefield;

    QFrame *mTopFrame;
    QFrame *mBottomFrame;
    QFrame *mMainFrame;

    QTime *mElapsedTime;
    QTimer *mTimer;
};

#endif // GAME_H
