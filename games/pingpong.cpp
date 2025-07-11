#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
      int score1 = 0;
      int score2 = 0;
      sf::RenderWindow window(sf::VideoMode(800,600),"Ping pong");
      sf::RectangleShape paddle1(sf::Vector2f(10,100));
      paddle1.setPosition(10,250);
      sf::RectangleShape paddle2(sf::Vector2f(10,100));
      paddle2.setPosition(780,250);
      sf::CircleShape ball(10);
      ball.setPosition(400,300);
      sf::Vector2f ballVelocity(-0.3f,-0.3f);
      while(window.isOpen())
      {
          sf::Event event;
          while(window.pollEvent(event))
          {
               if(event.type==sf::Event::Closed)
                   window.close();
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
               paddle1.move(0,-0.5f);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
               paddle1.move(0,0.5f);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
               paddle2.move(0,-0.5f);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
               paddle2.move(0,0.5f);
          ball.move(ballVelocity);
          if(ball.getPosition().y<0 || ball.getPosition().y>580)
                ballVelocity.y=-ballVelocity.y;
          if(ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) || ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
                ballVelocity.x=-ballVelocity.x;
          if(ball.getPosition().x < 0) {
                      score2++;    
                      std::cout<<"one point for player2 \n";
                      std::cout<<"score1:"<<score1;  
                      std::cout<<"\nscore2:"<<score2;                
                      ball.setPosition(400, 300); 
                      ballVelocity.x = 0.3f; 
          }
          if(ball.getPosition().x > 800) {
                  score1++;
                  std::cout<<"\none point for player1 \n";  
                  std::cout<<"score1:"<<score1;   
                  std::cout<<"\nscore2:"<<score2; 
                   ball.setPosition(400, 300); 
                  ballVelocity.x = -0.3f;
           }
          if(score1 == 3 || score2 == 3) {
               std::cout<<"Game over\n";
               if(score1==3)
                   std::cout<<"The winner is player1";
               if(score2==3)
                   std::cout<<"The winner is player2";
               window.close();
          }

          window.clear();
          window.draw(paddle1);
          window.draw(paddle2);
          window.draw(ball);
          window.display();

       }
      return 0;
}