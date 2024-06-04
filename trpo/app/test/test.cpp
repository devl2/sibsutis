#include <gtest/gtest.h>
#include "../game/quiz.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

RenderWindow window(VideoMode(w, h - 200), "QuizRunner");

int win(){return 0;}

void fonwin(Vector2f& pos)
{
    Font arial;
    arial.loadFromFile("app/Arial/arial_bolditalicmt.ttf");
    wintexture.loadFromFile("app/images/win.png");
    winsprite.setTexture(wintexture);
    winsprite.setPosition(650,450);
    Text p1(k[kol_vo] , arial, 100);
    Text p2("/ 10", arial, 100);
    p1.setPosition(w / 2 -170, h/2);
    p2.setPosition(w / 2 - 50, h / 2); // поменять место 
    window.clear();

    if (backsprite.getGlobalBounds().contains(pos.x, pos.y)) { backsprite.setColor(Color(255, 250, 0)); }
    else { backsprite.setColor(Color::White); }

    whosprite.setPosition(w / 2 - 300, -20);

    window.draw(Fonsprite);
    window.draw(whosprite);
    window.draw(winsprite);
    window.draw(backsprite);
    window.draw(p1);
    window.draw(p2);
    window.display();
}
void hod(Vector2f& pos)
{
    if (p0S.getGlobalBounds().contains(pos.x, pos.y)) { poswin = 0;  }
    if (p1S.getGlobalBounds().contains(pos.x, pos.y)) { poswin = 1; }
    if (p2S.getGlobalBounds().contains(pos.x, pos.y)) { poswin = 2; }
    if (p3S.getGlobalBounds().contains(pos.x, pos.y)) { poswin = 3; }
}

//lib's
void playerlib()
{
    messitexture.loadFromFile("app/players/messi.jpg");
    mbappetexture.loadFromFile("app/players/mbappe.jpg");
    noyertexture.loadFromFile("app/players/noyer.jpg");
    neymartexture.loadFromFile("app/players/neymar.jpg");

    akinfeevtexture.loadFromFile("app/players/akinfeev.jpg");
    bufontexture.loadFromFile("app/players/bufon.jpg");
    modrictexture.loadFromFile("app/players/modric.jpg");

    oblaktexture.loadFromFile("app/players/yan_oblak.jpg");
    suarestexture.loadFromFile("app/players/suares.jpg");
    zlatantexture.loadFromFile("app/players/zlatan.jpg");

    oblaksprite.setTexture(oblaktexture);
    suaressprite.setTexture(suarestexture);
    zlatansprite.setTexture(zlatantexture);
    
    messiprite.setTexture(messitexture);
    mbappesprite.setTexture(mbappetexture);
    noyersprite.setTexture(noyertexture);
    neymarsprite.setTexture(neymartexture);

    akinfeevsprite.setTexture(akinfeevtexture);
    bufonsprite.setTexture(bufontexture);
    modricsprite.setTexture(modrictexture);
    
}
void clublib()
{
    BarcelonaT.loadFromFile("app/club/barcelona.png");
    BavariaT.loadFromFile("app/club/bayern-munich.png");
    BorissaT.loadFromFile("app/club/borussia.png");
    KobenhavnT.loadFromFile("app/club/kobenhavn.png");
    qingbaoT.loadFromFile("app/club/qingdao.png");
    RealT.loadFromFile("app/club/real-madrid.png");
    salzburgT.loadFromFile("app/club/salzburg.png");
    santosT.loadFromFile("app/club/santos.png");
    spartakT.loadFromFile("app/club/spartak.png");
    torontoT.loadFromFile("app/club/toronto.png");

    BarcelonaS.setTexture(BarcelonaT);
    BavariaS.setTexture(BavariaT);
    BorissaS.setTexture(BorissaT);
    KobenhavnS.setTexture(KobenhavnT);
    qingbaoS.setTexture(qingbaoT);
    RealS.setTexture(RealT);
    salzburgS.setTexture(salzburgT);
    santosS.setTexture(santosT);
    spartakS.setTexture(spartakT);
    torontoS.setTexture(torontoT);
}

//Quiz
void Quizplayer()
{
    playerlib();
    
    Sprite photos[Size] = { messiprite, mbappesprite, noyersprite, neymarsprite, akinfeevsprite, bufonsprite, modricsprite, suaressprite, zlatansprite,oblaksprite };

    int TrueP = rand() % 4;
    checkwin = TrueP;

    positions[TrueP] = 2;
    
    posnames[TrueP] = names[TruePlayer];
    p = photos[TruePlayer];

    int Falsep = rand() % 10;
    if (TrueP == 0)
    {
        posnames[1] = names[Falsep];
        posnames[2] = names[Falsep];
        posnames[3] = names[Falsep];
        while (posnames[0] == posnames[1]) { Falsep = rand() % 10; posnames[1] = names[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = names[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = names[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 1)
    {
        posnames[0] = names[Falsep];
        posnames[2] = names[Falsep];
        posnames[3] = names[Falsep];
        while (posnames[1] == posnames[0]) { Falsep = rand() % 10; posnames[0] = names[Falsep]; positions[0] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = names[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = names[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 2)
    {
        posnames[0] = names[Falsep];
        posnames[1] = names[Falsep];
        posnames[3] = names[Falsep];
        while (posnames[2] == posnames[0]) { Falsep = rand() % 10; posnames[0] = names[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[2])) { Falsep = rand() % 10; posnames[1] = names[Falsep]; positions[1] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = names[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 3)
    {
        posnames[0] = names[Falsep];
        posnames[1] = names[Falsep];
        posnames[2] = names[Falsep];
        while (posnames[3] == posnames[0]) { Falsep = rand() % 10; posnames[0] = names[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[3])) { Falsep = rand() % 10; posnames[1] = names[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1]) || (posnames[2] == posnames[3])) { Falsep = rand() % 10; posnames[2] = names[Falsep]; positions[2] = 1; }
    }
    
}
void Quizcountry()
{
    playerlib();

    Sprite photos[Size] = { messiprite, mbappesprite, noyersprite, neymarsprite, akinfeevsprite, bufonsprite, modricsprite, suaressprite, zlatansprite,oblaksprite };

    int TrueP = rand() % 4;
    checkwin = TrueP;
  
    positions[TrueP] = 2;

    posnames[TrueP] = country[TruePlayer];
    p = photos[TruePlayer];

    int Falsep = rand() % 10;
    if (TrueP == 0)
    {
        posnames[1] = country[Falsep];
        posnames[2] = country[Falsep];
        posnames[3] = country[Falsep];
        while (posnames[0] == posnames[1]) { Falsep = rand() % 10; posnames[1] = country[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = country[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = country[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 1)
    {
        posnames[0] = country[Falsep];
        posnames[2] = country[Falsep];
        posnames[3] = country[Falsep];
        while (posnames[1] == posnames[0]) { Falsep = rand() % 10; posnames[0] = country[Falsep]; positions[0] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = country[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = country[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 2)
    {
        posnames[0] = country[Falsep];
        posnames[1] = country[Falsep];
        posnames[3] = country[Falsep];
        while (posnames[2] == posnames[0]) { Falsep = rand() % 10; posnames[0] = country[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[2])) { Falsep = rand() % 10; posnames[1] = country[Falsep]; positions[1] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = country[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 3)
    {
        posnames[0] = country[Falsep];
        posnames[1] = country[Falsep];
        posnames[2] = country[Falsep];
        while (posnames[3] == posnames[0]) { Falsep = rand() % 10; posnames[0] = country[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[3])) { Falsep = rand() % 10; posnames[1] = country[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1]) || (posnames[2] == posnames[3])) { Falsep = rand() % 10; posnames[2] = country[Falsep]; positions[2] = 1; }
    }

}
void Quizclub()
{
    //load
    clublib();
    //photos
    Sprite photos[Size] = { BarcelonaS, BavariaS, BorissaS, KobenhavnS, qingbaoS, RealS, salzburgS, santosS, spartakS, torontoS };
    
    int TrueP = rand() % 4;
    checkwin = TrueP;

    positions[TrueP] = 2;

    posnames[TrueP] = club[TruePlayer];
    p = photos[TruePlayer];

    int Falsep = rand() % 10;
    if (TrueP == 0)
    {
        posnames[1] = club[Falsep];
        posnames[2] = club[Falsep];
        posnames[3] = club[Falsep];
        while (posnames[0] == posnames[1]) { Falsep = rand() % 10; posnames[1] = club[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = club[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = club[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 1)
    {
        posnames[0] = club[Falsep];
        posnames[2] = club[Falsep];
        posnames[3] = club[Falsep];
        while (posnames[1] == posnames[0]) { Falsep = rand() % 10; posnames[0] = club[Falsep]; positions[0] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1])) { Falsep = rand() % 10; posnames[2] = club[Falsep]; positions[2] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = club[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 2)
    {
        posnames[0] = club[Falsep];
        posnames[1] = club[Falsep];
        posnames[3] = club[Falsep];
        while (posnames[2] == posnames[0]) { Falsep = rand() % 10; posnames[0] = club[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[2])) { Falsep = rand() % 10; posnames[1] = club[Falsep]; positions[1] = 1; }
        while ((posnames[3] == posnames[0]) || (posnames[3] == posnames[1]) || (posnames[3] == posnames[2])) { Falsep = rand() % 10; posnames[3] = club[Falsep]; positions[3] = 1; }
    }
    if (TrueP == 3)
    {
        posnames[0] = club[Falsep];
        posnames[1] = club[Falsep];
        posnames[2] = club[Falsep];
        while (posnames[3] == posnames[0]) { Falsep = rand() % 10; posnames[0] = club[Falsep]; positions[0] = 1; }
        while ((posnames[1] == posnames[0]) || (posnames[1] == posnames[3])) { Falsep = rand() % 10; posnames[1] = club[Falsep]; positions[1] = 1; }
        while ((posnames[2] == posnames[0]) || (posnames[2] == posnames[1]) || (posnames[2] == posnames[3])) { Falsep = rand() % 10; posnames[2] = club[Falsep]; positions[2] = 1; }
    }

}

void mode (Vector2f& pos)
{
    mintexture.loadFromFile("app/images/whomin.png");
    minsprite.setTexture(mintexture);
    
    clubtexture.loadFromFile("app/images/club.png");
    clubsprite.setTexture(clubtexture);
    
    playertexture.loadFromFile("app/images/player.png");
    playersprite.setTexture(playertexture);

    countrytexture.loadFromFile("app/images/country.png");
    countrysprite.setTexture(countrytexture);

    backtexture.loadFromFile("app/images/back.png");
    backsprite.setTexture(backtexture);

    modetexture.loadFromFile("app/images/mode.png");
    modesprite.setTexture(modetexture);
    modesprite.setColor(Color(255, 250, 0));

    //position
    minsprite.setPosition(w / 2 - 180, 60);
    modesprite.setPosition(w / 2 - 170, 350);
    playersprite.setPosition(w/2 - 250, 500);
    countrysprite.setPosition(w / 2 - 200, 600);
    clubsprite.setPosition(w / 2 - 150, 700);
    backsprite.setPosition(w / 3 - 250, 355);
    

    if (playersprite.getGlobalBounds().contains(pos.x, pos.y)) { playersprite.setColor(Color(255, 250, 0)); }
    else { playersprite.setColor(Color::White); }
    if (clubsprite.getGlobalBounds().contains(pos.x, pos.y)) { clubsprite.setColor(Color(255, 250, 0)); }
    else { clubsprite.setColor(Color::White); }
    if (countrysprite.getGlobalBounds().contains(pos.x, pos.y)) { countrysprite.setColor(Color(255, 250, 0)); }
    else { countrysprite.setColor(Color::White); }

    if (backsprite.getGlobalBounds().contains(pos.x, pos.y)) { backsprite.setColor(Color(255, 250, 0)); }
    else { backsprite.setColor(Color::White); }


    window.clear();

    window.draw(Fonsprite);
    window.draw(minsprite);
    window.draw(modesprite);
    window.draw(playersprite);
    window.draw(countrysprite);
    window.draw(clubsprite);
    window.draw(backsprite);
    
    window.display();
}
void menu(Vector2f& pos)
{

    Fontexture.loadFromFile("app/images/Fonmenu.jpg");
    Fonsprite.setTexture(Fontexture);
    whotexture.loadFromFile("app/images/who.png");
    whosprite.setTexture(whotexture);
    playtexture.loadFromFile("app/images/play.png");
    playsprite.setTexture(playtexture);
    exittexture.loadFromFile("app/images/exit.png");
    exitsprite.setTexture(exittexture);

    //position
    Fonsprite.setPosition(0, 0);
    whosprite.setPosition(w/2-300, -20);
    playsprite.setPosition(w/2 - 200, 560);
    exitsprite.setPosition(w/2 - 200, 710);

    if (playsprite.getGlobalBounds().contains(pos.x, pos.y)) { playsprite.setColor(Color(255,250,0)); }
    else { playsprite.setColor(Color::White); }
    if (exitsprite.getGlobalBounds().contains(pos.x, pos.y)) { exitsprite.setColor(Color(255, 250, 0)); }
    else { exitsprite.setColor(Color::White); }

    window.clear();
    window.draw(Fonsprite);
    window.draw(whosprite);
    window.draw(playsprite);
    window.draw(exitsprite);
    window.display();
}

// Games
void player(Vector2f& pos)
{
    window.clear();
    window.draw(fullfonsprite);

    Font arial;
    arial.loadFromFile("app/Arial/arial_bolditalicmt.ttf");

    gamefontexture.loadFromFile("app/images/gamefon.png");
    gamefonsprite.setTexture(gamefontexture);
    fullfontexture.loadFromFile("app/images/fullfon.png");
    fullfonsprite.setTexture(fullfontexture);
    backtexture.loadFromFile("app/images/back.png");
    backsprite.setTexture(backtexture);
    gameT.loadFromFile("app/images/who is.png");

    pdT.loadFromFile("app/images/p2.png");

    p0T.loadFromFile("app/images/p.png");
    p0S.setTexture(p0T);
    p1S.setTexture(p0T);
    p2S.setTexture(p0T);
    p3S.setTexture(p0T);

    gameS.setTexture(gameT);

    gameS.setPosition(400,400);
    fullfonsprite.setPosition(0, 0);

    backsprite.setPosition(100, 200);
    if (backsprite.getGlobalBounds().contains(pos.x, pos.y)) { backsprite.setColor(Color(255, 250, 0)); }
    else { backsprite.setColor(Color::White); }

    Text p1(posnames[0], arial, 40);
    Text p2(posnames[1], arial, 40);
    Text p3(posnames[2], arial, 40);
    Text p4(posnames[3], arial, 40);

    p1.setPosition(w / 2 - 500, 520);
    p2.setPosition(w / 2 + 100, 520);
    p3.setPosition(w / 2 -500, 720);
    p4.setPosition(w / 2 + 100, 720);
    p.setPosition(w/2 - 350, 20);

    p0S.setPosition(w/2 - 600, 500);
    p1S.setPosition(w / 2 , 500);
    p2S.setPosition(w / 2 - 600, 700);
    p3S.setPosition(w / 2 , 700);

    if (p0S.getGlobalBounds().contains(pos.x, pos.y)) { p0S.setTexture(pdT); }
    else { p0S.setTexture(p0T); }
    if (p1S.getGlobalBounds().contains(pos.x, pos.y)) { p1S.setTexture(pdT); }
    else { p1S.setTexture(p0T); }
    if (p2S.getGlobalBounds().contains(pos.x, pos.y)) { p2S.setTexture(pdT); }
    else { p2S.setTexture(p0T); }
    if (p3S.getGlobalBounds().contains(pos.x, pos.y)) { p3S.setTexture(pdT); }
    else { p3S.setTexture(p0T); }

    if (names[TruePlayer] == "STOP") { m1 = 5;  TruePlayer = 0; }
    window.draw(p);
    if (Working == 1) { Quizplayer(); Working = 0; }
    if ((win() != 0))
    {
        window.draw(winsprite);
        poswin = 100;
        ret = 0;
        Working = 1;
        TruePlayer++;
    }

    window.draw(gameS);
 
    window.draw(p0S);
    window.draw(p1S);
    window.draw(p2S);
    window.draw(p3S);
    window.draw(p1);
    window.draw(p2);
    window.draw(p3);
    window.draw(p4);
    window.draw(backsprite);
    window.display();
}
void Club(Vector2f& pos)
{
    window.clear();
    window.draw(fullfonsprite);

    Font arial;
    arial.loadFromFile("app/Arial/arial_bolditalicmt.ttf");

    gamefontexture.loadFromFile("app/images/gamefon.png");
    gamefonsprite.setTexture(gamefontexture);
    fullfontexture.loadFromFile("app/images/fullfon.png");
    fullfonsprite.setTexture(fullfontexture);
    backtexture.loadFromFile("app/images/back.png");
    backsprite.setTexture(backtexture);
    
    gameT.loadFromFile("app/images/wich is.png");

    pdT.loadFromFile("app/images/p2.png");

    p0T.loadFromFile("app/images/p.png");
    p0S.setTexture(p0T);
    p1S.setTexture(p0T);
    p2S.setTexture(p0T);
    p3S.setTexture(p0T);

    fullfonsprite.setPosition(0, 0);

    gameS.setTexture(gameT);
    gameS.setPosition(400, 400);

    backsprite.setPosition(100, 200);
    if (backsprite.getGlobalBounds().contains(pos.x, pos.y)) { backsprite.setColor(Color(255, 250, 0)); }
    else { backsprite.setColor(Color::White); }

    Text p1(posnames[0], arial, 40);
    Text p2(posnames[1], arial, 40);
    Text p3(posnames[2], arial, 40);
    Text p4(posnames[3], arial, 40);

    p1.setPosition(w / 2 - 500, 520);
    p2.setPosition(w / 2 + 100, 520);
    p3.setPosition(w / 2 - 500, 720);
    p4.setPosition(w / 2 + 100, 720);
    p.setPosition(w/2 - 350, 20);

    p0S.setPosition(w / 2 - 600, 500);
    p1S.setPosition(w / 2, 500);
    p2S.setPosition(w / 2 - 600, 700);
    p3S.setPosition(w / 2, 700);

    if (club[TruePlayer] == "STOP") { m1 = 5;  TruePlayer = 0; }
    window.draw(p);
    if (Working == 1) { Quizclub(); Working = 0; }
    if ((win() != 0))
    {
        winsprite.setPosition(1300, 150);
        window.draw(winsprite);
        poswin = 100;
        ret = 0;
        Working = 1;
        TruePlayer++;
        

    }
    if (p0S.getGlobalBounds().contains(pos.x, pos.y)) { p0S.setTexture(pdT); }
    else { p0S.setTexture(p0T); }
    if (p1S.getGlobalBounds().contains(pos.x, pos.y)) { p1S.setTexture(pdT);}
    else { p1S.setTexture(p0T); }
    if (p2S.getGlobalBounds().contains(pos.x, pos.y)) { p2S.setTexture(pdT); }
    else { p2S.setTexture(p0T); }
    if (p3S.getGlobalBounds().contains(pos.x, pos.y)) { p3S.setTexture(pdT); }
    else { p3S.setTexture(p0T); }
    
    window.draw(gameS);

    window.draw(p0S);
    window.draw(p1S);
    window.draw(p2S);
    window.draw(p3S);
    window.draw(p1);
    window.draw(p2);
    window.draw(p3);
    window.draw(p4);
    window.draw(backsprite);
    window.display();
}

void Country(Vector2f& pos)
{
    window.clear();
    window.draw(fullfonsprite);

    Font arial;
    arial.loadFromFile("app/Arial/arial_bolditalicmt.ttf");

    gamefontexture.loadFromFile("app/images/gamefon.png");
    gamefonsprite.setTexture(gamefontexture);
    fullfontexture.loadFromFile("app/images/fullfon.png");
    fullfonsprite.setTexture(fullfontexture);
    backtexture.loadFromFile("app/images/back.png");
    backsprite.setTexture(backtexture);
    pdT.loadFromFile("app/images/p2.png");
    gameT.loadFromFile("app/images/where is.png");

    p0T.loadFromFile("app/images/p.png");
    p0S.setTexture(p0T);
    p1S.setTexture(p0T);
    p2S.setTexture(p0T);
    p3S.setTexture(p0T);

    fullfonsprite.setPosition(0, 0);

    backsprite.setPosition(100, 200);
    if (backsprite.getGlobalBounds().contains(pos.x, pos.y)) { backsprite.setColor(Color(255, 250, 0)); }
    else { backsprite.setColor(Color::White); }

    gameS.setTexture(gameT);
    gameS.setPosition(400, 400);


    Text p1(posnames[0], arial, 40);
    Text p2(posnames[1], arial, 40);
    Text p3(posnames[2], arial, 40);
    Text p4(posnames[3], arial, 40);

    p1.setPosition(w / 2 - 500, 520);
    p2.setPosition(w / 2 + 100, 520);
    p3.setPosition(w / 2 - 500, 720);
    p4.setPosition(w / 2 + 100, 720);
    p.setPosition(w/2 - 350, 20);

    p0S.setPosition(w / 2 - 600, 500);
    p1S.setPosition(w / 2, 500);
    p2S.setPosition(w / 2 - 600, 700);
    p3S.setPosition(w / 2, 700);

    if (p0S.getGlobalBounds().contains(pos.x, pos.y)) { p0S.setTexture(pdT); }
    else { p0S.setTexture(p0T); }
    if (p1S.getGlobalBounds().contains(pos.x, pos.y)) { p1S.setTexture(pdT); }
    else { p1S.setTexture(p0T); }
    if (p2S.getGlobalBounds().contains(pos.x, pos.y)) { p2S.setTexture(pdT); }
    else { p2S.setTexture(p0T); }
    if (p3S.getGlobalBounds().contains(pos.x, pos.y)) { p3S.setTexture(pdT); }
    else { p3S.setTexture(p0T); }

    window.draw(p);
    if (Working == 1) { Quizcountry(); Working = 0; }
    if ((win() != 0))
    {
        winsprite.setPosition(1300, 150);
        window.draw(winsprite);
        poswin = 100;
        ret = 0;
        Working = 1;
        TruePlayer++;
        

    }
    if (country[TruePlayer] == "STOP") { m1 = 5;  TruePlayer = 0; }

    window.draw(gameS);

    window.draw(p0S);
    window.draw(p1S);
    window.draw(p2S);
    window.draw(p3S);
    window.draw(p1);
    window.draw(p2);
    window.draw(p3);
    window.draw(p4);
    window.draw(backsprite);
    window.display();
}

bool mockLoadFromFile(sf::Texture& texture, const std::string& filename) {
    return texture.create(100, 100); // Создание фиктивной текстуры размером 100x100
}

// Переопределение функции загрузки текстуры для тестирования
void mockPlayerLib() {
    mockLoadFromFile(messitexture, "app/players/messi.jpg");
    mockLoadFromFile(mbappetexture, "app/players/mbappe.jpg");
    mockLoadFromFile(noyertexture, "app/players/noyer.jpg");
    mockLoadFromFile(neymartexture, "app/players/neymar.jpg");
    mockLoadFromFile(akinfeevtexture, "app/players/akinfeev.jpg");
    mockLoadFromFile(bufontexture, "app/players/bufon.jpg");
    mockLoadFromFile(modrictexture, "app/players/modric.jpg");
    mockLoadFromFile(oblaktexture, "app/players/yan_oblak.jpg");
    mockLoadFromFile(suarestexture, "app/players/suares.jpg");
    mockLoadFromFile(zlatantexture, "app/players/zlatan.jpg");

    oblaksprite.setTexture(oblaktexture);
    suaressprite.setTexture(suarestexture);
    zlatansprite.setTexture(zlatantexture);
    messiprite.setTexture(messitexture);
    mbappesprite.setTexture(mbappetexture);
    noyersprite.setTexture(noyertexture);
    neymarsprite.setTexture(neymartexture);
    akinfeevsprite.setTexture(akinfeevtexture);
    bufonsprite.setTexture(bufontexture);
    modricsprite.setTexture(modrictexture);
}

void mockClubLib() {
    mockLoadFromFile(BarcelonaT, "app/club/barcelona.png");
    mockLoadFromFile(BavariaT, "app/club/bayern-munich.png");
    mockLoadFromFile(BorissaT, "app/club/borussia.png");
    mockLoadFromFile(KobenhavnT, "app/club/kobenhavn.png");
    mockLoadFromFile(qingbaoT, "app/club/qingdao.png");
    mockLoadFromFile(RealT, "app/club/real-madrid.png");
    mockLoadFromFile(salzburgT, "app/club/salzburg.png");
    mockLoadFromFile(santosT, "app/club/santos.png");
    mockLoadFromFile(spartakT, "app/club/spartak.png");
    mockLoadFromFile(torontoT, "app/club/toronto.png");

    BarcelonaS.setTexture(BarcelonaT);
    BavariaS.setTexture(BavariaT);
    BorissaS.setTexture(BorissaT);
    KobenhavnS.setTexture(KobenhavnT);
    qingbaoS.setTexture(qingbaoT);
    RealS.setTexture(RealT);
    salzburgS.setTexture(salzburgT);
    santosS.setTexture(santosT);
    spartakS.setTexture(spartakT);
    torontoS.setTexture(torontoT);
}

TEST(WinFunctionTest, WinCondition) {
  poswin = 2;
  checkwin = 2;
  ret = 0; 
  kol_vo = 0;

  int result = win();
  ASSERT_EQ(result, 2);
  ASSERT_EQ(kol_vo, 1); 
}

TEST(WinFunctionTest, IncorrectAnswer) {
  poswin = 1;
  checkwin = 3;
  ret = 0;
  kol_vo = 0;

  int result = win();
  ASSERT_EQ(result, 1); 
  ASSERT_EQ(kol_vo, 0); 
}

TEST(WinFunctionTest, InvalidInput) {
  poswin = 100;
  checkwin = 2;
  ret = 0; 
  kol_vo = 0;

  int result = win();
  ASSERT_EQ(result, 0); 
  ASSERT_EQ(kol_vo, 0); 
}

TEST(PlayerLibTest, TexturesLoadCorrectly) {
  playerlib();
  ASSERT_TRUE(messitexture.getSize().x > 0);
  ASSERT_TRUE(mbappetexture.getSize().x > 0);
  ASSERT_TRUE(noyertexture.getSize().x > 0);
  ASSERT_TRUE(neymartexture.getSize().x > 0);
  ASSERT_TRUE(akinfeevtexture.getSize().x > 0);
  ASSERT_TRUE(bufontexture.getSize().x > 0);
  ASSERT_TRUE(modrictexture.getSize().x > 0);
  ASSERT_TRUE(oblaktexture.getSize().x > 0);
  ASSERT_TRUE(suarestexture.getSize().x > 0);
  ASSERT_TRUE(zlatantexture.getSize().x > 0);
}

TEST(ClubLibTest, TexturesLoadCorrectly) {
  clublib();
  ASSERT_TRUE(BarcelonaT.getSize().x > 0);
  ASSERT_TRUE(BavariaT.getSize().x > 0);
  ASSERT_TRUE(BorissaT.getSize().x > 0);
  ASSERT_TRUE(KobenhavnT.getSize().x > 0);
  ASSERT_TRUE(qingbaoT.getSize().x > 0);
  ASSERT_TRUE(RealT.getSize().x > 0);
  ASSERT_TRUE(salzburgT.getSize().x > 0);
  ASSERT_TRUE(santosT.getSize().x > 0);
  ASSERT_TRUE(spartakT.getSize().x > 0);
  ASSERT_TRUE(torontoT.getSize().x > 0);
}

TEST(QuizplayerTest, ValidTruePlayer) {
  srand(static_cast<unsigned int>(time(nullptr)));
  Quizplayer();
  ASSERT_TRUE(checkwin >= 0 && checkwin < 4);
  ASSERT_TRUE(positions[checkwin] == 2);
  ASSERT_TRUE(posnames[checkwin] == names[TruePlayer]);
}

TEST(QuizplayerTest, ValidFalsePlayers) {
  srand(time(nullptr));
  Quizplayer();
  for (int i = 0; i < 4; ++i) {
      if (i != checkwin) {
          ASSERT_NE(posnames[i], names[TruePlayer]);
      }
  }
}

TEST(LibraryTest, PlayerLibTexturesLoad) {
    mockPlayerLib();

    // Проверка установки текстур
    EXPECT_EQ(messiprite.getTexture(), &messitexture);
    EXPECT_EQ(mbappesprite.getTexture(), &mbappetexture);
    EXPECT_EQ(noyersprite.getTexture(), &noyertexture);
    EXPECT_EQ(neymarsprite.getTexture(), &neymartexture);
    EXPECT_EQ(akinfeevsprite.getTexture(), &akinfeevtexture);
    EXPECT_EQ(bufonsprite.getTexture(), &bufontexture);
    EXPECT_EQ(modricsprite.getTexture(), &modrictexture);
    EXPECT_EQ(oblaksprite.getTexture(), &oblaktexture);
    EXPECT_EQ(suaressprite.getTexture(), &suarestexture);
    EXPECT_EQ(zlatansprite.getTexture(), &zlatantexture);
}

TEST(LibraryTest, ClubLibTexturesLoad) {
    mockClubLib();

    // Проверка установки текстур
    EXPECT_EQ(BarcelonaS.getTexture(), &BarcelonaT);
    EXPECT_EQ(BavariaS.getTexture(), &BavariaT);
    EXPECT_EQ(BorissaS.getTexture(), &BorissaT);
    EXPECT_EQ(KobenhavnS.getTexture(), &KobenhavnT);
    EXPECT_EQ(qingbaoS.getTexture(), &qingbaoT);
    EXPECT_EQ(RealS.getTexture(), &RealT);
    EXPECT_EQ(salzburgS.getTexture(), &salzburgT);
    EXPECT_EQ(santosS.getTexture(), &santosT);
    EXPECT_EQ(spartakS.getTexture(), &spartakT);
    EXPECT_EQ(torontoS.getTexture(), &torontoT);
}

