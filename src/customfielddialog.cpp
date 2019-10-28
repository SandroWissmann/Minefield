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

#include "customfielddialog.h"
#include "ui_customfielddialog.h"

#include <QRegExpValidator>

#include <limits>
#include <algorithm>

#include <QDebug>

CustomFieldDialog::CustomFieldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomFieldDialog)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);

    QRegExp regEx("[0-9]{0, 40}");
    ui->heightLineEdit->setValidator(
                new QRegExpValidator(regEx, ui->heightLineEdit));
    ui->widthLineEdit->setValidator(
                new QRegExpValidator(regEx, ui->widthLineEdit));
    ui->minesLineEdit->setValidator(
                new QRegExpValidator(regEx, ui->minesLineEdit));

    ui->heightLineEdit->setText(
                QString::number(mGameSettings.minefieldCustomHeight()));
    ui->widthLineEdit->setText(
                QString::number(mGameSettings.minefieldCustomWidth()));
    ui->minesLineEdit->setText(
                QString::number(mGameSettings.minefieldCustomCountOfMines()));

    connect(this, &CustomFieldDialog::accepted,
            this, &CustomFieldDialog::saveData);
}

CustomFieldDialog::~CustomFieldDialog()
{
    delete ui;
}

void CustomFieldDialog::saveData()
{
    auto minHeight = mGameSettings.beginnerMineFieldHeight();
    auto minWidth = mGameSettings.beginnerMineFieldWidth();
    auto minCountOfMines = mGameSettings.countOfMines();

    constexpr auto maxHeight = 24;
    constexpr auto maxWidth = 30;

    auto height = limitInput(minHeight, maxHeight, ui->heightLineEdit->text());
    auto width = limitInput(minWidth, maxWidth, ui->widthLineEdit->text());


    const auto maxCountOfMines =
            (height * width) - (height + width - 1);


    auto countOfMines = limitInput(
                minCountOfMines, maxCountOfMines, ui->minesLineEdit->text());

    mGameSettings.setMinefieldCustomHeight(height);
    mGameSettings.setMinefieldCustomWidth(width);
    mGameSettings.setMinefieldCustomCountOfMines(countOfMines);
}

int CustomFieldDialog::limitInput(
        int minValue, int maxValue, const QString &input)
{
    constexpr auto maxIntSize = std::numeric_limits<int>::max();
    const auto maxLengthOfInt = QString::number(maxIntSize).length();

    if(input.isEmpty()) {
        return minValue;
    }
    if(input.size() > maxLengthOfInt) {
        return minValue;
    }
    if(input.toLong() > maxIntSize) {
        return minValue;
    }
    return std::clamp(input.toInt(), minValue, maxValue);
}
