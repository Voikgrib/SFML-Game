
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>

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
const int Max_obj = 1000;
sf::RenderWindow *Pwindow;
sf::Clock *Pclock;

// Including class libs

#include"libs/manager_lib.h"
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


#define ADDER_DECLARE( cur_class )																\
void cur_class##_adder(class manager* all_objs, class cur_class* cur_massive, int max)			\
{																								\
	int i = 0;																					\
																								\
	while(i != max)																				\
	{																							\
		all_objs->add( & cur_massive[i]);														\
																								\
		i++;																					\
	}																							\
}																								\



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int game_start(void);
sf::Texture texture_upload(char *str);

ADDER_DECLARE( bullet )
ADDER_DECLARE( enemy )

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
	float screen_high = 900;
	float screen_lengh = 1500;
	float backgr_high = screen_high / 733;
	float backgr_lengh = screen_lengh / 1100;

	sf::RenderWindow window(sf::VideoMode(screen_lengh, screen_high), "SHAITAN PROGA");
	window.setFramerateLimit(25);

	Pwindow = &window;

	sf::Clock main_clock;
	sf::Vector2f hero_position;
	sf::Time cur_time = main_clock.getElapsedTime();
	sf::Time last_shoot_time;

	Pclock = &main_clock;

	sf::Texture enemy_texture;
	sf::Texture hero_bullet_texture;
	sf::Texture backgrownd_texture;
	sf::Texture dead_screen_texture;
	sf::Texture heal_texture;

	class hero main_hero;
	
	try
	{
		heal_texture = texture_upload("hp_one.png");
		dead_screen_texture = texture_upload("dead_screen.png");
		backgrownd_texture = texture_upload("backgrownd.jpg");
		hero_bullet_texture = texture_upload("shoot.png");
		enemy_texture = texture_upload("enemy.png");
	}
	catch(char *str)
	{
		printf("!!! Error with open %s !!!\n", str);
		assert(false);
	}

	sf::Sprite backgrownd_sprite;
	sf::Sprite dead_screen_sprite;
	//sf::Sprite *heal_sprite = new sf::Sprite [max_heal];
	dead_screen_sprite.setTexture(dead_screen_texture);
	dead_screen_sprite.setOrigin(256/2, 144/2); 
	dead_screen_sprite.setPosition(screen_lengh/2, screen_high/2);
	backgrownd_sprite.setTexture(backgrownd_texture);
	backgrownd_sprite.setScale(backgr_lengh, backgr_high);
	backgrownd_sprite.setPosition(0, 0);

	

		//texture.loadFromFile(texture_adr);
		//sprite.setTexture(texture);

	int max_heal = 5;
	int max_bullets = 250;
	int current_bullet = 0;
	int max_enemy = 20;
	int cur_enemy = 0;
	int hp_position = 20;
	
	class bullet *hero_bullets = new bullet[max_bullets];
	class bullet *cur_bullet = NULL;
	class enemy *test_enemy = new enemy[max_enemy];	
	class heals *heals_massive = new heals[max_heal];

	class manager all_objs;

	// INIT HEAL     	is work, but not heal

	int cur_heal = 0;

	while(cur_heal != max_heal)
	{
		heals_massive[cur_heal].sprite.setTexture(heal_texture);
		
		cur_heal++;
	}

	///* TEST ENTITY !

	while(cur_enemy != max_enemy)
	{
		test_enemy[cur_enemy].sprite.setTexture(enemy_texture);
		test_enemy[cur_enemy].sprite.setOrigin(test_enemy[cur_enemy].size.x/2, test_enemy[cur_enemy].size.y/2);
		test_enemy[cur_enemy].is_alive = false;

		cur_enemy++;
	}

	// TEST ENTITY ! */

	//bullet_adder(&all_objs, hero_bullets, max_bullets);
	//enemy_adder(&all_objs, test_enemy, max_enemy);

	all_objs.adder(hero_bullets, max_bullets, sizeof(class bullet));
	all_objs.adder(test_enemy, max_enemy, sizeof(class enemy));

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

		mob_spawn(test_enemy, max_enemy, main_clock.getElapsedTime());

		is_bullet_hit(hero_bullets, max_bullets, test_enemy, max_enemy);
		main_hero.is_alive = is_hero_alive(&main_hero);
		player_hit(&main_hero, test_enemy, max_enemy, main_clock.getElapsedTime());
		kill_dead_enemys(test_enemy, max_enemy, heals_massive, max_heal);
		enemys_set_speed(test_enemy, max_enemy, main_hero.sprite.getPosition());
		
		enemy_rotation(test_enemy, max_enemy);

        window.clear();
		window.draw(backgrownd_sprite);
		hp_draw(main_hero);
		heals_draw(heals_massive, max_heal);
		all_objs.run();
		if(main_hero.is_alive == true)
        	window.draw(main_hero.sprite);
		else
			window.draw(dead_screen_sprite);		
        window.display();
    }

	delete [] hero_bullets;
	delete [] test_enemy;
	delete [] heals_massive;

	return 0;
}


//================================================================
//!
//! This function upload textures
//!
//================================================================
sf::Texture texture_upload(char *str)
{
	sf::Texture cur_texture;

	if(!cur_texture.loadFromFile(str))
			throw str;

	return cur_texture;
}




