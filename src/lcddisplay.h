#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <QWidget>

class LcdDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit LcdDisplay(QWidget *parent = nullptr);
    LcdDisplay(int value, QWidget *parent = nullptr);

    void setDisplayValue(int value);
    [[nodiscard]] int displayValue() const;

public slots:
    void toggleColor(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage getImage(int digit);

    bool mColorOn;
    int mValue{ 0 };
    int mDigit0{ 0 };
    int mDigit1{ 0 };
    int mDigit2{ 0 };
};

#endif // LCDDISPLAY_H
