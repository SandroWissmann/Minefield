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
