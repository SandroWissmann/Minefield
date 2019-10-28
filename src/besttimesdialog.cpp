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

#include "besttimesdialog.h"
#include "ui_besttimesdialog.h"

#include <QPushButton>

BestTimesDialog::BestTimesDialog(
        QWidget *parent)
        :QDialog(parent),
        ui(new Ui::BestTimesDialog)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);

    setLabelsTextFromSettings();

    connect(ui->buttonBox->button(QDialogButtonBox::Reset),
            &QPushButton::clicked, this, &BestTimesDialog::resetToDefaults);
}

BestTimesDialog::~BestTimesDialog()
{
    delete ui;
}

void BestTimesDialog::resetToDefaults()
{
    mGameSettings.setDefaultBeginnerName();
    mGameSettings.setDefaultIntermediateName();
    mGameSettings.setDefaultExpertName();
    mGameSettings.setDefaultBeginnerTime();
    mGameSettings.setDefaultIntermediateTime();
    mGameSettings.setDefaultExpertTime();   

    setLabelsTextFromSettings();
    update();
}

void BestTimesDialog::setLabelsTextFromSettings()
{
    ui->beginnerFastestTimeLabel->setNum(mGameSettings.beginnerTime());
    ui->intermediateFastestTimeLabel->setNum(mGameSettings.intermediateTime());
    ui->expertFastestTimeLabel->setNum(mGameSettings.expertTime());
    ui->beginnerPlayerLabel->setText(mGameSettings.beginnerName());
    ui->intermediatePlayerLabel->setText(mGameSettings.intermediateName());
    ui->expertPlayerLabel->setText(mGameSettings.expertName());
}
