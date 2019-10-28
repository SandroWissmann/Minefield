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

    bool mCustomCheckedOnStart;

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
