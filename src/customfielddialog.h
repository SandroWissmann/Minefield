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


#ifndef CUSTOMFIELDDIALOG_H
#define CUSTOMFIELDDIALOG_H

#include "gamesettings.h"

#include <QDialog>

namespace Ui {
class CustomFieldDialog;
}

class CustomFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomFieldDialog(QWidget *parent = nullptr);
    ~CustomFieldDialog() override;

    CustomFieldDialog(const CustomFieldDialog&) = delete;
    CustomFieldDialog(CustomFieldDialog&&) = delete;
    CustomFieldDialog& operator=(const CustomFieldDialog&) = delete;
    CustomFieldDialog& operator=(CustomFieldDialog&&) = delete;

private slots:
    void saveData();

private:
    int limitInput(int minValue, int maxValue, const QString &input);

    Ui::CustomFieldDialog *ui;
    GameSettings mGameSettings;
};

#endif // CUSTOMFIELDDIALOG_H
