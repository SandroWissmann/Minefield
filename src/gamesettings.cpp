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

#include "gamesettings.h"

#include <QSettings>

#include <QDebug>

static constexpr auto applicationName = "minefield";
static constexpr auto organizationName = "sandro4912";

namespace difficulty{
    static constexpr auto keyString = "difficulty";

    static constexpr auto beginner = "beginner";
    static constexpr auto intermediate = "intermediate";
    static constexpr auto expert = "expert";
    static constexpr auto custom = "custom";
}

namespace minefield::custom::width {
    static constexpr auto keyString = "minefield/custom/width";
}

namespace minefield::custom::height {
    static constexpr auto keyString = "minefield/custom/height";
}

namespace minefield::custom::countOfMines {
    static constexpr auto keyString = "minefield/custom/countOfMines";
}

namespace minefield::width {
    static constexpr auto keyString = "minefield/width";

    static constexpr auto beginner = 8;
    static constexpr auto intermediate = 16;
    static constexpr auto expert = 30;
}

namespace minefield::height {
    static constexpr auto keyString = "minefield/height";

    static constexpr auto beginner = 8;
    static constexpr auto intermediate = 16;
    static constexpr auto expert = intermediate;
}

namespace minefield::countOfMines {
    static constexpr auto keyString = "minefield/countOfMines";

    static constexpr auto beginner = 10;
    static constexpr auto intermediate = 40;
    static constexpr auto expert = 99;
}

namespace minefield::questionMarks {
    static constexpr auto keyString = "minefield/questionMarks";
    static constexpr auto enable = 1;
    static constexpr auto disable = 0;
}

namespace color {
    static constexpr auto keyString = "color";
    static constexpr auto enable = 1;
    static constexpr auto disable = 0;
}

namespace records::beginner::name {
    static constexpr auto keyString = "records/beginnerName";
    static constexpr auto defaultName = "Anonymous";
}

namespace records::intermediate::name {
    static constexpr auto keyString = "records/intermediateName";
    static constexpr auto defaultName = "Anonymous";
}

namespace records::expert::name {
    static constexpr auto keyString = "records/expertName";
    static constexpr auto defaultName = "Anonymous";
}

namespace records::beginner::time {
    static constexpr auto keyString = "records/beginnerTime";
    static constexpr auto defaultTime = 999;
}

namespace records::intermediate::time {
    static constexpr auto keyString = "records/intermediateTime";
    static constexpr auto defaultTime = 999;
}

namespace records::expert::time {
    static constexpr auto keyString = "records/expertTime";
    static constexpr auto defaultTime = 999;
}

GameSettings::GameSettings()
    :mSettings{ QSettings::IniFormat, QSettings::UserScope,
                applicationName, organizationName  }
{   
    initToDefaultIfNotExists();
}

void GameSettings::setDifficulty(GameSettings::Difficulty difficulty)
{
    switch (difficulty){
        case Difficulty::beginner:
        mSettings.setValue(difficulty::keyString, difficulty::beginner);
        setMinefieldParametersToBeginner();
        break;
        case Difficulty::intermediate:
        mSettings.setValue(difficulty::keyString, difficulty::intermediate);
        setMinefieldParametersToIntermediate();
        break;
        case Difficulty::expert:
        mSettings.setValue(difficulty::keyString, difficulty::expert);
        setMinefieldParametersToExpert();
        break;
        case Difficulty::custom:
        mSettings.setValue(difficulty::keyString, difficulty::custom);
        setMinefieldParametersToCustom();
        break;
    }
}

GameSettings::Difficulty GameSettings::difficulty() const
{
    if(mSettings.value(
                difficulty::keyString).toString() == difficulty::beginner) {
        return Difficulty::beginner;
    }
    if(mSettings.value(
                difficulty::keyString).toString() == difficulty::intermediate) {
        return Difficulty::intermediate;
    }
    if(mSettings.value(
                difficulty::keyString).toString() == difficulty::expert) {
        return Difficulty::expert;
    }
    if(mSettings.value(
                difficulty::keyString).toString() == difficulty::custom) {
        return Difficulty::custom;
    }
    return Difficulty::beginner;
}

int GameSettings::beginnerMineFieldWidth() const
{
    return minefield::width::beginner;
}

int GameSettings::beginnerMineFieldHeight() const
{
    return minefield::height::beginner;
}

int GameSettings::beginnerMineFieldCountOfMines() const
{
     return minefield::countOfMines::beginner;
}

int GameSettings::minefieldWidth() const
{
    return mSettings.value(minefield::width::keyString).toInt();
}

int GameSettings::minefieldHeight() const
{
    return mSettings.value(minefield::height::keyString).toInt();
}

int GameSettings::countOfMines() const
{
    return mSettings.value(minefield::countOfMines::keyString).toInt();
}

void GameSettings::setMinefieldCustomWidth(int width)
{
    mSettings.setValue(minefield::custom::width::keyString, width);
}

int GameSettings::minefieldCustomWidth() const
{
    return mSettings.value(minefield::custom::width::keyString).toInt();
}

void GameSettings::setMinefieldCustomHeight(int height)
{
    mSettings.setValue(minefield::custom::height::keyString, height);
}

int GameSettings::minefieldCustomHeight() const
{
    return mSettings.value(minefield::custom::height::keyString).toInt();
}

void GameSettings::setMinefieldCustomCountOfMines(int count)
{
    mSettings.setValue(minefield::custom::countOfMines::keyString, count);
}

int GameSettings::minefieldCustomCountOfMines() const
{
    return mSettings.value(minefield::custom::countOfMines::keyString).toInt();
}

void GameSettings::setBeginnerName(const QString &name)
{
    mSettings.setValue(records::beginner::name::keyString, name);
}

void GameSettings::setDefaultBeginnerName()
{
    mSettings.setValue(records::beginner::name::keyString,
                       records::beginner::name::defaultName);
}

QString GameSettings::beginnerName() const
{
    return mSettings.value(records::beginner::name::keyString).toString();
}

void GameSettings::setIntermediateName(const QString &name)
{
    mSettings.setValue(records::intermediate::name::keyString, name);
}

void GameSettings::setDefaultIntermediateName()
{
    mSettings.setValue(records::intermediate::name::keyString,
                       records::intermediate::name::defaultName);
}

QString GameSettings::intermediateName() const
{
    return mSettings.value(records::intermediate::name::keyString).toString();
}

void GameSettings::setExpertName(const QString &name)
{
    mSettings.setValue(records::expert::name::keyString, name);
}

void GameSettings::setDefaultExpertName()
{
    mSettings.setValue(records::expert::name::keyString,
                       records::expert::name::defaultName);
}

QString GameSettings::expertName() const
{
    return mSettings.value(records::expert::name::keyString).toString();
}

void GameSettings::setBeginnerTime(int time)
{
    mSettings.setValue(records::beginner::time::keyString, time);
}

void GameSettings::setDefaultBeginnerTime()
{
    mSettings.setValue(records::beginner::time::keyString,
                       records::beginner::time::defaultTime);
}

int GameSettings::beginnerTime() const
{
    return mSettings.value(records::beginner::time::keyString).toInt();
}

void GameSettings::setIntermediateTime(int time)
{
    mSettings.setValue(records::intermediate::time::keyString, time);
}

void GameSettings::setDefaultIntermediateTime()
{
    mSettings.setValue(records::intermediate::time::keyString,
                       records::intermediate::time::defaultTime);
}

int GameSettings::intermediateTime() const
{
    return mSettings.value(records::intermediate::time::keyString).toInt();
}

void GameSettings::setExpertTime(int time)
{
    mSettings.setValue(records::expert::time::keyString, time);
}

void GameSettings::setDefaultExpertTime()
{
    mSettings.setValue(records::expert::time::keyString,
                       records::expert::time::defaultTime);
}

int GameSettings::expertTime() const
{
    return mSettings.value(records::expert::time::keyString).toInt();
}

void GameSettings::toggleQuestionMarks(bool value)
{
    if(value) {
        mSettings.setValue(minefield::questionMarks::keyString,
                           minefield::questionMarks::enable);
    }
    else {
        mSettings.setValue(minefield::questionMarks::keyString,
                           minefield::questionMarks::disable);
    }
}

bool GameSettings::questionMarksOn() const
{
    return static_cast<bool>(
                mSettings.value(minefield::questionMarks::keyString).toInt());
}

void GameSettings::toggleColor(bool value)
{
    if(value) {
        mSettings.setValue(color::keyString, color::enable);
    }
    else {
        mSettings.setValue(color::keyString, color::disable);
    }
}

bool GameSettings::colorOn() const
{
    return static_cast<bool>(mSettings.value(color::keyString).toInt());
}

void GameSettings::setMinefieldParametersToBeginner()
{
    mSettings.setValue(minefield::width::keyString,
                       minefield::width::beginner);
    mSettings.setValue(minefield::height::keyString,
                       minefield::height::beginner);
    mSettings.setValue(minefield::countOfMines::keyString,
                       minefield::countOfMines::beginner);
}

void GameSettings::setMinefieldParametersToIntermediate()
{
    mSettings.setValue(minefield::width::keyString,
                       minefield::width::intermediate);
    mSettings.setValue(minefield::height::keyString,
                       minefield::height::intermediate);
    mSettings.setValue(minefield::countOfMines::keyString,
                       minefield::countOfMines::intermediate);
}

void GameSettings::setMinefieldParametersToExpert()
{
    mSettings.setValue(minefield::width::keyString,
                       minefield::width::expert);
    mSettings.setValue(minefield::height::keyString,
                       minefield::height::expert);
    mSettings.setValue(minefield::countOfMines::keyString,
                       minefield::countOfMines::expert);
}

void GameSettings::setMinefieldParametersToCustom()
{
    mSettings.setValue(minefield::width::keyString,
                       mSettings.value(minefield::custom::width::keyString));
    mSettings.setValue(minefield::height::keyString,
                       mSettings.value(minefield::custom::height::keyString));
    mSettings.setValue(minefield::countOfMines::keyString,
                       mSettings.value(
                           minefield::custom::countOfMines::keyString));
}

void GameSettings::initToDefaultIfNotExists()
{
    if(mSettings.value(difficulty::keyString).isNull()) {
        mSettings.setValue(difficulty::keyString,
                            difficulty::beginner);
    }
    if(mSettings.value(minefield::width::keyString).isNull()) {
        mSettings.setValue(minefield::width::keyString,
                         minefield::width::beginner);
    }
    if(mSettings.value(minefield::height::keyString).isNull()) {
        mSettings.setValue(minefield::height::keyString,
                         minefield::height::beginner);
    }
    if(mSettings.value(minefield::countOfMines::keyString).isNull()) {
        mSettings.setValue(minefield::countOfMines::keyString,
                         minefield::countOfMines::beginner);
    }
    if(mSettings.value(
                ::minefield::custom::width::keyString).isNull()) {
        mSettings.setValue(::minefield::custom::width::keyString,
                         ::minefield::width::beginner);
    }
    if(mSettings.value(minefield::custom::height::keyString).isNull()) {
        mSettings.setValue(minefield::custom::height::keyString,
                         minefield::height::beginner);
    }
    if(mSettings.value(minefield::custom::countOfMines::keyString).isNull()) {
        mSettings.setValue(minefield::custom::countOfMines::keyString,
                         minefield::countOfMines::beginner);
    }
    if(mSettings.value(minefield::questionMarks::keyString).isNull()) {
        mSettings.setValue(minefield::questionMarks::keyString,
                         minefield::questionMarks::enable);
    }
    if(mSettings.value(color::keyString).isNull()) {
        mSettings.setValue(color::keyString, color::enable);
    }
    if(mSettings.value(records::beginner::name::keyString).isNull()) {
        setDefaultBeginnerName();
    }
    if(mSettings.value(records::intermediate::name::keyString).isNull()) {
        setDefaultIntermediateName();
    }
    if(mSettings.value(records::expert::name::keyString).isNull()) {
        setDefaultExpertName();
    }
    if(mSettings.value(records::beginner::time::keyString).isNull()) {
        setDefaultBeginnerTime();
    }
    if(mSettings.value(records::intermediate::time::keyString).isNull()) {
        setDefaultIntermediateTime();
    }
    if(mSettings.value(records::expert::time::keyString).isNull()) {
        setDefaultExpertTime();
    }
}
