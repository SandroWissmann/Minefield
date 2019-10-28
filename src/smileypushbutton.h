#ifndef SMILEYPUSHBUTTON_H
#define SMILEYPUSHBUTTON_H

#include <QPushButton>

class SmileyPushButton : public QPushButton
{
public:
    explicit SmileyPushButton(QWidget *parent = nullptr);

public slots:
    void toggleColor(int value);

    void setSmile();
    void setOpen();
    void setSunglasses();
    void setDead();

private slots:
    void setPressed();
    void setReleased();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    enum class DisplayType{
        smile,
        open,
        sunglasses,
        dead
    };

    QImage displayImage(DisplayType type);

    bool mPressed;
    bool mColorOn;
    DisplayType mDisplayType;
};

#endif // SMILEYPUSHBUTTON_H
