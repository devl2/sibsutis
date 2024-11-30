#ifndef QUIZ_LIB_HPP
#define QUIZ_LIB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

int poswin, checkwin, ret, positions[4];
int m1 = 0;
int TruePlayer = 0;
int Working = 1;
int kol_vo = 0;
const int Size = 11;
std::string k[11] = {"0","1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

float w = sf::VideoMode::getDesktopMode().width;
float h = sf::VideoMode::getDesktopMode().height;

float ttime;

sf::Texture wintexture;
sf::Sprite winsprite;

std::string names[Size] = {"Messi", "Mbappe", "Noyer", " Neymar","Akinfeev","Bufon","Modric","Suares","Zlatan","Oblak","STOP"};
std::string country[Size] = { "Argentina", "Franch", "Germany", " Brazil","Russia","Italy","Croatia","Uruguay","Sweden","Slovenia","STOP"};
std::string club[Size] = { "Barcelona", "Bavaria", "Borissa", "Kobenhavn", "qingbao", "Real Madrid", "salzburg", "santos", "spartak", "toronto","STOP" };
std::string posnames [4];

sf::Sprite photos[Size];
sf::Sprite p;

sf::Texture Fontexture, whotexture, playtexture, exittexture;
sf::Sprite Fonsprite, whosprite, playsprite, exitsprite;

sf::Texture mintexture, clubtexture, playertexture, countrytexture, modetexture, backtexture;
sf::Sprite minsprite, clubsprite, playersprite, countrysprite, modesprite, backsprite;

sf::Texture gamefontexture, fullfontexture, p0T, p1T, p2T, p3T, pdT, gameT;
sf::Sprite gamefonsprite, fullfonsprite, p0S, p1S, p2S, p3S, gameS;

sf::Texture messitexture, mbappetexture, noyertexture, neymartexture, akinfeevtexture, bufontexture, modrictexture, suarestexture, zlatantexture, oblaktexture;
sf::Sprite messiprite, mbappesprite, noyersprite, neymarsprite, akinfeevsprite, bufonsprite, modricsprite, suaressprite, zlatansprite, oblaksprite;

sf::Texture BarcelonaT, BavariaT, BorissaT, KobenhavnT, qingbaoT, RealT, salzburgT, santosT, spartakT, torontoT;
sf::Sprite BarcelonaS, BavariaS, BorissaS, KobenhavnS, qingbaoS, RealS, salzburgS, santosS, spartakS, torontoS;

int win();
void fonwin(sf::Vector2f& pos);
void hod(sf::Vector2f& pos);
void playerlib();
void clublib();
void Quizplayer();
void Quizcountry();
void Quizclub();
void mode (sf::Vector2f& pos);
void menu(sf::Vector2f& pos);
void player(sf::Vector2f& pos);
void Club(sf::Vector2f& pos);
void Country(sf::Vector2f& pos);

#endif 
