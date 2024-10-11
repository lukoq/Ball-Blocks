#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


class Kwadrat;
class Combo;


class Pilka :public Drawable
{
public:
    Pilka();
    Vector2f pozycja();
    void celuj(Combo &combo, Event &event);
    void wystrzal();
    bool strzal=false;
    bool trwaStrzal=false;
    bool generat=false;
    int licznik=0;
    void draw(RenderTarget& target, RenderStates state) const override;
    float x();
    float y();
    int moc=1;
    float left();
    float right();
    float top();
    float bottom();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void changeColor(int i);
    Sound drop;
private:
    CircleShape circle;
    Texture cel;
    SoundBuffer buffer;
    Sprite celownik;
    Vector2f velocityCelownika{v, v};
    float predkosc{5.0f};
    Vector2f velocity{predkosc, predkosc};
    float r{10.0f};
    float znikanie{170.0f};
    float v{6.0f};
    float a{0.0f};
    float b{0.0f};
    float ab{90.0f};
    float bc{0.0f};
    float ac{0.0f};
    int licz=0;
    bool zmiana_punktow;
};
class Interfejs :public Drawable
{
public:
    Interfejs();
    void bonus(int czas);
    void draw(RenderTarget& target, RenderStates state) const override;
private:
    Texture ramka;
    Sprite uramka;
};
class Tlo :public Drawable
{
public:
    Tlo();
    void draw(RenderTarget& target, RenderStates state) const override;
private:
    Texture tlo;
    Sprite utlo;
};
class Kwadrat :public Drawable
{
public:
    Kwadrat();
    void generuj(bool &generat, int i);
    void update();
    void draw(RenderTarget& target, RenderStates state) const override;
    float bottom();
    float top();
    float left();
    float right();
    bool down=false;
    int pkt;
    sf::String punkty;
    string str;
    Font font;
    Text tekst;
    int taki=0;
    void poziom(int ile, int jaki);
    void odswiez();
    bool kill=false;
    bool koniecGry=false;
private:
    RectangleShape rectangle;
    float v{3.0f};
    Vector2f velocity{0, v};
    int los1;
    int los2;
    int los3;
    float x{19};
    float y{74};
    float opacity{255};
    float yp();
    int licznik=0;
};
class Combo :public Drawable
{
public:
    bool wykonajCombo=false;
    int liczCombo=0;
    Combo(float px, float py);
    void draw(RenderTarget& target, RenderStates state) const override;
    void update();
private:
    Texture texture;
    Sprite ogien;
    float v{0.4f};
    float znik{0};
};
class Menu :public Drawable
{
public:
    Menu();
    void draw(RenderTarget& target, RenderStates state) const override;
    void update(Window &window, Pilka &pilka);
    bool menuON=true;
    bool ustwON=false;
private:
    Texture texture;
    Texture textureUSTW;
    Sprite menu;
    Sprite ustw;
    SoundBuffer buffer;
    Sound click;

};
