//stack new my-project
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>

//cd Desktop/adaptiveprogrammingSFML/snake
//open main.cpp
//g++ -std=c++17 main.cpp -o main -DSFML_STATIC -I/Users/wolfsinem/Desktop/SFML/include -L/Users/wolfsinem/Desktop/SFML/lib  -lsfml-graphics -lsfml-window -lsfml-system
// ./main

using namespace sf;

int N=35, M=35; //breedte x lengte
int size=16; //dimension
int w = size*N; //window width
int h = size*M; //window height
int score=0;
int newScore;
int highScore;
int game=0;
int dir, num=1; //directie worm en num is lengte

struct snake{
    int x,y;
}s[100]; //de maximale lengte van de worm, array stores location of each part of snake

struct Fruit{ //fruit location
    int x,y;
}f;

struct Poison{ //poison location
    int x,y;
}p;

//move function snake
void Tick()
{
    for (int i=num;i>0;--i) //st
    {s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    
    //directie van de snake
    if (dir==0) s[0].y+=1; //beneden
    if (dir==1) s[0].x-=1; //links
    if (dir==2) s[0].x+=1; //rechts
    if (dir==3) s[0].y-=1; //boven
    
    if ((s[0].x==f.x) && (s[0].y==f.y)) //if snake eats fruit
    {
        num++;
        score++;
        f.x=rand() % N;
        f.y=rand() % M;
    }
    
    if ((s[0].x==p.x) && (s[0].y==p.y)) //if snake eats poison
    {
        num = 1; //snake decreases
        score = 0; //score decreases
        p.x=rand() % N;
        p.y=rand() % M;
    }
    
    for (int i=1;i<=num;i++)
        if ((s[0].x==s[i].x) && (s[0].y==s[i].y)) //if snake eats itself
        {
            num = 1; //snake starts over
            score = 0; //score starts over
        }
    
    //aantal punten is de lengte van de snake
    for (int i=1;i<=num;i++)
    {
        if (s[0].x==s[i].x && s[0].y==s[i].y)
        {
            num=i;
            score=i;
        }
    }
    
    //als highscore wordt behaald
    if (score > highScore)
    {
        highScore = score;
    }
    
//    //left window
//    if (s[i].getPosition().x <= 0 )
//    //top window
//    if ( sprite.getPosition().y <= 0 ) { }
//    //right window
//    if ( sprite.getPosition().x + sprite.getLocalBounds().width >= window.getSize().x ) { }
//    //bottom window
//    if ( sprite.getPosition().y + sprite.getLocalBounds().height >= window.getSize().y ) { }
    
    //teleporteren van de ene zijde naar de tegenovergestelde
    if (s[0].x>N) s[0].x=0;
    if (s[0].x<0) s[0].x=N;

    if (s[0].y>M) s[0].y=0;
    if (s[0].y<0) s[0].y=M;
    
    //game over
//    for (int i=1; i<num; i++)
//        if (s[0].x==s[i].x && s[0].y==s[i].y) {num=i;}
}

int main(){
    
    //punten telling
    sf::Font letter;
    letter.loadFromFile("images2/CaviarDreams.ttf");
    std::ostringstream Score;
    std::ostringstream High;
    //    Score<<"Score: "<<score;
    //    High<<"Highscore: "<<highScore;
    
    Text text,text2;
    text.setCharacterSize(30);
    text.setPosition({10,10});
    text.setFont(letter);
    text.setString(Score.str());
    text.setColor(sf::Color::Black);
    
    text2.setCharacterSize(30);
    text2.setPosition({10,35});
    text2.setFont(letter);
    text2.setString(High.str());
    text2.setColor(sf::Color::Red);
    
    //    sf::Font font;
    //    if (!font.loadFromFile("images2/CaviarDreams.ttf"))
    //    {
    //        std::cout<<"\nError in loading font file.\n";
    //    }
    //    sf::Text text;
    //    text.setFont(font);
    //    text.setCharacterSize(40);
    //    text.setColor(sf::Color::Black);
    
    srand(time(0));
    
    RenderWindow window(VideoMode (w,h),"Snake Game");
    
    Texture t1, t2, t3,t4,t5;
    t1.loadFromFile("images2/white.png"); //background grid
    t2.loadFromFile("images2/red.png"); //poison
    t3.loadFromFile("images2/green.png"); //fruit
    t4.loadFromFile("images2/backgroundd.png"); //background
    t5.loadFromFile("images2/snake.png"); //snake
    
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    Sprite sprite5(t5);
    
    //snelheid snake
    Clock clock;
    float timer=0, delay=0.1;
    
    //locatie fruit eerste keer
    f.x=10;
    f.y=10;
    
    //locatie poison eerste keer
    p.x=15;
    p.y=15;

    
    while(window.isOpen())
    {
        
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //standaard
        Event e;
        while(window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        
        //toetsen die richting bepalen
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0; //default
        
        if (timer>delay) {timer=0; Tick();}
        
        //draw//
        window.clear();
        
//        grid-achtergrond
        for (int i=0; i==N; i++)
            for (int j=0; j==M; j++)
                { sprite1.setPosition(i*size,j*size); window.draw(sprite1); }
        
        window.draw(sprite4);
        
        //punten
        window.draw(text);
        Score.str("");
        Score<<"Score: "<<score;
        text.setString(Score.str());
        
        //        text.setString("Punten: " + std::to_string(long(num)));
        //        text.setPosition(50,50);
        //        window.draw(text);
        
        window.draw(text2);
        High.str("");
        High<<"Highscore: "<<highScore;
        text2.setString(High.str());
        
        //snake
        for (int i=0;i<num;i++)
        {sprite5.setPosition(s[i].x*size,s[i].y*size); window.draw(sprite5);}
        
        //fruit
        sprite3.setPosition(f.x*size, f.y*size); window.draw(sprite3);
        
        //poison
        sprite2.setPosition(p.x*size, p.y*size); window.draw(sprite2);
        
        
//        if (game){
//            std::cout<<">>Game Over<<\n Score: "<<score<<"\n";
//            system("pause");
//            window.close();
//        }
//
        window.display();
    }
    return 0;
}
