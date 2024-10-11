#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include "Klasy.h"
#include <sstream>

#define M_PI 3.14159265358979323846


using namespace sf;
using namespace std;

Pilka::Pilka()
{
    circle.setRadius(r);
    circle.setOrigin(r, r);
    circle.setFillColor(Color(255,255,255));
    circle.setPosition(250, 720);
    cel.loadFromFile("texture/celownik.png");
    celownik.setTexture(cel);
    celownik.setOrigin(255, 750);
    celownik.setPosition(250, 720);
    celownik.setColor(Color(220, 220, 220, 160));
    buffer.loadFromFile("sound/drop.ogg");
    drop.setBuffer(buffer);
    drop.setVolume(60.0f);
    licznik=0;
}
Vector2f Pilka::pozycja()
{
    return this->circle.getPosition();
}
void Pilka::celuj(Combo &combo, Event &event)
{
    combo.liczCombo=0;
    if(licz==0)
    {
        celownik.setPosition(pozycja().x, 720);
        celownik.setColor(Color(220, 220, 220, 170));
        licz=1;
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Space))
    {
        strzal=true;
    }

    if(Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
    {
        celownik.rotate(-1.0f);
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
    {
        celownik.rotate(1.0f);
    }
    if(celownik.getRotation()==280.0f)
    {
        celownik.rotate(1.0f);
    }
    if(celownik.getRotation()==80.0f)
    {
        celownik.rotate(-1.0f);
    }
    if(strzal==true)
    {
        if(licznik<55)
        {
            licznik++;
        }
        if(licznik<44)
        {
            celownik.setColor(Color(220, 220, 220, znikanie));
            znikanie-=4.0f;
        }
        if(licznik==54)
        {
            celownik.setColor(Color(220, 220, 220, 0));
            if(celownik.getRotation()>=0 && celownik.getRotation()<=80)
            {
                ac=celownik.getRotation();
                bc=180.0f-(ab+ac);
                a=predkosc*sin(ac*M_PI/180);
                b=sqrt(pow(predkosc, 2)-pow(a, 2));
                velocity.x=a;
                velocity.y=-b;
            }


            else if(celownik.getRotation()<=359 && celownik.getRotation()>280)
            {
                ac=360-celownik.getRotation();
                bc=180.0f-(ab+ac);
                a=predkosc*sin(ac*M_PI/180);
                b=sqrt(pow(predkosc, 2)-pow(a, 2));
                velocity.x=-a;
                velocity.y=-b;
            }
            trwaStrzal=true;
            strzal=false;
            licznik=0;
        }
    }
}
void Pilka::wystrzal()
{
    this->circle.move(velocity);

    if(x()-10<15)
    {
        velocity.x=a;
    }
    else if(x()+10>485)
    {
        velocity.x=-a;
    }
    if(y()+10<95)
    {
        velocity.y=b;
    }
    else if(y()>720)
    {
        generat=true;
        circle.setPosition(x(), 720);
        velocity.x=0;
        velocity.y=0;
        trwaStrzal=false;
        znikanie=170.0f;
        licz=0;
    }

}
void Pilka::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->circle, state);
    target.draw(this->celownik, state);
}
float Pilka::x()
{
    return this->circle.getPosition().x;
}
float Pilka::y()
{
    return this->circle.getPosition().y;
}
float Pilka::left()
{
    return circle.getPosition().x-10.0f;
}
float Pilka::right()
{
    return circle.getPosition().x+10.0f;
}
float Pilka::top()
{
    return circle.getPosition().y-10.0f;
}
float Pilka::bottom()
{
    return circle.getPosition().y+10.0f;
}
void Pilka::moveUp()
{
    drop.play();
    velocity.y=-b;
}
void Pilka::moveDown()
{
    drop.play();
    velocity.y=b;
}
void Pilka::moveLeft()
{
    drop.play();
    velocity.x=-a;
}
void Pilka::moveRight()
{
    drop.play();
    velocity.x=a;
}
void Pilka::changeColor(int i)
{
    if(i==1)
    {
        circle.setFillColor(Color(255,255,255));
    }
    else if(i==2)
    {
        circle.setFillColor(Color(30,220,255));
    }
    else if(i==3)
    {
        circle.setFillColor(Color(200,100,100));
    }
}

//////////////////////////////
/////////INTERFEJS////////////
//////////////////////////////

Interfejs::Interfejs()
{
    ramka.loadFromFile("texture/rama.png");
    uramka.setTexture(ramka);
}
void Interfejs::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->uramka, state);
}
Tlo::Tlo()
{
    tlo.loadFromFile("texture/tlo.png");
    utlo.setTexture(tlo);
}
void Tlo::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->utlo, state);
}
//////////////////////////////
/////////KWADART//////////////
//////////////////////////////
Kwadrat::Kwadrat()
{
    rectangle.setFillColor(Color::White);
    rectangle.setSize({88, 88});
    rectangle.setPosition(x, y);
    los1=0;
    los2=0;
    los3=130;
    font.loadFromFile("font/KozGoPr6N.otf");

}
void Kwadrat::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->rectangle, state);
    target.draw(this->tekst, state);
}
void Kwadrat::generuj(bool &generat, int i)
{

    if(i==0 && x!=20)
        x=20;
    if(i==1 && x!=113)
        x=113;
    if(i==2 && x!=206)
        x=206;
    if(i==3 && x!=299)
        x=299;
    if(i==4 && x!=113)
        x=392;


    rectangle.setFillColor(Color(100, los3, 160));
    rectangle.setPosition(x, y);
    tekst.setColor(Color(255,255,255));
    tekst.setPosition(x+5.0f, y);


    generat=false;
}
float Kwadrat::yp()
{
    return this->rectangle.getPosition().y;
}
void Kwadrat::update()
{
    down=true;
    this->rectangle.move(velocity);
    this->tekst.move(velocity);
    velocity.y=v;
    licznik++;
    if(rectangle.getPosition().y>600.0f)
    {
        licznik=0;
        koniecGry=true;
    }
    if(licznik==31)
    {
        licznik=0;
        down=false;
    }

}
float Kwadrat::left()
{
    return rectangle.getPosition().x;
}
float Kwadrat::right()
{
    return rectangle.getPosition().x+88.0f;
}
float Kwadrat::top()
{
    return rectangle.getPosition().y;
}
float Kwadrat::bottom()
{
    return rectangle.getPosition().y+88.0f;
}

void Kwadrat::poziom(int ile, int jaki)
{
    if(ile==0)
    {
        ile=1;
    }
    if(ile>1)
    {
        if(jaki!=taki)
        {
            ile++;
        }
        ile=round(float(ile+rand()%ile)*3);
    }
    rectangle.setFillColor(Color(((ile/3)*2), 170, 120));
    taki=jaki;
    pkt=ile;
    ostringstream ss;
    ss<<pkt;
    str=ss.str();
    punkty=str;
    tekst.setFont(font);
    tekst.setCharacterSize(24);
    tekst.setString(punkty);
}
void Kwadrat::odswiez()
{
    ostringstream ss;
    ss<<pkt;
    str=ss.str();
    punkty=str;
    tekst.setString(punkty);

    if(pkt<=0)
    {
        tekst.setCharacterSize(0);
        tekst.setColor(Color(0,0,0,0));
        rectangle.setPosition(-1000, 167);
        rectangle.setFillColor(Color(0,0,0,0));
    }
}
Combo::Combo(float px, float py)
{
    texture.loadFromFile("texture/oc.png");
    ogien.setTexture(texture);
    ogien.setColor(Color(0,0,0,0));
    ogien.setOrigin(194, 239);
    ogien.setPosition(px/2, py/2);
    ogien.setScale(0.3f, 0.3f);
}
void Combo::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->ogien, state);
}
void Combo::update()
{
        v=v-0.001f;
        znik+=3;
        ogien.setScale(v, v);
        ogien.setColor(Color(255, 255, 255, znik));
        if(znik>=250)
        {
            znik=0;
            v=0.4f;
            ogien.setColor(Color(255, 255, 255, 0));
            ogien.setScale(0.3f, 0.3f);
            liczCombo=0;
            wykonajCombo=false;
        }
}
Menu::Menu()
{
    texture.loadFromFile("texture/menu.png");
    menu.setTexture(texture);
    textureUSTW.loadFromFile("texture/menuUST.png");
    ustw.setTexture(textureUSTW);
    buffer.loadFromFile("sound/click.ogg");
    click.setBuffer(buffer);
}
void Menu::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->menu, state);
    if(ustwON==true)
    {
        target.draw(this->ustw, state);
    }
}
void Menu::update(Window &window, Pilka &pilka)
{
    if(ustwON==false)
    {
        if(Mouse::getPosition(window).x>120.0f &&Mouse::getPosition(window).y>140.0f
        && Mouse::getPosition(window).x<380.0f &&Mouse::getPosition(window).y<200.0f
        && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            menuON=false;
        }
        else if(Mouse::getPosition(window).x>120.0f &&Mouse::getPosition(window).y>410.0f
                && Mouse::getPosition(window).x<380.0f &&Mouse::getPosition(window).y<470.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            window.close();
        }

    }
    else if(ustwON==true)
    {
        if(Mouse::getPosition(window).x>20.0f &&Mouse::getPosition(window).y>750.0f
            && Mouse::getPosition(window).x<60.0f &&Mouse::getPosition(window).y<790.0f
            && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            ustwON=false;
        }
        else if(Mouse::getPosition(window).x>160.0f &&Mouse::getPosition(window).y>360.0f
                && Mouse::getPosition(window).x<340.0f &&Mouse::getPosition(window).y<410.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            pilka.changeColor(1);
        }
        else if(Mouse::getPosition(window).x>160.0f &&Mouse::getPosition(window).y>420.0f
                && Mouse::getPosition(window).x<340.0f &&Mouse::getPosition(window).y<470.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            pilka.changeColor(2);
        }
        else if(Mouse::getPosition(window).x>160.0f &&Mouse::getPosition(window).y>460.0f
                && Mouse::getPosition(window).x<340.0f &&Mouse::getPosition(window).y<530.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            pilka.changeColor(3);
        }
        else if(Mouse::getPosition(window).x>160.0f &&Mouse::getPosition(window).y>120.0f
                && Mouse::getPosition(window).x<340.0f &&Mouse::getPosition(window).y<180.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            pilka.drop.setVolume(60.0f);
            click.setVolume(60.0f);
        }
        else if(Mouse::getPosition(window).x>160.0f &&Mouse::getPosition(window).y>190.0f
                && Mouse::getPosition(window).x<340.0f &&Mouse::getPosition(window).y<250.0f
                && Mouse::isButtonPressed(Mouse::Left))
        {
            click.play();
            pilka.drop.setVolume(0.0f);
            click.setVolume(0.0f);
        }

    }
    if(Mouse::getPosition(window).x>120.0f &&Mouse::getPosition(window).y>275.0f
        && Mouse::getPosition(window).x<380.0f &&Mouse::getPosition(window).y<335.0f
        && Mouse::isButtonPressed(Mouse::Left) && ustwON==false)
    {
        click.play();
        ustwON=true;
    }

}


