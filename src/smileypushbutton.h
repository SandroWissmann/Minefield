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

    bool mPressed{ false };
    bool mColorOn{ true };
    DisplayType mDisplayType{ DisplayType::smile };
};

#endif // SMILEYPUSHBUTTON_H
