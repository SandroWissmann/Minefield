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

#ifndef BESTTIMESDIALOG_H
#define BESTTIMESDIALOG_H

#include "gamesettings.h"

#include <QDialog>

namespace Ui {
class BestTimesDialog;
}

class BestTimesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BestTimesDialog(
            QWidget *parent = nullptr);
    ~BestTimesDialog() override;

    BestTimesDialog(const BestTimesDialog&) = delete;
    BestTimesDialog(BestTimesDialog&&) = delete;
    BestTimesDialog& operator=(const BestTimesDialog&) = delete;
    BestTimesDialog& operator=(BestTimesDialog&&) = delete;

private slots:
    void resetToDefaults();

private:
    void setLabelsTextFromSettings();

    Ui::BestTimesDialog *ui;
    GameSettings mGameSettings;
};

#endif // BESTTIMESDIALOG_H
