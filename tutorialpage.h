#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QDialog>

namespace Ui {
class TutorialPage;
}

/**
 * @class TutorialPage
 * @brief Displays a tutorial dialog that provides instructions for players.
 */
class TutorialPage : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructs the TutorialPage and sets up its layout and style.
     * @param parent Optional parent widget.
     */
    explicit TutorialPage(QWidget *parent = nullptr);

    /**
     * Destructor. Cleans up dynamically allocated resources.
     */
    ~TutorialPage();

private slots:
    /**
     * Triggered when the close button is clicked, closes the tutorial window.
     */
    void on_closeButton_clicked();

private:
    Ui::TutorialPage *ui;   //Pointer to the auto-generated UI elements.
};

#endif // TUTORIALPAGE_H
