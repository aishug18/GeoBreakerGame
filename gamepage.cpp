#include "gamepage.h"
#include "ui_gamepage.h"
#include "mainwindow.h"
#include "mappage.h"

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePage)
    , world(new b2World(b2Vec2(0.0f, 0.0f)))
    , score(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Game");
    setupObjects();

    ui->scoreLabel->setText(QString::number(score));

    connect(this, &GamePage::scoreChanged, ui->scoreLabel, QOverload<int>::of(&QLabel::setNum));

    // Set image for buttons
    QString buttonStyle = R"(
        QPushButton {
            border-image: url(:/images/assets/wood_button.png);
            color: white;
            font-weight: bold;
            font-size: 18px;
            padding: 10px;
        }
        QPushButton:hover {
            opacity: 0.9;
        }
    )";
    ui->home->setStyleSheet(buttonStyle);
    ui->map->setStyleSheet(buttonStyle);

    // Connect buttons to respective windows
    connect(ui->home, &QPushButton::clicked, this, &GamePage::homeButtonClicked);
    connect(ui->map, &QPushButton::clicked, this, &GamePage::mapButtonClicked);

    // Set up the audio output and player for background music
    gameAudioOutput = new QAudioOutput(this);
    gameMusicPlayer = new QMediaPlayer(this);
    gameMusicPlayer->setAudioOutput(gameAudioOutput);

    // Load and play music
    gameMusicPlayer->setSource(QUrl("qrc:/images/assets/menu_music.mp3"));  // change source
    gameAudioOutput->setVolume(0.1);  // volume
    gameMusicPlayer->play();
    gameMusicPlayer->setLoops(QMediaPlayer::Infinite);

    // Audio for clicking buttons
    clickAudio = new QAudioOutput(this);
    clickPlayer = new QMediaPlayer(this);
    clickPlayer->setAudioOutput(clickAudio);
    clickPlayer->setSource(QUrl("qrc:/images/assets/button_click_sound_1.mp3"));
    clickAudio->setVolume(0.5);

    // Timer for updating physics and rendering game objects
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,[this]() {
        updatePhysics();
        this->update();
    });
    timer->start(16);   // About 60 fps

}

GamePage::~GamePage()
{
    delete ui;
    delete world;

    // delete any other box2d objects and objects created with "new" if needed
}

void GamePage::setupObjects() {
    // Set up the ball, walls, and bricks

    // Create the ball
    ball = new Ball(world);

    // Create walls, adjust values as needed
    walls.push_back(new Wall(world, QRectF(0, 0, 800, 30)));    // Top wall
    walls.push_back(new Wall(world, QRectF(0, 0, 30, 800)));    // Left wall
    walls.push_back(new Wall(world, QRectF(770, 0, 30, 800)));    // Right wall

    // Create bricks, adjust values as needed
    bricks.push_back(new Brick(world, QPointF(200, 200), "Answer1", true));
    bricks.push_back(new Brick(world, QPointF(300, 200), "Answer2", false));
    // etc

    // Create platform
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(400.0f, 650.0f); // adjust position accordingly
    platformBody = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(50.0f, 10.0f); // Platform dimensions, change accordingly
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    platformBody->CreateFixture(&fixtureDef);
}

void GamePage::updatePhysics() {
    // 1st parameter = 60 fps (if changing, change in constructor timer too).
    // other parameters: higher value = higher accuracy but worse performance. 6 and 2 are typical values.
    world->Step(1.0f / 60.0f, 6, 2);    // Simulate Box2D world
    checkCollision();
}

void GamePage::checkCollision() {
    // If the ball hits a wall, it automatically bounces because we adjusted the restitution value.

    for(b2Contact* contact = world->GetContactList(); contact; contact = contact->GetNext()) {
        // Get the bodies involved in the contact
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        // Check if one of the bodies is the ball, and handle ball-brick collision
        if(bodyA == ball->getBody() || bodyB == ball->getBody()) {
            for(Brick* brick : bricks) {
                // Check if the brick is hit
                if(bodyA == brick->getBody() || bodyB == brick->getBody()) {
                    // Update score based on brick answer
                    if(brick->isCorrectAnswer()) {
                        score += 10;    // adjust as needed
                    }
                    else {
                        score -= 5; // adjust as needed
                    }
                    emit scoreChanged(score);
                    //ui->scoreLabel->setText(QString::number(score));

                    // Remove brick and reset ball position
                    brick->destroy();
                    ball->resetPosition();
                    return; // End processing after one collision
                }
            }
        }
    }
}

void GamePage::drawGame(QPainter& painter) {
    // render the ball, bricks, and walls
    // Draw the ball
    ball->draw(painter);

    // Draw the walls
    for(Wall* wall : walls) {
        wall->draw(painter);
    }

    // Draw the bricks
    for(Brick* brick : bricks) {
        if(brick->getBody() != nullptr) {
            brick->draw(painter);
        }
    }

    // Draw the platform
    drawPlatform(painter);

    // Draw the aim line
    if(!aimStart.isNull() && !aimEnd.isNull()) {
        painter.setPen(QPen(Qt::white, 2));  // adjust color as needed
        painter.drawLine(aimStart, aimEnd);

        // Draw reflected aim line for bouncing

    }

}

void GamePage::drawPlatform(QPainter& painter) {
    QPointF position(platformBody->GetPosition().x, platformBody->GetPosition().y); // the center of the brick
    painter.setBrush(Qt::gray);    // change color as needed
    painter.drawRect(QRectF(position.x() - 10, position.y() - 10, 200, 20)); // (left, top, width, height)
}


void GamePage::keyPressEvent(QKeyEvent* event) {
    // implement if we need keyboard input
}
void GamePage::keyReleaseEvent(QKeyEvent* event) {
    // implement if we need keyboard input
}


void GamePage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    drawGame(painter);
}

void GamePage::mousePressEvent(QMouseEvent *event) {
    // Start aiming
    aimStart = QPointF(ball->getBody()->GetPosition().x, ball->getBody()->GetPosition().y);
    aimEnd = event->pos();
}
void GamePage::mouseMoveEvent(QMouseEvent *event) {
    // Update aim line
    aimStart = QPointF(ball->getBody()->GetPosition().x, ball->getBody()->GetPosition().y);
    aimEnd = event->pos();
    this->update(); // Trigger repaint to show aim line
}
void GamePage::mouseReleaseEvent(QMouseEvent *event) {
    // Launch the ball
    QPointF direction = aimEnd - aimStart;

    // Scale direction for speed adjustment
    float speed = 500.0f;    // not changing the speed, Adjust this value to control launch speed
    QPointF velocity(direction.x() * speed, direction.y() * speed);

    // Apply velocity to the ball
    ball->setVelocity(velocity);

    // Clear aim line
    aimStart = QPointF();
    aimEnd = QPointF();

    this->update();// Trigger repaint to clear the aim line
}

void GamePage::homeButtonClicked() {
    MainWindow *mainMenu = new MainWindow();
    clickPlayer->play();  // Play click sound 1
    gameMusicPlayer->stop(); // Stop game page music
    mainMenu->show();
    this->close();  // Close the current GamePage
}

void GamePage::mapButtonClicked() {
    MapPage *mapWindow = new MapPage();
    clickPlayer->play();  // Play click sound 1
    gameMusicPlayer->stop(); // Stop game page music
    mapWindow->show();
    this->close();  // Close the game window
}

void GamePage::updateTimer() {

}

void GamePage::updateGame() {

}
