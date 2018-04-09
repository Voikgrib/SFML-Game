
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>

//------------------------------------------
//! Class realise vector kak v geometrii
//------------------------------------------
template <typename data_t>
class my_vector
{
	public:

	data_t x;
	data_t y;
};

// Global consts and so on

const int max_bullets = 100;
sf::RenderWindow *Pwindow;

// Including class libs

#include"libs/hero_lib.h"
#include"libs/enemy_lib.h"
#include"libs/bullet_lib.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#define MOVEMENT( direction , move_x , move_y , rotation) 			\
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::direction))		\
		{															\
    		main_hero.sprite.move(move_x, move_y);					\
			main_hero.sprite.setRotation(rotation);					\
		}															\


#define ROTATING(direction , rotation)													\
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::direction))								\
		main_hero.sprite.setRotation(rotation);											\


#define SHOOTING( direction , move_x , move_y)													\
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::direction))										\
		{																						\
			cur_bullet = bullet_finder(hero_bullets, max_bullets);								\
																								\
			if(cur_bullet != NULL && cur_time - last_shoot_time > main_hero.shoot_cooldown)		\
			{																					\
				cur_bullet->sprite.setTexture(hero_bullet_texture);								\
				cur_bullet->sprite.setOrigin(cur_bullet->size.x/2, cur_bullet->size.y/2);		\
				hero_position = main_hero.sprite.getPosition();									\
				cur_bullet->sprite.setPosition(hero_position.x, hero_position.y);				\
				cur_bullet->speed.x = move_x;													\
				cur_bullet->speed.y = move_y;													\
				cur_bullet->time_of_born = cur_time;											\
				last_shoot_time = cur_time;														\
			}																					\
		}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int game_start(void);

//===================================================================
//! This programm contain my trying in graphics
//!		
//!		Author: Vladimir Gribanov
//===================================================================
int main()
{
	int my_error = 0;

	my_error = game_start();    

    return 0;
}

//-------------------------------------------------------------------
//!
//! This function contain main game sycle
//!
//-------------------------------------------------------------------
int game_start(void)
{
	sf::RenderWindow window(sf::VideoMode(1500, 900), "SHAITAN PROGA");
	window.setFramerateLimit(25);

	Pwindow = &window;

	sf::Clock main_clock;
	sf::Vector2f hero_position;
	sf::Time cur_time = main_clock.getElapsedTime();
	sf::Time last_shoot_time;

	sf::Texture enemy_texture;
	sf::Texture hero_bullet_texture;
	hero_bullet_texture.loadFromFile("shoot.png");
	enemy_texture.loadFromFile("enemy.png");
	hero_bullet_texture.setSmooth(true);

		//texture.loadFromFile(texture_adr);
		//sprite.setTexture(texture);

	int max_bullets = 250;
	int current_bullet = 0;

	class hero main_hero;
	class bullet *hero_bullets = new bullet[max_bullets];
	class bullet *cur_bullet = NULL;
	class enemy test_enemy;

	///* TEST ENTITY !

	test_enemy.sprite.setTexture(enemy_texture);
	test_enemy.sprite.setPosition(500, 500);
	test_enemy.sprite.setOrigin(test_enemy.size.x/2, test_enemy.size.y/2);
	test_enemy.is_alive = true;

	// TEST ENTITY ! */

    while (window.isOpen())		// Main sycle
    {
		cur_time = main_clock.getElapsedTime();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		MOVEMENT(D, main_hero.speed , 0 , 90)
		MOVEMENT(A, -main_hero.speed, 0 , 270)
		MOVEMENT(S, 0 , main_hero.speed , 180)
		MOVEMENT(W, 0 , -main_hero.speed, 0)

		ROTATING(Left , 270)
		ROTATING(Right, 90)
		ROTATING(Up	  , 0)
		ROTATING(Down , 180)

		SHOOTING(Left , -main_hero.bullet_speed	, 0)
		SHOOTING(Right, main_hero.bullet_speed	, 0)
		SHOOTING(Up	  , 0, -main_hero.bullet_speed )
		SHOOTING(Down , 0, main_hero.bullet_speed  )

		is_bullet_hit(hero_bullets, max_bullets, &test_enemy, 1);
		kill_dead_enemys(&test_enemy, 1); // TEST
		enemys_set_speed(&test_enemy, 1, main_hero.sprite.getPosition()); // TEST
		

		bullet_move(hero_bullets, max_bullets, main_clock.getElapsedTime());
		enemy_rotation(&test_enemy, 1); // TEST
		enemy_movement(&test_enemy, 1); // TEST

        window.clear();
		bullet_draw(hero_bullets, max_bullets);
		enemys_draw(&test_enemy, 1); // TEST
        window.draw(main_hero.sprite);
        window.display();
    }

	delete [] hero_bullets;

	return 0;
}
