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

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QSettings>

class GameSettings
{
public:
    GameSettings();

    enum class Difficulty{
        beginner,
        intermediate,
        expert,
        custom
    };

    void setDifficulty(Difficulty difficulty);
    [[nodiscard]] Difficulty difficulty() const;

    [[nodiscard]] int beginnerMineFieldWidth() const;
    [[nodiscard]] int beginnerMineFieldHeight() const;
    [[nodiscard]] int beginnerMineFieldCountOfMines() const;

    [[nodiscard]] int minefieldWidth() const;
    [[nodiscard]] int minefieldHeight() const;
    [[nodiscard]] int countOfMines() const;

    void setMinefieldCustomWidth(int width);
    [[nodiscard]] int minefieldCustomWidth() const;

    void setMinefieldCustomHeight(int height);
    [[nodiscard]] int minefieldCustomHeight() const;

    void setMinefieldCustomCountOfMines(int count);
    [[nodiscard]] int minefieldCustomCountOfMines() const;

    void setBeginnerName(const QString &name);
    void setDefaultBeginnerName();
    [[nodiscard]] QString beginnerName() const;

    void setIntermediateName(const QString &name);
    void setDefaultIntermediateName();
    [[nodiscard]] QString intermediateName() const;

    void setExpertName(const QString &name);
    void setDefaultExpertName();
    [[nodiscard]] QString expertName() const;

    void setBeginnerTime(int time);
    void setDefaultBeginnerTime();
    [[nodiscard]] int beginnerTime() const;

    void setIntermediateTime(int time);
    void setDefaultIntermediateTime();
    [[nodiscard]] int intermediateTime() const;

    void setExpertTime(int time);
    void setDefaultExpertTime();
    [[nodiscard]] int expertTime() const;

    void toggleQuestionMarks(bool value);
    [[nodiscard]] bool questionMarksOn() const;

    void toggleColor(bool value);
    [[nodiscard]] bool colorOn() const;

private:
    void setMinefieldParametersToBeginner();
    void setMinefieldParametersToIntermediate();
    void setMinefieldParametersToExpert();
    void setMinefieldParametersToCustom();

    void initToDefaultIfNotExists();   

    QSettings mSettings;
};

#endif // GAMESETTINGS_H
