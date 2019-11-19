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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamesettings.h"

#include <QMainWindow>

class QAction;
class QMenu;
class QActionGroup;
class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    bool event(QEvent *event) override;

private slots:
    void makeNewMinefield();
    void makeBeginnerMinefield();
    void makeIntermediateMinefield();
    void makeExpertMinefield();
    void makeCustomMinefield();
    void toggleQuestionMarks();
    void toggleColor();
    void showBestTimes();

    void about();
private:
    void createActions();
    void createMenus();

    bool mCustomCheckedOnStart{ false };

    GameSettings mGameSettings;

    Game *mGame;

    QMenu *mGameMenu{};
    QMenu *mHelpMenu{};

    // Game Menu
    QAction *mNewAction{};

    QAction *mBeginnerAction{};
    QAction *mIntermediateAction{};
    QAction *mExpertAction{};
    QAction *mCustomAction{};

    QActionGroup *mDifficultyActionGroup{};

    QAction *mQuestionMarksAction{};
    QAction *mColorAction{};
    QAction *mBestTimesAction{};
    QAction *mExitAction{};

    // Help Menu
    QAction *mAboutAction{};
    QAction *mAboutQtAction{};  
};

#endif // MAINWINDOW_H
