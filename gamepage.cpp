#include "gamepage.h"
#include "resultpage.h"
#include "ui_gamepage.h"
#include "contactlistener.h"
#include "mainwindow.h"
#include "mappage.h"
#include <QPainter>        // for QPainter in paintEvent/drawGame
#include <QMouseEvent>     // for QMouseEvent in mouse*Event()
#include <QMessageBox>     // for QMessageBox in endGame()
#include <QMessageBox>
#include <QTimer>        // for QTimer::singleShot
#include <algorithm>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePage)
    , world(new b2World(b2Vec2(0.0f, 0.0f)))
    , contactListener(new ContactListener(this))
    , rng(std::random_device{}())
{
    ui->setupUi(this);
    setWindowTitle("Game");

    // Hook up the contact listener
    world->SetContactListener(contactListener);

    // Audio: background
    gameAudioOutput = new QAudioOutput(this);
    gameMusicPlayer = new QMediaPlayer(this);
    gameMusicPlayer->setAudioOutput(gameAudioOutput);
    gameMusicPlayer->setSource(QUrl("qrc:/images/assets/menu_music.mp3"));
    gameAudioOutput->setVolume(0.1);
    gameMusicPlayer->play();
    gameMusicPlayer->setLoops(QMediaPlayer::Infinite);

    // Audio: click
    clickAudio = new QAudioOutput(this);
    clickPlayer = new QMediaPlayer(this);
    clickPlayer->setAudioOutput(clickAudio);
    clickPlayer->setSource(QUrl("qrc:/images/assets/button_click_sound_1.mp3"));
    clickAudio->setVolume(0.5);

    // Audio: correct / wrong
    correctAudio = new QAudioOutput(this);
    correctPlayer = new QMediaPlayer(this);
    correctPlayer->setAudioOutput(correctAudio);
    correctPlayer->setSource(QUrl("qrc:/images/assets/correct_sound.mp3"));
    correctAudio->setVolume(0.7);

    wrongAudio = new QAudioOutput(this);
    wrongPlayer = new QMediaPlayer(this);
    wrongPlayer->setAudioOutput(wrongAudio);
    wrongPlayer->setSource(QUrl("qrc:/images/assets/wrong_sound.mp3"));
    wrongAudio->setVolume(0.7);

    // Score label
    ui->scoreLabel->setText("0");
    connect(this, &GamePage::scoreChanged, ui->scoreLabel, QOverload<int>::of(&QLabel::setNum));

    // Timer label (you said your .ui has a QLabel* named 'timer')
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &GamePage::onTimerTick);
    remainingTime = 60;
    ui->timer->setText(QString::number(remainingTime));
    countdownTimer->start(1000);

    // Setup world
    setupObjects();

    // Main loop for physics & repaint
    QTimer* loop = new QTimer(this);
    connect(loop, &QTimer::timeout, this, [this]() {
        updatePhysics();
        update();  // trigger paintEvent
    });
    loop->start(16);  // ~60fps

    // Buttons
    QString buttonStyle = R"(
    QPushButton {
        border: none;
        background-color: transparent;
        border-image: url(:/images/assets/wood_button.png);
        padding: 10px;
        color: black;
        font-size: 20px;
        font-weight: bold;
    }
    QPushButton:hover {
        opacity: 0.9;
    }
    )";

    ui->home->setStyleSheet(buttonStyle);
    ui->map->setStyleSheet(buttonStyle);
    connect(ui->home, &QPushButton::clicked, this, &GamePage::homeButtonClicked);
    connect(ui->map,  &QPushButton::clicked, this, &GamePage::mapButtonClicked);

    QString labelStyle = R"(
    QLabel {
        background-image: url(:/images/assets/scoreboard_frame.png);
        background-repeat: no-repeat;
        background-position: center;
        color: black;
        font-size: 30px;
        font-weight: bold;
        qproperty-alignment: AlignCenter;
        padding: 10px;
    }
    )";

    ui->timer->setStyleSheet(labelStyle);
    ui->scoreLabel->setStyleSheet(labelStyle);

    QString scoreLabelStyle = R"(
    QLabel {
        background-image: url(:/images/assets/scoreboard_frame_2.png);
        background-repeat: no-repeat;
        background-position: center;
        color: black;
        font-size: 30px;
        font-weight: bold;
        qproperty-alignment: AlignCenter;
        padding: 10px;
    }
    )";

    ui->scoreTextLabel->setStyleSheet(scoreLabelStyle);
}

GamePage::~GamePage() {
    delete countdownTimer;
    delete contactListener;
    delete world;
    delete ui;
}

void GamePage::setupObjects() {
    // Ball
    ball = new Ball(world);

    // Walls
    walls.push_back(new Wall(world, QRectF(0,0,800,30)));   // top
    walls.push_back(new Wall(world, QRectF(0,0,30,800)));   // left
    walls.push_back(new Wall(world, QRectF(800,0,30,800))); // right

    // Platform (static)
    b2BodyDef pd; pd.type = b2_staticBody; pd.position.Set(400,700);
    platformBody = world->CreateBody(&pd);
    b2PolygonShape ps; ps.SetAsBox(100,10);
    b2FixtureDef pf; pf.shape = &ps; pf.density=1.0f;
    platformBody->CreateFixture(&pf);

    // Data & first round
    populateCountryData();
    setupRoundOne();
}

void GamePage::destroyAllBricks() {
    for (auto* b : bricks) {
        b->destroy();
        delete b;
    }
    bricks.clear();
}

void GamePage::setupRoundOne() {
    roundState = RoundState::MultipleChoice;
    destroyAllBricks();

    // pick 5 random
    QVector<int> idx(allCountries.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), rng);
    selectedCountries.clear();
    for(int i=0; i<5; ++i) selectedCountries.append(allCountries[idx[i]]);

    // choose correct index
    std::uniform_int_distribution<int> dist5(0,4);
    int correctIdx = dist5(rng);
    targetCountry = selectedCountries[correctIdx];

    // build question
    std::uniform_int_distribution<int> coin(0,1);
    bool askCapital = (coin(rng)==0);
    QString q;
    if (askCapital) {
        q = QString("Which country has %1 as its capital?")
        .arg(targetCountry.capital);
    } else {
        std::uniform_int_distribution<int> distF(0, targetCountry.facts.size()-1);
        currentFactIndex = distF(rng);
        q = QString("Which country does this fact belong to?\n\"%1\"")
                .arg(targetCountry.facts[currentFactIndex]);
    }
    ui->questionLabel->setText(q);
    ui->questionLabel->setAlignment(Qt::AlignCenter);

    QPointF positions[5] = {
        {175,275}, {375,275}, {575,275}, {275,475}, {475,475}
    };

    // Create an array of label pointers for easy access
    QLabel* labels[5] = {
        ui->label_3,
        ui->label_4,
        ui->label_5,
        ui->label_6,
        ui->label_7
    };

    for (QLabel* label : labels) {
        label->clear();             // Optional: clear text
        label->setVisible(false);   // Hide label
    }

    for(int i = 0; i < 5; ++i) {
        const auto& country = selectedCountries[i];
        bool isRight = (country.name == targetCountry.name);
        qDebug() << "Spawning brick for" << country.name << "correct?" << isRight;

        // Create the brick
        bricks.push_back(
            new Brick(world, positions[i], country.name, isRight)
            );

        // Set the corresponding label text
        labels[i]->setText(country.name);
    }
}

void GamePage::setupRoundTwo() {
    roundState = RoundState::MultipleChoice;
    destroyAllBricks();

    // Pick 5 random countries
    QVector<int> idx(allCountries.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), rng);
    selectedCountries.clear();
    for(int i=0; i<5; ++i) selectedCountries.append(allCountries[idx[i]]);

    // Choose correct index
    std::uniform_int_distribution<int> dist5(0,4);
    int correctIdx = dist5(rng);
    targetCountry = selectedCountries[correctIdx];

    // Select a fact from the target country
    std::uniform_int_distribution<int> distF(0, targetCountry.facts.size()-1);
    currentFactIndex = distF(rng);

    // Ask question based on fact
    QString q = QString("Which country does this fact belong to?\n\"%1\"")
                    .arg(targetCountry.facts[currentFactIndex]);
    ui->questionLabel->setText(q);
    ui->questionLabel->setAlignment(Qt::AlignCenter);

    QPointF positions[5] = {
        {175,275}, {375,275}, {575,275}, {275,475}, {475,475}
    };

    QLabel* labels[5] = {
        ui->label_3,
        ui->label_4,
        ui->label_5,
        ui->label_6,
        ui->label_7
    };

    for (QLabel* label : labels) {
        label->clear();
        label->setVisible(false);
    }

    for(int i = 0; i < 5; ++i) {
        const auto& country = selectedCountries[i];
        bool isRight = (country.name == targetCountry.name);
        qDebug() << "Spawning Round 2 brick for" << country.name << "correct?" << isRight;

        bricks.push_back(
            new Brick(world, positions[i], country.name, isRight)
            );

        labels[i]->setText(country.name);
    }
}


void GamePage::updatePhysics() {
    world->Step(1/60.0f, 6, 2);
}

void GamePage::handleContact(b2Body* A, b2Body* B) {
    b2Body* ballBody = ball->getBody();
    if (A!=ballBody && B!=ballBody) return;
    b2Body* other = (A==ballBody?B:A);

    Brick* hit = nullptr;
    for (auto* b : bricks) {
        if (b->getBody()==other) { hit=b; break; }
    }
    if (!hit) return;

    // Safely handle the brick contact using a timer to avoid physics issues
    QTimer::singleShot(0, this, [this, hit]() {
        bool correct = hit->isCorrectAnswer();

        // Score & round transition
        if (roundState == RoundState::MultipleChoice) {
            if (correct) {
                score += 10;
                ++correctCount;
                playCorrectSound();
                emit scoreChanged(score);
                QTimer::singleShot(500, this, &GamePage::setupRoundTwo);
            } else {
                ++wrongCount;
                score = std::max(0, score - 5);
                playWrongSound();
                emit scoreChanged(score);
            }
        } else { // True/False round
            if (correct) {
                ++correctCount;
                score += 5;
                playCorrectSound();
            } else {
                ++wrongCount;
                score = std::max(0, score - 2);
                playWrongSound();
            }
            emit scoreChanged(score);
            QTimer::singleShot(500, this, &GamePage::setupRoundOne);
        }

        // Now it's safe to destroy the brick
        hit->destroy();
        bricks.erase(std::remove(bricks.begin(), bricks.end(), hit), bricks.end());
        delete hit;

        // Reset the ball after destruction
        ball->resetPosition();
    });
}

void GamePage::paintEvent(QPaintEvent*) {
    QPainter p(this);
    drawGame(p);
}

void GamePage::drawGame(QPainter& p) {
    ball->draw(p);
    for (auto* w : walls)  w->draw(p);
    for (auto* b : bricks) if (b->getBody()) b->draw(p);
    drawPlatform(p);

    if (!aimStart.isNull() && !aimEnd.isNull()) {
        p.setPen(QPen(Qt::white,2));
        p.drawLine(aimStart, aimEnd);
        if (roundState==RoundState::MultipleChoice)
            drawReflectedLine(p, aimStart, aimEnd);
    }
}

void GamePage::drawPlatform(QPainter& p) {
    auto pos = platformBody->GetPosition();
    p.setBrush(Qt::gray);
    p.drawRect(QRectF(pos.x-100, pos.y-10, 200,20));
}

void GamePage::drawReflectedLine(QPainter& p, const QPointF& A, const QPointF& B) {
    QPointF d = B - A;
    // intersect with y=30 (top wall bottom edge):
    if (d.y()==0) return;
    float t = (30 - A.y())/d.y();
    if (t>0 && t<1) {
        QPointF hit = A + d*t;
        QPointF refl{ d.x(), -d.y() };
        p.setPen(QPen(Qt::white,1,Qt::DashLine));
        p.drawLine(hit, hit + refl*0.5);
    }
}

void GamePage::mousePressEvent(QMouseEvent *e) {
    aimStart = {ball->getBody()->GetPosition().x,
                ball->getBody()->GetPosition().y};
    aimEnd = e->pos();
}

void GamePage::mouseMoveEvent(QMouseEvent *e) {
    aimEnd = e->pos();
}

void GamePage::mouseReleaseEvent(QMouseEvent*) {
    QPointF dir = aimEnd - aimStart;
    float mag = std::hypot(dir.x(), dir.y());
    if (mag==0) return;
    QPointF norm = dir/mag;
    constexpr float speed=500000.0f;
    ball->setVelocity(norm*speed);
    aimStart = aimEnd = {};
}

void GamePage::onTimerTick() {
    remainingTime--;
    ui->timer->setText(QString::number(remainingTime));
    if (remainingTime<=0) {
        countdownTimer->stop();
        endGame();
    }
}

void GamePage::endGame() {
     auto* results = new ResultPage(score,correctCount,wrongCount);
    results->show();
    close();
}


void GamePage::homeButtonClicked() {
    clickPlayer->play();
    gameMusicPlayer->stop();
    (new MainWindow())->show();
    close();
}

void GamePage::mapButtonClicked() {
    clickPlayer->play();
    gameMusicPlayer->stop();
    (new MapPage())->show();
    close();
}


void GamePage::populateCountryData() {
    // Australia
    CountryInfo australia;
    australia.name = "Australia";
    australia.capital = "Canberra";
    australia.facts.append("Home to the Great Barrier Reef, the world’s largest coral system.");
    australia.facts.append("Over 80% of its animals are unique (like kangaroos and platypuses).");
    australia.facts.append("The entire country is also a continent.");
    australia.facts.append("Once fought a war against emus—and lost (look up 'Great Emu War').");
    allCountries.append(australia);

    // New Zealand
    CountryInfo newZealand;
    newZealand.name = "New Zealand";
    newZealand.capital = "Wellington";
    newZealand.facts.append("Famous for its Lord of the Rings filming locations.");
    newZealand.facts.append("Its Māori name, Aotearoa, means 'Land of the Long White Cloud.'");
    newZealand.facts.append("More sheep than people—about a 5:1 ratio.");
    newZealand.facts.append("First country to grant women voting rights (1893).");
    allCountries.append(newZealand);

    // China
    CountryInfo china;
    china.name = "China";
    china.capital = "Beijing";
    china.facts.append("World’s most populous country (India is close).");
    china.facts.append("Great Wall is over 13,000 miles long.");
    china.facts.append("Has only one time zone despite its vast size.");
    china.facts.append("Invented toilet paper over 1,400 years ago.");
    allCountries.append(china);

    // Japan
    CountryInfo japan;
    japan.name = "Japan";
    japan.capital = "Tokyo";
    japan.facts.append("Made up of over 6,800 islands.");
    japan.facts.append("Mount Fuji is its iconic symbol.");
    japan.facts.append("Bullet trains (Shinkansen) can go over 300 km/h.");
    japan.facts.append("Has a 'crying sumo' baby contest for good luck.");
    allCountries.append(japan);

    // India
    CountryInfo india;
    india.name = "India";
    india.capital = "New Delhi";
    india.facts.append("Second-most populous country.");
    india.facts.append("Birthplace of chess, yoga, and zero.");
    india.facts.append("Has the world’s largest vegetarian population.");
    india.facts.append("A temple worships a motorbike (Om Banna Temple).");
    allCountries.append(india);

    // Russia
    CountryInfo russia;
    russia.name = "Russia";
    russia.capital = "Moscow";
    russia.facts.append("Largest country by land area.");
    russia.facts.append("Trans-Siberian is the longest railway in the world.");
    russia.facts.append("Spans 11 time zones.");
    russia.facts.append("Oymyakon is the coldest inhabited town on Earth.");
    allCountries.append(russia);

    // Italy
    CountryInfo italy;
    italy.name = "Italy";
    italy.capital = "Rome";
    italy.facts.append("Birthplace of the Renaissance (especially Florence).");
    italy.facts.append("Home to Vatican City, the smallest country.");
    italy.facts.append("Pizza began in Naples in the 18th century.");
    italy.facts.append("Ancient Romans used urine to whiten teeth.");
    allCountries.append(italy);

    // England (UK)
    CountryInfo england;
    england.name = "England";
    england.capital = "London";
    england.facts.append("Birthplace of Shakespeare and The Beatles.");
    england.facts.append("Big Ben is the bell, not the clock tower.");
    england.facts.append("Tea came from China via India.");
    england.facts.append("The Queen owns all unmarked swans on the Thames.");
    allCountries.append(england);

    // France
    CountryInfo france;
    france.name = "France";
    france.capital = "Paris";
    france.facts.append("The Eiffel Tower was meant to be temporary.");
    france.facts.append("Produces more cheese types than there are days in a year.");
    france.facts.append("The monarchy was abolished in the Revolution (then returned).");
    france.facts.append("There’s a town called 'Y'—just one letter.");
    allCountries.append(france);

    // South Africa
    CountryInfo southAfrica;
    southAfrica.name = "South Africa";
    southAfrica.capital = "Pretoria (admin), Cape Town (legis), Bloemfontein (judicial)";
    southAfrica.facts.append("Called the 'Rainbow Nation' for its diversity.");
    southAfrica.facts.append("Hosted Africa’s first soccer World Cup (2010).");
    southAfrica.facts.append("Home to Table Mountain, one of the oldest in the world.");
    southAfrica.facts.append("Has 11 official languages.");
    allCountries.append(southAfrica);

    // Nigeria
    CountryInfo nigeria;
    nigeria.name = "Nigeria";
    nigeria.capital = "Abuja";
    nigeria.facts.append("Africa’s most populous country.");
    nigeria.facts.append("Home to Nollywood, second in film volume.");
    nigeria.facts.append("Yoruba and Igbo mythologies are very rich.");
    nigeria.facts.append("Makoko is a floating slum built on stilts.");
    allCountries.append(nigeria);

    // Egypt
    CountryInfo egypt;
    egypt.name = "Egypt";
    egypt.capital = "Cairo";
    egypt.facts.append("Home to pyramids and the Great Sphinx.");
    egypt.facts.append("The Nile, the world’s longest river, flows through it.");
    egypt.facts.append("Cleopatra was Greek, not Egyptian.");
    egypt.facts.append("Ancient Egyptians mummified cats they worshipped.");
    allCountries.append(egypt);

    // Brazil
    CountryInfo brazil;
    brazil.name = "Brazil";
    brazil.capital = "Brasília";
    brazil.facts.append("Home to the Amazon, the largest rainforest.");
    brazil.facts.append("Has won the most FIFA World Cups (5).");
    brazil.facts.append("Christ the Redeemer is 98 feet tall.");
    brazil.facts.append("Snake Island is so deadly, it's off-limits.");
    allCountries.append(brazil);

    // Argentina
    CountryInfo argentina;
    argentina.name = "Argentina";
    argentina.capital = "Buenos Aires";
    argentina.facts.append("Birthplace of the tango.");
    argentina.facts.append("Home to Ushuaia, a southernmost city.");
    argentina.facts.append("Famous for beef and Mendoza wine.");
    argentina.facts.append("Had 5 presidents in 10 days (2001 crisis).");
    allCountries.append(argentina);

    // Mexico
    CountryInfo mexico;
    mexico.name = "Mexico";
    mexico.capital = "Mexico City";
    mexico.facts.append("Chocolate originated with the Aztecs.");
    mexico.facts.append("The Maya and Aztecs were ancient civilizations.");
    mexico.facts.append("Cholula has the largest pyramid by volume.");
    mexico.facts.append("The volcano rabbit lives on a few volcanoes.");
    allCountries.append(mexico);

    // USA
    CountryInfo usa;
    usa.name = "USA";
    usa.capital = "Washington, D.C.";
    usa.facts.append("Has 50 states and 330+ million people.");
    usa.facts.append("First to land on the moon (1969).");
    usa.facts.append("Declaration of Independence signed in 1776.");
    usa.facts.append("Barrow, Alaska has 65 straight dark days.");
    allCountries.append(usa);

    // Canada
    CountryInfo canada;
    canada.name = "Canada";
    canada.capital = "Ottawa";
    canada.facts.append("Second-largest country by land area.");
    canada.facts.append("Known for maple syrup and hockey.");
    canada.facts.append("Has the world’s longest coastline.");
    canada.facts.append("Tried making ketchup soda—it flopped.");
    allCountries.append(canada);

    // Greenland
    CountryInfo greenland;
    greenland.name = "Greenland";
    greenland.capital = "Nuuk";
    greenland.facts.append("An autonomous territory of Denmark.");
    greenland.facts.append("Despite the name, it’s mostly ice-covered.");
    greenland.facts.append("No roads between towns—only boats, sleds, or planes.");
    greenland.facts.append("Endless day or night for weeks at a time.");
    allCountries.append(greenland);

    // Norway
    CountryInfo norway;
    norway.name = "Norway";
    norway.capital = "Oslo";
    norway.facts.append("Famous for fjords and scenic beauty.");
    norway.facts.append("Relies heavily on hydropower.");
    norway.facts.append("Hosts the Nobel Peace Prize event.");
    norway.facts.append("'Slow TV' shows knitting and train rides.");
    allCountries.append(norway);

    // Indonesia
    CountryInfo indonesia;
    indonesia.name = "Indonesia";
    indonesia.capital = "Jakarta";
    indonesia.facts.append("Largest island nation—17,000+ islands.");
    indonesia.facts.append("Home to Komodo dragons, giant lizards.");
    indonesia.facts.append("World’s fourth most populous country.");
    indonesia.facts.append("Has over 120 active volcanoes.");
    allCountries.append(indonesia);
}
