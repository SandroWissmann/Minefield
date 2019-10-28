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
