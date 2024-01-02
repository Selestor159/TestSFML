#include <SFML/Graphics.hpp>


using namespace sf;


float offsetX=0, offsetY=0;


const int H = 12;
const int W = 40;
int sz = 64;

String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                        B        BBBB      BB",
"B                        BBBBB    BB        BB",
"BBB BBBBBBB    B    BBBBBBB       BB        BB",                      
"B         B    B    B             BB        BB",
"B         B    B    B  BBB   BBBBBBBBB      BB",
"B         B    BB   BBBBBB   BBBBBBBBB      BB",
"BBB  BB   B    BB			                 BB",
"B    BB  BB    BB                BB    BB   BB",
"B    BB        BB   BBBBBBBBBB    BB  BB    BB",
"B   BBB        BB   BBBBBBBBBB      BB      BB",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

}; 

class PLAYER {

public:

float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;

    PLAYER(Texture &image)
   {
	sprite.setTexture(image);
	rect = FloatRect(6*sz,8*sz,40,83);

	dx=dy=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {	

	 rect.left += dx * time;	
	 Collision(0);

	 rect.top += dy*time;
	 Collision(1);
  
	 
	  currentFrame += 0.005*time;
	  if (currentFrame > 8) currentFrame -=8 ;

	  if (dx>0) sprite.setTextureRect(IntRect(83*int(currentFrame),83,83,83));
	  if (dx<0) sprite.setTextureRect(IntRect(83*int(currentFrame)+83,83,-83,83));
	 

	  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	  dx = 0;
	  dy = 0;
   }



   void Collision(int dir)
   {
     for (int i = rect.top/sz ; i<(rect.top+rect.height)/sz; i++)
	  for (int j = rect.left/sz; j<(rect.left+rect.width)/sz; j++)
		{ 
	  	 if (TileMap[i][j]=='B') 
		   { 
	        if ((dx>0) && (dir==0)) rect.left =  j*sz -  rect.width; 
		    if ((dx<0) && (dir==0)) rect.left =  j*sz + sz;
			if ((dy>0) && (dir==1))  { rect.top =   i*sz -  rect.height; }
			if ((dy<0) && (dir==1))  { rect.top = i*sz + sz; }
		   }
		 
		 if (TileMap[i][j]=='0') 
		                   { 
			                 TileMap[i][j]=' ';
		                   }
	         	
    	}
   
   }
};

int main()
{
    RenderWindow window( VideoMode(1200, 1000), "GAME!");

	Texture t;
	t.loadFromFile("123456.png");


	float currentFrame=0;

    PLAYER p(t);

    Clock clock;

	RectangleShape rectangle( Vector2f(sz,sz));


    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/700;
		
		if (time>20) time = 20;

		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

	    if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			p.dx = -0.1;

		}

	    if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			p.dy=-0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p.dy = 0.1;
		}

		p.update(time);

		if (p.rect.left>300) offsetX = p.rect.left - 300;
        offsetY = p.rect.top - 200;

		window.clear(Color::White);

		Texture  textuereWall;
		textuereWall.loadFromFile("wall.jpg");

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W ; j++)
				{ 
				  if (TileMap[i][j]=='B') rectangle.setTexture(&textuereWall);

			      if (TileMap[i][j]=='0')  rectangle.setFillColor(Color::White);

				  if (TileMap[i][j]==' ') continue;

		          rectangle.setPosition(j*sz-offsetX,i*sz - offsetY) ; 
		          window.draw(rectangle);
	       	 }
    
		window.draw(p.sprite);
        window.display();
    }

    return 0;
}




