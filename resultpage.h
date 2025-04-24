#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

/**
 * @class ResultPage
 * @brief Represents the results screen displayed at the end of the game, showing final score, high scores, and navigation options.
 */
class ResultPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ResultPage and displays final score and performance.
     * @param finalScore Final score achieved by the player.
     * @param correctCount Number of correct answers.
     * @param wrongCount Number of wrong answers.
     * @param parent Optional parent widget.
     */
    explicit ResultPage(int finalScore,
                        int correctCount,
                        int wrongCount,
                        QWidget* parent = nullptr);

    /**
     * @brief Destructor. Cleans up the page.
     */
    ~ResultPage();

private slots:
    /**
     * Triggered when the user clicks "Main Menu" to return to the start page.
     */
    void onMainMenuClicked();

    /**
     * Triggered when the user clicks "Map" to return to the map page.
     */
    void onMapClicked();

protected:
    /**
     * Paints the background image for the result screen.
     * @param event Unused QPaintEvent parameter.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel* scoreLabel;     //Displays the final score
    QLabel* correctLabel;   //Displays the number of correct answers
    QLabel* wrongLabel;     //Displays the number of wrong answers
    QListWidget* highScoreList; //List showing top 5 high scores
    QPushButton* mainMenuBtn;   //Button to go back to main menu
    QPushButton* mapBtn;        //Button to return to map

    int finalScore;     //The final score for this session
};

#endif // RESULTPAGE_H
