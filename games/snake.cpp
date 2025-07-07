#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#define WIDTH 40
#define HEIGHT 20

struct COORD {
    int X;
    int Y;
};

bool kbhit() {
    termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

char getch() {
    char buf = 0;
    termios old = {};
    tcgetattr(0, &old);
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return buf;
}

class Snake {
private:
        std::vector<COORD> body;
        char direction;

public:
    Snake() {
        COORD start = {WIDTH / 2, HEIGHT / 2};
        body.push_back(start);
        direction = 'n';
       }

    void change_dir(char dir) {
        direction = dir;
    }

    void move(bool grow = false) {
        COORD head = body[0];
        switch (direction) {
            case 'u': head.Y--; break;
            case 'd': head.Y++; break;
            case 'l': head.X--; break;
            case 'r': head.X++; break;
        }
        body.insert(body.begin(), head); // Νέα θέση κεφαλιού
        if (!grow)
            body.pop_back(); // Αφαίρεση τελευταίου αν δεν φάγαμε
    }

     COORD get_head() {
        return body[0];
    }

    std::vector<COORD> get_body() {
        return body;
    }

    bool eaten(COORD food_pos) {
        return (food_pos.X == body[0].X && food_pos.Y == body[0].Y);
    }

    bool collided() {
        COORD head = body[0];
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i].X == head.X && body[i].Y == head.Y)
                return true;
        }
        return false;
    }
};

class Food {
private:
    COORD pos;

public:
    Food() {
        gen();
    }

    void gen() {
        pos.X = rand() % (WIDTH - 2) + 1;
        pos.Y = rand() % (HEIGHT - 2) + 1;
    }

    COORD get_pos() {
        return pos;
    }
};

void draw_board(const std::vector<COORD>& body, COORD food_pos) {
    std::cout << "\033[H"; // Move cursor to top-left
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                std::cout << "#";
            } else {
                bool printed = false;
                for (size_t i = 0; i < body.size(); i++) {
                    if (x == body[i].X && y == body[i].Y) {
                        std::cout << (i == 0 ? "O" : "o");
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    if (x == food_pos.X && y == food_pos.Y)
                        std::cout << "*";
                    else
                        std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }
}

int main() {
    srand(time(0));
    Snake snake;
    Food food;

    std::cout << "\033[2J"; // Clear screen

    while (true) {
        if (kbhit()) {
            char key = getch();
            switch (key) {
                case 'w': snake.change_dir('u'); break;
                case 's': snake.change_dir('d'); break;
                case 'a': snake.change_dir('l'); break;
                case 'd': snake.change_dir('r'); break;
                case 'q': return 0; // quit
            }
        }

        
        bool grow=false;
        if (snake.eaten(food.get_pos())) {
            food.gen();
            grow=true;
        }
         snake.move(grow);
        COORD head = snake.get_head();
        if (head.X <= 0 || head.X >= WIDTH - 1 || head.Y <= 0 || head.Y >= HEIGHT - 1 || snake.collided()) {
            std::cout << "\nGame Over!\n";
            break;
        }
        draw_board(snake.get_body(), food.get_pos());
        usleep(100000); // 100ms delay
    }

    return 0;
}
