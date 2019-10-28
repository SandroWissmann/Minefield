#ifndef WINDIALOG_H
#define WINDIALOG_H

#include "gamesettings.h"

#include <QDialog>

namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT
public:
    WinDialog(int recordTime, QWidget *parent = nullptr);
    ~WinDialog() override;

    WinDialog(const WinDialog&) = delete;
    WinDialog(WinDialog&&) = delete;
    WinDialog& operator=(const WinDialog&) = delete;
    WinDialog& operator=(WinDialog&&) = delete;

private slots:
    void saveData();

private:
    GameSettings mGameSettings;
    int mRecordTime;
    Ui::WinDialog *ui;   
};

#endif // WINDIALOG_H
