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
