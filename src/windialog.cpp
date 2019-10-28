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
