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

#include "mainwindow.h"

#include "game.h"
#include "besttimesdialog.h"
#include "customfielddialog.h"

#include <QDebug>

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mCustomCheckedOnStart{ false },
      mGame{ new Game{ this } }
{
    setWindowTitle("Minefield");
    setCentralWidget(mGame);

    createActions();
    createMenus();

    if(mGameSettings.difficulty() == GameSettings::Difficulty::beginner) {
        mBeginnerAction->setChecked(true);
        makeBeginnerMinefield();
    }
    if(mGameSettings.difficulty() == GameSettings::Difficulty::intermediate) {
        mIntermediateAction->setChecked(true);
        makeIntermediateMinefield();
    }
    if(mGameSettings.difficulty() == GameSettings::Difficulty::expert) {
        mExpertAction->setChecked(true);
        makeExpertMinefield();
    }
    if(mGameSettings.difficulty() == GameSettings::Difficulty::custom) {
        mCustomAction->setChecked(true);
        mCustomCheckedOnStart = true;
        makeCustomMinefield();
    }
    if(mGameSettings.questionMarksOn()) {
        mQuestionMarksAction->setChecked(true);
    }
    if(mGameSettings.colorOn()) {
        mColorAction->setChecked(true);
    }
    toggleQuestionMarks();
    toggleColor();
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::LayoutRequest) {
        setFixedSize(sizeHint());
    }
    return QMainWindow::event(event);
}

void MainWindow::makeNewMinefield()
{
    mGame->makeNewMinefield(
            mGameSettings.minefieldWidth(),
            mGameSettings.minefieldHeight(),
            mGameSettings.countOfMines());
    update();
}

void MainWindow::makeBeginnerMinefield()
{
    mGameSettings.setDifficulty(GameSettings::Difficulty::beginner);
    makeNewMinefield();
    update();
}

void MainWindow::makeIntermediateMinefield()
{
    mGameSettings.setDifficulty(GameSettings::Difficulty::intermediate);
    makeNewMinefield();
    update();
}

void MainWindow::makeExpertMinefield()
{
    mGameSettings.setDifficulty(GameSettings::Difficulty::expert);
    makeNewMinefield();
    update();
}

void MainWindow::makeCustomMinefield()
{
    if(!mCustomCheckedOnStart) {
        CustomFieldDialog dialog{ this};
        dialog.exec();
    }
    else {
        mCustomCheckedOnStart = false;
    }

    mGameSettings.setDifficulty(GameSettings::Difficulty::custom);
    makeNewMinefield();
    update();

}

void MainWindow::toggleQuestionMarks()
{
    if(mQuestionMarksAction->isChecked()) {       
        mGameSettings.toggleQuestionMarks(true);
        mQuestionMarksAction->setChecked(true);
        mGame->toggleNewQuesionMarksInCells(true);
    }
    else {
        mGameSettings.toggleQuestionMarks(false);
        mQuestionMarksAction->setChecked(false);
        mGame->toggleNewQuesionMarksInCells(false);
    }
}

void MainWindow::toggleColor()
{
    if(mColorAction->isChecked()) {
        mGameSettings.toggleColor(true);
        mColorAction->setChecked(true);
        mGame->toggleColor(true);
    }
    else {
        mGameSettings.toggleColor(false);
        mColorAction->setChecked(false);
        mGame->toggleColor(false);
    }
}

void MainWindow::showBestTimes()
{
    BestTimesDialog dialog{ this};
    dialog.exec();
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("About"),
        tr("Free cross platform minesweeper clone based on:\n"
           "http://www.minesweeper.info/downloads/Winmine95.html\n"),
           QMessageBox::Ok);
}

void MainWindow::createActions()
{
    mNewAction = new QAction{tr("&New"), this};
    mNewAction->setShortcut(Qt::Key::Key_F2);
    connect(mNewAction, &QAction::triggered,
            this, &MainWindow::makeNewMinefield);

    mBeginnerAction = new QAction{tr("&Beginner"), this};
    mBeginnerAction->setCheckable(true);  
    connect(mBeginnerAction, &QAction::triggered,
            this, &MainWindow::makeBeginnerMinefield);

    mIntermediateAction = new QAction{tr("&Intermediate"), this};
    mIntermediateAction->setCheckable(true);
    connect(mIntermediateAction, &QAction::triggered,
        this, &MainWindow::makeIntermediateMinefield);

    mExpertAction = new QAction{tr("&Expert"), this};
    mExpertAction->setCheckable(true);
    connect(mExpertAction, &QAction::triggered,
            this, &MainWindow::makeExpertMinefield);

    mCustomAction = new QAction{tr("&Custom..."), this};
    mCustomAction->setCheckable(true);
    connect(mCustomAction, &QAction::triggered,
            this, &MainWindow::makeCustomMinefield);

    mDifficultyActionGroup = new QActionGroup(this);

    mQuestionMarksAction = new QAction{tr("&Marks (?)"), this};
    mQuestionMarksAction->setCheckable(true);
    connect(mQuestionMarksAction, &QAction::toggled,
            this, &MainWindow::toggleQuestionMarks);

    mColorAction = new QAction{tr("C&olor"), this};
    mColorAction->setCheckable(true);
    connect(mColorAction, &QAction::triggered,
            this, &MainWindow::toggleColor);

    mBestTimesAction = new QAction{tr("Best &Times..."), this};
    connect(mBestTimesAction, &QAction::triggered,
            this, &MainWindow::showBestTimes);

    mExitAction = new QAction{tr("E&xit"), this};
    connect(mExitAction, &QAction::triggered,
            QApplication::instance(), &QApplication::closeAllWindows);

    mAboutAction = new QAction{tr("&About"), this};
    connect(mAboutAction, &QAction::triggered,
            this, &MainWindow::about);

    mAboutQtAction = new QAction{tr("About &Qt"), this};
    connect(mAboutQtAction, &QAction::triggered,
            QApplication::instance(), &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    mGameMenu = menuBar()->addMenu(tr("&Game"));
    mGameMenu->addAction(mNewAction);
    mGameMenu->addSeparator();

    mDifficultyActionGroup->setExclusive(true);
    mDifficultyActionGroup->addAction(mBeginnerAction);
    mDifficultyActionGroup->addAction(mIntermediateAction);
    mDifficultyActionGroup->addAction(mExpertAction);
    mDifficultyActionGroup->addAction(mCustomAction);

    mGameMenu->addAction(mBeginnerAction);
    mGameMenu->addAction(mIntermediateAction);
    mGameMenu->addAction(mExpertAction);
    mGameMenu->addAction(mCustomAction);
    mGameMenu->addSeparator();
    mGameMenu->addAction(mQuestionMarksAction);
    mGameMenu->addAction(mColorAction);
    mGameMenu->addSeparator();
    mGameMenu->addAction(mBestTimesAction);
    mGameMenu->addAction(mExitAction);

    mHelpMenu = menuBar()->addMenu(tr("&Help"));
    mHelpMenu->addAction(mAboutAction);
    mHelpMenu->addAction(mAboutQtAction);
}
