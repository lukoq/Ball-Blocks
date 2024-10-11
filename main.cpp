#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "Klasy.h"
#include <cmath>
#include <time.h>
#include <sstream>

using namespace std;
using namespace sf;

const int roz_x=500, roz_y=800;

template <class T1, class T2> bool isIntersecting(T1 &a, T2 &b)
{
    return a.right()>=b.left() && a.left()<=b.right()
           && a.bottom()>=b.top() && a.top()<=b.bottom();
}
bool kolizja(Kwadrat &kwadrat, Pilka &pilka, Combo &combo)
{
    if(!isIntersecting(kwadrat, pilka)) return false;

    kwadrat.pkt-=pilka.moc;
    pilka.moc++;
    combo.liczCombo++;

    float overLeft{pilka.right()-kwadrat.left()};
    float overRight{kwadrat.right()-pilka.left()};
    float overTop{pilka.bottom()-kwadrat.top()};
    float overBottom{kwadrat.bottom()-pilka.top()};

    bool fromLeft(abs(overLeft)<abs(overRight));
    bool fromTop(abs(overTop)<abs(overBottom));

    float minOverlapX{fromLeft ? overLeft : overRight};
    float minOverlapY{fromTop ? overTop : overBottom};
    if(abs(minOverlapX)<abs(minOverlapY))
    {
        fromLeft ? pilka.moveLeft() : pilka.moveRight();
        return true;
    }
    else
    {
        fromTop ? pilka.moveUp() : pilka.moveDown();
        return true;
    }

}

int main()
{

	Font font;
	//font.loadFromFile("font/KozGoPr6N.otf");
	Text napis("Lukasz Kinder / 2017", font, 13);
	napis.setPosition(7 ,roz_y-20.0f);
	Text twojamocText("Twoja moc: ", font, 13);
    twojamocText.setPosition((roz_x/2)-25.0f, 5.0f);
    Text poziom("LEVEL UP!", font, 40);
    poziom.setPosition(roz_x/2-80.0f, roz_y/2-50.0f);
    Text escape("Menu (ESC)", font, 13);
	escape.setPosition(425 ,roz_y-20.0f);

    RenderWindow window(VideoMode(roz_x, roz_y, 32), "Ball & Blocks");
    window.setFramerateLimit(60);
    int los2=0, los3=0, ktora=0, srd=0, lvlUp=0;
    string mc;
    String power;




    Pilka *pilka=new Pilka[1];
    Kwadrat *kwadrat=new Kwadrat[100];
    Interfejs interface;
    Tlo tlo;/**<  */
    Menu menu;
    Combo combo(roz_x, roz_y);
    pilka->generat=true;



    while(window.isOpen())
    {
        window.clear(Color::Black);
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type==Event::Closed)
            {
                window.close();
            }
            if(event.type==Event::Resized)
            {
                window.setSize(sf::Vector2u(roz_x, roz_y));
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                menu.menuON=true;
            }
        }
        if(menu.menuON==true)
        {
            menu.update(window, pilka[0]);
            window.draw(menu);
        }
        else if(menu.menuON==false)
        {
            if(pilka->trwaStrzal==false)
            {
                pilka->celuj(combo, event);
            }
            if(pilka->trwaStrzal==true)
            {
                pilka->wystrzal();
            }
            if(pilka[0].moc>9 && pilka[0].moc<11)
            {
                srd=10;
            }
            if(pilka[0].moc>99 && pilka[0].moc<101)
            {
                srd=20;
            }
            if(combo.liczCombo==4)
            {
                combo.wykonajCombo=true;
            }

            ostringstream ss;
            ss<<pilka[0].moc;
            mc=ss.str();
            //power=mc;
            Text twojamoc(power, font, 35);
            twojamoc.setPosition((roz_x/2)-srd, 20.0f);



            if(pilka->generat==true)
            {

                srand(time(NULL));
                for(int i=ktora; i<ktora+2; i++)
                {
                    do
                    {
                        los3=los2;
                        los2=rand()%5;
                    }
                    while(los2==los3);

                    kwadrat[i].generuj(pilka->generat, los2);
                    kwadrat[i].poziom(ktora, i);
                }
                kwadrat->down=true;
                ktora+=2;
                lvlUp=0;
                if(ktora==100)
                {
                    ktora=2;
                    lvlUp=1;
                }
            }
            if(kwadrat->down==true)
            {
                for(int i=0; i<ktora-2; i++)
                {
                    kwadrat[i].update();
                    if(kwadrat[i].koniecGry==true)
                    {
                        srd=0;
                        ktora=0;
                        pilka[0].moc=1;
                        kwadrat->down=false;
                        kwadrat[i].koniecGry=false;
                        menu.menuON=true;
                    }
                }
            }

            window.draw(tlo);
            window.draw(pilka[0]);
            window.draw(interface);

            for(int i=0; i<ktora; i++)
            {
                kolizja(kwadrat[i], pilka[0], combo);
                window.draw(kwadrat[i]);
                kwadrat[i].odswiez();
            }
            if(combo.wykonajCombo==true)
            {
                combo.update();
            }
            if(lvlUp!=0)
            {
                window.draw(poziom);
            }
            window.draw(escape);
            window.draw(twojamocText);
            window.draw(twojamoc);
            window.draw(combo);
        }
        if(menu.ustwON==false)
        {
            window.draw(napis);
        }
        window.display();
    }


    return 0;
}

