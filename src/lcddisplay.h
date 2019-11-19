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

    bool mColorOn{ true };
    int mValue{ 0 };
    int mDigit0{ 0 };
    int mDigit1{ 0 };
    int mDigit2{ 0 };
};

#endif // LCDDISPLAY_H
