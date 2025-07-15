#include <SFML/Graphics.hpp>
void playSinglePlayer(sf::RenderWindow& window) {
    sf::View view(sf::FloatRect(0, 0, 800, 600)); // αρχική κάμερα
    // Φόρτωση Background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background2.png");
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    // Φόρτωση Παίκτη
    sf::Texture playerTexture;
    playerTexture.loadFromFile("player1.png");
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(100, 500);

    // Πλατφόρμες
    std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(2000, 50)); // Πίστα μήκους 2000 pixels
    ground.setPosition(0, 550);
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    sf::RectangleShape platform1(sf::Vector2f(150, 20));
    platform1.setPosition(900, 480);
    platform1.setFillColor(sf::Color::Red);
    platforms.push_back(platform1);

     sf::RectangleShape platform2(sf::Vector2f(150, 20));
     platform2.setPosition(1300, 450);
     platform2.setFillColor(sf::Color::Yellow);
     platforms.push_back(platform2);


    // Φυσική και κίνηση
    float velocityY = 0;
    bool isOnGround = false;

    // Main game loop
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Χειρισμός
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerSprite.move(-0.5f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerSprite.move(0.5f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            velocityY = -10.0f;
            isOnGround = false;
        }

        // Βαρύτητα
        velocityY += 0.5f;
        playerSprite.move(0, velocityY);

        // Έλεγχος εδάφους
        if (playerSprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            velocityY = 0;
            isOnGround = true;
            playerSprite.setPosition(playerSprite.getPosition().x, ground.getPosition().y - playerSprite.getGlobalBounds().height);
        }
        if (playerSprite.getGlobalBounds().intersects(platform1.getGlobalBounds())) {
        velocityY = 0;
        isOnGround = true;
        playerSprite.setPosition(
        playerSprite.getPosition().x,
        platform1.getPosition().y - playerSprite.getGlobalBounds().height);
        }
        
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect platformBounds = platform1.getGlobalBounds();

        bool isLandingOnPlatform =
        playerBounds.top + playerBounds.height <= platformBounds.top + 5 &&
        playerBounds.top + playerBounds.height + velocityY >= platformBounds.top &&
        playerBounds.left + playerBounds.width > platformBounds.left &&
        playerBounds.left < platformBounds.left + platformBounds.width;

        if (isLandingOnPlatform) {
         velocityY = 0;
         isOnGround = true;
         playerSprite.setPosition(playerBounds.left, platformBounds.top - playerBounds.height);
         }

        view.setCenter(playerSprite.getPosition()); // κάμερα ακολουθεί τον παίκτη
        window.setView(view);
        sf::RectangleShape platformA(sf::Vector2f(150, 20));
        platformA.setPosition(1000, 480);
        platformA.setFillColor(sf::Color::Yellow);
  
        backgroundSprite.setPosition(view.getCenter().x - 400, 0);


        sf::RectangleShape platformB(sf::Vector2f(150, 20));
        platformB.setPosition(1300, 400);
        platformB.setFillColor(sf::Color::Magenta);

        sf::RectangleShape finish(sf::Vector2f(50, 80));
        finish.setPosition(1800, 470);
        finish.setFillColor(sf::Color::Red);

        if (playerSprite.getGlobalBounds().intersects(finish.getGlobalBounds())) {
            window.close();
       }


        // Render
        window.clear();
        window.draw(backgroundSprite);
        window.draw(ground);
        window.draw(platform1);
        window.draw(playerSprite);
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
