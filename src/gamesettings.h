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
