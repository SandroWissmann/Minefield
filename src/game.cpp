#include "game.h"

#include "lcddisplay.h"
#include "smileypushbutton.h"
#include "minefield.h"
#include "cellutility.h"
#include "windialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QFrame>
#include <QTime>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

#include <QDebug>

Game::Game(QWidget *parent)
    :QWidget(parent),
    mInsideRender{ false },
    mLcdDisplayMinesLeft{ new LcdDisplay},
    mLcdDisplayElapsedTime{ new LcdDisplay },
    mSmileyPushButton{ new SmileyPushButton },
    mMinefield{ nullptr },
    mTopFrame{ new QFrame },
    mBottomFrame{ new QFrame },
    mMainFrame{ new QFrame },
    mElapsedTime{ new QTime },
    mTimer{ new QTimer{ this }}
{
    connect(mTimer, &QTimer::timeout,
            this, &Game::updateLcdDisplayElapsedTime);

    connect(mSmileyPushButton, &SmileyPushButton::pressed,
            this, &Game::makeNewMinefieldWithSameParameters);
    connect(mSmileyPushButton, &SmileyPushButton::pressed,
            mSmileyPushButton, &SmileyPushButton::setSmile);

    connect(this, &Game::toggleColor,
            mSmileyPushButton, &SmileyPushButton::toggleColor);
    connect(this, &Game::toggleColor,
            mLcdDisplayMinesLeft, &LcdDisplay::toggleColor);
    connect(this, &Game::toggleColor,
            mLcdDisplayElapsedTime, &LcdDisplay::toggleColor);

    mMainFrame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    mMainFrame->setLineWidth(3);

    mTopFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mTopFrame->setLineWidth(3);

    mBottomFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mBottomFrame->setLineWidth(3);

    auto topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addWidget(mLcdDisplayMinesLeft);
    topLayout->setAlignment(mLcdDisplayMinesLeft, Qt::AlignLeft);
    topLayout->addWidget(mSmileyPushButton);
    topLayout->addWidget(mLcdDisplayElapsedTime);
    topLayout->setAlignment(mLcdDisplayElapsedTime, Qt::AlignRight);
    mTopFrame->setLayout(topLayout);

    auto bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setContentsMargins(0,0,0,0);
    mBottomFrame->setLayout(bottomLayout);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(mTopFrame);
    mainLayout->addWidget(mBottomFrame);

    mMainFrame->setLayout(mainLayout);

    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(mMainFrame);

    setLayout(layout);
}

int Game::mineFieldWidth()
{
    if(mMinefield) {
        return mMinefield->fieldWidth();
    }
    return 0;
}

int Game::mineFieldHeight()
{
    if(mMinefield) {
        return mMinefield->fieldHeight();
    }
    return 0;
}

int Game::mineFieldCountOfMines()
{
    if(mMinefield) {
        return mMinefield->countOfMines();
    }
    return 0;
}

void Game::makeNewMinefield(int width, int height, int countOfMines)
{
    mLcdDisplayMinesLeft->setDisplayValue(countOfMines);


    auto cells = createCells(width, height, countOfMines);
    randomizeCells(cells);
    auto newMinefield = new Minefield{ cells, width, height };
    auto returnItem = mBottomFrame->layout()->replaceWidget(
                mMinefield, newMinefield);

    if(!returnItem) {
        mBottomFrame->layout()->addWidget(newMinefield);
    }
    else {
        delete mMinefield;
        delete returnItem;
    }

    mMinefield = newMinefield;

    stopTimer();

    mLcdDisplayMinesLeft->setDisplayValue(mMinefield->countOfMines());
    mLcdDisplayElapsedTime->setDisplayValue(0);
    mSmileyPushButton->setSmile();

    connectToMinefield();
    update();
}

void Game::win()
{   
    int recordTime = 0;
    switch(mGameSettings.difficulty()) {
        case GameSettings::Difficulty::beginner:
            recordTime = mGameSettings.beginnerTime();
            break;
        case GameSettings::Difficulty::intermediate:
            recordTime = mGameSettings.beginnerTime();
            break;
        case GameSettings::Difficulty::expert:
            recordTime = mGameSettings.beginnerTime();
            break;
        case GameSettings::Difficulty::custom:
            return;
    }

    if(mLcdDisplayElapsedTime->displayValue() < recordTime) {       
        WinDialog dialog{ mLcdDisplayElapsedTime->displayValue(), this};
        dialog.exec();
    }
}

void Game::startTimer()
{
    constexpr auto ms = 1000;
    mTimer->start(ms);
    mElapsedTime->restart();
}

void Game::stopTimer()
{
    mTimer->stop();
}

void Game::updateLcdDisplayElapsedTime()
{   
    constexpr auto divisorMsToS = 1000;
    mLcdDisplayElapsedTime->setDisplayValue(
                mElapsedTime->elapsed() / divisorMsToS);
}

void Game::resetLcdDisplayElapsedTime()
{
    mLcdDisplayElapsedTime->setDisplayValue(0);
}

void Game::makeNewMinefieldWithSameParameters()
{
    if(mMinefield == nullptr) {
        return;
    }

    auto width = mMinefield->fieldWidth();
    auto height = mMinefield->fieldHeight();
    auto minesCount = mMinefield->countOfMines();

    makeNewMinefield(width, height, minesCount);
}

void Game::connectToMinefield()
{
    connect(mMinefield, &Minefield::uncoveredFirstCell,
            this, &Game::startTimer);
    connect(mMinefield, &Minefield::mineExploded,
            this, &Game::stopTimer);
    connect(mMinefield, &Minefield::uncoveredAllSafeCells,
            this, &Game::stopTimer);
    connect(mMinefield, &Minefield::uncoveredAllSafeCells,
            this, &Game::win);

    connect(mMinefield, &Minefield::pressedCell,
            mSmileyPushButton, &SmileyPushButton::setOpen);
    connect(mMinefield, &Minefield::releasedCell,
            mSmileyPushButton, &SmileyPushButton::setSmile);
    connect(mMinefield, &Minefield::uncoveredEmptyCell,
            mSmileyPushButton, &SmileyPushButton::setSmile);


    connect(mMinefield, &Minefield::uncoveredAllSafeCells,
            [=](){
        disconnect(mMinefield, &Minefield::pressedCell,
                mSmileyPushButton, &SmileyPushButton::setOpen);
        disconnect(mMinefield, &Minefield::releasedCell,
                mSmileyPushButton, &SmileyPushButton::setSmile);
        disconnect(mMinefield, &Minefield::uncoveredEmptyCell,
                mSmileyPushButton, &SmileyPushButton::setSmile);
        mSmileyPushButton->setSunglasses();
    });

    connect(mMinefield, &Minefield::mineExploded,
            [=](){

        disconnect(mMinefield, &Minefield::pressedCell,
                mSmileyPushButton, &SmileyPushButton::setOpen);
        disconnect(mMinefield, &Minefield::releasedCell,
                mSmileyPushButton, &SmileyPushButton::setSmile);
        disconnect(mMinefield, &Minefield::uncoveredEmptyCell,
                mSmileyPushButton, &SmileyPushButton::setSmile);
        disconnect(mMinefield, &Minefield::uncoveredAllSafeCells,
                mSmileyPushButton, &SmileyPushButton::setSunglasses);
        mSmileyPushButton->setDead();
    });

    connect(mMinefield, &Minefield::minesLeftChanged,
        mLcdDisplayMinesLeft, &LcdDisplay::setDisplayValue);
    connect(this, &Game::toggleNewQuesionMarksInCells,
            mMinefield, &Minefield::toggleNewQuesionMarksInCells);
    connect(this, &Game::toggleColor,
            mMinefield, &Minefield::toggleColorInCells);
}
