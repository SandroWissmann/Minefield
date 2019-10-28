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

#include "smileypushbutton.h"

#include "converttograyscale.h"

#include <QPainter>

#include <QDebug>

SmileyPushButton::SmileyPushButton(QWidget *parent)
    :QPushButton{ parent },
    mPressed{ false },
    mColorOn{ true },
    mDisplayType{ DisplayType::smile }
{
    connect(this, &SmileyPushButton::pressed,
            this, &SmileyPushButton::setPressed);

    connect(this, &SmileyPushButton::released,
            this, &SmileyPushButton::setReleased);

    setFixedSize(displayImage(mDisplayType).size());
}

void SmileyPushButton::toggleColor(int value)
{
    mColorOn = value;
    update();
}

void SmileyPushButton::setSmile()
{
    qDebug() << "set smile";

    mDisplayType = DisplayType::smile;
    update();
}

void SmileyPushButton::setOpen()
{
    mDisplayType = DisplayType::open;
    update();
}

void SmileyPushButton::setSunglasses()
{
    qDebug() << "set sunglasses";

    mDisplayType = DisplayType::sunglasses;
    update();
}

void SmileyPushButton::setDead()
{
    mDisplayType = DisplayType::dead;
    update();
}

void SmileyPushButton::setPressed()
{
    mPressed = true;
    update();
}

void SmileyPushButton::setReleased()
{
    mPressed = false;
    update();
}

void SmileyPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter{ this };

    auto image = displayImage(mDisplayType);

    if(!mColorOn) {
        image = convertToGrayscale(image);
    }

    painter.drawImage(rect(), image);

    auto posX = rect().x();
    auto posY = rect().y();
    auto w = image.width();
    auto h = image.height();


    QColor topAndLeftColor;
    QColor bottomAndRightColor;

    if(mPressed) {
        topAndLeftColor = Qt::GlobalColor::black;
        bottomAndRightColor = Qt::GlobalColor::white;
    }
    else {
        topAndLeftColor = Qt::GlobalColor::white;
        bottomAndRightColor = Qt::GlobalColor::black;
    }

    painter.setPen(QPen{ topAndLeftColor, 4 });
    painter.drawLine(posX, posY, posX + w, posY);
    painter.drawLine(posX, posY, posX, posY + h);

    painter.setPen(QPen{ bottomAndRightColor, 4 });
    painter.drawLine(posX + w, posY, posX + w, posY + h);
    painter.drawLine(posX, posY + h, posX + w, posY + h);

    painter.setPen(QPen{Qt::GlobalColor::gray, 1});
    painter.drawRect(posX, posY, posX + w, posY + h);
}

QImage SmileyPushButton::displayImage(SmileyPushButton::DisplayType type)
{
    switch(type){
        case DisplayType::smile:
            return QImage{":/ressources/smiley_smile.png"};
        case DisplayType::open:
            return QImage{":/ressources/smiley_open.png"};
        case DisplayType::sunglasses:
            return QImage{":/ressources/smiley_sunglasses.png"};
        case DisplayType::dead:
            return QImage{":/ressources/smiley_dead.png"};
    }
    return QImage{};
}



