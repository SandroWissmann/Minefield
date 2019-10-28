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

#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(int recordTime, QWidget *parent)
    : QDialog(parent),
    mRecordTime{ recordTime },
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);

    QString part;
    switch(mGameSettings.difficulty()){
    case GameSettings::Difficulty::beginner:
        part = tr("beginner");
        break;
    case GameSettings::Difficulty::intermediate:
        part = tr("intermediate");
        break;
    case GameSettings::Difficulty::expert:
        part = tr("expert");
        break;
    case GameSettings::Difficulty::custom:
        break;
    }

    ui->textEdit->setText(tr("You have the fastest time for %1 level. "
                             "Please type your name:").arg(part));
    ui->textEdit->viewport()->setAutoFillBackground(false);

    connect(this, &WinDialog::finished, this, &WinDialog::saveData);
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::saveData()
{
    switch(mGameSettings.difficulty()){
    case GameSettings::Difficulty::beginner:
        mGameSettings.setBeginnerTime(mRecordTime);
        mGameSettings.setBeginnerName(ui->playerNameLineEdit->text());
        break;
    case GameSettings::Difficulty::intermediate:
        mGameSettings.setIntermediateTime(mRecordTime);
        mGameSettings.setIntermediateName(ui->playerNameLineEdit->text());
        break;
    case GameSettings::Difficulty::expert:
        mGameSettings.setExpertTime(mRecordTime);
        mGameSettings.setExpertName(ui->playerNameLineEdit->text());
        break;
    case GameSettings::Difficulty::custom:
        break;
    }
}
