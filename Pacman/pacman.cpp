#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <graphics.h>

using namespace std;

class World
{
    int world_coor[27][4] = {{10, 10, 850, 610}, {10, 170, 90, 450}, {770, 170, 850, 450}, {50, 50, 130, 130}, {170, 50, 450, 90}, {490, 50, 610, 90}, {650, 50, 810, 130}, {330, 130, 570, 170}, {250, 130, 290, 330}, {50, 490, 170, 570}, {210, 490, 410, 570}, {130, 170, 210, 250}, {130, 250, 170, 330}, {570, 210, 610, 290}, {650, 210, 690, 330}, {610, 330, 690, 410}, {330, 330, 570, 370}, {330, 210, 530, 290}, {170, 370, 250, 450}, {250, 410, 290, 450}, {450, 530, 490, 610}, {610, 570, 650, 610}, {690, 490, 810, 570}, {530, 490, 650, 530}, {530, 530, 570, 570}, {330, 410, 410, 450}, {450, 410, 570, 450}};

    int black[6][4] = {{8, 172, 12, 449}, {849, 172, 852, 449}, {132, 249, 169, 252}, {249, 412, 252, 449}, {652, 329, 689, 332}, {532, 529, 569, 532}};

    int specialFood[6][2] = {{30, 30}, {830, 30}, {30, 590}, {830, 590}, {510, 590}, {190, 310}};

public:
    int food[104] = {1, 19, 1, 1, 2,
                     1, 7, 1, 3, 1, 4, 2, 2, 13, 4,
                     7, 1, 1, 6, 7, 2, 1, 2, 1, 1,
                     12, 4, 1, 2, 1, 1, 1, 5, 1, 1,
                     1, 1, 2, 4, 1, 1, 2, 1, 1, 5,
                     1, 1, 1, 1, 2, 4, 1, 2, 1, 1,
                     9, 1, 2, 4, 6, 6, 1, 2, 2, 4,
                     2, 2, 9, 2, 2, 4, 2, 3, 1, 2,
                     1, 3, 5, 2, 22, 3, 1, 5, 3, 3,
                     1, 3, 2, 3, 1, 5, 1, 1, 1, 1,
                     3, 3, 1, 1, 10, 2, 2, 1, 4};

    void createWorld()
    {
        cleardevice();
        for (int i = 0; i < 27; i++)
        {
            int left = world_coor[i][0];
            int top = world_coor[i][1];
            int right = world_coor[i][2];
            int bottom = world_coor[i][3];
            setcolor(BLUE);
            rectangle(left - 1, top - 1, right + 1, bottom + 1);
            rectangle(left, top, right, bottom);
            rectangle(left + 1, top + 1, right - 1, bottom - 1);
        }
        for (int i = 0; i < 6; i++)
        {
            int left = black[i][0];
            int top = black[i][1];
            int right = black[i][2];
            int bottom = black[i][3];
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            bar(left, top, right, bottom);
        }
    }

    void placeFood()
    {
        int p = 1, x = 30, y = 30;
        for (int i = 0; i < 104; i++)
        {
            int value = food[i];
            for (int j = 0; j < value; j++)
            {
                if (p == 0)
                {
                    setcolor(CYAN);
                    setfillstyle(SOLID_FILL, CYAN);
                    fillellipse(x, y, 5, 5);
                }
                x += 40;
                if (x > 830)
                {
                    x = 30;
                    y += 40;
                }
            }
            if (p == 0)
            {
                p = 1;
            }
            else
            {
                p = 0;
            }
        }
    }

    void placeSpecialFood()
    {
        for (int i = 0; i < 6; i++)
        {
            setfillstyle(SOLID_FILL, GREEN);
            setcolor(GREEN);
            fillellipse(specialFood[i][0], specialFood[i][1], 10, 10);
        }
    }
};

class Pacman : public World
{
public:
    int x, y, life, score, setscore = -1, p = 0, totalfood = 0, maxscore;
    Pacman()
    {
        for (int i = 1; i < 104; i += 2)
        {
            totalfood += food[i];
            maxscore = totalfood * 10;
            maxscore += 600;
            maxscore = 300;
        }
        x = 470;
        y = 470;
        life = 3;
        score = 0;
    }

    void moveRight()
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 0, 360, 15, 15);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        sector(++x, y, 45, 315, 14, 14);
        if ((getpixel(x + 15, y + 15) == CYAN) || (getpixel(x + 15, y - 15) == CYAN) || (getpixel(x + 15, y) == CYAN))
        {
            score += 10;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x + 4) / 40) + 1) * 40 - 10, (((y - 10) / 40) + 1) * 40 - 10, 5, 5);
        }
        if ((getpixel(x + 15, y + 15) == GREEN) || (getpixel(x + 15, y - 15) == GREEN) || (getpixel(x + 15, y) == GREEN))
        {
            score += 100;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x + 4) / 40) + 1) * 40 - 10, (((y - 10) / 40) + 1) * 40 - 10, 10, 10);
        }
    }
    void moveUp()
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 0, 360, 14, 14);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        sector(x, --y, 145, 405, 14, 14);
        if ((getpixel(x + 15, y - 15) == CYAN) || (getpixel(x - 15, y - 15) == CYAN) || (getpixel(x, y - 15) == CYAN))
        {
            score += 10;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(((x + 34) / 40) * 40 - 10, ((y + 24) / 40) * 40 - 10, 5, 5);
        }
        if ((getpixel(x + 15, y - 15) == GREEN) || (getpixel(x - 15, y - 15) == GREEN) || (getpixel(x, y - 15) == GREEN))
        {
            score += 100;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(((x + 34) / 40) * 40 - 10, ((y + 24) / 40) * 40 - 10, 10, 10);
        }
    }

    void moveLeft()
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 0, 360, 14, 14);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        sector(--x, y, 0, 360, 14, 14);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 135, 225, 14, 14);
        if ((getpixel(x - 15, y + 15) == CYAN) ||
            (getpixel(x - 15, y - 15) == CYAN) ||
            (getpixel(x - 15, y) == CYAN))
        {
            score += 10;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x - 24) / 40) + 1) * 40 - 10, (((y - 10) / 40) + 1) * 40 - 10, 5, 5);
        }
        if ((getpixel(x - 15, y + 15) == GREEN) ||
            (getpixel(x - 15, y - 15) == GREEN) ||
            (getpixel(x - 15, y) == GREEN))
        {
            score += 100;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x - 24) / 40) + 1) * 40 - 10, (((y - 10) / 40) + 1) * 40 - 10, 10, 10);
        }
    }

    void moveDown()
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 0, 360, 14, 14);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        sector(x, ++y, 0, 360, 14, 14);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        sector(x, y, 225, 315, 14, 14);
        if ((getpixel(x + 15, y + 15) == CYAN) || (getpixel(x - 15, y + 15) == CYAN) || (getpixel(x, y + 15) == CYAN))
        {
            score += 10;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x - 24) / 40) + 1) * 40 - 10, ((y + 56) / 40) * 40 - 10, 5, 5);
        }
        if ((getpixel(x + 15, y + 15) == GREEN) || (getpixel(x - 15, y + 15) == GREEN) || (getpixel(x, y + 15) == GREEN))
        {
            score += 100;
            updateScore();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse((((x - 24) / 40) + 1) * 40 - 10, ((y + 56) / 40) * 40 - 10, 10, 10);
        }
    }

    void updateScore()
    {
        if (setscore < score)
        {
            setscore = score;
            settextstyle(BOLD_FONT, HORIZ_DIR, 3);
            char scoreString[10];
            sprintf(scoreString, "SCORE : %d", setscore);
            setcolor(BLACK);
            outtextxy(830, 290, scoreString);
            setcolor(WHITE);
            sprintf(scoreString, "SCORE : %d", score);
            outtextxy(830, 290, scoreString);

            if (score >= maxscore)
            {
                cleardevice();
                outtextxy(200, 200, "THANKS FOR PLAYING OUR VARIATION OF THE EPIC PACMAN");
                outtextxy(200, 250, "CREATED BY:");
                outtextxy(200, 300, "PARAS - IIITU17102");
                outtextxy(200, 350, "AKHIL - IIITU17104");
                outtextxy(200, 400, "DEEPESH - IIITU17110");
            }
        }
    }
};

int main()
{
    initwindow(1000, 650, "Pacman");

    Pacman pacman;
    pacman.createWorld();
    pacman.placeFood();
    pacman.placeSpecialFood();
    pacman.moveRight();
    pacman.updateScore();

    while (true)
    {
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if ((getpixel(pacman.x + 16, pacman.y + 15) == BLUE) ||
                (getpixel(pacman.x + 16, pacman.y - 15) == BLUE))
            {
            }
            else
            {
                pacman.moveRight();
            }
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            if ((getpixel(pacman.x - 16, pacman.y + 15) == BLUE) ||
                (getpixel(pacman.x - 16, pacman.y - 15) == BLUE))
            {
            }
            else
            {
                pacman.moveLeft();
            }
        }
        if (GetAsyncKeyState(VK_UP))
        {
            if ((getpixel(pacman.x + 15, pacman.y - 16) == BLUE) ||
                (getpixel(pacman.x - 15, pacman.y - 16) == BLUE))
            {
            }
            else
            {
                pacman.moveUp();
            }
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            if ((getpixel(pacman.x - 15, pacman.y + 16) == BLUE) ||
                (getpixel(pacman.x + 15, pacman.y + 16) == BLUE))
            {
            }
            else
            {
                pacman.moveDown();
            }
        }
        delay(10);
    }

    getch();
}
