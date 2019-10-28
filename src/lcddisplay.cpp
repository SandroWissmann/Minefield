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

#include "lcddisplay.h"

#include "converttograyscale.h"

#include <QPainter>
#include <QDebug>

#include <algorithm>

LcdDisplay::LcdDisplay(QWidget *parent)
    : LcdDisplay(0, parent)
{  
}

LcdDisplay::LcdDisplay(int value, QWidget *parent)
    :QWidget{ parent },
     mColorOn{ true }
{
    auto image =  getImage(0);   // assume all images have same size
    auto h = image.size().height();
    auto w = image.size().width() * 3;
    setFixedSize(QSize{ w, h });

    setDisplayValue(value);
}

void LcdDisplay::setDisplayValue(int value)
{
    constexpr auto minDisplayValue = -99;
    constexpr auto maxDisplayValue = 999;

    mValue = std::clamp(value, minDisplayValue, maxDisplayValue);

    if(value < 0) {
        mDigit2 = -1;

        value *= -1;

        mDigit0 = value % 10;
        mDigit1 = value / 10;
    }
    else {
        mDigit0 = value % 10;
        value /= 10;
        mDigit1 = value % 10;
        mDigit2 = value / 10;
    }
    update();
}

int LcdDisplay::displayValue() const
{
    return mValue;
}

void LcdDisplay::toggleColor(int value)
{
    mColorOn = value;
    update();
}

void LcdDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    auto image0 = getImage(mDigit0);
    auto image1 = getImage(mDigit1);
    auto image2 = getImage(mDigit2);

    if(!mColorOn) {
        image0 = convertToGrayscale(image0);
        image1 = convertToGrayscale(image1);
        image2 = convertToGrayscale(image2);
    }

    auto image2Rect = rect();
    image2Rect.setWidth(image2.width());

    auto image1Rect = rect();   
    image1Rect.setX(image1Rect.x() + image2.width());
    image1Rect.setWidth(image1.width());

    auto image0Rect = rect();  
    image0Rect.setX(image0Rect.x() + image2.width() + image1.width());
    image0Rect.setWidth(image0.width());

    QPainter painter{ this };
    painter.drawImage(image2Rect, image2);
    painter.drawImage(image1Rect, image1);
    painter.drawImage(image0Rect, image0);
}

QImage LcdDisplay::getImage(int digit)
{
    switch(digit) {
    case -1:
        return QImage{":/ressources/display_negative.png"};
    case 0:
        return QImage{":/ressources/display_0.png"};
    case 1:
        return QImage{":/ressources/display_1.png"};
    case 2:
        return QImage{":/ressources/display_2.png"};
    case 3:
        return QImage{":/ressources/display_3.png"};
    case 4:
        return QImage{":/ressources/display_4.png"};
    case 5:
        return QImage{":/ressources/display_5.png"};
    case 6:
        return QImage{":/ressources/display_6.png"};
    case 7:
        return QImage{":/ressources/display_7.png"};
    case 8:
        return QImage{":/ressources/display_8.png"};
    case 9:
        return QImage{":/ressources/display_9.png"};
    default:
        return QImage{":/ressources/display_0.png"};
    }
}
