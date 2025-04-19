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
            border-image: url(:/images/assets/wood_button.png);
            color: white; font-weight: bold; font-size: 18px; padding: 10px;
        }
        QPushButton:hover { opacity: 0.9; }
    )";
    ui->home->setStyleSheet(buttonStyle);
    ui->map->setStyleSheet(buttonStyle);
    connect(ui->home, &QPushButton::clicked, this, &GamePage::homeButtonClicked);
    connect(ui->map,  &QPushButton::clicked, this, &GamePage::mapButtonClicked);
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

void GamePage::setupCountrySpecificRound() {
    roundState = RoundState::TrueFalse;
    destroyAllBricks();

    // Hide previous labels from round 1
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

    QString fact = targetCountry.facts[currentFactIndex];
    ui->questionLabel->setText(
        "Is this fact about " + targetCountry.name + " true?\n" + fact
        );

    bricks.push_back(new Brick(world, {250,375}, "True",  true));
    bricks.push_back(new Brick(world, {550,375}, "False", false));
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
                QTimer::singleShot(500, this, &GamePage::setupCountrySpecificRound);
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
    australia.facts.append("It's home to the Great Barrier Reef, the world's largest coral reef system.");
    australia.facts.append("Over 80% of its animals are unique to Australia (like kangaroos and platypuses).");
    australia.facts.append("The entire country is also a continent.");
    australia.facts.append("It once had a war against emus—and lost. Look up the \"Great Emu War\" of 1932!");
    allCountries.append(australia);

    // New Zealand
    CountryInfo newZealand;
    newZealand.name = "New Zealand";
    newZealand.capital = "Wellington";
    newZealand.facts.append("Known for its Lord of the Rings filming locations.");
    newZealand.facts.append("The indigenous Māori name is Aotearoa, meaning \"Land of the Long White Cloud.\"");
    newZealand.facts.append("There are more sheep than people—about 5:1.");
    newZealand.facts.append("New Zealand was the first country to grant women the right to vote in 1893.");
    allCountries.append(newZealand);

    // China
    CountryInfo china;
    china.name = "China";
    china.capital = "Beijing";
    china.facts.append("It's the world's most populous country (though India is catching up).");
    china.facts.append("Home to the Great Wall of China, which is over 13,000 miles long.");
    china.facts.append("It has only one time zone despite its vast size.");
    china.facts.append("Ancient Chinese invented toilet paper… over 1,400 years ago.");
    allCountries.append(china);

    // Japan
    CountryInfo japan;
    japan.name = "Japan";
    japan.capital = "Tokyo";
    japan.facts.append("Composed of over 6,800 islands.");
    japan.facts.append("Mount Fuji is its most iconic natural symbol.");
    japan.facts.append("It's home to Shinkansen—bullet trains that can exceed 300 km/h (186 mph).");
    japan.facts.append("Japan has a \"crying sumo\" contest to see which baby cries first (for good luck).");
    allCountries.append(japan);

    // India
    CountryInfo india;
    india.name = "India";
    india.capital = "New Delhi";
    india.facts.append("Second-most populous country in the world.");
    india.facts.append("Birthplace of chess, yoga, and zero (the concept, not just the digit).");
    india.facts.append("Has the world’s largest vegetarian population.");
    india.facts.append("There's a temple in Rajasthan that worships a motorbike (Om Banna Temple).");
    allCountries.append(india);

    // Russia
    CountryInfo russia;
    russia.name = "Russia";
    russia.capital = "Moscow";
    russia.facts.append("The largest country in the world by land area.");
    russia.facts.append("Trans-Siberian Railway is the longest railway line globally.");
    russia.facts.append("It spans 11 time zones.");
    russia.facts.append("There’s a Russian city (Oymyakon) that’s considered the coldest inhabited place on Earth.");
    allCountries.append(russia);

    // Italy
    CountryInfo italy;
    italy.name = "Italy";
    italy.capital = "Rome";
    italy.facts.append("Known as the birthplace of the Renaissance (Florence was key).");
    italy.facts.append("Home to the world’s smallest country—Vatican City.");
    italy.facts.append("Pizza originated in Naples in the 18th century.");
    italy.facts.append("Ancient Romans used urine to whiten their teeth. Yikes.");
    allCountries.append(italy);

    // England (UK)
    CountryInfo england;
    england.name = "England";
    england.capital = "London";
    england.facts.append("Birthplace of Shakespeare and The Beatles.");
    england.facts.append("Big Ben is not the clock—it's the bell inside the tower.");
    england.facts.append("Tea culture runs deep, but tea came from China via India.");
    england.facts.append("The Queen owns all the unmarked swans on the River Thames.");
    allCountries.append(england);

    // France
    CountryInfo france;
    france.name = "France";
    france.capital = "Paris";
    france.facts.append("The Eiffel Tower was originally meant to be temporary.");
    france.facts.append("France produces more kinds of cheese than days in the year.");
    france.facts.append("The French Revolution abolished the monarchy (then got one back).");
    france.facts.append("There’s a town called Y—just one letter long.");
    allCountries.append(france);

    // South Africa
    CountryInfo southAfrica;
    southAfrica.name = "South Africa";
    southAfrica.capital = "Pretoria (administrative), Cape Town (legislative), Bloemfontein (judicial)";
    southAfrica.facts.append("Nicknamed the \"Rainbow Nation\" due to its diversity.");
    southAfrica.facts.append("Hosted the first soccer World Cup in Africa (2010).");
    southAfrica.facts.append("Home to Table Mountain, one of the world's oldest mountains.");
    southAfrica.facts.append("Has 11 official languages—more than any other country.");
    allCountries.append(southAfrica);

    // Nigeria
    CountryInfo nigeria;
    nigeria.name = "Nigeria";
    nigeria.capital = "Abuja";
    nigeria.facts.append("Most populous country in Africa.");
    nigeria.facts.append("Home to Nollywood, the second-largest film industry by volume.");
    nigeria.facts.append("The Yoruba and Igbo cultures have deep mythological traditions.");
    nigeria.facts.append("Nigeria has a floating slum called Makoko—built entirely on stilts.");
    allCountries.append(nigeria);

    // Egypt
    CountryInfo egypt;
    egypt.name = "Egypt";
    egypt.capital = "Cairo";
    egypt.facts.append("Home of the ancient pyramids and Sphinx.");
    egypt.facts.append("The Nile River, the longest in the world, flows through it.");
    egypt.facts.append("Cleopatra was actually Greek (Ptolemaic dynasty).");
    egypt.facts.append("Ancient Egyptians worshipped cats, often mummifying them.");
    allCountries.append(egypt);

    // Brazil
    CountryInfo brazil;
    brazil.name = "Brazil";
    brazil.capital = "Brasília";
    brazil.facts.append("Home to the Amazon Rainforest, the largest tropical rainforest.");
    brazil.facts.append("Has won the most FIFA World Cups (5).");
    brazil.facts.append("The statue of Christ the Redeemer in Rio is 98 feet tall.");
    brazil.facts.append("A Brazilian island, Ilha da Queimada Grande, is infested with venomous snakes and is off-limits.");
    allCountries.append(brazil);

    // Argentina
    CountryInfo argentina;
    argentina.name = "Argentina";
    argentina.capital = "Buenos Aires";
    argentina.facts.append("Birthplace of tango dancing.");
    argentina.facts.append("Has one of the world’s southernmost cities: Ushuaia.");
    argentina.facts.append("Known for its beef and wine, especially from Mendoza.");
    argentina.facts.append("Argentina once had 5 presidents in 10 days during a 2001 crisis.");
    allCountries.append(argentina);

    // Mexico
    CountryInfo mexico;
    mexico.name = "Mexico";
    mexico.capital = "Mexico City";
    mexico.facts.append("Birthplace of chocolate (from the Aztecs).");
    mexico.facts.append("The Maya and Aztecs were major ancient civilizations.");
    mexico.facts.append("Home to the largest pyramid by volume: the Great Pyramid of Cholula.");
    mexico.facts.append("There’s a volcano rabbit native only to a few Mexican volcanoes.");
    allCountries.append(mexico);

    // USA
    CountryInfo usa;
    usa.name = "USA";
    usa.capital = "Washington, D.C.";
    usa.facts.append("It has 50 states and over 330 million people.");
    usa.facts.append("The first moon landing (1969) was by an American crew.");
    usa.facts.append("The Declaration of Independence was signed in 1776.");
    usa.facts.append("There's a town in Alaska that experiences 65 straight days of darkness (Barrow).");
    allCountries.append(usa);

    // Canada
    CountryInfo canada;
    canada.name = "Canada";
    canada.capital = "Ottawa";
    canada.facts.append("Second-largest country in the world by land area.");
    canada.facts.append("Famous for maple syrup, hockey, and politeness.");
    canada.facts.append("Has the longest coastline in the world.");
    canada.facts.append("Canada once tried to make ketchup-flavored soda. It didn’t last.");
    allCountries.append(canada);

    // Greenland
    CountryInfo greenland;
    greenland.name = "Greenland";
    greenland.capital = "Nuuk";
    greenland.facts.append("It’s an autonomous territory of Denmark.");
    greenland.facts.append("Despite the name, it’s mostly covered in ice.");
    greenland.facts.append("Has no roads connecting towns—travel is by boat, dog sled, or plane.");
    greenland.facts.append("The sun doesn’t rise for weeks in winter and doesn’t set for weeks in summer.");
    allCountries.append(greenland);

    // Norway
    CountryInfo norway;
    norway.name = "Norway";
    norway.capital = "Oslo";
    norway.facts.append("Known for fjords and natural beauty.");
    norway.facts.append("Runs mostly on hydropower—a clean energy leader.");
    norway.facts.append("Hosts the Nobel Peace Prize ceremony.");
    norway.facts.append("Has a \"slow TV\" trend: people literally watch hours of train rides or knitting.");
    allCountries.append(norway);

    // Indonesia
    CountryInfo indonesia;
    indonesia.name = "Indonesia";
    indonesia.capital = "Jakarta";
    indonesia.facts.append("Largest island nation in the world, with over 17,000 islands.");
    indonesia.facts.append("Home to Komodo dragons, the world’s largest lizards.");
    indonesia.facts.append("The world's fourth most populous country.");
    indonesia.facts.append("Has more active volcanoes than any other country—over 120.");
    allCountries.append(indonesia);
}


