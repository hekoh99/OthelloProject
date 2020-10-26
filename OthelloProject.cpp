#include <iostream>
#include <bangtal>
using namespace std;
using namespace bangtal;

ScenePtr Gamescene;
ObjectPtr stones[64];

ObjectPtr BScoreten;
ObjectPtr BScoreone;
ObjectPtr WScoreten;
ObjectPtr WScoreone;

enum class Status {
    BLANK,
    POSSIBLE,
    BLACK,
    WHITE
};

Status state[64];

enum class Turn {
    BLACK,
    WHITE
};

enum class Purpose {
    CHECK,
    REVERSE
};

Turn turn = Turn::BLACK;

void setStatus(int t, Status s) {
    switch (s) {
    case Status::BLANK:
        stones[t]->setImage("Images/blank.png");
        break;

    case Status::POSSIBLE:
        if (turn == Turn::BLACK) {
            stones[t]->setImage("Images/black possible.png");
        }
        else if (turn == Turn::WHITE) {
            stones[t]->setImage("Images/white possible.png");
        }
        break;

    case Status::BLACK:
        stones[t]->setImage("Images/black.png");
        break;

    case Status::WHITE:
        stones[t]->setImage("Images/white.png");
        break;
    }
    state[t] = s;
}

void reverse(int t, Status s, int d) {
    t += d;
    while (state[t] != s) {
        setStatus(t, s);
        t += d;
    }
}

bool isPossible(int t, Purpose p) {

    if (state[t] == Status::BLACK) return false;
    if (state[t] == Status::WHITE) return false;
    if (t <= 55 && state[t + 8] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = 16; t + i < 64; i += 8) {
            if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, 8);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t <= 55 && state[t + 8] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = 16; t + i < 64; i += 8) {
            if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, 8);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 7 && t <= 54 && state[t + 9] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = 18; t + i < 64; i += 9) {
            if ((t + 9) % 8 == 7) break;
            if ((t + i) % 8 == 7 && state[t + i] != Status::WHITE) break;
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, 9);
                }
                else {
                    return true;
                }
            }
        }
    }
    if (t % 8 != 7 && t <= 54 && state[t + 9] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = 18; t + i < 64; i += 9) {
            if ((t + 9) % 8 == 7) break;
            if ((t + i) % 8 == 7 && state[t + i] != Status::BLACK) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, 9);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 7 && t <= 62 && state[t + 1] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = 2; t + i < 64; i += 1) {
            if ((t + i) % 8 == 7 && state[t + i] != Status::WHITE) break;
            if ((t + 1) % 8 == 7) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, 1);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 7 && t <= 62 && state[t + 1] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = 2; t + i < 64; i += 1) {
            if ((t + 1) % 8 == 7) break;
            if ((t + i) % 8 == 7 && state[t + i] != Status::BLACK) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, 1);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 7 && t >= 14 && state[t - 7] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = -14; t + i >= 0; i -= 7) {
            if ((t - 7) % 8 == 7) break;
            if ((t + i) % 8 == 7 && state[t + i] != Status::WHITE) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, -7);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 7 && t >= 14 && state[t - 7] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = -14; t + i >= 0; i -= 7) {
            if ((t - 7) % 8 == 7) break;
            if ((t + i) % 8 == 7 && state[t + i] != Status::BLACK) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, -7);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t >= 16 && state[t - 8] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = -16; t + i >= 0; i -= 8) {
            if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, -8);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t >= 16 && state[t - 8] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = -16; t + i >= 0; i -= 8) {
            if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, -8);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t >= 18 && state[t - 9] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = -18; t + i >= 0; i -= 9) {
            if ((t - 9) % 8 == 0) break;
            if ((t + i) % 8 == 0 && state[t + i] != Status::WHITE) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, -9);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t >= 18 && state[t - 9] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = -18; t + i >= 0; i -= 9) {
            if ((t - 9) % 8 == 0) break;
            if ((t + i) % 8 == 0 && state[t + i] != Status::BLACK) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, -9);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t >= 2 && state[t - 1] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = -2; t + i >= 0; i -= 1) {
            if ((t + i) % 8 == 0 && state[t + i] != Status::WHITE) break;
            if ((t - 1) % 8 == 0) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, -1);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t >= 2 && state[t - 1] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = -2; t + i >= 0; i -= 1) {
            if ((t + i) % 8 == 0 && state[t + i] != Status::BLACK) break;
            if ((t - 1) % 8 == 0) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, -1);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t <= 56 && state[t + 7] == Status::BLACK && turn == Turn::WHITE) {
        for (int i = 14; t + i < 64; i += 7) {
            if ((t + 7) % 8 == 0) break;
            if ((t + i) % 8 == 0 && state[t + i] != Status::WHITE) break;
            else if (state[t + i] == Status::WHITE) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::WHITE, 7);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }
    if (t % 8 != 0 && t <= 56 && state[t + 7] == Status::WHITE && turn == Turn::BLACK) {
        for (int i = 14; t + i < 64; i += 7) {
            if ((t + 7) % 8 == 0) break;
            if ((t + i) % 8 == 0 && state[t + i] != Status::BLACK) break;
            else if (state[t + i] == Status::BLACK) {
                if (p == Purpose::REVERSE) {
                    reverse(t, Status::BLACK, 7);
                }
                else {
                    return true;
                }
            }
            else if (state[t + i] == Status::BLANK || state[t + i] == Status::POSSIBLE) break;
        }
    }

    return false;
}

int countState(Status s) {
    int count = 0;
    for (int i = 0; i < 64; i++) {
        if (state[i] == s) {
            count++;
        }
    }
    return count;
}

void setPossible() {
    for (int i = 0; i < 64; i++) {
        if (state[i] == Status::POSSIBLE) {
            setStatus(i, Status::BLANK);
        }
        if (isPossible(i, Purpose::CHECK)) {
            setStatus(i, Status::POSSIBLE);
        }
    }
}

void setScore() {
    int b = countState(Status::BLACK);
    int w = countState(Status::WHITE);

    BScoreten->setImage("Images/L" + to_string(b / 10) + ".png");
    BScoreone->setImage("Images/L" + to_string(b % 10) + ".png");
    WScoreten->setImage("Images/L" + to_string(w / 10) + ".png");
    WScoreone->setImage("Images/L" + to_string(w % 10) + ".png");

    cout << b << " " << w << endl;
}

int comTurn() {
    for (int i = 0; i < 64; i++) {
        if (state[i] == Status::POSSIBLE) {
            return i;
        }
    }
    return -1;
}

int main()
{

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    Gamescene = Scene::create("1", "Images/background.png");

    for (int i = 0; i < 64; i++) {
        stones[i] = Object::create("Images/blank.png", Gamescene, 40 + (i % 8) * 80, 40 + (i / 8) * 80);
        stones[i]->setOnMouseCallback([&, i](ObjectPtr object, int x, int y, MouseAction action)->bool {
            if (state[i] == Status::POSSIBLE) {
                if (turn == Turn::BLACK) {
                    isPossible(i, Purpose::REVERSE); // 돌 바꾸기
                    setStatus(i, Status::BLACK); // 클릭한 곳에 돌 놓기
                    setScore(); // 스코어 변경
                    turn = Turn::WHITE; // 흰 돌로 차례 넘기기
                    setPossible(); // 흰 돌 가능한 자리 체크

                    auto timer = Timer::create(1.0f);
                    timer->setOnTimerCallback([&](TimerPtr t)->bool {
                        if (comTurn() != -1) {
                            isPossible(comTurn(), Purpose::REVERSE);  // 돌 바꾸기
                            setStatus(comTurn(), Status::WHITE); // 컴이 선택한 위치에 흰 돌 놓기
                            setScore(); // 스코어 변경
                            turn = Turn::BLACK; // 검은 돌로 차례 넘기기
                            setPossible(); // 검은 돌 가능한 자리 체크

                            if (countState(Status::POSSIBLE) == 0) {
                                turn = Turn::WHITE;
                                setPossible();
                                if (countState(Status::POSSIBLE) == 0) {
                                    showMessage("end game");
                                }
                                else {
                                    t->set(1.0f);
                                    t->start();
                                }                                
                            }
                        }
                        else if (comTurn() == -1) {
                            turn = Turn::BLACK;
                            setPossible();
                            if (countState(Status::POSSIBLE) == 0){
                                showMessage("end game");
                            }
                        }
                         return true;
                    });
                    timer->start();
                    
                }
            }
            return true;
            });
        state[i] = Status::BLANK;
    }

    setStatus(27, Status::BLACK);
    setStatus(28, Status::WHITE);
    setStatus(35, Status::WHITE);
    setStatus(36, Status::BLACK);

    BScoreten = Object::create("Images/L0.png", Gamescene, 760, 230);
    BScoreone = Object::create("Images/L2.png", Gamescene, 830, 230);
    WScoreten = Object::create("Images/L0.png", Gamescene, 1070, 230);
    WScoreone = Object::create("Images/L2.png", Gamescene, 1140, 230);

    setPossible();

    startGame(Gamescene);
    return 0;
}