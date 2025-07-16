#include <SFML/Graphics.hpp>
#include <iostream>

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
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Χειρισμός
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerSprite.move(-0.5f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerSprite.move(0.5f, 0);
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
            window.close();

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
        if (playerSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && !stompedEnemy) {
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
        window.setView(window.getDefaultView());
        window.draw(livesText);
        window.setView(view);
        window.display();
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Super Petros Adventure");
    sf::Event event;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
    return -1;
    }

    sf::RectangleShape button1(sf::Vector2f(200, 50));
    button1.setPosition(300, 250);
    button1.setFillColor(sf::Color::Blue);
    sf::Text text1;
    text1.setString("1 Player");
    text1.setFont(font);
    text1.setCharacterSize(24);
    text1.setPosition(320, 260);
    text1.setFillColor(sf::Color::White);


    sf::RectangleShape button2(sf::Vector2f(200, 50));
    button2.setPosition(300, 350);
    button2.setFillColor(sf::Color::Blue);
    sf::Text text2;
    text2.setString("2 Players");
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setPosition(310, 360);

    

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

  
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);

    sf::Texture playerTexture;
     if (!playerTexture.loadFromFile("player1.png")) 
     {
        return -1;
     }

     sf::Sprite playerSprite;
     playerSprite.setTexture(playerTexture);
     playerSprite.setPosition(100, 500); // αρχική θέση

    sf::Texture player2Texture;
    if (!player2Texture.loadFromFile("player2.png")) {
    return -1;
    }
   
   sf::Sprite player2Sprite;
   player2Sprite.setTexture(player2Texture);
   player2Sprite.setPosition(600, 500); // διαφορετική αρχική θέση


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
             sf::Vector2i mousePos = sf::Mouse::getPosition(window);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
             playerSprite.move(-0.5f, 0); 
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
             playerSprite.move(0.5f, 0); 
             }
             float velocityY = 0;
             bool isOnGround = false;

             if (!isOnGround) {
             velocityY += 0.5f;              
             playerSprite.move(0, velocityY);
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
             velocityY = -10.0f; // προς τα πάνω
             isOnGround = false;
             }


             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                  player2Sprite.move(-0.5f, 0);
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
             player2Sprite.move(0.5f, 0);
             }
       
            float player2VelocityY = 0;
            bool player2OnGround = true;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2OnGround) {
                  player2VelocityY = -10.0f; // αρνητική τιμή = άλμα προς τα πάνω
                  player2OnGround = false;
            }

            player2VelocityY += 0.5f; // βαρύτητα
            player2Sprite.move(0, player2VelocityY);

           // Έλεγχος αν παίκτης είναι στο έδαφος
           if (player2Sprite.getPosition().y >= 500) {
           player2Sprite.setPosition(player2Sprite.getPosition().x, 500);
           player2VelocityY = 0;
           player2OnGround = true;
           }

             if (button1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
             {
                  playSinglePlayer(window);

             }
    if (button2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        
             }
          }
        window.clear();
        window.draw(backgroundSprite);
        window.draw(playerSprite);
        window.draw(player2Sprite);
        window.draw(button1);
        window.draw(text1);
        window.draw(button2);
        window.draw(text2);
        window.display();
       }
    
    return 0;
}
