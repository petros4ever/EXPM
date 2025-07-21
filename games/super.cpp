#include <SFML/Graphics.hpp>
#include <iostream>

void playLevel2(sf::RenderWindow& window)
{
      sf::View view(sf::FloatRect(0, 0, 800, 600));

    // Background
    sf::Texture bgTexture;
    bgTexture.loadFromFile("level2_bg.png");
    sf::Sprite bgSprite(bgTexture);

    // Παίκτης
    sf::Texture playerTexture;
    playerTexture.loadFromFile("player1.png");
    sf::Sprite playerSprite(playerTexture);
    
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("enemy.png");
    sf::Sprite enemySprite(enemyTexture);
    enemySprite.setPosition(1300, 500);

    sf::Texture bossTexture;
    bossTexture.loadFromFile("boss1.png");
    sf::Sprite boss1Sprite(bossTexture);
    float bossHeight = boss1Sprite.getGlobalBounds().height;
    


    int boss1Health = 10;
    bool boss1Alive = true;

    // Platforms
    std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(4000, 50)); // μεγάλο έδαφος
    ground.setPosition(0, 550);
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);
    playerSprite.setPosition(100, ground.getPosition().y - playerSprite.getGlobalBounds().height);
    boss1Sprite.setPosition(1000, ground.getPosition().y - bossHeight);
    // Πλατφόρμες με gaps
    sf::RectangleShape platA(sf::Vector2f(150, 20));
    platA.setPosition(700, 400); platforms.push_back(platA);

    sf::RectangleShape platB(sf::Vector2f(150, 20));
    platB.setPosition(1100, 350); platforms.push_back(platB);

    sf::RectangleShape platC(sf::Vector2f(150, 20));
    platC.setPosition(1500, 420); platforms.push_back(platC);


    // Lives
    int playerLives = 3;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text livesText("Lives: 3", font, 24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 10);


    // Finish flag
    sf::RectangleShape finish(sf::Vector2f(50, 80));
    finish.setPosition(3800, 470);
    finish.setFillColor(sf::Color::Red);

    // Φυσική
    float velocityY = 0;
    bool isOnGround = true;
    
    bool isInvincible = false;
    sf::Clock invincibleClock;
    sf::Clock rockCooldown;
    std::vector<sf::CircleShape> rocks;
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Κίνηση παίκτη
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerSprite.move(-2.0f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerSprite.move(2.0f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            velocityY = -10.0f;
            isOnGround = false;
        }

        velocityY += 0.5f;
        playerSprite.move(0, velocityY);
        isOnGround = false;

        // Έλεγχος πλατφόρμας
        for (auto& plat : platforms) {
            sf::FloatRect pBounds = playerSprite.getGlobalBounds();
            sf::FloatRect platBounds = plat.getGlobalBounds();

            bool landed =
                pBounds.top + pBounds.height <= platBounds.top + 5 &&
                pBounds.top + pBounds.height + velocityY >= platBounds.top &&
                pBounds.left + pBounds.width > platBounds.left &&
                pBounds.left < platBounds.left + platBounds.width;

            if (landed) {
                velocityY = 0;
                isOnGround = true;
                playerSprite.setPosition(pBounds.left, platBounds.top - pBounds.height);
            }
        }



         if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !isInvincible) {
           isInvincible = true;
           invincibleClock.restart();
           playerSprite.setColor(sf::Color::Cyan); // Χρώμα ασπίδας
        }

        if (isInvincible && invincibleClock.getElapsedTime().asSeconds() > 5.0f) {
            isInvincible = false;
            playerSprite.setColor(sf::Color::White); // Επιστροφή στο φυσιολογικό
        }

        

                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && rockCooldown.getElapsedTime().asSeconds() > 0.5f) {
                        sf::CircleShape rock(10);
                        rock.setFillColor(sf::Color::Blue);
                        rock.setPosition(playerSprite.getPosition().x + 30, playerSprite.getPosition().y + 20);
                        rocks.push_back(rock);
                        rockCooldown.restart(); // reset cooldown
                    }


        for (size_t i = 0; i < rocks.size(); ++i) {
             rocks[i].move(4.0f, 0); // ευθύγραμμα δεξιά

            if (boss1Alive && rocks[i].getGlobalBounds().intersects(boss1Sprite.getGlobalBounds())) {
                 boss1Health--;
                 rocks.erase(rocks.begin() + i);
                 --i;
                 boss1Sprite.setColor(sf::Color::Red);
            }
        }

        if (boss1Alive && boss1Health <= 0) {
              boss1Alive = false;
              boss1Sprite.setPosition(-1000, -1000); // Εξαφάνιση
              std::cout << "Boss 1 defeated!\n";
        }


        // Εχθρός: πάτημα από πάνω
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();

        bool stompedEnemy =
            playerBounds.top + playerBounds.height < enemyBounds.top + 10 &&
            playerBounds.top + playerBounds.height + velocityY >= enemyBounds.top &&
            playerBounds.left < enemyBounds.left + enemyBounds.width &&
            playerBounds.left + playerBounds.width > enemyBounds.left;

        if (stompedEnemy) {
            enemySprite.setPosition(-1000, -1000);
            velocityY = -10.0f;
        }

        // Αν δεν έγινε πάτημα: ζημιά
        if (playerSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && !stompedEnemy && !isInvincible ) {
            playerLives--;
            playerSprite.setPosition(100, ground.getPosition().y - playerSprite.getGlobalBounds().height);
            velocityY = 0;        // σταματά η πτώση
            isOnGround = true;    // θεωρείται ότι πατάει στο έδαφος
            livesText.setString("Lives: " + std::to_string(playerLives));
        }

        if (playerLives <= 0) {
            std::cout << "Game Over\n";
            window.close();
        }

        if (velocityY > 12.0f) velocityY = 12.0f;

        // Gaps / πτώση
        if (playerSprite.getPosition().y > 600) {
            playerSprite.setPosition(100, ground.getPosition().y - playerSprite.getGlobalBounds().height); // reset
            velocityY = 0;
        }

        // Finish flag
        if (playerSprite.getGlobalBounds().intersects(finish.getGlobalBounds())) {
            std::cout << "Level 2 complete!\n";
            window.close(); // ή πέρασμα σε επόμενη πίστα
        }

        // Κάμερα
        view.setCenter(playerSprite.getPosition());
        window.setView(view);

        // Render
        window.clear();
        bgSprite.setPosition(view.getCenter().x - 400, 0);
        window.draw(bgSprite);
        for (auto& plat : platforms)
            window.draw(plat);
        window.draw(finish);
        window.draw(playerSprite);
        for (auto& rock : rocks)
            window.draw(rock);
        if (boss1Alive) {
              window.draw(boss1Sprite);
              sf::Text bossHealthText("Boss HP: " + std::to_string(boss1Health), font, 20);
              bossHealthText.setPosition(view.getCenter().x - 350, 50);
              window.draw(bossHealthText);
        }

        sf::Text bossHealthText("Boss HP: " + std::to_string(boss1Health), font, 20);
        bossHealthText.setPosition(view.getCenter().x - 350, 50);
        window.draw(bossHealthText);
        window.display();
    }
}


void playSinglePlayer(sf::RenderWindow& window) {
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // Background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background2.png");
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    std::vector<sf::RectangleShape> platforms;
    //ground
    sf::RectangleShape ground(sf::Vector2f(2000, 50));
    ground.setPosition(0, 550);
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    // Παίκτης
    sf::Texture playerTexture;
    playerTexture.loadFromFile("player1.png");
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(100, ground.getPosition().y - playerSprite.getGlobalBounds().height);

    // Εχθρός
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("enemy.png");
    sf::Sprite enemySprite(enemyTexture);
    enemySprite.setPosition(1000, 500);

    float enemySpeed = 1.0f;
    int enemyDirection = 1;

    // Lives
    int playerLives = 3;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text livesText("Lives: 3", font, 24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 10);

    // Πλατφόρμες
    

    sf::RectangleShape platform1(sf::Vector2f(150, 20));
    platform1.setPosition(900, 480);
    platform1.setFillColor(sf::Color::Red);
    platforms.push_back(platform1);

    sf::RectangleShape platform2(sf::Vector2f(150, 20));
    platform2.setPosition(1300, 450);
    platform2.setFillColor(sf::Color::Yellow);
    platforms.push_back(platform2);

    sf::RectangleShape platformA(sf::Vector2f(150, 20));
    platformA.setPosition(1000, 480);
    platformA.setFillColor(sf::Color::Yellow);
    platforms.push_back(platformA);

    sf::RectangleShape platformB(sf::Vector2f(150, 20));
    platformB.setPosition(1300, 400);
    platformB.setFillColor(sf::Color::Magenta);
    platforms.push_back(platformB);

    sf::RectangleShape finish(sf::Vector2f(50, 80));
    finish.setPosition(1800, 470);
    finish.setFillColor(sf::Color::Red);

    float velocityY = 0;
    bool isOnGround = false;

    sf::Event event;
    bool isInvincible = false;
    sf::Clock invincibleClock;
    sf::Clock rockCooldown;
    std::vector<sf::CircleShape> rocks;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Χειρισμός
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerSprite.move(-2.0f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerSprite.move(2.0f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            velocityY = -10.0f;
            isOnGround = false;
        }

        // Βαρύτητα
        velocityY += 0.5f;
        playerSprite.move(0, velocityY);

        // Εχθρός κινείται
        enemySprite.move(enemySpeed * enemyDirection, 0);
        if (enemySprite.getPosition().x < 950 || enemySprite.getPosition().x > 1150)
            enemyDirection *= -1;

        // Έλεγχος επαφής με πλατφόρμες
        isOnGround = false;
        for (auto& platform : platforms) {
            sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
            sf::FloatRect platBounds = platform.getGlobalBounds();

            bool landed =
                playerBounds.top + playerBounds.height <= platBounds.top + 5 &&
                playerBounds.top + playerBounds.height + velocityY >= platBounds.top &&
                playerBounds.left + playerBounds.width > platBounds.left &&
                playerBounds.left < platBounds.left + platBounds.width;

            if (landed) {
                velocityY = 0;
                isOnGround = true;
                playerSprite.setPosition(playerBounds.left, platBounds.top - playerBounds.height);
            }
        }

        // Έλεγχος finish
        if (playerSprite.getGlobalBounds().intersects(finish.getGlobalBounds()))
        {
            playLevel2(window);
            return;
         }
            

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !isInvincible) {
           isInvincible = true;
           invincibleClock.restart();
           playerSprite.setColor(sf::Color::Cyan); // Χρώμα ασπίδας
        }

        if (isInvincible && invincibleClock.getElapsedTime().asSeconds() > 5.0f) {
            isInvincible = false;
            playerSprite.setColor(sf::Color::White); // Επιστροφή στο φυσιολογικό
        }

        

                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && rockCooldown.getElapsedTime().asSeconds() > 0.5f) {
                        sf::CircleShape rock(10);
                        rock.setFillColor(sf::Color::Blue);
                        rock.setPosition(playerSprite.getPosition().x + 30, playerSprite.getPosition().y + 20);
                        rocks.push_back(rock);
                        rockCooldown.restart(); // reset cooldown
                    }


        for (size_t i = 0; i < rocks.size(); ++i) {
             rocks[i].move(4.0f, 0); // ευθύγραμμα δεξιά

            if (rocks[i].getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                 enemySprite.setPosition(-1000, -1000);
                 rocks.erase(rocks.begin() + i);
                 --i;
            }
        }

        


        // Εχθρός: πάτημα από πάνω
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();

        bool stompedEnemy =
            playerBounds.top + playerBounds.height < enemyBounds.top + 10 &&
            playerBounds.top + playerBounds.height + velocityY >= enemyBounds.top &&
            playerBounds.left < enemyBounds.left + enemyBounds.width &&
            playerBounds.left + playerBounds.width > enemyBounds.left;

        if (stompedEnemy) {
            enemySprite.setPosition(-1000, -1000);
            velocityY = -10.0f;
        }

        // Αν δεν έγινε πάτημα: ζημιά
        if (playerSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && !stompedEnemy && !isInvincible ) {
            playerLives--;
            playerSprite.setPosition(100, ground.getPosition().y - playerSprite.getGlobalBounds().height);
            velocityY = 0;        // σταματά η πτώση
            isOnGround = true;    // θεωρείται ότι πατάει στο έδαφος
            livesText.setString("Lives: " + std::to_string(playerLives));
        }

        if (playerLives <= 0) {
            std::cout << "Game Over\n";
            window.close();
        }

        // Κάμερα & background
        view.setCenter(playerSprite.getPosition());
        window.setView(view);
        backgroundSprite.setPosition(view.getCenter().x - 400, 0);

        // Render
        window.clear();
        window.draw(backgroundSprite);
        for (auto& plat : platforms)
            window.draw(plat);

        window.draw(finish);
        window.draw(enemySprite);
        window.draw(playerSprite);
        for (auto& rock : rocks)
            window.draw(rock);
        window.setView(window.getDefaultView());
        window.draw(livesText);
        window.setView(view);
        window.display();
    }
}

void   playMultiplayer(sf::RenderWindow& window){
return ;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super Petros Adventure");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) return -1;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Buttons
    sf::RectangleShape button1(sf::Vector2f(200, 50));
    button1.setPosition(300, 250);
    button1.setFillColor(sf::Color::Blue);

    sf::Text text1("1 Player", font, 24);
    text1.setPosition(320, 260);
    text1.setFillColor(sf::Color::White);

    sf::RectangleShape button2(sf::Vector2f(200, 50));
    button2.setPosition(300, 350);
    button2.setFillColor(sf::Color::Blue);

    sf::Text text2("2 Players", font, 24);
    text2.setPosition(310, 360);
    text2.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Κλείσιμο παραθύρου
            if (event.type == sf::Event::Closed)
                window.close();

            // Χειρισμός mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    playSinglePlayer(window);
                    return 0;
                }
                if (button2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    playMultiplayer(window);
                    return 0;
                }
            }
        }

        // Draw menu
        window.clear();
        window.draw(backgroundSprite);
        window.draw(button1); window.draw(text1);
        window.draw(button2); window.draw(text2);
        window.display();
    }

    return 0;
}
