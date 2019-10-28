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
