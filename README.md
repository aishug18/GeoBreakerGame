# Geo Breaker

Geo Breaker is a Qt-based educational game that blends map-based trivia with simple interactive gameplay. Designed to make learning geography engaging, players are challenged to shoot the correct answers in a visually rich game environment.

---

## Game Overview

In Geo Breaker, players begin at the main menu, where they can either play the game or view a tutorial:

1. The **Play** button opens the **Map Page**, a themed interface with a background image and sound.
2. From the Map Page, clicking **Play** launches the **Game Page**, where the player answers questions by shooting a ball at the correct option.
3. The **Tutorial** button on the main menu opens a dialog with instructions and guidance.

Each screen includes background music and click sounds to enhance user experience.

---

## Features

- Map-based UI with custom background images and styled buttons
- Seamless navigation between main menu, map page, and game screen
- Integrated music and sound effects using QMediaPlayer
- A tutorial popup for first-time users
- Simple quiz mechanic: shoot the ball at the correct answer

---

## Project Structure

- `mainwindow.*` – Sets up the main menu and handles navigation
- `mappage.*` – Displays the map and manages transition to the game or back to the menu
- `tutorialpage.*` – A modal dialog with tutorial instructions
- `gamepage.*` – Core gameplay screen where the questions and interactions occur
- `resources.qrc` – Manages paths to all media assets (images and sound)
- `assets/` – Folder containing images, buttons, and sound files used across the game

---

## Build Instructions

1. Open the project in Qt Creator.
2. Make sure the Qt Multimedia module is available in your installation.
3. Build the project and run using the default build system.
4. Ensure all image and audio files are correctly referenced in the resource file.

---

## Dependencies

- Qt 6.x or higher
- Qt Multimedia module (for music and sound)

---

## Assets

- `menu_music.mp3` – Background music for the main menu
- `map_music.mp3` – Background music for the map screen
- `button_click_sound_1.mp3` – Sound effect for button clicks
- `wood_button.png` – Button background image
- `ge.png`, `world_map.jpg` – Visual assets for the main menu and map

---

## Developers

This game was developed as a group project by:

- Aishwarya Golakoti  
- Anurup Kumar  
- Diya Mandot  
- Morris Lu  
- Kunj Rathod

---

## Notes

Geo Breaker can be extended to include additional levels, animations, and question types. The modular design makes it easy to add future functionality or adapt the game for other educational topics.
